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
    I64 _t5 = 0;
    (void)_t5;
    I64 _t6 = 1;
    (void)_t6;
    I64 _t7 = U8_cmp(DEREF(a), DEREF(b));
    (void)_t7;
    I64 _t8 = I64_sub(_t5, _t6);
    (void)_t8;
    ;
    ;
    Bool _t9 = I64_eq(_t7, _t8);
    (void)_t9;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t9; return _r; }
}

Bool * U8_gt(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    I64 _t10 = U8_cmp(DEREF(a), DEREF(b));
    (void)_t10;
    I64 _t11 = 1;
    (void)_t11;
    Bool _t12 = I64_eq(_t10, _t11);
    (void)_t12;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t12; return _r; }
}

Bool * U8_neq(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t13 = U8_eq(DEREF(a), DEREF(b));
    (void)_t13;
    Bool _t14 = Bool_not(_t13);
    (void)_t14;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t14; return _r; }
}

Bool * U8_lte(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t15; { Bool *_hp = (Bool *)U8_gt(a, b); _t15 = *_hp; free(_hp); }
    (void)_t15;
    Bool _t16 = Bool_not(_t15);
    (void)_t16;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t16; return _r; }
}

Bool * U8_gte(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t17; { Bool *_hp = (Bool *)U8_lt(a, b); _t17 = *_hp; free(_hp); }
    (void)_t17;
    Bool _t18 = Bool_not(_t17);
    (void)_t18;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t18; return _r; }
}

Bool * I16_lt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t34 = 0;
    (void)_t34;
    I64 _t35 = 1;
    (void)_t35;
    I64 _t36 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t36;
    I64 _t37 = I64_sub(_t34, _t35);
    (void)_t37;
    ;
    ;
    Bool _t38 = I64_eq(_t36, _t37);
    (void)_t38;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t38; return _r; }
}

Bool * I16_gt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t39 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t39;
    I64 _t40 = 1;
    (void)_t40;
    Bool _t41 = I64_eq(_t39, _t40);
    (void)_t41;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t41; return _r; }
}

Bool * I16_neq(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t42 = I16_eq(DEREF(a), DEREF(b));
    (void)_t42;
    Bool _t43 = Bool_not(_t42);
    (void)_t43;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t43; return _r; }
}

Bool * I16_lte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t44; { Bool *_hp = (Bool *)I16_gt(a, b); _t44 = *_hp; free(_hp); }
    (void)_t44;
    Bool _t45 = Bool_not(_t44);
    (void)_t45;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t45; return _r; }
}

Bool * I16_gte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t46; { Bool *_hp = (Bool *)I16_lt(a, b); _t46 = *_hp; free(_hp); }
    (void)_t46;
    Bool _t47 = Bool_not(_t46);
    (void)_t47;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t47; return _r; }
}

Bool * I32_lt(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    I64 _t63 = 0;
    (void)_t63;
    I64 _t64 = 1;
    (void)_t64;
    I64 _t65 = I32_cmp(DEREF(a), DEREF(b));
    (void)_t65;
    I64 _t66 = I64_sub(_t63, _t64);
    (void)_t66;
    ;
    ;
    Bool _t67 = I64_eq(_t65, _t66);
    (void)_t67;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t67; return _r; }
}

Bool * I32_gt(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    I64 _t68 = I32_cmp(DEREF(a), DEREF(b));
    (void)_t68;
    I64 _t69 = 1;
    (void)_t69;
    Bool _t70 = I64_eq(_t68, _t69);
    (void)_t70;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t70; return _r; }
}

Bool * I32_neq(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t71 = I32_eq(DEREF(a), DEREF(b));
    (void)_t71;
    Bool _t72 = Bool_not(_t71);
    (void)_t72;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t72; return _r; }
}

Bool * I32_lte(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t73; { Bool *_hp = (Bool *)I32_gt(a, b); _t73 = *_hp; free(_hp); }
    (void)_t73;
    Bool _t74 = Bool_not(_t73);
    (void)_t74;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t74; return _r; }
}

Bool * I32_gte(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t75; { Bool *_hp = (Bool *)I32_lt(a, b); _t75 = *_hp; free(_hp); }
    (void)_t75;
    Bool _t76 = Bool_not(_t75);
    (void)_t76;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t76; return _r; }
}

Bool * F32_lt(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    I64 _t79 = 0;
    (void)_t79;
    I64 _t80 = 1;
    (void)_t80;
    I64 _t81 = F32_cmp(DEREF(a), DEREF(b));
    (void)_t81;
    I64 _t82 = I64_sub(_t79, _t80);
    (void)_t82;
    ;
    ;
    Bool _t83 = I64_eq(_t81, _t82);
    (void)_t83;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t83; return _r; }
}

Bool * F32_gt(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    I64 _t84 = F32_cmp(DEREF(a), DEREF(b));
    (void)_t84;
    I64 _t85 = 1;
    (void)_t85;
    Bool _t86 = I64_eq(_t84, _t85);
    (void)_t86;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t86; return _r; }
}

Bool * F32_neq(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t87 = F32_eq(DEREF(a), DEREF(b));
    (void)_t87;
    Bool _t88 = Bool_not(_t87);
    (void)_t88;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t88; return _r; }
}

Bool * F32_lte(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t89; { Bool *_hp = (Bool *)F32_gt(a, b); _t89 = *_hp; free(_hp); }
    (void)_t89;
    Bool _t90 = Bool_not(_t89);
    (void)_t90;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t90; return _r; }
}

Bool * F32_gte(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t91; { Bool *_hp = (Bool *)F32_lt(a, b); _t91 = *_hp; free(_hp); }
    (void)_t91;
    Bool _t92 = Bool_not(_t91);
    (void)_t92;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t92; return _r; }
}

Bool * U32_lt(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    I64 _t96 = 0;
    (void)_t96;
    I64 _t97 = 1;
    (void)_t97;
    I64 _t98 = U32_cmp(DEREF(a), DEREF(b));
    (void)_t98;
    I64 _t99 = I64_sub(_t96, _t97);
    (void)_t99;
    ;
    ;
    Bool _t100 = I64_eq(_t98, _t99);
    (void)_t100;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t100; return _r; }
}

Bool * U32_gt(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    I64 _t101 = U32_cmp(DEREF(a), DEREF(b));
    (void)_t101;
    I64 _t102 = 1;
    (void)_t102;
    Bool _t103 = I64_eq(_t101, _t102);
    (void)_t103;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t103; return _r; }
}

Bool * U32_neq(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t104 = U32_eq(DEREF(a), DEREF(b));
    (void)_t104;
    Bool _t105 = Bool_not(_t104);
    (void)_t105;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t105; return _r; }
}

Bool * U32_lte(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t106; { Bool *_hp = (Bool *)U32_gt(a, b); _t106 = *_hp; free(_hp); }
    (void)_t106;
    Bool _t107 = Bool_not(_t106);
    (void)_t107;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t107; return _r; }
}

Bool * U32_gte(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t108; { Bool *_hp = (Bool *)U32_lt(a, b); _t108 = *_hp; free(_hp); }
    (void)_t108;
    Bool _t109 = Bool_not(_t108);
    (void)_t109;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t109; return _r; }
}

Bool * U64_lt(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    I64 _t113 = 0;
    (void)_t113;
    I64 _t114 = 1;
    (void)_t114;
    I64 _t115 = U64_cmp(DEREF(a), DEREF(b));
    (void)_t115;
    I64 _t116 = I64_sub(_t113, _t114);
    (void)_t116;
    ;
    ;
    Bool _t117 = I64_eq(_t115, _t116);
    (void)_t117;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t117; return _r; }
}

Bool * U64_gt(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    I64 _t118 = U64_cmp(DEREF(a), DEREF(b));
    (void)_t118;
    I64 _t119 = 1;
    (void)_t119;
    Bool _t120 = I64_eq(_t118, _t119);
    (void)_t120;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t120; return _r; }
}

Bool * U64_neq(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t121 = U64_eq(DEREF(a), DEREF(b));
    (void)_t121;
    Bool _t122 = Bool_not(_t121);
    (void)_t122;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t122; return _r; }
}

Bool * U64_lte(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t123; { Bool *_hp = (Bool *)U64_gt(a, b); _t123 = *_hp; free(_hp); }
    (void)_t123;
    Bool _t124 = Bool_not(_t123);
    (void)_t124;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t124; return _r; }
}

Bool * U64_gte(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t125; { Bool *_hp = (Bool *)U64_lt(a, b); _t125 = *_hp; free(_hp); }
    (void)_t125;
    Bool _t126 = Bool_not(_t125);
    (void)_t126;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t126; return _r; }
}

Bool * I64_lt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t184 = 0;
    (void)_t184;
    I64 _t185 = 1;
    (void)_t185;
    I64 _t186 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t186;
    I64 _t187 = I64_sub(_t184, _t185);
    (void)_t187;
    ;
    ;
    Bool _t188 = I64_eq(_t186, _t187);
    (void)_t188;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t188; return _r; }
}

Bool * I64_gt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t189 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t189;
    I64 _t190 = 1;
    (void)_t190;
    Bool _t191 = I64_eq(_t189, _t190);
    (void)_t191;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t191; return _r; }
}

Bool * I64_neq(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t192 = I64_eq(DEREF(a), DEREF(b));
    (void)_t192;
    Bool _t193 = Bool_not(_t192);
    (void)_t193;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t193; return _r; }
}

Bool * I64_lte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t194; { Bool *_hp = (Bool *)I64_gt(a, b); _t194 = *_hp; free(_hp); }
    (void)_t194;
    Bool _t195 = Bool_not(_t194);
    (void)_t195;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t195; return _r; }
}

Bool * I64_gte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t196; { Bool *_hp = (Bool *)I64_lt(a, b); _t196 = *_hp; free(_hp); }
    (void)_t196;
    Bool _t197 = Bool_not(_t196);
    (void)_t197;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t197; return _r; }
}

U64 *Range_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Range);
    return r;
}

Bool * Bool_lt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t218 = 0;
    (void)_t218;
    I64 _t219 = 1;
    (void)_t219;
    I64 _t220; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t220 = *_hp; free(_hp); }
    (void)_t220;
    I64 _t221 = I64_sub(_t218, _t219);
    (void)_t221;
    ;
    ;
    Bool _t222 = I64_eq(_t220, _t221);
    (void)_t222;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t222; return _r; }
}

Bool * Bool_gt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t223; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t223 = *_hp; free(_hp); }
    (void)_t223;
    I64 _t224 = 1;
    (void)_t224;
    Bool _t225 = I64_eq(_t223, _t224);
    (void)_t225;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t225; return _r; }
}

Bool * Bool_neq(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t226 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t226;
    Bool _t227 = Bool_not(_t226);
    (void)_t227;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t227; return _r; }
}

Bool * Bool_lte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t228; { Bool *_hp = (Bool *)Bool_gt(a, b); _t228 = *_hp; free(_hp); }
    (void)_t228;
    Bool _t229 = Bool_not(_t228);
    (void)_t229;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t229; return _r; }
}

Bool * Bool_gte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t230; { Bool *_hp = (Bool *)Bool_lt(a, b); _t230 = *_hp; free(_hp); }
    (void)_t230;
    Bool _t231 = Bool_not(_t230);
    (void)_t231;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t231; return _r; }
}

void println(Array * parts) {
    (void)parts;
    {
        U64 *_fi232 = malloc(sizeof(U64));
        *_fi232 = 0;
        (void)_fi232;
        while (1) {
            U64 _t234; { U64 *_hp = (U64 *)Array_len(parts); _t234 = *_hp; free(_hp); }
            (void)_t234;
            Bool _wcond233; { Bool *_hp = (Bool *)U64_lt(_fi232, &(U64){_t234}); _wcond233 = *_hp; free(_hp); }
            (void)_wcond233;
            ;
            if (_wcond233) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi232);
            (void)s;
            U64 _t235 = 1;
            (void)_t235;
            U64 _t236 = U64_add(DEREF(_fi232), _t235);
            (void)_t236;
            ;
            *_fi232 = _t236;
            ;
            print_single(s);
        }
        U64_delete(_fi232, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
    print_flush();
}

void print(Array * parts) {
    (void)parts;
    {
        U64 *_fi237 = malloc(sizeof(U64));
        *_fi237 = 0;
        (void)_fi237;
        while (1) {
            U64 _t239; { U64 *_hp = (U64 *)Array_len(parts); _t239 = *_hp; free(_hp); }
            (void)_t239;
            Bool _wcond238; { Bool *_hp = (Bool *)U64_lt(_fi237, &(U64){_t239}); _wcond238 = *_hp; free(_hp); }
            (void)_wcond238;
            ;
            if (_wcond238) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi237);
            (void)s;
            U64 _t240 = 1;
            (void)_t240;
            U64 _t241 = U64_add(DEREF(_fi237), _t240);
            (void)_t241;
            ;
            *_fi237 = _t241;
            ;
            print_single(s);
        }
        U64_delete(_fi237, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
}

Str * format(Array * parts) {
    (void)parts;
    U64 total = 0;
    (void)total;
    {
        U64 *_fi242 = malloc(sizeof(U64));
        *_fi242 = 0;
        (void)_fi242;
        while (1) {
            U64 _t244; { U64 *_hp = (U64 *)Array_len(parts); _t244 = *_hp; free(_hp); }
            (void)_t244;
            Bool _wcond243; { Bool *_hp = (Bool *)U64_lt(_fi242, &(U64){_t244}); _wcond243 = *_hp; free(_hp); }
            (void)_wcond243;
            ;
            if (_wcond243) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi242);
            (void)s;
            U64 _t245 = 1;
            (void)_t245;
            U64 _t246 = U64_add(DEREF(_fi242), _t245);
            (void)_t246;
            ;
            *_fi242 = _t246;
            ;
            U64 _t247; { U64 *_hp = (U64 *)Str_len(s); _t247 = *_hp; free(_hp); }
            (void)_t247;
            U64 _t248 = U64_add(total, _t247);
            (void)_t248;
            ;
            total = _t248;
            ;
        }
        U64_delete(_fi242, &(Bool){1});
    }
    U8 *buf = malloc(total);
    (void)buf;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 *_fi249 = malloc(sizeof(U64));
        *_fi249 = 0;
        (void)_fi249;
        while (1) {
            U64 _t251; { U64 *_hp = (U64 *)Array_len(parts); _t251 = *_hp; free(_hp); }
            (void)_t251;
            Bool _wcond250; { Bool *_hp = (Bool *)U64_lt(_fi249, &(U64){_t251}); _wcond250 = *_hp; free(_hp); }
            (void)_wcond250;
            ;
            if (_wcond250) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi249);
            (void)s;
            U64 _t252 = 1;
            (void)_t252;
            U64 _t253 = U64_add(DEREF(_fi249), _t252);
            (void)_t253;
            ;
            *_fi249 = _t253;
            ;
            void *_t254 = ptr_add(buf, DEREF(offset));
            (void)_t254;
            U64 _t255; { U64 *_hp = (U64 *)Str_len(s); _t255 = *_hp; free(_hp); }
            (void)_t255;
            memcpy(_t254, s->c_str, _t255);
            ;
            U64 _t256; { U64 *_hp = (U64 *)Str_len(s); _t256 = *_hp; free(_hp); }
            (void)_t256;
            U64 _t257 = U64_add(DEREF(offset), _t256);
            (void)_t257;
            ;
            *offset = _t257;
            ;
        }
        U64_delete(_fi249, &(Bool){1});
    }
    U64_delete(offset, &(Bool){1});
    Array_delete(parts, &(Bool){1});
    U64 _t258 = U64_clone(&(U64){total});
    (void)_t258;
    U64 _t259 = U64_clone(&(U64){total});
    (void)_t259;
    ;
    Str *_t260 = malloc(sizeof(Str));
    _t260->c_str = buf;
    _t260->count = _t258;
    _t260->cap = _t259;
    (void)_t260;
    ;
    ;
    return _t260;
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
    I32 _t261 = 0;
    (void)_t261;
    memset(src, _t261, size);
    ;
}

I64 * wait_cmd(I64 * pid) {
    (void)pid;
    while (1) {
        I64 status = check_cmd_status(DEREF(pid));
        (void)status;
        I64 _t262 = 0;
        (void)_t262;
        I64 _t263 = 1;
        (void)_t263;
        I64 _t264 = I64_sub(_t262, _t263);
        (void)_t264;
        ;
        ;
        Bool _t265; { Bool *_hp = (Bool *)I64_neq(&(I64){status}, &(I64){_t264}); _t265 = *_hp; free(_hp); }
        (void)_t265;
        ;
        if (_t265) {
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = status; return _r; }
        }
        ;
        ;
        I64 _t266 = 50;
        (void)_t266;
        sleep_ms(_t266);
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
        U64 _t272; { U64 *_hp = (U64 *)Array_len(args); _t272 = *_hp; free(_hp); }
        (void)_t272;
        Bool _wcond267; { Bool *_hp = (Bool *)U64_lt(i, &(U64){_t272}); _wcond267 = *_hp; free(_hp); }
        (void)_wcond267;
        ;
        if (_wcond267) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, i);
        (void)arg;
        U64 _t273 = 0;
        (void)_t273;
        Bool _t274; { Bool *_hp = (Bool *)U64_gt(i, &(U64){_t273}); _t274 = *_hp; free(_hp); }
        (void)_t274;
        ;
        if (_t274) {
            Str *_t268 = Str_lit(" '", 2ULL);
            (void)_t268;
            Str *_t269 = Str_concat(cmd, _t268);
            (void)_t269;
            Str_delete(_t268, &(Bool){1});
            Str *_t270 = Str_concat(_t269, arg);
            (void)_t270;
            Str_delete(_t269, &(Bool){1});
            Str *_t271 = Str_lit("'", 1ULL);
            (void)_t271;
            cmd = Str_concat(_t270, _t271);
            Str_delete(_t270, &(Bool){1});
            Str_delete(_t271, &(Bool){1});
        } else {
            cmd = Str_clone(arg);
        }
        ;
        U64 _t275 = 1;
        (void)_t275;
        U64 _t276 = U64_add(DEREF(i), _t275);
        (void)_t276;
        ;
        *i = _t276;
        ;
    }
    Array_delete(args, &(Bool){1});
    U64_delete(i, &(Bool){1});
    Str *tmpf = Str_lit("tmp/_run_cmd_out", 16ULL);
    (void)tmpf;
    Str *_t277 = Str_lit(" > ", 3ULL);
    (void)_t277;
    Str *_t278 = Str_concat(cmd, _t277);
    (void)_t278;
    Str_delete(_t277, &(Bool){1});
    Str_delete(cmd, &(Bool){1});
    Str *_t279 = Str_concat(_t278, tmpf);
    (void)_t279;
    Str_delete(_t278, &(Bool){1});
    Str *_t280 = Str_lit(" 2>&1", 5ULL);
    (void)_t280;
    Str *_t281 = Str_concat(_t279, _t280);
    (void)_t281;
    Str_delete(_t279, &(Bool){1});
    Str_delete(_t280, &(Bool){1});
    I64 pid; { I64 *_hp = (I64 *)spawn_cmd(_t281); pid = *_hp; free(_hp); }
    (void)pid;
    Str_delete(_t281, &(Bool){1});
    I64 ec; { I64 *_hp = (I64 *)wait_cmd(&(I64){pid}); ec = *_hp; free(_hp); }
    (void)ec;
    ;
    Str *content = readfile(tmpf);
    (void)content;
    Str_delete(tmpf, &(Bool){1});
    U64 _t282; { U64 *_hp = (U64 *)Str_size(); _t282 = *_hp; free(_hp); }
    (void)_t282;
    memcpy(output, content, _t282);
    ;
    free(content);
    { I64 *_r = malloc(sizeof(I64)); *_r = ec; return _r; }
}

void panic(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t283 = Str_lit("Str", 3ULL);
    (void)_t283;
    U64 _t284; { U64 *_hp = (U64 *)Str_size(); _t284 = *_hp; free(_hp); }
    (void)_t284;
    U64 _t285 = 3;
    (void)_t285;
    Array *_va0 = Array_new(_t283, &(U64){_t284}, &(U64){_t285});
    (void)_va0;
    Str_delete(_t283, &(Bool){1});
    ;
    ;
    U64 _t286 = 0;
    (void)_t286;
    Str *_t287 = Str_clone(loc_str);
    (void)_t287;
    Array_set(_va0, &(U64){_t286}, _t287);
    ;
    U64 _t288 = 1;
    (void)_t288;
    Str *_t289 = Str_lit(": panic: ", 9ULL);
    (void)_t289;
    Array_set(_va0, &(U64){_t288}, _t289);
    ;
    U64 _t290 = 2;
    (void)_t290;
    Str *_t291 = format(parts);
    (void)_t291;
    Array_set(_va0, &(U64){_t290}, _t291);
    ;
    println(_va0);
    I64 _t292 = 1;
    (void)_t292;
    exit(_t292);
    ;
}

void TODO(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t293 = Str_lit("Str", 3ULL);
    (void)_t293;
    U64 _t294; { U64 *_hp = (U64 *)Str_size(); _t294 = *_hp; free(_hp); }
    (void)_t294;
    U64 _t295 = 2;
    (void)_t295;
    Array *_va1 = Array_new(_t293, &(U64){_t294}, &(U64){_t295});
    (void)_va1;
    Str_delete(_t293, &(Bool){1});
    ;
    ;
    U64 _t296 = 0;
    (void)_t296;
    Str *_t297 = Str_lit("TODO: ", 6ULL);
    (void)_t297;
    Array_set(_va1, &(U64){_t296}, _t297);
    ;
    U64 _t298 = 1;
    (void)_t298;
    Str *_t299 = format(parts);
    (void)_t299;
    Array_set(_va1, &(U64){_t298}, _t299);
    ;
    panic(loc_str, _va1);
}

void UNREACHABLE(Str * loc_str) {
    (void)loc_str;
    Str *_t300 = Str_lit("Str", 3ULL);
    (void)_t300;
    U64 _t301; { U64 *_hp = (U64 *)Str_size(); _t301 = *_hp; free(_hp); }
    (void)_t301;
    U64 _t302 = 1;
    (void)_t302;
    Array *_va2 = Array_new(_t300, &(U64){_t301}, &(U64){_t302});
    (void)_va2;
    Str_delete(_t300, &(Bool){1});
    ;
    ;
    U64 _t303 = 0;
    (void)_t303;
    Str *_t304 = Str_lit("unreachable", 11ULL);
    (void)_t304;
    Array_set(_va2, &(U64){_t303}, _t304);
    ;
    panic(loc_str, _va2);
}

Bool * assert(Str * loc_str, Bool * cond) {
    (void)loc_str;
    (void)cond;
    Bool _t310 = Bool_not(DEREF(cond));
    (void)_t310;
    if (_t310) {
        Str *_t305 = Str_lit("Str", 3ULL);
        (void)_t305;
        U64 _t306; { U64 *_hp = (U64 *)Str_size(); _t306 = *_hp; free(_hp); }
        (void)_t306;
        U64 _t307 = 1;
        (void)_t307;
        Array *_va3 = Array_new(_t305, &(U64){_t306}, &(U64){_t307});
        (void)_va3;
        Str_delete(_t305, &(Bool){1});
        ;
        ;
        U64 _t308 = 0;
        (void)_t308;
        Str *_t309 = Str_lit("assert failed", 13ULL);
        (void)_t309;
        Array_set(_va3, &(U64){_t308}, _t309);
        ;
        panic(loc_str, _va3);
    }
    ;
    Bool _t311 = 1;
    (void)_t311;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t311; return _r; }
}

void expect(Str * loc_str, Bool * cond, Array * parts) {
    (void)loc_str;
    (void)cond;
    (void)parts;
    Bool _t319 = Bool_not(DEREF(cond));
    (void)_t319;
    if (_t319) {
        Str *_t312 = Str_lit("Str", 3ULL);
        (void)_t312;
        U64 _t313; { U64 *_hp = (U64 *)Str_size(); _t313 = *_hp; free(_hp); }
        (void)_t313;
        U64 _t314 = 2;
        (void)_t314;
        Array *_va4 = Array_new(_t312, &(U64){_t313}, &(U64){_t314});
        (void)_va4;
        Str_delete(_t312, &(Bool){1});
        ;
        ;
        U64 _t315 = 0;
        (void)_t315;
        Str *_t316 = Str_lit("assert failed: ", 15ULL);
        (void)_t316;
        Array_set(_va4, &(U64){_t315}, _t316);
        ;
        U64 _t317 = 1;
        (void)_t317;
        Str *_t318 = format(parts);
        (void)_t318;
        Array_set(_va4, &(U64){_t317}, _t318);
        ;
        panic(loc_str, _va4);
    }
    ;
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t333; { Bool *_hp = (Bool *)I64_neq(a, b); _t333 = *_hp; free(_hp); }
    (void)_t333;
    if (_t333) {
        Str *_t320 = Str_lit("Str", 3ULL);
        (void)_t320;
        U64 _t321; { U64 *_hp = (U64 *)Str_size(); _t321 = *_hp; free(_hp); }
        (void)_t321;
        U64 _t322 = 5;
        (void)_t322;
        Array *_va5 = Array_new(_t320, &(U64){_t321}, &(U64){_t322});
        (void)_va5;
        Str_delete(_t320, &(Bool){1});
        ;
        ;
        U64 _t323 = 0;
        (void)_t323;
        Str *_t324 = Str_lit("assert_eq failed: expected '", 28ULL);
        (void)_t324;
        Array_set(_va5, &(U64){_t323}, _t324);
        ;
        U64 _t325 = 1;
        (void)_t325;
        Str *_t326 = I64_to_str(a);
        (void)_t326;
        Array_set(_va5, &(U64){_t325}, _t326);
        ;
        U64 _t327 = 2;
        (void)_t327;
        Str *_t328 = Str_lit("', found '", 10ULL);
        (void)_t328;
        Array_set(_va5, &(U64){_t327}, _t328);
        ;
        U64 _t329 = 3;
        (void)_t329;
        Str *_t330 = I64_to_str(b);
        (void)_t330;
        Array_set(_va5, &(U64){_t329}, _t330);
        ;
        U64 _t331 = 4;
        (void)_t331;
        Str *_t332 = Str_lit("'", 1ULL);
        (void)_t332;
        Array_set(_va5, &(U64){_t331}, _t332);
        ;
        panic(loc_str, _va5);
    }
    ;
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t347; { Bool *_hp = (Bool *)Str_eq(a, b); _t347 = *_hp; free(_hp); }
    (void)_t347;
    Bool _t348 = Bool_not(_t347);
    (void)_t348;
    ;
    if (_t348) {
        Str *_t334 = Str_lit("Str", 3ULL);
        (void)_t334;
        U64 _t335; { U64 *_hp = (U64 *)Str_size(); _t335 = *_hp; free(_hp); }
        (void)_t335;
        U64 _t336 = 5;
        (void)_t336;
        Array *_va6 = Array_new(_t334, &(U64){_t335}, &(U64){_t336});
        (void)_va6;
        Str_delete(_t334, &(Bool){1});
        ;
        ;
        U64 _t337 = 0;
        (void)_t337;
        Str *_t338 = Str_lit("assert_eq_str failed: expected '", 32ULL);
        (void)_t338;
        Array_set(_va6, &(U64){_t337}, _t338);
        ;
        U64 _t339 = 1;
        (void)_t339;
        Str *_t340 = Str_clone(a);
        (void)_t340;
        Array_set(_va6, &(U64){_t339}, _t340);
        ;
        U64 _t341 = 2;
        (void)_t341;
        Str *_t342 = Str_lit("', found '", 10ULL);
        (void)_t342;
        Array_set(_va6, &(U64){_t341}, _t342);
        ;
        U64 _t343 = 3;
        (void)_t343;
        Str *_t344 = Str_clone(b);
        (void)_t344;
        Array_set(_va6, &(U64){_t343}, _t344);
        ;
        U64 _t345 = 4;
        (void)_t345;
        Str *_t346 = Str_lit("'", 1ULL);
        (void)_t346;
        Array_set(_va6, &(U64){_t345}, _t346);
        ;
        panic(loc_str, _va6);
    }
    ;
}

