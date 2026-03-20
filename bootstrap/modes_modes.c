#include "modes_modes.h"

Bool * Mode_eq(Mode * a, Mode * b) {
    (void)a;
    (void)b;
    Bool _t4106; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t4106 = *_hp; free(_hp); }
    (void)_t4106;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4106; return _r; }
}

Mode * Mode_clone(Mode * self) {
    (void)self;
    Bool _t4107 = Bool_clone(&self->needs_main);
    (void)_t4107;
    Bool _t4108 = Bool_clone(&self->decls_only);
    (void)_t4108;
    Bool _t4109 = Bool_clone(&self->is_pure);
    (void)_t4109;
    Bool _t4110 = Bool_clone(&self->debug_prints);
    (void)_t4110;
    Mode *_t4111 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(&self->name); _t4111->name = *_ca; free(_ca); }
    _t4111->needs_main = _t4107;
    _t4111->decls_only = _t4108;
    { Str *_ca = Str_clone(&self->auto_import); _t4111->auto_import = *_ca; free(_ca); }
    _t4111->is_pure = _t4109;
    _t4111->debug_prints = _t4110;
    (void)_t4111;
    ;
    ;
    ;
    ;
    return _t4111;
}

void Mode_delete(Mode * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4112 = 0;
    (void)_t4112;
    Str_delete(&self->name, &(Bool){_t4112});
    ;
    Bool _t4113 = 0;
    (void)_t4113;
    Bool_delete(&self->needs_main, &(Bool){_t4113});
    ;
    Bool _t4114 = 0;
    (void)_t4114;
    Bool_delete(&self->decls_only, &(Bool){_t4114});
    ;
    Bool _t4115 = 0;
    (void)_t4115;
    Str_delete(&self->auto_import, &(Bool){_t4115});
    ;
    Bool _t4116 = 0;
    (void)_t4116;
    Bool_delete(&self->is_pure, &(Bool){_t4116});
    ;
    Bool _t4117 = 0;
    (void)_t4117;
    Bool_delete(&self->debug_prints, &(Bool){_t4117});
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
    Str *_t4119 = Str_lit("lib", 3ULL);
    (void)_t4119;
    Str *_t4120 = Str_lit("liba", 4ULL);
    (void)_t4120;
    Bool _t4121; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4119); _t4121 = *_hp; free(_hp); }
    (void)_t4121;
    Str_delete(_t4119, &(Bool){1});
    Bool _t4122; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4120); _t4122 = *_hp; free(_hp); }
    (void)_t4122;
    Str_delete(_t4120, &(Bool){1});
    Bool _t4123 = Bool_or(_t4121, _t4122);
    (void)_t4123;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4123; return _r; }
}

Bool * mode_is_lib_output(Mode * m) {
    (void)m;
    Str *_t4124 = Str_lit("lib", 3ULL);
    (void)_t4124;
    Str *_t4125 = Str_lit("liba", 4ULL);
    (void)_t4125;
    Bool _t4126; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4124); _t4126 = *_hp; free(_hp); }
    (void)_t4126;
    Str_delete(_t4124, &(Bool){1});
    Bool _t4127; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4125); _t4127 = *_hp; free(_hp); }
    (void)_t4127;
    Str_delete(_t4125, &(Bool){1});
    Str *_t4128 = Str_lit("pure", 4ULL);
    (void)_t4128;
    Bool _t4129 = Bool_or(_t4126, _t4127);
    (void)_t4129;
    ;
    ;
    Bool _t4130; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4128); _t4130 = *_hp; free(_hp); }
    (void)_t4130;
    Str_delete(_t4128, &(Bool){1});
    Str *_t4131 = Str_lit("pura", 4ULL);
    (void)_t4131;
    Bool _t4132 = Bool_or(_t4129, _t4130);
    (void)_t4132;
    ;
    ;
    Bool _t4133; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4131); _t4133 = *_hp; free(_hp); }
    (void)_t4133;
    Str_delete(_t4131, &(Bool){1});
    Bool _t4134 = Bool_or(_t4132, _t4133);
    (void)_t4134;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4134; return _r; }
}

