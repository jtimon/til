#include "modes_modes.h"

Bool * Mode_eq(Mode * a, Mode * b) {
    (void)a;
    (void)b;
    Bool _t4139; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t4139 = *_hp; free(_hp); }
    (void)_t4139;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4139; return _r; }
}

Mode * Mode_clone(Mode * self) {
    (void)self;
    Bool _t4140 = Bool_clone(&self->needs_main);
    (void)_t4140;
    Bool _t4141 = Bool_clone(&self->decls_only);
    (void)_t4141;
    Bool _t4142 = Bool_clone(&self->is_pure);
    (void)_t4142;
    Bool _t4143 = Bool_clone(&self->debug_prints);
    (void)_t4143;
    Mode *_t4144 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(&self->name); _t4144->name = *_ca; free(_ca); }
    _t4144->needs_main = _t4140;
    _t4144->decls_only = _t4141;
    { Str *_ca = Str_clone(&self->auto_import); _t4144->auto_import = *_ca; free(_ca); }
    _t4144->is_pure = _t4142;
    _t4144->debug_prints = _t4143;
    (void)_t4144;
    ;
    ;
    ;
    ;
    return _t4144;
}

void Mode_delete(Mode * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t4145 = 0;
    (void)_t4145;
    Str_delete(&self->name, &(Bool){_t4145});
    ;
    Bool _t4146 = 0;
    (void)_t4146;
    Bool_delete(&self->needs_main, &(Bool){_t4146});
    ;
    Bool _t4147 = 0;
    (void)_t4147;
    Bool_delete(&self->decls_only, &(Bool){_t4147});
    ;
    Bool _t4148 = 0;
    (void)_t4148;
    Str_delete(&self->auto_import, &(Bool){_t4148});
    ;
    Bool _t4149 = 0;
    (void)_t4149;
    Bool_delete(&self->is_pure, &(Bool){_t4149});
    ;
    Bool _t4150 = 0;
    (void)_t4150;
    Bool_delete(&self->debug_prints, &(Bool){_t4150});
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
    Str *_t4152 = Str_lit("lib", 3ULL);
    (void)_t4152;
    Str *_t4153 = Str_lit("liba", 4ULL);
    (void)_t4153;
    Bool _t4154; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4152); _t4154 = *_hp; free(_hp); }
    (void)_t4154;
    Str_delete(_t4152, &(Bool){1});
    Bool _t4155; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4153); _t4155 = *_hp; free(_hp); }
    (void)_t4155;
    Str_delete(_t4153, &(Bool){1});
    Bool _t4156 = Bool_or(_t4154, _t4155);
    (void)_t4156;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4156; return _r; }
}

Bool * mode_is_lib_output(Mode * m) {
    (void)m;
    Str *_t4157 = Str_lit("lib", 3ULL);
    (void)_t4157;
    Str *_t4158 = Str_lit("liba", 4ULL);
    (void)_t4158;
    Bool _t4159; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4157); _t4159 = *_hp; free(_hp); }
    (void)_t4159;
    Str_delete(_t4157, &(Bool){1});
    Bool _t4160; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4158); _t4160 = *_hp; free(_hp); }
    (void)_t4160;
    Str_delete(_t4158, &(Bool){1});
    Str *_t4161 = Str_lit("pure", 4ULL);
    (void)_t4161;
    Bool _t4162 = Bool_or(_t4159, _t4160);
    (void)_t4162;
    ;
    ;
    Bool _t4163; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4161); _t4163 = *_hp; free(_hp); }
    (void)_t4163;
    Str_delete(_t4161, &(Bool){1});
    Str *_t4164 = Str_lit("pura", 4ULL);
    (void)_t4164;
    Bool _t4165 = Bool_or(_t4162, _t4163);
    (void)_t4165;
    ;
    ;
    Bool _t4166; { Bool *_hp = (Bool *)Str_eq(&m->name, _t4164); _t4166 = *_hp; free(_hp); }
    (void)_t4166;
    Str_delete(_t4164, &(Bool){1});
    Bool _t4167 = Bool_or(_t4165, _t4166);
    (void)_t4167;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t4167; return _r; }
}

