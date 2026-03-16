#include "ast_ast.h"

Str * til_type_name_c(TilType * t) {
    (void)t;
    {
        TilType *_sw2275 = TilType_clone(t);
        (void)_sw2275;
        Bool _t2310; { Bool *_hp = (Bool *)TilType_eq(_sw2275, TilType_Unknown()); _t2310 = *_hp; free(_hp); }
        (void)_t2310;
        if (_t2310) {
            Str *_t2276 = Str_lit("unknown", 7ULL);
            (void)_t2276;
            TilType_delete(_sw2275, &(Bool){1});
            ;
            return _t2276;
        } else {
            Bool _t2309; { Bool *_hp = (Bool *)TilType_eq(_sw2275, TilType_None()); _t2309 = *_hp; free(_hp); }
            (void)_t2309;
            if (_t2309) {
                Str *_t2277 = Str_lit("None", 4ULL);
                (void)_t2277;
                ;
                TilType_delete(_sw2275, &(Bool){1});
                ;
                return _t2277;
            } else {
                Bool _t2308; { Bool *_hp = (Bool *)TilType_eq(_sw2275, TilType_I64()); _t2308 = *_hp; free(_hp); }
                (void)_t2308;
                if (_t2308) {
                    Str *_t2278 = Str_lit("I64", 3ULL);
                    (void)_t2278;
                    ;
                    ;
                    TilType_delete(_sw2275, &(Bool){1});
                    ;
                    return _t2278;
                } else {
                    Bool _t2307; { Bool *_hp = (Bool *)TilType_eq(_sw2275, TilType_U8()); _t2307 = *_hp; free(_hp); }
                    (void)_t2307;
                    if (_t2307) {
                        Str *_t2279 = Str_lit("U8", 2ULL);
                        (void)_t2279;
                        ;
                        ;
                        ;
                        TilType_delete(_sw2275, &(Bool){1});
                        ;
                        return _t2279;
                    } else {
                        Bool _t2306; { Bool *_hp = (Bool *)TilType_eq(_sw2275, TilType_I16()); _t2306 = *_hp; free(_hp); }
                        (void)_t2306;
                        if (_t2306) {
                            Str *_t2280 = Str_lit("I16", 3ULL);
                            (void)_t2280;
                            ;
                            ;
                            ;
                            ;
                            TilType_delete(_sw2275, &(Bool){1});
                            ;
                            return _t2280;
                        } else {
                            Bool _t2305; { Bool *_hp = (Bool *)TilType_eq(_sw2275, TilType_I32()); _t2305 = *_hp; free(_hp); }
                            (void)_t2305;
                            if (_t2305) {
                                Str *_t2281 = Str_lit("I32", 3ULL);
                                (void)_t2281;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TilType_delete(_sw2275, &(Bool){1});
                                ;
                                return _t2281;
                            } else {
                                Bool _t2304; { Bool *_hp = (Bool *)TilType_eq(_sw2275, TilType_U32()); _t2304 = *_hp; free(_hp); }
                                (void)_t2304;
                                if (_t2304) {
                                    Str *_t2282 = Str_lit("U32", 3ULL);
                                    (void)_t2282;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TilType_delete(_sw2275, &(Bool){1});
                                    ;
                                    return _t2282;
                                } else {
                                    Bool _t2303; { Bool *_hp = (Bool *)TilType_eq(_sw2275, TilType_U64()); _t2303 = *_hp; free(_hp); }
                                    (void)_t2303;
                                    if (_t2303) {
                                        Str *_t2283 = Str_lit("U64", 3ULL);
                                        (void)_t2283;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TilType_delete(_sw2275, &(Bool){1});
                                        ;
                                        return _t2283;
                                    } else {
                                        Bool _t2302; { Bool *_hp = (Bool *)TilType_eq(_sw2275, TilType_F32()); _t2302 = *_hp; free(_hp); }
                                        (void)_t2302;
                                        if (_t2302) {
                                            Str *_t2284 = Str_lit("F32", 3ULL);
                                            (void)_t2284;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TilType_delete(_sw2275, &(Bool){1});
                                            ;
                                            return _t2284;
                                        } else {
                                            Bool _t2301; { Bool *_hp = (Bool *)TilType_eq(_sw2275, TilType_Bool()); _t2301 = *_hp; free(_hp); }
                                            (void)_t2301;
                                            if (_t2301) {
                                                Str *_t2285 = Str_lit("Bool", 4ULL);
                                                (void)_t2285;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                TilType_delete(_sw2275, &(Bool){1});
                                                ;
                                                return _t2285;
                                            } else {
                                                Bool _t2300; { Bool *_hp = (Bool *)TilType_eq(_sw2275, TilType_Struct()); _t2300 = *_hp; free(_hp); }
                                                (void)_t2300;
                                                if (_t2300) {
                                                    Str *_t2286 = Str_lit("Struct", 6ULL);
                                                    (void)_t2286;
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
                                                    TilType_delete(_sw2275, &(Bool){1});
                                                    ;
                                                    return _t2286;
                                                } else {
                                                    Bool _t2299; { Bool *_hp = (Bool *)TilType_eq(_sw2275, TilType_StructDef()); _t2299 = *_hp; free(_hp); }
                                                    (void)_t2299;
                                                    if (_t2299) {
                                                        Str *_t2287 = Str_lit("StructDef", 9ULL);
                                                        (void)_t2287;
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
                                                        TilType_delete(_sw2275, &(Bool){1});
                                                        ;
                                                        return _t2287;
                                                    } else {
                                                        Bool _t2298; { Bool *_hp = (Bool *)TilType_eq(_sw2275, TilType_Enum()); _t2298 = *_hp; free(_hp); }
                                                        (void)_t2298;
                                                        if (_t2298) {
                                                            Str *_t2288 = Str_lit("Enum", 4ULL);
                                                            (void)_t2288;
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
                                                            TilType_delete(_sw2275, &(Bool){1});
                                                            ;
                                                            return _t2288;
                                                        } else {
                                                            Bool _t2297; { Bool *_hp = (Bool *)TilType_eq(_sw2275, TilType_EnumDef()); _t2297 = *_hp; free(_hp); }
                                                            (void)_t2297;
                                                            if (_t2297) {
                                                                Str *_t2289 = Str_lit("EnumDef", 7ULL);
                                                                (void)_t2289;
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
                                                                TilType_delete(_sw2275, &(Bool){1});
                                                                ;
                                                                return _t2289;
                                                            } else {
                                                                Bool _t2296; { Bool *_hp = (Bool *)TilType_eq(_sw2275, TilType_FuncDef()); _t2296 = *_hp; free(_hp); }
                                                                (void)_t2296;
                                                                if (_t2296) {
                                                                    Str *_t2290 = Str_lit("FunctionDef", 11ULL);
                                                                    (void)_t2290;
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
                                                                    TilType_delete(_sw2275, &(Bool){1});
                                                                    ;
                                                                    return _t2290;
                                                                } else {
                                                                    Bool _t2295; { Bool *_hp = (Bool *)TilType_eq(_sw2275, TilType_FuncPtr()); _t2295 = *_hp; free(_hp); }
                                                                    (void)_t2295;
                                                                    if (_t2295) {
                                                                        Str *_t2291 = Str_lit("Fn", 2ULL);
                                                                        (void)_t2291;
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
                                                                        TilType_delete(_sw2275, &(Bool){1});
                                                                        ;
                                                                        return _t2291;
                                                                    } else {
                                                                        Bool _t2294; { Bool *_hp = (Bool *)TilType_eq(_sw2275, TilType_Dynamic()); _t2294 = *_hp; free(_hp); }
                                                                        (void)_t2294;
                                                                        if (_t2294) {
                                                                            Str *_t2292 = Str_lit("Dynamic", 7ULL);
                                                                            (void)_t2292;
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
                                                                            TilType_delete(_sw2275, &(Bool){1});
                                                                            ;
                                                                            return _t2292;
                                                                        } else {
                                                                            Str *_t2293 = Str_lit("?", 1ULL);
                                                                            (void)_t2293;
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
                                                                            TilType_delete(_sw2275, &(Bool){1});
                                                                            ;
                                                                            return _t2293;
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
        TilType_delete(_sw2275, &(Bool){1});
        ;
    }
}

Bool * Declaration_eq(Declaration * a, Declaration * b) {
    (void)a;
    (void)b;
    Bool _t2311; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t2311 = *_hp; free(_hp); }
    (void)_t2311;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2311; return _r; }
}

Str * Declaration_to_str(Declaration * self) {
    (void)self;
    { Str *_r = malloc(sizeof(Str)); *_r = self->name; return _r; }
}

Declaration * Declaration_clone(Declaration * self) {
    (void)self;
    Bool _t2312 = Bool_clone(&self->is_mut);
    (void)_t2312;
    Bool _t2313 = Bool_clone(&self->is_namespace);
    (void)_t2313;
    Bool _t2314 = Bool_clone(&self->is_ref);
    (void)_t2314;
    Bool _t2315 = Bool_clone(&self->is_own);
    (void)_t2315;
    I32 _t2316 = I32_clone(&self->field_offset);
    (void)_t2316;
    I32 _t2317 = I32_clone(&self->field_size);
    (void)_t2317;
    Declaration *_t2318 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); _t2318->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); _t2318->explicit_type = *_ca; free(_ca); }
    _t2318->is_mut = _t2312;
    _t2318->is_namespace = _t2313;
    _t2318->is_ref = _t2314;
    _t2318->is_own = _t2315;
    _t2318->field_offset = _t2316;
    _t2318->field_size = _t2317;
    _t2318->field_struct_def = self->field_struct_def;
    _t2318->fn_sig = self->fn_sig;
    (void)_t2318;
    ;
    ;
    ;
    ;
    ;
    ;
    return _t2318;
}

U64 *Declaration_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Declaration);
    return r;
}

void Expr_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Str *_t2642 = Str_lit("Str", 3ULL);
    (void)_t2642;
    U64 _t2643; { U64 *_hp = (U64 *)Str_size(); _t2643 = *_hp; free(_hp); }
    (void)_t2643;
    U64 _t2644 = 7;
    (void)_t2644;
    Array *_va35 = Array_new(_t2642, &(U64){_t2643}, &(U64){_t2644});
    (void)_va35;
    Str_delete(_t2642, &(Bool){1});
    ;
    ;
    U64 _t2645 = 0;
    (void)_t2645;
    Str *_t2646 = Str_clone(&self->path);
    (void)_t2646;
    Array_set(_va35, &(U64){_t2645}, _t2646);
    ;
    U64 _t2647 = 1;
    (void)_t2647;
    Str *_t2648 = Str_lit(":", 1ULL);
    (void)_t2648;
    Array_set(_va35, &(U64){_t2647}, _t2648);
    ;
    U64 _t2649 = 2;
    (void)_t2649;
    Str *_t2650 = U32_to_str(&self->line);
    (void)_t2650;
    Array_set(_va35, &(U64){_t2649}, _t2650);
    ;
    U64 _t2651 = 3;
    (void)_t2651;
    Str *_t2652 = Str_lit(":", 1ULL);
    (void)_t2652;
    Array_set(_va35, &(U64){_t2651}, _t2652);
    ;
    U64 _t2653 = 4;
    (void)_t2653;
    Str *_t2654 = U32_to_str(&self->col);
    (void)_t2654;
    Array_set(_va35, &(U64){_t2653}, _t2654);
    ;
    U64 _t2655 = 5;
    (void)_t2655;
    Str *_t2656 = Str_lit(": error: ", 9ULL);
    (void)_t2656;
    Array_set(_va35, &(U64){_t2655}, _t2656);
    ;
    U64 _t2657 = 6;
    (void)_t2657;
    Str *_t2658 = Str_clone(msg);
    (void)_t2658;
    Array_set(_va35, &(U64){_t2657}, _t2658);
    ;
    println(_va35);
}

void Expr_todo_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Expr_error(self, msg);
    Str *_t2659 = Str_lit("Str", 3ULL);
    (void)_t2659;
    U64 _t2660; { U64 *_hp = (U64 *)Str_size(); _t2660 = *_hp; free(_hp); }
    (void)_t2660;
    U64 _t2661 = 1;
    (void)_t2661;
    Array *_va36 = Array_new(_t2659, &(U64){_t2660}, &(U64){_t2661});
    (void)_va36;
    Str_delete(_t2659, &(Bool){1});
    ;
    ;
    U64 _t2662 = 0;
    (void)_t2662;
    Str *_t2663 = Str_lit("  note: this language feature is not implemented yet", 52ULL);
    (void)_t2663;
    Array_set(_va36, &(U64){_t2662}, _t2663);
    ;
    println(_va36);
}

void Expr_lang_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Expr_error(self, msg);
    Str *_t2664 = Str_lit("Str", 3ULL);
    (void)_t2664;
    U64 _t2665; { U64 *_hp = (U64 *)Str_size(); _t2665 = *_hp; free(_hp); }
    (void)_t2665;
    U64 _t2666 = 1;
    (void)_t2666;
    Array *_va37 = Array_new(_t2664, &(U64){_t2665}, &(U64){_t2666});
    (void)_va37;
    Str_delete(_t2664, &(Bool){1});
    ;
    ;
    U64 _t2667 = 0;
    (void)_t2667;
    Str *_t2668 = Str_lit("  note: this is a bug in the language, please report it", 55ULL);
    (void)_t2668;
    Array_set(_va37, &(U64){_t2667}, _t2668);
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
    U64 *_t2669 = malloc(sizeof(U64)); *_t2669 = I64_to_u64(DEREF(i));
    (void)_t2669;
    Expr *c = Vec_get(&parent->children, _t2669);
    (void)c;
    U64_delete(_t2669, &(Bool){1});
    return c;
}

I64 * Expr_child_count(Expr * parent) {
    (void)parent;
    U64 _t2670; { U64 *_hp = (U64 *)Vec_len(&parent->children); _t2670 = *_hp; free(_hp); }
    (void)_t2670;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t2670; return _r; }
}

Expr * Expr_new(ExprData * data, U32 line, U32 col, Str * path) {
    (void)data;
    (void)line;
    (void)col;
    (void)path;
    I64 _t2671 = 0;
    (void)_t2671;
    I64 _t2672 = 1;
    (void)_t2672;
    I64 _t2673 = I64_sub(_t2671, _t2672);
    (void)_t2673;
    ;
    ;
    I64 _t2674 = 0;
    (void)_t2674;
    I64 _t2675 = 1;
    (void)_t2675;
    I64 _t2676 = I64_sub(_t2674, _t2675);
    (void)_t2676;
    ;
    ;
    Str *_t2677 = Str_lit("Expr", 4ULL);
    (void)_t2677;
    U64 _t2678; { U64 *_hp = (U64 *)Expr_size(); _t2678 = *_hp; free(_hp); }
    (void)_t2678;
    Bool _t2679 = 0;
    (void)_t2679;
    Bool _t2680 = 0;
    (void)_t2680;
    Bool _t2681 = 0;
    (void)_t2681;
    Bool _t2682 = 0;
    (void)_t2682;
    Bool _t2683 = 0;
    (void)_t2683;
    Bool _t2684 = 0;
    (void)_t2684;
    Bool _t2685 = 0;
    (void)_t2685;
    Bool _t2686 = 0;
    (void)_t2686;
    I32 _t2687 = 0;
    (void)_t2687;
    I32 _t2688 = I64_to_i32(_t2673);
    (void)_t2688;
    ;
    U32 _t2689 = 0;
    (void)_t2689;
    I32 _t2690 = I64_to_i32(_t2676);
    (void)_t2690;
    ;
    U32 _t2691 = 0;
    (void)_t2691;
    U32 _t2692 = U32_clone(&(U32){col});
    (void)_t2692;
    Str *_t2693 = Str_clone(path);
    (void)_t2693;
    Expr *_t2694 = malloc(sizeof(Expr));
    { ExprData *_ca = ExprData_clone(data); _t2694->data = *_ca; free(_ca); }
    { TilType *_ca = TilType_clone(TilType_Unknown()); _t2694->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t2694->struct_name = *_ca; free(_ca); }
    _t2694->is_own_arg = _t2679;
    _t2694->is_splat = _t2680;
    _t2694->is_own_field = _t2681;
    _t2694->is_ref_field = _t2682;
    _t2694->is_ns_field = _t2683;
    _t2694->is_ext = _t2684;
    _t2694->is_core = _t2685;
    _t2694->save_old_delete = _t2686;
    _t2694->total_struct_size = _t2687;
    _t2694->variadic_index = _t2688;
    _t2694->variadic_count = _t2689;
    _t2694->kwargs_index = _t2690;
    _t2694->kwargs_count = _t2691;
    _t2694->fn_sig = NULL;
    { Vec *_ca = Vec_new(_t2677, &(U64){_t2678}); _t2694->children = *_ca; free(_ca); }
    _t2694->line = U32_clone(&(U32){line});
    _t2694->col = _t2692;
    { Str *_ca = Str_clone(_t2693); _t2694->path = *_ca; free(_ca); }
    (void)_t2694;
    Str_delete(_t2677, &(Bool){1});
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
    Str_delete(_t2693, &(Bool){1});
    return _t2694;
}

Expr * Expr_clone(Expr * self) {
    (void)self;
    Bool _t2695 = Bool_clone(&self->is_own_arg);
    (void)_t2695;
    Bool _t2696 = Bool_clone(&self->is_splat);
    (void)_t2696;
    Bool _t2697 = Bool_clone(&self->is_own_field);
    (void)_t2697;
    Bool _t2698 = Bool_clone(&self->is_ref_field);
    (void)_t2698;
    Bool _t2699 = Bool_clone(&self->is_ns_field);
    (void)_t2699;
    Bool _t2700 = Bool_clone(&self->is_ext);
    (void)_t2700;
    Bool _t2701 = Bool_clone(&self->is_core);
    (void)_t2701;
    Bool _t2702 = Bool_clone(&self->save_old_delete);
    (void)_t2702;
    I32 _t2703 = I32_clone(&self->total_struct_size);
    (void)_t2703;
    I32 _t2704 = I32_clone(&self->variadic_index);
    (void)_t2704;
    U32 _t2705 = U32_clone(&self->variadic_count);
    (void)_t2705;
    I32 _t2706 = I32_clone(&self->kwargs_index);
    (void)_t2706;
    U32 _t2707 = U32_clone(&self->kwargs_count);
    (void)_t2707;
    U32 _t2708 = U32_clone(&self->col);
    (void)_t2708;
    Str *_t2709 = Str_clone(&self->path);
    (void)_t2709;
    Expr *_t2710 = malloc(sizeof(Expr));
    { ExprData *_ca = ExprData_clone(&self->data); _t2710->data = *_ca; free(_ca); }
    { TilType *_ca = TilType_clone(&self->til_type); _t2710->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->struct_name); _t2710->struct_name = *_ca; free(_ca); }
    _t2710->is_own_arg = _t2695;
    _t2710->is_splat = _t2696;
    _t2710->is_own_field = _t2697;
    _t2710->is_ref_field = _t2698;
    _t2710->is_ns_field = _t2699;
    _t2710->is_ext = _t2700;
    _t2710->is_core = _t2701;
    _t2710->save_old_delete = _t2702;
    _t2710->total_struct_size = _t2703;
    _t2710->variadic_index = _t2704;
    _t2710->variadic_count = _t2705;
    _t2710->kwargs_index = _t2706;
    _t2710->kwargs_count = _t2707;
    _t2710->fn_sig = self->fn_sig;
    { Vec *_ca = Vec_clone(&self->children); _t2710->children = *_ca; free(_ca); }
    _t2710->line = U32_clone(&self->line);
    _t2710->col = _t2708;
    { Str *_ca = Str_clone(_t2709); _t2710->path = *_ca; free(_ca); }
    (void)_t2710;
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
    Str_delete(_t2709, &(Bool){1});
    return _t2710;
}

U64 *Expr_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Expr);
    return r;
}

Str * node_name(ExprData * data) {
    (void)data;
    {
        ExprData *_sw2732 = ExprData_clone(data);
        (void)_sw2732;
        Bool _t2783; { Bool *_hp = (Bool *)ExprData_eq(_sw2732, ExprData_Body()); _t2783 = *_hp; free(_hp); }
        (void)_t2783;
        if (_t2783) {
            Str *_t2733 = Str_lit("body", 4ULL);
            (void)_t2733;
            ExprData_delete(_sw2732, &(Bool){1});
            ;
            return _t2733;
        } else {
            Bool _t2782; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw2732); _t2782 = *_hp; free(_hp); }
            (void)_t2782;
            if (_t2782) {
                Str *_t2734 = Str_lit("str", 3ULL);
                (void)_t2734;
                ;
                ExprData_delete(_sw2732, &(Bool){1});
                ;
                return _t2734;
            } else {
                Bool _t2781; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw2732); _t2781 = *_hp; free(_hp); }
                (void)_t2781;
                if (_t2781) {
                    Str *_t2735 = Str_lit("num", 3ULL);
                    (void)_t2735;
                    ;
                    ;
                    ExprData_delete(_sw2732, &(Bool){1});
                    ;
                    return _t2735;
                } else {
                    Bool _t2780; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw2732); _t2780 = *_hp; free(_hp); }
                    (void)_t2780;
                    if (_t2780) {
                        Str *_t2736 = Str_lit("bool", 4ULL);
                        (void)_t2736;
                        ;
                        ;
                        ;
                        ExprData_delete(_sw2732, &(Bool){1});
                        ;
                        return _t2736;
                    } else {
                        Bool _t2779; { Bool *_hp = (Bool *)ExprData_eq(_sw2732, ExprData_LiteralNull()); _t2779 = *_hp; free(_hp); }
                        (void)_t2779;
                        if (_t2779) {
                            Str *_t2737 = Str_lit("null", 4ULL);
                            (void)_t2737;
                            ;
                            ;
                            ;
                            ;
                            ExprData_delete(_sw2732, &(Bool){1});
                            ;
                            return _t2737;
                        } else {
                            Bool _t2778; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw2732); _t2778 = *_hp; free(_hp); }
                            (void)_t2778;
                            if (_t2778) {
                                Str *_t2738 = Str_lit("ident", 5ULL);
                                (void)_t2738;
                                ;
                                ;
                                ;
                                ;
                                ;
                                ExprData_delete(_sw2732, &(Bool){1});
                                ;
                                return _t2738;
                            } else {
                                Bool _t2777; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw2732); _t2777 = *_hp; free(_hp); }
                                (void)_t2777;
                                if (_t2777) {
                                    Str *_t2739 = Str_lit("decl", 4ULL);
                                    (void)_t2739;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ExprData_delete(_sw2732, &(Bool){1});
                                    ;
                                    return _t2739;
                                } else {
                                    Bool _t2776; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw2732); _t2776 = *_hp; free(_hp); }
                                    (void)_t2776;
                                    if (_t2776) {
                                        Str *_t2740 = Str_lit("assign", 6ULL);
                                        (void)_t2740;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ExprData_delete(_sw2732, &(Bool){1});
                                        ;
                                        return _t2740;
                                    } else {
                                        Bool _t2775; { Bool *_hp = (Bool *)ExprData_eq(_sw2732, ExprData_FCall()); _t2775 = *_hp; free(_hp); }
                                        (void)_t2775;
                                        if (_t2775) {
                                            Str *_t2741 = Str_lit("fcall", 5ULL);
                                            (void)_t2741;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ExprData_delete(_sw2732, &(Bool){1});
                                            ;
                                            return _t2741;
                                        } else {
                                            Bool _t2774; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw2732); _t2774 = *_hp; free(_hp); }
                                            (void)_t2774;
                                            if (_t2774) {
                                                Str *_t2742 = Str_lit("func_def", 8ULL);
                                                (void)_t2742;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ExprData_delete(_sw2732, &(Bool){1});
                                                ;
                                                return _t2742;
                                            } else {
                                                Bool _t2773; { Bool *_hp = (Bool *)ExprData_eq(_sw2732, ExprData_StructDef()); _t2773 = *_hp; free(_hp); }
                                                (void)_t2773;
                                                if (_t2773) {
                                                    Str *_t2743 = Str_lit("struct_def", 10ULL);
                                                    (void)_t2743;
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
                                                    ExprData_delete(_sw2732, &(Bool){1});
                                                    ;
                                                    return _t2743;
                                                } else {
                                                    Bool _t2772; { Bool *_hp = (Bool *)ExprData_eq(_sw2732, ExprData_EnumDef()); _t2772 = *_hp; free(_hp); }
                                                    (void)_t2772;
                                                    if (_t2772) {
                                                        Str *_t2744 = Str_lit("enum_def", 8ULL);
                                                        (void)_t2744;
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
                                                        ExprData_delete(_sw2732, &(Bool){1});
                                                        ;
                                                        return _t2744;
                                                    } else {
                                                        Bool _t2771; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(_sw2732); _t2771 = *_hp; free(_hp); }
                                                        (void)_t2771;
                                                        if (_t2771) {
                                                            Str *_t2745 = Str_lit("field_access", 12ULL);
                                                            (void)_t2745;
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
                                                            ExprData_delete(_sw2732, &(Bool){1});
                                                            ;
                                                            return _t2745;
                                                        } else {
                                                            Bool _t2770; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(_sw2732); _t2770 = *_hp; free(_hp); }
                                                            (void)_t2770;
                                                            if (_t2770) {
                                                                Str *_t2746 = Str_lit("field_assign", 12ULL);
                                                                (void)_t2746;
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
                                                                ExprData_delete(_sw2732, &(Bool){1});
                                                                ;
                                                                return _t2746;
                                                            } else {
                                                                Bool _t2769; { Bool *_hp = (Bool *)ExprData_eq(_sw2732, ExprData_Return()); _t2769 = *_hp; free(_hp); }
                                                                (void)_t2769;
                                                                if (_t2769) {
                                                                    Str *_t2747 = Str_lit("return", 6ULL);
                                                                    (void)_t2747;
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
                                                                    ExprData_delete(_sw2732, &(Bool){1});
                                                                    ;
                                                                    return _t2747;
                                                                } else {
                                                                    Bool _t2768; { Bool *_hp = (Bool *)ExprData_eq(_sw2732, ExprData_If()); _t2768 = *_hp; free(_hp); }
                                                                    (void)_t2768;
                                                                    if (_t2768) {
                                                                        Str *_t2748 = Str_lit("if", 2ULL);
                                                                        (void)_t2748;
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
                                                                        ExprData_delete(_sw2732, &(Bool){1});
                                                                        ;
                                                                        return _t2748;
                                                                    } else {
                                                                        Bool _t2767; { Bool *_hp = (Bool *)ExprData_eq(_sw2732, ExprData_While()); _t2767 = *_hp; free(_hp); }
                                                                        (void)_t2767;
                                                                        if (_t2767) {
                                                                            Str *_t2749 = Str_lit("while", 5ULL);
                                                                            (void)_t2749;
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
                                                                            ExprData_delete(_sw2732, &(Bool){1});
                                                                            ;
                                                                            return _t2749;
                                                                        } else {
                                                                            Bool _t2766; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw2732); _t2766 = *_hp; free(_hp); }
                                                                            (void)_t2766;
                                                                            if (_t2766) {
                                                                                Str *_t2750 = Str_lit("for_in", 6ULL);
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
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ExprData_delete(_sw2732, &(Bool){1});
                                                                                ;
                                                                                return _t2750;
                                                                            } else {
                                                                                Bool _t2765; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw2732); _t2765 = *_hp; free(_hp); }
                                                                                (void)_t2765;
                                                                                if (_t2765) {
                                                                                    Str *_t2751 = Str_lit("named_arg", 9ULL);
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
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ExprData_delete(_sw2732, &(Bool){1});
                                                                                    ;
                                                                                    return _t2751;
                                                                                } else {
                                                                                    Bool _t2764; { Bool *_hp = (Bool *)ExprData_eq(_sw2732, ExprData_Break()); _t2764 = *_hp; free(_hp); }
                                                                                    (void)_t2764;
                                                                                    if (_t2764) {
                                                                                        Str *_t2752 = Str_lit("break", 5ULL);
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
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ExprData_delete(_sw2732, &(Bool){1});
                                                                                        ;
                                                                                        return _t2752;
                                                                                    } else {
                                                                                        Bool _t2763; { Bool *_hp = (Bool *)ExprData_eq(_sw2732, ExprData_Continue()); _t2763 = *_hp; free(_hp); }
                                                                                        (void)_t2763;
                                                                                        if (_t2763) {
                                                                                            Str *_t2753 = Str_lit("continue", 8ULL);
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
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ExprData_delete(_sw2732, &(Bool){1});
                                                                                            ;
                                                                                            return _t2753;
                                                                                        } else {
                                                                                            Bool _t2762; { Bool *_hp = (Bool *)ExprData_eq(_sw2732, ExprData_MapLit()); _t2762 = *_hp; free(_hp); }
                                                                                            (void)_t2762;
                                                                                            if (_t2762) {
                                                                                                Str *_t2754 = Str_lit("map_lit", 7ULL);
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
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ExprData_delete(_sw2732, &(Bool){1});
                                                                                                ;
                                                                                                return _t2754;
                                                                                            } else {
                                                                                                Bool _t2761; { Bool *_hp = (Bool *)ExprData_eq(_sw2732, ExprData_SetLit()); _t2761 = *_hp; free(_hp); }
                                                                                                (void)_t2761;
                                                                                                if (_t2761) {
                                                                                                    Str *_t2755 = Str_lit("set_lit", 7ULL);
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
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ExprData_delete(_sw2732, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t2755;
                                                                                                } else {
                                                                                                    Bool _t2760; { Bool *_hp = (Bool *)ExprData_eq(_sw2732, ExprData_Switch()); _t2760 = *_hp; free(_hp); }
                                                                                                    (void)_t2760;
                                                                                                    if (_t2760) {
                                                                                                        Str *_t2756 = Str_lit("switch", 6ULL);
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
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ExprData_delete(_sw2732, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t2756;
                                                                                                    } else {
                                                                                                        Bool _t2759; { Bool *_hp = (Bool *)ExprData_eq(_sw2732, ExprData_Case()); _t2759 = *_hp; free(_hp); }
                                                                                                        (void)_t2759;
                                                                                                        if (_t2759) {
                                                                                                            Str *_t2757 = Str_lit("case", 4ULL);
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
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ExprData_delete(_sw2732, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t2757;
                                                                                                        } else {
                                                                                                            Str *_t2758 = Str_lit("?", 1ULL);
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
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ExprData_delete(_sw2732, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t2758;
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
        ExprData_delete(_sw2732, &(Bool){1});
        ;
    }
}

Str * func_type_name(FuncType * ft) {
    (void)ft;
    {
        FuncType *_sw2784 = FuncType_clone(ft);
        (void)_sw2784;
        Bool _t2797; { Bool *_hp = (Bool *)FuncType_eq(_sw2784, FuncType_Func()); _t2797 = *_hp; free(_hp); }
        (void)_t2797;
        if (_t2797) {
            Str *_t2785 = Str_lit("func", 4ULL);
            (void)_t2785;
            FuncType_delete(_sw2784, &(Bool){1});
            ;
            return _t2785;
        } else {
            Bool _t2796; { Bool *_hp = (Bool *)FuncType_eq(_sw2784, FuncType_Proc()); _t2796 = *_hp; free(_hp); }
            (void)_t2796;
            if (_t2796) {
                Str *_t2786 = Str_lit("proc", 4ULL);
                (void)_t2786;
                ;
                FuncType_delete(_sw2784, &(Bool){1});
                ;
                return _t2786;
            } else {
                Bool _t2795; { Bool *_hp = (Bool *)FuncType_eq(_sw2784, FuncType_Test()); _t2795 = *_hp; free(_hp); }
                (void)_t2795;
                if (_t2795) {
                    Str *_t2787 = Str_lit("test", 4ULL);
                    (void)_t2787;
                    ;
                    ;
                    FuncType_delete(_sw2784, &(Bool){1});
                    ;
                    return _t2787;
                } else {
                    Bool _t2794; { Bool *_hp = (Bool *)FuncType_eq(_sw2784, FuncType_Macro()); _t2794 = *_hp; free(_hp); }
                    (void)_t2794;
                    if (_t2794) {
                        Str *_t2788 = Str_lit("macro", 5ULL);
                        (void)_t2788;
                        ;
                        ;
                        ;
                        FuncType_delete(_sw2784, &(Bool){1});
                        ;
                        return _t2788;
                    } else {
                        Bool _t2793; { Bool *_hp = (Bool *)FuncType_eq(_sw2784, FuncType_ExtFunc()); _t2793 = *_hp; free(_hp); }
                        (void)_t2793;
                        if (_t2793) {
                            Str *_t2789 = Str_lit("ext_func", 8ULL);
                            (void)_t2789;
                            ;
                            ;
                            ;
                            ;
                            FuncType_delete(_sw2784, &(Bool){1});
                            ;
                            return _t2789;
                        } else {
                            Bool _t2792; { Bool *_hp = (Bool *)FuncType_eq(_sw2784, FuncType_ExtProc()); _t2792 = *_hp; free(_hp); }
                            (void)_t2792;
                            if (_t2792) {
                                Str *_t2790 = Str_lit("ext_proc", 8ULL);
                                (void)_t2790;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw2784, &(Bool){1});
                                ;
                                return _t2790;
                            } else {
                                Str *_t2791 = Str_lit("?", 1ULL);
                                (void)_t2791;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw2784, &(Bool){1});
                                ;
                                return _t2791;
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
        FuncType_delete(_sw2784, &(Bool){1});
        ;
    }
}

void ast_print(Expr * e, U32 indent) {
    (void)e;
    (void)indent;
    {
        U64 _fi2798 = 0;
        (void)_fi2798;
        while (1) {
            I64 _t2800 = U32_to_i64(indent);
            (void)_t2800;
            U64 _t2801 = 0;
            (void)_t2801;
            U64 _t2802 = I64_to_u64(_t2800);
            (void)_t2802;
            ;
            Range *_t2803 = Range_new(_t2801, _t2802);
            (void)_t2803;
            ;
            ;
            U64 _t2804; { U64 *_hp = (U64 *)Range_len(_t2803); _t2804 = *_hp; free(_hp); }
            (void)_t2804;
            Range_delete(_t2803, &(Bool){1});
            Bool _wcond2799; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2798}, &(U64){_t2804}); _wcond2799 = *_hp; free(_hp); }
            (void)_wcond2799;
            ;
            if (_wcond2799) {
            } else {
                ;
                break;
            }
            ;
            I64 _t2805 = U32_to_i64(indent);
            (void)_t2805;
            U64 _t2806 = 0;
            (void)_t2806;
            U64 _t2807 = I64_to_u64(_t2805);
            (void)_t2807;
            ;
            Range *_t2808 = Range_new(_t2806, _t2807);
            (void)_t2808;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t2808, _fi2798); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t2808, &(Bool){1});
            ;
            U64 _t2809 = 1;
            (void)_t2809;
            U64 _t2810 = U64_add(_fi2798, _t2809);
            (void)_t2810;
            ;
            _fi2798 = _t2810;
            ;
            Str *_t2811 = Str_lit("Str", 3ULL);
            (void)_t2811;
            U64 _t2812; { U64 *_hp = (U64 *)Str_size(); _t2812 = *_hp; free(_hp); }
            (void)_t2812;
            U64 _t2813 = 1;
            (void)_t2813;
            Array *_va38 = Array_new(_t2811, &(U64){_t2812}, &(U64){_t2813});
            (void)_va38;
            Str_delete(_t2811, &(Bool){1});
            ;
            ;
            U64 _t2814 = 0;
            (void)_t2814;
            Str *_t2815 = Str_lit("  ", 2ULL);
            (void)_t2815;
            Array_set(_va38, &(U64){_t2814}, _t2815);
            ;
            print(_va38);
        }
        ;
    }
    Str *_t2949 = Str_lit("Str", 3ULL);
    (void)_t2949;
    U64 _t2950; { U64 *_hp = (U64 *)Str_size(); _t2950 = *_hp; free(_hp); }
    (void)_t2950;
    U64 _t2951 = 2;
    (void)_t2951;
    Array *_va52 = Array_new(_t2949, &(U64){_t2950}, &(U64){_t2951});
    (void)_va52;
    Str_delete(_t2949, &(Bool){1});
    ;
    ;
    U64 _t2952 = 0;
    (void)_t2952;
    Str *_t2953 = Str_lit("(", 1ULL);
    (void)_t2953;
    Array_set(_va52, &(U64){_t2952}, _t2953);
    ;
    U64 _t2954 = 1;
    (void)_t2954;
    Str *_t2955 = node_name(&e->data);
    (void)_t2955;
    Array_set(_va52, &(U64){_t2954}, _t2955);
    ;
    print(_va52);
    Bool _t2956; { Bool *_hp = (Bool *)TilType_eq(&e->til_type, TilType_Unknown()); _t2956 = *_hp; free(_hp); }
    (void)_t2956;
    Bool _t2957 = Bool_not(_t2956);
    (void)_t2957;
    ;
    if (_t2957) {
        Str *_t2816 = Str_lit("Str", 3ULL);
        (void)_t2816;
        U64 _t2817; { U64 *_hp = (U64 *)Str_size(); _t2817 = *_hp; free(_hp); }
        (void)_t2817;
        U64 _t2818 = 2;
        (void)_t2818;
        Array *_va39 = Array_new(_t2816, &(U64){_t2817}, &(U64){_t2818});
        (void)_va39;
        Str_delete(_t2816, &(Bool){1});
        ;
        ;
        U64 _t2819 = 0;
        (void)_t2819;
        Str *_t2820 = Str_lit(":", 1ULL);
        (void)_t2820;
        Array_set(_va39, &(U64){_t2819}, _t2820);
        ;
        U64 _t2821 = 1;
        (void)_t2821;
        Str *_t2822 = til_type_name_c(&e->til_type);
        (void)_t2822;
        Array_set(_va39, &(U64){_t2821}, _t2822);
        ;
        print(_va39);
    }
    ;
    {
        ExprData *_sw2823 = ExprData_clone(&e->data);
        (void)_sw2823;
        Bool _t2910; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw2823); _t2910 = *_hp; free(_hp); }
        (void)_t2910;
        if (_t2910) {
            Str *s = ExprData_get_Ident(_sw2823);
            (void)s;
            Str *_t2824 = Str_lit("Str", 3ULL);
            (void)_t2824;
            U64 _t2825; { U64 *_hp = (U64 *)Str_size(); _t2825 = *_hp; free(_hp); }
            (void)_t2825;
            U64 _t2826 = 3;
            (void)_t2826;
            Array *_va40 = Array_new(_t2824, &(U64){_t2825}, &(U64){_t2826});
            (void)_va40;
            Str_delete(_t2824, &(Bool){1});
            ;
            ;
            U64 _t2827 = 0;
            (void)_t2827;
            Str *_t2828 = Str_lit(" \"", 3ULL);
            (void)_t2828;
            Array_set(_va40, &(U64){_t2827}, _t2828);
            ;
            U64 _t2829 = 1;
            (void)_t2829;
            Str *_t2830 = Str_clone(s);
            (void)_t2830;
            Str_delete(s, &(Bool){1});
            Array_set(_va40, &(U64){_t2829}, _t2830);
            ;
            U64 _t2831 = 2;
            (void)_t2831;
            Str *_t2832 = Str_lit("\"", 2ULL);
            (void)_t2832;
            Array_set(_va40, &(U64){_t2831}, _t2832);
            ;
            print(_va40);
        } else {
            Bool _t2909; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw2823); _t2909 = *_hp; free(_hp); }
            (void)_t2909;
            if (_t2909) {
                Str *s = ExprData_get_LiteralStr(_sw2823);
                (void)s;
                Str *_t2833 = Str_lit("Str", 3ULL);
                (void)_t2833;
                U64 _t2834; { U64 *_hp = (U64 *)Str_size(); _t2834 = *_hp; free(_hp); }
                (void)_t2834;
                U64 _t2835 = 3;
                (void)_t2835;
                Array *_va41 = Array_new(_t2833, &(U64){_t2834}, &(U64){_t2835});
                (void)_va41;
                Str_delete(_t2833, &(Bool){1});
                ;
                ;
                U64 _t2836 = 0;
                (void)_t2836;
                Str *_t2837 = Str_lit(" \"", 3ULL);
                (void)_t2837;
                Array_set(_va41, &(U64){_t2836}, _t2837);
                ;
                U64 _t2838 = 1;
                (void)_t2838;
                Str *_t2839 = Str_clone(s);
                (void)_t2839;
                Str_delete(s, &(Bool){1});
                Array_set(_va41, &(U64){_t2838}, _t2839);
                ;
                U64 _t2840 = 2;
                (void)_t2840;
                Str *_t2841 = Str_lit("\"", 2ULL);
                (void)_t2841;
                Array_set(_va41, &(U64){_t2840}, _t2841);
                ;
                print(_va41);
            } else {
                Bool _t2908; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw2823); _t2908 = *_hp; free(_hp); }
                (void)_t2908;
                if (_t2908) {
                    Str *s = ExprData_get_LiteralNum(_sw2823);
                    (void)s;
                    Str *_t2842 = Str_lit("Str", 3ULL);
                    (void)_t2842;
                    U64 _t2843; { U64 *_hp = (U64 *)Str_size(); _t2843 = *_hp; free(_hp); }
                    (void)_t2843;
                    U64 _t2844 = 3;
                    (void)_t2844;
                    Array *_va42 = Array_new(_t2842, &(U64){_t2843}, &(U64){_t2844});
                    (void)_va42;
                    Str_delete(_t2842, &(Bool){1});
                    ;
                    ;
                    U64 _t2845 = 0;
                    (void)_t2845;
                    Str *_t2846 = Str_lit(" \"", 3ULL);
                    (void)_t2846;
                    Array_set(_va42, &(U64){_t2845}, _t2846);
                    ;
                    U64 _t2847 = 1;
                    (void)_t2847;
                    Str *_t2848 = Str_clone(s);
                    (void)_t2848;
                    Str_delete(s, &(Bool){1});
                    Array_set(_va42, &(U64){_t2847}, _t2848);
                    ;
                    U64 _t2849 = 2;
                    (void)_t2849;
                    Str *_t2850 = Str_lit("\"", 2ULL);
                    (void)_t2850;
                    Array_set(_va42, &(U64){_t2849}, _t2850);
                    ;
                    print(_va42);
                } else {
                    Bool _t2907; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw2823); _t2907 = *_hp; free(_hp); }
                    (void)_t2907;
                    if (_t2907) {
                        Str *s = ExprData_get_LiteralBool(_sw2823);
                        (void)s;
                        Str *_t2851 = Str_lit("Str", 3ULL);
                        (void)_t2851;
                        U64 _t2852; { U64 *_hp = (U64 *)Str_size(); _t2852 = *_hp; free(_hp); }
                        (void)_t2852;
                        U64 _t2853 = 3;
                        (void)_t2853;
                        Array *_va43 = Array_new(_t2851, &(U64){_t2852}, &(U64){_t2853});
                        (void)_va43;
                        Str_delete(_t2851, &(Bool){1});
                        ;
                        ;
                        U64 _t2854 = 0;
                        (void)_t2854;
                        Str *_t2855 = Str_lit(" \"", 3ULL);
                        (void)_t2855;
                        Array_set(_va43, &(U64){_t2854}, _t2855);
                        ;
                        U64 _t2856 = 1;
                        (void)_t2856;
                        Str *_t2857 = Str_clone(s);
                        (void)_t2857;
                        Str_delete(s, &(Bool){1});
                        Array_set(_va43, &(U64){_t2856}, _t2857);
                        ;
                        U64 _t2858 = 2;
                        (void)_t2858;
                        Str *_t2859 = Str_lit("\"", 2ULL);
                        (void)_t2859;
                        Array_set(_va43, &(U64){_t2858}, _t2859);
                        ;
                        print(_va43);
                    } else {
                        Bool _t2906; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw2823); _t2906 = *_hp; free(_hp); }
                        (void)_t2906;
                        if (_t2906) {
                            Str *s = ExprData_get_ForIn(_sw2823);
                            (void)s;
                            Str *_t2860 = Str_lit("Str", 3ULL);
                            (void)_t2860;
                            U64 _t2861; { U64 *_hp = (U64 *)Str_size(); _t2861 = *_hp; free(_hp); }
                            (void)_t2861;
                            U64 _t2862 = 3;
                            (void)_t2862;
                            Array *_va44 = Array_new(_t2860, &(U64){_t2861}, &(U64){_t2862});
                            (void)_va44;
                            Str_delete(_t2860, &(Bool){1});
                            ;
                            ;
                            U64 _t2863 = 0;
                            (void)_t2863;
                            Str *_t2864 = Str_lit(" \"", 3ULL);
                            (void)_t2864;
                            Array_set(_va44, &(U64){_t2863}, _t2864);
                            ;
                            U64 _t2865 = 1;
                            (void)_t2865;
                            Str *_t2866 = Str_clone(s);
                            (void)_t2866;
                            Str_delete(s, &(Bool){1});
                            Array_set(_va44, &(U64){_t2865}, _t2866);
                            ;
                            U64 _t2867 = 2;
                            (void)_t2867;
                            Str *_t2868 = Str_lit("\"", 2ULL);
                            (void)_t2868;
                            Array_set(_va44, &(U64){_t2867}, _t2868);
                            ;
                            print(_va44);
                        } else {
                            Bool _t2905; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw2823); _t2905 = *_hp; free(_hp); }
                            (void)_t2905;
                            if (_t2905) {
                                Declaration *decl = ExprData_get_Decl(_sw2823);
                                (void)decl;
                                if (decl->is_mut) {
                                    Str *_t2869 = Str_lit("Str", 3ULL);
                                    (void)_t2869;
                                    U64 _t2870; { U64 *_hp = (U64 *)Str_size(); _t2870 = *_hp; free(_hp); }
                                    (void)_t2870;
                                    U64 _t2871 = 1;
                                    (void)_t2871;
                                    Array *_va45 = Array_new(_t2869, &(U64){_t2870}, &(U64){_t2871});
                                    (void)_va45;
                                    Str_delete(_t2869, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t2872 = 0;
                                    (void)_t2872;
                                    Str *_t2873 = Str_lit(" mut", 4ULL);
                                    (void)_t2873;
                                    Array_set(_va45, &(U64){_t2872}, _t2873);
                                    ;
                                    print(_va45);
                                }
                                Str *_t2874 = Str_lit("Str", 3ULL);
                                (void)_t2874;
                                U64 _t2875; { U64 *_hp = (U64 *)Str_size(); _t2875 = *_hp; free(_hp); }
                                (void)_t2875;
                                U64 _t2876 = 2;
                                (void)_t2876;
                                Array *_va46 = Array_new(_t2874, &(U64){_t2875}, &(U64){_t2876});
                                (void)_va46;
                                Str_delete(_t2874, &(Bool){1});
                                ;
                                ;
                                U64 _t2877 = 0;
                                (void)_t2877;
                                Str *_t2878 = Str_lit(" ", 1ULL);
                                (void)_t2878;
                                Array_set(_va46, &(U64){_t2877}, _t2878);
                                ;
                                U64 _t2879 = 1;
                                (void)_t2879;
                                Str *_t2880 = Str_clone(&decl->name);
                                (void)_t2880;
                                Declaration_delete(decl, &(Bool){1});
                                Array_set(_va46, &(U64){_t2879}, _t2880);
                                ;
                                print(_va46);
                            } else {
                                Bool _t2904; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw2823); _t2904 = *_hp; free(_hp); }
                                (void)_t2904;
                                if (_t2904) {
                                    Str *s = ExprData_get_Assign(_sw2823);
                                    (void)s;
                                    Str *_t2881 = Str_lit("Str", 3ULL);
                                    (void)_t2881;
                                    U64 _t2882; { U64 *_hp = (U64 *)Str_size(); _t2882 = *_hp; free(_hp); }
                                    (void)_t2882;
                                    U64 _t2883 = 2;
                                    (void)_t2883;
                                    Array *_va47 = Array_new(_t2881, &(U64){_t2882}, &(U64){_t2883});
                                    (void)_va47;
                                    Str_delete(_t2881, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t2884 = 0;
                                    (void)_t2884;
                                    Str *_t2885 = Str_lit(" ", 1ULL);
                                    (void)_t2885;
                                    Array_set(_va47, &(U64){_t2884}, _t2885);
                                    ;
                                    U64 _t2886 = 1;
                                    (void)_t2886;
                                    Str *_t2887 = Str_clone(s);
                                    (void)_t2887;
                                    Str_delete(s, &(Bool){1});
                                    Array_set(_va47, &(U64){_t2886}, _t2887);
                                    ;
                                    print(_va47);
                                } else {
                                    Bool _t2903; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw2823); _t2903 = *_hp; free(_hp); }
                                    (void)_t2903;
                                    if (_t2903) {
                                        Str *s = ExprData_get_NamedArg(_sw2823);
                                        (void)s;
                                        Str *_t2888 = Str_lit("Str", 3ULL);
                                        (void)_t2888;
                                        U64 _t2889; { U64 *_hp = (U64 *)Str_size(); _t2889 = *_hp; free(_hp); }
                                        (void)_t2889;
                                        U64 _t2890 = 2;
                                        (void)_t2890;
                                        Array *_va48 = Array_new(_t2888, &(U64){_t2889}, &(U64){_t2890});
                                        (void)_va48;
                                        Str_delete(_t2888, &(Bool){1});
                                        ;
                                        ;
                                        U64 _t2891 = 0;
                                        (void)_t2891;
                                        Str *_t2892 = Str_lit(" ", 1ULL);
                                        (void)_t2892;
                                        Array_set(_va48, &(U64){_t2891}, _t2892);
                                        ;
                                        U64 _t2893 = 1;
                                        (void)_t2893;
                                        Str *_t2894 = Str_clone(s);
                                        (void)_t2894;
                                        Str_delete(s, &(Bool){1});
                                        Array_set(_va48, &(U64){_t2893}, _t2894);
                                        ;
                                        print(_va48);
                                    } else {
                                        Bool _t2902; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw2823); _t2902 = *_hp; free(_hp); }
                                        (void)_t2902;
                                        if (_t2902) {
                                            FunctionDef *fdef = ExprData_get_FuncDef(_sw2823);
                                            (void)fdef;
                                            Str *_t2895 = Str_lit("Str", 3ULL);
                                            (void)_t2895;
                                            U64 _t2896; { U64 *_hp = (U64 *)Str_size(); _t2896 = *_hp; free(_hp); }
                                            (void)_t2896;
                                            U64 _t2897 = 2;
                                            (void)_t2897;
                                            Array *_va49 = Array_new(_t2895, &(U64){_t2896}, &(U64){_t2897});
                                            (void)_va49;
                                            Str_delete(_t2895, &(Bool){1});
                                            ;
                                            ;
                                            U64 _t2898 = 0;
                                            (void)_t2898;
                                            Str *_t2899 = Str_lit(" ", 1ULL);
                                            (void)_t2899;
                                            Array_set(_va49, &(U64){_t2898}, _t2899);
                                            ;
                                            U64 _t2900 = 1;
                                            (void)_t2900;
                                            Str *_t2901 = func_type_name(&fdef->func_type);
                                            (void)_t2901;
                                            FunctionDef_delete(fdef, &(Bool){1});
                                            Array_set(_va49, &(U64){_t2900}, _t2901);
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
        ExprData_delete(_sw2823, &(Bool){1});
        ;
    }
    U64 _t2958; { U64 *_hp = (U64 *)Vec_len(&e->children); _t2958 = *_hp; free(_hp); }
    (void)_t2958;
    U64 _t2959 = 0;
    (void)_t2959;
    Bool _t2960; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2958}, &(U64){_t2959}); _t2960 = *_hp; free(_hp); }
    (void)_t2960;
    ;
    ;
    if (_t2960) {
        Str *_t2944 = Str_lit("Str", 3ULL);
        (void)_t2944;
        U64 _t2945; { U64 *_hp = (U64 *)Str_size(); _t2945 = *_hp; free(_hp); }
        (void)_t2945;
        U64 _t2946 = 1;
        (void)_t2946;
        Array *_va51 = Array_new(_t2944, &(U64){_t2945}, &(U64){_t2946});
        (void)_va51;
        Str_delete(_t2944, &(Bool){1});
        ;
        ;
        U64 _t2947 = 0;
        (void)_t2947;
        Str *_t2948 = Str_lit("", 0ULL);
        (void)_t2948;
        Array_set(_va51, &(U64){_t2947}, _t2948);
        ;
        println(_va51);
        {
            U64 _fi2911 = 0;
            (void)_fi2911;
            while (1) {
                U64 _t2913 = 0;
                (void)_t2913;
                U64 _t2914; { U64 *_hp = (U64 *)Vec_len(&e->children); _t2914 = *_hp; free(_hp); }
                (void)_t2914;
                Range *_t2915 = Range_new(_t2913, _t2914);
                (void)_t2915;
                ;
                ;
                U64 _t2916; { U64 *_hp = (U64 *)Range_len(_t2915); _t2916 = *_hp; free(_hp); }
                (void)_t2916;
                Range_delete(_t2915, &(Bool){1});
                Bool _wcond2912; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2911}, &(U64){_t2916}); _wcond2912 = *_hp; free(_hp); }
                (void)_wcond2912;
                ;
                if (_wcond2912) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t2917 = 0;
                (void)_t2917;
                U64 _t2918; { U64 *_hp = (U64 *)Vec_len(&e->children); _t2918 = *_hp; free(_hp); }
                (void)_t2918;
                Range *_t2919 = Range_new(_t2917, _t2918);
                (void)_t2919;
                ;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t2919, _fi2911); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t2919, &(Bool){1});
                U64 _t2920 = 1;
                (void)_t2920;
                U64 _t2921 = U64_add(_fi2911, _t2920);
                (void)_t2921;
                ;
                _fi2911 = _t2921;
                ;
                I64 *_t2922 = malloc(sizeof(I64)); *_t2922 = U64_to_i64(i);
                (void)_t2922;
                ;
                U32 _t2923 = 1;
                (void)_t2923;
                Expr *_t2924 = Expr_child(e, _t2922);
                (void)_t2924;
                U32 _t2925 = U32_add(indent, _t2923);
                (void)_t2925;
                ;
                ast_print(_t2924, _t2925);
                I64_delete(_t2922, &(Bool){1});
                ;
            }
            ;
        }
        {
            U64 _fi2926 = 0;
            (void)_fi2926;
            while (1) {
                I64 _t2928 = U32_to_i64(indent);
                (void)_t2928;
                U64 _t2929 = 0;
                (void)_t2929;
                U64 _t2930 = I64_to_u64(_t2928);
                (void)_t2930;
                ;
                Range *_t2931 = Range_new(_t2929, _t2930);
                (void)_t2931;
                ;
                ;
                U64 _t2932; { U64 *_hp = (U64 *)Range_len(_t2931); _t2932 = *_hp; free(_hp); }
                (void)_t2932;
                Range_delete(_t2931, &(Bool){1});
                Bool _wcond2927; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2926}, &(U64){_t2932}); _wcond2927 = *_hp; free(_hp); }
                (void)_wcond2927;
                ;
                if (_wcond2927) {
                } else {
                    ;
                    break;
                }
                ;
                I64 _t2933 = U32_to_i64(indent);
                (void)_t2933;
                U64 _t2934 = 0;
                (void)_t2934;
                U64 _t2935 = I64_to_u64(_t2933);
                (void)_t2935;
                ;
                Range *_t2936 = Range_new(_t2934, _t2935);
                (void)_t2936;
                ;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t2936, _fi2926); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t2936, &(Bool){1});
                ;
                U64 _t2937 = 1;
                (void)_t2937;
                U64 _t2938 = U64_add(_fi2926, _t2937);
                (void)_t2938;
                ;
                _fi2926 = _t2938;
                ;
                Str *_t2939 = Str_lit("Str", 3ULL);
                (void)_t2939;
                U64 _t2940; { U64 *_hp = (U64 *)Str_size(); _t2940 = *_hp; free(_hp); }
                (void)_t2940;
                U64 _t2941 = 1;
                (void)_t2941;
                Array *_va50 = Array_new(_t2939, &(U64){_t2940}, &(U64){_t2941});
                (void)_va50;
                Str_delete(_t2939, &(Bool){1});
                ;
                ;
                U64 _t2942 = 0;
                (void)_t2942;
                Str *_t2943 = Str_lit("  ", 2ULL);
                (void)_t2943;
                Array_set(_va50, &(U64){_t2942}, _t2943);
                ;
                print(_va50);
            }
            ;
        }
    }
    ;
    Str *_t2961 = Str_lit("Str", 3ULL);
    (void)_t2961;
    U64 _t2962; { U64 *_hp = (U64 *)Str_size(); _t2962 = *_hp; free(_hp); }
    (void)_t2962;
    U64 _t2963 = 1;
    (void)_t2963;
    Array *_va53 = Array_new(_t2961, &(U64){_t2962}, &(U64){_t2963});
    (void)_va53;
    Str_delete(_t2961, &(Bool){1});
    ;
    ;
    U64 _t2964 = 0;
    (void)_t2964;
    Str *_t2965 = Str_lit(")", 1ULL);
    (void)_t2965;
    Array_set(_va53, &(U64){_t2964}, _t2965);
    ;
    println(_va53);
}

Bool * enum_has_payloads(Expr * enum_def) {
    (void)enum_def;
    I64 *_t2987 = malloc(sizeof(I64));
    *_t2987 = 0;
    (void)_t2987;
    Expr *body = Expr_child(enum_def, _t2987);
    (void)body;
    {
        U64 _fi2966 = 0;
        (void)_fi2966;
        while (1) {
            I64 _t2974; { I64 *_hp = (I64 *)Expr_child_count(body); _t2974 = *_hp; free(_hp); }
            (void)_t2974;
            U64 _t2975 = 0;
            (void)_t2975;
            U64 _t2976 = I64_to_u64(_t2974);
            (void)_t2976;
            ;
            Range *_t2977 = Range_new(_t2975, _t2976);
            (void)_t2977;
            ;
            ;
            U64 _t2978; { U64 *_hp = (U64 *)Range_len(_t2977); _t2978 = *_hp; free(_hp); }
            (void)_t2978;
            Range_delete(_t2977, &(Bool){1});
            Bool _wcond2967; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2966}, &(U64){_t2978}); _wcond2967 = *_hp; free(_hp); }
            (void)_wcond2967;
            ;
            if (_wcond2967) {
            } else {
                ;
                break;
            }
            ;
            I64 _t2979; { I64 *_hp = (I64 *)Expr_child_count(body); _t2979 = *_hp; free(_hp); }
            (void)_t2979;
            U64 _t2980 = 0;
            (void)_t2980;
            U64 _t2981 = I64_to_u64(_t2979);
            (void)_t2981;
            ;
            Range *_t2982 = Range_new(_t2980, _t2981);
            (void)_t2982;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t2982, _fi2966); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t2982, &(Bool){1});
            U64 _t2983 = 1;
            (void)_t2983;
            U64 _t2984 = U64_add(_fi2966, _t2983);
            (void)_t2984;
            ;
            _fi2966 = _t2984;
            ;
            I64 *_t2985 = malloc(sizeof(I64)); *_t2985 = U64_to_i64(i);
            (void)_t2985;
            ;
            Expr *f = Expr_child(body, _t2985);
            (void)f;
            Bool _t2986; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2986 = *_hp; free(_hp); }
            (void)_t2986;
            if (_t2986) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                U64 _t2969; { U64 *_hp = (U64 *)Str_len(&decl->explicit_type); _t2969 = *_hp; free(_hp); }
                (void)_t2969;
                U64 _t2970 = 0;
                (void)_t2970;
                Bool _t2971 = Bool_not(decl->is_namespace);
                (void)_t2971;
                Declaration_delete(decl, &(Bool){1});
                Bool _t2972; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2969}, &(U64){_t2970}); _t2972 = *_hp; free(_hp); }
                (void)_t2972;
                ;
                ;
                Bool _t2973 = Bool_and(_t2971, _t2972);
                (void)_t2973;
                ;
                ;
                if (_t2973) {
                    Bool _t2968 = 1;
                    (void)_t2968;
                    ;
                    I64_delete(_t2985, &(Bool){1});
                    ;
                    ;
                    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2968; return _r; }
                }
                ;
            }
            I64_delete(_t2985, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t2987, &(Bool){1});
    Bool _t2988 = 0;
    (void)_t2988;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2988; return _r; }
}

I32 * enum_variant_tag(Expr * enum_def, Str * variant_name) {
    (void)enum_def;
    (void)variant_name;
    I64 *_t3008 = malloc(sizeof(I64));
    *_t3008 = 0;
    (void)_t3008;
    Expr *body = Expr_child(enum_def, _t3008);
    (void)body;
    I32 tag = 0;
    (void)tag;
    {
        U64 _fi2989 = 0;
        (void)_fi2989;
        while (1) {
            I64 _t2995; { I64 *_hp = (I64 *)Expr_child_count(body); _t2995 = *_hp; free(_hp); }
            (void)_t2995;
            U64 _t2996 = 0;
            (void)_t2996;
            U64 _t2997 = I64_to_u64(_t2995);
            (void)_t2997;
            ;
            Range *_t2998 = Range_new(_t2996, _t2997);
            (void)_t2998;
            ;
            ;
            U64 _t2999; { U64 *_hp = (U64 *)Range_len(_t2998); _t2999 = *_hp; free(_hp); }
            (void)_t2999;
            Range_delete(_t2998, &(Bool){1});
            Bool _wcond2990; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2989}, &(U64){_t2999}); _wcond2990 = *_hp; free(_hp); }
            (void)_wcond2990;
            ;
            if (_wcond2990) {
            } else {
                ;
                break;
            }
            ;
            I64 _t3000; { I64 *_hp = (I64 *)Expr_child_count(body); _t3000 = *_hp; free(_hp); }
            (void)_t3000;
            U64 _t3001 = 0;
            (void)_t3001;
            U64 _t3002 = I64_to_u64(_t3000);
            (void)_t3002;
            ;
            Range *_t3003 = Range_new(_t3001, _t3002);
            (void)_t3003;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t3003, _fi2989); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t3003, &(Bool){1});
            U64 _t3004 = 1;
            (void)_t3004;
            U64 _t3005 = U64_add(_fi2989, _t3004);
            (void)_t3005;
            ;
            _fi2989 = _t3005;
            ;
            I64 *_t3006 = malloc(sizeof(I64)); *_t3006 = U64_to_i64(i);
            (void)_t3006;
            ;
            Expr *f = Expr_child(body, _t3006);
            (void)f;
            Bool _t3007; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t3007 = *_hp; free(_hp); }
            (void)_t3007;
            if (_t3007) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t2994 = Bool_not(decl->is_namespace);
                (void)_t2994;
                if (_t2994) {
                    Bool _t2991; { Bool *_hp = (Bool *)Str_eq(&decl->name, variant_name); _t2991 = *_hp; free(_hp); }
                    (void)_t2991;
                    if (_t2991) {
                        ;
                        ;
                        Declaration_delete(decl, &(Bool){1});
                        I64_delete(_t3006, &(Bool){1});
                        ;
                        ;
                        { I32 *_r = malloc(sizeof(I32)); *_r = tag; return _r; }
                    }
                    ;
                    I32 _t2992 = 1;
                    (void)_t2992;
                    I32 _t2993 = I32_add(tag, _t2992);
                    (void)_t2993;
                    ;
                    tag = _t2993;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t3006, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t3008, &(Bool){1});
    ;
    I64 _t3009 = 0;
    (void)_t3009;
    I64 _t3010 = 1;
    (void)_t3010;
    I64 _t3011 = I64_sub(_t3009, _t3010);
    (void)_t3011;
    ;
    ;
    I32 _t3012 = I64_to_i32(_t3011);
    (void)_t3012;
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t3012; return _r; }
}

Str * enum_variant_type(Expr * enum_def, I32 tag) {
    (void)enum_def;
    (void)tag;
    I64 *_t3032 = malloc(sizeof(I64));
    *_t3032 = 0;
    (void)_t3032;
    Expr *body = Expr_child(enum_def, _t3032);
    (void)body;
    I32 idx = 0;
    (void)idx;
    {
        U64 _fi3013 = 0;
        (void)_fi3013;
        while (1) {
            I64 _t3019; { I64 *_hp = (I64 *)Expr_child_count(body); _t3019 = *_hp; free(_hp); }
            (void)_t3019;
            U64 _t3020 = 0;
            (void)_t3020;
            U64 _t3021 = I64_to_u64(_t3019);
            (void)_t3021;
            ;
            Range *_t3022 = Range_new(_t3020, _t3021);
            (void)_t3022;
            ;
            ;
            U64 _t3023; { U64 *_hp = (U64 *)Range_len(_t3022); _t3023 = *_hp; free(_hp); }
            (void)_t3023;
            Range_delete(_t3022, &(Bool){1});
            Bool _wcond3014; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3013}, &(U64){_t3023}); _wcond3014 = *_hp; free(_hp); }
            (void)_wcond3014;
            ;
            if (_wcond3014) {
            } else {
                ;
                break;
            }
            ;
            I64 _t3024; { I64 *_hp = (I64 *)Expr_child_count(body); _t3024 = *_hp; free(_hp); }
            (void)_t3024;
            U64 _t3025 = 0;
            (void)_t3025;
            U64 _t3026 = I64_to_u64(_t3024);
            (void)_t3026;
            ;
            Range *_t3027 = Range_new(_t3025, _t3026);
            (void)_t3027;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t3027, _fi3013); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t3027, &(Bool){1});
            U64 _t3028 = 1;
            (void)_t3028;
            U64 _t3029 = U64_add(_fi3013, _t3028);
            (void)_t3029;
            ;
            _fi3013 = _t3029;
            ;
            I64 *_t3030 = malloc(sizeof(I64)); *_t3030 = U64_to_i64(i);
            (void)_t3030;
            ;
            Expr *f = Expr_child(body, _t3030);
            (void)f;
            Bool _t3031; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t3031 = *_hp; free(_hp); }
            (void)_t3031;
            if (_t3031) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t3018 = Bool_not(decl->is_namespace);
                (void)_t3018;
                if (_t3018) {
                    Bool _t3015 = I32_eq(idx, tag);
                    (void)_t3015;
                    if (_t3015) {
                        ;
                        ;
                        I64_delete(_t3030, &(Bool){1});
                        ;
                        ;
                        { Str *_r = malloc(sizeof(Str)); *_r = decl->explicit_type; return _r; }
                    }
                    ;
                    I32 _t3016 = 1;
                    (void)_t3016;
                    I32 _t3017 = I32_add(idx, _t3016);
                    (void)_t3017;
                    ;
                    idx = _t3017;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t3030, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t3032, &(Bool){1});
    ;
    Str *_t3033 = Str_lit("", 0ULL);
    (void)_t3033;
    return _t3033;
}

