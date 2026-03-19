#include "modes_modes.h"

Bool * Mode_eq(Mode * a, Mode * b) {
    (void)a;
    (void)b;
    Bool _t4195; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t4195 = *_hp; free(_hp); }
    (void)_t4195;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4195; return _r; }
}

Mode * Mode_clone(Mode * self) {
    (void)self;
    Bool _t4196 = Bool_clone(&self->needs_main);
    (void)_t4196;
    Bool _t4197 = Bool_clone(&self->decls_only);
    (void)_t4197;
    Bool _t4198 = Bool_clone(&self->is_pure);
    (void)_t4198;
    Bool _t4199 = Bool_clone(&self->debug_prints);
    (void)_t4199;
    Mode *_t4200 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(&self->name); _t4200->name = *_ca; free(_ca); }
    _t4200->needs_main = _t4196;
    _t4200->decls_only = _t4197;
    { Str *_ca = Str_clone(&self->auto_import); _t4200->auto_import = *_ca; free(_ca); }
    _t4200->is_pure = _t4198;
    _t4200->debug_prints = _t4199;
    (void)_t4200;
    ;
    ;
    ;
    ;
    return _t4200;
}

void Mode_delete(Mode * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4201 = 0;
    (void)_t4201;
    Str_delete(&self->name, &(Bool){_t4201});
    ;
    Bool _t4202 = 0;
    (void)_t4202;
    Bool_delete(&self->needs_main, &(Bool){_t4202});
    ;
    Bool _t4203 = 0;
    (void)_t4203;
    Bool_delete(&self->decls_only, &(Bool){_t4203});
    ;
    Bool _t4204 = 0;
    (void)_t4204;
    Str_delete(&self->auto_import, &(Bool){_t4204});
    ;
    Bool _t4205 = 0;
    (void)_t4205;
    Bool_delete(&self->is_pure, &(Bool){_t4205});
    ;
    Bool _t4206 = 0;
    (void)_t4206;
    Bool_delete(&self->debug_prints, &(Bool){_t4206});
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
    Str *_t4208 = Str_lit("lib", 3ULL);
    (void)_t4208;
    Str *_t4209 = Str_lit("liba", 4ULL);
    (void)_t4209;
    Bool _t4210; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4208); _t4210 = *_hp; free(_hp); }
    (void)_t4210;
    Str_delete(_t4208, &(Bool){1});
    Bool _t4211; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4209); _t4211 = *_hp; free(_hp); }
    (void)_t4211;
    Str_delete(_t4209, &(Bool){1});
    Bool _t4212 = Bool_or(_t4210, _t4211);
    (void)_t4212;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4212; return _r; }
}

Bool * mode_is_lib_output(Mode * m) {
    (void)m;
    Str *_t4213 = Str_lit("lib", 3ULL);
    (void)_t4213;
    Str *_t4214 = Str_lit("liba", 4ULL);
    (void)_t4214;
    Bool _t4215; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4213); _t4215 = *_hp; free(_hp); }
    (void)_t4215;
    Str_delete(_t4213, &(Bool){1});
    Bool _t4216; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4214); _t4216 = *_hp; free(_hp); }
    (void)_t4216;
    Str_delete(_t4214, &(Bool){1});
    Str *_t4217 = Str_lit("pure", 4ULL);
    (void)_t4217;
    Bool _t4218 = Bool_or(_t4215, _t4216);
    (void)_t4218;
    ;
    ;
    Bool _t4219; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4217); _t4219 = *_hp; free(_hp); }
    (void)_t4219;
    Str_delete(_t4217, &(Bool){1});
    Str *_t4220 = Str_lit("pura", 4ULL);
    (void)_t4220;
    Bool _t4221 = Bool_or(_t4218, _t4219);
    (void)_t4221;
    ;
    ;
    Bool _t4222; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4220); _t4222 = *_hp; free(_hp); }
    (void)_t4222;
    Str_delete(_t4220, &(Bool){1});
    Bool _t4223 = Bool_or(_t4221, _t4222);
    (void)_t4223;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4223; return _r; }
}

