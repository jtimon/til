#include "ast_lexer.h"

Token * Token_clone(Token * self) {
    (void)self;
    I64 _t1598 = I64_clone(&self->line);
    (void)_t1598;
    I64 _t1599 = I64_clone(&self->col);
    (void)_t1599;
    Token *_t1600 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(&self->type); _t1600->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->text); _t1600->text = *_ca; free(_ca); }
    _t1600->line = _t1598;
    _t1600->col = _t1599;
    (void)_t1600;
    ;
    ;
    return _t1600;
}

U64 *Token_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Token);
    return r;
}

Bool * is_digit(U8 * c) {
    (void)c;
    U8 _t1606 = 48;
    (void)_t1606;
    U8 _t1607 = 57;
    (void)_t1607;
    Bool _t1608; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1606}); _t1608 = *_hp; free(_hp); }
    (void)_t1608;
    ;
    Bool _t1609; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1607}); _t1609 = *_hp; free(_hp); }
    (void)_t1609;
    ;
    Bool _t1610 = Bool_and(_t1608, _t1609);
    (void)_t1610;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1610; return _r; }
}

Bool * is_alpha(U8 * c) {
    (void)c;
    U8 _t1611 = 97;
    (void)_t1611;
    U8 _t1612 = 122;
    (void)_t1612;
    Bool _t1613; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1611}); _t1613 = *_hp; free(_hp); }
    (void)_t1613;
    ;
    Bool _t1614; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1612}); _t1614 = *_hp; free(_hp); }
    (void)_t1614;
    ;
    U8 _t1615 = 65;
    (void)_t1615;
    U8 _t1616 = 90;
    (void)_t1616;
    Bool _t1617; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1615}); _t1617 = *_hp; free(_hp); }
    (void)_t1617;
    ;
    Bool _t1618; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1616}); _t1618 = *_hp; free(_hp); }
    (void)_t1618;
    ;
    Bool _t1619 = Bool_and(_t1613, _t1614);
    (void)_t1619;
    ;
    ;
    Bool _t1620 = Bool_and(_t1617, _t1618);
    (void)_t1620;
    ;
    ;
    U8 _t1621 = 95;
    (void)_t1621;
    Bool _t1622 = Bool_or(_t1619, _t1620);
    (void)_t1622;
    ;
    ;
    Bool _t1623 = U8_eq(DEREF(c), _t1621);
    (void)_t1623;
    ;
    Bool _t1624 = Bool_or(_t1622, _t1623);
    (void)_t1624;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1624; return _r; }
}

Bool * is_alnum(U8 * c) {
    (void)c;
    Bool _t1625; { Bool *_hp = (Bool *)is_alpha(c); _t1625 = *_hp; free(_hp); }
    (void)_t1625;
    Bool _t1626; { Bool *_hp = (Bool *)is_digit(c); _t1626 = *_hp; free(_hp); }
    (void)_t1626;
    Bool _t1627 = Bool_or(_t1625, _t1626);
    (void)_t1627;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1627; return _r; }
}

Str * tok_name(TokenType * type) {
    (void)type;
    {
        TokenType *_sw1628 = TokenType_clone(type);
        (void)_sw1628;
        Bool _t1761; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_Eof()); _t1761 = *_hp; free(_hp); }
        (void)_t1761;
        if (_t1761) {
            Str *_t1629 = Str_lit("eof", 3ULL);
            (void)_t1629;
            TokenType_delete(_sw1628, &(Bool){1});
            ;
            return _t1629;
        } else {
            Bool _t1760; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_LParen()); _t1760 = *_hp; free(_hp); }
            (void)_t1760;
            if (_t1760) {
                Str *_t1630 = Str_lit("(", 1ULL);
                (void)_t1630;
                ;
                TokenType_delete(_sw1628, &(Bool){1});
                ;
                return _t1630;
            } else {
                Bool _t1759; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_RParen()); _t1759 = *_hp; free(_hp); }
                (void)_t1759;
                if (_t1759) {
                    Str *_t1631 = Str_lit(")", 1ULL);
                    (void)_t1631;
                    ;
                    ;
                    TokenType_delete(_sw1628, &(Bool){1});
                    ;
                    return _t1631;
                } else {
                    Bool _t1758; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_LBrace()); _t1758 = *_hp; free(_hp); }
                    (void)_t1758;
                    if (_t1758) {
                        Str *_t1632 = Str_lit("{", 1ULL);
                        (void)_t1632;
                        ;
                        ;
                        ;
                        TokenType_delete(_sw1628, &(Bool){1});
                        ;
                        return _t1632;
                    } else {
                        Bool _t1757; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_RBrace()); _t1757 = *_hp; free(_hp); }
                        (void)_t1757;
                        if (_t1757) {
                            Str *_t1633 = Str_lit("}", 1ULL);
                            (void)_t1633;
                            ;
                            ;
                            ;
                            ;
                            TokenType_delete(_sw1628, &(Bool){1});
                            ;
                            return _t1633;
                        } else {
                            Bool _t1756; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_LBracket()); _t1756 = *_hp; free(_hp); }
                            (void)_t1756;
                            if (_t1756) {
                                Str *_t1634 = Str_lit("[", 1ULL);
                                (void)_t1634;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TokenType_delete(_sw1628, &(Bool){1});
                                ;
                                return _t1634;
                            } else {
                                Bool _t1755; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_RBracket()); _t1755 = *_hp; free(_hp); }
                                (void)_t1755;
                                if (_t1755) {
                                    Str *_t1635 = Str_lit("]", 1ULL);
                                    (void)_t1635;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TokenType_delete(_sw1628, &(Bool){1});
                                    ;
                                    return _t1635;
                                } else {
                                    Bool _t1754; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_Comma()); _t1754 = *_hp; free(_hp); }
                                    (void)_t1754;
                                    if (_t1754) {
                                        Str *_t1636 = Str_lit(",", 1ULL);
                                        (void)_t1636;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TokenType_delete(_sw1628, &(Bool){1});
                                        ;
                                        return _t1636;
                                    } else {
                                        Bool _t1753; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_Colon()); _t1753 = *_hp; free(_hp); }
                                        (void)_t1753;
                                        if (_t1753) {
                                            Str *_t1637 = Str_lit(":", 1ULL);
                                            (void)_t1637;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TokenType_delete(_sw1628, &(Bool){1});
                                            ;
                                            return _t1637;
                                        } else {
                                            Bool _t1752; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_Question()); _t1752 = *_hp; free(_hp); }
                                            (void)_t1752;
                                            if (_t1752) {
                                                Str *_t1638 = Str_lit("?", 1ULL);
                                                (void)_t1638;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                TokenType_delete(_sw1628, &(Bool){1});
                                                ;
                                                return _t1638;
                                            } else {
                                                Bool _t1751; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_Bang()); _t1751 = *_hp; free(_hp); }
                                                (void)_t1751;
                                                if (_t1751) {
                                                    Str *_t1639 = Str_lit("!", 1ULL);
                                                    (void)_t1639;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    TokenType_delete(_sw1628, &(Bool){1});
                                                    ;
                                                    return _t1639;
                                                } else {
                                                    Bool _t1750; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_Minus()); _t1750 = *_hp; free(_hp); }
                                                    (void)_t1750;
                                                    if (_t1750) {
                                                        Str *_t1640 = Str_lit("-", 1ULL);
                                                        (void)_t1640;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        TokenType_delete(_sw1628, &(Bool){1});
                                                        ;
                                                        return _t1640;
                                                    } else {
                                                        Bool _t1749; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_Plus()); _t1749 = *_hp; free(_hp); }
                                                        (void)_t1749;
                                                        if (_t1749) {
                                                            Str *_t1641 = Str_lit("+", 1ULL);
                                                            (void)_t1641;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            TokenType_delete(_sw1628, &(Bool){1});
                                                            ;
                                                            return _t1641;
                                                        } else {
                                                            Bool _t1748; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_Star()); _t1748 = *_hp; free(_hp); }
                                                            (void)_t1748;
                                                            if (_t1748) {
                                                                Str *_t1642 = Str_lit("*", 1ULL);
                                                                (void)_t1642;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                TokenType_delete(_sw1628, &(Bool){1});
                                                                ;
                                                                return _t1642;
                                                            } else {
                                                                Bool _t1747; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_Slash()); _t1747 = *_hp; free(_hp); }
                                                                (void)_t1747;
                                                                if (_t1747) {
                                                                    Str *_t1643 = Str_lit("/", 1ULL);
                                                                    (void)_t1643;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    TokenType_delete(_sw1628, &(Bool){1});
                                                                    ;
                                                                    return _t1643;
                                                                } else {
                                                                    Bool _t1746; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_Dot()); _t1746 = *_hp; free(_hp); }
                                                                    (void)_t1746;
                                                                    if (_t1746) {
                                                                        Str *_t1644 = Str_lit(".", 1ULL);
                                                                        (void)_t1644;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        TokenType_delete(_sw1628, &(Bool){1});
                                                                        ;
                                                                        return _t1644;
                                                                    } else {
                                                                        Bool _t1745; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_DotDot()); _t1745 = *_hp; free(_hp); }
                                                                        (void)_t1745;
                                                                        if (_t1745) {
                                                                            Str *_t1645 = Str_lit("..", 2ULL);
                                                                            (void)_t1645;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TokenType_delete(_sw1628, &(Bool){1});
                                                                            ;
                                                                            return _t1645;
                                                                        } else {
                                                                            Bool _t1744; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_DotDotDot()); _t1744 = *_hp; free(_hp); }
                                                                            (void)_t1744;
                                                                            if (_t1744) {
                                                                                Str *_t1646 = Str_lit("...", 3ULL);
                                                                                (void)_t1646;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                TokenType_delete(_sw1628, &(Bool){1});
                                                                                ;
                                                                                return _t1646;
                                                                            } else {
                                                                                Bool _t1743; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_Eq()); _t1743 = *_hp; free(_hp); }
                                                                                (void)_t1743;
                                                                                if (_t1743) {
                                                                                    Str *_t1647 = Str_lit("=", 1ULL);
                                                                                    (void)_t1647;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    TokenType_delete(_sw1628, &(Bool){1});
                                                                                    ;
                                                                                    return _t1647;
                                                                                } else {
                                                                                    Bool _t1742; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_EqEq()); _t1742 = *_hp; free(_hp); }
                                                                                    (void)_t1742;
                                                                                    if (_t1742) {
                                                                                        Str *_t1648 = Str_lit("==", 2ULL);
                                                                                        (void)_t1648;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        TokenType_delete(_sw1628, &(Bool){1});
                                                                                        ;
                                                                                        return _t1648;
                                                                                    } else {
                                                                                        Bool _t1741; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_Neq()); _t1741 = *_hp; free(_hp); }
                                                                                        (void)_t1741;
                                                                                        if (_t1741) {
                                                                                            Str *_t1649 = Str_lit("!=", 2ULL);
                                                                                            (void)_t1649;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            TokenType_delete(_sw1628, &(Bool){1});
                                                                                            ;
                                                                                            return _t1649;
                                                                                        } else {
                                                                                            Bool _t1740; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_Lt()); _t1740 = *_hp; free(_hp); }
                                                                                            (void)_t1740;
                                                                                            if (_t1740) {
                                                                                                Str *_t1650 = Str_lit("<", 1ULL);
                                                                                                (void)_t1650;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                TokenType_delete(_sw1628, &(Bool){1});
                                                                                                ;
                                                                                                return _t1650;
                                                                                            } else {
                                                                                                Bool _t1739; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_LtEq()); _t1739 = *_hp; free(_hp); }
                                                                                                (void)_t1739;
                                                                                                if (_t1739) {
                                                                                                    Str *_t1651 = Str_lit("<=", 2ULL);
                                                                                                    (void)_t1651;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    TokenType_delete(_sw1628, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t1651;
                                                                                                } else {
                                                                                                    Bool _t1738; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_Gt()); _t1738 = *_hp; free(_hp); }
                                                                                                    (void)_t1738;
                                                                                                    if (_t1738) {
                                                                                                        Str *_t1652 = Str_lit(">", 1ULL);
                                                                                                        (void)_t1652;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        TokenType_delete(_sw1628, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t1652;
                                                                                                    } else {
                                                                                                        Bool _t1737; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_GtEq()); _t1737 = *_hp; free(_hp); }
                                                                                                        (void)_t1737;
                                                                                                        if (_t1737) {
                                                                                                            Str *_t1653 = Str_lit(">=", 2ULL);
                                                                                                            (void)_t1653;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            TokenType_delete(_sw1628, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1653;
                                                                                                        } else {
                                                                                                            Bool _t1736; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_ColonEq()); _t1736 = *_hp; free(_hp); }
                                                                                                            (void)_t1736;
                                                                                                            if (_t1736) {
                                                                                                                Str *_t1654 = Str_lit(":=", 2ULL);
                                                                                                                (void)_t1654;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                ;
                                                                                                                return _t1654;
                                                                                                            } else {
                                                                                                                Bool _t1735; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_Ident()); _t1735 = *_hp; free(_hp); }
                                                                                                                (void)_t1735;
                                                                                                                if (_t1735) {
                                                                                                                    Str *_t1655 = Str_lit("identifier", 10ULL);
                                                                                                                    (void)_t1655;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return _t1655;
                                                                                                                } else {
                                                                                                                    Bool _t1734; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_StringTok()); _t1734 = *_hp; free(_hp); }
                                                                                                                    (void)_t1734;
                                                                                                                    if (_t1734) {
                                                                                                                        Str *_t1656 = Str_lit("string", 6ULL);
                                                                                                                        (void)_t1656;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return _t1656;
                                                                                                                    } else {
                                                                                                                        Bool _t1733; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_Number()); _t1733 = *_hp; free(_hp); }
                                                                                                                        (void)_t1733;
                                                                                                                        if (_t1733) {
                                                                                                                            Str *_t1657 = Str_lit("number", 6ULL);
                                                                                                                            (void)_t1657;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return _t1657;
                                                                                                                        } else {
                                                                                                                            Bool _t1732; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_Char()); _t1732 = *_hp; free(_hp); }
                                                                                                                            (void)_t1732;
                                                                                                                            if (_t1732) {
                                                                                                                                Str *_t1658 = Str_lit("char", 4ULL);
                                                                                                                                (void)_t1658;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return _t1658;
                                                                                                                            } else {
                                                                                                                                Bool _t1731; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwMode()); _t1731 = *_hp; free(_hp); }
                                                                                                                                (void)_t1731;
                                                                                                                                if (_t1731) {
                                                                                                                                    Str *_t1659 = Str_lit("mode", 4ULL);
                                                                                                                                    (void)_t1659;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return _t1659;
                                                                                                                                } else {
                                                                                                                                    Bool _t1730; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwMut()); _t1730 = *_hp; free(_hp); }
                                                                                                                                    (void)_t1730;
                                                                                                                                    if (_t1730) {
                                                                                                                                        Str *_t1660 = Str_lit("mut", 3ULL);
                                                                                                                                        (void)_t1660;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return _t1660;
                                                                                                                                    } else {
                                                                                                                                        Bool _t1729; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwOwn()); _t1729 = *_hp; free(_hp); }
                                                                                                                                        (void)_t1729;
                                                                                                                                        if (_t1729) {
                                                                                                                                            Str *_t1661 = Str_lit("own", 3ULL);
                                                                                                                                            (void)_t1661;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return _t1661;
                                                                                                                                        } else {
                                                                                                                                            Bool _t1728; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwRef()); _t1728 = *_hp; free(_hp); }
                                                                                                                                            (void)_t1728;
                                                                                                                                            if (_t1728) {
                                                                                                                                                Str *_t1662 = Str_lit("ref", 3ULL);
                                                                                                                                                (void)_t1662;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return _t1662;
                                                                                                                                            } else {
                                                                                                                                                Bool _t1727; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwShallow()); _t1727 = *_hp; free(_hp); }
                                                                                                                                                (void)_t1727;
                                                                                                                                                if (_t1727) {
                                                                                                                                                    Str *_t1663 = Str_lit("shallow", 7ULL);
                                                                                                                                                    (void)_t1663;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                    ;
                                                                                                                                                    return _t1663;
                                                                                                                                                } else {
                                                                                                                                                    Bool _t1726; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwStruct()); _t1726 = *_hp; free(_hp); }
                                                                                                                                                    (void)_t1726;
                                                                                                                                                    if (_t1726) {
                                                                                                                                                        Str *_t1664 = Str_lit("struct", 6ULL);
                                                                                                                                                        (void)_t1664;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                        ;
                                                                                                                                                        return _t1664;
                                                                                                                                                    } else {
                                                                                                                                                        Bool _t1725; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwExtStruct()); _t1725 = *_hp; free(_hp); }
                                                                                                                                                        (void)_t1725;
                                                                                                                                                        if (_t1725) {
                                                                                                                                                            Str *_t1665 = Str_lit("ext_struct", 10ULL);
                                                                                                                                                            (void)_t1665;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                            ;
                                                                                                                                                            return _t1665;
                                                                                                                                                        } else {
                                                                                                                                                            Bool _t1724; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwEnum()); _t1724 = *_hp; free(_hp); }
                                                                                                                                                            (void)_t1724;
                                                                                                                                                            if (_t1724) {
                                                                                                                                                                Str *_t1666 = Str_lit("enum", 4ULL);
                                                                                                                                                                (void)_t1666;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                ;
                                                                                                                                                                return _t1666;
                                                                                                                                                            } else {
                                                                                                                                                                Bool _t1723; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwNamespace()); _t1723 = *_hp; free(_hp); }
                                                                                                                                                                (void)_t1723;
                                                                                                                                                                if (_t1723) {
                                                                                                                                                                    Str *_t1667 = Str_lit("namespace", 9ULL);
                                                                                                                                                                    (void)_t1667;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                    ;
                                                                                                                                                                    return _t1667;
                                                                                                                                                                } else {
                                                                                                                                                                    Bool _t1722; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwFunc()); _t1722 = *_hp; free(_hp); }
                                                                                                                                                                    (void)_t1722;
                                                                                                                                                                    if (_t1722) {
                                                                                                                                                                        Str *_t1668 = Str_lit("func", 4ULL);
                                                                                                                                                                        (void)_t1668;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                        ;
                                                                                                                                                                        return _t1668;
                                                                                                                                                                    } else {
                                                                                                                                                                        Bool _t1721; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwProc()); _t1721 = *_hp; free(_hp); }
                                                                                                                                                                        (void)_t1721;
                                                                                                                                                                        if (_t1721) {
                                                                                                                                                                            Str *_t1669 = Str_lit("proc", 4ULL);
                                                                                                                                                                            (void)_t1669;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                            ;
                                                                                                                                                                            return _t1669;
                                                                                                                                                                        } else {
                                                                                                                                                                            Bool _t1720; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwTest()); _t1720 = *_hp; free(_hp); }
                                                                                                                                                                            (void)_t1720;
                                                                                                                                                                            if (_t1720) {
                                                                                                                                                                                Str *_t1670 = Str_lit("test", 4ULL);
                                                                                                                                                                                (void)_t1670;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                ;
                                                                                                                                                                                return _t1670;
                                                                                                                                                                            } else {
                                                                                                                                                                                Bool _t1719; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwMacro()); _t1719 = *_hp; free(_hp); }
                                                                                                                                                                                (void)_t1719;
                                                                                                                                                                                if (_t1719) {
                                                                                                                                                                                    Str *_t1671 = Str_lit("macro", 5ULL);
                                                                                                                                                                                    (void)_t1671;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                    ;
                                                                                                                                                                                    return _t1671;
                                                                                                                                                                                } else {
                                                                                                                                                                                    Bool _t1718; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwExtFunc()); _t1718 = *_hp; free(_hp); }
                                                                                                                                                                                    (void)_t1718;
                                                                                                                                                                                    if (_t1718) {
                                                                                                                                                                                        Str *_t1672 = Str_lit("ext_func", 8ULL);
                                                                                                                                                                                        (void)_t1672;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                        ;
                                                                                                                                                                                        return _t1672;
                                                                                                                                                                                    } else {
                                                                                                                                                                                        Bool _t1717; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwExtProc()); _t1717 = *_hp; free(_hp); }
                                                                                                                                                                                        (void)_t1717;
                                                                                                                                                                                        if (_t1717) {
                                                                                                                                                                                            Str *_t1673 = Str_lit("ext_proc", 8ULL);
                                                                                                                                                                                            (void)_t1673;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                            ;
                                                                                                                                                                                            return _t1673;
                                                                                                                                                                                        } else {
                                                                                                                                                                                            Bool _t1716; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwReturns()); _t1716 = *_hp; free(_hp); }
                                                                                                                                                                                            (void)_t1716;
                                                                                                                                                                                            if (_t1716) {
                                                                                                                                                                                                Str *_t1674 = Str_lit("returns", 7ULL);
                                                                                                                                                                                                (void)_t1674;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                                ;
                                                                                                                                                                                                return _t1674;
                                                                                                                                                                                            } else {
                                                                                                                                                                                                Bool _t1715; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwThrows()); _t1715 = *_hp; free(_hp); }
                                                                                                                                                                                                (void)_t1715;
                                                                                                                                                                                                if (_t1715) {
                                                                                                                                                                                                    Str *_t1675 = Str_lit("throws", 6ULL);
                                                                                                                                                                                                    (void)_t1675;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    return _t1675;
                                                                                                                                                                                                } else {
                                                                                                                                                                                                    Bool _t1714; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwIf()); _t1714 = *_hp; free(_hp); }
                                                                                                                                                                                                    (void)_t1714;
                                                                                                                                                                                                    if (_t1714) {
                                                                                                                                                                                                        Str *_t1676 = Str_lit("if", 2ULL);
                                                                                                                                                                                                        (void)_t1676;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        return _t1676;
                                                                                                                                                                                                    } else {
                                                                                                                                                                                                        Bool _t1713; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwElse()); _t1713 = *_hp; free(_hp); }
                                                                                                                                                                                                        (void)_t1713;
                                                                                                                                                                                                        if (_t1713) {
                                                                                                                                                                                                            Str *_t1677 = Str_lit("else", 4ULL);
                                                                                                                                                                                                            (void)_t1677;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            return _t1677;
                                                                                                                                                                                                        } else {
                                                                                                                                                                                                            Bool _t1712; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwWhile()); _t1712 = *_hp; free(_hp); }
                                                                                                                                                                                                            (void)_t1712;
                                                                                                                                                                                                            if (_t1712) {
                                                                                                                                                                                                                Str *_t1678 = Str_lit("while", 5ULL);
                                                                                                                                                                                                                (void)_t1678;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                return _t1678;
                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                Bool _t1711; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwFor()); _t1711 = *_hp; free(_hp); }
                                                                                                                                                                                                                (void)_t1711;
                                                                                                                                                                                                                if (_t1711) {
                                                                                                                                                                                                                    Str *_t1679 = Str_lit("for", 3ULL);
                                                                                                                                                                                                                    (void)_t1679;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    return _t1679;
                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                    Bool _t1710; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwIn()); _t1710 = *_hp; free(_hp); }
                                                                                                                                                                                                                    (void)_t1710;
                                                                                                                                                                                                                    if (_t1710) {
                                                                                                                                                                                                                        Str *_t1680 = Str_lit("in", 2ULL);
                                                                                                                                                                                                                        (void)_t1680;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        return _t1680;
                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                        Bool _t1709; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwSwitch()); _t1709 = *_hp; free(_hp); }
                                                                                                                                                                                                                        (void)_t1709;
                                                                                                                                                                                                                        if (_t1709) {
                                                                                                                                                                                                                            Str *_t1681 = Str_lit("switch", 6ULL);
                                                                                                                                                                                                                            (void)_t1681;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            return _t1681;
                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                            Bool _t1708; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwMatch()); _t1708 = *_hp; free(_hp); }
                                                                                                                                                                                                                            (void)_t1708;
                                                                                                                                                                                                                            if (_t1708) {
                                                                                                                                                                                                                                Str *_t1682 = Str_lit("match", 5ULL);
                                                                                                                                                                                                                                (void)_t1682;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                return _t1682;
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                Bool _t1707; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwCase()); _t1707 = *_hp; free(_hp); }
                                                                                                                                                                                                                                (void)_t1707;
                                                                                                                                                                                                                                if (_t1707) {
                                                                                                                                                                                                                                    Str *_t1683 = Str_lit("case", 4ULL);
                                                                                                                                                                                                                                    (void)_t1683;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    return _t1683;
                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                    Bool _t1706; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwDefault()); _t1706 = *_hp; free(_hp); }
                                                                                                                                                                                                                                    (void)_t1706;
                                                                                                                                                                                                                                    if (_t1706) {
                                                                                                                                                                                                                                        Str *_t1684 = Str_lit("default", 7ULL);
                                                                                                                                                                                                                                        (void)_t1684;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        return _t1684;
                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                        Bool _t1705; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwReturn()); _t1705 = *_hp; free(_hp); }
                                                                                                                                                                                                                                        (void)_t1705;
                                                                                                                                                                                                                                        if (_t1705) {
                                                                                                                                                                                                                                            Str *_t1685 = Str_lit("return", 6ULL);
                                                                                                                                                                                                                                            (void)_t1685;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            return _t1685;
                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                            Bool _t1704; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwThrow()); _t1704 = *_hp; free(_hp); }
                                                                                                                                                                                                                                            (void)_t1704;
                                                                                                                                                                                                                                            if (_t1704) {
                                                                                                                                                                                                                                                Str *_t1686 = Str_lit("throw", 5ULL);
                                                                                                                                                                                                                                                (void)_t1686;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                return _t1686;
                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                Bool _t1703; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwCatch()); _t1703 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                (void)_t1703;
                                                                                                                                                                                                                                                if (_t1703) {
                                                                                                                                                                                                                                                    Str *_t1687 = Str_lit("catch", 5ULL);
                                                                                                                                                                                                                                                    (void)_t1687;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    return _t1687;
                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                    Bool _t1702; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwBreak()); _t1702 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                    (void)_t1702;
                                                                                                                                                                                                                                                    if (_t1702) {
                                                                                                                                                                                                                                                        Str *_t1688 = Str_lit("break", 5ULL);
                                                                                                                                                                                                                                                        (void)_t1688;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        return _t1688;
                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                        Bool _t1701; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwContinue()); _t1701 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                        (void)_t1701;
                                                                                                                                                                                                                                                        if (_t1701) {
                                                                                                                                                                                                                                                            Str *_t1689 = Str_lit("continue", 8ULL);
                                                                                                                                                                                                                                                            (void)_t1689;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            return _t1689;
                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                            Bool _t1700; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwDefer()); _t1700 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                            (void)_t1700;
                                                                                                                                                                                                                                                            if (_t1700) {
                                                                                                                                                                                                                                                                Str *_t1690 = Str_lit("defer", 5ULL);
                                                                                                                                                                                                                                                                (void)_t1690;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                return _t1690;
                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                Bool _t1699; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwTrue()); _t1699 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                (void)_t1699;
                                                                                                                                                                                                                                                                if (_t1699) {
                                                                                                                                                                                                                                                                    Str *_t1691 = Str_lit("true", 4ULL);
                                                                                                                                                                                                                                                                    (void)_t1691;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t1691;
                                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                                    Bool _t1698; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwFalse()); _t1698 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                    (void)_t1698;
                                                                                                                                                                                                                                                                    if (_t1698) {
                                                                                                                                                                                                                                                                        Str *_t1692 = Str_lit("false", 5ULL);
                                                                                                                                                                                                                                                                        (void)_t1692;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        return _t1692;
                                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                                        Bool _t1697; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_KwNull()); _t1697 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                        (void)_t1697;
                                                                                                                                                                                                                                                                        if (_t1697) {
                                                                                                                                                                                                                                                                            Str *_t1693 = Str_lit("NULL", 4ULL);
                                                                                                                                                                                                                                                                            (void)_t1693;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            return _t1693;
                                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                                            Bool _t1696; { Bool *_hp = (Bool *)TokenType_eq(_sw1628, TokenType_Error()); _t1696 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                            (void)_t1696;
                                                                                                                                                                                                                                                                            if (_t1696) {
                                                                                                                                                                                                                                                                                Str *_t1694 = Str_lit("error", 5ULL);
                                                                                                                                                                                                                                                                                (void)_t1694;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t1694;
                                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                                Str *_t1695 = Str_lit("?", 1ULL);
                                                                                                                                                                                                                                                                                (void)_t1695;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                TokenType_delete(_sw1628, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t1695;
                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                        }
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                    }
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                }
                                                                                                                                                                                                                ;
                                                                                                                                                                                                            }
                                                                                                                                                                                                            ;
                                                                                                                                                                                                        }
                                                                                                                                                                                                        ;
                                                                                                                                                                                                    }
                                                                                                                                                                                                    ;
                                                                                                                                                                                                }
                                                                                                                                                                                                ;
                                                                                                                                                                                            }
                                                                                                                                                                                            ;
                                                                                                                                                                                        }
                                                                                                                                                                                        ;
                                                                                                                                                                                    }
                                                                                                                                                                                    ;
                                                                                                                                                                                }
                                                                                                                                                                                ;
                                                                                                                                                                            }
                                                                                                                                                                            ;
                                                                                                                                                                        }
                                                                                                                                                                        ;
                                                                                                                                                                    }
                                                                                                                                                                    ;
                                                                                                                                                                }
                                                                                                                                                                ;
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                        ;
                                                                                                                                                    }
                                                                                                                                                    ;
                                                                                                                                                }
                                                                                                                                                ;
                                                                                                                                            }
                                                                                                                                            ;
                                                                                                                                        }
                                                                                                                                        ;
                                                                                                                                    }
                                                                                                                                    ;
                                                                                                                                }
                                                                                                                                ;
                                                                                                                            }
                                                                                                                            ;
                                                                                                                        }
                                                                                                                        ;
                                                                                                                    }
                                                                                                                    ;
                                                                                                                }
                                                                                                                ;
                                                                                                            }
                                                                                                            ;
                                                                                                        }
                                                                                                        ;
                                                                                                    }
                                                                                                    ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                            ;
                                                                                        }
                                                                                        ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                                ;
                                                                            }
                                                                            ;
                                                                        }
                                                                        ;
                                                                    }
                                                                    ;
                                                                }
                                                                ;
                                                            }
                                                            ;
                                                        }
                                                        ;
                                                    }
                                                    ;
                                                }
                                                ;
                                            }
                                            ;
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        TokenType_delete(_sw1628, &(Bool){1});
        ;
    }
}

TokenType * lookup_keyword(Str * word) {
    (void)word;
    {
        Str *_sw1762 = Str_clone(word);
        (void)_sw1762;
        Str *_t1831 = Str_lit("mode", 4ULL);
        (void)_t1831;
        Bool _t1832; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1831); _t1832 = *_hp; free(_hp); }
        (void)_t1832;
        Str_delete(_t1831, &(Bool){1});
        if (_t1832) {
            Str_delete(_sw1762, &(Bool){1});
            ;
            return TokenType_KwMode();
        } else {
            Str *_t1829 = Str_lit("mut", 3ULL);
            (void)_t1829;
            Bool _t1830; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1829); _t1830 = *_hp; free(_hp); }
            (void)_t1830;
            Str_delete(_t1829, &(Bool){1});
            if (_t1830) {
                ;
                Str_delete(_sw1762, &(Bool){1});
                ;
                return TokenType_KwMut();
            } else {
                Str *_t1827 = Str_lit("own", 3ULL);
                (void)_t1827;
                Bool _t1828; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1827); _t1828 = *_hp; free(_hp); }
                (void)_t1828;
                Str_delete(_t1827, &(Bool){1});
                if (_t1828) {
                    ;
                    ;
                    Str_delete(_sw1762, &(Bool){1});
                    ;
                    return TokenType_KwOwn();
                } else {
                    Str *_t1825 = Str_lit("ref", 3ULL);
                    (void)_t1825;
                    Bool _t1826; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1825); _t1826 = *_hp; free(_hp); }
                    (void)_t1826;
                    Str_delete(_t1825, &(Bool){1});
                    if (_t1826) {
                        ;
                        ;
                        ;
                        Str_delete(_sw1762, &(Bool){1});
                        ;
                        return TokenType_KwRef();
                    } else {
                        Str *_t1823 = Str_lit("shallow", 7ULL);
                        (void)_t1823;
                        Bool _t1824; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1823); _t1824 = *_hp; free(_hp); }
                        (void)_t1824;
                        Str_delete(_t1823, &(Bool){1});
                        if (_t1824) {
                            ;
                            ;
                            ;
                            ;
                            Str_delete(_sw1762, &(Bool){1});
                            ;
                            return TokenType_KwShallow();
                        } else {
                            Str *_t1821 = Str_lit("struct", 6ULL);
                            (void)_t1821;
                            Bool _t1822; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1821); _t1822 = *_hp; free(_hp); }
                            (void)_t1822;
                            Str_delete(_t1821, &(Bool){1});
                            if (_t1822) {
                                ;
                                ;
                                ;
                                ;
                                ;
                                Str_delete(_sw1762, &(Bool){1});
                                ;
                                return TokenType_KwStruct();
                            } else {
                                Str *_t1819 = Str_lit("ext_struct", 10ULL);
                                (void)_t1819;
                                Bool _t1820; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1819); _t1820 = *_hp; free(_hp); }
                                (void)_t1820;
                                Str_delete(_t1819, &(Bool){1});
                                if (_t1820) {
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    Str_delete(_sw1762, &(Bool){1});
                                    ;
                                    return TokenType_KwExtStruct();
                                } else {
                                    Str *_t1817 = Str_lit("enum", 4ULL);
                                    (void)_t1817;
                                    Bool _t1818; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1817); _t1818 = *_hp; free(_hp); }
                                    (void)_t1818;
                                    Str_delete(_t1817, &(Bool){1});
                                    if (_t1818) {
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        Str_delete(_sw1762, &(Bool){1});
                                        ;
                                        return TokenType_KwEnum();
                                    } else {
                                        Str *_t1815 = Str_lit("namespace", 9ULL);
                                        (void)_t1815;
                                        Bool _t1816; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1815); _t1816 = *_hp; free(_hp); }
                                        (void)_t1816;
                                        Str_delete(_t1815, &(Bool){1});
                                        if (_t1816) {
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            Str_delete(_sw1762, &(Bool){1});
                                            ;
                                            return TokenType_KwNamespace();
                                        } else {
                                            Str *_t1813 = Str_lit("func", 4ULL);
                                            (void)_t1813;
                                            Bool _t1814; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1813); _t1814 = *_hp; free(_hp); }
                                            (void)_t1814;
                                            Str_delete(_t1813, &(Bool){1});
                                            if (_t1814) {
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                Str_delete(_sw1762, &(Bool){1});
                                                ;
                                                return TokenType_KwFunc();
                                            } else {
                                                Str *_t1811 = Str_lit("proc", 4ULL);
                                                (void)_t1811;
                                                Bool _t1812; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1811); _t1812 = *_hp; free(_hp); }
                                                (void)_t1812;
                                                Str_delete(_t1811, &(Bool){1});
                                                if (_t1812) {
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    Str_delete(_sw1762, &(Bool){1});
                                                    ;
                                                    return TokenType_KwProc();
                                                } else {
                                                    Str *_t1809 = Str_lit("test", 4ULL);
                                                    (void)_t1809;
                                                    Bool _t1810; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1809); _t1810 = *_hp; free(_hp); }
                                                    (void)_t1810;
                                                    Str_delete(_t1809, &(Bool){1});
                                                    if (_t1810) {
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        Str_delete(_sw1762, &(Bool){1});
                                                        ;
                                                        return TokenType_KwTest();
                                                    } else {
                                                        Str *_t1807 = Str_lit("macro", 5ULL);
                                                        (void)_t1807;
                                                        Bool _t1808; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1807); _t1808 = *_hp; free(_hp); }
                                                        (void)_t1808;
                                                        Str_delete(_t1807, &(Bool){1});
                                                        if (_t1808) {
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            Str_delete(_sw1762, &(Bool){1});
                                                            ;
                                                            return TokenType_KwMacro();
                                                        } else {
                                                            Str *_t1805 = Str_lit("ext_func", 8ULL);
                                                            (void)_t1805;
                                                            Bool _t1806; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1805); _t1806 = *_hp; free(_hp); }
                                                            (void)_t1806;
                                                            Str_delete(_t1805, &(Bool){1});
                                                            if (_t1806) {
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                Str_delete(_sw1762, &(Bool){1});
                                                                ;
                                                                return TokenType_KwExtFunc();
                                                            } else {
                                                                Str *_t1803 = Str_lit("ext_proc", 8ULL);
                                                                (void)_t1803;
                                                                Bool _t1804; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1803); _t1804 = *_hp; free(_hp); }
                                                                (void)_t1804;
                                                                Str_delete(_t1803, &(Bool){1});
                                                                if (_t1804) {
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    Str_delete(_sw1762, &(Bool){1});
                                                                    ;
                                                                    return TokenType_KwExtProc();
                                                                } else {
                                                                    Str *_t1801 = Str_lit("returns", 7ULL);
                                                                    (void)_t1801;
                                                                    Bool _t1802; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1801); _t1802 = *_hp; free(_hp); }
                                                                    (void)_t1802;
                                                                    Str_delete(_t1801, &(Bool){1});
                                                                    if (_t1802) {
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        Str_delete(_sw1762, &(Bool){1});
                                                                        ;
                                                                        return TokenType_KwReturns();
                                                                    } else {
                                                                        Str *_t1799 = Str_lit("throws", 6ULL);
                                                                        (void)_t1799;
                                                                        Bool _t1800; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1799); _t1800 = *_hp; free(_hp); }
                                                                        (void)_t1800;
                                                                        Str_delete(_t1799, &(Bool){1});
                                                                        if (_t1800) {
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            Str_delete(_sw1762, &(Bool){1});
                                                                            ;
                                                                            return TokenType_KwThrows();
                                                                        } else {
                                                                            Str *_t1797 = Str_lit("if", 2ULL);
                                                                            (void)_t1797;
                                                                            Bool _t1798; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1797); _t1798 = *_hp; free(_hp); }
                                                                            (void)_t1798;
                                                                            Str_delete(_t1797, &(Bool){1});
                                                                            if (_t1798) {
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                Str_delete(_sw1762, &(Bool){1});
                                                                                ;
                                                                                return TokenType_KwIf();
                                                                            } else {
                                                                                Str *_t1795 = Str_lit("else", 4ULL);
                                                                                (void)_t1795;
                                                                                Bool _t1796; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1795); _t1796 = *_hp; free(_hp); }
                                                                                (void)_t1796;
                                                                                Str_delete(_t1795, &(Bool){1});
                                                                                if (_t1796) {
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    Str_delete(_sw1762, &(Bool){1});
                                                                                    ;
                                                                                    return TokenType_KwElse();
                                                                                } else {
                                                                                    Str *_t1793 = Str_lit("while", 5ULL);
                                                                                    (void)_t1793;
                                                                                    Bool _t1794; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1793); _t1794 = *_hp; free(_hp); }
                                                                                    (void)_t1794;
                                                                                    Str_delete(_t1793, &(Bool){1});
                                                                                    if (_t1794) {
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        Str_delete(_sw1762, &(Bool){1});
                                                                                        ;
                                                                                        return TokenType_KwWhile();
                                                                                    } else {
                                                                                        Str *_t1791 = Str_lit("for", 3ULL);
                                                                                        (void)_t1791;
                                                                                        Bool _t1792; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1791); _t1792 = *_hp; free(_hp); }
                                                                                        (void)_t1792;
                                                                                        Str_delete(_t1791, &(Bool){1});
                                                                                        if (_t1792) {
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            Str_delete(_sw1762, &(Bool){1});
                                                                                            ;
                                                                                            return TokenType_KwFor();
                                                                                        } else {
                                                                                            Str *_t1789 = Str_lit("in", 2ULL);
                                                                                            (void)_t1789;
                                                                                            Bool _t1790; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1789); _t1790 = *_hp; free(_hp); }
                                                                                            (void)_t1790;
                                                                                            Str_delete(_t1789, &(Bool){1});
                                                                                            if (_t1790) {
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                Str_delete(_sw1762, &(Bool){1});
                                                                                                ;
                                                                                                return TokenType_KwIn();
                                                                                            } else {
                                                                                                Str *_t1787 = Str_lit("switch", 6ULL);
                                                                                                (void)_t1787;
                                                                                                Bool _t1788; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1787); _t1788 = *_hp; free(_hp); }
                                                                                                (void)_t1788;
                                                                                                Str_delete(_t1787, &(Bool){1});
                                                                                                if (_t1788) {
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    Str_delete(_sw1762, &(Bool){1});
                                                                                                    ;
                                                                                                    return TokenType_KwSwitch();
                                                                                                } else {
                                                                                                    Str *_t1785 = Str_lit("match", 5ULL);
                                                                                                    (void)_t1785;
                                                                                                    Bool _t1786; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1785); _t1786 = *_hp; free(_hp); }
                                                                                                    (void)_t1786;
                                                                                                    Str_delete(_t1785, &(Bool){1});
                                                                                                    if (_t1786) {
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        Str_delete(_sw1762, &(Bool){1});
                                                                                                        ;
                                                                                                        return TokenType_KwMatch();
                                                                                                    } else {
                                                                                                        Str *_t1783 = Str_lit("case", 4ULL);
                                                                                                        (void)_t1783;
                                                                                                        Bool _t1784; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1783); _t1784 = *_hp; free(_hp); }
                                                                                                        (void)_t1784;
                                                                                                        Str_delete(_t1783, &(Bool){1});
                                                                                                        if (_t1784) {
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            Str_delete(_sw1762, &(Bool){1});
                                                                                                            ;
                                                                                                            return TokenType_KwCase();
                                                                                                        } else {
                                                                                                            Str *_t1781 = Str_lit("default", 7ULL);
                                                                                                            (void)_t1781;
                                                                                                            Bool _t1782; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1781); _t1782 = *_hp; free(_hp); }
                                                                                                            (void)_t1782;
                                                                                                            Str_delete(_t1781, &(Bool){1});
                                                                                                            if (_t1782) {
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                Str_delete(_sw1762, &(Bool){1});
                                                                                                                ;
                                                                                                                return TokenType_KwDefault();
                                                                                                            } else {
                                                                                                                Str *_t1779 = Str_lit("return", 6ULL);
                                                                                                                (void)_t1779;
                                                                                                                Bool _t1780; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1779); _t1780 = *_hp; free(_hp); }
                                                                                                                (void)_t1780;
                                                                                                                Str_delete(_t1779, &(Bool){1});
                                                                                                                if (_t1780) {
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    Str_delete(_sw1762, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return TokenType_KwReturn();
                                                                                                                } else {
                                                                                                                    Str *_t1777 = Str_lit("throw", 5ULL);
                                                                                                                    (void)_t1777;
                                                                                                                    Bool _t1778; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1777); _t1778 = *_hp; free(_hp); }
                                                                                                                    (void)_t1778;
                                                                                                                    Str_delete(_t1777, &(Bool){1});
                                                                                                                    if (_t1778) {
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        Str_delete(_sw1762, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return TokenType_KwThrow();
                                                                                                                    } else {
                                                                                                                        Str *_t1775 = Str_lit("catch", 5ULL);
                                                                                                                        (void)_t1775;
                                                                                                                        Bool _t1776; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1775); _t1776 = *_hp; free(_hp); }
                                                                                                                        (void)_t1776;
                                                                                                                        Str_delete(_t1775, &(Bool){1});
                                                                                                                        if (_t1776) {
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            Str_delete(_sw1762, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return TokenType_KwCatch();
                                                                                                                        } else {
                                                                                                                            Str *_t1773 = Str_lit("break", 5ULL);
                                                                                                                            (void)_t1773;
                                                                                                                            Bool _t1774; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1773); _t1774 = *_hp; free(_hp); }
                                                                                                                            (void)_t1774;
                                                                                                                            Str_delete(_t1773, &(Bool){1});
                                                                                                                            if (_t1774) {
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                Str_delete(_sw1762, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return TokenType_KwBreak();
                                                                                                                            } else {
                                                                                                                                Str *_t1771 = Str_lit("continue", 8ULL);
                                                                                                                                (void)_t1771;
                                                                                                                                Bool _t1772; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1771); _t1772 = *_hp; free(_hp); }
                                                                                                                                (void)_t1772;
                                                                                                                                Str_delete(_t1771, &(Bool){1});
                                                                                                                                if (_t1772) {
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    Str_delete(_sw1762, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return TokenType_KwContinue();
                                                                                                                                } else {
                                                                                                                                    Str *_t1769 = Str_lit("defer", 5ULL);
                                                                                                                                    (void)_t1769;
                                                                                                                                    Bool _t1770; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1769); _t1770 = *_hp; free(_hp); }
                                                                                                                                    (void)_t1770;
                                                                                                                                    Str_delete(_t1769, &(Bool){1});
                                                                                                                                    if (_t1770) {
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        Str_delete(_sw1762, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return TokenType_KwDefer();
                                                                                                                                    } else {
                                                                                                                                        Str *_t1767 = Str_lit("true", 4ULL);
                                                                                                                                        (void)_t1767;
                                                                                                                                        Bool _t1768; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1767); _t1768 = *_hp; free(_hp); }
                                                                                                                                        (void)_t1768;
                                                                                                                                        Str_delete(_t1767, &(Bool){1});
                                                                                                                                        if (_t1768) {
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            Str_delete(_sw1762, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return TokenType_KwTrue();
                                                                                                                                        } else {
                                                                                                                                            Str *_t1765 = Str_lit("false", 5ULL);
                                                                                                                                            (void)_t1765;
                                                                                                                                            Bool _t1766; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1765); _t1766 = *_hp; free(_hp); }
                                                                                                                                            (void)_t1766;
                                                                                                                                            Str_delete(_t1765, &(Bool){1});
                                                                                                                                            if (_t1766) {
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                Str_delete(_sw1762, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return TokenType_KwFalse();
                                                                                                                                            } else {
                                                                                                                                                Str *_t1763 = Str_lit("NULL", 4ULL);
                                                                                                                                                (void)_t1763;
                                                                                                                                                Bool _t1764; { Bool *_hp = (Bool *)Str_eq(_sw1762, _t1763); _t1764 = *_hp; free(_hp); }
                                                                                                                                                (void)_t1764;
                                                                                                                                                Str_delete(_t1763, &(Bool){1});
                                                                                                                                                if (_t1764) {
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    Str_delete(_sw1762, &(Bool){1});
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
                                                                                                                                                    Str_delete(_sw1762, &(Bool){1});
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
        Str_delete(_sw1762, &(Bool){1});
        ;
    }
}

Vec * tokenize(Str * src, Str * path) {
    (void)src;
    (void)path;
    Str *_t2181 = Str_lit("Token", 5ULL);
    (void)_t2181;
    U64 _t2182; { U64 *_hp = (U64 *)Token_size(); _t2182 = *_hp; free(_hp); }
    (void)_t2182;
    Vec *tokens = Vec_new(_t2181, &(U64){_t2182});
    (void)tokens;
    Str_delete(_t2181, &(Bool){1});
    ;
    U64 *pos = malloc(sizeof(U64));
    *pos = 0;
    (void)pos;
    I64 line = 1;
    (void)line;
    U64 line_start = 0;
    (void)line_start;
    U64 src_len; { U64 *_hp = (U64 *)Str_len(src); src_len = *_hp; free(_hp); }
    (void)src_len;
    while (1) {
        Bool _wcond1833; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1833 = *_hp; free(_hp); }
        (void)_wcond1833;
        if (_wcond1833) {
        } else {
            ;
            break;
        }
        ;
        U8 *c = Str_byte_at(src, pos);
        (void)c;
        U8 _t2127 = 32;
        (void)_t2127;
        U8 _t2128 = 9;
        (void)_t2128;
        Bool _t2129 = U8_eq(DEREF(c), _t2127);
        (void)_t2129;
        ;
        Bool _t2130 = U8_eq(DEREF(c), _t2128);
        (void)_t2130;
        ;
        U8 _t2131 = 13;
        (void)_t2131;
        Bool _t2132 = Bool_or(_t2129, _t2130);
        (void)_t2132;
        ;
        ;
        Bool _t2133 = U8_eq(DEREF(c), _t2131);
        (void)_t2133;
        ;
        U8 _t2134 = 59;
        (void)_t2134;
        Bool _t2135 = Bool_or(_t2132, _t2133);
        (void)_t2135;
        ;
        ;
        Bool _t2136 = U8_eq(DEREF(c), _t2134);
        (void)_t2136;
        ;
        Bool _t2137 = Bool_or(_t2135, _t2136);
        (void)_t2137;
        ;
        ;
        if (_t2137) {
            U64 _t1834 = U64_inc(DEREF(pos));
            (void)_t1834;
            *pos = _t1834;
            ;
            ;
            continue;
        }
        ;
        U8 _t2138 = 10;
        (void)_t2138;
        Bool _t2139 = U8_eq(DEREF(c), _t2138);
        (void)_t2139;
        ;
        if (_t2139) {
            U64 _t1835 = U64_inc(DEREF(pos));
            (void)_t1835;
            *pos = _t1835;
            ;
            I64 _t1836 = 1;
            (void)_t1836;
            I64 _t1837 = I64_add(line, _t1836);
            (void)_t1837;
            ;
            line = _t1837;
            ;
            U64 _t1838 = U64_clone(pos);
            (void)_t1838;
            line_start = _t1838;
            ;
            ;
            continue;
        }
        ;
        U64 _t2140 = U64_sub(DEREF(pos), line_start);
        (void)_t2140;
        U64 _t2141 = 1;
        (void)_t2141;
        U64 _t2142 = U64_add(_t2140, _t2141);
        (void)_t2142;
        ;
        ;
        I64 col = U64_to_i64(_t2142);
        (void)col;
        ;
        U64 start = U64_clone(pos);
        (void)start;
        U8 _t2143 = 35;
        (void)_t2143;
        Bool _t2144 = U8_eq(DEREF(c), _t2143);
        (void)_t2144;
        ;
        if (_t2144) {
            while (1) {
                Bool _wcond1839; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1839 = *_hp; free(_hp); }
                (void)_wcond1839;
                if (_wcond1839) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1840 = Str_byte_at(src, pos);
                (void)_t1840;
                U8 _t1841 = 10;
                (void)_t1841;
                Bool _t1842 = U8_eq(DEREF(_t1840), _t1841);
                (void)_t1842;
                ;
                if (_t1842) {
                    ;
                    break;
                }
                ;
                U64 _t1843 = U64_inc(DEREF(pos));
                (void)_t1843;
                *pos = _t1843;
                ;
            }
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t2145 = 47;
        (void)_t2145;
        U64 _t2146 = 1;
        (void)_t2146;
        U64 _t2147 = U64_add(DEREF(pos), _t2146);
        (void)_t2147;
        ;
        Bool _t2148 = U8_eq(DEREF(c), _t2145);
        (void)_t2148;
        ;
        Bool _t2149; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2147}, &(U64){src_len}); _t2149 = *_hp; free(_hp); }
        (void)_t2149;
        ;
        Bool _t2150 = Bool_and(_t2148, _t2149);
        (void)_t2150;
        ;
        ;
        if (_t2150) {
            U64 _t1902 = 1;
            (void)_t1902;
            U64 *_t1903 = malloc(sizeof(U64)); *_t1903 = U64_add(DEREF(pos), _t1902);
            (void)_t1903;
            ;
            U8 *c2 = Str_byte_at(src, _t1903);
            (void)c2;
            U8 _t1904 = 47;
            (void)_t1904;
            Bool _t1905 = U8_eq(DEREF(c2), _t1904);
            (void)_t1905;
            ;
            if (_t1905) {
                while (1) {
                    Bool _wcond1844; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1844 = *_hp; free(_hp); }
                    (void)_wcond1844;
                    if (_wcond1844) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U8 *_t1845 = Str_byte_at(src, pos);
                    (void)_t1845;
                    U8 _t1846 = 10;
                    (void)_t1846;
                    Bool _t1847 = U8_eq(DEREF(_t1845), _t1846);
                    (void)_t1847;
                    ;
                    if (_t1847) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1848 = U64_inc(DEREF(pos));
                    (void)_t1848;
                    *pos = _t1848;
                    ;
                }
                U64_delete(_t1903, &(Bool){1});
                ;
                ;
                ;
                ;
                continue;
            }
            ;
            U8 _t1906 = 42;
            (void)_t1906;
            Bool _t1907 = U8_eq(DEREF(c2), _t1906);
            (void)_t1907;
            U64_delete(_t1903, &(Bool){1});
            ;
            if (_t1907) {
                U64 _t1898 = 2;
                (void)_t1898;
                U64 _t1899 = U64_add(DEREF(pos), _t1898);
                (void)_t1899;
                ;
                *pos = _t1899;
                ;
                I64 depth = 1;
                (void)depth;
                while (1) {
                    Bool _wcond1849; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1849 = *_hp; free(_hp); }
                    (void)_wcond1849;
                    if (_wcond1849) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    I64 _t1874 = 0;
                    (void)_t1874;
                    Bool _t1875; { Bool *_hp = (Bool *)I64_lte(&(I64){depth}, &(I64){_t1874}); _t1875 = *_hp; free(_hp); }
                    (void)_t1875;
                    ;
                    if (_t1875) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1876 = 1;
                    (void)_t1876;
                    U64 _t1877 = U64_add(DEREF(pos), _t1876);
                    (void)_t1877;
                    ;
                    Bool _t1878; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1877}, &(U64){src_len}); _t1878 = *_hp; free(_hp); }
                    (void)_t1878;
                    ;
                    if (_t1878) {
                        U8 *b1 = Str_byte_at(src, pos);
                        (void)b1;
                        U64 _t1858 = 1;
                        (void)_t1858;
                        U64 *_t1859 = malloc(sizeof(U64)); *_t1859 = U64_add(DEREF(pos), _t1858);
                        (void)_t1859;
                        ;
                        U8 *b2 = Str_byte_at(src, _t1859);
                        (void)b2;
                        U8 _t1860 = 47;
                        (void)_t1860;
                        U8 _t1861 = 42;
                        (void)_t1861;
                        Bool _t1862 = U8_eq(DEREF(b1), _t1860);
                        (void)_t1862;
                        ;
                        Bool _t1863 = U8_eq(DEREF(b2), _t1861);
                        (void)_t1863;
                        ;
                        Bool _t1864 = Bool_and(_t1862, _t1863);
                        (void)_t1864;
                        ;
                        ;
                        if (_t1864) {
                            I64 _t1850 = 1;
                            (void)_t1850;
                            I64 _t1851 = I64_add(depth, _t1850);
                            (void)_t1851;
                            ;
                            depth = _t1851;
                            ;
                            U64 _t1852 = 2;
                            (void)_t1852;
                            U64 _t1853 = U64_add(DEREF(pos), _t1852);
                            (void)_t1853;
                            ;
                            *pos = _t1853;
                            ;
                            U64_delete(_t1859, &(Bool){1});
                            ;
                            ;
                            continue;
                        }
                        ;
                        U8 _t1865 = 42;
                        (void)_t1865;
                        U8 _t1866 = 47;
                        (void)_t1866;
                        Bool _t1867 = U8_eq(DEREF(b1), _t1865);
                        (void)_t1867;
                        ;
                        Bool _t1868 = U8_eq(DEREF(b2), _t1866);
                        (void)_t1868;
                        U64_delete(_t1859, &(Bool){1});
                        ;
                        Bool _t1869 = Bool_and(_t1867, _t1868);
                        (void)_t1869;
                        ;
                        ;
                        if (_t1869) {
                            I64 _t1854 = 1;
                            (void)_t1854;
                            I64 _t1855 = I64_sub(depth, _t1854);
                            (void)_t1855;
                            ;
                            depth = _t1855;
                            ;
                            U64 _t1856 = 2;
                            (void)_t1856;
                            U64 _t1857 = U64_add(DEREF(pos), _t1856);
                            (void)_t1857;
                            ;
                            *pos = _t1857;
                            ;
                            ;
                            ;
                            continue;
                        }
                        ;
                    }
                    ;
                    U8 *_t1879 = Str_byte_at(src, pos);
                    (void)_t1879;
                    U8 _t1880 = 10;
                    (void)_t1880;
                    Bool _t1881 = U8_eq(DEREF(_t1879), _t1880);
                    (void)_t1881;
                    ;
                    if (_t1881) {
                        I64 _t1870 = 1;
                        (void)_t1870;
                        I64 _t1871 = I64_add(line, _t1870);
                        (void)_t1871;
                        ;
                        line = _t1871;
                        ;
                        U64 _t1872 = 1;
                        (void)_t1872;
                        U64 _t1873 = U64_add(DEREF(pos), _t1872);
                        (void)_t1873;
                        ;
                        line_start = _t1873;
                        ;
                    }
                    ;
                    U64 _t1882 = U64_inc(DEREF(pos));
                    (void)_t1882;
                    *pos = _t1882;
                    ;
                }
                I64 _t1900 = 0;
                (void)_t1900;
                Bool _t1901; { Bool *_hp = (Bool *)I64_gt(&(I64){depth}, &(I64){_t1900}); _t1901 = *_hp; free(_hp); }
                (void)_t1901;
                ;
                ;
                if (_t1901) {
                    Str *_t1883 = Str_lit("Str", 3ULL);
                    (void)_t1883;
                    U64 _t1884; { U64 *_hp = (U64 *)Str_size(); _t1884 = *_hp; free(_hp); }
                    (void)_t1884;
                    U64 _t1885 = 6;
                    (void)_t1885;
                    Array *_va20 = Array_new(_t1883, &(U64){_t1884}, &(U64){_t1885});
                    (void)_va20;
                    Str_delete(_t1883, &(Bool){1});
                    ;
                    ;
                    U64 _t1886 = 0;
                    (void)_t1886;
                    Str *_t1887 = Str_clone(path);
                    (void)_t1887;
                    Array_set(_va20, &(U64){_t1886}, _t1887);
                    ;
                    U64 _t1888 = 1;
                    (void)_t1888;
                    Str *_t1889 = Str_lit(":", 1ULL);
                    (void)_t1889;
                    Array_set(_va20, &(U64){_t1888}, _t1889);
                    ;
                    U64 _t1890 = 2;
                    (void)_t1890;
                    Str *_t1891 = I64_to_str(&(I64){line});
                    (void)_t1891;
                    Array_set(_va20, &(U64){_t1890}, _t1891);
                    ;
                    U64 _t1892 = 3;
                    (void)_t1892;
                    Str *_t1893 = Str_lit(":", 1ULL);
                    (void)_t1893;
                    Array_set(_va20, &(U64){_t1892}, _t1893);
                    ;
                    U64 _t1894 = 4;
                    (void)_t1894;
                    Str *_t1895 = I64_to_str(&(I64){col});
                    (void)_t1895;
                    Array_set(_va20, &(U64){_t1894}, _t1895);
                    ;
                    U64 _t1896 = 5;
                    (void)_t1896;
                    Str *_t1897 = Str_lit(": error: unterminated comment", 29ULL);
                    (void)_t1897;
                    Array_set(_va20, &(U64){_t1896}, _t1897);
                    ;
                    println(_va20);
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
        Bool _t2151; { Bool *_hp = (Bool *)is_digit(c); _t2151 = *_hp; free(_hp); }
        (void)_t2151;
        if (_t2151) {
            while (1) {
                Bool _wcond1908; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1908 = *_hp; free(_hp); }
                (void)_wcond1908;
                if (_wcond1908) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1909 = Str_byte_at(src, pos);
                (void)_t1909;
                Bool _t1910; { Bool *_hp = (Bool *)is_digit(_t1909); _t1910 = *_hp; free(_hp); }
                (void)_t1910;
                Bool _t1911 = Bool_not(_t1910);
                (void)_t1911;
                ;
                if (_t1911) {
                    ;
                    break;
                }
                ;
                U64 _t1912 = U64_inc(DEREF(pos));
                (void)_t1912;
                *pos = _t1912;
                ;
            }
            U64 _t1927 = 1;
            (void)_t1927;
            U64 _t1928 = U64_add(DEREF(pos), _t1927);
            (void)_t1928;
            ;
            Bool _t1929; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1928}, &(U64){src_len}); _t1929 = *_hp; free(_hp); }
            (void)_t1929;
            ;
            if (_t1929) {
                U8 *_t1919 = Str_byte_at(src, pos);
                (void)_t1919;
                U8 _t1920 = 46;
                (void)_t1920;
                U64 _t1921 = 1;
                (void)_t1921;
                U64 *_t1922 = malloc(sizeof(U64)); *_t1922 = U64_add(DEREF(pos), _t1921);
                (void)_t1922;
                ;
                U8 *_t1923 = Str_byte_at(src, _t1922);
                (void)_t1923;
                Bool _t1924 = U8_eq(DEREF(_t1919), _t1920);
                (void)_t1924;
                ;
                Bool _t1925; { Bool *_hp = (Bool *)is_digit(_t1923); _t1925 = *_hp; free(_hp); }
                (void)_t1925;
                U64_delete(_t1922, &(Bool){1});
                Bool _t1926 = Bool_and(_t1924, _t1925);
                (void)_t1926;
                ;
                ;
                if (_t1926) {
                    U64 _t1918 = U64_inc(DEREF(pos));
                    (void)_t1918;
                    *pos = _t1918;
                    ;
                    while (1) {
                        Bool _wcond1913; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1913 = *_hp; free(_hp); }
                        (void)_wcond1913;
                        if (_wcond1913) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U8 *_t1914 = Str_byte_at(src, pos);
                        (void)_t1914;
                        Bool _t1915; { Bool *_hp = (Bool *)is_digit(_t1914); _t1915 = *_hp; free(_hp); }
                        (void)_t1915;
                        Bool _t1916 = Bool_not(_t1915);
                        (void)_t1916;
                        ;
                        if (_t1916) {
                            ;
                            break;
                        }
                        ;
                        U64 _t1917 = U64_inc(DEREF(pos));
                        (void)_t1917;
                        *pos = _t1917;
                        ;
                    }
                }
                ;
            }
            ;
            U64 _t1930 = U64_sub(DEREF(pos), start);
            (void)_t1930;
            I64 _t1931 = I64_clone(&(I64){col});
            (void)_t1931;
            Token *_t1932 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(TokenType_Number()); _t1932->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1930}); _t1932->text = *_ca; free(_ca); }
            _t1932->line = I64_clone(&(I64){line});
            _t1932->col = _t1931;
            (void)_t1932;
            ;
            ;
            Vec_push(tokens, _t1932);
            ;
            ;
            ;
            continue;
        }
        ;
        Bool _t2152; { Bool *_hp = (Bool *)is_alpha(c); _t2152 = *_hp; free(_hp); }
        (void)_t2152;
        if (_t2152) {
            while (1) {
                Bool _wcond1933; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1933 = *_hp; free(_hp); }
                (void)_wcond1933;
                if (_wcond1933) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1934 = Str_byte_at(src, pos);
                (void)_t1934;
                Bool _t1935; { Bool *_hp = (Bool *)is_alnum(_t1934); _t1935 = *_hp; free(_hp); }
                (void)_t1935;
                Bool _t1936 = Bool_not(_t1935);
                (void)_t1936;
                ;
                if (_t1936) {
                    ;
                    break;
                }
                ;
                U64 _t1937 = U64_inc(DEREF(pos));
                (void)_t1937;
                *pos = _t1937;
                ;
            }
            U64 _t1938 = U64_sub(DEREF(pos), start);
            (void)_t1938;
            Str *word = Str_substr(src, &(U64){start}, &(U64){_t1938});
            (void)word;
            ;
            TokenType *type = lookup_keyword(word);
            (void)type;
            I64 _t1939 = I64_clone(&(I64){line});
            (void)_t1939;
            I64 _t1940 = I64_clone(&(I64){col});
            (void)_t1940;
            Token *_t1941 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(type); _t1941->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(word); _t1941->text = *_ca; free(_ca); }
            _t1941->line = _t1939;
            _t1941->col = _t1940;
            (void)_t1941;
            ;
            ;
            TokenType_delete(type, &(Bool){1});
            Str_delete(word, &(Bool){1});
            Vec_push(tokens, _t1941);
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t2153 = 34;
        (void)_t2153;
        Bool _t2154 = U8_eq(DEREF(c), _t2153);
        (void)_t2154;
        ;
        if (_t2154) {
            U64 _t1988 = U64_inc(DEREF(pos));
            (void)_t1988;
            *pos = _t1988;
            ;
            while (1) {
                Bool _wcond1942; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1942 = *_hp; free(_hp); }
                (void)_wcond1942;
                if (_wcond1942) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1948 = Str_byte_at(src, pos);
                (void)_t1948;
                U8 _t1949 = 34;
                (void)_t1949;
                Bool _t1950 = U8_eq(DEREF(_t1948), _t1949);
                (void)_t1950;
                ;
                if (_t1950) {
                    ;
                    break;
                }
                ;
                U8 *_t1951 = Str_byte_at(src, pos);
                (void)_t1951;
                U8 _t1952 = 92;
                (void)_t1952;
                U64 _t1953 = 1;
                (void)_t1953;
                U64 _t1954 = U64_add(DEREF(pos), _t1953);
                (void)_t1954;
                ;
                Bool _t1955 = U8_eq(DEREF(_t1951), _t1952);
                (void)_t1955;
                ;
                Bool _t1956; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1954}, &(U64){src_len}); _t1956 = *_hp; free(_hp); }
                (void)_t1956;
                ;
                Bool _t1957 = Bool_and(_t1955, _t1956);
                (void)_t1957;
                ;
                ;
                if (_t1957) {
                    U64 _t1943 = U64_inc(DEREF(pos));
                    (void)_t1943;
                    *pos = _t1943;
                    ;
                }
                ;
                U8 *_t1958 = Str_byte_at(src, pos);
                (void)_t1958;
                U8 _t1959 = 10;
                (void)_t1959;
                Bool _t1960 = U8_eq(DEREF(_t1958), _t1959);
                (void)_t1960;
                ;
                if (_t1960) {
                    I64 _t1944 = 1;
                    (void)_t1944;
                    I64 _t1945 = I64_add(line, _t1944);
                    (void)_t1945;
                    ;
                    line = _t1945;
                    ;
                    U64 _t1946 = 1;
                    (void)_t1946;
                    U64 _t1947 = U64_add(DEREF(pos), _t1946);
                    (void)_t1947;
                    ;
                    line_start = _t1947;
                    ;
                }
                ;
                U64 _t1961 = U64_inc(DEREF(pos));
                (void)_t1961;
                *pos = _t1961;
                ;
            }
            U8 *_t1989 = Str_byte_at(src, pos);
            (void)_t1989;
            U8 _t1990 = 34;
            (void)_t1990;
            Bool _t1991; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t1991 = *_hp; free(_hp); }
            (void)_t1991;
            Bool _t1992 = U8_eq(DEREF(_t1989), _t1990);
            (void)_t1992;
            ;
            Bool _t1993 = Bool_and(_t1991, _t1992);
            (void)_t1993;
            ;
            ;
            if (_t1993) {
                U64 _t1962 = U64_inc(DEREF(pos));
                (void)_t1962;
                *pos = _t1962;
                ;
                U64 _t1963 = 1;
                (void)_t1963;
                U64 _t1964 = U64_sub(DEREF(pos), start);
                (void)_t1964;
                U64 _t1965 = 2;
                (void)_t1965;
                U64 _t1966 = U64_add(start, _t1963);
                (void)_t1966;
                ;
                U64 _t1967 = U64_sub(_t1964, _t1965);
                (void)_t1967;
                ;
                ;
                I64 _t1968 = I64_clone(&(I64){col});
                (void)_t1968;
                Token *_t1969 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_StringTok()); _t1969->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){_t1966}, &(U64){_t1967}); _t1969->text = *_ca; free(_ca); }
                _t1969->line = I64_clone(&(I64){line});
                _t1969->col = _t1968;
                (void)_t1969;
                ;
                ;
                ;
                Vec_push(tokens, _t1969);
            } else {
                Str *_t1970 = Str_lit("Str", 3ULL);
                (void)_t1970;
                U64 _t1971; { U64 *_hp = (U64 *)Str_size(); _t1971 = *_hp; free(_hp); }
                (void)_t1971;
                U64 _t1972 = 6;
                (void)_t1972;
                Array *_va21 = Array_new(_t1970, &(U64){_t1971}, &(U64){_t1972});
                (void)_va21;
                Str_delete(_t1970, &(Bool){1});
                ;
                ;
                U64 _t1973 = 0;
                (void)_t1973;
                Str *_t1974 = Str_clone(path);
                (void)_t1974;
                Array_set(_va21, &(U64){_t1973}, _t1974);
                ;
                U64 _t1975 = 1;
                (void)_t1975;
                Str *_t1976 = Str_lit(":", 1ULL);
                (void)_t1976;
                Array_set(_va21, &(U64){_t1975}, _t1976);
                ;
                U64 _t1977 = 2;
                (void)_t1977;
                Str *_t1978 = I64_to_str(&(I64){line});
                (void)_t1978;
                Array_set(_va21, &(U64){_t1977}, _t1978);
                ;
                U64 _t1979 = 3;
                (void)_t1979;
                Str *_t1980 = Str_lit(":", 1ULL);
                (void)_t1980;
                Array_set(_va21, &(U64){_t1979}, _t1980);
                ;
                U64 _t1981 = 4;
                (void)_t1981;
                Str *_t1982 = I64_to_str(&(I64){col});
                (void)_t1982;
                Array_set(_va21, &(U64){_t1981}, _t1982);
                ;
                U64 _t1983 = 5;
                (void)_t1983;
                Str *_t1984 = Str_lit(": error: unterminated string", 28ULL);
                (void)_t1984;
                Array_set(_va21, &(U64){_t1983}, _t1984);
                ;
                println(_va21);
                U64 _t1985 = U64_sub(DEREF(pos), start);
                (void)_t1985;
                I64 _t1986 = I64_clone(&(I64){col});
                (void)_t1986;
                Token *_t1987 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1987->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1985}); _t1987->text = *_ca; free(_ca); }
                _t1987->line = I64_clone(&(I64){line});
                _t1987->col = _t1986;
                (void)_t1987;
                ;
                ;
                Vec_push(tokens, _t1987);
            }
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t2155 = 39;
        (void)_t2155;
        Bool _t2156 = U8_eq(DEREF(c), _t2155);
        (void)_t2156;
        ;
        if (_t2156) {
            U64 _t2017 = U64_inc(DEREF(pos));
            (void)_t2017;
            *pos = _t2017;
            ;
            U64 ch_start = U64_clone(pos);
            (void)ch_start;
            U8 *_t2018 = Str_byte_at(src, pos);
            (void)_t2018;
            U8 _t2019 = 92;
            (void)_t2019;
            U64 _t2020 = 1;
            (void)_t2020;
            U64 _t2021 = U64_add(DEREF(pos), _t2020);
            (void)_t2021;
            ;
            Bool _t2022 = U8_eq(DEREF(_t2018), _t2019);
            (void)_t2022;
            ;
            Bool _t2023; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2021}, &(U64){src_len}); _t2023 = *_hp; free(_hp); }
            (void)_t2023;
            ;
            Bool _t2024; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2024 = *_hp; free(_hp); }
            (void)_t2024;
            Bool _t2025 = Bool_and(_t2022, _t2023);
            (void)_t2025;
            ;
            ;
            Bool _t2026 = Bool_and(_t2024, _t2025);
            (void)_t2026;
            ;
            ;
            if (_t2026) {
                U64 _t1994 = U64_inc(DEREF(pos));
                (void)_t1994;
                *pos = _t1994;
                ;
            }
            ;
            U64 _t2027 = U64_inc(DEREF(pos));
            (void)_t2027;
            *pos = _t2027;
            ;
            U8 *_t2028 = Str_byte_at(src, pos);
            (void)_t2028;
            U8 _t2029 = 39;
            (void)_t2029;
            Bool _t2030; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2030 = *_hp; free(_hp); }
            (void)_t2030;
            Bool _t2031 = U8_eq(DEREF(_t2028), _t2029);
            (void)_t2031;
            ;
            Bool _t2032 = Bool_and(_t2030, _t2031);
            (void)_t2032;
            ;
            ;
            if (_t2032) {
                U64 _t1995 = U64_sub(DEREF(pos), ch_start);
                (void)_t1995;
                I64 _t1996 = I64_clone(&(I64){col});
                (void)_t1996;
                Token *_t1997 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Char()); _t1997->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){ch_start}, &(U64){_t1995}); _t1997->text = *_ca; free(_ca); }
                _t1997->line = I64_clone(&(I64){line});
                _t1997->col = _t1996;
                (void)_t1997;
                ;
                ;
                Vec_push(tokens, _t1997);
                U64 _t1998 = U64_inc(DEREF(pos));
                (void)_t1998;
                *pos = _t1998;
                ;
            } else {
                Str *_t1999 = Str_lit("Str", 3ULL);
                (void)_t1999;
                U64 _t2000; { U64 *_hp = (U64 *)Str_size(); _t2000 = *_hp; free(_hp); }
                (void)_t2000;
                U64 _t2001 = 6;
                (void)_t2001;
                Array *_va22 = Array_new(_t1999, &(U64){_t2000}, &(U64){_t2001});
                (void)_va22;
                Str_delete(_t1999, &(Bool){1});
                ;
                ;
                U64 _t2002 = 0;
                (void)_t2002;
                Str *_t2003 = Str_clone(path);
                (void)_t2003;
                Array_set(_va22, &(U64){_t2002}, _t2003);
                ;
                U64 _t2004 = 1;
                (void)_t2004;
                Str *_t2005 = Str_lit(":", 1ULL);
                (void)_t2005;
                Array_set(_va22, &(U64){_t2004}, _t2005);
                ;
                U64 _t2006 = 2;
                (void)_t2006;
                Str *_t2007 = I64_to_str(&(I64){line});
                (void)_t2007;
                Array_set(_va22, &(U64){_t2006}, _t2007);
                ;
                U64 _t2008 = 3;
                (void)_t2008;
                Str *_t2009 = Str_lit(":", 1ULL);
                (void)_t2009;
                Array_set(_va22, &(U64){_t2008}, _t2009);
                ;
                U64 _t2010 = 4;
                (void)_t2010;
                Str *_t2011 = I64_to_str(&(I64){col});
                (void)_t2011;
                Array_set(_va22, &(U64){_t2010}, _t2011);
                ;
                U64 _t2012 = 5;
                (void)_t2012;
                Str *_t2013 = Str_lit(": error: unterminated character literal", 39ULL);
                (void)_t2013;
                Array_set(_va22, &(U64){_t2012}, _t2013);
                ;
                println(_va22);
                U64 _t2014 = U64_sub(DEREF(pos), start);
                (void)_t2014;
                I64 _t2015 = I64_clone(&(I64){col});
                (void)_t2015;
                Token *_t2016 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2016->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t2014}); _t2016->text = *_ca; free(_ca); }
                _t2016->line = I64_clone(&(I64){line});
                _t2016->col = _t2015;
                (void)_t2016;
                ;
                ;
                Vec_push(tokens, _t2016);
            }
            ;
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U64 _t2157 = 1;
        (void)_t2157;
        U64 _t2158 = U64_add(DEREF(pos), _t2157);
        (void)_t2158;
        ;
        Bool _t2159; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2158}, &(U64){src_len}); _t2159 = *_hp; free(_hp); }
        (void)_t2159;
        ;
        if (_t2159) {
            U64 _t2076 = 1;
            (void)_t2076;
            U64 *_t2077 = malloc(sizeof(U64)); *_t2077 = U64_add(DEREF(pos), _t2076);
            (void)_t2077;
            ;
            U8 *c2 = Str_byte_at(src, _t2077);
            (void)c2;
            TokenType *two = TokenType_clone(TokenType_Eof());
            (void)two;
            U8 _t2078 = 58;
            (void)_t2078;
            U8 _t2079 = 61;
            (void)_t2079;
            Bool _t2080 = U8_eq(DEREF(c), _t2078);
            (void)_t2080;
            ;
            Bool _t2081 = U8_eq(DEREF(c2), _t2079);
            (void)_t2081;
            ;
            Bool _t2082 = Bool_and(_t2080, _t2081);
            (void)_t2082;
            ;
            ;
            if (_t2082) {
                two = TokenType_clone(TokenType_ColonEq());
            } else {
                U8 _t2065 = 61;
                (void)_t2065;
                U8 _t2066 = 61;
                (void)_t2066;
                Bool _t2067 = U8_eq(DEREF(c), _t2065);
                (void)_t2067;
                ;
                Bool _t2068 = U8_eq(DEREF(c2), _t2066);
                (void)_t2068;
                ;
                Bool _t2069 = Bool_and(_t2067, _t2068);
                (void)_t2069;
                ;
                ;
                if (_t2069) {
                    two = TokenType_clone(TokenType_EqEq());
                } else {
                    U8 _t2060 = 33;
                    (void)_t2060;
                    U8 _t2061 = 61;
                    (void)_t2061;
                    Bool _t2062 = U8_eq(DEREF(c), _t2060);
                    (void)_t2062;
                    ;
                    Bool _t2063 = U8_eq(DEREF(c2), _t2061);
                    (void)_t2063;
                    ;
                    Bool _t2064 = Bool_and(_t2062, _t2063);
                    (void)_t2064;
                    ;
                    ;
                    if (_t2064) {
                        two = TokenType_clone(TokenType_Neq());
                    } else {
                        U8 _t2055 = 60;
                        (void)_t2055;
                        U8 _t2056 = 61;
                        (void)_t2056;
                        Bool _t2057 = U8_eq(DEREF(c), _t2055);
                        (void)_t2057;
                        ;
                        Bool _t2058 = U8_eq(DEREF(c2), _t2056);
                        (void)_t2058;
                        ;
                        Bool _t2059 = Bool_and(_t2057, _t2058);
                        (void)_t2059;
                        ;
                        ;
                        if (_t2059) {
                            two = TokenType_clone(TokenType_LtEq());
                        } else {
                            U8 _t2050 = 62;
                            (void)_t2050;
                            U8 _t2051 = 61;
                            (void)_t2051;
                            Bool _t2052 = U8_eq(DEREF(c), _t2050);
                            (void)_t2052;
                            ;
                            Bool _t2053 = U8_eq(DEREF(c2), _t2051);
                            (void)_t2053;
                            ;
                            Bool _t2054 = Bool_and(_t2052, _t2053);
                            (void)_t2054;
                            ;
                            ;
                            if (_t2054) {
                                two = TokenType_clone(TokenType_GtEq());
                            } else {
                                U8 _t2045 = 46;
                                (void)_t2045;
                                U8 _t2046 = 46;
                                (void)_t2046;
                                Bool _t2047 = U8_eq(DEREF(c), _t2045);
                                (void)_t2047;
                                ;
                                Bool _t2048 = U8_eq(DEREF(c2), _t2046);
                                (void)_t2048;
                                ;
                                Bool _t2049 = Bool_and(_t2047, _t2048);
                                (void)_t2049;
                                ;
                                ;
                                if (_t2049) {
                                    U64 _t2042 = 2;
                                    (void)_t2042;
                                    U64 _t2043 = U64_add(DEREF(pos), _t2042);
                                    (void)_t2043;
                                    ;
                                    Bool _t2044; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2043}, &(U64){src_len}); _t2044 = *_hp; free(_hp); }
                                    (void)_t2044;
                                    ;
                                    if (_t2044) {
                                        U64 _t2038 = 2;
                                        (void)_t2038;
                                        U64 *_t2039 = malloc(sizeof(U64)); *_t2039 = U64_add(DEREF(pos), _t2038);
                                        (void)_t2039;
                                        ;
                                        U8 *c3 = Str_byte_at(src, _t2039);
                                        (void)c3;
                                        U8 _t2040 = 46;
                                        (void)_t2040;
                                        Bool _t2041 = U8_eq(DEREF(c3), _t2040);
                                        (void)_t2041;
                                        U64_delete(_t2039, &(Bool){1});
                                        ;
                                        if (_t2041) {
                                            U64 _t2033 = 3;
                                            (void)_t2033;
                                            I64 _t2034 = I64_clone(&(I64){col});
                                            (void)_t2034;
                                            Token *_t2035 = malloc(sizeof(Token));
                                            { TokenType *_ca = TokenType_clone(TokenType_DotDotDot()); _t2035->type = *_ca; free(_ca); }
                                            { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t2033}); _t2035->text = *_ca; free(_ca); }
                                            _t2035->line = I64_clone(&(I64){line});
                                            _t2035->col = _t2034;
                                            (void)_t2035;
                                            ;
                                            ;
                                            Vec_push(tokens, _t2035);
                                            U64 _t2036 = 3;
                                            (void)_t2036;
                                            U64 _t2037 = U64_add(DEREF(pos), _t2036);
                                            (void)_t2037;
                                            ;
                                            *pos = _t2037;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            U64_delete(_t2077, &(Bool){1});
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
            U64_delete(_t2077, &(Bool){1});
            ;
            Bool _t2083; { Bool *_hp = (Bool *)TokenType_eq(two, TokenType_Eof()); _t2083 = *_hp; free(_hp); }
            (void)_t2083;
            Bool _t2084 = Bool_not(_t2083);
            (void)_t2084;
            ;
            if (_t2084) {
                U64 _t2070 = 2;
                (void)_t2070;
                I64 _t2071 = I64_clone(&(I64){line});
                (void)_t2071;
                I64 _t2072 = I64_clone(&(I64){col});
                (void)_t2072;
                Token *_t2073 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(two); _t2073->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t2070}); _t2073->text = *_ca; free(_ca); }
                _t2073->line = _t2071;
                _t2073->col = _t2072;
                (void)_t2073;
                ;
                ;
                ;
                Vec_push(tokens, _t2073);
                U64 _t2074 = 2;
                (void)_t2074;
                U64 _t2075 = U64_add(DEREF(pos), _t2074);
                (void)_t2075;
                ;
                *pos = _t2075;
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
            U8 _sw2085 = U8_clone(c);
            (void)_sw2085;
            U8 _t2120 = 40;
            (void)_t2120;
            Bool _t2121 = U8_eq(_sw2085, _t2120);
            (void)_t2121;
            ;
            if (_t2121) {
                single = TokenType_clone(TokenType_LParen());
            } else {
                U8 _t2118 = 41;
                (void)_t2118;
                Bool _t2119 = U8_eq(_sw2085, _t2118);
                (void)_t2119;
                ;
                if (_t2119) {
                    single = TokenType_clone(TokenType_RParen());
                } else {
                    U8 _t2116 = 123;
                    (void)_t2116;
                    Bool _t2117 = U8_eq(_sw2085, _t2116);
                    (void)_t2117;
                    ;
                    if (_t2117) {
                        single = TokenType_clone(TokenType_LBrace());
                    } else {
                        U8 _t2114 = 125;
                        (void)_t2114;
                        Bool _t2115 = U8_eq(_sw2085, _t2114);
                        (void)_t2115;
                        ;
                        if (_t2115) {
                            single = TokenType_clone(TokenType_RBrace());
                        } else {
                            U8 _t2112 = 91;
                            (void)_t2112;
                            Bool _t2113 = U8_eq(_sw2085, _t2112);
                            (void)_t2113;
                            ;
                            if (_t2113) {
                                single = TokenType_clone(TokenType_LBracket());
                            } else {
                                U8 _t2110 = 93;
                                (void)_t2110;
                                Bool _t2111 = U8_eq(_sw2085, _t2110);
                                (void)_t2111;
                                ;
                                if (_t2111) {
                                    single = TokenType_clone(TokenType_RBracket());
                                } else {
                                    U8 _t2108 = 44;
                                    (void)_t2108;
                                    Bool _t2109 = U8_eq(_sw2085, _t2108);
                                    (void)_t2109;
                                    ;
                                    if (_t2109) {
                                        single = TokenType_clone(TokenType_Comma());
                                    } else {
                                        U8 _t2106 = 58;
                                        (void)_t2106;
                                        Bool _t2107 = U8_eq(_sw2085, _t2106);
                                        (void)_t2107;
                                        ;
                                        if (_t2107) {
                                            single = TokenType_clone(TokenType_Colon());
                                        } else {
                                            U8 _t2104 = 46;
                                            (void)_t2104;
                                            Bool _t2105 = U8_eq(_sw2085, _t2104);
                                            (void)_t2105;
                                            ;
                                            if (_t2105) {
                                                single = TokenType_clone(TokenType_Dot());
                                            } else {
                                                U8 _t2102 = 63;
                                                (void)_t2102;
                                                Bool _t2103 = U8_eq(_sw2085, _t2102);
                                                (void)_t2103;
                                                ;
                                                if (_t2103) {
                                                    single = TokenType_clone(TokenType_Question());
                                                } else {
                                                    U8 _t2100 = 33;
                                                    (void)_t2100;
                                                    Bool _t2101 = U8_eq(_sw2085, _t2100);
                                                    (void)_t2101;
                                                    ;
                                                    if (_t2101) {
                                                        single = TokenType_clone(TokenType_Bang());
                                                    } else {
                                                        U8 _t2098 = 43;
                                                        (void)_t2098;
                                                        Bool _t2099 = U8_eq(_sw2085, _t2098);
                                                        (void)_t2099;
                                                        ;
                                                        if (_t2099) {
                                                            single = TokenType_clone(TokenType_Plus());
                                                        } else {
                                                            U8 _t2096 = 45;
                                                            (void)_t2096;
                                                            Bool _t2097 = U8_eq(_sw2085, _t2096);
                                                            (void)_t2097;
                                                            ;
                                                            if (_t2097) {
                                                                single = TokenType_clone(TokenType_Minus());
                                                            } else {
                                                                U8 _t2094 = 42;
                                                                (void)_t2094;
                                                                Bool _t2095 = U8_eq(_sw2085, _t2094);
                                                                (void)_t2095;
                                                                ;
                                                                if (_t2095) {
                                                                    single = TokenType_clone(TokenType_Star());
                                                                } else {
                                                                    U8 _t2092 = 47;
                                                                    (void)_t2092;
                                                                    Bool _t2093 = U8_eq(_sw2085, _t2092);
                                                                    (void)_t2093;
                                                                    ;
                                                                    if (_t2093) {
                                                                        single = TokenType_clone(TokenType_Slash());
                                                                    } else {
                                                                        U8 _t2090 = 61;
                                                                        (void)_t2090;
                                                                        Bool _t2091 = U8_eq(_sw2085, _t2090);
                                                                        (void)_t2091;
                                                                        ;
                                                                        if (_t2091) {
                                                                            single = TokenType_clone(TokenType_Eq());
                                                                        } else {
                                                                            U8 _t2088 = 60;
                                                                            (void)_t2088;
                                                                            Bool _t2089 = U8_eq(_sw2085, _t2088);
                                                                            (void)_t2089;
                                                                            ;
                                                                            if (_t2089) {
                                                                                single = TokenType_clone(TokenType_Lt());
                                                                            } else {
                                                                                U8 _t2086 = 62;
                                                                                (void)_t2086;
                                                                                Bool _t2087 = U8_eq(_sw2085, _t2086);
                                                                                (void)_t2087;
                                                                                ;
                                                                                if (_t2087) {
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
        Bool _t2160; { Bool *_hp = (Bool *)TokenType_eq(single, TokenType_Eof()); _t2160 = *_hp; free(_hp); }
        (void)_t2160;
        Bool _t2161 = Bool_not(_t2160);
        (void)_t2161;
        ;
        if (_t2161) {
            U64 _t2122 = 1;
            (void)_t2122;
            I64 _t2123 = I64_clone(&(I64){line});
            (void)_t2123;
            I64 _t2124 = I64_clone(&(I64){col});
            (void)_t2124;
            Token *_t2125 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(single); _t2125->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t2122}); _t2125->text = *_ca; free(_ca); }
            _t2125->line = _t2123;
            _t2125->col = _t2124;
            (void)_t2125;
            ;
            ;
            ;
            Vec_push(tokens, _t2125);
            U64 _t2126 = U64_inc(DEREF(pos));
            (void)_t2126;
            *pos = _t2126;
            ;
            ;
            ;
            TokenType_delete(single, &(Bool){1});
            ;
            continue;
        }
        ;
        TokenType_delete(single, &(Bool){1});
        Str *_t2162 = Str_lit("Str", 3ULL);
        (void)_t2162;
        U64 _t2163; { U64 *_hp = (U64 *)Str_size(); _t2163 = *_hp; free(_hp); }
        (void)_t2163;
        U64 _t2164 = 6;
        (void)_t2164;
        Array *_va23 = Array_new(_t2162, &(U64){_t2163}, &(U64){_t2164});
        (void)_va23;
        Str_delete(_t2162, &(Bool){1});
        ;
        ;
        U64 _t2165 = 0;
        (void)_t2165;
        Str *_t2166 = Str_clone(path);
        (void)_t2166;
        Array_set(_va23, &(U64){_t2165}, _t2166);
        ;
        U64 _t2167 = 1;
        (void)_t2167;
        Str *_t2168 = Str_lit(":", 1ULL);
        (void)_t2168;
        Array_set(_va23, &(U64){_t2167}, _t2168);
        ;
        U64 _t2169 = 2;
        (void)_t2169;
        Str *_t2170 = I64_to_str(&(I64){line});
        (void)_t2170;
        Array_set(_va23, &(U64){_t2169}, _t2170);
        ;
        U64 _t2171 = 3;
        (void)_t2171;
        Str *_t2172 = Str_lit(":", 1ULL);
        (void)_t2172;
        Array_set(_va23, &(U64){_t2171}, _t2172);
        ;
        U64 _t2173 = 4;
        (void)_t2173;
        Str *_t2174 = I64_to_str(&(I64){col});
        (void)_t2174;
        Array_set(_va23, &(U64){_t2173}, _t2174);
        ;
        U64 _t2175 = 5;
        (void)_t2175;
        Str *_t2176 = Str_lit(": error: unexpected character", 29ULL);
        (void)_t2176;
        Array_set(_va23, &(U64){_t2175}, _t2176);
        ;
        println(_va23);
        U64 _t2177 = 1;
        (void)_t2177;
        I64 _t2178 = I64_clone(&(I64){col});
        (void)_t2178;
        ;
        Token *_t2179 = malloc(sizeof(Token));
        { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2179->type = *_ca; free(_ca); }
        { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t2177}); _t2179->text = *_ca; free(_ca); }
        _t2179->line = I64_clone(&(I64){line});
        _t2179->col = _t2178;
        (void)_t2179;
        ;
        ;
        ;
        Vec_push(tokens, _t2179);
        U64 _t2180 = U64_inc(DEREF(pos));
        (void)_t2180;
        *pos = _t2180;
        ;
    }
    ;
    U64 _t2183 = U64_sub(DEREF(pos), line_start);
    (void)_t2183;
    ;
    U64_delete(pos, &(Bool){1});
    U64 _t2184 = 1;
    (void)_t2184;
    U64 _t2185 = U64_add(_t2183, _t2184);
    (void)_t2185;
    ;
    ;
    I64 col = U64_to_i64(_t2185);
    (void)col;
    ;
    I64 _t2186 = I64_clone(&(I64){col});
    (void)_t2186;
    ;
    Token *_t2187 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(TokenType_Eof()); _t2187->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t2187->text = *_ca; free(_ca); }
    _t2187->line = I64_clone(&(I64){line});
    _t2187->col = _t2186;
    (void)_t2187;
    ;
    ;
    Vec_push(tokens, _t2187);
    return tokens;
}

