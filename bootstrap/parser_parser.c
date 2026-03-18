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
        Str *_t3080 = Str_lit("src/self/parser.til:33:15", 25ULL);
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
        Str *_t3107 = Str_lit("src/self/parser.til:43:15", 25ULL);
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
    Bool _t3143 = check(p, TokenType_LParen());
    (void)_t3143;
    Bool _t3144 = Bool_not(_t3143);
    (void)_t3144;
    ;
    if (_t3144) {
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
    Token *_t3145 = advance(p);
    (void)_t3145;
    Str *_t3146 = Str_lit("Str", 3ULL);
    (void)_t3146;
    U64 _t3147; { U64 *_hp = (U64 *)Str_size(); _t3147 = *_hp; free(_hp); }
    (void)_t3147;
    Vec *ptypes = Vec_new(_t3146, &(U64){_t3147});
    (void)ptypes;
    Str_delete(_t3146, &(Bool){1});
    ;
    Str *_t3148 = Str_lit("Bool", 4ULL);
    (void)_t3148;
    U64 _t3149; { U64 *_hp = (U64 *)Bool_size(); _t3149 = *_hp; free(_hp); }
    (void)_t3149;
    Vec *pmuts = Vec_new(_t3148, &(U64){_t3149});
    (void)pmuts;
    Str_delete(_t3148, &(Bool){1});
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
    Token *_t3150 = expect_token(p, TokenType_RParen());
    (void)_t3150;
    Str *return_type = Str_lit("", 0ULL);
    (void)return_type;
    Bool _t3151 = check(p, TokenType_KwReturns());
    (void)_t3151;
    if (_t3151) {
        Token *_t3125 = advance(p);
        (void)_t3125;
        return_type = expect_text(p, TokenType_Ident());
    }
    ;
    Str *_t3152 = Str_lit("Str", 3ULL);
    (void)_t3152;
    U64 _t3153; { U64 *_hp = (U64 *)Str_size(); _t3153 = *_hp; free(_hp); }
    (void)_t3153;
    Str *_t3154 = Str_lit("Str", 3ULL);
    (void)_t3154;
    U64 _t3155; { U64 *_hp = (U64 *)Str_size(); _t3155 = *_hp; free(_hp); }
    (void)_t3155;
    Str *_t3156 = Str_lit("Bool", 4ULL);
    (void)_t3156;
    U64 _t3157; { U64 *_hp = (U64 *)Bool_size(); _t3157 = *_hp; free(_hp); }
    (void)_t3157;
    Str *_t3158 = Str_lit("Bool", 4ULL);
    (void)_t3158;
    U64 _t3159; { U64 *_hp = (U64 *)Bool_size(); _t3159 = *_hp; free(_hp); }
    (void)_t3159;
    Str *_t3160 = Str_lit("Bool", 4ULL);
    (void)_t3160;
    U64 _t3161; { U64 *_hp = (U64 *)Bool_size(); _t3161 = *_hp; free(_hp); }
    (void)_t3161;
    Str *_t3162 = Str_lit("I64", 3ULL);
    (void)_t3162;
    U64 _t3163; { U64 *_hp = (U64 *)I64_size(); _t3163 = *_hp; free(_hp); }
    (void)_t3163;
    Str *_t3164 = Str_lit("Str", 3ULL);
    (void)_t3164;
    U64 _t3165; { U64 *_hp = (U64 *)Str_size(); _t3165 = *_hp; free(_hp); }
    (void)_t3165;
    Str *_t3166 = Str_lit("Expr", 4ULL);
    (void)_t3166;
    U64 _t3167; { U64 *_hp = (U64 *)Expr_size(); _t3167 = *_hp; free(_hp); }
    (void)_t3167;
    I64 _t3168 = 0;
    (void)_t3168;
    I64 _t3169 = 1;
    (void)_t3169;
    I64 _t3170 = I64_sub(_t3168, _t3169);
    (void)_t3170;
    ;
    ;
    I64 _t3171 = 0;
    (void)_t3171;
    I64 _t3172 = 1;
    (void)_t3172;
    I64 _t3173 = I64_sub(_t3171, _t3172);
    (void)_t3173;
    ;
    ;
    U32 _t3174 = 0;
    (void)_t3174;
    I32 _t3175 = I64_to_i32(_t3170);
    (void)_t3175;
    ;
    I32 _t3176 = I64_to_i32(_t3173);
    (void)_t3176;
    ;
    Bool _t3177 = 0;
    (void)_t3177;
    Bool _t3178 = 0;
    (void)_t3178;
    FunctionDef *fd = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(FuncType_Func()); fd->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3152, &(U64){_t3153}); fd->param_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3154, &(U64){_t3155}); fd->param_types = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3156, &(U64){_t3157}); fd->param_muts = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3158, &(U64){_t3159}); fd->param_owns = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3160, &(U64){_t3161}); fd->param_shallows = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3162, &(U64){_t3163}); fd->param_fn_sigs = *_ca; free(_ca); }
    fd->nparam = _t3174;
    { Map *_ca = Map_new(_t3164, &(U64){_t3165}, _t3166, &(U64){_t3167}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3175;
    fd->kwargs_index = _t3176;
    fd->return_is_ref = _t3177;
    fd->return_is_shallow = _t3178;
    (void)fd;
    Str_delete(_t3152, &(Bool){1});
    ;
    Str_delete(_t3154, &(Bool){1});
    ;
    Str_delete(_t3156, &(Bool){1});
    ;
    Str_delete(_t3158, &(Bool){1});
    ;
    Str_delete(_t3160, &(Bool){1});
    ;
    Str_delete(_t3162, &(Bool){1});
    ;
    Str_delete(_t3164, &(Bool){1});
    ;
    Str_delete(_t3166, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    U64 _t3179; { U64 *_hp = (U64 *)Str_len(return_type); _t3179 = *_hp; free(_hp); }
    (void)_t3179;
    U64 _t3180 = 0;
    (void)_t3180;
    Bool _t3181; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3179}, &(U64){_t3180}); _t3181 = *_hp; free(_hp); }
    (void)_t3181;
    ;
    ;
    if (_t3181) {
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
    Bool _t3182 = 0;
    (void)_t3182;
    fd->return_is_ref = _t3182;
    ;
    Bool _t3183 = 0;
    (void)_t3183;
    fd->return_is_shallow = _t3183;
    ;
    I64 _t3184 = 0;
    (void)_t3184;
    I64 _t3185 = 1;
    (void)_t3185;
    I64 _t3186 = I64_sub(_t3184, _t3185);
    (void)_t3186;
    ;
    ;
    I32 _t3187 = I64_to_i32(_t3186);
    (void)_t3187;
    ;
    fd->variadic_index = _t3187;
    ;
    I64 _t3188 = 0;
    (void)_t3188;
    I64 _t3189 = 1;
    (void)_t3189;
    I64 _t3190 = I64_sub(_t3188, _t3189);
    (void)_t3190;
    ;
    ;
    I32 _t3191 = I64_to_i32(_t3190);
    (void)_t3191;
    ;
    fd->kwargs_index = _t3191;
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
            Vec_push(&fd->param_fn_sigs, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = _t3142; _oa; }));
        }
        ;
    }
    Vec_delete(&fd->param_types, &(Bool){0});
    { Vec *_fa = Vec_clone(ptypes); fd->param_types = *_fa; free(_fa); }
    Vec_delete(ptypes, &(Bool){1});
    Vec_delete(&fd->param_muts, &(Bool){0});
    { Vec *_fa = Vec_clone(pmuts); fd->param_muts = *_fa; free(_fa); }
    Vec_delete(pmuts, &(Bool){1});
    U64 _t3192; { U64 *_hp = (U64 *)Vec_len(&fd->param_types); _t3192 = *_hp; free(_hp); }
    (void)_t3192;
    I64 _t3193 = U64_to_i64(_t3192);
    (void)_t3193;
    ;
    U32 _t3194 = I64_to_u32(_t3193);
    (void)_t3194;
    ;
    fd->nparam = _t3194;
    ;
    ExprData *_t3195 = ExprData_FuncDef(fd);
    (void)_t3195;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *sig = Expr_new(_t3195, line, col, &p->path);
    (void)sig;
    ExprData_delete(_t3195, &(Bool){1});
    return sig;
}

Expr * parse_block(Parser * p) {
    (void)p;
    U32 _t3202 = peek_line(p);
    (void)_t3202;
    U32 _t3203 = peek_col(p);
    (void)_t3203;
    Expr *body = Expr_new(ExprData_Body(), _t3202, _t3203, &p->path);
    (void)body;
    ;
    ;
    while (1) {
        Bool _t3197 = check(p, TokenType_RBrace());
        (void)_t3197;
        Bool _t3198 = check(p, TokenType_Eof());
        (void)_t3198;
        Bool _t3199 = Bool_not(_t3197);
        (void)_t3199;
        ;
        Bool _t3200 = Bool_not(_t3198);
        (void)_t3200;
        ;
        Bool _wcond3196 = Bool_and(_t3199, _t3200);
        (void)_wcond3196;
        ;
        ;
        if (_wcond3196) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t3201 = parse_statement(p);
        (void)_t3201;
        Expr_add_child(body, _t3201);
    }
    Token *_t3204 = expect_token(p, TokenType_RBrace());
    (void)_t3204;
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
        TokenType *_sw3205 = TokenType_clone(&kw->type);
        (void)_sw3205;
        Bool _t3217; { Bool *_hp = (Bool *)TokenType_eq(_sw3205, TokenType_KwFunc()); _t3217 = *_hp; free(_hp); }
        (void)_t3217;
        if (_t3217) {
            ft = FuncType_clone(FuncType_Func());
        } else {
            Bool _t3216; { Bool *_hp = (Bool *)TokenType_eq(_sw3205, TokenType_KwProc()); _t3216 = *_hp; free(_hp); }
            (void)_t3216;
            if (_t3216) {
                ft = FuncType_clone(FuncType_Proc());
            } else {
                Bool _t3215; { Bool *_hp = (Bool *)TokenType_eq(_sw3205, TokenType_KwTest()); _t3215 = *_hp; free(_hp); }
                (void)_t3215;
                if (_t3215) {
                    ft = FuncType_clone(FuncType_Test());
                } else {
                    Bool _t3214; { Bool *_hp = (Bool *)TokenType_eq(_sw3205, TokenType_KwMacro()); _t3214 = *_hp; free(_hp); }
                    (void)_t3214;
                    if (_t3214) {
                        ft = FuncType_clone(FuncType_Macro());
                    } else {
                        Bool _t3213; { Bool *_hp = (Bool *)TokenType_eq(_sw3205, TokenType_KwExtFunc()); _t3213 = *_hp; free(_hp); }
                        (void)_t3213;
                        if (_t3213) {
                            ft = FuncType_clone(FuncType_ExtFunc());
                        } else {
                            Bool _t3212; { Bool *_hp = (Bool *)TokenType_eq(_sw3205, TokenType_KwExtProc()); _t3212 = *_hp; free(_hp); }
                            (void)_t3212;
                            if (_t3212) {
                                ft = FuncType_clone(FuncType_ExtProc());
                            } else {
                                Str *_t3206 = Str_lit("Str", 3ULL);
                                (void)_t3206;
                                U64 _t3207; { U64 *_hp = (U64 *)Str_size(); _t3207 = *_hp; free(_hp); }
                                (void)_t3207;
                                U64 _t3208 = 1;
                                (void)_t3208;
                                Array *_va56 = Array_new(_t3206, &(U64){_t3207}, &(U64){_t3208});
                                (void)_va56;
                                Str_delete(_t3206, &(Bool){1});
                                ;
                                ;
                                U64 _t3209 = 0;
                                (void)_t3209;
                                Str *_t3210 = Str_lit("expected function keyword", 25ULL);
                                (void)_t3210;
                                Array_set(_va56, &(U64){_t3209}, _t3210);
                                ;
                                Str *_t3211 = Str_lit("src/self/parser.til:134:17", 26ULL);
                                (void)_t3211;
                                panic(_t3211, _va56);
                                Str_delete(_t3211, &(Bool){1});
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
        TokenType_delete(_sw3205, &(Bool){1});
        ;
    }
    Token *_t3411 = expect_token(p, TokenType_LParen());
    (void)_t3411;
    Str *_t3412 = Str_lit("Str", 3ULL);
    (void)_t3412;
    U64 _t3413; { U64 *_hp = (U64 *)Str_size(); _t3413 = *_hp; free(_hp); }
    (void)_t3413;
    Str *_t3414 = Str_lit("Str", 3ULL);
    (void)_t3414;
    U64 _t3415; { U64 *_hp = (U64 *)Str_size(); _t3415 = *_hp; free(_hp); }
    (void)_t3415;
    Str *_t3416 = Str_lit("Bool", 4ULL);
    (void)_t3416;
    U64 _t3417; { U64 *_hp = (U64 *)Bool_size(); _t3417 = *_hp; free(_hp); }
    (void)_t3417;
    Str *_t3418 = Str_lit("Bool", 4ULL);
    (void)_t3418;
    U64 _t3419; { U64 *_hp = (U64 *)Bool_size(); _t3419 = *_hp; free(_hp); }
    (void)_t3419;
    Str *_t3420 = Str_lit("Bool", 4ULL);
    (void)_t3420;
    U64 _t3421; { U64 *_hp = (U64 *)Bool_size(); _t3421 = *_hp; free(_hp); }
    (void)_t3421;
    Str *_t3422 = Str_lit("I64", 3ULL);
    (void)_t3422;
    U64 _t3423; { U64 *_hp = (U64 *)I64_size(); _t3423 = *_hp; free(_hp); }
    (void)_t3423;
    Str *_t3424 = Str_lit("Str", 3ULL);
    (void)_t3424;
    U64 _t3425; { U64 *_hp = (U64 *)Str_size(); _t3425 = *_hp; free(_hp); }
    (void)_t3425;
    Str *_t3426 = Str_lit("Expr", 4ULL);
    (void)_t3426;
    U64 _t3427; { U64 *_hp = (U64 *)Expr_size(); _t3427 = *_hp; free(_hp); }
    (void)_t3427;
    I64 _t3428 = 0;
    (void)_t3428;
    I64 _t3429 = 1;
    (void)_t3429;
    I64 _t3430 = I64_sub(_t3428, _t3429);
    (void)_t3430;
    ;
    ;
    I64 _t3431 = 0;
    (void)_t3431;
    I64 _t3432 = 1;
    (void)_t3432;
    I64 _t3433 = I64_sub(_t3431, _t3432);
    (void)_t3433;
    ;
    ;
    U32 _t3434 = 0;
    (void)_t3434;
    I32 _t3435 = I64_to_i32(_t3430);
    (void)_t3435;
    ;
    I32 _t3436 = I64_to_i32(_t3433);
    (void)_t3436;
    ;
    Bool _t3437 = 0;
    (void)_t3437;
    Bool _t3438 = 0;
    (void)_t3438;
    FunctionDef *fd = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(FuncType_Func()); fd->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3412, &(U64){_t3413}); fd->param_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3414, &(U64){_t3415}); fd->param_types = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3416, &(U64){_t3417}); fd->param_muts = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3418, &(U64){_t3419}); fd->param_owns = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3420, &(U64){_t3421}); fd->param_shallows = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3422, &(U64){_t3423}); fd->param_fn_sigs = *_ca; free(_ca); }
    fd->nparam = _t3434;
    { Map *_ca = Map_new(_t3424, &(U64){_t3425}, _t3426, &(U64){_t3427}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3435;
    fd->kwargs_index = _t3436;
    fd->return_is_ref = _t3437;
    fd->return_is_shallow = _t3438;
    (void)fd;
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
    Str_delete(_t3424, &(Bool){1});
    ;
    Str_delete(_t3426, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    FuncType_delete(&fd->func_type, &(Bool){0});
    { FuncType *_fa = FuncType_clone(ft); fd->func_type = *_fa; free(_fa); }
    Str *_t3439 = Str_lit("Expr", 4ULL);
    (void)_t3439;
    U64 _t3440; { U64 *_hp = (U64 *)Expr_size(); _t3440 = *_hp; free(_hp); }
    (void)_t3440;
    Vec *def_exprs = Vec_new(_t3439, &(U64){_t3440});
    (void)def_exprs;
    Str_delete(_t3439, &(Bool){1});
    ;
    while (1) {
        Bool _t3336 = check(p, TokenType_RParen());
        (void)_t3336;
        Bool _t3337 = check(p, TokenType_Eof());
        (void)_t3337;
        Bool _t3338 = Bool_not(_t3336);
        (void)_t3338;
        ;
        Bool _t3339 = Bool_not(_t3337);
        (void)_t3339;
        ;
        Bool _wcond3218 = Bool_and(_t3338, _t3339);
        (void)_wcond3218;
        ;
        ;
        if (_wcond3218) {
        } else {
            ;
            break;
        }
        ;
        Bool is_shallow = 0;
        (void)is_shallow;
        Bool _t3340 = check(p, TokenType_KwShallow());
        (void)_t3340;
        if (_t3340) {
            Token *_t3219 = advance(p);
            (void)_t3219;
            Bool _t3220 = 1;
            (void)_t3220;
            is_shallow = _t3220;
            ;
        }
        ;
        Bool is_own = 0;
        (void)is_own;
        Bool _t3341 = check(p, TokenType_KwOwn());
        (void)_t3341;
        if (_t3341) {
            Token *_t3221 = advance(p);
            (void)_t3221;
            Bool _t3222 = 1;
            (void)_t3222;
            is_own = _t3222;
            ;
        }
        ;
        Bool is_mut = 0;
        (void)is_mut;
        Bool _t3342 = check(p, TokenType_KwMut());
        (void)_t3342;
        if (_t3342) {
            Token *_t3223 = advance(p);
            (void)_t3223;
            Bool _t3224 = 1;
            (void)_t3224;
            is_mut = _t3224;
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
        Bool _t3343 = check(p, TokenType_Colon());
        (void)_t3343;
        Bool _t3344 = Bool_not(_t3343);
        (void)_t3344;
        ;
        if (_t3344) {
            tp = Str_clone(pname);
            nm = Str_lit("", 0ULL);
        } else {
            Token *_t3318 = expect_token(p, TokenType_Colon());
            (void)_t3318;
            Bool _t3319 = check(p, TokenType_DotDotDot());
            (void)_t3319;
            if (_t3319) {
                Token *_t3255 = advance(p);
                (void)_t3255;
                Bool _t3256 = Bool_or(is_own, is_mut);
                (void)_t3256;
                Bool _t3257 = Bool_or(_t3256, is_shallow);
                (void)_t3257;
                ;
                if (_t3257) {
                    Str *_t3225 = Str_lit("Str", 3ULL);
                    (void)_t3225;
                    U64 _t3226; { U64 *_hp = (U64 *)Str_size(); _t3226 = *_hp; free(_hp); }
                    (void)_t3226;
                    U64 _t3227 = 6;
                    (void)_t3227;
                    Array *_va57 = Array_new(_t3225, &(U64){_t3226}, &(U64){_t3227});
                    (void)_va57;
                    Str_delete(_t3225, &(Bool){1});
                    ;
                    ;
                    U64 _t3228 = 0;
                    (void)_t3228;
                    Str *_t3229 = Str_clone(&p->path);
                    (void)_t3229;
                    Array_set(_va57, &(U64){_t3228}, _t3229);
                    ;
                    U64 _t3230 = 1;
                    (void)_t3230;
                    Str *_t3231 = Str_lit(":", 1ULL);
                    (void)_t3231;
                    Array_set(_va57, &(U64){_t3230}, _t3231);
                    ;
                    U32 _t3232 = peek_line(p);
                    (void)_t3232;
                    U64 _t3233 = 2;
                    (void)_t3233;
                    Str *_t3234 = U32_to_str(&(U32){_t3232});
                    (void)_t3234;
                    ;
                    Array_set(_va57, &(U64){_t3233}, _t3234);
                    ;
                    U64 _t3235 = 3;
                    (void)_t3235;
                    Str *_t3236 = Str_lit(":", 1ULL);
                    (void)_t3236;
                    Array_set(_va57, &(U64){_t3235}, _t3236);
                    ;
                    U32 _t3237 = peek_col(p);
                    (void)_t3237;
                    U64 _t3238 = 4;
                    (void)_t3238;
                    Str *_t3239 = U32_to_str(&(U32){_t3237});
                    (void)_t3239;
                    ;
                    Array_set(_va57, &(U64){_t3238}, _t3239);
                    ;
                    U64 _t3240 = 5;
                    (void)_t3240;
                    Str *_t3241 = Str_lit(": kwargs parameter cannot be own/mut/shallow", 44ULL);
                    (void)_t3241;
                    Array_set(_va57, &(U64){_t3240}, _t3241);
                    ;
                    Str *_t3242 = Str_lit("src/self/parser.til:165:27", 26ULL);
                    (void)_t3242;
                    panic(_t3242, _va57);
                    Str_delete(_t3242, &(Bool){1});
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
                Bool _t3262; { Bool *_hp = (Bool *)I32_neq(&fd->kwargs_index, &(I32){_t3261}); _t3262 = *_hp; free(_hp); }
                (void)_t3262;
                ;
                if (_t3262) {
                    Str *_t3243 = Str_lit("Str", 3ULL);
                    (void)_t3243;
                    U64 _t3244; { U64 *_hp = (U64 *)Str_size(); _t3244 = *_hp; free(_hp); }
                    (void)_t3244;
                    U64 _t3245 = 1;
                    (void)_t3245;
                    Array *_va58 = Array_new(_t3243, &(U64){_t3244}, &(U64){_t3245});
                    (void)_va58;
                    Str_delete(_t3243, &(Bool){1});
                    ;
                    ;
                    U64 _t3246 = 0;
                    (void)_t3246;
                    Str *_t3247 = Str_lit("only one kwargs parameter is allowed", 36ULL);
                    (void)_t3247;
                    Array_set(_va58, &(U64){_t3246}, _t3247);
                    ;
                    Str *_t3248 = Str_lit("src/self/parser.til:169:27", 26ULL);
                    (void)_t3248;
                    panic(_t3248, _va58);
                    Str_delete(_t3248, &(Bool){1});
                }
                ;
                I64 _t3263 = 0;
                (void)_t3263;
                I64 _t3264 = 1;
                (void)_t3264;
                I64 _t3265 = I64_sub(_t3263, _t3264);
                (void)_t3265;
                ;
                ;
                I32 _t3266 = I64_to_i32(_t3265);
                (void)_t3266;
                ;
                Bool _t3267; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3266}); _t3267 = *_hp; free(_hp); }
                (void)_t3267;
                ;
                if (_t3267) {
                    Str *_t3249 = Str_lit("Str", 3ULL);
                    (void)_t3249;
                    U64 _t3250; { U64 *_hp = (U64 *)Str_size(); _t3250 = *_hp; free(_hp); }
                    (void)_t3250;
                    U64 _t3251 = 1;
                    (void)_t3251;
                    Array *_va59 = Array_new(_t3249, &(U64){_t3250}, &(U64){_t3251});
                    (void)_va59;
                    Str_delete(_t3249, &(Bool){1});
                    ;
                    ;
                    U64 _t3252 = 0;
                    (void)_t3252;
                    Str *_t3253 = Str_lit("cannot combine variadic and kwargs in the same function", 55ULL);
                    (void)_t3253;
                    Array_set(_va59, &(U64){_t3252}, _t3253);
                    ;
                    Str *_t3254 = Str_lit("src/self/parser.til:172:27", 26ULL);
                    (void)_t3254;
                    panic(_t3254, _va59);
                    Str_delete(_t3254, &(Bool){1});
                }
                ;
                U64 _t3268; { U64 *_hp = (U64 *)Vec_len(&fd->param_names); _t3268 = *_hp; free(_hp); }
                (void)_t3268;
                I64 _t3269 = U64_to_i64(_t3268);
                (void)_t3269;
                ;
                I32 _t3270 = I64_to_i32(_t3269);
                (void)_t3270;
                ;
                fd->kwargs_index = _t3270;
                ;
                Bool _t3271 = 1;
                (void)_t3271;
                is_own = _t3271;
                ;
                nm = Str_clone(pname);
                tp = Str_lit("Map", 3ULL);
            } else {
                Bool _t3317 = check(p, TokenType_DotDot());
                (void)_t3317;
                if (_t3317) {
                    Token *_t3302 = advance(p);
                    (void)_t3302;
                    if (is_own) {
                        Str *_t3272 = Str_lit("Str", 3ULL);
                        (void)_t3272;
                        U64 _t3273; { U64 *_hp = (U64 *)Str_size(); _t3273 = *_hp; free(_hp); }
                        (void)_t3273;
                        U64 _t3274 = 1;
                        (void)_t3274;
                        Array *_va60 = Array_new(_t3272, &(U64){_t3273}, &(U64){_t3274});
                        (void)_va60;
                        Str_delete(_t3272, &(Bool){1});
                        ;
                        ;
                        U64 _t3275 = 0;
                        (void)_t3275;
                        Str *_t3276 = Str_lit("variadic param cannot be 'own'", 30ULL);
                        (void)_t3276;
                        Array_set(_va60, &(U64){_t3275}, _t3276);
                        ;
                        Str *_t3277 = Str_lit("src/self/parser.til:180:35", 26ULL);
                        (void)_t3277;
                        panic(_t3277, _va60);
                        Str_delete(_t3277, &(Bool){1});
                    }
                    if (is_mut) {
                        Str *_t3278 = Str_lit("Str", 3ULL);
                        (void)_t3278;
                        U64 _t3279; { U64 *_hp = (U64 *)Str_size(); _t3279 = *_hp; free(_hp); }
                        (void)_t3279;
                        U64 _t3280 = 1;
                        (void)_t3280;
                        Array *_va61 = Array_new(_t3278, &(U64){_t3279}, &(U64){_t3280});
                        (void)_va61;
                        Str_delete(_t3278, &(Bool){1});
                        ;
                        ;
                        U64 _t3281 = 0;
                        (void)_t3281;
                        Str *_t3282 = Str_lit("variadic param cannot be 'mut'", 30ULL);
                        (void)_t3282;
                        Array_set(_va61, &(U64){_t3281}, _t3282);
                        ;
                        Str *_t3283 = Str_lit("src/self/parser.til:181:35", 26ULL);
                        (void)_t3283;
                        panic(_t3283, _va61);
                        Str_delete(_t3283, &(Bool){1});
                    }
                    if (is_shallow) {
                        Str *_t3284 = Str_lit("Str", 3ULL);
                        (void)_t3284;
                        U64 _t3285; { U64 *_hp = (U64 *)Str_size(); _t3285 = *_hp; free(_hp); }
                        (void)_t3285;
                        U64 _t3286 = 1;
                        (void)_t3286;
                        Array *_va62 = Array_new(_t3284, &(U64){_t3285}, &(U64){_t3286});
                        (void)_va62;
                        Str_delete(_t3284, &(Bool){1});
                        ;
                        ;
                        U64 _t3287 = 0;
                        (void)_t3287;
                        Str *_t3288 = Str_lit("variadic param cannot be 'shallow'", 34ULL);
                        (void)_t3288;
                        Array_set(_va62, &(U64){_t3287}, _t3288);
                        ;
                        Str *_t3289 = Str_lit("src/self/parser.til:182:39", 26ULL);
                        (void)_t3289;
                        panic(_t3289, _va62);
                        Str_delete(_t3289, &(Bool){1});
                    }
                    I64 _t3303 = 0;
                    (void)_t3303;
                    I64 _t3304 = 1;
                    (void)_t3304;
                    I64 _t3305 = I64_sub(_t3303, _t3304);
                    (void)_t3305;
                    ;
                    ;
                    I32 _t3306 = I64_to_i32(_t3305);
                    (void)_t3306;
                    ;
                    Bool _t3307; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3306}); _t3307 = *_hp; free(_hp); }
                    (void)_t3307;
                    ;
                    if (_t3307) {
                        Str *_t3290 = Str_lit("Str", 3ULL);
                        (void)_t3290;
                        U64 _t3291; { U64 *_hp = (U64 *)Str_size(); _t3291 = *_hp; free(_hp); }
                        (void)_t3291;
                        U64 _t3292 = 1;
                        (void)_t3292;
                        Array *_va63 = Array_new(_t3290, &(U64){_t3291}, &(U64){_t3292});
                        (void)_va63;
                        Str_delete(_t3290, &(Bool){1});
                        ;
                        ;
                        U64 _t3293 = 0;
                        (void)_t3293;
                        Str *_t3294 = Str_lit("only one variadic param allowed", 31ULL);
                        (void)_t3294;
                        Array_set(_va63, &(U64){_t3293}, _t3294);
                        ;
                        Str *_t3295 = Str_lit("src/self/parser.til:183:69", 26ULL);
                        (void)_t3295;
                        panic(_t3295, _va63);
                        Str_delete(_t3295, &(Bool){1});
                    }
                    ;
                    I64 _t3308 = 0;
                    (void)_t3308;
                    I64 _t3309 = 1;
                    (void)_t3309;
                    I64 _t3310 = I64_sub(_t3308, _t3309);
                    (void)_t3310;
                    ;
                    ;
                    I32 _t3311 = I64_to_i32(_t3310);
                    (void)_t3311;
                    ;
                    Bool _t3312; { Bool *_hp = (Bool *)I32_neq(&fd->kwargs_index, &(I32){_t3311}); _t3312 = *_hp; free(_hp); }
                    (void)_t3312;
                    ;
                    if (_t3312) {
                        Str *_t3296 = Str_lit("Str", 3ULL);
                        (void)_t3296;
                        U64 _t3297; { U64 *_hp = (U64 *)Str_size(); _t3297 = *_hp; free(_hp); }
                        (void)_t3297;
                        U64 _t3298 = 1;
                        (void)_t3298;
                        Array *_va64 = Array_new(_t3296, &(U64){_t3297}, &(U64){_t3298});
                        (void)_va64;
                        Str_delete(_t3296, &(Bool){1});
                        ;
                        ;
                        U64 _t3299 = 0;
                        (void)_t3299;
                        Str *_t3300 = Str_lit("cannot combine variadic and kwargs in the same function", 55ULL);
                        (void)_t3300;
                        Array_set(_va64, &(U64){_t3299}, _t3300);
                        ;
                        Str *_t3301 = Str_lit("src/self/parser.til:185:27", 26ULL);
                        (void)_t3301;
                        panic(_t3301, _va64);
                        Str_delete(_t3301, &(Bool){1});
                    }
                    ;
                    U64 _t3313; { U64 *_hp = (U64 *)Vec_len(&fd->param_names); _t3313 = *_hp; free(_hp); }
                    (void)_t3313;
                    I64 _t3314 = U64_to_i64(_t3313);
                    (void)_t3314;
                    ;
                    I32 _t3315 = I64_to_i32(_t3314);
                    (void)_t3315;
                    ;
                    fd->variadic_index = _t3315;
                    ;
                    Bool _t3316 = 1;
                    (void)_t3316;
                    is_variadic = _t3316;
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
        I64 _t3345 = 0;
        (void)_t3345;
        I64 _t3346 = 1;
        (void)_t3346;
        I64 fn_sig_idx = I64_sub(_t3345, _t3346);
        (void)fn_sig_idx;
        ;
        ;
        Str *_t3347 = Str_lit("Fn", 2ULL);
        (void)_t3347;
        Bool _t3348; { Bool *_hp = (Bool *)Str_eq(tp, _t3347); _t3348 = *_hp; free(_hp); }
        (void)_t3348;
        Str_delete(_t3347, &(Bool){1});
        if (_t3348) {
            U32 _t3322 = peek_line(p);
            (void)_t3322;
            U32 _t3323 = peek_col(p);
            (void)_t3323;
            Expr *sig = parse_fn_signature(p, _t3322, _t3323);
            (void)sig;
            ;
            ;
            U32 _t3324 = 0;
            (void)_t3324;
            Bool _t3325; { Bool *_hp = (Bool *)U32_neq(&sig->line, &(U32){_t3324}); _t3325 = *_hp; free(_hp); }
            (void)_t3325;
            ;
            if (_t3325) {
                U64 _t3320; { U64 *_hp = (U64 *)Vec_len(def_exprs); _t3320 = *_hp; free(_hp); }
                (void)_t3320;
                I64 _t3321 = U64_to_i64(_t3320);
                (void)_t3321;
                ;
                fn_sig_idx = _t3321;
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
        I64 _t3349 = 0;
        (void)_t3349;
        I64 _t3350 = 1;
        (void)_t3350;
        I64 has_default = I64_sub(_t3349, _t3350);
        (void)has_default;
        ;
        ;
        Bool _t3351 = check(p, TokenType_Eq());
        (void)_t3351;
        if (_t3351) {
            Token *_t3326 = advance(p);
            (void)_t3326;
            U64 _t3327; { U64 *_hp = (U64 *)Vec_len(def_exprs); _t3327 = *_hp; free(_hp); }
            (void)_t3327;
            I64 _t3328 = U64_to_i64(_t3327);
            (void)_t3328;
            ;
            has_default = _t3328;
            ;
            Expr *def_expr = parse_expression(p);
            (void)def_expr;
            Vec_push(def_exprs, def_expr);
        }
        ;
        I64 _t3352 = 0;
        (void)_t3352;
        I64 _t3353 = 1;
        (void)_t3353;
        I64 _t3354 = I64_sub(_t3352, _t3353);
        (void)_t3354;
        ;
        ;
        I32 _t3355 = I64_to_i32(_t3354);
        (void)_t3355;
        ;
        Bool _t3356; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3355}); _t3356 = *_hp; free(_hp); }
        (void)_t3356;
        ;
        Bool _t3357 = Bool_not(is_variadic);
        (void)_t3357;
        ;
        I64 _t3358 = 0;
        (void)_t3358;
        I64 _t3359 = 1;
        (void)_t3359;
        I64 _t3360 = I64_sub(_t3358, _t3359);
        (void)_t3360;
        ;
        ;
        Bool _t3361 = Bool_and(_t3356, _t3357);
        (void)_t3361;
        ;
        ;
        Bool _t3362 = I64_eq(has_default, _t3360);
        (void)_t3362;
        ;
        ;
        Bool _t3363 = Bool_and(_t3361, _t3362);
        (void)_t3363;
        ;
        ;
        if (_t3363) {
            Str *_t3329 = Str_lit("Str", 3ULL);
            (void)_t3329;
            U64 _t3330; { U64 *_hp = (U64 *)Str_size(); _t3330 = *_hp; free(_hp); }
            (void)_t3330;
            U64 _t3331 = 1;
            (void)_t3331;
            Array *_va65 = Array_new(_t3329, &(U64){_t3330}, &(U64){_t3331});
            (void)_va65;
            Str_delete(_t3329, &(Bool){1});
            ;
            ;
            U64 _t3332 = 0;
            (void)_t3332;
            Str *_t3333 = Str_lit("positional param not allowed after variadic", 43ULL);
            (void)_t3333;
            Array_set(_va65, &(U64){_t3332}, _t3333);
            ;
            Str *_t3334 = Str_lit("src/self/parser.til:224:19", 26ULL);
            (void)_t3334;
            panic(_t3334, _va65);
            Str_delete(_t3334, &(Bool){1});
        }
        ;
        Bool _t3364 = check(p, TokenType_Comma());
        (void)_t3364;
        if (_t3364) {
            Token *_t3335 = advance(p);
            (void)_t3335;
        }
        ;
    }
    Token *_t3441 = expect_token(p, TokenType_RParen());
    (void)_t3441;
    Bool _t3442 = check(p, TokenType_KwReturns());
    (void)_t3442;
    if (_t3442) {
        Token *_t3370 = advance(p);
        (void)_t3370;
        Bool _t3371 = check(p, TokenType_KwRef());
        (void)_t3371;
        if (_t3371) {
            Token *_t3365 = advance(p);
            (void)_t3365;
            Bool _t3366 = 1;
            (void)_t3366;
            fd->return_is_ref = _t3366;
            ;
        } else {
            Bool _t3369 = check(p, TokenType_KwShallow());
            (void)_t3369;
            if (_t3369) {
                Token *_t3367 = advance(p);
                (void)_t3367;
                Bool _t3368 = 1;
                (void)_t3368;
                fd->return_is_shallow = _t3368;
                ;
            }
            ;
        }
        ;
        Str_delete(&fd->return_type, &(Bool){0});
        { Str *_fa = expect_text(p, TokenType_Ident()); fd->return_type = *_fa; free(_fa); }
    }
    ;
    U64 _t3443; { U64 *_hp = (U64 *)Vec_len(&fd->param_names); _t3443 = *_hp; free(_hp); }
    (void)_t3443;
    I64 _t3444 = U64_to_i64(_t3443);
    (void)_t3444;
    ;
    U32 _t3445 = I64_to_u32(_t3444);
    (void)_t3445;
    ;
    fd->nparam = _t3445;
    ;
    ExprData *_t3446 = ExprData_FuncDef(fd);
    (void)_t3446;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *def = Expr_new(_t3446, kw_line, kw_col, &p->path);
    (void)def;
    ExprData_delete(_t3446, &(Bool){1});
    Bool _t3447 = check(p, TokenType_LBrace());
    (void)_t3447;
    if (_t3447) {
        Token *_t3372 = expect_token(p, TokenType_LBrace());
        (void)_t3372;
        Expr *_t3373 = parse_block(p);
        (void)_t3373;
        Expr_add_child(def, _t3373);
    } else {
        Bool _t3394; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Func()); _t3394 = *_hp; free(_hp); }
        (void)_t3394;
        Bool _t3395; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Proc()); _t3395 = *_hp; free(_hp); }
        (void)_t3395;
        Bool _t3396 = Bool_not(_t3394);
        (void)_t3396;
        ;
        Bool _t3397 = Bool_not(_t3395);
        (void)_t3397;
        ;
        Bool _t3398 = Bool_and(_t3396, _t3397);
        (void)_t3398;
        ;
        ;
        if (_t3398) {
            Str *_t3374 = Str_lit("Str", 3ULL);
            (void)_t3374;
            U64 _t3375; { U64 *_hp = (U64 *)Str_size(); _t3375 = *_hp; free(_hp); }
            (void)_t3375;
            U64 _t3376 = 8;
            (void)_t3376;
            Array *_va66 = Array_new(_t3374, &(U64){_t3375}, &(U64){_t3376});
            (void)_va66;
            Str_delete(_t3374, &(Bool){1});
            ;
            ;
            U64 _t3377 = 0;
            (void)_t3377;
            Str *_t3378 = Str_clone(&p->path);
            (void)_t3378;
            Array_set(_va66, &(U64){_t3377}, _t3378);
            ;
            U64 _t3379 = 1;
            (void)_t3379;
            Str *_t3380 = Str_lit(":", 1ULL);
            (void)_t3380;
            Array_set(_va66, &(U64){_t3379}, _t3380);
            ;
            U64 _t3381 = 2;
            (void)_t3381;
            Str *_t3382 = U32_to_str(&(U32){kw_line});
            (void)_t3382;
            Array_set(_va66, &(U64){_t3381}, _t3382);
            ;
            U64 _t3383 = 3;
            (void)_t3383;
            Str *_t3384 = Str_lit(":", 1ULL);
            (void)_t3384;
            Array_set(_va66, &(U64){_t3383}, _t3384);
            ;
            U64 _t3385 = 4;
            (void)_t3385;
            Str *_t3386 = U32_to_str(&(U32){kw_col});
            (void)_t3386;
            Array_set(_va66, &(U64){_t3385}, _t3386);
            ;
            U64 _t3387 = 5;
            (void)_t3387;
            Str *_t3388 = Str_lit(": ", 2ULL);
            (void)_t3388;
            Array_set(_va66, &(U64){_t3387}, _t3388);
            ;
            U64 _t3389 = 6;
            (void)_t3389;
            Str *_t3390 = func_type_name(ft);
            (void)_t3390;
            Array_set(_va66, &(U64){_t3389}, _t3390);
            ;
            U64 _t3391 = 7;
            (void)_t3391;
            Str *_t3392 = Str_lit(" requires a body", 16ULL);
            (void)_t3392;
            Array_set(_va66, &(U64){_t3391}, _t3392);
            ;
            Str *_t3393 = Str_lit("src/self/parser.til:252:19", 26ULL);
            (void)_t3393;
            panic(_t3393, _va66);
            Str_delete(_t3393, &(Bool){1});
        }
        ;
    }
    ;
    FuncType_delete(ft, &(Bool){1});
    ;
    ;
    {
        U64 _fi3399 = 0;
        (void)_fi3399;
        while (1) {
            U64 _t3401 = 0;
            (void)_t3401;
            U64 _t3402; { U64 *_hp = (U64 *)Vec_len(def_exprs); _t3402 = *_hp; free(_hp); }
            (void)_t3402;
            Range *_t3403 = Range_new(_t3401, _t3402);
            (void)_t3403;
            ;
            ;
            U64 _t3404; { U64 *_hp = (U64 *)Range_len(_t3403); _t3404 = *_hp; free(_hp); }
            (void)_t3404;
            Range_delete(_t3403, &(Bool){1});
            Bool _wcond3400; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3399}, &(U64){_t3404}); _wcond3400 = *_hp; free(_hp); }
            (void)_wcond3400;
            ;
            if (_wcond3400) {
            } else {
                ;
                break;
            }
            ;
            U64 _t3405 = 0;
            (void)_t3405;
            U64 _t3406; { U64 *_hp = (U64 *)Vec_len(def_exprs); _t3406 = *_hp; free(_hp); }
            (void)_t3406;
            Range *_t3407 = Range_new(_t3405, _t3406);
            (void)_t3407;
            ;
            ;
            U64 *i = Range_get(_t3407, _fi3399);
            (void)i;
            Range_delete(_t3407, &(Bool){1});
            U64 _t3408 = 1;
            (void)_t3408;
            U64 _t3409 = U64_add(_fi3399, _t3408);
            (void)_t3409;
            ;
            _fi3399 = _t3409;
            ;
            Expr *de = Vec_get(def_exprs, i);
            (void)de;
            Expr *_t3410 = Expr_clone(de);
            (void)_t3410;
            U64_delete(i, &(Bool){1});
            Expr_add_child(def, _t3410);
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
    Token *_t3461 = advance(p);
    (void)_t3461;
    Expr *def = Expr_new(ExprData_StructDef(), kw_line, kw_col, &p->path);
    (void)def;
    ;
    ;
    Bool _t3462 = Bool_clone(&(Bool){is_ext});
    (void)_t3462;
    ;
    def->is_ext = _t3462;
    ;
    Token *_t3463 = expect_token(p, TokenType_LBrace());
    (void)_t3463;
    U32 _t3464 = peek_line(p);
    (void)_t3464;
    U32 _t3465 = peek_col(p);
    (void)_t3465;
    Expr *body = Expr_new(ExprData_Body(), _t3464, _t3465, &p->path);
    (void)body;
    ;
    ;
    Bool in_namespace = 0;
    (void)in_namespace;
    while (1) {
        Bool _t3454 = check(p, TokenType_RBrace());
        (void)_t3454;
        Bool _t3455 = check(p, TokenType_Eof());
        (void)_t3455;
        Bool _t3456 = Bool_not(_t3454);
        (void)_t3456;
        ;
        Bool _t3457 = Bool_not(_t3455);
        (void)_t3457;
        ;
        Bool _wcond3448 = Bool_and(_t3456, _t3457);
        (void)_wcond3448;
        ;
        ;
        if (_wcond3448) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3458 = check(p, TokenType_KwNamespace());
        (void)_t3458;
        if (_t3458) {
            Token *_t3449 = advance(p);
            (void)_t3449;
            Token *_t3450 = expect_token(p, TokenType_Colon());
            (void)_t3450;
            Bool _t3451 = 1;
            (void)_t3451;
            in_namespace = _t3451;
            ;
            ;
            continue;
        }
        ;
        Expr *stmt = parse_statement(p);
        (void)stmt;
        Bool _t3459; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3459 = *_hp; free(_hp); }
        (void)_t3459;
        Bool _t3460 = Bool_and(in_namespace, _t3459);
        (void)_t3460;
        ;
        if (_t3460) {
            Bool _t3453; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3453 = *_hp; free(_hp); }
            (void)_t3453;
            if (_t3453) {
                Declaration *dd = ExprData_get_Decl(&stmt->data);
                (void)dd;
                Bool _t3452 = 1;
                (void)_t3452;
                dd->is_namespace = _t3452;
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
    Token *_t3466 = expect_token(p, TokenType_RBrace());
    (void)_t3466;
    Expr_add_child(def, body);
    return def;
}

Expr * parse_enum_def(Parser * p) {
    (void)p;
    U32 kw_line = peek_line(p);
    (void)kw_line;
    U32 kw_col = peek_col(p);
    (void)kw_col;
    Token *_t3490 = advance(p);
    (void)_t3490;
    Expr *def = Expr_new(ExprData_EnumDef(), kw_line, kw_col, &p->path);
    (void)def;
    ;
    ;
    Token *_t3491 = expect_token(p, TokenType_LBrace());
    (void)_t3491;
    U32 _t3492 = peek_line(p);
    (void)_t3492;
    U32 _t3493 = peek_col(p);
    (void)_t3493;
    Expr *body = Expr_new(ExprData_Body(), _t3492, _t3493, &p->path);
    (void)body;
    ;
    ;
    Bool in_namespace = 0;
    (void)in_namespace;
    while (1) {
        Bool _t3485 = check(p, TokenType_RBrace());
        (void)_t3485;
        Bool _t3486 = check(p, TokenType_Eof());
        (void)_t3486;
        Bool _t3487 = Bool_not(_t3485);
        (void)_t3487;
        ;
        Bool _t3488 = Bool_not(_t3486);
        (void)_t3488;
        ;
        Bool _wcond3467 = Bool_and(_t3487, _t3488);
        (void)_wcond3467;
        ;
        ;
        if (_wcond3467) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3489 = check(p, TokenType_KwNamespace());
        (void)_t3489;
        if (_t3489) {
            Token *_t3468 = advance(p);
            (void)_t3468;
            Token *_t3469 = expect_token(p, TokenType_Colon());
            (void)_t3469;
            Bool _t3470 = 1;
            (void)_t3470;
            in_namespace = _t3470;
            ;
            ;
            continue;
        }
        ;
        if (in_namespace) {
            Expr *stmt = parse_statement(p);
            (void)stmt;
            Bool _t3473; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3473 = *_hp; free(_hp); }
            (void)_t3473;
            if (_t3473) {
                Bool _t3472; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3472 = *_hp; free(_hp); }
                (void)_t3472;
                if (_t3472) {
                    Declaration *dd = ExprData_get_Decl(&stmt->data);
                    (void)dd;
                    Bool _t3471 = 1;
                    (void)_t3471;
                    dd->is_namespace = _t3471;
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
            Bool _t3476 = 0;
            (void)_t3476;
            Bool _t3477 = 0;
            (void)_t3477;
            Bool _t3478 = 0;
            (void)_t3478;
            Bool _t3479 = 0;
            (void)_t3479;
            I32 _t3480 = 0;
            (void)_t3480;
            I32 _t3481 = 0;
            (void)_t3481;
            Declaration *dd = malloc(sizeof(Declaration));
            { Str *_ca = Str_clone(vname); dd->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
            dd->is_mut = _t3476;
            dd->is_namespace = _t3477;
            dd->is_ref = _t3478;
            dd->is_own = _t3479;
            dd->field_offset = _t3480;
            dd->field_size = _t3481;
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
            Bool _t3482 = check(p, TokenType_Colon());
            (void)_t3482;
            if (_t3482) {
                Token *_t3474 = advance(p);
                (void)_t3474;
                Str_delete(&dd->explicit_type, &(Bool){0});
                { Str *_fa = expect_text(p, TokenType_Ident()); dd->explicit_type = *_fa; free(_fa); }
            }
            ;
            ExprData *_t3483 = ExprData_Decl(dd);
            (void)_t3483;
            Declaration_delete(dd, &(Bool){1});
            Expr *variant = Expr_new(_t3483, v_line, v_col, &p->path);
            (void)variant;
            ExprData_delete(_t3483, &(Bool){1});
            ;
            ;
            Expr_add_child(body, variant);
            Bool _t3484 = check(p, TokenType_Comma());
            (void)_t3484;
            if (_t3484) {
                Token *_t3475 = advance(p);
                (void)_t3475;
            }
            ;
        }
    }
    ;
    Token *_t3494 = expect_token(p, TokenType_RBrace());
    (void)_t3494;
    Expr_add_child(def, body);
    return def;
}

Expr * parse_call(Parser * p, Str * name, U32 call_line, U32 call_col) {
    (void)p;
    (void)name;
    (void)call_line;
    (void)call_col;
    Token *_t3525 = advance(p);
    (void)_t3525;
    Expr *call = Expr_new(ExprData_FCall(), call_line, call_col, &p->path);
    (void)call;
    Str *_t3526 = Str_clone(name);
    (void)_t3526;
    ExprData *_t3527 = ExprData_Ident(_t3526);
    (void)_t3527;
    Str_delete(_t3526, &(Bool){1});
    Expr *callee = Expr_new(_t3527, call_line, call_col, &p->path);
    (void)callee;
    ExprData_delete(_t3527, &(Bool){1});
    Expr_add_child(call, callee);
    while (1) {
        Bool _t3515 = check(p, TokenType_RParen());
        (void)_t3515;
        Bool _t3516 = check(p, TokenType_Eof());
        (void)_t3516;
        Bool _t3517 = Bool_not(_t3515);
        (void)_t3517;
        ;
        Bool _t3518 = Bool_not(_t3516);
        (void)_t3518;
        ;
        Bool _wcond3495 = Bool_and(_t3517, _t3518);
        (void)_wcond3495;
        ;
        ;
        if (_wcond3495) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3519 = check(p, TokenType_Ident());
        (void)_t3519;
        if (_t3519) {
            U64 _t3506 = 1;
            (void)_t3506;
            U64 _t3507 = U64_add(p->pos, _t3506);
            (void)_t3507;
            ;
            U64 _t3508; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3508 = *_hp; free(_hp); }
            (void)_t3508;
            Bool _t3509; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3507}, &(U64){_t3508}); _t3509 = *_hp; free(_hp); }
            (void)_t3509;
            ;
            ;
            if (_t3509) {
                U64 _t3501 = 1;
                (void)_t3501;
                U64 _t3502 = U64_add(p->pos, _t3501);
                (void)_t3502;
                ;
                I64 _t3503 = U64_to_i64(_t3502);
                (void)_t3503;
                ;
                U64 *_t3504 = malloc(sizeof(U64)); *_t3504 = I64_to_u64(_t3503);
                (void)_t3504;
                ;
                Token *next_tok = Vec_get(&p->tokens, _t3504);
                (void)next_tok;
                Bool _t3505; { Bool *_hp = (Bool *)TokenType_eq(&next_tok->type, TokenType_Eq()); _t3505 = *_hp; free(_hp); }
                (void)_t3505;
                U64_delete(_t3504, &(Bool){1});
                if (_t3505) {
                    U32 na_line = peek_line(p);
                    (void)na_line;
                    U32 na_col = peek_col(p);
                    (void)na_col;
                    Str *aname = expect_text(p, TokenType_Ident());
                    (void)aname;
                    Token *_t3497 = advance(p);
                    (void)_t3497;
                    ExprData *_t3498 = ExprData_NamedArg(aname);
                    (void)_t3498;
                    Str_delete(aname, &(Bool){1});
                    Expr *na = Expr_new(_t3498, na_line, na_col, &p->path);
                    (void)na;
                    ExprData_delete(_t3498, &(Bool){1});
                    ;
                    ;
                    Expr *_t3499 = parse_expression(p);
                    (void)_t3499;
                    Expr_add_child(na, _t3499);
                    Expr_add_child(call, na);
                    Bool _t3500 = check(p, TokenType_Comma());
                    (void)_t3500;
                    if (_t3500) {
                        Token *_t3496 = advance(p);
                        (void)_t3496;
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
        Bool _t3520 = check(p, TokenType_DotDot());
        (void)_t3520;
        if (_t3520) {
            Token *_t3510 = advance(p);
            (void)_t3510;
            Bool _t3511 = 1;
            (void)_t3511;
            is_splat = _t3511;
            ;
        }
        ;
        Bool is_own_arg = 0;
        (void)is_own_arg;
        Bool _t3521 = check(p, TokenType_KwOwn());
        (void)_t3521;
        if (_t3521) {
            Token *_t3512 = advance(p);
            (void)_t3512;
            Bool _t3513 = 1;
            (void)_t3513;
            is_own_arg = _t3513;
            ;
        }
        ;
        Expr *arg = parse_expression(p);
        (void)arg;
        Bool _t3522 = Bool_clone(&(Bool){is_own_arg});
        (void)_t3522;
        ;
        arg->is_own_arg = _t3522;
        ;
        Bool _t3523 = Bool_clone(&(Bool){is_splat});
        (void)_t3523;
        ;
        arg->is_splat = _t3523;
        ;
        Expr_add_child(call, arg);
        Bool _t3524 = check(p, TokenType_Comma());
        (void)_t3524;
        if (_t3524) {
            Token *_t3514 = advance(p);
            (void)_t3514;
        }
        ;
    }
    Token *_t3528 = expect_token(p, TokenType_RParen());
    (void)_t3528;
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
    U32 _t3716 = 0;
    (void)_t3716;
    U32 _t3717 = 0;
    (void)_t3717;
    Expr *e = Expr_new(ExprData_Body(), _t3716, _t3717, &p->path);
    (void)e;
    ;
    ;
    Bool e_set = 0;
    (void)e_set;
    Bool _t3718; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t3718 = *_hp; free(_hp); }
    (void)_t3718;
    if (_t3718) {
        Token *_t3529 = advance(p);
        (void)_t3529;
        Str *_t3530 = Str_clone(&t->text);
        (void)_t3530;
        ExprData *_t3531 = ExprData_LiteralStr(_t3530);
        (void)_t3531;
        Str_delete(_t3530, &(Bool){1});
        e = Expr_new(_t3531, t_line, t_col, &p->path);
        ExprData_delete(_t3531, &(Bool){1});
        Bool _t3532 = 1;
        (void)_t3532;
        e_set = _t3532;
        ;
    }
    ;
    Bool _t3719 = Bool_not(e_set);
    (void)_t3719;
    Bool _t3720; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t3720 = *_hp; free(_hp); }
    (void)_t3720;
    Bool _t3721 = Bool_and(_t3719, _t3720);
    (void)_t3721;
    ;
    ;
    if (_t3721) {
        Token *_t3533 = advance(p);
        (void)_t3533;
        Str *_t3534 = Str_clone(&t->text);
        (void)_t3534;
        ExprData *_t3535 = ExprData_LiteralNum(_t3534);
        (void)_t3535;
        Str_delete(_t3534, &(Bool){1});
        e = Expr_new(_t3535, t_line, t_col, &p->path);
        ExprData_delete(_t3535, &(Bool){1});
        Bool _t3536 = 1;
        (void)_t3536;
        e_set = _t3536;
        ;
    }
    ;
    Bool _t3722 = Bool_not(e_set);
    (void)_t3722;
    Bool _t3723; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Char()); _t3723 = *_hp; free(_hp); }
    (void)_t3723;
    Bool _t3724 = Bool_and(_t3722, _t3723);
    (void)_t3724;
    ;
    ;
    if (_t3724) {
        Token *_t3566 = advance(p);
        (void)_t3566;
        Str *ch = Str_clone(&t->text);
        (void)ch;
        I64 byte_val = 0;
        (void)byte_val;
        U64 _t3567; { U64 *_hp = (U64 *)Str_len(ch); _t3567 = *_hp; free(_hp); }
        (void)_t3567;
        U64 _t3568 = 0;
        (void)_t3568;
        U64 *_t3569 = malloc(sizeof(U64));
        *_t3569 = 0;
        (void)_t3569;
        U8 *_t3570 = Str_get(ch, _t3569);
        (void)_t3570;
        U8 _t3571 = 92;
        (void)_t3571;
        Bool _t3572; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3567}, &(U64){_t3568}); _t3572 = *_hp; free(_hp); }
        (void)_t3572;
        ;
        ;
        Bool _t3573 = U8_eq(DEREF(_t3570), _t3571);
        (void)_t3573;
        U64_delete(_t3569, &(Bool){1});
        ;
        Bool _t3574 = Bool_and(_t3572, _t3573);
        (void)_t3574;
        ;
        ;
        if (_t3574) {
            U64 _t3557; { U64 *_hp = (U64 *)Str_len(ch); _t3557 = *_hp; free(_hp); }
            (void)_t3557;
            U64 _t3558 = 1;
            (void)_t3558;
            Bool _t3559; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3557}, &(U64){_t3558}); _t3559 = *_hp; free(_hp); }
            (void)_t3559;
            ;
            ;
            if (_t3559) {
                U64 *_t3554 = malloc(sizeof(U64));
                *_t3554 = 1;
                (void)_t3554;
                U8 *c2 = Str_get(ch, _t3554);
                (void)c2;
                U8 _t3555 = 110;
                (void)_t3555;
                Bool _t3556 = U8_eq(DEREF(c2), _t3555);
                (void)_t3556;
                ;
                if (_t3556) {
                    I64 _t3537 = 10;
                    (void)_t3537;
                    byte_val = _t3537;
                    ;
                } else {
                    U8 _t3552 = 116;
                    (void)_t3552;
                    Bool _t3553 = U8_eq(DEREF(c2), _t3552);
                    (void)_t3553;
                    ;
                    if (_t3553) {
                        I64 _t3538 = 9;
                        (void)_t3538;
                        byte_val = _t3538;
                        ;
                    } else {
                        U8 _t3550 = 114;
                        (void)_t3550;
                        Bool _t3551 = U8_eq(DEREF(c2), _t3550);
                        (void)_t3551;
                        ;
                        if (_t3551) {
                            I64 _t3539 = 13;
                            (void)_t3539;
                            byte_val = _t3539;
                            ;
                        } else {
                            U8 _t3548 = 92;
                            (void)_t3548;
                            Bool _t3549 = U8_eq(DEREF(c2), _t3548);
                            (void)_t3549;
                            ;
                            if (_t3549) {
                                I64 _t3540 = 92;
                                (void)_t3540;
                                byte_val = _t3540;
                                ;
                            } else {
                                U8 _t3546 = 39;
                                (void)_t3546;
                                Bool _t3547 = U8_eq(DEREF(c2), _t3546);
                                (void)_t3547;
                                ;
                                if (_t3547) {
                                    I64 _t3541 = 39;
                                    (void)_t3541;
                                    byte_val = _t3541;
                                    ;
                                } else {
                                    U8 _t3544 = 48;
                                    (void)_t3544;
                                    Bool _t3545 = U8_eq(DEREF(c2), _t3544);
                                    (void)_t3545;
                                    ;
                                    if (_t3545) {
                                        I64 _t3542 = 0;
                                        (void)_t3542;
                                        byte_val = _t3542;
                                        ;
                                    } else {
                                        I64 _t3543 = U8_to_i64(DEREF(c2));
                                        (void)_t3543;
                                        byte_val = _t3543;
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
                U64_delete(_t3554, &(Bool){1});
                ;
            }
            ;
        } else {
            U64 _t3563; { U64 *_hp = (U64 *)Str_len(ch); _t3563 = *_hp; free(_hp); }
            (void)_t3563;
            U64 _t3564 = 0;
            (void)_t3564;
            Bool _t3565; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3563}, &(U64){_t3564}); _t3565 = *_hp; free(_hp); }
            (void)_t3565;
            ;
            ;
            if (_t3565) {
                U64 *_t3560 = malloc(sizeof(U64));
                *_t3560 = 0;
                (void)_t3560;
                U8 *_t3561 = Str_get(ch, _t3560);
                (void)_t3561;
                I64 _t3562 = U8_to_i64(DEREF(_t3561));
                (void)_t3562;
                U64_delete(_t3560, &(Bool){1});
                byte_val = _t3562;
                ;
            }
            ;
        }
        ;
        Str_delete(ch, &(Bool){1});
        Str *_t3575 = I64_to_str(&(I64){byte_val});
        (void)_t3575;
        ;
        ExprData *_t3576 = ExprData_LiteralNum(_t3575);
        (void)_t3576;
        Str_delete(_t3575, &(Bool){1});
        e = Expr_new(_t3576, t_line, t_col, &p->path);
        ExprData_delete(_t3576, &(Bool){1});
        TilType_delete(&e->til_type, &(Bool){0});
        { TilType *_fa = TilType_clone(TilType_U8()); e->til_type = *_fa; free(_fa); }
        Bool _t3577 = 1;
        (void)_t3577;
        e_set = _t3577;
        ;
    }
    ;
    Bool _t3725; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t3725 = *_hp; free(_hp); }
    (void)_t3725;
    Bool _t3726; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t3726 = *_hp; free(_hp); }
    (void)_t3726;
    Bool _t3727 = Bool_not(e_set);
    (void)_t3727;
    Bool _t3728 = Bool_or(_t3725, _t3726);
    (void)_t3728;
    ;
    ;
    Bool _t3729 = Bool_and(_t3727, _t3728);
    (void)_t3729;
    ;
    ;
    if (_t3729) {
        Token *_t3578 = advance(p);
        (void)_t3578;
        Str *_t3579 = Str_clone(&t->text);
        (void)_t3579;
        ExprData *_t3580 = ExprData_LiteralBool(_t3579);
        (void)_t3580;
        Str_delete(_t3579, &(Bool){1});
        e = Expr_new(_t3580, t_line, t_col, &p->path);
        ExprData_delete(_t3580, &(Bool){1});
        Bool _t3581 = 1;
        (void)_t3581;
        e_set = _t3581;
        ;
    }
    ;
    Bool _t3730 = Bool_not(e_set);
    (void)_t3730;
    Bool _t3731; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwNull()); _t3731 = *_hp; free(_hp); }
    (void)_t3731;
    Bool _t3732 = Bool_and(_t3730, _t3731);
    (void)_t3732;
    ;
    ;
    if (_t3732) {
        Token *_t3582 = advance(p);
        (void)_t3582;
        e = Expr_new(ExprData_LiteralNull(), t_line, t_col, &p->path);
        Bool _t3583 = 1;
        (void)_t3583;
        e_set = _t3583;
        ;
    }
    ;
    Bool _t3733 = Bool_not(e_set);
    (void)_t3733;
    Bool _t3734; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t3734 = *_hp; free(_hp); }
    (void)_t3734;
    Bool _t3735 = Bool_and(_t3733, _t3734);
    (void)_t3735;
    ;
    ;
    if (_t3735) {
        Token *_t3619 = advance(p);
        (void)_t3619;
        Str *name = Str_clone(&t->text);
        (void)name;
        Str *_t3620 = Str_lit("__LOC__", 7ULL);
        (void)_t3620;
        Bool _t3621; { Bool *_hp = (Bool *)Str_eq(name, _t3620); _t3621 = *_hp; free(_hp); }
        (void)_t3621;
        Str_delete(_t3620, &(Bool){1});
        if (_t3621) {
            Str *_t3584 = Str_lit("Str", 3ULL);
            (void)_t3584;
            U64 _t3585; { U64 *_hp = (U64 *)Str_size(); _t3585 = *_hp; free(_hp); }
            (void)_t3585;
            U64 _t3586 = 5;
            (void)_t3586;
            Array *_va67 = Array_new(_t3584, &(U64){_t3585}, &(U64){_t3586});
            (void)_va67;
            Str_delete(_t3584, &(Bool){1});
            ;
            ;
            U64 _t3587 = 0;
            (void)_t3587;
            Str *_t3588 = Str_clone(&p->path);
            (void)_t3588;
            Array_set(_va67, &(U64){_t3587}, _t3588);
            ;
            U64 _t3589 = 1;
            (void)_t3589;
            Str *_t3590 = Str_lit(":", 1ULL);
            (void)_t3590;
            Array_set(_va67, &(U64){_t3589}, _t3590);
            ;
            U64 _t3591 = 2;
            (void)_t3591;
            Str *_t3592 = U32_to_str(&(U32){t_line});
            (void)_t3592;
            Array_set(_va67, &(U64){_t3591}, _t3592);
            ;
            U64 _t3593 = 3;
            (void)_t3593;
            Str *_t3594 = Str_lit(":", 1ULL);
            (void)_t3594;
            Array_set(_va67, &(U64){_t3593}, _t3594);
            ;
            U64 _t3595 = 4;
            (void)_t3595;
            Str *_t3596 = U32_to_str(&(U32){t_col});
            (void)_t3596;
            Array_set(_va67, &(U64){_t3595}, _t3596);
            ;
            Str *_t3597 = format(_va67);
            (void)_t3597;
            ExprData *_t3598 = ExprData_LiteralStr(_t3597);
            (void)_t3598;
            Str_delete(_t3597, &(Bool){1});
            e = Expr_new(_t3598, t_line, t_col, &p->path);
            ExprData_delete(_t3598, &(Bool){1});
            Bool _t3599 = 1;
            (void)_t3599;
            e_set = _t3599;
            ;
        } else {
            Str *_t3617 = Str_lit("__FILE__", 8ULL);
            (void)_t3617;
            Bool _t3618; { Bool *_hp = (Bool *)Str_eq(name, _t3617); _t3618 = *_hp; free(_hp); }
            (void)_t3618;
            Str_delete(_t3617, &(Bool){1});
            if (_t3618) {
                Str *_t3600 = Str_clone(&p->path);
                (void)_t3600;
                ExprData *_t3601 = ExprData_LiteralStr(_t3600);
                (void)_t3601;
                Str_delete(_t3600, &(Bool){1});
                e = Expr_new(_t3601, t_line, t_col, &p->path);
                ExprData_delete(_t3601, &(Bool){1});
                Bool _t3602 = 1;
                (void)_t3602;
                e_set = _t3602;
                ;
            } else {
                Str *_t3615 = Str_lit("__LINE__", 8ULL);
                (void)_t3615;
                Bool _t3616; { Bool *_hp = (Bool *)Str_eq(name, _t3615); _t3616 = *_hp; free(_hp); }
                (void)_t3616;
                Str_delete(_t3615, &(Bool){1});
                if (_t3616) {
                    Str *_t3603 = U32_to_str(&(U32){t_line});
                    (void)_t3603;
                    ExprData *_t3604 = ExprData_LiteralNum(_t3603);
                    (void)_t3604;
                    Str_delete(_t3603, &(Bool){1});
                    e = Expr_new(_t3604, t_line, t_col, &p->path);
                    ExprData_delete(_t3604, &(Bool){1});
                    Bool _t3605 = 1;
                    (void)_t3605;
                    e_set = _t3605;
                    ;
                } else {
                    Str *_t3613 = Str_lit("__COL__", 7ULL);
                    (void)_t3613;
                    Bool _t3614; { Bool *_hp = (Bool *)Str_eq(name, _t3613); _t3614 = *_hp; free(_hp); }
                    (void)_t3614;
                    Str_delete(_t3613, &(Bool){1});
                    if (_t3614) {
                        Str *_t3606 = U32_to_str(&(U32){t_col});
                        (void)_t3606;
                        ExprData *_t3607 = ExprData_LiteralNum(_t3606);
                        (void)_t3607;
                        Str_delete(_t3606, &(Bool){1});
                        e = Expr_new(_t3607, t_line, t_col, &p->path);
                        ExprData_delete(_t3607, &(Bool){1});
                        Bool _t3608 = 1;
                        (void)_t3608;
                        e_set = _t3608;
                        ;
                    } else {
                        Bool _t3612 = check(p, TokenType_LParen());
                        (void)_t3612;
                        if (_t3612) {
                            e = parse_call(p, name, t_line, t_col);
                            Bool _t3609 = 1;
                            (void)_t3609;
                            e_set = _t3609;
                            ;
                        } else {
                            ExprData *_t3610 = ExprData_Ident(name);
                            (void)_t3610;
                            e = Expr_new(_t3610, t_line, t_col, &p->path);
                            ExprData_delete(_t3610, &(Bool){1});
                            Bool _t3611 = 1;
                            (void)_t3611;
                            e_set = _t3611;
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
    Bool _t3736; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFunc()); _t3736 = *_hp; free(_hp); }
    (void)_t3736;
    Bool _t3737; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwProc()); _t3737 = *_hp; free(_hp); }
    (void)_t3737;
    Bool _t3738 = Bool_or(_t3736, _t3737);
    (void)_t3738;
    ;
    ;
    Bool _t3739; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTest()); _t3739 = *_hp; free(_hp); }
    (void)_t3739;
    Bool _t3740 = Bool_or(_t3738, _t3739);
    (void)_t3740;
    ;
    ;
    Bool _t3741; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMacro()); _t3741 = *_hp; free(_hp); }
    (void)_t3741;
    Bool _t3742 = Bool_or(_t3740, _t3741);
    (void)_t3742;
    ;
    ;
    Bool _t3743; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtFunc()); _t3743 = *_hp; free(_hp); }
    (void)_t3743;
    Bool _t3744 = Bool_or(_t3742, _t3743);
    (void)_t3744;
    ;
    ;
    Bool _t3745; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtProc()); _t3745 = *_hp; free(_hp); }
    (void)_t3745;
    Bool _t3746 = Bool_not(e_set);
    (void)_t3746;
    Bool _t3747 = Bool_or(_t3744, _t3745);
    (void)_t3747;
    ;
    ;
    Bool _t3748 = Bool_and(_t3746, _t3747);
    (void)_t3748;
    ;
    ;
    if (_t3748) {
        Expr *_t3622 = parse_func_def(p);
        (void)_t3622;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3622;
    }
    ;
    Bool _t3749; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwStruct()); _t3749 = *_hp; free(_hp); }
    (void)_t3749;
    Bool _t3750; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtStruct()); _t3750 = *_hp; free(_hp); }
    (void)_t3750;
    Bool _t3751 = Bool_not(e_set);
    (void)_t3751;
    Bool _t3752 = Bool_or(_t3749, _t3750);
    (void)_t3752;
    ;
    ;
    Bool _t3753 = Bool_and(_t3751, _t3752);
    (void)_t3753;
    ;
    ;
    if (_t3753) {
        Expr *_t3623 = parse_struct_def(p);
        (void)_t3623;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3623;
    }
    ;
    Bool _t3754 = Bool_not(e_set);
    (void)_t3754;
    Bool _t3755; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwEnum()); _t3755 = *_hp; free(_hp); }
    (void)_t3755;
    Bool _t3756 = Bool_and(_t3754, _t3755);
    (void)_t3756;
    ;
    ;
    if (_t3756) {
        Expr *_t3624 = parse_enum_def(p);
        (void)_t3624;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3624;
    }
    ;
    Bool _t3757 = Bool_not(e_set);
    (void)_t3757;
    Bool _t3758; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t3758 = *_hp; free(_hp); }
    (void)_t3758;
    Bool _t3759 = Bool_and(_t3757, _t3758);
    (void)_t3759;
    ;
    ;
    if (_t3759) {
        Token *_t3649 = advance(p);
        (void)_t3649;
        Expr *first = parse_expression(p);
        (void)first;
        Bool _t3650 = check(p, TokenType_Colon());
        (void)_t3650;
        if (_t3650) {
            e = Expr_new(ExprData_MapLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Token *_t3636 = advance(p);
            (void)_t3636;
            Expr *_t3637 = parse_expression(p);
            (void)_t3637;
            Expr_add_child(e, _t3637);
            Bool _t3638 = check(p, TokenType_Comma());
            (void)_t3638;
            if (_t3638) {
                Token *_t3625 = advance(p);
                (void)_t3625;
            }
            ;
            while (1) {
                Bool _t3628 = check(p, TokenType_RBrace());
                (void)_t3628;
                Bool _t3629 = check(p, TokenType_Eof());
                (void)_t3629;
                Bool _t3630 = Bool_not(_t3628);
                (void)_t3630;
                ;
                Bool _t3631 = Bool_not(_t3629);
                (void)_t3631;
                ;
                Bool _wcond3626 = Bool_and(_t3630, _t3631);
                (void)_wcond3626;
                ;
                ;
                if (_wcond3626) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3632 = parse_expression(p);
                (void)_t3632;
                Expr_add_child(e, _t3632);
                Token *_t3633 = expect_token(p, TokenType_Colon());
                (void)_t3633;
                Expr *_t3634 = parse_expression(p);
                (void)_t3634;
                Expr_add_child(e, _t3634);
                Bool _t3635 = check(p, TokenType_Comma());
                (void)_t3635;
                if (_t3635) {
                    Token *_t3627 = advance(p);
                    (void)_t3627;
                }
                ;
            }
        } else {
            e = Expr_new(ExprData_SetLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Bool _t3648 = check(p, TokenType_Comma());
            (void)_t3648;
            if (_t3648) {
                Token *_t3639 = advance(p);
                (void)_t3639;
            }
            ;
            while (1) {
                Bool _t3642 = check(p, TokenType_RBrace());
                (void)_t3642;
                Bool _t3643 = check(p, TokenType_Eof());
                (void)_t3643;
                Bool _t3644 = Bool_not(_t3642);
                (void)_t3644;
                ;
                Bool _t3645 = Bool_not(_t3643);
                (void)_t3645;
                ;
                Bool _wcond3640 = Bool_and(_t3644, _t3645);
                (void)_wcond3640;
                ;
                ;
                if (_wcond3640) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3646 = parse_expression(p);
                (void)_t3646;
                Expr_add_child(e, _t3646);
                Bool _t3647 = check(p, TokenType_Comma());
                (void)_t3647;
                if (_t3647) {
                    Token *_t3641 = advance(p);
                    (void)_t3641;
                }
                ;
            }
        }
        ;
        Token *_t3651 = expect_token(p, TokenType_RBrace());
        (void)_t3651;
        Bool _t3652 = 1;
        (void)_t3652;
        e_set = _t3652;
        ;
    }
    ;
    Bool _t3760 = Bool_not(e_set);
    (void)_t3760;
    ;
    if (_t3760) {
        Str *_t3653 = Str_lit("Str", 3ULL);
        (void)_t3653;
        U64 _t3654; { U64 *_hp = (U64 *)Str_size(); _t3654 = *_hp; free(_hp); }
        (void)_t3654;
        U64 _t3655 = 8;
        (void)_t3655;
        Array *_va68 = Array_new(_t3653, &(U64){_t3654}, &(U64){_t3655});
        (void)_va68;
        Str_delete(_t3653, &(Bool){1});
        ;
        ;
        U64 _t3656 = 0;
        (void)_t3656;
        Str *_t3657 = Str_clone(&p->path);
        (void)_t3657;
        Array_set(_va68, &(U64){_t3656}, _t3657);
        ;
        U64 _t3658 = 1;
        (void)_t3658;
        Str *_t3659 = Str_lit(":", 1ULL);
        (void)_t3659;
        Array_set(_va68, &(U64){_t3658}, _t3659);
        ;
        U64 _t3660 = 2;
        (void)_t3660;
        Str *_t3661 = U32_to_str(&(U32){t_line});
        (void)_t3661;
        Array_set(_va68, &(U64){_t3660}, _t3661);
        ;
        U64 _t3662 = 3;
        (void)_t3662;
        Str *_t3663 = Str_lit(":", 1ULL);
        (void)_t3663;
        Array_set(_va68, &(U64){_t3662}, _t3663);
        ;
        U64 _t3664 = 4;
        (void)_t3664;
        Str *_t3665 = U32_to_str(&(U32){t_col});
        (void)_t3665;
        Array_set(_va68, &(U64){_t3664}, _t3665);
        ;
        U64 _t3666 = 5;
        (void)_t3666;
        Str *_t3667 = Str_lit(": unexpected token '", 20ULL);
        (void)_t3667;
        Array_set(_va68, &(U64){_t3666}, _t3667);
        ;
        U64 _t3668 = 6;
        (void)_t3668;
        Str *_t3669 = Str_clone(&t->text);
        (void)_t3669;
        Array_set(_va68, &(U64){_t3668}, _t3669);
        ;
        U64 _t3670 = 7;
        (void)_t3670;
        Str *_t3671 = Str_lit("'", 1ULL);
        (void)_t3671;
        Array_set(_va68, &(U64){_t3670}, _t3671);
        ;
        Str *_t3672 = Str_lit("src/self/parser.til:517:15", 26ULL);
        (void)_t3672;
        panic(_t3672, _va68);
        Str_delete(_t3672, &(Bool){1});
    }
    ;
    ;
    ;
    while (1) {
        Bool _wcond3673 = check(p, TokenType_Dot());
        (void)_wcond3673;
        if (_wcond3673) {
        } else {
            ;
            break;
        }
        ;
        Token *_t3706 = advance(p);
        (void)_t3706;
        U32 f_line = peek_line(p);
        (void)f_line;
        U32 f_col = peek_col(p);
        (void)f_col;
        Str *fname = expect_text(p, TokenType_Ident());
        (void)fname;
        Bool _t3707 = check(p, TokenType_LParen());
        (void)_t3707;
        if (_t3707) {
            Token *_t3700 = advance(p);
            (void)_t3700;
            ExprData *_t3701 = ExprData_FieldAccess(fname);
            (void)_t3701;
            Expr *callee = Expr_new(_t3701, f_line, f_col, &p->path);
            (void)callee;
            ExprData_delete(_t3701, &(Bool){1});
            Expr *_t3702 = Expr_clone(e);
            (void)_t3702;
            Expr_add_child(callee, _t3702);
            Expr *mcall = Expr_new(ExprData_FCall(), f_line, f_col, &p->path);
            (void)mcall;
            Expr_add_child(mcall, callee);
            while (1) {
                Bool _t3692 = check(p, TokenType_RParen());
                (void)_t3692;
                Bool _t3693 = check(p, TokenType_Eof());
                (void)_t3693;
                Bool _t3694 = Bool_not(_t3692);
                (void)_t3694;
                ;
                Bool _t3695 = Bool_not(_t3693);
                (void)_t3695;
                ;
                Bool _wcond3674 = Bool_and(_t3694, _t3695);
                (void)_wcond3674;
                ;
                ;
                if (_wcond3674) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3696 = check(p, TokenType_Ident());
                (void)_t3696;
                if (_t3696) {
                    U64 _t3685 = 1;
                    (void)_t3685;
                    U64 _t3686 = U64_add(p->pos, _t3685);
                    (void)_t3686;
                    ;
                    U64 _t3687; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3687 = *_hp; free(_hp); }
                    (void)_t3687;
                    Bool _t3688; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3686}, &(U64){_t3687}); _t3688 = *_hp; free(_hp); }
                    (void)_t3688;
                    ;
                    ;
                    if (_t3688) {
                        U64 _t3680 = 1;
                        (void)_t3680;
                        U64 _t3681 = U64_add(p->pos, _t3680);
                        (void)_t3681;
                        ;
                        I64 _t3682 = U64_to_i64(_t3681);
                        (void)_t3682;
                        ;
                        U64 *_t3683 = malloc(sizeof(U64)); *_t3683 = I64_to_u64(_t3682);
                        (void)_t3683;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3683);
                        (void)nt;
                        Bool _t3684; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3684 = *_hp; free(_hp); }
                        (void)_t3684;
                        U64_delete(_t3683, &(Bool){1});
                        if (_t3684) {
                            U32 na_line = peek_line(p);
                            (void)na_line;
                            U32 na_col = peek_col(p);
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3676 = advance(p);
                            (void)_t3676;
                            ExprData *_t3677 = ExprData_NamedArg(aname);
                            (void)_t3677;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3677, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3677, &(Bool){1});
                            ;
                            ;
                            Expr *_t3678 = parse_expression(p);
                            (void)_t3678;
                            Expr_add_child(na, _t3678);
                            Expr_add_child(mcall, na);
                            Bool _t3679 = check(p, TokenType_Comma());
                            (void)_t3679;
                            if (_t3679) {
                                Token *_t3675 = advance(p);
                                (void)_t3675;
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
                Bool _t3697 = check(p, TokenType_KwOwn());
                (void)_t3697;
                if (_t3697) {
                    Token *_t3689 = advance(p);
                    (void)_t3689;
                    Bool _t3690 = 1;
                    (void)_t3690;
                    is_own_arg = _t3690;
                    ;
                }
                ;
                Expr *marg = parse_expression(p);
                (void)marg;
                Bool _t3698 = Bool_clone(&(Bool){is_own_arg});
                (void)_t3698;
                ;
                marg->is_own_arg = _t3698;
                ;
                Expr_add_child(mcall, marg);
                Bool _t3699 = check(p, TokenType_Comma());
                (void)_t3699;
                if (_t3699) {
                    Token *_t3691 = advance(p);
                    (void)_t3691;
                }
                ;
            }
            Token *_t3703 = expect_token(p, TokenType_RParen());
            (void)_t3703;
            e = Expr_clone(mcall);
            Expr_delete(mcall, &(Bool){1});
        } else {
            ExprData *_t3704 = ExprData_FieldAccess(fname);
            (void)_t3704;
            Expr *access = Expr_new(_t3704, f_line, f_col, &p->path);
            (void)access;
            ExprData_delete(_t3704, &(Bool){1});
            Expr *_t3705 = Expr_clone(e);
            (void)_t3705;
            Expr_add_child(access, _t3705);
            e = Expr_clone(access);
            Expr_delete(access, &(Bool){1});
        }
        ;
        ;
        ;
        Str_delete(fname, &(Bool){1});
    }
    Bool _t3761 = check(p, TokenType_DotDot());
    (void)_t3761;
    if (_t3761) {
        U32 dt_line = peek_line(p);
        (void)dt_line;
        U32 dt_col = peek_col(p);
        (void)dt_col;
        Token *_t3708 = advance(p);
        (void)_t3708;
        Expr *rhs = parse_expression(p);
        (void)rhs;
        Str *_t3709 = Str_lit("Range", 5ULL);
        (void)_t3709;
        Str *_t3710 = Str_clone(_t3709);
        (void)_t3710;
        Str_delete(_t3709, &(Bool){1});
        ExprData *_t3711 = ExprData_Ident(_t3710);
        (void)_t3711;
        Str_delete(_t3710, &(Bool){1});
        Expr *range_ident = Expr_new(_t3711, dt_line, dt_col, &p->path);
        (void)range_ident;
        ExprData_delete(_t3711, &(Bool){1});
        Str *_t3712 = Str_lit("new", 3ULL);
        (void)_t3712;
        Str *_t3713 = Str_clone(_t3712);
        (void)_t3713;
        Str_delete(_t3712, &(Bool){1});
        ExprData *_t3714 = ExprData_FieldAccess(_t3713);
        (void)_t3714;
        Str_delete(_t3713, &(Bool){1});
        Expr *new_access = Expr_new(_t3714, dt_line, dt_col, &p->path);
        (void)new_access;
        ExprData_delete(_t3714, &(Bool){1});
        Expr_add_child(new_access, range_ident);
        Expr *rcall = Expr_new(ExprData_FCall(), dt_line, dt_col, &p->path);
        (void)rcall;
        ;
        ;
        Expr_add_child(rcall, new_access);
        Expr *_t3715 = Expr_clone(e);
        (void)_t3715;
        Expr_add_child(rcall, _t3715);
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
        Token *_t3762 = advance(p);
        (void)_t3762;
        Bool _t3763 = Bool_clone(&(Bool){is_mut});
        (void)_t3763;
        Bool _t3764 = 0;
        (void)_t3764;
        Bool _t3765 = 0;
        (void)_t3765;
        Bool _t3766 = Bool_clone(&(Bool){is_own});
        (void)_t3766;
        I32 _t3767 = 0;
        (void)_t3767;
        I32 _t3768 = 0;
        (void)_t3768;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3763;
        dd->is_namespace = _t3764;
        dd->is_ref = _t3765;
        dd->is_own = _t3766;
        dd->field_offset = _t3767;
        dd->field_size = _t3768;
        dd->field_struct_def = NULL;
        dd->fn_sig = NULL;
        (void)dd;
        ;
        ;
        ;
        ;
        ;
        ;
        ExprData *_t3769 = ExprData_Decl(dd);
        (void)_t3769;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3769, t_line, t_col, &p->path);
        (void)decl;
        ExprData_delete(_t3769, &(Bool){1});
        Expr *_t3770 = parse_expression(p);
        (void)_t3770;
        Expr_add_child(decl, _t3770);
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
            Token *_t3788 = expect_token(p, TokenType_Eq());
            (void)_t3788;
            Token *_t3789 = expect_token(p, TokenType_LParen());
            (void)_t3789;
            Bool _t3790; { Bool *_hp = (Bool *)ExprData_is_FuncDef(&sig->data); _t3790 = *_hp; free(_hp); }
            (void)_t3790;
            if (_t3790) {
                FunctionDef *sfd = ExprData_get_FuncDef(&sig->data);
                (void)sfd;
                Str *_t3785 = Str_lit("Str", 3ULL);
                (void)_t3785;
                U64 _t3786; { U64 *_hp = (U64 *)Str_size(); _t3786 = *_hp; free(_hp); }
                (void)_t3786;
                Vec *new_names = Vec_new(_t3785, &(U64){_t3786});
                (void)new_names;
                Str_delete(_t3785, &(Bool){1});
                ;
                {
                    U64 _fi3771 = 0;
                    (void)_fi3771;
                    while (1) {
                        U64 _t3774 = 0;
                        (void)_t3774;
                        U64 _t3775; { U64 *_hp = (U64 *)Vec_len(&sfd->param_names); _t3775 = *_hp; free(_hp); }
                        (void)_t3775;
                        Range *_t3776 = Range_new(_t3774, _t3775);
                        (void)_t3776;
                        ;
                        ;
                        U64 _t3777; { U64 *_hp = (U64 *)Range_len(_t3776); _t3777 = *_hp; free(_hp); }
                        (void)_t3777;
                        Range_delete(_t3776, &(Bool){1});
                        Bool _wcond3772; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3771}, &(U64){_t3777}); _wcond3772 = *_hp; free(_hp); }
                        (void)_wcond3772;
                        ;
                        if (_wcond3772) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 _t3778 = 0;
                        (void)_t3778;
                        U64 _t3779; { U64 *_hp = (U64 *)Vec_len(&sfd->param_names); _t3779 = *_hp; free(_hp); }
                        (void)_t3779;
                        Range *_t3780 = Range_new(_t3778, _t3779);
                        (void)_t3780;
                        ;
                        ;
                        U64 pi; { U64 *_hp = (U64 *)Range_get(_t3780, _fi3771); pi = *_hp; free(_hp); }
                        (void)pi;
                        Range_delete(_t3780, &(Bool){1});
                        U64 _t3781 = 1;
                        (void)_t3781;
                        U64 _t3782 = U64_add(_fi3771, _t3781);
                        (void)_t3782;
                        ;
                        _fi3771 = _t3782;
                        ;
                        U64 _t3783 = 0;
                        (void)_t3783;
                        Bool _t3784; { Bool *_hp = (Bool *)U64_gt(&(U64){pi}, &(U64){_t3783}); _t3784 = *_hp; free(_hp); }
                        (void)_t3784;
                        ;
                        ;
                        if (_t3784) {
                            Token *_t3773 = expect_token(p, TokenType_Comma());
                            (void)_t3773;
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
            Bool _t3791 = check(p, TokenType_Comma());
            (void)_t3791;
            if (_t3791) {
                Token *_t3787 = advance(p);
                (void)_t3787;
            }
            ;
            Token *_t3792 = expect_token(p, TokenType_RParen());
            (void)_t3792;
            Token *_t3793 = expect_token(p, TokenType_LBrace());
            (void)_t3793;
            Expr *_t3794 = parse_block(p);
            (void)_t3794;
            Expr_add_child(sig, _t3794);
            Bool _t3795 = Bool_clone(&(Bool){is_mut});
            (void)_t3795;
            Bool _t3796 = 0;
            (void)_t3796;
            Bool _t3797 = 0;
            (void)_t3797;
            Bool _t3798 = Bool_clone(&(Bool){is_own});
            (void)_t3798;
            I32 _t3799 = 0;
            (void)_t3799;
            I32 _t3800 = 0;
            (void)_t3800;
            Declaration *dd = malloc(sizeof(Declaration));
            { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
            dd->is_mut = _t3795;
            dd->is_namespace = _t3796;
            dd->is_ref = _t3797;
            dd->is_own = _t3798;
            dd->field_offset = _t3799;
            dd->field_size = _t3800;
            dd->field_struct_def = NULL;
            dd->fn_sig = NULL;
            (void)dd;
            ;
            ;
            ;
            ;
            ;
            ;
            ExprData *_t3801 = ExprData_Decl(dd);
            (void)_t3801;
            Declaration_delete(dd, &(Bool){1});
            Expr *decl = Expr_new(_t3801, t_line, t_col, &p->path);
            (void)decl;
            ExprData_delete(_t3801, &(Bool){1});
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
            U32 _t3803 = 0;
            (void)_t3803;
            Bool _t3804; { Bool *_hp = (Bool *)U32_neq(&sig->line, &(U32){_t3803}); _t3804 = *_hp; free(_hp); }
            (void)_t3804;
            ;
            Expr_delete(sig, &(Bool){1});
            if (_t3804) {
                I64 _t3802 = 0;
                (void)_t3802;
                fn_sig_idx = _t3802;
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
                Bool _t3808 = check(p, TokenType_RParen());
                (void)_t3808;
                Bool _t3809 = check(p, TokenType_Eof());
                (void)_t3809;
                Bool _t3810 = Bool_not(_t3808);
                (void)_t3810;
                ;
                Bool _t3811 = Bool_not(_t3809);
                (void)_t3811;
                ;
                Bool _wcond3805 = Bool_and(_t3810, _t3811);
                (void)_wcond3805;
                ;
                ;
                if (_wcond3805) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3812 = check(p, TokenType_Ident());
                (void)_t3812;
                Bool _t3813 = Bool_not(_t3812);
                (void)_t3813;
                ;
                if (_t3813) {
                    Bool _t3806 = 0;
                    (void)_t3806;
                    is_fsf = _t3806;
                    ;
                    ;
                    break;
                }
                ;
                Token *_t3814 = advance(p);
                (void)_t3814;
                Bool _t3815 = check(p, TokenType_Comma());
                (void)_t3815;
                if (_t3815) {
                    Token *_t3807 = advance(p);
                    (void)_t3807;
                }
                ;
            }
            Bool _t3892 = check(p, TokenType_RParen());
            (void)_t3892;
            Bool _t3893 = Bool_and(is_fsf, _t3892);
            (void)_t3893;
            ;
            if (_t3893) {
                Token *_t3817 = advance(p);
                (void)_t3817;
                Bool _t3818 = check(p, TokenType_LBrace());
                (void)_t3818;
                Bool _t3819 = Bool_not(_t3818);
                (void)_t3819;
                ;
                if (_t3819) {
                    Bool _t3816 = 0;
                    (void)_t3816;
                    is_fsf = _t3816;
                    ;
                }
                ;
            } else {
                Bool _t3820 = 0;
                (void)_t3820;
                is_fsf = _t3820;
                ;
            }
            ;
            U64 _t3894 = U64_clone(&(U64){saved});
            (void)_t3894;
            ;
            p->pos = _t3894;
            ;
            if (is_fsf) {
                Token *_t3841 = expect_token(p, TokenType_LParen());
                (void)_t3841;
                Str *_t3842 = Str_lit("Str", 3ULL);
                (void)_t3842;
                U64 _t3843; { U64 *_hp = (U64 *)Str_size(); _t3843 = *_hp; free(_hp); }
                (void)_t3843;
                Vec *pnames = Vec_new(_t3842, &(U64){_t3843});
                (void)pnames;
                Str_delete(_t3842, &(Bool){1});
                ;
                while (1) {
                    Bool _t3823 = check(p, TokenType_RParen());
                    (void)_t3823;
                    Bool _wcond3821 = Bool_not(_t3823);
                    (void)_wcond3821;
                    ;
                    if (_wcond3821) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *pn = expect_text(p, TokenType_Ident());
                    (void)pn;
                    Vec_push(pnames, pn);
                    Bool _t3824 = check(p, TokenType_Comma());
                    (void)_t3824;
                    if (_t3824) {
                        Token *_t3822 = advance(p);
                        (void)_t3822;
                    }
                    ;
                }
                Token *_t3844 = expect_token(p, TokenType_RParen());
                (void)_t3844;
                Token *_t3845 = expect_token(p, TokenType_LBrace());
                (void)_t3845;
                Expr *body = parse_block(p);
                (void)body;
                Str *_t3846 = Str_lit("Str", 3ULL);
                (void)_t3846;
                U64 _t3847; { U64 *_hp = (U64 *)Str_size(); _t3847 = *_hp; free(_hp); }
                (void)_t3847;
                Str *_t3848 = Str_lit("Str", 3ULL);
                (void)_t3848;
                U64 _t3849; { U64 *_hp = (U64 *)Str_size(); _t3849 = *_hp; free(_hp); }
                (void)_t3849;
                Str *_t3850 = Str_lit("Bool", 4ULL);
                (void)_t3850;
                U64 _t3851; { U64 *_hp = (U64 *)Bool_size(); _t3851 = *_hp; free(_hp); }
                (void)_t3851;
                Str *_t3852 = Str_lit("Bool", 4ULL);
                (void)_t3852;
                U64 _t3853; { U64 *_hp = (U64 *)Bool_size(); _t3853 = *_hp; free(_hp); }
                (void)_t3853;
                Str *_t3854 = Str_lit("Bool", 4ULL);
                (void)_t3854;
                U64 _t3855; { U64 *_hp = (U64 *)Bool_size(); _t3855 = *_hp; free(_hp); }
                (void)_t3855;
                Str *_t3856 = Str_lit("I64", 3ULL);
                (void)_t3856;
                U64 _t3857; { U64 *_hp = (U64 *)I64_size(); _t3857 = *_hp; free(_hp); }
                (void)_t3857;
                Str *_t3858 = Str_lit("Str", 3ULL);
                (void)_t3858;
                U64 _t3859; { U64 *_hp = (U64 *)Str_size(); _t3859 = *_hp; free(_hp); }
                (void)_t3859;
                Str *_t3860 = Str_lit("Expr", 4ULL);
                (void)_t3860;
                U64 _t3861; { U64 *_hp = (U64 *)Expr_size(); _t3861 = *_hp; free(_hp); }
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
                { Vec *_ca = Vec_new(_t3846, &(U64){_t3847}); ffd->param_names = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3848, &(U64){_t3849}); ffd->param_types = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3850, &(U64){_t3851}); ffd->param_muts = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3852, &(U64){_t3853}); ffd->param_owns = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3854, &(U64){_t3855}); ffd->param_shallows = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3856, &(U64){_t3857}); ffd->param_fn_sigs = *_ca; free(_ca); }
                ffd->nparam = _t3868;
                { Map *_ca = Map_new(_t3858, &(U64){_t3859}, _t3860, &(U64){_t3861}); ffd->param_defaults = *_ca; free(_ca); }
                { Str *_ca = Str_clone(Str_lit("", 0ULL)); ffd->return_type = *_ca; free(_ca); }
                ffd->variadic_index = _t3869;
                ffd->kwargs_index = _t3870;
                ffd->return_is_ref = _t3871;
                ffd->return_is_shallow = _t3872;
                (void)ffd;
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
                    U64 _fi3825 = 0;
                    (void)_fi3825;
                    while (1) {
                        U64 _t3827 = 0;
                        (void)_t3827;
                        Range *_t3828 = Range_new(_t3827, np);
                        (void)_t3828;
                        ;
                        U64 _t3829; { U64 *_hp = (U64 *)Range_len(_t3828); _t3829 = *_hp; free(_hp); }
                        (void)_t3829;
                        Range_delete(_t3828, &(Bool){1});
                        Bool _wcond3826; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3825}, &(U64){_t3829}); _wcond3826 = *_hp; free(_hp); }
                        (void)_wcond3826;
                        ;
                        if (_wcond3826) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 _t3830 = 0;
                        (void)_t3830;
                        Range *_t3831 = Range_new(_t3830, np);
                        (void)_t3831;
                        ;
                        U64 _; { U64 *_hp = (U64 *)Range_get(_t3831, _fi3825); _ = *_hp; free(_hp); }
                        (void)_;
                        ;
                        Range_delete(_t3831, &(Bool){1});
                        U64 _t3832 = 1;
                        (void)_t3832;
                        U64 _t3833 = U64_add(_fi3825, _t3832);
                        (void)_t3833;
                        ;
                        _fi3825 = _t3833;
                        ;
                        Str *_t3834 = Str_lit("", 0ULL);
                        (void)_t3834;
                        Vec_push(&ffd->param_types, _t3834);
                        Bool _t3835 = 0;
                        (void)_t3835;
                        Vec_push(&ffd->param_muts, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3835; _oa; }));
                        Bool _t3836 = 0;
                        (void)_t3836;
                        Vec_push(&ffd->param_owns, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3836; _oa; }));
                        Bool _t3837 = 0;
                        (void)_t3837;
                        Vec_push(&ffd->param_shallows, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3837; _oa; }));
                        I64 _t3838 = 0;
                        (void)_t3838;
                        I64 _t3839 = 1;
                        (void)_t3839;
                        I64 _t3840 = I64_sub(_t3838, _t3839);
                        (void)_t3840;
                        ;
                        ;
                        Vec_push(&ffd->param_fn_sigs, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = _t3840; _oa; }));
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
    Str *_t3987 = Str_lit("src/self/parser.til:785:11", 26ULL);
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
                Str *_t4106 = Str_lit("src/self/parser.til:919:23", 26ULL);
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
    Str *_t4168 = Str_lit("src/self/parser.til:946:11", 26ULL);
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

