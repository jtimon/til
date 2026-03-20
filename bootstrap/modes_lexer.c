#include "modes_lexer.h"

Token * Token_clone(Token * self) {
    (void)self;
    U32 _t2387 = U32_clone(&self->line);
    (void)_t2387;
    U32 _t2388 = U32_clone(&self->col);
    (void)_t2388;
    Token *_t2389 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(&self->type); _t2389->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->text); _t2389->text = *_ca; free(_ca); }
    _t2389->line = _t2387;
    _t2389->col = _t2388;
    (void)_t2389;
    ;
    ;
    return _t2389;
}

void Token_delete(Token * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t2390 = 0;
    (void)_t2390;
    TokenType_delete(&self->type, &(Bool){_t2390});
    ;
    Bool _t2391 = 0;
    (void)_t2391;
    Str_delete(&self->text, &(Bool){_t2391});
    ;
    Bool _t2392 = 0;
    (void)_t2392;
    U32_delete(&self->line, &(Bool){_t2392});
    ;
    Bool _t2393 = 0;
    (void)_t2393;
    U32_delete(&self->col, &(Bool){_t2393});
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
    U8 _t2395 = 48;
    (void)_t2395;
    U8 _t2396 = 57;
    (void)_t2396;
    Bool _t2397; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t2395}); _t2397 = *_hp; free(_hp); }
    (void)_t2397;
    ;
    Bool _t2398; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t2396}); _t2398 = *_hp; free(_hp); }
    (void)_t2398;
    ;
    Bool _t2399 = Bool_and(_t2397, _t2398);
    (void)_t2399;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2399; return _r; }
}

Bool * is_alpha(U8 * c) {
    (void)c;
    U8 _t2400 = 97;
    (void)_t2400;
    U8 _t2401 = 122;
    (void)_t2401;
    Bool _t2402; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t2400}); _t2402 = *_hp; free(_hp); }
    (void)_t2402;
    ;
    Bool _t2403; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t2401}); _t2403 = *_hp; free(_hp); }
    (void)_t2403;
    ;
    U8 _t2404 = 65;
    (void)_t2404;
    U8 _t2405 = 90;
    (void)_t2405;
    Bool _t2406; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t2404}); _t2406 = *_hp; free(_hp); }
    (void)_t2406;
    ;
    Bool _t2407; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t2405}); _t2407 = *_hp; free(_hp); }
    (void)_t2407;
    ;
    Bool _t2408 = Bool_and(_t2402, _t2403);
    (void)_t2408;
    ;
    ;
    Bool _t2409 = Bool_and(_t2406, _t2407);
    (void)_t2409;
    ;
    ;
    U8 _t2410 = 95;
    (void)_t2410;
    Bool _t2411 = Bool_or(_t2408, _t2409);
    (void)_t2411;
    ;
    ;
    Bool _t2412 = U8_eq(DEREF(c), _t2410);
    (void)_t2412;
    ;
    Bool _t2413 = Bool_or(_t2411, _t2412);
    (void)_t2413;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2413; return _r; }
}

Bool * is_alnum(U8 * c) {
    (void)c;
    Bool _t2414; { Bool *_hp = (Bool *)is_alpha(c); _t2414 = *_hp; free(_hp); }
    (void)_t2414;
    Bool _t2415; { Bool *_hp = (Bool *)is_digit(c); _t2415 = *_hp; free(_hp); }
    (void)_t2415;
    Bool _t2416 = Bool_or(_t2414, _t2415);
    (void)_t2416;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2416; return _r; }
}

Str * tok_name(TokenType * type) {
    (void)type;
    {
        TokenType *_sw2417 = TokenType_clone(type);
        (void)_sw2417;
        Bool _t2550; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_Eof()); _t2550 = *_hp; free(_hp); }
        (void)_t2550;
        if (_t2550) {
            Str *_t2418 = Str_lit("eof", 3ULL);
            (void)_t2418;
            TokenType_delete(_sw2417, &(Bool){1});
            ;
            return _t2418;
        } else {
            Bool _t2549; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_LParen()); _t2549 = *_hp; free(_hp); }
            (void)_t2549;
            if (_t2549) {
                Str *_t2419 = Str_lit("(", 1ULL);
                (void)_t2419;
                ;
                TokenType_delete(_sw2417, &(Bool){1});
                ;
                return _t2419;
            } else {
                Bool _t2548; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_RParen()); _t2548 = *_hp; free(_hp); }
                (void)_t2548;
                if (_t2548) {
                    Str *_t2420 = Str_lit(")", 1ULL);
                    (void)_t2420;
                    ;
                    ;
                    TokenType_delete(_sw2417, &(Bool){1});
                    ;
                    return _t2420;
                } else {
                    Bool _t2547; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_LBrace()); _t2547 = *_hp; free(_hp); }
                    (void)_t2547;
                    if (_t2547) {
                        Str *_t2421 = Str_lit("{", 1ULL);
                        (void)_t2421;
                        ;
                        ;
                        ;
                        TokenType_delete(_sw2417, &(Bool){1});
                        ;
                        return _t2421;
                    } else {
                        Bool _t2546; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_RBrace()); _t2546 = *_hp; free(_hp); }
                        (void)_t2546;
                        if (_t2546) {
                            Str *_t2422 = Str_lit("}", 1ULL);
                            (void)_t2422;
                            ;
                            ;
                            ;
                            ;
                            TokenType_delete(_sw2417, &(Bool){1});
                            ;
                            return _t2422;
                        } else {
                            Bool _t2545; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_LBracket()); _t2545 = *_hp; free(_hp); }
                            (void)_t2545;
                            if (_t2545) {
                                Str *_t2423 = Str_lit("[", 1ULL);
                                (void)_t2423;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TokenType_delete(_sw2417, &(Bool){1});
                                ;
                                return _t2423;
                            } else {
                                Bool _t2544; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_RBracket()); _t2544 = *_hp; free(_hp); }
                                (void)_t2544;
                                if (_t2544) {
                                    Str *_t2424 = Str_lit("]", 1ULL);
                                    (void)_t2424;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TokenType_delete(_sw2417, &(Bool){1});
                                    ;
                                    return _t2424;
                                } else {
                                    Bool _t2543; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_Comma()); _t2543 = *_hp; free(_hp); }
                                    (void)_t2543;
                                    if (_t2543) {
                                        Str *_t2425 = Str_lit(",", 1ULL);
                                        (void)_t2425;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TokenType_delete(_sw2417, &(Bool){1});
                                        ;
                                        return _t2425;
                                    } else {
                                        Bool _t2542; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_Colon()); _t2542 = *_hp; free(_hp); }
                                        (void)_t2542;
                                        if (_t2542) {
                                            Str *_t2426 = Str_lit(":", 1ULL);
                                            (void)_t2426;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TokenType_delete(_sw2417, &(Bool){1});
                                            ;
                                            return _t2426;
                                        } else {
                                            Bool _t2541; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_Question()); _t2541 = *_hp; free(_hp); }
                                            (void)_t2541;
                                            if (_t2541) {
                                                Str *_t2427 = Str_lit("?", 1ULL);
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
                                                TokenType_delete(_sw2417, &(Bool){1});
                                                ;
                                                return _t2427;
                                            } else {
                                                Bool _t2540; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_Bang()); _t2540 = *_hp; free(_hp); }
                                                (void)_t2540;
                                                if (_t2540) {
                                                    Str *_t2428 = Str_lit("!", 1ULL);
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
                                                    TokenType_delete(_sw2417, &(Bool){1});
                                                    ;
                                                    return _t2428;
                                                } else {
                                                    Bool _t2539; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_Minus()); _t2539 = *_hp; free(_hp); }
                                                    (void)_t2539;
                                                    if (_t2539) {
                                                        Str *_t2429 = Str_lit("-", 1ULL);
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
                                                        TokenType_delete(_sw2417, &(Bool){1});
                                                        ;
                                                        return _t2429;
                                                    } else {
                                                        Bool _t2538; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_Plus()); _t2538 = *_hp; free(_hp); }
                                                        (void)_t2538;
                                                        if (_t2538) {
                                                            Str *_t2430 = Str_lit("+", 1ULL);
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
                                                            TokenType_delete(_sw2417, &(Bool){1});
                                                            ;
                                                            return _t2430;
                                                        } else {
                                                            Bool _t2537; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_Star()); _t2537 = *_hp; free(_hp); }
                                                            (void)_t2537;
                                                            if (_t2537) {
                                                                Str *_t2431 = Str_lit("*", 1ULL);
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
                                                                TokenType_delete(_sw2417, &(Bool){1});
                                                                ;
                                                                return _t2431;
                                                            } else {
                                                                Bool _t2536; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_Slash()); _t2536 = *_hp; free(_hp); }
                                                                (void)_t2536;
                                                                if (_t2536) {
                                                                    Str *_t2432 = Str_lit("/", 1ULL);
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
                                                                    TokenType_delete(_sw2417, &(Bool){1});
                                                                    ;
                                                                    return _t2432;
                                                                } else {
                                                                    Bool _t2535; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_Dot()); _t2535 = *_hp; free(_hp); }
                                                                    (void)_t2535;
                                                                    if (_t2535) {
                                                                        Str *_t2433 = Str_lit(".", 1ULL);
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
                                                                        TokenType_delete(_sw2417, &(Bool){1});
                                                                        ;
                                                                        return _t2433;
                                                                    } else {
                                                                        Bool _t2534; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_DotDot()); _t2534 = *_hp; free(_hp); }
                                                                        (void)_t2534;
                                                                        if (_t2534) {
                                                                            Str *_t2434 = Str_lit("..", 2ULL);
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
                                                                            TokenType_delete(_sw2417, &(Bool){1});
                                                                            ;
                                                                            return _t2434;
                                                                        } else {
                                                                            Bool _t2533; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_DotDotDot()); _t2533 = *_hp; free(_hp); }
                                                                            (void)_t2533;
                                                                            if (_t2533) {
                                                                                Str *_t2435 = Str_lit("...", 3ULL);
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
                                                                                TokenType_delete(_sw2417, &(Bool){1});
                                                                                ;
                                                                                return _t2435;
                                                                            } else {
                                                                                Bool _t2532; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_Eq()); _t2532 = *_hp; free(_hp); }
                                                                                (void)_t2532;
                                                                                if (_t2532) {
                                                                                    Str *_t2436 = Str_lit("=", 1ULL);
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
                                                                                    TokenType_delete(_sw2417, &(Bool){1});
                                                                                    ;
                                                                                    return _t2436;
                                                                                } else {
                                                                                    Bool _t2531; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_EqEq()); _t2531 = *_hp; free(_hp); }
                                                                                    (void)_t2531;
                                                                                    if (_t2531) {
                                                                                        Str *_t2437 = Str_lit("==", 2ULL);
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
                                                                                        TokenType_delete(_sw2417, &(Bool){1});
                                                                                        ;
                                                                                        return _t2437;
                                                                                    } else {
                                                                                        Bool _t2530; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_Neq()); _t2530 = *_hp; free(_hp); }
                                                                                        (void)_t2530;
                                                                                        if (_t2530) {
                                                                                            Str *_t2438 = Str_lit("!=", 2ULL);
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
                                                                                            TokenType_delete(_sw2417, &(Bool){1});
                                                                                            ;
                                                                                            return _t2438;
                                                                                        } else {
                                                                                            Bool _t2529; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_Lt()); _t2529 = *_hp; free(_hp); }
                                                                                            (void)_t2529;
                                                                                            if (_t2529) {
                                                                                                Str *_t2439 = Str_lit("<", 1ULL);
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
                                                                                                TokenType_delete(_sw2417, &(Bool){1});
                                                                                                ;
                                                                                                return _t2439;
                                                                                            } else {
                                                                                                Bool _t2528; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_LtEq()); _t2528 = *_hp; free(_hp); }
                                                                                                (void)_t2528;
                                                                                                if (_t2528) {
                                                                                                    Str *_t2440 = Str_lit("<=", 2ULL);
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
                                                                                                    TokenType_delete(_sw2417, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t2440;
                                                                                                } else {
                                                                                                    Bool _t2527; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_Gt()); _t2527 = *_hp; free(_hp); }
                                                                                                    (void)_t2527;
                                                                                                    if (_t2527) {
                                                                                                        Str *_t2441 = Str_lit(">", 1ULL);
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
                                                                                                        TokenType_delete(_sw2417, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t2441;
                                                                                                    } else {
                                                                                                        Bool _t2526; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_GtEq()); _t2526 = *_hp; free(_hp); }
                                                                                                        (void)_t2526;
                                                                                                        if (_t2526) {
                                                                                                            Str *_t2442 = Str_lit(">=", 2ULL);
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
                                                                                                            TokenType_delete(_sw2417, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t2442;
                                                                                                        } else {
                                                                                                            Bool _t2525; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_ColonEq()); _t2525 = *_hp; free(_hp); }
                                                                                                            (void)_t2525;
                                                                                                            if (_t2525) {
                                                                                                                Str *_t2443 = Str_lit(":=", 2ULL);
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
                                                                                                                TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                ;
                                                                                                                return _t2443;
                                                                                                            } else {
                                                                                                                Bool _t2524; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_Ident()); _t2524 = *_hp; free(_hp); }
                                                                                                                (void)_t2524;
                                                                                                                if (_t2524) {
                                                                                                                    Str *_t2444 = Str_lit("identifier", 10ULL);
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
                                                                                                                    TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return _t2444;
                                                                                                                } else {
                                                                                                                    Bool _t2523; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_StringTok()); _t2523 = *_hp; free(_hp); }
                                                                                                                    (void)_t2523;
                                                                                                                    if (_t2523) {
                                                                                                                        Str *_t2445 = Str_lit("string", 6ULL);
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
                                                                                                                        TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return _t2445;
                                                                                                                    } else {
                                                                                                                        Bool _t2522; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_Number()); _t2522 = *_hp; free(_hp); }
                                                                                                                        (void)_t2522;
                                                                                                                        if (_t2522) {
                                                                                                                            Str *_t2446 = Str_lit("number", 6ULL);
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
                                                                                                                            TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return _t2446;
                                                                                                                        } else {
                                                                                                                            Bool _t2521; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_Char()); _t2521 = *_hp; free(_hp); }
                                                                                                                            (void)_t2521;
                                                                                                                            if (_t2521) {
                                                                                                                                Str *_t2447 = Str_lit("char", 4ULL);
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
                                                                                                                                TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return _t2447;
                                                                                                                            } else {
                                                                                                                                Bool _t2520; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwMode()); _t2520 = *_hp; free(_hp); }
                                                                                                                                (void)_t2520;
                                                                                                                                if (_t2520) {
                                                                                                                                    Str *_t2448 = Str_lit("mode", 4ULL);
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
                                                                                                                                    TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return _t2448;
                                                                                                                                } else {
                                                                                                                                    Bool _t2519; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwMut()); _t2519 = *_hp; free(_hp); }
                                                                                                                                    (void)_t2519;
                                                                                                                                    if (_t2519) {
                                                                                                                                        Str *_t2449 = Str_lit("mut", 3ULL);
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
                                                                                                                                        TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return _t2449;
                                                                                                                                    } else {
                                                                                                                                        Bool _t2518; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwOwn()); _t2518 = *_hp; free(_hp); }
                                                                                                                                        (void)_t2518;
                                                                                                                                        if (_t2518) {
                                                                                                                                            Str *_t2450 = Str_lit("own", 3ULL);
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
                                                                                                                                            TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return _t2450;
                                                                                                                                        } else {
                                                                                                                                            Bool _t2517; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwRef()); _t2517 = *_hp; free(_hp); }
                                                                                                                                            (void)_t2517;
                                                                                                                                            if (_t2517) {
                                                                                                                                                Str *_t2451 = Str_lit("ref", 3ULL);
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
                                                                                                                                                TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return _t2451;
                                                                                                                                            } else {
                                                                                                                                                Bool _t2516; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwShallow()); _t2516 = *_hp; free(_hp); }
                                                                                                                                                (void)_t2516;
                                                                                                                                                if (_t2516) {
                                                                                                                                                    Str *_t2452 = Str_lit("shallow", 7ULL);
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
                                                                                                                                                    TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                    ;
                                                                                                                                                    return _t2452;
                                                                                                                                                } else {
                                                                                                                                                    Bool _t2515; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwStruct()); _t2515 = *_hp; free(_hp); }
                                                                                                                                                    (void)_t2515;
                                                                                                                                                    if (_t2515) {
                                                                                                                                                        Str *_t2453 = Str_lit("struct", 6ULL);
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
                                                                                                                                                        TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                        ;
                                                                                                                                                        return _t2453;
                                                                                                                                                    } else {
                                                                                                                                                        Bool _t2514; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwExtStruct()); _t2514 = *_hp; free(_hp); }
                                                                                                                                                        (void)_t2514;
                                                                                                                                                        if (_t2514) {
                                                                                                                                                            Str *_t2454 = Str_lit("ext_struct", 10ULL);
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
                                                                                                                                                            TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                            ;
                                                                                                                                                            return _t2454;
                                                                                                                                                        } else {
                                                                                                                                                            Bool _t2513; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwEnum()); _t2513 = *_hp; free(_hp); }
                                                                                                                                                            (void)_t2513;
                                                                                                                                                            if (_t2513) {
                                                                                                                                                                Str *_t2455 = Str_lit("enum", 4ULL);
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
                                                                                                                                                                TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                ;
                                                                                                                                                                return _t2455;
                                                                                                                                                            } else {
                                                                                                                                                                Bool _t2512; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwNamespace()); _t2512 = *_hp; free(_hp); }
                                                                                                                                                                (void)_t2512;
                                                                                                                                                                if (_t2512) {
                                                                                                                                                                    Str *_t2456 = Str_lit("namespace", 9ULL);
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
                                                                                                                                                                    TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                    ;
                                                                                                                                                                    return _t2456;
                                                                                                                                                                } else {
                                                                                                                                                                    Bool _t2511; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwFunc()); _t2511 = *_hp; free(_hp); }
                                                                                                                                                                    (void)_t2511;
                                                                                                                                                                    if (_t2511) {
                                                                                                                                                                        Str *_t2457 = Str_lit("func", 4ULL);
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
                                                                                                                                                                        TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                        ;
                                                                                                                                                                        return _t2457;
                                                                                                                                                                    } else {
                                                                                                                                                                        Bool _t2510; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwProc()); _t2510 = *_hp; free(_hp); }
                                                                                                                                                                        (void)_t2510;
                                                                                                                                                                        if (_t2510) {
                                                                                                                                                                            Str *_t2458 = Str_lit("proc", 4ULL);
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
                                                                                                                                                                            TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                            ;
                                                                                                                                                                            return _t2458;
                                                                                                                                                                        } else {
                                                                                                                                                                            Bool _t2509; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwTest()); _t2509 = *_hp; free(_hp); }
                                                                                                                                                                            (void)_t2509;
                                                                                                                                                                            if (_t2509) {
                                                                                                                                                                                Str *_t2459 = Str_lit("test", 4ULL);
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
                                                                                                                                                                                TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                ;
                                                                                                                                                                                return _t2459;
                                                                                                                                                                            } else {
                                                                                                                                                                                Bool _t2508; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwMacro()); _t2508 = *_hp; free(_hp); }
                                                                                                                                                                                (void)_t2508;
                                                                                                                                                                                if (_t2508) {
                                                                                                                                                                                    Str *_t2460 = Str_lit("macro", 5ULL);
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
                                                                                                                                                                                    TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                    ;
                                                                                                                                                                                    return _t2460;
                                                                                                                                                                                } else {
                                                                                                                                                                                    Bool _t2507; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwExtFunc()); _t2507 = *_hp; free(_hp); }
                                                                                                                                                                                    (void)_t2507;
                                                                                                                                                                                    if (_t2507) {
                                                                                                                                                                                        Str *_t2461 = Str_lit("ext_func", 8ULL);
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
                                                                                                                                                                                        TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                        ;
                                                                                                                                                                                        return _t2461;
                                                                                                                                                                                    } else {
                                                                                                                                                                                        Bool _t2506; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwExtProc()); _t2506 = *_hp; free(_hp); }
                                                                                                                                                                                        (void)_t2506;
                                                                                                                                                                                        if (_t2506) {
                                                                                                                                                                                            Str *_t2462 = Str_lit("ext_proc", 8ULL);
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
                                                                                                                                                                                            TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                            ;
                                                                                                                                                                                            return _t2462;
                                                                                                                                                                                        } else {
                                                                                                                                                                                            Bool _t2505; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwReturns()); _t2505 = *_hp; free(_hp); }
                                                                                                                                                                                            (void)_t2505;
                                                                                                                                                                                            if (_t2505) {
                                                                                                                                                                                                Str *_t2463 = Str_lit("returns", 7ULL);
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
                                                                                                                                                                                                TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                                ;
                                                                                                                                                                                                return _t2463;
                                                                                                                                                                                            } else {
                                                                                                                                                                                                Bool _t2504; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwThrows()); _t2504 = *_hp; free(_hp); }
                                                                                                                                                                                                (void)_t2504;
                                                                                                                                                                                                if (_t2504) {
                                                                                                                                                                                                    Str *_t2464 = Str_lit("throws", 6ULL);
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
                                                                                                                                                                                                    TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    return _t2464;
                                                                                                                                                                                                } else {
                                                                                                                                                                                                    Bool _t2503; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwIf()); _t2503 = *_hp; free(_hp); }
                                                                                                                                                                                                    (void)_t2503;
                                                                                                                                                                                                    if (_t2503) {
                                                                                                                                                                                                        Str *_t2465 = Str_lit("if", 2ULL);
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
                                                                                                                                                                                                        TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        return _t2465;
                                                                                                                                                                                                    } else {
                                                                                                                                                                                                        Bool _t2502; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwElse()); _t2502 = *_hp; free(_hp); }
                                                                                                                                                                                                        (void)_t2502;
                                                                                                                                                                                                        if (_t2502) {
                                                                                                                                                                                                            Str *_t2466 = Str_lit("else", 4ULL);
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
                                                                                                                                                                                                            TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            return _t2466;
                                                                                                                                                                                                        } else {
                                                                                                                                                                                                            Bool _t2501; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwWhile()); _t2501 = *_hp; free(_hp); }
                                                                                                                                                                                                            (void)_t2501;
                                                                                                                                                                                                            if (_t2501) {
                                                                                                                                                                                                                Str *_t2467 = Str_lit("while", 5ULL);
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
                                                                                                                                                                                                                TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                return _t2467;
                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                Bool _t2500; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwFor()); _t2500 = *_hp; free(_hp); }
                                                                                                                                                                                                                (void)_t2500;
                                                                                                                                                                                                                if (_t2500) {
                                                                                                                                                                                                                    Str *_t2468 = Str_lit("for", 3ULL);
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
                                                                                                                                                                                                                    TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    return _t2468;
                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                    Bool _t2499; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwIn()); _t2499 = *_hp; free(_hp); }
                                                                                                                                                                                                                    (void)_t2499;
                                                                                                                                                                                                                    if (_t2499) {
                                                                                                                                                                                                                        Str *_t2469 = Str_lit("in", 2ULL);
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
                                                                                                                                                                                                                        TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        return _t2469;
                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                        Bool _t2498; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwSwitch()); _t2498 = *_hp; free(_hp); }
                                                                                                                                                                                                                        (void)_t2498;
                                                                                                                                                                                                                        if (_t2498) {
                                                                                                                                                                                                                            Str *_t2470 = Str_lit("switch", 6ULL);
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
                                                                                                                                                                                                                            TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            return _t2470;
                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                            Bool _t2497; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwMatch()); _t2497 = *_hp; free(_hp); }
                                                                                                                                                                                                                            (void)_t2497;
                                                                                                                                                                                                                            if (_t2497) {
                                                                                                                                                                                                                                Str *_t2471 = Str_lit("match", 5ULL);
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
                                                                                                                                                                                                                                TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                return _t2471;
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                Bool _t2496; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwCase()); _t2496 = *_hp; free(_hp); }
                                                                                                                                                                                                                                (void)_t2496;
                                                                                                                                                                                                                                if (_t2496) {
                                                                                                                                                                                                                                    Str *_t2472 = Str_lit("case", 4ULL);
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
                                                                                                                                                                                                                                    TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    return _t2472;
                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                    Bool _t2495; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwDefault()); _t2495 = *_hp; free(_hp); }
                                                                                                                                                                                                                                    (void)_t2495;
                                                                                                                                                                                                                                    if (_t2495) {
                                                                                                                                                                                                                                        Str *_t2473 = Str_lit("default", 7ULL);
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
                                                                                                                                                                                                                                        TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        return _t2473;
                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                        Bool _t2494; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwReturn()); _t2494 = *_hp; free(_hp); }
                                                                                                                                                                                                                                        (void)_t2494;
                                                                                                                                                                                                                                        if (_t2494) {
                                                                                                                                                                                                                                            Str *_t2474 = Str_lit("return", 6ULL);
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
                                                                                                                                                                                                                                            TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            return _t2474;
                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                            Bool _t2493; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwThrow()); _t2493 = *_hp; free(_hp); }
                                                                                                                                                                                                                                            (void)_t2493;
                                                                                                                                                                                                                                            if (_t2493) {
                                                                                                                                                                                                                                                Str *_t2475 = Str_lit("throw", 5ULL);
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
                                                                                                                                                                                                                                                TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                return _t2475;
                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                Bool _t2492; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwCatch()); _t2492 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                (void)_t2492;
                                                                                                                                                                                                                                                if (_t2492) {
                                                                                                                                                                                                                                                    Str *_t2476 = Str_lit("catch", 5ULL);
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
                                                                                                                                                                                                                                                    TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    return _t2476;
                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                    Bool _t2491; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwBreak()); _t2491 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                    (void)_t2491;
                                                                                                                                                                                                                                                    if (_t2491) {
                                                                                                                                                                                                                                                        Str *_t2477 = Str_lit("break", 5ULL);
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
                                                                                                                                                                                                                                                        TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        return _t2477;
                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                        Bool _t2490; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwContinue()); _t2490 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                        (void)_t2490;
                                                                                                                                                                                                                                                        if (_t2490) {
                                                                                                                                                                                                                                                            Str *_t2478 = Str_lit("continue", 8ULL);
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
                                                                                                                                                                                                                                                            TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            return _t2478;
                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                            Bool _t2489; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwDefer()); _t2489 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                            (void)_t2489;
                                                                                                                                                                                                                                                            if (_t2489) {
                                                                                                                                                                                                                                                                Str *_t2479 = Str_lit("defer", 5ULL);
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
                                                                                                                                                                                                                                                                TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                return _t2479;
                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                Bool _t2488; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwTrue()); _t2488 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                (void)_t2488;
                                                                                                                                                                                                                                                                if (_t2488) {
                                                                                                                                                                                                                                                                    Str *_t2480 = Str_lit("true", 4ULL);
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
                                                                                                                                                                                                                                                                    TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t2480;
                                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                                    Bool _t2487; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwFalse()); _t2487 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                    (void)_t2487;
                                                                                                                                                                                                                                                                    if (_t2487) {
                                                                                                                                                                                                                                                                        Str *_t2481 = Str_lit("false", 5ULL);
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
                                                                                                                                                                                                                                                                        TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        return _t2481;
                                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                                        Bool _t2486; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_KwNull()); _t2486 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                        (void)_t2486;
                                                                                                                                                                                                                                                                        if (_t2486) {
                                                                                                                                                                                                                                                                            Str *_t2482 = Str_lit("NULL", 4ULL);
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
                                                                                                                                                                                                                                                                            TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            return _t2482;
                                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                                            Bool _t2485; { Bool *_hp = (Bool *)TokenType_eq(_sw2417, TokenType_Error()); _t2485 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                            (void)_t2485;
                                                                                                                                                                                                                                                                            if (_t2485) {
                                                                                                                                                                                                                                                                                Str *_t2483 = Str_lit("error", 5ULL);
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
                                                                                                                                                                                                                                                                                TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t2483;
                                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                                Str *_t2484 = Str_lit("?", 1ULL);
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
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                TokenType_delete(_sw2417, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t2484;
                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                        }
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                    }
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                }
                                                                                                                                                                                                                ;
                                                                                                                                                                                                            }
                                                                                                                                                                                                            ;
                                                                                                                                                                                                        }
                                                                                                                                                                                                        ;
                                                                                                                                                                                                    }
                                                                                                                                                                                                    ;
                                                                                                                                                                                                }
                                                                                                                                                                                                ;
                                                                                                                                                                                            }
                                                                                                                                                                                            ;
                                                                                                                                                                                        }
                                                                                                                                                                                        ;
                                                                                                                                                                                    }
                                                                                                                                                                                    ;
                                                                                                                                                                                }
                                                                                                                                                                                ;
                                                                                                                                                                            }
                                                                                                                                                                            ;
                                                                                                                                                                        }
                                                                                                                                                                        ;
                                                                                                                                                                    }
                                                                                                                                                                    ;
                                                                                                                                                                }
                                                                                                                                                                ;
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                        ;
                                                                                                                                                    }
                                                                                                                                                    ;
                                                                                                                                                }
                                                                                                                                                ;
                                                                                                                                            }
                                                                                                                                            ;
                                                                                                                                        }
                                                                                                                                        ;
                                                                                                                                    }
                                                                                                                                    ;
                                                                                                                                }
                                                                                                                                ;
                                                                                                                            }
                                                                                                                            ;
                                                                                                                        }
                                                                                                                        ;
                                                                                                                    }
                                                                                                                    ;
                                                                                                                }
                                                                                                                ;
                                                                                                            }
                                                                                                            ;
                                                                                                        }
                                                                                                        ;
                                                                                                    }
                                                                                                    ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                            ;
                                                                                        }
                                                                                        ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                                ;
                                                                            }
                                                                            ;
                                                                        }
                                                                        ;
                                                                    }
                                                                    ;
                                                                }
                                                                ;
                                                            }
                                                            ;
                                                        }
                                                        ;
                                                    }
                                                    ;
                                                }
                                                ;
                                            }
                                            ;
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        TokenType_delete(_sw2417, &(Bool){1});
        ;
    }
}

TokenType * lookup_keyword(Str * word) {
    (void)word;
    {
        Str *_sw2551 = Str_clone(word);
        (void)_sw2551;
        Str *_t2620 = Str_lit("mode", 4ULL);
        (void)_t2620;
        Bool _t2621; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2620); _t2621 = *_hp; free(_hp); }
        (void)_t2621;
        Str_delete(_t2620, &(Bool){1});
        if (_t2621) {
            Str_delete(_sw2551, &(Bool){1});
            ;
            return TokenType_KwMode();
        } else {
            Str *_t2618 = Str_lit("mut", 3ULL);
            (void)_t2618;
            Bool _t2619; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2618); _t2619 = *_hp; free(_hp); }
            (void)_t2619;
            Str_delete(_t2618, &(Bool){1});
            if (_t2619) {
                ;
                Str_delete(_sw2551, &(Bool){1});
                ;
                return TokenType_KwMut();
            } else {
                Str *_t2616 = Str_lit("own", 3ULL);
                (void)_t2616;
                Bool _t2617; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2616); _t2617 = *_hp; free(_hp); }
                (void)_t2617;
                Str_delete(_t2616, &(Bool){1});
                if (_t2617) {
                    ;
                    ;
                    Str_delete(_sw2551, &(Bool){1});
                    ;
                    return TokenType_KwOwn();
                } else {
                    Str *_t2614 = Str_lit("ref", 3ULL);
                    (void)_t2614;
                    Bool _t2615; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2614); _t2615 = *_hp; free(_hp); }
                    (void)_t2615;
                    Str_delete(_t2614, &(Bool){1});
                    if (_t2615) {
                        ;
                        ;
                        ;
                        Str_delete(_sw2551, &(Bool){1});
                        ;
                        return TokenType_KwRef();
                    } else {
                        Str *_t2612 = Str_lit("shallow", 7ULL);
                        (void)_t2612;
                        Bool _t2613; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2612); _t2613 = *_hp; free(_hp); }
                        (void)_t2613;
                        Str_delete(_t2612, &(Bool){1});
                        if (_t2613) {
                            ;
                            ;
                            ;
                            ;
                            Str_delete(_sw2551, &(Bool){1});
                            ;
                            return TokenType_KwShallow();
                        } else {
                            Str *_t2610 = Str_lit("struct", 6ULL);
                            (void)_t2610;
                            Bool _t2611; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2610); _t2611 = *_hp; free(_hp); }
                            (void)_t2611;
                            Str_delete(_t2610, &(Bool){1});
                            if (_t2611) {
                                ;
                                ;
                                ;
                                ;
                                ;
                                Str_delete(_sw2551, &(Bool){1});
                                ;
                                return TokenType_KwStruct();
                            } else {
                                Str *_t2608 = Str_lit("ext_struct", 10ULL);
                                (void)_t2608;
                                Bool _t2609; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2608); _t2609 = *_hp; free(_hp); }
                                (void)_t2609;
                                Str_delete(_t2608, &(Bool){1});
                                if (_t2609) {
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    Str_delete(_sw2551, &(Bool){1});
                                    ;
                                    return TokenType_KwExtStruct();
                                } else {
                                    Str *_t2606 = Str_lit("enum", 4ULL);
                                    (void)_t2606;
                                    Bool _t2607; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2606); _t2607 = *_hp; free(_hp); }
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
                                        Str_delete(_sw2551, &(Bool){1});
                                        ;
                                        return TokenType_KwEnum();
                                    } else {
                                        Str *_t2604 = Str_lit("namespace", 9ULL);
                                        (void)_t2604;
                                        Bool _t2605; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2604); _t2605 = *_hp; free(_hp); }
                                        (void)_t2605;
                                        Str_delete(_t2604, &(Bool){1});
                                        if (_t2605) {
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            Str_delete(_sw2551, &(Bool){1});
                                            ;
                                            return TokenType_KwNamespace();
                                        } else {
                                            Str *_t2602 = Str_lit("func", 4ULL);
                                            (void)_t2602;
                                            Bool _t2603; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2602); _t2603 = *_hp; free(_hp); }
                                            (void)_t2603;
                                            Str_delete(_t2602, &(Bool){1});
                                            if (_t2603) {
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                Str_delete(_sw2551, &(Bool){1});
                                                ;
                                                return TokenType_KwFunc();
                                            } else {
                                                Str *_t2600 = Str_lit("proc", 4ULL);
                                                (void)_t2600;
                                                Bool _t2601; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2600); _t2601 = *_hp; free(_hp); }
                                                (void)_t2601;
                                                Str_delete(_t2600, &(Bool){1});
                                                if (_t2601) {
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    Str_delete(_sw2551, &(Bool){1});
                                                    ;
                                                    return TokenType_KwProc();
                                                } else {
                                                    Str *_t2598 = Str_lit("test", 4ULL);
                                                    (void)_t2598;
                                                    Bool _t2599; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2598); _t2599 = *_hp; free(_hp); }
                                                    (void)_t2599;
                                                    Str_delete(_t2598, &(Bool){1});
                                                    if (_t2599) {
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        Str_delete(_sw2551, &(Bool){1});
                                                        ;
                                                        return TokenType_KwTest();
                                                    } else {
                                                        Str *_t2596 = Str_lit("macro", 5ULL);
                                                        (void)_t2596;
                                                        Bool _t2597; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2596); _t2597 = *_hp; free(_hp); }
                                                        (void)_t2597;
                                                        Str_delete(_t2596, &(Bool){1});
                                                        if (_t2597) {
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            Str_delete(_sw2551, &(Bool){1});
                                                            ;
                                                            return TokenType_KwMacro();
                                                        } else {
                                                            Str *_t2594 = Str_lit("ext_func", 8ULL);
                                                            (void)_t2594;
                                                            Bool _t2595; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2594); _t2595 = *_hp; free(_hp); }
                                                            (void)_t2595;
                                                            Str_delete(_t2594, &(Bool){1});
                                                            if (_t2595) {
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                Str_delete(_sw2551, &(Bool){1});
                                                                ;
                                                                return TokenType_KwExtFunc();
                                                            } else {
                                                                Str *_t2592 = Str_lit("ext_proc", 8ULL);
                                                                (void)_t2592;
                                                                Bool _t2593; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2592); _t2593 = *_hp; free(_hp); }
                                                                (void)_t2593;
                                                                Str_delete(_t2592, &(Bool){1});
                                                                if (_t2593) {
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    Str_delete(_sw2551, &(Bool){1});
                                                                    ;
                                                                    return TokenType_KwExtProc();
                                                                } else {
                                                                    Str *_t2590 = Str_lit("returns", 7ULL);
                                                                    (void)_t2590;
                                                                    Bool _t2591; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2590); _t2591 = *_hp; free(_hp); }
                                                                    (void)_t2591;
                                                                    Str_delete(_t2590, &(Bool){1});
                                                                    if (_t2591) {
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        Str_delete(_sw2551, &(Bool){1});
                                                                        ;
                                                                        return TokenType_KwReturns();
                                                                    } else {
                                                                        Str *_t2588 = Str_lit("throws", 6ULL);
                                                                        (void)_t2588;
                                                                        Bool _t2589; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2588); _t2589 = *_hp; free(_hp); }
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
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            Str_delete(_sw2551, &(Bool){1});
                                                                            ;
                                                                            return TokenType_KwThrows();
                                                                        } else {
                                                                            Str *_t2586 = Str_lit("if", 2ULL);
                                                                            (void)_t2586;
                                                                            Bool _t2587; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2586); _t2587 = *_hp; free(_hp); }
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
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                Str_delete(_sw2551, &(Bool){1});
                                                                                ;
                                                                                return TokenType_KwIf();
                                                                            } else {
                                                                                Str *_t2584 = Str_lit("else", 4ULL);
                                                                                (void)_t2584;
                                                                                Bool _t2585; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2584); _t2585 = *_hp; free(_hp); }
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
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    Str_delete(_sw2551, &(Bool){1});
                                                                                    ;
                                                                                    return TokenType_KwElse();
                                                                                } else {
                                                                                    Str *_t2582 = Str_lit("while", 5ULL);
                                                                                    (void)_t2582;
                                                                                    Bool _t2583; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2582); _t2583 = *_hp; free(_hp); }
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
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        Str_delete(_sw2551, &(Bool){1});
                                                                                        ;
                                                                                        return TokenType_KwWhile();
                                                                                    } else {
                                                                                        Str *_t2580 = Str_lit("for", 3ULL);
                                                                                        (void)_t2580;
                                                                                        Bool _t2581; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2580); _t2581 = *_hp; free(_hp); }
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
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            Str_delete(_sw2551, &(Bool){1});
                                                                                            ;
                                                                                            return TokenType_KwFor();
                                                                                        } else {
                                                                                            Str *_t2578 = Str_lit("in", 2ULL);
                                                                                            (void)_t2578;
                                                                                            Bool _t2579; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2578); _t2579 = *_hp; free(_hp); }
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
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                Str_delete(_sw2551, &(Bool){1});
                                                                                                ;
                                                                                                return TokenType_KwIn();
                                                                                            } else {
                                                                                                Str *_t2576 = Str_lit("switch", 6ULL);
                                                                                                (void)_t2576;
                                                                                                Bool _t2577; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2576); _t2577 = *_hp; free(_hp); }
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
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    Str_delete(_sw2551, &(Bool){1});
                                                                                                    ;
                                                                                                    return TokenType_KwSwitch();
                                                                                                } else {
                                                                                                    Str *_t2574 = Str_lit("match", 5ULL);
                                                                                                    (void)_t2574;
                                                                                                    Bool _t2575; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2574); _t2575 = *_hp; free(_hp); }
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
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        Str_delete(_sw2551, &(Bool){1});
                                                                                                        ;
                                                                                                        return TokenType_KwMatch();
                                                                                                    } else {
                                                                                                        Str *_t2572 = Str_lit("case", 4ULL);
                                                                                                        (void)_t2572;
                                                                                                        Bool _t2573; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2572); _t2573 = *_hp; free(_hp); }
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
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            Str_delete(_sw2551, &(Bool){1});
                                                                                                            ;
                                                                                                            return TokenType_KwCase();
                                                                                                        } else {
                                                                                                            Str *_t2570 = Str_lit("default", 7ULL);
                                                                                                            (void)_t2570;
                                                                                                            Bool _t2571; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2570); _t2571 = *_hp; free(_hp); }
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
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                Str_delete(_sw2551, &(Bool){1});
                                                                                                                ;
                                                                                                                return TokenType_KwDefault();
                                                                                                            } else {
                                                                                                                Str *_t2568 = Str_lit("return", 6ULL);
                                                                                                                (void)_t2568;
                                                                                                                Bool _t2569; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2568); _t2569 = *_hp; free(_hp); }
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
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    Str_delete(_sw2551, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return TokenType_KwReturn();
                                                                                                                } else {
                                                                                                                    Str *_t2566 = Str_lit("throw", 5ULL);
                                                                                                                    (void)_t2566;
                                                                                                                    Bool _t2567; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2566); _t2567 = *_hp; free(_hp); }
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
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        Str_delete(_sw2551, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return TokenType_KwThrow();
                                                                                                                    } else {
                                                                                                                        Str *_t2564 = Str_lit("catch", 5ULL);
                                                                                                                        (void)_t2564;
                                                                                                                        Bool _t2565; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2564); _t2565 = *_hp; free(_hp); }
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
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            Str_delete(_sw2551, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return TokenType_KwCatch();
                                                                                                                        } else {
                                                                                                                            Str *_t2562 = Str_lit("break", 5ULL);
                                                                                                                            (void)_t2562;
                                                                                                                            Bool _t2563; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2562); _t2563 = *_hp; free(_hp); }
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
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                Str_delete(_sw2551, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return TokenType_KwBreak();
                                                                                                                            } else {
                                                                                                                                Str *_t2560 = Str_lit("continue", 8ULL);
                                                                                                                                (void)_t2560;
                                                                                                                                Bool _t2561; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2560); _t2561 = *_hp; free(_hp); }
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
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    Str_delete(_sw2551, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return TokenType_KwContinue();
                                                                                                                                } else {
                                                                                                                                    Str *_t2558 = Str_lit("defer", 5ULL);
                                                                                                                                    (void)_t2558;
                                                                                                                                    Bool _t2559; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2558); _t2559 = *_hp; free(_hp); }
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
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        Str_delete(_sw2551, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return TokenType_KwDefer();
                                                                                                                                    } else {
                                                                                                                                        Str *_t2556 = Str_lit("true", 4ULL);
                                                                                                                                        (void)_t2556;
                                                                                                                                        Bool _t2557; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2556); _t2557 = *_hp; free(_hp); }
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
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            Str_delete(_sw2551, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return TokenType_KwTrue();
                                                                                                                                        } else {
                                                                                                                                            Str *_t2554 = Str_lit("false", 5ULL);
                                                                                                                                            (void)_t2554;
                                                                                                                                            Bool _t2555; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2554); _t2555 = *_hp; free(_hp); }
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
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                Str_delete(_sw2551, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return TokenType_KwFalse();
                                                                                                                                            } else {
                                                                                                                                                Str *_t2552 = Str_lit("NULL", 4ULL);
                                                                                                                                                (void)_t2552;
                                                                                                                                                Bool _t2553; { Bool *_hp = (Bool *)Str_eq(_sw2551, _t2552); _t2553 = *_hp; free(_hp); }
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
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    Str_delete(_sw2551, &(Bool){1});
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
                                                                                                                                                    Str_delete(_sw2551, &(Bool){1});
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
        Str_delete(_sw2551, &(Bool){1});
        ;
    }
}

Vec * tokenize(Str * src, Str * path) {
    (void)src;
    (void)path;
    Str *_t2961 = Str_lit("Token", 5ULL);
    (void)_t2961;
    U64 _t2962; { U64 *_hp = (U64 *)Token_size(); _t2962 = *_hp; free(_hp); }
    (void)_t2962;
    Vec *tokens = Vec_new(_t2961, &(U64){_t2962});
    (void)tokens;
    Str_delete(_t2961, &(Bool){1});
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
        Bool _wcond2622; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2622 = *_hp; free(_hp); }
        (void)_wcond2622;
        if (_wcond2622) {
        } else {
            ;
            break;
        }
        ;
        U8 *c = Str_byte_at(src, pos);
        (void)c;
        U8 _t2906 = 32;
        (void)_t2906;
        U8 _t2907 = 9;
        (void)_t2907;
        Bool _t2908 = U8_eq(DEREF(c), _t2906);
        (void)_t2908;
        ;
        Bool _t2909 = U8_eq(DEREF(c), _t2907);
        (void)_t2909;
        ;
        U8 _t2910 = 13;
        (void)_t2910;
        Bool _t2911 = Bool_or(_t2908, _t2909);
        (void)_t2911;
        ;
        ;
        Bool _t2912 = U8_eq(DEREF(c), _t2910);
        (void)_t2912;
        ;
        U8 _t2913 = 59;
        (void)_t2913;
        Bool _t2914 = Bool_or(_t2911, _t2912);
        (void)_t2914;
        ;
        ;
        Bool _t2915 = U8_eq(DEREF(c), _t2913);
        (void)_t2915;
        ;
        Bool _t2916 = Bool_or(_t2914, _t2915);
        (void)_t2916;
        ;
        ;
        if (_t2916) {
            U64_inc(pos);
            ;
            continue;
        }
        ;
        U8 _t2917 = 10;
        (void)_t2917;
        Bool _t2918 = U8_eq(DEREF(c), _t2917);
        (void)_t2918;
        ;
        if (_t2918) {
            U64_inc(pos);
            U32 _t2623 = 1;
            (void)_t2623;
            U32 _t2624 = U32_add(line, _t2623);
            (void)_t2624;
            ;
            line = _t2624;
            ;
            U64 _t2625 = U64_clone(pos);
            (void)_t2625;
            line_start = _t2625;
            ;
            ;
            continue;
        }
        ;
        U64 _t2919 = U64_sub(DEREF(pos), line_start);
        (void)_t2919;
        U64 _t2920 = 1;
        (void)_t2920;
        U64 _t2921 = U64_add(_t2919, _t2920);
        (void)_t2921;
        ;
        ;
        I64 _t2922 = U64_to_i64(_t2921);
        (void)_t2922;
        ;
        U32 col = I64_to_u32(_t2922);
        (void)col;
        ;
        U64 start = U64_clone(pos);
        (void)start;
        U8 _t2923 = 35;
        (void)_t2923;
        Bool _t2924 = U8_eq(DEREF(c), _t2923);
        (void)_t2924;
        ;
        if (_t2924) {
            while (1) {
                Bool _wcond2626; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2626 = *_hp; free(_hp); }
                (void)_wcond2626;
                if (_wcond2626) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2627 = Str_byte_at(src, pos);
                (void)_t2627;
                U8 _t2628 = 10;
                (void)_t2628;
                Bool _t2629 = U8_eq(DEREF(_t2627), _t2628);
                (void)_t2629;
                ;
                if (_t2629) {
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
        U8 _t2925 = 47;
        (void)_t2925;
        U64 _t2926 = 1;
        (void)_t2926;
        U64 _t2927 = U64_add(DEREF(pos), _t2926);
        (void)_t2927;
        ;
        Bool _t2928 = U8_eq(DEREF(c), _t2925);
        (void)_t2928;
        ;
        Bool _t2929; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2927}, &(U64){src_len}); _t2929 = *_hp; free(_hp); }
        (void)_t2929;
        ;
        Bool _t2930 = Bool_and(_t2928, _t2929);
        (void)_t2930;
        ;
        ;
        if (_t2930) {
            U64 _t2686 = 1;
            (void)_t2686;
            U64 *_t2687 = malloc(sizeof(U64)); *_t2687 = U64_add(DEREF(pos), _t2686);
            (void)_t2687;
            ;
            U8 *c2 = Str_byte_at(src, _t2687);
            (void)c2;
            U8 _t2688 = 47;
            (void)_t2688;
            Bool _t2689 = U8_eq(DEREF(c2), _t2688);
            (void)_t2689;
            ;
            if (_t2689) {
                while (1) {
                    Bool _wcond2630; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2630 = *_hp; free(_hp); }
                    (void)_wcond2630;
                    if (_wcond2630) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U8 *_t2631 = Str_byte_at(src, pos);
                    (void)_t2631;
                    U8 _t2632 = 10;
                    (void)_t2632;
                    Bool _t2633 = U8_eq(DEREF(_t2631), _t2632);
                    (void)_t2633;
                    ;
                    if (_t2633) {
                        ;
                        break;
                    }
                    ;
                    U64_inc(pos);
                }
                U64_delete(_t2687, &(Bool){1});
                ;
                ;
                ;
                ;
                continue;
            }
            ;
            U8 _t2690 = 42;
            (void)_t2690;
            Bool _t2691 = U8_eq(DEREF(c2), _t2690);
            (void)_t2691;
            U64_delete(_t2687, &(Bool){1});
            ;
            if (_t2691) {
                U64 _t2682 = 2;
                (void)_t2682;
                U64 _t2683 = U64_add(DEREF(pos), _t2682);
                (void)_t2683;
                ;
                *pos = _t2683;
                ;
                I64 depth = 1;
                (void)depth;
                while (1) {
                    Bool _wcond2634; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2634 = *_hp; free(_hp); }
                    (void)_wcond2634;
                    if (_wcond2634) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    I64 _t2659 = 0;
                    (void)_t2659;
                    Bool _t2660; { Bool *_hp = (Bool *)I64_lte(&(I64){depth}, &(I64){_t2659}); _t2660 = *_hp; free(_hp); }
                    (void)_t2660;
                    ;
                    if (_t2660) {
                        ;
                        break;
                    }
                    ;
                    U64 _t2661 = 1;
                    (void)_t2661;
                    U64 _t2662 = U64_add(DEREF(pos), _t2661);
                    (void)_t2662;
                    ;
                    Bool _t2663; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2662}, &(U64){src_len}); _t2663 = *_hp; free(_hp); }
                    (void)_t2663;
                    ;
                    if (_t2663) {
                        U8 *b1 = Str_byte_at(src, pos);
                        (void)b1;
                        U64 _t2643 = 1;
                        (void)_t2643;
                        U64 *_t2644 = malloc(sizeof(U64)); *_t2644 = U64_add(DEREF(pos), _t2643);
                        (void)_t2644;
                        ;
                        U8 *b2 = Str_byte_at(src, _t2644);
                        (void)b2;
                        U8 _t2645 = 47;
                        (void)_t2645;
                        U8 _t2646 = 42;
                        (void)_t2646;
                        Bool _t2647 = U8_eq(DEREF(b1), _t2645);
                        (void)_t2647;
                        ;
                        Bool _t2648 = U8_eq(DEREF(b2), _t2646);
                        (void)_t2648;
                        ;
                        Bool _t2649 = Bool_and(_t2647, _t2648);
                        (void)_t2649;
                        ;
                        ;
                        if (_t2649) {
                            I64 _t2635 = 1;
                            (void)_t2635;
                            I64 _t2636 = I64_add(depth, _t2635);
                            (void)_t2636;
                            ;
                            depth = _t2636;
                            ;
                            U64 _t2637 = 2;
                            (void)_t2637;
                            U64 _t2638 = U64_add(DEREF(pos), _t2637);
                            (void)_t2638;
                            ;
                            *pos = _t2638;
                            ;
                            U64_delete(_t2644, &(Bool){1});
                            ;
                            ;
                            continue;
                        }
                        ;
                        U8 _t2650 = 42;
                        (void)_t2650;
                        U8 _t2651 = 47;
                        (void)_t2651;
                        Bool _t2652 = U8_eq(DEREF(b1), _t2650);
                        (void)_t2652;
                        ;
                        Bool _t2653 = U8_eq(DEREF(b2), _t2651);
                        (void)_t2653;
                        U64_delete(_t2644, &(Bool){1});
                        ;
                        Bool _t2654 = Bool_and(_t2652, _t2653);
                        (void)_t2654;
                        ;
                        ;
                        if (_t2654) {
                            I64 _t2639 = 1;
                            (void)_t2639;
                            I64 _t2640 = I64_sub(depth, _t2639);
                            (void)_t2640;
                            ;
                            depth = _t2640;
                            ;
                            U64 _t2641 = 2;
                            (void)_t2641;
                            U64 _t2642 = U64_add(DEREF(pos), _t2641);
                            (void)_t2642;
                            ;
                            *pos = _t2642;
                            ;
                            ;
                            ;
                            continue;
                        }
                        ;
                    }
                    ;
                    U8 *_t2664 = Str_byte_at(src, pos);
                    (void)_t2664;
                    U8 _t2665 = 10;
                    (void)_t2665;
                    Bool _t2666 = U8_eq(DEREF(_t2664), _t2665);
                    (void)_t2666;
                    ;
                    if (_t2666) {
                        U32 _t2655 = 1;
                        (void)_t2655;
                        U32 _t2656 = U32_add(line, _t2655);
                        (void)_t2656;
                        ;
                        line = _t2656;
                        ;
                        U64 _t2657 = 1;
                        (void)_t2657;
                        U64 _t2658 = U64_add(DEREF(pos), _t2657);
                        (void)_t2658;
                        ;
                        line_start = _t2658;
                        ;
                    }
                    ;
                    U64_inc(pos);
                }
                I64 _t2684 = 0;
                (void)_t2684;
                Bool _t2685; { Bool *_hp = (Bool *)I64_gt(&(I64){depth}, &(I64){_t2684}); _t2685 = *_hp; free(_hp); }
                (void)_t2685;
                ;
                ;
                if (_t2685) {
                    Str *_t2667 = Str_lit("Str", 3ULL);
                    (void)_t2667;
                    U64 _t2668; { U64 *_hp = (U64 *)Str_size(); _t2668 = *_hp; free(_hp); }
                    (void)_t2668;
                    U64 _t2669 = 6;
                    (void)_t2669;
                    Array *_va53 = Array_new(_t2667, &(U64){_t2668}, &(U64){_t2669});
                    (void)_va53;
                    Str_delete(_t2667, &(Bool){1});
                    ;
                    ;
                    U64 _t2670 = 0;
                    (void)_t2670;
                    Str *_t2671 = Str_clone(path);
                    (void)_t2671;
                    Array_set(_va53, &(U64){_t2670}, _t2671);
                    ;
                    U64 _t2672 = 1;
                    (void)_t2672;
                    Str *_t2673 = Str_lit(":", 1ULL);
                    (void)_t2673;
                    Array_set(_va53, &(U64){_t2672}, _t2673);
                    ;
                    U64 _t2674 = 2;
                    (void)_t2674;
                    Str *_t2675 = U32_to_str(&(U32){line});
                    (void)_t2675;
                    Array_set(_va53, &(U64){_t2674}, _t2675);
                    ;
                    U64 _t2676 = 3;
                    (void)_t2676;
                    Str *_t2677 = Str_lit(":", 1ULL);
                    (void)_t2677;
                    Array_set(_va53, &(U64){_t2676}, _t2677);
                    ;
                    U64 _t2678 = 4;
                    (void)_t2678;
                    Str *_t2679 = U32_to_str(&(U32){col});
                    (void)_t2679;
                    Array_set(_va53, &(U64){_t2678}, _t2679);
                    ;
                    U64 _t2680 = 5;
                    (void)_t2680;
                    Str *_t2681 = Str_lit(": error: unterminated comment", 29ULL);
                    (void)_t2681;
                    Array_set(_va53, &(U64){_t2680}, _t2681);
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
        Bool _t2931; { Bool *_hp = (Bool *)is_digit(c); _t2931 = *_hp; free(_hp); }
        (void)_t2931;
        if (_t2931) {
            while (1) {
                Bool _wcond2692; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2692 = *_hp; free(_hp); }
                (void)_wcond2692;
                if (_wcond2692) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2693 = Str_byte_at(src, pos);
                (void)_t2693;
                Bool _t2694; { Bool *_hp = (Bool *)is_digit(_t2693); _t2694 = *_hp; free(_hp); }
                (void)_t2694;
                Bool _t2695 = Bool_not(_t2694);
                (void)_t2695;
                ;
                if (_t2695) {
                    ;
                    break;
                }
                ;
                U64_inc(pos);
            }
            U64 _t2708 = 1;
            (void)_t2708;
            U64 _t2709 = U64_add(DEREF(pos), _t2708);
            (void)_t2709;
            ;
            Bool _t2710; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2709}, &(U64){src_len}); _t2710 = *_hp; free(_hp); }
            (void)_t2710;
            ;
            if (_t2710) {
                U8 *_t2700 = Str_byte_at(src, pos);
                (void)_t2700;
                U8 _t2701 = 46;
                (void)_t2701;
                U64 _t2702 = 1;
                (void)_t2702;
                U64 *_t2703 = malloc(sizeof(U64)); *_t2703 = U64_add(DEREF(pos), _t2702);
                (void)_t2703;
                ;
                U8 *_t2704 = Str_byte_at(src, _t2703);
                (void)_t2704;
                Bool _t2705 = U8_eq(DEREF(_t2700), _t2701);
                (void)_t2705;
                ;
                Bool _t2706; { Bool *_hp = (Bool *)is_digit(_t2704); _t2706 = *_hp; free(_hp); }
                (void)_t2706;
                U64_delete(_t2703, &(Bool){1});
                Bool _t2707 = Bool_and(_t2705, _t2706);
                (void)_t2707;
                ;
                ;
                if (_t2707) {
                    U64_inc(pos);
                    while (1) {
                        Bool _wcond2696; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2696 = *_hp; free(_hp); }
                        (void)_wcond2696;
                        if (_wcond2696) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U8 *_t2697 = Str_byte_at(src, pos);
                        (void)_t2697;
                        Bool _t2698; { Bool *_hp = (Bool *)is_digit(_t2697); _t2698 = *_hp; free(_hp); }
                        (void)_t2698;
                        Bool _t2699 = Bool_not(_t2698);
                        (void)_t2699;
                        ;
                        if (_t2699) {
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
            U64 _t2711 = U64_sub(DEREF(pos), start);
            (void)_t2711;
            Str *_t2712 = Str_substr(src, &(U64){start}, &(U64){_t2711});
            (void)_t2712;
            ;
            U32 _t2713 = U32_clone(&(U32){col});
            (void)_t2713;
            Token *_t2714 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(TokenType_Number()); _t2714->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(_t2712); _t2714->text = *_ca; free(_ca); }
            _t2714->line = U32_clone(&(U32){line});
            _t2714->col = _t2713;
            (void)_t2714;
            Str_delete(_t2712, &(Bool){1});
            ;
            Vec_push(tokens, _t2714);
            ;
            ;
            ;
            continue;
        }
        ;
        Bool _t2932; { Bool *_hp = (Bool *)is_alpha(c); _t2932 = *_hp; free(_hp); }
        (void)_t2932;
        if (_t2932) {
            while (1) {
                Bool _wcond2715; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2715 = *_hp; free(_hp); }
                (void)_wcond2715;
                if (_wcond2715) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2716 = Str_byte_at(src, pos);
                (void)_t2716;
                Bool _t2717; { Bool *_hp = (Bool *)is_alnum(_t2716); _t2717 = *_hp; free(_hp); }
                (void)_t2717;
                Bool _t2718 = Bool_not(_t2717);
                (void)_t2718;
                ;
                if (_t2718) {
                    ;
                    break;
                }
                ;
                U64_inc(pos);
            }
            U64 _t2719 = U64_sub(DEREF(pos), start);
            (void)_t2719;
            Str *word = Str_substr(src, &(U64){start}, &(U64){_t2719});
            (void)word;
            ;
            TokenType *type = lookup_keyword(word);
            (void)type;
            U32 _t2720 = U32_clone(&(U32){line});
            (void)_t2720;
            U32 _t2721 = U32_clone(&(U32){col});
            (void)_t2721;
            Token *_t2722 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(type); _t2722->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(word); _t2722->text = *_ca; free(_ca); }
            _t2722->line = _t2720;
            _t2722->col = _t2721;
            (void)_t2722;
            ;
            ;
            TokenType_delete(type, &(Bool){1});
            Str_delete(word, &(Bool){1});
            Vec_push(tokens, _t2722);
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t2933 = 34;
        (void)_t2933;
        Bool _t2934 = U8_eq(DEREF(c), _t2933);
        (void)_t2934;
        ;
        if (_t2934) {
            U64_inc(pos);
            while (1) {
                Bool _wcond2723; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond2723 = *_hp; free(_hp); }
                (void)_wcond2723;
                if (_wcond2723) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t2728 = Str_byte_at(src, pos);
                (void)_t2728;
                U8 _t2729 = 34;
                (void)_t2729;
                Bool _t2730 = U8_eq(DEREF(_t2728), _t2729);
                (void)_t2730;
                ;
                if (_t2730) {
                    ;
                    break;
                }
                ;
                U8 *_t2731 = Str_byte_at(src, pos);
                (void)_t2731;
                U8 _t2732 = 92;
                (void)_t2732;
                U64 _t2733 = 1;
                (void)_t2733;
                U64 _t2734 = U64_add(DEREF(pos), _t2733);
                (void)_t2734;
                ;
                Bool _t2735 = U8_eq(DEREF(_t2731), _t2732);
                (void)_t2735;
                ;
                Bool _t2736; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2734}, &(U64){src_len}); _t2736 = *_hp; free(_hp); }
                (void)_t2736;
                ;
                Bool _t2737 = Bool_and(_t2735, _t2736);
                (void)_t2737;
                ;
                ;
                if (_t2737) {
                    U64_inc(pos);
                }
                ;
                U8 *_t2738 = Str_byte_at(src, pos);
                (void)_t2738;
                U8 _t2739 = 10;
                (void)_t2739;
                Bool _t2740 = U8_eq(DEREF(_t2738), _t2739);
                (void)_t2740;
                ;
                if (_t2740) {
                    U32 _t2724 = 1;
                    (void)_t2724;
                    U32 _t2725 = U32_add(line, _t2724);
                    (void)_t2725;
                    ;
                    line = _t2725;
                    ;
                    U64 _t2726 = 1;
                    (void)_t2726;
                    U64 _t2727 = U64_add(DEREF(pos), _t2726);
                    (void)_t2727;
                    ;
                    line_start = _t2727;
                    ;
                }
                ;
                U64_inc(pos);
            }
            U8 *_t2768 = Str_byte_at(src, pos);
            (void)_t2768;
            U8 _t2769 = 34;
            (void)_t2769;
            Bool _t2770; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2770 = *_hp; free(_hp); }
            (void)_t2770;
            Bool _t2771 = U8_eq(DEREF(_t2768), _t2769);
            (void)_t2771;
            ;
            Bool _t2772 = Bool_and(_t2770, _t2771);
            (void)_t2772;
            ;
            ;
            if (_t2772) {
                U64_inc(pos);
                U64 _t2741 = 1;
                (void)_t2741;
                U64 _t2742 = U64_sub(DEREF(pos), start);
                (void)_t2742;
                U64 _t2743 = 2;
                (void)_t2743;
                U64 _t2744 = U64_add(start, _t2741);
                (void)_t2744;
                ;
                U64 _t2745 = U64_sub(_t2742, _t2743);
                (void)_t2745;
                ;
                ;
                Str *_t2746 = Str_substr(src, &(U64){_t2744}, &(U64){_t2745});
                (void)_t2746;
                ;
                ;
                U32 _t2747 = U32_clone(&(U32){col});
                (void)_t2747;
                Token *_t2748 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_StringTok()); _t2748->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2746); _t2748->text = *_ca; free(_ca); }
                _t2748->line = U32_clone(&(U32){line});
                _t2748->col = _t2747;
                (void)_t2748;
                Str_delete(_t2746, &(Bool){1});
                ;
                Vec_push(tokens, _t2748);
            } else {
                Str *_t2749 = Str_lit("Str", 3ULL);
                (void)_t2749;
                U64 _t2750; { U64 *_hp = (U64 *)Str_size(); _t2750 = *_hp; free(_hp); }
                (void)_t2750;
                U64 _t2751 = 6;
                (void)_t2751;
                Array *_va54 = Array_new(_t2749, &(U64){_t2750}, &(U64){_t2751});
                (void)_va54;
                Str_delete(_t2749, &(Bool){1});
                ;
                ;
                U64 _t2752 = 0;
                (void)_t2752;
                Str *_t2753 = Str_clone(path);
                (void)_t2753;
                Array_set(_va54, &(U64){_t2752}, _t2753);
                ;
                U64 _t2754 = 1;
                (void)_t2754;
                Str *_t2755 = Str_lit(":", 1ULL);
                (void)_t2755;
                Array_set(_va54, &(U64){_t2754}, _t2755);
                ;
                U64 _t2756 = 2;
                (void)_t2756;
                Str *_t2757 = U32_to_str(&(U32){line});
                (void)_t2757;
                Array_set(_va54, &(U64){_t2756}, _t2757);
                ;
                U64 _t2758 = 3;
                (void)_t2758;
                Str *_t2759 = Str_lit(":", 1ULL);
                (void)_t2759;
                Array_set(_va54, &(U64){_t2758}, _t2759);
                ;
                U64 _t2760 = 4;
                (void)_t2760;
                Str *_t2761 = U32_to_str(&(U32){col});
                (void)_t2761;
                Array_set(_va54, &(U64){_t2760}, _t2761);
                ;
                U64 _t2762 = 5;
                (void)_t2762;
                Str *_t2763 = Str_lit(": error: unterminated string", 28ULL);
                (void)_t2763;
                Array_set(_va54, &(U64){_t2762}, _t2763);
                ;
                println(_va54);
                U64 _t2764 = U64_sub(DEREF(pos), start);
                (void)_t2764;
                Str *_t2765 = Str_substr(src, &(U64){start}, &(U64){_t2764});
                (void)_t2765;
                ;
                U32 _t2766 = U32_clone(&(U32){col});
                (void)_t2766;
                Token *_t2767 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2767->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2765); _t2767->text = *_ca; free(_ca); }
                _t2767->line = U32_clone(&(U32){line});
                _t2767->col = _t2766;
                (void)_t2767;
                Str_delete(_t2765, &(Bool){1});
                ;
                Vec_push(tokens, _t2767);
            }
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t2935 = 39;
        (void)_t2935;
        Bool _t2936 = U8_eq(DEREF(c), _t2935);
        (void)_t2936;
        ;
        if (_t2936) {
            U64_inc(pos);
            U64 ch_start = U64_clone(pos);
            (void)ch_start;
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
            Bool _t2802; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2802 = *_hp; free(_hp); }
            (void)_t2802;
            Bool _t2803 = Bool_and(_t2800, _t2801);
            (void)_t2803;
            ;
            ;
            Bool _t2804 = Bool_and(_t2802, _t2803);
            (void)_t2804;
            ;
            ;
            if (_t2804) {
                U64_inc(pos);
            }
            ;
            U64_inc(pos);
            U8 *_t2805 = Str_byte_at(src, pos);
            (void)_t2805;
            U8 _t2806 = 39;
            (void)_t2806;
            Bool _t2807; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2807 = *_hp; free(_hp); }
            (void)_t2807;
            Bool _t2808 = U8_eq(DEREF(_t2805), _t2806);
            (void)_t2808;
            ;
            Bool _t2809 = Bool_and(_t2807, _t2808);
            (void)_t2809;
            ;
            ;
            if (_t2809) {
                U64 _t2773 = U64_sub(DEREF(pos), ch_start);
                (void)_t2773;
                Str *_t2774 = Str_substr(src, &(U64){ch_start}, &(U64){_t2773});
                (void)_t2774;
                ;
                U32 _t2775 = U32_clone(&(U32){col});
                (void)_t2775;
                Token *_t2776 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Char()); _t2776->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2774); _t2776->text = *_ca; free(_ca); }
                _t2776->line = U32_clone(&(U32){line});
                _t2776->col = _t2775;
                (void)_t2776;
                Str_delete(_t2774, &(Bool){1});
                ;
                Vec_push(tokens, _t2776);
                U64_inc(pos);
            } else {
                Str *_t2777 = Str_lit("Str", 3ULL);
                (void)_t2777;
                U64 _t2778; { U64 *_hp = (U64 *)Str_size(); _t2778 = *_hp; free(_hp); }
                (void)_t2778;
                U64 _t2779 = 6;
                (void)_t2779;
                Array *_va55 = Array_new(_t2777, &(U64){_t2778}, &(U64){_t2779});
                (void)_va55;
                Str_delete(_t2777, &(Bool){1});
                ;
                ;
                U64 _t2780 = 0;
                (void)_t2780;
                Str *_t2781 = Str_clone(path);
                (void)_t2781;
                Array_set(_va55, &(U64){_t2780}, _t2781);
                ;
                U64 _t2782 = 1;
                (void)_t2782;
                Str *_t2783 = Str_lit(":", 1ULL);
                (void)_t2783;
                Array_set(_va55, &(U64){_t2782}, _t2783);
                ;
                U64 _t2784 = 2;
                (void)_t2784;
                Str *_t2785 = U32_to_str(&(U32){line});
                (void)_t2785;
                Array_set(_va55, &(U64){_t2784}, _t2785);
                ;
                U64 _t2786 = 3;
                (void)_t2786;
                Str *_t2787 = Str_lit(":", 1ULL);
                (void)_t2787;
                Array_set(_va55, &(U64){_t2786}, _t2787);
                ;
                U64 _t2788 = 4;
                (void)_t2788;
                Str *_t2789 = U32_to_str(&(U32){col});
                (void)_t2789;
                Array_set(_va55, &(U64){_t2788}, _t2789);
                ;
                U64 _t2790 = 5;
                (void)_t2790;
                Str *_t2791 = Str_lit(": error: unterminated character literal", 39ULL);
                (void)_t2791;
                Array_set(_va55, &(U64){_t2790}, _t2791);
                ;
                println(_va55);
                U64 _t2792 = U64_sub(DEREF(pos), start);
                (void)_t2792;
                Str *_t2793 = Str_substr(src, &(U64){start}, &(U64){_t2792});
                (void)_t2793;
                ;
                U32 _t2794 = U32_clone(&(U32){col});
                (void)_t2794;
                Token *_t2795 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2795->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2793); _t2795->text = *_ca; free(_ca); }
                _t2795->line = U32_clone(&(U32){line});
                _t2795->col = _t2794;
                (void)_t2795;
                Str_delete(_t2793, &(Bool){1});
                ;
                Vec_push(tokens, _t2795);
            }
            ;
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U64 _t2937 = 1;
        (void)_t2937;
        U64 _t2938 = U64_add(DEREF(pos), _t2937);
        (void)_t2938;
        ;
        Bool _t2939; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2938}, &(U64){src_len}); _t2939 = *_hp; free(_hp); }
        (void)_t2939;
        ;
        if (_t2939) {
            U64 _t2855 = 1;
            (void)_t2855;
            U64 *_t2856 = malloc(sizeof(U64)); *_t2856 = U64_add(DEREF(pos), _t2855);
            (void)_t2856;
            ;
            U8 *c2 = Str_byte_at(src, _t2856);
            (void)c2;
            TokenType *two = TokenType_clone(TokenType_Eof());
            (void)two;
            U8 _t2857 = 58;
            (void)_t2857;
            U8 _t2858 = 61;
            (void)_t2858;
            Bool _t2859 = U8_eq(DEREF(c), _t2857);
            (void)_t2859;
            ;
            Bool _t2860 = U8_eq(DEREF(c2), _t2858);
            (void)_t2860;
            ;
            Bool _t2861 = Bool_and(_t2859, _t2860);
            (void)_t2861;
            ;
            ;
            if (_t2861) {
                two = TokenType_clone(TokenType_ColonEq());
            } else {
                U8 _t2843 = 61;
                (void)_t2843;
                U8 _t2844 = 61;
                (void)_t2844;
                Bool _t2845 = U8_eq(DEREF(c), _t2843);
                (void)_t2845;
                ;
                Bool _t2846 = U8_eq(DEREF(c2), _t2844);
                (void)_t2846;
                ;
                Bool _t2847 = Bool_and(_t2845, _t2846);
                (void)_t2847;
                ;
                ;
                if (_t2847) {
                    two = TokenType_clone(TokenType_EqEq());
                } else {
                    U8 _t2838 = 33;
                    (void)_t2838;
                    U8 _t2839 = 61;
                    (void)_t2839;
                    Bool _t2840 = U8_eq(DEREF(c), _t2838);
                    (void)_t2840;
                    ;
                    Bool _t2841 = U8_eq(DEREF(c2), _t2839);
                    (void)_t2841;
                    ;
                    Bool _t2842 = Bool_and(_t2840, _t2841);
                    (void)_t2842;
                    ;
                    ;
                    if (_t2842) {
                        two = TokenType_clone(TokenType_Neq());
                    } else {
                        U8 _t2833 = 60;
                        (void)_t2833;
                        U8 _t2834 = 61;
                        (void)_t2834;
                        Bool _t2835 = U8_eq(DEREF(c), _t2833);
                        (void)_t2835;
                        ;
                        Bool _t2836 = U8_eq(DEREF(c2), _t2834);
                        (void)_t2836;
                        ;
                        Bool _t2837 = Bool_and(_t2835, _t2836);
                        (void)_t2837;
                        ;
                        ;
                        if (_t2837) {
                            two = TokenType_clone(TokenType_LtEq());
                        } else {
                            U8 _t2828 = 62;
                            (void)_t2828;
                            U8 _t2829 = 61;
                            (void)_t2829;
                            Bool _t2830 = U8_eq(DEREF(c), _t2828);
                            (void)_t2830;
                            ;
                            Bool _t2831 = U8_eq(DEREF(c2), _t2829);
                            (void)_t2831;
                            ;
                            Bool _t2832 = Bool_and(_t2830, _t2831);
                            (void)_t2832;
                            ;
                            ;
                            if (_t2832) {
                                two = TokenType_clone(TokenType_GtEq());
                            } else {
                                U8 _t2823 = 46;
                                (void)_t2823;
                                U8 _t2824 = 46;
                                (void)_t2824;
                                Bool _t2825 = U8_eq(DEREF(c), _t2823);
                                (void)_t2825;
                                ;
                                Bool _t2826 = U8_eq(DEREF(c2), _t2824);
                                (void)_t2826;
                                ;
                                Bool _t2827 = Bool_and(_t2825, _t2826);
                                (void)_t2827;
                                ;
                                ;
                                if (_t2827) {
                                    U64 _t2820 = 2;
                                    (void)_t2820;
                                    U64 _t2821 = U64_add(DEREF(pos), _t2820);
                                    (void)_t2821;
                                    ;
                                    Bool _t2822; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2821}, &(U64){src_len}); _t2822 = *_hp; free(_hp); }
                                    (void)_t2822;
                                    ;
                                    if (_t2822) {
                                        U64 _t2816 = 2;
                                        (void)_t2816;
                                        U64 *_t2817 = malloc(sizeof(U64)); *_t2817 = U64_add(DEREF(pos), _t2816);
                                        (void)_t2817;
                                        ;
                                        U8 *c3 = Str_byte_at(src, _t2817);
                                        (void)c3;
                                        U8 _t2818 = 46;
                                        (void)_t2818;
                                        Bool _t2819 = U8_eq(DEREF(c3), _t2818);
                                        (void)_t2819;
                                        U64_delete(_t2817, &(Bool){1});
                                        ;
                                        if (_t2819) {
                                            U64 _t2810 = 3;
                                            (void)_t2810;
                                            Str *_t2811 = Str_substr(src, &(U64){start}, &(U64){_t2810});
                                            (void)_t2811;
                                            ;
                                            U32 _t2812 = U32_clone(&(U32){col});
                                            (void)_t2812;
                                            Token *_t2813 = malloc(sizeof(Token));
                                            { TokenType *_ca = TokenType_clone(TokenType_DotDotDot()); _t2813->type = *_ca; free(_ca); }
                                            { Str *_ca = Str_clone(_t2811); _t2813->text = *_ca; free(_ca); }
                                            _t2813->line = U32_clone(&(U32){line});
                                            _t2813->col = _t2812;
                                            (void)_t2813;
                                            Str_delete(_t2811, &(Bool){1});
                                            ;
                                            Vec_push(tokens, _t2813);
                                            U64 _t2814 = 3;
                                            (void)_t2814;
                                            U64 _t2815 = U64_add(DEREF(pos), _t2814);
                                            (void)_t2815;
                                            ;
                                            *pos = _t2815;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            U64_delete(_t2856, &(Bool){1});
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
            U64_delete(_t2856, &(Bool){1});
            ;
            Bool _t2862; { Bool *_hp = (Bool *)TokenType_eq(two, TokenType_Eof()); _t2862 = *_hp; free(_hp); }
            (void)_t2862;
            Bool _t2863 = Bool_not(_t2862);
            (void)_t2863;
            ;
            if (_t2863) {
                U64 _t2848 = 2;
                (void)_t2848;
                Str *_t2849 = Str_substr(src, &(U64){start}, &(U64){_t2848});
                (void)_t2849;
                ;
                U32 _t2850 = U32_clone(&(U32){line});
                (void)_t2850;
                U32 _t2851 = U32_clone(&(U32){col});
                (void)_t2851;
                Token *_t2852 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(two); _t2852->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2849); _t2852->text = *_ca; free(_ca); }
                _t2852->line = _t2850;
                _t2852->col = _t2851;
                (void)_t2852;
                Str_delete(_t2849, &(Bool){1});
                ;
                ;
                Vec_push(tokens, _t2852);
                U64 _t2853 = 2;
                (void)_t2853;
                U64 _t2854 = U64_add(DEREF(pos), _t2853);
                (void)_t2854;
                ;
                *pos = _t2854;
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
            U8 _sw2864 = U8_clone(c);
            (void)_sw2864;
            U8 _t2899 = 40;
            (void)_t2899;
            Bool _t2900 = U8_eq(_sw2864, _t2899);
            (void)_t2900;
            ;
            if (_t2900) {
                single = TokenType_clone(TokenType_LParen());
            } else {
                U8 _t2897 = 41;
                (void)_t2897;
                Bool _t2898 = U8_eq(_sw2864, _t2897);
                (void)_t2898;
                ;
                if (_t2898) {
                    single = TokenType_clone(TokenType_RParen());
                } else {
                    U8 _t2895 = 123;
                    (void)_t2895;
                    Bool _t2896 = U8_eq(_sw2864, _t2895);
                    (void)_t2896;
                    ;
                    if (_t2896) {
                        single = TokenType_clone(TokenType_LBrace());
                    } else {
                        U8 _t2893 = 125;
                        (void)_t2893;
                        Bool _t2894 = U8_eq(_sw2864, _t2893);
                        (void)_t2894;
                        ;
                        if (_t2894) {
                            single = TokenType_clone(TokenType_RBrace());
                        } else {
                            U8 _t2891 = 91;
                            (void)_t2891;
                            Bool _t2892 = U8_eq(_sw2864, _t2891);
                            (void)_t2892;
                            ;
                            if (_t2892) {
                                single = TokenType_clone(TokenType_LBracket());
                            } else {
                                U8 _t2889 = 93;
                                (void)_t2889;
                                Bool _t2890 = U8_eq(_sw2864, _t2889);
                                (void)_t2890;
                                ;
                                if (_t2890) {
                                    single = TokenType_clone(TokenType_RBracket());
                                } else {
                                    U8 _t2887 = 44;
                                    (void)_t2887;
                                    Bool _t2888 = U8_eq(_sw2864, _t2887);
                                    (void)_t2888;
                                    ;
                                    if (_t2888) {
                                        single = TokenType_clone(TokenType_Comma());
                                    } else {
                                        U8 _t2885 = 58;
                                        (void)_t2885;
                                        Bool _t2886 = U8_eq(_sw2864, _t2885);
                                        (void)_t2886;
                                        ;
                                        if (_t2886) {
                                            single = TokenType_clone(TokenType_Colon());
                                        } else {
                                            U8 _t2883 = 46;
                                            (void)_t2883;
                                            Bool _t2884 = U8_eq(_sw2864, _t2883);
                                            (void)_t2884;
                                            ;
                                            if (_t2884) {
                                                single = TokenType_clone(TokenType_Dot());
                                            } else {
                                                U8 _t2881 = 63;
                                                (void)_t2881;
                                                Bool _t2882 = U8_eq(_sw2864, _t2881);
                                                (void)_t2882;
                                                ;
                                                if (_t2882) {
                                                    single = TokenType_clone(TokenType_Question());
                                                } else {
                                                    U8 _t2879 = 33;
                                                    (void)_t2879;
                                                    Bool _t2880 = U8_eq(_sw2864, _t2879);
                                                    (void)_t2880;
                                                    ;
                                                    if (_t2880) {
                                                        single = TokenType_clone(TokenType_Bang());
                                                    } else {
                                                        U8 _t2877 = 43;
                                                        (void)_t2877;
                                                        Bool _t2878 = U8_eq(_sw2864, _t2877);
                                                        (void)_t2878;
                                                        ;
                                                        if (_t2878) {
                                                            single = TokenType_clone(TokenType_Plus());
                                                        } else {
                                                            U8 _t2875 = 45;
                                                            (void)_t2875;
                                                            Bool _t2876 = U8_eq(_sw2864, _t2875);
                                                            (void)_t2876;
                                                            ;
                                                            if (_t2876) {
                                                                single = TokenType_clone(TokenType_Minus());
                                                            } else {
                                                                U8 _t2873 = 42;
                                                                (void)_t2873;
                                                                Bool _t2874 = U8_eq(_sw2864, _t2873);
                                                                (void)_t2874;
                                                                ;
                                                                if (_t2874) {
                                                                    single = TokenType_clone(TokenType_Star());
                                                                } else {
                                                                    U8 _t2871 = 47;
                                                                    (void)_t2871;
                                                                    Bool _t2872 = U8_eq(_sw2864, _t2871);
                                                                    (void)_t2872;
                                                                    ;
                                                                    if (_t2872) {
                                                                        single = TokenType_clone(TokenType_Slash());
                                                                    } else {
                                                                        U8 _t2869 = 61;
                                                                        (void)_t2869;
                                                                        Bool _t2870 = U8_eq(_sw2864, _t2869);
                                                                        (void)_t2870;
                                                                        ;
                                                                        if (_t2870) {
                                                                            single = TokenType_clone(TokenType_Eq());
                                                                        } else {
                                                                            U8 _t2867 = 60;
                                                                            (void)_t2867;
                                                                            Bool _t2868 = U8_eq(_sw2864, _t2867);
                                                                            (void)_t2868;
                                                                            ;
                                                                            if (_t2868) {
                                                                                single = TokenType_clone(TokenType_Lt());
                                                                            } else {
                                                                                U8 _t2865 = 62;
                                                                                (void)_t2865;
                                                                                Bool _t2866 = U8_eq(_sw2864, _t2865);
                                                                                (void)_t2866;
                                                                                ;
                                                                                if (_t2866) {
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
        Bool _t2940; { Bool *_hp = (Bool *)TokenType_eq(single, TokenType_Eof()); _t2940 = *_hp; free(_hp); }
        (void)_t2940;
        Bool _t2941 = Bool_not(_t2940);
        (void)_t2941;
        ;
        if (_t2941) {
            U64 _t2901 = 1;
            (void)_t2901;
            Str *_t2902 = Str_substr(src, &(U64){start}, &(U64){_t2901});
            (void)_t2902;
            ;
            U32 _t2903 = U32_clone(&(U32){line});
            (void)_t2903;
            U32 _t2904 = U32_clone(&(U32){col});
            (void)_t2904;
            Token *_t2905 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(single); _t2905->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(_t2902); _t2905->text = *_ca; free(_ca); }
            _t2905->line = _t2903;
            _t2905->col = _t2904;
            (void)_t2905;
            Str_delete(_t2902, &(Bool){1});
            ;
            ;
            Vec_push(tokens, _t2905);
            U64_inc(pos);
            ;
            ;
            TokenType_delete(single, &(Bool){1});
            ;
            continue;
        }
        ;
        TokenType_delete(single, &(Bool){1});
        Str *_t2942 = Str_lit("Str", 3ULL);
        (void)_t2942;
        U64 _t2943; { U64 *_hp = (U64 *)Str_size(); _t2943 = *_hp; free(_hp); }
        (void)_t2943;
        U64 _t2944 = 6;
        (void)_t2944;
        Array *_va56 = Array_new(_t2942, &(U64){_t2943}, &(U64){_t2944});
        (void)_va56;
        Str_delete(_t2942, &(Bool){1});
        ;
        ;
        U64 _t2945 = 0;
        (void)_t2945;
        Str *_t2946 = Str_clone(path);
        (void)_t2946;
        Array_set(_va56, &(U64){_t2945}, _t2946);
        ;
        U64 _t2947 = 1;
        (void)_t2947;
        Str *_t2948 = Str_lit(":", 1ULL);
        (void)_t2948;
        Array_set(_va56, &(U64){_t2947}, _t2948);
        ;
        U64 _t2949 = 2;
        (void)_t2949;
        Str *_t2950 = U32_to_str(&(U32){line});
        (void)_t2950;
        Array_set(_va56, &(U64){_t2949}, _t2950);
        ;
        U64 _t2951 = 3;
        (void)_t2951;
        Str *_t2952 = Str_lit(":", 1ULL);
        (void)_t2952;
        Array_set(_va56, &(U64){_t2951}, _t2952);
        ;
        U64 _t2953 = 4;
        (void)_t2953;
        Str *_t2954 = U32_to_str(&(U32){col});
        (void)_t2954;
        Array_set(_va56, &(U64){_t2953}, _t2954);
        ;
        U64 _t2955 = 5;
        (void)_t2955;
        Str *_t2956 = Str_lit(": error: unexpected character", 29ULL);
        (void)_t2956;
        Array_set(_va56, &(U64){_t2955}, _t2956);
        ;
        println(_va56);
        U64 _t2957 = 1;
        (void)_t2957;
        Str *_t2958 = Str_substr(src, &(U64){start}, &(U64){_t2957});
        (void)_t2958;
        ;
        ;
        U32 _t2959 = U32_clone(&(U32){col});
        (void)_t2959;
        ;
        Token *_t2960 = malloc(sizeof(Token));
        { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2960->type = *_ca; free(_ca); }
        { Str *_ca = Str_clone(_t2958); _t2960->text = *_ca; free(_ca); }
        _t2960->line = U32_clone(&(U32){line});
        _t2960->col = _t2959;
        (void)_t2960;
        Str_delete(_t2958, &(Bool){1});
        ;
        Vec_push(tokens, _t2960);
        U64_inc(pos);
    }
    ;
    U64 _t2963 = U64_sub(DEREF(pos), line_start);
    (void)_t2963;
    ;
    U64_delete(pos, &(Bool){1});
    U64 _t2964 = 1;
    (void)_t2964;
    U64 _t2965 = U64_add(_t2963, _t2964);
    (void)_t2965;
    ;
    ;
    I64 col = U64_to_i64(_t2965);
    (void)col;
    ;
    I64 _t2966 = I64_clone(&(I64){col});
    (void)_t2966;
    ;
    Token *_t2967 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(TokenType_Eof()); _t2967->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t2967->text = *_ca; free(_ca); }
    _t2967->line = U32_clone(&(U32){line});
    _t2967->col = _t2966;
    (void)_t2967;
    ;
    ;
    Vec_push(tokens, _t2967);
    return tokens;
}

