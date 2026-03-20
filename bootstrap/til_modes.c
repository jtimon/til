#include "til_modes.h"

Bool * Mode_eq(Mode * a, Mode * b) {
    (void)a;
    (void)b;
    Bool _t4147; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t4147 = *_hp; free(_hp); }
    (void)_t4147;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4147; return _r; }
}

Mode * Mode_clone(Mode * self) {
    (void)self;
    Bool _t4148 = Bool_clone(&self->needs_main);
    (void)_t4148;
    Bool _t4149 = Bool_clone(&self->decls_only);
    (void)_t4149;
    Bool _t4150 = Bool_clone(&self->is_pure);
    (void)_t4150;
    Bool _t4151 = Bool_clone(&self->debug_prints);
    (void)_t4151;
    Mode *_t4152 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(&self->name); _t4152->name = *_ca; free(_ca); }
    _t4152->needs_main = _t4148;
    _t4152->decls_only = _t4149;
    { Str *_ca = Str_clone(&self->auto_import); _t4152->auto_import = *_ca; free(_ca); }
    _t4152->is_pure = _t4150;
    _t4152->debug_prints = _t4151;
    (void)_t4152;
    ;
    ;
    ;
    ;
    return _t4152;
}

void Mode_delete(Mode * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4153 = 0;
    (void)_t4153;
    Str_delete(&self->name, &(Bool){_t4153});
    ;
    Bool _t4154 = 0;
    (void)_t4154;
    Bool_delete(&self->needs_main, &(Bool){_t4154});
    ;
    Bool _t4155 = 0;
    (void)_t4155;
    Bool_delete(&self->decls_only, &(Bool){_t4155});
    ;
    Bool _t4156 = 0;
    (void)_t4156;
    Str_delete(&self->auto_import, &(Bool){_t4156});
    ;
    Bool _t4157 = 0;
    (void)_t4157;
    Bool_delete(&self->is_pure, &(Bool){_t4157});
    ;
    Bool _t4158 = 0;
    (void)_t4158;
    Bool_delete(&self->debug_prints, &(Bool){_t4158});
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
    Str *_t4160 = Str_lit("lib", 3ULL);
    (void)_t4160;
    Str *_t4161 = Str_lit("liba", 4ULL);
    (void)_t4161;
    Bool _t4162; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4160); _t4162 = *_hp; free(_hp); }
    (void)_t4162;
    Str_delete(_t4160, &(Bool){1});
    Bool _t4163; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4161); _t4163 = *_hp; free(_hp); }
    (void)_t4163;
    Str_delete(_t4161, &(Bool){1});
    Bool _t4164 = Bool_or(_t4162, _t4163);
    (void)_t4164;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4164; return _r; }
}

Bool * mode_is_lib_output(Mode * m) {
    (void)m;
    Str *_t4165 = Str_lit("lib", 3ULL);
    (void)_t4165;
    Str *_t4166 = Str_lit("liba", 4ULL);
    (void)_t4166;
    Bool _t4167; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4165); _t4167 = *_hp; free(_hp); }
    (void)_t4167;
    Str_delete(_t4165, &(Bool){1});
    Bool _t4168; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4166); _t4168 = *_hp; free(_hp); }
    (void)_t4168;
    Str_delete(_t4166, &(Bool){1});
    Str *_t4169 = Str_lit("pure", 4ULL);
    (void)_t4169;
    Bool _t4170 = Bool_or(_t4167, _t4168);
    (void)_t4170;
    ;
    ;
    Bool _t4171; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4169); _t4171 = *_hp; free(_hp); }
    (void)_t4171;
    Str_delete(_t4169, &(Bool){1});
    Str *_t4172 = Str_lit("pura", 4ULL);
    (void)_t4172;
    Bool _t4173 = Bool_or(_t4170, _t4171);
    (void)_t4173;
    ;
    ;
    Bool _t4174; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4172); _t4174 = *_hp; free(_hp); }
    (void)_t4174;
    Str_delete(_t4172, &(Bool){1});
    Bool _t4175 = Bool_or(_t4173, _t4174);
    (void)_t4175;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4175; return _r; }
}

