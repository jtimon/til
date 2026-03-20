#include "til_dispatch.h"

ExtStr * ExtStr_clone(ExtStr * self) {
    (void)self;
    U64 _t4141 = U64_clone(&self->count);
    (void)_t4141;
    U64 _t4142 = U64_clone(&self->cap);
    (void)_t4142;
    ExtStr *_t4143 = malloc(sizeof(ExtStr));
    _t4143->data = self->data;
    _t4143->count = _t4141;
    _t4143->cap = _t4142;
    (void)_t4143;
    ;
    ;
    return _t4143;
}

void ExtStr_delete(ExtStr * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4144 = 0;
    (void)_t4144;
    U64_delete(&self->count, &(Bool){_t4144});
    ;
    Bool _t4145 = 0;
    (void)_t4145;
    U64_delete(&self->cap, &(Bool){_t4145});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *ExtStr_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(ExtStr);
    return r;
}

