#include "til_modes.h"

Bool * Mode_eq(Mode * a, Mode * b) {
    (void)a;
    (void)b;
    Bool _t3033; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t3033 = *_hp; free(_hp); }
    (void)_t3033;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t3033; return _r; }
}

Mode * Mode_clone(Mode * self) {
    (void)self;
    Bool _t3034 = Bool_clone(&self->needs_main);
    (void)_t3034;
    Bool _t3035 = Bool_clone(&self->decls_only);
    (void)_t3035;
    Bool _t3036 = Bool_clone(&self->is_pure);
    (void)_t3036;
    Bool _t3037 = Bool_clone(&self->debug_prints);
    (void)_t3037;
    Mode *_t3038 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(&self->name); _t3038->name = *_ca; free(_ca); }
    _t3038->needs_main = _t3034;
    _t3038->decls_only = _t3035;
    { Str *_ca = Str_clone(&self->auto_import); _t3038->auto_import = *_ca; free(_ca); }
    _t3038->is_pure = _t3036;
    _t3038->debug_prints = _t3037;
    (void)_t3038;
    ;
    ;
    ;
    ;
    return _t3038;
}

U64 *Mode_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Mode);
    return r;
}

Mode * mode_resolve(Str * name) {
    (void)name;
    Str *_t3046 = Str_lit("script", 6ULL);
    (void)_t3046;
    Bool _t3047; { Bool *_hp = (Bool *)Str_eq(name, _t3046); _t3047 = *_hp; free(_hp); }
    (void)_t3047;
    Str_delete(_t3046, &(Bool){1});
    if (_t3047) {
        ;
        return MODE_SCRIPT;
    }
    ;
    Str *_t3048 = Str_lit("cli", 3ULL);
    (void)_t3048;
    Bool _t3049; { Bool *_hp = (Bool *)Str_eq(name, _t3048); _t3049 = *_hp; free(_hp); }
    (void)_t3049;
    Str_delete(_t3048, &(Bool){1});
    if (_t3049) {
        ;
        return MODE_CLI;
    }
    ;
    Str *_t3050 = Str_lit("gui", 3ULL);
    (void)_t3050;
    Bool _t3051; { Bool *_hp = (Bool *)Str_eq(name, _t3050); _t3051 = *_hp; free(_hp); }
    (void)_t3051;
    Str_delete(_t3050, &(Bool){1});
    if (_t3051) {
        ;
        return MODE_GUI;
    }
    ;
    Str *_t3052 = Str_lit("test", 4ULL);
    (void)_t3052;
    Bool _t3053; { Bool *_hp = (Bool *)Str_eq(name, _t3052); _t3053 = *_hp; free(_hp); }
    (void)_t3053;
    Str_delete(_t3052, &(Bool){1});
    if (_t3053) {
        ;
        return MODE_TEST;
    }
    ;
    Str *_t3054 = Str_lit("pure", 4ULL);
    (void)_t3054;
    Bool _t3055; { Bool *_hp = (Bool *)Str_eq(name, _t3054); _t3055 = *_hp; free(_hp); }
    (void)_t3055;
    Str_delete(_t3054, &(Bool){1});
    if (_t3055) {
        ;
        return MODE_PURE;
    }
    ;
    Str *_t3056 = Str_lit("pura", 4ULL);
    (void)_t3056;
    Bool _t3057; { Bool *_hp = (Bool *)Str_eq(name, _t3056); _t3057 = *_hp; free(_hp); }
    (void)_t3057;
    Str_delete(_t3056, &(Bool){1});
    if (_t3057) {
        ;
        return MODE_PURA;
    }
    ;
    Str *_t3058 = Str_lit("lib", 3ULL);
    (void)_t3058;
    Bool _t3059; { Bool *_hp = (Bool *)Str_eq(name, _t3058); _t3059 = *_hp; free(_hp); }
    (void)_t3059;
    Str_delete(_t3058, &(Bool){1});
    if (_t3059) {
        ;
        return MODE_LIB;
    }
    ;
    Str *_t3060 = Str_lit("liba", 4ULL);
    (void)_t3060;
    Bool _t3061; { Bool *_hp = (Bool *)Str_eq(name, _t3060); _t3061 = *_hp; free(_hp); }
    (void)_t3061;
    Str_delete(_t3060, &(Bool){1});
    if (_t3061) {
        ;
        return MODE_LIBA;
    }
    ;
    Str *_t3062 = Str_lit("Str", 3ULL);
    (void)_t3062;
    U64 _t3063; { U64 *_hp = (U64 *)Str_size(); _t3063 = *_hp; free(_hp); }
    (void)_t3063;
    U64 _t3064 = 1;
    (void)_t3064;
    Array *_va54 = Array_new(_t3062, &(U64){_t3063}, &(U64){_t3064});
    (void)_va54;
    Str_delete(_t3062, &(Bool){1});
    ;
    ;
    Str *_t3065 = Str_lit("unknown mode '", 14ULL);
    (void)_t3065;
    Str *_t3066 = Str_concat(_t3065, name);
    (void)_t3066;
    Str_delete(_t3065, &(Bool){1});
    Str *_t3067 = Str_lit("'", 1ULL);
    (void)_t3067;
    U64 _t3068 = 0;
    (void)_t3068;
    Str *_t3069 = Str_concat(_t3066, _t3067);
    (void)_t3069;
    Str_delete(_t3066, &(Bool){1});
    Str_delete(_t3067, &(Bool){1});
    Array_set(_va54, &(U64){_t3068}, _t3069);
    ;
    Str *_t3070 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/modes.til:34:11", 62ULL);
    (void)_t3070;
    panic(_t3070, _va54);
    Str_delete(_t3070, &(Bool){1});
    return MODE_SCRIPT;
}

Bool * mode_is_lib(Mode * m) {
    (void)m;
    Str *_t3071 = Str_lit("lib", 3ULL);
    (void)_t3071;
    Str *_t3072 = Str_lit("liba", 4ULL);
    (void)_t3072;
    Bool _t3073; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3071); _t3073 = *_hp; free(_hp); }
    (void)_t3073;
    Str_delete(_t3071, &(Bool){1});
    Bool _t3074; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3072); _t3074 = *_hp; free(_hp); }
    (void)_t3074;
    Str_delete(_t3072, &(Bool){1});
    Bool _t3075 = Bool_or(_t3073, _t3074);
    (void)_t3075;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t3075; return _r; }
}

Bool * mode_is_lib_output(Mode * m) {
    (void)m;
    Str *_t3076 = Str_lit("lib", 3ULL);
    (void)_t3076;
    Str *_t3077 = Str_lit("liba", 4ULL);
    (void)_t3077;
    Bool _t3078; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3076); _t3078 = *_hp; free(_hp); }
    (void)_t3078;
    Str_delete(_t3076, &(Bool){1});
    Bool _t3079; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3077); _t3079 = *_hp; free(_hp); }
    (void)_t3079;
    Str_delete(_t3077, &(Bool){1});
    Str *_t3080 = Str_lit("pure", 4ULL);
    (void)_t3080;
    Bool _t3081 = Bool_or(_t3078, _t3079);
    (void)_t3081;
    ;
    ;
    Bool _t3082; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3080); _t3082 = *_hp; free(_hp); }
    (void)_t3082;
    Str_delete(_t3080, &(Bool){1});
    Str *_t3083 = Str_lit("pura", 4ULL);
    (void)_t3083;
    Bool _t3084 = Bool_or(_t3081, _t3082);
    (void)_t3084;
    ;
    ;
    Bool _t3085; { Bool *_hp = (Bool *)Str_eq(&m->name, _t3083); _t3085 = *_hp; free(_hp); }
    (void)_t3085;
    Str_delete(_t3083, &(Bool){1});
    Bool _t3086 = Bool_or(_t3084, _t3085);
    (void)_t3086;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t3086; return _r; }
}

