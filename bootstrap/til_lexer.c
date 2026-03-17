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

U64 *Token_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Token);
    return r;
}

