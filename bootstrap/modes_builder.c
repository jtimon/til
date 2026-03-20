#include "modes_builder.h"

CollectionInfo * CollectionInfo_clone(CollectionInfo * self) {
    (void)self;
    CollectionInfo *_t4133 = malloc(sizeof(CollectionInfo));
    _t4133->type_name = self->type_name;
    _t4133->is_vec = I32_clone(&self->is_vec);
    (void)_t4133;
    return _t4133;
}

void CollectionInfo_delete(CollectionInfo * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4134 = 0;
    (void)_t4134;
    I32_delete(&self->is_vec, &(Bool){_t4134});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *CollectionInfo_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(CollectionInfo);
    return r;
}

DynCallInfo * DynCallInfo_clone(DynCallInfo * self) {
    (void)self;
    Bool _t4136 = Bool_clone(&self->has_return);
    (void)_t4136;
    DynCallInfo *_t4137 = malloc(sizeof(DynCallInfo));
    _t4137->method = self->method;
    _t4137->nargs = I32_clone(&self->nargs);
    _t4137->has_return = _t4136;
    (void)_t4137;
    ;
    return _t4137;
}

void DynCallInfo_delete(DynCallInfo * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4138 = 0;
    (void)_t4138;
    I32_delete(&self->nargs, &(Bool){_t4138});
    ;
    Bool _t4139 = 0;
    (void)_t4139;
    Bool_delete(&self->has_return, &(Bool){_t4139});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *DynCallInfo_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(DynCallInfo);
    return r;
}

