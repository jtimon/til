#include "modes_core.h"

EnumDef * EnumDef_clone(EnumDef * self) {
    (void)self;
    EnumDef *_t0 = malloc(sizeof(EnumDef));
    (void)_t0;
    return _t0;
}

void EnumDef_delete(EnumDef * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *EnumDef_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(EnumDef);
    return r;
}

Bool * U8_lt(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    I64 _t11 = 0;
    (void)_t11;
    I64 _t12 = 1;
    (void)_t12;
    I64 _t13 = U8_cmp(DEREF(a), DEREF(b));
    (void)_t13;
    I64 _t14 = I64_sub(_t11, _t12);
    (void)_t14;
    ;
    ;
    Bool _t15 = I64_eq(_t13, _t14);
    (void)_t15;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t15; return _r; }
}

Bool * U8_gt(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    I64 _t16 = U8_cmp(DEREF(a), DEREF(b));
    (void)_t16;
    I64 _t17 = 1;
    (void)_t17;
    Bool _t18 = I64_eq(_t16, _t17);
    (void)_t18;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t18; return _r; }
}

Bool * U8_neq(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t19 = U8_eq(DEREF(a), DEREF(b));
    (void)_t19;
    Bool _t20 = Bool_not(_t19);
    (void)_t20;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t20; return _r; }
}

Bool * U8_lte(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t21; { Bool *_hp = (Bool *)U8_gt(a, b); _t21 = *_hp; free(_hp); }
    (void)_t21;
    Bool _t22 = Bool_not(_t21);
    (void)_t22;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t22; return _r; }
}

Bool * U8_gte(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t23; { Bool *_hp = (Bool *)U8_lt(a, b); _t23 = *_hp; free(_hp); }
    (void)_t23;
    Bool _t24 = Bool_not(_t23);
    (void)_t24;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t24; return _r; }
}

Bool * I16_lt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t46 = 0;
    (void)_t46;
    I64 _t47 = 1;
    (void)_t47;
    I64 _t48 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t48;
    I64 _t49 = I64_sub(_t46, _t47);
    (void)_t49;
    ;
    ;
    Bool _t50 = I64_eq(_t48, _t49);
    (void)_t50;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t50; return _r; }
}

Bool * I16_gt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t51 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t51;
    I64 _t52 = 1;
    (void)_t52;
    Bool _t53 = I64_eq(_t51, _t52);
    (void)_t53;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t53; return _r; }
}

Bool * I16_neq(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t54 = I16_eq(DEREF(a), DEREF(b));
    (void)_t54;
    Bool _t55 = Bool_not(_t54);
    (void)_t55;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t55; return _r; }
}

Bool * I16_lte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t56; { Bool *_hp = (Bool *)I16_gt(a, b); _t56 = *_hp; free(_hp); }
    (void)_t56;
    Bool _t57 = Bool_not(_t56);
    (void)_t57;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t57; return _r; }
}

Bool * I16_gte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t58; { Bool *_hp = (Bool *)I16_lt(a, b); _t58 = *_hp; free(_hp); }
    (void)_t58;
    Bool _t59 = Bool_not(_t58);
    (void)_t59;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t59; return _r; }
}

Bool * I32_lt(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    I64 _t81 = 0;
    (void)_t81;
    I64 _t82 = 1;
    (void)_t82;
    I64 _t83 = I32_cmp(DEREF(a), DEREF(b));
    (void)_t83;
    I64 _t84 = I64_sub(_t81, _t82);
    (void)_t84;
    ;
    ;
    Bool _t85 = I64_eq(_t83, _t84);
    (void)_t85;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t85; return _r; }
}

Bool * I32_gt(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    I64 _t86 = I32_cmp(DEREF(a), DEREF(b));
    (void)_t86;
    I64 _t87 = 1;
    (void)_t87;
    Bool _t88 = I64_eq(_t86, _t87);
    (void)_t88;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t88; return _r; }
}

Bool * I32_neq(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t89 = I32_eq(DEREF(a), DEREF(b));
    (void)_t89;
    Bool _t90 = Bool_not(_t89);
    (void)_t90;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t90; return _r; }
}

Bool * I32_lte(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t91; { Bool *_hp = (Bool *)I32_gt(a, b); _t91 = *_hp; free(_hp); }
    (void)_t91;
    Bool _t92 = Bool_not(_t91);
    (void)_t92;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t92; return _r; }
}

Bool * I32_gte(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t93; { Bool *_hp = (Bool *)I32_lt(a, b); _t93 = *_hp; free(_hp); }
    (void)_t93;
    Bool _t94 = Bool_not(_t93);
    (void)_t94;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t94; return _r; }
}

Bool * F32_lt(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    I64 _t97 = 0;
    (void)_t97;
    I64 _t98 = 1;
    (void)_t98;
    I64 _t99 = F32_cmp(DEREF(a), DEREF(b));
    (void)_t99;
    I64 _t100 = I64_sub(_t97, _t98);
    (void)_t100;
    ;
    ;
    Bool _t101 = I64_eq(_t99, _t100);
    (void)_t101;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t101; return _r; }
}

Bool * F32_gt(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    I64 _t102 = F32_cmp(DEREF(a), DEREF(b));
    (void)_t102;
    I64 _t103 = 1;
    (void)_t103;
    Bool _t104 = I64_eq(_t102, _t103);
    (void)_t104;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t104; return _r; }
}

Bool * F32_neq(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t105 = F32_eq(DEREF(a), DEREF(b));
    (void)_t105;
    Bool _t106 = Bool_not(_t105);
    (void)_t106;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t106; return _r; }
}

Bool * F32_lte(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t107; { Bool *_hp = (Bool *)F32_gt(a, b); _t107 = *_hp; free(_hp); }
    (void)_t107;
    Bool _t108 = Bool_not(_t107);
    (void)_t108;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t108; return _r; }
}

Bool * F32_gte(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t109; { Bool *_hp = (Bool *)F32_lt(a, b); _t109 = *_hp; free(_hp); }
    (void)_t109;
    Bool _t110 = Bool_not(_t109);
    (void)_t110;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t110; return _r; }
}

Bool * U32_lt(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    I64 _t120 = 0;
    (void)_t120;
    I64 _t121 = 1;
    (void)_t121;
    I64 _t122 = U32_cmp(DEREF(a), DEREF(b));
    (void)_t122;
    I64 _t123 = I64_sub(_t120, _t121);
    (void)_t123;
    ;
    ;
    Bool _t124 = I64_eq(_t122, _t123);
    (void)_t124;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t124; return _r; }
}

Bool * U32_gt(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    I64 _t125 = U32_cmp(DEREF(a), DEREF(b));
    (void)_t125;
    I64 _t126 = 1;
    (void)_t126;
    Bool _t127 = I64_eq(_t125, _t126);
    (void)_t127;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t127; return _r; }
}

Bool * U32_neq(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t128 = U32_eq(DEREF(a), DEREF(b));
    (void)_t128;
    Bool _t129 = Bool_not(_t128);
    (void)_t129;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t129; return _r; }
}

Bool * U32_lte(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t130; { Bool *_hp = (Bool *)U32_gt(a, b); _t130 = *_hp; free(_hp); }
    (void)_t130;
    Bool _t131 = Bool_not(_t130);
    (void)_t131;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t131; return _r; }
}

Bool * U32_gte(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t132; { Bool *_hp = (Bool *)U32_lt(a, b); _t132 = *_hp; free(_hp); }
    (void)_t132;
    Bool _t133 = Bool_not(_t132);
    (void)_t133;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t133; return _r; }
}

Bool * U64_lt(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    I64 _t143 = 0;
    (void)_t143;
    I64 _t144 = 1;
    (void)_t144;
    I64 _t145 = U64_cmp(DEREF(a), DEREF(b));
    (void)_t145;
    I64 _t146 = I64_sub(_t143, _t144);
    (void)_t146;
    ;
    ;
    Bool _t147 = I64_eq(_t145, _t146);
    (void)_t147;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t147; return _r; }
}

Bool * U64_gt(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    I64 _t148 = U64_cmp(DEREF(a), DEREF(b));
    (void)_t148;
    I64 _t149 = 1;
    (void)_t149;
    Bool _t150 = I64_eq(_t148, _t149);
    (void)_t150;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t150; return _r; }
}

Bool * U64_neq(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t151 = U64_eq(DEREF(a), DEREF(b));
    (void)_t151;
    Bool _t152 = Bool_not(_t151);
    (void)_t152;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t152; return _r; }
}

Bool * U64_lte(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t153; { Bool *_hp = (Bool *)U64_gt(a, b); _t153 = *_hp; free(_hp); }
    (void)_t153;
    Bool _t154 = Bool_not(_t153);
    (void)_t154;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t154; return _r; }
}

Bool * U64_gte(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t155; { Bool *_hp = (Bool *)U64_lt(a, b); _t155 = *_hp; free(_hp); }
    (void)_t155;
    Bool _t156 = Bool_not(_t155);
    (void)_t156;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t156; return _r; }
}

Bool * I64_lt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t219 = 0;
    (void)_t219;
    I64 _t220 = 1;
    (void)_t220;
    I64 _t221 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t221;
    I64 _t222 = I64_sub(_t219, _t220);
    (void)_t222;
    ;
    ;
    Bool _t223 = I64_eq(_t221, _t222);
    (void)_t223;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t223; return _r; }
}

Bool * I64_gt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t224 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t224;
    I64 _t225 = 1;
    (void)_t225;
    Bool _t226 = I64_eq(_t224, _t225);
    (void)_t226;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t226; return _r; }
}

Bool * I64_neq(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t227 = I64_eq(DEREF(a), DEREF(b));
    (void)_t227;
    Bool _t228 = Bool_not(_t227);
    (void)_t228;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t228; return _r; }
}

Bool * I64_lte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t229; { Bool *_hp = (Bool *)I64_gt(a, b); _t229 = *_hp; free(_hp); }
    (void)_t229;
    Bool _t230 = Bool_not(_t229);
    (void)_t230;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t230; return _r; }
}

Bool * I64_gte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t231; { Bool *_hp = (Bool *)I64_lt(a, b); _t231 = *_hp; free(_hp); }
    (void)_t231;
    Bool _t232 = Bool_not(_t231);
    (void)_t232;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t232; return _r; }
}

U64 *Range_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Range);
    return r;
}

Bool * Bool_lt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t253 = 0;
    (void)_t253;
    I64 _t254 = 1;
    (void)_t254;
    I64 _t255; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t255 = *_hp; free(_hp); }
    (void)_t255;
    I64 _t256 = I64_sub(_t253, _t254);
    (void)_t256;
    ;
    ;
    Bool _t257 = I64_eq(_t255, _t256);
    (void)_t257;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t257; return _r; }
}

Bool * Bool_gt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t258; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t258 = *_hp; free(_hp); }
    (void)_t258;
    I64 _t259 = 1;
    (void)_t259;
    Bool _t260 = I64_eq(_t258, _t259);
    (void)_t260;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t260; return _r; }
}

Bool * Bool_neq(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t261 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t261;
    Bool _t262 = Bool_not(_t261);
    (void)_t262;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t262; return _r; }
}

Bool * Bool_lte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t263; { Bool *_hp = (Bool *)Bool_gt(a, b); _t263 = *_hp; free(_hp); }
    (void)_t263;
    Bool _t264 = Bool_not(_t263);
    (void)_t264;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t264; return _r; }
}

Bool * Bool_gte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t265; { Bool *_hp = (Bool *)Bool_lt(a, b); _t265 = *_hp; free(_hp); }
    (void)_t265;
    Bool _t266 = Bool_not(_t265);
    (void)_t266;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t266; return _r; }
}

void println(Array * parts) {
    (void)parts;
    {
        Array *_fc267 = Array_clone(parts);
        (void)_fc267;
        U64 *_fi267 = malloc(sizeof(U64));
        *_fi267 = 0;
        (void)_fi267;
        while (1) {
            U64 _t269; { U64 *_hp = (U64 *)Array_len(_fc267); _t269 = *_hp; free(_hp); }
            (void)_t269;
            Bool _wcond268; { Bool *_hp = (Bool *)U64_lt(_fi267, &(U64){_t269}); _wcond268 = *_hp; free(_hp); }
            (void)_wcond268;
            ;
            if (_wcond268) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc267, _fi267);
            (void)s;
            U64 _t270 = 1;
            (void)_t270;
            U64 _t271 = U64_add(DEREF(_fi267), _t270);
            (void)_t271;
            ;
            *_fi267 = _t271;
            ;
            print_single(s);
        }
        Array_delete(_fc267, &(Bool){1});
        U64_delete(_fi267, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
    print_flush();
}

void print(Array * parts) {
    (void)parts;
    {
        Array *_fc272 = Array_clone(parts);
        (void)_fc272;
        U64 *_fi272 = malloc(sizeof(U64));
        *_fi272 = 0;
        (void)_fi272;
        while (1) {
            U64 _t274; { U64 *_hp = (U64 *)Array_len(_fc272); _t274 = *_hp; free(_hp); }
            (void)_t274;
            Bool _wcond273; { Bool *_hp = (Bool *)U64_lt(_fi272, &(U64){_t274}); _wcond273 = *_hp; free(_hp); }
            (void)_wcond273;
            ;
            if (_wcond273) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc272, _fi272);
            (void)s;
            U64 _t275 = 1;
            (void)_t275;
            U64 _t276 = U64_add(DEREF(_fi272), _t275);
            (void)_t276;
            ;
            *_fi272 = _t276;
            ;
            print_single(s);
        }
        Array_delete(_fc272, &(Bool){1});
        U64_delete(_fi272, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
}

Str * format(Array * parts) {
    (void)parts;
    U64 total = 0;
    (void)total;
    {
        Array *_fc277 = Array_clone(parts);
        (void)_fc277;
        U64 *_fi277 = malloc(sizeof(U64));
        *_fi277 = 0;
        (void)_fi277;
        while (1) {
            U64 _t279; { U64 *_hp = (U64 *)Array_len(_fc277); _t279 = *_hp; free(_hp); }
            (void)_t279;
            Bool _wcond278; { Bool *_hp = (Bool *)U64_lt(_fi277, &(U64){_t279}); _wcond278 = *_hp; free(_hp); }
            (void)_wcond278;
            ;
            if (_wcond278) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc277, _fi277);
            (void)s;
            U64 _t280 = 1;
            (void)_t280;
            U64 _t281 = U64_add(DEREF(_fi277), _t280);
            (void)_t281;
            ;
            *_fi277 = _t281;
            ;
            U64 _t282; { U64 *_hp = (U64 *)Str_len(s); _t282 = *_hp; free(_hp); }
            (void)_t282;
            U64 _t283 = U64_add(total, _t282);
            (void)_t283;
            ;
            total = _t283;
            ;
        }
        Array_delete(_fc277, &(Bool){1});
        U64_delete(_fi277, &(Bool){1});
    }
    U8 *buf = malloc(total);
    (void)buf;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        Array *_fc284 = Array_clone(parts);
        (void)_fc284;
        U64 *_fi284 = malloc(sizeof(U64));
        *_fi284 = 0;
        (void)_fi284;
        while (1) {
            U64 _t286; { U64 *_hp = (U64 *)Array_len(_fc284); _t286 = *_hp; free(_hp); }
            (void)_t286;
            Bool _wcond285; { Bool *_hp = (Bool *)U64_lt(_fi284, &(U64){_t286}); _wcond285 = *_hp; free(_hp); }
            (void)_wcond285;
            ;
            if (_wcond285) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc284, _fi284);
            (void)s;
            U64 _t287 = 1;
            (void)_t287;
            U64 _t288 = U64_add(DEREF(_fi284), _t287);
            (void)_t288;
            ;
            *_fi284 = _t288;
            ;
            void *_t289 = ptr_add(buf, DEREF(offset));
            (void)_t289;
            U64 _t290; { U64 *_hp = (U64 *)Str_len(s); _t290 = *_hp; free(_hp); }
            (void)_t290;
            memcpy(_t289, s->c_str, _t290);
            ;
            U64 _t291; { U64 *_hp = (U64 *)Str_len(s); _t291 = *_hp; free(_hp); }
            (void)_t291;
            U64 _t292 = U64_add(DEREF(offset), _t291);
            (void)_t292;
            ;
            *offset = _t292;
            ;
        }
        Array_delete(_fc284, &(Bool){1});
        U64_delete(_fi284, &(Bool){1});
    }
    U64_delete(offset, &(Bool){1});
    Array_delete(parts, &(Bool){1});
    U64 _t293 = U64_clone(&(U64){total});
    (void)_t293;
    U64 _t294 = U64_clone(&(U64){total});
    (void)_t294;
    ;
    Str *_t295 = malloc(sizeof(Str));
    _t295->c_str = buf;
    _t295->count = _t293;
    _t295->cap = _t294;
    (void)_t295;
    ;
    ;
    return _t295;
}

void swap(void * a, void * b, U64 size) {
    (void)a;
    (void)b;
    (void)size;
    U8 *tmp = malloc(size);
    (void)tmp;
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

void move(void * dest, void * src, U64 size) {
    (void)dest;
    (void)src;
    (void)size;
    memcpy(dest, src, size);
    I32 _t296 = 0;
    (void)_t296;
    memset(src, _t296, size);
    ;
}

I64 * wait_cmd(I64 * pid) {
    (void)pid;
    while (1) {
        I64 status = check_cmd_status(DEREF(pid));
        (void)status;
        I64 _t297 = 0;
        (void)_t297;
        I64 _t298 = 1;
        (void)_t298;
        I64 _t299 = I64_sub(_t297, _t298);
        (void)_t299;
        ;
        ;
        Bool _t300; { Bool *_hp = (Bool *)I64_neq(&(I64){status}, &(I64){_t299}); _t300 = *_hp; free(_hp); }
        (void)_t300;
        ;
        if (_t300) {
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = status; return _r; }
        }
        ;
        ;
        I64 _t301 = 50;
        (void)_t301;
        sleep_ms(_t301);
        ;
    }
}

I64 * run_cmd(Str * output, Array * args) {
    (void)output;
    (void)args;
    Str *cmd = Str_lit("", 0ULL);
    (void)cmd;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    while (1) {
        U64 _t307; { U64 *_hp = (U64 *)Array_len(args); _t307 = *_hp; free(_hp); }
        (void)_t307;
        Bool _wcond302; { Bool *_hp = (Bool *)U64_lt(i, &(U64){_t307}); _wcond302 = *_hp; free(_hp); }
        (void)_wcond302;
        ;
        if (_wcond302) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, i);
        (void)arg;
        U64 _t308 = 0;
        (void)_t308;
        Bool _t309; { Bool *_hp = (Bool *)U64_gt(i, &(U64){_t308}); _t309 = *_hp; free(_hp); }
        (void)_t309;
        ;
        if (_t309) {
            Str *_t303 = Str_lit(" '", 2ULL);
            (void)_t303;
            Str *_t304 = Str_concat(cmd, _t303);
            (void)_t304;
            Str_delete(_t303, &(Bool){1});
            Str *_t305 = Str_concat(_t304, arg);
            (void)_t305;
            Str_delete(_t304, &(Bool){1});
            Str *_t306 = Str_lit("'", 1ULL);
            (void)_t306;
            cmd = Str_concat(_t305, _t306);
            Str_delete(_t305, &(Bool){1});
            Str_delete(_t306, &(Bool){1});
        } else {
            cmd = Str_clone(arg);
        }
        ;
        U64 _t310 = 1;
        (void)_t310;
        U64 _t311 = U64_add(DEREF(i), _t310);
        (void)_t311;
        ;
        *i = _t311;
        ;
    }
    Array_delete(args, &(Bool){1});
    U64_delete(i, &(Bool){1});
    Str *tmpf = Str_lit("tmp/_run_cmd_out", 16ULL);
    (void)tmpf;
    Str *_t312 = Str_lit(" > ", 3ULL);
    (void)_t312;
    Str *_t313 = Str_concat(cmd, _t312);
    (void)_t313;
    Str_delete(_t312, &(Bool){1});
    Str_delete(cmd, &(Bool){1});
    Str *_t314 = Str_concat(_t313, tmpf);
    (void)_t314;
    Str_delete(_t313, &(Bool){1});
    Str *_t315 = Str_lit(" 2>&1", 5ULL);
    (void)_t315;
    Str *_t316 = Str_concat(_t314, _t315);
    (void)_t316;
    Str_delete(_t314, &(Bool){1});
    Str_delete(_t315, &(Bool){1});
    I64 pid; { I64 *_hp = (I64 *)spawn_cmd(_t316); pid = *_hp; free(_hp); }
    (void)pid;
    Str_delete(_t316, &(Bool){1});
    I64 ec; { I64 *_hp = (I64 *)wait_cmd(&(I64){pid}); ec = *_hp; free(_hp); }
    (void)ec;
    ;
    Str *content = readfile(tmpf);
    (void)content;
    Str_delete(tmpf, &(Bool){1});
    U64 _t317; { U64 *_hp = (U64 *)Str_size(); _t317 = *_hp; free(_hp); }
    (void)_t317;
    memcpy(output, content, _t317);
    ;
    free(content);
    { I64 *_r = malloc(sizeof(I64)); *_r = ec; return _r; }
}

void panic(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t318 = Str_lit("Str", 3ULL);
    (void)_t318;
    U64 _t319; { U64 *_hp = (U64 *)Str_size(); _t319 = *_hp; free(_hp); }
    (void)_t319;
    U64 _t320 = 3;
    (void)_t320;
    Array *_va0 = Array_new(_t318, &(U64){_t319}, &(U64){_t320});
    (void)_va0;
    Str_delete(_t318, &(Bool){1});
    ;
    ;
    U64 _t321 = 0;
    (void)_t321;
    Str *_t322 = Str_clone(loc_str);
    (void)_t322;
    Array_set(_va0, &(U64){_t321}, _t322);
    ;
    U64 _t323 = 1;
    (void)_t323;
    Str *_t324 = Str_lit(": panic: ", 9ULL);
    (void)_t324;
    Array_set(_va0, &(U64){_t323}, _t324);
    ;
    U64 _t325 = 2;
    (void)_t325;
    Str *_t326 = format(parts);
    (void)_t326;
    Array_set(_va0, &(U64){_t325}, _t326);
    ;
    println(_va0);
    I64 _t327 = 1;
    (void)_t327;
    exit(_t327);
    ;
}

void TODO(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t328 = Str_lit("Str", 3ULL);
    (void)_t328;
    U64 _t329; { U64 *_hp = (U64 *)Str_size(); _t329 = *_hp; free(_hp); }
    (void)_t329;
    U64 _t330 = 2;
    (void)_t330;
    Array *_va1 = Array_new(_t328, &(U64){_t329}, &(U64){_t330});
    (void)_va1;
    Str_delete(_t328, &(Bool){1});
    ;
    ;
    U64 _t331 = 0;
    (void)_t331;
    Str *_t332 = Str_lit("TODO: ", 6ULL);
    (void)_t332;
    Array_set(_va1, &(U64){_t331}, _t332);
    ;
    U64 _t333 = 1;
    (void)_t333;
    Str *_t334 = format(parts);
    (void)_t334;
    Array_set(_va1, &(U64){_t333}, _t334);
    ;
    panic(loc_str, _va1);
}

void UNREACHABLE(Str * loc_str) {
    (void)loc_str;
    Str *_t335 = Str_lit("Str", 3ULL);
    (void)_t335;
    U64 _t336; { U64 *_hp = (U64 *)Str_size(); _t336 = *_hp; free(_hp); }
    (void)_t336;
    U64 _t337 = 1;
    (void)_t337;
    Array *_va2 = Array_new(_t335, &(U64){_t336}, &(U64){_t337});
    (void)_va2;
    Str_delete(_t335, &(Bool){1});
    ;
    ;
    U64 _t338 = 0;
    (void)_t338;
    Str *_t339 = Str_lit("unreachable", 11ULL);
    (void)_t339;
    Array_set(_va2, &(U64){_t338}, _t339);
    ;
    panic(loc_str, _va2);
}

Bool * assert(Str * loc_str, Bool * cond) {
    (void)loc_str;
    (void)cond;
    Bool _t345 = Bool_not(DEREF(cond));
    (void)_t345;
    if (_t345) {
        Str *_t340 = Str_lit("Str", 3ULL);
        (void)_t340;
        U64 _t341; { U64 *_hp = (U64 *)Str_size(); _t341 = *_hp; free(_hp); }
        (void)_t341;
        U64 _t342 = 1;
        (void)_t342;
        Array *_va3 = Array_new(_t340, &(U64){_t341}, &(U64){_t342});
        (void)_va3;
        Str_delete(_t340, &(Bool){1});
        ;
        ;
        U64 _t343 = 0;
        (void)_t343;
        Str *_t344 = Str_lit("assert failed", 13ULL);
        (void)_t344;
        Array_set(_va3, &(U64){_t343}, _t344);
        ;
        panic(loc_str, _va3);
    }
    ;
    Bool _t346 = 1;
    (void)_t346;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t346; return _r; }
}

void expect(Str * loc_str, Bool * cond, Array * parts) {
    (void)loc_str;
    (void)cond;
    (void)parts;
    Bool _t354 = Bool_not(DEREF(cond));
    (void)_t354;
    if (_t354) {
        Str *_t347 = Str_lit("Str", 3ULL);
        (void)_t347;
        U64 _t348; { U64 *_hp = (U64 *)Str_size(); _t348 = *_hp; free(_hp); }
        (void)_t348;
        U64 _t349 = 2;
        (void)_t349;
        Array *_va4 = Array_new(_t347, &(U64){_t348}, &(U64){_t349});
        (void)_va4;
        Str_delete(_t347, &(Bool){1});
        ;
        ;
        U64 _t350 = 0;
        (void)_t350;
        Str *_t351 = Str_lit("assert failed: ", 15ULL);
        (void)_t351;
        Array_set(_va4, &(U64){_t350}, _t351);
        ;
        U64 _t352 = 1;
        (void)_t352;
        Str *_t353 = format(parts);
        (void)_t353;
        Array_set(_va4, &(U64){_t352}, _t353);
        ;
        panic(loc_str, _va4);
    }
    ;
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t368; { Bool *_hp = (Bool *)I64_neq(a, b); _t368 = *_hp; free(_hp); }
    (void)_t368;
    if (_t368) {
        Str *_t355 = Str_lit("Str", 3ULL);
        (void)_t355;
        U64 _t356; { U64 *_hp = (U64 *)Str_size(); _t356 = *_hp; free(_hp); }
        (void)_t356;
        U64 _t357 = 5;
        (void)_t357;
        Array *_va5 = Array_new(_t355, &(U64){_t356}, &(U64){_t357});
        (void)_va5;
        Str_delete(_t355, &(Bool){1});
        ;
        ;
        U64 _t358 = 0;
        (void)_t358;
        Str *_t359 = Str_lit("assert_eq failed: expected '", 28ULL);
        (void)_t359;
        Array_set(_va5, &(U64){_t358}, _t359);
        ;
        U64 _t360 = 1;
        (void)_t360;
        Str *_t361 = I64_to_str(a);
        (void)_t361;
        Array_set(_va5, &(U64){_t360}, _t361);
        ;
        U64 _t362 = 2;
        (void)_t362;
        Str *_t363 = Str_lit("', found '", 10ULL);
        (void)_t363;
        Array_set(_va5, &(U64){_t362}, _t363);
        ;
        U64 _t364 = 3;
        (void)_t364;
        Str *_t365 = I64_to_str(b);
        (void)_t365;
        Array_set(_va5, &(U64){_t364}, _t365);
        ;
        U64 _t366 = 4;
        (void)_t366;
        Str *_t367 = Str_lit("'", 1ULL);
        (void)_t367;
        Array_set(_va5, &(U64){_t366}, _t367);
        ;
        panic(loc_str, _va5);
    }
    ;
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t382; { Bool *_hp = (Bool *)Str_eq(a, b); _t382 = *_hp; free(_hp); }
    (void)_t382;
    Bool _t383 = Bool_not(_t382);
    (void)_t383;
    ;
    if (_t383) {
        Str *_t369 = Str_lit("Str", 3ULL);
        (void)_t369;
        U64 _t370; { U64 *_hp = (U64 *)Str_size(); _t370 = *_hp; free(_hp); }
        (void)_t370;
        U64 _t371 = 5;
        (void)_t371;
        Array *_va6 = Array_new(_t369, &(U64){_t370}, &(U64){_t371});
        (void)_va6;
        Str_delete(_t369, &(Bool){1});
        ;
        ;
        U64 _t372 = 0;
        (void)_t372;
        Str *_t373 = Str_lit("assert_eq_str failed: expected '", 32ULL);
        (void)_t373;
        Array_set(_va6, &(U64){_t372}, _t373);
        ;
        U64 _t374 = 1;
        (void)_t374;
        Str *_t375 = Str_clone(a);
        (void)_t375;
        Array_set(_va6, &(U64){_t374}, _t375);
        ;
        U64 _t376 = 2;
        (void)_t376;
        Str *_t377 = Str_lit("', found '", 10ULL);
        (void)_t377;
        Array_set(_va6, &(U64){_t376}, _t377);
        ;
        U64 _t378 = 3;
        (void)_t378;
        Str *_t379 = Str_clone(b);
        (void)_t379;
        Array_set(_va6, &(U64){_t378}, _t379);
        ;
        U64 _t380 = 4;
        (void)_t380;
        Str *_t381 = Str_lit("'", 1ULL);
        (void)_t381;
        Array_set(_va6, &(U64){_t380}, _t381);
        ;
        panic(loc_str, _va6);
    }
    ;
}

