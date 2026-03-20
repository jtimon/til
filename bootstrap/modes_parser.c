#include "modes_parser.h"

Parser * Parser_clone(Parser * self) {
    (void)self;
    U64 _t2967 = U64_clone(&self->pos);
    (void)_t2967;
    Parser *_t2968 = malloc(sizeof(Parser));
    { Vec *_ca = Vec_clone(&self->tokens); _t2968->tokens = *_ca; free(_ca); }
    _t2968->pos = _t2967;
    { Str *_ca = Str_clone(&self->path); _t2968->path = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->fn_sig_decls); _t2968->fn_sig_decls = *_ca; free(_ca); }
    (void)_t2968;
    ;
    return _t2968;
}

void Parser_delete(Parser * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t2969 = 0;
    (void)_t2969;
    Vec_delete(&self->tokens, &(Bool){_t2969});
    ;
    Bool _t2970 = 0;
    (void)_t2970;
    U64_delete(&self->pos, &(Bool){_t2970});
    ;
    Bool _t2971 = 0;
    (void)_t2971;
    Str_delete(&self->path, &(Bool){_t2971});
    ;
    Bool _t2972 = 0;
    (void)_t2972;
    Vec_delete(&self->fn_sig_decls, &(Bool){_t2972});
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
    I64 _t2974 = U64_to_i64(p->pos);
    (void)_t2974;
    U64 *_t2975 = malloc(sizeof(U64)); *_t2975 = I64_to_u64(_t2974);
    (void)_t2975;
    ;
    Token *t = Vec_get(&p->tokens, _t2975);
    (void)t;
    U64_delete(_t2975, &(Bool){1});
    return t;
}

Token * advance(Parser * p) {
    (void)p;
    I64 _t2978 = U64_to_i64(p->pos);
    (void)_t2978;
    U64 *_t2979 = malloc(sizeof(U64)); *_t2979 = I64_to_u64(_t2978);
    (void)_t2979;
    ;
    Token *t = Vec_get(&p->tokens, _t2979);
    (void)t;
    Bool _t2980; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Eof()); _t2980 = *_hp; free(_hp); }
    (void)_t2980;
    Bool _t2981 = Bool_not(_t2980);
    (void)_t2981;
    ;
    if (_t2981) {
        U64 _t2976 = 1;
        (void)_t2976;
        U64 _t2977 = U64_add(p->pos, _t2976);
        (void)_t2977;
        ;
        p->pos = _t2977;
        ;
    }
    ;
    U64_delete(_t2979, &(Bool){1});
    return t;
}

Bool check(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Bool _t2982; { Bool *_hp = (Bool *)TokenType_eq(&peek(p)->type, type); _t2982 = *_hp; free(_hp); }
    (void)_t2982;
    return _t2982;
}

Token * expect_token(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Token *t = peek(p);
    (void)t;
    Bool _t3007; { Bool *_hp = (Bool *)TokenType_eq(&t->type, type); _t3007 = *_hp; free(_hp); }
    (void)_t3007;
    Bool _t3008 = Bool_not(_t3007);
    (void)_t3008;
    ;
    if (_t3008) {
        Str *_t2983 = Str_lit("Str", 3ULL);
        (void)_t2983;
        U64 _t2984; { U64 *_hp = (U64 *)Str_size(); _t2984 = *_hp; free(_hp); }
        (void)_t2984;
        U64 _t2985 = 10;
        (void)_t2985;
        Array *_va57 = Array_new(_t2983, &(U64){_t2984}, &(U64){_t2985});
        (void)_va57;
        Str_delete(_t2983, &(Bool){1});
        ;
        ;
        U64 _t2986 = 0;
        (void)_t2986;
        Str *_t2987 = Str_clone(&p->path);
        (void)_t2987;
        Array_set(_va57, &(U64){_t2986}, _t2987);
        ;
        U64 _t2988 = 1;
        (void)_t2988;
        Str *_t2989 = Str_lit(":", 1ULL);
        (void)_t2989;
        Array_set(_va57, &(U64){_t2988}, _t2989);
        ;
        U64 _t2990 = 2;
        (void)_t2990;
        Str *_t2991 = U32_to_str(&t->line);
        (void)_t2991;
        Array_set(_va57, &(U64){_t2990}, _t2991);
        ;
        U64 _t2992 = 3;
        (void)_t2992;
        Str *_t2993 = Str_lit(":", 1ULL);
        (void)_t2993;
        Array_set(_va57, &(U64){_t2992}, _t2993);
        ;
        U64 _t2994 = 4;
        (void)_t2994;
        Str *_t2995 = U32_to_str(&t->col);
        (void)_t2995;
        Array_set(_va57, &(U64){_t2994}, _t2995);
        ;
        U64 _t2996 = 5;
        (void)_t2996;
        Str *_t2997 = Str_lit(": expected '", 12ULL);
        (void)_t2997;
        Array_set(_va57, &(U64){_t2996}, _t2997);
        ;
        U64 _t2998 = 6;
        (void)_t2998;
        Str *_t2999 = tok_name(type);
        (void)_t2999;
        Array_set(_va57, &(U64){_t2998}, _t2999);
        ;
        U64 _t3000 = 7;
        (void)_t3000;
        Str *_t3001 = Str_lit("', found '", 10ULL);
        (void)_t3001;
        Array_set(_va57, &(U64){_t3000}, _t3001);
        ;
        U64 _t3002 = 8;
        (void)_t3002;
        Str *_t3003 = Str_clone(&t->text);
        (void)_t3003;
        Array_set(_va57, &(U64){_t3002}, _t3003);
        ;
        U64 _t3004 = 9;
        (void)_t3004;
        Str *_t3005 = Str_lit("'", 1ULL);
        (void)_t3005;
        Array_set(_va57, &(U64){_t3004}, _t3005);
        ;
        Str *_t3006 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:34:15", 63ULL);
        (void)_t3006;
        panic(_t3006, _va57);
        Str_delete(_t3006, &(Bool){1});
    }
    ;
    Token *_t3009 = advance(p);
    (void)_t3009;
    return _t3009;
}

Str * expect_text(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Token *t = peek(p);
    (void)t;
    Bool _t3034; { Bool *_hp = (Bool *)TokenType_eq(&t->type, type); _t3034 = *_hp; free(_hp); }
    (void)_t3034;
    Bool _t3035 = Bool_not(_t3034);
    (void)_t3035;
    ;
    if (_t3035) {
        Str *_t3010 = Str_lit("Str", 3ULL);
        (void)_t3010;
        U64 _t3011; { U64 *_hp = (U64 *)Str_size(); _t3011 = *_hp; free(_hp); }
        (void)_t3011;
        U64 _t3012 = 10;
        (void)_t3012;
        Array *_va58 = Array_new(_t3010, &(U64){_t3011}, &(U64){_t3012});
        (void)_va58;
        Str_delete(_t3010, &(Bool){1});
        ;
        ;
        U64 _t3013 = 0;
        (void)_t3013;
        Str *_t3014 = Str_clone(&p->path);
        (void)_t3014;
        Array_set(_va58, &(U64){_t3013}, _t3014);
        ;
        U64 _t3015 = 1;
        (void)_t3015;
        Str *_t3016 = Str_lit(":", 1ULL);
        (void)_t3016;
        Array_set(_va58, &(U64){_t3015}, _t3016);
        ;
        U64 _t3017 = 2;
        (void)_t3017;
        Str *_t3018 = U32_to_str(&t->line);
        (void)_t3018;
        Array_set(_va58, &(U64){_t3017}, _t3018);
        ;
        U64 _t3019 = 3;
        (void)_t3019;
        Str *_t3020 = Str_lit(":", 1ULL);
        (void)_t3020;
        Array_set(_va58, &(U64){_t3019}, _t3020);
        ;
        U64 _t3021 = 4;
        (void)_t3021;
        Str *_t3022 = U32_to_str(&t->col);
        (void)_t3022;
        Array_set(_va58, &(U64){_t3021}, _t3022);
        ;
        U64 _t3023 = 5;
        (void)_t3023;
        Str *_t3024 = Str_lit(": expected '", 12ULL);
        (void)_t3024;
        Array_set(_va58, &(U64){_t3023}, _t3024);
        ;
        U64 _t3025 = 6;
        (void)_t3025;
        Str *_t3026 = tok_name(type);
        (void)_t3026;
        Array_set(_va58, &(U64){_t3025}, _t3026);
        ;
        U64 _t3027 = 7;
        (void)_t3027;
        Str *_t3028 = Str_lit("', found '", 10ULL);
        (void)_t3028;
        Array_set(_va58, &(U64){_t3027}, _t3028);
        ;
        U64 _t3029 = 8;
        (void)_t3029;
        Str *_t3030 = Str_clone(&t->text);
        (void)_t3030;
        Array_set(_va58, &(U64){_t3029}, _t3030);
        ;
        U64 _t3031 = 9;
        (void)_t3031;
        Str *_t3032 = Str_lit("'", 1ULL);
        (void)_t3032;
        Array_set(_va58, &(U64){_t3031}, _t3032);
        ;
        Str *_t3033 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:44:15", 63ULL);
        (void)_t3033;
        panic(_t3033, _va58);
        Str_delete(_t3033, &(Bool){1});
    }
    ;
    Str *text = Str_clone(&t->text);
    (void)text;
    Token *_t3036 = advance(p);
    (void)_t3036;
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
    Bool _t3070 = check(p, TokenType_LParen());
    (void)_t3070;
    Bool _t3071 = Bool_not(_t3070);
    (void)_t3071;
    ;
    if (_t3071) {
        Str *_t3037 = Str_lit("", 0ULL);
        (void)_t3037;
        ;
        return _t3037;
    }
    ;
    Token *_t3072 = advance(p);
    (void)_t3072;
    Str *_t3073 = Str_lit("Str", 3ULL);
    (void)_t3073;
    U64 _t3074; { U64 *_hp = (U64 *)Str_size(); _t3074 = *_hp; free(_hp); }
    (void)_t3074;
    Vec *ptypes = Vec_new(_t3073, &(U64){_t3074});
    (void)ptypes;
    Str_delete(_t3073, &(Bool){1});
    ;
    Str *_t3075 = Str_lit("Bool", 4ULL);
    (void)_t3075;
    U64 _t3076; { U64 *_hp = (U64 *)Bool_size(); _t3076 = *_hp; free(_hp); }
    (void)_t3076;
    Vec *pmuts = Vec_new(_t3075, &(U64){_t3076});
    (void)pmuts;
    Str_delete(_t3075, &(Bool){1});
    ;
    while (1) {
        Bool _t3042 = check(p, TokenType_RParen());
        (void)_t3042;
        Bool _t3043 = check(p, TokenType_Eof());
        (void)_t3043;
        Bool _t3044 = Bool_not(_t3042);
        (void)_t3044;
        ;
        Bool _t3045 = Bool_not(_t3043);
        (void)_t3045;
        ;
        Bool _wcond3038 = Bool_and(_t3044, _t3045);
        (void)_wcond3038;
        ;
        ;
        if (_wcond3038) {
        } else {
            ;
            break;
        }
        ;
        Bool is_mut = 0;
        (void)is_mut;
        Bool _t3046 = check(p, TokenType_KwMut());
        (void)_t3046;
        if (_t3046) {
            Token *_t3039 = advance(p);
            (void)_t3039;
            Bool _t3040 = 1;
            (void)_t3040;
            is_mut = _t3040;
            ;
        }
        ;
        Str *ptype = expect_text(p, TokenType_Ident());
        (void)ptype;
        Vec_push(ptypes, ptype);
        Vec_push(pmuts, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = is_mut; _oa; }));
        Bool _t3047 = check(p, TokenType_Comma());
        (void)_t3047;
        if (_t3047) {
            Token *_t3041 = advance(p);
            (void)_t3041;
        }
        ;
    }
    Token *_t3077 = expect_token(p, TokenType_RParen());
    (void)_t3077;
    Str *return_type = Str_lit("", 0ULL);
    (void)return_type;
    Bool _t3078 = check(p, TokenType_KwReturns());
    (void)_t3078;
    if (_t3078) {
        Token *_t3048 = advance(p);
        (void)_t3048;
        return_type = expect_text(p, TokenType_Ident());
    }
    ;
    Str *name = Str_lit("_Fn", 3ULL);
    (void)name;
    {
        U64 _t3056 = 0;
        (void)_t3056;
        U64 _t3057; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3057 = *_hp; free(_hp); }
        (void)_t3057;
        Range *_fc3049 = Range_new(_t3056, _t3057);
        (void)_fc3049;
        ;
        ;
        U64 _fi3049 = 0;
        (void)_fi3049;
        while (1) {
            U64 _t3052; { U64 *_hp = (U64 *)Range_len(_fc3049); _t3052 = *_hp; free(_hp); }
            (void)_t3052;
            Bool _wcond3050; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3049}, &(U64){_t3052}); _wcond3050 = *_hp; free(_hp); }
            (void)_wcond3050;
            ;
            if (_wcond3050) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc3049, _fi3049);
            (void)i;
            U64 _t3053 = 1;
            (void)_t3053;
            U64 _t3054 = U64_add(_fi3049, _t3053);
            (void)_t3054;
            ;
            _fi3049 = _t3054;
            ;
            Str *_t3055 = Str_lit("_", 1ULL);
            (void)_t3055;
            name = Str_concat(name, _t3055);
            Str_delete(_t3055, &(Bool){1});
            Bool *m = Vec_get(pmuts, i);
            (void)m;
            if (DEREF(m)) {
                Str *_t3051 = Str_lit("mut_", 4ULL);
                (void)_t3051;
                name = Str_concat(name, _t3051);
                Str_delete(_t3051, &(Bool){1});
            }
            Str *t = Vec_get(ptypes, i);
            (void)t;
            name = Str_concat(name, t);
            U64_delete(i, &(Bool){1});
        }
        Range_delete(_fc3049, &(Bool){1});
        ;
    }
    U64 _t3079; { U64 *_hp = (U64 *)Str_len(return_type); _t3079 = *_hp; free(_hp); }
    (void)_t3079;
    U64 _t3080 = 0;
    (void)_t3080;
    Bool _t3081; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3079}, &(U64){_t3080}); _t3081 = *_hp; free(_hp); }
    (void)_t3081;
    ;
    ;
    if (_t3081) {
        Str *_t3058 = Str_lit("_ret_", 5ULL);
        (void)_t3058;
        name = Str_concat(name, _t3058);
        Str_delete(_t3058, &(Bool){1});
        name = Str_concat(name, return_type);
    }
    ;
    Str *_t3082 = Str_lit("Param", 5ULL);
    (void)_t3082;
    U64 _t3083; { U64 *_hp = (U64 *)Param_size(); _t3083 = *_hp; free(_hp); }
    (void)_t3083;
    Str *_t3084 = Str_lit("Str", 3ULL);
    (void)_t3084;
    U64 _t3085; { U64 *_hp = (U64 *)Str_size(); _t3085 = *_hp; free(_hp); }
    (void)_t3085;
    Str *_t3086 = Str_lit("Expr", 4ULL);
    (void)_t3086;
    U64 _t3087; { U64 *_hp = (U64 *)Expr_size(); _t3087 = *_hp; free(_hp); }
    (void)_t3087;
    I64 _t3088 = 0;
    (void)_t3088;
    I64 _t3089 = 1;
    (void)_t3089;
    I64 _t3090 = I64_sub(_t3088, _t3089);
    (void)_t3090;
    ;
    ;
    I64 _t3091 = 0;
    (void)_t3091;
    I64 _t3092 = 1;
    (void)_t3092;
    I64 _t3093 = I64_sub(_t3091, _t3092);
    (void)_t3093;
    ;
    ;
    U32 _t3094 = 0;
    (void)_t3094;
    I32 _t3095 = I64_to_i32(_t3090);
    (void)_t3095;
    ;
    I32 _t3096 = I64_to_i32(_t3093);
    (void)_t3096;
    ;
    Bool _t3097 = 0;
    (void)_t3097;
    Bool _t3098 = 0;
    (void)_t3098;
    FunctionDef *fd = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(FuncType_Func()); fd->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3082, &(U64){_t3083}); fd->params = *_ca; free(_ca); }
    fd->nparam = _t3094;
    { Map *_ca = Map_new(_t3084, &(U64){_t3085}, _t3086, &(U64){_t3087}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3095;
    fd->kwargs_index = _t3096;
    fd->return_is_ref = _t3097;
    fd->return_is_shallow = _t3098;
    (void)fd;
    Str_delete(_t3082, &(Bool){1});
    ;
    Str_delete(_t3084, &(Bool){1});
    ;
    Str_delete(_t3086, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    U64 _t3099; { U64 *_hp = (U64 *)Str_len(return_type); _t3099 = *_hp; free(_hp); }
    (void)_t3099;
    U64 _t3100 = 0;
    (void)_t3100;
    Bool _t3101; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3099}, &(U64){_t3100}); _t3101 = *_hp; free(_hp); }
    (void)_t3101;
    ;
    ;
    if (_t3101) {
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
    Bool _t3102 = 0;
    (void)_t3102;
    fd->return_is_ref = _t3102;
    ;
    Bool _t3103 = 0;
    (void)_t3103;
    fd->return_is_shallow = _t3103;
    ;
    I64 _t3104 = 0;
    (void)_t3104;
    I64 _t3105 = 1;
    (void)_t3105;
    I64 _t3106 = I64_sub(_t3104, _t3105);
    (void)_t3106;
    ;
    ;
    I32 _t3107 = I64_to_i32(_t3106);
    (void)_t3107;
    ;
    fd->variadic_index = _t3107;
    ;
    I64 _t3108 = 0;
    (void)_t3108;
    I64 _t3109 = 1;
    (void)_t3109;
    I64 _t3110 = I64_sub(_t3108, _t3109);
    (void)_t3110;
    ;
    ;
    I32 _t3111 = I64_to_i32(_t3110);
    (void)_t3111;
    ;
    fd->kwargs_index = _t3111;
    ;
    {
        U64 _t3068 = 0;
        (void)_t3068;
        U64 _t3069; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3069 = *_hp; free(_hp); }
        (void)_t3069;
        Range *_fc3059 = Range_new(_t3068, _t3069);
        (void)_fc3059;
        ;
        ;
        U64 _fi3059 = 0;
        (void)_fi3059;
        while (1) {
            U64 _t3061; { U64 *_hp = (U64 *)Range_len(_fc3059); _t3061 = *_hp; free(_hp); }
            (void)_t3061;
            Bool _wcond3060; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3059}, &(U64){_t3061}); _wcond3060 = *_hp; free(_hp); }
            (void)_wcond3060;
            ;
            if (_wcond3060) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc3059, _fi3059);
            (void)i;
            U64 _t3062 = 1;
            (void)_t3062;
            U64 _t3063 = U64_add(_fi3059, _t3062);
            (void)_t3063;
            ;
            _fi3059 = _t3063;
            ;
            Str *t = Vec_get(ptypes, i);
            (void)t;
            Bool *m = Vec_get(pmuts, i);
            (void)m;
            Bool _t3064 = Bool_clone(m);
            (void)_t3064;
            Bool _t3065 = 0;
            (void)_t3065;
            Bool _t3066 = 0;
            (void)_t3066;
            Param *_t3067 = malloc(sizeof(Param));
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t3067->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(t); _t3067->ptype = *_ca; free(_ca); }
            _t3067->is_mut = _t3064;
            _t3067->is_own = _t3065;
            _t3067->is_shallow = _t3066;
            (void)_t3067;
            ;
            ;
            ;
            U64_delete(i, &(Bool){1});
            Vec_push(&fd->params, _t3067);
        }
        Range_delete(_fc3059, &(Bool){1});
        ;
    }
    Vec_delete(pmuts, &(Bool){1});
    Vec_delete(ptypes, &(Bool){1});
    U64 _t3112; { U64 *_hp = (U64 *)Vec_len(&fd->params); _t3112 = *_hp; free(_hp); }
    (void)_t3112;
    I64 _t3113 = U64_to_i64(_t3112);
    (void)_t3113;
    ;
    U32 _t3114 = I64_to_u32(_t3113);
    (void)_t3114;
    ;
    fd->nparam = _t3114;
    ;
    ExprData *_t3115 = ExprData_FuncDef(fd);
    (void)_t3115;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *sig = Expr_new(_t3115, line, col, &p->path);
    (void)sig;
    ExprData_delete(_t3115, &(Bool){1});
    Bool _t3116 = 0;
    (void)_t3116;
    Bool _t3117 = 0;
    (void)_t3117;
    Bool _t3118 = 0;
    (void)_t3118;
    Bool _t3119 = 0;
    (void)_t3119;
    I32 _t3120 = 0;
    (void)_t3120;
    I32 _t3121 = 0;
    (void)_t3121;
    Declaration *_t3122 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(name); _t3122->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t3122->explicit_type = *_ca; free(_ca); }
    _t3122->is_mut = _t3116;
    _t3122->is_namespace = _t3117;
    _t3122->is_ref = _t3118;
    _t3122->is_own = _t3119;
    _t3122->field_offset = _t3120;
    _t3122->field_size = _t3121;
    _t3122->field_struct_def = NULL;
    _t3122->fn_sig = NULL;
    (void)_t3122;
    ;
    ;
    ;
    ;
    ;
    ;
    ExprData *_t3123 = ExprData_Decl(_t3122);
    (void)_t3123;
    Declaration_delete(_t3122, &(Bool){1});
    Expr *decl = Expr_new(_t3123, line, col, &p->path);
    (void)decl;
    ExprData_delete(_t3123, &(Bool){1});
    Expr_add_child(decl, sig);
    Vec_push(&p->fn_sig_decls, decl);
    return name;
}

Expr * parse_block(Parser * p) {
    (void)p;
    U32 _t3130 = peek_line(p);
    (void)_t3130;
    U32 _t3131 = peek_col(p);
    (void)_t3131;
    Expr *body = Expr_new(ExprData_Body(), _t3130, _t3131, &p->path);
    (void)body;
    ;
    ;
    while (1) {
        Bool _t3125 = check(p, TokenType_RBrace());
        (void)_t3125;
        Bool _t3126 = check(p, TokenType_Eof());
        (void)_t3126;
        Bool _t3127 = Bool_not(_t3125);
        (void)_t3127;
        ;
        Bool _t3128 = Bool_not(_t3126);
        (void)_t3128;
        ;
        Bool _wcond3124 = Bool_and(_t3127, _t3128);
        (void)_wcond3124;
        ;
        ;
        if (_wcond3124) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t3129 = parse_statement(p);
        (void)_t3129;
        Expr_add_child(body, _t3129);
    }
    Token *_t3132 = expect_token(p, TokenType_RBrace());
    (void)_t3132;
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
        TokenType *_sw3133 = TokenType_clone(&kw->type);
        (void)_sw3133;
        Bool _t3145; { Bool *_hp = (Bool *)TokenType_eq(_sw3133, TokenType_KwFunc()); _t3145 = *_hp; free(_hp); }
        (void)_t3145;
        if (_t3145) {
            ft = FuncType_clone(FuncType_Func());
        } else {
            Bool _t3144; { Bool *_hp = (Bool *)TokenType_eq(_sw3133, TokenType_KwProc()); _t3144 = *_hp; free(_hp); }
            (void)_t3144;
            if (_t3144) {
                ft = FuncType_clone(FuncType_Proc());
            } else {
                Bool _t3143; { Bool *_hp = (Bool *)TokenType_eq(_sw3133, TokenType_KwTest()); _t3143 = *_hp; free(_hp); }
                (void)_t3143;
                if (_t3143) {
                    ft = FuncType_clone(FuncType_Test());
                } else {
                    Bool _t3142; { Bool *_hp = (Bool *)TokenType_eq(_sw3133, TokenType_KwMacro()); _t3142 = *_hp; free(_hp); }
                    (void)_t3142;
                    if (_t3142) {
                        ft = FuncType_clone(FuncType_Macro());
                    } else {
                        Bool _t3141; { Bool *_hp = (Bool *)TokenType_eq(_sw3133, TokenType_KwExtFunc()); _t3141 = *_hp; free(_hp); }
                        (void)_t3141;
                        if (_t3141) {
                            ft = FuncType_clone(FuncType_ExtFunc());
                        } else {
                            Bool _t3140; { Bool *_hp = (Bool *)TokenType_eq(_sw3133, TokenType_KwExtProc()); _t3140 = *_hp; free(_hp); }
                            (void)_t3140;
                            if (_t3140) {
                                ft = FuncType_clone(FuncType_ExtProc());
                            } else {
                                Str *_t3134 = Str_lit("Str", 3ULL);
                                (void)_t3134;
                                U64 _t3135; { U64 *_hp = (U64 *)Str_size(); _t3135 = *_hp; free(_hp); }
                                (void)_t3135;
                                U64 _t3136 = 1;
                                (void)_t3136;
                                Array *_va59 = Array_new(_t3134, &(U64){_t3135}, &(U64){_t3136});
                                (void)_va59;
                                Str_delete(_t3134, &(Bool){1});
                                ;
                                ;
                                U64 _t3137 = 0;
                                (void)_t3137;
                                Str *_t3138 = Str_lit("expected function keyword", 25ULL);
                                (void)_t3138;
                                Array_set(_va59, &(U64){_t3137}, _t3138);
                                ;
                                Str *_t3139 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:150:17", 64ULL);
                                (void)_t3139;
                                panic(_t3139, _va59);
                                Str_delete(_t3139, &(Bool){1});
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
        TokenType_delete(_sw3133, &(Bool){1});
        ;
    }
    Token *_t3323 = expect_token(p, TokenType_LParen());
    (void)_t3323;
    Str *_t3324 = Str_lit("Param", 5ULL);
    (void)_t3324;
    U64 _t3325; { U64 *_hp = (U64 *)Param_size(); _t3325 = *_hp; free(_hp); }
    (void)_t3325;
    Str *_t3326 = Str_lit("Str", 3ULL);
    (void)_t3326;
    U64 _t3327; { U64 *_hp = (U64 *)Str_size(); _t3327 = *_hp; free(_hp); }
    (void)_t3327;
    Str *_t3328 = Str_lit("Expr", 4ULL);
    (void)_t3328;
    U64 _t3329; { U64 *_hp = (U64 *)Expr_size(); _t3329 = *_hp; free(_hp); }
    (void)_t3329;
    I64 _t3330 = 0;
    (void)_t3330;
    I64 _t3331 = 1;
    (void)_t3331;
    I64 _t3332 = I64_sub(_t3330, _t3331);
    (void)_t3332;
    ;
    ;
    I64 _t3333 = 0;
    (void)_t3333;
    I64 _t3334 = 1;
    (void)_t3334;
    I64 _t3335 = I64_sub(_t3333, _t3334);
    (void)_t3335;
    ;
    ;
    U32 _t3336 = 0;
    (void)_t3336;
    I32 _t3337 = I64_to_i32(_t3332);
    (void)_t3337;
    ;
    I32 _t3338 = I64_to_i32(_t3335);
    (void)_t3338;
    ;
    Bool _t3339 = 0;
    (void)_t3339;
    Bool _t3340 = 0;
    (void)_t3340;
    FunctionDef *fd = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(FuncType_Func()); fd->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3324, &(U64){_t3325}); fd->params = *_ca; free(_ca); }
    fd->nparam = _t3336;
    { Map *_ca = Map_new(_t3326, &(U64){_t3327}, _t3328, &(U64){_t3329}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3337;
    fd->kwargs_index = _t3338;
    fd->return_is_ref = _t3339;
    fd->return_is_shallow = _t3340;
    (void)fd;
    Str_delete(_t3324, &(Bool){1});
    ;
    Str_delete(_t3326, &(Bool){1});
    ;
    Str_delete(_t3328, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    FuncType_delete(&fd->func_type, &(Bool){0});
    { FuncType *_fa = FuncType_clone(ft); fd->func_type = *_fa; free(_fa); }
    while (1) {
        Bool _t3263 = check(p, TokenType_RParen());
        (void)_t3263;
        Bool _t3264 = check(p, TokenType_Eof());
        (void)_t3264;
        Bool _t3265 = Bool_not(_t3263);
        (void)_t3265;
        ;
        Bool _t3266 = Bool_not(_t3264);
        (void)_t3266;
        ;
        Bool _wcond3146 = Bool_and(_t3265, _t3266);
        (void)_wcond3146;
        ;
        ;
        if (_wcond3146) {
        } else {
            ;
            break;
        }
        ;
        Bool is_shallow = 0;
        (void)is_shallow;
        Bool _t3267 = check(p, TokenType_KwShallow());
        (void)_t3267;
        if (_t3267) {
            Token *_t3147 = advance(p);
            (void)_t3147;
            Bool _t3148 = 1;
            (void)_t3148;
            is_shallow = _t3148;
            ;
        }
        ;
        Bool is_own = 0;
        (void)is_own;
        Bool _t3268 = check(p, TokenType_KwOwn());
        (void)_t3268;
        if (_t3268) {
            Token *_t3149 = advance(p);
            (void)_t3149;
            Bool _t3150 = 1;
            (void)_t3150;
            is_own = _t3150;
            ;
        }
        ;
        Bool is_mut = 0;
        (void)is_mut;
        Bool _t3269 = check(p, TokenType_KwMut());
        (void)_t3269;
        if (_t3269) {
            Token *_t3151 = advance(p);
            (void)_t3151;
            Bool _t3152 = 1;
            (void)_t3152;
            is_mut = _t3152;
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
        Bool _t3270 = check(p, TokenType_Colon());
        (void)_t3270;
        Bool _t3271 = Bool_not(_t3270);
        (void)_t3271;
        ;
        if (_t3271) {
            tp = Str_clone(pname);
            nm = Str_lit("", 0ULL);
        } else {
            Token *_t3246 = expect_token(p, TokenType_Colon());
            (void)_t3246;
            Bool _t3247 = check(p, TokenType_DotDotDot());
            (void)_t3247;
            if (_t3247) {
                Token *_t3183 = advance(p);
                (void)_t3183;
                Bool _t3184 = Bool_or(is_own, is_mut);
                (void)_t3184;
                Bool _t3185 = Bool_or(_t3184, is_shallow);
                (void)_t3185;
                ;
                if (_t3185) {
                    Str *_t3153 = Str_lit("Str", 3ULL);
                    (void)_t3153;
                    U64 _t3154; { U64 *_hp = (U64 *)Str_size(); _t3154 = *_hp; free(_hp); }
                    (void)_t3154;
                    U64 _t3155 = 6;
                    (void)_t3155;
                    Array *_va60 = Array_new(_t3153, &(U64){_t3154}, &(U64){_t3155});
                    (void)_va60;
                    Str_delete(_t3153, &(Bool){1});
                    ;
                    ;
                    U64 _t3156 = 0;
                    (void)_t3156;
                    Str *_t3157 = Str_clone(&p->path);
                    (void)_t3157;
                    Array_set(_va60, &(U64){_t3156}, _t3157);
                    ;
                    U64 _t3158 = 1;
                    (void)_t3158;
                    Str *_t3159 = Str_lit(":", 1ULL);
                    (void)_t3159;
                    Array_set(_va60, &(U64){_t3158}, _t3159);
                    ;
                    U32 _t3160 = peek_line(p);
                    (void)_t3160;
                    U64 _t3161 = 2;
                    (void)_t3161;
                    Str *_t3162 = U32_to_str(&(U32){_t3160});
                    (void)_t3162;
                    ;
                    Array_set(_va60, &(U64){_t3161}, _t3162);
                    ;
                    U64 _t3163 = 3;
                    (void)_t3163;
                    Str *_t3164 = Str_lit(":", 1ULL);
                    (void)_t3164;
                    Array_set(_va60, &(U64){_t3163}, _t3164);
                    ;
                    U32 _t3165 = peek_col(p);
                    (void)_t3165;
                    U64 _t3166 = 4;
                    (void)_t3166;
                    Str *_t3167 = U32_to_str(&(U32){_t3165});
                    (void)_t3167;
                    ;
                    Array_set(_va60, &(U64){_t3166}, _t3167);
                    ;
                    U64 _t3168 = 5;
                    (void)_t3168;
                    Str *_t3169 = Str_lit(": kwargs parameter cannot be own/mut/shallow", 44ULL);
                    (void)_t3169;
                    Array_set(_va60, &(U64){_t3168}, _t3169);
                    ;
                    Str *_t3170 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:180:27", 64ULL);
                    (void)_t3170;
                    panic(_t3170, _va60);
                    Str_delete(_t3170, &(Bool){1});
                }
                ;
                I64 _t3186 = 0;
                (void)_t3186;
                I64 _t3187 = 1;
                (void)_t3187;
                I64 _t3188 = I64_sub(_t3186, _t3187);
                (void)_t3188;
                ;
                ;
                I32 _t3189 = I64_to_i32(_t3188);
                (void)_t3189;
                ;
                Bool _t3190; { Bool *_hp = (Bool *)I32_neq(&fd->kwargs_index, &(I32){_t3189}); _t3190 = *_hp; free(_hp); }
                (void)_t3190;
                ;
                if (_t3190) {
                    Str *_t3171 = Str_lit("Str", 3ULL);
                    (void)_t3171;
                    U64 _t3172; { U64 *_hp = (U64 *)Str_size(); _t3172 = *_hp; free(_hp); }
                    (void)_t3172;
                    U64 _t3173 = 1;
                    (void)_t3173;
                    Array *_va61 = Array_new(_t3171, &(U64){_t3172}, &(U64){_t3173});
                    (void)_va61;
                    Str_delete(_t3171, &(Bool){1});
                    ;
                    ;
                    U64 _t3174 = 0;
                    (void)_t3174;
                    Str *_t3175 = Str_lit("only one kwargs parameter is allowed", 36ULL);
                    (void)_t3175;
                    Array_set(_va61, &(U64){_t3174}, _t3175);
                    ;
                    Str *_t3176 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:184:27", 64ULL);
                    (void)_t3176;
                    panic(_t3176, _va61);
                    Str_delete(_t3176, &(Bool){1});
                }
                ;
                I64 _t3191 = 0;
                (void)_t3191;
                I64 _t3192 = 1;
                (void)_t3192;
                I64 _t3193 = I64_sub(_t3191, _t3192);
                (void)_t3193;
                ;
                ;
                I32 _t3194 = I64_to_i32(_t3193);
                (void)_t3194;
                ;
                Bool _t3195; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3194}); _t3195 = *_hp; free(_hp); }
                (void)_t3195;
                ;
                if (_t3195) {
                    Str *_t3177 = Str_lit("Str", 3ULL);
                    (void)_t3177;
                    U64 _t3178; { U64 *_hp = (U64 *)Str_size(); _t3178 = *_hp; free(_hp); }
                    (void)_t3178;
                    U64 _t3179 = 1;
                    (void)_t3179;
                    Array *_va62 = Array_new(_t3177, &(U64){_t3178}, &(U64){_t3179});
                    (void)_va62;
                    Str_delete(_t3177, &(Bool){1});
                    ;
                    ;
                    U64 _t3180 = 0;
                    (void)_t3180;
                    Str *_t3181 = Str_lit("cannot combine variadic and kwargs in the same function", 55ULL);
                    (void)_t3181;
                    Array_set(_va62, &(U64){_t3180}, _t3181);
                    ;
                    Str *_t3182 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:187:27", 64ULL);
                    (void)_t3182;
                    panic(_t3182, _va62);
                    Str_delete(_t3182, &(Bool){1});
                }
                ;
                U64 _t3196; { U64 *_hp = (U64 *)Vec_len(&fd->params); _t3196 = *_hp; free(_hp); }
                (void)_t3196;
                I64 _t3197 = U64_to_i64(_t3196);
                (void)_t3197;
                ;
                I32 _t3198 = I64_to_i32(_t3197);
                (void)_t3198;
                ;
                fd->kwargs_index = _t3198;
                ;
                Bool _t3199 = 1;
                (void)_t3199;
                is_own = _t3199;
                ;
                nm = Str_clone(pname);
                tp = Str_lit("Map", 3ULL);
            } else {
                Bool _t3245 = check(p, TokenType_DotDot());
                (void)_t3245;
                if (_t3245) {
                    Token *_t3230 = advance(p);
                    (void)_t3230;
                    if (is_own) {
                        Str *_t3200 = Str_lit("Str", 3ULL);
                        (void)_t3200;
                        U64 _t3201; { U64 *_hp = (U64 *)Str_size(); _t3201 = *_hp; free(_hp); }
                        (void)_t3201;
                        U64 _t3202 = 1;
                        (void)_t3202;
                        Array *_va63 = Array_new(_t3200, &(U64){_t3201}, &(U64){_t3202});
                        (void)_va63;
                        Str_delete(_t3200, &(Bool){1});
                        ;
                        ;
                        U64 _t3203 = 0;
                        (void)_t3203;
                        Str *_t3204 = Str_lit("variadic param cannot be 'own'", 30ULL);
                        (void)_t3204;
                        Array_set(_va63, &(U64){_t3203}, _t3204);
                        ;
                        Str *_t3205 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:195:35", 64ULL);
                        (void)_t3205;
                        panic(_t3205, _va63);
                        Str_delete(_t3205, &(Bool){1});
                    }
                    if (is_mut) {
                        Str *_t3206 = Str_lit("Str", 3ULL);
                        (void)_t3206;
                        U64 _t3207; { U64 *_hp = (U64 *)Str_size(); _t3207 = *_hp; free(_hp); }
                        (void)_t3207;
                        U64 _t3208 = 1;
                        (void)_t3208;
                        Array *_va64 = Array_new(_t3206, &(U64){_t3207}, &(U64){_t3208});
                        (void)_va64;
                        Str_delete(_t3206, &(Bool){1});
                        ;
                        ;
                        U64 _t3209 = 0;
                        (void)_t3209;
                        Str *_t3210 = Str_lit("variadic param cannot be 'mut'", 30ULL);
                        (void)_t3210;
                        Array_set(_va64, &(U64){_t3209}, _t3210);
                        ;
                        Str *_t3211 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:196:35", 64ULL);
                        (void)_t3211;
                        panic(_t3211, _va64);
                        Str_delete(_t3211, &(Bool){1});
                    }
                    if (is_shallow) {
                        Str *_t3212 = Str_lit("Str", 3ULL);
                        (void)_t3212;
                        U64 _t3213; { U64 *_hp = (U64 *)Str_size(); _t3213 = *_hp; free(_hp); }
                        (void)_t3213;
                        U64 _t3214 = 1;
                        (void)_t3214;
                        Array *_va65 = Array_new(_t3212, &(U64){_t3213}, &(U64){_t3214});
                        (void)_va65;
                        Str_delete(_t3212, &(Bool){1});
                        ;
                        ;
                        U64 _t3215 = 0;
                        (void)_t3215;
                        Str *_t3216 = Str_lit("variadic param cannot be 'shallow'", 34ULL);
                        (void)_t3216;
                        Array_set(_va65, &(U64){_t3215}, _t3216);
                        ;
                        Str *_t3217 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:197:39", 64ULL);
                        (void)_t3217;
                        panic(_t3217, _va65);
                        Str_delete(_t3217, &(Bool){1});
                    }
                    I64 _t3231 = 0;
                    (void)_t3231;
                    I64 _t3232 = 1;
                    (void)_t3232;
                    I64 _t3233 = I64_sub(_t3231, _t3232);
                    (void)_t3233;
                    ;
                    ;
                    I32 _t3234 = I64_to_i32(_t3233);
                    (void)_t3234;
                    ;
                    Bool _t3235; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3234}); _t3235 = *_hp; free(_hp); }
                    (void)_t3235;
                    ;
                    if (_t3235) {
                        Str *_t3218 = Str_lit("Str", 3ULL);
                        (void)_t3218;
                        U64 _t3219; { U64 *_hp = (U64 *)Str_size(); _t3219 = *_hp; free(_hp); }
                        (void)_t3219;
                        U64 _t3220 = 1;
                        (void)_t3220;
                        Array *_va66 = Array_new(_t3218, &(U64){_t3219}, &(U64){_t3220});
                        (void)_va66;
                        Str_delete(_t3218, &(Bool){1});
                        ;
                        ;
                        U64 _t3221 = 0;
                        (void)_t3221;
                        Str *_t3222 = Str_lit("only one variadic param allowed", 31ULL);
                        (void)_t3222;
                        Array_set(_va66, &(U64){_t3221}, _t3222);
                        ;
                        Str *_t3223 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:198:63", 64ULL);
                        (void)_t3223;
                        panic(_t3223, _va66);
                        Str_delete(_t3223, &(Bool){1});
                    }
                    ;
                    I64 _t3236 = 0;
                    (void)_t3236;
                    I64 _t3237 = 1;
                    (void)_t3237;
                    I64 _t3238 = I64_sub(_t3236, _t3237);
                    (void)_t3238;
                    ;
                    ;
                    I32 _t3239 = I64_to_i32(_t3238);
                    (void)_t3239;
                    ;
                    Bool _t3240; { Bool *_hp = (Bool *)I32_neq(&fd->kwargs_index, &(I32){_t3239}); _t3240 = *_hp; free(_hp); }
                    (void)_t3240;
                    ;
                    if (_t3240) {
                        Str *_t3224 = Str_lit("Str", 3ULL);
                        (void)_t3224;
                        U64 _t3225; { U64 *_hp = (U64 *)Str_size(); _t3225 = *_hp; free(_hp); }
                        (void)_t3225;
                        U64 _t3226 = 1;
                        (void)_t3226;
                        Array *_va67 = Array_new(_t3224, &(U64){_t3225}, &(U64){_t3226});
                        (void)_va67;
                        Str_delete(_t3224, &(Bool){1});
                        ;
                        ;
                        U64 _t3227 = 0;
                        (void)_t3227;
                        Str *_t3228 = Str_lit("cannot combine variadic and kwargs in the same function", 55ULL);
                        (void)_t3228;
                        Array_set(_va67, &(U64){_t3227}, _t3228);
                        ;
                        Str *_t3229 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:200:27", 64ULL);
                        (void)_t3229;
                        panic(_t3229, _va67);
                        Str_delete(_t3229, &(Bool){1});
                    }
                    ;
                    U64 _t3241; { U64 *_hp = (U64 *)Vec_len(&fd->params); _t3241 = *_hp; free(_hp); }
                    (void)_t3241;
                    I64 _t3242 = U64_to_i64(_t3241);
                    (void)_t3242;
                    ;
                    I32 _t3243 = I64_to_i32(_t3242);
                    (void)_t3243;
                    ;
                    fd->variadic_index = _t3243;
                    ;
                    Bool _t3244 = 1;
                    (void)_t3244;
                    is_variadic = _t3244;
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
        Str *_t3272 = Str_lit("Fn", 2ULL);
        (void)_t3272;
        Bool _t3273; { Bool *_hp = (Bool *)Str_eq(tp, _t3272); _t3273 = *_hp; free(_hp); }
        (void)_t3273;
        Str_delete(_t3272, &(Bool){1});
        if (_t3273) {
            U32 _t3248 = peek_line(p);
            (void)_t3248;
            U32 _t3249 = peek_col(p);
            (void)_t3249;
            Str *syn_name = parse_fn_signature(p, _t3248, _t3249);
            (void)syn_name;
            ;
            ;
            U64 _t3250; { U64 *_hp = (U64 *)Str_len(syn_name); _t3250 = *_hp; free(_hp); }
            (void)_t3250;
            U64 _t3251 = 0;
            (void)_t3251;
            Bool _t3252; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3250}, &(U64){_t3251}); _t3252 = *_hp; free(_hp); }
            (void)_t3252;
            ;
            ;
            if (_t3252) {
                tp = Str_clone(syn_name);
            }
            ;
            Str_delete(syn_name, &(Bool){1});
        }
        ;
        Bool has_default = 0;
        (void)has_default;
        Bool _t3274 = check(p, TokenType_Eq());
        (void)_t3274;
        if (_t3274) {
            Token *_t3253 = advance(p);
            (void)_t3253;
            Expr *def_expr = parse_expression(p);
            (void)def_expr;
            Str *_t3254 = Str_clone(nm);
            (void)_t3254;
            Map_set(&fd->param_defaults, _t3254, def_expr);
            Bool _t3255 = 1;
            (void)_t3255;
            has_default = _t3255;
            ;
        }
        ;
        I64 _t3275 = 0;
        (void)_t3275;
        I64 _t3276 = 1;
        (void)_t3276;
        I64 _t3277 = I64_sub(_t3275, _t3276);
        (void)_t3277;
        ;
        ;
        I32 _t3278 = I64_to_i32(_t3277);
        (void)_t3278;
        ;
        Bool _t3279; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3278}); _t3279 = *_hp; free(_hp); }
        (void)_t3279;
        ;
        Bool _t3280 = Bool_not(is_variadic);
        (void)_t3280;
        ;
        Bool _t3281 = Bool_and(_t3279, _t3280);
        (void)_t3281;
        ;
        ;
        Bool _t3282 = Bool_not(has_default);
        (void)_t3282;
        ;
        Bool _t3283 = Bool_and(_t3281, _t3282);
        (void)_t3283;
        ;
        ;
        if (_t3283) {
            Str *_t3256 = Str_lit("Str", 3ULL);
            (void)_t3256;
            U64 _t3257; { U64 *_hp = (U64 *)Str_size(); _t3257 = *_hp; free(_hp); }
            (void)_t3257;
            U64 _t3258 = 1;
            (void)_t3258;
            Array *_va68 = Array_new(_t3256, &(U64){_t3257}, &(U64){_t3258});
            (void)_va68;
            Str_delete(_t3256, &(Bool){1});
            ;
            ;
            U64 _t3259 = 0;
            (void)_t3259;
            Str *_t3260 = Str_lit("positional param not allowed after variadic", 43ULL);
            (void)_t3260;
            Array_set(_va68, &(U64){_t3259}, _t3260);
            ;
            Str *_t3261 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:227:19", 64ULL);
            (void)_t3261;
            panic(_t3261, _va68);
            Str_delete(_t3261, &(Bool){1});
        }
        ;
        Bool _t3284 = Bool_clone(&(Bool){is_mut});
        (void)_t3284;
        ;
        Bool _t3285 = Bool_clone(&(Bool){is_own});
        (void)_t3285;
        ;
        Bool _t3286 = Bool_clone(&(Bool){is_shallow});
        (void)_t3286;
        ;
        Param *_t3287 = malloc(sizeof(Param));
        { Str *_ca = Str_clone(nm); _t3287->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(tp); _t3287->ptype = *_ca; free(_ca); }
        _t3287->is_mut = _t3284;
        _t3287->is_own = _t3285;
        _t3287->is_shallow = _t3286;
        (void)_t3287;
        ;
        ;
        ;
        Str_delete(nm, &(Bool){1});
        Str_delete(tp, &(Bool){1});
        Vec_push(&fd->params, _t3287);
        Bool _t3288 = check(p, TokenType_Comma());
        (void)_t3288;
        if (_t3288) {
            Token *_t3262 = advance(p);
            (void)_t3262;
        }
        ;
    }
    Token *_t3341 = expect_token(p, TokenType_RParen());
    (void)_t3341;
    Bool _t3342 = check(p, TokenType_KwReturns());
    (void)_t3342;
    if (_t3342) {
        Token *_t3294 = advance(p);
        (void)_t3294;
        Bool _t3295 = check(p, TokenType_KwRef());
        (void)_t3295;
        if (_t3295) {
            Token *_t3289 = advance(p);
            (void)_t3289;
            Bool _t3290 = 1;
            (void)_t3290;
            fd->return_is_ref = _t3290;
            ;
        } else {
            Bool _t3293 = check(p, TokenType_KwShallow());
            (void)_t3293;
            if (_t3293) {
                Token *_t3291 = advance(p);
                (void)_t3291;
                Bool _t3292 = 1;
                (void)_t3292;
                fd->return_is_shallow = _t3292;
                ;
            }
            ;
        }
        ;
        Str_delete(&fd->return_type, &(Bool){0});
        { Str *_fa = expect_text(p, TokenType_Ident()); fd->return_type = *_fa; free(_fa); }
    }
    ;
    U64 _t3343; { U64 *_hp = (U64 *)Vec_len(&fd->params); _t3343 = *_hp; free(_hp); }
    (void)_t3343;
    I64 _t3344 = U64_to_i64(_t3343);
    (void)_t3344;
    ;
    U32 _t3345 = I64_to_u32(_t3344);
    (void)_t3345;
    ;
    fd->nparam = _t3345;
    ;
    ExprData *_t3346 = ExprData_FuncDef(fd);
    (void)_t3346;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *def = Expr_new(_t3346, kw_line, kw_col, &p->path);
    (void)def;
    ExprData_delete(_t3346, &(Bool){1});
    Bool _t3347 = check(p, TokenType_LBrace());
    (void)_t3347;
    if (_t3347) {
        Token *_t3296 = expect_token(p, TokenType_LBrace());
        (void)_t3296;
        Expr *_t3297 = parse_block(p);
        (void)_t3297;
        Expr_add_child(def, _t3297);
    } else {
        Bool _t3318; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Func()); _t3318 = *_hp; free(_hp); }
        (void)_t3318;
        Bool _t3319; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Proc()); _t3319 = *_hp; free(_hp); }
        (void)_t3319;
        Bool _t3320 = Bool_not(_t3318);
        (void)_t3320;
        ;
        Bool _t3321 = Bool_not(_t3319);
        (void)_t3321;
        ;
        Bool _t3322 = Bool_and(_t3320, _t3321);
        (void)_t3322;
        ;
        ;
        if (_t3322) {
            Str *_t3298 = Str_lit("Str", 3ULL);
            (void)_t3298;
            U64 _t3299; { U64 *_hp = (U64 *)Str_size(); _t3299 = *_hp; free(_hp); }
            (void)_t3299;
            U64 _t3300 = 8;
            (void)_t3300;
            Array *_va69 = Array_new(_t3298, &(U64){_t3299}, &(U64){_t3300});
            (void)_va69;
            Str_delete(_t3298, &(Bool){1});
            ;
            ;
            U64 _t3301 = 0;
            (void)_t3301;
            Str *_t3302 = Str_clone(&p->path);
            (void)_t3302;
            Array_set(_va69, &(U64){_t3301}, _t3302);
            ;
            U64 _t3303 = 1;
            (void)_t3303;
            Str *_t3304 = Str_lit(":", 1ULL);
            (void)_t3304;
            Array_set(_va69, &(U64){_t3303}, _t3304);
            ;
            U64 _t3305 = 2;
            (void)_t3305;
            Str *_t3306 = U32_to_str(&(U32){kw_line});
            (void)_t3306;
            Array_set(_va69, &(U64){_t3305}, _t3306);
            ;
            U64 _t3307 = 3;
            (void)_t3307;
            Str *_t3308 = Str_lit(":", 1ULL);
            (void)_t3308;
            Array_set(_va69, &(U64){_t3307}, _t3308);
            ;
            U64 _t3309 = 4;
            (void)_t3309;
            Str *_t3310 = U32_to_str(&(U32){kw_col});
            (void)_t3310;
            Array_set(_va69, &(U64){_t3309}, _t3310);
            ;
            U64 _t3311 = 5;
            (void)_t3311;
            Str *_t3312 = Str_lit(": ", 2ULL);
            (void)_t3312;
            Array_set(_va69, &(U64){_t3311}, _t3312);
            ;
            U64 _t3313 = 6;
            (void)_t3313;
            Str *_t3314 = func_type_name(ft);
            (void)_t3314;
            Array_set(_va69, &(U64){_t3313}, _t3314);
            ;
            U64 _t3315 = 7;
            (void)_t3315;
            Str *_t3316 = Str_lit(" requires a body", 16ULL);
            (void)_t3316;
            Array_set(_va69, &(U64){_t3315}, _t3316);
            ;
            Str *_t3317 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:257:19", 64ULL);
            (void)_t3317;
            panic(_t3317, _va69);
            Str_delete(_t3317, &(Bool){1});
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
    Token *_t3361 = advance(p);
    (void)_t3361;
    Expr *def = Expr_new(ExprData_StructDef(), kw_line, kw_col, &p->path);
    (void)def;
    ;
    ;
    Bool _t3362 = Bool_clone(&(Bool){is_ext});
    (void)_t3362;
    ;
    def->is_ext = _t3362;
    ;
    Token *_t3363 = expect_token(p, TokenType_LBrace());
    (void)_t3363;
    U32 _t3364 = peek_line(p);
    (void)_t3364;
    U32 _t3365 = peek_col(p);
    (void)_t3365;
    Expr *body = Expr_new(ExprData_Body(), _t3364, _t3365, &p->path);
    (void)body;
    ;
    ;
    Bool in_namespace = 0;
    (void)in_namespace;
    while (1) {
        Bool _t3354 = check(p, TokenType_RBrace());
        (void)_t3354;
        Bool _t3355 = check(p, TokenType_Eof());
        (void)_t3355;
        Bool _t3356 = Bool_not(_t3354);
        (void)_t3356;
        ;
        Bool _t3357 = Bool_not(_t3355);
        (void)_t3357;
        ;
        Bool _wcond3348 = Bool_and(_t3356, _t3357);
        (void)_wcond3348;
        ;
        ;
        if (_wcond3348) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3358 = check(p, TokenType_KwNamespace());
        (void)_t3358;
        if (_t3358) {
            Token *_t3349 = advance(p);
            (void)_t3349;
            Token *_t3350 = expect_token(p, TokenType_Colon());
            (void)_t3350;
            Bool _t3351 = 1;
            (void)_t3351;
            in_namespace = _t3351;
            ;
            ;
            continue;
        }
        ;
        Expr *stmt = parse_statement(p);
        (void)stmt;
        Bool _t3359; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3359 = *_hp; free(_hp); }
        (void)_t3359;
        Bool _t3360 = Bool_and(in_namespace, _t3359);
        (void)_t3360;
        ;
        if (_t3360) {
            Bool _t3353; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3353 = *_hp; free(_hp); }
            (void)_t3353;
            if (_t3353) {
                Declaration *dd = ExprData_get_Decl(&stmt->data);
                (void)dd;
                Bool _t3352 = 1;
                (void)_t3352;
                dd->is_namespace = _t3352;
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
    Token *_t3366 = expect_token(p, TokenType_RBrace());
    (void)_t3366;
    Expr_add_child(def, body);
    return def;
}

Expr * parse_enum_def(Parser * p) {
    (void)p;
    U32 kw_line = peek_line(p);
    (void)kw_line;
    U32 kw_col = peek_col(p);
    (void)kw_col;
    Token *_t3390 = advance(p);
    (void)_t3390;
    Expr *def = Expr_new(ExprData_EnumDef(), kw_line, kw_col, &p->path);
    (void)def;
    ;
    ;
    Token *_t3391 = expect_token(p, TokenType_LBrace());
    (void)_t3391;
    U32 _t3392 = peek_line(p);
    (void)_t3392;
    U32 _t3393 = peek_col(p);
    (void)_t3393;
    Expr *body = Expr_new(ExprData_Body(), _t3392, _t3393, &p->path);
    (void)body;
    ;
    ;
    Bool in_namespace = 0;
    (void)in_namespace;
    while (1) {
        Bool _t3385 = check(p, TokenType_RBrace());
        (void)_t3385;
        Bool _t3386 = check(p, TokenType_Eof());
        (void)_t3386;
        Bool _t3387 = Bool_not(_t3385);
        (void)_t3387;
        ;
        Bool _t3388 = Bool_not(_t3386);
        (void)_t3388;
        ;
        Bool _wcond3367 = Bool_and(_t3387, _t3388);
        (void)_wcond3367;
        ;
        ;
        if (_wcond3367) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3389 = check(p, TokenType_KwNamespace());
        (void)_t3389;
        if (_t3389) {
            Token *_t3368 = advance(p);
            (void)_t3368;
            Token *_t3369 = expect_token(p, TokenType_Colon());
            (void)_t3369;
            Bool _t3370 = 1;
            (void)_t3370;
            in_namespace = _t3370;
            ;
            ;
            continue;
        }
        ;
        if (in_namespace) {
            Expr *stmt = parse_statement(p);
            (void)stmt;
            Bool _t3373; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3373 = *_hp; free(_hp); }
            (void)_t3373;
            if (_t3373) {
                Bool _t3372; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3372 = *_hp; free(_hp); }
                (void)_t3372;
                if (_t3372) {
                    Declaration *dd = ExprData_get_Decl(&stmt->data);
                    (void)dd;
                    Bool _t3371 = 1;
                    (void)_t3371;
                    dd->is_namespace = _t3371;
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
            Bool _t3376 = 0;
            (void)_t3376;
            Bool _t3377 = 0;
            (void)_t3377;
            Bool _t3378 = 0;
            (void)_t3378;
            Bool _t3379 = 0;
            (void)_t3379;
            I32 _t3380 = 0;
            (void)_t3380;
            I32 _t3381 = 0;
            (void)_t3381;
            Declaration *dd = malloc(sizeof(Declaration));
            { Str *_ca = Str_clone(vname); dd->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
            dd->is_mut = _t3376;
            dd->is_namespace = _t3377;
            dd->is_ref = _t3378;
            dd->is_own = _t3379;
            dd->field_offset = _t3380;
            dd->field_size = _t3381;
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
            Bool _t3382 = check(p, TokenType_Colon());
            (void)_t3382;
            if (_t3382) {
                Token *_t3374 = advance(p);
                (void)_t3374;
                Str_delete(&dd->explicit_type, &(Bool){0});
                { Str *_fa = expect_text(p, TokenType_Ident()); dd->explicit_type = *_fa; free(_fa); }
            }
            ;
            ExprData *_t3383 = ExprData_Decl(dd);
            (void)_t3383;
            Declaration_delete(dd, &(Bool){1});
            Expr *variant = Expr_new(_t3383, v_line, v_col, &p->path);
            (void)variant;
            ExprData_delete(_t3383, &(Bool){1});
            ;
            ;
            Expr_add_child(body, variant);
            Bool _t3384 = check(p, TokenType_Comma());
            (void)_t3384;
            if (_t3384) {
                Token *_t3375 = advance(p);
                (void)_t3375;
            }
            ;
        }
    }
    ;
    Token *_t3394 = expect_token(p, TokenType_RBrace());
    (void)_t3394;
    Expr_add_child(def, body);
    return def;
}

Expr * parse_call(Parser * p, Str * name, U32 call_line, U32 call_col) {
    (void)p;
    (void)name;
    (void)call_line;
    (void)call_col;
    Token *_t3425 = advance(p);
    (void)_t3425;
    Expr *call = Expr_new(ExprData_FCall(), call_line, call_col, &p->path);
    (void)call;
    Str *_t3426 = Str_clone(name);
    (void)_t3426;
    ExprData *_t3427 = ExprData_Ident(_t3426);
    (void)_t3427;
    Str_delete(_t3426, &(Bool){1});
    Expr *callee = Expr_new(_t3427, call_line, call_col, &p->path);
    (void)callee;
    ExprData_delete(_t3427, &(Bool){1});
    Expr_add_child(call, callee);
    while (1) {
        Bool _t3415 = check(p, TokenType_RParen());
        (void)_t3415;
        Bool _t3416 = check(p, TokenType_Eof());
        (void)_t3416;
        Bool _t3417 = Bool_not(_t3415);
        (void)_t3417;
        ;
        Bool _t3418 = Bool_not(_t3416);
        (void)_t3418;
        ;
        Bool _wcond3395 = Bool_and(_t3417, _t3418);
        (void)_wcond3395;
        ;
        ;
        if (_wcond3395) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3419 = check(p, TokenType_Ident());
        (void)_t3419;
        if (_t3419) {
            U64 _t3406 = 1;
            (void)_t3406;
            U64 _t3407 = U64_add(p->pos, _t3406);
            (void)_t3407;
            ;
            U64 _t3408; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3408 = *_hp; free(_hp); }
            (void)_t3408;
            Bool _t3409; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3407}, &(U64){_t3408}); _t3409 = *_hp; free(_hp); }
            (void)_t3409;
            ;
            ;
            if (_t3409) {
                U64 _t3401 = 1;
                (void)_t3401;
                U64 _t3402 = U64_add(p->pos, _t3401);
                (void)_t3402;
                ;
                I64 _t3403 = U64_to_i64(_t3402);
                (void)_t3403;
                ;
                U64 *_t3404 = malloc(sizeof(U64)); *_t3404 = I64_to_u64(_t3403);
                (void)_t3404;
                ;
                Token *next_tok = Vec_get(&p->tokens, _t3404);
                (void)next_tok;
                Bool _t3405; { Bool *_hp = (Bool *)TokenType_eq(&next_tok->type, TokenType_Eq()); _t3405 = *_hp; free(_hp); }
                (void)_t3405;
                U64_delete(_t3404, &(Bool){1});
                if (_t3405) {
                    U32 na_line = peek_line(p);
                    (void)na_line;
                    U32 na_col = peek_col(p);
                    (void)na_col;
                    Str *aname = expect_text(p, TokenType_Ident());
                    (void)aname;
                    Token *_t3397 = advance(p);
                    (void)_t3397;
                    ExprData *_t3398 = ExprData_NamedArg(aname);
                    (void)_t3398;
                    Str_delete(aname, &(Bool){1});
                    Expr *na = Expr_new(_t3398, na_line, na_col, &p->path);
                    (void)na;
                    ExprData_delete(_t3398, &(Bool){1});
                    ;
                    ;
                    Expr *_t3399 = parse_expression(p);
                    (void)_t3399;
                    Expr_add_child(na, _t3399);
                    Expr_add_child(call, na);
                    Bool _t3400 = check(p, TokenType_Comma());
                    (void)_t3400;
                    if (_t3400) {
                        Token *_t3396 = advance(p);
                        (void)_t3396;
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
        Bool _t3420 = check(p, TokenType_DotDot());
        (void)_t3420;
        if (_t3420) {
            Token *_t3410 = advance(p);
            (void)_t3410;
            Bool _t3411 = 1;
            (void)_t3411;
            is_splat = _t3411;
            ;
        }
        ;
        Bool is_own_arg = 0;
        (void)is_own_arg;
        Bool _t3421 = check(p, TokenType_KwOwn());
        (void)_t3421;
        if (_t3421) {
            Token *_t3412 = advance(p);
            (void)_t3412;
            Bool _t3413 = 1;
            (void)_t3413;
            is_own_arg = _t3413;
            ;
        }
        ;
        Expr *arg = parse_expression(p);
        (void)arg;
        Bool _t3422 = Bool_clone(&(Bool){is_own_arg});
        (void)_t3422;
        ;
        arg->is_own_arg = _t3422;
        ;
        Bool _t3423 = Bool_clone(&(Bool){is_splat});
        (void)_t3423;
        ;
        arg->is_splat = _t3423;
        ;
        Expr_add_child(call, arg);
        Bool _t3424 = check(p, TokenType_Comma());
        (void)_t3424;
        if (_t3424) {
            Token *_t3414 = advance(p);
            (void)_t3414;
        }
        ;
    }
    Token *_t3428 = expect_token(p, TokenType_RParen());
    (void)_t3428;
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
    U32 _t3635 = 0;
    (void)_t3635;
    U32 _t3636 = 0;
    (void)_t3636;
    Expr *e = Expr_new(ExprData_Body(), _t3635, _t3636, &p->path);
    (void)e;
    ;
    ;
    Bool e_set = 0;
    (void)e_set;
    Bool _t3637; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t3637 = *_hp; free(_hp); }
    (void)_t3637;
    if (_t3637) {
        Token *_t3429 = advance(p);
        (void)_t3429;
        Str *_t3430 = Str_clone(&t->text);
        (void)_t3430;
        ExprData *_t3431 = ExprData_LiteralStr(_t3430);
        (void)_t3431;
        Str_delete(_t3430, &(Bool){1});
        e = Expr_new(_t3431, t_line, t_col, &p->path);
        ExprData_delete(_t3431, &(Bool){1});
        Bool _t3432 = 1;
        (void)_t3432;
        e_set = _t3432;
        ;
    }
    ;
    Bool _t3638 = Bool_not(e_set);
    (void)_t3638;
    Bool _t3639; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t3639 = *_hp; free(_hp); }
    (void)_t3639;
    Bool _t3640 = Bool_and(_t3638, _t3639);
    (void)_t3640;
    ;
    ;
    if (_t3640) {
        Token *_t3433 = advance(p);
        (void)_t3433;
        Str *_t3434 = Str_clone(&t->text);
        (void)_t3434;
        ExprData *_t3435 = ExprData_LiteralNum(_t3434);
        (void)_t3435;
        Str_delete(_t3434, &(Bool){1});
        e = Expr_new(_t3435, t_line, t_col, &p->path);
        ExprData_delete(_t3435, &(Bool){1});
        Bool _t3436 = 1;
        (void)_t3436;
        e_set = _t3436;
        ;
    }
    ;
    Bool _t3641 = Bool_not(e_set);
    (void)_t3641;
    Bool _t3642; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Minus()); _t3642 = *_hp; free(_hp); }
    (void)_t3642;
    Bool _t3643 = Bool_and(_t3641, _t3642);
    (void)_t3643;
    ;
    ;
    if (_t3643) {
        U64 _t3452 = 1;
        (void)_t3452;
        U64 _t3453 = U64_add(p->pos, _t3452);
        (void)_t3453;
        ;
        U64 _t3454; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3454 = *_hp; free(_hp); }
        (void)_t3454;
        Bool _t3455; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3453}, &(U64){_t3454}); _t3455 = *_hp; free(_hp); }
        (void)_t3455;
        ;
        ;
        if (_t3455) {
            U64 _t3447 = 1;
            (void)_t3447;
            U64 _t3448 = U64_add(p->pos, _t3447);
            (void)_t3448;
            ;
            I64 _t3449 = U64_to_i64(_t3448);
            (void)_t3449;
            ;
            U64 *_t3450 = malloc(sizeof(U64)); *_t3450 = I64_to_u64(_t3449);
            (void)_t3450;
            ;
            Token *next_tok = Vec_get(&p->tokens, _t3450);
            (void)next_tok;
            Bool _t3451; { Bool *_hp = (Bool *)TokenType_eq(&next_tok->type, TokenType_Number()); _t3451 = *_hp; free(_hp); }
            (void)_t3451;
            U64_delete(_t3450, &(Bool){1});
            if (_t3451) {
                Token *_t3437 = advance(p);
                (void)_t3437;
                Token *num_tok = advance(p);
                (void)num_tok;
                Str *_t3438 = Str_lit("0", 1ULL);
                (void)_t3438;
                Str *_t3439 = Str_clone(_t3438);
                (void)_t3439;
                Str_delete(_t3438, &(Bool){1});
                ExprData *_t3440 = ExprData_LiteralNum(_t3439);
                (void)_t3440;
                Str_delete(_t3439, &(Bool){1});
                Expr *zero = Expr_new(_t3440, t_line, t_col, &p->path);
                (void)zero;
                ExprData_delete(_t3440, &(Bool){1});
                Str *_t3441 = Str_lit("sub", 3ULL);
                (void)_t3441;
                Str *_t3442 = Str_clone(_t3441);
                (void)_t3442;
                Str_delete(_t3441, &(Bool){1});
                ExprData *_t3443 = ExprData_FieldAccess(_t3442);
                (void)_t3443;
                Str_delete(_t3442, &(Bool){1});
                Expr *sub_access = Expr_new(_t3443, t_line, t_col, &p->path);
                (void)sub_access;
                ExprData_delete(_t3443, &(Bool){1});
                Expr_add_child(sub_access, zero);
                Expr *sub_call = Expr_new(ExprData_FCall(), t_line, t_col, &p->path);
                (void)sub_call;
                Expr_add_child(sub_call, sub_access);
                Str *_t3444 = Str_clone(&num_tok->text);
                (void)_t3444;
                ExprData *_t3445 = ExprData_LiteralNum(_t3444);
                (void)_t3445;
                Str_delete(_t3444, &(Bool){1});
                Expr *num_arg = Expr_new(_t3445, t_line, t_col, &p->path);
                (void)num_arg;
                ExprData_delete(_t3445, &(Bool){1});
                Expr_add_child(sub_call, num_arg);
                e = Expr_clone(sub_call);
                Expr_delete(sub_call, &(Bool){1});
                Bool _t3446 = 1;
                (void)_t3446;
                e_set = _t3446;
                ;
            }
            ;
        }
        ;
    }
    ;
    Bool _t3644 = Bool_not(e_set);
    (void)_t3644;
    Bool _t3645; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Char()); _t3645 = *_hp; free(_hp); }
    (void)_t3645;
    Bool _t3646 = Bool_and(_t3644, _t3645);
    (void)_t3646;
    ;
    ;
    if (_t3646) {
        Token *_t3485 = advance(p);
        (void)_t3485;
        Str *ch = Str_clone(&t->text);
        (void)ch;
        I64 byte_val = 0;
        (void)byte_val;
        U64 _t3486; { U64 *_hp = (U64 *)Str_len(ch); _t3486 = *_hp; free(_hp); }
        (void)_t3486;
        U64 _t3487 = 0;
        (void)_t3487;
        U64 *_t3488 = malloc(sizeof(U64));
        *_t3488 = 0;
        (void)_t3488;
        U8 *_t3489 = Str_get(ch, _t3488);
        (void)_t3489;
        U8 _t3490 = 92;
        (void)_t3490;
        Bool _t3491; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3486}, &(U64){_t3487}); _t3491 = *_hp; free(_hp); }
        (void)_t3491;
        ;
        ;
        Bool _t3492 = U8_eq(DEREF(_t3489), _t3490);
        (void)_t3492;
        U64_delete(_t3488, &(Bool){1});
        ;
        Bool _t3493 = Bool_and(_t3491, _t3492);
        (void)_t3493;
        ;
        ;
        if (_t3493) {
            U64 _t3476; { U64 *_hp = (U64 *)Str_len(ch); _t3476 = *_hp; free(_hp); }
            (void)_t3476;
            U64 _t3477 = 1;
            (void)_t3477;
            Bool _t3478; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3476}, &(U64){_t3477}); _t3478 = *_hp; free(_hp); }
            (void)_t3478;
            ;
            ;
            if (_t3478) {
                U64 *_t3473 = malloc(sizeof(U64));
                *_t3473 = 1;
                (void)_t3473;
                U8 *c2 = Str_get(ch, _t3473);
                (void)c2;
                U8 _t3474 = 110;
                (void)_t3474;
                Bool _t3475 = U8_eq(DEREF(c2), _t3474);
                (void)_t3475;
                ;
                if (_t3475) {
                    I64 _t3456 = 10;
                    (void)_t3456;
                    byte_val = _t3456;
                    ;
                } else {
                    U8 _t3471 = 116;
                    (void)_t3471;
                    Bool _t3472 = U8_eq(DEREF(c2), _t3471);
                    (void)_t3472;
                    ;
                    if (_t3472) {
                        I64 _t3457 = 9;
                        (void)_t3457;
                        byte_val = _t3457;
                        ;
                    } else {
                        U8 _t3469 = 114;
                        (void)_t3469;
                        Bool _t3470 = U8_eq(DEREF(c2), _t3469);
                        (void)_t3470;
                        ;
                        if (_t3470) {
                            I64 _t3458 = 13;
                            (void)_t3458;
                            byte_val = _t3458;
                            ;
                        } else {
                            U8 _t3467 = 92;
                            (void)_t3467;
                            Bool _t3468 = U8_eq(DEREF(c2), _t3467);
                            (void)_t3468;
                            ;
                            if (_t3468) {
                                I64 _t3459 = 92;
                                (void)_t3459;
                                byte_val = _t3459;
                                ;
                            } else {
                                U8 _t3465 = 39;
                                (void)_t3465;
                                Bool _t3466 = U8_eq(DEREF(c2), _t3465);
                                (void)_t3466;
                                ;
                                if (_t3466) {
                                    I64 _t3460 = 39;
                                    (void)_t3460;
                                    byte_val = _t3460;
                                    ;
                                } else {
                                    U8 _t3463 = 48;
                                    (void)_t3463;
                                    Bool _t3464 = U8_eq(DEREF(c2), _t3463);
                                    (void)_t3464;
                                    ;
                                    if (_t3464) {
                                        I64 _t3461 = 0;
                                        (void)_t3461;
                                        byte_val = _t3461;
                                        ;
                                    } else {
                                        I64 _t3462 = U8_to_i64(DEREF(c2));
                                        (void)_t3462;
                                        byte_val = _t3462;
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
                U64_delete(_t3473, &(Bool){1});
                ;
            }
            ;
        } else {
            U64 _t3482; { U64 *_hp = (U64 *)Str_len(ch); _t3482 = *_hp; free(_hp); }
            (void)_t3482;
            U64 _t3483 = 0;
            (void)_t3483;
            Bool _t3484; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3482}, &(U64){_t3483}); _t3484 = *_hp; free(_hp); }
            (void)_t3484;
            ;
            ;
            if (_t3484) {
                U64 *_t3479 = malloc(sizeof(U64));
                *_t3479 = 0;
                (void)_t3479;
                U8 *_t3480 = Str_get(ch, _t3479);
                (void)_t3480;
                I64 _t3481 = U8_to_i64(DEREF(_t3480));
                (void)_t3481;
                U64_delete(_t3479, &(Bool){1});
                byte_val = _t3481;
                ;
            }
            ;
        }
        ;
        Str_delete(ch, &(Bool){1});
        Str *_t3494 = I64_to_str(&(I64){byte_val});
        (void)_t3494;
        ;
        ExprData *_t3495 = ExprData_LiteralNum(_t3494);
        (void)_t3495;
        Str_delete(_t3494, &(Bool){1});
        e = Expr_new(_t3495, t_line, t_col, &p->path);
        ExprData_delete(_t3495, &(Bool){1});
        TilType_delete(&e->til_type, &(Bool){0});
        { TilType *_fa = TilType_clone(TilType_U8()); e->til_type = *_fa; free(_fa); }
        Bool _t3496 = 1;
        (void)_t3496;
        e_set = _t3496;
        ;
    }
    ;
    Bool _t3647; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t3647 = *_hp; free(_hp); }
    (void)_t3647;
    Bool _t3648; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t3648 = *_hp; free(_hp); }
    (void)_t3648;
    Bool _t3649 = Bool_not(e_set);
    (void)_t3649;
    Bool _t3650 = Bool_or(_t3647, _t3648);
    (void)_t3650;
    ;
    ;
    Bool _t3651 = Bool_and(_t3649, _t3650);
    (void)_t3651;
    ;
    ;
    if (_t3651) {
        Token *_t3497 = advance(p);
        (void)_t3497;
        Str *_t3498 = Str_clone(&t->text);
        (void)_t3498;
        ExprData *_t3499 = ExprData_LiteralBool(_t3498);
        (void)_t3499;
        Str_delete(_t3498, &(Bool){1});
        e = Expr_new(_t3499, t_line, t_col, &p->path);
        ExprData_delete(_t3499, &(Bool){1});
        Bool _t3500 = 1;
        (void)_t3500;
        e_set = _t3500;
        ;
    }
    ;
    Bool _t3652 = Bool_not(e_set);
    (void)_t3652;
    Bool _t3653; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwNull()); _t3653 = *_hp; free(_hp); }
    (void)_t3653;
    Bool _t3654 = Bool_and(_t3652, _t3653);
    (void)_t3654;
    ;
    ;
    if (_t3654) {
        Token *_t3501 = advance(p);
        (void)_t3501;
        e = Expr_new(ExprData_LiteralNull(), t_line, t_col, &p->path);
        Bool _t3502 = 1;
        (void)_t3502;
        e_set = _t3502;
        ;
    }
    ;
    Bool _t3655 = Bool_not(e_set);
    (void)_t3655;
    Bool _t3656; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t3656 = *_hp; free(_hp); }
    (void)_t3656;
    Bool _t3657 = Bool_and(_t3655, _t3656);
    (void)_t3657;
    ;
    ;
    if (_t3657) {
        Token *_t3538 = advance(p);
        (void)_t3538;
        Str *name = Str_clone(&t->text);
        (void)name;
        Str *_t3539 = Str_lit("__LOC__", 7ULL);
        (void)_t3539;
        Bool _t3540; { Bool *_hp = (Bool *)Str_eq(name, _t3539); _t3540 = *_hp; free(_hp); }
        (void)_t3540;
        Str_delete(_t3539, &(Bool){1});
        if (_t3540) {
            Str *_t3503 = Str_lit("Str", 3ULL);
            (void)_t3503;
            U64 _t3504; { U64 *_hp = (U64 *)Str_size(); _t3504 = *_hp; free(_hp); }
            (void)_t3504;
            U64 _t3505 = 5;
            (void)_t3505;
            Array *_va70 = Array_new(_t3503, &(U64){_t3504}, &(U64){_t3505});
            (void)_va70;
            Str_delete(_t3503, &(Bool){1});
            ;
            ;
            U64 _t3506 = 0;
            (void)_t3506;
            Str *_t3507 = Str_clone(&p->path);
            (void)_t3507;
            Array_set(_va70, &(U64){_t3506}, _t3507);
            ;
            U64 _t3508 = 1;
            (void)_t3508;
            Str *_t3509 = Str_lit(":", 1ULL);
            (void)_t3509;
            Array_set(_va70, &(U64){_t3508}, _t3509);
            ;
            U64 _t3510 = 2;
            (void)_t3510;
            Str *_t3511 = U32_to_str(&(U32){t_line});
            (void)_t3511;
            Array_set(_va70, &(U64){_t3510}, _t3511);
            ;
            U64 _t3512 = 3;
            (void)_t3512;
            Str *_t3513 = Str_lit(":", 1ULL);
            (void)_t3513;
            Array_set(_va70, &(U64){_t3512}, _t3513);
            ;
            U64 _t3514 = 4;
            (void)_t3514;
            Str *_t3515 = U32_to_str(&(U32){t_col});
            (void)_t3515;
            Array_set(_va70, &(U64){_t3514}, _t3515);
            ;
            Str *_t3516 = format(_va70);
            (void)_t3516;
            ExprData *_t3517 = ExprData_LiteralStr(_t3516);
            (void)_t3517;
            Str_delete(_t3516, &(Bool){1});
            e = Expr_new(_t3517, t_line, t_col, &p->path);
            ExprData_delete(_t3517, &(Bool){1});
            Bool _t3518 = 1;
            (void)_t3518;
            e_set = _t3518;
            ;
        } else {
            Str *_t3536 = Str_lit("__FILE__", 8ULL);
            (void)_t3536;
            Bool _t3537; { Bool *_hp = (Bool *)Str_eq(name, _t3536); _t3537 = *_hp; free(_hp); }
            (void)_t3537;
            Str_delete(_t3536, &(Bool){1});
            if (_t3537) {
                Str *_t3519 = Str_clone(&p->path);
                (void)_t3519;
                ExprData *_t3520 = ExprData_LiteralStr(_t3519);
                (void)_t3520;
                Str_delete(_t3519, &(Bool){1});
                e = Expr_new(_t3520, t_line, t_col, &p->path);
                ExprData_delete(_t3520, &(Bool){1});
                Bool _t3521 = 1;
                (void)_t3521;
                e_set = _t3521;
                ;
            } else {
                Str *_t3534 = Str_lit("__LINE__", 8ULL);
                (void)_t3534;
                Bool _t3535; { Bool *_hp = (Bool *)Str_eq(name, _t3534); _t3535 = *_hp; free(_hp); }
                (void)_t3535;
                Str_delete(_t3534, &(Bool){1});
                if (_t3535) {
                    Str *_t3522 = U32_to_str(&(U32){t_line});
                    (void)_t3522;
                    ExprData *_t3523 = ExprData_LiteralNum(_t3522);
                    (void)_t3523;
                    Str_delete(_t3522, &(Bool){1});
                    e = Expr_new(_t3523, t_line, t_col, &p->path);
                    ExprData_delete(_t3523, &(Bool){1});
                    Bool _t3524 = 1;
                    (void)_t3524;
                    e_set = _t3524;
                    ;
                } else {
                    Str *_t3532 = Str_lit("__COL__", 7ULL);
                    (void)_t3532;
                    Bool _t3533; { Bool *_hp = (Bool *)Str_eq(name, _t3532); _t3533 = *_hp; free(_hp); }
                    (void)_t3533;
                    Str_delete(_t3532, &(Bool){1});
                    if (_t3533) {
                        Str *_t3525 = U32_to_str(&(U32){t_col});
                        (void)_t3525;
                        ExprData *_t3526 = ExprData_LiteralNum(_t3525);
                        (void)_t3526;
                        Str_delete(_t3525, &(Bool){1});
                        e = Expr_new(_t3526, t_line, t_col, &p->path);
                        ExprData_delete(_t3526, &(Bool){1});
                        Bool _t3527 = 1;
                        (void)_t3527;
                        e_set = _t3527;
                        ;
                    } else {
                        Bool _t3531 = check(p, TokenType_LParen());
                        (void)_t3531;
                        if (_t3531) {
                            e = parse_call(p, name, t_line, t_col);
                            Bool _t3528 = 1;
                            (void)_t3528;
                            e_set = _t3528;
                            ;
                        } else {
                            ExprData *_t3529 = ExprData_Ident(name);
                            (void)_t3529;
                            e = Expr_new(_t3529, t_line, t_col, &p->path);
                            ExprData_delete(_t3529, &(Bool){1});
                            Bool _t3530 = 1;
                            (void)_t3530;
                            e_set = _t3530;
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
    Bool _t3658; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFunc()); _t3658 = *_hp; free(_hp); }
    (void)_t3658;
    Bool _t3659; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwProc()); _t3659 = *_hp; free(_hp); }
    (void)_t3659;
    Bool _t3660 = Bool_or(_t3658, _t3659);
    (void)_t3660;
    ;
    ;
    Bool _t3661; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTest()); _t3661 = *_hp; free(_hp); }
    (void)_t3661;
    Bool _t3662 = Bool_or(_t3660, _t3661);
    (void)_t3662;
    ;
    ;
    Bool _t3663; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMacro()); _t3663 = *_hp; free(_hp); }
    (void)_t3663;
    Bool _t3664 = Bool_or(_t3662, _t3663);
    (void)_t3664;
    ;
    ;
    Bool _t3665; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtFunc()); _t3665 = *_hp; free(_hp); }
    (void)_t3665;
    Bool _t3666 = Bool_or(_t3664, _t3665);
    (void)_t3666;
    ;
    ;
    Bool _t3667; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtProc()); _t3667 = *_hp; free(_hp); }
    (void)_t3667;
    Bool _t3668 = Bool_not(e_set);
    (void)_t3668;
    Bool _t3669 = Bool_or(_t3666, _t3667);
    (void)_t3669;
    ;
    ;
    Bool _t3670 = Bool_and(_t3668, _t3669);
    (void)_t3670;
    ;
    ;
    if (_t3670) {
        Expr *_t3541 = parse_func_def(p);
        (void)_t3541;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3541;
    }
    ;
    Bool _t3671; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwStruct()); _t3671 = *_hp; free(_hp); }
    (void)_t3671;
    Bool _t3672; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtStruct()); _t3672 = *_hp; free(_hp); }
    (void)_t3672;
    Bool _t3673 = Bool_not(e_set);
    (void)_t3673;
    Bool _t3674 = Bool_or(_t3671, _t3672);
    (void)_t3674;
    ;
    ;
    Bool _t3675 = Bool_and(_t3673, _t3674);
    (void)_t3675;
    ;
    ;
    if (_t3675) {
        Expr *_t3542 = parse_struct_def(p);
        (void)_t3542;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3542;
    }
    ;
    Bool _t3676 = Bool_not(e_set);
    (void)_t3676;
    Bool _t3677; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwEnum()); _t3677 = *_hp; free(_hp); }
    (void)_t3677;
    Bool _t3678 = Bool_and(_t3676, _t3677);
    (void)_t3678;
    ;
    ;
    if (_t3678) {
        Expr *_t3543 = parse_enum_def(p);
        (void)_t3543;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3543;
    }
    ;
    Bool _t3679 = Bool_not(e_set);
    (void)_t3679;
    Bool _t3680; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t3680 = *_hp; free(_hp); }
    (void)_t3680;
    Bool _t3681 = Bool_and(_t3679, _t3680);
    (void)_t3681;
    ;
    ;
    if (_t3681) {
        Token *_t3568 = advance(p);
        (void)_t3568;
        Expr *first = parse_expression(p);
        (void)first;
        Bool _t3569 = check(p, TokenType_Colon());
        (void)_t3569;
        if (_t3569) {
            e = Expr_new(ExprData_MapLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Token *_t3555 = advance(p);
            (void)_t3555;
            Expr *_t3556 = parse_expression(p);
            (void)_t3556;
            Expr_add_child(e, _t3556);
            Bool _t3557 = check(p, TokenType_Comma());
            (void)_t3557;
            if (_t3557) {
                Token *_t3544 = advance(p);
                (void)_t3544;
            }
            ;
            while (1) {
                Bool _t3547 = check(p, TokenType_RBrace());
                (void)_t3547;
                Bool _t3548 = check(p, TokenType_Eof());
                (void)_t3548;
                Bool _t3549 = Bool_not(_t3547);
                (void)_t3549;
                ;
                Bool _t3550 = Bool_not(_t3548);
                (void)_t3550;
                ;
                Bool _wcond3545 = Bool_and(_t3549, _t3550);
                (void)_wcond3545;
                ;
                ;
                if (_wcond3545) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3551 = parse_expression(p);
                (void)_t3551;
                Expr_add_child(e, _t3551);
                Token *_t3552 = expect_token(p, TokenType_Colon());
                (void)_t3552;
                Expr *_t3553 = parse_expression(p);
                (void)_t3553;
                Expr_add_child(e, _t3553);
                Bool _t3554 = check(p, TokenType_Comma());
                (void)_t3554;
                if (_t3554) {
                    Token *_t3546 = advance(p);
                    (void)_t3546;
                }
                ;
            }
        } else {
            e = Expr_new(ExprData_SetLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Bool _t3567 = check(p, TokenType_Comma());
            (void)_t3567;
            if (_t3567) {
                Token *_t3558 = advance(p);
                (void)_t3558;
            }
            ;
            while (1) {
                Bool _t3561 = check(p, TokenType_RBrace());
                (void)_t3561;
                Bool _t3562 = check(p, TokenType_Eof());
                (void)_t3562;
                Bool _t3563 = Bool_not(_t3561);
                (void)_t3563;
                ;
                Bool _t3564 = Bool_not(_t3562);
                (void)_t3564;
                ;
                Bool _wcond3559 = Bool_and(_t3563, _t3564);
                (void)_wcond3559;
                ;
                ;
                if (_wcond3559) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3565 = parse_expression(p);
                (void)_t3565;
                Expr_add_child(e, _t3565);
                Bool _t3566 = check(p, TokenType_Comma());
                (void)_t3566;
                if (_t3566) {
                    Token *_t3560 = advance(p);
                    (void)_t3560;
                }
                ;
            }
        }
        ;
        Token *_t3570 = expect_token(p, TokenType_RBrace());
        (void)_t3570;
        Bool _t3571 = 1;
        (void)_t3571;
        e_set = _t3571;
        ;
    }
    ;
    Bool _t3682 = Bool_not(e_set);
    (void)_t3682;
    ;
    if (_t3682) {
        Str *_t3572 = Str_lit("Str", 3ULL);
        (void)_t3572;
        U64 _t3573; { U64 *_hp = (U64 *)Str_size(); _t3573 = *_hp; free(_hp); }
        (void)_t3573;
        U64 _t3574 = 8;
        (void)_t3574;
        Array *_va71 = Array_new(_t3572, &(U64){_t3573}, &(U64){_t3574});
        (void)_va71;
        Str_delete(_t3572, &(Bool){1});
        ;
        ;
        U64 _t3575 = 0;
        (void)_t3575;
        Str *_t3576 = Str_clone(&p->path);
        (void)_t3576;
        Array_set(_va71, &(U64){_t3575}, _t3576);
        ;
        U64 _t3577 = 1;
        (void)_t3577;
        Str *_t3578 = Str_lit(":", 1ULL);
        (void)_t3578;
        Array_set(_va71, &(U64){_t3577}, _t3578);
        ;
        U64 _t3579 = 2;
        (void)_t3579;
        Str *_t3580 = U32_to_str(&(U32){t_line});
        (void)_t3580;
        Array_set(_va71, &(U64){_t3579}, _t3580);
        ;
        U64 _t3581 = 3;
        (void)_t3581;
        Str *_t3582 = Str_lit(":", 1ULL);
        (void)_t3582;
        Array_set(_va71, &(U64){_t3581}, _t3582);
        ;
        U64 _t3583 = 4;
        (void)_t3583;
        Str *_t3584 = U32_to_str(&(U32){t_col});
        (void)_t3584;
        Array_set(_va71, &(U64){_t3583}, _t3584);
        ;
        U64 _t3585 = 5;
        (void)_t3585;
        Str *_t3586 = Str_lit(": unexpected token '", 20ULL);
        (void)_t3586;
        Array_set(_va71, &(U64){_t3585}, _t3586);
        ;
        U64 _t3587 = 6;
        (void)_t3587;
        Str *_t3588 = Str_clone(&t->text);
        (void)_t3588;
        Array_set(_va71, &(U64){_t3587}, _t3588);
        ;
        U64 _t3589 = 7;
        (void)_t3589;
        Str *_t3590 = Str_lit("'", 1ULL);
        (void)_t3590;
        Array_set(_va71, &(U64){_t3589}, _t3590);
        ;
        Str *_t3591 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:536:15", 64ULL);
        (void)_t3591;
        panic(_t3591, _va71);
        Str_delete(_t3591, &(Bool){1});
    }
    ;
    ;
    ;
    while (1) {
        Bool _wcond3592 = check(p, TokenType_Dot());
        (void)_wcond3592;
        if (_wcond3592) {
        } else {
            ;
            break;
        }
        ;
        Token *_t3625 = advance(p);
        (void)_t3625;
        U32 f_line = peek_line(p);
        (void)f_line;
        U32 f_col = peek_col(p);
        (void)f_col;
        Str *fname = expect_text(p, TokenType_Ident());
        (void)fname;
        Bool _t3626 = check(p, TokenType_LParen());
        (void)_t3626;
        if (_t3626) {
            Token *_t3619 = advance(p);
            (void)_t3619;
            ExprData *_t3620 = ExprData_FieldAccess(fname);
            (void)_t3620;
            Expr *callee = Expr_new(_t3620, f_line, f_col, &p->path);
            (void)callee;
            ExprData_delete(_t3620, &(Bool){1});
            Expr *_t3621 = Expr_clone(e);
            (void)_t3621;
            Expr_add_child(callee, _t3621);
            Expr *mcall = Expr_new(ExprData_FCall(), f_line, f_col, &p->path);
            (void)mcall;
            Expr_add_child(mcall, callee);
            while (1) {
                Bool _t3611 = check(p, TokenType_RParen());
                (void)_t3611;
                Bool _t3612 = check(p, TokenType_Eof());
                (void)_t3612;
                Bool _t3613 = Bool_not(_t3611);
                (void)_t3613;
                ;
                Bool _t3614 = Bool_not(_t3612);
                (void)_t3614;
                ;
                Bool _wcond3593 = Bool_and(_t3613, _t3614);
                (void)_wcond3593;
                ;
                ;
                if (_wcond3593) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3615 = check(p, TokenType_Ident());
                (void)_t3615;
                if (_t3615) {
                    U64 _t3604 = 1;
                    (void)_t3604;
                    U64 _t3605 = U64_add(p->pos, _t3604);
                    (void)_t3605;
                    ;
                    U64 _t3606; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3606 = *_hp; free(_hp); }
                    (void)_t3606;
                    Bool _t3607; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3605}, &(U64){_t3606}); _t3607 = *_hp; free(_hp); }
                    (void)_t3607;
                    ;
                    ;
                    if (_t3607) {
                        U64 _t3599 = 1;
                        (void)_t3599;
                        U64 _t3600 = U64_add(p->pos, _t3599);
                        (void)_t3600;
                        ;
                        I64 _t3601 = U64_to_i64(_t3600);
                        (void)_t3601;
                        ;
                        U64 *_t3602 = malloc(sizeof(U64)); *_t3602 = I64_to_u64(_t3601);
                        (void)_t3602;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3602);
                        (void)nt;
                        Bool _t3603; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3603 = *_hp; free(_hp); }
                        (void)_t3603;
                        U64_delete(_t3602, &(Bool){1});
                        if (_t3603) {
                            U32 na_line = peek_line(p);
                            (void)na_line;
                            U32 na_col = peek_col(p);
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3595 = advance(p);
                            (void)_t3595;
                            ExprData *_t3596 = ExprData_NamedArg(aname);
                            (void)_t3596;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3596, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3596, &(Bool){1});
                            ;
                            ;
                            Expr *_t3597 = parse_expression(p);
                            (void)_t3597;
                            Expr_add_child(na, _t3597);
                            Expr_add_child(mcall, na);
                            Bool _t3598 = check(p, TokenType_Comma());
                            (void)_t3598;
                            if (_t3598) {
                                Token *_t3594 = advance(p);
                                (void)_t3594;
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
                Bool _t3616 = check(p, TokenType_KwOwn());
                (void)_t3616;
                if (_t3616) {
                    Token *_t3608 = advance(p);
                    (void)_t3608;
                    Bool _t3609 = 1;
                    (void)_t3609;
                    is_own_arg = _t3609;
                    ;
                }
                ;
                Expr *marg = parse_expression(p);
                (void)marg;
                Bool _t3617 = Bool_clone(&(Bool){is_own_arg});
                (void)_t3617;
                ;
                marg->is_own_arg = _t3617;
                ;
                Expr_add_child(mcall, marg);
                Bool _t3618 = check(p, TokenType_Comma());
                (void)_t3618;
                if (_t3618) {
                    Token *_t3610 = advance(p);
                    (void)_t3610;
                }
                ;
            }
            Token *_t3622 = expect_token(p, TokenType_RParen());
            (void)_t3622;
            e = Expr_clone(mcall);
            Expr_delete(mcall, &(Bool){1});
        } else {
            ExprData *_t3623 = ExprData_FieldAccess(fname);
            (void)_t3623;
            Expr *access = Expr_new(_t3623, f_line, f_col, &p->path);
            (void)access;
            ExprData_delete(_t3623, &(Bool){1});
            Expr *_t3624 = Expr_clone(e);
            (void)_t3624;
            Expr_add_child(access, _t3624);
            e = Expr_clone(access);
            Expr_delete(access, &(Bool){1});
        }
        ;
        ;
        ;
        Str_delete(fname, &(Bool){1});
    }
    Bool _t3683 = check(p, TokenType_DotDot());
    (void)_t3683;
    if (_t3683) {
        U32 dt_line = peek_line(p);
        (void)dt_line;
        U32 dt_col = peek_col(p);
        (void)dt_col;
        Token *_t3627 = advance(p);
        (void)_t3627;
        Expr *rhs = parse_expression(p);
        (void)rhs;
        Str *_t3628 = Str_lit("Range", 5ULL);
        (void)_t3628;
        Str *_t3629 = Str_clone(_t3628);
        (void)_t3629;
        Str_delete(_t3628, &(Bool){1});
        ExprData *_t3630 = ExprData_Ident(_t3629);
        (void)_t3630;
        Str_delete(_t3629, &(Bool){1});
        Expr *range_ident = Expr_new(_t3630, dt_line, dt_col, &p->path);
        (void)range_ident;
        ExprData_delete(_t3630, &(Bool){1});
        Str *_t3631 = Str_lit("new", 3ULL);
        (void)_t3631;
        Str *_t3632 = Str_clone(_t3631);
        (void)_t3632;
        Str_delete(_t3631, &(Bool){1});
        ExprData *_t3633 = ExprData_FieldAccess(_t3632);
        (void)_t3633;
        Str_delete(_t3632, &(Bool){1});
        Expr *new_access = Expr_new(_t3633, dt_line, dt_col, &p->path);
        (void)new_access;
        ExprData_delete(_t3633, &(Bool){1});
        Expr_add_child(new_access, range_ident);
        Expr *rcall = Expr_new(ExprData_FCall(), dt_line, dt_col, &p->path);
        (void)rcall;
        ;
        ;
        Expr_add_child(rcall, new_access);
        Expr *_t3634 = Expr_clone(e);
        (void)_t3634;
        Expr_add_child(rcall, _t3634);
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
    Bool _t3863 = check(p, TokenType_ColonEq());
    (void)_t3863;
    if (_t3863) {
        Token *_t3684 = advance(p);
        (void)_t3684;
        Bool _t3685 = Bool_clone(&(Bool){is_mut});
        (void)_t3685;
        Bool _t3686 = 0;
        (void)_t3686;
        Bool _t3687 = 0;
        (void)_t3687;
        Bool _t3688 = Bool_clone(&(Bool){is_own});
        (void)_t3688;
        I32 _t3689 = 0;
        (void)_t3689;
        I32 _t3690 = 0;
        (void)_t3690;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3685;
        dd->is_namespace = _t3686;
        dd->is_ref = _t3687;
        dd->is_own = _t3688;
        dd->field_offset = _t3689;
        dd->field_size = _t3690;
        dd->field_struct_def = NULL;
        dd->fn_sig = NULL;
        (void)dd;
        ;
        ;
        ;
        ;
        ;
        ;
        ExprData *_t3691 = ExprData_Decl(dd);
        (void)_t3691;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3691, t_line, t_col, &p->path);
        (void)decl;
        ExprData_delete(_t3691, &(Bool){1});
        Expr *_t3692 = parse_expression(p);
        (void)_t3692;
        Expr_add_child(decl, _t3692);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return decl;
    }
    ;
    Bool _t3864 = check(p, TokenType_Colon());
    (void)_t3864;
    if (_t3864) {
        Token *_t3797 = advance(p);
        (void)_t3797;
        Bool _t3798 = check(p, TokenType_KwFunc());
        (void)_t3798;
        Bool _t3799 = check(p, TokenType_KwProc());
        (void)_t3799;
        Bool _t3800 = Bool_or(_t3798, _t3799);
        (void)_t3800;
        ;
        ;
        if (_t3800) {
            Expr *sig = parse_func_def(p);
            (void)sig;
            Token *_t3706 = expect_token(p, TokenType_Eq());
            (void)_t3706;
            Token *_t3707 = expect_token(p, TokenType_LParen());
            (void)_t3707;
            Bool _t3708; { Bool *_hp = (Bool *)ExprData_is_FuncDef(&sig->data); _t3708 = *_hp; free(_hp); }
            (void)_t3708;
            if (_t3708) {
                FunctionDef *sfd = ExprData_get_FuncDef(&sig->data);
                (void)sfd;
                Str *_t3703 = Str_lit("Str", 3ULL);
                (void)_t3703;
                U64 _t3704; { U64 *_hp = (U64 *)Str_size(); _t3704 = *_hp; free(_hp); }
                (void)_t3704;
                Vec *new_names = Vec_new(_t3703, &(U64){_t3704});
                (void)new_names;
                Str_delete(_t3703, &(Bool){1});
                ;
                Vec_delete(new_names, &(Bool){1});
                {
                    U64 _t3701 = 0;
                    (void)_t3701;
                    U64 _t3702; { U64 *_hp = (U64 *)Vec_len(&sfd->params); _t3702 = *_hp; free(_hp); }
                    (void)_t3702;
                    Range *_fc3693 = Range_new(_t3701, _t3702);
                    (void)_fc3693;
                    ;
                    ;
                    U64 _fi3693 = 0;
                    (void)_fi3693;
                    while (1) {
                        U64 _t3696; { U64 *_hp = (U64 *)Range_len(_fc3693); _t3696 = *_hp; free(_hp); }
                        (void)_t3696;
                        Bool _wcond3694; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3693}, &(U64){_t3696}); _wcond3694 = *_hp; free(_hp); }
                        (void)_wcond3694;
                        ;
                        if (_wcond3694) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 *pi = Range_get(_fc3693, _fi3693);
                        (void)pi;
                        U64 _t3697 = 1;
                        (void)_t3697;
                        U64 _t3698 = U64_add(_fi3693, _t3697);
                        (void)_t3698;
                        ;
                        _fi3693 = _t3698;
                        ;
                        U64 _t3699 = 0;
                        (void)_t3699;
                        Bool _t3700; { Bool *_hp = (Bool *)U64_gt(pi, &(U64){_t3699}); _t3700 = *_hp; free(_hp); }
                        (void)_t3700;
                        ;
                        if (_t3700) {
                            Token *_t3695 = expect_token(p, TokenType_Comma());
                            (void)_t3695;
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
                    Range_delete(_fc3693, &(Bool){1});
                    ;
                }
                ExprData_delete(&sig->data, &(Bool){0});
                { ExprData *_fa = ExprData_FuncDef(sfd); sig->data = *_fa; free(_fa); }
                FunctionDef_delete(sfd, &(Bool){1});
            }
            ;
            Bool _t3709 = check(p, TokenType_Comma());
            (void)_t3709;
            if (_t3709) {
                Token *_t3705 = advance(p);
                (void)_t3705;
            }
            ;
            Token *_t3710 = expect_token(p, TokenType_RParen());
            (void)_t3710;
            Token *_t3711 = expect_token(p, TokenType_LBrace());
            (void)_t3711;
            Expr *_t3712 = parse_block(p);
            (void)_t3712;
            Expr_add_child(sig, _t3712);
            Bool _t3713 = Bool_clone(&(Bool){is_mut});
            (void)_t3713;
            Bool _t3714 = 0;
            (void)_t3714;
            Bool _t3715 = 0;
            (void)_t3715;
            Bool _t3716 = Bool_clone(&(Bool){is_own});
            (void)_t3716;
            I32 _t3717 = 0;
            (void)_t3717;
            I32 _t3718 = 0;
            (void)_t3718;
            Declaration *dd = malloc(sizeof(Declaration));
            { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
            dd->is_mut = _t3713;
            dd->is_namespace = _t3714;
            dd->is_ref = _t3715;
            dd->is_own = _t3716;
            dd->field_offset = _t3717;
            dd->field_size = _t3718;
            dd->field_struct_def = NULL;
            dd->fn_sig = NULL;
            (void)dd;
            ;
            ;
            ;
            ;
            ;
            ;
            ExprData *_t3719 = ExprData_Decl(dd);
            (void)_t3719;
            Declaration_delete(dd, &(Bool){1});
            Expr *decl = Expr_new(_t3719, t_line, t_col, &p->path);
            (void)decl;
            ExprData_delete(_t3719, &(Bool){1});
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
        Str *_t3801 = Str_lit("Fn", 2ULL);
        (void)_t3801;
        Bool _t3802; { Bool *_hp = (Bool *)Str_eq(type_name, _t3801); _t3802 = *_hp; free(_hp); }
        (void)_t3802;
        Str_delete(_t3801, &(Bool){1});
        if (_t3802) {
            Str *syn_name = parse_fn_signature(p, t_line, t_col);
            (void)syn_name;
            U64 _t3720; { U64 *_hp = (U64 *)Str_len(syn_name); _t3720 = *_hp; free(_hp); }
            (void)_t3720;
            U64 _t3721 = 0;
            (void)_t3721;
            Bool _t3722; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3720}, &(U64){_t3721}); _t3722 = *_hp; free(_hp); }
            (void)_t3722;
            ;
            ;
            if (_t3722) {
                type_name = Str_clone(syn_name);
            }
            ;
            Str_delete(syn_name, &(Bool){1});
        }
        ;
        Token *_t3803 = expect_token(p, TokenType_Eq());
        (void)_t3803;
        Bool _t3804 = check(p, TokenType_LParen());
        (void)_t3804;
        if (_t3804) {
            U64 saved = p->pos;
            (void)saved;
            Token *_t3793 = advance(p);
            (void)_t3793;
            Bool is_fsf = 1;
            (void)is_fsf;
            while (1) {
                Bool _t3726 = check(p, TokenType_RParen());
                (void)_t3726;
                Bool _t3727 = check(p, TokenType_Eof());
                (void)_t3727;
                Bool _t3728 = Bool_not(_t3726);
                (void)_t3728;
                ;
                Bool _t3729 = Bool_not(_t3727);
                (void)_t3729;
                ;
                Bool _wcond3723 = Bool_and(_t3728, _t3729);
                (void)_wcond3723;
                ;
                ;
                if (_wcond3723) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3730 = check(p, TokenType_Ident());
                (void)_t3730;
                Bool _t3731 = Bool_not(_t3730);
                (void)_t3731;
                ;
                if (_t3731) {
                    Bool _t3724 = 0;
                    (void)_t3724;
                    is_fsf = _t3724;
                    ;
                    ;
                    break;
                }
                ;
                Token *_t3732 = advance(p);
                (void)_t3732;
                Bool _t3733 = check(p, TokenType_Comma());
                (void)_t3733;
                if (_t3733) {
                    Token *_t3725 = advance(p);
                    (void)_t3725;
                }
                ;
            }
            Bool _t3794 = check(p, TokenType_RParen());
            (void)_t3794;
            Bool _t3795 = Bool_and(is_fsf, _t3794);
            (void)_t3795;
            ;
            if (_t3795) {
                Token *_t3735 = advance(p);
                (void)_t3735;
                Bool _t3736 = check(p, TokenType_LBrace());
                (void)_t3736;
                Bool _t3737 = Bool_not(_t3736);
                (void)_t3737;
                ;
                if (_t3737) {
                    Bool _t3734 = 0;
                    (void)_t3734;
                    is_fsf = _t3734;
                    ;
                }
                ;
            } else {
                Bool _t3738 = 0;
                (void)_t3738;
                is_fsf = _t3738;
                ;
            }
            ;
            U64 _t3796 = U64_clone(&(U64){saved});
            (void)_t3796;
            ;
            p->pos = _t3796;
            ;
            if (is_fsf) {
                Token *_t3753 = expect_token(p, TokenType_LParen());
                (void)_t3753;
                Str *_t3754 = Str_lit("Str", 3ULL);
                (void)_t3754;
                U64 _t3755; { U64 *_hp = (U64 *)Str_size(); _t3755 = *_hp; free(_hp); }
                (void)_t3755;
                Vec *pnames = Vec_new(_t3754, &(U64){_t3755});
                (void)pnames;
                Str_delete(_t3754, &(Bool){1});
                ;
                while (1) {
                    Bool _t3741 = check(p, TokenType_RParen());
                    (void)_t3741;
                    Bool _wcond3739 = Bool_not(_t3741);
                    (void)_wcond3739;
                    ;
                    if (_wcond3739) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *pn = expect_text(p, TokenType_Ident());
                    (void)pn;
                    Vec_push(pnames, pn);
                    Bool _t3742 = check(p, TokenType_Comma());
                    (void)_t3742;
                    if (_t3742) {
                        Token *_t3740 = advance(p);
                        (void)_t3740;
                    }
                    ;
                }
                Token *_t3756 = expect_token(p, TokenType_RParen());
                (void)_t3756;
                Token *_t3757 = expect_token(p, TokenType_LBrace());
                (void)_t3757;
                Expr *body = parse_block(p);
                (void)body;
                Str *_t3758 = Str_lit("Param", 5ULL);
                (void)_t3758;
                U64 _t3759; { U64 *_hp = (U64 *)Param_size(); _t3759 = *_hp; free(_hp); }
                (void)_t3759;
                Str *_t3760 = Str_lit("Str", 3ULL);
                (void)_t3760;
                U64 _t3761; { U64 *_hp = (U64 *)Str_size(); _t3761 = *_hp; free(_hp); }
                (void)_t3761;
                Str *_t3762 = Str_lit("Expr", 4ULL);
                (void)_t3762;
                U64 _t3763; { U64 *_hp = (U64 *)Expr_size(); _t3763 = *_hp; free(_hp); }
                (void)_t3763;
                I64 _t3764 = 0;
                (void)_t3764;
                I64 _t3765 = 1;
                (void)_t3765;
                I64 _t3766 = I64_sub(_t3764, _t3765);
                (void)_t3766;
                ;
                ;
                I64 _t3767 = 0;
                (void)_t3767;
                I64 _t3768 = 1;
                (void)_t3768;
                I64 _t3769 = I64_sub(_t3767, _t3768);
                (void)_t3769;
                ;
                ;
                U32 _t3770 = 0;
                (void)_t3770;
                I32 _t3771 = I64_to_i32(_t3766);
                (void)_t3771;
                ;
                I32 _t3772 = I64_to_i32(_t3769);
                (void)_t3772;
                ;
                Bool _t3773 = 0;
                (void)_t3773;
                Bool _t3774 = 0;
                (void)_t3774;
                FunctionDef *ffd = malloc(sizeof(FunctionDef));
                { FuncType *_ca = FuncType_clone(FuncType_Func()); ffd->func_type = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3758, &(U64){_t3759}); ffd->params = *_ca; free(_ca); }
                ffd->nparam = _t3770;
                { Map *_ca = Map_new(_t3760, &(U64){_t3761}, _t3762, &(U64){_t3763}); ffd->param_defaults = *_ca; free(_ca); }
                { Str *_ca = Str_clone(Str_lit("", 0ULL)); ffd->return_type = *_ca; free(_ca); }
                ffd->variadic_index = _t3771;
                ffd->kwargs_index = _t3772;
                ffd->return_is_ref = _t3773;
                ffd->return_is_shallow = _t3774;
                (void)ffd;
                Str_delete(_t3758, &(Bool){1});
                ;
                Str_delete(_t3760, &(Bool){1});
                ;
                Str_delete(_t3762, &(Bool){1});
                ;
                ;
                ;
                ;
                ;
                ;
                FuncType_delete(&ffd->func_type, &(Bool){0});
                { FuncType *_fa = FuncType_clone(FuncType_Func()); ffd->func_type = *_fa; free(_fa); }
                I64 _t3775 = 0;
                (void)_t3775;
                I64 _t3776 = 1;
                (void)_t3776;
                I64 _t3777 = I64_sub(_t3775, _t3776);
                (void)_t3777;
                ;
                ;
                I32 _t3778 = I64_to_i32(_t3777);
                (void)_t3778;
                ;
                ffd->variadic_index = _t3778;
                ;
                I64 _t3779 = 0;
                (void)_t3779;
                I64 _t3780 = 1;
                (void)_t3780;
                I64 _t3781 = I64_sub(_t3779, _t3780);
                (void)_t3781;
                ;
                ;
                I32 _t3782 = I64_to_i32(_t3781);
                (void)_t3782;
                ;
                ffd->kwargs_index = _t3782;
                ;
                U64 np; { U64 *_hp = (U64 *)Vec_len(pnames); np = *_hp; free(_hp); }
                (void)np;
                {
                    U64 _t3752 = 0;
                    (void)_t3752;
                    Range *_fc3743 = Range_new(_t3752, np);
                    (void)_fc3743;
                    ;
                    U64 _fi3743 = 0;
                    (void)_fi3743;
                    while (1) {
                        U64 _t3745; { U64 *_hp = (U64 *)Range_len(_fc3743); _t3745 = *_hp; free(_hp); }
                        (void)_t3745;
                        Bool _wcond3744; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3743}, &(U64){_t3745}); _wcond3744 = *_hp; free(_hp); }
                        (void)_wcond3744;
                        ;
                        if (_wcond3744) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 *i = Range_get(_fc3743, _fi3743);
                        (void)i;
                        U64 _t3746 = 1;
                        (void)_t3746;
                        U64 _t3747 = U64_add(_fi3743, _t3746);
                        (void)_t3747;
                        ;
                        _fi3743 = _t3747;
                        ;
                        Str *pn = Vec_get(pnames, i);
                        (void)pn;
                        Bool _t3748 = 0;
                        (void)_t3748;
                        Bool _t3749 = 0;
                        (void)_t3749;
                        Bool _t3750 = 0;
                        (void)_t3750;
                        Param *_t3751 = malloc(sizeof(Param));
                        { Str *_ca = Str_clone(pn); _t3751->name = *_ca; free(_ca); }
                        { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t3751->ptype = *_ca; free(_ca); }
                        _t3751->is_mut = _t3748;
                        _t3751->is_own = _t3749;
                        _t3751->is_shallow = _t3750;
                        (void)_t3751;
                        ;
                        ;
                        ;
                        U64_delete(i, &(Bool){1});
                        Vec_push(&ffd->params, _t3751);
                    }
                    Range_delete(_fc3743, &(Bool){1});
                    ;
                }
                Vec_delete(pnames, &(Bool){1});
                I64 _t3783 = U64_to_i64(np);
                (void)_t3783;
                ;
                U32 _t3784 = I64_to_u32(_t3783);
                (void)_t3784;
                ;
                ffd->nparam = _t3784;
                ;
                ExprData *_t3785 = ExprData_FuncDef(ffd);
                (void)_t3785;
                FunctionDef_delete(ffd, &(Bool){1});
                Expr *fdef = Expr_new(_t3785, t_line, t_col, &p->path);
                (void)fdef;
                ExprData_delete(_t3785, &(Bool){1});
                Expr_add_child(fdef, body);
                Bool _t3786 = Bool_clone(&(Bool){is_mut});
                (void)_t3786;
                Bool _t3787 = 0;
                (void)_t3787;
                Bool _t3788 = 0;
                (void)_t3788;
                Bool _t3789 = Bool_clone(&(Bool){is_own});
                (void)_t3789;
                I32 _t3790 = 0;
                (void)_t3790;
                I32 _t3791 = 0;
                (void)_t3791;
                Declaration *dd = malloc(sizeof(Declaration));
                { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
                { Str *_ca = Str_clone(type_name); dd->explicit_type = *_ca; free(_ca); }
                dd->is_mut = _t3786;
                dd->is_namespace = _t3787;
                dd->is_ref = _t3788;
                dd->is_own = _t3789;
                dd->field_offset = _t3790;
                dd->field_size = _t3791;
                dd->field_struct_def = NULL;
                dd->fn_sig = NULL;
                (void)dd;
                ;
                ;
                ;
                ;
                ;
                ;
                ExprData *_t3792 = ExprData_Decl(dd);
                (void)_t3792;
                Declaration_delete(dd, &(Bool){1});
                Expr *decl = Expr_new(_t3792, t_line, t_col, &p->path);
                (void)decl;
                ExprData_delete(_t3792, &(Bool){1});
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
        Bool _t3805 = Bool_clone(&(Bool){is_mut});
        (void)_t3805;
        Bool _t3806 = 0;
        (void)_t3806;
        Bool _t3807 = 0;
        (void)_t3807;
        Bool _t3808 = Bool_clone(&(Bool){is_own});
        (void)_t3808;
        I32 _t3809 = 0;
        (void)_t3809;
        I32 _t3810 = 0;
        (void)_t3810;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(type_name); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3805;
        dd->is_namespace = _t3806;
        dd->is_ref = _t3807;
        dd->is_own = _t3808;
        dd->field_offset = _t3809;
        dd->field_size = _t3810;
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
        ExprData *_t3811 = ExprData_Decl(dd);
        (void)_t3811;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3811, t_line, t_col, &p->path);
        (void)decl;
        ExprData_delete(_t3811, &(Bool){1});
        Expr *_t3812 = parse_expression(p);
        (void)_t3812;
        Expr_add_child(decl, _t3812);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return decl;
    }
    ;
    Bool _t3865 = check(p, TokenType_Dot());
    (void)_t3865;
    if (_t3865) {
        Str *_t3851 = Str_clone(name);
        (void)_t3851;
        ExprData *_t3852 = ExprData_Ident(_t3851);
        (void)_t3852;
        Str_delete(_t3851, &(Bool){1});
        Expr *obj = Expr_new(_t3852, t_line, t_col, &p->path);
        (void)obj;
        ExprData_delete(_t3852, &(Bool){1});
        Str *last_field = Str_lit("", 0ULL);
        (void)last_field;
        U32 last_line = 0;
        (void)last_line;
        U32 last_col = 0;
        (void)last_col;
        while (1) {
            Bool _wcond3813 = check(p, TokenType_Dot());
            (void)_wcond3813;
            if (_wcond3813) {
            } else {
                ;
                break;
            }
            ;
            Token *_t3817 = advance(p);
            (void)_t3817;
            U32 _t3818 = peek_line(p);
            (void)_t3818;
            last_line = _t3818;
            ;
            U32 _t3819 = peek_col(p);
            (void)_t3819;
            last_col = _t3819;
            ;
            last_field = expect_text(p, TokenType_Ident());
            Bool _t3820 = check(p, TokenType_Dot());
            (void)_t3820;
            if (_t3820) {
                Str *_t3814 = Str_clone(last_field);
                (void)_t3814;
                ExprData *_t3815 = ExprData_FieldAccess(_t3814);
                (void)_t3815;
                Str_delete(_t3814, &(Bool){1});
                Expr *access = Expr_new(_t3815, last_line, last_col, &p->path);
                (void)access;
                ExprData_delete(_t3815, &(Bool){1});
                Expr *_t3816 = Expr_clone(obj);
                (void)_t3816;
                Expr_add_child(access, _t3816);
                obj = Expr_clone(access);
                Expr_delete(access, &(Bool){1});
            }
            ;
        }
        Bool _t3853 = check(p, TokenType_LParen());
        (void)_t3853;
        if (_t3853) {
            Token *_t3847 = advance(p);
            (void)_t3847;
            ExprData *_t3848 = ExprData_FieldAccess(last_field);
            (void)_t3848;
            Expr *callee = Expr_new(_t3848, last_line, last_col, &p->path);
            (void)callee;
            ExprData_delete(_t3848, &(Bool){1});
            Expr *_t3849 = Expr_clone(obj);
            (void)_t3849;
            Expr_add_child(callee, _t3849);
            Expr *mcall = Expr_new(ExprData_FCall(), last_line, last_col, &p->path);
            (void)mcall;
            Expr_add_child(mcall, callee);
            while (1) {
                Bool _t3839 = check(p, TokenType_RParen());
                (void)_t3839;
                Bool _t3840 = check(p, TokenType_Eof());
                (void)_t3840;
                Bool _t3841 = Bool_not(_t3839);
                (void)_t3841;
                ;
                Bool _t3842 = Bool_not(_t3840);
                (void)_t3842;
                ;
                Bool _wcond3821 = Bool_and(_t3841, _t3842);
                (void)_wcond3821;
                ;
                ;
                if (_wcond3821) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3843 = check(p, TokenType_Ident());
                (void)_t3843;
                if (_t3843) {
                    U64 _t3832 = 1;
                    (void)_t3832;
                    U64 _t3833 = U64_add(p->pos, _t3832);
                    (void)_t3833;
                    ;
                    U64 _t3834; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3834 = *_hp; free(_hp); }
                    (void)_t3834;
                    Bool _t3835; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3833}, &(U64){_t3834}); _t3835 = *_hp; free(_hp); }
                    (void)_t3835;
                    ;
                    ;
                    if (_t3835) {
                        U64 _t3827 = 1;
                        (void)_t3827;
                        U64 _t3828 = U64_add(p->pos, _t3827);
                        (void)_t3828;
                        ;
                        I64 _t3829 = U64_to_i64(_t3828);
                        (void)_t3829;
                        ;
                        U64 *_t3830 = malloc(sizeof(U64)); *_t3830 = I64_to_u64(_t3829);
                        (void)_t3830;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3830);
                        (void)nt;
                        Bool _t3831; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3831 = *_hp; free(_hp); }
                        (void)_t3831;
                        U64_delete(_t3830, &(Bool){1});
                        if (_t3831) {
                            U32 na_line = peek_line(p);
                            (void)na_line;
                            U32 na_col = peek_col(p);
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3823 = advance(p);
                            (void)_t3823;
                            ExprData *_t3824 = ExprData_NamedArg(aname);
                            (void)_t3824;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3824, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3824, &(Bool){1});
                            ;
                            ;
                            Expr *_t3825 = parse_expression(p);
                            (void)_t3825;
                            Expr_add_child(na, _t3825);
                            Expr_add_child(mcall, na);
                            Bool _t3826 = check(p, TokenType_Comma());
                            (void)_t3826;
                            if (_t3826) {
                                Token *_t3822 = advance(p);
                                (void)_t3822;
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
                Bool _t3844 = check(p, TokenType_KwOwn());
                (void)_t3844;
                if (_t3844) {
                    Token *_t3836 = advance(p);
                    (void)_t3836;
                    Bool _t3837 = 1;
                    (void)_t3837;
                    is_own_arg = _t3837;
                    ;
                }
                ;
                Expr *marg = parse_expression(p);
                (void)marg;
                Bool _t3845 = Bool_clone(&(Bool){is_own_arg});
                (void)_t3845;
                ;
                marg->is_own_arg = _t3845;
                ;
                Expr_add_child(mcall, marg);
                Bool _t3846 = check(p, TokenType_Comma());
                (void)_t3846;
                if (_t3846) {
                    Token *_t3838 = advance(p);
                    (void)_t3838;
                }
                ;
            }
            Token *_t3850 = expect_token(p, TokenType_RParen());
            (void)_t3850;
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
        Token *_t3854 = expect_token(p, TokenType_Eq());
        (void)_t3854;
        ExprData *_t3855 = ExprData_FieldAssign(last_field);
        (void)_t3855;
        Str_delete(last_field, &(Bool){1});
        Expr *fa = Expr_new(_t3855, t_line, t_col, &p->path);
        (void)fa;
        ExprData_delete(_t3855, &(Bool){1});
        Expr *_t3856 = Expr_clone(obj);
        (void)_t3856;
        Expr_delete(obj, &(Bool){1});
        Expr_add_child(fa, _t3856);
        Expr *_t3857 = parse_expression(p);
        (void)_t3857;
        Expr_add_child(fa, _t3857);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return fa;
    }
    ;
    Bool _t3866 = check(p, TokenType_Eq());
    (void)_t3866;
    if (_t3866) {
        Token *_t3858 = advance(p);
        (void)_t3858;
        Str *_t3859 = Str_clone(name);
        (void)_t3859;
        ExprData *_t3860 = ExprData_Assign(_t3859);
        (void)_t3860;
        Str_delete(_t3859, &(Bool){1});
        Expr *assign = Expr_new(_t3860, t_line, t_col, &p->path);
        (void)assign;
        ExprData_delete(_t3860, &(Bool){1});
        Expr *_t3861 = parse_expression(p);
        (void)_t3861;
        Expr_add_child(assign, _t3861);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return assign;
    }
    ;
    Bool _t3867 = check(p, TokenType_LParen());
    (void)_t3867;
    if (_t3867) {
        Expr *_t3862 = parse_call(p, name, t_line, t_col);
        (void)_t3862;
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return _t3862;
    }
    ;
    Str *_t3868 = Str_lit("Str", 3ULL);
    (void)_t3868;
    U64 _t3869; { U64 *_hp = (U64 *)Str_size(); _t3869 = *_hp; free(_hp); }
    (void)_t3869;
    U64 _t3870 = 8;
    (void)_t3870;
    Array *_va72 = Array_new(_t3868, &(U64){_t3869}, &(U64){_t3870});
    (void)_va72;
    Str_delete(_t3868, &(Bool){1});
    ;
    ;
    U64 _t3871 = 0;
    (void)_t3871;
    Str *_t3872 = Str_clone(&p->path);
    (void)_t3872;
    Array_set(_va72, &(U64){_t3871}, _t3872);
    ;
    U64 _t3873 = 1;
    (void)_t3873;
    Str *_t3874 = Str_lit(":", 1ULL);
    (void)_t3874;
    Array_set(_va72, &(U64){_t3873}, _t3874);
    ;
    U64 _t3875 = 2;
    (void)_t3875;
    Str *_t3876 = U32_to_str(&(U32){t_line});
    (void)_t3876;
    ;
    Array_set(_va72, &(U64){_t3875}, _t3876);
    ;
    U64 _t3877 = 3;
    (void)_t3877;
    Str *_t3878 = Str_lit(":", 1ULL);
    (void)_t3878;
    Array_set(_va72, &(U64){_t3877}, _t3878);
    ;
    U64 _t3879 = 4;
    (void)_t3879;
    Str *_t3880 = U32_to_str(&(U32){t_col});
    (void)_t3880;
    ;
    Array_set(_va72, &(U64){_t3879}, _t3880);
    ;
    U64 _t3881 = 5;
    (void)_t3881;
    Str *_t3882 = Str_lit(": expected ':=', ':', '=' or '(' after identifier '", 51ULL);
    (void)_t3882;
    Array_set(_va72, &(U64){_t3881}, _t3882);
    ;
    U64 _t3883 = 6;
    (void)_t3883;
    Str *_t3884 = Str_clone(name);
    (void)_t3884;
    Str_delete(name, &(Bool){1});
    Array_set(_va72, &(U64){_t3883}, _t3884);
    ;
    U64 _t3885 = 7;
    (void)_t3885;
    Str *_t3886 = Str_lit("'", 1ULL);
    (void)_t3886;
    Array_set(_va72, &(U64){_t3885}, _t3886);
    ;
    Str *_t3887 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:797:11", 64ULL);
    (void)_t3887;
    panic(_t3887, _va72);
    Str_delete(_t3887, &(Bool){1});
    U32 _t3888 = 0;
    (void)_t3888;
    U32 _t3889 = 0;
    (void)_t3889;
    Expr *_t3890 = Expr_new(ExprData_Body(), _t3888, _t3889, &p->path);
    (void)_t3890;
    ;
    ;
    return _t3890;
}

Expr * parse_statement(Parser * p) {
    (void)p;
    U32 t_line = peek_line(p);
    (void)t_line;
    U32 t_col = peek_col(p);
    (void)t_col;
    Token *t = peek(p);
    (void)t;
    Bool _t4028; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t4028 = *_hp; free(_hp); }
    (void)_t4028;
    if (_t4028) {
        Bool _t3891 = 0;
        (void)_t3891;
        Bool _t3892 = 0;
        (void)_t3892;
        Expr *_t3893 = parse_statement_ident(p, _t3891, _t3892);
        (void)_t3893;
        ;
        ;
        ;
        ;
        ;
        return _t3893;
    }
    ;
    Bool _t4029; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwRef()); _t4029 = *_hp; free(_hp); }
    (void)_t4029;
    if (_t4029) {
        Token *_t3900 = advance(p);
        (void)_t3900;
        Bool ref_mut = 0;
        (void)ref_mut;
        Bool _t3901 = check(p, TokenType_KwMut());
        (void)_t3901;
        if (_t3901) {
            Token *_t3894 = advance(p);
            (void)_t3894;
            Bool _t3895 = 1;
            (void)_t3895;
            ref_mut = _t3895;
            ;
        }
        ;
        U32 i_line = peek_line(p);
        (void)i_line;
        U32 i_col = peek_col(p);
        (void)i_col;
        Str *iname = expect_text(p, TokenType_Ident());
        (void)iname;
        Bool _t3902 = 0;
        (void)_t3902;
        Bool _t3903 = 0;
        (void)_t3903;
        Bool _t3904 = 1;
        (void)_t3904;
        Bool _t3905 = 0;
        (void)_t3905;
        I32 _t3906 = 0;
        (void)_t3906;
        I32 _t3907 = 0;
        (void)_t3907;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(iname); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3902;
        dd->is_namespace = _t3903;
        dd->is_ref = _t3904;
        dd->is_own = _t3905;
        dd->field_offset = _t3906;
        dd->field_size = _t3907;
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
            Bool _t3896 = 1;
            (void)_t3896;
            dd->is_mut = _t3896;
            ;
        }
        ;
        Bool _t3908 = check(p, TokenType_Colon());
        (void)_t3908;
        if (_t3908) {
            Token *_t3897 = advance(p);
            (void)_t3897;
            Str_delete(&dd->explicit_type, &(Bool){0});
            { Str *_fa = expect_text(p, TokenType_Ident()); dd->explicit_type = *_fa; free(_fa); }
            Token *_t3898 = expect_token(p, TokenType_Eq());
            (void)_t3898;
        } else {
            Token *_t3899 = expect_token(p, TokenType_ColonEq());
            (void)_t3899;
        }
        ;
        ExprData *_t3909 = ExprData_Decl(dd);
        (void)_t3909;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3909, i_line, i_col, &p->path);
        (void)decl;
        ExprData_delete(_t3909, &(Bool){1});
        ;
        ;
        Expr *_t3910 = parse_expression(p);
        (void)_t3910;
        Expr_add_child(decl, _t3910);
        ;
        ;
        ;
        return decl;
    }
    ;
    Bool _t4030; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMut()); _t4030 = *_hp; free(_hp); }
    (void)_t4030;
    if (_t4030) {
        Token *_t3911 = advance(p);
        (void)_t3911;
        Bool _t3912 = 1;
        (void)_t3912;
        Bool _t3913 = 0;
        (void)_t3913;
        Expr *_t3914 = parse_statement_ident(p, _t3912, _t3913);
        (void)_t3914;
        ;
        ;
        ;
        ;
        ;
        return _t3914;
    }
    ;
    Bool _t4031; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwReturn()); _t4031 = *_hp; free(_hp); }
    (void)_t4031;
    if (_t4031) {
        Token *_t3916 = advance(p);
        (void)_t3916;
        Expr *ret = Expr_new(ExprData_Return(), t_line, t_col, &p->path);
        (void)ret;
        Bool _t3917 = check(p, TokenType_RBrace());
        (void)_t3917;
        Bool _t3918 = check(p, TokenType_Eof());
        (void)_t3918;
        Bool _t3919 = Bool_not(_t3917);
        (void)_t3919;
        ;
        Bool _t3920 = Bool_not(_t3918);
        (void)_t3920;
        ;
        Bool _t3921 = Bool_and(_t3919, _t3920);
        (void)_t3921;
        ;
        ;
        if (_t3921) {
            Expr *_t3915 = parse_expression(p);
            (void)_t3915;
            Expr_add_child(ret, _t3915);
        }
        ;
        ;
        ;
        ;
        return ret;
    }
    ;
    Bool _t4032; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwIf()); _t4032 = *_hp; free(_hp); }
    (void)_t4032;
    if (_t4032) {
        Token *_t3929 = advance(p);
        (void)_t3929;
        Expr *node = Expr_new(ExprData_If(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t3930 = parse_expression(p);
        (void)_t3930;
        Expr_add_child(node, _t3930);
        Token *_t3931 = expect_token(p, TokenType_LBrace());
        (void)_t3931;
        Expr *_t3932 = parse_block(p);
        (void)_t3932;
        Expr_add_child(node, _t3932);
        Bool _t3933 = check(p, TokenType_KwElse());
        (void)_t3933;
        if (_t3933) {
            Token *_t3927 = advance(p);
            (void)_t3927;
            Bool _t3928 = check(p, TokenType_KwIf());
            (void)_t3928;
            if (_t3928) {
                U32 _t3922 = peek_line(p);
                (void)_t3922;
                U32 _t3923 = peek_col(p);
                (void)_t3923;
                Expr *else_body = Expr_new(ExprData_Body(), _t3922, _t3923, &p->path);
                (void)else_body;
                ;
                ;
                Expr *_t3924 = parse_statement(p);
                (void)_t3924;
                Expr_add_child(else_body, _t3924);
                Expr_add_child(node, else_body);
            } else {
                Token *_t3925 = expect_token(p, TokenType_LBrace());
                (void)_t3925;
                Expr *_t3926 = parse_block(p);
                (void)_t3926;
                Expr_add_child(node, _t3926);
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
    Bool _t4033; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t4033 = *_hp; free(_hp); }
    (void)_t4033;
    Bool _t4034; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t4034 = *_hp; free(_hp); }
    (void)_t4034;
    Bool _t4035 = Bool_or(_t4033, _t4034);
    (void)_t4035;
    ;
    ;
    Bool _t4036; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t4036 = *_hp; free(_hp); }
    (void)_t4036;
    Bool _t4037 = Bool_or(_t4035, _t4036);
    (void)_t4037;
    ;
    ;
    Bool _t4038; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t4038 = *_hp; free(_hp); }
    (void)_t4038;
    Bool _t4039 = Bool_or(_t4037, _t4038);
    (void)_t4039;
    ;
    ;
    Bool _t4040; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwNull()); _t4040 = *_hp; free(_hp); }
    (void)_t4040;
    Bool _t4041 = Bool_or(_t4039, _t4040);
    (void)_t4041;
    ;
    ;
    if (_t4041) {
        Expr *_t3934 = parse_expression(p);
        (void)_t3934;
        ;
        ;
        ;
        return _t3934;
    }
    ;
    Bool _t4042; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t4042 = *_hp; free(_hp); }
    (void)_t4042;
    if (_t4042) {
        Token *_t3935 = advance(p);
        (void)_t3935;
        Expr *_t3936 = parse_block(p);
        (void)_t3936;
        ;
        ;
        ;
        return _t3936;
    }
    ;
    Bool _t4043; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwWhile()); _t4043 = *_hp; free(_hp); }
    (void)_t4043;
    if (_t4043) {
        Token *_t3937 = advance(p);
        (void)_t3937;
        Expr *node = Expr_new(ExprData_While(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t3938 = parse_expression(p);
        (void)_t3938;
        Expr_add_child(node, _t3938);
        Token *_t3939 = expect_token(p, TokenType_LBrace());
        (void)_t3939;
        Expr *_t3940 = parse_block(p);
        (void)_t3940;
        Expr_add_child(node, _t3940);
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4044; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFor()); _t4044 = *_hp; free(_hp); }
    (void)_t4044;
    if (_t4044) {
        Token *_t3942 = advance(p);
        (void)_t3942;
        U32 i_line = peek_line(p);
        (void)i_line;
        U32 i_col = peek_col(p);
        (void)i_col;
        Str *iname = expect_text(p, TokenType_Ident());
        (void)iname;
        ExprData *_t3943 = ExprData_ForIn(iname);
        (void)_t3943;
        Str_delete(iname, &(Bool){1});
        Expr *node = Expr_new(_t3943, i_line, i_col, &p->path);
        (void)node;
        ExprData_delete(_t3943, &(Bool){1});
        ;
        ;
        Bool _t3944 = check(p, TokenType_Colon());
        (void)_t3944;
        if (_t3944) {
            Token *_t3941 = advance(p);
            (void)_t3941;
            Str_delete(&node->struct_name, &(Bool){0});
            { Str *_fa = expect_text(p, TokenType_Ident()); node->struct_name = *_fa; free(_fa); }
        }
        ;
        Token *_t3945 = expect_token(p, TokenType_KwIn());
        (void)_t3945;
        Expr *_t3946 = parse_expression(p);
        (void)_t3946;
        Expr_add_child(node, _t3946);
        Token *_t3947 = expect_token(p, TokenType_LBrace());
        (void)_t3947;
        Expr *_t3948 = parse_block(p);
        (void)_t3948;
        Expr_add_child(node, _t3948);
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4045; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwSwitch()); _t4045 = *_hp; free(_hp); }
    (void)_t4045;
    if (_t4045) {
        Token *_t3972 = advance(p);
        (void)_t3972;
        Expr *node = Expr_new(ExprData_Switch(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t3973 = parse_expression(p);
        (void)_t3973;
        Expr_add_child(node, _t3973);
        Token *_t3974 = expect_token(p, TokenType_LBrace());
        (void)_t3974;
        while (1) {
            Bool _t3960 = check(p, TokenType_RBrace());
            (void)_t3960;
            Bool _t3961 = check(p, TokenType_Eof());
            (void)_t3961;
            Bool _t3962 = Bool_not(_t3960);
            (void)_t3962;
            ;
            Bool _t3963 = Bool_not(_t3961);
            (void)_t3963;
            ;
            Bool _wcond3949 = Bool_and(_t3962, _t3963);
            (void)_wcond3949;
            ;
            ;
            if (_wcond3949) {
            } else {
                ;
                break;
            }
            ;
            Token *_t3964 = expect_token(p, TokenType_KwCase());
            (void)_t3964;
            U32 _t3965 = peek_line(p);
            (void)_t3965;
            U32 _t3966 = peek_col(p);
            (void)_t3966;
            Expr *cn = Expr_new(ExprData_Case(), _t3965, _t3966, &p->path);
            (void)cn;
            ;
            ;
            Bool _t3967 = check(p, TokenType_Colon());
            (void)_t3967;
            Bool _t3968 = Bool_not(_t3967);
            (void)_t3968;
            ;
            if (_t3968) {
                Expr *_t3950 = parse_expression(p);
                (void)_t3950;
                Expr_add_child(cn, _t3950);
            }
            ;
            Token *_t3969 = expect_token(p, TokenType_Colon());
            (void)_t3969;
            U32 _t3970 = peek_line(p);
            (void)_t3970;
            U32 _t3971 = peek_col(p);
            (void)_t3971;
            Expr *cb = Expr_new(ExprData_Body(), _t3970, _t3971, &p->path);
            (void)cb;
            ;
            ;
            while (1) {
                Bool _t3952 = check(p, TokenType_KwCase());
                (void)_t3952;
                Bool _t3953 = check(p, TokenType_RBrace());
                (void)_t3953;
                Bool _t3954 = Bool_not(_t3952);
                (void)_t3954;
                ;
                Bool _t3955 = Bool_not(_t3953);
                (void)_t3955;
                ;
                Bool _t3956 = check(p, TokenType_Eof());
                (void)_t3956;
                Bool _t3957 = Bool_and(_t3954, _t3955);
                (void)_t3957;
                ;
                ;
                Bool _t3958 = Bool_not(_t3956);
                (void)_t3958;
                ;
                Bool _wcond3951 = Bool_and(_t3957, _t3958);
                (void)_wcond3951;
                ;
                ;
                if (_wcond3951) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3959 = parse_statement(p);
                (void)_t3959;
                Expr_add_child(cb, _t3959);
            }
            Expr_add_child(cn, cb);
            Expr_add_child(node, cn);
        }
        Token *_t3975 = expect_token(p, TokenType_RBrace());
        (void)_t3975;
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4046; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwOwn()); _t4046 = *_hp; free(_hp); }
    (void)_t4046;
    if (_t4046) {
        Token *_t4017 = advance(p);
        (void)_t4017;
        Bool _t4018 = check(p, TokenType_Ident());
        (void)_t4018;
        Bool _t4019 = check(p, TokenType_KwMut());
        (void)_t4019;
        Bool _t4020 = Bool_or(_t4018, _t4019);
        (void)_t4020;
        ;
        ;
        if (_t4020) {
            Bool own_mut = 0;
            (void)own_mut;
            Bool _t4007 = check(p, TokenType_KwMut());
            (void)_t4007;
            if (_t4007) {
                Token *_t3976 = advance(p);
                (void)_t3976;
                Bool _t3977 = 1;
                (void)_t3977;
                own_mut = _t3977;
                ;
            }
            ;
            Bool _t4008 = check(p, TokenType_Ident());
            (void)_t4008;
            if (_t4008) {
                U64 _t3987 = 1;
                (void)_t3987;
                U64 _t3988 = U64_add(p->pos, _t3987);
                (void)_t3988;
                ;
                U64 _t3989; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3989 = *_hp; free(_hp); }
                (void)_t3989;
                Bool _t3990; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3988}, &(U64){_t3989}); _t3990 = *_hp; free(_hp); }
                (void)_t3990;
                ;
                ;
                if (_t3990) {
                    U64 _t3980 = 1;
                    (void)_t3980;
                    U64 _t3981 = U64_add(p->pos, _t3980);
                    (void)_t3981;
                    ;
                    I64 _t3982 = U64_to_i64(_t3981);
                    (void)_t3982;
                    ;
                    U64 *_t3983 = malloc(sizeof(U64)); *_t3983 = I64_to_u64(_t3982);
                    (void)_t3983;
                    ;
                    Token *nt = Vec_get(&p->tokens, _t3983);
                    (void)nt;
                    Bool _t3984; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_ColonEq()); _t3984 = *_hp; free(_hp); }
                    (void)_t3984;
                    Bool _t3985; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Colon()); _t3985 = *_hp; free(_hp); }
                    (void)_t3985;
                    U64_delete(_t3983, &(Bool){1});
                    Bool _t3986 = Bool_or(_t3984, _t3985);
                    (void)_t3986;
                    ;
                    ;
                    if (_t3986) {
                        Bool _t3978 = 1;
                        (void)_t3978;
                        Expr *_t3979 = parse_statement_ident(p, own_mut, _t3978);
                        (void)_t3979;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        return _t3979;
                    }
                    ;
                }
                ;
            }
            ;
            if (own_mut) {
                Str *_t3991 = Str_lit("Str", 3ULL);
                (void)_t3991;
                U64 _t3992; { U64 *_hp = (U64 *)Str_size(); _t3992 = *_hp; free(_hp); }
                (void)_t3992;
                U64 _t3993 = 6;
                (void)_t3993;
                Array *_va73 = Array_new(_t3991, &(U64){_t3992}, &(U64){_t3993});
                (void)_va73;
                Str_delete(_t3991, &(Bool){1});
                ;
                ;
                U64 _t3994 = 0;
                (void)_t3994;
                Str *_t3995 = Str_clone(&p->path);
                (void)_t3995;
                Array_set(_va73, &(U64){_t3994}, _t3995);
                ;
                U64 _t3996 = 1;
                (void)_t3996;
                Str *_t3997 = Str_lit(":", 1ULL);
                (void)_t3997;
                Array_set(_va73, &(U64){_t3996}, _t3997);
                ;
                U64 _t3998 = 2;
                (void)_t3998;
                Str *_t3999 = U32_to_str(&(U32){t_line});
                (void)_t3999;
                Array_set(_va73, &(U64){_t3998}, _t3999);
                ;
                U64 _t4000 = 3;
                (void)_t4000;
                Str *_t4001 = Str_lit(":", 1ULL);
                (void)_t4001;
                Array_set(_va73, &(U64){_t4000}, _t4001);
                ;
                U64 _t4002 = 4;
                (void)_t4002;
                Str *_t4003 = U32_to_str(&(U32){t_col});
                (void)_t4003;
                Array_set(_va73, &(U64){_t4002}, _t4003);
                ;
                U64 _t4004 = 5;
                (void)_t4004;
                Str *_t4005 = Str_lit(": expected identifier after 'own mut'", 37ULL);
                (void)_t4005;
                Array_set(_va73, &(U64){_t4004}, _t4005);
                ;
                Str *_t4006 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:931:23", 64ULL);
                (void)_t4006;
                panic(_t4006, _va73);
                Str_delete(_t4006, &(Bool){1});
            }
            ;
        }
        ;
        Expr *expr = parse_expression(p);
        (void)expr;
        I64 _t4021 = 0;
        (void)_t4021;
        I64 _t4022 = 1;
        (void)_t4022;
        I64 primary_idx = I64_sub(_t4021, _t4022);
        (void)primary_idx;
        ;
        ;
        ;
        Expr *cur = Expr_clone(expr);
        (void)cur;
        while (1) {
            U64 _t4010; { U64 *_hp = (U64 *)Vec_len(&cur->children); _t4010 = *_hp; free(_hp); }
            (void)_t4010;
            U64 _t4011 = 0;
            (void)_t4011;
            Bool _t4012; { Bool *_hp = (Bool *)ExprData_is_FCall(&cur->data); _t4012 = *_hp; free(_hp); }
            (void)_t4012;
            Bool _t4013; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(&cur->data); _t4013 = *_hp; free(_hp); }
            (void)_t4013;
            Bool _t4014; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4010}, &(U64){_t4011}); _t4014 = *_hp; free(_hp); }
            (void)_t4014;
            ;
            ;
            Bool _t4015 = Bool_or(_t4012, _t4013);
            (void)_t4015;
            ;
            ;
            Bool _wcond4009 = Bool_and(_t4014, _t4015);
            (void)_wcond4009;
            ;
            ;
            if (_wcond4009) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t4016 = malloc(sizeof(U64));
            *_t4016 = 0;
            (void)_t4016;
            Expr *ch = Vec_get(&cur->children, _t4016);
            (void)ch;
            cur = Expr_clone(ch);
            U64_delete(_t4016, &(Bool){1});
        }
        Bool _t4023 = 1;
        (void)_t4023;
        cur->is_own_arg = _t4023;
        ;
        Expr_delete(cur, &(Bool){1});
        ;
        ;
        ;
        ;
        return expr;
    }
    ;
    Bool _t4047; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwBreak()); _t4047 = *_hp; free(_hp); }
    (void)_t4047;
    if (_t4047) {
        Token *_t4024 = advance(p);
        (void)_t4024;
        Expr *_t4025 = Expr_new(ExprData_Break(), t_line, t_col, &p->path);
        (void)_t4025;
        ;
        ;
        ;
        return _t4025;
    }
    ;
    Bool _t4048; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwContinue()); _t4048 = *_hp; free(_hp); }
    (void)_t4048;
    if (_t4048) {
        Token *_t4026 = advance(p);
        (void)_t4026;
        Expr *_t4027 = Expr_new(ExprData_Continue(), t_line, t_col, &p->path);
        (void)_t4027;
        ;
        ;
        ;
        return _t4027;
    }
    ;
    Str *_t4049 = Str_lit("Str", 3ULL);
    (void)_t4049;
    U64 _t4050; { U64 *_hp = (U64 *)Str_size(); _t4050 = *_hp; free(_hp); }
    (void)_t4050;
    U64 _t4051 = 8;
    (void)_t4051;
    Array *_va74 = Array_new(_t4049, &(U64){_t4050}, &(U64){_t4051});
    (void)_va74;
    Str_delete(_t4049, &(Bool){1});
    ;
    ;
    U64 _t4052 = 0;
    (void)_t4052;
    Str *_t4053 = Str_clone(&p->path);
    (void)_t4053;
    Array_set(_va74, &(U64){_t4052}, _t4053);
    ;
    U64 _t4054 = 1;
    (void)_t4054;
    Str *_t4055 = Str_lit(":", 1ULL);
    (void)_t4055;
    Array_set(_va74, &(U64){_t4054}, _t4055);
    ;
    U64 _t4056 = 2;
    (void)_t4056;
    Str *_t4057 = U32_to_str(&(U32){t_line});
    (void)_t4057;
    ;
    Array_set(_va74, &(U64){_t4056}, _t4057);
    ;
    U64 _t4058 = 3;
    (void)_t4058;
    Str *_t4059 = Str_lit(":", 1ULL);
    (void)_t4059;
    Array_set(_va74, &(U64){_t4058}, _t4059);
    ;
    U64 _t4060 = 4;
    (void)_t4060;
    Str *_t4061 = U32_to_str(&(U32){t_col});
    (void)_t4061;
    ;
    Array_set(_va74, &(U64){_t4060}, _t4061);
    ;
    U64 _t4062 = 5;
    (void)_t4062;
    Str *_t4063 = Str_lit(": expected statement, found '", 29ULL);
    (void)_t4063;
    Array_set(_va74, &(U64){_t4062}, _t4063);
    ;
    U64 _t4064 = 6;
    (void)_t4064;
    Str *_t4065 = Str_clone(&t->text);
    (void)_t4065;
    Array_set(_va74, &(U64){_t4064}, _t4065);
    ;
    U64 _t4066 = 7;
    (void)_t4066;
    Str *_t4067 = Str_lit("'", 1ULL);
    (void)_t4067;
    Array_set(_va74, &(U64){_t4066}, _t4067);
    ;
    Str *_t4068 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:958:11", 64ULL);
    (void)_t4068;
    panic(_t4068, _va74);
    Str_delete(_t4068, &(Bool){1});
    U32 _t4069 = 0;
    (void)_t4069;
    U32 _t4070 = 0;
    (void)_t4070;
    Expr *_t4071 = Expr_new(ExprData_Body(), _t4069, _t4070, &p->path);
    (void)_t4071;
    ;
    ;
    return _t4071;
}

Expr * parse(Vec * tokens, Str * path, Str * mode_out) {
    (void)tokens;
    (void)path;
    (void)mode_out;
    Str *_t4091 = Str_lit("Expr", 4ULL);
    (void)_t4091;
    U64 _t4092; { U64 *_hp = (U64 *)Expr_size(); _t4092 = *_hp; free(_hp); }
    (void)_t4092;
    I64 _t4093 = 0;
    (void)_t4093;
    Parser *p = malloc(sizeof(Parser));
    { Vec *_ca = Vec_clone(tokens); p->tokens = *_ca; free(_ca); }
    p->pos = _t4093;
    { Str *_ca = Str_clone(path); p->path = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t4091, &(U64){_t4092}); p->fn_sig_decls = *_ca; free(_ca); }
    (void)p;
    Str_delete(_t4091, &(Bool){1});
    ;
    ;
    Bool _t4094 = check(p, TokenType_KwMode());
    (void)_t4094;
    if (_t4094) {
        Token *_t4076 = advance(p);
        (void)_t4076;
        Bool _t4077 = check(p, TokenType_Ident());
        (void)_t4077;
        Bool _t4078 = check(p, TokenType_KwTest());
        (void)_t4078;
        Bool _t4079 = Bool_or(_t4077, _t4078);
        (void)_t4079;
        ;
        ;
        if (_t4079) {
            Str *_t4072 = Str_clone(&peek(p)->text);
            (void)_t4072;
            U64 _t4073; { U64 *_hp = (U64 *)Str_size(); _t4073 = *_hp; free(_hp); }
            (void)_t4073;
            swap(mode_out, _t4072, _t4073);
            Str_delete(_t4072, &(Bool){1});
            ;
            Token *_t4074 = advance(p);
            (void)_t4074;
        } else {
            Token *_t4075 = expect_token(p, TokenType_Ident());
            (void)_t4075;
        }
        ;
    }
    ;
    U32 _t4095 = 1;
    (void)_t4095;
    U32 _t4096 = 1;
    (void)_t4096;
    Expr *root = Expr_new(ExprData_Body(), _t4095, _t4096, &p->path);
    (void)root;
    ;
    ;
    while (1) {
        Bool _t4081 = check(p, TokenType_Eof());
        (void)_t4081;
        Bool _wcond4080 = Bool_not(_t4081);
        (void)_wcond4080;
        ;
        if (_wcond4080) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t4082 = parse_statement(p);
        (void)_t4082;
        Expr_add_child(root, _t4082);
    }
    {
        U64 _t4089 = 0;
        (void)_t4089;
        U64 _t4090; { U64 *_hp = (U64 *)Vec_len(&p->fn_sig_decls); _t4090 = *_hp; free(_hp); }
        (void)_t4090;
        Range *_fc4083 = Range_new(_t4089, _t4090);
        (void)_fc4083;
        ;
        ;
        U64 _fi4083 = 0;
        (void)_fi4083;
        while (1) {
            U64 _t4085; { U64 *_hp = (U64 *)Range_len(_fc4083); _t4085 = *_hp; free(_hp); }
            (void)_t4085;
            Bool _wcond4084; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi4083}, &(U64){_t4085}); _wcond4084 = *_hp; free(_hp); }
            (void)_wcond4084;
            ;
            if (_wcond4084) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc4083, _fi4083);
            (void)i;
            U64 _t4086 = 1;
            (void)_t4086;
            U64 _t4087 = U64_add(_fi4083, _t4086);
            (void)_t4087;
            ;
            _fi4083 = _t4087;
            ;
            Expr *d = Vec_get(&p->fn_sig_decls, i);
            (void)d;
            Expr *_t4088 = Expr_clone(d);
            (void)_t4088;
            U64_delete(i, &(Bool){1});
            Expr_add_child(root, _t4088);
        }
        Range_delete(_fc4083, &(Bool){1});
        ;
    }
    Parser_delete(p, &(Bool){1});
    return root;
}

