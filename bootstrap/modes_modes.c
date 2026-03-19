#include "modes_modes.h"

Bool * Mode_eq(Mode * a, Mode * b) {
    (void)a;
    (void)b;
    Bool _t3041; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t3041 = *_hp; free(_hp); }
    (void)_t3041;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t3041; return _r; }
}

Mode * Mode_clone(Mode * self) {
    (void)self;
    Bool _t3042 = Bool_clone(&self->needs_main);
    (void)_t3042;
    Bool _t3043 = Bool_clone(&self->decls_only);
    (void)_t3043;
    Bool _t3044 = Bool_clone(&self->is_pure);
    (void)_t3044;
    Bool _t3045 = Bool_clone(&self->debug_prints);
    (void)_t3045;
    Mode *_t3046 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(&self->name); _t3046->name = *_ca; free(_ca); }
    _t3046->needs_main = _t3042;
    _t3046->decls_only = _t3043;
    { Str *_ca = Str_clone(&self->auto_import); _t3046->auto_import = *_ca; free(_ca); }
    _t3046->is_pure = _t3044;
    _t3046->debug_prints = _t3045;
    (void)_t3046;
    ;
    ;
    ;
    ;
    return _t3046;
}

void Mode_delete(Mode * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t3047 = 0;
    (void)_t3047;
    Str_delete(&self->name, &(Bool){_t3047});
    ;
    Bool _t3048 = 0;
    (void)_t3048;
    Bool_delete(&self->needs_main, &(Bool){_t3048});
    ;
    Bool _t3049 = 0;
    (void)_t3049;
    Bool_delete(&self->decls_only, &(Bool){_t3049});
    ;
    Bool _t3050 = 0;
    (void)_t3050;
    Str_delete(&self->auto_import, &(Bool){_t3050});
    ;
    Bool _t3051 = 0;
    (void)_t3051;
    Bool_delete(&self->is_pure, &(Bool){_t3051});
    ;
    Bool _t3052 = 0;
    (void)_t3052;
    Bool_delete(&self->debug_prints, &(Bool){_t3052});
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
    Str *_t3054 = Str_lit("lib", 3ULL);
    (void)_t3054;
    Str *_t3055 = Str_lit("liba", 4ULL);
    (void)_t3055;
    Bool _t3056; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3054); _t3056 = *_hp; free(_hp); }
    (void)_t3056;
    Str_delete(_t3054, &(Bool){1});
    Bool _t3057; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3055); _t3057 = *_hp; free(_hp); }
    (void)_t3057;
    Str_delete(_t3055, &(Bool){1});
    Bool _t3058 = Bool_or(_t3056, _t3057);
    (void)_t3058;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t3058; return _r; }
}

Bool * mode_is_lib_output(Mode * m) {
    (void)m;
    Str *_t3059 = Str_lit("lib", 3ULL);
    (void)_t3059;
    Str *_t3060 = Str_lit("liba", 4ULL);
    (void)_t3060;
    Bool _t3061; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3059); _t3061 = *_hp; free(_hp); }
    (void)_t3061;
    Str_delete(_t3059, &(Bool){1});
    Bool _t3062; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3060); _t3062 = *_hp; free(_hp); }
    (void)_t3062;
    Str_delete(_t3060, &(Bool){1});
    Str *_t3063 = Str_lit("pure", 4ULL);
    (void)_t3063;
    Bool _t3064 = Bool_or(_t3061, _t3062);
    (void)_t3064;
    ;
    ;
    Bool _t3065; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3063); _t3065 = *_hp; free(_hp); }
    (void)_t3065;
    Str_delete(_t3063, &(Bool){1});
    Str *_t3066 = Str_lit("pura", 4ULL);
    (void)_t3066;
    Bool _t3067 = Bool_or(_t3064, _t3065);
    (void)_t3067;
    ;
    ;
    Bool _t3068; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3066); _t3068 = *_hp; free(_hp); }
    (void)_t3068;
    Str_delete(_t3066, &(Bool){1});
    Bool _t3069 = Bool_or(_t3067, _t3068);
    (void)_t3069;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t3069; return _r; }
}

