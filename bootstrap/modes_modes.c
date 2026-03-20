#include "modes_modes.h"

Bool * Mode_eq(Mode * a, Mode * b) {
    (void)a;
    (void)b;
    Bool _t4123; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t4123 = *_hp; free(_hp); }
    (void)_t4123;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4123; return _r; }
}

Mode * Mode_clone(Mode * self) {
    (void)self;
    Bool _t4124 = Bool_clone(&self->needs_main);
    (void)_t4124;
    Bool _t4125 = Bool_clone(&self->decls_only);
    (void)_t4125;
    Bool _t4126 = Bool_clone(&self->is_pure);
    (void)_t4126;
    Bool _t4127 = Bool_clone(&self->debug_prints);
    (void)_t4127;
    Mode *_t4128 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(&self->name); _t4128->name = *_ca; free(_ca); }
    _t4128->needs_main = _t4124;
    _t4128->decls_only = _t4125;
    { Str *_ca = Str_clone(&self->auto_import); _t4128->auto_import = *_ca; free(_ca); }
    _t4128->is_pure = _t4126;
    _t4128->debug_prints = _t4127;
    (void)_t4128;
    ;
    ;
    ;
    ;
    return _t4128;
}

void Mode_delete(Mode * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4129 = 0;
    (void)_t4129;
    Str_delete(&self->name, &(Bool){_t4129});
    ;
    Bool _t4130 = 0;
    (void)_t4130;
    Bool_delete(&self->needs_main, &(Bool){_t4130});
    ;
    Bool _t4131 = 0;
    (void)_t4131;
    Bool_delete(&self->decls_only, &(Bool){_t4131});
    ;
    Bool _t4132 = 0;
    (void)_t4132;
    Str_delete(&self->auto_import, &(Bool){_t4132});
    ;
    Bool _t4133 = 0;
    (void)_t4133;
    Bool_delete(&self->is_pure, &(Bool){_t4133});
    ;
    Bool _t4134 = 0;
    (void)_t4134;
    Bool_delete(&self->debug_prints, &(Bool){_t4134});
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
    Str *_t4136 = Str_lit("lib", 3ULL);
    (void)_t4136;
    Str *_t4137 = Str_lit("liba", 4ULL);
    (void)_t4137;
    Bool _t4138; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4136); _t4138 = *_hp; free(_hp); }
    (void)_t4138;
    Str_delete(_t4136, &(Bool){1});
    Bool _t4139; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4137); _t4139 = *_hp; free(_hp); }
    (void)_t4139;
    Str_delete(_t4137, &(Bool){1});
    Bool _t4140 = Bool_or(_t4138, _t4139);
    (void)_t4140;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4140; return _r; }
}

Bool * mode_is_lib_output(Mode * m) {
    (void)m;
    Str *_t4141 = Str_lit("lib", 3ULL);
    (void)_t4141;
    Str *_t4142 = Str_lit("liba", 4ULL);
    (void)_t4142;
    Bool _t4143; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4141); _t4143 = *_hp; free(_hp); }
    (void)_t4143;
    Str_delete(_t4141, &(Bool){1});
    Bool _t4144; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4142); _t4144 = *_hp; free(_hp); }
    (void)_t4144;
    Str_delete(_t4142, &(Bool){1});
    Str *_t4145 = Str_lit("pure", 4ULL);
    (void)_t4145;
    Bool _t4146 = Bool_or(_t4143, _t4144);
    (void)_t4146;
    ;
    ;
    Bool _t4147; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4145); _t4147 = *_hp; free(_hp); }
    (void)_t4147;
    Str_delete(_t4145, &(Bool){1});
    Str *_t4148 = Str_lit("pura", 4ULL);
    (void)_t4148;
    Bool _t4149 = Bool_or(_t4146, _t4147);
    (void)_t4149;
    ;
    ;
    Bool _t4150; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4148); _t4150 = *_hp; free(_hp); }
    (void)_t4150;
    Str_delete(_t4148, &(Bool){1});
    Bool _t4151 = Bool_or(_t4149, _t4150);
    (void)_t4151;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4151; return _r; }
}

