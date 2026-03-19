#include "modes_modes.h"

Bool * Mode_eq(Mode * a, Mode * b) {
    (void)a;
    (void)b;
    Bool _t4174; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t4174 = *_hp; free(_hp); }
    (void)_t4174;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4174; return _r; }
}

Mode * Mode_clone(Mode * self) {
    (void)self;
    Bool _t4175 = Bool_clone(&self->needs_main);
    (void)_t4175;
    Bool _t4176 = Bool_clone(&self->decls_only);
    (void)_t4176;
    Bool _t4177 = Bool_clone(&self->is_pure);
    (void)_t4177;
    Bool _t4178 = Bool_clone(&self->debug_prints);
    (void)_t4178;
    Mode *_t4179 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(&self->name); _t4179->name = *_ca; free(_ca); }
    _t4179->needs_main = _t4175;
    _t4179->decls_only = _t4176;
    { Str *_ca = Str_clone(&self->auto_import); _t4179->auto_import = *_ca; free(_ca); }
    _t4179->is_pure = _t4177;
    _t4179->debug_prints = _t4178;
    (void)_t4179;
    ;
    ;
    ;
    ;
    return _t4179;
}

void Mode_delete(Mode * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4180 = 0;
    (void)_t4180;
    Str_delete(&self->name, &(Bool){_t4180});
    ;
    Bool _t4181 = 0;
    (void)_t4181;
    Bool_delete(&self->needs_main, &(Bool){_t4181});
    ;
    Bool _t4182 = 0;
    (void)_t4182;
    Bool_delete(&self->decls_only, &(Bool){_t4182});
    ;
    Bool _t4183 = 0;
    (void)_t4183;
    Str_delete(&self->auto_import, &(Bool){_t4183});
    ;
    Bool _t4184 = 0;
    (void)_t4184;
    Bool_delete(&self->is_pure, &(Bool){_t4184});
    ;
    Bool _t4185 = 0;
    (void)_t4185;
    Bool_delete(&self->debug_prints, &(Bool){_t4185});
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
    Str *_t4187 = Str_lit("lib", 3ULL);
    (void)_t4187;
    Str *_t4188 = Str_lit("liba", 4ULL);
    (void)_t4188;
    Bool _t4189; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4187); _t4189 = *_hp; free(_hp); }
    (void)_t4189;
    Str_delete(_t4187, &(Bool){1});
    Bool _t4190; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4188); _t4190 = *_hp; free(_hp); }
    (void)_t4190;
    Str_delete(_t4188, &(Bool){1});
    Bool _t4191 = Bool_or(_t4189, _t4190);
    (void)_t4191;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4191; return _r; }
}

Bool * mode_is_lib_output(Mode * m) {
    (void)m;
    Str *_t4192 = Str_lit("lib", 3ULL);
    (void)_t4192;
    Str *_t4193 = Str_lit("liba", 4ULL);
    (void)_t4193;
    Bool _t4194; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4192); _t4194 = *_hp; free(_hp); }
    (void)_t4194;
    Str_delete(_t4192, &(Bool){1});
    Bool _t4195; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4193); _t4195 = *_hp; free(_hp); }
    (void)_t4195;
    Str_delete(_t4193, &(Bool){1});
    Str *_t4196 = Str_lit("pure", 4ULL);
    (void)_t4196;
    Bool _t4197 = Bool_or(_t4194, _t4195);
    (void)_t4197;
    ;
    ;
    Bool _t4198; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4196); _t4198 = *_hp; free(_hp); }
    (void)_t4198;
    Str_delete(_t4196, &(Bool){1});
    Str *_t4199 = Str_lit("pura", 4ULL);
    (void)_t4199;
    Bool _t4200 = Bool_or(_t4197, _t4198);
    (void)_t4200;
    ;
    ;
    Bool _t4201; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4199); _t4201 = *_hp; free(_hp); }
    (void)_t4201;
    Str_delete(_t4199, &(Bool){1});
    Bool _t4202 = Bool_or(_t4200, _t4201);
    (void)_t4202;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4202; return _r; }
}

