#include "modes_initer.h"

TypeBinding * TypeBinding_clone(TypeBinding * self) {
    (void)self;
    Bool _t4097 = Bool_clone(&self->is_mut);
    (void)_t4097;
    U32 _t4098 = U32_clone(&self->line);
    (void)_t4098;
    U32 _t4099 = U32_clone(&self->col);
    (void)_t4099;
    Bool _t4100 = Bool_clone(&self->is_param);
    (void)_t4100;
    Bool _t4101 = Bool_clone(&self->is_own);
    (void)_t4101;
    Bool _t4102 = Bool_clone(&self->is_ref);
    (void)_t4102;
    Bool _t4103 = Bool_clone(&self->is_alias);
    (void)_t4103;
    Bool _t4104 = Bool_clone(&self->is_type_alias);
    (void)_t4104;
    Bool _t4105 = Bool_clone(&self->is_builtin);
    (void)_t4105;
    TypeBinding *_t4106 = malloc(sizeof(TypeBinding));
    _t4106->name = self->name;
    { TilType *_ca = TilType_clone(&self->type); _t4106->type = *_ca; free(_ca); }
    _t4106->is_proc = I32_clone(&self->is_proc);
    _t4106->is_mut = _t4097;
    _t4106->line = _t4098;
    _t4106->col = _t4099;
    _t4106->is_param = _t4100;
    _t4106->is_own = _t4101;
    _t4106->is_ref = _t4102;
    _t4106->is_alias = _t4103;
    _t4106->is_type_alias = _t4104;
    _t4106->alias_target = self->alias_target;
    _t4106->struct_def = self->struct_def;
    _t4106->func_def = self->func_def;
    _t4106->is_builtin = _t4105;
    _t4106->is_ext = Bool_clone(&self->is_ext);
    _t4106->struct_name = self->struct_name;
    (void)_t4106;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    return _t4106;
}

void TypeBinding_delete(TypeBinding * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4107 = 0;
    (void)_t4107;
    TilType_delete(&self->type, &(Bool){_t4107});
    ;
    Bool _t4108 = 0;
    (void)_t4108;
    I32_delete(&self->is_proc, &(Bool){_t4108});
    ;
    Bool _t4109 = 0;
    (void)_t4109;
    Bool_delete(&self->is_mut, &(Bool){_t4109});
    ;
    Bool _t4110 = 0;
    (void)_t4110;
    U32_delete(&self->line, &(Bool){_t4110});
    ;
    Bool _t4111 = 0;
    (void)_t4111;
    U32_delete(&self->col, &(Bool){_t4111});
    ;
    Bool _t4112 = 0;
    (void)_t4112;
    Bool_delete(&self->is_param, &(Bool){_t4112});
    ;
    Bool _t4113 = 0;
    (void)_t4113;
    Bool_delete(&self->is_own, &(Bool){_t4113});
    ;
    Bool _t4114 = 0;
    (void)_t4114;
    Bool_delete(&self->is_ref, &(Bool){_t4114});
    ;
    Bool _t4115 = 0;
    (void)_t4115;
    Bool_delete(&self->is_alias, &(Bool){_t4115});
    ;
    Bool _t4116 = 0;
    (void)_t4116;
    Bool_delete(&self->is_type_alias, &(Bool){_t4116});
    ;
    Bool _t4117 = 0;
    (void)_t4117;
    Bool_delete(&self->is_builtin, &(Bool){_t4117});
    ;
    Bool _t4118 = 0;
    (void)_t4118;
    Bool_delete(&self->is_ext, &(Bool){_t4118});
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
    TypeScope *_t4120 = malloc(sizeof(TypeScope));
    { Map *_ca = Map_clone(&self->bindings); _t4120->bindings = *_ca; free(_ca); }
    _t4120->parent = self->parent;
    (void)_t4120;
    return _t4120;
}

void TypeScope_delete(TypeScope * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4121 = 0;
    (void)_t4121;
    Map_delete(&self->bindings, &(Bool){_t4121});
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

