#include "modes_lexer.h"

Token * Token_clone(Token * self) {
    (void)self;
    U32 _t2386 = U32_clone(&self->line);
    (void)_t2386;
    U32 _t2387 = U32_clone(&self->col);
    (void)_t2387;
    Token *_t2388 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(&self->type); _t2388->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->text); _t2388->text = *_ca; free(_ca); }
    _t2388->line = _t2386;
    _t2388->col = _t2387;
    (void)_t2388;
    ;
    ;
    return _t2388;
}

void Token_delete(Token * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t2389 = 0;
    (void)_t2389;
    TokenType_delete(&self->type, &(Bool){_t2389});
    ;
    Bool _t2390 = 0;
    (void)_t2390;
    Str_delete(&self->text, &(Bool){_t2390});
    ;
    Bool _t2391 = 0;
    (void)_t2391;
    U32_delete(&self->line, &(Bool){_t2391});
    ;
    Bool _t2392 = 0;
    (void)_t2392;
    U32_delete(&self->col, &(Bool){_t2392});
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
    U8 _t2394 = 48;
    (void)_t2394;
    U8 _t2395 = 57;
    (void)_t2395;
    Bool _t2396; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t2394}); _t2396 = *_hp; free(_hp); }
    (void)_t2396;
    ;
    Bool _t2397; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t2395}); _t2397 = *_hp; free(_hp); }
    (void)_t2397;
    ;
    Bool _t2398 = Bool_and(_t2396, _t2397);
    (void)_t2398;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2398; return _r; }
}

Bool * is_alpha(U8 * c) {
    (void)c;
    U8 _t2399 = 97;
    (void)_t2399;
    U8 _t2400 = 122;
    (void)_t2400;
    Bool _t2401; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t2399}); _t2401 = *_hp; free(_hp); }
    (void)_t2401;
    ;
    Bool _t2402; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t2400}); _t2402 = *_hp; free(_hp); }
    (void)_t2402;
    ;
    U8 _t2403 = 65;
    (void)_t2403;
    U8 _t2404 = 90;
    (void)_t2404;
    Bool _t2405; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t2403}); _t2405 = *_hp; free(_hp); }
    (void)_t2405;
    ;
    Bool _t2406; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t2404}); _t2406 = *_hp; free(_hp); }
    (void)_t2406;
    ;
    Bool _t2407 = Bool_and(_t2401, _t2402);
    (void)_t2407;
    ;
    ;
    Bool _t2408 = Bool_and(_t2405, _t2406);
    (void)_t2408;
    ;
    ;
    U8 _t2409 = 95;
    (void)_t2409;
    Bool _t2410 = Bool_or(_t2407, _t2408);
    (void)_t2410;
    ;
    ;
    Bool _t2411 = U8_eq(DEREF(c), _t2409);
    (void)_t2411;
    ;
    Bool _t2412 = Bool_or(_t2410, _t2411);
    (void)_t2412;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2412; return _r; }
}

Bool * is_alnum(U8 * c) {
    (void)c;
    Bool _t2413; { Bool *_hp = (Bool *)is_alpha(c); _t2413 = *_hp; free(_hp); }
    (void)_t2413;
    Bool _t2414; { Bool *_hp = (Bool *)is_digit(c); _t2414 = *_hp; free(_hp); }
    (void)_t2414;
    Bool _t2415 = Bool_or(_t2413, _t2414);
    (void)_t2415;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2415; return _r; }
}

Str * tok_name(TokenType * type) {
    (void)type;
    {
        TokenType *_sw2416 = TokenType_clone(type);
        (void)_sw2416;
        Bool _t2549; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_Eof()); _t2549 = *_hp; free(_hp); }
        (void)_t2549;
        if (_t2549) {
            Str *_t2417 = Str_lit("eof", 3ULL);
            (void)_t2417;
            TokenType_delete(_sw2416, &(Bool){1});
            ;
            return _t2417;
        } else {
            Bool _t2548; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_LParen()); _t2548 = *_hp; free(_hp); }
            (void)_t2548;
            if (_t2548) {
                Str *_t2418 = Str_lit("(", 1ULL);
                (void)_t2418;
                ;
                TokenType_delete(_sw2416, &(Bool){1});
                ;
                return _t2418;
            } else {
                Bool _t2547; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_RParen()); _t2547 = *_hp; free(_hp); }
                (void)_t2547;
                if (_t2547) {
                    Str *_t2419 = Str_lit(")", 1ULL);
                    (void)_t2419;
                    ;
                    ;
                    TokenType_delete(_sw2416, &(Bool){1});
                    ;
                    return _t2419;
                } else {
                    Bool _t2546; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_LBrace()); _t2546 = *_hp; free(_hp); }
                    (void)_t2546;
                    if (_t2546) {
                        Str *_t2420 = Str_lit("{", 1ULL);
                        (void)_t2420;
                        ;
                        ;
                        ;
                        TokenType_delete(_sw2416, &(Bool){1});
                        ;
                        return _t2420;
                    } else {
                        Bool _t2545; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_RBrace()); _t2545 = *_hp; free(_hp); }
                        (void)_t2545;
                        if (_t2545) {
                            Str *_t2421 = Str_lit("}", 1ULL);
                            (void)_t2421;
                            ;
                            ;
                            ;
                            ;
                            TokenType_delete(_sw2416, &(Bool){1});
                            ;
                            return _t2421;
                        } else {
                            Bool _t2544; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_LBracket()); _t2544 = *_hp; free(_hp); }
                            (void)_t2544;
                            if (_t2544) {
                                Str *_t2422 = Str_lit("[", 1ULL);
                                (void)_t2422;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TokenType_delete(_sw2416, &(Bool){1});
                                ;
                                return _t2422;
                            } else {
                                Bool _t2543; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_RBracket()); _t2543 = *_hp; free(_hp); }
                                (void)_t2543;
                                if (_t2543) {
                                    Str *_t2423 = Str_lit("]", 1ULL);
                                    (void)_t2423;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TokenType_delete(_sw2416, &(Bool){1});
                                    ;
                                    return _t2423;
                                } else {
                                    Bool _t2542; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_Comma()); _t2542 = *_hp; free(_hp); }
                                    (void)_t2542;
                                    if (_t2542) {
                                        Str *_t2424 = Str_lit(",", 1ULL);
                                        (void)_t2424;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TokenType_delete(_sw2416, &(Bool){1});
                                        ;
                                        return _t2424;
                                    } else {
                                        Bool _t2541; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_Colon()); _t2541 = *_hp; free(_hp); }
                                        (void)_t2541;
                                        if (_t2541) {
                                            Str *_t2425 = Str_lit(":", 1ULL);
                                            (void)_t2425;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TokenType_delete(_sw2416, &(Bool){1});
                                            ;
                                            return _t2425;
                                        } else {
                                            Bool _t2540; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_Question()); _t2540 = *_hp; free(_hp); }
                                            (void)_t2540;
                                            if (_t2540) {
                                                Str *_t2426 = Str_lit("?", 1ULL);
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
                                                TokenType_delete(_sw2416, &(Bool){1});
                                                ;
                                                return _t2426;
                                            } else {
                                                Bool _t2539; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_Bang()); _t2539 = *_hp; free(_hp); }
                                                (void)_t2539;
                                                if (_t2539) {
                                                    Str *_t2427 = Str_lit("!", 1ULL);
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
                                                    TokenType_delete(_sw2416, &(Bool){1});
                                                    ;
                                                    return _t2427;
                                                } else {
                                                    Bool _t2538; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_Minus()); _t2538 = *_hp; free(_hp); }
                                                    (void)_t2538;
                                                    if (_t2538) {
                                                        Str *_t2428 = Str_lit("-", 1ULL);
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
                                                        TokenType_delete(_sw2416, &(Bool){1});
                                                        ;
                                                        return _t2428;
                                                    } else {
                                                        Bool _t2537; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_Plus()); _t2537 = *_hp; free(_hp); }
                                                        (void)_t2537;
                                                        if (_t2537) {
                                                            Str *_t2429 = Str_lit("+", 1ULL);
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
                                                            TokenType_delete(_sw2416, &(Bool){1});
                                                            ;
                                                            return _t2429;
                                                        } else {
                                                            Bool _t2536; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_Star()); _t2536 = *_hp; free(_hp); }
                                                            (void)_t2536;
                                                            if (_t2536) {
                                                                Str *_t2430 = Str_lit("*", 1ULL);
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
                                                                TokenType_delete(_sw2416, &(Bool){1});
                                                                ;
                                                                return _t2430;
                                                            } else {
                                                                Bool _t2535; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_Slash()); _t2535 = *_hp; free(_hp); }
                                                                (void)_t2535;
                                                                if (_t2535) {
                                                                    Str *_t2431 = Str_lit("/", 1ULL);
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
                                                                    TokenType_delete(_sw2416, &(Bool){1});
                                                                    ;
                                                                    return _t2431;
                                                                } else {
                                                                    Bool _t2534; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_Dot()); _t2534 = *_hp; free(_hp); }
                                                                    (void)_t2534;
                                                                    if (_t2534) {
                                                                        Str *_t2432 = Str_lit(".", 1ULL);
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
                                                                        TokenType_delete(_sw2416, &(Bool){1});
                                                                        ;
                                                                        return _t2432;
                                                                    } else {
                                                                        Bool _t2533; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_DotDot()); _t2533 = *_hp; free(_hp); }
                                                                        (void)_t2533;
                                                                        if (_t2533) {
                                                                            Str *_t2433 = Str_lit("..", 2ULL);
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
                                                                            TokenType_delete(_sw2416, &(Bool){1});
                                                                            ;
                                                                            return _t2433;
                                                                        } else {
                                                                            Bool _t2532; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_DotDotDot()); _t2532 = *_hp; free(_hp); }
                                                                            (void)_t2532;
                                                                            if (_t2532) {
                                                                                Str *_t2434 = Str_lit("...", 3ULL);
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
                                                                                TokenType_delete(_sw2416, &(Bool){1});
                                                                                ;
                                                                                return _t2434;
                                                                            } else {
                                                                                Bool _t2531; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_Eq()); _t2531 = *_hp; free(_hp); }
                                                                                (void)_t2531;
                                                                                if (_t2531) {
                                                                                    Str *_t2435 = Str_lit("=", 1ULL);
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
                                                                                    TokenType_delete(_sw2416, &(Bool){1});
                                                                                    ;
                                                                                    return _t2435;
                                                                                } else {
                                                                                    Bool _t2530; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_EqEq()); _t2530 = *_hp; free(_hp); }
                                                                                    (void)_t2530;
                                                                                    if (_t2530) {
                                                                                        Str *_t2436 = Str_lit("==", 2ULL);
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
                                                                                        TokenType_delete(_sw2416, &(Bool){1});
                                                                                        ;
                                                                                        return _t2436;
                                                                                    } else {
                                                                                        Bool _t2529; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_Neq()); _t2529 = *_hp; free(_hp); }
                                                                                        (void)_t2529;
                                                                                        if (_t2529) {
                                                                                            Str *_t2437 = Str_lit("!=", 2ULL);
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
                                                                                            TokenType_delete(_sw2416, &(Bool){1});
                                                                                            ;
                                                                                            return _t2437;
                                                                                        } else {
                                                                                            Bool _t2528; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_Lt()); _t2528 = *_hp; free(_hp); }
                                                                                            (void)_t2528;
                                                                                            if (_t2528) {
                                                                                                Str *_t2438 = Str_lit("<", 1ULL);
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
                                                                                                TokenType_delete(_sw2416, &(Bool){1});
                                                                                                ;
                                                                                                return _t2438;
                                                                                            } else {
                                                                                                Bool _t2527; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_LtEq()); _t2527 = *_hp; free(_hp); }
                                                                                                (void)_t2527;
                                                                                                if (_t2527) {
                                                                                                    Str *_t2439 = Str_lit("<=", 2ULL);
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
                                                                                                    TokenType_delete(_sw2416, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t2439;
                                                                                                } else {
                                                                                                    Bool _t2526; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_Gt()); _t2526 = *_hp; free(_hp); }
                                                                                                    (void)_t2526;
                                                                                                    if (_t2526) {
                                                                                                        Str *_t2440 = Str_lit(">", 1ULL);
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
                                                                                                        TokenType_delete(_sw2416, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t2440;
                                                                                                    } else {
                                                                                                        Bool _t2525; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_GtEq()); _t2525 = *_hp; free(_hp); }
                                                                                                        (void)_t2525;
                                                                                                        if (_t2525) {
                                                                                                            Str *_t2441 = Str_lit(">=", 2ULL);
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
                                                                                                            TokenType_delete(_sw2416, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t2441;
                                                                                                        } else {
                                                                                                            Bool _t2524; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_ColonEq()); _t2524 = *_hp; free(_hp); }
                                                                                                            (void)_t2524;
                                                                                                            if (_t2524) {
                                                                                                                Str *_t2442 = Str_lit(":=", 2ULL);
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
                                                                                                                TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                ;
                                                                                                                return _t2442;
                                                                                                            } else {
                                                                                                                Bool _t2523; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_Ident()); _t2523 = *_hp; free(_hp); }
                                                                                                                (void)_t2523;
                                                                                                                if (_t2523) {
                                                                                                                    Str *_t2443 = Str_lit("identifier", 10ULL);
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
                                                                                                                    TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return _t2443;
                                                                                                                } else {
                                                                                                                    Bool _t2522; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_StringTok()); _t2522 = *_hp; free(_hp); }
                                                                                                                    (void)_t2522;
                                                                                                                    if (_t2522) {
                                                                                                                        Str *_t2444 = Str_lit("string", 6ULL);
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
                                                                                                                        TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return _t2444;
                                                                                                                    } else {
                                                                                                                        Bool _t2521; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_Number()); _t2521 = *_hp; free(_hp); }
                                                                                                                        (void)_t2521;
                                                                                                                        if (_t2521) {
                                                                                                                            Str *_t2445 = Str_lit("number", 6ULL);
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
                                                                                                                            TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return _t2445;
                                                                                                                        } else {
                                                                                                                            Bool _t2520; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_Char()); _t2520 = *_hp; free(_hp); }
                                                                                                                            (void)_t2520;
                                                                                                                            if (_t2520) {
                                                                                                                                Str *_t2446 = Str_lit("char", 4ULL);
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
                                                                                                                                TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return _t2446;
                                                                                                                            } else {
                                                                                                                                Bool _t2519; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwMode()); _t2519 = *_hp; free(_hp); }
                                                                                                                                (void)_t2519;
                                                                                                                                if (_t2519) {
                                                                                                                                    Str *_t2447 = Str_lit("mode", 4ULL);
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
                                                                                                                                    TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return _t2447;
                                                                                                                                } else {
                                                                                                                                    Bool _t2518; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwMut()); _t2518 = *_hp; free(_hp); }
                                                                                                                                    (void)_t2518;
                                                                                                                                    if (_t2518) {
                                                                                                                                        Str *_t2448 = Str_lit("mut", 3ULL);
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
                                                                                                                                        TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return _t2448;
                                                                                                                                    } else {
                                                                                                                                        Bool _t2517; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwOwn()); _t2517 = *_hp; free(_hp); }
                                                                                                                                        (void)_t2517;
                                                                                                                                        if (_t2517) {
                                                                                                                                            Str *_t2449 = Str_lit("own", 3ULL);
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
                                                                                                                                            TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return _t2449;
                                                                                                                                        } else {
                                                                                                                                            Bool _t2516; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwRef()); _t2516 = *_hp; free(_hp); }
                                                                                                                                            (void)_t2516;
                                                                                                                                            if (_t2516) {
                                                                                                                                                Str *_t2450 = Str_lit("ref", 3ULL);
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
                                                                                                                                                TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return _t2450;
                                                                                                                                            } else {
                                                                                                                                                Bool _t2515; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwShallow()); _t2515 = *_hp; free(_hp); }
                                                                                                                                                (void)_t2515;
                                                                                                                                                if (_t2515) {
                                                                                                                                                    Str *_t2451 = Str_lit("shallow", 7ULL);
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
                                                                                                                                                    TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                    ;
                                                                                                                                                    return _t2451;
                                                                                                                                                } else {
                                                                                                                                                    Bool _t2514; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwStruct()); _t2514 = *_hp; free(_hp); }
                                                                                                                                                    (void)_t2514;
                                                                                                                                                    if (_t2514) {
                                                                                                                                                        Str *_t2452 = Str_lit("struct", 6ULL);
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
                                                                                                                                                        TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                        ;
                                                                                                                                                        return _t2452;
                                                                                                                                                    } else {
                                                                                                                                                        Bool _t2513; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwExtStruct()); _t2513 = *_hp; free(_hp); }
                                                                                                                                                        (void)_t2513;
                                                                                                                                                        if (_t2513) {
                                                                                                                                                            Str *_t2453 = Str_lit("ext_struct", 10ULL);
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
                                                                                                                                                            TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                            ;
                                                                                                                                                            return _t2453;
                                                                                                                                                        } else {
                                                                                                                                                            Bool _t2512; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwEnum()); _t2512 = *_hp; free(_hp); }
                                                                                                                                                            (void)_t2512;
                                                                                                                                                            if (_t2512) {
                                                                                                                                                                Str *_t2454 = Str_lit("enum", 4ULL);
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
                                                                                                                                                                TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                ;
                                                                                                                                                                return _t2454;
                                                                                                                                                            } else {
                                                                                                                                                                Bool _t2511; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwNamespace()); _t2511 = *_hp; free(_hp); }
                                                                                                                                                                (void)_t2511;
                                                                                                                                                                if (_t2511) {
                                                                                                                                                                    Str *_t2455 = Str_lit("namespace", 9ULL);
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
                                                                                                                                                                    TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                    ;
                                                                                                                                                                    return _t2455;
                                                                                                                                                                } else {
                                                                                                                                                                    Bool _t2510; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwFunc()); _t2510 = *_hp; free(_hp); }
                                                                                                                                                                    (void)_t2510;
                                                                                                                                                                    if (_t2510) {
                                                                                                                                                                        Str *_t2456 = Str_lit("func", 4ULL);
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
                                                                                                                                                                        TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                        ;
                                                                                                                                                                        return _t2456;
                                                                                                                                                                    } else {
                                                                                                                                                                        Bool _t2509; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwProc()); _t2509 = *_hp; free(_hp); }
                                                                                                                                                                        (void)_t2509;
                                                                                                                                                                        if (_t2509) {
                                                                                                                                                                            Str *_t2457 = Str_lit("proc", 4ULL);
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
                                                                                                                                                                            TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                            ;
                                                                                                                                                                            return _t2457;
                                                                                                                                                                        } else {
                                                                                                                                                                            Bool _t2508; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwTest()); _t2508 = *_hp; free(_hp); }
                                                                                                                                                                            (void)_t2508;
                                                                                                                                                                            if (_t2508) {
                                                                                                                                                                                Str *_t2458 = Str_lit("test", 4ULL);
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
                                                                                                                                                                                TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                ;
                                                                                                                                                                                return _t2458;
                                                                                                                                                                            } else {
                                                                                                                                                                                Bool _t2507; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwMacro()); _t2507 = *_hp; free(_hp); }
                                                                                                                                                                                (void)_t2507;
                                                                                                                                                                                if (_t2507) {
                                                                                                                                                                                    Str *_t2459 = Str_lit("macro", 5ULL);
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
                                                                                                                                                                                    TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                    ;
                                                                                                                                                                                    return _t2459;
                                                                                                                                                                                } else {
                                                                                                                                                                                    Bool _t2506; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwExtFunc()); _t2506 = *_hp; free(_hp); }
                                                                                                                                                                                    (void)_t2506;
                                                                                                                                                                                    if (_t2506) {
                                                                                                                                                                                        Str *_t2460 = Str_lit("ext_func", 8ULL);
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
                                                                                                                                                                                        TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                        ;
                                                                                                                                                                                        return _t2460;
                                                                                                                                                                                    } else {
                                                                                                                                                                                        Bool _t2505; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwExtProc()); _t2505 = *_hp; free(_hp); }
                                                                                                                                                                                        (void)_t2505;
                                                                                                                                                                                        if (_t2505) {
                                                                                                                                                                                            Str *_t2461 = Str_lit("ext_proc", 8ULL);
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
                                                                                                                                                                                            TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                            ;
                                                                                                                                                                                            return _t2461;
                                                                                                                                                                                        } else {
                                                                                                                                                                                            Bool _t2504; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwReturns()); _t2504 = *_hp; free(_hp); }
                                                                                                                                                                                            (void)_t2504;
                                                                                                                                                                                            if (_t2504) {
                                                                                                                                                                                                Str *_t2462 = Str_lit("returns", 7ULL);
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
                                                                                                                                                                                                TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                                ;
                                                                                                                                                                                                return _t2462;
                                                                                                                                                                                            } else {
                                                                                                                                                                                                Bool _t2503; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwThrows()); _t2503 = *_hp; free(_hp); }
                                                                                                                                                                                                (void)_t2503;
                                                                                                                                                                                                if (_t2503) {
                                                                                                                                                                                                    Str *_t2463 = Str_lit("throws", 6ULL);
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
                                                                                                                                                                                                    TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    return _t2463;
                                                                                                                                                                                                } else {
                                                                                                                                                                                                    Bool _t2502; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwIf()); _t2502 = *_hp; free(_hp); }
                                                                                                                                                                                                    (void)_t2502;
                                                                                                                                                                                                    if (_t2502) {
                                                                                                                                                                                                        Str *_t2464 = Str_lit("if", 2ULL);
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
                                                                                                                                                                                                        TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        return _t2464;
                                                                                                                                                                                                    } else {
                                                                                                                                                                                                        Bool _t2501; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwElse()); _t2501 = *_hp; free(_hp); }
                                                                                                                                                                                                        (void)_t2501;
                                                                                                                                                                                                        if (_t2501) {
                                                                                                                                                                                                            Str *_t2465 = Str_lit("else", 4ULL);
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
                                                                                                                                                                                                            TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            return _t2465;
                                                                                                                                                                                                        } else {
                                                                                                                                                                                                            Bool _t2500; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwWhile()); _t2500 = *_hp; free(_hp); }
                                                                                                                                                                                                            (void)_t2500;
                                                                                                                                                                                                            if (_t2500) {
                                                                                                                                                                                                                Str *_t2466 = Str_lit("while", 5ULL);
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
                                                                                                                                                                                                                TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                return _t2466;
                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                Bool _t2499; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwFor()); _t2499 = *_hp; free(_hp); }
                                                                                                                                                                                                                (void)_t2499;
                                                                                                                                                                                                                if (_t2499) {
                                                                                                                                                                                                                    Str *_t2467 = Str_lit("for", 3ULL);
                                                                                                                                                                                                                    (void)_t2467;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    return _t2467;
                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                    Bool _t2498; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwIn()); _t2498 = *_hp; free(_hp); }
                                                                                                                                                                                                                    (void)_t2498;
                                                                                                                                                                                                                    if (_t2498) {
                                                                                                                                                                                                                        Str *_t2468 = Str_lit("in", 2ULL);
                                                                                                                                                                                                                        (void)_t2468;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        return _t2468;
                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                        Bool _t2497; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwSwitch()); _t2497 = *_hp; free(_hp); }
                                                                                                                                                                                                                        (void)_t2497;
                                                                                                                                                                                                                        if (_t2497) {
                                                                                                                                                                                                                            Str *_t2469 = Str_lit("switch", 6ULL);
                                                                                                                                                                                                                            (void)_t2469;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            return _t2469;
                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                            Bool _t2496; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwMatch()); _t2496 = *_hp; free(_hp); }
                                                                                                                                                                                                                            (void)_t2496;
                                                                                                                                                                                                                            if (_t2496) {
                                                                                                                                                                                                                                Str *_t2470 = Str_lit("match", 5ULL);
                                                                                                                                                                                                                                (void)_t2470;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                return _t2470;
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                Bool _t2495; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwCase()); _t2495 = *_hp; free(_hp); }
                                                                                                                                                                                                                                (void)_t2495;
                                                                                                                                                                                                                                if (_t2495) {
                                                                                                                                                                                                                                    Str *_t2471 = Str_lit("case", 4ULL);
                                                                                                                                                                                                                                    (void)_t2471;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    return _t2471;
                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                    Bool _t2494; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwDefault()); _t2494 = *_hp; free(_hp); }
                                                                                                                                                                                                                                    (void)_t2494;
                                                                                                                                                                                                                                    if (_t2494) {
                                                                                                                                                                                                                                        Str *_t2472 = Str_lit("default", 7ULL);
                                                                                                                                                                                                                                        (void)_t2472;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        return _t2472;
                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                        Bool _t2493; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwReturn()); _t2493 = *_hp; free(_hp); }
                                                                                                                                                                                                                                        (void)_t2493;
                                                                                                                                                                                                                                        if (_t2493) {
                                                                                                                                                                                                                                            Str *_t2473 = Str_lit("return", 6ULL);
                                                                                                                                                                                                                                            (void)_t2473;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            return _t2473;
                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                            Bool _t2492; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwThrow()); _t2492 = *_hp; free(_hp); }
                                                                                                                                                                                                                                            (void)_t2492;
                                                                                                                                                                                                                                            if (_t2492) {
                                                                                                                                                                                                                                                Str *_t2474 = Str_lit("throw", 5ULL);
                                                                                                                                                                                                                                                (void)_t2474;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                return _t2474;
                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                Bool _t2491; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwCatch()); _t2491 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                (void)_t2491;
                                                                                                                                                                                                                                                if (_t2491) {
                                                                                                                                                                                                                                                    Str *_t2475 = Str_lit("catch", 5ULL);
                                                                                                                                                                                                                                                    (void)_t2475;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    return _t2475;
                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                    Bool _t2490; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwBreak()); _t2490 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                    (void)_t2490;
                                                                                                                                                                                                                                                    if (_t2490) {
                                                                                                                                                                                                                                                        Str *_t2476 = Str_lit("break", 5ULL);
                                                                                                                                                                                                                                                        (void)_t2476;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        return _t2476;
                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                        Bool _t2489; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwContinue()); _t2489 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                        (void)_t2489;
                                                                                                                                                                                                                                                        if (_t2489) {
                                                                                                                                                                                                                                                            Str *_t2477 = Str_lit("continue", 8ULL);
                                                                                                                                                                                                                                                            (void)_t2477;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            return _t2477;
                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                            Bool _t2488; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwDefer()); _t2488 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                            (void)_t2488;
                                                                                                                                                                                                                                                            if (_t2488) {
                                                                                                                                                                                                                                                                Str *_t2478 = Str_lit("defer", 5ULL);
                                                                                                                                                                                                                                                                (void)_t2478;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                return _t2478;
                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                Bool _t2487; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwTrue()); _t2487 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                (void)_t2487;
                                                                                                                                                                                                                                                                if (_t2487) {
                                                                                                                                                                                                                                                                    Str *_t2479 = Str_lit("true", 4ULL);
                                                                                                                                                                                                                                                                    (void)_t2479;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t2479;
                                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                                    Bool _t2486; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwFalse()); _t2486 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                    (void)_t2486;
                                                                                                                                                                                                                                                                    if (_t2486) {
                                                                                                                                                                                                                                                                        Str *_t2480 = Str_lit("false", 5ULL);
                                                                                                                                                                                                                                                                        (void)_t2480;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        return _t2480;
                                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                                        Bool _t2485; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_KwNull()); _t2485 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                        (void)_t2485;
                                                                                                                                                                                                                                                                        if (_t2485) {
                                                                                                                                                                                                                                                                            Str *_t2481 = Str_lit("NULL", 4ULL);
                                                                                                                                                                                                                                                                            (void)_t2481;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            return _t2481;
                                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                                            Bool _t2484; { Bool *_hp = (Bool *)TokenType_eq(_sw2416, TokenType_Error()); _t2484 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                            (void)_t2484;
                                                                                                                                                                                                                                                                            if (_t2484) {
                                                                                                                                                                                                                                                                                Str *_t2482 = Str_lit("error", 5ULL);
                                                                                                                                                                                                                                                                                (void)_t2482;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t2482;
                                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                                Str *_t2483 = Str_lit("?", 1ULL);
                                                                                                                                                                                                                                                                                (void)_t2483;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                TokenType_delete(_sw2416, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t2483;
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
        TokenType_delete(_sw2416, &(Bool){1});
        ;
    }
}

TokenType * lookup_keyword(Str * word) {
    (void)word;
    {
        Str *_sw2550 = Str_clone(word);
        (void)_sw2550;
        Str *_t2619 = Str_lit("mode", 4ULL);
        (void)_t2619;
        Bool _t2620; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2619); _t2620 = *_hp; free(_hp); }
        (void)_t2620;
        Str_delete(_t2619, &(Bool){1});
        if (_t2620) {
            Str_delete(_sw2550, &(Bool){1});
            ;
            return TokenType_KwMode();
        } else {
            Str *_t2617 = Str_lit("mut", 3ULL);
            (void)_t2617;
            Bool _t2618; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2617); _t2618 = *_hp; free(_hp); }
            (void)_t2618;
            Str_delete(_t2617, &(Bool){1});
            if (_t2618) {
                ;
                Str_delete(_sw2550, &(Bool){1});
                ;
                return TokenType_KwMut();
            } else {
                Str *_t2615 = Str_lit("own", 3ULL);
                (void)_t2615;
                Bool _t2616; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2615); _t2616 = *_hp; free(_hp); }
                (void)_t2616;
                Str_delete(_t2615, &(Bool){1});
                if (_t2616) {
                    ;
                    ;
                    Str_delete(_sw2550, &(Bool){1});
                    ;
                    return TokenType_KwOwn();
                } else {
                    Str *_t2613 = Str_lit("ref", 3ULL);
                    (void)_t2613;
                    Bool _t2614; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2613); _t2614 = *_hp; free(_hp); }
                    (void)_t2614;
                    Str_delete(_t2613, &(Bool){1});
                    if (_t2614) {
                        ;
                        ;
                        ;
                        Str_delete(_sw2550, &(Bool){1});
                        ;
                        return TokenType_KwRef();
                    } else {
                        Str *_t2611 = Str_lit("shallow", 7ULL);
                        (void)_t2611;
                        Bool _t2612; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2611); _t2612 = *_hp; free(_hp); }
                        (void)_t2612;
                        Str_delete(_t2611, &(Bool){1});
                        if (_t2612) {
                            ;
                            ;
                            ;
                            ;
                            Str_delete(_sw2550, &(Bool){1});
                            ;
                            return TokenType_KwShallow();
                        } else {
                            Str *_t2609 = Str_lit("struct", 6ULL);
                            (void)_t2609;
                            Bool _t2610; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2609); _t2610 = *_hp; free(_hp); }
                            (void)_t2610;
                            Str_delete(_t2609, &(Bool){1});
                            if (_t2610) {
                                ;
                                ;
                                ;
                                ;
                                ;
                                Str_delete(_sw2550, &(Bool){1});
                                ;
                                return TokenType_KwStruct();
                            } else {
                                Str *_t2607 = Str_lit("ext_struct", 10ULL);
                                (void)_t2607;
                                Bool _t2608; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2607); _t2608 = *_hp; free(_hp); }
                                (void)_t2608;
                                Str_delete(_t2607, &(Bool){1});
                                if (_t2608) {
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    Str_delete(_sw2550, &(Bool){1});
                                    ;
                                    return TokenType_KwExtStruct();
                                } else {
                                    Str *_t2605 = Str_lit("enum", 4ULL);
                                    (void)_t2605;
                                    Bool _t2606; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2605); _t2606 = *_hp; free(_hp); }
                                    (void)_t2606;
                                    Str_delete(_t2605, &(Bool){1});
                                    if (_t2606) {
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        Str_delete(_sw2550, &(Bool){1});
                                        ;
                                        return TokenType_KwEnum();
                                    } else {
                                        Str *_t2603 = Str_lit("namespace", 9ULL);
                                        (void)_t2603;
                                        Bool _t2604; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2603); _t2604 = *_hp; free(_hp); }
                                        (void)_t2604;
                                        Str_delete(_t2603, &(Bool){1});
                                        if (_t2604) {
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            Str_delete(_sw2550, &(Bool){1});
                                            ;
                                            return TokenType_KwNamespace();
                                        } else {
                                            Str *_t2601 = Str_lit("func", 4ULL);
                                            (void)_t2601;
                                            Bool _t2602; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2601); _t2602 = *_hp; free(_hp); }
                                            (void)_t2602;
                                            Str_delete(_t2601, &(Bool){1});
                                            if (_t2602) {
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                Str_delete(_sw2550, &(Bool){1});
                                                ;
                                                return TokenType_KwFunc();
                                            } else {
                                                Str *_t2599 = Str_lit("proc", 4ULL);
                                                (void)_t2599;
                                                Bool _t2600; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2599); _t2600 = *_hp; free(_hp); }
                                                (void)_t2600;
                                                Str_delete(_t2599, &(Bool){1});
                                                if (_t2600) {
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    Str_delete(_sw2550, &(Bool){1});
                                                    ;
                                                    return TokenType_KwProc();
                                                } else {
                                                    Str *_t2597 = Str_lit("test", 4ULL);
                                                    (void)_t2597;
                                                    Bool _t2598; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2597); _t2598 = *_hp; free(_hp); }
                                                    (void)_t2598;
                                                    Str_delete(_t2597, &(Bool){1});
                                                    if (_t2598) {
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        Str_delete(_sw2550, &(Bool){1});
                                                        ;
                                                        return TokenType_KwTest();
                                                    } else {
                                                        Str *_t2595 = Str_lit("macro", 5ULL);
                                                        (void)_t2595;
                                                        Bool _t2596; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2595); _t2596 = *_hp; free(_hp); }
                                                        (void)_t2596;
                                                        Str_delete(_t2595, &(Bool){1});
                                                        if (_t2596) {
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            Str_delete(_sw2550, &(Bool){1});
                                                            ;
                                                            return TokenType_KwMacro();
                                                        } else {
                                                            Str *_t2593 = Str_lit("ext_func", 8ULL);
                                                            (void)_t2593;
                                                            Bool _t2594; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2593); _t2594 = *_hp; free(_hp); }
                                                            (void)_t2594;
                                                            Str_delete(_t2593, &(Bool){1});
                                                            if (_t2594) {
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                Str_delete(_sw2550, &(Bool){1});
                                                                ;
                                                                return TokenType_KwExtFunc();
                                                            } else {
                                                                Str *_t2591 = Str_lit("ext_proc", 8ULL);
                                                                (void)_t2591;
                                                                Bool _t2592; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2591); _t2592 = *_hp; free(_hp); }
                                                                (void)_t2592;
                                                                Str_delete(_t2591, &(Bool){1});
                                                                if (_t2592) {
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    Str_delete(_sw2550, &(Bool){1});
                                                                    ;
                                                                    return TokenType_KwExtProc();
                                                                } else {
                                                                    Str *_t2589 = Str_lit("returns", 7ULL);
                                                                    (void)_t2589;
                                                                    Bool _t2590; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2589); _t2590 = *_hp; free(_hp); }
                                                                    (void)_t2590;
                                                                    Str_delete(_t2589, &(Bool){1});
                                                                    if (_t2590) {
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        Str_delete(_sw2550, &(Bool){1});
                                                                        ;
                                                                        return TokenType_KwReturns();
                                                                    } else {
                                                                        Str *_t2587 = Str_lit("throws", 6ULL);
                                                                        (void)_t2587;
                                                                        Bool _t2588; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2587); _t2588 = *_hp; free(_hp); }
                                                                        (void)_t2588;
                                                                        Str_delete(_t2587, &(Bool){1});
                                                                        if (_t2588) {
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            Str_delete(_sw2550, &(Bool){1});
                                                                            ;
                                                                            return TokenType_KwThrows();
                                                                        } else {
                                                                            Str *_t2585 = Str_lit("if", 2ULL);
                                                                            (void)_t2585;
                                                                            Bool _t2586; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2585); _t2586 = *_hp; free(_hp); }
                                                                            (void)_t2586;
                                                                            Str_delete(_t2585, &(Bool){1});
                                                                            if (_t2586) {
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                Str_delete(_sw2550, &(Bool){1});
                                                                                ;
                                                                                return TokenType_KwIf();
                                                                            } else {
                                                                                Str *_t2583 = Str_lit("else", 4ULL);
                                                                                (void)_t2583;
                                                                                Bool _t2584; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2583); _t2584 = *_hp; free(_hp); }
                                                                                (void)_t2584;
                                                                                Str_delete(_t2583, &(Bool){1});
                                                                                if (_t2584) {
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    Str_delete(_sw2550, &(Bool){1});
                                                                                    ;
                                                                                    return TokenType_KwElse();
                                                                                } else {
                                                                                    Str *_t2581 = Str_lit("while", 5ULL);
                                                                                    (void)_t2581;
                                                                                    Bool _t2582; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2581); _t2582 = *_hp; free(_hp); }
                                                                                    (void)_t2582;
                                                                                    Str_delete(_t2581, &(Bool){1});
                                                                                    if (_t2582) {
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        Str_delete(_sw2550, &(Bool){1});
                                                                                        ;
                                                                                        return TokenType_KwWhile();
                                                                                    } else {
                                                                                        Str *_t2579 = Str_lit("for", 3ULL);
                                                                                        (void)_t2579;
                                                                                        Bool _t2580; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2579); _t2580 = *_hp; free(_hp); }
                                                                                        (void)_t2580;
                                                                                        Str_delete(_t2579, &(Bool){1});
                                                                                        if (_t2580) {
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            Str_delete(_sw2550, &(Bool){1});
                                                                                            ;
                                                                                            return TokenType_KwFor();
                                                                                        } else {
                                                                                            Str *_t2577 = Str_lit("in", 2ULL);
                                                                                            (void)_t2577;
                                                                                            Bool _t2578; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2577); _t2578 = *_hp; free(_hp); }
                                                                                            (void)_t2578;
                                                                                            Str_delete(_t2577, &(Bool){1});
                                                                                            if (_t2578) {
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                Str_delete(_sw2550, &(Bool){1});
                                                                                                ;
                                                                                                return TokenType_KwIn();
                                                                                            } else {
                                                                                                Str *_t2575 = Str_lit("switch", 6ULL);
                                                                                                (void)_t2575;
                                                                                                Bool _t2576; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2575); _t2576 = *_hp; free(_hp); }
                                                                                                (void)_t2576;
                                                                                                Str_delete(_t2575, &(Bool){1});
                                                                                                if (_t2576) {
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    Str_delete(_sw2550, &(Bool){1});
                                                                                                    ;
                                                                                                    return TokenType_KwSwitch();
                                                                                                } else {
                                                                                                    Str *_t2573 = Str_lit("match", 5ULL);
                                                                                                    (void)_t2573;
                                                                                                    Bool _t2574; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2573); _t2574 = *_hp; free(_hp); }
                                                                                                    (void)_t2574;
                                                                                                    Str_delete(_t2573, &(Bool){1});
                                                                                                    if (_t2574) {
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        Str_delete(_sw2550, &(Bool){1});
                                                                                                        ;
                                                                                                        return TokenType_KwMatch();
                                                                                                    } else {
                                                                                                        Str *_t2571 = Str_lit("case", 4ULL);
                                                                                                        (void)_t2571;
                                                                                                        Bool _t2572; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2571); _t2572 = *_hp; free(_hp); }
                                                                                                        (void)_t2572;
                                                                                                        Str_delete(_t2571, &(Bool){1});
                                                                                                        if (_t2572) {
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            Str_delete(_sw2550, &(Bool){1});
                                                                                                            ;
                                                                                                            return TokenType_KwCase();
                                                                                                        } else {
                                                                                                            Str *_t2569 = Str_lit("default", 7ULL);
                                                                                                            (void)_t2569;
                                                                                                            Bool _t2570; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2569); _t2570 = *_hp; free(_hp); }
                                                                                                            (void)_t2570;
                                                                                                            Str_delete(_t2569, &(Bool){1});
                                                                                                            if (_t2570) {
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                Str_delete(_sw2550, &(Bool){1});
                                                                                                                ;
                                                                                                                return TokenType_KwDefault();
                                                                                                            } else {
                                                                                                                Str *_t2567 = Str_lit("return", 6ULL);
                                                                                                                (void)_t2567;
                                                                                                                Bool _t2568; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2567); _t2568 = *_hp; free(_hp); }
                                                                                                                (void)_t2568;
                                                                                                                Str_delete(_t2567, &(Bool){1});
                                                                                                                if (_t2568) {
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    Str_delete(_sw2550, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return TokenType_KwReturn();
                                                                                                                } else {
                                                                                                                    Str *_t2565 = Str_lit("throw", 5ULL);
                                                                                                                    (void)_t2565;
                                                                                                                    Bool _t2566; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2565); _t2566 = *_hp; free(_hp); }
                                                                                                                    (void)_t2566;
                                                                                                                    Str_delete(_t2565, &(Bool){1});
                                                                                                                    if (_t2566) {
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        Str_delete(_sw2550, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return TokenType_KwThrow();
                                                                                                                    } else {
                                                                                                                        Str *_t2563 = Str_lit("catch", 5ULL);
                                                                                                                        (void)_t2563;
                                                                                                                        Bool _t2564; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2563); _t2564 = *_hp; free(_hp); }
                                                                                                                        (void)_t2564;
                                                                                                                        Str_delete(_t2563, &(Bool){1});
                                                                                                                        if (_t2564) {
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            Str_delete(_sw2550, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return TokenType_KwCatch();
                                                                                                                        } else {
                                                                                                                            Str *_t2561 = Str_lit("break", 5ULL);
                                                                                                                            (void)_t2561;
                                                                                                                            Bool _t2562; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2561); _t2562 = *_hp; free(_hp); }
                                                                                                                            (void)_t2562;
                                                                                                                            Str_delete(_t2561, &(Bool){1});
                                                                                                                            if (_t2562) {
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                Str_delete(_sw2550, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return TokenType_KwBreak();
                                                                                                                            } else {
                                                                                                                                Str *_t2559 = Str_lit("continue", 8ULL);
                                                                                                                                (void)_t2559;
                                                                                                                                Bool _t2560; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2559); _t2560 = *_hp; free(_hp); }
                                                                                                                                (void)_t2560;
                                                                                                                                Str_delete(_t2559, &(Bool){1});
                                                                                                                                if (_t2560) {
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    Str_delete(_sw2550, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return TokenType_KwContinue();
                                                                                                                                } else {
                                                                                                                                    Str *_t2557 = Str_lit("defer", 5ULL);
                                                                                                                                    (void)_t2557;
                                                                                                                                    Bool _t2558; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2557); _t2558 = *_hp; free(_hp); }
                                                                                                                                    (void)_t2558;
                                                                                                                                    Str_delete(_t2557, &(Bool){1});
                                                                                                                                    if (_t2558) {
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        Str_delete(_sw2550, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return TokenType_KwDefer();
                                                                                                                                    } else {
                                                                                                                                        Str *_t2555 = Str_lit("true", 4ULL);
                                                                                                                                        (void)_t2555;
                                                                                                                                        Bool _t2556; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2555); _t2556 = *_hp; free(_hp); }
                                                                                                                                        (void)_t2556;
                                                                                                                                        Str_delete(_t2555, &(Bool){1});
                                                                                                                                        if (_t2556) {
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            Str_delete(_sw2550, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return TokenType_KwTrue();
                                                                                                                                        } else {
                                                                                                                                            Str *_t2553 = Str_lit("false", 5ULL);
                                                                                                                                            (void)_t2553;
                                                                                                                                            Bool _t2554; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2553); _t2554 = *_hp; free(_hp); }
                                                                                                                                            (void)_t2554;
                                                                                                                                            Str_delete(_t2553, &(Bool){1});
                                                                                                                                            if (_t2554) {
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                Str_delete(_sw2550, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return TokenType_KwFalse();
                                                                                                                                            } else {
                                                                                                                                                Str *_t2551 = Str_lit("NULL", 4ULL);
                                                                                                                                                (void)_t2551;
                                                                                                                                                Bool _t2552; { Bool *_hp = (Bool *)Str_eq(_sw2550, _t2551); _t2552 = *_hp; free(_hp); }
                                                                                                                                                (void)_t2552;
                                                                                                                                                Str_delete(_t2551, &(Bool){1});
                                                                                                                                                if (_t2552) {
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    Str_delete(_sw2550, &(Bool){1});
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
                                                                                                                                                    Str_delete(_sw2550, &(Bool){1});
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
        Str_delete(_sw2550, &(Bool){1});
        ;
    }
}

Vec * tokenize(Str * src, Str * path) {
    (void)src;
    (void)path;
    Str *_t2960 = Str_lit("Token", 5ULL);
    (void)_t2960;
    U64 _t2961; { U64 *_hp = (U64 *)Token_size(); _t2961 = *_hp; free(_hp); }
    (void)_t2961;
    Vec *tokens = Vec_new(_t2960, &(U64){_t2961});
    (void)tokens;
    Str_delete(_t2960, &(Bool){1});
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
        Bool _wcond2621; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2621 = *_hp; free(_hp); }
        (void)_wcond2621;
        if (_wcond2621) {
        } else {
            ;
            break;
        }
        ;
        U8 *c = Str_byte_at(src, pos);
        (void)c;
        U8 _t2905 = 32;
        (void)_t2905;
        U8 _t2906 = 9;
        (void)_t2906;
        Bool _t2907 = U8_eq(DEREF(c), _t2905);
        (void)_t2907;
        ;
        Bool _t2908 = U8_eq(DEREF(c), _t2906);
        (void)_t2908;
        ;
        U8 _t2909 = 13;
        (void)_t2909;
        Bool _t2910 = Bool_or(_t2907, _t2908);
        (void)_t2910;
        ;
        ;
        Bool _t2911 = U8_eq(DEREF(c), _t2909);
        (void)_t2911;
        ;
        U8 _t2912 = 59;
        (void)_t2912;
        Bool _t2913 = Bool_or(_t2910, _t2911);
        (void)_t2913;
        ;
        ;
        Bool _t2914 = U8_eq(DEREF(c), _t2912);
        (void)_t2914;
        ;
        Bool _t2915 = Bool_or(_t2913, _t2914);
        (void)_t2915;
        ;
        ;
        if (_t2915) {
            U64_inc(pos);
            ;
            continue;
        }
        ;
        U8 _t2916 = 10;
        (void)_t2916;
        Bool _t2917 = U8_eq(DEREF(c), _t2916);
        (void)_t2917;
        ;
        if (_t2917) {
            U64_inc(pos);
            U32 _t2622 = 1;
            (void)_t2622;
            U32 _t2623 = U32_add(line, _t2622);
            (void)_t2623;
            ;
            line = _t2623;
            ;
            U64 _t2624 = U64_clone(pos);
            (void)_t2624;
            line_start = _t2624;
            ;
            ;
            continue;
        }
        ;
        U64 _t2918 = U64_sub(DEREF(pos), line_start);
        (void)_t2918;
        U64 _t2919 = 1;
        (void)_t2919;
        U64 _t2920 = U64_add(_t2918, _t2919);
        (void)_t2920;
        ;
        ;
        I64 _t2921 = U64_to_i64(_t2920);
        (void)_t2921;
        ;
        U32 col = I64_to_u32(_t2921);
        (void)col;
        ;
        U64 start = U64_clone(pos);
        (void)start;
        U8 _t2922 = 35;
        (void)_t2922;
        Bool _t2923 = U8_eq(DEREF(c), _t2922);
        (void)_t2923;
        ;
        if (_t2923) {
            while (1) {
                Bool _wcond2625; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2625 = *_hp; free(_hp); }
                (void)_wcond2625;
                if (_wcond2625) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2626 = Str_byte_at(src, pos);
                (void)_t2626;
                U8 _t2627 = 10;
                (void)_t2627;
                Bool _t2628 = U8_eq(DEREF(_t2626), _t2627);
                (void)_t2628;
                ;
                if (_t2628) {
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
        U8 _t2924 = 47;
        (void)_t2924;
        U64 _t2925 = 1;
        (void)_t2925;
        U64 _t2926 = U64_add(DEREF(pos), _t2925);
        (void)_t2926;
        ;
        Bool _t2927 = U8_eq(DEREF(c), _t2924);
        (void)_t2927;
        ;
        Bool _t2928; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2926}, &(U64){src_len}); _t2928 = *_hp; free(_hp); }
        (void)_t2928;
        ;
        Bool _t2929 = Bool_and(_t2927, _t2928);
        (void)_t2929;
        ;
        ;
        if (_t2929) {
            U64 _t2685 = 1;
            (void)_t2685;
            U64 *_t2686 = malloc(sizeof(U64)); *_t2686 = U64_add(DEREF(pos), _t2685);
            (void)_t2686;
            ;
            U8 *c2 = Str_byte_at(src, _t2686);
            (void)c2;
            U8 _t2687 = 47;
            (void)_t2687;
            Bool _t2688 = U8_eq(DEREF(c2), _t2687);
            (void)_t2688;
            ;
            if (_t2688) {
                while (1) {
                    Bool _wcond2629; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2629 = *_hp; free(_hp); }
                    (void)_wcond2629;
                    if (_wcond2629) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U8 *_t2630 = Str_byte_at(src, pos);
                    (void)_t2630;
                    U8 _t2631 = 10;
                    (void)_t2631;
                    Bool _t2632 = U8_eq(DEREF(_t2630), _t2631);
                    (void)_t2632;
                    ;
                    if (_t2632) {
                        ;
                        break;
                    }
                    ;
                    U64_inc(pos);
                }
                U64_delete(_t2686, &(Bool){1});
                ;
                ;
                ;
                ;
                continue;
            }
            ;
            U8 _t2689 = 42;
            (void)_t2689;
            Bool _t2690 = U8_eq(DEREF(c2), _t2689);
            (void)_t2690;
            U64_delete(_t2686, &(Bool){1});
            ;
            if (_t2690) {
                U64 _t2681 = 2;
                (void)_t2681;
                U64 _t2682 = U64_add(DEREF(pos), _t2681);
                (void)_t2682;
                ;
                *pos = _t2682;
                ;
                I64 depth = 1;
                (void)depth;
                while (1) {
                    Bool _wcond2633; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2633 = *_hp; free(_hp); }
                    (void)_wcond2633;
                    if (_wcond2633) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    I64 _t2658 = 0;
                    (void)_t2658;
                    Bool _t2659; { Bool *_hp = (Bool *)I64_lte(&(I64){depth}, &(I64){_t2658}); _t2659 = *_hp; free(_hp); }
                    (void)_t2659;
                    ;
                    if (_t2659) {
                        ;
                        break;
                    }
                    ;
                    U64 _t2660 = 1;
                    (void)_t2660;
                    U64 _t2661 = U64_add(DEREF(pos), _t2660);
                    (void)_t2661;
                    ;
                    Bool _t2662; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2661}, &(U64){src_len}); _t2662 = *_hp; free(_hp); }
                    (void)_t2662;
                    ;
                    if (_t2662) {
                        U8 *b1 = Str_byte_at(src, pos);
                        (void)b1;
                        U64 _t2642 = 1;
                        (void)_t2642;
                        U64 *_t2643 = malloc(sizeof(U64)); *_t2643 = U64_add(DEREF(pos), _t2642);
                        (void)_t2643;
                        ;
                        U8 *b2 = Str_byte_at(src, _t2643);
                        (void)b2;
                        U8 _t2644 = 47;
                        (void)_t2644;
                        U8 _t2645 = 42;
                        (void)_t2645;
                        Bool _t2646 = U8_eq(DEREF(b1), _t2644);
                        (void)_t2646;
                        ;
                        Bool _t2647 = U8_eq(DEREF(b2), _t2645);
                        (void)_t2647;
                        ;
                        Bool _t2648 = Bool_and(_t2646, _t2647);
                        (void)_t2648;
                        ;
                        ;
                        if (_t2648) {
                            I64 _t2634 = 1;
                            (void)_t2634;
                            I64 _t2635 = I64_add(depth, _t2634);
                            (void)_t2635;
                            ;
                            depth = _t2635;
                            ;
                            U64 _t2636 = 2;
                            (void)_t2636;
                            U64 _t2637 = U64_add(DEREF(pos), _t2636);
                            (void)_t2637;
                            ;
                            *pos = _t2637;
                            ;
                            U64_delete(_t2643, &(Bool){1});
                            ;
                            ;
                            continue;
                        }
                        ;
                        U8 _t2649 = 42;
                        (void)_t2649;
                        U8 _t2650 = 47;
                        (void)_t2650;
                        Bool _t2651 = U8_eq(DEREF(b1), _t2649);
                        (void)_t2651;
                        ;
                        Bool _t2652 = U8_eq(DEREF(b2), _t2650);
                        (void)_t2652;
                        U64_delete(_t2643, &(Bool){1});
                        ;
                        Bool _t2653 = Bool_and(_t2651, _t2652);
                        (void)_t2653;
                        ;
                        ;
                        if (_t2653) {
                            I64 _t2638 = 1;
                            (void)_t2638;
                            I64 _t2639 = I64_sub(depth, _t2638);
                            (void)_t2639;
                            ;
                            depth = _t2639;
                            ;
                            U64 _t2640 = 2;
                            (void)_t2640;
                            U64 _t2641 = U64_add(DEREF(pos), _t2640);
                            (void)_t2641;
                            ;
                            *pos = _t2641;
                            ;
                            ;
                            ;
                            continue;
                        }
                        ;
                    }
                    ;
                    U8 *_t2663 = Str_byte_at(src, pos);
                    (void)_t2663;
                    U8 _t2664 = 10;
                    (void)_t2664;
                    Bool _t2665 = U8_eq(DEREF(_t2663), _t2664);
                    (void)_t2665;
                    ;
                    if (_t2665) {
                        U32 _t2654 = 1;
                        (void)_t2654;
                        U32 _t2655 = U32_add(line, _t2654);
                        (void)_t2655;
                        ;
                        line = _t2655;
                        ;
                        U64 _t2656 = 1;
                        (void)_t2656;
                        U64 _t2657 = U64_add(DEREF(pos), _t2656);
                        (void)_t2657;
                        ;
                        line_start = _t2657;
                        ;
                    }
                    ;
                    U64_inc(pos);
                }
                I64 _t2683 = 0;
                (void)_t2683;
                Bool _t2684; { Bool *_hp = (Bool *)I64_gt(&(I64){depth}, &(I64){_t2683}); _t2684 = *_hp; free(_hp); }
                (void)_t2684;
                ;
                ;
                if (_t2684) {
                    Str *_t2666 = Str_lit("Str", 3ULL);
                    (void)_t2666;
                    U64 _t2667; { U64 *_hp = (U64 *)Str_size(); _t2667 = *_hp; free(_hp); }
                    (void)_t2667;
                    U64 _t2668 = 6;
                    (void)_t2668;
                    Array *_va53 = Array_new(_t2666, &(U64){_t2667}, &(U64){_t2668});
                    (void)_va53;
                    Str_delete(_t2666, &(Bool){1});
                    ;
                    ;
                    U64 _t2669 = 0;
                    (void)_t2669;
                    Str *_t2670 = Str_clone(path);
                    (void)_t2670;
                    Array_set(_va53, &(U64){_t2669}, _t2670);
                    ;
                    U64 _t2671 = 1;
                    (void)_t2671;
                    Str *_t2672 = Str_lit(":", 1ULL);
                    (void)_t2672;
                    Array_set(_va53, &(U64){_t2671}, _t2672);
                    ;
                    U64 _t2673 = 2;
                    (void)_t2673;
                    Str *_t2674 = U32_to_str(&(U32){line});
                    (void)_t2674;
                    Array_set(_va53, &(U64){_t2673}, _t2674);
                    ;
                    U64 _t2675 = 3;
                    (void)_t2675;
                    Str *_t2676 = Str_lit(":", 1ULL);
                    (void)_t2676;
                    Array_set(_va53, &(U64){_t2675}, _t2676);
                    ;
                    U64 _t2677 = 4;
                    (void)_t2677;
                    Str *_t2678 = U32_to_str(&(U32){col});
                    (void)_t2678;
                    Array_set(_va53, &(U64){_t2677}, _t2678);
                    ;
                    U64 _t2679 = 5;
                    (void)_t2679;
                    Str *_t2680 = Str_lit(": error: unterminated comment", 29ULL);
                    (void)_t2680;
                    Array_set(_va53, &(U64){_t2679}, _t2680);
                    ;
                    println(_va53);
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
        Bool _t2930; { Bool *_hp = (Bool *)is_digit(c); _t2930 = *_hp; free(_hp); }
        (void)_t2930;
        if (_t2930) {
            while (1) {
                Bool _wcond2691; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2691 = *_hp; free(_hp); }
                (void)_wcond2691;
                if (_wcond2691) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2692 = Str_byte_at(src, pos);
                (void)_t2692;
                Bool _t2693; { Bool *_hp = (Bool *)is_digit(_t2692); _t2693 = *_hp; free(_hp); }
                (void)_t2693;
                Bool _t2694 = Bool_not(_t2693);
                (void)_t2694;
                ;
                if (_t2694) {
                    ;
                    break;
                }
                ;
                U64_inc(pos);
            }
            U64 _t2707 = 1;
            (void)_t2707;
            U64 _t2708 = U64_add(DEREF(pos), _t2707);
            (void)_t2708;
            ;
            Bool _t2709; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2708}, &(U64){src_len}); _t2709 = *_hp; free(_hp); }
            (void)_t2709;
            ;
            if (_t2709) {
                U8 *_t2699 = Str_byte_at(src, pos);
                (void)_t2699;
                U8 _t2700 = 46;
                (void)_t2700;
                U64 _t2701 = 1;
                (void)_t2701;
                U64 *_t2702 = malloc(sizeof(U64)); *_t2702 = U64_add(DEREF(pos), _t2701);
                (void)_t2702;
                ;
                U8 *_t2703 = Str_byte_at(src, _t2702);
                (void)_t2703;
                Bool _t2704 = U8_eq(DEREF(_t2699), _t2700);
                (void)_t2704;
                ;
                Bool _t2705; { Bool *_hp = (Bool *)is_digit(_t2703); _t2705 = *_hp; free(_hp); }
                (void)_t2705;
                U64_delete(_t2702, &(Bool){1});
                Bool _t2706 = Bool_and(_t2704, _t2705);
                (void)_t2706;
                ;
                ;
                if (_t2706) {
                    U64_inc(pos);
                    while (1) {
                        Bool _wcond2695; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2695 = *_hp; free(_hp); }
                        (void)_wcond2695;
                        if (_wcond2695) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U8 *_t2696 = Str_byte_at(src, pos);
                        (void)_t2696;
                        Bool _t2697; { Bool *_hp = (Bool *)is_digit(_t2696); _t2697 = *_hp; free(_hp); }
                        (void)_t2697;
                        Bool _t2698 = Bool_not(_t2697);
                        (void)_t2698;
                        ;
                        if (_t2698) {
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
            U64 _t2710 = U64_sub(DEREF(pos), start);
            (void)_t2710;
            Str *_t2711 = Str_substr(src, &(U64){start}, &(U64){_t2710});
            (void)_t2711;
            ;
            U32 _t2712 = U32_clone(&(U32){col});
            (void)_t2712;
            Token *_t2713 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(TokenType_Number()); _t2713->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(_t2711); _t2713->text = *_ca; free(_ca); }
            _t2713->line = U32_clone(&(U32){line});
            _t2713->col = _t2712;
            (void)_t2713;
            Str_delete(_t2711, &(Bool){1});
            ;
            Vec_push(tokens, _t2713);
            ;
            ;
            ;
            continue;
        }
        ;
        Bool _t2931; { Bool *_hp = (Bool *)is_alpha(c); _t2931 = *_hp; free(_hp); }
        (void)_t2931;
        if (_t2931) {
            while (1) {
                Bool _wcond2714; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2714 = *_hp; free(_hp); }
                (void)_wcond2714;
                if (_wcond2714) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2715 = Str_byte_at(src, pos);
                (void)_t2715;
                Bool _t2716; { Bool *_hp = (Bool *)is_alnum(_t2715); _t2716 = *_hp; free(_hp); }
                (void)_t2716;
                Bool _t2717 = Bool_not(_t2716);
                (void)_t2717;
                ;
                if (_t2717) {
                    ;
                    break;
                }
                ;
                U64_inc(pos);
            }
            U64 _t2718 = U64_sub(DEREF(pos), start);
            (void)_t2718;
            Str *word = Str_substr(src, &(U64){start}, &(U64){_t2718});
            (void)word;
            ;
            TokenType *type = lookup_keyword(word);
            (void)type;
            U32 _t2719 = U32_clone(&(U32){line});
            (void)_t2719;
            U32 _t2720 = U32_clone(&(U32){col});
            (void)_t2720;
            Token *_t2721 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(type); _t2721->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(word); _t2721->text = *_ca; free(_ca); }
            _t2721->line = _t2719;
            _t2721->col = _t2720;
            (void)_t2721;
            ;
            ;
            TokenType_delete(type, &(Bool){1});
            Str_delete(word, &(Bool){1});
            Vec_push(tokens, _t2721);
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t2932 = 34;
        (void)_t2932;
        Bool _t2933 = U8_eq(DEREF(c), _t2932);
        (void)_t2933;
        ;
        if (_t2933) {
            U64_inc(pos);
            while (1) {
                Bool _wcond2722; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2722 = *_hp; free(_hp); }
                (void)_wcond2722;
                if (_wcond2722) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2727 = Str_byte_at(src, pos);
                (void)_t2727;
                U8 _t2728 = 34;
                (void)_t2728;
                Bool _t2729 = U8_eq(DEREF(_t2727), _t2728);
                (void)_t2729;
                ;
                if (_t2729) {
                    ;
                    break;
                }
                ;
                U8 *_t2730 = Str_byte_at(src, pos);
                (void)_t2730;
                U8 _t2731 = 92;
                (void)_t2731;
                U64 _t2732 = 1;
                (void)_t2732;
                U64 _t2733 = U64_add(DEREF(pos), _t2732);
                (void)_t2733;
                ;
                Bool _t2734 = U8_eq(DEREF(_t2730), _t2731);
                (void)_t2734;
                ;
                Bool _t2735; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2733}, &(U64){src_len}); _t2735 = *_hp; free(_hp); }
                (void)_t2735;
                ;
                Bool _t2736 = Bool_and(_t2734, _t2735);
                (void)_t2736;
                ;
                ;
                if (_t2736) {
                    U64_inc(pos);
                }
                ;
                U8 *_t2737 = Str_byte_at(src, pos);
                (void)_t2737;
                U8 _t2738 = 10;
                (void)_t2738;
                Bool _t2739 = U8_eq(DEREF(_t2737), _t2738);
                (void)_t2739;
                ;
                if (_t2739) {
                    U32 _t2723 = 1;
                    (void)_t2723;
                    U32 _t2724 = U32_add(line, _t2723);
                    (void)_t2724;
                    ;
                    line = _t2724;
                    ;
                    U64 _t2725 = 1;
                    (void)_t2725;
                    U64 _t2726 = U64_add(DEREF(pos), _t2725);
                    (void)_t2726;
                    ;
                    line_start = _t2726;
                    ;
                }
                ;
                U64_inc(pos);
            }
            U8 *_t2767 = Str_byte_at(src, pos);
            (void)_t2767;
            U8 _t2768 = 34;
            (void)_t2768;
            Bool _t2769; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2769 = *_hp; free(_hp); }
            (void)_t2769;
            Bool _t2770 = U8_eq(DEREF(_t2767), _t2768);
            (void)_t2770;
            ;
            Bool _t2771 = Bool_and(_t2769, _t2770);
            (void)_t2771;
            ;
            ;
            if (_t2771) {
                U64_inc(pos);
                U64 _t2740 = 1;
                (void)_t2740;
                U64 _t2741 = U64_sub(DEREF(pos), start);
                (void)_t2741;
                U64 _t2742 = 2;
                (void)_t2742;
                U64 _t2743 = U64_add(start, _t2740);
                (void)_t2743;
                ;
                U64 _t2744 = U64_sub(_t2741, _t2742);
                (void)_t2744;
                ;
                ;
                Str *_t2745 = Str_substr(src, &(U64){_t2743}, &(U64){_t2744});
                (void)_t2745;
                ;
                ;
                U32 _t2746 = U32_clone(&(U32){col});
                (void)_t2746;
                Token *_t2747 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_StringTok()); _t2747->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2745); _t2747->text = *_ca; free(_ca); }
                _t2747->line = U32_clone(&(U32){line});
                _t2747->col = _t2746;
                (void)_t2747;
                Str_delete(_t2745, &(Bool){1});
                ;
                Vec_push(tokens, _t2747);
            } else {
                Str *_t2748 = Str_lit("Str", 3ULL);
                (void)_t2748;
                U64 _t2749; { U64 *_hp = (U64 *)Str_size(); _t2749 = *_hp; free(_hp); }
                (void)_t2749;
                U64 _t2750 = 6;
                (void)_t2750;
                Array *_va54 = Array_new(_t2748, &(U64){_t2749}, &(U64){_t2750});
                (void)_va54;
                Str_delete(_t2748, &(Bool){1});
                ;
                ;
                U64 _t2751 = 0;
                (void)_t2751;
                Str *_t2752 = Str_clone(path);
                (void)_t2752;
                Array_set(_va54, &(U64){_t2751}, _t2752);
                ;
                U64 _t2753 = 1;
                (void)_t2753;
                Str *_t2754 = Str_lit(":", 1ULL);
                (void)_t2754;
                Array_set(_va54, &(U64){_t2753}, _t2754);
                ;
                U64 _t2755 = 2;
                (void)_t2755;
                Str *_t2756 = U32_to_str(&(U32){line});
                (void)_t2756;
                Array_set(_va54, &(U64){_t2755}, _t2756);
                ;
                U64 _t2757 = 3;
                (void)_t2757;
                Str *_t2758 = Str_lit(":", 1ULL);
                (void)_t2758;
                Array_set(_va54, &(U64){_t2757}, _t2758);
                ;
                U64 _t2759 = 4;
                (void)_t2759;
                Str *_t2760 = U32_to_str(&(U32){col});
                (void)_t2760;
                Array_set(_va54, &(U64){_t2759}, _t2760);
                ;
                U64 _t2761 = 5;
                (void)_t2761;
                Str *_t2762 = Str_lit(": error: unterminated string", 28ULL);
                (void)_t2762;
                Array_set(_va54, &(U64){_t2761}, _t2762);
                ;
                println(_va54);
                U64 _t2763 = U64_sub(DEREF(pos), start);
                (void)_t2763;
                Str *_t2764 = Str_substr(src, &(U64){start}, &(U64){_t2763});
                (void)_t2764;
                ;
                U32 _t2765 = U32_clone(&(U32){col});
                (void)_t2765;
                Token *_t2766 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2766->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2764); _t2766->text = *_ca; free(_ca); }
                _t2766->line = U32_clone(&(U32){line});
                _t2766->col = _t2765;
                (void)_t2766;
                Str_delete(_t2764, &(Bool){1});
                ;
                Vec_push(tokens, _t2766);
            }
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t2934 = 39;
        (void)_t2934;
        Bool _t2935 = U8_eq(DEREF(c), _t2934);
        (void)_t2935;
        ;
        if (_t2935) {
            U64_inc(pos);
            U64 ch_start = U64_clone(pos);
            (void)ch_start;
            U8 *_t2795 = Str_byte_at(src, pos);
            (void)_t2795;
            U8 _t2796 = 92;
            (void)_t2796;
            U64 _t2797 = 1;
            (void)_t2797;
            U64 _t2798 = U64_add(DEREF(pos), _t2797);
            (void)_t2798;
            ;
            Bool _t2799 = U8_eq(DEREF(_t2795), _t2796);
            (void)_t2799;
            ;
            Bool _t2800; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2798}, &(U64){src_len}); _t2800 = *_hp; free(_hp); }
            (void)_t2800;
            ;
            Bool _t2801; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2801 = *_hp; free(_hp); }
            (void)_t2801;
            Bool _t2802 = Bool_and(_t2799, _t2800);
            (void)_t2802;
            ;
            ;
            Bool _t2803 = Bool_and(_t2801, _t2802);
            (void)_t2803;
            ;
            ;
            if (_t2803) {
                U64_inc(pos);
            }
            ;
            U64_inc(pos);
            U8 *_t2804 = Str_byte_at(src, pos);
            (void)_t2804;
            U8 _t2805 = 39;
            (void)_t2805;
            Bool _t2806; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2806 = *_hp; free(_hp); }
            (void)_t2806;
            Bool _t2807 = U8_eq(DEREF(_t2804), _t2805);
            (void)_t2807;
            ;
            Bool _t2808 = Bool_and(_t2806, _t2807);
            (void)_t2808;
            ;
            ;
            if (_t2808) {
                U64 _t2772 = U64_sub(DEREF(pos), ch_start);
                (void)_t2772;
                Str *_t2773 = Str_substr(src, &(U64){ch_start}, &(U64){_t2772});
                (void)_t2773;
                ;
                U32 _t2774 = U32_clone(&(U32){col});
                (void)_t2774;
                Token *_t2775 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Char()); _t2775->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2773); _t2775->text = *_ca; free(_ca); }
                _t2775->line = U32_clone(&(U32){line});
                _t2775->col = _t2774;
                (void)_t2775;
                Str_delete(_t2773, &(Bool){1});
                ;
                Vec_push(tokens, _t2775);
                U64_inc(pos);
            } else {
                Str *_t2776 = Str_lit("Str", 3ULL);
                (void)_t2776;
                U64 _t2777; { U64 *_hp = (U64 *)Str_size(); _t2777 = *_hp; free(_hp); }
                (void)_t2777;
                U64 _t2778 = 6;
                (void)_t2778;
                Array *_va55 = Array_new(_t2776, &(U64){_t2777}, &(U64){_t2778});
                (void)_va55;
                Str_delete(_t2776, &(Bool){1});
                ;
                ;
                U64 _t2779 = 0;
                (void)_t2779;
                Str *_t2780 = Str_clone(path);
                (void)_t2780;
                Array_set(_va55, &(U64){_t2779}, _t2780);
                ;
                U64 _t2781 = 1;
                (void)_t2781;
                Str *_t2782 = Str_lit(":", 1ULL);
                (void)_t2782;
                Array_set(_va55, &(U64){_t2781}, _t2782);
                ;
                U64 _t2783 = 2;
                (void)_t2783;
                Str *_t2784 = U32_to_str(&(U32){line});
                (void)_t2784;
                Array_set(_va55, &(U64){_t2783}, _t2784);
                ;
                U64 _t2785 = 3;
                (void)_t2785;
                Str *_t2786 = Str_lit(":", 1ULL);
                (void)_t2786;
                Array_set(_va55, &(U64){_t2785}, _t2786);
                ;
                U64 _t2787 = 4;
                (void)_t2787;
                Str *_t2788 = U32_to_str(&(U32){col});
                (void)_t2788;
                Array_set(_va55, &(U64){_t2787}, _t2788);
                ;
                U64 _t2789 = 5;
                (void)_t2789;
                Str *_t2790 = Str_lit(": error: unterminated character literal", 39ULL);
                (void)_t2790;
                Array_set(_va55, &(U64){_t2789}, _t2790);
                ;
                println(_va55);
                U64 _t2791 = U64_sub(DEREF(pos), start);
                (void)_t2791;
                Str *_t2792 = Str_substr(src, &(U64){start}, &(U64){_t2791});
                (void)_t2792;
                ;
                U32 _t2793 = U32_clone(&(U32){col});
                (void)_t2793;
                Token *_t2794 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2794->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2792); _t2794->text = *_ca; free(_ca); }
                _t2794->line = U32_clone(&(U32){line});
                _t2794->col = _t2793;
                (void)_t2794;
                Str_delete(_t2792, &(Bool){1});
                ;
                Vec_push(tokens, _t2794);
            }
            ;
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U64 _t2936 = 1;
        (void)_t2936;
        U64 _t2937 = U64_add(DEREF(pos), _t2936);
        (void)_t2937;
        ;
        Bool _t2938; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2937}, &(U64){src_len}); _t2938 = *_hp; free(_hp); }
        (void)_t2938;
        ;
        if (_t2938) {
            U64 _t2854 = 1;
            (void)_t2854;
            U64 *_t2855 = malloc(sizeof(U64)); *_t2855 = U64_add(DEREF(pos), _t2854);
            (void)_t2855;
            ;
            U8 *c2 = Str_byte_at(src, _t2855);
            (void)c2;
            TokenType *two = TokenType_clone(TokenType_Eof());
            (void)two;
            U8 _t2856 = 58;
            (void)_t2856;
            U8 _t2857 = 61;
            (void)_t2857;
            Bool _t2858 = U8_eq(DEREF(c), _t2856);
            (void)_t2858;
            ;
            Bool _t2859 = U8_eq(DEREF(c2), _t2857);
            (void)_t2859;
            ;
            Bool _t2860 = Bool_and(_t2858, _t2859);
            (void)_t2860;
            ;
            ;
            if (_t2860) {
                two = TokenType_clone(TokenType_ColonEq());
            } else {
                U8 _t2842 = 61;
                (void)_t2842;
                U8 _t2843 = 61;
                (void)_t2843;
                Bool _t2844 = U8_eq(DEREF(c), _t2842);
                (void)_t2844;
                ;
                Bool _t2845 = U8_eq(DEREF(c2), _t2843);
                (void)_t2845;
                ;
                Bool _t2846 = Bool_and(_t2844, _t2845);
                (void)_t2846;
                ;
                ;
                if (_t2846) {
                    two = TokenType_clone(TokenType_EqEq());
                } else {
                    U8 _t2837 = 33;
                    (void)_t2837;
                    U8 _t2838 = 61;
                    (void)_t2838;
                    Bool _t2839 = U8_eq(DEREF(c), _t2837);
                    (void)_t2839;
                    ;
                    Bool _t2840 = U8_eq(DEREF(c2), _t2838);
                    (void)_t2840;
                    ;
                    Bool _t2841 = Bool_and(_t2839, _t2840);
                    (void)_t2841;
                    ;
                    ;
                    if (_t2841) {
                        two = TokenType_clone(TokenType_Neq());
                    } else {
                        U8 _t2832 = 60;
                        (void)_t2832;
                        U8 _t2833 = 61;
                        (void)_t2833;
                        Bool _t2834 = U8_eq(DEREF(c), _t2832);
                        (void)_t2834;
                        ;
                        Bool _t2835 = U8_eq(DEREF(c2), _t2833);
                        (void)_t2835;
                        ;
                        Bool _t2836 = Bool_and(_t2834, _t2835);
                        (void)_t2836;
                        ;
                        ;
                        if (_t2836) {
                            two = TokenType_clone(TokenType_LtEq());
                        } else {
                            U8 _t2827 = 62;
                            (void)_t2827;
                            U8 _t2828 = 61;
                            (void)_t2828;
                            Bool _t2829 = U8_eq(DEREF(c), _t2827);
                            (void)_t2829;
                            ;
                            Bool _t2830 = U8_eq(DEREF(c2), _t2828);
                            (void)_t2830;
                            ;
                            Bool _t2831 = Bool_and(_t2829, _t2830);
                            (void)_t2831;
                            ;
                            ;
                            if (_t2831) {
                                two = TokenType_clone(TokenType_GtEq());
                            } else {
                                U8 _t2822 = 46;
                                (void)_t2822;
                                U8 _t2823 = 46;
                                (void)_t2823;
                                Bool _t2824 = U8_eq(DEREF(c), _t2822);
                                (void)_t2824;
                                ;
                                Bool _t2825 = U8_eq(DEREF(c2), _t2823);
                                (void)_t2825;
                                ;
                                Bool _t2826 = Bool_and(_t2824, _t2825);
                                (void)_t2826;
                                ;
                                ;
                                if (_t2826) {
                                    U64 _t2819 = 2;
                                    (void)_t2819;
                                    U64 _t2820 = U64_add(DEREF(pos), _t2819);
                                    (void)_t2820;
                                    ;
                                    Bool _t2821; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2820}, &(U64){src_len}); _t2821 = *_hp; free(_hp); }
                                    (void)_t2821;
                                    ;
                                    if (_t2821) {
                                        U64 _t2815 = 2;
                                        (void)_t2815;
                                        U64 *_t2816 = malloc(sizeof(U64)); *_t2816 = U64_add(DEREF(pos), _t2815);
                                        (void)_t2816;
                                        ;
                                        U8 *c3 = Str_byte_at(src, _t2816);
                                        (void)c3;
                                        U8 _t2817 = 46;
                                        (void)_t2817;
                                        Bool _t2818 = U8_eq(DEREF(c3), _t2817);
                                        (void)_t2818;
                                        U64_delete(_t2816, &(Bool){1});
                                        ;
                                        if (_t2818) {
                                            U64 _t2809 = 3;
                                            (void)_t2809;
                                            Str *_t2810 = Str_substr(src, &(U64){start}, &(U64){_t2809});
                                            (void)_t2810;
                                            ;
                                            U32 _t2811 = U32_clone(&(U32){col});
                                            (void)_t2811;
                                            Token *_t2812 = malloc(sizeof(Token));
                                            { TokenType *_ca = TokenType_clone(TokenType_DotDotDot()); _t2812->type = *_ca; free(_ca); }
                                            { Str *_ca = Str_clone(_t2810); _t2812->text = *_ca; free(_ca); }
                                            _t2812->line = U32_clone(&(U32){line});
                                            _t2812->col = _t2811;
                                            (void)_t2812;
                                            Str_delete(_t2810, &(Bool){1});
                                            ;
                                            Vec_push(tokens, _t2812);
                                            U64 _t2813 = 3;
                                            (void)_t2813;
                                            U64 _t2814 = U64_add(DEREF(pos), _t2813);
                                            (void)_t2814;
                                            ;
                                            *pos = _t2814;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            U64_delete(_t2855, &(Bool){1});
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
            U64_delete(_t2855, &(Bool){1});
            ;
            Bool _t2861; { Bool *_hp = (Bool *)TokenType_eq(two, TokenType_Eof()); _t2861 = *_hp; free(_hp); }
            (void)_t2861;
            Bool _t2862 = Bool_not(_t2861);
            (void)_t2862;
            ;
            if (_t2862) {
                U64 _t2847 = 2;
                (void)_t2847;
                Str *_t2848 = Str_substr(src, &(U64){start}, &(U64){_t2847});
                (void)_t2848;
                ;
                U32 _t2849 = U32_clone(&(U32){line});
                (void)_t2849;
                U32 _t2850 = U32_clone(&(U32){col});
                (void)_t2850;
                Token *_t2851 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(two); _t2851->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2848); _t2851->text = *_ca; free(_ca); }
                _t2851->line = _t2849;
                _t2851->col = _t2850;
                (void)_t2851;
                Str_delete(_t2848, &(Bool){1});
                ;
                ;
                Vec_push(tokens, _t2851);
                U64 _t2852 = 2;
                (void)_t2852;
                U64 _t2853 = U64_add(DEREF(pos), _t2852);
                (void)_t2853;
                ;
                *pos = _t2853;
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
            U8 _sw2863 = U8_clone(c);
            (void)_sw2863;
            U8 _t2898 = 40;
            (void)_t2898;
            Bool _t2899 = U8_eq(_sw2863, _t2898);
            (void)_t2899;
            ;
            if (_t2899) {
                single = TokenType_clone(TokenType_LParen());
            } else {
                U8 _t2896 = 41;
                (void)_t2896;
                Bool _t2897 = U8_eq(_sw2863, _t2896);
                (void)_t2897;
                ;
                if (_t2897) {
                    single = TokenType_clone(TokenType_RParen());
                } else {
                    U8 _t2894 = 123;
                    (void)_t2894;
                    Bool _t2895 = U8_eq(_sw2863, _t2894);
                    (void)_t2895;
                    ;
                    if (_t2895) {
                        single = TokenType_clone(TokenType_LBrace());
                    } else {
                        U8 _t2892 = 125;
                        (void)_t2892;
                        Bool _t2893 = U8_eq(_sw2863, _t2892);
                        (void)_t2893;
                        ;
                        if (_t2893) {
                            single = TokenType_clone(TokenType_RBrace());
                        } else {
                            U8 _t2890 = 91;
                            (void)_t2890;
                            Bool _t2891 = U8_eq(_sw2863, _t2890);
                            (void)_t2891;
                            ;
                            if (_t2891) {
                                single = TokenType_clone(TokenType_LBracket());
                            } else {
                                U8 _t2888 = 93;
                                (void)_t2888;
                                Bool _t2889 = U8_eq(_sw2863, _t2888);
                                (void)_t2889;
                                ;
                                if (_t2889) {
                                    single = TokenType_clone(TokenType_RBracket());
                                } else {
                                    U8 _t2886 = 44;
                                    (void)_t2886;
                                    Bool _t2887 = U8_eq(_sw2863, _t2886);
                                    (void)_t2887;
                                    ;
                                    if (_t2887) {
                                        single = TokenType_clone(TokenType_Comma());
                                    } else {
                                        U8 _t2884 = 58;
                                        (void)_t2884;
                                        Bool _t2885 = U8_eq(_sw2863, _t2884);
                                        (void)_t2885;
                                        ;
                                        if (_t2885) {
                                            single = TokenType_clone(TokenType_Colon());
                                        } else {
                                            U8 _t2882 = 46;
                                            (void)_t2882;
                                            Bool _t2883 = U8_eq(_sw2863, _t2882);
                                            (void)_t2883;
                                            ;
                                            if (_t2883) {
                                                single = TokenType_clone(TokenType_Dot());
                                            } else {
                                                U8 _t2880 = 63;
                                                (void)_t2880;
                                                Bool _t2881 = U8_eq(_sw2863, _t2880);
                                                (void)_t2881;
                                                ;
                                                if (_t2881) {
                                                    single = TokenType_clone(TokenType_Question());
                                                } else {
                                                    U8 _t2878 = 33;
                                                    (void)_t2878;
                                                    Bool _t2879 = U8_eq(_sw2863, _t2878);
                                                    (void)_t2879;
                                                    ;
                                                    if (_t2879) {
                                                        single = TokenType_clone(TokenType_Bang());
                                                    } else {
                                                        U8 _t2876 = 43;
                                                        (void)_t2876;
                                                        Bool _t2877 = U8_eq(_sw2863, _t2876);
                                                        (void)_t2877;
                                                        ;
                                                        if (_t2877) {
                                                            single = TokenType_clone(TokenType_Plus());
                                                        } else {
                                                            U8 _t2874 = 45;
                                                            (void)_t2874;
                                                            Bool _t2875 = U8_eq(_sw2863, _t2874);
                                                            (void)_t2875;
                                                            ;
                                                            if (_t2875) {
                                                                single = TokenType_clone(TokenType_Minus());
                                                            } else {
                                                                U8 _t2872 = 42;
                                                                (void)_t2872;
                                                                Bool _t2873 = U8_eq(_sw2863, _t2872);
                                                                (void)_t2873;
                                                                ;
                                                                if (_t2873) {
                                                                    single = TokenType_clone(TokenType_Star());
                                                                } else {
                                                                    U8 _t2870 = 47;
                                                                    (void)_t2870;
                                                                    Bool _t2871 = U8_eq(_sw2863, _t2870);
                                                                    (void)_t2871;
                                                                    ;
                                                                    if (_t2871) {
                                                                        single = TokenType_clone(TokenType_Slash());
                                                                    } else {
                                                                        U8 _t2868 = 61;
                                                                        (void)_t2868;
                                                                        Bool _t2869 = U8_eq(_sw2863, _t2868);
                                                                        (void)_t2869;
                                                                        ;
                                                                        if (_t2869) {
                                                                            single = TokenType_clone(TokenType_Eq());
                                                                        } else {
                                                                            U8 _t2866 = 60;
                                                                            (void)_t2866;
                                                                            Bool _t2867 = U8_eq(_sw2863, _t2866);
                                                                            (void)_t2867;
                                                                            ;
                                                                            if (_t2867) {
                                                                                single = TokenType_clone(TokenType_Lt());
                                                                            } else {
                                                                                U8 _t2864 = 62;
                                                                                (void)_t2864;
                                                                                Bool _t2865 = U8_eq(_sw2863, _t2864);
                                                                                (void)_t2865;
                                                                                ;
                                                                                if (_t2865) {
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
        Bool _t2939; { Bool *_hp = (Bool *)TokenType_eq(single, TokenType_Eof()); _t2939 = *_hp; free(_hp); }
        (void)_t2939;
        Bool _t2940 = Bool_not(_t2939);
        (void)_t2940;
        ;
        if (_t2940) {
            U64 _t2900 = 1;
            (void)_t2900;
            Str *_t2901 = Str_substr(src, &(U64){start}, &(U64){_t2900});
            (void)_t2901;
            ;
            U32 _t2902 = U32_clone(&(U32){line});
            (void)_t2902;
            U32 _t2903 = U32_clone(&(U32){col});
            (void)_t2903;
            Token *_t2904 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(single); _t2904->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(_t2901); _t2904->text = *_ca; free(_ca); }
            _t2904->line = _t2902;
            _t2904->col = _t2903;
            (void)_t2904;
            Str_delete(_t2901, &(Bool){1});
            ;
            ;
            Vec_push(tokens, _t2904);
            U64_inc(pos);
            ;
            ;
            TokenType_delete(single, &(Bool){1});
            ;
            continue;
        }
        ;
        TokenType_delete(single, &(Bool){1});
        Str *_t2941 = Str_lit("Str", 3ULL);
        (void)_t2941;
        U64 _t2942; { U64 *_hp = (U64 *)Str_size(); _t2942 = *_hp; free(_hp); }
        (void)_t2942;
        U64 _t2943 = 6;
        (void)_t2943;
        Array *_va56 = Array_new(_t2941, &(U64){_t2942}, &(U64){_t2943});
        (void)_va56;
        Str_delete(_t2941, &(Bool){1});
        ;
        ;
        U64 _t2944 = 0;
        (void)_t2944;
        Str *_t2945 = Str_clone(path);
        (void)_t2945;
        Array_set(_va56, &(U64){_t2944}, _t2945);
        ;
        U64 _t2946 = 1;
        (void)_t2946;
        Str *_t2947 = Str_lit(":", 1ULL);
        (void)_t2947;
        Array_set(_va56, &(U64){_t2946}, _t2947);
        ;
        U64 _t2948 = 2;
        (void)_t2948;
        Str *_t2949 = U32_to_str(&(U32){line});
        (void)_t2949;
        Array_set(_va56, &(U64){_t2948}, _t2949);
        ;
        U64 _t2950 = 3;
        (void)_t2950;
        Str *_t2951 = Str_lit(":", 1ULL);
        (void)_t2951;
        Array_set(_va56, &(U64){_t2950}, _t2951);
        ;
        U64 _t2952 = 4;
        (void)_t2952;
        Str *_t2953 = U32_to_str(&(U32){col});
        (void)_t2953;
        Array_set(_va56, &(U64){_t2952}, _t2953);
        ;
        U64 _t2954 = 5;
        (void)_t2954;
        Str *_t2955 = Str_lit(": error: unexpected character", 29ULL);
        (void)_t2955;
        Array_set(_va56, &(U64){_t2954}, _t2955);
        ;
        println(_va56);
        U64 _t2956 = 1;
        (void)_t2956;
        Str *_t2957 = Str_substr(src, &(U64){start}, &(U64){_t2956});
        (void)_t2957;
        ;
        ;
        U32 _t2958 = U32_clone(&(U32){col});
        (void)_t2958;
        ;
        Token *_t2959 = malloc(sizeof(Token));
        { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2959->type = *_ca; free(_ca); }
        { Str *_ca = Str_clone(_t2957); _t2959->text = *_ca; free(_ca); }
        _t2959->line = U32_clone(&(U32){line});
        _t2959->col = _t2958;
        (void)_t2959;
        Str_delete(_t2957, &(Bool){1});
        ;
        Vec_push(tokens, _t2959);
        U64_inc(pos);
    }
    ;
    U64 _t2962 = U64_sub(DEREF(pos), line_start);
    (void)_t2962;
    ;
    U64_delete(pos, &(Bool){1});
    U64 _t2963 = 1;
    (void)_t2963;
    U64 _t2964 = U64_add(_t2962, _t2963);
    (void)_t2964;
    ;
    ;
    I64 col = U64_to_i64(_t2964);
    (void)col;
    ;
    I64 _t2965 = I64_clone(&(I64){col});
    (void)_t2965;
    ;
    Token *_t2966 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(TokenType_Eof()); _t2966->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t2966->text = *_ca; free(_ca); }
    _t2966->line = U32_clone(&(U32){line});
    _t2966->col = _t2965;
    (void)_t2966;
    ;
    ;
    Vec_push(tokens, _t2966);
    return tokens;
}

