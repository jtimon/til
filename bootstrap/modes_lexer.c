#include "modes_lexer.h"

Token * Token_clone(Token * self) {
    (void)self;
    U32 _t2369 = U32_clone(&self->line);
    (void)_t2369;
    U32 _t2370 = U32_clone(&self->col);
    (void)_t2370;
    Token *_t2371 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(&self->type); _t2371->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->text); _t2371->text = *_ca; free(_ca); }
    _t2371->line = _t2369;
    _t2371->col = _t2370;
    (void)_t2371;
    ;
    ;
    return _t2371;
}

void Token_delete(Token * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t2372 = 0;
    (void)_t2372;
    TokenType_delete(&self->type, &(Bool){_t2372});
    ;
    Bool _t2373 = 0;
    (void)_t2373;
    Str_delete(&self->text, &(Bool){_t2373});
    ;
    Bool _t2374 = 0;
    (void)_t2374;
    U32_delete(&self->line, &(Bool){_t2374});
    ;
    Bool _t2375 = 0;
    (void)_t2375;
    U32_delete(&self->col, &(Bool){_t2375});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *Token_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Token);
    return r;
}

Bool * is_digit(U8 * c) {
    (void)c;
    U8 _t2377 = 48;
    (void)_t2377;
    U8 _t2378 = 57;
    (void)_t2378;
    Bool _t2379; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t2377}); _t2379 = *_hp; free(_hp); }
    (void)_t2379;
    ;
    Bool _t2380; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t2378}); _t2380 = *_hp; free(_hp); }
    (void)_t2380;
    ;
    Bool _t2381 = Bool_and(_t2379, _t2380);
    (void)_t2381;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2381; return _r; }
}

Bool * is_alpha(U8 * c) {
    (void)c;
    U8 _t2382 = 97;
    (void)_t2382;
    U8 _t2383 = 122;
    (void)_t2383;
    Bool _t2384; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t2382}); _t2384 = *_hp; free(_hp); }
    (void)_t2384;
    ;
    Bool _t2385; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t2383}); _t2385 = *_hp; free(_hp); }
    (void)_t2385;
    ;
    U8 _t2386 = 65;
    (void)_t2386;
    U8 _t2387 = 90;
    (void)_t2387;
    Bool _t2388; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t2386}); _t2388 = *_hp; free(_hp); }
    (void)_t2388;
    ;
    Bool _t2389; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t2387}); _t2389 = *_hp; free(_hp); }
    (void)_t2389;
    ;
    Bool _t2390 = Bool_and(_t2384, _t2385);
    (void)_t2390;
    ;
    ;
    Bool _t2391 = Bool_and(_t2388, _t2389);
    (void)_t2391;
    ;
    ;
    U8 _t2392 = 95;
    (void)_t2392;
    Bool _t2393 = Bool_or(_t2390, _t2391);
    (void)_t2393;
    ;
    ;
    Bool _t2394 = U8_eq(DEREF(c), _t2392);
    (void)_t2394;
    ;
    Bool _t2395 = Bool_or(_t2393, _t2394);
    (void)_t2395;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2395; return _r; }
}

Bool * is_alnum(U8 * c) {
    (void)c;
    Bool _t2396; { Bool *_hp = (Bool *)is_alpha(c); _t2396 = *_hp; free(_hp); }
    (void)_t2396;
    Bool _t2397; { Bool *_hp = (Bool *)is_digit(c); _t2397 = *_hp; free(_hp); }
    (void)_t2397;
    Bool _t2398 = Bool_or(_t2396, _t2397);
    (void)_t2398;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2398; return _r; }
}

Str * tok_name(TokenType * type) {
    (void)type;
    {
        TokenType *_sw2399 = TokenType_clone(type);
        (void)_sw2399;
        Bool _t2532; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_Eof()); _t2532 = *_hp; free(_hp); }
        (void)_t2532;
        if (_t2532) {
            Str *_t2400 = Str_lit("eof", 3ULL);
            (void)_t2400;
            TokenType_delete(_sw2399, &(Bool){1});
            ;
            return _t2400;
        } else {
            Bool _t2531; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_LParen()); _t2531 = *_hp; free(_hp); }
            (void)_t2531;
            if (_t2531) {
                Str *_t2401 = Str_lit("(", 1ULL);
                (void)_t2401;
                ;
                TokenType_delete(_sw2399, &(Bool){1});
                ;
                return _t2401;
            } else {
                Bool _t2530; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_RParen()); _t2530 = *_hp; free(_hp); }
                (void)_t2530;
                if (_t2530) {
                    Str *_t2402 = Str_lit(")", 1ULL);
                    (void)_t2402;
                    ;
                    ;
                    TokenType_delete(_sw2399, &(Bool){1});
                    ;
                    return _t2402;
                } else {
                    Bool _t2529; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_LBrace()); _t2529 = *_hp; free(_hp); }
                    (void)_t2529;
                    if (_t2529) {
                        Str *_t2403 = Str_lit("{", 1ULL);
                        (void)_t2403;
                        ;
                        ;
                        ;
                        TokenType_delete(_sw2399, &(Bool){1});
                        ;
                        return _t2403;
                    } else {
                        Bool _t2528; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_RBrace()); _t2528 = *_hp; free(_hp); }
                        (void)_t2528;
                        if (_t2528) {
                            Str *_t2404 = Str_lit("}", 1ULL);
                            (void)_t2404;
                            ;
                            ;
                            ;
                            ;
                            TokenType_delete(_sw2399, &(Bool){1});
                            ;
                            return _t2404;
                        } else {
                            Bool _t2527; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_LBracket()); _t2527 = *_hp; free(_hp); }
                            (void)_t2527;
                            if (_t2527) {
                                Str *_t2405 = Str_lit("[", 1ULL);
                                (void)_t2405;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TokenType_delete(_sw2399, &(Bool){1});
                                ;
                                return _t2405;
                            } else {
                                Bool _t2526; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_RBracket()); _t2526 = *_hp; free(_hp); }
                                (void)_t2526;
                                if (_t2526) {
                                    Str *_t2406 = Str_lit("]", 1ULL);
                                    (void)_t2406;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TokenType_delete(_sw2399, &(Bool){1});
                                    ;
                                    return _t2406;
                                } else {
                                    Bool _t2525; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_Comma()); _t2525 = *_hp; free(_hp); }
                                    (void)_t2525;
                                    if (_t2525) {
                                        Str *_t2407 = Str_lit(",", 1ULL);
                                        (void)_t2407;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TokenType_delete(_sw2399, &(Bool){1});
                                        ;
                                        return _t2407;
                                    } else {
                                        Bool _t2524; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_Colon()); _t2524 = *_hp; free(_hp); }
                                        (void)_t2524;
                                        if (_t2524) {
                                            Str *_t2408 = Str_lit(":", 1ULL);
                                            (void)_t2408;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TokenType_delete(_sw2399, &(Bool){1});
                                            ;
                                            return _t2408;
                                        } else {
                                            Bool _t2523; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_Question()); _t2523 = *_hp; free(_hp); }
                                            (void)_t2523;
                                            if (_t2523) {
                                                Str *_t2409 = Str_lit("?", 1ULL);
                                                (void)_t2409;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                TokenType_delete(_sw2399, &(Bool){1});
                                                ;
                                                return _t2409;
                                            } else {
                                                Bool _t2522; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_Bang()); _t2522 = *_hp; free(_hp); }
                                                (void)_t2522;
                                                if (_t2522) {
                                                    Str *_t2410 = Str_lit("!", 1ULL);
                                                    (void)_t2410;
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
                                                    TokenType_delete(_sw2399, &(Bool){1});
                                                    ;
                                                    return _t2410;
                                                } else {
                                                    Bool _t2521; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_Minus()); _t2521 = *_hp; free(_hp); }
                                                    (void)_t2521;
                                                    if (_t2521) {
                                                        Str *_t2411 = Str_lit("-", 1ULL);
                                                        (void)_t2411;
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
                                                        TokenType_delete(_sw2399, &(Bool){1});
                                                        ;
                                                        return _t2411;
                                                    } else {
                                                        Bool _t2520; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_Plus()); _t2520 = *_hp; free(_hp); }
                                                        (void)_t2520;
                                                        if (_t2520) {
                                                            Str *_t2412 = Str_lit("+", 1ULL);
                                                            (void)_t2412;
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
                                                            TokenType_delete(_sw2399, &(Bool){1});
                                                            ;
                                                            return _t2412;
                                                        } else {
                                                            Bool _t2519; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_Star()); _t2519 = *_hp; free(_hp); }
                                                            (void)_t2519;
                                                            if (_t2519) {
                                                                Str *_t2413 = Str_lit("*", 1ULL);
                                                                (void)_t2413;
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
                                                                TokenType_delete(_sw2399, &(Bool){1});
                                                                ;
                                                                return _t2413;
                                                            } else {
                                                                Bool _t2518; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_Slash()); _t2518 = *_hp; free(_hp); }
                                                                (void)_t2518;
                                                                if (_t2518) {
                                                                    Str *_t2414 = Str_lit("/", 1ULL);
                                                                    (void)_t2414;
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
                                                                    TokenType_delete(_sw2399, &(Bool){1});
                                                                    ;
                                                                    return _t2414;
                                                                } else {
                                                                    Bool _t2517; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_Dot()); _t2517 = *_hp; free(_hp); }
                                                                    (void)_t2517;
                                                                    if (_t2517) {
                                                                        Str *_t2415 = Str_lit(".", 1ULL);
                                                                        (void)_t2415;
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
                                                                        TokenType_delete(_sw2399, &(Bool){1});
                                                                        ;
                                                                        return _t2415;
                                                                    } else {
                                                                        Bool _t2516; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_DotDot()); _t2516 = *_hp; free(_hp); }
                                                                        (void)_t2516;
                                                                        if (_t2516) {
                                                                            Str *_t2416 = Str_lit("..", 2ULL);
                                                                            (void)_t2416;
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
                                                                            TokenType_delete(_sw2399, &(Bool){1});
                                                                            ;
                                                                            return _t2416;
                                                                        } else {
                                                                            Bool _t2515; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_DotDotDot()); _t2515 = *_hp; free(_hp); }
                                                                            (void)_t2515;
                                                                            if (_t2515) {
                                                                                Str *_t2417 = Str_lit("...", 3ULL);
                                                                                (void)_t2417;
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
                                                                                TokenType_delete(_sw2399, &(Bool){1});
                                                                                ;
                                                                                return _t2417;
                                                                            } else {
                                                                                Bool _t2514; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_Eq()); _t2514 = *_hp; free(_hp); }
                                                                                (void)_t2514;
                                                                                if (_t2514) {
                                                                                    Str *_t2418 = Str_lit("=", 1ULL);
                                                                                    (void)_t2418;
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
                                                                                    TokenType_delete(_sw2399, &(Bool){1});
                                                                                    ;
                                                                                    return _t2418;
                                                                                } else {
                                                                                    Bool _t2513; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_EqEq()); _t2513 = *_hp; free(_hp); }
                                                                                    (void)_t2513;
                                                                                    if (_t2513) {
                                                                                        Str *_t2419 = Str_lit("==", 2ULL);
                                                                                        (void)_t2419;
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
                                                                                        TokenType_delete(_sw2399, &(Bool){1});
                                                                                        ;
                                                                                        return _t2419;
                                                                                    } else {
                                                                                        Bool _t2512; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_Neq()); _t2512 = *_hp; free(_hp); }
                                                                                        (void)_t2512;
                                                                                        if (_t2512) {
                                                                                            Str *_t2420 = Str_lit("!=", 2ULL);
                                                                                            (void)_t2420;
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
                                                                                            TokenType_delete(_sw2399, &(Bool){1});
                                                                                            ;
                                                                                            return _t2420;
                                                                                        } else {
                                                                                            Bool _t2511; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_Lt()); _t2511 = *_hp; free(_hp); }
                                                                                            (void)_t2511;
                                                                                            if (_t2511) {
                                                                                                Str *_t2421 = Str_lit("<", 1ULL);
                                                                                                (void)_t2421;
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
                                                                                                TokenType_delete(_sw2399, &(Bool){1});
                                                                                                ;
                                                                                                return _t2421;
                                                                                            } else {
                                                                                                Bool _t2510; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_LtEq()); _t2510 = *_hp; free(_hp); }
                                                                                                (void)_t2510;
                                                                                                if (_t2510) {
                                                                                                    Str *_t2422 = Str_lit("<=", 2ULL);
                                                                                                    (void)_t2422;
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
                                                                                                    TokenType_delete(_sw2399, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t2422;
                                                                                                } else {
                                                                                                    Bool _t2509; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_Gt()); _t2509 = *_hp; free(_hp); }
                                                                                                    (void)_t2509;
                                                                                                    if (_t2509) {
                                                                                                        Str *_t2423 = Str_lit(">", 1ULL);
                                                                                                        (void)_t2423;
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
                                                                                                        TokenType_delete(_sw2399, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t2423;
                                                                                                    } else {
                                                                                                        Bool _t2508; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_GtEq()); _t2508 = *_hp; free(_hp); }
                                                                                                        (void)_t2508;
                                                                                                        if (_t2508) {
                                                                                                            Str *_t2424 = Str_lit(">=", 2ULL);
                                                                                                            (void)_t2424;
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
                                                                                                            TokenType_delete(_sw2399, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t2424;
                                                                                                        } else {
                                                                                                            Bool _t2507; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_ColonEq()); _t2507 = *_hp; free(_hp); }
                                                                                                            (void)_t2507;
                                                                                                            if (_t2507) {
                                                                                                                Str *_t2425 = Str_lit(":=", 2ULL);
                                                                                                                (void)_t2425;
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
                                                                                                                ;
                                                                                                                TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                ;
                                                                                                                return _t2425;
                                                                                                            } else {
                                                                                                                Bool _t2506; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_Ident()); _t2506 = *_hp; free(_hp); }
                                                                                                                (void)_t2506;
                                                                                                                if (_t2506) {
                                                                                                                    Str *_t2426 = Str_lit("identifier", 10ULL);
                                                                                                                    (void)_t2426;
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
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return _t2426;
                                                                                                                } else {
                                                                                                                    Bool _t2505; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_StringTok()); _t2505 = *_hp; free(_hp); }
                                                                                                                    (void)_t2505;
                                                                                                                    if (_t2505) {
                                                                                                                        Str *_t2427 = Str_lit("string", 6ULL);
                                                                                                                        (void)_t2427;
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
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return _t2427;
                                                                                                                    } else {
                                                                                                                        Bool _t2504; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_Number()); _t2504 = *_hp; free(_hp); }
                                                                                                                        (void)_t2504;
                                                                                                                        if (_t2504) {
                                                                                                                            Str *_t2428 = Str_lit("number", 6ULL);
                                                                                                                            (void)_t2428;
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
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return _t2428;
                                                                                                                        } else {
                                                                                                                            Bool _t2503; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_Char()); _t2503 = *_hp; free(_hp); }
                                                                                                                            (void)_t2503;
                                                                                                                            if (_t2503) {
                                                                                                                                Str *_t2429 = Str_lit("char", 4ULL);
                                                                                                                                (void)_t2429;
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
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return _t2429;
                                                                                                                            } else {
                                                                                                                                Bool _t2502; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwMode()); _t2502 = *_hp; free(_hp); }
                                                                                                                                (void)_t2502;
                                                                                                                                if (_t2502) {
                                                                                                                                    Str *_t2430 = Str_lit("mode", 4ULL);
                                                                                                                                    (void)_t2430;
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
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return _t2430;
                                                                                                                                } else {
                                                                                                                                    Bool _t2501; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwMut()); _t2501 = *_hp; free(_hp); }
                                                                                                                                    (void)_t2501;
                                                                                                                                    if (_t2501) {
                                                                                                                                        Str *_t2431 = Str_lit("mut", 3ULL);
                                                                                                                                        (void)_t2431;
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
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return _t2431;
                                                                                                                                    } else {
                                                                                                                                        Bool _t2500; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwOwn()); _t2500 = *_hp; free(_hp); }
                                                                                                                                        (void)_t2500;
                                                                                                                                        if (_t2500) {
                                                                                                                                            Str *_t2432 = Str_lit("own", 3ULL);
                                                                                                                                            (void)_t2432;
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
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return _t2432;
                                                                                                                                        } else {
                                                                                                                                            Bool _t2499; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwRef()); _t2499 = *_hp; free(_hp); }
                                                                                                                                            (void)_t2499;
                                                                                                                                            if (_t2499) {
                                                                                                                                                Str *_t2433 = Str_lit("ref", 3ULL);
                                                                                                                                                (void)_t2433;
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
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return _t2433;
                                                                                                                                            } else {
                                                                                                                                                Bool _t2498; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwShallow()); _t2498 = *_hp; free(_hp); }
                                                                                                                                                (void)_t2498;
                                                                                                                                                if (_t2498) {
                                                                                                                                                    Str *_t2434 = Str_lit("shallow", 7ULL);
                                                                                                                                                    (void)_t2434;
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
                                                                                                                                                    TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                    ;
                                                                                                                                                    return _t2434;
                                                                                                                                                } else {
                                                                                                                                                    Bool _t2497; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwStruct()); _t2497 = *_hp; free(_hp); }
                                                                                                                                                    (void)_t2497;
                                                                                                                                                    if (_t2497) {
                                                                                                                                                        Str *_t2435 = Str_lit("struct", 6ULL);
                                                                                                                                                        (void)_t2435;
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
                                                                                                                                                        TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                        ;
                                                                                                                                                        return _t2435;
                                                                                                                                                    } else {
                                                                                                                                                        Bool _t2496; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwExtStruct()); _t2496 = *_hp; free(_hp); }
                                                                                                                                                        (void)_t2496;
                                                                                                                                                        if (_t2496) {
                                                                                                                                                            Str *_t2436 = Str_lit("ext_struct", 10ULL);
                                                                                                                                                            (void)_t2436;
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
                                                                                                                                                            TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                            ;
                                                                                                                                                            return _t2436;
                                                                                                                                                        } else {
                                                                                                                                                            Bool _t2495; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwEnum()); _t2495 = *_hp; free(_hp); }
                                                                                                                                                            (void)_t2495;
                                                                                                                                                            if (_t2495) {
                                                                                                                                                                Str *_t2437 = Str_lit("enum", 4ULL);
                                                                                                                                                                (void)_t2437;
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
                                                                                                                                                                TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                ;
                                                                                                                                                                return _t2437;
                                                                                                                                                            } else {
                                                                                                                                                                Bool _t2494; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwNamespace()); _t2494 = *_hp; free(_hp); }
                                                                                                                                                                (void)_t2494;
                                                                                                                                                                if (_t2494) {
                                                                                                                                                                    Str *_t2438 = Str_lit("namespace", 9ULL);
                                                                                                                                                                    (void)_t2438;
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
                                                                                                                                                                    TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                    ;
                                                                                                                                                                    return _t2438;
                                                                                                                                                                } else {
                                                                                                                                                                    Bool _t2493; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwFunc()); _t2493 = *_hp; free(_hp); }
                                                                                                                                                                    (void)_t2493;
                                                                                                                                                                    if (_t2493) {
                                                                                                                                                                        Str *_t2439 = Str_lit("func", 4ULL);
                                                                                                                                                                        (void)_t2439;
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
                                                                                                                                                                        TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                        ;
                                                                                                                                                                        return _t2439;
                                                                                                                                                                    } else {
                                                                                                                                                                        Bool _t2492; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwProc()); _t2492 = *_hp; free(_hp); }
                                                                                                                                                                        (void)_t2492;
                                                                                                                                                                        if (_t2492) {
                                                                                                                                                                            Str *_t2440 = Str_lit("proc", 4ULL);
                                                                                                                                                                            (void)_t2440;
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
                                                                                                                                                                            TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                            ;
                                                                                                                                                                            return _t2440;
                                                                                                                                                                        } else {
                                                                                                                                                                            Bool _t2491; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwTest()); _t2491 = *_hp; free(_hp); }
                                                                                                                                                                            (void)_t2491;
                                                                                                                                                                            if (_t2491) {
                                                                                                                                                                                Str *_t2441 = Str_lit("test", 4ULL);
                                                                                                                                                                                (void)_t2441;
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
                                                                                                                                                                                TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                ;
                                                                                                                                                                                return _t2441;
                                                                                                                                                                            } else {
                                                                                                                                                                                Bool _t2490; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwMacro()); _t2490 = *_hp; free(_hp); }
                                                                                                                                                                                (void)_t2490;
                                                                                                                                                                                if (_t2490) {
                                                                                                                                                                                    Str *_t2442 = Str_lit("macro", 5ULL);
                                                                                                                                                                                    (void)_t2442;
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
                                                                                                                                                                                    TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                    ;
                                                                                                                                                                                    return _t2442;
                                                                                                                                                                                } else {
                                                                                                                                                                                    Bool _t2489; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwExtFunc()); _t2489 = *_hp; free(_hp); }
                                                                                                                                                                                    (void)_t2489;
                                                                                                                                                                                    if (_t2489) {
                                                                                                                                                                                        Str *_t2443 = Str_lit("ext_func", 8ULL);
                                                                                                                                                                                        (void)_t2443;
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
                                                                                                                                                                                        TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                        ;
                                                                                                                                                                                        return _t2443;
                                                                                                                                                                                    } else {
                                                                                                                                                                                        Bool _t2488; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwExtProc()); _t2488 = *_hp; free(_hp); }
                                                                                                                                                                                        (void)_t2488;
                                                                                                                                                                                        if (_t2488) {
                                                                                                                                                                                            Str *_t2444 = Str_lit("ext_proc", 8ULL);
                                                                                                                                                                                            (void)_t2444;
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
                                                                                                                                                                                            TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                            ;
                                                                                                                                                                                            return _t2444;
                                                                                                                                                                                        } else {
                                                                                                                                                                                            Bool _t2487; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwReturns()); _t2487 = *_hp; free(_hp); }
                                                                                                                                                                                            (void)_t2487;
                                                                                                                                                                                            if (_t2487) {
                                                                                                                                                                                                Str *_t2445 = Str_lit("returns", 7ULL);
                                                                                                                                                                                                (void)_t2445;
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
                                                                                                                                                                                                TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                                ;
                                                                                                                                                                                                return _t2445;
                                                                                                                                                                                            } else {
                                                                                                                                                                                                Bool _t2486; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwThrows()); _t2486 = *_hp; free(_hp); }
                                                                                                                                                                                                (void)_t2486;
                                                                                                                                                                                                if (_t2486) {
                                                                                                                                                                                                    Str *_t2446 = Str_lit("throws", 6ULL);
                                                                                                                                                                                                    (void)_t2446;
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
                                                                                                                                                                                                    TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    return _t2446;
                                                                                                                                                                                                } else {
                                                                                                                                                                                                    Bool _t2485; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwIf()); _t2485 = *_hp; free(_hp); }
                                                                                                                                                                                                    (void)_t2485;
                                                                                                                                                                                                    if (_t2485) {
                                                                                                                                                                                                        Str *_t2447 = Str_lit("if", 2ULL);
                                                                                                                                                                                                        (void)_t2447;
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
                                                                                                                                                                                                        TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        return _t2447;
                                                                                                                                                                                                    } else {
                                                                                                                                                                                                        Bool _t2484; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwElse()); _t2484 = *_hp; free(_hp); }
                                                                                                                                                                                                        (void)_t2484;
                                                                                                                                                                                                        if (_t2484) {
                                                                                                                                                                                                            Str *_t2448 = Str_lit("else", 4ULL);
                                                                                                                                                                                                            (void)_t2448;
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
                                                                                                                                                                                                            TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            return _t2448;
                                                                                                                                                                                                        } else {
                                                                                                                                                                                                            Bool _t2483; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwWhile()); _t2483 = *_hp; free(_hp); }
                                                                                                                                                                                                            (void)_t2483;
                                                                                                                                                                                                            if (_t2483) {
                                                                                                                                                                                                                Str *_t2449 = Str_lit("while", 5ULL);
                                                                                                                                                                                                                (void)_t2449;
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
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                return _t2449;
                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                Bool _t2482; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwFor()); _t2482 = *_hp; free(_hp); }
                                                                                                                                                                                                                (void)_t2482;
                                                                                                                                                                                                                if (_t2482) {
                                                                                                                                                                                                                    Str *_t2450 = Str_lit("for", 3ULL);
                                                                                                                                                                                                                    (void)_t2450;
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
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    return _t2450;
                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                    Bool _t2481; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwIn()); _t2481 = *_hp; free(_hp); }
                                                                                                                                                                                                                    (void)_t2481;
                                                                                                                                                                                                                    if (_t2481) {
                                                                                                                                                                                                                        Str *_t2451 = Str_lit("in", 2ULL);
                                                                                                                                                                                                                        (void)_t2451;
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
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        return _t2451;
                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                        Bool _t2480; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwSwitch()); _t2480 = *_hp; free(_hp); }
                                                                                                                                                                                                                        (void)_t2480;
                                                                                                                                                                                                                        if (_t2480) {
                                                                                                                                                                                                                            Str *_t2452 = Str_lit("switch", 6ULL);
                                                                                                                                                                                                                            (void)_t2452;
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
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            return _t2452;
                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                            Bool _t2479; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwMatch()); _t2479 = *_hp; free(_hp); }
                                                                                                                                                                                                                            (void)_t2479;
                                                                                                                                                                                                                            if (_t2479) {
                                                                                                                                                                                                                                Str *_t2453 = Str_lit("match", 5ULL);
                                                                                                                                                                                                                                (void)_t2453;
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
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                return _t2453;
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                Bool _t2478; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwCase()); _t2478 = *_hp; free(_hp); }
                                                                                                                                                                                                                                (void)_t2478;
                                                                                                                                                                                                                                if (_t2478) {
                                                                                                                                                                                                                                    Str *_t2454 = Str_lit("case", 4ULL);
                                                                                                                                                                                                                                    (void)_t2454;
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
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    return _t2454;
                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                    Bool _t2477; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwDefault()); _t2477 = *_hp; free(_hp); }
                                                                                                                                                                                                                                    (void)_t2477;
                                                                                                                                                                                                                                    if (_t2477) {
                                                                                                                                                                                                                                        Str *_t2455 = Str_lit("default", 7ULL);
                                                                                                                                                                                                                                        (void)_t2455;
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
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        return _t2455;
                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                        Bool _t2476; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwReturn()); _t2476 = *_hp; free(_hp); }
                                                                                                                                                                                                                                        (void)_t2476;
                                                                                                                                                                                                                                        if (_t2476) {
                                                                                                                                                                                                                                            Str *_t2456 = Str_lit("return", 6ULL);
                                                                                                                                                                                                                                            (void)_t2456;
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
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            return _t2456;
                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                            Bool _t2475; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwThrow()); _t2475 = *_hp; free(_hp); }
                                                                                                                                                                                                                                            (void)_t2475;
                                                                                                                                                                                                                                            if (_t2475) {
                                                                                                                                                                                                                                                Str *_t2457 = Str_lit("throw", 5ULL);
                                                                                                                                                                                                                                                (void)_t2457;
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
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                return _t2457;
                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                Bool _t2474; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwCatch()); _t2474 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                (void)_t2474;
                                                                                                                                                                                                                                                if (_t2474) {
                                                                                                                                                                                                                                                    Str *_t2458 = Str_lit("catch", 5ULL);
                                                                                                                                                                                                                                                    (void)_t2458;
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
                                                                                                                                                                                                                                                    TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    return _t2458;
                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                    Bool _t2473; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwBreak()); _t2473 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                    (void)_t2473;
                                                                                                                                                                                                                                                    if (_t2473) {
                                                                                                                                                                                                                                                        Str *_t2459 = Str_lit("break", 5ULL);
                                                                                                                                                                                                                                                        (void)_t2459;
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
                                                                                                                                                                                                                                                        TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        return _t2459;
                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                        Bool _t2472; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwContinue()); _t2472 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                        (void)_t2472;
                                                                                                                                                                                                                                                        if (_t2472) {
                                                                                                                                                                                                                                                            Str *_t2460 = Str_lit("continue", 8ULL);
                                                                                                                                                                                                                                                            (void)_t2460;
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
                                                                                                                                                                                                                                                            TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            return _t2460;
                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                            Bool _t2471; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwDefer()); _t2471 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                            (void)_t2471;
                                                                                                                                                                                                                                                            if (_t2471) {
                                                                                                                                                                                                                                                                Str *_t2461 = Str_lit("defer", 5ULL);
                                                                                                                                                                                                                                                                (void)_t2461;
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
                                                                                                                                                                                                                                                                TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                return _t2461;
                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                Bool _t2470; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwTrue()); _t2470 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                (void)_t2470;
                                                                                                                                                                                                                                                                if (_t2470) {
                                                                                                                                                                                                                                                                    Str *_t2462 = Str_lit("true", 4ULL);
                                                                                                                                                                                                                                                                    (void)_t2462;
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
                                                                                                                                                                                                                                                                    TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t2462;
                                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                                    Bool _t2469; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwFalse()); _t2469 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                    (void)_t2469;
                                                                                                                                                                                                                                                                    if (_t2469) {
                                                                                                                                                                                                                                                                        Str *_t2463 = Str_lit("false", 5ULL);
                                                                                                                                                                                                                                                                        (void)_t2463;
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
                                                                                                                                                                                                                                                                        TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        return _t2463;
                                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                                        Bool _t2468; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_KwNull()); _t2468 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                        (void)_t2468;
                                                                                                                                                                                                                                                                        if (_t2468) {
                                                                                                                                                                                                                                                                            Str *_t2464 = Str_lit("NULL", 4ULL);
                                                                                                                                                                                                                                                                            (void)_t2464;
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
                                                                                                                                                                                                                                                                            TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            return _t2464;
                                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                                            Bool _t2467; { Bool *_hp = (Bool *)TokenType_eq(_sw2399, TokenType_Error()); _t2467 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                            (void)_t2467;
                                                                                                                                                                                                                                                                            if (_t2467) {
                                                                                                                                                                                                                                                                                Str *_t2465 = Str_lit("error", 5ULL);
                                                                                                                                                                                                                                                                                (void)_t2465;
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
                                                                                                                                                                                                                                                                                TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t2465;
                                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                                Str *_t2466 = Str_lit("?", 1ULL);
                                                                                                                                                                                                                                                                                (void)_t2466;
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
                                                                                                                                                                                                                                                                                TokenType_delete(_sw2399, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t2466;
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
        TokenType_delete(_sw2399, &(Bool){1});
        ;
    }
}

TokenType * lookup_keyword(Str * word) {
    (void)word;
    {
        Str *_sw2533 = Str_clone(word);
        (void)_sw2533;
        Str *_t2602 = Str_lit("mode", 4ULL);
        (void)_t2602;
        Bool _t2603; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2602); _t2603 = *_hp; free(_hp); }
        (void)_t2603;
        Str_delete(_t2602, &(Bool){1});
        if (_t2603) {
            Str_delete(_sw2533, &(Bool){1});
            ;
            return TokenType_KwMode();
        } else {
            Str *_t2600 = Str_lit("mut", 3ULL);
            (void)_t2600;
            Bool _t2601; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2600); _t2601 = *_hp; free(_hp); }
            (void)_t2601;
            Str_delete(_t2600, &(Bool){1});
            if (_t2601) {
                ;
                Str_delete(_sw2533, &(Bool){1});
                ;
                return TokenType_KwMut();
            } else {
                Str *_t2598 = Str_lit("own", 3ULL);
                (void)_t2598;
                Bool _t2599; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2598); _t2599 = *_hp; free(_hp); }
                (void)_t2599;
                Str_delete(_t2598, &(Bool){1});
                if (_t2599) {
                    ;
                    ;
                    Str_delete(_sw2533, &(Bool){1});
                    ;
                    return TokenType_KwOwn();
                } else {
                    Str *_t2596 = Str_lit("ref", 3ULL);
                    (void)_t2596;
                    Bool _t2597; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2596); _t2597 = *_hp; free(_hp); }
                    (void)_t2597;
                    Str_delete(_t2596, &(Bool){1});
                    if (_t2597) {
                        ;
                        ;
                        ;
                        Str_delete(_sw2533, &(Bool){1});
                        ;
                        return TokenType_KwRef();
                    } else {
                        Str *_t2594 = Str_lit("shallow", 7ULL);
                        (void)_t2594;
                        Bool _t2595; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2594); _t2595 = *_hp; free(_hp); }
                        (void)_t2595;
                        Str_delete(_t2594, &(Bool){1});
                        if (_t2595) {
                            ;
                            ;
                            ;
                            ;
                            Str_delete(_sw2533, &(Bool){1});
                            ;
                            return TokenType_KwShallow();
                        } else {
                            Str *_t2592 = Str_lit("struct", 6ULL);
                            (void)_t2592;
                            Bool _t2593; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2592); _t2593 = *_hp; free(_hp); }
                            (void)_t2593;
                            Str_delete(_t2592, &(Bool){1});
                            if (_t2593) {
                                ;
                                ;
                                ;
                                ;
                                ;
                                Str_delete(_sw2533, &(Bool){1});
                                ;
                                return TokenType_KwStruct();
                            } else {
                                Str *_t2590 = Str_lit("ext_struct", 10ULL);
                                (void)_t2590;
                                Bool _t2591; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2590); _t2591 = *_hp; free(_hp); }
                                (void)_t2591;
                                Str_delete(_t2590, &(Bool){1});
                                if (_t2591) {
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    Str_delete(_sw2533, &(Bool){1});
                                    ;
                                    return TokenType_KwExtStruct();
                                } else {
                                    Str *_t2588 = Str_lit("enum", 4ULL);
                                    (void)_t2588;
                                    Bool _t2589; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2588); _t2589 = *_hp; free(_hp); }
                                    (void)_t2589;
                                    Str_delete(_t2588, &(Bool){1});
                                    if (_t2589) {
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        Str_delete(_sw2533, &(Bool){1});
                                        ;
                                        return TokenType_KwEnum();
                                    } else {
                                        Str *_t2586 = Str_lit("namespace", 9ULL);
                                        (void)_t2586;
                                        Bool _t2587; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2586); _t2587 = *_hp; free(_hp); }
                                        (void)_t2587;
                                        Str_delete(_t2586, &(Bool){1});
                                        if (_t2587) {
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            Str_delete(_sw2533, &(Bool){1});
                                            ;
                                            return TokenType_KwNamespace();
                                        } else {
                                            Str *_t2584 = Str_lit("func", 4ULL);
                                            (void)_t2584;
                                            Bool _t2585; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2584); _t2585 = *_hp; free(_hp); }
                                            (void)_t2585;
                                            Str_delete(_t2584, &(Bool){1});
                                            if (_t2585) {
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                Str_delete(_sw2533, &(Bool){1});
                                                ;
                                                return TokenType_KwFunc();
                                            } else {
                                                Str *_t2582 = Str_lit("proc", 4ULL);
                                                (void)_t2582;
                                                Bool _t2583; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2582); _t2583 = *_hp; free(_hp); }
                                                (void)_t2583;
                                                Str_delete(_t2582, &(Bool){1});
                                                if (_t2583) {
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
                                                    Str_delete(_sw2533, &(Bool){1});
                                                    ;
                                                    return TokenType_KwProc();
                                                } else {
                                                    Str *_t2580 = Str_lit("test", 4ULL);
                                                    (void)_t2580;
                                                    Bool _t2581; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2580); _t2581 = *_hp; free(_hp); }
                                                    (void)_t2581;
                                                    Str_delete(_t2580, &(Bool){1});
                                                    if (_t2581) {
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
                                                        Str_delete(_sw2533, &(Bool){1});
                                                        ;
                                                        return TokenType_KwTest();
                                                    } else {
                                                        Str *_t2578 = Str_lit("macro", 5ULL);
                                                        (void)_t2578;
                                                        Bool _t2579; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2578); _t2579 = *_hp; free(_hp); }
                                                        (void)_t2579;
                                                        Str_delete(_t2578, &(Bool){1});
                                                        if (_t2579) {
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
                                                            Str_delete(_sw2533, &(Bool){1});
                                                            ;
                                                            return TokenType_KwMacro();
                                                        } else {
                                                            Str *_t2576 = Str_lit("ext_func", 8ULL);
                                                            (void)_t2576;
                                                            Bool _t2577; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2576); _t2577 = *_hp; free(_hp); }
                                                            (void)_t2577;
                                                            Str_delete(_t2576, &(Bool){1});
                                                            if (_t2577) {
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
                                                                Str_delete(_sw2533, &(Bool){1});
                                                                ;
                                                                return TokenType_KwExtFunc();
                                                            } else {
                                                                Str *_t2574 = Str_lit("ext_proc", 8ULL);
                                                                (void)_t2574;
                                                                Bool _t2575; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2574); _t2575 = *_hp; free(_hp); }
                                                                (void)_t2575;
                                                                Str_delete(_t2574, &(Bool){1});
                                                                if (_t2575) {
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
                                                                    Str_delete(_sw2533, &(Bool){1});
                                                                    ;
                                                                    return TokenType_KwExtProc();
                                                                } else {
                                                                    Str *_t2572 = Str_lit("returns", 7ULL);
                                                                    (void)_t2572;
                                                                    Bool _t2573; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2572); _t2573 = *_hp; free(_hp); }
                                                                    (void)_t2573;
                                                                    Str_delete(_t2572, &(Bool){1});
                                                                    if (_t2573) {
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
                                                                        Str_delete(_sw2533, &(Bool){1});
                                                                        ;
                                                                        return TokenType_KwReturns();
                                                                    } else {
                                                                        Str *_t2570 = Str_lit("throws", 6ULL);
                                                                        (void)_t2570;
                                                                        Bool _t2571; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2570); _t2571 = *_hp; free(_hp); }
                                                                        (void)_t2571;
                                                                        Str_delete(_t2570, &(Bool){1});
                                                                        if (_t2571) {
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
                                                                            Str_delete(_sw2533, &(Bool){1});
                                                                            ;
                                                                            return TokenType_KwThrows();
                                                                        } else {
                                                                            Str *_t2568 = Str_lit("if", 2ULL);
                                                                            (void)_t2568;
                                                                            Bool _t2569; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2568); _t2569 = *_hp; free(_hp); }
                                                                            (void)_t2569;
                                                                            Str_delete(_t2568, &(Bool){1});
                                                                            if (_t2569) {
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
                                                                                Str_delete(_sw2533, &(Bool){1});
                                                                                ;
                                                                                return TokenType_KwIf();
                                                                            } else {
                                                                                Str *_t2566 = Str_lit("else", 4ULL);
                                                                                (void)_t2566;
                                                                                Bool _t2567; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2566); _t2567 = *_hp; free(_hp); }
                                                                                (void)_t2567;
                                                                                Str_delete(_t2566, &(Bool){1});
                                                                                if (_t2567) {
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
                                                                                    Str_delete(_sw2533, &(Bool){1});
                                                                                    ;
                                                                                    return TokenType_KwElse();
                                                                                } else {
                                                                                    Str *_t2564 = Str_lit("while", 5ULL);
                                                                                    (void)_t2564;
                                                                                    Bool _t2565; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2564); _t2565 = *_hp; free(_hp); }
                                                                                    (void)_t2565;
                                                                                    Str_delete(_t2564, &(Bool){1});
                                                                                    if (_t2565) {
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
                                                                                        Str_delete(_sw2533, &(Bool){1});
                                                                                        ;
                                                                                        return TokenType_KwWhile();
                                                                                    } else {
                                                                                        Str *_t2562 = Str_lit("for", 3ULL);
                                                                                        (void)_t2562;
                                                                                        Bool _t2563; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2562); _t2563 = *_hp; free(_hp); }
                                                                                        (void)_t2563;
                                                                                        Str_delete(_t2562, &(Bool){1});
                                                                                        if (_t2563) {
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
                                                                                            Str_delete(_sw2533, &(Bool){1});
                                                                                            ;
                                                                                            return TokenType_KwFor();
                                                                                        } else {
                                                                                            Str *_t2560 = Str_lit("in", 2ULL);
                                                                                            (void)_t2560;
                                                                                            Bool _t2561; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2560); _t2561 = *_hp; free(_hp); }
                                                                                            (void)_t2561;
                                                                                            Str_delete(_t2560, &(Bool){1});
                                                                                            if (_t2561) {
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
                                                                                                Str_delete(_sw2533, &(Bool){1});
                                                                                                ;
                                                                                                return TokenType_KwIn();
                                                                                            } else {
                                                                                                Str *_t2558 = Str_lit("switch", 6ULL);
                                                                                                (void)_t2558;
                                                                                                Bool _t2559; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2558); _t2559 = *_hp; free(_hp); }
                                                                                                (void)_t2559;
                                                                                                Str_delete(_t2558, &(Bool){1});
                                                                                                if (_t2559) {
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
                                                                                                    Str_delete(_sw2533, &(Bool){1});
                                                                                                    ;
                                                                                                    return TokenType_KwSwitch();
                                                                                                } else {
                                                                                                    Str *_t2556 = Str_lit("match", 5ULL);
                                                                                                    (void)_t2556;
                                                                                                    Bool _t2557; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2556); _t2557 = *_hp; free(_hp); }
                                                                                                    (void)_t2557;
                                                                                                    Str_delete(_t2556, &(Bool){1});
                                                                                                    if (_t2557) {
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
                                                                                                        Str_delete(_sw2533, &(Bool){1});
                                                                                                        ;
                                                                                                        return TokenType_KwMatch();
                                                                                                    } else {
                                                                                                        Str *_t2554 = Str_lit("case", 4ULL);
                                                                                                        (void)_t2554;
                                                                                                        Bool _t2555; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2554); _t2555 = *_hp; free(_hp); }
                                                                                                        (void)_t2555;
                                                                                                        Str_delete(_t2554, &(Bool){1});
                                                                                                        if (_t2555) {
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
                                                                                                            Str_delete(_sw2533, &(Bool){1});
                                                                                                            ;
                                                                                                            return TokenType_KwCase();
                                                                                                        } else {
                                                                                                            Str *_t2552 = Str_lit("default", 7ULL);
                                                                                                            (void)_t2552;
                                                                                                            Bool _t2553; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2552); _t2553 = *_hp; free(_hp); }
                                                                                                            (void)_t2553;
                                                                                                            Str_delete(_t2552, &(Bool){1});
                                                                                                            if (_t2553) {
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
                                                                                                                ;
                                                                                                                Str_delete(_sw2533, &(Bool){1});
                                                                                                                ;
                                                                                                                return TokenType_KwDefault();
                                                                                                            } else {
                                                                                                                Str *_t2550 = Str_lit("return", 6ULL);
                                                                                                                (void)_t2550;
                                                                                                                Bool _t2551; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2550); _t2551 = *_hp; free(_hp); }
                                                                                                                (void)_t2551;
                                                                                                                Str_delete(_t2550, &(Bool){1});
                                                                                                                if (_t2551) {
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
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    Str_delete(_sw2533, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return TokenType_KwReturn();
                                                                                                                } else {
                                                                                                                    Str *_t2548 = Str_lit("throw", 5ULL);
                                                                                                                    (void)_t2548;
                                                                                                                    Bool _t2549; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2548); _t2549 = *_hp; free(_hp); }
                                                                                                                    (void)_t2549;
                                                                                                                    Str_delete(_t2548, &(Bool){1});
                                                                                                                    if (_t2549) {
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
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        Str_delete(_sw2533, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return TokenType_KwThrow();
                                                                                                                    } else {
                                                                                                                        Str *_t2546 = Str_lit("catch", 5ULL);
                                                                                                                        (void)_t2546;
                                                                                                                        Bool _t2547; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2546); _t2547 = *_hp; free(_hp); }
                                                                                                                        (void)_t2547;
                                                                                                                        Str_delete(_t2546, &(Bool){1});
                                                                                                                        if (_t2547) {
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
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            Str_delete(_sw2533, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return TokenType_KwCatch();
                                                                                                                        } else {
                                                                                                                            Str *_t2544 = Str_lit("break", 5ULL);
                                                                                                                            (void)_t2544;
                                                                                                                            Bool _t2545; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2544); _t2545 = *_hp; free(_hp); }
                                                                                                                            (void)_t2545;
                                                                                                                            Str_delete(_t2544, &(Bool){1});
                                                                                                                            if (_t2545) {
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
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                Str_delete(_sw2533, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return TokenType_KwBreak();
                                                                                                                            } else {
                                                                                                                                Str *_t2542 = Str_lit("continue", 8ULL);
                                                                                                                                (void)_t2542;
                                                                                                                                Bool _t2543; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2542); _t2543 = *_hp; free(_hp); }
                                                                                                                                (void)_t2543;
                                                                                                                                Str_delete(_t2542, &(Bool){1});
                                                                                                                                if (_t2543) {
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
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    Str_delete(_sw2533, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return TokenType_KwContinue();
                                                                                                                                } else {
                                                                                                                                    Str *_t2540 = Str_lit("defer", 5ULL);
                                                                                                                                    (void)_t2540;
                                                                                                                                    Bool _t2541; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2540); _t2541 = *_hp; free(_hp); }
                                                                                                                                    (void)_t2541;
                                                                                                                                    Str_delete(_t2540, &(Bool){1});
                                                                                                                                    if (_t2541) {
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
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        Str_delete(_sw2533, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return TokenType_KwDefer();
                                                                                                                                    } else {
                                                                                                                                        Str *_t2538 = Str_lit("true", 4ULL);
                                                                                                                                        (void)_t2538;
                                                                                                                                        Bool _t2539; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2538); _t2539 = *_hp; free(_hp); }
                                                                                                                                        (void)_t2539;
                                                                                                                                        Str_delete(_t2538, &(Bool){1});
                                                                                                                                        if (_t2539) {
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
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            Str_delete(_sw2533, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return TokenType_KwTrue();
                                                                                                                                        } else {
                                                                                                                                            Str *_t2536 = Str_lit("false", 5ULL);
                                                                                                                                            (void)_t2536;
                                                                                                                                            Bool _t2537; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2536); _t2537 = *_hp; free(_hp); }
                                                                                                                                            (void)_t2537;
                                                                                                                                            Str_delete(_t2536, &(Bool){1});
                                                                                                                                            if (_t2537) {
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
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                Str_delete(_sw2533, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return TokenType_KwFalse();
                                                                                                                                            } else {
                                                                                                                                                Str *_t2534 = Str_lit("NULL", 4ULL);
                                                                                                                                                (void)_t2534;
                                                                                                                                                Bool _t2535; { Bool *_hp = (Bool *)Str_eq(_sw2533, _t2534); _t2535 = *_hp; free(_hp); }
                                                                                                                                                (void)_t2535;
                                                                                                                                                Str_delete(_t2534, &(Bool){1});
                                                                                                                                                if (_t2535) {
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
                                                                                                                                                    Str_delete(_sw2533, &(Bool){1});
                                                                                                                                                    ;
                                                                                                                                                    return TokenType_KwNull();
                                                                                                                                                } else {
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
                                                                                                                                                    Str_delete(_sw2533, &(Bool){1});
                                                                                                                                                    ;
                                                                                                                                                    return TokenType_Ident();
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
        Str_delete(_sw2533, &(Bool){1});
        ;
    }
}

Vec * tokenize(Str * src, Str * path) {
    (void)src;
    (void)path;
    Str *_t2943 = Str_lit("Token", 5ULL);
    (void)_t2943;
    U64 _t2944; { U64 *_hp = (U64 *)Token_size(); _t2944 = *_hp; free(_hp); }
    (void)_t2944;
    Vec *tokens = Vec_new(_t2943, &(U64){_t2944});
    (void)tokens;
    Str_delete(_t2943, &(Bool){1});
    ;
    U64 *pos = malloc(sizeof(U64));
    *pos = 0;
    (void)pos;
    U32 line = 1;
    (void)line;
    U64 line_start = 0;
    (void)line_start;
    U64 src_len; { U64 *_hp = (U64 *)Str_len(src); src_len = *_hp; free(_hp); }
    (void)src_len;
    while (1) {
        Bool _wcond2604; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2604 = *_hp; free(_hp); }
        (void)_wcond2604;
        if (_wcond2604) {
        } else {
            ;
            break;
        }
        ;
        U8 *c = Str_byte_at(src, pos);
        (void)c;
        U8 _t2888 = 32;
        (void)_t2888;
        U8 _t2889 = 9;
        (void)_t2889;
        Bool _t2890 = U8_eq(DEREF(c), _t2888);
        (void)_t2890;
        ;
        Bool _t2891 = U8_eq(DEREF(c), _t2889);
        (void)_t2891;
        ;
        U8 _t2892 = 13;
        (void)_t2892;
        Bool _t2893 = Bool_or(_t2890, _t2891);
        (void)_t2893;
        ;
        ;
        Bool _t2894 = U8_eq(DEREF(c), _t2892);
        (void)_t2894;
        ;
        U8 _t2895 = 59;
        (void)_t2895;
        Bool _t2896 = Bool_or(_t2893, _t2894);
        (void)_t2896;
        ;
        ;
        Bool _t2897 = U8_eq(DEREF(c), _t2895);
        (void)_t2897;
        ;
        Bool _t2898 = Bool_or(_t2896, _t2897);
        (void)_t2898;
        ;
        ;
        if (_t2898) {
            U64_inc(pos);
            ;
            continue;
        }
        ;
        U8 _t2899 = 10;
        (void)_t2899;
        Bool _t2900 = U8_eq(DEREF(c), _t2899);
        (void)_t2900;
        ;
        if (_t2900) {
            U64_inc(pos);
            U32 _t2605 = 1;
            (void)_t2605;
            U32 _t2606 = U32_add(line, _t2605);
            (void)_t2606;
            ;
            line = _t2606;
            ;
            U64 _t2607 = U64_clone(pos);
            (void)_t2607;
            line_start = _t2607;
            ;
            ;
            continue;
        }
        ;
        U64 _t2901 = U64_sub(DEREF(pos), line_start);
        (void)_t2901;
        U64 _t2902 = 1;
        (void)_t2902;
        U64 _t2903 = U64_add(_t2901, _t2902);
        (void)_t2903;
        ;
        ;
        I64 _t2904 = U64_to_i64(_t2903);
        (void)_t2904;
        ;
        U32 col = I64_to_u32(_t2904);
        (void)col;
        ;
        U64 start = U64_clone(pos);
        (void)start;
        U8 _t2905 = 35;
        (void)_t2905;
        Bool _t2906 = U8_eq(DEREF(c), _t2905);
        (void)_t2906;
        ;
        if (_t2906) {
            while (1) {
                Bool _wcond2608; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2608 = *_hp; free(_hp); }
                (void)_wcond2608;
                if (_wcond2608) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2609 = Str_byte_at(src, pos);
                (void)_t2609;
                U8 _t2610 = 10;
                (void)_t2610;
                Bool _t2611 = U8_eq(DEREF(_t2609), _t2610);
                (void)_t2611;
                ;
                if (_t2611) {
                    ;
                    break;
                }
                ;
                U64_inc(pos);
            }
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t2907 = 47;
        (void)_t2907;
        U64 _t2908 = 1;
        (void)_t2908;
        U64 _t2909 = U64_add(DEREF(pos), _t2908);
        (void)_t2909;
        ;
        Bool _t2910 = U8_eq(DEREF(c), _t2907);
        (void)_t2910;
        ;
        Bool _t2911; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2909}, &(U64){src_len}); _t2911 = *_hp; free(_hp); }
        (void)_t2911;
        ;
        Bool _t2912 = Bool_and(_t2910, _t2911);
        (void)_t2912;
        ;
        ;
        if (_t2912) {
            U64 _t2668 = 1;
            (void)_t2668;
            U64 *_t2669 = malloc(sizeof(U64)); *_t2669 = U64_add(DEREF(pos), _t2668);
            (void)_t2669;
            ;
            U8 *c2 = Str_byte_at(src, _t2669);
            (void)c2;
            U8 _t2670 = 47;
            (void)_t2670;
            Bool _t2671 = U8_eq(DEREF(c2), _t2670);
            (void)_t2671;
            ;
            if (_t2671) {
                while (1) {
                    Bool _wcond2612; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2612 = *_hp; free(_hp); }
                    (void)_wcond2612;
                    if (_wcond2612) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U8 *_t2613 = Str_byte_at(src, pos);
                    (void)_t2613;
                    U8 _t2614 = 10;
                    (void)_t2614;
                    Bool _t2615 = U8_eq(DEREF(_t2613), _t2614);
                    (void)_t2615;
                    ;
                    if (_t2615) {
                        ;
                        break;
                    }
                    ;
                    U64_inc(pos);
                }
                U64_delete(_t2669, &(Bool){1});
                ;
                ;
                ;
                ;
                continue;
            }
            ;
            U8 _t2672 = 42;
            (void)_t2672;
            Bool _t2673 = U8_eq(DEREF(c2), _t2672);
            (void)_t2673;
            U64_delete(_t2669, &(Bool){1});
            ;
            if (_t2673) {
                U64 _t2664 = 2;
                (void)_t2664;
                U64 _t2665 = U64_add(DEREF(pos), _t2664);
                (void)_t2665;
                ;
                *pos = _t2665;
                ;
                I64 depth = 1;
                (void)depth;
                while (1) {
                    Bool _wcond2616; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2616 = *_hp; free(_hp); }
                    (void)_wcond2616;
                    if (_wcond2616) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    I64 _t2641 = 0;
                    (void)_t2641;
                    Bool _t2642; { Bool *_hp = (Bool *)I64_lte(&(I64){depth}, &(I64){_t2641}); _t2642 = *_hp; free(_hp); }
                    (void)_t2642;
                    ;
                    if (_t2642) {
                        ;
                        break;
                    }
                    ;
                    U64 _t2643 = 1;
                    (void)_t2643;
                    U64 _t2644 = U64_add(DEREF(pos), _t2643);
                    (void)_t2644;
                    ;
                    Bool _t2645; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2644}, &(U64){src_len}); _t2645 = *_hp; free(_hp); }
                    (void)_t2645;
                    ;
                    if (_t2645) {
                        U8 *b1 = Str_byte_at(src, pos);
                        (void)b1;
                        U64 _t2625 = 1;
                        (void)_t2625;
                        U64 *_t2626 = malloc(sizeof(U64)); *_t2626 = U64_add(DEREF(pos), _t2625);
                        (void)_t2626;
                        ;
                        U8 *b2 = Str_byte_at(src, _t2626);
                        (void)b2;
                        U8 _t2627 = 47;
                        (void)_t2627;
                        U8 _t2628 = 42;
                        (void)_t2628;
                        Bool _t2629 = U8_eq(DEREF(b1), _t2627);
                        (void)_t2629;
                        ;
                        Bool _t2630 = U8_eq(DEREF(b2), _t2628);
                        (void)_t2630;
                        ;
                        Bool _t2631 = Bool_and(_t2629, _t2630);
                        (void)_t2631;
                        ;
                        ;
                        if (_t2631) {
                            I64 _t2617 = 1;
                            (void)_t2617;
                            I64 _t2618 = I64_add(depth, _t2617);
                            (void)_t2618;
                            ;
                            depth = _t2618;
                            ;
                            U64 _t2619 = 2;
                            (void)_t2619;
                            U64 _t2620 = U64_add(DEREF(pos), _t2619);
                            (void)_t2620;
                            ;
                            *pos = _t2620;
                            ;
                            U64_delete(_t2626, &(Bool){1});
                            ;
                            ;
                            continue;
                        }
                        ;
                        U8 _t2632 = 42;
                        (void)_t2632;
                        U8 _t2633 = 47;
                        (void)_t2633;
                        Bool _t2634 = U8_eq(DEREF(b1), _t2632);
                        (void)_t2634;
                        ;
                        Bool _t2635 = U8_eq(DEREF(b2), _t2633);
                        (void)_t2635;
                        U64_delete(_t2626, &(Bool){1});
                        ;
                        Bool _t2636 = Bool_and(_t2634, _t2635);
                        (void)_t2636;
                        ;
                        ;
                        if (_t2636) {
                            I64 _t2621 = 1;
                            (void)_t2621;
                            I64 _t2622 = I64_sub(depth, _t2621);
                            (void)_t2622;
                            ;
                            depth = _t2622;
                            ;
                            U64 _t2623 = 2;
                            (void)_t2623;
                            U64 _t2624 = U64_add(DEREF(pos), _t2623);
                            (void)_t2624;
                            ;
                            *pos = _t2624;
                            ;
                            ;
                            ;
                            continue;
                        }
                        ;
                    }
                    ;
                    U8 *_t2646 = Str_byte_at(src, pos);
                    (void)_t2646;
                    U8 _t2647 = 10;
                    (void)_t2647;
                    Bool _t2648 = U8_eq(DEREF(_t2646), _t2647);
                    (void)_t2648;
                    ;
                    if (_t2648) {
                        U32 _t2637 = 1;
                        (void)_t2637;
                        U32 _t2638 = U32_add(line, _t2637);
                        (void)_t2638;
                        ;
                        line = _t2638;
                        ;
                        U64 _t2639 = 1;
                        (void)_t2639;
                        U64 _t2640 = U64_add(DEREF(pos), _t2639);
                        (void)_t2640;
                        ;
                        line_start = _t2640;
                        ;
                    }
                    ;
                    U64_inc(pos);
                }
                I64 _t2666 = 0;
                (void)_t2666;
                Bool _t2667; { Bool *_hp = (Bool *)I64_gt(&(I64){depth}, &(I64){_t2666}); _t2667 = *_hp; free(_hp); }
                (void)_t2667;
                ;
                ;
                if (_t2667) {
                    Str *_t2649 = Str_lit("Str", 3ULL);
                    (void)_t2649;
                    U64 _t2650; { U64 *_hp = (U64 *)Str_size(); _t2650 = *_hp; free(_hp); }
                    (void)_t2650;
                    U64 _t2651 = 6;
                    (void)_t2651;
                    Array *_va50 = Array_new(_t2649, &(U64){_t2650}, &(U64){_t2651});
                    (void)_va50;
                    Str_delete(_t2649, &(Bool){1});
                    ;
                    ;
                    U64 _t2652 = 0;
                    (void)_t2652;
                    Str *_t2653 = Str_clone(path);
                    (void)_t2653;
                    Array_set(_va50, &(U64){_t2652}, _t2653);
                    ;
                    U64 _t2654 = 1;
                    (void)_t2654;
                    Str *_t2655 = Str_lit(":", 1ULL);
                    (void)_t2655;
                    Array_set(_va50, &(U64){_t2654}, _t2655);
                    ;
                    U64 _t2656 = 2;
                    (void)_t2656;
                    Str *_t2657 = U32_to_str(&(U32){line});
                    (void)_t2657;
                    Array_set(_va50, &(U64){_t2656}, _t2657);
                    ;
                    U64 _t2658 = 3;
                    (void)_t2658;
                    Str *_t2659 = Str_lit(":", 1ULL);
                    (void)_t2659;
                    Array_set(_va50, &(U64){_t2658}, _t2659);
                    ;
                    U64 _t2660 = 4;
                    (void)_t2660;
                    Str *_t2661 = U32_to_str(&(U32){col});
                    (void)_t2661;
                    Array_set(_va50, &(U64){_t2660}, _t2661);
                    ;
                    U64 _t2662 = 5;
                    (void)_t2662;
                    Str *_t2663 = Str_lit(": error: unterminated comment", 29ULL);
                    (void)_t2663;
                    Array_set(_va50, &(U64){_t2662}, _t2663);
                    ;
                    println(_va50);
                }
                ;
                ;
                ;
                ;
                ;
                continue;
            }
            ;
        }
        ;
        Bool _t2913; { Bool *_hp = (Bool *)is_digit(c); _t2913 = *_hp; free(_hp); }
        (void)_t2913;
        if (_t2913) {
            while (1) {
                Bool _wcond2674; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2674 = *_hp; free(_hp); }
                (void)_wcond2674;
                if (_wcond2674) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2675 = Str_byte_at(src, pos);
                (void)_t2675;
                Bool _t2676; { Bool *_hp = (Bool *)is_digit(_t2675); _t2676 = *_hp; free(_hp); }
                (void)_t2676;
                Bool _t2677 = Bool_not(_t2676);
                (void)_t2677;
                ;
                if (_t2677) {
                    ;
                    break;
                }
                ;
                U64_inc(pos);
            }
            U64 _t2690 = 1;
            (void)_t2690;
            U64 _t2691 = U64_add(DEREF(pos), _t2690);
            (void)_t2691;
            ;
            Bool _t2692; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2691}, &(U64){src_len}); _t2692 = *_hp; free(_hp); }
            (void)_t2692;
            ;
            if (_t2692) {
                U8 *_t2682 = Str_byte_at(src, pos);
                (void)_t2682;
                U8 _t2683 = 46;
                (void)_t2683;
                U64 _t2684 = 1;
                (void)_t2684;
                U64 *_t2685 = malloc(sizeof(U64)); *_t2685 = U64_add(DEREF(pos), _t2684);
                (void)_t2685;
                ;
                U8 *_t2686 = Str_byte_at(src, _t2685);
                (void)_t2686;
                Bool _t2687 = U8_eq(DEREF(_t2682), _t2683);
                (void)_t2687;
                ;
                Bool _t2688; { Bool *_hp = (Bool *)is_digit(_t2686); _t2688 = *_hp; free(_hp); }
                (void)_t2688;
                U64_delete(_t2685, &(Bool){1});
                Bool _t2689 = Bool_and(_t2687, _t2688);
                (void)_t2689;
                ;
                ;
                if (_t2689) {
                    U64_inc(pos);
                    while (1) {
                        Bool _wcond2678; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2678 = *_hp; free(_hp); }
                        (void)_wcond2678;
                        if (_wcond2678) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U8 *_t2679 = Str_byte_at(src, pos);
                        (void)_t2679;
                        Bool _t2680; { Bool *_hp = (Bool *)is_digit(_t2679); _t2680 = *_hp; free(_hp); }
                        (void)_t2680;
                        Bool _t2681 = Bool_not(_t2680);
                        (void)_t2681;
                        ;
                        if (_t2681) {
                            ;
                            break;
                        }
                        ;
                        U64_inc(pos);
                    }
                }
                ;
            }
            ;
            U64 _t2693 = U64_sub(DEREF(pos), start);
            (void)_t2693;
            Str *_t2694 = Str_substr(src, &(U64){start}, &(U64){_t2693});
            (void)_t2694;
            ;
            U32 _t2695 = U32_clone(&(U32){col});
            (void)_t2695;
            Token *_t2696 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(TokenType_Number()); _t2696->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(_t2694); _t2696->text = *_ca; free(_ca); }
            _t2696->line = U32_clone(&(U32){line});
            _t2696->col = _t2695;
            (void)_t2696;
            Str_delete(_t2694, &(Bool){1});
            ;
            Vec_push(tokens, _t2696);
            ;
            ;
            ;
            continue;
        }
        ;
        Bool _t2914; { Bool *_hp = (Bool *)is_alpha(c); _t2914 = *_hp; free(_hp); }
        (void)_t2914;
        if (_t2914) {
            while (1) {
                Bool _wcond2697; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2697 = *_hp; free(_hp); }
                (void)_wcond2697;
                if (_wcond2697) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2698 = Str_byte_at(src, pos);
                (void)_t2698;
                Bool _t2699; { Bool *_hp = (Bool *)is_alnum(_t2698); _t2699 = *_hp; free(_hp); }
                (void)_t2699;
                Bool _t2700 = Bool_not(_t2699);
                (void)_t2700;
                ;
                if (_t2700) {
                    ;
                    break;
                }
                ;
                U64_inc(pos);
            }
            U64 _t2701 = U64_sub(DEREF(pos), start);
            (void)_t2701;
            Str *word = Str_substr(src, &(U64){start}, &(U64){_t2701});
            (void)word;
            ;
            TokenType *type = lookup_keyword(word);
            (void)type;
            U32 _t2702 = U32_clone(&(U32){line});
            (void)_t2702;
            U32 _t2703 = U32_clone(&(U32){col});
            (void)_t2703;
            Token *_t2704 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(type); _t2704->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(word); _t2704->text = *_ca; free(_ca); }
            _t2704->line = _t2702;
            _t2704->col = _t2703;
            (void)_t2704;
            ;
            ;
            TokenType_delete(type, &(Bool){1});
            Str_delete(word, &(Bool){1});
            Vec_push(tokens, _t2704);
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t2915 = 34;
        (void)_t2915;
        Bool _t2916 = U8_eq(DEREF(c), _t2915);
        (void)_t2916;
        ;
        if (_t2916) {
            U64_inc(pos);
            while (1) {
                Bool _wcond2705; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2705 = *_hp; free(_hp); }
                (void)_wcond2705;
                if (_wcond2705) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2710 = Str_byte_at(src, pos);
                (void)_t2710;
                U8 _t2711 = 34;
                (void)_t2711;
                Bool _t2712 = U8_eq(DEREF(_t2710), _t2711);
                (void)_t2712;
                ;
                if (_t2712) {
                    ;
                    break;
                }
                ;
                U8 *_t2713 = Str_byte_at(src, pos);
                (void)_t2713;
                U8 _t2714 = 92;
                (void)_t2714;
                U64 _t2715 = 1;
                (void)_t2715;
                U64 _t2716 = U64_add(DEREF(pos), _t2715);
                (void)_t2716;
                ;
                Bool _t2717 = U8_eq(DEREF(_t2713), _t2714);
                (void)_t2717;
                ;
                Bool _t2718; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2716}, &(U64){src_len}); _t2718 = *_hp; free(_hp); }
                (void)_t2718;
                ;
                Bool _t2719 = Bool_and(_t2717, _t2718);
                (void)_t2719;
                ;
                ;
                if (_t2719) {
                    U64_inc(pos);
                }
                ;
                U8 *_t2720 = Str_byte_at(src, pos);
                (void)_t2720;
                U8 _t2721 = 10;
                (void)_t2721;
                Bool _t2722 = U8_eq(DEREF(_t2720), _t2721);
                (void)_t2722;
                ;
                if (_t2722) {
                    U32 _t2706 = 1;
                    (void)_t2706;
                    U32 _t2707 = U32_add(line, _t2706);
                    (void)_t2707;
                    ;
                    line = _t2707;
                    ;
                    U64 _t2708 = 1;
                    (void)_t2708;
                    U64 _t2709 = U64_add(DEREF(pos), _t2708);
                    (void)_t2709;
                    ;
                    line_start = _t2709;
                    ;
                }
                ;
                U64_inc(pos);
            }
            U8 *_t2750 = Str_byte_at(src, pos);
            (void)_t2750;
            U8 _t2751 = 34;
            (void)_t2751;
            Bool _t2752; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2752 = *_hp; free(_hp); }
            (void)_t2752;
            Bool _t2753 = U8_eq(DEREF(_t2750), _t2751);
            (void)_t2753;
            ;
            Bool _t2754 = Bool_and(_t2752, _t2753);
            (void)_t2754;
            ;
            ;
            if (_t2754) {
                U64_inc(pos);
                U64 _t2723 = 1;
                (void)_t2723;
                U64 _t2724 = U64_sub(DEREF(pos), start);
                (void)_t2724;
                U64 _t2725 = 2;
                (void)_t2725;
                U64 _t2726 = U64_add(start, _t2723);
                (void)_t2726;
                ;
                U64 _t2727 = U64_sub(_t2724, _t2725);
                (void)_t2727;
                ;
                ;
                Str *_t2728 = Str_substr(src, &(U64){_t2726}, &(U64){_t2727});
                (void)_t2728;
                ;
                ;
                U32 _t2729 = U32_clone(&(U32){col});
                (void)_t2729;
                Token *_t2730 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_StringTok()); _t2730->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2728); _t2730->text = *_ca; free(_ca); }
                _t2730->line = U32_clone(&(U32){line});
                _t2730->col = _t2729;
                (void)_t2730;
                Str_delete(_t2728, &(Bool){1});
                ;
                Vec_push(tokens, _t2730);
            } else {
                Str *_t2731 = Str_lit("Str", 3ULL);
                (void)_t2731;
                U64 _t2732; { U64 *_hp = (U64 *)Str_size(); _t2732 = *_hp; free(_hp); }
                (void)_t2732;
                U64 _t2733 = 6;
                (void)_t2733;
                Array *_va51 = Array_new(_t2731, &(U64){_t2732}, &(U64){_t2733});
                (void)_va51;
                Str_delete(_t2731, &(Bool){1});
                ;
                ;
                U64 _t2734 = 0;
                (void)_t2734;
                Str *_t2735 = Str_clone(path);
                (void)_t2735;
                Array_set(_va51, &(U64){_t2734}, _t2735);
                ;
                U64 _t2736 = 1;
                (void)_t2736;
                Str *_t2737 = Str_lit(":", 1ULL);
                (void)_t2737;
                Array_set(_va51, &(U64){_t2736}, _t2737);
                ;
                U64 _t2738 = 2;
                (void)_t2738;
                Str *_t2739 = U32_to_str(&(U32){line});
                (void)_t2739;
                Array_set(_va51, &(U64){_t2738}, _t2739);
                ;
                U64 _t2740 = 3;
                (void)_t2740;
                Str *_t2741 = Str_lit(":", 1ULL);
                (void)_t2741;
                Array_set(_va51, &(U64){_t2740}, _t2741);
                ;
                U64 _t2742 = 4;
                (void)_t2742;
                Str *_t2743 = U32_to_str(&(U32){col});
                (void)_t2743;
                Array_set(_va51, &(U64){_t2742}, _t2743);
                ;
                U64 _t2744 = 5;
                (void)_t2744;
                Str *_t2745 = Str_lit(": error: unterminated string", 28ULL);
                (void)_t2745;
                Array_set(_va51, &(U64){_t2744}, _t2745);
                ;
                println(_va51);
                U64 _t2746 = U64_sub(DEREF(pos), start);
                (void)_t2746;
                Str *_t2747 = Str_substr(src, &(U64){start}, &(U64){_t2746});
                (void)_t2747;
                ;
                U32 _t2748 = U32_clone(&(U32){col});
                (void)_t2748;
                Token *_t2749 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2749->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2747); _t2749->text = *_ca; free(_ca); }
                _t2749->line = U32_clone(&(U32){line});
                _t2749->col = _t2748;
                (void)_t2749;
                Str_delete(_t2747, &(Bool){1});
                ;
                Vec_push(tokens, _t2749);
            }
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t2917 = 39;
        (void)_t2917;
        Bool _t2918 = U8_eq(DEREF(c), _t2917);
        (void)_t2918;
        ;
        if (_t2918) {
            U64_inc(pos);
            U64 ch_start = U64_clone(pos);
            (void)ch_start;
            U8 *_t2778 = Str_byte_at(src, pos);
            (void)_t2778;
            U8 _t2779 = 92;
            (void)_t2779;
            U64 _t2780 = 1;
            (void)_t2780;
            U64 _t2781 = U64_add(DEREF(pos), _t2780);
            (void)_t2781;
            ;
            Bool _t2782 = U8_eq(DEREF(_t2778), _t2779);
            (void)_t2782;
            ;
            Bool _t2783; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2781}, &(U64){src_len}); _t2783 = *_hp; free(_hp); }
            (void)_t2783;
            ;
            Bool _t2784; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2784 = *_hp; free(_hp); }
            (void)_t2784;
            Bool _t2785 = Bool_and(_t2782, _t2783);
            (void)_t2785;
            ;
            ;
            Bool _t2786 = Bool_and(_t2784, _t2785);
            (void)_t2786;
            ;
            ;
            if (_t2786) {
                U64_inc(pos);
            }
            ;
            U64_inc(pos);
            U8 *_t2787 = Str_byte_at(src, pos);
            (void)_t2787;
            U8 _t2788 = 39;
            (void)_t2788;
            Bool _t2789; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2789 = *_hp; free(_hp); }
            (void)_t2789;
            Bool _t2790 = U8_eq(DEREF(_t2787), _t2788);
            (void)_t2790;
            ;
            Bool _t2791 = Bool_and(_t2789, _t2790);
            (void)_t2791;
            ;
            ;
            if (_t2791) {
                U64 _t2755 = U64_sub(DEREF(pos), ch_start);
                (void)_t2755;
                Str *_t2756 = Str_substr(src, &(U64){ch_start}, &(U64){_t2755});
                (void)_t2756;
                ;
                U32 _t2757 = U32_clone(&(U32){col});
                (void)_t2757;
                Token *_t2758 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Char()); _t2758->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2756); _t2758->text = *_ca; free(_ca); }
                _t2758->line = U32_clone(&(U32){line});
                _t2758->col = _t2757;
                (void)_t2758;
                Str_delete(_t2756, &(Bool){1});
                ;
                Vec_push(tokens, _t2758);
                U64_inc(pos);
            } else {
                Str *_t2759 = Str_lit("Str", 3ULL);
                (void)_t2759;
                U64 _t2760; { U64 *_hp = (U64 *)Str_size(); _t2760 = *_hp; free(_hp); }
                (void)_t2760;
                U64 _t2761 = 6;
                (void)_t2761;
                Array *_va52 = Array_new(_t2759, &(U64){_t2760}, &(U64){_t2761});
                (void)_va52;
                Str_delete(_t2759, &(Bool){1});
                ;
                ;
                U64 _t2762 = 0;
                (void)_t2762;
                Str *_t2763 = Str_clone(path);
                (void)_t2763;
                Array_set(_va52, &(U64){_t2762}, _t2763);
                ;
                U64 _t2764 = 1;
                (void)_t2764;
                Str *_t2765 = Str_lit(":", 1ULL);
                (void)_t2765;
                Array_set(_va52, &(U64){_t2764}, _t2765);
                ;
                U64 _t2766 = 2;
                (void)_t2766;
                Str *_t2767 = U32_to_str(&(U32){line});
                (void)_t2767;
                Array_set(_va52, &(U64){_t2766}, _t2767);
                ;
                U64 _t2768 = 3;
                (void)_t2768;
                Str *_t2769 = Str_lit(":", 1ULL);
                (void)_t2769;
                Array_set(_va52, &(U64){_t2768}, _t2769);
                ;
                U64 _t2770 = 4;
                (void)_t2770;
                Str *_t2771 = U32_to_str(&(U32){col});
                (void)_t2771;
                Array_set(_va52, &(U64){_t2770}, _t2771);
                ;
                U64 _t2772 = 5;
                (void)_t2772;
                Str *_t2773 = Str_lit(": error: unterminated character literal", 39ULL);
                (void)_t2773;
                Array_set(_va52, &(U64){_t2772}, _t2773);
                ;
                println(_va52);
                U64 _t2774 = U64_sub(DEREF(pos), start);
                (void)_t2774;
                Str *_t2775 = Str_substr(src, &(U64){start}, &(U64){_t2774});
                (void)_t2775;
                ;
                U32 _t2776 = U32_clone(&(U32){col});
                (void)_t2776;
                Token *_t2777 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2777->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2775); _t2777->text = *_ca; free(_ca); }
                _t2777->line = U32_clone(&(U32){line});
                _t2777->col = _t2776;
                (void)_t2777;
                Str_delete(_t2775, &(Bool){1});
                ;
                Vec_push(tokens, _t2777);
            }
            ;
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U64 _t2919 = 1;
        (void)_t2919;
        U64 _t2920 = U64_add(DEREF(pos), _t2919);
        (void)_t2920;
        ;
        Bool _t2921; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2920}, &(U64){src_len}); _t2921 = *_hp; free(_hp); }
        (void)_t2921;
        ;
        if (_t2921) {
            U64 _t2837 = 1;
            (void)_t2837;
            U64 *_t2838 = malloc(sizeof(U64)); *_t2838 = U64_add(DEREF(pos), _t2837);
            (void)_t2838;
            ;
            U8 *c2 = Str_byte_at(src, _t2838);
            (void)c2;
            TokenType *two = TokenType_clone(TokenType_Eof());
            (void)two;
            U8 _t2839 = 58;
            (void)_t2839;
            U8 _t2840 = 61;
            (void)_t2840;
            Bool _t2841 = U8_eq(DEREF(c), _t2839);
            (void)_t2841;
            ;
            Bool _t2842 = U8_eq(DEREF(c2), _t2840);
            (void)_t2842;
            ;
            Bool _t2843 = Bool_and(_t2841, _t2842);
            (void)_t2843;
            ;
            ;
            if (_t2843) {
                two = TokenType_clone(TokenType_ColonEq());
            } else {
                U8 _t2825 = 61;
                (void)_t2825;
                U8 _t2826 = 61;
                (void)_t2826;
                Bool _t2827 = U8_eq(DEREF(c), _t2825);
                (void)_t2827;
                ;
                Bool _t2828 = U8_eq(DEREF(c2), _t2826);
                (void)_t2828;
                ;
                Bool _t2829 = Bool_and(_t2827, _t2828);
                (void)_t2829;
                ;
                ;
                if (_t2829) {
                    two = TokenType_clone(TokenType_EqEq());
                } else {
                    U8 _t2820 = 33;
                    (void)_t2820;
                    U8 _t2821 = 61;
                    (void)_t2821;
                    Bool _t2822 = U8_eq(DEREF(c), _t2820);
                    (void)_t2822;
                    ;
                    Bool _t2823 = U8_eq(DEREF(c2), _t2821);
                    (void)_t2823;
                    ;
                    Bool _t2824 = Bool_and(_t2822, _t2823);
                    (void)_t2824;
                    ;
                    ;
                    if (_t2824) {
                        two = TokenType_clone(TokenType_Neq());
                    } else {
                        U8 _t2815 = 60;
                        (void)_t2815;
                        U8 _t2816 = 61;
                        (void)_t2816;
                        Bool _t2817 = U8_eq(DEREF(c), _t2815);
                        (void)_t2817;
                        ;
                        Bool _t2818 = U8_eq(DEREF(c2), _t2816);
                        (void)_t2818;
                        ;
                        Bool _t2819 = Bool_and(_t2817, _t2818);
                        (void)_t2819;
                        ;
                        ;
                        if (_t2819) {
                            two = TokenType_clone(TokenType_LtEq());
                        } else {
                            U8 _t2810 = 62;
                            (void)_t2810;
                            U8 _t2811 = 61;
                            (void)_t2811;
                            Bool _t2812 = U8_eq(DEREF(c), _t2810);
                            (void)_t2812;
                            ;
                            Bool _t2813 = U8_eq(DEREF(c2), _t2811);
                            (void)_t2813;
                            ;
                            Bool _t2814 = Bool_and(_t2812, _t2813);
                            (void)_t2814;
                            ;
                            ;
                            if (_t2814) {
                                two = TokenType_clone(TokenType_GtEq());
                            } else {
                                U8 _t2805 = 46;
                                (void)_t2805;
                                U8 _t2806 = 46;
                                (void)_t2806;
                                Bool _t2807 = U8_eq(DEREF(c), _t2805);
                                (void)_t2807;
                                ;
                                Bool _t2808 = U8_eq(DEREF(c2), _t2806);
                                (void)_t2808;
                                ;
                                Bool _t2809 = Bool_and(_t2807, _t2808);
                                (void)_t2809;
                                ;
                                ;
                                if (_t2809) {
                                    U64 _t2802 = 2;
                                    (void)_t2802;
                                    U64 _t2803 = U64_add(DEREF(pos), _t2802);
                                    (void)_t2803;
                                    ;
                                    Bool _t2804; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2803}, &(U64){src_len}); _t2804 = *_hp; free(_hp); }
                                    (void)_t2804;
                                    ;
                                    if (_t2804) {
                                        U64 _t2798 = 2;
                                        (void)_t2798;
                                        U64 *_t2799 = malloc(sizeof(U64)); *_t2799 = U64_add(DEREF(pos), _t2798);
                                        (void)_t2799;
                                        ;
                                        U8 *c3 = Str_byte_at(src, _t2799);
                                        (void)c3;
                                        U8 _t2800 = 46;
                                        (void)_t2800;
                                        Bool _t2801 = U8_eq(DEREF(c3), _t2800);
                                        (void)_t2801;
                                        U64_delete(_t2799, &(Bool){1});
                                        ;
                                        if (_t2801) {
                                            U64 _t2792 = 3;
                                            (void)_t2792;
                                            Str *_t2793 = Str_substr(src, &(U64){start}, &(U64){_t2792});
                                            (void)_t2793;
                                            ;
                                            U32 _t2794 = U32_clone(&(U32){col});
                                            (void)_t2794;
                                            Token *_t2795 = malloc(sizeof(Token));
                                            { TokenType *_ca = TokenType_clone(TokenType_DotDotDot()); _t2795->type = *_ca; free(_ca); }
                                            { Str *_ca = Str_clone(_t2793); _t2795->text = *_ca; free(_ca); }
                                            _t2795->line = U32_clone(&(U32){line});
                                            _t2795->col = _t2794;
                                            (void)_t2795;
                                            Str_delete(_t2793, &(Bool){1});
                                            ;
                                            Vec_push(tokens, _t2795);
                                            U64 _t2796 = 3;
                                            (void)_t2796;
                                            U64 _t2797 = U64_add(DEREF(pos), _t2796);
                                            (void)_t2797;
                                            ;
                                            *pos = _t2797;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            U64_delete(_t2838, &(Bool){1});
                                            ;
                                            TokenType_delete(two, &(Bool){1});
                                            ;
                                            ;
                                            ;
                                            continue;
                                        }
                                        ;
                                    }
                                    ;
                                    two = TokenType_clone(TokenType_DotDot());
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
            U64_delete(_t2838, &(Bool){1});
            ;
            Bool _t2844; { Bool *_hp = (Bool *)TokenType_eq(two, TokenType_Eof()); _t2844 = *_hp; free(_hp); }
            (void)_t2844;
            Bool _t2845 = Bool_not(_t2844);
            (void)_t2845;
            ;
            if (_t2845) {
                U64 _t2830 = 2;
                (void)_t2830;
                Str *_t2831 = Str_substr(src, &(U64){start}, &(U64){_t2830});
                (void)_t2831;
                ;
                U32 _t2832 = U32_clone(&(U32){line});
                (void)_t2832;
                U32 _t2833 = U32_clone(&(U32){col});
                (void)_t2833;
                Token *_t2834 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(two); _t2834->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2831); _t2834->text = *_ca; free(_ca); }
                _t2834->line = _t2832;
                _t2834->col = _t2833;
                (void)_t2834;
                Str_delete(_t2831, &(Bool){1});
                ;
                ;
                Vec_push(tokens, _t2834);
                U64 _t2835 = 2;
                (void)_t2835;
                U64 _t2836 = U64_add(DEREF(pos), _t2835);
                (void)_t2836;
                ;
                *pos = _t2836;
                ;
                ;
                TokenType_delete(two, &(Bool){1});
                ;
                ;
                ;
                continue;
            }
            ;
            TokenType_delete(two, &(Bool){1});
        }
        ;
        TokenType *single = TokenType_clone(TokenType_Eof());
        (void)single;
        {
            U8 _sw2846 = U8_clone(c);
            (void)_sw2846;
            U8 _t2881 = 40;
            (void)_t2881;
            Bool _t2882 = U8_eq(_sw2846, _t2881);
            (void)_t2882;
            ;
            if (_t2882) {
                single = TokenType_clone(TokenType_LParen());
            } else {
                U8 _t2879 = 41;
                (void)_t2879;
                Bool _t2880 = U8_eq(_sw2846, _t2879);
                (void)_t2880;
                ;
                if (_t2880) {
                    single = TokenType_clone(TokenType_RParen());
                } else {
                    U8 _t2877 = 123;
                    (void)_t2877;
                    Bool _t2878 = U8_eq(_sw2846, _t2877);
                    (void)_t2878;
                    ;
                    if (_t2878) {
                        single = TokenType_clone(TokenType_LBrace());
                    } else {
                        U8 _t2875 = 125;
                        (void)_t2875;
                        Bool _t2876 = U8_eq(_sw2846, _t2875);
                        (void)_t2876;
                        ;
                        if (_t2876) {
                            single = TokenType_clone(TokenType_RBrace());
                        } else {
                            U8 _t2873 = 91;
                            (void)_t2873;
                            Bool _t2874 = U8_eq(_sw2846, _t2873);
                            (void)_t2874;
                            ;
                            if (_t2874) {
                                single = TokenType_clone(TokenType_LBracket());
                            } else {
                                U8 _t2871 = 93;
                                (void)_t2871;
                                Bool _t2872 = U8_eq(_sw2846, _t2871);
                                (void)_t2872;
                                ;
                                if (_t2872) {
                                    single = TokenType_clone(TokenType_RBracket());
                                } else {
                                    U8 _t2869 = 44;
                                    (void)_t2869;
                                    Bool _t2870 = U8_eq(_sw2846, _t2869);
                                    (void)_t2870;
                                    ;
                                    if (_t2870) {
                                        single = TokenType_clone(TokenType_Comma());
                                    } else {
                                        U8 _t2867 = 58;
                                        (void)_t2867;
                                        Bool _t2868 = U8_eq(_sw2846, _t2867);
                                        (void)_t2868;
                                        ;
                                        if (_t2868) {
                                            single = TokenType_clone(TokenType_Colon());
                                        } else {
                                            U8 _t2865 = 46;
                                            (void)_t2865;
                                            Bool _t2866 = U8_eq(_sw2846, _t2865);
                                            (void)_t2866;
                                            ;
                                            if (_t2866) {
                                                single = TokenType_clone(TokenType_Dot());
                                            } else {
                                                U8 _t2863 = 63;
                                                (void)_t2863;
                                                Bool _t2864 = U8_eq(_sw2846, _t2863);
                                                (void)_t2864;
                                                ;
                                                if (_t2864) {
                                                    single = TokenType_clone(TokenType_Question());
                                                } else {
                                                    U8 _t2861 = 33;
                                                    (void)_t2861;
                                                    Bool _t2862 = U8_eq(_sw2846, _t2861);
                                                    (void)_t2862;
                                                    ;
                                                    if (_t2862) {
                                                        single = TokenType_clone(TokenType_Bang());
                                                    } else {
                                                        U8 _t2859 = 43;
                                                        (void)_t2859;
                                                        Bool _t2860 = U8_eq(_sw2846, _t2859);
                                                        (void)_t2860;
                                                        ;
                                                        if (_t2860) {
                                                            single = TokenType_clone(TokenType_Plus());
                                                        } else {
                                                            U8 _t2857 = 45;
                                                            (void)_t2857;
                                                            Bool _t2858 = U8_eq(_sw2846, _t2857);
                                                            (void)_t2858;
                                                            ;
                                                            if (_t2858) {
                                                                single = TokenType_clone(TokenType_Minus());
                                                            } else {
                                                                U8 _t2855 = 42;
                                                                (void)_t2855;
                                                                Bool _t2856 = U8_eq(_sw2846, _t2855);
                                                                (void)_t2856;
                                                                ;
                                                                if (_t2856) {
                                                                    single = TokenType_clone(TokenType_Star());
                                                                } else {
                                                                    U8 _t2853 = 47;
                                                                    (void)_t2853;
                                                                    Bool _t2854 = U8_eq(_sw2846, _t2853);
                                                                    (void)_t2854;
                                                                    ;
                                                                    if (_t2854) {
                                                                        single = TokenType_clone(TokenType_Slash());
                                                                    } else {
                                                                        U8 _t2851 = 61;
                                                                        (void)_t2851;
                                                                        Bool _t2852 = U8_eq(_sw2846, _t2851);
                                                                        (void)_t2852;
                                                                        ;
                                                                        if (_t2852) {
                                                                            single = TokenType_clone(TokenType_Eq());
                                                                        } else {
                                                                            U8 _t2849 = 60;
                                                                            (void)_t2849;
                                                                            Bool _t2850 = U8_eq(_sw2846, _t2849);
                                                                            (void)_t2850;
                                                                            ;
                                                                            if (_t2850) {
                                                                                single = TokenType_clone(TokenType_Lt());
                                                                            } else {
                                                                                U8 _t2847 = 62;
                                                                                (void)_t2847;
                                                                                Bool _t2848 = U8_eq(_sw2846, _t2847);
                                                                                (void)_t2848;
                                                                                ;
                                                                                if (_t2848) {
                                                                                    single = TokenType_clone(TokenType_Gt());
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
            ;
        }
        Bool _t2922; { Bool *_hp = (Bool *)TokenType_eq(single, TokenType_Eof()); _t2922 = *_hp; free(_hp); }
        (void)_t2922;
        Bool _t2923 = Bool_not(_t2922);
        (void)_t2923;
        ;
        if (_t2923) {
            U64 _t2883 = 1;
            (void)_t2883;
            Str *_t2884 = Str_substr(src, &(U64){start}, &(U64){_t2883});
            (void)_t2884;
            ;
            U32 _t2885 = U32_clone(&(U32){line});
            (void)_t2885;
            U32 _t2886 = U32_clone(&(U32){col});
            (void)_t2886;
            Token *_t2887 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(single); _t2887->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(_t2884); _t2887->text = *_ca; free(_ca); }
            _t2887->line = _t2885;
            _t2887->col = _t2886;
            (void)_t2887;
            Str_delete(_t2884, &(Bool){1});
            ;
            ;
            Vec_push(tokens, _t2887);
            U64_inc(pos);
            ;
            ;
            TokenType_delete(single, &(Bool){1});
            ;
            continue;
        }
        ;
        TokenType_delete(single, &(Bool){1});
        Str *_t2924 = Str_lit("Str", 3ULL);
        (void)_t2924;
        U64 _t2925; { U64 *_hp = (U64 *)Str_size(); _t2925 = *_hp; free(_hp); }
        (void)_t2925;
        U64 _t2926 = 6;
        (void)_t2926;
        Array *_va53 = Array_new(_t2924, &(U64){_t2925}, &(U64){_t2926});
        (void)_va53;
        Str_delete(_t2924, &(Bool){1});
        ;
        ;
        U64 _t2927 = 0;
        (void)_t2927;
        Str *_t2928 = Str_clone(path);
        (void)_t2928;
        Array_set(_va53, &(U64){_t2927}, _t2928);
        ;
        U64 _t2929 = 1;
        (void)_t2929;
        Str *_t2930 = Str_lit(":", 1ULL);
        (void)_t2930;
        Array_set(_va53, &(U64){_t2929}, _t2930);
        ;
        U64 _t2931 = 2;
        (void)_t2931;
        Str *_t2932 = U32_to_str(&(U32){line});
        (void)_t2932;
        Array_set(_va53, &(U64){_t2931}, _t2932);
        ;
        U64 _t2933 = 3;
        (void)_t2933;
        Str *_t2934 = Str_lit(":", 1ULL);
        (void)_t2934;
        Array_set(_va53, &(U64){_t2933}, _t2934);
        ;
        U64 _t2935 = 4;
        (void)_t2935;
        Str *_t2936 = U32_to_str(&(U32){col});
        (void)_t2936;
        Array_set(_va53, &(U64){_t2935}, _t2936);
        ;
        U64 _t2937 = 5;
        (void)_t2937;
        Str *_t2938 = Str_lit(": error: unexpected character", 29ULL);
        (void)_t2938;
        Array_set(_va53, &(U64){_t2937}, _t2938);
        ;
        println(_va53);
        U64 _t2939 = 1;
        (void)_t2939;
        Str *_t2940 = Str_substr(src, &(U64){start}, &(U64){_t2939});
        (void)_t2940;
        ;
        ;
        U32 _t2941 = U32_clone(&(U32){col});
        (void)_t2941;
        ;
        Token *_t2942 = malloc(sizeof(Token));
        { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2942->type = *_ca; free(_ca); }
        { Str *_ca = Str_clone(_t2940); _t2942->text = *_ca; free(_ca); }
        _t2942->line = U32_clone(&(U32){line});
        _t2942->col = _t2941;
        (void)_t2942;
        Str_delete(_t2940, &(Bool){1});
        ;
        Vec_push(tokens, _t2942);
        U64_inc(pos);
    }
    ;
    U64 _t2945 = U64_sub(DEREF(pos), line_start);
    (void)_t2945;
    ;
    U64_delete(pos, &(Bool){1});
    U64 _t2946 = 1;
    (void)_t2946;
    U64 _t2947 = U64_add(_t2945, _t2946);
    (void)_t2947;
    ;
    ;
    I64 col = U64_to_i64(_t2947);
    (void)col;
    ;
    I64 _t2948 = I64_clone(&(I64){col});
    (void)_t2948;
    ;
    Token *_t2949 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(TokenType_Eof()); _t2949->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t2949->text = *_ca; free(_ca); }
    _t2949->line = U32_clone(&(U32){line});
    _t2949->col = _t2948;
    (void)_t2949;
    ;
    ;
    Vec_push(tokens, _t2949);
    return tokens;
}

