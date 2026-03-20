#include "modes_modes.h"

Bool * Mode_eq(Mode * a, Mode * b) {
    (void)a;
    (void)b;
    Bool _t4133; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t4133 = *_hp; free(_hp); }
    (void)_t4133;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4133; return _r; }
}

Mode * Mode_clone(Mode * self) {
    (void)self;
    Bool _t4134 = Bool_clone(&self->needs_main);
    (void)_t4134;
    Bool _t4135 = Bool_clone(&self->decls_only);
    (void)_t4135;
    Bool _t4136 = Bool_clone(&self->is_pure);
    (void)_t4136;
    Bool _t4137 = Bool_clone(&self->debug_prints);
    (void)_t4137;
    Mode *_t4138 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(&self->name); _t4138->name = *_ca; free(_ca); }
    _t4138->needs_main = _t4134;
    _t4138->decls_only = _t4135;
    { Str *_ca = Str_clone(&self->auto_import); _t4138->auto_import = *_ca; free(_ca); }
    _t4138->is_pure = _t4136;
    _t4138->debug_prints = _t4137;
    (void)_t4138;
    ;
    ;
    ;
    ;
    return _t4138;
}

void Mode_delete(Mode * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4139 = 0;
    (void)_t4139;
    Str_delete(&self->name, &(Bool){_t4139});
    ;
    Bool _t4140 = 0;
    (void)_t4140;
    Bool_delete(&self->needs_main, &(Bool){_t4140});
    ;
    Bool _t4141 = 0;
    (void)_t4141;
    Bool_delete(&self->decls_only, &(Bool){_t4141});
    ;
    Bool _t4142 = 0;
    (void)_t4142;
    Str_delete(&self->auto_import, &(Bool){_t4142});
    ;
    Bool _t4143 = 0;
    (void)_t4143;
    Bool_delete(&self->is_pure, &(Bool){_t4143});
    ;
    Bool _t4144 = 0;
    (void)_t4144;
    Bool_delete(&self->debug_prints, &(Bool){_t4144});
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
    Str *_t4146 = Str_lit("lib", 3ULL);
    (void)_t4146;
    Str *_t4147 = Str_lit("liba", 4ULL);
    (void)_t4147;
    Bool _t4148; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4146); _t4148 = *_hp; free(_hp); }
    (void)_t4148;
    Str_delete(_t4146, &(Bool){1});
    Bool _t4149; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4147); _t4149 = *_hp; free(_hp); }
    (void)_t4149;
    Str_delete(_t4147, &(Bool){1});
    Bool _t4150 = Bool_or(_t4148, _t4149);
    (void)_t4150;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4150; return _r; }
}

Bool * mode_is_lib_output(Mode * m) {
    (void)m;
    Str *_t4151 = Str_lit("lib", 3ULL);
    (void)_t4151;
    Str *_t4152 = Str_lit("liba", 4ULL);
    (void)_t4152;
    Bool _t4153; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4151); _t4153 = *_hp; free(_hp); }
    (void)_t4153;
    Str_delete(_t4151, &(Bool){1});
    Bool _t4154; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4152); _t4154 = *_hp; free(_hp); }
    (void)_t4154;
    Str_delete(_t4152, &(Bool){1});
    Str *_t4155 = Str_lit("pure", 4ULL);
    (void)_t4155;
    Bool _t4156 = Bool_or(_t4153, _t4154);
    (void)_t4156;
    ;
    ;
    Bool _t4157; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4155); _t4157 = *_hp; free(_hp); }
    (void)_t4157;
    Str_delete(_t4155, &(Bool){1});
    Str *_t4158 = Str_lit("pura", 4ULL);
    (void)_t4158;
    Bool _t4159 = Bool_or(_t4156, _t4157);
    (void)_t4159;
    ;
    ;
    Bool _t4160; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4158); _t4160 = *_hp; free(_hp); }
    (void)_t4160;
    Str_delete(_t4158, &(Bool){1});
    Bool _t4161 = Bool_or(_t4159, _t4160);
    (void)_t4161;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4161; return _r; }
}

