#include "modes_ast.h"

Str * til_type_name_c(TilType * t) {
    (void)t;
    {
        TilType *_sw2285 = TilType_clone(t);
        (void)_sw2285;
        Bool _t2320; { Bool *_hp = (Bool *)TilType_eq(_sw2285, TilType_Unknown()); _t2320 = *_hp; free(_hp); }
        (void)_t2320;
        if (_t2320) {
            Str *_t2286 = Str_lit("unknown", 7ULL);
            (void)_t2286;
            TilType_delete(_sw2285, &(Bool){1});
            ;
            return _t2286;
        } else {
            Bool _t2319; { Bool *_hp = (Bool *)TilType_eq(_sw2285, TilType_None()); _t2319 = *_hp; free(_hp); }
            (void)_t2319;
            if (_t2319) {
                Str *_t2287 = Str_lit("None", 4ULL);
                (void)_t2287;
                ;
                TilType_delete(_sw2285, &(Bool){1});
                ;
                return _t2287;
            } else {
                Bool _t2318; { Bool *_hp = (Bool *)TilType_eq(_sw2285, TilType_I64()); _t2318 = *_hp; free(_hp); }
                (void)_t2318;
                if (_t2318) {
                    Str *_t2288 = Str_lit("I64", 3ULL);
                    (void)_t2288;
                    ;
                    ;
                    TilType_delete(_sw2285, &(Bool){1});
                    ;
                    return _t2288;
                } else {
                    Bool _t2317; { Bool *_hp = (Bool *)TilType_eq(_sw2285, TilType_U8()); _t2317 = *_hp; free(_hp); }
                    (void)_t2317;
                    if (_t2317) {
                        Str *_t2289 = Str_lit("U8", 2ULL);
                        (void)_t2289;
                        ;
                        ;
                        ;
                        TilType_delete(_sw2285, &(Bool){1});
                        ;
                        return _t2289;
                    } else {
                        Bool _t2316; { Bool *_hp = (Bool *)TilType_eq(_sw2285, TilType_I16()); _t2316 = *_hp; free(_hp); }
                        (void)_t2316;
                        if (_t2316) {
                            Str *_t2290 = Str_lit("I16", 3ULL);
                            (void)_t2290;
                            ;
                            ;
                            ;
                            ;
                            TilType_delete(_sw2285, &(Bool){1});
                            ;
                            return _t2290;
                        } else {
                            Bool _t2315; { Bool *_hp = (Bool *)TilType_eq(_sw2285, TilType_I32()); _t2315 = *_hp; free(_hp); }
                            (void)_t2315;
                            if (_t2315) {
                                Str *_t2291 = Str_lit("I32", 3ULL);
                                (void)_t2291;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TilType_delete(_sw2285, &(Bool){1});
                                ;
                                return _t2291;
                            } else {
                                Bool _t2314; { Bool *_hp = (Bool *)TilType_eq(_sw2285, TilType_U32()); _t2314 = *_hp; free(_hp); }
                                (void)_t2314;
                                if (_t2314) {
                                    Str *_t2292 = Str_lit("U32", 3ULL);
                                    (void)_t2292;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TilType_delete(_sw2285, &(Bool){1});
                                    ;
                                    return _t2292;
                                } else {
                                    Bool _t2313; { Bool *_hp = (Bool *)TilType_eq(_sw2285, TilType_U64()); _t2313 = *_hp; free(_hp); }
                                    (void)_t2313;
                                    if (_t2313) {
                                        Str *_t2293 = Str_lit("U64", 3ULL);
                                        (void)_t2293;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TilType_delete(_sw2285, &(Bool){1});
                                        ;
                                        return _t2293;
                                    } else {
                                        Bool _t2312; { Bool *_hp = (Bool *)TilType_eq(_sw2285, TilType_F32()); _t2312 = *_hp; free(_hp); }
                                        (void)_t2312;
                                        if (_t2312) {
                                            Str *_t2294 = Str_lit("F32", 3ULL);
                                            (void)_t2294;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TilType_delete(_sw2285, &(Bool){1});
                                            ;
                                            return _t2294;
                                        } else {
                                            Bool _t2311; { Bool *_hp = (Bool *)TilType_eq(_sw2285, TilType_Bool()); _t2311 = *_hp; free(_hp); }
                                            (void)_t2311;
                                            if (_t2311) {
                                                Str *_t2295 = Str_lit("Bool", 4ULL);
                                                (void)_t2295;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                TilType_delete(_sw2285, &(Bool){1});
                                                ;
                                                return _t2295;
                                            } else {
                                                Bool _t2310; { Bool *_hp = (Bool *)TilType_eq(_sw2285, TilType_Struct()); _t2310 = *_hp; free(_hp); }
                                                (void)_t2310;
                                                if (_t2310) {
                                                    Str *_t2296 = Str_lit("Struct", 6ULL);
                                                    (void)_t2296;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    TilType_delete(_sw2285, &(Bool){1});
                                                    ;
                                                    return _t2296;
                                                } else {
                                                    Bool _t2309; { Bool *_hp = (Bool *)TilType_eq(_sw2285, TilType_StructDef()); _t2309 = *_hp; free(_hp); }
                                                    (void)_t2309;
                                                    if (_t2309) {
                                                        Str *_t2297 = Str_lit("StructDef", 9ULL);
                                                        (void)_t2297;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        TilType_delete(_sw2285, &(Bool){1});
                                                        ;
                                                        return _t2297;
                                                    } else {
                                                        Bool _t2308; { Bool *_hp = (Bool *)TilType_eq(_sw2285, TilType_Enum()); _t2308 = *_hp; free(_hp); }
                                                        (void)_t2308;
                                                        if (_t2308) {
                                                            Str *_t2298 = Str_lit("Enum", 4ULL);
                                                            (void)_t2298;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            TilType_delete(_sw2285, &(Bool){1});
                                                            ;
                                                            return _t2298;
                                                        } else {
                                                            Bool _t2307; { Bool *_hp = (Bool *)TilType_eq(_sw2285, TilType_EnumDef()); _t2307 = *_hp; free(_hp); }
                                                            (void)_t2307;
                                                            if (_t2307) {
                                                                Str *_t2299 = Str_lit("EnumDef", 7ULL);
                                                                (void)_t2299;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                TilType_delete(_sw2285, &(Bool){1});
                                                                ;
                                                                return _t2299;
                                                            } else {
                                                                Bool _t2306; { Bool *_hp = (Bool *)TilType_eq(_sw2285, TilType_FuncDef()); _t2306 = *_hp; free(_hp); }
                                                                (void)_t2306;
                                                                if (_t2306) {
                                                                    Str *_t2300 = Str_lit("FunctionDef", 11ULL);
                                                                    (void)_t2300;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    TilType_delete(_sw2285, &(Bool){1});
                                                                    ;
                                                                    return _t2300;
                                                                } else {
                                                                    Bool _t2305; { Bool *_hp = (Bool *)TilType_eq(_sw2285, TilType_FuncPtr()); _t2305 = *_hp; free(_hp); }
                                                                    (void)_t2305;
                                                                    if (_t2305) {
                                                                        Str *_t2301 = Str_lit("Fn", 2ULL);
                                                                        (void)_t2301;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        TilType_delete(_sw2285, &(Bool){1});
                                                                        ;
                                                                        return _t2301;
                                                                    } else {
                                                                        Bool _t2304; { Bool *_hp = (Bool *)TilType_eq(_sw2285, TilType_Dynamic()); _t2304 = *_hp; free(_hp); }
                                                                        (void)_t2304;
                                                                        if (_t2304) {
                                                                            Str *_t2302 = Str_lit("Dynamic", 7ULL);
                                                                            (void)_t2302;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TilType_delete(_sw2285, &(Bool){1});
                                                                            ;
                                                                            return _t2302;
                                                                        } else {
                                                                            Str *_t2303 = Str_lit("?", 1ULL);
                                                                            (void)_t2303;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TilType_delete(_sw2285, &(Bool){1});
                                                                            ;
                                                                            return _t2303;
                                                                        }
                                                                        ;
                                                                    }
                                                                    ;
                                                                }
                                                                ;
                                                            }
                                                            ;
                                                        }
                                                        ;
                                                    }
                                                    ;
                                                }
                                                ;
                                            }
                                            ;
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        TilType_delete(_sw2285, &(Bool){1});
        ;
    }
}

Bool * Declaration_eq(Declaration * a, Declaration * b) {
    (void)a;
    (void)b;
    Bool _t2321; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t2321 = *_hp; free(_hp); }
    (void)_t2321;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2321; return _r; }
}

Str * Declaration_to_str(Declaration * self) {
    (void)self;
    { Str *_r = malloc(sizeof(Str)); *_r = self->name; return _r; }
}

Declaration * Declaration_clone(Declaration * self) {
    (void)self;
    Bool _t2322 = Bool_clone(&self->is_mut);
    (void)_t2322;
    Bool _t2323 = Bool_clone(&self->is_namespace);
    (void)_t2323;
    Bool _t2324 = Bool_clone(&self->is_ref);
    (void)_t2324;
    Bool _t2325 = Bool_clone(&self->is_own);
    (void)_t2325;
    I32 _t2326 = I32_clone(&self->field_offset);
    (void)_t2326;
    I32 _t2327 = I32_clone(&self->field_size);
    (void)_t2327;
    Declaration *_t2328 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); _t2328->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); _t2328->explicit_type = *_ca; free(_ca); }
    _t2328->is_mut = _t2322;
    _t2328->is_namespace = _t2323;
    _t2328->is_ref = _t2324;
    _t2328->is_own = _t2325;
    _t2328->field_offset = _t2326;
    _t2328->field_size = _t2327;
    _t2328->field_struct_def = self->field_struct_def;
    _t2328->fn_sig = self->fn_sig;
    (void)_t2328;
    ;
    ;
    ;
    ;
    ;
    ;
    return _t2328;
}

U64 *Declaration_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Declaration);
    return r;
}

void Expr_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Str *_t2652 = Str_lit("Str", 3ULL);
    (void)_t2652;
    U64 _t2653; { U64 *_hp = (U64 *)Str_size(); _t2653 = *_hp; free(_hp); }
    (void)_t2653;
    U64 _t2654 = 7;
    (void)_t2654;
    Array *_va35 = Array_new(_t2652, &(U64){_t2653}, &(U64){_t2654});
    (void)_va35;
    Str_delete(_t2652, &(Bool){1});
    ;
    ;
    U64 _t2655 = 0;
    (void)_t2655;
    Str *_t2656 = Str_clone(&self->path);
    (void)_t2656;
    Array_set(_va35, &(U64){_t2655}, _t2656);
    ;
    U64 _t2657 = 1;
    (void)_t2657;
    Str *_t2658 = Str_lit(":", 1ULL);
    (void)_t2658;
    Array_set(_va35, &(U64){_t2657}, _t2658);
    ;
    U64 _t2659 = 2;
    (void)_t2659;
    Str *_t2660 = U32_to_str(&self->line);
    (void)_t2660;
    Array_set(_va35, &(U64){_t2659}, _t2660);
    ;
    U64 _t2661 = 3;
    (void)_t2661;
    Str *_t2662 = Str_lit(":", 1ULL);
    (void)_t2662;
    Array_set(_va35, &(U64){_t2661}, _t2662);
    ;
    U64 _t2663 = 4;
    (void)_t2663;
    Str *_t2664 = U32_to_str(&self->col);
    (void)_t2664;
    Array_set(_va35, &(U64){_t2663}, _t2664);
    ;
    U64 _t2665 = 5;
    (void)_t2665;
    Str *_t2666 = Str_lit(": error: ", 9ULL);
    (void)_t2666;
    Array_set(_va35, &(U64){_t2665}, _t2666);
    ;
    U64 _t2667 = 6;
    (void)_t2667;
    Str *_t2668 = Str_clone(msg);
    (void)_t2668;
    Array_set(_va35, &(U64){_t2667}, _t2668);
    ;
    println(_va35);
}

void Expr_todo_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Expr_error(self, msg);
    Str *_t2669 = Str_lit("Str", 3ULL);
    (void)_t2669;
    U64 _t2670; { U64 *_hp = (U64 *)Str_size(); _t2670 = *_hp; free(_hp); }
    (void)_t2670;
    U64 _t2671 = 1;
    (void)_t2671;
    Array *_va36 = Array_new(_t2669, &(U64){_t2670}, &(U64){_t2671});
    (void)_va36;
    Str_delete(_t2669, &(Bool){1});
    ;
    ;
    U64 _t2672 = 0;
    (void)_t2672;
    Str *_t2673 = Str_lit("  note: this language feature is not implemented yet", 52ULL);
    (void)_t2673;
    Array_set(_va36, &(U64){_t2672}, _t2673);
    ;
    println(_va36);
}

void Expr_lang_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Expr_error(self, msg);
    Str *_t2674 = Str_lit("Str", 3ULL);
    (void)_t2674;
    U64 _t2675; { U64 *_hp = (U64 *)Str_size(); _t2675 = *_hp; free(_hp); }
    (void)_t2675;
    U64 _t2676 = 1;
    (void)_t2676;
    Array *_va37 = Array_new(_t2674, &(U64){_t2675}, &(U64){_t2676});
    (void)_va37;
    Str_delete(_t2674, &(Bool){1});
    ;
    ;
    U64 _t2677 = 0;
    (void)_t2677;
    Str *_t2678 = Str_lit("  note: this is a bug in the language, please report it", 55ULL);
    (void)_t2678;
    Array_set(_va37, &(U64){_t2677}, _t2678);
    ;
    println(_va37);
}

void Expr_add_child(Expr * self, Expr * child) {
    (void)self;
    (void)child;
    Vec_push(&self->children, child);
}

Expr * Expr_child(Expr * parent, I64 * i) {
    (void)parent;
    (void)i;
    U64 *_t2679 = malloc(sizeof(U64)); *_t2679 = I64_to_u64(DEREF(i));
    (void)_t2679;
    Expr *c = Vec_get(&parent->children, _t2679);
    (void)c;
    U64_delete(_t2679, &(Bool){1});
    return c;
}

I64 * Expr_child_count(Expr * parent) {
    (void)parent;
    U64 _t2680; { U64 *_hp = (U64 *)Vec_len(&parent->children); _t2680 = *_hp; free(_hp); }
    (void)_t2680;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t2680; return _r; }
}

Expr * Expr_new(ExprData * data, U32 line, U32 col, Str * path) {
    (void)data;
    (void)line;
    (void)col;
    (void)path;
    I64 _t2681 = 0;
    (void)_t2681;
    I64 _t2682 = 1;
    (void)_t2682;
    I64 _t2683 = I64_sub(_t2681, _t2682);
    (void)_t2683;
    ;
    ;
    I64 _t2684 = 0;
    (void)_t2684;
    I64 _t2685 = 1;
    (void)_t2685;
    I64 _t2686 = I64_sub(_t2684, _t2685);
    (void)_t2686;
    ;
    ;
    Str *_t2687 = Str_lit("", 0ULL);
    (void)_t2687;
    U64 _t2688; { U64 *_hp = (U64 *)Expr_size(); _t2688 = *_hp; free(_hp); }
    (void)_t2688;
    Bool _t2689 = 0;
    (void)_t2689;
    Bool _t2690 = 0;
    (void)_t2690;
    Bool _t2691 = 0;
    (void)_t2691;
    Bool _t2692 = 0;
    (void)_t2692;
    Bool _t2693 = 0;
    (void)_t2693;
    Bool _t2694 = 0;
    (void)_t2694;
    Bool _t2695 = 0;
    (void)_t2695;
    Bool _t2696 = 0;
    (void)_t2696;
    I32 _t2697 = 0;
    (void)_t2697;
    I32 _t2698 = I64_to_i32(_t2683);
    (void)_t2698;
    ;
    U32 _t2699 = 0;
    (void)_t2699;
    I32 _t2700 = I64_to_i32(_t2686);
    (void)_t2700;
    ;
    U32 _t2701 = 0;
    (void)_t2701;
    U32 _t2702 = U32_clone(&(U32){col});
    (void)_t2702;
    Str *_t2703 = Str_clone(path);
    (void)_t2703;
    Expr *_t2704 = malloc(sizeof(Expr));
    { ExprData *_ca = ExprData_clone(data); _t2704->data = *_ca; free(_ca); }
    { TilType *_ca = TilType_clone(TilType_Unknown()); _t2704->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t2704->struct_name = *_ca; free(_ca); }
    _t2704->is_own_arg = _t2689;
    _t2704->is_splat = _t2690;
    _t2704->is_own_field = _t2691;
    _t2704->is_ref_field = _t2692;
    _t2704->is_ns_field = _t2693;
    _t2704->is_ext = _t2694;
    _t2704->is_core = _t2695;
    _t2704->save_old_delete = _t2696;
    _t2704->total_struct_size = _t2697;
    _t2704->variadic_index = _t2698;
    _t2704->variadic_count = _t2699;
    _t2704->kwargs_index = _t2700;
    _t2704->kwargs_count = _t2701;
    _t2704->fn_sig = NULL;
    { Vec *_ca = Vec_new(_t2687, &(U64){_t2688}); _t2704->children = *_ca; free(_ca); }
    _t2704->line = U32_clone(&(U32){line});
    _t2704->col = _t2702;
    { Str *_ca = Str_clone(_t2703); _t2704->path = *_ca; free(_ca); }
    (void)_t2704;
    Str_delete(_t2687, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    Str_delete(_t2703, &(Bool){1});
    return _t2704;
}

Expr * Expr_clone(Expr * self) {
    (void)self;
    Str *_t2716 = Str_lit("", 0ULL);
    (void)_t2716;
    U64 _t2717; { U64 *_hp = (U64 *)Expr_size(); _t2717 = *_hp; free(_hp); }
    (void)_t2717;
    Vec *new_children = Vec_new(_t2716, &(U64){_t2717});
    (void)new_children;
    Str_delete(_t2716, &(Bool){1});
    ;
    {
        U64 _fi2705 = 0;
        (void)_fi2705;
        while (1) {
            U64 _t2707 = 0;
            (void)_t2707;
            U64 _t2708; { U64 *_hp = (U64 *)Vec_len(&self->children); _t2708 = *_hp; free(_hp); }
            (void)_t2708;
            Range *_t2709 = Range_new(_t2707, _t2708);
            (void)_t2709;
            ;
            ;
            U64 _t2710; { U64 *_hp = (U64 *)Range_len(_t2709); _t2710 = *_hp; free(_hp); }
            (void)_t2710;
            Range_delete(_t2709, &(Bool){1});
            Bool _wcond2706; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2705}, &(U64){_t2710}); _wcond2706 = *_hp; free(_hp); }
            (void)_wcond2706;
            ;
            if (_wcond2706) {
            } else {
                ;
                break;
            }
            ;
            U64 _t2711 = 0;
            (void)_t2711;
            U64 _t2712; { U64 *_hp = (U64 *)Vec_len(&self->children); _t2712 = *_hp; free(_hp); }
            (void)_t2712;
            Range *_t2713 = Range_new(_t2711, _t2712);
            (void)_t2713;
            ;
            ;
            U64 *i = Range_get(_t2713, _fi2705);
            (void)i;
            Range_delete(_t2713, &(Bool){1});
            U64 _t2714 = 1;
            (void)_t2714;
            U64 _t2715 = U64_add(_fi2705, _t2714);
            (void)_t2715;
            ;
            _fi2705 = _t2715;
            ;
            Expr *c = Vec_get(&self->children, i);
            (void)c;
            Expr *cloned = Expr_clone(c);
            (void)cloned;
            U64_delete(i, &(Bool){1});
            Vec_push(new_children, cloned);
        }
        ;
    }
    Expr *_t2718 = malloc(sizeof(Expr));
    { ExprData *_ca = ExprData_clone(&self->data); _t2718->data = *_ca; free(_ca); }
    { TilType *_ca = TilType_clone(&self->til_type); _t2718->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->struct_name); _t2718->struct_name = *_ca; free(_ca); }
    _t2718->is_own_arg = self->is_own_arg;
    _t2718->is_splat = self->is_splat;
    _t2718->is_own_field = self->is_own_field;
    _t2718->is_ref_field = self->is_ref_field;
    _t2718->is_ns_field = self->is_ns_field;
    _t2718->is_ext = self->is_ext;
    _t2718->is_core = self->is_core;
    _t2718->save_old_delete = self->save_old_delete;
    _t2718->total_struct_size = self->total_struct_size;
    _t2718->variadic_index = self->variadic_index;
    _t2718->variadic_count = self->variadic_count;
    _t2718->kwargs_index = self->kwargs_index;
    _t2718->kwargs_count = self->kwargs_count;
    _t2718->fn_sig = self->fn_sig;
    { Vec *_ca = Vec_clone(new_children); _t2718->children = *_ca; free(_ca); }
    _t2718->line = self->line;
    _t2718->col = self->col;
    { Str *_ca = Str_clone(&self->path); _t2718->path = *_ca; free(_ca); }
    (void)_t2718;
    Vec_delete(new_children, &(Bool){1});
    return _t2718;
}

U64 *Expr_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Expr);
    return r;
}

Str * node_name(ExprData * data) {
    (void)data;
    {
        ExprData *_sw2740 = ExprData_clone(data);
        (void)_sw2740;
        Bool _t2791; { Bool *_hp = (Bool *)ExprData_eq(_sw2740, ExprData_Body()); _t2791 = *_hp; free(_hp); }
        (void)_t2791;
        if (_t2791) {
            Str *_t2741 = Str_lit("body", 4ULL);
            (void)_t2741;
            ExprData_delete(_sw2740, &(Bool){1});
            ;
            return _t2741;
        } else {
            Bool _t2790; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw2740); _t2790 = *_hp; free(_hp); }
            (void)_t2790;
            if (_t2790) {
                Str *_t2742 = Str_lit("str", 3ULL);
                (void)_t2742;
                ;
                ExprData_delete(_sw2740, &(Bool){1});
                ;
                return _t2742;
            } else {
                Bool _t2789; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw2740); _t2789 = *_hp; free(_hp); }
                (void)_t2789;
                if (_t2789) {
                    Str *_t2743 = Str_lit("num", 3ULL);
                    (void)_t2743;
                    ;
                    ;
                    ExprData_delete(_sw2740, &(Bool){1});
                    ;
                    return _t2743;
                } else {
                    Bool _t2788; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw2740); _t2788 = *_hp; free(_hp); }
                    (void)_t2788;
                    if (_t2788) {
                        Str *_t2744 = Str_lit("bool", 4ULL);
                        (void)_t2744;
                        ;
                        ;
                        ;
                        ExprData_delete(_sw2740, &(Bool){1});
                        ;
                        return _t2744;
                    } else {
                        Bool _t2787; { Bool *_hp = (Bool *)ExprData_eq(_sw2740, ExprData_LiteralNull()); _t2787 = *_hp; free(_hp); }
                        (void)_t2787;
                        if (_t2787) {
                            Str *_t2745 = Str_lit("null", 4ULL);
                            (void)_t2745;
                            ;
                            ;
                            ;
                            ;
                            ExprData_delete(_sw2740, &(Bool){1});
                            ;
                            return _t2745;
                        } else {
                            Bool _t2786; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw2740); _t2786 = *_hp; free(_hp); }
                            (void)_t2786;
                            if (_t2786) {
                                Str *_t2746 = Str_lit("ident", 5ULL);
                                (void)_t2746;
                                ;
                                ;
                                ;
                                ;
                                ;
                                ExprData_delete(_sw2740, &(Bool){1});
                                ;
                                return _t2746;
                            } else {
                                Bool _t2785; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw2740); _t2785 = *_hp; free(_hp); }
                                (void)_t2785;
                                if (_t2785) {
                                    Str *_t2747 = Str_lit("decl", 4ULL);
                                    (void)_t2747;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ExprData_delete(_sw2740, &(Bool){1});
                                    ;
                                    return _t2747;
                                } else {
                                    Bool _t2784; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw2740); _t2784 = *_hp; free(_hp); }
                                    (void)_t2784;
                                    if (_t2784) {
                                        Str *_t2748 = Str_lit("assign", 6ULL);
                                        (void)_t2748;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ExprData_delete(_sw2740, &(Bool){1});
                                        ;
                                        return _t2748;
                                    } else {
                                        Bool _t2783; { Bool *_hp = (Bool *)ExprData_eq(_sw2740, ExprData_FCall()); _t2783 = *_hp; free(_hp); }
                                        (void)_t2783;
                                        if (_t2783) {
                                            Str *_t2749 = Str_lit("fcall", 5ULL);
                                            (void)_t2749;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ExprData_delete(_sw2740, &(Bool){1});
                                            ;
                                            return _t2749;
                                        } else {
                                            Bool _t2782; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw2740); _t2782 = *_hp; free(_hp); }
                                            (void)_t2782;
                                            if (_t2782) {
                                                Str *_t2750 = Str_lit("func_def", 8ULL);
                                                (void)_t2750;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ExprData_delete(_sw2740, &(Bool){1});
                                                ;
                                                return _t2750;
                                            } else {
                                                Bool _t2781; { Bool *_hp = (Bool *)ExprData_eq(_sw2740, ExprData_StructDef()); _t2781 = *_hp; free(_hp); }
                                                (void)_t2781;
                                                if (_t2781) {
                                                    Str *_t2751 = Str_lit("struct_def", 10ULL);
                                                    (void)_t2751;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ExprData_delete(_sw2740, &(Bool){1});
                                                    ;
                                                    return _t2751;
                                                } else {
                                                    Bool _t2780; { Bool *_hp = (Bool *)ExprData_eq(_sw2740, ExprData_EnumDef()); _t2780 = *_hp; free(_hp); }
                                                    (void)_t2780;
                                                    if (_t2780) {
                                                        Str *_t2752 = Str_lit("enum_def", 8ULL);
                                                        (void)_t2752;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ExprData_delete(_sw2740, &(Bool){1});
                                                        ;
                                                        return _t2752;
                                                    } else {
                                                        Bool _t2779; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(_sw2740); _t2779 = *_hp; free(_hp); }
                                                        (void)_t2779;
                                                        if (_t2779) {
                                                            Str *_t2753 = Str_lit("field_access", 12ULL);
                                                            (void)_t2753;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ExprData_delete(_sw2740, &(Bool){1});
                                                            ;
                                                            return _t2753;
                                                        } else {
                                                            Bool _t2778; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(_sw2740); _t2778 = *_hp; free(_hp); }
                                                            (void)_t2778;
                                                            if (_t2778) {
                                                                Str *_t2754 = Str_lit("field_assign", 12ULL);
                                                                (void)_t2754;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ExprData_delete(_sw2740, &(Bool){1});
                                                                ;
                                                                return _t2754;
                                                            } else {
                                                                Bool _t2777; { Bool *_hp = (Bool *)ExprData_eq(_sw2740, ExprData_Return()); _t2777 = *_hp; free(_hp); }
                                                                (void)_t2777;
                                                                if (_t2777) {
                                                                    Str *_t2755 = Str_lit("return", 6ULL);
                                                                    (void)_t2755;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ExprData_delete(_sw2740, &(Bool){1});
                                                                    ;
                                                                    return _t2755;
                                                                } else {
                                                                    Bool _t2776; { Bool *_hp = (Bool *)ExprData_eq(_sw2740, ExprData_If()); _t2776 = *_hp; free(_hp); }
                                                                    (void)_t2776;
                                                                    if (_t2776) {
                                                                        Str *_t2756 = Str_lit("if", 2ULL);
                                                                        (void)_t2756;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ExprData_delete(_sw2740, &(Bool){1});
                                                                        ;
                                                                        return _t2756;
                                                                    } else {
                                                                        Bool _t2775; { Bool *_hp = (Bool *)ExprData_eq(_sw2740, ExprData_While()); _t2775 = *_hp; free(_hp); }
                                                                        (void)_t2775;
                                                                        if (_t2775) {
                                                                            Str *_t2757 = Str_lit("while", 5ULL);
                                                                            (void)_t2757;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ExprData_delete(_sw2740, &(Bool){1});
                                                                            ;
                                                                            return _t2757;
                                                                        } else {
                                                                            Bool _t2774; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw2740); _t2774 = *_hp; free(_hp); }
                                                                            (void)_t2774;
                                                                            if (_t2774) {
                                                                                Str *_t2758 = Str_lit("for_in", 6ULL);
                                                                                (void)_t2758;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ExprData_delete(_sw2740, &(Bool){1});
                                                                                ;
                                                                                return _t2758;
                                                                            } else {
                                                                                Bool _t2773; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw2740); _t2773 = *_hp; free(_hp); }
                                                                                (void)_t2773;
                                                                                if (_t2773) {
                                                                                    Str *_t2759 = Str_lit("named_arg", 9ULL);
                                                                                    (void)_t2759;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ExprData_delete(_sw2740, &(Bool){1});
                                                                                    ;
                                                                                    return _t2759;
                                                                                } else {
                                                                                    Bool _t2772; { Bool *_hp = (Bool *)ExprData_eq(_sw2740, ExprData_Break()); _t2772 = *_hp; free(_hp); }
                                                                                    (void)_t2772;
                                                                                    if (_t2772) {
                                                                                        Str *_t2760 = Str_lit("break", 5ULL);
                                                                                        (void)_t2760;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ExprData_delete(_sw2740, &(Bool){1});
                                                                                        ;
                                                                                        return _t2760;
                                                                                    } else {
                                                                                        Bool _t2771; { Bool *_hp = (Bool *)ExprData_eq(_sw2740, ExprData_Continue()); _t2771 = *_hp; free(_hp); }
                                                                                        (void)_t2771;
                                                                                        if (_t2771) {
                                                                                            Str *_t2761 = Str_lit("continue", 8ULL);
                                                                                            (void)_t2761;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ExprData_delete(_sw2740, &(Bool){1});
                                                                                            ;
                                                                                            return _t2761;
                                                                                        } else {
                                                                                            Bool _t2770; { Bool *_hp = (Bool *)ExprData_eq(_sw2740, ExprData_MapLit()); _t2770 = *_hp; free(_hp); }
                                                                                            (void)_t2770;
                                                                                            if (_t2770) {
                                                                                                Str *_t2762 = Str_lit("map_lit", 7ULL);
                                                                                                (void)_t2762;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ExprData_delete(_sw2740, &(Bool){1});
                                                                                                ;
                                                                                                return _t2762;
                                                                                            } else {
                                                                                                Bool _t2769; { Bool *_hp = (Bool *)ExprData_eq(_sw2740, ExprData_SetLit()); _t2769 = *_hp; free(_hp); }
                                                                                                (void)_t2769;
                                                                                                if (_t2769) {
                                                                                                    Str *_t2763 = Str_lit("set_lit", 7ULL);
                                                                                                    (void)_t2763;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ExprData_delete(_sw2740, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t2763;
                                                                                                } else {
                                                                                                    Bool _t2768; { Bool *_hp = (Bool *)ExprData_eq(_sw2740, ExprData_Switch()); _t2768 = *_hp; free(_hp); }
                                                                                                    (void)_t2768;
                                                                                                    if (_t2768) {
                                                                                                        Str *_t2764 = Str_lit("switch", 6ULL);
                                                                                                        (void)_t2764;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ExprData_delete(_sw2740, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t2764;
                                                                                                    } else {
                                                                                                        Bool _t2767; { Bool *_hp = (Bool *)ExprData_eq(_sw2740, ExprData_Case()); _t2767 = *_hp; free(_hp); }
                                                                                                        (void)_t2767;
                                                                                                        if (_t2767) {
                                                                                                            Str *_t2765 = Str_lit("case", 4ULL);
                                                                                                            (void)_t2765;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ExprData_delete(_sw2740, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t2765;
                                                                                                        } else {
                                                                                                            Str *_t2766 = Str_lit("?", 1ULL);
                                                                                                            (void)_t2766;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ExprData_delete(_sw2740, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t2766;
                                                                                                        }
                                                                                                        ;
                                                                                                    }
                                                                                                    ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                            ;
                                                                                        }
                                                                                        ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                                ;
                                                                            }
                                                                            ;
                                                                        }
                                                                        ;
                                                                    }
                                                                    ;
                                                                }
                                                                ;
                                                            }
                                                            ;
                                                        }
                                                        ;
                                                    }
                                                    ;
                                                }
                                                ;
                                            }
                                            ;
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        ExprData_delete(_sw2740, &(Bool){1});
        ;
    }
}

Str * func_type_name(FuncType * ft) {
    (void)ft;
    {
        FuncType *_sw2792 = FuncType_clone(ft);
        (void)_sw2792;
        Bool _t2805; { Bool *_hp = (Bool *)FuncType_eq(_sw2792, FuncType_Func()); _t2805 = *_hp; free(_hp); }
        (void)_t2805;
        if (_t2805) {
            Str *_t2793 = Str_lit("func", 4ULL);
            (void)_t2793;
            FuncType_delete(_sw2792, &(Bool){1});
            ;
            return _t2793;
        } else {
            Bool _t2804; { Bool *_hp = (Bool *)FuncType_eq(_sw2792, FuncType_Proc()); _t2804 = *_hp; free(_hp); }
            (void)_t2804;
            if (_t2804) {
                Str *_t2794 = Str_lit("proc", 4ULL);
                (void)_t2794;
                ;
                FuncType_delete(_sw2792, &(Bool){1});
                ;
                return _t2794;
            } else {
                Bool _t2803; { Bool *_hp = (Bool *)FuncType_eq(_sw2792, FuncType_Test()); _t2803 = *_hp; free(_hp); }
                (void)_t2803;
                if (_t2803) {
                    Str *_t2795 = Str_lit("test", 4ULL);
                    (void)_t2795;
                    ;
                    ;
                    FuncType_delete(_sw2792, &(Bool){1});
                    ;
                    return _t2795;
                } else {
                    Bool _t2802; { Bool *_hp = (Bool *)FuncType_eq(_sw2792, FuncType_Macro()); _t2802 = *_hp; free(_hp); }
                    (void)_t2802;
                    if (_t2802) {
                        Str *_t2796 = Str_lit("macro", 5ULL);
                        (void)_t2796;
                        ;
                        ;
                        ;
                        FuncType_delete(_sw2792, &(Bool){1});
                        ;
                        return _t2796;
                    } else {
                        Bool _t2801; { Bool *_hp = (Bool *)FuncType_eq(_sw2792, FuncType_ExtFunc()); _t2801 = *_hp; free(_hp); }
                        (void)_t2801;
                        if (_t2801) {
                            Str *_t2797 = Str_lit("ext_func", 8ULL);
                            (void)_t2797;
                            ;
                            ;
                            ;
                            ;
                            FuncType_delete(_sw2792, &(Bool){1});
                            ;
                            return _t2797;
                        } else {
                            Bool _t2800; { Bool *_hp = (Bool *)FuncType_eq(_sw2792, FuncType_ExtProc()); _t2800 = *_hp; free(_hp); }
                            (void)_t2800;
                            if (_t2800) {
                                Str *_t2798 = Str_lit("ext_proc", 8ULL);
                                (void)_t2798;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw2792, &(Bool){1});
                                ;
                                return _t2798;
                            } else {
                                Str *_t2799 = Str_lit("?", 1ULL);
                                (void)_t2799;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw2792, &(Bool){1});
                                ;
                                return _t2799;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        FuncType_delete(_sw2792, &(Bool){1});
        ;
    }
}

void ast_print(Expr * e, U32 indent) {
    (void)e;
    (void)indent;
    {
        U64 _fi2806 = 0;
        (void)_fi2806;
        while (1) {
            I64 _t2808 = U32_to_i64(indent);
            (void)_t2808;
            U64 _t2809 = 0;
            (void)_t2809;
            U64 _t2810 = I64_to_u64(_t2808);
            (void)_t2810;
            ;
            Range *_t2811 = Range_new(_t2809, _t2810);
            (void)_t2811;
            ;
            ;
            U64 _t2812; { U64 *_hp = (U64 *)Range_len(_t2811); _t2812 = *_hp; free(_hp); }
            (void)_t2812;
            Range_delete(_t2811, &(Bool){1});
            Bool _wcond2807; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2806}, &(U64){_t2812}); _wcond2807 = *_hp; free(_hp); }
            (void)_wcond2807;
            ;
            if (_wcond2807) {
            } else {
                ;
                break;
            }
            ;
            I64 _t2813 = U32_to_i64(indent);
            (void)_t2813;
            U64 _t2814 = 0;
            (void)_t2814;
            U64 _t2815 = I64_to_u64(_t2813);
            (void)_t2815;
            ;
            Range *_t2816 = Range_new(_t2814, _t2815);
            (void)_t2816;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t2816, _fi2806); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t2816, &(Bool){1});
            ;
            U64 _t2817 = 1;
            (void)_t2817;
            U64 _t2818 = U64_add(_fi2806, _t2817);
            (void)_t2818;
            ;
            _fi2806 = _t2818;
            ;
            Str *_t2819 = Str_lit("Str", 3ULL);
            (void)_t2819;
            U64 _t2820; { U64 *_hp = (U64 *)Str_size(); _t2820 = *_hp; free(_hp); }
            (void)_t2820;
            U64 _t2821 = 1;
            (void)_t2821;
            Array *_va38 = Array_new(_t2819, &(U64){_t2820}, &(U64){_t2821});
            (void)_va38;
            Str_delete(_t2819, &(Bool){1});
            ;
            ;
            U64 _t2822 = 0;
            (void)_t2822;
            Str *_t2823 = Str_lit("  ", 2ULL);
            (void)_t2823;
            Array_set(_va38, &(U64){_t2822}, _t2823);
            ;
            print(_va38);
        }
        ;
    }
    Str *_t2957 = Str_lit("Str", 3ULL);
    (void)_t2957;
    U64 _t2958; { U64 *_hp = (U64 *)Str_size(); _t2958 = *_hp; free(_hp); }
    (void)_t2958;
    U64 _t2959 = 2;
    (void)_t2959;
    Array *_va52 = Array_new(_t2957, &(U64){_t2958}, &(U64){_t2959});
    (void)_va52;
    Str_delete(_t2957, &(Bool){1});
    ;
    ;
    U64 _t2960 = 0;
    (void)_t2960;
    Str *_t2961 = Str_lit("(", 1ULL);
    (void)_t2961;
    Array_set(_va52, &(U64){_t2960}, _t2961);
    ;
    U64 _t2962 = 1;
    (void)_t2962;
    Str *_t2963 = node_name(&e->data);
    (void)_t2963;
    Array_set(_va52, &(U64){_t2962}, _t2963);
    ;
    print(_va52);
    Bool _t2964; { Bool *_hp = (Bool *)TilType_eq(&e->til_type, TilType_Unknown()); _t2964 = *_hp; free(_hp); }
    (void)_t2964;
    Bool _t2965 = Bool_not(_t2964);
    (void)_t2965;
    ;
    if (_t2965) {
        Str *_t2824 = Str_lit("Str", 3ULL);
        (void)_t2824;
        U64 _t2825; { U64 *_hp = (U64 *)Str_size(); _t2825 = *_hp; free(_hp); }
        (void)_t2825;
        U64 _t2826 = 2;
        (void)_t2826;
        Array *_va39 = Array_new(_t2824, &(U64){_t2825}, &(U64){_t2826});
        (void)_va39;
        Str_delete(_t2824, &(Bool){1});
        ;
        ;
        U64 _t2827 = 0;
        (void)_t2827;
        Str *_t2828 = Str_lit(":", 1ULL);
        (void)_t2828;
        Array_set(_va39, &(U64){_t2827}, _t2828);
        ;
        U64 _t2829 = 1;
        (void)_t2829;
        Str *_t2830 = til_type_name_c(&e->til_type);
        (void)_t2830;
        Array_set(_va39, &(U64){_t2829}, _t2830);
        ;
        print(_va39);
    }
    ;
    {
        ExprData *_sw2831 = ExprData_clone(&e->data);
        (void)_sw2831;
        Bool _t2918; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw2831); _t2918 = *_hp; free(_hp); }
        (void)_t2918;
        if (_t2918) {
            Str *s = ExprData_get_Ident(_sw2831);
            (void)s;
            Str *_t2832 = Str_lit("Str", 3ULL);
            (void)_t2832;
            U64 _t2833; { U64 *_hp = (U64 *)Str_size(); _t2833 = *_hp; free(_hp); }
            (void)_t2833;
            U64 _t2834 = 3;
            (void)_t2834;
            Array *_va40 = Array_new(_t2832, &(U64){_t2833}, &(U64){_t2834});
            (void)_va40;
            Str_delete(_t2832, &(Bool){1});
            ;
            ;
            U64 _t2835 = 0;
            (void)_t2835;
            Str *_t2836 = Str_lit(" \"", 3ULL);
            (void)_t2836;
            Array_set(_va40, &(U64){_t2835}, _t2836);
            ;
            U64 _t2837 = 1;
            (void)_t2837;
            Str *_t2838 = Str_clone(s);
            (void)_t2838;
            Str_delete(s, &(Bool){1});
            Array_set(_va40, &(U64){_t2837}, _t2838);
            ;
            U64 _t2839 = 2;
            (void)_t2839;
            Str *_t2840 = Str_lit("\"", 2ULL);
            (void)_t2840;
            Array_set(_va40, &(U64){_t2839}, _t2840);
            ;
            print(_va40);
        } else {
            Bool _t2917; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw2831); _t2917 = *_hp; free(_hp); }
            (void)_t2917;
            if (_t2917) {
                Str *s = ExprData_get_LiteralStr(_sw2831);
                (void)s;
                Str *_t2841 = Str_lit("Str", 3ULL);
                (void)_t2841;
                U64 _t2842; { U64 *_hp = (U64 *)Str_size(); _t2842 = *_hp; free(_hp); }
                (void)_t2842;
                U64 _t2843 = 3;
                (void)_t2843;
                Array *_va41 = Array_new(_t2841, &(U64){_t2842}, &(U64){_t2843});
                (void)_va41;
                Str_delete(_t2841, &(Bool){1});
                ;
                ;
                U64 _t2844 = 0;
                (void)_t2844;
                Str *_t2845 = Str_lit(" \"", 3ULL);
                (void)_t2845;
                Array_set(_va41, &(U64){_t2844}, _t2845);
                ;
                U64 _t2846 = 1;
                (void)_t2846;
                Str *_t2847 = Str_clone(s);
                (void)_t2847;
                Str_delete(s, &(Bool){1});
                Array_set(_va41, &(U64){_t2846}, _t2847);
                ;
                U64 _t2848 = 2;
                (void)_t2848;
                Str *_t2849 = Str_lit("\"", 2ULL);
                (void)_t2849;
                Array_set(_va41, &(U64){_t2848}, _t2849);
                ;
                print(_va41);
            } else {
                Bool _t2916; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw2831); _t2916 = *_hp; free(_hp); }
                (void)_t2916;
                if (_t2916) {
                    Str *s = ExprData_get_LiteralNum(_sw2831);
                    (void)s;
                    Str *_t2850 = Str_lit("Str", 3ULL);
                    (void)_t2850;
                    U64 _t2851; { U64 *_hp = (U64 *)Str_size(); _t2851 = *_hp; free(_hp); }
                    (void)_t2851;
                    U64 _t2852 = 3;
                    (void)_t2852;
                    Array *_va42 = Array_new(_t2850, &(U64){_t2851}, &(U64){_t2852});
                    (void)_va42;
                    Str_delete(_t2850, &(Bool){1});
                    ;
                    ;
                    U64 _t2853 = 0;
                    (void)_t2853;
                    Str *_t2854 = Str_lit(" \"", 3ULL);
                    (void)_t2854;
                    Array_set(_va42, &(U64){_t2853}, _t2854);
                    ;
                    U64 _t2855 = 1;
                    (void)_t2855;
                    Str *_t2856 = Str_clone(s);
                    (void)_t2856;
                    Str_delete(s, &(Bool){1});
                    Array_set(_va42, &(U64){_t2855}, _t2856);
                    ;
                    U64 _t2857 = 2;
                    (void)_t2857;
                    Str *_t2858 = Str_lit("\"", 2ULL);
                    (void)_t2858;
                    Array_set(_va42, &(U64){_t2857}, _t2858);
                    ;
                    print(_va42);
                } else {
                    Bool _t2915; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw2831); _t2915 = *_hp; free(_hp); }
                    (void)_t2915;
                    if (_t2915) {
                        Str *s = ExprData_get_LiteralBool(_sw2831);
                        (void)s;
                        Str *_t2859 = Str_lit("Str", 3ULL);
                        (void)_t2859;
                        U64 _t2860; { U64 *_hp = (U64 *)Str_size(); _t2860 = *_hp; free(_hp); }
                        (void)_t2860;
                        U64 _t2861 = 3;
                        (void)_t2861;
                        Array *_va43 = Array_new(_t2859, &(U64){_t2860}, &(U64){_t2861});
                        (void)_va43;
                        Str_delete(_t2859, &(Bool){1});
                        ;
                        ;
                        U64 _t2862 = 0;
                        (void)_t2862;
                        Str *_t2863 = Str_lit(" \"", 3ULL);
                        (void)_t2863;
                        Array_set(_va43, &(U64){_t2862}, _t2863);
                        ;
                        U64 _t2864 = 1;
                        (void)_t2864;
                        Str *_t2865 = Str_clone(s);
                        (void)_t2865;
                        Str_delete(s, &(Bool){1});
                        Array_set(_va43, &(U64){_t2864}, _t2865);
                        ;
                        U64 _t2866 = 2;
                        (void)_t2866;
                        Str *_t2867 = Str_lit("\"", 2ULL);
                        (void)_t2867;
                        Array_set(_va43, &(U64){_t2866}, _t2867);
                        ;
                        print(_va43);
                    } else {
                        Bool _t2914; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw2831); _t2914 = *_hp; free(_hp); }
                        (void)_t2914;
                        if (_t2914) {
                            Str *s = ExprData_get_ForIn(_sw2831);
                            (void)s;
                            Str *_t2868 = Str_lit("Str", 3ULL);
                            (void)_t2868;
                            U64 _t2869; { U64 *_hp = (U64 *)Str_size(); _t2869 = *_hp; free(_hp); }
                            (void)_t2869;
                            U64 _t2870 = 3;
                            (void)_t2870;
                            Array *_va44 = Array_new(_t2868, &(U64){_t2869}, &(U64){_t2870});
                            (void)_va44;
                            Str_delete(_t2868, &(Bool){1});
                            ;
                            ;
                            U64 _t2871 = 0;
                            (void)_t2871;
                            Str *_t2872 = Str_lit(" \"", 3ULL);
                            (void)_t2872;
                            Array_set(_va44, &(U64){_t2871}, _t2872);
                            ;
                            U64 _t2873 = 1;
                            (void)_t2873;
                            Str *_t2874 = Str_clone(s);
                            (void)_t2874;
                            Str_delete(s, &(Bool){1});
                            Array_set(_va44, &(U64){_t2873}, _t2874);
                            ;
                            U64 _t2875 = 2;
                            (void)_t2875;
                            Str *_t2876 = Str_lit("\"", 2ULL);
                            (void)_t2876;
                            Array_set(_va44, &(U64){_t2875}, _t2876);
                            ;
                            print(_va44);
                        } else {
                            Bool _t2913; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw2831); _t2913 = *_hp; free(_hp); }
                            (void)_t2913;
                            if (_t2913) {
                                Declaration *decl = ExprData_get_Decl(_sw2831);
                                (void)decl;
                                if (decl->is_mut) {
                                    Str *_t2877 = Str_lit("Str", 3ULL);
                                    (void)_t2877;
                                    U64 _t2878; { U64 *_hp = (U64 *)Str_size(); _t2878 = *_hp; free(_hp); }
                                    (void)_t2878;
                                    U64 _t2879 = 1;
                                    (void)_t2879;
                                    Array *_va45 = Array_new(_t2877, &(U64){_t2878}, &(U64){_t2879});
                                    (void)_va45;
                                    Str_delete(_t2877, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t2880 = 0;
                                    (void)_t2880;
                                    Str *_t2881 = Str_lit(" mut", 4ULL);
                                    (void)_t2881;
                                    Array_set(_va45, &(U64){_t2880}, _t2881);
                                    ;
                                    print(_va45);
                                }
                                Str *_t2882 = Str_lit("Str", 3ULL);
                                (void)_t2882;
                                U64 _t2883; { U64 *_hp = (U64 *)Str_size(); _t2883 = *_hp; free(_hp); }
                                (void)_t2883;
                                U64 _t2884 = 2;
                                (void)_t2884;
                                Array *_va46 = Array_new(_t2882, &(U64){_t2883}, &(U64){_t2884});
                                (void)_va46;
                                Str_delete(_t2882, &(Bool){1});
                                ;
                                ;
                                U64 _t2885 = 0;
                                (void)_t2885;
                                Str *_t2886 = Str_lit(" ", 1ULL);
                                (void)_t2886;
                                Array_set(_va46, &(U64){_t2885}, _t2886);
                                ;
                                U64 _t2887 = 1;
                                (void)_t2887;
                                Str *_t2888 = Str_clone(&decl->name);
                                (void)_t2888;
                                Declaration_delete(decl, &(Bool){1});
                                Array_set(_va46, &(U64){_t2887}, _t2888);
                                ;
                                print(_va46);
                            } else {
                                Bool _t2912; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw2831); _t2912 = *_hp; free(_hp); }
                                (void)_t2912;
                                if (_t2912) {
                                    Str *s = ExprData_get_Assign(_sw2831);
                                    (void)s;
                                    Str *_t2889 = Str_lit("Str", 3ULL);
                                    (void)_t2889;
                                    U64 _t2890; { U64 *_hp = (U64 *)Str_size(); _t2890 = *_hp; free(_hp); }
                                    (void)_t2890;
                                    U64 _t2891 = 2;
                                    (void)_t2891;
                                    Array *_va47 = Array_new(_t2889, &(U64){_t2890}, &(U64){_t2891});
                                    (void)_va47;
                                    Str_delete(_t2889, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t2892 = 0;
                                    (void)_t2892;
                                    Str *_t2893 = Str_lit(" ", 1ULL);
                                    (void)_t2893;
                                    Array_set(_va47, &(U64){_t2892}, _t2893);
                                    ;
                                    U64 _t2894 = 1;
                                    (void)_t2894;
                                    Str *_t2895 = Str_clone(s);
                                    (void)_t2895;
                                    Str_delete(s, &(Bool){1});
                                    Array_set(_va47, &(U64){_t2894}, _t2895);
                                    ;
                                    print(_va47);
                                } else {
                                    Bool _t2911; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw2831); _t2911 = *_hp; free(_hp); }
                                    (void)_t2911;
                                    if (_t2911) {
                                        Str *s = ExprData_get_NamedArg(_sw2831);
                                        (void)s;
                                        Str *_t2896 = Str_lit("Str", 3ULL);
                                        (void)_t2896;
                                        U64 _t2897; { U64 *_hp = (U64 *)Str_size(); _t2897 = *_hp; free(_hp); }
                                        (void)_t2897;
                                        U64 _t2898 = 2;
                                        (void)_t2898;
                                        Array *_va48 = Array_new(_t2896, &(U64){_t2897}, &(U64){_t2898});
                                        (void)_va48;
                                        Str_delete(_t2896, &(Bool){1});
                                        ;
                                        ;
                                        U64 _t2899 = 0;
                                        (void)_t2899;
                                        Str *_t2900 = Str_lit(" ", 1ULL);
                                        (void)_t2900;
                                        Array_set(_va48, &(U64){_t2899}, _t2900);
                                        ;
                                        U64 _t2901 = 1;
                                        (void)_t2901;
                                        Str *_t2902 = Str_clone(s);
                                        (void)_t2902;
                                        Str_delete(s, &(Bool){1});
                                        Array_set(_va48, &(U64){_t2901}, _t2902);
                                        ;
                                        print(_va48);
                                    } else {
                                        Bool _t2910; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw2831); _t2910 = *_hp; free(_hp); }
                                        (void)_t2910;
                                        if (_t2910) {
                                            FunctionDef *fdef = ExprData_get_FuncDef(_sw2831);
                                            (void)fdef;
                                            Str *_t2903 = Str_lit("Str", 3ULL);
                                            (void)_t2903;
                                            U64 _t2904; { U64 *_hp = (U64 *)Str_size(); _t2904 = *_hp; free(_hp); }
                                            (void)_t2904;
                                            U64 _t2905 = 2;
                                            (void)_t2905;
                                            Array *_va49 = Array_new(_t2903, &(U64){_t2904}, &(U64){_t2905});
                                            (void)_va49;
                                            Str_delete(_t2903, &(Bool){1});
                                            ;
                                            ;
                                            U64 _t2906 = 0;
                                            (void)_t2906;
                                            Str *_t2907 = Str_lit(" ", 1ULL);
                                            (void)_t2907;
                                            Array_set(_va49, &(U64){_t2906}, _t2907);
                                            ;
                                            U64 _t2908 = 1;
                                            (void)_t2908;
                                            Str *_t2909 = func_type_name(&fdef->func_type);
                                            (void)_t2909;
                                            FunctionDef_delete(fdef, &(Bool){1});
                                            Array_set(_va49, &(U64){_t2908}, _t2909);
                                            ;
                                            print(_va49);
                                        } else {
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        ExprData_delete(_sw2831, &(Bool){1});
        ;
    }
    U64 _t2966; { U64 *_hp = (U64 *)Vec_len(&e->children); _t2966 = *_hp; free(_hp); }
    (void)_t2966;
    U64 _t2967 = 0;
    (void)_t2967;
    Bool _t2968; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2966}, &(U64){_t2967}); _t2968 = *_hp; free(_hp); }
    (void)_t2968;
    ;
    ;
    if (_t2968) {
        Str *_t2952 = Str_lit("Str", 3ULL);
        (void)_t2952;
        U64 _t2953; { U64 *_hp = (U64 *)Str_size(); _t2953 = *_hp; free(_hp); }
        (void)_t2953;
        U64 _t2954 = 1;
        (void)_t2954;
        Array *_va51 = Array_new(_t2952, &(U64){_t2953}, &(U64){_t2954});
        (void)_va51;
        Str_delete(_t2952, &(Bool){1});
        ;
        ;
        U64 _t2955 = 0;
        (void)_t2955;
        Str *_t2956 = Str_lit("", 0ULL);
        (void)_t2956;
        Array_set(_va51, &(U64){_t2955}, _t2956);
        ;
        println(_va51);
        {
            U64 _fi2919 = 0;
            (void)_fi2919;
            while (1) {
                U64 _t2921 = 0;
                (void)_t2921;
                U64 _t2922; { U64 *_hp = (U64 *)Vec_len(&e->children); _t2922 = *_hp; free(_hp); }
                (void)_t2922;
                Range *_t2923 = Range_new(_t2921, _t2922);
                (void)_t2923;
                ;
                ;
                U64 _t2924; { U64 *_hp = (U64 *)Range_len(_t2923); _t2924 = *_hp; free(_hp); }
                (void)_t2924;
                Range_delete(_t2923, &(Bool){1});
                Bool _wcond2920; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2919}, &(U64){_t2924}); _wcond2920 = *_hp; free(_hp); }
                (void)_wcond2920;
                ;
                if (_wcond2920) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t2925 = 0;
                (void)_t2925;
                U64 _t2926; { U64 *_hp = (U64 *)Vec_len(&e->children); _t2926 = *_hp; free(_hp); }
                (void)_t2926;
                Range *_t2927 = Range_new(_t2925, _t2926);
                (void)_t2927;
                ;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t2927, _fi2919); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t2927, &(Bool){1});
                U64 _t2928 = 1;
                (void)_t2928;
                U64 _t2929 = U64_add(_fi2919, _t2928);
                (void)_t2929;
                ;
                _fi2919 = _t2929;
                ;
                I64 *_t2930 = malloc(sizeof(I64)); *_t2930 = U64_to_i64(i);
                (void)_t2930;
                ;
                U32 _t2931 = 1;
                (void)_t2931;
                Expr *_t2932 = Expr_child(e, _t2930);
                (void)_t2932;
                U32 _t2933 = U32_add(indent, _t2931);
                (void)_t2933;
                ;
                ast_print(_t2932, _t2933);
                I64_delete(_t2930, &(Bool){1});
                ;
            }
            ;
        }
        {
            U64 _fi2934 = 0;
            (void)_fi2934;
            while (1) {
                I64 _t2936 = U32_to_i64(indent);
                (void)_t2936;
                U64 _t2937 = 0;
                (void)_t2937;
                U64 _t2938 = I64_to_u64(_t2936);
                (void)_t2938;
                ;
                Range *_t2939 = Range_new(_t2937, _t2938);
                (void)_t2939;
                ;
                ;
                U64 _t2940; { U64 *_hp = (U64 *)Range_len(_t2939); _t2940 = *_hp; free(_hp); }
                (void)_t2940;
                Range_delete(_t2939, &(Bool){1});
                Bool _wcond2935; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2934}, &(U64){_t2940}); _wcond2935 = *_hp; free(_hp); }
                (void)_wcond2935;
                ;
                if (_wcond2935) {
                } else {
                    ;
                    break;
                }
                ;
                I64 _t2941 = U32_to_i64(indent);
                (void)_t2941;
                U64 _t2942 = 0;
                (void)_t2942;
                U64 _t2943 = I64_to_u64(_t2941);
                (void)_t2943;
                ;
                Range *_t2944 = Range_new(_t2942, _t2943);
                (void)_t2944;
                ;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t2944, _fi2934); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t2944, &(Bool){1});
                ;
                U64 _t2945 = 1;
                (void)_t2945;
                U64 _t2946 = U64_add(_fi2934, _t2945);
                (void)_t2946;
                ;
                _fi2934 = _t2946;
                ;
                Str *_t2947 = Str_lit("Str", 3ULL);
                (void)_t2947;
                U64 _t2948; { U64 *_hp = (U64 *)Str_size(); _t2948 = *_hp; free(_hp); }
                (void)_t2948;
                U64 _t2949 = 1;
                (void)_t2949;
                Array *_va50 = Array_new(_t2947, &(U64){_t2948}, &(U64){_t2949});
                (void)_va50;
                Str_delete(_t2947, &(Bool){1});
                ;
                ;
                U64 _t2950 = 0;
                (void)_t2950;
                Str *_t2951 = Str_lit("  ", 2ULL);
                (void)_t2951;
                Array_set(_va50, &(U64){_t2950}, _t2951);
                ;
                print(_va50);
            }
            ;
        }
    }
    ;
    Str *_t2969 = Str_lit("Str", 3ULL);
    (void)_t2969;
    U64 _t2970; { U64 *_hp = (U64 *)Str_size(); _t2970 = *_hp; free(_hp); }
    (void)_t2970;
    U64 _t2971 = 1;
    (void)_t2971;
    Array *_va53 = Array_new(_t2969, &(U64){_t2970}, &(U64){_t2971});
    (void)_va53;
    Str_delete(_t2969, &(Bool){1});
    ;
    ;
    U64 _t2972 = 0;
    (void)_t2972;
    Str *_t2973 = Str_lit(")", 1ULL);
    (void)_t2973;
    Array_set(_va53, &(U64){_t2972}, _t2973);
    ;
    println(_va53);
}

Bool * enum_has_payloads(Expr * enum_def) {
    (void)enum_def;
    I64 *_t2995 = malloc(sizeof(I64));
    *_t2995 = 0;
    (void)_t2995;
    Expr *body = Expr_child(enum_def, _t2995);
    (void)body;
    {
        U64 _fi2974 = 0;
        (void)_fi2974;
        while (1) {
            I64 _t2982; { I64 *_hp = (I64 *)Expr_child_count(body); _t2982 = *_hp; free(_hp); }
            (void)_t2982;
            U64 _t2983 = 0;
            (void)_t2983;
            U64 _t2984 = I64_to_u64(_t2982);
            (void)_t2984;
            ;
            Range *_t2985 = Range_new(_t2983, _t2984);
            (void)_t2985;
            ;
            ;
            U64 _t2986; { U64 *_hp = (U64 *)Range_len(_t2985); _t2986 = *_hp; free(_hp); }
            (void)_t2986;
            Range_delete(_t2985, &(Bool){1});
            Bool _wcond2975; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2974}, &(U64){_t2986}); _wcond2975 = *_hp; free(_hp); }
            (void)_wcond2975;
            ;
            if (_wcond2975) {
            } else {
                ;
                break;
            }
            ;
            I64 _t2987; { I64 *_hp = (I64 *)Expr_child_count(body); _t2987 = *_hp; free(_hp); }
            (void)_t2987;
            U64 _t2988 = 0;
            (void)_t2988;
            U64 _t2989 = I64_to_u64(_t2987);
            (void)_t2989;
            ;
            Range *_t2990 = Range_new(_t2988, _t2989);
            (void)_t2990;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t2990, _fi2974); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t2990, &(Bool){1});
            U64 _t2991 = 1;
            (void)_t2991;
            U64 _t2992 = U64_add(_fi2974, _t2991);
            (void)_t2992;
            ;
            _fi2974 = _t2992;
            ;
            I64 *_t2993 = malloc(sizeof(I64)); *_t2993 = U64_to_i64(i);
            (void)_t2993;
            ;
            Expr *f = Expr_child(body, _t2993);
            (void)f;
            Bool _t2994; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2994 = *_hp; free(_hp); }
            (void)_t2994;
            if (_t2994) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                U64 _t2977; { U64 *_hp = (U64 *)Str_len(&decl->explicit_type); _t2977 = *_hp; free(_hp); }
                (void)_t2977;
                U64 _t2978 = 0;
                (void)_t2978;
                Bool _t2979 = Bool_not(decl->is_namespace);
                (void)_t2979;
                Declaration_delete(decl, &(Bool){1});
                Bool _t2980; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2977}, &(U64){_t2978}); _t2980 = *_hp; free(_hp); }
                (void)_t2980;
                ;
                ;
                Bool _t2981 = Bool_and(_t2979, _t2980);
                (void)_t2981;
                ;
                ;
                if (_t2981) {
                    Bool _t2976 = 1;
                    (void)_t2976;
                    ;
                    I64_delete(_t2993, &(Bool){1});
                    ;
                    ;
                    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2976; return _r; }
                }
                ;
            }
            I64_delete(_t2993, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t2995, &(Bool){1});
    Bool _t2996 = 0;
    (void)_t2996;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2996; return _r; }
}

I32 * enum_variant_tag(Expr * enum_def, Str * variant_name) {
    (void)enum_def;
    (void)variant_name;
    I64 *_t3016 = malloc(sizeof(I64));
    *_t3016 = 0;
    (void)_t3016;
    Expr *body = Expr_child(enum_def, _t3016);
    (void)body;
    I32 tag = 0;
    (void)tag;
    {
        U64 _fi2997 = 0;
        (void)_fi2997;
        while (1) {
            I64 _t3003; { I64 *_hp = (I64 *)Expr_child_count(body); _t3003 = *_hp; free(_hp); }
            (void)_t3003;
            U64 _t3004 = 0;
            (void)_t3004;
            U64 _t3005 = I64_to_u64(_t3003);
            (void)_t3005;
            ;
            Range *_t3006 = Range_new(_t3004, _t3005);
            (void)_t3006;
            ;
            ;
            U64 _t3007; { U64 *_hp = (U64 *)Range_len(_t3006); _t3007 = *_hp; free(_hp); }
            (void)_t3007;
            Range_delete(_t3006, &(Bool){1});
            Bool _wcond2998; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2997}, &(U64){_t3007}); _wcond2998 = *_hp; free(_hp); }
            (void)_wcond2998;
            ;
            if (_wcond2998) {
            } else {
                ;
                break;
            }
            ;
            I64 _t3008; { I64 *_hp = (I64 *)Expr_child_count(body); _t3008 = *_hp; free(_hp); }
            (void)_t3008;
            U64 _t3009 = 0;
            (void)_t3009;
            U64 _t3010 = I64_to_u64(_t3008);
            (void)_t3010;
            ;
            Range *_t3011 = Range_new(_t3009, _t3010);
            (void)_t3011;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t3011, _fi2997); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t3011, &(Bool){1});
            U64 _t3012 = 1;
            (void)_t3012;
            U64 _t3013 = U64_add(_fi2997, _t3012);
            (void)_t3013;
            ;
            _fi2997 = _t3013;
            ;
            I64 *_t3014 = malloc(sizeof(I64)); *_t3014 = U64_to_i64(i);
            (void)_t3014;
            ;
            Expr *f = Expr_child(body, _t3014);
            (void)f;
            Bool _t3015; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t3015 = *_hp; free(_hp); }
            (void)_t3015;
            if (_t3015) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t3002 = Bool_not(decl->is_namespace);
                (void)_t3002;
                if (_t3002) {
                    Bool _t2999; { Bool *_hp = (Bool *)Str_eq(&decl->name, variant_name); _t2999 = *_hp; free(_hp); }
                    (void)_t2999;
                    if (_t2999) {
                        ;
                        ;
                        Declaration_delete(decl, &(Bool){1});
                        I64_delete(_t3014, &(Bool){1});
                        ;
                        ;
                        { I32 *_r = malloc(sizeof(I32)); *_r = tag; return _r; }
                    }
                    ;
                    I32 _t3000 = 1;
                    (void)_t3000;
                    I32 _t3001 = I32_add(tag, _t3000);
                    (void)_t3001;
                    ;
                    tag = _t3001;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t3014, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t3016, &(Bool){1});
    ;
    I64 _t3017 = 0;
    (void)_t3017;
    I64 _t3018 = 1;
    (void)_t3018;
    I64 _t3019 = I64_sub(_t3017, _t3018);
    (void)_t3019;
    ;
    ;
    I32 _t3020 = I64_to_i32(_t3019);
    (void)_t3020;
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t3020; return _r; }
}

Str * enum_variant_type(Expr * enum_def, I32 tag) {
    (void)enum_def;
    (void)tag;
    I64 *_t3040 = malloc(sizeof(I64));
    *_t3040 = 0;
    (void)_t3040;
    Expr *body = Expr_child(enum_def, _t3040);
    (void)body;
    I32 idx = 0;
    (void)idx;
    {
        U64 _fi3021 = 0;
        (void)_fi3021;
        while (1) {
            I64 _t3027; { I64 *_hp = (I64 *)Expr_child_count(body); _t3027 = *_hp; free(_hp); }
            (void)_t3027;
            U64 _t3028 = 0;
            (void)_t3028;
            U64 _t3029 = I64_to_u64(_t3027);
            (void)_t3029;
            ;
            Range *_t3030 = Range_new(_t3028, _t3029);
            (void)_t3030;
            ;
            ;
            U64 _t3031; { U64 *_hp = (U64 *)Range_len(_t3030); _t3031 = *_hp; free(_hp); }
            (void)_t3031;
            Range_delete(_t3030, &(Bool){1});
            Bool _wcond3022; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3021}, &(U64){_t3031}); _wcond3022 = *_hp; free(_hp); }
            (void)_wcond3022;
            ;
            if (_wcond3022) {
            } else {
                ;
                break;
            }
            ;
            I64 _t3032; { I64 *_hp = (I64 *)Expr_child_count(body); _t3032 = *_hp; free(_hp); }
            (void)_t3032;
            U64 _t3033 = 0;
            (void)_t3033;
            U64 _t3034 = I64_to_u64(_t3032);
            (void)_t3034;
            ;
            Range *_t3035 = Range_new(_t3033, _t3034);
            (void)_t3035;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t3035, _fi3021); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t3035, &(Bool){1});
            U64 _t3036 = 1;
            (void)_t3036;
            U64 _t3037 = U64_add(_fi3021, _t3036);
            (void)_t3037;
            ;
            _fi3021 = _t3037;
            ;
            I64 *_t3038 = malloc(sizeof(I64)); *_t3038 = U64_to_i64(i);
            (void)_t3038;
            ;
            Expr *f = Expr_child(body, _t3038);
            (void)f;
            Bool _t3039; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t3039 = *_hp; free(_hp); }
            (void)_t3039;
            if (_t3039) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t3026 = Bool_not(decl->is_namespace);
                (void)_t3026;
                if (_t3026) {
                    Bool _t3023 = I32_eq(idx, tag);
                    (void)_t3023;
                    if (_t3023) {
                        ;
                        ;
                        I64_delete(_t3038, &(Bool){1});
                        ;
                        ;
                        { Str *_r = malloc(sizeof(Str)); *_r = decl->explicit_type; return _r; }
                    }
                    ;
                    I32 _t3024 = 1;
                    (void)_t3024;
                    I32 _t3025 = I32_add(idx, _t3024);
                    (void)_t3025;
                    ;
                    idx = _t3025;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t3038, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t3040, &(Bool){1});
    ;
    Str *_t3041 = Str_lit("", 0ULL);
    (void)_t3041;
    return _t3041;
}

