#include "til_dispatch.h"

ExtStr * ExtStr_clone(ExtStr * self) {
    (void)self;
    U64 _t4133 = U64_clone(&self->count);
    (void)_t4133;
    U64 _t4134 = U64_clone(&self->cap);
    (void)_t4134;
    ExtStr *_t4135 = malloc(sizeof(ExtStr));
    _t4135->data = self->data;
    _t4135->count = _t4133;
    _t4135->cap = _t4134;
    (void)_t4135;
    ;
    ;
    return _t4135;
}

void ExtStr_delete(ExtStr * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4136 = 0;
    (void)_t4136;
    U64_delete(&self->count, &(Bool){_t4136});
    ;
    Bool _t4137 = 0;
    (void)_t4137;
    U64_delete(&self->cap, &(Bool){_t4137});
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

