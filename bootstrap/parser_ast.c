#include "parser_ast.h"

Str * til_type_name_c(TilType * t) {
    (void)t;
    {
        TilType *_sw2276 = TilType_clone(t);
        (void)_sw2276;
        Bool _t2311; { Bool *_hp = (Bool *)TilType_eq(_sw2276, TilType_Unknown()); _t2311 = *_hp; free(_hp); }
        (void)_t2311;
        if (_t2311) {
            Str *_t2277 = Str_lit("unknown", 7ULL);
            (void)_t2277;
            TilType_delete(_sw2276, &(Bool){1});
            ;
            return _t2277;
        } else {
            Bool _t2310; { Bool *_hp = (Bool *)TilType_eq(_sw2276, TilType_None()); _t2310 = *_hp; free(_hp); }
            (void)_t2310;
            if (_t2310) {
                Str *_t2278 = Str_lit("None", 4ULL);
                (void)_t2278;
                ;
                TilType_delete(_sw2276, &(Bool){1});
                ;
                return _t2278;
            } else {
                Bool _t2309; { Bool *_hp = (Bool *)TilType_eq(_sw2276, TilType_I64()); _t2309 = *_hp; free(_hp); }
                (void)_t2309;
                if (_t2309) {
                    Str *_t2279 = Str_lit("I64", 3ULL);
                    (void)_t2279;
                    ;
                    ;
                    TilType_delete(_sw2276, &(Bool){1});
                    ;
                    return _t2279;
                } else {
                    Bool _t2308; { Bool *_hp = (Bool *)TilType_eq(_sw2276, TilType_U8()); _t2308 = *_hp; free(_hp); }
                    (void)_t2308;
                    if (_t2308) {
                        Str *_t2280 = Str_lit("U8", 2ULL);
                        (void)_t2280;
                        ;
                        ;
                        ;
                        TilType_delete(_sw2276, &(Bool){1});
                        ;
                        return _t2280;
                    } else {
                        Bool _t2307; { Bool *_hp = (Bool *)TilType_eq(_sw2276, TilType_I16()); _t2307 = *_hp; free(_hp); }
                        (void)_t2307;
                        if (_t2307) {
                            Str *_t2281 = Str_lit("I16", 3ULL);
                            (void)_t2281;
                            ;
                            ;
                            ;
                            ;
                            TilType_delete(_sw2276, &(Bool){1});
                            ;
                            return _t2281;
                        } else {
                            Bool _t2306; { Bool *_hp = (Bool *)TilType_eq(_sw2276, TilType_I32()); _t2306 = *_hp; free(_hp); }
                            (void)_t2306;
                            if (_t2306) {
                                Str *_t2282 = Str_lit("I32", 3ULL);
                                (void)_t2282;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TilType_delete(_sw2276, &(Bool){1});
                                ;
                                return _t2282;
                            } else {
                                Bool _t2305; { Bool *_hp = (Bool *)TilType_eq(_sw2276, TilType_U32()); _t2305 = *_hp; free(_hp); }
                                (void)_t2305;
                                if (_t2305) {
                                    Str *_t2283 = Str_lit("U32", 3ULL);
                                    (void)_t2283;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TilType_delete(_sw2276, &(Bool){1});
                                    ;
                                    return _t2283;
                                } else {
                                    Bool _t2304; { Bool *_hp = (Bool *)TilType_eq(_sw2276, TilType_U64()); _t2304 = *_hp; free(_hp); }
                                    (void)_t2304;
                                    if (_t2304) {
                                        Str *_t2284 = Str_lit("U64", 3ULL);
                                        (void)_t2284;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TilType_delete(_sw2276, &(Bool){1});
                                        ;
                                        return _t2284;
                                    } else {
                                        Bool _t2303; { Bool *_hp = (Bool *)TilType_eq(_sw2276, TilType_F32()); _t2303 = *_hp; free(_hp); }
                                        (void)_t2303;
                                        if (_t2303) {
                                            Str *_t2285 = Str_lit("F32", 3ULL);
                                            (void)_t2285;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TilType_delete(_sw2276, &(Bool){1});
                                            ;
                                            return _t2285;
                                        } else {
                                            Bool _t2302; { Bool *_hp = (Bool *)TilType_eq(_sw2276, TilType_Bool()); _t2302 = *_hp; free(_hp); }
                                            (void)_t2302;
                                            if (_t2302) {
                                                Str *_t2286 = Str_lit("Bool", 4ULL);
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
                                                TilType_delete(_sw2276, &(Bool){1});
                                                ;
                                                return _t2286;
                                            } else {
                                                Bool _t2301; { Bool *_hp = (Bool *)TilType_eq(_sw2276, TilType_Struct()); _t2301 = *_hp; free(_hp); }
                                                (void)_t2301;
                                                if (_t2301) {
                                                    Str *_t2287 = Str_lit("Struct", 6ULL);
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
                                                    TilType_delete(_sw2276, &(Bool){1});
                                                    ;
                                                    return _t2287;
                                                } else {
                                                    Bool _t2300; { Bool *_hp = (Bool *)TilType_eq(_sw2276, TilType_StructDef()); _t2300 = *_hp; free(_hp); }
                                                    (void)_t2300;
                                                    if (_t2300) {
                                                        Str *_t2288 = Str_lit("StructDef", 9ULL);
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
                                                        TilType_delete(_sw2276, &(Bool){1});
                                                        ;
                                                        return _t2288;
                                                    } else {
                                                        Bool _t2299; { Bool *_hp = (Bool *)TilType_eq(_sw2276, TilType_Enum()); _t2299 = *_hp; free(_hp); }
                                                        (void)_t2299;
                                                        if (_t2299) {
                                                            Str *_t2289 = Str_lit("Enum", 4ULL);
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
                                                            TilType_delete(_sw2276, &(Bool){1});
                                                            ;
                                                            return _t2289;
                                                        } else {
                                                            Bool _t2298; { Bool *_hp = (Bool *)TilType_eq(_sw2276, TilType_EnumDef()); _t2298 = *_hp; free(_hp); }
                                                            (void)_t2298;
                                                            if (_t2298) {
                                                                Str *_t2290 = Str_lit("EnumDef", 7ULL);
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
                                                                TilType_delete(_sw2276, &(Bool){1});
                                                                ;
                                                                return _t2290;
                                                            } else {
                                                                Bool _t2297; { Bool *_hp = (Bool *)TilType_eq(_sw2276, TilType_FuncDef()); _t2297 = *_hp; free(_hp); }
                                                                (void)_t2297;
                                                                if (_t2297) {
                                                                    Str *_t2291 = Str_lit("FunctionDef", 11ULL);
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
                                                                    TilType_delete(_sw2276, &(Bool){1});
                                                                    ;
                                                                    return _t2291;
                                                                } else {
                                                                    Bool _t2296; { Bool *_hp = (Bool *)TilType_eq(_sw2276, TilType_FuncPtr()); _t2296 = *_hp; free(_hp); }
                                                                    (void)_t2296;
                                                                    if (_t2296) {
                                                                        Str *_t2292 = Str_lit("Fn", 2ULL);
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
                                                                        TilType_delete(_sw2276, &(Bool){1});
                                                                        ;
                                                                        return _t2292;
                                                                    } else {
                                                                        Bool _t2295; { Bool *_hp = (Bool *)TilType_eq(_sw2276, TilType_Dynamic()); _t2295 = *_hp; free(_hp); }
                                                                        (void)_t2295;
                                                                        if (_t2295) {
                                                                            Str *_t2293 = Str_lit("Dynamic", 7ULL);
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
                                                                            TilType_delete(_sw2276, &(Bool){1});
                                                                            ;
                                                                            return _t2293;
                                                                        } else {
                                                                            Str *_t2294 = Str_lit("?", 1ULL);
                                                                            (void)_t2294;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TilType_delete(_sw2276, &(Bool){1});
                                                                            ;
                                                                            return _t2294;
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
        TilType_delete(_sw2276, &(Bool){1});
        ;
    }
}

Bool * Declaration_eq(Declaration * a, Declaration * b) {
    (void)a;
    (void)b;
    Bool _t2312; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t2312 = *_hp; free(_hp); }
    (void)_t2312;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2312; return _r; }
}

Str * Declaration_to_str(Declaration * self) {
    (void)self;
    { Str *_r = malloc(sizeof(Str)); *_r = self->name; return _r; }
}

Declaration * Declaration_clone(Declaration * self) {
    (void)self;
    Bool _t2313 = Bool_clone(&self->is_mut);
    (void)_t2313;
    Bool _t2314 = Bool_clone(&self->is_namespace);
    (void)_t2314;
    Bool _t2315 = Bool_clone(&self->is_ref);
    (void)_t2315;
    Bool _t2316 = Bool_clone(&self->is_own);
    (void)_t2316;
    I32 _t2317 = I32_clone(&self->field_offset);
    (void)_t2317;
    I32 _t2318 = I32_clone(&self->field_size);
    (void)_t2318;
    Declaration *_t2319 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); _t2319->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); _t2319->explicit_type = *_ca; free(_ca); }
    _t2319->is_mut = _t2313;
    _t2319->is_namespace = _t2314;
    _t2319->is_ref = _t2315;
    _t2319->is_own = _t2316;
    _t2319->field_offset = _t2317;
    _t2319->field_size = _t2318;
    _t2319->field_struct_def = self->field_struct_def;
    _t2319->fn_sig = self->fn_sig;
    (void)_t2319;
    ;
    ;
    ;
    ;
    ;
    ;
    return _t2319;
}

U64 *Declaration_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Declaration);
    return r;
}

void Expr_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Str *_t2643 = Str_lit("Str", 3ULL);
    (void)_t2643;
    U64 _t2644; { U64 *_hp = (U64 *)Str_size(); _t2644 = *_hp; free(_hp); }
    (void)_t2644;
    U64 _t2645 = 7;
    (void)_t2645;
    Array *_va35 = Array_new(_t2643, &(U64){_t2644}, &(U64){_t2645});
    (void)_va35;
    Str_delete(_t2643, &(Bool){1});
    ;
    ;
    U64 _t2646 = 0;
    (void)_t2646;
    Str *_t2647 = Str_clone(&self->path);
    (void)_t2647;
    Array_set(_va35, &(U64){_t2646}, _t2647);
    ;
    U64 _t2648 = 1;
    (void)_t2648;
    Str *_t2649 = Str_lit(":", 1ULL);
    (void)_t2649;
    Array_set(_va35, &(U64){_t2648}, _t2649);
    ;
    U64 _t2650 = 2;
    (void)_t2650;
    Str *_t2651 = U32_to_str(&self->line);
    (void)_t2651;
    Array_set(_va35, &(U64){_t2650}, _t2651);
    ;
    U64 _t2652 = 3;
    (void)_t2652;
    Str *_t2653 = Str_lit(":", 1ULL);
    (void)_t2653;
    Array_set(_va35, &(U64){_t2652}, _t2653);
    ;
    U64 _t2654 = 4;
    (void)_t2654;
    Str *_t2655 = U32_to_str(&self->col);
    (void)_t2655;
    Array_set(_va35, &(U64){_t2654}, _t2655);
    ;
    U64 _t2656 = 5;
    (void)_t2656;
    Str *_t2657 = Str_lit(": error: ", 9ULL);
    (void)_t2657;
    Array_set(_va35, &(U64){_t2656}, _t2657);
    ;
    U64 _t2658 = 6;
    (void)_t2658;
    Str *_t2659 = Str_clone(msg);
    (void)_t2659;
    Array_set(_va35, &(U64){_t2658}, _t2659);
    ;
    println(_va35);
}

void Expr_todo_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Expr_error(self, msg);
    Str *_t2660 = Str_lit("Str", 3ULL);
    (void)_t2660;
    U64 _t2661; { U64 *_hp = (U64 *)Str_size(); _t2661 = *_hp; free(_hp); }
    (void)_t2661;
    U64 _t2662 = 1;
    (void)_t2662;
    Array *_va36 = Array_new(_t2660, &(U64){_t2661}, &(U64){_t2662});
    (void)_va36;
    Str_delete(_t2660, &(Bool){1});
    ;
    ;
    U64 _t2663 = 0;
    (void)_t2663;
    Str *_t2664 = Str_lit("  note: this language feature is not implemented yet", 52ULL);
    (void)_t2664;
    Array_set(_va36, &(U64){_t2663}, _t2664);
    ;
    println(_va36);
}

void Expr_lang_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Expr_error(self, msg);
    Str *_t2665 = Str_lit("Str", 3ULL);
    (void)_t2665;
    U64 _t2666; { U64 *_hp = (U64 *)Str_size(); _t2666 = *_hp; free(_hp); }
    (void)_t2666;
    U64 _t2667 = 1;
    (void)_t2667;
    Array *_va37 = Array_new(_t2665, &(U64){_t2666}, &(U64){_t2667});
    (void)_va37;
    Str_delete(_t2665, &(Bool){1});
    ;
    ;
    U64 _t2668 = 0;
    (void)_t2668;
    Str *_t2669 = Str_lit("  note: this is a bug in the language, please report it", 55ULL);
    (void)_t2669;
    Array_set(_va37, &(U64){_t2668}, _t2669);
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
    U64 *_t2670 = malloc(sizeof(U64)); *_t2670 = I64_to_u64(DEREF(i));
    (void)_t2670;
    Expr *c = Vec_get(&parent->children, _t2670);
    (void)c;
    U64_delete(_t2670, &(Bool){1});
    return c;
}

I64 * Expr_child_count(Expr * parent) {
    (void)parent;
    U64 _t2671; { U64 *_hp = (U64 *)Vec_len(&parent->children); _t2671 = *_hp; free(_hp); }
    (void)_t2671;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t2671; return _r; }
}

Expr * Expr_new(ExprData * data, U32 line, U32 col, Str * path) {
    (void)data;
    (void)line;
    (void)col;
    (void)path;
    I64 _t2672 = 0;
    (void)_t2672;
    I64 _t2673 = 1;
    (void)_t2673;
    I64 _t2674 = I64_sub(_t2672, _t2673);
    (void)_t2674;
    ;
    ;
    I64 _t2675 = 0;
    (void)_t2675;
    I64 _t2676 = 1;
    (void)_t2676;
    I64 _t2677 = I64_sub(_t2675, _t2676);
    (void)_t2677;
    ;
    ;
    Str *_t2678 = Str_lit("", 0ULL);
    (void)_t2678;
    U64 _t2679; { U64 *_hp = (U64 *)Expr_size(); _t2679 = *_hp; free(_hp); }
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
    Bool _t2687 = 0;
    (void)_t2687;
    I32 _t2688 = 0;
    (void)_t2688;
    I32 _t2689 = I64_to_i32(_t2674);
    (void)_t2689;
    ;
    U32 _t2690 = 0;
    (void)_t2690;
    I32 _t2691 = I64_to_i32(_t2677);
    (void)_t2691;
    ;
    U32 _t2692 = 0;
    (void)_t2692;
    U32 _t2693 = U32_clone(&(U32){col});
    (void)_t2693;
    Str *_t2694 = Str_clone(path);
    (void)_t2694;
    Expr *_t2695 = malloc(sizeof(Expr));
    { ExprData *_ca = ExprData_clone(data); _t2695->data = *_ca; free(_ca); }
    { TilType *_ca = TilType_clone(TilType_Unknown()); _t2695->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t2695->struct_name = *_ca; free(_ca); }
    _t2695->is_own_arg = _t2680;
    _t2695->is_splat = _t2681;
    _t2695->is_own_field = _t2682;
    _t2695->is_ref_field = _t2683;
    _t2695->is_ns_field = _t2684;
    _t2695->is_ext = _t2685;
    _t2695->is_core = _t2686;
    _t2695->save_old_delete = _t2687;
    _t2695->total_struct_size = _t2688;
    _t2695->variadic_index = _t2689;
    _t2695->variadic_count = _t2690;
    _t2695->kwargs_index = _t2691;
    _t2695->kwargs_count = _t2692;
    _t2695->fn_sig = NULL;
    { Vec *_ca = Vec_new(_t2678, &(U64){_t2679}); _t2695->children = *_ca; free(_ca); }
    _t2695->line = U32_clone(&(U32){line});
    _t2695->col = _t2693;
    { Str *_ca = Str_clone(_t2694); _t2695->path = *_ca; free(_ca); }
    (void)_t2695;
    Str_delete(_t2678, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    Str_delete(_t2694, &(Bool){1});
    return _t2695;
}

Expr * Expr_clone(Expr * self) {
    (void)self;
    Str *_t2707 = Str_lit("", 0ULL);
    (void)_t2707;
    U64 _t2708; { U64 *_hp = (U64 *)Expr_size(); _t2708 = *_hp; free(_hp); }
    (void)_t2708;
    Vec *new_children = Vec_new(_t2707, &(U64){_t2708});
    (void)new_children;
    Str_delete(_t2707, &(Bool){1});
    ;
    {
        U64 _fi2696 = 0;
        (void)_fi2696;
        while (1) {
            U64 _t2698 = 0;
            (void)_t2698;
            U64 _t2699; { U64 *_hp = (U64 *)Vec_len(&self->children); _t2699 = *_hp; free(_hp); }
            (void)_t2699;
            Range *_t2700 = Range_new(_t2698, _t2699);
            (void)_t2700;
            ;
            ;
            U64 _t2701; { U64 *_hp = (U64 *)Range_len(_t2700); _t2701 = *_hp; free(_hp); }
            (void)_t2701;
            Range_delete(_t2700, &(Bool){1});
            Bool _wcond2697; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2696}, &(U64){_t2701}); _wcond2697 = *_hp; free(_hp); }
            (void)_wcond2697;
            ;
            if (_wcond2697) {
            } else {
                ;
                break;
            }
            ;
            U64 _t2702 = 0;
            (void)_t2702;
            U64 _t2703; { U64 *_hp = (U64 *)Vec_len(&self->children); _t2703 = *_hp; free(_hp); }
            (void)_t2703;
            Range *_t2704 = Range_new(_t2702, _t2703);
            (void)_t2704;
            ;
            ;
            U64 *i = Range_get(_t2704, _fi2696);
            (void)i;
            Range_delete(_t2704, &(Bool){1});
            U64 _t2705 = 1;
            (void)_t2705;
            U64 _t2706 = U64_add(_fi2696, _t2705);
            (void)_t2706;
            ;
            _fi2696 = _t2706;
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
    Expr *_t2709 = malloc(sizeof(Expr));
    { ExprData *_ca = ExprData_clone(&self->data); _t2709->data = *_ca; free(_ca); }
    { TilType *_ca = TilType_clone(&self->til_type); _t2709->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->struct_name); _t2709->struct_name = *_ca; free(_ca); }
    _t2709->is_own_arg = self->is_own_arg;
    _t2709->is_splat = self->is_splat;
    _t2709->is_own_field = self->is_own_field;
    _t2709->is_ref_field = self->is_ref_field;
    _t2709->is_ns_field = self->is_ns_field;
    _t2709->is_ext = self->is_ext;
    _t2709->is_core = self->is_core;
    _t2709->save_old_delete = self->save_old_delete;
    _t2709->total_struct_size = self->total_struct_size;
    _t2709->variadic_index = self->variadic_index;
    _t2709->variadic_count = self->variadic_count;
    _t2709->kwargs_index = self->kwargs_index;
    _t2709->kwargs_count = self->kwargs_count;
    _t2709->fn_sig = self->fn_sig;
    { Vec *_ca = Vec_clone(new_children); _t2709->children = *_ca; free(_ca); }
    _t2709->line = self->line;
    _t2709->col = self->col;
    { Str *_ca = Str_clone(&self->path); _t2709->path = *_ca; free(_ca); }
    (void)_t2709;
    Vec_delete(new_children, &(Bool){1});
    return _t2709;
}

U64 *Expr_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Expr);
    return r;
}

Str * node_name(ExprData * data) {
    (void)data;
    {
        ExprData *_sw2731 = ExprData_clone(data);
        (void)_sw2731;
        Bool _t2782; { Bool *_hp = (Bool *)ExprData_eq(_sw2731, ExprData_Body()); _t2782 = *_hp; free(_hp); }
        (void)_t2782;
        if (_t2782) {
            Str *_t2732 = Str_lit("body", 4ULL);
            (void)_t2732;
            ExprData_delete(_sw2731, &(Bool){1});
            ;
            return _t2732;
        } else {
            Bool _t2781; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw2731); _t2781 = *_hp; free(_hp); }
            (void)_t2781;
            if (_t2781) {
                Str *_t2733 = Str_lit("str", 3ULL);
                (void)_t2733;
                ;
                ExprData_delete(_sw2731, &(Bool){1});
                ;
                return _t2733;
            } else {
                Bool _t2780; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw2731); _t2780 = *_hp; free(_hp); }
                (void)_t2780;
                if (_t2780) {
                    Str *_t2734 = Str_lit("num", 3ULL);
                    (void)_t2734;
                    ;
                    ;
                    ExprData_delete(_sw2731, &(Bool){1});
                    ;
                    return _t2734;
                } else {
                    Bool _t2779; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw2731); _t2779 = *_hp; free(_hp); }
                    (void)_t2779;
                    if (_t2779) {
                        Str *_t2735 = Str_lit("bool", 4ULL);
                        (void)_t2735;
                        ;
                        ;
                        ;
                        ExprData_delete(_sw2731, &(Bool){1});
                        ;
                        return _t2735;
                    } else {
                        Bool _t2778; { Bool *_hp = (Bool *)ExprData_eq(_sw2731, ExprData_LiteralNull()); _t2778 = *_hp; free(_hp); }
                        (void)_t2778;
                        if (_t2778) {
                            Str *_t2736 = Str_lit("null", 4ULL);
                            (void)_t2736;
                            ;
                            ;
                            ;
                            ;
                            ExprData_delete(_sw2731, &(Bool){1});
                            ;
                            return _t2736;
                        } else {
                            Bool _t2777; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw2731); _t2777 = *_hp; free(_hp); }
                            (void)_t2777;
                            if (_t2777) {
                                Str *_t2737 = Str_lit("ident", 5ULL);
                                (void)_t2737;
                                ;
                                ;
                                ;
                                ;
                                ;
                                ExprData_delete(_sw2731, &(Bool){1});
                                ;
                                return _t2737;
                            } else {
                                Bool _t2776; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw2731); _t2776 = *_hp; free(_hp); }
                                (void)_t2776;
                                if (_t2776) {
                                    Str *_t2738 = Str_lit("decl", 4ULL);
                                    (void)_t2738;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ExprData_delete(_sw2731, &(Bool){1});
                                    ;
                                    return _t2738;
                                } else {
                                    Bool _t2775; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw2731); _t2775 = *_hp; free(_hp); }
                                    (void)_t2775;
                                    if (_t2775) {
                                        Str *_t2739 = Str_lit("assign", 6ULL);
                                        (void)_t2739;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ExprData_delete(_sw2731, &(Bool){1});
                                        ;
                                        return _t2739;
                                    } else {
                                        Bool _t2774; { Bool *_hp = (Bool *)ExprData_eq(_sw2731, ExprData_FCall()); _t2774 = *_hp; free(_hp); }
                                        (void)_t2774;
                                        if (_t2774) {
                                            Str *_t2740 = Str_lit("fcall", 5ULL);
                                            (void)_t2740;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ExprData_delete(_sw2731, &(Bool){1});
                                            ;
                                            return _t2740;
                                        } else {
                                            Bool _t2773; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw2731); _t2773 = *_hp; free(_hp); }
                                            (void)_t2773;
                                            if (_t2773) {
                                                Str *_t2741 = Str_lit("func_def", 8ULL);
                                                (void)_t2741;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ExprData_delete(_sw2731, &(Bool){1});
                                                ;
                                                return _t2741;
                                            } else {
                                                Bool _t2772; { Bool *_hp = (Bool *)ExprData_eq(_sw2731, ExprData_StructDef()); _t2772 = *_hp; free(_hp); }
                                                (void)_t2772;
                                                if (_t2772) {
                                                    Str *_t2742 = Str_lit("struct_def", 10ULL);
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
                                                    ;
                                                    ExprData_delete(_sw2731, &(Bool){1});
                                                    ;
                                                    return _t2742;
                                                } else {
                                                    Bool _t2771; { Bool *_hp = (Bool *)ExprData_eq(_sw2731, ExprData_EnumDef()); _t2771 = *_hp; free(_hp); }
                                                    (void)_t2771;
                                                    if (_t2771) {
                                                        Str *_t2743 = Str_lit("enum_def", 8ULL);
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
                                                        ;
                                                        ExprData_delete(_sw2731, &(Bool){1});
                                                        ;
                                                        return _t2743;
                                                    } else {
                                                        Bool _t2770; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(_sw2731); _t2770 = *_hp; free(_hp); }
                                                        (void)_t2770;
                                                        if (_t2770) {
                                                            Str *_t2744 = Str_lit("field_access", 12ULL);
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
                                                            ;
                                                            ExprData_delete(_sw2731, &(Bool){1});
                                                            ;
                                                            return _t2744;
                                                        } else {
                                                            Bool _t2769; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(_sw2731); _t2769 = *_hp; free(_hp); }
                                                            (void)_t2769;
                                                            if (_t2769) {
                                                                Str *_t2745 = Str_lit("field_assign", 12ULL);
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
                                                                ;
                                                                ExprData_delete(_sw2731, &(Bool){1});
                                                                ;
                                                                return _t2745;
                                                            } else {
                                                                Bool _t2768; { Bool *_hp = (Bool *)ExprData_eq(_sw2731, ExprData_Return()); _t2768 = *_hp; free(_hp); }
                                                                (void)_t2768;
                                                                if (_t2768) {
                                                                    Str *_t2746 = Str_lit("return", 6ULL);
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
                                                                    ;
                                                                    ExprData_delete(_sw2731, &(Bool){1});
                                                                    ;
                                                                    return _t2746;
                                                                } else {
                                                                    Bool _t2767; { Bool *_hp = (Bool *)ExprData_eq(_sw2731, ExprData_If()); _t2767 = *_hp; free(_hp); }
                                                                    (void)_t2767;
                                                                    if (_t2767) {
                                                                        Str *_t2747 = Str_lit("if", 2ULL);
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
                                                                        ;
                                                                        ExprData_delete(_sw2731, &(Bool){1});
                                                                        ;
                                                                        return _t2747;
                                                                    } else {
                                                                        Bool _t2766; { Bool *_hp = (Bool *)ExprData_eq(_sw2731, ExprData_While()); _t2766 = *_hp; free(_hp); }
                                                                        (void)_t2766;
                                                                        if (_t2766) {
                                                                            Str *_t2748 = Str_lit("while", 5ULL);
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
                                                                            ;
                                                                            ExprData_delete(_sw2731, &(Bool){1});
                                                                            ;
                                                                            return _t2748;
                                                                        } else {
                                                                            Bool _t2765; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw2731); _t2765 = *_hp; free(_hp); }
                                                                            (void)_t2765;
                                                                            if (_t2765) {
                                                                                Str *_t2749 = Str_lit("for_in", 6ULL);
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
                                                                                ;
                                                                                ExprData_delete(_sw2731, &(Bool){1});
                                                                                ;
                                                                                return _t2749;
                                                                            } else {
                                                                                Bool _t2764; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw2731); _t2764 = *_hp; free(_hp); }
                                                                                (void)_t2764;
                                                                                if (_t2764) {
                                                                                    Str *_t2750 = Str_lit("named_arg", 9ULL);
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
                                                                                    ;
                                                                                    ExprData_delete(_sw2731, &(Bool){1});
                                                                                    ;
                                                                                    return _t2750;
                                                                                } else {
                                                                                    Bool _t2763; { Bool *_hp = (Bool *)ExprData_eq(_sw2731, ExprData_Break()); _t2763 = *_hp; free(_hp); }
                                                                                    (void)_t2763;
                                                                                    if (_t2763) {
                                                                                        Str *_t2751 = Str_lit("break", 5ULL);
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
                                                                                        ;
                                                                                        ExprData_delete(_sw2731, &(Bool){1});
                                                                                        ;
                                                                                        return _t2751;
                                                                                    } else {
                                                                                        Bool _t2762; { Bool *_hp = (Bool *)ExprData_eq(_sw2731, ExprData_Continue()); _t2762 = *_hp; free(_hp); }
                                                                                        (void)_t2762;
                                                                                        if (_t2762) {
                                                                                            Str *_t2752 = Str_lit("continue", 8ULL);
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
                                                                                            ;
                                                                                            ExprData_delete(_sw2731, &(Bool){1});
                                                                                            ;
                                                                                            return _t2752;
                                                                                        } else {
                                                                                            Bool _t2761; { Bool *_hp = (Bool *)ExprData_eq(_sw2731, ExprData_MapLit()); _t2761 = *_hp; free(_hp); }
                                                                                            (void)_t2761;
                                                                                            if (_t2761) {
                                                                                                Str *_t2753 = Str_lit("map_lit", 7ULL);
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
                                                                                                ;
                                                                                                ExprData_delete(_sw2731, &(Bool){1});
                                                                                                ;
                                                                                                return _t2753;
                                                                                            } else {
                                                                                                Bool _t2760; { Bool *_hp = (Bool *)ExprData_eq(_sw2731, ExprData_SetLit()); _t2760 = *_hp; free(_hp); }
                                                                                                (void)_t2760;
                                                                                                if (_t2760) {
                                                                                                    Str *_t2754 = Str_lit("set_lit", 7ULL);
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
                                                                                                    ;
                                                                                                    ExprData_delete(_sw2731, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t2754;
                                                                                                } else {
                                                                                                    Bool _t2759; { Bool *_hp = (Bool *)ExprData_eq(_sw2731, ExprData_Switch()); _t2759 = *_hp; free(_hp); }
                                                                                                    (void)_t2759;
                                                                                                    if (_t2759) {
                                                                                                        Str *_t2755 = Str_lit("switch", 6ULL);
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
                                                                                                        ;
                                                                                                        ExprData_delete(_sw2731, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t2755;
                                                                                                    } else {
                                                                                                        Bool _t2758; { Bool *_hp = (Bool *)ExprData_eq(_sw2731, ExprData_Case()); _t2758 = *_hp; free(_hp); }
                                                                                                        (void)_t2758;
                                                                                                        if (_t2758) {
                                                                                                            Str *_t2756 = Str_lit("case", 4ULL);
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
                                                                                                            ;
                                                                                                            ExprData_delete(_sw2731, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t2756;
                                                                                                        } else {
                                                                                                            Str *_t2757 = Str_lit("?", 1ULL);
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
                                                                                                            ExprData_delete(_sw2731, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t2757;
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
        ExprData_delete(_sw2731, &(Bool){1});
        ;
    }
}

Str * func_type_name(FuncType * ft) {
    (void)ft;
    {
        FuncType *_sw2783 = FuncType_clone(ft);
        (void)_sw2783;
        Bool _t2796; { Bool *_hp = (Bool *)FuncType_eq(_sw2783, FuncType_Func()); _t2796 = *_hp; free(_hp); }
        (void)_t2796;
        if (_t2796) {
            Str *_t2784 = Str_lit("func", 4ULL);
            (void)_t2784;
            FuncType_delete(_sw2783, &(Bool){1});
            ;
            return _t2784;
        } else {
            Bool _t2795; { Bool *_hp = (Bool *)FuncType_eq(_sw2783, FuncType_Proc()); _t2795 = *_hp; free(_hp); }
            (void)_t2795;
            if (_t2795) {
                Str *_t2785 = Str_lit("proc", 4ULL);
                (void)_t2785;
                ;
                FuncType_delete(_sw2783, &(Bool){1});
                ;
                return _t2785;
            } else {
                Bool _t2794; { Bool *_hp = (Bool *)FuncType_eq(_sw2783, FuncType_Test()); _t2794 = *_hp; free(_hp); }
                (void)_t2794;
                if (_t2794) {
                    Str *_t2786 = Str_lit("test", 4ULL);
                    (void)_t2786;
                    ;
                    ;
                    FuncType_delete(_sw2783, &(Bool){1});
                    ;
                    return _t2786;
                } else {
                    Bool _t2793; { Bool *_hp = (Bool *)FuncType_eq(_sw2783, FuncType_Macro()); _t2793 = *_hp; free(_hp); }
                    (void)_t2793;
                    if (_t2793) {
                        Str *_t2787 = Str_lit("macro", 5ULL);
                        (void)_t2787;
                        ;
                        ;
                        ;
                        FuncType_delete(_sw2783, &(Bool){1});
                        ;
                        return _t2787;
                    } else {
                        Bool _t2792; { Bool *_hp = (Bool *)FuncType_eq(_sw2783, FuncType_ExtFunc()); _t2792 = *_hp; free(_hp); }
                        (void)_t2792;
                        if (_t2792) {
                            Str *_t2788 = Str_lit("ext_func", 8ULL);
                            (void)_t2788;
                            ;
                            ;
                            ;
                            ;
                            FuncType_delete(_sw2783, &(Bool){1});
                            ;
                            return _t2788;
                        } else {
                            Bool _t2791; { Bool *_hp = (Bool *)FuncType_eq(_sw2783, FuncType_ExtProc()); _t2791 = *_hp; free(_hp); }
                            (void)_t2791;
                            if (_t2791) {
                                Str *_t2789 = Str_lit("ext_proc", 8ULL);
                                (void)_t2789;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw2783, &(Bool){1});
                                ;
                                return _t2789;
                            } else {
                                Str *_t2790 = Str_lit("?", 1ULL);
                                (void)_t2790;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw2783, &(Bool){1});
                                ;
                                return _t2790;
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
        FuncType_delete(_sw2783, &(Bool){1});
        ;
    }
}

void ast_print(Expr * e, U32 indent) {
    (void)e;
    (void)indent;
    {
        U64 _fi2797 = 0;
        (void)_fi2797;
        while (1) {
            I64 _t2799 = U32_to_i64(indent);
            (void)_t2799;
            U64 _t2800 = 0;
            (void)_t2800;
            U64 _t2801 = I64_to_u64(_t2799);
            (void)_t2801;
            ;
            Range *_t2802 = Range_new(_t2800, _t2801);
            (void)_t2802;
            ;
            ;
            U64 _t2803; { U64 *_hp = (U64 *)Range_len(_t2802); _t2803 = *_hp; free(_hp); }
            (void)_t2803;
            Range_delete(_t2802, &(Bool){1});
            Bool _wcond2798; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2797}, &(U64){_t2803}); _wcond2798 = *_hp; free(_hp); }
            (void)_wcond2798;
            ;
            if (_wcond2798) {
            } else {
                ;
                break;
            }
            ;
            I64 _t2804 = U32_to_i64(indent);
            (void)_t2804;
            U64 _t2805 = 0;
            (void)_t2805;
            U64 _t2806 = I64_to_u64(_t2804);
            (void)_t2806;
            ;
            Range *_t2807 = Range_new(_t2805, _t2806);
            (void)_t2807;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t2807, _fi2797); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t2807, &(Bool){1});
            ;
            U64 _t2808 = 1;
            (void)_t2808;
            U64 _t2809 = U64_add(_fi2797, _t2808);
            (void)_t2809;
            ;
            _fi2797 = _t2809;
            ;
            Str *_t2810 = Str_lit("Str", 3ULL);
            (void)_t2810;
            U64 _t2811; { U64 *_hp = (U64 *)Str_size(); _t2811 = *_hp; free(_hp); }
            (void)_t2811;
            U64 _t2812 = 1;
            (void)_t2812;
            Array *_va38 = Array_new(_t2810, &(U64){_t2811}, &(U64){_t2812});
            (void)_va38;
            Str_delete(_t2810, &(Bool){1});
            ;
            ;
            U64 _t2813 = 0;
            (void)_t2813;
            Str *_t2814 = Str_lit("  ", 2ULL);
            (void)_t2814;
            Array_set(_va38, &(U64){_t2813}, _t2814);
            ;
            print(_va38);
        }
        ;
    }
    Str *_t2948 = Str_lit("Str", 3ULL);
    (void)_t2948;
    U64 _t2949; { U64 *_hp = (U64 *)Str_size(); _t2949 = *_hp; free(_hp); }
    (void)_t2949;
    U64 _t2950 = 2;
    (void)_t2950;
    Array *_va52 = Array_new(_t2948, &(U64){_t2949}, &(U64){_t2950});
    (void)_va52;
    Str_delete(_t2948, &(Bool){1});
    ;
    ;
    U64 _t2951 = 0;
    (void)_t2951;
    Str *_t2952 = Str_lit("(", 1ULL);
    (void)_t2952;
    Array_set(_va52, &(U64){_t2951}, _t2952);
    ;
    U64 _t2953 = 1;
    (void)_t2953;
    Str *_t2954 = node_name(&e->data);
    (void)_t2954;
    Array_set(_va52, &(U64){_t2953}, _t2954);
    ;
    print(_va52);
    Bool _t2955; { Bool *_hp = (Bool *)TilType_eq(&e->til_type, TilType_Unknown()); _t2955 = *_hp; free(_hp); }
    (void)_t2955;
    Bool _t2956 = Bool_not(_t2955);
    (void)_t2956;
    ;
    if (_t2956) {
        Str *_t2815 = Str_lit("Str", 3ULL);
        (void)_t2815;
        U64 _t2816; { U64 *_hp = (U64 *)Str_size(); _t2816 = *_hp; free(_hp); }
        (void)_t2816;
        U64 _t2817 = 2;
        (void)_t2817;
        Array *_va39 = Array_new(_t2815, &(U64){_t2816}, &(U64){_t2817});
        (void)_va39;
        Str_delete(_t2815, &(Bool){1});
        ;
        ;
        U64 _t2818 = 0;
        (void)_t2818;
        Str *_t2819 = Str_lit(":", 1ULL);
        (void)_t2819;
        Array_set(_va39, &(U64){_t2818}, _t2819);
        ;
        U64 _t2820 = 1;
        (void)_t2820;
        Str *_t2821 = til_type_name_c(&e->til_type);
        (void)_t2821;
        Array_set(_va39, &(U64){_t2820}, _t2821);
        ;
        print(_va39);
    }
    ;
    {
        ExprData *_sw2822 = ExprData_clone(&e->data);
        (void)_sw2822;
        Bool _t2909; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw2822); _t2909 = *_hp; free(_hp); }
        (void)_t2909;
        if (_t2909) {
            Str *s = ExprData_get_Ident(_sw2822);
            (void)s;
            Str *_t2823 = Str_lit("Str", 3ULL);
            (void)_t2823;
            U64 _t2824; { U64 *_hp = (U64 *)Str_size(); _t2824 = *_hp; free(_hp); }
            (void)_t2824;
            U64 _t2825 = 3;
            (void)_t2825;
            Array *_va40 = Array_new(_t2823, &(U64){_t2824}, &(U64){_t2825});
            (void)_va40;
            Str_delete(_t2823, &(Bool){1});
            ;
            ;
            U64 _t2826 = 0;
            (void)_t2826;
            Str *_t2827 = Str_lit(" \"", 3ULL);
            (void)_t2827;
            Array_set(_va40, &(U64){_t2826}, _t2827);
            ;
            U64 _t2828 = 1;
            (void)_t2828;
            Str *_t2829 = Str_clone(s);
            (void)_t2829;
            Str_delete(s, &(Bool){1});
            Array_set(_va40, &(U64){_t2828}, _t2829);
            ;
            U64 _t2830 = 2;
            (void)_t2830;
            Str *_t2831 = Str_lit("\"", 2ULL);
            (void)_t2831;
            Array_set(_va40, &(U64){_t2830}, _t2831);
            ;
            print(_va40);
        } else {
            Bool _t2908; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw2822); _t2908 = *_hp; free(_hp); }
            (void)_t2908;
            if (_t2908) {
                Str *s = ExprData_get_LiteralStr(_sw2822);
                (void)s;
                Str *_t2832 = Str_lit("Str", 3ULL);
                (void)_t2832;
                U64 _t2833; { U64 *_hp = (U64 *)Str_size(); _t2833 = *_hp; free(_hp); }
                (void)_t2833;
                U64 _t2834 = 3;
                (void)_t2834;
                Array *_va41 = Array_new(_t2832, &(U64){_t2833}, &(U64){_t2834});
                (void)_va41;
                Str_delete(_t2832, &(Bool){1});
                ;
                ;
                U64 _t2835 = 0;
                (void)_t2835;
                Str *_t2836 = Str_lit(" \"", 3ULL);
                (void)_t2836;
                Array_set(_va41, &(U64){_t2835}, _t2836);
                ;
                U64 _t2837 = 1;
                (void)_t2837;
                Str *_t2838 = Str_clone(s);
                (void)_t2838;
                Str_delete(s, &(Bool){1});
                Array_set(_va41, &(U64){_t2837}, _t2838);
                ;
                U64 _t2839 = 2;
                (void)_t2839;
                Str *_t2840 = Str_lit("\"", 2ULL);
                (void)_t2840;
                Array_set(_va41, &(U64){_t2839}, _t2840);
                ;
                print(_va41);
            } else {
                Bool _t2907; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw2822); _t2907 = *_hp; free(_hp); }
                (void)_t2907;
                if (_t2907) {
                    Str *s = ExprData_get_LiteralNum(_sw2822);
                    (void)s;
                    Str *_t2841 = Str_lit("Str", 3ULL);
                    (void)_t2841;
                    U64 _t2842; { U64 *_hp = (U64 *)Str_size(); _t2842 = *_hp; free(_hp); }
                    (void)_t2842;
                    U64 _t2843 = 3;
                    (void)_t2843;
                    Array *_va42 = Array_new(_t2841, &(U64){_t2842}, &(U64){_t2843});
                    (void)_va42;
                    Str_delete(_t2841, &(Bool){1});
                    ;
                    ;
                    U64 _t2844 = 0;
                    (void)_t2844;
                    Str *_t2845 = Str_lit(" \"", 3ULL);
                    (void)_t2845;
                    Array_set(_va42, &(U64){_t2844}, _t2845);
                    ;
                    U64 _t2846 = 1;
                    (void)_t2846;
                    Str *_t2847 = Str_clone(s);
                    (void)_t2847;
                    Str_delete(s, &(Bool){1});
                    Array_set(_va42, &(U64){_t2846}, _t2847);
                    ;
                    U64 _t2848 = 2;
                    (void)_t2848;
                    Str *_t2849 = Str_lit("\"", 2ULL);
                    (void)_t2849;
                    Array_set(_va42, &(U64){_t2848}, _t2849);
                    ;
                    print(_va42);
                } else {
                    Bool _t2906; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw2822); _t2906 = *_hp; free(_hp); }
                    (void)_t2906;
                    if (_t2906) {
                        Str *s = ExprData_get_LiteralBool(_sw2822);
                        (void)s;
                        Str *_t2850 = Str_lit("Str", 3ULL);
                        (void)_t2850;
                        U64 _t2851; { U64 *_hp = (U64 *)Str_size(); _t2851 = *_hp; free(_hp); }
                        (void)_t2851;
                        U64 _t2852 = 3;
                        (void)_t2852;
                        Array *_va43 = Array_new(_t2850, &(U64){_t2851}, &(U64){_t2852});
                        (void)_va43;
                        Str_delete(_t2850, &(Bool){1});
                        ;
                        ;
                        U64 _t2853 = 0;
                        (void)_t2853;
                        Str *_t2854 = Str_lit(" \"", 3ULL);
                        (void)_t2854;
                        Array_set(_va43, &(U64){_t2853}, _t2854);
                        ;
                        U64 _t2855 = 1;
                        (void)_t2855;
                        Str *_t2856 = Str_clone(s);
                        (void)_t2856;
                        Str_delete(s, &(Bool){1});
                        Array_set(_va43, &(U64){_t2855}, _t2856);
                        ;
                        U64 _t2857 = 2;
                        (void)_t2857;
                        Str *_t2858 = Str_lit("\"", 2ULL);
                        (void)_t2858;
                        Array_set(_va43, &(U64){_t2857}, _t2858);
                        ;
                        print(_va43);
                    } else {
                        Bool _t2905; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw2822); _t2905 = *_hp; free(_hp); }
                        (void)_t2905;
                        if (_t2905) {
                            Str *s = ExprData_get_ForIn(_sw2822);
                            (void)s;
                            Str *_t2859 = Str_lit("Str", 3ULL);
                            (void)_t2859;
                            U64 _t2860; { U64 *_hp = (U64 *)Str_size(); _t2860 = *_hp; free(_hp); }
                            (void)_t2860;
                            U64 _t2861 = 3;
                            (void)_t2861;
                            Array *_va44 = Array_new(_t2859, &(U64){_t2860}, &(U64){_t2861});
                            (void)_va44;
                            Str_delete(_t2859, &(Bool){1});
                            ;
                            ;
                            U64 _t2862 = 0;
                            (void)_t2862;
                            Str *_t2863 = Str_lit(" \"", 3ULL);
                            (void)_t2863;
                            Array_set(_va44, &(U64){_t2862}, _t2863);
                            ;
                            U64 _t2864 = 1;
                            (void)_t2864;
                            Str *_t2865 = Str_clone(s);
                            (void)_t2865;
                            Str_delete(s, &(Bool){1});
                            Array_set(_va44, &(U64){_t2864}, _t2865);
                            ;
                            U64 _t2866 = 2;
                            (void)_t2866;
                            Str *_t2867 = Str_lit("\"", 2ULL);
                            (void)_t2867;
                            Array_set(_va44, &(U64){_t2866}, _t2867);
                            ;
                            print(_va44);
                        } else {
                            Bool _t2904; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw2822); _t2904 = *_hp; free(_hp); }
                            (void)_t2904;
                            if (_t2904) {
                                Declaration *decl = ExprData_get_Decl(_sw2822);
                                (void)decl;
                                if (decl->is_mut) {
                                    Str *_t2868 = Str_lit("Str", 3ULL);
                                    (void)_t2868;
                                    U64 _t2869; { U64 *_hp = (U64 *)Str_size(); _t2869 = *_hp; free(_hp); }
                                    (void)_t2869;
                                    U64 _t2870 = 1;
                                    (void)_t2870;
                                    Array *_va45 = Array_new(_t2868, &(U64){_t2869}, &(U64){_t2870});
                                    (void)_va45;
                                    Str_delete(_t2868, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t2871 = 0;
                                    (void)_t2871;
                                    Str *_t2872 = Str_lit(" mut", 4ULL);
                                    (void)_t2872;
                                    Array_set(_va45, &(U64){_t2871}, _t2872);
                                    ;
                                    print(_va45);
                                }
                                Str *_t2873 = Str_lit("Str", 3ULL);
                                (void)_t2873;
                                U64 _t2874; { U64 *_hp = (U64 *)Str_size(); _t2874 = *_hp; free(_hp); }
                                (void)_t2874;
                                U64 _t2875 = 2;
                                (void)_t2875;
                                Array *_va46 = Array_new(_t2873, &(U64){_t2874}, &(U64){_t2875});
                                (void)_va46;
                                Str_delete(_t2873, &(Bool){1});
                                ;
                                ;
                                U64 _t2876 = 0;
                                (void)_t2876;
                                Str *_t2877 = Str_lit(" ", 1ULL);
                                (void)_t2877;
                                Array_set(_va46, &(U64){_t2876}, _t2877);
                                ;
                                U64 _t2878 = 1;
                                (void)_t2878;
                                Str *_t2879 = Str_clone(&decl->name);
                                (void)_t2879;
                                Declaration_delete(decl, &(Bool){1});
                                Array_set(_va46, &(U64){_t2878}, _t2879);
                                ;
                                print(_va46);
                            } else {
                                Bool _t2903; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw2822); _t2903 = *_hp; free(_hp); }
                                (void)_t2903;
                                if (_t2903) {
                                    Str *s = ExprData_get_Assign(_sw2822);
                                    (void)s;
                                    Str *_t2880 = Str_lit("Str", 3ULL);
                                    (void)_t2880;
                                    U64 _t2881; { U64 *_hp = (U64 *)Str_size(); _t2881 = *_hp; free(_hp); }
                                    (void)_t2881;
                                    U64 _t2882 = 2;
                                    (void)_t2882;
                                    Array *_va47 = Array_new(_t2880, &(U64){_t2881}, &(U64){_t2882});
                                    (void)_va47;
                                    Str_delete(_t2880, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t2883 = 0;
                                    (void)_t2883;
                                    Str *_t2884 = Str_lit(" ", 1ULL);
                                    (void)_t2884;
                                    Array_set(_va47, &(U64){_t2883}, _t2884);
                                    ;
                                    U64 _t2885 = 1;
                                    (void)_t2885;
                                    Str *_t2886 = Str_clone(s);
                                    (void)_t2886;
                                    Str_delete(s, &(Bool){1});
                                    Array_set(_va47, &(U64){_t2885}, _t2886);
                                    ;
                                    print(_va47);
                                } else {
                                    Bool _t2902; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw2822); _t2902 = *_hp; free(_hp); }
                                    (void)_t2902;
                                    if (_t2902) {
                                        Str *s = ExprData_get_NamedArg(_sw2822);
                                        (void)s;
                                        Str *_t2887 = Str_lit("Str", 3ULL);
                                        (void)_t2887;
                                        U64 _t2888; { U64 *_hp = (U64 *)Str_size(); _t2888 = *_hp; free(_hp); }
                                        (void)_t2888;
                                        U64 _t2889 = 2;
                                        (void)_t2889;
                                        Array *_va48 = Array_new(_t2887, &(U64){_t2888}, &(U64){_t2889});
                                        (void)_va48;
                                        Str_delete(_t2887, &(Bool){1});
                                        ;
                                        ;
                                        U64 _t2890 = 0;
                                        (void)_t2890;
                                        Str *_t2891 = Str_lit(" ", 1ULL);
                                        (void)_t2891;
                                        Array_set(_va48, &(U64){_t2890}, _t2891);
                                        ;
                                        U64 _t2892 = 1;
                                        (void)_t2892;
                                        Str *_t2893 = Str_clone(s);
                                        (void)_t2893;
                                        Str_delete(s, &(Bool){1});
                                        Array_set(_va48, &(U64){_t2892}, _t2893);
                                        ;
                                        print(_va48);
                                    } else {
                                        Bool _t2901; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw2822); _t2901 = *_hp; free(_hp); }
                                        (void)_t2901;
                                        if (_t2901) {
                                            FunctionDef *fdef = ExprData_get_FuncDef(_sw2822);
                                            (void)fdef;
                                            Str *_t2894 = Str_lit("Str", 3ULL);
                                            (void)_t2894;
                                            U64 _t2895; { U64 *_hp = (U64 *)Str_size(); _t2895 = *_hp; free(_hp); }
                                            (void)_t2895;
                                            U64 _t2896 = 2;
                                            (void)_t2896;
                                            Array *_va49 = Array_new(_t2894, &(U64){_t2895}, &(U64){_t2896});
                                            (void)_va49;
                                            Str_delete(_t2894, &(Bool){1});
                                            ;
                                            ;
                                            U64 _t2897 = 0;
                                            (void)_t2897;
                                            Str *_t2898 = Str_lit(" ", 1ULL);
                                            (void)_t2898;
                                            Array_set(_va49, &(U64){_t2897}, _t2898);
                                            ;
                                            U64 _t2899 = 1;
                                            (void)_t2899;
                                            Str *_t2900 = func_type_name(&fdef->func_type);
                                            (void)_t2900;
                                            FunctionDef_delete(fdef, &(Bool){1});
                                            Array_set(_va49, &(U64){_t2899}, _t2900);
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
        ExprData_delete(_sw2822, &(Bool){1});
        ;
    }
    U64 _t2957; { U64 *_hp = (U64 *)Vec_len(&e->children); _t2957 = *_hp; free(_hp); }
    (void)_t2957;
    U64 _t2958 = 0;
    (void)_t2958;
    Bool _t2959; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2957}, &(U64){_t2958}); _t2959 = *_hp; free(_hp); }
    (void)_t2959;
    ;
    ;
    if (_t2959) {
        Str *_t2943 = Str_lit("Str", 3ULL);
        (void)_t2943;
        U64 _t2944; { U64 *_hp = (U64 *)Str_size(); _t2944 = *_hp; free(_hp); }
        (void)_t2944;
        U64 _t2945 = 1;
        (void)_t2945;
        Array *_va51 = Array_new(_t2943, &(U64){_t2944}, &(U64){_t2945});
        (void)_va51;
        Str_delete(_t2943, &(Bool){1});
        ;
        ;
        U64 _t2946 = 0;
        (void)_t2946;
        Str *_t2947 = Str_lit("", 0ULL);
        (void)_t2947;
        Array_set(_va51, &(U64){_t2946}, _t2947);
        ;
        println(_va51);
        {
            U64 _fi2910 = 0;
            (void)_fi2910;
            while (1) {
                U64 _t2912 = 0;
                (void)_t2912;
                U64 _t2913; { U64 *_hp = (U64 *)Vec_len(&e->children); _t2913 = *_hp; free(_hp); }
                (void)_t2913;
                Range *_t2914 = Range_new(_t2912, _t2913);
                (void)_t2914;
                ;
                ;
                U64 _t2915; { U64 *_hp = (U64 *)Range_len(_t2914); _t2915 = *_hp; free(_hp); }
                (void)_t2915;
                Range_delete(_t2914, &(Bool){1});
                Bool _wcond2911; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2910}, &(U64){_t2915}); _wcond2911 = *_hp; free(_hp); }
                (void)_wcond2911;
                ;
                if (_wcond2911) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t2916 = 0;
                (void)_t2916;
                U64 _t2917; { U64 *_hp = (U64 *)Vec_len(&e->children); _t2917 = *_hp; free(_hp); }
                (void)_t2917;
                Range *_t2918 = Range_new(_t2916, _t2917);
                (void)_t2918;
                ;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t2918, _fi2910); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t2918, &(Bool){1});
                U64 _t2919 = 1;
                (void)_t2919;
                U64 _t2920 = U64_add(_fi2910, _t2919);
                (void)_t2920;
                ;
                _fi2910 = _t2920;
                ;
                I64 *_t2921 = malloc(sizeof(I64)); *_t2921 = U64_to_i64(i);
                (void)_t2921;
                ;
                U32 _t2922 = 1;
                (void)_t2922;
                Expr *_t2923 = Expr_child(e, _t2921);
                (void)_t2923;
                U32 _t2924 = U32_add(indent, _t2922);
                (void)_t2924;
                ;
                ast_print(_t2923, _t2924);
                I64_delete(_t2921, &(Bool){1});
                ;
            }
            ;
        }
        {
            U64 _fi2925 = 0;
            (void)_fi2925;
            while (1) {
                I64 _t2927 = U32_to_i64(indent);
                (void)_t2927;
                U64 _t2928 = 0;
                (void)_t2928;
                U64 _t2929 = I64_to_u64(_t2927);
                (void)_t2929;
                ;
                Range *_t2930 = Range_new(_t2928, _t2929);
                (void)_t2930;
                ;
                ;
                U64 _t2931; { U64 *_hp = (U64 *)Range_len(_t2930); _t2931 = *_hp; free(_hp); }
                (void)_t2931;
                Range_delete(_t2930, &(Bool){1});
                Bool _wcond2926; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2925}, &(U64){_t2931}); _wcond2926 = *_hp; free(_hp); }
                (void)_wcond2926;
                ;
                if (_wcond2926) {
                } else {
                    ;
                    break;
                }
                ;
                I64 _t2932 = U32_to_i64(indent);
                (void)_t2932;
                U64 _t2933 = 0;
                (void)_t2933;
                U64 _t2934 = I64_to_u64(_t2932);
                (void)_t2934;
                ;
                Range *_t2935 = Range_new(_t2933, _t2934);
                (void)_t2935;
                ;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t2935, _fi2925); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t2935, &(Bool){1});
                ;
                U64 _t2936 = 1;
                (void)_t2936;
                U64 _t2937 = U64_add(_fi2925, _t2936);
                (void)_t2937;
                ;
                _fi2925 = _t2937;
                ;
                Str *_t2938 = Str_lit("Str", 3ULL);
                (void)_t2938;
                U64 _t2939; { U64 *_hp = (U64 *)Str_size(); _t2939 = *_hp; free(_hp); }
                (void)_t2939;
                U64 _t2940 = 1;
                (void)_t2940;
                Array *_va50 = Array_new(_t2938, &(U64){_t2939}, &(U64){_t2940});
                (void)_va50;
                Str_delete(_t2938, &(Bool){1});
                ;
                ;
                U64 _t2941 = 0;
                (void)_t2941;
                Str *_t2942 = Str_lit("  ", 2ULL);
                (void)_t2942;
                Array_set(_va50, &(U64){_t2941}, _t2942);
                ;
                print(_va50);
            }
            ;
        }
    }
    ;
    Str *_t2960 = Str_lit("Str", 3ULL);
    (void)_t2960;
    U64 _t2961; { U64 *_hp = (U64 *)Str_size(); _t2961 = *_hp; free(_hp); }
    (void)_t2961;
    U64 _t2962 = 1;
    (void)_t2962;
    Array *_va53 = Array_new(_t2960, &(U64){_t2961}, &(U64){_t2962});
    (void)_va53;
    Str_delete(_t2960, &(Bool){1});
    ;
    ;
    U64 _t2963 = 0;
    (void)_t2963;
    Str *_t2964 = Str_lit(")", 1ULL);
    (void)_t2964;
    Array_set(_va53, &(U64){_t2963}, _t2964);
    ;
    println(_va53);
}

Bool * enum_has_payloads(Expr * enum_def) {
    (void)enum_def;
    I64 *_t2986 = malloc(sizeof(I64));
    *_t2986 = 0;
    (void)_t2986;
    Expr *body = Expr_child(enum_def, _t2986);
    (void)body;
    {
        U64 _fi2965 = 0;
        (void)_fi2965;
        while (1) {
            I64 _t2973; { I64 *_hp = (I64 *)Expr_child_count(body); _t2973 = *_hp; free(_hp); }
            (void)_t2973;
            U64 _t2974 = 0;
            (void)_t2974;
            U64 _t2975 = I64_to_u64(_t2973);
            (void)_t2975;
            ;
            Range *_t2976 = Range_new(_t2974, _t2975);
            (void)_t2976;
            ;
            ;
            U64 _t2977; { U64 *_hp = (U64 *)Range_len(_t2976); _t2977 = *_hp; free(_hp); }
            (void)_t2977;
            Range_delete(_t2976, &(Bool){1});
            Bool _wcond2966; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2965}, &(U64){_t2977}); _wcond2966 = *_hp; free(_hp); }
            (void)_wcond2966;
            ;
            if (_wcond2966) {
            } else {
                ;
                break;
            }
            ;
            I64 _t2978; { I64 *_hp = (I64 *)Expr_child_count(body); _t2978 = *_hp; free(_hp); }
            (void)_t2978;
            U64 _t2979 = 0;
            (void)_t2979;
            U64 _t2980 = I64_to_u64(_t2978);
            (void)_t2980;
            ;
            Range *_t2981 = Range_new(_t2979, _t2980);
            (void)_t2981;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t2981, _fi2965); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t2981, &(Bool){1});
            U64 _t2982 = 1;
            (void)_t2982;
            U64 _t2983 = U64_add(_fi2965, _t2982);
            (void)_t2983;
            ;
            _fi2965 = _t2983;
            ;
            I64 *_t2984 = malloc(sizeof(I64)); *_t2984 = U64_to_i64(i);
            (void)_t2984;
            ;
            Expr *f = Expr_child(body, _t2984);
            (void)f;
            Bool _t2985; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2985 = *_hp; free(_hp); }
            (void)_t2985;
            if (_t2985) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                U64 _t2968; { U64 *_hp = (U64 *)Str_len(&decl->explicit_type); _t2968 = *_hp; free(_hp); }
                (void)_t2968;
                U64 _t2969 = 0;
                (void)_t2969;
                Bool _t2970 = Bool_not(decl->is_namespace);
                (void)_t2970;
                Declaration_delete(decl, &(Bool){1});
                Bool _t2971; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2968}, &(U64){_t2969}); _t2971 = *_hp; free(_hp); }
                (void)_t2971;
                ;
                ;
                Bool _t2972 = Bool_and(_t2970, _t2971);
                (void)_t2972;
                ;
                ;
                if (_t2972) {
                    Bool _t2967 = 1;
                    (void)_t2967;
                    ;
                    I64_delete(_t2984, &(Bool){1});
                    ;
                    ;
                    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2967; return _r; }
                }
                ;
            }
            I64_delete(_t2984, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t2986, &(Bool){1});
    Bool _t2987 = 0;
    (void)_t2987;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2987; return _r; }
}

I32 * enum_variant_tag(Expr * enum_def, Str * variant_name) {
    (void)enum_def;
    (void)variant_name;
    I64 *_t3007 = malloc(sizeof(I64));
    *_t3007 = 0;
    (void)_t3007;
    Expr *body = Expr_child(enum_def, _t3007);
    (void)body;
    I32 tag = 0;
    (void)tag;
    {
        U64 _fi2988 = 0;
        (void)_fi2988;
        while (1) {
            I64 _t2994; { I64 *_hp = (I64 *)Expr_child_count(body); _t2994 = *_hp; free(_hp); }
            (void)_t2994;
            U64 _t2995 = 0;
            (void)_t2995;
            U64 _t2996 = I64_to_u64(_t2994);
            (void)_t2996;
            ;
            Range *_t2997 = Range_new(_t2995, _t2996);
            (void)_t2997;
            ;
            ;
            U64 _t2998; { U64 *_hp = (U64 *)Range_len(_t2997); _t2998 = *_hp; free(_hp); }
            (void)_t2998;
            Range_delete(_t2997, &(Bool){1});
            Bool _wcond2989; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2988}, &(U64){_t2998}); _wcond2989 = *_hp; free(_hp); }
            (void)_wcond2989;
            ;
            if (_wcond2989) {
            } else {
                ;
                break;
            }
            ;
            I64 _t2999; { I64 *_hp = (I64 *)Expr_child_count(body); _t2999 = *_hp; free(_hp); }
            (void)_t2999;
            U64 _t3000 = 0;
            (void)_t3000;
            U64 _t3001 = I64_to_u64(_t2999);
            (void)_t3001;
            ;
            Range *_t3002 = Range_new(_t3000, _t3001);
            (void)_t3002;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t3002, _fi2988); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t3002, &(Bool){1});
            U64 _t3003 = 1;
            (void)_t3003;
            U64 _t3004 = U64_add(_fi2988, _t3003);
            (void)_t3004;
            ;
            _fi2988 = _t3004;
            ;
            I64 *_t3005 = malloc(sizeof(I64)); *_t3005 = U64_to_i64(i);
            (void)_t3005;
            ;
            Expr *f = Expr_child(body, _t3005);
            (void)f;
            Bool _t3006; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t3006 = *_hp; free(_hp); }
            (void)_t3006;
            if (_t3006) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t2993 = Bool_not(decl->is_namespace);
                (void)_t2993;
                if (_t2993) {
                    Bool _t2990; { Bool *_hp = (Bool *)Str_eq(&decl->name, variant_name); _t2990 = *_hp; free(_hp); }
                    (void)_t2990;
                    if (_t2990) {
                        ;
                        ;
                        Declaration_delete(decl, &(Bool){1});
                        I64_delete(_t3005, &(Bool){1});
                        ;
                        ;
                        { I32 *_r = malloc(sizeof(I32)); *_r = tag; return _r; }
                    }
                    ;
                    I32 _t2991 = 1;
                    (void)_t2991;
                    I32 _t2992 = I32_add(tag, _t2991);
                    (void)_t2992;
                    ;
                    tag = _t2992;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t3005, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t3007, &(Bool){1});
    ;
    I64 _t3008 = 0;
    (void)_t3008;
    I64 _t3009 = 1;
    (void)_t3009;
    I64 _t3010 = I64_sub(_t3008, _t3009);
    (void)_t3010;
    ;
    ;
    I32 _t3011 = I64_to_i32(_t3010);
    (void)_t3011;
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t3011; return _r; }
}

Str * enum_variant_type(Expr * enum_def, I32 tag) {
    (void)enum_def;
    (void)tag;
    I64 *_t3031 = malloc(sizeof(I64));
    *_t3031 = 0;
    (void)_t3031;
    Expr *body = Expr_child(enum_def, _t3031);
    (void)body;
    I32 idx = 0;
    (void)idx;
    {
        U64 _fi3012 = 0;
        (void)_fi3012;
        while (1) {
            I64 _t3018; { I64 *_hp = (I64 *)Expr_child_count(body); _t3018 = *_hp; free(_hp); }
            (void)_t3018;
            U64 _t3019 = 0;
            (void)_t3019;
            U64 _t3020 = I64_to_u64(_t3018);
            (void)_t3020;
            ;
            Range *_t3021 = Range_new(_t3019, _t3020);
            (void)_t3021;
            ;
            ;
            U64 _t3022; { U64 *_hp = (U64 *)Range_len(_t3021); _t3022 = *_hp; free(_hp); }
            (void)_t3022;
            Range_delete(_t3021, &(Bool){1});
            Bool _wcond3013; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3012}, &(U64){_t3022}); _wcond3013 = *_hp; free(_hp); }
            (void)_wcond3013;
            ;
            if (_wcond3013) {
            } else {
                ;
                break;
            }
            ;
            I64 _t3023; { I64 *_hp = (I64 *)Expr_child_count(body); _t3023 = *_hp; free(_hp); }
            (void)_t3023;
            U64 _t3024 = 0;
            (void)_t3024;
            U64 _t3025 = I64_to_u64(_t3023);
            (void)_t3025;
            ;
            Range *_t3026 = Range_new(_t3024, _t3025);
            (void)_t3026;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t3026, _fi3012); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t3026, &(Bool){1});
            U64 _t3027 = 1;
            (void)_t3027;
            U64 _t3028 = U64_add(_fi3012, _t3027);
            (void)_t3028;
            ;
            _fi3012 = _t3028;
            ;
            I64 *_t3029 = malloc(sizeof(I64)); *_t3029 = U64_to_i64(i);
            (void)_t3029;
            ;
            Expr *f = Expr_child(body, _t3029);
            (void)f;
            Bool _t3030; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t3030 = *_hp; free(_hp); }
            (void)_t3030;
            if (_t3030) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t3017 = Bool_not(decl->is_namespace);
                (void)_t3017;
                if (_t3017) {
                    Bool _t3014 = I32_eq(idx, tag);
                    (void)_t3014;
                    if (_t3014) {
                        ;
                        ;
                        I64_delete(_t3029, &(Bool){1});
                        ;
                        ;
                        { Str *_r = malloc(sizeof(Str)); *_r = decl->explicit_type; return _r; }
                    }
                    ;
                    I32 _t3015 = 1;
                    (void)_t3015;
                    I32 _t3016 = I32_add(idx, _t3015);
                    (void)_t3016;
                    ;
                    idx = _t3016;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t3029, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t3031, &(Bool){1});
    ;
    Str *_t3032 = Str_lit("", 0ULL);
    (void)_t3032;
    return _t3032;
}

