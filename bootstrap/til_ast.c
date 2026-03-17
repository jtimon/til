#include "til_ast.h"

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

