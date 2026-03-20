#include "til_parser.h"

Parser * Parser_clone(Parser * self) {
    (void)self;
    U64 _t2950 = U64_clone(&self->pos);
    (void)_t2950;
    Parser *_t2951 = malloc(sizeof(Parser));
    { Vec *_ca = Vec_clone(&self->tokens); _t2951->tokens = *_ca; free(_ca); }
    _t2951->pos = _t2950;
    { Str *_ca = Str_clone(&self->path); _t2951->path = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->fn_sig_decls); _t2951->fn_sig_decls = *_ca; free(_ca); }
    (void)_t2951;
    ;
    return _t2951;
}

void Parser_delete(Parser * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t2952 = 0;
    (void)_t2952;
    Vec_delete(&self->tokens, &(Bool){_t2952});
    ;
    Bool _t2953 = 0;
    (void)_t2953;
    U64_delete(&self->pos, &(Bool){_t2953});
    ;
    Bool _t2954 = 0;
    (void)_t2954;
    Str_delete(&self->path, &(Bool){_t2954});
    ;
    Bool _t2955 = 0;
    (void)_t2955;
    Vec_delete(&self->fn_sig_decls, &(Bool){_t2955});
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
    I64 _t2957 = U64_to_i64(p->pos);
    (void)_t2957;
    U64 *_t2958 = malloc(sizeof(U64)); *_t2958 = I64_to_u64(_t2957);
    (void)_t2958;
    ;
    Token *t = Vec_get(&p->tokens, _t2958);
    (void)t;
    U64_delete(_t2958, &(Bool){1});
    return t;
}

Token * advance(Parser * p) {
    (void)p;
    I64 _t2961 = U64_to_i64(p->pos);
    (void)_t2961;
    U64 *_t2962 = malloc(sizeof(U64)); *_t2962 = I64_to_u64(_t2961);
    (void)_t2962;
    ;
    Token *t = Vec_get(&p->tokens, _t2962);
    (void)t;
    Bool _t2963; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Eof()); _t2963 = *_hp; free(_hp); }
    (void)_t2963;
    Bool _t2964 = Bool_not(_t2963);
    (void)_t2964;
    ;
    if (_t2964) {
        U64 _t2959 = 1;
        (void)_t2959;
        U64 _t2960 = U64_add(p->pos, _t2959);
        (void)_t2960;
        ;
        p->pos = _t2960;
        ;
    }
    ;
    U64_delete(_t2962, &(Bool){1});
    return t;
}

Bool check(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Bool _t2965; { Bool *_hp = (Bool *)TokenType_eq(&peek(p)->type, type); _t2965 = *_hp; free(_hp); }
    (void)_t2965;
    return _t2965;
}

Token * expect_token(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Token *t = peek(p);
    (void)t;
    Bool _t2990; { Bool *_hp = (Bool *)TokenType_eq(&t->type, type); _t2990 = *_hp; free(_hp); }
    (void)_t2990;
    Bool _t2991 = Bool_not(_t2990);
    (void)_t2991;
    ;
    if (_t2991) {
        Str *_t2966 = Str_lit("Str", 3ULL);
        (void)_t2966;
        U64 _t2967; { U64 *_hp = (U64 *)Str_size(); _t2967 = *_hp; free(_hp); }
        (void)_t2967;
        U64 _t2968 = 10;
        (void)_t2968;
        Array *_va54 = Array_new(_t2966, &(U64){_t2967}, &(U64){_t2968});
        (void)_va54;
        Str_delete(_t2966, &(Bool){1});
        ;
        ;
        U64 _t2969 = 0;
        (void)_t2969;
        Str *_t2970 = Str_clone(&p->path);
        (void)_t2970;
        Array_set(_va54, &(U64){_t2969}, _t2970);
        ;
        U64 _t2971 = 1;
        (void)_t2971;
        Str *_t2972 = Str_lit(":", 1ULL);
        (void)_t2972;
        Array_set(_va54, &(U64){_t2971}, _t2972);
        ;
        U64 _t2973 = 2;
        (void)_t2973;
        Str *_t2974 = U32_to_str(&t->line);
        (void)_t2974;
        Array_set(_va54, &(U64){_t2973}, _t2974);
        ;
        U64 _t2975 = 3;
        (void)_t2975;
        Str *_t2976 = Str_lit(":", 1ULL);
        (void)_t2976;
        Array_set(_va54, &(U64){_t2975}, _t2976);
        ;
        U64 _t2977 = 4;
        (void)_t2977;
        Str *_t2978 = U32_to_str(&t->col);
        (void)_t2978;
        Array_set(_va54, &(U64){_t2977}, _t2978);
        ;
        U64 _t2979 = 5;
        (void)_t2979;
        Str *_t2980 = Str_lit(": expected '", 12ULL);
        (void)_t2980;
        Array_set(_va54, &(U64){_t2979}, _t2980);
        ;
        U64 _t2981 = 6;
        (void)_t2981;
        Str *_t2982 = tok_name(type);
        (void)_t2982;
        Array_set(_va54, &(U64){_t2981}, _t2982);
        ;
        U64 _t2983 = 7;
        (void)_t2983;
        Str *_t2984 = Str_lit("', found '", 10ULL);
        (void)_t2984;
        Array_set(_va54, &(U64){_t2983}, _t2984);
        ;
        U64 _t2985 = 8;
        (void)_t2985;
        Str *_t2986 = Str_clone(&t->text);
        (void)_t2986;
        Array_set(_va54, &(U64){_t2985}, _t2986);
        ;
        U64 _t2987 = 9;
        (void)_t2987;
        Str *_t2988 = Str_lit("'", 1ULL);
        (void)_t2988;
        Array_set(_va54, &(U64){_t2987}, _t2988);
        ;
        Str *_t2989 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:34:15", 63ULL);
        (void)_t2989;
        panic(_t2989, _va54);
        Str_delete(_t2989, &(Bool){1});
    }
    ;
    Token *_t2992 = advance(p);
    (void)_t2992;
    return _t2992;
}

Str * expect_text(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Token *t = peek(p);
    (void)t;
    Bool _t3017; { Bool *_hp = (Bool *)TokenType_eq(&t->type, type); _t3017 = *_hp; free(_hp); }
    (void)_t3017;
    Bool _t3018 = Bool_not(_t3017);
    (void)_t3018;
    ;
    if (_t3018) {
        Str *_t2993 = Str_lit("Str", 3ULL);
        (void)_t2993;
        U64 _t2994; { U64 *_hp = (U64 *)Str_size(); _t2994 = *_hp; free(_hp); }
        (void)_t2994;
        U64 _t2995 = 10;
        (void)_t2995;
        Array *_va55 = Array_new(_t2993, &(U64){_t2994}, &(U64){_t2995});
        (void)_va55;
        Str_delete(_t2993, &(Bool){1});
        ;
        ;
        U64 _t2996 = 0;
        (void)_t2996;
        Str *_t2997 = Str_clone(&p->path);
        (void)_t2997;
        Array_set(_va55, &(U64){_t2996}, _t2997);
        ;
        U64 _t2998 = 1;
        (void)_t2998;
        Str *_t2999 = Str_lit(":", 1ULL);
        (void)_t2999;
        Array_set(_va55, &(U64){_t2998}, _t2999);
        ;
        U64 _t3000 = 2;
        (void)_t3000;
        Str *_t3001 = U32_to_str(&t->line);
        (void)_t3001;
        Array_set(_va55, &(U64){_t3000}, _t3001);
        ;
        U64 _t3002 = 3;
        (void)_t3002;
        Str *_t3003 = Str_lit(":", 1ULL);
        (void)_t3003;
        Array_set(_va55, &(U64){_t3002}, _t3003);
        ;
        U64 _t3004 = 4;
        (void)_t3004;
        Str *_t3005 = U32_to_str(&t->col);
        (void)_t3005;
        Array_set(_va55, &(U64){_t3004}, _t3005);
        ;
        U64 _t3006 = 5;
        (void)_t3006;
        Str *_t3007 = Str_lit(": expected '", 12ULL);
        (void)_t3007;
        Array_set(_va55, &(U64){_t3006}, _t3007);
        ;
        U64 _t3008 = 6;
        (void)_t3008;
        Str *_t3009 = tok_name(type);
        (void)_t3009;
        Array_set(_va55, &(U64){_t3008}, _t3009);
        ;
        U64 _t3010 = 7;
        (void)_t3010;
        Str *_t3011 = Str_lit("', found '", 10ULL);
        (void)_t3011;
        Array_set(_va55, &(U64){_t3010}, _t3011);
        ;
        U64 _t3012 = 8;
        (void)_t3012;
        Str *_t3013 = Str_clone(&t->text);
        (void)_t3013;
        Array_set(_va55, &(U64){_t3012}, _t3013);
        ;
        U64 _t3014 = 9;
        (void)_t3014;
        Str *_t3015 = Str_lit("'", 1ULL);
        (void)_t3015;
        Array_set(_va55, &(U64){_t3014}, _t3015);
        ;
        Str *_t3016 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:44:15", 63ULL);
        (void)_t3016;
        panic(_t3016, _va55);
        Str_delete(_t3016, &(Bool){1});
    }
    ;
    Str *text = Str_clone(&t->text);
    (void)text;
    Token *_t3019 = advance(p);
    (void)_t3019;
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
    Bool _t3053 = check(p, TokenType_LParen());
    (void)_t3053;
    Bool _t3054 = Bool_not(_t3053);
    (void)_t3054;
    ;
    if (_t3054) {
        Str *_t3020 = Str_lit("", 0ULL);
        (void)_t3020;
        ;
        return _t3020;
    }
    ;
    Token *_t3055 = advance(p);
    (void)_t3055;
    Str *_t3056 = Str_lit("Str", 3ULL);
    (void)_t3056;
    U64 _t3057; { U64 *_hp = (U64 *)Str_size(); _t3057 = *_hp; free(_hp); }
    (void)_t3057;
    Vec *ptypes = Vec_new(_t3056, &(U64){_t3057});
    (void)ptypes;
    Str_delete(_t3056, &(Bool){1});
    ;
    Str *_t3058 = Str_lit("Bool", 4ULL);
    (void)_t3058;
    U64 _t3059; { U64 *_hp = (U64 *)Bool_size(); _t3059 = *_hp; free(_hp); }
    (void)_t3059;
    Vec *pmuts = Vec_new(_t3058, &(U64){_t3059});
    (void)pmuts;
    Str_delete(_t3058, &(Bool){1});
    ;
    while (1) {
        Bool _t3025 = check(p, TokenType_RParen());
        (void)_t3025;
        Bool _t3026 = check(p, TokenType_Eof());
        (void)_t3026;
        Bool _t3027 = Bool_not(_t3025);
        (void)_t3027;
        ;
        Bool _t3028 = Bool_not(_t3026);
        (void)_t3028;
        ;
        Bool _wcond3021 = Bool_and(_t3027, _t3028);
        (void)_wcond3021;
        ;
        ;
        if (_wcond3021) {
        } else {
            ;
            break;
        }
        ;
        Bool is_mut = 0;
        (void)is_mut;
        Bool _t3029 = check(p, TokenType_KwMut());
        (void)_t3029;
        if (_t3029) {
            Token *_t3022 = advance(p);
            (void)_t3022;
            Bool _t3023 = 1;
            (void)_t3023;
            is_mut = _t3023;
            ;
        }
        ;
        Str *ptype = expect_text(p, TokenType_Ident());
        (void)ptype;
        Vec_push(ptypes, ptype);
        Vec_push(pmuts, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = is_mut; _oa; }));
        Bool _t3030 = check(p, TokenType_Comma());
        (void)_t3030;
        if (_t3030) {
            Token *_t3024 = advance(p);
            (void)_t3024;
        }
        ;
    }
    Token *_t3060 = expect_token(p, TokenType_RParen());
    (void)_t3060;
    Str *return_type = Str_lit("", 0ULL);
    (void)return_type;
    Bool _t3061 = check(p, TokenType_KwReturns());
    (void)_t3061;
    if (_t3061) {
        Token *_t3031 = advance(p);
        (void)_t3031;
        return_type = expect_text(p, TokenType_Ident());
    }
    ;
    Str *name = Str_lit("_Fn", 3ULL);
    (void)name;
    {
        U64 _t3039 = 0;
        (void)_t3039;
        U64 _t3040; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3040 = *_hp; free(_hp); }
        (void)_t3040;
        Range *_fc3032 = Range_new(_t3039, _t3040);
        (void)_fc3032;
        ;
        ;
        U64 _fi3032 = 0;
        (void)_fi3032;
        while (1) {
            U64 _t3035; { U64 *_hp = (U64 *)Range_len(_fc3032); _t3035 = *_hp; free(_hp); }
            (void)_t3035;
            Bool _wcond3033; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3032}, &(U64){_t3035}); _wcond3033 = *_hp; free(_hp); }
            (void)_wcond3033;
            ;
            if (_wcond3033) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc3032, _fi3032);
            (void)i;
            U64 _t3036 = 1;
            (void)_t3036;
            U64 _t3037 = U64_add(_fi3032, _t3036);
            (void)_t3037;
            ;
            _fi3032 = _t3037;
            ;
            Str *_t3038 = Str_lit("_", 1ULL);
            (void)_t3038;
            name = Str_concat(name, _t3038);
            Str_delete(_t3038, &(Bool){1});
            Bool *m = Vec_get(pmuts, i);
            (void)m;
            if (DEREF(m)) {
                Str *_t3034 = Str_lit("mut_", 4ULL);
                (void)_t3034;
                name = Str_concat(name, _t3034);
                Str_delete(_t3034, &(Bool){1});
            }
            Str *t = Vec_get(ptypes, i);
            (void)t;
            name = Str_concat(name, t);
            U64_delete(i, &(Bool){1});
        }
        Range_delete(_fc3032, &(Bool){1});
        ;
    }
    U64 _t3062; { U64 *_hp = (U64 *)Str_len(return_type); _t3062 = *_hp; free(_hp); }
    (void)_t3062;
    U64 _t3063 = 0;
    (void)_t3063;
    Bool _t3064; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3062}, &(U64){_t3063}); _t3064 = *_hp; free(_hp); }
    (void)_t3064;
    ;
    ;
    if (_t3064) {
        Str *_t3041 = Str_lit("_ret_", 5ULL);
        (void)_t3041;
        name = Str_concat(name, _t3041);
        Str_delete(_t3041, &(Bool){1});
        name = Str_concat(name, return_type);
    }
    ;
    Str *_t3065 = Str_lit("Param", 5ULL);
    (void)_t3065;
    U64 _t3066; { U64 *_hp = (U64 *)Param_size(); _t3066 = *_hp; free(_hp); }
    (void)_t3066;
    Str *_t3067 = Str_lit("Str", 3ULL);
    (void)_t3067;
    U64 _t3068; { U64 *_hp = (U64 *)Str_size(); _t3068 = *_hp; free(_hp); }
    (void)_t3068;
    Str *_t3069 = Str_lit("Expr", 4ULL);
    (void)_t3069;
    U64 _t3070; { U64 *_hp = (U64 *)Expr_size(); _t3070 = *_hp; free(_hp); }
    (void)_t3070;
    I64 _t3071 = 0;
    (void)_t3071;
    I64 _t3072 = 1;
    (void)_t3072;
    I64 _t3073 = I64_sub(_t3071, _t3072);
    (void)_t3073;
    ;
    ;
    I64 _t3074 = 0;
    (void)_t3074;
    I64 _t3075 = 1;
    (void)_t3075;
    I64 _t3076 = I64_sub(_t3074, _t3075);
    (void)_t3076;
    ;
    ;
    U32 _t3077 = 0;
    (void)_t3077;
    I32 _t3078 = I64_to_i32(_t3073);
    (void)_t3078;
    ;
    I32 _t3079 = I64_to_i32(_t3076);
    (void)_t3079;
    ;
    Bool _t3080 = 0;
    (void)_t3080;
    Bool _t3081 = 0;
    (void)_t3081;
    FunctionDef *fd = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(FuncType_Func()); fd->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3065, &(U64){_t3066}); fd->params = *_ca; free(_ca); }
    fd->nparam = _t3077;
    { Map *_ca = Map_new(_t3067, &(U64){_t3068}, _t3069, &(U64){_t3070}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3078;
    fd->kwargs_index = _t3079;
    fd->return_is_ref = _t3080;
    fd->return_is_shallow = _t3081;
    (void)fd;
    Str_delete(_t3065, &(Bool){1});
    ;
    Str_delete(_t3067, &(Bool){1});
    ;
    Str_delete(_t3069, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    U64 _t3082; { U64 *_hp = (U64 *)Str_len(return_type); _t3082 = *_hp; free(_hp); }
    (void)_t3082;
    U64 _t3083 = 0;
    (void)_t3083;
    Bool _t3084; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3082}, &(U64){_t3083}); _t3084 = *_hp; free(_hp); }
    (void)_t3084;
    ;
    ;
    if (_t3084) {
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
    Bool _t3085 = 0;
    (void)_t3085;
    fd->return_is_ref = _t3085;
    ;
    Bool _t3086 = 0;
    (void)_t3086;
    fd->return_is_shallow = _t3086;
    ;
    I64 _t3087 = 0;
    (void)_t3087;
    I64 _t3088 = 1;
    (void)_t3088;
    I64 _t3089 = I64_sub(_t3087, _t3088);
    (void)_t3089;
    ;
    ;
    I32 _t3090 = I64_to_i32(_t3089);
    (void)_t3090;
    ;
    fd->variadic_index = _t3090;
    ;
    I64 _t3091 = 0;
    (void)_t3091;
    I64 _t3092 = 1;
    (void)_t3092;
    I64 _t3093 = I64_sub(_t3091, _t3092);
    (void)_t3093;
    ;
    ;
    I32 _t3094 = I64_to_i32(_t3093);
    (void)_t3094;
    ;
    fd->kwargs_index = _t3094;
    ;
    {
        U64 _t3051 = 0;
        (void)_t3051;
        U64 _t3052; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3052 = *_hp; free(_hp); }
        (void)_t3052;
        Range *_fc3042 = Range_new(_t3051, _t3052);
        (void)_fc3042;
        ;
        ;
        U64 _fi3042 = 0;
        (void)_fi3042;
        while (1) {
            U64 _t3044; { U64 *_hp = (U64 *)Range_len(_fc3042); _t3044 = *_hp; free(_hp); }
            (void)_t3044;
            Bool _wcond3043; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3042}, &(U64){_t3044}); _wcond3043 = *_hp; free(_hp); }
            (void)_wcond3043;
            ;
            if (_wcond3043) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc3042, _fi3042);
            (void)i;
            U64 _t3045 = 1;
            (void)_t3045;
            U64 _t3046 = U64_add(_fi3042, _t3045);
            (void)_t3046;
            ;
            _fi3042 = _t3046;
            ;
            Str *t = Vec_get(ptypes, i);
            (void)t;
            Bool *m = Vec_get(pmuts, i);
            (void)m;
            Bool _t3047 = Bool_clone(m);
            (void)_t3047;
            Bool _t3048 = 0;
            (void)_t3048;
            Bool _t3049 = 0;
            (void)_t3049;
            Param *_t3050 = malloc(sizeof(Param));
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t3050->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(t); _t3050->ptype = *_ca; free(_ca); }
            _t3050->is_mut = _t3047;
            _t3050->is_own = _t3048;
            _t3050->is_shallow = _t3049;
            (void)_t3050;
            ;
            ;
            ;
            U64_delete(i, &(Bool){1});
            Vec_push(&fd->params, _t3050);
        }
        Range_delete(_fc3042, &(Bool){1});
        ;
    }
    Vec_delete(pmuts, &(Bool){1});
    Vec_delete(ptypes, &(Bool){1});
    U64 _t3095; { U64 *_hp = (U64 *)Vec_len(&fd->params); _t3095 = *_hp; free(_hp); }
    (void)_t3095;
    I64 _t3096 = U64_to_i64(_t3095);
    (void)_t3096;
    ;
    U32 _t3097 = I64_to_u32(_t3096);
    (void)_t3097;
    ;
    fd->nparam = _t3097;
    ;
    ExprData *_t3098 = ExprData_FuncDef(fd);
    (void)_t3098;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *sig = Expr_new(_t3098, line, col, &p->path);
    (void)sig;
    ExprData_delete(_t3098, &(Bool){1});
    Bool _t3099 = 0;
    (void)_t3099;
    Bool _t3100 = 0;
    (void)_t3100;
    Bool _t3101 = 0;
    (void)_t3101;
    Bool _t3102 = 0;
    (void)_t3102;
    I32 _t3103 = 0;
    (void)_t3103;
    I32 _t3104 = 0;
    (void)_t3104;
    Declaration *_t3105 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(name); _t3105->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t3105->explicit_type = *_ca; free(_ca); }
    _t3105->is_mut = _t3099;
    _t3105->is_namespace = _t3100;
    _t3105->is_ref = _t3101;
    _t3105->is_own = _t3102;
    _t3105->field_offset = _t3103;
    _t3105->field_size = _t3104;
    _t3105->field_struct_def = NULL;
    _t3105->fn_sig = NULL;
    (void)_t3105;
    ;
    ;
    ;
    ;
    ;
    ;
    ExprData *_t3106 = ExprData_Decl(_t3105);
    (void)_t3106;
    Declaration_delete(_t3105, &(Bool){1});
    Expr *decl = Expr_new(_t3106, line, col, &p->path);
    (void)decl;
    ExprData_delete(_t3106, &(Bool){1});
    Expr_add_child(decl, sig);
    Vec_push(&p->fn_sig_decls, decl);
    return name;
}

Expr * parse_block(Parser * p) {
    (void)p;
    U32 _t3113 = peek_line(p);
    (void)_t3113;
    U32 _t3114 = peek_col(p);
    (void)_t3114;
    Expr *body = Expr_new(ExprData_Body(), _t3113, _t3114, &p->path);
    (void)body;
    ;
    ;
    while (1) {
        Bool _t3108 = check(p, TokenType_RBrace());
        (void)_t3108;
        Bool _t3109 = check(p, TokenType_Eof());
        (void)_t3109;
        Bool _t3110 = Bool_not(_t3108);
        (void)_t3110;
        ;
        Bool _t3111 = Bool_not(_t3109);
        (void)_t3111;
        ;
        Bool _wcond3107 = Bool_and(_t3110, _t3111);
        (void)_wcond3107;
        ;
        ;
        if (_wcond3107) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t3112 = parse_statement(p);
        (void)_t3112;
        Expr_add_child(body, _t3112);
    }
    Token *_t3115 = expect_token(p, TokenType_RBrace());
    (void)_t3115;
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
        TokenType *_sw3116 = TokenType_clone(&kw->type);
        (void)_sw3116;
        Bool _t3128; { Bool *_hp = (Bool *)TokenType_eq(_sw3116, TokenType_KwFunc()); _t3128 = *_hp; free(_hp); }
        (void)_t3128;
        if (_t3128) {
            ft = FuncType_clone(FuncType_Func());
        } else {
            Bool _t3127; { Bool *_hp = (Bool *)TokenType_eq(_sw3116, TokenType_KwProc()); _t3127 = *_hp; free(_hp); }
            (void)_t3127;
            if (_t3127) {
                ft = FuncType_clone(FuncType_Proc());
            } else {
                Bool _t3126; { Bool *_hp = (Bool *)TokenType_eq(_sw3116, TokenType_KwTest()); _t3126 = *_hp; free(_hp); }
                (void)_t3126;
                if (_t3126) {
                    ft = FuncType_clone(FuncType_Test());
                } else {
                    Bool _t3125; { Bool *_hp = (Bool *)TokenType_eq(_sw3116, TokenType_KwMacro()); _t3125 = *_hp; free(_hp); }
                    (void)_t3125;
                    if (_t3125) {
                        ft = FuncType_clone(FuncType_Macro());
                    } else {
                        Bool _t3124; { Bool *_hp = (Bool *)TokenType_eq(_sw3116, TokenType_KwExtFunc()); _t3124 = *_hp; free(_hp); }
                        (void)_t3124;
                        if (_t3124) {
                            ft = FuncType_clone(FuncType_ExtFunc());
                        } else {
                            Bool _t3123; { Bool *_hp = (Bool *)TokenType_eq(_sw3116, TokenType_KwExtProc()); _t3123 = *_hp; free(_hp); }
                            (void)_t3123;
                            if (_t3123) {
                                ft = FuncType_clone(FuncType_ExtProc());
                            } else {
                                Str *_t3117 = Str_lit("Str", 3ULL);
                                (void)_t3117;
                                U64 _t3118; { U64 *_hp = (U64 *)Str_size(); _t3118 = *_hp; free(_hp); }
                                (void)_t3118;
                                U64 _t3119 = 1;
                                (void)_t3119;
                                Array *_va56 = Array_new(_t3117, &(U64){_t3118}, &(U64){_t3119});
                                (void)_va56;
                                Str_delete(_t3117, &(Bool){1});
                                ;
                                ;
                                U64 _t3120 = 0;
                                (void)_t3120;
                                Str *_t3121 = Str_lit("expected function keyword", 25ULL);
                                (void)_t3121;
                                Array_set(_va56, &(U64){_t3120}, _t3121);
                                ;
                                Str *_t3122 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:150:17", 64ULL);
                                (void)_t3122;
                                panic(_t3122, _va56);
                                Str_delete(_t3122, &(Bool){1});
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
        TokenType_delete(_sw3116, &(Bool){1});
        ;
    }
    Token *_t3306 = expect_token(p, TokenType_LParen());
    (void)_t3306;
    Str *_t3307 = Str_lit("Param", 5ULL);
    (void)_t3307;
    U64 _t3308; { U64 *_hp = (U64 *)Param_size(); _t3308 = *_hp; free(_hp); }
    (void)_t3308;
    Str *_t3309 = Str_lit("Str", 3ULL);
    (void)_t3309;
    U64 _t3310; { U64 *_hp = (U64 *)Str_size(); _t3310 = *_hp; free(_hp); }
    (void)_t3310;
    Str *_t3311 = Str_lit("Expr", 4ULL);
    (void)_t3311;
    U64 _t3312; { U64 *_hp = (U64 *)Expr_size(); _t3312 = *_hp; free(_hp); }
    (void)_t3312;
    I64 _t3313 = 0;
    (void)_t3313;
    I64 _t3314 = 1;
    (void)_t3314;
    I64 _t3315 = I64_sub(_t3313, _t3314);
    (void)_t3315;
    ;
    ;
    I64 _t3316 = 0;
    (void)_t3316;
    I64 _t3317 = 1;
    (void)_t3317;
    I64 _t3318 = I64_sub(_t3316, _t3317);
    (void)_t3318;
    ;
    ;
    U32 _t3319 = 0;
    (void)_t3319;
    I32 _t3320 = I64_to_i32(_t3315);
    (void)_t3320;
    ;
    I32 _t3321 = I64_to_i32(_t3318);
    (void)_t3321;
    ;
    Bool _t3322 = 0;
    (void)_t3322;
    Bool _t3323 = 0;
    (void)_t3323;
    FunctionDef *fd = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(FuncType_Func()); fd->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3307, &(U64){_t3308}); fd->params = *_ca; free(_ca); }
    fd->nparam = _t3319;
    { Map *_ca = Map_new(_t3309, &(U64){_t3310}, _t3311, &(U64){_t3312}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3320;
    fd->kwargs_index = _t3321;
    fd->return_is_ref = _t3322;
    fd->return_is_shallow = _t3323;
    (void)fd;
    Str_delete(_t3307, &(Bool){1});
    ;
    Str_delete(_t3309, &(Bool){1});
    ;
    Str_delete(_t3311, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    FuncType_delete(&fd->func_type, &(Bool){0});
    { FuncType *_fa = FuncType_clone(ft); fd->func_type = *_fa; free(_fa); }
    while (1) {
        Bool _t3246 = check(p, TokenType_RParen());
        (void)_t3246;
        Bool _t3247 = check(p, TokenType_Eof());
        (void)_t3247;
        Bool _t3248 = Bool_not(_t3246);
        (void)_t3248;
        ;
        Bool _t3249 = Bool_not(_t3247);
        (void)_t3249;
        ;
        Bool _wcond3129 = Bool_and(_t3248, _t3249);
        (void)_wcond3129;
        ;
        ;
        if (_wcond3129) {
        } else {
            ;
            break;
        }
        ;
        Bool is_shallow = 0;
        (void)is_shallow;
        Bool _t3250 = check(p, TokenType_KwShallow());
        (void)_t3250;
        if (_t3250) {
            Token *_t3130 = advance(p);
            (void)_t3130;
            Bool _t3131 = 1;
            (void)_t3131;
            is_shallow = _t3131;
            ;
        }
        ;
        Bool is_own = 0;
        (void)is_own;
        Bool _t3251 = check(p, TokenType_KwOwn());
        (void)_t3251;
        if (_t3251) {
            Token *_t3132 = advance(p);
            (void)_t3132;
            Bool _t3133 = 1;
            (void)_t3133;
            is_own = _t3133;
            ;
        }
        ;
        Bool is_mut = 0;
        (void)is_mut;
        Bool _t3252 = check(p, TokenType_KwMut());
        (void)_t3252;
        if (_t3252) {
            Token *_t3134 = advance(p);
            (void)_t3134;
            Bool _t3135 = 1;
            (void)_t3135;
            is_mut = _t3135;
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
        Bool _t3253 = check(p, TokenType_Colon());
        (void)_t3253;
        Bool _t3254 = Bool_not(_t3253);
        (void)_t3254;
        ;
        if (_t3254) {
            tp = Str_clone(pname);
            nm = Str_lit("", 0ULL);
        } else {
            Token *_t3229 = expect_token(p, TokenType_Colon());
            (void)_t3229;
            Bool _t3230 = check(p, TokenType_DotDotDot());
            (void)_t3230;
            if (_t3230) {
                Token *_t3166 = advance(p);
                (void)_t3166;
                Bool _t3167 = Bool_or(is_own, is_mut);
                (void)_t3167;
                Bool _t3168 = Bool_or(_t3167, is_shallow);
                (void)_t3168;
                ;
                if (_t3168) {
                    Str *_t3136 = Str_lit("Str", 3ULL);
                    (void)_t3136;
                    U64 _t3137; { U64 *_hp = (U64 *)Str_size(); _t3137 = *_hp; free(_hp); }
                    (void)_t3137;
                    U64 _t3138 = 6;
                    (void)_t3138;
                    Array *_va57 = Array_new(_t3136, &(U64){_t3137}, &(U64){_t3138});
                    (void)_va57;
                    Str_delete(_t3136, &(Bool){1});
                    ;
                    ;
                    U64 _t3139 = 0;
                    (void)_t3139;
                    Str *_t3140 = Str_clone(&p->path);
                    (void)_t3140;
                    Array_set(_va57, &(U64){_t3139}, _t3140);
                    ;
                    U64 _t3141 = 1;
                    (void)_t3141;
                    Str *_t3142 = Str_lit(":", 1ULL);
                    (void)_t3142;
                    Array_set(_va57, &(U64){_t3141}, _t3142);
                    ;
                    U32 _t3143 = peek_line(p);
                    (void)_t3143;
                    U64 _t3144 = 2;
                    (void)_t3144;
                    Str *_t3145 = U32_to_str(&(U32){_t3143});
                    (void)_t3145;
                    ;
                    Array_set(_va57, &(U64){_t3144}, _t3145);
                    ;
                    U64 _t3146 = 3;
                    (void)_t3146;
                    Str *_t3147 = Str_lit(":", 1ULL);
                    (void)_t3147;
                    Array_set(_va57, &(U64){_t3146}, _t3147);
                    ;
                    U32 _t3148 = peek_col(p);
                    (void)_t3148;
                    U64 _t3149 = 4;
                    (void)_t3149;
                    Str *_t3150 = U32_to_str(&(U32){_t3148});
                    (void)_t3150;
                    ;
                    Array_set(_va57, &(U64){_t3149}, _t3150);
                    ;
                    U64 _t3151 = 5;
                    (void)_t3151;
                    Str *_t3152 = Str_lit(": kwargs parameter cannot be own/mut/shallow", 44ULL);
                    (void)_t3152;
                    Array_set(_va57, &(U64){_t3151}, _t3152);
                    ;
                    Str *_t3153 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:180:27", 64ULL);
                    (void)_t3153;
                    panic(_t3153, _va57);
                    Str_delete(_t3153, &(Bool){1});
                }
                ;
                I64 _t3169 = 0;
                (void)_t3169;
                I64 _t3170 = 1;
                (void)_t3170;
                I64 _t3171 = I64_sub(_t3169, _t3170);
                (void)_t3171;
                ;
                ;
                I32 _t3172 = I64_to_i32(_t3171);
                (void)_t3172;
                ;
                Bool _t3173; { Bool *_hp = (Bool *)I32_neq(&fd->kwargs_index, &(I32){_t3172}); _t3173 = *_hp; free(_hp); }
                (void)_t3173;
                ;
                if (_t3173) {
                    Str *_t3154 = Str_lit("Str", 3ULL);
                    (void)_t3154;
                    U64 _t3155; { U64 *_hp = (U64 *)Str_size(); _t3155 = *_hp; free(_hp); }
                    (void)_t3155;
                    U64 _t3156 = 1;
                    (void)_t3156;
                    Array *_va58 = Array_new(_t3154, &(U64){_t3155}, &(U64){_t3156});
                    (void)_va58;
                    Str_delete(_t3154, &(Bool){1});
                    ;
                    ;
                    U64 _t3157 = 0;
                    (void)_t3157;
                    Str *_t3158 = Str_lit("only one kwargs parameter is allowed", 36ULL);
                    (void)_t3158;
                    Array_set(_va58, &(U64){_t3157}, _t3158);
                    ;
                    Str *_t3159 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:184:27", 64ULL);
                    (void)_t3159;
                    panic(_t3159, _va58);
                    Str_delete(_t3159, &(Bool){1});
                }
                ;
                I64 _t3174 = 0;
                (void)_t3174;
                I64 _t3175 = 1;
                (void)_t3175;
                I64 _t3176 = I64_sub(_t3174, _t3175);
                (void)_t3176;
                ;
                ;
                I32 _t3177 = I64_to_i32(_t3176);
                (void)_t3177;
                ;
                Bool _t3178; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3177}); _t3178 = *_hp; free(_hp); }
                (void)_t3178;
                ;
                if (_t3178) {
                    Str *_t3160 = Str_lit("Str", 3ULL);
                    (void)_t3160;
                    U64 _t3161; { U64 *_hp = (U64 *)Str_size(); _t3161 = *_hp; free(_hp); }
                    (void)_t3161;
                    U64 _t3162 = 1;
                    (void)_t3162;
                    Array *_va59 = Array_new(_t3160, &(U64){_t3161}, &(U64){_t3162});
                    (void)_va59;
                    Str_delete(_t3160, &(Bool){1});
                    ;
                    ;
                    U64 _t3163 = 0;
                    (void)_t3163;
                    Str *_t3164 = Str_lit("cannot combine variadic and kwargs in the same function", 55ULL);
                    (void)_t3164;
                    Array_set(_va59, &(U64){_t3163}, _t3164);
                    ;
                    Str *_t3165 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:187:27", 64ULL);
                    (void)_t3165;
                    panic(_t3165, _va59);
                    Str_delete(_t3165, &(Bool){1});
                }
                ;
                U64 _t3179; { U64 *_hp = (U64 *)Vec_len(&fd->params); _t3179 = *_hp; free(_hp); }
                (void)_t3179;
                I64 _t3180 = U64_to_i64(_t3179);
                (void)_t3180;
                ;
                I32 _t3181 = I64_to_i32(_t3180);
                (void)_t3181;
                ;
                fd->kwargs_index = _t3181;
                ;
                Bool _t3182 = 1;
                (void)_t3182;
                is_own = _t3182;
                ;
                nm = Str_clone(pname);
                tp = Str_lit("Map", 3ULL);
            } else {
                Bool _t3228 = check(p, TokenType_DotDot());
                (void)_t3228;
                if (_t3228) {
                    Token *_t3213 = advance(p);
                    (void)_t3213;
                    if (is_own) {
                        Str *_t3183 = Str_lit("Str", 3ULL);
                        (void)_t3183;
                        U64 _t3184; { U64 *_hp = (U64 *)Str_size(); _t3184 = *_hp; free(_hp); }
                        (void)_t3184;
                        U64 _t3185 = 1;
                        (void)_t3185;
                        Array *_va60 = Array_new(_t3183, &(U64){_t3184}, &(U64){_t3185});
                        (void)_va60;
                        Str_delete(_t3183, &(Bool){1});
                        ;
                        ;
                        U64 _t3186 = 0;
                        (void)_t3186;
                        Str *_t3187 = Str_lit("variadic param cannot be 'own'", 30ULL);
                        (void)_t3187;
                        Array_set(_va60, &(U64){_t3186}, _t3187);
                        ;
                        Str *_t3188 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:195:35", 64ULL);
                        (void)_t3188;
                        panic(_t3188, _va60);
                        Str_delete(_t3188, &(Bool){1});
                    }
                    if (is_mut) {
                        Str *_t3189 = Str_lit("Str", 3ULL);
                        (void)_t3189;
                        U64 _t3190; { U64 *_hp = (U64 *)Str_size(); _t3190 = *_hp; free(_hp); }
                        (void)_t3190;
                        U64 _t3191 = 1;
                        (void)_t3191;
                        Array *_va61 = Array_new(_t3189, &(U64){_t3190}, &(U64){_t3191});
                        (void)_va61;
                        Str_delete(_t3189, &(Bool){1});
                        ;
                        ;
                        U64 _t3192 = 0;
                        (void)_t3192;
                        Str *_t3193 = Str_lit("variadic param cannot be 'mut'", 30ULL);
                        (void)_t3193;
                        Array_set(_va61, &(U64){_t3192}, _t3193);
                        ;
                        Str *_t3194 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:196:35", 64ULL);
                        (void)_t3194;
                        panic(_t3194, _va61);
                        Str_delete(_t3194, &(Bool){1});
                    }
                    if (is_shallow) {
                        Str *_t3195 = Str_lit("Str", 3ULL);
                        (void)_t3195;
                        U64 _t3196; { U64 *_hp = (U64 *)Str_size(); _t3196 = *_hp; free(_hp); }
                        (void)_t3196;
                        U64 _t3197 = 1;
                        (void)_t3197;
                        Array *_va62 = Array_new(_t3195, &(U64){_t3196}, &(U64){_t3197});
                        (void)_va62;
                        Str_delete(_t3195, &(Bool){1});
                        ;
                        ;
                        U64 _t3198 = 0;
                        (void)_t3198;
                        Str *_t3199 = Str_lit("variadic param cannot be 'shallow'", 34ULL);
                        (void)_t3199;
                        Array_set(_va62, &(U64){_t3198}, _t3199);
                        ;
                        Str *_t3200 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:197:39", 64ULL);
                        (void)_t3200;
                        panic(_t3200, _va62);
                        Str_delete(_t3200, &(Bool){1});
                    }
                    I64 _t3214 = 0;
                    (void)_t3214;
                    I64 _t3215 = 1;
                    (void)_t3215;
                    I64 _t3216 = I64_sub(_t3214, _t3215);
                    (void)_t3216;
                    ;
                    ;
                    I32 _t3217 = I64_to_i32(_t3216);
                    (void)_t3217;
                    ;
                    Bool _t3218; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3217}); _t3218 = *_hp; free(_hp); }
                    (void)_t3218;
                    ;
                    if (_t3218) {
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
                        Str *_t3205 = Str_lit("only one variadic param allowed", 31ULL);
                        (void)_t3205;
                        Array_set(_va63, &(U64){_t3204}, _t3205);
                        ;
                        Str *_t3206 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:198:63", 64ULL);
                        (void)_t3206;
                        panic(_t3206, _va63);
                        Str_delete(_t3206, &(Bool){1});
                    }
                    ;
                    I64 _t3219 = 0;
                    (void)_t3219;
                    I64 _t3220 = 1;
                    (void)_t3220;
                    I64 _t3221 = I64_sub(_t3219, _t3220);
                    (void)_t3221;
                    ;
                    ;
                    I32 _t3222 = I64_to_i32(_t3221);
                    (void)_t3222;
                    ;
                    Bool _t3223; { Bool *_hp = (Bool *)I32_neq(&fd->kwargs_index, &(I32){_t3222}); _t3223 = *_hp; free(_hp); }
                    (void)_t3223;
                    ;
                    if (_t3223) {
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
                        Str *_t3211 = Str_lit("cannot combine variadic and kwargs in the same function", 55ULL);
                        (void)_t3211;
                        Array_set(_va64, &(U64){_t3210}, _t3211);
                        ;
                        Str *_t3212 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:200:27", 64ULL);
                        (void)_t3212;
                        panic(_t3212, _va64);
                        Str_delete(_t3212, &(Bool){1});
                    }
                    ;
                    U64 _t3224; { U64 *_hp = (U64 *)Vec_len(&fd->params); _t3224 = *_hp; free(_hp); }
                    (void)_t3224;
                    I64 _t3225 = U64_to_i64(_t3224);
                    (void)_t3225;
                    ;
                    I32 _t3226 = I64_to_i32(_t3225);
                    (void)_t3226;
                    ;
                    fd->variadic_index = _t3226;
                    ;
                    Bool _t3227 = 1;
                    (void)_t3227;
                    is_variadic = _t3227;
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
        Str *_t3255 = Str_lit("Fn", 2ULL);
        (void)_t3255;
        Bool _t3256; { Bool *_hp = (Bool *)Str_eq(tp, _t3255); _t3256 = *_hp; free(_hp); }
        (void)_t3256;
        Str_delete(_t3255, &(Bool){1});
        if (_t3256) {
            U32 _t3231 = peek_line(p);
            (void)_t3231;
            U32 _t3232 = peek_col(p);
            (void)_t3232;
            Str *syn_name = parse_fn_signature(p, _t3231, _t3232);
            (void)syn_name;
            ;
            ;
            U64 _t3233; { U64 *_hp = (U64 *)Str_len(syn_name); _t3233 = *_hp; free(_hp); }
            (void)_t3233;
            U64 _t3234 = 0;
            (void)_t3234;
            Bool _t3235; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3233}, &(U64){_t3234}); _t3235 = *_hp; free(_hp); }
            (void)_t3235;
            ;
            ;
            if (_t3235) {
                tp = Str_clone(syn_name);
            }
            ;
            Str_delete(syn_name, &(Bool){1});
        }
        ;
        Bool has_default = 0;
        (void)has_default;
        Bool _t3257 = check(p, TokenType_Eq());
        (void)_t3257;
        if (_t3257) {
            Token *_t3236 = advance(p);
            (void)_t3236;
            Expr *def_expr = parse_expression(p);
            (void)def_expr;
            Str *_t3237 = Str_clone(nm);
            (void)_t3237;
            Map_set(&fd->param_defaults, _t3237, def_expr);
            Bool _t3238 = 1;
            (void)_t3238;
            has_default = _t3238;
            ;
        }
        ;
        I64 _t3258 = 0;
        (void)_t3258;
        I64 _t3259 = 1;
        (void)_t3259;
        I64 _t3260 = I64_sub(_t3258, _t3259);
        (void)_t3260;
        ;
        ;
        I32 _t3261 = I64_to_i32(_t3260);
        (void)_t3261;
        ;
        Bool _t3262; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3261}); _t3262 = *_hp; free(_hp); }
        (void)_t3262;
        ;
        Bool _t3263 = Bool_not(is_variadic);
        (void)_t3263;
        ;
        Bool _t3264 = Bool_and(_t3262, _t3263);
        (void)_t3264;
        ;
        ;
        Bool _t3265 = Bool_not(has_default);
        (void)_t3265;
        ;
        Bool _t3266 = Bool_and(_t3264, _t3265);
        (void)_t3266;
        ;
        ;
        if (_t3266) {
            Str *_t3239 = Str_lit("Str", 3ULL);
            (void)_t3239;
            U64 _t3240; { U64 *_hp = (U64 *)Str_size(); _t3240 = *_hp; free(_hp); }
            (void)_t3240;
            U64 _t3241 = 1;
            (void)_t3241;
            Array *_va65 = Array_new(_t3239, &(U64){_t3240}, &(U64){_t3241});
            (void)_va65;
            Str_delete(_t3239, &(Bool){1});
            ;
            ;
            U64 _t3242 = 0;
            (void)_t3242;
            Str *_t3243 = Str_lit("positional param not allowed after variadic", 43ULL);
            (void)_t3243;
            Array_set(_va65, &(U64){_t3242}, _t3243);
            ;
            Str *_t3244 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:227:19", 64ULL);
            (void)_t3244;
            panic(_t3244, _va65);
            Str_delete(_t3244, &(Bool){1});
        }
        ;
        Bool _t3267 = Bool_clone(&(Bool){is_mut});
        (void)_t3267;
        ;
        Bool _t3268 = Bool_clone(&(Bool){is_own});
        (void)_t3268;
        ;
        Bool _t3269 = Bool_clone(&(Bool){is_shallow});
        (void)_t3269;
        ;
        Param *_t3270 = malloc(sizeof(Param));
        { Str *_ca = Str_clone(nm); _t3270->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(tp); _t3270->ptype = *_ca; free(_ca); }
        _t3270->is_mut = _t3267;
        _t3270->is_own = _t3268;
        _t3270->is_shallow = _t3269;
        (void)_t3270;
        ;
        ;
        ;
        Str_delete(nm, &(Bool){1});
        Str_delete(tp, &(Bool){1});
        Vec_push(&fd->params, _t3270);
        Bool _t3271 = check(p, TokenType_Comma());
        (void)_t3271;
        if (_t3271) {
            Token *_t3245 = advance(p);
            (void)_t3245;
        }
        ;
    }
    Token *_t3324 = expect_token(p, TokenType_RParen());
    (void)_t3324;
    Bool _t3325 = check(p, TokenType_KwReturns());
    (void)_t3325;
    if (_t3325) {
        Token *_t3277 = advance(p);
        (void)_t3277;
        Bool _t3278 = check(p, TokenType_KwRef());
        (void)_t3278;
        if (_t3278) {
            Token *_t3272 = advance(p);
            (void)_t3272;
            Bool _t3273 = 1;
            (void)_t3273;
            fd->return_is_ref = _t3273;
            ;
        } else {
            Bool _t3276 = check(p, TokenType_KwShallow());
            (void)_t3276;
            if (_t3276) {
                Token *_t3274 = advance(p);
                (void)_t3274;
                Bool _t3275 = 1;
                (void)_t3275;
                fd->return_is_shallow = _t3275;
                ;
            }
            ;
        }
        ;
        Str_delete(&fd->return_type, &(Bool){0});
        { Str *_fa = expect_text(p, TokenType_Ident()); fd->return_type = *_fa; free(_fa); }
    }
    ;
    U64 _t3326; { U64 *_hp = (U64 *)Vec_len(&fd->params); _t3326 = *_hp; free(_hp); }
    (void)_t3326;
    I64 _t3327 = U64_to_i64(_t3326);
    (void)_t3327;
    ;
    U32 _t3328 = I64_to_u32(_t3327);
    (void)_t3328;
    ;
    fd->nparam = _t3328;
    ;
    ExprData *_t3329 = ExprData_FuncDef(fd);
    (void)_t3329;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *def = Expr_new(_t3329, kw_line, kw_col, &p->path);
    (void)def;
    ExprData_delete(_t3329, &(Bool){1});
    Bool _t3330 = check(p, TokenType_LBrace());
    (void)_t3330;
    if (_t3330) {
        Token *_t3279 = expect_token(p, TokenType_LBrace());
        (void)_t3279;
        Expr *_t3280 = parse_block(p);
        (void)_t3280;
        Expr_add_child(def, _t3280);
    } else {
        Bool _t3301; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Func()); _t3301 = *_hp; free(_hp); }
        (void)_t3301;
        Bool _t3302; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Proc()); _t3302 = *_hp; free(_hp); }
        (void)_t3302;
        Bool _t3303 = Bool_not(_t3301);
        (void)_t3303;
        ;
        Bool _t3304 = Bool_not(_t3302);
        (void)_t3304;
        ;
        Bool _t3305 = Bool_and(_t3303, _t3304);
        (void)_t3305;
        ;
        ;
        if (_t3305) {
            Str *_t3281 = Str_lit("Str", 3ULL);
            (void)_t3281;
            U64 _t3282; { U64 *_hp = (U64 *)Str_size(); _t3282 = *_hp; free(_hp); }
            (void)_t3282;
            U64 _t3283 = 8;
            (void)_t3283;
            Array *_va66 = Array_new(_t3281, &(U64){_t3282}, &(U64){_t3283});
            (void)_va66;
            Str_delete(_t3281, &(Bool){1});
            ;
            ;
            U64 _t3284 = 0;
            (void)_t3284;
            Str *_t3285 = Str_clone(&p->path);
            (void)_t3285;
            Array_set(_va66, &(U64){_t3284}, _t3285);
            ;
            U64 _t3286 = 1;
            (void)_t3286;
            Str *_t3287 = Str_lit(":", 1ULL);
            (void)_t3287;
            Array_set(_va66, &(U64){_t3286}, _t3287);
            ;
            U64 _t3288 = 2;
            (void)_t3288;
            Str *_t3289 = U32_to_str(&(U32){kw_line});
            (void)_t3289;
            Array_set(_va66, &(U64){_t3288}, _t3289);
            ;
            U64 _t3290 = 3;
            (void)_t3290;
            Str *_t3291 = Str_lit(":", 1ULL);
            (void)_t3291;
            Array_set(_va66, &(U64){_t3290}, _t3291);
            ;
            U64 _t3292 = 4;
            (void)_t3292;
            Str *_t3293 = U32_to_str(&(U32){kw_col});
            (void)_t3293;
            Array_set(_va66, &(U64){_t3292}, _t3293);
            ;
            U64 _t3294 = 5;
            (void)_t3294;
            Str *_t3295 = Str_lit(": ", 2ULL);
            (void)_t3295;
            Array_set(_va66, &(U64){_t3294}, _t3295);
            ;
            U64 _t3296 = 6;
            (void)_t3296;
            Str *_t3297 = func_type_name(ft);
            (void)_t3297;
            Array_set(_va66, &(U64){_t3296}, _t3297);
            ;
            U64 _t3298 = 7;
            (void)_t3298;
            Str *_t3299 = Str_lit(" requires a body", 16ULL);
            (void)_t3299;
            Array_set(_va66, &(U64){_t3298}, _t3299);
            ;
            Str *_t3300 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:257:19", 64ULL);
            (void)_t3300;
            panic(_t3300, _va66);
            Str_delete(_t3300, &(Bool){1});
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
    Token *_t3344 = advance(p);
    (void)_t3344;
    Expr *def = Expr_new(ExprData_StructDef(), kw_line, kw_col, &p->path);
    (void)def;
    ;
    ;
    Bool _t3345 = Bool_clone(&(Bool){is_ext});
    (void)_t3345;
    ;
    def->is_ext = _t3345;
    ;
    Token *_t3346 = expect_token(p, TokenType_LBrace());
    (void)_t3346;
    U32 _t3347 = peek_line(p);
    (void)_t3347;
    U32 _t3348 = peek_col(p);
    (void)_t3348;
    Expr *body = Expr_new(ExprData_Body(), _t3347, _t3348, &p->path);
    (void)body;
    ;
    ;
    Bool in_namespace = 0;
    (void)in_namespace;
    while (1) {
        Bool _t3337 = check(p, TokenType_RBrace());
        (void)_t3337;
        Bool _t3338 = check(p, TokenType_Eof());
        (void)_t3338;
        Bool _t3339 = Bool_not(_t3337);
        (void)_t3339;
        ;
        Bool _t3340 = Bool_not(_t3338);
        (void)_t3340;
        ;
        Bool _wcond3331 = Bool_and(_t3339, _t3340);
        (void)_wcond3331;
        ;
        ;
        if (_wcond3331) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3341 = check(p, TokenType_KwNamespace());
        (void)_t3341;
        if (_t3341) {
            Token *_t3332 = advance(p);
            (void)_t3332;
            Token *_t3333 = expect_token(p, TokenType_Colon());
            (void)_t3333;
            Bool _t3334 = 1;
            (void)_t3334;
            in_namespace = _t3334;
            ;
            ;
            continue;
        }
        ;
        Expr *stmt = parse_statement(p);
        (void)stmt;
        Bool _t3342; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3342 = *_hp; free(_hp); }
        (void)_t3342;
        Bool _t3343 = Bool_and(in_namespace, _t3342);
        (void)_t3343;
        ;
        if (_t3343) {
            Bool _t3336; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3336 = *_hp; free(_hp); }
            (void)_t3336;
            if (_t3336) {
                Declaration *dd = ExprData_get_Decl(&stmt->data);
                (void)dd;
                Bool _t3335 = 1;
                (void)_t3335;
                dd->is_namespace = _t3335;
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
    Token *_t3349 = expect_token(p, TokenType_RBrace());
    (void)_t3349;
    Expr_add_child(def, body);
    return def;
}

Expr * parse_enum_def(Parser * p) {
    (void)p;
    U32 kw_line = peek_line(p);
    (void)kw_line;
    U32 kw_col = peek_col(p);
    (void)kw_col;
    Token *_t3373 = advance(p);
    (void)_t3373;
    Expr *def = Expr_new(ExprData_EnumDef(), kw_line, kw_col, &p->path);
    (void)def;
    ;
    ;
    Token *_t3374 = expect_token(p, TokenType_LBrace());
    (void)_t3374;
    U32 _t3375 = peek_line(p);
    (void)_t3375;
    U32 _t3376 = peek_col(p);
    (void)_t3376;
    Expr *body = Expr_new(ExprData_Body(), _t3375, _t3376, &p->path);
    (void)body;
    ;
    ;
    Bool in_namespace = 0;
    (void)in_namespace;
    while (1) {
        Bool _t3368 = check(p, TokenType_RBrace());
        (void)_t3368;
        Bool _t3369 = check(p, TokenType_Eof());
        (void)_t3369;
        Bool _t3370 = Bool_not(_t3368);
        (void)_t3370;
        ;
        Bool _t3371 = Bool_not(_t3369);
        (void)_t3371;
        ;
        Bool _wcond3350 = Bool_and(_t3370, _t3371);
        (void)_wcond3350;
        ;
        ;
        if (_wcond3350) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3372 = check(p, TokenType_KwNamespace());
        (void)_t3372;
        if (_t3372) {
            Token *_t3351 = advance(p);
            (void)_t3351;
            Token *_t3352 = expect_token(p, TokenType_Colon());
            (void)_t3352;
            Bool _t3353 = 1;
            (void)_t3353;
            in_namespace = _t3353;
            ;
            ;
            continue;
        }
        ;
        if (in_namespace) {
            Expr *stmt = parse_statement(p);
            (void)stmt;
            Bool _t3356; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3356 = *_hp; free(_hp); }
            (void)_t3356;
            if (_t3356) {
                Bool _t3355; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3355 = *_hp; free(_hp); }
                (void)_t3355;
                if (_t3355) {
                    Declaration *dd = ExprData_get_Decl(&stmt->data);
                    (void)dd;
                    Bool _t3354 = 1;
                    (void)_t3354;
                    dd->is_namespace = _t3354;
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
            Bool _t3359 = 0;
            (void)_t3359;
            Bool _t3360 = 0;
            (void)_t3360;
            Bool _t3361 = 0;
            (void)_t3361;
            Bool _t3362 = 0;
            (void)_t3362;
            I32 _t3363 = 0;
            (void)_t3363;
            I32 _t3364 = 0;
            (void)_t3364;
            Declaration *dd = malloc(sizeof(Declaration));
            { Str *_ca = Str_clone(vname); dd->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
            dd->is_mut = _t3359;
            dd->is_namespace = _t3360;
            dd->is_ref = _t3361;
            dd->is_own = _t3362;
            dd->field_offset = _t3363;
            dd->field_size = _t3364;
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
            Bool _t3365 = check(p, TokenType_Colon());
            (void)_t3365;
            if (_t3365) {
                Token *_t3357 = advance(p);
                (void)_t3357;
                Str_delete(&dd->explicit_type, &(Bool){0});
                { Str *_fa = expect_text(p, TokenType_Ident()); dd->explicit_type = *_fa; free(_fa); }
            }
            ;
            ExprData *_t3366 = ExprData_Decl(dd);
            (void)_t3366;
            Declaration_delete(dd, &(Bool){1});
            Expr *variant = Expr_new(_t3366, v_line, v_col, &p->path);
            (void)variant;
            ExprData_delete(_t3366, &(Bool){1});
            ;
            ;
            Expr_add_child(body, variant);
            Bool _t3367 = check(p, TokenType_Comma());
            (void)_t3367;
            if (_t3367) {
                Token *_t3358 = advance(p);
                (void)_t3358;
            }
            ;
        }
    }
    ;
    Token *_t3377 = expect_token(p, TokenType_RBrace());
    (void)_t3377;
    Expr_add_child(def, body);
    return def;
}

Expr * parse_call(Parser * p, Str * name, U32 call_line, U32 call_col) {
    (void)p;
    (void)name;
    (void)call_line;
    (void)call_col;
    Token *_t3408 = advance(p);
    (void)_t3408;
    Expr *call = Expr_new(ExprData_FCall(), call_line, call_col, &p->path);
    (void)call;
    Str *_t3409 = Str_clone(name);
    (void)_t3409;
    ExprData *_t3410 = ExprData_Ident(_t3409);
    (void)_t3410;
    Str_delete(_t3409, &(Bool){1});
    Expr *callee = Expr_new(_t3410, call_line, call_col, &p->path);
    (void)callee;
    ExprData_delete(_t3410, &(Bool){1});
    Expr_add_child(call, callee);
    while (1) {
        Bool _t3398 = check(p, TokenType_RParen());
        (void)_t3398;
        Bool _t3399 = check(p, TokenType_Eof());
        (void)_t3399;
        Bool _t3400 = Bool_not(_t3398);
        (void)_t3400;
        ;
        Bool _t3401 = Bool_not(_t3399);
        (void)_t3401;
        ;
        Bool _wcond3378 = Bool_and(_t3400, _t3401);
        (void)_wcond3378;
        ;
        ;
        if (_wcond3378) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3402 = check(p, TokenType_Ident());
        (void)_t3402;
        if (_t3402) {
            U64 _t3389 = 1;
            (void)_t3389;
            U64 _t3390 = U64_add(p->pos, _t3389);
            (void)_t3390;
            ;
            U64 _t3391; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3391 = *_hp; free(_hp); }
            (void)_t3391;
            Bool _t3392; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3390}, &(U64){_t3391}); _t3392 = *_hp; free(_hp); }
            (void)_t3392;
            ;
            ;
            if (_t3392) {
                U64 _t3384 = 1;
                (void)_t3384;
                U64 _t3385 = U64_add(p->pos, _t3384);
                (void)_t3385;
                ;
                I64 _t3386 = U64_to_i64(_t3385);
                (void)_t3386;
                ;
                U64 *_t3387 = malloc(sizeof(U64)); *_t3387 = I64_to_u64(_t3386);
                (void)_t3387;
                ;
                Token *next_tok = Vec_get(&p->tokens, _t3387);
                (void)next_tok;
                Bool _t3388; { Bool *_hp = (Bool *)TokenType_eq(&next_tok->type, TokenType_Eq()); _t3388 = *_hp; free(_hp); }
                (void)_t3388;
                U64_delete(_t3387, &(Bool){1});
                if (_t3388) {
                    U32 na_line = peek_line(p);
                    (void)na_line;
                    U32 na_col = peek_col(p);
                    (void)na_col;
                    Str *aname = expect_text(p, TokenType_Ident());
                    (void)aname;
                    Token *_t3380 = advance(p);
                    (void)_t3380;
                    ExprData *_t3381 = ExprData_NamedArg(aname);
                    (void)_t3381;
                    Str_delete(aname, &(Bool){1});
                    Expr *na = Expr_new(_t3381, na_line, na_col, &p->path);
                    (void)na;
                    ExprData_delete(_t3381, &(Bool){1});
                    ;
                    ;
                    Expr *_t3382 = parse_expression(p);
                    (void)_t3382;
                    Expr_add_child(na, _t3382);
                    Expr_add_child(call, na);
                    Bool _t3383 = check(p, TokenType_Comma());
                    (void)_t3383;
                    if (_t3383) {
                        Token *_t3379 = advance(p);
                        (void)_t3379;
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
        Bool _t3403 = check(p, TokenType_DotDot());
        (void)_t3403;
        if (_t3403) {
            Token *_t3393 = advance(p);
            (void)_t3393;
            Bool _t3394 = 1;
            (void)_t3394;
            is_splat = _t3394;
            ;
        }
        ;
        Bool is_own_arg = 0;
        (void)is_own_arg;
        Bool _t3404 = check(p, TokenType_KwOwn());
        (void)_t3404;
        if (_t3404) {
            Token *_t3395 = advance(p);
            (void)_t3395;
            Bool _t3396 = 1;
            (void)_t3396;
            is_own_arg = _t3396;
            ;
        }
        ;
        Expr *arg = parse_expression(p);
        (void)arg;
        Bool _t3405 = Bool_clone(&(Bool){is_own_arg});
        (void)_t3405;
        ;
        arg->is_own_arg = _t3405;
        ;
        Bool _t3406 = Bool_clone(&(Bool){is_splat});
        (void)_t3406;
        ;
        arg->is_splat = _t3406;
        ;
        Expr_add_child(call, arg);
        Bool _t3407 = check(p, TokenType_Comma());
        (void)_t3407;
        if (_t3407) {
            Token *_t3397 = advance(p);
            (void)_t3397;
        }
        ;
    }
    Token *_t3411 = expect_token(p, TokenType_RParen());
    (void)_t3411;
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
    U32 _t3618 = 0;
    (void)_t3618;
    U32 _t3619 = 0;
    (void)_t3619;
    Expr *e = Expr_new(ExprData_Body(), _t3618, _t3619, &p->path);
    (void)e;
    ;
    ;
    Bool e_set = 0;
    (void)e_set;
    Bool _t3620; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t3620 = *_hp; free(_hp); }
    (void)_t3620;
    if (_t3620) {
        Token *_t3412 = advance(p);
        (void)_t3412;
        Str *_t3413 = Str_clone(&t->text);
        (void)_t3413;
        ExprData *_t3414 = ExprData_LiteralStr(_t3413);
        (void)_t3414;
        Str_delete(_t3413, &(Bool){1});
        e = Expr_new(_t3414, t_line, t_col, &p->path);
        ExprData_delete(_t3414, &(Bool){1});
        Bool _t3415 = 1;
        (void)_t3415;
        e_set = _t3415;
        ;
    }
    ;
    Bool _t3621 = Bool_not(e_set);
    (void)_t3621;
    Bool _t3622; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t3622 = *_hp; free(_hp); }
    (void)_t3622;
    Bool _t3623 = Bool_and(_t3621, _t3622);
    (void)_t3623;
    ;
    ;
    if (_t3623) {
        Token *_t3416 = advance(p);
        (void)_t3416;
        Str *_t3417 = Str_clone(&t->text);
        (void)_t3417;
        ExprData *_t3418 = ExprData_LiteralNum(_t3417);
        (void)_t3418;
        Str_delete(_t3417, &(Bool){1});
        e = Expr_new(_t3418, t_line, t_col, &p->path);
        ExprData_delete(_t3418, &(Bool){1});
        Bool _t3419 = 1;
        (void)_t3419;
        e_set = _t3419;
        ;
    }
    ;
    Bool _t3624 = Bool_not(e_set);
    (void)_t3624;
    Bool _t3625; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Minus()); _t3625 = *_hp; free(_hp); }
    (void)_t3625;
    Bool _t3626 = Bool_and(_t3624, _t3625);
    (void)_t3626;
    ;
    ;
    if (_t3626) {
        U64 _t3435 = 1;
        (void)_t3435;
        U64 _t3436 = U64_add(p->pos, _t3435);
        (void)_t3436;
        ;
        U64 _t3437; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3437 = *_hp; free(_hp); }
        (void)_t3437;
        Bool _t3438; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3436}, &(U64){_t3437}); _t3438 = *_hp; free(_hp); }
        (void)_t3438;
        ;
        ;
        if (_t3438) {
            U64 _t3430 = 1;
            (void)_t3430;
            U64 _t3431 = U64_add(p->pos, _t3430);
            (void)_t3431;
            ;
            I64 _t3432 = U64_to_i64(_t3431);
            (void)_t3432;
            ;
            U64 *_t3433 = malloc(sizeof(U64)); *_t3433 = I64_to_u64(_t3432);
            (void)_t3433;
            ;
            Token *next_tok = Vec_get(&p->tokens, _t3433);
            (void)next_tok;
            Bool _t3434; { Bool *_hp = (Bool *)TokenType_eq(&next_tok->type, TokenType_Number()); _t3434 = *_hp; free(_hp); }
            (void)_t3434;
            U64_delete(_t3433, &(Bool){1});
            if (_t3434) {
                Token *_t3420 = advance(p);
                (void)_t3420;
                Token *num_tok = advance(p);
                (void)num_tok;
                Str *_t3421 = Str_lit("0", 1ULL);
                (void)_t3421;
                Str *_t3422 = Str_clone(_t3421);
                (void)_t3422;
                Str_delete(_t3421, &(Bool){1});
                ExprData *_t3423 = ExprData_LiteralNum(_t3422);
                (void)_t3423;
                Str_delete(_t3422, &(Bool){1});
                Expr *zero = Expr_new(_t3423, t_line, t_col, &p->path);
                (void)zero;
                ExprData_delete(_t3423, &(Bool){1});
                Str *_t3424 = Str_lit("sub", 3ULL);
                (void)_t3424;
                Str *_t3425 = Str_clone(_t3424);
                (void)_t3425;
                Str_delete(_t3424, &(Bool){1});
                ExprData *_t3426 = ExprData_FieldAccess(_t3425);
                (void)_t3426;
                Str_delete(_t3425, &(Bool){1});
                Expr *sub_access = Expr_new(_t3426, t_line, t_col, &p->path);
                (void)sub_access;
                ExprData_delete(_t3426, &(Bool){1});
                Expr_add_child(sub_access, zero);
                Expr *sub_call = Expr_new(ExprData_FCall(), t_line, t_col, &p->path);
                (void)sub_call;
                Expr_add_child(sub_call, sub_access);
                Str *_t3427 = Str_clone(&num_tok->text);
                (void)_t3427;
                ExprData *_t3428 = ExprData_LiteralNum(_t3427);
                (void)_t3428;
                Str_delete(_t3427, &(Bool){1});
                Expr *num_arg = Expr_new(_t3428, t_line, t_col, &p->path);
                (void)num_arg;
                ExprData_delete(_t3428, &(Bool){1});
                Expr_add_child(sub_call, num_arg);
                e = Expr_clone(sub_call);
                Expr_delete(sub_call, &(Bool){1});
                Bool _t3429 = 1;
                (void)_t3429;
                e_set = _t3429;
                ;
            }
            ;
        }
        ;
    }
    ;
    Bool _t3627 = Bool_not(e_set);
    (void)_t3627;
    Bool _t3628; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Char()); _t3628 = *_hp; free(_hp); }
    (void)_t3628;
    Bool _t3629 = Bool_and(_t3627, _t3628);
    (void)_t3629;
    ;
    ;
    if (_t3629) {
        Token *_t3468 = advance(p);
        (void)_t3468;
        Str *ch = Str_clone(&t->text);
        (void)ch;
        I64 byte_val = 0;
        (void)byte_val;
        U64 _t3469; { U64 *_hp = (U64 *)Str_len(ch); _t3469 = *_hp; free(_hp); }
        (void)_t3469;
        U64 _t3470 = 0;
        (void)_t3470;
        U64 *_t3471 = malloc(sizeof(U64));
        *_t3471 = 0;
        (void)_t3471;
        U8 *_t3472 = Str_get(ch, _t3471);
        (void)_t3472;
        U8 _t3473 = 92;
        (void)_t3473;
        Bool _t3474; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3469}, &(U64){_t3470}); _t3474 = *_hp; free(_hp); }
        (void)_t3474;
        ;
        ;
        Bool _t3475 = U8_eq(DEREF(_t3472), _t3473);
        (void)_t3475;
        U64_delete(_t3471, &(Bool){1});
        ;
        Bool _t3476 = Bool_and(_t3474, _t3475);
        (void)_t3476;
        ;
        ;
        if (_t3476) {
            U64 _t3459; { U64 *_hp = (U64 *)Str_len(ch); _t3459 = *_hp; free(_hp); }
            (void)_t3459;
            U64 _t3460 = 1;
            (void)_t3460;
            Bool _t3461; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3459}, &(U64){_t3460}); _t3461 = *_hp; free(_hp); }
            (void)_t3461;
            ;
            ;
            if (_t3461) {
                U64 *_t3456 = malloc(sizeof(U64));
                *_t3456 = 1;
                (void)_t3456;
                U8 *c2 = Str_get(ch, _t3456);
                (void)c2;
                U8 _t3457 = 110;
                (void)_t3457;
                Bool _t3458 = U8_eq(DEREF(c2), _t3457);
                (void)_t3458;
                ;
                if (_t3458) {
                    I64 _t3439 = 10;
                    (void)_t3439;
                    byte_val = _t3439;
                    ;
                } else {
                    U8 _t3454 = 116;
                    (void)_t3454;
                    Bool _t3455 = U8_eq(DEREF(c2), _t3454);
                    (void)_t3455;
                    ;
                    if (_t3455) {
                        I64 _t3440 = 9;
                        (void)_t3440;
                        byte_val = _t3440;
                        ;
                    } else {
                        U8 _t3452 = 114;
                        (void)_t3452;
                        Bool _t3453 = U8_eq(DEREF(c2), _t3452);
                        (void)_t3453;
                        ;
                        if (_t3453) {
                            I64 _t3441 = 13;
                            (void)_t3441;
                            byte_val = _t3441;
                            ;
                        } else {
                            U8 _t3450 = 92;
                            (void)_t3450;
                            Bool _t3451 = U8_eq(DEREF(c2), _t3450);
                            (void)_t3451;
                            ;
                            if (_t3451) {
                                I64 _t3442 = 92;
                                (void)_t3442;
                                byte_val = _t3442;
                                ;
                            } else {
                                U8 _t3448 = 39;
                                (void)_t3448;
                                Bool _t3449 = U8_eq(DEREF(c2), _t3448);
                                (void)_t3449;
                                ;
                                if (_t3449) {
                                    I64 _t3443 = 39;
                                    (void)_t3443;
                                    byte_val = _t3443;
                                    ;
                                } else {
                                    U8 _t3446 = 48;
                                    (void)_t3446;
                                    Bool _t3447 = U8_eq(DEREF(c2), _t3446);
                                    (void)_t3447;
                                    ;
                                    if (_t3447) {
                                        I64 _t3444 = 0;
                                        (void)_t3444;
                                        byte_val = _t3444;
                                        ;
                                    } else {
                                        I64 _t3445 = U8_to_i64(DEREF(c2));
                                        (void)_t3445;
                                        byte_val = _t3445;
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
                U64_delete(_t3456, &(Bool){1});
                ;
            }
            ;
        } else {
            U64 _t3465; { U64 *_hp = (U64 *)Str_len(ch); _t3465 = *_hp; free(_hp); }
            (void)_t3465;
            U64 _t3466 = 0;
            (void)_t3466;
            Bool _t3467; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3465}, &(U64){_t3466}); _t3467 = *_hp; free(_hp); }
            (void)_t3467;
            ;
            ;
            if (_t3467) {
                U64 *_t3462 = malloc(sizeof(U64));
                *_t3462 = 0;
                (void)_t3462;
                U8 *_t3463 = Str_get(ch, _t3462);
                (void)_t3463;
                I64 _t3464 = U8_to_i64(DEREF(_t3463));
                (void)_t3464;
                U64_delete(_t3462, &(Bool){1});
                byte_val = _t3464;
                ;
            }
            ;
        }
        ;
        Str_delete(ch, &(Bool){1});
        Str *_t3477 = I64_to_str(&(I64){byte_val});
        (void)_t3477;
        ;
        ExprData *_t3478 = ExprData_LiteralNum(_t3477);
        (void)_t3478;
        Str_delete(_t3477, &(Bool){1});
        e = Expr_new(_t3478, t_line, t_col, &p->path);
        ExprData_delete(_t3478, &(Bool){1});
        TilType_delete(&e->til_type, &(Bool){0});
        { TilType *_fa = TilType_clone(TilType_U8()); e->til_type = *_fa; free(_fa); }
        Bool _t3479 = 1;
        (void)_t3479;
        e_set = _t3479;
        ;
    }
    ;
    Bool _t3630; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t3630 = *_hp; free(_hp); }
    (void)_t3630;
    Bool _t3631; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t3631 = *_hp; free(_hp); }
    (void)_t3631;
    Bool _t3632 = Bool_not(e_set);
    (void)_t3632;
    Bool _t3633 = Bool_or(_t3630, _t3631);
    (void)_t3633;
    ;
    ;
    Bool _t3634 = Bool_and(_t3632, _t3633);
    (void)_t3634;
    ;
    ;
    if (_t3634) {
        Token *_t3480 = advance(p);
        (void)_t3480;
        Str *_t3481 = Str_clone(&t->text);
        (void)_t3481;
        ExprData *_t3482 = ExprData_LiteralBool(_t3481);
        (void)_t3482;
        Str_delete(_t3481, &(Bool){1});
        e = Expr_new(_t3482, t_line, t_col, &p->path);
        ExprData_delete(_t3482, &(Bool){1});
        Bool _t3483 = 1;
        (void)_t3483;
        e_set = _t3483;
        ;
    }
    ;
    Bool _t3635 = Bool_not(e_set);
    (void)_t3635;
    Bool _t3636; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwNull()); _t3636 = *_hp; free(_hp); }
    (void)_t3636;
    Bool _t3637 = Bool_and(_t3635, _t3636);
    (void)_t3637;
    ;
    ;
    if (_t3637) {
        Token *_t3484 = advance(p);
        (void)_t3484;
        e = Expr_new(ExprData_LiteralNull(), t_line, t_col, &p->path);
        Bool _t3485 = 1;
        (void)_t3485;
        e_set = _t3485;
        ;
    }
    ;
    Bool _t3638 = Bool_not(e_set);
    (void)_t3638;
    Bool _t3639; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t3639 = *_hp; free(_hp); }
    (void)_t3639;
    Bool _t3640 = Bool_and(_t3638, _t3639);
    (void)_t3640;
    ;
    ;
    if (_t3640) {
        Token *_t3521 = advance(p);
        (void)_t3521;
        Str *name = Str_clone(&t->text);
        (void)name;
        Str *_t3522 = Str_lit("__LOC__", 7ULL);
        (void)_t3522;
        Bool _t3523; { Bool *_hp = (Bool *)Str_eq(name, _t3522); _t3523 = *_hp; free(_hp); }
        (void)_t3523;
        Str_delete(_t3522, &(Bool){1});
        if (_t3523) {
            Str *_t3486 = Str_lit("Str", 3ULL);
            (void)_t3486;
            U64 _t3487; { U64 *_hp = (U64 *)Str_size(); _t3487 = *_hp; free(_hp); }
            (void)_t3487;
            U64 _t3488 = 5;
            (void)_t3488;
            Array *_va67 = Array_new(_t3486, &(U64){_t3487}, &(U64){_t3488});
            (void)_va67;
            Str_delete(_t3486, &(Bool){1});
            ;
            ;
            U64 _t3489 = 0;
            (void)_t3489;
            Str *_t3490 = Str_clone(&p->path);
            (void)_t3490;
            Array_set(_va67, &(U64){_t3489}, _t3490);
            ;
            U64 _t3491 = 1;
            (void)_t3491;
            Str *_t3492 = Str_lit(":", 1ULL);
            (void)_t3492;
            Array_set(_va67, &(U64){_t3491}, _t3492);
            ;
            U64 _t3493 = 2;
            (void)_t3493;
            Str *_t3494 = U32_to_str(&(U32){t_line});
            (void)_t3494;
            Array_set(_va67, &(U64){_t3493}, _t3494);
            ;
            U64 _t3495 = 3;
            (void)_t3495;
            Str *_t3496 = Str_lit(":", 1ULL);
            (void)_t3496;
            Array_set(_va67, &(U64){_t3495}, _t3496);
            ;
            U64 _t3497 = 4;
            (void)_t3497;
            Str *_t3498 = U32_to_str(&(U32){t_col});
            (void)_t3498;
            Array_set(_va67, &(U64){_t3497}, _t3498);
            ;
            Str *_t3499 = format(_va67);
            (void)_t3499;
            ExprData *_t3500 = ExprData_LiteralStr(_t3499);
            (void)_t3500;
            Str_delete(_t3499, &(Bool){1});
            e = Expr_new(_t3500, t_line, t_col, &p->path);
            ExprData_delete(_t3500, &(Bool){1});
            Bool _t3501 = 1;
            (void)_t3501;
            e_set = _t3501;
            ;
        } else {
            Str *_t3519 = Str_lit("__FILE__", 8ULL);
            (void)_t3519;
            Bool _t3520; { Bool *_hp = (Bool *)Str_eq(name, _t3519); _t3520 = *_hp; free(_hp); }
            (void)_t3520;
            Str_delete(_t3519, &(Bool){1});
            if (_t3520) {
                Str *_t3502 = Str_clone(&p->path);
                (void)_t3502;
                ExprData *_t3503 = ExprData_LiteralStr(_t3502);
                (void)_t3503;
                Str_delete(_t3502, &(Bool){1});
                e = Expr_new(_t3503, t_line, t_col, &p->path);
                ExprData_delete(_t3503, &(Bool){1});
                Bool _t3504 = 1;
                (void)_t3504;
                e_set = _t3504;
                ;
            } else {
                Str *_t3517 = Str_lit("__LINE__", 8ULL);
                (void)_t3517;
                Bool _t3518; { Bool *_hp = (Bool *)Str_eq(name, _t3517); _t3518 = *_hp; free(_hp); }
                (void)_t3518;
                Str_delete(_t3517, &(Bool){1});
                if (_t3518) {
                    Str *_t3505 = U32_to_str(&(U32){t_line});
                    (void)_t3505;
                    ExprData *_t3506 = ExprData_LiteralNum(_t3505);
                    (void)_t3506;
                    Str_delete(_t3505, &(Bool){1});
                    e = Expr_new(_t3506, t_line, t_col, &p->path);
                    ExprData_delete(_t3506, &(Bool){1});
                    Bool _t3507 = 1;
                    (void)_t3507;
                    e_set = _t3507;
                    ;
                } else {
                    Str *_t3515 = Str_lit("__COL__", 7ULL);
                    (void)_t3515;
                    Bool _t3516; { Bool *_hp = (Bool *)Str_eq(name, _t3515); _t3516 = *_hp; free(_hp); }
                    (void)_t3516;
                    Str_delete(_t3515, &(Bool){1});
                    if (_t3516) {
                        Str *_t3508 = U32_to_str(&(U32){t_col});
                        (void)_t3508;
                        ExprData *_t3509 = ExprData_LiteralNum(_t3508);
                        (void)_t3509;
                        Str_delete(_t3508, &(Bool){1});
                        e = Expr_new(_t3509, t_line, t_col, &p->path);
                        ExprData_delete(_t3509, &(Bool){1});
                        Bool _t3510 = 1;
                        (void)_t3510;
                        e_set = _t3510;
                        ;
                    } else {
                        Bool _t3514 = check(p, TokenType_LParen());
                        (void)_t3514;
                        if (_t3514) {
                            e = parse_call(p, name, t_line, t_col);
                            Bool _t3511 = 1;
                            (void)_t3511;
                            e_set = _t3511;
                            ;
                        } else {
                            ExprData *_t3512 = ExprData_Ident(name);
                            (void)_t3512;
                            e = Expr_new(_t3512, t_line, t_col, &p->path);
                            ExprData_delete(_t3512, &(Bool){1});
                            Bool _t3513 = 1;
                            (void)_t3513;
                            e_set = _t3513;
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
    Bool _t3641; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFunc()); _t3641 = *_hp; free(_hp); }
    (void)_t3641;
    Bool _t3642; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwProc()); _t3642 = *_hp; free(_hp); }
    (void)_t3642;
    Bool _t3643 = Bool_or(_t3641, _t3642);
    (void)_t3643;
    ;
    ;
    Bool _t3644; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTest()); _t3644 = *_hp; free(_hp); }
    (void)_t3644;
    Bool _t3645 = Bool_or(_t3643, _t3644);
    (void)_t3645;
    ;
    ;
    Bool _t3646; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMacro()); _t3646 = *_hp; free(_hp); }
    (void)_t3646;
    Bool _t3647 = Bool_or(_t3645, _t3646);
    (void)_t3647;
    ;
    ;
    Bool _t3648; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtFunc()); _t3648 = *_hp; free(_hp); }
    (void)_t3648;
    Bool _t3649 = Bool_or(_t3647, _t3648);
    (void)_t3649;
    ;
    ;
    Bool _t3650; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtProc()); _t3650 = *_hp; free(_hp); }
    (void)_t3650;
    Bool _t3651 = Bool_not(e_set);
    (void)_t3651;
    Bool _t3652 = Bool_or(_t3649, _t3650);
    (void)_t3652;
    ;
    ;
    Bool _t3653 = Bool_and(_t3651, _t3652);
    (void)_t3653;
    ;
    ;
    if (_t3653) {
        Expr *_t3524 = parse_func_def(p);
        (void)_t3524;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3524;
    }
    ;
    Bool _t3654; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwStruct()); _t3654 = *_hp; free(_hp); }
    (void)_t3654;
    Bool _t3655; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtStruct()); _t3655 = *_hp; free(_hp); }
    (void)_t3655;
    Bool _t3656 = Bool_not(e_set);
    (void)_t3656;
    Bool _t3657 = Bool_or(_t3654, _t3655);
    (void)_t3657;
    ;
    ;
    Bool _t3658 = Bool_and(_t3656, _t3657);
    (void)_t3658;
    ;
    ;
    if (_t3658) {
        Expr *_t3525 = parse_struct_def(p);
        (void)_t3525;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3525;
    }
    ;
    Bool _t3659 = Bool_not(e_set);
    (void)_t3659;
    Bool _t3660; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwEnum()); _t3660 = *_hp; free(_hp); }
    (void)_t3660;
    Bool _t3661 = Bool_and(_t3659, _t3660);
    (void)_t3661;
    ;
    ;
    if (_t3661) {
        Expr *_t3526 = parse_enum_def(p);
        (void)_t3526;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3526;
    }
    ;
    Bool _t3662 = Bool_not(e_set);
    (void)_t3662;
    Bool _t3663; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t3663 = *_hp; free(_hp); }
    (void)_t3663;
    Bool _t3664 = Bool_and(_t3662, _t3663);
    (void)_t3664;
    ;
    ;
    if (_t3664) {
        Token *_t3551 = advance(p);
        (void)_t3551;
        Expr *first = parse_expression(p);
        (void)first;
        Bool _t3552 = check(p, TokenType_Colon());
        (void)_t3552;
        if (_t3552) {
            e = Expr_new(ExprData_MapLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Token *_t3538 = advance(p);
            (void)_t3538;
            Expr *_t3539 = parse_expression(p);
            (void)_t3539;
            Expr_add_child(e, _t3539);
            Bool _t3540 = check(p, TokenType_Comma());
            (void)_t3540;
            if (_t3540) {
                Token *_t3527 = advance(p);
                (void)_t3527;
            }
            ;
            while (1) {
                Bool _t3530 = check(p, TokenType_RBrace());
                (void)_t3530;
                Bool _t3531 = check(p, TokenType_Eof());
                (void)_t3531;
                Bool _t3532 = Bool_not(_t3530);
                (void)_t3532;
                ;
                Bool _t3533 = Bool_not(_t3531);
                (void)_t3533;
                ;
                Bool _wcond3528 = Bool_and(_t3532, _t3533);
                (void)_wcond3528;
                ;
                ;
                if (_wcond3528) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3534 = parse_expression(p);
                (void)_t3534;
                Expr_add_child(e, _t3534);
                Token *_t3535 = expect_token(p, TokenType_Colon());
                (void)_t3535;
                Expr *_t3536 = parse_expression(p);
                (void)_t3536;
                Expr_add_child(e, _t3536);
                Bool _t3537 = check(p, TokenType_Comma());
                (void)_t3537;
                if (_t3537) {
                    Token *_t3529 = advance(p);
                    (void)_t3529;
                }
                ;
            }
        } else {
            e = Expr_new(ExprData_SetLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Bool _t3550 = check(p, TokenType_Comma());
            (void)_t3550;
            if (_t3550) {
                Token *_t3541 = advance(p);
                (void)_t3541;
            }
            ;
            while (1) {
                Bool _t3544 = check(p, TokenType_RBrace());
                (void)_t3544;
                Bool _t3545 = check(p, TokenType_Eof());
                (void)_t3545;
                Bool _t3546 = Bool_not(_t3544);
                (void)_t3546;
                ;
                Bool _t3547 = Bool_not(_t3545);
                (void)_t3547;
                ;
                Bool _wcond3542 = Bool_and(_t3546, _t3547);
                (void)_wcond3542;
                ;
                ;
                if (_wcond3542) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3548 = parse_expression(p);
                (void)_t3548;
                Expr_add_child(e, _t3548);
                Bool _t3549 = check(p, TokenType_Comma());
                (void)_t3549;
                if (_t3549) {
                    Token *_t3543 = advance(p);
                    (void)_t3543;
                }
                ;
            }
        }
        ;
        Token *_t3553 = expect_token(p, TokenType_RBrace());
        (void)_t3553;
        Bool _t3554 = 1;
        (void)_t3554;
        e_set = _t3554;
        ;
    }
    ;
    Bool _t3665 = Bool_not(e_set);
    (void)_t3665;
    ;
    if (_t3665) {
        Str *_t3555 = Str_lit("Str", 3ULL);
        (void)_t3555;
        U64 _t3556; { U64 *_hp = (U64 *)Str_size(); _t3556 = *_hp; free(_hp); }
        (void)_t3556;
        U64 _t3557 = 8;
        (void)_t3557;
        Array *_va68 = Array_new(_t3555, &(U64){_t3556}, &(U64){_t3557});
        (void)_va68;
        Str_delete(_t3555, &(Bool){1});
        ;
        ;
        U64 _t3558 = 0;
        (void)_t3558;
        Str *_t3559 = Str_clone(&p->path);
        (void)_t3559;
        Array_set(_va68, &(U64){_t3558}, _t3559);
        ;
        U64 _t3560 = 1;
        (void)_t3560;
        Str *_t3561 = Str_lit(":", 1ULL);
        (void)_t3561;
        Array_set(_va68, &(U64){_t3560}, _t3561);
        ;
        U64 _t3562 = 2;
        (void)_t3562;
        Str *_t3563 = U32_to_str(&(U32){t_line});
        (void)_t3563;
        Array_set(_va68, &(U64){_t3562}, _t3563);
        ;
        U64 _t3564 = 3;
        (void)_t3564;
        Str *_t3565 = Str_lit(":", 1ULL);
        (void)_t3565;
        Array_set(_va68, &(U64){_t3564}, _t3565);
        ;
        U64 _t3566 = 4;
        (void)_t3566;
        Str *_t3567 = U32_to_str(&(U32){t_col});
        (void)_t3567;
        Array_set(_va68, &(U64){_t3566}, _t3567);
        ;
        U64 _t3568 = 5;
        (void)_t3568;
        Str *_t3569 = Str_lit(": unexpected token '", 20ULL);
        (void)_t3569;
        Array_set(_va68, &(U64){_t3568}, _t3569);
        ;
        U64 _t3570 = 6;
        (void)_t3570;
        Str *_t3571 = Str_clone(&t->text);
        (void)_t3571;
        Array_set(_va68, &(U64){_t3570}, _t3571);
        ;
        U64 _t3572 = 7;
        (void)_t3572;
        Str *_t3573 = Str_lit("'", 1ULL);
        (void)_t3573;
        Array_set(_va68, &(U64){_t3572}, _t3573);
        ;
        Str *_t3574 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:536:15", 64ULL);
        (void)_t3574;
        panic(_t3574, _va68);
        Str_delete(_t3574, &(Bool){1});
    }
    ;
    ;
    ;
    while (1) {
        Bool _wcond3575 = check(p, TokenType_Dot());
        (void)_wcond3575;
        if (_wcond3575) {
        } else {
            ;
            break;
        }
        ;
        Token *_t3608 = advance(p);
        (void)_t3608;
        U32 f_line = peek_line(p);
        (void)f_line;
        U32 f_col = peek_col(p);
        (void)f_col;
        Str *fname = expect_text(p, TokenType_Ident());
        (void)fname;
        Bool _t3609 = check(p, TokenType_LParen());
        (void)_t3609;
        if (_t3609) {
            Token *_t3602 = advance(p);
            (void)_t3602;
            ExprData *_t3603 = ExprData_FieldAccess(fname);
            (void)_t3603;
            Expr *callee = Expr_new(_t3603, f_line, f_col, &p->path);
            (void)callee;
            ExprData_delete(_t3603, &(Bool){1});
            Expr *_t3604 = Expr_clone(e);
            (void)_t3604;
            Expr_add_child(callee, _t3604);
            Expr *mcall = Expr_new(ExprData_FCall(), f_line, f_col, &p->path);
            (void)mcall;
            Expr_add_child(mcall, callee);
            while (1) {
                Bool _t3594 = check(p, TokenType_RParen());
                (void)_t3594;
                Bool _t3595 = check(p, TokenType_Eof());
                (void)_t3595;
                Bool _t3596 = Bool_not(_t3594);
                (void)_t3596;
                ;
                Bool _t3597 = Bool_not(_t3595);
                (void)_t3597;
                ;
                Bool _wcond3576 = Bool_and(_t3596, _t3597);
                (void)_wcond3576;
                ;
                ;
                if (_wcond3576) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3598 = check(p, TokenType_Ident());
                (void)_t3598;
                if (_t3598) {
                    U64 _t3587 = 1;
                    (void)_t3587;
                    U64 _t3588 = U64_add(p->pos, _t3587);
                    (void)_t3588;
                    ;
                    U64 _t3589; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3589 = *_hp; free(_hp); }
                    (void)_t3589;
                    Bool _t3590; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3588}, &(U64){_t3589}); _t3590 = *_hp; free(_hp); }
                    (void)_t3590;
                    ;
                    ;
                    if (_t3590) {
                        U64 _t3582 = 1;
                        (void)_t3582;
                        U64 _t3583 = U64_add(p->pos, _t3582);
                        (void)_t3583;
                        ;
                        I64 _t3584 = U64_to_i64(_t3583);
                        (void)_t3584;
                        ;
                        U64 *_t3585 = malloc(sizeof(U64)); *_t3585 = I64_to_u64(_t3584);
                        (void)_t3585;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3585);
                        (void)nt;
                        Bool _t3586; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3586 = *_hp; free(_hp); }
                        (void)_t3586;
                        U64_delete(_t3585, &(Bool){1});
                        if (_t3586) {
                            U32 na_line = peek_line(p);
                            (void)na_line;
                            U32 na_col = peek_col(p);
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3578 = advance(p);
                            (void)_t3578;
                            ExprData *_t3579 = ExprData_NamedArg(aname);
                            (void)_t3579;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3579, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3579, &(Bool){1});
                            ;
                            ;
                            Expr *_t3580 = parse_expression(p);
                            (void)_t3580;
                            Expr_add_child(na, _t3580);
                            Expr_add_child(mcall, na);
                            Bool _t3581 = check(p, TokenType_Comma());
                            (void)_t3581;
                            if (_t3581) {
                                Token *_t3577 = advance(p);
                                (void)_t3577;
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
                Bool _t3599 = check(p, TokenType_KwOwn());
                (void)_t3599;
                if (_t3599) {
                    Token *_t3591 = advance(p);
                    (void)_t3591;
                    Bool _t3592 = 1;
                    (void)_t3592;
                    is_own_arg = _t3592;
                    ;
                }
                ;
                Expr *marg = parse_expression(p);
                (void)marg;
                Bool _t3600 = Bool_clone(&(Bool){is_own_arg});
                (void)_t3600;
                ;
                marg->is_own_arg = _t3600;
                ;
                Expr_add_child(mcall, marg);
                Bool _t3601 = check(p, TokenType_Comma());
                (void)_t3601;
                if (_t3601) {
                    Token *_t3593 = advance(p);
                    (void)_t3593;
                }
                ;
            }
            Token *_t3605 = expect_token(p, TokenType_RParen());
            (void)_t3605;
            e = Expr_clone(mcall);
            Expr_delete(mcall, &(Bool){1});
        } else {
            ExprData *_t3606 = ExprData_FieldAccess(fname);
            (void)_t3606;
            Expr *access = Expr_new(_t3606, f_line, f_col, &p->path);
            (void)access;
            ExprData_delete(_t3606, &(Bool){1});
            Expr *_t3607 = Expr_clone(e);
            (void)_t3607;
            Expr_add_child(access, _t3607);
            e = Expr_clone(access);
            Expr_delete(access, &(Bool){1});
        }
        ;
        ;
        ;
        Str_delete(fname, &(Bool){1});
    }
    Bool _t3666 = check(p, TokenType_DotDot());
    (void)_t3666;
    if (_t3666) {
        U32 dt_line = peek_line(p);
        (void)dt_line;
        U32 dt_col = peek_col(p);
        (void)dt_col;
        Token *_t3610 = advance(p);
        (void)_t3610;
        Expr *rhs = parse_expression(p);
        (void)rhs;
        Str *_t3611 = Str_lit("Range", 5ULL);
        (void)_t3611;
        Str *_t3612 = Str_clone(_t3611);
        (void)_t3612;
        Str_delete(_t3611, &(Bool){1});
        ExprData *_t3613 = ExprData_Ident(_t3612);
        (void)_t3613;
        Str_delete(_t3612, &(Bool){1});
        Expr *range_ident = Expr_new(_t3613, dt_line, dt_col, &p->path);
        (void)range_ident;
        ExprData_delete(_t3613, &(Bool){1});
        Str *_t3614 = Str_lit("new", 3ULL);
        (void)_t3614;
        Str *_t3615 = Str_clone(_t3614);
        (void)_t3615;
        Str_delete(_t3614, &(Bool){1});
        ExprData *_t3616 = ExprData_FieldAccess(_t3615);
        (void)_t3616;
        Str_delete(_t3615, &(Bool){1});
        Expr *new_access = Expr_new(_t3616, dt_line, dt_col, &p->path);
        (void)new_access;
        ExprData_delete(_t3616, &(Bool){1});
        Expr_add_child(new_access, range_ident);
        Expr *rcall = Expr_new(ExprData_FCall(), dt_line, dt_col, &p->path);
        (void)rcall;
        ;
        ;
        Expr_add_child(rcall, new_access);
        Expr *_t3617 = Expr_clone(e);
        (void)_t3617;
        Expr_add_child(rcall, _t3617);
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
    Bool _t3846 = check(p, TokenType_ColonEq());
    (void)_t3846;
    if (_t3846) {
        Token *_t3667 = advance(p);
        (void)_t3667;
        Bool _t3668 = Bool_clone(&(Bool){is_mut});
        (void)_t3668;
        Bool _t3669 = 0;
        (void)_t3669;
        Bool _t3670 = 0;
        (void)_t3670;
        Bool _t3671 = Bool_clone(&(Bool){is_own});
        (void)_t3671;
        I32 _t3672 = 0;
        (void)_t3672;
        I32 _t3673 = 0;
        (void)_t3673;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3668;
        dd->is_namespace = _t3669;
        dd->is_ref = _t3670;
        dd->is_own = _t3671;
        dd->field_offset = _t3672;
        dd->field_size = _t3673;
        dd->field_struct_def = NULL;
        dd->fn_sig = NULL;
        (void)dd;
        ;
        ;
        ;
        ;
        ;
        ;
        ExprData *_t3674 = ExprData_Decl(dd);
        (void)_t3674;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3674, t_line, t_col, &p->path);
        (void)decl;
        ExprData_delete(_t3674, &(Bool){1});
        Expr *_t3675 = parse_expression(p);
        (void)_t3675;
        Expr_add_child(decl, _t3675);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return decl;
    }
    ;
    Bool _t3847 = check(p, TokenType_Colon());
    (void)_t3847;
    if (_t3847) {
        Token *_t3780 = advance(p);
        (void)_t3780;
        Bool _t3781 = check(p, TokenType_KwFunc());
        (void)_t3781;
        Bool _t3782 = check(p, TokenType_KwProc());
        (void)_t3782;
        Bool _t3783 = Bool_or(_t3781, _t3782);
        (void)_t3783;
        ;
        ;
        if (_t3783) {
            Expr *sig = parse_func_def(p);
            (void)sig;
            Token *_t3689 = expect_token(p, TokenType_Eq());
            (void)_t3689;
            Token *_t3690 = expect_token(p, TokenType_LParen());
            (void)_t3690;
            Bool _t3691; { Bool *_hp = (Bool *)ExprData_is_FuncDef(&sig->data); _t3691 = *_hp; free(_hp); }
            (void)_t3691;
            if (_t3691) {
                FunctionDef *sfd = ExprData_get_FuncDef(&sig->data);
                (void)sfd;
                Str *_t3686 = Str_lit("Str", 3ULL);
                (void)_t3686;
                U64 _t3687; { U64 *_hp = (U64 *)Str_size(); _t3687 = *_hp; free(_hp); }
                (void)_t3687;
                Vec *new_names = Vec_new(_t3686, &(U64){_t3687});
                (void)new_names;
                Str_delete(_t3686, &(Bool){1});
                ;
                Vec_delete(new_names, &(Bool){1});
                {
                    U64 _t3684 = 0;
                    (void)_t3684;
                    U64 _t3685; { U64 *_hp = (U64 *)Vec_len(&sfd->params); _t3685 = *_hp; free(_hp); }
                    (void)_t3685;
                    Range *_fc3676 = Range_new(_t3684, _t3685);
                    (void)_fc3676;
                    ;
                    ;
                    U64 _fi3676 = 0;
                    (void)_fi3676;
                    while (1) {
                        U64 _t3679; { U64 *_hp = (U64 *)Range_len(_fc3676); _t3679 = *_hp; free(_hp); }
                        (void)_t3679;
                        Bool _wcond3677; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3676}, &(U64){_t3679}); _wcond3677 = *_hp; free(_hp); }
                        (void)_wcond3677;
                        ;
                        if (_wcond3677) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 *pi = Range_get(_fc3676, _fi3676);
                        (void)pi;
                        U64 _t3680 = 1;
                        (void)_t3680;
                        U64 _t3681 = U64_add(_fi3676, _t3680);
                        (void)_t3681;
                        ;
                        _fi3676 = _t3681;
                        ;
                        U64 _t3682 = 0;
                        (void)_t3682;
                        Bool _t3683; { Bool *_hp = (Bool *)U64_gt(pi, &(U64){_t3682}); _t3683 = *_hp; free(_hp); }
                        (void)_t3683;
                        ;
                        if (_t3683) {
                            Token *_t3678 = expect_token(p, TokenType_Comma());
                            (void)_t3678;
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
                    Range_delete(_fc3676, &(Bool){1});
                    ;
                }
                ExprData_delete(&sig->data, &(Bool){0});
                { ExprData *_fa = ExprData_FuncDef(sfd); sig->data = *_fa; free(_fa); }
                FunctionDef_delete(sfd, &(Bool){1});
            }
            ;
            Bool _t3692 = check(p, TokenType_Comma());
            (void)_t3692;
            if (_t3692) {
                Token *_t3688 = advance(p);
                (void)_t3688;
            }
            ;
            Token *_t3693 = expect_token(p, TokenType_RParen());
            (void)_t3693;
            Token *_t3694 = expect_token(p, TokenType_LBrace());
            (void)_t3694;
            Expr *_t3695 = parse_block(p);
            (void)_t3695;
            Expr_add_child(sig, _t3695);
            Bool _t3696 = Bool_clone(&(Bool){is_mut});
            (void)_t3696;
            Bool _t3697 = 0;
            (void)_t3697;
            Bool _t3698 = 0;
            (void)_t3698;
            Bool _t3699 = Bool_clone(&(Bool){is_own});
            (void)_t3699;
            I32 _t3700 = 0;
            (void)_t3700;
            I32 _t3701 = 0;
            (void)_t3701;
            Declaration *dd = malloc(sizeof(Declaration));
            { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
            dd->is_mut = _t3696;
            dd->is_namespace = _t3697;
            dd->is_ref = _t3698;
            dd->is_own = _t3699;
            dd->field_offset = _t3700;
            dd->field_size = _t3701;
            dd->field_struct_def = NULL;
            dd->fn_sig = NULL;
            (void)dd;
            ;
            ;
            ;
            ;
            ;
            ;
            ExprData *_t3702 = ExprData_Decl(dd);
            (void)_t3702;
            Declaration_delete(dd, &(Bool){1});
            Expr *decl = Expr_new(_t3702, t_line, t_col, &p->path);
            (void)decl;
            ExprData_delete(_t3702, &(Bool){1});
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
        Str *_t3784 = Str_lit("Fn", 2ULL);
        (void)_t3784;
        Bool _t3785; { Bool *_hp = (Bool *)Str_eq(type_name, _t3784); _t3785 = *_hp; free(_hp); }
        (void)_t3785;
        Str_delete(_t3784, &(Bool){1});
        if (_t3785) {
            Str *syn_name = parse_fn_signature(p, t_line, t_col);
            (void)syn_name;
            U64 _t3703; { U64 *_hp = (U64 *)Str_len(syn_name); _t3703 = *_hp; free(_hp); }
            (void)_t3703;
            U64 _t3704 = 0;
            (void)_t3704;
            Bool _t3705; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3703}, &(U64){_t3704}); _t3705 = *_hp; free(_hp); }
            (void)_t3705;
            ;
            ;
            if (_t3705) {
                type_name = Str_clone(syn_name);
            }
            ;
            Str_delete(syn_name, &(Bool){1});
        }
        ;
        Token *_t3786 = expect_token(p, TokenType_Eq());
        (void)_t3786;
        Bool _t3787 = check(p, TokenType_LParen());
        (void)_t3787;
        if (_t3787) {
            U64 saved = p->pos;
            (void)saved;
            Token *_t3776 = advance(p);
            (void)_t3776;
            Bool is_fsf = 1;
            (void)is_fsf;
            while (1) {
                Bool _t3709 = check(p, TokenType_RParen());
                (void)_t3709;
                Bool _t3710 = check(p, TokenType_Eof());
                (void)_t3710;
                Bool _t3711 = Bool_not(_t3709);
                (void)_t3711;
                ;
                Bool _t3712 = Bool_not(_t3710);
                (void)_t3712;
                ;
                Bool _wcond3706 = Bool_and(_t3711, _t3712);
                (void)_wcond3706;
                ;
                ;
                if (_wcond3706) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3713 = check(p, TokenType_Ident());
                (void)_t3713;
                Bool _t3714 = Bool_not(_t3713);
                (void)_t3714;
                ;
                if (_t3714) {
                    Bool _t3707 = 0;
                    (void)_t3707;
                    is_fsf = _t3707;
                    ;
                    ;
                    break;
                }
                ;
                Token *_t3715 = advance(p);
                (void)_t3715;
                Bool _t3716 = check(p, TokenType_Comma());
                (void)_t3716;
                if (_t3716) {
                    Token *_t3708 = advance(p);
                    (void)_t3708;
                }
                ;
            }
            Bool _t3777 = check(p, TokenType_RParen());
            (void)_t3777;
            Bool _t3778 = Bool_and(is_fsf, _t3777);
            (void)_t3778;
            ;
            if (_t3778) {
                Token *_t3718 = advance(p);
                (void)_t3718;
                Bool _t3719 = check(p, TokenType_LBrace());
                (void)_t3719;
                Bool _t3720 = Bool_not(_t3719);
                (void)_t3720;
                ;
                if (_t3720) {
                    Bool _t3717 = 0;
                    (void)_t3717;
                    is_fsf = _t3717;
                    ;
                }
                ;
            } else {
                Bool _t3721 = 0;
                (void)_t3721;
                is_fsf = _t3721;
                ;
            }
            ;
            U64 _t3779 = U64_clone(&(U64){saved});
            (void)_t3779;
            ;
            p->pos = _t3779;
            ;
            if (is_fsf) {
                Token *_t3736 = expect_token(p, TokenType_LParen());
                (void)_t3736;
                Str *_t3737 = Str_lit("Str", 3ULL);
                (void)_t3737;
                U64 _t3738; { U64 *_hp = (U64 *)Str_size(); _t3738 = *_hp; free(_hp); }
                (void)_t3738;
                Vec *pnames = Vec_new(_t3737, &(U64){_t3738});
                (void)pnames;
                Str_delete(_t3737, &(Bool){1});
                ;
                while (1) {
                    Bool _t3724 = check(p, TokenType_RParen());
                    (void)_t3724;
                    Bool _wcond3722 = Bool_not(_t3724);
                    (void)_wcond3722;
                    ;
                    if (_wcond3722) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *pn = expect_text(p, TokenType_Ident());
                    (void)pn;
                    Vec_push(pnames, pn);
                    Bool _t3725 = check(p, TokenType_Comma());
                    (void)_t3725;
                    if (_t3725) {
                        Token *_t3723 = advance(p);
                        (void)_t3723;
                    }
                    ;
                }
                Token *_t3739 = expect_token(p, TokenType_RParen());
                (void)_t3739;
                Token *_t3740 = expect_token(p, TokenType_LBrace());
                (void)_t3740;
                Expr *body = parse_block(p);
                (void)body;
                Str *_t3741 = Str_lit("Param", 5ULL);
                (void)_t3741;
                U64 _t3742; { U64 *_hp = (U64 *)Param_size(); _t3742 = *_hp; free(_hp); }
                (void)_t3742;
                Str *_t3743 = Str_lit("Str", 3ULL);
                (void)_t3743;
                U64 _t3744; { U64 *_hp = (U64 *)Str_size(); _t3744 = *_hp; free(_hp); }
                (void)_t3744;
                Str *_t3745 = Str_lit("Expr", 4ULL);
                (void)_t3745;
                U64 _t3746; { U64 *_hp = (U64 *)Expr_size(); _t3746 = *_hp; free(_hp); }
                (void)_t3746;
                I64 _t3747 = 0;
                (void)_t3747;
                I64 _t3748 = 1;
                (void)_t3748;
                I64 _t3749 = I64_sub(_t3747, _t3748);
                (void)_t3749;
                ;
                ;
                I64 _t3750 = 0;
                (void)_t3750;
                I64 _t3751 = 1;
                (void)_t3751;
                I64 _t3752 = I64_sub(_t3750, _t3751);
                (void)_t3752;
                ;
                ;
                U32 _t3753 = 0;
                (void)_t3753;
                I32 _t3754 = I64_to_i32(_t3749);
                (void)_t3754;
                ;
                I32 _t3755 = I64_to_i32(_t3752);
                (void)_t3755;
                ;
                Bool _t3756 = 0;
                (void)_t3756;
                Bool _t3757 = 0;
                (void)_t3757;
                FunctionDef *ffd = malloc(sizeof(FunctionDef));
                { FuncType *_ca = FuncType_clone(FuncType_Func()); ffd->func_type = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3741, &(U64){_t3742}); ffd->params = *_ca; free(_ca); }
                ffd->nparam = _t3753;
                { Map *_ca = Map_new(_t3743, &(U64){_t3744}, _t3745, &(U64){_t3746}); ffd->param_defaults = *_ca; free(_ca); }
                { Str *_ca = Str_clone(Str_lit("", 0ULL)); ffd->return_type = *_ca; free(_ca); }
                ffd->variadic_index = _t3754;
                ffd->kwargs_index = _t3755;
                ffd->return_is_ref = _t3756;
                ffd->return_is_shallow = _t3757;
                (void)ffd;
                Str_delete(_t3741, &(Bool){1});
                ;
                Str_delete(_t3743, &(Bool){1});
                ;
                Str_delete(_t3745, &(Bool){1});
                ;
                ;
                ;
                ;
                ;
                ;
                FuncType_delete(&ffd->func_type, &(Bool){0});
                { FuncType *_fa = FuncType_clone(FuncType_Func()); ffd->func_type = *_fa; free(_fa); }
                I64 _t3758 = 0;
                (void)_t3758;
                I64 _t3759 = 1;
                (void)_t3759;
                I64 _t3760 = I64_sub(_t3758, _t3759);
                (void)_t3760;
                ;
                ;
                I32 _t3761 = I64_to_i32(_t3760);
                (void)_t3761;
                ;
                ffd->variadic_index = _t3761;
                ;
                I64 _t3762 = 0;
                (void)_t3762;
                I64 _t3763 = 1;
                (void)_t3763;
                I64 _t3764 = I64_sub(_t3762, _t3763);
                (void)_t3764;
                ;
                ;
                I32 _t3765 = I64_to_i32(_t3764);
                (void)_t3765;
                ;
                ffd->kwargs_index = _t3765;
                ;
                U64 np; { U64 *_hp = (U64 *)Vec_len(pnames); np = *_hp; free(_hp); }
                (void)np;
                {
                    U64 _t3735 = 0;
                    (void)_t3735;
                    Range *_fc3726 = Range_new(_t3735, np);
                    (void)_fc3726;
                    ;
                    U64 _fi3726 = 0;
                    (void)_fi3726;
                    while (1) {
                        U64 _t3728; { U64 *_hp = (U64 *)Range_len(_fc3726); _t3728 = *_hp; free(_hp); }
                        (void)_t3728;
                        Bool _wcond3727; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3726}, &(U64){_t3728}); _wcond3727 = *_hp; free(_hp); }
                        (void)_wcond3727;
                        ;
                        if (_wcond3727) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 *i = Range_get(_fc3726, _fi3726);
                        (void)i;
                        U64 _t3729 = 1;
                        (void)_t3729;
                        U64 _t3730 = U64_add(_fi3726, _t3729);
                        (void)_t3730;
                        ;
                        _fi3726 = _t3730;
                        ;
                        Str *pn = Vec_get(pnames, i);
                        (void)pn;
                        Bool _t3731 = 0;
                        (void)_t3731;
                        Bool _t3732 = 0;
                        (void)_t3732;
                        Bool _t3733 = 0;
                        (void)_t3733;
                        Param *_t3734 = malloc(sizeof(Param));
                        { Str *_ca = Str_clone(pn); _t3734->name = *_ca; free(_ca); }
                        { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t3734->ptype = *_ca; free(_ca); }
                        _t3734->is_mut = _t3731;
                        _t3734->is_own = _t3732;
                        _t3734->is_shallow = _t3733;
                        (void)_t3734;
                        ;
                        ;
                        ;
                        U64_delete(i, &(Bool){1});
                        Vec_push(&ffd->params, _t3734);
                    }
                    Range_delete(_fc3726, &(Bool){1});
                    ;
                }
                Vec_delete(pnames, &(Bool){1});
                I64 _t3766 = U64_to_i64(np);
                (void)_t3766;
                ;
                U32 _t3767 = I64_to_u32(_t3766);
                (void)_t3767;
                ;
                ffd->nparam = _t3767;
                ;
                ExprData *_t3768 = ExprData_FuncDef(ffd);
                (void)_t3768;
                FunctionDef_delete(ffd, &(Bool){1});
                Expr *fdef = Expr_new(_t3768, t_line, t_col, &p->path);
                (void)fdef;
                ExprData_delete(_t3768, &(Bool){1});
                Expr_add_child(fdef, body);
                Bool _t3769 = Bool_clone(&(Bool){is_mut});
                (void)_t3769;
                Bool _t3770 = 0;
                (void)_t3770;
                Bool _t3771 = 0;
                (void)_t3771;
                Bool _t3772 = Bool_clone(&(Bool){is_own});
                (void)_t3772;
                I32 _t3773 = 0;
                (void)_t3773;
                I32 _t3774 = 0;
                (void)_t3774;
                Declaration *dd = malloc(sizeof(Declaration));
                { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
                { Str *_ca = Str_clone(type_name); dd->explicit_type = *_ca; free(_ca); }
                dd->is_mut = _t3769;
                dd->is_namespace = _t3770;
                dd->is_ref = _t3771;
                dd->is_own = _t3772;
                dd->field_offset = _t3773;
                dd->field_size = _t3774;
                dd->field_struct_def = NULL;
                dd->fn_sig = NULL;
                (void)dd;
                ;
                ;
                ;
                ;
                ;
                ;
                ExprData *_t3775 = ExprData_Decl(dd);
                (void)_t3775;
                Declaration_delete(dd, &(Bool){1});
                Expr *decl = Expr_new(_t3775, t_line, t_col, &p->path);
                (void)decl;
                ExprData_delete(_t3775, &(Bool){1});
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
        Bool _t3788 = Bool_clone(&(Bool){is_mut});
        (void)_t3788;
        Bool _t3789 = 0;
        (void)_t3789;
        Bool _t3790 = 0;
        (void)_t3790;
        Bool _t3791 = Bool_clone(&(Bool){is_own});
        (void)_t3791;
        I32 _t3792 = 0;
        (void)_t3792;
        I32 _t3793 = 0;
        (void)_t3793;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(type_name); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3788;
        dd->is_namespace = _t3789;
        dd->is_ref = _t3790;
        dd->is_own = _t3791;
        dd->field_offset = _t3792;
        dd->field_size = _t3793;
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
        ExprData *_t3794 = ExprData_Decl(dd);
        (void)_t3794;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3794, t_line, t_col, &p->path);
        (void)decl;
        ExprData_delete(_t3794, &(Bool){1});
        Expr *_t3795 = parse_expression(p);
        (void)_t3795;
        Expr_add_child(decl, _t3795);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return decl;
    }
    ;
    Bool _t3848 = check(p, TokenType_Dot());
    (void)_t3848;
    if (_t3848) {
        Str *_t3834 = Str_clone(name);
        (void)_t3834;
        ExprData *_t3835 = ExprData_Ident(_t3834);
        (void)_t3835;
        Str_delete(_t3834, &(Bool){1});
        Expr *obj = Expr_new(_t3835, t_line, t_col, &p->path);
        (void)obj;
        ExprData_delete(_t3835, &(Bool){1});
        Str *last_field = Str_lit("", 0ULL);
        (void)last_field;
        U32 last_line = 0;
        (void)last_line;
        U32 last_col = 0;
        (void)last_col;
        while (1) {
            Bool _wcond3796 = check(p, TokenType_Dot());
            (void)_wcond3796;
            if (_wcond3796) {
            } else {
                ;
                break;
            }
            ;
            Token *_t3800 = advance(p);
            (void)_t3800;
            U32 _t3801 = peek_line(p);
            (void)_t3801;
            last_line = _t3801;
            ;
            U32 _t3802 = peek_col(p);
            (void)_t3802;
            last_col = _t3802;
            ;
            last_field = expect_text(p, TokenType_Ident());
            Bool _t3803 = check(p, TokenType_Dot());
            (void)_t3803;
            if (_t3803) {
                Str *_t3797 = Str_clone(last_field);
                (void)_t3797;
                ExprData *_t3798 = ExprData_FieldAccess(_t3797);
                (void)_t3798;
                Str_delete(_t3797, &(Bool){1});
                Expr *access = Expr_new(_t3798, last_line, last_col, &p->path);
                (void)access;
                ExprData_delete(_t3798, &(Bool){1});
                Expr *_t3799 = Expr_clone(obj);
                (void)_t3799;
                Expr_add_child(access, _t3799);
                obj = Expr_clone(access);
                Expr_delete(access, &(Bool){1});
            }
            ;
        }
        Bool _t3836 = check(p, TokenType_LParen());
        (void)_t3836;
        if (_t3836) {
            Token *_t3830 = advance(p);
            (void)_t3830;
            ExprData *_t3831 = ExprData_FieldAccess(last_field);
            (void)_t3831;
            Expr *callee = Expr_new(_t3831, last_line, last_col, &p->path);
            (void)callee;
            ExprData_delete(_t3831, &(Bool){1});
            Expr *_t3832 = Expr_clone(obj);
            (void)_t3832;
            Expr_add_child(callee, _t3832);
            Expr *mcall = Expr_new(ExprData_FCall(), last_line, last_col, &p->path);
            (void)mcall;
            Expr_add_child(mcall, callee);
            while (1) {
                Bool _t3822 = check(p, TokenType_RParen());
                (void)_t3822;
                Bool _t3823 = check(p, TokenType_Eof());
                (void)_t3823;
                Bool _t3824 = Bool_not(_t3822);
                (void)_t3824;
                ;
                Bool _t3825 = Bool_not(_t3823);
                (void)_t3825;
                ;
                Bool _wcond3804 = Bool_and(_t3824, _t3825);
                (void)_wcond3804;
                ;
                ;
                if (_wcond3804) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3826 = check(p, TokenType_Ident());
                (void)_t3826;
                if (_t3826) {
                    U64 _t3815 = 1;
                    (void)_t3815;
                    U64 _t3816 = U64_add(p->pos, _t3815);
                    (void)_t3816;
                    ;
                    U64 _t3817; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3817 = *_hp; free(_hp); }
                    (void)_t3817;
                    Bool _t3818; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3816}, &(U64){_t3817}); _t3818 = *_hp; free(_hp); }
                    (void)_t3818;
                    ;
                    ;
                    if (_t3818) {
                        U64 _t3810 = 1;
                        (void)_t3810;
                        U64 _t3811 = U64_add(p->pos, _t3810);
                        (void)_t3811;
                        ;
                        I64 _t3812 = U64_to_i64(_t3811);
                        (void)_t3812;
                        ;
                        U64 *_t3813 = malloc(sizeof(U64)); *_t3813 = I64_to_u64(_t3812);
                        (void)_t3813;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3813);
                        (void)nt;
                        Bool _t3814; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3814 = *_hp; free(_hp); }
                        (void)_t3814;
                        U64_delete(_t3813, &(Bool){1});
                        if (_t3814) {
                            U32 na_line = peek_line(p);
                            (void)na_line;
                            U32 na_col = peek_col(p);
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3806 = advance(p);
                            (void)_t3806;
                            ExprData *_t3807 = ExprData_NamedArg(aname);
                            (void)_t3807;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3807, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3807, &(Bool){1});
                            ;
                            ;
                            Expr *_t3808 = parse_expression(p);
                            (void)_t3808;
                            Expr_add_child(na, _t3808);
                            Expr_add_child(mcall, na);
                            Bool _t3809 = check(p, TokenType_Comma());
                            (void)_t3809;
                            if (_t3809) {
                                Token *_t3805 = advance(p);
                                (void)_t3805;
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
                Bool _t3827 = check(p, TokenType_KwOwn());
                (void)_t3827;
                if (_t3827) {
                    Token *_t3819 = advance(p);
                    (void)_t3819;
                    Bool _t3820 = 1;
                    (void)_t3820;
                    is_own_arg = _t3820;
                    ;
                }
                ;
                Expr *marg = parse_expression(p);
                (void)marg;
                Bool _t3828 = Bool_clone(&(Bool){is_own_arg});
                (void)_t3828;
                ;
                marg->is_own_arg = _t3828;
                ;
                Expr_add_child(mcall, marg);
                Bool _t3829 = check(p, TokenType_Comma());
                (void)_t3829;
                if (_t3829) {
                    Token *_t3821 = advance(p);
                    (void)_t3821;
                }
                ;
            }
            Token *_t3833 = expect_token(p, TokenType_RParen());
            (void)_t3833;
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
        Token *_t3837 = expect_token(p, TokenType_Eq());
        (void)_t3837;
        ExprData *_t3838 = ExprData_FieldAssign(last_field);
        (void)_t3838;
        Str_delete(last_field, &(Bool){1});
        Expr *fa = Expr_new(_t3838, t_line, t_col, &p->path);
        (void)fa;
        ExprData_delete(_t3838, &(Bool){1});
        Expr *_t3839 = Expr_clone(obj);
        (void)_t3839;
        Expr_delete(obj, &(Bool){1});
        Expr_add_child(fa, _t3839);
        Expr *_t3840 = parse_expression(p);
        (void)_t3840;
        Expr_add_child(fa, _t3840);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return fa;
    }
    ;
    Bool _t3849 = check(p, TokenType_Eq());
    (void)_t3849;
    if (_t3849) {
        Token *_t3841 = advance(p);
        (void)_t3841;
        Str *_t3842 = Str_clone(name);
        (void)_t3842;
        ExprData *_t3843 = ExprData_Assign(_t3842);
        (void)_t3843;
        Str_delete(_t3842, &(Bool){1});
        Expr *assign = Expr_new(_t3843, t_line, t_col, &p->path);
        (void)assign;
        ExprData_delete(_t3843, &(Bool){1});
        Expr *_t3844 = parse_expression(p);
        (void)_t3844;
        Expr_add_child(assign, _t3844);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return assign;
    }
    ;
    Bool _t3850 = check(p, TokenType_LParen());
    (void)_t3850;
    if (_t3850) {
        Expr *_t3845 = parse_call(p, name, t_line, t_col);
        (void)_t3845;
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return _t3845;
    }
    ;
    Str *_t3851 = Str_lit("Str", 3ULL);
    (void)_t3851;
    U64 _t3852; { U64 *_hp = (U64 *)Str_size(); _t3852 = *_hp; free(_hp); }
    (void)_t3852;
    U64 _t3853 = 8;
    (void)_t3853;
    Array *_va69 = Array_new(_t3851, &(U64){_t3852}, &(U64){_t3853});
    (void)_va69;
    Str_delete(_t3851, &(Bool){1});
    ;
    ;
    U64 _t3854 = 0;
    (void)_t3854;
    Str *_t3855 = Str_clone(&p->path);
    (void)_t3855;
    Array_set(_va69, &(U64){_t3854}, _t3855);
    ;
    U64 _t3856 = 1;
    (void)_t3856;
    Str *_t3857 = Str_lit(":", 1ULL);
    (void)_t3857;
    Array_set(_va69, &(U64){_t3856}, _t3857);
    ;
    U64 _t3858 = 2;
    (void)_t3858;
    Str *_t3859 = U32_to_str(&(U32){t_line});
    (void)_t3859;
    ;
    Array_set(_va69, &(U64){_t3858}, _t3859);
    ;
    U64 _t3860 = 3;
    (void)_t3860;
    Str *_t3861 = Str_lit(":", 1ULL);
    (void)_t3861;
    Array_set(_va69, &(U64){_t3860}, _t3861);
    ;
    U64 _t3862 = 4;
    (void)_t3862;
    Str *_t3863 = U32_to_str(&(U32){t_col});
    (void)_t3863;
    ;
    Array_set(_va69, &(U64){_t3862}, _t3863);
    ;
    U64 _t3864 = 5;
    (void)_t3864;
    Str *_t3865 = Str_lit(": expected ':=', ':', '=' or '(' after identifier '", 51ULL);
    (void)_t3865;
    Array_set(_va69, &(U64){_t3864}, _t3865);
    ;
    U64 _t3866 = 6;
    (void)_t3866;
    Str *_t3867 = Str_clone(name);
    (void)_t3867;
    Str_delete(name, &(Bool){1});
    Array_set(_va69, &(U64){_t3866}, _t3867);
    ;
    U64 _t3868 = 7;
    (void)_t3868;
    Str *_t3869 = Str_lit("'", 1ULL);
    (void)_t3869;
    Array_set(_va69, &(U64){_t3868}, _t3869);
    ;
    Str *_t3870 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:797:11", 64ULL);
    (void)_t3870;
    panic(_t3870, _va69);
    Str_delete(_t3870, &(Bool){1});
    U32 _t3871 = 0;
    (void)_t3871;
    U32 _t3872 = 0;
    (void)_t3872;
    Expr *_t3873 = Expr_new(ExprData_Body(), _t3871, _t3872, &p->path);
    (void)_t3873;
    ;
    ;
    return _t3873;
}

Expr * parse_statement(Parser * p) {
    (void)p;
    U32 t_line = peek_line(p);
    (void)t_line;
    U32 t_col = peek_col(p);
    (void)t_col;
    Token *t = peek(p);
    (void)t;
    Bool _t4011; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t4011 = *_hp; free(_hp); }
    (void)_t4011;
    if (_t4011) {
        Bool _t3874 = 0;
        (void)_t3874;
        Bool _t3875 = 0;
        (void)_t3875;
        Expr *_t3876 = parse_statement_ident(p, _t3874, _t3875);
        (void)_t3876;
        ;
        ;
        ;
        ;
        ;
        return _t3876;
    }
    ;
    Bool _t4012; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwRef()); _t4012 = *_hp; free(_hp); }
    (void)_t4012;
    if (_t4012) {
        Token *_t3883 = advance(p);
        (void)_t3883;
        Bool ref_mut = 0;
        (void)ref_mut;
        Bool _t3884 = check(p, TokenType_KwMut());
        (void)_t3884;
        if (_t3884) {
            Token *_t3877 = advance(p);
            (void)_t3877;
            Bool _t3878 = 1;
            (void)_t3878;
            ref_mut = _t3878;
            ;
        }
        ;
        U32 i_line = peek_line(p);
        (void)i_line;
        U32 i_col = peek_col(p);
        (void)i_col;
        Str *iname = expect_text(p, TokenType_Ident());
        (void)iname;
        Bool _t3885 = 0;
        (void)_t3885;
        Bool _t3886 = 0;
        (void)_t3886;
        Bool _t3887 = 1;
        (void)_t3887;
        Bool _t3888 = 0;
        (void)_t3888;
        I32 _t3889 = 0;
        (void)_t3889;
        I32 _t3890 = 0;
        (void)_t3890;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(iname); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3885;
        dd->is_namespace = _t3886;
        dd->is_ref = _t3887;
        dd->is_own = _t3888;
        dd->field_offset = _t3889;
        dd->field_size = _t3890;
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
            Bool _t3879 = 1;
            (void)_t3879;
            dd->is_mut = _t3879;
            ;
        }
        ;
        Bool _t3891 = check(p, TokenType_Colon());
        (void)_t3891;
        if (_t3891) {
            Token *_t3880 = advance(p);
            (void)_t3880;
            Str_delete(&dd->explicit_type, &(Bool){0});
            { Str *_fa = expect_text(p, TokenType_Ident()); dd->explicit_type = *_fa; free(_fa); }
            Token *_t3881 = expect_token(p, TokenType_Eq());
            (void)_t3881;
        } else {
            Token *_t3882 = expect_token(p, TokenType_ColonEq());
            (void)_t3882;
        }
        ;
        ExprData *_t3892 = ExprData_Decl(dd);
        (void)_t3892;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3892, i_line, i_col, &p->path);
        (void)decl;
        ExprData_delete(_t3892, &(Bool){1});
        ;
        ;
        Expr *_t3893 = parse_expression(p);
        (void)_t3893;
        Expr_add_child(decl, _t3893);
        ;
        ;
        ;
        return decl;
    }
    ;
    Bool _t4013; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMut()); _t4013 = *_hp; free(_hp); }
    (void)_t4013;
    if (_t4013) {
        Token *_t3894 = advance(p);
        (void)_t3894;
        Bool _t3895 = 1;
        (void)_t3895;
        Bool _t3896 = 0;
        (void)_t3896;
        Expr *_t3897 = parse_statement_ident(p, _t3895, _t3896);
        (void)_t3897;
        ;
        ;
        ;
        ;
        ;
        return _t3897;
    }
    ;
    Bool _t4014; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwReturn()); _t4014 = *_hp; free(_hp); }
    (void)_t4014;
    if (_t4014) {
        Token *_t3899 = advance(p);
        (void)_t3899;
        Expr *ret = Expr_new(ExprData_Return(), t_line, t_col, &p->path);
        (void)ret;
        Bool _t3900 = check(p, TokenType_RBrace());
        (void)_t3900;
        Bool _t3901 = check(p, TokenType_Eof());
        (void)_t3901;
        Bool _t3902 = Bool_not(_t3900);
        (void)_t3902;
        ;
        Bool _t3903 = Bool_not(_t3901);
        (void)_t3903;
        ;
        Bool _t3904 = Bool_and(_t3902, _t3903);
        (void)_t3904;
        ;
        ;
        if (_t3904) {
            Expr *_t3898 = parse_expression(p);
            (void)_t3898;
            Expr_add_child(ret, _t3898);
        }
        ;
        ;
        ;
        ;
        return ret;
    }
    ;
    Bool _t4015; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwIf()); _t4015 = *_hp; free(_hp); }
    (void)_t4015;
    if (_t4015) {
        Token *_t3912 = advance(p);
        (void)_t3912;
        Expr *node = Expr_new(ExprData_If(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t3913 = parse_expression(p);
        (void)_t3913;
        Expr_add_child(node, _t3913);
        Token *_t3914 = expect_token(p, TokenType_LBrace());
        (void)_t3914;
        Expr *_t3915 = parse_block(p);
        (void)_t3915;
        Expr_add_child(node, _t3915);
        Bool _t3916 = check(p, TokenType_KwElse());
        (void)_t3916;
        if (_t3916) {
            Token *_t3910 = advance(p);
            (void)_t3910;
            Bool _t3911 = check(p, TokenType_KwIf());
            (void)_t3911;
            if (_t3911) {
                U32 _t3905 = peek_line(p);
                (void)_t3905;
                U32 _t3906 = peek_col(p);
                (void)_t3906;
                Expr *else_body = Expr_new(ExprData_Body(), _t3905, _t3906, &p->path);
                (void)else_body;
                ;
                ;
                Expr *_t3907 = parse_statement(p);
                (void)_t3907;
                Expr_add_child(else_body, _t3907);
                Expr_add_child(node, else_body);
            } else {
                Token *_t3908 = expect_token(p, TokenType_LBrace());
                (void)_t3908;
                Expr *_t3909 = parse_block(p);
                (void)_t3909;
                Expr_add_child(node, _t3909);
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
    Bool _t4016; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t4016 = *_hp; free(_hp); }
    (void)_t4016;
    Bool _t4017; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t4017 = *_hp; free(_hp); }
    (void)_t4017;
    Bool _t4018 = Bool_or(_t4016, _t4017);
    (void)_t4018;
    ;
    ;
    Bool _t4019; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t4019 = *_hp; free(_hp); }
    (void)_t4019;
    Bool _t4020 = Bool_or(_t4018, _t4019);
    (void)_t4020;
    ;
    ;
    Bool _t4021; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t4021 = *_hp; free(_hp); }
    (void)_t4021;
    Bool _t4022 = Bool_or(_t4020, _t4021);
    (void)_t4022;
    ;
    ;
    Bool _t4023; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwNull()); _t4023 = *_hp; free(_hp); }
    (void)_t4023;
    Bool _t4024 = Bool_or(_t4022, _t4023);
    (void)_t4024;
    ;
    ;
    if (_t4024) {
        Expr *_t3917 = parse_expression(p);
        (void)_t3917;
        ;
        ;
        ;
        return _t3917;
    }
    ;
    Bool _t4025; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t4025 = *_hp; free(_hp); }
    (void)_t4025;
    if (_t4025) {
        Token *_t3918 = advance(p);
        (void)_t3918;
        Expr *_t3919 = parse_block(p);
        (void)_t3919;
        ;
        ;
        ;
        return _t3919;
    }
    ;
    Bool _t4026; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwWhile()); _t4026 = *_hp; free(_hp); }
    (void)_t4026;
    if (_t4026) {
        Token *_t3920 = advance(p);
        (void)_t3920;
        Expr *node = Expr_new(ExprData_While(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t3921 = parse_expression(p);
        (void)_t3921;
        Expr_add_child(node, _t3921);
        Token *_t3922 = expect_token(p, TokenType_LBrace());
        (void)_t3922;
        Expr *_t3923 = parse_block(p);
        (void)_t3923;
        Expr_add_child(node, _t3923);
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4027; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFor()); _t4027 = *_hp; free(_hp); }
    (void)_t4027;
    if (_t4027) {
        Token *_t3925 = advance(p);
        (void)_t3925;
        U32 i_line = peek_line(p);
        (void)i_line;
        U32 i_col = peek_col(p);
        (void)i_col;
        Str *iname = expect_text(p, TokenType_Ident());
        (void)iname;
        ExprData *_t3926 = ExprData_ForIn(iname);
        (void)_t3926;
        Str_delete(iname, &(Bool){1});
        Expr *node = Expr_new(_t3926, i_line, i_col, &p->path);
        (void)node;
        ExprData_delete(_t3926, &(Bool){1});
        ;
        ;
        Bool _t3927 = check(p, TokenType_Colon());
        (void)_t3927;
        if (_t3927) {
            Token *_t3924 = advance(p);
            (void)_t3924;
            Str_delete(&node->struct_name, &(Bool){0});
            { Str *_fa = expect_text(p, TokenType_Ident()); node->struct_name = *_fa; free(_fa); }
        }
        ;
        Token *_t3928 = expect_token(p, TokenType_KwIn());
        (void)_t3928;
        Expr *_t3929 = parse_expression(p);
        (void)_t3929;
        Expr_add_child(node, _t3929);
        Token *_t3930 = expect_token(p, TokenType_LBrace());
        (void)_t3930;
        Expr *_t3931 = parse_block(p);
        (void)_t3931;
        Expr_add_child(node, _t3931);
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4028; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwSwitch()); _t4028 = *_hp; free(_hp); }
    (void)_t4028;
    if (_t4028) {
        Token *_t3955 = advance(p);
        (void)_t3955;
        Expr *node = Expr_new(ExprData_Switch(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t3956 = parse_expression(p);
        (void)_t3956;
        Expr_add_child(node, _t3956);
        Token *_t3957 = expect_token(p, TokenType_LBrace());
        (void)_t3957;
        while (1) {
            Bool _t3943 = check(p, TokenType_RBrace());
            (void)_t3943;
            Bool _t3944 = check(p, TokenType_Eof());
            (void)_t3944;
            Bool _t3945 = Bool_not(_t3943);
            (void)_t3945;
            ;
            Bool _t3946 = Bool_not(_t3944);
            (void)_t3946;
            ;
            Bool _wcond3932 = Bool_and(_t3945, _t3946);
            (void)_wcond3932;
            ;
            ;
            if (_wcond3932) {
            } else {
                ;
                break;
            }
            ;
            Token *_t3947 = expect_token(p, TokenType_KwCase());
            (void)_t3947;
            U32 _t3948 = peek_line(p);
            (void)_t3948;
            U32 _t3949 = peek_col(p);
            (void)_t3949;
            Expr *cn = Expr_new(ExprData_Case(), _t3948, _t3949, &p->path);
            (void)cn;
            ;
            ;
            Bool _t3950 = check(p, TokenType_Colon());
            (void)_t3950;
            Bool _t3951 = Bool_not(_t3950);
            (void)_t3951;
            ;
            if (_t3951) {
                Expr *_t3933 = parse_expression(p);
                (void)_t3933;
                Expr_add_child(cn, _t3933);
            }
            ;
            Token *_t3952 = expect_token(p, TokenType_Colon());
            (void)_t3952;
            U32 _t3953 = peek_line(p);
            (void)_t3953;
            U32 _t3954 = peek_col(p);
            (void)_t3954;
            Expr *cb = Expr_new(ExprData_Body(), _t3953, _t3954, &p->path);
            (void)cb;
            ;
            ;
            while (1) {
                Bool _t3935 = check(p, TokenType_KwCase());
                (void)_t3935;
                Bool _t3936 = check(p, TokenType_RBrace());
                (void)_t3936;
                Bool _t3937 = Bool_not(_t3935);
                (void)_t3937;
                ;
                Bool _t3938 = Bool_not(_t3936);
                (void)_t3938;
                ;
                Bool _t3939 = check(p, TokenType_Eof());
                (void)_t3939;
                Bool _t3940 = Bool_and(_t3937, _t3938);
                (void)_t3940;
                ;
                ;
                Bool _t3941 = Bool_not(_t3939);
                (void)_t3941;
                ;
                Bool _wcond3934 = Bool_and(_t3940, _t3941);
                (void)_wcond3934;
                ;
                ;
                if (_wcond3934) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3942 = parse_statement(p);
                (void)_t3942;
                Expr_add_child(cb, _t3942);
            }
            Expr_add_child(cn, cb);
            Expr_add_child(node, cn);
        }
        Token *_t3958 = expect_token(p, TokenType_RBrace());
        (void)_t3958;
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4029; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwOwn()); _t4029 = *_hp; free(_hp); }
    (void)_t4029;
    if (_t4029) {
        Token *_t4000 = advance(p);
        (void)_t4000;
        Bool _t4001 = check(p, TokenType_Ident());
        (void)_t4001;
        Bool _t4002 = check(p, TokenType_KwMut());
        (void)_t4002;
        Bool _t4003 = Bool_or(_t4001, _t4002);
        (void)_t4003;
        ;
        ;
        if (_t4003) {
            Bool own_mut = 0;
            (void)own_mut;
            Bool _t3990 = check(p, TokenType_KwMut());
            (void)_t3990;
            if (_t3990) {
                Token *_t3959 = advance(p);
                (void)_t3959;
                Bool _t3960 = 1;
                (void)_t3960;
                own_mut = _t3960;
                ;
            }
            ;
            Bool _t3991 = check(p, TokenType_Ident());
            (void)_t3991;
            if (_t3991) {
                U64 _t3970 = 1;
                (void)_t3970;
                U64 _t3971 = U64_add(p->pos, _t3970);
                (void)_t3971;
                ;
                U64 _t3972; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3972 = *_hp; free(_hp); }
                (void)_t3972;
                Bool _t3973; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3971}, &(U64){_t3972}); _t3973 = *_hp; free(_hp); }
                (void)_t3973;
                ;
                ;
                if (_t3973) {
                    U64 _t3963 = 1;
                    (void)_t3963;
                    U64 _t3964 = U64_add(p->pos, _t3963);
                    (void)_t3964;
                    ;
                    I64 _t3965 = U64_to_i64(_t3964);
                    (void)_t3965;
                    ;
                    U64 *_t3966 = malloc(sizeof(U64)); *_t3966 = I64_to_u64(_t3965);
                    (void)_t3966;
                    ;
                    Token *nt = Vec_get(&p->tokens, _t3966);
                    (void)nt;
                    Bool _t3967; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_ColonEq()); _t3967 = *_hp; free(_hp); }
                    (void)_t3967;
                    Bool _t3968; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Colon()); _t3968 = *_hp; free(_hp); }
                    (void)_t3968;
                    U64_delete(_t3966, &(Bool){1});
                    Bool _t3969 = Bool_or(_t3967, _t3968);
                    (void)_t3969;
                    ;
                    ;
                    if (_t3969) {
                        Bool _t3961 = 1;
                        (void)_t3961;
                        Expr *_t3962 = parse_statement_ident(p, own_mut, _t3961);
                        (void)_t3962;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        return _t3962;
                    }
                    ;
                }
                ;
            }
            ;
            if (own_mut) {
                Str *_t3974 = Str_lit("Str", 3ULL);
                (void)_t3974;
                U64 _t3975; { U64 *_hp = (U64 *)Str_size(); _t3975 = *_hp; free(_hp); }
                (void)_t3975;
                U64 _t3976 = 6;
                (void)_t3976;
                Array *_va70 = Array_new(_t3974, &(U64){_t3975}, &(U64){_t3976});
                (void)_va70;
                Str_delete(_t3974, &(Bool){1});
                ;
                ;
                U64 _t3977 = 0;
                (void)_t3977;
                Str *_t3978 = Str_clone(&p->path);
                (void)_t3978;
                Array_set(_va70, &(U64){_t3977}, _t3978);
                ;
                U64 _t3979 = 1;
                (void)_t3979;
                Str *_t3980 = Str_lit(":", 1ULL);
                (void)_t3980;
                Array_set(_va70, &(U64){_t3979}, _t3980);
                ;
                U64 _t3981 = 2;
                (void)_t3981;
                Str *_t3982 = U32_to_str(&(U32){t_line});
                (void)_t3982;
                Array_set(_va70, &(U64){_t3981}, _t3982);
                ;
                U64 _t3983 = 3;
                (void)_t3983;
                Str *_t3984 = Str_lit(":", 1ULL);
                (void)_t3984;
                Array_set(_va70, &(U64){_t3983}, _t3984);
                ;
                U64 _t3985 = 4;
                (void)_t3985;
                Str *_t3986 = U32_to_str(&(U32){t_col});
                (void)_t3986;
                Array_set(_va70, &(U64){_t3985}, _t3986);
                ;
                U64 _t3987 = 5;
                (void)_t3987;
                Str *_t3988 = Str_lit(": expected identifier after 'own mut'", 37ULL);
                (void)_t3988;
                Array_set(_va70, &(U64){_t3987}, _t3988);
                ;
                Str *_t3989 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:931:23", 64ULL);
                (void)_t3989;
                panic(_t3989, _va70);
                Str_delete(_t3989, &(Bool){1});
            }
            ;
        }
        ;
        Expr *expr = parse_expression(p);
        (void)expr;
        I64 _t4004 = 0;
        (void)_t4004;
        I64 _t4005 = 1;
        (void)_t4005;
        I64 primary_idx = I64_sub(_t4004, _t4005);
        (void)primary_idx;
        ;
        ;
        ;
        Expr *cur = Expr_clone(expr);
        (void)cur;
        while (1) {
            U64 _t3993; { U64 *_hp = (U64 *)Vec_len(&cur->children); _t3993 = *_hp; free(_hp); }
            (void)_t3993;
            U64 _t3994 = 0;
            (void)_t3994;
            Bool _t3995; { Bool *_hp = (Bool *)ExprData_is_FCall(&cur->data); _t3995 = *_hp; free(_hp); }
            (void)_t3995;
            Bool _t3996; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(&cur->data); _t3996 = *_hp; free(_hp); }
            (void)_t3996;
            Bool _t3997; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3993}, &(U64){_t3994}); _t3997 = *_hp; free(_hp); }
            (void)_t3997;
            ;
            ;
            Bool _t3998 = Bool_or(_t3995, _t3996);
            (void)_t3998;
            ;
            ;
            Bool _wcond3992 = Bool_and(_t3997, _t3998);
            (void)_wcond3992;
            ;
            ;
            if (_wcond3992) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t3999 = malloc(sizeof(U64));
            *_t3999 = 0;
            (void)_t3999;
            Expr *ch = Vec_get(&cur->children, _t3999);
            (void)ch;
            cur = Expr_clone(ch);
            U64_delete(_t3999, &(Bool){1});
        }
        Bool _t4006 = 1;
        (void)_t4006;
        cur->is_own_arg = _t4006;
        ;
        Expr_delete(cur, &(Bool){1});
        ;
        ;
        ;
        ;
        return expr;
    }
    ;
    Bool _t4030; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwBreak()); _t4030 = *_hp; free(_hp); }
    (void)_t4030;
    if (_t4030) {
        Token *_t4007 = advance(p);
        (void)_t4007;
        Expr *_t4008 = Expr_new(ExprData_Break(), t_line, t_col, &p->path);
        (void)_t4008;
        ;
        ;
        ;
        return _t4008;
    }
    ;
    Bool _t4031; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwContinue()); _t4031 = *_hp; free(_hp); }
    (void)_t4031;
    if (_t4031) {
        Token *_t4009 = advance(p);
        (void)_t4009;
        Expr *_t4010 = Expr_new(ExprData_Continue(), t_line, t_col, &p->path);
        (void)_t4010;
        ;
        ;
        ;
        return _t4010;
    }
    ;
    Str *_t4032 = Str_lit("Str", 3ULL);
    (void)_t4032;
    U64 _t4033; { U64 *_hp = (U64 *)Str_size(); _t4033 = *_hp; free(_hp); }
    (void)_t4033;
    U64 _t4034 = 8;
    (void)_t4034;
    Array *_va71 = Array_new(_t4032, &(U64){_t4033}, &(U64){_t4034});
    (void)_va71;
    Str_delete(_t4032, &(Bool){1});
    ;
    ;
    U64 _t4035 = 0;
    (void)_t4035;
    Str *_t4036 = Str_clone(&p->path);
    (void)_t4036;
    Array_set(_va71, &(U64){_t4035}, _t4036);
    ;
    U64 _t4037 = 1;
    (void)_t4037;
    Str *_t4038 = Str_lit(":", 1ULL);
    (void)_t4038;
    Array_set(_va71, &(U64){_t4037}, _t4038);
    ;
    U64 _t4039 = 2;
    (void)_t4039;
    Str *_t4040 = U32_to_str(&(U32){t_line});
    (void)_t4040;
    ;
    Array_set(_va71, &(U64){_t4039}, _t4040);
    ;
    U64 _t4041 = 3;
    (void)_t4041;
    Str *_t4042 = Str_lit(":", 1ULL);
    (void)_t4042;
    Array_set(_va71, &(U64){_t4041}, _t4042);
    ;
    U64 _t4043 = 4;
    (void)_t4043;
    Str *_t4044 = U32_to_str(&(U32){t_col});
    (void)_t4044;
    ;
    Array_set(_va71, &(U64){_t4043}, _t4044);
    ;
    U64 _t4045 = 5;
    (void)_t4045;
    Str *_t4046 = Str_lit(": expected statement, found '", 29ULL);
    (void)_t4046;
    Array_set(_va71, &(U64){_t4045}, _t4046);
    ;
    U64 _t4047 = 6;
    (void)_t4047;
    Str *_t4048 = Str_clone(&t->text);
    (void)_t4048;
    Array_set(_va71, &(U64){_t4047}, _t4048);
    ;
    U64 _t4049 = 7;
    (void)_t4049;
    Str *_t4050 = Str_lit("'", 1ULL);
    (void)_t4050;
    Array_set(_va71, &(U64){_t4049}, _t4050);
    ;
    Str *_t4051 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:958:11", 64ULL);
    (void)_t4051;
    panic(_t4051, _va71);
    Str_delete(_t4051, &(Bool){1});
    U32 _t4052 = 0;
    (void)_t4052;
    U32 _t4053 = 0;
    (void)_t4053;
    Expr *_t4054 = Expr_new(ExprData_Body(), _t4052, _t4053, &p->path);
    (void)_t4054;
    ;
    ;
    return _t4054;
}

Expr * parse(Vec * tokens, Str * path, Str * mode_out) {
    (void)tokens;
    (void)path;
    (void)mode_out;
    Str *_t4074 = Str_lit("Expr", 4ULL);
    (void)_t4074;
    U64 _t4075; { U64 *_hp = (U64 *)Expr_size(); _t4075 = *_hp; free(_hp); }
    (void)_t4075;
    I64 _t4076 = 0;
    (void)_t4076;
    Parser *p = malloc(sizeof(Parser));
    { Vec *_ca = Vec_clone(tokens); p->tokens = *_ca; free(_ca); }
    p->pos = _t4076;
    { Str *_ca = Str_clone(path); p->path = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t4074, &(U64){_t4075}); p->fn_sig_decls = *_ca; free(_ca); }
    (void)p;
    Str_delete(_t4074, &(Bool){1});
    ;
    ;
    Bool _t4077 = check(p, TokenType_KwMode());
    (void)_t4077;
    if (_t4077) {
        Token *_t4059 = advance(p);
        (void)_t4059;
        Bool _t4060 = check(p, TokenType_Ident());
        (void)_t4060;
        Bool _t4061 = check(p, TokenType_KwTest());
        (void)_t4061;
        Bool _t4062 = Bool_or(_t4060, _t4061);
        (void)_t4062;
        ;
        ;
        if (_t4062) {
            Str *_t4055 = Str_clone(&peek(p)->text);
            (void)_t4055;
            U64 _t4056; { U64 *_hp = (U64 *)Str_size(); _t4056 = *_hp; free(_hp); }
            (void)_t4056;
            swap(mode_out, _t4055, _t4056);
            Str_delete(_t4055, &(Bool){1});
            ;
            Token *_t4057 = advance(p);
            (void)_t4057;
        } else {
            Token *_t4058 = expect_token(p, TokenType_Ident());
            (void)_t4058;
        }
        ;
    }
    ;
    U32 _t4078 = 1;
    (void)_t4078;
    U32 _t4079 = 1;
    (void)_t4079;
    Expr *root = Expr_new(ExprData_Body(), _t4078, _t4079, &p->path);
    (void)root;
    ;
    ;
    while (1) {
        Bool _t4064 = check(p, TokenType_Eof());
        (void)_t4064;
        Bool _wcond4063 = Bool_not(_t4064);
        (void)_wcond4063;
        ;
        if (_wcond4063) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t4065 = parse_statement(p);
        (void)_t4065;
        Expr_add_child(root, _t4065);
    }
    {
        U64 _t4072 = 0;
        (void)_t4072;
        U64 _t4073; { U64 *_hp = (U64 *)Vec_len(&p->fn_sig_decls); _t4073 = *_hp; free(_hp); }
        (void)_t4073;
        Range *_fc4066 = Range_new(_t4072, _t4073);
        (void)_fc4066;
        ;
        ;
        U64 _fi4066 = 0;
        (void)_fi4066;
        while (1) {
            U64 _t4068; { U64 *_hp = (U64 *)Range_len(_fc4066); _t4068 = *_hp; free(_hp); }
            (void)_t4068;
            Bool _wcond4067; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi4066}, &(U64){_t4068}); _wcond4067 = *_hp; free(_hp); }
            (void)_wcond4067;
            ;
            if (_wcond4067) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc4066, _fi4066);
            (void)i;
            U64 _t4069 = 1;
            (void)_t4069;
            U64 _t4070 = U64_add(_fi4066, _t4069);
            (void)_t4070;
            ;
            _fi4066 = _t4070;
            ;
            Expr *d = Vec_get(&p->fn_sig_decls, i);
            (void)d;
            Expr *_t4071 = Expr_clone(d);
            (void)_t4071;
            U64_delete(i, &(Bool){1});
            Expr_add_child(root, _t4071);
        }
        Range_delete(_fc4066, &(Bool){1});
        ;
    }
    Parser_delete(p, &(Bool){1});
    return root;
}

