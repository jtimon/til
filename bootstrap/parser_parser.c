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
    U64 _t3193; { U64 *_hp = (U64 *)Vec_len(&fd->param_types); _t3193 = *_hp; free(_hp); }
    (void)_t3193;
    I64 _t3194 = U64_to_i64(_t3193);
    (void)_t3194;
    ;
    U32 _t3195 = I64_to_u32(_t3194);
    (void)_t3195;
    ;
    fd->nparam = _t3195;
    ;
    ExprData *_t3196 = ExprData_FuncDef(fd);
    (void)_t3196;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *sig = Expr_new(_t3196, line, col, &p->path);
    (void)sig;
    ExprData_delete(_t3196, &(Bool){1});
    return sig;
}

Expr * parse_block(Parser * p) {
    (void)p;
    U32 _t3203 = peek_line(p);
    (void)_t3203;
    U32 _t3204 = peek_col(p);
    (void)_t3204;
    Expr *body = Expr_new(ExprData_Body(), _t3203, _t3204, &p->path);
    (void)body;
    ;
    ;
    while (1) {
        Bool _t3198 = check(p, TokenType_RBrace());
        (void)_t3198;
        Bool _t3199 = check(p, TokenType_Eof());
        (void)_t3199;
        Bool _t3200 = Bool_not(_t3198);
        (void)_t3200;
        ;
        Bool _t3201 = Bool_not(_t3199);
        (void)_t3201;
        ;
        Bool _wcond3197 = Bool_and(_t3200, _t3201);
        (void)_wcond3197;
        ;
        ;
        if (_wcond3197) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t3202 = parse_statement(p);
        (void)_t3202;
        Expr_add_child(body, _t3202);
    }
    Token *_t3205 = expect_token(p, TokenType_RBrace());
    (void)_t3205;
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
        TokenType *_sw3206 = TokenType_clone(&kw->type);
        (void)_sw3206;
        Bool _t3218; { Bool *_hp = (Bool *)TokenType_eq(_sw3206, TokenType_KwFunc()); _t3218 = *_hp; free(_hp); }
        (void)_t3218;
        if (_t3218) {
            ft = FuncType_clone(FuncType_Func());
        } else {
            Bool _t3217; { Bool *_hp = (Bool *)TokenType_eq(_sw3206, TokenType_KwProc()); _t3217 = *_hp; free(_hp); }
            (void)_t3217;
            if (_t3217) {
                ft = FuncType_clone(FuncType_Proc());
            } else {
                Bool _t3216; { Bool *_hp = (Bool *)TokenType_eq(_sw3206, TokenType_KwTest()); _t3216 = *_hp; free(_hp); }
                (void)_t3216;
                if (_t3216) {
                    ft = FuncType_clone(FuncType_Test());
                } else {
                    Bool _t3215; { Bool *_hp = (Bool *)TokenType_eq(_sw3206, TokenType_KwMacro()); _t3215 = *_hp; free(_hp); }
                    (void)_t3215;
                    if (_t3215) {
                        ft = FuncType_clone(FuncType_Macro());
                    } else {
                        Bool _t3214; { Bool *_hp = (Bool *)TokenType_eq(_sw3206, TokenType_KwExtFunc()); _t3214 = *_hp; free(_hp); }
                        (void)_t3214;
                        if (_t3214) {
                            ft = FuncType_clone(FuncType_ExtFunc());
                        } else {
                            Bool _t3213; { Bool *_hp = (Bool *)TokenType_eq(_sw3206, TokenType_KwExtProc()); _t3213 = *_hp; free(_hp); }
                            (void)_t3213;
                            if (_t3213) {
                                ft = FuncType_clone(FuncType_ExtProc());
                            } else {
                                Str *_t3207 = Str_lit("Str", 3ULL);
                                (void)_t3207;
                                U64 _t3208; { U64 *_hp = (U64 *)Str_size(); _t3208 = *_hp; free(_hp); }
                                (void)_t3208;
                                U64 _t3209 = 1;
                                (void)_t3209;
                                Array *_va56 = Array_new(_t3207, &(U64){_t3208}, &(U64){_t3209});
                                (void)_va56;
                                Str_delete(_t3207, &(Bool){1});
                                ;
                                ;
                                U64 _t3210 = 0;
                                (void)_t3210;
                                Str *_t3211 = Str_lit("expected function keyword", 25ULL);
                                (void)_t3211;
                                Array_set(_va56, &(U64){_t3210}, _t3211);
                                ;
                                Str *_t3212 = Str_lit("src/self/parser.til:136:17", 26ULL);
                                (void)_t3212;
                                panic(_t3212, _va56);
                                Str_delete(_t3212, &(Bool){1});
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
        TokenType_delete(_sw3206, &(Bool){1});
        ;
    }
    Token *_t3412 = expect_token(p, TokenType_LParen());
    (void)_t3412;
    Str *_t3413 = Str_lit("Str", 3ULL);
    (void)_t3413;
    U64 _t3414; { U64 *_hp = (U64 *)Str_size(); _t3414 = *_hp; free(_hp); }
    (void)_t3414;
    Str *_t3415 = Str_lit("Str", 3ULL);
    (void)_t3415;
    U64 _t3416; { U64 *_hp = (U64 *)Str_size(); _t3416 = *_hp; free(_hp); }
    (void)_t3416;
    Str *_t3417 = Str_lit("Bool", 4ULL);
    (void)_t3417;
    U64 _t3418; { U64 *_hp = (U64 *)Bool_size(); _t3418 = *_hp; free(_hp); }
    (void)_t3418;
    Str *_t3419 = Str_lit("Bool", 4ULL);
    (void)_t3419;
    U64 _t3420; { U64 *_hp = (U64 *)Bool_size(); _t3420 = *_hp; free(_hp); }
    (void)_t3420;
    Str *_t3421 = Str_lit("Bool", 4ULL);
    (void)_t3421;
    U64 _t3422; { U64 *_hp = (U64 *)Bool_size(); _t3422 = *_hp; free(_hp); }
    (void)_t3422;
    Str *_t3423 = Str_lit("I64", 3ULL);
    (void)_t3423;
    U64 _t3424; { U64 *_hp = (U64 *)I64_size(); _t3424 = *_hp; free(_hp); }
    (void)_t3424;
    Str *_t3425 = Str_lit("I64", 3ULL);
    (void)_t3425;
    U64 _t3426; { U64 *_hp = (U64 *)I64_size(); _t3426 = *_hp; free(_hp); }
    (void)_t3426;
    I64 _t3427 = 0;
    (void)_t3427;
    I64 _t3428 = 1;
    (void)_t3428;
    I64 _t3429 = I64_sub(_t3427, _t3428);
    (void)_t3429;
    ;
    ;
    I64 _t3430 = 0;
    (void)_t3430;
    I64 _t3431 = 1;
    (void)_t3431;
    I64 _t3432 = I64_sub(_t3430, _t3431);
    (void)_t3432;
    ;
    ;
    U32 _t3433 = 0;
    (void)_t3433;
    I32 _t3434 = I64_to_i32(_t3429);
    (void)_t3434;
    ;
    I32 _t3435 = I64_to_i32(_t3432);
    (void)_t3435;
    ;
    Bool _t3436 = 0;
    (void)_t3436;
    Bool _t3437 = 0;
    (void)_t3437;
    FunctionDef *fd = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(FuncType_Func()); fd->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3413, &(U64){_t3414}); fd->param_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3415, &(U64){_t3416}); fd->param_types = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3417, &(U64){_t3418}); fd->param_muts = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3419, &(U64){_t3420}); fd->param_owns = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3421, &(U64){_t3422}); fd->param_shallows = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3423, &(U64){_t3424}); fd->param_fn_sigs = *_ca; free(_ca); }
    fd->nparam = _t3433;
    { Vec *_ca = Vec_new(_t3425, &(U64){_t3426}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3434;
    fd->kwargs_index = _t3435;
    fd->return_is_ref = _t3436;
    fd->return_is_shallow = _t3437;
    (void)fd;
    Str_delete(_t3413, &(Bool){1});
    ;
    Str_delete(_t3415, &(Bool){1});
    ;
    Str_delete(_t3417, &(Bool){1});
    ;
    Str_delete(_t3419, &(Bool){1});
    ;
    Str_delete(_t3421, &(Bool){1});
    ;
    Str_delete(_t3423, &(Bool){1});
    ;
    Str_delete(_t3425, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    FuncType_delete(&fd->func_type, &(Bool){0});
    { FuncType *_fa = FuncType_clone(ft); fd->func_type = *_fa; free(_fa); }
    Str *_t3438 = Str_lit("Expr", 4ULL);
    (void)_t3438;
    U64 _t3439; { U64 *_hp = (U64 *)Expr_size(); _t3439 = *_hp; free(_hp); }
    (void)_t3439;
    Vec *def_exprs = Vec_new(_t3438, &(U64){_t3439});
    (void)def_exprs;
    Str_delete(_t3438, &(Bool){1});
    ;
    while (1) {
        Bool _t3337 = check(p, TokenType_RParen());
        (void)_t3337;
        Bool _t3338 = check(p, TokenType_Eof());
        (void)_t3338;
        Bool _t3339 = Bool_not(_t3337);
        (void)_t3339;
        ;
        Bool _t3340 = Bool_not(_t3338);
        (void)_t3340;
        ;
        Bool _wcond3219 = Bool_and(_t3339, _t3340);
        (void)_wcond3219;
        ;
        ;
        if (_wcond3219) {
        } else {
            ;
            break;
        }
        ;
        Bool is_shallow = 0;
        (void)is_shallow;
        Bool _t3341 = check(p, TokenType_KwShallow());
        (void)_t3341;
        if (_t3341) {
            Token *_t3220 = advance(p);
            (void)_t3220;
            Bool _t3221 = 1;
            (void)_t3221;
            is_shallow = _t3221;
            ;
        }
        ;
        Bool is_own = 0;
        (void)is_own;
        Bool _t3342 = check(p, TokenType_KwOwn());
        (void)_t3342;
        if (_t3342) {
            Token *_t3222 = advance(p);
            (void)_t3222;
            Bool _t3223 = 1;
            (void)_t3223;
            is_own = _t3223;
            ;
        }
        ;
        Bool is_mut = 0;
        (void)is_mut;
        Bool _t3343 = check(p, TokenType_KwMut());
        (void)_t3343;
        if (_t3343) {
            Token *_t3224 = advance(p);
            (void)_t3224;
            Bool _t3225 = 1;
            (void)_t3225;
            is_mut = _t3225;
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
        Bool _t3344 = check(p, TokenType_Colon());
        (void)_t3344;
        Bool _t3345 = Bool_not(_t3344);
        (void)_t3345;
        ;
        if (_t3345) {
            tp = Str_clone(pname);
            nm = Str_lit("", 0ULL);
        } else {
            Token *_t3319 = expect_token(p, TokenType_Colon());
            (void)_t3319;
            Bool _t3320 = check(p, TokenType_DotDotDot());
            (void)_t3320;
            if (_t3320) {
                Token *_t3256 = advance(p);
                (void)_t3256;
                Bool _t3257 = Bool_or(is_own, is_mut);
                (void)_t3257;
                Bool _t3258 = Bool_or(_t3257, is_shallow);
                (void)_t3258;
                ;
                if (_t3258) {
                    Str *_t3226 = Str_lit("Str", 3ULL);
                    (void)_t3226;
                    U64 _t3227; { U64 *_hp = (U64 *)Str_size(); _t3227 = *_hp; free(_hp); }
                    (void)_t3227;
                    U64 _t3228 = 6;
                    (void)_t3228;
                    Array *_va57 = Array_new(_t3226, &(U64){_t3227}, &(U64){_t3228});
                    (void)_va57;
                    Str_delete(_t3226, &(Bool){1});
                    ;
                    ;
                    U64 _t3229 = 0;
                    (void)_t3229;
                    Str *_t3230 = Str_clone(&p->path);
                    (void)_t3230;
                    Array_set(_va57, &(U64){_t3229}, _t3230);
                    ;
                    U64 _t3231 = 1;
                    (void)_t3231;
                    Str *_t3232 = Str_lit(":", 1ULL);
                    (void)_t3232;
                    Array_set(_va57, &(U64){_t3231}, _t3232);
                    ;
                    U32 _t3233 = peek_line(p);
                    (void)_t3233;
                    U64 _t3234 = 2;
                    (void)_t3234;
                    Str *_t3235 = U32_to_str(&(U32){_t3233});
                    (void)_t3235;
                    ;
                    Array_set(_va57, &(U64){_t3234}, _t3235);
                    ;
                    U64 _t3236 = 3;
                    (void)_t3236;
                    Str *_t3237 = Str_lit(":", 1ULL);
                    (void)_t3237;
                    Array_set(_va57, &(U64){_t3236}, _t3237);
                    ;
                    U32 _t3238 = peek_col(p);
                    (void)_t3238;
                    U64 _t3239 = 4;
                    (void)_t3239;
                    Str *_t3240 = U32_to_str(&(U32){_t3238});
                    (void)_t3240;
                    ;
                    Array_set(_va57, &(U64){_t3239}, _t3240);
                    ;
                    U64 _t3241 = 5;
                    (void)_t3241;
                    Str *_t3242 = Str_lit(": kwargs parameter cannot be own/mut/shallow", 44ULL);
                    (void)_t3242;
                    Array_set(_va57, &(U64){_t3241}, _t3242);
                    ;
                    Str *_t3243 = Str_lit("src/self/parser.til:167:27", 26ULL);
                    (void)_t3243;
                    panic(_t3243, _va57);
                    Str_delete(_t3243, &(Bool){1});
                }
                ;
                I64 _t3259 = 0;
                (void)_t3259;
                I64 _t3260 = 1;
                (void)_t3260;
                I64 _t3261 = I64_sub(_t3259, _t3260);
                (void)_t3261;
                ;
                ;
                I32 _t3262 = I64_to_i32(_t3261);
                (void)_t3262;
                ;
                Bool _t3263; { Bool *_hp = (Bool *)I32_neq(&fd->kwargs_index, &(I32){_t3262}); _t3263 = *_hp; free(_hp); }
                (void)_t3263;
                ;
                if (_t3263) {
                    Str *_t3244 = Str_lit("Str", 3ULL);
                    (void)_t3244;
                    U64 _t3245; { U64 *_hp = (U64 *)Str_size(); _t3245 = *_hp; free(_hp); }
                    (void)_t3245;
                    U64 _t3246 = 1;
                    (void)_t3246;
                    Array *_va58 = Array_new(_t3244, &(U64){_t3245}, &(U64){_t3246});
                    (void)_va58;
                    Str_delete(_t3244, &(Bool){1});
                    ;
                    ;
                    U64 _t3247 = 0;
                    (void)_t3247;
                    Str *_t3248 = Str_lit("only one kwargs parameter is allowed", 36ULL);
                    (void)_t3248;
                    Array_set(_va58, &(U64){_t3247}, _t3248);
                    ;
                    Str *_t3249 = Str_lit("src/self/parser.til:171:27", 26ULL);
                    (void)_t3249;
                    panic(_t3249, _va58);
                    Str_delete(_t3249, &(Bool){1});
                }
                ;
                I64 _t3264 = 0;
                (void)_t3264;
                I64 _t3265 = 1;
                (void)_t3265;
                I64 _t3266 = I64_sub(_t3264, _t3265);
                (void)_t3266;
                ;
                ;
                I32 _t3267 = I64_to_i32(_t3266);
                (void)_t3267;
                ;
                Bool _t3268; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3267}); _t3268 = *_hp; free(_hp); }
                (void)_t3268;
                ;
                if (_t3268) {
                    Str *_t3250 = Str_lit("Str", 3ULL);
                    (void)_t3250;
                    U64 _t3251; { U64 *_hp = (U64 *)Str_size(); _t3251 = *_hp; free(_hp); }
                    (void)_t3251;
                    U64 _t3252 = 1;
                    (void)_t3252;
                    Array *_va59 = Array_new(_t3250, &(U64){_t3251}, &(U64){_t3252});
                    (void)_va59;
                    Str_delete(_t3250, &(Bool){1});
                    ;
                    ;
                    U64 _t3253 = 0;
                    (void)_t3253;
                    Str *_t3254 = Str_lit("cannot combine variadic and kwargs in the same function", 55ULL);
                    (void)_t3254;
                    Array_set(_va59, &(U64){_t3253}, _t3254);
                    ;
                    Str *_t3255 = Str_lit("src/self/parser.til:174:27", 26ULL);
                    (void)_t3255;
                    panic(_t3255, _va59);
                    Str_delete(_t3255, &(Bool){1});
                }
                ;
                U64 _t3269; { U64 *_hp = (U64 *)Vec_len(&fd->param_names); _t3269 = *_hp; free(_hp); }
                (void)_t3269;
                I64 _t3270 = U64_to_i64(_t3269);
                (void)_t3270;
                ;
                I32 _t3271 = I64_to_i32(_t3270);
                (void)_t3271;
                ;
                fd->kwargs_index = _t3271;
                ;
                Bool _t3272 = 1;
                (void)_t3272;
                is_own = _t3272;
                ;
                nm = Str_clone(pname);
                tp = Str_lit("Map", 3ULL);
            } else {
                Bool _t3318 = check(p, TokenType_DotDot());
                (void)_t3318;
                if (_t3318) {
                    Token *_t3303 = advance(p);
                    (void)_t3303;
                    if (is_own) {
                        Str *_t3273 = Str_lit("Str", 3ULL);
                        (void)_t3273;
                        U64 _t3274; { U64 *_hp = (U64 *)Str_size(); _t3274 = *_hp; free(_hp); }
                        (void)_t3274;
                        U64 _t3275 = 1;
                        (void)_t3275;
                        Array *_va60 = Array_new(_t3273, &(U64){_t3274}, &(U64){_t3275});
                        (void)_va60;
                        Str_delete(_t3273, &(Bool){1});
                        ;
                        ;
                        U64 _t3276 = 0;
                        (void)_t3276;
                        Str *_t3277 = Str_lit("variadic param cannot be 'own'", 30ULL);
                        (void)_t3277;
                        Array_set(_va60, &(U64){_t3276}, _t3277);
                        ;
                        Str *_t3278 = Str_lit("src/self/parser.til:182:35", 26ULL);
                        (void)_t3278;
                        panic(_t3278, _va60);
                        Str_delete(_t3278, &(Bool){1});
                    }
                    if (is_mut) {
                        Str *_t3279 = Str_lit("Str", 3ULL);
                        (void)_t3279;
                        U64 _t3280; { U64 *_hp = (U64 *)Str_size(); _t3280 = *_hp; free(_hp); }
                        (void)_t3280;
                        U64 _t3281 = 1;
                        (void)_t3281;
                        Array *_va61 = Array_new(_t3279, &(U64){_t3280}, &(U64){_t3281});
                        (void)_va61;
                        Str_delete(_t3279, &(Bool){1});
                        ;
                        ;
                        U64 _t3282 = 0;
                        (void)_t3282;
                        Str *_t3283 = Str_lit("variadic param cannot be 'mut'", 30ULL);
                        (void)_t3283;
                        Array_set(_va61, &(U64){_t3282}, _t3283);
                        ;
                        Str *_t3284 = Str_lit("src/self/parser.til:183:35", 26ULL);
                        (void)_t3284;
                        panic(_t3284, _va61);
                        Str_delete(_t3284, &(Bool){1});
                    }
                    if (is_shallow) {
                        Str *_t3285 = Str_lit("Str", 3ULL);
                        (void)_t3285;
                        U64 _t3286; { U64 *_hp = (U64 *)Str_size(); _t3286 = *_hp; free(_hp); }
                        (void)_t3286;
                        U64 _t3287 = 1;
                        (void)_t3287;
                        Array *_va62 = Array_new(_t3285, &(U64){_t3286}, &(U64){_t3287});
                        (void)_va62;
                        Str_delete(_t3285, &(Bool){1});
                        ;
                        ;
                        U64 _t3288 = 0;
                        (void)_t3288;
                        Str *_t3289 = Str_lit("variadic param cannot be 'shallow'", 34ULL);
                        (void)_t3289;
                        Array_set(_va62, &(U64){_t3288}, _t3289);
                        ;
                        Str *_t3290 = Str_lit("src/self/parser.til:184:39", 26ULL);
                        (void)_t3290;
                        panic(_t3290, _va62);
                        Str_delete(_t3290, &(Bool){1});
                    }
                    I64 _t3304 = 0;
                    (void)_t3304;
                    I64 _t3305 = 1;
                    (void)_t3305;
                    I64 _t3306 = I64_sub(_t3304, _t3305);
                    (void)_t3306;
                    ;
                    ;
                    I32 _t3307 = I64_to_i32(_t3306);
                    (void)_t3307;
                    ;
                    Bool _t3308; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3307}); _t3308 = *_hp; free(_hp); }
                    (void)_t3308;
                    ;
                    if (_t3308) {
                        Str *_t3291 = Str_lit("Str", 3ULL);
                        (void)_t3291;
                        U64 _t3292; { U64 *_hp = (U64 *)Str_size(); _t3292 = *_hp; free(_hp); }
                        (void)_t3292;
                        U64 _t3293 = 1;
                        (void)_t3293;
                        Array *_va63 = Array_new(_t3291, &(U64){_t3292}, &(U64){_t3293});
                        (void)_va63;
                        Str_delete(_t3291, &(Bool){1});
                        ;
                        ;
                        U64 _t3294 = 0;
                        (void)_t3294;
                        Str *_t3295 = Str_lit("only one variadic param allowed", 31ULL);
                        (void)_t3295;
                        Array_set(_va63, &(U64){_t3294}, _t3295);
                        ;
                        Str *_t3296 = Str_lit("src/self/parser.til:185:69", 26ULL);
                        (void)_t3296;
                        panic(_t3296, _va63);
                        Str_delete(_t3296, &(Bool){1});
                    }
                    ;
                    I64 _t3309 = 0;
                    (void)_t3309;
                    I64 _t3310 = 1;
                    (void)_t3310;
                    I64 _t3311 = I64_sub(_t3309, _t3310);
                    (void)_t3311;
                    ;
                    ;
                    I32 _t3312 = I64_to_i32(_t3311);
                    (void)_t3312;
                    ;
                    Bool _t3313; { Bool *_hp = (Bool *)I32_neq(&fd->kwargs_index, &(I32){_t3312}); _t3313 = *_hp; free(_hp); }
                    (void)_t3313;
                    ;
                    if (_t3313) {
                        Str *_t3297 = Str_lit("Str", 3ULL);
                        (void)_t3297;
                        U64 _t3298; { U64 *_hp = (U64 *)Str_size(); _t3298 = *_hp; free(_hp); }
                        (void)_t3298;
                        U64 _t3299 = 1;
                        (void)_t3299;
                        Array *_va64 = Array_new(_t3297, &(U64){_t3298}, &(U64){_t3299});
                        (void)_va64;
                        Str_delete(_t3297, &(Bool){1});
                        ;
                        ;
                        U64 _t3300 = 0;
                        (void)_t3300;
                        Str *_t3301 = Str_lit("cannot combine variadic and kwargs in the same function", 55ULL);
                        (void)_t3301;
                        Array_set(_va64, &(U64){_t3300}, _t3301);
                        ;
                        Str *_t3302 = Str_lit("src/self/parser.til:187:27", 26ULL);
                        (void)_t3302;
                        panic(_t3302, _va64);
                        Str_delete(_t3302, &(Bool){1});
                    }
                    ;
                    U64 _t3314; { U64 *_hp = (U64 *)Vec_len(&fd->param_names); _t3314 = *_hp; free(_hp); }
                    (void)_t3314;
                    I64 _t3315 = U64_to_i64(_t3314);
                    (void)_t3315;
                    ;
                    I32 _t3316 = I64_to_i32(_t3315);
                    (void)_t3316;
                    ;
                    fd->variadic_index = _t3316;
                    ;
                    Bool _t3317 = 1;
                    (void)_t3317;
                    is_variadic = _t3317;
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
        I64 _t3346 = 0;
        (void)_t3346;
        I64 _t3347 = 1;
        (void)_t3347;
        I64 fn_sig_idx = I64_sub(_t3346, _t3347);
        (void)fn_sig_idx;
        ;
        ;
        Str *_t3348 = Str_lit("Fn", 2ULL);
        (void)_t3348;
        Bool _t3349; { Bool *_hp = (Bool *)Str_eq(tp, _t3348); _t3349 = *_hp; free(_hp); }
        (void)_t3349;
        Str_delete(_t3348, &(Bool){1});
        if (_t3349) {
            U32 _t3323 = peek_line(p);
            (void)_t3323;
            U32 _t3324 = peek_col(p);
            (void)_t3324;
            Expr *sig = parse_fn_signature(p, _t3323, _t3324);
            (void)sig;
            ;
            ;
            U32 _t3325 = 0;
            (void)_t3325;
            Bool _t3326; { Bool *_hp = (Bool *)U32_neq(&sig->line, &(U32){_t3325}); _t3326 = *_hp; free(_hp); }
            (void)_t3326;
            ;
            if (_t3326) {
                U64 _t3321; { U64 *_hp = (U64 *)Vec_len(def_exprs); _t3321 = *_hp; free(_hp); }
                (void)_t3321;
                I64 _t3322 = U64_to_i64(_t3321);
                (void)_t3322;
                ;
                fn_sig_idx = _t3322;
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
        I64 _t3350 = 0;
        (void)_t3350;
        I64 _t3351 = 1;
        (void)_t3351;
        I64 has_default = I64_sub(_t3350, _t3351);
        (void)has_default;
        ;
        ;
        Bool _t3352 = check(p, TokenType_Eq());
        (void)_t3352;
        if (_t3352) {
            Token *_t3327 = advance(p);
            (void)_t3327;
            U64 _t3328; { U64 *_hp = (U64 *)Vec_len(def_exprs); _t3328 = *_hp; free(_hp); }
            (void)_t3328;
            I64 _t3329 = U64_to_i64(_t3328);
            (void)_t3329;
            ;
            has_default = _t3329;
            ;
            Expr *def_expr = parse_expression(p);
            (void)def_expr;
            Vec_push(def_exprs, def_expr);
        }
        ;
        I64 _t3353 = 0;
        (void)_t3353;
        I64 _t3354 = 1;
        (void)_t3354;
        I64 _t3355 = I64_sub(_t3353, _t3354);
        (void)_t3355;
        ;
        ;
        I32 _t3356 = I64_to_i32(_t3355);
        (void)_t3356;
        ;
        Bool _t3357; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3356}); _t3357 = *_hp; free(_hp); }
        (void)_t3357;
        ;
        Bool _t3358 = Bool_not(is_variadic);
        (void)_t3358;
        ;
        I64 _t3359 = 0;
        (void)_t3359;
        I64 _t3360 = 1;
        (void)_t3360;
        I64 _t3361 = I64_sub(_t3359, _t3360);
        (void)_t3361;
        ;
        ;
        Bool _t3362 = Bool_and(_t3357, _t3358);
        (void)_t3362;
        ;
        ;
        Bool _t3363 = I64_eq(has_default, _t3361);
        (void)_t3363;
        ;
        Bool _t3364 = Bool_and(_t3362, _t3363);
        (void)_t3364;
        ;
        ;
        if (_t3364) {
            Str *_t3330 = Str_lit("Str", 3ULL);
            (void)_t3330;
            U64 _t3331; { U64 *_hp = (U64 *)Str_size(); _t3331 = *_hp; free(_hp); }
            (void)_t3331;
            U64 _t3332 = 1;
            (void)_t3332;
            Array *_va65 = Array_new(_t3330, &(U64){_t3331}, &(U64){_t3332});
            (void)_va65;
            Str_delete(_t3330, &(Bool){1});
            ;
            ;
            U64 _t3333 = 0;
            (void)_t3333;
            Str *_t3334 = Str_lit("positional param not allowed after variadic", 43ULL);
            (void)_t3334;
            Array_set(_va65, &(U64){_t3333}, _t3334);
            ;
            Str *_t3335 = Str_lit("src/self/parser.til:226:19", 26ULL);
            (void)_t3335;
            panic(_t3335, _va65);
            Str_delete(_t3335, &(Bool){1});
        }
        ;
        Vec_push(&fd->param_defaults, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = has_default; _oa; }));
        Bool _t3365 = check(p, TokenType_Comma());
        (void)_t3365;
        if (_t3365) {
            Token *_t3336 = advance(p);
            (void)_t3336;
        }
        ;
    }
    Token *_t3440 = expect_token(p, TokenType_RParen());
    (void)_t3440;
    Bool _t3441 = check(p, TokenType_KwReturns());
    (void)_t3441;
    if (_t3441) {
        Token *_t3371 = advance(p);
        (void)_t3371;
        Bool _t3372 = check(p, TokenType_KwRef());
        (void)_t3372;
        if (_t3372) {
            Token *_t3366 = advance(p);
            (void)_t3366;
            Bool _t3367 = 1;
            (void)_t3367;
            fd->return_is_ref = _t3367;
            ;
        } else {
            Bool _t3370 = check(p, TokenType_KwShallow());
            (void)_t3370;
            if (_t3370) {
                Token *_t3368 = advance(p);
                (void)_t3368;
                Bool _t3369 = 1;
                (void)_t3369;
                fd->return_is_shallow = _t3369;
                ;
            }
            ;
        }
        ;
        Str_delete(&fd->return_type, &(Bool){0});
        { Str *_fa = expect_text(p, TokenType_Ident()); fd->return_type = *_fa; free(_fa); }
    }
    ;
    U64 _t3442; { U64 *_hp = (U64 *)Vec_len(&fd->param_names); _t3442 = *_hp; free(_hp); }
    (void)_t3442;
    I64 _t3443 = U64_to_i64(_t3442);
    (void)_t3443;
    ;
    U32 _t3444 = I64_to_u32(_t3443);
    (void)_t3444;
    ;
    fd->nparam = _t3444;
    ;
    ExprData *_t3445 = ExprData_FuncDef(fd);
    (void)_t3445;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *def = Expr_new(_t3445, kw_line, kw_col, &p->path);
    (void)def;
    ExprData_delete(_t3445, &(Bool){1});
    Bool _t3446 = check(p, TokenType_LBrace());
    (void)_t3446;
    if (_t3446) {
        Token *_t3373 = expect_token(p, TokenType_LBrace());
        (void)_t3373;
        Expr *_t3374 = parse_block(p);
        (void)_t3374;
        Expr_add_child(def, _t3374);
    } else {
        Bool _t3395; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Func()); _t3395 = *_hp; free(_hp); }
        (void)_t3395;
        Bool _t3396; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Proc()); _t3396 = *_hp; free(_hp); }
        (void)_t3396;
        Bool _t3397 = Bool_not(_t3395);
        (void)_t3397;
        ;
        Bool _t3398 = Bool_not(_t3396);
        (void)_t3398;
        ;
        Bool _t3399 = Bool_and(_t3397, _t3398);
        (void)_t3399;
        ;
        ;
        if (_t3399) {
            Str *_t3375 = Str_lit("Str", 3ULL);
            (void)_t3375;
            U64 _t3376; { U64 *_hp = (U64 *)Str_size(); _t3376 = *_hp; free(_hp); }
            (void)_t3376;
            U64 _t3377 = 8;
            (void)_t3377;
            Array *_va66 = Array_new(_t3375, &(U64){_t3376}, &(U64){_t3377});
            (void)_va66;
            Str_delete(_t3375, &(Bool){1});
            ;
            ;
            U64 _t3378 = 0;
            (void)_t3378;
            Str *_t3379 = Str_clone(&p->path);
            (void)_t3379;
            Array_set(_va66, &(U64){_t3378}, _t3379);
            ;
            U64 _t3380 = 1;
            (void)_t3380;
            Str *_t3381 = Str_lit(":", 1ULL);
            (void)_t3381;
            Array_set(_va66, &(U64){_t3380}, _t3381);
            ;
            U64 _t3382 = 2;
            (void)_t3382;
            Str *_t3383 = U32_to_str(&(U32){kw_line});
            (void)_t3383;
            Array_set(_va66, &(U64){_t3382}, _t3383);
            ;
            U64 _t3384 = 3;
            (void)_t3384;
            Str *_t3385 = Str_lit(":", 1ULL);
            (void)_t3385;
            Array_set(_va66, &(U64){_t3384}, _t3385);
            ;
            U64 _t3386 = 4;
            (void)_t3386;
            Str *_t3387 = U32_to_str(&(U32){kw_col});
            (void)_t3387;
            Array_set(_va66, &(U64){_t3386}, _t3387);
            ;
            U64 _t3388 = 5;
            (void)_t3388;
            Str *_t3389 = Str_lit(": ", 2ULL);
            (void)_t3389;
            Array_set(_va66, &(U64){_t3388}, _t3389);
            ;
            U64 _t3390 = 6;
            (void)_t3390;
            Str *_t3391 = func_type_name(ft);
            (void)_t3391;
            Array_set(_va66, &(U64){_t3390}, _t3391);
            ;
            U64 _t3392 = 7;
            (void)_t3392;
            Str *_t3393 = Str_lit(" requires a body", 16ULL);
            (void)_t3393;
            Array_set(_va66, &(U64){_t3392}, _t3393);
            ;
            Str *_t3394 = Str_lit("src/self/parser.til:255:19", 26ULL);
            (void)_t3394;
            panic(_t3394, _va66);
            Str_delete(_t3394, &(Bool){1});
        }
        ;
    }
    ;
    FuncType_delete(ft, &(Bool){1});
    ;
    ;
    {
        U64 _fi3400 = 0;
        (void)_fi3400;
        while (1) {
            U64 _t3402 = 0;
            (void)_t3402;
            U64 _t3403; { U64 *_hp = (U64 *)Vec_len(def_exprs); _t3403 = *_hp; free(_hp); }
            (void)_t3403;
            Range *_t3404 = Range_new(_t3402, _t3403);
            (void)_t3404;
            ;
            ;
            U64 _t3405; { U64 *_hp = (U64 *)Range_len(_t3404); _t3405 = *_hp; free(_hp); }
            (void)_t3405;
            Range_delete(_t3404, &(Bool){1});
            Bool _wcond3401; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3400}, &(U64){_t3405}); _wcond3401 = *_hp; free(_hp); }
            (void)_wcond3401;
            ;
            if (_wcond3401) {
            } else {
                ;
                break;
            }
            ;
            U64 _t3406 = 0;
            (void)_t3406;
            U64 _t3407; { U64 *_hp = (U64 *)Vec_len(def_exprs); _t3407 = *_hp; free(_hp); }
            (void)_t3407;
            Range *_t3408 = Range_new(_t3406, _t3407);
            (void)_t3408;
            ;
            ;
            U64 *i = Range_get(_t3408, _fi3400);
            (void)i;
            Range_delete(_t3408, &(Bool){1});
            U64 _t3409 = 1;
            (void)_t3409;
            U64 _t3410 = U64_add(_fi3400, _t3409);
            (void)_t3410;
            ;
            _fi3400 = _t3410;
            ;
            Expr *de = Vec_get(def_exprs, i);
            (void)de;
            Expr *_t3411 = Expr_clone(de);
            (void)_t3411;
            U64_delete(i, &(Bool){1});
            Expr_add_child(def, _t3411);
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
    Token *_t3460 = advance(p);
    (void)_t3460;
    Expr *def = Expr_new(ExprData_StructDef(), kw_line, kw_col, &p->path);
    (void)def;
    ;
    ;
    Bool _t3461 = Bool_clone(&(Bool){is_ext});
    (void)_t3461;
    ;
    def->is_ext = _t3461;
    ;
    Token *_t3462 = expect_token(p, TokenType_LBrace());
    (void)_t3462;
    U32 _t3463 = peek_line(p);
    (void)_t3463;
    U32 _t3464 = peek_col(p);
    (void)_t3464;
    Expr *body = Expr_new(ExprData_Body(), _t3463, _t3464, &p->path);
    (void)body;
    ;
    ;
    Bool in_namespace = 0;
    (void)in_namespace;
    while (1) {
        Bool _t3453 = check(p, TokenType_RBrace());
        (void)_t3453;
        Bool _t3454 = check(p, TokenType_Eof());
        (void)_t3454;
        Bool _t3455 = Bool_not(_t3453);
        (void)_t3455;
        ;
        Bool _t3456 = Bool_not(_t3454);
        (void)_t3456;
        ;
        Bool _wcond3447 = Bool_and(_t3455, _t3456);
        (void)_wcond3447;
        ;
        ;
        if (_wcond3447) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3457 = check(p, TokenType_KwNamespace());
        (void)_t3457;
        if (_t3457) {
            Token *_t3448 = advance(p);
            (void)_t3448;
            Token *_t3449 = expect_token(p, TokenType_Colon());
            (void)_t3449;
            Bool _t3450 = 1;
            (void)_t3450;
            in_namespace = _t3450;
            ;
            ;
            continue;
        }
        ;
        Expr *stmt = parse_statement(p);
        (void)stmt;
        Bool _t3458; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3458 = *_hp; free(_hp); }
        (void)_t3458;
        Bool _t3459 = Bool_and(in_namespace, _t3458);
        (void)_t3459;
        ;
        if (_t3459) {
            Bool _t3452; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3452 = *_hp; free(_hp); }
            (void)_t3452;
            if (_t3452) {
                Declaration *dd = ExprData_get_Decl(&stmt->data);
                (void)dd;
                Bool _t3451 = 1;
                (void)_t3451;
                dd->is_namespace = _t3451;
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
    Token *_t3465 = expect_token(p, TokenType_RBrace());
    (void)_t3465;
    Expr_add_child(def, body);
    return def;
}

Expr * parse_enum_def(Parser * p) {
    (void)p;
    U32 kw_line = peek_line(p);
    (void)kw_line;
    U32 kw_col = peek_col(p);
    (void)kw_col;
    Token *_t3489 = advance(p);
    (void)_t3489;
    Expr *def = Expr_new(ExprData_EnumDef(), kw_line, kw_col, &p->path);
    (void)def;
    ;
    ;
    Token *_t3490 = expect_token(p, TokenType_LBrace());
    (void)_t3490;
    U32 _t3491 = peek_line(p);
    (void)_t3491;
    U32 _t3492 = peek_col(p);
    (void)_t3492;
    Expr *body = Expr_new(ExprData_Body(), _t3491, _t3492, &p->path);
    (void)body;
    ;
    ;
    Bool in_namespace = 0;
    (void)in_namespace;
    while (1) {
        Bool _t3484 = check(p, TokenType_RBrace());
        (void)_t3484;
        Bool _t3485 = check(p, TokenType_Eof());
        (void)_t3485;
        Bool _t3486 = Bool_not(_t3484);
        (void)_t3486;
        ;
        Bool _t3487 = Bool_not(_t3485);
        (void)_t3487;
        ;
        Bool _wcond3466 = Bool_and(_t3486, _t3487);
        (void)_wcond3466;
        ;
        ;
        if (_wcond3466) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3488 = check(p, TokenType_KwNamespace());
        (void)_t3488;
        if (_t3488) {
            Token *_t3467 = advance(p);
            (void)_t3467;
            Token *_t3468 = expect_token(p, TokenType_Colon());
            (void)_t3468;
            Bool _t3469 = 1;
            (void)_t3469;
            in_namespace = _t3469;
            ;
            ;
            continue;
        }
        ;
        if (in_namespace) {
            Expr *stmt = parse_statement(p);
            (void)stmt;
            Bool _t3472; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3472 = *_hp; free(_hp); }
            (void)_t3472;
            if (_t3472) {
                Bool _t3471; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3471 = *_hp; free(_hp); }
                (void)_t3471;
                if (_t3471) {
                    Declaration *dd = ExprData_get_Decl(&stmt->data);
                    (void)dd;
                    Bool _t3470 = 1;
                    (void)_t3470;
                    dd->is_namespace = _t3470;
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
            Bool _t3475 = 0;
            (void)_t3475;
            Bool _t3476 = 0;
            (void)_t3476;
            Bool _t3477 = 0;
            (void)_t3477;
            Bool _t3478 = 0;
            (void)_t3478;
            I32 _t3479 = 0;
            (void)_t3479;
            I32 _t3480 = 0;
            (void)_t3480;
            Declaration *dd = malloc(sizeof(Declaration));
            { Str *_ca = Str_clone(vname); dd->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
            dd->is_mut = _t3475;
            dd->is_namespace = _t3476;
            dd->is_ref = _t3477;
            dd->is_own = _t3478;
            dd->field_offset = _t3479;
            dd->field_size = _t3480;
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
            Bool _t3481 = check(p, TokenType_Colon());
            (void)_t3481;
            if (_t3481) {
                Token *_t3473 = advance(p);
                (void)_t3473;
                Str_delete(&dd->explicit_type, &(Bool){0});
                { Str *_fa = expect_text(p, TokenType_Ident()); dd->explicit_type = *_fa; free(_fa); }
            }
            ;
            ExprData *_t3482 = ExprData_Decl(dd);
            (void)_t3482;
            Declaration_delete(dd, &(Bool){1});
            Expr *variant = Expr_new(_t3482, v_line, v_col, &p->path);
            (void)variant;
            ExprData_delete(_t3482, &(Bool){1});
            ;
            ;
            Expr_add_child(body, variant);
            Bool _t3483 = check(p, TokenType_Comma());
            (void)_t3483;
            if (_t3483) {
                Token *_t3474 = advance(p);
                (void)_t3474;
            }
            ;
        }
    }
    ;
    Token *_t3493 = expect_token(p, TokenType_RBrace());
    (void)_t3493;
    Expr_add_child(def, body);
    return def;
}

Expr * parse_call(Parser * p, Str * name, U32 call_line, U32 call_col) {
    (void)p;
    (void)name;
    (void)call_line;
    (void)call_col;
    Token *_t3524 = advance(p);
    (void)_t3524;
    Expr *call = Expr_new(ExprData_FCall(), call_line, call_col, &p->path);
    (void)call;
    Str *_t3525 = Str_clone(name);
    (void)_t3525;
    ExprData *_t3526 = ExprData_Ident(_t3525);
    (void)_t3526;
    Str_delete(_t3525, &(Bool){1});
    Expr *callee = Expr_new(_t3526, call_line, call_col, &p->path);
    (void)callee;
    ExprData_delete(_t3526, &(Bool){1});
    Expr_add_child(call, callee);
    while (1) {
        Bool _t3514 = check(p, TokenType_RParen());
        (void)_t3514;
        Bool _t3515 = check(p, TokenType_Eof());
        (void)_t3515;
        Bool _t3516 = Bool_not(_t3514);
        (void)_t3516;
        ;
        Bool _t3517 = Bool_not(_t3515);
        (void)_t3517;
        ;
        Bool _wcond3494 = Bool_and(_t3516, _t3517);
        (void)_wcond3494;
        ;
        ;
        if (_wcond3494) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3518 = check(p, TokenType_Ident());
        (void)_t3518;
        if (_t3518) {
            U64 _t3505 = 1;
            (void)_t3505;
            U64 _t3506 = U64_add(p->pos, _t3505);
            (void)_t3506;
            ;
            U64 _t3507; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3507 = *_hp; free(_hp); }
            (void)_t3507;
            Bool _t3508; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3506}, &(U64){_t3507}); _t3508 = *_hp; free(_hp); }
            (void)_t3508;
            ;
            ;
            if (_t3508) {
                U64 _t3500 = 1;
                (void)_t3500;
                U64 _t3501 = U64_add(p->pos, _t3500);
                (void)_t3501;
                ;
                I64 _t3502 = U64_to_i64(_t3501);
                (void)_t3502;
                ;
                U64 *_t3503 = malloc(sizeof(U64)); *_t3503 = I64_to_u64(_t3502);
                (void)_t3503;
                ;
                Token *next_tok = Vec_get(&p->tokens, _t3503);
                (void)next_tok;
                Bool _t3504; { Bool *_hp = (Bool *)TokenType_eq(&next_tok->type, TokenType_Eq()); _t3504 = *_hp; free(_hp); }
                (void)_t3504;
                U64_delete(_t3503, &(Bool){1});
                if (_t3504) {
                    U32 na_line = peek_line(p);
                    (void)na_line;
                    U32 na_col = peek_col(p);
                    (void)na_col;
                    Str *aname = expect_text(p, TokenType_Ident());
                    (void)aname;
                    Token *_t3496 = advance(p);
                    (void)_t3496;
                    ExprData *_t3497 = ExprData_NamedArg(aname);
                    (void)_t3497;
                    Str_delete(aname, &(Bool){1});
                    Expr *na = Expr_new(_t3497, na_line, na_col, &p->path);
                    (void)na;
                    ExprData_delete(_t3497, &(Bool){1});
                    ;
                    ;
                    Expr *_t3498 = parse_expression(p);
                    (void)_t3498;
                    Expr_add_child(na, _t3498);
                    Expr_add_child(call, na);
                    Bool _t3499 = check(p, TokenType_Comma());
                    (void)_t3499;
                    if (_t3499) {
                        Token *_t3495 = advance(p);
                        (void)_t3495;
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
        Bool _t3519 = check(p, TokenType_DotDot());
        (void)_t3519;
        if (_t3519) {
            Token *_t3509 = advance(p);
            (void)_t3509;
            Bool _t3510 = 1;
            (void)_t3510;
            is_splat = _t3510;
            ;
        }
        ;
        Bool is_own_arg = 0;
        (void)is_own_arg;
        Bool _t3520 = check(p, TokenType_KwOwn());
        (void)_t3520;
        if (_t3520) {
            Token *_t3511 = advance(p);
            (void)_t3511;
            Bool _t3512 = 1;
            (void)_t3512;
            is_own_arg = _t3512;
            ;
        }
        ;
        Expr *arg = parse_expression(p);
        (void)arg;
        Bool _t3521 = Bool_clone(&(Bool){is_own_arg});
        (void)_t3521;
        ;
        arg->is_own_arg = _t3521;
        ;
        Bool _t3522 = Bool_clone(&(Bool){is_splat});
        (void)_t3522;
        ;
        arg->is_splat = _t3522;
        ;
        Expr_add_child(call, arg);
        Bool _t3523 = check(p, TokenType_Comma());
        (void)_t3523;
        if (_t3523) {
            Token *_t3513 = advance(p);
            (void)_t3513;
        }
        ;
    }
    Token *_t3527 = expect_token(p, TokenType_RParen());
    (void)_t3527;
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
    U32 _t3715 = 0;
    (void)_t3715;
    U32 _t3716 = 0;
    (void)_t3716;
    Expr *e = Expr_new(ExprData_Body(), _t3715, _t3716, &p->path);
    (void)e;
    ;
    ;
    Bool e_set = 0;
    (void)e_set;
    Bool _t3717; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t3717 = *_hp; free(_hp); }
    (void)_t3717;
    if (_t3717) {
        Token *_t3528 = advance(p);
        (void)_t3528;
        Str *_t3529 = Str_clone(&t->text);
        (void)_t3529;
        ExprData *_t3530 = ExprData_LiteralStr(_t3529);
        (void)_t3530;
        Str_delete(_t3529, &(Bool){1});
        e = Expr_new(_t3530, t_line, t_col, &p->path);
        ExprData_delete(_t3530, &(Bool){1});
        Bool _t3531 = 1;
        (void)_t3531;
        e_set = _t3531;
        ;
    }
    ;
    Bool _t3718 = Bool_not(e_set);
    (void)_t3718;
    Bool _t3719; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t3719 = *_hp; free(_hp); }
    (void)_t3719;
    Bool _t3720 = Bool_and(_t3718, _t3719);
    (void)_t3720;
    ;
    ;
    if (_t3720) {
        Token *_t3532 = advance(p);
        (void)_t3532;
        Str *_t3533 = Str_clone(&t->text);
        (void)_t3533;
        ExprData *_t3534 = ExprData_LiteralNum(_t3533);
        (void)_t3534;
        Str_delete(_t3533, &(Bool){1});
        e = Expr_new(_t3534, t_line, t_col, &p->path);
        ExprData_delete(_t3534, &(Bool){1});
        Bool _t3535 = 1;
        (void)_t3535;
        e_set = _t3535;
        ;
    }
    ;
    Bool _t3721 = Bool_not(e_set);
    (void)_t3721;
    Bool _t3722; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Char()); _t3722 = *_hp; free(_hp); }
    (void)_t3722;
    Bool _t3723 = Bool_and(_t3721, _t3722);
    (void)_t3723;
    ;
    ;
    if (_t3723) {
        Token *_t3565 = advance(p);
        (void)_t3565;
        Str *ch = Str_clone(&t->text);
        (void)ch;
        I64 byte_val = 0;
        (void)byte_val;
        U64 _t3566; { U64 *_hp = (U64 *)Str_len(ch); _t3566 = *_hp; free(_hp); }
        (void)_t3566;
        U64 _t3567 = 0;
        (void)_t3567;
        U64 *_t3568 = malloc(sizeof(U64));
        *_t3568 = 0;
        (void)_t3568;
        U8 *_t3569 = Str_get(ch, _t3568);
        (void)_t3569;
        U8 _t3570 = 92;
        (void)_t3570;
        Bool _t3571; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3566}, &(U64){_t3567}); _t3571 = *_hp; free(_hp); }
        (void)_t3571;
        ;
        ;
        Bool _t3572 = U8_eq(DEREF(_t3569), _t3570);
        (void)_t3572;
        U64_delete(_t3568, &(Bool){1});
        ;
        Bool _t3573 = Bool_and(_t3571, _t3572);
        (void)_t3573;
        ;
        ;
        if (_t3573) {
            U64 _t3556; { U64 *_hp = (U64 *)Str_len(ch); _t3556 = *_hp; free(_hp); }
            (void)_t3556;
            U64 _t3557 = 1;
            (void)_t3557;
            Bool _t3558; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3556}, &(U64){_t3557}); _t3558 = *_hp; free(_hp); }
            (void)_t3558;
            ;
            ;
            if (_t3558) {
                U64 *_t3553 = malloc(sizeof(U64));
                *_t3553 = 1;
                (void)_t3553;
                U8 *c2 = Str_get(ch, _t3553);
                (void)c2;
                U8 _t3554 = 110;
                (void)_t3554;
                Bool _t3555 = U8_eq(DEREF(c2), _t3554);
                (void)_t3555;
                ;
                if (_t3555) {
                    I64 _t3536 = 10;
                    (void)_t3536;
                    byte_val = _t3536;
                    ;
                } else {
                    U8 _t3551 = 116;
                    (void)_t3551;
                    Bool _t3552 = U8_eq(DEREF(c2), _t3551);
                    (void)_t3552;
                    ;
                    if (_t3552) {
                        I64 _t3537 = 9;
                        (void)_t3537;
                        byte_val = _t3537;
                        ;
                    } else {
                        U8 _t3549 = 114;
                        (void)_t3549;
                        Bool _t3550 = U8_eq(DEREF(c2), _t3549);
                        (void)_t3550;
                        ;
                        if (_t3550) {
                            I64 _t3538 = 13;
                            (void)_t3538;
                            byte_val = _t3538;
                            ;
                        } else {
                            U8 _t3547 = 92;
                            (void)_t3547;
                            Bool _t3548 = U8_eq(DEREF(c2), _t3547);
                            (void)_t3548;
                            ;
                            if (_t3548) {
                                I64 _t3539 = 92;
                                (void)_t3539;
                                byte_val = _t3539;
                                ;
                            } else {
                                U8 _t3545 = 39;
                                (void)_t3545;
                                Bool _t3546 = U8_eq(DEREF(c2), _t3545);
                                (void)_t3546;
                                ;
                                if (_t3546) {
                                    I64 _t3540 = 39;
                                    (void)_t3540;
                                    byte_val = _t3540;
                                    ;
                                } else {
                                    U8 _t3543 = 48;
                                    (void)_t3543;
                                    Bool _t3544 = U8_eq(DEREF(c2), _t3543);
                                    (void)_t3544;
                                    ;
                                    if (_t3544) {
                                        I64 _t3541 = 0;
                                        (void)_t3541;
                                        byte_val = _t3541;
                                        ;
                                    } else {
                                        I64 _t3542 = U8_to_i64(DEREF(c2));
                                        (void)_t3542;
                                        byte_val = _t3542;
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
                U64_delete(_t3553, &(Bool){1});
                ;
            }
            ;
        } else {
            U64 _t3562; { U64 *_hp = (U64 *)Str_len(ch); _t3562 = *_hp; free(_hp); }
            (void)_t3562;
            U64 _t3563 = 0;
            (void)_t3563;
            Bool _t3564; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3562}, &(U64){_t3563}); _t3564 = *_hp; free(_hp); }
            (void)_t3564;
            ;
            ;
            if (_t3564) {
                U64 *_t3559 = malloc(sizeof(U64));
                *_t3559 = 0;
                (void)_t3559;
                U8 *_t3560 = Str_get(ch, _t3559);
                (void)_t3560;
                I64 _t3561 = U8_to_i64(DEREF(_t3560));
                (void)_t3561;
                U64_delete(_t3559, &(Bool){1});
                byte_val = _t3561;
                ;
            }
            ;
        }
        ;
        Str_delete(ch, &(Bool){1});
        Str *_t3574 = I64_to_str(&(I64){byte_val});
        (void)_t3574;
        ;
        ExprData *_t3575 = ExprData_LiteralNum(_t3574);
        (void)_t3575;
        Str_delete(_t3574, &(Bool){1});
        e = Expr_new(_t3575, t_line, t_col, &p->path);
        ExprData_delete(_t3575, &(Bool){1});
        TilType_delete(&e->til_type, &(Bool){0});
        { TilType *_fa = TilType_clone(TilType_U8()); e->til_type = *_fa; free(_fa); }
        Bool _t3576 = 1;
        (void)_t3576;
        e_set = _t3576;
        ;
    }
    ;
    Bool _t3724; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t3724 = *_hp; free(_hp); }
    (void)_t3724;
    Bool _t3725; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t3725 = *_hp; free(_hp); }
    (void)_t3725;
    Bool _t3726 = Bool_not(e_set);
    (void)_t3726;
    Bool _t3727 = Bool_or(_t3724, _t3725);
    (void)_t3727;
    ;
    ;
    Bool _t3728 = Bool_and(_t3726, _t3727);
    (void)_t3728;
    ;
    ;
    if (_t3728) {
        Token *_t3577 = advance(p);
        (void)_t3577;
        Str *_t3578 = Str_clone(&t->text);
        (void)_t3578;
        ExprData *_t3579 = ExprData_LiteralBool(_t3578);
        (void)_t3579;
        Str_delete(_t3578, &(Bool){1});
        e = Expr_new(_t3579, t_line, t_col, &p->path);
        ExprData_delete(_t3579, &(Bool){1});
        Bool _t3580 = 1;
        (void)_t3580;
        e_set = _t3580;
        ;
    }
    ;
    Bool _t3729 = Bool_not(e_set);
    (void)_t3729;
    Bool _t3730; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwNull()); _t3730 = *_hp; free(_hp); }
    (void)_t3730;
    Bool _t3731 = Bool_and(_t3729, _t3730);
    (void)_t3731;
    ;
    ;
    if (_t3731) {
        Token *_t3581 = advance(p);
        (void)_t3581;
        e = Expr_new(ExprData_LiteralNull(), t_line, t_col, &p->path);
        Bool _t3582 = 1;
        (void)_t3582;
        e_set = _t3582;
        ;
    }
    ;
    Bool _t3732 = Bool_not(e_set);
    (void)_t3732;
    Bool _t3733; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t3733 = *_hp; free(_hp); }
    (void)_t3733;
    Bool _t3734 = Bool_and(_t3732, _t3733);
    (void)_t3734;
    ;
    ;
    if (_t3734) {
        Token *_t3618 = advance(p);
        (void)_t3618;
        Str *name = Str_clone(&t->text);
        (void)name;
        Str *_t3619 = Str_lit("__LOC__", 7ULL);
        (void)_t3619;
        Bool _t3620; { Bool *_hp = (Bool *)Str_eq(name, _t3619); _t3620 = *_hp; free(_hp); }
        (void)_t3620;
        Str_delete(_t3619, &(Bool){1});
        if (_t3620) {
            Str *_t3583 = Str_lit("Str", 3ULL);
            (void)_t3583;
            U64 _t3584; { U64 *_hp = (U64 *)Str_size(); _t3584 = *_hp; free(_hp); }
            (void)_t3584;
            U64 _t3585 = 5;
            (void)_t3585;
            Array *_va67 = Array_new(_t3583, &(U64){_t3584}, &(U64){_t3585});
            (void)_va67;
            Str_delete(_t3583, &(Bool){1});
            ;
            ;
            U64 _t3586 = 0;
            (void)_t3586;
            Str *_t3587 = Str_clone(&p->path);
            (void)_t3587;
            Array_set(_va67, &(U64){_t3586}, _t3587);
            ;
            U64 _t3588 = 1;
            (void)_t3588;
            Str *_t3589 = Str_lit(":", 1ULL);
            (void)_t3589;
            Array_set(_va67, &(U64){_t3588}, _t3589);
            ;
            U64 _t3590 = 2;
            (void)_t3590;
            Str *_t3591 = U32_to_str(&(U32){t_line});
            (void)_t3591;
            Array_set(_va67, &(U64){_t3590}, _t3591);
            ;
            U64 _t3592 = 3;
            (void)_t3592;
            Str *_t3593 = Str_lit(":", 1ULL);
            (void)_t3593;
            Array_set(_va67, &(U64){_t3592}, _t3593);
            ;
            U64 _t3594 = 4;
            (void)_t3594;
            Str *_t3595 = U32_to_str(&(U32){t_col});
            (void)_t3595;
            Array_set(_va67, &(U64){_t3594}, _t3595);
            ;
            Str *_t3596 = format(_va67);
            (void)_t3596;
            ExprData *_t3597 = ExprData_LiteralStr(_t3596);
            (void)_t3597;
            Str_delete(_t3596, &(Bool){1});
            e = Expr_new(_t3597, t_line, t_col, &p->path);
            ExprData_delete(_t3597, &(Bool){1});
            Bool _t3598 = 1;
            (void)_t3598;
            e_set = _t3598;
            ;
        } else {
            Str *_t3616 = Str_lit("__FILE__", 8ULL);
            (void)_t3616;
            Bool _t3617; { Bool *_hp = (Bool *)Str_eq(name, _t3616); _t3617 = *_hp; free(_hp); }
            (void)_t3617;
            Str_delete(_t3616, &(Bool){1});
            if (_t3617) {
                Str *_t3599 = Str_clone(&p->path);
                (void)_t3599;
                ExprData *_t3600 = ExprData_LiteralStr(_t3599);
                (void)_t3600;
                Str_delete(_t3599, &(Bool){1});
                e = Expr_new(_t3600, t_line, t_col, &p->path);
                ExprData_delete(_t3600, &(Bool){1});
                Bool _t3601 = 1;
                (void)_t3601;
                e_set = _t3601;
                ;
            } else {
                Str *_t3614 = Str_lit("__LINE__", 8ULL);
                (void)_t3614;
                Bool _t3615; { Bool *_hp = (Bool *)Str_eq(name, _t3614); _t3615 = *_hp; free(_hp); }
                (void)_t3615;
                Str_delete(_t3614, &(Bool){1});
                if (_t3615) {
                    Str *_t3602 = U32_to_str(&(U32){t_line});
                    (void)_t3602;
                    ExprData *_t3603 = ExprData_LiteralNum(_t3602);
                    (void)_t3603;
                    Str_delete(_t3602, &(Bool){1});
                    e = Expr_new(_t3603, t_line, t_col, &p->path);
                    ExprData_delete(_t3603, &(Bool){1});
                    Bool _t3604 = 1;
                    (void)_t3604;
                    e_set = _t3604;
                    ;
                } else {
                    Str *_t3612 = Str_lit("__COL__", 7ULL);
                    (void)_t3612;
                    Bool _t3613; { Bool *_hp = (Bool *)Str_eq(name, _t3612); _t3613 = *_hp; free(_hp); }
                    (void)_t3613;
                    Str_delete(_t3612, &(Bool){1});
                    if (_t3613) {
                        Str *_t3605 = U32_to_str(&(U32){t_col});
                        (void)_t3605;
                        ExprData *_t3606 = ExprData_LiteralNum(_t3605);
                        (void)_t3606;
                        Str_delete(_t3605, &(Bool){1});
                        e = Expr_new(_t3606, t_line, t_col, &p->path);
                        ExprData_delete(_t3606, &(Bool){1});
                        Bool _t3607 = 1;
                        (void)_t3607;
                        e_set = _t3607;
                        ;
                    } else {
                        Bool _t3611 = check(p, TokenType_LParen());
                        (void)_t3611;
                        if (_t3611) {
                            e = parse_call(p, name, t_line, t_col);
                            Bool _t3608 = 1;
                            (void)_t3608;
                            e_set = _t3608;
                            ;
                        } else {
                            ExprData *_t3609 = ExprData_Ident(name);
                            (void)_t3609;
                            e = Expr_new(_t3609, t_line, t_col, &p->path);
                            ExprData_delete(_t3609, &(Bool){1});
                            Bool _t3610 = 1;
                            (void)_t3610;
                            e_set = _t3610;
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
    Bool _t3735; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFunc()); _t3735 = *_hp; free(_hp); }
    (void)_t3735;
    Bool _t3736; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwProc()); _t3736 = *_hp; free(_hp); }
    (void)_t3736;
    Bool _t3737 = Bool_or(_t3735, _t3736);
    (void)_t3737;
    ;
    ;
    Bool _t3738; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTest()); _t3738 = *_hp; free(_hp); }
    (void)_t3738;
    Bool _t3739 = Bool_or(_t3737, _t3738);
    (void)_t3739;
    ;
    ;
    Bool _t3740; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMacro()); _t3740 = *_hp; free(_hp); }
    (void)_t3740;
    Bool _t3741 = Bool_or(_t3739, _t3740);
    (void)_t3741;
    ;
    ;
    Bool _t3742; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtFunc()); _t3742 = *_hp; free(_hp); }
    (void)_t3742;
    Bool _t3743 = Bool_or(_t3741, _t3742);
    (void)_t3743;
    ;
    ;
    Bool _t3744; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtProc()); _t3744 = *_hp; free(_hp); }
    (void)_t3744;
    Bool _t3745 = Bool_not(e_set);
    (void)_t3745;
    Bool _t3746 = Bool_or(_t3743, _t3744);
    (void)_t3746;
    ;
    ;
    Bool _t3747 = Bool_and(_t3745, _t3746);
    (void)_t3747;
    ;
    ;
    if (_t3747) {
        Expr *_t3621 = parse_func_def(p);
        (void)_t3621;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3621;
    }
    ;
    Bool _t3748; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwStruct()); _t3748 = *_hp; free(_hp); }
    (void)_t3748;
    Bool _t3749; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtStruct()); _t3749 = *_hp; free(_hp); }
    (void)_t3749;
    Bool _t3750 = Bool_not(e_set);
    (void)_t3750;
    Bool _t3751 = Bool_or(_t3748, _t3749);
    (void)_t3751;
    ;
    ;
    Bool _t3752 = Bool_and(_t3750, _t3751);
    (void)_t3752;
    ;
    ;
    if (_t3752) {
        Expr *_t3622 = parse_struct_def(p);
        (void)_t3622;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3622;
    }
    ;
    Bool _t3753 = Bool_not(e_set);
    (void)_t3753;
    Bool _t3754; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwEnum()); _t3754 = *_hp; free(_hp); }
    (void)_t3754;
    Bool _t3755 = Bool_and(_t3753, _t3754);
    (void)_t3755;
    ;
    ;
    if (_t3755) {
        Expr *_t3623 = parse_enum_def(p);
        (void)_t3623;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3623;
    }
    ;
    Bool _t3756 = Bool_not(e_set);
    (void)_t3756;
    Bool _t3757; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t3757 = *_hp; free(_hp); }
    (void)_t3757;
    Bool _t3758 = Bool_and(_t3756, _t3757);
    (void)_t3758;
    ;
    ;
    if (_t3758) {
        Token *_t3648 = advance(p);
        (void)_t3648;
        Expr *first = parse_expression(p);
        (void)first;
        Bool _t3649 = check(p, TokenType_Colon());
        (void)_t3649;
        if (_t3649) {
            e = Expr_new(ExprData_MapLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Token *_t3635 = advance(p);
            (void)_t3635;
            Expr *_t3636 = parse_expression(p);
            (void)_t3636;
            Expr_add_child(e, _t3636);
            Bool _t3637 = check(p, TokenType_Comma());
            (void)_t3637;
            if (_t3637) {
                Token *_t3624 = advance(p);
                (void)_t3624;
            }
            ;
            while (1) {
                Bool _t3627 = check(p, TokenType_RBrace());
                (void)_t3627;
                Bool _t3628 = check(p, TokenType_Eof());
                (void)_t3628;
                Bool _t3629 = Bool_not(_t3627);
                (void)_t3629;
                ;
                Bool _t3630 = Bool_not(_t3628);
                (void)_t3630;
                ;
                Bool _wcond3625 = Bool_and(_t3629, _t3630);
                (void)_wcond3625;
                ;
                ;
                if (_wcond3625) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3631 = parse_expression(p);
                (void)_t3631;
                Expr_add_child(e, _t3631);
                Token *_t3632 = expect_token(p, TokenType_Colon());
                (void)_t3632;
                Expr *_t3633 = parse_expression(p);
                (void)_t3633;
                Expr_add_child(e, _t3633);
                Bool _t3634 = check(p, TokenType_Comma());
                (void)_t3634;
                if (_t3634) {
                    Token *_t3626 = advance(p);
                    (void)_t3626;
                }
                ;
            }
        } else {
            e = Expr_new(ExprData_SetLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Bool _t3647 = check(p, TokenType_Comma());
            (void)_t3647;
            if (_t3647) {
                Token *_t3638 = advance(p);
                (void)_t3638;
            }
            ;
            while (1) {
                Bool _t3641 = check(p, TokenType_RBrace());
                (void)_t3641;
                Bool _t3642 = check(p, TokenType_Eof());
                (void)_t3642;
                Bool _t3643 = Bool_not(_t3641);
                (void)_t3643;
                ;
                Bool _t3644 = Bool_not(_t3642);
                (void)_t3644;
                ;
                Bool _wcond3639 = Bool_and(_t3643, _t3644);
                (void)_wcond3639;
                ;
                ;
                if (_wcond3639) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3645 = parse_expression(p);
                (void)_t3645;
                Expr_add_child(e, _t3645);
                Bool _t3646 = check(p, TokenType_Comma());
                (void)_t3646;
                if (_t3646) {
                    Token *_t3640 = advance(p);
                    (void)_t3640;
                }
                ;
            }
        }
        ;
        Token *_t3650 = expect_token(p, TokenType_RBrace());
        (void)_t3650;
        Bool _t3651 = 1;
        (void)_t3651;
        e_set = _t3651;
        ;
    }
    ;
    Bool _t3759 = Bool_not(e_set);
    (void)_t3759;
    ;
    if (_t3759) {
        Str *_t3652 = Str_lit("Str", 3ULL);
        (void)_t3652;
        U64 _t3653; { U64 *_hp = (U64 *)Str_size(); _t3653 = *_hp; free(_hp); }
        (void)_t3653;
        U64 _t3654 = 8;
        (void)_t3654;
        Array *_va68 = Array_new(_t3652, &(U64){_t3653}, &(U64){_t3654});
        (void)_va68;
        Str_delete(_t3652, &(Bool){1});
        ;
        ;
        U64 _t3655 = 0;
        (void)_t3655;
        Str *_t3656 = Str_clone(&p->path);
        (void)_t3656;
        Array_set(_va68, &(U64){_t3655}, _t3656);
        ;
        U64 _t3657 = 1;
        (void)_t3657;
        Str *_t3658 = Str_lit(":", 1ULL);
        (void)_t3658;
        Array_set(_va68, &(U64){_t3657}, _t3658);
        ;
        U64 _t3659 = 2;
        (void)_t3659;
        Str *_t3660 = U32_to_str(&(U32){t_line});
        (void)_t3660;
        Array_set(_va68, &(U64){_t3659}, _t3660);
        ;
        U64 _t3661 = 3;
        (void)_t3661;
        Str *_t3662 = Str_lit(":", 1ULL);
        (void)_t3662;
        Array_set(_va68, &(U64){_t3661}, _t3662);
        ;
        U64 _t3663 = 4;
        (void)_t3663;
        Str *_t3664 = U32_to_str(&(U32){t_col});
        (void)_t3664;
        Array_set(_va68, &(U64){_t3663}, _t3664);
        ;
        U64 _t3665 = 5;
        (void)_t3665;
        Str *_t3666 = Str_lit(": unexpected token '", 20ULL);
        (void)_t3666;
        Array_set(_va68, &(U64){_t3665}, _t3666);
        ;
        U64 _t3667 = 6;
        (void)_t3667;
        Str *_t3668 = Str_clone(&t->text);
        (void)_t3668;
        Array_set(_va68, &(U64){_t3667}, _t3668);
        ;
        U64 _t3669 = 7;
        (void)_t3669;
        Str *_t3670 = Str_lit("'", 1ULL);
        (void)_t3670;
        Array_set(_va68, &(U64){_t3669}, _t3670);
        ;
        Str *_t3671 = Str_lit("src/self/parser.til:520:15", 26ULL);
        (void)_t3671;
        panic(_t3671, _va68);
        Str_delete(_t3671, &(Bool){1});
    }
    ;
    ;
    ;
    while (1) {
        Bool _wcond3672 = check(p, TokenType_Dot());
        (void)_wcond3672;
        if (_wcond3672) {
        } else {
            ;
            break;
        }
        ;
        Token *_t3705 = advance(p);
        (void)_t3705;
        U32 f_line = peek_line(p);
        (void)f_line;
        U32 f_col = peek_col(p);
        (void)f_col;
        Str *fname = expect_text(p, TokenType_Ident());
        (void)fname;
        Bool _t3706 = check(p, TokenType_LParen());
        (void)_t3706;
        if (_t3706) {
            Token *_t3699 = advance(p);
            (void)_t3699;
            ExprData *_t3700 = ExprData_FieldAccess(fname);
            (void)_t3700;
            Expr *callee = Expr_new(_t3700, f_line, f_col, &p->path);
            (void)callee;
            ExprData_delete(_t3700, &(Bool){1});
            Expr *_t3701 = Expr_clone(e);
            (void)_t3701;
            Expr_add_child(callee, _t3701);
            Expr *mcall = Expr_new(ExprData_FCall(), f_line, f_col, &p->path);
            (void)mcall;
            Expr_add_child(mcall, callee);
            while (1) {
                Bool _t3691 = check(p, TokenType_RParen());
                (void)_t3691;
                Bool _t3692 = check(p, TokenType_Eof());
                (void)_t3692;
                Bool _t3693 = Bool_not(_t3691);
                (void)_t3693;
                ;
                Bool _t3694 = Bool_not(_t3692);
                (void)_t3694;
                ;
                Bool _wcond3673 = Bool_and(_t3693, _t3694);
                (void)_wcond3673;
                ;
                ;
                if (_wcond3673) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3695 = check(p, TokenType_Ident());
                (void)_t3695;
                if (_t3695) {
                    U64 _t3684 = 1;
                    (void)_t3684;
                    U64 _t3685 = U64_add(p->pos, _t3684);
                    (void)_t3685;
                    ;
                    U64 _t3686; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3686 = *_hp; free(_hp); }
                    (void)_t3686;
                    Bool _t3687; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3685}, &(U64){_t3686}); _t3687 = *_hp; free(_hp); }
                    (void)_t3687;
                    ;
                    ;
                    if (_t3687) {
                        U64 _t3679 = 1;
                        (void)_t3679;
                        U64 _t3680 = U64_add(p->pos, _t3679);
                        (void)_t3680;
                        ;
                        I64 _t3681 = U64_to_i64(_t3680);
                        (void)_t3681;
                        ;
                        U64 *_t3682 = malloc(sizeof(U64)); *_t3682 = I64_to_u64(_t3681);
                        (void)_t3682;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3682);
                        (void)nt;
                        Bool _t3683; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3683 = *_hp; free(_hp); }
                        (void)_t3683;
                        U64_delete(_t3682, &(Bool){1});
                        if (_t3683) {
                            U32 na_line = peek_line(p);
                            (void)na_line;
                            U32 na_col = peek_col(p);
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3675 = advance(p);
                            (void)_t3675;
                            ExprData *_t3676 = ExprData_NamedArg(aname);
                            (void)_t3676;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3676, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3676, &(Bool){1});
                            ;
                            ;
                            Expr *_t3677 = parse_expression(p);
                            (void)_t3677;
                            Expr_add_child(na, _t3677);
                            Expr_add_child(mcall, na);
                            Bool _t3678 = check(p, TokenType_Comma());
                            (void)_t3678;
                            if (_t3678) {
                                Token *_t3674 = advance(p);
                                (void)_t3674;
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
                Bool _t3696 = check(p, TokenType_KwOwn());
                (void)_t3696;
                if (_t3696) {
                    Token *_t3688 = advance(p);
                    (void)_t3688;
                    Bool _t3689 = 1;
                    (void)_t3689;
                    is_own_arg = _t3689;
                    ;
                }
                ;
                Expr *marg = parse_expression(p);
                (void)marg;
                Bool _t3697 = Bool_clone(&(Bool){is_own_arg});
                (void)_t3697;
                ;
                marg->is_own_arg = _t3697;
                ;
                Expr_add_child(mcall, marg);
                Bool _t3698 = check(p, TokenType_Comma());
                (void)_t3698;
                if (_t3698) {
                    Token *_t3690 = advance(p);
                    (void)_t3690;
                }
                ;
            }
            Token *_t3702 = expect_token(p, TokenType_RParen());
            (void)_t3702;
            e = Expr_clone(mcall);
            Expr_delete(mcall, &(Bool){1});
        } else {
            ExprData *_t3703 = ExprData_FieldAccess(fname);
            (void)_t3703;
            Expr *access = Expr_new(_t3703, f_line, f_col, &p->path);
            (void)access;
            ExprData_delete(_t3703, &(Bool){1});
            Expr *_t3704 = Expr_clone(e);
            (void)_t3704;
            Expr_add_child(access, _t3704);
            e = Expr_clone(access);
            Expr_delete(access, &(Bool){1});
        }
        ;
        ;
        ;
        Str_delete(fname, &(Bool){1});
    }
    Bool _t3760 = check(p, TokenType_DotDot());
    (void)_t3760;
    if (_t3760) {
        U32 dt_line = peek_line(p);
        (void)dt_line;
        U32 dt_col = peek_col(p);
        (void)dt_col;
        Token *_t3707 = advance(p);
        (void)_t3707;
        Expr *rhs = parse_expression(p);
        (void)rhs;
        Str *_t3708 = Str_lit("Range", 5ULL);
        (void)_t3708;
        Str *_t3709 = Str_clone(_t3708);
        (void)_t3709;
        Str_delete(_t3708, &(Bool){1});
        ExprData *_t3710 = ExprData_Ident(_t3709);
        (void)_t3710;
        Str_delete(_t3709, &(Bool){1});
        Expr *range_ident = Expr_new(_t3710, dt_line, dt_col, &p->path);
        (void)range_ident;
        ExprData_delete(_t3710, &(Bool){1});
        Str *_t3711 = Str_lit("new", 3ULL);
        (void)_t3711;
        Str *_t3712 = Str_clone(_t3711);
        (void)_t3712;
        Str_delete(_t3711, &(Bool){1});
        ExprData *_t3713 = ExprData_FieldAccess(_t3712);
        (void)_t3713;
        Str_delete(_t3712, &(Bool){1});
        Expr *new_access = Expr_new(_t3713, dt_line, dt_col, &p->path);
        (void)new_access;
        ExprData_delete(_t3713, &(Bool){1});
        Expr_add_child(new_access, range_ident);
        Expr *rcall = Expr_new(ExprData_FCall(), dt_line, dt_col, &p->path);
        (void)rcall;
        ;
        ;
        Expr_add_child(rcall, new_access);
        Expr *_t3714 = Expr_clone(e);
        (void)_t3714;
        Expr_add_child(rcall, _t3714);
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
    Bool _t3963 = check(p, TokenType_ColonEq());
    (void)_t3963;
    if (_t3963) {
        Token *_t3761 = advance(p);
        (void)_t3761;
        Bool _t3762 = Bool_clone(&(Bool){is_mut});
        (void)_t3762;
        Bool _t3763 = 0;
        (void)_t3763;
        Bool _t3764 = 0;
        (void)_t3764;
        Bool _t3765 = Bool_clone(&(Bool){is_own});
        (void)_t3765;
        I32 _t3766 = 0;
        (void)_t3766;
        I32 _t3767 = 0;
        (void)_t3767;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3762;
        dd->is_namespace = _t3763;
        dd->is_ref = _t3764;
        dd->is_own = _t3765;
        dd->field_offset = _t3766;
        dd->field_size = _t3767;
        dd->field_struct_def = NULL;
        dd->fn_sig = NULL;
        (void)dd;
        ;
        ;
        ;
        ;
        ;
        ;
        ExprData *_t3768 = ExprData_Decl(dd);
        (void)_t3768;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3768, t_line, t_col, &p->path);
        (void)decl;
        ExprData_delete(_t3768, &(Bool){1});
        Expr *_t3769 = parse_expression(p);
        (void)_t3769;
        Expr_add_child(decl, _t3769);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return decl;
    }
    ;
    Bool _t3964 = check(p, TokenType_Colon());
    (void)_t3964;
    if (_t3964) {
        Token *_t3895 = advance(p);
        (void)_t3895;
        Bool _t3896 = check(p, TokenType_KwFunc());
        (void)_t3896;
        Bool _t3897 = check(p, TokenType_KwProc());
        (void)_t3897;
        Bool _t3898 = Bool_or(_t3896, _t3897);
        (void)_t3898;
        ;
        ;
        if (_t3898) {
            Expr *sig = parse_func_def(p);
            (void)sig;
            Token *_t3787 = expect_token(p, TokenType_Eq());
            (void)_t3787;
            Token *_t3788 = expect_token(p, TokenType_LParen());
            (void)_t3788;
            Bool _t3789; { Bool *_hp = (Bool *)ExprData_is_FuncDef(&sig->data); _t3789 = *_hp; free(_hp); }
            (void)_t3789;
            if (_t3789) {
                FunctionDef *sfd = ExprData_get_FuncDef(&sig->data);
                (void)sfd;
                Str *_t3784 = Str_lit("Str", 3ULL);
                (void)_t3784;
                U64 _t3785; { U64 *_hp = (U64 *)Str_size(); _t3785 = *_hp; free(_hp); }
                (void)_t3785;
                Vec *new_names = Vec_new(_t3784, &(U64){_t3785});
                (void)new_names;
                Str_delete(_t3784, &(Bool){1});
                ;
                {
                    U64 _fi3770 = 0;
                    (void)_fi3770;
                    while (1) {
                        U64 _t3773 = 0;
                        (void)_t3773;
                        U64 _t3774; { U64 *_hp = (U64 *)Vec_len(&sfd->param_names); _t3774 = *_hp; free(_hp); }
                        (void)_t3774;
                        Range *_t3775 = Range_new(_t3773, _t3774);
                        (void)_t3775;
                        ;
                        ;
                        U64 _t3776; { U64 *_hp = (U64 *)Range_len(_t3775); _t3776 = *_hp; free(_hp); }
                        (void)_t3776;
                        Range_delete(_t3775, &(Bool){1});
                        Bool _wcond3771; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3770}, &(U64){_t3776}); _wcond3771 = *_hp; free(_hp); }
                        (void)_wcond3771;
                        ;
                        if (_wcond3771) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 _t3777 = 0;
                        (void)_t3777;
                        U64 _t3778; { U64 *_hp = (U64 *)Vec_len(&sfd->param_names); _t3778 = *_hp; free(_hp); }
                        (void)_t3778;
                        Range *_t3779 = Range_new(_t3777, _t3778);
                        (void)_t3779;
                        ;
                        ;
                        U64 pi; { U64 *_hp = (U64 *)Range_get(_t3779, _fi3770); pi = *_hp; free(_hp); }
                        (void)pi;
                        Range_delete(_t3779, &(Bool){1});
                        U64 _t3780 = 1;
                        (void)_t3780;
                        U64 _t3781 = U64_add(_fi3770, _t3780);
                        (void)_t3781;
                        ;
                        _fi3770 = _t3781;
                        ;
                        U64 _t3782 = 0;
                        (void)_t3782;
                        Bool _t3783; { Bool *_hp = (Bool *)U64_gt(&(U64){pi}, &(U64){_t3782}); _t3783 = *_hp; free(_hp); }
                        (void)_t3783;
                        ;
                        ;
                        if (_t3783) {
                            Token *_t3772 = expect_token(p, TokenType_Comma());
                            (void)_t3772;
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
            Bool _t3790 = check(p, TokenType_Comma());
            (void)_t3790;
            if (_t3790) {
                Token *_t3786 = advance(p);
                (void)_t3786;
            }
            ;
            Token *_t3791 = expect_token(p, TokenType_RParen());
            (void)_t3791;
            Token *_t3792 = expect_token(p, TokenType_LBrace());
            (void)_t3792;
            Expr *_t3793 = parse_block(p);
            (void)_t3793;
            Expr_add_child(sig, _t3793);
            Bool _t3794 = Bool_clone(&(Bool){is_mut});
            (void)_t3794;
            Bool _t3795 = 0;
            (void)_t3795;
            Bool _t3796 = 0;
            (void)_t3796;
            Bool _t3797 = Bool_clone(&(Bool){is_own});
            (void)_t3797;
            I32 _t3798 = 0;
            (void)_t3798;
            I32 _t3799 = 0;
            (void)_t3799;
            Declaration *dd = malloc(sizeof(Declaration));
            { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
            dd->is_mut = _t3794;
            dd->is_namespace = _t3795;
            dd->is_ref = _t3796;
            dd->is_own = _t3797;
            dd->field_offset = _t3798;
            dd->field_size = _t3799;
            dd->field_struct_def = NULL;
            dd->fn_sig = NULL;
            (void)dd;
            ;
            ;
            ;
            ;
            ;
            ;
            ExprData *_t3800 = ExprData_Decl(dd);
            (void)_t3800;
            Declaration_delete(dd, &(Bool){1});
            Expr *decl = Expr_new(_t3800, t_line, t_col, &p->path);
            (void)decl;
            ExprData_delete(_t3800, &(Bool){1});
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
        I64 _t3899 = 0;
        (void)_t3899;
        I64 _t3900 = 1;
        (void)_t3900;
        I64 fn_sig_idx = I64_sub(_t3899, _t3900);
        (void)fn_sig_idx;
        ;
        ;
        Str *_t3901 = Str_lit("Fn", 2ULL);
        (void)_t3901;
        Bool _t3902; { Bool *_hp = (Bool *)Str_eq(type_name, _t3901); _t3902 = *_hp; free(_hp); }
        (void)_t3902;
        Str_delete(_t3901, &(Bool){1});
        if (_t3902) {
            Expr *sig = parse_fn_signature(p, t_line, t_col);
            (void)sig;
            U32 _t3802 = 0;
            (void)_t3802;
            Bool _t3803; { Bool *_hp = (Bool *)U32_neq(&sig->line, &(U32){_t3802}); _t3803 = *_hp; free(_hp); }
            (void)_t3803;
            ;
            Expr_delete(sig, &(Bool){1});
            if (_t3803) {
                I64 _t3801 = 0;
                (void)_t3801;
                fn_sig_idx = _t3801;
                ;
            }
            ;
        }
        ;
        ;
        Token *_t3903 = expect_token(p, TokenType_Eq());
        (void)_t3903;
        Bool _t3904 = check(p, TokenType_LParen());
        (void)_t3904;
        if (_t3904) {
            U64 saved = p->pos;
            (void)saved;
            Token *_t3891 = advance(p);
            (void)_t3891;
            Bool is_fsf = 1;
            (void)is_fsf;
            while (1) {
                Bool _t3807 = check(p, TokenType_RParen());
                (void)_t3807;
                Bool _t3808 = check(p, TokenType_Eof());
                (void)_t3808;
                Bool _t3809 = Bool_not(_t3807);
                (void)_t3809;
                ;
                Bool _t3810 = Bool_not(_t3808);
                (void)_t3810;
                ;
                Bool _wcond3804 = Bool_and(_t3809, _t3810);
                (void)_wcond3804;
                ;
                ;
                if (_wcond3804) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3811 = check(p, TokenType_Ident());
                (void)_t3811;
                Bool _t3812 = Bool_not(_t3811);
                (void)_t3812;
                ;
                if (_t3812) {
                    Bool _t3805 = 0;
                    (void)_t3805;
                    is_fsf = _t3805;
                    ;
                    ;
                    break;
                }
                ;
                Token *_t3813 = advance(p);
                (void)_t3813;
                Bool _t3814 = check(p, TokenType_Comma());
                (void)_t3814;
                if (_t3814) {
                    Token *_t3806 = advance(p);
                    (void)_t3806;
                }
                ;
            }
            Bool _t3892 = check(p, TokenType_RParen());
            (void)_t3892;
            Bool _t3893 = Bool_and(is_fsf, _t3892);
            (void)_t3893;
            ;
            if (_t3893) {
                Token *_t3816 = advance(p);
                (void)_t3816;
                Bool _t3817 = check(p, TokenType_LBrace());
                (void)_t3817;
                Bool _t3818 = Bool_not(_t3817);
                (void)_t3818;
                ;
                if (_t3818) {
                    Bool _t3815 = 0;
                    (void)_t3815;
                    is_fsf = _t3815;
                    ;
                }
                ;
            } else {
                Bool _t3819 = 0;
                (void)_t3819;
                is_fsf = _t3819;
                ;
            }
            ;
            U64 _t3894 = U64_clone(&(U64){saved});
            (void)_t3894;
            ;
            p->pos = _t3894;
            ;
            if (is_fsf) {
                Token *_t3843 = expect_token(p, TokenType_LParen());
                (void)_t3843;
                Str *_t3844 = Str_lit("Str", 3ULL);
                (void)_t3844;
                U64 _t3845; { U64 *_hp = (U64 *)Str_size(); _t3845 = *_hp; free(_hp); }
                (void)_t3845;
                Vec *pnames = Vec_new(_t3844, &(U64){_t3845});
                (void)pnames;
                Str_delete(_t3844, &(Bool){1});
                ;
                while (1) {
                    Bool _t3822 = check(p, TokenType_RParen());
                    (void)_t3822;
                    Bool _wcond3820 = Bool_not(_t3822);
                    (void)_wcond3820;
                    ;
                    if (_wcond3820) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *pn = expect_text(p, TokenType_Ident());
                    (void)pn;
                    Vec_push(pnames, pn);
                    Bool _t3823 = check(p, TokenType_Comma());
                    (void)_t3823;
                    if (_t3823) {
                        Token *_t3821 = advance(p);
                        (void)_t3821;
                    }
                    ;
                }
                Token *_t3846 = expect_token(p, TokenType_RParen());
                (void)_t3846;
                Token *_t3847 = expect_token(p, TokenType_LBrace());
                (void)_t3847;
                Expr *body = parse_block(p);
                (void)body;
                Str *_t3848 = Str_lit("Str", 3ULL);
                (void)_t3848;
                U64 _t3849; { U64 *_hp = (U64 *)Str_size(); _t3849 = *_hp; free(_hp); }
                (void)_t3849;
                Str *_t3850 = Str_lit("Str", 3ULL);
                (void)_t3850;
                U64 _t3851; { U64 *_hp = (U64 *)Str_size(); _t3851 = *_hp; free(_hp); }
                (void)_t3851;
                Str *_t3852 = Str_lit("Bool", 4ULL);
                (void)_t3852;
                U64 _t3853; { U64 *_hp = (U64 *)Bool_size(); _t3853 = *_hp; free(_hp); }
                (void)_t3853;
                Str *_t3854 = Str_lit("Bool", 4ULL);
                (void)_t3854;
                U64 _t3855; { U64 *_hp = (U64 *)Bool_size(); _t3855 = *_hp; free(_hp); }
                (void)_t3855;
                Str *_t3856 = Str_lit("Bool", 4ULL);
                (void)_t3856;
                U64 _t3857; { U64 *_hp = (U64 *)Bool_size(); _t3857 = *_hp; free(_hp); }
                (void)_t3857;
                Str *_t3858 = Str_lit("I64", 3ULL);
                (void)_t3858;
                U64 _t3859; { U64 *_hp = (U64 *)I64_size(); _t3859 = *_hp; free(_hp); }
                (void)_t3859;
                Str *_t3860 = Str_lit("I64", 3ULL);
                (void)_t3860;
                U64 _t3861; { U64 *_hp = (U64 *)I64_size(); _t3861 = *_hp; free(_hp); }
                (void)_t3861;
                I64 _t3862 = 0;
                (void)_t3862;
                I64 _t3863 = 1;
                (void)_t3863;
                I64 _t3864 = I64_sub(_t3862, _t3863);
                (void)_t3864;
                ;
                ;
                I64 _t3865 = 0;
                (void)_t3865;
                I64 _t3866 = 1;
                (void)_t3866;
                I64 _t3867 = I64_sub(_t3865, _t3866);
                (void)_t3867;
                ;
                ;
                U32 _t3868 = 0;
                (void)_t3868;
                I32 _t3869 = I64_to_i32(_t3864);
                (void)_t3869;
                ;
                I32 _t3870 = I64_to_i32(_t3867);
                (void)_t3870;
                ;
                Bool _t3871 = 0;
                (void)_t3871;
                Bool _t3872 = 0;
                (void)_t3872;
                FunctionDef *ffd = malloc(sizeof(FunctionDef));
                { FuncType *_ca = FuncType_clone(FuncType_Func()); ffd->func_type = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3848, &(U64){_t3849}); ffd->param_names = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3850, &(U64){_t3851}); ffd->param_types = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3852, &(U64){_t3853}); ffd->param_muts = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3854, &(U64){_t3855}); ffd->param_owns = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3856, &(U64){_t3857}); ffd->param_shallows = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3858, &(U64){_t3859}); ffd->param_fn_sigs = *_ca; free(_ca); }
                ffd->nparam = _t3868;
                { Vec *_ca = Vec_new(_t3860, &(U64){_t3861}); ffd->param_defaults = *_ca; free(_ca); }
                { Str *_ca = Str_clone(Str_lit("", 0ULL)); ffd->return_type = *_ca; free(_ca); }
                ffd->variadic_index = _t3869;
                ffd->kwargs_index = _t3870;
                ffd->return_is_ref = _t3871;
                ffd->return_is_shallow = _t3872;
                (void)ffd;
                Str_delete(_t3848, &(Bool){1});
                ;
                Str_delete(_t3850, &(Bool){1});
                ;
                Str_delete(_t3852, &(Bool){1});
                ;
                Str_delete(_t3854, &(Bool){1});
                ;
                Str_delete(_t3856, &(Bool){1});
                ;
                Str_delete(_t3858, &(Bool){1});
                ;
                Str_delete(_t3860, &(Bool){1});
                ;
                ;
                ;
                ;
                ;
                ;
                FuncType_delete(&ffd->func_type, &(Bool){0});
                { FuncType *_fa = FuncType_clone(FuncType_Func()); ffd->func_type = *_fa; free(_fa); }
                I64 _t3873 = 0;
                (void)_t3873;
                I64 _t3874 = 1;
                (void)_t3874;
                I64 _t3875 = I64_sub(_t3873, _t3874);
                (void)_t3875;
                ;
                ;
                I32 _t3876 = I64_to_i32(_t3875);
                (void)_t3876;
                ;
                ffd->variadic_index = _t3876;
                ;
                I64 _t3877 = 0;
                (void)_t3877;
                I64 _t3878 = 1;
                (void)_t3878;
                I64 _t3879 = I64_sub(_t3877, _t3878);
                (void)_t3879;
                ;
                ;
                I32 _t3880 = I64_to_i32(_t3879);
                (void)_t3880;
                ;
                ffd->kwargs_index = _t3880;
                ;
                U64 np; { U64 *_hp = (U64 *)Vec_len(pnames); np = *_hp; free(_hp); }
                (void)np;
                {
                    U64 _fi3824 = 0;
                    (void)_fi3824;
                    while (1) {
                        U64 _t3826 = 0;
                        (void)_t3826;
                        Range *_t3827 = Range_new(_t3826, np);
                        (void)_t3827;
                        ;
                        U64 _t3828; { U64 *_hp = (U64 *)Range_len(_t3827); _t3828 = *_hp; free(_hp); }
                        (void)_t3828;
                        Range_delete(_t3827, &(Bool){1});
                        Bool _wcond3825; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3824}, &(U64){_t3828}); _wcond3825 = *_hp; free(_hp); }
                        (void)_wcond3825;
                        ;
                        if (_wcond3825) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 _t3829 = 0;
                        (void)_t3829;
                        Range *_t3830 = Range_new(_t3829, np);
                        (void)_t3830;
                        ;
                        U64 _; { U64 *_hp = (U64 *)Range_get(_t3830, _fi3824); _ = *_hp; free(_hp); }
                        (void)_;
                        ;
                        Range_delete(_t3830, &(Bool){1});
                        U64 _t3831 = 1;
                        (void)_t3831;
                        U64 _t3832 = U64_add(_fi3824, _t3831);
                        (void)_t3832;
                        ;
                        _fi3824 = _t3832;
                        ;
                        Str *_t3833 = Str_lit("", 0ULL);
                        (void)_t3833;
                        Vec_push(&ffd->param_types, _t3833);
                        Bool _t3834 = 0;
                        (void)_t3834;
                        Vec_push(&ffd->param_muts, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3834; _oa; }));
                        Bool _t3835 = 0;
                        (void)_t3835;
                        Vec_push(&ffd->param_owns, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3835; _oa; }));
                        Bool _t3836 = 0;
                        (void)_t3836;
                        Vec_push(&ffd->param_shallows, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3836; _oa; }));
                        I64 _t3837 = 0;
                        (void)_t3837;
                        I64 _t3838 = 1;
                        (void)_t3838;
                        I64 _t3839 = I64_sub(_t3837, _t3838);
                        (void)_t3839;
                        ;
                        ;
                        Vec_push(&ffd->param_defaults, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = _t3839; _oa; }));
                        I64 _t3840 = 0;
                        (void)_t3840;
                        I64 _t3841 = 1;
                        (void)_t3841;
                        I64 _t3842 = I64_sub(_t3840, _t3841);
                        (void)_t3842;
                        ;
                        ;
                        Vec_push(&ffd->param_fn_sigs, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = _t3842; _oa; }));
                    }
                    ;
                }
                Vec_delete(&ffd->param_names, &(Bool){0});
                { Vec *_fa = Vec_clone(pnames); ffd->param_names = *_fa; free(_fa); }
                Vec_delete(pnames, &(Bool){1});
                I64 _t3881 = U64_to_i64(np);
                (void)_t3881;
                ;
                U32 _t3882 = I64_to_u32(_t3881);
                (void)_t3882;
                ;
                ffd->nparam = _t3882;
                ;
                ExprData *_t3883 = ExprData_FuncDef(ffd);
                (void)_t3883;
                FunctionDef_delete(ffd, &(Bool){1});
                Expr *fdef = Expr_new(_t3883, t_line, t_col, &p->path);
                (void)fdef;
                ExprData_delete(_t3883, &(Bool){1});
                Expr_add_child(fdef, body);
                Bool _t3884 = Bool_clone(&(Bool){is_mut});
                (void)_t3884;
                Bool _t3885 = 0;
                (void)_t3885;
                Bool _t3886 = 0;
                (void)_t3886;
                Bool _t3887 = Bool_clone(&(Bool){is_own});
                (void)_t3887;
                I32 _t3888 = 0;
                (void)_t3888;
                I32 _t3889 = 0;
                (void)_t3889;
                Declaration *dd = malloc(sizeof(Declaration));
                { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
                { Str *_ca = Str_clone(type_name); dd->explicit_type = *_ca; free(_ca); }
                dd->is_mut = _t3884;
                dd->is_namespace = _t3885;
                dd->is_ref = _t3886;
                dd->is_own = _t3887;
                dd->field_offset = _t3888;
                dd->field_size = _t3889;
                dd->field_struct_def = NULL;
                dd->fn_sig = NULL;
                (void)dd;
                ;
                ;
                ;
                ;
                ;
                ;
                ExprData *_t3890 = ExprData_Decl(dd);
                (void)_t3890;
                Declaration_delete(dd, &(Bool){1});
                Expr *decl = Expr_new(_t3890, t_line, t_col, &p->path);
                (void)decl;
                ExprData_delete(_t3890, &(Bool){1});
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
        Bool _t3905 = Bool_clone(&(Bool){is_mut});
        (void)_t3905;
        Bool _t3906 = 0;
        (void)_t3906;
        Bool _t3907 = 0;
        (void)_t3907;
        Bool _t3908 = Bool_clone(&(Bool){is_own});
        (void)_t3908;
        I32 _t3909 = 0;
        (void)_t3909;
        I32 _t3910 = 0;
        (void)_t3910;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(type_name); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3905;
        dd->is_namespace = _t3906;
        dd->is_ref = _t3907;
        dd->is_own = _t3908;
        dd->field_offset = _t3909;
        dd->field_size = _t3910;
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
        ExprData *_t3911 = ExprData_Decl(dd);
        (void)_t3911;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3911, t_line, t_col, &p->path);
        (void)decl;
        ExprData_delete(_t3911, &(Bool){1});
        Expr *_t3912 = parse_expression(p);
        (void)_t3912;
        Expr_add_child(decl, _t3912);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return decl;
    }
    ;
    Bool _t3965 = check(p, TokenType_Dot());
    (void)_t3965;
    if (_t3965) {
        Str *_t3951 = Str_clone(name);
        (void)_t3951;
        ExprData *_t3952 = ExprData_Ident(_t3951);
        (void)_t3952;
        Str_delete(_t3951, &(Bool){1});
        Expr *obj = Expr_new(_t3952, t_line, t_col, &p->path);
        (void)obj;
        ExprData_delete(_t3952, &(Bool){1});
        Str *last_field = Str_lit("", 0ULL);
        (void)last_field;
        U32 last_line = 0;
        (void)last_line;
        U32 last_col = 0;
        (void)last_col;
        while (1) {
            Bool _wcond3913 = check(p, TokenType_Dot());
            (void)_wcond3913;
            if (_wcond3913) {
            } else {
                ;
                break;
            }
            ;
            Token *_t3917 = advance(p);
            (void)_t3917;
            U32 _t3918 = peek_line(p);
            (void)_t3918;
            last_line = _t3918;
            ;
            U32 _t3919 = peek_col(p);
            (void)_t3919;
            last_col = _t3919;
            ;
            last_field = expect_text(p, TokenType_Ident());
            Bool _t3920 = check(p, TokenType_Dot());
            (void)_t3920;
            if (_t3920) {
                Str *_t3914 = Str_clone(last_field);
                (void)_t3914;
                ExprData *_t3915 = ExprData_FieldAccess(_t3914);
                (void)_t3915;
                Str_delete(_t3914, &(Bool){1});
                Expr *access = Expr_new(_t3915, last_line, last_col, &p->path);
                (void)access;
                ExprData_delete(_t3915, &(Bool){1});
                Expr *_t3916 = Expr_clone(obj);
                (void)_t3916;
                Expr_add_child(access, _t3916);
                obj = Expr_clone(access);
                Expr_delete(access, &(Bool){1});
            }
            ;
        }
        Bool _t3953 = check(p, TokenType_LParen());
        (void)_t3953;
        if (_t3953) {
            Token *_t3947 = advance(p);
            (void)_t3947;
            ExprData *_t3948 = ExprData_FieldAccess(last_field);
            (void)_t3948;
            Expr *callee = Expr_new(_t3948, last_line, last_col, &p->path);
            (void)callee;
            ExprData_delete(_t3948, &(Bool){1});
            Expr *_t3949 = Expr_clone(obj);
            (void)_t3949;
            Expr_add_child(callee, _t3949);
            Expr *mcall = Expr_new(ExprData_FCall(), last_line, last_col, &p->path);
            (void)mcall;
            Expr_add_child(mcall, callee);
            while (1) {
                Bool _t3939 = check(p, TokenType_RParen());
                (void)_t3939;
                Bool _t3940 = check(p, TokenType_Eof());
                (void)_t3940;
                Bool _t3941 = Bool_not(_t3939);
                (void)_t3941;
                ;
                Bool _t3942 = Bool_not(_t3940);
                (void)_t3942;
                ;
                Bool _wcond3921 = Bool_and(_t3941, _t3942);
                (void)_wcond3921;
                ;
                ;
                if (_wcond3921) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3943 = check(p, TokenType_Ident());
                (void)_t3943;
                if (_t3943) {
                    U64 _t3932 = 1;
                    (void)_t3932;
                    U64 _t3933 = U64_add(p->pos, _t3932);
                    (void)_t3933;
                    ;
                    U64 _t3934; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3934 = *_hp; free(_hp); }
                    (void)_t3934;
                    Bool _t3935; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3933}, &(U64){_t3934}); _t3935 = *_hp; free(_hp); }
                    (void)_t3935;
                    ;
                    ;
                    if (_t3935) {
                        U64 _t3927 = 1;
                        (void)_t3927;
                        U64 _t3928 = U64_add(p->pos, _t3927);
                        (void)_t3928;
                        ;
                        I64 _t3929 = U64_to_i64(_t3928);
                        (void)_t3929;
                        ;
                        U64 *_t3930 = malloc(sizeof(U64)); *_t3930 = I64_to_u64(_t3929);
                        (void)_t3930;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3930);
                        (void)nt;
                        Bool _t3931; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3931 = *_hp; free(_hp); }
                        (void)_t3931;
                        U64_delete(_t3930, &(Bool){1});
                        if (_t3931) {
                            U32 na_line = peek_line(p);
                            (void)na_line;
                            U32 na_col = peek_col(p);
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3923 = advance(p);
                            (void)_t3923;
                            ExprData *_t3924 = ExprData_NamedArg(aname);
                            (void)_t3924;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3924, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3924, &(Bool){1});
                            ;
                            ;
                            Expr *_t3925 = parse_expression(p);
                            (void)_t3925;
                            Expr_add_child(na, _t3925);
                            Expr_add_child(mcall, na);
                            Bool _t3926 = check(p, TokenType_Comma());
                            (void)_t3926;
                            if (_t3926) {
                                Token *_t3922 = advance(p);
                                (void)_t3922;
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
                Bool _t3944 = check(p, TokenType_KwOwn());
                (void)_t3944;
                if (_t3944) {
                    Token *_t3936 = advance(p);
                    (void)_t3936;
                    Bool _t3937 = 1;
                    (void)_t3937;
                    is_own_arg = _t3937;
                    ;
                }
                ;
                Expr *marg = parse_expression(p);
                (void)marg;
                Bool _t3945 = Bool_clone(&(Bool){is_own_arg});
                (void)_t3945;
                ;
                marg->is_own_arg = _t3945;
                ;
                Expr_add_child(mcall, marg);
                Bool _t3946 = check(p, TokenType_Comma());
                (void)_t3946;
                if (_t3946) {
                    Token *_t3938 = advance(p);
                    (void)_t3938;
                }
                ;
            }
            Token *_t3950 = expect_token(p, TokenType_RParen());
            (void)_t3950;
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
        Token *_t3954 = expect_token(p, TokenType_Eq());
        (void)_t3954;
        ExprData *_t3955 = ExprData_FieldAssign(last_field);
        (void)_t3955;
        Str_delete(last_field, &(Bool){1});
        Expr *fa = Expr_new(_t3955, t_line, t_col, &p->path);
        (void)fa;
        ExprData_delete(_t3955, &(Bool){1});
        Expr *_t3956 = Expr_clone(obj);
        (void)_t3956;
        Expr_delete(obj, &(Bool){1});
        Expr_add_child(fa, _t3956);
        Expr *_t3957 = parse_expression(p);
        (void)_t3957;
        Expr_add_child(fa, _t3957);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return fa;
    }
    ;
    Bool _t3966 = check(p, TokenType_Eq());
    (void)_t3966;
    if (_t3966) {
        Token *_t3958 = advance(p);
        (void)_t3958;
        Str *_t3959 = Str_clone(name);
        (void)_t3959;
        ExprData *_t3960 = ExprData_Assign(_t3959);
        (void)_t3960;
        Str_delete(_t3959, &(Bool){1});
        Expr *assign = Expr_new(_t3960, t_line, t_col, &p->path);
        (void)assign;
        ExprData_delete(_t3960, &(Bool){1});
        Expr *_t3961 = parse_expression(p);
        (void)_t3961;
        Expr_add_child(assign, _t3961);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return assign;
    }
    ;
    Bool _t3967 = check(p, TokenType_LParen());
    (void)_t3967;
    if (_t3967) {
        Expr *_t3962 = parse_call(p, name, t_line, t_col);
        (void)_t3962;
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return _t3962;
    }
    ;
    Str *_t3968 = Str_lit("Str", 3ULL);
    (void)_t3968;
    U64 _t3969; { U64 *_hp = (U64 *)Str_size(); _t3969 = *_hp; free(_hp); }
    (void)_t3969;
    U64 _t3970 = 8;
    (void)_t3970;
    Array *_va69 = Array_new(_t3968, &(U64){_t3969}, &(U64){_t3970});
    (void)_va69;
    Str_delete(_t3968, &(Bool){1});
    ;
    ;
    U64 _t3971 = 0;
    (void)_t3971;
    Str *_t3972 = Str_clone(&p->path);
    (void)_t3972;
    Array_set(_va69, &(U64){_t3971}, _t3972);
    ;
    U64 _t3973 = 1;
    (void)_t3973;
    Str *_t3974 = Str_lit(":", 1ULL);
    (void)_t3974;
    Array_set(_va69, &(U64){_t3973}, _t3974);
    ;
    U64 _t3975 = 2;
    (void)_t3975;
    Str *_t3976 = U32_to_str(&(U32){t_line});
    (void)_t3976;
    ;
    Array_set(_va69, &(U64){_t3975}, _t3976);
    ;
    U64 _t3977 = 3;
    (void)_t3977;
    Str *_t3978 = Str_lit(":", 1ULL);
    (void)_t3978;
    Array_set(_va69, &(U64){_t3977}, _t3978);
    ;
    U64 _t3979 = 4;
    (void)_t3979;
    Str *_t3980 = U32_to_str(&(U32){t_col});
    (void)_t3980;
    ;
    Array_set(_va69, &(U64){_t3979}, _t3980);
    ;
    U64 _t3981 = 5;
    (void)_t3981;
    Str *_t3982 = Str_lit(": expected ':=', ':', '=' or '(' after identifier '", 51ULL);
    (void)_t3982;
    Array_set(_va69, &(U64){_t3981}, _t3982);
    ;
    U64 _t3983 = 6;
    (void)_t3983;
    Str *_t3984 = Str_clone(name);
    (void)_t3984;
    Str_delete(name, &(Bool){1});
    Array_set(_va69, &(U64){_t3983}, _t3984);
    ;
    U64 _t3985 = 7;
    (void)_t3985;
    Str *_t3986 = Str_lit("'", 1ULL);
    (void)_t3986;
    Array_set(_va69, &(U64){_t3985}, _t3986);
    ;
    Str *_t3987 = Str_lit("src/self/parser.til:789:11", 26ULL);
    (void)_t3987;
    panic(_t3987, _va69);
    Str_delete(_t3987, &(Bool){1});
    U32 _t3988 = 0;
    (void)_t3988;
    U32 _t3989 = 0;
    (void)_t3989;
    Expr *_t3990 = Expr_new(ExprData_Body(), _t3988, _t3989, &p->path);
    (void)_t3990;
    ;
    ;
    return _t3990;
}

Expr * parse_statement(Parser * p) {
    (void)p;
    U32 t_line = peek_line(p);
    (void)t_line;
    U32 t_col = peek_col(p);
    (void)t_col;
    Token *t = peek(p);
    (void)t;
    Bool _t4128; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t4128 = *_hp; free(_hp); }
    (void)_t4128;
    if (_t4128) {
        Bool _t3991 = 0;
        (void)_t3991;
        Bool _t3992 = 0;
        (void)_t3992;
        Expr *_t3993 = parse_statement_ident(p, _t3991, _t3992);
        (void)_t3993;
        ;
        ;
        ;
        ;
        ;
        return _t3993;
    }
    ;
    Bool _t4129; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwRef()); _t4129 = *_hp; free(_hp); }
    (void)_t4129;
    if (_t4129) {
        Token *_t4000 = advance(p);
        (void)_t4000;
        Bool ref_mut = 0;
        (void)ref_mut;
        Bool _t4001 = check(p, TokenType_KwMut());
        (void)_t4001;
        if (_t4001) {
            Token *_t3994 = advance(p);
            (void)_t3994;
            Bool _t3995 = 1;
            (void)_t3995;
            ref_mut = _t3995;
            ;
        }
        ;
        U32 i_line = peek_line(p);
        (void)i_line;
        U32 i_col = peek_col(p);
        (void)i_col;
        Str *iname = expect_text(p, TokenType_Ident());
        (void)iname;
        Bool _t4002 = 0;
        (void)_t4002;
        Bool _t4003 = 0;
        (void)_t4003;
        Bool _t4004 = 1;
        (void)_t4004;
        Bool _t4005 = 0;
        (void)_t4005;
        I32 _t4006 = 0;
        (void)_t4006;
        I32 _t4007 = 0;
        (void)_t4007;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(iname); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t4002;
        dd->is_namespace = _t4003;
        dd->is_ref = _t4004;
        dd->is_own = _t4005;
        dd->field_offset = _t4006;
        dd->field_size = _t4007;
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
            Bool _t3996 = 1;
            (void)_t3996;
            dd->is_mut = _t3996;
            ;
        }
        ;
        Bool _t4008 = check(p, TokenType_Colon());
        (void)_t4008;
        if (_t4008) {
            Token *_t3997 = advance(p);
            (void)_t3997;
            Str_delete(&dd->explicit_type, &(Bool){0});
            { Str *_fa = expect_text(p, TokenType_Ident()); dd->explicit_type = *_fa; free(_fa); }
            Token *_t3998 = expect_token(p, TokenType_Eq());
            (void)_t3998;
        } else {
            Token *_t3999 = expect_token(p, TokenType_ColonEq());
            (void)_t3999;
        }
        ;
        ExprData *_t4009 = ExprData_Decl(dd);
        (void)_t4009;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t4009, i_line, i_col, &p->path);
        (void)decl;
        ExprData_delete(_t4009, &(Bool){1});
        ;
        ;
        Expr *_t4010 = parse_expression(p);
        (void)_t4010;
        Expr_add_child(decl, _t4010);
        ;
        ;
        ;
        return decl;
    }
    ;
    Bool _t4130; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMut()); _t4130 = *_hp; free(_hp); }
    (void)_t4130;
    if (_t4130) {
        Token *_t4011 = advance(p);
        (void)_t4011;
        Bool _t4012 = 1;
        (void)_t4012;
        Bool _t4013 = 0;
        (void)_t4013;
        Expr *_t4014 = parse_statement_ident(p, _t4012, _t4013);
        (void)_t4014;
        ;
        ;
        ;
        ;
        ;
        return _t4014;
    }
    ;
    Bool _t4131; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwReturn()); _t4131 = *_hp; free(_hp); }
    (void)_t4131;
    if (_t4131) {
        Token *_t4016 = advance(p);
        (void)_t4016;
        Expr *ret = Expr_new(ExprData_Return(), t_line, t_col, &p->path);
        (void)ret;
        Bool _t4017 = check(p, TokenType_RBrace());
        (void)_t4017;
        Bool _t4018 = check(p, TokenType_Eof());
        (void)_t4018;
        Bool _t4019 = Bool_not(_t4017);
        (void)_t4019;
        ;
        Bool _t4020 = Bool_not(_t4018);
        (void)_t4020;
        ;
        Bool _t4021 = Bool_and(_t4019, _t4020);
        (void)_t4021;
        ;
        ;
        if (_t4021) {
            Expr *_t4015 = parse_expression(p);
            (void)_t4015;
            Expr_add_child(ret, _t4015);
        }
        ;
        ;
        ;
        ;
        return ret;
    }
    ;
    Bool _t4132; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwIf()); _t4132 = *_hp; free(_hp); }
    (void)_t4132;
    if (_t4132) {
        Token *_t4029 = advance(p);
        (void)_t4029;
        Expr *node = Expr_new(ExprData_If(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t4030 = parse_expression(p);
        (void)_t4030;
        Expr_add_child(node, _t4030);
        Token *_t4031 = expect_token(p, TokenType_LBrace());
        (void)_t4031;
        Expr *_t4032 = parse_block(p);
        (void)_t4032;
        Expr_add_child(node, _t4032);
        Bool _t4033 = check(p, TokenType_KwElse());
        (void)_t4033;
        if (_t4033) {
            Token *_t4027 = advance(p);
            (void)_t4027;
            Bool _t4028 = check(p, TokenType_KwIf());
            (void)_t4028;
            if (_t4028) {
                U32 _t4022 = peek_line(p);
                (void)_t4022;
                U32 _t4023 = peek_col(p);
                (void)_t4023;
                Expr *else_body = Expr_new(ExprData_Body(), _t4022, _t4023, &p->path);
                (void)else_body;
                ;
                ;
                Expr *_t4024 = parse_statement(p);
                (void)_t4024;
                Expr_add_child(else_body, _t4024);
                Expr_add_child(node, else_body);
            } else {
                Token *_t4025 = expect_token(p, TokenType_LBrace());
                (void)_t4025;
                Expr *_t4026 = parse_block(p);
                (void)_t4026;
                Expr_add_child(node, _t4026);
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
    Bool _t4133; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t4133 = *_hp; free(_hp); }
    (void)_t4133;
    Bool _t4134; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t4134 = *_hp; free(_hp); }
    (void)_t4134;
    Bool _t4135 = Bool_or(_t4133, _t4134);
    (void)_t4135;
    ;
    ;
    Bool _t4136; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t4136 = *_hp; free(_hp); }
    (void)_t4136;
    Bool _t4137 = Bool_or(_t4135, _t4136);
    (void)_t4137;
    ;
    ;
    Bool _t4138; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t4138 = *_hp; free(_hp); }
    (void)_t4138;
    Bool _t4139 = Bool_or(_t4137, _t4138);
    (void)_t4139;
    ;
    ;
    Bool _t4140; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwNull()); _t4140 = *_hp; free(_hp); }
    (void)_t4140;
    Bool _t4141 = Bool_or(_t4139, _t4140);
    (void)_t4141;
    ;
    ;
    if (_t4141) {
        Expr *_t4034 = parse_expression(p);
        (void)_t4034;
        ;
        ;
        ;
        return _t4034;
    }
    ;
    Bool _t4142; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t4142 = *_hp; free(_hp); }
    (void)_t4142;
    if (_t4142) {
        Token *_t4035 = advance(p);
        (void)_t4035;
        Expr *_t4036 = parse_block(p);
        (void)_t4036;
        ;
        ;
        ;
        return _t4036;
    }
    ;
    Bool _t4143; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwWhile()); _t4143 = *_hp; free(_hp); }
    (void)_t4143;
    if (_t4143) {
        Token *_t4037 = advance(p);
        (void)_t4037;
        Expr *node = Expr_new(ExprData_While(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t4038 = parse_expression(p);
        (void)_t4038;
        Expr_add_child(node, _t4038);
        Token *_t4039 = expect_token(p, TokenType_LBrace());
        (void)_t4039;
        Expr *_t4040 = parse_block(p);
        (void)_t4040;
        Expr_add_child(node, _t4040);
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4144; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFor()); _t4144 = *_hp; free(_hp); }
    (void)_t4144;
    if (_t4144) {
        Token *_t4042 = advance(p);
        (void)_t4042;
        U32 i_line = peek_line(p);
        (void)i_line;
        U32 i_col = peek_col(p);
        (void)i_col;
        Str *iname = expect_text(p, TokenType_Ident());
        (void)iname;
        ExprData *_t4043 = ExprData_ForIn(iname);
        (void)_t4043;
        Str_delete(iname, &(Bool){1});
        Expr *node = Expr_new(_t4043, i_line, i_col, &p->path);
        (void)node;
        ExprData_delete(_t4043, &(Bool){1});
        ;
        ;
        Bool _t4044 = check(p, TokenType_Colon());
        (void)_t4044;
        if (_t4044) {
            Token *_t4041 = advance(p);
            (void)_t4041;
            Str_delete(&node->struct_name, &(Bool){0});
            { Str *_fa = expect_text(p, TokenType_Ident()); node->struct_name = *_fa; free(_fa); }
        }
        ;
        Token *_t4045 = expect_token(p, TokenType_KwIn());
        (void)_t4045;
        Expr *_t4046 = parse_expression(p);
        (void)_t4046;
        Expr_add_child(node, _t4046);
        Token *_t4047 = expect_token(p, TokenType_LBrace());
        (void)_t4047;
        Expr *_t4048 = parse_block(p);
        (void)_t4048;
        Expr_add_child(node, _t4048);
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4145; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwSwitch()); _t4145 = *_hp; free(_hp); }
    (void)_t4145;
    if (_t4145) {
        Token *_t4072 = advance(p);
        (void)_t4072;
        Expr *node = Expr_new(ExprData_Switch(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t4073 = parse_expression(p);
        (void)_t4073;
        Expr_add_child(node, _t4073);
        Token *_t4074 = expect_token(p, TokenType_LBrace());
        (void)_t4074;
        while (1) {
            Bool _t4060 = check(p, TokenType_RBrace());
            (void)_t4060;
            Bool _t4061 = check(p, TokenType_Eof());
            (void)_t4061;
            Bool _t4062 = Bool_not(_t4060);
            (void)_t4062;
            ;
            Bool _t4063 = Bool_not(_t4061);
            (void)_t4063;
            ;
            Bool _wcond4049 = Bool_and(_t4062, _t4063);
            (void)_wcond4049;
            ;
            ;
            if (_wcond4049) {
            } else {
                ;
                break;
            }
            ;
            Token *_t4064 = expect_token(p, TokenType_KwCase());
            (void)_t4064;
            U32 _t4065 = peek_line(p);
            (void)_t4065;
            U32 _t4066 = peek_col(p);
            (void)_t4066;
            Expr *cn = Expr_new(ExprData_Case(), _t4065, _t4066, &p->path);
            (void)cn;
            ;
            ;
            Bool _t4067 = check(p, TokenType_Colon());
            (void)_t4067;
            Bool _t4068 = Bool_not(_t4067);
            (void)_t4068;
            ;
            if (_t4068) {
                Expr *_t4050 = parse_expression(p);
                (void)_t4050;
                Expr_add_child(cn, _t4050);
            }
            ;
            Token *_t4069 = expect_token(p, TokenType_Colon());
            (void)_t4069;
            U32 _t4070 = peek_line(p);
            (void)_t4070;
            U32 _t4071 = peek_col(p);
            (void)_t4071;
            Expr *cb = Expr_new(ExprData_Body(), _t4070, _t4071, &p->path);
            (void)cb;
            ;
            ;
            while (1) {
                Bool _t4052 = check(p, TokenType_KwCase());
                (void)_t4052;
                Bool _t4053 = check(p, TokenType_RBrace());
                (void)_t4053;
                Bool _t4054 = Bool_not(_t4052);
                (void)_t4054;
                ;
                Bool _t4055 = Bool_not(_t4053);
                (void)_t4055;
                ;
                Bool _t4056 = check(p, TokenType_Eof());
                (void)_t4056;
                Bool _t4057 = Bool_and(_t4054, _t4055);
                (void)_t4057;
                ;
                ;
                Bool _t4058 = Bool_not(_t4056);
                (void)_t4058;
                ;
                Bool _wcond4051 = Bool_and(_t4057, _t4058);
                (void)_wcond4051;
                ;
                ;
                if (_wcond4051) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t4059 = parse_statement(p);
                (void)_t4059;
                Expr_add_child(cb, _t4059);
            }
            Expr_add_child(cn, cb);
            Expr_add_child(node, cn);
        }
        Token *_t4075 = expect_token(p, TokenType_RBrace());
        (void)_t4075;
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4146; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwOwn()); _t4146 = *_hp; free(_hp); }
    (void)_t4146;
    if (_t4146) {
        Token *_t4117 = advance(p);
        (void)_t4117;
        Bool _t4118 = check(p, TokenType_Ident());
        (void)_t4118;
        Bool _t4119 = check(p, TokenType_KwMut());
        (void)_t4119;
        Bool _t4120 = Bool_or(_t4118, _t4119);
        (void)_t4120;
        ;
        ;
        if (_t4120) {
            Bool own_mut = 0;
            (void)own_mut;
            Bool _t4107 = check(p, TokenType_KwMut());
            (void)_t4107;
            if (_t4107) {
                Token *_t4076 = advance(p);
                (void)_t4076;
                Bool _t4077 = 1;
                (void)_t4077;
                own_mut = _t4077;
                ;
            }
            ;
            Bool _t4108 = check(p, TokenType_Ident());
            (void)_t4108;
            if (_t4108) {
                U64 _t4087 = 1;
                (void)_t4087;
                U64 _t4088 = U64_add(p->pos, _t4087);
                (void)_t4088;
                ;
                U64 _t4089; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t4089 = *_hp; free(_hp); }
                (void)_t4089;
                Bool _t4090; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4088}, &(U64){_t4089}); _t4090 = *_hp; free(_hp); }
                (void)_t4090;
                ;
                ;
                if (_t4090) {
                    U64 _t4080 = 1;
                    (void)_t4080;
                    U64 _t4081 = U64_add(p->pos, _t4080);
                    (void)_t4081;
                    ;
                    I64 _t4082 = U64_to_i64(_t4081);
                    (void)_t4082;
                    ;
                    U64 *_t4083 = malloc(sizeof(U64)); *_t4083 = I64_to_u64(_t4082);
                    (void)_t4083;
                    ;
                    Token *nt = Vec_get(&p->tokens, _t4083);
                    (void)nt;
                    Bool _t4084; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_ColonEq()); _t4084 = *_hp; free(_hp); }
                    (void)_t4084;
                    Bool _t4085; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Colon()); _t4085 = *_hp; free(_hp); }
                    (void)_t4085;
                    U64_delete(_t4083, &(Bool){1});
                    Bool _t4086 = Bool_or(_t4084, _t4085);
                    (void)_t4086;
                    ;
                    ;
                    if (_t4086) {
                        Bool _t4078 = 1;
                        (void)_t4078;
                        Expr *_t4079 = parse_statement_ident(p, own_mut, _t4078);
                        (void)_t4079;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        return _t4079;
                    }
                    ;
                }
                ;
            }
            ;
            if (own_mut) {
                Str *_t4091 = Str_lit("Str", 3ULL);
                (void)_t4091;
                U64 _t4092; { U64 *_hp = (U64 *)Str_size(); _t4092 = *_hp; free(_hp); }
                (void)_t4092;
                U64 _t4093 = 6;
                (void)_t4093;
                Array *_va70 = Array_new(_t4091, &(U64){_t4092}, &(U64){_t4093});
                (void)_va70;
                Str_delete(_t4091, &(Bool){1});
                ;
                ;
                U64 _t4094 = 0;
                (void)_t4094;
                Str *_t4095 = Str_clone(&p->path);
                (void)_t4095;
                Array_set(_va70, &(U64){_t4094}, _t4095);
                ;
                U64 _t4096 = 1;
                (void)_t4096;
                Str *_t4097 = Str_lit(":", 1ULL);
                (void)_t4097;
                Array_set(_va70, &(U64){_t4096}, _t4097);
                ;
                U64 _t4098 = 2;
                (void)_t4098;
                Str *_t4099 = U32_to_str(&(U32){t_line});
                (void)_t4099;
                Array_set(_va70, &(U64){_t4098}, _t4099);
                ;
                U64 _t4100 = 3;
                (void)_t4100;
                Str *_t4101 = Str_lit(":", 1ULL);
                (void)_t4101;
                Array_set(_va70, &(U64){_t4100}, _t4101);
                ;
                U64 _t4102 = 4;
                (void)_t4102;
                Str *_t4103 = U32_to_str(&(U32){t_col});
                (void)_t4103;
                Array_set(_va70, &(U64){_t4102}, _t4103);
                ;
                U64 _t4104 = 5;
                (void)_t4104;
                Str *_t4105 = Str_lit(": expected identifier after 'own mut'", 37ULL);
                (void)_t4105;
                Array_set(_va70, &(U64){_t4104}, _t4105);
                ;
                Str *_t4106 = Str_lit("src/self/parser.til:923:23", 26ULL);
                (void)_t4106;
                panic(_t4106, _va70);
                Str_delete(_t4106, &(Bool){1});
            }
            ;
        }
        ;
        Expr *expr = parse_expression(p);
        (void)expr;
        I64 _t4121 = 0;
        (void)_t4121;
        I64 _t4122 = 1;
        (void)_t4122;
        I64 primary_idx = I64_sub(_t4121, _t4122);
        (void)primary_idx;
        ;
        ;
        ;
        Expr *cur = Expr_clone(expr);
        (void)cur;
        while (1) {
            U64 _t4110; { U64 *_hp = (U64 *)Vec_len(&cur->children); _t4110 = *_hp; free(_hp); }
            (void)_t4110;
            U64 _t4111 = 0;
            (void)_t4111;
            Bool _t4112; { Bool *_hp = (Bool *)ExprData_is_FCall(&cur->data); _t4112 = *_hp; free(_hp); }
            (void)_t4112;
            Bool _t4113; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(&cur->data); _t4113 = *_hp; free(_hp); }
            (void)_t4113;
            Bool _t4114; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4110}, &(U64){_t4111}); _t4114 = *_hp; free(_hp); }
            (void)_t4114;
            ;
            ;
            Bool _t4115 = Bool_or(_t4112, _t4113);
            (void)_t4115;
            ;
            ;
            Bool _wcond4109 = Bool_and(_t4114, _t4115);
            (void)_wcond4109;
            ;
            ;
            if (_wcond4109) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t4116 = malloc(sizeof(U64));
            *_t4116 = 0;
            (void)_t4116;
            Expr *ch = Vec_get(&cur->children, _t4116);
            (void)ch;
            cur = Expr_clone(ch);
            U64_delete(_t4116, &(Bool){1});
        }
        Bool _t4123 = 1;
        (void)_t4123;
        cur->is_own_arg = _t4123;
        ;
        Expr_delete(cur, &(Bool){1});
        ;
        ;
        ;
        ;
        return expr;
    }
    ;
    Bool _t4147; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwBreak()); _t4147 = *_hp; free(_hp); }
    (void)_t4147;
    if (_t4147) {
        Token *_t4124 = advance(p);
        (void)_t4124;
        Expr *_t4125 = Expr_new(ExprData_Break(), t_line, t_col, &p->path);
        (void)_t4125;
        ;
        ;
        ;
        return _t4125;
    }
    ;
    Bool _t4148; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwContinue()); _t4148 = *_hp; free(_hp); }
    (void)_t4148;
    if (_t4148) {
        Token *_t4126 = advance(p);
        (void)_t4126;
        Expr *_t4127 = Expr_new(ExprData_Continue(), t_line, t_col, &p->path);
        (void)_t4127;
        ;
        ;
        ;
        return _t4127;
    }
    ;
    Str *_t4149 = Str_lit("Str", 3ULL);
    (void)_t4149;
    U64 _t4150; { U64 *_hp = (U64 *)Str_size(); _t4150 = *_hp; free(_hp); }
    (void)_t4150;
    U64 _t4151 = 8;
    (void)_t4151;
    Array *_va71 = Array_new(_t4149, &(U64){_t4150}, &(U64){_t4151});
    (void)_va71;
    Str_delete(_t4149, &(Bool){1});
    ;
    ;
    U64 _t4152 = 0;
    (void)_t4152;
    Str *_t4153 = Str_clone(&p->path);
    (void)_t4153;
    Array_set(_va71, &(U64){_t4152}, _t4153);
    ;
    U64 _t4154 = 1;
    (void)_t4154;
    Str *_t4155 = Str_lit(":", 1ULL);
    (void)_t4155;
    Array_set(_va71, &(U64){_t4154}, _t4155);
    ;
    U64 _t4156 = 2;
    (void)_t4156;
    Str *_t4157 = U32_to_str(&(U32){t_line});
    (void)_t4157;
    ;
    Array_set(_va71, &(U64){_t4156}, _t4157);
    ;
    U64 _t4158 = 3;
    (void)_t4158;
    Str *_t4159 = Str_lit(":", 1ULL);
    (void)_t4159;
    Array_set(_va71, &(U64){_t4158}, _t4159);
    ;
    U64 _t4160 = 4;
    (void)_t4160;
    Str *_t4161 = U32_to_str(&(U32){t_col});
    (void)_t4161;
    ;
    Array_set(_va71, &(U64){_t4160}, _t4161);
    ;
    U64 _t4162 = 5;
    (void)_t4162;
    Str *_t4163 = Str_lit(": expected statement, found '", 29ULL);
    (void)_t4163;
    Array_set(_va71, &(U64){_t4162}, _t4163);
    ;
    U64 _t4164 = 6;
    (void)_t4164;
    Str *_t4165 = Str_clone(&t->text);
    (void)_t4165;
    Array_set(_va71, &(U64){_t4164}, _t4165);
    ;
    U64 _t4166 = 7;
    (void)_t4166;
    Str *_t4167 = Str_lit("'", 1ULL);
    (void)_t4167;
    Array_set(_va71, &(U64){_t4166}, _t4167);
    ;
    Str *_t4168 = Str_lit("src/self/parser.til:950:11", 26ULL);
    (void)_t4168;
    panic(_t4168, _va71);
    Str_delete(_t4168, &(Bool){1});
    U32 _t4169 = 0;
    (void)_t4169;
    U32 _t4170 = 0;
    (void)_t4170;
    Expr *_t4171 = Expr_new(ExprData_Body(), _t4169, _t4170, &p->path);
    (void)_t4171;
    ;
    ;
    return _t4171;
}

Expr * parse(Vec * tokens, Str * path, Str * mode_out) {
    (void)tokens;
    (void)path;
    (void)mode_out;
    I64 _t4183 = 0;
    (void)_t4183;
    Parser *p = malloc(sizeof(Parser));
    { Vec *_ca = Vec_clone(tokens); p->tokens = *_ca; free(_ca); }
    p->pos = _t4183;
    { Str *_ca = Str_clone(path); p->path = *_ca; free(_ca); }
    (void)p;
    ;
    Bool _t4184 = check(p, TokenType_KwMode());
    (void)_t4184;
    if (_t4184) {
        Token *_t4176 = advance(p);
        (void)_t4176;
        Bool _t4177 = check(p, TokenType_Ident());
        (void)_t4177;
        Bool _t4178 = check(p, TokenType_KwTest());
        (void)_t4178;
        Bool _t4179 = Bool_or(_t4177, _t4178);
        (void)_t4179;
        ;
        ;
        if (_t4179) {
            Str *_t4172 = Str_clone(&peek(p)->text);
            (void)_t4172;
            U64 _t4173; { U64 *_hp = (U64 *)Str_size(); _t4173 = *_hp; free(_hp); }
            (void)_t4173;
            swap(mode_out, _t4172, _t4173);
            Str_delete(_t4172, &(Bool){1});
            ;
            Token *_t4174 = advance(p);
            (void)_t4174;
        } else {
            Token *_t4175 = expect_token(p, TokenType_Ident());
            (void)_t4175;
        }
        ;
    }
    ;
    U32 _t4185 = 1;
    (void)_t4185;
    U32 _t4186 = 1;
    (void)_t4186;
    Expr *root = Expr_new(ExprData_Body(), _t4185, _t4186, &p->path);
    (void)root;
    ;
    ;
    while (1) {
        Bool _t4181 = check(p, TokenType_Eof());
        (void)_t4181;
        Bool _wcond4180 = Bool_not(_t4181);
        (void)_wcond4180;
        ;
        if (_wcond4180) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t4182 = parse_statement(p);
        (void)_t4182;
        Expr_add_child(root, _t4182);
    }
    Parser_delete(p, &(Bool){1});
    return root;
}

