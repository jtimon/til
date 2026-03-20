#include "modes_initer.h"

TypeBinding * TypeBinding_clone(TypeBinding * self) {
    (void)self;
    Bool _t4212 = Bool_clone(&self->is_mut);
    (void)_t4212;
    U32 _t4213 = U32_clone(&self->line);
    (void)_t4213;
    U32 _t4214 = U32_clone(&self->col);
    (void)_t4214;
    Bool _t4215 = Bool_clone(&self->is_param);
    (void)_t4215;
    Bool _t4216 = Bool_clone(&self->is_own);
    (void)_t4216;
    Bool _t4217 = Bool_clone(&self->is_ref);
    (void)_t4217;
    Bool _t4218 = Bool_clone(&self->is_alias);
    (void)_t4218;
    Bool _t4219 = Bool_clone(&self->is_type_alias);
    (void)_t4219;
    Bool _t4220 = Bool_clone(&self->is_builtin);
    (void)_t4220;
    TypeBinding *_t4221 = malloc(sizeof(TypeBinding));
    _t4221->name = self->name;
    { TilType *_ca = TilType_clone(&self->type); _t4221->type = *_ca; free(_ca); }
    _t4221->is_proc = I32_clone(&self->is_proc);
    _t4221->is_mut = _t4212;
    _t4221->line = _t4213;
    _t4221->col = _t4214;
    _t4221->is_param = _t4215;
    _t4221->is_own = _t4216;
    _t4221->is_ref = _t4217;
    _t4221->is_alias = _t4218;
    _t4221->is_type_alias = _t4219;
    _t4221->alias_target = self->alias_target;
    _t4221->struct_def = self->struct_def;
    _t4221->func_def = self->func_def;
    _t4221->is_builtin = _t4220;
    _t4221->is_ext = Bool_clone(&self->is_ext);
    _t4221->struct_name = self->struct_name;
    (void)_t4221;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    return _t4221;
}

void TypeBinding_delete(TypeBinding * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4222 = 0;
    (void)_t4222;
    TilType_delete(&self->type, &(Bool){_t4222});
    ;
    Bool _t4223 = 0;
    (void)_t4223;
    I32_delete(&self->is_proc, &(Bool){_t4223});
    ;
    Bool _t4224 = 0;
    (void)_t4224;
    Bool_delete(&self->is_mut, &(Bool){_t4224});
    ;
    Bool _t4225 = 0;
    (void)_t4225;
    U32_delete(&self->line, &(Bool){_t4225});
    ;
    Bool _t4226 = 0;
    (void)_t4226;
    U32_delete(&self->col, &(Bool){_t4226});
    ;
    Bool _t4227 = 0;
    (void)_t4227;
    Bool_delete(&self->is_param, &(Bool){_t4227});
    ;
    Bool _t4228 = 0;
    (void)_t4228;
    Bool_delete(&self->is_own, &(Bool){_t4228});
    ;
    Bool _t4229 = 0;
    (void)_t4229;
    Bool_delete(&self->is_ref, &(Bool){_t4229});
    ;
    Bool _t4230 = 0;
    (void)_t4230;
    Bool_delete(&self->is_alias, &(Bool){_t4230});
    ;
    Bool _t4231 = 0;
    (void)_t4231;
    Bool_delete(&self->is_type_alias, &(Bool){_t4231});
    ;
    Bool _t4232 = 0;
    (void)_t4232;
    Bool_delete(&self->is_builtin, &(Bool){_t4232});
    ;
    Bool _t4233 = 0;
    (void)_t4233;
    Bool_delete(&self->is_ext, &(Bool){_t4233});
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
    TypeScope *_t4235 = malloc(sizeof(TypeScope));
    { Map *_ca = Map_clone(&self->bindings); _t4235->bindings = *_ca; free(_ca); }
    _t4235->parent = self->parent;
    (void)_t4235;
    return _t4235;
}

void TypeScope_delete(TypeScope * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4236 = 0;
    (void)_t4236;
    Map_delete(&self->bindings, &(Bool){_t4236});
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

