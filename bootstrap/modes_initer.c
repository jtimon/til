#include "modes_initer.h"

TypeBinding * TypeBinding_clone(TypeBinding * self) {
    (void)self;
    Bool _t4080 = Bool_clone(&self->is_mut);
    (void)_t4080;
    U32 _t4081 = U32_clone(&self->line);
    (void)_t4081;
    U32 _t4082 = U32_clone(&self->col);
    (void)_t4082;
    Bool _t4083 = Bool_clone(&self->is_param);
    (void)_t4083;
    Bool _t4084 = Bool_clone(&self->is_own);
    (void)_t4084;
    Bool _t4085 = Bool_clone(&self->is_ref);
    (void)_t4085;
    Bool _t4086 = Bool_clone(&self->is_alias);
    (void)_t4086;
    Bool _t4087 = Bool_clone(&self->is_type_alias);
    (void)_t4087;
    Bool _t4088 = Bool_clone(&self->is_builtin);
    (void)_t4088;
    TypeBinding *_t4089 = malloc(sizeof(TypeBinding));
    _t4089->name = self->name;
    { TilType *_ca = TilType_clone(&self->type); _t4089->type = *_ca; free(_ca); }
    _t4089->is_proc = I32_clone(&self->is_proc);
    _t4089->is_mut = _t4080;
    _t4089->line = _t4081;
    _t4089->col = _t4082;
    _t4089->is_param = _t4083;
    _t4089->is_own = _t4084;
    _t4089->is_ref = _t4085;
    _t4089->is_alias = _t4086;
    _t4089->is_type_alias = _t4087;
    _t4089->alias_target = self->alias_target;
    _t4089->struct_def = self->struct_def;
    _t4089->func_def = self->func_def;
    _t4089->is_builtin = _t4088;
    _t4089->is_ext = Bool_clone(&self->is_ext);
    _t4089->struct_name = self->struct_name;
    (void)_t4089;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    return _t4089;
}

void TypeBinding_delete(TypeBinding * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4090 = 0;
    (void)_t4090;
    TilType_delete(&self->type, &(Bool){_t4090});
    ;
    Bool _t4091 = 0;
    (void)_t4091;
    I32_delete(&self->is_proc, &(Bool){_t4091});
    ;
    Bool _t4092 = 0;
    (void)_t4092;
    Bool_delete(&self->is_mut, &(Bool){_t4092});
    ;
    Bool _t4093 = 0;
    (void)_t4093;
    U32_delete(&self->line, &(Bool){_t4093});
    ;
    Bool _t4094 = 0;
    (void)_t4094;
    U32_delete(&self->col, &(Bool){_t4094});
    ;
    Bool _t4095 = 0;
    (void)_t4095;
    Bool_delete(&self->is_param, &(Bool){_t4095});
    ;
    Bool _t4096 = 0;
    (void)_t4096;
    Bool_delete(&self->is_own, &(Bool){_t4096});
    ;
    Bool _t4097 = 0;
    (void)_t4097;
    Bool_delete(&self->is_ref, &(Bool){_t4097});
    ;
    Bool _t4098 = 0;
    (void)_t4098;
    Bool_delete(&self->is_alias, &(Bool){_t4098});
    ;
    Bool _t4099 = 0;
    (void)_t4099;
    Bool_delete(&self->is_type_alias, &(Bool){_t4099});
    ;
    Bool _t4100 = 0;
    (void)_t4100;
    Bool_delete(&self->is_builtin, &(Bool){_t4100});
    ;
    Bool _t4101 = 0;
    (void)_t4101;
    Bool_delete(&self->is_ext, &(Bool){_t4101});
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
    TypeScope *_t4103 = malloc(sizeof(TypeScope));
    { Map *_ca = Map_clone(&self->bindings); _t4103->bindings = *_ca; free(_ca); }
    _t4103->parent = self->parent;
    (void)_t4103;
    return _t4103;
}

void TypeScope_delete(TypeScope * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4104 = 0;
    (void)_t4104;
    Map_delete(&self->bindings, &(Bool){_t4104});
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

