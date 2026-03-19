#include "til_modes.h"

Bool * Mode_eq(Mode * a, Mode * b) {
    (void)a;
    (void)b;
    Bool _t4222; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t4222 = *_hp; free(_hp); }
    (void)_t4222;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4222; return _r; }
}

Mode * Mode_clone(Mode * self) {
    (void)self;
    Bool _t4223 = Bool_clone(&self->needs_main);
    (void)_t4223;
    Bool _t4224 = Bool_clone(&self->decls_only);
    (void)_t4224;
    Bool _t4225 = Bool_clone(&self->is_pure);
    (void)_t4225;
    Bool _t4226 = Bool_clone(&self->debug_prints);
    (void)_t4226;
    Mode *_t4227 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(&self->name); _t4227->name = *_ca; free(_ca); }
    _t4227->needs_main = _t4223;
    _t4227->decls_only = _t4224;
    { Str *_ca = Str_clone(&self->auto_import); _t4227->auto_import = *_ca; free(_ca); }
    _t4227->is_pure = _t4225;
    _t4227->debug_prints = _t4226;
    (void)_t4227;
    ;
    ;
    ;
    ;
    return _t4227;
}

void Mode_delete(Mode * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4228 = 0;
    (void)_t4228;
    Str_delete(&self->name, &(Bool){_t4228});
    ;
    Bool _t4229 = 0;
    (void)_t4229;
    Bool_delete(&self->needs_main, &(Bool){_t4229});
    ;
    Bool _t4230 = 0;
    (void)_t4230;
    Bool_delete(&self->decls_only, &(Bool){_t4230});
    ;
    Bool _t4231 = 0;
    (void)_t4231;
    Str_delete(&self->auto_import, &(Bool){_t4231});
    ;
    Bool _t4232 = 0;
    (void)_t4232;
    Bool_delete(&self->is_pure, &(Bool){_t4232});
    ;
    Bool _t4233 = 0;
    (void)_t4233;
    Bool_delete(&self->debug_prints, &(Bool){_t4233});
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
    Str *_t4235 = Str_lit("lib", 3ULL);
    (void)_t4235;
    Str *_t4236 = Str_lit("liba", 4ULL);
    (void)_t4236;
    Bool _t4237; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4235); _t4237 = *_hp; free(_hp); }
    (void)_t4237;
    Str_delete(_t4235, &(Bool){1});
    Bool _t4238; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4236); _t4238 = *_hp; free(_hp); }
    (void)_t4238;
    Str_delete(_t4236, &(Bool){1});
    Bool _t4239 = Bool_or(_t4237, _t4238);
    (void)_t4239;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4239; return _r; }
}

Bool * mode_is_lib_output(Mode * m) {
    (void)m;
    Str *_t4240 = Str_lit("lib", 3ULL);
    (void)_t4240;
    Str *_t4241 = Str_lit("liba", 4ULL);
    (void)_t4241;
    Bool _t4242; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4240); _t4242 = *_hp; free(_hp); }
    (void)_t4242;
    Str_delete(_t4240, &(Bool){1});
    Bool _t4243; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4241); _t4243 = *_hp; free(_hp); }
    (void)_t4243;
    Str_delete(_t4241, &(Bool){1});
    Str *_t4244 = Str_lit("pure", 4ULL);
    (void)_t4244;
    Bool _t4245 = Bool_or(_t4242, _t4243);
    (void)_t4245;
    ;
    ;
    Bool _t4246; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4244); _t4246 = *_hp; free(_hp); }
    (void)_t4246;
    Str_delete(_t4244, &(Bool){1});
    Str *_t4247 = Str_lit("pura", 4ULL);
    (void)_t4247;
    Bool _t4248 = Bool_or(_t4245, _t4246);
    (void)_t4248;
    ;
    ;
    Bool _t4249; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4247); _t4249 = *_hp; free(_hp); }
    (void)_t4249;
    Str_delete(_t4247, &(Bool){1});
    Bool _t4250 = Bool_or(_t4248, _t4249);
    (void)_t4250;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4250; return _r; }
}

