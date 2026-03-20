#include "modes_lexer.h"

Token * Token_clone(Token * self) {
    (void)self;
    U32 _t2482 = U32_clone(&self->line);
    (void)_t2482;
    U32 _t2483 = U32_clone(&self->col);
    (void)_t2483;
    Token *_t2484 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(&self->type); _t2484->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->text); _t2484->text = *_ca; free(_ca); }
    _t2484->line = _t2482;
    _t2484->col = _t2483;
    (void)_t2484;
    ;
    ;
    return _t2484;
}

void Token_delete(Token * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t2485 = 0;
    (void)_t2485;
    TokenType_delete(&self->type, &(Bool){_t2485});
    ;
    Bool _t2486 = 0;
    (void)_t2486;
    Str_delete(&self->text, &(Bool){_t2486});
    ;
    Bool _t2487 = 0;
    (void)_t2487;
    U32_delete(&self->line, &(Bool){_t2487});
    ;
    Bool _t2488 = 0;
    (void)_t2488;
    U32_delete(&self->col, &(Bool){_t2488});
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
    U8 _t2490 = 48;
    (void)_t2490;
    U8 _t2491 = 57;
    (void)_t2491;
    Bool _t2492; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t2490}); _t2492 = *_hp; free(_hp); }
    (void)_t2492;
    ;
    Bool _t2493; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t2491}); _t2493 = *_hp; free(_hp); }
    (void)_t2493;
    ;
    Bool _t2494 = Bool_and(_t2492, _t2493);
    (void)_t2494;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2494; return _r; }
}

Bool * is_alpha(U8 * c) {
    (void)c;
    U8 _t2495 = 97;
    (void)_t2495;
    U8 _t2496 = 122;
    (void)_t2496;
    Bool _t2497; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t2495}); _t2497 = *_hp; free(_hp); }
    (void)_t2497;
    ;
    Bool _t2498; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t2496}); _t2498 = *_hp; free(_hp); }
    (void)_t2498;
    ;
    U8 _t2499 = 65;
    (void)_t2499;
    U8 _t2500 = 90;
    (void)_t2500;
    Bool _t2501; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t2499}); _t2501 = *_hp; free(_hp); }
    (void)_t2501;
    ;
    Bool _t2502; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t2500}); _t2502 = *_hp; free(_hp); }
    (void)_t2502;
    ;
    Bool _t2503 = Bool_and(_t2497, _t2498);
    (void)_t2503;
    ;
    ;
    Bool _t2504 = Bool_and(_t2501, _t2502);
    (void)_t2504;
    ;
    ;
    U8 _t2505 = 95;
    (void)_t2505;
    Bool _t2506 = Bool_or(_t2503, _t2504);
    (void)_t2506;
    ;
    ;
    Bool _t2507 = U8_eq(DEREF(c), _t2505);
    (void)_t2507;
    ;
    Bool _t2508 = Bool_or(_t2506, _t2507);
    (void)_t2508;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2508; return _r; }
}

Bool * is_alnum(U8 * c) {
    (void)c;
    Bool _t2509; { Bool *_hp = (Bool *)is_alpha(c); _t2509 = *_hp; free(_hp); }
    (void)_t2509;
    Bool _t2510; { Bool *_hp = (Bool *)is_digit(c); _t2510 = *_hp; free(_hp); }
    (void)_t2510;
    Bool _t2511 = Bool_or(_t2509, _t2510);
    (void)_t2511;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2511; return _r; }
}

Str * tok_name(TokenType * type) {
    (void)type;
    {
        TokenType *_sw2512 = TokenType_clone(type);
        (void)_sw2512;
        Bool _t2645; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_Eof()); _t2645 = *_hp; free(_hp); }
        (void)_t2645;
        if (_t2645) {
            Str *_t2513 = Str_lit("eof", 3ULL);
            (void)_t2513;
            TokenType_delete(_sw2512, &(Bool){1});
            ;
            return _t2513;
        } else {
            Bool _t2644; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_LParen()); _t2644 = *_hp; free(_hp); }
            (void)_t2644;
            if (_t2644) {
                Str *_t2514 = Str_lit("(", 1ULL);
                (void)_t2514;
                ;
                TokenType_delete(_sw2512, &(Bool){1});
                ;
                return _t2514;
            } else {
                Bool _t2643; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_RParen()); _t2643 = *_hp; free(_hp); }
                (void)_t2643;
                if (_t2643) {
                    Str *_t2515 = Str_lit(")", 1ULL);
                    (void)_t2515;
                    ;
                    ;
                    TokenType_delete(_sw2512, &(Bool){1});
                    ;
                    return _t2515;
                } else {
                    Bool _t2642; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_LBrace()); _t2642 = *_hp; free(_hp); }
                    (void)_t2642;
                    if (_t2642) {
                        Str *_t2516 = Str_lit("{", 1ULL);
                        (void)_t2516;
                        ;
                        ;
                        ;
                        TokenType_delete(_sw2512, &(Bool){1});
                        ;
                        return _t2516;
                    } else {
                        Bool _t2641; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_RBrace()); _t2641 = *_hp; free(_hp); }
                        (void)_t2641;
                        if (_t2641) {
                            Str *_t2517 = Str_lit("}", 1ULL);
                            (void)_t2517;
                            ;
                            ;
                            ;
                            ;
                            TokenType_delete(_sw2512, &(Bool){1});
                            ;
                            return _t2517;
                        } else {
                            Bool _t2640; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_LBracket()); _t2640 = *_hp; free(_hp); }
                            (void)_t2640;
                            if (_t2640) {
                                Str *_t2518 = Str_lit("[", 1ULL);
                                (void)_t2518;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TokenType_delete(_sw2512, &(Bool){1});
                                ;
                                return _t2518;
                            } else {
                                Bool _t2639; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_RBracket()); _t2639 = *_hp; free(_hp); }
                                (void)_t2639;
                                if (_t2639) {
                                    Str *_t2519 = Str_lit("]", 1ULL);
                                    (void)_t2519;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TokenType_delete(_sw2512, &(Bool){1});
                                    ;
                                    return _t2519;
                                } else {
                                    Bool _t2638; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_Comma()); _t2638 = *_hp; free(_hp); }
                                    (void)_t2638;
                                    if (_t2638) {
                                        Str *_t2520 = Str_lit(",", 1ULL);
                                        (void)_t2520;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TokenType_delete(_sw2512, &(Bool){1});
                                        ;
                                        return _t2520;
                                    } else {
                                        Bool _t2637; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_Colon()); _t2637 = *_hp; free(_hp); }
                                        (void)_t2637;
                                        if (_t2637) {
                                            Str *_t2521 = Str_lit(":", 1ULL);
                                            (void)_t2521;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TokenType_delete(_sw2512, &(Bool){1});
                                            ;
                                            return _t2521;
                                        } else {
                                            Bool _t2636; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_Question()); _t2636 = *_hp; free(_hp); }
                                            (void)_t2636;
                                            if (_t2636) {
                                                Str *_t2522 = Str_lit("?", 1ULL);
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
                                                TokenType_delete(_sw2512, &(Bool){1});
                                                ;
                                                return _t2522;
                                            } else {
                                                Bool _t2635; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_Bang()); _t2635 = *_hp; free(_hp); }
                                                (void)_t2635;
                                                if (_t2635) {
                                                    Str *_t2523 = Str_lit("!", 1ULL);
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
                                                    TokenType_delete(_sw2512, &(Bool){1});
                                                    ;
                                                    return _t2523;
                                                } else {
                                                    Bool _t2634; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_Minus()); _t2634 = *_hp; free(_hp); }
                                                    (void)_t2634;
                                                    if (_t2634) {
                                                        Str *_t2524 = Str_lit("-", 1ULL);
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
                                                        TokenType_delete(_sw2512, &(Bool){1});
                                                        ;
                                                        return _t2524;
                                                    } else {
                                                        Bool _t2633; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_Plus()); _t2633 = *_hp; free(_hp); }
                                                        (void)_t2633;
                                                        if (_t2633) {
                                                            Str *_t2525 = Str_lit("+", 1ULL);
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
                                                            TokenType_delete(_sw2512, &(Bool){1});
                                                            ;
                                                            return _t2525;
                                                        } else {
                                                            Bool _t2632; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_Star()); _t2632 = *_hp; free(_hp); }
                                                            (void)_t2632;
                                                            if (_t2632) {
                                                                Str *_t2526 = Str_lit("*", 1ULL);
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
                                                                TokenType_delete(_sw2512, &(Bool){1});
                                                                ;
                                                                return _t2526;
                                                            } else {
                                                                Bool _t2631; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_Slash()); _t2631 = *_hp; free(_hp); }
                                                                (void)_t2631;
                                                                if (_t2631) {
                                                                    Str *_t2527 = Str_lit("/", 1ULL);
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
                                                                    TokenType_delete(_sw2512, &(Bool){1});
                                                                    ;
                                                                    return _t2527;
                                                                } else {
                                                                    Bool _t2630; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_Dot()); _t2630 = *_hp; free(_hp); }
                                                                    (void)_t2630;
                                                                    if (_t2630) {
                                                                        Str *_t2528 = Str_lit(".", 1ULL);
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
                                                                        TokenType_delete(_sw2512, &(Bool){1});
                                                                        ;
                                                                        return _t2528;
                                                                    } else {
                                                                        Bool _t2629; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_DotDot()); _t2629 = *_hp; free(_hp); }
                                                                        (void)_t2629;
                                                                        if (_t2629) {
                                                                            Str *_t2529 = Str_lit("..", 2ULL);
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
                                                                            TokenType_delete(_sw2512, &(Bool){1});
                                                                            ;
                                                                            return _t2529;
                                                                        } else {
                                                                            Bool _t2628; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_DotDotDot()); _t2628 = *_hp; free(_hp); }
                                                                            (void)_t2628;
                                                                            if (_t2628) {
                                                                                Str *_t2530 = Str_lit("...", 3ULL);
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
                                                                                TokenType_delete(_sw2512, &(Bool){1});
                                                                                ;
                                                                                return _t2530;
                                                                            } else {
                                                                                Bool _t2627; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_Eq()); _t2627 = *_hp; free(_hp); }
                                                                                (void)_t2627;
                                                                                if (_t2627) {
                                                                                    Str *_t2531 = Str_lit("=", 1ULL);
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
                                                                                    TokenType_delete(_sw2512, &(Bool){1});
                                                                                    ;
                                                                                    return _t2531;
                                                                                } else {
                                                                                    Bool _t2626; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_EqEq()); _t2626 = *_hp; free(_hp); }
                                                                                    (void)_t2626;
                                                                                    if (_t2626) {
                                                                                        Str *_t2532 = Str_lit("==", 2ULL);
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
                                                                                        TokenType_delete(_sw2512, &(Bool){1});
                                                                                        ;
                                                                                        return _t2532;
                                                                                    } else {
                                                                                        Bool _t2625; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_Neq()); _t2625 = *_hp; free(_hp); }
                                                                                        (void)_t2625;
                                                                                        if (_t2625) {
                                                                                            Str *_t2533 = Str_lit("!=", 2ULL);
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
                                                                                            TokenType_delete(_sw2512, &(Bool){1});
                                                                                            ;
                                                                                            return _t2533;
                                                                                        } else {
                                                                                            Bool _t2624; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_Lt()); _t2624 = *_hp; free(_hp); }
                                                                                            (void)_t2624;
                                                                                            if (_t2624) {
                                                                                                Str *_t2534 = Str_lit("<", 1ULL);
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
                                                                                                TokenType_delete(_sw2512, &(Bool){1});
                                                                                                ;
                                                                                                return _t2534;
                                                                                            } else {
                                                                                                Bool _t2623; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_LtEq()); _t2623 = *_hp; free(_hp); }
                                                                                                (void)_t2623;
                                                                                                if (_t2623) {
                                                                                                    Str *_t2535 = Str_lit("<=", 2ULL);
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
                                                                                                    TokenType_delete(_sw2512, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t2535;
                                                                                                } else {
                                                                                                    Bool _t2622; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_Gt()); _t2622 = *_hp; free(_hp); }
                                                                                                    (void)_t2622;
                                                                                                    if (_t2622) {
                                                                                                        Str *_t2536 = Str_lit(">", 1ULL);
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
                                                                                                        TokenType_delete(_sw2512, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t2536;
                                                                                                    } else {
                                                                                                        Bool _t2621; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_GtEq()); _t2621 = *_hp; free(_hp); }
                                                                                                        (void)_t2621;
                                                                                                        if (_t2621) {
                                                                                                            Str *_t2537 = Str_lit(">=", 2ULL);
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
                                                                                                            TokenType_delete(_sw2512, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t2537;
                                                                                                        } else {
                                                                                                            Bool _t2620; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_ColonEq()); _t2620 = *_hp; free(_hp); }
                                                                                                            (void)_t2620;
                                                                                                            if (_t2620) {
                                                                                                                Str *_t2538 = Str_lit(":=", 2ULL);
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
                                                                                                                TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                ;
                                                                                                                return _t2538;
                                                                                                            } else {
                                                                                                                Bool _t2619; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_Ident()); _t2619 = *_hp; free(_hp); }
                                                                                                                (void)_t2619;
                                                                                                                if (_t2619) {
                                                                                                                    Str *_t2539 = Str_lit("identifier", 10ULL);
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
                                                                                                                    TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return _t2539;
                                                                                                                } else {
                                                                                                                    Bool _t2618; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_StringTok()); _t2618 = *_hp; free(_hp); }
                                                                                                                    (void)_t2618;
                                                                                                                    if (_t2618) {
                                                                                                                        Str *_t2540 = Str_lit("string", 6ULL);
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
                                                                                                                        TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return _t2540;
                                                                                                                    } else {
                                                                                                                        Bool _t2617; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_Number()); _t2617 = *_hp; free(_hp); }
                                                                                                                        (void)_t2617;
                                                                                                                        if (_t2617) {
                                                                                                                            Str *_t2541 = Str_lit("number", 6ULL);
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
                                                                                                                            TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return _t2541;
                                                                                                                        } else {
                                                                                                                            Bool _t2616; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_Char()); _t2616 = *_hp; free(_hp); }
                                                                                                                            (void)_t2616;
                                                                                                                            if (_t2616) {
                                                                                                                                Str *_t2542 = Str_lit("char", 4ULL);
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
                                                                                                                                TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return _t2542;
                                                                                                                            } else {
                                                                                                                                Bool _t2615; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwMode()); _t2615 = *_hp; free(_hp); }
                                                                                                                                (void)_t2615;
                                                                                                                                if (_t2615) {
                                                                                                                                    Str *_t2543 = Str_lit("mode", 4ULL);
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
                                                                                                                                    TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return _t2543;
                                                                                                                                } else {
                                                                                                                                    Bool _t2614; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwMut()); _t2614 = *_hp; free(_hp); }
                                                                                                                                    (void)_t2614;
                                                                                                                                    if (_t2614) {
                                                                                                                                        Str *_t2544 = Str_lit("mut", 3ULL);
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
                                                                                                                                        TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return _t2544;
                                                                                                                                    } else {
                                                                                                                                        Bool _t2613; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwOwn()); _t2613 = *_hp; free(_hp); }
                                                                                                                                        (void)_t2613;
                                                                                                                                        if (_t2613) {
                                                                                                                                            Str *_t2545 = Str_lit("own", 3ULL);
                                                                                                                                            (void)_t2545;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return _t2545;
                                                                                                                                        } else {
                                                                                                                                            Bool _t2612; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwRef()); _t2612 = *_hp; free(_hp); }
                                                                                                                                            (void)_t2612;
                                                                                                                                            if (_t2612) {
                                                                                                                                                Str *_t2546 = Str_lit("ref", 3ULL);
                                                                                                                                                (void)_t2546;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return _t2546;
                                                                                                                                            } else {
                                                                                                                                                Bool _t2611; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwShallow()); _t2611 = *_hp; free(_hp); }
                                                                                                                                                (void)_t2611;
                                                                                                                                                if (_t2611) {
                                                                                                                                                    Str *_t2547 = Str_lit("shallow", 7ULL);
                                                                                                                                                    (void)_t2547;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                    ;
                                                                                                                                                    return _t2547;
                                                                                                                                                } else {
                                                                                                                                                    Bool _t2610; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwStruct()); _t2610 = *_hp; free(_hp); }
                                                                                                                                                    (void)_t2610;
                                                                                                                                                    if (_t2610) {
                                                                                                                                                        Str *_t2548 = Str_lit("struct", 6ULL);
                                                                                                                                                        (void)_t2548;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                        ;
                                                                                                                                                        return _t2548;
                                                                                                                                                    } else {
                                                                                                                                                        Bool _t2609; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwExtStruct()); _t2609 = *_hp; free(_hp); }
                                                                                                                                                        (void)_t2609;
                                                                                                                                                        if (_t2609) {
                                                                                                                                                            Str *_t2549 = Str_lit("ext_struct", 10ULL);
                                                                                                                                                            (void)_t2549;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                            ;
                                                                                                                                                            return _t2549;
                                                                                                                                                        } else {
                                                                                                                                                            Bool _t2608; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwEnum()); _t2608 = *_hp; free(_hp); }
                                                                                                                                                            (void)_t2608;
                                                                                                                                                            if (_t2608) {
                                                                                                                                                                Str *_t2550 = Str_lit("enum", 4ULL);
                                                                                                                                                                (void)_t2550;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                ;
                                                                                                                                                                return _t2550;
                                                                                                                                                            } else {
                                                                                                                                                                Bool _t2607; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwNamespace()); _t2607 = *_hp; free(_hp); }
                                                                                                                                                                (void)_t2607;
                                                                                                                                                                if (_t2607) {
                                                                                                                                                                    Str *_t2551 = Str_lit("namespace", 9ULL);
                                                                                                                                                                    (void)_t2551;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                    ;
                                                                                                                                                                    return _t2551;
                                                                                                                                                                } else {
                                                                                                                                                                    Bool _t2606; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwFunc()); _t2606 = *_hp; free(_hp); }
                                                                                                                                                                    (void)_t2606;
                                                                                                                                                                    if (_t2606) {
                                                                                                                                                                        Str *_t2552 = Str_lit("func", 4ULL);
                                                                                                                                                                        (void)_t2552;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                        ;
                                                                                                                                                                        return _t2552;
                                                                                                                                                                    } else {
                                                                                                                                                                        Bool _t2605; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwProc()); _t2605 = *_hp; free(_hp); }
                                                                                                                                                                        (void)_t2605;
                                                                                                                                                                        if (_t2605) {
                                                                                                                                                                            Str *_t2553 = Str_lit("proc", 4ULL);
                                                                                                                                                                            (void)_t2553;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                            ;
                                                                                                                                                                            return _t2553;
                                                                                                                                                                        } else {
                                                                                                                                                                            Bool _t2604; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwTest()); _t2604 = *_hp; free(_hp); }
                                                                                                                                                                            (void)_t2604;
                                                                                                                                                                            if (_t2604) {
                                                                                                                                                                                Str *_t2554 = Str_lit("test", 4ULL);
                                                                                                                                                                                (void)_t2554;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                ;
                                                                                                                                                                                return _t2554;
                                                                                                                                                                            } else {
                                                                                                                                                                                Bool _t2603; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwMacro()); _t2603 = *_hp; free(_hp); }
                                                                                                                                                                                (void)_t2603;
                                                                                                                                                                                if (_t2603) {
                                                                                                                                                                                    Str *_t2555 = Str_lit("macro", 5ULL);
                                                                                                                                                                                    (void)_t2555;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                    ;
                                                                                                                                                                                    return _t2555;
                                                                                                                                                                                } else {
                                                                                                                                                                                    Bool _t2602; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwExtFunc()); _t2602 = *_hp; free(_hp); }
                                                                                                                                                                                    (void)_t2602;
                                                                                                                                                                                    if (_t2602) {
                                                                                                                                                                                        Str *_t2556 = Str_lit("ext_func", 8ULL);
                                                                                                                                                                                        (void)_t2556;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                        ;
                                                                                                                                                                                        return _t2556;
                                                                                                                                                                                    } else {
                                                                                                                                                                                        Bool _t2601; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwExtProc()); _t2601 = *_hp; free(_hp); }
                                                                                                                                                                                        (void)_t2601;
                                                                                                                                                                                        if (_t2601) {
                                                                                                                                                                                            Str *_t2557 = Str_lit("ext_proc", 8ULL);
                                                                                                                                                                                            (void)_t2557;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                            ;
                                                                                                                                                                                            return _t2557;
                                                                                                                                                                                        } else {
                                                                                                                                                                                            Bool _t2600; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwReturns()); _t2600 = *_hp; free(_hp); }
                                                                                                                                                                                            (void)_t2600;
                                                                                                                                                                                            if (_t2600) {
                                                                                                                                                                                                Str *_t2558 = Str_lit("returns", 7ULL);
                                                                                                                                                                                                (void)_t2558;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                                ;
                                                                                                                                                                                                return _t2558;
                                                                                                                                                                                            } else {
                                                                                                                                                                                                Bool _t2599; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwThrows()); _t2599 = *_hp; free(_hp); }
                                                                                                                                                                                                (void)_t2599;
                                                                                                                                                                                                if (_t2599) {
                                                                                                                                                                                                    Str *_t2559 = Str_lit("throws", 6ULL);
                                                                                                                                                                                                    (void)_t2559;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    return _t2559;
                                                                                                                                                                                                } else {
                                                                                                                                                                                                    Bool _t2598; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwIf()); _t2598 = *_hp; free(_hp); }
                                                                                                                                                                                                    (void)_t2598;
                                                                                                                                                                                                    if (_t2598) {
                                                                                                                                                                                                        Str *_t2560 = Str_lit("if", 2ULL);
                                                                                                                                                                                                        (void)_t2560;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        return _t2560;
                                                                                                                                                                                                    } else {
                                                                                                                                                                                                        Bool _t2597; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwElse()); _t2597 = *_hp; free(_hp); }
                                                                                                                                                                                                        (void)_t2597;
                                                                                                                                                                                                        if (_t2597) {
                                                                                                                                                                                                            Str *_t2561 = Str_lit("else", 4ULL);
                                                                                                                                                                                                            (void)_t2561;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            return _t2561;
                                                                                                                                                                                                        } else {
                                                                                                                                                                                                            Bool _t2596; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwWhile()); _t2596 = *_hp; free(_hp); }
                                                                                                                                                                                                            (void)_t2596;
                                                                                                                                                                                                            if (_t2596) {
                                                                                                                                                                                                                Str *_t2562 = Str_lit("while", 5ULL);
                                                                                                                                                                                                                (void)_t2562;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                return _t2562;
                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                Bool _t2595; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwFor()); _t2595 = *_hp; free(_hp); }
                                                                                                                                                                                                                (void)_t2595;
                                                                                                                                                                                                                if (_t2595) {
                                                                                                                                                                                                                    Str *_t2563 = Str_lit("for", 3ULL);
                                                                                                                                                                                                                    (void)_t2563;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    return _t2563;
                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                    Bool _t2594; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwIn()); _t2594 = *_hp; free(_hp); }
                                                                                                                                                                                                                    (void)_t2594;
                                                                                                                                                                                                                    if (_t2594) {
                                                                                                                                                                                                                        Str *_t2564 = Str_lit("in", 2ULL);
                                                                                                                                                                                                                        (void)_t2564;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        return _t2564;
                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                        Bool _t2593; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwSwitch()); _t2593 = *_hp; free(_hp); }
                                                                                                                                                                                                                        (void)_t2593;
                                                                                                                                                                                                                        if (_t2593) {
                                                                                                                                                                                                                            Str *_t2565 = Str_lit("switch", 6ULL);
                                                                                                                                                                                                                            (void)_t2565;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            return _t2565;
                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                            Bool _t2592; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwMatch()); _t2592 = *_hp; free(_hp); }
                                                                                                                                                                                                                            (void)_t2592;
                                                                                                                                                                                                                            if (_t2592) {
                                                                                                                                                                                                                                Str *_t2566 = Str_lit("match", 5ULL);
                                                                                                                                                                                                                                (void)_t2566;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                return _t2566;
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                Bool _t2591; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwCase()); _t2591 = *_hp; free(_hp); }
                                                                                                                                                                                                                                (void)_t2591;
                                                                                                                                                                                                                                if (_t2591) {
                                                                                                                                                                                                                                    Str *_t2567 = Str_lit("case", 4ULL);
                                                                                                                                                                                                                                    (void)_t2567;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    return _t2567;
                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                    Bool _t2590; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwDefault()); _t2590 = *_hp; free(_hp); }
                                                                                                                                                                                                                                    (void)_t2590;
                                                                                                                                                                                                                                    if (_t2590) {
                                                                                                                                                                                                                                        Str *_t2568 = Str_lit("default", 7ULL);
                                                                                                                                                                                                                                        (void)_t2568;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        return _t2568;
                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                        Bool _t2589; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwReturn()); _t2589 = *_hp; free(_hp); }
                                                                                                                                                                                                                                        (void)_t2589;
                                                                                                                                                                                                                                        if (_t2589) {
                                                                                                                                                                                                                                            Str *_t2569 = Str_lit("return", 6ULL);
                                                                                                                                                                                                                                            (void)_t2569;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            return _t2569;
                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                            Bool _t2588; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwThrow()); _t2588 = *_hp; free(_hp); }
                                                                                                                                                                                                                                            (void)_t2588;
                                                                                                                                                                                                                                            if (_t2588) {
                                                                                                                                                                                                                                                Str *_t2570 = Str_lit("throw", 5ULL);
                                                                                                                                                                                                                                                (void)_t2570;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                return _t2570;
                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                Bool _t2587; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwCatch()); _t2587 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                (void)_t2587;
                                                                                                                                                                                                                                                if (_t2587) {
                                                                                                                                                                                                                                                    Str *_t2571 = Str_lit("catch", 5ULL);
                                                                                                                                                                                                                                                    (void)_t2571;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    return _t2571;
                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                    Bool _t2586; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwBreak()); _t2586 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                    (void)_t2586;
                                                                                                                                                                                                                                                    if (_t2586) {
                                                                                                                                                                                                                                                        Str *_t2572 = Str_lit("break", 5ULL);
                                                                                                                                                                                                                                                        (void)_t2572;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        return _t2572;
                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                        Bool _t2585; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwContinue()); _t2585 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                        (void)_t2585;
                                                                                                                                                                                                                                                        if (_t2585) {
                                                                                                                                                                                                                                                            Str *_t2573 = Str_lit("continue", 8ULL);
                                                                                                                                                                                                                                                            (void)_t2573;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            return _t2573;
                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                            Bool _t2584; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwDefer()); _t2584 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                            (void)_t2584;
                                                                                                                                                                                                                                                            if (_t2584) {
                                                                                                                                                                                                                                                                Str *_t2574 = Str_lit("defer", 5ULL);
                                                                                                                                                                                                                                                                (void)_t2574;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                return _t2574;
                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                Bool _t2583; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwTrue()); _t2583 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                (void)_t2583;
                                                                                                                                                                                                                                                                if (_t2583) {
                                                                                                                                                                                                                                                                    Str *_t2575 = Str_lit("true", 4ULL);
                                                                                                                                                                                                                                                                    (void)_t2575;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t2575;
                                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                                    Bool _t2582; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwFalse()); _t2582 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                    (void)_t2582;
                                                                                                                                                                                                                                                                    if (_t2582) {
                                                                                                                                                                                                                                                                        Str *_t2576 = Str_lit("false", 5ULL);
                                                                                                                                                                                                                                                                        (void)_t2576;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        return _t2576;
                                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                                        Bool _t2581; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_KwNull()); _t2581 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                        (void)_t2581;
                                                                                                                                                                                                                                                                        if (_t2581) {
                                                                                                                                                                                                                                                                            Str *_t2577 = Str_lit("NULL", 4ULL);
                                                                                                                                                                                                                                                                            (void)_t2577;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            return _t2577;
                                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                                            Bool _t2580; { Bool *_hp = (Bool *)TokenType_eq(_sw2512, TokenType_Error()); _t2580 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                            (void)_t2580;
                                                                                                                                                                                                                                                                            if (_t2580) {
                                                                                                                                                                                                                                                                                Str *_t2578 = Str_lit("error", 5ULL);
                                                                                                                                                                                                                                                                                (void)_t2578;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t2578;
                                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                                Str *_t2579 = Str_lit("?", 1ULL);
                                                                                                                                                                                                                                                                                (void)_t2579;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                TokenType_delete(_sw2512, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t2579;
                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                        }
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                    }
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                }
                                                                                                                                                                                                                ;
                                                                                                                                                                                                            }
                                                                                                                                                                                                            ;
                                                                                                                                                                                                        }
                                                                                                                                                                                                        ;
                                                                                                                                                                                                    }
                                                                                                                                                                                                    ;
                                                                                                                                                                                                }
                                                                                                                                                                                                ;
                                                                                                                                                                                            }
                                                                                                                                                                                            ;
                                                                                                                                                                                        }
                                                                                                                                                                                        ;
                                                                                                                                                                                    }
                                                                                                                                                                                    ;
                                                                                                                                                                                }
                                                                                                                                                                                ;
                                                                                                                                                                            }
                                                                                                                                                                            ;
                                                                                                                                                                        }
                                                                                                                                                                        ;
                                                                                                                                                                    }
                                                                                                                                                                    ;
                                                                                                                                                                }
                                                                                                                                                                ;
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                        ;
                                                                                                                                                    }
                                                                                                                                                    ;
                                                                                                                                                }
                                                                                                                                                ;
                                                                                                                                            }
                                                                                                                                            ;
                                                                                                                                        }
                                                                                                                                        ;
                                                                                                                                    }
                                                                                                                                    ;
                                                                                                                                }
                                                                                                                                ;
                                                                                                                            }
                                                                                                                            ;
                                                                                                                        }
                                                                                                                        ;
                                                                                                                    }
                                                                                                                    ;
                                                                                                                }
                                                                                                                ;
                                                                                                            }
                                                                                                            ;
                                                                                                        }
                                                                                                        ;
                                                                                                    }
                                                                                                    ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                            ;
                                                                                        }
                                                                                        ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                                ;
                                                                            }
                                                                            ;
                                                                        }
                                                                        ;
                                                                    }
                                                                    ;
                                                                }
                                                                ;
                                                            }
                                                            ;
                                                        }
                                                        ;
                                                    }
                                                    ;
                                                }
                                                ;
                                            }
                                            ;
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        TokenType_delete(_sw2512, &(Bool){1});
        ;
    }
}

TokenType * lookup_keyword(Str * word) {
    (void)word;
    {
        Str *_sw2646 = Str_clone(word);
        (void)_sw2646;
        Str *_t2715 = Str_lit("mode", 4ULL);
        (void)_t2715;
        Bool _t2716; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2715); _t2716 = *_hp; free(_hp); }
        (void)_t2716;
        Str_delete(_t2715, &(Bool){1});
        if (_t2716) {
            Str_delete(_sw2646, &(Bool){1});
            ;
            return TokenType_KwMode();
        } else {
            Str *_t2713 = Str_lit("mut", 3ULL);
            (void)_t2713;
            Bool _t2714; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2713); _t2714 = *_hp; free(_hp); }
            (void)_t2714;
            Str_delete(_t2713, &(Bool){1});
            if (_t2714) {
                ;
                Str_delete(_sw2646, &(Bool){1});
                ;
                return TokenType_KwMut();
            } else {
                Str *_t2711 = Str_lit("own", 3ULL);
                (void)_t2711;
                Bool _t2712; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2711); _t2712 = *_hp; free(_hp); }
                (void)_t2712;
                Str_delete(_t2711, &(Bool){1});
                if (_t2712) {
                    ;
                    ;
                    Str_delete(_sw2646, &(Bool){1});
                    ;
                    return TokenType_KwOwn();
                } else {
                    Str *_t2709 = Str_lit("ref", 3ULL);
                    (void)_t2709;
                    Bool _t2710; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2709); _t2710 = *_hp; free(_hp); }
                    (void)_t2710;
                    Str_delete(_t2709, &(Bool){1});
                    if (_t2710) {
                        ;
                        ;
                        ;
                        Str_delete(_sw2646, &(Bool){1});
                        ;
                        return TokenType_KwRef();
                    } else {
                        Str *_t2707 = Str_lit("shallow", 7ULL);
                        (void)_t2707;
                        Bool _t2708; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2707); _t2708 = *_hp; free(_hp); }
                        (void)_t2708;
                        Str_delete(_t2707, &(Bool){1});
                        if (_t2708) {
                            ;
                            ;
                            ;
                            ;
                            Str_delete(_sw2646, &(Bool){1});
                            ;
                            return TokenType_KwShallow();
                        } else {
                            Str *_t2705 = Str_lit("struct", 6ULL);
                            (void)_t2705;
                            Bool _t2706; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2705); _t2706 = *_hp; free(_hp); }
                            (void)_t2706;
                            Str_delete(_t2705, &(Bool){1});
                            if (_t2706) {
                                ;
                                ;
                                ;
                                ;
                                ;
                                Str_delete(_sw2646, &(Bool){1});
                                ;
                                return TokenType_KwStruct();
                            } else {
                                Str *_t2703 = Str_lit("ext_struct", 10ULL);
                                (void)_t2703;
                                Bool _t2704; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2703); _t2704 = *_hp; free(_hp); }
                                (void)_t2704;
                                Str_delete(_t2703, &(Bool){1});
                                if (_t2704) {
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    Str_delete(_sw2646, &(Bool){1});
                                    ;
                                    return TokenType_KwExtStruct();
                                } else {
                                    Str *_t2701 = Str_lit("enum", 4ULL);
                                    (void)_t2701;
                                    Bool _t2702; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2701); _t2702 = *_hp; free(_hp); }
                                    (void)_t2702;
                                    Str_delete(_t2701, &(Bool){1});
                                    if (_t2702) {
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        Str_delete(_sw2646, &(Bool){1});
                                        ;
                                        return TokenType_KwEnum();
                                    } else {
                                        Str *_t2699 = Str_lit("namespace", 9ULL);
                                        (void)_t2699;
                                        Bool _t2700; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2699); _t2700 = *_hp; free(_hp); }
                                        (void)_t2700;
                                        Str_delete(_t2699, &(Bool){1});
                                        if (_t2700) {
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            Str_delete(_sw2646, &(Bool){1});
                                            ;
                                            return TokenType_KwNamespace();
                                        } else {
                                            Str *_t2697 = Str_lit("func", 4ULL);
                                            (void)_t2697;
                                            Bool _t2698; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2697); _t2698 = *_hp; free(_hp); }
                                            (void)_t2698;
                                            Str_delete(_t2697, &(Bool){1});
                                            if (_t2698) {
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                Str_delete(_sw2646, &(Bool){1});
                                                ;
                                                return TokenType_KwFunc();
                                            } else {
                                                Str *_t2695 = Str_lit("proc", 4ULL);
                                                (void)_t2695;
                                                Bool _t2696; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2695); _t2696 = *_hp; free(_hp); }
                                                (void)_t2696;
                                                Str_delete(_t2695, &(Bool){1});
                                                if (_t2696) {
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    Str_delete(_sw2646, &(Bool){1});
                                                    ;
                                                    return TokenType_KwProc();
                                                } else {
                                                    Str *_t2693 = Str_lit("test", 4ULL);
                                                    (void)_t2693;
                                                    Bool _t2694; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2693); _t2694 = *_hp; free(_hp); }
                                                    (void)_t2694;
                                                    Str_delete(_t2693, &(Bool){1});
                                                    if (_t2694) {
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        Str_delete(_sw2646, &(Bool){1});
                                                        ;
                                                        return TokenType_KwTest();
                                                    } else {
                                                        Str *_t2691 = Str_lit("macro", 5ULL);
                                                        (void)_t2691;
                                                        Bool _t2692; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2691); _t2692 = *_hp; free(_hp); }
                                                        (void)_t2692;
                                                        Str_delete(_t2691, &(Bool){1});
                                                        if (_t2692) {
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            Str_delete(_sw2646, &(Bool){1});
                                                            ;
                                                            return TokenType_KwMacro();
                                                        } else {
                                                            Str *_t2689 = Str_lit("ext_func", 8ULL);
                                                            (void)_t2689;
                                                            Bool _t2690; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2689); _t2690 = *_hp; free(_hp); }
                                                            (void)_t2690;
                                                            Str_delete(_t2689, &(Bool){1});
                                                            if (_t2690) {
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                Str_delete(_sw2646, &(Bool){1});
                                                                ;
                                                                return TokenType_KwExtFunc();
                                                            } else {
                                                                Str *_t2687 = Str_lit("ext_proc", 8ULL);
                                                                (void)_t2687;
                                                                Bool _t2688; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2687); _t2688 = *_hp; free(_hp); }
                                                                (void)_t2688;
                                                                Str_delete(_t2687, &(Bool){1});
                                                                if (_t2688) {
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    Str_delete(_sw2646, &(Bool){1});
                                                                    ;
                                                                    return TokenType_KwExtProc();
                                                                } else {
                                                                    Str *_t2685 = Str_lit("returns", 7ULL);
                                                                    (void)_t2685;
                                                                    Bool _t2686; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2685); _t2686 = *_hp; free(_hp); }
                                                                    (void)_t2686;
                                                                    Str_delete(_t2685, &(Bool){1});
                                                                    if (_t2686) {
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        Str_delete(_sw2646, &(Bool){1});
                                                                        ;
                                                                        return TokenType_KwReturns();
                                                                    } else {
                                                                        Str *_t2683 = Str_lit("throws", 6ULL);
                                                                        (void)_t2683;
                                                                        Bool _t2684; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2683); _t2684 = *_hp; free(_hp); }
                                                                        (void)_t2684;
                                                                        Str_delete(_t2683, &(Bool){1});
                                                                        if (_t2684) {
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            Str_delete(_sw2646, &(Bool){1});
                                                                            ;
                                                                            return TokenType_KwThrows();
                                                                        } else {
                                                                            Str *_t2681 = Str_lit("if", 2ULL);
                                                                            (void)_t2681;
                                                                            Bool _t2682; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2681); _t2682 = *_hp; free(_hp); }
                                                                            (void)_t2682;
                                                                            Str_delete(_t2681, &(Bool){1});
                                                                            if (_t2682) {
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                Str_delete(_sw2646, &(Bool){1});
                                                                                ;
                                                                                return TokenType_KwIf();
                                                                            } else {
                                                                                Str *_t2679 = Str_lit("else", 4ULL);
                                                                                (void)_t2679;
                                                                                Bool _t2680; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2679); _t2680 = *_hp; free(_hp); }
                                                                                (void)_t2680;
                                                                                Str_delete(_t2679, &(Bool){1});
                                                                                if (_t2680) {
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    Str_delete(_sw2646, &(Bool){1});
                                                                                    ;
                                                                                    return TokenType_KwElse();
                                                                                } else {
                                                                                    Str *_t2677 = Str_lit("while", 5ULL);
                                                                                    (void)_t2677;
                                                                                    Bool _t2678; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2677); _t2678 = *_hp; free(_hp); }
                                                                                    (void)_t2678;
                                                                                    Str_delete(_t2677, &(Bool){1});
                                                                                    if (_t2678) {
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        Str_delete(_sw2646, &(Bool){1});
                                                                                        ;
                                                                                        return TokenType_KwWhile();
                                                                                    } else {
                                                                                        Str *_t2675 = Str_lit("for", 3ULL);
                                                                                        (void)_t2675;
                                                                                        Bool _t2676; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2675); _t2676 = *_hp; free(_hp); }
                                                                                        (void)_t2676;
                                                                                        Str_delete(_t2675, &(Bool){1});
                                                                                        if (_t2676) {
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            Str_delete(_sw2646, &(Bool){1});
                                                                                            ;
                                                                                            return TokenType_KwFor();
                                                                                        } else {
                                                                                            Str *_t2673 = Str_lit("in", 2ULL);
                                                                                            (void)_t2673;
                                                                                            Bool _t2674; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2673); _t2674 = *_hp; free(_hp); }
                                                                                            (void)_t2674;
                                                                                            Str_delete(_t2673, &(Bool){1});
                                                                                            if (_t2674) {
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                Str_delete(_sw2646, &(Bool){1});
                                                                                                ;
                                                                                                return TokenType_KwIn();
                                                                                            } else {
                                                                                                Str *_t2671 = Str_lit("switch", 6ULL);
                                                                                                (void)_t2671;
                                                                                                Bool _t2672; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2671); _t2672 = *_hp; free(_hp); }
                                                                                                (void)_t2672;
                                                                                                Str_delete(_t2671, &(Bool){1});
                                                                                                if (_t2672) {
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    Str_delete(_sw2646, &(Bool){1});
                                                                                                    ;
                                                                                                    return TokenType_KwSwitch();
                                                                                                } else {
                                                                                                    Str *_t2669 = Str_lit("match", 5ULL);
                                                                                                    (void)_t2669;
                                                                                                    Bool _t2670; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2669); _t2670 = *_hp; free(_hp); }
                                                                                                    (void)_t2670;
                                                                                                    Str_delete(_t2669, &(Bool){1});
                                                                                                    if (_t2670) {
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        Str_delete(_sw2646, &(Bool){1});
                                                                                                        ;
                                                                                                        return TokenType_KwMatch();
                                                                                                    } else {
                                                                                                        Str *_t2667 = Str_lit("case", 4ULL);
                                                                                                        (void)_t2667;
                                                                                                        Bool _t2668; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2667); _t2668 = *_hp; free(_hp); }
                                                                                                        (void)_t2668;
                                                                                                        Str_delete(_t2667, &(Bool){1});
                                                                                                        if (_t2668) {
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            Str_delete(_sw2646, &(Bool){1});
                                                                                                            ;
                                                                                                            return TokenType_KwCase();
                                                                                                        } else {
                                                                                                            Str *_t2665 = Str_lit("default", 7ULL);
                                                                                                            (void)_t2665;
                                                                                                            Bool _t2666; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2665); _t2666 = *_hp; free(_hp); }
                                                                                                            (void)_t2666;
                                                                                                            Str_delete(_t2665, &(Bool){1});
                                                                                                            if (_t2666) {
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                Str_delete(_sw2646, &(Bool){1});
                                                                                                                ;
                                                                                                                return TokenType_KwDefault();
                                                                                                            } else {
                                                                                                                Str *_t2663 = Str_lit("return", 6ULL);
                                                                                                                (void)_t2663;
                                                                                                                Bool _t2664; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2663); _t2664 = *_hp; free(_hp); }
                                                                                                                (void)_t2664;
                                                                                                                Str_delete(_t2663, &(Bool){1});
                                                                                                                if (_t2664) {
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    Str_delete(_sw2646, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return TokenType_KwReturn();
                                                                                                                } else {
                                                                                                                    Str *_t2661 = Str_lit("throw", 5ULL);
                                                                                                                    (void)_t2661;
                                                                                                                    Bool _t2662; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2661); _t2662 = *_hp; free(_hp); }
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
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        Str_delete(_sw2646, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return TokenType_KwThrow();
                                                                                                                    } else {
                                                                                                                        Str *_t2659 = Str_lit("catch", 5ULL);
                                                                                                                        (void)_t2659;
                                                                                                                        Bool _t2660; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2659); _t2660 = *_hp; free(_hp); }
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
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            Str_delete(_sw2646, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return TokenType_KwCatch();
                                                                                                                        } else {
                                                                                                                            Str *_t2657 = Str_lit("break", 5ULL);
                                                                                                                            (void)_t2657;
                                                                                                                            Bool _t2658; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2657); _t2658 = *_hp; free(_hp); }
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
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                Str_delete(_sw2646, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return TokenType_KwBreak();
                                                                                                                            } else {
                                                                                                                                Str *_t2655 = Str_lit("continue", 8ULL);
                                                                                                                                (void)_t2655;
                                                                                                                                Bool _t2656; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2655); _t2656 = *_hp; free(_hp); }
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
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    Str_delete(_sw2646, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return TokenType_KwContinue();
                                                                                                                                } else {
                                                                                                                                    Str *_t2653 = Str_lit("defer", 5ULL);
                                                                                                                                    (void)_t2653;
                                                                                                                                    Bool _t2654; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2653); _t2654 = *_hp; free(_hp); }
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
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        Str_delete(_sw2646, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return TokenType_KwDefer();
                                                                                                                                    } else {
                                                                                                                                        Str *_t2651 = Str_lit("true", 4ULL);
                                                                                                                                        (void)_t2651;
                                                                                                                                        Bool _t2652; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2651); _t2652 = *_hp; free(_hp); }
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
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            Str_delete(_sw2646, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return TokenType_KwTrue();
                                                                                                                                        } else {
                                                                                                                                            Str *_t2649 = Str_lit("false", 5ULL);
                                                                                                                                            (void)_t2649;
                                                                                                                                            Bool _t2650; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2649); _t2650 = *_hp; free(_hp); }
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
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                Str_delete(_sw2646, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return TokenType_KwFalse();
                                                                                                                                            } else {
                                                                                                                                                Str *_t2647 = Str_lit("NULL", 4ULL);
                                                                                                                                                (void)_t2647;
                                                                                                                                                Bool _t2648; { Bool *_hp = (Bool *)Str_eq(_sw2646, _t2647); _t2648 = *_hp; free(_hp); }
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
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    Str_delete(_sw2646, &(Bool){1});
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
                                                                                                                                                    Str_delete(_sw2646, &(Bool){1});
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
        Str_delete(_sw2646, &(Bool){1});
        ;
    }
}

Vec * tokenize(Str * src, Str * path) {
    (void)src;
    (void)path;
    Str *_t3056 = Str_lit("Token", 5ULL);
    (void)_t3056;
    U64 _t3057; { U64 *_hp = (U64 *)Token_size(); _t3057 = *_hp; free(_hp); }
    (void)_t3057;
    Vec *tokens = Vec_new(_t3056, &(U64){_t3057});
    (void)tokens;
    Str_delete(_t3056, &(Bool){1});
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
        Bool _wcond2717; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2717 = *_hp; free(_hp); }
        (void)_wcond2717;
        if (_wcond2717) {
        } else {
            ;
            break;
        }
        ;
        U8 *c = Str_byte_at(src, pos);
        (void)c;
        U8 _t3001 = 32;
        (void)_t3001;
        U8 _t3002 = 9;
        (void)_t3002;
        Bool _t3003 = U8_eq(DEREF(c), _t3001);
        (void)_t3003;
        ;
        Bool _t3004 = U8_eq(DEREF(c), _t3002);
        (void)_t3004;
        ;
        U8 _t3005 = 13;
        (void)_t3005;
        Bool _t3006 = Bool_or(_t3003, _t3004);
        (void)_t3006;
        ;
        ;
        Bool _t3007 = U8_eq(DEREF(c), _t3005);
        (void)_t3007;
        ;
        U8 _t3008 = 59;
        (void)_t3008;
        Bool _t3009 = Bool_or(_t3006, _t3007);
        (void)_t3009;
        ;
        ;
        Bool _t3010 = U8_eq(DEREF(c), _t3008);
        (void)_t3010;
        ;
        Bool _t3011 = Bool_or(_t3009, _t3010);
        (void)_t3011;
        ;
        ;
        if (_t3011) {
            U64_inc(pos);
            ;
            continue;
        }
        ;
        U8 _t3012 = 10;
        (void)_t3012;
        Bool _t3013 = U8_eq(DEREF(c), _t3012);
        (void)_t3013;
        ;
        if (_t3013) {
            U64_inc(pos);
            U32 _t2718 = 1;
            (void)_t2718;
            U32 _t2719 = U32_add(line, _t2718);
            (void)_t2719;
            ;
            line = _t2719;
            ;
            U64 _t2720 = U64_clone(pos);
            (void)_t2720;
            line_start = _t2720;
            ;
            ;
            continue;
        }
        ;
        U64 _t3014 = U64_sub(DEREF(pos), line_start);
        (void)_t3014;
        U64 _t3015 = 1;
        (void)_t3015;
        U64 _t3016 = U64_add(_t3014, _t3015);
        (void)_t3016;
        ;
        ;
        I64 _t3017 = U64_to_i64(_t3016);
        (void)_t3017;
        ;
        U32 col = I64_to_u32(_t3017);
        (void)col;
        ;
        U64 start = U64_clone(pos);
        (void)start;
        U8 _t3018 = 35;
        (void)_t3018;
        Bool _t3019 = U8_eq(DEREF(c), _t3018);
        (void)_t3019;
        ;
        if (_t3019) {
            while (1) {
                Bool _wcond2721; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2721 = *_hp; free(_hp); }
                (void)_wcond2721;
                if (_wcond2721) {
                } else {
                    ;
                    break;
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
        U8 _t3020 = 47;
        (void)_t3020;
        U64 _t3021 = 1;
        (void)_t3021;
        U64 _t3022 = U64_add(DEREF(pos), _t3021);
        (void)_t3022;
        ;
        Bool _t3023 = U8_eq(DEREF(c), _t3020);
        (void)_t3023;
        ;
        Bool _t3024; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3022}, &(U64){src_len}); _t3024 = *_hp; free(_hp); }
        (void)_t3024;
        ;
        Bool _t3025 = Bool_and(_t3023, _t3024);
        (void)_t3025;
        ;
        ;
        if (_t3025) {
            U64 _t2781 = 1;
            (void)_t2781;
            U64 *_t2782 = malloc(sizeof(U64)); *_t2782 = U64_add(DEREF(pos), _t2781);
            (void)_t2782;
            ;
            U8 *c2 = Str_byte_at(src, _t2782);
            (void)c2;
            U8 _t2783 = 47;
            (void)_t2783;
            Bool _t2784 = U8_eq(DEREF(c2), _t2783);
            (void)_t2784;
            ;
            if (_t2784) {
                while (1) {
                    Bool _wcond2725; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2725 = *_hp; free(_hp); }
                    (void)_wcond2725;
                    if (_wcond2725) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U8 *_t2726 = Str_byte_at(src, pos);
                    (void)_t2726;
                    U8 _t2727 = 10;
                    (void)_t2727;
                    Bool _t2728 = U8_eq(DEREF(_t2726), _t2727);
                    (void)_t2728;
                    ;
                    if (_t2728) {
                        ;
                        break;
                    }
                    ;
                    U64_inc(pos);
                }
                U64_delete(_t2782, &(Bool){1});
                ;
                ;
                ;
                ;
                continue;
            }
            ;
            U8 _t2785 = 42;
            (void)_t2785;
            Bool _t2786 = U8_eq(DEREF(c2), _t2785);
            (void)_t2786;
            U64_delete(_t2782, &(Bool){1});
            ;
            if (_t2786) {
                U64 _t2777 = 2;
                (void)_t2777;
                U64 _t2778 = U64_add(DEREF(pos), _t2777);
                (void)_t2778;
                ;
                *pos = _t2778;
                ;
                I64 depth = 1;
                (void)depth;
                while (1) {
                    Bool _wcond2729; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2729 = *_hp; free(_hp); }
                    (void)_wcond2729;
                    if (_wcond2729) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    I64 _t2754 = 0;
                    (void)_t2754;
                    Bool _t2755; { Bool *_hp = (Bool *)I64_lte(&(I64){depth}, &(I64){_t2754}); _t2755 = *_hp; free(_hp); }
                    (void)_t2755;
                    ;
                    if (_t2755) {
                        ;
                        break;
                    }
                    ;
                    U64 _t2756 = 1;
                    (void)_t2756;
                    U64 _t2757 = U64_add(DEREF(pos), _t2756);
                    (void)_t2757;
                    ;
                    Bool _t2758; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2757}, &(U64){src_len}); _t2758 = *_hp; free(_hp); }
                    (void)_t2758;
                    ;
                    if (_t2758) {
                        U8 *b1 = Str_byte_at(src, pos);
                        (void)b1;
                        U64 _t2738 = 1;
                        (void)_t2738;
                        U64 *_t2739 = malloc(sizeof(U64)); *_t2739 = U64_add(DEREF(pos), _t2738);
                        (void)_t2739;
                        ;
                        U8 *b2 = Str_byte_at(src, _t2739);
                        (void)b2;
                        U8 _t2740 = 47;
                        (void)_t2740;
                        U8 _t2741 = 42;
                        (void)_t2741;
                        Bool _t2742 = U8_eq(DEREF(b1), _t2740);
                        (void)_t2742;
                        ;
                        Bool _t2743 = U8_eq(DEREF(b2), _t2741);
                        (void)_t2743;
                        ;
                        Bool _t2744 = Bool_and(_t2742, _t2743);
                        (void)_t2744;
                        ;
                        ;
                        if (_t2744) {
                            I64 _t2730 = 1;
                            (void)_t2730;
                            I64 _t2731 = I64_add(depth, _t2730);
                            (void)_t2731;
                            ;
                            depth = _t2731;
                            ;
                            U64 _t2732 = 2;
                            (void)_t2732;
                            U64 _t2733 = U64_add(DEREF(pos), _t2732);
                            (void)_t2733;
                            ;
                            *pos = _t2733;
                            ;
                            U64_delete(_t2739, &(Bool){1});
                            ;
                            ;
                            continue;
                        }
                        ;
                        U8 _t2745 = 42;
                        (void)_t2745;
                        U8 _t2746 = 47;
                        (void)_t2746;
                        Bool _t2747 = U8_eq(DEREF(b1), _t2745);
                        (void)_t2747;
                        ;
                        Bool _t2748 = U8_eq(DEREF(b2), _t2746);
                        (void)_t2748;
                        U64_delete(_t2739, &(Bool){1});
                        ;
                        Bool _t2749 = Bool_and(_t2747, _t2748);
                        (void)_t2749;
                        ;
                        ;
                        if (_t2749) {
                            I64 _t2734 = 1;
                            (void)_t2734;
                            I64 _t2735 = I64_sub(depth, _t2734);
                            (void)_t2735;
                            ;
                            depth = _t2735;
                            ;
                            U64 _t2736 = 2;
                            (void)_t2736;
                            U64 _t2737 = U64_add(DEREF(pos), _t2736);
                            (void)_t2737;
                            ;
                            *pos = _t2737;
                            ;
                            ;
                            ;
                            continue;
                        }
                        ;
                    }
                    ;
                    U8 *_t2759 = Str_byte_at(src, pos);
                    (void)_t2759;
                    U8 _t2760 = 10;
                    (void)_t2760;
                    Bool _t2761 = U8_eq(DEREF(_t2759), _t2760);
                    (void)_t2761;
                    ;
                    if (_t2761) {
                        U32 _t2750 = 1;
                        (void)_t2750;
                        U32 _t2751 = U32_add(line, _t2750);
                        (void)_t2751;
                        ;
                        line = _t2751;
                        ;
                        U64 _t2752 = 1;
                        (void)_t2752;
                        U64 _t2753 = U64_add(DEREF(pos), _t2752);
                        (void)_t2753;
                        ;
                        line_start = _t2753;
                        ;
                    }
                    ;
                    U64_inc(pos);
                }
                I64 _t2779 = 0;
                (void)_t2779;
                Bool _t2780; { Bool *_hp = (Bool *)I64_gt(&(I64){depth}, &(I64){_t2779}); _t2780 = *_hp; free(_hp); }
                (void)_t2780;
                ;
                ;
                if (_t2780) {
                    Str *_t2762 = Str_lit("Str", 3ULL);
                    (void)_t2762;
                    U64 _t2763; { U64 *_hp = (U64 *)Str_size(); _t2763 = *_hp; free(_hp); }
                    (void)_t2763;
                    U64 _t2764 = 6;
                    (void)_t2764;
                    Array *_va50 = Array_new(_t2762, &(U64){_t2763}, &(U64){_t2764});
                    (void)_va50;
                    Str_delete(_t2762, &(Bool){1});
                    ;
                    ;
                    U64 _t2765 = 0;
                    (void)_t2765;
                    Str *_t2766 = Str_clone(path);
                    (void)_t2766;
                    Array_set(_va50, &(U64){_t2765}, _t2766);
                    ;
                    U64 _t2767 = 1;
                    (void)_t2767;
                    Str *_t2768 = Str_lit(":", 1ULL);
                    (void)_t2768;
                    Array_set(_va50, &(U64){_t2767}, _t2768);
                    ;
                    U64 _t2769 = 2;
                    (void)_t2769;
                    Str *_t2770 = U32_to_str(&(U32){line});
                    (void)_t2770;
                    Array_set(_va50, &(U64){_t2769}, _t2770);
                    ;
                    U64 _t2771 = 3;
                    (void)_t2771;
                    Str *_t2772 = Str_lit(":", 1ULL);
                    (void)_t2772;
                    Array_set(_va50, &(U64){_t2771}, _t2772);
                    ;
                    U64 _t2773 = 4;
                    (void)_t2773;
                    Str *_t2774 = U32_to_str(&(U32){col});
                    (void)_t2774;
                    Array_set(_va50, &(U64){_t2773}, _t2774);
                    ;
                    U64 _t2775 = 5;
                    (void)_t2775;
                    Str *_t2776 = Str_lit(": error: unterminated comment", 29ULL);
                    (void)_t2776;
                    Array_set(_va50, &(U64){_t2775}, _t2776);
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
        Bool _t3026; { Bool *_hp = (Bool *)is_digit(c); _t3026 = *_hp; free(_hp); }
        (void)_t3026;
        if (_t3026) {
            while (1) {
                Bool _wcond2787; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2787 = *_hp; free(_hp); }
                (void)_wcond2787;
                if (_wcond2787) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2788 = Str_byte_at(src, pos);
                (void)_t2788;
                Bool _t2789; { Bool *_hp = (Bool *)is_digit(_t2788); _t2789 = *_hp; free(_hp); }
                (void)_t2789;
                Bool _t2790 = Bool_not(_t2789);
                (void)_t2790;
                ;
                if (_t2790) {
                    ;
                    break;
                }
                ;
                U64_inc(pos);
            }
            U64 _t2803 = 1;
            (void)_t2803;
            U64 _t2804 = U64_add(DEREF(pos), _t2803);
            (void)_t2804;
            ;
            Bool _t2805; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2804}, &(U64){src_len}); _t2805 = *_hp; free(_hp); }
            (void)_t2805;
            ;
            if (_t2805) {
                U8 *_t2795 = Str_byte_at(src, pos);
                (void)_t2795;
                U8 _t2796 = 46;
                (void)_t2796;
                U64 _t2797 = 1;
                (void)_t2797;
                U64 *_t2798 = malloc(sizeof(U64)); *_t2798 = U64_add(DEREF(pos), _t2797);
                (void)_t2798;
                ;
                U8 *_t2799 = Str_byte_at(src, _t2798);
                (void)_t2799;
                Bool _t2800 = U8_eq(DEREF(_t2795), _t2796);
                (void)_t2800;
                ;
                Bool _t2801; { Bool *_hp = (Bool *)is_digit(_t2799); _t2801 = *_hp; free(_hp); }
                (void)_t2801;
                U64_delete(_t2798, &(Bool){1});
                Bool _t2802 = Bool_and(_t2800, _t2801);
                (void)_t2802;
                ;
                ;
                if (_t2802) {
                    U64_inc(pos);
                    while (1) {
                        Bool _wcond2791; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2791 = *_hp; free(_hp); }
                        (void)_wcond2791;
                        if (_wcond2791) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U8 *_t2792 = Str_byte_at(src, pos);
                        (void)_t2792;
                        Bool _t2793; { Bool *_hp = (Bool *)is_digit(_t2792); _t2793 = *_hp; free(_hp); }
                        (void)_t2793;
                        Bool _t2794 = Bool_not(_t2793);
                        (void)_t2794;
                        ;
                        if (_t2794) {
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
            U64 _t2806 = U64_sub(DEREF(pos), start);
            (void)_t2806;
            Str *_t2807 = Str_substr(src, &(U64){start}, &(U64){_t2806});
            (void)_t2807;
            ;
            U32 _t2808 = U32_clone(&(U32){col});
            (void)_t2808;
            Token *_t2809 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(TokenType_Number()); _t2809->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(_t2807); _t2809->text = *_ca; free(_ca); }
            _t2809->line = U32_clone(&(U32){line});
            _t2809->col = _t2808;
            (void)_t2809;
            Str_delete(_t2807, &(Bool){1});
            ;
            Vec_push(tokens, _t2809);
            ;
            ;
            ;
            continue;
        }
        ;
        Bool _t3027; { Bool *_hp = (Bool *)is_alpha(c); _t3027 = *_hp; free(_hp); }
        (void)_t3027;
        if (_t3027) {
            while (1) {
                Bool _wcond2810; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2810 = *_hp; free(_hp); }
                (void)_wcond2810;
                if (_wcond2810) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2811 = Str_byte_at(src, pos);
                (void)_t2811;
                Bool _t2812; { Bool *_hp = (Bool *)is_alnum(_t2811); _t2812 = *_hp; free(_hp); }
                (void)_t2812;
                Bool _t2813 = Bool_not(_t2812);
                (void)_t2813;
                ;
                if (_t2813) {
                    ;
                    break;
                }
                ;
                U64_inc(pos);
            }
            U64 _t2814 = U64_sub(DEREF(pos), start);
            (void)_t2814;
            Str *word = Str_substr(src, &(U64){start}, &(U64){_t2814});
            (void)word;
            ;
            TokenType *type = lookup_keyword(word);
            (void)type;
            U32 _t2815 = U32_clone(&(U32){line});
            (void)_t2815;
            U32 _t2816 = U32_clone(&(U32){col});
            (void)_t2816;
            Token *_t2817 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(type); _t2817->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(word); _t2817->text = *_ca; free(_ca); }
            _t2817->line = _t2815;
            _t2817->col = _t2816;
            (void)_t2817;
            ;
            ;
            TokenType_delete(type, &(Bool){1});
            Str_delete(word, &(Bool){1});
            Vec_push(tokens, _t2817);
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t3028 = 34;
        (void)_t3028;
        Bool _t3029 = U8_eq(DEREF(c), _t3028);
        (void)_t3029;
        ;
        if (_t3029) {
            U64_inc(pos);
            while (1) {
                Bool _wcond2818; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2818 = *_hp; free(_hp); }
                (void)_wcond2818;
                if (_wcond2818) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2823 = Str_byte_at(src, pos);
                (void)_t2823;
                U8 _t2824 = 34;
                (void)_t2824;
                Bool _t2825 = U8_eq(DEREF(_t2823), _t2824);
                (void)_t2825;
                ;
                if (_t2825) {
                    ;
                    break;
                }
                ;
                U8 *_t2826 = Str_byte_at(src, pos);
                (void)_t2826;
                U8 _t2827 = 92;
                (void)_t2827;
                U64 _t2828 = 1;
                (void)_t2828;
                U64 _t2829 = U64_add(DEREF(pos), _t2828);
                (void)_t2829;
                ;
                Bool _t2830 = U8_eq(DEREF(_t2826), _t2827);
                (void)_t2830;
                ;
                Bool _t2831; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2829}, &(U64){src_len}); _t2831 = *_hp; free(_hp); }
                (void)_t2831;
                ;
                Bool _t2832 = Bool_and(_t2830, _t2831);
                (void)_t2832;
                ;
                ;
                if (_t2832) {
                    U64_inc(pos);
                }
                ;
                U8 *_t2833 = Str_byte_at(src, pos);
                (void)_t2833;
                U8 _t2834 = 10;
                (void)_t2834;
                Bool _t2835 = U8_eq(DEREF(_t2833), _t2834);
                (void)_t2835;
                ;
                if (_t2835) {
                    U32 _t2819 = 1;
                    (void)_t2819;
                    U32 _t2820 = U32_add(line, _t2819);
                    (void)_t2820;
                    ;
                    line = _t2820;
                    ;
                    U64 _t2821 = 1;
                    (void)_t2821;
                    U64 _t2822 = U64_add(DEREF(pos), _t2821);
                    (void)_t2822;
                    ;
                    line_start = _t2822;
                    ;
                }
                ;
                U64_inc(pos);
            }
            U8 *_t2863 = Str_byte_at(src, pos);
            (void)_t2863;
            U8 _t2864 = 34;
            (void)_t2864;
            Bool _t2865; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2865 = *_hp; free(_hp); }
            (void)_t2865;
            Bool _t2866 = U8_eq(DEREF(_t2863), _t2864);
            (void)_t2866;
            ;
            Bool _t2867 = Bool_and(_t2865, _t2866);
            (void)_t2867;
            ;
            ;
            if (_t2867) {
                U64_inc(pos);
                U64 _t2836 = 1;
                (void)_t2836;
                U64 _t2837 = U64_sub(DEREF(pos), start);
                (void)_t2837;
                U64 _t2838 = 2;
                (void)_t2838;
                U64 _t2839 = U64_add(start, _t2836);
                (void)_t2839;
                ;
                U64 _t2840 = U64_sub(_t2837, _t2838);
                (void)_t2840;
                ;
                ;
                Str *_t2841 = Str_substr(src, &(U64){_t2839}, &(U64){_t2840});
                (void)_t2841;
                ;
                ;
                U32 _t2842 = U32_clone(&(U32){col});
                (void)_t2842;
                Token *_t2843 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_StringTok()); _t2843->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2841); _t2843->text = *_ca; free(_ca); }
                _t2843->line = U32_clone(&(U32){line});
                _t2843->col = _t2842;
                (void)_t2843;
                Str_delete(_t2841, &(Bool){1});
                ;
                Vec_push(tokens, _t2843);
            } else {
                Str *_t2844 = Str_lit("Str", 3ULL);
                (void)_t2844;
                U64 _t2845; { U64 *_hp = (U64 *)Str_size(); _t2845 = *_hp; free(_hp); }
                (void)_t2845;
                U64 _t2846 = 6;
                (void)_t2846;
                Array *_va51 = Array_new(_t2844, &(U64){_t2845}, &(U64){_t2846});
                (void)_va51;
                Str_delete(_t2844, &(Bool){1});
                ;
                ;
                U64 _t2847 = 0;
                (void)_t2847;
                Str *_t2848 = Str_clone(path);
                (void)_t2848;
                Array_set(_va51, &(U64){_t2847}, _t2848);
                ;
                U64 _t2849 = 1;
                (void)_t2849;
                Str *_t2850 = Str_lit(":", 1ULL);
                (void)_t2850;
                Array_set(_va51, &(U64){_t2849}, _t2850);
                ;
                U64 _t2851 = 2;
                (void)_t2851;
                Str *_t2852 = U32_to_str(&(U32){line});
                (void)_t2852;
                Array_set(_va51, &(U64){_t2851}, _t2852);
                ;
                U64 _t2853 = 3;
                (void)_t2853;
                Str *_t2854 = Str_lit(":", 1ULL);
                (void)_t2854;
                Array_set(_va51, &(U64){_t2853}, _t2854);
                ;
                U64 _t2855 = 4;
                (void)_t2855;
                Str *_t2856 = U32_to_str(&(U32){col});
                (void)_t2856;
                Array_set(_va51, &(U64){_t2855}, _t2856);
                ;
                U64 _t2857 = 5;
                (void)_t2857;
                Str *_t2858 = Str_lit(": error: unterminated string", 28ULL);
                (void)_t2858;
                Array_set(_va51, &(U64){_t2857}, _t2858);
                ;
                println(_va51);
                U64 _t2859 = U64_sub(DEREF(pos), start);
                (void)_t2859;
                Str *_t2860 = Str_substr(src, &(U64){start}, &(U64){_t2859});
                (void)_t2860;
                ;
                U32 _t2861 = U32_clone(&(U32){col});
                (void)_t2861;
                Token *_t2862 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2862->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2860); _t2862->text = *_ca; free(_ca); }
                _t2862->line = U32_clone(&(U32){line});
                _t2862->col = _t2861;
                (void)_t2862;
                Str_delete(_t2860, &(Bool){1});
                ;
                Vec_push(tokens, _t2862);
            }
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t3030 = 39;
        (void)_t3030;
        Bool _t3031 = U8_eq(DEREF(c), _t3030);
        (void)_t3031;
        ;
        if (_t3031) {
            U64_inc(pos);
            U64 ch_start = U64_clone(pos);
            (void)ch_start;
            U8 *_t2891 = Str_byte_at(src, pos);
            (void)_t2891;
            U8 _t2892 = 92;
            (void)_t2892;
            U64 _t2893 = 1;
            (void)_t2893;
            U64 _t2894 = U64_add(DEREF(pos), _t2893);
            (void)_t2894;
            ;
            Bool _t2895 = U8_eq(DEREF(_t2891), _t2892);
            (void)_t2895;
            ;
            Bool _t2896; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2894}, &(U64){src_len}); _t2896 = *_hp; free(_hp); }
            (void)_t2896;
            ;
            Bool _t2897; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2897 = *_hp; free(_hp); }
            (void)_t2897;
            Bool _t2898 = Bool_and(_t2895, _t2896);
            (void)_t2898;
            ;
            ;
            Bool _t2899 = Bool_and(_t2897, _t2898);
            (void)_t2899;
            ;
            ;
            if (_t2899) {
                U64_inc(pos);
            }
            ;
            U64_inc(pos);
            U8 *_t2900 = Str_byte_at(src, pos);
            (void)_t2900;
            U8 _t2901 = 39;
            (void)_t2901;
            Bool _t2902; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2902 = *_hp; free(_hp); }
            (void)_t2902;
            Bool _t2903 = U8_eq(DEREF(_t2900), _t2901);
            (void)_t2903;
            ;
            Bool _t2904 = Bool_and(_t2902, _t2903);
            (void)_t2904;
            ;
            ;
            if (_t2904) {
                U64 _t2868 = U64_sub(DEREF(pos), ch_start);
                (void)_t2868;
                Str *_t2869 = Str_substr(src, &(U64){ch_start}, &(U64){_t2868});
                (void)_t2869;
                ;
                U32 _t2870 = U32_clone(&(U32){col});
                (void)_t2870;
                Token *_t2871 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Char()); _t2871->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2869); _t2871->text = *_ca; free(_ca); }
                _t2871->line = U32_clone(&(U32){line});
                _t2871->col = _t2870;
                (void)_t2871;
                Str_delete(_t2869, &(Bool){1});
                ;
                Vec_push(tokens, _t2871);
                U64_inc(pos);
            } else {
                Str *_t2872 = Str_lit("Str", 3ULL);
                (void)_t2872;
                U64 _t2873; { U64 *_hp = (U64 *)Str_size(); _t2873 = *_hp; free(_hp); }
                (void)_t2873;
                U64 _t2874 = 6;
                (void)_t2874;
                Array *_va52 = Array_new(_t2872, &(U64){_t2873}, &(U64){_t2874});
                (void)_va52;
                Str_delete(_t2872, &(Bool){1});
                ;
                ;
                U64 _t2875 = 0;
                (void)_t2875;
                Str *_t2876 = Str_clone(path);
                (void)_t2876;
                Array_set(_va52, &(U64){_t2875}, _t2876);
                ;
                U64 _t2877 = 1;
                (void)_t2877;
                Str *_t2878 = Str_lit(":", 1ULL);
                (void)_t2878;
                Array_set(_va52, &(U64){_t2877}, _t2878);
                ;
                U64 _t2879 = 2;
                (void)_t2879;
                Str *_t2880 = U32_to_str(&(U32){line});
                (void)_t2880;
                Array_set(_va52, &(U64){_t2879}, _t2880);
                ;
                U64 _t2881 = 3;
                (void)_t2881;
                Str *_t2882 = Str_lit(":", 1ULL);
                (void)_t2882;
                Array_set(_va52, &(U64){_t2881}, _t2882);
                ;
                U64 _t2883 = 4;
                (void)_t2883;
                Str *_t2884 = U32_to_str(&(U32){col});
                (void)_t2884;
                Array_set(_va52, &(U64){_t2883}, _t2884);
                ;
                U64 _t2885 = 5;
                (void)_t2885;
                Str *_t2886 = Str_lit(": error: unterminated character literal", 39ULL);
                (void)_t2886;
                Array_set(_va52, &(U64){_t2885}, _t2886);
                ;
                println(_va52);
                U64 _t2887 = U64_sub(DEREF(pos), start);
                (void)_t2887;
                Str *_t2888 = Str_substr(src, &(U64){start}, &(U64){_t2887});
                (void)_t2888;
                ;
                U32 _t2889 = U32_clone(&(U32){col});
                (void)_t2889;
                Token *_t2890 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2890->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2888); _t2890->text = *_ca; free(_ca); }
                _t2890->line = U32_clone(&(U32){line});
                _t2890->col = _t2889;
                (void)_t2890;
                Str_delete(_t2888, &(Bool){1});
                ;
                Vec_push(tokens, _t2890);
            }
            ;
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U64 _t3032 = 1;
        (void)_t3032;
        U64 _t3033 = U64_add(DEREF(pos), _t3032);
        (void)_t3033;
        ;
        Bool _t3034; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3033}, &(U64){src_len}); _t3034 = *_hp; free(_hp); }
        (void)_t3034;
        ;
        if (_t3034) {
            U64 _t2950 = 1;
            (void)_t2950;
            U64 *_t2951 = malloc(sizeof(U64)); *_t2951 = U64_add(DEREF(pos), _t2950);
            (void)_t2951;
            ;
            U8 *c2 = Str_byte_at(src, _t2951);
            (void)c2;
            TokenType *two = TokenType_clone(TokenType_Eof());
            (void)two;
            U8 _t2952 = 58;
            (void)_t2952;
            U8 _t2953 = 61;
            (void)_t2953;
            Bool _t2954 = U8_eq(DEREF(c), _t2952);
            (void)_t2954;
            ;
            Bool _t2955 = U8_eq(DEREF(c2), _t2953);
            (void)_t2955;
            ;
            Bool _t2956 = Bool_and(_t2954, _t2955);
            (void)_t2956;
            ;
            ;
            if (_t2956) {
                two = TokenType_clone(TokenType_ColonEq());
            } else {
                U8 _t2938 = 61;
                (void)_t2938;
                U8 _t2939 = 61;
                (void)_t2939;
                Bool _t2940 = U8_eq(DEREF(c), _t2938);
                (void)_t2940;
                ;
                Bool _t2941 = U8_eq(DEREF(c2), _t2939);
                (void)_t2941;
                ;
                Bool _t2942 = Bool_and(_t2940, _t2941);
                (void)_t2942;
                ;
                ;
                if (_t2942) {
                    two = TokenType_clone(TokenType_EqEq());
                } else {
                    U8 _t2933 = 33;
                    (void)_t2933;
                    U8 _t2934 = 61;
                    (void)_t2934;
                    Bool _t2935 = U8_eq(DEREF(c), _t2933);
                    (void)_t2935;
                    ;
                    Bool _t2936 = U8_eq(DEREF(c2), _t2934);
                    (void)_t2936;
                    ;
                    Bool _t2937 = Bool_and(_t2935, _t2936);
                    (void)_t2937;
                    ;
                    ;
                    if (_t2937) {
                        two = TokenType_clone(TokenType_Neq());
                    } else {
                        U8 _t2928 = 60;
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
                            two = TokenType_clone(TokenType_LtEq());
                        } else {
                            U8 _t2923 = 62;
                            (void)_t2923;
                            U8 _t2924 = 61;
                            (void)_t2924;
                            Bool _t2925 = U8_eq(DEREF(c), _t2923);
                            (void)_t2925;
                            ;
                            Bool _t2926 = U8_eq(DEREF(c2), _t2924);
                            (void)_t2926;
                            ;
                            Bool _t2927 = Bool_and(_t2925, _t2926);
                            (void)_t2927;
                            ;
                            ;
                            if (_t2927) {
                                two = TokenType_clone(TokenType_GtEq());
                            } else {
                                U8 _t2918 = 46;
                                (void)_t2918;
                                U8 _t2919 = 46;
                                (void)_t2919;
                                Bool _t2920 = U8_eq(DEREF(c), _t2918);
                                (void)_t2920;
                                ;
                                Bool _t2921 = U8_eq(DEREF(c2), _t2919);
                                (void)_t2921;
                                ;
                                Bool _t2922 = Bool_and(_t2920, _t2921);
                                (void)_t2922;
                                ;
                                ;
                                if (_t2922) {
                                    U64 _t2915 = 2;
                                    (void)_t2915;
                                    U64 _t2916 = U64_add(DEREF(pos), _t2915);
                                    (void)_t2916;
                                    ;
                                    Bool _t2917; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2916}, &(U64){src_len}); _t2917 = *_hp; free(_hp); }
                                    (void)_t2917;
                                    ;
                                    if (_t2917) {
                                        U64 _t2911 = 2;
                                        (void)_t2911;
                                        U64 *_t2912 = malloc(sizeof(U64)); *_t2912 = U64_add(DEREF(pos), _t2911);
                                        (void)_t2912;
                                        ;
                                        U8 *c3 = Str_byte_at(src, _t2912);
                                        (void)c3;
                                        U8 _t2913 = 46;
                                        (void)_t2913;
                                        Bool _t2914 = U8_eq(DEREF(c3), _t2913);
                                        (void)_t2914;
                                        U64_delete(_t2912, &(Bool){1});
                                        ;
                                        if (_t2914) {
                                            U64 _t2905 = 3;
                                            (void)_t2905;
                                            Str *_t2906 = Str_substr(src, &(U64){start}, &(U64){_t2905});
                                            (void)_t2906;
                                            ;
                                            U32 _t2907 = U32_clone(&(U32){col});
                                            (void)_t2907;
                                            Token *_t2908 = malloc(sizeof(Token));
                                            { TokenType *_ca = TokenType_clone(TokenType_DotDotDot()); _t2908->type = *_ca; free(_ca); }
                                            { Str *_ca = Str_clone(_t2906); _t2908->text = *_ca; free(_ca); }
                                            _t2908->line = U32_clone(&(U32){line});
                                            _t2908->col = _t2907;
                                            (void)_t2908;
                                            Str_delete(_t2906, &(Bool){1});
                                            ;
                                            Vec_push(tokens, _t2908);
                                            U64 _t2909 = 3;
                                            (void)_t2909;
                                            U64 _t2910 = U64_add(DEREF(pos), _t2909);
                                            (void)_t2910;
                                            ;
                                            *pos = _t2910;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            U64_delete(_t2951, &(Bool){1});
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
            U64_delete(_t2951, &(Bool){1});
            ;
            Bool _t2957; { Bool *_hp = (Bool *)TokenType_eq(two, TokenType_Eof()); _t2957 = *_hp; free(_hp); }
            (void)_t2957;
            Bool _t2958 = Bool_not(_t2957);
            (void)_t2958;
            ;
            if (_t2958) {
                U64 _t2943 = 2;
                (void)_t2943;
                Str *_t2944 = Str_substr(src, &(U64){start}, &(U64){_t2943});
                (void)_t2944;
                ;
                U32 _t2945 = U32_clone(&(U32){line});
                (void)_t2945;
                U32 _t2946 = U32_clone(&(U32){col});
                (void)_t2946;
                Token *_t2947 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(two); _t2947->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2944); _t2947->text = *_ca; free(_ca); }
                _t2947->line = _t2945;
                _t2947->col = _t2946;
                (void)_t2947;
                Str_delete(_t2944, &(Bool){1});
                ;
                ;
                Vec_push(tokens, _t2947);
                U64 _t2948 = 2;
                (void)_t2948;
                U64 _t2949 = U64_add(DEREF(pos), _t2948);
                (void)_t2949;
                ;
                *pos = _t2949;
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
            U8 _sw2959 = U8_clone(c);
            (void)_sw2959;
            U8 _t2994 = 40;
            (void)_t2994;
            Bool _t2995 = U8_eq(_sw2959, _t2994);
            (void)_t2995;
            ;
            if (_t2995) {
                single = TokenType_clone(TokenType_LParen());
            } else {
                U8 _t2992 = 41;
                (void)_t2992;
                Bool _t2993 = U8_eq(_sw2959, _t2992);
                (void)_t2993;
                ;
                if (_t2993) {
                    single = TokenType_clone(TokenType_RParen());
                } else {
                    U8 _t2990 = 123;
                    (void)_t2990;
                    Bool _t2991 = U8_eq(_sw2959, _t2990);
                    (void)_t2991;
                    ;
                    if (_t2991) {
                        single = TokenType_clone(TokenType_LBrace());
                    } else {
                        U8 _t2988 = 125;
                        (void)_t2988;
                        Bool _t2989 = U8_eq(_sw2959, _t2988);
                        (void)_t2989;
                        ;
                        if (_t2989) {
                            single = TokenType_clone(TokenType_RBrace());
                        } else {
                            U8 _t2986 = 91;
                            (void)_t2986;
                            Bool _t2987 = U8_eq(_sw2959, _t2986);
                            (void)_t2987;
                            ;
                            if (_t2987) {
                                single = TokenType_clone(TokenType_LBracket());
                            } else {
                                U8 _t2984 = 93;
                                (void)_t2984;
                                Bool _t2985 = U8_eq(_sw2959, _t2984);
                                (void)_t2985;
                                ;
                                if (_t2985) {
                                    single = TokenType_clone(TokenType_RBracket());
                                } else {
                                    U8 _t2982 = 44;
                                    (void)_t2982;
                                    Bool _t2983 = U8_eq(_sw2959, _t2982);
                                    (void)_t2983;
                                    ;
                                    if (_t2983) {
                                        single = TokenType_clone(TokenType_Comma());
                                    } else {
                                        U8 _t2980 = 58;
                                        (void)_t2980;
                                        Bool _t2981 = U8_eq(_sw2959, _t2980);
                                        (void)_t2981;
                                        ;
                                        if (_t2981) {
                                            single = TokenType_clone(TokenType_Colon());
                                        } else {
                                            U8 _t2978 = 46;
                                            (void)_t2978;
                                            Bool _t2979 = U8_eq(_sw2959, _t2978);
                                            (void)_t2979;
                                            ;
                                            if (_t2979) {
                                                single = TokenType_clone(TokenType_Dot());
                                            } else {
                                                U8 _t2976 = 63;
                                                (void)_t2976;
                                                Bool _t2977 = U8_eq(_sw2959, _t2976);
                                                (void)_t2977;
                                                ;
                                                if (_t2977) {
                                                    single = TokenType_clone(TokenType_Question());
                                                } else {
                                                    U8 _t2974 = 33;
                                                    (void)_t2974;
                                                    Bool _t2975 = U8_eq(_sw2959, _t2974);
                                                    (void)_t2975;
                                                    ;
                                                    if (_t2975) {
                                                        single = TokenType_clone(TokenType_Bang());
                                                    } else {
                                                        U8 _t2972 = 43;
                                                        (void)_t2972;
                                                        Bool _t2973 = U8_eq(_sw2959, _t2972);
                                                        (void)_t2973;
                                                        ;
                                                        if (_t2973) {
                                                            single = TokenType_clone(TokenType_Plus());
                                                        } else {
                                                            U8 _t2970 = 45;
                                                            (void)_t2970;
                                                            Bool _t2971 = U8_eq(_sw2959, _t2970);
                                                            (void)_t2971;
                                                            ;
                                                            if (_t2971) {
                                                                single = TokenType_clone(TokenType_Minus());
                                                            } else {
                                                                U8 _t2968 = 42;
                                                                (void)_t2968;
                                                                Bool _t2969 = U8_eq(_sw2959, _t2968);
                                                                (void)_t2969;
                                                                ;
                                                                if (_t2969) {
                                                                    single = TokenType_clone(TokenType_Star());
                                                                } else {
                                                                    U8 _t2966 = 47;
                                                                    (void)_t2966;
                                                                    Bool _t2967 = U8_eq(_sw2959, _t2966);
                                                                    (void)_t2967;
                                                                    ;
                                                                    if (_t2967) {
                                                                        single = TokenType_clone(TokenType_Slash());
                                                                    } else {
                                                                        U8 _t2964 = 61;
                                                                        (void)_t2964;
                                                                        Bool _t2965 = U8_eq(_sw2959, _t2964);
                                                                        (void)_t2965;
                                                                        ;
                                                                        if (_t2965) {
                                                                            single = TokenType_clone(TokenType_Eq());
                                                                        } else {
                                                                            U8 _t2962 = 60;
                                                                            (void)_t2962;
                                                                            Bool _t2963 = U8_eq(_sw2959, _t2962);
                                                                            (void)_t2963;
                                                                            ;
                                                                            if (_t2963) {
                                                                                single = TokenType_clone(TokenType_Lt());
                                                                            } else {
                                                                                U8 _t2960 = 62;
                                                                                (void)_t2960;
                                                                                Bool _t2961 = U8_eq(_sw2959, _t2960);
                                                                                (void)_t2961;
                                                                                ;
                                                                                if (_t2961) {
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
        Bool _t3035; { Bool *_hp = (Bool *)TokenType_eq(single, TokenType_Eof()); _t3035 = *_hp; free(_hp); }
        (void)_t3035;
        Bool _t3036 = Bool_not(_t3035);
        (void)_t3036;
        ;
        if (_t3036) {
            U64 _t2996 = 1;
            (void)_t2996;
            Str *_t2997 = Str_substr(src, &(U64){start}, &(U64){_t2996});
            (void)_t2997;
            ;
            U32 _t2998 = U32_clone(&(U32){line});
            (void)_t2998;
            U32 _t2999 = U32_clone(&(U32){col});
            (void)_t2999;
            Token *_t3000 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(single); _t3000->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(_t2997); _t3000->text = *_ca; free(_ca); }
            _t3000->line = _t2998;
            _t3000->col = _t2999;
            (void)_t3000;
            Str_delete(_t2997, &(Bool){1});
            ;
            ;
            Vec_push(tokens, _t3000);
            U64_inc(pos);
            ;
            ;
            TokenType_delete(single, &(Bool){1});
            ;
            continue;
        }
        ;
        TokenType_delete(single, &(Bool){1});
        Str *_t3037 = Str_lit("Str", 3ULL);
        (void)_t3037;
        U64 _t3038; { U64 *_hp = (U64 *)Str_size(); _t3038 = *_hp; free(_hp); }
        (void)_t3038;
        U64 _t3039 = 6;
        (void)_t3039;
        Array *_va53 = Array_new(_t3037, &(U64){_t3038}, &(U64){_t3039});
        (void)_va53;
        Str_delete(_t3037, &(Bool){1});
        ;
        ;
        U64 _t3040 = 0;
        (void)_t3040;
        Str *_t3041 = Str_clone(path);
        (void)_t3041;
        Array_set(_va53, &(U64){_t3040}, _t3041);
        ;
        U64 _t3042 = 1;
        (void)_t3042;
        Str *_t3043 = Str_lit(":", 1ULL);
        (void)_t3043;
        Array_set(_va53, &(U64){_t3042}, _t3043);
        ;
        U64 _t3044 = 2;
        (void)_t3044;
        Str *_t3045 = U32_to_str(&(U32){line});
        (void)_t3045;
        Array_set(_va53, &(U64){_t3044}, _t3045);
        ;
        U64 _t3046 = 3;
        (void)_t3046;
        Str *_t3047 = Str_lit(":", 1ULL);
        (void)_t3047;
        Array_set(_va53, &(U64){_t3046}, _t3047);
        ;
        U64 _t3048 = 4;
        (void)_t3048;
        Str *_t3049 = U32_to_str(&(U32){col});
        (void)_t3049;
        Array_set(_va53, &(U64){_t3048}, _t3049);
        ;
        U64 _t3050 = 5;
        (void)_t3050;
        Str *_t3051 = Str_lit(": error: unexpected character", 29ULL);
        (void)_t3051;
        Array_set(_va53, &(U64){_t3050}, _t3051);
        ;
        println(_va53);
        U64 _t3052 = 1;
        (void)_t3052;
        Str *_t3053 = Str_substr(src, &(U64){start}, &(U64){_t3052});
        (void)_t3053;
        ;
        ;
        U32 _t3054 = U32_clone(&(U32){col});
        (void)_t3054;
        ;
        Token *_t3055 = malloc(sizeof(Token));
        { TokenType *_ca = TokenType_clone(TokenType_Error()); _t3055->type = *_ca; free(_ca); }
        { Str *_ca = Str_clone(_t3053); _t3055->text = *_ca; free(_ca); }
        _t3055->line = U32_clone(&(U32){line});
        _t3055->col = _t3054;
        (void)_t3055;
        Str_delete(_t3053, &(Bool){1});
        ;
        Vec_push(tokens, _t3055);
        U64_inc(pos);
    }
    ;
    U64 _t3058 = U64_sub(DEREF(pos), line_start);
    (void)_t3058;
    ;
    U64_delete(pos, &(Bool){1});
    U64 _t3059 = 1;
    (void)_t3059;
    U64 _t3060 = U64_add(_t3058, _t3059);
    (void)_t3060;
    ;
    ;
    I64 col = U64_to_i64(_t3060);
    (void)col;
    ;
    I64 _t3061 = I64_clone(&(I64){col});
    (void)_t3061;
    ;
    Token *_t3062 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(TokenType_Eof()); _t3062->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t3062->text = *_ca; free(_ca); }
    _t3062->line = U32_clone(&(U32){line});
    _t3062->col = _t3061;
    (void)_t3062;
    ;
    ;
    Vec_push(tokens, _t3062);
    return tokens;
}

