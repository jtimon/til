#include "lexer_lexer.h"

Token * Token_clone(Token * self) {
    (void)self;
    I64 _t1595 = I64_clone(&self->line);
    (void)_t1595;
    I64 _t1596 = I64_clone(&self->col);
    (void)_t1596;
    Token *_t1597 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(&self->type); _t1597->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->text); _t1597->text = *_ca; free(_ca); }
    _t1597->line = _t1595;
    _t1597->col = _t1596;
    (void)_t1597;
    ;
    ;
    return _t1597;
}

U64 *Token_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Token);
    return r;
}

Bool * is_digit(U8 * c) {
    (void)c;
    U8 _t1603 = 48;
    (void)_t1603;
    U8 _t1604 = 57;
    (void)_t1604;
    Bool _t1605; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1603}); _t1605 = *_hp; free(_hp); }
    (void)_t1605;
    ;
    Bool _t1606; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1604}); _t1606 = *_hp; free(_hp); }
    (void)_t1606;
    ;
    Bool _t1607 = Bool_and(_t1605, _t1606);
    (void)_t1607;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1607; return _r; }
}

Bool * is_alpha(U8 * c) {
    (void)c;
    U8 _t1608 = 97;
    (void)_t1608;
    U8 _t1609 = 122;
    (void)_t1609;
    Bool _t1610; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1608}); _t1610 = *_hp; free(_hp); }
    (void)_t1610;
    ;
    Bool _t1611; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1609}); _t1611 = *_hp; free(_hp); }
    (void)_t1611;
    ;
    U8 _t1612 = 65;
    (void)_t1612;
    U8 _t1613 = 90;
    (void)_t1613;
    Bool _t1614; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1612}); _t1614 = *_hp; free(_hp); }
    (void)_t1614;
    ;
    Bool _t1615; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1613}); _t1615 = *_hp; free(_hp); }
    (void)_t1615;
    ;
    Bool _t1616 = Bool_and(_t1610, _t1611);
    (void)_t1616;
    ;
    ;
    Bool _t1617 = Bool_and(_t1614, _t1615);
    (void)_t1617;
    ;
    ;
    U8 _t1618 = 95;
    (void)_t1618;
    Bool _t1619 = Bool_or(_t1616, _t1617);
    (void)_t1619;
    ;
    ;
    Bool _t1620 = U8_eq(DEREF(c), _t1618);
    (void)_t1620;
    ;
    Bool _t1621 = Bool_or(_t1619, _t1620);
    (void)_t1621;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1621; return _r; }
}

Bool * is_alnum(U8 * c) {
    (void)c;
    Bool _t1622; { Bool *_hp = (Bool *)is_alpha(c); _t1622 = *_hp; free(_hp); }
    (void)_t1622;
    Bool _t1623; { Bool *_hp = (Bool *)is_digit(c); _t1623 = *_hp; free(_hp); }
    (void)_t1623;
    Bool _t1624 = Bool_or(_t1622, _t1623);
    (void)_t1624;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1624; return _r; }
}

Str * tok_name(TokenType * type) {
    (void)type;
    {
        TokenType *_sw1625 = TokenType_clone(type);
        (void)_sw1625;
        Bool _t1758; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Eof()); _t1758 = *_hp; free(_hp); }
        (void)_t1758;
        if (_t1758) {
            Str *_t1626 = Str_lit("eof", 3ULL);
            (void)_t1626;
            TokenType_delete(_sw1625, &(Bool){1});
            ;
            return _t1626;
        } else {
            Bool _t1757; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_LParen()); _t1757 = *_hp; free(_hp); }
            (void)_t1757;
            if (_t1757) {
                Str *_t1627 = Str_lit("(", 1ULL);
                (void)_t1627;
                ;
                TokenType_delete(_sw1625, &(Bool){1});
                ;
                return _t1627;
            } else {
                Bool _t1756; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_RParen()); _t1756 = *_hp; free(_hp); }
                (void)_t1756;
                if (_t1756) {
                    Str *_t1628 = Str_lit(")", 1ULL);
                    (void)_t1628;
                    ;
                    ;
                    TokenType_delete(_sw1625, &(Bool){1});
                    ;
                    return _t1628;
                } else {
                    Bool _t1755; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_LBrace()); _t1755 = *_hp; free(_hp); }
                    (void)_t1755;
                    if (_t1755) {
                        Str *_t1629 = Str_lit("{", 1ULL);
                        (void)_t1629;
                        ;
                        ;
                        ;
                        TokenType_delete(_sw1625, &(Bool){1});
                        ;
                        return _t1629;
                    } else {
                        Bool _t1754; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_RBrace()); _t1754 = *_hp; free(_hp); }
                        (void)_t1754;
                        if (_t1754) {
                            Str *_t1630 = Str_lit("}", 1ULL);
                            (void)_t1630;
                            ;
                            ;
                            ;
                            ;
                            TokenType_delete(_sw1625, &(Bool){1});
                            ;
                            return _t1630;
                        } else {
                            Bool _t1753; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_LBracket()); _t1753 = *_hp; free(_hp); }
                            (void)_t1753;
                            if (_t1753) {
                                Str *_t1631 = Str_lit("[", 1ULL);
                                (void)_t1631;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TokenType_delete(_sw1625, &(Bool){1});
                                ;
                                return _t1631;
                            } else {
                                Bool _t1752; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_RBracket()); _t1752 = *_hp; free(_hp); }
                                (void)_t1752;
                                if (_t1752) {
                                    Str *_t1632 = Str_lit("]", 1ULL);
                                    (void)_t1632;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TokenType_delete(_sw1625, &(Bool){1});
                                    ;
                                    return _t1632;
                                } else {
                                    Bool _t1751; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Comma()); _t1751 = *_hp; free(_hp); }
                                    (void)_t1751;
                                    if (_t1751) {
                                        Str *_t1633 = Str_lit(",", 1ULL);
                                        (void)_t1633;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TokenType_delete(_sw1625, &(Bool){1});
                                        ;
                                        return _t1633;
                                    } else {
                                        Bool _t1750; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Colon()); _t1750 = *_hp; free(_hp); }
                                        (void)_t1750;
                                        if (_t1750) {
                                            Str *_t1634 = Str_lit(":", 1ULL);
                                            (void)_t1634;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TokenType_delete(_sw1625, &(Bool){1});
                                            ;
                                            return _t1634;
                                        } else {
                                            Bool _t1749; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Question()); _t1749 = *_hp; free(_hp); }
                                            (void)_t1749;
                                            if (_t1749) {
                                                Str *_t1635 = Str_lit("?", 1ULL);
                                                (void)_t1635;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                TokenType_delete(_sw1625, &(Bool){1});
                                                ;
                                                return _t1635;
                                            } else {
                                                Bool _t1748; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Bang()); _t1748 = *_hp; free(_hp); }
                                                (void)_t1748;
                                                if (_t1748) {
                                                    Str *_t1636 = Str_lit("!", 1ULL);
                                                    (void)_t1636;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                    ;
                                                    return _t1636;
                                                } else {
                                                    Bool _t1747; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Minus()); _t1747 = *_hp; free(_hp); }
                                                    (void)_t1747;
                                                    if (_t1747) {
                                                        Str *_t1637 = Str_lit("-", 1ULL);
                                                        (void)_t1637;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                        ;
                                                        return _t1637;
                                                    } else {
                                                        Bool _t1746; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Plus()); _t1746 = *_hp; free(_hp); }
                                                        (void)_t1746;
                                                        if (_t1746) {
                                                            Str *_t1638 = Str_lit("+", 1ULL);
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
                                                            ;
                                                            ;
                                                            ;
                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                            ;
                                                            return _t1638;
                                                        } else {
                                                            Bool _t1745; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Star()); _t1745 = *_hp; free(_hp); }
                                                            (void)_t1745;
                                                            if (_t1745) {
                                                                Str *_t1639 = Str_lit("*", 1ULL);
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
                                                                ;
                                                                ;
                                                                ;
                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                ;
                                                                return _t1639;
                                                            } else {
                                                                Bool _t1744; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Slash()); _t1744 = *_hp; free(_hp); }
                                                                (void)_t1744;
                                                                if (_t1744) {
                                                                    Str *_t1640 = Str_lit("/", 1ULL);
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
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                    ;
                                                                    return _t1640;
                                                                } else {
                                                                    Bool _t1743; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Dot()); _t1743 = *_hp; free(_hp); }
                                                                    (void)_t1743;
                                                                    if (_t1743) {
                                                                        Str *_t1641 = Str_lit(".", 1ULL);
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
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                        ;
                                                                        return _t1641;
                                                                    } else {
                                                                        Bool _t1742; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_DotDot()); _t1742 = *_hp; free(_hp); }
                                                                        (void)_t1742;
                                                                        if (_t1742) {
                                                                            Str *_t1642 = Str_lit("..", 2ULL);
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
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                            ;
                                                                            return _t1642;
                                                                        } else {
                                                                            Bool _t1741; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_DotDotDot()); _t1741 = *_hp; free(_hp); }
                                                                            (void)_t1741;
                                                                            if (_t1741) {
                                                                                Str *_t1643 = Str_lit("...", 3ULL);
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
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                ;
                                                                                return _t1643;
                                                                            } else {
                                                                                Bool _t1740; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Eq()); _t1740 = *_hp; free(_hp); }
                                                                                (void)_t1740;
                                                                                if (_t1740) {
                                                                                    Str *_t1644 = Str_lit("=", 1ULL);
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
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                    ;
                                                                                    return _t1644;
                                                                                } else {
                                                                                    Bool _t1739; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_EqEq()); _t1739 = *_hp; free(_hp); }
                                                                                    (void)_t1739;
                                                                                    if (_t1739) {
                                                                                        Str *_t1645 = Str_lit("==", 2ULL);
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
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                        ;
                                                                                        return _t1645;
                                                                                    } else {
                                                                                        Bool _t1738; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Neq()); _t1738 = *_hp; free(_hp); }
                                                                                        (void)_t1738;
                                                                                        if (_t1738) {
                                                                                            Str *_t1646 = Str_lit("!=", 2ULL);
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
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                            ;
                                                                                            return _t1646;
                                                                                        } else {
                                                                                            Bool _t1737; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Lt()); _t1737 = *_hp; free(_hp); }
                                                                                            (void)_t1737;
                                                                                            if (_t1737) {
                                                                                                Str *_t1647 = Str_lit("<", 1ULL);
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
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                ;
                                                                                                return _t1647;
                                                                                            } else {
                                                                                                Bool _t1736; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_LtEq()); _t1736 = *_hp; free(_hp); }
                                                                                                (void)_t1736;
                                                                                                if (_t1736) {
                                                                                                    Str *_t1648 = Str_lit("<=", 2ULL);
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
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t1648;
                                                                                                } else {
                                                                                                    Bool _t1735; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Gt()); _t1735 = *_hp; free(_hp); }
                                                                                                    (void)_t1735;
                                                                                                    if (_t1735) {
                                                                                                        Str *_t1649 = Str_lit(">", 1ULL);
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
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t1649;
                                                                                                    } else {
                                                                                                        Bool _t1734; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_GtEq()); _t1734 = *_hp; free(_hp); }
                                                                                                        (void)_t1734;
                                                                                                        if (_t1734) {
                                                                                                            Str *_t1650 = Str_lit(">=", 2ULL);
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
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1650;
                                                                                                        } else {
                                                                                                            Bool _t1733; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_ColonEq()); _t1733 = *_hp; free(_hp); }
                                                                                                            (void)_t1733;
                                                                                                            if (_t1733) {
                                                                                                                Str *_t1651 = Str_lit(":=", 2ULL);
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
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                ;
                                                                                                                return _t1651;
                                                                                                            } else {
                                                                                                                Bool _t1732; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Ident()); _t1732 = *_hp; free(_hp); }
                                                                                                                (void)_t1732;
                                                                                                                if (_t1732) {
                                                                                                                    Str *_t1652 = Str_lit("identifier", 10ULL);
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
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return _t1652;
                                                                                                                } else {
                                                                                                                    Bool _t1731; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_StringTok()); _t1731 = *_hp; free(_hp); }
                                                                                                                    (void)_t1731;
                                                                                                                    if (_t1731) {
                                                                                                                        Str *_t1653 = Str_lit("string", 6ULL);
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
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return _t1653;
                                                                                                                    } else {
                                                                                                                        Bool _t1730; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Number()); _t1730 = *_hp; free(_hp); }
                                                                                                                        (void)_t1730;
                                                                                                                        if (_t1730) {
                                                                                                                            Str *_t1654 = Str_lit("number", 6ULL);
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
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return _t1654;
                                                                                                                        } else {
                                                                                                                            Bool _t1729; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Char()); _t1729 = *_hp; free(_hp); }
                                                                                                                            (void)_t1729;
                                                                                                                            if (_t1729) {
                                                                                                                                Str *_t1655 = Str_lit("char", 4ULL);
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
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return _t1655;
                                                                                                                            } else {
                                                                                                                                Bool _t1728; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwMode()); _t1728 = *_hp; free(_hp); }
                                                                                                                                (void)_t1728;
                                                                                                                                if (_t1728) {
                                                                                                                                    Str *_t1656 = Str_lit("mode", 4ULL);
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
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return _t1656;
                                                                                                                                } else {
                                                                                                                                    Bool _t1727; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwMut()); _t1727 = *_hp; free(_hp); }
                                                                                                                                    (void)_t1727;
                                                                                                                                    if (_t1727) {
                                                                                                                                        Str *_t1657 = Str_lit("mut", 3ULL);
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
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return _t1657;
                                                                                                                                    } else {
                                                                                                                                        Bool _t1726; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwOwn()); _t1726 = *_hp; free(_hp); }
                                                                                                                                        (void)_t1726;
                                                                                                                                        if (_t1726) {
                                                                                                                                            Str *_t1658 = Str_lit("own", 3ULL);
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
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return _t1658;
                                                                                                                                        } else {
                                                                                                                                            Bool _t1725; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwRef()); _t1725 = *_hp; free(_hp); }
                                                                                                                                            (void)_t1725;
                                                                                                                                            if (_t1725) {
                                                                                                                                                Str *_t1659 = Str_lit("ref", 3ULL);
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
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return _t1659;
                                                                                                                                            } else {
                                                                                                                                                Bool _t1724; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwShallow()); _t1724 = *_hp; free(_hp); }
                                                                                                                                                (void)_t1724;
                                                                                                                                                if (_t1724) {
                                                                                                                                                    Str *_t1660 = Str_lit("shallow", 7ULL);
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
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                    ;
                                                                                                                                                    return _t1660;
                                                                                                                                                } else {
                                                                                                                                                    Bool _t1723; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwStruct()); _t1723 = *_hp; free(_hp); }
                                                                                                                                                    (void)_t1723;
                                                                                                                                                    if (_t1723) {
                                                                                                                                                        Str *_t1661 = Str_lit("struct", 6ULL);
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
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                        ;
                                                                                                                                                        return _t1661;
                                                                                                                                                    } else {
                                                                                                                                                        Bool _t1722; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwExtStruct()); _t1722 = *_hp; free(_hp); }
                                                                                                                                                        (void)_t1722;
                                                                                                                                                        if (_t1722) {
                                                                                                                                                            Str *_t1662 = Str_lit("ext_struct", 10ULL);
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
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                            ;
                                                                                                                                                            return _t1662;
                                                                                                                                                        } else {
                                                                                                                                                            Bool _t1721; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwEnum()); _t1721 = *_hp; free(_hp); }
                                                                                                                                                            (void)_t1721;
                                                                                                                                                            if (_t1721) {
                                                                                                                                                                Str *_t1663 = Str_lit("enum", 4ULL);
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
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                ;
                                                                                                                                                                return _t1663;
                                                                                                                                                            } else {
                                                                                                                                                                Bool _t1720; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwNamespace()); _t1720 = *_hp; free(_hp); }
                                                                                                                                                                (void)_t1720;
                                                                                                                                                                if (_t1720) {
                                                                                                                                                                    Str *_t1664 = Str_lit("namespace", 9ULL);
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
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                    ;
                                                                                                                                                                    return _t1664;
                                                                                                                                                                } else {
                                                                                                                                                                    Bool _t1719; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwFunc()); _t1719 = *_hp; free(_hp); }
                                                                                                                                                                    (void)_t1719;
                                                                                                                                                                    if (_t1719) {
                                                                                                                                                                        Str *_t1665 = Str_lit("func", 4ULL);
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
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                        ;
                                                                                                                                                                        return _t1665;
                                                                                                                                                                    } else {
                                                                                                                                                                        Bool _t1718; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwProc()); _t1718 = *_hp; free(_hp); }
                                                                                                                                                                        (void)_t1718;
                                                                                                                                                                        if (_t1718) {
                                                                                                                                                                            Str *_t1666 = Str_lit("proc", 4ULL);
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
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                            ;
                                                                                                                                                                            return _t1666;
                                                                                                                                                                        } else {
                                                                                                                                                                            Bool _t1717; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwTest()); _t1717 = *_hp; free(_hp); }
                                                                                                                                                                            (void)_t1717;
                                                                                                                                                                            if (_t1717) {
                                                                                                                                                                                Str *_t1667 = Str_lit("test", 4ULL);
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
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                ;
                                                                                                                                                                                return _t1667;
                                                                                                                                                                            } else {
                                                                                                                                                                                Bool _t1716; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwMacro()); _t1716 = *_hp; free(_hp); }
                                                                                                                                                                                (void)_t1716;
                                                                                                                                                                                if (_t1716) {
                                                                                                                                                                                    Str *_t1668 = Str_lit("macro", 5ULL);
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
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                    ;
                                                                                                                                                                                    return _t1668;
                                                                                                                                                                                } else {
                                                                                                                                                                                    Bool _t1715; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwExtFunc()); _t1715 = *_hp; free(_hp); }
                                                                                                                                                                                    (void)_t1715;
                                                                                                                                                                                    if (_t1715) {
                                                                                                                                                                                        Str *_t1669 = Str_lit("ext_func", 8ULL);
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
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                        ;
                                                                                                                                                                                        return _t1669;
                                                                                                                                                                                    } else {
                                                                                                                                                                                        Bool _t1714; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwExtProc()); _t1714 = *_hp; free(_hp); }
                                                                                                                                                                                        (void)_t1714;
                                                                                                                                                                                        if (_t1714) {
                                                                                                                                                                                            Str *_t1670 = Str_lit("ext_proc", 8ULL);
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
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                            ;
                                                                                                                                                                                            return _t1670;
                                                                                                                                                                                        } else {
                                                                                                                                                                                            Bool _t1713; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwReturns()); _t1713 = *_hp; free(_hp); }
                                                                                                                                                                                            (void)_t1713;
                                                                                                                                                                                            if (_t1713) {
                                                                                                                                                                                                Str *_t1671 = Str_lit("returns", 7ULL);
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
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                ;
                                                                                                                                                                                                return _t1671;
                                                                                                                                                                                            } else {
                                                                                                                                                                                                Bool _t1712; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwThrows()); _t1712 = *_hp; free(_hp); }
                                                                                                                                                                                                (void)_t1712;
                                                                                                                                                                                                if (_t1712) {
                                                                                                                                                                                                    Str *_t1672 = Str_lit("throws", 6ULL);
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
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    return _t1672;
                                                                                                                                                                                                } else {
                                                                                                                                                                                                    Bool _t1711; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwIf()); _t1711 = *_hp; free(_hp); }
                                                                                                                                                                                                    (void)_t1711;
                                                                                                                                                                                                    if (_t1711) {
                                                                                                                                                                                                        Str *_t1673 = Str_lit("if", 2ULL);
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
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        return _t1673;
                                                                                                                                                                                                    } else {
                                                                                                                                                                                                        Bool _t1710; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwElse()); _t1710 = *_hp; free(_hp); }
                                                                                                                                                                                                        (void)_t1710;
                                                                                                                                                                                                        if (_t1710) {
                                                                                                                                                                                                            Str *_t1674 = Str_lit("else", 4ULL);
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
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            return _t1674;
                                                                                                                                                                                                        } else {
                                                                                                                                                                                                            Bool _t1709; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwWhile()); _t1709 = *_hp; free(_hp); }
                                                                                                                                                                                                            (void)_t1709;
                                                                                                                                                                                                            if (_t1709) {
                                                                                                                                                                                                                Str *_t1675 = Str_lit("while", 5ULL);
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
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                return _t1675;
                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                Bool _t1708; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwFor()); _t1708 = *_hp; free(_hp); }
                                                                                                                                                                                                                (void)_t1708;
                                                                                                                                                                                                                if (_t1708) {
                                                                                                                                                                                                                    Str *_t1676 = Str_lit("for", 3ULL);
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
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    return _t1676;
                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                    Bool _t1707; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwIn()); _t1707 = *_hp; free(_hp); }
                                                                                                                                                                                                                    (void)_t1707;
                                                                                                                                                                                                                    if (_t1707) {
                                                                                                                                                                                                                        Str *_t1677 = Str_lit("in", 2ULL);
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
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        return _t1677;
                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                        Bool _t1706; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwSwitch()); _t1706 = *_hp; free(_hp); }
                                                                                                                                                                                                                        (void)_t1706;
                                                                                                                                                                                                                        if (_t1706) {
                                                                                                                                                                                                                            Str *_t1678 = Str_lit("switch", 6ULL);
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
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            return _t1678;
                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                            Bool _t1705; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwMatch()); _t1705 = *_hp; free(_hp); }
                                                                                                                                                                                                                            (void)_t1705;
                                                                                                                                                                                                                            if (_t1705) {
                                                                                                                                                                                                                                Str *_t1679 = Str_lit("match", 5ULL);
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
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                return _t1679;
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                Bool _t1704; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwCase()); _t1704 = *_hp; free(_hp); }
                                                                                                                                                                                                                                (void)_t1704;
                                                                                                                                                                                                                                if (_t1704) {
                                                                                                                                                                                                                                    Str *_t1680 = Str_lit("case", 4ULL);
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
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    return _t1680;
                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                    Bool _t1703; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwDefault()); _t1703 = *_hp; free(_hp); }
                                                                                                                                                                                                                                    (void)_t1703;
                                                                                                                                                                                                                                    if (_t1703) {
                                                                                                                                                                                                                                        Str *_t1681 = Str_lit("default", 7ULL);
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
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        return _t1681;
                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                        Bool _t1702; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwReturn()); _t1702 = *_hp; free(_hp); }
                                                                                                                                                                                                                                        (void)_t1702;
                                                                                                                                                                                                                                        if (_t1702) {
                                                                                                                                                                                                                                            Str *_t1682 = Str_lit("return", 6ULL);
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
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            return _t1682;
                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                            Bool _t1701; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwThrow()); _t1701 = *_hp; free(_hp); }
                                                                                                                                                                                                                                            (void)_t1701;
                                                                                                                                                                                                                                            if (_t1701) {
                                                                                                                                                                                                                                                Str *_t1683 = Str_lit("throw", 5ULL);
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
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                return _t1683;
                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                Bool _t1700; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwCatch()); _t1700 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                (void)_t1700;
                                                                                                                                                                                                                                                if (_t1700) {
                                                                                                                                                                                                                                                    Str *_t1684 = Str_lit("catch", 5ULL);
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
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    return _t1684;
                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                    Bool _t1699; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwBreak()); _t1699 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                    (void)_t1699;
                                                                                                                                                                                                                                                    if (_t1699) {
                                                                                                                                                                                                                                                        Str *_t1685 = Str_lit("break", 5ULL);
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
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        return _t1685;
                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                        Bool _t1698; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwContinue()); _t1698 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                        (void)_t1698;
                                                                                                                                                                                                                                                        if (_t1698) {
                                                                                                                                                                                                                                                            Str *_t1686 = Str_lit("continue", 8ULL);
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
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            return _t1686;
                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                            Bool _t1697; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwDefer()); _t1697 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                            (void)_t1697;
                                                                                                                                                                                                                                                            if (_t1697) {
                                                                                                                                                                                                                                                                Str *_t1687 = Str_lit("defer", 5ULL);
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
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                return _t1687;
                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                Bool _t1696; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwTrue()); _t1696 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                (void)_t1696;
                                                                                                                                                                                                                                                                if (_t1696) {
                                                                                                                                                                                                                                                                    Str *_t1688 = Str_lit("true", 4ULL);
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
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t1688;
                                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                                    Bool _t1695; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwFalse()); _t1695 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                    (void)_t1695;
                                                                                                                                                                                                                                                                    if (_t1695) {
                                                                                                                                                                                                                                                                        Str *_t1689 = Str_lit("false", 5ULL);
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
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        return _t1689;
                                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                                        Bool _t1694; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwNull()); _t1694 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                        (void)_t1694;
                                                                                                                                                                                                                                                                        if (_t1694) {
                                                                                                                                                                                                                                                                            Str *_t1690 = Str_lit("NULL", 4ULL);
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
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            return _t1690;
                                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                                            Bool _t1693; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Error()); _t1693 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                            (void)_t1693;
                                                                                                                                                                                                                                                                            if (_t1693) {
                                                                                                                                                                                                                                                                                Str *_t1691 = Str_lit("error", 5ULL);
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
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t1691;
                                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                                Str *_t1692 = Str_lit("?", 1ULL);
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
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t1692;
                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                        }
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                    }
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                }
                                                                                                                                                                                                                ;
                                                                                                                                                                                                            }
                                                                                                                                                                                                            ;
                                                                                                                                                                                                        }
                                                                                                                                                                                                        ;
                                                                                                                                                                                                    }
                                                                                                                                                                                                    ;
                                                                                                                                                                                                }
                                                                                                                                                                                                ;
                                                                                                                                                                                            }
                                                                                                                                                                                            ;
                                                                                                                                                                                        }
                                                                                                                                                                                        ;
                                                                                                                                                                                    }
                                                                                                                                                                                    ;
                                                                                                                                                                                }
                                                                                                                                                                                ;
                                                                                                                                                                            }
                                                                                                                                                                            ;
                                                                                                                                                                        }
                                                                                                                                                                        ;
                                                                                                                                                                    }
                                                                                                                                                                    ;
                                                                                                                                                                }
                                                                                                                                                                ;
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                        ;
                                                                                                                                                    }
                                                                                                                                                    ;
                                                                                                                                                }
                                                                                                                                                ;
                                                                                                                                            }
                                                                                                                                            ;
                                                                                                                                        }
                                                                                                                                        ;
                                                                                                                                    }
                                                                                                                                    ;
                                                                                                                                }
                                                                                                                                ;
                                                                                                                            }
                                                                                                                            ;
                                                                                                                        }
                                                                                                                        ;
                                                                                                                    }
                                                                                                                    ;
                                                                                                                }
                                                                                                                ;
                                                                                                            }
                                                                                                            ;
                                                                                                        }
                                                                                                        ;
                                                                                                    }
                                                                                                    ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                            ;
                                                                                        }
                                                                                        ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                                ;
                                                                            }
                                                                            ;
                                                                        }
                                                                        ;
                                                                    }
                                                                    ;
                                                                }
                                                                ;
                                                            }
                                                            ;
                                                        }
                                                        ;
                                                    }
                                                    ;
                                                }
                                                ;
                                            }
                                            ;
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        TokenType_delete(_sw1625, &(Bool){1});
        ;
    }
}

TokenType * lookup_keyword(Str * word) {
    (void)word;
    {
        Str *_sw1759 = Str_clone(word);
        (void)_sw1759;
        Str *_t1828 = Str_lit("mode", 4ULL);
        (void)_t1828;
        Bool _t1829; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1828); _t1829 = *_hp; free(_hp); }
        (void)_t1829;
        Str_delete(_t1828, &(Bool){1});
        if (_t1829) {
            Str_delete(_sw1759, &(Bool){1});
            ;
            return TokenType_KwMode();
        } else {
            Str *_t1826 = Str_lit("mut", 3ULL);
            (void)_t1826;
            Bool _t1827; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1826); _t1827 = *_hp; free(_hp); }
            (void)_t1827;
            Str_delete(_t1826, &(Bool){1});
            if (_t1827) {
                ;
                Str_delete(_sw1759, &(Bool){1});
                ;
                return TokenType_KwMut();
            } else {
                Str *_t1824 = Str_lit("own", 3ULL);
                (void)_t1824;
                Bool _t1825; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1824); _t1825 = *_hp; free(_hp); }
                (void)_t1825;
                Str_delete(_t1824, &(Bool){1});
                if (_t1825) {
                    ;
                    ;
                    Str_delete(_sw1759, &(Bool){1});
                    ;
                    return TokenType_KwOwn();
                } else {
                    Str *_t1822 = Str_lit("ref", 3ULL);
                    (void)_t1822;
                    Bool _t1823; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1822); _t1823 = *_hp; free(_hp); }
                    (void)_t1823;
                    Str_delete(_t1822, &(Bool){1});
                    if (_t1823) {
                        ;
                        ;
                        ;
                        Str_delete(_sw1759, &(Bool){1});
                        ;
                        return TokenType_KwRef();
                    } else {
                        Str *_t1820 = Str_lit("shallow", 7ULL);
                        (void)_t1820;
                        Bool _t1821; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1820); _t1821 = *_hp; free(_hp); }
                        (void)_t1821;
                        Str_delete(_t1820, &(Bool){1});
                        if (_t1821) {
                            ;
                            ;
                            ;
                            ;
                            Str_delete(_sw1759, &(Bool){1});
                            ;
                            return TokenType_KwShallow();
                        } else {
                            Str *_t1818 = Str_lit("struct", 6ULL);
                            (void)_t1818;
                            Bool _t1819; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1818); _t1819 = *_hp; free(_hp); }
                            (void)_t1819;
                            Str_delete(_t1818, &(Bool){1});
                            if (_t1819) {
                                ;
                                ;
                                ;
                                ;
                                ;
                                Str_delete(_sw1759, &(Bool){1});
                                ;
                                return TokenType_KwStruct();
                            } else {
                                Str *_t1816 = Str_lit("ext_struct", 10ULL);
                                (void)_t1816;
                                Bool _t1817; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1816); _t1817 = *_hp; free(_hp); }
                                (void)_t1817;
                                Str_delete(_t1816, &(Bool){1});
                                if (_t1817) {
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    Str_delete(_sw1759, &(Bool){1});
                                    ;
                                    return TokenType_KwExtStruct();
                                } else {
                                    Str *_t1814 = Str_lit("enum", 4ULL);
                                    (void)_t1814;
                                    Bool _t1815; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1814); _t1815 = *_hp; free(_hp); }
                                    (void)_t1815;
                                    Str_delete(_t1814, &(Bool){1});
                                    if (_t1815) {
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        Str_delete(_sw1759, &(Bool){1});
                                        ;
                                        return TokenType_KwEnum();
                                    } else {
                                        Str *_t1812 = Str_lit("namespace", 9ULL);
                                        (void)_t1812;
                                        Bool _t1813; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1812); _t1813 = *_hp; free(_hp); }
                                        (void)_t1813;
                                        Str_delete(_t1812, &(Bool){1});
                                        if (_t1813) {
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            Str_delete(_sw1759, &(Bool){1});
                                            ;
                                            return TokenType_KwNamespace();
                                        } else {
                                            Str *_t1810 = Str_lit("func", 4ULL);
                                            (void)_t1810;
                                            Bool _t1811; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1810); _t1811 = *_hp; free(_hp); }
                                            (void)_t1811;
                                            Str_delete(_t1810, &(Bool){1});
                                            if (_t1811) {
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                Str_delete(_sw1759, &(Bool){1});
                                                ;
                                                return TokenType_KwFunc();
                                            } else {
                                                Str *_t1808 = Str_lit("proc", 4ULL);
                                                (void)_t1808;
                                                Bool _t1809; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1808); _t1809 = *_hp; free(_hp); }
                                                (void)_t1809;
                                                Str_delete(_t1808, &(Bool){1});
                                                if (_t1809) {
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    Str_delete(_sw1759, &(Bool){1});
                                                    ;
                                                    return TokenType_KwProc();
                                                } else {
                                                    Str *_t1806 = Str_lit("test", 4ULL);
                                                    (void)_t1806;
                                                    Bool _t1807; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1806); _t1807 = *_hp; free(_hp); }
                                                    (void)_t1807;
                                                    Str_delete(_t1806, &(Bool){1});
                                                    if (_t1807) {
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        Str_delete(_sw1759, &(Bool){1});
                                                        ;
                                                        return TokenType_KwTest();
                                                    } else {
                                                        Str *_t1804 = Str_lit("macro", 5ULL);
                                                        (void)_t1804;
                                                        Bool _t1805; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1804); _t1805 = *_hp; free(_hp); }
                                                        (void)_t1805;
                                                        Str_delete(_t1804, &(Bool){1});
                                                        if (_t1805) {
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            Str_delete(_sw1759, &(Bool){1});
                                                            ;
                                                            return TokenType_KwMacro();
                                                        } else {
                                                            Str *_t1802 = Str_lit("ext_func", 8ULL);
                                                            (void)_t1802;
                                                            Bool _t1803; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1802); _t1803 = *_hp; free(_hp); }
                                                            (void)_t1803;
                                                            Str_delete(_t1802, &(Bool){1});
                                                            if (_t1803) {
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                Str_delete(_sw1759, &(Bool){1});
                                                                ;
                                                                return TokenType_KwExtFunc();
                                                            } else {
                                                                Str *_t1800 = Str_lit("ext_proc", 8ULL);
                                                                (void)_t1800;
                                                                Bool _t1801; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1800); _t1801 = *_hp; free(_hp); }
                                                                (void)_t1801;
                                                                Str_delete(_t1800, &(Bool){1});
                                                                if (_t1801) {
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    Str_delete(_sw1759, &(Bool){1});
                                                                    ;
                                                                    return TokenType_KwExtProc();
                                                                } else {
                                                                    Str *_t1798 = Str_lit("returns", 7ULL);
                                                                    (void)_t1798;
                                                                    Bool _t1799; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1798); _t1799 = *_hp; free(_hp); }
                                                                    (void)_t1799;
                                                                    Str_delete(_t1798, &(Bool){1});
                                                                    if (_t1799) {
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        Str_delete(_sw1759, &(Bool){1});
                                                                        ;
                                                                        return TokenType_KwReturns();
                                                                    } else {
                                                                        Str *_t1796 = Str_lit("throws", 6ULL);
                                                                        (void)_t1796;
                                                                        Bool _t1797; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1796); _t1797 = *_hp; free(_hp); }
                                                                        (void)_t1797;
                                                                        Str_delete(_t1796, &(Bool){1});
                                                                        if (_t1797) {
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            Str_delete(_sw1759, &(Bool){1});
                                                                            ;
                                                                            return TokenType_KwThrows();
                                                                        } else {
                                                                            Str *_t1794 = Str_lit("if", 2ULL);
                                                                            (void)_t1794;
                                                                            Bool _t1795; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1794); _t1795 = *_hp; free(_hp); }
                                                                            (void)_t1795;
                                                                            Str_delete(_t1794, &(Bool){1});
                                                                            if (_t1795) {
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                Str_delete(_sw1759, &(Bool){1});
                                                                                ;
                                                                                return TokenType_KwIf();
                                                                            } else {
                                                                                Str *_t1792 = Str_lit("else", 4ULL);
                                                                                (void)_t1792;
                                                                                Bool _t1793; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1792); _t1793 = *_hp; free(_hp); }
                                                                                (void)_t1793;
                                                                                Str_delete(_t1792, &(Bool){1});
                                                                                if (_t1793) {
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    Str_delete(_sw1759, &(Bool){1});
                                                                                    ;
                                                                                    return TokenType_KwElse();
                                                                                } else {
                                                                                    Str *_t1790 = Str_lit("while", 5ULL);
                                                                                    (void)_t1790;
                                                                                    Bool _t1791; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1790); _t1791 = *_hp; free(_hp); }
                                                                                    (void)_t1791;
                                                                                    Str_delete(_t1790, &(Bool){1});
                                                                                    if (_t1791) {
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        Str_delete(_sw1759, &(Bool){1});
                                                                                        ;
                                                                                        return TokenType_KwWhile();
                                                                                    } else {
                                                                                        Str *_t1788 = Str_lit("for", 3ULL);
                                                                                        (void)_t1788;
                                                                                        Bool _t1789; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1788); _t1789 = *_hp; free(_hp); }
                                                                                        (void)_t1789;
                                                                                        Str_delete(_t1788, &(Bool){1});
                                                                                        if (_t1789) {
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            Str_delete(_sw1759, &(Bool){1});
                                                                                            ;
                                                                                            return TokenType_KwFor();
                                                                                        } else {
                                                                                            Str *_t1786 = Str_lit("in", 2ULL);
                                                                                            (void)_t1786;
                                                                                            Bool _t1787; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1786); _t1787 = *_hp; free(_hp); }
                                                                                            (void)_t1787;
                                                                                            Str_delete(_t1786, &(Bool){1});
                                                                                            if (_t1787) {
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                Str_delete(_sw1759, &(Bool){1});
                                                                                                ;
                                                                                                return TokenType_KwIn();
                                                                                            } else {
                                                                                                Str *_t1784 = Str_lit("switch", 6ULL);
                                                                                                (void)_t1784;
                                                                                                Bool _t1785; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1784); _t1785 = *_hp; free(_hp); }
                                                                                                (void)_t1785;
                                                                                                Str_delete(_t1784, &(Bool){1});
                                                                                                if (_t1785) {
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    Str_delete(_sw1759, &(Bool){1});
                                                                                                    ;
                                                                                                    return TokenType_KwSwitch();
                                                                                                } else {
                                                                                                    Str *_t1782 = Str_lit("match", 5ULL);
                                                                                                    (void)_t1782;
                                                                                                    Bool _t1783; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1782); _t1783 = *_hp; free(_hp); }
                                                                                                    (void)_t1783;
                                                                                                    Str_delete(_t1782, &(Bool){1});
                                                                                                    if (_t1783) {
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        Str_delete(_sw1759, &(Bool){1});
                                                                                                        ;
                                                                                                        return TokenType_KwMatch();
                                                                                                    } else {
                                                                                                        Str *_t1780 = Str_lit("case", 4ULL);
                                                                                                        (void)_t1780;
                                                                                                        Bool _t1781; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1780); _t1781 = *_hp; free(_hp); }
                                                                                                        (void)_t1781;
                                                                                                        Str_delete(_t1780, &(Bool){1});
                                                                                                        if (_t1781) {
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            Str_delete(_sw1759, &(Bool){1});
                                                                                                            ;
                                                                                                            return TokenType_KwCase();
                                                                                                        } else {
                                                                                                            Str *_t1778 = Str_lit("default", 7ULL);
                                                                                                            (void)_t1778;
                                                                                                            Bool _t1779; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1778); _t1779 = *_hp; free(_hp); }
                                                                                                            (void)_t1779;
                                                                                                            Str_delete(_t1778, &(Bool){1});
                                                                                                            if (_t1779) {
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                Str_delete(_sw1759, &(Bool){1});
                                                                                                                ;
                                                                                                                return TokenType_KwDefault();
                                                                                                            } else {
                                                                                                                Str *_t1776 = Str_lit("return", 6ULL);
                                                                                                                (void)_t1776;
                                                                                                                Bool _t1777; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1776); _t1777 = *_hp; free(_hp); }
                                                                                                                (void)_t1777;
                                                                                                                Str_delete(_t1776, &(Bool){1});
                                                                                                                if (_t1777) {
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    Str_delete(_sw1759, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return TokenType_KwReturn();
                                                                                                                } else {
                                                                                                                    Str *_t1774 = Str_lit("throw", 5ULL);
                                                                                                                    (void)_t1774;
                                                                                                                    Bool _t1775; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1774); _t1775 = *_hp; free(_hp); }
                                                                                                                    (void)_t1775;
                                                                                                                    Str_delete(_t1774, &(Bool){1});
                                                                                                                    if (_t1775) {
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        Str_delete(_sw1759, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return TokenType_KwThrow();
                                                                                                                    } else {
                                                                                                                        Str *_t1772 = Str_lit("catch", 5ULL);
                                                                                                                        (void)_t1772;
                                                                                                                        Bool _t1773; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1772); _t1773 = *_hp; free(_hp); }
                                                                                                                        (void)_t1773;
                                                                                                                        Str_delete(_t1772, &(Bool){1});
                                                                                                                        if (_t1773) {
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            Str_delete(_sw1759, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return TokenType_KwCatch();
                                                                                                                        } else {
                                                                                                                            Str *_t1770 = Str_lit("break", 5ULL);
                                                                                                                            (void)_t1770;
                                                                                                                            Bool _t1771; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1770); _t1771 = *_hp; free(_hp); }
                                                                                                                            (void)_t1771;
                                                                                                                            Str_delete(_t1770, &(Bool){1});
                                                                                                                            if (_t1771) {
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                Str_delete(_sw1759, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return TokenType_KwBreak();
                                                                                                                            } else {
                                                                                                                                Str *_t1768 = Str_lit("continue", 8ULL);
                                                                                                                                (void)_t1768;
                                                                                                                                Bool _t1769; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1768); _t1769 = *_hp; free(_hp); }
                                                                                                                                (void)_t1769;
                                                                                                                                Str_delete(_t1768, &(Bool){1});
                                                                                                                                if (_t1769) {
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    Str_delete(_sw1759, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return TokenType_KwContinue();
                                                                                                                                } else {
                                                                                                                                    Str *_t1766 = Str_lit("defer", 5ULL);
                                                                                                                                    (void)_t1766;
                                                                                                                                    Bool _t1767; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1766); _t1767 = *_hp; free(_hp); }
                                                                                                                                    (void)_t1767;
                                                                                                                                    Str_delete(_t1766, &(Bool){1});
                                                                                                                                    if (_t1767) {
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        Str_delete(_sw1759, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return TokenType_KwDefer();
                                                                                                                                    } else {
                                                                                                                                        Str *_t1764 = Str_lit("true", 4ULL);
                                                                                                                                        (void)_t1764;
                                                                                                                                        Bool _t1765; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1764); _t1765 = *_hp; free(_hp); }
                                                                                                                                        (void)_t1765;
                                                                                                                                        Str_delete(_t1764, &(Bool){1});
                                                                                                                                        if (_t1765) {
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            Str_delete(_sw1759, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return TokenType_KwTrue();
                                                                                                                                        } else {
                                                                                                                                            Str *_t1762 = Str_lit("false", 5ULL);
                                                                                                                                            (void)_t1762;
                                                                                                                                            Bool _t1763; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1762); _t1763 = *_hp; free(_hp); }
                                                                                                                                            (void)_t1763;
                                                                                                                                            Str_delete(_t1762, &(Bool){1});
                                                                                                                                            if (_t1763) {
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                Str_delete(_sw1759, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return TokenType_KwFalse();
                                                                                                                                            } else {
                                                                                                                                                Str *_t1760 = Str_lit("NULL", 4ULL);
                                                                                                                                                (void)_t1760;
                                                                                                                                                Bool _t1761; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1760); _t1761 = *_hp; free(_hp); }
                                                                                                                                                (void)_t1761;
                                                                                                                                                Str_delete(_t1760, &(Bool){1});
                                                                                                                                                if (_t1761) {
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    Str_delete(_sw1759, &(Bool){1});
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
                                                                                                                                                    Str_delete(_sw1759, &(Bool){1});
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
        Str_delete(_sw1759, &(Bool){1});
        ;
    }
}

Vec * tokenize(Str * src, Str * path) {
    (void)src;
    (void)path;
    Str *_t2178 = Str_lit("Token", 5ULL);
    (void)_t2178;
    U64 _t2179; { U64 *_hp = (U64 *)Token_size(); _t2179 = *_hp; free(_hp); }
    (void)_t2179;
    Vec *tokens = Vec_new(_t2178, &(U64){_t2179});
    (void)tokens;
    Str_delete(_t2178, &(Bool){1});
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
        Bool _wcond1830; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1830 = *_hp; free(_hp); }
        (void)_wcond1830;
        if (_wcond1830) {
        } else {
            ;
            break;
        }
        ;
        U8 *c = Str_byte_at(src, pos);
        (void)c;
        U8 _t2124 = 32;
        (void)_t2124;
        U8 _t2125 = 9;
        (void)_t2125;
        Bool _t2126 = U8_eq(DEREF(c), _t2124);
        (void)_t2126;
        ;
        Bool _t2127 = U8_eq(DEREF(c), _t2125);
        (void)_t2127;
        ;
        U8 _t2128 = 13;
        (void)_t2128;
        Bool _t2129 = Bool_or(_t2126, _t2127);
        (void)_t2129;
        ;
        ;
        Bool _t2130 = U8_eq(DEREF(c), _t2128);
        (void)_t2130;
        ;
        U8 _t2131 = 59;
        (void)_t2131;
        Bool _t2132 = Bool_or(_t2129, _t2130);
        (void)_t2132;
        ;
        ;
        Bool _t2133 = U8_eq(DEREF(c), _t2131);
        (void)_t2133;
        ;
        Bool _t2134 = Bool_or(_t2132, _t2133);
        (void)_t2134;
        ;
        ;
        if (_t2134) {
            U64 _t1831 = U64_inc(DEREF(pos));
            (void)_t1831;
            *pos = _t1831;
            ;
            ;
            continue;
        }
        ;
        U8 _t2135 = 10;
        (void)_t2135;
        Bool _t2136 = U8_eq(DEREF(c), _t2135);
        (void)_t2136;
        ;
        if (_t2136) {
            U64 _t1832 = U64_inc(DEREF(pos));
            (void)_t1832;
            *pos = _t1832;
            ;
            I64 _t1833 = 1;
            (void)_t1833;
            I64 _t1834 = I64_add(line, _t1833);
            (void)_t1834;
            ;
            line = _t1834;
            ;
            U64 _t1835 = U64_clone(pos);
            (void)_t1835;
            line_start = _t1835;
            ;
            ;
            continue;
        }
        ;
        U64 _t2137 = U64_sub(DEREF(pos), line_start);
        (void)_t2137;
        U64 _t2138 = 1;
        (void)_t2138;
        U64 _t2139 = U64_add(_t2137, _t2138);
        (void)_t2139;
        ;
        ;
        I64 col = U64_to_i64(_t2139);
        (void)col;
        ;
        U64 start = U64_clone(pos);
        (void)start;
        U8 _t2140 = 35;
        (void)_t2140;
        Bool _t2141 = U8_eq(DEREF(c), _t2140);
        (void)_t2141;
        ;
        if (_t2141) {
            while (1) {
                Bool _wcond1836; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1836 = *_hp; free(_hp); }
                (void)_wcond1836;
                if (_wcond1836) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1837 = Str_byte_at(src, pos);
                (void)_t1837;
                U8 _t1838 = 10;
                (void)_t1838;
                Bool _t1839 = U8_eq(DEREF(_t1837), _t1838);
                (void)_t1839;
                ;
                if (_t1839) {
                    ;
                    break;
                }
                ;
                U64 _t1840 = U64_inc(DEREF(pos));
                (void)_t1840;
                *pos = _t1840;
                ;
            }
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t2142 = 47;
        (void)_t2142;
        U64 _t2143 = 1;
        (void)_t2143;
        U64 _t2144 = U64_add(DEREF(pos), _t2143);
        (void)_t2144;
        ;
        Bool _t2145 = U8_eq(DEREF(c), _t2142);
        (void)_t2145;
        ;
        Bool _t2146; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2144}, &(U64){src_len}); _t2146 = *_hp; free(_hp); }
        (void)_t2146;
        ;
        Bool _t2147 = Bool_and(_t2145, _t2146);
        (void)_t2147;
        ;
        ;
        if (_t2147) {
            U64 _t1899 = 1;
            (void)_t1899;
            U64 *_t1900 = malloc(sizeof(U64)); *_t1900 = U64_add(DEREF(pos), _t1899);
            (void)_t1900;
            ;
            U8 *c2 = Str_byte_at(src, _t1900);
            (void)c2;
            U8 _t1901 = 47;
            (void)_t1901;
            Bool _t1902 = U8_eq(DEREF(c2), _t1901);
            (void)_t1902;
            ;
            if (_t1902) {
                while (1) {
                    Bool _wcond1841; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1841 = *_hp; free(_hp); }
                    (void)_wcond1841;
                    if (_wcond1841) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U8 *_t1842 = Str_byte_at(src, pos);
                    (void)_t1842;
                    U8 _t1843 = 10;
                    (void)_t1843;
                    Bool _t1844 = U8_eq(DEREF(_t1842), _t1843);
                    (void)_t1844;
                    ;
                    if (_t1844) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1845 = U64_inc(DEREF(pos));
                    (void)_t1845;
                    *pos = _t1845;
                    ;
                }
                U64_delete(_t1900, &(Bool){1});
                ;
                ;
                ;
                ;
                continue;
            }
            ;
            U8 _t1903 = 42;
            (void)_t1903;
            Bool _t1904 = U8_eq(DEREF(c2), _t1903);
            (void)_t1904;
            U64_delete(_t1900, &(Bool){1});
            ;
            if (_t1904) {
                U64 _t1895 = 2;
                (void)_t1895;
                U64 _t1896 = U64_add(DEREF(pos), _t1895);
                (void)_t1896;
                ;
                *pos = _t1896;
                ;
                I64 depth = 1;
                (void)depth;
                while (1) {
                    Bool _wcond1846; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1846 = *_hp; free(_hp); }
                    (void)_wcond1846;
                    if (_wcond1846) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    I64 _t1871 = 0;
                    (void)_t1871;
                    Bool _t1872; { Bool *_hp = (Bool *)I64_lte(&(I64){depth}, &(I64){_t1871}); _t1872 = *_hp; free(_hp); }
                    (void)_t1872;
                    ;
                    if (_t1872) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1873 = 1;
                    (void)_t1873;
                    U64 _t1874 = U64_add(DEREF(pos), _t1873);
                    (void)_t1874;
                    ;
                    Bool _t1875; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1874}, &(U64){src_len}); _t1875 = *_hp; free(_hp); }
                    (void)_t1875;
                    ;
                    if (_t1875) {
                        U8 *b1 = Str_byte_at(src, pos);
                        (void)b1;
                        U64 _t1855 = 1;
                        (void)_t1855;
                        U64 *_t1856 = malloc(sizeof(U64)); *_t1856 = U64_add(DEREF(pos), _t1855);
                        (void)_t1856;
                        ;
                        U8 *b2 = Str_byte_at(src, _t1856);
                        (void)b2;
                        U8 _t1857 = 47;
                        (void)_t1857;
                        U8 _t1858 = 42;
                        (void)_t1858;
                        Bool _t1859 = U8_eq(DEREF(b1), _t1857);
                        (void)_t1859;
                        ;
                        Bool _t1860 = U8_eq(DEREF(b2), _t1858);
                        (void)_t1860;
                        ;
                        Bool _t1861 = Bool_and(_t1859, _t1860);
                        (void)_t1861;
                        ;
                        ;
                        if (_t1861) {
                            I64 _t1847 = 1;
                            (void)_t1847;
                            I64 _t1848 = I64_add(depth, _t1847);
                            (void)_t1848;
                            ;
                            depth = _t1848;
                            ;
                            U64 _t1849 = 2;
                            (void)_t1849;
                            U64 _t1850 = U64_add(DEREF(pos), _t1849);
                            (void)_t1850;
                            ;
                            *pos = _t1850;
                            ;
                            U64_delete(_t1856, &(Bool){1});
                            ;
                            ;
                            continue;
                        }
                        ;
                        U8 _t1862 = 42;
                        (void)_t1862;
                        U8 _t1863 = 47;
                        (void)_t1863;
                        Bool _t1864 = U8_eq(DEREF(b1), _t1862);
                        (void)_t1864;
                        ;
                        Bool _t1865 = U8_eq(DEREF(b2), _t1863);
                        (void)_t1865;
                        U64_delete(_t1856, &(Bool){1});
                        ;
                        Bool _t1866 = Bool_and(_t1864, _t1865);
                        (void)_t1866;
                        ;
                        ;
                        if (_t1866) {
                            I64 _t1851 = 1;
                            (void)_t1851;
                            I64 _t1852 = I64_sub(depth, _t1851);
                            (void)_t1852;
                            ;
                            depth = _t1852;
                            ;
                            U64 _t1853 = 2;
                            (void)_t1853;
                            U64 _t1854 = U64_add(DEREF(pos), _t1853);
                            (void)_t1854;
                            ;
                            *pos = _t1854;
                            ;
                            ;
                            ;
                            continue;
                        }
                        ;
                    }
                    ;
                    U8 *_t1876 = Str_byte_at(src, pos);
                    (void)_t1876;
                    U8 _t1877 = 10;
                    (void)_t1877;
                    Bool _t1878 = U8_eq(DEREF(_t1876), _t1877);
                    (void)_t1878;
                    ;
                    if (_t1878) {
                        I64 _t1867 = 1;
                        (void)_t1867;
                        I64 _t1868 = I64_add(line, _t1867);
                        (void)_t1868;
                        ;
                        line = _t1868;
                        ;
                        U64 _t1869 = 1;
                        (void)_t1869;
                        U64 _t1870 = U64_add(DEREF(pos), _t1869);
                        (void)_t1870;
                        ;
                        line_start = _t1870;
                        ;
                    }
                    ;
                    U64 _t1879 = U64_inc(DEREF(pos));
                    (void)_t1879;
                    *pos = _t1879;
                    ;
                }
                I64 _t1897 = 0;
                (void)_t1897;
                Bool _t1898; { Bool *_hp = (Bool *)I64_gt(&(I64){depth}, &(I64){_t1897}); _t1898 = *_hp; free(_hp); }
                (void)_t1898;
                ;
                ;
                if (_t1898) {
                    Str *_t1880 = Str_lit("Str", 3ULL);
                    (void)_t1880;
                    U64 _t1881; { U64 *_hp = (U64 *)Str_size(); _t1881 = *_hp; free(_hp); }
                    (void)_t1881;
                    U64 _t1882 = 6;
                    (void)_t1882;
                    Array *_va20 = Array_new(_t1880, &(U64){_t1881}, &(U64){_t1882});
                    (void)_va20;
                    Str_delete(_t1880, &(Bool){1});
                    ;
                    ;
                    U64 _t1883 = 0;
                    (void)_t1883;
                    Str *_t1884 = Str_clone(path);
                    (void)_t1884;
                    Array_set(_va20, &(U64){_t1883}, _t1884);
                    ;
                    U64 _t1885 = 1;
                    (void)_t1885;
                    Str *_t1886 = Str_lit(":", 1ULL);
                    (void)_t1886;
                    Array_set(_va20, &(U64){_t1885}, _t1886);
                    ;
                    U64 _t1887 = 2;
                    (void)_t1887;
                    Str *_t1888 = I64_to_str(&(I64){line});
                    (void)_t1888;
                    Array_set(_va20, &(U64){_t1887}, _t1888);
                    ;
                    U64 _t1889 = 3;
                    (void)_t1889;
                    Str *_t1890 = Str_lit(":", 1ULL);
                    (void)_t1890;
                    Array_set(_va20, &(U64){_t1889}, _t1890);
                    ;
                    U64 _t1891 = 4;
                    (void)_t1891;
                    Str *_t1892 = I64_to_str(&(I64){col});
                    (void)_t1892;
                    Array_set(_va20, &(U64){_t1891}, _t1892);
                    ;
                    U64 _t1893 = 5;
                    (void)_t1893;
                    Str *_t1894 = Str_lit(": error: unterminated comment", 29ULL);
                    (void)_t1894;
                    Array_set(_va20, &(U64){_t1893}, _t1894);
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
        Bool _t2148; { Bool *_hp = (Bool *)is_digit(c); _t2148 = *_hp; free(_hp); }
        (void)_t2148;
        if (_t2148) {
            while (1) {
                Bool _wcond1905; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1905 = *_hp; free(_hp); }
                (void)_wcond1905;
                if (_wcond1905) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1906 = Str_byte_at(src, pos);
                (void)_t1906;
                Bool _t1907; { Bool *_hp = (Bool *)is_digit(_t1906); _t1907 = *_hp; free(_hp); }
                (void)_t1907;
                Bool _t1908 = Bool_not(_t1907);
                (void)_t1908;
                ;
                if (_t1908) {
                    ;
                    break;
                }
                ;
                U64 _t1909 = U64_inc(DEREF(pos));
                (void)_t1909;
                *pos = _t1909;
                ;
            }
            U64 _t1924 = 1;
            (void)_t1924;
            U64 _t1925 = U64_add(DEREF(pos), _t1924);
            (void)_t1925;
            ;
            Bool _t1926; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1925}, &(U64){src_len}); _t1926 = *_hp; free(_hp); }
            (void)_t1926;
            ;
            if (_t1926) {
                U8 *_t1916 = Str_byte_at(src, pos);
                (void)_t1916;
                U8 _t1917 = 46;
                (void)_t1917;
                U64 _t1918 = 1;
                (void)_t1918;
                U64 *_t1919 = malloc(sizeof(U64)); *_t1919 = U64_add(DEREF(pos), _t1918);
                (void)_t1919;
                ;
                U8 *_t1920 = Str_byte_at(src, _t1919);
                (void)_t1920;
                Bool _t1921 = U8_eq(DEREF(_t1916), _t1917);
                (void)_t1921;
                ;
                Bool _t1922; { Bool *_hp = (Bool *)is_digit(_t1920); _t1922 = *_hp; free(_hp); }
                (void)_t1922;
                U64_delete(_t1919, &(Bool){1});
                Bool _t1923 = Bool_and(_t1921, _t1922);
                (void)_t1923;
                ;
                ;
                if (_t1923) {
                    U64 _t1915 = U64_inc(DEREF(pos));
                    (void)_t1915;
                    *pos = _t1915;
                    ;
                    while (1) {
                        Bool _wcond1910; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1910 = *_hp; free(_hp); }
                        (void)_wcond1910;
                        if (_wcond1910) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U8 *_t1911 = Str_byte_at(src, pos);
                        (void)_t1911;
                        Bool _t1912; { Bool *_hp = (Bool *)is_digit(_t1911); _t1912 = *_hp; free(_hp); }
                        (void)_t1912;
                        Bool _t1913 = Bool_not(_t1912);
                        (void)_t1913;
                        ;
                        if (_t1913) {
                            ;
                            break;
                        }
                        ;
                        U64 _t1914 = U64_inc(DEREF(pos));
                        (void)_t1914;
                        *pos = _t1914;
                        ;
                    }
                }
                ;
            }
            ;
            U64 _t1927 = U64_sub(DEREF(pos), start);
            (void)_t1927;
            I64 _t1928 = I64_clone(&(I64){col});
            (void)_t1928;
            Token *_t1929 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(TokenType_Number()); _t1929->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1927}); _t1929->text = *_ca; free(_ca); }
            _t1929->line = I64_clone(&(I64){line});
            _t1929->col = _t1928;
            (void)_t1929;
            ;
            ;
            Vec_push(tokens, _t1929);
            ;
            ;
            ;
            continue;
        }
        ;
        Bool _t2149; { Bool *_hp = (Bool *)is_alpha(c); _t2149 = *_hp; free(_hp); }
        (void)_t2149;
        if (_t2149) {
            while (1) {
                Bool _wcond1930; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1930 = *_hp; free(_hp); }
                (void)_wcond1930;
                if (_wcond1930) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1931 = Str_byte_at(src, pos);
                (void)_t1931;
                Bool _t1932; { Bool *_hp = (Bool *)is_alnum(_t1931); _t1932 = *_hp; free(_hp); }
                (void)_t1932;
                Bool _t1933 = Bool_not(_t1932);
                (void)_t1933;
                ;
                if (_t1933) {
                    ;
                    break;
                }
                ;
                U64 _t1934 = U64_inc(DEREF(pos));
                (void)_t1934;
                *pos = _t1934;
                ;
            }
            U64 _t1935 = U64_sub(DEREF(pos), start);
            (void)_t1935;
            Str *word = Str_substr(src, &(U64){start}, &(U64){_t1935});
            (void)word;
            ;
            TokenType *type = lookup_keyword(word);
            (void)type;
            I64 _t1936 = I64_clone(&(I64){line});
            (void)_t1936;
            I64 _t1937 = I64_clone(&(I64){col});
            (void)_t1937;
            Token *_t1938 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(type); _t1938->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(word); _t1938->text = *_ca; free(_ca); }
            _t1938->line = _t1936;
            _t1938->col = _t1937;
            (void)_t1938;
            ;
            ;
            TokenType_delete(type, &(Bool){1});
            Str_delete(word, &(Bool){1});
            Vec_push(tokens, _t1938);
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t2150 = 34;
        (void)_t2150;
        Bool _t2151 = U8_eq(DEREF(c), _t2150);
        (void)_t2151;
        ;
        if (_t2151) {
            U64 _t1985 = U64_inc(DEREF(pos));
            (void)_t1985;
            *pos = _t1985;
            ;
            while (1) {
                Bool _wcond1939; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1939 = *_hp; free(_hp); }
                (void)_wcond1939;
                if (_wcond1939) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1945 = Str_byte_at(src, pos);
                (void)_t1945;
                U8 _t1946 = 34;
                (void)_t1946;
                Bool _t1947 = U8_eq(DEREF(_t1945), _t1946);
                (void)_t1947;
                ;
                if (_t1947) {
                    ;
                    break;
                }
                ;
                U8 *_t1948 = Str_byte_at(src, pos);
                (void)_t1948;
                U8 _t1949 = 92;
                (void)_t1949;
                U64 _t1950 = 1;
                (void)_t1950;
                U64 _t1951 = U64_add(DEREF(pos), _t1950);
                (void)_t1951;
                ;
                Bool _t1952 = U8_eq(DEREF(_t1948), _t1949);
                (void)_t1952;
                ;
                Bool _t1953; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1951}, &(U64){src_len}); _t1953 = *_hp; free(_hp); }
                (void)_t1953;
                ;
                Bool _t1954 = Bool_and(_t1952, _t1953);
                (void)_t1954;
                ;
                ;
                if (_t1954) {
                    U64 _t1940 = U64_inc(DEREF(pos));
                    (void)_t1940;
                    *pos = _t1940;
                    ;
                }
                ;
                U8 *_t1955 = Str_byte_at(src, pos);
                (void)_t1955;
                U8 _t1956 = 10;
                (void)_t1956;
                Bool _t1957 = U8_eq(DEREF(_t1955), _t1956);
                (void)_t1957;
                ;
                if (_t1957) {
                    I64 _t1941 = 1;
                    (void)_t1941;
                    I64 _t1942 = I64_add(line, _t1941);
                    (void)_t1942;
                    ;
                    line = _t1942;
                    ;
                    U64 _t1943 = 1;
                    (void)_t1943;
                    U64 _t1944 = U64_add(DEREF(pos), _t1943);
                    (void)_t1944;
                    ;
                    line_start = _t1944;
                    ;
                }
                ;
                U64 _t1958 = U64_inc(DEREF(pos));
                (void)_t1958;
                *pos = _t1958;
                ;
            }
            U8 *_t1986 = Str_byte_at(src, pos);
            (void)_t1986;
            U8 _t1987 = 34;
            (void)_t1987;
            Bool _t1988; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t1988 = *_hp; free(_hp); }
            (void)_t1988;
            Bool _t1989 = U8_eq(DEREF(_t1986), _t1987);
            (void)_t1989;
            ;
            Bool _t1990 = Bool_and(_t1988, _t1989);
            (void)_t1990;
            ;
            ;
            if (_t1990) {
                U64 _t1959 = U64_inc(DEREF(pos));
                (void)_t1959;
                *pos = _t1959;
                ;
                U64 _t1960 = 1;
                (void)_t1960;
                U64 _t1961 = U64_sub(DEREF(pos), start);
                (void)_t1961;
                U64 _t1962 = 2;
                (void)_t1962;
                U64 _t1963 = U64_add(start, _t1960);
                (void)_t1963;
                ;
                U64 _t1964 = U64_sub(_t1961, _t1962);
                (void)_t1964;
                ;
                ;
                I64 _t1965 = I64_clone(&(I64){col});
                (void)_t1965;
                Token *_t1966 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_StringTok()); _t1966->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){_t1963}, &(U64){_t1964}); _t1966->text = *_ca; free(_ca); }
                _t1966->line = I64_clone(&(I64){line});
                _t1966->col = _t1965;
                (void)_t1966;
                ;
                ;
                ;
                Vec_push(tokens, _t1966);
            } else {
                Str *_t1967 = Str_lit("Str", 3ULL);
                (void)_t1967;
                U64 _t1968; { U64 *_hp = (U64 *)Str_size(); _t1968 = *_hp; free(_hp); }
                (void)_t1968;
                U64 _t1969 = 6;
                (void)_t1969;
                Array *_va21 = Array_new(_t1967, &(U64){_t1968}, &(U64){_t1969});
                (void)_va21;
                Str_delete(_t1967, &(Bool){1});
                ;
                ;
                U64 _t1970 = 0;
                (void)_t1970;
                Str *_t1971 = Str_clone(path);
                (void)_t1971;
                Array_set(_va21, &(U64){_t1970}, _t1971);
                ;
                U64 _t1972 = 1;
                (void)_t1972;
                Str *_t1973 = Str_lit(":", 1ULL);
                (void)_t1973;
                Array_set(_va21, &(U64){_t1972}, _t1973);
                ;
                U64 _t1974 = 2;
                (void)_t1974;
                Str *_t1975 = I64_to_str(&(I64){line});
                (void)_t1975;
                Array_set(_va21, &(U64){_t1974}, _t1975);
                ;
                U64 _t1976 = 3;
                (void)_t1976;
                Str *_t1977 = Str_lit(":", 1ULL);
                (void)_t1977;
                Array_set(_va21, &(U64){_t1976}, _t1977);
                ;
                U64 _t1978 = 4;
                (void)_t1978;
                Str *_t1979 = I64_to_str(&(I64){col});
                (void)_t1979;
                Array_set(_va21, &(U64){_t1978}, _t1979);
                ;
                U64 _t1980 = 5;
                (void)_t1980;
                Str *_t1981 = Str_lit(": error: unterminated string", 28ULL);
                (void)_t1981;
                Array_set(_va21, &(U64){_t1980}, _t1981);
                ;
                println(_va21);
                U64 _t1982 = U64_sub(DEREF(pos), start);
                (void)_t1982;
                I64 _t1983 = I64_clone(&(I64){col});
                (void)_t1983;
                Token *_t1984 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1984->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1982}); _t1984->text = *_ca; free(_ca); }
                _t1984->line = I64_clone(&(I64){line});
                _t1984->col = _t1983;
                (void)_t1984;
                ;
                ;
                Vec_push(tokens, _t1984);
            }
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t2152 = 39;
        (void)_t2152;
        Bool _t2153 = U8_eq(DEREF(c), _t2152);
        (void)_t2153;
        ;
        if (_t2153) {
            U64 _t2014 = U64_inc(DEREF(pos));
            (void)_t2014;
            *pos = _t2014;
            ;
            U64 ch_start = U64_clone(pos);
            (void)ch_start;
            U8 *_t2015 = Str_byte_at(src, pos);
            (void)_t2015;
            U8 _t2016 = 92;
            (void)_t2016;
            U64 _t2017 = 1;
            (void)_t2017;
            U64 _t2018 = U64_add(DEREF(pos), _t2017);
            (void)_t2018;
            ;
            Bool _t2019 = U8_eq(DEREF(_t2015), _t2016);
            (void)_t2019;
            ;
            Bool _t2020; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2018}, &(U64){src_len}); _t2020 = *_hp; free(_hp); }
            (void)_t2020;
            ;
            Bool _t2021; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2021 = *_hp; free(_hp); }
            (void)_t2021;
            Bool _t2022 = Bool_and(_t2019, _t2020);
            (void)_t2022;
            ;
            ;
            Bool _t2023 = Bool_and(_t2021, _t2022);
            (void)_t2023;
            ;
            ;
            if (_t2023) {
                U64 _t1991 = U64_inc(DEREF(pos));
                (void)_t1991;
                *pos = _t1991;
                ;
            }
            ;
            U64 _t2024 = U64_inc(DEREF(pos));
            (void)_t2024;
            *pos = _t2024;
            ;
            U8 *_t2025 = Str_byte_at(src, pos);
            (void)_t2025;
            U8 _t2026 = 39;
            (void)_t2026;
            Bool _t2027; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2027 = *_hp; free(_hp); }
            (void)_t2027;
            Bool _t2028 = U8_eq(DEREF(_t2025), _t2026);
            (void)_t2028;
            ;
            Bool _t2029 = Bool_and(_t2027, _t2028);
            (void)_t2029;
            ;
            ;
            if (_t2029) {
                U64 _t1992 = U64_sub(DEREF(pos), ch_start);
                (void)_t1992;
                I64 _t1993 = I64_clone(&(I64){col});
                (void)_t1993;
                Token *_t1994 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Char()); _t1994->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){ch_start}, &(U64){_t1992}); _t1994->text = *_ca; free(_ca); }
                _t1994->line = I64_clone(&(I64){line});
                _t1994->col = _t1993;
                (void)_t1994;
                ;
                ;
                Vec_push(tokens, _t1994);
                U64 _t1995 = U64_inc(DEREF(pos));
                (void)_t1995;
                *pos = _t1995;
                ;
            } else {
                Str *_t1996 = Str_lit("Str", 3ULL);
                (void)_t1996;
                U64 _t1997; { U64 *_hp = (U64 *)Str_size(); _t1997 = *_hp; free(_hp); }
                (void)_t1997;
                U64 _t1998 = 6;
                (void)_t1998;
                Array *_va22 = Array_new(_t1996, &(U64){_t1997}, &(U64){_t1998});
                (void)_va22;
                Str_delete(_t1996, &(Bool){1});
                ;
                ;
                U64 _t1999 = 0;
                (void)_t1999;
                Str *_t2000 = Str_clone(path);
                (void)_t2000;
                Array_set(_va22, &(U64){_t1999}, _t2000);
                ;
                U64 _t2001 = 1;
                (void)_t2001;
                Str *_t2002 = Str_lit(":", 1ULL);
                (void)_t2002;
                Array_set(_va22, &(U64){_t2001}, _t2002);
                ;
                U64 _t2003 = 2;
                (void)_t2003;
                Str *_t2004 = I64_to_str(&(I64){line});
                (void)_t2004;
                Array_set(_va22, &(U64){_t2003}, _t2004);
                ;
                U64 _t2005 = 3;
                (void)_t2005;
                Str *_t2006 = Str_lit(":", 1ULL);
                (void)_t2006;
                Array_set(_va22, &(U64){_t2005}, _t2006);
                ;
                U64 _t2007 = 4;
                (void)_t2007;
                Str *_t2008 = I64_to_str(&(I64){col});
                (void)_t2008;
                Array_set(_va22, &(U64){_t2007}, _t2008);
                ;
                U64 _t2009 = 5;
                (void)_t2009;
                Str *_t2010 = Str_lit(": error: unterminated character literal", 39ULL);
                (void)_t2010;
                Array_set(_va22, &(U64){_t2009}, _t2010);
                ;
                println(_va22);
                U64 _t2011 = U64_sub(DEREF(pos), start);
                (void)_t2011;
                I64 _t2012 = I64_clone(&(I64){col});
                (void)_t2012;
                Token *_t2013 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2013->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t2011}); _t2013->text = *_ca; free(_ca); }
                _t2013->line = I64_clone(&(I64){line});
                _t2013->col = _t2012;
                (void)_t2013;
                ;
                ;
                Vec_push(tokens, _t2013);
            }
            ;
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U64 _t2154 = 1;
        (void)_t2154;
        U64 _t2155 = U64_add(DEREF(pos), _t2154);
        (void)_t2155;
        ;
        Bool _t2156; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2155}, &(U64){src_len}); _t2156 = *_hp; free(_hp); }
        (void)_t2156;
        ;
        if (_t2156) {
            U64 _t2073 = 1;
            (void)_t2073;
            U64 *_t2074 = malloc(sizeof(U64)); *_t2074 = U64_add(DEREF(pos), _t2073);
            (void)_t2074;
            ;
            U8 *c2 = Str_byte_at(src, _t2074);
            (void)c2;
            TokenType *two = TokenType_clone(TokenType_Eof());
            (void)two;
            U8 _t2075 = 58;
            (void)_t2075;
            U8 _t2076 = 61;
            (void)_t2076;
            Bool _t2077 = U8_eq(DEREF(c), _t2075);
            (void)_t2077;
            ;
            Bool _t2078 = U8_eq(DEREF(c2), _t2076);
            (void)_t2078;
            ;
            Bool _t2079 = Bool_and(_t2077, _t2078);
            (void)_t2079;
            ;
            ;
            if (_t2079) {
                two = TokenType_clone(TokenType_ColonEq());
            } else {
                U8 _t2062 = 61;
                (void)_t2062;
                U8 _t2063 = 61;
                (void)_t2063;
                Bool _t2064 = U8_eq(DEREF(c), _t2062);
                (void)_t2064;
                ;
                Bool _t2065 = U8_eq(DEREF(c2), _t2063);
                (void)_t2065;
                ;
                Bool _t2066 = Bool_and(_t2064, _t2065);
                (void)_t2066;
                ;
                ;
                if (_t2066) {
                    two = TokenType_clone(TokenType_EqEq());
                } else {
                    U8 _t2057 = 33;
                    (void)_t2057;
                    U8 _t2058 = 61;
                    (void)_t2058;
                    Bool _t2059 = U8_eq(DEREF(c), _t2057);
                    (void)_t2059;
                    ;
                    Bool _t2060 = U8_eq(DEREF(c2), _t2058);
                    (void)_t2060;
                    ;
                    Bool _t2061 = Bool_and(_t2059, _t2060);
                    (void)_t2061;
                    ;
                    ;
                    if (_t2061) {
                        two = TokenType_clone(TokenType_Neq());
                    } else {
                        U8 _t2052 = 60;
                        (void)_t2052;
                        U8 _t2053 = 61;
                        (void)_t2053;
                        Bool _t2054 = U8_eq(DEREF(c), _t2052);
                        (void)_t2054;
                        ;
                        Bool _t2055 = U8_eq(DEREF(c2), _t2053);
                        (void)_t2055;
                        ;
                        Bool _t2056 = Bool_and(_t2054, _t2055);
                        (void)_t2056;
                        ;
                        ;
                        if (_t2056) {
                            two = TokenType_clone(TokenType_LtEq());
                        } else {
                            U8 _t2047 = 62;
                            (void)_t2047;
                            U8 _t2048 = 61;
                            (void)_t2048;
                            Bool _t2049 = U8_eq(DEREF(c), _t2047);
                            (void)_t2049;
                            ;
                            Bool _t2050 = U8_eq(DEREF(c2), _t2048);
                            (void)_t2050;
                            ;
                            Bool _t2051 = Bool_and(_t2049, _t2050);
                            (void)_t2051;
                            ;
                            ;
                            if (_t2051) {
                                two = TokenType_clone(TokenType_GtEq());
                            } else {
                                U8 _t2042 = 46;
                                (void)_t2042;
                                U8 _t2043 = 46;
                                (void)_t2043;
                                Bool _t2044 = U8_eq(DEREF(c), _t2042);
                                (void)_t2044;
                                ;
                                Bool _t2045 = U8_eq(DEREF(c2), _t2043);
                                (void)_t2045;
                                ;
                                Bool _t2046 = Bool_and(_t2044, _t2045);
                                (void)_t2046;
                                ;
                                ;
                                if (_t2046) {
                                    U64 _t2039 = 2;
                                    (void)_t2039;
                                    U64 _t2040 = U64_add(DEREF(pos), _t2039);
                                    (void)_t2040;
                                    ;
                                    Bool _t2041; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2040}, &(U64){src_len}); _t2041 = *_hp; free(_hp); }
                                    (void)_t2041;
                                    ;
                                    if (_t2041) {
                                        U64 _t2035 = 2;
                                        (void)_t2035;
                                        U64 *_t2036 = malloc(sizeof(U64)); *_t2036 = U64_add(DEREF(pos), _t2035);
                                        (void)_t2036;
                                        ;
                                        U8 *c3 = Str_byte_at(src, _t2036);
                                        (void)c3;
                                        U8 _t2037 = 46;
                                        (void)_t2037;
                                        Bool _t2038 = U8_eq(DEREF(c3), _t2037);
                                        (void)_t2038;
                                        U64_delete(_t2036, &(Bool){1});
                                        ;
                                        if (_t2038) {
                                            U64 _t2030 = 3;
                                            (void)_t2030;
                                            I64 _t2031 = I64_clone(&(I64){col});
                                            (void)_t2031;
                                            Token *_t2032 = malloc(sizeof(Token));
                                            { TokenType *_ca = TokenType_clone(TokenType_DotDotDot()); _t2032->type = *_ca; free(_ca); }
                                            { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t2030}); _t2032->text = *_ca; free(_ca); }
                                            _t2032->line = I64_clone(&(I64){line});
                                            _t2032->col = _t2031;
                                            (void)_t2032;
                                            ;
                                            ;
                                            Vec_push(tokens, _t2032);
                                            U64 _t2033 = 3;
                                            (void)_t2033;
                                            U64 _t2034 = U64_add(DEREF(pos), _t2033);
                                            (void)_t2034;
                                            ;
                                            *pos = _t2034;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            U64_delete(_t2074, &(Bool){1});
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
            U64_delete(_t2074, &(Bool){1});
            ;
            Bool _t2080; { Bool *_hp = (Bool *)TokenType_eq(two, TokenType_Eof()); _t2080 = *_hp; free(_hp); }
            (void)_t2080;
            Bool _t2081 = Bool_not(_t2080);
            (void)_t2081;
            ;
            if (_t2081) {
                U64 _t2067 = 2;
                (void)_t2067;
                I64 _t2068 = I64_clone(&(I64){line});
                (void)_t2068;
                I64 _t2069 = I64_clone(&(I64){col});
                (void)_t2069;
                Token *_t2070 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(two); _t2070->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t2067}); _t2070->text = *_ca; free(_ca); }
                _t2070->line = _t2068;
                _t2070->col = _t2069;
                (void)_t2070;
                ;
                ;
                ;
                Vec_push(tokens, _t2070);
                U64 _t2071 = 2;
                (void)_t2071;
                U64 _t2072 = U64_add(DEREF(pos), _t2071);
                (void)_t2072;
                ;
                *pos = _t2072;
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
            U8 _sw2082 = U8_clone(c);
            (void)_sw2082;
            U8 _t2117 = 40;
            (void)_t2117;
            Bool _t2118 = U8_eq(_sw2082, _t2117);
            (void)_t2118;
            ;
            if (_t2118) {
                single = TokenType_clone(TokenType_LParen());
            } else {
                U8 _t2115 = 41;
                (void)_t2115;
                Bool _t2116 = U8_eq(_sw2082, _t2115);
                (void)_t2116;
                ;
                if (_t2116) {
                    single = TokenType_clone(TokenType_RParen());
                } else {
                    U8 _t2113 = 123;
                    (void)_t2113;
                    Bool _t2114 = U8_eq(_sw2082, _t2113);
                    (void)_t2114;
                    ;
                    if (_t2114) {
                        single = TokenType_clone(TokenType_LBrace());
                    } else {
                        U8 _t2111 = 125;
                        (void)_t2111;
                        Bool _t2112 = U8_eq(_sw2082, _t2111);
                        (void)_t2112;
                        ;
                        if (_t2112) {
                            single = TokenType_clone(TokenType_RBrace());
                        } else {
                            U8 _t2109 = 91;
                            (void)_t2109;
                            Bool _t2110 = U8_eq(_sw2082, _t2109);
                            (void)_t2110;
                            ;
                            if (_t2110) {
                                single = TokenType_clone(TokenType_LBracket());
                            } else {
                                U8 _t2107 = 93;
                                (void)_t2107;
                                Bool _t2108 = U8_eq(_sw2082, _t2107);
                                (void)_t2108;
                                ;
                                if (_t2108) {
                                    single = TokenType_clone(TokenType_RBracket());
                                } else {
                                    U8 _t2105 = 44;
                                    (void)_t2105;
                                    Bool _t2106 = U8_eq(_sw2082, _t2105);
                                    (void)_t2106;
                                    ;
                                    if (_t2106) {
                                        single = TokenType_clone(TokenType_Comma());
                                    } else {
                                        U8 _t2103 = 58;
                                        (void)_t2103;
                                        Bool _t2104 = U8_eq(_sw2082, _t2103);
                                        (void)_t2104;
                                        ;
                                        if (_t2104) {
                                            single = TokenType_clone(TokenType_Colon());
                                        } else {
                                            U8 _t2101 = 46;
                                            (void)_t2101;
                                            Bool _t2102 = U8_eq(_sw2082, _t2101);
                                            (void)_t2102;
                                            ;
                                            if (_t2102) {
                                                single = TokenType_clone(TokenType_Dot());
                                            } else {
                                                U8 _t2099 = 63;
                                                (void)_t2099;
                                                Bool _t2100 = U8_eq(_sw2082, _t2099);
                                                (void)_t2100;
                                                ;
                                                if (_t2100) {
                                                    single = TokenType_clone(TokenType_Question());
                                                } else {
                                                    U8 _t2097 = 33;
                                                    (void)_t2097;
                                                    Bool _t2098 = U8_eq(_sw2082, _t2097);
                                                    (void)_t2098;
                                                    ;
                                                    if (_t2098) {
                                                        single = TokenType_clone(TokenType_Bang());
                                                    } else {
                                                        U8 _t2095 = 43;
                                                        (void)_t2095;
                                                        Bool _t2096 = U8_eq(_sw2082, _t2095);
                                                        (void)_t2096;
                                                        ;
                                                        if (_t2096) {
                                                            single = TokenType_clone(TokenType_Plus());
                                                        } else {
                                                            U8 _t2093 = 45;
                                                            (void)_t2093;
                                                            Bool _t2094 = U8_eq(_sw2082, _t2093);
                                                            (void)_t2094;
                                                            ;
                                                            if (_t2094) {
                                                                single = TokenType_clone(TokenType_Minus());
                                                            } else {
                                                                U8 _t2091 = 42;
                                                                (void)_t2091;
                                                                Bool _t2092 = U8_eq(_sw2082, _t2091);
                                                                (void)_t2092;
                                                                ;
                                                                if (_t2092) {
                                                                    single = TokenType_clone(TokenType_Star());
                                                                } else {
                                                                    U8 _t2089 = 47;
                                                                    (void)_t2089;
                                                                    Bool _t2090 = U8_eq(_sw2082, _t2089);
                                                                    (void)_t2090;
                                                                    ;
                                                                    if (_t2090) {
                                                                        single = TokenType_clone(TokenType_Slash());
                                                                    } else {
                                                                        U8 _t2087 = 61;
                                                                        (void)_t2087;
                                                                        Bool _t2088 = U8_eq(_sw2082, _t2087);
                                                                        (void)_t2088;
                                                                        ;
                                                                        if (_t2088) {
                                                                            single = TokenType_clone(TokenType_Eq());
                                                                        } else {
                                                                            U8 _t2085 = 60;
                                                                            (void)_t2085;
                                                                            Bool _t2086 = U8_eq(_sw2082, _t2085);
                                                                            (void)_t2086;
                                                                            ;
                                                                            if (_t2086) {
                                                                                single = TokenType_clone(TokenType_Lt());
                                                                            } else {
                                                                                U8 _t2083 = 62;
                                                                                (void)_t2083;
                                                                                Bool _t2084 = U8_eq(_sw2082, _t2083);
                                                                                (void)_t2084;
                                                                                ;
                                                                                if (_t2084) {
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
        Bool _t2157; { Bool *_hp = (Bool *)TokenType_eq(single, TokenType_Eof()); _t2157 = *_hp; free(_hp); }
        (void)_t2157;
        Bool _t2158 = Bool_not(_t2157);
        (void)_t2158;
        ;
        if (_t2158) {
            U64 _t2119 = 1;
            (void)_t2119;
            I64 _t2120 = I64_clone(&(I64){line});
            (void)_t2120;
            I64 _t2121 = I64_clone(&(I64){col});
            (void)_t2121;
            Token *_t2122 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(single); _t2122->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t2119}); _t2122->text = *_ca; free(_ca); }
            _t2122->line = _t2120;
            _t2122->col = _t2121;
            (void)_t2122;
            ;
            ;
            ;
            Vec_push(tokens, _t2122);
            U64 _t2123 = U64_inc(DEREF(pos));
            (void)_t2123;
            *pos = _t2123;
            ;
            ;
            ;
            TokenType_delete(single, &(Bool){1});
            ;
            continue;
        }
        ;
        TokenType_delete(single, &(Bool){1});
        Str *_t2159 = Str_lit("Str", 3ULL);
        (void)_t2159;
        U64 _t2160; { U64 *_hp = (U64 *)Str_size(); _t2160 = *_hp; free(_hp); }
        (void)_t2160;
        U64 _t2161 = 6;
        (void)_t2161;
        Array *_va23 = Array_new(_t2159, &(U64){_t2160}, &(U64){_t2161});
        (void)_va23;
        Str_delete(_t2159, &(Bool){1});
        ;
        ;
        U64 _t2162 = 0;
        (void)_t2162;
        Str *_t2163 = Str_clone(path);
        (void)_t2163;
        Array_set(_va23, &(U64){_t2162}, _t2163);
        ;
        U64 _t2164 = 1;
        (void)_t2164;
        Str *_t2165 = Str_lit(":", 1ULL);
        (void)_t2165;
        Array_set(_va23, &(U64){_t2164}, _t2165);
        ;
        U64 _t2166 = 2;
        (void)_t2166;
        Str *_t2167 = I64_to_str(&(I64){line});
        (void)_t2167;
        Array_set(_va23, &(U64){_t2166}, _t2167);
        ;
        U64 _t2168 = 3;
        (void)_t2168;
        Str *_t2169 = Str_lit(":", 1ULL);
        (void)_t2169;
        Array_set(_va23, &(U64){_t2168}, _t2169);
        ;
        U64 _t2170 = 4;
        (void)_t2170;
        Str *_t2171 = I64_to_str(&(I64){col});
        (void)_t2171;
        Array_set(_va23, &(U64){_t2170}, _t2171);
        ;
        U64 _t2172 = 5;
        (void)_t2172;
        Str *_t2173 = Str_lit(": error: unexpected character", 29ULL);
        (void)_t2173;
        Array_set(_va23, &(U64){_t2172}, _t2173);
        ;
        println(_va23);
        U64 _t2174 = 1;
        (void)_t2174;
        I64 _t2175 = I64_clone(&(I64){col});
        (void)_t2175;
        ;
        Token *_t2176 = malloc(sizeof(Token));
        { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2176->type = *_ca; free(_ca); }
        { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t2174}); _t2176->text = *_ca; free(_ca); }
        _t2176->line = I64_clone(&(I64){line});
        _t2176->col = _t2175;
        (void)_t2176;
        ;
        ;
        ;
        Vec_push(tokens, _t2176);
        U64 _t2177 = U64_inc(DEREF(pos));
        (void)_t2177;
        *pos = _t2177;
        ;
    }
    ;
    U64 _t2180 = U64_sub(DEREF(pos), line_start);
    (void)_t2180;
    ;
    U64_delete(pos, &(Bool){1});
    U64 _t2181 = 1;
    (void)_t2181;
    U64 _t2182 = U64_add(_t2180, _t2181);
    (void)_t2182;
    ;
    ;
    I64 col = U64_to_i64(_t2182);
    (void)col;
    ;
    I64 _t2183 = I64_clone(&(I64){col});
    (void)_t2183;
    ;
    Token *_t2184 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(TokenType_Eof()); _t2184->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t2184->text = *_ca; free(_ca); }
    _t2184->line = I64_clone(&(I64){line});
    _t2184->col = _t2183;
    (void)_t2184;
    ;
    ;
    Vec_push(tokens, _t2184);
    return tokens;
}

