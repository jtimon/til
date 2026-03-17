#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

#include "til_core.h"
#include "til_array.h"
#include "til_set.h"
#include "til_str.h"
#include "til_vec.h"
#include "til_til.h"

#include "ext.h"

Token * til_tokenize(Str *, Str *);
U32 til_tok_count(void);
Expr * til_parse(Token *, U32, Str *);
Str * til_parse_mode(void);
Expr * expr_null(void);
Bool expr_is_null(Expr *);
I32 expr_get_tag(Expr *);
Str * expr_get_str_val(Expr *);
Expr * expr_get_child(Expr *, U32);
U32 expr_nchildren(Expr *);
void expr_set_core(Expr *);
void expr_swap_children(Expr *, Vec *);
Vec * expr_vec_new(void);
void expr_vec_push(Vec *, Expr *);
Expr * expr_vec_get(Vec *, U32);
U32 expr_vec_count(Vec *);
Mode * til_mode_none(void);
Mode * til_mode_resolve(Str *);
Bool til_mode_eq(Mode *, Mode *);
Mode * til_mode_test(void);
Mode * til_mode_pure(void);
Mode * til_mode_pura(void);
Str * til_mode_name(Mode *);
Str * til_mode_auto_import(Mode *);
Bool til_mode_is_lib(Mode *);
Bool til_mode_is_lib_output(Mode *);
TypeScope * tscope_new(TypeScope *);
I32 til_init_declarations(Expr *, TypeScope *);
I32 til_type_check(Expr *, TypeScope *, Mode *);
void til_precomp(Expr *);
void til_scavenge(Expr *, Mode *, Bool);
I32 til_interpret_v(Expr *, Mode *, Bool, Str *, Str *, Str *, Str *, Vec *);
I32 til_build(Expr *, Mode *, Bool, Str *, Str *);
I32 til_build_header(Expr *, Str *);
I32 til_build_til_binding(Expr *, Str *, Str *);
I32 til_compile_c(Str *, Str *, Str *, Str *, Str *);
I32 til_compile_lib(Str *, Str *, Str *, Str *, Str *);
void til_ast_print(Expr *, U32);
Str * til_bin_dir(void);
Str * til_realpath(Str *);
Str * til_str_left(Str *, U64);
I32 til_system(Str *);
Set * til_set_new(void);
Bool til_set_has(Set *, Str *);
void til_set_add(Set *, Str *);

Str *Str_lit(const char *s, unsigned long long len);
void print_single(Str *s);
void print_flush();

U64 * U8_size(void);
Bool * U8_neq(U8 * a, U8 * b);
Str * I32_to_str(I32 * val);
U64 * I32_size(void);
Bool * I32_gt(I32 * a, I32 * b);
U64 * U32_size(void);
Bool * U32_lt(U32 * a, U32 * b);
Str * U64_to_str(U64 val);
U64 * U64_size(void);
Bool * U64_lt(U64 * a, U64 * b);
Bool * U64_gt(U64 * a, U64 * b);
Bool * U64_lte(U64 * a, U64 * b);
Bool * U64_gte(U64 * a, U64 * b);
Str * I64_to_str(I64 * val);
U64 * I64_size(void);
Bool * I64_lt(I64 * a, I64 * b);
Bool * I64_gt(I64 * a, I64 * b);
Bool * I64_neq(I64 * a, I64 * b);
Bool * I64_gte(I64 * a, I64 * b);
Range * Range_new(U64 start, U64 end);
U64 * Range_len(Range * self);
U64 * Range_get(Range * self, U64 i);
Range * Range_clone(Range * val);
void Range_delete(Range * self, Bool * call_free);
U64 * Range_size(void);
I64 * Bool_cmp(Bool * a, Bool * b);
U64 * Bool_size(void);
void println(Array * parts);
Str * format(Array * parts);
void panic(Str * loc_str, Array * parts);
Array * Array_new(Str * elem_type, U64 * elem_size, U64 * cap);
U64 * Array_len(Array * self);
void * Array_get(Array * self, U64 * i);
void Array_set(Array * self, U64 * i, void * val);
void Array_delete(Array * self, Bool * call_free);
Array * Array_clone(Array * self);
U64 * Array_size(void);
void Set_delete(Set * self, Bool * call_free);
Set * Set_clone(Set * self);
U64 * Set_size(void);
U64 * Str_len(Str * self);
U8 * Str_get(Str * self, U64 * i);
I64 * Str_cmp(Str * a, Str * b);
Str * Str_concat(Str * a, Str * b);
Str * Str_clone(Str * val);
void Str_delete(Str * self, Bool * call_free);
Str * Str_substr(Str * s, U64 * start, U64 * n);
Bool * Str_starts_with(Str * a, Str * b);
Bool * Str_ends_with(Str * a, Str * b);
Bool * Str_is_empty(Str * self);
I64 * Str_rfind(Str * self, Str * needle);
U64 * Str_size(void);
Bool * Str_eq(Str * a, Str * b);
Vec * Vec_new(Str * elem_type, U64 * elem_size);
U64 * Vec_len(Vec * self);
void Vec_push(Vec * self, void * val);
void * Vec_get(Vec * self, U64 * i);
void Vec_delete(Vec * self, Bool * call_free);
Vec * Vec_clone(Vec * self);
U64 * Vec_size(void);
Expr * Expr_clone(Expr * self);
void Expr_delete(Expr * self, Bool * call_free);
U64 * Expr_size(void);
Token * Token_clone(Token * self);
void Token_delete(Token * self, Bool * call_free);
U64 * Token_size(void);
Mode * Mode_clone(Mode * self);
void Mode_delete(Mode * self, Bool * call_free);
U64 * Mode_size(void);
TypeScope * TypeScope_clone(TypeScope * self);
void TypeScope_delete(TypeScope * self, Bool * call_free);
U64 * TypeScope_size(void);
Vec * extract_imports(void * body);
I32 * resolve_imports(Vec * import_paths, Str * base_dir, void * resolved_set, void * stack, void * merged, Str * lib_dir);
void usage(void);
void mark_core(void * e);

void dyn_call_delete(Str *type_name, void *val, void *arg2);
void *dyn_call_clone(Str *type_name, void *val);

#define DEREF(p) (*(p ? p : (fprintf(stderr, "panic: null deref\n"), exit(1), p)))
#define TIL_CAP_LIT ULLONG_MAX
Str *Str_lit(const char *s, unsigned long long len) {
    Str *r = malloc(sizeof(Str));
    r->c_str = (U8 *)s;
    r->count = len;
    r->cap = TIL_CAP_LIT;
    return r;
}
void print_single(Str *s) {
    fwrite(s->c_str, 1, (size_t)s->count, stdout);
}
void print_flush() {
    putchar('\n');
}

static I64 *_t1871;
static I64 *_t1872;
static I64 *_t1873;
static U64 *CAP_LIT;
static I64 *_t1874;
static I64 *_t1875;
static I64 *_t1876;
static U64 *CAP_VIEW;
static I32 *NODE_BODY;
static I32 *NODE_LITERAL_STR;
static I32 *NODE_LITERAL_NUM;
static I32 *NODE_LITERAL_BOOL;
static I32 *NODE_LITERAL_NULL;
static I32 *NODE_IDENT;
static I32 *NODE_DECL;
static I32 *NODE_ASSIGN;
static I32 *NODE_FCALL;
static I32 *NODE_FUNC_DEF;
static I32 *NODE_STRUCT_DEF;
static I32 *NODE_ENUM_DEF;
static I32 *NODE_FIELD_ACCESS;
static I32 *NODE_FIELD_ASSIGN;
static I32 *NODE_RETURN;
static I32 *NODE_IF;
static I32 *NODE_WHILE;
static I32 *NODE_FOR_IN;
static I32 *NODE_NAMED_ARG;
static I32 *NODE_BREAK;
static I32 *NODE_CONTINUE;
static I32 *NODE_MAP_LIT;
static I32 *NODE_SET_LIT;
static I32 *NODE_SWITCH;
static I32 *NODE_CASE;

U64 *U8_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U8);
    return r;
}

Str * I32_to_str(I32 * val) {
    (void)val;
    I64 _t102 = I32_to_i64(DEREF(val));
    (void)_t102;
    Str *_t103 = I64_to_str(&(I64){_t102});
    (void)_t103;
    ;
    return _t103;
}

U64 *I32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I32);
    return r;
}

U64 *U32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U32);
    return r;
}

Str * U64_to_str(U64 val) {
    (void)val;
    /* TODO: nested func U64_to_str_ext */
    Str *_t164 = U64_to_str_ext(val);
    (void)_t164;
    return _t164;
}

U64 *U64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U64);
    return r;
}

Str * I64_to_str(I64 * val) {
    (void)val;
    I64 _t217 = 0;
    (void)_t217;
    Bool _t218 = I64_eq(DEREF(val), _t217);
    (void)_t218;
    ;
    if (_t218) {
        U64 _t181 = 2;
        (void)_t181;
        U8 *buf = malloc(_t181);
        (void)buf;
        ;
        I64 _t182 = 48;
        (void)_t182;
        U64 _t183 = 1;
        (void)_t183;
        memcpy(buf, &(I64){_t182}, _t183);
        ;
        ;
        U64 *_t184 = malloc(sizeof(U64));
        *_t184 = 1;
        (void)_t184;
        void *_t185 = ptr_add(buf, DEREF(_t184));
        (void)_t185;
        I32 _t186 = 0;
        (void)_t186;
        U64 _t187 = 1;
        (void)_t187;
        memset(_t185, _t186, _t187);
        U64_delete(_t184, &(Bool){1});
        ;
        ;
        I64 _t188 = 1;
        (void)_t188;
        I64 _t189 = 1;
        (void)_t189;
        Str *_t190 = malloc(sizeof(Str));
        _t190->c_str = buf;
        _t190->count = _t188;
        _t190->cap = _t189;
        (void)_t190;
        ;
        ;
        ;
        return _t190;
    }
    ;
    Bool is_neg = 0;
    (void)is_neg;
    I64 v = I64_clone(val);
    (void)v;
    I64 _t219 = 0;
    (void)_t219;
    Bool _t220; { Bool *_hp = (Bool *)I64_lt(val, &(I64){_t219}); _t220 = *_hp; free(_hp); }
    (void)_t220;
    ;
    if (_t220) {
        Bool _t191 = 1;
        (void)_t191;
        is_neg = _t191;
        ;
        I64 _t192 = 0;
        (void)_t192;
        I64 _t193 = I64_sub(_t192, DEREF(val));
        (void)_t193;
        ;
        v = _t193;
        ;
    }
    ;
    U64 ndigits = 0;
    (void)ndigits;
    I64 tmp = I64_clone(&(I64){v});
    (void)tmp;
    while (1) {
        I64 _t195 = 0;
        (void)_t195;
        Bool _wcond194; { Bool *_hp = (Bool *)I64_gt(&(I64){tmp}, &(I64){_t195}); _wcond194 = *_hp; free(_hp); }
        (void)_wcond194;
        ;
        if (_wcond194) {
        } else {
            ;
            break;
        }
        ;
        U64 _t196 = 1;
        (void)_t196;
        U64 _t197 = U64_add(ndigits, _t196);
        (void)_t197;
        ;
        ndigits = _t197;
        ;
        I64 _t198 = 10;
        (void)_t198;
        I64 _t199 = I64_div(tmp, _t198);
        (void)_t199;
        ;
        tmp = _t199;
        ;
    }
    ;
    U64 *total = malloc(sizeof(U64)); *total = U64_clone(&(U64){ndigits});
    (void)total;
    ;
    if (is_neg) {
        U64 _t200 = 1;
        (void)_t200;
        U64 _t201 = U64_add(DEREF(total), _t200);
        (void)_t201;
        ;
        *total = _t201;
        ;
    }
    U64 _t221 = 1;
    (void)_t221;
    U64 _t222 = U64_add(DEREF(total), _t221);
    (void)_t222;
    ;
    U8 *buf = malloc(_t222);
    (void)buf;
    ;
    if (is_neg) {
        I64 _t202 = 45;
        (void)_t202;
        U64 _t203 = 1;
        (void)_t203;
        memcpy(buf, &(I64){_t202}, _t203);
        ;
        ;
    }
    ;
    U64 _t223 = 1;
    (void)_t223;
    U64 *i = malloc(sizeof(U64)); *i = U64_sub(DEREF(total), _t223);
    (void)i;
    ;
    while (1) {
        I64 _t205 = 0;
        (void)_t205;
        Bool _wcond204; { Bool *_hp = (Bool *)I64_gt(&(I64){v}, &(I64){_t205}); _wcond204 = *_hp; free(_hp); }
        (void)_wcond204;
        ;
        if (_wcond204) {
        } else {
            ;
            break;
        }
        ;
        I64 _t206 = 10;
        (void)_t206;
        I64 _t207 = I64_mod(v, _t206);
        (void)_t207;
        ;
        I64 _t208 = 48;
        (void)_t208;
        I64 _t209 = I64_add(_t207, _t208);
        (void)_t209;
        ;
        ;
        void *_t210 = ptr_add(buf, DEREF(i));
        (void)_t210;
        U8 _t211 = I64_to_u8(_t209);
        (void)_t211;
        ;
        U64 _t212 = 1;
        (void)_t212;
        memcpy(_t210, &(U8){_t211}, _t212);
        ;
        ;
        I64 _t213 = 10;
        (void)_t213;
        I64 _t214 = I64_div(v, _t213);
        (void)_t214;
        ;
        v = _t214;
        ;
        U64 _t215 = 1;
        (void)_t215;
        U64 _t216 = U64_sub(DEREF(i), _t215);
        (void)_t216;
        ;
        *i = _t216;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    void *_t224 = ptr_add(buf, DEREF(total));
    (void)_t224;
    I32 _t225 = 0;
    (void)_t225;
    U64 _t226 = 1;
    (void)_t226;
    memset(_t224, _t225, _t226);
    ;
    ;
    U64 _t227 = U64_clone(total);
    (void)_t227;
    U64 _t228 = U64_clone(total);
    (void)_t228;
    U64_delete(total, &(Bool){1});
    Str *_t229 = malloc(sizeof(Str));
    _t229->c_str = buf;
    _t229->count = _t227;
    _t229->cap = _t228;
    (void)_t229;
    ;
    ;
    return _t229;
}

U64 *I64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I64);
    return r;
}

Range * Range_new(U64 start, U64 end) {
    (void)start;
    (void)end;
    U64 _t252 = U64_clone(&(U64){start});
    (void)_t252;
    U64 _t253 = U64_clone(&(U64){end});
    (void)_t253;
    Range *_t254 = malloc(sizeof(Range));
    _t254->start = _t252;
    _t254->end = _t253;
    (void)_t254;
    ;
    ;
    return _t254;
}

U64 * Range_len(Range * self) {
    (void)self;
    Bool _t256; { Bool *_hp = (Bool *)U64_lte(&self->start, &self->end); _t256 = *_hp; free(_hp); }
    (void)_t256;
    if (_t256) {
        U64 _t255 = U64_sub(self->end, self->start);
        (void)_t255;
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t255; return _r; }
    }
    ;
    U64 _t257 = U64_sub(self->start, self->end);
    (void)_t257;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t257; return _r; }
}

U64 * Range_get(Range * self, U64 i) {
    (void)self;
    (void)i;
    Bool _t259; { Bool *_hp = (Bool *)U64_lte(&self->start, &self->end); _t259 = *_hp; free(_hp); }
    (void)_t259;
    if (_t259) {
        U64 _t258 = U64_add(self->start, i);
        (void)_t258;
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t258; return _r; }
    }
    ;
    U64 _t260 = U64_sub(self->start, i);
    (void)_t260;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t260; return _r; }
}

Range * Range_clone(Range * val) {
    (void)val;
    Range *_t261 = malloc(sizeof(Range));
    _t261->start = val->start;
    _t261->end = val->end;
    (void)_t261;
    return _t261;
}

void Range_delete(Range * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    if (DEREF(call_free)) {
        free(self);
    }
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t269 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t269;
    if (_t269) {
        I64 _t265 = 0;
        (void)_t265;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t265; return _r; }
    }
    ;
    if (DEREF(b)) {
        I64 _t266 = 0;
        (void)_t266;
        I64 _t267 = 1;
        (void)_t267;
        I64 _t268 = I64_sub(_t266, _t267);
        (void)_t268;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t268; return _r; }
    }
    I64 _t270 = 1;
    (void)_t270;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t270; return _r; }
}

U64 *Bool_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Bool);
    return r;
}

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
    if (!self) return;
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

void Set_delete(Set * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
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
    if (!self) return;
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

Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    void *_t1067 = malloc(DEREF(elem_size));
    (void)_t1067;
    U64 _t1068 = 0;
    (void)_t1068;
    I64 _t1069 = 1;
    (void)_t1069;
    U64 _t1070 = U64_clone(elem_size);
    (void)_t1070;
    Vec *_t1071 = malloc(sizeof(Vec));
    _t1071->data = _t1067;
    _t1071->count = _t1068;
    _t1071->cap = _t1069;
    _t1071->elem_size = _t1070;
    { Str *_ca = Str_clone(elem_type); _t1071->elem_type = *_ca; free(_ca); }
    (void)_t1071;
    ;
    ;
    ;
    return _t1071;
}

U64 * Vec_len(Vec * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    (void)val;
    Bool _t1076 = U64_eq(self->count, self->cap);
    (void)_t1076;
    if (_t1076) {
        U64 _t1072 = 2;
        (void)_t1072;
        U64 new_cap = U64_mul(self->cap, _t1072);
        (void)new_cap;
        ;
        U64 _t1073 = U64_mul(new_cap, self->elem_size);
        (void)_t1073;
        void *_t1074 = realloc(self->data, _t1073);
        (void)_t1074;
        ;
        self->data = _t1074;
        U64 _t1075 = U64_clone(&(U64){new_cap});
        (void)_t1075;
        ;
        self->cap = _t1075;
        ;
    }
    ;
    U64 *_t1077 = malloc(sizeof(U64)); *_t1077 = U64_mul(self->count, self->elem_size);
    (void)_t1077;
    void *_t1078 = ptr_add(self->data, DEREF(_t1077));
    (void)_t1078;
    memcpy(_t1078, val, self->elem_size);
    U64_delete(_t1077, &(Bool){1});
    free(val);
    U64 _t1079 = 1;
    (void)_t1079;
    U64 _t1080 = U64_add(self->count, _t1079);
    (void)_t1080;
    ;
    self->count = _t1080;
    ;
}

void * Vec_get(Vec * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t1095; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t1095 = *_hp; free(_hp); }
    (void)_t1095;
    if (_t1095) {
        Str *_t1081 = Str_lit("Str", 3ULL);
        (void)_t1081;
        U64 _t1082; { U64 *_hp = (U64 *)Str_size(); _t1082 = *_hp; free(_hp); }
        (void)_t1082;
        U64 _t1083 = 5;
        (void)_t1083;
        Array *_va18 = Array_new(_t1081, &(U64){_t1082}, &(U64){_t1083});
        (void)_va18;
        Str_delete(_t1081, &(Bool){1});
        ;
        ;
        U64 _t1084 = 0;
        (void)_t1084;
        Str *_t1085 = Str_lit("Vec.get: index ", 15ULL);
        (void)_t1085;
        Array_set(_va18, &(U64){_t1084}, _t1085);
        ;
        U64 _t1086 = 1;
        (void)_t1086;
        Str *_t1087 = U64_to_str(DEREF(i));
        (void)_t1087;
        Array_set(_va18, &(U64){_t1086}, _t1087);
        ;
        U64 _t1088 = 2;
        (void)_t1088;
        Str *_t1089 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t1089;
        Array_set(_va18, &(U64){_t1088}, _t1089);
        ;
        U64 _t1090 = 3;
        (void)_t1090;
        Str *_t1091 = U64_to_str(self->count);
        (void)_t1091;
        Array_set(_va18, &(U64){_t1090}, _t1091);
        ;
        U64 _t1092 = 4;
        (void)_t1092;
        Str *_t1093 = Str_lit(")", 1ULL);
        (void)_t1093;
        Array_set(_va18, &(U64){_t1092}, _t1093);
        ;
        Str *_t1094 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/vec.til:31:19", 60ULL);
        (void)_t1094;
        panic(_t1094, _va18);
        Str_delete(_t1094, &(Bool){1});
    }
    ;
    U64 *_t1096 = malloc(sizeof(U64)); *_t1096 = U64_mul(DEREF(i), self->elem_size);
    (void)_t1096;
    void *_t1097 = ptr_add(self->data, DEREF(_t1096));
    (void)_t1097;
    U64_delete(_t1096, &(Bool){1});
    return _t1097;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1111; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1111 = *_hp; free(_hp); }
    (void)_t1111;
    Bool _t1112 = Bool_not(_t1111);
    (void)_t1112;
    ;
    if (_t1112) {
        {
            U64 _fi1098 = 0;
            (void)_fi1098;
            while (1) {
                U64 _t1100 = 0;
                (void)_t1100;
                Range *_t1101 = Range_new(_t1100, self->count);
                (void)_t1101;
                ;
                U64 _t1102; { U64 *_hp = (U64 *)Range_len(_t1101); _t1102 = *_hp; free(_hp); }
                (void)_t1102;
                Range_delete(_t1101, &(Bool){1});
                Bool _wcond1099; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1098}, &(U64){_t1102}); _wcond1099 = *_hp; free(_hp); }
                (void)_wcond1099;
                ;
                if (_wcond1099) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t1103 = 0;
                (void)_t1103;
                Range *_t1104 = Range_new(_t1103, self->count);
                (void)_t1104;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t1104, _fi1098); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t1104, &(Bool){1});
                U64 _t1105 = 1;
                (void)_t1105;
                U64 _t1106 = U64_add(_fi1098, _t1105);
                (void)_t1106;
                ;
                _fi1098 = _t1106;
                ;
                U64 *_t1107 = malloc(sizeof(U64)); *_t1107 = U64_mul(i, self->elem_size);
                (void)_t1107;
                ;
                void *_t1108 = ptr_add(self->data, DEREF(_t1107));
                (void)_t1108;
                Bool _t1109 = 0;
                (void)_t1109;
                dyn_call_delete(&self->elem_type, _t1108, &(Bool){_t1109});
                U64_delete(_t1107, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t1113; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1113 = *_hp; free(_hp); }
    (void)_t1113;
    Bool _t1114 = Bool_not(_t1113);
    (void)_t1114;
    ;
    if (_t1114) {
        Bool _t1110 = 0;
        (void)_t1110;
        Str_delete(&self->elem_type, &(Bool){_t1110});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U64 _t1129 = U64_mul(self->cap, self->elem_size);
    (void)_t1129;
    U8 *new_data = malloc(_t1129);
    (void)new_data;
    ;
    Bool _t1130; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1130 = *_hp; free(_hp); }
    (void)_t1130;
    Bool _t1131 = Bool_not(_t1130);
    (void)_t1131;
    ;
    if (_t1131) {
        {
            U64 _fi1115 = 0;
            (void)_fi1115;
            while (1) {
                U64 _t1117 = 0;
                (void)_t1117;
                Range *_t1118 = Range_new(_t1117, self->count);
                (void)_t1118;
                ;
                U64 _t1119; { U64 *_hp = (U64 *)Range_len(_t1118); _t1119 = *_hp; free(_hp); }
                (void)_t1119;
                Range_delete(_t1118, &(Bool){1});
                Bool _wcond1116; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1115}, &(U64){_t1119}); _wcond1116 = *_hp; free(_hp); }
                (void)_wcond1116;
                ;
                if (_wcond1116) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t1120 = 0;
                (void)_t1120;
                Range *_t1121 = Range_new(_t1120, self->count);
                (void)_t1121;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t1121, _fi1115); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t1121, &(Bool){1});
                U64 _t1122 = 1;
                (void)_t1122;
                U64 _t1123 = U64_add(_fi1115, _t1122);
                (void)_t1123;
                ;
                _fi1115 = _t1123;
                ;
                U64 *_t1124 = malloc(sizeof(U64)); *_t1124 = U64_mul(i, self->elem_size);
                (void)_t1124;
                void *_t1125 = ptr_add(self->data, DEREF(_t1124));
                (void)_t1125;
                void *cloned = dyn_call_clone(&self->elem_type, _t1125);
                (void)cloned;
                U64_delete(_t1124, &(Bool){1});
                U64 *_t1126 = malloc(sizeof(U64)); *_t1126 = U64_mul(i, self->elem_size);
                (void)_t1126;
                ;
                void *_t1127 = ptr_add(new_data, DEREF(_t1126));
                (void)_t1127;
                memcpy(_t1127, cloned, self->elem_size);
                U64_delete(_t1126, &(Bool){1});
                free(cloned);
            }
            ;
        }
    } else {
        U64 _t1128 = U64_mul(self->count, self->elem_size);
        (void)_t1128;
        memcpy(new_data, self->data, _t1128);
        ;
    }
    ;
    Vec *_t1132 = malloc(sizeof(Vec));
    _t1132->data = new_data;
    _t1132->count = self->count;
    _t1132->cap = self->cap;
    _t1132->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t1132->elem_type = *_ca; free(_ca); }
    (void)_t1132;
    return _t1132;
}

void Expr_delete(Expr * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    if (DEREF(call_free)) {
        free(self);
    }
}

void Token_delete(Token * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    if (DEREF(call_free)) {
        free(self);
    }
}

void Mode_delete(Mode * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    if (DEREF(call_free)) {
        free(self);
    }
}

void TypeScope_delete(TypeScope * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    if (DEREF(call_free)) {
        free(self);
    }
}

#include "til_core.c"
#include "til_array.c"
#include "til_set.c"
#include "til_str.c"
#include "til_vec.c"
#include "til_til.c"

void dyn_call_delete(Str *type_name, void *val, void *arg2) {
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) { U8_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) { I32_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) { U32_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) { U64_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) { I64_delete(val, arg2); return; }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) { Range_delete(val, arg2); return; }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) { Bool_delete(val, arg2); return; }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0) { Array_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Set", 3ULL) == 0) { Set_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) { Str_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0) { Vec_delete(val, arg2); return; }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) { Expr_delete(val, arg2); return; }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) { Token_delete(val, arg2); return; }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Mode", 4ULL) == 0) { Mode_delete(val, arg2); return; }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TypeScope", 9ULL) == 0) { TypeScope_delete(val, arg2); return; }
    fprintf(stderr, "dyn_call: unknown type for delete\n");
    exit(1);
}

void *dyn_call_clone(Str *type_name, void *val) {
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) { U8 *_r = malloc(sizeof(U8)); *_r = U8_clone(val); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) { I32 *_r = malloc(sizeof(I32)); *_r = I32_clone(val); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) { U32 *_r = malloc(sizeof(U32)); *_r = U32_clone(val); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) { U64 *_r = malloc(sizeof(U64)); *_r = U64_clone(val); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = I64_clone(val); return _r; }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) return (void *)Range_clone(val);
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) { Bool *_r = malloc(sizeof(Bool)); *_r = Bool_clone(val); return _r; }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0) return (void *)Array_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Set", 3ULL) == 0) return (void *)Set_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) return (void *)Str_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0) return (void *)Vec_clone(val);
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) return (void *)Expr_clone(val);
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) return (void *)Token_clone(val);
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Mode", 4ULL) == 0) return (void *)Mode_clone(val);
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TypeScope", 9ULL) == 0) return (void *)TypeScope_clone(val);
    fprintf(stderr, "dyn_call: unknown type for clone\n");
    exit(1);
}

