#include "modes_typer.h"

LocalInfo * LocalInfo_clone(LocalInfo * self) {
    (void)self;
    I32 _t4124 = I32_clone(&self->own_transfer);
    (void)_t4124;
    Bool _t4125 = Bool_clone(&self->skip_delete);
    (void)_t4125;
    LocalInfo *_t4126 = malloc(sizeof(LocalInfo));
    _t4126->name = self->name;
    { TilType *_ca = TilType_clone(&self->type); _t4126->type = *_ca; free(_ca); }
    _t4126->struct_name = self->struct_name;
    _t4126->decl_index = I32_clone(&self->decl_index);
    _t4126->last_use = I32_clone(&self->last_use);
    _t4126->own_transfer = _t4124;
    _t4126->skip_delete = _t4125;
    (void)_t4126;
    ;
    ;
    return _t4126;
}

void LocalInfo_delete(LocalInfo * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4127 = 0;
    (void)_t4127;
    TilType_delete(&self->type, &(Bool){_t4127});
    ;
    Bool _t4128 = 0;
    (void)_t4128;
    I32_delete(&self->decl_index, &(Bool){_t4128});
    ;
    Bool _t4129 = 0;
    (void)_t4129;
    I32_delete(&self->last_use, &(Bool){_t4129});
    ;
    Bool _t4130 = 0;
    (void)_t4130;
    I32_delete(&self->own_transfer, &(Bool){_t4130});
    ;
    Bool _t4131 = 0;
    (void)_t4131;
    Bool_delete(&self->skip_delete, &(Bool){_t4131});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *LocalInfo_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(LocalInfo);
    return r;
}

