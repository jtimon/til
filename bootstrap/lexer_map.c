Map * Map_new(Str * key_type, U64 * key_size, Str * val_type, U64 * val_size) {
    (void)key_type;
    (void)key_size;
    (void)val_type;
    (void)val_size;
    Bool _t485; { Bool *_hp = (Bool *)Str_is_empty(key_type); _t485 = *_hp; free(_hp); }
    (void)_t485;
    Bool _t486 = Bool_not(_t485);
    (void)_t486;
    ;
    if (_t486) {
        Bool _t483 = dyn_has_cmp(key_type);
        (void)_t483;
        Bool _t484 = Bool_not(_t483);
        (void)_t484;
        ;
        if (_t484) {
            Str *_t473 = Str_lit("Str", 3ULL);
            (void)_t473;
            U64 _t474; { U64 *_hp = (U64 *)Str_size(); _t474 = *_hp; free(_hp); }
            (void)_t474;
            U64 _t475 = 3;
            (void)_t475;
            Array *_va9 = Array_new(_t473, &(U64){_t474}, &(U64){_t475});
            (void)_va9;
            Str_delete(_t473, &(Bool){1});
            ;
            ;
            U64 _t476 = 0;
            (void)_t476;
            Str *_t477 = Str_lit("Map.new: type ", 14ULL);
            (void)_t477;
            Array_set(_va9, &(U64){_t476}, _t477);
            ;
            U64 _t478 = 1;
            (void)_t478;
            Str *_t479 = Str_clone(key_type);
            (void)_t479;
            Array_set(_va9, &(U64){_t478}, _t479);
            ;
            U64 _t480 = 2;
            (void)_t480;
            Str *_t481 = Str_lit(" must implement cmp", 19ULL);
            (void)_t481;
            Array_set(_va9, &(U64){_t480}, _t481);
            ;
            Str *_t482 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:17:23", 60ULL);
            (void)_t482;
            panic(_t482, _va9);
            Str_delete(_t482, &(Bool){1});
        }
        ;
    }
    ;
    void *_t487 = malloc(DEREF(key_size));
    (void)_t487;
    void *_t488 = malloc(DEREF(val_size));
    (void)_t488;
    U64 _t489 = 0;
    (void)_t489;
    I64 _t490 = 1;
    (void)_t490;
    U64 _t491 = U64_clone(key_size);
    (void)_t491;
    U64 _t492 = U64_clone(val_size);
    (void)_t492;
    Map *_t493 = malloc(sizeof(Map));
    _t493->key_data = _t487;
    _t493->val_data = _t488;
    _t493->count = _t489;
    _t493->cap = _t490;
    _t493->key_size = _t491;
    { Str *_ca = Str_clone(key_type); _t493->key_type = *_ca; free(_ca); }
    _t493->val_size = _t492;
    { Str *_ca = Str_clone(val_type); _t493->val_type = *_ca; free(_ca); }
    (void)_t493;
    ;
    ;
    ;
    ;
    return _t493;
}

U64 * Map_len(Map * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

Bool * Map_has(Map * self, void * key) {
    (void)self;
    (void)key;
    U64 lo = 0;
    (void)lo;
    U64 hi = self->count;
    (void)hi;
    while (1) {
        Bool _wcond494; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond494 = *_hp; free(_hp); }
        (void)_wcond494;
        if (_wcond494) {
        } else {
            ;
            break;
        }
        ;
        U64 _t501 = U64_sub(hi, lo);
        (void)_t501;
        U64 _t502 = 2;
        (void)_t502;
        U64 _t503 = U64_div(_t501, _t502);
        (void)_t503;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t503);
        (void)mid;
        ;
        U64 *_t504 = malloc(sizeof(U64)); *_t504 = U64_mul(DEREF(mid), self->key_size);
        (void)_t504;
        void *_t505 = ptr_add(self->key_data, DEREF(_t504));
        (void)_t505;
        I64 *c = dyn_call_cmp(&self->key_type, _t505, key);
        (void)c;
        U64_delete(_t504, &(Bool){1});
        I64 _t506 = 0;
        (void)_t506;
        Bool _t507; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t506}); _t507 = *_hp; free(_hp); }
        (void)_t507;
        ;
        if (_t507) {
            U64 _t495 = 1;
            (void)_t495;
            U64 _t496 = U64_add(DEREF(mid), _t495);
            (void)_t496;
            ;
            lo = _t496;
            ;
        } else {
            I64 _t499 = 0;
            (void)_t499;
            Bool _t500; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t499}); _t500 = *_hp; free(_hp); }
            (void)_t500;
            ;
            if (_t500) {
                U64 _t497 = U64_clone(mid);
                (void)_t497;
                hi = _t497;
                ;
            } else {
                Bool _t498 = 1;
                (void)_t498;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t498; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t508 = 0;
    (void)_t508;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t508; return _r; }
}

void * Map_get(Map * self, void * key) {
    (void)self;
    (void)key;
    U64 lo = 0;
    (void)lo;
    U64 hi = self->count;
    (void)hi;
    while (1) {
        Bool _wcond509; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond509 = *_hp; free(_hp); }
        (void)_wcond509;
        if (_wcond509) {
        } else {
            ;
            break;
        }
        ;
        U64 _t517 = U64_sub(hi, lo);
        (void)_t517;
        U64 _t518 = 2;
        (void)_t518;
        U64 _t519 = U64_div(_t517, _t518);
        (void)_t519;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t519);
        (void)mid;
        ;
        U64 *_t520 = malloc(sizeof(U64)); *_t520 = U64_mul(DEREF(mid), self->key_size);
        (void)_t520;
        void *_t521 = ptr_add(self->key_data, DEREF(_t520));
        (void)_t521;
        I64 *c = dyn_call_cmp(&self->key_type, _t521, key);
        (void)c;
        U64_delete(_t520, &(Bool){1});
        I64 _t522 = 0;
        (void)_t522;
        Bool _t523; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t522}); _t523 = *_hp; free(_hp); }
        (void)_t523;
        ;
        if (_t523) {
            U64 _t510 = 1;
            (void)_t510;
            U64 _t511 = U64_add(DEREF(mid), _t510);
            (void)_t511;
            ;
            lo = _t511;
            ;
        } else {
            I64 _t515 = 0;
            (void)_t515;
            Bool _t516; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t515}); _t516 = *_hp; free(_hp); }
            (void)_t516;
            ;
            if (_t516) {
                U64 _t512 = U64_clone(mid);
                (void)_t512;
                hi = _t512;
                ;
            } else {
                U64 *_t513 = malloc(sizeof(U64)); *_t513 = U64_mul(DEREF(mid), self->val_size);
                (void)_t513;
                void *_t514 = ptr_add(self->val_data, DEREF(_t513));
                (void)_t514;
                U64_delete(_t513, &(Bool){1});
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                return _t514;
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Str *_t524 = Str_lit("Str", 3ULL);
    (void)_t524;
    U64 _t525; { U64 *_hp = (U64 *)Str_size(); _t525 = *_hp; free(_hp); }
    (void)_t525;
    U64 _t526 = 1;
    (void)_t526;
    Array *_va10 = Array_new(_t524, &(U64){_t525}, &(U64){_t526});
    (void)_va10;
    Str_delete(_t524, &(Bool){1});
    ;
    ;
    U64 _t527 = 0;
    (void)_t527;
    Str *_t528 = Str_lit("Map.get: key not found", 22ULL);
    (void)_t528;
    Array_set(_va10, &(U64){_t527}, _t528);
    ;
    Str *_t529 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:56:15", 60ULL);
    (void)_t529;
    panic(_t529, _va10);
    Str_delete(_t529, &(Bool){1});
    U64 *_t530 = malloc(sizeof(U64));
    *_t530 = 0;
    (void)_t530;
    void *_t531 = ptr_add(self->val_data, DEREF(_t530));
    (void)_t531;
    U64_delete(_t530, &(Bool){1});
    return _t531;
}

void Map_set(Map * self, void * key, void * val) {
    (void)self;
    (void)key;
    (void)val;
    U64 lo = 0;
    (void)lo;
    U64 hi = self->count;
    (void)hi;
    Bool found = 0;
    (void)found;
    while (1) {
        Bool _wcond532; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond532 = *_hp; free(_hp); }
        (void)_wcond532;
        if (_wcond532) {
        } else {
            ;
            break;
        }
        ;
        U64 _t541 = U64_sub(hi, lo);
        (void)_t541;
        U64 _t542 = 2;
        (void)_t542;
        U64 _t543 = U64_div(_t541, _t542);
        (void)_t543;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t543);
        (void)mid;
        ;
        U64 *_t544 = malloc(sizeof(U64)); *_t544 = U64_mul(DEREF(mid), self->key_size);
        (void)_t544;
        void *_t545 = ptr_add(self->key_data, DEREF(_t544));
        (void)_t545;
        I64 *c = dyn_call_cmp(&self->key_type, _t545, key);
        (void)c;
        U64_delete(_t544, &(Bool){1});
        I64 _t546 = 0;
        (void)_t546;
        Bool _t547; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t546}); _t547 = *_hp; free(_hp); }
        (void)_t547;
        ;
        if (_t547) {
            U64 _t533 = 1;
            (void)_t533;
            U64 _t534 = U64_add(DEREF(mid), _t533);
            (void)_t534;
            ;
            lo = _t534;
            ;
        } else {
            I64 _t539 = 0;
            (void)_t539;
            Bool _t540; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t539}); _t540 = *_hp; free(_hp); }
            (void)_t540;
            ;
            if (_t540) {
                U64 _t535 = U64_clone(mid);
                (void)_t535;
                hi = _t535;
                ;
            } else {
                Bool _t536 = 1;
                (void)_t536;
                found = _t536;
                ;
                U64 _t537 = U64_clone(mid);
                (void)_t537;
                lo = _t537;
                ;
                U64 _t538 = U64_clone(mid);
                (void)_t538;
                hi = _t538;
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
        Bool _t552; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t552 = *_hp; free(_hp); }
        (void)_t552;
        Bool _t553 = Bool_not(_t552);
        (void)_t553;
        ;
        if (_t553) {
            Bool _t548 = 0;
            (void)_t548;
            dyn_call_delete(&self->key_type, key, &(Bool){_t548});
            ;
        }
        ;
        free(key);
        Bool _t554; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t554 = *_hp; free(_hp); }
        (void)_t554;
        Bool _t555 = Bool_not(_t554);
        (void)_t555;
        ;
        if (_t555) {
            U64 *_t549 = malloc(sizeof(U64)); *_t549 = U64_mul(lo, self->val_size);
            (void)_t549;
            void *_t550 = ptr_add(self->val_data, DEREF(_t549));
            (void)_t550;
            Bool _t551 = 0;
            (void)_t551;
            dyn_call_delete(&self->val_type, _t550, &(Bool){_t551});
            U64_delete(_t549, &(Bool){1});
            ;
        }
        ;
        U64 *_t556 = malloc(sizeof(U64)); *_t556 = U64_mul(lo, self->val_size);
        (void)_t556;
        void *_t557 = ptr_add(self->val_data, DEREF(_t556));
        (void)_t557;
        memcpy(_t557, val, self->val_size);
        U64_delete(_t556, &(Bool){1});
        free(val);
    } else {
        Bool _t564 = U64_eq(self->count, self->cap);
        (void)_t564;
        if (_t564) {
            U64 _t558 = 2;
            (void)_t558;
            U64 new_cap = U64_mul(self->cap, _t558);
            (void)new_cap;
            ;
            U64 _t559 = U64_mul(new_cap, self->key_size);
            (void)_t559;
            void *_t560 = realloc(self->key_data, _t559);
            (void)_t560;
            ;
            self->key_data = _t560;
            U64 _t561 = U64_mul(new_cap, self->val_size);
            (void)_t561;
            void *_t562 = realloc(self->val_data, _t561);
            (void)_t562;
            ;
            self->val_data = _t562;
            U64 _t563 = U64_clone(&(U64){new_cap});
            (void)_t563;
            ;
            self->cap = _t563;
            ;
        }
        ;
        U64 _t565 = 1;
        (void)_t565;
        U64 _t566 = U64_add(lo, _t565);
        (void)_t566;
        ;
        U64 *_t567 = malloc(sizeof(U64)); *_t567 = U64_mul(_t566, self->key_size);
        (void)_t567;
        ;
        U64 *_t568 = malloc(sizeof(U64)); *_t568 = U64_mul(lo, self->key_size);
        (void)_t568;
        U64 _t569 = U64_sub(self->count, lo);
        (void)_t569;
        void *_t570 = ptr_add(self->key_data, DEREF(_t567));
        (void)_t570;
        void *_t571 = ptr_add(self->key_data, DEREF(_t568));
        (void)_t571;
        U64 _t572 = U64_mul(_t569, self->key_size);
        (void)_t572;
        ;
        memmove(_t570, _t571, _t572);
        U64_delete(_t567, &(Bool){1});
        U64_delete(_t568, &(Bool){1});
        ;
        U64 _t573 = 1;
        (void)_t573;
        U64 _t574 = U64_add(lo, _t573);
        (void)_t574;
        ;
        U64 *_t575 = malloc(sizeof(U64)); *_t575 = U64_mul(_t574, self->val_size);
        (void)_t575;
        ;
        U64 *_t576 = malloc(sizeof(U64)); *_t576 = U64_mul(lo, self->val_size);
        (void)_t576;
        U64 _t577 = U64_sub(self->count, lo);
        (void)_t577;
        void *_t578 = ptr_add(self->val_data, DEREF(_t575));
        (void)_t578;
        void *_t579 = ptr_add(self->val_data, DEREF(_t576));
        (void)_t579;
        U64 _t580 = U64_mul(_t577, self->val_size);
        (void)_t580;
        ;
        memmove(_t578, _t579, _t580);
        U64_delete(_t575, &(Bool){1});
        U64_delete(_t576, &(Bool){1});
        ;
        U64 *_t581 = malloc(sizeof(U64)); *_t581 = U64_mul(lo, self->key_size);
        (void)_t581;
        void *_t582 = ptr_add(self->key_data, DEREF(_t581));
        (void)_t582;
        memcpy(_t582, key, self->key_size);
        U64_delete(_t581, &(Bool){1});
        U64 *_t583 = malloc(sizeof(U64)); *_t583 = U64_mul(lo, self->val_size);
        (void)_t583;
        void *_t584 = ptr_add(self->val_data, DEREF(_t583));
        (void)_t584;
        memcpy(_t584, val, self->val_size);
        U64_delete(_t583, &(Bool){1});
        free(key);
        free(val);
        U64 _t585 = 1;
        (void)_t585;
        U64 _t586 = U64_add(self->count, _t585);
        (void)_t586;
        ;
        self->count = _t586;
        ;
    }
    ;
    ;
}

void Map_delete(Map * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t613; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t613 = *_hp; free(_hp); }
    (void)_t613;
    Bool _t614 = Bool_not(_t613);
    (void)_t614;
    ;
    if (_t614) {
        {
            U64 _fi587 = 0;
            (void)_fi587;
            while (1) {
                U64 _t589 = 0;
                (void)_t589;
                Range *_t590 = Range_new(_t589, self->count);
                (void)_t590;
                ;
                U64 _t591; { U64 *_hp = (U64 *)Range_len(_t590); _t591 = *_hp; free(_hp); }
                (void)_t591;
                Range_delete(_t590, &(Bool){1});
                Bool _wcond588; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi587}, &(U64){_t591}); _wcond588 = *_hp; free(_hp); }
                (void)_wcond588;
                ;
                if (_wcond588) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t592 = 0;
                (void)_t592;
                Range *_t593 = Range_new(_t592, self->count);
                (void)_t593;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t593, _fi587); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t593, &(Bool){1});
                U64 _t594 = 1;
                (void)_t594;
                U64 _t595 = U64_add(_fi587, _t594);
                (void)_t595;
                ;
                _fi587 = _t595;
                ;
                U64 *_t596 = malloc(sizeof(U64)); *_t596 = U64_mul(i, self->key_size);
                (void)_t596;
                ;
                void *_t597 = ptr_add(self->key_data, DEREF(_t596));
                (void)_t597;
                Bool _t598 = 0;
                (void)_t598;
                dyn_call_delete(&self->key_type, _t597, &(Bool){_t598});
                U64_delete(_t596, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    Bool _t615; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t615 = *_hp; free(_hp); }
    (void)_t615;
    Bool _t616 = Bool_not(_t615);
    (void)_t616;
    ;
    if (_t616) {
        {
            U64 _fi599 = 0;
            (void)_fi599;
            while (1) {
                U64 _t601 = 0;
                (void)_t601;
                Range *_t602 = Range_new(_t601, self->count);
                (void)_t602;
                ;
                U64 _t603; { U64 *_hp = (U64 *)Range_len(_t602); _t603 = *_hp; free(_hp); }
                (void)_t603;
                Range_delete(_t602, &(Bool){1});
                Bool _wcond600; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi599}, &(U64){_t603}); _wcond600 = *_hp; free(_hp); }
                (void)_wcond600;
                ;
                if (_wcond600) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t604 = 0;
                (void)_t604;
                Range *_t605 = Range_new(_t604, self->count);
                (void)_t605;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t605, _fi599); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t605, &(Bool){1});
                U64 _t606 = 1;
                (void)_t606;
                U64 _t607 = U64_add(_fi599, _t606);
                (void)_t607;
                ;
                _fi599 = _t607;
                ;
                U64 *_t608 = malloc(sizeof(U64)); *_t608 = U64_mul(i, self->val_size);
                (void)_t608;
                ;
                void *_t609 = ptr_add(self->val_data, DEREF(_t608));
                (void)_t609;
                Bool _t610 = 0;
                (void)_t610;
                dyn_call_delete(&self->val_type, _t609, &(Bool){_t610});
                U64_delete(_t608, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->key_data);
    free(self->val_data);
    Bool _t617; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t617 = *_hp; free(_hp); }
    (void)_t617;
    Bool _t618 = Bool_not(_t617);
    (void)_t618;
    ;
    if (_t618) {
        Bool _t611 = 0;
        (void)_t611;
        Str_delete(&self->key_type, &(Bool){_t611});
        ;
    }
    ;
    Bool _t619; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t619 = *_hp; free(_hp); }
    (void)_t619;
    Bool _t620 = Bool_not(_t619);
    (void)_t620;
    ;
    if (_t620) {
        Bool _t612 = 0;
        (void)_t612;
        Str_delete(&self->val_type, &(Bool){_t612});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Map * Map_clone(Map * self) {
    (void)self;
    U64 _t638 = U64_mul(self->cap, self->key_size);
    (void)_t638;
    U8 *new_keys = malloc(_t638);
    (void)new_keys;
    ;
    U64 _t639 = U64_mul(self->cap, self->val_size);
    (void)_t639;
    U8 *new_vals = malloc(_t639);
    (void)new_vals;
    ;
    {
        U64 _fi621 = 0;
        (void)_fi621;
        while (1) {
            U64 _t623 = 0;
            (void)_t623;
            Range *_t624 = Range_new(_t623, self->count);
            (void)_t624;
            ;
            U64 _t625; { U64 *_hp = (U64 *)Range_len(_t624); _t625 = *_hp; free(_hp); }
            (void)_t625;
            Range_delete(_t624, &(Bool){1});
            Bool _wcond622; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi621}, &(U64){_t625}); _wcond622 = *_hp; free(_hp); }
            (void)_wcond622;
            ;
            if (_wcond622) {
            } else {
                ;
                break;
            }
            ;
            U64 _t626 = 0;
            (void)_t626;
            Range *_t627 = Range_new(_t626, self->count);
            (void)_t627;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t627, _fi621); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t627, &(Bool){1});
            U64 _t628 = 1;
            (void)_t628;
            U64 _t629 = U64_add(_fi621, _t628);
            (void)_t629;
            ;
            _fi621 = _t629;
            ;
            U64 *_t630 = malloc(sizeof(U64)); *_t630 = U64_mul(i, self->key_size);
            (void)_t630;
            void *_t631 = ptr_add(self->key_data, DEREF(_t630));
            (void)_t631;
            void *ck = dyn_call_clone(&self->key_type, _t631);
            (void)ck;
            U64_delete(_t630, &(Bool){1});
            U64 *_t632 = malloc(sizeof(U64)); *_t632 = U64_mul(i, self->key_size);
            (void)_t632;
            void *_t633 = ptr_add(new_keys, DEREF(_t632));
            (void)_t633;
            memcpy(_t633, ck, self->key_size);
            U64_delete(_t632, &(Bool){1});
            free(ck);
            U64 *_t634 = malloc(sizeof(U64)); *_t634 = U64_mul(i, self->val_size);
            (void)_t634;
            void *_t635 = ptr_add(self->val_data, DEREF(_t634));
            (void)_t635;
            void *cv = dyn_call_clone(&self->val_type, _t635);
            (void)cv;
            U64_delete(_t634, &(Bool){1});
            U64 *_t636 = malloc(sizeof(U64)); *_t636 = U64_mul(i, self->val_size);
            (void)_t636;
            ;
            void *_t637 = ptr_add(new_vals, DEREF(_t636));
            (void)_t637;
            memcpy(_t637, cv, self->val_size);
            U64_delete(_t636, &(Bool){1});
            free(cv);
        }
        ;
    }
    Map *_t640 = malloc(sizeof(Map));
    _t640->key_data = new_keys;
    _t640->val_data = new_vals;
    _t640->count = self->count;
    _t640->cap = self->cap;
    _t640->key_size = self->key_size;
    { Str *_ca = Str_clone(&self->key_type); _t640->key_type = *_ca; free(_ca); }
    _t640->val_size = self->val_size;
    { Str *_ca = Str_clone(&self->val_type); _t640->val_type = *_ca; free(_ca); }
    (void)_t640;
    return _t640;
}

U64 *Map_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Map);
    return r;
}

