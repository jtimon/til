Str * til_type_name_c(TilType * t) {
    (void)t;
    {
        TilType *_sw2272 = TilType_clone(t);
        (void)_sw2272;
        Bool _t2307; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_Unknown()); _t2307 = *_hp; free(_hp); }
        (void)_t2307;
        if (_t2307) {
            Str *_t2273 = Str_lit("unknown", 7ULL);
            (void)_t2273;
            TilType_delete(_sw2272, &(Bool){1});
            ;
            return _t2273;
        } else {
            Bool _t2306; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_None()); _t2306 = *_hp; free(_hp); }
            (void)_t2306;
            if (_t2306) {
                Str *_t2274 = Str_lit("None", 4ULL);
                (void)_t2274;
                ;
                TilType_delete(_sw2272, &(Bool){1});
                ;
                return _t2274;
            } else {
                Bool _t2305; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_I64()); _t2305 = *_hp; free(_hp); }
                (void)_t2305;
                if (_t2305) {
                    Str *_t2275 = Str_lit("I64", 3ULL);
                    (void)_t2275;
                    ;
                    ;
                    TilType_delete(_sw2272, &(Bool){1});
                    ;
                    return _t2275;
                } else {
                    Bool _t2304; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_U8()); _t2304 = *_hp; free(_hp); }
                    (void)_t2304;
                    if (_t2304) {
                        Str *_t2276 = Str_lit("U8", 2ULL);
                        (void)_t2276;
                        ;
                        ;
                        ;
                        TilType_delete(_sw2272, &(Bool){1});
                        ;
                        return _t2276;
                    } else {
                        Bool _t2303; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_I16()); _t2303 = *_hp; free(_hp); }
                        (void)_t2303;
                        if (_t2303) {
                            Str *_t2277 = Str_lit("I16", 3ULL);
                            (void)_t2277;
                            ;
                            ;
                            ;
                            ;
                            TilType_delete(_sw2272, &(Bool){1});
                            ;
                            return _t2277;
                        } else {
                            Bool _t2302; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_I32()); _t2302 = *_hp; free(_hp); }
                            (void)_t2302;
                            if (_t2302) {
                                Str *_t2278 = Str_lit("I32", 3ULL);
                                (void)_t2278;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TilType_delete(_sw2272, &(Bool){1});
                                ;
                                return _t2278;
                            } else {
                                Bool _t2301; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_U32()); _t2301 = *_hp; free(_hp); }
                                (void)_t2301;
                                if (_t2301) {
                                    Str *_t2279 = Str_lit("U32", 3ULL);
                                    (void)_t2279;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TilType_delete(_sw2272, &(Bool){1});
                                    ;
                                    return _t2279;
                                } else {
                                    Bool _t2300; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_U64()); _t2300 = *_hp; free(_hp); }
                                    (void)_t2300;
                                    if (_t2300) {
                                        Str *_t2280 = Str_lit("U64", 3ULL);
                                        (void)_t2280;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TilType_delete(_sw2272, &(Bool){1});
                                        ;
                                        return _t2280;
                                    } else {
                                        Bool _t2299; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_F32()); _t2299 = *_hp; free(_hp); }
                                        (void)_t2299;
                                        if (_t2299) {
                                            Str *_t2281 = Str_lit("F32", 3ULL);
                                            (void)_t2281;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TilType_delete(_sw2272, &(Bool){1});
                                            ;
                                            return _t2281;
                                        } else {
                                            Bool _t2298; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_Bool()); _t2298 = *_hp; free(_hp); }
                                            (void)_t2298;
                                            if (_t2298) {
                                                Str *_t2282 = Str_lit("Bool", 4ULL);
                                                (void)_t2282;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                TilType_delete(_sw2272, &(Bool){1});
                                                ;
                                                return _t2282;
                                            } else {
                                                Bool _t2297; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_Struct()); _t2297 = *_hp; free(_hp); }
                                                (void)_t2297;
                                                if (_t2297) {
                                                    Str *_t2283 = Str_lit("Struct", 6ULL);
                                                    (void)_t2283;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    TilType_delete(_sw2272, &(Bool){1});
                                                    ;
                                                    return _t2283;
                                                } else {
                                                    Bool _t2296; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_StructDef()); _t2296 = *_hp; free(_hp); }
                                                    (void)_t2296;
                                                    if (_t2296) {
                                                        Str *_t2284 = Str_lit("StructDef", 9ULL);
                                                        (void)_t2284;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        TilType_delete(_sw2272, &(Bool){1});
                                                        ;
                                                        return _t2284;
                                                    } else {
                                                        Bool _t2295; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_Enum()); _t2295 = *_hp; free(_hp); }
                                                        (void)_t2295;
                                                        if (_t2295) {
                                                            Str *_t2285 = Str_lit("Enum", 4ULL);
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
                                                            ;
                                                            ;
                                                            ;
                                                            TilType_delete(_sw2272, &(Bool){1});
                                                            ;
                                                            return _t2285;
                                                        } else {
                                                            Bool _t2294; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_EnumDef()); _t2294 = *_hp; free(_hp); }
                                                            (void)_t2294;
                                                            if (_t2294) {
                                                                Str *_t2286 = Str_lit("EnumDef", 7ULL);
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
                                                                ;
                                                                ;
                                                                ;
                                                                TilType_delete(_sw2272, &(Bool){1});
                                                                ;
                                                                return _t2286;
                                                            } else {
                                                                Bool _t2293; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_FuncDef()); _t2293 = *_hp; free(_hp); }
                                                                (void)_t2293;
                                                                if (_t2293) {
                                                                    Str *_t2287 = Str_lit("FunctionDef", 11ULL);
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
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    TilType_delete(_sw2272, &(Bool){1});
                                                                    ;
                                                                    return _t2287;
                                                                } else {
                                                                    Bool _t2292; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_FuncPtr()); _t2292 = *_hp; free(_hp); }
                                                                    (void)_t2292;
                                                                    if (_t2292) {
                                                                        Str *_t2288 = Str_lit("Fn", 2ULL);
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
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        TilType_delete(_sw2272, &(Bool){1});
                                                                        ;
                                                                        return _t2288;
                                                                    } else {
                                                                        Bool _t2291; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_Dynamic()); _t2291 = *_hp; free(_hp); }
                                                                        (void)_t2291;
                                                                        if (_t2291) {
                                                                            Str *_t2289 = Str_lit("Dynamic", 7ULL);
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
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TilType_delete(_sw2272, &(Bool){1});
                                                                            ;
                                                                            return _t2289;
                                                                        } else {
                                                                            Str *_t2290 = Str_lit("?", 1ULL);
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
                                                                            ;
                                                                            ;
                                                                            TilType_delete(_sw2272, &(Bool){1});
                                                                            ;
                                                                            return _t2290;
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
        TilType_delete(_sw2272, &(Bool){1});
        ;
    }
}

Bool * Declaration_eq(Declaration * a, Declaration * b) {
    (void)a;
    (void)b;
    Bool _t2308; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t2308 = *_hp; free(_hp); }
    (void)_t2308;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2308; return _r; }
}

Str * Declaration_to_str(Declaration * self) {
    (void)self;
    { Str *_r = malloc(sizeof(Str)); *_r = self->name; return _r; }
}

Declaration * Declaration_clone(Declaration * self) {
    (void)self;
    Bool _t2309 = Bool_clone(&self->is_mut);
    (void)_t2309;
    Bool _t2310 = Bool_clone(&self->is_namespace);
    (void)_t2310;
    Bool _t2311 = Bool_clone(&self->is_ref);
    (void)_t2311;
    Bool _t2312 = Bool_clone(&self->is_own);
    (void)_t2312;
    I32 _t2313 = I32_clone(&self->field_offset);
    (void)_t2313;
    I32 _t2314 = I32_clone(&self->field_size);
    (void)_t2314;
    Declaration *_t2315 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); _t2315->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); _t2315->explicit_type = *_ca; free(_ca); }
    _t2315->is_mut = _t2309;
    _t2315->is_namespace = _t2310;
    _t2315->is_ref = _t2311;
    _t2315->is_own = _t2312;
    _t2315->field_offset = _t2313;
    _t2315->field_size = _t2314;
    _t2315->field_struct_def = self->field_struct_def;
    _t2315->fn_sig = self->fn_sig;
    (void)_t2315;
    ;
    ;
    ;
    ;
    ;
    ;
    return _t2315;
}

U64 *Declaration_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Declaration);
    return r;
}

void Expr_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Str *_t2639 = Str_lit("Str", 3ULL);
    (void)_t2639;
    U64 _t2640; { U64 *_hp = (U64 *)Str_size(); _t2640 = *_hp; free(_hp); }
    (void)_t2640;
    U64 _t2641 = 7;
    (void)_t2641;
    Array *_va35 = Array_new(_t2639, &(U64){_t2640}, &(U64){_t2641});
    (void)_va35;
    Str_delete(_t2639, &(Bool){1});
    ;
    ;
    U64 _t2642 = 0;
    (void)_t2642;
    Str *_t2643 = Str_clone(&self->path);
    (void)_t2643;
    Array_set(_va35, &(U64){_t2642}, _t2643);
    ;
    U64 _t2644 = 1;
    (void)_t2644;
    Str *_t2645 = Str_lit(":", 1ULL);
    (void)_t2645;
    Array_set(_va35, &(U64){_t2644}, _t2645);
    ;
    U64 _t2646 = 2;
    (void)_t2646;
    Str *_t2647 = U32_to_str(&self->line);
    (void)_t2647;
    Array_set(_va35, &(U64){_t2646}, _t2647);
    ;
    U64 _t2648 = 3;
    (void)_t2648;
    Str *_t2649 = Str_lit(":", 1ULL);
    (void)_t2649;
    Array_set(_va35, &(U64){_t2648}, _t2649);
    ;
    U64 _t2650 = 4;
    (void)_t2650;
    Str *_t2651 = U32_to_str(&self->col);
    (void)_t2651;
    Array_set(_va35, &(U64){_t2650}, _t2651);
    ;
    U64 _t2652 = 5;
    (void)_t2652;
    Str *_t2653 = Str_lit(": error: ", 9ULL);
    (void)_t2653;
    Array_set(_va35, &(U64){_t2652}, _t2653);
    ;
    U64 _t2654 = 6;
    (void)_t2654;
    Str *_t2655 = Str_clone(msg);
    (void)_t2655;
    Array_set(_va35, &(U64){_t2654}, _t2655);
    ;
    println(_va35);
}

void Expr_todo_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Expr_error(self, msg);
    Str *_t2656 = Str_lit("Str", 3ULL);
    (void)_t2656;
    U64 _t2657; { U64 *_hp = (U64 *)Str_size(); _t2657 = *_hp; free(_hp); }
    (void)_t2657;
    U64 _t2658 = 1;
    (void)_t2658;
    Array *_va36 = Array_new(_t2656, &(U64){_t2657}, &(U64){_t2658});
    (void)_va36;
    Str_delete(_t2656, &(Bool){1});
    ;
    ;
    U64 _t2659 = 0;
    (void)_t2659;
    Str *_t2660 = Str_lit("  note: this language feature is not implemented yet", 52ULL);
    (void)_t2660;
    Array_set(_va36, &(U64){_t2659}, _t2660);
    ;
    println(_va36);
}

void Expr_lang_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Expr_error(self, msg);
    Str *_t2661 = Str_lit("Str", 3ULL);
    (void)_t2661;
    U64 _t2662; { U64 *_hp = (U64 *)Str_size(); _t2662 = *_hp; free(_hp); }
    (void)_t2662;
    U64 _t2663 = 1;
    (void)_t2663;
    Array *_va37 = Array_new(_t2661, &(U64){_t2662}, &(U64){_t2663});
    (void)_va37;
    Str_delete(_t2661, &(Bool){1});
    ;
    ;
    U64 _t2664 = 0;
    (void)_t2664;
    Str *_t2665 = Str_lit("  note: this is a bug in the language, please report it", 55ULL);
    (void)_t2665;
    Array_set(_va37, &(U64){_t2664}, _t2665);
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
    U64 *_t2666 = malloc(sizeof(U64)); *_t2666 = I64_to_u64(DEREF(i));
    (void)_t2666;
    Expr *c = Vec_get(&parent->children, _t2666);
    (void)c;
    U64_delete(_t2666, &(Bool){1});
    return c;
}

I64 * Expr_child_count(Expr * parent) {
    (void)parent;
    U64 _t2667; { U64 *_hp = (U64 *)Vec_len(&parent->children); _t2667 = *_hp; free(_hp); }
    (void)_t2667;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t2667; return _r; }
}

Expr * Expr_new(ExprData * data, U32 line, U32 col, Str * path) {
    (void)data;
    (void)line;
    (void)col;
    (void)path;
    I64 _t2668 = 0;
    (void)_t2668;
    I64 _t2669 = 1;
    (void)_t2669;
    I64 _t2670 = I64_sub(_t2668, _t2669);
    (void)_t2670;
    ;
    ;
    I64 _t2671 = 0;
    (void)_t2671;
    I64 _t2672 = 1;
    (void)_t2672;
    I64 _t2673 = I64_sub(_t2671, _t2672);
    (void)_t2673;
    ;
    ;
    Str *_t2674 = Str_lit("Expr", 4ULL);
    (void)_t2674;
    U64 _t2675; { U64 *_hp = (U64 *)Expr_size(); _t2675 = *_hp; free(_hp); }
    (void)_t2675;
    Bool _t2676 = 0;
    (void)_t2676;
    Bool _t2677 = 0;
    (void)_t2677;
    Bool _t2678 = 0;
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
    I32 _t2684 = 0;
    (void)_t2684;
    I32 _t2685 = I64_to_i32(_t2670);
    (void)_t2685;
    ;
    U32 _t2686 = 0;
    (void)_t2686;
    I32 _t2687 = I64_to_i32(_t2673);
    (void)_t2687;
    ;
    U32 _t2688 = 0;
    (void)_t2688;
    U32 _t2689 = U32_clone(&(U32){col});
    (void)_t2689;
    Str *_t2690 = Str_clone(path);
    (void)_t2690;
    Expr *_t2691 = malloc(sizeof(Expr));
    { ExprData *_ca = ExprData_clone(data); _t2691->data = *_ca; free(_ca); }
    { TilType *_ca = TilType_clone(TilType_Unknown()); _t2691->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t2691->struct_name = *_ca; free(_ca); }
    _t2691->is_own_arg = _t2676;
    _t2691->is_splat = _t2677;
    _t2691->is_own_field = _t2678;
    _t2691->is_ref_field = _t2679;
    _t2691->is_ns_field = _t2680;
    _t2691->is_ext = _t2681;
    _t2691->is_core = _t2682;
    _t2691->save_old_delete = _t2683;
    _t2691->total_struct_size = _t2684;
    _t2691->variadic_index = _t2685;
    _t2691->variadic_count = _t2686;
    _t2691->kwargs_index = _t2687;
    _t2691->kwargs_count = _t2688;
    _t2691->fn_sig = NULL;
    { Vec *_ca = Vec_new(_t2674, &(U64){_t2675}); _t2691->children = *_ca; free(_ca); }
    _t2691->line = U32_clone(&(U32){line});
    _t2691->col = _t2689;
    { Str *_ca = Str_clone(_t2690); _t2691->path = *_ca; free(_ca); }
    (void)_t2691;
    Str_delete(_t2674, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    Str_delete(_t2690, &(Bool){1});
    return _t2691;
}

Expr * Expr_clone(Expr * self) {
    (void)self;
    Bool _t2692 = Bool_clone(&self->is_own_arg);
    (void)_t2692;
    Bool _t2693 = Bool_clone(&self->is_splat);
    (void)_t2693;
    Bool _t2694 = Bool_clone(&self->is_own_field);
    (void)_t2694;
    Bool _t2695 = Bool_clone(&self->is_ref_field);
    (void)_t2695;
    Bool _t2696 = Bool_clone(&self->is_ns_field);
    (void)_t2696;
    Bool _t2697 = Bool_clone(&self->is_ext);
    (void)_t2697;
    Bool _t2698 = Bool_clone(&self->is_core);
    (void)_t2698;
    Bool _t2699 = Bool_clone(&self->save_old_delete);
    (void)_t2699;
    I32 _t2700 = I32_clone(&self->total_struct_size);
    (void)_t2700;
    I32 _t2701 = I32_clone(&self->variadic_index);
    (void)_t2701;
    U32 _t2702 = U32_clone(&self->variadic_count);
    (void)_t2702;
    I32 _t2703 = I32_clone(&self->kwargs_index);
    (void)_t2703;
    U32 _t2704 = U32_clone(&self->kwargs_count);
    (void)_t2704;
    U32 _t2705 = U32_clone(&self->col);
    (void)_t2705;
    Str *_t2706 = Str_clone(&self->path);
    (void)_t2706;
    Expr *_t2707 = malloc(sizeof(Expr));
    { ExprData *_ca = ExprData_clone(&self->data); _t2707->data = *_ca; free(_ca); }
    { TilType *_ca = TilType_clone(&self->til_type); _t2707->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->struct_name); _t2707->struct_name = *_ca; free(_ca); }
    _t2707->is_own_arg = _t2692;
    _t2707->is_splat = _t2693;
    _t2707->is_own_field = _t2694;
    _t2707->is_ref_field = _t2695;
    _t2707->is_ns_field = _t2696;
    _t2707->is_ext = _t2697;
    _t2707->is_core = _t2698;
    _t2707->save_old_delete = _t2699;
    _t2707->total_struct_size = _t2700;
    _t2707->variadic_index = _t2701;
    _t2707->variadic_count = _t2702;
    _t2707->kwargs_index = _t2703;
    _t2707->kwargs_count = _t2704;
    _t2707->fn_sig = self->fn_sig;
    { Vec *_ca = Vec_clone(&self->children); _t2707->children = *_ca; free(_ca); }
    _t2707->line = U32_clone(&self->line);
    _t2707->col = _t2705;
    { Str *_ca = Str_clone(_t2706); _t2707->path = *_ca; free(_ca); }
    (void)_t2707;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    Str_delete(_t2706, &(Bool){1});
    return _t2707;
}

U64 *Expr_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Expr);
    return r;
}

Str * node_name(ExprData * data) {
    (void)data;
    {
        ExprData *_sw2729 = ExprData_clone(data);
        (void)_sw2729;
        Bool _t2780; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_Body()); _t2780 = *_hp; free(_hp); }
        (void)_t2780;
        if (_t2780) {
            Str *_t2730 = Str_lit("body", 4ULL);
            (void)_t2730;
            ExprData_delete(_sw2729, &(Bool){1});
            ;
            return _t2730;
        } else {
            Bool _t2779; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw2729); _t2779 = *_hp; free(_hp); }
            (void)_t2779;
            if (_t2779) {
                Str *_t2731 = Str_lit("str", 3ULL);
                (void)_t2731;
                ;
                ExprData_delete(_sw2729, &(Bool){1});
                ;
                return _t2731;
            } else {
                Bool _t2778; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw2729); _t2778 = *_hp; free(_hp); }
                (void)_t2778;
                if (_t2778) {
                    Str *_t2732 = Str_lit("num", 3ULL);
                    (void)_t2732;
                    ;
                    ;
                    ExprData_delete(_sw2729, &(Bool){1});
                    ;
                    return _t2732;
                } else {
                    Bool _t2777; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw2729); _t2777 = *_hp; free(_hp); }
                    (void)_t2777;
                    if (_t2777) {
                        Str *_t2733 = Str_lit("bool", 4ULL);
                        (void)_t2733;
                        ;
                        ;
                        ;
                        ExprData_delete(_sw2729, &(Bool){1});
                        ;
                        return _t2733;
                    } else {
                        Bool _t2776; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_LiteralNull()); _t2776 = *_hp; free(_hp); }
                        (void)_t2776;
                        if (_t2776) {
                            Str *_t2734 = Str_lit("null", 4ULL);
                            (void)_t2734;
                            ;
                            ;
                            ;
                            ;
                            ExprData_delete(_sw2729, &(Bool){1});
                            ;
                            return _t2734;
                        } else {
                            Bool _t2775; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw2729); _t2775 = *_hp; free(_hp); }
                            (void)_t2775;
                            if (_t2775) {
                                Str *_t2735 = Str_lit("ident", 5ULL);
                                (void)_t2735;
                                ;
                                ;
                                ;
                                ;
                                ;
                                ExprData_delete(_sw2729, &(Bool){1});
                                ;
                                return _t2735;
                            } else {
                                Bool _t2774; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw2729); _t2774 = *_hp; free(_hp); }
                                (void)_t2774;
                                if (_t2774) {
                                    Str *_t2736 = Str_lit("decl", 4ULL);
                                    (void)_t2736;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ExprData_delete(_sw2729, &(Bool){1});
                                    ;
                                    return _t2736;
                                } else {
                                    Bool _t2773; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw2729); _t2773 = *_hp; free(_hp); }
                                    (void)_t2773;
                                    if (_t2773) {
                                        Str *_t2737 = Str_lit("assign", 6ULL);
                                        (void)_t2737;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ExprData_delete(_sw2729, &(Bool){1});
                                        ;
                                        return _t2737;
                                    } else {
                                        Bool _t2772; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_FCall()); _t2772 = *_hp; free(_hp); }
                                        (void)_t2772;
                                        if (_t2772) {
                                            Str *_t2738 = Str_lit("fcall", 5ULL);
                                            (void)_t2738;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ExprData_delete(_sw2729, &(Bool){1});
                                            ;
                                            return _t2738;
                                        } else {
                                            Bool _t2771; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw2729); _t2771 = *_hp; free(_hp); }
                                            (void)_t2771;
                                            if (_t2771) {
                                                Str *_t2739 = Str_lit("func_def", 8ULL);
                                                (void)_t2739;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ExprData_delete(_sw2729, &(Bool){1});
                                                ;
                                                return _t2739;
                                            } else {
                                                Bool _t2770; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_StructDef()); _t2770 = *_hp; free(_hp); }
                                                (void)_t2770;
                                                if (_t2770) {
                                                    Str *_t2740 = Str_lit("struct_def", 10ULL);
                                                    (void)_t2740;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ExprData_delete(_sw2729, &(Bool){1});
                                                    ;
                                                    return _t2740;
                                                } else {
                                                    Bool _t2769; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_EnumDef()); _t2769 = *_hp; free(_hp); }
                                                    (void)_t2769;
                                                    if (_t2769) {
                                                        Str *_t2741 = Str_lit("enum_def", 8ULL);
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
                                                        ;
                                                        ;
                                                        ExprData_delete(_sw2729, &(Bool){1});
                                                        ;
                                                        return _t2741;
                                                    } else {
                                                        Bool _t2768; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(_sw2729); _t2768 = *_hp; free(_hp); }
                                                        (void)_t2768;
                                                        if (_t2768) {
                                                            Str *_t2742 = Str_lit("field_access", 12ULL);
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
                                                            ;
                                                            ;
                                                            ExprData_delete(_sw2729, &(Bool){1});
                                                            ;
                                                            return _t2742;
                                                        } else {
                                                            Bool _t2767; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(_sw2729); _t2767 = *_hp; free(_hp); }
                                                            (void)_t2767;
                                                            if (_t2767) {
                                                                Str *_t2743 = Str_lit("field_assign", 12ULL);
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
                                                                ;
                                                                ;
                                                                ExprData_delete(_sw2729, &(Bool){1});
                                                                ;
                                                                return _t2743;
                                                            } else {
                                                                Bool _t2766; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_Return()); _t2766 = *_hp; free(_hp); }
                                                                (void)_t2766;
                                                                if (_t2766) {
                                                                    Str *_t2744 = Str_lit("return", 6ULL);
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
                                                                    ;
                                                                    ;
                                                                    ExprData_delete(_sw2729, &(Bool){1});
                                                                    ;
                                                                    return _t2744;
                                                                } else {
                                                                    Bool _t2765; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_If()); _t2765 = *_hp; free(_hp); }
                                                                    (void)_t2765;
                                                                    if (_t2765) {
                                                                        Str *_t2745 = Str_lit("if", 2ULL);
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
                                                                        ;
                                                                        ;
                                                                        ExprData_delete(_sw2729, &(Bool){1});
                                                                        ;
                                                                        return _t2745;
                                                                    } else {
                                                                        Bool _t2764; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_While()); _t2764 = *_hp; free(_hp); }
                                                                        (void)_t2764;
                                                                        if (_t2764) {
                                                                            Str *_t2746 = Str_lit("while", 5ULL);
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
                                                                            ;
                                                                            ;
                                                                            ExprData_delete(_sw2729, &(Bool){1});
                                                                            ;
                                                                            return _t2746;
                                                                        } else {
                                                                            Bool _t2763; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw2729); _t2763 = *_hp; free(_hp); }
                                                                            (void)_t2763;
                                                                            if (_t2763) {
                                                                                Str *_t2747 = Str_lit("for_in", 6ULL);
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
                                                                                ;
                                                                                ;
                                                                                ExprData_delete(_sw2729, &(Bool){1});
                                                                                ;
                                                                                return _t2747;
                                                                            } else {
                                                                                Bool _t2762; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw2729); _t2762 = *_hp; free(_hp); }
                                                                                (void)_t2762;
                                                                                if (_t2762) {
                                                                                    Str *_t2748 = Str_lit("named_arg", 9ULL);
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
                                                                                    ;
                                                                                    ;
                                                                                    ExprData_delete(_sw2729, &(Bool){1});
                                                                                    ;
                                                                                    return _t2748;
                                                                                } else {
                                                                                    Bool _t2761; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_Break()); _t2761 = *_hp; free(_hp); }
                                                                                    (void)_t2761;
                                                                                    if (_t2761) {
                                                                                        Str *_t2749 = Str_lit("break", 5ULL);
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
                                                                                        ;
                                                                                        ;
                                                                                        ExprData_delete(_sw2729, &(Bool){1});
                                                                                        ;
                                                                                        return _t2749;
                                                                                    } else {
                                                                                        Bool _t2760; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_Continue()); _t2760 = *_hp; free(_hp); }
                                                                                        (void)_t2760;
                                                                                        if (_t2760) {
                                                                                            Str *_t2750 = Str_lit("continue", 8ULL);
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
                                                                                            ;
                                                                                            ;
                                                                                            ExprData_delete(_sw2729, &(Bool){1});
                                                                                            ;
                                                                                            return _t2750;
                                                                                        } else {
                                                                                            Bool _t2759; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_MapLit()); _t2759 = *_hp; free(_hp); }
                                                                                            (void)_t2759;
                                                                                            if (_t2759) {
                                                                                                Str *_t2751 = Str_lit("map_lit", 7ULL);
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
                                                                                                ;
                                                                                                ;
                                                                                                ExprData_delete(_sw2729, &(Bool){1});
                                                                                                ;
                                                                                                return _t2751;
                                                                                            } else {
                                                                                                Bool _t2758; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_SetLit()); _t2758 = *_hp; free(_hp); }
                                                                                                (void)_t2758;
                                                                                                if (_t2758) {
                                                                                                    Str *_t2752 = Str_lit("set_lit", 7ULL);
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
                                                                                                    ;
                                                                                                    ;
                                                                                                    ExprData_delete(_sw2729, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t2752;
                                                                                                } else {
                                                                                                    Bool _t2757; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_Switch()); _t2757 = *_hp; free(_hp); }
                                                                                                    (void)_t2757;
                                                                                                    if (_t2757) {
                                                                                                        Str *_t2753 = Str_lit("switch", 6ULL);
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
                                                                                                        ;
                                                                                                        ;
                                                                                                        ExprData_delete(_sw2729, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t2753;
                                                                                                    } else {
                                                                                                        Bool _t2756; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_Case()); _t2756 = *_hp; free(_hp); }
                                                                                                        (void)_t2756;
                                                                                                        if (_t2756) {
                                                                                                            Str *_t2754 = Str_lit("case", 4ULL);
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
                                                                                                            ;
                                                                                                            ;
                                                                                                            ExprData_delete(_sw2729, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t2754;
                                                                                                        } else {
                                                                                                            Str *_t2755 = Str_lit("?", 1ULL);
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
                                                                                                            ;
                                                                                                            ExprData_delete(_sw2729, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t2755;
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
        ExprData_delete(_sw2729, &(Bool){1});
        ;
    }
}

Str * func_type_name(FuncType * ft) {
    (void)ft;
    {
        FuncType *_sw2781 = FuncType_clone(ft);
        (void)_sw2781;
        Bool _t2794; { Bool *_hp = (Bool *)FuncType_eq(_sw2781, FuncType_Func()); _t2794 = *_hp; free(_hp); }
        (void)_t2794;
        if (_t2794) {
            Str *_t2782 = Str_lit("func", 4ULL);
            (void)_t2782;
            FuncType_delete(_sw2781, &(Bool){1});
            ;
            return _t2782;
        } else {
            Bool _t2793; { Bool *_hp = (Bool *)FuncType_eq(_sw2781, FuncType_Proc()); _t2793 = *_hp; free(_hp); }
            (void)_t2793;
            if (_t2793) {
                Str *_t2783 = Str_lit("proc", 4ULL);
                (void)_t2783;
                ;
                FuncType_delete(_sw2781, &(Bool){1});
                ;
                return _t2783;
            } else {
                Bool _t2792; { Bool *_hp = (Bool *)FuncType_eq(_sw2781, FuncType_Test()); _t2792 = *_hp; free(_hp); }
                (void)_t2792;
                if (_t2792) {
                    Str *_t2784 = Str_lit("test", 4ULL);
                    (void)_t2784;
                    ;
                    ;
                    FuncType_delete(_sw2781, &(Bool){1});
                    ;
                    return _t2784;
                } else {
                    Bool _t2791; { Bool *_hp = (Bool *)FuncType_eq(_sw2781, FuncType_Macro()); _t2791 = *_hp; free(_hp); }
                    (void)_t2791;
                    if (_t2791) {
                        Str *_t2785 = Str_lit("macro", 5ULL);
                        (void)_t2785;
                        ;
                        ;
                        ;
                        FuncType_delete(_sw2781, &(Bool){1});
                        ;
                        return _t2785;
                    } else {
                        Bool _t2790; { Bool *_hp = (Bool *)FuncType_eq(_sw2781, FuncType_ExtFunc()); _t2790 = *_hp; free(_hp); }
                        (void)_t2790;
                        if (_t2790) {
                            Str *_t2786 = Str_lit("ext_func", 8ULL);
                            (void)_t2786;
                            ;
                            ;
                            ;
                            ;
                            FuncType_delete(_sw2781, &(Bool){1});
                            ;
                            return _t2786;
                        } else {
                            Bool _t2789; { Bool *_hp = (Bool *)FuncType_eq(_sw2781, FuncType_ExtProc()); _t2789 = *_hp; free(_hp); }
                            (void)_t2789;
                            if (_t2789) {
                                Str *_t2787 = Str_lit("ext_proc", 8ULL);
                                (void)_t2787;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw2781, &(Bool){1});
                                ;
                                return _t2787;
                            } else {
                                Str *_t2788 = Str_lit("?", 1ULL);
                                (void)_t2788;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw2781, &(Bool){1});
                                ;
                                return _t2788;
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
        FuncType_delete(_sw2781, &(Bool){1});
        ;
    }
}

void ast_print(Expr * e, U32 indent) {
    (void)e;
    (void)indent;
    {
        U64 _fi2795 = 0;
        (void)_fi2795;
        while (1) {
            I64 _t2797 = U32_to_i64(indent);
            (void)_t2797;
            U64 _t2798 = 0;
            (void)_t2798;
            U64 _t2799 = I64_to_u64(_t2797);
            (void)_t2799;
            ;
            Range *_t2800 = Range_new(_t2798, _t2799);
            (void)_t2800;
            ;
            ;
            U64 _t2801; { U64 *_hp = (U64 *)Range_len(_t2800); _t2801 = *_hp; free(_hp); }
            (void)_t2801;
            Range_delete(_t2800, &(Bool){1});
            Bool _wcond2796; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2795}, &(U64){_t2801}); _wcond2796 = *_hp; free(_hp); }
            (void)_wcond2796;
            ;
            if (_wcond2796) {
            } else {
                ;
                break;
            }
            ;
            I64 _t2802 = U32_to_i64(indent);
            (void)_t2802;
            U64 _t2803 = 0;
            (void)_t2803;
            U64 _t2804 = I64_to_u64(_t2802);
            (void)_t2804;
            ;
            Range *_t2805 = Range_new(_t2803, _t2804);
            (void)_t2805;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t2805, _fi2795); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t2805, &(Bool){1});
            ;
            U64 _t2806 = 1;
            (void)_t2806;
            U64 _t2807 = U64_add(_fi2795, _t2806);
            (void)_t2807;
            ;
            _fi2795 = _t2807;
            ;
            Str *_t2808 = Str_lit("Str", 3ULL);
            (void)_t2808;
            U64 _t2809; { U64 *_hp = (U64 *)Str_size(); _t2809 = *_hp; free(_hp); }
            (void)_t2809;
            U64 _t2810 = 1;
            (void)_t2810;
            Array *_va38 = Array_new(_t2808, &(U64){_t2809}, &(U64){_t2810});
            (void)_va38;
            Str_delete(_t2808, &(Bool){1});
            ;
            ;
            U64 _t2811 = 0;
            (void)_t2811;
            Str *_t2812 = Str_lit("  ", 2ULL);
            (void)_t2812;
            Array_set(_va38, &(U64){_t2811}, _t2812);
            ;
            print(_va38);
        }
        ;
    }
    Str *_t2946 = Str_lit("Str", 3ULL);
    (void)_t2946;
    U64 _t2947; { U64 *_hp = (U64 *)Str_size(); _t2947 = *_hp; free(_hp); }
    (void)_t2947;
    U64 _t2948 = 2;
    (void)_t2948;
    Array *_va52 = Array_new(_t2946, &(U64){_t2947}, &(U64){_t2948});
    (void)_va52;
    Str_delete(_t2946, &(Bool){1});
    ;
    ;
    U64 _t2949 = 0;
    (void)_t2949;
    Str *_t2950 = Str_lit("(", 1ULL);
    (void)_t2950;
    Array_set(_va52, &(U64){_t2949}, _t2950);
    ;
    U64 _t2951 = 1;
    (void)_t2951;
    Str *_t2952 = node_name(&e->data);
    (void)_t2952;
    Array_set(_va52, &(U64){_t2951}, _t2952);
    ;
    print(_va52);
    Bool _t2953; { Bool *_hp = (Bool *)TilType_eq(&e->til_type, TilType_Unknown()); _t2953 = *_hp; free(_hp); }
    (void)_t2953;
    Bool _t2954 = Bool_not(_t2953);
    (void)_t2954;
    ;
    if (_t2954) {
        Str *_t2813 = Str_lit("Str", 3ULL);
        (void)_t2813;
        U64 _t2814; { U64 *_hp = (U64 *)Str_size(); _t2814 = *_hp; free(_hp); }
        (void)_t2814;
        U64 _t2815 = 2;
        (void)_t2815;
        Array *_va39 = Array_new(_t2813, &(U64){_t2814}, &(U64){_t2815});
        (void)_va39;
        Str_delete(_t2813, &(Bool){1});
        ;
        ;
        U64 _t2816 = 0;
        (void)_t2816;
        Str *_t2817 = Str_lit(":", 1ULL);
        (void)_t2817;
        Array_set(_va39, &(U64){_t2816}, _t2817);
        ;
        U64 _t2818 = 1;
        (void)_t2818;
        Str *_t2819 = til_type_name_c(&e->til_type);
        (void)_t2819;
        Array_set(_va39, &(U64){_t2818}, _t2819);
        ;
        print(_va39);
    }
    ;
    {
        ExprData *_sw2820 = ExprData_clone(&e->data);
        (void)_sw2820;
        Bool _t2907; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw2820); _t2907 = *_hp; free(_hp); }
        (void)_t2907;
        if (_t2907) {
            Str *s = ExprData_get_Ident(_sw2820);
            (void)s;
            Str *_t2821 = Str_lit("Str", 3ULL);
            (void)_t2821;
            U64 _t2822; { U64 *_hp = (U64 *)Str_size(); _t2822 = *_hp; free(_hp); }
            (void)_t2822;
            U64 _t2823 = 3;
            (void)_t2823;
            Array *_va40 = Array_new(_t2821, &(U64){_t2822}, &(U64){_t2823});
            (void)_va40;
            Str_delete(_t2821, &(Bool){1});
            ;
            ;
            U64 _t2824 = 0;
            (void)_t2824;
            Str *_t2825 = Str_lit(" \"", 3ULL);
            (void)_t2825;
            Array_set(_va40, &(U64){_t2824}, _t2825);
            ;
            U64 _t2826 = 1;
            (void)_t2826;
            Str *_t2827 = Str_clone(s);
            (void)_t2827;
            Str_delete(s, &(Bool){1});
            Array_set(_va40, &(U64){_t2826}, _t2827);
            ;
            U64 _t2828 = 2;
            (void)_t2828;
            Str *_t2829 = Str_lit("\"", 2ULL);
            (void)_t2829;
            Array_set(_va40, &(U64){_t2828}, _t2829);
            ;
            print(_va40);
        } else {
            Bool _t2906; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw2820); _t2906 = *_hp; free(_hp); }
            (void)_t2906;
            if (_t2906) {
                Str *s = ExprData_get_LiteralStr(_sw2820);
                (void)s;
                Str *_t2830 = Str_lit("Str", 3ULL);
                (void)_t2830;
                U64 _t2831; { U64 *_hp = (U64 *)Str_size(); _t2831 = *_hp; free(_hp); }
                (void)_t2831;
                U64 _t2832 = 3;
                (void)_t2832;
                Array *_va41 = Array_new(_t2830, &(U64){_t2831}, &(U64){_t2832});
                (void)_va41;
                Str_delete(_t2830, &(Bool){1});
                ;
                ;
                U64 _t2833 = 0;
                (void)_t2833;
                Str *_t2834 = Str_lit(" \"", 3ULL);
                (void)_t2834;
                Array_set(_va41, &(U64){_t2833}, _t2834);
                ;
                U64 _t2835 = 1;
                (void)_t2835;
                Str *_t2836 = Str_clone(s);
                (void)_t2836;
                Str_delete(s, &(Bool){1});
                Array_set(_va41, &(U64){_t2835}, _t2836);
                ;
                U64 _t2837 = 2;
                (void)_t2837;
                Str *_t2838 = Str_lit("\"", 2ULL);
                (void)_t2838;
                Array_set(_va41, &(U64){_t2837}, _t2838);
                ;
                print(_va41);
            } else {
                Bool _t2905; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw2820); _t2905 = *_hp; free(_hp); }
                (void)_t2905;
                if (_t2905) {
                    Str *s = ExprData_get_LiteralNum(_sw2820);
                    (void)s;
                    Str *_t2839 = Str_lit("Str", 3ULL);
                    (void)_t2839;
                    U64 _t2840; { U64 *_hp = (U64 *)Str_size(); _t2840 = *_hp; free(_hp); }
                    (void)_t2840;
                    U64 _t2841 = 3;
                    (void)_t2841;
                    Array *_va42 = Array_new(_t2839, &(U64){_t2840}, &(U64){_t2841});
                    (void)_va42;
                    Str_delete(_t2839, &(Bool){1});
                    ;
                    ;
                    U64 _t2842 = 0;
                    (void)_t2842;
                    Str *_t2843 = Str_lit(" \"", 3ULL);
                    (void)_t2843;
                    Array_set(_va42, &(U64){_t2842}, _t2843);
                    ;
                    U64 _t2844 = 1;
                    (void)_t2844;
                    Str *_t2845 = Str_clone(s);
                    (void)_t2845;
                    Str_delete(s, &(Bool){1});
                    Array_set(_va42, &(U64){_t2844}, _t2845);
                    ;
                    U64 _t2846 = 2;
                    (void)_t2846;
                    Str *_t2847 = Str_lit("\"", 2ULL);
                    (void)_t2847;
                    Array_set(_va42, &(U64){_t2846}, _t2847);
                    ;
                    print(_va42);
                } else {
                    Bool _t2904; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw2820); _t2904 = *_hp; free(_hp); }
                    (void)_t2904;
                    if (_t2904) {
                        Str *s = ExprData_get_LiteralBool(_sw2820);
                        (void)s;
                        Str *_t2848 = Str_lit("Str", 3ULL);
                        (void)_t2848;
                        U64 _t2849; { U64 *_hp = (U64 *)Str_size(); _t2849 = *_hp; free(_hp); }
                        (void)_t2849;
                        U64 _t2850 = 3;
                        (void)_t2850;
                        Array *_va43 = Array_new(_t2848, &(U64){_t2849}, &(U64){_t2850});
                        (void)_va43;
                        Str_delete(_t2848, &(Bool){1});
                        ;
                        ;
                        U64 _t2851 = 0;
                        (void)_t2851;
                        Str *_t2852 = Str_lit(" \"", 3ULL);
                        (void)_t2852;
                        Array_set(_va43, &(U64){_t2851}, _t2852);
                        ;
                        U64 _t2853 = 1;
                        (void)_t2853;
                        Str *_t2854 = Str_clone(s);
                        (void)_t2854;
                        Str_delete(s, &(Bool){1});
                        Array_set(_va43, &(U64){_t2853}, _t2854);
                        ;
                        U64 _t2855 = 2;
                        (void)_t2855;
                        Str *_t2856 = Str_lit("\"", 2ULL);
                        (void)_t2856;
                        Array_set(_va43, &(U64){_t2855}, _t2856);
                        ;
                        print(_va43);
                    } else {
                        Bool _t2903; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw2820); _t2903 = *_hp; free(_hp); }
                        (void)_t2903;
                        if (_t2903) {
                            Str *s = ExprData_get_ForIn(_sw2820);
                            (void)s;
                            Str *_t2857 = Str_lit("Str", 3ULL);
                            (void)_t2857;
                            U64 _t2858; { U64 *_hp = (U64 *)Str_size(); _t2858 = *_hp; free(_hp); }
                            (void)_t2858;
                            U64 _t2859 = 3;
                            (void)_t2859;
                            Array *_va44 = Array_new(_t2857, &(U64){_t2858}, &(U64){_t2859});
                            (void)_va44;
                            Str_delete(_t2857, &(Bool){1});
                            ;
                            ;
                            U64 _t2860 = 0;
                            (void)_t2860;
                            Str *_t2861 = Str_lit(" \"", 3ULL);
                            (void)_t2861;
                            Array_set(_va44, &(U64){_t2860}, _t2861);
                            ;
                            U64 _t2862 = 1;
                            (void)_t2862;
                            Str *_t2863 = Str_clone(s);
                            (void)_t2863;
                            Str_delete(s, &(Bool){1});
                            Array_set(_va44, &(U64){_t2862}, _t2863);
                            ;
                            U64 _t2864 = 2;
                            (void)_t2864;
                            Str *_t2865 = Str_lit("\"", 2ULL);
                            (void)_t2865;
                            Array_set(_va44, &(U64){_t2864}, _t2865);
                            ;
                            print(_va44);
                        } else {
                            Bool _t2902; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw2820); _t2902 = *_hp; free(_hp); }
                            (void)_t2902;
                            if (_t2902) {
                                Declaration *decl = ExprData_get_Decl(_sw2820);
                                (void)decl;
                                if (decl->is_mut) {
                                    Str *_t2866 = Str_lit("Str", 3ULL);
                                    (void)_t2866;
                                    U64 _t2867; { U64 *_hp = (U64 *)Str_size(); _t2867 = *_hp; free(_hp); }
                                    (void)_t2867;
                                    U64 _t2868 = 1;
                                    (void)_t2868;
                                    Array *_va45 = Array_new(_t2866, &(U64){_t2867}, &(U64){_t2868});
                                    (void)_va45;
                                    Str_delete(_t2866, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t2869 = 0;
                                    (void)_t2869;
                                    Str *_t2870 = Str_lit(" mut", 4ULL);
                                    (void)_t2870;
                                    Array_set(_va45, &(U64){_t2869}, _t2870);
                                    ;
                                    print(_va45);
                                }
                                Str *_t2871 = Str_lit("Str", 3ULL);
                                (void)_t2871;
                                U64 _t2872; { U64 *_hp = (U64 *)Str_size(); _t2872 = *_hp; free(_hp); }
                                (void)_t2872;
                                U64 _t2873 = 2;
                                (void)_t2873;
                                Array *_va46 = Array_new(_t2871, &(U64){_t2872}, &(U64){_t2873});
                                (void)_va46;
                                Str_delete(_t2871, &(Bool){1});
                                ;
                                ;
                                U64 _t2874 = 0;
                                (void)_t2874;
                                Str *_t2875 = Str_lit(" ", 1ULL);
                                (void)_t2875;
                                Array_set(_va46, &(U64){_t2874}, _t2875);
                                ;
                                U64 _t2876 = 1;
                                (void)_t2876;
                                Str *_t2877 = Str_clone(&decl->name);
                                (void)_t2877;
                                Declaration_delete(decl, &(Bool){1});
                                Array_set(_va46, &(U64){_t2876}, _t2877);
                                ;
                                print(_va46);
                            } else {
                                Bool _t2901; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw2820); _t2901 = *_hp; free(_hp); }
                                (void)_t2901;
                                if (_t2901) {
                                    Str *s = ExprData_get_Assign(_sw2820);
                                    (void)s;
                                    Str *_t2878 = Str_lit("Str", 3ULL);
                                    (void)_t2878;
                                    U64 _t2879; { U64 *_hp = (U64 *)Str_size(); _t2879 = *_hp; free(_hp); }
                                    (void)_t2879;
                                    U64 _t2880 = 2;
                                    (void)_t2880;
                                    Array *_va47 = Array_new(_t2878, &(U64){_t2879}, &(U64){_t2880});
                                    (void)_va47;
                                    Str_delete(_t2878, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t2881 = 0;
                                    (void)_t2881;
                                    Str *_t2882 = Str_lit(" ", 1ULL);
                                    (void)_t2882;
                                    Array_set(_va47, &(U64){_t2881}, _t2882);
                                    ;
                                    U64 _t2883 = 1;
                                    (void)_t2883;
                                    Str *_t2884 = Str_clone(s);
                                    (void)_t2884;
                                    Str_delete(s, &(Bool){1});
                                    Array_set(_va47, &(U64){_t2883}, _t2884);
                                    ;
                                    print(_va47);
                                } else {
                                    Bool _t2900; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw2820); _t2900 = *_hp; free(_hp); }
                                    (void)_t2900;
                                    if (_t2900) {
                                        Str *s = ExprData_get_NamedArg(_sw2820);
                                        (void)s;
                                        Str *_t2885 = Str_lit("Str", 3ULL);
                                        (void)_t2885;
                                        U64 _t2886; { U64 *_hp = (U64 *)Str_size(); _t2886 = *_hp; free(_hp); }
                                        (void)_t2886;
                                        U64 _t2887 = 2;
                                        (void)_t2887;
                                        Array *_va48 = Array_new(_t2885, &(U64){_t2886}, &(U64){_t2887});
                                        (void)_va48;
                                        Str_delete(_t2885, &(Bool){1});
                                        ;
                                        ;
                                        U64 _t2888 = 0;
                                        (void)_t2888;
                                        Str *_t2889 = Str_lit(" ", 1ULL);
                                        (void)_t2889;
                                        Array_set(_va48, &(U64){_t2888}, _t2889);
                                        ;
                                        U64 _t2890 = 1;
                                        (void)_t2890;
                                        Str *_t2891 = Str_clone(s);
                                        (void)_t2891;
                                        Str_delete(s, &(Bool){1});
                                        Array_set(_va48, &(U64){_t2890}, _t2891);
                                        ;
                                        print(_va48);
                                    } else {
                                        Bool _t2899; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw2820); _t2899 = *_hp; free(_hp); }
                                        (void)_t2899;
                                        if (_t2899) {
                                            FunctionDef *fdef = ExprData_get_FuncDef(_sw2820);
                                            (void)fdef;
                                            Str *_t2892 = Str_lit("Str", 3ULL);
                                            (void)_t2892;
                                            U64 _t2893; { U64 *_hp = (U64 *)Str_size(); _t2893 = *_hp; free(_hp); }
                                            (void)_t2893;
                                            U64 _t2894 = 2;
                                            (void)_t2894;
                                            Array *_va49 = Array_new(_t2892, &(U64){_t2893}, &(U64){_t2894});
                                            (void)_va49;
                                            Str_delete(_t2892, &(Bool){1});
                                            ;
                                            ;
                                            U64 _t2895 = 0;
                                            (void)_t2895;
                                            Str *_t2896 = Str_lit(" ", 1ULL);
                                            (void)_t2896;
                                            Array_set(_va49, &(U64){_t2895}, _t2896);
                                            ;
                                            U64 _t2897 = 1;
                                            (void)_t2897;
                                            Str *_t2898 = func_type_name(&fdef->func_type);
                                            (void)_t2898;
                                            FunctionDef_delete(fdef, &(Bool){1});
                                            Array_set(_va49, &(U64){_t2897}, _t2898);
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
        ExprData_delete(_sw2820, &(Bool){1});
        ;
    }
    U64 _t2955; { U64 *_hp = (U64 *)Vec_len(&e->children); _t2955 = *_hp; free(_hp); }
    (void)_t2955;
    U64 _t2956 = 0;
    (void)_t2956;
    Bool _t2957; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2955}, &(U64){_t2956}); _t2957 = *_hp; free(_hp); }
    (void)_t2957;
    ;
    ;
    if (_t2957) {
        Str *_t2941 = Str_lit("Str", 3ULL);
        (void)_t2941;
        U64 _t2942; { U64 *_hp = (U64 *)Str_size(); _t2942 = *_hp; free(_hp); }
        (void)_t2942;
        U64 _t2943 = 1;
        (void)_t2943;
        Array *_va51 = Array_new(_t2941, &(U64){_t2942}, &(U64){_t2943});
        (void)_va51;
        Str_delete(_t2941, &(Bool){1});
        ;
        ;
        U64 _t2944 = 0;
        (void)_t2944;
        Str *_t2945 = Str_lit("", 0ULL);
        (void)_t2945;
        Array_set(_va51, &(U64){_t2944}, _t2945);
        ;
        println(_va51);
        {
            U64 _fi2908 = 0;
            (void)_fi2908;
            while (1) {
                U64 _t2910 = 0;
                (void)_t2910;
                U64 _t2911; { U64 *_hp = (U64 *)Vec_len(&e->children); _t2911 = *_hp; free(_hp); }
                (void)_t2911;
                Range *_t2912 = Range_new(_t2910, _t2911);
                (void)_t2912;
                ;
                ;
                U64 _t2913; { U64 *_hp = (U64 *)Range_len(_t2912); _t2913 = *_hp; free(_hp); }
                (void)_t2913;
                Range_delete(_t2912, &(Bool){1});
                Bool _wcond2909; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2908}, &(U64){_t2913}); _wcond2909 = *_hp; free(_hp); }
                (void)_wcond2909;
                ;
                if (_wcond2909) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t2914 = 0;
                (void)_t2914;
                U64 _t2915; { U64 *_hp = (U64 *)Vec_len(&e->children); _t2915 = *_hp; free(_hp); }
                (void)_t2915;
                Range *_t2916 = Range_new(_t2914, _t2915);
                (void)_t2916;
                ;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t2916, _fi2908); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t2916, &(Bool){1});
                U64 _t2917 = 1;
                (void)_t2917;
                U64 _t2918 = U64_add(_fi2908, _t2917);
                (void)_t2918;
                ;
                _fi2908 = _t2918;
                ;
                I64 *_t2919 = malloc(sizeof(I64)); *_t2919 = U64_to_i64(i);
                (void)_t2919;
                ;
                U32 _t2920 = 1;
                (void)_t2920;
                Expr *_t2921 = Expr_child(e, _t2919);
                (void)_t2921;
                U32 _t2922 = U32_add(indent, _t2920);
                (void)_t2922;
                ;
                ast_print(_t2921, _t2922);
                I64_delete(_t2919, &(Bool){1});
                ;
            }
            ;
        }
        {
            U64 _fi2923 = 0;
            (void)_fi2923;
            while (1) {
                I64 _t2925 = U32_to_i64(indent);
                (void)_t2925;
                U64 _t2926 = 0;
                (void)_t2926;
                U64 _t2927 = I64_to_u64(_t2925);
                (void)_t2927;
                ;
                Range *_t2928 = Range_new(_t2926, _t2927);
                (void)_t2928;
                ;
                ;
                U64 _t2929; { U64 *_hp = (U64 *)Range_len(_t2928); _t2929 = *_hp; free(_hp); }
                (void)_t2929;
                Range_delete(_t2928, &(Bool){1});
                Bool _wcond2924; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2923}, &(U64){_t2929}); _wcond2924 = *_hp; free(_hp); }
                (void)_wcond2924;
                ;
                if (_wcond2924) {
                } else {
                    ;
                    break;
                }
                ;
                I64 _t2930 = U32_to_i64(indent);
                (void)_t2930;
                U64 _t2931 = 0;
                (void)_t2931;
                U64 _t2932 = I64_to_u64(_t2930);
                (void)_t2932;
                ;
                Range *_t2933 = Range_new(_t2931, _t2932);
                (void)_t2933;
                ;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t2933, _fi2923); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t2933, &(Bool){1});
                ;
                U64 _t2934 = 1;
                (void)_t2934;
                U64 _t2935 = U64_add(_fi2923, _t2934);
                (void)_t2935;
                ;
                _fi2923 = _t2935;
                ;
                Str *_t2936 = Str_lit("Str", 3ULL);
                (void)_t2936;
                U64 _t2937; { U64 *_hp = (U64 *)Str_size(); _t2937 = *_hp; free(_hp); }
                (void)_t2937;
                U64 _t2938 = 1;
                (void)_t2938;
                Array *_va50 = Array_new(_t2936, &(U64){_t2937}, &(U64){_t2938});
                (void)_va50;
                Str_delete(_t2936, &(Bool){1});
                ;
                ;
                U64 _t2939 = 0;
                (void)_t2939;
                Str *_t2940 = Str_lit("  ", 2ULL);
                (void)_t2940;
                Array_set(_va50, &(U64){_t2939}, _t2940);
                ;
                print(_va50);
            }
            ;
        }
    }
    ;
    Str *_t2958 = Str_lit("Str", 3ULL);
    (void)_t2958;
    U64 _t2959; { U64 *_hp = (U64 *)Str_size(); _t2959 = *_hp; free(_hp); }
    (void)_t2959;
    U64 _t2960 = 1;
    (void)_t2960;
    Array *_va53 = Array_new(_t2958, &(U64){_t2959}, &(U64){_t2960});
    (void)_va53;
    Str_delete(_t2958, &(Bool){1});
    ;
    ;
    U64 _t2961 = 0;
    (void)_t2961;
    Str *_t2962 = Str_lit(")", 1ULL);
    (void)_t2962;
    Array_set(_va53, &(U64){_t2961}, _t2962);
    ;
    println(_va53);
}

Bool * enum_has_payloads(Expr * enum_def) {
    (void)enum_def;
    I64 *_t2984 = malloc(sizeof(I64));
    *_t2984 = 0;
    (void)_t2984;
    Expr *body = Expr_child(enum_def, _t2984);
    (void)body;
    {
        U64 _fi2963 = 0;
        (void)_fi2963;
        while (1) {
            I64 _t2971; { I64 *_hp = (I64 *)Expr_child_count(body); _t2971 = *_hp; free(_hp); }
            (void)_t2971;
            U64 _t2972 = 0;
            (void)_t2972;
            U64 _t2973 = I64_to_u64(_t2971);
            (void)_t2973;
            ;
            Range *_t2974 = Range_new(_t2972, _t2973);
            (void)_t2974;
            ;
            ;
            U64 _t2975; { U64 *_hp = (U64 *)Range_len(_t2974); _t2975 = *_hp; free(_hp); }
            (void)_t2975;
            Range_delete(_t2974, &(Bool){1});
            Bool _wcond2964; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2963}, &(U64){_t2975}); _wcond2964 = *_hp; free(_hp); }
            (void)_wcond2964;
            ;
            if (_wcond2964) {
            } else {
                ;
                break;
            }
            ;
            I64 _t2976; { I64 *_hp = (I64 *)Expr_child_count(body); _t2976 = *_hp; free(_hp); }
            (void)_t2976;
            U64 _t2977 = 0;
            (void)_t2977;
            U64 _t2978 = I64_to_u64(_t2976);
            (void)_t2978;
            ;
            Range *_t2979 = Range_new(_t2977, _t2978);
            (void)_t2979;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t2979, _fi2963); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t2979, &(Bool){1});
            U64 _t2980 = 1;
            (void)_t2980;
            U64 _t2981 = U64_add(_fi2963, _t2980);
            (void)_t2981;
            ;
            _fi2963 = _t2981;
            ;
            I64 *_t2982 = malloc(sizeof(I64)); *_t2982 = U64_to_i64(i);
            (void)_t2982;
            ;
            Expr *f = Expr_child(body, _t2982);
            (void)f;
            Bool _t2983; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2983 = *_hp; free(_hp); }
            (void)_t2983;
            if (_t2983) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                U64 _t2966; { U64 *_hp = (U64 *)Str_len(&decl->explicit_type); _t2966 = *_hp; free(_hp); }
                (void)_t2966;
                U64 _t2967 = 0;
                (void)_t2967;
                Bool _t2968 = Bool_not(decl->is_namespace);
                (void)_t2968;
                Declaration_delete(decl, &(Bool){1});
                Bool _t2969; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2966}, &(U64){_t2967}); _t2969 = *_hp; free(_hp); }
                (void)_t2969;
                ;
                ;
                Bool _t2970 = Bool_and(_t2968, _t2969);
                (void)_t2970;
                ;
                ;
                if (_t2970) {
                    Bool _t2965 = 1;
                    (void)_t2965;
                    ;
                    I64_delete(_t2982, &(Bool){1});
                    ;
                    ;
                    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2965; return _r; }
                }
                ;
            }
            I64_delete(_t2982, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t2984, &(Bool){1});
    Bool _t2985 = 0;
    (void)_t2985;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2985; return _r; }
}

I32 * enum_variant_tag(Expr * enum_def, Str * variant_name) {
    (void)enum_def;
    (void)variant_name;
    I64 *_t3005 = malloc(sizeof(I64));
    *_t3005 = 0;
    (void)_t3005;
    Expr *body = Expr_child(enum_def, _t3005);
    (void)body;
    I32 tag = 0;
    (void)tag;
    {
        U64 _fi2986 = 0;
        (void)_fi2986;
        while (1) {
            I64 _t2992; { I64 *_hp = (I64 *)Expr_child_count(body); _t2992 = *_hp; free(_hp); }
            (void)_t2992;
            U64 _t2993 = 0;
            (void)_t2993;
            U64 _t2994 = I64_to_u64(_t2992);
            (void)_t2994;
            ;
            Range *_t2995 = Range_new(_t2993, _t2994);
            (void)_t2995;
            ;
            ;
            U64 _t2996; { U64 *_hp = (U64 *)Range_len(_t2995); _t2996 = *_hp; free(_hp); }
            (void)_t2996;
            Range_delete(_t2995, &(Bool){1});
            Bool _wcond2987; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2986}, &(U64){_t2996}); _wcond2987 = *_hp; free(_hp); }
            (void)_wcond2987;
            ;
            if (_wcond2987) {
            } else {
                ;
                break;
            }
            ;
            I64 _t2997; { I64 *_hp = (I64 *)Expr_child_count(body); _t2997 = *_hp; free(_hp); }
            (void)_t2997;
            U64 _t2998 = 0;
            (void)_t2998;
            U64 _t2999 = I64_to_u64(_t2997);
            (void)_t2999;
            ;
            Range *_t3000 = Range_new(_t2998, _t2999);
            (void)_t3000;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t3000, _fi2986); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t3000, &(Bool){1});
            U64 _t3001 = 1;
            (void)_t3001;
            U64 _t3002 = U64_add(_fi2986, _t3001);
            (void)_t3002;
            ;
            _fi2986 = _t3002;
            ;
            I64 *_t3003 = malloc(sizeof(I64)); *_t3003 = U64_to_i64(i);
            (void)_t3003;
            ;
            Expr *f = Expr_child(body, _t3003);
            (void)f;
            Bool _t3004; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t3004 = *_hp; free(_hp); }
            (void)_t3004;
            if (_t3004) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t2991 = Bool_not(decl->is_namespace);
                (void)_t2991;
                if (_t2991) {
                    Bool _t2988; { Bool *_hp = (Bool *)Str_eq(&decl->name, variant_name); _t2988 = *_hp; free(_hp); }
                    (void)_t2988;
                    if (_t2988) {
                        ;
                        ;
                        Declaration_delete(decl, &(Bool){1});
                        I64_delete(_t3003, &(Bool){1});
                        ;
                        ;
                        { I32 *_r = malloc(sizeof(I32)); *_r = tag; return _r; }
                    }
                    ;
                    I32 _t2989 = 1;
                    (void)_t2989;
                    I32 _t2990 = I32_add(tag, _t2989);
                    (void)_t2990;
                    ;
                    tag = _t2990;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t3003, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t3005, &(Bool){1});
    ;
    I64 _t3006 = 0;
    (void)_t3006;
    I64 _t3007 = 1;
    (void)_t3007;
    I64 _t3008 = I64_sub(_t3006, _t3007);
    (void)_t3008;
    ;
    ;
    I32 _t3009 = I64_to_i32(_t3008);
    (void)_t3009;
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t3009; return _r; }
}

Str * enum_variant_type(Expr * enum_def, I32 tag) {
    (void)enum_def;
    (void)tag;
    I64 *_t3029 = malloc(sizeof(I64));
    *_t3029 = 0;
    (void)_t3029;
    Expr *body = Expr_child(enum_def, _t3029);
    (void)body;
    I32 idx = 0;
    (void)idx;
    {
        U64 _fi3010 = 0;
        (void)_fi3010;
        while (1) {
            I64 _t3016; { I64 *_hp = (I64 *)Expr_child_count(body); _t3016 = *_hp; free(_hp); }
            (void)_t3016;
            U64 _t3017 = 0;
            (void)_t3017;
            U64 _t3018 = I64_to_u64(_t3016);
            (void)_t3018;
            ;
            Range *_t3019 = Range_new(_t3017, _t3018);
            (void)_t3019;
            ;
            ;
            U64 _t3020; { U64 *_hp = (U64 *)Range_len(_t3019); _t3020 = *_hp; free(_hp); }
            (void)_t3020;
            Range_delete(_t3019, &(Bool){1});
            Bool _wcond3011; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3010}, &(U64){_t3020}); _wcond3011 = *_hp; free(_hp); }
            (void)_wcond3011;
            ;
            if (_wcond3011) {
            } else {
                ;
                break;
            }
            ;
            I64 _t3021; { I64 *_hp = (I64 *)Expr_child_count(body); _t3021 = *_hp; free(_hp); }
            (void)_t3021;
            U64 _t3022 = 0;
            (void)_t3022;
            U64 _t3023 = I64_to_u64(_t3021);
            (void)_t3023;
            ;
            Range *_t3024 = Range_new(_t3022, _t3023);
            (void)_t3024;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t3024, _fi3010); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t3024, &(Bool){1});
            U64 _t3025 = 1;
            (void)_t3025;
            U64 _t3026 = U64_add(_fi3010, _t3025);
            (void)_t3026;
            ;
            _fi3010 = _t3026;
            ;
            I64 *_t3027 = malloc(sizeof(I64)); *_t3027 = U64_to_i64(i);
            (void)_t3027;
            ;
            Expr *f = Expr_child(body, _t3027);
            (void)f;
            Bool _t3028; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t3028 = *_hp; free(_hp); }
            (void)_t3028;
            if (_t3028) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t3015 = Bool_not(decl->is_namespace);
                (void)_t3015;
                if (_t3015) {
                    Bool _t3012 = I32_eq(idx, tag);
                    (void)_t3012;
                    if (_t3012) {
                        ;
                        ;
                        I64_delete(_t3027, &(Bool){1});
                        ;
                        ;
                        { Str *_r = malloc(sizeof(Str)); *_r = decl->explicit_type; return _r; }
                    }
                    ;
                    I32 _t3013 = 1;
                    (void)_t3013;
                    I32 _t3014 = I32_add(idx, _t3013);
                    (void)_t3014;
                    ;
                    idx = _t3014;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t3027, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t3029, &(Bool){1});
    ;
    Str *_t3030 = Str_lit("", 0ULL);
    (void)_t3030;
    return _t3030;
}

