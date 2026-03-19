#include "modes_initer.h"

TypeBinding * TypeBinding_clone(TypeBinding * self) {
    (void)self;
    Bool _t4196 = Bool_clone(&self->is_mut);
    (void)_t4196;
    U32 _t4197 = U32_clone(&self->line);
    (void)_t4197;
    U32 _t4198 = U32_clone(&self->col);
    (void)_t4198;
    Bool _t4199 = Bool_clone(&self->is_param);
    (void)_t4199;
    Bool _t4200 = Bool_clone(&self->is_own);
    (void)_t4200;
    Bool _t4201 = Bool_clone(&self->is_ref);
    (void)_t4201;
    Bool _t4202 = Bool_clone(&self->is_alias);
    (void)_t4202;
    Bool _t4203 = Bool_clone(&self->is_builtin);
    (void)_t4203;
    TypeBinding *_t4204 = malloc(sizeof(TypeBinding));
    _t4204->name = self->name;
    { TilType *_ca = TilType_clone(&self->type); _t4204->type = *_ca; free(_ca); }
    _t4204->is_proc = I32_clone(&self->is_proc);
    _t4204->is_mut = _t4196;
    _t4204->line = _t4197;
    _t4204->col = _t4198;
    _t4204->is_param = _t4199;
    _t4204->is_own = _t4200;
    _t4204->is_ref = _t4201;
    _t4204->is_alias = _t4202;
    _t4204->struct_def = self->struct_def;
    _t4204->func_def = self->func_def;
    _t4204->is_builtin = _t4203;
    _t4204->is_ext = Bool_clone(&self->is_ext);
    _t4204->struct_name = self->struct_name;
    (void)_t4204;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    return _t4204;
}

void TypeBinding_delete(TypeBinding * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4205 = 0;
    (void)_t4205;
    TilType_delete(&self->type, &(Bool){_t4205});
    ;
    Bool _t4206 = 0;
    (void)_t4206;
    I32_delete(&self->is_proc, &(Bool){_t4206});
    ;
    Bool _t4207 = 0;
    (void)_t4207;
    Bool_delete(&self->is_mut, &(Bool){_t4207});
    ;
    Bool _t4208 = 0;
    (void)_t4208;
    U32_delete(&self->line, &(Bool){_t4208});
    ;
    Bool _t4209 = 0;
    (void)_t4209;
    U32_delete(&self->col, &(Bool){_t4209});
    ;
    Bool _t4210 = 0;
    (void)_t4210;
    Bool_delete(&self->is_param, &(Bool){_t4210});
    ;
    Bool _t4211 = 0;
    (void)_t4211;
    Bool_delete(&self->is_own, &(Bool){_t4211});
    ;
    Bool _t4212 = 0;
    (void)_t4212;
    Bool_delete(&self->is_ref, &(Bool){_t4212});
    ;
    Bool _t4213 = 0;
    (void)_t4213;
    Bool_delete(&self->is_alias, &(Bool){_t4213});
    ;
    Bool _t4214 = 0;
    (void)_t4214;
    Bool_delete(&self->is_builtin, &(Bool){_t4214});
    ;
    Bool _t4215 = 0;
    (void)_t4215;
    Bool_delete(&self->is_ext, &(Bool){_t4215});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *TypeBinding_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TypeBinding);
    return r;
}

TypeScope * TypeScope_clone(TypeScope * self) {
    (void)self;
    TypeScope *_t4217 = malloc(sizeof(TypeScope));
    { Map *_ca = Map_clone(&self->bindings); _t4217->bindings = *_ca; free(_ca); }
    _t4217->parent = self->parent;
    (void)_t4217;
    return _t4217;
}

void TypeScope_delete(TypeScope * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4218 = 0;
    (void)_t4218;
    Map_delete(&self->bindings, &(Bool){_t4218});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *TypeScope_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TypeScope);
    return r;
}

