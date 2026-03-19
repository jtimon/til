#include "til_lexer.h"

Token * Token_clone(Token * self) {
    (void)self;
    U32 _t2447 = U32_clone(&self->line);
    (void)_t2447;
    U32 _t2448 = U32_clone(&self->col);
    (void)_t2448;
    Token *_t2449 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(&self->type); _t2449->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->text); _t2449->text = *_ca; free(_ca); }
    _t2449->line = _t2447;
    _t2449->col = _t2448;
    (void)_t2449;
    ;
    ;
    return _t2449;
}

void Token_delete(Token * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t2450 = 0;
    (void)_t2450;
    TokenType_delete(&self->type, &(Bool){_t2450});
    ;
    Bool _t2451 = 0;
    (void)_t2451;
    Str_delete(&self->text, &(Bool){_t2451});
    ;
    Bool _t2452 = 0;
    (void)_t2452;
    U32_delete(&self->line, &(Bool){_t2452});
    ;
    Bool _t2453 = 0;
    (void)_t2453;
    U32_delete(&self->col, &(Bool){_t2453});
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
    U8 _t2455 = 48;
    (void)_t2455;
    U8 _t2456 = 57;
    (void)_t2456;
    Bool _t2457; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t2455}); _t2457 = *_hp; free(_hp); }
    (void)_t2457;
    ;
    Bool _t2458; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t2456}); _t2458 = *_hp; free(_hp); }
    (void)_t2458;
    ;
    Bool _t2459 = Bool_and(_t2457, _t2458);
    (void)_t2459;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2459; return _r; }
}

Bool * is_alpha(U8 * c) {
    (void)c;
    U8 _t2460 = 97;
    (void)_t2460;
    U8 _t2461 = 122;
    (void)_t2461;
    Bool _t2462; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t2460}); _t2462 = *_hp; free(_hp); }
    (void)_t2462;
    ;
    Bool _t2463; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t2461}); _t2463 = *_hp; free(_hp); }
    (void)_t2463;
    ;
    U8 _t2464 = 65;
    (void)_t2464;
    U8 _t2465 = 90;
    (void)_t2465;
    Bool _t2466; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t2464}); _t2466 = *_hp; free(_hp); }
    (void)_t2466;
    ;
    Bool _t2467; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t2465}); _t2467 = *_hp; free(_hp); }
    (void)_t2467;
    ;
    Bool _t2468 = Bool_and(_t2462, _t2463);
    (void)_t2468;
    ;
    ;
    Bool _t2469 = Bool_and(_t2466, _t2467);
    (void)_t2469;
    ;
    ;
    U8 _t2470 = 95;
    (void)_t2470;
    Bool _t2471 = Bool_or(_t2468, _t2469);
    (void)_t2471;
    ;
    ;
    Bool _t2472 = U8_eq(DEREF(c), _t2470);
    (void)_t2472;
    ;
    Bool _t2473 = Bool_or(_t2471, _t2472);
    (void)_t2473;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2473; return _r; }
}

Bool * is_alnum(U8 * c) {
    (void)c;
    Bool _t2474; { Bool *_hp = (Bool *)is_alpha(c); _t2474 = *_hp; free(_hp); }
    (void)_t2474;
    Bool _t2475; { Bool *_hp = (Bool *)is_digit(c); _t2475 = *_hp; free(_hp); }
    (void)_t2475;
    Bool _t2476 = Bool_or(_t2474, _t2475);
    (void)_t2476;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2476; return _r; }
}

Str * tok_name(TokenType * type) {
    (void)type;
    {
        TokenType *_sw2477 = TokenType_clone(type);
        (void)_sw2477;
        Bool _t2610; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_Eof()); _t2610 = *_hp; free(_hp); }
        (void)_t2610;
        if (_t2610) {
            Str *_t2478 = Str_lit("eof", 3ULL);
            (void)_t2478;
            TokenType_delete(_sw2477, &(Bool){1});
            ;
            return _t2478;
        } else {
            Bool _t2609; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_LParen()); _t2609 = *_hp; free(_hp); }
            (void)_t2609;
            if (_t2609) {
                Str *_t2479 = Str_lit("(", 1ULL);
                (void)_t2479;
                ;
                TokenType_delete(_sw2477, &(Bool){1});
                ;
                return _t2479;
            } else {
                Bool _t2608; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_RParen()); _t2608 = *_hp; free(_hp); }
                (void)_t2608;
                if (_t2608) {
                    Str *_t2480 = Str_lit(")", 1ULL);
                    (void)_t2480;
                    ;
                    ;
                    TokenType_delete(_sw2477, &(Bool){1});
                    ;
                    return _t2480;
                } else {
                    Bool _t2607; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_LBrace()); _t2607 = *_hp; free(_hp); }
                    (void)_t2607;
                    if (_t2607) {
                        Str *_t2481 = Str_lit("{", 1ULL);
                        (void)_t2481;
                        ;
                        ;
                        ;
                        TokenType_delete(_sw2477, &(Bool){1});
                        ;
                        return _t2481;
                    } else {
                        Bool _t2606; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_RBrace()); _t2606 = *_hp; free(_hp); }
                        (void)_t2606;
                        if (_t2606) {
                            Str *_t2482 = Str_lit("}", 1ULL);
                            (void)_t2482;
                            ;
                            ;
                            ;
                            ;
                            TokenType_delete(_sw2477, &(Bool){1});
                            ;
                            return _t2482;
                        } else {
                            Bool _t2605; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_LBracket()); _t2605 = *_hp; free(_hp); }
                            (void)_t2605;
                            if (_t2605) {
                                Str *_t2483 = Str_lit("[", 1ULL);
                                (void)_t2483;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TokenType_delete(_sw2477, &(Bool){1});
                                ;
                                return _t2483;
                            } else {
                                Bool _t2604; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_RBracket()); _t2604 = *_hp; free(_hp); }
                                (void)_t2604;
                                if (_t2604) {
                                    Str *_t2484 = Str_lit("]", 1ULL);
                                    (void)_t2484;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TokenType_delete(_sw2477, &(Bool){1});
                                    ;
                                    return _t2484;
                                } else {
                                    Bool _t2603; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_Comma()); _t2603 = *_hp; free(_hp); }
                                    (void)_t2603;
                                    if (_t2603) {
                                        Str *_t2485 = Str_lit(",", 1ULL);
                                        (void)_t2485;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TokenType_delete(_sw2477, &(Bool){1});
                                        ;
                                        return _t2485;
                                    } else {
                                        Bool _t2602; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_Colon()); _t2602 = *_hp; free(_hp); }
                                        (void)_t2602;
                                        if (_t2602) {
                                            Str *_t2486 = Str_lit(":", 1ULL);
                                            (void)_t2486;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TokenType_delete(_sw2477, &(Bool){1});
                                            ;
                                            return _t2486;
                                        } else {
                                            Bool _t2601; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_Question()); _t2601 = *_hp; free(_hp); }
                                            (void)_t2601;
                                            if (_t2601) {
                                                Str *_t2487 = Str_lit("?", 1ULL);
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
                                                TokenType_delete(_sw2477, &(Bool){1});
                                                ;
                                                return _t2487;
                                            } else {
                                                Bool _t2600; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_Bang()); _t2600 = *_hp; free(_hp); }
                                                (void)_t2600;
                                                if (_t2600) {
                                                    Str *_t2488 = Str_lit("!", 1ULL);
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
                                                    TokenType_delete(_sw2477, &(Bool){1});
                                                    ;
                                                    return _t2488;
                                                } else {
                                                    Bool _t2599; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_Minus()); _t2599 = *_hp; free(_hp); }
                                                    (void)_t2599;
                                                    if (_t2599) {
                                                        Str *_t2489 = Str_lit("-", 1ULL);
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
                                                        TokenType_delete(_sw2477, &(Bool){1});
                                                        ;
                                                        return _t2489;
                                                    } else {
                                                        Bool _t2598; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_Plus()); _t2598 = *_hp; free(_hp); }
                                                        (void)_t2598;
                                                        if (_t2598) {
                                                            Str *_t2490 = Str_lit("+", 1ULL);
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
                                                            TokenType_delete(_sw2477, &(Bool){1});
                                                            ;
                                                            return _t2490;
                                                        } else {
                                                            Bool _t2597; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_Star()); _t2597 = *_hp; free(_hp); }
                                                            (void)_t2597;
                                                            if (_t2597) {
                                                                Str *_t2491 = Str_lit("*", 1ULL);
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
                                                                TokenType_delete(_sw2477, &(Bool){1});
                                                                ;
                                                                return _t2491;
                                                            } else {
                                                                Bool _t2596; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_Slash()); _t2596 = *_hp; free(_hp); }
                                                                (void)_t2596;
                                                                if (_t2596) {
                                                                    Str *_t2492 = Str_lit("/", 1ULL);
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
                                                                    TokenType_delete(_sw2477, &(Bool){1});
                                                                    ;
                                                                    return _t2492;
                                                                } else {
                                                                    Bool _t2595; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_Dot()); _t2595 = *_hp; free(_hp); }
                                                                    (void)_t2595;
                                                                    if (_t2595) {
                                                                        Str *_t2493 = Str_lit(".", 1ULL);
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
                                                                        TokenType_delete(_sw2477, &(Bool){1});
                                                                        ;
                                                                        return _t2493;
                                                                    } else {
                                                                        Bool _t2594; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_DotDot()); _t2594 = *_hp; free(_hp); }
                                                                        (void)_t2594;
                                                                        if (_t2594) {
                                                                            Str *_t2494 = Str_lit("..", 2ULL);
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
                                                                            TokenType_delete(_sw2477, &(Bool){1});
                                                                            ;
                                                                            return _t2494;
                                                                        } else {
                                                                            Bool _t2593; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_DotDotDot()); _t2593 = *_hp; free(_hp); }
                                                                            (void)_t2593;
                                                                            if (_t2593) {
                                                                                Str *_t2495 = Str_lit("...", 3ULL);
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
                                                                                TokenType_delete(_sw2477, &(Bool){1});
                                                                                ;
                                                                                return _t2495;
                                                                            } else {
                                                                                Bool _t2592; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_Eq()); _t2592 = *_hp; free(_hp); }
                                                                                (void)_t2592;
                                                                                if (_t2592) {
                                                                                    Str *_t2496 = Str_lit("=", 1ULL);
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
                                                                                    TokenType_delete(_sw2477, &(Bool){1});
                                                                                    ;
                                                                                    return _t2496;
                                                                                } else {
                                                                                    Bool _t2591; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_EqEq()); _t2591 = *_hp; free(_hp); }
                                                                                    (void)_t2591;
                                                                                    if (_t2591) {
                                                                                        Str *_t2497 = Str_lit("==", 2ULL);
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
                                                                                        TokenType_delete(_sw2477, &(Bool){1});
                                                                                        ;
                                                                                        return _t2497;
                                                                                    } else {
                                                                                        Bool _t2590; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_Neq()); _t2590 = *_hp; free(_hp); }
                                                                                        (void)_t2590;
                                                                                        if (_t2590) {
                                                                                            Str *_t2498 = Str_lit("!=", 2ULL);
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
                                                                                            TokenType_delete(_sw2477, &(Bool){1});
                                                                                            ;
                                                                                            return _t2498;
                                                                                        } else {
                                                                                            Bool _t2589; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_Lt()); _t2589 = *_hp; free(_hp); }
                                                                                            (void)_t2589;
                                                                                            if (_t2589) {
                                                                                                Str *_t2499 = Str_lit("<", 1ULL);
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
                                                                                                TokenType_delete(_sw2477, &(Bool){1});
                                                                                                ;
                                                                                                return _t2499;
                                                                                            } else {
                                                                                                Bool _t2588; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_LtEq()); _t2588 = *_hp; free(_hp); }
                                                                                                (void)_t2588;
                                                                                                if (_t2588) {
                                                                                                    Str *_t2500 = Str_lit("<=", 2ULL);
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
                                                                                                    TokenType_delete(_sw2477, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t2500;
                                                                                                } else {
                                                                                                    Bool _t2587; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_Gt()); _t2587 = *_hp; free(_hp); }
                                                                                                    (void)_t2587;
                                                                                                    if (_t2587) {
                                                                                                        Str *_t2501 = Str_lit(">", 1ULL);
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
                                                                                                        TokenType_delete(_sw2477, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t2501;
                                                                                                    } else {
                                                                                                        Bool _t2586; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_GtEq()); _t2586 = *_hp; free(_hp); }
                                                                                                        (void)_t2586;
                                                                                                        if (_t2586) {
                                                                                                            Str *_t2502 = Str_lit(">=", 2ULL);
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
                                                                                                            TokenType_delete(_sw2477, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t2502;
                                                                                                        } else {
                                                                                                            Bool _t2585; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_ColonEq()); _t2585 = *_hp; free(_hp); }
                                                                                                            (void)_t2585;
                                                                                                            if (_t2585) {
                                                                                                                Str *_t2503 = Str_lit(":=", 2ULL);
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
                                                                                                                TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                ;
                                                                                                                return _t2503;
                                                                                                            } else {
                                                                                                                Bool _t2584; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_Ident()); _t2584 = *_hp; free(_hp); }
                                                                                                                (void)_t2584;
                                                                                                                if (_t2584) {
                                                                                                                    Str *_t2504 = Str_lit("identifier", 10ULL);
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
                                                                                                                    TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return _t2504;
                                                                                                                } else {
                                                                                                                    Bool _t2583; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_StringTok()); _t2583 = *_hp; free(_hp); }
                                                                                                                    (void)_t2583;
                                                                                                                    if (_t2583) {
                                                                                                                        Str *_t2505 = Str_lit("string", 6ULL);
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
                                                                                                                        TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return _t2505;
                                                                                                                    } else {
                                                                                                                        Bool _t2582; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_Number()); _t2582 = *_hp; free(_hp); }
                                                                                                                        (void)_t2582;
                                                                                                                        if (_t2582) {
                                                                                                                            Str *_t2506 = Str_lit("number", 6ULL);
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
                                                                                                                            TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return _t2506;
                                                                                                                        } else {
                                                                                                                            Bool _t2581; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_Char()); _t2581 = *_hp; free(_hp); }
                                                                                                                            (void)_t2581;
                                                                                                                            if (_t2581) {
                                                                                                                                Str *_t2507 = Str_lit("char", 4ULL);
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
                                                                                                                                TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return _t2507;
                                                                                                                            } else {
                                                                                                                                Bool _t2580; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwMode()); _t2580 = *_hp; free(_hp); }
                                                                                                                                (void)_t2580;
                                                                                                                                if (_t2580) {
                                                                                                                                    Str *_t2508 = Str_lit("mode", 4ULL);
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
                                                                                                                                    TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return _t2508;
                                                                                                                                } else {
                                                                                                                                    Bool _t2579; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwMut()); _t2579 = *_hp; free(_hp); }
                                                                                                                                    (void)_t2579;
                                                                                                                                    if (_t2579) {
                                                                                                                                        Str *_t2509 = Str_lit("mut", 3ULL);
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
                                                                                                                                        TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return _t2509;
                                                                                                                                    } else {
                                                                                                                                        Bool _t2578; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwOwn()); _t2578 = *_hp; free(_hp); }
                                                                                                                                        (void)_t2578;
                                                                                                                                        if (_t2578) {
                                                                                                                                            Str *_t2510 = Str_lit("own", 3ULL);
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
                                                                                                                                            TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return _t2510;
                                                                                                                                        } else {
                                                                                                                                            Bool _t2577; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwRef()); _t2577 = *_hp; free(_hp); }
                                                                                                                                            (void)_t2577;
                                                                                                                                            if (_t2577) {
                                                                                                                                                Str *_t2511 = Str_lit("ref", 3ULL);
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
                                                                                                                                                TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return _t2511;
                                                                                                                                            } else {
                                                                                                                                                Bool _t2576; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwShallow()); _t2576 = *_hp; free(_hp); }
                                                                                                                                                (void)_t2576;
                                                                                                                                                if (_t2576) {
                                                                                                                                                    Str *_t2512 = Str_lit("shallow", 7ULL);
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
                                                                                                                                                    TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                    ;
                                                                                                                                                    return _t2512;
                                                                                                                                                } else {
                                                                                                                                                    Bool _t2575; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwStruct()); _t2575 = *_hp; free(_hp); }
                                                                                                                                                    (void)_t2575;
                                                                                                                                                    if (_t2575) {
                                                                                                                                                        Str *_t2513 = Str_lit("struct", 6ULL);
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
                                                                                                                                                        TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                        ;
                                                                                                                                                        return _t2513;
                                                                                                                                                    } else {
                                                                                                                                                        Bool _t2574; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwExtStruct()); _t2574 = *_hp; free(_hp); }
                                                                                                                                                        (void)_t2574;
                                                                                                                                                        if (_t2574) {
                                                                                                                                                            Str *_t2514 = Str_lit("ext_struct", 10ULL);
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
                                                                                                                                                            TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                            ;
                                                                                                                                                            return _t2514;
                                                                                                                                                        } else {
                                                                                                                                                            Bool _t2573; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwEnum()); _t2573 = *_hp; free(_hp); }
                                                                                                                                                            (void)_t2573;
                                                                                                                                                            if (_t2573) {
                                                                                                                                                                Str *_t2515 = Str_lit("enum", 4ULL);
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
                                                                                                                                                                TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                ;
                                                                                                                                                                return _t2515;
                                                                                                                                                            } else {
                                                                                                                                                                Bool _t2572; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwNamespace()); _t2572 = *_hp; free(_hp); }
                                                                                                                                                                (void)_t2572;
                                                                                                                                                                if (_t2572) {
                                                                                                                                                                    Str *_t2516 = Str_lit("namespace", 9ULL);
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
                                                                                                                                                                    TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                    ;
                                                                                                                                                                    return _t2516;
                                                                                                                                                                } else {
                                                                                                                                                                    Bool _t2571; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwFunc()); _t2571 = *_hp; free(_hp); }
                                                                                                                                                                    (void)_t2571;
                                                                                                                                                                    if (_t2571) {
                                                                                                                                                                        Str *_t2517 = Str_lit("func", 4ULL);
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
                                                                                                                                                                        TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                        ;
                                                                                                                                                                        return _t2517;
                                                                                                                                                                    } else {
                                                                                                                                                                        Bool _t2570; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwProc()); _t2570 = *_hp; free(_hp); }
                                                                                                                                                                        (void)_t2570;
                                                                                                                                                                        if (_t2570) {
                                                                                                                                                                            Str *_t2518 = Str_lit("proc", 4ULL);
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
                                                                                                                                                                            TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                            ;
                                                                                                                                                                            return _t2518;
                                                                                                                                                                        } else {
                                                                                                                                                                            Bool _t2569; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwTest()); _t2569 = *_hp; free(_hp); }
                                                                                                                                                                            (void)_t2569;
                                                                                                                                                                            if (_t2569) {
                                                                                                                                                                                Str *_t2519 = Str_lit("test", 4ULL);
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
                                                                                                                                                                                TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                ;
                                                                                                                                                                                return _t2519;
                                                                                                                                                                            } else {
                                                                                                                                                                                Bool _t2568; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwMacro()); _t2568 = *_hp; free(_hp); }
                                                                                                                                                                                (void)_t2568;
                                                                                                                                                                                if (_t2568) {
                                                                                                                                                                                    Str *_t2520 = Str_lit("macro", 5ULL);
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
                                                                                                                                                                                    TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                    ;
                                                                                                                                                                                    return _t2520;
                                                                                                                                                                                } else {
                                                                                                                                                                                    Bool _t2567; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwExtFunc()); _t2567 = *_hp; free(_hp); }
                                                                                                                                                                                    (void)_t2567;
                                                                                                                                                                                    if (_t2567) {
                                                                                                                                                                                        Str *_t2521 = Str_lit("ext_func", 8ULL);
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
                                                                                                                                                                                        TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                        ;
                                                                                                                                                                                        return _t2521;
                                                                                                                                                                                    } else {
                                                                                                                                                                                        Bool _t2566; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwExtProc()); _t2566 = *_hp; free(_hp); }
                                                                                                                                                                                        (void)_t2566;
                                                                                                                                                                                        if (_t2566) {
                                                                                                                                                                                            Str *_t2522 = Str_lit("ext_proc", 8ULL);
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
                                                                                                                                                                                            TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                            ;
                                                                                                                                                                                            return _t2522;
                                                                                                                                                                                        } else {
                                                                                                                                                                                            Bool _t2565; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwReturns()); _t2565 = *_hp; free(_hp); }
                                                                                                                                                                                            (void)_t2565;
                                                                                                                                                                                            if (_t2565) {
                                                                                                                                                                                                Str *_t2523 = Str_lit("returns", 7ULL);
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
                                                                                                                                                                                                TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                                ;
                                                                                                                                                                                                return _t2523;
                                                                                                                                                                                            } else {
                                                                                                                                                                                                Bool _t2564; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwThrows()); _t2564 = *_hp; free(_hp); }
                                                                                                                                                                                                (void)_t2564;
                                                                                                                                                                                                if (_t2564) {
                                                                                                                                                                                                    Str *_t2524 = Str_lit("throws", 6ULL);
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
                                                                                                                                                                                                    TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    return _t2524;
                                                                                                                                                                                                } else {
                                                                                                                                                                                                    Bool _t2563; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwIf()); _t2563 = *_hp; free(_hp); }
                                                                                                                                                                                                    (void)_t2563;
                                                                                                                                                                                                    if (_t2563) {
                                                                                                                                                                                                        Str *_t2525 = Str_lit("if", 2ULL);
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
                                                                                                                                                                                                        TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        return _t2525;
                                                                                                                                                                                                    } else {
                                                                                                                                                                                                        Bool _t2562; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwElse()); _t2562 = *_hp; free(_hp); }
                                                                                                                                                                                                        (void)_t2562;
                                                                                                                                                                                                        if (_t2562) {
                                                                                                                                                                                                            Str *_t2526 = Str_lit("else", 4ULL);
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
                                                                                                                                                                                                            TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            return _t2526;
                                                                                                                                                                                                        } else {
                                                                                                                                                                                                            Bool _t2561; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwWhile()); _t2561 = *_hp; free(_hp); }
                                                                                                                                                                                                            (void)_t2561;
                                                                                                                                                                                                            if (_t2561) {
                                                                                                                                                                                                                Str *_t2527 = Str_lit("while", 5ULL);
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
                                                                                                                                                                                                                TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                return _t2527;
                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                Bool _t2560; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwFor()); _t2560 = *_hp; free(_hp); }
                                                                                                                                                                                                                (void)_t2560;
                                                                                                                                                                                                                if (_t2560) {
                                                                                                                                                                                                                    Str *_t2528 = Str_lit("for", 3ULL);
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
                                                                                                                                                                                                                    TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    return _t2528;
                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                    Bool _t2559; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwIn()); _t2559 = *_hp; free(_hp); }
                                                                                                                                                                                                                    (void)_t2559;
                                                                                                                                                                                                                    if (_t2559) {
                                                                                                                                                                                                                        Str *_t2529 = Str_lit("in", 2ULL);
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
                                                                                                                                                                                                                        TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        return _t2529;
                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                        Bool _t2558; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwSwitch()); _t2558 = *_hp; free(_hp); }
                                                                                                                                                                                                                        (void)_t2558;
                                                                                                                                                                                                                        if (_t2558) {
                                                                                                                                                                                                                            Str *_t2530 = Str_lit("switch", 6ULL);
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
                                                                                                                                                                                                                            TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            return _t2530;
                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                            Bool _t2557; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwMatch()); _t2557 = *_hp; free(_hp); }
                                                                                                                                                                                                                            (void)_t2557;
                                                                                                                                                                                                                            if (_t2557) {
                                                                                                                                                                                                                                Str *_t2531 = Str_lit("match", 5ULL);
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
                                                                                                                                                                                                                                TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                return _t2531;
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                Bool _t2556; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwCase()); _t2556 = *_hp; free(_hp); }
                                                                                                                                                                                                                                (void)_t2556;
                                                                                                                                                                                                                                if (_t2556) {
                                                                                                                                                                                                                                    Str *_t2532 = Str_lit("case", 4ULL);
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
                                                                                                                                                                                                                                    TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    return _t2532;
                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                    Bool _t2555; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwDefault()); _t2555 = *_hp; free(_hp); }
                                                                                                                                                                                                                                    (void)_t2555;
                                                                                                                                                                                                                                    if (_t2555) {
                                                                                                                                                                                                                                        Str *_t2533 = Str_lit("default", 7ULL);
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
                                                                                                                                                                                                                                        TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        return _t2533;
                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                        Bool _t2554; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwReturn()); _t2554 = *_hp; free(_hp); }
                                                                                                                                                                                                                                        (void)_t2554;
                                                                                                                                                                                                                                        if (_t2554) {
                                                                                                                                                                                                                                            Str *_t2534 = Str_lit("return", 6ULL);
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
                                                                                                                                                                                                                                            TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            return _t2534;
                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                            Bool _t2553; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwThrow()); _t2553 = *_hp; free(_hp); }
                                                                                                                                                                                                                                            (void)_t2553;
                                                                                                                                                                                                                                            if (_t2553) {
                                                                                                                                                                                                                                                Str *_t2535 = Str_lit("throw", 5ULL);
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
                                                                                                                                                                                                                                                TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                return _t2535;
                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                Bool _t2552; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwCatch()); _t2552 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                (void)_t2552;
                                                                                                                                                                                                                                                if (_t2552) {
                                                                                                                                                                                                                                                    Str *_t2536 = Str_lit("catch", 5ULL);
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
                                                                                                                                                                                                                                                    TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    return _t2536;
                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                    Bool _t2551; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwBreak()); _t2551 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                    (void)_t2551;
                                                                                                                                                                                                                                                    if (_t2551) {
                                                                                                                                                                                                                                                        Str *_t2537 = Str_lit("break", 5ULL);
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
                                                                                                                                                                                                                                                        TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        return _t2537;
                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                        Bool _t2550; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwContinue()); _t2550 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                        (void)_t2550;
                                                                                                                                                                                                                                                        if (_t2550) {
                                                                                                                                                                                                                                                            Str *_t2538 = Str_lit("continue", 8ULL);
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
                                                                                                                                                                                                                                                            TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            return _t2538;
                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                            Bool _t2549; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwDefer()); _t2549 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                            (void)_t2549;
                                                                                                                                                                                                                                                            if (_t2549) {
                                                                                                                                                                                                                                                                Str *_t2539 = Str_lit("defer", 5ULL);
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
                                                                                                                                                                                                                                                                TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                return _t2539;
                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                Bool _t2548; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwTrue()); _t2548 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                (void)_t2548;
                                                                                                                                                                                                                                                                if (_t2548) {
                                                                                                                                                                                                                                                                    Str *_t2540 = Str_lit("true", 4ULL);
                                                                                                                                                                                                                                                                    (void)_t2540;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t2540;
                                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                                    Bool _t2547; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwFalse()); _t2547 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                    (void)_t2547;
                                                                                                                                                                                                                                                                    if (_t2547) {
                                                                                                                                                                                                                                                                        Str *_t2541 = Str_lit("false", 5ULL);
                                                                                                                                                                                                                                                                        (void)_t2541;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        return _t2541;
                                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                                        Bool _t2546; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_KwNull()); _t2546 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                        (void)_t2546;
                                                                                                                                                                                                                                                                        if (_t2546) {
                                                                                                                                                                                                                                                                            Str *_t2542 = Str_lit("NULL", 4ULL);
                                                                                                                                                                                                                                                                            (void)_t2542;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            return _t2542;
                                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                                            Bool _t2545; { Bool *_hp = (Bool *)TokenType_eq(_sw2477, TokenType_Error()); _t2545 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                            (void)_t2545;
                                                                                                                                                                                                                                                                            if (_t2545) {
                                                                                                                                                                                                                                                                                Str *_t2543 = Str_lit("error", 5ULL);
                                                                                                                                                                                                                                                                                (void)_t2543;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t2543;
                                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                                Str *_t2544 = Str_lit("?", 1ULL);
                                                                                                                                                                                                                                                                                (void)_t2544;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                TokenType_delete(_sw2477, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t2544;
                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                        }
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                    }
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                }
                                                                                                                                                                                                                ;
                                                                                                                                                                                                            }
                                                                                                                                                                                                            ;
                                                                                                                                                                                                        }
                                                                                                                                                                                                        ;
                                                                                                                                                                                                    }
                                                                                                                                                                                                    ;
                                                                                                                                                                                                }
                                                                                                                                                                                                ;
                                                                                                                                                                                            }
                                                                                                                                                                                            ;
                                                                                                                                                                                        }
                                                                                                                                                                                        ;
                                                                                                                                                                                    }
                                                                                                                                                                                    ;
                                                                                                                                                                                }
                                                                                                                                                                                ;
                                                                                                                                                                            }
                                                                                                                                                                            ;
                                                                                                                                                                        }
                                                                                                                                                                        ;
                                                                                                                                                                    }
                                                                                                                                                                    ;
                                                                                                                                                                }
                                                                                                                                                                ;
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                        ;
                                                                                                                                                    }
                                                                                                                                                    ;
                                                                                                                                                }
                                                                                                                                                ;
                                                                                                                                            }
                                                                                                                                            ;
                                                                                                                                        }
                                                                                                                                        ;
                                                                                                                                    }
                                                                                                                                    ;
                                                                                                                                }
                                                                                                                                ;
                                                                                                                            }
                                                                                                                            ;
                                                                                                                        }
                                                                                                                        ;
                                                                                                                    }
                                                                                                                    ;
                                                                                                                }
                                                                                                                ;
                                                                                                            }
                                                                                                            ;
                                                                                                        }
                                                                                                        ;
                                                                                                    }
                                                                                                    ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                            ;
                                                                                        }
                                                                                        ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                                ;
                                                                            }
                                                                            ;
                                                                        }
                                                                        ;
                                                                    }
                                                                    ;
                                                                }
                                                                ;
                                                            }
                                                            ;
                                                        }
                                                        ;
                                                    }
                                                    ;
                                                }
                                                ;
                                            }
                                            ;
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        TokenType_delete(_sw2477, &(Bool){1});
        ;
    }
}

TokenType * lookup_keyword(Str * word) {
    (void)word;
    {
        Str *_sw2611 = Str_clone(word);
        (void)_sw2611;
        Str *_t2680 = Str_lit("mode", 4ULL);
        (void)_t2680;
        Bool _t2681; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2680); _t2681 = *_hp; free(_hp); }
        (void)_t2681;
        Str_delete(_t2680, &(Bool){1});
        if (_t2681) {
            Str_delete(_sw2611, &(Bool){1});
            ;
            return TokenType_KwMode();
        } else {
            Str *_t2678 = Str_lit("mut", 3ULL);
            (void)_t2678;
            Bool _t2679; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2678); _t2679 = *_hp; free(_hp); }
            (void)_t2679;
            Str_delete(_t2678, &(Bool){1});
            if (_t2679) {
                ;
                Str_delete(_sw2611, &(Bool){1});
                ;
                return TokenType_KwMut();
            } else {
                Str *_t2676 = Str_lit("own", 3ULL);
                (void)_t2676;
                Bool _t2677; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2676); _t2677 = *_hp; free(_hp); }
                (void)_t2677;
                Str_delete(_t2676, &(Bool){1});
                if (_t2677) {
                    ;
                    ;
                    Str_delete(_sw2611, &(Bool){1});
                    ;
                    return TokenType_KwOwn();
                } else {
                    Str *_t2674 = Str_lit("ref", 3ULL);
                    (void)_t2674;
                    Bool _t2675; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2674); _t2675 = *_hp; free(_hp); }
                    (void)_t2675;
                    Str_delete(_t2674, &(Bool){1});
                    if (_t2675) {
                        ;
                        ;
                        ;
                        Str_delete(_sw2611, &(Bool){1});
                        ;
                        return TokenType_KwRef();
                    } else {
                        Str *_t2672 = Str_lit("shallow", 7ULL);
                        (void)_t2672;
                        Bool _t2673; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2672); _t2673 = *_hp; free(_hp); }
                        (void)_t2673;
                        Str_delete(_t2672, &(Bool){1});
                        if (_t2673) {
                            ;
                            ;
                            ;
                            ;
                            Str_delete(_sw2611, &(Bool){1});
                            ;
                            return TokenType_KwShallow();
                        } else {
                            Str *_t2670 = Str_lit("struct", 6ULL);
                            (void)_t2670;
                            Bool _t2671; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2670); _t2671 = *_hp; free(_hp); }
                            (void)_t2671;
                            Str_delete(_t2670, &(Bool){1});
                            if (_t2671) {
                                ;
                                ;
                                ;
                                ;
                                ;
                                Str_delete(_sw2611, &(Bool){1});
                                ;
                                return TokenType_KwStruct();
                            } else {
                                Str *_t2668 = Str_lit("ext_struct", 10ULL);
                                (void)_t2668;
                                Bool _t2669; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2668); _t2669 = *_hp; free(_hp); }
                                (void)_t2669;
                                Str_delete(_t2668, &(Bool){1});
                                if (_t2669) {
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    Str_delete(_sw2611, &(Bool){1});
                                    ;
                                    return TokenType_KwExtStruct();
                                } else {
                                    Str *_t2666 = Str_lit("enum", 4ULL);
                                    (void)_t2666;
                                    Bool _t2667; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2666); _t2667 = *_hp; free(_hp); }
                                    (void)_t2667;
                                    Str_delete(_t2666, &(Bool){1});
                                    if (_t2667) {
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        Str_delete(_sw2611, &(Bool){1});
                                        ;
                                        return TokenType_KwEnum();
                                    } else {
                                        Str *_t2664 = Str_lit("namespace", 9ULL);
                                        (void)_t2664;
                                        Bool _t2665; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2664); _t2665 = *_hp; free(_hp); }
                                        (void)_t2665;
                                        Str_delete(_t2664, &(Bool){1});
                                        if (_t2665) {
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            Str_delete(_sw2611, &(Bool){1});
                                            ;
                                            return TokenType_KwNamespace();
                                        } else {
                                            Str *_t2662 = Str_lit("func", 4ULL);
                                            (void)_t2662;
                                            Bool _t2663; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2662); _t2663 = *_hp; free(_hp); }
                                            (void)_t2663;
                                            Str_delete(_t2662, &(Bool){1});
                                            if (_t2663) {
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                Str_delete(_sw2611, &(Bool){1});
                                                ;
                                                return TokenType_KwFunc();
                                            } else {
                                                Str *_t2660 = Str_lit("proc", 4ULL);
                                                (void)_t2660;
                                                Bool _t2661; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2660); _t2661 = *_hp; free(_hp); }
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
                                                    ;
                                                    ;
                                                    ;
                                                    Str_delete(_sw2611, &(Bool){1});
                                                    ;
                                                    return TokenType_KwProc();
                                                } else {
                                                    Str *_t2658 = Str_lit("test", 4ULL);
                                                    (void)_t2658;
                                                    Bool _t2659; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2658); _t2659 = *_hp; free(_hp); }
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
                                                        ;
                                                        ;
                                                        ;
                                                        Str_delete(_sw2611, &(Bool){1});
                                                        ;
                                                        return TokenType_KwTest();
                                                    } else {
                                                        Str *_t2656 = Str_lit("macro", 5ULL);
                                                        (void)_t2656;
                                                        Bool _t2657; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2656); _t2657 = *_hp; free(_hp); }
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
                                                            ;
                                                            ;
                                                            ;
                                                            Str_delete(_sw2611, &(Bool){1});
                                                            ;
                                                            return TokenType_KwMacro();
                                                        } else {
                                                            Str *_t2654 = Str_lit("ext_func", 8ULL);
                                                            (void)_t2654;
                                                            Bool _t2655; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2654); _t2655 = *_hp; free(_hp); }
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
                                                                ;
                                                                ;
                                                                ;
                                                                Str_delete(_sw2611, &(Bool){1});
                                                                ;
                                                                return TokenType_KwExtFunc();
                                                            } else {
                                                                Str *_t2652 = Str_lit("ext_proc", 8ULL);
                                                                (void)_t2652;
                                                                Bool _t2653; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2652); _t2653 = *_hp; free(_hp); }
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
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    Str_delete(_sw2611, &(Bool){1});
                                                                    ;
                                                                    return TokenType_KwExtProc();
                                                                } else {
                                                                    Str *_t2650 = Str_lit("returns", 7ULL);
                                                                    (void)_t2650;
                                                                    Bool _t2651; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2650); _t2651 = *_hp; free(_hp); }
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
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        Str_delete(_sw2611, &(Bool){1});
                                                                        ;
                                                                        return TokenType_KwReturns();
                                                                    } else {
                                                                        Str *_t2648 = Str_lit("throws", 6ULL);
                                                                        (void)_t2648;
                                                                        Bool _t2649; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2648); _t2649 = *_hp; free(_hp); }
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
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            Str_delete(_sw2611, &(Bool){1});
                                                                            ;
                                                                            return TokenType_KwThrows();
                                                                        } else {
                                                                            Str *_t2646 = Str_lit("if", 2ULL);
                                                                            (void)_t2646;
                                                                            Bool _t2647; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2646); _t2647 = *_hp; free(_hp); }
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
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                Str_delete(_sw2611, &(Bool){1});
                                                                                ;
                                                                                return TokenType_KwIf();
                                                                            } else {
                                                                                Str *_t2644 = Str_lit("else", 4ULL);
                                                                                (void)_t2644;
                                                                                Bool _t2645; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2644); _t2645 = *_hp; free(_hp); }
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
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    Str_delete(_sw2611, &(Bool){1});
                                                                                    ;
                                                                                    return TokenType_KwElse();
                                                                                } else {
                                                                                    Str *_t2642 = Str_lit("while", 5ULL);
                                                                                    (void)_t2642;
                                                                                    Bool _t2643; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2642); _t2643 = *_hp; free(_hp); }
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
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        Str_delete(_sw2611, &(Bool){1});
                                                                                        ;
                                                                                        return TokenType_KwWhile();
                                                                                    } else {
                                                                                        Str *_t2640 = Str_lit("for", 3ULL);
                                                                                        (void)_t2640;
                                                                                        Bool _t2641; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2640); _t2641 = *_hp; free(_hp); }
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
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            Str_delete(_sw2611, &(Bool){1});
                                                                                            ;
                                                                                            return TokenType_KwFor();
                                                                                        } else {
                                                                                            Str *_t2638 = Str_lit("in", 2ULL);
                                                                                            (void)_t2638;
                                                                                            Bool _t2639; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2638); _t2639 = *_hp; free(_hp); }
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
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                Str_delete(_sw2611, &(Bool){1});
                                                                                                ;
                                                                                                return TokenType_KwIn();
                                                                                            } else {
                                                                                                Str *_t2636 = Str_lit("switch", 6ULL);
                                                                                                (void)_t2636;
                                                                                                Bool _t2637; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2636); _t2637 = *_hp; free(_hp); }
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
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    Str_delete(_sw2611, &(Bool){1});
                                                                                                    ;
                                                                                                    return TokenType_KwSwitch();
                                                                                                } else {
                                                                                                    Str *_t2634 = Str_lit("match", 5ULL);
                                                                                                    (void)_t2634;
                                                                                                    Bool _t2635; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2634); _t2635 = *_hp; free(_hp); }
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
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        Str_delete(_sw2611, &(Bool){1});
                                                                                                        ;
                                                                                                        return TokenType_KwMatch();
                                                                                                    } else {
                                                                                                        Str *_t2632 = Str_lit("case", 4ULL);
                                                                                                        (void)_t2632;
                                                                                                        Bool _t2633; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2632); _t2633 = *_hp; free(_hp); }
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
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            Str_delete(_sw2611, &(Bool){1});
                                                                                                            ;
                                                                                                            return TokenType_KwCase();
                                                                                                        } else {
                                                                                                            Str *_t2630 = Str_lit("default", 7ULL);
                                                                                                            (void)_t2630;
                                                                                                            Bool _t2631; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2630); _t2631 = *_hp; free(_hp); }
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
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                Str_delete(_sw2611, &(Bool){1});
                                                                                                                ;
                                                                                                                return TokenType_KwDefault();
                                                                                                            } else {
                                                                                                                Str *_t2628 = Str_lit("return", 6ULL);
                                                                                                                (void)_t2628;
                                                                                                                Bool _t2629; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2628); _t2629 = *_hp; free(_hp); }
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
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    Str_delete(_sw2611, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return TokenType_KwReturn();
                                                                                                                } else {
                                                                                                                    Str *_t2626 = Str_lit("throw", 5ULL);
                                                                                                                    (void)_t2626;
                                                                                                                    Bool _t2627; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2626); _t2627 = *_hp; free(_hp); }
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
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        Str_delete(_sw2611, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return TokenType_KwThrow();
                                                                                                                    } else {
                                                                                                                        Str *_t2624 = Str_lit("catch", 5ULL);
                                                                                                                        (void)_t2624;
                                                                                                                        Bool _t2625; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2624); _t2625 = *_hp; free(_hp); }
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
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            Str_delete(_sw2611, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return TokenType_KwCatch();
                                                                                                                        } else {
                                                                                                                            Str *_t2622 = Str_lit("break", 5ULL);
                                                                                                                            (void)_t2622;
                                                                                                                            Bool _t2623; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2622); _t2623 = *_hp; free(_hp); }
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
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                Str_delete(_sw2611, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return TokenType_KwBreak();
                                                                                                                            } else {
                                                                                                                                Str *_t2620 = Str_lit("continue", 8ULL);
                                                                                                                                (void)_t2620;
                                                                                                                                Bool _t2621; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2620); _t2621 = *_hp; free(_hp); }
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
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    Str_delete(_sw2611, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return TokenType_KwContinue();
                                                                                                                                } else {
                                                                                                                                    Str *_t2618 = Str_lit("defer", 5ULL);
                                                                                                                                    (void)_t2618;
                                                                                                                                    Bool _t2619; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2618); _t2619 = *_hp; free(_hp); }
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
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        Str_delete(_sw2611, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return TokenType_KwDefer();
                                                                                                                                    } else {
                                                                                                                                        Str *_t2616 = Str_lit("true", 4ULL);
                                                                                                                                        (void)_t2616;
                                                                                                                                        Bool _t2617; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2616); _t2617 = *_hp; free(_hp); }
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
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            Str_delete(_sw2611, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return TokenType_KwTrue();
                                                                                                                                        } else {
                                                                                                                                            Str *_t2614 = Str_lit("false", 5ULL);
                                                                                                                                            (void)_t2614;
                                                                                                                                            Bool _t2615; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2614); _t2615 = *_hp; free(_hp); }
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
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                Str_delete(_sw2611, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return TokenType_KwFalse();
                                                                                                                                            } else {
                                                                                                                                                Str *_t2612 = Str_lit("NULL", 4ULL);
                                                                                                                                                (void)_t2612;
                                                                                                                                                Bool _t2613; { Bool *_hp = (Bool *)Str_eq(_sw2611, _t2612); _t2613 = *_hp; free(_hp); }
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
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    Str_delete(_sw2611, &(Bool){1});
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
                                                                                                                                                    Str_delete(_sw2611, &(Bool){1});
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
        Str_delete(_sw2611, &(Bool){1});
        ;
    }
}

Vec * tokenize(Str * src, Str * path) {
    (void)src;
    (void)path;
    Str *_t3040 = Str_lit("Token", 5ULL);
    (void)_t3040;
    U64 _t3041; { U64 *_hp = (U64 *)Token_size(); _t3041 = *_hp; free(_hp); }
    (void)_t3041;
    Vec *tokens = Vec_new(_t3040, &(U64){_t3041});
    (void)tokens;
    Str_delete(_t3040, &(Bool){1});
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
        Bool _wcond2682; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2682 = *_hp; free(_hp); }
        (void)_wcond2682;
        if (_wcond2682) {
        } else {
            ;
            break;
        }
        ;
        U8 *c = Str_byte_at(src, pos);
        (void)c;
        U8 _t2984 = 32;
        (void)_t2984;
        U8 _t2985 = 9;
        (void)_t2985;
        Bool _t2986 = U8_eq(DEREF(c), _t2984);
        (void)_t2986;
        ;
        Bool _t2987 = U8_eq(DEREF(c), _t2985);
        (void)_t2987;
        ;
        U8 _t2988 = 13;
        (void)_t2988;
        Bool _t2989 = Bool_or(_t2986, _t2987);
        (void)_t2989;
        ;
        ;
        Bool _t2990 = U8_eq(DEREF(c), _t2988);
        (void)_t2990;
        ;
        U8 _t2991 = 59;
        (void)_t2991;
        Bool _t2992 = Bool_or(_t2989, _t2990);
        (void)_t2992;
        ;
        ;
        Bool _t2993 = U8_eq(DEREF(c), _t2991);
        (void)_t2993;
        ;
        Bool _t2994 = Bool_or(_t2992, _t2993);
        (void)_t2994;
        ;
        ;
        if (_t2994) {
            U64 _t2683 = U64_inc(DEREF(pos));
            (void)_t2683;
            *pos = _t2683;
            ;
            ;
            continue;
        }
        ;
        U8 _t2995 = 10;
        (void)_t2995;
        Bool _t2996 = U8_eq(DEREF(c), _t2995);
        (void)_t2996;
        ;
        if (_t2996) {
            U64 _t2684 = U64_inc(DEREF(pos));
            (void)_t2684;
            *pos = _t2684;
            ;
            U32 _t2685 = 1;
            (void)_t2685;
            U32 _t2686 = U32_add(line, _t2685);
            (void)_t2686;
            ;
            line = _t2686;
            ;
            U64 _t2687 = U64_clone(pos);
            (void)_t2687;
            line_start = _t2687;
            ;
            ;
            continue;
        }
        ;
        U64 _t2997 = U64_sub(DEREF(pos), line_start);
        (void)_t2997;
        U64 _t2998 = 1;
        (void)_t2998;
        U64 _t2999 = U64_add(_t2997, _t2998);
        (void)_t2999;
        ;
        ;
        I64 _t3000 = U64_to_i64(_t2999);
        (void)_t3000;
        ;
        U32 col = I64_to_u32(_t3000);
        (void)col;
        ;
        U64 start = U64_clone(pos);
        (void)start;
        U8 _t3001 = 35;
        (void)_t3001;
        Bool _t3002 = U8_eq(DEREF(c), _t3001);
        (void)_t3002;
        ;
        if (_t3002) {
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
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t3003 = 47;
        (void)_t3003;
        U64 _t3004 = 1;
        (void)_t3004;
        U64 _t3005 = U64_add(DEREF(pos), _t3004);
        (void)_t3005;
        ;
        Bool _t3006 = U8_eq(DEREF(c), _t3003);
        (void)_t3006;
        ;
        Bool _t3007; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3005}, &(U64){src_len}); _t3007 = *_hp; free(_hp); }
        (void)_t3007;
        ;
        Bool _t3008 = Bool_and(_t3006, _t3007);
        (void)_t3008;
        ;
        ;
        if (_t3008) {
            U64 _t2751 = 1;
            (void)_t2751;
            U64 *_t2752 = malloc(sizeof(U64)); *_t2752 = U64_add(DEREF(pos), _t2751);
            (void)_t2752;
            ;
            U8 *c2 = Str_byte_at(src, _t2752);
            (void)c2;
            U8 _t2753 = 47;
            (void)_t2753;
            Bool _t2754 = U8_eq(DEREF(c2), _t2753);
            (void)_t2754;
            ;
            if (_t2754) {
                while (1) {
                    Bool _wcond2693; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2693 = *_hp; free(_hp); }
                    (void)_wcond2693;
                    if (_wcond2693) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U8 *_t2694 = Str_byte_at(src, pos);
                    (void)_t2694;
                    U8 _t2695 = 10;
                    (void)_t2695;
                    Bool _t2696 = U8_eq(DEREF(_t2694), _t2695);
                    (void)_t2696;
                    ;
                    if (_t2696) {
                        ;
                        break;
                    }
                    ;
                    U64 _t2697 = U64_inc(DEREF(pos));
                    (void)_t2697;
                    *pos = _t2697;
                    ;
                }
                U64_delete(_t2752, &(Bool){1});
                ;
                ;
                ;
                ;
                continue;
            }
            ;
            U8 _t2755 = 42;
            (void)_t2755;
            Bool _t2756 = U8_eq(DEREF(c2), _t2755);
            (void)_t2756;
            U64_delete(_t2752, &(Bool){1});
            ;
            if (_t2756) {
                U64 _t2747 = 2;
                (void)_t2747;
                U64 _t2748 = U64_add(DEREF(pos), _t2747);
                (void)_t2748;
                ;
                *pos = _t2748;
                ;
                I64 depth = 1;
                (void)depth;
                while (1) {
                    Bool _wcond2698; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2698 = *_hp; free(_hp); }
                    (void)_wcond2698;
                    if (_wcond2698) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    I64 _t2723 = 0;
                    (void)_t2723;
                    Bool _t2724; { Bool *_hp = (Bool *)I64_lte(&(I64){depth}, &(I64){_t2723}); _t2724 = *_hp; free(_hp); }
                    (void)_t2724;
                    ;
                    if (_t2724) {
                        ;
                        break;
                    }
                    ;
                    U64 _t2725 = 1;
                    (void)_t2725;
                    U64 _t2726 = U64_add(DEREF(pos), _t2725);
                    (void)_t2726;
                    ;
                    Bool _t2727; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2726}, &(U64){src_len}); _t2727 = *_hp; free(_hp); }
                    (void)_t2727;
                    ;
                    if (_t2727) {
                        U8 *b1 = Str_byte_at(src, pos);
                        (void)b1;
                        U64 _t2707 = 1;
                        (void)_t2707;
                        U64 *_t2708 = malloc(sizeof(U64)); *_t2708 = U64_add(DEREF(pos), _t2707);
                        (void)_t2708;
                        ;
                        U8 *b2 = Str_byte_at(src, _t2708);
                        (void)b2;
                        U8 _t2709 = 47;
                        (void)_t2709;
                        U8 _t2710 = 42;
                        (void)_t2710;
                        Bool _t2711 = U8_eq(DEREF(b1), _t2709);
                        (void)_t2711;
                        ;
                        Bool _t2712 = U8_eq(DEREF(b2), _t2710);
                        (void)_t2712;
                        ;
                        Bool _t2713 = Bool_and(_t2711, _t2712);
                        (void)_t2713;
                        ;
                        ;
                        if (_t2713) {
                            I64 _t2699 = 1;
                            (void)_t2699;
                            I64 _t2700 = I64_add(depth, _t2699);
                            (void)_t2700;
                            ;
                            depth = _t2700;
                            ;
                            U64 _t2701 = 2;
                            (void)_t2701;
                            U64 _t2702 = U64_add(DEREF(pos), _t2701);
                            (void)_t2702;
                            ;
                            *pos = _t2702;
                            ;
                            U64_delete(_t2708, &(Bool){1});
                            ;
                            ;
                            continue;
                        }
                        ;
                        U8 _t2714 = 42;
                        (void)_t2714;
                        U8 _t2715 = 47;
                        (void)_t2715;
                        Bool _t2716 = U8_eq(DEREF(b1), _t2714);
                        (void)_t2716;
                        ;
                        Bool _t2717 = U8_eq(DEREF(b2), _t2715);
                        (void)_t2717;
                        U64_delete(_t2708, &(Bool){1});
                        ;
                        Bool _t2718 = Bool_and(_t2716, _t2717);
                        (void)_t2718;
                        ;
                        ;
                        if (_t2718) {
                            I64 _t2703 = 1;
                            (void)_t2703;
                            I64 _t2704 = I64_sub(depth, _t2703);
                            (void)_t2704;
                            ;
                            depth = _t2704;
                            ;
                            U64 _t2705 = 2;
                            (void)_t2705;
                            U64 _t2706 = U64_add(DEREF(pos), _t2705);
                            (void)_t2706;
                            ;
                            *pos = _t2706;
                            ;
                            ;
                            ;
                            continue;
                        }
                        ;
                    }
                    ;
                    U8 *_t2728 = Str_byte_at(src, pos);
                    (void)_t2728;
                    U8 _t2729 = 10;
                    (void)_t2729;
                    Bool _t2730 = U8_eq(DEREF(_t2728), _t2729);
                    (void)_t2730;
                    ;
                    if (_t2730) {
                        U32 _t2719 = 1;
                        (void)_t2719;
                        U32 _t2720 = U32_add(line, _t2719);
                        (void)_t2720;
                        ;
                        line = _t2720;
                        ;
                        U64 _t2721 = 1;
                        (void)_t2721;
                        U64 _t2722 = U64_add(DEREF(pos), _t2721);
                        (void)_t2722;
                        ;
                        line_start = _t2722;
                        ;
                    }
                    ;
                    U64 _t2731 = U64_inc(DEREF(pos));
                    (void)_t2731;
                    *pos = _t2731;
                    ;
                }
                I64 _t2749 = 0;
                (void)_t2749;
                Bool _t2750; { Bool *_hp = (Bool *)I64_gt(&(I64){depth}, &(I64){_t2749}); _t2750 = *_hp; free(_hp); }
                (void)_t2750;
                ;
                ;
                if (_t2750) {
                    Str *_t2732 = Str_lit("Str", 3ULL);
                    (void)_t2732;
                    U64 _t2733; { U64 *_hp = (U64 *)Str_size(); _t2733 = *_hp; free(_hp); }
                    (void)_t2733;
                    U64 _t2734 = 6;
                    (void)_t2734;
                    Array *_va50 = Array_new(_t2732, &(U64){_t2733}, &(U64){_t2734});
                    (void)_va50;
                    Str_delete(_t2732, &(Bool){1});
                    ;
                    ;
                    U64 _t2735 = 0;
                    (void)_t2735;
                    Str *_t2736 = Str_clone(path);
                    (void)_t2736;
                    Array_set(_va50, &(U64){_t2735}, _t2736);
                    ;
                    U64 _t2737 = 1;
                    (void)_t2737;
                    Str *_t2738 = Str_lit(":", 1ULL);
                    (void)_t2738;
                    Array_set(_va50, &(U64){_t2737}, _t2738);
                    ;
                    U64 _t2739 = 2;
                    (void)_t2739;
                    Str *_t2740 = U32_to_str(&(U32){line});
                    (void)_t2740;
                    Array_set(_va50, &(U64){_t2739}, _t2740);
                    ;
                    U64 _t2741 = 3;
                    (void)_t2741;
                    Str *_t2742 = Str_lit(":", 1ULL);
                    (void)_t2742;
                    Array_set(_va50, &(U64){_t2741}, _t2742);
                    ;
                    U64 _t2743 = 4;
                    (void)_t2743;
                    Str *_t2744 = U32_to_str(&(U32){col});
                    (void)_t2744;
                    Array_set(_va50, &(U64){_t2743}, _t2744);
                    ;
                    U64 _t2745 = 5;
                    (void)_t2745;
                    Str *_t2746 = Str_lit(": error: unterminated comment", 29ULL);
                    (void)_t2746;
                    Array_set(_va50, &(U64){_t2745}, _t2746);
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
        Bool _t3009; { Bool *_hp = (Bool *)is_digit(c); _t3009 = *_hp; free(_hp); }
        (void)_t3009;
        if (_t3009) {
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
            U64 _t2776 = 1;
            (void)_t2776;
            U64 _t2777 = U64_add(DEREF(pos), _t2776);
            (void)_t2777;
            ;
            Bool _t2778; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2777}, &(U64){src_len}); _t2778 = *_hp; free(_hp); }
            (void)_t2778;
            ;
            if (_t2778) {
                U8 *_t2768 = Str_byte_at(src, pos);
                (void)_t2768;
                U8 _t2769 = 46;
                (void)_t2769;
                U64 _t2770 = 1;
                (void)_t2770;
                U64 *_t2771 = malloc(sizeof(U64)); *_t2771 = U64_add(DEREF(pos), _t2770);
                (void)_t2771;
                ;
                U8 *_t2772 = Str_byte_at(src, _t2771);
                (void)_t2772;
                Bool _t2773 = U8_eq(DEREF(_t2768), _t2769);
                (void)_t2773;
                ;
                Bool _t2774; { Bool *_hp = (Bool *)is_digit(_t2772); _t2774 = *_hp; free(_hp); }
                (void)_t2774;
                U64_delete(_t2771, &(Bool){1});
                Bool _t2775 = Bool_and(_t2773, _t2774);
                (void)_t2775;
                ;
                ;
                if (_t2775) {
                    U64 _t2767 = U64_inc(DEREF(pos));
                    (void)_t2767;
                    *pos = _t2767;
                    ;
                    while (1) {
                        Bool _wcond2762; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2762 = *_hp; free(_hp); }
                        (void)_wcond2762;
                        if (_wcond2762) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U8 *_t2763 = Str_byte_at(src, pos);
                        (void)_t2763;
                        Bool _t2764; { Bool *_hp = (Bool *)is_digit(_t2763); _t2764 = *_hp; free(_hp); }
                        (void)_t2764;
                        Bool _t2765 = Bool_not(_t2764);
                        (void)_t2765;
                        ;
                        if (_t2765) {
                            ;
                            break;
                        }
                        ;
                        U64 _t2766 = U64_inc(DEREF(pos));
                        (void)_t2766;
                        *pos = _t2766;
                        ;
                    }
                }
                ;
            }
            ;
            U64 _t2779 = U64_sub(DEREF(pos), start);
            (void)_t2779;
            Str *_t2780 = Str_substr(src, &(U64){start}, &(U64){_t2779});
            (void)_t2780;
            ;
            U32 _t2781 = U32_clone(&(U32){col});
            (void)_t2781;
            Token *_t2782 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(TokenType_Number()); _t2782->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(_t2780); _t2782->text = *_ca; free(_ca); }
            _t2782->line = U32_clone(&(U32){line});
            _t2782->col = _t2781;
            (void)_t2782;
            Str_delete(_t2780, &(Bool){1});
            ;
            Vec_push(tokens, _t2782);
            ;
            ;
            ;
            continue;
        }
        ;
        Bool _t3010; { Bool *_hp = (Bool *)is_alpha(c); _t3010 = *_hp; free(_hp); }
        (void)_t3010;
        if (_t3010) {
            while (1) {
                Bool _wcond2783; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2783 = *_hp; free(_hp); }
                (void)_wcond2783;
                if (_wcond2783) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2784 = Str_byte_at(src, pos);
                (void)_t2784;
                Bool _t2785; { Bool *_hp = (Bool *)is_alnum(_t2784); _t2785 = *_hp; free(_hp); }
                (void)_t2785;
                Bool _t2786 = Bool_not(_t2785);
                (void)_t2786;
                ;
                if (_t2786) {
                    ;
                    break;
                }
                ;
                U64 _t2787 = U64_inc(DEREF(pos));
                (void)_t2787;
                *pos = _t2787;
                ;
            }
            U64 _t2788 = U64_sub(DEREF(pos), start);
            (void)_t2788;
            Str *word = Str_substr(src, &(U64){start}, &(U64){_t2788});
            (void)word;
            ;
            TokenType *type = lookup_keyword(word);
            (void)type;
            U32 _t2789 = U32_clone(&(U32){line});
            (void)_t2789;
            U32 _t2790 = U32_clone(&(U32){col});
            (void)_t2790;
            Token *_t2791 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(type); _t2791->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(word); _t2791->text = *_ca; free(_ca); }
            _t2791->line = _t2789;
            _t2791->col = _t2790;
            (void)_t2791;
            ;
            ;
            TokenType_delete(type, &(Bool){1});
            Str_delete(word, &(Bool){1});
            Vec_push(tokens, _t2791);
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t3011 = 34;
        (void)_t3011;
        Bool _t3012 = U8_eq(DEREF(c), _t3011);
        (void)_t3012;
        ;
        if (_t3012) {
            U64 _t2840 = U64_inc(DEREF(pos));
            (void)_t2840;
            *pos = _t2840;
            ;
            while (1) {
                Bool _wcond2792; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2792 = *_hp; free(_hp); }
                (void)_wcond2792;
                if (_wcond2792) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2798 = Str_byte_at(src, pos);
                (void)_t2798;
                U8 _t2799 = 34;
                (void)_t2799;
                Bool _t2800 = U8_eq(DEREF(_t2798), _t2799);
                (void)_t2800;
                ;
                if (_t2800) {
                    ;
                    break;
                }
                ;
                U8 *_t2801 = Str_byte_at(src, pos);
                (void)_t2801;
                U8 _t2802 = 92;
                (void)_t2802;
                U64 _t2803 = 1;
                (void)_t2803;
                U64 _t2804 = U64_add(DEREF(pos), _t2803);
                (void)_t2804;
                ;
                Bool _t2805 = U8_eq(DEREF(_t2801), _t2802);
                (void)_t2805;
                ;
                Bool _t2806; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2804}, &(U64){src_len}); _t2806 = *_hp; free(_hp); }
                (void)_t2806;
                ;
                Bool _t2807 = Bool_and(_t2805, _t2806);
                (void)_t2807;
                ;
                ;
                if (_t2807) {
                    U64 _t2793 = U64_inc(DEREF(pos));
                    (void)_t2793;
                    *pos = _t2793;
                    ;
                }
                ;
                U8 *_t2808 = Str_byte_at(src, pos);
                (void)_t2808;
                U8 _t2809 = 10;
                (void)_t2809;
                Bool _t2810 = U8_eq(DEREF(_t2808), _t2809);
                (void)_t2810;
                ;
                if (_t2810) {
                    U32 _t2794 = 1;
                    (void)_t2794;
                    U32 _t2795 = U32_add(line, _t2794);
                    (void)_t2795;
                    ;
                    line = _t2795;
                    ;
                    U64 _t2796 = 1;
                    (void)_t2796;
                    U64 _t2797 = U64_add(DEREF(pos), _t2796);
                    (void)_t2797;
                    ;
                    line_start = _t2797;
                    ;
                }
                ;
                U64 _t2811 = U64_inc(DEREF(pos));
                (void)_t2811;
                *pos = _t2811;
                ;
            }
            U8 *_t2841 = Str_byte_at(src, pos);
            (void)_t2841;
            U8 _t2842 = 34;
            (void)_t2842;
            Bool _t2843; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2843 = *_hp; free(_hp); }
            (void)_t2843;
            Bool _t2844 = U8_eq(DEREF(_t2841), _t2842);
            (void)_t2844;
            ;
            Bool _t2845 = Bool_and(_t2843, _t2844);
            (void)_t2845;
            ;
            ;
            if (_t2845) {
                U64 _t2812 = U64_inc(DEREF(pos));
                (void)_t2812;
                *pos = _t2812;
                ;
                U64 _t2813 = 1;
                (void)_t2813;
                U64 _t2814 = U64_sub(DEREF(pos), start);
                (void)_t2814;
                U64 _t2815 = 2;
                (void)_t2815;
                U64 _t2816 = U64_add(start, _t2813);
                (void)_t2816;
                ;
                U64 _t2817 = U64_sub(_t2814, _t2815);
                (void)_t2817;
                ;
                ;
                Str *_t2818 = Str_substr(src, &(U64){_t2816}, &(U64){_t2817});
                (void)_t2818;
                ;
                ;
                U32 _t2819 = U32_clone(&(U32){col});
                (void)_t2819;
                Token *_t2820 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_StringTok()); _t2820->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2818); _t2820->text = *_ca; free(_ca); }
                _t2820->line = U32_clone(&(U32){line});
                _t2820->col = _t2819;
                (void)_t2820;
                Str_delete(_t2818, &(Bool){1});
                ;
                Vec_push(tokens, _t2820);
            } else {
                Str *_t2821 = Str_lit("Str", 3ULL);
                (void)_t2821;
                U64 _t2822; { U64 *_hp = (U64 *)Str_size(); _t2822 = *_hp; free(_hp); }
                (void)_t2822;
                U64 _t2823 = 6;
                (void)_t2823;
                Array *_va51 = Array_new(_t2821, &(U64){_t2822}, &(U64){_t2823});
                (void)_va51;
                Str_delete(_t2821, &(Bool){1});
                ;
                ;
                U64 _t2824 = 0;
                (void)_t2824;
                Str *_t2825 = Str_clone(path);
                (void)_t2825;
                Array_set(_va51, &(U64){_t2824}, _t2825);
                ;
                U64 _t2826 = 1;
                (void)_t2826;
                Str *_t2827 = Str_lit(":", 1ULL);
                (void)_t2827;
                Array_set(_va51, &(U64){_t2826}, _t2827);
                ;
                U64 _t2828 = 2;
                (void)_t2828;
                Str *_t2829 = U32_to_str(&(U32){line});
                (void)_t2829;
                Array_set(_va51, &(U64){_t2828}, _t2829);
                ;
                U64 _t2830 = 3;
                (void)_t2830;
                Str *_t2831 = Str_lit(":", 1ULL);
                (void)_t2831;
                Array_set(_va51, &(U64){_t2830}, _t2831);
                ;
                U64 _t2832 = 4;
                (void)_t2832;
                Str *_t2833 = U32_to_str(&(U32){col});
                (void)_t2833;
                Array_set(_va51, &(U64){_t2832}, _t2833);
                ;
                U64 _t2834 = 5;
                (void)_t2834;
                Str *_t2835 = Str_lit(": error: unterminated string", 28ULL);
                (void)_t2835;
                Array_set(_va51, &(U64){_t2834}, _t2835);
                ;
                println(_va51);
                U64 _t2836 = U64_sub(DEREF(pos), start);
                (void)_t2836;
                Str *_t2837 = Str_substr(src, &(U64){start}, &(U64){_t2836});
                (void)_t2837;
                ;
                U32 _t2838 = U32_clone(&(U32){col});
                (void)_t2838;
                Token *_t2839 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2839->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2837); _t2839->text = *_ca; free(_ca); }
                _t2839->line = U32_clone(&(U32){line});
                _t2839->col = _t2838;
                (void)_t2839;
                Str_delete(_t2837, &(Bool){1});
                ;
                Vec_push(tokens, _t2839);
            }
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t3013 = 39;
        (void)_t3013;
        Bool _t3014 = U8_eq(DEREF(c), _t3013);
        (void)_t3014;
        ;
        if (_t3014) {
            U64 _t2871 = U64_inc(DEREF(pos));
            (void)_t2871;
            *pos = _t2871;
            ;
            U64 ch_start = U64_clone(pos);
            (void)ch_start;
            U8 *_t2872 = Str_byte_at(src, pos);
            (void)_t2872;
            U8 _t2873 = 92;
            (void)_t2873;
            U64 _t2874 = 1;
            (void)_t2874;
            U64 _t2875 = U64_add(DEREF(pos), _t2874);
            (void)_t2875;
            ;
            Bool _t2876 = U8_eq(DEREF(_t2872), _t2873);
            (void)_t2876;
            ;
            Bool _t2877; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2875}, &(U64){src_len}); _t2877 = *_hp; free(_hp); }
            (void)_t2877;
            ;
            Bool _t2878; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2878 = *_hp; free(_hp); }
            (void)_t2878;
            Bool _t2879 = Bool_and(_t2876, _t2877);
            (void)_t2879;
            ;
            ;
            Bool _t2880 = Bool_and(_t2878, _t2879);
            (void)_t2880;
            ;
            ;
            if (_t2880) {
                U64 _t2846 = U64_inc(DEREF(pos));
                (void)_t2846;
                *pos = _t2846;
                ;
            }
            ;
            U64 _t2881 = U64_inc(DEREF(pos));
            (void)_t2881;
            *pos = _t2881;
            ;
            U8 *_t2882 = Str_byte_at(src, pos);
            (void)_t2882;
            U8 _t2883 = 39;
            (void)_t2883;
            Bool _t2884; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2884 = *_hp; free(_hp); }
            (void)_t2884;
            Bool _t2885 = U8_eq(DEREF(_t2882), _t2883);
            (void)_t2885;
            ;
            Bool _t2886 = Bool_and(_t2884, _t2885);
            (void)_t2886;
            ;
            ;
            if (_t2886) {
                U64 _t2847 = U64_sub(DEREF(pos), ch_start);
                (void)_t2847;
                Str *_t2848 = Str_substr(src, &(U64){ch_start}, &(U64){_t2847});
                (void)_t2848;
                ;
                U32 _t2849 = U32_clone(&(U32){col});
                (void)_t2849;
                Token *_t2850 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Char()); _t2850->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2848); _t2850->text = *_ca; free(_ca); }
                _t2850->line = U32_clone(&(U32){line});
                _t2850->col = _t2849;
                (void)_t2850;
                Str_delete(_t2848, &(Bool){1});
                ;
                Vec_push(tokens, _t2850);
                U64 _t2851 = U64_inc(DEREF(pos));
                (void)_t2851;
                *pos = _t2851;
                ;
            } else {
                Str *_t2852 = Str_lit("Str", 3ULL);
                (void)_t2852;
                U64 _t2853; { U64 *_hp = (U64 *)Str_size(); _t2853 = *_hp; free(_hp); }
                (void)_t2853;
                U64 _t2854 = 6;
                (void)_t2854;
                Array *_va52 = Array_new(_t2852, &(U64){_t2853}, &(U64){_t2854});
                (void)_va52;
                Str_delete(_t2852, &(Bool){1});
                ;
                ;
                U64 _t2855 = 0;
                (void)_t2855;
                Str *_t2856 = Str_clone(path);
                (void)_t2856;
                Array_set(_va52, &(U64){_t2855}, _t2856);
                ;
                U64 _t2857 = 1;
                (void)_t2857;
                Str *_t2858 = Str_lit(":", 1ULL);
                (void)_t2858;
                Array_set(_va52, &(U64){_t2857}, _t2858);
                ;
                U64 _t2859 = 2;
                (void)_t2859;
                Str *_t2860 = U32_to_str(&(U32){line});
                (void)_t2860;
                Array_set(_va52, &(U64){_t2859}, _t2860);
                ;
                U64 _t2861 = 3;
                (void)_t2861;
                Str *_t2862 = Str_lit(":", 1ULL);
                (void)_t2862;
                Array_set(_va52, &(U64){_t2861}, _t2862);
                ;
                U64 _t2863 = 4;
                (void)_t2863;
                Str *_t2864 = U32_to_str(&(U32){col});
                (void)_t2864;
                Array_set(_va52, &(U64){_t2863}, _t2864);
                ;
                U64 _t2865 = 5;
                (void)_t2865;
                Str *_t2866 = Str_lit(": error: unterminated character literal", 39ULL);
                (void)_t2866;
                Array_set(_va52, &(U64){_t2865}, _t2866);
                ;
                println(_va52);
                U64 _t2867 = U64_sub(DEREF(pos), start);
                (void)_t2867;
                Str *_t2868 = Str_substr(src, &(U64){start}, &(U64){_t2867});
                (void)_t2868;
                ;
                U32 _t2869 = U32_clone(&(U32){col});
                (void)_t2869;
                Token *_t2870 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2870->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2868); _t2870->text = *_ca; free(_ca); }
                _t2870->line = U32_clone(&(U32){line});
                _t2870->col = _t2869;
                (void)_t2870;
                Str_delete(_t2868, &(Bool){1});
                ;
                Vec_push(tokens, _t2870);
            }
            ;
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U64 _t3015 = 1;
        (void)_t3015;
        U64 _t3016 = U64_add(DEREF(pos), _t3015);
        (void)_t3016;
        ;
        Bool _t3017; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3016}, &(U64){src_len}); _t3017 = *_hp; free(_hp); }
        (void)_t3017;
        ;
        if (_t3017) {
            U64 _t2932 = 1;
            (void)_t2932;
            U64 *_t2933 = malloc(sizeof(U64)); *_t2933 = U64_add(DEREF(pos), _t2932);
            (void)_t2933;
            ;
            U8 *c2 = Str_byte_at(src, _t2933);
            (void)c2;
            TokenType *two = TokenType_clone(TokenType_Eof());
            (void)two;
            U8 _t2934 = 58;
            (void)_t2934;
            U8 _t2935 = 61;
            (void)_t2935;
            Bool _t2936 = U8_eq(DEREF(c), _t2934);
            (void)_t2936;
            ;
            Bool _t2937 = U8_eq(DEREF(c2), _t2935);
            (void)_t2937;
            ;
            Bool _t2938 = Bool_and(_t2936, _t2937);
            (void)_t2938;
            ;
            ;
            if (_t2938) {
                two = TokenType_clone(TokenType_ColonEq());
            } else {
                U8 _t2920 = 61;
                (void)_t2920;
                U8 _t2921 = 61;
                (void)_t2921;
                Bool _t2922 = U8_eq(DEREF(c), _t2920);
                (void)_t2922;
                ;
                Bool _t2923 = U8_eq(DEREF(c2), _t2921);
                (void)_t2923;
                ;
                Bool _t2924 = Bool_and(_t2922, _t2923);
                (void)_t2924;
                ;
                ;
                if (_t2924) {
                    two = TokenType_clone(TokenType_EqEq());
                } else {
                    U8 _t2915 = 33;
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
                        two = TokenType_clone(TokenType_Neq());
                    } else {
                        U8 _t2910 = 60;
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
                            two = TokenType_clone(TokenType_LtEq());
                        } else {
                            U8 _t2905 = 62;
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
                                two = TokenType_clone(TokenType_GtEq());
                            } else {
                                U8 _t2900 = 46;
                                (void)_t2900;
                                U8 _t2901 = 46;
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
                                    U64 _t2897 = 2;
                                    (void)_t2897;
                                    U64 _t2898 = U64_add(DEREF(pos), _t2897);
                                    (void)_t2898;
                                    ;
                                    Bool _t2899; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2898}, &(U64){src_len}); _t2899 = *_hp; free(_hp); }
                                    (void)_t2899;
                                    ;
                                    if (_t2899) {
                                        U64 _t2893 = 2;
                                        (void)_t2893;
                                        U64 *_t2894 = malloc(sizeof(U64)); *_t2894 = U64_add(DEREF(pos), _t2893);
                                        (void)_t2894;
                                        ;
                                        U8 *c3 = Str_byte_at(src, _t2894);
                                        (void)c3;
                                        U8 _t2895 = 46;
                                        (void)_t2895;
                                        Bool _t2896 = U8_eq(DEREF(c3), _t2895);
                                        (void)_t2896;
                                        U64_delete(_t2894, &(Bool){1});
                                        ;
                                        if (_t2896) {
                                            U64 _t2887 = 3;
                                            (void)_t2887;
                                            Str *_t2888 = Str_substr(src, &(U64){start}, &(U64){_t2887});
                                            (void)_t2888;
                                            ;
                                            U32 _t2889 = U32_clone(&(U32){col});
                                            (void)_t2889;
                                            Token *_t2890 = malloc(sizeof(Token));
                                            { TokenType *_ca = TokenType_clone(TokenType_DotDotDot()); _t2890->type = *_ca; free(_ca); }
                                            { Str *_ca = Str_clone(_t2888); _t2890->text = *_ca; free(_ca); }
                                            _t2890->line = U32_clone(&(U32){line});
                                            _t2890->col = _t2889;
                                            (void)_t2890;
                                            Str_delete(_t2888, &(Bool){1});
                                            ;
                                            Vec_push(tokens, _t2890);
                                            U64 _t2891 = 3;
                                            (void)_t2891;
                                            U64 _t2892 = U64_add(DEREF(pos), _t2891);
                                            (void)_t2892;
                                            ;
                                            *pos = _t2892;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            U64_delete(_t2933, &(Bool){1});
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
            U64_delete(_t2933, &(Bool){1});
            ;
            Bool _t2939; { Bool *_hp = (Bool *)TokenType_eq(two, TokenType_Eof()); _t2939 = *_hp; free(_hp); }
            (void)_t2939;
            Bool _t2940 = Bool_not(_t2939);
            (void)_t2940;
            ;
            if (_t2940) {
                U64 _t2925 = 2;
                (void)_t2925;
                Str *_t2926 = Str_substr(src, &(U64){start}, &(U64){_t2925});
                (void)_t2926;
                ;
                U32 _t2927 = U32_clone(&(U32){line});
                (void)_t2927;
                U32 _t2928 = U32_clone(&(U32){col});
                (void)_t2928;
                Token *_t2929 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(two); _t2929->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2926); _t2929->text = *_ca; free(_ca); }
                _t2929->line = _t2927;
                _t2929->col = _t2928;
                (void)_t2929;
                Str_delete(_t2926, &(Bool){1});
                ;
                ;
                Vec_push(tokens, _t2929);
                U64 _t2930 = 2;
                (void)_t2930;
                U64 _t2931 = U64_add(DEREF(pos), _t2930);
                (void)_t2931;
                ;
                *pos = _t2931;
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
            U8 _sw2941 = U8_clone(c);
            (void)_sw2941;
            U8 _t2976 = 40;
            (void)_t2976;
            Bool _t2977 = U8_eq(_sw2941, _t2976);
            (void)_t2977;
            ;
            if (_t2977) {
                single = TokenType_clone(TokenType_LParen());
            } else {
                U8 _t2974 = 41;
                (void)_t2974;
                Bool _t2975 = U8_eq(_sw2941, _t2974);
                (void)_t2975;
                ;
                if (_t2975) {
                    single = TokenType_clone(TokenType_RParen());
                } else {
                    U8 _t2972 = 123;
                    (void)_t2972;
                    Bool _t2973 = U8_eq(_sw2941, _t2972);
                    (void)_t2973;
                    ;
                    if (_t2973) {
                        single = TokenType_clone(TokenType_LBrace());
                    } else {
                        U8 _t2970 = 125;
                        (void)_t2970;
                        Bool _t2971 = U8_eq(_sw2941, _t2970);
                        (void)_t2971;
                        ;
                        if (_t2971) {
                            single = TokenType_clone(TokenType_RBrace());
                        } else {
                            U8 _t2968 = 91;
                            (void)_t2968;
                            Bool _t2969 = U8_eq(_sw2941, _t2968);
                            (void)_t2969;
                            ;
                            if (_t2969) {
                                single = TokenType_clone(TokenType_LBracket());
                            } else {
                                U8 _t2966 = 93;
                                (void)_t2966;
                                Bool _t2967 = U8_eq(_sw2941, _t2966);
                                (void)_t2967;
                                ;
                                if (_t2967) {
                                    single = TokenType_clone(TokenType_RBracket());
                                } else {
                                    U8 _t2964 = 44;
                                    (void)_t2964;
                                    Bool _t2965 = U8_eq(_sw2941, _t2964);
                                    (void)_t2965;
                                    ;
                                    if (_t2965) {
                                        single = TokenType_clone(TokenType_Comma());
                                    } else {
                                        U8 _t2962 = 58;
                                        (void)_t2962;
                                        Bool _t2963 = U8_eq(_sw2941, _t2962);
                                        (void)_t2963;
                                        ;
                                        if (_t2963) {
                                            single = TokenType_clone(TokenType_Colon());
                                        } else {
                                            U8 _t2960 = 46;
                                            (void)_t2960;
                                            Bool _t2961 = U8_eq(_sw2941, _t2960);
                                            (void)_t2961;
                                            ;
                                            if (_t2961) {
                                                single = TokenType_clone(TokenType_Dot());
                                            } else {
                                                U8 _t2958 = 63;
                                                (void)_t2958;
                                                Bool _t2959 = U8_eq(_sw2941, _t2958);
                                                (void)_t2959;
                                                ;
                                                if (_t2959) {
                                                    single = TokenType_clone(TokenType_Question());
                                                } else {
                                                    U8 _t2956 = 33;
                                                    (void)_t2956;
                                                    Bool _t2957 = U8_eq(_sw2941, _t2956);
                                                    (void)_t2957;
                                                    ;
                                                    if (_t2957) {
                                                        single = TokenType_clone(TokenType_Bang());
                                                    } else {
                                                        U8 _t2954 = 43;
                                                        (void)_t2954;
                                                        Bool _t2955 = U8_eq(_sw2941, _t2954);
                                                        (void)_t2955;
                                                        ;
                                                        if (_t2955) {
                                                            single = TokenType_clone(TokenType_Plus());
                                                        } else {
                                                            U8 _t2952 = 45;
                                                            (void)_t2952;
                                                            Bool _t2953 = U8_eq(_sw2941, _t2952);
                                                            (void)_t2953;
                                                            ;
                                                            if (_t2953) {
                                                                single = TokenType_clone(TokenType_Minus());
                                                            } else {
                                                                U8 _t2950 = 42;
                                                                (void)_t2950;
                                                                Bool _t2951 = U8_eq(_sw2941, _t2950);
                                                                (void)_t2951;
                                                                ;
                                                                if (_t2951) {
                                                                    single = TokenType_clone(TokenType_Star());
                                                                } else {
                                                                    U8 _t2948 = 47;
                                                                    (void)_t2948;
                                                                    Bool _t2949 = U8_eq(_sw2941, _t2948);
                                                                    (void)_t2949;
                                                                    ;
                                                                    if (_t2949) {
                                                                        single = TokenType_clone(TokenType_Slash());
                                                                    } else {
                                                                        U8 _t2946 = 61;
                                                                        (void)_t2946;
                                                                        Bool _t2947 = U8_eq(_sw2941, _t2946);
                                                                        (void)_t2947;
                                                                        ;
                                                                        if (_t2947) {
                                                                            single = TokenType_clone(TokenType_Eq());
                                                                        } else {
                                                                            U8 _t2944 = 60;
                                                                            (void)_t2944;
                                                                            Bool _t2945 = U8_eq(_sw2941, _t2944);
                                                                            (void)_t2945;
                                                                            ;
                                                                            if (_t2945) {
                                                                                single = TokenType_clone(TokenType_Lt());
                                                                            } else {
                                                                                U8 _t2942 = 62;
                                                                                (void)_t2942;
                                                                                Bool _t2943 = U8_eq(_sw2941, _t2942);
                                                                                (void)_t2943;
                                                                                ;
                                                                                if (_t2943) {
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
        Bool _t3018; { Bool *_hp = (Bool *)TokenType_eq(single, TokenType_Eof()); _t3018 = *_hp; free(_hp); }
        (void)_t3018;
        Bool _t3019 = Bool_not(_t3018);
        (void)_t3019;
        ;
        if (_t3019) {
            U64 _t2978 = 1;
            (void)_t2978;
            Str *_t2979 = Str_substr(src, &(U64){start}, &(U64){_t2978});
            (void)_t2979;
            ;
            U32 _t2980 = U32_clone(&(U32){line});
            (void)_t2980;
            U32 _t2981 = U32_clone(&(U32){col});
            (void)_t2981;
            Token *_t2982 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(single); _t2982->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(_t2979); _t2982->text = *_ca; free(_ca); }
            _t2982->line = _t2980;
            _t2982->col = _t2981;
            (void)_t2982;
            Str_delete(_t2979, &(Bool){1});
            ;
            ;
            Vec_push(tokens, _t2982);
            U64 _t2983 = U64_inc(DEREF(pos));
            (void)_t2983;
            *pos = _t2983;
            ;
            ;
            ;
            TokenType_delete(single, &(Bool){1});
            ;
            continue;
        }
        ;
        TokenType_delete(single, &(Bool){1});
        Str *_t3020 = Str_lit("Str", 3ULL);
        (void)_t3020;
        U64 _t3021; { U64 *_hp = (U64 *)Str_size(); _t3021 = *_hp; free(_hp); }
        (void)_t3021;
        U64 _t3022 = 6;
        (void)_t3022;
        Array *_va53 = Array_new(_t3020, &(U64){_t3021}, &(U64){_t3022});
        (void)_va53;
        Str_delete(_t3020, &(Bool){1});
        ;
        ;
        U64 _t3023 = 0;
        (void)_t3023;
        Str *_t3024 = Str_clone(path);
        (void)_t3024;
        Array_set(_va53, &(U64){_t3023}, _t3024);
        ;
        U64 _t3025 = 1;
        (void)_t3025;
        Str *_t3026 = Str_lit(":", 1ULL);
        (void)_t3026;
        Array_set(_va53, &(U64){_t3025}, _t3026);
        ;
        U64 _t3027 = 2;
        (void)_t3027;
        Str *_t3028 = U32_to_str(&(U32){line});
        (void)_t3028;
        Array_set(_va53, &(U64){_t3027}, _t3028);
        ;
        U64 _t3029 = 3;
        (void)_t3029;
        Str *_t3030 = Str_lit(":", 1ULL);
        (void)_t3030;
        Array_set(_va53, &(U64){_t3029}, _t3030);
        ;
        U64 _t3031 = 4;
        (void)_t3031;
        Str *_t3032 = U32_to_str(&(U32){col});
        (void)_t3032;
        Array_set(_va53, &(U64){_t3031}, _t3032);
        ;
        U64 _t3033 = 5;
        (void)_t3033;
        Str *_t3034 = Str_lit(": error: unexpected character", 29ULL);
        (void)_t3034;
        Array_set(_va53, &(U64){_t3033}, _t3034);
        ;
        println(_va53);
        U64 _t3035 = 1;
        (void)_t3035;
        Str *_t3036 = Str_substr(src, &(U64){start}, &(U64){_t3035});
        (void)_t3036;
        ;
        ;
        U32 _t3037 = U32_clone(&(U32){col});
        (void)_t3037;
        ;
        Token *_t3038 = malloc(sizeof(Token));
        { TokenType *_ca = TokenType_clone(TokenType_Error()); _t3038->type = *_ca; free(_ca); }
        { Str *_ca = Str_clone(_t3036); _t3038->text = *_ca; free(_ca); }
        _t3038->line = U32_clone(&(U32){line});
        _t3038->col = _t3037;
        (void)_t3038;
        Str_delete(_t3036, &(Bool){1});
        ;
        Vec_push(tokens, _t3038);
        U64 _t3039 = U64_inc(DEREF(pos));
        (void)_t3039;
        *pos = _t3039;
        ;
    }
    ;
    U64 _t3042 = U64_sub(DEREF(pos), line_start);
    (void)_t3042;
    ;
    U64_delete(pos, &(Bool){1});
    U64 _t3043 = 1;
    (void)_t3043;
    U64 _t3044 = U64_add(_t3042, _t3043);
    (void)_t3044;
    ;
    ;
    I64 col = U64_to_i64(_t3044);
    (void)col;
    ;
    I64 _t3045 = I64_clone(&(I64){col});
    (void)_t3045;
    ;
    Token *_t3046 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(TokenType_Eof()); _t3046->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t3046->text = *_ca; free(_ca); }
    _t3046->line = U32_clone(&(U32){line});
    _t3046->col = _t3045;
    (void)_t3046;
    ;
    ;
    Vec_push(tokens, _t3046);
    return tokens;
}

