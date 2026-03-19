#include "til_initer.h"

TypeBinding * TypeBinding_clone(TypeBinding * self) {
    (void)self;
    Bool _t4174 = Bool_clone(&self->is_mut);
    (void)_t4174;
    U32 _t4175 = U32_clone(&self->line);
    (void)_t4175;
    U32 _t4176 = U32_clone(&self->col);
    (void)_t4176;
    Bool _t4177 = Bool_clone(&self->is_param);
    (void)_t4177;
    Bool _t4178 = Bool_clone(&self->is_own);
    (void)_t4178;
    Bool _t4179 = Bool_clone(&self->is_ref);
    (void)_t4179;
    Bool _t4180 = Bool_clone(&self->is_alias);
    (void)_t4180;
    Bool _t4181 = Bool_clone(&self->is_builtin);
    (void)_t4181;
    TypeBinding *_t4182 = malloc(sizeof(TypeBinding));
    _t4182->name = self->name;
    { TilType *_ca = TilType_clone(&self->type); _t4182->type = *_ca; free(_ca); }
    _t4182->is_proc = I32_clone(&self->is_proc);
    _t4182->is_mut = _t4174;
    _t4182->line = _t4175;
    _t4182->col = _t4176;
    _t4182->is_param = _t4177;
    _t4182->is_own = _t4178;
    _t4182->is_ref = _t4179;
    _t4182->is_alias = _t4180;
    _t4182->struct_def = self->struct_def;
    _t4182->func_def = self->func_def;
    _t4182->is_builtin = _t4181;
    _t4182->is_ext = Bool_clone(&self->is_ext);
    _t4182->struct_name = self->struct_name;
    (void)_t4182;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    return _t4182;
}

void TypeBinding_delete(TypeBinding * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4183 = 0;
    (void)_t4183;
    TilType_delete(&self->type, &(Bool){_t4183});
    ;
    Bool _t4184 = 0;
    (void)_t4184;
    I32_delete(&self->is_proc, &(Bool){_t4184});
    ;
    Bool _t4185 = 0;
    (void)_t4185;
    Bool_delete(&self->is_mut, &(Bool){_t4185});
    ;
    Bool _t4186 = 0;
    (void)_t4186;
    U32_delete(&self->line, &(Bool){_t4186});
    ;
    Bool _t4187 = 0;
    (void)_t4187;
    U32_delete(&self->col, &(Bool){_t4187});
    ;
    Bool _t4188 = 0;
    (void)_t4188;
    Bool_delete(&self->is_param, &(Bool){_t4188});
    ;
    Bool _t4189 = 0;
    (void)_t4189;
    Bool_delete(&self->is_own, &(Bool){_t4189});
    ;
    Bool _t4190 = 0;
    (void)_t4190;
    Bool_delete(&self->is_ref, &(Bool){_t4190});
    ;
    Bool _t4191 = 0;
    (void)_t4191;
    Bool_delete(&self->is_alias, &(Bool){_t4191});
    ;
    Bool _t4192 = 0;
    (void)_t4192;
    Bool_delete(&self->is_builtin, &(Bool){_t4192});
    ;
    Bool _t4193 = 0;
    (void)_t4193;
    Bool_delete(&self->is_ext, &(Bool){_t4193});
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
    TypeScope *_t4195 = malloc(sizeof(TypeScope));
    { Map *_ca = Map_clone(&self->bindings); _t4195->bindings = *_ca; free(_ca); }
    _t4195->parent = self->parent;
    (void)_t4195;
    return _t4195;
}

void TypeScope_delete(TypeScope * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4196 = 0;
    (void)_t4196;
    Map_delete(&self->bindings, &(Bool){_t4196});
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

