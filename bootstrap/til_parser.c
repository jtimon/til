#include "til_parser.h"

Parser * Parser_clone(Parser * self) {
    (void)self;
    U64 _t2968 = U64_clone(&self->pos);
    (void)_t2968;
    Parser *_t2969 = malloc(sizeof(Parser));
    { Vec *_ca = Vec_clone(&self->tokens); _t2969->tokens = *_ca; free(_ca); }
    _t2969->pos = _t2968;
    { Str *_ca = Str_clone(&self->path); _t2969->path = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->fn_sig_decls); _t2969->fn_sig_decls = *_ca; free(_ca); }
    (void)_t2969;
    ;
    return _t2969;
}

void Parser_delete(Parser * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t2970 = 0;
    (void)_t2970;
    Vec_delete(&self->tokens, &(Bool){_t2970});
    ;
    Bool _t2971 = 0;
    (void)_t2971;
    U64_delete(&self->pos, &(Bool){_t2971});
    ;
    Bool _t2972 = 0;
    (void)_t2972;
    Str_delete(&self->path, &(Bool){_t2972});
    ;
    Bool _t2973 = 0;
    (void)_t2973;
    Vec_delete(&self->fn_sig_decls, &(Bool){_t2973});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *Parser_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Parser);
    return r;
}

Token * peek(Parser * p) {
    (void)p;
    I64 _t2975 = U64_to_i64(p->pos);
    (void)_t2975;
    U64 *_t2976 = malloc(sizeof(U64)); *_t2976 = I64_to_u64(_t2975);
    (void)_t2976;
    ;
    Token *t = Vec_get(&p->tokens, _t2976);
    (void)t;
    U64_delete(_t2976, &(Bool){1});
    return t;
}

Token * advance(Parser * p) {
    (void)p;
    I64 _t2979 = U64_to_i64(p->pos);
    (void)_t2979;
    U64 *_t2980 = malloc(sizeof(U64)); *_t2980 = I64_to_u64(_t2979);
    (void)_t2980;
    ;
    Token *t = Vec_get(&p->tokens, _t2980);
    (void)t;
    Bool _t2981; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Eof()); _t2981 = *_hp; free(_hp); }
    (void)_t2981;
    Bool _t2982 = Bool_not(_t2981);
    (void)_t2982;
    ;
    if (_t2982) {
        U64 _t2977 = 1;
        (void)_t2977;
        U64 _t2978 = U64_add(p->pos, _t2977);
        (void)_t2978;
        ;
        p->pos = _t2978;
        ;
    }
    ;
    U64_delete(_t2980, &(Bool){1});
    return t;
}

Bool check(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Bool _t2983; { Bool *_hp = (Bool *)TokenType_eq(&peek(p)->type, type); _t2983 = *_hp; free(_hp); }
    (void)_t2983;
    return _t2983;
}

Token * expect_token(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Token *t = peek(p);
    (void)t;
    Bool _t3008; { Bool *_hp = (Bool *)TokenType_eq(&t->type, type); _t3008 = *_hp; free(_hp); }
    (void)_t3008;
    Bool _t3009 = Bool_not(_t3008);
    (void)_t3009;
    ;
    if (_t3009) {
        Str *_t2984 = Str_lit("Str", 3ULL);
        (void)_t2984;
        U64 _t2985; { U64 *_hp = (U64 *)Str_size(); _t2985 = *_hp; free(_hp); }
        (void)_t2985;
        U64 _t2986 = 10;
        (void)_t2986;
        Array *_va57 = Array_new(_t2984, &(U64){_t2985}, &(U64){_t2986});
        (void)_va57;
        Str_delete(_t2984, &(Bool){1});
        ;
        ;
        U64 _t2987 = 0;
        (void)_t2987;
        Str *_t2988 = Str_clone(&p->path);
        (void)_t2988;
        Array_set(_va57, &(U64){_t2987}, _t2988);
        ;
        U64 _t2989 = 1;
        (void)_t2989;
        Str *_t2990 = Str_lit(":", 1ULL);
        (void)_t2990;
        Array_set(_va57, &(U64){_t2989}, _t2990);
        ;
        U64 _t2991 = 2;
        (void)_t2991;
        Str *_t2992 = U32_to_str(&t->line);
        (void)_t2992;
        Array_set(_va57, &(U64){_t2991}, _t2992);
        ;
        U64 _t2993 = 3;
        (void)_t2993;
        Str *_t2994 = Str_lit(":", 1ULL);
        (void)_t2994;
        Array_set(_va57, &(U64){_t2993}, _t2994);
        ;
        U64 _t2995 = 4;
        (void)_t2995;
        Str *_t2996 = U32_to_str(&t->col);
        (void)_t2996;
        Array_set(_va57, &(U64){_t2995}, _t2996);
        ;
        U64 _t2997 = 5;
        (void)_t2997;
        Str *_t2998 = Str_lit(": expected '", 12ULL);
        (void)_t2998;
        Array_set(_va57, &(U64){_t2997}, _t2998);
        ;
        U64 _t2999 = 6;
        (void)_t2999;
        Str *_t3000 = tok_name(type);
        (void)_t3000;
        Array_set(_va57, &(U64){_t2999}, _t3000);
        ;
        U64 _t3001 = 7;
        (void)_t3001;
        Str *_t3002 = Str_lit("', found '", 10ULL);
        (void)_t3002;
        Array_set(_va57, &(U64){_t3001}, _t3002);
        ;
        U64 _t3003 = 8;
        (void)_t3003;
        Str *_t3004 = Str_clone(&t->text);
        (void)_t3004;
        Array_set(_va57, &(U64){_t3003}, _t3004);
        ;
        U64 _t3005 = 9;
        (void)_t3005;
        Str *_t3006 = Str_lit("'", 1ULL);
        (void)_t3006;
        Array_set(_va57, &(U64){_t3005}, _t3006);
        ;
        Str *_t3007 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:34:15", 63ULL);
        (void)_t3007;
        panic(_t3007, _va57);
        Str_delete(_t3007, &(Bool){1});
    }
    ;
    Token *_t3010 = advance(p);
    (void)_t3010;
    return _t3010;
}

Str * expect_text(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Token *t = peek(p);
    (void)t;
    Bool _t3035; { Bool *_hp = (Bool *)TokenType_eq(&t->type, type); _t3035 = *_hp; free(_hp); }
    (void)_t3035;
    Bool _t3036 = Bool_not(_t3035);
    (void)_t3036;
    ;
    if (_t3036) {
        Str *_t3011 = Str_lit("Str", 3ULL);
        (void)_t3011;
        U64 _t3012; { U64 *_hp = (U64 *)Str_size(); _t3012 = *_hp; free(_hp); }
        (void)_t3012;
        U64 _t3013 = 10;
        (void)_t3013;
        Array *_va58 = Array_new(_t3011, &(U64){_t3012}, &(U64){_t3013});
        (void)_va58;
        Str_delete(_t3011, &(Bool){1});
        ;
        ;
        U64 _t3014 = 0;
        (void)_t3014;
        Str *_t3015 = Str_clone(&p->path);
        (void)_t3015;
        Array_set(_va58, &(U64){_t3014}, _t3015);
        ;
        U64 _t3016 = 1;
        (void)_t3016;
        Str *_t3017 = Str_lit(":", 1ULL);
        (void)_t3017;
        Array_set(_va58, &(U64){_t3016}, _t3017);
        ;
        U64 _t3018 = 2;
        (void)_t3018;
        Str *_t3019 = U32_to_str(&t->line);
        (void)_t3019;
        Array_set(_va58, &(U64){_t3018}, _t3019);
        ;
        U64 _t3020 = 3;
        (void)_t3020;
        Str *_t3021 = Str_lit(":", 1ULL);
        (void)_t3021;
        Array_set(_va58, &(U64){_t3020}, _t3021);
        ;
        U64 _t3022 = 4;
        (void)_t3022;
        Str *_t3023 = U32_to_str(&t->col);
        (void)_t3023;
        Array_set(_va58, &(U64){_t3022}, _t3023);
        ;
        U64 _t3024 = 5;
        (void)_t3024;
        Str *_t3025 = Str_lit(": expected '", 12ULL);
        (void)_t3025;
        Array_set(_va58, &(U64){_t3024}, _t3025);
        ;
        U64 _t3026 = 6;
        (void)_t3026;
        Str *_t3027 = tok_name(type);
        (void)_t3027;
        Array_set(_va58, &(U64){_t3026}, _t3027);
        ;
        U64 _t3028 = 7;
        (void)_t3028;
        Str *_t3029 = Str_lit("', found '", 10ULL);
        (void)_t3029;
        Array_set(_va58, &(U64){_t3028}, _t3029);
        ;
        U64 _t3030 = 8;
        (void)_t3030;
        Str *_t3031 = Str_clone(&t->text);
        (void)_t3031;
        Array_set(_va58, &(U64){_t3030}, _t3031);
        ;
        U64 _t3032 = 9;
        (void)_t3032;
        Str *_t3033 = Str_lit("'", 1ULL);
        (void)_t3033;
        Array_set(_va58, &(U64){_t3032}, _t3033);
        ;
        Str *_t3034 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:44:15", 63ULL);
        (void)_t3034;
        panic(_t3034, _va58);
        Str_delete(_t3034, &(Bool){1});
    }
    ;
    Str *text = Str_clone(&t->text);
    (void)text;
    Token *_t3037 = advance(p);
    (void)_t3037;
    return text;
}

U32 peek_line(Parser * p) {
    (void)p;
    return peek(p)->line;
}

U32 peek_col(Parser * p) {
    (void)p;
    return peek(p)->col;
}

Str * parse_fn_signature(Parser * p, U32 line, U32 col) {
    (void)p;
    (void)line;
    (void)col;
    Bool _t3071 = check(p, TokenType_LParen());
    (void)_t3071;
    Bool _t3072 = Bool_not(_t3071);
    (void)_t3072;
    ;
    if (_t3072) {
        Str *_t3038 = Str_lit("", 0ULL);
        (void)_t3038;
        ;
        return _t3038;
    }
    ;
    Token *_t3073 = advance(p);
    (void)_t3073;
    Str *_t3074 = Str_lit("Str", 3ULL);
    (void)_t3074;
    U64 _t3075; { U64 *_hp = (U64 *)Str_size(); _t3075 = *_hp; free(_hp); }
    (void)_t3075;
    Vec *ptypes = Vec_new(_t3074, &(U64){_t3075});
    (void)ptypes;
    Str_delete(_t3074, &(Bool){1});
    ;
    Str *_t3076 = Str_lit("Bool", 4ULL);
    (void)_t3076;
    U64 _t3077; { U64 *_hp = (U64 *)Bool_size(); _t3077 = *_hp; free(_hp); }
    (void)_t3077;
    Vec *pmuts = Vec_new(_t3076, &(U64){_t3077});
    (void)pmuts;
    Str_delete(_t3076, &(Bool){1});
    ;
    while (1) {
        Bool _t3043 = check(p, TokenType_RParen());
        (void)_t3043;
        Bool _t3044 = check(p, TokenType_Eof());
        (void)_t3044;
        Bool _t3045 = Bool_not(_t3043);
        (void)_t3045;
        ;
        Bool _t3046 = Bool_not(_t3044);
        (void)_t3046;
        ;
        Bool _wcond3039 = Bool_and(_t3045, _t3046);
        (void)_wcond3039;
        ;
        ;
        if (_wcond3039) {
        } else {
            ;
            break;
        }
        ;
        Bool is_mut = 0;
        (void)is_mut;
        Bool _t3047 = check(p, TokenType_KwMut());
        (void)_t3047;
        if (_t3047) {
            Token *_t3040 = advance(p);
            (void)_t3040;
            Bool _t3041 = 1;
            (void)_t3041;
            is_mut = _t3041;
            ;
        }
        ;
        Str *ptype = expect_text(p, TokenType_Ident());
        (void)ptype;
        Vec_push(ptypes, ptype);
        Vec_push(pmuts, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = is_mut; _oa; }));
        Bool _t3048 = check(p, TokenType_Comma());
        (void)_t3048;
        if (_t3048) {
            Token *_t3042 = advance(p);
            (void)_t3042;
        }
        ;
    }
    Token *_t3078 = expect_token(p, TokenType_RParen());
    (void)_t3078;
    Str *return_type = Str_lit("", 0ULL);
    (void)return_type;
    Bool _t3079 = check(p, TokenType_KwReturns());
    (void)_t3079;
    if (_t3079) {
        Token *_t3049 = advance(p);
        (void)_t3049;
        return_type = expect_text(p, TokenType_Ident());
    }
    ;
    Str *name = Str_lit("_Fn", 3ULL);
    (void)name;
    {
        U64 _t3057 = 0;
        (void)_t3057;
        U64 _t3058; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3058 = *_hp; free(_hp); }
        (void)_t3058;
        Range *_fc3050 = Range_new(_t3057, _t3058);
        (void)_fc3050;
        ;
        ;
        U64 _fi3050 = 0;
        (void)_fi3050;
        while (1) {
            U64 _t3053; { U64 *_hp = (U64 *)Range_len(_fc3050); _t3053 = *_hp; free(_hp); }
            (void)_t3053;
            Bool _wcond3051; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3050}, &(U64){_t3053}); _wcond3051 = *_hp; free(_hp); }
            (void)_wcond3051;
            ;
            if (_wcond3051) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc3050, _fi3050);
            (void)i;
            U64 _t3054 = 1;
            (void)_t3054;
            U64 _t3055 = U64_add(_fi3050, _t3054);
            (void)_t3055;
            ;
            _fi3050 = _t3055;
            ;
            Str *_t3056 = Str_lit("_", 1ULL);
            (void)_t3056;
            name = Str_concat(name, _t3056);
            Str_delete(_t3056, &(Bool){1});
            Bool *m = Vec_get(pmuts, i);
            (void)m;
            if (DEREF(m)) {
                Str *_t3052 = Str_lit("mut_", 4ULL);
                (void)_t3052;
                name = Str_concat(name, _t3052);
                Str_delete(_t3052, &(Bool){1});
            }
            Str *t = Vec_get(ptypes, i);
            (void)t;
            name = Str_concat(name, t);
            U64_delete(i, &(Bool){1});
        }
        Range_delete(_fc3050, &(Bool){1});
        ;
    }
    U64 _t3080; { U64 *_hp = (U64 *)Str_len(return_type); _t3080 = *_hp; free(_hp); }
    (void)_t3080;
    U64 _t3081 = 0;
    (void)_t3081;
    Bool _t3082; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3080}, &(U64){_t3081}); _t3082 = *_hp; free(_hp); }
    (void)_t3082;
    ;
    ;
    if (_t3082) {
        Str *_t3059 = Str_lit("_ret_", 5ULL);
        (void)_t3059;
        name = Str_concat(name, _t3059);
        Str_delete(_t3059, &(Bool){1});
        name = Str_concat(name, return_type);
    }
    ;
    Str *_t3083 = Str_lit("Param", 5ULL);
    (void)_t3083;
    U64 _t3084; { U64 *_hp = (U64 *)Param_size(); _t3084 = *_hp; free(_hp); }
    (void)_t3084;
    Str *_t3085 = Str_lit("Str", 3ULL);
    (void)_t3085;
    U64 _t3086; { U64 *_hp = (U64 *)Str_size(); _t3086 = *_hp; free(_hp); }
    (void)_t3086;
    Str *_t3087 = Str_lit("Expr", 4ULL);
    (void)_t3087;
    U64 _t3088; { U64 *_hp = (U64 *)Expr_size(); _t3088 = *_hp; free(_hp); }
    (void)_t3088;
    I64 _t3089 = 0;
    (void)_t3089;
    I64 _t3090 = 1;
    (void)_t3090;
    I64 _t3091 = I64_sub(_t3089, _t3090);
    (void)_t3091;
    ;
    ;
    I64 _t3092 = 0;
    (void)_t3092;
    I64 _t3093 = 1;
    (void)_t3093;
    I64 _t3094 = I64_sub(_t3092, _t3093);
    (void)_t3094;
    ;
    ;
    U32 _t3095 = 0;
    (void)_t3095;
    I32 _t3096 = I64_to_i32(_t3091);
    (void)_t3096;
    ;
    I32 _t3097 = I64_to_i32(_t3094);
    (void)_t3097;
    ;
    Bool _t3098 = 0;
    (void)_t3098;
    Bool _t3099 = 0;
    (void)_t3099;
    FunctionDef *fd = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(FuncType_Func()); fd->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3083, &(U64){_t3084}); fd->params = *_ca; free(_ca); }
    fd->nparam = _t3095;
    { Map *_ca = Map_new(_t3085, &(U64){_t3086}, _t3087, &(U64){_t3088}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3096;
    fd->kwargs_index = _t3097;
    fd->return_is_ref = _t3098;
    fd->return_is_shallow = _t3099;
    (void)fd;
    Str_delete(_t3083, &(Bool){1});
    ;
    Str_delete(_t3085, &(Bool){1});
    ;
    Str_delete(_t3087, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    U64 _t3100; { U64 *_hp = (U64 *)Str_len(return_type); _t3100 = *_hp; free(_hp); }
    (void)_t3100;
    U64 _t3101 = 0;
    (void)_t3101;
    Bool _t3102; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3100}, &(U64){_t3101}); _t3102 = *_hp; free(_hp); }
    (void)_t3102;
    ;
    ;
    if (_t3102) {
        FuncType_delete(&fd->func_type, &(Bool){0});
        { FuncType *_fa = FuncType_clone(FuncType_Func()); fd->func_type = *_fa; free(_fa); }
    } else {
        FuncType_delete(&fd->func_type, &(Bool){0});
        { FuncType *_fa = FuncType_clone(FuncType_Proc()); fd->func_type = *_fa; free(_fa); }
    }
    ;
    Str_delete(&fd->return_type, &(Bool){0});
    { Str *_fa = Str_clone(return_type); fd->return_type = *_fa; free(_fa); }
    Str_delete(return_type, &(Bool){1});
    Bool _t3103 = 0;
    (void)_t3103;
    fd->return_is_ref = _t3103;
    ;
    Bool _t3104 = 0;
    (void)_t3104;
    fd->return_is_shallow = _t3104;
    ;
    I64 _t3105 = 0;
    (void)_t3105;
    I64 _t3106 = 1;
    (void)_t3106;
    I64 _t3107 = I64_sub(_t3105, _t3106);
    (void)_t3107;
    ;
    ;
    I32 _t3108 = I64_to_i32(_t3107);
    (void)_t3108;
    ;
    fd->variadic_index = _t3108;
    ;
    I64 _t3109 = 0;
    (void)_t3109;
    I64 _t3110 = 1;
    (void)_t3110;
    I64 _t3111 = I64_sub(_t3109, _t3110);
    (void)_t3111;
    ;
    ;
    I32 _t3112 = I64_to_i32(_t3111);
    (void)_t3112;
    ;
    fd->kwargs_index = _t3112;
    ;
    {
        U64 _t3069 = 0;
        (void)_t3069;
        U64 _t3070; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3070 = *_hp; free(_hp); }
        (void)_t3070;
        Range *_fc3060 = Range_new(_t3069, _t3070);
        (void)_fc3060;
        ;
        ;
        U64 _fi3060 = 0;
        (void)_fi3060;
        while (1) {
            U64 _t3062; { U64 *_hp = (U64 *)Range_len(_fc3060); _t3062 = *_hp; free(_hp); }
            (void)_t3062;
            Bool _wcond3061; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3060}, &(U64){_t3062}); _wcond3061 = *_hp; free(_hp); }
            (void)_wcond3061;
            ;
            if (_wcond3061) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc3060, _fi3060);
            (void)i;
            U64 _t3063 = 1;
            (void)_t3063;
            U64 _t3064 = U64_add(_fi3060, _t3063);
            (void)_t3064;
            ;
            _fi3060 = _t3064;
            ;
            Str *t = Vec_get(ptypes, i);
            (void)t;
            Bool *m = Vec_get(pmuts, i);
            (void)m;
            Bool _t3065 = Bool_clone(m);
            (void)_t3065;
            Bool _t3066 = 0;
            (void)_t3066;
            Bool _t3067 = 0;
            (void)_t3067;
            Param *_t3068 = malloc(sizeof(Param));
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t3068->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(t); _t3068->ptype = *_ca; free(_ca); }
            _t3068->is_mut = _t3065;
            _t3068->is_own = _t3066;
            _t3068->is_shallow = _t3067;
            (void)_t3068;
            ;
            ;
            ;
            U64_delete(i, &(Bool){1});
            Vec_push(&fd->params, _t3068);
        }
        Range_delete(_fc3060, &(Bool){1});
        ;
    }
    Vec_delete(pmuts, &(Bool){1});
    Vec_delete(ptypes, &(Bool){1});
    U64 _t3113; { U64 *_hp = (U64 *)Vec_len(&fd->params); _t3113 = *_hp; free(_hp); }
    (void)_t3113;
    I64 _t3114 = U64_to_i64(_t3113);
    (void)_t3114;
    ;
    U32 _t3115 = I64_to_u32(_t3114);
    (void)_t3115;
    ;
    fd->nparam = _t3115;
    ;
    ExprData *_t3116 = ExprData_FuncDef(fd);
    (void)_t3116;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *sig = Expr_new(_t3116, line, col, &p->path);
    (void)sig;
    ExprData_delete(_t3116, &(Bool){1});
    Bool _t3117 = 0;
    (void)_t3117;
    Bool _t3118 = 0;
    (void)_t3118;
    Bool _t3119 = 0;
    (void)_t3119;
    Bool _t3120 = 0;
    (void)_t3120;
    I32 _t3121 = 0;
    (void)_t3121;
    I32 _t3122 = 0;
    (void)_t3122;
    Declaration *_t3123 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(name); _t3123->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t3123->explicit_type = *_ca; free(_ca); }
    _t3123->is_mut = _t3117;
    _t3123->is_namespace = _t3118;
    _t3123->is_ref = _t3119;
    _t3123->is_own = _t3120;
    _t3123->field_offset = _t3121;
    _t3123->field_size = _t3122;
    _t3123->field_struct_def = NULL;
    _t3123->fn_sig = NULL;
    (void)_t3123;
    ;
    ;
    ;
    ;
    ;
    ;
    ExprData *_t3124 = ExprData_Decl(_t3123);
    (void)_t3124;
    Declaration_delete(_t3123, &(Bool){1});
    Expr *decl = Expr_new(_t3124, line, col, &p->path);
    (void)decl;
    ExprData_delete(_t3124, &(Bool){1});
    Expr_add_child(decl, sig);
    Vec_push(&p->fn_sig_decls, decl);
    return name;
}

Expr * parse_block(Parser * p) {
    (void)p;
    U32 _t3131 = peek_line(p);
    (void)_t3131;
    U32 _t3132 = peek_col(p);
    (void)_t3132;
    Expr *body = Expr_new(ExprData_Body(), _t3131, _t3132, &p->path);
    (void)body;
    ;
    ;
    while (1) {
        Bool _t3126 = check(p, TokenType_RBrace());
        (void)_t3126;
        Bool _t3127 = check(p, TokenType_Eof());
        (void)_t3127;
        Bool _t3128 = Bool_not(_t3126);
        (void)_t3128;
        ;
        Bool _t3129 = Bool_not(_t3127);
        (void)_t3129;
        ;
        Bool _wcond3125 = Bool_and(_t3128, _t3129);
        (void)_wcond3125;
        ;
        ;
        if (_wcond3125) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t3130 = parse_statement(p);
        (void)_t3130;
        Expr_add_child(body, _t3130);
    }
    Token *_t3133 = expect_token(p, TokenType_RBrace());
    (void)_t3133;
    return body;
}

Expr * parse_func_def(Parser * p) {
    (void)p;
    U32 kw_line = peek_line(p);
    (void)kw_line;
    U32 kw_col = peek_col(p);
    (void)kw_col;
    Token *kw = advance(p);
    (void)kw;
    FuncType *ft = FuncType_clone(FuncType_Func());
    (void)ft;
    {
        TokenType *_sw3134 = TokenType_clone(&kw->type);
        (void)_sw3134;
        Bool _t3146; { Bool *_hp = (Bool *)TokenType_eq(_sw3134, TokenType_KwFunc()); _t3146 = *_hp; free(_hp); }
        (void)_t3146;
        if (_t3146) {
            ft = FuncType_clone(FuncType_Func());
        } else {
            Bool _t3145; { Bool *_hp = (Bool *)TokenType_eq(_sw3134, TokenType_KwProc()); _t3145 = *_hp; free(_hp); }
            (void)_t3145;
            if (_t3145) {
                ft = FuncType_clone(FuncType_Proc());
            } else {
                Bool _t3144; { Bool *_hp = (Bool *)TokenType_eq(_sw3134, TokenType_KwTest()); _t3144 = *_hp; free(_hp); }
                (void)_t3144;
                if (_t3144) {
                    ft = FuncType_clone(FuncType_Test());
                } else {
                    Bool _t3143; { Bool *_hp = (Bool *)TokenType_eq(_sw3134, TokenType_KwMacro()); _t3143 = *_hp; free(_hp); }
                    (void)_t3143;
                    if (_t3143) {
                        ft = FuncType_clone(FuncType_Macro());
                    } else {
                        Bool _t3142; { Bool *_hp = (Bool *)TokenType_eq(_sw3134, TokenType_KwExtFunc()); _t3142 = *_hp; free(_hp); }
                        (void)_t3142;
                        if (_t3142) {
                            ft = FuncType_clone(FuncType_ExtFunc());
                        } else {
                            Bool _t3141; { Bool *_hp = (Bool *)TokenType_eq(_sw3134, TokenType_KwExtProc()); _t3141 = *_hp; free(_hp); }
                            (void)_t3141;
                            if (_t3141) {
                                ft = FuncType_clone(FuncType_ExtProc());
                            } else {
                                Str *_t3135 = Str_lit("Str", 3ULL);
                                (void)_t3135;
                                U64 _t3136; { U64 *_hp = (U64 *)Str_size(); _t3136 = *_hp; free(_hp); }
                                (void)_t3136;
                                U64 _t3137 = 1;
                                (void)_t3137;
                                Array *_va59 = Array_new(_t3135, &(U64){_t3136}, &(U64){_t3137});
                                (void)_va59;
                                Str_delete(_t3135, &(Bool){1});
                                ;
                                ;
                                U64 _t3138 = 0;
                                (void)_t3138;
                                Str *_t3139 = Str_lit("expected function keyword", 25ULL);
                                (void)_t3139;
                                Array_set(_va59, &(U64){_t3138}, _t3139);
                                ;
                                Str *_t3140 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:150:17", 64ULL);
                                (void)_t3140;
                                panic(_t3140, _va59);
                                Str_delete(_t3140, &(Bool){1});
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
        TokenType_delete(_sw3134, &(Bool){1});
        ;
    }
    Token *_t3324 = expect_token(p, TokenType_LParen());
    (void)_t3324;
    Str *_t3325 = Str_lit("Param", 5ULL);
    (void)_t3325;
    U64 _t3326; { U64 *_hp = (U64 *)Param_size(); _t3326 = *_hp; free(_hp); }
    (void)_t3326;
    Str *_t3327 = Str_lit("Str", 3ULL);
    (void)_t3327;
    U64 _t3328; { U64 *_hp = (U64 *)Str_size(); _t3328 = *_hp; free(_hp); }
    (void)_t3328;
    Str *_t3329 = Str_lit("Expr", 4ULL);
    (void)_t3329;
    U64 _t3330; { U64 *_hp = (U64 *)Expr_size(); _t3330 = *_hp; free(_hp); }
    (void)_t3330;
    I64 _t3331 = 0;
    (void)_t3331;
    I64 _t3332 = 1;
    (void)_t3332;
    I64 _t3333 = I64_sub(_t3331, _t3332);
    (void)_t3333;
    ;
    ;
    I64 _t3334 = 0;
    (void)_t3334;
    I64 _t3335 = 1;
    (void)_t3335;
    I64 _t3336 = I64_sub(_t3334, _t3335);
    (void)_t3336;
    ;
    ;
    U32 _t3337 = 0;
    (void)_t3337;
    I32 _t3338 = I64_to_i32(_t3333);
    (void)_t3338;
    ;
    I32 _t3339 = I64_to_i32(_t3336);
    (void)_t3339;
    ;
    Bool _t3340 = 0;
    (void)_t3340;
    Bool _t3341 = 0;
    (void)_t3341;
    FunctionDef *fd = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(FuncType_Func()); fd->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3325, &(U64){_t3326}); fd->params = *_ca; free(_ca); }
    fd->nparam = _t3337;
    { Map *_ca = Map_new(_t3327, &(U64){_t3328}, _t3329, &(U64){_t3330}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3338;
    fd->kwargs_index = _t3339;
    fd->return_is_ref = _t3340;
    fd->return_is_shallow = _t3341;
    (void)fd;
    Str_delete(_t3325, &(Bool){1});
    ;
    Str_delete(_t3327, &(Bool){1});
    ;
    Str_delete(_t3329, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    FuncType_delete(&fd->func_type, &(Bool){0});
    { FuncType *_fa = FuncType_clone(ft); fd->func_type = *_fa; free(_fa); }
    while (1) {
        Bool _t3264 = check(p, TokenType_RParen());
        (void)_t3264;
        Bool _t3265 = check(p, TokenType_Eof());
        (void)_t3265;
        Bool _t3266 = Bool_not(_t3264);
        (void)_t3266;
        ;
        Bool _t3267 = Bool_not(_t3265);
        (void)_t3267;
        ;
        Bool _wcond3147 = Bool_and(_t3266, _t3267);
        (void)_wcond3147;
        ;
        ;
        if (_wcond3147) {
        } else {
            ;
            break;
        }
        ;
        Bool is_shallow = 0;
        (void)is_shallow;
        Bool _t3268 = check(p, TokenType_KwShallow());
        (void)_t3268;
        if (_t3268) {
            Token *_t3148 = advance(p);
            (void)_t3148;
            Bool _t3149 = 1;
            (void)_t3149;
            is_shallow = _t3149;
            ;
        }
        ;
        Bool is_own = 0;
        (void)is_own;
        Bool _t3269 = check(p, TokenType_KwOwn());
        (void)_t3269;
        if (_t3269) {
            Token *_t3150 = advance(p);
            (void)_t3150;
            Bool _t3151 = 1;
            (void)_t3151;
            is_own = _t3151;
            ;
        }
        ;
        Bool is_mut = 0;
        (void)is_mut;
        Bool _t3270 = check(p, TokenType_KwMut());
        (void)_t3270;
        if (_t3270) {
            Token *_t3152 = advance(p);
            (void)_t3152;
            Bool _t3153 = 1;
            (void)_t3153;
            is_mut = _t3153;
            ;
        }
        ;
        Str *pname = expect_text(p, TokenType_Ident());
        (void)pname;
        Str *nm = Str_lit("", 0ULL);
        (void)nm;
        Str *tp = Str_lit("", 0ULL);
        (void)tp;
        Bool is_variadic = 0;
        (void)is_variadic;
        Bool _t3271 = check(p, TokenType_Colon());
        (void)_t3271;
        Bool _t3272 = Bool_not(_t3271);
        (void)_t3272;
        ;
        if (_t3272) {
            tp = Str_clone(pname);
            nm = Str_lit("", 0ULL);
        } else {
            Token *_t3247 = expect_token(p, TokenType_Colon());
            (void)_t3247;
            Bool _t3248 = check(p, TokenType_DotDotDot());
            (void)_t3248;
            if (_t3248) {
                Token *_t3184 = advance(p);
                (void)_t3184;
                Bool _t3185 = Bool_or(is_own, is_mut);
                (void)_t3185;
                Bool _t3186 = Bool_or(_t3185, is_shallow);
                (void)_t3186;
                ;
                if (_t3186) {
                    Str *_t3154 = Str_lit("Str", 3ULL);
                    (void)_t3154;
                    U64 _t3155; { U64 *_hp = (U64 *)Str_size(); _t3155 = *_hp; free(_hp); }
                    (void)_t3155;
                    U64 _t3156 = 6;
                    (void)_t3156;
                    Array *_va60 = Array_new(_t3154, &(U64){_t3155}, &(U64){_t3156});
                    (void)_va60;
                    Str_delete(_t3154, &(Bool){1});
                    ;
                    ;
                    U64 _t3157 = 0;
                    (void)_t3157;
                    Str *_t3158 = Str_clone(&p->path);
                    (void)_t3158;
                    Array_set(_va60, &(U64){_t3157}, _t3158);
                    ;
                    U64 _t3159 = 1;
                    (void)_t3159;
                    Str *_t3160 = Str_lit(":", 1ULL);
                    (void)_t3160;
                    Array_set(_va60, &(U64){_t3159}, _t3160);
                    ;
                    U32 _t3161 = peek_line(p);
                    (void)_t3161;
                    U64 _t3162 = 2;
                    (void)_t3162;
                    Str *_t3163 = U32_to_str(&(U32){_t3161});
                    (void)_t3163;
                    ;
                    Array_set(_va60, &(U64){_t3162}, _t3163);
                    ;
                    U64 _t3164 = 3;
                    (void)_t3164;
                    Str *_t3165 = Str_lit(":", 1ULL);
                    (void)_t3165;
                    Array_set(_va60, &(U64){_t3164}, _t3165);
                    ;
                    U32 _t3166 = peek_col(p);
                    (void)_t3166;
                    U64 _t3167 = 4;
                    (void)_t3167;
                    Str *_t3168 = U32_to_str(&(U32){_t3166});
                    (void)_t3168;
                    ;
                    Array_set(_va60, &(U64){_t3167}, _t3168);
                    ;
                    U64 _t3169 = 5;
                    (void)_t3169;
                    Str *_t3170 = Str_lit(": kwargs parameter cannot be own/mut/shallow", 44ULL);
                    (void)_t3170;
                    Array_set(_va60, &(U64){_t3169}, _t3170);
                    ;
                    Str *_t3171 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:180:27", 64ULL);
                    (void)_t3171;
                    panic(_t3171, _va60);
                    Str_delete(_t3171, &(Bool){1});
                }
                ;
                I64 _t3187 = 0;
                (void)_t3187;
                I64 _t3188 = 1;
                (void)_t3188;
                I64 _t3189 = I64_sub(_t3187, _t3188);
                (void)_t3189;
                ;
                ;
                I32 _t3190 = I64_to_i32(_t3189);
                (void)_t3190;
                ;
                Bool _t3191; { Bool *_hp = (Bool *)I32_neq(&fd->kwargs_index, &(I32){_t3190}); _t3191 = *_hp; free(_hp); }
                (void)_t3191;
                ;
                if (_t3191) {
                    Str *_t3172 = Str_lit("Str", 3ULL);
                    (void)_t3172;
                    U64 _t3173; { U64 *_hp = (U64 *)Str_size(); _t3173 = *_hp; free(_hp); }
                    (void)_t3173;
                    U64 _t3174 = 1;
                    (void)_t3174;
                    Array *_va61 = Array_new(_t3172, &(U64){_t3173}, &(U64){_t3174});
                    (void)_va61;
                    Str_delete(_t3172, &(Bool){1});
                    ;
                    ;
                    U64 _t3175 = 0;
                    (void)_t3175;
                    Str *_t3176 = Str_lit("only one kwargs parameter is allowed", 36ULL);
                    (void)_t3176;
                    Array_set(_va61, &(U64){_t3175}, _t3176);
                    ;
                    Str *_t3177 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:184:27", 64ULL);
                    (void)_t3177;
                    panic(_t3177, _va61);
                    Str_delete(_t3177, &(Bool){1});
                }
                ;
                I64 _t3192 = 0;
                (void)_t3192;
                I64 _t3193 = 1;
                (void)_t3193;
                I64 _t3194 = I64_sub(_t3192, _t3193);
                (void)_t3194;
                ;
                ;
                I32 _t3195 = I64_to_i32(_t3194);
                (void)_t3195;
                ;
                Bool _t3196; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3195}); _t3196 = *_hp; free(_hp); }
                (void)_t3196;
                ;
                if (_t3196) {
                    Str *_t3178 = Str_lit("Str", 3ULL);
                    (void)_t3178;
                    U64 _t3179; { U64 *_hp = (U64 *)Str_size(); _t3179 = *_hp; free(_hp); }
                    (void)_t3179;
                    U64 _t3180 = 1;
                    (void)_t3180;
                    Array *_va62 = Array_new(_t3178, &(U64){_t3179}, &(U64){_t3180});
                    (void)_va62;
                    Str_delete(_t3178, &(Bool){1});
                    ;
                    ;
                    U64 _t3181 = 0;
                    (void)_t3181;
                    Str *_t3182 = Str_lit("cannot combine variadic and kwargs in the same function", 55ULL);
                    (void)_t3182;
                    Array_set(_va62, &(U64){_t3181}, _t3182);
                    ;
                    Str *_t3183 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:187:27", 64ULL);
                    (void)_t3183;
                    panic(_t3183, _va62);
                    Str_delete(_t3183, &(Bool){1});
                }
                ;
                U64 _t3197; { U64 *_hp = (U64 *)Vec_len(&fd->params); _t3197 = *_hp; free(_hp); }
                (void)_t3197;
                I64 _t3198 = U64_to_i64(_t3197);
                (void)_t3198;
                ;
                I32 _t3199 = I64_to_i32(_t3198);
                (void)_t3199;
                ;
                fd->kwargs_index = _t3199;
                ;
                Bool _t3200 = 1;
                (void)_t3200;
                is_own = _t3200;
                ;
                nm = Str_clone(pname);
                tp = Str_lit("Map", 3ULL);
            } else {
                Bool _t3246 = check(p, TokenType_DotDot());
                (void)_t3246;
                if (_t3246) {
                    Token *_t3231 = advance(p);
                    (void)_t3231;
                    if (is_own) {
                        Str *_t3201 = Str_lit("Str", 3ULL);
                        (void)_t3201;
                        U64 _t3202; { U64 *_hp = (U64 *)Str_size(); _t3202 = *_hp; free(_hp); }
                        (void)_t3202;
                        U64 _t3203 = 1;
                        (void)_t3203;
                        Array *_va63 = Array_new(_t3201, &(U64){_t3202}, &(U64){_t3203});
                        (void)_va63;
                        Str_delete(_t3201, &(Bool){1});
                        ;
                        ;
                        U64 _t3204 = 0;
                        (void)_t3204;
                        Str *_t3205 = Str_lit("variadic param cannot be 'own'", 30ULL);
                        (void)_t3205;
                        Array_set(_va63, &(U64){_t3204}, _t3205);
                        ;
                        Str *_t3206 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:195:35", 64ULL);
                        (void)_t3206;
                        panic(_t3206, _va63);
                        Str_delete(_t3206, &(Bool){1});
                    }
                    if (is_mut) {
                        Str *_t3207 = Str_lit("Str", 3ULL);
                        (void)_t3207;
                        U64 _t3208; { U64 *_hp = (U64 *)Str_size(); _t3208 = *_hp; free(_hp); }
                        (void)_t3208;
                        U64 _t3209 = 1;
                        (void)_t3209;
                        Array *_va64 = Array_new(_t3207, &(U64){_t3208}, &(U64){_t3209});
                        (void)_va64;
                        Str_delete(_t3207, &(Bool){1});
                        ;
                        ;
                        U64 _t3210 = 0;
                        (void)_t3210;
                        Str *_t3211 = Str_lit("variadic param cannot be 'mut'", 30ULL);
                        (void)_t3211;
                        Array_set(_va64, &(U64){_t3210}, _t3211);
                        ;
                        Str *_t3212 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:196:35", 64ULL);
                        (void)_t3212;
                        panic(_t3212, _va64);
                        Str_delete(_t3212, &(Bool){1});
                    }
                    if (is_shallow) {
                        Str *_t3213 = Str_lit("Str", 3ULL);
                        (void)_t3213;
                        U64 _t3214; { U64 *_hp = (U64 *)Str_size(); _t3214 = *_hp; free(_hp); }
                        (void)_t3214;
                        U64 _t3215 = 1;
                        (void)_t3215;
                        Array *_va65 = Array_new(_t3213, &(U64){_t3214}, &(U64){_t3215});
                        (void)_va65;
                        Str_delete(_t3213, &(Bool){1});
                        ;
                        ;
                        U64 _t3216 = 0;
                        (void)_t3216;
                        Str *_t3217 = Str_lit("variadic param cannot be 'shallow'", 34ULL);
                        (void)_t3217;
                        Array_set(_va65, &(U64){_t3216}, _t3217);
                        ;
                        Str *_t3218 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:197:39", 64ULL);
                        (void)_t3218;
                        panic(_t3218, _va65);
                        Str_delete(_t3218, &(Bool){1});
                    }
                    I64 _t3232 = 0;
                    (void)_t3232;
                    I64 _t3233 = 1;
                    (void)_t3233;
                    I64 _t3234 = I64_sub(_t3232, _t3233);
                    (void)_t3234;
                    ;
                    ;
                    I32 _t3235 = I64_to_i32(_t3234);
                    (void)_t3235;
                    ;
                    Bool _t3236; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3235}); _t3236 = *_hp; free(_hp); }
                    (void)_t3236;
                    ;
                    if (_t3236) {
                        Str *_t3219 = Str_lit("Str", 3ULL);
                        (void)_t3219;
                        U64 _t3220; { U64 *_hp = (U64 *)Str_size(); _t3220 = *_hp; free(_hp); }
                        (void)_t3220;
                        U64 _t3221 = 1;
                        (void)_t3221;
                        Array *_va66 = Array_new(_t3219, &(U64){_t3220}, &(U64){_t3221});
                        (void)_va66;
                        Str_delete(_t3219, &(Bool){1});
                        ;
                        ;
                        U64 _t3222 = 0;
                        (void)_t3222;
                        Str *_t3223 = Str_lit("only one variadic param allowed", 31ULL);
                        (void)_t3223;
                        Array_set(_va66, &(U64){_t3222}, _t3223);
                        ;
                        Str *_t3224 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:198:63", 64ULL);
                        (void)_t3224;
                        panic(_t3224, _va66);
                        Str_delete(_t3224, &(Bool){1});
                    }
                    ;
                    I64 _t3237 = 0;
                    (void)_t3237;
                    I64 _t3238 = 1;
                    (void)_t3238;
                    I64 _t3239 = I64_sub(_t3237, _t3238);
                    (void)_t3239;
                    ;
                    ;
                    I32 _t3240 = I64_to_i32(_t3239);
                    (void)_t3240;
                    ;
                    Bool _t3241; { Bool *_hp = (Bool *)I32_neq(&fd->kwargs_index, &(I32){_t3240}); _t3241 = *_hp; free(_hp); }
                    (void)_t3241;
                    ;
                    if (_t3241) {
                        Str *_t3225 = Str_lit("Str", 3ULL);
                        (void)_t3225;
                        U64 _t3226; { U64 *_hp = (U64 *)Str_size(); _t3226 = *_hp; free(_hp); }
                        (void)_t3226;
                        U64 _t3227 = 1;
                        (void)_t3227;
                        Array *_va67 = Array_new(_t3225, &(U64){_t3226}, &(U64){_t3227});
                        (void)_va67;
                        Str_delete(_t3225, &(Bool){1});
                        ;
                        ;
                        U64 _t3228 = 0;
                        (void)_t3228;
                        Str *_t3229 = Str_lit("cannot combine variadic and kwargs in the same function", 55ULL);
                        (void)_t3229;
                        Array_set(_va67, &(U64){_t3228}, _t3229);
                        ;
                        Str *_t3230 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:200:27", 64ULL);
                        (void)_t3230;
                        panic(_t3230, _va67);
                        Str_delete(_t3230, &(Bool){1});
                    }
                    ;
                    U64 _t3242; { U64 *_hp = (U64 *)Vec_len(&fd->params); _t3242 = *_hp; free(_hp); }
                    (void)_t3242;
                    I64 _t3243 = U64_to_i64(_t3242);
                    (void)_t3243;
                    ;
                    I32 _t3244 = I64_to_i32(_t3243);
                    (void)_t3244;
                    ;
                    fd->variadic_index = _t3244;
                    ;
                    Bool _t3245 = 1;
                    (void)_t3245;
                    is_variadic = _t3245;
                    ;
                    tp = expect_text(p, TokenType_Ident());
                    nm = Str_clone(pname);
                } else {
                    tp = expect_text(p, TokenType_Ident());
                    nm = Str_clone(pname);
                }
                ;
            }
            ;
        }
        ;
        Str_delete(pname, &(Bool){1});
        Str *_t3273 = Str_lit("Fn", 2ULL);
        (void)_t3273;
        Bool _t3274; { Bool *_hp = (Bool *)Str_eq(tp, _t3273); _t3274 = *_hp; free(_hp); }
        (void)_t3274;
        Str_delete(_t3273, &(Bool){1});
        if (_t3274) {
            U32 _t3249 = peek_line(p);
            (void)_t3249;
            U32 _t3250 = peek_col(p);
            (void)_t3250;
            Str *syn_name = parse_fn_signature(p, _t3249, _t3250);
            (void)syn_name;
            ;
            ;
            U64 _t3251; { U64 *_hp = (U64 *)Str_len(syn_name); _t3251 = *_hp; free(_hp); }
            (void)_t3251;
            U64 _t3252 = 0;
            (void)_t3252;
            Bool _t3253; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3251}, &(U64){_t3252}); _t3253 = *_hp; free(_hp); }
            (void)_t3253;
            ;
            ;
            if (_t3253) {
                tp = Str_clone(syn_name);
            }
            ;
            Str_delete(syn_name, &(Bool){1});
        }
        ;
        Bool has_default = 0;
        (void)has_default;
        Bool _t3275 = check(p, TokenType_Eq());
        (void)_t3275;
        if (_t3275) {
            Token *_t3254 = advance(p);
            (void)_t3254;
            Expr *def_expr = parse_expression(p);
            (void)def_expr;
            Str *_t3255 = Str_clone(nm);
            (void)_t3255;
            Map_set(&fd->param_defaults, _t3255, def_expr);
            Bool _t3256 = 1;
            (void)_t3256;
            has_default = _t3256;
            ;
        }
        ;
        I64 _t3276 = 0;
        (void)_t3276;
        I64 _t3277 = 1;
        (void)_t3277;
        I64 _t3278 = I64_sub(_t3276, _t3277);
        (void)_t3278;
        ;
        ;
        I32 _t3279 = I64_to_i32(_t3278);
        (void)_t3279;
        ;
        Bool _t3280; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3279}); _t3280 = *_hp; free(_hp); }
        (void)_t3280;
        ;
        Bool _t3281 = Bool_not(is_variadic);
        (void)_t3281;
        ;
        Bool _t3282 = Bool_and(_t3280, _t3281);
        (void)_t3282;
        ;
        ;
        Bool _t3283 = Bool_not(has_default);
        (void)_t3283;
        ;
        Bool _t3284 = Bool_and(_t3282, _t3283);
        (void)_t3284;
        ;
        ;
        if (_t3284) {
            Str *_t3257 = Str_lit("Str", 3ULL);
            (void)_t3257;
            U64 _t3258; { U64 *_hp = (U64 *)Str_size(); _t3258 = *_hp; free(_hp); }
            (void)_t3258;
            U64 _t3259 = 1;
            (void)_t3259;
            Array *_va68 = Array_new(_t3257, &(U64){_t3258}, &(U64){_t3259});
            (void)_va68;
            Str_delete(_t3257, &(Bool){1});
            ;
            ;
            U64 _t3260 = 0;
            (void)_t3260;
            Str *_t3261 = Str_lit("positional param not allowed after variadic", 43ULL);
            (void)_t3261;
            Array_set(_va68, &(U64){_t3260}, _t3261);
            ;
            Str *_t3262 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:227:19", 64ULL);
            (void)_t3262;
            panic(_t3262, _va68);
            Str_delete(_t3262, &(Bool){1});
        }
        ;
        Bool _t3285 = Bool_clone(&(Bool){is_mut});
        (void)_t3285;
        ;
        Bool _t3286 = Bool_clone(&(Bool){is_own});
        (void)_t3286;
        ;
        Bool _t3287 = Bool_clone(&(Bool){is_shallow});
        (void)_t3287;
        ;
        Param *_t3288 = malloc(sizeof(Param));
        { Str *_ca = Str_clone(nm); _t3288->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(tp); _t3288->ptype = *_ca; free(_ca); }
        _t3288->is_mut = _t3285;
        _t3288->is_own = _t3286;
        _t3288->is_shallow = _t3287;
        (void)_t3288;
        ;
        ;
        ;
        Str_delete(nm, &(Bool){1});
        Str_delete(tp, &(Bool){1});
        Vec_push(&fd->params, _t3288);
        Bool _t3289 = check(p, TokenType_Comma());
        (void)_t3289;
        if (_t3289) {
            Token *_t3263 = advance(p);
            (void)_t3263;
        }
        ;
    }
    Token *_t3342 = expect_token(p, TokenType_RParen());
    (void)_t3342;
    Bool _t3343 = check(p, TokenType_KwReturns());
    (void)_t3343;
    if (_t3343) {
        Token *_t3295 = advance(p);
        (void)_t3295;
        Bool _t3296 = check(p, TokenType_KwRef());
        (void)_t3296;
        if (_t3296) {
            Token *_t3290 = advance(p);
            (void)_t3290;
            Bool _t3291 = 1;
            (void)_t3291;
            fd->return_is_ref = _t3291;
            ;
        } else {
            Bool _t3294 = check(p, TokenType_KwShallow());
            (void)_t3294;
            if (_t3294) {
                Token *_t3292 = advance(p);
                (void)_t3292;
                Bool _t3293 = 1;
                (void)_t3293;
                fd->return_is_shallow = _t3293;
                ;
            }
            ;
        }
        ;
        Str_delete(&fd->return_type, &(Bool){0});
        { Str *_fa = expect_text(p, TokenType_Ident()); fd->return_type = *_fa; free(_fa); }
    }
    ;
    U64 _t3344; { U64 *_hp = (U64 *)Vec_len(&fd->params); _t3344 = *_hp; free(_hp); }
    (void)_t3344;
    I64 _t3345 = U64_to_i64(_t3344);
    (void)_t3345;
    ;
    U32 _t3346 = I64_to_u32(_t3345);
    (void)_t3346;
    ;
    fd->nparam = _t3346;
    ;
    ExprData *_t3347 = ExprData_FuncDef(fd);
    (void)_t3347;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *def = Expr_new(_t3347, kw_line, kw_col, &p->path);
    (void)def;
    ExprData_delete(_t3347, &(Bool){1});
    Bool _t3348 = check(p, TokenType_LBrace());
    (void)_t3348;
    if (_t3348) {
        Token *_t3297 = expect_token(p, TokenType_LBrace());
        (void)_t3297;
        Expr *_t3298 = parse_block(p);
        (void)_t3298;
        Expr_add_child(def, _t3298);
    } else {
        Bool _t3319; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Func()); _t3319 = *_hp; free(_hp); }
        (void)_t3319;
        Bool _t3320; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Proc()); _t3320 = *_hp; free(_hp); }
        (void)_t3320;
        Bool _t3321 = Bool_not(_t3319);
        (void)_t3321;
        ;
        Bool _t3322 = Bool_not(_t3320);
        (void)_t3322;
        ;
        Bool _t3323 = Bool_and(_t3321, _t3322);
        (void)_t3323;
        ;
        ;
        if (_t3323) {
            Str *_t3299 = Str_lit("Str", 3ULL);
            (void)_t3299;
            U64 _t3300; { U64 *_hp = (U64 *)Str_size(); _t3300 = *_hp; free(_hp); }
            (void)_t3300;
            U64 _t3301 = 8;
            (void)_t3301;
            Array *_va69 = Array_new(_t3299, &(U64){_t3300}, &(U64){_t3301});
            (void)_va69;
            Str_delete(_t3299, &(Bool){1});
            ;
            ;
            U64 _t3302 = 0;
            (void)_t3302;
            Str *_t3303 = Str_clone(&p->path);
            (void)_t3303;
            Array_set(_va69, &(U64){_t3302}, _t3303);
            ;
            U64 _t3304 = 1;
            (void)_t3304;
            Str *_t3305 = Str_lit(":", 1ULL);
            (void)_t3305;
            Array_set(_va69, &(U64){_t3304}, _t3305);
            ;
            U64 _t3306 = 2;
            (void)_t3306;
            Str *_t3307 = U32_to_str(&(U32){kw_line});
            (void)_t3307;
            Array_set(_va69, &(U64){_t3306}, _t3307);
            ;
            U64 _t3308 = 3;
            (void)_t3308;
            Str *_t3309 = Str_lit(":", 1ULL);
            (void)_t3309;
            Array_set(_va69, &(U64){_t3308}, _t3309);
            ;
            U64 _t3310 = 4;
            (void)_t3310;
            Str *_t3311 = U32_to_str(&(U32){kw_col});
            (void)_t3311;
            Array_set(_va69, &(U64){_t3310}, _t3311);
            ;
            U64 _t3312 = 5;
            (void)_t3312;
            Str *_t3313 = Str_lit(": ", 2ULL);
            (void)_t3313;
            Array_set(_va69, &(U64){_t3312}, _t3313);
            ;
            U64 _t3314 = 6;
            (void)_t3314;
            Str *_t3315 = func_type_name(ft);
            (void)_t3315;
            Array_set(_va69, &(U64){_t3314}, _t3315);
            ;
            U64 _t3316 = 7;
            (void)_t3316;
            Str *_t3317 = Str_lit(" requires a body", 16ULL);
            (void)_t3317;
            Array_set(_va69, &(U64){_t3316}, _t3317);
            ;
            Str *_t3318 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:257:19", 64ULL);
            (void)_t3318;
            panic(_t3318, _va69);
            Str_delete(_t3318, &(Bool){1});
        }
        ;
    }
    ;
    FuncType_delete(ft, &(Bool){1});
    ;
    ;
    return def;
}

Expr * parse_struct_def(Parser * p) {
    (void)p;
    U32 kw_line = peek_line(p);
    (void)kw_line;
    U32 kw_col = peek_col(p);
    (void)kw_col;
    Bool is_ext = check(p, TokenType_KwExtStruct());
    (void)is_ext;
    Token *_t3362 = advance(p);
    (void)_t3362;
    Expr *def = Expr_new(ExprData_StructDef(), kw_line, kw_col, &p->path);
    (void)def;
    ;
    ;
    Bool _t3363 = Bool_clone(&(Bool){is_ext});
    (void)_t3363;
    ;
    def->is_ext = _t3363;
    ;
    Token *_t3364 = expect_token(p, TokenType_LBrace());
    (void)_t3364;
    U32 _t3365 = peek_line(p);
    (void)_t3365;
    U32 _t3366 = peek_col(p);
    (void)_t3366;
    Expr *body = Expr_new(ExprData_Body(), _t3365, _t3366, &p->path);
    (void)body;
    ;
    ;
    Bool in_namespace = 0;
    (void)in_namespace;
    while (1) {
        Bool _t3355 = check(p, TokenType_RBrace());
        (void)_t3355;
        Bool _t3356 = check(p, TokenType_Eof());
        (void)_t3356;
        Bool _t3357 = Bool_not(_t3355);
        (void)_t3357;
        ;
        Bool _t3358 = Bool_not(_t3356);
        (void)_t3358;
        ;
        Bool _wcond3349 = Bool_and(_t3357, _t3358);
        (void)_wcond3349;
        ;
        ;
        if (_wcond3349) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3359 = check(p, TokenType_KwNamespace());
        (void)_t3359;
        if (_t3359) {
            Token *_t3350 = advance(p);
            (void)_t3350;
            Token *_t3351 = expect_token(p, TokenType_Colon());
            (void)_t3351;
            Bool _t3352 = 1;
            (void)_t3352;
            in_namespace = _t3352;
            ;
            ;
            continue;
        }
        ;
        Expr *stmt = parse_statement(p);
        (void)stmt;
        Bool _t3360; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3360 = *_hp; free(_hp); }
        (void)_t3360;
        Bool _t3361 = Bool_and(in_namespace, _t3360);
        (void)_t3361;
        ;
        if (_t3361) {
            Bool _t3354; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3354 = *_hp; free(_hp); }
            (void)_t3354;
            if (_t3354) {
                Declaration *dd = ExprData_get_Decl(&stmt->data);
                (void)dd;
                Bool _t3353 = 1;
                (void)_t3353;
                dd->is_namespace = _t3353;
                ;
                ExprData_delete(&stmt->data, &(Bool){0});
                { ExprData *_fa = ExprData_Decl(dd); stmt->data = *_fa; free(_fa); }
                Declaration_delete(dd, &(Bool){1});
            }
            ;
        }
        ;
        Expr_add_child(body, stmt);
    }
    ;
    Token *_t3367 = expect_token(p, TokenType_RBrace());
    (void)_t3367;
    Expr_add_child(def, body);
    return def;
}

Expr * parse_enum_def(Parser * p) {
    (void)p;
    U32 kw_line = peek_line(p);
    (void)kw_line;
    U32 kw_col = peek_col(p);
    (void)kw_col;
    Token *_t3391 = advance(p);
    (void)_t3391;
    Expr *def = Expr_new(ExprData_EnumDef(), kw_line, kw_col, &p->path);
    (void)def;
    ;
    ;
    Token *_t3392 = expect_token(p, TokenType_LBrace());
    (void)_t3392;
    U32 _t3393 = peek_line(p);
    (void)_t3393;
    U32 _t3394 = peek_col(p);
    (void)_t3394;
    Expr *body = Expr_new(ExprData_Body(), _t3393, _t3394, &p->path);
    (void)body;
    ;
    ;
    Bool in_namespace = 0;
    (void)in_namespace;
    while (1) {
        Bool _t3386 = check(p, TokenType_RBrace());
        (void)_t3386;
        Bool _t3387 = check(p, TokenType_Eof());
        (void)_t3387;
        Bool _t3388 = Bool_not(_t3386);
        (void)_t3388;
        ;
        Bool _t3389 = Bool_not(_t3387);
        (void)_t3389;
        ;
        Bool _wcond3368 = Bool_and(_t3388, _t3389);
        (void)_wcond3368;
        ;
        ;
        if (_wcond3368) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3390 = check(p, TokenType_KwNamespace());
        (void)_t3390;
        if (_t3390) {
            Token *_t3369 = advance(p);
            (void)_t3369;
            Token *_t3370 = expect_token(p, TokenType_Colon());
            (void)_t3370;
            Bool _t3371 = 1;
            (void)_t3371;
            in_namespace = _t3371;
            ;
            ;
            continue;
        }
        ;
        if (in_namespace) {
            Expr *stmt = parse_statement(p);
            (void)stmt;
            Bool _t3374; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3374 = *_hp; free(_hp); }
            (void)_t3374;
            if (_t3374) {
                Bool _t3373; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3373 = *_hp; free(_hp); }
                (void)_t3373;
                if (_t3373) {
                    Declaration *dd = ExprData_get_Decl(&stmt->data);
                    (void)dd;
                    Bool _t3372 = 1;
                    (void)_t3372;
                    dd->is_namespace = _t3372;
                    ;
                    ExprData_delete(&stmt->data, &(Bool){0});
                    { ExprData *_fa = ExprData_Decl(dd); stmt->data = *_fa; free(_fa); }
                    Declaration_delete(dd, &(Bool){1});
                }
                ;
            }
            ;
            Expr_add_child(body, stmt);
        } else {
            U32 v_line = peek_line(p);
            (void)v_line;
            U32 v_col = peek_col(p);
            (void)v_col;
            Str *vname = expect_text(p, TokenType_Ident());
            (void)vname;
            Bool _t3377 = 0;
            (void)_t3377;
            Bool _t3378 = 0;
            (void)_t3378;
            Bool _t3379 = 0;
            (void)_t3379;
            Bool _t3380 = 0;
            (void)_t3380;
            I32 _t3381 = 0;
            (void)_t3381;
            I32 _t3382 = 0;
            (void)_t3382;
            Declaration *dd = malloc(sizeof(Declaration));
            { Str *_ca = Str_clone(vname); dd->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
            dd->is_mut = _t3377;
            dd->is_namespace = _t3378;
            dd->is_ref = _t3379;
            dd->is_own = _t3380;
            dd->field_offset = _t3381;
            dd->field_size = _t3382;
            dd->field_struct_def = NULL;
            dd->fn_sig = NULL;
            (void)dd;
            ;
            ;
            ;
            ;
            ;
            ;
            Str_delete(vname, &(Bool){1});
            Bool _t3383 = check(p, TokenType_Colon());
            (void)_t3383;
            if (_t3383) {
                Token *_t3375 = advance(p);
                (void)_t3375;
                Str_delete(&dd->explicit_type, &(Bool){0});
                { Str *_fa = expect_text(p, TokenType_Ident()); dd->explicit_type = *_fa; free(_fa); }
            }
            ;
            ExprData *_t3384 = ExprData_Decl(dd);
            (void)_t3384;
            Declaration_delete(dd, &(Bool){1});
            Expr *variant = Expr_new(_t3384, v_line, v_col, &p->path);
            (void)variant;
            ExprData_delete(_t3384, &(Bool){1});
            ;
            ;
            Expr_add_child(body, variant);
            Bool _t3385 = check(p, TokenType_Comma());
            (void)_t3385;
            if (_t3385) {
                Token *_t3376 = advance(p);
                (void)_t3376;
            }
            ;
        }
    }
    ;
    Token *_t3395 = expect_token(p, TokenType_RBrace());
    (void)_t3395;
    Expr_add_child(def, body);
    return def;
}

Expr * parse_call(Parser * p, Str * name, U32 call_line, U32 call_col) {
    (void)p;
    (void)name;
    (void)call_line;
    (void)call_col;
    Token *_t3426 = advance(p);
    (void)_t3426;
    Expr *call = Expr_new(ExprData_FCall(), call_line, call_col, &p->path);
    (void)call;
    Str *_t3427 = Str_clone(name);
    (void)_t3427;
    ExprData *_t3428 = ExprData_Ident(_t3427);
    (void)_t3428;
    Str_delete(_t3427, &(Bool){1});
    Expr *callee = Expr_new(_t3428, call_line, call_col, &p->path);
    (void)callee;
    ExprData_delete(_t3428, &(Bool){1});
    Expr_add_child(call, callee);
    while (1) {
        Bool _t3416 = check(p, TokenType_RParen());
        (void)_t3416;
        Bool _t3417 = check(p, TokenType_Eof());
        (void)_t3417;
        Bool _t3418 = Bool_not(_t3416);
        (void)_t3418;
        ;
        Bool _t3419 = Bool_not(_t3417);
        (void)_t3419;
        ;
        Bool _wcond3396 = Bool_and(_t3418, _t3419);
        (void)_wcond3396;
        ;
        ;
        if (_wcond3396) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3420 = check(p, TokenType_Ident());
        (void)_t3420;
        if (_t3420) {
            U64 _t3407 = 1;
            (void)_t3407;
            U64 _t3408 = U64_add(p->pos, _t3407);
            (void)_t3408;
            ;
            U64 _t3409; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3409 = *_hp; free(_hp); }
            (void)_t3409;
            Bool _t3410; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3408}, &(U64){_t3409}); _t3410 = *_hp; free(_hp); }
            (void)_t3410;
            ;
            ;
            if (_t3410) {
                U64 _t3402 = 1;
                (void)_t3402;
                U64 _t3403 = U64_add(p->pos, _t3402);
                (void)_t3403;
                ;
                I64 _t3404 = U64_to_i64(_t3403);
                (void)_t3404;
                ;
                U64 *_t3405 = malloc(sizeof(U64)); *_t3405 = I64_to_u64(_t3404);
                (void)_t3405;
                ;
                Token *next_tok = Vec_get(&p->tokens, _t3405);
                (void)next_tok;
                Bool _t3406; { Bool *_hp = (Bool *)TokenType_eq(&next_tok->type, TokenType_Eq()); _t3406 = *_hp; free(_hp); }
                (void)_t3406;
                U64_delete(_t3405, &(Bool){1});
                if (_t3406) {
                    U32 na_line = peek_line(p);
                    (void)na_line;
                    U32 na_col = peek_col(p);
                    (void)na_col;
                    Str *aname = expect_text(p, TokenType_Ident());
                    (void)aname;
                    Token *_t3398 = advance(p);
                    (void)_t3398;
                    ExprData *_t3399 = ExprData_NamedArg(aname);
                    (void)_t3399;
                    Str_delete(aname, &(Bool){1});
                    Expr *na = Expr_new(_t3399, na_line, na_col, &p->path);
                    (void)na;
                    ExprData_delete(_t3399, &(Bool){1});
                    ;
                    ;
                    Expr *_t3400 = parse_expression(p);
                    (void)_t3400;
                    Expr_add_child(na, _t3400);
                    Expr_add_child(call, na);
                    Bool _t3401 = check(p, TokenType_Comma());
                    (void)_t3401;
                    if (_t3401) {
                        Token *_t3397 = advance(p);
                        (void)_t3397;
                    }
                    ;
                    ;
                    ;
                    ;
                    continue;
                }
                ;
            }
            ;
        }
        ;
        Bool is_splat = 0;
        (void)is_splat;
        Bool _t3421 = check(p, TokenType_DotDot());
        (void)_t3421;
        if (_t3421) {
            Token *_t3411 = advance(p);
            (void)_t3411;
            Bool _t3412 = 1;
            (void)_t3412;
            is_splat = _t3412;
            ;
        }
        ;
        Bool is_own_arg = 0;
        (void)is_own_arg;
        Bool _t3422 = check(p, TokenType_KwOwn());
        (void)_t3422;
        if (_t3422) {
            Token *_t3413 = advance(p);
            (void)_t3413;
            Bool _t3414 = 1;
            (void)_t3414;
            is_own_arg = _t3414;
            ;
        }
        ;
        Expr *arg = parse_expression(p);
        (void)arg;
        Bool _t3423 = Bool_clone(&(Bool){is_own_arg});
        (void)_t3423;
        ;
        arg->is_own_arg = _t3423;
        ;
        Bool _t3424 = Bool_clone(&(Bool){is_splat});
        (void)_t3424;
        ;
        arg->is_splat = _t3424;
        ;
        Expr_add_child(call, arg);
        Bool _t3425 = check(p, TokenType_Comma());
        (void)_t3425;
        if (_t3425) {
            Token *_t3415 = advance(p);
            (void)_t3415;
        }
        ;
    }
    Token *_t3429 = expect_token(p, TokenType_RParen());
    (void)_t3429;
    return call;
}

Expr * parse_expression(Parser * p) {
    (void)p;
    U32 t_line = peek_line(p);
    (void)t_line;
    U32 t_col = peek_col(p);
    (void)t_col;
    Token *t = peek(p);
    (void)t;
    U32 _t3636 = 0;
    (void)_t3636;
    U32 _t3637 = 0;
    (void)_t3637;
    Expr *e = Expr_new(ExprData_Body(), _t3636, _t3637, &p->path);
    (void)e;
    ;
    ;
    Bool e_set = 0;
    (void)e_set;
    Bool _t3638; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t3638 = *_hp; free(_hp); }
    (void)_t3638;
    if (_t3638) {
        Token *_t3430 = advance(p);
        (void)_t3430;
        Str *_t3431 = Str_clone(&t->text);
        (void)_t3431;
        ExprData *_t3432 = ExprData_LiteralStr(_t3431);
        (void)_t3432;
        Str_delete(_t3431, &(Bool){1});
        e = Expr_new(_t3432, t_line, t_col, &p->path);
        ExprData_delete(_t3432, &(Bool){1});
        Bool _t3433 = 1;
        (void)_t3433;
        e_set = _t3433;
        ;
    }
    ;
    Bool _t3639 = Bool_not(e_set);
    (void)_t3639;
    Bool _t3640; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t3640 = *_hp; free(_hp); }
    (void)_t3640;
    Bool _t3641 = Bool_and(_t3639, _t3640);
    (void)_t3641;
    ;
    ;
    if (_t3641) {
        Token *_t3434 = advance(p);
        (void)_t3434;
        Str *_t3435 = Str_clone(&t->text);
        (void)_t3435;
        ExprData *_t3436 = ExprData_LiteralNum(_t3435);
        (void)_t3436;
        Str_delete(_t3435, &(Bool){1});
        e = Expr_new(_t3436, t_line, t_col, &p->path);
        ExprData_delete(_t3436, &(Bool){1});
        Bool _t3437 = 1;
        (void)_t3437;
        e_set = _t3437;
        ;
    }
    ;
    Bool _t3642 = Bool_not(e_set);
    (void)_t3642;
    Bool _t3643; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Minus()); _t3643 = *_hp; free(_hp); }
    (void)_t3643;
    Bool _t3644 = Bool_and(_t3642, _t3643);
    (void)_t3644;
    ;
    ;
    if (_t3644) {
        U64 _t3453 = 1;
        (void)_t3453;
        U64 _t3454 = U64_add(p->pos, _t3453);
        (void)_t3454;
        ;
        U64 _t3455; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3455 = *_hp; free(_hp); }
        (void)_t3455;
        Bool _t3456; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3454}, &(U64){_t3455}); _t3456 = *_hp; free(_hp); }
        (void)_t3456;
        ;
        ;
        if (_t3456) {
            U64 _t3448 = 1;
            (void)_t3448;
            U64 _t3449 = U64_add(p->pos, _t3448);
            (void)_t3449;
            ;
            I64 _t3450 = U64_to_i64(_t3449);
            (void)_t3450;
            ;
            U64 *_t3451 = malloc(sizeof(U64)); *_t3451 = I64_to_u64(_t3450);
            (void)_t3451;
            ;
            Token *next_tok = Vec_get(&p->tokens, _t3451);
            (void)next_tok;
            Bool _t3452; { Bool *_hp = (Bool *)TokenType_eq(&next_tok->type, TokenType_Number()); _t3452 = *_hp; free(_hp); }
            (void)_t3452;
            U64_delete(_t3451, &(Bool){1});
            if (_t3452) {
                Token *_t3438 = advance(p);
                (void)_t3438;
                Token *num_tok = advance(p);
                (void)num_tok;
                Str *_t3439 = Str_lit("0", 1ULL);
                (void)_t3439;
                Str *_t3440 = Str_clone(_t3439);
                (void)_t3440;
                Str_delete(_t3439, &(Bool){1});
                ExprData *_t3441 = ExprData_LiteralNum(_t3440);
                (void)_t3441;
                Str_delete(_t3440, &(Bool){1});
                Expr *zero = Expr_new(_t3441, t_line, t_col, &p->path);
                (void)zero;
                ExprData_delete(_t3441, &(Bool){1});
                Str *_t3442 = Str_lit("sub", 3ULL);
                (void)_t3442;
                Str *_t3443 = Str_clone(_t3442);
                (void)_t3443;
                Str_delete(_t3442, &(Bool){1});
                ExprData *_t3444 = ExprData_FieldAccess(_t3443);
                (void)_t3444;
                Str_delete(_t3443, &(Bool){1});
                Expr *sub_access = Expr_new(_t3444, t_line, t_col, &p->path);
                (void)sub_access;
                ExprData_delete(_t3444, &(Bool){1});
                Expr_add_child(sub_access, zero);
                Expr *sub_call = Expr_new(ExprData_FCall(), t_line, t_col, &p->path);
                (void)sub_call;
                Expr_add_child(sub_call, sub_access);
                Str *_t3445 = Str_clone(&num_tok->text);
                (void)_t3445;
                ExprData *_t3446 = ExprData_LiteralNum(_t3445);
                (void)_t3446;
                Str_delete(_t3445, &(Bool){1});
                Expr *num_arg = Expr_new(_t3446, t_line, t_col, &p->path);
                (void)num_arg;
                ExprData_delete(_t3446, &(Bool){1});
                Expr_add_child(sub_call, num_arg);
                e = Expr_clone(sub_call);
                Expr_delete(sub_call, &(Bool){1});
                Bool _t3447 = 1;
                (void)_t3447;
                e_set = _t3447;
                ;
            }
            ;
        }
        ;
    }
    ;
    Bool _t3645 = Bool_not(e_set);
    (void)_t3645;
    Bool _t3646; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Char()); _t3646 = *_hp; free(_hp); }
    (void)_t3646;
    Bool _t3647 = Bool_and(_t3645, _t3646);
    (void)_t3647;
    ;
    ;
    if (_t3647) {
        Token *_t3486 = advance(p);
        (void)_t3486;
        Str *ch = Str_clone(&t->text);
        (void)ch;
        I64 byte_val = 0;
        (void)byte_val;
        U64 _t3487; { U64 *_hp = (U64 *)Str_len(ch); _t3487 = *_hp; free(_hp); }
        (void)_t3487;
        U64 _t3488 = 0;
        (void)_t3488;
        U64 *_t3489 = malloc(sizeof(U64));
        *_t3489 = 0;
        (void)_t3489;
        U8 *_t3490 = Str_get(ch, _t3489);
        (void)_t3490;
        U8 _t3491 = 92;
        (void)_t3491;
        Bool _t3492; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3487}, &(U64){_t3488}); _t3492 = *_hp; free(_hp); }
        (void)_t3492;
        ;
        ;
        Bool _t3493 = U8_eq(DEREF(_t3490), _t3491);
        (void)_t3493;
        U64_delete(_t3489, &(Bool){1});
        ;
        Bool _t3494 = Bool_and(_t3492, _t3493);
        (void)_t3494;
        ;
        ;
        if (_t3494) {
            U64 _t3477; { U64 *_hp = (U64 *)Str_len(ch); _t3477 = *_hp; free(_hp); }
            (void)_t3477;
            U64 _t3478 = 1;
            (void)_t3478;
            Bool _t3479; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3477}, &(U64){_t3478}); _t3479 = *_hp; free(_hp); }
            (void)_t3479;
            ;
            ;
            if (_t3479) {
                U64 *_t3474 = malloc(sizeof(U64));
                *_t3474 = 1;
                (void)_t3474;
                U8 *c2 = Str_get(ch, _t3474);
                (void)c2;
                U8 _t3475 = 110;
                (void)_t3475;
                Bool _t3476 = U8_eq(DEREF(c2), _t3475);
                (void)_t3476;
                ;
                if (_t3476) {
                    I64 _t3457 = 10;
                    (void)_t3457;
                    byte_val = _t3457;
                    ;
                } else {
                    U8 _t3472 = 116;
                    (void)_t3472;
                    Bool _t3473 = U8_eq(DEREF(c2), _t3472);
                    (void)_t3473;
                    ;
                    if (_t3473) {
                        I64 _t3458 = 9;
                        (void)_t3458;
                        byte_val = _t3458;
                        ;
                    } else {
                        U8 _t3470 = 114;
                        (void)_t3470;
                        Bool _t3471 = U8_eq(DEREF(c2), _t3470);
                        (void)_t3471;
                        ;
                        if (_t3471) {
                            I64 _t3459 = 13;
                            (void)_t3459;
                            byte_val = _t3459;
                            ;
                        } else {
                            U8 _t3468 = 92;
                            (void)_t3468;
                            Bool _t3469 = U8_eq(DEREF(c2), _t3468);
                            (void)_t3469;
                            ;
                            if (_t3469) {
                                I64 _t3460 = 92;
                                (void)_t3460;
                                byte_val = _t3460;
                                ;
                            } else {
                                U8 _t3466 = 39;
                                (void)_t3466;
                                Bool _t3467 = U8_eq(DEREF(c2), _t3466);
                                (void)_t3467;
                                ;
                                if (_t3467) {
                                    I64 _t3461 = 39;
                                    (void)_t3461;
                                    byte_val = _t3461;
                                    ;
                                } else {
                                    U8 _t3464 = 48;
                                    (void)_t3464;
                                    Bool _t3465 = U8_eq(DEREF(c2), _t3464);
                                    (void)_t3465;
                                    ;
                                    if (_t3465) {
                                        I64 _t3462 = 0;
                                        (void)_t3462;
                                        byte_val = _t3462;
                                        ;
                                    } else {
                                        I64 _t3463 = U8_to_i64(DEREF(c2));
                                        (void)_t3463;
                                        byte_val = _t3463;
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
                U64_delete(_t3474, &(Bool){1});
                ;
            }
            ;
        } else {
            U64 _t3483; { U64 *_hp = (U64 *)Str_len(ch); _t3483 = *_hp; free(_hp); }
            (void)_t3483;
            U64 _t3484 = 0;
            (void)_t3484;
            Bool _t3485; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3483}, &(U64){_t3484}); _t3485 = *_hp; free(_hp); }
            (void)_t3485;
            ;
            ;
            if (_t3485) {
                U64 *_t3480 = malloc(sizeof(U64));
                *_t3480 = 0;
                (void)_t3480;
                U8 *_t3481 = Str_get(ch, _t3480);
                (void)_t3481;
                I64 _t3482 = U8_to_i64(DEREF(_t3481));
                (void)_t3482;
                U64_delete(_t3480, &(Bool){1});
                byte_val = _t3482;
                ;
            }
            ;
        }
        ;
        Str_delete(ch, &(Bool){1});
        Str *_t3495 = I64_to_str(&(I64){byte_val});
        (void)_t3495;
        ;
        ExprData *_t3496 = ExprData_LiteralNum(_t3495);
        (void)_t3496;
        Str_delete(_t3495, &(Bool){1});
        e = Expr_new(_t3496, t_line, t_col, &p->path);
        ExprData_delete(_t3496, &(Bool){1});
        TilType_delete(&e->til_type, &(Bool){0});
        { TilType *_fa = TilType_clone(TilType_U8()); e->til_type = *_fa; free(_fa); }
        Bool _t3497 = 1;
        (void)_t3497;
        e_set = _t3497;
        ;
    }
    ;
    Bool _t3648; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t3648 = *_hp; free(_hp); }
    (void)_t3648;
    Bool _t3649; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t3649 = *_hp; free(_hp); }
    (void)_t3649;
    Bool _t3650 = Bool_not(e_set);
    (void)_t3650;
    Bool _t3651 = Bool_or(_t3648, _t3649);
    (void)_t3651;
    ;
    ;
    Bool _t3652 = Bool_and(_t3650, _t3651);
    (void)_t3652;
    ;
    ;
    if (_t3652) {
        Token *_t3498 = advance(p);
        (void)_t3498;
        Str *_t3499 = Str_clone(&t->text);
        (void)_t3499;
        ExprData *_t3500 = ExprData_LiteralBool(_t3499);
        (void)_t3500;
        Str_delete(_t3499, &(Bool){1});
        e = Expr_new(_t3500, t_line, t_col, &p->path);
        ExprData_delete(_t3500, &(Bool){1});
        Bool _t3501 = 1;
        (void)_t3501;
        e_set = _t3501;
        ;
    }
    ;
    Bool _t3653 = Bool_not(e_set);
    (void)_t3653;
    Bool _t3654; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwNull()); _t3654 = *_hp; free(_hp); }
    (void)_t3654;
    Bool _t3655 = Bool_and(_t3653, _t3654);
    (void)_t3655;
    ;
    ;
    if (_t3655) {
        Token *_t3502 = advance(p);
        (void)_t3502;
        e = Expr_new(ExprData_LiteralNull(), t_line, t_col, &p->path);
        Bool _t3503 = 1;
        (void)_t3503;
        e_set = _t3503;
        ;
    }
    ;
    Bool _t3656 = Bool_not(e_set);
    (void)_t3656;
    Bool _t3657; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t3657 = *_hp; free(_hp); }
    (void)_t3657;
    Bool _t3658 = Bool_and(_t3656, _t3657);
    (void)_t3658;
    ;
    ;
    if (_t3658) {
        Token *_t3539 = advance(p);
        (void)_t3539;
        Str *name = Str_clone(&t->text);
        (void)name;
        Str *_t3540 = Str_lit("__LOC__", 7ULL);
        (void)_t3540;
        Bool _t3541; { Bool *_hp = (Bool *)Str_eq(name, _t3540); _t3541 = *_hp; free(_hp); }
        (void)_t3541;
        Str_delete(_t3540, &(Bool){1});
        if (_t3541) {
            Str *_t3504 = Str_lit("Str", 3ULL);
            (void)_t3504;
            U64 _t3505; { U64 *_hp = (U64 *)Str_size(); _t3505 = *_hp; free(_hp); }
            (void)_t3505;
            U64 _t3506 = 5;
            (void)_t3506;
            Array *_va70 = Array_new(_t3504, &(U64){_t3505}, &(U64){_t3506});
            (void)_va70;
            Str_delete(_t3504, &(Bool){1});
            ;
            ;
            U64 _t3507 = 0;
            (void)_t3507;
            Str *_t3508 = Str_clone(&p->path);
            (void)_t3508;
            Array_set(_va70, &(U64){_t3507}, _t3508);
            ;
            U64 _t3509 = 1;
            (void)_t3509;
            Str *_t3510 = Str_lit(":", 1ULL);
            (void)_t3510;
            Array_set(_va70, &(U64){_t3509}, _t3510);
            ;
            U64 _t3511 = 2;
            (void)_t3511;
            Str *_t3512 = U32_to_str(&(U32){t_line});
            (void)_t3512;
            Array_set(_va70, &(U64){_t3511}, _t3512);
            ;
            U64 _t3513 = 3;
            (void)_t3513;
            Str *_t3514 = Str_lit(":", 1ULL);
            (void)_t3514;
            Array_set(_va70, &(U64){_t3513}, _t3514);
            ;
            U64 _t3515 = 4;
            (void)_t3515;
            Str *_t3516 = U32_to_str(&(U32){t_col});
            (void)_t3516;
            Array_set(_va70, &(U64){_t3515}, _t3516);
            ;
            Str *_t3517 = format(_va70);
            (void)_t3517;
            ExprData *_t3518 = ExprData_LiteralStr(_t3517);
            (void)_t3518;
            Str_delete(_t3517, &(Bool){1});
            e = Expr_new(_t3518, t_line, t_col, &p->path);
            ExprData_delete(_t3518, &(Bool){1});
            Bool _t3519 = 1;
            (void)_t3519;
            e_set = _t3519;
            ;
        } else {
            Str *_t3537 = Str_lit("__FILE__", 8ULL);
            (void)_t3537;
            Bool _t3538; { Bool *_hp = (Bool *)Str_eq(name, _t3537); _t3538 = *_hp; free(_hp); }
            (void)_t3538;
            Str_delete(_t3537, &(Bool){1});
            if (_t3538) {
                Str *_t3520 = Str_clone(&p->path);
                (void)_t3520;
                ExprData *_t3521 = ExprData_LiteralStr(_t3520);
                (void)_t3521;
                Str_delete(_t3520, &(Bool){1});
                e = Expr_new(_t3521, t_line, t_col, &p->path);
                ExprData_delete(_t3521, &(Bool){1});
                Bool _t3522 = 1;
                (void)_t3522;
                e_set = _t3522;
                ;
            } else {
                Str *_t3535 = Str_lit("__LINE__", 8ULL);
                (void)_t3535;
                Bool _t3536; { Bool *_hp = (Bool *)Str_eq(name, _t3535); _t3536 = *_hp; free(_hp); }
                (void)_t3536;
                Str_delete(_t3535, &(Bool){1});
                if (_t3536) {
                    Str *_t3523 = U32_to_str(&(U32){t_line});
                    (void)_t3523;
                    ExprData *_t3524 = ExprData_LiteralNum(_t3523);
                    (void)_t3524;
                    Str_delete(_t3523, &(Bool){1});
                    e = Expr_new(_t3524, t_line, t_col, &p->path);
                    ExprData_delete(_t3524, &(Bool){1});
                    Bool _t3525 = 1;
                    (void)_t3525;
                    e_set = _t3525;
                    ;
                } else {
                    Str *_t3533 = Str_lit("__COL__", 7ULL);
                    (void)_t3533;
                    Bool _t3534; { Bool *_hp = (Bool *)Str_eq(name, _t3533); _t3534 = *_hp; free(_hp); }
                    (void)_t3534;
                    Str_delete(_t3533, &(Bool){1});
                    if (_t3534) {
                        Str *_t3526 = U32_to_str(&(U32){t_col});
                        (void)_t3526;
                        ExprData *_t3527 = ExprData_LiteralNum(_t3526);
                        (void)_t3527;
                        Str_delete(_t3526, &(Bool){1});
                        e = Expr_new(_t3527, t_line, t_col, &p->path);
                        ExprData_delete(_t3527, &(Bool){1});
                        Bool _t3528 = 1;
                        (void)_t3528;
                        e_set = _t3528;
                        ;
                    } else {
                        Bool _t3532 = check(p, TokenType_LParen());
                        (void)_t3532;
                        if (_t3532) {
                            e = parse_call(p, name, t_line, t_col);
                            Bool _t3529 = 1;
                            (void)_t3529;
                            e_set = _t3529;
                            ;
                        } else {
                            ExprData *_t3530 = ExprData_Ident(name);
                            (void)_t3530;
                            e = Expr_new(_t3530, t_line, t_col, &p->path);
                            ExprData_delete(_t3530, &(Bool){1});
                            Bool _t3531 = 1;
                            (void)_t3531;
                            e_set = _t3531;
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
        Str_delete(name, &(Bool){1});
    }
    ;
    Bool _t3659; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFunc()); _t3659 = *_hp; free(_hp); }
    (void)_t3659;
    Bool _t3660; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwProc()); _t3660 = *_hp; free(_hp); }
    (void)_t3660;
    Bool _t3661 = Bool_or(_t3659, _t3660);
    (void)_t3661;
    ;
    ;
    Bool _t3662; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTest()); _t3662 = *_hp; free(_hp); }
    (void)_t3662;
    Bool _t3663 = Bool_or(_t3661, _t3662);
    (void)_t3663;
    ;
    ;
    Bool _t3664; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMacro()); _t3664 = *_hp; free(_hp); }
    (void)_t3664;
    Bool _t3665 = Bool_or(_t3663, _t3664);
    (void)_t3665;
    ;
    ;
    Bool _t3666; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtFunc()); _t3666 = *_hp; free(_hp); }
    (void)_t3666;
    Bool _t3667 = Bool_or(_t3665, _t3666);
    (void)_t3667;
    ;
    ;
    Bool _t3668; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtProc()); _t3668 = *_hp; free(_hp); }
    (void)_t3668;
    Bool _t3669 = Bool_not(e_set);
    (void)_t3669;
    Bool _t3670 = Bool_or(_t3667, _t3668);
    (void)_t3670;
    ;
    ;
    Bool _t3671 = Bool_and(_t3669, _t3670);
    (void)_t3671;
    ;
    ;
    if (_t3671) {
        Expr *_t3542 = parse_func_def(p);
        (void)_t3542;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3542;
    }
    ;
    Bool _t3672; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwStruct()); _t3672 = *_hp; free(_hp); }
    (void)_t3672;
    Bool _t3673; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtStruct()); _t3673 = *_hp; free(_hp); }
    (void)_t3673;
    Bool _t3674 = Bool_not(e_set);
    (void)_t3674;
    Bool _t3675 = Bool_or(_t3672, _t3673);
    (void)_t3675;
    ;
    ;
    Bool _t3676 = Bool_and(_t3674, _t3675);
    (void)_t3676;
    ;
    ;
    if (_t3676) {
        Expr *_t3543 = parse_struct_def(p);
        (void)_t3543;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3543;
    }
    ;
    Bool _t3677 = Bool_not(e_set);
    (void)_t3677;
    Bool _t3678; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwEnum()); _t3678 = *_hp; free(_hp); }
    (void)_t3678;
    Bool _t3679 = Bool_and(_t3677, _t3678);
    (void)_t3679;
    ;
    ;
    if (_t3679) {
        Expr *_t3544 = parse_enum_def(p);
        (void)_t3544;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3544;
    }
    ;
    Bool _t3680 = Bool_not(e_set);
    (void)_t3680;
    Bool _t3681; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t3681 = *_hp; free(_hp); }
    (void)_t3681;
    Bool _t3682 = Bool_and(_t3680, _t3681);
    (void)_t3682;
    ;
    ;
    if (_t3682) {
        Token *_t3569 = advance(p);
        (void)_t3569;
        Expr *first = parse_expression(p);
        (void)first;
        Bool _t3570 = check(p, TokenType_Colon());
        (void)_t3570;
        if (_t3570) {
            e = Expr_new(ExprData_MapLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Token *_t3556 = advance(p);
            (void)_t3556;
            Expr *_t3557 = parse_expression(p);
            (void)_t3557;
            Expr_add_child(e, _t3557);
            Bool _t3558 = check(p, TokenType_Comma());
            (void)_t3558;
            if (_t3558) {
                Token *_t3545 = advance(p);
                (void)_t3545;
            }
            ;
            while (1) {
                Bool _t3548 = check(p, TokenType_RBrace());
                (void)_t3548;
                Bool _t3549 = check(p, TokenType_Eof());
                (void)_t3549;
                Bool _t3550 = Bool_not(_t3548);
                (void)_t3550;
                ;
                Bool _t3551 = Bool_not(_t3549);
                (void)_t3551;
                ;
                Bool _wcond3546 = Bool_and(_t3550, _t3551);
                (void)_wcond3546;
                ;
                ;
                if (_wcond3546) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3552 = parse_expression(p);
                (void)_t3552;
                Expr_add_child(e, _t3552);
                Token *_t3553 = expect_token(p, TokenType_Colon());
                (void)_t3553;
                Expr *_t3554 = parse_expression(p);
                (void)_t3554;
                Expr_add_child(e, _t3554);
                Bool _t3555 = check(p, TokenType_Comma());
                (void)_t3555;
                if (_t3555) {
                    Token *_t3547 = advance(p);
                    (void)_t3547;
                }
                ;
            }
        } else {
            e = Expr_new(ExprData_SetLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Bool _t3568 = check(p, TokenType_Comma());
            (void)_t3568;
            if (_t3568) {
                Token *_t3559 = advance(p);
                (void)_t3559;
            }
            ;
            while (1) {
                Bool _t3562 = check(p, TokenType_RBrace());
                (void)_t3562;
                Bool _t3563 = check(p, TokenType_Eof());
                (void)_t3563;
                Bool _t3564 = Bool_not(_t3562);
                (void)_t3564;
                ;
                Bool _t3565 = Bool_not(_t3563);
                (void)_t3565;
                ;
                Bool _wcond3560 = Bool_and(_t3564, _t3565);
                (void)_wcond3560;
                ;
                ;
                if (_wcond3560) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3566 = parse_expression(p);
                (void)_t3566;
                Expr_add_child(e, _t3566);
                Bool _t3567 = check(p, TokenType_Comma());
                (void)_t3567;
                if (_t3567) {
                    Token *_t3561 = advance(p);
                    (void)_t3561;
                }
                ;
            }
        }
        ;
        Token *_t3571 = expect_token(p, TokenType_RBrace());
        (void)_t3571;
        Bool _t3572 = 1;
        (void)_t3572;
        e_set = _t3572;
        ;
    }
    ;
    Bool _t3683 = Bool_not(e_set);
    (void)_t3683;
    ;
    if (_t3683) {
        Str *_t3573 = Str_lit("Str", 3ULL);
        (void)_t3573;
        U64 _t3574; { U64 *_hp = (U64 *)Str_size(); _t3574 = *_hp; free(_hp); }
        (void)_t3574;
        U64 _t3575 = 8;
        (void)_t3575;
        Array *_va71 = Array_new(_t3573, &(U64){_t3574}, &(U64){_t3575});
        (void)_va71;
        Str_delete(_t3573, &(Bool){1});
        ;
        ;
        U64 _t3576 = 0;
        (void)_t3576;
        Str *_t3577 = Str_clone(&p->path);
        (void)_t3577;
        Array_set(_va71, &(U64){_t3576}, _t3577);
        ;
        U64 _t3578 = 1;
        (void)_t3578;
        Str *_t3579 = Str_lit(":", 1ULL);
        (void)_t3579;
        Array_set(_va71, &(U64){_t3578}, _t3579);
        ;
        U64 _t3580 = 2;
        (void)_t3580;
        Str *_t3581 = U32_to_str(&(U32){t_line});
        (void)_t3581;
        Array_set(_va71, &(U64){_t3580}, _t3581);
        ;
        U64 _t3582 = 3;
        (void)_t3582;
        Str *_t3583 = Str_lit(":", 1ULL);
        (void)_t3583;
        Array_set(_va71, &(U64){_t3582}, _t3583);
        ;
        U64 _t3584 = 4;
        (void)_t3584;
        Str *_t3585 = U32_to_str(&(U32){t_col});
        (void)_t3585;
        Array_set(_va71, &(U64){_t3584}, _t3585);
        ;
        U64 _t3586 = 5;
        (void)_t3586;
        Str *_t3587 = Str_lit(": unexpected token '", 20ULL);
        (void)_t3587;
        Array_set(_va71, &(U64){_t3586}, _t3587);
        ;
        U64 _t3588 = 6;
        (void)_t3588;
        Str *_t3589 = Str_clone(&t->text);
        (void)_t3589;
        Array_set(_va71, &(U64){_t3588}, _t3589);
        ;
        U64 _t3590 = 7;
        (void)_t3590;
        Str *_t3591 = Str_lit("'", 1ULL);
        (void)_t3591;
        Array_set(_va71, &(U64){_t3590}, _t3591);
        ;
        Str *_t3592 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:536:15", 64ULL);
        (void)_t3592;
        panic(_t3592, _va71);
        Str_delete(_t3592, &(Bool){1});
    }
    ;
    ;
    ;
    while (1) {
        Bool _wcond3593 = check(p, TokenType_Dot());
        (void)_wcond3593;
        if (_wcond3593) {
        } else {
            ;
            break;
        }
        ;
        Token *_t3626 = advance(p);
        (void)_t3626;
        U32 f_line = peek_line(p);
        (void)f_line;
        U32 f_col = peek_col(p);
        (void)f_col;
        Str *fname = expect_text(p, TokenType_Ident());
        (void)fname;
        Bool _t3627 = check(p, TokenType_LParen());
        (void)_t3627;
        if (_t3627) {
            Token *_t3620 = advance(p);
            (void)_t3620;
            ExprData *_t3621 = ExprData_FieldAccess(fname);
            (void)_t3621;
            Expr *callee = Expr_new(_t3621, f_line, f_col, &p->path);
            (void)callee;
            ExprData_delete(_t3621, &(Bool){1});
            Expr *_t3622 = Expr_clone(e);
            (void)_t3622;
            Expr_add_child(callee, _t3622);
            Expr *mcall = Expr_new(ExprData_FCall(), f_line, f_col, &p->path);
            (void)mcall;
            Expr_add_child(mcall, callee);
            while (1) {
                Bool _t3612 = check(p, TokenType_RParen());
                (void)_t3612;
                Bool _t3613 = check(p, TokenType_Eof());
                (void)_t3613;
                Bool _t3614 = Bool_not(_t3612);
                (void)_t3614;
                ;
                Bool _t3615 = Bool_not(_t3613);
                (void)_t3615;
                ;
                Bool _wcond3594 = Bool_and(_t3614, _t3615);
                (void)_wcond3594;
                ;
                ;
                if (_wcond3594) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3616 = check(p, TokenType_Ident());
                (void)_t3616;
                if (_t3616) {
                    U64 _t3605 = 1;
                    (void)_t3605;
                    U64 _t3606 = U64_add(p->pos, _t3605);
                    (void)_t3606;
                    ;
                    U64 _t3607; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3607 = *_hp; free(_hp); }
                    (void)_t3607;
                    Bool _t3608; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3606}, &(U64){_t3607}); _t3608 = *_hp; free(_hp); }
                    (void)_t3608;
                    ;
                    ;
                    if (_t3608) {
                        U64 _t3600 = 1;
                        (void)_t3600;
                        U64 _t3601 = U64_add(p->pos, _t3600);
                        (void)_t3601;
                        ;
                        I64 _t3602 = U64_to_i64(_t3601);
                        (void)_t3602;
                        ;
                        U64 *_t3603 = malloc(sizeof(U64)); *_t3603 = I64_to_u64(_t3602);
                        (void)_t3603;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3603);
                        (void)nt;
                        Bool _t3604; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3604 = *_hp; free(_hp); }
                        (void)_t3604;
                        U64_delete(_t3603, &(Bool){1});
                        if (_t3604) {
                            U32 na_line = peek_line(p);
                            (void)na_line;
                            U32 na_col = peek_col(p);
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3596 = advance(p);
                            (void)_t3596;
                            ExprData *_t3597 = ExprData_NamedArg(aname);
                            (void)_t3597;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3597, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3597, &(Bool){1});
                            ;
                            ;
                            Expr *_t3598 = parse_expression(p);
                            (void)_t3598;
                            Expr_add_child(na, _t3598);
                            Expr_add_child(mcall, na);
                            Bool _t3599 = check(p, TokenType_Comma());
                            (void)_t3599;
                            if (_t3599) {
                                Token *_t3595 = advance(p);
                                (void)_t3595;
                            }
                            ;
                            ;
                            ;
                            ;
                            continue;
                        }
                        ;
                    }
                    ;
                }
                ;
                Bool is_own_arg = 0;
                (void)is_own_arg;
                Bool _t3617 = check(p, TokenType_KwOwn());
                (void)_t3617;
                if (_t3617) {
                    Token *_t3609 = advance(p);
                    (void)_t3609;
                    Bool _t3610 = 1;
                    (void)_t3610;
                    is_own_arg = _t3610;
                    ;
                }
                ;
                Expr *marg = parse_expression(p);
                (void)marg;
                Bool _t3618 = Bool_clone(&(Bool){is_own_arg});
                (void)_t3618;
                ;
                marg->is_own_arg = _t3618;
                ;
                Expr_add_child(mcall, marg);
                Bool _t3619 = check(p, TokenType_Comma());
                (void)_t3619;
                if (_t3619) {
                    Token *_t3611 = advance(p);
                    (void)_t3611;
                }
                ;
            }
            Token *_t3623 = expect_token(p, TokenType_RParen());
            (void)_t3623;
            e = Expr_clone(mcall);
            Expr_delete(mcall, &(Bool){1});
        } else {
            ExprData *_t3624 = ExprData_FieldAccess(fname);
            (void)_t3624;
            Expr *access = Expr_new(_t3624, f_line, f_col, &p->path);
            (void)access;
            ExprData_delete(_t3624, &(Bool){1});
            Expr *_t3625 = Expr_clone(e);
            (void)_t3625;
            Expr_add_child(access, _t3625);
            e = Expr_clone(access);
            Expr_delete(access, &(Bool){1});
        }
        ;
        ;
        ;
        Str_delete(fname, &(Bool){1});
    }
    Bool _t3684 = check(p, TokenType_DotDot());
    (void)_t3684;
    if (_t3684) {
        U32 dt_line = peek_line(p);
        (void)dt_line;
        U32 dt_col = peek_col(p);
        (void)dt_col;
        Token *_t3628 = advance(p);
        (void)_t3628;
        Expr *rhs = parse_expression(p);
        (void)rhs;
        Str *_t3629 = Str_lit("Range", 5ULL);
        (void)_t3629;
        Str *_t3630 = Str_clone(_t3629);
        (void)_t3630;
        Str_delete(_t3629, &(Bool){1});
        ExprData *_t3631 = ExprData_Ident(_t3630);
        (void)_t3631;
        Str_delete(_t3630, &(Bool){1});
        Expr *range_ident = Expr_new(_t3631, dt_line, dt_col, &p->path);
        (void)range_ident;
        ExprData_delete(_t3631, &(Bool){1});
        Str *_t3632 = Str_lit("new", 3ULL);
        (void)_t3632;
        Str *_t3633 = Str_clone(_t3632);
        (void)_t3633;
        Str_delete(_t3632, &(Bool){1});
        ExprData *_t3634 = ExprData_FieldAccess(_t3633);
        (void)_t3634;
        Str_delete(_t3633, &(Bool){1});
        Expr *new_access = Expr_new(_t3634, dt_line, dt_col, &p->path);
        (void)new_access;
        ExprData_delete(_t3634, &(Bool){1});
        Expr_add_child(new_access, range_ident);
        Expr *rcall = Expr_new(ExprData_FCall(), dt_line, dt_col, &p->path);
        (void)rcall;
        ;
        ;
        Expr_add_child(rcall, new_access);
        Expr *_t3635 = Expr_clone(e);
        (void)_t3635;
        Expr_add_child(rcall, _t3635);
        Expr_add_child(rcall, rhs);
        e = Expr_clone(rcall);
        Expr_delete(rcall, &(Bool){1});
    }
    ;
    return e;
}

Expr * parse_statement_ident(Parser * p, Bool is_mut, Bool is_own) {
    (void)p;
    (void)is_mut;
    (void)is_own;
    U32 t_line = peek_line(p);
    (void)t_line;
    U32 t_col = peek_col(p);
    (void)t_col;
    Str *name = expect_text(p, TokenType_Ident());
    (void)name;
    Bool _t3864 = check(p, TokenType_ColonEq());
    (void)_t3864;
    if (_t3864) {
        Token *_t3685 = advance(p);
        (void)_t3685;
        Bool _t3686 = Bool_clone(&(Bool){is_mut});
        (void)_t3686;
        Bool _t3687 = 0;
        (void)_t3687;
        Bool _t3688 = 0;
        (void)_t3688;
        Bool _t3689 = Bool_clone(&(Bool){is_own});
        (void)_t3689;
        I32 _t3690 = 0;
        (void)_t3690;
        I32 _t3691 = 0;
        (void)_t3691;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3686;
        dd->is_namespace = _t3687;
        dd->is_ref = _t3688;
        dd->is_own = _t3689;
        dd->field_offset = _t3690;
        dd->field_size = _t3691;
        dd->field_struct_def = NULL;
        dd->fn_sig = NULL;
        (void)dd;
        ;
        ;
        ;
        ;
        ;
        ;
        ExprData *_t3692 = ExprData_Decl(dd);
        (void)_t3692;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3692, t_line, t_col, &p->path);
        (void)decl;
        ExprData_delete(_t3692, &(Bool){1});
        Expr *_t3693 = parse_expression(p);
        (void)_t3693;
        Expr_add_child(decl, _t3693);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return decl;
    }
    ;
    Bool _t3865 = check(p, TokenType_Colon());
    (void)_t3865;
    if (_t3865) {
        Token *_t3798 = advance(p);
        (void)_t3798;
        Bool _t3799 = check(p, TokenType_KwFunc());
        (void)_t3799;
        Bool _t3800 = check(p, TokenType_KwProc());
        (void)_t3800;
        Bool _t3801 = Bool_or(_t3799, _t3800);
        (void)_t3801;
        ;
        ;
        if (_t3801) {
            Expr *sig = parse_func_def(p);
            (void)sig;
            Token *_t3707 = expect_token(p, TokenType_Eq());
            (void)_t3707;
            Token *_t3708 = expect_token(p, TokenType_LParen());
            (void)_t3708;
            Bool _t3709; { Bool *_hp = (Bool *)ExprData_is_FuncDef(&sig->data); _t3709 = *_hp; free(_hp); }
            (void)_t3709;
            if (_t3709) {
                FunctionDef *sfd = ExprData_get_FuncDef(&sig->data);
                (void)sfd;
                Str *_t3704 = Str_lit("Str", 3ULL);
                (void)_t3704;
                U64 _t3705; { U64 *_hp = (U64 *)Str_size(); _t3705 = *_hp; free(_hp); }
                (void)_t3705;
                Vec *new_names = Vec_new(_t3704, &(U64){_t3705});
                (void)new_names;
                Str_delete(_t3704, &(Bool){1});
                ;
                Vec_delete(new_names, &(Bool){1});
                {
                    U64 _t3702 = 0;
                    (void)_t3702;
                    U64 _t3703; { U64 *_hp = (U64 *)Vec_len(&sfd->params); _t3703 = *_hp; free(_hp); }
                    (void)_t3703;
                    Range *_fc3694 = Range_new(_t3702, _t3703);
                    (void)_fc3694;
                    ;
                    ;
                    U64 _fi3694 = 0;
                    (void)_fi3694;
                    while (1) {
                        U64 _t3697; { U64 *_hp = (U64 *)Range_len(_fc3694); _t3697 = *_hp; free(_hp); }
                        (void)_t3697;
                        Bool _wcond3695; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3694}, &(U64){_t3697}); _wcond3695 = *_hp; free(_hp); }
                        (void)_wcond3695;
                        ;
                        if (_wcond3695) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 *pi = Range_get(_fc3694, _fi3694);
                        (void)pi;
                        U64 _t3698 = 1;
                        (void)_t3698;
                        U64 _t3699 = U64_add(_fi3694, _t3698);
                        (void)_t3699;
                        ;
                        _fi3694 = _t3699;
                        ;
                        U64 _t3700 = 0;
                        (void)_t3700;
                        Bool _t3701; { Bool *_hp = (Bool *)U64_gt(pi, &(U64){_t3700}); _t3701 = *_hp; free(_hp); }
                        (void)_t3701;
                        ;
                        if (_t3701) {
                            Token *_t3696 = expect_token(p, TokenType_Comma());
                            (void)_t3696;
                        }
                        ;
                        Str *pn = expect_text(p, TokenType_Ident());
                        (void)pn;
                        Param *pp = Vec_get(&sfd->params, pi);
                        (void)pp;
                        Str_delete(&pp->name, &(Bool){0});
                        { Str *_fa = Str_clone(pn); pp->name = *_fa; free(_fa); }
                        U64_delete(pi, &(Bool){1});
                        Str_delete(pn, &(Bool){1});
                    }
                    Range_delete(_fc3694, &(Bool){1});
                    ;
                }
                ExprData_delete(&sig->data, &(Bool){0});
                { ExprData *_fa = ExprData_FuncDef(sfd); sig->data = *_fa; free(_fa); }
                FunctionDef_delete(sfd, &(Bool){1});
            }
            ;
            Bool _t3710 = check(p, TokenType_Comma());
            (void)_t3710;
            if (_t3710) {
                Token *_t3706 = advance(p);
                (void)_t3706;
            }
            ;
            Token *_t3711 = expect_token(p, TokenType_RParen());
            (void)_t3711;
            Token *_t3712 = expect_token(p, TokenType_LBrace());
            (void)_t3712;
            Expr *_t3713 = parse_block(p);
            (void)_t3713;
            Expr_add_child(sig, _t3713);
            Bool _t3714 = Bool_clone(&(Bool){is_mut});
            (void)_t3714;
            Bool _t3715 = 0;
            (void)_t3715;
            Bool _t3716 = 0;
            (void)_t3716;
            Bool _t3717 = Bool_clone(&(Bool){is_own});
            (void)_t3717;
            I32 _t3718 = 0;
            (void)_t3718;
            I32 _t3719 = 0;
            (void)_t3719;
            Declaration *dd = malloc(sizeof(Declaration));
            { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
            dd->is_mut = _t3714;
            dd->is_namespace = _t3715;
            dd->is_ref = _t3716;
            dd->is_own = _t3717;
            dd->field_offset = _t3718;
            dd->field_size = _t3719;
            dd->field_struct_def = NULL;
            dd->fn_sig = NULL;
            (void)dd;
            ;
            ;
            ;
            ;
            ;
            ;
            ExprData *_t3720 = ExprData_Decl(dd);
            (void)_t3720;
            Declaration_delete(dd, &(Bool){1});
            Expr *decl = Expr_new(_t3720, t_line, t_col, &p->path);
            (void)decl;
            ExprData_delete(_t3720, &(Bool){1});
            Expr_add_child(decl, sig);
            ;
            ;
            Str_delete(name, &(Bool){1});
            ;
            ;
            return decl;
        }
        ;
        Str *type_name = expect_text(p, TokenType_Ident());
        (void)type_name;
        Str *_t3802 = Str_lit("Fn", 2ULL);
        (void)_t3802;
        Bool _t3803; { Bool *_hp = (Bool *)Str_eq(type_name, _t3802); _t3803 = *_hp; free(_hp); }
        (void)_t3803;
        Str_delete(_t3802, &(Bool){1});
        if (_t3803) {
            Str *syn_name = parse_fn_signature(p, t_line, t_col);
            (void)syn_name;
            U64 _t3721; { U64 *_hp = (U64 *)Str_len(syn_name); _t3721 = *_hp; free(_hp); }
            (void)_t3721;
            U64 _t3722 = 0;
            (void)_t3722;
            Bool _t3723; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3721}, &(U64){_t3722}); _t3723 = *_hp; free(_hp); }
            (void)_t3723;
            ;
            ;
            if (_t3723) {
                type_name = Str_clone(syn_name);
            }
            ;
            Str_delete(syn_name, &(Bool){1});
        }
        ;
        Token *_t3804 = expect_token(p, TokenType_Eq());
        (void)_t3804;
        Bool _t3805 = check(p, TokenType_LParen());
        (void)_t3805;
        if (_t3805) {
            U64 saved = p->pos;
            (void)saved;
            Token *_t3794 = advance(p);
            (void)_t3794;
            Bool is_fsf = 1;
            (void)is_fsf;
            while (1) {
                Bool _t3727 = check(p, TokenType_RParen());
                (void)_t3727;
                Bool _t3728 = check(p, TokenType_Eof());
                (void)_t3728;
                Bool _t3729 = Bool_not(_t3727);
                (void)_t3729;
                ;
                Bool _t3730 = Bool_not(_t3728);
                (void)_t3730;
                ;
                Bool _wcond3724 = Bool_and(_t3729, _t3730);
                (void)_wcond3724;
                ;
                ;
                if (_wcond3724) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3731 = check(p, TokenType_Ident());
                (void)_t3731;
                Bool _t3732 = Bool_not(_t3731);
                (void)_t3732;
                ;
                if (_t3732) {
                    Bool _t3725 = 0;
                    (void)_t3725;
                    is_fsf = _t3725;
                    ;
                    ;
                    break;
                }
                ;
                Token *_t3733 = advance(p);
                (void)_t3733;
                Bool _t3734 = check(p, TokenType_Comma());
                (void)_t3734;
                if (_t3734) {
                    Token *_t3726 = advance(p);
                    (void)_t3726;
                }
                ;
            }
            Bool _t3795 = check(p, TokenType_RParen());
            (void)_t3795;
            Bool _t3796 = Bool_and(is_fsf, _t3795);
            (void)_t3796;
            ;
            if (_t3796) {
                Token *_t3736 = advance(p);
                (void)_t3736;
                Bool _t3737 = check(p, TokenType_LBrace());
                (void)_t3737;
                Bool _t3738 = Bool_not(_t3737);
                (void)_t3738;
                ;
                if (_t3738) {
                    Bool _t3735 = 0;
                    (void)_t3735;
                    is_fsf = _t3735;
                    ;
                }
                ;
            } else {
                Bool _t3739 = 0;
                (void)_t3739;
                is_fsf = _t3739;
                ;
            }
            ;
            U64 _t3797 = U64_clone(&(U64){saved});
            (void)_t3797;
            ;
            p->pos = _t3797;
            ;
            if (is_fsf) {
                Token *_t3754 = expect_token(p, TokenType_LParen());
                (void)_t3754;
                Str *_t3755 = Str_lit("Str", 3ULL);
                (void)_t3755;
                U64 _t3756; { U64 *_hp = (U64 *)Str_size(); _t3756 = *_hp; free(_hp); }
                (void)_t3756;
                Vec *pnames = Vec_new(_t3755, &(U64){_t3756});
                (void)pnames;
                Str_delete(_t3755, &(Bool){1});
                ;
                while (1) {
                    Bool _t3742 = check(p, TokenType_RParen());
                    (void)_t3742;
                    Bool _wcond3740 = Bool_not(_t3742);
                    (void)_wcond3740;
                    ;
                    if (_wcond3740) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *pn = expect_text(p, TokenType_Ident());
                    (void)pn;
                    Vec_push(pnames, pn);
                    Bool _t3743 = check(p, TokenType_Comma());
                    (void)_t3743;
                    if (_t3743) {
                        Token *_t3741 = advance(p);
                        (void)_t3741;
                    }
                    ;
                }
                Token *_t3757 = expect_token(p, TokenType_RParen());
                (void)_t3757;
                Token *_t3758 = expect_token(p, TokenType_LBrace());
                (void)_t3758;
                Expr *body = parse_block(p);
                (void)body;
                Str *_t3759 = Str_lit("Param", 5ULL);
                (void)_t3759;
                U64 _t3760; { U64 *_hp = (U64 *)Param_size(); _t3760 = *_hp; free(_hp); }
                (void)_t3760;
                Str *_t3761 = Str_lit("Str", 3ULL);
                (void)_t3761;
                U64 _t3762; { U64 *_hp = (U64 *)Str_size(); _t3762 = *_hp; free(_hp); }
                (void)_t3762;
                Str *_t3763 = Str_lit("Expr", 4ULL);
                (void)_t3763;
                U64 _t3764; { U64 *_hp = (U64 *)Expr_size(); _t3764 = *_hp; free(_hp); }
                (void)_t3764;
                I64 _t3765 = 0;
                (void)_t3765;
                I64 _t3766 = 1;
                (void)_t3766;
                I64 _t3767 = I64_sub(_t3765, _t3766);
                (void)_t3767;
                ;
                ;
                I64 _t3768 = 0;
                (void)_t3768;
                I64 _t3769 = 1;
                (void)_t3769;
                I64 _t3770 = I64_sub(_t3768, _t3769);
                (void)_t3770;
                ;
                ;
                U32 _t3771 = 0;
                (void)_t3771;
                I32 _t3772 = I64_to_i32(_t3767);
                (void)_t3772;
                ;
                I32 _t3773 = I64_to_i32(_t3770);
                (void)_t3773;
                ;
                Bool _t3774 = 0;
                (void)_t3774;
                Bool _t3775 = 0;
                (void)_t3775;
                FunctionDef *ffd = malloc(sizeof(FunctionDef));
                { FuncType *_ca = FuncType_clone(FuncType_Func()); ffd->func_type = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3759, &(U64){_t3760}); ffd->params = *_ca; free(_ca); }
                ffd->nparam = _t3771;
                { Map *_ca = Map_new(_t3761, &(U64){_t3762}, _t3763, &(U64){_t3764}); ffd->param_defaults = *_ca; free(_ca); }
                { Str *_ca = Str_clone(Str_lit("", 0ULL)); ffd->return_type = *_ca; free(_ca); }
                ffd->variadic_index = _t3772;
                ffd->kwargs_index = _t3773;
                ffd->return_is_ref = _t3774;
                ffd->return_is_shallow = _t3775;
                (void)ffd;
                Str_delete(_t3759, &(Bool){1});
                ;
                Str_delete(_t3761, &(Bool){1});
                ;
                Str_delete(_t3763, &(Bool){1});
                ;
                ;
                ;
                ;
                ;
                ;
                FuncType_delete(&ffd->func_type, &(Bool){0});
                { FuncType *_fa = FuncType_clone(FuncType_Func()); ffd->func_type = *_fa; free(_fa); }
                I64 _t3776 = 0;
                (void)_t3776;
                I64 _t3777 = 1;
                (void)_t3777;
                I64 _t3778 = I64_sub(_t3776, _t3777);
                (void)_t3778;
                ;
                ;
                I32 _t3779 = I64_to_i32(_t3778);
                (void)_t3779;
                ;
                ffd->variadic_index = _t3779;
                ;
                I64 _t3780 = 0;
                (void)_t3780;
                I64 _t3781 = 1;
                (void)_t3781;
                I64 _t3782 = I64_sub(_t3780, _t3781);
                (void)_t3782;
                ;
                ;
                I32 _t3783 = I64_to_i32(_t3782);
                (void)_t3783;
                ;
                ffd->kwargs_index = _t3783;
                ;
                U64 np; { U64 *_hp = (U64 *)Vec_len(pnames); np = *_hp; free(_hp); }
                (void)np;
                {
                    U64 _t3753 = 0;
                    (void)_t3753;
                    Range *_fc3744 = Range_new(_t3753, np);
                    (void)_fc3744;
                    ;
                    U64 _fi3744 = 0;
                    (void)_fi3744;
                    while (1) {
                        U64 _t3746; { U64 *_hp = (U64 *)Range_len(_fc3744); _t3746 = *_hp; free(_hp); }
                        (void)_t3746;
                        Bool _wcond3745; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3744}, &(U64){_t3746}); _wcond3745 = *_hp; free(_hp); }
                        (void)_wcond3745;
                        ;
                        if (_wcond3745) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 *i = Range_get(_fc3744, _fi3744);
                        (void)i;
                        U64 _t3747 = 1;
                        (void)_t3747;
                        U64 _t3748 = U64_add(_fi3744, _t3747);
                        (void)_t3748;
                        ;
                        _fi3744 = _t3748;
                        ;
                        Str *pn = Vec_get(pnames, i);
                        (void)pn;
                        Bool _t3749 = 0;
                        (void)_t3749;
                        Bool _t3750 = 0;
                        (void)_t3750;
                        Bool _t3751 = 0;
                        (void)_t3751;
                        Param *_t3752 = malloc(sizeof(Param));
                        { Str *_ca = Str_clone(pn); _t3752->name = *_ca; free(_ca); }
                        { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t3752->ptype = *_ca; free(_ca); }
                        _t3752->is_mut = _t3749;
                        _t3752->is_own = _t3750;
                        _t3752->is_shallow = _t3751;
                        (void)_t3752;
                        ;
                        ;
                        ;
                        U64_delete(i, &(Bool){1});
                        Vec_push(&ffd->params, _t3752);
                    }
                    Range_delete(_fc3744, &(Bool){1});
                    ;
                }
                Vec_delete(pnames, &(Bool){1});
                I64 _t3784 = U64_to_i64(np);
                (void)_t3784;
                ;
                U32 _t3785 = I64_to_u32(_t3784);
                (void)_t3785;
                ;
                ffd->nparam = _t3785;
                ;
                ExprData *_t3786 = ExprData_FuncDef(ffd);
                (void)_t3786;
                FunctionDef_delete(ffd, &(Bool){1});
                Expr *fdef = Expr_new(_t3786, t_line, t_col, &p->path);
                (void)fdef;
                ExprData_delete(_t3786, &(Bool){1});
                Expr_add_child(fdef, body);
                Bool _t3787 = Bool_clone(&(Bool){is_mut});
                (void)_t3787;
                Bool _t3788 = 0;
                (void)_t3788;
                Bool _t3789 = 0;
                (void)_t3789;
                Bool _t3790 = Bool_clone(&(Bool){is_own});
                (void)_t3790;
                I32 _t3791 = 0;
                (void)_t3791;
                I32 _t3792 = 0;
                (void)_t3792;
                Declaration *dd = malloc(sizeof(Declaration));
                { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
                { Str *_ca = Str_clone(type_name); dd->explicit_type = *_ca; free(_ca); }
                dd->is_mut = _t3787;
                dd->is_namespace = _t3788;
                dd->is_ref = _t3789;
                dd->is_own = _t3790;
                dd->field_offset = _t3791;
                dd->field_size = _t3792;
                dd->field_struct_def = NULL;
                dd->fn_sig = NULL;
                (void)dd;
                ;
                ;
                ;
                ;
                ;
                ;
                ExprData *_t3793 = ExprData_Decl(dd);
                (void)_t3793;
                Declaration_delete(dd, &(Bool){1});
                Expr *decl = Expr_new(_t3793, t_line, t_col, &p->path);
                (void)decl;
                ExprData_delete(_t3793, &(Bool){1});
                Expr_add_child(decl, fdef);
                ;
                ;
                Str_delete(type_name, &(Bool){1});
                ;
                Str_delete(name, &(Bool){1});
                ;
                ;
                return decl;
            }
            ;
        }
        ;
        Bool _t3806 = Bool_clone(&(Bool){is_mut});
        (void)_t3806;
        Bool _t3807 = 0;
        (void)_t3807;
        Bool _t3808 = 0;
        (void)_t3808;
        Bool _t3809 = Bool_clone(&(Bool){is_own});
        (void)_t3809;
        I32 _t3810 = 0;
        (void)_t3810;
        I32 _t3811 = 0;
        (void)_t3811;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(type_name); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3806;
        dd->is_namespace = _t3807;
        dd->is_ref = _t3808;
        dd->is_own = _t3809;
        dd->field_offset = _t3810;
        dd->field_size = _t3811;
        dd->field_struct_def = NULL;
        dd->fn_sig = NULL;
        (void)dd;
        ;
        ;
        ;
        ;
        ;
        ;
        Str_delete(type_name, &(Bool){1});
        ExprData *_t3812 = ExprData_Decl(dd);
        (void)_t3812;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3812, t_line, t_col, &p->path);
        (void)decl;
        ExprData_delete(_t3812, &(Bool){1});
        Expr *_t3813 = parse_expression(p);
        (void)_t3813;
        Expr_add_child(decl, _t3813);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return decl;
    }
    ;
    Bool _t3866 = check(p, TokenType_Dot());
    (void)_t3866;
    if (_t3866) {
        Str *_t3852 = Str_clone(name);
        (void)_t3852;
        ExprData *_t3853 = ExprData_Ident(_t3852);
        (void)_t3853;
        Str_delete(_t3852, &(Bool){1});
        Expr *obj = Expr_new(_t3853, t_line, t_col, &p->path);
        (void)obj;
        ExprData_delete(_t3853, &(Bool){1});
        Str *last_field = Str_lit("", 0ULL);
        (void)last_field;
        U32 last_line = 0;
        (void)last_line;
        U32 last_col = 0;
        (void)last_col;
        while (1) {
            Bool _wcond3814 = check(p, TokenType_Dot());
            (void)_wcond3814;
            if (_wcond3814) {
            } else {
                ;
                break;
            }
            ;
            Token *_t3818 = advance(p);
            (void)_t3818;
            U32 _t3819 = peek_line(p);
            (void)_t3819;
            last_line = _t3819;
            ;
            U32 _t3820 = peek_col(p);
            (void)_t3820;
            last_col = _t3820;
            ;
            last_field = expect_text(p, TokenType_Ident());
            Bool _t3821 = check(p, TokenType_Dot());
            (void)_t3821;
            if (_t3821) {
                Str *_t3815 = Str_clone(last_field);
                (void)_t3815;
                ExprData *_t3816 = ExprData_FieldAccess(_t3815);
                (void)_t3816;
                Str_delete(_t3815, &(Bool){1});
                Expr *access = Expr_new(_t3816, last_line, last_col, &p->path);
                (void)access;
                ExprData_delete(_t3816, &(Bool){1});
                Expr *_t3817 = Expr_clone(obj);
                (void)_t3817;
                Expr_add_child(access, _t3817);
                obj = Expr_clone(access);
                Expr_delete(access, &(Bool){1});
            }
            ;
        }
        Bool _t3854 = check(p, TokenType_LParen());
        (void)_t3854;
        if (_t3854) {
            Token *_t3848 = advance(p);
            (void)_t3848;
            ExprData *_t3849 = ExprData_FieldAccess(last_field);
            (void)_t3849;
            Expr *callee = Expr_new(_t3849, last_line, last_col, &p->path);
            (void)callee;
            ExprData_delete(_t3849, &(Bool){1});
            Expr *_t3850 = Expr_clone(obj);
            (void)_t3850;
            Expr_add_child(callee, _t3850);
            Expr *mcall = Expr_new(ExprData_FCall(), last_line, last_col, &p->path);
            (void)mcall;
            Expr_add_child(mcall, callee);
            while (1) {
                Bool _t3840 = check(p, TokenType_RParen());
                (void)_t3840;
                Bool _t3841 = check(p, TokenType_Eof());
                (void)_t3841;
                Bool _t3842 = Bool_not(_t3840);
                (void)_t3842;
                ;
                Bool _t3843 = Bool_not(_t3841);
                (void)_t3843;
                ;
                Bool _wcond3822 = Bool_and(_t3842, _t3843);
                (void)_wcond3822;
                ;
                ;
                if (_wcond3822) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3844 = check(p, TokenType_Ident());
                (void)_t3844;
                if (_t3844) {
                    U64 _t3833 = 1;
                    (void)_t3833;
                    U64 _t3834 = U64_add(p->pos, _t3833);
                    (void)_t3834;
                    ;
                    U64 _t3835; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3835 = *_hp; free(_hp); }
                    (void)_t3835;
                    Bool _t3836; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3834}, &(U64){_t3835}); _t3836 = *_hp; free(_hp); }
                    (void)_t3836;
                    ;
                    ;
                    if (_t3836) {
                        U64 _t3828 = 1;
                        (void)_t3828;
                        U64 _t3829 = U64_add(p->pos, _t3828);
                        (void)_t3829;
                        ;
                        I64 _t3830 = U64_to_i64(_t3829);
                        (void)_t3830;
                        ;
                        U64 *_t3831 = malloc(sizeof(U64)); *_t3831 = I64_to_u64(_t3830);
                        (void)_t3831;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3831);
                        (void)nt;
                        Bool _t3832; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3832 = *_hp; free(_hp); }
                        (void)_t3832;
                        U64_delete(_t3831, &(Bool){1});
                        if (_t3832) {
                            U32 na_line = peek_line(p);
                            (void)na_line;
                            U32 na_col = peek_col(p);
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3824 = advance(p);
                            (void)_t3824;
                            ExprData *_t3825 = ExprData_NamedArg(aname);
                            (void)_t3825;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3825, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3825, &(Bool){1});
                            ;
                            ;
                            Expr *_t3826 = parse_expression(p);
                            (void)_t3826;
                            Expr_add_child(na, _t3826);
                            Expr_add_child(mcall, na);
                            Bool _t3827 = check(p, TokenType_Comma());
                            (void)_t3827;
                            if (_t3827) {
                                Token *_t3823 = advance(p);
                                (void)_t3823;
                            }
                            ;
                            ;
                            ;
                            ;
                            continue;
                        }
                        ;
                    }
                    ;
                }
                ;
                Bool is_own_arg = 0;
                (void)is_own_arg;
                Bool _t3845 = check(p, TokenType_KwOwn());
                (void)_t3845;
                if (_t3845) {
                    Token *_t3837 = advance(p);
                    (void)_t3837;
                    Bool _t3838 = 1;
                    (void)_t3838;
                    is_own_arg = _t3838;
                    ;
                }
                ;
                Expr *marg = parse_expression(p);
                (void)marg;
                Bool _t3846 = Bool_clone(&(Bool){is_own_arg});
                (void)_t3846;
                ;
                marg->is_own_arg = _t3846;
                ;
                Expr_add_child(mcall, marg);
                Bool _t3847 = check(p, TokenType_Comma());
                (void)_t3847;
                if (_t3847) {
                    Token *_t3839 = advance(p);
                    (void)_t3839;
                }
                ;
            }
            Token *_t3851 = expect_token(p, TokenType_RParen());
            (void)_t3851;
            ;
            ;
            Str_delete(last_field, &(Bool){1});
            ;
            Expr_delete(obj, &(Bool){1});
            ;
            Str_delete(name, &(Bool){1});
            ;
            ;
            return mcall;
        }
        ;
        ;
        ;
        Token *_t3855 = expect_token(p, TokenType_Eq());
        (void)_t3855;
        ExprData *_t3856 = ExprData_FieldAssign(last_field);
        (void)_t3856;
        Str_delete(last_field, &(Bool){1});
        Expr *fa = Expr_new(_t3856, t_line, t_col, &p->path);
        (void)fa;
        ExprData_delete(_t3856, &(Bool){1});
        Expr *_t3857 = Expr_clone(obj);
        (void)_t3857;
        Expr_delete(obj, &(Bool){1});
        Expr_add_child(fa, _t3857);
        Expr *_t3858 = parse_expression(p);
        (void)_t3858;
        Expr_add_child(fa, _t3858);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return fa;
    }
    ;
    Bool _t3867 = check(p, TokenType_Eq());
    (void)_t3867;
    if (_t3867) {
        Token *_t3859 = advance(p);
        (void)_t3859;
        Str *_t3860 = Str_clone(name);
        (void)_t3860;
        ExprData *_t3861 = ExprData_Assign(_t3860);
        (void)_t3861;
        Str_delete(_t3860, &(Bool){1});
        Expr *assign = Expr_new(_t3861, t_line, t_col, &p->path);
        (void)assign;
        ExprData_delete(_t3861, &(Bool){1});
        Expr *_t3862 = parse_expression(p);
        (void)_t3862;
        Expr_add_child(assign, _t3862);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return assign;
    }
    ;
    Bool _t3868 = check(p, TokenType_LParen());
    (void)_t3868;
    if (_t3868) {
        Expr *_t3863 = parse_call(p, name, t_line, t_col);
        (void)_t3863;
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return _t3863;
    }
    ;
    Str *_t3869 = Str_lit("Str", 3ULL);
    (void)_t3869;
    U64 _t3870; { U64 *_hp = (U64 *)Str_size(); _t3870 = *_hp; free(_hp); }
    (void)_t3870;
    U64 _t3871 = 8;
    (void)_t3871;
    Array *_va72 = Array_new(_t3869, &(U64){_t3870}, &(U64){_t3871});
    (void)_va72;
    Str_delete(_t3869, &(Bool){1});
    ;
    ;
    U64 _t3872 = 0;
    (void)_t3872;
    Str *_t3873 = Str_clone(&p->path);
    (void)_t3873;
    Array_set(_va72, &(U64){_t3872}, _t3873);
    ;
    U64 _t3874 = 1;
    (void)_t3874;
    Str *_t3875 = Str_lit(":", 1ULL);
    (void)_t3875;
    Array_set(_va72, &(U64){_t3874}, _t3875);
    ;
    U64 _t3876 = 2;
    (void)_t3876;
    Str *_t3877 = U32_to_str(&(U32){t_line});
    (void)_t3877;
    ;
    Array_set(_va72, &(U64){_t3876}, _t3877);
    ;
    U64 _t3878 = 3;
    (void)_t3878;
    Str *_t3879 = Str_lit(":", 1ULL);
    (void)_t3879;
    Array_set(_va72, &(U64){_t3878}, _t3879);
    ;
    U64 _t3880 = 4;
    (void)_t3880;
    Str *_t3881 = U32_to_str(&(U32){t_col});
    (void)_t3881;
    ;
    Array_set(_va72, &(U64){_t3880}, _t3881);
    ;
    U64 _t3882 = 5;
    (void)_t3882;
    Str *_t3883 = Str_lit(": expected ':=', ':', '=' or '(' after identifier '", 51ULL);
    (void)_t3883;
    Array_set(_va72, &(U64){_t3882}, _t3883);
    ;
    U64 _t3884 = 6;
    (void)_t3884;
    Str *_t3885 = Str_clone(name);
    (void)_t3885;
    Str_delete(name, &(Bool){1});
    Array_set(_va72, &(U64){_t3884}, _t3885);
    ;
    U64 _t3886 = 7;
    (void)_t3886;
    Str *_t3887 = Str_lit("'", 1ULL);
    (void)_t3887;
    Array_set(_va72, &(U64){_t3886}, _t3887);
    ;
    Str *_t3888 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:797:11", 64ULL);
    (void)_t3888;
    panic(_t3888, _va72);
    Str_delete(_t3888, &(Bool){1});
    U32 _t3889 = 0;
    (void)_t3889;
    U32 _t3890 = 0;
    (void)_t3890;
    Expr *_t3891 = Expr_new(ExprData_Body(), _t3889, _t3890, &p->path);
    (void)_t3891;
    ;
    ;
    return _t3891;
}

Expr * parse_statement(Parser * p) {
    (void)p;
    U32 t_line = peek_line(p);
    (void)t_line;
    U32 t_col = peek_col(p);
    (void)t_col;
    Token *t = peek(p);
    (void)t;
    Bool _t4029; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t4029 = *_hp; free(_hp); }
    (void)_t4029;
    if (_t4029) {
        Bool _t3892 = 0;
        (void)_t3892;
        Bool _t3893 = 0;
        (void)_t3893;
        Expr *_t3894 = parse_statement_ident(p, _t3892, _t3893);
        (void)_t3894;
        ;
        ;
        ;
        ;
        ;
        return _t3894;
    }
    ;
    Bool _t4030; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwRef()); _t4030 = *_hp; free(_hp); }
    (void)_t4030;
    if (_t4030) {
        Token *_t3901 = advance(p);
        (void)_t3901;
        Bool ref_mut = 0;
        (void)ref_mut;
        Bool _t3902 = check(p, TokenType_KwMut());
        (void)_t3902;
        if (_t3902) {
            Token *_t3895 = advance(p);
            (void)_t3895;
            Bool _t3896 = 1;
            (void)_t3896;
            ref_mut = _t3896;
            ;
        }
        ;
        U32 i_line = peek_line(p);
        (void)i_line;
        U32 i_col = peek_col(p);
        (void)i_col;
        Str *iname = expect_text(p, TokenType_Ident());
        (void)iname;
        Bool _t3903 = 0;
        (void)_t3903;
        Bool _t3904 = 0;
        (void)_t3904;
        Bool _t3905 = 1;
        (void)_t3905;
        Bool _t3906 = 0;
        (void)_t3906;
        I32 _t3907 = 0;
        (void)_t3907;
        I32 _t3908 = 0;
        (void)_t3908;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(iname); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3903;
        dd->is_namespace = _t3904;
        dd->is_ref = _t3905;
        dd->is_own = _t3906;
        dd->field_offset = _t3907;
        dd->field_size = _t3908;
        dd->field_struct_def = NULL;
        dd->fn_sig = NULL;
        (void)dd;
        ;
        ;
        ;
        ;
        ;
        ;
        Str_delete(iname, &(Bool){1});
        if (ref_mut) {
            Bool _t3897 = 1;
            (void)_t3897;
            dd->is_mut = _t3897;
            ;
        }
        ;
        Bool _t3909 = check(p, TokenType_Colon());
        (void)_t3909;
        if (_t3909) {
            Token *_t3898 = advance(p);
            (void)_t3898;
            Str_delete(&dd->explicit_type, &(Bool){0});
            { Str *_fa = expect_text(p, TokenType_Ident()); dd->explicit_type = *_fa; free(_fa); }
            Token *_t3899 = expect_token(p, TokenType_Eq());
            (void)_t3899;
        } else {
            Token *_t3900 = expect_token(p, TokenType_ColonEq());
            (void)_t3900;
        }
        ;
        ExprData *_t3910 = ExprData_Decl(dd);
        (void)_t3910;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3910, i_line, i_col, &p->path);
        (void)decl;
        ExprData_delete(_t3910, &(Bool){1});
        ;
        ;
        Expr *_t3911 = parse_expression(p);
        (void)_t3911;
        Expr_add_child(decl, _t3911);
        ;
        ;
        ;
        return decl;
    }
    ;
    Bool _t4031; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMut()); _t4031 = *_hp; free(_hp); }
    (void)_t4031;
    if (_t4031) {
        Token *_t3912 = advance(p);
        (void)_t3912;
        Bool _t3913 = 1;
        (void)_t3913;
        Bool _t3914 = 0;
        (void)_t3914;
        Expr *_t3915 = parse_statement_ident(p, _t3913, _t3914);
        (void)_t3915;
        ;
        ;
        ;
        ;
        ;
        return _t3915;
    }
    ;
    Bool _t4032; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwReturn()); _t4032 = *_hp; free(_hp); }
    (void)_t4032;
    if (_t4032) {
        Token *_t3917 = advance(p);
        (void)_t3917;
        Expr *ret = Expr_new(ExprData_Return(), t_line, t_col, &p->path);
        (void)ret;
        Bool _t3918 = check(p, TokenType_RBrace());
        (void)_t3918;
        Bool _t3919 = check(p, TokenType_Eof());
        (void)_t3919;
        Bool _t3920 = Bool_not(_t3918);
        (void)_t3920;
        ;
        Bool _t3921 = Bool_not(_t3919);
        (void)_t3921;
        ;
        Bool _t3922 = Bool_and(_t3920, _t3921);
        (void)_t3922;
        ;
        ;
        if (_t3922) {
            Expr *_t3916 = parse_expression(p);
            (void)_t3916;
            Expr_add_child(ret, _t3916);
        }
        ;
        ;
        ;
        ;
        return ret;
    }
    ;
    Bool _t4033; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwIf()); _t4033 = *_hp; free(_hp); }
    (void)_t4033;
    if (_t4033) {
        Token *_t3930 = advance(p);
        (void)_t3930;
        Expr *node = Expr_new(ExprData_If(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t3931 = parse_expression(p);
        (void)_t3931;
        Expr_add_child(node, _t3931);
        Token *_t3932 = expect_token(p, TokenType_LBrace());
        (void)_t3932;
        Expr *_t3933 = parse_block(p);
        (void)_t3933;
        Expr_add_child(node, _t3933);
        Bool _t3934 = check(p, TokenType_KwElse());
        (void)_t3934;
        if (_t3934) {
            Token *_t3928 = advance(p);
            (void)_t3928;
            Bool _t3929 = check(p, TokenType_KwIf());
            (void)_t3929;
            if (_t3929) {
                U32 _t3923 = peek_line(p);
                (void)_t3923;
                U32 _t3924 = peek_col(p);
                (void)_t3924;
                Expr *else_body = Expr_new(ExprData_Body(), _t3923, _t3924, &p->path);
                (void)else_body;
                ;
                ;
                Expr *_t3925 = parse_statement(p);
                (void)_t3925;
                Expr_add_child(else_body, _t3925);
                Expr_add_child(node, else_body);
            } else {
                Token *_t3926 = expect_token(p, TokenType_LBrace());
                (void)_t3926;
                Expr *_t3927 = parse_block(p);
                (void)_t3927;
                Expr_add_child(node, _t3927);
            }
            ;
        }
        ;
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4034; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t4034 = *_hp; free(_hp); }
    (void)_t4034;
    Bool _t4035; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t4035 = *_hp; free(_hp); }
    (void)_t4035;
    Bool _t4036 = Bool_or(_t4034, _t4035);
    (void)_t4036;
    ;
    ;
    Bool _t4037; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t4037 = *_hp; free(_hp); }
    (void)_t4037;
    Bool _t4038 = Bool_or(_t4036, _t4037);
    (void)_t4038;
    ;
    ;
    Bool _t4039; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t4039 = *_hp; free(_hp); }
    (void)_t4039;
    Bool _t4040 = Bool_or(_t4038, _t4039);
    (void)_t4040;
    ;
    ;
    Bool _t4041; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwNull()); _t4041 = *_hp; free(_hp); }
    (void)_t4041;
    Bool _t4042 = Bool_or(_t4040, _t4041);
    (void)_t4042;
    ;
    ;
    if (_t4042) {
        Expr *_t3935 = parse_expression(p);
        (void)_t3935;
        ;
        ;
        ;
        return _t3935;
    }
    ;
    Bool _t4043; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t4043 = *_hp; free(_hp); }
    (void)_t4043;
    if (_t4043) {
        Token *_t3936 = advance(p);
        (void)_t3936;
        Expr *_t3937 = parse_block(p);
        (void)_t3937;
        ;
        ;
        ;
        return _t3937;
    }
    ;
    Bool _t4044; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwWhile()); _t4044 = *_hp; free(_hp); }
    (void)_t4044;
    if (_t4044) {
        Token *_t3938 = advance(p);
        (void)_t3938;
        Expr *node = Expr_new(ExprData_While(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t3939 = parse_expression(p);
        (void)_t3939;
        Expr_add_child(node, _t3939);
        Token *_t3940 = expect_token(p, TokenType_LBrace());
        (void)_t3940;
        Expr *_t3941 = parse_block(p);
        (void)_t3941;
        Expr_add_child(node, _t3941);
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4045; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFor()); _t4045 = *_hp; free(_hp); }
    (void)_t4045;
    if (_t4045) {
        Token *_t3943 = advance(p);
        (void)_t3943;
        U32 i_line = peek_line(p);
        (void)i_line;
        U32 i_col = peek_col(p);
        (void)i_col;
        Str *iname = expect_text(p, TokenType_Ident());
        (void)iname;
        ExprData *_t3944 = ExprData_ForIn(iname);
        (void)_t3944;
        Str_delete(iname, &(Bool){1});
        Expr *node = Expr_new(_t3944, i_line, i_col, &p->path);
        (void)node;
        ExprData_delete(_t3944, &(Bool){1});
        ;
        ;
        Bool _t3945 = check(p, TokenType_Colon());
        (void)_t3945;
        if (_t3945) {
            Token *_t3942 = advance(p);
            (void)_t3942;
            Str_delete(&node->struct_name, &(Bool){0});
            { Str *_fa = expect_text(p, TokenType_Ident()); node->struct_name = *_fa; free(_fa); }
        }
        ;
        Token *_t3946 = expect_token(p, TokenType_KwIn());
        (void)_t3946;
        Expr *_t3947 = parse_expression(p);
        (void)_t3947;
        Expr_add_child(node, _t3947);
        Token *_t3948 = expect_token(p, TokenType_LBrace());
        (void)_t3948;
        Expr *_t3949 = parse_block(p);
        (void)_t3949;
        Expr_add_child(node, _t3949);
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4046; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwSwitch()); _t4046 = *_hp; free(_hp); }
    (void)_t4046;
    if (_t4046) {
        Token *_t3973 = advance(p);
        (void)_t3973;
        Expr *node = Expr_new(ExprData_Switch(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t3974 = parse_expression(p);
        (void)_t3974;
        Expr_add_child(node, _t3974);
        Token *_t3975 = expect_token(p, TokenType_LBrace());
        (void)_t3975;
        while (1) {
            Bool _t3961 = check(p, TokenType_RBrace());
            (void)_t3961;
            Bool _t3962 = check(p, TokenType_Eof());
            (void)_t3962;
            Bool _t3963 = Bool_not(_t3961);
            (void)_t3963;
            ;
            Bool _t3964 = Bool_not(_t3962);
            (void)_t3964;
            ;
            Bool _wcond3950 = Bool_and(_t3963, _t3964);
            (void)_wcond3950;
            ;
            ;
            if (_wcond3950) {
            } else {
                ;
                break;
            }
            ;
            Token *_t3965 = expect_token(p, TokenType_KwCase());
            (void)_t3965;
            U32 _t3966 = peek_line(p);
            (void)_t3966;
            U32 _t3967 = peek_col(p);
            (void)_t3967;
            Expr *cn = Expr_new(ExprData_Case(), _t3966, _t3967, &p->path);
            (void)cn;
            ;
            ;
            Bool _t3968 = check(p, TokenType_Colon());
            (void)_t3968;
            Bool _t3969 = Bool_not(_t3968);
            (void)_t3969;
            ;
            if (_t3969) {
                Expr *_t3951 = parse_expression(p);
                (void)_t3951;
                Expr_add_child(cn, _t3951);
            }
            ;
            Token *_t3970 = expect_token(p, TokenType_Colon());
            (void)_t3970;
            U32 _t3971 = peek_line(p);
            (void)_t3971;
            U32 _t3972 = peek_col(p);
            (void)_t3972;
            Expr *cb = Expr_new(ExprData_Body(), _t3971, _t3972, &p->path);
            (void)cb;
            ;
            ;
            while (1) {
                Bool _t3953 = check(p, TokenType_KwCase());
                (void)_t3953;
                Bool _t3954 = check(p, TokenType_RBrace());
                (void)_t3954;
                Bool _t3955 = Bool_not(_t3953);
                (void)_t3955;
                ;
                Bool _t3956 = Bool_not(_t3954);
                (void)_t3956;
                ;
                Bool _t3957 = check(p, TokenType_Eof());
                (void)_t3957;
                Bool _t3958 = Bool_and(_t3955, _t3956);
                (void)_t3958;
                ;
                ;
                Bool _t3959 = Bool_not(_t3957);
                (void)_t3959;
                ;
                Bool _wcond3952 = Bool_and(_t3958, _t3959);
                (void)_wcond3952;
                ;
                ;
                if (_wcond3952) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3960 = parse_statement(p);
                (void)_t3960;
                Expr_add_child(cb, _t3960);
            }
            Expr_add_child(cn, cb);
            Expr_add_child(node, cn);
        }
        Token *_t3976 = expect_token(p, TokenType_RBrace());
        (void)_t3976;
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4047; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwOwn()); _t4047 = *_hp; free(_hp); }
    (void)_t4047;
    if (_t4047) {
        Token *_t4018 = advance(p);
        (void)_t4018;
        Bool _t4019 = check(p, TokenType_Ident());
        (void)_t4019;
        Bool _t4020 = check(p, TokenType_KwMut());
        (void)_t4020;
        Bool _t4021 = Bool_or(_t4019, _t4020);
        (void)_t4021;
        ;
        ;
        if (_t4021) {
            Bool own_mut = 0;
            (void)own_mut;
            Bool _t4008 = check(p, TokenType_KwMut());
            (void)_t4008;
            if (_t4008) {
                Token *_t3977 = advance(p);
                (void)_t3977;
                Bool _t3978 = 1;
                (void)_t3978;
                own_mut = _t3978;
                ;
            }
            ;
            Bool _t4009 = check(p, TokenType_Ident());
            (void)_t4009;
            if (_t4009) {
                U64 _t3988 = 1;
                (void)_t3988;
                U64 _t3989 = U64_add(p->pos, _t3988);
                (void)_t3989;
                ;
                U64 _t3990; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3990 = *_hp; free(_hp); }
                (void)_t3990;
                Bool _t3991; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3989}, &(U64){_t3990}); _t3991 = *_hp; free(_hp); }
                (void)_t3991;
                ;
                ;
                if (_t3991) {
                    U64 _t3981 = 1;
                    (void)_t3981;
                    U64 _t3982 = U64_add(p->pos, _t3981);
                    (void)_t3982;
                    ;
                    I64 _t3983 = U64_to_i64(_t3982);
                    (void)_t3983;
                    ;
                    U64 *_t3984 = malloc(sizeof(U64)); *_t3984 = I64_to_u64(_t3983);
                    (void)_t3984;
                    ;
                    Token *nt = Vec_get(&p->tokens, _t3984);
                    (void)nt;
                    Bool _t3985; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_ColonEq()); _t3985 = *_hp; free(_hp); }
                    (void)_t3985;
                    Bool _t3986; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Colon()); _t3986 = *_hp; free(_hp); }
                    (void)_t3986;
                    U64_delete(_t3984, &(Bool){1});
                    Bool _t3987 = Bool_or(_t3985, _t3986);
                    (void)_t3987;
                    ;
                    ;
                    if (_t3987) {
                        Bool _t3979 = 1;
                        (void)_t3979;
                        Expr *_t3980 = parse_statement_ident(p, own_mut, _t3979);
                        (void)_t3980;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        return _t3980;
                    }
                    ;
                }
                ;
            }
            ;
            if (own_mut) {
                Str *_t3992 = Str_lit("Str", 3ULL);
                (void)_t3992;
                U64 _t3993; { U64 *_hp = (U64 *)Str_size(); _t3993 = *_hp; free(_hp); }
                (void)_t3993;
                U64 _t3994 = 6;
                (void)_t3994;
                Array *_va73 = Array_new(_t3992, &(U64){_t3993}, &(U64){_t3994});
                (void)_va73;
                Str_delete(_t3992, &(Bool){1});
                ;
                ;
                U64 _t3995 = 0;
                (void)_t3995;
                Str *_t3996 = Str_clone(&p->path);
                (void)_t3996;
                Array_set(_va73, &(U64){_t3995}, _t3996);
                ;
                U64 _t3997 = 1;
                (void)_t3997;
                Str *_t3998 = Str_lit(":", 1ULL);
                (void)_t3998;
                Array_set(_va73, &(U64){_t3997}, _t3998);
                ;
                U64 _t3999 = 2;
                (void)_t3999;
                Str *_t4000 = U32_to_str(&(U32){t_line});
                (void)_t4000;
                Array_set(_va73, &(U64){_t3999}, _t4000);
                ;
                U64 _t4001 = 3;
                (void)_t4001;
                Str *_t4002 = Str_lit(":", 1ULL);
                (void)_t4002;
                Array_set(_va73, &(U64){_t4001}, _t4002);
                ;
                U64 _t4003 = 4;
                (void)_t4003;
                Str *_t4004 = U32_to_str(&(U32){t_col});
                (void)_t4004;
                Array_set(_va73, &(U64){_t4003}, _t4004);
                ;
                U64 _t4005 = 5;
                (void)_t4005;
                Str *_t4006 = Str_lit(": expected identifier after 'own mut'", 37ULL);
                (void)_t4006;
                Array_set(_va73, &(U64){_t4005}, _t4006);
                ;
                Str *_t4007 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:931:23", 64ULL);
                (void)_t4007;
                panic(_t4007, _va73);
                Str_delete(_t4007, &(Bool){1});
            }
            ;
        }
        ;
        Expr *expr = parse_expression(p);
        (void)expr;
        I64 _t4022 = 0;
        (void)_t4022;
        I64 _t4023 = 1;
        (void)_t4023;
        I64 primary_idx = I64_sub(_t4022, _t4023);
        (void)primary_idx;
        ;
        ;
        ;
        Expr *cur = Expr_clone(expr);
        (void)cur;
        while (1) {
            U64 _t4011; { U64 *_hp = (U64 *)Vec_len(&cur->children); _t4011 = *_hp; free(_hp); }
            (void)_t4011;
            U64 _t4012 = 0;
            (void)_t4012;
            Bool _t4013; { Bool *_hp = (Bool *)ExprData_is_FCall(&cur->data); _t4013 = *_hp; free(_hp); }
            (void)_t4013;
            Bool _t4014; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(&cur->data); _t4014 = *_hp; free(_hp); }
            (void)_t4014;
            Bool _t4015; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4011}, &(U64){_t4012}); _t4015 = *_hp; free(_hp); }
            (void)_t4015;
            ;
            ;
            Bool _t4016 = Bool_or(_t4013, _t4014);
            (void)_t4016;
            ;
            ;
            Bool _wcond4010 = Bool_and(_t4015, _t4016);
            (void)_wcond4010;
            ;
            ;
            if (_wcond4010) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t4017 = malloc(sizeof(U64));
            *_t4017 = 0;
            (void)_t4017;
            Expr *ch = Vec_get(&cur->children, _t4017);
            (void)ch;
            cur = Expr_clone(ch);
            U64_delete(_t4017, &(Bool){1});
        }
        Bool _t4024 = 1;
        (void)_t4024;
        cur->is_own_arg = _t4024;
        ;
        Expr_delete(cur, &(Bool){1});
        ;
        ;
        ;
        ;
        return expr;
    }
    ;
    Bool _t4048; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwBreak()); _t4048 = *_hp; free(_hp); }
    (void)_t4048;
    if (_t4048) {
        Token *_t4025 = advance(p);
        (void)_t4025;
        Expr *_t4026 = Expr_new(ExprData_Break(), t_line, t_col, &p->path);
        (void)_t4026;
        ;
        ;
        ;
        return _t4026;
    }
    ;
    Bool _t4049; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwContinue()); _t4049 = *_hp; free(_hp); }
    (void)_t4049;
    if (_t4049) {
        Token *_t4027 = advance(p);
        (void)_t4027;
        Expr *_t4028 = Expr_new(ExprData_Continue(), t_line, t_col, &p->path);
        (void)_t4028;
        ;
        ;
        ;
        return _t4028;
    }
    ;
    Str *_t4050 = Str_lit("Str", 3ULL);
    (void)_t4050;
    U64 _t4051; { U64 *_hp = (U64 *)Str_size(); _t4051 = *_hp; free(_hp); }
    (void)_t4051;
    U64 _t4052 = 8;
    (void)_t4052;
    Array *_va74 = Array_new(_t4050, &(U64){_t4051}, &(U64){_t4052});
    (void)_va74;
    Str_delete(_t4050, &(Bool){1});
    ;
    ;
    U64 _t4053 = 0;
    (void)_t4053;
    Str *_t4054 = Str_clone(&p->path);
    (void)_t4054;
    Array_set(_va74, &(U64){_t4053}, _t4054);
    ;
    U64 _t4055 = 1;
    (void)_t4055;
    Str *_t4056 = Str_lit(":", 1ULL);
    (void)_t4056;
    Array_set(_va74, &(U64){_t4055}, _t4056);
    ;
    U64 _t4057 = 2;
    (void)_t4057;
    Str *_t4058 = U32_to_str(&(U32){t_line});
    (void)_t4058;
    ;
    Array_set(_va74, &(U64){_t4057}, _t4058);
    ;
    U64 _t4059 = 3;
    (void)_t4059;
    Str *_t4060 = Str_lit(":", 1ULL);
    (void)_t4060;
    Array_set(_va74, &(U64){_t4059}, _t4060);
    ;
    U64 _t4061 = 4;
    (void)_t4061;
    Str *_t4062 = U32_to_str(&(U32){t_col});
    (void)_t4062;
    ;
    Array_set(_va74, &(U64){_t4061}, _t4062);
    ;
    U64 _t4063 = 5;
    (void)_t4063;
    Str *_t4064 = Str_lit(": expected statement, found '", 29ULL);
    (void)_t4064;
    Array_set(_va74, &(U64){_t4063}, _t4064);
    ;
    U64 _t4065 = 6;
    (void)_t4065;
    Str *_t4066 = Str_clone(&t->text);
    (void)_t4066;
    Array_set(_va74, &(U64){_t4065}, _t4066);
    ;
    U64 _t4067 = 7;
    (void)_t4067;
    Str *_t4068 = Str_lit("'", 1ULL);
    (void)_t4068;
    Array_set(_va74, &(U64){_t4067}, _t4068);
    ;
    Str *_t4069 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:958:11", 64ULL);
    (void)_t4069;
    panic(_t4069, _va74);
    Str_delete(_t4069, &(Bool){1});
    U32 _t4070 = 0;
    (void)_t4070;
    U32 _t4071 = 0;
    (void)_t4071;
    Expr *_t4072 = Expr_new(ExprData_Body(), _t4070, _t4071, &p->path);
    (void)_t4072;
    ;
    ;
    return _t4072;
}

Expr * parse(Vec * tokens, Str * path, Str * mode_out) {
    (void)tokens;
    (void)path;
    (void)mode_out;
    Str *_t4092 = Str_lit("Expr", 4ULL);
    (void)_t4092;
    U64 _t4093; { U64 *_hp = (U64 *)Expr_size(); _t4093 = *_hp; free(_hp); }
    (void)_t4093;
    I64 _t4094 = 0;
    (void)_t4094;
    Parser *p = malloc(sizeof(Parser));
    { Vec *_ca = Vec_clone(tokens); p->tokens = *_ca; free(_ca); }
    p->pos = _t4094;
    { Str *_ca = Str_clone(path); p->path = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t4092, &(U64){_t4093}); p->fn_sig_decls = *_ca; free(_ca); }
    (void)p;
    Str_delete(_t4092, &(Bool){1});
    ;
    ;
    Bool _t4095 = check(p, TokenType_KwMode());
    (void)_t4095;
    if (_t4095) {
        Token *_t4077 = advance(p);
        (void)_t4077;
        Bool _t4078 = check(p, TokenType_Ident());
        (void)_t4078;
        Bool _t4079 = check(p, TokenType_KwTest());
        (void)_t4079;
        Bool _t4080 = Bool_or(_t4078, _t4079);
        (void)_t4080;
        ;
        ;
        if (_t4080) {
            Str *_t4073 = Str_clone(&peek(p)->text);
            (void)_t4073;
            U64 _t4074; { U64 *_hp = (U64 *)Str_size(); _t4074 = *_hp; free(_hp); }
            (void)_t4074;
            swap(mode_out, _t4073, _t4074);
            Str_delete(_t4073, &(Bool){1});
            ;
            Token *_t4075 = advance(p);
            (void)_t4075;
        } else {
            Token *_t4076 = expect_token(p, TokenType_Ident());
            (void)_t4076;
        }
        ;
    }
    ;
    U32 _t4096 = 1;
    (void)_t4096;
    U32 _t4097 = 1;
    (void)_t4097;
    Expr *root = Expr_new(ExprData_Body(), _t4096, _t4097, &p->path);
    (void)root;
    ;
    ;
    while (1) {
        Bool _t4082 = check(p, TokenType_Eof());
        (void)_t4082;
        Bool _wcond4081 = Bool_not(_t4082);
        (void)_wcond4081;
        ;
        if (_wcond4081) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t4083 = parse_statement(p);
        (void)_t4083;
        Expr_add_child(root, _t4083);
    }
    {
        U64 _t4090 = 0;
        (void)_t4090;
        U64 _t4091; { U64 *_hp = (U64 *)Vec_len(&p->fn_sig_decls); _t4091 = *_hp; free(_hp); }
        (void)_t4091;
        Range *_fc4084 = Range_new(_t4090, _t4091);
        (void)_fc4084;
        ;
        ;
        U64 _fi4084 = 0;
        (void)_fi4084;
        while (1) {
            U64 _t4086; { U64 *_hp = (U64 *)Range_len(_fc4084); _t4086 = *_hp; free(_hp); }
            (void)_t4086;
            Bool _wcond4085; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi4084}, &(U64){_t4086}); _wcond4085 = *_hp; free(_hp); }
            (void)_wcond4085;
            ;
            if (_wcond4085) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc4084, _fi4084);
            (void)i;
            U64 _t4087 = 1;
            (void)_t4087;
            U64 _t4088 = U64_add(_fi4084, _t4087);
            (void)_t4088;
            ;
            _fi4084 = _t4088;
            ;
            Expr *d = Vec_get(&p->fn_sig_decls, i);
            (void)d;
            Expr *_t4089 = Expr_clone(d);
            (void)_t4089;
            U64_delete(i, &(Bool){1});
            Expr_add_child(root, _t4089);
        }
        Range_delete(_fc4084, &(Bool){1});
        ;
    }
    Parser_delete(p, &(Bool){1});
    return root;
}

