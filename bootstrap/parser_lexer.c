#include "parser_lexer.h"

Token * Token_clone(Token * self) {
    (void)self;
    U32 _t2441 = U32_clone(&self->line);
    (void)_t2441;
    U32 _t2442 = U32_clone(&self->col);
    (void)_t2442;
    Token *_t2443 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(&self->type); _t2443->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->text); _t2443->text = *_ca; free(_ca); }
    _t2443->line = _t2441;
    _t2443->col = _t2442;
    (void)_t2443;
    ;
    ;
    return _t2443;
}

void Token_delete(Token * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t2444 = 0;
    (void)_t2444;
    TokenType_delete(&self->type, &(Bool){_t2444});
    ;
    Bool _t2445 = 0;
    (void)_t2445;
    Str_delete(&self->text, &(Bool){_t2445});
    ;
    Bool _t2446 = 0;
    (void)_t2446;
    U32_delete(&self->line, &(Bool){_t2446});
    ;
    Bool _t2447 = 0;
    (void)_t2447;
    U32_delete(&self->col, &(Bool){_t2447});
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
    U8 _t2449 = 48;
    (void)_t2449;
    U8 _t2450 = 57;
    (void)_t2450;
    Bool _t2451; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t2449}); _t2451 = *_hp; free(_hp); }
    (void)_t2451;
    ;
    Bool _t2452; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t2450}); _t2452 = *_hp; free(_hp); }
    (void)_t2452;
    ;
    Bool _t2453 = Bool_and(_t2451, _t2452);
    (void)_t2453;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2453; return _r; }
}

Bool * is_alpha(U8 * c) {
    (void)c;
    U8 _t2454 = 97;
    (void)_t2454;
    U8 _t2455 = 122;
    (void)_t2455;
    Bool _t2456; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t2454}); _t2456 = *_hp; free(_hp); }
    (void)_t2456;
    ;
    Bool _t2457; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t2455}); _t2457 = *_hp; free(_hp); }
    (void)_t2457;
    ;
    U8 _t2458 = 65;
    (void)_t2458;
    U8 _t2459 = 90;
    (void)_t2459;
    Bool _t2460; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t2458}); _t2460 = *_hp; free(_hp); }
    (void)_t2460;
    ;
    Bool _t2461; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t2459}); _t2461 = *_hp; free(_hp); }
    (void)_t2461;
    ;
    Bool _t2462 = Bool_and(_t2456, _t2457);
    (void)_t2462;
    ;
    ;
    Bool _t2463 = Bool_and(_t2460, _t2461);
    (void)_t2463;
    ;
    ;
    U8 _t2464 = 95;
    (void)_t2464;
    Bool _t2465 = Bool_or(_t2462, _t2463);
    (void)_t2465;
    ;
    ;
    Bool _t2466 = U8_eq(DEREF(c), _t2464);
    (void)_t2466;
    ;
    Bool _t2467 = Bool_or(_t2465, _t2466);
    (void)_t2467;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2467; return _r; }
}

Bool * is_alnum(U8 * c) {
    (void)c;
    Bool _t2468; { Bool *_hp = (Bool *)is_alpha(c); _t2468 = *_hp; free(_hp); }
    (void)_t2468;
    Bool _t2469; { Bool *_hp = (Bool *)is_digit(c); _t2469 = *_hp; free(_hp); }
    (void)_t2469;
    Bool _t2470 = Bool_or(_t2468, _t2469);
    (void)_t2470;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2470; return _r; }
}

Str * tok_name(TokenType * type) {
    (void)type;
    {
        TokenType *_sw2471 = TokenType_clone(type);
        (void)_sw2471;
        Bool _t2604; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_Eof()); _t2604 = *_hp; free(_hp); }
        (void)_t2604;
        if (_t2604) {
            Str *_t2472 = Str_lit("eof", 3ULL);
            (void)_t2472;
            TokenType_delete(_sw2471, &(Bool){1});
            ;
            return _t2472;
        } else {
            Bool _t2603; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_LParen()); _t2603 = *_hp; free(_hp); }
            (void)_t2603;
            if (_t2603) {
                Str *_t2473 = Str_lit("(", 1ULL);
                (void)_t2473;
                ;
                TokenType_delete(_sw2471, &(Bool){1});
                ;
                return _t2473;
            } else {
                Bool _t2602; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_RParen()); _t2602 = *_hp; free(_hp); }
                (void)_t2602;
                if (_t2602) {
                    Str *_t2474 = Str_lit(")", 1ULL);
                    (void)_t2474;
                    ;
                    ;
                    TokenType_delete(_sw2471, &(Bool){1});
                    ;
                    return _t2474;
                } else {
                    Bool _t2601; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_LBrace()); _t2601 = *_hp; free(_hp); }
                    (void)_t2601;
                    if (_t2601) {
                        Str *_t2475 = Str_lit("{", 1ULL);
                        (void)_t2475;
                        ;
                        ;
                        ;
                        TokenType_delete(_sw2471, &(Bool){1});
                        ;
                        return _t2475;
                    } else {
                        Bool _t2600; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_RBrace()); _t2600 = *_hp; free(_hp); }
                        (void)_t2600;
                        if (_t2600) {
                            Str *_t2476 = Str_lit("}", 1ULL);
                            (void)_t2476;
                            ;
                            ;
                            ;
                            ;
                            TokenType_delete(_sw2471, &(Bool){1});
                            ;
                            return _t2476;
                        } else {
                            Bool _t2599; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_LBracket()); _t2599 = *_hp; free(_hp); }
                            (void)_t2599;
                            if (_t2599) {
                                Str *_t2477 = Str_lit("[", 1ULL);
                                (void)_t2477;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TokenType_delete(_sw2471, &(Bool){1});
                                ;
                                return _t2477;
                            } else {
                                Bool _t2598; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_RBracket()); _t2598 = *_hp; free(_hp); }
                                (void)_t2598;
                                if (_t2598) {
                                    Str *_t2478 = Str_lit("]", 1ULL);
                                    (void)_t2478;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TokenType_delete(_sw2471, &(Bool){1});
                                    ;
                                    return _t2478;
                                } else {
                                    Bool _t2597; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_Comma()); _t2597 = *_hp; free(_hp); }
                                    (void)_t2597;
                                    if (_t2597) {
                                        Str *_t2479 = Str_lit(",", 1ULL);
                                        (void)_t2479;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TokenType_delete(_sw2471, &(Bool){1});
                                        ;
                                        return _t2479;
                                    } else {
                                        Bool _t2596; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_Colon()); _t2596 = *_hp; free(_hp); }
                                        (void)_t2596;
                                        if (_t2596) {
                                            Str *_t2480 = Str_lit(":", 1ULL);
                                            (void)_t2480;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TokenType_delete(_sw2471, &(Bool){1});
                                            ;
                                            return _t2480;
                                        } else {
                                            Bool _t2595; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_Question()); _t2595 = *_hp; free(_hp); }
                                            (void)_t2595;
                                            if (_t2595) {
                                                Str *_t2481 = Str_lit("?", 1ULL);
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
                                                TokenType_delete(_sw2471, &(Bool){1});
                                                ;
                                                return _t2481;
                                            } else {
                                                Bool _t2594; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_Bang()); _t2594 = *_hp; free(_hp); }
                                                (void)_t2594;
                                                if (_t2594) {
                                                    Str *_t2482 = Str_lit("!", 1ULL);
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
                                                    TokenType_delete(_sw2471, &(Bool){1});
                                                    ;
                                                    return _t2482;
                                                } else {
                                                    Bool _t2593; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_Minus()); _t2593 = *_hp; free(_hp); }
                                                    (void)_t2593;
                                                    if (_t2593) {
                                                        Str *_t2483 = Str_lit("-", 1ULL);
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
                                                        TokenType_delete(_sw2471, &(Bool){1});
                                                        ;
                                                        return _t2483;
                                                    } else {
                                                        Bool _t2592; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_Plus()); _t2592 = *_hp; free(_hp); }
                                                        (void)_t2592;
                                                        if (_t2592) {
                                                            Str *_t2484 = Str_lit("+", 1ULL);
                                                            (void)_t2484;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            TokenType_delete(_sw2471, &(Bool){1});
                                                            ;
                                                            return _t2484;
                                                        } else {
                                                            Bool _t2591; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_Star()); _t2591 = *_hp; free(_hp); }
                                                            (void)_t2591;
                                                            if (_t2591) {
                                                                Str *_t2485 = Str_lit("*", 1ULL);
                                                                (void)_t2485;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                TokenType_delete(_sw2471, &(Bool){1});
                                                                ;
                                                                return _t2485;
                                                            } else {
                                                                Bool _t2590; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_Slash()); _t2590 = *_hp; free(_hp); }
                                                                (void)_t2590;
                                                                if (_t2590) {
                                                                    Str *_t2486 = Str_lit("/", 1ULL);
                                                                    (void)_t2486;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    TokenType_delete(_sw2471, &(Bool){1});
                                                                    ;
                                                                    return _t2486;
                                                                } else {
                                                                    Bool _t2589; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_Dot()); _t2589 = *_hp; free(_hp); }
                                                                    (void)_t2589;
                                                                    if (_t2589) {
                                                                        Str *_t2487 = Str_lit(".", 1ULL);
                                                                        (void)_t2487;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        TokenType_delete(_sw2471, &(Bool){1});
                                                                        ;
                                                                        return _t2487;
                                                                    } else {
                                                                        Bool _t2588; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_DotDot()); _t2588 = *_hp; free(_hp); }
                                                                        (void)_t2588;
                                                                        if (_t2588) {
                                                                            Str *_t2488 = Str_lit("..", 2ULL);
                                                                            (void)_t2488;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TokenType_delete(_sw2471, &(Bool){1});
                                                                            ;
                                                                            return _t2488;
                                                                        } else {
                                                                            Bool _t2587; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_DotDotDot()); _t2587 = *_hp; free(_hp); }
                                                                            (void)_t2587;
                                                                            if (_t2587) {
                                                                                Str *_t2489 = Str_lit("...", 3ULL);
                                                                                (void)_t2489;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                TokenType_delete(_sw2471, &(Bool){1});
                                                                                ;
                                                                                return _t2489;
                                                                            } else {
                                                                                Bool _t2586; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_Eq()); _t2586 = *_hp; free(_hp); }
                                                                                (void)_t2586;
                                                                                if (_t2586) {
                                                                                    Str *_t2490 = Str_lit("=", 1ULL);
                                                                                    (void)_t2490;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    TokenType_delete(_sw2471, &(Bool){1});
                                                                                    ;
                                                                                    return _t2490;
                                                                                } else {
                                                                                    Bool _t2585; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_EqEq()); _t2585 = *_hp; free(_hp); }
                                                                                    (void)_t2585;
                                                                                    if (_t2585) {
                                                                                        Str *_t2491 = Str_lit("==", 2ULL);
                                                                                        (void)_t2491;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        TokenType_delete(_sw2471, &(Bool){1});
                                                                                        ;
                                                                                        return _t2491;
                                                                                    } else {
                                                                                        Bool _t2584; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_Neq()); _t2584 = *_hp; free(_hp); }
                                                                                        (void)_t2584;
                                                                                        if (_t2584) {
                                                                                            Str *_t2492 = Str_lit("!=", 2ULL);
                                                                                            (void)_t2492;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            TokenType_delete(_sw2471, &(Bool){1});
                                                                                            ;
                                                                                            return _t2492;
                                                                                        } else {
                                                                                            Bool _t2583; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_Lt()); _t2583 = *_hp; free(_hp); }
                                                                                            (void)_t2583;
                                                                                            if (_t2583) {
                                                                                                Str *_t2493 = Str_lit("<", 1ULL);
                                                                                                (void)_t2493;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                TokenType_delete(_sw2471, &(Bool){1});
                                                                                                ;
                                                                                                return _t2493;
                                                                                            } else {
                                                                                                Bool _t2582; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_LtEq()); _t2582 = *_hp; free(_hp); }
                                                                                                (void)_t2582;
                                                                                                if (_t2582) {
                                                                                                    Str *_t2494 = Str_lit("<=", 2ULL);
                                                                                                    (void)_t2494;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    TokenType_delete(_sw2471, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t2494;
                                                                                                } else {
                                                                                                    Bool _t2581; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_Gt()); _t2581 = *_hp; free(_hp); }
                                                                                                    (void)_t2581;
                                                                                                    if (_t2581) {
                                                                                                        Str *_t2495 = Str_lit(">", 1ULL);
                                                                                                        (void)_t2495;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        TokenType_delete(_sw2471, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t2495;
                                                                                                    } else {
                                                                                                        Bool _t2580; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_GtEq()); _t2580 = *_hp; free(_hp); }
                                                                                                        (void)_t2580;
                                                                                                        if (_t2580) {
                                                                                                            Str *_t2496 = Str_lit(">=", 2ULL);
                                                                                                            (void)_t2496;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            TokenType_delete(_sw2471, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t2496;
                                                                                                        } else {
                                                                                                            Bool _t2579; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_ColonEq()); _t2579 = *_hp; free(_hp); }
                                                                                                            (void)_t2579;
                                                                                                            if (_t2579) {
                                                                                                                Str *_t2497 = Str_lit(":=", 2ULL);
                                                                                                                (void)_t2497;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                ;
                                                                                                                return _t2497;
                                                                                                            } else {
                                                                                                                Bool _t2578; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_Ident()); _t2578 = *_hp; free(_hp); }
                                                                                                                (void)_t2578;
                                                                                                                if (_t2578) {
                                                                                                                    Str *_t2498 = Str_lit("identifier", 10ULL);
                                                                                                                    (void)_t2498;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return _t2498;
                                                                                                                } else {
                                                                                                                    Bool _t2577; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_StringTok()); _t2577 = *_hp; free(_hp); }
                                                                                                                    (void)_t2577;
                                                                                                                    if (_t2577) {
                                                                                                                        Str *_t2499 = Str_lit("string", 6ULL);
                                                                                                                        (void)_t2499;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return _t2499;
                                                                                                                    } else {
                                                                                                                        Bool _t2576; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_Number()); _t2576 = *_hp; free(_hp); }
                                                                                                                        (void)_t2576;
                                                                                                                        if (_t2576) {
                                                                                                                            Str *_t2500 = Str_lit("number", 6ULL);
                                                                                                                            (void)_t2500;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return _t2500;
                                                                                                                        } else {
                                                                                                                            Bool _t2575; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_Char()); _t2575 = *_hp; free(_hp); }
                                                                                                                            (void)_t2575;
                                                                                                                            if (_t2575) {
                                                                                                                                Str *_t2501 = Str_lit("char", 4ULL);
                                                                                                                                (void)_t2501;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return _t2501;
                                                                                                                            } else {
                                                                                                                                Bool _t2574; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwMode()); _t2574 = *_hp; free(_hp); }
                                                                                                                                (void)_t2574;
                                                                                                                                if (_t2574) {
                                                                                                                                    Str *_t2502 = Str_lit("mode", 4ULL);
                                                                                                                                    (void)_t2502;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return _t2502;
                                                                                                                                } else {
                                                                                                                                    Bool _t2573; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwMut()); _t2573 = *_hp; free(_hp); }
                                                                                                                                    (void)_t2573;
                                                                                                                                    if (_t2573) {
                                                                                                                                        Str *_t2503 = Str_lit("mut", 3ULL);
                                                                                                                                        (void)_t2503;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return _t2503;
                                                                                                                                    } else {
                                                                                                                                        Bool _t2572; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwOwn()); _t2572 = *_hp; free(_hp); }
                                                                                                                                        (void)_t2572;
                                                                                                                                        if (_t2572) {
                                                                                                                                            Str *_t2504 = Str_lit("own", 3ULL);
                                                                                                                                            (void)_t2504;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return _t2504;
                                                                                                                                        } else {
                                                                                                                                            Bool _t2571; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwRef()); _t2571 = *_hp; free(_hp); }
                                                                                                                                            (void)_t2571;
                                                                                                                                            if (_t2571) {
                                                                                                                                                Str *_t2505 = Str_lit("ref", 3ULL);
                                                                                                                                                (void)_t2505;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return _t2505;
                                                                                                                                            } else {
                                                                                                                                                Bool _t2570; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwShallow()); _t2570 = *_hp; free(_hp); }
                                                                                                                                                (void)_t2570;
                                                                                                                                                if (_t2570) {
                                                                                                                                                    Str *_t2506 = Str_lit("shallow", 7ULL);
                                                                                                                                                    (void)_t2506;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                    ;
                                                                                                                                                    return _t2506;
                                                                                                                                                } else {
                                                                                                                                                    Bool _t2569; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwStruct()); _t2569 = *_hp; free(_hp); }
                                                                                                                                                    (void)_t2569;
                                                                                                                                                    if (_t2569) {
                                                                                                                                                        Str *_t2507 = Str_lit("struct", 6ULL);
                                                                                                                                                        (void)_t2507;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                        ;
                                                                                                                                                        return _t2507;
                                                                                                                                                    } else {
                                                                                                                                                        Bool _t2568; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwExtStruct()); _t2568 = *_hp; free(_hp); }
                                                                                                                                                        (void)_t2568;
                                                                                                                                                        if (_t2568) {
                                                                                                                                                            Str *_t2508 = Str_lit("ext_struct", 10ULL);
                                                                                                                                                            (void)_t2508;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                            ;
                                                                                                                                                            return _t2508;
                                                                                                                                                        } else {
                                                                                                                                                            Bool _t2567; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwEnum()); _t2567 = *_hp; free(_hp); }
                                                                                                                                                            (void)_t2567;
                                                                                                                                                            if (_t2567) {
                                                                                                                                                                Str *_t2509 = Str_lit("enum", 4ULL);
                                                                                                                                                                (void)_t2509;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                ;
                                                                                                                                                                return _t2509;
                                                                                                                                                            } else {
                                                                                                                                                                Bool _t2566; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwNamespace()); _t2566 = *_hp; free(_hp); }
                                                                                                                                                                (void)_t2566;
                                                                                                                                                                if (_t2566) {
                                                                                                                                                                    Str *_t2510 = Str_lit("namespace", 9ULL);
                                                                                                                                                                    (void)_t2510;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                    ;
                                                                                                                                                                    return _t2510;
                                                                                                                                                                } else {
                                                                                                                                                                    Bool _t2565; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwFunc()); _t2565 = *_hp; free(_hp); }
                                                                                                                                                                    (void)_t2565;
                                                                                                                                                                    if (_t2565) {
                                                                                                                                                                        Str *_t2511 = Str_lit("func", 4ULL);
                                                                                                                                                                        (void)_t2511;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                        ;
                                                                                                                                                                        return _t2511;
                                                                                                                                                                    } else {
                                                                                                                                                                        Bool _t2564; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwProc()); _t2564 = *_hp; free(_hp); }
                                                                                                                                                                        (void)_t2564;
                                                                                                                                                                        if (_t2564) {
                                                                                                                                                                            Str *_t2512 = Str_lit("proc", 4ULL);
                                                                                                                                                                            (void)_t2512;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                            ;
                                                                                                                                                                            return _t2512;
                                                                                                                                                                        } else {
                                                                                                                                                                            Bool _t2563; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwTest()); _t2563 = *_hp; free(_hp); }
                                                                                                                                                                            (void)_t2563;
                                                                                                                                                                            if (_t2563) {
                                                                                                                                                                                Str *_t2513 = Str_lit("test", 4ULL);
                                                                                                                                                                                (void)_t2513;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                ;
                                                                                                                                                                                return _t2513;
                                                                                                                                                                            } else {
                                                                                                                                                                                Bool _t2562; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwMacro()); _t2562 = *_hp; free(_hp); }
                                                                                                                                                                                (void)_t2562;
                                                                                                                                                                                if (_t2562) {
                                                                                                                                                                                    Str *_t2514 = Str_lit("macro", 5ULL);
                                                                                                                                                                                    (void)_t2514;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                    ;
                                                                                                                                                                                    return _t2514;
                                                                                                                                                                                } else {
                                                                                                                                                                                    Bool _t2561; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwExtFunc()); _t2561 = *_hp; free(_hp); }
                                                                                                                                                                                    (void)_t2561;
                                                                                                                                                                                    if (_t2561) {
                                                                                                                                                                                        Str *_t2515 = Str_lit("ext_func", 8ULL);
                                                                                                                                                                                        (void)_t2515;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                        ;
                                                                                                                                                                                        return _t2515;
                                                                                                                                                                                    } else {
                                                                                                                                                                                        Bool _t2560; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwExtProc()); _t2560 = *_hp; free(_hp); }
                                                                                                                                                                                        (void)_t2560;
                                                                                                                                                                                        if (_t2560) {
                                                                                                                                                                                            Str *_t2516 = Str_lit("ext_proc", 8ULL);
                                                                                                                                                                                            (void)_t2516;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                            ;
                                                                                                                                                                                            return _t2516;
                                                                                                                                                                                        } else {
                                                                                                                                                                                            Bool _t2559; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwReturns()); _t2559 = *_hp; free(_hp); }
                                                                                                                                                                                            (void)_t2559;
                                                                                                                                                                                            if (_t2559) {
                                                                                                                                                                                                Str *_t2517 = Str_lit("returns", 7ULL);
                                                                                                                                                                                                (void)_t2517;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                                ;
                                                                                                                                                                                                return _t2517;
                                                                                                                                                                                            } else {
                                                                                                                                                                                                Bool _t2558; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwThrows()); _t2558 = *_hp; free(_hp); }
                                                                                                                                                                                                (void)_t2558;
                                                                                                                                                                                                if (_t2558) {
                                                                                                                                                                                                    Str *_t2518 = Str_lit("throws", 6ULL);
                                                                                                                                                                                                    (void)_t2518;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    return _t2518;
                                                                                                                                                                                                } else {
                                                                                                                                                                                                    Bool _t2557; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwIf()); _t2557 = *_hp; free(_hp); }
                                                                                                                                                                                                    (void)_t2557;
                                                                                                                                                                                                    if (_t2557) {
                                                                                                                                                                                                        Str *_t2519 = Str_lit("if", 2ULL);
                                                                                                                                                                                                        (void)_t2519;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        return _t2519;
                                                                                                                                                                                                    } else {
                                                                                                                                                                                                        Bool _t2556; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwElse()); _t2556 = *_hp; free(_hp); }
                                                                                                                                                                                                        (void)_t2556;
                                                                                                                                                                                                        if (_t2556) {
                                                                                                                                                                                                            Str *_t2520 = Str_lit("else", 4ULL);
                                                                                                                                                                                                            (void)_t2520;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            return _t2520;
                                                                                                                                                                                                        } else {
                                                                                                                                                                                                            Bool _t2555; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwWhile()); _t2555 = *_hp; free(_hp); }
                                                                                                                                                                                                            (void)_t2555;
                                                                                                                                                                                                            if (_t2555) {
                                                                                                                                                                                                                Str *_t2521 = Str_lit("while", 5ULL);
                                                                                                                                                                                                                (void)_t2521;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                return _t2521;
                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                Bool _t2554; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwFor()); _t2554 = *_hp; free(_hp); }
                                                                                                                                                                                                                (void)_t2554;
                                                                                                                                                                                                                if (_t2554) {
                                                                                                                                                                                                                    Str *_t2522 = Str_lit("for", 3ULL);
                                                                                                                                                                                                                    (void)_t2522;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    return _t2522;
                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                    Bool _t2553; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwIn()); _t2553 = *_hp; free(_hp); }
                                                                                                                                                                                                                    (void)_t2553;
                                                                                                                                                                                                                    if (_t2553) {
                                                                                                                                                                                                                        Str *_t2523 = Str_lit("in", 2ULL);
                                                                                                                                                                                                                        (void)_t2523;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        return _t2523;
                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                        Bool _t2552; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwSwitch()); _t2552 = *_hp; free(_hp); }
                                                                                                                                                                                                                        (void)_t2552;
                                                                                                                                                                                                                        if (_t2552) {
                                                                                                                                                                                                                            Str *_t2524 = Str_lit("switch", 6ULL);
                                                                                                                                                                                                                            (void)_t2524;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            return _t2524;
                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                            Bool _t2551; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwMatch()); _t2551 = *_hp; free(_hp); }
                                                                                                                                                                                                                            (void)_t2551;
                                                                                                                                                                                                                            if (_t2551) {
                                                                                                                                                                                                                                Str *_t2525 = Str_lit("match", 5ULL);
                                                                                                                                                                                                                                (void)_t2525;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                return _t2525;
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                Bool _t2550; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwCase()); _t2550 = *_hp; free(_hp); }
                                                                                                                                                                                                                                (void)_t2550;
                                                                                                                                                                                                                                if (_t2550) {
                                                                                                                                                                                                                                    Str *_t2526 = Str_lit("case", 4ULL);
                                                                                                                                                                                                                                    (void)_t2526;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    return _t2526;
                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                    Bool _t2549; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwDefault()); _t2549 = *_hp; free(_hp); }
                                                                                                                                                                                                                                    (void)_t2549;
                                                                                                                                                                                                                                    if (_t2549) {
                                                                                                                                                                                                                                        Str *_t2527 = Str_lit("default", 7ULL);
                                                                                                                                                                                                                                        (void)_t2527;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        return _t2527;
                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                        Bool _t2548; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwReturn()); _t2548 = *_hp; free(_hp); }
                                                                                                                                                                                                                                        (void)_t2548;
                                                                                                                                                                                                                                        if (_t2548) {
                                                                                                                                                                                                                                            Str *_t2528 = Str_lit("return", 6ULL);
                                                                                                                                                                                                                                            (void)_t2528;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            return _t2528;
                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                            Bool _t2547; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwThrow()); _t2547 = *_hp; free(_hp); }
                                                                                                                                                                                                                                            (void)_t2547;
                                                                                                                                                                                                                                            if (_t2547) {
                                                                                                                                                                                                                                                Str *_t2529 = Str_lit("throw", 5ULL);
                                                                                                                                                                                                                                                (void)_t2529;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                return _t2529;
                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                Bool _t2546; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwCatch()); _t2546 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                (void)_t2546;
                                                                                                                                                                                                                                                if (_t2546) {
                                                                                                                                                                                                                                                    Str *_t2530 = Str_lit("catch", 5ULL);
                                                                                                                                                                                                                                                    (void)_t2530;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    return _t2530;
                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                    Bool _t2545; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwBreak()); _t2545 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                    (void)_t2545;
                                                                                                                                                                                                                                                    if (_t2545) {
                                                                                                                                                                                                                                                        Str *_t2531 = Str_lit("break", 5ULL);
                                                                                                                                                                                                                                                        (void)_t2531;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        return _t2531;
                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                        Bool _t2544; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwContinue()); _t2544 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                        (void)_t2544;
                                                                                                                                                                                                                                                        if (_t2544) {
                                                                                                                                                                                                                                                            Str *_t2532 = Str_lit("continue", 8ULL);
                                                                                                                                                                                                                                                            (void)_t2532;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            return _t2532;
                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                            Bool _t2543; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwDefer()); _t2543 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                            (void)_t2543;
                                                                                                                                                                                                                                                            if (_t2543) {
                                                                                                                                                                                                                                                                Str *_t2533 = Str_lit("defer", 5ULL);
                                                                                                                                                                                                                                                                (void)_t2533;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                return _t2533;
                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                Bool _t2542; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwTrue()); _t2542 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                (void)_t2542;
                                                                                                                                                                                                                                                                if (_t2542) {
                                                                                                                                                                                                                                                                    Str *_t2534 = Str_lit("true", 4ULL);
                                                                                                                                                                                                                                                                    (void)_t2534;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t2534;
                                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                                    Bool _t2541; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwFalse()); _t2541 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                    (void)_t2541;
                                                                                                                                                                                                                                                                    if (_t2541) {
                                                                                                                                                                                                                                                                        Str *_t2535 = Str_lit("false", 5ULL);
                                                                                                                                                                                                                                                                        (void)_t2535;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        return _t2535;
                                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                                        Bool _t2540; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_KwNull()); _t2540 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                        (void)_t2540;
                                                                                                                                                                                                                                                                        if (_t2540) {
                                                                                                                                                                                                                                                                            Str *_t2536 = Str_lit("NULL", 4ULL);
                                                                                                                                                                                                                                                                            (void)_t2536;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            return _t2536;
                                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                                            Bool _t2539; { Bool *_hp = (Bool *)TokenType_eq(_sw2471, TokenType_Error()); _t2539 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                            (void)_t2539;
                                                                                                                                                                                                                                                                            if (_t2539) {
                                                                                                                                                                                                                                                                                Str *_t2537 = Str_lit("error", 5ULL);
                                                                                                                                                                                                                                                                                (void)_t2537;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t2537;
                                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                                Str *_t2538 = Str_lit("?", 1ULL);
                                                                                                                                                                                                                                                                                (void)_t2538;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                TokenType_delete(_sw2471, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t2538;
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
        TokenType_delete(_sw2471, &(Bool){1});
        ;
    }
}

TokenType * lookup_keyword(Str * word) {
    (void)word;
    {
        Str *_sw2605 = Str_clone(word);
        (void)_sw2605;
        Str *_t2674 = Str_lit("mode", 4ULL);
        (void)_t2674;
        Bool _t2675; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2674); _t2675 = *_hp; free(_hp); }
        (void)_t2675;
        Str_delete(_t2674, &(Bool){1});
        if (_t2675) {
            Str_delete(_sw2605, &(Bool){1});
            ;
            return TokenType_KwMode();
        } else {
            Str *_t2672 = Str_lit("mut", 3ULL);
            (void)_t2672;
            Bool _t2673; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2672); _t2673 = *_hp; free(_hp); }
            (void)_t2673;
            Str_delete(_t2672, &(Bool){1});
            if (_t2673) {
                ;
                Str_delete(_sw2605, &(Bool){1});
                ;
                return TokenType_KwMut();
            } else {
                Str *_t2670 = Str_lit("own", 3ULL);
                (void)_t2670;
                Bool _t2671; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2670); _t2671 = *_hp; free(_hp); }
                (void)_t2671;
                Str_delete(_t2670, &(Bool){1});
                if (_t2671) {
                    ;
                    ;
                    Str_delete(_sw2605, &(Bool){1});
                    ;
                    return TokenType_KwOwn();
                } else {
                    Str *_t2668 = Str_lit("ref", 3ULL);
                    (void)_t2668;
                    Bool _t2669; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2668); _t2669 = *_hp; free(_hp); }
                    (void)_t2669;
                    Str_delete(_t2668, &(Bool){1});
                    if (_t2669) {
                        ;
                        ;
                        ;
                        Str_delete(_sw2605, &(Bool){1});
                        ;
                        return TokenType_KwRef();
                    } else {
                        Str *_t2666 = Str_lit("shallow", 7ULL);
                        (void)_t2666;
                        Bool _t2667; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2666); _t2667 = *_hp; free(_hp); }
                        (void)_t2667;
                        Str_delete(_t2666, &(Bool){1});
                        if (_t2667) {
                            ;
                            ;
                            ;
                            ;
                            Str_delete(_sw2605, &(Bool){1});
                            ;
                            return TokenType_KwShallow();
                        } else {
                            Str *_t2664 = Str_lit("struct", 6ULL);
                            (void)_t2664;
                            Bool _t2665; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2664); _t2665 = *_hp; free(_hp); }
                            (void)_t2665;
                            Str_delete(_t2664, &(Bool){1});
                            if (_t2665) {
                                ;
                                ;
                                ;
                                ;
                                ;
                                Str_delete(_sw2605, &(Bool){1});
                                ;
                                return TokenType_KwStruct();
                            } else {
                                Str *_t2662 = Str_lit("ext_struct", 10ULL);
                                (void)_t2662;
                                Bool _t2663; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2662); _t2663 = *_hp; free(_hp); }
                                (void)_t2663;
                                Str_delete(_t2662, &(Bool){1});
                                if (_t2663) {
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    Str_delete(_sw2605, &(Bool){1});
                                    ;
                                    return TokenType_KwExtStruct();
                                } else {
                                    Str *_t2660 = Str_lit("enum", 4ULL);
                                    (void)_t2660;
                                    Bool _t2661; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2660); _t2661 = *_hp; free(_hp); }
                                    (void)_t2661;
                                    Str_delete(_t2660, &(Bool){1});
                                    if (_t2661) {
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        Str_delete(_sw2605, &(Bool){1});
                                        ;
                                        return TokenType_KwEnum();
                                    } else {
                                        Str *_t2658 = Str_lit("namespace", 9ULL);
                                        (void)_t2658;
                                        Bool _t2659; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2658); _t2659 = *_hp; free(_hp); }
                                        (void)_t2659;
                                        Str_delete(_t2658, &(Bool){1});
                                        if (_t2659) {
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            Str_delete(_sw2605, &(Bool){1});
                                            ;
                                            return TokenType_KwNamespace();
                                        } else {
                                            Str *_t2656 = Str_lit("func", 4ULL);
                                            (void)_t2656;
                                            Bool _t2657; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2656); _t2657 = *_hp; free(_hp); }
                                            (void)_t2657;
                                            Str_delete(_t2656, &(Bool){1});
                                            if (_t2657) {
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                Str_delete(_sw2605, &(Bool){1});
                                                ;
                                                return TokenType_KwFunc();
                                            } else {
                                                Str *_t2654 = Str_lit("proc", 4ULL);
                                                (void)_t2654;
                                                Bool _t2655; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2654); _t2655 = *_hp; free(_hp); }
                                                (void)_t2655;
                                                Str_delete(_t2654, &(Bool){1});
                                                if (_t2655) {
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    Str_delete(_sw2605, &(Bool){1});
                                                    ;
                                                    return TokenType_KwProc();
                                                } else {
                                                    Str *_t2652 = Str_lit("test", 4ULL);
                                                    (void)_t2652;
                                                    Bool _t2653; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2652); _t2653 = *_hp; free(_hp); }
                                                    (void)_t2653;
                                                    Str_delete(_t2652, &(Bool){1});
                                                    if (_t2653) {
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        Str_delete(_sw2605, &(Bool){1});
                                                        ;
                                                        return TokenType_KwTest();
                                                    } else {
                                                        Str *_t2650 = Str_lit("macro", 5ULL);
                                                        (void)_t2650;
                                                        Bool _t2651; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2650); _t2651 = *_hp; free(_hp); }
                                                        (void)_t2651;
                                                        Str_delete(_t2650, &(Bool){1});
                                                        if (_t2651) {
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            Str_delete(_sw2605, &(Bool){1});
                                                            ;
                                                            return TokenType_KwMacro();
                                                        } else {
                                                            Str *_t2648 = Str_lit("ext_func", 8ULL);
                                                            (void)_t2648;
                                                            Bool _t2649; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2648); _t2649 = *_hp; free(_hp); }
                                                            (void)_t2649;
                                                            Str_delete(_t2648, &(Bool){1});
                                                            if (_t2649) {
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                Str_delete(_sw2605, &(Bool){1});
                                                                ;
                                                                return TokenType_KwExtFunc();
                                                            } else {
                                                                Str *_t2646 = Str_lit("ext_proc", 8ULL);
                                                                (void)_t2646;
                                                                Bool _t2647; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2646); _t2647 = *_hp; free(_hp); }
                                                                (void)_t2647;
                                                                Str_delete(_t2646, &(Bool){1});
                                                                if (_t2647) {
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    Str_delete(_sw2605, &(Bool){1});
                                                                    ;
                                                                    return TokenType_KwExtProc();
                                                                } else {
                                                                    Str *_t2644 = Str_lit("returns", 7ULL);
                                                                    (void)_t2644;
                                                                    Bool _t2645; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2644); _t2645 = *_hp; free(_hp); }
                                                                    (void)_t2645;
                                                                    Str_delete(_t2644, &(Bool){1});
                                                                    if (_t2645) {
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        Str_delete(_sw2605, &(Bool){1});
                                                                        ;
                                                                        return TokenType_KwReturns();
                                                                    } else {
                                                                        Str *_t2642 = Str_lit("throws", 6ULL);
                                                                        (void)_t2642;
                                                                        Bool _t2643; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2642); _t2643 = *_hp; free(_hp); }
                                                                        (void)_t2643;
                                                                        Str_delete(_t2642, &(Bool){1});
                                                                        if (_t2643) {
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            Str_delete(_sw2605, &(Bool){1});
                                                                            ;
                                                                            return TokenType_KwThrows();
                                                                        } else {
                                                                            Str *_t2640 = Str_lit("if", 2ULL);
                                                                            (void)_t2640;
                                                                            Bool _t2641; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2640); _t2641 = *_hp; free(_hp); }
                                                                            (void)_t2641;
                                                                            Str_delete(_t2640, &(Bool){1});
                                                                            if (_t2641) {
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                Str_delete(_sw2605, &(Bool){1});
                                                                                ;
                                                                                return TokenType_KwIf();
                                                                            } else {
                                                                                Str *_t2638 = Str_lit("else", 4ULL);
                                                                                (void)_t2638;
                                                                                Bool _t2639; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2638); _t2639 = *_hp; free(_hp); }
                                                                                (void)_t2639;
                                                                                Str_delete(_t2638, &(Bool){1});
                                                                                if (_t2639) {
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    Str_delete(_sw2605, &(Bool){1});
                                                                                    ;
                                                                                    return TokenType_KwElse();
                                                                                } else {
                                                                                    Str *_t2636 = Str_lit("while", 5ULL);
                                                                                    (void)_t2636;
                                                                                    Bool _t2637; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2636); _t2637 = *_hp; free(_hp); }
                                                                                    (void)_t2637;
                                                                                    Str_delete(_t2636, &(Bool){1});
                                                                                    if (_t2637) {
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        Str_delete(_sw2605, &(Bool){1});
                                                                                        ;
                                                                                        return TokenType_KwWhile();
                                                                                    } else {
                                                                                        Str *_t2634 = Str_lit("for", 3ULL);
                                                                                        (void)_t2634;
                                                                                        Bool _t2635; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2634); _t2635 = *_hp; free(_hp); }
                                                                                        (void)_t2635;
                                                                                        Str_delete(_t2634, &(Bool){1});
                                                                                        if (_t2635) {
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            Str_delete(_sw2605, &(Bool){1});
                                                                                            ;
                                                                                            return TokenType_KwFor();
                                                                                        } else {
                                                                                            Str *_t2632 = Str_lit("in", 2ULL);
                                                                                            (void)_t2632;
                                                                                            Bool _t2633; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2632); _t2633 = *_hp; free(_hp); }
                                                                                            (void)_t2633;
                                                                                            Str_delete(_t2632, &(Bool){1});
                                                                                            if (_t2633) {
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                Str_delete(_sw2605, &(Bool){1});
                                                                                                ;
                                                                                                return TokenType_KwIn();
                                                                                            } else {
                                                                                                Str *_t2630 = Str_lit("switch", 6ULL);
                                                                                                (void)_t2630;
                                                                                                Bool _t2631; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2630); _t2631 = *_hp; free(_hp); }
                                                                                                (void)_t2631;
                                                                                                Str_delete(_t2630, &(Bool){1});
                                                                                                if (_t2631) {
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    Str_delete(_sw2605, &(Bool){1});
                                                                                                    ;
                                                                                                    return TokenType_KwSwitch();
                                                                                                } else {
                                                                                                    Str *_t2628 = Str_lit("match", 5ULL);
                                                                                                    (void)_t2628;
                                                                                                    Bool _t2629; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2628); _t2629 = *_hp; free(_hp); }
                                                                                                    (void)_t2629;
                                                                                                    Str_delete(_t2628, &(Bool){1});
                                                                                                    if (_t2629) {
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        Str_delete(_sw2605, &(Bool){1});
                                                                                                        ;
                                                                                                        return TokenType_KwMatch();
                                                                                                    } else {
                                                                                                        Str *_t2626 = Str_lit("case", 4ULL);
                                                                                                        (void)_t2626;
                                                                                                        Bool _t2627; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2626); _t2627 = *_hp; free(_hp); }
                                                                                                        (void)_t2627;
                                                                                                        Str_delete(_t2626, &(Bool){1});
                                                                                                        if (_t2627) {
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            Str_delete(_sw2605, &(Bool){1});
                                                                                                            ;
                                                                                                            return TokenType_KwCase();
                                                                                                        } else {
                                                                                                            Str *_t2624 = Str_lit("default", 7ULL);
                                                                                                            (void)_t2624;
                                                                                                            Bool _t2625; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2624); _t2625 = *_hp; free(_hp); }
                                                                                                            (void)_t2625;
                                                                                                            Str_delete(_t2624, &(Bool){1});
                                                                                                            if (_t2625) {
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                Str_delete(_sw2605, &(Bool){1});
                                                                                                                ;
                                                                                                                return TokenType_KwDefault();
                                                                                                            } else {
                                                                                                                Str *_t2622 = Str_lit("return", 6ULL);
                                                                                                                (void)_t2622;
                                                                                                                Bool _t2623; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2622); _t2623 = *_hp; free(_hp); }
                                                                                                                (void)_t2623;
                                                                                                                Str_delete(_t2622, &(Bool){1});
                                                                                                                if (_t2623) {
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    Str_delete(_sw2605, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return TokenType_KwReturn();
                                                                                                                } else {
                                                                                                                    Str *_t2620 = Str_lit("throw", 5ULL);
                                                                                                                    (void)_t2620;
                                                                                                                    Bool _t2621; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2620); _t2621 = *_hp; free(_hp); }
                                                                                                                    (void)_t2621;
                                                                                                                    Str_delete(_t2620, &(Bool){1});
                                                                                                                    if (_t2621) {
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        Str_delete(_sw2605, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return TokenType_KwThrow();
                                                                                                                    } else {
                                                                                                                        Str *_t2618 = Str_lit("catch", 5ULL);
                                                                                                                        (void)_t2618;
                                                                                                                        Bool _t2619; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2618); _t2619 = *_hp; free(_hp); }
                                                                                                                        (void)_t2619;
                                                                                                                        Str_delete(_t2618, &(Bool){1});
                                                                                                                        if (_t2619) {
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            Str_delete(_sw2605, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return TokenType_KwCatch();
                                                                                                                        } else {
                                                                                                                            Str *_t2616 = Str_lit("break", 5ULL);
                                                                                                                            (void)_t2616;
                                                                                                                            Bool _t2617; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2616); _t2617 = *_hp; free(_hp); }
                                                                                                                            (void)_t2617;
                                                                                                                            Str_delete(_t2616, &(Bool){1});
                                                                                                                            if (_t2617) {
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                Str_delete(_sw2605, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return TokenType_KwBreak();
                                                                                                                            } else {
                                                                                                                                Str *_t2614 = Str_lit("continue", 8ULL);
                                                                                                                                (void)_t2614;
                                                                                                                                Bool _t2615; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2614); _t2615 = *_hp; free(_hp); }
                                                                                                                                (void)_t2615;
                                                                                                                                Str_delete(_t2614, &(Bool){1});
                                                                                                                                if (_t2615) {
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    Str_delete(_sw2605, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return TokenType_KwContinue();
                                                                                                                                } else {
                                                                                                                                    Str *_t2612 = Str_lit("defer", 5ULL);
                                                                                                                                    (void)_t2612;
                                                                                                                                    Bool _t2613; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2612); _t2613 = *_hp; free(_hp); }
                                                                                                                                    (void)_t2613;
                                                                                                                                    Str_delete(_t2612, &(Bool){1});
                                                                                                                                    if (_t2613) {
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        Str_delete(_sw2605, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return TokenType_KwDefer();
                                                                                                                                    } else {
                                                                                                                                        Str *_t2610 = Str_lit("true", 4ULL);
                                                                                                                                        (void)_t2610;
                                                                                                                                        Bool _t2611; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2610); _t2611 = *_hp; free(_hp); }
                                                                                                                                        (void)_t2611;
                                                                                                                                        Str_delete(_t2610, &(Bool){1});
                                                                                                                                        if (_t2611) {
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            Str_delete(_sw2605, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return TokenType_KwTrue();
                                                                                                                                        } else {
                                                                                                                                            Str *_t2608 = Str_lit("false", 5ULL);
                                                                                                                                            (void)_t2608;
                                                                                                                                            Bool _t2609; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2608); _t2609 = *_hp; free(_hp); }
                                                                                                                                            (void)_t2609;
                                                                                                                                            Str_delete(_t2608, &(Bool){1});
                                                                                                                                            if (_t2609) {
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                Str_delete(_sw2605, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return TokenType_KwFalse();
                                                                                                                                            } else {
                                                                                                                                                Str *_t2606 = Str_lit("NULL", 4ULL);
                                                                                                                                                (void)_t2606;
                                                                                                                                                Bool _t2607; { Bool *_hp = (Bool *)Str_eq(_sw2605, _t2606); _t2607 = *_hp; free(_hp); }
                                                                                                                                                (void)_t2607;
                                                                                                                                                Str_delete(_t2606, &(Bool){1});
                                                                                                                                                if (_t2607) {
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    Str_delete(_sw2605, &(Bool){1});
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
                                                                                                                                                    Str_delete(_sw2605, &(Bool){1});
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
        Str_delete(_sw2605, &(Bool){1});
        ;
    }
}

Vec * tokenize(Str * src, Str * path) {
    (void)src;
    (void)path;
    Str *_t3034 = Str_lit("Token", 5ULL);
    (void)_t3034;
    U64 _t3035; { U64 *_hp = (U64 *)Token_size(); _t3035 = *_hp; free(_hp); }
    (void)_t3035;
    Vec *tokens = Vec_new(_t3034, &(U64){_t3035});
    (void)tokens;
    Str_delete(_t3034, &(Bool){1});
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
        Bool _wcond2676; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2676 = *_hp; free(_hp); }
        (void)_wcond2676;
        if (_wcond2676) {
        } else {
            ;
            break;
        }
        ;
        U8 *c = Str_byte_at(src, pos);
        (void)c;
        U8 _t2978 = 32;
        (void)_t2978;
        U8 _t2979 = 9;
        (void)_t2979;
        Bool _t2980 = U8_eq(DEREF(c), _t2978);
        (void)_t2980;
        ;
        Bool _t2981 = U8_eq(DEREF(c), _t2979);
        (void)_t2981;
        ;
        U8 _t2982 = 13;
        (void)_t2982;
        Bool _t2983 = Bool_or(_t2980, _t2981);
        (void)_t2983;
        ;
        ;
        Bool _t2984 = U8_eq(DEREF(c), _t2982);
        (void)_t2984;
        ;
        U8 _t2985 = 59;
        (void)_t2985;
        Bool _t2986 = Bool_or(_t2983, _t2984);
        (void)_t2986;
        ;
        ;
        Bool _t2987 = U8_eq(DEREF(c), _t2985);
        (void)_t2987;
        ;
        Bool _t2988 = Bool_or(_t2986, _t2987);
        (void)_t2988;
        ;
        ;
        if (_t2988) {
            U64 _t2677 = U64_inc(DEREF(pos));
            (void)_t2677;
            *pos = _t2677;
            ;
            ;
            continue;
        }
        ;
        U8 _t2989 = 10;
        (void)_t2989;
        Bool _t2990 = U8_eq(DEREF(c), _t2989);
        (void)_t2990;
        ;
        if (_t2990) {
            U64 _t2678 = U64_inc(DEREF(pos));
            (void)_t2678;
            *pos = _t2678;
            ;
            U32 _t2679 = 1;
            (void)_t2679;
            U32 _t2680 = U32_add(line, _t2679);
            (void)_t2680;
            ;
            line = _t2680;
            ;
            U64 _t2681 = U64_clone(pos);
            (void)_t2681;
            line_start = _t2681;
            ;
            ;
            continue;
        }
        ;
        U64 _t2991 = U64_sub(DEREF(pos), line_start);
        (void)_t2991;
        U64 _t2992 = 1;
        (void)_t2992;
        U64 _t2993 = U64_add(_t2991, _t2992);
        (void)_t2993;
        ;
        ;
        I64 _t2994 = U64_to_i64(_t2993);
        (void)_t2994;
        ;
        U32 col = I64_to_u32(_t2994);
        (void)col;
        ;
        U64 start = U64_clone(pos);
        (void)start;
        U8 _t2995 = 35;
        (void)_t2995;
        Bool _t2996 = U8_eq(DEREF(c), _t2995);
        (void)_t2996;
        ;
        if (_t2996) {
            while (1) {
                Bool _wcond2682; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2682 = *_hp; free(_hp); }
                (void)_wcond2682;
                if (_wcond2682) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2683 = Str_byte_at(src, pos);
                (void)_t2683;
                U8 _t2684 = 10;
                (void)_t2684;
                Bool _t2685 = U8_eq(DEREF(_t2683), _t2684);
                (void)_t2685;
                ;
                if (_t2685) {
                    ;
                    break;
                }
                ;
                U64 _t2686 = U64_inc(DEREF(pos));
                (void)_t2686;
                *pos = _t2686;
                ;
            }
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t2997 = 47;
        (void)_t2997;
        U64 _t2998 = 1;
        (void)_t2998;
        U64 _t2999 = U64_add(DEREF(pos), _t2998);
        (void)_t2999;
        ;
        Bool _t3000 = U8_eq(DEREF(c), _t2997);
        (void)_t3000;
        ;
        Bool _t3001; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2999}, &(U64){src_len}); _t3001 = *_hp; free(_hp); }
        (void)_t3001;
        ;
        Bool _t3002 = Bool_and(_t3000, _t3001);
        (void)_t3002;
        ;
        ;
        if (_t3002) {
            U64 _t2745 = 1;
            (void)_t2745;
            U64 *_t2746 = malloc(sizeof(U64)); *_t2746 = U64_add(DEREF(pos), _t2745);
            (void)_t2746;
            ;
            U8 *c2 = Str_byte_at(src, _t2746);
            (void)c2;
            U8 _t2747 = 47;
            (void)_t2747;
            Bool _t2748 = U8_eq(DEREF(c2), _t2747);
            (void)_t2748;
            ;
            if (_t2748) {
                while (1) {
                    Bool _wcond2687; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2687 = *_hp; free(_hp); }
                    (void)_wcond2687;
                    if (_wcond2687) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U8 *_t2688 = Str_byte_at(src, pos);
                    (void)_t2688;
                    U8 _t2689 = 10;
                    (void)_t2689;
                    Bool _t2690 = U8_eq(DEREF(_t2688), _t2689);
                    (void)_t2690;
                    ;
                    if (_t2690) {
                        ;
                        break;
                    }
                    ;
                    U64 _t2691 = U64_inc(DEREF(pos));
                    (void)_t2691;
                    *pos = _t2691;
                    ;
                }
                U64_delete(_t2746, &(Bool){1});
                ;
                ;
                ;
                ;
                continue;
            }
            ;
            U8 _t2749 = 42;
            (void)_t2749;
            Bool _t2750 = U8_eq(DEREF(c2), _t2749);
            (void)_t2750;
            U64_delete(_t2746, &(Bool){1});
            ;
            if (_t2750) {
                U64 _t2741 = 2;
                (void)_t2741;
                U64 _t2742 = U64_add(DEREF(pos), _t2741);
                (void)_t2742;
                ;
                *pos = _t2742;
                ;
                I64 depth = 1;
                (void)depth;
                while (1) {
                    Bool _wcond2692; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2692 = *_hp; free(_hp); }
                    (void)_wcond2692;
                    if (_wcond2692) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    I64 _t2717 = 0;
                    (void)_t2717;
                    Bool _t2718; { Bool *_hp = (Bool *)I64_lte(&(I64){depth}, &(I64){_t2717}); _t2718 = *_hp; free(_hp); }
                    (void)_t2718;
                    ;
                    if (_t2718) {
                        ;
                        break;
                    }
                    ;
                    U64 _t2719 = 1;
                    (void)_t2719;
                    U64 _t2720 = U64_add(DEREF(pos), _t2719);
                    (void)_t2720;
                    ;
                    Bool _t2721; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2720}, &(U64){src_len}); _t2721 = *_hp; free(_hp); }
                    (void)_t2721;
                    ;
                    if (_t2721) {
                        U8 *b1 = Str_byte_at(src, pos);
                        (void)b1;
                        U64 _t2701 = 1;
                        (void)_t2701;
                        U64 *_t2702 = malloc(sizeof(U64)); *_t2702 = U64_add(DEREF(pos), _t2701);
                        (void)_t2702;
                        ;
                        U8 *b2 = Str_byte_at(src, _t2702);
                        (void)b2;
                        U8 _t2703 = 47;
                        (void)_t2703;
                        U8 _t2704 = 42;
                        (void)_t2704;
                        Bool _t2705 = U8_eq(DEREF(b1), _t2703);
                        (void)_t2705;
                        ;
                        Bool _t2706 = U8_eq(DEREF(b2), _t2704);
                        (void)_t2706;
                        ;
                        Bool _t2707 = Bool_and(_t2705, _t2706);
                        (void)_t2707;
                        ;
                        ;
                        if (_t2707) {
                            I64 _t2693 = 1;
                            (void)_t2693;
                            I64 _t2694 = I64_add(depth, _t2693);
                            (void)_t2694;
                            ;
                            depth = _t2694;
                            ;
                            U64 _t2695 = 2;
                            (void)_t2695;
                            U64 _t2696 = U64_add(DEREF(pos), _t2695);
                            (void)_t2696;
                            ;
                            *pos = _t2696;
                            ;
                            U64_delete(_t2702, &(Bool){1});
                            ;
                            ;
                            continue;
                        }
                        ;
                        U8 _t2708 = 42;
                        (void)_t2708;
                        U8 _t2709 = 47;
                        (void)_t2709;
                        Bool _t2710 = U8_eq(DEREF(b1), _t2708);
                        (void)_t2710;
                        ;
                        Bool _t2711 = U8_eq(DEREF(b2), _t2709);
                        (void)_t2711;
                        U64_delete(_t2702, &(Bool){1});
                        ;
                        Bool _t2712 = Bool_and(_t2710, _t2711);
                        (void)_t2712;
                        ;
                        ;
                        if (_t2712) {
                            I64 _t2697 = 1;
                            (void)_t2697;
                            I64 _t2698 = I64_sub(depth, _t2697);
                            (void)_t2698;
                            ;
                            depth = _t2698;
                            ;
                            U64 _t2699 = 2;
                            (void)_t2699;
                            U64 _t2700 = U64_add(DEREF(pos), _t2699);
                            (void)_t2700;
                            ;
                            *pos = _t2700;
                            ;
                            ;
                            ;
                            continue;
                        }
                        ;
                    }
                    ;
                    U8 *_t2722 = Str_byte_at(src, pos);
                    (void)_t2722;
                    U8 _t2723 = 10;
                    (void)_t2723;
                    Bool _t2724 = U8_eq(DEREF(_t2722), _t2723);
                    (void)_t2724;
                    ;
                    if (_t2724) {
                        U32 _t2713 = 1;
                        (void)_t2713;
                        U32 _t2714 = U32_add(line, _t2713);
                        (void)_t2714;
                        ;
                        line = _t2714;
                        ;
                        U64 _t2715 = 1;
                        (void)_t2715;
                        U64 _t2716 = U64_add(DEREF(pos), _t2715);
                        (void)_t2716;
                        ;
                        line_start = _t2716;
                        ;
                    }
                    ;
                    U64 _t2725 = U64_inc(DEREF(pos));
                    (void)_t2725;
                    *pos = _t2725;
                    ;
                }
                I64 _t2743 = 0;
                (void)_t2743;
                Bool _t2744; { Bool *_hp = (Bool *)I64_gt(&(I64){depth}, &(I64){_t2743}); _t2744 = *_hp; free(_hp); }
                (void)_t2744;
                ;
                ;
                if (_t2744) {
                    Str *_t2726 = Str_lit("Str", 3ULL);
                    (void)_t2726;
                    U64 _t2727; { U64 *_hp = (U64 *)Str_size(); _t2727 = *_hp; free(_hp); }
                    (void)_t2727;
                    U64 _t2728 = 6;
                    (void)_t2728;
                    Array *_va50 = Array_new(_t2726, &(U64){_t2727}, &(U64){_t2728});
                    (void)_va50;
                    Str_delete(_t2726, &(Bool){1});
                    ;
                    ;
                    U64 _t2729 = 0;
                    (void)_t2729;
                    Str *_t2730 = Str_clone(path);
                    (void)_t2730;
                    Array_set(_va50, &(U64){_t2729}, _t2730);
                    ;
                    U64 _t2731 = 1;
                    (void)_t2731;
                    Str *_t2732 = Str_lit(":", 1ULL);
                    (void)_t2732;
                    Array_set(_va50, &(U64){_t2731}, _t2732);
                    ;
                    U64 _t2733 = 2;
                    (void)_t2733;
                    Str *_t2734 = U32_to_str(&(U32){line});
                    (void)_t2734;
                    Array_set(_va50, &(U64){_t2733}, _t2734);
                    ;
                    U64 _t2735 = 3;
                    (void)_t2735;
                    Str *_t2736 = Str_lit(":", 1ULL);
                    (void)_t2736;
                    Array_set(_va50, &(U64){_t2735}, _t2736);
                    ;
                    U64 _t2737 = 4;
                    (void)_t2737;
                    Str *_t2738 = U32_to_str(&(U32){col});
                    (void)_t2738;
                    Array_set(_va50, &(U64){_t2737}, _t2738);
                    ;
                    U64 _t2739 = 5;
                    (void)_t2739;
                    Str *_t2740 = Str_lit(": error: unterminated comment", 29ULL);
                    (void)_t2740;
                    Array_set(_va50, &(U64){_t2739}, _t2740);
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
        Bool _t3003; { Bool *_hp = (Bool *)is_digit(c); _t3003 = *_hp; free(_hp); }
        (void)_t3003;
        if (_t3003) {
            while (1) {
                Bool _wcond2751; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2751 = *_hp; free(_hp); }
                (void)_wcond2751;
                if (_wcond2751) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2752 = Str_byte_at(src, pos);
                (void)_t2752;
                Bool _t2753; { Bool *_hp = (Bool *)is_digit(_t2752); _t2753 = *_hp; free(_hp); }
                (void)_t2753;
                Bool _t2754 = Bool_not(_t2753);
                (void)_t2754;
                ;
                if (_t2754) {
                    ;
                    break;
                }
                ;
                U64 _t2755 = U64_inc(DEREF(pos));
                (void)_t2755;
                *pos = _t2755;
                ;
            }
            U64 _t2770 = 1;
            (void)_t2770;
            U64 _t2771 = U64_add(DEREF(pos), _t2770);
            (void)_t2771;
            ;
            Bool _t2772; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2771}, &(U64){src_len}); _t2772 = *_hp; free(_hp); }
            (void)_t2772;
            ;
            if (_t2772) {
                U8 *_t2762 = Str_byte_at(src, pos);
                (void)_t2762;
                U8 _t2763 = 46;
                (void)_t2763;
                U64 _t2764 = 1;
                (void)_t2764;
                U64 *_t2765 = malloc(sizeof(U64)); *_t2765 = U64_add(DEREF(pos), _t2764);
                (void)_t2765;
                ;
                U8 *_t2766 = Str_byte_at(src, _t2765);
                (void)_t2766;
                Bool _t2767 = U8_eq(DEREF(_t2762), _t2763);
                (void)_t2767;
                ;
                Bool _t2768; { Bool *_hp = (Bool *)is_digit(_t2766); _t2768 = *_hp; free(_hp); }
                (void)_t2768;
                U64_delete(_t2765, &(Bool){1});
                Bool _t2769 = Bool_and(_t2767, _t2768);
                (void)_t2769;
                ;
                ;
                if (_t2769) {
                    U64 _t2761 = U64_inc(DEREF(pos));
                    (void)_t2761;
                    *pos = _t2761;
                    ;
                    while (1) {
                        Bool _wcond2756; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2756 = *_hp; free(_hp); }
                        (void)_wcond2756;
                        if (_wcond2756) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U8 *_t2757 = Str_byte_at(src, pos);
                        (void)_t2757;
                        Bool _t2758; { Bool *_hp = (Bool *)is_digit(_t2757); _t2758 = *_hp; free(_hp); }
                        (void)_t2758;
                        Bool _t2759 = Bool_not(_t2758);
                        (void)_t2759;
                        ;
                        if (_t2759) {
                            ;
                            break;
                        }
                        ;
                        U64 _t2760 = U64_inc(DEREF(pos));
                        (void)_t2760;
                        *pos = _t2760;
                        ;
                    }
                }
                ;
            }
            ;
            U64 _t2773 = U64_sub(DEREF(pos), start);
            (void)_t2773;
            Str *_t2774 = Str_substr(src, &(U64){start}, &(U64){_t2773});
            (void)_t2774;
            ;
            U32 _t2775 = U32_clone(&(U32){col});
            (void)_t2775;
            Token *_t2776 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(TokenType_Number()); _t2776->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(_t2774); _t2776->text = *_ca; free(_ca); }
            _t2776->line = U32_clone(&(U32){line});
            _t2776->col = _t2775;
            (void)_t2776;
            Str_delete(_t2774, &(Bool){1});
            ;
            Vec_push(tokens, _t2776);
            ;
            ;
            ;
            continue;
        }
        ;
        Bool _t3004; { Bool *_hp = (Bool *)is_alpha(c); _t3004 = *_hp; free(_hp); }
        (void)_t3004;
        if (_t3004) {
            while (1) {
                Bool _wcond2777; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2777 = *_hp; free(_hp); }
                (void)_wcond2777;
                if (_wcond2777) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2778 = Str_byte_at(src, pos);
                (void)_t2778;
                Bool _t2779; { Bool *_hp = (Bool *)is_alnum(_t2778); _t2779 = *_hp; free(_hp); }
                (void)_t2779;
                Bool _t2780 = Bool_not(_t2779);
                (void)_t2780;
                ;
                if (_t2780) {
                    ;
                    break;
                }
                ;
                U64 _t2781 = U64_inc(DEREF(pos));
                (void)_t2781;
                *pos = _t2781;
                ;
            }
            U64 _t2782 = U64_sub(DEREF(pos), start);
            (void)_t2782;
            Str *word = Str_substr(src, &(U64){start}, &(U64){_t2782});
            (void)word;
            ;
            TokenType *type = lookup_keyword(word);
            (void)type;
            U32 _t2783 = U32_clone(&(U32){line});
            (void)_t2783;
            U32 _t2784 = U32_clone(&(U32){col});
            (void)_t2784;
            Token *_t2785 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(type); _t2785->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(word); _t2785->text = *_ca; free(_ca); }
            _t2785->line = _t2783;
            _t2785->col = _t2784;
            (void)_t2785;
            ;
            ;
            TokenType_delete(type, &(Bool){1});
            Str_delete(word, &(Bool){1});
            Vec_push(tokens, _t2785);
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t3005 = 34;
        (void)_t3005;
        Bool _t3006 = U8_eq(DEREF(c), _t3005);
        (void)_t3006;
        ;
        if (_t3006) {
            U64 _t2834 = U64_inc(DEREF(pos));
            (void)_t2834;
            *pos = _t2834;
            ;
            while (1) {
                Bool _wcond2786; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2786 = *_hp; free(_hp); }
                (void)_wcond2786;
                if (_wcond2786) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2792 = Str_byte_at(src, pos);
                (void)_t2792;
                U8 _t2793 = 34;
                (void)_t2793;
                Bool _t2794 = U8_eq(DEREF(_t2792), _t2793);
                (void)_t2794;
                ;
                if (_t2794) {
                    ;
                    break;
                }
                ;
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
                Bool _t2801 = Bool_and(_t2799, _t2800);
                (void)_t2801;
                ;
                ;
                if (_t2801) {
                    U64 _t2787 = U64_inc(DEREF(pos));
                    (void)_t2787;
                    *pos = _t2787;
                    ;
                }
                ;
                U8 *_t2802 = Str_byte_at(src, pos);
                (void)_t2802;
                U8 _t2803 = 10;
                (void)_t2803;
                Bool _t2804 = U8_eq(DEREF(_t2802), _t2803);
                (void)_t2804;
                ;
                if (_t2804) {
                    U32 _t2788 = 1;
                    (void)_t2788;
                    U32 _t2789 = U32_add(line, _t2788);
                    (void)_t2789;
                    ;
                    line = _t2789;
                    ;
                    U64 _t2790 = 1;
                    (void)_t2790;
                    U64 _t2791 = U64_add(DEREF(pos), _t2790);
                    (void)_t2791;
                    ;
                    line_start = _t2791;
                    ;
                }
                ;
                U64 _t2805 = U64_inc(DEREF(pos));
                (void)_t2805;
                *pos = _t2805;
                ;
            }
            U8 *_t2835 = Str_byte_at(src, pos);
            (void)_t2835;
            U8 _t2836 = 34;
            (void)_t2836;
            Bool _t2837; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2837 = *_hp; free(_hp); }
            (void)_t2837;
            Bool _t2838 = U8_eq(DEREF(_t2835), _t2836);
            (void)_t2838;
            ;
            Bool _t2839 = Bool_and(_t2837, _t2838);
            (void)_t2839;
            ;
            ;
            if (_t2839) {
                U64 _t2806 = U64_inc(DEREF(pos));
                (void)_t2806;
                *pos = _t2806;
                ;
                U64 _t2807 = 1;
                (void)_t2807;
                U64 _t2808 = U64_sub(DEREF(pos), start);
                (void)_t2808;
                U64 _t2809 = 2;
                (void)_t2809;
                U64 _t2810 = U64_add(start, _t2807);
                (void)_t2810;
                ;
                U64 _t2811 = U64_sub(_t2808, _t2809);
                (void)_t2811;
                ;
                ;
                Str *_t2812 = Str_substr(src, &(U64){_t2810}, &(U64){_t2811});
                (void)_t2812;
                ;
                ;
                U32 _t2813 = U32_clone(&(U32){col});
                (void)_t2813;
                Token *_t2814 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_StringTok()); _t2814->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2812); _t2814->text = *_ca; free(_ca); }
                _t2814->line = U32_clone(&(U32){line});
                _t2814->col = _t2813;
                (void)_t2814;
                Str_delete(_t2812, &(Bool){1});
                ;
                Vec_push(tokens, _t2814);
            } else {
                Str *_t2815 = Str_lit("Str", 3ULL);
                (void)_t2815;
                U64 _t2816; { U64 *_hp = (U64 *)Str_size(); _t2816 = *_hp; free(_hp); }
                (void)_t2816;
                U64 _t2817 = 6;
                (void)_t2817;
                Array *_va51 = Array_new(_t2815, &(U64){_t2816}, &(U64){_t2817});
                (void)_va51;
                Str_delete(_t2815, &(Bool){1});
                ;
                ;
                U64 _t2818 = 0;
                (void)_t2818;
                Str *_t2819 = Str_clone(path);
                (void)_t2819;
                Array_set(_va51, &(U64){_t2818}, _t2819);
                ;
                U64 _t2820 = 1;
                (void)_t2820;
                Str *_t2821 = Str_lit(":", 1ULL);
                (void)_t2821;
                Array_set(_va51, &(U64){_t2820}, _t2821);
                ;
                U64 _t2822 = 2;
                (void)_t2822;
                Str *_t2823 = U32_to_str(&(U32){line});
                (void)_t2823;
                Array_set(_va51, &(U64){_t2822}, _t2823);
                ;
                U64 _t2824 = 3;
                (void)_t2824;
                Str *_t2825 = Str_lit(":", 1ULL);
                (void)_t2825;
                Array_set(_va51, &(U64){_t2824}, _t2825);
                ;
                U64 _t2826 = 4;
                (void)_t2826;
                Str *_t2827 = U32_to_str(&(U32){col});
                (void)_t2827;
                Array_set(_va51, &(U64){_t2826}, _t2827);
                ;
                U64 _t2828 = 5;
                (void)_t2828;
                Str *_t2829 = Str_lit(": error: unterminated string", 28ULL);
                (void)_t2829;
                Array_set(_va51, &(U64){_t2828}, _t2829);
                ;
                println(_va51);
                U64 _t2830 = U64_sub(DEREF(pos), start);
                (void)_t2830;
                Str *_t2831 = Str_substr(src, &(U64){start}, &(U64){_t2830});
                (void)_t2831;
                ;
                U32 _t2832 = U32_clone(&(U32){col});
                (void)_t2832;
                Token *_t2833 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2833->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2831); _t2833->text = *_ca; free(_ca); }
                _t2833->line = U32_clone(&(U32){line});
                _t2833->col = _t2832;
                (void)_t2833;
                Str_delete(_t2831, &(Bool){1});
                ;
                Vec_push(tokens, _t2833);
            }
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t3007 = 39;
        (void)_t3007;
        Bool _t3008 = U8_eq(DEREF(c), _t3007);
        (void)_t3008;
        ;
        if (_t3008) {
            U64 _t2865 = U64_inc(DEREF(pos));
            (void)_t2865;
            *pos = _t2865;
            ;
            U64 ch_start = U64_clone(pos);
            (void)ch_start;
            U8 *_t2866 = Str_byte_at(src, pos);
            (void)_t2866;
            U8 _t2867 = 92;
            (void)_t2867;
            U64 _t2868 = 1;
            (void)_t2868;
            U64 _t2869 = U64_add(DEREF(pos), _t2868);
            (void)_t2869;
            ;
            Bool _t2870 = U8_eq(DEREF(_t2866), _t2867);
            (void)_t2870;
            ;
            Bool _t2871; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2869}, &(U64){src_len}); _t2871 = *_hp; free(_hp); }
            (void)_t2871;
            ;
            Bool _t2872; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2872 = *_hp; free(_hp); }
            (void)_t2872;
            Bool _t2873 = Bool_and(_t2870, _t2871);
            (void)_t2873;
            ;
            ;
            Bool _t2874 = Bool_and(_t2872, _t2873);
            (void)_t2874;
            ;
            ;
            if (_t2874) {
                U64 _t2840 = U64_inc(DEREF(pos));
                (void)_t2840;
                *pos = _t2840;
                ;
            }
            ;
            U64 _t2875 = U64_inc(DEREF(pos));
            (void)_t2875;
            *pos = _t2875;
            ;
            U8 *_t2876 = Str_byte_at(src, pos);
            (void)_t2876;
            U8 _t2877 = 39;
            (void)_t2877;
            Bool _t2878; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2878 = *_hp; free(_hp); }
            (void)_t2878;
            Bool _t2879 = U8_eq(DEREF(_t2876), _t2877);
            (void)_t2879;
            ;
            Bool _t2880 = Bool_and(_t2878, _t2879);
            (void)_t2880;
            ;
            ;
            if (_t2880) {
                U64 _t2841 = U64_sub(DEREF(pos), ch_start);
                (void)_t2841;
                Str *_t2842 = Str_substr(src, &(U64){ch_start}, &(U64){_t2841});
                (void)_t2842;
                ;
                U32 _t2843 = U32_clone(&(U32){col});
                (void)_t2843;
                Token *_t2844 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Char()); _t2844->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2842); _t2844->text = *_ca; free(_ca); }
                _t2844->line = U32_clone(&(U32){line});
                _t2844->col = _t2843;
                (void)_t2844;
                Str_delete(_t2842, &(Bool){1});
                ;
                Vec_push(tokens, _t2844);
                U64 _t2845 = U64_inc(DEREF(pos));
                (void)_t2845;
                *pos = _t2845;
                ;
            } else {
                Str *_t2846 = Str_lit("Str", 3ULL);
                (void)_t2846;
                U64 _t2847; { U64 *_hp = (U64 *)Str_size(); _t2847 = *_hp; free(_hp); }
                (void)_t2847;
                U64 _t2848 = 6;
                (void)_t2848;
                Array *_va52 = Array_new(_t2846, &(U64){_t2847}, &(U64){_t2848});
                (void)_va52;
                Str_delete(_t2846, &(Bool){1});
                ;
                ;
                U64 _t2849 = 0;
                (void)_t2849;
                Str *_t2850 = Str_clone(path);
                (void)_t2850;
                Array_set(_va52, &(U64){_t2849}, _t2850);
                ;
                U64 _t2851 = 1;
                (void)_t2851;
                Str *_t2852 = Str_lit(":", 1ULL);
                (void)_t2852;
                Array_set(_va52, &(U64){_t2851}, _t2852);
                ;
                U64 _t2853 = 2;
                (void)_t2853;
                Str *_t2854 = U32_to_str(&(U32){line});
                (void)_t2854;
                Array_set(_va52, &(U64){_t2853}, _t2854);
                ;
                U64 _t2855 = 3;
                (void)_t2855;
                Str *_t2856 = Str_lit(":", 1ULL);
                (void)_t2856;
                Array_set(_va52, &(U64){_t2855}, _t2856);
                ;
                U64 _t2857 = 4;
                (void)_t2857;
                Str *_t2858 = U32_to_str(&(U32){col});
                (void)_t2858;
                Array_set(_va52, &(U64){_t2857}, _t2858);
                ;
                U64 _t2859 = 5;
                (void)_t2859;
                Str *_t2860 = Str_lit(": error: unterminated character literal", 39ULL);
                (void)_t2860;
                Array_set(_va52, &(U64){_t2859}, _t2860);
                ;
                println(_va52);
                U64 _t2861 = U64_sub(DEREF(pos), start);
                (void)_t2861;
                Str *_t2862 = Str_substr(src, &(U64){start}, &(U64){_t2861});
                (void)_t2862;
                ;
                U32 _t2863 = U32_clone(&(U32){col});
                (void)_t2863;
                Token *_t2864 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2864->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2862); _t2864->text = *_ca; free(_ca); }
                _t2864->line = U32_clone(&(U32){line});
                _t2864->col = _t2863;
                (void)_t2864;
                Str_delete(_t2862, &(Bool){1});
                ;
                Vec_push(tokens, _t2864);
            }
            ;
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U64 _t3009 = 1;
        (void)_t3009;
        U64 _t3010 = U64_add(DEREF(pos), _t3009);
        (void)_t3010;
        ;
        Bool _t3011; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3010}, &(U64){src_len}); _t3011 = *_hp; free(_hp); }
        (void)_t3011;
        ;
        if (_t3011) {
            U64 _t2926 = 1;
            (void)_t2926;
            U64 *_t2927 = malloc(sizeof(U64)); *_t2927 = U64_add(DEREF(pos), _t2926);
            (void)_t2927;
            ;
            U8 *c2 = Str_byte_at(src, _t2927);
            (void)c2;
            TokenType *two = TokenType_clone(TokenType_Eof());
            (void)two;
            U8 _t2928 = 58;
            (void)_t2928;
            U8 _t2929 = 61;
            (void)_t2929;
            Bool _t2930 = U8_eq(DEREF(c), _t2928);
            (void)_t2930;
            ;
            Bool _t2931 = U8_eq(DEREF(c2), _t2929);
            (void)_t2931;
            ;
            Bool _t2932 = Bool_and(_t2930, _t2931);
            (void)_t2932;
            ;
            ;
            if (_t2932) {
                two = TokenType_clone(TokenType_ColonEq());
            } else {
                U8 _t2914 = 61;
                (void)_t2914;
                U8 _t2915 = 61;
                (void)_t2915;
                Bool _t2916 = U8_eq(DEREF(c), _t2914);
                (void)_t2916;
                ;
                Bool _t2917 = U8_eq(DEREF(c2), _t2915);
                (void)_t2917;
                ;
                Bool _t2918 = Bool_and(_t2916, _t2917);
                (void)_t2918;
                ;
                ;
                if (_t2918) {
                    two = TokenType_clone(TokenType_EqEq());
                } else {
                    U8 _t2909 = 33;
                    (void)_t2909;
                    U8 _t2910 = 61;
                    (void)_t2910;
                    Bool _t2911 = U8_eq(DEREF(c), _t2909);
                    (void)_t2911;
                    ;
                    Bool _t2912 = U8_eq(DEREF(c2), _t2910);
                    (void)_t2912;
                    ;
                    Bool _t2913 = Bool_and(_t2911, _t2912);
                    (void)_t2913;
                    ;
                    ;
                    if (_t2913) {
                        two = TokenType_clone(TokenType_Neq());
                    } else {
                        U8 _t2904 = 60;
                        (void)_t2904;
                        U8 _t2905 = 61;
                        (void)_t2905;
                        Bool _t2906 = U8_eq(DEREF(c), _t2904);
                        (void)_t2906;
                        ;
                        Bool _t2907 = U8_eq(DEREF(c2), _t2905);
                        (void)_t2907;
                        ;
                        Bool _t2908 = Bool_and(_t2906, _t2907);
                        (void)_t2908;
                        ;
                        ;
                        if (_t2908) {
                            two = TokenType_clone(TokenType_LtEq());
                        } else {
                            U8 _t2899 = 62;
                            (void)_t2899;
                            U8 _t2900 = 61;
                            (void)_t2900;
                            Bool _t2901 = U8_eq(DEREF(c), _t2899);
                            (void)_t2901;
                            ;
                            Bool _t2902 = U8_eq(DEREF(c2), _t2900);
                            (void)_t2902;
                            ;
                            Bool _t2903 = Bool_and(_t2901, _t2902);
                            (void)_t2903;
                            ;
                            ;
                            if (_t2903) {
                                two = TokenType_clone(TokenType_GtEq());
                            } else {
                                U8 _t2894 = 46;
                                (void)_t2894;
                                U8 _t2895 = 46;
                                (void)_t2895;
                                Bool _t2896 = U8_eq(DEREF(c), _t2894);
                                (void)_t2896;
                                ;
                                Bool _t2897 = U8_eq(DEREF(c2), _t2895);
                                (void)_t2897;
                                ;
                                Bool _t2898 = Bool_and(_t2896, _t2897);
                                (void)_t2898;
                                ;
                                ;
                                if (_t2898) {
                                    U64 _t2891 = 2;
                                    (void)_t2891;
                                    U64 _t2892 = U64_add(DEREF(pos), _t2891);
                                    (void)_t2892;
                                    ;
                                    Bool _t2893; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2892}, &(U64){src_len}); _t2893 = *_hp; free(_hp); }
                                    (void)_t2893;
                                    ;
                                    if (_t2893) {
                                        U64 _t2887 = 2;
                                        (void)_t2887;
                                        U64 *_t2888 = malloc(sizeof(U64)); *_t2888 = U64_add(DEREF(pos), _t2887);
                                        (void)_t2888;
                                        ;
                                        U8 *c3 = Str_byte_at(src, _t2888);
                                        (void)c3;
                                        U8 _t2889 = 46;
                                        (void)_t2889;
                                        Bool _t2890 = U8_eq(DEREF(c3), _t2889);
                                        (void)_t2890;
                                        U64_delete(_t2888, &(Bool){1});
                                        ;
                                        if (_t2890) {
                                            U64 _t2881 = 3;
                                            (void)_t2881;
                                            Str *_t2882 = Str_substr(src, &(U64){start}, &(U64){_t2881});
                                            (void)_t2882;
                                            ;
                                            U32 _t2883 = U32_clone(&(U32){col});
                                            (void)_t2883;
                                            Token *_t2884 = malloc(sizeof(Token));
                                            { TokenType *_ca = TokenType_clone(TokenType_DotDotDot()); _t2884->type = *_ca; free(_ca); }
                                            { Str *_ca = Str_clone(_t2882); _t2884->text = *_ca; free(_ca); }
                                            _t2884->line = U32_clone(&(U32){line});
                                            _t2884->col = _t2883;
                                            (void)_t2884;
                                            Str_delete(_t2882, &(Bool){1});
                                            ;
                                            Vec_push(tokens, _t2884);
                                            U64 _t2885 = 3;
                                            (void)_t2885;
                                            U64 _t2886 = U64_add(DEREF(pos), _t2885);
                                            (void)_t2886;
                                            ;
                                            *pos = _t2886;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            U64_delete(_t2927, &(Bool){1});
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
            U64_delete(_t2927, &(Bool){1});
            ;
            Bool _t2933; { Bool *_hp = (Bool *)TokenType_eq(two, TokenType_Eof()); _t2933 = *_hp; free(_hp); }
            (void)_t2933;
            Bool _t2934 = Bool_not(_t2933);
            (void)_t2934;
            ;
            if (_t2934) {
                U64 _t2919 = 2;
                (void)_t2919;
                Str *_t2920 = Str_substr(src, &(U64){start}, &(U64){_t2919});
                (void)_t2920;
                ;
                U32 _t2921 = U32_clone(&(U32){line});
                (void)_t2921;
                U32 _t2922 = U32_clone(&(U32){col});
                (void)_t2922;
                Token *_t2923 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(two); _t2923->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2920); _t2923->text = *_ca; free(_ca); }
                _t2923->line = _t2921;
                _t2923->col = _t2922;
                (void)_t2923;
                Str_delete(_t2920, &(Bool){1});
                ;
                ;
                Vec_push(tokens, _t2923);
                U64 _t2924 = 2;
                (void)_t2924;
                U64 _t2925 = U64_add(DEREF(pos), _t2924);
                (void)_t2925;
                ;
                *pos = _t2925;
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
            U8 _sw2935 = U8_clone(c);
            (void)_sw2935;
            U8 _t2970 = 40;
            (void)_t2970;
            Bool _t2971 = U8_eq(_sw2935, _t2970);
            (void)_t2971;
            ;
            if (_t2971) {
                single = TokenType_clone(TokenType_LParen());
            } else {
                U8 _t2968 = 41;
                (void)_t2968;
                Bool _t2969 = U8_eq(_sw2935, _t2968);
                (void)_t2969;
                ;
                if (_t2969) {
                    single = TokenType_clone(TokenType_RParen());
                } else {
                    U8 _t2966 = 123;
                    (void)_t2966;
                    Bool _t2967 = U8_eq(_sw2935, _t2966);
                    (void)_t2967;
                    ;
                    if (_t2967) {
                        single = TokenType_clone(TokenType_LBrace());
                    } else {
                        U8 _t2964 = 125;
                        (void)_t2964;
                        Bool _t2965 = U8_eq(_sw2935, _t2964);
                        (void)_t2965;
                        ;
                        if (_t2965) {
                            single = TokenType_clone(TokenType_RBrace());
                        } else {
                            U8 _t2962 = 91;
                            (void)_t2962;
                            Bool _t2963 = U8_eq(_sw2935, _t2962);
                            (void)_t2963;
                            ;
                            if (_t2963) {
                                single = TokenType_clone(TokenType_LBracket());
                            } else {
                                U8 _t2960 = 93;
                                (void)_t2960;
                                Bool _t2961 = U8_eq(_sw2935, _t2960);
                                (void)_t2961;
                                ;
                                if (_t2961) {
                                    single = TokenType_clone(TokenType_RBracket());
                                } else {
                                    U8 _t2958 = 44;
                                    (void)_t2958;
                                    Bool _t2959 = U8_eq(_sw2935, _t2958);
                                    (void)_t2959;
                                    ;
                                    if (_t2959) {
                                        single = TokenType_clone(TokenType_Comma());
                                    } else {
                                        U8 _t2956 = 58;
                                        (void)_t2956;
                                        Bool _t2957 = U8_eq(_sw2935, _t2956);
                                        (void)_t2957;
                                        ;
                                        if (_t2957) {
                                            single = TokenType_clone(TokenType_Colon());
                                        } else {
                                            U8 _t2954 = 46;
                                            (void)_t2954;
                                            Bool _t2955 = U8_eq(_sw2935, _t2954);
                                            (void)_t2955;
                                            ;
                                            if (_t2955) {
                                                single = TokenType_clone(TokenType_Dot());
                                            } else {
                                                U8 _t2952 = 63;
                                                (void)_t2952;
                                                Bool _t2953 = U8_eq(_sw2935, _t2952);
                                                (void)_t2953;
                                                ;
                                                if (_t2953) {
                                                    single = TokenType_clone(TokenType_Question());
                                                } else {
                                                    U8 _t2950 = 33;
                                                    (void)_t2950;
                                                    Bool _t2951 = U8_eq(_sw2935, _t2950);
                                                    (void)_t2951;
                                                    ;
                                                    if (_t2951) {
                                                        single = TokenType_clone(TokenType_Bang());
                                                    } else {
                                                        U8 _t2948 = 43;
                                                        (void)_t2948;
                                                        Bool _t2949 = U8_eq(_sw2935, _t2948);
                                                        (void)_t2949;
                                                        ;
                                                        if (_t2949) {
                                                            single = TokenType_clone(TokenType_Plus());
                                                        } else {
                                                            U8 _t2946 = 45;
                                                            (void)_t2946;
                                                            Bool _t2947 = U8_eq(_sw2935, _t2946);
                                                            (void)_t2947;
                                                            ;
                                                            if (_t2947) {
                                                                single = TokenType_clone(TokenType_Minus());
                                                            } else {
                                                                U8 _t2944 = 42;
                                                                (void)_t2944;
                                                                Bool _t2945 = U8_eq(_sw2935, _t2944);
                                                                (void)_t2945;
                                                                ;
                                                                if (_t2945) {
                                                                    single = TokenType_clone(TokenType_Star());
                                                                } else {
                                                                    U8 _t2942 = 47;
                                                                    (void)_t2942;
                                                                    Bool _t2943 = U8_eq(_sw2935, _t2942);
                                                                    (void)_t2943;
                                                                    ;
                                                                    if (_t2943) {
                                                                        single = TokenType_clone(TokenType_Slash());
                                                                    } else {
                                                                        U8 _t2940 = 61;
                                                                        (void)_t2940;
                                                                        Bool _t2941 = U8_eq(_sw2935, _t2940);
                                                                        (void)_t2941;
                                                                        ;
                                                                        if (_t2941) {
                                                                            single = TokenType_clone(TokenType_Eq());
                                                                        } else {
                                                                            U8 _t2938 = 60;
                                                                            (void)_t2938;
                                                                            Bool _t2939 = U8_eq(_sw2935, _t2938);
                                                                            (void)_t2939;
                                                                            ;
                                                                            if (_t2939) {
                                                                                single = TokenType_clone(TokenType_Lt());
                                                                            } else {
                                                                                U8 _t2936 = 62;
                                                                                (void)_t2936;
                                                                                Bool _t2937 = U8_eq(_sw2935, _t2936);
                                                                                (void)_t2937;
                                                                                ;
                                                                                if (_t2937) {
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
        Bool _t3012; { Bool *_hp = (Bool *)TokenType_eq(single, TokenType_Eof()); _t3012 = *_hp; free(_hp); }
        (void)_t3012;
        Bool _t3013 = Bool_not(_t3012);
        (void)_t3013;
        ;
        if (_t3013) {
            U64 _t2972 = 1;
            (void)_t2972;
            Str *_t2973 = Str_substr(src, &(U64){start}, &(U64){_t2972});
            (void)_t2973;
            ;
            U32 _t2974 = U32_clone(&(U32){line});
            (void)_t2974;
            U32 _t2975 = U32_clone(&(U32){col});
            (void)_t2975;
            Token *_t2976 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(single); _t2976->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(_t2973); _t2976->text = *_ca; free(_ca); }
            _t2976->line = _t2974;
            _t2976->col = _t2975;
            (void)_t2976;
            Str_delete(_t2973, &(Bool){1});
            ;
            ;
            Vec_push(tokens, _t2976);
            U64 _t2977 = U64_inc(DEREF(pos));
            (void)_t2977;
            *pos = _t2977;
            ;
            ;
            ;
            TokenType_delete(single, &(Bool){1});
            ;
            continue;
        }
        ;
        TokenType_delete(single, &(Bool){1});
        Str *_t3014 = Str_lit("Str", 3ULL);
        (void)_t3014;
        U64 _t3015; { U64 *_hp = (U64 *)Str_size(); _t3015 = *_hp; free(_hp); }
        (void)_t3015;
        U64 _t3016 = 6;
        (void)_t3016;
        Array *_va53 = Array_new(_t3014, &(U64){_t3015}, &(U64){_t3016});
        (void)_va53;
        Str_delete(_t3014, &(Bool){1});
        ;
        ;
        U64 _t3017 = 0;
        (void)_t3017;
        Str *_t3018 = Str_clone(path);
        (void)_t3018;
        Array_set(_va53, &(U64){_t3017}, _t3018);
        ;
        U64 _t3019 = 1;
        (void)_t3019;
        Str *_t3020 = Str_lit(":", 1ULL);
        (void)_t3020;
        Array_set(_va53, &(U64){_t3019}, _t3020);
        ;
        U64 _t3021 = 2;
        (void)_t3021;
        Str *_t3022 = U32_to_str(&(U32){line});
        (void)_t3022;
        Array_set(_va53, &(U64){_t3021}, _t3022);
        ;
        U64 _t3023 = 3;
        (void)_t3023;
        Str *_t3024 = Str_lit(":", 1ULL);
        (void)_t3024;
        Array_set(_va53, &(U64){_t3023}, _t3024);
        ;
        U64 _t3025 = 4;
        (void)_t3025;
        Str *_t3026 = U32_to_str(&(U32){col});
        (void)_t3026;
        Array_set(_va53, &(U64){_t3025}, _t3026);
        ;
        U64 _t3027 = 5;
        (void)_t3027;
        Str *_t3028 = Str_lit(": error: unexpected character", 29ULL);
        (void)_t3028;
        Array_set(_va53, &(U64){_t3027}, _t3028);
        ;
        println(_va53);
        U64 _t3029 = 1;
        (void)_t3029;
        Str *_t3030 = Str_substr(src, &(U64){start}, &(U64){_t3029});
        (void)_t3030;
        ;
        ;
        U32 _t3031 = U32_clone(&(U32){col});
        (void)_t3031;
        ;
        Token *_t3032 = malloc(sizeof(Token));
        { TokenType *_ca = TokenType_clone(TokenType_Error()); _t3032->type = *_ca; free(_ca); }
        { Str *_ca = Str_clone(_t3030); _t3032->text = *_ca; free(_ca); }
        _t3032->line = U32_clone(&(U32){line});
        _t3032->col = _t3031;
        (void)_t3032;
        Str_delete(_t3030, &(Bool){1});
        ;
        Vec_push(tokens, _t3032);
        U64 _t3033 = U64_inc(DEREF(pos));
        (void)_t3033;
        *pos = _t3033;
        ;
    }
    ;
    U64 _t3036 = U64_sub(DEREF(pos), line_start);
    (void)_t3036;
    ;
    U64_delete(pos, &(Bool){1});
    U64 _t3037 = 1;
    (void)_t3037;
    U64 _t3038 = U64_add(_t3036, _t3037);
    (void)_t3038;
    ;
    ;
    I64 col = U64_to_i64(_t3038);
    (void)col;
    ;
    I64 _t3039 = I64_clone(&(I64){col});
    (void)_t3039;
    ;
    Token *_t3040 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(TokenType_Eof()); _t3040->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t3040->text = *_ca; free(_ca); }
    _t3040->line = U32_clone(&(U32){line});
    _t3040->col = _t3039;
    (void)_t3040;
    ;
    ;
    Vec_push(tokens, _t3040);
    return tokens;
}

