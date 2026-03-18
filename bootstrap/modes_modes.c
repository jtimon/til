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
    Bool _t3055; { Bool *_hp = (Bool *)Map_has(core_modes, name); _t3055 = *_hp; free(_hp); }
    (void)_t3055;
    if (_t3055) {
        Mode *m = Map_get(core_modes, name);
        (void)m;
        ;
        return m;
    }
    ;
    Str *_t3056 = Str_lit("Str", 3ULL);
    (void)_t3056;
    U64 _t3057; { U64 *_hp = (U64 *)Str_size(); _t3057 = *_hp; free(_hp); }
    (void)_t3057;
    U64 _t3058 = 1;
    (void)_t3058;
    Array *_va54 = Array_new(_t3056, &(U64){_t3057}, &(U64){_t3058});
    (void)_va54;
    Str_delete(_t3056, &(Bool){1});
    ;
    ;
    Str *_t3059 = Str_lit("unknown mode '", 14ULL);
    (void)_t3059;
    Str *_t3060 = Str_concat(_t3059, name);
    (void)_t3060;
    Str_delete(_t3059, &(Bool){1});
    Str *_t3061 = Str_lit("'", 1ULL);
    (void)_t3061;
    U64 _t3062 = 0;
    (void)_t3062;
    Str *_t3063 = Str_concat(_t3060, _t3061);
    (void)_t3063;
    Str_delete(_t3060, &(Bool){1});
    Str_delete(_t3061, &(Bool){1});
    Array_set(_va54, &(U64){_t3062}, _t3063);
    ;
    Str *_t3064 = Str_lit("src/self/modes.til:45:11", 24ULL);
    (void)_t3064;
    panic(_t3064, _va54);
    Str_delete(_t3064, &(Bool){1});
    return MODE_SCRIPT;
}

Bool * mode_is_lib(Mode * m) {
    (void)m;
    Str *_t3065 = Str_lit("lib", 3ULL);
    (void)_t3065;
    Str *_t3066 = Str_lit("liba", 4ULL);
    (void)_t3066;
    Bool _t3067; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3065); _t3067 = *_hp; free(_hp); }
    (void)_t3067;
    Str_delete(_t3065, &(Bool){1});
    Bool _t3068; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3066); _t3068 = *_hp; free(_hp); }
    (void)_t3068;
    Str_delete(_t3066, &(Bool){1});
    Bool _t3069 = Bool_or(_t3067, _t3068);
    (void)_t3069;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t3069; return _r; }
}

Bool * mode_is_lib_output(Mode * m) {
    (void)m;
    Str *_t3070 = Str_lit("lib", 3ULL);
    (void)_t3070;
    Str *_t3071 = Str_lit("liba", 4ULL);
    (void)_t3071;
    Bool _t3072; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3070); _t3072 = *_hp; free(_hp); }
    (void)_t3072;
    Str_delete(_t3070, &(Bool){1});
    Bool _t3073; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3071); _t3073 = *_hp; free(_hp); }
    (void)_t3073;
    Str_delete(_t3071, &(Bool){1});
    Str *_t3074 = Str_lit("pure", 4ULL);
    (void)_t3074;
    Bool _t3075 = Bool_or(_t3072, _t3073);
    (void)_t3075;
    ;
    ;
    Bool _t3076; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3074); _t3076 = *_hp; free(_hp); }
    (void)_t3076;
    Str_delete(_t3074, &(Bool){1});
    Str *_t3077 = Str_lit("pura", 4ULL);
    (void)_t3077;
    Bool _t3078 = Bool_or(_t3075, _t3076);
    (void)_t3078;
    ;
    ;
    Bool _t3079; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3077); _t3079 = *_hp; free(_hp); }
    (void)_t3079;
    Str_delete(_t3077, &(Bool){1});
    Bool _t3080 = Bool_or(_t3078, _t3079);
    (void)_t3080;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t3080; return _r; }
}

