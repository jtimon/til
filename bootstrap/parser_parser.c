#include "parser_parser.h"

Parser * Parser_clone(Parser * self) {
    (void)self;
    U32 _t3033 = U32_clone(&self->count);
    (void)_t3033;
    U32 _t3034 = U32_clone(&self->pos);
    (void)_t3034;
    Parser *_t3035 = malloc(sizeof(Parser));
    { Vec *_ca = Vec_clone(&self->tokens); _t3035->tokens = *_ca; free(_ca); }
    _t3035->count = _t3033;
    _t3035->pos = _t3034;
    { Str *_ca = Str_clone(&self->path); _t3035->path = *_ca; free(_ca); }
    (void)_t3035;
    ;
    ;
    return _t3035;
}

U64 *Parser_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Parser);
    return r;
}

Token * peek(Parser * p) {
    (void)p;
    I64 _t3041 = U32_to_i64(p->pos);
    (void)_t3041;
    U64 *_t3042 = malloc(sizeof(U64)); *_t3042 = I64_to_u64(_t3041);
    (void)_t3042;
    ;
    Token *t = Vec_get(&p->tokens, _t3042);
    (void)t;
    U64_delete(_t3042, &(Bool){1});
    return t;
}

Token * advance(Parser * p) {
    (void)p;
    I64 _t3045 = U32_to_i64(p->pos);
    (void)_t3045;
    U64 *_t3046 = malloc(sizeof(U64)); *_t3046 = I64_to_u64(_t3045);
    (void)_t3046;
    ;
    Token *t = Vec_get(&p->tokens, _t3046);
    (void)t;
    Bool _t3047; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Eof()); _t3047 = *_hp; free(_hp); }
    (void)_t3047;
    Bool _t3048 = Bool_not(_t3047);
    (void)_t3048;
    ;
    if (_t3048) {
        U32 _t3043 = 1;
        (void)_t3043;
        U32 _t3044 = U32_add(p->pos, _t3043);
        (void)_t3044;
        ;
        p->pos = _t3044;
        ;
    }
    ;
    U64_delete(_t3046, &(Bool){1});
    return t;
}

Bool * check(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Bool _t3049; { Bool *_hp = (Bool *)TokenType_eq(&peek(p)->type, type); _t3049 = *_hp; free(_hp); }
    (void)_t3049;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t3049; return _r; }
}

void expect_token(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Token *t = peek(p);
    (void)t;
    Bool _t3074; { Bool *_hp = (Bool *)TokenType_eq(&t->type, type); _t3074 = *_hp; free(_hp); }
    (void)_t3074;
    Bool _t3075 = Bool_not(_t3074);
    (void)_t3075;
    ;
    if (_t3075) {
        Str *_t3050 = Str_lit("Str", 3ULL);
        (void)_t3050;
        U64 _t3051; { U64 *_hp = (U64 *)Str_size(); _t3051 = *_hp; free(_hp); }
        (void)_t3051;
        U64 _t3052 = 10;
        (void)_t3052;
        Array *_va54 = Array_new(_t3050, &(U64){_t3051}, &(U64){_t3052});
        (void)_va54;
        Str_delete(_t3050, &(Bool){1});
        ;
        ;
        U64 _t3053 = 0;
        (void)_t3053;
        Str *_t3054 = Str_clone(&p->path);
        (void)_t3054;
        Array_set(_va54, &(U64){_t3053}, _t3054);
        ;
        U64 _t3055 = 1;
        (void)_t3055;
        Str *_t3056 = Str_lit(":", 1ULL);
        (void)_t3056;
        Array_set(_va54, &(U64){_t3055}, _t3056);
        ;
        U64 _t3057 = 2;
        (void)_t3057;
        Str *_t3058 = U32_to_str(&t->line);
        (void)_t3058;
        Array_set(_va54, &(U64){_t3057}, _t3058);
        ;
        U64 _t3059 = 3;
        (void)_t3059;
        Str *_t3060 = Str_lit(":", 1ULL);
        (void)_t3060;
        Array_set(_va54, &(U64){_t3059}, _t3060);
        ;
        U64 _t3061 = 4;
        (void)_t3061;
        Str *_t3062 = U32_to_str(&t->col);
        (void)_t3062;
        Array_set(_va54, &(U64){_t3061}, _t3062);
        ;
        U64 _t3063 = 5;
        (void)_t3063;
        Str *_t3064 = Str_lit(": expected '", 12ULL);
        (void)_t3064;
        Array_set(_va54, &(U64){_t3063}, _t3064);
        ;
        U64 _t3065 = 6;
        (void)_t3065;
        Str *_t3066 = tok_name(type);
        (void)_t3066;
        Array_set(_va54, &(U64){_t3065}, _t3066);
        ;
        U64 _t3067 = 7;
        (void)_t3067;
        Str *_t3068 = Str_lit("', found '", 10ULL);
        (void)_t3068;
        Array_set(_va54, &(U64){_t3067}, _t3068);
        ;
        U64 _t3069 = 8;
        (void)_t3069;
        Str *_t3070 = Str_clone(&t->text);
        (void)_t3070;
        Array_set(_va54, &(U64){_t3069}, _t3070);
        ;
        U64 _t3071 = 9;
        (void)_t3071;
        Str *_t3072 = Str_lit("'", 1ULL);
        (void)_t3072;
        Array_set(_va54, &(U64){_t3071}, _t3072);
        ;
        Str *_t3073 = Str_lit("src/self/parser.til:35:15", 25ULL);
        (void)_t3073;
        panic(_t3073, _va54);
        Str_delete(_t3073, &(Bool){1});
    }
    ;
    Token *_t3076 = advance(p);
    (void)_t3076;
}

Str * expect_text(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Token *t = peek(p);
    (void)t;
    Bool _t3101; { Bool *_hp = (Bool *)TokenType_eq(&t->type, type); _t3101 = *_hp; free(_hp); }
    (void)_t3101;
    Bool _t3102 = Bool_not(_t3101);
    (void)_t3102;
    ;
    if (_t3102) {
        Str *_t3077 = Str_lit("Str", 3ULL);
        (void)_t3077;
        U64 _t3078; { U64 *_hp = (U64 *)Str_size(); _t3078 = *_hp; free(_hp); }
        (void)_t3078;
        U64 _t3079 = 10;
        (void)_t3079;
        Array *_va55 = Array_new(_t3077, &(U64){_t3078}, &(U64){_t3079});
        (void)_va55;
        Str_delete(_t3077, &(Bool){1});
        ;
        ;
        U64 _t3080 = 0;
        (void)_t3080;
        Str *_t3081 = Str_clone(&p->path);
        (void)_t3081;
        Array_set(_va55, &(U64){_t3080}, _t3081);
        ;
        U64 _t3082 = 1;
        (void)_t3082;
        Str *_t3083 = Str_lit(":", 1ULL);
        (void)_t3083;
        Array_set(_va55, &(U64){_t3082}, _t3083);
        ;
        U64 _t3084 = 2;
        (void)_t3084;
        Str *_t3085 = U32_to_str(&t->line);
        (void)_t3085;
        Array_set(_va55, &(U64){_t3084}, _t3085);
        ;
        U64 _t3086 = 3;
        (void)_t3086;
        Str *_t3087 = Str_lit(":", 1ULL);
        (void)_t3087;
        Array_set(_va55, &(U64){_t3086}, _t3087);
        ;
        U64 _t3088 = 4;
        (void)_t3088;
        Str *_t3089 = U32_to_str(&t->col);
        (void)_t3089;
        Array_set(_va55, &(U64){_t3088}, _t3089);
        ;
        U64 _t3090 = 5;
        (void)_t3090;
        Str *_t3091 = Str_lit(": expected '", 12ULL);
        (void)_t3091;
        Array_set(_va55, &(U64){_t3090}, _t3091);
        ;
        U64 _t3092 = 6;
        (void)_t3092;
        Str *_t3093 = tok_name(type);
        (void)_t3093;
        Array_set(_va55, &(U64){_t3092}, _t3093);
        ;
        U64 _t3094 = 7;
        (void)_t3094;
        Str *_t3095 = Str_lit("', found '", 10ULL);
        (void)_t3095;
        Array_set(_va55, &(U64){_t3094}, _t3095);
        ;
        U64 _t3096 = 8;
        (void)_t3096;
        Str *_t3097 = Str_clone(&t->text);
        (void)_t3097;
        Array_set(_va55, &(U64){_t3096}, _t3097);
        ;
        U64 _t3098 = 9;
        (void)_t3098;
        Str *_t3099 = Str_lit("'", 1ULL);
        (void)_t3099;
        Array_set(_va55, &(U64){_t3098}, _t3099);
        ;
        Str *_t3100 = Str_lit("src/self/parser.til:45:15", 25ULL);
        (void)_t3100;
        panic(_t3100, _va55);
        Str_delete(_t3100, &(Bool){1});
    }
    ;
    Str *text = Str_clone(&t->text);
    (void)text;
    Token *_t3103 = advance(p);
    (void)_t3103;
    return text;
}

U32 * peek_line(Parser * p) {
    (void)p;
    { U32 *_r = malloc(sizeof(U32)); *_r = peek(p)->line; return _r; }
}

U32 * peek_col(Parser * p) {
    (void)p;
    { U32 *_r = malloc(sizeof(U32)); *_r = peek(p)->col; return _r; }
}

Expr * parse_fn_signature(Parser * p, U32 * line, U32 * col) {
    (void)p;
    (void)line;
    (void)col;
    Bool _t3139; { Bool *_hp = (Bool *)check(p, TokenType_LParen()); _t3139 = *_hp; free(_hp); }
    (void)_t3139;
    Bool _t3140 = Bool_not(_t3139);
    (void)_t3140;
    ;
    if (_t3140) {
        U32 _t3104 = 0;
        (void)_t3104;
        U32 _t3105 = 0;
        (void)_t3105;
        Str *_t3106 = Str_lit("", 0ULL);
        (void)_t3106;
        Expr *_t3107 = Expr_new(ExprData_Body(), _t3104, _t3105, _t3106);
        (void)_t3107;
        ;
        ;
        Str_delete(_t3106, &(Bool){1});
        ;
        return _t3107;
    }
    ;
    Token *_t3141 = advance(p);
    (void)_t3141;
    Str *_t3142 = Str_lit("Str", 3ULL);
    (void)_t3142;
    U64 _t3143; { U64 *_hp = (U64 *)Str_size(); _t3143 = *_hp; free(_hp); }
    (void)_t3143;
    Vec *ptypes = Vec_new(_t3142, &(U64){_t3143});
    (void)ptypes;
    Str_delete(_t3142, &(Bool){1});
    ;
    Str *_t3144 = Str_lit("Bool", 4ULL);
    (void)_t3144;
    U64 _t3145; { U64 *_hp = (U64 *)Bool_size(); _t3145 = *_hp; free(_hp); }
    (void)_t3145;
    Vec *pmuts = Vec_new(_t3144, &(U64){_t3145});
    (void)pmuts;
    Str_delete(_t3144, &(Bool){1});
    ;
    while (1) {
        Bool _t3112; { Bool *_hp = (Bool *)check(p, TokenType_RParen()); _t3112 = *_hp; free(_hp); }
        (void)_t3112;
        Bool _t3113; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3113 = *_hp; free(_hp); }
        (void)_t3113;
        Bool _t3114 = Bool_not(_t3112);
        (void)_t3114;
        ;
        Bool _t3115 = Bool_not(_t3113);
        (void)_t3115;
        ;
        Bool _wcond3108 = Bool_and(_t3114, _t3115);
        (void)_wcond3108;
        ;
        ;
        if (_wcond3108) {
        } else {
            ;
            break;
        }
        ;
        Bool is_mut = 0;
        (void)is_mut;
        Bool _t3116; { Bool *_hp = (Bool *)check(p, TokenType_KwMut()); _t3116 = *_hp; free(_hp); }
        (void)_t3116;
        if (_t3116) {
            Token *_t3109 = advance(p);
            (void)_t3109;
            Bool _t3110 = 1;
            (void)_t3110;
            is_mut = _t3110;
            ;
        }
        ;
        Str *ptype = expect_text(p, TokenType_Ident());
        (void)ptype;
        Vec_push(ptypes, ptype);
        Vec_push(pmuts, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = is_mut; _oa; }));
        Bool _t3117; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3117 = *_hp; free(_hp); }
        (void)_t3117;
        if (_t3117) {
            Token *_t3111 = advance(p);
            (void)_t3111;
        }
        ;
    }
    expect_token(p, TokenType_RParen());
    Str *return_type = Str_lit("", 0ULL);
    (void)return_type;
    Bool _t3146; { Bool *_hp = (Bool *)check(p, TokenType_KwReturns()); _t3146 = *_hp; free(_hp); }
    (void)_t3146;
    if (_t3146) {
        Token *_t3118 = advance(p);
        (void)_t3118;
        return_type = expect_text(p, TokenType_Ident());
    }
    ;
    Str *_t3147 = Str_lit("Str", 3ULL);
    (void)_t3147;
    U64 _t3148; { U64 *_hp = (U64 *)Str_size(); _t3148 = *_hp; free(_hp); }
    (void)_t3148;
    Str *_t3149 = Str_lit("Str", 3ULL);
    (void)_t3149;
    U64 _t3150; { U64 *_hp = (U64 *)Str_size(); _t3150 = *_hp; free(_hp); }
    (void)_t3150;
    Str *_t3151 = Str_lit("Bool", 4ULL);
    (void)_t3151;
    U64 _t3152; { U64 *_hp = (U64 *)Bool_size(); _t3152 = *_hp; free(_hp); }
    (void)_t3152;
    Str *_t3153 = Str_lit("Bool", 4ULL);
    (void)_t3153;
    U64 _t3154; { U64 *_hp = (U64 *)Bool_size(); _t3154 = *_hp; free(_hp); }
    (void)_t3154;
    Str *_t3155 = Str_lit("Bool", 4ULL);
    (void)_t3155;
    U64 _t3156; { U64 *_hp = (U64 *)Bool_size(); _t3156 = *_hp; free(_hp); }
    (void)_t3156;
    Str *_t3157 = Str_lit("I64", 3ULL);
    (void)_t3157;
    U64 _t3158; { U64 *_hp = (U64 *)I64_size(); _t3158 = *_hp; free(_hp); }
    (void)_t3158;
    Str *_t3159 = Str_lit("I64", 3ULL);
    (void)_t3159;
    U64 _t3160; { U64 *_hp = (U64 *)I64_size(); _t3160 = *_hp; free(_hp); }
    (void)_t3160;
    I64 _t3161 = 0;
    (void)_t3161;
    I64 _t3162 = 1;
    (void)_t3162;
    I64 _t3163 = I64_sub(_t3161, _t3162);
    (void)_t3163;
    ;
    ;
    I64 _t3164 = 0;
    (void)_t3164;
    I64 _t3165 = 1;
    (void)_t3165;
    I64 _t3166 = I64_sub(_t3164, _t3165);
    (void)_t3166;
    ;
    ;
    U32 _t3167 = 0;
    (void)_t3167;
    I32 _t3168 = I64_to_i32(_t3163);
    (void)_t3168;
    ;
    I32 _t3169 = I64_to_i32(_t3166);
    (void)_t3169;
    ;
    Bool _t3170 = 0;
    (void)_t3170;
    Bool _t3171 = 0;
    (void)_t3171;
    FunctionDef *fd = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(FuncType_Func()); fd->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3147, &(U64){_t3148}); fd->param_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3149, &(U64){_t3150}); fd->param_types = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3151, &(U64){_t3152}); fd->param_muts = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3153, &(U64){_t3154}); fd->param_owns = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3155, &(U64){_t3156}); fd->param_shallows = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3157, &(U64){_t3158}); fd->param_fn_sigs = *_ca; free(_ca); }
    fd->nparam = _t3167;
    { Vec *_ca = Vec_new(_t3159, &(U64){_t3160}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3168;
    fd->kwargs_index = _t3169;
    fd->return_is_ref = _t3170;
    fd->return_is_shallow = _t3171;
    (void)fd;
    Str_delete(_t3147, &(Bool){1});
    ;
    Str_delete(_t3149, &(Bool){1});
    ;
    Str_delete(_t3151, &(Bool){1});
    ;
    Str_delete(_t3153, &(Bool){1});
    ;
    Str_delete(_t3155, &(Bool){1});
    ;
    Str_delete(_t3157, &(Bool){1});
    ;
    Str_delete(_t3159, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    U64 _t3172; { U64 *_hp = (U64 *)Str_len(return_type); _t3172 = *_hp; free(_hp); }
    (void)_t3172;
    U64 _t3173 = 0;
    (void)_t3173;
    Bool _t3174; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3172}, &(U64){_t3173}); _t3174 = *_hp; free(_hp); }
    (void)_t3174;
    ;
    ;
    if (_t3174) {
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
    Bool _t3175 = 0;
    (void)_t3175;
    fd->return_is_ref = _t3175;
    ;
    Bool _t3176 = 0;
    (void)_t3176;
    fd->return_is_shallow = _t3176;
    ;
    I64 _t3177 = 0;
    (void)_t3177;
    I64 _t3178 = 1;
    (void)_t3178;
    I64 _t3179 = I64_sub(_t3177, _t3178);
    (void)_t3179;
    ;
    ;
    I32 _t3180 = I64_to_i32(_t3179);
    (void)_t3180;
    ;
    fd->variadic_index = _t3180;
    ;
    I64 _t3181 = 0;
    (void)_t3181;
    I64 _t3182 = 1;
    (void)_t3182;
    I64 _t3183 = I64_sub(_t3181, _t3182);
    (void)_t3183;
    ;
    ;
    I32 _t3184 = I64_to_i32(_t3183);
    (void)_t3184;
    ;
    fd->kwargs_index = _t3184;
    ;
    {
        U64 _fi3119 = 0;
        (void)_fi3119;
        while (1) {
            U64 _t3121 = 0;
            (void)_t3121;
            U64 _t3122; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3122 = *_hp; free(_hp); }
            (void)_t3122;
            Range *_t3123 = Range_new(_t3121, _t3122);
            (void)_t3123;
            ;
            ;
            U64 _t3124; { U64 *_hp = (U64 *)Range_len(_t3123); _t3124 = *_hp; free(_hp); }
            (void)_t3124;
            Range_delete(_t3123, &(Bool){1});
            Bool _wcond3120; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3119}, &(U64){_t3124}); _wcond3120 = *_hp; free(_hp); }
            (void)_wcond3120;
            ;
            if (_wcond3120) {
            } else {
                ;
                break;
            }
            ;
            U64 _t3125 = 0;
            (void)_t3125;
            U64 _t3126; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3126 = *_hp; free(_hp); }
            (void)_t3126;
            Range *_t3127 = Range_new(_t3125, _t3126);
            (void)_t3127;
            ;
            ;
            U64 _; { U64 *_hp = (U64 *)Range_get(_t3127, _fi3119); _ = *_hp; free(_hp); }
            (void)_;
            ;
            Range_delete(_t3127, &(Bool){1});
            U64 _t3128 = 1;
            (void)_t3128;
            U64 _t3129 = U64_add(_fi3119, _t3128);
            (void)_t3129;
            ;
            _fi3119 = _t3129;
            ;
            Str *_t3130 = Str_lit("", 0ULL);
            (void)_t3130;
            Vec_push(&fd->param_names, _t3130);
            Bool _t3131 = 0;
            (void)_t3131;
            Vec_push(&fd->param_owns, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3131; _oa; }));
            Bool _t3132 = 0;
            (void)_t3132;
            Vec_push(&fd->param_shallows, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3132; _oa; }));
            I64 _t3133 = 0;
            (void)_t3133;
            I64 _t3134 = 1;
            (void)_t3134;
            I64 _t3135 = I64_sub(_t3133, _t3134);
            (void)_t3135;
            ;
            ;
            Vec_push(&fd->param_defaults, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = _t3135; _oa; }));
            I64 _t3136 = 0;
            (void)_t3136;
            I64 _t3137 = 1;
            (void)_t3137;
            I64 _t3138 = I64_sub(_t3136, _t3137);
            (void)_t3138;
            ;
            ;
            Vec_push(&fd->param_fn_sigs, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = _t3138; _oa; }));
        }
        ;
    }
    Vec_delete(&fd->param_types, &(Bool){0});
    { Vec *_fa = Vec_clone(ptypes); fd->param_types = *_fa; free(_fa); }
    Vec_delete(ptypes, &(Bool){1});
    Vec_delete(&fd->param_muts, &(Bool){0});
    { Vec *_fa = Vec_clone(pmuts); fd->param_muts = *_fa; free(_fa); }
    Vec_delete(pmuts, &(Bool){1});
    ExprData *_t3185 = ExprData_FuncDef(fd);
    (void)_t3185;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *sig = Expr_new(_t3185, DEREF(line), DEREF(col), &p->path);
    (void)sig;
    ExprData_delete(_t3185, &(Bool){1});
    return sig;
}

Expr * parse_block(Parser * p) {
    (void)p;
    U32 _t3192; { U32 *_hp = (U32 *)peek_line(p); _t3192 = *_hp; free(_hp); }
    (void)_t3192;
    U32 _t3193; { U32 *_hp = (U32 *)peek_col(p); _t3193 = *_hp; free(_hp); }
    (void)_t3193;
    Expr *body = Expr_new(ExprData_Body(), _t3192, _t3193, &p->path);
    (void)body;
    ;
    ;
    while (1) {
        Bool _t3187; { Bool *_hp = (Bool *)check(p, TokenType_RBrace()); _t3187 = *_hp; free(_hp); }
        (void)_t3187;
        Bool _t3188; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3188 = *_hp; free(_hp); }
        (void)_t3188;
        Bool _t3189 = Bool_not(_t3187);
        (void)_t3189;
        ;
        Bool _t3190 = Bool_not(_t3188);
        (void)_t3190;
        ;
        Bool _wcond3186 = Bool_and(_t3189, _t3190);
        (void)_wcond3186;
        ;
        ;
        if (_wcond3186) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t3191 = parse_statement(p);
        (void)_t3191;
        Expr_add_child(body, _t3191);
    }
    expect_token(p, TokenType_RBrace());
    return body;
}

Expr * parse_func_def(Parser * p) {
    (void)p;
    U32 kw_line; { U32 *_hp = (U32 *)peek_line(p); kw_line = *_hp; free(_hp); }
    (void)kw_line;
    U32 kw_col; { U32 *_hp = (U32 *)peek_col(p); kw_col = *_hp; free(_hp); }
    (void)kw_col;
    Token *kw = advance(p);
    (void)kw;
    FuncType *ft = FuncType_clone(FuncType_Func());
    (void)ft;
    {
        TokenType *_sw3194 = TokenType_clone(&kw->type);
        (void)_sw3194;
        Bool _t3206; { Bool *_hp = (Bool *)TokenType_eq(_sw3194, TokenType_KwFunc()); _t3206 = *_hp; free(_hp); }
        (void)_t3206;
        if (_t3206) {
            ft = FuncType_clone(FuncType_Func());
        } else {
            Bool _t3205; { Bool *_hp = (Bool *)TokenType_eq(_sw3194, TokenType_KwProc()); _t3205 = *_hp; free(_hp); }
            (void)_t3205;
            if (_t3205) {
                ft = FuncType_clone(FuncType_Proc());
            } else {
                Bool _t3204; { Bool *_hp = (Bool *)TokenType_eq(_sw3194, TokenType_KwTest()); _t3204 = *_hp; free(_hp); }
                (void)_t3204;
                if (_t3204) {
                    ft = FuncType_clone(FuncType_Test());
                } else {
                    Bool _t3203; { Bool *_hp = (Bool *)TokenType_eq(_sw3194, TokenType_KwMacro()); _t3203 = *_hp; free(_hp); }
                    (void)_t3203;
                    if (_t3203) {
                        ft = FuncType_clone(FuncType_Macro());
                    } else {
                        Bool _t3202; { Bool *_hp = (Bool *)TokenType_eq(_sw3194, TokenType_KwExtFunc()); _t3202 = *_hp; free(_hp); }
                        (void)_t3202;
                        if (_t3202) {
                            ft = FuncType_clone(FuncType_ExtFunc());
                        } else {
                            Bool _t3201; { Bool *_hp = (Bool *)TokenType_eq(_sw3194, TokenType_KwExtProc()); _t3201 = *_hp; free(_hp); }
                            (void)_t3201;
                            if (_t3201) {
                                ft = FuncType_clone(FuncType_ExtProc());
                            } else {
                                Str *_t3195 = Str_lit("Str", 3ULL);
                                (void)_t3195;
                                U64 _t3196; { U64 *_hp = (U64 *)Str_size(); _t3196 = *_hp; free(_hp); }
                                (void)_t3196;
                                U64 _t3197 = 1;
                                (void)_t3197;
                                Array *_va56 = Array_new(_t3195, &(U64){_t3196}, &(U64){_t3197});
                                (void)_va56;
                                Str_delete(_t3195, &(Bool){1});
                                ;
                                ;
                                U64 _t3198 = 0;
                                (void)_t3198;
                                Str *_t3199 = Str_lit("expected function keyword", 25ULL);
                                (void)_t3199;
                                Array_set(_va56, &(U64){_t3198}, _t3199);
                                ;
                                Str *_t3200 = Str_lit("src/self/parser.til:136:17", 26ULL);
                                (void)_t3200;
                                panic(_t3200, _va56);
                                Str_delete(_t3200, &(Bool){1});
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
        TokenType_delete(_sw3194, &(Bool){1});
        ;
    }
    expect_token(p, TokenType_LParen());
    Str *_t3398 = Str_lit("Str", 3ULL);
    (void)_t3398;
    U64 _t3399; { U64 *_hp = (U64 *)Str_size(); _t3399 = *_hp; free(_hp); }
    (void)_t3399;
    Str *_t3400 = Str_lit("Str", 3ULL);
    (void)_t3400;
    U64 _t3401; { U64 *_hp = (U64 *)Str_size(); _t3401 = *_hp; free(_hp); }
    (void)_t3401;
    Str *_t3402 = Str_lit("Bool", 4ULL);
    (void)_t3402;
    U64 _t3403; { U64 *_hp = (U64 *)Bool_size(); _t3403 = *_hp; free(_hp); }
    (void)_t3403;
    Str *_t3404 = Str_lit("Bool", 4ULL);
    (void)_t3404;
    U64 _t3405; { U64 *_hp = (U64 *)Bool_size(); _t3405 = *_hp; free(_hp); }
    (void)_t3405;
    Str *_t3406 = Str_lit("Bool", 4ULL);
    (void)_t3406;
    U64 _t3407; { U64 *_hp = (U64 *)Bool_size(); _t3407 = *_hp; free(_hp); }
    (void)_t3407;
    Str *_t3408 = Str_lit("I64", 3ULL);
    (void)_t3408;
    U64 _t3409; { U64 *_hp = (U64 *)I64_size(); _t3409 = *_hp; free(_hp); }
    (void)_t3409;
    Str *_t3410 = Str_lit("I64", 3ULL);
    (void)_t3410;
    U64 _t3411; { U64 *_hp = (U64 *)I64_size(); _t3411 = *_hp; free(_hp); }
    (void)_t3411;
    I64 _t3412 = 0;
    (void)_t3412;
    I64 _t3413 = 1;
    (void)_t3413;
    I64 _t3414 = I64_sub(_t3412, _t3413);
    (void)_t3414;
    ;
    ;
    I64 _t3415 = 0;
    (void)_t3415;
    I64 _t3416 = 1;
    (void)_t3416;
    I64 _t3417 = I64_sub(_t3415, _t3416);
    (void)_t3417;
    ;
    ;
    U32 _t3418 = 0;
    (void)_t3418;
    I32 _t3419 = I64_to_i32(_t3414);
    (void)_t3419;
    ;
    I32 _t3420 = I64_to_i32(_t3417);
    (void)_t3420;
    ;
    Bool _t3421 = 0;
    (void)_t3421;
    Bool _t3422 = 0;
    (void)_t3422;
    FunctionDef *fd = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(FuncType_Func()); fd->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3398, &(U64){_t3399}); fd->param_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3400, &(U64){_t3401}); fd->param_types = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3402, &(U64){_t3403}); fd->param_muts = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3404, &(U64){_t3405}); fd->param_owns = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3406, &(U64){_t3407}); fd->param_shallows = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3408, &(U64){_t3409}); fd->param_fn_sigs = *_ca; free(_ca); }
    fd->nparam = _t3418;
    { Vec *_ca = Vec_new(_t3410, &(U64){_t3411}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3419;
    fd->kwargs_index = _t3420;
    fd->return_is_ref = _t3421;
    fd->return_is_shallow = _t3422;
    (void)fd;
    Str_delete(_t3398, &(Bool){1});
    ;
    Str_delete(_t3400, &(Bool){1});
    ;
    Str_delete(_t3402, &(Bool){1});
    ;
    Str_delete(_t3404, &(Bool){1});
    ;
    Str_delete(_t3406, &(Bool){1});
    ;
    Str_delete(_t3408, &(Bool){1});
    ;
    Str_delete(_t3410, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    FuncType_delete(&fd->func_type, &(Bool){0});
    { FuncType *_fa = FuncType_clone(ft); fd->func_type = *_fa; free(_fa); }
    Str *_t3423 = Str_lit("Expr", 4ULL);
    (void)_t3423;
    U64 _t3424; { U64 *_hp = (U64 *)Expr_size(); _t3424 = *_hp; free(_hp); }
    (void)_t3424;
    Vec *def_exprs = Vec_new(_t3423, &(U64){_t3424});
    (void)def_exprs;
    Str_delete(_t3423, &(Bool){1});
    ;
    while (1) {
        Bool _t3324; { Bool *_hp = (Bool *)check(p, TokenType_RParen()); _t3324 = *_hp; free(_hp); }
        (void)_t3324;
        Bool _t3325; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3325 = *_hp; free(_hp); }
        (void)_t3325;
        Bool _t3326 = Bool_not(_t3324);
        (void)_t3326;
        ;
        Bool _t3327 = Bool_not(_t3325);
        (void)_t3327;
        ;
        Bool _wcond3207 = Bool_and(_t3326, _t3327);
        (void)_wcond3207;
        ;
        ;
        if (_wcond3207) {
        } else {
            ;
            break;
        }
        ;
        Bool is_shallow = 0;
        (void)is_shallow;
        Bool _t3328; { Bool *_hp = (Bool *)check(p, TokenType_KwShallow()); _t3328 = *_hp; free(_hp); }
        (void)_t3328;
        if (_t3328) {
            Token *_t3208 = advance(p);
            (void)_t3208;
            Bool _t3209 = 1;
            (void)_t3209;
            is_shallow = _t3209;
            ;
        }
        ;
        Bool is_own = 0;
        (void)is_own;
        Bool _t3329; { Bool *_hp = (Bool *)check(p, TokenType_KwOwn()); _t3329 = *_hp; free(_hp); }
        (void)_t3329;
        if (_t3329) {
            Token *_t3210 = advance(p);
            (void)_t3210;
            Bool _t3211 = 1;
            (void)_t3211;
            is_own = _t3211;
            ;
        }
        ;
        Bool is_mut = 0;
        (void)is_mut;
        Bool _t3330; { Bool *_hp = (Bool *)check(p, TokenType_KwMut()); _t3330 = *_hp; free(_hp); }
        (void)_t3330;
        if (_t3330) {
            Token *_t3212 = advance(p);
            (void)_t3212;
            Bool _t3213 = 1;
            (void)_t3213;
            is_mut = _t3213;
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
        Bool _t3331; { Bool *_hp = (Bool *)check(p, TokenType_Colon()); _t3331 = *_hp; free(_hp); }
        (void)_t3331;
        Bool _t3332 = Bool_not(_t3331);
        (void)_t3332;
        ;
        if (_t3332) {
            tp = Str_clone(pname);
            nm = Str_lit("", 0ULL);
        } else {
            expect_token(p, TokenType_Colon());
            Bool _t3307; { Bool *_hp = (Bool *)check(p, TokenType_DotDotDot()); _t3307 = *_hp; free(_hp); }
            (void)_t3307;
            if (_t3307) {
                Token *_t3244 = advance(p);
                (void)_t3244;
                Bool _t3245 = Bool_or(is_own, is_mut);
                (void)_t3245;
                Bool _t3246 = Bool_or(_t3245, is_shallow);
                (void)_t3246;
                ;
                if (_t3246) {
                    Str *_t3214 = Str_lit("Str", 3ULL);
                    (void)_t3214;
                    U64 _t3215; { U64 *_hp = (U64 *)Str_size(); _t3215 = *_hp; free(_hp); }
                    (void)_t3215;
                    U64 _t3216 = 6;
                    (void)_t3216;
                    Array *_va57 = Array_new(_t3214, &(U64){_t3215}, &(U64){_t3216});
                    (void)_va57;
                    Str_delete(_t3214, &(Bool){1});
                    ;
                    ;
                    U64 _t3217 = 0;
                    (void)_t3217;
                    Str *_t3218 = Str_clone(&p->path);
                    (void)_t3218;
                    Array_set(_va57, &(U64){_t3217}, _t3218);
                    ;
                    U64 _t3219 = 1;
                    (void)_t3219;
                    Str *_t3220 = Str_lit(":", 1ULL);
                    (void)_t3220;
                    Array_set(_va57, &(U64){_t3219}, _t3220);
                    ;
                    U32 _t3221; { U32 *_hp = (U32 *)peek_line(p); _t3221 = *_hp; free(_hp); }
                    (void)_t3221;
                    U64 _t3222 = 2;
                    (void)_t3222;
                    Str *_t3223 = U32_to_str(&(U32){_t3221});
                    (void)_t3223;
                    ;
                    Array_set(_va57, &(U64){_t3222}, _t3223);
                    ;
                    U64 _t3224 = 3;
                    (void)_t3224;
                    Str *_t3225 = Str_lit(":", 1ULL);
                    (void)_t3225;
                    Array_set(_va57, &(U64){_t3224}, _t3225);
                    ;
                    U32 _t3226; { U32 *_hp = (U32 *)peek_col(p); _t3226 = *_hp; free(_hp); }
                    (void)_t3226;
                    U64 _t3227 = 4;
                    (void)_t3227;
                    Str *_t3228 = U32_to_str(&(U32){_t3226});
                    (void)_t3228;
                    ;
                    Array_set(_va57, &(U64){_t3227}, _t3228);
                    ;
                    U64 _t3229 = 5;
                    (void)_t3229;
                    Str *_t3230 = Str_lit(": kwargs parameter cannot be own/mut/shallow", 44ULL);
                    (void)_t3230;
                    Array_set(_va57, &(U64){_t3229}, _t3230);
                    ;
                    Str *_t3231 = Str_lit("src/self/parser.til:167:27", 26ULL);
                    (void)_t3231;
                    panic(_t3231, _va57);
                    Str_delete(_t3231, &(Bool){1});
                }
                ;
                I64 _t3247 = 0;
                (void)_t3247;
                I64 _t3248 = 1;
                (void)_t3248;
                I64 _t3249 = I64_sub(_t3247, _t3248);
                (void)_t3249;
                ;
                ;
                I32 _t3250 = I64_to_i32(_t3249);
                (void)_t3250;
                ;
                Bool _t3251; { Bool *_hp = (Bool *)I32_neq(&fd->kwargs_index, &(I32){_t3250}); _t3251 = *_hp; free(_hp); }
                (void)_t3251;
                ;
                if (_t3251) {
                    Str *_t3232 = Str_lit("Str", 3ULL);
                    (void)_t3232;
                    U64 _t3233; { U64 *_hp = (U64 *)Str_size(); _t3233 = *_hp; free(_hp); }
                    (void)_t3233;
                    U64 _t3234 = 1;
                    (void)_t3234;
                    Array *_va58 = Array_new(_t3232, &(U64){_t3233}, &(U64){_t3234});
                    (void)_va58;
                    Str_delete(_t3232, &(Bool){1});
                    ;
                    ;
                    U64 _t3235 = 0;
                    (void)_t3235;
                    Str *_t3236 = Str_lit("only one kwargs parameter is allowed", 36ULL);
                    (void)_t3236;
                    Array_set(_va58, &(U64){_t3235}, _t3236);
                    ;
                    Str *_t3237 = Str_lit("src/self/parser.til:171:27", 26ULL);
                    (void)_t3237;
                    panic(_t3237, _va58);
                    Str_delete(_t3237, &(Bool){1});
                }
                ;
                I64 _t3252 = 0;
                (void)_t3252;
                I64 _t3253 = 1;
                (void)_t3253;
                I64 _t3254 = I64_sub(_t3252, _t3253);
                (void)_t3254;
                ;
                ;
                I32 _t3255 = I64_to_i32(_t3254);
                (void)_t3255;
                ;
                Bool _t3256; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3255}); _t3256 = *_hp; free(_hp); }
                (void)_t3256;
                ;
                if (_t3256) {
                    Str *_t3238 = Str_lit("Str", 3ULL);
                    (void)_t3238;
                    U64 _t3239; { U64 *_hp = (U64 *)Str_size(); _t3239 = *_hp; free(_hp); }
                    (void)_t3239;
                    U64 _t3240 = 1;
                    (void)_t3240;
                    Array *_va59 = Array_new(_t3238, &(U64){_t3239}, &(U64){_t3240});
                    (void)_va59;
                    Str_delete(_t3238, &(Bool){1});
                    ;
                    ;
                    U64 _t3241 = 0;
                    (void)_t3241;
                    Str *_t3242 = Str_lit("cannot combine variadic and kwargs in the same function", 55ULL);
                    (void)_t3242;
                    Array_set(_va59, &(U64){_t3241}, _t3242);
                    ;
                    Str *_t3243 = Str_lit("src/self/parser.til:174:27", 26ULL);
                    (void)_t3243;
                    panic(_t3243, _va59);
                    Str_delete(_t3243, &(Bool){1});
                }
                ;
                U64 _t3257; { U64 *_hp = (U64 *)Vec_len(&fd->param_names); _t3257 = *_hp; free(_hp); }
                (void)_t3257;
                I64 _t3258 = U64_to_i64(_t3257);
                (void)_t3258;
                ;
                I32 _t3259 = I64_to_i32(_t3258);
                (void)_t3259;
                ;
                fd->kwargs_index = _t3259;
                ;
                Bool _t3260 = 1;
                (void)_t3260;
                is_own = _t3260;
                ;
                nm = Str_clone(pname);
                tp = Str_lit("Map", 3ULL);
            } else {
                Bool _t3306; { Bool *_hp = (Bool *)check(p, TokenType_DotDot()); _t3306 = *_hp; free(_hp); }
                (void)_t3306;
                if (_t3306) {
                    Token *_t3291 = advance(p);
                    (void)_t3291;
                    if (is_own) {
                        Str *_t3261 = Str_lit("Str", 3ULL);
                        (void)_t3261;
                        U64 _t3262; { U64 *_hp = (U64 *)Str_size(); _t3262 = *_hp; free(_hp); }
                        (void)_t3262;
                        U64 _t3263 = 1;
                        (void)_t3263;
                        Array *_va60 = Array_new(_t3261, &(U64){_t3262}, &(U64){_t3263});
                        (void)_va60;
                        Str_delete(_t3261, &(Bool){1});
                        ;
                        ;
                        U64 _t3264 = 0;
                        (void)_t3264;
                        Str *_t3265 = Str_lit("variadic param cannot be 'own'", 30ULL);
                        (void)_t3265;
                        Array_set(_va60, &(U64){_t3264}, _t3265);
                        ;
                        Str *_t3266 = Str_lit("src/self/parser.til:182:35", 26ULL);
                        (void)_t3266;
                        panic(_t3266, _va60);
                        Str_delete(_t3266, &(Bool){1});
                    }
                    if (is_mut) {
                        Str *_t3267 = Str_lit("Str", 3ULL);
                        (void)_t3267;
                        U64 _t3268; { U64 *_hp = (U64 *)Str_size(); _t3268 = *_hp; free(_hp); }
                        (void)_t3268;
                        U64 _t3269 = 1;
                        (void)_t3269;
                        Array *_va61 = Array_new(_t3267, &(U64){_t3268}, &(U64){_t3269});
                        (void)_va61;
                        Str_delete(_t3267, &(Bool){1});
                        ;
                        ;
                        U64 _t3270 = 0;
                        (void)_t3270;
                        Str *_t3271 = Str_lit("variadic param cannot be 'mut'", 30ULL);
                        (void)_t3271;
                        Array_set(_va61, &(U64){_t3270}, _t3271);
                        ;
                        Str *_t3272 = Str_lit("src/self/parser.til:183:35", 26ULL);
                        (void)_t3272;
                        panic(_t3272, _va61);
                        Str_delete(_t3272, &(Bool){1});
                    }
                    if (is_shallow) {
                        Str *_t3273 = Str_lit("Str", 3ULL);
                        (void)_t3273;
                        U64 _t3274; { U64 *_hp = (U64 *)Str_size(); _t3274 = *_hp; free(_hp); }
                        (void)_t3274;
                        U64 _t3275 = 1;
                        (void)_t3275;
                        Array *_va62 = Array_new(_t3273, &(U64){_t3274}, &(U64){_t3275});
                        (void)_va62;
                        Str_delete(_t3273, &(Bool){1});
                        ;
                        ;
                        U64 _t3276 = 0;
                        (void)_t3276;
                        Str *_t3277 = Str_lit("variadic param cannot be 'shallow'", 34ULL);
                        (void)_t3277;
                        Array_set(_va62, &(U64){_t3276}, _t3277);
                        ;
                        Str *_t3278 = Str_lit("src/self/parser.til:184:39", 26ULL);
                        (void)_t3278;
                        panic(_t3278, _va62);
                        Str_delete(_t3278, &(Bool){1});
                    }
                    I64 _t3292 = 0;
                    (void)_t3292;
                    I64 _t3293 = 1;
                    (void)_t3293;
                    I64 _t3294 = I64_sub(_t3292, _t3293);
                    (void)_t3294;
                    ;
                    ;
                    I32 _t3295 = I64_to_i32(_t3294);
                    (void)_t3295;
                    ;
                    Bool _t3296; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3295}); _t3296 = *_hp; free(_hp); }
                    (void)_t3296;
                    ;
                    if (_t3296) {
                        Str *_t3279 = Str_lit("Str", 3ULL);
                        (void)_t3279;
                        U64 _t3280; { U64 *_hp = (U64 *)Str_size(); _t3280 = *_hp; free(_hp); }
                        (void)_t3280;
                        U64 _t3281 = 1;
                        (void)_t3281;
                        Array *_va63 = Array_new(_t3279, &(U64){_t3280}, &(U64){_t3281});
                        (void)_va63;
                        Str_delete(_t3279, &(Bool){1});
                        ;
                        ;
                        U64 _t3282 = 0;
                        (void)_t3282;
                        Str *_t3283 = Str_lit("only one variadic param allowed", 31ULL);
                        (void)_t3283;
                        Array_set(_va63, &(U64){_t3282}, _t3283);
                        ;
                        Str *_t3284 = Str_lit("src/self/parser.til:185:69", 26ULL);
                        (void)_t3284;
                        panic(_t3284, _va63);
                        Str_delete(_t3284, &(Bool){1});
                    }
                    ;
                    I64 _t3297 = 0;
                    (void)_t3297;
                    I64 _t3298 = 1;
                    (void)_t3298;
                    I64 _t3299 = I64_sub(_t3297, _t3298);
                    (void)_t3299;
                    ;
                    ;
                    I32 _t3300 = I64_to_i32(_t3299);
                    (void)_t3300;
                    ;
                    Bool _t3301; { Bool *_hp = (Bool *)I32_neq(&fd->kwargs_index, &(I32){_t3300}); _t3301 = *_hp; free(_hp); }
                    (void)_t3301;
                    ;
                    if (_t3301) {
                        Str *_t3285 = Str_lit("Str", 3ULL);
                        (void)_t3285;
                        U64 _t3286; { U64 *_hp = (U64 *)Str_size(); _t3286 = *_hp; free(_hp); }
                        (void)_t3286;
                        U64 _t3287 = 1;
                        (void)_t3287;
                        Array *_va64 = Array_new(_t3285, &(U64){_t3286}, &(U64){_t3287});
                        (void)_va64;
                        Str_delete(_t3285, &(Bool){1});
                        ;
                        ;
                        U64 _t3288 = 0;
                        (void)_t3288;
                        Str *_t3289 = Str_lit("cannot combine variadic and kwargs in the same function", 55ULL);
                        (void)_t3289;
                        Array_set(_va64, &(U64){_t3288}, _t3289);
                        ;
                        Str *_t3290 = Str_lit("src/self/parser.til:187:27", 26ULL);
                        (void)_t3290;
                        panic(_t3290, _va64);
                        Str_delete(_t3290, &(Bool){1});
                    }
                    ;
                    U64 _t3302; { U64 *_hp = (U64 *)Vec_len(&fd->param_names); _t3302 = *_hp; free(_hp); }
                    (void)_t3302;
                    I64 _t3303 = U64_to_i64(_t3302);
                    (void)_t3303;
                    ;
                    I32 _t3304 = I64_to_i32(_t3303);
                    (void)_t3304;
                    ;
                    fd->variadic_index = _t3304;
                    ;
                    Bool _t3305 = 1;
                    (void)_t3305;
                    is_variadic = _t3305;
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
        I64 _t3333 = 0;
        (void)_t3333;
        I64 _t3334 = 1;
        (void)_t3334;
        I64 fn_sig_idx = I64_sub(_t3333, _t3334);
        (void)fn_sig_idx;
        ;
        ;
        Str *_t3335 = Str_lit("Fn", 2ULL);
        (void)_t3335;
        Bool _t3336; { Bool *_hp = (Bool *)Str_eq(tp, _t3335); _t3336 = *_hp; free(_hp); }
        (void)_t3336;
        Str_delete(_t3335, &(Bool){1});
        if (_t3336) {
            U32 _t3310; { U32 *_hp = (U32 *)peek_line(p); _t3310 = *_hp; free(_hp); }
            (void)_t3310;
            U32 _t3311; { U32 *_hp = (U32 *)peek_col(p); _t3311 = *_hp; free(_hp); }
            (void)_t3311;
            Expr *sig = parse_fn_signature(p, &(U32){_t3310}, &(U32){_t3311});
            (void)sig;
            ;
            ;
            U32 _t3312 = 0;
            (void)_t3312;
            Bool _t3313; { Bool *_hp = (Bool *)U32_neq(&sig->line, &(U32){_t3312}); _t3313 = *_hp; free(_hp); }
            (void)_t3313;
            ;
            if (_t3313) {
                U64 _t3308; { U64 *_hp = (U64 *)Vec_len(def_exprs); _t3308 = *_hp; free(_hp); }
                (void)_t3308;
                I64 _t3309 = U64_to_i64(_t3308);
                (void)_t3309;
                ;
                fn_sig_idx = _t3309;
                ;
                Vec_push(def_exprs, sig);
            }
            ;
        }
        ;
        Vec_push(&fd->param_names, nm);
        Vec_push(&fd->param_types, tp);
        Vec_push(&fd->param_muts, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = is_mut; _oa; }));
        Vec_push(&fd->param_owns, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = is_own; _oa; }));
        Vec_push(&fd->param_shallows, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = is_shallow; _oa; }));
        Vec_push(&fd->param_fn_sigs, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = fn_sig_idx; _oa; }));
        I64 _t3337 = 0;
        (void)_t3337;
        I64 _t3338 = 1;
        (void)_t3338;
        I64 has_default = I64_sub(_t3337, _t3338);
        (void)has_default;
        ;
        ;
        Bool _t3339; { Bool *_hp = (Bool *)check(p, TokenType_Eq()); _t3339 = *_hp; free(_hp); }
        (void)_t3339;
        if (_t3339) {
            Token *_t3314 = advance(p);
            (void)_t3314;
            U64 _t3315; { U64 *_hp = (U64 *)Vec_len(def_exprs); _t3315 = *_hp; free(_hp); }
            (void)_t3315;
            I64 _t3316 = U64_to_i64(_t3315);
            (void)_t3316;
            ;
            has_default = _t3316;
            ;
            Expr *def_expr = parse_expression(p);
            (void)def_expr;
            Vec_push(def_exprs, def_expr);
        }
        ;
        I64 _t3340 = 0;
        (void)_t3340;
        I64 _t3341 = 1;
        (void)_t3341;
        I64 _t3342 = I64_sub(_t3340, _t3341);
        (void)_t3342;
        ;
        ;
        I32 _t3343 = I64_to_i32(_t3342);
        (void)_t3343;
        ;
        Bool _t3344; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3343}); _t3344 = *_hp; free(_hp); }
        (void)_t3344;
        ;
        Bool _t3345 = Bool_not(is_variadic);
        (void)_t3345;
        ;
        I64 _t3346 = 0;
        (void)_t3346;
        I64 _t3347 = 1;
        (void)_t3347;
        I64 _t3348 = I64_sub(_t3346, _t3347);
        (void)_t3348;
        ;
        ;
        Bool _t3349 = Bool_and(_t3344, _t3345);
        (void)_t3349;
        ;
        ;
        Bool _t3350 = I64_eq(has_default, _t3348);
        (void)_t3350;
        ;
        Bool _t3351 = Bool_and(_t3349, _t3350);
        (void)_t3351;
        ;
        ;
        if (_t3351) {
            Str *_t3317 = Str_lit("Str", 3ULL);
            (void)_t3317;
            U64 _t3318; { U64 *_hp = (U64 *)Str_size(); _t3318 = *_hp; free(_hp); }
            (void)_t3318;
            U64 _t3319 = 1;
            (void)_t3319;
            Array *_va65 = Array_new(_t3317, &(U64){_t3318}, &(U64){_t3319});
            (void)_va65;
            Str_delete(_t3317, &(Bool){1});
            ;
            ;
            U64 _t3320 = 0;
            (void)_t3320;
            Str *_t3321 = Str_lit("positional param not allowed after variadic", 43ULL);
            (void)_t3321;
            Array_set(_va65, &(U64){_t3320}, _t3321);
            ;
            Str *_t3322 = Str_lit("src/self/parser.til:226:19", 26ULL);
            (void)_t3322;
            panic(_t3322, _va65);
            Str_delete(_t3322, &(Bool){1});
        }
        ;
        Vec_push(&fd->param_defaults, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = has_default; _oa; }));
        Bool _t3352; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3352 = *_hp; free(_hp); }
        (void)_t3352;
        if (_t3352) {
            Token *_t3323 = advance(p);
            (void)_t3323;
        }
        ;
    }
    expect_token(p, TokenType_RParen());
    Bool _t3425; { Bool *_hp = (Bool *)check(p, TokenType_KwReturns()); _t3425 = *_hp; free(_hp); }
    (void)_t3425;
    if (_t3425) {
        Token *_t3358 = advance(p);
        (void)_t3358;
        Bool _t3359; { Bool *_hp = (Bool *)check(p, TokenType_KwRef()); _t3359 = *_hp; free(_hp); }
        (void)_t3359;
        if (_t3359) {
            Token *_t3353 = advance(p);
            (void)_t3353;
            Bool _t3354 = 1;
            (void)_t3354;
            fd->return_is_ref = _t3354;
            ;
        } else {
            Bool _t3357; { Bool *_hp = (Bool *)check(p, TokenType_KwShallow()); _t3357 = *_hp; free(_hp); }
            (void)_t3357;
            if (_t3357) {
                Token *_t3355 = advance(p);
                (void)_t3355;
                Bool _t3356 = 1;
                (void)_t3356;
                fd->return_is_shallow = _t3356;
                ;
            }
            ;
        }
        ;
        Str_delete(&fd->return_type, &(Bool){0});
        { Str *_fa = expect_text(p, TokenType_Ident()); fd->return_type = *_fa; free(_fa); }
    }
    ;
    ExprData *_t3426 = ExprData_FuncDef(fd);
    (void)_t3426;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *def = Expr_new(_t3426, kw_line, kw_col, &p->path);
    (void)def;
    ExprData_delete(_t3426, &(Bool){1});
    Bool _t3427; { Bool *_hp = (Bool *)check(p, TokenType_LBrace()); _t3427 = *_hp; free(_hp); }
    (void)_t3427;
    if (_t3427) {
        expect_token(p, TokenType_LBrace());
        Expr *_t3360 = parse_block(p);
        (void)_t3360;
        Expr_add_child(def, _t3360);
    } else {
        Bool _t3381; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Func()); _t3381 = *_hp; free(_hp); }
        (void)_t3381;
        Bool _t3382; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Proc()); _t3382 = *_hp; free(_hp); }
        (void)_t3382;
        Bool _t3383 = Bool_not(_t3381);
        (void)_t3383;
        ;
        Bool _t3384 = Bool_not(_t3382);
        (void)_t3384;
        ;
        Bool _t3385 = Bool_and(_t3383, _t3384);
        (void)_t3385;
        ;
        ;
        if (_t3385) {
            Str *_t3361 = Str_lit("Str", 3ULL);
            (void)_t3361;
            U64 _t3362; { U64 *_hp = (U64 *)Str_size(); _t3362 = *_hp; free(_hp); }
            (void)_t3362;
            U64 _t3363 = 8;
            (void)_t3363;
            Array *_va66 = Array_new(_t3361, &(U64){_t3362}, &(U64){_t3363});
            (void)_va66;
            Str_delete(_t3361, &(Bool){1});
            ;
            ;
            U64 _t3364 = 0;
            (void)_t3364;
            Str *_t3365 = Str_clone(&p->path);
            (void)_t3365;
            Array_set(_va66, &(U64){_t3364}, _t3365);
            ;
            U64 _t3366 = 1;
            (void)_t3366;
            Str *_t3367 = Str_lit(":", 1ULL);
            (void)_t3367;
            Array_set(_va66, &(U64){_t3366}, _t3367);
            ;
            U64 _t3368 = 2;
            (void)_t3368;
            Str *_t3369 = U32_to_str(&(U32){kw_line});
            (void)_t3369;
            Array_set(_va66, &(U64){_t3368}, _t3369);
            ;
            U64 _t3370 = 3;
            (void)_t3370;
            Str *_t3371 = Str_lit(":", 1ULL);
            (void)_t3371;
            Array_set(_va66, &(U64){_t3370}, _t3371);
            ;
            U64 _t3372 = 4;
            (void)_t3372;
            Str *_t3373 = U32_to_str(&(U32){kw_col});
            (void)_t3373;
            Array_set(_va66, &(U64){_t3372}, _t3373);
            ;
            U64 _t3374 = 5;
            (void)_t3374;
            Str *_t3375 = Str_lit(": ", 2ULL);
            (void)_t3375;
            Array_set(_va66, &(U64){_t3374}, _t3375);
            ;
            U64 _t3376 = 6;
            (void)_t3376;
            Str *_t3377 = func_type_name(ft);
            (void)_t3377;
            Array_set(_va66, &(U64){_t3376}, _t3377);
            ;
            U64 _t3378 = 7;
            (void)_t3378;
            Str *_t3379 = Str_lit(" requires a body", 16ULL);
            (void)_t3379;
            Array_set(_va66, &(U64){_t3378}, _t3379);
            ;
            Str *_t3380 = Str_lit("src/self/parser.til:254:19", 26ULL);
            (void)_t3380;
            panic(_t3380, _va66);
            Str_delete(_t3380, &(Bool){1});
        }
        ;
    }
    ;
    FuncType_delete(ft, &(Bool){1});
    ;
    ;
    {
        U64 _fi3386 = 0;
        (void)_fi3386;
        while (1) {
            U64 _t3388 = 0;
            (void)_t3388;
            U64 _t3389; { U64 *_hp = (U64 *)Vec_len(def_exprs); _t3389 = *_hp; free(_hp); }
            (void)_t3389;
            Range *_t3390 = Range_new(_t3388, _t3389);
            (void)_t3390;
            ;
            ;
            U64 _t3391; { U64 *_hp = (U64 *)Range_len(_t3390); _t3391 = *_hp; free(_hp); }
            (void)_t3391;
            Range_delete(_t3390, &(Bool){1});
            Bool _wcond3387; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3386}, &(U64){_t3391}); _wcond3387 = *_hp; free(_hp); }
            (void)_wcond3387;
            ;
            if (_wcond3387) {
            } else {
                ;
                break;
            }
            ;
            U64 _t3392 = 0;
            (void)_t3392;
            U64 _t3393; { U64 *_hp = (U64 *)Vec_len(def_exprs); _t3393 = *_hp; free(_hp); }
            (void)_t3393;
            Range *_t3394 = Range_new(_t3392, _t3393);
            (void)_t3394;
            ;
            ;
            U64 *i = Range_get(_t3394, _fi3386);
            (void)i;
            Range_delete(_t3394, &(Bool){1});
            U64 _t3395 = 1;
            (void)_t3395;
            U64 _t3396 = U64_add(_fi3386, _t3395);
            (void)_t3396;
            ;
            _fi3386 = _t3396;
            ;
            Expr *de = Vec_get(def_exprs, i);
            (void)de;
            Expr *_t3397 = Expr_clone(de);
            (void)_t3397;
            U64_delete(i, &(Bool){1});
            Expr_add_child(def, _t3397);
        }
        ;
    }
    Vec_delete(def_exprs, &(Bool){1});
    return def;
}

Expr * parse_struct_def(Parser * p) {
    (void)p;
    U32 kw_line; { U32 *_hp = (U32 *)peek_line(p); kw_line = *_hp; free(_hp); }
    (void)kw_line;
    U32 kw_col; { U32 *_hp = (U32 *)peek_col(p); kw_col = *_hp; free(_hp); }
    (void)kw_col;
    Bool is_ext; { Bool *_hp = (Bool *)check(p, TokenType_KwExtStruct()); is_ext = *_hp; free(_hp); }
    (void)is_ext;
    Token *_t3440 = advance(p);
    (void)_t3440;
    Expr *def = Expr_new(ExprData_StructDef(), kw_line, kw_col, &p->path);
    (void)def;
    ;
    ;
    Bool _t3441 = Bool_clone(&(Bool){is_ext});
    (void)_t3441;
    ;
    def->is_ext = _t3441;
    ;
    expect_token(p, TokenType_LBrace());
    U32 _t3442; { U32 *_hp = (U32 *)peek_line(p); _t3442 = *_hp; free(_hp); }
    (void)_t3442;
    U32 _t3443; { U32 *_hp = (U32 *)peek_col(p); _t3443 = *_hp; free(_hp); }
    (void)_t3443;
    Expr *body = Expr_new(ExprData_Body(), _t3442, _t3443, &p->path);
    (void)body;
    ;
    ;
    Bool in_namespace = 0;
    (void)in_namespace;
    while (1) {
        Bool _t3433; { Bool *_hp = (Bool *)check(p, TokenType_RBrace()); _t3433 = *_hp; free(_hp); }
        (void)_t3433;
        Bool _t3434; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3434 = *_hp; free(_hp); }
        (void)_t3434;
        Bool _t3435 = Bool_not(_t3433);
        (void)_t3435;
        ;
        Bool _t3436 = Bool_not(_t3434);
        (void)_t3436;
        ;
        Bool _wcond3428 = Bool_and(_t3435, _t3436);
        (void)_wcond3428;
        ;
        ;
        if (_wcond3428) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3437; { Bool *_hp = (Bool *)check(p, TokenType_KwNamespace()); _t3437 = *_hp; free(_hp); }
        (void)_t3437;
        if (_t3437) {
            Token *_t3429 = advance(p);
            (void)_t3429;
            expect_token(p, TokenType_Colon());
            Bool _t3430 = 1;
            (void)_t3430;
            in_namespace = _t3430;
            ;
            ;
            continue;
        }
        ;
        Expr *stmt = parse_statement(p);
        (void)stmt;
        Bool _t3438; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3438 = *_hp; free(_hp); }
        (void)_t3438;
        Bool _t3439 = Bool_and(in_namespace, _t3438);
        (void)_t3439;
        ;
        if (_t3439) {
            Bool _t3432; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3432 = *_hp; free(_hp); }
            (void)_t3432;
            if (_t3432) {
                Declaration *dd = ExprData_get_Decl(&stmt->data);
                (void)dd;
                Bool _t3431 = 1;
                (void)_t3431;
                dd->is_namespace = _t3431;
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
    expect_token(p, TokenType_RBrace());
    Expr_add_child(def, body);
    return def;
}

Expr * parse_enum_def(Parser * p) {
    (void)p;
    U32 kw_line; { U32 *_hp = (U32 *)peek_line(p); kw_line = *_hp; free(_hp); }
    (void)kw_line;
    U32 kw_col; { U32 *_hp = (U32 *)peek_col(p); kw_col = *_hp; free(_hp); }
    (void)kw_col;
    Token *_t3466 = advance(p);
    (void)_t3466;
    Expr *def = Expr_new(ExprData_EnumDef(), kw_line, kw_col, &p->path);
    (void)def;
    ;
    ;
    expect_token(p, TokenType_LBrace());
    U32 _t3467; { U32 *_hp = (U32 *)peek_line(p); _t3467 = *_hp; free(_hp); }
    (void)_t3467;
    U32 _t3468; { U32 *_hp = (U32 *)peek_col(p); _t3468 = *_hp; free(_hp); }
    (void)_t3468;
    Expr *body = Expr_new(ExprData_Body(), _t3467, _t3468, &p->path);
    (void)body;
    ;
    ;
    Bool in_namespace = 0;
    (void)in_namespace;
    while (1) {
        Bool _t3461; { Bool *_hp = (Bool *)check(p, TokenType_RBrace()); _t3461 = *_hp; free(_hp); }
        (void)_t3461;
        Bool _t3462; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3462 = *_hp; free(_hp); }
        (void)_t3462;
        Bool _t3463 = Bool_not(_t3461);
        (void)_t3463;
        ;
        Bool _t3464 = Bool_not(_t3462);
        (void)_t3464;
        ;
        Bool _wcond3444 = Bool_and(_t3463, _t3464);
        (void)_wcond3444;
        ;
        ;
        if (_wcond3444) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3465; { Bool *_hp = (Bool *)check(p, TokenType_KwNamespace()); _t3465 = *_hp; free(_hp); }
        (void)_t3465;
        if (_t3465) {
            Token *_t3445 = advance(p);
            (void)_t3445;
            expect_token(p, TokenType_Colon());
            Bool _t3446 = 1;
            (void)_t3446;
            in_namespace = _t3446;
            ;
            ;
            continue;
        }
        ;
        if (in_namespace) {
            Expr *stmt = parse_statement(p);
            (void)stmt;
            Bool _t3449; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3449 = *_hp; free(_hp); }
            (void)_t3449;
            if (_t3449) {
                Bool _t3448; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3448 = *_hp; free(_hp); }
                (void)_t3448;
                if (_t3448) {
                    Declaration *dd = ExprData_get_Decl(&stmt->data);
                    (void)dd;
                    Bool _t3447 = 1;
                    (void)_t3447;
                    dd->is_namespace = _t3447;
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
            U32 v_line; { U32 *_hp = (U32 *)peek_line(p); v_line = *_hp; free(_hp); }
            (void)v_line;
            U32 v_col; { U32 *_hp = (U32 *)peek_col(p); v_col = *_hp; free(_hp); }
            (void)v_col;
            Str *vname = expect_text(p, TokenType_Ident());
            (void)vname;
            Bool _t3452 = 0;
            (void)_t3452;
            Bool _t3453 = 0;
            (void)_t3453;
            Bool _t3454 = 0;
            (void)_t3454;
            Bool _t3455 = 0;
            (void)_t3455;
            I32 _t3456 = 0;
            (void)_t3456;
            I32 _t3457 = 0;
            (void)_t3457;
            Declaration *dd = malloc(sizeof(Declaration));
            { Str *_ca = Str_clone(vname); dd->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
            dd->is_mut = _t3452;
            dd->is_namespace = _t3453;
            dd->is_ref = _t3454;
            dd->is_own = _t3455;
            dd->field_offset = _t3456;
            dd->field_size = _t3457;
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
            Bool _t3458; { Bool *_hp = (Bool *)check(p, TokenType_Colon()); _t3458 = *_hp; free(_hp); }
            (void)_t3458;
            if (_t3458) {
                Token *_t3450 = advance(p);
                (void)_t3450;
                Str_delete(&dd->explicit_type, &(Bool){0});
                { Str *_fa = expect_text(p, TokenType_Ident()); dd->explicit_type = *_fa; free(_fa); }
            }
            ;
            ExprData *_t3459 = ExprData_Decl(dd);
            (void)_t3459;
            Declaration_delete(dd, &(Bool){1});
            Expr *variant = Expr_new(_t3459, v_line, v_col, &p->path);
            (void)variant;
            ExprData_delete(_t3459, &(Bool){1});
            ;
            ;
            Expr_add_child(body, variant);
            Bool _t3460; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3460 = *_hp; free(_hp); }
            (void)_t3460;
            if (_t3460) {
                Token *_t3451 = advance(p);
                (void)_t3451;
            }
            ;
        }
    }
    ;
    expect_token(p, TokenType_RBrace());
    Expr_add_child(def, body);
    return def;
}

Expr * parse_call(Parser * p, Str * name, U32 * call_line, U32 * call_col) {
    (void)p;
    (void)name;
    (void)call_line;
    (void)call_col;
    Token *_t3498 = advance(p);
    (void)_t3498;
    Expr *call = Expr_new(ExprData_FCall(), DEREF(call_line), DEREF(call_col), &p->path);
    (void)call;
    Str *_t3499 = Str_clone(name);
    (void)_t3499;
    ExprData *_t3500 = ExprData_Ident(_t3499);
    (void)_t3500;
    Str_delete(_t3499, &(Bool){1});
    Expr *callee = Expr_new(_t3500, DEREF(call_line), DEREF(call_col), &p->path);
    (void)callee;
    ExprData_delete(_t3500, &(Bool){1});
    Expr_add_child(call, callee);
    while (1) {
        Bool _t3488; { Bool *_hp = (Bool *)check(p, TokenType_RParen()); _t3488 = *_hp; free(_hp); }
        (void)_t3488;
        Bool _t3489; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3489 = *_hp; free(_hp); }
        (void)_t3489;
        Bool _t3490 = Bool_not(_t3488);
        (void)_t3490;
        ;
        Bool _t3491 = Bool_not(_t3489);
        (void)_t3491;
        ;
        Bool _wcond3469 = Bool_and(_t3490, _t3491);
        (void)_wcond3469;
        ;
        ;
        if (_wcond3469) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3492; { Bool *_hp = (Bool *)check(p, TokenType_Ident()); _t3492 = *_hp; free(_hp); }
        (void)_t3492;
        if (_t3492) {
            U32 _t3480 = 1;
            (void)_t3480;
            U32 _t3481 = U32_add(p->pos, _t3480);
            (void)_t3481;
            ;
            Bool _t3482; { Bool *_hp = (Bool *)U32_lt(&(U32){_t3481}, &p->count); _t3482 = *_hp; free(_hp); }
            (void)_t3482;
            ;
            if (_t3482) {
                U32 _t3475 = 1;
                (void)_t3475;
                U32 _t3476 = U32_add(p->pos, _t3475);
                (void)_t3476;
                ;
                I64 _t3477 = U32_to_i64(_t3476);
                (void)_t3477;
                ;
                U64 *_t3478 = malloc(sizeof(U64)); *_t3478 = I64_to_u64(_t3477);
                (void)_t3478;
                ;
                Token *next_tok = Vec_get(&p->tokens, _t3478);
                (void)next_tok;
                Bool _t3479; { Bool *_hp = (Bool *)TokenType_eq(&next_tok->type, TokenType_Eq()); _t3479 = *_hp; free(_hp); }
                (void)_t3479;
                U64_delete(_t3478, &(Bool){1});
                if (_t3479) {
                    U32 na_line; { U32 *_hp = (U32 *)peek_line(p); na_line = *_hp; free(_hp); }
                    (void)na_line;
                    U32 na_col; { U32 *_hp = (U32 *)peek_col(p); na_col = *_hp; free(_hp); }
                    (void)na_col;
                    Str *aname = expect_text(p, TokenType_Ident());
                    (void)aname;
                    Token *_t3471 = advance(p);
                    (void)_t3471;
                    ExprData *_t3472 = ExprData_NamedArg(aname);
                    (void)_t3472;
                    Str_delete(aname, &(Bool){1});
                    Expr *na = Expr_new(_t3472, na_line, na_col, &p->path);
                    (void)na;
                    ExprData_delete(_t3472, &(Bool){1});
                    ;
                    ;
                    Expr *_t3473 = parse_expression(p);
                    (void)_t3473;
                    Expr_add_child(na, _t3473);
                    Expr_add_child(call, na);
                    Bool _t3474; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3474 = *_hp; free(_hp); }
                    (void)_t3474;
                    if (_t3474) {
                        Token *_t3470 = advance(p);
                        (void)_t3470;
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
        Bool _t3493; { Bool *_hp = (Bool *)check(p, TokenType_DotDot()); _t3493 = *_hp; free(_hp); }
        (void)_t3493;
        if (_t3493) {
            Token *_t3483 = advance(p);
            (void)_t3483;
            Bool _t3484 = 1;
            (void)_t3484;
            is_splat = _t3484;
            ;
        }
        ;
        Bool is_own_arg = 0;
        (void)is_own_arg;
        Bool _t3494; { Bool *_hp = (Bool *)check(p, TokenType_KwOwn()); _t3494 = *_hp; free(_hp); }
        (void)_t3494;
        if (_t3494) {
            Token *_t3485 = advance(p);
            (void)_t3485;
            Bool _t3486 = 1;
            (void)_t3486;
            is_own_arg = _t3486;
            ;
        }
        ;
        Expr *arg = parse_expression(p);
        (void)arg;
        Bool _t3495 = Bool_clone(&(Bool){is_own_arg});
        (void)_t3495;
        ;
        arg->is_own_arg = _t3495;
        ;
        Bool _t3496 = Bool_clone(&(Bool){is_splat});
        (void)_t3496;
        ;
        arg->is_splat = _t3496;
        ;
        Expr_add_child(call, arg);
        Bool _t3497; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3497 = *_hp; free(_hp); }
        (void)_t3497;
        if (_t3497) {
            Token *_t3487 = advance(p);
            (void)_t3487;
        }
        ;
    }
    expect_token(p, TokenType_RParen());
    return call;
}

Expr * parse_expression(Parser * p) {
    (void)p;
    U32 t_line; { U32 *_hp = (U32 *)peek_line(p); t_line = *_hp; free(_hp); }
    (void)t_line;
    U32 t_col; { U32 *_hp = (U32 *)peek_col(p); t_col = *_hp; free(_hp); }
    (void)t_col;
    Token *t = peek(p);
    (void)t;
    U32 _t3682 = 0;
    (void)_t3682;
    U32 _t3683 = 0;
    (void)_t3683;
    Expr *e = Expr_new(ExprData_Body(), _t3682, _t3683, &p->path);
    (void)e;
    ;
    ;
    Bool e_set = 0;
    (void)e_set;
    Bool _t3684; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t3684 = *_hp; free(_hp); }
    (void)_t3684;
    if (_t3684) {
        Token *_t3501 = advance(p);
        (void)_t3501;
        Str *_t3502 = Str_clone(&t->text);
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
    }
    ;
    Bool _t3685 = Bool_not(e_set);
    (void)_t3685;
    Bool _t3686; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t3686 = *_hp; free(_hp); }
    (void)_t3686;
    Bool _t3687 = Bool_and(_t3685, _t3686);
    (void)_t3687;
    ;
    ;
    if (_t3687) {
        Token *_t3505 = advance(p);
        (void)_t3505;
        Str *_t3506 = Str_clone(&t->text);
        (void)_t3506;
        ExprData *_t3507 = ExprData_LiteralNum(_t3506);
        (void)_t3507;
        Str_delete(_t3506, &(Bool){1});
        e = Expr_new(_t3507, t_line, t_col, &p->path);
        ExprData_delete(_t3507, &(Bool){1});
        Bool _t3508 = 1;
        (void)_t3508;
        e_set = _t3508;
        ;
    }
    ;
    Bool _t3688 = Bool_not(e_set);
    (void)_t3688;
    Bool _t3689; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Char()); _t3689 = *_hp; free(_hp); }
    (void)_t3689;
    Bool _t3690 = Bool_and(_t3688, _t3689);
    (void)_t3690;
    ;
    ;
    if (_t3690) {
        Token *_t3538 = advance(p);
        (void)_t3538;
        Str *ch = Str_clone(&t->text);
        (void)ch;
        I64 byte_val = 0;
        (void)byte_val;
        U64 _t3539; { U64 *_hp = (U64 *)Str_len(ch); _t3539 = *_hp; free(_hp); }
        (void)_t3539;
        U64 _t3540 = 0;
        (void)_t3540;
        U64 *_t3541 = malloc(sizeof(U64));
        *_t3541 = 0;
        (void)_t3541;
        U8 *_t3542 = Str_get(ch, _t3541);
        (void)_t3542;
        U8 _t3543 = 92;
        (void)_t3543;
        Bool _t3544; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3539}, &(U64){_t3540}); _t3544 = *_hp; free(_hp); }
        (void)_t3544;
        ;
        ;
        Bool _t3545 = U8_eq(DEREF(_t3542), _t3543);
        (void)_t3545;
        U64_delete(_t3541, &(Bool){1});
        ;
        Bool _t3546 = Bool_and(_t3544, _t3545);
        (void)_t3546;
        ;
        ;
        if (_t3546) {
            U64 _t3529; { U64 *_hp = (U64 *)Str_len(ch); _t3529 = *_hp; free(_hp); }
            (void)_t3529;
            U64 _t3530 = 1;
            (void)_t3530;
            Bool _t3531; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3529}, &(U64){_t3530}); _t3531 = *_hp; free(_hp); }
            (void)_t3531;
            ;
            ;
            if (_t3531) {
                U64 *_t3526 = malloc(sizeof(U64));
                *_t3526 = 1;
                (void)_t3526;
                U8 *c2 = Str_get(ch, _t3526);
                (void)c2;
                U8 _t3527 = 110;
                (void)_t3527;
                Bool _t3528 = U8_eq(DEREF(c2), _t3527);
                (void)_t3528;
                ;
                if (_t3528) {
                    I64 _t3509 = 10;
                    (void)_t3509;
                    byte_val = _t3509;
                    ;
                } else {
                    U8 _t3524 = 116;
                    (void)_t3524;
                    Bool _t3525 = U8_eq(DEREF(c2), _t3524);
                    (void)_t3525;
                    ;
                    if (_t3525) {
                        I64 _t3510 = 9;
                        (void)_t3510;
                        byte_val = _t3510;
                        ;
                    } else {
                        U8 _t3522 = 114;
                        (void)_t3522;
                        Bool _t3523 = U8_eq(DEREF(c2), _t3522);
                        (void)_t3523;
                        ;
                        if (_t3523) {
                            I64 _t3511 = 13;
                            (void)_t3511;
                            byte_val = _t3511;
                            ;
                        } else {
                            U8 _t3520 = 92;
                            (void)_t3520;
                            Bool _t3521 = U8_eq(DEREF(c2), _t3520);
                            (void)_t3521;
                            ;
                            if (_t3521) {
                                I64 _t3512 = 92;
                                (void)_t3512;
                                byte_val = _t3512;
                                ;
                            } else {
                                U8 _t3518 = 39;
                                (void)_t3518;
                                Bool _t3519 = U8_eq(DEREF(c2), _t3518);
                                (void)_t3519;
                                ;
                                if (_t3519) {
                                    I64 _t3513 = 39;
                                    (void)_t3513;
                                    byte_val = _t3513;
                                    ;
                                } else {
                                    U8 _t3516 = 48;
                                    (void)_t3516;
                                    Bool _t3517 = U8_eq(DEREF(c2), _t3516);
                                    (void)_t3517;
                                    ;
                                    if (_t3517) {
                                        I64 _t3514 = 0;
                                        (void)_t3514;
                                        byte_val = _t3514;
                                        ;
                                    } else {
                                        I64 _t3515 = U8_to_i64(DEREF(c2));
                                        (void)_t3515;
                                        byte_val = _t3515;
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
                U64_delete(_t3526, &(Bool){1});
                ;
            }
            ;
        } else {
            U64 _t3535; { U64 *_hp = (U64 *)Str_len(ch); _t3535 = *_hp; free(_hp); }
            (void)_t3535;
            U64 _t3536 = 0;
            (void)_t3536;
            Bool _t3537; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3535}, &(U64){_t3536}); _t3537 = *_hp; free(_hp); }
            (void)_t3537;
            ;
            ;
            if (_t3537) {
                U64 *_t3532 = malloc(sizeof(U64));
                *_t3532 = 0;
                (void)_t3532;
                U8 *_t3533 = Str_get(ch, _t3532);
                (void)_t3533;
                I64 _t3534 = U8_to_i64(DEREF(_t3533));
                (void)_t3534;
                U64_delete(_t3532, &(Bool){1});
                byte_val = _t3534;
                ;
            }
            ;
        }
        ;
        Str_delete(ch, &(Bool){1});
        Str *_t3547 = I64_to_str(&(I64){byte_val});
        (void)_t3547;
        ;
        ExprData *_t3548 = ExprData_LiteralNum(_t3547);
        (void)_t3548;
        Str_delete(_t3547, &(Bool){1});
        e = Expr_new(_t3548, t_line, t_col, &p->path);
        ExprData_delete(_t3548, &(Bool){1});
        TilType_delete(&e->til_type, &(Bool){0});
        { TilType *_fa = TilType_clone(TilType_U8()); e->til_type = *_fa; free(_fa); }
        Bool _t3549 = 1;
        (void)_t3549;
        e_set = _t3549;
        ;
    }
    ;
    Bool _t3691; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t3691 = *_hp; free(_hp); }
    (void)_t3691;
    Bool _t3692; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t3692 = *_hp; free(_hp); }
    (void)_t3692;
    Bool _t3693 = Bool_not(e_set);
    (void)_t3693;
    Bool _t3694 = Bool_or(_t3691, _t3692);
    (void)_t3694;
    ;
    ;
    Bool _t3695 = Bool_and(_t3693, _t3694);
    (void)_t3695;
    ;
    ;
    if (_t3695) {
        Token *_t3550 = advance(p);
        (void)_t3550;
        Str *_t3551 = Str_clone(&t->text);
        (void)_t3551;
        ExprData *_t3552 = ExprData_LiteralBool(_t3551);
        (void)_t3552;
        Str_delete(_t3551, &(Bool){1});
        e = Expr_new(_t3552, t_line, t_col, &p->path);
        ExprData_delete(_t3552, &(Bool){1});
        Bool _t3553 = 1;
        (void)_t3553;
        e_set = _t3553;
        ;
    }
    ;
    Bool _t3696 = Bool_not(e_set);
    (void)_t3696;
    Bool _t3697; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t3697 = *_hp; free(_hp); }
    (void)_t3697;
    Bool _t3698 = Bool_and(_t3696, _t3697);
    (void)_t3698;
    ;
    ;
    if (_t3698) {
        Token *_t3589 = advance(p);
        (void)_t3589;
        Str *name = Str_clone(&t->text);
        (void)name;
        Str *_t3590 = Str_lit("__LOC__", 7ULL);
        (void)_t3590;
        Bool _t3591; { Bool *_hp = (Bool *)Str_eq(name, _t3590); _t3591 = *_hp; free(_hp); }
        (void)_t3591;
        Str_delete(_t3590, &(Bool){1});
        if (_t3591) {
            Str *_t3554 = Str_lit("Str", 3ULL);
            (void)_t3554;
            U64 _t3555; { U64 *_hp = (U64 *)Str_size(); _t3555 = *_hp; free(_hp); }
            (void)_t3555;
            U64 _t3556 = 5;
            (void)_t3556;
            Array *_va67 = Array_new(_t3554, &(U64){_t3555}, &(U64){_t3556});
            (void)_va67;
            Str_delete(_t3554, &(Bool){1});
            ;
            ;
            U64 _t3557 = 0;
            (void)_t3557;
            Str *_t3558 = Str_clone(&p->path);
            (void)_t3558;
            Array_set(_va67, &(U64){_t3557}, _t3558);
            ;
            U64 _t3559 = 1;
            (void)_t3559;
            Str *_t3560 = Str_lit(":", 1ULL);
            (void)_t3560;
            Array_set(_va67, &(U64){_t3559}, _t3560);
            ;
            U64 _t3561 = 2;
            (void)_t3561;
            Str *_t3562 = U32_to_str(&(U32){t_line});
            (void)_t3562;
            Array_set(_va67, &(U64){_t3561}, _t3562);
            ;
            U64 _t3563 = 3;
            (void)_t3563;
            Str *_t3564 = Str_lit(":", 1ULL);
            (void)_t3564;
            Array_set(_va67, &(U64){_t3563}, _t3564);
            ;
            U64 _t3565 = 4;
            (void)_t3565;
            Str *_t3566 = U32_to_str(&(U32){t_col});
            (void)_t3566;
            Array_set(_va67, &(U64){_t3565}, _t3566);
            ;
            Str *_t3567 = format(_va67);
            (void)_t3567;
            ExprData *_t3568 = ExprData_LiteralStr(_t3567);
            (void)_t3568;
            Str_delete(_t3567, &(Bool){1});
            e = Expr_new(_t3568, t_line, t_col, &p->path);
            ExprData_delete(_t3568, &(Bool){1});
            Bool _t3569 = 1;
            (void)_t3569;
            e_set = _t3569;
            ;
        } else {
            Str *_t3587 = Str_lit("__FILE__", 8ULL);
            (void)_t3587;
            Bool _t3588; { Bool *_hp = (Bool *)Str_eq(name, _t3587); _t3588 = *_hp; free(_hp); }
            (void)_t3588;
            Str_delete(_t3587, &(Bool){1});
            if (_t3588) {
                Str *_t3570 = Str_clone(&p->path);
                (void)_t3570;
                ExprData *_t3571 = ExprData_LiteralStr(_t3570);
                (void)_t3571;
                Str_delete(_t3570, &(Bool){1});
                e = Expr_new(_t3571, t_line, t_col, &p->path);
                ExprData_delete(_t3571, &(Bool){1});
                Bool _t3572 = 1;
                (void)_t3572;
                e_set = _t3572;
                ;
            } else {
                Str *_t3585 = Str_lit("__LINE__", 8ULL);
                (void)_t3585;
                Bool _t3586; { Bool *_hp = (Bool *)Str_eq(name, _t3585); _t3586 = *_hp; free(_hp); }
                (void)_t3586;
                Str_delete(_t3585, &(Bool){1});
                if (_t3586) {
                    Str *_t3573 = U32_to_str(&(U32){t_line});
                    (void)_t3573;
                    ExprData *_t3574 = ExprData_LiteralNum(_t3573);
                    (void)_t3574;
                    Str_delete(_t3573, &(Bool){1});
                    e = Expr_new(_t3574, t_line, t_col, &p->path);
                    ExprData_delete(_t3574, &(Bool){1});
                    Bool _t3575 = 1;
                    (void)_t3575;
                    e_set = _t3575;
                    ;
                } else {
                    Str *_t3583 = Str_lit("__COL__", 7ULL);
                    (void)_t3583;
                    Bool _t3584; { Bool *_hp = (Bool *)Str_eq(name, _t3583); _t3584 = *_hp; free(_hp); }
                    (void)_t3584;
                    Str_delete(_t3583, &(Bool){1});
                    if (_t3584) {
                        Str *_t3576 = U32_to_str(&(U32){t_col});
                        (void)_t3576;
                        ExprData *_t3577 = ExprData_LiteralNum(_t3576);
                        (void)_t3577;
                        Str_delete(_t3576, &(Bool){1});
                        e = Expr_new(_t3577, t_line, t_col, &p->path);
                        ExprData_delete(_t3577, &(Bool){1});
                        Bool _t3578 = 1;
                        (void)_t3578;
                        e_set = _t3578;
                        ;
                    } else {
                        Bool _t3582; { Bool *_hp = (Bool *)check(p, TokenType_LParen()); _t3582 = *_hp; free(_hp); }
                        (void)_t3582;
                        if (_t3582) {
                            e = parse_call(p, name, &(U32){t_line}, &(U32){t_col});
                            Bool _t3579 = 1;
                            (void)_t3579;
                            e_set = _t3579;
                            ;
                        } else {
                            ExprData *_t3580 = ExprData_Ident(name);
                            (void)_t3580;
                            e = Expr_new(_t3580, t_line, t_col, &p->path);
                            ExprData_delete(_t3580, &(Bool){1});
                            Bool _t3581 = 1;
                            (void)_t3581;
                            e_set = _t3581;
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
    Bool _t3699; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFunc()); _t3699 = *_hp; free(_hp); }
    (void)_t3699;
    Bool _t3700; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwProc()); _t3700 = *_hp; free(_hp); }
    (void)_t3700;
    Bool _t3701 = Bool_or(_t3699, _t3700);
    (void)_t3701;
    ;
    ;
    Bool _t3702; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTest()); _t3702 = *_hp; free(_hp); }
    (void)_t3702;
    Bool _t3703 = Bool_or(_t3701, _t3702);
    (void)_t3703;
    ;
    ;
    Bool _t3704; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMacro()); _t3704 = *_hp; free(_hp); }
    (void)_t3704;
    Bool _t3705 = Bool_or(_t3703, _t3704);
    (void)_t3705;
    ;
    ;
    Bool _t3706; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtFunc()); _t3706 = *_hp; free(_hp); }
    (void)_t3706;
    Bool _t3707 = Bool_or(_t3705, _t3706);
    (void)_t3707;
    ;
    ;
    Bool _t3708; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtProc()); _t3708 = *_hp; free(_hp); }
    (void)_t3708;
    Bool _t3709 = Bool_not(e_set);
    (void)_t3709;
    Bool _t3710 = Bool_or(_t3707, _t3708);
    (void)_t3710;
    ;
    ;
    Bool _t3711 = Bool_and(_t3709, _t3710);
    (void)_t3711;
    ;
    ;
    if (_t3711) {
        Expr *_t3592 = parse_func_def(p);
        (void)_t3592;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3592;
    }
    ;
    Bool _t3712; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwStruct()); _t3712 = *_hp; free(_hp); }
    (void)_t3712;
    Bool _t3713; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtStruct()); _t3713 = *_hp; free(_hp); }
    (void)_t3713;
    Bool _t3714 = Bool_not(e_set);
    (void)_t3714;
    Bool _t3715 = Bool_or(_t3712, _t3713);
    (void)_t3715;
    ;
    ;
    Bool _t3716 = Bool_and(_t3714, _t3715);
    (void)_t3716;
    ;
    ;
    if (_t3716) {
        Expr *_t3593 = parse_struct_def(p);
        (void)_t3593;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3593;
    }
    ;
    Bool _t3717 = Bool_not(e_set);
    (void)_t3717;
    Bool _t3718; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwEnum()); _t3718 = *_hp; free(_hp); }
    (void)_t3718;
    Bool _t3719 = Bool_and(_t3717, _t3718);
    (void)_t3719;
    ;
    ;
    if (_t3719) {
        Expr *_t3594 = parse_enum_def(p);
        (void)_t3594;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3594;
    }
    ;
    Bool _t3720 = Bool_not(e_set);
    (void)_t3720;
    Bool _t3721; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t3721 = *_hp; free(_hp); }
    (void)_t3721;
    Bool _t3722 = Bool_and(_t3720, _t3721);
    (void)_t3722;
    ;
    ;
    if (_t3722) {
        Token *_t3618 = advance(p);
        (void)_t3618;
        Expr *first = parse_expression(p);
        (void)first;
        Bool _t3619; { Bool *_hp = (Bool *)check(p, TokenType_Colon()); _t3619 = *_hp; free(_hp); }
        (void)_t3619;
        if (_t3619) {
            e = Expr_new(ExprData_MapLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Token *_t3605 = advance(p);
            (void)_t3605;
            Expr *_t3606 = parse_expression(p);
            (void)_t3606;
            Expr_add_child(e, _t3606);
            Bool _t3607; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3607 = *_hp; free(_hp); }
            (void)_t3607;
            if (_t3607) {
                Token *_t3595 = advance(p);
                (void)_t3595;
            }
            ;
            while (1) {
                Bool _t3598; { Bool *_hp = (Bool *)check(p, TokenType_RBrace()); _t3598 = *_hp; free(_hp); }
                (void)_t3598;
                Bool _t3599; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3599 = *_hp; free(_hp); }
                (void)_t3599;
                Bool _t3600 = Bool_not(_t3598);
                (void)_t3600;
                ;
                Bool _t3601 = Bool_not(_t3599);
                (void)_t3601;
                ;
                Bool _wcond3596 = Bool_and(_t3600, _t3601);
                (void)_wcond3596;
                ;
                ;
                if (_wcond3596) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3602 = parse_expression(p);
                (void)_t3602;
                Expr_add_child(e, _t3602);
                expect_token(p, TokenType_Colon());
                Expr *_t3603 = parse_expression(p);
                (void)_t3603;
                Expr_add_child(e, _t3603);
                Bool _t3604; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3604 = *_hp; free(_hp); }
                (void)_t3604;
                if (_t3604) {
                    Token *_t3597 = advance(p);
                    (void)_t3597;
                }
                ;
            }
        } else {
            e = Expr_new(ExprData_SetLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Bool _t3617; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3617 = *_hp; free(_hp); }
            (void)_t3617;
            if (_t3617) {
                Token *_t3608 = advance(p);
                (void)_t3608;
            }
            ;
            while (1) {
                Bool _t3611; { Bool *_hp = (Bool *)check(p, TokenType_RBrace()); _t3611 = *_hp; free(_hp); }
                (void)_t3611;
                Bool _t3612; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3612 = *_hp; free(_hp); }
                (void)_t3612;
                Bool _t3613 = Bool_not(_t3611);
                (void)_t3613;
                ;
                Bool _t3614 = Bool_not(_t3612);
                (void)_t3614;
                ;
                Bool _wcond3609 = Bool_and(_t3613, _t3614);
                (void)_wcond3609;
                ;
                ;
                if (_wcond3609) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3615 = parse_expression(p);
                (void)_t3615;
                Expr_add_child(e, _t3615);
                Bool _t3616; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3616 = *_hp; free(_hp); }
                (void)_t3616;
                if (_t3616) {
                    Token *_t3610 = advance(p);
                    (void)_t3610;
                }
                ;
            }
        }
        ;
        expect_token(p, TokenType_RBrace());
        Bool _t3620 = 1;
        (void)_t3620;
        e_set = _t3620;
        ;
    }
    ;
    Bool _t3723 = Bool_not(e_set);
    (void)_t3723;
    ;
    if (_t3723) {
        Str *_t3621 = Str_lit("Str", 3ULL);
        (void)_t3621;
        U64 _t3622; { U64 *_hp = (U64 *)Str_size(); _t3622 = *_hp; free(_hp); }
        (void)_t3622;
        U64 _t3623 = 8;
        (void)_t3623;
        Array *_va68 = Array_new(_t3621, &(U64){_t3622}, &(U64){_t3623});
        (void)_va68;
        Str_delete(_t3621, &(Bool){1});
        ;
        ;
        U64 _t3624 = 0;
        (void)_t3624;
        Str *_t3625 = Str_clone(&p->path);
        (void)_t3625;
        Array_set(_va68, &(U64){_t3624}, _t3625);
        ;
        U64 _t3626 = 1;
        (void)_t3626;
        Str *_t3627 = Str_lit(":", 1ULL);
        (void)_t3627;
        Array_set(_va68, &(U64){_t3626}, _t3627);
        ;
        U64 _t3628 = 2;
        (void)_t3628;
        Str *_t3629 = U32_to_str(&(U32){t_line});
        (void)_t3629;
        Array_set(_va68, &(U64){_t3628}, _t3629);
        ;
        U64 _t3630 = 3;
        (void)_t3630;
        Str *_t3631 = Str_lit(":", 1ULL);
        (void)_t3631;
        Array_set(_va68, &(U64){_t3630}, _t3631);
        ;
        U64 _t3632 = 4;
        (void)_t3632;
        Str *_t3633 = U32_to_str(&(U32){t_col});
        (void)_t3633;
        Array_set(_va68, &(U64){_t3632}, _t3633);
        ;
        U64 _t3634 = 5;
        (void)_t3634;
        Str *_t3635 = Str_lit(": unexpected token '", 20ULL);
        (void)_t3635;
        Array_set(_va68, &(U64){_t3634}, _t3635);
        ;
        U64 _t3636 = 6;
        (void)_t3636;
        Str *_t3637 = Str_clone(&t->text);
        (void)_t3637;
        Array_set(_va68, &(U64){_t3636}, _t3637);
        ;
        U64 _t3638 = 7;
        (void)_t3638;
        Str *_t3639 = Str_lit("'", 1ULL);
        (void)_t3639;
        Array_set(_va68, &(U64){_t3638}, _t3639);
        ;
        Str *_t3640 = Str_lit("src/self/parser.til:514:15", 26ULL);
        (void)_t3640;
        panic(_t3640, _va68);
        Str_delete(_t3640, &(Bool){1});
    }
    ;
    ;
    ;
    while (1) {
        Bool _wcond3641; { Bool *_hp = (Bool *)check(p, TokenType_Dot()); _wcond3641 = *_hp; free(_hp); }
        (void)_wcond3641;
        if (_wcond3641) {
        } else {
            ;
            break;
        }
        ;
        Token *_t3672 = advance(p);
        (void)_t3672;
        U32 f_line; { U32 *_hp = (U32 *)peek_line(p); f_line = *_hp; free(_hp); }
        (void)f_line;
        U32 f_col; { U32 *_hp = (U32 *)peek_col(p); f_col = *_hp; free(_hp); }
        (void)f_col;
        Str *fname = expect_text(p, TokenType_Ident());
        (void)fname;
        Bool _t3673; { Bool *_hp = (Bool *)check(p, TokenType_LParen()); _t3673 = *_hp; free(_hp); }
        (void)_t3673;
        if (_t3673) {
            Token *_t3667 = advance(p);
            (void)_t3667;
            ExprData *_t3668 = ExprData_FieldAccess(fname);
            (void)_t3668;
            Expr *callee = Expr_new(_t3668, f_line, f_col, &p->path);
            (void)callee;
            ExprData_delete(_t3668, &(Bool){1});
            Expr *_t3669 = Expr_clone(e);
            (void)_t3669;
            Expr_add_child(callee, _t3669);
            Expr *mcall = Expr_new(ExprData_FCall(), f_line, f_col, &p->path);
            (void)mcall;
            Expr_add_child(mcall, callee);
            while (1) {
                Bool _t3659; { Bool *_hp = (Bool *)check(p, TokenType_RParen()); _t3659 = *_hp; free(_hp); }
                (void)_t3659;
                Bool _t3660; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3660 = *_hp; free(_hp); }
                (void)_t3660;
                Bool _t3661 = Bool_not(_t3659);
                (void)_t3661;
                ;
                Bool _t3662 = Bool_not(_t3660);
                (void)_t3662;
                ;
                Bool _wcond3642 = Bool_and(_t3661, _t3662);
                (void)_wcond3642;
                ;
                ;
                if (_wcond3642) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3663; { Bool *_hp = (Bool *)check(p, TokenType_Ident()); _t3663 = *_hp; free(_hp); }
                (void)_t3663;
                if (_t3663) {
                    U32 _t3653 = 1;
                    (void)_t3653;
                    U32 _t3654 = U32_add(p->pos, _t3653);
                    (void)_t3654;
                    ;
                    Bool _t3655; { Bool *_hp = (Bool *)U32_lt(&(U32){_t3654}, &p->count); _t3655 = *_hp; free(_hp); }
                    (void)_t3655;
                    ;
                    if (_t3655) {
                        U32 _t3648 = 1;
                        (void)_t3648;
                        U32 _t3649 = U32_add(p->pos, _t3648);
                        (void)_t3649;
                        ;
                        I64 _t3650 = U32_to_i64(_t3649);
                        (void)_t3650;
                        ;
                        U64 *_t3651 = malloc(sizeof(U64)); *_t3651 = I64_to_u64(_t3650);
                        (void)_t3651;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3651);
                        (void)nt;
                        Bool _t3652; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3652 = *_hp; free(_hp); }
                        (void)_t3652;
                        U64_delete(_t3651, &(Bool){1});
                        if (_t3652) {
                            U32 na_line; { U32 *_hp = (U32 *)peek_line(p); na_line = *_hp; free(_hp); }
                            (void)na_line;
                            U32 na_col; { U32 *_hp = (U32 *)peek_col(p); na_col = *_hp; free(_hp); }
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3644 = advance(p);
                            (void)_t3644;
                            ExprData *_t3645 = ExprData_NamedArg(aname);
                            (void)_t3645;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3645, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3645, &(Bool){1});
                            ;
                            ;
                            Expr *_t3646 = parse_expression(p);
                            (void)_t3646;
                            Expr_add_child(na, _t3646);
                            Expr_add_child(mcall, na);
                            Bool _t3647; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3647 = *_hp; free(_hp); }
                            (void)_t3647;
                            if (_t3647) {
                                Token *_t3643 = advance(p);
                                (void)_t3643;
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
                Bool _t3664; { Bool *_hp = (Bool *)check(p, TokenType_KwOwn()); _t3664 = *_hp; free(_hp); }
                (void)_t3664;
                if (_t3664) {
                    Token *_t3656 = advance(p);
                    (void)_t3656;
                    Bool _t3657 = 1;
                    (void)_t3657;
                    is_own_arg = _t3657;
                    ;
                }
                ;
                Expr *marg = parse_expression(p);
                (void)marg;
                Bool _t3665 = Bool_clone(&(Bool){is_own_arg});
                (void)_t3665;
                ;
                marg->is_own_arg = _t3665;
                ;
                Expr_add_child(mcall, marg);
                Bool _t3666; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3666 = *_hp; free(_hp); }
                (void)_t3666;
                if (_t3666) {
                    Token *_t3658 = advance(p);
                    (void)_t3658;
                }
                ;
            }
            expect_token(p, TokenType_RParen());
            e = Expr_clone(mcall);
            Expr_delete(mcall, &(Bool){1});
        } else {
            ExprData *_t3670 = ExprData_FieldAccess(fname);
            (void)_t3670;
            Expr *access = Expr_new(_t3670, f_line, f_col, &p->path);
            (void)access;
            ExprData_delete(_t3670, &(Bool){1});
            Expr *_t3671 = Expr_clone(e);
            (void)_t3671;
            Expr_add_child(access, _t3671);
            e = Expr_clone(access);
            Expr_delete(access, &(Bool){1});
        }
        ;
        ;
        ;
        Str_delete(fname, &(Bool){1});
    }
    Bool _t3724; { Bool *_hp = (Bool *)check(p, TokenType_DotDot()); _t3724 = *_hp; free(_hp); }
    (void)_t3724;
    if (_t3724) {
        U32 dt_line; { U32 *_hp = (U32 *)peek_line(p); dt_line = *_hp; free(_hp); }
        (void)dt_line;
        U32 dt_col; { U32 *_hp = (U32 *)peek_col(p); dt_col = *_hp; free(_hp); }
        (void)dt_col;
        Token *_t3674 = advance(p);
        (void)_t3674;
        Expr *rhs = parse_expression(p);
        (void)rhs;
        Str *_t3675 = Str_lit("Range", 5ULL);
        (void)_t3675;
        Str *_t3676 = Str_clone(_t3675);
        (void)_t3676;
        Str_delete(_t3675, &(Bool){1});
        ExprData *_t3677 = ExprData_Ident(_t3676);
        (void)_t3677;
        Str_delete(_t3676, &(Bool){1});
        Expr *range_ident = Expr_new(_t3677, dt_line, dt_col, &p->path);
        (void)range_ident;
        ExprData_delete(_t3677, &(Bool){1});
        Str *_t3678 = Str_lit("new", 3ULL);
        (void)_t3678;
        Str *_t3679 = Str_clone(_t3678);
        (void)_t3679;
        Str_delete(_t3678, &(Bool){1});
        ExprData *_t3680 = ExprData_FieldAccess(_t3679);
        (void)_t3680;
        Str_delete(_t3679, &(Bool){1});
        Expr *new_access = Expr_new(_t3680, dt_line, dt_col, &p->path);
        (void)new_access;
        ExprData_delete(_t3680, &(Bool){1});
        Expr_add_child(new_access, range_ident);
        Expr *rcall = Expr_new(ExprData_FCall(), dt_line, dt_col, &p->path);
        (void)rcall;
        ;
        ;
        Expr_add_child(rcall, new_access);
        Expr *_t3681 = Expr_clone(e);
        (void)_t3681;
        Expr_add_child(rcall, _t3681);
        Expr_add_child(rcall, rhs);
        e = Expr_clone(rcall);
        Expr_delete(rcall, &(Bool){1});
    }
    ;
    return e;
}

Expr * parse_statement_ident(Parser * p, Bool * is_mut, Bool * is_own) {
    (void)p;
    (void)is_mut;
    (void)is_own;
    U32 t_line; { U32 *_hp = (U32 *)peek_line(p); t_line = *_hp; free(_hp); }
    (void)t_line;
    U32 t_col; { U32 *_hp = (U32 *)peek_col(p); t_col = *_hp; free(_hp); }
    (void)t_col;
    Str *name = expect_text(p, TokenType_Ident());
    (void)name;
    Bool _t3913; { Bool *_hp = (Bool *)check(p, TokenType_ColonEq()); _t3913 = *_hp; free(_hp); }
    (void)_t3913;
    if (_t3913) {
        Token *_t3725 = advance(p);
        (void)_t3725;
        Bool _t3726 = Bool_clone(is_mut);
        (void)_t3726;
        Bool _t3727 = 0;
        (void)_t3727;
        Bool _t3728 = 0;
        (void)_t3728;
        Bool _t3729 = Bool_clone(is_own);
        (void)_t3729;
        I32 _t3730 = 0;
        (void)_t3730;
        I32 _t3731 = 0;
        (void)_t3731;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3726;
        dd->is_namespace = _t3727;
        dd->is_ref = _t3728;
        dd->is_own = _t3729;
        dd->field_offset = _t3730;
        dd->field_size = _t3731;
        dd->field_struct_def = NULL;
        dd->fn_sig = NULL;
        (void)dd;
        ;
        ;
        ;
        ;
        ;
        ;
        ExprData *_t3732 = ExprData_Decl(dd);
        (void)_t3732;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3732, t_line, t_col, &p->path);
        (void)decl;
        ExprData_delete(_t3732, &(Bool){1});
        Expr *_t3733 = parse_expression(p);
        (void)_t3733;
        Expr_add_child(decl, _t3733);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return decl;
    }
    ;
    Bool _t3914; { Bool *_hp = (Bool *)check(p, TokenType_Colon()); _t3914 = *_hp; free(_hp); }
    (void)_t3914;
    if (_t3914) {
        Token *_t3849 = advance(p);
        (void)_t3849;
        Bool _t3850; { Bool *_hp = (Bool *)check(p, TokenType_KwFunc()); _t3850 = *_hp; free(_hp); }
        (void)_t3850;
        Bool _t3851; { Bool *_hp = (Bool *)check(p, TokenType_KwProc()); _t3851 = *_hp; free(_hp); }
        (void)_t3851;
        Bool _t3852 = Bool_or(_t3850, _t3851);
        (void)_t3852;
        ;
        ;
        if (_t3852) {
            Expr *sig = parse_func_def(p);
            (void)sig;
            expect_token(p, TokenType_Eq());
            expect_token(p, TokenType_LParen());
            Bool _t3750; { Bool *_hp = (Bool *)ExprData_is_FuncDef(&sig->data); _t3750 = *_hp; free(_hp); }
            (void)_t3750;
            if (_t3750) {
                FunctionDef *sfd = ExprData_get_FuncDef(&sig->data);
                (void)sfd;
                Str *_t3747 = Str_lit("Str", 3ULL);
                (void)_t3747;
                U64 _t3748; { U64 *_hp = (U64 *)Str_size(); _t3748 = *_hp; free(_hp); }
                (void)_t3748;
                Vec *new_names = Vec_new(_t3747, &(U64){_t3748});
                (void)new_names;
                Str_delete(_t3747, &(Bool){1});
                ;
                {
                    U64 _fi3734 = 0;
                    (void)_fi3734;
                    while (1) {
                        U64 _t3736 = 0;
                        (void)_t3736;
                        U64 _t3737; { U64 *_hp = (U64 *)Vec_len(&sfd->param_names); _t3737 = *_hp; free(_hp); }
                        (void)_t3737;
                        Range *_t3738 = Range_new(_t3736, _t3737);
                        (void)_t3738;
                        ;
                        ;
                        U64 _t3739; { U64 *_hp = (U64 *)Range_len(_t3738); _t3739 = *_hp; free(_hp); }
                        (void)_t3739;
                        Range_delete(_t3738, &(Bool){1});
                        Bool _wcond3735; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3734}, &(U64){_t3739}); _wcond3735 = *_hp; free(_hp); }
                        (void)_wcond3735;
                        ;
                        if (_wcond3735) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 _t3740 = 0;
                        (void)_t3740;
                        U64 _t3741; { U64 *_hp = (U64 *)Vec_len(&sfd->param_names); _t3741 = *_hp; free(_hp); }
                        (void)_t3741;
                        Range *_t3742 = Range_new(_t3740, _t3741);
                        (void)_t3742;
                        ;
                        ;
                        U64 pi; { U64 *_hp = (U64 *)Range_get(_t3742, _fi3734); pi = *_hp; free(_hp); }
                        (void)pi;
                        Range_delete(_t3742, &(Bool){1});
                        U64 _t3743 = 1;
                        (void)_t3743;
                        U64 _t3744 = U64_add(_fi3734, _t3743);
                        (void)_t3744;
                        ;
                        _fi3734 = _t3744;
                        ;
                        U64 _t3745 = 0;
                        (void)_t3745;
                        Bool _t3746; { Bool *_hp = (Bool *)U64_gt(&(U64){pi}, &(U64){_t3745}); _t3746 = *_hp; free(_hp); }
                        (void)_t3746;
                        ;
                        ;
                        if (_t3746) {
                            expect_token(p, TokenType_Comma());
                        }
                        ;
                        Str *pn = expect_text(p, TokenType_Ident());
                        (void)pn;
                        Vec_push(new_names, pn);
                    }
                    ;
                }
                Vec_delete(&sfd->param_names, &(Bool){0});
                { Vec *_fa = Vec_clone(new_names); sfd->param_names = *_fa; free(_fa); }
                Vec_delete(new_names, &(Bool){1});
                ExprData_delete(&sig->data, &(Bool){0});
                { ExprData *_fa = ExprData_FuncDef(sfd); sig->data = *_fa; free(_fa); }
                FunctionDef_delete(sfd, &(Bool){1});
            }
            ;
            Bool _t3751; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3751 = *_hp; free(_hp); }
            (void)_t3751;
            if (_t3751) {
                Token *_t3749 = advance(p);
                (void)_t3749;
            }
            ;
            expect_token(p, TokenType_RParen());
            expect_token(p, TokenType_LBrace());
            Expr *_t3752 = parse_block(p);
            (void)_t3752;
            Expr_add_child(sig, _t3752);
            Bool _t3753 = Bool_clone(is_mut);
            (void)_t3753;
            Bool _t3754 = 0;
            (void)_t3754;
            Bool _t3755 = 0;
            (void)_t3755;
            Bool _t3756 = Bool_clone(is_own);
            (void)_t3756;
            I32 _t3757 = 0;
            (void)_t3757;
            I32 _t3758 = 0;
            (void)_t3758;
            Declaration *dd = malloc(sizeof(Declaration));
            { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
            dd->is_mut = _t3753;
            dd->is_namespace = _t3754;
            dd->is_ref = _t3755;
            dd->is_own = _t3756;
            dd->field_offset = _t3757;
            dd->field_size = _t3758;
            dd->field_struct_def = NULL;
            dd->fn_sig = NULL;
            (void)dd;
            ;
            ;
            ;
            ;
            ;
            ;
            ExprData *_t3759 = ExprData_Decl(dd);
            (void)_t3759;
            Declaration_delete(dd, &(Bool){1});
            Expr *decl = Expr_new(_t3759, t_line, t_col, &p->path);
            (void)decl;
            ExprData_delete(_t3759, &(Bool){1});
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
        I64 _t3853 = 0;
        (void)_t3853;
        I64 _t3854 = 1;
        (void)_t3854;
        I64 fn_sig_idx = I64_sub(_t3853, _t3854);
        (void)fn_sig_idx;
        ;
        ;
        Str *_t3855 = Str_lit("Fn", 2ULL);
        (void)_t3855;
        Bool _t3856; { Bool *_hp = (Bool *)Str_eq(type_name, _t3855); _t3856 = *_hp; free(_hp); }
        (void)_t3856;
        Str_delete(_t3855, &(Bool){1});
        if (_t3856) {
            Expr *sig = parse_fn_signature(p, &(U32){t_line}, &(U32){t_col});
            (void)sig;
            U32 _t3761 = 0;
            (void)_t3761;
            Bool _t3762; { Bool *_hp = (Bool *)U32_neq(&sig->line, &(U32){_t3761}); _t3762 = *_hp; free(_hp); }
            (void)_t3762;
            ;
            Expr_delete(sig, &(Bool){1});
            if (_t3762) {
                I64 _t3760 = 0;
                (void)_t3760;
                fn_sig_idx = _t3760;
                ;
            }
            ;
        }
        ;
        ;
        expect_token(p, TokenType_Eq());
        Bool _t3857; { Bool *_hp = (Bool *)check(p, TokenType_LParen()); _t3857 = *_hp; free(_hp); }
        (void)_t3857;
        if (_t3857) {
            U32 saved = p->pos;
            (void)saved;
            Token *_t3845 = advance(p);
            (void)_t3845;
            Bool is_fsf = 1;
            (void)is_fsf;
            while (1) {
                Bool _t3766; { Bool *_hp = (Bool *)check(p, TokenType_RParen()); _t3766 = *_hp; free(_hp); }
                (void)_t3766;
                Bool _t3767; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3767 = *_hp; free(_hp); }
                (void)_t3767;
                Bool _t3768 = Bool_not(_t3766);
                (void)_t3768;
                ;
                Bool _t3769 = Bool_not(_t3767);
                (void)_t3769;
                ;
                Bool _wcond3763 = Bool_and(_t3768, _t3769);
                (void)_wcond3763;
                ;
                ;
                if (_wcond3763) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3770; { Bool *_hp = (Bool *)check(p, TokenType_Ident()); _t3770 = *_hp; free(_hp); }
                (void)_t3770;
                Bool _t3771 = Bool_not(_t3770);
                (void)_t3771;
                ;
                if (_t3771) {
                    Bool _t3764 = 0;
                    (void)_t3764;
                    is_fsf = _t3764;
                    ;
                    ;
                    break;
                }
                ;
                Token *_t3772 = advance(p);
                (void)_t3772;
                Bool _t3773; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3773 = *_hp; free(_hp); }
                (void)_t3773;
                if (_t3773) {
                    Token *_t3765 = advance(p);
                    (void)_t3765;
                }
                ;
            }
            Bool _t3846; { Bool *_hp = (Bool *)check(p, TokenType_RParen()); _t3846 = *_hp; free(_hp); }
            (void)_t3846;
            Bool _t3847 = Bool_and(is_fsf, _t3846);
            (void)_t3847;
            ;
            if (_t3847) {
                Token *_t3775 = advance(p);
                (void)_t3775;
                Bool _t3776; { Bool *_hp = (Bool *)check(p, TokenType_LBrace()); _t3776 = *_hp; free(_hp); }
                (void)_t3776;
                Bool _t3777 = Bool_not(_t3776);
                (void)_t3777;
                ;
                if (_t3777) {
                    Bool _t3774 = 0;
                    (void)_t3774;
                    is_fsf = _t3774;
                    ;
                }
                ;
            } else {
                Bool _t3778 = 0;
                (void)_t3778;
                is_fsf = _t3778;
                ;
            }
            ;
            U32 _t3848 = U32_clone(&(U32){saved});
            (void)_t3848;
            ;
            p->pos = _t3848;
            ;
            if (is_fsf) {
                expect_token(p, TokenType_LParen());
                Str *_t3802 = Str_lit("Str", 3ULL);
                (void)_t3802;
                U64 _t3803; { U64 *_hp = (U64 *)Str_size(); _t3803 = *_hp; free(_hp); }
                (void)_t3803;
                Vec *pnames = Vec_new(_t3802, &(U64){_t3803});
                (void)pnames;
                Str_delete(_t3802, &(Bool){1});
                ;
                while (1) {
                    Bool _t3781; { Bool *_hp = (Bool *)check(p, TokenType_RParen()); _t3781 = *_hp; free(_hp); }
                    (void)_t3781;
                    Bool _wcond3779 = Bool_not(_t3781);
                    (void)_wcond3779;
                    ;
                    if (_wcond3779) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *pn = expect_text(p, TokenType_Ident());
                    (void)pn;
                    Vec_push(pnames, pn);
                    Bool _t3782; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3782 = *_hp; free(_hp); }
                    (void)_t3782;
                    if (_t3782) {
                        Token *_t3780 = advance(p);
                        (void)_t3780;
                    }
                    ;
                }
                expect_token(p, TokenType_RParen());
                expect_token(p, TokenType_LBrace());
                Expr *body = parse_block(p);
                (void)body;
                Str *_t3804 = Str_lit("Str", 3ULL);
                (void)_t3804;
                U64 _t3805; { U64 *_hp = (U64 *)Str_size(); _t3805 = *_hp; free(_hp); }
                (void)_t3805;
                Str *_t3806 = Str_lit("Str", 3ULL);
                (void)_t3806;
                U64 _t3807; { U64 *_hp = (U64 *)Str_size(); _t3807 = *_hp; free(_hp); }
                (void)_t3807;
                Str *_t3808 = Str_lit("Bool", 4ULL);
                (void)_t3808;
                U64 _t3809; { U64 *_hp = (U64 *)Bool_size(); _t3809 = *_hp; free(_hp); }
                (void)_t3809;
                Str *_t3810 = Str_lit("Bool", 4ULL);
                (void)_t3810;
                U64 _t3811; { U64 *_hp = (U64 *)Bool_size(); _t3811 = *_hp; free(_hp); }
                (void)_t3811;
                Str *_t3812 = Str_lit("Bool", 4ULL);
                (void)_t3812;
                U64 _t3813; { U64 *_hp = (U64 *)Bool_size(); _t3813 = *_hp; free(_hp); }
                (void)_t3813;
                Str *_t3814 = Str_lit("I64", 3ULL);
                (void)_t3814;
                U64 _t3815; { U64 *_hp = (U64 *)I64_size(); _t3815 = *_hp; free(_hp); }
                (void)_t3815;
                Str *_t3816 = Str_lit("I64", 3ULL);
                (void)_t3816;
                U64 _t3817; { U64 *_hp = (U64 *)I64_size(); _t3817 = *_hp; free(_hp); }
                (void)_t3817;
                I64 _t3818 = 0;
                (void)_t3818;
                I64 _t3819 = 1;
                (void)_t3819;
                I64 _t3820 = I64_sub(_t3818, _t3819);
                (void)_t3820;
                ;
                ;
                I64 _t3821 = 0;
                (void)_t3821;
                I64 _t3822 = 1;
                (void)_t3822;
                I64 _t3823 = I64_sub(_t3821, _t3822);
                (void)_t3823;
                ;
                ;
                U32 _t3824 = 0;
                (void)_t3824;
                I32 _t3825 = I64_to_i32(_t3820);
                (void)_t3825;
                ;
                I32 _t3826 = I64_to_i32(_t3823);
                (void)_t3826;
                ;
                Bool _t3827 = 0;
                (void)_t3827;
                Bool _t3828 = 0;
                (void)_t3828;
                FunctionDef *ffd = malloc(sizeof(FunctionDef));
                { FuncType *_ca = FuncType_clone(FuncType_Func()); ffd->func_type = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3804, &(U64){_t3805}); ffd->param_names = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3806, &(U64){_t3807}); ffd->param_types = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3808, &(U64){_t3809}); ffd->param_muts = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3810, &(U64){_t3811}); ffd->param_owns = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3812, &(U64){_t3813}); ffd->param_shallows = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3814, &(U64){_t3815}); ffd->param_fn_sigs = *_ca; free(_ca); }
                ffd->nparam = _t3824;
                { Vec *_ca = Vec_new(_t3816, &(U64){_t3817}); ffd->param_defaults = *_ca; free(_ca); }
                { Str *_ca = Str_clone(Str_lit("", 0ULL)); ffd->return_type = *_ca; free(_ca); }
                ffd->variadic_index = _t3825;
                ffd->kwargs_index = _t3826;
                ffd->return_is_ref = _t3827;
                ffd->return_is_shallow = _t3828;
                (void)ffd;
                Str_delete(_t3804, &(Bool){1});
                ;
                Str_delete(_t3806, &(Bool){1});
                ;
                Str_delete(_t3808, &(Bool){1});
                ;
                Str_delete(_t3810, &(Bool){1});
                ;
                Str_delete(_t3812, &(Bool){1});
                ;
                Str_delete(_t3814, &(Bool){1});
                ;
                Str_delete(_t3816, &(Bool){1});
                ;
                ;
                ;
                ;
                ;
                ;
                FuncType_delete(&ffd->func_type, &(Bool){0});
                { FuncType *_fa = FuncType_clone(FuncType_Func()); ffd->func_type = *_fa; free(_fa); }
                I64 _t3829 = 0;
                (void)_t3829;
                I64 _t3830 = 1;
                (void)_t3830;
                I64 _t3831 = I64_sub(_t3829, _t3830);
                (void)_t3831;
                ;
                ;
                I32 _t3832 = I64_to_i32(_t3831);
                (void)_t3832;
                ;
                ffd->variadic_index = _t3832;
                ;
                I64 _t3833 = 0;
                (void)_t3833;
                I64 _t3834 = 1;
                (void)_t3834;
                I64 _t3835 = I64_sub(_t3833, _t3834);
                (void)_t3835;
                ;
                ;
                I32 _t3836 = I64_to_i32(_t3835);
                (void)_t3836;
                ;
                ffd->kwargs_index = _t3836;
                ;
                U64 np; { U64 *_hp = (U64 *)Vec_len(pnames); np = *_hp; free(_hp); }
                (void)np;
                {
                    U64 _fi3783 = 0;
                    (void)_fi3783;
                    while (1) {
                        U64 _t3785 = 0;
                        (void)_t3785;
                        Range *_t3786 = Range_new(_t3785, np);
                        (void)_t3786;
                        ;
                        U64 _t3787; { U64 *_hp = (U64 *)Range_len(_t3786); _t3787 = *_hp; free(_hp); }
                        (void)_t3787;
                        Range_delete(_t3786, &(Bool){1});
                        Bool _wcond3784; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3783}, &(U64){_t3787}); _wcond3784 = *_hp; free(_hp); }
                        (void)_wcond3784;
                        ;
                        if (_wcond3784) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 _t3788 = 0;
                        (void)_t3788;
                        Range *_t3789 = Range_new(_t3788, np);
                        (void)_t3789;
                        ;
                        U64 _; { U64 *_hp = (U64 *)Range_get(_t3789, _fi3783); _ = *_hp; free(_hp); }
                        (void)_;
                        ;
                        Range_delete(_t3789, &(Bool){1});
                        U64 _t3790 = 1;
                        (void)_t3790;
                        U64 _t3791 = U64_add(_fi3783, _t3790);
                        (void)_t3791;
                        ;
                        _fi3783 = _t3791;
                        ;
                        Str *_t3792 = Str_lit("", 0ULL);
                        (void)_t3792;
                        Vec_push(&ffd->param_types, _t3792);
                        Bool _t3793 = 0;
                        (void)_t3793;
                        Vec_push(&ffd->param_muts, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3793; _oa; }));
                        Bool _t3794 = 0;
                        (void)_t3794;
                        Vec_push(&ffd->param_owns, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3794; _oa; }));
                        Bool _t3795 = 0;
                        (void)_t3795;
                        Vec_push(&ffd->param_shallows, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3795; _oa; }));
                        I64 _t3796 = 0;
                        (void)_t3796;
                        I64 _t3797 = 1;
                        (void)_t3797;
                        I64 _t3798 = I64_sub(_t3796, _t3797);
                        (void)_t3798;
                        ;
                        ;
                        Vec_push(&ffd->param_defaults, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = _t3798; _oa; }));
                        I64 _t3799 = 0;
                        (void)_t3799;
                        I64 _t3800 = 1;
                        (void)_t3800;
                        I64 _t3801 = I64_sub(_t3799, _t3800);
                        (void)_t3801;
                        ;
                        ;
                        Vec_push(&ffd->param_fn_sigs, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = _t3801; _oa; }));
                    }
                    ;
                }
                ;
                Vec_delete(&ffd->param_names, &(Bool){0});
                { Vec *_fa = Vec_clone(pnames); ffd->param_names = *_fa; free(_fa); }
                Vec_delete(pnames, &(Bool){1});
                ExprData *_t3837 = ExprData_FuncDef(ffd);
                (void)_t3837;
                FunctionDef_delete(ffd, &(Bool){1});
                Expr *fdef = Expr_new(_t3837, t_line, t_col, &p->path);
                (void)fdef;
                ExprData_delete(_t3837, &(Bool){1});
                Expr_add_child(fdef, body);
                Bool _t3838 = Bool_clone(is_mut);
                (void)_t3838;
                Bool _t3839 = 0;
                (void)_t3839;
                Bool _t3840 = 0;
                (void)_t3840;
                Bool _t3841 = Bool_clone(is_own);
                (void)_t3841;
                I32 _t3842 = 0;
                (void)_t3842;
                I32 _t3843 = 0;
                (void)_t3843;
                Declaration *dd = malloc(sizeof(Declaration));
                { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
                { Str *_ca = Str_clone(type_name); dd->explicit_type = *_ca; free(_ca); }
                dd->is_mut = _t3838;
                dd->is_namespace = _t3839;
                dd->is_ref = _t3840;
                dd->is_own = _t3841;
                dd->field_offset = _t3842;
                dd->field_size = _t3843;
                dd->field_struct_def = NULL;
                dd->fn_sig = NULL;
                (void)dd;
                ;
                ;
                ;
                ;
                ;
                ;
                ExprData *_t3844 = ExprData_Decl(dd);
                (void)_t3844;
                Declaration_delete(dd, &(Bool){1});
                Expr *decl = Expr_new(_t3844, t_line, t_col, &p->path);
                (void)decl;
                ExprData_delete(_t3844, &(Bool){1});
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
        Bool _t3858 = Bool_clone(is_mut);
        (void)_t3858;
        Bool _t3859 = 0;
        (void)_t3859;
        Bool _t3860 = 0;
        (void)_t3860;
        Bool _t3861 = Bool_clone(is_own);
        (void)_t3861;
        I32 _t3862 = 0;
        (void)_t3862;
        I32 _t3863 = 0;
        (void)_t3863;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(type_name); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3858;
        dd->is_namespace = _t3859;
        dd->is_ref = _t3860;
        dd->is_own = _t3861;
        dd->field_offset = _t3862;
        dd->field_size = _t3863;
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
        ExprData *_t3864 = ExprData_Decl(dd);
        (void)_t3864;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3864, t_line, t_col, &p->path);
        (void)decl;
        ExprData_delete(_t3864, &(Bool){1});
        Expr *_t3865 = parse_expression(p);
        (void)_t3865;
        Expr_add_child(decl, _t3865);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return decl;
    }
    ;
    Bool _t3915; { Bool *_hp = (Bool *)check(p, TokenType_Dot()); _t3915 = *_hp; free(_hp); }
    (void)_t3915;
    if (_t3915) {
        Str *_t3902 = Str_clone(name);
        (void)_t3902;
        ExprData *_t3903 = ExprData_Ident(_t3902);
        (void)_t3903;
        Str_delete(_t3902, &(Bool){1});
        Expr *obj = Expr_new(_t3903, t_line, t_col, &p->path);
        (void)obj;
        ExprData_delete(_t3903, &(Bool){1});
        Str *last_field = Str_lit("", 0ULL);
        (void)last_field;
        U32 last_line = 0;
        (void)last_line;
        U32 last_col = 0;
        (void)last_col;
        while (1) {
            Bool _wcond3866; { Bool *_hp = (Bool *)check(p, TokenType_Dot()); _wcond3866 = *_hp; free(_hp); }
            (void)_wcond3866;
            if (_wcond3866) {
            } else {
                ;
                break;
            }
            ;
            Token *_t3870 = advance(p);
            (void)_t3870;
            U32 _t3871; { U32 *_hp = (U32 *)peek_line(p); _t3871 = *_hp; free(_hp); }
            (void)_t3871;
            last_line = _t3871;
            ;
            U32 _t3872; { U32 *_hp = (U32 *)peek_col(p); _t3872 = *_hp; free(_hp); }
            (void)_t3872;
            last_col = _t3872;
            ;
            last_field = expect_text(p, TokenType_Ident());
            Bool _t3873; { Bool *_hp = (Bool *)check(p, TokenType_Dot()); _t3873 = *_hp; free(_hp); }
            (void)_t3873;
            if (_t3873) {
                Str *_t3867 = Str_clone(last_field);
                (void)_t3867;
                ExprData *_t3868 = ExprData_FieldAccess(_t3867);
                (void)_t3868;
                Str_delete(_t3867, &(Bool){1});
                Expr *access = Expr_new(_t3868, last_line, last_col, &p->path);
                (void)access;
                ExprData_delete(_t3868, &(Bool){1});
                Expr *_t3869 = Expr_clone(obj);
                (void)_t3869;
                Expr_add_child(access, _t3869);
                obj = Expr_clone(access);
                Expr_delete(access, &(Bool){1});
            }
            ;
        }
        Bool _t3904; { Bool *_hp = (Bool *)check(p, TokenType_LParen()); _t3904 = *_hp; free(_hp); }
        (void)_t3904;
        if (_t3904) {
            Token *_t3899 = advance(p);
            (void)_t3899;
            ExprData *_t3900 = ExprData_FieldAccess(last_field);
            (void)_t3900;
            Expr *callee = Expr_new(_t3900, last_line, last_col, &p->path);
            (void)callee;
            ExprData_delete(_t3900, &(Bool){1});
            Expr *_t3901 = Expr_clone(obj);
            (void)_t3901;
            Expr_add_child(callee, _t3901);
            Expr *mcall = Expr_new(ExprData_FCall(), last_line, last_col, &p->path);
            (void)mcall;
            Expr_add_child(mcall, callee);
            while (1) {
                Bool _t3891; { Bool *_hp = (Bool *)check(p, TokenType_RParen()); _t3891 = *_hp; free(_hp); }
                (void)_t3891;
                Bool _t3892; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3892 = *_hp; free(_hp); }
                (void)_t3892;
                Bool _t3893 = Bool_not(_t3891);
                (void)_t3893;
                ;
                Bool _t3894 = Bool_not(_t3892);
                (void)_t3894;
                ;
                Bool _wcond3874 = Bool_and(_t3893, _t3894);
                (void)_wcond3874;
                ;
                ;
                if (_wcond3874) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3895; { Bool *_hp = (Bool *)check(p, TokenType_Ident()); _t3895 = *_hp; free(_hp); }
                (void)_t3895;
                if (_t3895) {
                    U32 _t3885 = 1;
                    (void)_t3885;
                    U32 _t3886 = U32_add(p->pos, _t3885);
                    (void)_t3886;
                    ;
                    Bool _t3887; { Bool *_hp = (Bool *)U32_lt(&(U32){_t3886}, &p->count); _t3887 = *_hp; free(_hp); }
                    (void)_t3887;
                    ;
                    if (_t3887) {
                        U32 _t3880 = 1;
                        (void)_t3880;
                        U32 _t3881 = U32_add(p->pos, _t3880);
                        (void)_t3881;
                        ;
                        I64 _t3882 = U32_to_i64(_t3881);
                        (void)_t3882;
                        ;
                        U64 *_t3883 = malloc(sizeof(U64)); *_t3883 = I64_to_u64(_t3882);
                        (void)_t3883;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3883);
                        (void)nt;
                        Bool _t3884; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3884 = *_hp; free(_hp); }
                        (void)_t3884;
                        U64_delete(_t3883, &(Bool){1});
                        if (_t3884) {
                            U32 na_line; { U32 *_hp = (U32 *)peek_line(p); na_line = *_hp; free(_hp); }
                            (void)na_line;
                            U32 na_col; { U32 *_hp = (U32 *)peek_col(p); na_col = *_hp; free(_hp); }
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3876 = advance(p);
                            (void)_t3876;
                            ExprData *_t3877 = ExprData_NamedArg(aname);
                            (void)_t3877;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3877, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3877, &(Bool){1});
                            ;
                            ;
                            Expr *_t3878 = parse_expression(p);
                            (void)_t3878;
                            Expr_add_child(na, _t3878);
                            Expr_add_child(mcall, na);
                            Bool _t3879; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3879 = *_hp; free(_hp); }
                            (void)_t3879;
                            if (_t3879) {
                                Token *_t3875 = advance(p);
                                (void)_t3875;
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
                Bool _t3896; { Bool *_hp = (Bool *)check(p, TokenType_KwOwn()); _t3896 = *_hp; free(_hp); }
                (void)_t3896;
                if (_t3896) {
                    Token *_t3888 = advance(p);
                    (void)_t3888;
                    Bool _t3889 = 1;
                    (void)_t3889;
                    is_own_arg = _t3889;
                    ;
                }
                ;
                Expr *marg = parse_expression(p);
                (void)marg;
                Bool _t3897 = Bool_clone(&(Bool){is_own_arg});
                (void)_t3897;
                ;
                marg->is_own_arg = _t3897;
                ;
                Expr_add_child(mcall, marg);
                Bool _t3898; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3898 = *_hp; free(_hp); }
                (void)_t3898;
                if (_t3898) {
                    Token *_t3890 = advance(p);
                    (void)_t3890;
                }
                ;
            }
            expect_token(p, TokenType_RParen());
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
        expect_token(p, TokenType_Eq());
        ExprData *_t3905 = ExprData_FieldAssign(last_field);
        (void)_t3905;
        Str_delete(last_field, &(Bool){1});
        Expr *fa = Expr_new(_t3905, t_line, t_col, &p->path);
        (void)fa;
        ExprData_delete(_t3905, &(Bool){1});
        Expr *_t3906 = Expr_clone(obj);
        (void)_t3906;
        Expr_delete(obj, &(Bool){1});
        Expr_add_child(fa, _t3906);
        Expr *_t3907 = parse_expression(p);
        (void)_t3907;
        Expr_add_child(fa, _t3907);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return fa;
    }
    ;
    Bool _t3916; { Bool *_hp = (Bool *)check(p, TokenType_Eq()); _t3916 = *_hp; free(_hp); }
    (void)_t3916;
    if (_t3916) {
        Token *_t3908 = advance(p);
        (void)_t3908;
        Str *_t3909 = Str_clone(name);
        (void)_t3909;
        ExprData *_t3910 = ExprData_Assign(_t3909);
        (void)_t3910;
        Str_delete(_t3909, &(Bool){1});
        Expr *assign = Expr_new(_t3910, t_line, t_col, &p->path);
        (void)assign;
        ExprData_delete(_t3910, &(Bool){1});
        Expr *_t3911 = parse_expression(p);
        (void)_t3911;
        Expr_add_child(assign, _t3911);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return assign;
    }
    ;
    Bool _t3917; { Bool *_hp = (Bool *)check(p, TokenType_LParen()); _t3917 = *_hp; free(_hp); }
    (void)_t3917;
    if (_t3917) {
        Expr *_t3912 = parse_call(p, name, &(U32){t_line}, &(U32){t_col});
        (void)_t3912;
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return _t3912;
    }
    ;
    Str *_t3918 = Str_lit("Str", 3ULL);
    (void)_t3918;
    U64 _t3919; { U64 *_hp = (U64 *)Str_size(); _t3919 = *_hp; free(_hp); }
    (void)_t3919;
    U64 _t3920 = 8;
    (void)_t3920;
    Array *_va69 = Array_new(_t3918, &(U64){_t3919}, &(U64){_t3920});
    (void)_va69;
    Str_delete(_t3918, &(Bool){1});
    ;
    ;
    U64 _t3921 = 0;
    (void)_t3921;
    Str *_t3922 = Str_clone(&p->path);
    (void)_t3922;
    Array_set(_va69, &(U64){_t3921}, _t3922);
    ;
    U64 _t3923 = 1;
    (void)_t3923;
    Str *_t3924 = Str_lit(":", 1ULL);
    (void)_t3924;
    Array_set(_va69, &(U64){_t3923}, _t3924);
    ;
    U64 _t3925 = 2;
    (void)_t3925;
    Str *_t3926 = U32_to_str(&(U32){t_line});
    (void)_t3926;
    ;
    Array_set(_va69, &(U64){_t3925}, _t3926);
    ;
    U64 _t3927 = 3;
    (void)_t3927;
    Str *_t3928 = Str_lit(":", 1ULL);
    (void)_t3928;
    Array_set(_va69, &(U64){_t3927}, _t3928);
    ;
    U64 _t3929 = 4;
    (void)_t3929;
    Str *_t3930 = U32_to_str(&(U32){t_col});
    (void)_t3930;
    ;
    Array_set(_va69, &(U64){_t3929}, _t3930);
    ;
    U64 _t3931 = 5;
    (void)_t3931;
    Str *_t3932 = Str_lit(": expected ':=', ':', '=' or '(' after identifier '", 51ULL);
    (void)_t3932;
    Array_set(_va69, &(U64){_t3931}, _t3932);
    ;
    U64 _t3933 = 6;
    (void)_t3933;
    Str *_t3934 = Str_clone(name);
    (void)_t3934;
    Str_delete(name, &(Bool){1});
    Array_set(_va69, &(U64){_t3933}, _t3934);
    ;
    U64 _t3935 = 7;
    (void)_t3935;
    Str *_t3936 = Str_lit("'", 1ULL);
    (void)_t3936;
    Array_set(_va69, &(U64){_t3935}, _t3936);
    ;
    Str *_t3937 = Str_lit("src/self/parser.til:782:11", 26ULL);
    (void)_t3937;
    panic(_t3937, _va69);
    Str_delete(_t3937, &(Bool){1});
    U32 _t3938 = 0;
    (void)_t3938;
    U32 _t3939 = 0;
    (void)_t3939;
    Expr *_t3940 = Expr_new(ExprData_Body(), _t3938, _t3939, &p->path);
    (void)_t3940;
    ;
    ;
    return _t3940;
}

Expr * parse_statement(Parser * p) {
    (void)p;
    U32 t_line; { U32 *_hp = (U32 *)peek_line(p); t_line = *_hp; free(_hp); }
    (void)t_line;
    U32 t_col; { U32 *_hp = (U32 *)peek_col(p); t_col = *_hp; free(_hp); }
    (void)t_col;
    Token *t = peek(p);
    (void)t;
    Bool _t4066; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t4066 = *_hp; free(_hp); }
    (void)_t4066;
    if (_t4066) {
        Bool _t3941 = 0;
        (void)_t3941;
        Bool _t3942 = 0;
        (void)_t3942;
        Expr *_t3943 = parse_statement_ident(p, &(Bool){_t3941}, &(Bool){_t3942});
        (void)_t3943;
        ;
        ;
        ;
        ;
        ;
        return _t3943;
    }
    ;
    Bool _t4067; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwRef()); _t4067 = *_hp; free(_hp); }
    (void)_t4067;
    if (_t4067) {
        Token *_t3948 = advance(p);
        (void)_t3948;
        Bool ref_mut = 0;
        (void)ref_mut;
        Bool _t3949; { Bool *_hp = (Bool *)check(p, TokenType_KwMut()); _t3949 = *_hp; free(_hp); }
        (void)_t3949;
        if (_t3949) {
            Token *_t3944 = advance(p);
            (void)_t3944;
            Bool _t3945 = 1;
            (void)_t3945;
            ref_mut = _t3945;
            ;
        }
        ;
        U32 i_line; { U32 *_hp = (U32 *)peek_line(p); i_line = *_hp; free(_hp); }
        (void)i_line;
        U32 i_col; { U32 *_hp = (U32 *)peek_col(p); i_col = *_hp; free(_hp); }
        (void)i_col;
        Str *iname = expect_text(p, TokenType_Ident());
        (void)iname;
        Bool _t3950 = 0;
        (void)_t3950;
        Bool _t3951 = 0;
        (void)_t3951;
        Bool _t3952 = 1;
        (void)_t3952;
        Bool _t3953 = 0;
        (void)_t3953;
        I32 _t3954 = 0;
        (void)_t3954;
        I32 _t3955 = 0;
        (void)_t3955;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(iname); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3950;
        dd->is_namespace = _t3951;
        dd->is_ref = _t3952;
        dd->is_own = _t3953;
        dd->field_offset = _t3954;
        dd->field_size = _t3955;
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
            Bool _t3946 = 1;
            (void)_t3946;
            dd->is_mut = _t3946;
            ;
        }
        ;
        Bool _t3956; { Bool *_hp = (Bool *)check(p, TokenType_Colon()); _t3956 = *_hp; free(_hp); }
        (void)_t3956;
        if (_t3956) {
            Token *_t3947 = advance(p);
            (void)_t3947;
            Str_delete(&dd->explicit_type, &(Bool){0});
            { Str *_fa = expect_text(p, TokenType_Ident()); dd->explicit_type = *_fa; free(_fa); }
            expect_token(p, TokenType_Eq());
        } else {
            expect_token(p, TokenType_ColonEq());
        }
        ;
        ExprData *_t3957 = ExprData_Decl(dd);
        (void)_t3957;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3957, i_line, i_col, &p->path);
        (void)decl;
        ExprData_delete(_t3957, &(Bool){1});
        ;
        ;
        Expr *_t3958 = parse_expression(p);
        (void)_t3958;
        Expr_add_child(decl, _t3958);
        ;
        ;
        ;
        return decl;
    }
    ;
    Bool _t4068; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMut()); _t4068 = *_hp; free(_hp); }
    (void)_t4068;
    if (_t4068) {
        Token *_t3959 = advance(p);
        (void)_t3959;
        Bool _t3960 = 1;
        (void)_t3960;
        Bool _t3961 = 0;
        (void)_t3961;
        Expr *_t3962 = parse_statement_ident(p, &(Bool){_t3960}, &(Bool){_t3961});
        (void)_t3962;
        ;
        ;
        ;
        ;
        ;
        return _t3962;
    }
    ;
    Bool _t4069; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwReturn()); _t4069 = *_hp; free(_hp); }
    (void)_t4069;
    if (_t4069) {
        Token *_t3964 = advance(p);
        (void)_t3964;
        Expr *ret = Expr_new(ExprData_Return(), t_line, t_col, &p->path);
        (void)ret;
        Bool _t3965; { Bool *_hp = (Bool *)check(p, TokenType_RBrace()); _t3965 = *_hp; free(_hp); }
        (void)_t3965;
        Bool _t3966; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3966 = *_hp; free(_hp); }
        (void)_t3966;
        Bool _t3967 = Bool_not(_t3965);
        (void)_t3967;
        ;
        Bool _t3968 = Bool_not(_t3966);
        (void)_t3968;
        ;
        Bool _t3969 = Bool_and(_t3967, _t3968);
        (void)_t3969;
        ;
        ;
        if (_t3969) {
            Expr *_t3963 = parse_expression(p);
            (void)_t3963;
            Expr_add_child(ret, _t3963);
        }
        ;
        ;
        ;
        ;
        return ret;
    }
    ;
    Bool _t4070; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwIf()); _t4070 = *_hp; free(_hp); }
    (void)_t4070;
    if (_t4070) {
        Token *_t3976 = advance(p);
        (void)_t3976;
        Expr *node = Expr_new(ExprData_If(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t3977 = parse_expression(p);
        (void)_t3977;
        Expr_add_child(node, _t3977);
        expect_token(p, TokenType_LBrace());
        Expr *_t3978 = parse_block(p);
        (void)_t3978;
        Expr_add_child(node, _t3978);
        Bool _t3979; { Bool *_hp = (Bool *)check(p, TokenType_KwElse()); _t3979 = *_hp; free(_hp); }
        (void)_t3979;
        if (_t3979) {
            Token *_t3974 = advance(p);
            (void)_t3974;
            Bool _t3975; { Bool *_hp = (Bool *)check(p, TokenType_KwIf()); _t3975 = *_hp; free(_hp); }
            (void)_t3975;
            if (_t3975) {
                U32 _t3970; { U32 *_hp = (U32 *)peek_line(p); _t3970 = *_hp; free(_hp); }
                (void)_t3970;
                U32 _t3971; { U32 *_hp = (U32 *)peek_col(p); _t3971 = *_hp; free(_hp); }
                (void)_t3971;
                Expr *else_body = Expr_new(ExprData_Body(), _t3970, _t3971, &p->path);
                (void)else_body;
                ;
                ;
                Expr *_t3972 = parse_statement(p);
                (void)_t3972;
                Expr_add_child(else_body, _t3972);
                Expr_add_child(node, else_body);
            } else {
                expect_token(p, TokenType_LBrace());
                Expr *_t3973 = parse_block(p);
                (void)_t3973;
                Expr_add_child(node, _t3973);
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
    Bool _t4071; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t4071 = *_hp; free(_hp); }
    (void)_t4071;
    Bool _t4072; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t4072 = *_hp; free(_hp); }
    (void)_t4072;
    Bool _t4073 = Bool_or(_t4071, _t4072);
    (void)_t4073;
    ;
    ;
    Bool _t4074; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t4074 = *_hp; free(_hp); }
    (void)_t4074;
    Bool _t4075 = Bool_or(_t4073, _t4074);
    (void)_t4075;
    ;
    ;
    Bool _t4076; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t4076 = *_hp; free(_hp); }
    (void)_t4076;
    Bool _t4077 = Bool_or(_t4075, _t4076);
    (void)_t4077;
    ;
    ;
    if (_t4077) {
        Expr *_t3980 = parse_expression(p);
        (void)_t3980;
        ;
        ;
        ;
        return _t3980;
    }
    ;
    Bool _t4078; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t4078 = *_hp; free(_hp); }
    (void)_t4078;
    if (_t4078) {
        Token *_t3981 = advance(p);
        (void)_t3981;
        Expr *_t3982 = parse_block(p);
        (void)_t3982;
        ;
        ;
        ;
        return _t3982;
    }
    ;
    Bool _t4079; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwWhile()); _t4079 = *_hp; free(_hp); }
    (void)_t4079;
    if (_t4079) {
        Token *_t3983 = advance(p);
        (void)_t3983;
        Expr *node = Expr_new(ExprData_While(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t3984 = parse_expression(p);
        (void)_t3984;
        Expr_add_child(node, _t3984);
        expect_token(p, TokenType_LBrace());
        Expr *_t3985 = parse_block(p);
        (void)_t3985;
        Expr_add_child(node, _t3985);
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4080; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFor()); _t4080 = *_hp; free(_hp); }
    (void)_t4080;
    if (_t4080) {
        Token *_t3987 = advance(p);
        (void)_t3987;
        U32 i_line; { U32 *_hp = (U32 *)peek_line(p); i_line = *_hp; free(_hp); }
        (void)i_line;
        U32 i_col; { U32 *_hp = (U32 *)peek_col(p); i_col = *_hp; free(_hp); }
        (void)i_col;
        Str *iname = expect_text(p, TokenType_Ident());
        (void)iname;
        ExprData *_t3988 = ExprData_ForIn(iname);
        (void)_t3988;
        Str_delete(iname, &(Bool){1});
        Expr *node = Expr_new(_t3988, i_line, i_col, &p->path);
        (void)node;
        ExprData_delete(_t3988, &(Bool){1});
        ;
        ;
        Bool _t3989; { Bool *_hp = (Bool *)check(p, TokenType_Colon()); _t3989 = *_hp; free(_hp); }
        (void)_t3989;
        if (_t3989) {
            Token *_t3986 = advance(p);
            (void)_t3986;
            Str_delete(&node->struct_name, &(Bool){0});
            { Str *_fa = expect_text(p, TokenType_Ident()); node->struct_name = *_fa; free(_fa); }
        }
        ;
        expect_token(p, TokenType_KwIn());
        Expr *_t3990 = parse_expression(p);
        (void)_t3990;
        Expr_add_child(node, _t3990);
        expect_token(p, TokenType_LBrace());
        Expr *_t3991 = parse_block(p);
        (void)_t3991;
        Expr_add_child(node, _t3991);
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4081; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwSwitch()); _t4081 = *_hp; free(_hp); }
    (void)_t4081;
    if (_t4081) {
        Token *_t4013 = advance(p);
        (void)_t4013;
        Expr *node = Expr_new(ExprData_Switch(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t4014 = parse_expression(p);
        (void)_t4014;
        Expr_add_child(node, _t4014);
        expect_token(p, TokenType_LBrace());
        while (1) {
            Bool _t4003; { Bool *_hp = (Bool *)check(p, TokenType_RBrace()); _t4003 = *_hp; free(_hp); }
            (void)_t4003;
            Bool _t4004; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t4004 = *_hp; free(_hp); }
            (void)_t4004;
            Bool _t4005 = Bool_not(_t4003);
            (void)_t4005;
            ;
            Bool _t4006 = Bool_not(_t4004);
            (void)_t4006;
            ;
            Bool _wcond3992 = Bool_and(_t4005, _t4006);
            (void)_wcond3992;
            ;
            ;
            if (_wcond3992) {
            } else {
                ;
                break;
            }
            ;
            expect_token(p, TokenType_KwCase());
            U32 _t4007; { U32 *_hp = (U32 *)peek_line(p); _t4007 = *_hp; free(_hp); }
            (void)_t4007;
            U32 _t4008; { U32 *_hp = (U32 *)peek_col(p); _t4008 = *_hp; free(_hp); }
            (void)_t4008;
            Expr *cn = Expr_new(ExprData_Case(), _t4007, _t4008, &p->path);
            (void)cn;
            ;
            ;
            Bool _t4009; { Bool *_hp = (Bool *)check(p, TokenType_Colon()); _t4009 = *_hp; free(_hp); }
            (void)_t4009;
            Bool _t4010 = Bool_not(_t4009);
            (void)_t4010;
            ;
            if (_t4010) {
                Expr *_t3993 = parse_expression(p);
                (void)_t3993;
                Expr_add_child(cn, _t3993);
            }
            ;
            expect_token(p, TokenType_Colon());
            U32 _t4011; { U32 *_hp = (U32 *)peek_line(p); _t4011 = *_hp; free(_hp); }
            (void)_t4011;
            U32 _t4012; { U32 *_hp = (U32 *)peek_col(p); _t4012 = *_hp; free(_hp); }
            (void)_t4012;
            Expr *cb = Expr_new(ExprData_Body(), _t4011, _t4012, &p->path);
            (void)cb;
            ;
            ;
            while (1) {
                Bool _t3995; { Bool *_hp = (Bool *)check(p, TokenType_KwCase()); _t3995 = *_hp; free(_hp); }
                (void)_t3995;
                Bool _t3996; { Bool *_hp = (Bool *)check(p, TokenType_RBrace()); _t3996 = *_hp; free(_hp); }
                (void)_t3996;
                Bool _t3997 = Bool_not(_t3995);
                (void)_t3997;
                ;
                Bool _t3998 = Bool_not(_t3996);
                (void)_t3998;
                ;
                Bool _t3999; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3999 = *_hp; free(_hp); }
                (void)_t3999;
                Bool _t4000 = Bool_and(_t3997, _t3998);
                (void)_t4000;
                ;
                ;
                Bool _t4001 = Bool_not(_t3999);
                (void)_t4001;
                ;
                Bool _wcond3994 = Bool_and(_t4000, _t4001);
                (void)_wcond3994;
                ;
                ;
                if (_wcond3994) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t4002 = parse_statement(p);
                (void)_t4002;
                Expr_add_child(cb, _t4002);
            }
            Expr_add_child(cn, cb);
            Expr_add_child(node, cn);
        }
        expect_token(p, TokenType_RBrace());
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4082; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwOwn()); _t4082 = *_hp; free(_hp); }
    (void)_t4082;
    if (_t4082) {
        Token *_t4055 = advance(p);
        (void)_t4055;
        Bool _t4056; { Bool *_hp = (Bool *)check(p, TokenType_Ident()); _t4056 = *_hp; free(_hp); }
        (void)_t4056;
        Bool _t4057; { Bool *_hp = (Bool *)check(p, TokenType_KwMut()); _t4057 = *_hp; free(_hp); }
        (void)_t4057;
        Bool _t4058 = Bool_or(_t4056, _t4057);
        (void)_t4058;
        ;
        ;
        if (_t4058) {
            Bool own_mut = 0;
            (void)own_mut;
            Bool _t4045; { Bool *_hp = (Bool *)check(p, TokenType_KwMut()); _t4045 = *_hp; free(_hp); }
            (void)_t4045;
            if (_t4045) {
                Token *_t4015 = advance(p);
                (void)_t4015;
                Bool _t4016 = 1;
                (void)_t4016;
                own_mut = _t4016;
                ;
            }
            ;
            Bool _t4046; { Bool *_hp = (Bool *)check(p, TokenType_Ident()); _t4046 = *_hp; free(_hp); }
            (void)_t4046;
            if (_t4046) {
                U32 _t4026 = 1;
                (void)_t4026;
                U32 _t4027 = U32_add(p->pos, _t4026);
                (void)_t4027;
                ;
                Bool _t4028; { Bool *_hp = (Bool *)U32_lt(&(U32){_t4027}, &p->count); _t4028 = *_hp; free(_hp); }
                (void)_t4028;
                ;
                if (_t4028) {
                    U32 _t4019 = 1;
                    (void)_t4019;
                    U32 _t4020 = U32_add(p->pos, _t4019);
                    (void)_t4020;
                    ;
                    I64 _t4021 = U32_to_i64(_t4020);
                    (void)_t4021;
                    ;
                    U64 *_t4022 = malloc(sizeof(U64)); *_t4022 = I64_to_u64(_t4021);
                    (void)_t4022;
                    ;
                    Token *nt = Vec_get(&p->tokens, _t4022);
                    (void)nt;
                    Bool _t4023; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_ColonEq()); _t4023 = *_hp; free(_hp); }
                    (void)_t4023;
                    Bool _t4024; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Colon()); _t4024 = *_hp; free(_hp); }
                    (void)_t4024;
                    U64_delete(_t4022, &(Bool){1});
                    Bool _t4025 = Bool_or(_t4023, _t4024);
                    (void)_t4025;
                    ;
                    ;
                    if (_t4025) {
                        Bool _t4017 = 1;
                        (void)_t4017;
                        Expr *_t4018 = parse_statement_ident(p, &(Bool){own_mut}, &(Bool){_t4017});
                        (void)_t4018;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        return _t4018;
                    }
                    ;
                }
                ;
            }
            ;
            if (own_mut) {
                Str *_t4029 = Str_lit("Str", 3ULL);
                (void)_t4029;
                U64 _t4030; { U64 *_hp = (U64 *)Str_size(); _t4030 = *_hp; free(_hp); }
                (void)_t4030;
                U64 _t4031 = 6;
                (void)_t4031;
                Array *_va70 = Array_new(_t4029, &(U64){_t4030}, &(U64){_t4031});
                (void)_va70;
                Str_delete(_t4029, &(Bool){1});
                ;
                ;
                U64 _t4032 = 0;
                (void)_t4032;
                Str *_t4033 = Str_clone(&p->path);
                (void)_t4033;
                Array_set(_va70, &(U64){_t4032}, _t4033);
                ;
                U64 _t4034 = 1;
                (void)_t4034;
                Str *_t4035 = Str_lit(":", 1ULL);
                (void)_t4035;
                Array_set(_va70, &(U64){_t4034}, _t4035);
                ;
                U64 _t4036 = 2;
                (void)_t4036;
                Str *_t4037 = U32_to_str(&(U32){t_line});
                (void)_t4037;
                Array_set(_va70, &(U64){_t4036}, _t4037);
                ;
                U64 _t4038 = 3;
                (void)_t4038;
                Str *_t4039 = Str_lit(":", 1ULL);
                (void)_t4039;
                Array_set(_va70, &(U64){_t4038}, _t4039);
                ;
                U64 _t4040 = 4;
                (void)_t4040;
                Str *_t4041 = U32_to_str(&(U32){t_col});
                (void)_t4041;
                Array_set(_va70, &(U64){_t4040}, _t4041);
                ;
                U64 _t4042 = 5;
                (void)_t4042;
                Str *_t4043 = Str_lit(": expected identifier after 'own mut'", 37ULL);
                (void)_t4043;
                Array_set(_va70, &(U64){_t4042}, _t4043);
                ;
                Str *_t4044 = Str_lit("src/self/parser.til:915:23", 26ULL);
                (void)_t4044;
                panic(_t4044, _va70);
                Str_delete(_t4044, &(Bool){1});
            }
            ;
        }
        ;
        Expr *expr = parse_expression(p);
        (void)expr;
        I64 _t4059 = 0;
        (void)_t4059;
        I64 _t4060 = 1;
        (void)_t4060;
        I64 primary_idx = I64_sub(_t4059, _t4060);
        (void)primary_idx;
        ;
        ;
        ;
        Expr *cur = Expr_clone(expr);
        (void)cur;
        while (1) {
            U64 _t4048; { U64 *_hp = (U64 *)Vec_len(&cur->children); _t4048 = *_hp; free(_hp); }
            (void)_t4048;
            U64 _t4049 = 0;
            (void)_t4049;
            Bool _t4050; { Bool *_hp = (Bool *)ExprData_is_FCall(&cur->data); _t4050 = *_hp; free(_hp); }
            (void)_t4050;
            Bool _t4051; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(&cur->data); _t4051 = *_hp; free(_hp); }
            (void)_t4051;
            Bool _t4052; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4048}, &(U64){_t4049}); _t4052 = *_hp; free(_hp); }
            (void)_t4052;
            ;
            ;
            Bool _t4053 = Bool_or(_t4050, _t4051);
            (void)_t4053;
            ;
            ;
            Bool _wcond4047 = Bool_and(_t4052, _t4053);
            (void)_wcond4047;
            ;
            ;
            if (_wcond4047) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t4054 = malloc(sizeof(U64));
            *_t4054 = 0;
            (void)_t4054;
            Expr *ch = Vec_get(&cur->children, _t4054);
            (void)ch;
            cur = Expr_clone(ch);
            U64_delete(_t4054, &(Bool){1});
        }
        Bool _t4061 = 1;
        (void)_t4061;
        cur->is_own_arg = _t4061;
        ;
        Expr_delete(cur, &(Bool){1});
        ;
        ;
        ;
        ;
        return expr;
    }
    ;
    Bool _t4083; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwBreak()); _t4083 = *_hp; free(_hp); }
    (void)_t4083;
    if (_t4083) {
        Token *_t4062 = advance(p);
        (void)_t4062;
        Expr *_t4063 = Expr_new(ExprData_Break(), t_line, t_col, &p->path);
        (void)_t4063;
        ;
        ;
        ;
        return _t4063;
    }
    ;
    Bool _t4084; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwContinue()); _t4084 = *_hp; free(_hp); }
    (void)_t4084;
    if (_t4084) {
        Token *_t4064 = advance(p);
        (void)_t4064;
        Expr *_t4065 = Expr_new(ExprData_Continue(), t_line, t_col, &p->path);
        (void)_t4065;
        ;
        ;
        ;
        return _t4065;
    }
    ;
    Str *_t4085 = Str_lit("Str", 3ULL);
    (void)_t4085;
    U64 _t4086; { U64 *_hp = (U64 *)Str_size(); _t4086 = *_hp; free(_hp); }
    (void)_t4086;
    U64 _t4087 = 8;
    (void)_t4087;
    Array *_va71 = Array_new(_t4085, &(U64){_t4086}, &(U64){_t4087});
    (void)_va71;
    Str_delete(_t4085, &(Bool){1});
    ;
    ;
    U64 _t4088 = 0;
    (void)_t4088;
    Str *_t4089 = Str_clone(&p->path);
    (void)_t4089;
    Array_set(_va71, &(U64){_t4088}, _t4089);
    ;
    U64 _t4090 = 1;
    (void)_t4090;
    Str *_t4091 = Str_lit(":", 1ULL);
    (void)_t4091;
    Array_set(_va71, &(U64){_t4090}, _t4091);
    ;
    U64 _t4092 = 2;
    (void)_t4092;
    Str *_t4093 = U32_to_str(&(U32){t_line});
    (void)_t4093;
    ;
    Array_set(_va71, &(U64){_t4092}, _t4093);
    ;
    U64 _t4094 = 3;
    (void)_t4094;
    Str *_t4095 = Str_lit(":", 1ULL);
    (void)_t4095;
    Array_set(_va71, &(U64){_t4094}, _t4095);
    ;
    U64 _t4096 = 4;
    (void)_t4096;
    Str *_t4097 = U32_to_str(&(U32){t_col});
    (void)_t4097;
    ;
    Array_set(_va71, &(U64){_t4096}, _t4097);
    ;
    U64 _t4098 = 5;
    (void)_t4098;
    Str *_t4099 = Str_lit(": expected statement, found '", 29ULL);
    (void)_t4099;
    Array_set(_va71, &(U64){_t4098}, _t4099);
    ;
    U64 _t4100 = 6;
    (void)_t4100;
    Str *_t4101 = Str_clone(&t->text);
    (void)_t4101;
    Array_set(_va71, &(U64){_t4100}, _t4101);
    ;
    U64 _t4102 = 7;
    (void)_t4102;
    Str *_t4103 = Str_lit("'", 1ULL);
    (void)_t4103;
    Array_set(_va71, &(U64){_t4102}, _t4103);
    ;
    Str *_t4104 = Str_lit("src/self/parser.til:942:11", 26ULL);
    (void)_t4104;
    panic(_t4104, _va71);
    Str_delete(_t4104, &(Bool){1});
    U32 _t4105 = 0;
    (void)_t4105;
    U32 _t4106 = 0;
    (void)_t4106;
    Expr *_t4107 = Expr_new(ExprData_Body(), _t4105, _t4106, &p->path);
    (void)_t4107;
    ;
    ;
    return _t4107;
}

Expr * parse(Vec * tokens, Str * path, Str * mode_out) {
    (void)tokens;
    (void)path;
    (void)mode_out;
    U64 _t4118; { U64 *_hp = (U64 *)Vec_len(tokens); _t4118 = *_hp; free(_hp); }
    (void)_t4118;
    I64 _t4119 = 0;
    (void)_t4119;
    Parser *p = malloc(sizeof(Parser));
    { Vec *_ca = Vec_clone(tokens); p->tokens = *_ca; free(_ca); }
    p->count = _t4118;
    p->pos = _t4119;
    { Str *_ca = Str_clone(path); p->path = *_ca; free(_ca); }
    (void)p;
    ;
    ;
    Bool _t4120; { Bool *_hp = (Bool *)check(p, TokenType_KwMode()); _t4120 = *_hp; free(_hp); }
    (void)_t4120;
    if (_t4120) {
        Token *_t4111 = advance(p);
        (void)_t4111;
        Bool _t4112; { Bool *_hp = (Bool *)check(p, TokenType_Ident()); _t4112 = *_hp; free(_hp); }
        (void)_t4112;
        Bool _t4113; { Bool *_hp = (Bool *)check(p, TokenType_KwTest()); _t4113 = *_hp; free(_hp); }
        (void)_t4113;
        Bool _t4114 = Bool_or(_t4112, _t4113);
        (void)_t4114;
        ;
        ;
        if (_t4114) {
            Str *_t4108 = Str_clone(&peek(p)->text);
            (void)_t4108;
            U64 _t4109; { U64 *_hp = (U64 *)Str_size(); _t4109 = *_hp; free(_hp); }
            (void)_t4109;
            swap(mode_out, _t4108, _t4109);
            Str_delete(_t4108, &(Bool){1});
            ;
            Token *_t4110 = advance(p);
            (void)_t4110;
        } else {
            expect_token(p, TokenType_Ident());
        }
        ;
    }
    ;
    U32 _t4121 = 1;
    (void)_t4121;
    U32 _t4122 = 1;
    (void)_t4122;
    Expr *root = Expr_new(ExprData_Body(), _t4121, _t4122, &p->path);
    (void)root;
    ;
    ;
    while (1) {
        Bool _t4116; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t4116 = *_hp; free(_hp); }
        (void)_t4116;
        Bool _wcond4115 = Bool_not(_t4116);
        (void)_wcond4115;
        ;
        if (_wcond4115) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t4117 = parse_statement(p);
        (void)_t4117;
        Expr_add_child(root, _t4117);
    }
    Parser_delete(p, &(Bool){1});
    return root;
}

