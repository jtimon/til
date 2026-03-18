#include "parser_parser.h"

Parser * Parser_clone(Parser * self) {
    (void)self;
    U64 _t3042 = U64_clone(&self->pos);
    (void)_t3042;
    Parser *_t3043 = malloc(sizeof(Parser));
    { Vec *_ca = Vec_clone(&self->tokens); _t3043->tokens = *_ca; free(_ca); }
    _t3043->pos = _t3042;
    { Str *_ca = Str_clone(&self->path); _t3043->path = *_ca; free(_ca); }
    (void)_t3043;
    ;
    return _t3043;
}

void Parser_delete(Parser * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t3044 = 0;
    (void)_t3044;
    Vec_delete(&self->tokens, &(Bool){_t3044});
    ;
    Bool _t3045 = 0;
    (void)_t3045;
    U64_delete(&self->pos, &(Bool){_t3045});
    ;
    Bool _t3046 = 0;
    (void)_t3046;
    Str_delete(&self->path, &(Bool){_t3046});
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
    I64 _t3048 = U64_to_i64(p->pos);
    (void)_t3048;
    U64 *_t3049 = malloc(sizeof(U64)); *_t3049 = I64_to_u64(_t3048);
    (void)_t3049;
    ;
    Token *t = Vec_get(&p->tokens, _t3049);
    (void)t;
    U64_delete(_t3049, &(Bool){1});
    return t;
}

Token * advance(Parser * p) {
    (void)p;
    I64 _t3052 = U64_to_i64(p->pos);
    (void)_t3052;
    U64 *_t3053 = malloc(sizeof(U64)); *_t3053 = I64_to_u64(_t3052);
    (void)_t3053;
    ;
    Token *t = Vec_get(&p->tokens, _t3053);
    (void)t;
    Bool _t3054; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Eof()); _t3054 = *_hp; free(_hp); }
    (void)_t3054;
    Bool _t3055 = Bool_not(_t3054);
    (void)_t3055;
    ;
    if (_t3055) {
        U64 _t3050 = 1;
        (void)_t3050;
        U64 _t3051 = U64_add(p->pos, _t3050);
        (void)_t3051;
        ;
        p->pos = _t3051;
        ;
    }
    ;
    U64_delete(_t3053, &(Bool){1});
    return t;
}

Bool check(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Bool _t3056; { Bool *_hp = (Bool *)TokenType_eq(&peek(p)->type, type); _t3056 = *_hp; free(_hp); }
    (void)_t3056;
    return _t3056;
}

Token * expect_token(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Token *t = peek(p);
    (void)t;
    Bool _t3081; { Bool *_hp = (Bool *)TokenType_eq(&t->type, type); _t3081 = *_hp; free(_hp); }
    (void)_t3081;
    Bool _t3082 = Bool_not(_t3081);
    (void)_t3082;
    ;
    if (_t3082) {
        Str *_t3057 = Str_lit("Str", 3ULL);
        (void)_t3057;
        U64 _t3058; { U64 *_hp = (U64 *)Str_size(); _t3058 = *_hp; free(_hp); }
        (void)_t3058;
        U64 _t3059 = 10;
        (void)_t3059;
        Array *_va54 = Array_new(_t3057, &(U64){_t3058}, &(U64){_t3059});
        (void)_va54;
        Str_delete(_t3057, &(Bool){1});
        ;
        ;
        U64 _t3060 = 0;
        (void)_t3060;
        Str *_t3061 = Str_clone(&p->path);
        (void)_t3061;
        Array_set(_va54, &(U64){_t3060}, _t3061);
        ;
        U64 _t3062 = 1;
        (void)_t3062;
        Str *_t3063 = Str_lit(":", 1ULL);
        (void)_t3063;
        Array_set(_va54, &(U64){_t3062}, _t3063);
        ;
        U64 _t3064 = 2;
        (void)_t3064;
        Str *_t3065 = U32_to_str(&t->line);
        (void)_t3065;
        Array_set(_va54, &(U64){_t3064}, _t3065);
        ;
        U64 _t3066 = 3;
        (void)_t3066;
        Str *_t3067 = Str_lit(":", 1ULL);
        (void)_t3067;
        Array_set(_va54, &(U64){_t3066}, _t3067);
        ;
        U64 _t3068 = 4;
        (void)_t3068;
        Str *_t3069 = U32_to_str(&t->col);
        (void)_t3069;
        Array_set(_va54, &(U64){_t3068}, _t3069);
        ;
        U64 _t3070 = 5;
        (void)_t3070;
        Str *_t3071 = Str_lit(": expected '", 12ULL);
        (void)_t3071;
        Array_set(_va54, &(U64){_t3070}, _t3071);
        ;
        U64 _t3072 = 6;
        (void)_t3072;
        Str *_t3073 = tok_name(type);
        (void)_t3073;
        Array_set(_va54, &(U64){_t3072}, _t3073);
        ;
        U64 _t3074 = 7;
        (void)_t3074;
        Str *_t3075 = Str_lit("', found '", 10ULL);
        (void)_t3075;
        Array_set(_va54, &(U64){_t3074}, _t3075);
        ;
        U64 _t3076 = 8;
        (void)_t3076;
        Str *_t3077 = Str_clone(&t->text);
        (void)_t3077;
        Array_set(_va54, &(U64){_t3076}, _t3077);
        ;
        U64 _t3078 = 9;
        (void)_t3078;
        Str *_t3079 = Str_lit("'", 1ULL);
        (void)_t3079;
        Array_set(_va54, &(U64){_t3078}, _t3079);
        ;
        Str *_t3080 = Str_lit("src/self/parser.til:34:15", 25ULL);
        (void)_t3080;
        panic(_t3080, _va54);
        Str_delete(_t3080, &(Bool){1});
    }
    ;
    Token *_t3083 = advance(p);
    (void)_t3083;
    return _t3083;
}

Str * expect_text(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Token *t = peek(p);
    (void)t;
    Bool _t3108; { Bool *_hp = (Bool *)TokenType_eq(&t->type, type); _t3108 = *_hp; free(_hp); }
    (void)_t3108;
    Bool _t3109 = Bool_not(_t3108);
    (void)_t3109;
    ;
    if (_t3109) {
        Str *_t3084 = Str_lit("Str", 3ULL);
        (void)_t3084;
        U64 _t3085; { U64 *_hp = (U64 *)Str_size(); _t3085 = *_hp; free(_hp); }
        (void)_t3085;
        U64 _t3086 = 10;
        (void)_t3086;
        Array *_va55 = Array_new(_t3084, &(U64){_t3085}, &(U64){_t3086});
        (void)_va55;
        Str_delete(_t3084, &(Bool){1});
        ;
        ;
        U64 _t3087 = 0;
        (void)_t3087;
        Str *_t3088 = Str_clone(&p->path);
        (void)_t3088;
        Array_set(_va55, &(U64){_t3087}, _t3088);
        ;
        U64 _t3089 = 1;
        (void)_t3089;
        Str *_t3090 = Str_lit(":", 1ULL);
        (void)_t3090;
        Array_set(_va55, &(U64){_t3089}, _t3090);
        ;
        U64 _t3091 = 2;
        (void)_t3091;
        Str *_t3092 = U32_to_str(&t->line);
        (void)_t3092;
        Array_set(_va55, &(U64){_t3091}, _t3092);
        ;
        U64 _t3093 = 3;
        (void)_t3093;
        Str *_t3094 = Str_lit(":", 1ULL);
        (void)_t3094;
        Array_set(_va55, &(U64){_t3093}, _t3094);
        ;
        U64 _t3095 = 4;
        (void)_t3095;
        Str *_t3096 = U32_to_str(&t->col);
        (void)_t3096;
        Array_set(_va55, &(U64){_t3095}, _t3096);
        ;
        U64 _t3097 = 5;
        (void)_t3097;
        Str *_t3098 = Str_lit(": expected '", 12ULL);
        (void)_t3098;
        Array_set(_va55, &(U64){_t3097}, _t3098);
        ;
        U64 _t3099 = 6;
        (void)_t3099;
        Str *_t3100 = tok_name(type);
        (void)_t3100;
        Array_set(_va55, &(U64){_t3099}, _t3100);
        ;
        U64 _t3101 = 7;
        (void)_t3101;
        Str *_t3102 = Str_lit("', found '", 10ULL);
        (void)_t3102;
        Array_set(_va55, &(U64){_t3101}, _t3102);
        ;
        U64 _t3103 = 8;
        (void)_t3103;
        Str *_t3104 = Str_clone(&t->text);
        (void)_t3104;
        Array_set(_va55, &(U64){_t3103}, _t3104);
        ;
        U64 _t3105 = 9;
        (void)_t3105;
        Str *_t3106 = Str_lit("'", 1ULL);
        (void)_t3106;
        Array_set(_va55, &(U64){_t3105}, _t3106);
        ;
        Str *_t3107 = Str_lit("src/self/parser.til:44:15", 25ULL);
        (void)_t3107;
        panic(_t3107, _va55);
        Str_delete(_t3107, &(Bool){1});
    }
    ;
    Str *text = Str_clone(&t->text);
    (void)text;
    Token *_t3110 = advance(p);
    (void)_t3110;
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

Expr * parse_fn_signature(Parser * p, U32 line, U32 col) {
    (void)p;
    (void)line;
    (void)col;
    Bool _t3146 = check(p, TokenType_LParen());
    (void)_t3146;
    Bool _t3147 = Bool_not(_t3146);
    (void)_t3147;
    ;
    if (_t3147) {
        U32 _t3111 = 0;
        (void)_t3111;
        U32 _t3112 = 0;
        (void)_t3112;
        Str *_t3113 = Str_lit("", 0ULL);
        (void)_t3113;
        Expr *_t3114 = Expr_new(ExprData_Body(), _t3111, _t3112, _t3113);
        (void)_t3114;
        ;
        ;
        Str_delete(_t3113, &(Bool){1});
        ;
        return _t3114;
    }
    ;
    Token *_t3148 = advance(p);
    (void)_t3148;
    Str *_t3149 = Str_lit("Str", 3ULL);
    (void)_t3149;
    U64 _t3150; { U64 *_hp = (U64 *)Str_size(); _t3150 = *_hp; free(_hp); }
    (void)_t3150;
    Vec *ptypes = Vec_new(_t3149, &(U64){_t3150});
    (void)ptypes;
    Str_delete(_t3149, &(Bool){1});
    ;
    Str *_t3151 = Str_lit("Bool", 4ULL);
    (void)_t3151;
    U64 _t3152; { U64 *_hp = (U64 *)Bool_size(); _t3152 = *_hp; free(_hp); }
    (void)_t3152;
    Vec *pmuts = Vec_new(_t3151, &(U64){_t3152});
    (void)pmuts;
    Str_delete(_t3151, &(Bool){1});
    ;
    while (1) {
        Bool _t3119 = check(p, TokenType_RParen());
        (void)_t3119;
        Bool _t3120 = check(p, TokenType_Eof());
        (void)_t3120;
        Bool _t3121 = Bool_not(_t3119);
        (void)_t3121;
        ;
        Bool _t3122 = Bool_not(_t3120);
        (void)_t3122;
        ;
        Bool _wcond3115 = Bool_and(_t3121, _t3122);
        (void)_wcond3115;
        ;
        ;
        if (_wcond3115) {
        } else {
            ;
            break;
        }
        ;
        Bool is_mut = 0;
        (void)is_mut;
        Bool _t3123 = check(p, TokenType_KwMut());
        (void)_t3123;
        if (_t3123) {
            Token *_t3116 = advance(p);
            (void)_t3116;
            Bool _t3117 = 1;
            (void)_t3117;
            is_mut = _t3117;
            ;
        }
        ;
        Str *ptype = expect_text(p, TokenType_Ident());
        (void)ptype;
        Vec_push(ptypes, ptype);
        Vec_push(pmuts, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = is_mut; _oa; }));
        Bool _t3124 = check(p, TokenType_Comma());
        (void)_t3124;
        if (_t3124) {
            Token *_t3118 = advance(p);
            (void)_t3118;
        }
        ;
    }
    Token *_t3153 = expect_token(p, TokenType_RParen());
    (void)_t3153;
    Str *return_type = Str_lit("", 0ULL);
    (void)return_type;
    Bool _t3154 = check(p, TokenType_KwReturns());
    (void)_t3154;
    if (_t3154) {
        Token *_t3125 = advance(p);
        (void)_t3125;
        return_type = expect_text(p, TokenType_Ident());
    }
    ;
    Str *_t3155 = Str_lit("Str", 3ULL);
    (void)_t3155;
    U64 _t3156; { U64 *_hp = (U64 *)Str_size(); _t3156 = *_hp; free(_hp); }
    (void)_t3156;
    Str *_t3157 = Str_lit("Str", 3ULL);
    (void)_t3157;
    U64 _t3158; { U64 *_hp = (U64 *)Str_size(); _t3158 = *_hp; free(_hp); }
    (void)_t3158;
    Str *_t3159 = Str_lit("Bool", 4ULL);
    (void)_t3159;
    U64 _t3160; { U64 *_hp = (U64 *)Bool_size(); _t3160 = *_hp; free(_hp); }
    (void)_t3160;
    Str *_t3161 = Str_lit("Bool", 4ULL);
    (void)_t3161;
    U64 _t3162; { U64 *_hp = (U64 *)Bool_size(); _t3162 = *_hp; free(_hp); }
    (void)_t3162;
    Str *_t3163 = Str_lit("Bool", 4ULL);
    (void)_t3163;
    U64 _t3164; { U64 *_hp = (U64 *)Bool_size(); _t3164 = *_hp; free(_hp); }
    (void)_t3164;
    Str *_t3165 = Str_lit("I64", 3ULL);
    (void)_t3165;
    U64 _t3166; { U64 *_hp = (U64 *)I64_size(); _t3166 = *_hp; free(_hp); }
    (void)_t3166;
    Str *_t3167 = Str_lit("I64", 3ULL);
    (void)_t3167;
    U64 _t3168; { U64 *_hp = (U64 *)I64_size(); _t3168 = *_hp; free(_hp); }
    (void)_t3168;
    I64 _t3169 = 0;
    (void)_t3169;
    I64 _t3170 = 1;
    (void)_t3170;
    I64 _t3171 = I64_sub(_t3169, _t3170);
    (void)_t3171;
    ;
    ;
    I64 _t3172 = 0;
    (void)_t3172;
    I64 _t3173 = 1;
    (void)_t3173;
    I64 _t3174 = I64_sub(_t3172, _t3173);
    (void)_t3174;
    ;
    ;
    U32 _t3175 = 0;
    (void)_t3175;
    I32 _t3176 = I64_to_i32(_t3171);
    (void)_t3176;
    ;
    I32 _t3177 = I64_to_i32(_t3174);
    (void)_t3177;
    ;
    Bool _t3178 = 0;
    (void)_t3178;
    Bool _t3179 = 0;
    (void)_t3179;
    FunctionDef *fd = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(FuncType_Func()); fd->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3155, &(U64){_t3156}); fd->param_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3157, &(U64){_t3158}); fd->param_types = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3159, &(U64){_t3160}); fd->param_muts = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3161, &(U64){_t3162}); fd->param_owns = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3163, &(U64){_t3164}); fd->param_shallows = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3165, &(U64){_t3166}); fd->param_fn_sigs = *_ca; free(_ca); }
    fd->nparam = _t3175;
    { Vec *_ca = Vec_new(_t3167, &(U64){_t3168}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3176;
    fd->kwargs_index = _t3177;
    fd->return_is_ref = _t3178;
    fd->return_is_shallow = _t3179;
    (void)fd;
    Str_delete(_t3155, &(Bool){1});
    ;
    Str_delete(_t3157, &(Bool){1});
    ;
    Str_delete(_t3159, &(Bool){1});
    ;
    Str_delete(_t3161, &(Bool){1});
    ;
    Str_delete(_t3163, &(Bool){1});
    ;
    Str_delete(_t3165, &(Bool){1});
    ;
    Str_delete(_t3167, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    U64 _t3180; { U64 *_hp = (U64 *)Str_len(return_type); _t3180 = *_hp; free(_hp); }
    (void)_t3180;
    U64 _t3181 = 0;
    (void)_t3181;
    Bool _t3182; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3180}, &(U64){_t3181}); _t3182 = *_hp; free(_hp); }
    (void)_t3182;
    ;
    ;
    if (_t3182) {
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
    Bool _t3183 = 0;
    (void)_t3183;
    fd->return_is_ref = _t3183;
    ;
    Bool _t3184 = 0;
    (void)_t3184;
    fd->return_is_shallow = _t3184;
    ;
    I64 _t3185 = 0;
    (void)_t3185;
    I64 _t3186 = 1;
    (void)_t3186;
    I64 _t3187 = I64_sub(_t3185, _t3186);
    (void)_t3187;
    ;
    ;
    I32 _t3188 = I64_to_i32(_t3187);
    (void)_t3188;
    ;
    fd->variadic_index = _t3188;
    ;
    I64 _t3189 = 0;
    (void)_t3189;
    I64 _t3190 = 1;
    (void)_t3190;
    I64 _t3191 = I64_sub(_t3189, _t3190);
    (void)_t3191;
    ;
    ;
    I32 _t3192 = I64_to_i32(_t3191);
    (void)_t3192;
    ;
    fd->kwargs_index = _t3192;
    ;
    {
        U64 _fi3126 = 0;
        (void)_fi3126;
        while (1) {
            U64 _t3128 = 0;
            (void)_t3128;
            U64 _t3129; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3129 = *_hp; free(_hp); }
            (void)_t3129;
            Range *_t3130 = Range_new(_t3128, _t3129);
            (void)_t3130;
            ;
            ;
            U64 _t3131; { U64 *_hp = (U64 *)Range_len(_t3130); _t3131 = *_hp; free(_hp); }
            (void)_t3131;
            Range_delete(_t3130, &(Bool){1});
            Bool _wcond3127; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3126}, &(U64){_t3131}); _wcond3127 = *_hp; free(_hp); }
            (void)_wcond3127;
            ;
            if (_wcond3127) {
            } else {
                ;
                break;
            }
            ;
            U64 _t3132 = 0;
            (void)_t3132;
            U64 _t3133; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3133 = *_hp; free(_hp); }
            (void)_t3133;
            Range *_t3134 = Range_new(_t3132, _t3133);
            (void)_t3134;
            ;
            ;
            U64 _; { U64 *_hp = (U64 *)Range_get(_t3134, _fi3126); _ = *_hp; free(_hp); }
            (void)_;
            ;
            Range_delete(_t3134, &(Bool){1});
            U64 _t3135 = 1;
            (void)_t3135;
            U64 _t3136 = U64_add(_fi3126, _t3135);
            (void)_t3136;
            ;
            _fi3126 = _t3136;
            ;
            Str *_t3137 = Str_lit("", 0ULL);
            (void)_t3137;
            Vec_push(&fd->param_names, _t3137);
            Bool _t3138 = 0;
            (void)_t3138;
            Vec_push(&fd->param_owns, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3138; _oa; }));
            Bool _t3139 = 0;
            (void)_t3139;
            Vec_push(&fd->param_shallows, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3139; _oa; }));
            I64 _t3140 = 0;
            (void)_t3140;
            I64 _t3141 = 1;
            (void)_t3141;
            I64 _t3142 = I64_sub(_t3140, _t3141);
            (void)_t3142;
            ;
            ;
            Vec_push(&fd->param_defaults, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = _t3142; _oa; }));
            I64 _t3143 = 0;
            (void)_t3143;
            I64 _t3144 = 1;
            (void)_t3144;
            I64 _t3145 = I64_sub(_t3143, _t3144);
            (void)_t3145;
            ;
            ;
            Vec_push(&fd->param_fn_sigs, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = _t3145; _oa; }));
        }
        ;
    }
    Vec_delete(&fd->param_types, &(Bool){0});
    { Vec *_fa = Vec_clone(ptypes); fd->param_types = *_fa; free(_fa); }
    Vec_delete(ptypes, &(Bool){1});
    Vec_delete(&fd->param_muts, &(Bool){0});
    { Vec *_fa = Vec_clone(pmuts); fd->param_muts = *_fa; free(_fa); }
    Vec_delete(pmuts, &(Bool){1});
    ExprData *_t3193 = ExprData_FuncDef(fd);
    (void)_t3193;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *sig = Expr_new(_t3193, line, col, &p->path);
    (void)sig;
    ExprData_delete(_t3193, &(Bool){1});
    return sig;
}

Expr * parse_block(Parser * p) {
    (void)p;
    U32 _t3200 = peek_line(p);
    (void)_t3200;
    U32 _t3201 = peek_col(p);
    (void)_t3201;
    Expr *body = Expr_new(ExprData_Body(), _t3200, _t3201, &p->path);
    (void)body;
    ;
    ;
    while (1) {
        Bool _t3195 = check(p, TokenType_RBrace());
        (void)_t3195;
        Bool _t3196 = check(p, TokenType_Eof());
        (void)_t3196;
        Bool _t3197 = Bool_not(_t3195);
        (void)_t3197;
        ;
        Bool _t3198 = Bool_not(_t3196);
        (void)_t3198;
        ;
        Bool _wcond3194 = Bool_and(_t3197, _t3198);
        (void)_wcond3194;
        ;
        ;
        if (_wcond3194) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t3199 = parse_statement(p);
        (void)_t3199;
        Expr_add_child(body, _t3199);
    }
    Token *_t3202 = expect_token(p, TokenType_RBrace());
    (void)_t3202;
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
        TokenType *_sw3203 = TokenType_clone(&kw->type);
        (void)_sw3203;
        Bool _t3215; { Bool *_hp = (Bool *)TokenType_eq(_sw3203, TokenType_KwFunc()); _t3215 = *_hp; free(_hp); }
        (void)_t3215;
        if (_t3215) {
            ft = FuncType_clone(FuncType_Func());
        } else {
            Bool _t3214; { Bool *_hp = (Bool *)TokenType_eq(_sw3203, TokenType_KwProc()); _t3214 = *_hp; free(_hp); }
            (void)_t3214;
            if (_t3214) {
                ft = FuncType_clone(FuncType_Proc());
            } else {
                Bool _t3213; { Bool *_hp = (Bool *)TokenType_eq(_sw3203, TokenType_KwTest()); _t3213 = *_hp; free(_hp); }
                (void)_t3213;
                if (_t3213) {
                    ft = FuncType_clone(FuncType_Test());
                } else {
                    Bool _t3212; { Bool *_hp = (Bool *)TokenType_eq(_sw3203, TokenType_KwMacro()); _t3212 = *_hp; free(_hp); }
                    (void)_t3212;
                    if (_t3212) {
                        ft = FuncType_clone(FuncType_Macro());
                    } else {
                        Bool _t3211; { Bool *_hp = (Bool *)TokenType_eq(_sw3203, TokenType_KwExtFunc()); _t3211 = *_hp; free(_hp); }
                        (void)_t3211;
                        if (_t3211) {
                            ft = FuncType_clone(FuncType_ExtFunc());
                        } else {
                            Bool _t3210; { Bool *_hp = (Bool *)TokenType_eq(_sw3203, TokenType_KwExtProc()); _t3210 = *_hp; free(_hp); }
                            (void)_t3210;
                            if (_t3210) {
                                ft = FuncType_clone(FuncType_ExtProc());
                            } else {
                                Str *_t3204 = Str_lit("Str", 3ULL);
                                (void)_t3204;
                                U64 _t3205; { U64 *_hp = (U64 *)Str_size(); _t3205 = *_hp; free(_hp); }
                                (void)_t3205;
                                U64 _t3206 = 1;
                                (void)_t3206;
                                Array *_va56 = Array_new(_t3204, &(U64){_t3205}, &(U64){_t3206});
                                (void)_va56;
                                Str_delete(_t3204, &(Bool){1});
                                ;
                                ;
                                U64 _t3207 = 0;
                                (void)_t3207;
                                Str *_t3208 = Str_lit("expected function keyword", 25ULL);
                                (void)_t3208;
                                Array_set(_va56, &(U64){_t3207}, _t3208);
                                ;
                                Str *_t3209 = Str_lit("src/self/parser.til:135:17", 26ULL);
                                (void)_t3209;
                                panic(_t3209, _va56);
                                Str_delete(_t3209, &(Bool){1});
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
        TokenType_delete(_sw3203, &(Bool){1});
        ;
    }
    Token *_t3409 = expect_token(p, TokenType_LParen());
    (void)_t3409;
    Str *_t3410 = Str_lit("Str", 3ULL);
    (void)_t3410;
    U64 _t3411; { U64 *_hp = (U64 *)Str_size(); _t3411 = *_hp; free(_hp); }
    (void)_t3411;
    Str *_t3412 = Str_lit("Str", 3ULL);
    (void)_t3412;
    U64 _t3413; { U64 *_hp = (U64 *)Str_size(); _t3413 = *_hp; free(_hp); }
    (void)_t3413;
    Str *_t3414 = Str_lit("Bool", 4ULL);
    (void)_t3414;
    U64 _t3415; { U64 *_hp = (U64 *)Bool_size(); _t3415 = *_hp; free(_hp); }
    (void)_t3415;
    Str *_t3416 = Str_lit("Bool", 4ULL);
    (void)_t3416;
    U64 _t3417; { U64 *_hp = (U64 *)Bool_size(); _t3417 = *_hp; free(_hp); }
    (void)_t3417;
    Str *_t3418 = Str_lit("Bool", 4ULL);
    (void)_t3418;
    U64 _t3419; { U64 *_hp = (U64 *)Bool_size(); _t3419 = *_hp; free(_hp); }
    (void)_t3419;
    Str *_t3420 = Str_lit("I64", 3ULL);
    (void)_t3420;
    U64 _t3421; { U64 *_hp = (U64 *)I64_size(); _t3421 = *_hp; free(_hp); }
    (void)_t3421;
    Str *_t3422 = Str_lit("I64", 3ULL);
    (void)_t3422;
    U64 _t3423; { U64 *_hp = (U64 *)I64_size(); _t3423 = *_hp; free(_hp); }
    (void)_t3423;
    I64 _t3424 = 0;
    (void)_t3424;
    I64 _t3425 = 1;
    (void)_t3425;
    I64 _t3426 = I64_sub(_t3424, _t3425);
    (void)_t3426;
    ;
    ;
    I64 _t3427 = 0;
    (void)_t3427;
    I64 _t3428 = 1;
    (void)_t3428;
    I64 _t3429 = I64_sub(_t3427, _t3428);
    (void)_t3429;
    ;
    ;
    U32 _t3430 = 0;
    (void)_t3430;
    I32 _t3431 = I64_to_i32(_t3426);
    (void)_t3431;
    ;
    I32 _t3432 = I64_to_i32(_t3429);
    (void)_t3432;
    ;
    Bool _t3433 = 0;
    (void)_t3433;
    Bool _t3434 = 0;
    (void)_t3434;
    FunctionDef *fd = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(FuncType_Func()); fd->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3410, &(U64){_t3411}); fd->param_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3412, &(U64){_t3413}); fd->param_types = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3414, &(U64){_t3415}); fd->param_muts = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3416, &(U64){_t3417}); fd->param_owns = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3418, &(U64){_t3419}); fd->param_shallows = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3420, &(U64){_t3421}); fd->param_fn_sigs = *_ca; free(_ca); }
    fd->nparam = _t3430;
    { Vec *_ca = Vec_new(_t3422, &(U64){_t3423}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3431;
    fd->kwargs_index = _t3432;
    fd->return_is_ref = _t3433;
    fd->return_is_shallow = _t3434;
    (void)fd;
    Str_delete(_t3410, &(Bool){1});
    ;
    Str_delete(_t3412, &(Bool){1});
    ;
    Str_delete(_t3414, &(Bool){1});
    ;
    Str_delete(_t3416, &(Bool){1});
    ;
    Str_delete(_t3418, &(Bool){1});
    ;
    Str_delete(_t3420, &(Bool){1});
    ;
    Str_delete(_t3422, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    FuncType_delete(&fd->func_type, &(Bool){0});
    { FuncType *_fa = FuncType_clone(ft); fd->func_type = *_fa; free(_fa); }
    Str *_t3435 = Str_lit("Expr", 4ULL);
    (void)_t3435;
    U64 _t3436; { U64 *_hp = (U64 *)Expr_size(); _t3436 = *_hp; free(_hp); }
    (void)_t3436;
    Vec *def_exprs = Vec_new(_t3435, &(U64){_t3436});
    (void)def_exprs;
    Str_delete(_t3435, &(Bool){1});
    ;
    while (1) {
        Bool _t3334 = check(p, TokenType_RParen());
        (void)_t3334;
        Bool _t3335 = check(p, TokenType_Eof());
        (void)_t3335;
        Bool _t3336 = Bool_not(_t3334);
        (void)_t3336;
        ;
        Bool _t3337 = Bool_not(_t3335);
        (void)_t3337;
        ;
        Bool _wcond3216 = Bool_and(_t3336, _t3337);
        (void)_wcond3216;
        ;
        ;
        if (_wcond3216) {
        } else {
            ;
            break;
        }
        ;
        Bool is_shallow = 0;
        (void)is_shallow;
        Bool _t3338 = check(p, TokenType_KwShallow());
        (void)_t3338;
        if (_t3338) {
            Token *_t3217 = advance(p);
            (void)_t3217;
            Bool _t3218 = 1;
            (void)_t3218;
            is_shallow = _t3218;
            ;
        }
        ;
        Bool is_own = 0;
        (void)is_own;
        Bool _t3339 = check(p, TokenType_KwOwn());
        (void)_t3339;
        if (_t3339) {
            Token *_t3219 = advance(p);
            (void)_t3219;
            Bool _t3220 = 1;
            (void)_t3220;
            is_own = _t3220;
            ;
        }
        ;
        Bool is_mut = 0;
        (void)is_mut;
        Bool _t3340 = check(p, TokenType_KwMut());
        (void)_t3340;
        if (_t3340) {
            Token *_t3221 = advance(p);
            (void)_t3221;
            Bool _t3222 = 1;
            (void)_t3222;
            is_mut = _t3222;
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
        Bool _t3341 = check(p, TokenType_Colon());
        (void)_t3341;
        Bool _t3342 = Bool_not(_t3341);
        (void)_t3342;
        ;
        if (_t3342) {
            tp = Str_clone(pname);
            nm = Str_lit("", 0ULL);
        } else {
            Token *_t3316 = expect_token(p, TokenType_Colon());
            (void)_t3316;
            Bool _t3317 = check(p, TokenType_DotDotDot());
            (void)_t3317;
            if (_t3317) {
                Token *_t3253 = advance(p);
                (void)_t3253;
                Bool _t3254 = Bool_or(is_own, is_mut);
                (void)_t3254;
                Bool _t3255 = Bool_or(_t3254, is_shallow);
                (void)_t3255;
                ;
                if (_t3255) {
                    Str *_t3223 = Str_lit("Str", 3ULL);
                    (void)_t3223;
                    U64 _t3224; { U64 *_hp = (U64 *)Str_size(); _t3224 = *_hp; free(_hp); }
                    (void)_t3224;
                    U64 _t3225 = 6;
                    (void)_t3225;
                    Array *_va57 = Array_new(_t3223, &(U64){_t3224}, &(U64){_t3225});
                    (void)_va57;
                    Str_delete(_t3223, &(Bool){1});
                    ;
                    ;
                    U64 _t3226 = 0;
                    (void)_t3226;
                    Str *_t3227 = Str_clone(&p->path);
                    (void)_t3227;
                    Array_set(_va57, &(U64){_t3226}, _t3227);
                    ;
                    U64 _t3228 = 1;
                    (void)_t3228;
                    Str *_t3229 = Str_lit(":", 1ULL);
                    (void)_t3229;
                    Array_set(_va57, &(U64){_t3228}, _t3229);
                    ;
                    U32 _t3230 = peek_line(p);
                    (void)_t3230;
                    U64 _t3231 = 2;
                    (void)_t3231;
                    Str *_t3232 = U32_to_str(&(U32){_t3230});
                    (void)_t3232;
                    ;
                    Array_set(_va57, &(U64){_t3231}, _t3232);
                    ;
                    U64 _t3233 = 3;
                    (void)_t3233;
                    Str *_t3234 = Str_lit(":", 1ULL);
                    (void)_t3234;
                    Array_set(_va57, &(U64){_t3233}, _t3234);
                    ;
                    U32 _t3235 = peek_col(p);
                    (void)_t3235;
                    U64 _t3236 = 4;
                    (void)_t3236;
                    Str *_t3237 = U32_to_str(&(U32){_t3235});
                    (void)_t3237;
                    ;
                    Array_set(_va57, &(U64){_t3236}, _t3237);
                    ;
                    U64 _t3238 = 5;
                    (void)_t3238;
                    Str *_t3239 = Str_lit(": kwargs parameter cannot be own/mut/shallow", 44ULL);
                    (void)_t3239;
                    Array_set(_va57, &(U64){_t3238}, _t3239);
                    ;
                    Str *_t3240 = Str_lit("src/self/parser.til:166:27", 26ULL);
                    (void)_t3240;
                    panic(_t3240, _va57);
                    Str_delete(_t3240, &(Bool){1});
                }
                ;
                I64 _t3256 = 0;
                (void)_t3256;
                I64 _t3257 = 1;
                (void)_t3257;
                I64 _t3258 = I64_sub(_t3256, _t3257);
                (void)_t3258;
                ;
                ;
                I32 _t3259 = I64_to_i32(_t3258);
                (void)_t3259;
                ;
                Bool _t3260; { Bool *_hp = (Bool *)I32_neq(&fd->kwargs_index, &(I32){_t3259}); _t3260 = *_hp; free(_hp); }
                (void)_t3260;
                ;
                if (_t3260) {
                    Str *_t3241 = Str_lit("Str", 3ULL);
                    (void)_t3241;
                    U64 _t3242; { U64 *_hp = (U64 *)Str_size(); _t3242 = *_hp; free(_hp); }
                    (void)_t3242;
                    U64 _t3243 = 1;
                    (void)_t3243;
                    Array *_va58 = Array_new(_t3241, &(U64){_t3242}, &(U64){_t3243});
                    (void)_va58;
                    Str_delete(_t3241, &(Bool){1});
                    ;
                    ;
                    U64 _t3244 = 0;
                    (void)_t3244;
                    Str *_t3245 = Str_lit("only one kwargs parameter is allowed", 36ULL);
                    (void)_t3245;
                    Array_set(_va58, &(U64){_t3244}, _t3245);
                    ;
                    Str *_t3246 = Str_lit("src/self/parser.til:170:27", 26ULL);
                    (void)_t3246;
                    panic(_t3246, _va58);
                    Str_delete(_t3246, &(Bool){1});
                }
                ;
                I64 _t3261 = 0;
                (void)_t3261;
                I64 _t3262 = 1;
                (void)_t3262;
                I64 _t3263 = I64_sub(_t3261, _t3262);
                (void)_t3263;
                ;
                ;
                I32 _t3264 = I64_to_i32(_t3263);
                (void)_t3264;
                ;
                Bool _t3265; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3264}); _t3265 = *_hp; free(_hp); }
                (void)_t3265;
                ;
                if (_t3265) {
                    Str *_t3247 = Str_lit("Str", 3ULL);
                    (void)_t3247;
                    U64 _t3248; { U64 *_hp = (U64 *)Str_size(); _t3248 = *_hp; free(_hp); }
                    (void)_t3248;
                    U64 _t3249 = 1;
                    (void)_t3249;
                    Array *_va59 = Array_new(_t3247, &(U64){_t3248}, &(U64){_t3249});
                    (void)_va59;
                    Str_delete(_t3247, &(Bool){1});
                    ;
                    ;
                    U64 _t3250 = 0;
                    (void)_t3250;
                    Str *_t3251 = Str_lit("cannot combine variadic and kwargs in the same function", 55ULL);
                    (void)_t3251;
                    Array_set(_va59, &(U64){_t3250}, _t3251);
                    ;
                    Str *_t3252 = Str_lit("src/self/parser.til:173:27", 26ULL);
                    (void)_t3252;
                    panic(_t3252, _va59);
                    Str_delete(_t3252, &(Bool){1});
                }
                ;
                U64 _t3266; { U64 *_hp = (U64 *)Vec_len(&fd->param_names); _t3266 = *_hp; free(_hp); }
                (void)_t3266;
                I64 _t3267 = U64_to_i64(_t3266);
                (void)_t3267;
                ;
                I32 _t3268 = I64_to_i32(_t3267);
                (void)_t3268;
                ;
                fd->kwargs_index = _t3268;
                ;
                Bool _t3269 = 1;
                (void)_t3269;
                is_own = _t3269;
                ;
                nm = Str_clone(pname);
                tp = Str_lit("Map", 3ULL);
            } else {
                Bool _t3315 = check(p, TokenType_DotDot());
                (void)_t3315;
                if (_t3315) {
                    Token *_t3300 = advance(p);
                    (void)_t3300;
                    if (is_own) {
                        Str *_t3270 = Str_lit("Str", 3ULL);
                        (void)_t3270;
                        U64 _t3271; { U64 *_hp = (U64 *)Str_size(); _t3271 = *_hp; free(_hp); }
                        (void)_t3271;
                        U64 _t3272 = 1;
                        (void)_t3272;
                        Array *_va60 = Array_new(_t3270, &(U64){_t3271}, &(U64){_t3272});
                        (void)_va60;
                        Str_delete(_t3270, &(Bool){1});
                        ;
                        ;
                        U64 _t3273 = 0;
                        (void)_t3273;
                        Str *_t3274 = Str_lit("variadic param cannot be 'own'", 30ULL);
                        (void)_t3274;
                        Array_set(_va60, &(U64){_t3273}, _t3274);
                        ;
                        Str *_t3275 = Str_lit("src/self/parser.til:181:35", 26ULL);
                        (void)_t3275;
                        panic(_t3275, _va60);
                        Str_delete(_t3275, &(Bool){1});
                    }
                    if (is_mut) {
                        Str *_t3276 = Str_lit("Str", 3ULL);
                        (void)_t3276;
                        U64 _t3277; { U64 *_hp = (U64 *)Str_size(); _t3277 = *_hp; free(_hp); }
                        (void)_t3277;
                        U64 _t3278 = 1;
                        (void)_t3278;
                        Array *_va61 = Array_new(_t3276, &(U64){_t3277}, &(U64){_t3278});
                        (void)_va61;
                        Str_delete(_t3276, &(Bool){1});
                        ;
                        ;
                        U64 _t3279 = 0;
                        (void)_t3279;
                        Str *_t3280 = Str_lit("variadic param cannot be 'mut'", 30ULL);
                        (void)_t3280;
                        Array_set(_va61, &(U64){_t3279}, _t3280);
                        ;
                        Str *_t3281 = Str_lit("src/self/parser.til:182:35", 26ULL);
                        (void)_t3281;
                        panic(_t3281, _va61);
                        Str_delete(_t3281, &(Bool){1});
                    }
                    if (is_shallow) {
                        Str *_t3282 = Str_lit("Str", 3ULL);
                        (void)_t3282;
                        U64 _t3283; { U64 *_hp = (U64 *)Str_size(); _t3283 = *_hp; free(_hp); }
                        (void)_t3283;
                        U64 _t3284 = 1;
                        (void)_t3284;
                        Array *_va62 = Array_new(_t3282, &(U64){_t3283}, &(U64){_t3284});
                        (void)_va62;
                        Str_delete(_t3282, &(Bool){1});
                        ;
                        ;
                        U64 _t3285 = 0;
                        (void)_t3285;
                        Str *_t3286 = Str_lit("variadic param cannot be 'shallow'", 34ULL);
                        (void)_t3286;
                        Array_set(_va62, &(U64){_t3285}, _t3286);
                        ;
                        Str *_t3287 = Str_lit("src/self/parser.til:183:39", 26ULL);
                        (void)_t3287;
                        panic(_t3287, _va62);
                        Str_delete(_t3287, &(Bool){1});
                    }
                    I64 _t3301 = 0;
                    (void)_t3301;
                    I64 _t3302 = 1;
                    (void)_t3302;
                    I64 _t3303 = I64_sub(_t3301, _t3302);
                    (void)_t3303;
                    ;
                    ;
                    I32 _t3304 = I64_to_i32(_t3303);
                    (void)_t3304;
                    ;
                    Bool _t3305; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3304}); _t3305 = *_hp; free(_hp); }
                    (void)_t3305;
                    ;
                    if (_t3305) {
                        Str *_t3288 = Str_lit("Str", 3ULL);
                        (void)_t3288;
                        U64 _t3289; { U64 *_hp = (U64 *)Str_size(); _t3289 = *_hp; free(_hp); }
                        (void)_t3289;
                        U64 _t3290 = 1;
                        (void)_t3290;
                        Array *_va63 = Array_new(_t3288, &(U64){_t3289}, &(U64){_t3290});
                        (void)_va63;
                        Str_delete(_t3288, &(Bool){1});
                        ;
                        ;
                        U64 _t3291 = 0;
                        (void)_t3291;
                        Str *_t3292 = Str_lit("only one variadic param allowed", 31ULL);
                        (void)_t3292;
                        Array_set(_va63, &(U64){_t3291}, _t3292);
                        ;
                        Str *_t3293 = Str_lit("src/self/parser.til:184:69", 26ULL);
                        (void)_t3293;
                        panic(_t3293, _va63);
                        Str_delete(_t3293, &(Bool){1});
                    }
                    ;
                    I64 _t3306 = 0;
                    (void)_t3306;
                    I64 _t3307 = 1;
                    (void)_t3307;
                    I64 _t3308 = I64_sub(_t3306, _t3307);
                    (void)_t3308;
                    ;
                    ;
                    I32 _t3309 = I64_to_i32(_t3308);
                    (void)_t3309;
                    ;
                    Bool _t3310; { Bool *_hp = (Bool *)I32_neq(&fd->kwargs_index, &(I32){_t3309}); _t3310 = *_hp; free(_hp); }
                    (void)_t3310;
                    ;
                    if (_t3310) {
                        Str *_t3294 = Str_lit("Str", 3ULL);
                        (void)_t3294;
                        U64 _t3295; { U64 *_hp = (U64 *)Str_size(); _t3295 = *_hp; free(_hp); }
                        (void)_t3295;
                        U64 _t3296 = 1;
                        (void)_t3296;
                        Array *_va64 = Array_new(_t3294, &(U64){_t3295}, &(U64){_t3296});
                        (void)_va64;
                        Str_delete(_t3294, &(Bool){1});
                        ;
                        ;
                        U64 _t3297 = 0;
                        (void)_t3297;
                        Str *_t3298 = Str_lit("cannot combine variadic and kwargs in the same function", 55ULL);
                        (void)_t3298;
                        Array_set(_va64, &(U64){_t3297}, _t3298);
                        ;
                        Str *_t3299 = Str_lit("src/self/parser.til:186:27", 26ULL);
                        (void)_t3299;
                        panic(_t3299, _va64);
                        Str_delete(_t3299, &(Bool){1});
                    }
                    ;
                    U64 _t3311; { U64 *_hp = (U64 *)Vec_len(&fd->param_names); _t3311 = *_hp; free(_hp); }
                    (void)_t3311;
                    I64 _t3312 = U64_to_i64(_t3311);
                    (void)_t3312;
                    ;
                    I32 _t3313 = I64_to_i32(_t3312);
                    (void)_t3313;
                    ;
                    fd->variadic_index = _t3313;
                    ;
                    Bool _t3314 = 1;
                    (void)_t3314;
                    is_variadic = _t3314;
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
        I64 _t3343 = 0;
        (void)_t3343;
        I64 _t3344 = 1;
        (void)_t3344;
        I64 fn_sig_idx = I64_sub(_t3343, _t3344);
        (void)fn_sig_idx;
        ;
        ;
        Str *_t3345 = Str_lit("Fn", 2ULL);
        (void)_t3345;
        Bool _t3346; { Bool *_hp = (Bool *)Str_eq(tp, _t3345); _t3346 = *_hp; free(_hp); }
        (void)_t3346;
        Str_delete(_t3345, &(Bool){1});
        if (_t3346) {
            U32 _t3320 = peek_line(p);
            (void)_t3320;
            U32 _t3321 = peek_col(p);
            (void)_t3321;
            Expr *sig = parse_fn_signature(p, _t3320, _t3321);
            (void)sig;
            ;
            ;
            U32 _t3322 = 0;
            (void)_t3322;
            Bool _t3323; { Bool *_hp = (Bool *)U32_neq(&sig->line, &(U32){_t3322}); _t3323 = *_hp; free(_hp); }
            (void)_t3323;
            ;
            if (_t3323) {
                U64 _t3318; { U64 *_hp = (U64 *)Vec_len(def_exprs); _t3318 = *_hp; free(_hp); }
                (void)_t3318;
                I64 _t3319 = U64_to_i64(_t3318);
                (void)_t3319;
                ;
                fn_sig_idx = _t3319;
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
        I64 _t3347 = 0;
        (void)_t3347;
        I64 _t3348 = 1;
        (void)_t3348;
        I64 has_default = I64_sub(_t3347, _t3348);
        (void)has_default;
        ;
        ;
        Bool _t3349 = check(p, TokenType_Eq());
        (void)_t3349;
        if (_t3349) {
            Token *_t3324 = advance(p);
            (void)_t3324;
            U64 _t3325; { U64 *_hp = (U64 *)Vec_len(def_exprs); _t3325 = *_hp; free(_hp); }
            (void)_t3325;
            I64 _t3326 = U64_to_i64(_t3325);
            (void)_t3326;
            ;
            has_default = _t3326;
            ;
            Expr *def_expr = parse_expression(p);
            (void)def_expr;
            Vec_push(def_exprs, def_expr);
        }
        ;
        I64 _t3350 = 0;
        (void)_t3350;
        I64 _t3351 = 1;
        (void)_t3351;
        I64 _t3352 = I64_sub(_t3350, _t3351);
        (void)_t3352;
        ;
        ;
        I32 _t3353 = I64_to_i32(_t3352);
        (void)_t3353;
        ;
        Bool _t3354; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3353}); _t3354 = *_hp; free(_hp); }
        (void)_t3354;
        ;
        Bool _t3355 = Bool_not(is_variadic);
        (void)_t3355;
        ;
        I64 _t3356 = 0;
        (void)_t3356;
        I64 _t3357 = 1;
        (void)_t3357;
        I64 _t3358 = I64_sub(_t3356, _t3357);
        (void)_t3358;
        ;
        ;
        Bool _t3359 = Bool_and(_t3354, _t3355);
        (void)_t3359;
        ;
        ;
        Bool _t3360 = I64_eq(has_default, _t3358);
        (void)_t3360;
        ;
        Bool _t3361 = Bool_and(_t3359, _t3360);
        (void)_t3361;
        ;
        ;
        if (_t3361) {
            Str *_t3327 = Str_lit("Str", 3ULL);
            (void)_t3327;
            U64 _t3328; { U64 *_hp = (U64 *)Str_size(); _t3328 = *_hp; free(_hp); }
            (void)_t3328;
            U64 _t3329 = 1;
            (void)_t3329;
            Array *_va65 = Array_new(_t3327, &(U64){_t3328}, &(U64){_t3329});
            (void)_va65;
            Str_delete(_t3327, &(Bool){1});
            ;
            ;
            U64 _t3330 = 0;
            (void)_t3330;
            Str *_t3331 = Str_lit("positional param not allowed after variadic", 43ULL);
            (void)_t3331;
            Array_set(_va65, &(U64){_t3330}, _t3331);
            ;
            Str *_t3332 = Str_lit("src/self/parser.til:225:19", 26ULL);
            (void)_t3332;
            panic(_t3332, _va65);
            Str_delete(_t3332, &(Bool){1});
        }
        ;
        Vec_push(&fd->param_defaults, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = has_default; _oa; }));
        Bool _t3362 = check(p, TokenType_Comma());
        (void)_t3362;
        if (_t3362) {
            Token *_t3333 = advance(p);
            (void)_t3333;
        }
        ;
    }
    Token *_t3437 = expect_token(p, TokenType_RParen());
    (void)_t3437;
    Bool _t3438 = check(p, TokenType_KwReturns());
    (void)_t3438;
    if (_t3438) {
        Token *_t3368 = advance(p);
        (void)_t3368;
        Bool _t3369 = check(p, TokenType_KwRef());
        (void)_t3369;
        if (_t3369) {
            Token *_t3363 = advance(p);
            (void)_t3363;
            Bool _t3364 = 1;
            (void)_t3364;
            fd->return_is_ref = _t3364;
            ;
        } else {
            Bool _t3367 = check(p, TokenType_KwShallow());
            (void)_t3367;
            if (_t3367) {
                Token *_t3365 = advance(p);
                (void)_t3365;
                Bool _t3366 = 1;
                (void)_t3366;
                fd->return_is_shallow = _t3366;
                ;
            }
            ;
        }
        ;
        Str_delete(&fd->return_type, &(Bool){0});
        { Str *_fa = expect_text(p, TokenType_Ident()); fd->return_type = *_fa; free(_fa); }
    }
    ;
    ExprData *_t3439 = ExprData_FuncDef(fd);
    (void)_t3439;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *def = Expr_new(_t3439, kw_line, kw_col, &p->path);
    (void)def;
    ExprData_delete(_t3439, &(Bool){1});
    Bool _t3440 = check(p, TokenType_LBrace());
    (void)_t3440;
    if (_t3440) {
        Token *_t3370 = expect_token(p, TokenType_LBrace());
        (void)_t3370;
        Expr *_t3371 = parse_block(p);
        (void)_t3371;
        Expr_add_child(def, _t3371);
    } else {
        Bool _t3392; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Func()); _t3392 = *_hp; free(_hp); }
        (void)_t3392;
        Bool _t3393; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Proc()); _t3393 = *_hp; free(_hp); }
        (void)_t3393;
        Bool _t3394 = Bool_not(_t3392);
        (void)_t3394;
        ;
        Bool _t3395 = Bool_not(_t3393);
        (void)_t3395;
        ;
        Bool _t3396 = Bool_and(_t3394, _t3395);
        (void)_t3396;
        ;
        ;
        if (_t3396) {
            Str *_t3372 = Str_lit("Str", 3ULL);
            (void)_t3372;
            U64 _t3373; { U64 *_hp = (U64 *)Str_size(); _t3373 = *_hp; free(_hp); }
            (void)_t3373;
            U64 _t3374 = 8;
            (void)_t3374;
            Array *_va66 = Array_new(_t3372, &(U64){_t3373}, &(U64){_t3374});
            (void)_va66;
            Str_delete(_t3372, &(Bool){1});
            ;
            ;
            U64 _t3375 = 0;
            (void)_t3375;
            Str *_t3376 = Str_clone(&p->path);
            (void)_t3376;
            Array_set(_va66, &(U64){_t3375}, _t3376);
            ;
            U64 _t3377 = 1;
            (void)_t3377;
            Str *_t3378 = Str_lit(":", 1ULL);
            (void)_t3378;
            Array_set(_va66, &(U64){_t3377}, _t3378);
            ;
            U64 _t3379 = 2;
            (void)_t3379;
            Str *_t3380 = U32_to_str(&(U32){kw_line});
            (void)_t3380;
            Array_set(_va66, &(U64){_t3379}, _t3380);
            ;
            U64 _t3381 = 3;
            (void)_t3381;
            Str *_t3382 = Str_lit(":", 1ULL);
            (void)_t3382;
            Array_set(_va66, &(U64){_t3381}, _t3382);
            ;
            U64 _t3383 = 4;
            (void)_t3383;
            Str *_t3384 = U32_to_str(&(U32){kw_col});
            (void)_t3384;
            Array_set(_va66, &(U64){_t3383}, _t3384);
            ;
            U64 _t3385 = 5;
            (void)_t3385;
            Str *_t3386 = Str_lit(": ", 2ULL);
            (void)_t3386;
            Array_set(_va66, &(U64){_t3385}, _t3386);
            ;
            U64 _t3387 = 6;
            (void)_t3387;
            Str *_t3388 = func_type_name(ft);
            (void)_t3388;
            Array_set(_va66, &(U64){_t3387}, _t3388);
            ;
            U64 _t3389 = 7;
            (void)_t3389;
            Str *_t3390 = Str_lit(" requires a body", 16ULL);
            (void)_t3390;
            Array_set(_va66, &(U64){_t3389}, _t3390);
            ;
            Str *_t3391 = Str_lit("src/self/parser.til:253:19", 26ULL);
            (void)_t3391;
            panic(_t3391, _va66);
            Str_delete(_t3391, &(Bool){1});
        }
        ;
    }
    ;
    FuncType_delete(ft, &(Bool){1});
    ;
    ;
    {
        U64 _fi3397 = 0;
        (void)_fi3397;
        while (1) {
            U64 _t3399 = 0;
            (void)_t3399;
            U64 _t3400; { U64 *_hp = (U64 *)Vec_len(def_exprs); _t3400 = *_hp; free(_hp); }
            (void)_t3400;
            Range *_t3401 = Range_new(_t3399, _t3400);
            (void)_t3401;
            ;
            ;
            U64 _t3402; { U64 *_hp = (U64 *)Range_len(_t3401); _t3402 = *_hp; free(_hp); }
            (void)_t3402;
            Range_delete(_t3401, &(Bool){1});
            Bool _wcond3398; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3397}, &(U64){_t3402}); _wcond3398 = *_hp; free(_hp); }
            (void)_wcond3398;
            ;
            if (_wcond3398) {
            } else {
                ;
                break;
            }
            ;
            U64 _t3403 = 0;
            (void)_t3403;
            U64 _t3404; { U64 *_hp = (U64 *)Vec_len(def_exprs); _t3404 = *_hp; free(_hp); }
            (void)_t3404;
            Range *_t3405 = Range_new(_t3403, _t3404);
            (void)_t3405;
            ;
            ;
            U64 *i = Range_get(_t3405, _fi3397);
            (void)i;
            Range_delete(_t3405, &(Bool){1});
            U64 _t3406 = 1;
            (void)_t3406;
            U64 _t3407 = U64_add(_fi3397, _t3406);
            (void)_t3407;
            ;
            _fi3397 = _t3407;
            ;
            Expr *de = Vec_get(def_exprs, i);
            (void)de;
            Expr *_t3408 = Expr_clone(de);
            (void)_t3408;
            U64_delete(i, &(Bool){1});
            Expr_add_child(def, _t3408);
        }
        ;
    }
    Vec_delete(def_exprs, &(Bool){1});
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
    Token *_t3454 = advance(p);
    (void)_t3454;
    Expr *def = Expr_new(ExprData_StructDef(), kw_line, kw_col, &p->path);
    (void)def;
    ;
    ;
    Bool _t3455 = Bool_clone(&(Bool){is_ext});
    (void)_t3455;
    ;
    def->is_ext = _t3455;
    ;
    Token *_t3456 = expect_token(p, TokenType_LBrace());
    (void)_t3456;
    U32 _t3457 = peek_line(p);
    (void)_t3457;
    U32 _t3458 = peek_col(p);
    (void)_t3458;
    Expr *body = Expr_new(ExprData_Body(), _t3457, _t3458, &p->path);
    (void)body;
    ;
    ;
    Bool in_namespace = 0;
    (void)in_namespace;
    while (1) {
        Bool _t3447 = check(p, TokenType_RBrace());
        (void)_t3447;
        Bool _t3448 = check(p, TokenType_Eof());
        (void)_t3448;
        Bool _t3449 = Bool_not(_t3447);
        (void)_t3449;
        ;
        Bool _t3450 = Bool_not(_t3448);
        (void)_t3450;
        ;
        Bool _wcond3441 = Bool_and(_t3449, _t3450);
        (void)_wcond3441;
        ;
        ;
        if (_wcond3441) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3451 = check(p, TokenType_KwNamespace());
        (void)_t3451;
        if (_t3451) {
            Token *_t3442 = advance(p);
            (void)_t3442;
            Token *_t3443 = expect_token(p, TokenType_Colon());
            (void)_t3443;
            Bool _t3444 = 1;
            (void)_t3444;
            in_namespace = _t3444;
            ;
            ;
            continue;
        }
        ;
        Expr *stmt = parse_statement(p);
        (void)stmt;
        Bool _t3452; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3452 = *_hp; free(_hp); }
        (void)_t3452;
        Bool _t3453 = Bool_and(in_namespace, _t3452);
        (void)_t3453;
        ;
        if (_t3453) {
            Bool _t3446; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3446 = *_hp; free(_hp); }
            (void)_t3446;
            if (_t3446) {
                Declaration *dd = ExprData_get_Decl(&stmt->data);
                (void)dd;
                Bool _t3445 = 1;
                (void)_t3445;
                dd->is_namespace = _t3445;
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
    Token *_t3459 = expect_token(p, TokenType_RBrace());
    (void)_t3459;
    Expr_add_child(def, body);
    return def;
}

Expr * parse_enum_def(Parser * p) {
    (void)p;
    U32 kw_line = peek_line(p);
    (void)kw_line;
    U32 kw_col = peek_col(p);
    (void)kw_col;
    Token *_t3483 = advance(p);
    (void)_t3483;
    Expr *def = Expr_new(ExprData_EnumDef(), kw_line, kw_col, &p->path);
    (void)def;
    ;
    ;
    Token *_t3484 = expect_token(p, TokenType_LBrace());
    (void)_t3484;
    U32 _t3485 = peek_line(p);
    (void)_t3485;
    U32 _t3486 = peek_col(p);
    (void)_t3486;
    Expr *body = Expr_new(ExprData_Body(), _t3485, _t3486, &p->path);
    (void)body;
    ;
    ;
    Bool in_namespace = 0;
    (void)in_namespace;
    while (1) {
        Bool _t3478 = check(p, TokenType_RBrace());
        (void)_t3478;
        Bool _t3479 = check(p, TokenType_Eof());
        (void)_t3479;
        Bool _t3480 = Bool_not(_t3478);
        (void)_t3480;
        ;
        Bool _t3481 = Bool_not(_t3479);
        (void)_t3481;
        ;
        Bool _wcond3460 = Bool_and(_t3480, _t3481);
        (void)_wcond3460;
        ;
        ;
        if (_wcond3460) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3482 = check(p, TokenType_KwNamespace());
        (void)_t3482;
        if (_t3482) {
            Token *_t3461 = advance(p);
            (void)_t3461;
            Token *_t3462 = expect_token(p, TokenType_Colon());
            (void)_t3462;
            Bool _t3463 = 1;
            (void)_t3463;
            in_namespace = _t3463;
            ;
            ;
            continue;
        }
        ;
        if (in_namespace) {
            Expr *stmt = parse_statement(p);
            (void)stmt;
            Bool _t3466; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3466 = *_hp; free(_hp); }
            (void)_t3466;
            if (_t3466) {
                Bool _t3465; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3465 = *_hp; free(_hp); }
                (void)_t3465;
                if (_t3465) {
                    Declaration *dd = ExprData_get_Decl(&stmt->data);
                    (void)dd;
                    Bool _t3464 = 1;
                    (void)_t3464;
                    dd->is_namespace = _t3464;
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
            Bool _t3469 = 0;
            (void)_t3469;
            Bool _t3470 = 0;
            (void)_t3470;
            Bool _t3471 = 0;
            (void)_t3471;
            Bool _t3472 = 0;
            (void)_t3472;
            I32 _t3473 = 0;
            (void)_t3473;
            I32 _t3474 = 0;
            (void)_t3474;
            Declaration *dd = malloc(sizeof(Declaration));
            { Str *_ca = Str_clone(vname); dd->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
            dd->is_mut = _t3469;
            dd->is_namespace = _t3470;
            dd->is_ref = _t3471;
            dd->is_own = _t3472;
            dd->field_offset = _t3473;
            dd->field_size = _t3474;
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
            Bool _t3475 = check(p, TokenType_Colon());
            (void)_t3475;
            if (_t3475) {
                Token *_t3467 = advance(p);
                (void)_t3467;
                Str_delete(&dd->explicit_type, &(Bool){0});
                { Str *_fa = expect_text(p, TokenType_Ident()); dd->explicit_type = *_fa; free(_fa); }
            }
            ;
            ExprData *_t3476 = ExprData_Decl(dd);
            (void)_t3476;
            Declaration_delete(dd, &(Bool){1});
            Expr *variant = Expr_new(_t3476, v_line, v_col, &p->path);
            (void)variant;
            ExprData_delete(_t3476, &(Bool){1});
            ;
            ;
            Expr_add_child(body, variant);
            Bool _t3477 = check(p, TokenType_Comma());
            (void)_t3477;
            if (_t3477) {
                Token *_t3468 = advance(p);
                (void)_t3468;
            }
            ;
        }
    }
    ;
    Token *_t3487 = expect_token(p, TokenType_RBrace());
    (void)_t3487;
    Expr_add_child(def, body);
    return def;
}

Expr * parse_call(Parser * p, Str * name, U32 call_line, U32 call_col) {
    (void)p;
    (void)name;
    (void)call_line;
    (void)call_col;
    Token *_t3518 = advance(p);
    (void)_t3518;
    Expr *call = Expr_new(ExprData_FCall(), call_line, call_col, &p->path);
    (void)call;
    Str *_t3519 = Str_clone(name);
    (void)_t3519;
    ExprData *_t3520 = ExprData_Ident(_t3519);
    (void)_t3520;
    Str_delete(_t3519, &(Bool){1});
    Expr *callee = Expr_new(_t3520, call_line, call_col, &p->path);
    (void)callee;
    ExprData_delete(_t3520, &(Bool){1});
    Expr_add_child(call, callee);
    while (1) {
        Bool _t3508 = check(p, TokenType_RParen());
        (void)_t3508;
        Bool _t3509 = check(p, TokenType_Eof());
        (void)_t3509;
        Bool _t3510 = Bool_not(_t3508);
        (void)_t3510;
        ;
        Bool _t3511 = Bool_not(_t3509);
        (void)_t3511;
        ;
        Bool _wcond3488 = Bool_and(_t3510, _t3511);
        (void)_wcond3488;
        ;
        ;
        if (_wcond3488) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3512 = check(p, TokenType_Ident());
        (void)_t3512;
        if (_t3512) {
            U64 _t3499 = 1;
            (void)_t3499;
            U64 _t3500 = U64_add(p->pos, _t3499);
            (void)_t3500;
            ;
            U64 _t3501; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3501 = *_hp; free(_hp); }
            (void)_t3501;
            Bool _t3502; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3500}, &(U64){_t3501}); _t3502 = *_hp; free(_hp); }
            (void)_t3502;
            ;
            ;
            if (_t3502) {
                U64 _t3494 = 1;
                (void)_t3494;
                U64 _t3495 = U64_add(p->pos, _t3494);
                (void)_t3495;
                ;
                I64 _t3496 = U64_to_i64(_t3495);
                (void)_t3496;
                ;
                U64 *_t3497 = malloc(sizeof(U64)); *_t3497 = I64_to_u64(_t3496);
                (void)_t3497;
                ;
                Token *next_tok = Vec_get(&p->tokens, _t3497);
                (void)next_tok;
                Bool _t3498; { Bool *_hp = (Bool *)TokenType_eq(&next_tok->type, TokenType_Eq()); _t3498 = *_hp; free(_hp); }
                (void)_t3498;
                U64_delete(_t3497, &(Bool){1});
                if (_t3498) {
                    U32 na_line = peek_line(p);
                    (void)na_line;
                    U32 na_col = peek_col(p);
                    (void)na_col;
                    Str *aname = expect_text(p, TokenType_Ident());
                    (void)aname;
                    Token *_t3490 = advance(p);
                    (void)_t3490;
                    ExprData *_t3491 = ExprData_NamedArg(aname);
                    (void)_t3491;
                    Str_delete(aname, &(Bool){1});
                    Expr *na = Expr_new(_t3491, na_line, na_col, &p->path);
                    (void)na;
                    ExprData_delete(_t3491, &(Bool){1});
                    ;
                    ;
                    Expr *_t3492 = parse_expression(p);
                    (void)_t3492;
                    Expr_add_child(na, _t3492);
                    Expr_add_child(call, na);
                    Bool _t3493 = check(p, TokenType_Comma());
                    (void)_t3493;
                    if (_t3493) {
                        Token *_t3489 = advance(p);
                        (void)_t3489;
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
        Bool _t3513 = check(p, TokenType_DotDot());
        (void)_t3513;
        if (_t3513) {
            Token *_t3503 = advance(p);
            (void)_t3503;
            Bool _t3504 = 1;
            (void)_t3504;
            is_splat = _t3504;
            ;
        }
        ;
        Bool is_own_arg = 0;
        (void)is_own_arg;
        Bool _t3514 = check(p, TokenType_KwOwn());
        (void)_t3514;
        if (_t3514) {
            Token *_t3505 = advance(p);
            (void)_t3505;
            Bool _t3506 = 1;
            (void)_t3506;
            is_own_arg = _t3506;
            ;
        }
        ;
        Expr *arg = parse_expression(p);
        (void)arg;
        Bool _t3515 = Bool_clone(&(Bool){is_own_arg});
        (void)_t3515;
        ;
        arg->is_own_arg = _t3515;
        ;
        Bool _t3516 = Bool_clone(&(Bool){is_splat});
        (void)_t3516;
        ;
        arg->is_splat = _t3516;
        ;
        Expr_add_child(call, arg);
        Bool _t3517 = check(p, TokenType_Comma());
        (void)_t3517;
        if (_t3517) {
            Token *_t3507 = advance(p);
            (void)_t3507;
        }
        ;
    }
    Token *_t3521 = expect_token(p, TokenType_RParen());
    (void)_t3521;
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
    U32 _t3707 = 0;
    (void)_t3707;
    U32 _t3708 = 0;
    (void)_t3708;
    Expr *e = Expr_new(ExprData_Body(), _t3707, _t3708, &p->path);
    (void)e;
    ;
    ;
    Bool e_set = 0;
    (void)e_set;
    Bool _t3709; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t3709 = *_hp; free(_hp); }
    (void)_t3709;
    if (_t3709) {
        Token *_t3522 = advance(p);
        (void)_t3522;
        Str *_t3523 = Str_clone(&t->text);
        (void)_t3523;
        ExprData *_t3524 = ExprData_LiteralStr(_t3523);
        (void)_t3524;
        Str_delete(_t3523, &(Bool){1});
        e = Expr_new(_t3524, t_line, t_col, &p->path);
        ExprData_delete(_t3524, &(Bool){1});
        Bool _t3525 = 1;
        (void)_t3525;
        e_set = _t3525;
        ;
    }
    ;
    Bool _t3710 = Bool_not(e_set);
    (void)_t3710;
    Bool _t3711; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t3711 = *_hp; free(_hp); }
    (void)_t3711;
    Bool _t3712 = Bool_and(_t3710, _t3711);
    (void)_t3712;
    ;
    ;
    if (_t3712) {
        Token *_t3526 = advance(p);
        (void)_t3526;
        Str *_t3527 = Str_clone(&t->text);
        (void)_t3527;
        ExprData *_t3528 = ExprData_LiteralNum(_t3527);
        (void)_t3528;
        Str_delete(_t3527, &(Bool){1});
        e = Expr_new(_t3528, t_line, t_col, &p->path);
        ExprData_delete(_t3528, &(Bool){1});
        Bool _t3529 = 1;
        (void)_t3529;
        e_set = _t3529;
        ;
    }
    ;
    Bool _t3713 = Bool_not(e_set);
    (void)_t3713;
    Bool _t3714; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Char()); _t3714 = *_hp; free(_hp); }
    (void)_t3714;
    Bool _t3715 = Bool_and(_t3713, _t3714);
    (void)_t3715;
    ;
    ;
    if (_t3715) {
        Token *_t3559 = advance(p);
        (void)_t3559;
        Str *ch = Str_clone(&t->text);
        (void)ch;
        I64 byte_val = 0;
        (void)byte_val;
        U64 _t3560; { U64 *_hp = (U64 *)Str_len(ch); _t3560 = *_hp; free(_hp); }
        (void)_t3560;
        U64 _t3561 = 0;
        (void)_t3561;
        U64 *_t3562 = malloc(sizeof(U64));
        *_t3562 = 0;
        (void)_t3562;
        U8 *_t3563 = Str_get(ch, _t3562);
        (void)_t3563;
        U8 _t3564 = 92;
        (void)_t3564;
        Bool _t3565; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3560}, &(U64){_t3561}); _t3565 = *_hp; free(_hp); }
        (void)_t3565;
        ;
        ;
        Bool _t3566 = U8_eq(DEREF(_t3563), _t3564);
        (void)_t3566;
        U64_delete(_t3562, &(Bool){1});
        ;
        Bool _t3567 = Bool_and(_t3565, _t3566);
        (void)_t3567;
        ;
        ;
        if (_t3567) {
            U64 _t3550; { U64 *_hp = (U64 *)Str_len(ch); _t3550 = *_hp; free(_hp); }
            (void)_t3550;
            U64 _t3551 = 1;
            (void)_t3551;
            Bool _t3552; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3550}, &(U64){_t3551}); _t3552 = *_hp; free(_hp); }
            (void)_t3552;
            ;
            ;
            if (_t3552) {
                U64 *_t3547 = malloc(sizeof(U64));
                *_t3547 = 1;
                (void)_t3547;
                U8 *c2 = Str_get(ch, _t3547);
                (void)c2;
                U8 _t3548 = 110;
                (void)_t3548;
                Bool _t3549 = U8_eq(DEREF(c2), _t3548);
                (void)_t3549;
                ;
                if (_t3549) {
                    I64 _t3530 = 10;
                    (void)_t3530;
                    byte_val = _t3530;
                    ;
                } else {
                    U8 _t3545 = 116;
                    (void)_t3545;
                    Bool _t3546 = U8_eq(DEREF(c2), _t3545);
                    (void)_t3546;
                    ;
                    if (_t3546) {
                        I64 _t3531 = 9;
                        (void)_t3531;
                        byte_val = _t3531;
                        ;
                    } else {
                        U8 _t3543 = 114;
                        (void)_t3543;
                        Bool _t3544 = U8_eq(DEREF(c2), _t3543);
                        (void)_t3544;
                        ;
                        if (_t3544) {
                            I64 _t3532 = 13;
                            (void)_t3532;
                            byte_val = _t3532;
                            ;
                        } else {
                            U8 _t3541 = 92;
                            (void)_t3541;
                            Bool _t3542 = U8_eq(DEREF(c2), _t3541);
                            (void)_t3542;
                            ;
                            if (_t3542) {
                                I64 _t3533 = 92;
                                (void)_t3533;
                                byte_val = _t3533;
                                ;
                            } else {
                                U8 _t3539 = 39;
                                (void)_t3539;
                                Bool _t3540 = U8_eq(DEREF(c2), _t3539);
                                (void)_t3540;
                                ;
                                if (_t3540) {
                                    I64 _t3534 = 39;
                                    (void)_t3534;
                                    byte_val = _t3534;
                                    ;
                                } else {
                                    U8 _t3537 = 48;
                                    (void)_t3537;
                                    Bool _t3538 = U8_eq(DEREF(c2), _t3537);
                                    (void)_t3538;
                                    ;
                                    if (_t3538) {
                                        I64 _t3535 = 0;
                                        (void)_t3535;
                                        byte_val = _t3535;
                                        ;
                                    } else {
                                        I64 _t3536 = U8_to_i64(DEREF(c2));
                                        (void)_t3536;
                                        byte_val = _t3536;
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
                U64_delete(_t3547, &(Bool){1});
                ;
            }
            ;
        } else {
            U64 _t3556; { U64 *_hp = (U64 *)Str_len(ch); _t3556 = *_hp; free(_hp); }
            (void)_t3556;
            U64 _t3557 = 0;
            (void)_t3557;
            Bool _t3558; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3556}, &(U64){_t3557}); _t3558 = *_hp; free(_hp); }
            (void)_t3558;
            ;
            ;
            if (_t3558) {
                U64 *_t3553 = malloc(sizeof(U64));
                *_t3553 = 0;
                (void)_t3553;
                U8 *_t3554 = Str_get(ch, _t3553);
                (void)_t3554;
                I64 _t3555 = U8_to_i64(DEREF(_t3554));
                (void)_t3555;
                U64_delete(_t3553, &(Bool){1});
                byte_val = _t3555;
                ;
            }
            ;
        }
        ;
        Str_delete(ch, &(Bool){1});
        Str *_t3568 = I64_to_str(&(I64){byte_val});
        (void)_t3568;
        ;
        ExprData *_t3569 = ExprData_LiteralNum(_t3568);
        (void)_t3569;
        Str_delete(_t3568, &(Bool){1});
        e = Expr_new(_t3569, t_line, t_col, &p->path);
        ExprData_delete(_t3569, &(Bool){1});
        TilType_delete(&e->til_type, &(Bool){0});
        { TilType *_fa = TilType_clone(TilType_U8()); e->til_type = *_fa; free(_fa); }
        Bool _t3570 = 1;
        (void)_t3570;
        e_set = _t3570;
        ;
    }
    ;
    Bool _t3716; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t3716 = *_hp; free(_hp); }
    (void)_t3716;
    Bool _t3717; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t3717 = *_hp; free(_hp); }
    (void)_t3717;
    Bool _t3718 = Bool_not(e_set);
    (void)_t3718;
    Bool _t3719 = Bool_or(_t3716, _t3717);
    (void)_t3719;
    ;
    ;
    Bool _t3720 = Bool_and(_t3718, _t3719);
    (void)_t3720;
    ;
    ;
    if (_t3720) {
        Token *_t3571 = advance(p);
        (void)_t3571;
        Str *_t3572 = Str_clone(&t->text);
        (void)_t3572;
        ExprData *_t3573 = ExprData_LiteralBool(_t3572);
        (void)_t3573;
        Str_delete(_t3572, &(Bool){1});
        e = Expr_new(_t3573, t_line, t_col, &p->path);
        ExprData_delete(_t3573, &(Bool){1});
        Bool _t3574 = 1;
        (void)_t3574;
        e_set = _t3574;
        ;
    }
    ;
    Bool _t3721 = Bool_not(e_set);
    (void)_t3721;
    Bool _t3722; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t3722 = *_hp; free(_hp); }
    (void)_t3722;
    Bool _t3723 = Bool_and(_t3721, _t3722);
    (void)_t3723;
    ;
    ;
    if (_t3723) {
        Token *_t3610 = advance(p);
        (void)_t3610;
        Str *name = Str_clone(&t->text);
        (void)name;
        Str *_t3611 = Str_lit("__LOC__", 7ULL);
        (void)_t3611;
        Bool _t3612; { Bool *_hp = (Bool *)Str_eq(name, _t3611); _t3612 = *_hp; free(_hp); }
        (void)_t3612;
        Str_delete(_t3611, &(Bool){1});
        if (_t3612) {
            Str *_t3575 = Str_lit("Str", 3ULL);
            (void)_t3575;
            U64 _t3576; { U64 *_hp = (U64 *)Str_size(); _t3576 = *_hp; free(_hp); }
            (void)_t3576;
            U64 _t3577 = 5;
            (void)_t3577;
            Array *_va67 = Array_new(_t3575, &(U64){_t3576}, &(U64){_t3577});
            (void)_va67;
            Str_delete(_t3575, &(Bool){1});
            ;
            ;
            U64 _t3578 = 0;
            (void)_t3578;
            Str *_t3579 = Str_clone(&p->path);
            (void)_t3579;
            Array_set(_va67, &(U64){_t3578}, _t3579);
            ;
            U64 _t3580 = 1;
            (void)_t3580;
            Str *_t3581 = Str_lit(":", 1ULL);
            (void)_t3581;
            Array_set(_va67, &(U64){_t3580}, _t3581);
            ;
            U64 _t3582 = 2;
            (void)_t3582;
            Str *_t3583 = U32_to_str(&(U32){t_line});
            (void)_t3583;
            Array_set(_va67, &(U64){_t3582}, _t3583);
            ;
            U64 _t3584 = 3;
            (void)_t3584;
            Str *_t3585 = Str_lit(":", 1ULL);
            (void)_t3585;
            Array_set(_va67, &(U64){_t3584}, _t3585);
            ;
            U64 _t3586 = 4;
            (void)_t3586;
            Str *_t3587 = U32_to_str(&(U32){t_col});
            (void)_t3587;
            Array_set(_va67, &(U64){_t3586}, _t3587);
            ;
            Str *_t3588 = format(_va67);
            (void)_t3588;
            ExprData *_t3589 = ExprData_LiteralStr(_t3588);
            (void)_t3589;
            Str_delete(_t3588, &(Bool){1});
            e = Expr_new(_t3589, t_line, t_col, &p->path);
            ExprData_delete(_t3589, &(Bool){1});
            Bool _t3590 = 1;
            (void)_t3590;
            e_set = _t3590;
            ;
        } else {
            Str *_t3608 = Str_lit("__FILE__", 8ULL);
            (void)_t3608;
            Bool _t3609; { Bool *_hp = (Bool *)Str_eq(name, _t3608); _t3609 = *_hp; free(_hp); }
            (void)_t3609;
            Str_delete(_t3608, &(Bool){1});
            if (_t3609) {
                Str *_t3591 = Str_clone(&p->path);
                (void)_t3591;
                ExprData *_t3592 = ExprData_LiteralStr(_t3591);
                (void)_t3592;
                Str_delete(_t3591, &(Bool){1});
                e = Expr_new(_t3592, t_line, t_col, &p->path);
                ExprData_delete(_t3592, &(Bool){1});
                Bool _t3593 = 1;
                (void)_t3593;
                e_set = _t3593;
                ;
            } else {
                Str *_t3606 = Str_lit("__LINE__", 8ULL);
                (void)_t3606;
                Bool _t3607; { Bool *_hp = (Bool *)Str_eq(name, _t3606); _t3607 = *_hp; free(_hp); }
                (void)_t3607;
                Str_delete(_t3606, &(Bool){1});
                if (_t3607) {
                    Str *_t3594 = U32_to_str(&(U32){t_line});
                    (void)_t3594;
                    ExprData *_t3595 = ExprData_LiteralNum(_t3594);
                    (void)_t3595;
                    Str_delete(_t3594, &(Bool){1});
                    e = Expr_new(_t3595, t_line, t_col, &p->path);
                    ExprData_delete(_t3595, &(Bool){1});
                    Bool _t3596 = 1;
                    (void)_t3596;
                    e_set = _t3596;
                    ;
                } else {
                    Str *_t3604 = Str_lit("__COL__", 7ULL);
                    (void)_t3604;
                    Bool _t3605; { Bool *_hp = (Bool *)Str_eq(name, _t3604); _t3605 = *_hp; free(_hp); }
                    (void)_t3605;
                    Str_delete(_t3604, &(Bool){1});
                    if (_t3605) {
                        Str *_t3597 = U32_to_str(&(U32){t_col});
                        (void)_t3597;
                        ExprData *_t3598 = ExprData_LiteralNum(_t3597);
                        (void)_t3598;
                        Str_delete(_t3597, &(Bool){1});
                        e = Expr_new(_t3598, t_line, t_col, &p->path);
                        ExprData_delete(_t3598, &(Bool){1});
                        Bool _t3599 = 1;
                        (void)_t3599;
                        e_set = _t3599;
                        ;
                    } else {
                        Bool _t3603 = check(p, TokenType_LParen());
                        (void)_t3603;
                        if (_t3603) {
                            e = parse_call(p, name, t_line, t_col);
                            Bool _t3600 = 1;
                            (void)_t3600;
                            e_set = _t3600;
                            ;
                        } else {
                            ExprData *_t3601 = ExprData_Ident(name);
                            (void)_t3601;
                            e = Expr_new(_t3601, t_line, t_col, &p->path);
                            ExprData_delete(_t3601, &(Bool){1});
                            Bool _t3602 = 1;
                            (void)_t3602;
                            e_set = _t3602;
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
    Bool _t3724; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFunc()); _t3724 = *_hp; free(_hp); }
    (void)_t3724;
    Bool _t3725; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwProc()); _t3725 = *_hp; free(_hp); }
    (void)_t3725;
    Bool _t3726 = Bool_or(_t3724, _t3725);
    (void)_t3726;
    ;
    ;
    Bool _t3727; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTest()); _t3727 = *_hp; free(_hp); }
    (void)_t3727;
    Bool _t3728 = Bool_or(_t3726, _t3727);
    (void)_t3728;
    ;
    ;
    Bool _t3729; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMacro()); _t3729 = *_hp; free(_hp); }
    (void)_t3729;
    Bool _t3730 = Bool_or(_t3728, _t3729);
    (void)_t3730;
    ;
    ;
    Bool _t3731; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtFunc()); _t3731 = *_hp; free(_hp); }
    (void)_t3731;
    Bool _t3732 = Bool_or(_t3730, _t3731);
    (void)_t3732;
    ;
    ;
    Bool _t3733; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtProc()); _t3733 = *_hp; free(_hp); }
    (void)_t3733;
    Bool _t3734 = Bool_not(e_set);
    (void)_t3734;
    Bool _t3735 = Bool_or(_t3732, _t3733);
    (void)_t3735;
    ;
    ;
    Bool _t3736 = Bool_and(_t3734, _t3735);
    (void)_t3736;
    ;
    ;
    if (_t3736) {
        Expr *_t3613 = parse_func_def(p);
        (void)_t3613;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3613;
    }
    ;
    Bool _t3737; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwStruct()); _t3737 = *_hp; free(_hp); }
    (void)_t3737;
    Bool _t3738; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtStruct()); _t3738 = *_hp; free(_hp); }
    (void)_t3738;
    Bool _t3739 = Bool_not(e_set);
    (void)_t3739;
    Bool _t3740 = Bool_or(_t3737, _t3738);
    (void)_t3740;
    ;
    ;
    Bool _t3741 = Bool_and(_t3739, _t3740);
    (void)_t3741;
    ;
    ;
    if (_t3741) {
        Expr *_t3614 = parse_struct_def(p);
        (void)_t3614;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3614;
    }
    ;
    Bool _t3742 = Bool_not(e_set);
    (void)_t3742;
    Bool _t3743; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwEnum()); _t3743 = *_hp; free(_hp); }
    (void)_t3743;
    Bool _t3744 = Bool_and(_t3742, _t3743);
    (void)_t3744;
    ;
    ;
    if (_t3744) {
        Expr *_t3615 = parse_enum_def(p);
        (void)_t3615;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3615;
    }
    ;
    Bool _t3745 = Bool_not(e_set);
    (void)_t3745;
    Bool _t3746; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t3746 = *_hp; free(_hp); }
    (void)_t3746;
    Bool _t3747 = Bool_and(_t3745, _t3746);
    (void)_t3747;
    ;
    ;
    if (_t3747) {
        Token *_t3640 = advance(p);
        (void)_t3640;
        Expr *first = parse_expression(p);
        (void)first;
        Bool _t3641 = check(p, TokenType_Colon());
        (void)_t3641;
        if (_t3641) {
            e = Expr_new(ExprData_MapLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Token *_t3627 = advance(p);
            (void)_t3627;
            Expr *_t3628 = parse_expression(p);
            (void)_t3628;
            Expr_add_child(e, _t3628);
            Bool _t3629 = check(p, TokenType_Comma());
            (void)_t3629;
            if (_t3629) {
                Token *_t3616 = advance(p);
                (void)_t3616;
            }
            ;
            while (1) {
                Bool _t3619 = check(p, TokenType_RBrace());
                (void)_t3619;
                Bool _t3620 = check(p, TokenType_Eof());
                (void)_t3620;
                Bool _t3621 = Bool_not(_t3619);
                (void)_t3621;
                ;
                Bool _t3622 = Bool_not(_t3620);
                (void)_t3622;
                ;
                Bool _wcond3617 = Bool_and(_t3621, _t3622);
                (void)_wcond3617;
                ;
                ;
                if (_wcond3617) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3623 = parse_expression(p);
                (void)_t3623;
                Expr_add_child(e, _t3623);
                Token *_t3624 = expect_token(p, TokenType_Colon());
                (void)_t3624;
                Expr *_t3625 = parse_expression(p);
                (void)_t3625;
                Expr_add_child(e, _t3625);
                Bool _t3626 = check(p, TokenType_Comma());
                (void)_t3626;
                if (_t3626) {
                    Token *_t3618 = advance(p);
                    (void)_t3618;
                }
                ;
            }
        } else {
            e = Expr_new(ExprData_SetLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Bool _t3639 = check(p, TokenType_Comma());
            (void)_t3639;
            if (_t3639) {
                Token *_t3630 = advance(p);
                (void)_t3630;
            }
            ;
            while (1) {
                Bool _t3633 = check(p, TokenType_RBrace());
                (void)_t3633;
                Bool _t3634 = check(p, TokenType_Eof());
                (void)_t3634;
                Bool _t3635 = Bool_not(_t3633);
                (void)_t3635;
                ;
                Bool _t3636 = Bool_not(_t3634);
                (void)_t3636;
                ;
                Bool _wcond3631 = Bool_and(_t3635, _t3636);
                (void)_wcond3631;
                ;
                ;
                if (_wcond3631) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3637 = parse_expression(p);
                (void)_t3637;
                Expr_add_child(e, _t3637);
                Bool _t3638 = check(p, TokenType_Comma());
                (void)_t3638;
                if (_t3638) {
                    Token *_t3632 = advance(p);
                    (void)_t3632;
                }
                ;
            }
        }
        ;
        Token *_t3642 = expect_token(p, TokenType_RBrace());
        (void)_t3642;
        Bool _t3643 = 1;
        (void)_t3643;
        e_set = _t3643;
        ;
    }
    ;
    Bool _t3748 = Bool_not(e_set);
    (void)_t3748;
    ;
    if (_t3748) {
        Str *_t3644 = Str_lit("Str", 3ULL);
        (void)_t3644;
        U64 _t3645; { U64 *_hp = (U64 *)Str_size(); _t3645 = *_hp; free(_hp); }
        (void)_t3645;
        U64 _t3646 = 8;
        (void)_t3646;
        Array *_va68 = Array_new(_t3644, &(U64){_t3645}, &(U64){_t3646});
        (void)_va68;
        Str_delete(_t3644, &(Bool){1});
        ;
        ;
        U64 _t3647 = 0;
        (void)_t3647;
        Str *_t3648 = Str_clone(&p->path);
        (void)_t3648;
        Array_set(_va68, &(U64){_t3647}, _t3648);
        ;
        U64 _t3649 = 1;
        (void)_t3649;
        Str *_t3650 = Str_lit(":", 1ULL);
        (void)_t3650;
        Array_set(_va68, &(U64){_t3649}, _t3650);
        ;
        U64 _t3651 = 2;
        (void)_t3651;
        Str *_t3652 = U32_to_str(&(U32){t_line});
        (void)_t3652;
        Array_set(_va68, &(U64){_t3651}, _t3652);
        ;
        U64 _t3653 = 3;
        (void)_t3653;
        Str *_t3654 = Str_lit(":", 1ULL);
        (void)_t3654;
        Array_set(_va68, &(U64){_t3653}, _t3654);
        ;
        U64 _t3655 = 4;
        (void)_t3655;
        Str *_t3656 = U32_to_str(&(U32){t_col});
        (void)_t3656;
        Array_set(_va68, &(U64){_t3655}, _t3656);
        ;
        U64 _t3657 = 5;
        (void)_t3657;
        Str *_t3658 = Str_lit(": unexpected token '", 20ULL);
        (void)_t3658;
        Array_set(_va68, &(U64){_t3657}, _t3658);
        ;
        U64 _t3659 = 6;
        (void)_t3659;
        Str *_t3660 = Str_clone(&t->text);
        (void)_t3660;
        Array_set(_va68, &(U64){_t3659}, _t3660);
        ;
        U64 _t3661 = 7;
        (void)_t3661;
        Str *_t3662 = Str_lit("'", 1ULL);
        (void)_t3662;
        Array_set(_va68, &(U64){_t3661}, _t3662);
        ;
        Str *_t3663 = Str_lit("src/self/parser.til:513:15", 26ULL);
        (void)_t3663;
        panic(_t3663, _va68);
        Str_delete(_t3663, &(Bool){1});
    }
    ;
    ;
    ;
    while (1) {
        Bool _wcond3664 = check(p, TokenType_Dot());
        (void)_wcond3664;
        if (_wcond3664) {
        } else {
            ;
            break;
        }
        ;
        Token *_t3697 = advance(p);
        (void)_t3697;
        U32 f_line = peek_line(p);
        (void)f_line;
        U32 f_col = peek_col(p);
        (void)f_col;
        Str *fname = expect_text(p, TokenType_Ident());
        (void)fname;
        Bool _t3698 = check(p, TokenType_LParen());
        (void)_t3698;
        if (_t3698) {
            Token *_t3691 = advance(p);
            (void)_t3691;
            ExprData *_t3692 = ExprData_FieldAccess(fname);
            (void)_t3692;
            Expr *callee = Expr_new(_t3692, f_line, f_col, &p->path);
            (void)callee;
            ExprData_delete(_t3692, &(Bool){1});
            Expr *_t3693 = Expr_clone(e);
            (void)_t3693;
            Expr_add_child(callee, _t3693);
            Expr *mcall = Expr_new(ExprData_FCall(), f_line, f_col, &p->path);
            (void)mcall;
            Expr_add_child(mcall, callee);
            while (1) {
                Bool _t3683 = check(p, TokenType_RParen());
                (void)_t3683;
                Bool _t3684 = check(p, TokenType_Eof());
                (void)_t3684;
                Bool _t3685 = Bool_not(_t3683);
                (void)_t3685;
                ;
                Bool _t3686 = Bool_not(_t3684);
                (void)_t3686;
                ;
                Bool _wcond3665 = Bool_and(_t3685, _t3686);
                (void)_wcond3665;
                ;
                ;
                if (_wcond3665) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3687 = check(p, TokenType_Ident());
                (void)_t3687;
                if (_t3687) {
                    U64 _t3676 = 1;
                    (void)_t3676;
                    U64 _t3677 = U64_add(p->pos, _t3676);
                    (void)_t3677;
                    ;
                    U64 _t3678; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3678 = *_hp; free(_hp); }
                    (void)_t3678;
                    Bool _t3679; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3677}, &(U64){_t3678}); _t3679 = *_hp; free(_hp); }
                    (void)_t3679;
                    ;
                    ;
                    if (_t3679) {
                        U64 _t3671 = 1;
                        (void)_t3671;
                        U64 _t3672 = U64_add(p->pos, _t3671);
                        (void)_t3672;
                        ;
                        I64 _t3673 = U64_to_i64(_t3672);
                        (void)_t3673;
                        ;
                        U64 *_t3674 = malloc(sizeof(U64)); *_t3674 = I64_to_u64(_t3673);
                        (void)_t3674;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3674);
                        (void)nt;
                        Bool _t3675; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3675 = *_hp; free(_hp); }
                        (void)_t3675;
                        U64_delete(_t3674, &(Bool){1});
                        if (_t3675) {
                            U32 na_line = peek_line(p);
                            (void)na_line;
                            U32 na_col = peek_col(p);
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3667 = advance(p);
                            (void)_t3667;
                            ExprData *_t3668 = ExprData_NamedArg(aname);
                            (void)_t3668;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3668, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3668, &(Bool){1});
                            ;
                            ;
                            Expr *_t3669 = parse_expression(p);
                            (void)_t3669;
                            Expr_add_child(na, _t3669);
                            Expr_add_child(mcall, na);
                            Bool _t3670 = check(p, TokenType_Comma());
                            (void)_t3670;
                            if (_t3670) {
                                Token *_t3666 = advance(p);
                                (void)_t3666;
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
                Bool _t3688 = check(p, TokenType_KwOwn());
                (void)_t3688;
                if (_t3688) {
                    Token *_t3680 = advance(p);
                    (void)_t3680;
                    Bool _t3681 = 1;
                    (void)_t3681;
                    is_own_arg = _t3681;
                    ;
                }
                ;
                Expr *marg = parse_expression(p);
                (void)marg;
                Bool _t3689 = Bool_clone(&(Bool){is_own_arg});
                (void)_t3689;
                ;
                marg->is_own_arg = _t3689;
                ;
                Expr_add_child(mcall, marg);
                Bool _t3690 = check(p, TokenType_Comma());
                (void)_t3690;
                if (_t3690) {
                    Token *_t3682 = advance(p);
                    (void)_t3682;
                }
                ;
            }
            Token *_t3694 = expect_token(p, TokenType_RParen());
            (void)_t3694;
            e = Expr_clone(mcall);
            Expr_delete(mcall, &(Bool){1});
        } else {
            ExprData *_t3695 = ExprData_FieldAccess(fname);
            (void)_t3695;
            Expr *access = Expr_new(_t3695, f_line, f_col, &p->path);
            (void)access;
            ExprData_delete(_t3695, &(Bool){1});
            Expr *_t3696 = Expr_clone(e);
            (void)_t3696;
            Expr_add_child(access, _t3696);
            e = Expr_clone(access);
            Expr_delete(access, &(Bool){1});
        }
        ;
        ;
        ;
        Str_delete(fname, &(Bool){1});
    }
    Bool _t3749 = check(p, TokenType_DotDot());
    (void)_t3749;
    if (_t3749) {
        U32 dt_line = peek_line(p);
        (void)dt_line;
        U32 dt_col = peek_col(p);
        (void)dt_col;
        Token *_t3699 = advance(p);
        (void)_t3699;
        Expr *rhs = parse_expression(p);
        (void)rhs;
        Str *_t3700 = Str_lit("Range", 5ULL);
        (void)_t3700;
        Str *_t3701 = Str_clone(_t3700);
        (void)_t3701;
        Str_delete(_t3700, &(Bool){1});
        ExprData *_t3702 = ExprData_Ident(_t3701);
        (void)_t3702;
        Str_delete(_t3701, &(Bool){1});
        Expr *range_ident = Expr_new(_t3702, dt_line, dt_col, &p->path);
        (void)range_ident;
        ExprData_delete(_t3702, &(Bool){1});
        Str *_t3703 = Str_lit("new", 3ULL);
        (void)_t3703;
        Str *_t3704 = Str_clone(_t3703);
        (void)_t3704;
        Str_delete(_t3703, &(Bool){1});
        ExprData *_t3705 = ExprData_FieldAccess(_t3704);
        (void)_t3705;
        Str_delete(_t3704, &(Bool){1});
        Expr *new_access = Expr_new(_t3705, dt_line, dt_col, &p->path);
        (void)new_access;
        ExprData_delete(_t3705, &(Bool){1});
        Expr_add_child(new_access, range_ident);
        Expr *rcall = Expr_new(ExprData_FCall(), dt_line, dt_col, &p->path);
        (void)rcall;
        ;
        ;
        Expr_add_child(rcall, new_access);
        Expr *_t3706 = Expr_clone(e);
        (void)_t3706;
        Expr_add_child(rcall, _t3706);
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
    Bool _t3950 = check(p, TokenType_ColonEq());
    (void)_t3950;
    if (_t3950) {
        Token *_t3750 = advance(p);
        (void)_t3750;
        Bool _t3751 = Bool_clone(&(Bool){is_mut});
        (void)_t3751;
        Bool _t3752 = 0;
        (void)_t3752;
        Bool _t3753 = 0;
        (void)_t3753;
        Bool _t3754 = Bool_clone(&(Bool){is_own});
        (void)_t3754;
        I32 _t3755 = 0;
        (void)_t3755;
        I32 _t3756 = 0;
        (void)_t3756;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3751;
        dd->is_namespace = _t3752;
        dd->is_ref = _t3753;
        dd->is_own = _t3754;
        dd->field_offset = _t3755;
        dd->field_size = _t3756;
        dd->field_struct_def = NULL;
        dd->fn_sig = NULL;
        (void)dd;
        ;
        ;
        ;
        ;
        ;
        ;
        ExprData *_t3757 = ExprData_Decl(dd);
        (void)_t3757;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3757, t_line, t_col, &p->path);
        (void)decl;
        ExprData_delete(_t3757, &(Bool){1});
        Expr *_t3758 = parse_expression(p);
        (void)_t3758;
        Expr_add_child(decl, _t3758);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return decl;
    }
    ;
    Bool _t3951 = check(p, TokenType_Colon());
    (void)_t3951;
    if (_t3951) {
        Token *_t3882 = advance(p);
        (void)_t3882;
        Bool _t3883 = check(p, TokenType_KwFunc());
        (void)_t3883;
        Bool _t3884 = check(p, TokenType_KwProc());
        (void)_t3884;
        Bool _t3885 = Bool_or(_t3883, _t3884);
        (void)_t3885;
        ;
        ;
        if (_t3885) {
            Expr *sig = parse_func_def(p);
            (void)sig;
            Token *_t3776 = expect_token(p, TokenType_Eq());
            (void)_t3776;
            Token *_t3777 = expect_token(p, TokenType_LParen());
            (void)_t3777;
            Bool _t3778; { Bool *_hp = (Bool *)ExprData_is_FuncDef(&sig->data); _t3778 = *_hp; free(_hp); }
            (void)_t3778;
            if (_t3778) {
                FunctionDef *sfd = ExprData_get_FuncDef(&sig->data);
                (void)sfd;
                Str *_t3773 = Str_lit("Str", 3ULL);
                (void)_t3773;
                U64 _t3774; { U64 *_hp = (U64 *)Str_size(); _t3774 = *_hp; free(_hp); }
                (void)_t3774;
                Vec *new_names = Vec_new(_t3773, &(U64){_t3774});
                (void)new_names;
                Str_delete(_t3773, &(Bool){1});
                ;
                {
                    U64 _fi3759 = 0;
                    (void)_fi3759;
                    while (1) {
                        U64 _t3762 = 0;
                        (void)_t3762;
                        U64 _t3763; { U64 *_hp = (U64 *)Vec_len(&sfd->param_names); _t3763 = *_hp; free(_hp); }
                        (void)_t3763;
                        Range *_t3764 = Range_new(_t3762, _t3763);
                        (void)_t3764;
                        ;
                        ;
                        U64 _t3765; { U64 *_hp = (U64 *)Range_len(_t3764); _t3765 = *_hp; free(_hp); }
                        (void)_t3765;
                        Range_delete(_t3764, &(Bool){1});
                        Bool _wcond3760; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3759}, &(U64){_t3765}); _wcond3760 = *_hp; free(_hp); }
                        (void)_wcond3760;
                        ;
                        if (_wcond3760) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 _t3766 = 0;
                        (void)_t3766;
                        U64 _t3767; { U64 *_hp = (U64 *)Vec_len(&sfd->param_names); _t3767 = *_hp; free(_hp); }
                        (void)_t3767;
                        Range *_t3768 = Range_new(_t3766, _t3767);
                        (void)_t3768;
                        ;
                        ;
                        U64 pi; { U64 *_hp = (U64 *)Range_get(_t3768, _fi3759); pi = *_hp; free(_hp); }
                        (void)pi;
                        Range_delete(_t3768, &(Bool){1});
                        U64 _t3769 = 1;
                        (void)_t3769;
                        U64 _t3770 = U64_add(_fi3759, _t3769);
                        (void)_t3770;
                        ;
                        _fi3759 = _t3770;
                        ;
                        U64 _t3771 = 0;
                        (void)_t3771;
                        Bool _t3772; { Bool *_hp = (Bool *)U64_gt(&(U64){pi}, &(U64){_t3771}); _t3772 = *_hp; free(_hp); }
                        (void)_t3772;
                        ;
                        ;
                        if (_t3772) {
                            Token *_t3761 = expect_token(p, TokenType_Comma());
                            (void)_t3761;
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
            Bool _t3779 = check(p, TokenType_Comma());
            (void)_t3779;
            if (_t3779) {
                Token *_t3775 = advance(p);
                (void)_t3775;
            }
            ;
            Token *_t3780 = expect_token(p, TokenType_RParen());
            (void)_t3780;
            Token *_t3781 = expect_token(p, TokenType_LBrace());
            (void)_t3781;
            Expr *_t3782 = parse_block(p);
            (void)_t3782;
            Expr_add_child(sig, _t3782);
            Bool _t3783 = Bool_clone(&(Bool){is_mut});
            (void)_t3783;
            Bool _t3784 = 0;
            (void)_t3784;
            Bool _t3785 = 0;
            (void)_t3785;
            Bool _t3786 = Bool_clone(&(Bool){is_own});
            (void)_t3786;
            I32 _t3787 = 0;
            (void)_t3787;
            I32 _t3788 = 0;
            (void)_t3788;
            Declaration *dd = malloc(sizeof(Declaration));
            { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
            dd->is_mut = _t3783;
            dd->is_namespace = _t3784;
            dd->is_ref = _t3785;
            dd->is_own = _t3786;
            dd->field_offset = _t3787;
            dd->field_size = _t3788;
            dd->field_struct_def = NULL;
            dd->fn_sig = NULL;
            (void)dd;
            ;
            ;
            ;
            ;
            ;
            ;
            ExprData *_t3789 = ExprData_Decl(dd);
            (void)_t3789;
            Declaration_delete(dd, &(Bool){1});
            Expr *decl = Expr_new(_t3789, t_line, t_col, &p->path);
            (void)decl;
            ExprData_delete(_t3789, &(Bool){1});
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
        I64 _t3886 = 0;
        (void)_t3886;
        I64 _t3887 = 1;
        (void)_t3887;
        I64 fn_sig_idx = I64_sub(_t3886, _t3887);
        (void)fn_sig_idx;
        ;
        ;
        Str *_t3888 = Str_lit("Fn", 2ULL);
        (void)_t3888;
        Bool _t3889; { Bool *_hp = (Bool *)Str_eq(type_name, _t3888); _t3889 = *_hp; free(_hp); }
        (void)_t3889;
        Str_delete(_t3888, &(Bool){1});
        if (_t3889) {
            Expr *sig = parse_fn_signature(p, t_line, t_col);
            (void)sig;
            U32 _t3791 = 0;
            (void)_t3791;
            Bool _t3792; { Bool *_hp = (Bool *)U32_neq(&sig->line, &(U32){_t3791}); _t3792 = *_hp; free(_hp); }
            (void)_t3792;
            ;
            Expr_delete(sig, &(Bool){1});
            if (_t3792) {
                I64 _t3790 = 0;
                (void)_t3790;
                fn_sig_idx = _t3790;
                ;
            }
            ;
        }
        ;
        ;
        Token *_t3890 = expect_token(p, TokenType_Eq());
        (void)_t3890;
        Bool _t3891 = check(p, TokenType_LParen());
        (void)_t3891;
        if (_t3891) {
            U64 saved = p->pos;
            (void)saved;
            Token *_t3878 = advance(p);
            (void)_t3878;
            Bool is_fsf = 1;
            (void)is_fsf;
            while (1) {
                Bool _t3796 = check(p, TokenType_RParen());
                (void)_t3796;
                Bool _t3797 = check(p, TokenType_Eof());
                (void)_t3797;
                Bool _t3798 = Bool_not(_t3796);
                (void)_t3798;
                ;
                Bool _t3799 = Bool_not(_t3797);
                (void)_t3799;
                ;
                Bool _wcond3793 = Bool_and(_t3798, _t3799);
                (void)_wcond3793;
                ;
                ;
                if (_wcond3793) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3800 = check(p, TokenType_Ident());
                (void)_t3800;
                Bool _t3801 = Bool_not(_t3800);
                (void)_t3801;
                ;
                if (_t3801) {
                    Bool _t3794 = 0;
                    (void)_t3794;
                    is_fsf = _t3794;
                    ;
                    ;
                    break;
                }
                ;
                Token *_t3802 = advance(p);
                (void)_t3802;
                Bool _t3803 = check(p, TokenType_Comma());
                (void)_t3803;
                if (_t3803) {
                    Token *_t3795 = advance(p);
                    (void)_t3795;
                }
                ;
            }
            Bool _t3879 = check(p, TokenType_RParen());
            (void)_t3879;
            Bool _t3880 = Bool_and(is_fsf, _t3879);
            (void)_t3880;
            ;
            if (_t3880) {
                Token *_t3805 = advance(p);
                (void)_t3805;
                Bool _t3806 = check(p, TokenType_LBrace());
                (void)_t3806;
                Bool _t3807 = Bool_not(_t3806);
                (void)_t3807;
                ;
                if (_t3807) {
                    Bool _t3804 = 0;
                    (void)_t3804;
                    is_fsf = _t3804;
                    ;
                }
                ;
            } else {
                Bool _t3808 = 0;
                (void)_t3808;
                is_fsf = _t3808;
                ;
            }
            ;
            U64 _t3881 = U64_clone(&(U64){saved});
            (void)_t3881;
            ;
            p->pos = _t3881;
            ;
            if (is_fsf) {
                Token *_t3832 = expect_token(p, TokenType_LParen());
                (void)_t3832;
                Str *_t3833 = Str_lit("Str", 3ULL);
                (void)_t3833;
                U64 _t3834; { U64 *_hp = (U64 *)Str_size(); _t3834 = *_hp; free(_hp); }
                (void)_t3834;
                Vec *pnames = Vec_new(_t3833, &(U64){_t3834});
                (void)pnames;
                Str_delete(_t3833, &(Bool){1});
                ;
                while (1) {
                    Bool _t3811 = check(p, TokenType_RParen());
                    (void)_t3811;
                    Bool _wcond3809 = Bool_not(_t3811);
                    (void)_wcond3809;
                    ;
                    if (_wcond3809) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *pn = expect_text(p, TokenType_Ident());
                    (void)pn;
                    Vec_push(pnames, pn);
                    Bool _t3812 = check(p, TokenType_Comma());
                    (void)_t3812;
                    if (_t3812) {
                        Token *_t3810 = advance(p);
                        (void)_t3810;
                    }
                    ;
                }
                Token *_t3835 = expect_token(p, TokenType_RParen());
                (void)_t3835;
                Token *_t3836 = expect_token(p, TokenType_LBrace());
                (void)_t3836;
                Expr *body = parse_block(p);
                (void)body;
                Str *_t3837 = Str_lit("Str", 3ULL);
                (void)_t3837;
                U64 _t3838; { U64 *_hp = (U64 *)Str_size(); _t3838 = *_hp; free(_hp); }
                (void)_t3838;
                Str *_t3839 = Str_lit("Str", 3ULL);
                (void)_t3839;
                U64 _t3840; { U64 *_hp = (U64 *)Str_size(); _t3840 = *_hp; free(_hp); }
                (void)_t3840;
                Str *_t3841 = Str_lit("Bool", 4ULL);
                (void)_t3841;
                U64 _t3842; { U64 *_hp = (U64 *)Bool_size(); _t3842 = *_hp; free(_hp); }
                (void)_t3842;
                Str *_t3843 = Str_lit("Bool", 4ULL);
                (void)_t3843;
                U64 _t3844; { U64 *_hp = (U64 *)Bool_size(); _t3844 = *_hp; free(_hp); }
                (void)_t3844;
                Str *_t3845 = Str_lit("Bool", 4ULL);
                (void)_t3845;
                U64 _t3846; { U64 *_hp = (U64 *)Bool_size(); _t3846 = *_hp; free(_hp); }
                (void)_t3846;
                Str *_t3847 = Str_lit("I64", 3ULL);
                (void)_t3847;
                U64 _t3848; { U64 *_hp = (U64 *)I64_size(); _t3848 = *_hp; free(_hp); }
                (void)_t3848;
                Str *_t3849 = Str_lit("I64", 3ULL);
                (void)_t3849;
                U64 _t3850; { U64 *_hp = (U64 *)I64_size(); _t3850 = *_hp; free(_hp); }
                (void)_t3850;
                I64 _t3851 = 0;
                (void)_t3851;
                I64 _t3852 = 1;
                (void)_t3852;
                I64 _t3853 = I64_sub(_t3851, _t3852);
                (void)_t3853;
                ;
                ;
                I64 _t3854 = 0;
                (void)_t3854;
                I64 _t3855 = 1;
                (void)_t3855;
                I64 _t3856 = I64_sub(_t3854, _t3855);
                (void)_t3856;
                ;
                ;
                U32 _t3857 = 0;
                (void)_t3857;
                I32 _t3858 = I64_to_i32(_t3853);
                (void)_t3858;
                ;
                I32 _t3859 = I64_to_i32(_t3856);
                (void)_t3859;
                ;
                Bool _t3860 = 0;
                (void)_t3860;
                Bool _t3861 = 0;
                (void)_t3861;
                FunctionDef *ffd = malloc(sizeof(FunctionDef));
                { FuncType *_ca = FuncType_clone(FuncType_Func()); ffd->func_type = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3837, &(U64){_t3838}); ffd->param_names = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3839, &(U64){_t3840}); ffd->param_types = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3841, &(U64){_t3842}); ffd->param_muts = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3843, &(U64){_t3844}); ffd->param_owns = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3845, &(U64){_t3846}); ffd->param_shallows = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3847, &(U64){_t3848}); ffd->param_fn_sigs = *_ca; free(_ca); }
                ffd->nparam = _t3857;
                { Vec *_ca = Vec_new(_t3849, &(U64){_t3850}); ffd->param_defaults = *_ca; free(_ca); }
                { Str *_ca = Str_clone(Str_lit("", 0ULL)); ffd->return_type = *_ca; free(_ca); }
                ffd->variadic_index = _t3858;
                ffd->kwargs_index = _t3859;
                ffd->return_is_ref = _t3860;
                ffd->return_is_shallow = _t3861;
                (void)ffd;
                Str_delete(_t3837, &(Bool){1});
                ;
                Str_delete(_t3839, &(Bool){1});
                ;
                Str_delete(_t3841, &(Bool){1});
                ;
                Str_delete(_t3843, &(Bool){1});
                ;
                Str_delete(_t3845, &(Bool){1});
                ;
                Str_delete(_t3847, &(Bool){1});
                ;
                Str_delete(_t3849, &(Bool){1});
                ;
                ;
                ;
                ;
                ;
                ;
                FuncType_delete(&ffd->func_type, &(Bool){0});
                { FuncType *_fa = FuncType_clone(FuncType_Func()); ffd->func_type = *_fa; free(_fa); }
                I64 _t3862 = 0;
                (void)_t3862;
                I64 _t3863 = 1;
                (void)_t3863;
                I64 _t3864 = I64_sub(_t3862, _t3863);
                (void)_t3864;
                ;
                ;
                I32 _t3865 = I64_to_i32(_t3864);
                (void)_t3865;
                ;
                ffd->variadic_index = _t3865;
                ;
                I64 _t3866 = 0;
                (void)_t3866;
                I64 _t3867 = 1;
                (void)_t3867;
                I64 _t3868 = I64_sub(_t3866, _t3867);
                (void)_t3868;
                ;
                ;
                I32 _t3869 = I64_to_i32(_t3868);
                (void)_t3869;
                ;
                ffd->kwargs_index = _t3869;
                ;
                U64 np; { U64 *_hp = (U64 *)Vec_len(pnames); np = *_hp; free(_hp); }
                (void)np;
                {
                    U64 _fi3813 = 0;
                    (void)_fi3813;
                    while (1) {
                        U64 _t3815 = 0;
                        (void)_t3815;
                        Range *_t3816 = Range_new(_t3815, np);
                        (void)_t3816;
                        ;
                        U64 _t3817; { U64 *_hp = (U64 *)Range_len(_t3816); _t3817 = *_hp; free(_hp); }
                        (void)_t3817;
                        Range_delete(_t3816, &(Bool){1});
                        Bool _wcond3814; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3813}, &(U64){_t3817}); _wcond3814 = *_hp; free(_hp); }
                        (void)_wcond3814;
                        ;
                        if (_wcond3814) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 _t3818 = 0;
                        (void)_t3818;
                        Range *_t3819 = Range_new(_t3818, np);
                        (void)_t3819;
                        ;
                        U64 _; { U64 *_hp = (U64 *)Range_get(_t3819, _fi3813); _ = *_hp; free(_hp); }
                        (void)_;
                        ;
                        Range_delete(_t3819, &(Bool){1});
                        U64 _t3820 = 1;
                        (void)_t3820;
                        U64 _t3821 = U64_add(_fi3813, _t3820);
                        (void)_t3821;
                        ;
                        _fi3813 = _t3821;
                        ;
                        Str *_t3822 = Str_lit("", 0ULL);
                        (void)_t3822;
                        Vec_push(&ffd->param_types, _t3822);
                        Bool _t3823 = 0;
                        (void)_t3823;
                        Vec_push(&ffd->param_muts, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3823; _oa; }));
                        Bool _t3824 = 0;
                        (void)_t3824;
                        Vec_push(&ffd->param_owns, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3824; _oa; }));
                        Bool _t3825 = 0;
                        (void)_t3825;
                        Vec_push(&ffd->param_shallows, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3825; _oa; }));
                        I64 _t3826 = 0;
                        (void)_t3826;
                        I64 _t3827 = 1;
                        (void)_t3827;
                        I64 _t3828 = I64_sub(_t3826, _t3827);
                        (void)_t3828;
                        ;
                        ;
                        Vec_push(&ffd->param_defaults, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = _t3828; _oa; }));
                        I64 _t3829 = 0;
                        (void)_t3829;
                        I64 _t3830 = 1;
                        (void)_t3830;
                        I64 _t3831 = I64_sub(_t3829, _t3830);
                        (void)_t3831;
                        ;
                        ;
                        Vec_push(&ffd->param_fn_sigs, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = _t3831; _oa; }));
                    }
                    ;
                }
                ;
                Vec_delete(&ffd->param_names, &(Bool){0});
                { Vec *_fa = Vec_clone(pnames); ffd->param_names = *_fa; free(_fa); }
                Vec_delete(pnames, &(Bool){1});
                ExprData *_t3870 = ExprData_FuncDef(ffd);
                (void)_t3870;
                FunctionDef_delete(ffd, &(Bool){1});
                Expr *fdef = Expr_new(_t3870, t_line, t_col, &p->path);
                (void)fdef;
                ExprData_delete(_t3870, &(Bool){1});
                Expr_add_child(fdef, body);
                Bool _t3871 = Bool_clone(&(Bool){is_mut});
                (void)_t3871;
                Bool _t3872 = 0;
                (void)_t3872;
                Bool _t3873 = 0;
                (void)_t3873;
                Bool _t3874 = Bool_clone(&(Bool){is_own});
                (void)_t3874;
                I32 _t3875 = 0;
                (void)_t3875;
                I32 _t3876 = 0;
                (void)_t3876;
                Declaration *dd = malloc(sizeof(Declaration));
                { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
                { Str *_ca = Str_clone(type_name); dd->explicit_type = *_ca; free(_ca); }
                dd->is_mut = _t3871;
                dd->is_namespace = _t3872;
                dd->is_ref = _t3873;
                dd->is_own = _t3874;
                dd->field_offset = _t3875;
                dd->field_size = _t3876;
                dd->field_struct_def = NULL;
                dd->fn_sig = NULL;
                (void)dd;
                ;
                ;
                ;
                ;
                ;
                ;
                ExprData *_t3877 = ExprData_Decl(dd);
                (void)_t3877;
                Declaration_delete(dd, &(Bool){1});
                Expr *decl = Expr_new(_t3877, t_line, t_col, &p->path);
                (void)decl;
                ExprData_delete(_t3877, &(Bool){1});
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
        Bool _t3892 = Bool_clone(&(Bool){is_mut});
        (void)_t3892;
        Bool _t3893 = 0;
        (void)_t3893;
        Bool _t3894 = 0;
        (void)_t3894;
        Bool _t3895 = Bool_clone(&(Bool){is_own});
        (void)_t3895;
        I32 _t3896 = 0;
        (void)_t3896;
        I32 _t3897 = 0;
        (void)_t3897;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(type_name); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3892;
        dd->is_namespace = _t3893;
        dd->is_ref = _t3894;
        dd->is_own = _t3895;
        dd->field_offset = _t3896;
        dd->field_size = _t3897;
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
        ExprData *_t3898 = ExprData_Decl(dd);
        (void)_t3898;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3898, t_line, t_col, &p->path);
        (void)decl;
        ExprData_delete(_t3898, &(Bool){1});
        Expr *_t3899 = parse_expression(p);
        (void)_t3899;
        Expr_add_child(decl, _t3899);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return decl;
    }
    ;
    Bool _t3952 = check(p, TokenType_Dot());
    (void)_t3952;
    if (_t3952) {
        Str *_t3938 = Str_clone(name);
        (void)_t3938;
        ExprData *_t3939 = ExprData_Ident(_t3938);
        (void)_t3939;
        Str_delete(_t3938, &(Bool){1});
        Expr *obj = Expr_new(_t3939, t_line, t_col, &p->path);
        (void)obj;
        ExprData_delete(_t3939, &(Bool){1});
        Str *last_field = Str_lit("", 0ULL);
        (void)last_field;
        U32 last_line = 0;
        (void)last_line;
        U32 last_col = 0;
        (void)last_col;
        while (1) {
            Bool _wcond3900 = check(p, TokenType_Dot());
            (void)_wcond3900;
            if (_wcond3900) {
            } else {
                ;
                break;
            }
            ;
            Token *_t3904 = advance(p);
            (void)_t3904;
            U32 _t3905 = peek_line(p);
            (void)_t3905;
            last_line = _t3905;
            ;
            U32 _t3906 = peek_col(p);
            (void)_t3906;
            last_col = _t3906;
            ;
            last_field = expect_text(p, TokenType_Ident());
            Bool _t3907 = check(p, TokenType_Dot());
            (void)_t3907;
            if (_t3907) {
                Str *_t3901 = Str_clone(last_field);
                (void)_t3901;
                ExprData *_t3902 = ExprData_FieldAccess(_t3901);
                (void)_t3902;
                Str_delete(_t3901, &(Bool){1});
                Expr *access = Expr_new(_t3902, last_line, last_col, &p->path);
                (void)access;
                ExprData_delete(_t3902, &(Bool){1});
                Expr *_t3903 = Expr_clone(obj);
                (void)_t3903;
                Expr_add_child(access, _t3903);
                obj = Expr_clone(access);
                Expr_delete(access, &(Bool){1});
            }
            ;
        }
        Bool _t3940 = check(p, TokenType_LParen());
        (void)_t3940;
        if (_t3940) {
            Token *_t3934 = advance(p);
            (void)_t3934;
            ExprData *_t3935 = ExprData_FieldAccess(last_field);
            (void)_t3935;
            Expr *callee = Expr_new(_t3935, last_line, last_col, &p->path);
            (void)callee;
            ExprData_delete(_t3935, &(Bool){1});
            Expr *_t3936 = Expr_clone(obj);
            (void)_t3936;
            Expr_add_child(callee, _t3936);
            Expr *mcall = Expr_new(ExprData_FCall(), last_line, last_col, &p->path);
            (void)mcall;
            Expr_add_child(mcall, callee);
            while (1) {
                Bool _t3926 = check(p, TokenType_RParen());
                (void)_t3926;
                Bool _t3927 = check(p, TokenType_Eof());
                (void)_t3927;
                Bool _t3928 = Bool_not(_t3926);
                (void)_t3928;
                ;
                Bool _t3929 = Bool_not(_t3927);
                (void)_t3929;
                ;
                Bool _wcond3908 = Bool_and(_t3928, _t3929);
                (void)_wcond3908;
                ;
                ;
                if (_wcond3908) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3930 = check(p, TokenType_Ident());
                (void)_t3930;
                if (_t3930) {
                    U64 _t3919 = 1;
                    (void)_t3919;
                    U64 _t3920 = U64_add(p->pos, _t3919);
                    (void)_t3920;
                    ;
                    U64 _t3921; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3921 = *_hp; free(_hp); }
                    (void)_t3921;
                    Bool _t3922; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3920}, &(U64){_t3921}); _t3922 = *_hp; free(_hp); }
                    (void)_t3922;
                    ;
                    ;
                    if (_t3922) {
                        U64 _t3914 = 1;
                        (void)_t3914;
                        U64 _t3915 = U64_add(p->pos, _t3914);
                        (void)_t3915;
                        ;
                        I64 _t3916 = U64_to_i64(_t3915);
                        (void)_t3916;
                        ;
                        U64 *_t3917 = malloc(sizeof(U64)); *_t3917 = I64_to_u64(_t3916);
                        (void)_t3917;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3917);
                        (void)nt;
                        Bool _t3918; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3918 = *_hp; free(_hp); }
                        (void)_t3918;
                        U64_delete(_t3917, &(Bool){1});
                        if (_t3918) {
                            U32 na_line = peek_line(p);
                            (void)na_line;
                            U32 na_col = peek_col(p);
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3910 = advance(p);
                            (void)_t3910;
                            ExprData *_t3911 = ExprData_NamedArg(aname);
                            (void)_t3911;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3911, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3911, &(Bool){1});
                            ;
                            ;
                            Expr *_t3912 = parse_expression(p);
                            (void)_t3912;
                            Expr_add_child(na, _t3912);
                            Expr_add_child(mcall, na);
                            Bool _t3913 = check(p, TokenType_Comma());
                            (void)_t3913;
                            if (_t3913) {
                                Token *_t3909 = advance(p);
                                (void)_t3909;
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
                Bool _t3931 = check(p, TokenType_KwOwn());
                (void)_t3931;
                if (_t3931) {
                    Token *_t3923 = advance(p);
                    (void)_t3923;
                    Bool _t3924 = 1;
                    (void)_t3924;
                    is_own_arg = _t3924;
                    ;
                }
                ;
                Expr *marg = parse_expression(p);
                (void)marg;
                Bool _t3932 = Bool_clone(&(Bool){is_own_arg});
                (void)_t3932;
                ;
                marg->is_own_arg = _t3932;
                ;
                Expr_add_child(mcall, marg);
                Bool _t3933 = check(p, TokenType_Comma());
                (void)_t3933;
                if (_t3933) {
                    Token *_t3925 = advance(p);
                    (void)_t3925;
                }
                ;
            }
            Token *_t3937 = expect_token(p, TokenType_RParen());
            (void)_t3937;
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
        Token *_t3941 = expect_token(p, TokenType_Eq());
        (void)_t3941;
        ExprData *_t3942 = ExprData_FieldAssign(last_field);
        (void)_t3942;
        Str_delete(last_field, &(Bool){1});
        Expr *fa = Expr_new(_t3942, t_line, t_col, &p->path);
        (void)fa;
        ExprData_delete(_t3942, &(Bool){1});
        Expr *_t3943 = Expr_clone(obj);
        (void)_t3943;
        Expr_delete(obj, &(Bool){1});
        Expr_add_child(fa, _t3943);
        Expr *_t3944 = parse_expression(p);
        (void)_t3944;
        Expr_add_child(fa, _t3944);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return fa;
    }
    ;
    Bool _t3953 = check(p, TokenType_Eq());
    (void)_t3953;
    if (_t3953) {
        Token *_t3945 = advance(p);
        (void)_t3945;
        Str *_t3946 = Str_clone(name);
        (void)_t3946;
        ExprData *_t3947 = ExprData_Assign(_t3946);
        (void)_t3947;
        Str_delete(_t3946, &(Bool){1});
        Expr *assign = Expr_new(_t3947, t_line, t_col, &p->path);
        (void)assign;
        ExprData_delete(_t3947, &(Bool){1});
        Expr *_t3948 = parse_expression(p);
        (void)_t3948;
        Expr_add_child(assign, _t3948);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return assign;
    }
    ;
    Bool _t3954 = check(p, TokenType_LParen());
    (void)_t3954;
    if (_t3954) {
        Expr *_t3949 = parse_call(p, name, t_line, t_col);
        (void)_t3949;
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return _t3949;
    }
    ;
    Str *_t3955 = Str_lit("Str", 3ULL);
    (void)_t3955;
    U64 _t3956; { U64 *_hp = (U64 *)Str_size(); _t3956 = *_hp; free(_hp); }
    (void)_t3956;
    U64 _t3957 = 8;
    (void)_t3957;
    Array *_va69 = Array_new(_t3955, &(U64){_t3956}, &(U64){_t3957});
    (void)_va69;
    Str_delete(_t3955, &(Bool){1});
    ;
    ;
    U64 _t3958 = 0;
    (void)_t3958;
    Str *_t3959 = Str_clone(&p->path);
    (void)_t3959;
    Array_set(_va69, &(U64){_t3958}, _t3959);
    ;
    U64 _t3960 = 1;
    (void)_t3960;
    Str *_t3961 = Str_lit(":", 1ULL);
    (void)_t3961;
    Array_set(_va69, &(U64){_t3960}, _t3961);
    ;
    U64 _t3962 = 2;
    (void)_t3962;
    Str *_t3963 = U32_to_str(&(U32){t_line});
    (void)_t3963;
    ;
    Array_set(_va69, &(U64){_t3962}, _t3963);
    ;
    U64 _t3964 = 3;
    (void)_t3964;
    Str *_t3965 = Str_lit(":", 1ULL);
    (void)_t3965;
    Array_set(_va69, &(U64){_t3964}, _t3965);
    ;
    U64 _t3966 = 4;
    (void)_t3966;
    Str *_t3967 = U32_to_str(&(U32){t_col});
    (void)_t3967;
    ;
    Array_set(_va69, &(U64){_t3966}, _t3967);
    ;
    U64 _t3968 = 5;
    (void)_t3968;
    Str *_t3969 = Str_lit(": expected ':=', ':', '=' or '(' after identifier '", 51ULL);
    (void)_t3969;
    Array_set(_va69, &(U64){_t3968}, _t3969);
    ;
    U64 _t3970 = 6;
    (void)_t3970;
    Str *_t3971 = Str_clone(name);
    (void)_t3971;
    Str_delete(name, &(Bool){1});
    Array_set(_va69, &(U64){_t3970}, _t3971);
    ;
    U64 _t3972 = 7;
    (void)_t3972;
    Str *_t3973 = Str_lit("'", 1ULL);
    (void)_t3973;
    Array_set(_va69, &(U64){_t3972}, _t3973);
    ;
    Str *_t3974 = Str_lit("src/self/parser.til:781:11", 26ULL);
    (void)_t3974;
    panic(_t3974, _va69);
    Str_delete(_t3974, &(Bool){1});
    U32 _t3975 = 0;
    (void)_t3975;
    U32 _t3976 = 0;
    (void)_t3976;
    Expr *_t3977 = Expr_new(ExprData_Body(), _t3975, _t3976, &p->path);
    (void)_t3977;
    ;
    ;
    return _t3977;
}

Expr * parse_statement(Parser * p) {
    (void)p;
    U32 t_line = peek_line(p);
    (void)t_line;
    U32 t_col = peek_col(p);
    (void)t_col;
    Token *t = peek(p);
    (void)t;
    Bool _t4115; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t4115 = *_hp; free(_hp); }
    (void)_t4115;
    if (_t4115) {
        Bool _t3978 = 0;
        (void)_t3978;
        Bool _t3979 = 0;
        (void)_t3979;
        Expr *_t3980 = parse_statement_ident(p, _t3978, _t3979);
        (void)_t3980;
        ;
        ;
        ;
        ;
        ;
        return _t3980;
    }
    ;
    Bool _t4116; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwRef()); _t4116 = *_hp; free(_hp); }
    (void)_t4116;
    if (_t4116) {
        Token *_t3987 = advance(p);
        (void)_t3987;
        Bool ref_mut = 0;
        (void)ref_mut;
        Bool _t3988 = check(p, TokenType_KwMut());
        (void)_t3988;
        if (_t3988) {
            Token *_t3981 = advance(p);
            (void)_t3981;
            Bool _t3982 = 1;
            (void)_t3982;
            ref_mut = _t3982;
            ;
        }
        ;
        U32 i_line = peek_line(p);
        (void)i_line;
        U32 i_col = peek_col(p);
        (void)i_col;
        Str *iname = expect_text(p, TokenType_Ident());
        (void)iname;
        Bool _t3989 = 0;
        (void)_t3989;
        Bool _t3990 = 0;
        (void)_t3990;
        Bool _t3991 = 1;
        (void)_t3991;
        Bool _t3992 = 0;
        (void)_t3992;
        I32 _t3993 = 0;
        (void)_t3993;
        I32 _t3994 = 0;
        (void)_t3994;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(iname); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3989;
        dd->is_namespace = _t3990;
        dd->is_ref = _t3991;
        dd->is_own = _t3992;
        dd->field_offset = _t3993;
        dd->field_size = _t3994;
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
            Bool _t3983 = 1;
            (void)_t3983;
            dd->is_mut = _t3983;
            ;
        }
        ;
        Bool _t3995 = check(p, TokenType_Colon());
        (void)_t3995;
        if (_t3995) {
            Token *_t3984 = advance(p);
            (void)_t3984;
            Str_delete(&dd->explicit_type, &(Bool){0});
            { Str *_fa = expect_text(p, TokenType_Ident()); dd->explicit_type = *_fa; free(_fa); }
            Token *_t3985 = expect_token(p, TokenType_Eq());
            (void)_t3985;
        } else {
            Token *_t3986 = expect_token(p, TokenType_ColonEq());
            (void)_t3986;
        }
        ;
        ExprData *_t3996 = ExprData_Decl(dd);
        (void)_t3996;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3996, i_line, i_col, &p->path);
        (void)decl;
        ExprData_delete(_t3996, &(Bool){1});
        ;
        ;
        Expr *_t3997 = parse_expression(p);
        (void)_t3997;
        Expr_add_child(decl, _t3997);
        ;
        ;
        ;
        return decl;
    }
    ;
    Bool _t4117; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMut()); _t4117 = *_hp; free(_hp); }
    (void)_t4117;
    if (_t4117) {
        Token *_t3998 = advance(p);
        (void)_t3998;
        Bool _t3999 = 1;
        (void)_t3999;
        Bool _t4000 = 0;
        (void)_t4000;
        Expr *_t4001 = parse_statement_ident(p, _t3999, _t4000);
        (void)_t4001;
        ;
        ;
        ;
        ;
        ;
        return _t4001;
    }
    ;
    Bool _t4118; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwReturn()); _t4118 = *_hp; free(_hp); }
    (void)_t4118;
    if (_t4118) {
        Token *_t4003 = advance(p);
        (void)_t4003;
        Expr *ret = Expr_new(ExprData_Return(), t_line, t_col, &p->path);
        (void)ret;
        Bool _t4004 = check(p, TokenType_RBrace());
        (void)_t4004;
        Bool _t4005 = check(p, TokenType_Eof());
        (void)_t4005;
        Bool _t4006 = Bool_not(_t4004);
        (void)_t4006;
        ;
        Bool _t4007 = Bool_not(_t4005);
        (void)_t4007;
        ;
        Bool _t4008 = Bool_and(_t4006, _t4007);
        (void)_t4008;
        ;
        ;
        if (_t4008) {
            Expr *_t4002 = parse_expression(p);
            (void)_t4002;
            Expr_add_child(ret, _t4002);
        }
        ;
        ;
        ;
        ;
        return ret;
    }
    ;
    Bool _t4119; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwIf()); _t4119 = *_hp; free(_hp); }
    (void)_t4119;
    if (_t4119) {
        Token *_t4016 = advance(p);
        (void)_t4016;
        Expr *node = Expr_new(ExprData_If(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t4017 = parse_expression(p);
        (void)_t4017;
        Expr_add_child(node, _t4017);
        Token *_t4018 = expect_token(p, TokenType_LBrace());
        (void)_t4018;
        Expr *_t4019 = parse_block(p);
        (void)_t4019;
        Expr_add_child(node, _t4019);
        Bool _t4020 = check(p, TokenType_KwElse());
        (void)_t4020;
        if (_t4020) {
            Token *_t4014 = advance(p);
            (void)_t4014;
            Bool _t4015 = check(p, TokenType_KwIf());
            (void)_t4015;
            if (_t4015) {
                U32 _t4009 = peek_line(p);
                (void)_t4009;
                U32 _t4010 = peek_col(p);
                (void)_t4010;
                Expr *else_body = Expr_new(ExprData_Body(), _t4009, _t4010, &p->path);
                (void)else_body;
                ;
                ;
                Expr *_t4011 = parse_statement(p);
                (void)_t4011;
                Expr_add_child(else_body, _t4011);
                Expr_add_child(node, else_body);
            } else {
                Token *_t4012 = expect_token(p, TokenType_LBrace());
                (void)_t4012;
                Expr *_t4013 = parse_block(p);
                (void)_t4013;
                Expr_add_child(node, _t4013);
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
    Bool _t4120; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t4120 = *_hp; free(_hp); }
    (void)_t4120;
    Bool _t4121; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t4121 = *_hp; free(_hp); }
    (void)_t4121;
    Bool _t4122 = Bool_or(_t4120, _t4121);
    (void)_t4122;
    ;
    ;
    Bool _t4123; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t4123 = *_hp; free(_hp); }
    (void)_t4123;
    Bool _t4124 = Bool_or(_t4122, _t4123);
    (void)_t4124;
    ;
    ;
    Bool _t4125; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t4125 = *_hp; free(_hp); }
    (void)_t4125;
    Bool _t4126 = Bool_or(_t4124, _t4125);
    (void)_t4126;
    ;
    ;
    if (_t4126) {
        Expr *_t4021 = parse_expression(p);
        (void)_t4021;
        ;
        ;
        ;
        return _t4021;
    }
    ;
    Bool _t4127; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t4127 = *_hp; free(_hp); }
    (void)_t4127;
    if (_t4127) {
        Token *_t4022 = advance(p);
        (void)_t4022;
        Expr *_t4023 = parse_block(p);
        (void)_t4023;
        ;
        ;
        ;
        return _t4023;
    }
    ;
    Bool _t4128; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwWhile()); _t4128 = *_hp; free(_hp); }
    (void)_t4128;
    if (_t4128) {
        Token *_t4024 = advance(p);
        (void)_t4024;
        Expr *node = Expr_new(ExprData_While(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t4025 = parse_expression(p);
        (void)_t4025;
        Expr_add_child(node, _t4025);
        Token *_t4026 = expect_token(p, TokenType_LBrace());
        (void)_t4026;
        Expr *_t4027 = parse_block(p);
        (void)_t4027;
        Expr_add_child(node, _t4027);
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4129; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFor()); _t4129 = *_hp; free(_hp); }
    (void)_t4129;
    if (_t4129) {
        Token *_t4029 = advance(p);
        (void)_t4029;
        U32 i_line = peek_line(p);
        (void)i_line;
        U32 i_col = peek_col(p);
        (void)i_col;
        Str *iname = expect_text(p, TokenType_Ident());
        (void)iname;
        ExprData *_t4030 = ExprData_ForIn(iname);
        (void)_t4030;
        Str_delete(iname, &(Bool){1});
        Expr *node = Expr_new(_t4030, i_line, i_col, &p->path);
        (void)node;
        ExprData_delete(_t4030, &(Bool){1});
        ;
        ;
        Bool _t4031 = check(p, TokenType_Colon());
        (void)_t4031;
        if (_t4031) {
            Token *_t4028 = advance(p);
            (void)_t4028;
            Str_delete(&node->struct_name, &(Bool){0});
            { Str *_fa = expect_text(p, TokenType_Ident()); node->struct_name = *_fa; free(_fa); }
        }
        ;
        Token *_t4032 = expect_token(p, TokenType_KwIn());
        (void)_t4032;
        Expr *_t4033 = parse_expression(p);
        (void)_t4033;
        Expr_add_child(node, _t4033);
        Token *_t4034 = expect_token(p, TokenType_LBrace());
        (void)_t4034;
        Expr *_t4035 = parse_block(p);
        (void)_t4035;
        Expr_add_child(node, _t4035);
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4130; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwSwitch()); _t4130 = *_hp; free(_hp); }
    (void)_t4130;
    if (_t4130) {
        Token *_t4059 = advance(p);
        (void)_t4059;
        Expr *node = Expr_new(ExprData_Switch(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t4060 = parse_expression(p);
        (void)_t4060;
        Expr_add_child(node, _t4060);
        Token *_t4061 = expect_token(p, TokenType_LBrace());
        (void)_t4061;
        while (1) {
            Bool _t4047 = check(p, TokenType_RBrace());
            (void)_t4047;
            Bool _t4048 = check(p, TokenType_Eof());
            (void)_t4048;
            Bool _t4049 = Bool_not(_t4047);
            (void)_t4049;
            ;
            Bool _t4050 = Bool_not(_t4048);
            (void)_t4050;
            ;
            Bool _wcond4036 = Bool_and(_t4049, _t4050);
            (void)_wcond4036;
            ;
            ;
            if (_wcond4036) {
            } else {
                ;
                break;
            }
            ;
            Token *_t4051 = expect_token(p, TokenType_KwCase());
            (void)_t4051;
            U32 _t4052 = peek_line(p);
            (void)_t4052;
            U32 _t4053 = peek_col(p);
            (void)_t4053;
            Expr *cn = Expr_new(ExprData_Case(), _t4052, _t4053, &p->path);
            (void)cn;
            ;
            ;
            Bool _t4054 = check(p, TokenType_Colon());
            (void)_t4054;
            Bool _t4055 = Bool_not(_t4054);
            (void)_t4055;
            ;
            if (_t4055) {
                Expr *_t4037 = parse_expression(p);
                (void)_t4037;
                Expr_add_child(cn, _t4037);
            }
            ;
            Token *_t4056 = expect_token(p, TokenType_Colon());
            (void)_t4056;
            U32 _t4057 = peek_line(p);
            (void)_t4057;
            U32 _t4058 = peek_col(p);
            (void)_t4058;
            Expr *cb = Expr_new(ExprData_Body(), _t4057, _t4058, &p->path);
            (void)cb;
            ;
            ;
            while (1) {
                Bool _t4039 = check(p, TokenType_KwCase());
                (void)_t4039;
                Bool _t4040 = check(p, TokenType_RBrace());
                (void)_t4040;
                Bool _t4041 = Bool_not(_t4039);
                (void)_t4041;
                ;
                Bool _t4042 = Bool_not(_t4040);
                (void)_t4042;
                ;
                Bool _t4043 = check(p, TokenType_Eof());
                (void)_t4043;
                Bool _t4044 = Bool_and(_t4041, _t4042);
                (void)_t4044;
                ;
                ;
                Bool _t4045 = Bool_not(_t4043);
                (void)_t4045;
                ;
                Bool _wcond4038 = Bool_and(_t4044, _t4045);
                (void)_wcond4038;
                ;
                ;
                if (_wcond4038) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t4046 = parse_statement(p);
                (void)_t4046;
                Expr_add_child(cb, _t4046);
            }
            Expr_add_child(cn, cb);
            Expr_add_child(node, cn);
        }
        Token *_t4062 = expect_token(p, TokenType_RBrace());
        (void)_t4062;
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4131; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwOwn()); _t4131 = *_hp; free(_hp); }
    (void)_t4131;
    if (_t4131) {
        Token *_t4104 = advance(p);
        (void)_t4104;
        Bool _t4105 = check(p, TokenType_Ident());
        (void)_t4105;
        Bool _t4106 = check(p, TokenType_KwMut());
        (void)_t4106;
        Bool _t4107 = Bool_or(_t4105, _t4106);
        (void)_t4107;
        ;
        ;
        if (_t4107) {
            Bool own_mut = 0;
            (void)own_mut;
            Bool _t4094 = check(p, TokenType_KwMut());
            (void)_t4094;
            if (_t4094) {
                Token *_t4063 = advance(p);
                (void)_t4063;
                Bool _t4064 = 1;
                (void)_t4064;
                own_mut = _t4064;
                ;
            }
            ;
            Bool _t4095 = check(p, TokenType_Ident());
            (void)_t4095;
            if (_t4095) {
                U64 _t4074 = 1;
                (void)_t4074;
                U64 _t4075 = U64_add(p->pos, _t4074);
                (void)_t4075;
                ;
                U64 _t4076; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t4076 = *_hp; free(_hp); }
                (void)_t4076;
                Bool _t4077; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4075}, &(U64){_t4076}); _t4077 = *_hp; free(_hp); }
                (void)_t4077;
                ;
                ;
                if (_t4077) {
                    U64 _t4067 = 1;
                    (void)_t4067;
                    U64 _t4068 = U64_add(p->pos, _t4067);
                    (void)_t4068;
                    ;
                    I64 _t4069 = U64_to_i64(_t4068);
                    (void)_t4069;
                    ;
                    U64 *_t4070 = malloc(sizeof(U64)); *_t4070 = I64_to_u64(_t4069);
                    (void)_t4070;
                    ;
                    Token *nt = Vec_get(&p->tokens, _t4070);
                    (void)nt;
                    Bool _t4071; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_ColonEq()); _t4071 = *_hp; free(_hp); }
                    (void)_t4071;
                    Bool _t4072; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Colon()); _t4072 = *_hp; free(_hp); }
                    (void)_t4072;
                    U64_delete(_t4070, &(Bool){1});
                    Bool _t4073 = Bool_or(_t4071, _t4072);
                    (void)_t4073;
                    ;
                    ;
                    if (_t4073) {
                        Bool _t4065 = 1;
                        (void)_t4065;
                        Expr *_t4066 = parse_statement_ident(p, own_mut, _t4065);
                        (void)_t4066;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        return _t4066;
                    }
                    ;
                }
                ;
            }
            ;
            if (own_mut) {
                Str *_t4078 = Str_lit("Str", 3ULL);
                (void)_t4078;
                U64 _t4079; { U64 *_hp = (U64 *)Str_size(); _t4079 = *_hp; free(_hp); }
                (void)_t4079;
                U64 _t4080 = 6;
                (void)_t4080;
                Array *_va70 = Array_new(_t4078, &(U64){_t4079}, &(U64){_t4080});
                (void)_va70;
                Str_delete(_t4078, &(Bool){1});
                ;
                ;
                U64 _t4081 = 0;
                (void)_t4081;
                Str *_t4082 = Str_clone(&p->path);
                (void)_t4082;
                Array_set(_va70, &(U64){_t4081}, _t4082);
                ;
                U64 _t4083 = 1;
                (void)_t4083;
                Str *_t4084 = Str_lit(":", 1ULL);
                (void)_t4084;
                Array_set(_va70, &(U64){_t4083}, _t4084);
                ;
                U64 _t4085 = 2;
                (void)_t4085;
                Str *_t4086 = U32_to_str(&(U32){t_line});
                (void)_t4086;
                Array_set(_va70, &(U64){_t4085}, _t4086);
                ;
                U64 _t4087 = 3;
                (void)_t4087;
                Str *_t4088 = Str_lit(":", 1ULL);
                (void)_t4088;
                Array_set(_va70, &(U64){_t4087}, _t4088);
                ;
                U64 _t4089 = 4;
                (void)_t4089;
                Str *_t4090 = U32_to_str(&(U32){t_col});
                (void)_t4090;
                Array_set(_va70, &(U64){_t4089}, _t4090);
                ;
                U64 _t4091 = 5;
                (void)_t4091;
                Str *_t4092 = Str_lit(": expected identifier after 'own mut'", 37ULL);
                (void)_t4092;
                Array_set(_va70, &(U64){_t4091}, _t4092);
                ;
                Str *_t4093 = Str_lit("src/self/parser.til:914:23", 26ULL);
                (void)_t4093;
                panic(_t4093, _va70);
                Str_delete(_t4093, &(Bool){1});
            }
            ;
        }
        ;
        Expr *expr = parse_expression(p);
        (void)expr;
        I64 _t4108 = 0;
        (void)_t4108;
        I64 _t4109 = 1;
        (void)_t4109;
        I64 primary_idx = I64_sub(_t4108, _t4109);
        (void)primary_idx;
        ;
        ;
        ;
        Expr *cur = Expr_clone(expr);
        (void)cur;
        while (1) {
            U64 _t4097; { U64 *_hp = (U64 *)Vec_len(&cur->children); _t4097 = *_hp; free(_hp); }
            (void)_t4097;
            U64 _t4098 = 0;
            (void)_t4098;
            Bool _t4099; { Bool *_hp = (Bool *)ExprData_is_FCall(&cur->data); _t4099 = *_hp; free(_hp); }
            (void)_t4099;
            Bool _t4100; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(&cur->data); _t4100 = *_hp; free(_hp); }
            (void)_t4100;
            Bool _t4101; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4097}, &(U64){_t4098}); _t4101 = *_hp; free(_hp); }
            (void)_t4101;
            ;
            ;
            Bool _t4102 = Bool_or(_t4099, _t4100);
            (void)_t4102;
            ;
            ;
            Bool _wcond4096 = Bool_and(_t4101, _t4102);
            (void)_wcond4096;
            ;
            ;
            if (_wcond4096) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t4103 = malloc(sizeof(U64));
            *_t4103 = 0;
            (void)_t4103;
            Expr *ch = Vec_get(&cur->children, _t4103);
            (void)ch;
            cur = Expr_clone(ch);
            U64_delete(_t4103, &(Bool){1});
        }
        Bool _t4110 = 1;
        (void)_t4110;
        cur->is_own_arg = _t4110;
        ;
        Expr_delete(cur, &(Bool){1});
        ;
        ;
        ;
        ;
        return expr;
    }
    ;
    Bool _t4132; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwBreak()); _t4132 = *_hp; free(_hp); }
    (void)_t4132;
    if (_t4132) {
        Token *_t4111 = advance(p);
        (void)_t4111;
        Expr *_t4112 = Expr_new(ExprData_Break(), t_line, t_col, &p->path);
        (void)_t4112;
        ;
        ;
        ;
        return _t4112;
    }
    ;
    Bool _t4133; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwContinue()); _t4133 = *_hp; free(_hp); }
    (void)_t4133;
    if (_t4133) {
        Token *_t4113 = advance(p);
        (void)_t4113;
        Expr *_t4114 = Expr_new(ExprData_Continue(), t_line, t_col, &p->path);
        (void)_t4114;
        ;
        ;
        ;
        return _t4114;
    }
    ;
    Str *_t4134 = Str_lit("Str", 3ULL);
    (void)_t4134;
    U64 _t4135; { U64 *_hp = (U64 *)Str_size(); _t4135 = *_hp; free(_hp); }
    (void)_t4135;
    U64 _t4136 = 8;
    (void)_t4136;
    Array *_va71 = Array_new(_t4134, &(U64){_t4135}, &(U64){_t4136});
    (void)_va71;
    Str_delete(_t4134, &(Bool){1});
    ;
    ;
    U64 _t4137 = 0;
    (void)_t4137;
    Str *_t4138 = Str_clone(&p->path);
    (void)_t4138;
    Array_set(_va71, &(U64){_t4137}, _t4138);
    ;
    U64 _t4139 = 1;
    (void)_t4139;
    Str *_t4140 = Str_lit(":", 1ULL);
    (void)_t4140;
    Array_set(_va71, &(U64){_t4139}, _t4140);
    ;
    U64 _t4141 = 2;
    (void)_t4141;
    Str *_t4142 = U32_to_str(&(U32){t_line});
    (void)_t4142;
    ;
    Array_set(_va71, &(U64){_t4141}, _t4142);
    ;
    U64 _t4143 = 3;
    (void)_t4143;
    Str *_t4144 = Str_lit(":", 1ULL);
    (void)_t4144;
    Array_set(_va71, &(U64){_t4143}, _t4144);
    ;
    U64 _t4145 = 4;
    (void)_t4145;
    Str *_t4146 = U32_to_str(&(U32){t_col});
    (void)_t4146;
    ;
    Array_set(_va71, &(U64){_t4145}, _t4146);
    ;
    U64 _t4147 = 5;
    (void)_t4147;
    Str *_t4148 = Str_lit(": expected statement, found '", 29ULL);
    (void)_t4148;
    Array_set(_va71, &(U64){_t4147}, _t4148);
    ;
    U64 _t4149 = 6;
    (void)_t4149;
    Str *_t4150 = Str_clone(&t->text);
    (void)_t4150;
    Array_set(_va71, &(U64){_t4149}, _t4150);
    ;
    U64 _t4151 = 7;
    (void)_t4151;
    Str *_t4152 = Str_lit("'", 1ULL);
    (void)_t4152;
    Array_set(_va71, &(U64){_t4151}, _t4152);
    ;
    Str *_t4153 = Str_lit("src/self/parser.til:941:11", 26ULL);
    (void)_t4153;
    panic(_t4153, _va71);
    Str_delete(_t4153, &(Bool){1});
    U32 _t4154 = 0;
    (void)_t4154;
    U32 _t4155 = 0;
    (void)_t4155;
    Expr *_t4156 = Expr_new(ExprData_Body(), _t4154, _t4155, &p->path);
    (void)_t4156;
    ;
    ;
    return _t4156;
}

Expr * parse(Vec * tokens, Str * path, Str * mode_out) {
    (void)tokens;
    (void)path;
    (void)mode_out;
    I64 _t4168 = 0;
    (void)_t4168;
    Parser *p = malloc(sizeof(Parser));
    { Vec *_ca = Vec_clone(tokens); p->tokens = *_ca; free(_ca); }
    p->pos = _t4168;
    { Str *_ca = Str_clone(path); p->path = *_ca; free(_ca); }
    (void)p;
    ;
    Bool _t4169 = check(p, TokenType_KwMode());
    (void)_t4169;
    if (_t4169) {
        Token *_t4161 = advance(p);
        (void)_t4161;
        Bool _t4162 = check(p, TokenType_Ident());
        (void)_t4162;
        Bool _t4163 = check(p, TokenType_KwTest());
        (void)_t4163;
        Bool _t4164 = Bool_or(_t4162, _t4163);
        (void)_t4164;
        ;
        ;
        if (_t4164) {
            Str *_t4157 = Str_clone(&peek(p)->text);
            (void)_t4157;
            U64 _t4158; { U64 *_hp = (U64 *)Str_size(); _t4158 = *_hp; free(_hp); }
            (void)_t4158;
            swap(mode_out, _t4157, _t4158);
            Str_delete(_t4157, &(Bool){1});
            ;
            Token *_t4159 = advance(p);
            (void)_t4159;
        } else {
            Token *_t4160 = expect_token(p, TokenType_Ident());
            (void)_t4160;
        }
        ;
    }
    ;
    U32 _t4170 = 1;
    (void)_t4170;
    U32 _t4171 = 1;
    (void)_t4171;
    Expr *root = Expr_new(ExprData_Body(), _t4170, _t4171, &p->path);
    (void)root;
    ;
    ;
    while (1) {
        Bool _t4166 = check(p, TokenType_Eof());
        (void)_t4166;
        Bool _wcond4165 = Bool_not(_t4166);
        (void)_wcond4165;
        ;
        if (_wcond4165) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t4167 = parse_statement(p);
        (void)_t4167;
        Expr_add_child(root, _t4167);
    }
    Parser_delete(p, &(Bool){1});
    return root;
}

