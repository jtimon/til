TokenType *TokenType_Eof() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Eof };
    return r;
}
TokenType *TokenType_LParen() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_LParen };
    return r;
}
TokenType *TokenType_RParen() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_RParen };
    return r;
}
TokenType *TokenType_LBrace() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_LBrace };
    return r;
}
TokenType *TokenType_RBrace() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_RBrace };
    return r;
}
TokenType *TokenType_LBracket() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_LBracket };
    return r;
}
TokenType *TokenType_RBracket() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_RBracket };
    return r;
}
TokenType *TokenType_Comma() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Comma };
    return r;
}
TokenType *TokenType_Colon() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Colon };
    return r;
}
TokenType *TokenType_Question() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Question };
    return r;
}
TokenType *TokenType_Bang() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Bang };
    return r;
}
TokenType *TokenType_Minus() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Minus };
    return r;
}
TokenType *TokenType_Plus() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Plus };
    return r;
}
TokenType *TokenType_Star() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Star };
    return r;
}
TokenType *TokenType_Slash() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Slash };
    return r;
}
TokenType *TokenType_Dot() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Dot };
    return r;
}
TokenType *TokenType_DotDot() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_DotDot };
    return r;
}
TokenType *TokenType_DotDotDot() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_DotDotDot };
    return r;
}
TokenType *TokenType_Eq() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Eq };
    return r;
}
TokenType *TokenType_EqEq() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_EqEq };
    return r;
}
TokenType *TokenType_Neq() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Neq };
    return r;
}
TokenType *TokenType_Lt() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Lt };
    return r;
}
TokenType *TokenType_LtEq() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_LtEq };
    return r;
}
TokenType *TokenType_Gt() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Gt };
    return r;
}
TokenType *TokenType_GtEq() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_GtEq };
    return r;
}
TokenType *TokenType_ColonEq() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_ColonEq };
    return r;
}
TokenType *TokenType_Ident() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Ident };
    return r;
}
TokenType *TokenType_StringTok() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_StringTok };
    return r;
}
TokenType *TokenType_Number() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Number };
    return r;
}
TokenType *TokenType_Char() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Char };
    return r;
}
TokenType *TokenType_KwMode() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwMode };
    return r;
}
TokenType *TokenType_KwMut() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwMut };
    return r;
}
TokenType *TokenType_KwOwn() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwOwn };
    return r;
}
TokenType *TokenType_KwRef() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwRef };
    return r;
}
TokenType *TokenType_KwShallow() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwShallow };
    return r;
}
TokenType *TokenType_KwStruct() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwStruct };
    return r;
}
TokenType *TokenType_KwExtStruct() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwExtStruct };
    return r;
}
TokenType *TokenType_KwEnum() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwEnum };
    return r;
}
TokenType *TokenType_KwNamespace() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwNamespace };
    return r;
}
TokenType *TokenType_KwFunc() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwFunc };
    return r;
}
TokenType *TokenType_KwProc() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwProc };
    return r;
}
TokenType *TokenType_KwTest() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwTest };
    return r;
}
TokenType *TokenType_KwMacro() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwMacro };
    return r;
}
TokenType *TokenType_KwExtFunc() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwExtFunc };
    return r;
}
TokenType *TokenType_KwExtProc() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwExtProc };
    return r;
}
TokenType *TokenType_KwReturns() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwReturns };
    return r;
}
TokenType *TokenType_KwThrows() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwThrows };
    return r;
}
TokenType *TokenType_KwIf() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwIf };
    return r;
}
TokenType *TokenType_KwElse() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwElse };
    return r;
}
TokenType *TokenType_KwWhile() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwWhile };
    return r;
}
TokenType *TokenType_KwFor() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwFor };
    return r;
}
TokenType *TokenType_KwIn() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwIn };
    return r;
}
TokenType *TokenType_KwSwitch() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwSwitch };
    return r;
}
TokenType *TokenType_KwMatch() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwMatch };
    return r;
}
TokenType *TokenType_KwCase() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwCase };
    return r;
}
TokenType *TokenType_KwDefault() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwDefault };
    return r;
}
TokenType *TokenType_KwReturn() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwReturn };
    return r;
}
TokenType *TokenType_KwThrow() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwThrow };
    return r;
}
TokenType *TokenType_KwCatch() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwCatch };
    return r;
}
TokenType *TokenType_KwBreak() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwBreak };
    return r;
}
TokenType *TokenType_KwContinue() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwContinue };
    return r;
}
TokenType *TokenType_KwDefer() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwDefer };
    return r;
}
TokenType *TokenType_KwTrue() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwTrue };
    return r;
}
TokenType *TokenType_KwFalse() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwFalse };
    return r;
}
TokenType *TokenType_KwNull() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwNull };
    return r;
}
TokenType *TokenType_Error() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Error };
    return r;
}
Bool *TokenType_is_Eof(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Eof);
    return r;
}
Bool *TokenType_is_LParen(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_LParen);
    return r;
}
Bool *TokenType_is_RParen(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_RParen);
    return r;
}
Bool *TokenType_is_LBrace(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_LBrace);
    return r;
}
Bool *TokenType_is_RBrace(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_RBrace);
    return r;
}
Bool *TokenType_is_LBracket(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_LBracket);
    return r;
}
Bool *TokenType_is_RBracket(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_RBracket);
    return r;
}
Bool *TokenType_is_Comma(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Comma);
    return r;
}
Bool *TokenType_is_Colon(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Colon);
    return r;
}
Bool *TokenType_is_Question(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Question);
    return r;
}
Bool *TokenType_is_Bang(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Bang);
    return r;
}
Bool *TokenType_is_Minus(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Minus);
    return r;
}
Bool *TokenType_is_Plus(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Plus);
    return r;
}
Bool *TokenType_is_Star(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Star);
    return r;
}
Bool *TokenType_is_Slash(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Slash);
    return r;
}
Bool *TokenType_is_Dot(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Dot);
    return r;
}
Bool *TokenType_is_DotDot(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_DotDot);
    return r;
}
Bool *TokenType_is_DotDotDot(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_DotDotDot);
    return r;
}
Bool *TokenType_is_Eq(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Eq);
    return r;
}
Bool *TokenType_is_EqEq(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_EqEq);
    return r;
}
Bool *TokenType_is_Neq(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Neq);
    return r;
}
Bool *TokenType_is_Lt(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Lt);
    return r;
}
Bool *TokenType_is_LtEq(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_LtEq);
    return r;
}
Bool *TokenType_is_Gt(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Gt);
    return r;
}
Bool *TokenType_is_GtEq(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_GtEq);
    return r;
}
Bool *TokenType_is_ColonEq(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_ColonEq);
    return r;
}
Bool *TokenType_is_Ident(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Ident);
    return r;
}
Bool *TokenType_is_StringTok(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_StringTok);
    return r;
}
Bool *TokenType_is_Number(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Number);
    return r;
}
Bool *TokenType_is_Char(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Char);
    return r;
}
Bool *TokenType_is_KwMode(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwMode);
    return r;
}
Bool *TokenType_is_KwMut(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwMut);
    return r;
}
Bool *TokenType_is_KwOwn(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwOwn);
    return r;
}
Bool *TokenType_is_KwRef(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwRef);
    return r;
}
Bool *TokenType_is_KwShallow(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwShallow);
    return r;
}
Bool *TokenType_is_KwStruct(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwStruct);
    return r;
}
Bool *TokenType_is_KwExtStruct(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwExtStruct);
    return r;
}
Bool *TokenType_is_KwEnum(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwEnum);
    return r;
}
Bool *TokenType_is_KwNamespace(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwNamespace);
    return r;
}
Bool *TokenType_is_KwFunc(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwFunc);
    return r;
}
Bool *TokenType_is_KwProc(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwProc);
    return r;
}
Bool *TokenType_is_KwTest(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwTest);
    return r;
}
Bool *TokenType_is_KwMacro(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwMacro);
    return r;
}
Bool *TokenType_is_KwExtFunc(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwExtFunc);
    return r;
}
Bool *TokenType_is_KwExtProc(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwExtProc);
    return r;
}
Bool *TokenType_is_KwReturns(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwReturns);
    return r;
}
Bool *TokenType_is_KwThrows(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwThrows);
    return r;
}
Bool *TokenType_is_KwIf(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwIf);
    return r;
}
Bool *TokenType_is_KwElse(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwElse);
    return r;
}
Bool *TokenType_is_KwWhile(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwWhile);
    return r;
}
Bool *TokenType_is_KwFor(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwFor);
    return r;
}
Bool *TokenType_is_KwIn(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwIn);
    return r;
}
Bool *TokenType_is_KwSwitch(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwSwitch);
    return r;
}
Bool *TokenType_is_KwMatch(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwMatch);
    return r;
}
Bool *TokenType_is_KwCase(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwCase);
    return r;
}
Bool *TokenType_is_KwDefault(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwDefault);
    return r;
}
Bool *TokenType_is_KwReturn(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwReturn);
    return r;
}
Bool *TokenType_is_KwThrow(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwThrow);
    return r;
}
Bool *TokenType_is_KwCatch(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwCatch);
    return r;
}
Bool *TokenType_is_KwBreak(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwBreak);
    return r;
}
Bool *TokenType_is_KwContinue(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwContinue);
    return r;
}
Bool *TokenType_is_KwDefer(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwDefer);
    return r;
}
Bool *TokenType_is_KwTrue(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwTrue);
    return r;
}
Bool *TokenType_is_KwFalse(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwFalse);
    return r;
}
Bool *TokenType_is_KwNull(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwNull);
    return r;
}
Bool *TokenType_is_Error(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Error);
    return r;
}
Bool * TokenType_eq(TokenType * self, TokenType * other) {
    (void)self;
    (void)other;
    Bool _t1329; { Bool *_hp = (Bool *)TokenType_is_Eof(self); _t1329 = *_hp; free(_hp); }
    (void)_t1329;
    if (_t1329) {
        Bool _t1263; { Bool *_hp = (Bool *)TokenType_is_Eof(other); _t1263 = *_hp; free(_hp); }
        (void)_t1263;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1263; return _r; }
    }
    ;
    Bool _t1330; { Bool *_hp = (Bool *)TokenType_is_LParen(self); _t1330 = *_hp; free(_hp); }
    (void)_t1330;
    if (_t1330) {
        Bool _t1264; { Bool *_hp = (Bool *)TokenType_is_LParen(other); _t1264 = *_hp; free(_hp); }
        (void)_t1264;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1264; return _r; }
    }
    ;
    Bool _t1331; { Bool *_hp = (Bool *)TokenType_is_RParen(self); _t1331 = *_hp; free(_hp); }
    (void)_t1331;
    if (_t1331) {
        Bool _t1265; { Bool *_hp = (Bool *)TokenType_is_RParen(other); _t1265 = *_hp; free(_hp); }
        (void)_t1265;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1265; return _r; }
    }
    ;
    Bool _t1332; { Bool *_hp = (Bool *)TokenType_is_LBrace(self); _t1332 = *_hp; free(_hp); }
    (void)_t1332;
    if (_t1332) {
        Bool _t1266; { Bool *_hp = (Bool *)TokenType_is_LBrace(other); _t1266 = *_hp; free(_hp); }
        (void)_t1266;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1266; return _r; }
    }
    ;
    Bool _t1333; { Bool *_hp = (Bool *)TokenType_is_RBrace(self); _t1333 = *_hp; free(_hp); }
    (void)_t1333;
    if (_t1333) {
        Bool _t1267; { Bool *_hp = (Bool *)TokenType_is_RBrace(other); _t1267 = *_hp; free(_hp); }
        (void)_t1267;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1267; return _r; }
    }
    ;
    Bool _t1334; { Bool *_hp = (Bool *)TokenType_is_LBracket(self); _t1334 = *_hp; free(_hp); }
    (void)_t1334;
    if (_t1334) {
        Bool _t1268; { Bool *_hp = (Bool *)TokenType_is_LBracket(other); _t1268 = *_hp; free(_hp); }
        (void)_t1268;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1268; return _r; }
    }
    ;
    Bool _t1335; { Bool *_hp = (Bool *)TokenType_is_RBracket(self); _t1335 = *_hp; free(_hp); }
    (void)_t1335;
    if (_t1335) {
        Bool _t1269; { Bool *_hp = (Bool *)TokenType_is_RBracket(other); _t1269 = *_hp; free(_hp); }
        (void)_t1269;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1269; return _r; }
    }
    ;
    Bool _t1336; { Bool *_hp = (Bool *)TokenType_is_Comma(self); _t1336 = *_hp; free(_hp); }
    (void)_t1336;
    if (_t1336) {
        Bool _t1270; { Bool *_hp = (Bool *)TokenType_is_Comma(other); _t1270 = *_hp; free(_hp); }
        (void)_t1270;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1270; return _r; }
    }
    ;
    Bool _t1337; { Bool *_hp = (Bool *)TokenType_is_Colon(self); _t1337 = *_hp; free(_hp); }
    (void)_t1337;
    if (_t1337) {
        Bool _t1271; { Bool *_hp = (Bool *)TokenType_is_Colon(other); _t1271 = *_hp; free(_hp); }
        (void)_t1271;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1271; return _r; }
    }
    ;
    Bool _t1338; { Bool *_hp = (Bool *)TokenType_is_Question(self); _t1338 = *_hp; free(_hp); }
    (void)_t1338;
    if (_t1338) {
        Bool _t1272; { Bool *_hp = (Bool *)TokenType_is_Question(other); _t1272 = *_hp; free(_hp); }
        (void)_t1272;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1272; return _r; }
    }
    ;
    Bool _t1339; { Bool *_hp = (Bool *)TokenType_is_Bang(self); _t1339 = *_hp; free(_hp); }
    (void)_t1339;
    if (_t1339) {
        Bool _t1273; { Bool *_hp = (Bool *)TokenType_is_Bang(other); _t1273 = *_hp; free(_hp); }
        (void)_t1273;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1273; return _r; }
    }
    ;
    Bool _t1340; { Bool *_hp = (Bool *)TokenType_is_Minus(self); _t1340 = *_hp; free(_hp); }
    (void)_t1340;
    if (_t1340) {
        Bool _t1274; { Bool *_hp = (Bool *)TokenType_is_Minus(other); _t1274 = *_hp; free(_hp); }
        (void)_t1274;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1274; return _r; }
    }
    ;
    Bool _t1341; { Bool *_hp = (Bool *)TokenType_is_Plus(self); _t1341 = *_hp; free(_hp); }
    (void)_t1341;
    if (_t1341) {
        Bool _t1275; { Bool *_hp = (Bool *)TokenType_is_Plus(other); _t1275 = *_hp; free(_hp); }
        (void)_t1275;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1275; return _r; }
    }
    ;
    Bool _t1342; { Bool *_hp = (Bool *)TokenType_is_Star(self); _t1342 = *_hp; free(_hp); }
    (void)_t1342;
    if (_t1342) {
        Bool _t1276; { Bool *_hp = (Bool *)TokenType_is_Star(other); _t1276 = *_hp; free(_hp); }
        (void)_t1276;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1276; return _r; }
    }
    ;
    Bool _t1343; { Bool *_hp = (Bool *)TokenType_is_Slash(self); _t1343 = *_hp; free(_hp); }
    (void)_t1343;
    if (_t1343) {
        Bool _t1277; { Bool *_hp = (Bool *)TokenType_is_Slash(other); _t1277 = *_hp; free(_hp); }
        (void)_t1277;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1277; return _r; }
    }
    ;
    Bool _t1344; { Bool *_hp = (Bool *)TokenType_is_Dot(self); _t1344 = *_hp; free(_hp); }
    (void)_t1344;
    if (_t1344) {
        Bool _t1278; { Bool *_hp = (Bool *)TokenType_is_Dot(other); _t1278 = *_hp; free(_hp); }
        (void)_t1278;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1278; return _r; }
    }
    ;
    Bool _t1345; { Bool *_hp = (Bool *)TokenType_is_DotDot(self); _t1345 = *_hp; free(_hp); }
    (void)_t1345;
    if (_t1345) {
        Bool _t1279; { Bool *_hp = (Bool *)TokenType_is_DotDot(other); _t1279 = *_hp; free(_hp); }
        (void)_t1279;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1279; return _r; }
    }
    ;
    Bool _t1346; { Bool *_hp = (Bool *)TokenType_is_DotDotDot(self); _t1346 = *_hp; free(_hp); }
    (void)_t1346;
    if (_t1346) {
        Bool _t1280; { Bool *_hp = (Bool *)TokenType_is_DotDotDot(other); _t1280 = *_hp; free(_hp); }
        (void)_t1280;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1280; return _r; }
    }
    ;
    Bool _t1347; { Bool *_hp = (Bool *)TokenType_is_Eq(self); _t1347 = *_hp; free(_hp); }
    (void)_t1347;
    if (_t1347) {
        Bool _t1281; { Bool *_hp = (Bool *)TokenType_is_Eq(other); _t1281 = *_hp; free(_hp); }
        (void)_t1281;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1281; return _r; }
    }
    ;
    Bool _t1348; { Bool *_hp = (Bool *)TokenType_is_EqEq(self); _t1348 = *_hp; free(_hp); }
    (void)_t1348;
    if (_t1348) {
        Bool _t1282; { Bool *_hp = (Bool *)TokenType_is_EqEq(other); _t1282 = *_hp; free(_hp); }
        (void)_t1282;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1282; return _r; }
    }
    ;
    Bool _t1349; { Bool *_hp = (Bool *)TokenType_is_Neq(self); _t1349 = *_hp; free(_hp); }
    (void)_t1349;
    if (_t1349) {
        Bool _t1283; { Bool *_hp = (Bool *)TokenType_is_Neq(other); _t1283 = *_hp; free(_hp); }
        (void)_t1283;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1283; return _r; }
    }
    ;
    Bool _t1350; { Bool *_hp = (Bool *)TokenType_is_Lt(self); _t1350 = *_hp; free(_hp); }
    (void)_t1350;
    if (_t1350) {
        Bool _t1284; { Bool *_hp = (Bool *)TokenType_is_Lt(other); _t1284 = *_hp; free(_hp); }
        (void)_t1284;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1284; return _r; }
    }
    ;
    Bool _t1351; { Bool *_hp = (Bool *)TokenType_is_LtEq(self); _t1351 = *_hp; free(_hp); }
    (void)_t1351;
    if (_t1351) {
        Bool _t1285; { Bool *_hp = (Bool *)TokenType_is_LtEq(other); _t1285 = *_hp; free(_hp); }
        (void)_t1285;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1285; return _r; }
    }
    ;
    Bool _t1352; { Bool *_hp = (Bool *)TokenType_is_Gt(self); _t1352 = *_hp; free(_hp); }
    (void)_t1352;
    if (_t1352) {
        Bool _t1286; { Bool *_hp = (Bool *)TokenType_is_Gt(other); _t1286 = *_hp; free(_hp); }
        (void)_t1286;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1286; return _r; }
    }
    ;
    Bool _t1353; { Bool *_hp = (Bool *)TokenType_is_GtEq(self); _t1353 = *_hp; free(_hp); }
    (void)_t1353;
    if (_t1353) {
        Bool _t1287; { Bool *_hp = (Bool *)TokenType_is_GtEq(other); _t1287 = *_hp; free(_hp); }
        (void)_t1287;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1287; return _r; }
    }
    ;
    Bool _t1354; { Bool *_hp = (Bool *)TokenType_is_ColonEq(self); _t1354 = *_hp; free(_hp); }
    (void)_t1354;
    if (_t1354) {
        Bool _t1288; { Bool *_hp = (Bool *)TokenType_is_ColonEq(other); _t1288 = *_hp; free(_hp); }
        (void)_t1288;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1288; return _r; }
    }
    ;
    Bool _t1355; { Bool *_hp = (Bool *)TokenType_is_Ident(self); _t1355 = *_hp; free(_hp); }
    (void)_t1355;
    if (_t1355) {
        Bool _t1289; { Bool *_hp = (Bool *)TokenType_is_Ident(other); _t1289 = *_hp; free(_hp); }
        (void)_t1289;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1289; return _r; }
    }
    ;
    Bool _t1356; { Bool *_hp = (Bool *)TokenType_is_StringTok(self); _t1356 = *_hp; free(_hp); }
    (void)_t1356;
    if (_t1356) {
        Bool _t1290; { Bool *_hp = (Bool *)TokenType_is_StringTok(other); _t1290 = *_hp; free(_hp); }
        (void)_t1290;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1290; return _r; }
    }
    ;
    Bool _t1357; { Bool *_hp = (Bool *)TokenType_is_Number(self); _t1357 = *_hp; free(_hp); }
    (void)_t1357;
    if (_t1357) {
        Bool _t1291; { Bool *_hp = (Bool *)TokenType_is_Number(other); _t1291 = *_hp; free(_hp); }
        (void)_t1291;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1291; return _r; }
    }
    ;
    Bool _t1358; { Bool *_hp = (Bool *)TokenType_is_Char(self); _t1358 = *_hp; free(_hp); }
    (void)_t1358;
    if (_t1358) {
        Bool _t1292; { Bool *_hp = (Bool *)TokenType_is_Char(other); _t1292 = *_hp; free(_hp); }
        (void)_t1292;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1292; return _r; }
    }
    ;
    Bool _t1359; { Bool *_hp = (Bool *)TokenType_is_KwMode(self); _t1359 = *_hp; free(_hp); }
    (void)_t1359;
    if (_t1359) {
        Bool _t1293; { Bool *_hp = (Bool *)TokenType_is_KwMode(other); _t1293 = *_hp; free(_hp); }
        (void)_t1293;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1293; return _r; }
    }
    ;
    Bool _t1360; { Bool *_hp = (Bool *)TokenType_is_KwMut(self); _t1360 = *_hp; free(_hp); }
    (void)_t1360;
    if (_t1360) {
        Bool _t1294; { Bool *_hp = (Bool *)TokenType_is_KwMut(other); _t1294 = *_hp; free(_hp); }
        (void)_t1294;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1294; return _r; }
    }
    ;
    Bool _t1361; { Bool *_hp = (Bool *)TokenType_is_KwOwn(self); _t1361 = *_hp; free(_hp); }
    (void)_t1361;
    if (_t1361) {
        Bool _t1295; { Bool *_hp = (Bool *)TokenType_is_KwOwn(other); _t1295 = *_hp; free(_hp); }
        (void)_t1295;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1295; return _r; }
    }
    ;
    Bool _t1362; { Bool *_hp = (Bool *)TokenType_is_KwRef(self); _t1362 = *_hp; free(_hp); }
    (void)_t1362;
    if (_t1362) {
        Bool _t1296; { Bool *_hp = (Bool *)TokenType_is_KwRef(other); _t1296 = *_hp; free(_hp); }
        (void)_t1296;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1296; return _r; }
    }
    ;
    Bool _t1363; { Bool *_hp = (Bool *)TokenType_is_KwShallow(self); _t1363 = *_hp; free(_hp); }
    (void)_t1363;
    if (_t1363) {
        Bool _t1297; { Bool *_hp = (Bool *)TokenType_is_KwShallow(other); _t1297 = *_hp; free(_hp); }
        (void)_t1297;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1297; return _r; }
    }
    ;
    Bool _t1364; { Bool *_hp = (Bool *)TokenType_is_KwStruct(self); _t1364 = *_hp; free(_hp); }
    (void)_t1364;
    if (_t1364) {
        Bool _t1298; { Bool *_hp = (Bool *)TokenType_is_KwStruct(other); _t1298 = *_hp; free(_hp); }
        (void)_t1298;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1298; return _r; }
    }
    ;
    Bool _t1365; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(self); _t1365 = *_hp; free(_hp); }
    (void)_t1365;
    if (_t1365) {
        Bool _t1299; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(other); _t1299 = *_hp; free(_hp); }
        (void)_t1299;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1299; return _r; }
    }
    ;
    Bool _t1366; { Bool *_hp = (Bool *)TokenType_is_KwEnum(self); _t1366 = *_hp; free(_hp); }
    (void)_t1366;
    if (_t1366) {
        Bool _t1300; { Bool *_hp = (Bool *)TokenType_is_KwEnum(other); _t1300 = *_hp; free(_hp); }
        (void)_t1300;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1300; return _r; }
    }
    ;
    Bool _t1367; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(self); _t1367 = *_hp; free(_hp); }
    (void)_t1367;
    if (_t1367) {
        Bool _t1301; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(other); _t1301 = *_hp; free(_hp); }
        (void)_t1301;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1301; return _r; }
    }
    ;
    Bool _t1368; { Bool *_hp = (Bool *)TokenType_is_KwFunc(self); _t1368 = *_hp; free(_hp); }
    (void)_t1368;
    if (_t1368) {
        Bool _t1302; { Bool *_hp = (Bool *)TokenType_is_KwFunc(other); _t1302 = *_hp; free(_hp); }
        (void)_t1302;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1302; return _r; }
    }
    ;
    Bool _t1369; { Bool *_hp = (Bool *)TokenType_is_KwProc(self); _t1369 = *_hp; free(_hp); }
    (void)_t1369;
    if (_t1369) {
        Bool _t1303; { Bool *_hp = (Bool *)TokenType_is_KwProc(other); _t1303 = *_hp; free(_hp); }
        (void)_t1303;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1303; return _r; }
    }
    ;
    Bool _t1370; { Bool *_hp = (Bool *)TokenType_is_KwTest(self); _t1370 = *_hp; free(_hp); }
    (void)_t1370;
    if (_t1370) {
        Bool _t1304; { Bool *_hp = (Bool *)TokenType_is_KwTest(other); _t1304 = *_hp; free(_hp); }
        (void)_t1304;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1304; return _r; }
    }
    ;
    Bool _t1371; { Bool *_hp = (Bool *)TokenType_is_KwMacro(self); _t1371 = *_hp; free(_hp); }
    (void)_t1371;
    if (_t1371) {
        Bool _t1305; { Bool *_hp = (Bool *)TokenType_is_KwMacro(other); _t1305 = *_hp; free(_hp); }
        (void)_t1305;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1305; return _r; }
    }
    ;
    Bool _t1372; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(self); _t1372 = *_hp; free(_hp); }
    (void)_t1372;
    if (_t1372) {
        Bool _t1306; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(other); _t1306 = *_hp; free(_hp); }
        (void)_t1306;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1306; return _r; }
    }
    ;
    Bool _t1373; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(self); _t1373 = *_hp; free(_hp); }
    (void)_t1373;
    if (_t1373) {
        Bool _t1307; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(other); _t1307 = *_hp; free(_hp); }
        (void)_t1307;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1307; return _r; }
    }
    ;
    Bool _t1374; { Bool *_hp = (Bool *)TokenType_is_KwReturns(self); _t1374 = *_hp; free(_hp); }
    (void)_t1374;
    if (_t1374) {
        Bool _t1308; { Bool *_hp = (Bool *)TokenType_is_KwReturns(other); _t1308 = *_hp; free(_hp); }
        (void)_t1308;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1308; return _r; }
    }
    ;
    Bool _t1375; { Bool *_hp = (Bool *)TokenType_is_KwThrows(self); _t1375 = *_hp; free(_hp); }
    (void)_t1375;
    if (_t1375) {
        Bool _t1309; { Bool *_hp = (Bool *)TokenType_is_KwThrows(other); _t1309 = *_hp; free(_hp); }
        (void)_t1309;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1309; return _r; }
    }
    ;
    Bool _t1376; { Bool *_hp = (Bool *)TokenType_is_KwIf(self); _t1376 = *_hp; free(_hp); }
    (void)_t1376;
    if (_t1376) {
        Bool _t1310; { Bool *_hp = (Bool *)TokenType_is_KwIf(other); _t1310 = *_hp; free(_hp); }
        (void)_t1310;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1310; return _r; }
    }
    ;
    Bool _t1377; { Bool *_hp = (Bool *)TokenType_is_KwElse(self); _t1377 = *_hp; free(_hp); }
    (void)_t1377;
    if (_t1377) {
        Bool _t1311; { Bool *_hp = (Bool *)TokenType_is_KwElse(other); _t1311 = *_hp; free(_hp); }
        (void)_t1311;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1311; return _r; }
    }
    ;
    Bool _t1378; { Bool *_hp = (Bool *)TokenType_is_KwWhile(self); _t1378 = *_hp; free(_hp); }
    (void)_t1378;
    if (_t1378) {
        Bool _t1312; { Bool *_hp = (Bool *)TokenType_is_KwWhile(other); _t1312 = *_hp; free(_hp); }
        (void)_t1312;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1312; return _r; }
    }
    ;
    Bool _t1379; { Bool *_hp = (Bool *)TokenType_is_KwFor(self); _t1379 = *_hp; free(_hp); }
    (void)_t1379;
    if (_t1379) {
        Bool _t1313; { Bool *_hp = (Bool *)TokenType_is_KwFor(other); _t1313 = *_hp; free(_hp); }
        (void)_t1313;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1313; return _r; }
    }
    ;
    Bool _t1380; { Bool *_hp = (Bool *)TokenType_is_KwIn(self); _t1380 = *_hp; free(_hp); }
    (void)_t1380;
    if (_t1380) {
        Bool _t1314; { Bool *_hp = (Bool *)TokenType_is_KwIn(other); _t1314 = *_hp; free(_hp); }
        (void)_t1314;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1314; return _r; }
    }
    ;
    Bool _t1381; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(self); _t1381 = *_hp; free(_hp); }
    (void)_t1381;
    if (_t1381) {
        Bool _t1315; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(other); _t1315 = *_hp; free(_hp); }
        (void)_t1315;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1315; return _r; }
    }
    ;
    Bool _t1382; { Bool *_hp = (Bool *)TokenType_is_KwMatch(self); _t1382 = *_hp; free(_hp); }
    (void)_t1382;
    if (_t1382) {
        Bool _t1316; { Bool *_hp = (Bool *)TokenType_is_KwMatch(other); _t1316 = *_hp; free(_hp); }
        (void)_t1316;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1316; return _r; }
    }
    ;
    Bool _t1383; { Bool *_hp = (Bool *)TokenType_is_KwCase(self); _t1383 = *_hp; free(_hp); }
    (void)_t1383;
    if (_t1383) {
        Bool _t1317; { Bool *_hp = (Bool *)TokenType_is_KwCase(other); _t1317 = *_hp; free(_hp); }
        (void)_t1317;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1317; return _r; }
    }
    ;
    Bool _t1384; { Bool *_hp = (Bool *)TokenType_is_KwDefault(self); _t1384 = *_hp; free(_hp); }
    (void)_t1384;
    if (_t1384) {
        Bool _t1318; { Bool *_hp = (Bool *)TokenType_is_KwDefault(other); _t1318 = *_hp; free(_hp); }
        (void)_t1318;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1318; return _r; }
    }
    ;
    Bool _t1385; { Bool *_hp = (Bool *)TokenType_is_KwReturn(self); _t1385 = *_hp; free(_hp); }
    (void)_t1385;
    if (_t1385) {
        Bool _t1319; { Bool *_hp = (Bool *)TokenType_is_KwReturn(other); _t1319 = *_hp; free(_hp); }
        (void)_t1319;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1319; return _r; }
    }
    ;
    Bool _t1386; { Bool *_hp = (Bool *)TokenType_is_KwThrow(self); _t1386 = *_hp; free(_hp); }
    (void)_t1386;
    if (_t1386) {
        Bool _t1320; { Bool *_hp = (Bool *)TokenType_is_KwThrow(other); _t1320 = *_hp; free(_hp); }
        (void)_t1320;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1320; return _r; }
    }
    ;
    Bool _t1387; { Bool *_hp = (Bool *)TokenType_is_KwCatch(self); _t1387 = *_hp; free(_hp); }
    (void)_t1387;
    if (_t1387) {
        Bool _t1321; { Bool *_hp = (Bool *)TokenType_is_KwCatch(other); _t1321 = *_hp; free(_hp); }
        (void)_t1321;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1321; return _r; }
    }
    ;
    Bool _t1388; { Bool *_hp = (Bool *)TokenType_is_KwBreak(self); _t1388 = *_hp; free(_hp); }
    (void)_t1388;
    if (_t1388) {
        Bool _t1322; { Bool *_hp = (Bool *)TokenType_is_KwBreak(other); _t1322 = *_hp; free(_hp); }
        (void)_t1322;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1322; return _r; }
    }
    ;
    Bool _t1389; { Bool *_hp = (Bool *)TokenType_is_KwContinue(self); _t1389 = *_hp; free(_hp); }
    (void)_t1389;
    if (_t1389) {
        Bool _t1323; { Bool *_hp = (Bool *)TokenType_is_KwContinue(other); _t1323 = *_hp; free(_hp); }
        (void)_t1323;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1323; return _r; }
    }
    ;
    Bool _t1390; { Bool *_hp = (Bool *)TokenType_is_KwDefer(self); _t1390 = *_hp; free(_hp); }
    (void)_t1390;
    if (_t1390) {
        Bool _t1324; { Bool *_hp = (Bool *)TokenType_is_KwDefer(other); _t1324 = *_hp; free(_hp); }
        (void)_t1324;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1324; return _r; }
    }
    ;
    Bool _t1391; { Bool *_hp = (Bool *)TokenType_is_KwTrue(self); _t1391 = *_hp; free(_hp); }
    (void)_t1391;
    if (_t1391) {
        Bool _t1325; { Bool *_hp = (Bool *)TokenType_is_KwTrue(other); _t1325 = *_hp; free(_hp); }
        (void)_t1325;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1325; return _r; }
    }
    ;
    Bool _t1392; { Bool *_hp = (Bool *)TokenType_is_KwFalse(self); _t1392 = *_hp; free(_hp); }
    (void)_t1392;
    if (_t1392) {
        Bool _t1326; { Bool *_hp = (Bool *)TokenType_is_KwFalse(other); _t1326 = *_hp; free(_hp); }
        (void)_t1326;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1326; return _r; }
    }
    ;
    Bool _t1393; { Bool *_hp = (Bool *)TokenType_is_KwNull(self); _t1393 = *_hp; free(_hp); }
    (void)_t1393;
    if (_t1393) {
        Bool _t1327; { Bool *_hp = (Bool *)TokenType_is_KwNull(other); _t1327 = *_hp; free(_hp); }
        (void)_t1327;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1327; return _r; }
    }
    ;
    Bool _t1394; { Bool *_hp = (Bool *)TokenType_is_Error(self); _t1394 = *_hp; free(_hp); }
    (void)_t1394;
    if (_t1394) {
        Bool _t1328; { Bool *_hp = (Bool *)TokenType_is_Error(other); _t1328 = *_hp; free(_hp); }
        (void)_t1328;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1328; return _r; }
    }
    ;
    Bool _t1395 = 0;
    (void)_t1395;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1395; return _r; }
}

TokenType * TokenType_clone(TokenType * self) {
    (void)self;
    Bool _t1396; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t1396 = *_hp; free(_hp); }
    (void)_t1396;
    if (_t1396) {
        ;
        return TokenType_Eof();
    }
    ;
    Bool _t1397; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t1397 = *_hp; free(_hp); }
    (void)_t1397;
    if (_t1397) {
        ;
        return TokenType_LParen();
    }
    ;
    Bool _t1398; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t1398 = *_hp; free(_hp); }
    (void)_t1398;
    if (_t1398) {
        ;
        return TokenType_RParen();
    }
    ;
    Bool _t1399; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t1399 = *_hp; free(_hp); }
    (void)_t1399;
    if (_t1399) {
        ;
        return TokenType_LBrace();
    }
    ;
    Bool _t1400; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t1400 = *_hp; free(_hp); }
    (void)_t1400;
    if (_t1400) {
        ;
        return TokenType_RBrace();
    }
    ;
    Bool _t1401; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t1401 = *_hp; free(_hp); }
    (void)_t1401;
    if (_t1401) {
        ;
        return TokenType_LBracket();
    }
    ;
    Bool _t1402; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t1402 = *_hp; free(_hp); }
    (void)_t1402;
    if (_t1402) {
        ;
        return TokenType_RBracket();
    }
    ;
    Bool _t1403; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t1403 = *_hp; free(_hp); }
    (void)_t1403;
    if (_t1403) {
        ;
        return TokenType_Comma();
    }
    ;
    Bool _t1404; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t1404 = *_hp; free(_hp); }
    (void)_t1404;
    if (_t1404) {
        ;
        return TokenType_Colon();
    }
    ;
    Bool _t1405; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t1405 = *_hp; free(_hp); }
    (void)_t1405;
    if (_t1405) {
        ;
        return TokenType_Question();
    }
    ;
    Bool _t1406; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t1406 = *_hp; free(_hp); }
    (void)_t1406;
    if (_t1406) {
        ;
        return TokenType_Bang();
    }
    ;
    Bool _t1407; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t1407 = *_hp; free(_hp); }
    (void)_t1407;
    if (_t1407) {
        ;
        return TokenType_Minus();
    }
    ;
    Bool _t1408; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t1408 = *_hp; free(_hp); }
    (void)_t1408;
    if (_t1408) {
        ;
        return TokenType_Plus();
    }
    ;
    Bool _t1409; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t1409 = *_hp; free(_hp); }
    (void)_t1409;
    if (_t1409) {
        ;
        return TokenType_Star();
    }
    ;
    Bool _t1410; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t1410 = *_hp; free(_hp); }
    (void)_t1410;
    if (_t1410) {
        ;
        return TokenType_Slash();
    }
    ;
    Bool _t1411; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t1411 = *_hp; free(_hp); }
    (void)_t1411;
    if (_t1411) {
        ;
        return TokenType_Dot();
    }
    ;
    Bool _t1412; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t1412 = *_hp; free(_hp); }
    (void)_t1412;
    if (_t1412) {
        ;
        return TokenType_DotDot();
    }
    ;
    Bool _t1413; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDotDot()); _t1413 = *_hp; free(_hp); }
    (void)_t1413;
    if (_t1413) {
        ;
        return TokenType_DotDotDot();
    }
    ;
    Bool _t1414; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t1414 = *_hp; free(_hp); }
    (void)_t1414;
    if (_t1414) {
        ;
        return TokenType_Eq();
    }
    ;
    Bool _t1415; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t1415 = *_hp; free(_hp); }
    (void)_t1415;
    if (_t1415) {
        ;
        return TokenType_EqEq();
    }
    ;
    Bool _t1416; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t1416 = *_hp; free(_hp); }
    (void)_t1416;
    if (_t1416) {
        ;
        return TokenType_Neq();
    }
    ;
    Bool _t1417; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t1417 = *_hp; free(_hp); }
    (void)_t1417;
    if (_t1417) {
        ;
        return TokenType_Lt();
    }
    ;
    Bool _t1418; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t1418 = *_hp; free(_hp); }
    (void)_t1418;
    if (_t1418) {
        ;
        return TokenType_LtEq();
    }
    ;
    Bool _t1419; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t1419 = *_hp; free(_hp); }
    (void)_t1419;
    if (_t1419) {
        ;
        return TokenType_Gt();
    }
    ;
    Bool _t1420; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t1420 = *_hp; free(_hp); }
    (void)_t1420;
    if (_t1420) {
        ;
        return TokenType_GtEq();
    }
    ;
    Bool _t1421; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t1421 = *_hp; free(_hp); }
    (void)_t1421;
    if (_t1421) {
        ;
        return TokenType_ColonEq();
    }
    ;
    Bool _t1422; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t1422 = *_hp; free(_hp); }
    (void)_t1422;
    if (_t1422) {
        ;
        return TokenType_Ident();
    }
    ;
    Bool _t1423; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t1423 = *_hp; free(_hp); }
    (void)_t1423;
    if (_t1423) {
        ;
        return TokenType_StringTok();
    }
    ;
    Bool _t1424; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t1424 = *_hp; free(_hp); }
    (void)_t1424;
    if (_t1424) {
        ;
        return TokenType_Number();
    }
    ;
    Bool _t1425; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t1425 = *_hp; free(_hp); }
    (void)_t1425;
    if (_t1425) {
        ;
        return TokenType_Char();
    }
    ;
    Bool _t1426; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t1426 = *_hp; free(_hp); }
    (void)_t1426;
    if (_t1426) {
        ;
        return TokenType_KwMode();
    }
    ;
    Bool _t1427; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t1427 = *_hp; free(_hp); }
    (void)_t1427;
    if (_t1427) {
        ;
        return TokenType_KwMut();
    }
    ;
    Bool _t1428; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t1428 = *_hp; free(_hp); }
    (void)_t1428;
    if (_t1428) {
        ;
        return TokenType_KwOwn();
    }
    ;
    Bool _t1429; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t1429 = *_hp; free(_hp); }
    (void)_t1429;
    if (_t1429) {
        ;
        return TokenType_KwRef();
    }
    ;
    Bool _t1430; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t1430 = *_hp; free(_hp); }
    (void)_t1430;
    if (_t1430) {
        ;
        return TokenType_KwShallow();
    }
    ;
    Bool _t1431; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t1431 = *_hp; free(_hp); }
    (void)_t1431;
    if (_t1431) {
        ;
        return TokenType_KwStruct();
    }
    ;
    Bool _t1432; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t1432 = *_hp; free(_hp); }
    (void)_t1432;
    if (_t1432) {
        ;
        return TokenType_KwExtStruct();
    }
    ;
    Bool _t1433; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t1433 = *_hp; free(_hp); }
    (void)_t1433;
    if (_t1433) {
        ;
        return TokenType_KwEnum();
    }
    ;
    Bool _t1434; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t1434 = *_hp; free(_hp); }
    (void)_t1434;
    if (_t1434) {
        ;
        return TokenType_KwNamespace();
    }
    ;
    Bool _t1435; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t1435 = *_hp; free(_hp); }
    (void)_t1435;
    if (_t1435) {
        ;
        return TokenType_KwFunc();
    }
    ;
    Bool _t1436; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t1436 = *_hp; free(_hp); }
    (void)_t1436;
    if (_t1436) {
        ;
        return TokenType_KwProc();
    }
    ;
    Bool _t1437; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t1437 = *_hp; free(_hp); }
    (void)_t1437;
    if (_t1437) {
        ;
        return TokenType_KwTest();
    }
    ;
    Bool _t1438; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t1438 = *_hp; free(_hp); }
    (void)_t1438;
    if (_t1438) {
        ;
        return TokenType_KwMacro();
    }
    ;
    Bool _t1439; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t1439 = *_hp; free(_hp); }
    (void)_t1439;
    if (_t1439) {
        ;
        return TokenType_KwExtFunc();
    }
    ;
    Bool _t1440; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t1440 = *_hp; free(_hp); }
    (void)_t1440;
    if (_t1440) {
        ;
        return TokenType_KwExtProc();
    }
    ;
    Bool _t1441; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t1441 = *_hp; free(_hp); }
    (void)_t1441;
    if (_t1441) {
        ;
        return TokenType_KwReturns();
    }
    ;
    Bool _t1442; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t1442 = *_hp; free(_hp); }
    (void)_t1442;
    if (_t1442) {
        ;
        return TokenType_KwThrows();
    }
    ;
    Bool _t1443; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t1443 = *_hp; free(_hp); }
    (void)_t1443;
    if (_t1443) {
        ;
        return TokenType_KwIf();
    }
    ;
    Bool _t1444; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t1444 = *_hp; free(_hp); }
    (void)_t1444;
    if (_t1444) {
        ;
        return TokenType_KwElse();
    }
    ;
    Bool _t1445; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t1445 = *_hp; free(_hp); }
    (void)_t1445;
    if (_t1445) {
        ;
        return TokenType_KwWhile();
    }
    ;
    Bool _t1446; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t1446 = *_hp; free(_hp); }
    (void)_t1446;
    if (_t1446) {
        ;
        return TokenType_KwFor();
    }
    ;
    Bool _t1447; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t1447 = *_hp; free(_hp); }
    (void)_t1447;
    if (_t1447) {
        ;
        return TokenType_KwIn();
    }
    ;
    Bool _t1448; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t1448 = *_hp; free(_hp); }
    (void)_t1448;
    if (_t1448) {
        ;
        return TokenType_KwSwitch();
    }
    ;
    Bool _t1449; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t1449 = *_hp; free(_hp); }
    (void)_t1449;
    if (_t1449) {
        ;
        return TokenType_KwMatch();
    }
    ;
    Bool _t1450; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t1450 = *_hp; free(_hp); }
    (void)_t1450;
    if (_t1450) {
        ;
        return TokenType_KwCase();
    }
    ;
    Bool _t1451; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t1451 = *_hp; free(_hp); }
    (void)_t1451;
    if (_t1451) {
        ;
        return TokenType_KwDefault();
    }
    ;
    Bool _t1452; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t1452 = *_hp; free(_hp); }
    (void)_t1452;
    if (_t1452) {
        ;
        return TokenType_KwReturn();
    }
    ;
    Bool _t1453; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t1453 = *_hp; free(_hp); }
    (void)_t1453;
    if (_t1453) {
        ;
        return TokenType_KwThrow();
    }
    ;
    Bool _t1454; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t1454 = *_hp; free(_hp); }
    (void)_t1454;
    if (_t1454) {
        ;
        return TokenType_KwCatch();
    }
    ;
    Bool _t1455; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t1455 = *_hp; free(_hp); }
    (void)_t1455;
    if (_t1455) {
        ;
        return TokenType_KwBreak();
    }
    ;
    Bool _t1456; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t1456 = *_hp; free(_hp); }
    (void)_t1456;
    if (_t1456) {
        ;
        return TokenType_KwContinue();
    }
    ;
    Bool _t1457; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t1457 = *_hp; free(_hp); }
    (void)_t1457;
    if (_t1457) {
        ;
        return TokenType_KwDefer();
    }
    ;
    Bool _t1458; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t1458 = *_hp; free(_hp); }
    (void)_t1458;
    if (_t1458) {
        ;
        return TokenType_KwTrue();
    }
    ;
    Bool _t1459; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t1459 = *_hp; free(_hp); }
    (void)_t1459;
    if (_t1459) {
        ;
        return TokenType_KwFalse();
    }
    ;
    Bool _t1460; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t1460 = *_hp; free(_hp); }
    (void)_t1460;
    if (_t1460) {
        ;
        return TokenType_KwNull();
    }
    ;
    return TokenType_Error();
}

void TokenType_delete(TokenType * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * TokenType_to_str(TokenType * self) {
    (void)self;
    Bool _t1527; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t1527 = *_hp; free(_hp); }
    (void)_t1527;
    if (_t1527) {
        Str *_t1461 = Str_lit("Eof", 3ULL);
        (void)_t1461;
        ;
        return _t1461;
    }
    ;
    Bool _t1528; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t1528 = *_hp; free(_hp); }
    (void)_t1528;
    if (_t1528) {
        Str *_t1462 = Str_lit("LParen", 6ULL);
        (void)_t1462;
        ;
        return _t1462;
    }
    ;
    Bool _t1529; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t1529 = *_hp; free(_hp); }
    (void)_t1529;
    if (_t1529) {
        Str *_t1463 = Str_lit("RParen", 6ULL);
        (void)_t1463;
        ;
        return _t1463;
    }
    ;
    Bool _t1530; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t1530 = *_hp; free(_hp); }
    (void)_t1530;
    if (_t1530) {
        Str *_t1464 = Str_lit("LBrace", 6ULL);
        (void)_t1464;
        ;
        return _t1464;
    }
    ;
    Bool _t1531; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t1531 = *_hp; free(_hp); }
    (void)_t1531;
    if (_t1531) {
        Str *_t1465 = Str_lit("RBrace", 6ULL);
        (void)_t1465;
        ;
        return _t1465;
    }
    ;
    Bool _t1532; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t1532 = *_hp; free(_hp); }
    (void)_t1532;
    if (_t1532) {
        Str *_t1466 = Str_lit("LBracket", 8ULL);
        (void)_t1466;
        ;
        return _t1466;
    }
    ;
    Bool _t1533; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t1533 = *_hp; free(_hp); }
    (void)_t1533;
    if (_t1533) {
        Str *_t1467 = Str_lit("RBracket", 8ULL);
        (void)_t1467;
        ;
        return _t1467;
    }
    ;
    Bool _t1534; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t1534 = *_hp; free(_hp); }
    (void)_t1534;
    if (_t1534) {
        Str *_t1468 = Str_lit("Comma", 5ULL);
        (void)_t1468;
        ;
        return _t1468;
    }
    ;
    Bool _t1535; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t1535 = *_hp; free(_hp); }
    (void)_t1535;
    if (_t1535) {
        Str *_t1469 = Str_lit("Colon", 5ULL);
        (void)_t1469;
        ;
        return _t1469;
    }
    ;
    Bool _t1536; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t1536 = *_hp; free(_hp); }
    (void)_t1536;
    if (_t1536) {
        Str *_t1470 = Str_lit("Question", 8ULL);
        (void)_t1470;
        ;
        return _t1470;
    }
    ;
    Bool _t1537; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t1537 = *_hp; free(_hp); }
    (void)_t1537;
    if (_t1537) {
        Str *_t1471 = Str_lit("Bang", 4ULL);
        (void)_t1471;
        ;
        return _t1471;
    }
    ;
    Bool _t1538; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t1538 = *_hp; free(_hp); }
    (void)_t1538;
    if (_t1538) {
        Str *_t1472 = Str_lit("Minus", 5ULL);
        (void)_t1472;
        ;
        return _t1472;
    }
    ;
    Bool _t1539; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t1539 = *_hp; free(_hp); }
    (void)_t1539;
    if (_t1539) {
        Str *_t1473 = Str_lit("Plus", 4ULL);
        (void)_t1473;
        ;
        return _t1473;
    }
    ;
    Bool _t1540; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t1540 = *_hp; free(_hp); }
    (void)_t1540;
    if (_t1540) {
        Str *_t1474 = Str_lit("Star", 4ULL);
        (void)_t1474;
        ;
        return _t1474;
    }
    ;
    Bool _t1541; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t1541 = *_hp; free(_hp); }
    (void)_t1541;
    if (_t1541) {
        Str *_t1475 = Str_lit("Slash", 5ULL);
        (void)_t1475;
        ;
        return _t1475;
    }
    ;
    Bool _t1542; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t1542 = *_hp; free(_hp); }
    (void)_t1542;
    if (_t1542) {
        Str *_t1476 = Str_lit("Dot", 3ULL);
        (void)_t1476;
        ;
        return _t1476;
    }
    ;
    Bool _t1543; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t1543 = *_hp; free(_hp); }
    (void)_t1543;
    if (_t1543) {
        Str *_t1477 = Str_lit("DotDot", 6ULL);
        (void)_t1477;
        ;
        return _t1477;
    }
    ;
    Bool _t1544; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDotDot()); _t1544 = *_hp; free(_hp); }
    (void)_t1544;
    if (_t1544) {
        Str *_t1478 = Str_lit("DotDotDot", 9ULL);
        (void)_t1478;
        ;
        return _t1478;
    }
    ;
    Bool _t1545; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t1545 = *_hp; free(_hp); }
    (void)_t1545;
    if (_t1545) {
        Str *_t1479 = Str_lit("Eq", 2ULL);
        (void)_t1479;
        ;
        return _t1479;
    }
    ;
    Bool _t1546; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t1546 = *_hp; free(_hp); }
    (void)_t1546;
    if (_t1546) {
        Str *_t1480 = Str_lit("EqEq", 4ULL);
        (void)_t1480;
        ;
        return _t1480;
    }
    ;
    Bool _t1547; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t1547 = *_hp; free(_hp); }
    (void)_t1547;
    if (_t1547) {
        Str *_t1481 = Str_lit("Neq", 3ULL);
        (void)_t1481;
        ;
        return _t1481;
    }
    ;
    Bool _t1548; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t1548 = *_hp; free(_hp); }
    (void)_t1548;
    if (_t1548) {
        Str *_t1482 = Str_lit("Lt", 2ULL);
        (void)_t1482;
        ;
        return _t1482;
    }
    ;
    Bool _t1549; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t1549 = *_hp; free(_hp); }
    (void)_t1549;
    if (_t1549) {
        Str *_t1483 = Str_lit("LtEq", 4ULL);
        (void)_t1483;
        ;
        return _t1483;
    }
    ;
    Bool _t1550; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t1550 = *_hp; free(_hp); }
    (void)_t1550;
    if (_t1550) {
        Str *_t1484 = Str_lit("Gt", 2ULL);
        (void)_t1484;
        ;
        return _t1484;
    }
    ;
    Bool _t1551; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t1551 = *_hp; free(_hp); }
    (void)_t1551;
    if (_t1551) {
        Str *_t1485 = Str_lit("GtEq", 4ULL);
        (void)_t1485;
        ;
        return _t1485;
    }
    ;
    Bool _t1552; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t1552 = *_hp; free(_hp); }
    (void)_t1552;
    if (_t1552) {
        Str *_t1486 = Str_lit("ColonEq", 7ULL);
        (void)_t1486;
        ;
        return _t1486;
    }
    ;
    Bool _t1553; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t1553 = *_hp; free(_hp); }
    (void)_t1553;
    if (_t1553) {
        Str *_t1487 = Str_lit("Ident", 5ULL);
        (void)_t1487;
        ;
        return _t1487;
    }
    ;
    Bool _t1554; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t1554 = *_hp; free(_hp); }
    (void)_t1554;
    if (_t1554) {
        Str *_t1488 = Str_lit("StringTok", 9ULL);
        (void)_t1488;
        ;
        return _t1488;
    }
    ;
    Bool _t1555; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t1555 = *_hp; free(_hp); }
    (void)_t1555;
    if (_t1555) {
        Str *_t1489 = Str_lit("Number", 6ULL);
        (void)_t1489;
        ;
        return _t1489;
    }
    ;
    Bool _t1556; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t1556 = *_hp; free(_hp); }
    (void)_t1556;
    if (_t1556) {
        Str *_t1490 = Str_lit("Char", 4ULL);
        (void)_t1490;
        ;
        return _t1490;
    }
    ;
    Bool _t1557; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t1557 = *_hp; free(_hp); }
    (void)_t1557;
    if (_t1557) {
        Str *_t1491 = Str_lit("KwMode", 6ULL);
        (void)_t1491;
        ;
        return _t1491;
    }
    ;
    Bool _t1558; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t1558 = *_hp; free(_hp); }
    (void)_t1558;
    if (_t1558) {
        Str *_t1492 = Str_lit("KwMut", 5ULL);
        (void)_t1492;
        ;
        return _t1492;
    }
    ;
    Bool _t1559; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t1559 = *_hp; free(_hp); }
    (void)_t1559;
    if (_t1559) {
        Str *_t1493 = Str_lit("KwOwn", 5ULL);
        (void)_t1493;
        ;
        return _t1493;
    }
    ;
    Bool _t1560; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t1560 = *_hp; free(_hp); }
    (void)_t1560;
    if (_t1560) {
        Str *_t1494 = Str_lit("KwRef", 5ULL);
        (void)_t1494;
        ;
        return _t1494;
    }
    ;
    Bool _t1561; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t1561 = *_hp; free(_hp); }
    (void)_t1561;
    if (_t1561) {
        Str *_t1495 = Str_lit("KwShallow", 9ULL);
        (void)_t1495;
        ;
        return _t1495;
    }
    ;
    Bool _t1562; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t1562 = *_hp; free(_hp); }
    (void)_t1562;
    if (_t1562) {
        Str *_t1496 = Str_lit("KwStruct", 8ULL);
        (void)_t1496;
        ;
        return _t1496;
    }
    ;
    Bool _t1563; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t1563 = *_hp; free(_hp); }
    (void)_t1563;
    if (_t1563) {
        Str *_t1497 = Str_lit("KwExtStruct", 11ULL);
        (void)_t1497;
        ;
        return _t1497;
    }
    ;
    Bool _t1564; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t1564 = *_hp; free(_hp); }
    (void)_t1564;
    if (_t1564) {
        Str *_t1498 = Str_lit("KwEnum", 6ULL);
        (void)_t1498;
        ;
        return _t1498;
    }
    ;
    Bool _t1565; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t1565 = *_hp; free(_hp); }
    (void)_t1565;
    if (_t1565) {
        Str *_t1499 = Str_lit("KwNamespace", 11ULL);
        (void)_t1499;
        ;
        return _t1499;
    }
    ;
    Bool _t1566; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t1566 = *_hp; free(_hp); }
    (void)_t1566;
    if (_t1566) {
        Str *_t1500 = Str_lit("KwFunc", 6ULL);
        (void)_t1500;
        ;
        return _t1500;
    }
    ;
    Bool _t1567; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t1567 = *_hp; free(_hp); }
    (void)_t1567;
    if (_t1567) {
        Str *_t1501 = Str_lit("KwProc", 6ULL);
        (void)_t1501;
        ;
        return _t1501;
    }
    ;
    Bool _t1568; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t1568 = *_hp; free(_hp); }
    (void)_t1568;
    if (_t1568) {
        Str *_t1502 = Str_lit("KwTest", 6ULL);
        (void)_t1502;
        ;
        return _t1502;
    }
    ;
    Bool _t1569; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t1569 = *_hp; free(_hp); }
    (void)_t1569;
    if (_t1569) {
        Str *_t1503 = Str_lit("KwMacro", 7ULL);
        (void)_t1503;
        ;
        return _t1503;
    }
    ;
    Bool _t1570; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t1570 = *_hp; free(_hp); }
    (void)_t1570;
    if (_t1570) {
        Str *_t1504 = Str_lit("KwExtFunc", 9ULL);
        (void)_t1504;
        ;
        return _t1504;
    }
    ;
    Bool _t1571; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t1571 = *_hp; free(_hp); }
    (void)_t1571;
    if (_t1571) {
        Str *_t1505 = Str_lit("KwExtProc", 9ULL);
        (void)_t1505;
        ;
        return _t1505;
    }
    ;
    Bool _t1572; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t1572 = *_hp; free(_hp); }
    (void)_t1572;
    if (_t1572) {
        Str *_t1506 = Str_lit("KwReturns", 9ULL);
        (void)_t1506;
        ;
        return _t1506;
    }
    ;
    Bool _t1573; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t1573 = *_hp; free(_hp); }
    (void)_t1573;
    if (_t1573) {
        Str *_t1507 = Str_lit("KwThrows", 8ULL);
        (void)_t1507;
        ;
        return _t1507;
    }
    ;
    Bool _t1574; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t1574 = *_hp; free(_hp); }
    (void)_t1574;
    if (_t1574) {
        Str *_t1508 = Str_lit("KwIf", 4ULL);
        (void)_t1508;
        ;
        return _t1508;
    }
    ;
    Bool _t1575; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t1575 = *_hp; free(_hp); }
    (void)_t1575;
    if (_t1575) {
        Str *_t1509 = Str_lit("KwElse", 6ULL);
        (void)_t1509;
        ;
        return _t1509;
    }
    ;
    Bool _t1576; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t1576 = *_hp; free(_hp); }
    (void)_t1576;
    if (_t1576) {
        Str *_t1510 = Str_lit("KwWhile", 7ULL);
        (void)_t1510;
        ;
        return _t1510;
    }
    ;
    Bool _t1577; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t1577 = *_hp; free(_hp); }
    (void)_t1577;
    if (_t1577) {
        Str *_t1511 = Str_lit("KwFor", 5ULL);
        (void)_t1511;
        ;
        return _t1511;
    }
    ;
    Bool _t1578; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t1578 = *_hp; free(_hp); }
    (void)_t1578;
    if (_t1578) {
        Str *_t1512 = Str_lit("KwIn", 4ULL);
        (void)_t1512;
        ;
        return _t1512;
    }
    ;
    Bool _t1579; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t1579 = *_hp; free(_hp); }
    (void)_t1579;
    if (_t1579) {
        Str *_t1513 = Str_lit("KwSwitch", 8ULL);
        (void)_t1513;
        ;
        return _t1513;
    }
    ;
    Bool _t1580; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t1580 = *_hp; free(_hp); }
    (void)_t1580;
    if (_t1580) {
        Str *_t1514 = Str_lit("KwMatch", 7ULL);
        (void)_t1514;
        ;
        return _t1514;
    }
    ;
    Bool _t1581; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t1581 = *_hp; free(_hp); }
    (void)_t1581;
    if (_t1581) {
        Str *_t1515 = Str_lit("KwCase", 6ULL);
        (void)_t1515;
        ;
        return _t1515;
    }
    ;
    Bool _t1582; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t1582 = *_hp; free(_hp); }
    (void)_t1582;
    if (_t1582) {
        Str *_t1516 = Str_lit("KwDefault", 9ULL);
        (void)_t1516;
        ;
        return _t1516;
    }
    ;
    Bool _t1583; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t1583 = *_hp; free(_hp); }
    (void)_t1583;
    if (_t1583) {
        Str *_t1517 = Str_lit("KwReturn", 8ULL);
        (void)_t1517;
        ;
        return _t1517;
    }
    ;
    Bool _t1584; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t1584 = *_hp; free(_hp); }
    (void)_t1584;
    if (_t1584) {
        Str *_t1518 = Str_lit("KwThrow", 7ULL);
        (void)_t1518;
        ;
        return _t1518;
    }
    ;
    Bool _t1585; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t1585 = *_hp; free(_hp); }
    (void)_t1585;
    if (_t1585) {
        Str *_t1519 = Str_lit("KwCatch", 7ULL);
        (void)_t1519;
        ;
        return _t1519;
    }
    ;
    Bool _t1586; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t1586 = *_hp; free(_hp); }
    (void)_t1586;
    if (_t1586) {
        Str *_t1520 = Str_lit("KwBreak", 7ULL);
        (void)_t1520;
        ;
        return _t1520;
    }
    ;
    Bool _t1587; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t1587 = *_hp; free(_hp); }
    (void)_t1587;
    if (_t1587) {
        Str *_t1521 = Str_lit("KwContinue", 10ULL);
        (void)_t1521;
        ;
        return _t1521;
    }
    ;
    Bool _t1588; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t1588 = *_hp; free(_hp); }
    (void)_t1588;
    if (_t1588) {
        Str *_t1522 = Str_lit("KwDefer", 7ULL);
        (void)_t1522;
        ;
        return _t1522;
    }
    ;
    Bool _t1589; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t1589 = *_hp; free(_hp); }
    (void)_t1589;
    if (_t1589) {
        Str *_t1523 = Str_lit("KwTrue", 6ULL);
        (void)_t1523;
        ;
        return _t1523;
    }
    ;
    Bool _t1590; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t1590 = *_hp; free(_hp); }
    (void)_t1590;
    if (_t1590) {
        Str *_t1524 = Str_lit("KwFalse", 7ULL);
        (void)_t1524;
        ;
        return _t1524;
    }
    ;
    Bool _t1591; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t1591 = *_hp; free(_hp); }
    (void)_t1591;
    if (_t1591) {
        Str *_t1525 = Str_lit("KwNull", 6ULL);
        (void)_t1525;
        ;
        return _t1525;
    }
    ;
    Bool _t1592; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Error()); _t1592 = *_hp; free(_hp); }
    (void)_t1592;
    if (_t1592) {
        Str *_t1526 = Str_lit("Error", 5ULL);
        (void)_t1526;
        ;
        return _t1526;
    }
    ;
    Str *_t1593 = Str_lit("unknown", 7ULL);
    (void)_t1593;
    return _t1593;
}

U64 *TokenType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TokenType);
    return r;
}


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

void Token_delete(Token * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t1598 = 0;
    (void)_t1598;
    TokenType_delete(&self->type, &(Bool){_t1598});
    ;
    Bool _t1599 = 0;
    (void)_t1599;
    Str_delete(&self->text, &(Bool){_t1599});
    ;
    Bool _t1600 = 0;
    (void)_t1600;
    I64_delete(&self->line, &(Bool){_t1600});
    ;
    Bool _t1601 = 0;
    (void)_t1601;
    I64_delete(&self->col, &(Bool){_t1601});
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

