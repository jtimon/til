#include "modes_modes.h"

Bool * Mode_eq(Mode * a, Mode * b) {
    (void)a;
    (void)b;
    Bool _t3042; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t3042 = *_hp; free(_hp); }
    (void)_t3042;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t3042; return _r; }
}

Mode * Mode_clone(Mode * self) {
    (void)self;
    Bool _t3043 = Bool_clone(&self->needs_main);
    (void)_t3043;
    Bool _t3044 = Bool_clone(&self->decls_only);
    (void)_t3044;
    Bool _t3045 = Bool_clone(&self->is_pure);
    (void)_t3045;
    Bool _t3046 = Bool_clone(&self->debug_prints);
    (void)_t3046;
    Mode *_t3047 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(&self->name); _t3047->name = *_ca; free(_ca); }
    _t3047->needs_main = _t3043;
    _t3047->decls_only = _t3044;
    { Str *_ca = Str_clone(&self->auto_import); _t3047->auto_import = *_ca; free(_ca); }
    _t3047->is_pure = _t3045;
    _t3047->debug_prints = _t3046;
    (void)_t3047;
    ;
    ;
    ;
    ;
    return _t3047;
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
    Str *_t3055 = Str_lit("lib", 3ULL);
    (void)_t3055;
    Str *_t3056 = Str_lit("liba", 4ULL);
    (void)_t3056;
    Bool _t3057; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3055); _t3057 = *_hp; free(_hp); }
    (void)_t3057;
    Str_delete(_t3055, &(Bool){1});
    Bool _t3058; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3056); _t3058 = *_hp; free(_hp); }
    (void)_t3058;
    Str_delete(_t3056, &(Bool){1});
    Bool _t3059 = Bool_or(_t3057, _t3058);
    (void)_t3059;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t3059; return _r; }
}

Bool * mode_is_lib_output(Mode * m) {
    (void)m;
    Str *_t3060 = Str_lit("lib", 3ULL);
    (void)_t3060;
    Str *_t3061 = Str_lit("liba", 4ULL);
    (void)_t3061;
    Bool _t3062; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3060); _t3062 = *_hp; free(_hp); }
    (void)_t3062;
    Str_delete(_t3060, &(Bool){1});
    Bool _t3063; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3061); _t3063 = *_hp; free(_hp); }
    (void)_t3063;
    Str_delete(_t3061, &(Bool){1});
    Str *_t3064 = Str_lit("pure", 4ULL);
    (void)_t3064;
    Bool _t3065 = Bool_or(_t3062, _t3063);
    (void)_t3065;
    ;
    ;
    Bool _t3066; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3064); _t3066 = *_hp; free(_hp); }
    (void)_t3066;
    Str_delete(_t3064, &(Bool){1});
    Str *_t3067 = Str_lit("pura", 4ULL);
    (void)_t3067;
    Bool _t3068 = Bool_or(_t3065, _t3066);
    (void)_t3068;
    ;
    ;
    Bool _t3069; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3067); _t3069 = *_hp; free(_hp); }
    (void)_t3069;
    Str_delete(_t3067, &(Bool){1});
    Bool _t3070 = Bool_or(_t3068, _t3069);
    (void)_t3070;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t3070; return _r; }
}

