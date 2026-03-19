#include "modes_modes.h"

Bool * Mode_eq(Mode * a, Mode * b) {
    (void)a;
    (void)b;
    Bool _t4187; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t4187 = *_hp; free(_hp); }
    (void)_t4187;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4187; return _r; }
}

Mode * Mode_clone(Mode * self) {
    (void)self;
    Bool _t4188 = Bool_clone(&self->needs_main);
    (void)_t4188;
    Bool _t4189 = Bool_clone(&self->decls_only);
    (void)_t4189;
    Bool _t4190 = Bool_clone(&self->is_pure);
    (void)_t4190;
    Bool _t4191 = Bool_clone(&self->debug_prints);
    (void)_t4191;
    Mode *_t4192 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(&self->name); _t4192->name = *_ca; free(_ca); }
    _t4192->needs_main = _t4188;
    _t4192->decls_only = _t4189;
    { Str *_ca = Str_clone(&self->auto_import); _t4192->auto_import = *_ca; free(_ca); }
    _t4192->is_pure = _t4190;
    _t4192->debug_prints = _t4191;
    (void)_t4192;
    ;
    ;
    ;
    ;
    return _t4192;
}

void Mode_delete(Mode * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4193 = 0;
    (void)_t4193;
    Str_delete(&self->name, &(Bool){_t4193});
    ;
    Bool _t4194 = 0;
    (void)_t4194;
    Bool_delete(&self->needs_main, &(Bool){_t4194});
    ;
    Bool _t4195 = 0;
    (void)_t4195;
    Bool_delete(&self->decls_only, &(Bool){_t4195});
    ;
    Bool _t4196 = 0;
    (void)_t4196;
    Str_delete(&self->auto_import, &(Bool){_t4196});
    ;
    Bool _t4197 = 0;
    (void)_t4197;
    Bool_delete(&self->is_pure, &(Bool){_t4197});
    ;
    Bool _t4198 = 0;
    (void)_t4198;
    Bool_delete(&self->debug_prints, &(Bool){_t4198});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *Mode_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Mode);
    return r;
}

Mode * mode_resolve(Str * name) {
    (void)name;
    Mode *m = Map_get(core_modes, name);
    (void)m;
    return m;
}

Bool * mode_is_lib(Mode * m) {
    (void)m;
    Str *_t4200 = Str_lit("lib", 3ULL);
    (void)_t4200;
    Str *_t4201 = Str_lit("liba", 4ULL);
    (void)_t4201;
    Bool _t4202; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4200); _t4202 = *_hp; free(_hp); }
    (void)_t4202;
    Str_delete(_t4200, &(Bool){1});
    Bool _t4203; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4201); _t4203 = *_hp; free(_hp); }
    (void)_t4203;
    Str_delete(_t4201, &(Bool){1});
    Bool _t4204 = Bool_or(_t4202, _t4203);
    (void)_t4204;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4204; return _r; }
}

Bool * mode_is_lib_output(Mode * m) {
    (void)m;
    Str *_t4205 = Str_lit("lib", 3ULL);
    (void)_t4205;
    Str *_t4206 = Str_lit("liba", 4ULL);
    (void)_t4206;
    Bool _t4207; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4205); _t4207 = *_hp; free(_hp); }
    (void)_t4207;
    Str_delete(_t4205, &(Bool){1});
    Bool _t4208; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4206); _t4208 = *_hp; free(_hp); }
    (void)_t4208;
    Str_delete(_t4206, &(Bool){1});
    Str *_t4209 = Str_lit("pure", 4ULL);
    (void)_t4209;
    Bool _t4210 = Bool_or(_t4207, _t4208);
    (void)_t4210;
    ;
    ;
    Bool _t4211; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4209); _t4211 = *_hp; free(_hp); }
    (void)_t4211;
    Str_delete(_t4209, &(Bool){1});
    Str *_t4212 = Str_lit("pura", 4ULL);
    (void)_t4212;
    Bool _t4213 = Bool_or(_t4210, _t4211);
    (void)_t4213;
    ;
    ;
    Bool _t4214; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4212); _t4214 = *_hp; free(_hp); }
    (void)_t4214;
    Str_delete(_t4212, &(Bool){1});
    Bool _t4215 = Bool_or(_t4213, _t4214);
    (void)_t4215;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4215; return _r; }
}

