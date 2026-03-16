Array * Array_new(Str * elem_type, U64 * elem_size, U64 * cap) {
    (void)elem_type;
    (void)elem_size;
    (void)cap;
    void *_t403 = calloc(DEREF(cap), DEREF(elem_size));
    (void)_t403;
    U64 _t404 = U64_clone(cap);
    (void)_t404;
    U64 _t405 = U64_clone(elem_size);
    (void)_t405;
    Array *_t406 = malloc(sizeof(Array));
    _t406->data = _t403;
    _t406->cap = _t404;
    _t406->elem_size = _t405;
    { Str *_ca = Str_clone(elem_type); _t406->elem_type = *_ca; free(_ca); }
    (void)_t406;
    ;
    ;
    return _t406;
}

U64 * Array_len(Array * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t421; { Bool *_hp = (Bool *)U64_gte(i, &self->cap); _t421 = *_hp; free(_hp); }
    (void)_t421;
    if (_t421) {
        Str *_t407 = Str_lit("Str", 3ULL);
        (void)_t407;
        U64 _t408; { U64 *_hp = (U64 *)Str_size(); _t408 = *_hp; free(_hp); }
        (void)_t408;
        U64 _t409 = 5;
        (void)_t409;
        Array *_va7 = Array_new(_t407, &(U64){_t408}, &(U64){_t409});
        (void)_va7;
        Str_delete(_t407, &(Bool){1});
        ;
        ;
        U64 _t410 = 0;
        (void)_t410;
        Str *_t411 = Str_lit("Array.get: index ", 17ULL);
        (void)_t411;
        Array_set(_va7, &(U64){_t410}, _t411);
        ;
        U64 _t412 = 1;
        (void)_t412;
        Str *_t413 = U64_to_str(DEREF(i));
        (void)_t413;
        Array_set(_va7, &(U64){_t412}, _t413);
        ;
        U64 _t414 = 2;
        (void)_t414;
        Str *_t415 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t415;
        Array_set(_va7, &(U64){_t414}, _t415);
        ;
        U64 _t416 = 3;
        (void)_t416;
        Str *_t417 = U64_to_str(self->cap);
        (void)_t417;
        Array_set(_va7, &(U64){_t416}, _t417);
        ;
        U64 _t418 = 4;
        (void)_t418;
        Str *_t419 = Str_lit(")", 1ULL);
        (void)_t419;
        Array_set(_va7, &(U64){_t418}, _t419);
        ;
        Str *_t420 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/array.til:19:19", 62ULL);
        (void)_t420;
        panic(_t420, _va7);
        Str_delete(_t420, &(Bool){1});
    }
    ;
    U64 *_t422 = malloc(sizeof(U64)); *_t422 = U64_mul(DEREF(i), self->elem_size);
    (void)_t422;
    void *_t423 = ptr_add(self->data, DEREF(_t422));
    (void)_t423;
    U64_delete(_t422, &(Bool){1});
    return _t423;
}

void Array_set(Array * self, U64 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t438; { Bool *_hp = (Bool *)U64_gte(i, &self->cap); _t438 = *_hp; free(_hp); }
    (void)_t438;
    if (_t438) {
        Str *_t424 = Str_lit("Str", 3ULL);
        (void)_t424;
        U64 _t425; { U64 *_hp = (U64 *)Str_size(); _t425 = *_hp; free(_hp); }
        (void)_t425;
        U64 _t426 = 5;
        (void)_t426;
        Array *_va8 = Array_new(_t424, &(U64){_t425}, &(U64){_t426});
        (void)_va8;
        Str_delete(_t424, &(Bool){1});
        ;
        ;
        U64 _t427 = 0;
        (void)_t427;
        Str *_t428 = Str_lit("Array.set: index ", 17ULL);
        (void)_t428;
        Array_set(_va8, &(U64){_t427}, _t428);
        ;
        U64 _t429 = 1;
        (void)_t429;
        Str *_t430 = U64_to_str(DEREF(i));
        (void)_t430;
        Array_set(_va8, &(U64){_t429}, _t430);
        ;
        U64 _t431 = 2;
        (void)_t431;
        Str *_t432 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t432;
        Array_set(_va8, &(U64){_t431}, _t432);
        ;
        U64 _t433 = 3;
        (void)_t433;
        Str *_t434 = U64_to_str(self->cap);
        (void)_t434;
        Array_set(_va8, &(U64){_t433}, _t434);
        ;
        U64 _t435 = 4;
        (void)_t435;
        Str *_t436 = Str_lit(")", 1ULL);
        (void)_t436;
        Array_set(_va8, &(U64){_t435}, _t436);
        ;
        Str *_t437 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/array.til:27:19", 62ULL);
        (void)_t437;
        panic(_t437, _va8);
        Str_delete(_t437, &(Bool){1});
    }
    ;
    U64 *_t439 = malloc(sizeof(U64)); *_t439 = U64_mul(DEREF(i), self->elem_size);
    (void)_t439;
    void *_t440 = ptr_add(self->data, DEREF(_t439));
    (void)_t440;
    Bool _t441 = 0;
    (void)_t441;
    dyn_call_delete(&self->elem_type, _t440, &(Bool){_t441});
    U64_delete(_t439, &(Bool){1});
    ;
    U64 *_t442 = malloc(sizeof(U64)); *_t442 = U64_mul(DEREF(i), self->elem_size);
    (void)_t442;
    void *_t443 = ptr_add(self->data, DEREF(_t442));
    (void)_t443;
    memcpy(_t443, val, self->elem_size);
    U64_delete(_t442, &(Bool){1});
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    {
        U64 _fi444 = 0;
        (void)_fi444;
        while (1) {
            U64 _t446 = 0;
            (void)_t446;
            Range *_t447 = Range_new(_t446, self->cap);
            (void)_t447;
            ;
            U64 _t448; { U64 *_hp = (U64 *)Range_len(_t447); _t448 = *_hp; free(_hp); }
            (void)_t448;
            Range_delete(_t447, &(Bool){1});
            Bool _wcond445; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi444}, &(U64){_t448}); _wcond445 = *_hp; free(_hp); }
            (void)_wcond445;
            ;
            if (_wcond445) {
            } else {
                ;
                break;
            }
            ;
            U64 _t449 = 0;
            (void)_t449;
            Range *_t450 = Range_new(_t449, self->cap);
            (void)_t450;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t450, _fi444); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t450, &(Bool){1});
            U64 _t451 = 1;
            (void)_t451;
            U64 _t452 = U64_add(_fi444, _t451);
            (void)_t452;
            ;
            _fi444 = _t452;
            ;
            U64 *_t453 = malloc(sizeof(U64)); *_t453 = U64_mul(i, self->elem_size);
            (void)_t453;
            ;
            void *_t454 = ptr_add(self->data, DEREF(_t453));
            (void)_t454;
            Bool _t455 = 0;
            (void)_t455;
            dyn_call_delete(&self->elem_type, _t454, &(Bool){_t455});
            U64_delete(_t453, &(Bool){1});
            ;
        }
        ;
    }
    free(self->data);
    Bool _t456 = 0;
    (void)_t456;
    Str_delete(&self->elem_type, &(Bool){_t456});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U64 _t470 = U64_mul(self->cap, self->elem_size);
    (void)_t470;
    U8 *new_data = malloc(_t470);
    (void)new_data;
    ;
    {
        U64 _fi457 = 0;
        (void)_fi457;
        while (1) {
            U64 _t459 = 0;
            (void)_t459;
            Range *_t460 = Range_new(_t459, self->cap);
            (void)_t460;
            ;
            U64 _t461; { U64 *_hp = (U64 *)Range_len(_t460); _t461 = *_hp; free(_hp); }
            (void)_t461;
            Range_delete(_t460, &(Bool){1});
            Bool _wcond458; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi457}, &(U64){_t461}); _wcond458 = *_hp; free(_hp); }
            (void)_wcond458;
            ;
            if (_wcond458) {
            } else {
                ;
                break;
            }
            ;
            U64 _t462 = 0;
            (void)_t462;
            Range *_t463 = Range_new(_t462, self->cap);
            (void)_t463;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t463, _fi457); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t463, &(Bool){1});
            U64 _t464 = 1;
            (void)_t464;
            U64 _t465 = U64_add(_fi457, _t464);
            (void)_t465;
            ;
            _fi457 = _t465;
            ;
            U64 *_t466 = malloc(sizeof(U64)); *_t466 = U64_mul(i, self->elem_size);
            (void)_t466;
            void *_t467 = ptr_add(self->data, DEREF(_t466));
            (void)_t467;
            void *cloned = dyn_call_clone(&self->elem_type, _t467);
            (void)cloned;
            U64_delete(_t466, &(Bool){1});
            U64 *_t468 = malloc(sizeof(U64)); *_t468 = U64_mul(i, self->elem_size);
            (void)_t468;
            ;
            void *_t469 = ptr_add(new_data, DEREF(_t468));
            (void)_t469;
            memcpy(_t469, cloned, self->elem_size);
            U64_delete(_t468, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Array *_t471 = malloc(sizeof(Array));
    _t471->data = new_data;
    _t471->cap = self->cap;
    _t471->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t471->elem_type = *_ca; free(_ca); }
    (void)_t471;
    return _t471;
}

U64 *Array_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Array);
    return r;
}

