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

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    (void)self;
    U32 _t35 = U32_clone(&self->nparam);
    (void)_t35;
    I32 _t36 = I32_clone(&self->variadic_index);
    (void)_t36;
    I32 _t37 = I32_clone(&self->kwargs_index);
    (void)_t37;
    Bool _t38 = Bool_clone(&self->return_is_ref);
    (void)_t38;
    Bool _t39 = Bool_clone(&self->return_is_shallow);
    (void)_t39;
    FunctionDef *_t40 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); _t40->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->param_names); _t40->param_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->param_types); _t40->param_types = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->param_muts); _t40->param_muts = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->param_owns); _t40->param_owns = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->param_shallows); _t40->param_shallows = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->param_fn_sigs); _t40->param_fn_sigs = *_ca; free(_ca); }
    _t40->nparam = _t35;
    { Map *_ca = Map_clone(&self->param_defaults); _t40->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); _t40->return_type = *_ca; free(_ca); }
    _t40->variadic_index = _t36;
    _t40->kwargs_index = _t37;
    _t40->return_is_ref = _t38;
    _t40->return_is_shallow = _t39;
    (void)_t40;
    ;
    ;
    ;
    ;
    ;
    return _t40;
}

void FunctionDef_delete(FunctionDef * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t41 = 0;
    (void)_t41;
    FuncType_delete(&self->func_type, &(Bool){_t41});
    ;
    Bool _t42 = 0;
    (void)_t42;
    Vec_delete(&self->param_names, &(Bool){_t42});
    ;
    Bool _t43 = 0;
    (void)_t43;
    Vec_delete(&self->param_types, &(Bool){_t43});
    ;
    Bool _t44 = 0;
    (void)_t44;
    Vec_delete(&self->param_muts, &(Bool){_t44});
    ;
    Bool _t45 = 0;
    (void)_t45;
    Vec_delete(&self->param_owns, &(Bool){_t45});
    ;
    Bool _t46 = 0;
    (void)_t46;
    Vec_delete(&self->param_shallows, &(Bool){_t46});
    ;
    Bool _t47 = 0;
    (void)_t47;
    Vec_delete(&self->param_fn_sigs, &(Bool){_t47});
    ;
    Bool _t48 = 0;
    (void)_t48;
    U32_delete(&self->nparam, &(Bool){_t48});
    ;
    Bool _t49 = 0;
    (void)_t49;
    Map_delete(&self->param_defaults, &(Bool){_t49});
    ;
    Bool _t50 = 0;
    (void)_t50;
    Str_delete(&self->return_type, &(Bool){_t50});
    ;
    Bool _t51 = 0;
    (void)_t51;
    I32_delete(&self->variadic_index, &(Bool){_t51});
    ;
    Bool _t52 = 0;
    (void)_t52;
    I32_delete(&self->kwargs_index, &(Bool){_t52});
    ;
    Bool _t53 = 0;
    (void)_t53;
    Bool_delete(&self->return_is_ref, &(Bool){_t53});
    ;
    Bool _t54 = 0;
    (void)_t54;
    Bool_delete(&self->return_is_shallow, &(Bool){_t54});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *FunctionDef_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(FunctionDef);
    return r;
}

Bool * U8_lt(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    I64 _t59 = 0;
    (void)_t59;
    I64 _t60 = 1;
    (void)_t60;
    I64 _t61 = U8_cmp(DEREF(a), DEREF(b));
    (void)_t61;
    I64 _t62 = I64_sub(_t59, _t60);
    (void)_t62;
    ;
    ;
    Bool _t63 = I64_eq(_t61, _t62);
    (void)_t63;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t63; return _r; }
}

Bool * U8_gt(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    I64 _t64 = U8_cmp(DEREF(a), DEREF(b));
    (void)_t64;
    I64 _t65 = 1;
    (void)_t65;
    Bool _t66 = I64_eq(_t64, _t65);
    (void)_t66;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t66; return _r; }
}

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

Bool * U8_lte(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t69; { Bool *_hp = (Bool *)U8_gt(a, b); _t69 = *_hp; free(_hp); }
    (void)_t69;
    Bool _t70 = Bool_not(_t69);
    (void)_t70;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t70; return _r; }
}

Bool * U8_gte(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t71; { Bool *_hp = (Bool *)U8_lt(a, b); _t71 = *_hp; free(_hp); }
    (void)_t71;
    Bool _t72 = Bool_not(_t71);
    (void)_t72;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t72; return _r; }
}

Bool * I16_lt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t88 = 0;
    (void)_t88;
    I64 _t89 = 1;
    (void)_t89;
    I64 _t90 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t90;
    I64 _t91 = I64_sub(_t88, _t89);
    (void)_t91;
    ;
    ;
    Bool _t92 = I64_eq(_t90, _t91);
    (void)_t92;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t92; return _r; }
}

Bool * I16_gt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t93 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t93;
    I64 _t94 = 1;
    (void)_t94;
    Bool _t95 = I64_eq(_t93, _t94);
    (void)_t95;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t95; return _r; }
}

Bool * I16_neq(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t96 = I16_eq(DEREF(a), DEREF(b));
    (void)_t96;
    Bool _t97 = Bool_not(_t96);
    (void)_t97;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t97; return _r; }
}

Bool * I16_lte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t98; { Bool *_hp = (Bool *)I16_gt(a, b); _t98 = *_hp; free(_hp); }
    (void)_t98;
    Bool _t99 = Bool_not(_t98);
    (void)_t99;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t99; return _r; }
}

Bool * I16_gte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t100; { Bool *_hp = (Bool *)I16_lt(a, b); _t100 = *_hp; free(_hp); }
    (void)_t100;
    Bool _t101 = Bool_not(_t100);
    (void)_t101;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t101; return _r; }
}

Bool * I32_lt(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    I64 _t117 = 0;
    (void)_t117;
    I64 _t118 = 1;
    (void)_t118;
    I64 _t119 = I32_cmp(DEREF(a), DEREF(b));
    (void)_t119;
    I64 _t120 = I64_sub(_t117, _t118);
    (void)_t120;
    ;
    ;
    Bool _t121 = I64_eq(_t119, _t120);
    (void)_t121;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t121; return _r; }
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

Bool * I32_neq(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t125 = I32_eq(DEREF(a), DEREF(b));
    (void)_t125;
    Bool _t126 = Bool_not(_t125);
    (void)_t126;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t126; return _r; }
}

Bool * I32_lte(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t127; { Bool *_hp = (Bool *)I32_gt(a, b); _t127 = *_hp; free(_hp); }
    (void)_t127;
    Bool _t128 = Bool_not(_t127);
    (void)_t128;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t128; return _r; }
}

Bool * I32_gte(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t129; { Bool *_hp = (Bool *)I32_lt(a, b); _t129 = *_hp; free(_hp); }
    (void)_t129;
    Bool _t130 = Bool_not(_t129);
    (void)_t130;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t130; return _r; }
}

Bool * F32_lt(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    I64 _t133 = 0;
    (void)_t133;
    I64 _t134 = 1;
    (void)_t134;
    I64 _t135 = F32_cmp(DEREF(a), DEREF(b));
    (void)_t135;
    I64 _t136 = I64_sub(_t133, _t134);
    (void)_t136;
    ;
    ;
    Bool _t137 = I64_eq(_t135, _t136);
    (void)_t137;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t137; return _r; }
}

Bool * F32_gt(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    I64 _t138 = F32_cmp(DEREF(a), DEREF(b));
    (void)_t138;
    I64 _t139 = 1;
    (void)_t139;
    Bool _t140 = I64_eq(_t138, _t139);
    (void)_t140;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t140; return _r; }
}

Bool * F32_neq(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t141 = F32_eq(DEREF(a), DEREF(b));
    (void)_t141;
    Bool _t142 = Bool_not(_t141);
    (void)_t142;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t142; return _r; }
}

Bool * F32_lte(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t143; { Bool *_hp = (Bool *)F32_gt(a, b); _t143 = *_hp; free(_hp); }
    (void)_t143;
    Bool _t144 = Bool_not(_t143);
    (void)_t144;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t144; return _r; }
}

Bool * F32_gte(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t145; { Bool *_hp = (Bool *)F32_lt(a, b); _t145 = *_hp; free(_hp); }
    (void)_t145;
    Bool _t146 = Bool_not(_t145);
    (void)_t146;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t146; return _r; }
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

Bool * U32_gt(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    I64 _t155 = U32_cmp(DEREF(a), DEREF(b));
    (void)_t155;
    I64 _t156 = 1;
    (void)_t156;
    Bool _t157 = I64_eq(_t155, _t156);
    (void)_t157;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t157; return _r; }
}

Bool * U32_neq(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t158 = U32_eq(DEREF(a), DEREF(b));
    (void)_t158;
    Bool _t159 = Bool_not(_t158);
    (void)_t159;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t159; return _r; }
}

Bool * U32_lte(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t160; { Bool *_hp = (Bool *)U32_gt(a, b); _t160 = *_hp; free(_hp); }
    (void)_t160;
    Bool _t161 = Bool_not(_t160);
    (void)_t161;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t161; return _r; }
}

Bool * U32_gte(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t162; { Bool *_hp = (Bool *)U32_lt(a, b); _t162 = *_hp; free(_hp); }
    (void)_t162;
    Bool _t163 = Bool_not(_t162);
    (void)_t163;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t163; return _r; }
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

Bool * U64_neq(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t175 = U64_eq(DEREF(a), DEREF(b));
    (void)_t175;
    Bool _t176 = Bool_not(_t175);
    (void)_t176;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t176; return _r; }
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

Bool * I64_lte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t248; { Bool *_hp = (Bool *)I64_gt(a, b); _t248 = *_hp; free(_hp); }
    (void)_t248;
    Bool _t249 = Bool_not(_t248);
    (void)_t249;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t249; return _r; }
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

Bool * Bool_lt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t272 = 0;
    (void)_t272;
    I64 _t273 = 1;
    (void)_t273;
    I64 _t274; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t274 = *_hp; free(_hp); }
    (void)_t274;
    I64 _t275 = I64_sub(_t272, _t273);
    (void)_t275;
    ;
    ;
    Bool _t276 = I64_eq(_t274, _t275);
    (void)_t276;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t276; return _r; }
}

Bool * Bool_gt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t277; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t277 = *_hp; free(_hp); }
    (void)_t277;
    I64 _t278 = 1;
    (void)_t278;
    Bool _t279 = I64_eq(_t277, _t278);
    (void)_t279;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t279; return _r; }
}

Bool * Bool_neq(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t280 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t280;
    Bool _t281 = Bool_not(_t280);
    (void)_t281;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t281; return _r; }
}

Bool * Bool_lte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t282; { Bool *_hp = (Bool *)Bool_gt(a, b); _t282 = *_hp; free(_hp); }
    (void)_t282;
    Bool _t283 = Bool_not(_t282);
    (void)_t283;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t283; return _r; }
}

Bool * Bool_gte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t284; { Bool *_hp = (Bool *)Bool_lt(a, b); _t284 = *_hp; free(_hp); }
    (void)_t284;
    Bool _t285 = Bool_not(_t284);
    (void)_t285;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t285; return _r; }
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

void print(Array * parts) {
    (void)parts;
    {
        U64 *_fi291 = malloc(sizeof(U64));
        *_fi291 = 0;
        (void)_fi291;
        while (1) {
            U64 _t293; { U64 *_hp = (U64 *)Array_len(parts); _t293 = *_hp; free(_hp); }
            (void)_t293;
            Bool _wcond292; { Bool *_hp = (Bool *)U64_lt(_fi291, &(U64){_t293}); _wcond292 = *_hp; free(_hp); }
            (void)_wcond292;
            ;
            if (_wcond292) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi291);
            (void)s;
            U64 _t294 = 1;
            (void)_t294;
            U64 _t295 = U64_add(DEREF(_fi291), _t294);
            (void)_t295;
            ;
            *_fi291 = _t295;
            ;
            print_single(s);
        }
        U64_delete(_fi291, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
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
    I32 _t315 = 0;
    (void)_t315;
    memset(src, _t315, size);
    ;
}

I64 * wait_cmd(I64 * pid) {
    (void)pid;
    while (1) {
        I64 status = check_cmd_status(DEREF(pid));
        (void)status;
        I64 _t316 = 0;
        (void)_t316;
        I64 _t317 = 1;
        (void)_t317;
        I64 _t318 = I64_sub(_t316, _t317);
        (void)_t318;
        ;
        ;
        Bool _t319; { Bool *_hp = (Bool *)I64_neq(&(I64){status}, &(I64){_t318}); _t319 = *_hp; free(_hp); }
        (void)_t319;
        ;
        if (_t319) {
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = status; return _r; }
        }
        ;
        ;
        I64 _t320 = 50;
        (void)_t320;
        sleep_ms(_t320);
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
        U64 _t326; { U64 *_hp = (U64 *)Array_len(args); _t326 = *_hp; free(_hp); }
        (void)_t326;
        Bool _wcond321; { Bool *_hp = (Bool *)U64_lt(i, &(U64){_t326}); _wcond321 = *_hp; free(_hp); }
        (void)_wcond321;
        ;
        if (_wcond321) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, i);
        (void)arg;
        U64 _t327 = 0;
        (void)_t327;
        Bool _t328; { Bool *_hp = (Bool *)U64_gt(i, &(U64){_t327}); _t328 = *_hp; free(_hp); }
        (void)_t328;
        ;
        if (_t328) {
            Str *_t322 = Str_lit(" '", 2ULL);
            (void)_t322;
            Str *_t323 = Str_concat(cmd, _t322);
            (void)_t323;
            Str_delete(_t322, &(Bool){1});
            Str *_t324 = Str_concat(_t323, arg);
            (void)_t324;
            Str_delete(_t323, &(Bool){1});
            Str *_t325 = Str_lit("'", 1ULL);
            (void)_t325;
            cmd = Str_concat(_t324, _t325);
            Str_delete(_t324, &(Bool){1});
            Str_delete(_t325, &(Bool){1});
        } else {
            cmd = Str_clone(arg);
        }
        ;
        U64 _t329 = 1;
        (void)_t329;
        U64 _t330 = U64_add(DEREF(i), _t329);
        (void)_t330;
        ;
        *i = _t330;
        ;
    }
    Array_delete(args, &(Bool){1});
    U64_delete(i, &(Bool){1});
    Str *tmpf = Str_lit("tmp/_run_cmd_out", 16ULL);
    (void)tmpf;
    Str *_t331 = Str_lit(" > ", 3ULL);
    (void)_t331;
    Str *_t332 = Str_concat(cmd, _t331);
    (void)_t332;
    Str_delete(_t331, &(Bool){1});
    Str_delete(cmd, &(Bool){1});
    Str *_t333 = Str_concat(_t332, tmpf);
    (void)_t333;
    Str_delete(_t332, &(Bool){1});
    Str *_t334 = Str_lit(" 2>&1", 5ULL);
    (void)_t334;
    Str *_t335 = Str_concat(_t333, _t334);
    (void)_t335;
    Str_delete(_t333, &(Bool){1});
    Str_delete(_t334, &(Bool){1});
    I64 pid; { I64 *_hp = (I64 *)spawn_cmd(_t335); pid = *_hp; free(_hp); }
    (void)pid;
    Str_delete(_t335, &(Bool){1});
    I64 ec; { I64 *_hp = (I64 *)wait_cmd(&(I64){pid}); ec = *_hp; free(_hp); }
    (void)ec;
    ;
    Str *content = readfile(tmpf);
    (void)content;
    Str_delete(tmpf, &(Bool){1});
    U64 _t336; { U64 *_hp = (U64 *)Str_size(); _t336 = *_hp; free(_hp); }
    (void)_t336;
    memcpy(output, content, _t336);
    ;
    free(content);
    { I64 *_r = malloc(sizeof(I64)); *_r = ec; return _r; }
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

void TODO(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t347 = Str_lit("Str", 3ULL);
    (void)_t347;
    U64 _t348; { U64 *_hp = (U64 *)Str_size(); _t348 = *_hp; free(_hp); }
    (void)_t348;
    U64 _t349 = 2;
    (void)_t349;
    Array *_va1 = Array_new(_t347, &(U64){_t348}, &(U64){_t349});
    (void)_va1;
    Str_delete(_t347, &(Bool){1});
    ;
    ;
    U64 _t350 = 0;
    (void)_t350;
    Str *_t351 = Str_lit("TODO: ", 6ULL);
    (void)_t351;
    Array_set(_va1, &(U64){_t350}, _t351);
    ;
    U64 _t352 = 1;
    (void)_t352;
    Str *_t353 = format(parts);
    (void)_t353;
    Array_set(_va1, &(U64){_t352}, _t353);
    ;
    panic(loc_str, _va1);
}

void UNREACHABLE(Str * loc_str) {
    (void)loc_str;
    Str *_t354 = Str_lit("Str", 3ULL);
    (void)_t354;
    U64 _t355; { U64 *_hp = (U64 *)Str_size(); _t355 = *_hp; free(_hp); }
    (void)_t355;
    U64 _t356 = 1;
    (void)_t356;
    Array *_va2 = Array_new(_t354, &(U64){_t355}, &(U64){_t356});
    (void)_va2;
    Str_delete(_t354, &(Bool){1});
    ;
    ;
    U64 _t357 = 0;
    (void)_t357;
    Str *_t358 = Str_lit("unreachable", 11ULL);
    (void)_t358;
    Array_set(_va2, &(U64){_t357}, _t358);
    ;
    panic(loc_str, _va2);
}

Bool * assert(Str * loc_str, Bool * cond) {
    (void)loc_str;
    (void)cond;
    Bool _t364 = Bool_not(DEREF(cond));
    (void)_t364;
    if (_t364) {
        Str *_t359 = Str_lit("Str", 3ULL);
        (void)_t359;
        U64 _t360; { U64 *_hp = (U64 *)Str_size(); _t360 = *_hp; free(_hp); }
        (void)_t360;
        U64 _t361 = 1;
        (void)_t361;
        Array *_va3 = Array_new(_t359, &(U64){_t360}, &(U64){_t361});
        (void)_va3;
        Str_delete(_t359, &(Bool){1});
        ;
        ;
        U64 _t362 = 0;
        (void)_t362;
        Str *_t363 = Str_lit("assert failed", 13ULL);
        (void)_t363;
        Array_set(_va3, &(U64){_t362}, _t363);
        ;
        panic(loc_str, _va3);
    }
    ;
    Bool _t365 = 1;
    (void)_t365;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t365; return _r; }
}

void expect(Str * loc_str, Bool * cond, Array * parts) {
    (void)loc_str;
    (void)cond;
    (void)parts;
    Bool _t373 = Bool_not(DEREF(cond));
    (void)_t373;
    if (_t373) {
        Str *_t366 = Str_lit("Str", 3ULL);
        (void)_t366;
        U64 _t367; { U64 *_hp = (U64 *)Str_size(); _t367 = *_hp; free(_hp); }
        (void)_t367;
        U64 _t368 = 2;
        (void)_t368;
        Array *_va4 = Array_new(_t366, &(U64){_t367}, &(U64){_t368});
        (void)_va4;
        Str_delete(_t366, &(Bool){1});
        ;
        ;
        U64 _t369 = 0;
        (void)_t369;
        Str *_t370 = Str_lit("assert failed: ", 15ULL);
        (void)_t370;
        Array_set(_va4, &(U64){_t369}, _t370);
        ;
        U64 _t371 = 1;
        (void)_t371;
        Str *_t372 = format(parts);
        (void)_t372;
        Array_set(_va4, &(U64){_t371}, _t372);
        ;
        panic(loc_str, _va4);
    }
    ;
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t387; { Bool *_hp = (Bool *)I64_neq(a, b); _t387 = *_hp; free(_hp); }
    (void)_t387;
    if (_t387) {
        Str *_t374 = Str_lit("Str", 3ULL);
        (void)_t374;
        U64 _t375; { U64 *_hp = (U64 *)Str_size(); _t375 = *_hp; free(_hp); }
        (void)_t375;
        U64 _t376 = 5;
        (void)_t376;
        Array *_va5 = Array_new(_t374, &(U64){_t375}, &(U64){_t376});
        (void)_va5;
        Str_delete(_t374, &(Bool){1});
        ;
        ;
        U64 _t377 = 0;
        (void)_t377;
        Str *_t378 = Str_lit("assert_eq failed: expected '", 28ULL);
        (void)_t378;
        Array_set(_va5, &(U64){_t377}, _t378);
        ;
        U64 _t379 = 1;
        (void)_t379;
        Str *_t380 = I64_to_str(a);
        (void)_t380;
        Array_set(_va5, &(U64){_t379}, _t380);
        ;
        U64 _t381 = 2;
        (void)_t381;
        Str *_t382 = Str_lit("', found '", 10ULL);
        (void)_t382;
        Array_set(_va5, &(U64){_t381}, _t382);
        ;
        U64 _t383 = 3;
        (void)_t383;
        Str *_t384 = I64_to_str(b);
        (void)_t384;
        Array_set(_va5, &(U64){_t383}, _t384);
        ;
        U64 _t385 = 4;
        (void)_t385;
        Str *_t386 = Str_lit("'", 1ULL);
        (void)_t386;
        Array_set(_va5, &(U64){_t385}, _t386);
        ;
        panic(loc_str, _va5);
    }
    ;
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t401; { Bool *_hp = (Bool *)Str_eq(a, b); _t401 = *_hp; free(_hp); }
    (void)_t401;
    Bool _t402 = Bool_not(_t401);
    (void)_t402;
    ;
    if (_t402) {
        Str *_t388 = Str_lit("Str", 3ULL);
        (void)_t388;
        U64 _t389; { U64 *_hp = (U64 *)Str_size(); _t389 = *_hp; free(_hp); }
        (void)_t389;
        U64 _t390 = 5;
        (void)_t390;
        Array *_va6 = Array_new(_t388, &(U64){_t389}, &(U64){_t390});
        (void)_va6;
        Str_delete(_t388, &(Bool){1});
        ;
        ;
        U64 _t391 = 0;
        (void)_t391;
        Str *_t392 = Str_lit("assert_eq_str failed: expected '", 32ULL);
        (void)_t392;
        Array_set(_va6, &(U64){_t391}, _t392);
        ;
        U64 _t393 = 1;
        (void)_t393;
        Str *_t394 = Str_clone(a);
        (void)_t394;
        Array_set(_va6, &(U64){_t393}, _t394);
        ;
        U64 _t395 = 2;
        (void)_t395;
        Str *_t396 = Str_lit("', found '", 10ULL);
        (void)_t396;
        Array_set(_va6, &(U64){_t395}, _t396);
        ;
        U64 _t397 = 3;
        (void)_t397;
        Str *_t398 = Str_clone(b);
        (void)_t398;
        Array_set(_va6, &(U64){_t397}, _t398);
        ;
        U64 _t399 = 4;
        (void)_t399;
        Str *_t400 = Str_lit("'", 1ULL);
        (void)_t400;
        Array_set(_va6, &(U64){_t399}, _t400);
        ;
        panic(loc_str, _va6);
    }
    ;
}

