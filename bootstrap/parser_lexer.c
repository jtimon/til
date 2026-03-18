#include "parser_lexer.h"

Token * Token_clone(Token * self) {
    (void)self;
    U32 _t2442 = U32_clone(&self->line);
    (void)_t2442;
    U32 _t2443 = U32_clone(&self->col);
    (void)_t2443;
    Token *_t2444 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(&self->type); _t2444->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->text); _t2444->text = *_ca; free(_ca); }
    _t2444->line = _t2442;
    _t2444->col = _t2443;
    (void)_t2444;
    ;
    ;
    return _t2444;
}

void Token_delete(Token * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t2445 = 0;
    (void)_t2445;
    TokenType_delete(&self->type, &(Bool){_t2445});
    ;
    Bool _t2446 = 0;
    (void)_t2446;
    Str_delete(&self->text, &(Bool){_t2446});
    ;
    Bool _t2447 = 0;
    (void)_t2447;
    U32_delete(&self->line, &(Bool){_t2447});
    ;
    Bool _t2448 = 0;
    (void)_t2448;
    U32_delete(&self->col, &(Bool){_t2448});
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
    U8 _t2450 = 48;
    (void)_t2450;
    U8 _t2451 = 57;
    (void)_t2451;
    Bool _t2452; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t2450}); _t2452 = *_hp; free(_hp); }
    (void)_t2452;
    ;
    Bool _t2453; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t2451}); _t2453 = *_hp; free(_hp); }
    (void)_t2453;
    ;
    Bool _t2454 = Bool_and(_t2452, _t2453);
    (void)_t2454;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2454; return _r; }
}

Bool * is_alpha(U8 * c) {
    (void)c;
    U8 _t2455 = 97;
    (void)_t2455;
    U8 _t2456 = 122;
    (void)_t2456;
    Bool _t2457; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t2455}); _t2457 = *_hp; free(_hp); }
    (void)_t2457;
    ;
    Bool _t2458; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t2456}); _t2458 = *_hp; free(_hp); }
    (void)_t2458;
    ;
    U8 _t2459 = 65;
    (void)_t2459;
    U8 _t2460 = 90;
    (void)_t2460;
    Bool _t2461; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t2459}); _t2461 = *_hp; free(_hp); }
    (void)_t2461;
    ;
    Bool _t2462; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t2460}); _t2462 = *_hp; free(_hp); }
    (void)_t2462;
    ;
    Bool _t2463 = Bool_and(_t2457, _t2458);
    (void)_t2463;
    ;
    ;
    Bool _t2464 = Bool_and(_t2461, _t2462);
    (void)_t2464;
    ;
    ;
    U8 _t2465 = 95;
    (void)_t2465;
    Bool _t2466 = Bool_or(_t2463, _t2464);
    (void)_t2466;
    ;
    ;
    Bool _t2467 = U8_eq(DEREF(c), _t2465);
    (void)_t2467;
    ;
    Bool _t2468 = Bool_or(_t2466, _t2467);
    (void)_t2468;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2468; return _r; }
}

Bool * is_alnum(U8 * c) {
    (void)c;
    Bool _t2469; { Bool *_hp = (Bool *)is_alpha(c); _t2469 = *_hp; free(_hp); }
    (void)_t2469;
    Bool _t2470; { Bool *_hp = (Bool *)is_digit(c); _t2470 = *_hp; free(_hp); }
    (void)_t2470;
    Bool _t2471 = Bool_or(_t2469, _t2470);
    (void)_t2471;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2471; return _r; }
}

Str * tok_name(TokenType * type) {
    (void)type;
    {
        TokenType *_sw2472 = TokenType_clone(type);
        (void)_sw2472;
        Bool _t2605; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_Eof()); _t2605 = *_hp; free(_hp); }
        (void)_t2605;
        if (_t2605) {
            Str *_t2473 = Str_lit("eof", 3ULL);
            (void)_t2473;
            TokenType_delete(_sw2472, &(Bool){1});
            ;
            return _t2473;
        } else {
            Bool _t2604; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_LParen()); _t2604 = *_hp; free(_hp); }
            (void)_t2604;
            if (_t2604) {
                Str *_t2474 = Str_lit("(", 1ULL);
                (void)_t2474;
                ;
                TokenType_delete(_sw2472, &(Bool){1});
                ;
                return _t2474;
            } else {
                Bool _t2603; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_RParen()); _t2603 = *_hp; free(_hp); }
                (void)_t2603;
                if (_t2603) {
                    Str *_t2475 = Str_lit(")", 1ULL);
                    (void)_t2475;
                    ;
                    ;
                    TokenType_delete(_sw2472, &(Bool){1});
                    ;
                    return _t2475;
                } else {
                    Bool _t2602; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_LBrace()); _t2602 = *_hp; free(_hp); }
                    (void)_t2602;
                    if (_t2602) {
                        Str *_t2476 = Str_lit("{", 1ULL);
                        (void)_t2476;
                        ;
                        ;
                        ;
                        TokenType_delete(_sw2472, &(Bool){1});
                        ;
                        return _t2476;
                    } else {
                        Bool _t2601; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_RBrace()); _t2601 = *_hp; free(_hp); }
                        (void)_t2601;
                        if (_t2601) {
                            Str *_t2477 = Str_lit("}", 1ULL);
                            (void)_t2477;
                            ;
                            ;
                            ;
                            ;
                            TokenType_delete(_sw2472, &(Bool){1});
                            ;
                            return _t2477;
                        } else {
                            Bool _t2600; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_LBracket()); _t2600 = *_hp; free(_hp); }
                            (void)_t2600;
                            if (_t2600) {
                                Str *_t2478 = Str_lit("[", 1ULL);
                                (void)_t2478;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TokenType_delete(_sw2472, &(Bool){1});
                                ;
                                return _t2478;
                            } else {
                                Bool _t2599; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_RBracket()); _t2599 = *_hp; free(_hp); }
                                (void)_t2599;
                                if (_t2599) {
                                    Str *_t2479 = Str_lit("]", 1ULL);
                                    (void)_t2479;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TokenType_delete(_sw2472, &(Bool){1});
                                    ;
                                    return _t2479;
                                } else {
                                    Bool _t2598; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_Comma()); _t2598 = *_hp; free(_hp); }
                                    (void)_t2598;
                                    if (_t2598) {
                                        Str *_t2480 = Str_lit(",", 1ULL);
                                        (void)_t2480;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TokenType_delete(_sw2472, &(Bool){1});
                                        ;
                                        return _t2480;
                                    } else {
                                        Bool _t2597; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_Colon()); _t2597 = *_hp; free(_hp); }
                                        (void)_t2597;
                                        if (_t2597) {
                                            Str *_t2481 = Str_lit(":", 1ULL);
                                            (void)_t2481;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TokenType_delete(_sw2472, &(Bool){1});
                                            ;
                                            return _t2481;
                                        } else {
                                            Bool _t2596; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_Question()); _t2596 = *_hp; free(_hp); }
                                            (void)_t2596;
                                            if (_t2596) {
                                                Str *_t2482 = Str_lit("?", 1ULL);
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
                                                TokenType_delete(_sw2472, &(Bool){1});
                                                ;
                                                return _t2482;
                                            } else {
                                                Bool _t2595; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_Bang()); _t2595 = *_hp; free(_hp); }
                                                (void)_t2595;
                                                if (_t2595) {
                                                    Str *_t2483 = Str_lit("!", 1ULL);
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
                                                    TokenType_delete(_sw2472, &(Bool){1});
                                                    ;
                                                    return _t2483;
                                                } else {
                                                    Bool _t2594; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_Minus()); _t2594 = *_hp; free(_hp); }
                                                    (void)_t2594;
                                                    if (_t2594) {
                                                        Str *_t2484 = Str_lit("-", 1ULL);
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
                                                        TokenType_delete(_sw2472, &(Bool){1});
                                                        ;
                                                        return _t2484;
                                                    } else {
                                                        Bool _t2593; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_Plus()); _t2593 = *_hp; free(_hp); }
                                                        (void)_t2593;
                                                        if (_t2593) {
                                                            Str *_t2485 = Str_lit("+", 1ULL);
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
                                                            TokenType_delete(_sw2472, &(Bool){1});
                                                            ;
                                                            return _t2485;
                                                        } else {
                                                            Bool _t2592; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_Star()); _t2592 = *_hp; free(_hp); }
                                                            (void)_t2592;
                                                            if (_t2592) {
                                                                Str *_t2486 = Str_lit("*", 1ULL);
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
                                                                TokenType_delete(_sw2472, &(Bool){1});
                                                                ;
                                                                return _t2486;
                                                            } else {
                                                                Bool _t2591; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_Slash()); _t2591 = *_hp; free(_hp); }
                                                                (void)_t2591;
                                                                if (_t2591) {
                                                                    Str *_t2487 = Str_lit("/", 1ULL);
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
                                                                    TokenType_delete(_sw2472, &(Bool){1});
                                                                    ;
                                                                    return _t2487;
                                                                } else {
                                                                    Bool _t2590; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_Dot()); _t2590 = *_hp; free(_hp); }
                                                                    (void)_t2590;
                                                                    if (_t2590) {
                                                                        Str *_t2488 = Str_lit(".", 1ULL);
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
                                                                        TokenType_delete(_sw2472, &(Bool){1});
                                                                        ;
                                                                        return _t2488;
                                                                    } else {
                                                                        Bool _t2589; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_DotDot()); _t2589 = *_hp; free(_hp); }
                                                                        (void)_t2589;
                                                                        if (_t2589) {
                                                                            Str *_t2489 = Str_lit("..", 2ULL);
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
                                                                            TokenType_delete(_sw2472, &(Bool){1});
                                                                            ;
                                                                            return _t2489;
                                                                        } else {
                                                                            Bool _t2588; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_DotDotDot()); _t2588 = *_hp; free(_hp); }
                                                                            (void)_t2588;
                                                                            if (_t2588) {
                                                                                Str *_t2490 = Str_lit("...", 3ULL);
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
                                                                                TokenType_delete(_sw2472, &(Bool){1});
                                                                                ;
                                                                                return _t2490;
                                                                            } else {
                                                                                Bool _t2587; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_Eq()); _t2587 = *_hp; free(_hp); }
                                                                                (void)_t2587;
                                                                                if (_t2587) {
                                                                                    Str *_t2491 = Str_lit("=", 1ULL);
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
                                                                                    TokenType_delete(_sw2472, &(Bool){1});
                                                                                    ;
                                                                                    return _t2491;
                                                                                } else {
                                                                                    Bool _t2586; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_EqEq()); _t2586 = *_hp; free(_hp); }
                                                                                    (void)_t2586;
                                                                                    if (_t2586) {
                                                                                        Str *_t2492 = Str_lit("==", 2ULL);
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
                                                                                        TokenType_delete(_sw2472, &(Bool){1});
                                                                                        ;
                                                                                        return _t2492;
                                                                                    } else {
                                                                                        Bool _t2585; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_Neq()); _t2585 = *_hp; free(_hp); }
                                                                                        (void)_t2585;
                                                                                        if (_t2585) {
                                                                                            Str *_t2493 = Str_lit("!=", 2ULL);
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
                                                                                            TokenType_delete(_sw2472, &(Bool){1});
                                                                                            ;
                                                                                            return _t2493;
                                                                                        } else {
                                                                                            Bool _t2584; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_Lt()); _t2584 = *_hp; free(_hp); }
                                                                                            (void)_t2584;
                                                                                            if (_t2584) {
                                                                                                Str *_t2494 = Str_lit("<", 1ULL);
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
                                                                                                TokenType_delete(_sw2472, &(Bool){1});
                                                                                                ;
                                                                                                return _t2494;
                                                                                            } else {
                                                                                                Bool _t2583; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_LtEq()); _t2583 = *_hp; free(_hp); }
                                                                                                (void)_t2583;
                                                                                                if (_t2583) {
                                                                                                    Str *_t2495 = Str_lit("<=", 2ULL);
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
                                                                                                    TokenType_delete(_sw2472, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t2495;
                                                                                                } else {
                                                                                                    Bool _t2582; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_Gt()); _t2582 = *_hp; free(_hp); }
                                                                                                    (void)_t2582;
                                                                                                    if (_t2582) {
                                                                                                        Str *_t2496 = Str_lit(">", 1ULL);
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
                                                                                                        TokenType_delete(_sw2472, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t2496;
                                                                                                    } else {
                                                                                                        Bool _t2581; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_GtEq()); _t2581 = *_hp; free(_hp); }
                                                                                                        (void)_t2581;
                                                                                                        if (_t2581) {
                                                                                                            Str *_t2497 = Str_lit(">=", 2ULL);
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
                                                                                                            TokenType_delete(_sw2472, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t2497;
                                                                                                        } else {
                                                                                                            Bool _t2580; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_ColonEq()); _t2580 = *_hp; free(_hp); }
                                                                                                            (void)_t2580;
                                                                                                            if (_t2580) {
                                                                                                                Str *_t2498 = Str_lit(":=", 2ULL);
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
                                                                                                                TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                ;
                                                                                                                return _t2498;
                                                                                                            } else {
                                                                                                                Bool _t2579; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_Ident()); _t2579 = *_hp; free(_hp); }
                                                                                                                (void)_t2579;
                                                                                                                if (_t2579) {
                                                                                                                    Str *_t2499 = Str_lit("identifier", 10ULL);
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
                                                                                                                    TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return _t2499;
                                                                                                                } else {
                                                                                                                    Bool _t2578; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_StringTok()); _t2578 = *_hp; free(_hp); }
                                                                                                                    (void)_t2578;
                                                                                                                    if (_t2578) {
                                                                                                                        Str *_t2500 = Str_lit("string", 6ULL);
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
                                                                                                                        TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return _t2500;
                                                                                                                    } else {
                                                                                                                        Bool _t2577; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_Number()); _t2577 = *_hp; free(_hp); }
                                                                                                                        (void)_t2577;
                                                                                                                        if (_t2577) {
                                                                                                                            Str *_t2501 = Str_lit("number", 6ULL);
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
                                                                                                                            TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return _t2501;
                                                                                                                        } else {
                                                                                                                            Bool _t2576; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_Char()); _t2576 = *_hp; free(_hp); }
                                                                                                                            (void)_t2576;
                                                                                                                            if (_t2576) {
                                                                                                                                Str *_t2502 = Str_lit("char", 4ULL);
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
                                                                                                                                TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return _t2502;
                                                                                                                            } else {
                                                                                                                                Bool _t2575; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwMode()); _t2575 = *_hp; free(_hp); }
                                                                                                                                (void)_t2575;
                                                                                                                                if (_t2575) {
                                                                                                                                    Str *_t2503 = Str_lit("mode", 4ULL);
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
                                                                                                                                    TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return _t2503;
                                                                                                                                } else {
                                                                                                                                    Bool _t2574; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwMut()); _t2574 = *_hp; free(_hp); }
                                                                                                                                    (void)_t2574;
                                                                                                                                    if (_t2574) {
                                                                                                                                        Str *_t2504 = Str_lit("mut", 3ULL);
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
                                                                                                                                        TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return _t2504;
                                                                                                                                    } else {
                                                                                                                                        Bool _t2573; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwOwn()); _t2573 = *_hp; free(_hp); }
                                                                                                                                        (void)_t2573;
                                                                                                                                        if (_t2573) {
                                                                                                                                            Str *_t2505 = Str_lit("own", 3ULL);
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
                                                                                                                                            TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return _t2505;
                                                                                                                                        } else {
                                                                                                                                            Bool _t2572; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwRef()); _t2572 = *_hp; free(_hp); }
                                                                                                                                            (void)_t2572;
                                                                                                                                            if (_t2572) {
                                                                                                                                                Str *_t2506 = Str_lit("ref", 3ULL);
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
                                                                                                                                                TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return _t2506;
                                                                                                                                            } else {
                                                                                                                                                Bool _t2571; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwShallow()); _t2571 = *_hp; free(_hp); }
                                                                                                                                                (void)_t2571;
                                                                                                                                                if (_t2571) {
                                                                                                                                                    Str *_t2507 = Str_lit("shallow", 7ULL);
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
                                                                                                                                                    TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                    ;
                                                                                                                                                    return _t2507;
                                                                                                                                                } else {
                                                                                                                                                    Bool _t2570; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwStruct()); _t2570 = *_hp; free(_hp); }
                                                                                                                                                    (void)_t2570;
                                                                                                                                                    if (_t2570) {
                                                                                                                                                        Str *_t2508 = Str_lit("struct", 6ULL);
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
                                                                                                                                                        TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                        ;
                                                                                                                                                        return _t2508;
                                                                                                                                                    } else {
                                                                                                                                                        Bool _t2569; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwExtStruct()); _t2569 = *_hp; free(_hp); }
                                                                                                                                                        (void)_t2569;
                                                                                                                                                        if (_t2569) {
                                                                                                                                                            Str *_t2509 = Str_lit("ext_struct", 10ULL);
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
                                                                                                                                                            TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                            ;
                                                                                                                                                            return _t2509;
                                                                                                                                                        } else {
                                                                                                                                                            Bool _t2568; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwEnum()); _t2568 = *_hp; free(_hp); }
                                                                                                                                                            (void)_t2568;
                                                                                                                                                            if (_t2568) {
                                                                                                                                                                Str *_t2510 = Str_lit("enum", 4ULL);
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
                                                                                                                                                                TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                ;
                                                                                                                                                                return _t2510;
                                                                                                                                                            } else {
                                                                                                                                                                Bool _t2567; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwNamespace()); _t2567 = *_hp; free(_hp); }
                                                                                                                                                                (void)_t2567;
                                                                                                                                                                if (_t2567) {
                                                                                                                                                                    Str *_t2511 = Str_lit("namespace", 9ULL);
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
                                                                                                                                                                    TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                    ;
                                                                                                                                                                    return _t2511;
                                                                                                                                                                } else {
                                                                                                                                                                    Bool _t2566; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwFunc()); _t2566 = *_hp; free(_hp); }
                                                                                                                                                                    (void)_t2566;
                                                                                                                                                                    if (_t2566) {
                                                                                                                                                                        Str *_t2512 = Str_lit("func", 4ULL);
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
                                                                                                                                                                        TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                        ;
                                                                                                                                                                        return _t2512;
                                                                                                                                                                    } else {
                                                                                                                                                                        Bool _t2565; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwProc()); _t2565 = *_hp; free(_hp); }
                                                                                                                                                                        (void)_t2565;
                                                                                                                                                                        if (_t2565) {
                                                                                                                                                                            Str *_t2513 = Str_lit("proc", 4ULL);
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
                                                                                                                                                                            TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                            ;
                                                                                                                                                                            return _t2513;
                                                                                                                                                                        } else {
                                                                                                                                                                            Bool _t2564; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwTest()); _t2564 = *_hp; free(_hp); }
                                                                                                                                                                            (void)_t2564;
                                                                                                                                                                            if (_t2564) {
                                                                                                                                                                                Str *_t2514 = Str_lit("test", 4ULL);
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
                                                                                                                                                                                TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                ;
                                                                                                                                                                                return _t2514;
                                                                                                                                                                            } else {
                                                                                                                                                                                Bool _t2563; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwMacro()); _t2563 = *_hp; free(_hp); }
                                                                                                                                                                                (void)_t2563;
                                                                                                                                                                                if (_t2563) {
                                                                                                                                                                                    Str *_t2515 = Str_lit("macro", 5ULL);
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
                                                                                                                                                                                    TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                    ;
                                                                                                                                                                                    return _t2515;
                                                                                                                                                                                } else {
                                                                                                                                                                                    Bool _t2562; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwExtFunc()); _t2562 = *_hp; free(_hp); }
                                                                                                                                                                                    (void)_t2562;
                                                                                                                                                                                    if (_t2562) {
                                                                                                                                                                                        Str *_t2516 = Str_lit("ext_func", 8ULL);
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
                                                                                                                                                                                        TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                        ;
                                                                                                                                                                                        return _t2516;
                                                                                                                                                                                    } else {
                                                                                                                                                                                        Bool _t2561; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwExtProc()); _t2561 = *_hp; free(_hp); }
                                                                                                                                                                                        (void)_t2561;
                                                                                                                                                                                        if (_t2561) {
                                                                                                                                                                                            Str *_t2517 = Str_lit("ext_proc", 8ULL);
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
                                                                                                                                                                                            TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                            ;
                                                                                                                                                                                            return _t2517;
                                                                                                                                                                                        } else {
                                                                                                                                                                                            Bool _t2560; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwReturns()); _t2560 = *_hp; free(_hp); }
                                                                                                                                                                                            (void)_t2560;
                                                                                                                                                                                            if (_t2560) {
                                                                                                                                                                                                Str *_t2518 = Str_lit("returns", 7ULL);
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
                                                                                                                                                                                                TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                                ;
                                                                                                                                                                                                return _t2518;
                                                                                                                                                                                            } else {
                                                                                                                                                                                                Bool _t2559; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwThrows()); _t2559 = *_hp; free(_hp); }
                                                                                                                                                                                                (void)_t2559;
                                                                                                                                                                                                if (_t2559) {
                                                                                                                                                                                                    Str *_t2519 = Str_lit("throws", 6ULL);
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
                                                                                                                                                                                                    TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    return _t2519;
                                                                                                                                                                                                } else {
                                                                                                                                                                                                    Bool _t2558; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwIf()); _t2558 = *_hp; free(_hp); }
                                                                                                                                                                                                    (void)_t2558;
                                                                                                                                                                                                    if (_t2558) {
                                                                                                                                                                                                        Str *_t2520 = Str_lit("if", 2ULL);
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
                                                                                                                                                                                                        TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        return _t2520;
                                                                                                                                                                                                    } else {
                                                                                                                                                                                                        Bool _t2557; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwElse()); _t2557 = *_hp; free(_hp); }
                                                                                                                                                                                                        (void)_t2557;
                                                                                                                                                                                                        if (_t2557) {
                                                                                                                                                                                                            Str *_t2521 = Str_lit("else", 4ULL);
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
                                                                                                                                                                                                            TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            return _t2521;
                                                                                                                                                                                                        } else {
                                                                                                                                                                                                            Bool _t2556; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwWhile()); _t2556 = *_hp; free(_hp); }
                                                                                                                                                                                                            (void)_t2556;
                                                                                                                                                                                                            if (_t2556) {
                                                                                                                                                                                                                Str *_t2522 = Str_lit("while", 5ULL);
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
                                                                                                                                                                                                                TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                return _t2522;
                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                Bool _t2555; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwFor()); _t2555 = *_hp; free(_hp); }
                                                                                                                                                                                                                (void)_t2555;
                                                                                                                                                                                                                if (_t2555) {
                                                                                                                                                                                                                    Str *_t2523 = Str_lit("for", 3ULL);
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
                                                                                                                                                                                                                    TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    return _t2523;
                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                    Bool _t2554; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwIn()); _t2554 = *_hp; free(_hp); }
                                                                                                                                                                                                                    (void)_t2554;
                                                                                                                                                                                                                    if (_t2554) {
                                                                                                                                                                                                                        Str *_t2524 = Str_lit("in", 2ULL);
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
                                                                                                                                                                                                                        TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        return _t2524;
                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                        Bool _t2553; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwSwitch()); _t2553 = *_hp; free(_hp); }
                                                                                                                                                                                                                        (void)_t2553;
                                                                                                                                                                                                                        if (_t2553) {
                                                                                                                                                                                                                            Str *_t2525 = Str_lit("switch", 6ULL);
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
                                                                                                                                                                                                                            TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            return _t2525;
                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                            Bool _t2552; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwMatch()); _t2552 = *_hp; free(_hp); }
                                                                                                                                                                                                                            (void)_t2552;
                                                                                                                                                                                                                            if (_t2552) {
                                                                                                                                                                                                                                Str *_t2526 = Str_lit("match", 5ULL);
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
                                                                                                                                                                                                                                TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                return _t2526;
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                Bool _t2551; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwCase()); _t2551 = *_hp; free(_hp); }
                                                                                                                                                                                                                                (void)_t2551;
                                                                                                                                                                                                                                if (_t2551) {
                                                                                                                                                                                                                                    Str *_t2527 = Str_lit("case", 4ULL);
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
                                                                                                                                                                                                                                    TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    return _t2527;
                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                    Bool _t2550; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwDefault()); _t2550 = *_hp; free(_hp); }
                                                                                                                                                                                                                                    (void)_t2550;
                                                                                                                                                                                                                                    if (_t2550) {
                                                                                                                                                                                                                                        Str *_t2528 = Str_lit("default", 7ULL);
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
                                                                                                                                                                                                                                        TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        return _t2528;
                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                        Bool _t2549; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwReturn()); _t2549 = *_hp; free(_hp); }
                                                                                                                                                                                                                                        (void)_t2549;
                                                                                                                                                                                                                                        if (_t2549) {
                                                                                                                                                                                                                                            Str *_t2529 = Str_lit("return", 6ULL);
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
                                                                                                                                                                                                                                            TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            return _t2529;
                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                            Bool _t2548; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwThrow()); _t2548 = *_hp; free(_hp); }
                                                                                                                                                                                                                                            (void)_t2548;
                                                                                                                                                                                                                                            if (_t2548) {
                                                                                                                                                                                                                                                Str *_t2530 = Str_lit("throw", 5ULL);
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
                                                                                                                                                                                                                                                TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                return _t2530;
                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                Bool _t2547; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwCatch()); _t2547 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                (void)_t2547;
                                                                                                                                                                                                                                                if (_t2547) {
                                                                                                                                                                                                                                                    Str *_t2531 = Str_lit("catch", 5ULL);
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
                                                                                                                                                                                                                                                    TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    return _t2531;
                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                    Bool _t2546; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwBreak()); _t2546 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                    (void)_t2546;
                                                                                                                                                                                                                                                    if (_t2546) {
                                                                                                                                                                                                                                                        Str *_t2532 = Str_lit("break", 5ULL);
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
                                                                                                                                                                                                                                                        TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        return _t2532;
                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                        Bool _t2545; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwContinue()); _t2545 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                        (void)_t2545;
                                                                                                                                                                                                                                                        if (_t2545) {
                                                                                                                                                                                                                                                            Str *_t2533 = Str_lit("continue", 8ULL);
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
                                                                                                                                                                                                                                                            TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            return _t2533;
                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                            Bool _t2544; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwDefer()); _t2544 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                            (void)_t2544;
                                                                                                                                                                                                                                                            if (_t2544) {
                                                                                                                                                                                                                                                                Str *_t2534 = Str_lit("defer", 5ULL);
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
                                                                                                                                                                                                                                                                TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                return _t2534;
                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                Bool _t2543; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwTrue()); _t2543 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                (void)_t2543;
                                                                                                                                                                                                                                                                if (_t2543) {
                                                                                                                                                                                                                                                                    Str *_t2535 = Str_lit("true", 4ULL);
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
                                                                                                                                                                                                                                                                    TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t2535;
                                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                                    Bool _t2542; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwFalse()); _t2542 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                    (void)_t2542;
                                                                                                                                                                                                                                                                    if (_t2542) {
                                                                                                                                                                                                                                                                        Str *_t2536 = Str_lit("false", 5ULL);
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
                                                                                                                                                                                                                                                                        TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        return _t2536;
                                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                                        Bool _t2541; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_KwNull()); _t2541 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                        (void)_t2541;
                                                                                                                                                                                                                                                                        if (_t2541) {
                                                                                                                                                                                                                                                                            Str *_t2537 = Str_lit("NULL", 4ULL);
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
                                                                                                                                                                                                                                                                            TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            return _t2537;
                                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                                            Bool _t2540; { Bool *_hp = (Bool *)TokenType_eq(_sw2472, TokenType_Error()); _t2540 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                            (void)_t2540;
                                                                                                                                                                                                                                                                            if (_t2540) {
                                                                                                                                                                                                                                                                                Str *_t2538 = Str_lit("error", 5ULL);
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
                                                                                                                                                                                                                                                                                TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t2538;
                                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                                Str *_t2539 = Str_lit("?", 1ULL);
                                                                                                                                                                                                                                                                                (void)_t2539;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                TokenType_delete(_sw2472, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t2539;
                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                        }
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                    }
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                }
                                                                                                                                                                                                                ;
                                                                                                                                                                                                            }
                                                                                                                                                                                                            ;
                                                                                                                                                                                                        }
                                                                                                                                                                                                        ;
                                                                                                                                                                                                    }
                                                                                                                                                                                                    ;
                                                                                                                                                                                                }
                                                                                                                                                                                                ;
                                                                                                                                                                                            }
                                                                                                                                                                                            ;
                                                                                                                                                                                        }
                                                                                                                                                                                        ;
                                                                                                                                                                                    }
                                                                                                                                                                                    ;
                                                                                                                                                                                }
                                                                                                                                                                                ;
                                                                                                                                                                            }
                                                                                                                                                                            ;
                                                                                                                                                                        }
                                                                                                                                                                        ;
                                                                                                                                                                    }
                                                                                                                                                                    ;
                                                                                                                                                                }
                                                                                                                                                                ;
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                        ;
                                                                                                                                                    }
                                                                                                                                                    ;
                                                                                                                                                }
                                                                                                                                                ;
                                                                                                                                            }
                                                                                                                                            ;
                                                                                                                                        }
                                                                                                                                        ;
                                                                                                                                    }
                                                                                                                                    ;
                                                                                                                                }
                                                                                                                                ;
                                                                                                                            }
                                                                                                                            ;
                                                                                                                        }
                                                                                                                        ;
                                                                                                                    }
                                                                                                                    ;
                                                                                                                }
                                                                                                                ;
                                                                                                            }
                                                                                                            ;
                                                                                                        }
                                                                                                        ;
                                                                                                    }
                                                                                                    ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                            ;
                                                                                        }
                                                                                        ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                                ;
                                                                            }
                                                                            ;
                                                                        }
                                                                        ;
                                                                    }
                                                                    ;
                                                                }
                                                                ;
                                                            }
                                                            ;
                                                        }
                                                        ;
                                                    }
                                                    ;
                                                }
                                                ;
                                            }
                                            ;
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        TokenType_delete(_sw2472, &(Bool){1});
        ;
    }
}

TokenType * lookup_keyword(Str * word) {
    (void)word;
    {
        Str *_sw2606 = Str_clone(word);
        (void)_sw2606;
        Str *_t2675 = Str_lit("mode", 4ULL);
        (void)_t2675;
        Bool _t2676; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2675); _t2676 = *_hp; free(_hp); }
        (void)_t2676;
        Str_delete(_t2675, &(Bool){1});
        if (_t2676) {
            Str_delete(_sw2606, &(Bool){1});
            ;
            return TokenType_KwMode();
        } else {
            Str *_t2673 = Str_lit("mut", 3ULL);
            (void)_t2673;
            Bool _t2674; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2673); _t2674 = *_hp; free(_hp); }
            (void)_t2674;
            Str_delete(_t2673, &(Bool){1});
            if (_t2674) {
                ;
                Str_delete(_sw2606, &(Bool){1});
                ;
                return TokenType_KwMut();
            } else {
                Str *_t2671 = Str_lit("own", 3ULL);
                (void)_t2671;
                Bool _t2672; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2671); _t2672 = *_hp; free(_hp); }
                (void)_t2672;
                Str_delete(_t2671, &(Bool){1});
                if (_t2672) {
                    ;
                    ;
                    Str_delete(_sw2606, &(Bool){1});
                    ;
                    return TokenType_KwOwn();
                } else {
                    Str *_t2669 = Str_lit("ref", 3ULL);
                    (void)_t2669;
                    Bool _t2670; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2669); _t2670 = *_hp; free(_hp); }
                    (void)_t2670;
                    Str_delete(_t2669, &(Bool){1});
                    if (_t2670) {
                        ;
                        ;
                        ;
                        Str_delete(_sw2606, &(Bool){1});
                        ;
                        return TokenType_KwRef();
                    } else {
                        Str *_t2667 = Str_lit("shallow", 7ULL);
                        (void)_t2667;
                        Bool _t2668; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2667); _t2668 = *_hp; free(_hp); }
                        (void)_t2668;
                        Str_delete(_t2667, &(Bool){1});
                        if (_t2668) {
                            ;
                            ;
                            ;
                            ;
                            Str_delete(_sw2606, &(Bool){1});
                            ;
                            return TokenType_KwShallow();
                        } else {
                            Str *_t2665 = Str_lit("struct", 6ULL);
                            (void)_t2665;
                            Bool _t2666; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2665); _t2666 = *_hp; free(_hp); }
                            (void)_t2666;
                            Str_delete(_t2665, &(Bool){1});
                            if (_t2666) {
                                ;
                                ;
                                ;
                                ;
                                ;
                                Str_delete(_sw2606, &(Bool){1});
                                ;
                                return TokenType_KwStruct();
                            } else {
                                Str *_t2663 = Str_lit("ext_struct", 10ULL);
                                (void)_t2663;
                                Bool _t2664; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2663); _t2664 = *_hp; free(_hp); }
                                (void)_t2664;
                                Str_delete(_t2663, &(Bool){1});
                                if (_t2664) {
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    Str_delete(_sw2606, &(Bool){1});
                                    ;
                                    return TokenType_KwExtStruct();
                                } else {
                                    Str *_t2661 = Str_lit("enum", 4ULL);
                                    (void)_t2661;
                                    Bool _t2662; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2661); _t2662 = *_hp; free(_hp); }
                                    (void)_t2662;
                                    Str_delete(_t2661, &(Bool){1});
                                    if (_t2662) {
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        Str_delete(_sw2606, &(Bool){1});
                                        ;
                                        return TokenType_KwEnum();
                                    } else {
                                        Str *_t2659 = Str_lit("namespace", 9ULL);
                                        (void)_t2659;
                                        Bool _t2660; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2659); _t2660 = *_hp; free(_hp); }
                                        (void)_t2660;
                                        Str_delete(_t2659, &(Bool){1});
                                        if (_t2660) {
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            Str_delete(_sw2606, &(Bool){1});
                                            ;
                                            return TokenType_KwNamespace();
                                        } else {
                                            Str *_t2657 = Str_lit("func", 4ULL);
                                            (void)_t2657;
                                            Bool _t2658; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2657); _t2658 = *_hp; free(_hp); }
                                            (void)_t2658;
                                            Str_delete(_t2657, &(Bool){1});
                                            if (_t2658) {
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                Str_delete(_sw2606, &(Bool){1});
                                                ;
                                                return TokenType_KwFunc();
                                            } else {
                                                Str *_t2655 = Str_lit("proc", 4ULL);
                                                (void)_t2655;
                                                Bool _t2656; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2655); _t2656 = *_hp; free(_hp); }
                                                (void)_t2656;
                                                Str_delete(_t2655, &(Bool){1});
                                                if (_t2656) {
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    Str_delete(_sw2606, &(Bool){1});
                                                    ;
                                                    return TokenType_KwProc();
                                                } else {
                                                    Str *_t2653 = Str_lit("test", 4ULL);
                                                    (void)_t2653;
                                                    Bool _t2654; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2653); _t2654 = *_hp; free(_hp); }
                                                    (void)_t2654;
                                                    Str_delete(_t2653, &(Bool){1});
                                                    if (_t2654) {
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        Str_delete(_sw2606, &(Bool){1});
                                                        ;
                                                        return TokenType_KwTest();
                                                    } else {
                                                        Str *_t2651 = Str_lit("macro", 5ULL);
                                                        (void)_t2651;
                                                        Bool _t2652; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2651); _t2652 = *_hp; free(_hp); }
                                                        (void)_t2652;
                                                        Str_delete(_t2651, &(Bool){1});
                                                        if (_t2652) {
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            Str_delete(_sw2606, &(Bool){1});
                                                            ;
                                                            return TokenType_KwMacro();
                                                        } else {
                                                            Str *_t2649 = Str_lit("ext_func", 8ULL);
                                                            (void)_t2649;
                                                            Bool _t2650; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2649); _t2650 = *_hp; free(_hp); }
                                                            (void)_t2650;
                                                            Str_delete(_t2649, &(Bool){1});
                                                            if (_t2650) {
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                Str_delete(_sw2606, &(Bool){1});
                                                                ;
                                                                return TokenType_KwExtFunc();
                                                            } else {
                                                                Str *_t2647 = Str_lit("ext_proc", 8ULL);
                                                                (void)_t2647;
                                                                Bool _t2648; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2647); _t2648 = *_hp; free(_hp); }
                                                                (void)_t2648;
                                                                Str_delete(_t2647, &(Bool){1});
                                                                if (_t2648) {
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    Str_delete(_sw2606, &(Bool){1});
                                                                    ;
                                                                    return TokenType_KwExtProc();
                                                                } else {
                                                                    Str *_t2645 = Str_lit("returns", 7ULL);
                                                                    (void)_t2645;
                                                                    Bool _t2646; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2645); _t2646 = *_hp; free(_hp); }
                                                                    (void)_t2646;
                                                                    Str_delete(_t2645, &(Bool){1});
                                                                    if (_t2646) {
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        Str_delete(_sw2606, &(Bool){1});
                                                                        ;
                                                                        return TokenType_KwReturns();
                                                                    } else {
                                                                        Str *_t2643 = Str_lit("throws", 6ULL);
                                                                        (void)_t2643;
                                                                        Bool _t2644; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2643); _t2644 = *_hp; free(_hp); }
                                                                        (void)_t2644;
                                                                        Str_delete(_t2643, &(Bool){1});
                                                                        if (_t2644) {
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            Str_delete(_sw2606, &(Bool){1});
                                                                            ;
                                                                            return TokenType_KwThrows();
                                                                        } else {
                                                                            Str *_t2641 = Str_lit("if", 2ULL);
                                                                            (void)_t2641;
                                                                            Bool _t2642; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2641); _t2642 = *_hp; free(_hp); }
                                                                            (void)_t2642;
                                                                            Str_delete(_t2641, &(Bool){1});
                                                                            if (_t2642) {
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                Str_delete(_sw2606, &(Bool){1});
                                                                                ;
                                                                                return TokenType_KwIf();
                                                                            } else {
                                                                                Str *_t2639 = Str_lit("else", 4ULL);
                                                                                (void)_t2639;
                                                                                Bool _t2640; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2639); _t2640 = *_hp; free(_hp); }
                                                                                (void)_t2640;
                                                                                Str_delete(_t2639, &(Bool){1});
                                                                                if (_t2640) {
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    Str_delete(_sw2606, &(Bool){1});
                                                                                    ;
                                                                                    return TokenType_KwElse();
                                                                                } else {
                                                                                    Str *_t2637 = Str_lit("while", 5ULL);
                                                                                    (void)_t2637;
                                                                                    Bool _t2638; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2637); _t2638 = *_hp; free(_hp); }
                                                                                    (void)_t2638;
                                                                                    Str_delete(_t2637, &(Bool){1});
                                                                                    if (_t2638) {
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        Str_delete(_sw2606, &(Bool){1});
                                                                                        ;
                                                                                        return TokenType_KwWhile();
                                                                                    } else {
                                                                                        Str *_t2635 = Str_lit("for", 3ULL);
                                                                                        (void)_t2635;
                                                                                        Bool _t2636; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2635); _t2636 = *_hp; free(_hp); }
                                                                                        (void)_t2636;
                                                                                        Str_delete(_t2635, &(Bool){1});
                                                                                        if (_t2636) {
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            Str_delete(_sw2606, &(Bool){1});
                                                                                            ;
                                                                                            return TokenType_KwFor();
                                                                                        } else {
                                                                                            Str *_t2633 = Str_lit("in", 2ULL);
                                                                                            (void)_t2633;
                                                                                            Bool _t2634; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2633); _t2634 = *_hp; free(_hp); }
                                                                                            (void)_t2634;
                                                                                            Str_delete(_t2633, &(Bool){1});
                                                                                            if (_t2634) {
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                Str_delete(_sw2606, &(Bool){1});
                                                                                                ;
                                                                                                return TokenType_KwIn();
                                                                                            } else {
                                                                                                Str *_t2631 = Str_lit("switch", 6ULL);
                                                                                                (void)_t2631;
                                                                                                Bool _t2632; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2631); _t2632 = *_hp; free(_hp); }
                                                                                                (void)_t2632;
                                                                                                Str_delete(_t2631, &(Bool){1});
                                                                                                if (_t2632) {
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    Str_delete(_sw2606, &(Bool){1});
                                                                                                    ;
                                                                                                    return TokenType_KwSwitch();
                                                                                                } else {
                                                                                                    Str *_t2629 = Str_lit("match", 5ULL);
                                                                                                    (void)_t2629;
                                                                                                    Bool _t2630; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2629); _t2630 = *_hp; free(_hp); }
                                                                                                    (void)_t2630;
                                                                                                    Str_delete(_t2629, &(Bool){1});
                                                                                                    if (_t2630) {
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        Str_delete(_sw2606, &(Bool){1});
                                                                                                        ;
                                                                                                        return TokenType_KwMatch();
                                                                                                    } else {
                                                                                                        Str *_t2627 = Str_lit("case", 4ULL);
                                                                                                        (void)_t2627;
                                                                                                        Bool _t2628; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2627); _t2628 = *_hp; free(_hp); }
                                                                                                        (void)_t2628;
                                                                                                        Str_delete(_t2627, &(Bool){1});
                                                                                                        if (_t2628) {
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            Str_delete(_sw2606, &(Bool){1});
                                                                                                            ;
                                                                                                            return TokenType_KwCase();
                                                                                                        } else {
                                                                                                            Str *_t2625 = Str_lit("default", 7ULL);
                                                                                                            (void)_t2625;
                                                                                                            Bool _t2626; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2625); _t2626 = *_hp; free(_hp); }
                                                                                                            (void)_t2626;
                                                                                                            Str_delete(_t2625, &(Bool){1});
                                                                                                            if (_t2626) {
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                Str_delete(_sw2606, &(Bool){1});
                                                                                                                ;
                                                                                                                return TokenType_KwDefault();
                                                                                                            } else {
                                                                                                                Str *_t2623 = Str_lit("return", 6ULL);
                                                                                                                (void)_t2623;
                                                                                                                Bool _t2624; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2623); _t2624 = *_hp; free(_hp); }
                                                                                                                (void)_t2624;
                                                                                                                Str_delete(_t2623, &(Bool){1});
                                                                                                                if (_t2624) {
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    Str_delete(_sw2606, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return TokenType_KwReturn();
                                                                                                                } else {
                                                                                                                    Str *_t2621 = Str_lit("throw", 5ULL);
                                                                                                                    (void)_t2621;
                                                                                                                    Bool _t2622; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2621); _t2622 = *_hp; free(_hp); }
                                                                                                                    (void)_t2622;
                                                                                                                    Str_delete(_t2621, &(Bool){1});
                                                                                                                    if (_t2622) {
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        Str_delete(_sw2606, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return TokenType_KwThrow();
                                                                                                                    } else {
                                                                                                                        Str *_t2619 = Str_lit("catch", 5ULL);
                                                                                                                        (void)_t2619;
                                                                                                                        Bool _t2620; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2619); _t2620 = *_hp; free(_hp); }
                                                                                                                        (void)_t2620;
                                                                                                                        Str_delete(_t2619, &(Bool){1});
                                                                                                                        if (_t2620) {
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            Str_delete(_sw2606, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return TokenType_KwCatch();
                                                                                                                        } else {
                                                                                                                            Str *_t2617 = Str_lit("break", 5ULL);
                                                                                                                            (void)_t2617;
                                                                                                                            Bool _t2618; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2617); _t2618 = *_hp; free(_hp); }
                                                                                                                            (void)_t2618;
                                                                                                                            Str_delete(_t2617, &(Bool){1});
                                                                                                                            if (_t2618) {
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                Str_delete(_sw2606, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return TokenType_KwBreak();
                                                                                                                            } else {
                                                                                                                                Str *_t2615 = Str_lit("continue", 8ULL);
                                                                                                                                (void)_t2615;
                                                                                                                                Bool _t2616; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2615); _t2616 = *_hp; free(_hp); }
                                                                                                                                (void)_t2616;
                                                                                                                                Str_delete(_t2615, &(Bool){1});
                                                                                                                                if (_t2616) {
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    Str_delete(_sw2606, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return TokenType_KwContinue();
                                                                                                                                } else {
                                                                                                                                    Str *_t2613 = Str_lit("defer", 5ULL);
                                                                                                                                    (void)_t2613;
                                                                                                                                    Bool _t2614; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2613); _t2614 = *_hp; free(_hp); }
                                                                                                                                    (void)_t2614;
                                                                                                                                    Str_delete(_t2613, &(Bool){1});
                                                                                                                                    if (_t2614) {
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        Str_delete(_sw2606, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return TokenType_KwDefer();
                                                                                                                                    } else {
                                                                                                                                        Str *_t2611 = Str_lit("true", 4ULL);
                                                                                                                                        (void)_t2611;
                                                                                                                                        Bool _t2612; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2611); _t2612 = *_hp; free(_hp); }
                                                                                                                                        (void)_t2612;
                                                                                                                                        Str_delete(_t2611, &(Bool){1});
                                                                                                                                        if (_t2612) {
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            Str_delete(_sw2606, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return TokenType_KwTrue();
                                                                                                                                        } else {
                                                                                                                                            Str *_t2609 = Str_lit("false", 5ULL);
                                                                                                                                            (void)_t2609;
                                                                                                                                            Bool _t2610; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2609); _t2610 = *_hp; free(_hp); }
                                                                                                                                            (void)_t2610;
                                                                                                                                            Str_delete(_t2609, &(Bool){1});
                                                                                                                                            if (_t2610) {
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                Str_delete(_sw2606, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return TokenType_KwFalse();
                                                                                                                                            } else {
                                                                                                                                                Str *_t2607 = Str_lit("NULL", 4ULL);
                                                                                                                                                (void)_t2607;
                                                                                                                                                Bool _t2608; { Bool *_hp = (Bool *)Str_eq(_sw2606, _t2607); _t2608 = *_hp; free(_hp); }
                                                                                                                                                (void)_t2608;
                                                                                                                                                Str_delete(_t2607, &(Bool){1});
                                                                                                                                                if (_t2608) {
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    Str_delete(_sw2606, &(Bool){1});
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
                                                                                                                                                    Str_delete(_sw2606, &(Bool){1});
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
        Str_delete(_sw2606, &(Bool){1});
        ;
    }
}

Vec * tokenize(Str * src, Str * path) {
    (void)src;
    (void)path;
    Str *_t3035 = Str_lit("Token", 5ULL);
    (void)_t3035;
    U64 _t3036; { U64 *_hp = (U64 *)Token_size(); _t3036 = *_hp; free(_hp); }
    (void)_t3036;
    Vec *tokens = Vec_new(_t3035, &(U64){_t3036});
    (void)tokens;
    Str_delete(_t3035, &(Bool){1});
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
        Bool _wcond2677; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2677 = *_hp; free(_hp); }
        (void)_wcond2677;
        if (_wcond2677) {
        } else {
            ;
            break;
        }
        ;
        U8 *c = Str_byte_at(src, pos);
        (void)c;
        U8 _t2979 = 32;
        (void)_t2979;
        U8 _t2980 = 9;
        (void)_t2980;
        Bool _t2981 = U8_eq(DEREF(c), _t2979);
        (void)_t2981;
        ;
        Bool _t2982 = U8_eq(DEREF(c), _t2980);
        (void)_t2982;
        ;
        U8 _t2983 = 13;
        (void)_t2983;
        Bool _t2984 = Bool_or(_t2981, _t2982);
        (void)_t2984;
        ;
        ;
        Bool _t2985 = U8_eq(DEREF(c), _t2983);
        (void)_t2985;
        ;
        U8 _t2986 = 59;
        (void)_t2986;
        Bool _t2987 = Bool_or(_t2984, _t2985);
        (void)_t2987;
        ;
        ;
        Bool _t2988 = U8_eq(DEREF(c), _t2986);
        (void)_t2988;
        ;
        Bool _t2989 = Bool_or(_t2987, _t2988);
        (void)_t2989;
        ;
        ;
        if (_t2989) {
            U64 _t2678 = U64_inc(DEREF(pos));
            (void)_t2678;
            *pos = _t2678;
            ;
            ;
            continue;
        }
        ;
        U8 _t2990 = 10;
        (void)_t2990;
        Bool _t2991 = U8_eq(DEREF(c), _t2990);
        (void)_t2991;
        ;
        if (_t2991) {
            U64 _t2679 = U64_inc(DEREF(pos));
            (void)_t2679;
            *pos = _t2679;
            ;
            U32 _t2680 = 1;
            (void)_t2680;
            U32 _t2681 = U32_add(line, _t2680);
            (void)_t2681;
            ;
            line = _t2681;
            ;
            U64 _t2682 = U64_clone(pos);
            (void)_t2682;
            line_start = _t2682;
            ;
            ;
            continue;
        }
        ;
        U64 _t2992 = U64_sub(DEREF(pos), line_start);
        (void)_t2992;
        U64 _t2993 = 1;
        (void)_t2993;
        U64 _t2994 = U64_add(_t2992, _t2993);
        (void)_t2994;
        ;
        ;
        I64 _t2995 = U64_to_i64(_t2994);
        (void)_t2995;
        ;
        U32 col = I64_to_u32(_t2995);
        (void)col;
        ;
        U64 start = U64_clone(pos);
        (void)start;
        U8 _t2996 = 35;
        (void)_t2996;
        Bool _t2997 = U8_eq(DEREF(c), _t2996);
        (void)_t2997;
        ;
        if (_t2997) {
            while (1) {
                Bool _wcond2683; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2683 = *_hp; free(_hp); }
                (void)_wcond2683;
                if (_wcond2683) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2684 = Str_byte_at(src, pos);
                (void)_t2684;
                U8 _t2685 = 10;
                (void)_t2685;
                Bool _t2686 = U8_eq(DEREF(_t2684), _t2685);
                (void)_t2686;
                ;
                if (_t2686) {
                    ;
                    break;
                }
                ;
                U64 _t2687 = U64_inc(DEREF(pos));
                (void)_t2687;
                *pos = _t2687;
                ;
            }
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t2998 = 47;
        (void)_t2998;
        U64 _t2999 = 1;
        (void)_t2999;
        U64 _t3000 = U64_add(DEREF(pos), _t2999);
        (void)_t3000;
        ;
        Bool _t3001 = U8_eq(DEREF(c), _t2998);
        (void)_t3001;
        ;
        Bool _t3002; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3000}, &(U64){src_len}); _t3002 = *_hp; free(_hp); }
        (void)_t3002;
        ;
        Bool _t3003 = Bool_and(_t3001, _t3002);
        (void)_t3003;
        ;
        ;
        if (_t3003) {
            U64 _t2746 = 1;
            (void)_t2746;
            U64 *_t2747 = malloc(sizeof(U64)); *_t2747 = U64_add(DEREF(pos), _t2746);
            (void)_t2747;
            ;
            U8 *c2 = Str_byte_at(src, _t2747);
            (void)c2;
            U8 _t2748 = 47;
            (void)_t2748;
            Bool _t2749 = U8_eq(DEREF(c2), _t2748);
            (void)_t2749;
            ;
            if (_t2749) {
                while (1) {
                    Bool _wcond2688; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2688 = *_hp; free(_hp); }
                    (void)_wcond2688;
                    if (_wcond2688) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U8 *_t2689 = Str_byte_at(src, pos);
                    (void)_t2689;
                    U8 _t2690 = 10;
                    (void)_t2690;
                    Bool _t2691 = U8_eq(DEREF(_t2689), _t2690);
                    (void)_t2691;
                    ;
                    if (_t2691) {
                        ;
                        break;
                    }
                    ;
                    U64 _t2692 = U64_inc(DEREF(pos));
                    (void)_t2692;
                    *pos = _t2692;
                    ;
                }
                U64_delete(_t2747, &(Bool){1});
                ;
                ;
                ;
                ;
                continue;
            }
            ;
            U8 _t2750 = 42;
            (void)_t2750;
            Bool _t2751 = U8_eq(DEREF(c2), _t2750);
            (void)_t2751;
            U64_delete(_t2747, &(Bool){1});
            ;
            if (_t2751) {
                U64 _t2742 = 2;
                (void)_t2742;
                U64 _t2743 = U64_add(DEREF(pos), _t2742);
                (void)_t2743;
                ;
                *pos = _t2743;
                ;
                I64 depth = 1;
                (void)depth;
                while (1) {
                    Bool _wcond2693; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2693 = *_hp; free(_hp); }
                    (void)_wcond2693;
                    if (_wcond2693) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    I64 _t2718 = 0;
                    (void)_t2718;
                    Bool _t2719; { Bool *_hp = (Bool *)I64_lte(&(I64){depth}, &(I64){_t2718}); _t2719 = *_hp; free(_hp); }
                    (void)_t2719;
                    ;
                    if (_t2719) {
                        ;
                        break;
                    }
                    ;
                    U64 _t2720 = 1;
                    (void)_t2720;
                    U64 _t2721 = U64_add(DEREF(pos), _t2720);
                    (void)_t2721;
                    ;
                    Bool _t2722; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2721}, &(U64){src_len}); _t2722 = *_hp; free(_hp); }
                    (void)_t2722;
                    ;
                    if (_t2722) {
                        U8 *b1 = Str_byte_at(src, pos);
                        (void)b1;
                        U64 _t2702 = 1;
                        (void)_t2702;
                        U64 *_t2703 = malloc(sizeof(U64)); *_t2703 = U64_add(DEREF(pos), _t2702);
                        (void)_t2703;
                        ;
                        U8 *b2 = Str_byte_at(src, _t2703);
                        (void)b2;
                        U8 _t2704 = 47;
                        (void)_t2704;
                        U8 _t2705 = 42;
                        (void)_t2705;
                        Bool _t2706 = U8_eq(DEREF(b1), _t2704);
                        (void)_t2706;
                        ;
                        Bool _t2707 = U8_eq(DEREF(b2), _t2705);
                        (void)_t2707;
                        ;
                        Bool _t2708 = Bool_and(_t2706, _t2707);
                        (void)_t2708;
                        ;
                        ;
                        if (_t2708) {
                            I64 _t2694 = 1;
                            (void)_t2694;
                            I64 _t2695 = I64_add(depth, _t2694);
                            (void)_t2695;
                            ;
                            depth = _t2695;
                            ;
                            U64 _t2696 = 2;
                            (void)_t2696;
                            U64 _t2697 = U64_add(DEREF(pos), _t2696);
                            (void)_t2697;
                            ;
                            *pos = _t2697;
                            ;
                            U64_delete(_t2703, &(Bool){1});
                            ;
                            ;
                            continue;
                        }
                        ;
                        U8 _t2709 = 42;
                        (void)_t2709;
                        U8 _t2710 = 47;
                        (void)_t2710;
                        Bool _t2711 = U8_eq(DEREF(b1), _t2709);
                        (void)_t2711;
                        ;
                        Bool _t2712 = U8_eq(DEREF(b2), _t2710);
                        (void)_t2712;
                        U64_delete(_t2703, &(Bool){1});
                        ;
                        Bool _t2713 = Bool_and(_t2711, _t2712);
                        (void)_t2713;
                        ;
                        ;
                        if (_t2713) {
                            I64 _t2698 = 1;
                            (void)_t2698;
                            I64 _t2699 = I64_sub(depth, _t2698);
                            (void)_t2699;
                            ;
                            depth = _t2699;
                            ;
                            U64 _t2700 = 2;
                            (void)_t2700;
                            U64 _t2701 = U64_add(DEREF(pos), _t2700);
                            (void)_t2701;
                            ;
                            *pos = _t2701;
                            ;
                            ;
                            ;
                            continue;
                        }
                        ;
                    }
                    ;
                    U8 *_t2723 = Str_byte_at(src, pos);
                    (void)_t2723;
                    U8 _t2724 = 10;
                    (void)_t2724;
                    Bool _t2725 = U8_eq(DEREF(_t2723), _t2724);
                    (void)_t2725;
                    ;
                    if (_t2725) {
                        U32 _t2714 = 1;
                        (void)_t2714;
                        U32 _t2715 = U32_add(line, _t2714);
                        (void)_t2715;
                        ;
                        line = _t2715;
                        ;
                        U64 _t2716 = 1;
                        (void)_t2716;
                        U64 _t2717 = U64_add(DEREF(pos), _t2716);
                        (void)_t2717;
                        ;
                        line_start = _t2717;
                        ;
                    }
                    ;
                    U64 _t2726 = U64_inc(DEREF(pos));
                    (void)_t2726;
                    *pos = _t2726;
                    ;
                }
                I64 _t2744 = 0;
                (void)_t2744;
                Bool _t2745; { Bool *_hp = (Bool *)I64_gt(&(I64){depth}, &(I64){_t2744}); _t2745 = *_hp; free(_hp); }
                (void)_t2745;
                ;
                ;
                if (_t2745) {
                    Str *_t2727 = Str_lit("Str", 3ULL);
                    (void)_t2727;
                    U64 _t2728; { U64 *_hp = (U64 *)Str_size(); _t2728 = *_hp; free(_hp); }
                    (void)_t2728;
                    U64 _t2729 = 6;
                    (void)_t2729;
                    Array *_va50 = Array_new(_t2727, &(U64){_t2728}, &(U64){_t2729});
                    (void)_va50;
                    Str_delete(_t2727, &(Bool){1});
                    ;
                    ;
                    U64 _t2730 = 0;
                    (void)_t2730;
                    Str *_t2731 = Str_clone(path);
                    (void)_t2731;
                    Array_set(_va50, &(U64){_t2730}, _t2731);
                    ;
                    U64 _t2732 = 1;
                    (void)_t2732;
                    Str *_t2733 = Str_lit(":", 1ULL);
                    (void)_t2733;
                    Array_set(_va50, &(U64){_t2732}, _t2733);
                    ;
                    U64 _t2734 = 2;
                    (void)_t2734;
                    Str *_t2735 = U32_to_str(&(U32){line});
                    (void)_t2735;
                    Array_set(_va50, &(U64){_t2734}, _t2735);
                    ;
                    U64 _t2736 = 3;
                    (void)_t2736;
                    Str *_t2737 = Str_lit(":", 1ULL);
                    (void)_t2737;
                    Array_set(_va50, &(U64){_t2736}, _t2737);
                    ;
                    U64 _t2738 = 4;
                    (void)_t2738;
                    Str *_t2739 = U32_to_str(&(U32){col});
                    (void)_t2739;
                    Array_set(_va50, &(U64){_t2738}, _t2739);
                    ;
                    U64 _t2740 = 5;
                    (void)_t2740;
                    Str *_t2741 = Str_lit(": error: unterminated comment", 29ULL);
                    (void)_t2741;
                    Array_set(_va50, &(U64){_t2740}, _t2741);
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
        Bool _t3004; { Bool *_hp = (Bool *)is_digit(c); _t3004 = *_hp; free(_hp); }
        (void)_t3004;
        if (_t3004) {
            while (1) {
                Bool _wcond2752; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2752 = *_hp; free(_hp); }
                (void)_wcond2752;
                if (_wcond2752) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2753 = Str_byte_at(src, pos);
                (void)_t2753;
                Bool _t2754; { Bool *_hp = (Bool *)is_digit(_t2753); _t2754 = *_hp; free(_hp); }
                (void)_t2754;
                Bool _t2755 = Bool_not(_t2754);
                (void)_t2755;
                ;
                if (_t2755) {
                    ;
                    break;
                }
                ;
                U64 _t2756 = U64_inc(DEREF(pos));
                (void)_t2756;
                *pos = _t2756;
                ;
            }
            U64 _t2771 = 1;
            (void)_t2771;
            U64 _t2772 = U64_add(DEREF(pos), _t2771);
            (void)_t2772;
            ;
            Bool _t2773; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2772}, &(U64){src_len}); _t2773 = *_hp; free(_hp); }
            (void)_t2773;
            ;
            if (_t2773) {
                U8 *_t2763 = Str_byte_at(src, pos);
                (void)_t2763;
                U8 _t2764 = 46;
                (void)_t2764;
                U64 _t2765 = 1;
                (void)_t2765;
                U64 *_t2766 = malloc(sizeof(U64)); *_t2766 = U64_add(DEREF(pos), _t2765);
                (void)_t2766;
                ;
                U8 *_t2767 = Str_byte_at(src, _t2766);
                (void)_t2767;
                Bool _t2768 = U8_eq(DEREF(_t2763), _t2764);
                (void)_t2768;
                ;
                Bool _t2769; { Bool *_hp = (Bool *)is_digit(_t2767); _t2769 = *_hp; free(_hp); }
                (void)_t2769;
                U64_delete(_t2766, &(Bool){1});
                Bool _t2770 = Bool_and(_t2768, _t2769);
                (void)_t2770;
                ;
                ;
                if (_t2770) {
                    U64 _t2762 = U64_inc(DEREF(pos));
                    (void)_t2762;
                    *pos = _t2762;
                    ;
                    while (1) {
                        Bool _wcond2757; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2757 = *_hp; free(_hp); }
                        (void)_wcond2757;
                        if (_wcond2757) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U8 *_t2758 = Str_byte_at(src, pos);
                        (void)_t2758;
                        Bool _t2759; { Bool *_hp = (Bool *)is_digit(_t2758); _t2759 = *_hp; free(_hp); }
                        (void)_t2759;
                        Bool _t2760 = Bool_not(_t2759);
                        (void)_t2760;
                        ;
                        if (_t2760) {
                            ;
                            break;
                        }
                        ;
                        U64 _t2761 = U64_inc(DEREF(pos));
                        (void)_t2761;
                        *pos = _t2761;
                        ;
                    }
                }
                ;
            }
            ;
            U64 _t2774 = U64_sub(DEREF(pos), start);
            (void)_t2774;
            Str *_t2775 = Str_substr(src, &(U64){start}, &(U64){_t2774});
            (void)_t2775;
            ;
            U32 _t2776 = U32_clone(&(U32){col});
            (void)_t2776;
            Token *_t2777 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(TokenType_Number()); _t2777->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(_t2775); _t2777->text = *_ca; free(_ca); }
            _t2777->line = U32_clone(&(U32){line});
            _t2777->col = _t2776;
            (void)_t2777;
            Str_delete(_t2775, &(Bool){1});
            ;
            Vec_push(tokens, _t2777);
            ;
            ;
            ;
            continue;
        }
        ;
        Bool _t3005; { Bool *_hp = (Bool *)is_alpha(c); _t3005 = *_hp; free(_hp); }
        (void)_t3005;
        if (_t3005) {
            while (1) {
                Bool _wcond2778; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2778 = *_hp; free(_hp); }
                (void)_wcond2778;
                if (_wcond2778) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2779 = Str_byte_at(src, pos);
                (void)_t2779;
                Bool _t2780; { Bool *_hp = (Bool *)is_alnum(_t2779); _t2780 = *_hp; free(_hp); }
                (void)_t2780;
                Bool _t2781 = Bool_not(_t2780);
                (void)_t2781;
                ;
                if (_t2781) {
                    ;
                    break;
                }
                ;
                U64 _t2782 = U64_inc(DEREF(pos));
                (void)_t2782;
                *pos = _t2782;
                ;
            }
            U64 _t2783 = U64_sub(DEREF(pos), start);
            (void)_t2783;
            Str *word = Str_substr(src, &(U64){start}, &(U64){_t2783});
            (void)word;
            ;
            TokenType *type = lookup_keyword(word);
            (void)type;
            U32 _t2784 = U32_clone(&(U32){line});
            (void)_t2784;
            U32 _t2785 = U32_clone(&(U32){col});
            (void)_t2785;
            Token *_t2786 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(type); _t2786->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(word); _t2786->text = *_ca; free(_ca); }
            _t2786->line = _t2784;
            _t2786->col = _t2785;
            (void)_t2786;
            ;
            ;
            TokenType_delete(type, &(Bool){1});
            Str_delete(word, &(Bool){1});
            Vec_push(tokens, _t2786);
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t3006 = 34;
        (void)_t3006;
        Bool _t3007 = U8_eq(DEREF(c), _t3006);
        (void)_t3007;
        ;
        if (_t3007) {
            U64 _t2835 = U64_inc(DEREF(pos));
            (void)_t2835;
            *pos = _t2835;
            ;
            while (1) {
                Bool _wcond2787; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2787 = *_hp; free(_hp); }
                (void)_wcond2787;
                if (_wcond2787) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2793 = Str_byte_at(src, pos);
                (void)_t2793;
                U8 _t2794 = 34;
                (void)_t2794;
                Bool _t2795 = U8_eq(DEREF(_t2793), _t2794);
                (void)_t2795;
                ;
                if (_t2795) {
                    ;
                    break;
                }
                ;
                U8 *_t2796 = Str_byte_at(src, pos);
                (void)_t2796;
                U8 _t2797 = 92;
                (void)_t2797;
                U64 _t2798 = 1;
                (void)_t2798;
                U64 _t2799 = U64_add(DEREF(pos), _t2798);
                (void)_t2799;
                ;
                Bool _t2800 = U8_eq(DEREF(_t2796), _t2797);
                (void)_t2800;
                ;
                Bool _t2801; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2799}, &(U64){src_len}); _t2801 = *_hp; free(_hp); }
                (void)_t2801;
                ;
                Bool _t2802 = Bool_and(_t2800, _t2801);
                (void)_t2802;
                ;
                ;
                if (_t2802) {
                    U64 _t2788 = U64_inc(DEREF(pos));
                    (void)_t2788;
                    *pos = _t2788;
                    ;
                }
                ;
                U8 *_t2803 = Str_byte_at(src, pos);
                (void)_t2803;
                U8 _t2804 = 10;
                (void)_t2804;
                Bool _t2805 = U8_eq(DEREF(_t2803), _t2804);
                (void)_t2805;
                ;
                if (_t2805) {
                    U32 _t2789 = 1;
                    (void)_t2789;
                    U32 _t2790 = U32_add(line, _t2789);
                    (void)_t2790;
                    ;
                    line = _t2790;
                    ;
                    U64 _t2791 = 1;
                    (void)_t2791;
                    U64 _t2792 = U64_add(DEREF(pos), _t2791);
                    (void)_t2792;
                    ;
                    line_start = _t2792;
                    ;
                }
                ;
                U64 _t2806 = U64_inc(DEREF(pos));
                (void)_t2806;
                *pos = _t2806;
                ;
            }
            U8 *_t2836 = Str_byte_at(src, pos);
            (void)_t2836;
            U8 _t2837 = 34;
            (void)_t2837;
            Bool _t2838; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2838 = *_hp; free(_hp); }
            (void)_t2838;
            Bool _t2839 = U8_eq(DEREF(_t2836), _t2837);
            (void)_t2839;
            ;
            Bool _t2840 = Bool_and(_t2838, _t2839);
            (void)_t2840;
            ;
            ;
            if (_t2840) {
                U64 _t2807 = U64_inc(DEREF(pos));
                (void)_t2807;
                *pos = _t2807;
                ;
                U64 _t2808 = 1;
                (void)_t2808;
                U64 _t2809 = U64_sub(DEREF(pos), start);
                (void)_t2809;
                U64 _t2810 = 2;
                (void)_t2810;
                U64 _t2811 = U64_add(start, _t2808);
                (void)_t2811;
                ;
                U64 _t2812 = U64_sub(_t2809, _t2810);
                (void)_t2812;
                ;
                ;
                Str *_t2813 = Str_substr(src, &(U64){_t2811}, &(U64){_t2812});
                (void)_t2813;
                ;
                ;
                U32 _t2814 = U32_clone(&(U32){col});
                (void)_t2814;
                Token *_t2815 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_StringTok()); _t2815->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2813); _t2815->text = *_ca; free(_ca); }
                _t2815->line = U32_clone(&(U32){line});
                _t2815->col = _t2814;
                (void)_t2815;
                Str_delete(_t2813, &(Bool){1});
                ;
                Vec_push(tokens, _t2815);
            } else {
                Str *_t2816 = Str_lit("Str", 3ULL);
                (void)_t2816;
                U64 _t2817; { U64 *_hp = (U64 *)Str_size(); _t2817 = *_hp; free(_hp); }
                (void)_t2817;
                U64 _t2818 = 6;
                (void)_t2818;
                Array *_va51 = Array_new(_t2816, &(U64){_t2817}, &(U64){_t2818});
                (void)_va51;
                Str_delete(_t2816, &(Bool){1});
                ;
                ;
                U64 _t2819 = 0;
                (void)_t2819;
                Str *_t2820 = Str_clone(path);
                (void)_t2820;
                Array_set(_va51, &(U64){_t2819}, _t2820);
                ;
                U64 _t2821 = 1;
                (void)_t2821;
                Str *_t2822 = Str_lit(":", 1ULL);
                (void)_t2822;
                Array_set(_va51, &(U64){_t2821}, _t2822);
                ;
                U64 _t2823 = 2;
                (void)_t2823;
                Str *_t2824 = U32_to_str(&(U32){line});
                (void)_t2824;
                Array_set(_va51, &(U64){_t2823}, _t2824);
                ;
                U64 _t2825 = 3;
                (void)_t2825;
                Str *_t2826 = Str_lit(":", 1ULL);
                (void)_t2826;
                Array_set(_va51, &(U64){_t2825}, _t2826);
                ;
                U64 _t2827 = 4;
                (void)_t2827;
                Str *_t2828 = U32_to_str(&(U32){col});
                (void)_t2828;
                Array_set(_va51, &(U64){_t2827}, _t2828);
                ;
                U64 _t2829 = 5;
                (void)_t2829;
                Str *_t2830 = Str_lit(": error: unterminated string", 28ULL);
                (void)_t2830;
                Array_set(_va51, &(U64){_t2829}, _t2830);
                ;
                println(_va51);
                U64 _t2831 = U64_sub(DEREF(pos), start);
                (void)_t2831;
                Str *_t2832 = Str_substr(src, &(U64){start}, &(U64){_t2831});
                (void)_t2832;
                ;
                U32 _t2833 = U32_clone(&(U32){col});
                (void)_t2833;
                Token *_t2834 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2834->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2832); _t2834->text = *_ca; free(_ca); }
                _t2834->line = U32_clone(&(U32){line});
                _t2834->col = _t2833;
                (void)_t2834;
                Str_delete(_t2832, &(Bool){1});
                ;
                Vec_push(tokens, _t2834);
            }
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t3008 = 39;
        (void)_t3008;
        Bool _t3009 = U8_eq(DEREF(c), _t3008);
        (void)_t3009;
        ;
        if (_t3009) {
            U64 _t2866 = U64_inc(DEREF(pos));
            (void)_t2866;
            *pos = _t2866;
            ;
            U64 ch_start = U64_clone(pos);
            (void)ch_start;
            U8 *_t2867 = Str_byte_at(src, pos);
            (void)_t2867;
            U8 _t2868 = 92;
            (void)_t2868;
            U64 _t2869 = 1;
            (void)_t2869;
            U64 _t2870 = U64_add(DEREF(pos), _t2869);
            (void)_t2870;
            ;
            Bool _t2871 = U8_eq(DEREF(_t2867), _t2868);
            (void)_t2871;
            ;
            Bool _t2872; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2870}, &(U64){src_len}); _t2872 = *_hp; free(_hp); }
            (void)_t2872;
            ;
            Bool _t2873; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2873 = *_hp; free(_hp); }
            (void)_t2873;
            Bool _t2874 = Bool_and(_t2871, _t2872);
            (void)_t2874;
            ;
            ;
            Bool _t2875 = Bool_and(_t2873, _t2874);
            (void)_t2875;
            ;
            ;
            if (_t2875) {
                U64 _t2841 = U64_inc(DEREF(pos));
                (void)_t2841;
                *pos = _t2841;
                ;
            }
            ;
            U64 _t2876 = U64_inc(DEREF(pos));
            (void)_t2876;
            *pos = _t2876;
            ;
            U8 *_t2877 = Str_byte_at(src, pos);
            (void)_t2877;
            U8 _t2878 = 39;
            (void)_t2878;
            Bool _t2879; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2879 = *_hp; free(_hp); }
            (void)_t2879;
            Bool _t2880 = U8_eq(DEREF(_t2877), _t2878);
            (void)_t2880;
            ;
            Bool _t2881 = Bool_and(_t2879, _t2880);
            (void)_t2881;
            ;
            ;
            if (_t2881) {
                U64 _t2842 = U64_sub(DEREF(pos), ch_start);
                (void)_t2842;
                Str *_t2843 = Str_substr(src, &(U64){ch_start}, &(U64){_t2842});
                (void)_t2843;
                ;
                U32 _t2844 = U32_clone(&(U32){col});
                (void)_t2844;
                Token *_t2845 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Char()); _t2845->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2843); _t2845->text = *_ca; free(_ca); }
                _t2845->line = U32_clone(&(U32){line});
                _t2845->col = _t2844;
                (void)_t2845;
                Str_delete(_t2843, &(Bool){1});
                ;
                Vec_push(tokens, _t2845);
                U64 _t2846 = U64_inc(DEREF(pos));
                (void)_t2846;
                *pos = _t2846;
                ;
            } else {
                Str *_t2847 = Str_lit("Str", 3ULL);
                (void)_t2847;
                U64 _t2848; { U64 *_hp = (U64 *)Str_size(); _t2848 = *_hp; free(_hp); }
                (void)_t2848;
                U64 _t2849 = 6;
                (void)_t2849;
                Array *_va52 = Array_new(_t2847, &(U64){_t2848}, &(U64){_t2849});
                (void)_va52;
                Str_delete(_t2847, &(Bool){1});
                ;
                ;
                U64 _t2850 = 0;
                (void)_t2850;
                Str *_t2851 = Str_clone(path);
                (void)_t2851;
                Array_set(_va52, &(U64){_t2850}, _t2851);
                ;
                U64 _t2852 = 1;
                (void)_t2852;
                Str *_t2853 = Str_lit(":", 1ULL);
                (void)_t2853;
                Array_set(_va52, &(U64){_t2852}, _t2853);
                ;
                U64 _t2854 = 2;
                (void)_t2854;
                Str *_t2855 = U32_to_str(&(U32){line});
                (void)_t2855;
                Array_set(_va52, &(U64){_t2854}, _t2855);
                ;
                U64 _t2856 = 3;
                (void)_t2856;
                Str *_t2857 = Str_lit(":", 1ULL);
                (void)_t2857;
                Array_set(_va52, &(U64){_t2856}, _t2857);
                ;
                U64 _t2858 = 4;
                (void)_t2858;
                Str *_t2859 = U32_to_str(&(U32){col});
                (void)_t2859;
                Array_set(_va52, &(U64){_t2858}, _t2859);
                ;
                U64 _t2860 = 5;
                (void)_t2860;
                Str *_t2861 = Str_lit(": error: unterminated character literal", 39ULL);
                (void)_t2861;
                Array_set(_va52, &(U64){_t2860}, _t2861);
                ;
                println(_va52);
                U64 _t2862 = U64_sub(DEREF(pos), start);
                (void)_t2862;
                Str *_t2863 = Str_substr(src, &(U64){start}, &(U64){_t2862});
                (void)_t2863;
                ;
                U32 _t2864 = U32_clone(&(U32){col});
                (void)_t2864;
                Token *_t2865 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2865->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2863); _t2865->text = *_ca; free(_ca); }
                _t2865->line = U32_clone(&(U32){line});
                _t2865->col = _t2864;
                (void)_t2865;
                Str_delete(_t2863, &(Bool){1});
                ;
                Vec_push(tokens, _t2865);
            }
            ;
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U64 _t3010 = 1;
        (void)_t3010;
        U64 _t3011 = U64_add(DEREF(pos), _t3010);
        (void)_t3011;
        ;
        Bool _t3012; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3011}, &(U64){src_len}); _t3012 = *_hp; free(_hp); }
        (void)_t3012;
        ;
        if (_t3012) {
            U64 _t2927 = 1;
            (void)_t2927;
            U64 *_t2928 = malloc(sizeof(U64)); *_t2928 = U64_add(DEREF(pos), _t2927);
            (void)_t2928;
            ;
            U8 *c2 = Str_byte_at(src, _t2928);
            (void)c2;
            TokenType *two = TokenType_clone(TokenType_Eof());
            (void)two;
            U8 _t2929 = 58;
            (void)_t2929;
            U8 _t2930 = 61;
            (void)_t2930;
            Bool _t2931 = U8_eq(DEREF(c), _t2929);
            (void)_t2931;
            ;
            Bool _t2932 = U8_eq(DEREF(c2), _t2930);
            (void)_t2932;
            ;
            Bool _t2933 = Bool_and(_t2931, _t2932);
            (void)_t2933;
            ;
            ;
            if (_t2933) {
                two = TokenType_clone(TokenType_ColonEq());
            } else {
                U8 _t2915 = 61;
                (void)_t2915;
                U8 _t2916 = 61;
                (void)_t2916;
                Bool _t2917 = U8_eq(DEREF(c), _t2915);
                (void)_t2917;
                ;
                Bool _t2918 = U8_eq(DEREF(c2), _t2916);
                (void)_t2918;
                ;
                Bool _t2919 = Bool_and(_t2917, _t2918);
                (void)_t2919;
                ;
                ;
                if (_t2919) {
                    two = TokenType_clone(TokenType_EqEq());
                } else {
                    U8 _t2910 = 33;
                    (void)_t2910;
                    U8 _t2911 = 61;
                    (void)_t2911;
                    Bool _t2912 = U8_eq(DEREF(c), _t2910);
                    (void)_t2912;
                    ;
                    Bool _t2913 = U8_eq(DEREF(c2), _t2911);
                    (void)_t2913;
                    ;
                    Bool _t2914 = Bool_and(_t2912, _t2913);
                    (void)_t2914;
                    ;
                    ;
                    if (_t2914) {
                        two = TokenType_clone(TokenType_Neq());
                    } else {
                        U8 _t2905 = 60;
                        (void)_t2905;
                        U8 _t2906 = 61;
                        (void)_t2906;
                        Bool _t2907 = U8_eq(DEREF(c), _t2905);
                        (void)_t2907;
                        ;
                        Bool _t2908 = U8_eq(DEREF(c2), _t2906);
                        (void)_t2908;
                        ;
                        Bool _t2909 = Bool_and(_t2907, _t2908);
                        (void)_t2909;
                        ;
                        ;
                        if (_t2909) {
                            two = TokenType_clone(TokenType_LtEq());
                        } else {
                            U8 _t2900 = 62;
                            (void)_t2900;
                            U8 _t2901 = 61;
                            (void)_t2901;
                            Bool _t2902 = U8_eq(DEREF(c), _t2900);
                            (void)_t2902;
                            ;
                            Bool _t2903 = U8_eq(DEREF(c2), _t2901);
                            (void)_t2903;
                            ;
                            Bool _t2904 = Bool_and(_t2902, _t2903);
                            (void)_t2904;
                            ;
                            ;
                            if (_t2904) {
                                two = TokenType_clone(TokenType_GtEq());
                            } else {
                                U8 _t2895 = 46;
                                (void)_t2895;
                                U8 _t2896 = 46;
                                (void)_t2896;
                                Bool _t2897 = U8_eq(DEREF(c), _t2895);
                                (void)_t2897;
                                ;
                                Bool _t2898 = U8_eq(DEREF(c2), _t2896);
                                (void)_t2898;
                                ;
                                Bool _t2899 = Bool_and(_t2897, _t2898);
                                (void)_t2899;
                                ;
                                ;
                                if (_t2899) {
                                    U64 _t2892 = 2;
                                    (void)_t2892;
                                    U64 _t2893 = U64_add(DEREF(pos), _t2892);
                                    (void)_t2893;
                                    ;
                                    Bool _t2894; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2893}, &(U64){src_len}); _t2894 = *_hp; free(_hp); }
                                    (void)_t2894;
                                    ;
                                    if (_t2894) {
                                        U64 _t2888 = 2;
                                        (void)_t2888;
                                        U64 *_t2889 = malloc(sizeof(U64)); *_t2889 = U64_add(DEREF(pos), _t2888);
                                        (void)_t2889;
                                        ;
                                        U8 *c3 = Str_byte_at(src, _t2889);
                                        (void)c3;
                                        U8 _t2890 = 46;
                                        (void)_t2890;
                                        Bool _t2891 = U8_eq(DEREF(c3), _t2890);
                                        (void)_t2891;
                                        U64_delete(_t2889, &(Bool){1});
                                        ;
                                        if (_t2891) {
                                            U64 _t2882 = 3;
                                            (void)_t2882;
                                            Str *_t2883 = Str_substr(src, &(U64){start}, &(U64){_t2882});
                                            (void)_t2883;
                                            ;
                                            U32 _t2884 = U32_clone(&(U32){col});
                                            (void)_t2884;
                                            Token *_t2885 = malloc(sizeof(Token));
                                            { TokenType *_ca = TokenType_clone(TokenType_DotDotDot()); _t2885->type = *_ca; free(_ca); }
                                            { Str *_ca = Str_clone(_t2883); _t2885->text = *_ca; free(_ca); }
                                            _t2885->line = U32_clone(&(U32){line});
                                            _t2885->col = _t2884;
                                            (void)_t2885;
                                            Str_delete(_t2883, &(Bool){1});
                                            ;
                                            Vec_push(tokens, _t2885);
                                            U64 _t2886 = 3;
                                            (void)_t2886;
                                            U64 _t2887 = U64_add(DEREF(pos), _t2886);
                                            (void)_t2887;
                                            ;
                                            *pos = _t2887;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            U64_delete(_t2928, &(Bool){1});
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
            U64_delete(_t2928, &(Bool){1});
            ;
            Bool _t2934; { Bool *_hp = (Bool *)TokenType_eq(two, TokenType_Eof()); _t2934 = *_hp; free(_hp); }
            (void)_t2934;
            Bool _t2935 = Bool_not(_t2934);
            (void)_t2935;
            ;
            if (_t2935) {
                U64 _t2920 = 2;
                (void)_t2920;
                Str *_t2921 = Str_substr(src, &(U64){start}, &(U64){_t2920});
                (void)_t2921;
                ;
                U32 _t2922 = U32_clone(&(U32){line});
                (void)_t2922;
                U32 _t2923 = U32_clone(&(U32){col});
                (void)_t2923;
                Token *_t2924 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(two); _t2924->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2921); _t2924->text = *_ca; free(_ca); }
                _t2924->line = _t2922;
                _t2924->col = _t2923;
                (void)_t2924;
                Str_delete(_t2921, &(Bool){1});
                ;
                ;
                Vec_push(tokens, _t2924);
                U64 _t2925 = 2;
                (void)_t2925;
                U64 _t2926 = U64_add(DEREF(pos), _t2925);
                (void)_t2926;
                ;
                *pos = _t2926;
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
            U8 _sw2936 = U8_clone(c);
            (void)_sw2936;
            U8 _t2971 = 40;
            (void)_t2971;
            Bool _t2972 = U8_eq(_sw2936, _t2971);
            (void)_t2972;
            ;
            if (_t2972) {
                single = TokenType_clone(TokenType_LParen());
            } else {
                U8 _t2969 = 41;
                (void)_t2969;
                Bool _t2970 = U8_eq(_sw2936, _t2969);
                (void)_t2970;
                ;
                if (_t2970) {
                    single = TokenType_clone(TokenType_RParen());
                } else {
                    U8 _t2967 = 123;
                    (void)_t2967;
                    Bool _t2968 = U8_eq(_sw2936, _t2967);
                    (void)_t2968;
                    ;
                    if (_t2968) {
                        single = TokenType_clone(TokenType_LBrace());
                    } else {
                        U8 _t2965 = 125;
                        (void)_t2965;
                        Bool _t2966 = U8_eq(_sw2936, _t2965);
                        (void)_t2966;
                        ;
                        if (_t2966) {
                            single = TokenType_clone(TokenType_RBrace());
                        } else {
                            U8 _t2963 = 91;
                            (void)_t2963;
                            Bool _t2964 = U8_eq(_sw2936, _t2963);
                            (void)_t2964;
                            ;
                            if (_t2964) {
                                single = TokenType_clone(TokenType_LBracket());
                            } else {
                                U8 _t2961 = 93;
                                (void)_t2961;
                                Bool _t2962 = U8_eq(_sw2936, _t2961);
                                (void)_t2962;
                                ;
                                if (_t2962) {
                                    single = TokenType_clone(TokenType_RBracket());
                                } else {
                                    U8 _t2959 = 44;
                                    (void)_t2959;
                                    Bool _t2960 = U8_eq(_sw2936, _t2959);
                                    (void)_t2960;
                                    ;
                                    if (_t2960) {
                                        single = TokenType_clone(TokenType_Comma());
                                    } else {
                                        U8 _t2957 = 58;
                                        (void)_t2957;
                                        Bool _t2958 = U8_eq(_sw2936, _t2957);
                                        (void)_t2958;
                                        ;
                                        if (_t2958) {
                                            single = TokenType_clone(TokenType_Colon());
                                        } else {
                                            U8 _t2955 = 46;
                                            (void)_t2955;
                                            Bool _t2956 = U8_eq(_sw2936, _t2955);
                                            (void)_t2956;
                                            ;
                                            if (_t2956) {
                                                single = TokenType_clone(TokenType_Dot());
                                            } else {
                                                U8 _t2953 = 63;
                                                (void)_t2953;
                                                Bool _t2954 = U8_eq(_sw2936, _t2953);
                                                (void)_t2954;
                                                ;
                                                if (_t2954) {
                                                    single = TokenType_clone(TokenType_Question());
                                                } else {
                                                    U8 _t2951 = 33;
                                                    (void)_t2951;
                                                    Bool _t2952 = U8_eq(_sw2936, _t2951);
                                                    (void)_t2952;
                                                    ;
                                                    if (_t2952) {
                                                        single = TokenType_clone(TokenType_Bang());
                                                    } else {
                                                        U8 _t2949 = 43;
                                                        (void)_t2949;
                                                        Bool _t2950 = U8_eq(_sw2936, _t2949);
                                                        (void)_t2950;
                                                        ;
                                                        if (_t2950) {
                                                            single = TokenType_clone(TokenType_Plus());
                                                        } else {
                                                            U8 _t2947 = 45;
                                                            (void)_t2947;
                                                            Bool _t2948 = U8_eq(_sw2936, _t2947);
                                                            (void)_t2948;
                                                            ;
                                                            if (_t2948) {
                                                                single = TokenType_clone(TokenType_Minus());
                                                            } else {
                                                                U8 _t2945 = 42;
                                                                (void)_t2945;
                                                                Bool _t2946 = U8_eq(_sw2936, _t2945);
                                                                (void)_t2946;
                                                                ;
                                                                if (_t2946) {
                                                                    single = TokenType_clone(TokenType_Star());
                                                                } else {
                                                                    U8 _t2943 = 47;
                                                                    (void)_t2943;
                                                                    Bool _t2944 = U8_eq(_sw2936, _t2943);
                                                                    (void)_t2944;
                                                                    ;
                                                                    if (_t2944) {
                                                                        single = TokenType_clone(TokenType_Slash());
                                                                    } else {
                                                                        U8 _t2941 = 61;
                                                                        (void)_t2941;
                                                                        Bool _t2942 = U8_eq(_sw2936, _t2941);
                                                                        (void)_t2942;
                                                                        ;
                                                                        if (_t2942) {
                                                                            single = TokenType_clone(TokenType_Eq());
                                                                        } else {
                                                                            U8 _t2939 = 60;
                                                                            (void)_t2939;
                                                                            Bool _t2940 = U8_eq(_sw2936, _t2939);
                                                                            (void)_t2940;
                                                                            ;
                                                                            if (_t2940) {
                                                                                single = TokenType_clone(TokenType_Lt());
                                                                            } else {
                                                                                U8 _t2937 = 62;
                                                                                (void)_t2937;
                                                                                Bool _t2938 = U8_eq(_sw2936, _t2937);
                                                                                (void)_t2938;
                                                                                ;
                                                                                if (_t2938) {
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
        Bool _t3013; { Bool *_hp = (Bool *)TokenType_eq(single, TokenType_Eof()); _t3013 = *_hp; free(_hp); }
        (void)_t3013;
        Bool _t3014 = Bool_not(_t3013);
        (void)_t3014;
        ;
        if (_t3014) {
            U64 _t2973 = 1;
            (void)_t2973;
            Str *_t2974 = Str_substr(src, &(U64){start}, &(U64){_t2973});
            (void)_t2974;
            ;
            U32 _t2975 = U32_clone(&(U32){line});
            (void)_t2975;
            U32 _t2976 = U32_clone(&(U32){col});
            (void)_t2976;
            Token *_t2977 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(single); _t2977->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(_t2974); _t2977->text = *_ca; free(_ca); }
            _t2977->line = _t2975;
            _t2977->col = _t2976;
            (void)_t2977;
            Str_delete(_t2974, &(Bool){1});
            ;
            ;
            Vec_push(tokens, _t2977);
            U64 _t2978 = U64_inc(DEREF(pos));
            (void)_t2978;
            *pos = _t2978;
            ;
            ;
            ;
            TokenType_delete(single, &(Bool){1});
            ;
            continue;
        }
        ;
        TokenType_delete(single, &(Bool){1});
        Str *_t3015 = Str_lit("Str", 3ULL);
        (void)_t3015;
        U64 _t3016; { U64 *_hp = (U64 *)Str_size(); _t3016 = *_hp; free(_hp); }
        (void)_t3016;
        U64 _t3017 = 6;
        (void)_t3017;
        Array *_va53 = Array_new(_t3015, &(U64){_t3016}, &(U64){_t3017});
        (void)_va53;
        Str_delete(_t3015, &(Bool){1});
        ;
        ;
        U64 _t3018 = 0;
        (void)_t3018;
        Str *_t3019 = Str_clone(path);
        (void)_t3019;
        Array_set(_va53, &(U64){_t3018}, _t3019);
        ;
        U64 _t3020 = 1;
        (void)_t3020;
        Str *_t3021 = Str_lit(":", 1ULL);
        (void)_t3021;
        Array_set(_va53, &(U64){_t3020}, _t3021);
        ;
        U64 _t3022 = 2;
        (void)_t3022;
        Str *_t3023 = U32_to_str(&(U32){line});
        (void)_t3023;
        Array_set(_va53, &(U64){_t3022}, _t3023);
        ;
        U64 _t3024 = 3;
        (void)_t3024;
        Str *_t3025 = Str_lit(":", 1ULL);
        (void)_t3025;
        Array_set(_va53, &(U64){_t3024}, _t3025);
        ;
        U64 _t3026 = 4;
        (void)_t3026;
        Str *_t3027 = U32_to_str(&(U32){col});
        (void)_t3027;
        Array_set(_va53, &(U64){_t3026}, _t3027);
        ;
        U64 _t3028 = 5;
        (void)_t3028;
        Str *_t3029 = Str_lit(": error: unexpected character", 29ULL);
        (void)_t3029;
        Array_set(_va53, &(U64){_t3028}, _t3029);
        ;
        println(_va53);
        U64 _t3030 = 1;
        (void)_t3030;
        Str *_t3031 = Str_substr(src, &(U64){start}, &(U64){_t3030});
        (void)_t3031;
        ;
        ;
        U32 _t3032 = U32_clone(&(U32){col});
        (void)_t3032;
        ;
        Token *_t3033 = malloc(sizeof(Token));
        { TokenType *_ca = TokenType_clone(TokenType_Error()); _t3033->type = *_ca; free(_ca); }
        { Str *_ca = Str_clone(_t3031); _t3033->text = *_ca; free(_ca); }
        _t3033->line = U32_clone(&(U32){line});
        _t3033->col = _t3032;
        (void)_t3033;
        Str_delete(_t3031, &(Bool){1});
        ;
        Vec_push(tokens, _t3033);
        U64 _t3034 = U64_inc(DEREF(pos));
        (void)_t3034;
        *pos = _t3034;
        ;
    }
    ;
    U64 _t3037 = U64_sub(DEREF(pos), line_start);
    (void)_t3037;
    ;
    U64_delete(pos, &(Bool){1});
    U64 _t3038 = 1;
    (void)_t3038;
    U64 _t3039 = U64_add(_t3037, _t3038);
    (void)_t3039;
    ;
    ;
    I64 col = U64_to_i64(_t3039);
    (void)col;
    ;
    I64 _t3040 = I64_clone(&(I64){col});
    (void)_t3040;
    ;
    Token *_t3041 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(TokenType_Eof()); _t3041->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t3041->text = *_ca; free(_ca); }
    _t3041->line = U32_clone(&(U32){line});
    _t3041->col = _t3040;
    (void)_t3041;
    ;
    ;
    Vec_push(tokens, _t3041);
    return tokens;
}

