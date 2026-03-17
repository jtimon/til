#include "til_core.h"

Bool * U8_neq(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t67 = U8_eq(DEREF(a), DEREF(b));
    (void)_t67;
    Bool _t68 = Bool_not(_t67);
    (void)_t68;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t68; return _r; }
}

Bool * I32_gt(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    I64 _t122 = I32_cmp(DEREF(a), DEREF(b));
    (void)_t122;
    I64 _t123 = 1;
    (void)_t123;
    Bool _t124 = I64_eq(_t122, _t123);
    (void)_t124;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t124; return _r; }
}

Bool * U32_lt(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    I64 _t150 = 0;
    (void)_t150;
    I64 _t151 = 1;
    (void)_t151;
    I64 _t152 = U32_cmp(DEREF(a), DEREF(b));
    (void)_t152;
    I64 _t153 = I64_sub(_t150, _t151);
    (void)_t153;
    ;
    ;
    Bool _t154 = I64_eq(_t152, _t153);
    (void)_t154;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t154; return _r; }
}

Bool * U64_lt(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    I64 _t167 = 0;
    (void)_t167;
    I64 _t168 = 1;
    (void)_t168;
    I64 _t169 = U64_cmp(DEREF(a), DEREF(b));
    (void)_t169;
    I64 _t170 = I64_sub(_t167, _t168);
    (void)_t170;
    ;
    ;
    Bool _t171 = I64_eq(_t169, _t170);
    (void)_t171;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t171; return _r; }
}

Bool * U64_gt(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    I64 _t172 = U64_cmp(DEREF(a), DEREF(b));
    (void)_t172;
    I64 _t173 = 1;
    (void)_t173;
    Bool _t174 = I64_eq(_t172, _t173);
    (void)_t174;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t174; return _r; }
}

Bool * U64_lte(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t177; { Bool *_hp = (Bool *)U64_gt(a, b); _t177 = *_hp; free(_hp); }
    (void)_t177;
    Bool _t178 = Bool_not(_t177);
    (void)_t178;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t178; return _r; }
}

Bool * U64_gte(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t179; { Bool *_hp = (Bool *)U64_lt(a, b); _t179 = *_hp; free(_hp); }
    (void)_t179;
    Bool _t180 = Bool_not(_t179);
    (void)_t180;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t180; return _r; }
}

Bool * I64_lt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t238 = 0;
    (void)_t238;
    I64 _t239 = 1;
    (void)_t239;
    I64 _t240 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t240;
    I64 _t241 = I64_sub(_t238, _t239);
    (void)_t241;
    ;
    ;
    Bool _t242 = I64_eq(_t240, _t241);
    (void)_t242;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t242; return _r; }
}

Bool * I64_gt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t243 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t243;
    I64 _t244 = 1;
    (void)_t244;
    Bool _t245 = I64_eq(_t243, _t244);
    (void)_t245;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t245; return _r; }
}

Bool * I64_neq(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t246 = I64_eq(DEREF(a), DEREF(b));
    (void)_t246;
    Bool _t247 = Bool_not(_t246);
    (void)_t247;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t247; return _r; }
}

Bool * I64_gte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t250; { Bool *_hp = (Bool *)I64_lt(a, b); _t250 = *_hp; free(_hp); }
    (void)_t250;
    Bool _t251 = Bool_not(_t250);
    (void)_t251;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t251; return _r; }
}

U64 *Range_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Range);
    return r;
}

void println(Array * parts) {
    (void)parts;
    {
        U64 *_fi286 = malloc(sizeof(U64));
        *_fi286 = 0;
        (void)_fi286;
        while (1) {
            U64 _t288; { U64 *_hp = (U64 *)Array_len(parts); _t288 = *_hp; free(_hp); }
            (void)_t288;
            Bool _wcond287; { Bool *_hp = (Bool *)U64_lt(_fi286, &(U64){_t288}); _wcond287 = *_hp; free(_hp); }
            (void)_wcond287;
            ;
            if (_wcond287) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi286);
            (void)s;
            U64 _t289 = 1;
            (void)_t289;
            U64 _t290 = U64_add(DEREF(_fi286), _t289);
            (void)_t290;
            ;
            *_fi286 = _t290;
            ;
            print_single(s);
        }
        U64_delete(_fi286, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
    print_flush();
}

Str * format(Array * parts) {
    (void)parts;
    U64 total = 0;
    (void)total;
    {
        U64 *_fi296 = malloc(sizeof(U64));
        *_fi296 = 0;
        (void)_fi296;
        while (1) {
            U64 _t298; { U64 *_hp = (U64 *)Array_len(parts); _t298 = *_hp; free(_hp); }
            (void)_t298;
            Bool _wcond297; { Bool *_hp = (Bool *)U64_lt(_fi296, &(U64){_t298}); _wcond297 = *_hp; free(_hp); }
            (void)_wcond297;
            ;
            if (_wcond297) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi296);
            (void)s;
            U64 _t299 = 1;
            (void)_t299;
            U64 _t300 = U64_add(DEREF(_fi296), _t299);
            (void)_t300;
            ;
            *_fi296 = _t300;
            ;
            U64 _t301; { U64 *_hp = (U64 *)Str_len(s); _t301 = *_hp; free(_hp); }
            (void)_t301;
            U64 _t302 = U64_add(total, _t301);
            (void)_t302;
            ;
            total = _t302;
            ;
        }
        U64_delete(_fi296, &(Bool){1});
    }
    U8 *buf = malloc(total);
    (void)buf;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 *_fi303 = malloc(sizeof(U64));
        *_fi303 = 0;
        (void)_fi303;
        while (1) {
            U64 _t305; { U64 *_hp = (U64 *)Array_len(parts); _t305 = *_hp; free(_hp); }
            (void)_t305;
            Bool _wcond304; { Bool *_hp = (Bool *)U64_lt(_fi303, &(U64){_t305}); _wcond304 = *_hp; free(_hp); }
            (void)_wcond304;
            ;
            if (_wcond304) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi303);
            (void)s;
            U64 _t306 = 1;
            (void)_t306;
            U64 _t307 = U64_add(DEREF(_fi303), _t306);
            (void)_t307;
            ;
            *_fi303 = _t307;
            ;
            void *_t308 = ptr_add(buf, DEREF(offset));
            (void)_t308;
            U64 _t309; { U64 *_hp = (U64 *)Str_len(s); _t309 = *_hp; free(_hp); }
            (void)_t309;
            memcpy(_t308, s->c_str, _t309);
            ;
            U64 _t310; { U64 *_hp = (U64 *)Str_len(s); _t310 = *_hp; free(_hp); }
            (void)_t310;
            U64 _t311 = U64_add(DEREF(offset), _t310);
            (void)_t311;
            ;
            *offset = _t311;
            ;
        }
        U64_delete(_fi303, &(Bool){1});
    }
    U64_delete(offset, &(Bool){1});
    Array_delete(parts, &(Bool){1});
    U64 _t312 = U64_clone(&(U64){total});
    (void)_t312;
    U64 _t313 = U64_clone(&(U64){total});
    (void)_t313;
    ;
    Str *_t314 = malloc(sizeof(Str));
    _t314->c_str = buf;
    _t314->count = _t312;
    _t314->cap = _t313;
    (void)_t314;
    ;
    ;
    return _t314;
}

void panic(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t337 = Str_lit("Str", 3ULL);
    (void)_t337;
    U64 _t338; { U64 *_hp = (U64 *)Str_size(); _t338 = *_hp; free(_hp); }
    (void)_t338;
    U64 _t339 = 3;
    (void)_t339;
    Array *_va0 = Array_new(_t337, &(U64){_t338}, &(U64){_t339});
    (void)_va0;
    Str_delete(_t337, &(Bool){1});
    ;
    ;
    U64 _t340 = 0;
    (void)_t340;
    Str *_t341 = Str_clone(loc_str);
    (void)_t341;
    Array_set(_va0, &(U64){_t340}, _t341);
    ;
    U64 _t342 = 1;
    (void)_t342;
    Str *_t343 = Str_lit(": panic: ", 9ULL);
    (void)_t343;
    Array_set(_va0, &(U64){_t342}, _t343);
    ;
    U64 _t344 = 2;
    (void)_t344;
    Str *_t345 = format(parts);
    (void)_t345;
    Array_set(_va0, &(U64){_t344}, _t345);
    ;
    println(_va0);
    I64 _t346 = 1;
    (void)_t346;
    exit(_t346);
    ;
}

