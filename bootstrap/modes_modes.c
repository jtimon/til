#include "modes_modes.h"

Bool * Mode_eq(Mode * a, Mode * b) {
    (void)a;
    (void)b;
    Bool _t4220; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t4220 = *_hp; free(_hp); }
    (void)_t4220;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4220; return _r; }
}

Mode * Mode_clone(Mode * self) {
    (void)self;
    Bool _t4221 = Bool_clone(&self->needs_main);
    (void)_t4221;
    Bool _t4222 = Bool_clone(&self->decls_only);
    (void)_t4222;
    Bool _t4223 = Bool_clone(&self->is_pure);
    (void)_t4223;
    Bool _t4224 = Bool_clone(&self->debug_prints);
    (void)_t4224;
    Mode *_t4225 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(&self->name); _t4225->name = *_ca; free(_ca); }
    _t4225->needs_main = _t4221;
    _t4225->decls_only = _t4222;
    { Str *_ca = Str_clone(&self->auto_import); _t4225->auto_import = *_ca; free(_ca); }
    _t4225->is_pure = _t4223;
    _t4225->debug_prints = _t4224;
    (void)_t4225;
    ;
    ;
    ;
    ;
    return _t4225;
}

void Mode_delete(Mode * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4226 = 0;
    (void)_t4226;
    Str_delete(&self->name, &(Bool){_t4226});
    ;
    Bool _t4227 = 0;
    (void)_t4227;
    Bool_delete(&self->needs_main, &(Bool){_t4227});
    ;
    Bool _t4228 = 0;
    (void)_t4228;
    Bool_delete(&self->decls_only, &(Bool){_t4228});
    ;
    Bool _t4229 = 0;
    (void)_t4229;
    Str_delete(&self->auto_import, &(Bool){_t4229});
    ;
    Bool _t4230 = 0;
    (void)_t4230;
    Bool_delete(&self->is_pure, &(Bool){_t4230});
    ;
    Bool _t4231 = 0;
    (void)_t4231;
    Bool_delete(&self->debug_prints, &(Bool){_t4231});
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
    Str *_t4233 = Str_lit("lib", 3ULL);
    (void)_t4233;
    Str *_t4234 = Str_lit("liba", 4ULL);
    (void)_t4234;
    Bool _t4235; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4233); _t4235 = *_hp; free(_hp); }
    (void)_t4235;
    Str_delete(_t4233, &(Bool){1});
    Bool _t4236; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4234); _t4236 = *_hp; free(_hp); }
    (void)_t4236;
    Str_delete(_t4234, &(Bool){1});
    Bool _t4237 = Bool_or(_t4235, _t4236);
    (void)_t4237;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4237; return _r; }
}

Bool * mode_is_lib_output(Mode * m) {
    (void)m;
    Str *_t4238 = Str_lit("lib", 3ULL);
    (void)_t4238;
    Str *_t4239 = Str_lit("liba", 4ULL);
    (void)_t4239;
    Bool _t4240; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4238); _t4240 = *_hp; free(_hp); }
    (void)_t4240;
    Str_delete(_t4238, &(Bool){1});
    Bool _t4241; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4239); _t4241 = *_hp; free(_hp); }
    (void)_t4241;
    Str_delete(_t4239, &(Bool){1});
    Str *_t4242 = Str_lit("pure", 4ULL);
    (void)_t4242;
    Bool _t4243 = Bool_or(_t4240, _t4241);
    (void)_t4243;
    ;
    ;
    Bool _t4244; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4242); _t4244 = *_hp; free(_hp); }
    (void)_t4244;
    Str_delete(_t4242, &(Bool){1});
    Str *_t4245 = Str_lit("pura", 4ULL);
    (void)_t4245;
    Bool _t4246 = Bool_or(_t4243, _t4244);
    (void)_t4246;
    ;
    ;
    Bool _t4247; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4245); _t4247 = *_hp; free(_hp); }
    (void)_t4247;
    Str_delete(_t4245, &(Bool){1});
    Bool _t4248 = Bool_or(_t4246, _t4247);
    (void)_t4248;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4248; return _r; }
}

