#include "til_lexer.h"

Token * Token_clone(Token * self) {
    (void)self;
    U32 _t1598 = U32_clone(&self->line);
    (void)_t1598;
    U32 _t1599 = U32_clone(&self->col);
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

void Token_delete(Token * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1601 = 0;
    (void)_t1601;
    TokenType_delete(&self->type, &(Bool){_t1601});
    ;
    Bool _t1602 = 0;
    (void)_t1602;
    Str_delete(&self->text, &(Bool){_t1602});
    ;
    Bool _t1603 = 0;
    (void)_t1603;
    U32_delete(&self->line, &(Bool){_t1603});
    ;
    Bool _t1604 = 0;
    (void)_t1604;
    U32_delete(&self->col, &(Bool){_t1604});
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
    Str *_t2191 = Str_lit("Token", 5ULL);
    (void)_t2191;
    U64 _t2192; { U64 *_hp = (U64 *)Token_size(); _t2192 = *_hp; free(_hp); }
    (void)_t2192;
    Vec *tokens = Vec_new(_t2191, &(U64){_t2192});
    (void)tokens;
    Str_delete(_t2191, &(Bool){1});
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
        U8 _t2135 = 32;
        (void)_t2135;
        U8 _t2136 = 9;
        (void)_t2136;
        Bool _t2137 = U8_eq(DEREF(c), _t2135);
        (void)_t2137;
        ;
        Bool _t2138 = U8_eq(DEREF(c), _t2136);
        (void)_t2138;
        ;
        U8 _t2139 = 13;
        (void)_t2139;
        Bool _t2140 = Bool_or(_t2137, _t2138);
        (void)_t2140;
        ;
        ;
        Bool _t2141 = U8_eq(DEREF(c), _t2139);
        (void)_t2141;
        ;
        U8 _t2142 = 59;
        (void)_t2142;
        Bool _t2143 = Bool_or(_t2140, _t2141);
        (void)_t2143;
        ;
        ;
        Bool _t2144 = U8_eq(DEREF(c), _t2142);
        (void)_t2144;
        ;
        Bool _t2145 = Bool_or(_t2143, _t2144);
        (void)_t2145;
        ;
        ;
        if (_t2145) {
            U64 _t1834 = U64_inc(DEREF(pos));
            (void)_t1834;
            *pos = _t1834;
            ;
            ;
            continue;
        }
        ;
        U8 _t2146 = 10;
        (void)_t2146;
        Bool _t2147 = U8_eq(DEREF(c), _t2146);
        (void)_t2147;
        ;
        if (_t2147) {
            U64 _t1835 = U64_inc(DEREF(pos));
            (void)_t1835;
            *pos = _t1835;
            ;
            U32 _t1836 = 1;
            (void)_t1836;
            U32 _t1837 = U32_add(line, _t1836);
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
        U64 _t2148 = U64_sub(DEREF(pos), line_start);
        (void)_t2148;
        U64 _t2149 = 1;
        (void)_t2149;
        U64 _t2150 = U64_add(_t2148, _t2149);
        (void)_t2150;
        ;
        ;
        I64 _t2151 = U64_to_i64(_t2150);
        (void)_t2151;
        ;
        U32 col = I64_to_u32(_t2151);
        (void)col;
        ;
        U64 start = U64_clone(pos);
        (void)start;
        U8 _t2152 = 35;
        (void)_t2152;
        Bool _t2153 = U8_eq(DEREF(c), _t2152);
        (void)_t2153;
        ;
        if (_t2153) {
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
        U8 _t2154 = 47;
        (void)_t2154;
        U64 _t2155 = 1;
        (void)_t2155;
        U64 _t2156 = U64_add(DEREF(pos), _t2155);
        (void)_t2156;
        ;
        Bool _t2157 = U8_eq(DEREF(c), _t2154);
        (void)_t2157;
        ;
        Bool _t2158; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2156}, &(U64){src_len}); _t2158 = *_hp; free(_hp); }
        (void)_t2158;
        ;
        Bool _t2159 = Bool_and(_t2157, _t2158);
        (void)_t2159;
        ;
        ;
        if (_t2159) {
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
                        U32 _t1870 = 1;
                        (void)_t1870;
                        U32 _t1871 = U32_add(line, _t1870);
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
                    Str *_t1891 = U32_to_str(&(U32){line});
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
                    Str *_t1895 = U32_to_str(&(U32){col});
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
        Bool _t2160; { Bool *_hp = (Bool *)is_digit(c); _t2160 = *_hp; free(_hp); }
        (void)_t2160;
        if (_t2160) {
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
            Str *_t1931 = Str_substr(src, &(U64){start}, &(U64){_t1930});
            (void)_t1931;
            ;
            U32 _t1932 = U32_clone(&(U32){col});
            (void)_t1932;
            Token *_t1933 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(TokenType_Number()); _t1933->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(_t1931); _t1933->text = *_ca; free(_ca); }
            _t1933->line = U32_clone(&(U32){line});
            _t1933->col = _t1932;
            (void)_t1933;
            Str_delete(_t1931, &(Bool){1});
            ;
            Vec_push(tokens, _t1933);
            ;
            ;
            ;
            continue;
        }
        ;
        Bool _t2161; { Bool *_hp = (Bool *)is_alpha(c); _t2161 = *_hp; free(_hp); }
        (void)_t2161;
        if (_t2161) {
            while (1) {
                Bool _wcond1934; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1934 = *_hp; free(_hp); }
                (void)_wcond1934;
                if (_wcond1934) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1935 = Str_byte_at(src, pos);
                (void)_t1935;
                Bool _t1936; { Bool *_hp = (Bool *)is_alnum(_t1935); _t1936 = *_hp; free(_hp); }
                (void)_t1936;
                Bool _t1937 = Bool_not(_t1936);
                (void)_t1937;
                ;
                if (_t1937) {
                    ;
                    break;
                }
                ;
                U64 _t1938 = U64_inc(DEREF(pos));
                (void)_t1938;
                *pos = _t1938;
                ;
            }
            U64 _t1939 = U64_sub(DEREF(pos), start);
            (void)_t1939;
            Str *word = Str_substr(src, &(U64){start}, &(U64){_t1939});
            (void)word;
            ;
            TokenType *type = lookup_keyword(word);
            (void)type;
            U32 _t1940 = U32_clone(&(U32){line});
            (void)_t1940;
            U32 _t1941 = U32_clone(&(U32){col});
            (void)_t1941;
            Token *_t1942 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(type); _t1942->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(word); _t1942->text = *_ca; free(_ca); }
            _t1942->line = _t1940;
            _t1942->col = _t1941;
            (void)_t1942;
            ;
            ;
            TokenType_delete(type, &(Bool){1});
            Str_delete(word, &(Bool){1});
            Vec_push(tokens, _t1942);
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t2162 = 34;
        (void)_t2162;
        Bool _t2163 = U8_eq(DEREF(c), _t2162);
        (void)_t2163;
        ;
        if (_t2163) {
            U64 _t1991 = U64_inc(DEREF(pos));
            (void)_t1991;
            *pos = _t1991;
            ;
            while (1) {
                Bool _wcond1943; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1943 = *_hp; free(_hp); }
                (void)_wcond1943;
                if (_wcond1943) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1949 = Str_byte_at(src, pos);
                (void)_t1949;
                U8 _t1950 = 34;
                (void)_t1950;
                Bool _t1951 = U8_eq(DEREF(_t1949), _t1950);
                (void)_t1951;
                ;
                if (_t1951) {
                    ;
                    break;
                }
                ;
                U8 *_t1952 = Str_byte_at(src, pos);
                (void)_t1952;
                U8 _t1953 = 92;
                (void)_t1953;
                U64 _t1954 = 1;
                (void)_t1954;
                U64 _t1955 = U64_add(DEREF(pos), _t1954);
                (void)_t1955;
                ;
                Bool _t1956 = U8_eq(DEREF(_t1952), _t1953);
                (void)_t1956;
                ;
                Bool _t1957; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1955}, &(U64){src_len}); _t1957 = *_hp; free(_hp); }
                (void)_t1957;
                ;
                Bool _t1958 = Bool_and(_t1956, _t1957);
                (void)_t1958;
                ;
                ;
                if (_t1958) {
                    U64 _t1944 = U64_inc(DEREF(pos));
                    (void)_t1944;
                    *pos = _t1944;
                    ;
                }
                ;
                U8 *_t1959 = Str_byte_at(src, pos);
                (void)_t1959;
                U8 _t1960 = 10;
                (void)_t1960;
                Bool _t1961 = U8_eq(DEREF(_t1959), _t1960);
                (void)_t1961;
                ;
                if (_t1961) {
                    U32 _t1945 = 1;
                    (void)_t1945;
                    U32 _t1946 = U32_add(line, _t1945);
                    (void)_t1946;
                    ;
                    line = _t1946;
                    ;
                    U64 _t1947 = 1;
                    (void)_t1947;
                    U64 _t1948 = U64_add(DEREF(pos), _t1947);
                    (void)_t1948;
                    ;
                    line_start = _t1948;
                    ;
                }
                ;
                U64 _t1962 = U64_inc(DEREF(pos));
                (void)_t1962;
                *pos = _t1962;
                ;
            }
            U8 *_t1992 = Str_byte_at(src, pos);
            (void)_t1992;
            U8 _t1993 = 34;
            (void)_t1993;
            Bool _t1994; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t1994 = *_hp; free(_hp); }
            (void)_t1994;
            Bool _t1995 = U8_eq(DEREF(_t1992), _t1993);
            (void)_t1995;
            ;
            Bool _t1996 = Bool_and(_t1994, _t1995);
            (void)_t1996;
            ;
            ;
            if (_t1996) {
                U64 _t1963 = U64_inc(DEREF(pos));
                (void)_t1963;
                *pos = _t1963;
                ;
                U64 _t1964 = 1;
                (void)_t1964;
                U64 _t1965 = U64_sub(DEREF(pos), start);
                (void)_t1965;
                U64 _t1966 = 2;
                (void)_t1966;
                U64 _t1967 = U64_add(start, _t1964);
                (void)_t1967;
                ;
                U64 _t1968 = U64_sub(_t1965, _t1966);
                (void)_t1968;
                ;
                ;
                Str *_t1969 = Str_substr(src, &(U64){_t1967}, &(U64){_t1968});
                (void)_t1969;
                ;
                ;
                U32 _t1970 = U32_clone(&(U32){col});
                (void)_t1970;
                Token *_t1971 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_StringTok()); _t1971->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t1969); _t1971->text = *_ca; free(_ca); }
                _t1971->line = U32_clone(&(U32){line});
                _t1971->col = _t1970;
                (void)_t1971;
                Str_delete(_t1969, &(Bool){1});
                ;
                Vec_push(tokens, _t1971);
            } else {
                Str *_t1972 = Str_lit("Str", 3ULL);
                (void)_t1972;
                U64 _t1973; { U64 *_hp = (U64 *)Str_size(); _t1973 = *_hp; free(_hp); }
                (void)_t1973;
                U64 _t1974 = 6;
                (void)_t1974;
                Array *_va21 = Array_new(_t1972, &(U64){_t1973}, &(U64){_t1974});
                (void)_va21;
                Str_delete(_t1972, &(Bool){1});
                ;
                ;
                U64 _t1975 = 0;
                (void)_t1975;
                Str *_t1976 = Str_clone(path);
                (void)_t1976;
                Array_set(_va21, &(U64){_t1975}, _t1976);
                ;
                U64 _t1977 = 1;
                (void)_t1977;
                Str *_t1978 = Str_lit(":", 1ULL);
                (void)_t1978;
                Array_set(_va21, &(U64){_t1977}, _t1978);
                ;
                U64 _t1979 = 2;
                (void)_t1979;
                Str *_t1980 = U32_to_str(&(U32){line});
                (void)_t1980;
                Array_set(_va21, &(U64){_t1979}, _t1980);
                ;
                U64 _t1981 = 3;
                (void)_t1981;
                Str *_t1982 = Str_lit(":", 1ULL);
                (void)_t1982;
                Array_set(_va21, &(U64){_t1981}, _t1982);
                ;
                U64 _t1983 = 4;
                (void)_t1983;
                Str *_t1984 = U32_to_str(&(U32){col});
                (void)_t1984;
                Array_set(_va21, &(U64){_t1983}, _t1984);
                ;
                U64 _t1985 = 5;
                (void)_t1985;
                Str *_t1986 = Str_lit(": error: unterminated string", 28ULL);
                (void)_t1986;
                Array_set(_va21, &(U64){_t1985}, _t1986);
                ;
                println(_va21);
                U64 _t1987 = U64_sub(DEREF(pos), start);
                (void)_t1987;
                Str *_t1988 = Str_substr(src, &(U64){start}, &(U64){_t1987});
                (void)_t1988;
                ;
                U32 _t1989 = U32_clone(&(U32){col});
                (void)_t1989;
                Token *_t1990 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1990->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t1988); _t1990->text = *_ca; free(_ca); }
                _t1990->line = U32_clone(&(U32){line});
                _t1990->col = _t1989;
                (void)_t1990;
                Str_delete(_t1988, &(Bool){1});
                ;
                Vec_push(tokens, _t1990);
            }
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t2164 = 39;
        (void)_t2164;
        Bool _t2165 = U8_eq(DEREF(c), _t2164);
        (void)_t2165;
        ;
        if (_t2165) {
            U64 _t2022 = U64_inc(DEREF(pos));
            (void)_t2022;
            *pos = _t2022;
            ;
            U64 ch_start = U64_clone(pos);
            (void)ch_start;
            U8 *_t2023 = Str_byte_at(src, pos);
            (void)_t2023;
            U8 _t2024 = 92;
            (void)_t2024;
            U64 _t2025 = 1;
            (void)_t2025;
            U64 _t2026 = U64_add(DEREF(pos), _t2025);
            (void)_t2026;
            ;
            Bool _t2027 = U8_eq(DEREF(_t2023), _t2024);
            (void)_t2027;
            ;
            Bool _t2028; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2026}, &(U64){src_len}); _t2028 = *_hp; free(_hp); }
            (void)_t2028;
            ;
            Bool _t2029; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2029 = *_hp; free(_hp); }
            (void)_t2029;
            Bool _t2030 = Bool_and(_t2027, _t2028);
            (void)_t2030;
            ;
            ;
            Bool _t2031 = Bool_and(_t2029, _t2030);
            (void)_t2031;
            ;
            ;
            if (_t2031) {
                U64 _t1997 = U64_inc(DEREF(pos));
                (void)_t1997;
                *pos = _t1997;
                ;
            }
            ;
            U64 _t2032 = U64_inc(DEREF(pos));
            (void)_t2032;
            *pos = _t2032;
            ;
            U8 *_t2033 = Str_byte_at(src, pos);
            (void)_t2033;
            U8 _t2034 = 39;
            (void)_t2034;
            Bool _t2035; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2035 = *_hp; free(_hp); }
            (void)_t2035;
            Bool _t2036 = U8_eq(DEREF(_t2033), _t2034);
            (void)_t2036;
            ;
            Bool _t2037 = Bool_and(_t2035, _t2036);
            (void)_t2037;
            ;
            ;
            if (_t2037) {
                U64 _t1998 = U64_sub(DEREF(pos), ch_start);
                (void)_t1998;
                Str *_t1999 = Str_substr(src, &(U64){ch_start}, &(U64){_t1998});
                (void)_t1999;
                ;
                U32 _t2000 = U32_clone(&(U32){col});
                (void)_t2000;
                Token *_t2001 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Char()); _t2001->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t1999); _t2001->text = *_ca; free(_ca); }
                _t2001->line = U32_clone(&(U32){line});
                _t2001->col = _t2000;
                (void)_t2001;
                Str_delete(_t1999, &(Bool){1});
                ;
                Vec_push(tokens, _t2001);
                U64 _t2002 = U64_inc(DEREF(pos));
                (void)_t2002;
                *pos = _t2002;
                ;
            } else {
                Str *_t2003 = Str_lit("Str", 3ULL);
                (void)_t2003;
                U64 _t2004; { U64 *_hp = (U64 *)Str_size(); _t2004 = *_hp; free(_hp); }
                (void)_t2004;
                U64 _t2005 = 6;
                (void)_t2005;
                Array *_va22 = Array_new(_t2003, &(U64){_t2004}, &(U64){_t2005});
                (void)_va22;
                Str_delete(_t2003, &(Bool){1});
                ;
                ;
                U64 _t2006 = 0;
                (void)_t2006;
                Str *_t2007 = Str_clone(path);
                (void)_t2007;
                Array_set(_va22, &(U64){_t2006}, _t2007);
                ;
                U64 _t2008 = 1;
                (void)_t2008;
                Str *_t2009 = Str_lit(":", 1ULL);
                (void)_t2009;
                Array_set(_va22, &(U64){_t2008}, _t2009);
                ;
                U64 _t2010 = 2;
                (void)_t2010;
                Str *_t2011 = U32_to_str(&(U32){line});
                (void)_t2011;
                Array_set(_va22, &(U64){_t2010}, _t2011);
                ;
                U64 _t2012 = 3;
                (void)_t2012;
                Str *_t2013 = Str_lit(":", 1ULL);
                (void)_t2013;
                Array_set(_va22, &(U64){_t2012}, _t2013);
                ;
                U64 _t2014 = 4;
                (void)_t2014;
                Str *_t2015 = U32_to_str(&(U32){col});
                (void)_t2015;
                Array_set(_va22, &(U64){_t2014}, _t2015);
                ;
                U64 _t2016 = 5;
                (void)_t2016;
                Str *_t2017 = Str_lit(": error: unterminated character literal", 39ULL);
                (void)_t2017;
                Array_set(_va22, &(U64){_t2016}, _t2017);
                ;
                println(_va22);
                U64 _t2018 = U64_sub(DEREF(pos), start);
                (void)_t2018;
                Str *_t2019 = Str_substr(src, &(U64){start}, &(U64){_t2018});
                (void)_t2019;
                ;
                U32 _t2020 = U32_clone(&(U32){col});
                (void)_t2020;
                Token *_t2021 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2021->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2019); _t2021->text = *_ca; free(_ca); }
                _t2021->line = U32_clone(&(U32){line});
                _t2021->col = _t2020;
                (void)_t2021;
                Str_delete(_t2019, &(Bool){1});
                ;
                Vec_push(tokens, _t2021);
            }
            ;
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U64 _t2166 = 1;
        (void)_t2166;
        U64 _t2167 = U64_add(DEREF(pos), _t2166);
        (void)_t2167;
        ;
        Bool _t2168; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2167}, &(U64){src_len}); _t2168 = *_hp; free(_hp); }
        (void)_t2168;
        ;
        if (_t2168) {
            U64 _t2083 = 1;
            (void)_t2083;
            U64 *_t2084 = malloc(sizeof(U64)); *_t2084 = U64_add(DEREF(pos), _t2083);
            (void)_t2084;
            ;
            U8 *c2 = Str_byte_at(src, _t2084);
            (void)c2;
            TokenType *two = TokenType_clone(TokenType_Eof());
            (void)two;
            U8 _t2085 = 58;
            (void)_t2085;
            U8 _t2086 = 61;
            (void)_t2086;
            Bool _t2087 = U8_eq(DEREF(c), _t2085);
            (void)_t2087;
            ;
            Bool _t2088 = U8_eq(DEREF(c2), _t2086);
            (void)_t2088;
            ;
            Bool _t2089 = Bool_and(_t2087, _t2088);
            (void)_t2089;
            ;
            ;
            if (_t2089) {
                two = TokenType_clone(TokenType_ColonEq());
            } else {
                U8 _t2071 = 61;
                (void)_t2071;
                U8 _t2072 = 61;
                (void)_t2072;
                Bool _t2073 = U8_eq(DEREF(c), _t2071);
                (void)_t2073;
                ;
                Bool _t2074 = U8_eq(DEREF(c2), _t2072);
                (void)_t2074;
                ;
                Bool _t2075 = Bool_and(_t2073, _t2074);
                (void)_t2075;
                ;
                ;
                if (_t2075) {
                    two = TokenType_clone(TokenType_EqEq());
                } else {
                    U8 _t2066 = 33;
                    (void)_t2066;
                    U8 _t2067 = 61;
                    (void)_t2067;
                    Bool _t2068 = U8_eq(DEREF(c), _t2066);
                    (void)_t2068;
                    ;
                    Bool _t2069 = U8_eq(DEREF(c2), _t2067);
                    (void)_t2069;
                    ;
                    Bool _t2070 = Bool_and(_t2068, _t2069);
                    (void)_t2070;
                    ;
                    ;
                    if (_t2070) {
                        two = TokenType_clone(TokenType_Neq());
                    } else {
                        U8 _t2061 = 60;
                        (void)_t2061;
                        U8 _t2062 = 61;
                        (void)_t2062;
                        Bool _t2063 = U8_eq(DEREF(c), _t2061);
                        (void)_t2063;
                        ;
                        Bool _t2064 = U8_eq(DEREF(c2), _t2062);
                        (void)_t2064;
                        ;
                        Bool _t2065 = Bool_and(_t2063, _t2064);
                        (void)_t2065;
                        ;
                        ;
                        if (_t2065) {
                            two = TokenType_clone(TokenType_LtEq());
                        } else {
                            U8 _t2056 = 62;
                            (void)_t2056;
                            U8 _t2057 = 61;
                            (void)_t2057;
                            Bool _t2058 = U8_eq(DEREF(c), _t2056);
                            (void)_t2058;
                            ;
                            Bool _t2059 = U8_eq(DEREF(c2), _t2057);
                            (void)_t2059;
                            ;
                            Bool _t2060 = Bool_and(_t2058, _t2059);
                            (void)_t2060;
                            ;
                            ;
                            if (_t2060) {
                                two = TokenType_clone(TokenType_GtEq());
                            } else {
                                U8 _t2051 = 46;
                                (void)_t2051;
                                U8 _t2052 = 46;
                                (void)_t2052;
                                Bool _t2053 = U8_eq(DEREF(c), _t2051);
                                (void)_t2053;
                                ;
                                Bool _t2054 = U8_eq(DEREF(c2), _t2052);
                                (void)_t2054;
                                ;
                                Bool _t2055 = Bool_and(_t2053, _t2054);
                                (void)_t2055;
                                ;
                                ;
                                if (_t2055) {
                                    U64 _t2048 = 2;
                                    (void)_t2048;
                                    U64 _t2049 = U64_add(DEREF(pos), _t2048);
                                    (void)_t2049;
                                    ;
                                    Bool _t2050; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2049}, &(U64){src_len}); _t2050 = *_hp; free(_hp); }
                                    (void)_t2050;
                                    ;
                                    if (_t2050) {
                                        U64 _t2044 = 2;
                                        (void)_t2044;
                                        U64 *_t2045 = malloc(sizeof(U64)); *_t2045 = U64_add(DEREF(pos), _t2044);
                                        (void)_t2045;
                                        ;
                                        U8 *c3 = Str_byte_at(src, _t2045);
                                        (void)c3;
                                        U8 _t2046 = 46;
                                        (void)_t2046;
                                        Bool _t2047 = U8_eq(DEREF(c3), _t2046);
                                        (void)_t2047;
                                        U64_delete(_t2045, &(Bool){1});
                                        ;
                                        if (_t2047) {
                                            U64 _t2038 = 3;
                                            (void)_t2038;
                                            Str *_t2039 = Str_substr(src, &(U64){start}, &(U64){_t2038});
                                            (void)_t2039;
                                            ;
                                            U32 _t2040 = U32_clone(&(U32){col});
                                            (void)_t2040;
                                            Token *_t2041 = malloc(sizeof(Token));
                                            { TokenType *_ca = TokenType_clone(TokenType_DotDotDot()); _t2041->type = *_ca; free(_ca); }
                                            { Str *_ca = Str_clone(_t2039); _t2041->text = *_ca; free(_ca); }
                                            _t2041->line = U32_clone(&(U32){line});
                                            _t2041->col = _t2040;
                                            (void)_t2041;
                                            Str_delete(_t2039, &(Bool){1});
                                            ;
                                            Vec_push(tokens, _t2041);
                                            U64 _t2042 = 3;
                                            (void)_t2042;
                                            U64 _t2043 = U64_add(DEREF(pos), _t2042);
                                            (void)_t2043;
                                            ;
                                            *pos = _t2043;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            U64_delete(_t2084, &(Bool){1});
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
            U64_delete(_t2084, &(Bool){1});
            ;
            Bool _t2090; { Bool *_hp = (Bool *)TokenType_eq(two, TokenType_Eof()); _t2090 = *_hp; free(_hp); }
            (void)_t2090;
            Bool _t2091 = Bool_not(_t2090);
            (void)_t2091;
            ;
            if (_t2091) {
                U64 _t2076 = 2;
                (void)_t2076;
                Str *_t2077 = Str_substr(src, &(U64){start}, &(U64){_t2076});
                (void)_t2077;
                ;
                U32 _t2078 = U32_clone(&(U32){line});
                (void)_t2078;
                U32 _t2079 = U32_clone(&(U32){col});
                (void)_t2079;
                Token *_t2080 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(two); _t2080->type = *_ca; free(_ca); }
                { Str *_ca = Str_clone(_t2077); _t2080->text = *_ca; free(_ca); }
                _t2080->line = _t2078;
                _t2080->col = _t2079;
                (void)_t2080;
                Str_delete(_t2077, &(Bool){1});
                ;
                ;
                Vec_push(tokens, _t2080);
                U64 _t2081 = 2;
                (void)_t2081;
                U64 _t2082 = U64_add(DEREF(pos), _t2081);
                (void)_t2082;
                ;
                *pos = _t2082;
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
            U8 _sw2092 = U8_clone(c);
            (void)_sw2092;
            U8 _t2127 = 40;
            (void)_t2127;
            Bool _t2128 = U8_eq(_sw2092, _t2127);
            (void)_t2128;
            ;
            if (_t2128) {
                single = TokenType_clone(TokenType_LParen());
            } else {
                U8 _t2125 = 41;
                (void)_t2125;
                Bool _t2126 = U8_eq(_sw2092, _t2125);
                (void)_t2126;
                ;
                if (_t2126) {
                    single = TokenType_clone(TokenType_RParen());
                } else {
                    U8 _t2123 = 123;
                    (void)_t2123;
                    Bool _t2124 = U8_eq(_sw2092, _t2123);
                    (void)_t2124;
                    ;
                    if (_t2124) {
                        single = TokenType_clone(TokenType_LBrace());
                    } else {
                        U8 _t2121 = 125;
                        (void)_t2121;
                        Bool _t2122 = U8_eq(_sw2092, _t2121);
                        (void)_t2122;
                        ;
                        if (_t2122) {
                            single = TokenType_clone(TokenType_RBrace());
                        } else {
                            U8 _t2119 = 91;
                            (void)_t2119;
                            Bool _t2120 = U8_eq(_sw2092, _t2119);
                            (void)_t2120;
                            ;
                            if (_t2120) {
                                single = TokenType_clone(TokenType_LBracket());
                            } else {
                                U8 _t2117 = 93;
                                (void)_t2117;
                                Bool _t2118 = U8_eq(_sw2092, _t2117);
                                (void)_t2118;
                                ;
                                if (_t2118) {
                                    single = TokenType_clone(TokenType_RBracket());
                                } else {
                                    U8 _t2115 = 44;
                                    (void)_t2115;
                                    Bool _t2116 = U8_eq(_sw2092, _t2115);
                                    (void)_t2116;
                                    ;
                                    if (_t2116) {
                                        single = TokenType_clone(TokenType_Comma());
                                    } else {
                                        U8 _t2113 = 58;
                                        (void)_t2113;
                                        Bool _t2114 = U8_eq(_sw2092, _t2113);
                                        (void)_t2114;
                                        ;
                                        if (_t2114) {
                                            single = TokenType_clone(TokenType_Colon());
                                        } else {
                                            U8 _t2111 = 46;
                                            (void)_t2111;
                                            Bool _t2112 = U8_eq(_sw2092, _t2111);
                                            (void)_t2112;
                                            ;
                                            if (_t2112) {
                                                single = TokenType_clone(TokenType_Dot());
                                            } else {
                                                U8 _t2109 = 63;
                                                (void)_t2109;
                                                Bool _t2110 = U8_eq(_sw2092, _t2109);
                                                (void)_t2110;
                                                ;
                                                if (_t2110) {
                                                    single = TokenType_clone(TokenType_Question());
                                                } else {
                                                    U8 _t2107 = 33;
                                                    (void)_t2107;
                                                    Bool _t2108 = U8_eq(_sw2092, _t2107);
                                                    (void)_t2108;
                                                    ;
                                                    if (_t2108) {
                                                        single = TokenType_clone(TokenType_Bang());
                                                    } else {
                                                        U8 _t2105 = 43;
                                                        (void)_t2105;
                                                        Bool _t2106 = U8_eq(_sw2092, _t2105);
                                                        (void)_t2106;
                                                        ;
                                                        if (_t2106) {
                                                            single = TokenType_clone(TokenType_Plus());
                                                        } else {
                                                            U8 _t2103 = 45;
                                                            (void)_t2103;
                                                            Bool _t2104 = U8_eq(_sw2092, _t2103);
                                                            (void)_t2104;
                                                            ;
                                                            if (_t2104) {
                                                                single = TokenType_clone(TokenType_Minus());
                                                            } else {
                                                                U8 _t2101 = 42;
                                                                (void)_t2101;
                                                                Bool _t2102 = U8_eq(_sw2092, _t2101);
                                                                (void)_t2102;
                                                                ;
                                                                if (_t2102) {
                                                                    single = TokenType_clone(TokenType_Star());
                                                                } else {
                                                                    U8 _t2099 = 47;
                                                                    (void)_t2099;
                                                                    Bool _t2100 = U8_eq(_sw2092, _t2099);
                                                                    (void)_t2100;
                                                                    ;
                                                                    if (_t2100) {
                                                                        single = TokenType_clone(TokenType_Slash());
                                                                    } else {
                                                                        U8 _t2097 = 61;
                                                                        (void)_t2097;
                                                                        Bool _t2098 = U8_eq(_sw2092, _t2097);
                                                                        (void)_t2098;
                                                                        ;
                                                                        if (_t2098) {
                                                                            single = TokenType_clone(TokenType_Eq());
                                                                        } else {
                                                                            U8 _t2095 = 60;
                                                                            (void)_t2095;
                                                                            Bool _t2096 = U8_eq(_sw2092, _t2095);
                                                                            (void)_t2096;
                                                                            ;
                                                                            if (_t2096) {
                                                                                single = TokenType_clone(TokenType_Lt());
                                                                            } else {
                                                                                U8 _t2093 = 62;
                                                                                (void)_t2093;
                                                                                Bool _t2094 = U8_eq(_sw2092, _t2093);
                                                                                (void)_t2094;
                                                                                ;
                                                                                if (_t2094) {
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
        Bool _t2169; { Bool *_hp = (Bool *)TokenType_eq(single, TokenType_Eof()); _t2169 = *_hp; free(_hp); }
        (void)_t2169;
        Bool _t2170 = Bool_not(_t2169);
        (void)_t2170;
        ;
        if (_t2170) {
            U64 _t2129 = 1;
            (void)_t2129;
            Str *_t2130 = Str_substr(src, &(U64){start}, &(U64){_t2129});
            (void)_t2130;
            ;
            U32 _t2131 = U32_clone(&(U32){line});
            (void)_t2131;
            U32 _t2132 = U32_clone(&(U32){col});
            (void)_t2132;
            Token *_t2133 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(single); _t2133->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(_t2130); _t2133->text = *_ca; free(_ca); }
            _t2133->line = _t2131;
            _t2133->col = _t2132;
            (void)_t2133;
            Str_delete(_t2130, &(Bool){1});
            ;
            ;
            Vec_push(tokens, _t2133);
            U64 _t2134 = U64_inc(DEREF(pos));
            (void)_t2134;
            *pos = _t2134;
            ;
            ;
            ;
            TokenType_delete(single, &(Bool){1});
            ;
            continue;
        }
        ;
        TokenType_delete(single, &(Bool){1});
        Str *_t2171 = Str_lit("Str", 3ULL);
        (void)_t2171;
        U64 _t2172; { U64 *_hp = (U64 *)Str_size(); _t2172 = *_hp; free(_hp); }
        (void)_t2172;
        U64 _t2173 = 6;
        (void)_t2173;
        Array *_va23 = Array_new(_t2171, &(U64){_t2172}, &(U64){_t2173});
        (void)_va23;
        Str_delete(_t2171, &(Bool){1});
        ;
        ;
        U64 _t2174 = 0;
        (void)_t2174;
        Str *_t2175 = Str_clone(path);
        (void)_t2175;
        Array_set(_va23, &(U64){_t2174}, _t2175);
        ;
        U64 _t2176 = 1;
        (void)_t2176;
        Str *_t2177 = Str_lit(":", 1ULL);
        (void)_t2177;
        Array_set(_va23, &(U64){_t2176}, _t2177);
        ;
        U64 _t2178 = 2;
        (void)_t2178;
        Str *_t2179 = U32_to_str(&(U32){line});
        (void)_t2179;
        Array_set(_va23, &(U64){_t2178}, _t2179);
        ;
        U64 _t2180 = 3;
        (void)_t2180;
        Str *_t2181 = Str_lit(":", 1ULL);
        (void)_t2181;
        Array_set(_va23, &(U64){_t2180}, _t2181);
        ;
        U64 _t2182 = 4;
        (void)_t2182;
        Str *_t2183 = U32_to_str(&(U32){col});
        (void)_t2183;
        Array_set(_va23, &(U64){_t2182}, _t2183);
        ;
        U64 _t2184 = 5;
        (void)_t2184;
        Str *_t2185 = Str_lit(": error: unexpected character", 29ULL);
        (void)_t2185;
        Array_set(_va23, &(U64){_t2184}, _t2185);
        ;
        println(_va23);
        U64 _t2186 = 1;
        (void)_t2186;
        Str *_t2187 = Str_substr(src, &(U64){start}, &(U64){_t2186});
        (void)_t2187;
        ;
        ;
        U32 _t2188 = U32_clone(&(U32){col});
        (void)_t2188;
        ;
        Token *_t2189 = malloc(sizeof(Token));
        { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2189->type = *_ca; free(_ca); }
        { Str *_ca = Str_clone(_t2187); _t2189->text = *_ca; free(_ca); }
        _t2189->line = U32_clone(&(U32){line});
        _t2189->col = _t2188;
        (void)_t2189;
        Str_delete(_t2187, &(Bool){1});
        ;
        Vec_push(tokens, _t2189);
        U64 _t2190 = U64_inc(DEREF(pos));
        (void)_t2190;
        *pos = _t2190;
        ;
    }
    ;
    U64 _t2193 = U64_sub(DEREF(pos), line_start);
    (void)_t2193;
    ;
    U64_delete(pos, &(Bool){1});
    U64 _t2194 = 1;
    (void)_t2194;
    U64 _t2195 = U64_add(_t2193, _t2194);
    (void)_t2195;
    ;
    ;
    I64 col = U64_to_i64(_t2195);
    (void)col;
    ;
    I64 _t2196 = I64_clone(&(I64){col});
    (void)_t2196;
    ;
    Token *_t2197 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(TokenType_Eof()); _t2197->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t2197->text = *_ca; free(_ca); }
    _t2197->line = U32_clone(&(U32){line});
    _t2197->col = _t2196;
    (void)_t2197;
    ;
    ;
    Vec_push(tokens, _t2197);
    return tokens;
}

