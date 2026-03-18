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
    U32 _t3709 = 0;
    (void)_t3709;
    U32 _t3710 = 0;
    (void)_t3710;
    Expr *e = Expr_new(ExprData_Body(), _t3709, _t3710, &p->path);
    (void)e;
    ;
    ;
    Bool e_set = 0;
    (void)e_set;
    Bool _t3711; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t3711 = *_hp; free(_hp); }
    (void)_t3711;
    if (_t3711) {
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
    Bool _t3712 = Bool_not(e_set);
    (void)_t3712;
    Bool _t3713; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t3713 = *_hp; free(_hp); }
    (void)_t3713;
    Bool _t3714 = Bool_and(_t3712, _t3713);
    (void)_t3714;
    ;
    ;
    if (_t3714) {
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
    Bool _t3715 = Bool_not(e_set);
    (void)_t3715;
    Bool _t3716; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Char()); _t3716 = *_hp; free(_hp); }
    (void)_t3716;
    Bool _t3717 = Bool_and(_t3715, _t3716);
    (void)_t3717;
    ;
    ;
    if (_t3717) {
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
    Bool _t3718; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t3718 = *_hp; free(_hp); }
    (void)_t3718;
    Bool _t3719; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t3719 = *_hp; free(_hp); }
    (void)_t3719;
    Bool _t3720 = Bool_not(e_set);
    (void)_t3720;
    Bool _t3721 = Bool_or(_t3718, _t3719);
    (void)_t3721;
    ;
    ;
    Bool _t3722 = Bool_and(_t3720, _t3721);
    (void)_t3722;
    ;
    ;
    if (_t3722) {
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
    Bool _t3723 = Bool_not(e_set);
    (void)_t3723;
    Bool _t3724; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwNull()); _t3724 = *_hp; free(_hp); }
    (void)_t3724;
    Bool _t3725 = Bool_and(_t3723, _t3724);
    (void)_t3725;
    ;
    ;
    if (_t3725) {
        Token *_t3575 = advance(p);
        (void)_t3575;
        e = Expr_new(ExprData_LiteralNull(), t_line, t_col, &p->path);
        Bool _t3576 = 1;
        (void)_t3576;
        e_set = _t3576;
        ;
    }
    ;
    Bool _t3726 = Bool_not(e_set);
    (void)_t3726;
    Bool _t3727; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t3727 = *_hp; free(_hp); }
    (void)_t3727;
    Bool _t3728 = Bool_and(_t3726, _t3727);
    (void)_t3728;
    ;
    ;
    if (_t3728) {
        Token *_t3612 = advance(p);
        (void)_t3612;
        Str *name = Str_clone(&t->text);
        (void)name;
        Str *_t3613 = Str_lit("__LOC__", 7ULL);
        (void)_t3613;
        Bool _t3614; { Bool *_hp = (Bool *)Str_eq(name, _t3613); _t3614 = *_hp; free(_hp); }
        (void)_t3614;
        Str_delete(_t3613, &(Bool){1});
        if (_t3614) {
            Str *_t3577 = Str_lit("Str", 3ULL);
            (void)_t3577;
            U64 _t3578; { U64 *_hp = (U64 *)Str_size(); _t3578 = *_hp; free(_hp); }
            (void)_t3578;
            U64 _t3579 = 5;
            (void)_t3579;
            Array *_va67 = Array_new(_t3577, &(U64){_t3578}, &(U64){_t3579});
            (void)_va67;
            Str_delete(_t3577, &(Bool){1});
            ;
            ;
            U64 _t3580 = 0;
            (void)_t3580;
            Str *_t3581 = Str_clone(&p->path);
            (void)_t3581;
            Array_set(_va67, &(U64){_t3580}, _t3581);
            ;
            U64 _t3582 = 1;
            (void)_t3582;
            Str *_t3583 = Str_lit(":", 1ULL);
            (void)_t3583;
            Array_set(_va67, &(U64){_t3582}, _t3583);
            ;
            U64 _t3584 = 2;
            (void)_t3584;
            Str *_t3585 = U32_to_str(&(U32){t_line});
            (void)_t3585;
            Array_set(_va67, &(U64){_t3584}, _t3585);
            ;
            U64 _t3586 = 3;
            (void)_t3586;
            Str *_t3587 = Str_lit(":", 1ULL);
            (void)_t3587;
            Array_set(_va67, &(U64){_t3586}, _t3587);
            ;
            U64 _t3588 = 4;
            (void)_t3588;
            Str *_t3589 = U32_to_str(&(U32){t_col});
            (void)_t3589;
            Array_set(_va67, &(U64){_t3588}, _t3589);
            ;
            Str *_t3590 = format(_va67);
            (void)_t3590;
            ExprData *_t3591 = ExprData_LiteralStr(_t3590);
            (void)_t3591;
            Str_delete(_t3590, &(Bool){1});
            e = Expr_new(_t3591, t_line, t_col, &p->path);
            ExprData_delete(_t3591, &(Bool){1});
            Bool _t3592 = 1;
            (void)_t3592;
            e_set = _t3592;
            ;
        } else {
            Str *_t3610 = Str_lit("__FILE__", 8ULL);
            (void)_t3610;
            Bool _t3611; { Bool *_hp = (Bool *)Str_eq(name, _t3610); _t3611 = *_hp; free(_hp); }
            (void)_t3611;
            Str_delete(_t3610, &(Bool){1});
            if (_t3611) {
                Str *_t3593 = Str_clone(&p->path);
                (void)_t3593;
                ExprData *_t3594 = ExprData_LiteralStr(_t3593);
                (void)_t3594;
                Str_delete(_t3593, &(Bool){1});
                e = Expr_new(_t3594, t_line, t_col, &p->path);
                ExprData_delete(_t3594, &(Bool){1});
                Bool _t3595 = 1;
                (void)_t3595;
                e_set = _t3595;
                ;
            } else {
                Str *_t3608 = Str_lit("__LINE__", 8ULL);
                (void)_t3608;
                Bool _t3609; { Bool *_hp = (Bool *)Str_eq(name, _t3608); _t3609 = *_hp; free(_hp); }
                (void)_t3609;
                Str_delete(_t3608, &(Bool){1});
                if (_t3609) {
                    Str *_t3596 = U32_to_str(&(U32){t_line});
                    (void)_t3596;
                    ExprData *_t3597 = ExprData_LiteralNum(_t3596);
                    (void)_t3597;
                    Str_delete(_t3596, &(Bool){1});
                    e = Expr_new(_t3597, t_line, t_col, &p->path);
                    ExprData_delete(_t3597, &(Bool){1});
                    Bool _t3598 = 1;
                    (void)_t3598;
                    e_set = _t3598;
                    ;
                } else {
                    Str *_t3606 = Str_lit("__COL__", 7ULL);
                    (void)_t3606;
                    Bool _t3607; { Bool *_hp = (Bool *)Str_eq(name, _t3606); _t3607 = *_hp; free(_hp); }
                    (void)_t3607;
                    Str_delete(_t3606, &(Bool){1});
                    if (_t3607) {
                        Str *_t3599 = U32_to_str(&(U32){t_col});
                        (void)_t3599;
                        ExprData *_t3600 = ExprData_LiteralNum(_t3599);
                        (void)_t3600;
                        Str_delete(_t3599, &(Bool){1});
                        e = Expr_new(_t3600, t_line, t_col, &p->path);
                        ExprData_delete(_t3600, &(Bool){1});
                        Bool _t3601 = 1;
                        (void)_t3601;
                        e_set = _t3601;
                        ;
                    } else {
                        Bool _t3605 = check(p, TokenType_LParen());
                        (void)_t3605;
                        if (_t3605) {
                            e = parse_call(p, name, t_line, t_col);
                            Bool _t3602 = 1;
                            (void)_t3602;
                            e_set = _t3602;
                            ;
                        } else {
                            ExprData *_t3603 = ExprData_Ident(name);
                            (void)_t3603;
                            e = Expr_new(_t3603, t_line, t_col, &p->path);
                            ExprData_delete(_t3603, &(Bool){1});
                            Bool _t3604 = 1;
                            (void)_t3604;
                            e_set = _t3604;
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
    Bool _t3729; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFunc()); _t3729 = *_hp; free(_hp); }
    (void)_t3729;
    Bool _t3730; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwProc()); _t3730 = *_hp; free(_hp); }
    (void)_t3730;
    Bool _t3731 = Bool_or(_t3729, _t3730);
    (void)_t3731;
    ;
    ;
    Bool _t3732; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTest()); _t3732 = *_hp; free(_hp); }
    (void)_t3732;
    Bool _t3733 = Bool_or(_t3731, _t3732);
    (void)_t3733;
    ;
    ;
    Bool _t3734; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMacro()); _t3734 = *_hp; free(_hp); }
    (void)_t3734;
    Bool _t3735 = Bool_or(_t3733, _t3734);
    (void)_t3735;
    ;
    ;
    Bool _t3736; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtFunc()); _t3736 = *_hp; free(_hp); }
    (void)_t3736;
    Bool _t3737 = Bool_or(_t3735, _t3736);
    (void)_t3737;
    ;
    ;
    Bool _t3738; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtProc()); _t3738 = *_hp; free(_hp); }
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
        Expr *_t3615 = parse_func_def(p);
        (void)_t3615;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3615;
    }
    ;
    Bool _t3742; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwStruct()); _t3742 = *_hp; free(_hp); }
    (void)_t3742;
    Bool _t3743; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtStruct()); _t3743 = *_hp; free(_hp); }
    (void)_t3743;
    Bool _t3744 = Bool_not(e_set);
    (void)_t3744;
    Bool _t3745 = Bool_or(_t3742, _t3743);
    (void)_t3745;
    ;
    ;
    Bool _t3746 = Bool_and(_t3744, _t3745);
    (void)_t3746;
    ;
    ;
    if (_t3746) {
        Expr *_t3616 = parse_struct_def(p);
        (void)_t3616;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3616;
    }
    ;
    Bool _t3747 = Bool_not(e_set);
    (void)_t3747;
    Bool _t3748; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwEnum()); _t3748 = *_hp; free(_hp); }
    (void)_t3748;
    Bool _t3749 = Bool_and(_t3747, _t3748);
    (void)_t3749;
    ;
    ;
    if (_t3749) {
        Expr *_t3617 = parse_enum_def(p);
        (void)_t3617;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3617;
    }
    ;
    Bool _t3750 = Bool_not(e_set);
    (void)_t3750;
    Bool _t3751; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t3751 = *_hp; free(_hp); }
    (void)_t3751;
    Bool _t3752 = Bool_and(_t3750, _t3751);
    (void)_t3752;
    ;
    ;
    if (_t3752) {
        Token *_t3642 = advance(p);
        (void)_t3642;
        Expr *first = parse_expression(p);
        (void)first;
        Bool _t3643 = check(p, TokenType_Colon());
        (void)_t3643;
        if (_t3643) {
            e = Expr_new(ExprData_MapLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Token *_t3629 = advance(p);
            (void)_t3629;
            Expr *_t3630 = parse_expression(p);
            (void)_t3630;
            Expr_add_child(e, _t3630);
            Bool _t3631 = check(p, TokenType_Comma());
            (void)_t3631;
            if (_t3631) {
                Token *_t3618 = advance(p);
                (void)_t3618;
            }
            ;
            while (1) {
                Bool _t3621 = check(p, TokenType_RBrace());
                (void)_t3621;
                Bool _t3622 = check(p, TokenType_Eof());
                (void)_t3622;
                Bool _t3623 = Bool_not(_t3621);
                (void)_t3623;
                ;
                Bool _t3624 = Bool_not(_t3622);
                (void)_t3624;
                ;
                Bool _wcond3619 = Bool_and(_t3623, _t3624);
                (void)_wcond3619;
                ;
                ;
                if (_wcond3619) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3625 = parse_expression(p);
                (void)_t3625;
                Expr_add_child(e, _t3625);
                Token *_t3626 = expect_token(p, TokenType_Colon());
                (void)_t3626;
                Expr *_t3627 = parse_expression(p);
                (void)_t3627;
                Expr_add_child(e, _t3627);
                Bool _t3628 = check(p, TokenType_Comma());
                (void)_t3628;
                if (_t3628) {
                    Token *_t3620 = advance(p);
                    (void)_t3620;
                }
                ;
            }
        } else {
            e = Expr_new(ExprData_SetLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Bool _t3641 = check(p, TokenType_Comma());
            (void)_t3641;
            if (_t3641) {
                Token *_t3632 = advance(p);
                (void)_t3632;
            }
            ;
            while (1) {
                Bool _t3635 = check(p, TokenType_RBrace());
                (void)_t3635;
                Bool _t3636 = check(p, TokenType_Eof());
                (void)_t3636;
                Bool _t3637 = Bool_not(_t3635);
                (void)_t3637;
                ;
                Bool _t3638 = Bool_not(_t3636);
                (void)_t3638;
                ;
                Bool _wcond3633 = Bool_and(_t3637, _t3638);
                (void)_wcond3633;
                ;
                ;
                if (_wcond3633) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3639 = parse_expression(p);
                (void)_t3639;
                Expr_add_child(e, _t3639);
                Bool _t3640 = check(p, TokenType_Comma());
                (void)_t3640;
                if (_t3640) {
                    Token *_t3634 = advance(p);
                    (void)_t3634;
                }
                ;
            }
        }
        ;
        Token *_t3644 = expect_token(p, TokenType_RBrace());
        (void)_t3644;
        Bool _t3645 = 1;
        (void)_t3645;
        e_set = _t3645;
        ;
    }
    ;
    Bool _t3753 = Bool_not(e_set);
    (void)_t3753;
    ;
    if (_t3753) {
        Str *_t3646 = Str_lit("Str", 3ULL);
        (void)_t3646;
        U64 _t3647; { U64 *_hp = (U64 *)Str_size(); _t3647 = *_hp; free(_hp); }
        (void)_t3647;
        U64 _t3648 = 8;
        (void)_t3648;
        Array *_va68 = Array_new(_t3646, &(U64){_t3647}, &(U64){_t3648});
        (void)_va68;
        Str_delete(_t3646, &(Bool){1});
        ;
        ;
        U64 _t3649 = 0;
        (void)_t3649;
        Str *_t3650 = Str_clone(&p->path);
        (void)_t3650;
        Array_set(_va68, &(U64){_t3649}, _t3650);
        ;
        U64 _t3651 = 1;
        (void)_t3651;
        Str *_t3652 = Str_lit(":", 1ULL);
        (void)_t3652;
        Array_set(_va68, &(U64){_t3651}, _t3652);
        ;
        U64 _t3653 = 2;
        (void)_t3653;
        Str *_t3654 = U32_to_str(&(U32){t_line});
        (void)_t3654;
        Array_set(_va68, &(U64){_t3653}, _t3654);
        ;
        U64 _t3655 = 3;
        (void)_t3655;
        Str *_t3656 = Str_lit(":", 1ULL);
        (void)_t3656;
        Array_set(_va68, &(U64){_t3655}, _t3656);
        ;
        U64 _t3657 = 4;
        (void)_t3657;
        Str *_t3658 = U32_to_str(&(U32){t_col});
        (void)_t3658;
        Array_set(_va68, &(U64){_t3657}, _t3658);
        ;
        U64 _t3659 = 5;
        (void)_t3659;
        Str *_t3660 = Str_lit(": unexpected token '", 20ULL);
        (void)_t3660;
        Array_set(_va68, &(U64){_t3659}, _t3660);
        ;
        U64 _t3661 = 6;
        (void)_t3661;
        Str *_t3662 = Str_clone(&t->text);
        (void)_t3662;
        Array_set(_va68, &(U64){_t3661}, _t3662);
        ;
        U64 _t3663 = 7;
        (void)_t3663;
        Str *_t3664 = Str_lit("'", 1ULL);
        (void)_t3664;
        Array_set(_va68, &(U64){_t3663}, _t3664);
        ;
        Str *_t3665 = Str_lit("src/self/parser.til:518:15", 26ULL);
        (void)_t3665;
        panic(_t3665, _va68);
        Str_delete(_t3665, &(Bool){1});
    }
    ;
    ;
    ;
    while (1) {
        Bool _wcond3666 = check(p, TokenType_Dot());
        (void)_wcond3666;
        if (_wcond3666) {
        } else {
            ;
            break;
        }
        ;
        Token *_t3699 = advance(p);
        (void)_t3699;
        U32 f_line = peek_line(p);
        (void)f_line;
        U32 f_col = peek_col(p);
        (void)f_col;
        Str *fname = expect_text(p, TokenType_Ident());
        (void)fname;
        Bool _t3700 = check(p, TokenType_LParen());
        (void)_t3700;
        if (_t3700) {
            Token *_t3693 = advance(p);
            (void)_t3693;
            ExprData *_t3694 = ExprData_FieldAccess(fname);
            (void)_t3694;
            Expr *callee = Expr_new(_t3694, f_line, f_col, &p->path);
            (void)callee;
            ExprData_delete(_t3694, &(Bool){1});
            Expr *_t3695 = Expr_clone(e);
            (void)_t3695;
            Expr_add_child(callee, _t3695);
            Expr *mcall = Expr_new(ExprData_FCall(), f_line, f_col, &p->path);
            (void)mcall;
            Expr_add_child(mcall, callee);
            while (1) {
                Bool _t3685 = check(p, TokenType_RParen());
                (void)_t3685;
                Bool _t3686 = check(p, TokenType_Eof());
                (void)_t3686;
                Bool _t3687 = Bool_not(_t3685);
                (void)_t3687;
                ;
                Bool _t3688 = Bool_not(_t3686);
                (void)_t3688;
                ;
                Bool _wcond3667 = Bool_and(_t3687, _t3688);
                (void)_wcond3667;
                ;
                ;
                if (_wcond3667) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3689 = check(p, TokenType_Ident());
                (void)_t3689;
                if (_t3689) {
                    U64 _t3678 = 1;
                    (void)_t3678;
                    U64 _t3679 = U64_add(p->pos, _t3678);
                    (void)_t3679;
                    ;
                    U64 _t3680; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3680 = *_hp; free(_hp); }
                    (void)_t3680;
                    Bool _t3681; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3679}, &(U64){_t3680}); _t3681 = *_hp; free(_hp); }
                    (void)_t3681;
                    ;
                    ;
                    if (_t3681) {
                        U64 _t3673 = 1;
                        (void)_t3673;
                        U64 _t3674 = U64_add(p->pos, _t3673);
                        (void)_t3674;
                        ;
                        I64 _t3675 = U64_to_i64(_t3674);
                        (void)_t3675;
                        ;
                        U64 *_t3676 = malloc(sizeof(U64)); *_t3676 = I64_to_u64(_t3675);
                        (void)_t3676;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3676);
                        (void)nt;
                        Bool _t3677; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3677 = *_hp; free(_hp); }
                        (void)_t3677;
                        U64_delete(_t3676, &(Bool){1});
                        if (_t3677) {
                            U32 na_line = peek_line(p);
                            (void)na_line;
                            U32 na_col = peek_col(p);
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3669 = advance(p);
                            (void)_t3669;
                            ExprData *_t3670 = ExprData_NamedArg(aname);
                            (void)_t3670;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3670, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3670, &(Bool){1});
                            ;
                            ;
                            Expr *_t3671 = parse_expression(p);
                            (void)_t3671;
                            Expr_add_child(na, _t3671);
                            Expr_add_child(mcall, na);
                            Bool _t3672 = check(p, TokenType_Comma());
                            (void)_t3672;
                            if (_t3672) {
                                Token *_t3668 = advance(p);
                                (void)_t3668;
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
                Bool _t3690 = check(p, TokenType_KwOwn());
                (void)_t3690;
                if (_t3690) {
                    Token *_t3682 = advance(p);
                    (void)_t3682;
                    Bool _t3683 = 1;
                    (void)_t3683;
                    is_own_arg = _t3683;
                    ;
                }
                ;
                Expr *marg = parse_expression(p);
                (void)marg;
                Bool _t3691 = Bool_clone(&(Bool){is_own_arg});
                (void)_t3691;
                ;
                marg->is_own_arg = _t3691;
                ;
                Expr_add_child(mcall, marg);
                Bool _t3692 = check(p, TokenType_Comma());
                (void)_t3692;
                if (_t3692) {
                    Token *_t3684 = advance(p);
                    (void)_t3684;
                }
                ;
            }
            Token *_t3696 = expect_token(p, TokenType_RParen());
            (void)_t3696;
            e = Expr_clone(mcall);
            Expr_delete(mcall, &(Bool){1});
        } else {
            ExprData *_t3697 = ExprData_FieldAccess(fname);
            (void)_t3697;
            Expr *access = Expr_new(_t3697, f_line, f_col, &p->path);
            (void)access;
            ExprData_delete(_t3697, &(Bool){1});
            Expr *_t3698 = Expr_clone(e);
            (void)_t3698;
            Expr_add_child(access, _t3698);
            e = Expr_clone(access);
            Expr_delete(access, &(Bool){1});
        }
        ;
        ;
        ;
        Str_delete(fname, &(Bool){1});
    }
    Bool _t3754 = check(p, TokenType_DotDot());
    (void)_t3754;
    if (_t3754) {
        U32 dt_line = peek_line(p);
        (void)dt_line;
        U32 dt_col = peek_col(p);
        (void)dt_col;
        Token *_t3701 = advance(p);
        (void)_t3701;
        Expr *rhs = parse_expression(p);
        (void)rhs;
        Str *_t3702 = Str_lit("Range", 5ULL);
        (void)_t3702;
        Str *_t3703 = Str_clone(_t3702);
        (void)_t3703;
        Str_delete(_t3702, &(Bool){1});
        ExprData *_t3704 = ExprData_Ident(_t3703);
        (void)_t3704;
        Str_delete(_t3703, &(Bool){1});
        Expr *range_ident = Expr_new(_t3704, dt_line, dt_col, &p->path);
        (void)range_ident;
        ExprData_delete(_t3704, &(Bool){1});
        Str *_t3705 = Str_lit("new", 3ULL);
        (void)_t3705;
        Str *_t3706 = Str_clone(_t3705);
        (void)_t3706;
        Str_delete(_t3705, &(Bool){1});
        ExprData *_t3707 = ExprData_FieldAccess(_t3706);
        (void)_t3707;
        Str_delete(_t3706, &(Bool){1});
        Expr *new_access = Expr_new(_t3707, dt_line, dt_col, &p->path);
        (void)new_access;
        ExprData_delete(_t3707, &(Bool){1});
        Expr_add_child(new_access, range_ident);
        Expr *rcall = Expr_new(ExprData_FCall(), dt_line, dt_col, &p->path);
        (void)rcall;
        ;
        ;
        Expr_add_child(rcall, new_access);
        Expr *_t3708 = Expr_clone(e);
        (void)_t3708;
        Expr_add_child(rcall, _t3708);
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
    Bool _t3955 = check(p, TokenType_ColonEq());
    (void)_t3955;
    if (_t3955) {
        Token *_t3755 = advance(p);
        (void)_t3755;
        Bool _t3756 = Bool_clone(&(Bool){is_mut});
        (void)_t3756;
        Bool _t3757 = 0;
        (void)_t3757;
        Bool _t3758 = 0;
        (void)_t3758;
        Bool _t3759 = Bool_clone(&(Bool){is_own});
        (void)_t3759;
        I32 _t3760 = 0;
        (void)_t3760;
        I32 _t3761 = 0;
        (void)_t3761;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3756;
        dd->is_namespace = _t3757;
        dd->is_ref = _t3758;
        dd->is_own = _t3759;
        dd->field_offset = _t3760;
        dd->field_size = _t3761;
        dd->field_struct_def = NULL;
        dd->fn_sig = NULL;
        (void)dd;
        ;
        ;
        ;
        ;
        ;
        ;
        ExprData *_t3762 = ExprData_Decl(dd);
        (void)_t3762;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3762, t_line, t_col, &p->path);
        (void)decl;
        ExprData_delete(_t3762, &(Bool){1});
        Expr *_t3763 = parse_expression(p);
        (void)_t3763;
        Expr_add_child(decl, _t3763);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return decl;
    }
    ;
    Bool _t3956 = check(p, TokenType_Colon());
    (void)_t3956;
    if (_t3956) {
        Token *_t3887 = advance(p);
        (void)_t3887;
        Bool _t3888 = check(p, TokenType_KwFunc());
        (void)_t3888;
        Bool _t3889 = check(p, TokenType_KwProc());
        (void)_t3889;
        Bool _t3890 = Bool_or(_t3888, _t3889);
        (void)_t3890;
        ;
        ;
        if (_t3890) {
            Expr *sig = parse_func_def(p);
            (void)sig;
            Token *_t3781 = expect_token(p, TokenType_Eq());
            (void)_t3781;
            Token *_t3782 = expect_token(p, TokenType_LParen());
            (void)_t3782;
            Bool _t3783; { Bool *_hp = (Bool *)ExprData_is_FuncDef(&sig->data); _t3783 = *_hp; free(_hp); }
            (void)_t3783;
            if (_t3783) {
                FunctionDef *sfd = ExprData_get_FuncDef(&sig->data);
                (void)sfd;
                Str *_t3778 = Str_lit("Str", 3ULL);
                (void)_t3778;
                U64 _t3779; { U64 *_hp = (U64 *)Str_size(); _t3779 = *_hp; free(_hp); }
                (void)_t3779;
                Vec *new_names = Vec_new(_t3778, &(U64){_t3779});
                (void)new_names;
                Str_delete(_t3778, &(Bool){1});
                ;
                {
                    U64 _fi3764 = 0;
                    (void)_fi3764;
                    while (1) {
                        U64 _t3767 = 0;
                        (void)_t3767;
                        U64 _t3768; { U64 *_hp = (U64 *)Vec_len(&sfd->param_names); _t3768 = *_hp; free(_hp); }
                        (void)_t3768;
                        Range *_t3769 = Range_new(_t3767, _t3768);
                        (void)_t3769;
                        ;
                        ;
                        U64 _t3770; { U64 *_hp = (U64 *)Range_len(_t3769); _t3770 = *_hp; free(_hp); }
                        (void)_t3770;
                        Range_delete(_t3769, &(Bool){1});
                        Bool _wcond3765; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3764}, &(U64){_t3770}); _wcond3765 = *_hp; free(_hp); }
                        (void)_wcond3765;
                        ;
                        if (_wcond3765) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 _t3771 = 0;
                        (void)_t3771;
                        U64 _t3772; { U64 *_hp = (U64 *)Vec_len(&sfd->param_names); _t3772 = *_hp; free(_hp); }
                        (void)_t3772;
                        Range *_t3773 = Range_new(_t3771, _t3772);
                        (void)_t3773;
                        ;
                        ;
                        U64 pi; { U64 *_hp = (U64 *)Range_get(_t3773, _fi3764); pi = *_hp; free(_hp); }
                        (void)pi;
                        Range_delete(_t3773, &(Bool){1});
                        U64 _t3774 = 1;
                        (void)_t3774;
                        U64 _t3775 = U64_add(_fi3764, _t3774);
                        (void)_t3775;
                        ;
                        _fi3764 = _t3775;
                        ;
                        U64 _t3776 = 0;
                        (void)_t3776;
                        Bool _t3777; { Bool *_hp = (Bool *)U64_gt(&(U64){pi}, &(U64){_t3776}); _t3777 = *_hp; free(_hp); }
                        (void)_t3777;
                        ;
                        ;
                        if (_t3777) {
                            Token *_t3766 = expect_token(p, TokenType_Comma());
                            (void)_t3766;
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
            Bool _t3784 = check(p, TokenType_Comma());
            (void)_t3784;
            if (_t3784) {
                Token *_t3780 = advance(p);
                (void)_t3780;
            }
            ;
            Token *_t3785 = expect_token(p, TokenType_RParen());
            (void)_t3785;
            Token *_t3786 = expect_token(p, TokenType_LBrace());
            (void)_t3786;
            Expr *_t3787 = parse_block(p);
            (void)_t3787;
            Expr_add_child(sig, _t3787);
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
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
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
            ExprData *_t3794 = ExprData_Decl(dd);
            (void)_t3794;
            Declaration_delete(dd, &(Bool){1});
            Expr *decl = Expr_new(_t3794, t_line, t_col, &p->path);
            (void)decl;
            ExprData_delete(_t3794, &(Bool){1});
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
        I64 _t3891 = 0;
        (void)_t3891;
        I64 _t3892 = 1;
        (void)_t3892;
        I64 fn_sig_idx = I64_sub(_t3891, _t3892);
        (void)fn_sig_idx;
        ;
        ;
        Str *_t3893 = Str_lit("Fn", 2ULL);
        (void)_t3893;
        Bool _t3894; { Bool *_hp = (Bool *)Str_eq(type_name, _t3893); _t3894 = *_hp; free(_hp); }
        (void)_t3894;
        Str_delete(_t3893, &(Bool){1});
        if (_t3894) {
            Expr *sig = parse_fn_signature(p, t_line, t_col);
            (void)sig;
            U32 _t3796 = 0;
            (void)_t3796;
            Bool _t3797; { Bool *_hp = (Bool *)U32_neq(&sig->line, &(U32){_t3796}); _t3797 = *_hp; free(_hp); }
            (void)_t3797;
            ;
            Expr_delete(sig, &(Bool){1});
            if (_t3797) {
                I64 _t3795 = 0;
                (void)_t3795;
                fn_sig_idx = _t3795;
                ;
            }
            ;
        }
        ;
        ;
        Token *_t3895 = expect_token(p, TokenType_Eq());
        (void)_t3895;
        Bool _t3896 = check(p, TokenType_LParen());
        (void)_t3896;
        if (_t3896) {
            U64 saved = p->pos;
            (void)saved;
            Token *_t3883 = advance(p);
            (void)_t3883;
            Bool is_fsf = 1;
            (void)is_fsf;
            while (1) {
                Bool _t3801 = check(p, TokenType_RParen());
                (void)_t3801;
                Bool _t3802 = check(p, TokenType_Eof());
                (void)_t3802;
                Bool _t3803 = Bool_not(_t3801);
                (void)_t3803;
                ;
                Bool _t3804 = Bool_not(_t3802);
                (void)_t3804;
                ;
                Bool _wcond3798 = Bool_and(_t3803, _t3804);
                (void)_wcond3798;
                ;
                ;
                if (_wcond3798) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3805 = check(p, TokenType_Ident());
                (void)_t3805;
                Bool _t3806 = Bool_not(_t3805);
                (void)_t3806;
                ;
                if (_t3806) {
                    Bool _t3799 = 0;
                    (void)_t3799;
                    is_fsf = _t3799;
                    ;
                    ;
                    break;
                }
                ;
                Token *_t3807 = advance(p);
                (void)_t3807;
                Bool _t3808 = check(p, TokenType_Comma());
                (void)_t3808;
                if (_t3808) {
                    Token *_t3800 = advance(p);
                    (void)_t3800;
                }
                ;
            }
            Bool _t3884 = check(p, TokenType_RParen());
            (void)_t3884;
            Bool _t3885 = Bool_and(is_fsf, _t3884);
            (void)_t3885;
            ;
            if (_t3885) {
                Token *_t3810 = advance(p);
                (void)_t3810;
                Bool _t3811 = check(p, TokenType_LBrace());
                (void)_t3811;
                Bool _t3812 = Bool_not(_t3811);
                (void)_t3812;
                ;
                if (_t3812) {
                    Bool _t3809 = 0;
                    (void)_t3809;
                    is_fsf = _t3809;
                    ;
                }
                ;
            } else {
                Bool _t3813 = 0;
                (void)_t3813;
                is_fsf = _t3813;
                ;
            }
            ;
            U64 _t3886 = U64_clone(&(U64){saved});
            (void)_t3886;
            ;
            p->pos = _t3886;
            ;
            if (is_fsf) {
                Token *_t3837 = expect_token(p, TokenType_LParen());
                (void)_t3837;
                Str *_t3838 = Str_lit("Str", 3ULL);
                (void)_t3838;
                U64 _t3839; { U64 *_hp = (U64 *)Str_size(); _t3839 = *_hp; free(_hp); }
                (void)_t3839;
                Vec *pnames = Vec_new(_t3838, &(U64){_t3839});
                (void)pnames;
                Str_delete(_t3838, &(Bool){1});
                ;
                while (1) {
                    Bool _t3816 = check(p, TokenType_RParen());
                    (void)_t3816;
                    Bool _wcond3814 = Bool_not(_t3816);
                    (void)_wcond3814;
                    ;
                    if (_wcond3814) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *pn = expect_text(p, TokenType_Ident());
                    (void)pn;
                    Vec_push(pnames, pn);
                    Bool _t3817 = check(p, TokenType_Comma());
                    (void)_t3817;
                    if (_t3817) {
                        Token *_t3815 = advance(p);
                        (void)_t3815;
                    }
                    ;
                }
                Token *_t3840 = expect_token(p, TokenType_RParen());
                (void)_t3840;
                Token *_t3841 = expect_token(p, TokenType_LBrace());
                (void)_t3841;
                Expr *body = parse_block(p);
                (void)body;
                Str *_t3842 = Str_lit("Str", 3ULL);
                (void)_t3842;
                U64 _t3843; { U64 *_hp = (U64 *)Str_size(); _t3843 = *_hp; free(_hp); }
                (void)_t3843;
                Str *_t3844 = Str_lit("Str", 3ULL);
                (void)_t3844;
                U64 _t3845; { U64 *_hp = (U64 *)Str_size(); _t3845 = *_hp; free(_hp); }
                (void)_t3845;
                Str *_t3846 = Str_lit("Bool", 4ULL);
                (void)_t3846;
                U64 _t3847; { U64 *_hp = (U64 *)Bool_size(); _t3847 = *_hp; free(_hp); }
                (void)_t3847;
                Str *_t3848 = Str_lit("Bool", 4ULL);
                (void)_t3848;
                U64 _t3849; { U64 *_hp = (U64 *)Bool_size(); _t3849 = *_hp; free(_hp); }
                (void)_t3849;
                Str *_t3850 = Str_lit("Bool", 4ULL);
                (void)_t3850;
                U64 _t3851; { U64 *_hp = (U64 *)Bool_size(); _t3851 = *_hp; free(_hp); }
                (void)_t3851;
                Str *_t3852 = Str_lit("I64", 3ULL);
                (void)_t3852;
                U64 _t3853; { U64 *_hp = (U64 *)I64_size(); _t3853 = *_hp; free(_hp); }
                (void)_t3853;
                Str *_t3854 = Str_lit("I64", 3ULL);
                (void)_t3854;
                U64 _t3855; { U64 *_hp = (U64 *)I64_size(); _t3855 = *_hp; free(_hp); }
                (void)_t3855;
                I64 _t3856 = 0;
                (void)_t3856;
                I64 _t3857 = 1;
                (void)_t3857;
                I64 _t3858 = I64_sub(_t3856, _t3857);
                (void)_t3858;
                ;
                ;
                I64 _t3859 = 0;
                (void)_t3859;
                I64 _t3860 = 1;
                (void)_t3860;
                I64 _t3861 = I64_sub(_t3859, _t3860);
                (void)_t3861;
                ;
                ;
                U32 _t3862 = 0;
                (void)_t3862;
                I32 _t3863 = I64_to_i32(_t3858);
                (void)_t3863;
                ;
                I32 _t3864 = I64_to_i32(_t3861);
                (void)_t3864;
                ;
                Bool _t3865 = 0;
                (void)_t3865;
                Bool _t3866 = 0;
                (void)_t3866;
                FunctionDef *ffd = malloc(sizeof(FunctionDef));
                { FuncType *_ca = FuncType_clone(FuncType_Func()); ffd->func_type = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3842, &(U64){_t3843}); ffd->param_names = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3844, &(U64){_t3845}); ffd->param_types = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3846, &(U64){_t3847}); ffd->param_muts = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3848, &(U64){_t3849}); ffd->param_owns = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3850, &(U64){_t3851}); ffd->param_shallows = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3852, &(U64){_t3853}); ffd->param_fn_sigs = *_ca; free(_ca); }
                ffd->nparam = _t3862;
                { Vec *_ca = Vec_new(_t3854, &(U64){_t3855}); ffd->param_defaults = *_ca; free(_ca); }
                { Str *_ca = Str_clone(Str_lit("", 0ULL)); ffd->return_type = *_ca; free(_ca); }
                ffd->variadic_index = _t3863;
                ffd->kwargs_index = _t3864;
                ffd->return_is_ref = _t3865;
                ffd->return_is_shallow = _t3866;
                (void)ffd;
                Str_delete(_t3842, &(Bool){1});
                ;
                Str_delete(_t3844, &(Bool){1});
                ;
                Str_delete(_t3846, &(Bool){1});
                ;
                Str_delete(_t3848, &(Bool){1});
                ;
                Str_delete(_t3850, &(Bool){1});
                ;
                Str_delete(_t3852, &(Bool){1});
                ;
                Str_delete(_t3854, &(Bool){1});
                ;
                ;
                ;
                ;
                ;
                ;
                FuncType_delete(&ffd->func_type, &(Bool){0});
                { FuncType *_fa = FuncType_clone(FuncType_Func()); ffd->func_type = *_fa; free(_fa); }
                I64 _t3867 = 0;
                (void)_t3867;
                I64 _t3868 = 1;
                (void)_t3868;
                I64 _t3869 = I64_sub(_t3867, _t3868);
                (void)_t3869;
                ;
                ;
                I32 _t3870 = I64_to_i32(_t3869);
                (void)_t3870;
                ;
                ffd->variadic_index = _t3870;
                ;
                I64 _t3871 = 0;
                (void)_t3871;
                I64 _t3872 = 1;
                (void)_t3872;
                I64 _t3873 = I64_sub(_t3871, _t3872);
                (void)_t3873;
                ;
                ;
                I32 _t3874 = I64_to_i32(_t3873);
                (void)_t3874;
                ;
                ffd->kwargs_index = _t3874;
                ;
                U64 np; { U64 *_hp = (U64 *)Vec_len(pnames); np = *_hp; free(_hp); }
                (void)np;
                {
                    U64 _fi3818 = 0;
                    (void)_fi3818;
                    while (1) {
                        U64 _t3820 = 0;
                        (void)_t3820;
                        Range *_t3821 = Range_new(_t3820, np);
                        (void)_t3821;
                        ;
                        U64 _t3822; { U64 *_hp = (U64 *)Range_len(_t3821); _t3822 = *_hp; free(_hp); }
                        (void)_t3822;
                        Range_delete(_t3821, &(Bool){1});
                        Bool _wcond3819; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3818}, &(U64){_t3822}); _wcond3819 = *_hp; free(_hp); }
                        (void)_wcond3819;
                        ;
                        if (_wcond3819) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 _t3823 = 0;
                        (void)_t3823;
                        Range *_t3824 = Range_new(_t3823, np);
                        (void)_t3824;
                        ;
                        U64 _; { U64 *_hp = (U64 *)Range_get(_t3824, _fi3818); _ = *_hp; free(_hp); }
                        (void)_;
                        ;
                        Range_delete(_t3824, &(Bool){1});
                        U64 _t3825 = 1;
                        (void)_t3825;
                        U64 _t3826 = U64_add(_fi3818, _t3825);
                        (void)_t3826;
                        ;
                        _fi3818 = _t3826;
                        ;
                        Str *_t3827 = Str_lit("", 0ULL);
                        (void)_t3827;
                        Vec_push(&ffd->param_types, _t3827);
                        Bool _t3828 = 0;
                        (void)_t3828;
                        Vec_push(&ffd->param_muts, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3828; _oa; }));
                        Bool _t3829 = 0;
                        (void)_t3829;
                        Vec_push(&ffd->param_owns, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3829; _oa; }));
                        Bool _t3830 = 0;
                        (void)_t3830;
                        Vec_push(&ffd->param_shallows, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3830; _oa; }));
                        I64 _t3831 = 0;
                        (void)_t3831;
                        I64 _t3832 = 1;
                        (void)_t3832;
                        I64 _t3833 = I64_sub(_t3831, _t3832);
                        (void)_t3833;
                        ;
                        ;
                        Vec_push(&ffd->param_defaults, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = _t3833; _oa; }));
                        I64 _t3834 = 0;
                        (void)_t3834;
                        I64 _t3835 = 1;
                        (void)_t3835;
                        I64 _t3836 = I64_sub(_t3834, _t3835);
                        (void)_t3836;
                        ;
                        ;
                        Vec_push(&ffd->param_fn_sigs, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = _t3836; _oa; }));
                    }
                    ;
                }
                ;
                Vec_delete(&ffd->param_names, &(Bool){0});
                { Vec *_fa = Vec_clone(pnames); ffd->param_names = *_fa; free(_fa); }
                Vec_delete(pnames, &(Bool){1});
                ExprData *_t3875 = ExprData_FuncDef(ffd);
                (void)_t3875;
                FunctionDef_delete(ffd, &(Bool){1});
                Expr *fdef = Expr_new(_t3875, t_line, t_col, &p->path);
                (void)fdef;
                ExprData_delete(_t3875, &(Bool){1});
                Expr_add_child(fdef, body);
                Bool _t3876 = Bool_clone(&(Bool){is_mut});
                (void)_t3876;
                Bool _t3877 = 0;
                (void)_t3877;
                Bool _t3878 = 0;
                (void)_t3878;
                Bool _t3879 = Bool_clone(&(Bool){is_own});
                (void)_t3879;
                I32 _t3880 = 0;
                (void)_t3880;
                I32 _t3881 = 0;
                (void)_t3881;
                Declaration *dd = malloc(sizeof(Declaration));
                { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
                { Str *_ca = Str_clone(type_name); dd->explicit_type = *_ca; free(_ca); }
                dd->is_mut = _t3876;
                dd->is_namespace = _t3877;
                dd->is_ref = _t3878;
                dd->is_own = _t3879;
                dd->field_offset = _t3880;
                dd->field_size = _t3881;
                dd->field_struct_def = NULL;
                dd->fn_sig = NULL;
                (void)dd;
                ;
                ;
                ;
                ;
                ;
                ;
                ExprData *_t3882 = ExprData_Decl(dd);
                (void)_t3882;
                Declaration_delete(dd, &(Bool){1});
                Expr *decl = Expr_new(_t3882, t_line, t_col, &p->path);
                (void)decl;
                ExprData_delete(_t3882, &(Bool){1});
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
        Bool _t3897 = Bool_clone(&(Bool){is_mut});
        (void)_t3897;
        Bool _t3898 = 0;
        (void)_t3898;
        Bool _t3899 = 0;
        (void)_t3899;
        Bool _t3900 = Bool_clone(&(Bool){is_own});
        (void)_t3900;
        I32 _t3901 = 0;
        (void)_t3901;
        I32 _t3902 = 0;
        (void)_t3902;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(type_name); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3897;
        dd->is_namespace = _t3898;
        dd->is_ref = _t3899;
        dd->is_own = _t3900;
        dd->field_offset = _t3901;
        dd->field_size = _t3902;
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
        ExprData *_t3903 = ExprData_Decl(dd);
        (void)_t3903;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3903, t_line, t_col, &p->path);
        (void)decl;
        ExprData_delete(_t3903, &(Bool){1});
        Expr *_t3904 = parse_expression(p);
        (void)_t3904;
        Expr_add_child(decl, _t3904);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return decl;
    }
    ;
    Bool _t3957 = check(p, TokenType_Dot());
    (void)_t3957;
    if (_t3957) {
        Str *_t3943 = Str_clone(name);
        (void)_t3943;
        ExprData *_t3944 = ExprData_Ident(_t3943);
        (void)_t3944;
        Str_delete(_t3943, &(Bool){1});
        Expr *obj = Expr_new(_t3944, t_line, t_col, &p->path);
        (void)obj;
        ExprData_delete(_t3944, &(Bool){1});
        Str *last_field = Str_lit("", 0ULL);
        (void)last_field;
        U32 last_line = 0;
        (void)last_line;
        U32 last_col = 0;
        (void)last_col;
        while (1) {
            Bool _wcond3905 = check(p, TokenType_Dot());
            (void)_wcond3905;
            if (_wcond3905) {
            } else {
                ;
                break;
            }
            ;
            Token *_t3909 = advance(p);
            (void)_t3909;
            U32 _t3910 = peek_line(p);
            (void)_t3910;
            last_line = _t3910;
            ;
            U32 _t3911 = peek_col(p);
            (void)_t3911;
            last_col = _t3911;
            ;
            last_field = expect_text(p, TokenType_Ident());
            Bool _t3912 = check(p, TokenType_Dot());
            (void)_t3912;
            if (_t3912) {
                Str *_t3906 = Str_clone(last_field);
                (void)_t3906;
                ExprData *_t3907 = ExprData_FieldAccess(_t3906);
                (void)_t3907;
                Str_delete(_t3906, &(Bool){1});
                Expr *access = Expr_new(_t3907, last_line, last_col, &p->path);
                (void)access;
                ExprData_delete(_t3907, &(Bool){1});
                Expr *_t3908 = Expr_clone(obj);
                (void)_t3908;
                Expr_add_child(access, _t3908);
                obj = Expr_clone(access);
                Expr_delete(access, &(Bool){1});
            }
            ;
        }
        Bool _t3945 = check(p, TokenType_LParen());
        (void)_t3945;
        if (_t3945) {
            Token *_t3939 = advance(p);
            (void)_t3939;
            ExprData *_t3940 = ExprData_FieldAccess(last_field);
            (void)_t3940;
            Expr *callee = Expr_new(_t3940, last_line, last_col, &p->path);
            (void)callee;
            ExprData_delete(_t3940, &(Bool){1});
            Expr *_t3941 = Expr_clone(obj);
            (void)_t3941;
            Expr_add_child(callee, _t3941);
            Expr *mcall = Expr_new(ExprData_FCall(), last_line, last_col, &p->path);
            (void)mcall;
            Expr_add_child(mcall, callee);
            while (1) {
                Bool _t3931 = check(p, TokenType_RParen());
                (void)_t3931;
                Bool _t3932 = check(p, TokenType_Eof());
                (void)_t3932;
                Bool _t3933 = Bool_not(_t3931);
                (void)_t3933;
                ;
                Bool _t3934 = Bool_not(_t3932);
                (void)_t3934;
                ;
                Bool _wcond3913 = Bool_and(_t3933, _t3934);
                (void)_wcond3913;
                ;
                ;
                if (_wcond3913) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3935 = check(p, TokenType_Ident());
                (void)_t3935;
                if (_t3935) {
                    U64 _t3924 = 1;
                    (void)_t3924;
                    U64 _t3925 = U64_add(p->pos, _t3924);
                    (void)_t3925;
                    ;
                    U64 _t3926; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3926 = *_hp; free(_hp); }
                    (void)_t3926;
                    Bool _t3927; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3925}, &(U64){_t3926}); _t3927 = *_hp; free(_hp); }
                    (void)_t3927;
                    ;
                    ;
                    if (_t3927) {
                        U64 _t3919 = 1;
                        (void)_t3919;
                        U64 _t3920 = U64_add(p->pos, _t3919);
                        (void)_t3920;
                        ;
                        I64 _t3921 = U64_to_i64(_t3920);
                        (void)_t3921;
                        ;
                        U64 *_t3922 = malloc(sizeof(U64)); *_t3922 = I64_to_u64(_t3921);
                        (void)_t3922;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3922);
                        (void)nt;
                        Bool _t3923; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3923 = *_hp; free(_hp); }
                        (void)_t3923;
                        U64_delete(_t3922, &(Bool){1});
                        if (_t3923) {
                            U32 na_line = peek_line(p);
                            (void)na_line;
                            U32 na_col = peek_col(p);
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3915 = advance(p);
                            (void)_t3915;
                            ExprData *_t3916 = ExprData_NamedArg(aname);
                            (void)_t3916;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3916, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3916, &(Bool){1});
                            ;
                            ;
                            Expr *_t3917 = parse_expression(p);
                            (void)_t3917;
                            Expr_add_child(na, _t3917);
                            Expr_add_child(mcall, na);
                            Bool _t3918 = check(p, TokenType_Comma());
                            (void)_t3918;
                            if (_t3918) {
                                Token *_t3914 = advance(p);
                                (void)_t3914;
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
                Bool _t3936 = check(p, TokenType_KwOwn());
                (void)_t3936;
                if (_t3936) {
                    Token *_t3928 = advance(p);
                    (void)_t3928;
                    Bool _t3929 = 1;
                    (void)_t3929;
                    is_own_arg = _t3929;
                    ;
                }
                ;
                Expr *marg = parse_expression(p);
                (void)marg;
                Bool _t3937 = Bool_clone(&(Bool){is_own_arg});
                (void)_t3937;
                ;
                marg->is_own_arg = _t3937;
                ;
                Expr_add_child(mcall, marg);
                Bool _t3938 = check(p, TokenType_Comma());
                (void)_t3938;
                if (_t3938) {
                    Token *_t3930 = advance(p);
                    (void)_t3930;
                }
                ;
            }
            Token *_t3942 = expect_token(p, TokenType_RParen());
            (void)_t3942;
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
        Token *_t3946 = expect_token(p, TokenType_Eq());
        (void)_t3946;
        ExprData *_t3947 = ExprData_FieldAssign(last_field);
        (void)_t3947;
        Str_delete(last_field, &(Bool){1});
        Expr *fa = Expr_new(_t3947, t_line, t_col, &p->path);
        (void)fa;
        ExprData_delete(_t3947, &(Bool){1});
        Expr *_t3948 = Expr_clone(obj);
        (void)_t3948;
        Expr_delete(obj, &(Bool){1});
        Expr_add_child(fa, _t3948);
        Expr *_t3949 = parse_expression(p);
        (void)_t3949;
        Expr_add_child(fa, _t3949);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return fa;
    }
    ;
    Bool _t3958 = check(p, TokenType_Eq());
    (void)_t3958;
    if (_t3958) {
        Token *_t3950 = advance(p);
        (void)_t3950;
        Str *_t3951 = Str_clone(name);
        (void)_t3951;
        ExprData *_t3952 = ExprData_Assign(_t3951);
        (void)_t3952;
        Str_delete(_t3951, &(Bool){1});
        Expr *assign = Expr_new(_t3952, t_line, t_col, &p->path);
        (void)assign;
        ExprData_delete(_t3952, &(Bool){1});
        Expr *_t3953 = parse_expression(p);
        (void)_t3953;
        Expr_add_child(assign, _t3953);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return assign;
    }
    ;
    Bool _t3959 = check(p, TokenType_LParen());
    (void)_t3959;
    if (_t3959) {
        Expr *_t3954 = parse_call(p, name, t_line, t_col);
        (void)_t3954;
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return _t3954;
    }
    ;
    Str *_t3960 = Str_lit("Str", 3ULL);
    (void)_t3960;
    U64 _t3961; { U64 *_hp = (U64 *)Str_size(); _t3961 = *_hp; free(_hp); }
    (void)_t3961;
    U64 _t3962 = 8;
    (void)_t3962;
    Array *_va69 = Array_new(_t3960, &(U64){_t3961}, &(U64){_t3962});
    (void)_va69;
    Str_delete(_t3960, &(Bool){1});
    ;
    ;
    U64 _t3963 = 0;
    (void)_t3963;
    Str *_t3964 = Str_clone(&p->path);
    (void)_t3964;
    Array_set(_va69, &(U64){_t3963}, _t3964);
    ;
    U64 _t3965 = 1;
    (void)_t3965;
    Str *_t3966 = Str_lit(":", 1ULL);
    (void)_t3966;
    Array_set(_va69, &(U64){_t3965}, _t3966);
    ;
    U64 _t3967 = 2;
    (void)_t3967;
    Str *_t3968 = U32_to_str(&(U32){t_line});
    (void)_t3968;
    ;
    Array_set(_va69, &(U64){_t3967}, _t3968);
    ;
    U64 _t3969 = 3;
    (void)_t3969;
    Str *_t3970 = Str_lit(":", 1ULL);
    (void)_t3970;
    Array_set(_va69, &(U64){_t3969}, _t3970);
    ;
    U64 _t3971 = 4;
    (void)_t3971;
    Str *_t3972 = U32_to_str(&(U32){t_col});
    (void)_t3972;
    ;
    Array_set(_va69, &(U64){_t3971}, _t3972);
    ;
    U64 _t3973 = 5;
    (void)_t3973;
    Str *_t3974 = Str_lit(": expected ':=', ':', '=' or '(' after identifier '", 51ULL);
    (void)_t3974;
    Array_set(_va69, &(U64){_t3973}, _t3974);
    ;
    U64 _t3975 = 6;
    (void)_t3975;
    Str *_t3976 = Str_clone(name);
    (void)_t3976;
    Str_delete(name, &(Bool){1});
    Array_set(_va69, &(U64){_t3975}, _t3976);
    ;
    U64 _t3977 = 7;
    (void)_t3977;
    Str *_t3978 = Str_lit("'", 1ULL);
    (void)_t3978;
    Array_set(_va69, &(U64){_t3977}, _t3978);
    ;
    Str *_t3979 = Str_lit("src/self/parser.til:786:11", 26ULL);
    (void)_t3979;
    panic(_t3979, _va69);
    Str_delete(_t3979, &(Bool){1});
    U32 _t3980 = 0;
    (void)_t3980;
    U32 _t3981 = 0;
    (void)_t3981;
    Expr *_t3982 = Expr_new(ExprData_Body(), _t3980, _t3981, &p->path);
    (void)_t3982;
    ;
    ;
    return _t3982;
}

Expr * parse_statement(Parser * p) {
    (void)p;
    U32 t_line = peek_line(p);
    (void)t_line;
    U32 t_col = peek_col(p);
    (void)t_col;
    Token *t = peek(p);
    (void)t;
    Bool _t4120; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t4120 = *_hp; free(_hp); }
    (void)_t4120;
    if (_t4120) {
        Bool _t3983 = 0;
        (void)_t3983;
        Bool _t3984 = 0;
        (void)_t3984;
        Expr *_t3985 = parse_statement_ident(p, _t3983, _t3984);
        (void)_t3985;
        ;
        ;
        ;
        ;
        ;
        return _t3985;
    }
    ;
    Bool _t4121; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwRef()); _t4121 = *_hp; free(_hp); }
    (void)_t4121;
    if (_t4121) {
        Token *_t3992 = advance(p);
        (void)_t3992;
        Bool ref_mut = 0;
        (void)ref_mut;
        Bool _t3993 = check(p, TokenType_KwMut());
        (void)_t3993;
        if (_t3993) {
            Token *_t3986 = advance(p);
            (void)_t3986;
            Bool _t3987 = 1;
            (void)_t3987;
            ref_mut = _t3987;
            ;
        }
        ;
        U32 i_line = peek_line(p);
        (void)i_line;
        U32 i_col = peek_col(p);
        (void)i_col;
        Str *iname = expect_text(p, TokenType_Ident());
        (void)iname;
        Bool _t3994 = 0;
        (void)_t3994;
        Bool _t3995 = 0;
        (void)_t3995;
        Bool _t3996 = 1;
        (void)_t3996;
        Bool _t3997 = 0;
        (void)_t3997;
        I32 _t3998 = 0;
        (void)_t3998;
        I32 _t3999 = 0;
        (void)_t3999;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(iname); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3994;
        dd->is_namespace = _t3995;
        dd->is_ref = _t3996;
        dd->is_own = _t3997;
        dd->field_offset = _t3998;
        dd->field_size = _t3999;
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
            Bool _t3988 = 1;
            (void)_t3988;
            dd->is_mut = _t3988;
            ;
        }
        ;
        Bool _t4000 = check(p, TokenType_Colon());
        (void)_t4000;
        if (_t4000) {
            Token *_t3989 = advance(p);
            (void)_t3989;
            Str_delete(&dd->explicit_type, &(Bool){0});
            { Str *_fa = expect_text(p, TokenType_Ident()); dd->explicit_type = *_fa; free(_fa); }
            Token *_t3990 = expect_token(p, TokenType_Eq());
            (void)_t3990;
        } else {
            Token *_t3991 = expect_token(p, TokenType_ColonEq());
            (void)_t3991;
        }
        ;
        ExprData *_t4001 = ExprData_Decl(dd);
        (void)_t4001;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t4001, i_line, i_col, &p->path);
        (void)decl;
        ExprData_delete(_t4001, &(Bool){1});
        ;
        ;
        Expr *_t4002 = parse_expression(p);
        (void)_t4002;
        Expr_add_child(decl, _t4002);
        ;
        ;
        ;
        return decl;
    }
    ;
    Bool _t4122; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMut()); _t4122 = *_hp; free(_hp); }
    (void)_t4122;
    if (_t4122) {
        Token *_t4003 = advance(p);
        (void)_t4003;
        Bool _t4004 = 1;
        (void)_t4004;
        Bool _t4005 = 0;
        (void)_t4005;
        Expr *_t4006 = parse_statement_ident(p, _t4004, _t4005);
        (void)_t4006;
        ;
        ;
        ;
        ;
        ;
        return _t4006;
    }
    ;
    Bool _t4123; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwReturn()); _t4123 = *_hp; free(_hp); }
    (void)_t4123;
    if (_t4123) {
        Token *_t4008 = advance(p);
        (void)_t4008;
        Expr *ret = Expr_new(ExprData_Return(), t_line, t_col, &p->path);
        (void)ret;
        Bool _t4009 = check(p, TokenType_RBrace());
        (void)_t4009;
        Bool _t4010 = check(p, TokenType_Eof());
        (void)_t4010;
        Bool _t4011 = Bool_not(_t4009);
        (void)_t4011;
        ;
        Bool _t4012 = Bool_not(_t4010);
        (void)_t4012;
        ;
        Bool _t4013 = Bool_and(_t4011, _t4012);
        (void)_t4013;
        ;
        ;
        if (_t4013) {
            Expr *_t4007 = parse_expression(p);
            (void)_t4007;
            Expr_add_child(ret, _t4007);
        }
        ;
        ;
        ;
        ;
        return ret;
    }
    ;
    Bool _t4124; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwIf()); _t4124 = *_hp; free(_hp); }
    (void)_t4124;
    if (_t4124) {
        Token *_t4021 = advance(p);
        (void)_t4021;
        Expr *node = Expr_new(ExprData_If(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t4022 = parse_expression(p);
        (void)_t4022;
        Expr_add_child(node, _t4022);
        Token *_t4023 = expect_token(p, TokenType_LBrace());
        (void)_t4023;
        Expr *_t4024 = parse_block(p);
        (void)_t4024;
        Expr_add_child(node, _t4024);
        Bool _t4025 = check(p, TokenType_KwElse());
        (void)_t4025;
        if (_t4025) {
            Token *_t4019 = advance(p);
            (void)_t4019;
            Bool _t4020 = check(p, TokenType_KwIf());
            (void)_t4020;
            if (_t4020) {
                U32 _t4014 = peek_line(p);
                (void)_t4014;
                U32 _t4015 = peek_col(p);
                (void)_t4015;
                Expr *else_body = Expr_new(ExprData_Body(), _t4014, _t4015, &p->path);
                (void)else_body;
                ;
                ;
                Expr *_t4016 = parse_statement(p);
                (void)_t4016;
                Expr_add_child(else_body, _t4016);
                Expr_add_child(node, else_body);
            } else {
                Token *_t4017 = expect_token(p, TokenType_LBrace());
                (void)_t4017;
                Expr *_t4018 = parse_block(p);
                (void)_t4018;
                Expr_add_child(node, _t4018);
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
    Bool _t4125; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t4125 = *_hp; free(_hp); }
    (void)_t4125;
    Bool _t4126; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t4126 = *_hp; free(_hp); }
    (void)_t4126;
    Bool _t4127 = Bool_or(_t4125, _t4126);
    (void)_t4127;
    ;
    ;
    Bool _t4128; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t4128 = *_hp; free(_hp); }
    (void)_t4128;
    Bool _t4129 = Bool_or(_t4127, _t4128);
    (void)_t4129;
    ;
    ;
    Bool _t4130; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t4130 = *_hp; free(_hp); }
    (void)_t4130;
    Bool _t4131 = Bool_or(_t4129, _t4130);
    (void)_t4131;
    ;
    ;
    Bool _t4132; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwNull()); _t4132 = *_hp; free(_hp); }
    (void)_t4132;
    Bool _t4133 = Bool_or(_t4131, _t4132);
    (void)_t4133;
    ;
    ;
    if (_t4133) {
        Expr *_t4026 = parse_expression(p);
        (void)_t4026;
        ;
        ;
        ;
        return _t4026;
    }
    ;
    Bool _t4134; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t4134 = *_hp; free(_hp); }
    (void)_t4134;
    if (_t4134) {
        Token *_t4027 = advance(p);
        (void)_t4027;
        Expr *_t4028 = parse_block(p);
        (void)_t4028;
        ;
        ;
        ;
        return _t4028;
    }
    ;
    Bool _t4135; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwWhile()); _t4135 = *_hp; free(_hp); }
    (void)_t4135;
    if (_t4135) {
        Token *_t4029 = advance(p);
        (void)_t4029;
        Expr *node = Expr_new(ExprData_While(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t4030 = parse_expression(p);
        (void)_t4030;
        Expr_add_child(node, _t4030);
        Token *_t4031 = expect_token(p, TokenType_LBrace());
        (void)_t4031;
        Expr *_t4032 = parse_block(p);
        (void)_t4032;
        Expr_add_child(node, _t4032);
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4136; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFor()); _t4136 = *_hp; free(_hp); }
    (void)_t4136;
    if (_t4136) {
        Token *_t4034 = advance(p);
        (void)_t4034;
        U32 i_line = peek_line(p);
        (void)i_line;
        U32 i_col = peek_col(p);
        (void)i_col;
        Str *iname = expect_text(p, TokenType_Ident());
        (void)iname;
        ExprData *_t4035 = ExprData_ForIn(iname);
        (void)_t4035;
        Str_delete(iname, &(Bool){1});
        Expr *node = Expr_new(_t4035, i_line, i_col, &p->path);
        (void)node;
        ExprData_delete(_t4035, &(Bool){1});
        ;
        ;
        Bool _t4036 = check(p, TokenType_Colon());
        (void)_t4036;
        if (_t4036) {
            Token *_t4033 = advance(p);
            (void)_t4033;
            Str_delete(&node->struct_name, &(Bool){0});
            { Str *_fa = expect_text(p, TokenType_Ident()); node->struct_name = *_fa; free(_fa); }
        }
        ;
        Token *_t4037 = expect_token(p, TokenType_KwIn());
        (void)_t4037;
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
    Bool _t4137; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwSwitch()); _t4137 = *_hp; free(_hp); }
    (void)_t4137;
    if (_t4137) {
        Token *_t4064 = advance(p);
        (void)_t4064;
        Expr *node = Expr_new(ExprData_Switch(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t4065 = parse_expression(p);
        (void)_t4065;
        Expr_add_child(node, _t4065);
        Token *_t4066 = expect_token(p, TokenType_LBrace());
        (void)_t4066;
        while (1) {
            Bool _t4052 = check(p, TokenType_RBrace());
            (void)_t4052;
            Bool _t4053 = check(p, TokenType_Eof());
            (void)_t4053;
            Bool _t4054 = Bool_not(_t4052);
            (void)_t4054;
            ;
            Bool _t4055 = Bool_not(_t4053);
            (void)_t4055;
            ;
            Bool _wcond4041 = Bool_and(_t4054, _t4055);
            (void)_wcond4041;
            ;
            ;
            if (_wcond4041) {
            } else {
                ;
                break;
            }
            ;
            Token *_t4056 = expect_token(p, TokenType_KwCase());
            (void)_t4056;
            U32 _t4057 = peek_line(p);
            (void)_t4057;
            U32 _t4058 = peek_col(p);
            (void)_t4058;
            Expr *cn = Expr_new(ExprData_Case(), _t4057, _t4058, &p->path);
            (void)cn;
            ;
            ;
            Bool _t4059 = check(p, TokenType_Colon());
            (void)_t4059;
            Bool _t4060 = Bool_not(_t4059);
            (void)_t4060;
            ;
            if (_t4060) {
                Expr *_t4042 = parse_expression(p);
                (void)_t4042;
                Expr_add_child(cn, _t4042);
            }
            ;
            Token *_t4061 = expect_token(p, TokenType_Colon());
            (void)_t4061;
            U32 _t4062 = peek_line(p);
            (void)_t4062;
            U32 _t4063 = peek_col(p);
            (void)_t4063;
            Expr *cb = Expr_new(ExprData_Body(), _t4062, _t4063, &p->path);
            (void)cb;
            ;
            ;
            while (1) {
                Bool _t4044 = check(p, TokenType_KwCase());
                (void)_t4044;
                Bool _t4045 = check(p, TokenType_RBrace());
                (void)_t4045;
                Bool _t4046 = Bool_not(_t4044);
                (void)_t4046;
                ;
                Bool _t4047 = Bool_not(_t4045);
                (void)_t4047;
                ;
                Bool _t4048 = check(p, TokenType_Eof());
                (void)_t4048;
                Bool _t4049 = Bool_and(_t4046, _t4047);
                (void)_t4049;
                ;
                ;
                Bool _t4050 = Bool_not(_t4048);
                (void)_t4050;
                ;
                Bool _wcond4043 = Bool_and(_t4049, _t4050);
                (void)_wcond4043;
                ;
                ;
                if (_wcond4043) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t4051 = parse_statement(p);
                (void)_t4051;
                Expr_add_child(cb, _t4051);
            }
            Expr_add_child(cn, cb);
            Expr_add_child(node, cn);
        }
        Token *_t4067 = expect_token(p, TokenType_RBrace());
        (void)_t4067;
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4138; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwOwn()); _t4138 = *_hp; free(_hp); }
    (void)_t4138;
    if (_t4138) {
        Token *_t4109 = advance(p);
        (void)_t4109;
        Bool _t4110 = check(p, TokenType_Ident());
        (void)_t4110;
        Bool _t4111 = check(p, TokenType_KwMut());
        (void)_t4111;
        Bool _t4112 = Bool_or(_t4110, _t4111);
        (void)_t4112;
        ;
        ;
        if (_t4112) {
            Bool own_mut = 0;
            (void)own_mut;
            Bool _t4099 = check(p, TokenType_KwMut());
            (void)_t4099;
            if (_t4099) {
                Token *_t4068 = advance(p);
                (void)_t4068;
                Bool _t4069 = 1;
                (void)_t4069;
                own_mut = _t4069;
                ;
            }
            ;
            Bool _t4100 = check(p, TokenType_Ident());
            (void)_t4100;
            if (_t4100) {
                U64 _t4079 = 1;
                (void)_t4079;
                U64 _t4080 = U64_add(p->pos, _t4079);
                (void)_t4080;
                ;
                U64 _t4081; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t4081 = *_hp; free(_hp); }
                (void)_t4081;
                Bool _t4082; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4080}, &(U64){_t4081}); _t4082 = *_hp; free(_hp); }
                (void)_t4082;
                ;
                ;
                if (_t4082) {
                    U64 _t4072 = 1;
                    (void)_t4072;
                    U64 _t4073 = U64_add(p->pos, _t4072);
                    (void)_t4073;
                    ;
                    I64 _t4074 = U64_to_i64(_t4073);
                    (void)_t4074;
                    ;
                    U64 *_t4075 = malloc(sizeof(U64)); *_t4075 = I64_to_u64(_t4074);
                    (void)_t4075;
                    ;
                    Token *nt = Vec_get(&p->tokens, _t4075);
                    (void)nt;
                    Bool _t4076; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_ColonEq()); _t4076 = *_hp; free(_hp); }
                    (void)_t4076;
                    Bool _t4077; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Colon()); _t4077 = *_hp; free(_hp); }
                    (void)_t4077;
                    U64_delete(_t4075, &(Bool){1});
                    Bool _t4078 = Bool_or(_t4076, _t4077);
                    (void)_t4078;
                    ;
                    ;
                    if (_t4078) {
                        Bool _t4070 = 1;
                        (void)_t4070;
                        Expr *_t4071 = parse_statement_ident(p, own_mut, _t4070);
                        (void)_t4071;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        return _t4071;
                    }
                    ;
                }
                ;
            }
            ;
            if (own_mut) {
                Str *_t4083 = Str_lit("Str", 3ULL);
                (void)_t4083;
                U64 _t4084; { U64 *_hp = (U64 *)Str_size(); _t4084 = *_hp; free(_hp); }
                (void)_t4084;
                U64 _t4085 = 6;
                (void)_t4085;
                Array *_va70 = Array_new(_t4083, &(U64){_t4084}, &(U64){_t4085});
                (void)_va70;
                Str_delete(_t4083, &(Bool){1});
                ;
                ;
                U64 _t4086 = 0;
                (void)_t4086;
                Str *_t4087 = Str_clone(&p->path);
                (void)_t4087;
                Array_set(_va70, &(U64){_t4086}, _t4087);
                ;
                U64 _t4088 = 1;
                (void)_t4088;
                Str *_t4089 = Str_lit(":", 1ULL);
                (void)_t4089;
                Array_set(_va70, &(U64){_t4088}, _t4089);
                ;
                U64 _t4090 = 2;
                (void)_t4090;
                Str *_t4091 = U32_to_str(&(U32){t_line});
                (void)_t4091;
                Array_set(_va70, &(U64){_t4090}, _t4091);
                ;
                U64 _t4092 = 3;
                (void)_t4092;
                Str *_t4093 = Str_lit(":", 1ULL);
                (void)_t4093;
                Array_set(_va70, &(U64){_t4092}, _t4093);
                ;
                U64 _t4094 = 4;
                (void)_t4094;
                Str *_t4095 = U32_to_str(&(U32){t_col});
                (void)_t4095;
                Array_set(_va70, &(U64){_t4094}, _t4095);
                ;
                U64 _t4096 = 5;
                (void)_t4096;
                Str *_t4097 = Str_lit(": expected identifier after 'own mut'", 37ULL);
                (void)_t4097;
                Array_set(_va70, &(U64){_t4096}, _t4097);
                ;
                Str *_t4098 = Str_lit("src/self/parser.til:920:23", 26ULL);
                (void)_t4098;
                panic(_t4098, _va70);
                Str_delete(_t4098, &(Bool){1});
            }
            ;
        }
        ;
        Expr *expr = parse_expression(p);
        (void)expr;
        I64 _t4113 = 0;
        (void)_t4113;
        I64 _t4114 = 1;
        (void)_t4114;
        I64 primary_idx = I64_sub(_t4113, _t4114);
        (void)primary_idx;
        ;
        ;
        ;
        Expr *cur = Expr_clone(expr);
        (void)cur;
        while (1) {
            U64 _t4102; { U64 *_hp = (U64 *)Vec_len(&cur->children); _t4102 = *_hp; free(_hp); }
            (void)_t4102;
            U64 _t4103 = 0;
            (void)_t4103;
            Bool _t4104; { Bool *_hp = (Bool *)ExprData_is_FCall(&cur->data); _t4104 = *_hp; free(_hp); }
            (void)_t4104;
            Bool _t4105; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(&cur->data); _t4105 = *_hp; free(_hp); }
            (void)_t4105;
            Bool _t4106; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4102}, &(U64){_t4103}); _t4106 = *_hp; free(_hp); }
            (void)_t4106;
            ;
            ;
            Bool _t4107 = Bool_or(_t4104, _t4105);
            (void)_t4107;
            ;
            ;
            Bool _wcond4101 = Bool_and(_t4106, _t4107);
            (void)_wcond4101;
            ;
            ;
            if (_wcond4101) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t4108 = malloc(sizeof(U64));
            *_t4108 = 0;
            (void)_t4108;
            Expr *ch = Vec_get(&cur->children, _t4108);
            (void)ch;
            cur = Expr_clone(ch);
            U64_delete(_t4108, &(Bool){1});
        }
        Bool _t4115 = 1;
        (void)_t4115;
        cur->is_own_arg = _t4115;
        ;
        Expr_delete(cur, &(Bool){1});
        ;
        ;
        ;
        ;
        return expr;
    }
    ;
    Bool _t4139; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwBreak()); _t4139 = *_hp; free(_hp); }
    (void)_t4139;
    if (_t4139) {
        Token *_t4116 = advance(p);
        (void)_t4116;
        Expr *_t4117 = Expr_new(ExprData_Break(), t_line, t_col, &p->path);
        (void)_t4117;
        ;
        ;
        ;
        return _t4117;
    }
    ;
    Bool _t4140; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwContinue()); _t4140 = *_hp; free(_hp); }
    (void)_t4140;
    if (_t4140) {
        Token *_t4118 = advance(p);
        (void)_t4118;
        Expr *_t4119 = Expr_new(ExprData_Continue(), t_line, t_col, &p->path);
        (void)_t4119;
        ;
        ;
        ;
        return _t4119;
    }
    ;
    Str *_t4141 = Str_lit("Str", 3ULL);
    (void)_t4141;
    U64 _t4142; { U64 *_hp = (U64 *)Str_size(); _t4142 = *_hp; free(_hp); }
    (void)_t4142;
    U64 _t4143 = 8;
    (void)_t4143;
    Array *_va71 = Array_new(_t4141, &(U64){_t4142}, &(U64){_t4143});
    (void)_va71;
    Str_delete(_t4141, &(Bool){1});
    ;
    ;
    U64 _t4144 = 0;
    (void)_t4144;
    Str *_t4145 = Str_clone(&p->path);
    (void)_t4145;
    Array_set(_va71, &(U64){_t4144}, _t4145);
    ;
    U64 _t4146 = 1;
    (void)_t4146;
    Str *_t4147 = Str_lit(":", 1ULL);
    (void)_t4147;
    Array_set(_va71, &(U64){_t4146}, _t4147);
    ;
    U64 _t4148 = 2;
    (void)_t4148;
    Str *_t4149 = U32_to_str(&(U32){t_line});
    (void)_t4149;
    ;
    Array_set(_va71, &(U64){_t4148}, _t4149);
    ;
    U64 _t4150 = 3;
    (void)_t4150;
    Str *_t4151 = Str_lit(":", 1ULL);
    (void)_t4151;
    Array_set(_va71, &(U64){_t4150}, _t4151);
    ;
    U64 _t4152 = 4;
    (void)_t4152;
    Str *_t4153 = U32_to_str(&(U32){t_col});
    (void)_t4153;
    ;
    Array_set(_va71, &(U64){_t4152}, _t4153);
    ;
    U64 _t4154 = 5;
    (void)_t4154;
    Str *_t4155 = Str_lit(": expected statement, found '", 29ULL);
    (void)_t4155;
    Array_set(_va71, &(U64){_t4154}, _t4155);
    ;
    U64 _t4156 = 6;
    (void)_t4156;
    Str *_t4157 = Str_clone(&t->text);
    (void)_t4157;
    Array_set(_va71, &(U64){_t4156}, _t4157);
    ;
    U64 _t4158 = 7;
    (void)_t4158;
    Str *_t4159 = Str_lit("'", 1ULL);
    (void)_t4159;
    Array_set(_va71, &(U64){_t4158}, _t4159);
    ;
    Str *_t4160 = Str_lit("src/self/parser.til:947:11", 26ULL);
    (void)_t4160;
    panic(_t4160, _va71);
    Str_delete(_t4160, &(Bool){1});
    U32 _t4161 = 0;
    (void)_t4161;
    U32 _t4162 = 0;
    (void)_t4162;
    Expr *_t4163 = Expr_new(ExprData_Body(), _t4161, _t4162, &p->path);
    (void)_t4163;
    ;
    ;
    return _t4163;
}

Expr * parse(Vec * tokens, Str * path, Str * mode_out) {
    (void)tokens;
    (void)path;
    (void)mode_out;
    I64 _t4175 = 0;
    (void)_t4175;
    Parser *p = malloc(sizeof(Parser));
    { Vec *_ca = Vec_clone(tokens); p->tokens = *_ca; free(_ca); }
    p->pos = _t4175;
    { Str *_ca = Str_clone(path); p->path = *_ca; free(_ca); }
    (void)p;
    ;
    Bool _t4176 = check(p, TokenType_KwMode());
    (void)_t4176;
    if (_t4176) {
        Token *_t4168 = advance(p);
        (void)_t4168;
        Bool _t4169 = check(p, TokenType_Ident());
        (void)_t4169;
        Bool _t4170 = check(p, TokenType_KwTest());
        (void)_t4170;
        Bool _t4171 = Bool_or(_t4169, _t4170);
        (void)_t4171;
        ;
        ;
        if (_t4171) {
            Str *_t4164 = Str_clone(&peek(p)->text);
            (void)_t4164;
            U64 _t4165; { U64 *_hp = (U64 *)Str_size(); _t4165 = *_hp; free(_hp); }
            (void)_t4165;
            swap(mode_out, _t4164, _t4165);
            Str_delete(_t4164, &(Bool){1});
            ;
            Token *_t4166 = advance(p);
            (void)_t4166;
        } else {
            Token *_t4167 = expect_token(p, TokenType_Ident());
            (void)_t4167;
        }
        ;
    }
    ;
    U32 _t4177 = 1;
    (void)_t4177;
    U32 _t4178 = 1;
    (void)_t4178;
    Expr *root = Expr_new(ExprData_Body(), _t4177, _t4178, &p->path);
    (void)root;
    ;
    ;
    while (1) {
        Bool _t4173 = check(p, TokenType_Eof());
        (void)_t4173;
        Bool _wcond4172 = Bool_not(_t4173);
        (void)_wcond4172;
        ;
        if (_wcond4172) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t4174 = parse_statement(p);
        (void)_t4174;
        Expr_add_child(root, _t4174);
    }
    Parser_delete(p, &(Bool){1});
    return root;
}

