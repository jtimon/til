U64 * Str_len(Str * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

U8 * Str_get(Str * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t751; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t751 = *_hp; free(_hp); }
    (void)_t751;
    if (_t751) {
        Str *_t745 = Str_lit("Str", 3ULL);
        (void)_t745;
        U64 _t746; { U64 *_hp = (U64 *)Str_size(); _t746 = *_hp; free(_hp); }
        (void)_t746;
        U64 _t747 = 1;
        (void)_t747;
        Array *_va12 = Array_new(_t745, &(U64){_t746}, &(U64){_t747});
        (void)_va12;
        Str_delete(_t745, &(Bool){1});
        ;
        ;
        U64 _t748 = 0;
        (void)_t748;
        Str *_t749 = Str_lit("Str.get: index out of bounds", 28ULL);
        (void)_t749;
        Array_set(_va12, &(U64){_t748}, _t749);
        ;
        Str *_t750 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:16:19", 60ULL);
        (void)_t750;
        panic(_t750, _va12);
        Str_delete(_t750, &(Bool){1});
    }
    ;
    void *_t752 = ptr_add(self->c_str, DEREF(i));
    (void)_t752;
    return _t752;
}

U8 * Str_byte_at(Str * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t753 = ptr_add(self->c_str, DEREF(i));
    (void)_t753;
    return _t753;
}

I64 * Str_cmp(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 min_len = a->count;
    (void)min_len;
    Bool _t765; { Bool *_hp = (Bool *)U64_lt(&b->count, &a->count); _t765 = *_hp; free(_hp); }
    (void)_t765;
    if (_t765) {
        min_len = b->count;
    }
    ;
    {
        U64 _fi754 = 0;
        (void)_fi754;
        while (1) {
            U64 _t756 = 0;
            (void)_t756;
            Range *_t757 = Range_new(_t756, min_len);
            (void)_t757;
            ;
            U64 _t758; { U64 *_hp = (U64 *)Range_len(_t757); _t758 = *_hp; free(_hp); }
            (void)_t758;
            Range_delete(_t757, &(Bool){1});
            Bool _wcond755; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi754}, &(U64){_t758}); _wcond755 = *_hp; free(_hp); }
            (void)_wcond755;
            ;
            if (_wcond755) {
            } else {
                ;
                break;
            }
            ;
            U64 _t759 = 0;
            (void)_t759;
            Range *_t760 = Range_new(_t759, min_len);
            (void)_t760;
            ;
            U64 *i = Range_get(_t760, _fi754);
            (void)i;
            Range_delete(_t760, &(Bool){1});
            U64 _t761 = 1;
            (void)_t761;
            U64 _t762 = U64_add(_fi754, _t761);
            (void)_t762;
            ;
            _fi754 = _t762;
            ;
            U8 *ab = Str_get(a, i);
            (void)ab;
            U8 *bb = Str_get(b, i);
            (void)bb;
            I64 *c = malloc(sizeof(I64)); *c = U8_cmp(DEREF(ab), DEREF(bb));
            (void)c;
            U64_delete(i, &(Bool){1});
            I64 _t763 = 0;
            (void)_t763;
            Bool _t764; { Bool *_hp = (Bool *)I64_neq(c, &(I64){_t763}); _t764 = *_hp; free(_hp); }
            (void)_t764;
            ;
            if (_t764) {
                ;
                ;
                return c;
            }
            ;
            I64_delete(c, &(Bool){1});
        }
        ;
    }
    ;
    I64 _t766 = U64_cmp(a->count, b->count);
    (void)_t766;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t766; return _r; }
}

Str * Str_concat(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(a->count, b->count);
    (void)new_len;
    U64 _t767 = 1;
    (void)_t767;
    U64 _t768 = U64_add(DEREF(new_len), _t767);
    (void)_t768;
    ;
    U8 *new_data = malloc(_t768);
    (void)new_data;
    ;
    memcpy(new_data, a->c_str, a->count);
    void *_t769 = ptr_add(new_data, a->count);
    (void)_t769;
    memcpy(_t769, b->c_str, b->count);
    void *_t770 = ptr_add(new_data, DEREF(new_len));
    (void)_t770;
    I32 _t771 = 0;
    (void)_t771;
    U64 _t772 = 1;
    (void)_t772;
    memset(_t770, _t771, _t772);
    ;
    ;
    U64 _t773 = U64_clone(new_len);
    (void)_t773;
    U64 _t774 = U64_clone(new_len);
    (void)_t774;
    U64_delete(new_len, &(Bool){1});
    Str *_t775 = malloc(sizeof(Str));
    _t775->c_str = new_data;
    _t775->count = _t773;
    _t775->cap = _t774;
    (void)_t775;
    ;
    ;
    return _t775;
}

Str * Str_with_capacity(U64 * n) {
    (void)n;
    U64 _t776 = 1;
    (void)_t776;
    U64 _t777 = U64_add(DEREF(n), _t776);
    (void)_t777;
    ;
    U8 *buf = malloc(_t777);
    (void)buf;
    ;
    I32 _t778 = 0;
    (void)_t778;
    U64 _t779 = 1;
    (void)_t779;
    memset(buf, _t778, _t779);
    ;
    ;
    I64 _t780 = 0;
    (void)_t780;
    U64 _t781 = U64_clone(n);
    (void)_t781;
    Str *_t782 = malloc(sizeof(Str));
    _t782->c_str = buf;
    _t782->count = _t780;
    _t782->cap = _t781;
    (void)_t782;
    ;
    ;
    return _t782;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    (void)s;
    Bool _t795; { Bool *_hp = (Bool *)U64_gte(&self->cap, CAP_VIEW); _t795 = *_hp; free(_hp); }
    (void)_t795;
    if (_t795) {
        Str *_t783 = Str_lit("Str", 3ULL);
        (void)_t783;
        U64 _t784; { U64 *_hp = (U64 *)Str_size(); _t784 = *_hp; free(_hp); }
        (void)_t784;
        U64 _t785 = 1;
        (void)_t785;
        Array *_va13 = Array_new(_t783, &(U64){_t784}, &(U64){_t785});
        (void)_va13;
        Str_delete(_t783, &(Bool){1});
        ;
        ;
        U64 _t786 = 0;
        (void)_t786;
        Str *_t787 = Str_lit("Str.push_str: cannot mutate a string view or literal", 52ULL);
        (void)_t787;
        Array_set(_va13, &(U64){_t786}, _t787);
        ;
        Str *_t788 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:55:19", 60ULL);
        (void)_t788;
        panic(_t788, _va13);
        Str_delete(_t788, &(Bool){1});
    }
    ;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(self->count, s->count);
    (void)new_len;
    Bool _t796; { Bool *_hp = (Bool *)U64_gt(new_len, &self->cap); _t796 = *_hp; free(_hp); }
    (void)_t796;
    if (_t796) {
        Str *_t789 = Str_lit("Str", 3ULL);
        (void)_t789;
        U64 _t790; { U64 *_hp = (U64 *)Str_size(); _t790 = *_hp; free(_hp); }
        (void)_t790;
        U64 _t791 = 1;
        (void)_t791;
        Array *_va14 = Array_new(_t789, &(U64){_t790}, &(U64){_t791});
        (void)_va14;
        Str_delete(_t789, &(Bool){1});
        ;
        ;
        U64 _t792 = 0;
        (void)_t792;
        Str *_t793 = Str_lit("Str.push_str: capacity exceeded", 31ULL);
        (void)_t793;
        Array_set(_va14, &(U64){_t792}, _t793);
        ;
        Str *_t794 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:59:19", 60ULL);
        (void)_t794;
        panic(_t794, _va14);
        Str_delete(_t794, &(Bool){1});
    }
    ;
    void *_t797 = ptr_add(self->c_str, self->count);
    (void)_t797;
    memcpy(_t797, s->c_str, s->count);
    U64 _t798 = U64_clone(new_len);
    (void)_t798;
    self->count = _t798;
    ;
    void *_t799 = ptr_add(self->c_str, DEREF(new_len));
    (void)_t799;
    I32 _t800 = 0;
    (void)_t800;
    U64 _t801 = 1;
    (void)_t801;
    memset(_t799, _t800, _t801);
    ;
    ;
    U64_delete(new_len, &(Bool){1});
}

Str * Str_clone(Str * val) {
    (void)val;
    U64 _t802 = 1;
    (void)_t802;
    U64 _t803 = U64_add(val->count, _t802);
    (void)_t803;
    ;
    U8 *new_data = malloc(_t803);
    (void)new_data;
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t804 = ptr_add(new_data, val->count);
    (void)_t804;
    I32 _t805 = 0;
    (void)_t805;
    U64 _t806 = 1;
    (void)_t806;
    memset(_t804, _t805, _t806);
    ;
    ;
    Str *_t807 = malloc(sizeof(Str));
    _t807->c_str = new_data;
    _t807->count = val->count;
    _t807->cap = val->count;
    (void)_t807;
    return _t807;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t808; { Bool *_hp = (Bool *)U64_lt(&self->cap, CAP_VIEW); _t808 = *_hp; free(_hp); }
    (void)_t808;
    if (_t808) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    (void)val;
    Str *_t809 = Str_clone(val);
    (void)_t809;
    return _t809;
}

Str * Str_substr(Str * s, U64 * start, U64 * n) {
    (void)s;
    (void)start;
    (void)n;
    U64 *st = malloc(sizeof(U64)); *st = U64_clone(start);
    (void)st;
    U64 ln = U64_clone(n);
    (void)ln;
    Bool _t811; { Bool *_hp = (Bool *)U64_gt(st, &s->count); _t811 = *_hp; free(_hp); }
    (void)_t811;
    if (_t811) {
        *st = s->count;
    }
    ;
    U64 _t812 = U64_add(DEREF(st), ln);
    (void)_t812;
    Bool _t813; { Bool *_hp = (Bool *)U64_gt(&(U64){_t812}, &s->count); _t813 = *_hp; free(_hp); }
    (void)_t813;
    ;
    if (_t813) {
        U64 _t810 = U64_sub(s->count, DEREF(st));
        (void)_t810;
        ln = _t810;
        ;
    }
    ;
    void *_t814 = ptr_add(s->c_str, DEREF(st));
    (void)_t814;
    U64 _t815 = U64_clone(&(U64){ln});
    (void)_t815;
    ;
    U64 _t816 = U64_clone(CAP_VIEW);
    (void)_t816;
    Str *_t817 = malloc(sizeof(Str));
    _t817->c_str = _t814;
    _t817->count = _t815;
    _t817->cap = _t816;
    (void)_t817;
    ;
    ;
    U64_delete(st, &(Bool){1});
    return _t817;
}

Bool * Str_contains(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 _t848 = 0;
    (void)_t848;
    Bool _t849 = U64_eq(b->count, _t848);
    (void)_t849;
    ;
    if (_t849) {
        Bool _t818 = 1;
        (void)_t818;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t818; return _r; }
    }
    ;
    Bool _t850; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t850 = *_hp; free(_hp); }
    (void)_t850;
    if (_t850) {
        Bool _t819 = 0;
        (void)_t819;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t819; return _r; }
    }
    ;
    {
        U64 _fi820 = 0;
        (void)_fi820;
        while (1) {
            U64 _t835 = U64_sub(a->count, b->count);
            (void)_t835;
            U64 _t836 = 1;
            (void)_t836;
            U64 _t837 = 0;
            (void)_t837;
            U64 _t838 = U64_add(_t835, _t836);
            (void)_t838;
            ;
            ;
            Range *_t839 = Range_new(_t837, _t838);
            (void)_t839;
            ;
            ;
            U64 _t840; { U64 *_hp = (U64 *)Range_len(_t839); _t840 = *_hp; free(_hp); }
            (void)_t840;
            Range_delete(_t839, &(Bool){1});
            Bool _wcond821; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi820}, &(U64){_t840}); _wcond821 = *_hp; free(_hp); }
            (void)_wcond821;
            ;
            if (_wcond821) {
            } else {
                ;
                break;
            }
            ;
            U64 _t841 = U64_sub(a->count, b->count);
            (void)_t841;
            U64 _t842 = 1;
            (void)_t842;
            U64 _t843 = 0;
            (void)_t843;
            U64 _t844 = U64_add(_t841, _t842);
            (void)_t844;
            ;
            ;
            Range *_t845 = Range_new(_t843, _t844);
            (void)_t845;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t845, _fi820); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t845, &(Bool){1});
            U64 _t846 = 1;
            (void)_t846;
            U64 _t847 = U64_add(_fi820, _t846);
            (void)_t847;
            ;
            _fi820 = _t847;
            ;
            Bool found = 1;
            (void)found;
            {
                U64 _fi822 = 0;
                (void)_fi822;
                while (1) {
                    U64 _t825 = 0;
                    (void)_t825;
                    Range *_t826 = Range_new(_t825, b->count);
                    (void)_t826;
                    ;
                    U64 _t827; { U64 *_hp = (U64 *)Range_len(_t826); _t827 = *_hp; free(_hp); }
                    (void)_t827;
                    Range_delete(_t826, &(Bool){1});
                    Bool _wcond823; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi822}, &(U64){_t827}); _wcond823 = *_hp; free(_hp); }
                    (void)_wcond823;
                    ;
                    if (_wcond823) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U64 _t828 = 0;
                    (void)_t828;
                    Range *_t829 = Range_new(_t828, b->count);
                    (void)_t829;
                    ;
                    U64 *j = Range_get(_t829, _fi822);
                    (void)j;
                    Range_delete(_t829, &(Bool){1});
                    U64 _t830 = 1;
                    (void)_t830;
                    U64 _t831 = U64_add(_fi822, _t830);
                    (void)_t831;
                    ;
                    _fi822 = _t831;
                    ;
                    U64 *_t832 = malloc(sizeof(U64)); *_t832 = U64_add(i, DEREF(j));
                    (void)_t832;
                    U8 *ac = Str_get(a, _t832);
                    (void)ac;
                    U8 *bc = Str_get(b, j);
                    (void)bc;
                    Bool _t833; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t833 = *_hp; free(_hp); }
                    (void)_t833;
                    U64_delete(_t832, &(Bool){1});
                    U64_delete(j, &(Bool){1});
                    if (_t833) {
                        Bool _t824 = 0;
                        (void)_t824;
                        found = _t824;
                        ;
                    }
                    ;
                }
                ;
            }
            ;
            if (found) {
                Bool _t834 = 1;
                (void)_t834;
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t834; return _r; }
            }
            ;
        }
        ;
    }
    Bool _t851 = 0;
    (void)_t851;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t851; return _r; }
}

Bool * Str_starts_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t864; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t864 = *_hp; free(_hp); }
    (void)_t864;
    if (_t864) {
        Bool _t852 = 0;
        (void)_t852;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t852; return _r; }
    }
    ;
    {
        U64 _fi853 = 0;
        (void)_fi853;
        while (1) {
            U64 _t856 = 0;
            (void)_t856;
            Range *_t857 = Range_new(_t856, b->count);
            (void)_t857;
            ;
            U64 _t858; { U64 *_hp = (U64 *)Range_len(_t857); _t858 = *_hp; free(_hp); }
            (void)_t858;
            Range_delete(_t857, &(Bool){1});
            Bool _wcond854; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi853}, &(U64){_t858}); _wcond854 = *_hp; free(_hp); }
            (void)_wcond854;
            ;
            if (_wcond854) {
            } else {
                ;
                break;
            }
            ;
            U64 _t859 = 0;
            (void)_t859;
            Range *_t860 = Range_new(_t859, b->count);
            (void)_t860;
            ;
            U64 *i = Range_get(_t860, _fi853);
            (void)i;
            Range_delete(_t860, &(Bool){1});
            U64 _t861 = 1;
            (void)_t861;
            U64 _t862 = U64_add(_fi853, _t861);
            (void)_t862;
            ;
            _fi853 = _t862;
            ;
            U8 *ac = Str_get(a, i);
            (void)ac;
            U8 *bc = Str_get(b, i);
            (void)bc;
            Bool _t863; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t863 = *_hp; free(_hp); }
            (void)_t863;
            U64_delete(i, &(Bool){1});
            if (_t863) {
                Bool _t855 = 0;
                (void)_t855;
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t855; return _r; }
            }
            ;
        }
        ;
    }
    Bool _t865 = 1;
    (void)_t865;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t865; return _r; }
}

Bool * Str_ends_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t879; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t879 = *_hp; free(_hp); }
    (void)_t879;
    if (_t879) {
        Bool _t866 = 0;
        (void)_t866;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t866; return _r; }
    }
    ;
    U64 offset = U64_sub(a->count, b->count);
    (void)offset;
    {
        U64 _fi867 = 0;
        (void)_fi867;
        while (1) {
            U64 _t870 = 0;
            (void)_t870;
            Range *_t871 = Range_new(_t870, b->count);
            (void)_t871;
            ;
            U64 _t872; { U64 *_hp = (U64 *)Range_len(_t871); _t872 = *_hp; free(_hp); }
            (void)_t872;
            Range_delete(_t871, &(Bool){1});
            Bool _wcond868; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi867}, &(U64){_t872}); _wcond868 = *_hp; free(_hp); }
            (void)_wcond868;
            ;
            if (_wcond868) {
            } else {
                ;
                break;
            }
            ;
            U64 _t873 = 0;
            (void)_t873;
            Range *_t874 = Range_new(_t873, b->count);
            (void)_t874;
            ;
            U64 *i = Range_get(_t874, _fi867);
            (void)i;
            Range_delete(_t874, &(Bool){1});
            U64 _t875 = 1;
            (void)_t875;
            U64 _t876 = U64_add(_fi867, _t875);
            (void)_t876;
            ;
            _fi867 = _t876;
            ;
            U64 *_t877 = malloc(sizeof(U64)); *_t877 = U64_add(offset, DEREF(i));
            (void)_t877;
            U8 *ac = Str_get(a, _t877);
            (void)ac;
            U8 *bc = Str_get(b, i);
            (void)bc;
            Bool _t878; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t878 = *_hp; free(_hp); }
            (void)_t878;
            U64_delete(_t877, &(Bool){1});
            U64_delete(i, &(Bool){1});
            if (_t878) {
                Bool _t869 = 0;
                (void)_t869;
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t869; return _r; }
            }
            ;
        }
        ;
    }
    ;
    Bool _t880 = 1;
    (void)_t880;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t880; return _r; }
}

Bool * Str_is_empty(Str * self) {
    (void)self;
    U64 _t881 = 0;
    (void)_t881;
    Bool _t882 = U64_eq(self->count, _t881);
    (void)_t882;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t882; return _r; }
}

I64 * Str_find(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U64 _t917 = 0;
    (void)_t917;
    Bool _t918 = U64_eq(needle->count, _t917);
    (void)_t918;
    ;
    if (_t918) {
        I64 _t883 = 0;
        (void)_t883;
        I64 _t884 = 1;
        (void)_t884;
        I64 _t885 = I64_sub(_t883, _t884);
        (void)_t885;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t885; return _r; }
    }
    ;
    Bool _t919; { Bool *_hp = (Bool *)U64_gt(&needle->count, &self->count); _t919 = *_hp; free(_hp); }
    (void)_t919;
    if (_t919) {
        I64 _t886 = 0;
        (void)_t886;
        I64 _t887 = 1;
        (void)_t887;
        I64 _t888 = I64_sub(_t886, _t887);
        (void)_t888;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t888; return _r; }
    }
    ;
    {
        U64 _fi889 = 0;
        (void)_fi889;
        while (1) {
            U64 _t904 = U64_sub(self->count, needle->count);
            (void)_t904;
            U64 _t905 = 1;
            (void)_t905;
            U64 _t906 = 0;
            (void)_t906;
            U64 _t907 = U64_add(_t904, _t905);
            (void)_t907;
            ;
            ;
            Range *_t908 = Range_new(_t906, _t907);
            (void)_t908;
            ;
            ;
            U64 _t909; { U64 *_hp = (U64 *)Range_len(_t908); _t909 = *_hp; free(_hp); }
            (void)_t909;
            Range_delete(_t908, &(Bool){1});
            Bool _wcond890; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi889}, &(U64){_t909}); _wcond890 = *_hp; free(_hp); }
            (void)_wcond890;
            ;
            if (_wcond890) {
            } else {
                ;
                break;
            }
            ;
            U64 _t910 = U64_sub(self->count, needle->count);
            (void)_t910;
            U64 _t911 = 1;
            (void)_t911;
            U64 _t912 = 0;
            (void)_t912;
            U64 _t913 = U64_add(_t910, _t911);
            (void)_t913;
            ;
            ;
            Range *_t914 = Range_new(_t912, _t913);
            (void)_t914;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t914, _fi889); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t914, &(Bool){1});
            U64 _t915 = 1;
            (void)_t915;
            U64 _t916 = U64_add(_fi889, _t915);
            (void)_t916;
            ;
            _fi889 = _t916;
            ;
            Bool found = 1;
            (void)found;
            {
                U64 _fi891 = 0;
                (void)_fi891;
                while (1) {
                    U64 _t894 = 0;
                    (void)_t894;
                    Range *_t895 = Range_new(_t894, needle->count);
                    (void)_t895;
                    ;
                    U64 _t896; { U64 *_hp = (U64 *)Range_len(_t895); _t896 = *_hp; free(_hp); }
                    (void)_t896;
                    Range_delete(_t895, &(Bool){1});
                    Bool _wcond892; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi891}, &(U64){_t896}); _wcond892 = *_hp; free(_hp); }
                    (void)_wcond892;
                    ;
                    if (_wcond892) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U64 _t897 = 0;
                    (void)_t897;
                    Range *_t898 = Range_new(_t897, needle->count);
                    (void)_t898;
                    ;
                    U64 *j = Range_get(_t898, _fi891);
                    (void)j;
                    Range_delete(_t898, &(Bool){1});
                    U64 _t899 = 1;
                    (void)_t899;
                    U64 _t900 = U64_add(_fi891, _t899);
                    (void)_t900;
                    ;
                    _fi891 = _t900;
                    ;
                    U64 *_t901 = malloc(sizeof(U64)); *_t901 = U64_add(i, DEREF(j));
                    (void)_t901;
                    U8 *ac = Str_get(self, _t901);
                    (void)ac;
                    U8 *bc = Str_get(needle, j);
                    (void)bc;
                    Bool _t902; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t902 = *_hp; free(_hp); }
                    (void)_t902;
                    U64_delete(_t901, &(Bool){1});
                    U64_delete(j, &(Bool){1});
                    if (_t902) {
                        Bool _t893 = 0;
                        (void)_t893;
                        found = _t893;
                        ;
                    }
                    ;
                }
                ;
            }
            if (found) {
                I64 _t903 = U64_to_i64(i);
                (void)_t903;
                ;
                ;
                ;
                { I64 *_r = malloc(sizeof(I64)); *_r = _t903; return _r; }
            }
            ;
            ;
        }
        ;
    }
    I64 _t920 = 0;
    (void)_t920;
    I64 _t921 = 1;
    (void)_t921;
    I64 _t922 = I64_sub(_t920, _t921);
    (void)_t922;
    ;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t922; return _r; }
}

I64 * Str_rfind(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U64 _t957 = 0;
    (void)_t957;
    Bool _t958 = U64_eq(needle->count, _t957);
    (void)_t958;
    ;
    if (_t958) {
        I64 _t923 = 0;
        (void)_t923;
        I64 _t924 = 1;
        (void)_t924;
        I64 _t925 = I64_sub(_t923, _t924);
        (void)_t925;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t925; return _r; }
    }
    ;
    Bool _t959; { Bool *_hp = (Bool *)U64_gt(&needle->count, &self->count); _t959 = *_hp; free(_hp); }
    (void)_t959;
    if (_t959) {
        I64 _t926 = 0;
        (void)_t926;
        I64 _t927 = 1;
        (void)_t927;
        I64 _t928 = I64_sub(_t926, _t927);
        (void)_t928;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t928; return _r; }
    }
    ;
    I64 _t960 = 0;
    (void)_t960;
    I64 _t961 = 1;
    (void)_t961;
    I64 last = I64_sub(_t960, _t961);
    (void)last;
    ;
    ;
    {
        U64 _fi929 = 0;
        (void)_fi929;
        while (1) {
            U64 _t944 = U64_sub(self->count, needle->count);
            (void)_t944;
            U64 _t945 = 1;
            (void)_t945;
            U64 _t946 = 0;
            (void)_t946;
            U64 _t947 = U64_add(_t944, _t945);
            (void)_t947;
            ;
            ;
            Range *_t948 = Range_new(_t946, _t947);
            (void)_t948;
            ;
            ;
            U64 _t949; { U64 *_hp = (U64 *)Range_len(_t948); _t949 = *_hp; free(_hp); }
            (void)_t949;
            Range_delete(_t948, &(Bool){1});
            Bool _wcond930; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi929}, &(U64){_t949}); _wcond930 = *_hp; free(_hp); }
            (void)_wcond930;
            ;
            if (_wcond930) {
            } else {
                ;
                break;
            }
            ;
            U64 _t950 = U64_sub(self->count, needle->count);
            (void)_t950;
            U64 _t951 = 1;
            (void)_t951;
            U64 _t952 = 0;
            (void)_t952;
            U64 _t953 = U64_add(_t950, _t951);
            (void)_t953;
            ;
            ;
            Range *_t954 = Range_new(_t952, _t953);
            (void)_t954;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t954, _fi929); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t954, &(Bool){1});
            U64 _t955 = 1;
            (void)_t955;
            U64 _t956 = U64_add(_fi929, _t955);
            (void)_t956;
            ;
            _fi929 = _t956;
            ;
            Bool found = 1;
            (void)found;
            {
                U64 _fi931 = 0;
                (void)_fi931;
                while (1) {
                    U64 _t934 = 0;
                    (void)_t934;
                    Range *_t935 = Range_new(_t934, needle->count);
                    (void)_t935;
                    ;
                    U64 _t936; { U64 *_hp = (U64 *)Range_len(_t935); _t936 = *_hp; free(_hp); }
                    (void)_t936;
                    Range_delete(_t935, &(Bool){1});
                    Bool _wcond932; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi931}, &(U64){_t936}); _wcond932 = *_hp; free(_hp); }
                    (void)_wcond932;
                    ;
                    if (_wcond932) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U64 _t937 = 0;
                    (void)_t937;
                    Range *_t938 = Range_new(_t937, needle->count);
                    (void)_t938;
                    ;
                    U64 *j = Range_get(_t938, _fi931);
                    (void)j;
                    Range_delete(_t938, &(Bool){1});
                    U64 _t939 = 1;
                    (void)_t939;
                    U64 _t940 = U64_add(_fi931, _t939);
                    (void)_t940;
                    ;
                    _fi931 = _t940;
                    ;
                    U64 *_t941 = malloc(sizeof(U64)); *_t941 = U64_add(i, DEREF(j));
                    (void)_t941;
                    U8 *ac = Str_get(self, _t941);
                    (void)ac;
                    U8 *bc = Str_get(needle, j);
                    (void)bc;
                    Bool _t942; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t942 = *_hp; free(_hp); }
                    (void)_t942;
                    U64_delete(_t941, &(Bool){1});
                    U64_delete(j, &(Bool){1});
                    if (_t942) {
                        Bool _t933 = 0;
                        (void)_t933;
                        found = _t933;
                        ;
                    }
                    ;
                }
                ;
            }
            if (found) {
                I64 _t943 = U64_to_i64(i);
                (void)_t943;
                last = _t943;
                ;
            }
            ;
            ;
        }
        ;
    }
    { I64 *_r = malloc(sizeof(I64)); *_r = last; return _r; }
}

Str * Str_replace(Str * self, Str * from, Str * to) {
    (void)self;
    (void)from;
    (void)to;
    U64 _t977 = 0;
    (void)_t977;
    Bool _t978 = U64_eq(from->count, _t977);
    (void)_t978;
    ;
    if (_t978) {
        Str *_t962 = Str_clone(self);
        (void)_t962;
        ;
        return _t962;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    U64 start = 0;
    (void)start;
    while (1) {
        U64 _t964 = U64_sub(self->count, from->count);
        (void)_t964;
        Bool _wcond963; { Bool *_hp = (Bool *)U64_lte(&(U64){start}, &(U64){_t964}); _wcond963 = *_hp; free(_hp); }
        (void)_wcond963;
        ;
        if (_wcond963) {
        } else {
            ;
            break;
        }
        ;
        U64 _t965 = U64_sub(self->count, start);
        (void)_t965;
        Str *rest = Str_substr(self, &(U64){start}, &(U64){_t965});
        (void)rest;
        ;
        I64 pos; { I64 *_hp = (I64 *)Str_find(rest, from); pos = *_hp; free(_hp); }
        (void)pos;
        I64 _t966 = 0;
        (void)_t966;
        I64 _t967 = 1;
        (void)_t967;
        I64 _t968 = I64_sub(_t966, _t967);
        (void)_t968;
        ;
        ;
        Bool _t969 = I64_eq(pos, _t968);
        (void)_t969;
        ;
        if (_t969) {
            result = Str_concat(result, rest);
            ;
            ;
            Str_delete(rest, &(Bool){1});
            ;
            return result;
        }
        ;
        Str_delete(rest, &(Bool){1});
        U64 _t970 = I64_to_u64(pos);
        (void)_t970;
        Str *_t971 = Str_substr(self, &(U64){start}, &(U64){_t970});
        (void)_t971;
        ;
        result = Str_concat(result, _t971);
        Str_delete(_t971, &(Bool){1});
        result = Str_concat(result, to);
        U64 _t972 = I64_to_u64(pos);
        (void)_t972;
        ;
        U64 _t973 = U64_add(start, _t972);
        (void)_t973;
        ;
        U64 _t974 = U64_add(_t973, from->count);
        (void)_t974;
        ;
        start = _t974;
        ;
    }
    Bool _t979; { Bool *_hp = (Bool *)U64_lt(&(U64){start}, &self->count); _t979 = *_hp; free(_hp); }
    (void)_t979;
    if (_t979) {
        U64 _t975 = U64_sub(self->count, start);
        (void)_t975;
        Str *_t976 = Str_substr(self, &(U64){start}, &(U64){_t975});
        (void)_t976;
        ;
        result = Str_concat(result, _t976);
        Str_delete(_t976, &(Bool){1});
    }
    ;
    ;
    return result;
}

Str * Str_get_char(Str * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t980 = 1;
    (void)_t980;
    Str *_t981 = Str_substr(self, i, &(U64){_t980});
    (void)_t981;
    ;
    return _t981;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    (void)prefix;
    Bool _t984; { Bool *_hp = (Bool *)Str_starts_with(self, prefix); _t984 = *_hp; free(_hp); }
    (void)_t984;
    if (_t984) {
        U64 _t982 = U64_sub(self->count, prefix->count);
        (void)_t982;
        Str *_t983 = Str_substr(self, &prefix->count, &(U64){_t982});
        (void)_t983;
        ;
        ;
        return _t983;
    }
    ;
    Str *_t985 = Str_clone(self);
    (void)_t985;
    return _t985;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    (void)suffix;
    Bool _t989; { Bool *_hp = (Bool *)Str_ends_with(self, suffix); _t989 = *_hp; free(_hp); }
    (void)_t989;
    if (_t989) {
        U64 _t986 = 0;
        (void)_t986;
        U64 _t987 = U64_sub(self->count, suffix->count);
        (void)_t987;
        Str *_t988 = Str_substr(self, &(U64){_t986}, &(U64){_t987});
        (void)_t988;
        ;
        ;
        ;
        return _t988;
    }
    ;
    Str *_t990 = Str_clone(self);
    (void)_t990;
    return _t990;
}

Str * Str_from_byte(U8 * byte) {
    (void)byte;
    U64 _t991 = 2;
    (void)_t991;
    U8 *buf = malloc(_t991);
    (void)buf;
    ;
    U64 _t992 = 1;
    (void)_t992;
    memcpy(buf, byte, _t992);
    ;
    U64 *_t993 = malloc(sizeof(U64));
    *_t993 = 1;
    (void)_t993;
    void *_t994 = ptr_add(buf, DEREF(_t993));
    (void)_t994;
    I32 _t995 = 0;
    (void)_t995;
    U64 _t996 = 1;
    (void)_t996;
    memset(_t994, _t995, _t996);
    U64_delete(_t993, &(Bool){1});
    ;
    ;
    I64 _t997 = 1;
    (void)_t997;
    I64 _t998 = 1;
    (void)_t998;
    Str *_t999 = malloc(sizeof(Str));
    _t999->c_str = buf;
    _t999->count = _t997;
    _t999->cap = _t998;
    (void)_t999;
    ;
    ;
    return _t999;
}

I64 * Str_to_i64(Str * self) {
    (void)self;
    U64 _t1043 = 0;
    (void)_t1043;
    Bool _t1044 = U64_eq(self->count, _t1043);
    (void)_t1044;
    ;
    if (_t1044) {
        Str *_t1000 = Str_lit("Str", 3ULL);
        (void)_t1000;
        U64 _t1001; { U64 *_hp = (U64 *)Str_size(); _t1001 = *_hp; free(_hp); }
        (void)_t1001;
        U64 _t1002 = 1;
        (void)_t1002;
        Array *_va15 = Array_new(_t1000, &(U64){_t1001}, &(U64){_t1002});
        (void)_va15;
        Str_delete(_t1000, &(Bool){1});
        ;
        ;
        U64 _t1003 = 0;
        (void)_t1003;
        Str *_t1004 = Str_lit("Str.to_i64: empty string", 24ULL);
        (void)_t1004;
        Array_set(_va15, &(U64){_t1003}, _t1004);
        ;
        Str *_t1005 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:206:37", 61ULL);
        (void)_t1005;
        panic(_t1005, _va15);
        Str_delete(_t1005, &(Bool){1});
    }
    ;
    I64 result = 0;
    (void)result;
    U64 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U64 *_t1045 = malloc(sizeof(U64));
    *_t1045 = 0;
    (void)_t1045;
    U8 *first = Str_get(self, _t1045);
    (void)first;
    U8 _t1046 = 45;
    (void)_t1046;
    Bool _t1047 = U8_eq(DEREF(first), _t1046);
    (void)_t1047;
    U64_delete(_t1045, &(Bool){1});
    ;
    if (_t1047) {
        Bool _t1006 = 1;
        (void)_t1006;
        neg = _t1006;
        ;
        U64 _t1007 = 1;
        (void)_t1007;
        start = _t1007;
        ;
    }
    ;
    Bool _t1048 = U64_eq(start, self->count);
    (void)_t1048;
    if (_t1048) {
        Str *_t1008 = Str_lit("Str", 3ULL);
        (void)_t1008;
        U64 _t1009; { U64 *_hp = (U64 *)Str_size(); _t1009 = *_hp; free(_hp); }
        (void)_t1009;
        U64 _t1010 = 1;
        (void)_t1010;
        Array *_va16 = Array_new(_t1008, &(U64){_t1009}, &(U64){_t1010});
        (void)_va16;
        Str_delete(_t1008, &(Bool){1});
        ;
        ;
        U64 _t1011 = 0;
        (void)_t1011;
        Str *_t1012 = Str_lit("Str.to_i64: no digits", 21ULL);
        (void)_t1012;
        Array_set(_va16, &(U64){_t1011}, _t1012);
        ;
        Str *_t1013 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:215:41", 61ULL);
        (void)_t1013;
        panic(_t1013, _va16);
        Str_delete(_t1013, &(Bool){1});
    }
    ;
    {
        U64 _fi1014 = 0;
        (void)_fi1014;
        while (1) {
            Range *_t1026 = Range_new(start, self->count);
            (void)_t1026;
            U64 _t1027; { U64 *_hp = (U64 *)Range_len(_t1026); _t1027 = *_hp; free(_hp); }
            (void)_t1027;
            Range_delete(_t1026, &(Bool){1});
            Bool _wcond1015; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1014}, &(U64){_t1027}); _wcond1015 = *_hp; free(_hp); }
            (void)_wcond1015;
            ;
            if (_wcond1015) {
            } else {
                ;
                break;
            }
            ;
            Range *_t1028 = Range_new(start, self->count);
            (void)_t1028;
            U64 *i = Range_get(_t1028, _fi1014);
            (void)i;
            Range_delete(_t1028, &(Bool){1});
            U64 _t1029 = 1;
            (void)_t1029;
            U64 _t1030 = U64_add(_fi1014, _t1029);
            (void)_t1030;
            ;
            _fi1014 = _t1030;
            ;
            U8 *ch = Str_get(self, i);
            (void)ch;
            I64 _t1031 = U8_to_i64(DEREF(ch));
            (void)_t1031;
            U64_delete(i, &(Bool){1});
            I64 _t1032 = 48;
            (void)_t1032;
            I64 d = I64_sub(_t1031, _t1032);
            (void)d;
            ;
            ;
            I64 _t1033 = 0;
            (void)_t1033;
            I64 _t1034 = 9;
            (void)_t1034;
            Bool _t1035; { Bool *_hp = (Bool *)I64_lt(&(I64){d}, &(I64){_t1033}); _t1035 = *_hp; free(_hp); }
            (void)_t1035;
            ;
            Bool _t1036; { Bool *_hp = (Bool *)I64_gt(&(I64){d}, &(I64){_t1034}); _t1036 = *_hp; free(_hp); }
            (void)_t1036;
            ;
            Bool _t1037 = Bool_or(_t1035, _t1036);
            (void)_t1037;
            ;
            ;
            if (_t1037) {
                Str *_t1016 = Str_lit("Str", 3ULL);
                (void)_t1016;
                U64 _t1017; { U64 *_hp = (U64 *)Str_size(); _t1017 = *_hp; free(_hp); }
                (void)_t1017;
                U64 _t1018 = 3;
                (void)_t1018;
                Array *_va17 = Array_new(_t1016, &(U64){_t1017}, &(U64){_t1018});
                (void)_va17;
                Str_delete(_t1016, &(Bool){1});
                ;
                ;
                U64 _t1019 = 0;
                (void)_t1019;
                Str *_t1020 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                (void)_t1020;
                Array_set(_va17, &(U64){_t1019}, _t1020);
                ;
                U64 _t1021 = 1;
                (void)_t1021;
                Str *_t1022 = Str_clone(self);
                (void)_t1022;
                Array_set(_va17, &(U64){_t1021}, _t1022);
                ;
                U64 _t1023 = 2;
                (void)_t1023;
                Str *_t1024 = Str_lit("'", 1ULL);
                (void)_t1024;
                Array_set(_va17, &(U64){_t1023}, _t1024);
                ;
                Str *_t1025 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:220:23", 61ULL);
                (void)_t1025;
                panic(_t1025, _va17);
                Str_delete(_t1025, &(Bool){1});
            }
            ;
            I64 _t1038 = 10;
            (void)_t1038;
            I64 _t1039 = I64_mul(result, _t1038);
            (void)_t1039;
            ;
            I64 _t1040 = I64_add(_t1039, d);
            (void)_t1040;
            ;
            ;
            result = _t1040;
            ;
        }
        ;
    }
    ;
    if (neg) {
        I64 _t1041 = 0;
        (void)_t1041;
        I64 _t1042 = I64_sub(_t1041, result);
        (void)_t1042;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t1042; return _r; }
    }
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = result; return _r; }
}

U64 *Str_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Str);
    return r;
}

Bool * Str_eq(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1050; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1050 = *_hp; free(_hp); }
    (void)_t1050;
    I64 _t1051 = 0;
    (void)_t1051;
    Bool _t1052 = I64_eq(_t1050, _t1051);
    (void)_t1052;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1052; return _r; }
}

Bool * Str_lt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1053 = 0;
    (void)_t1053;
    I64 _t1054 = 1;
    (void)_t1054;
    I64 _t1055; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1055 = *_hp; free(_hp); }
    (void)_t1055;
    I64 _t1056 = I64_sub(_t1053, _t1054);
    (void)_t1056;
    ;
    ;
    Bool _t1057 = I64_eq(_t1055, _t1056);
    (void)_t1057;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1057; return _r; }
}

Bool * Str_gt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1058; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1058 = *_hp; free(_hp); }
    (void)_t1058;
    I64 _t1059 = 1;
    (void)_t1059;
    Bool _t1060 = I64_eq(_t1058, _t1059);
    (void)_t1060;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1060; return _r; }
}

Bool * Str_neq(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1061; { Bool *_hp = (Bool *)Str_eq(a, b); _t1061 = *_hp; free(_hp); }
    (void)_t1061;
    Bool _t1062 = Bool_not(_t1061);
    (void)_t1062;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1062; return _r; }
}

Bool * Str_lte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1063; { Bool *_hp = (Bool *)Str_gt(a, b); _t1063 = *_hp; free(_hp); }
    (void)_t1063;
    Bool _t1064 = Bool_not(_t1063);
    (void)_t1064;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1064; return _r; }
}

Bool * Str_gte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1065; { Bool *_hp = (Bool *)Str_lt(a, b); _t1065 = *_hp; free(_hp); }
    (void)_t1065;
    Bool _t1066 = Bool_not(_t1065);
    (void)_t1066;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1066; return _r; }
}

