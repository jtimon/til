#include "til_modes.h"

Bool * Mode_eq(Mode * a, Mode * b) {
    (void)a;
    (void)b;
    Bool _t4198; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t4198 = *_hp; free(_hp); }
    (void)_t4198;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4198; return _r; }
}

Mode * Mode_clone(Mode * self) {
    (void)self;
    Bool _t4199 = Bool_clone(&self->needs_main);
    (void)_t4199;
    Bool _t4200 = Bool_clone(&self->decls_only);
    (void)_t4200;
    Bool _t4201 = Bool_clone(&self->is_pure);
    (void)_t4201;
    Bool _t4202 = Bool_clone(&self->debug_prints);
    (void)_t4202;
    Mode *_t4203 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(&self->name); _t4203->name = *_ca; free(_ca); }
    _t4203->needs_main = _t4199;
    _t4203->decls_only = _t4200;
    { Str *_ca = Str_clone(&self->auto_import); _t4203->auto_import = *_ca; free(_ca); }
    _t4203->is_pure = _t4201;
    _t4203->debug_prints = _t4202;
    (void)_t4203;
    ;
    ;
    ;
    ;
    return _t4203;
}

void Mode_delete(Mode * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4204 = 0;
    (void)_t4204;
    Str_delete(&self->name, &(Bool){_t4204});
    ;
    Bool _t4205 = 0;
    (void)_t4205;
    Bool_delete(&self->needs_main, &(Bool){_t4205});
    ;
    Bool _t4206 = 0;
    (void)_t4206;
    Bool_delete(&self->decls_only, &(Bool){_t4206});
    ;
    Bool _t4207 = 0;
    (void)_t4207;
    Str_delete(&self->auto_import, &(Bool){_t4207});
    ;
    Bool _t4208 = 0;
    (void)_t4208;
    Bool_delete(&self->is_pure, &(Bool){_t4208});
    ;
    Bool _t4209 = 0;
    (void)_t4209;
    Bool_delete(&self->debug_prints, &(Bool){_t4209});
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
    Str *_t4211 = Str_lit("lib", 3ULL);
    (void)_t4211;
    Str *_t4212 = Str_lit("liba", 4ULL);
    (void)_t4212;
    Bool _t4213; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4211); _t4213 = *_hp; free(_hp); }
    (void)_t4213;
    Str_delete(_t4211, &(Bool){1});
    Bool _t4214; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4212); _t4214 = *_hp; free(_hp); }
    (void)_t4214;
    Str_delete(_t4212, &(Bool){1});
    Bool _t4215 = Bool_or(_t4213, _t4214);
    (void)_t4215;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4215; return _r; }
}

Bool * mode_is_lib_output(Mode * m) {
    (void)m;
    Str *_t4216 = Str_lit("lib", 3ULL);
    (void)_t4216;
    Str *_t4217 = Str_lit("liba", 4ULL);
    (void)_t4217;
    Bool _t4218; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4216); _t4218 = *_hp; free(_hp); }
    (void)_t4218;
    Str_delete(_t4216, &(Bool){1});
    Bool _t4219; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4217); _t4219 = *_hp; free(_hp); }
    (void)_t4219;
    Str_delete(_t4217, &(Bool){1});
    Str *_t4220 = Str_lit("pure", 4ULL);
    (void)_t4220;
    Bool _t4221 = Bool_or(_t4218, _t4219);
    (void)_t4221;
    ;
    ;
    Bool _t4222; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4220); _t4222 = *_hp; free(_hp); }
    (void)_t4222;
    Str_delete(_t4220, &(Bool){1});
    Str *_t4223 = Str_lit("pura", 4ULL);
    (void)_t4223;
    Bool _t4224 = Bool_or(_t4221, _t4222);
    (void)_t4224;
    ;
    ;
    Bool _t4225; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4223); _t4225 = *_hp; free(_hp); }
    (void)_t4225;
    Str_delete(_t4223, &(Bool){1});
    Bool _t4226 = Bool_or(_t4224, _t4225);
    (void)_t4226;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4226; return _r; }
}

