#include "til_modes.h"

Bool * Mode_eq(Mode * a, Mode * b) {
    (void)a;
    (void)b;
    Bool _t4238; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t4238 = *_hp; free(_hp); }
    (void)_t4238;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4238; return _r; }
}

Mode * Mode_clone(Mode * self) {
    (void)self;
    Bool _t4239 = Bool_clone(&self->needs_main);
    (void)_t4239;
    Bool _t4240 = Bool_clone(&self->decls_only);
    (void)_t4240;
    Bool _t4241 = Bool_clone(&self->is_pure);
    (void)_t4241;
    Bool _t4242 = Bool_clone(&self->debug_prints);
    (void)_t4242;
    Mode *_t4243 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(&self->name); _t4243->name = *_ca; free(_ca); }
    _t4243->needs_main = _t4239;
    _t4243->decls_only = _t4240;
    { Str *_ca = Str_clone(&self->auto_import); _t4243->auto_import = *_ca; free(_ca); }
    _t4243->is_pure = _t4241;
    _t4243->debug_prints = _t4242;
    (void)_t4243;
    ;
    ;
    ;
    ;
    return _t4243;
}

void Mode_delete(Mode * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4244 = 0;
    (void)_t4244;
    Str_delete(&self->name, &(Bool){_t4244});
    ;
    Bool _t4245 = 0;
    (void)_t4245;
    Bool_delete(&self->needs_main, &(Bool){_t4245});
    ;
    Bool _t4246 = 0;
    (void)_t4246;
    Bool_delete(&self->decls_only, &(Bool){_t4246});
    ;
    Bool _t4247 = 0;
    (void)_t4247;
    Str_delete(&self->auto_import, &(Bool){_t4247});
    ;
    Bool _t4248 = 0;
    (void)_t4248;
    Bool_delete(&self->is_pure, &(Bool){_t4248});
    ;
    Bool _t4249 = 0;
    (void)_t4249;
    Bool_delete(&self->debug_prints, &(Bool){_t4249});
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
    Str *_t4251 = Str_lit("lib", 3ULL);
    (void)_t4251;
    Str *_t4252 = Str_lit("liba", 4ULL);
    (void)_t4252;
    Bool _t4253; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4251); _t4253 = *_hp; free(_hp); }
    (void)_t4253;
    Str_delete(_t4251, &(Bool){1});
    Bool _t4254; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4252); _t4254 = *_hp; free(_hp); }
    (void)_t4254;
    Str_delete(_t4252, &(Bool){1});
    Bool _t4255 = Bool_or(_t4253, _t4254);
    (void)_t4255;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4255; return _r; }
}

Bool * mode_is_lib_output(Mode * m) {
    (void)m;
    Str *_t4256 = Str_lit("lib", 3ULL);
    (void)_t4256;
    Str *_t4257 = Str_lit("liba", 4ULL);
    (void)_t4257;
    Bool _t4258; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4256); _t4258 = *_hp; free(_hp); }
    (void)_t4258;
    Str_delete(_t4256, &(Bool){1});
    Bool _t4259; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4257); _t4259 = *_hp; free(_hp); }
    (void)_t4259;
    Str_delete(_t4257, &(Bool){1});
    Str *_t4260 = Str_lit("pure", 4ULL);
    (void)_t4260;
    Bool _t4261 = Bool_or(_t4258, _t4259);
    (void)_t4261;
    ;
    ;
    Bool _t4262; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4260); _t4262 = *_hp; free(_hp); }
    (void)_t4262;
    Str_delete(_t4260, &(Bool){1});
    Str *_t4263 = Str_lit("pura", 4ULL);
    (void)_t4263;
    Bool _t4264 = Bool_or(_t4261, _t4262);
    (void)_t4264;
    ;
    ;
    Bool _t4265; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4263); _t4265 = *_hp; free(_hp); }
    (void)_t4265;
    Str_delete(_t4263, &(Bool){1});
    Bool _t4266 = Bool_or(_t4264, _t4265);
    (void)_t4266;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4266; return _r; }
}

