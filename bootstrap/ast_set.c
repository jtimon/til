Set * Set_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    Bool _t654; { Bool *_hp = (Bool *)Str_is_empty(elem_type); _t654 = *_hp; free(_hp); }
    (void)_t654;
    Bool _t655 = Bool_not(_t654);
    (void)_t655;
    ;
    if (_t655) {
        Bool _t652 = dyn_has_cmp(elem_type);
        (void)_t652;
        Bool _t653 = Bool_not(_t652);
        (void)_t653;
        ;
        if (_t653) {
            Str *_t642 = Str_lit("Str", 3ULL);
            (void)_t642;
            U64 _t643; { U64 *_hp = (U64 *)Str_size(); _t643 = *_hp; free(_hp); }
            (void)_t643;
            U64 _t644 = 3;
            (void)_t644;
            Array *_va11 = Array_new(_t642, &(U64){_t643}, &(U64){_t644});
            (void)_va11;
            Str_delete(_t642, &(Bool){1});
            ;
            ;
            U64 _t645 = 0;
            (void)_t645;
            Str *_t646 = Str_lit("Set.new: type ", 14ULL);
            (void)_t646;
            Array_set(_va11, &(U64){_t645}, _t646);
            ;
            U64 _t647 = 1;
            (void)_t647;
            Str *_t648 = Str_clone(elem_type);
            (void)_t648;
            Array_set(_va11, &(U64){_t647}, _t648);
            ;
            U64 _t649 = 2;
            (void)_t649;
            Str *_t650 = Str_lit(" must implement cmp", 19ULL);
            (void)_t650;
            Array_set(_va11, &(U64){_t649}, _t650);
            ;
            Str *_t651 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/set.til:14:23", 60ULL);
            (void)_t651;
            panic(_t651, _va11);
            Str_delete(_t651, &(Bool){1});
        }
        ;
    }
    ;
    void *_t656 = malloc(DEREF(elem_size));
    (void)_t656;
    U64 _t657 = 0;
    (void)_t657;
    I64 _t658 = 1;
    (void)_t658;
    U64 _t659 = U64_clone(elem_size);
    (void)_t659;
    Set *_t660 = malloc(sizeof(Set));
    _t660->data = _t656;
    _t660->count = _t657;
    _t660->cap = _t658;
    _t660->elem_size = _t659;
    { Str *_ca = Str_clone(elem_type); _t660->elem_type = *_ca; free(_ca); }
    (void)_t660;
    ;
    ;
    ;
    return _t660;
}

U64 * Set_len(Set * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

Bool * Set_has(Set * self, void * val) {
    (void)self;
    (void)val;
    U64 lo = 0;
    (void)lo;
    U64 hi = self->count;
    (void)hi;
    while (1) {
        Bool _wcond661; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond661 = *_hp; free(_hp); }
        (void)_wcond661;
        if (_wcond661) {
        } else {
            ;
            break;
        }
        ;
        U64 _t668 = U64_sub(hi, lo);
        (void)_t668;
        U64 _t669 = 2;
        (void)_t669;
        U64 _t670 = U64_div(_t668, _t669);
        (void)_t670;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t670);
        (void)mid;
        ;
        U64 *_t671 = malloc(sizeof(U64)); *_t671 = U64_mul(DEREF(mid), self->elem_size);
        (void)_t671;
        void *_t672 = ptr_add(self->data, DEREF(_t671));
        (void)_t672;
        I64 *c = dyn_call_cmp(&self->elem_type, _t672, val);
        (void)c;
        U64_delete(_t671, &(Bool){1});
        I64 _t673 = 0;
        (void)_t673;
        Bool _t674; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t673}); _t674 = *_hp; free(_hp); }
        (void)_t674;
        ;
        if (_t674) {
            U64 _t662 = 1;
            (void)_t662;
            U64 _t663 = U64_add(DEREF(mid), _t662);
            (void)_t663;
            ;
            lo = _t663;
            ;
        } else {
            I64 _t666 = 0;
            (void)_t666;
            Bool _t667; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t666}); _t667 = *_hp; free(_hp); }
            (void)_t667;
            ;
            if (_t667) {
                U64 _t664 = U64_clone(mid);
                (void)_t664;
                hi = _t664;
                ;
            } else {
                Bool _t665 = 1;
                (void)_t665;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t665; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t675 = 0;
    (void)_t675;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t675; return _r; }
}

void Set_add(Set * self, void * val) {
    (void)self;
    (void)val;
    U64 lo = 0;
    (void)lo;
    U64 hi = self->count;
    (void)hi;
    Bool found = 0;
    (void)found;
    while (1) {
        Bool _wcond676; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond676 = *_hp; free(_hp); }
        (void)_wcond676;
        if (_wcond676) {
        } else {
            ;
            break;
        }
        ;
        U64 _t685 = U64_sub(hi, lo);
        (void)_t685;
        U64 _t686 = 2;
        (void)_t686;
        U64 _t687 = U64_div(_t685, _t686);
        (void)_t687;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t687);
        (void)mid;
        ;
        U64 *_t688 = malloc(sizeof(U64)); *_t688 = U64_mul(DEREF(mid), self->elem_size);
        (void)_t688;
        void *_t689 = ptr_add(self->data, DEREF(_t688));
        (void)_t689;
        I64 *c = dyn_call_cmp(&self->elem_type, _t689, val);
        (void)c;
        U64_delete(_t688, &(Bool){1});
        I64 _t690 = 0;
        (void)_t690;
        Bool _t691; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t690}); _t691 = *_hp; free(_hp); }
        (void)_t691;
        ;
        if (_t691) {
            U64 _t677 = 1;
            (void)_t677;
            U64 _t678 = U64_add(DEREF(mid), _t677);
            (void)_t678;
            ;
            lo = _t678;
            ;
        } else {
            I64 _t683 = 0;
            (void)_t683;
            Bool _t684; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t683}); _t684 = *_hp; free(_hp); }
            (void)_t684;
            ;
            if (_t684) {
                U64 _t679 = U64_clone(mid);
                (void)_t679;
                hi = _t679;
                ;
            } else {
                Bool _t680 = 1;
                (void)_t680;
                found = _t680;
                ;
                U64 _t681 = U64_clone(mid);
                (void)_t681;
                lo = _t681;
                ;
                U64 _t682 = U64_clone(mid);
                (void)_t682;
                hi = _t682;
                ;
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    if (found) {
        Bool _t693; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t693 = *_hp; free(_hp); }
        (void)_t693;
        Bool _t694 = Bool_not(_t693);
        (void)_t694;
        ;
        if (_t694) {
            Bool _t692 = 0;
            (void)_t692;
            dyn_call_delete(&self->elem_type, val, &(Bool){_t692});
            ;
        }
        ;
        free(val);
    } else {
        Bool _t699 = U64_eq(self->count, self->cap);
        (void)_t699;
        if (_t699) {
            U64 _t695 = 2;
            (void)_t695;
            U64 new_cap = U64_mul(self->cap, _t695);
            (void)new_cap;
            ;
            U64 _t696 = U64_mul(new_cap, self->elem_size);
            (void)_t696;
            void *_t697 = realloc(self->data, _t696);
            (void)_t697;
            ;
            self->data = _t697;
            U64 _t698 = U64_clone(&(U64){new_cap});
            (void)_t698;
            ;
            self->cap = _t698;
            ;
        }
        ;
        U64 _t700 = 1;
        (void)_t700;
        U64 _t701 = U64_add(lo, _t700);
        (void)_t701;
        ;
        U64 *_t702 = malloc(sizeof(U64)); *_t702 = U64_mul(_t701, self->elem_size);
        (void)_t702;
        ;
        U64 *_t703 = malloc(sizeof(U64)); *_t703 = U64_mul(lo, self->elem_size);
        (void)_t703;
        U64 _t704 = U64_sub(self->count, lo);
        (void)_t704;
        void *_t705 = ptr_add(self->data, DEREF(_t702));
        (void)_t705;
        void *_t706 = ptr_add(self->data, DEREF(_t703));
        (void)_t706;
        U64 _t707 = U64_mul(_t704, self->elem_size);
        (void)_t707;
        ;
        memmove(_t705, _t706, _t707);
        U64_delete(_t702, &(Bool){1});
        U64_delete(_t703, &(Bool){1});
        ;
        U64 *_t708 = malloc(sizeof(U64)); *_t708 = U64_mul(lo, self->elem_size);
        (void)_t708;
        void *_t709 = ptr_add(self->data, DEREF(_t708));
        (void)_t709;
        memcpy(_t709, val, self->elem_size);
        U64_delete(_t708, &(Bool){1});
        free(val);
        U64 _t710 = 1;
        (void)_t710;
        U64 _t711 = U64_add(self->count, _t710);
        (void)_t711;
        ;
        self->count = _t711;
        ;
    }
    ;
    ;
}

void Set_delete(Set * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t725; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t725 = *_hp; free(_hp); }
    (void)_t725;
    Bool _t726 = Bool_not(_t725);
    (void)_t726;
    ;
    if (_t726) {
        {
            U64 _fi712 = 0;
            (void)_fi712;
            while (1) {
                U64 _t714 = 0;
                (void)_t714;
                Range *_t715 = Range_new(_t714, self->count);
                (void)_t715;
                ;
                U64 _t716; { U64 *_hp = (U64 *)Range_len(_t715); _t716 = *_hp; free(_hp); }
                (void)_t716;
                Range_delete(_t715, &(Bool){1});
                Bool _wcond713; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi712}, &(U64){_t716}); _wcond713 = *_hp; free(_hp); }
                (void)_wcond713;
                ;
                if (_wcond713) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t717 = 0;
                (void)_t717;
                Range *_t718 = Range_new(_t717, self->count);
                (void)_t718;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t718, _fi712); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t718, &(Bool){1});
                U64 _t719 = 1;
                (void)_t719;
                U64 _t720 = U64_add(_fi712, _t719);
                (void)_t720;
                ;
                _fi712 = _t720;
                ;
                U64 *_t721 = malloc(sizeof(U64)); *_t721 = U64_mul(i, self->elem_size);
                (void)_t721;
                ;
                void *_t722 = ptr_add(self->data, DEREF(_t721));
                (void)_t722;
                Bool _t723 = 0;
                (void)_t723;
                dyn_call_delete(&self->elem_type, _t722, &(Bool){_t723});
                U64_delete(_t721, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t727; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t727 = *_hp; free(_hp); }
    (void)_t727;
    Bool _t728 = Bool_not(_t727);
    (void)_t728;
    ;
    if (_t728) {
        Bool _t724 = 0;
        (void)_t724;
        Str_delete(&self->elem_type, &(Bool){_t724});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Set * Set_clone(Set * self) {
    (void)self;
    U64 _t742 = U64_mul(self->cap, self->elem_size);
    (void)_t742;
    U8 *new_data = malloc(_t742);
    (void)new_data;
    ;
    {
        U64 _fi729 = 0;
        (void)_fi729;
        while (1) {
            U64 _t731 = 0;
            (void)_t731;
            Range *_t732 = Range_new(_t731, self->count);
            (void)_t732;
            ;
            U64 _t733; { U64 *_hp = (U64 *)Range_len(_t732); _t733 = *_hp; free(_hp); }
            (void)_t733;
            Range_delete(_t732, &(Bool){1});
            Bool _wcond730; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi729}, &(U64){_t733}); _wcond730 = *_hp; free(_hp); }
            (void)_wcond730;
            ;
            if (_wcond730) {
            } else {
                ;
                break;
            }
            ;
            U64 _t734 = 0;
            (void)_t734;
            Range *_t735 = Range_new(_t734, self->count);
            (void)_t735;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t735, _fi729); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t735, &(Bool){1});
            U64 _t736 = 1;
            (void)_t736;
            U64 _t737 = U64_add(_fi729, _t736);
            (void)_t737;
            ;
            _fi729 = _t737;
            ;
            U64 *_t738 = malloc(sizeof(U64)); *_t738 = U64_mul(i, self->elem_size);
            (void)_t738;
            void *_t739 = ptr_add(self->data, DEREF(_t738));
            (void)_t739;
            void *cloned = dyn_call_clone(&self->elem_type, _t739);
            (void)cloned;
            U64_delete(_t738, &(Bool){1});
            U64 *_t740 = malloc(sizeof(U64)); *_t740 = U64_mul(i, self->elem_size);
            (void)_t740;
            ;
            void *_t741 = ptr_add(new_data, DEREF(_t740));
            (void)_t741;
            memcpy(_t741, cloned, self->elem_size);
            U64_delete(_t740, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Set *_t743 = malloc(sizeof(Set));
    _t743->data = new_data;
    _t743->count = self->count;
    _t743->cap = self->cap;
    _t743->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t743->elem_type = *_ca; free(_ca); }
    (void)_t743;
    return _t743;
}

U64 *Set_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Set);
    return r;
}

