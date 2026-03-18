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
    Token *_t3406 = expect_token(p, TokenType_LParen());
    (void)_t3406;
    Str *_t3407 = Str_lit("Str", 3ULL);
    (void)_t3407;
    U64 _t3408; { U64 *_hp = (U64 *)Str_size(); _t3408 = *_hp; free(_hp); }
    (void)_t3408;
    Str *_t3409 = Str_lit("Str", 3ULL);
    (void)_t3409;
    U64 _t3410; { U64 *_hp = (U64 *)Str_size(); _t3410 = *_hp; free(_hp); }
    (void)_t3410;
    Str *_t3411 = Str_lit("Bool", 4ULL);
    (void)_t3411;
    U64 _t3412; { U64 *_hp = (U64 *)Bool_size(); _t3412 = *_hp; free(_hp); }
    (void)_t3412;
    Str *_t3413 = Str_lit("Bool", 4ULL);
    (void)_t3413;
    U64 _t3414; { U64 *_hp = (U64 *)Bool_size(); _t3414 = *_hp; free(_hp); }
    (void)_t3414;
    Str *_t3415 = Str_lit("Bool", 4ULL);
    (void)_t3415;
    U64 _t3416; { U64 *_hp = (U64 *)Bool_size(); _t3416 = *_hp; free(_hp); }
    (void)_t3416;
    Str *_t3417 = Str_lit("I64", 3ULL);
    (void)_t3417;
    U64 _t3418; { U64 *_hp = (U64 *)I64_size(); _t3418 = *_hp; free(_hp); }
    (void)_t3418;
    Str *_t3419 = Str_lit("Str", 3ULL);
    (void)_t3419;
    U64 _t3420; { U64 *_hp = (U64 *)Str_size(); _t3420 = *_hp; free(_hp); }
    (void)_t3420;
    Str *_t3421 = Str_lit("Expr", 4ULL);
    (void)_t3421;
    U64 _t3422; { U64 *_hp = (U64 *)Expr_size(); _t3422 = *_hp; free(_hp); }
    (void)_t3422;
    I64 _t3423 = 0;
    (void)_t3423;
    I64 _t3424 = 1;
    (void)_t3424;
    I64 _t3425 = I64_sub(_t3423, _t3424);
    (void)_t3425;
    ;
    ;
    I64 _t3426 = 0;
    (void)_t3426;
    I64 _t3427 = 1;
    (void)_t3427;
    I64 _t3428 = I64_sub(_t3426, _t3427);
    (void)_t3428;
    ;
    ;
    U32 _t3429 = 0;
    (void)_t3429;
    I32 _t3430 = I64_to_i32(_t3425);
    (void)_t3430;
    ;
    I32 _t3431 = I64_to_i32(_t3428);
    (void)_t3431;
    ;
    Bool _t3432 = 0;
    (void)_t3432;
    Bool _t3433 = 0;
    (void)_t3433;
    FunctionDef *fd = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(FuncType_Func()); fd->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3407, &(U64){_t3408}); fd->param_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3409, &(U64){_t3410}); fd->param_types = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3411, &(U64){_t3412}); fd->param_muts = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3413, &(U64){_t3414}); fd->param_owns = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3415, &(U64){_t3416}); fd->param_shallows = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3417, &(U64){_t3418}); fd->param_fn_sigs = *_ca; free(_ca); }
    fd->nparam = _t3429;
    { Map *_ca = Map_new(_t3419, &(U64){_t3420}, _t3421, &(U64){_t3422}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3430;
    fd->kwargs_index = _t3431;
    fd->return_is_ref = _t3432;
    fd->return_is_shallow = _t3433;
    (void)fd;
    Str_delete(_t3407, &(Bool){1});
    ;
    Str_delete(_t3409, &(Bool){1});
    ;
    Str_delete(_t3411, &(Bool){1});
    ;
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
    ;
    ;
    ;
    ;
    ;
    FuncType_delete(&fd->func_type, &(Bool){0});
    { FuncType *_fa = FuncType_clone(ft); fd->func_type = *_fa; free(_fa); }
    Str *_t3434 = Str_lit("Expr", 4ULL);
    (void)_t3434;
    U64 _t3435; { U64 *_hp = (U64 *)Expr_size(); _t3435 = *_hp; free(_hp); }
    (void)_t3435;
    Vec *def_exprs = Vec_new(_t3434, &(U64){_t3435});
    (void)def_exprs;
    Str_delete(_t3434, &(Bool){1});
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
        Bool has_default = 0;
        (void)has_default;
        Bool _t3349 = check(p, TokenType_Eq());
        (void)_t3349;
        if (_t3349) {
            Token *_t3326 = advance(p);
            (void)_t3326;
            Expr *def_expr = parse_expression(p);
            (void)def_expr;
            Str *_t3327 = Str_clone(nm);
            (void)_t3327;
            Map_set(&fd->param_defaults, _t3327, def_expr);
            Bool _t3328 = 1;
            (void)_t3328;
            has_default = _t3328;
            ;
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
        Bool _t3356 = Bool_and(_t3354, _t3355);
        (void)_t3356;
        ;
        ;
        Bool _t3357 = Bool_not(has_default);
        (void)_t3357;
        ;
        Bool _t3358 = Bool_and(_t3356, _t3357);
        (void)_t3358;
        ;
        ;
        if (_t3358) {
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
            Str *_t3334 = Str_lit("src/self/parser.til:217:19", 26ULL);
            (void)_t3334;
            panic(_t3334, _va65);
            Str_delete(_t3334, &(Bool){1});
        }
        ;
        Vec_push(&fd->param_names, nm);
        Vec_push(&fd->param_types, tp);
        Vec_push(&fd->param_muts, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = is_mut; _oa; }));
        Vec_push(&fd->param_owns, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = is_own; _oa; }));
        Vec_push(&fd->param_shallows, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = is_shallow; _oa; }));
        Vec_push(&fd->param_fn_sigs, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = fn_sig_idx; _oa; }));
        Bool _t3359 = check(p, TokenType_Comma());
        (void)_t3359;
        if (_t3359) {
            Token *_t3335 = advance(p);
            (void)_t3335;
        }
        ;
    }
    Token *_t3436 = expect_token(p, TokenType_RParen());
    (void)_t3436;
    Bool _t3437 = check(p, TokenType_KwReturns());
    (void)_t3437;
    if (_t3437) {
        Token *_t3365 = advance(p);
        (void)_t3365;
        Bool _t3366 = check(p, TokenType_KwRef());
        (void)_t3366;
        if (_t3366) {
            Token *_t3360 = advance(p);
            (void)_t3360;
            Bool _t3361 = 1;
            (void)_t3361;
            fd->return_is_ref = _t3361;
            ;
        } else {
            Bool _t3364 = check(p, TokenType_KwShallow());
            (void)_t3364;
            if (_t3364) {
                Token *_t3362 = advance(p);
                (void)_t3362;
                Bool _t3363 = 1;
                (void)_t3363;
                fd->return_is_shallow = _t3363;
                ;
            }
            ;
        }
        ;
        Str_delete(&fd->return_type, &(Bool){0});
        { Str *_fa = expect_text(p, TokenType_Ident()); fd->return_type = *_fa; free(_fa); }
    }
    ;
    U64 _t3438; { U64 *_hp = (U64 *)Vec_len(&fd->param_names); _t3438 = *_hp; free(_hp); }
    (void)_t3438;
    I64 _t3439 = U64_to_i64(_t3438);
    (void)_t3439;
    ;
    U32 _t3440 = I64_to_u32(_t3439);
    (void)_t3440;
    ;
    fd->nparam = _t3440;
    ;
    ExprData *_t3441 = ExprData_FuncDef(fd);
    (void)_t3441;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *def = Expr_new(_t3441, kw_line, kw_col, &p->path);
    (void)def;
    ExprData_delete(_t3441, &(Bool){1});
    Bool _t3442 = check(p, TokenType_LBrace());
    (void)_t3442;
    if (_t3442) {
        Token *_t3367 = expect_token(p, TokenType_LBrace());
        (void)_t3367;
        Expr *_t3368 = parse_block(p);
        (void)_t3368;
        Expr_add_child(def, _t3368);
    } else {
        Bool _t3389; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Func()); _t3389 = *_hp; free(_hp); }
        (void)_t3389;
        Bool _t3390; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Proc()); _t3390 = *_hp; free(_hp); }
        (void)_t3390;
        Bool _t3391 = Bool_not(_t3389);
        (void)_t3391;
        ;
        Bool _t3392 = Bool_not(_t3390);
        (void)_t3392;
        ;
        Bool _t3393 = Bool_and(_t3391, _t3392);
        (void)_t3393;
        ;
        ;
        if (_t3393) {
            Str *_t3369 = Str_lit("Str", 3ULL);
            (void)_t3369;
            U64 _t3370; { U64 *_hp = (U64 *)Str_size(); _t3370 = *_hp; free(_hp); }
            (void)_t3370;
            U64 _t3371 = 8;
            (void)_t3371;
            Array *_va66 = Array_new(_t3369, &(U64){_t3370}, &(U64){_t3371});
            (void)_va66;
            Str_delete(_t3369, &(Bool){1});
            ;
            ;
            U64 _t3372 = 0;
            (void)_t3372;
            Str *_t3373 = Str_clone(&p->path);
            (void)_t3373;
            Array_set(_va66, &(U64){_t3372}, _t3373);
            ;
            U64 _t3374 = 1;
            (void)_t3374;
            Str *_t3375 = Str_lit(":", 1ULL);
            (void)_t3375;
            Array_set(_va66, &(U64){_t3374}, _t3375);
            ;
            U64 _t3376 = 2;
            (void)_t3376;
            Str *_t3377 = U32_to_str(&(U32){kw_line});
            (void)_t3377;
            Array_set(_va66, &(U64){_t3376}, _t3377);
            ;
            U64 _t3378 = 3;
            (void)_t3378;
            Str *_t3379 = Str_lit(":", 1ULL);
            (void)_t3379;
            Array_set(_va66, &(U64){_t3378}, _t3379);
            ;
            U64 _t3380 = 4;
            (void)_t3380;
            Str *_t3381 = U32_to_str(&(U32){kw_col});
            (void)_t3381;
            Array_set(_va66, &(U64){_t3380}, _t3381);
            ;
            U64 _t3382 = 5;
            (void)_t3382;
            Str *_t3383 = Str_lit(": ", 2ULL);
            (void)_t3383;
            Array_set(_va66, &(U64){_t3382}, _t3383);
            ;
            U64 _t3384 = 6;
            (void)_t3384;
            Str *_t3385 = func_type_name(ft);
            (void)_t3385;
            Array_set(_va66, &(U64){_t3384}, _t3385);
            ;
            U64 _t3386 = 7;
            (void)_t3386;
            Str *_t3387 = Str_lit(" requires a body", 16ULL);
            (void)_t3387;
            Array_set(_va66, &(U64){_t3386}, _t3387);
            ;
            Str *_t3388 = Str_lit("src/self/parser.til:252:19", 26ULL);
            (void)_t3388;
            panic(_t3388, _va66);
            Str_delete(_t3388, &(Bool){1});
        }
        ;
    }
    ;
    FuncType_delete(ft, &(Bool){1});
    ;
    ;
    {
        U64 _fi3394 = 0;
        (void)_fi3394;
        while (1) {
            U64 _t3396 = 0;
            (void)_t3396;
            U64 _t3397; { U64 *_hp = (U64 *)Vec_len(def_exprs); _t3397 = *_hp; free(_hp); }
            (void)_t3397;
            Range *_t3398 = Range_new(_t3396, _t3397);
            (void)_t3398;
            ;
            ;
            U64 _t3399; { U64 *_hp = (U64 *)Range_len(_t3398); _t3399 = *_hp; free(_hp); }
            (void)_t3399;
            Range_delete(_t3398, &(Bool){1});
            Bool _wcond3395; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3394}, &(U64){_t3399}); _wcond3395 = *_hp; free(_hp); }
            (void)_wcond3395;
            ;
            if (_wcond3395) {
            } else {
                ;
                break;
            }
            ;
            U64 _t3400 = 0;
            (void)_t3400;
            U64 _t3401; { U64 *_hp = (U64 *)Vec_len(def_exprs); _t3401 = *_hp; free(_hp); }
            (void)_t3401;
            Range *_t3402 = Range_new(_t3400, _t3401);
            (void)_t3402;
            ;
            ;
            U64 *i = Range_get(_t3402, _fi3394);
            (void)i;
            Range_delete(_t3402, &(Bool){1});
            U64 _t3403 = 1;
            (void)_t3403;
            U64 _t3404 = U64_add(_fi3394, _t3403);
            (void)_t3404;
            ;
            _fi3394 = _t3404;
            ;
            Expr *de = Vec_get(def_exprs, i);
            (void)de;
            Expr *_t3405 = Expr_clone(de);
            (void)_t3405;
            U64_delete(i, &(Bool){1});
            Expr_add_child(def, _t3405);
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
    Token *_t3456 = advance(p);
    (void)_t3456;
    Expr *def = Expr_new(ExprData_StructDef(), kw_line, kw_col, &p->path);
    (void)def;
    ;
    ;
    Bool _t3457 = Bool_clone(&(Bool){is_ext});
    (void)_t3457;
    ;
    def->is_ext = _t3457;
    ;
    Token *_t3458 = expect_token(p, TokenType_LBrace());
    (void)_t3458;
    U32 _t3459 = peek_line(p);
    (void)_t3459;
    U32 _t3460 = peek_col(p);
    (void)_t3460;
    Expr *body = Expr_new(ExprData_Body(), _t3459, _t3460, &p->path);
    (void)body;
    ;
    ;
    Bool in_namespace = 0;
    (void)in_namespace;
    while (1) {
        Bool _t3449 = check(p, TokenType_RBrace());
        (void)_t3449;
        Bool _t3450 = check(p, TokenType_Eof());
        (void)_t3450;
        Bool _t3451 = Bool_not(_t3449);
        (void)_t3451;
        ;
        Bool _t3452 = Bool_not(_t3450);
        (void)_t3452;
        ;
        Bool _wcond3443 = Bool_and(_t3451, _t3452);
        (void)_wcond3443;
        ;
        ;
        if (_wcond3443) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3453 = check(p, TokenType_KwNamespace());
        (void)_t3453;
        if (_t3453) {
            Token *_t3444 = advance(p);
            (void)_t3444;
            Token *_t3445 = expect_token(p, TokenType_Colon());
            (void)_t3445;
            Bool _t3446 = 1;
            (void)_t3446;
            in_namespace = _t3446;
            ;
            ;
            continue;
        }
        ;
        Expr *stmt = parse_statement(p);
        (void)stmt;
        Bool _t3454; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3454 = *_hp; free(_hp); }
        (void)_t3454;
        Bool _t3455 = Bool_and(in_namespace, _t3454);
        (void)_t3455;
        ;
        if (_t3455) {
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
    }
    ;
    Token *_t3461 = expect_token(p, TokenType_RBrace());
    (void)_t3461;
    Expr_add_child(def, body);
    return def;
}

Expr * parse_enum_def(Parser * p) {
    (void)p;
    U32 kw_line = peek_line(p);
    (void)kw_line;
    U32 kw_col = peek_col(p);
    (void)kw_col;
    Token *_t3485 = advance(p);
    (void)_t3485;
    Expr *def = Expr_new(ExprData_EnumDef(), kw_line, kw_col, &p->path);
    (void)def;
    ;
    ;
    Token *_t3486 = expect_token(p, TokenType_LBrace());
    (void)_t3486;
    U32 _t3487 = peek_line(p);
    (void)_t3487;
    U32 _t3488 = peek_col(p);
    (void)_t3488;
    Expr *body = Expr_new(ExprData_Body(), _t3487, _t3488, &p->path);
    (void)body;
    ;
    ;
    Bool in_namespace = 0;
    (void)in_namespace;
    while (1) {
        Bool _t3480 = check(p, TokenType_RBrace());
        (void)_t3480;
        Bool _t3481 = check(p, TokenType_Eof());
        (void)_t3481;
        Bool _t3482 = Bool_not(_t3480);
        (void)_t3482;
        ;
        Bool _t3483 = Bool_not(_t3481);
        (void)_t3483;
        ;
        Bool _wcond3462 = Bool_and(_t3482, _t3483);
        (void)_wcond3462;
        ;
        ;
        if (_wcond3462) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3484 = check(p, TokenType_KwNamespace());
        (void)_t3484;
        if (_t3484) {
            Token *_t3463 = advance(p);
            (void)_t3463;
            Token *_t3464 = expect_token(p, TokenType_Colon());
            (void)_t3464;
            Bool _t3465 = 1;
            (void)_t3465;
            in_namespace = _t3465;
            ;
            ;
            continue;
        }
        ;
        if (in_namespace) {
            Expr *stmt = parse_statement(p);
            (void)stmt;
            Bool _t3468; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3468 = *_hp; free(_hp); }
            (void)_t3468;
            if (_t3468) {
                Bool _t3467; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3467 = *_hp; free(_hp); }
                (void)_t3467;
                if (_t3467) {
                    Declaration *dd = ExprData_get_Decl(&stmt->data);
                    (void)dd;
                    Bool _t3466 = 1;
                    (void)_t3466;
                    dd->is_namespace = _t3466;
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
            Bool _t3471 = 0;
            (void)_t3471;
            Bool _t3472 = 0;
            (void)_t3472;
            Bool _t3473 = 0;
            (void)_t3473;
            Bool _t3474 = 0;
            (void)_t3474;
            I32 _t3475 = 0;
            (void)_t3475;
            I32 _t3476 = 0;
            (void)_t3476;
            Declaration *dd = malloc(sizeof(Declaration));
            { Str *_ca = Str_clone(vname); dd->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
            dd->is_mut = _t3471;
            dd->is_namespace = _t3472;
            dd->is_ref = _t3473;
            dd->is_own = _t3474;
            dd->field_offset = _t3475;
            dd->field_size = _t3476;
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
            Bool _t3477 = check(p, TokenType_Colon());
            (void)_t3477;
            if (_t3477) {
                Token *_t3469 = advance(p);
                (void)_t3469;
                Str_delete(&dd->explicit_type, &(Bool){0});
                { Str *_fa = expect_text(p, TokenType_Ident()); dd->explicit_type = *_fa; free(_fa); }
            }
            ;
            ExprData *_t3478 = ExprData_Decl(dd);
            (void)_t3478;
            Declaration_delete(dd, &(Bool){1});
            Expr *variant = Expr_new(_t3478, v_line, v_col, &p->path);
            (void)variant;
            ExprData_delete(_t3478, &(Bool){1});
            ;
            ;
            Expr_add_child(body, variant);
            Bool _t3479 = check(p, TokenType_Comma());
            (void)_t3479;
            if (_t3479) {
                Token *_t3470 = advance(p);
                (void)_t3470;
            }
            ;
        }
    }
    ;
    Token *_t3489 = expect_token(p, TokenType_RBrace());
    (void)_t3489;
    Expr_add_child(def, body);
    return def;
}

Expr * parse_call(Parser * p, Str * name, U32 call_line, U32 call_col) {
    (void)p;
    (void)name;
    (void)call_line;
    (void)call_col;
    Token *_t3520 = advance(p);
    (void)_t3520;
    Expr *call = Expr_new(ExprData_FCall(), call_line, call_col, &p->path);
    (void)call;
    Str *_t3521 = Str_clone(name);
    (void)_t3521;
    ExprData *_t3522 = ExprData_Ident(_t3521);
    (void)_t3522;
    Str_delete(_t3521, &(Bool){1});
    Expr *callee = Expr_new(_t3522, call_line, call_col, &p->path);
    (void)callee;
    ExprData_delete(_t3522, &(Bool){1});
    Expr_add_child(call, callee);
    while (1) {
        Bool _t3510 = check(p, TokenType_RParen());
        (void)_t3510;
        Bool _t3511 = check(p, TokenType_Eof());
        (void)_t3511;
        Bool _t3512 = Bool_not(_t3510);
        (void)_t3512;
        ;
        Bool _t3513 = Bool_not(_t3511);
        (void)_t3513;
        ;
        Bool _wcond3490 = Bool_and(_t3512, _t3513);
        (void)_wcond3490;
        ;
        ;
        if (_wcond3490) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3514 = check(p, TokenType_Ident());
        (void)_t3514;
        if (_t3514) {
            U64 _t3501 = 1;
            (void)_t3501;
            U64 _t3502 = U64_add(p->pos, _t3501);
            (void)_t3502;
            ;
            U64 _t3503; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3503 = *_hp; free(_hp); }
            (void)_t3503;
            Bool _t3504; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3502}, &(U64){_t3503}); _t3504 = *_hp; free(_hp); }
            (void)_t3504;
            ;
            ;
            if (_t3504) {
                U64 _t3496 = 1;
                (void)_t3496;
                U64 _t3497 = U64_add(p->pos, _t3496);
                (void)_t3497;
                ;
                I64 _t3498 = U64_to_i64(_t3497);
                (void)_t3498;
                ;
                U64 *_t3499 = malloc(sizeof(U64)); *_t3499 = I64_to_u64(_t3498);
                (void)_t3499;
                ;
                Token *next_tok = Vec_get(&p->tokens, _t3499);
                (void)next_tok;
                Bool _t3500; { Bool *_hp = (Bool *)TokenType_eq(&next_tok->type, TokenType_Eq()); _t3500 = *_hp; free(_hp); }
                (void)_t3500;
                U64_delete(_t3499, &(Bool){1});
                if (_t3500) {
                    U32 na_line = peek_line(p);
                    (void)na_line;
                    U32 na_col = peek_col(p);
                    (void)na_col;
                    Str *aname = expect_text(p, TokenType_Ident());
                    (void)aname;
                    Token *_t3492 = advance(p);
                    (void)_t3492;
                    ExprData *_t3493 = ExprData_NamedArg(aname);
                    (void)_t3493;
                    Str_delete(aname, &(Bool){1});
                    Expr *na = Expr_new(_t3493, na_line, na_col, &p->path);
                    (void)na;
                    ExprData_delete(_t3493, &(Bool){1});
                    ;
                    ;
                    Expr *_t3494 = parse_expression(p);
                    (void)_t3494;
                    Expr_add_child(na, _t3494);
                    Expr_add_child(call, na);
                    Bool _t3495 = check(p, TokenType_Comma());
                    (void)_t3495;
                    if (_t3495) {
                        Token *_t3491 = advance(p);
                        (void)_t3491;
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
        Bool _t3515 = check(p, TokenType_DotDot());
        (void)_t3515;
        if (_t3515) {
            Token *_t3505 = advance(p);
            (void)_t3505;
            Bool _t3506 = 1;
            (void)_t3506;
            is_splat = _t3506;
            ;
        }
        ;
        Bool is_own_arg = 0;
        (void)is_own_arg;
        Bool _t3516 = check(p, TokenType_KwOwn());
        (void)_t3516;
        if (_t3516) {
            Token *_t3507 = advance(p);
            (void)_t3507;
            Bool _t3508 = 1;
            (void)_t3508;
            is_own_arg = _t3508;
            ;
        }
        ;
        Expr *arg = parse_expression(p);
        (void)arg;
        Bool _t3517 = Bool_clone(&(Bool){is_own_arg});
        (void)_t3517;
        ;
        arg->is_own_arg = _t3517;
        ;
        Bool _t3518 = Bool_clone(&(Bool){is_splat});
        (void)_t3518;
        ;
        arg->is_splat = _t3518;
        ;
        Expr_add_child(call, arg);
        Bool _t3519 = check(p, TokenType_Comma());
        (void)_t3519;
        if (_t3519) {
            Token *_t3509 = advance(p);
            (void)_t3509;
        }
        ;
    }
    Token *_t3523 = expect_token(p, TokenType_RParen());
    (void)_t3523;
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
    U32 _t3711 = 0;
    (void)_t3711;
    U32 _t3712 = 0;
    (void)_t3712;
    Expr *e = Expr_new(ExprData_Body(), _t3711, _t3712, &p->path);
    (void)e;
    ;
    ;
    Bool e_set = 0;
    (void)e_set;
    Bool _t3713; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t3713 = *_hp; free(_hp); }
    (void)_t3713;
    if (_t3713) {
        Token *_t3524 = advance(p);
        (void)_t3524;
        Str *_t3525 = Str_clone(&t->text);
        (void)_t3525;
        ExprData *_t3526 = ExprData_LiteralStr(_t3525);
        (void)_t3526;
        Str_delete(_t3525, &(Bool){1});
        e = Expr_new(_t3526, t_line, t_col, &p->path);
        ExprData_delete(_t3526, &(Bool){1});
        Bool _t3527 = 1;
        (void)_t3527;
        e_set = _t3527;
        ;
    }
    ;
    Bool _t3714 = Bool_not(e_set);
    (void)_t3714;
    Bool _t3715; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t3715 = *_hp; free(_hp); }
    (void)_t3715;
    Bool _t3716 = Bool_and(_t3714, _t3715);
    (void)_t3716;
    ;
    ;
    if (_t3716) {
        Token *_t3528 = advance(p);
        (void)_t3528;
        Str *_t3529 = Str_clone(&t->text);
        (void)_t3529;
        ExprData *_t3530 = ExprData_LiteralNum(_t3529);
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
    Bool _t3717 = Bool_not(e_set);
    (void)_t3717;
    Bool _t3718; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Char()); _t3718 = *_hp; free(_hp); }
    (void)_t3718;
    Bool _t3719 = Bool_and(_t3717, _t3718);
    (void)_t3719;
    ;
    ;
    if (_t3719) {
        Token *_t3561 = advance(p);
        (void)_t3561;
        Str *ch = Str_clone(&t->text);
        (void)ch;
        I64 byte_val = 0;
        (void)byte_val;
        U64 _t3562; { U64 *_hp = (U64 *)Str_len(ch); _t3562 = *_hp; free(_hp); }
        (void)_t3562;
        U64 _t3563 = 0;
        (void)_t3563;
        U64 *_t3564 = malloc(sizeof(U64));
        *_t3564 = 0;
        (void)_t3564;
        U8 *_t3565 = Str_get(ch, _t3564);
        (void)_t3565;
        U8 _t3566 = 92;
        (void)_t3566;
        Bool _t3567; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3562}, &(U64){_t3563}); _t3567 = *_hp; free(_hp); }
        (void)_t3567;
        ;
        ;
        Bool _t3568 = U8_eq(DEREF(_t3565), _t3566);
        (void)_t3568;
        U64_delete(_t3564, &(Bool){1});
        ;
        Bool _t3569 = Bool_and(_t3567, _t3568);
        (void)_t3569;
        ;
        ;
        if (_t3569) {
            U64 _t3552; { U64 *_hp = (U64 *)Str_len(ch); _t3552 = *_hp; free(_hp); }
            (void)_t3552;
            U64 _t3553 = 1;
            (void)_t3553;
            Bool _t3554; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3552}, &(U64){_t3553}); _t3554 = *_hp; free(_hp); }
            (void)_t3554;
            ;
            ;
            if (_t3554) {
                U64 *_t3549 = malloc(sizeof(U64));
                *_t3549 = 1;
                (void)_t3549;
                U8 *c2 = Str_get(ch, _t3549);
                (void)c2;
                U8 _t3550 = 110;
                (void)_t3550;
                Bool _t3551 = U8_eq(DEREF(c2), _t3550);
                (void)_t3551;
                ;
                if (_t3551) {
                    I64 _t3532 = 10;
                    (void)_t3532;
                    byte_val = _t3532;
                    ;
                } else {
                    U8 _t3547 = 116;
                    (void)_t3547;
                    Bool _t3548 = U8_eq(DEREF(c2), _t3547);
                    (void)_t3548;
                    ;
                    if (_t3548) {
                        I64 _t3533 = 9;
                        (void)_t3533;
                        byte_val = _t3533;
                        ;
                    } else {
                        U8 _t3545 = 114;
                        (void)_t3545;
                        Bool _t3546 = U8_eq(DEREF(c2), _t3545);
                        (void)_t3546;
                        ;
                        if (_t3546) {
                            I64 _t3534 = 13;
                            (void)_t3534;
                            byte_val = _t3534;
                            ;
                        } else {
                            U8 _t3543 = 92;
                            (void)_t3543;
                            Bool _t3544 = U8_eq(DEREF(c2), _t3543);
                            (void)_t3544;
                            ;
                            if (_t3544) {
                                I64 _t3535 = 92;
                                (void)_t3535;
                                byte_val = _t3535;
                                ;
                            } else {
                                U8 _t3541 = 39;
                                (void)_t3541;
                                Bool _t3542 = U8_eq(DEREF(c2), _t3541);
                                (void)_t3542;
                                ;
                                if (_t3542) {
                                    I64 _t3536 = 39;
                                    (void)_t3536;
                                    byte_val = _t3536;
                                    ;
                                } else {
                                    U8 _t3539 = 48;
                                    (void)_t3539;
                                    Bool _t3540 = U8_eq(DEREF(c2), _t3539);
                                    (void)_t3540;
                                    ;
                                    if (_t3540) {
                                        I64 _t3537 = 0;
                                        (void)_t3537;
                                        byte_val = _t3537;
                                        ;
                                    } else {
                                        I64 _t3538 = U8_to_i64(DEREF(c2));
                                        (void)_t3538;
                                        byte_val = _t3538;
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
                U64_delete(_t3549, &(Bool){1});
                ;
            }
            ;
        } else {
            U64 _t3558; { U64 *_hp = (U64 *)Str_len(ch); _t3558 = *_hp; free(_hp); }
            (void)_t3558;
            U64 _t3559 = 0;
            (void)_t3559;
            Bool _t3560; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3558}, &(U64){_t3559}); _t3560 = *_hp; free(_hp); }
            (void)_t3560;
            ;
            ;
            if (_t3560) {
                U64 *_t3555 = malloc(sizeof(U64));
                *_t3555 = 0;
                (void)_t3555;
                U8 *_t3556 = Str_get(ch, _t3555);
                (void)_t3556;
                I64 _t3557 = U8_to_i64(DEREF(_t3556));
                (void)_t3557;
                U64_delete(_t3555, &(Bool){1});
                byte_val = _t3557;
                ;
            }
            ;
        }
        ;
        Str_delete(ch, &(Bool){1});
        Str *_t3570 = I64_to_str(&(I64){byte_val});
        (void)_t3570;
        ;
        ExprData *_t3571 = ExprData_LiteralNum(_t3570);
        (void)_t3571;
        Str_delete(_t3570, &(Bool){1});
        e = Expr_new(_t3571, t_line, t_col, &p->path);
        ExprData_delete(_t3571, &(Bool){1});
        TilType_delete(&e->til_type, &(Bool){0});
        { TilType *_fa = TilType_clone(TilType_U8()); e->til_type = *_fa; free(_fa); }
        Bool _t3572 = 1;
        (void)_t3572;
        e_set = _t3572;
        ;
    }
    ;
    Bool _t3720; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t3720 = *_hp; free(_hp); }
    (void)_t3720;
    Bool _t3721; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t3721 = *_hp; free(_hp); }
    (void)_t3721;
    Bool _t3722 = Bool_not(e_set);
    (void)_t3722;
    Bool _t3723 = Bool_or(_t3720, _t3721);
    (void)_t3723;
    ;
    ;
    Bool _t3724 = Bool_and(_t3722, _t3723);
    (void)_t3724;
    ;
    ;
    if (_t3724) {
        Token *_t3573 = advance(p);
        (void)_t3573;
        Str *_t3574 = Str_clone(&t->text);
        (void)_t3574;
        ExprData *_t3575 = ExprData_LiteralBool(_t3574);
        (void)_t3575;
        Str_delete(_t3574, &(Bool){1});
        e = Expr_new(_t3575, t_line, t_col, &p->path);
        ExprData_delete(_t3575, &(Bool){1});
        Bool _t3576 = 1;
        (void)_t3576;
        e_set = _t3576;
        ;
    }
    ;
    Bool _t3725 = Bool_not(e_set);
    (void)_t3725;
    Bool _t3726; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwNull()); _t3726 = *_hp; free(_hp); }
    (void)_t3726;
    Bool _t3727 = Bool_and(_t3725, _t3726);
    (void)_t3727;
    ;
    ;
    if (_t3727) {
        Token *_t3577 = advance(p);
        (void)_t3577;
        e = Expr_new(ExprData_LiteralNull(), t_line, t_col, &p->path);
        Bool _t3578 = 1;
        (void)_t3578;
        e_set = _t3578;
        ;
    }
    ;
    Bool _t3728 = Bool_not(e_set);
    (void)_t3728;
    Bool _t3729; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t3729 = *_hp; free(_hp); }
    (void)_t3729;
    Bool _t3730 = Bool_and(_t3728, _t3729);
    (void)_t3730;
    ;
    ;
    if (_t3730) {
        Token *_t3614 = advance(p);
        (void)_t3614;
        Str *name = Str_clone(&t->text);
        (void)name;
        Str *_t3615 = Str_lit("__LOC__", 7ULL);
        (void)_t3615;
        Bool _t3616; { Bool *_hp = (Bool *)Str_eq(name, _t3615); _t3616 = *_hp; free(_hp); }
        (void)_t3616;
        Str_delete(_t3615, &(Bool){1});
        if (_t3616) {
            Str *_t3579 = Str_lit("Str", 3ULL);
            (void)_t3579;
            U64 _t3580; { U64 *_hp = (U64 *)Str_size(); _t3580 = *_hp; free(_hp); }
            (void)_t3580;
            U64 _t3581 = 5;
            (void)_t3581;
            Array *_va67 = Array_new(_t3579, &(U64){_t3580}, &(U64){_t3581});
            (void)_va67;
            Str_delete(_t3579, &(Bool){1});
            ;
            ;
            U64 _t3582 = 0;
            (void)_t3582;
            Str *_t3583 = Str_clone(&p->path);
            (void)_t3583;
            Array_set(_va67, &(U64){_t3582}, _t3583);
            ;
            U64 _t3584 = 1;
            (void)_t3584;
            Str *_t3585 = Str_lit(":", 1ULL);
            (void)_t3585;
            Array_set(_va67, &(U64){_t3584}, _t3585);
            ;
            U64 _t3586 = 2;
            (void)_t3586;
            Str *_t3587 = U32_to_str(&(U32){t_line});
            (void)_t3587;
            Array_set(_va67, &(U64){_t3586}, _t3587);
            ;
            U64 _t3588 = 3;
            (void)_t3588;
            Str *_t3589 = Str_lit(":", 1ULL);
            (void)_t3589;
            Array_set(_va67, &(U64){_t3588}, _t3589);
            ;
            U64 _t3590 = 4;
            (void)_t3590;
            Str *_t3591 = U32_to_str(&(U32){t_col});
            (void)_t3591;
            Array_set(_va67, &(U64){_t3590}, _t3591);
            ;
            Str *_t3592 = format(_va67);
            (void)_t3592;
            ExprData *_t3593 = ExprData_LiteralStr(_t3592);
            (void)_t3593;
            Str_delete(_t3592, &(Bool){1});
            e = Expr_new(_t3593, t_line, t_col, &p->path);
            ExprData_delete(_t3593, &(Bool){1});
            Bool _t3594 = 1;
            (void)_t3594;
            e_set = _t3594;
            ;
        } else {
            Str *_t3612 = Str_lit("__FILE__", 8ULL);
            (void)_t3612;
            Bool _t3613; { Bool *_hp = (Bool *)Str_eq(name, _t3612); _t3613 = *_hp; free(_hp); }
            (void)_t3613;
            Str_delete(_t3612, &(Bool){1});
            if (_t3613) {
                Str *_t3595 = Str_clone(&p->path);
                (void)_t3595;
                ExprData *_t3596 = ExprData_LiteralStr(_t3595);
                (void)_t3596;
                Str_delete(_t3595, &(Bool){1});
                e = Expr_new(_t3596, t_line, t_col, &p->path);
                ExprData_delete(_t3596, &(Bool){1});
                Bool _t3597 = 1;
                (void)_t3597;
                e_set = _t3597;
                ;
            } else {
                Str *_t3610 = Str_lit("__LINE__", 8ULL);
                (void)_t3610;
                Bool _t3611; { Bool *_hp = (Bool *)Str_eq(name, _t3610); _t3611 = *_hp; free(_hp); }
                (void)_t3611;
                Str_delete(_t3610, &(Bool){1});
                if (_t3611) {
                    Str *_t3598 = U32_to_str(&(U32){t_line});
                    (void)_t3598;
                    ExprData *_t3599 = ExprData_LiteralNum(_t3598);
                    (void)_t3599;
                    Str_delete(_t3598, &(Bool){1});
                    e = Expr_new(_t3599, t_line, t_col, &p->path);
                    ExprData_delete(_t3599, &(Bool){1});
                    Bool _t3600 = 1;
                    (void)_t3600;
                    e_set = _t3600;
                    ;
                } else {
                    Str *_t3608 = Str_lit("__COL__", 7ULL);
                    (void)_t3608;
                    Bool _t3609; { Bool *_hp = (Bool *)Str_eq(name, _t3608); _t3609 = *_hp; free(_hp); }
                    (void)_t3609;
                    Str_delete(_t3608, &(Bool){1});
                    if (_t3609) {
                        Str *_t3601 = U32_to_str(&(U32){t_col});
                        (void)_t3601;
                        ExprData *_t3602 = ExprData_LiteralNum(_t3601);
                        (void)_t3602;
                        Str_delete(_t3601, &(Bool){1});
                        e = Expr_new(_t3602, t_line, t_col, &p->path);
                        ExprData_delete(_t3602, &(Bool){1});
                        Bool _t3603 = 1;
                        (void)_t3603;
                        e_set = _t3603;
                        ;
                    } else {
                        Bool _t3607 = check(p, TokenType_LParen());
                        (void)_t3607;
                        if (_t3607) {
                            e = parse_call(p, name, t_line, t_col);
                            Bool _t3604 = 1;
                            (void)_t3604;
                            e_set = _t3604;
                            ;
                        } else {
                            ExprData *_t3605 = ExprData_Ident(name);
                            (void)_t3605;
                            e = Expr_new(_t3605, t_line, t_col, &p->path);
                            ExprData_delete(_t3605, &(Bool){1});
                            Bool _t3606 = 1;
                            (void)_t3606;
                            e_set = _t3606;
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
    Bool _t3731; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFunc()); _t3731 = *_hp; free(_hp); }
    (void)_t3731;
    Bool _t3732; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwProc()); _t3732 = *_hp; free(_hp); }
    (void)_t3732;
    Bool _t3733 = Bool_or(_t3731, _t3732);
    (void)_t3733;
    ;
    ;
    Bool _t3734; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTest()); _t3734 = *_hp; free(_hp); }
    (void)_t3734;
    Bool _t3735 = Bool_or(_t3733, _t3734);
    (void)_t3735;
    ;
    ;
    Bool _t3736; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMacro()); _t3736 = *_hp; free(_hp); }
    (void)_t3736;
    Bool _t3737 = Bool_or(_t3735, _t3736);
    (void)_t3737;
    ;
    ;
    Bool _t3738; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtFunc()); _t3738 = *_hp; free(_hp); }
    (void)_t3738;
    Bool _t3739 = Bool_or(_t3737, _t3738);
    (void)_t3739;
    ;
    ;
    Bool _t3740; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtProc()); _t3740 = *_hp; free(_hp); }
    (void)_t3740;
    Bool _t3741 = Bool_not(e_set);
    (void)_t3741;
    Bool _t3742 = Bool_or(_t3739, _t3740);
    (void)_t3742;
    ;
    ;
    Bool _t3743 = Bool_and(_t3741, _t3742);
    (void)_t3743;
    ;
    ;
    if (_t3743) {
        Expr *_t3617 = parse_func_def(p);
        (void)_t3617;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3617;
    }
    ;
    Bool _t3744; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwStruct()); _t3744 = *_hp; free(_hp); }
    (void)_t3744;
    Bool _t3745; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtStruct()); _t3745 = *_hp; free(_hp); }
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
        Expr *_t3618 = parse_struct_def(p);
        (void)_t3618;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3618;
    }
    ;
    Bool _t3749 = Bool_not(e_set);
    (void)_t3749;
    Bool _t3750; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwEnum()); _t3750 = *_hp; free(_hp); }
    (void)_t3750;
    Bool _t3751 = Bool_and(_t3749, _t3750);
    (void)_t3751;
    ;
    ;
    if (_t3751) {
        Expr *_t3619 = parse_enum_def(p);
        (void)_t3619;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3619;
    }
    ;
    Bool _t3752 = Bool_not(e_set);
    (void)_t3752;
    Bool _t3753; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t3753 = *_hp; free(_hp); }
    (void)_t3753;
    Bool _t3754 = Bool_and(_t3752, _t3753);
    (void)_t3754;
    ;
    ;
    if (_t3754) {
        Token *_t3644 = advance(p);
        (void)_t3644;
        Expr *first = parse_expression(p);
        (void)first;
        Bool _t3645 = check(p, TokenType_Colon());
        (void)_t3645;
        if (_t3645) {
            e = Expr_new(ExprData_MapLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Token *_t3631 = advance(p);
            (void)_t3631;
            Expr *_t3632 = parse_expression(p);
            (void)_t3632;
            Expr_add_child(e, _t3632);
            Bool _t3633 = check(p, TokenType_Comma());
            (void)_t3633;
            if (_t3633) {
                Token *_t3620 = advance(p);
                (void)_t3620;
            }
            ;
            while (1) {
                Bool _t3623 = check(p, TokenType_RBrace());
                (void)_t3623;
                Bool _t3624 = check(p, TokenType_Eof());
                (void)_t3624;
                Bool _t3625 = Bool_not(_t3623);
                (void)_t3625;
                ;
                Bool _t3626 = Bool_not(_t3624);
                (void)_t3626;
                ;
                Bool _wcond3621 = Bool_and(_t3625, _t3626);
                (void)_wcond3621;
                ;
                ;
                if (_wcond3621) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3627 = parse_expression(p);
                (void)_t3627;
                Expr_add_child(e, _t3627);
                Token *_t3628 = expect_token(p, TokenType_Colon());
                (void)_t3628;
                Expr *_t3629 = parse_expression(p);
                (void)_t3629;
                Expr_add_child(e, _t3629);
                Bool _t3630 = check(p, TokenType_Comma());
                (void)_t3630;
                if (_t3630) {
                    Token *_t3622 = advance(p);
                    (void)_t3622;
                }
                ;
            }
        } else {
            e = Expr_new(ExprData_SetLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Bool _t3643 = check(p, TokenType_Comma());
            (void)_t3643;
            if (_t3643) {
                Token *_t3634 = advance(p);
                (void)_t3634;
            }
            ;
            while (1) {
                Bool _t3637 = check(p, TokenType_RBrace());
                (void)_t3637;
                Bool _t3638 = check(p, TokenType_Eof());
                (void)_t3638;
                Bool _t3639 = Bool_not(_t3637);
                (void)_t3639;
                ;
                Bool _t3640 = Bool_not(_t3638);
                (void)_t3640;
                ;
                Bool _wcond3635 = Bool_and(_t3639, _t3640);
                (void)_wcond3635;
                ;
                ;
                if (_wcond3635) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3641 = parse_expression(p);
                (void)_t3641;
                Expr_add_child(e, _t3641);
                Bool _t3642 = check(p, TokenType_Comma());
                (void)_t3642;
                if (_t3642) {
                    Token *_t3636 = advance(p);
                    (void)_t3636;
                }
                ;
            }
        }
        ;
        Token *_t3646 = expect_token(p, TokenType_RBrace());
        (void)_t3646;
        Bool _t3647 = 1;
        (void)_t3647;
        e_set = _t3647;
        ;
    }
    ;
    Bool _t3755 = Bool_not(e_set);
    (void)_t3755;
    ;
    if (_t3755) {
        Str *_t3648 = Str_lit("Str", 3ULL);
        (void)_t3648;
        U64 _t3649; { U64 *_hp = (U64 *)Str_size(); _t3649 = *_hp; free(_hp); }
        (void)_t3649;
        U64 _t3650 = 8;
        (void)_t3650;
        Array *_va68 = Array_new(_t3648, &(U64){_t3649}, &(U64){_t3650});
        (void)_va68;
        Str_delete(_t3648, &(Bool){1});
        ;
        ;
        U64 _t3651 = 0;
        (void)_t3651;
        Str *_t3652 = Str_clone(&p->path);
        (void)_t3652;
        Array_set(_va68, &(U64){_t3651}, _t3652);
        ;
        U64 _t3653 = 1;
        (void)_t3653;
        Str *_t3654 = Str_lit(":", 1ULL);
        (void)_t3654;
        Array_set(_va68, &(U64){_t3653}, _t3654);
        ;
        U64 _t3655 = 2;
        (void)_t3655;
        Str *_t3656 = U32_to_str(&(U32){t_line});
        (void)_t3656;
        Array_set(_va68, &(U64){_t3655}, _t3656);
        ;
        U64 _t3657 = 3;
        (void)_t3657;
        Str *_t3658 = Str_lit(":", 1ULL);
        (void)_t3658;
        Array_set(_va68, &(U64){_t3657}, _t3658);
        ;
        U64 _t3659 = 4;
        (void)_t3659;
        Str *_t3660 = U32_to_str(&(U32){t_col});
        (void)_t3660;
        Array_set(_va68, &(U64){_t3659}, _t3660);
        ;
        U64 _t3661 = 5;
        (void)_t3661;
        Str *_t3662 = Str_lit(": unexpected token '", 20ULL);
        (void)_t3662;
        Array_set(_va68, &(U64){_t3661}, _t3662);
        ;
        U64 _t3663 = 6;
        (void)_t3663;
        Str *_t3664 = Str_clone(&t->text);
        (void)_t3664;
        Array_set(_va68, &(U64){_t3663}, _t3664);
        ;
        U64 _t3665 = 7;
        (void)_t3665;
        Str *_t3666 = Str_lit("'", 1ULL);
        (void)_t3666;
        Array_set(_va68, &(U64){_t3665}, _t3666);
        ;
        Str *_t3667 = Str_lit("src/self/parser.til:517:15", 26ULL);
        (void)_t3667;
        panic(_t3667, _va68);
        Str_delete(_t3667, &(Bool){1});
    }
    ;
    ;
    ;
    while (1) {
        Bool _wcond3668 = check(p, TokenType_Dot());
        (void)_wcond3668;
        if (_wcond3668) {
        } else {
            ;
            break;
        }
        ;
        Token *_t3701 = advance(p);
        (void)_t3701;
        U32 f_line = peek_line(p);
        (void)f_line;
        U32 f_col = peek_col(p);
        (void)f_col;
        Str *fname = expect_text(p, TokenType_Ident());
        (void)fname;
        Bool _t3702 = check(p, TokenType_LParen());
        (void)_t3702;
        if (_t3702) {
            Token *_t3695 = advance(p);
            (void)_t3695;
            ExprData *_t3696 = ExprData_FieldAccess(fname);
            (void)_t3696;
            Expr *callee = Expr_new(_t3696, f_line, f_col, &p->path);
            (void)callee;
            ExprData_delete(_t3696, &(Bool){1});
            Expr *_t3697 = Expr_clone(e);
            (void)_t3697;
            Expr_add_child(callee, _t3697);
            Expr *mcall = Expr_new(ExprData_FCall(), f_line, f_col, &p->path);
            (void)mcall;
            Expr_add_child(mcall, callee);
            while (1) {
                Bool _t3687 = check(p, TokenType_RParen());
                (void)_t3687;
                Bool _t3688 = check(p, TokenType_Eof());
                (void)_t3688;
                Bool _t3689 = Bool_not(_t3687);
                (void)_t3689;
                ;
                Bool _t3690 = Bool_not(_t3688);
                (void)_t3690;
                ;
                Bool _wcond3669 = Bool_and(_t3689, _t3690);
                (void)_wcond3669;
                ;
                ;
                if (_wcond3669) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3691 = check(p, TokenType_Ident());
                (void)_t3691;
                if (_t3691) {
                    U64 _t3680 = 1;
                    (void)_t3680;
                    U64 _t3681 = U64_add(p->pos, _t3680);
                    (void)_t3681;
                    ;
                    U64 _t3682; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3682 = *_hp; free(_hp); }
                    (void)_t3682;
                    Bool _t3683; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3681}, &(U64){_t3682}); _t3683 = *_hp; free(_hp); }
                    (void)_t3683;
                    ;
                    ;
                    if (_t3683) {
                        U64 _t3675 = 1;
                        (void)_t3675;
                        U64 _t3676 = U64_add(p->pos, _t3675);
                        (void)_t3676;
                        ;
                        I64 _t3677 = U64_to_i64(_t3676);
                        (void)_t3677;
                        ;
                        U64 *_t3678 = malloc(sizeof(U64)); *_t3678 = I64_to_u64(_t3677);
                        (void)_t3678;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3678);
                        (void)nt;
                        Bool _t3679; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3679 = *_hp; free(_hp); }
                        (void)_t3679;
                        U64_delete(_t3678, &(Bool){1});
                        if (_t3679) {
                            U32 na_line = peek_line(p);
                            (void)na_line;
                            U32 na_col = peek_col(p);
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3671 = advance(p);
                            (void)_t3671;
                            ExprData *_t3672 = ExprData_NamedArg(aname);
                            (void)_t3672;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3672, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3672, &(Bool){1});
                            ;
                            ;
                            Expr *_t3673 = parse_expression(p);
                            (void)_t3673;
                            Expr_add_child(na, _t3673);
                            Expr_add_child(mcall, na);
                            Bool _t3674 = check(p, TokenType_Comma());
                            (void)_t3674;
                            if (_t3674) {
                                Token *_t3670 = advance(p);
                                (void)_t3670;
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
                Bool _t3692 = check(p, TokenType_KwOwn());
                (void)_t3692;
                if (_t3692) {
                    Token *_t3684 = advance(p);
                    (void)_t3684;
                    Bool _t3685 = 1;
                    (void)_t3685;
                    is_own_arg = _t3685;
                    ;
                }
                ;
                Expr *marg = parse_expression(p);
                (void)marg;
                Bool _t3693 = Bool_clone(&(Bool){is_own_arg});
                (void)_t3693;
                ;
                marg->is_own_arg = _t3693;
                ;
                Expr_add_child(mcall, marg);
                Bool _t3694 = check(p, TokenType_Comma());
                (void)_t3694;
                if (_t3694) {
                    Token *_t3686 = advance(p);
                    (void)_t3686;
                }
                ;
            }
            Token *_t3698 = expect_token(p, TokenType_RParen());
            (void)_t3698;
            e = Expr_clone(mcall);
            Expr_delete(mcall, &(Bool){1});
        } else {
            ExprData *_t3699 = ExprData_FieldAccess(fname);
            (void)_t3699;
            Expr *access = Expr_new(_t3699, f_line, f_col, &p->path);
            (void)access;
            ExprData_delete(_t3699, &(Bool){1});
            Expr *_t3700 = Expr_clone(e);
            (void)_t3700;
            Expr_add_child(access, _t3700);
            e = Expr_clone(access);
            Expr_delete(access, &(Bool){1});
        }
        ;
        ;
        ;
        Str_delete(fname, &(Bool){1});
    }
    Bool _t3756 = check(p, TokenType_DotDot());
    (void)_t3756;
    if (_t3756) {
        U32 dt_line = peek_line(p);
        (void)dt_line;
        U32 dt_col = peek_col(p);
        (void)dt_col;
        Token *_t3703 = advance(p);
        (void)_t3703;
        Expr *rhs = parse_expression(p);
        (void)rhs;
        Str *_t3704 = Str_lit("Range", 5ULL);
        (void)_t3704;
        Str *_t3705 = Str_clone(_t3704);
        (void)_t3705;
        Str_delete(_t3704, &(Bool){1});
        ExprData *_t3706 = ExprData_Ident(_t3705);
        (void)_t3706;
        Str_delete(_t3705, &(Bool){1});
        Expr *range_ident = Expr_new(_t3706, dt_line, dt_col, &p->path);
        (void)range_ident;
        ExprData_delete(_t3706, &(Bool){1});
        Str *_t3707 = Str_lit("new", 3ULL);
        (void)_t3707;
        Str *_t3708 = Str_clone(_t3707);
        (void)_t3708;
        Str_delete(_t3707, &(Bool){1});
        ExprData *_t3709 = ExprData_FieldAccess(_t3708);
        (void)_t3709;
        Str_delete(_t3708, &(Bool){1});
        Expr *new_access = Expr_new(_t3709, dt_line, dt_col, &p->path);
        (void)new_access;
        ExprData_delete(_t3709, &(Bool){1});
        Expr_add_child(new_access, range_ident);
        Expr *rcall = Expr_new(ExprData_FCall(), dt_line, dt_col, &p->path);
        (void)rcall;
        ;
        ;
        Expr_add_child(rcall, new_access);
        Expr *_t3710 = Expr_clone(e);
        (void)_t3710;
        Expr_add_child(rcall, _t3710);
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
    Bool _t3958 = check(p, TokenType_ColonEq());
    (void)_t3958;
    if (_t3958) {
        Token *_t3757 = advance(p);
        (void)_t3757;
        Bool _t3758 = Bool_clone(&(Bool){is_mut});
        (void)_t3758;
        Bool _t3759 = 0;
        (void)_t3759;
        Bool _t3760 = 0;
        (void)_t3760;
        Bool _t3761 = Bool_clone(&(Bool){is_own});
        (void)_t3761;
        I32 _t3762 = 0;
        (void)_t3762;
        I32 _t3763 = 0;
        (void)_t3763;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3758;
        dd->is_namespace = _t3759;
        dd->is_ref = _t3760;
        dd->is_own = _t3761;
        dd->field_offset = _t3762;
        dd->field_size = _t3763;
        dd->field_struct_def = NULL;
        dd->fn_sig = NULL;
        (void)dd;
        ;
        ;
        ;
        ;
        ;
        ;
        ExprData *_t3764 = ExprData_Decl(dd);
        (void)_t3764;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3764, t_line, t_col, &p->path);
        (void)decl;
        ExprData_delete(_t3764, &(Bool){1});
        Expr *_t3765 = parse_expression(p);
        (void)_t3765;
        Expr_add_child(decl, _t3765);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return decl;
    }
    ;
    Bool _t3959 = check(p, TokenType_Colon());
    (void)_t3959;
    if (_t3959) {
        Token *_t3890 = advance(p);
        (void)_t3890;
        Bool _t3891 = check(p, TokenType_KwFunc());
        (void)_t3891;
        Bool _t3892 = check(p, TokenType_KwProc());
        (void)_t3892;
        Bool _t3893 = Bool_or(_t3891, _t3892);
        (void)_t3893;
        ;
        ;
        if (_t3893) {
            Expr *sig = parse_func_def(p);
            (void)sig;
            Token *_t3783 = expect_token(p, TokenType_Eq());
            (void)_t3783;
            Token *_t3784 = expect_token(p, TokenType_LParen());
            (void)_t3784;
            Bool _t3785; { Bool *_hp = (Bool *)ExprData_is_FuncDef(&sig->data); _t3785 = *_hp; free(_hp); }
            (void)_t3785;
            if (_t3785) {
                FunctionDef *sfd = ExprData_get_FuncDef(&sig->data);
                (void)sfd;
                Str *_t3780 = Str_lit("Str", 3ULL);
                (void)_t3780;
                U64 _t3781; { U64 *_hp = (U64 *)Str_size(); _t3781 = *_hp; free(_hp); }
                (void)_t3781;
                Vec *new_names = Vec_new(_t3780, &(U64){_t3781});
                (void)new_names;
                Str_delete(_t3780, &(Bool){1});
                ;
                {
                    U64 _fi3766 = 0;
                    (void)_fi3766;
                    while (1) {
                        U64 _t3769 = 0;
                        (void)_t3769;
                        U64 _t3770; { U64 *_hp = (U64 *)Vec_len(&sfd->param_names); _t3770 = *_hp; free(_hp); }
                        (void)_t3770;
                        Range *_t3771 = Range_new(_t3769, _t3770);
                        (void)_t3771;
                        ;
                        ;
                        U64 _t3772; { U64 *_hp = (U64 *)Range_len(_t3771); _t3772 = *_hp; free(_hp); }
                        (void)_t3772;
                        Range_delete(_t3771, &(Bool){1});
                        Bool _wcond3767; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3766}, &(U64){_t3772}); _wcond3767 = *_hp; free(_hp); }
                        (void)_wcond3767;
                        ;
                        if (_wcond3767) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 _t3773 = 0;
                        (void)_t3773;
                        U64 _t3774; { U64 *_hp = (U64 *)Vec_len(&sfd->param_names); _t3774 = *_hp; free(_hp); }
                        (void)_t3774;
                        Range *_t3775 = Range_new(_t3773, _t3774);
                        (void)_t3775;
                        ;
                        ;
                        U64 pi; { U64 *_hp = (U64 *)Range_get(_t3775, _fi3766); pi = *_hp; free(_hp); }
                        (void)pi;
                        Range_delete(_t3775, &(Bool){1});
                        U64 _t3776 = 1;
                        (void)_t3776;
                        U64 _t3777 = U64_add(_fi3766, _t3776);
                        (void)_t3777;
                        ;
                        _fi3766 = _t3777;
                        ;
                        U64 _t3778 = 0;
                        (void)_t3778;
                        Bool _t3779; { Bool *_hp = (Bool *)U64_gt(&(U64){pi}, &(U64){_t3778}); _t3779 = *_hp; free(_hp); }
                        (void)_t3779;
                        ;
                        ;
                        if (_t3779) {
                            Token *_t3768 = expect_token(p, TokenType_Comma());
                            (void)_t3768;
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
            Bool _t3786 = check(p, TokenType_Comma());
            (void)_t3786;
            if (_t3786) {
                Token *_t3782 = advance(p);
                (void)_t3782;
            }
            ;
            Token *_t3787 = expect_token(p, TokenType_RParen());
            (void)_t3787;
            Token *_t3788 = expect_token(p, TokenType_LBrace());
            (void)_t3788;
            Expr *_t3789 = parse_block(p);
            (void)_t3789;
            Expr_add_child(sig, _t3789);
            Bool _t3790 = Bool_clone(&(Bool){is_mut});
            (void)_t3790;
            Bool _t3791 = 0;
            (void)_t3791;
            Bool _t3792 = 0;
            (void)_t3792;
            Bool _t3793 = Bool_clone(&(Bool){is_own});
            (void)_t3793;
            I32 _t3794 = 0;
            (void)_t3794;
            I32 _t3795 = 0;
            (void)_t3795;
            Declaration *dd = malloc(sizeof(Declaration));
            { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
            dd->is_mut = _t3790;
            dd->is_namespace = _t3791;
            dd->is_ref = _t3792;
            dd->is_own = _t3793;
            dd->field_offset = _t3794;
            dd->field_size = _t3795;
            dd->field_struct_def = NULL;
            dd->fn_sig = NULL;
            (void)dd;
            ;
            ;
            ;
            ;
            ;
            ;
            ExprData *_t3796 = ExprData_Decl(dd);
            (void)_t3796;
            Declaration_delete(dd, &(Bool){1});
            Expr *decl = Expr_new(_t3796, t_line, t_col, &p->path);
            (void)decl;
            ExprData_delete(_t3796, &(Bool){1});
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
        I64 _t3894 = 0;
        (void)_t3894;
        I64 _t3895 = 1;
        (void)_t3895;
        I64 fn_sig_idx = I64_sub(_t3894, _t3895);
        (void)fn_sig_idx;
        ;
        ;
        Str *_t3896 = Str_lit("Fn", 2ULL);
        (void)_t3896;
        Bool _t3897; { Bool *_hp = (Bool *)Str_eq(type_name, _t3896); _t3897 = *_hp; free(_hp); }
        (void)_t3897;
        Str_delete(_t3896, &(Bool){1});
        if (_t3897) {
            Expr *sig = parse_fn_signature(p, t_line, t_col);
            (void)sig;
            U32 _t3798 = 0;
            (void)_t3798;
            Bool _t3799; { Bool *_hp = (Bool *)U32_neq(&sig->line, &(U32){_t3798}); _t3799 = *_hp; free(_hp); }
            (void)_t3799;
            ;
            Expr_delete(sig, &(Bool){1});
            if (_t3799) {
                I64 _t3797 = 0;
                (void)_t3797;
                fn_sig_idx = _t3797;
                ;
            }
            ;
        }
        ;
        ;
        Token *_t3898 = expect_token(p, TokenType_Eq());
        (void)_t3898;
        Bool _t3899 = check(p, TokenType_LParen());
        (void)_t3899;
        if (_t3899) {
            U64 saved = p->pos;
            (void)saved;
            Token *_t3886 = advance(p);
            (void)_t3886;
            Bool is_fsf = 1;
            (void)is_fsf;
            while (1) {
                Bool _t3803 = check(p, TokenType_RParen());
                (void)_t3803;
                Bool _t3804 = check(p, TokenType_Eof());
                (void)_t3804;
                Bool _t3805 = Bool_not(_t3803);
                (void)_t3805;
                ;
                Bool _t3806 = Bool_not(_t3804);
                (void)_t3806;
                ;
                Bool _wcond3800 = Bool_and(_t3805, _t3806);
                (void)_wcond3800;
                ;
                ;
                if (_wcond3800) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3807 = check(p, TokenType_Ident());
                (void)_t3807;
                Bool _t3808 = Bool_not(_t3807);
                (void)_t3808;
                ;
                if (_t3808) {
                    Bool _t3801 = 0;
                    (void)_t3801;
                    is_fsf = _t3801;
                    ;
                    ;
                    break;
                }
                ;
                Token *_t3809 = advance(p);
                (void)_t3809;
                Bool _t3810 = check(p, TokenType_Comma());
                (void)_t3810;
                if (_t3810) {
                    Token *_t3802 = advance(p);
                    (void)_t3802;
                }
                ;
            }
            Bool _t3887 = check(p, TokenType_RParen());
            (void)_t3887;
            Bool _t3888 = Bool_and(is_fsf, _t3887);
            (void)_t3888;
            ;
            if (_t3888) {
                Token *_t3812 = advance(p);
                (void)_t3812;
                Bool _t3813 = check(p, TokenType_LBrace());
                (void)_t3813;
                Bool _t3814 = Bool_not(_t3813);
                (void)_t3814;
                ;
                if (_t3814) {
                    Bool _t3811 = 0;
                    (void)_t3811;
                    is_fsf = _t3811;
                    ;
                }
                ;
            } else {
                Bool _t3815 = 0;
                (void)_t3815;
                is_fsf = _t3815;
                ;
            }
            ;
            U64 _t3889 = U64_clone(&(U64){saved});
            (void)_t3889;
            ;
            p->pos = _t3889;
            ;
            if (is_fsf) {
                Token *_t3836 = expect_token(p, TokenType_LParen());
                (void)_t3836;
                Str *_t3837 = Str_lit("Str", 3ULL);
                (void)_t3837;
                U64 _t3838; { U64 *_hp = (U64 *)Str_size(); _t3838 = *_hp; free(_hp); }
                (void)_t3838;
                Vec *pnames = Vec_new(_t3837, &(U64){_t3838});
                (void)pnames;
                Str_delete(_t3837, &(Bool){1});
                ;
                while (1) {
                    Bool _t3818 = check(p, TokenType_RParen());
                    (void)_t3818;
                    Bool _wcond3816 = Bool_not(_t3818);
                    (void)_wcond3816;
                    ;
                    if (_wcond3816) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *pn = expect_text(p, TokenType_Ident());
                    (void)pn;
                    Vec_push(pnames, pn);
                    Bool _t3819 = check(p, TokenType_Comma());
                    (void)_t3819;
                    if (_t3819) {
                        Token *_t3817 = advance(p);
                        (void)_t3817;
                    }
                    ;
                }
                Token *_t3839 = expect_token(p, TokenType_RParen());
                (void)_t3839;
                Token *_t3840 = expect_token(p, TokenType_LBrace());
                (void)_t3840;
                Expr *body = parse_block(p);
                (void)body;
                Str *_t3841 = Str_lit("Str", 3ULL);
                (void)_t3841;
                U64 _t3842; { U64 *_hp = (U64 *)Str_size(); _t3842 = *_hp; free(_hp); }
                (void)_t3842;
                Str *_t3843 = Str_lit("Str", 3ULL);
                (void)_t3843;
                U64 _t3844; { U64 *_hp = (U64 *)Str_size(); _t3844 = *_hp; free(_hp); }
                (void)_t3844;
                Str *_t3845 = Str_lit("Bool", 4ULL);
                (void)_t3845;
                U64 _t3846; { U64 *_hp = (U64 *)Bool_size(); _t3846 = *_hp; free(_hp); }
                (void)_t3846;
                Str *_t3847 = Str_lit("Bool", 4ULL);
                (void)_t3847;
                U64 _t3848; { U64 *_hp = (U64 *)Bool_size(); _t3848 = *_hp; free(_hp); }
                (void)_t3848;
                Str *_t3849 = Str_lit("Bool", 4ULL);
                (void)_t3849;
                U64 _t3850; { U64 *_hp = (U64 *)Bool_size(); _t3850 = *_hp; free(_hp); }
                (void)_t3850;
                Str *_t3851 = Str_lit("I64", 3ULL);
                (void)_t3851;
                U64 _t3852; { U64 *_hp = (U64 *)I64_size(); _t3852 = *_hp; free(_hp); }
                (void)_t3852;
                Str *_t3853 = Str_lit("Str", 3ULL);
                (void)_t3853;
                U64 _t3854; { U64 *_hp = (U64 *)Str_size(); _t3854 = *_hp; free(_hp); }
                (void)_t3854;
                Str *_t3855 = Str_lit("Expr", 4ULL);
                (void)_t3855;
                U64 _t3856; { U64 *_hp = (U64 *)Expr_size(); _t3856 = *_hp; free(_hp); }
                (void)_t3856;
                I64 _t3857 = 0;
                (void)_t3857;
                I64 _t3858 = 1;
                (void)_t3858;
                I64 _t3859 = I64_sub(_t3857, _t3858);
                (void)_t3859;
                ;
                ;
                I64 _t3860 = 0;
                (void)_t3860;
                I64 _t3861 = 1;
                (void)_t3861;
                I64 _t3862 = I64_sub(_t3860, _t3861);
                (void)_t3862;
                ;
                ;
                U32 _t3863 = 0;
                (void)_t3863;
                I32 _t3864 = I64_to_i32(_t3859);
                (void)_t3864;
                ;
                I32 _t3865 = I64_to_i32(_t3862);
                (void)_t3865;
                ;
                Bool _t3866 = 0;
                (void)_t3866;
                Bool _t3867 = 0;
                (void)_t3867;
                FunctionDef *ffd = malloc(sizeof(FunctionDef));
                { FuncType *_ca = FuncType_clone(FuncType_Func()); ffd->func_type = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3841, &(U64){_t3842}); ffd->param_names = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3843, &(U64){_t3844}); ffd->param_types = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3845, &(U64){_t3846}); ffd->param_muts = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3847, &(U64){_t3848}); ffd->param_owns = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3849, &(U64){_t3850}); ffd->param_shallows = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3851, &(U64){_t3852}); ffd->param_fn_sigs = *_ca; free(_ca); }
                ffd->nparam = _t3863;
                { Map *_ca = Map_new(_t3853, &(U64){_t3854}, _t3855, &(U64){_t3856}); ffd->param_defaults = *_ca; free(_ca); }
                { Str *_ca = Str_clone(Str_lit("", 0ULL)); ffd->return_type = *_ca; free(_ca); }
                ffd->variadic_index = _t3864;
                ffd->kwargs_index = _t3865;
                ffd->return_is_ref = _t3866;
                ffd->return_is_shallow = _t3867;
                (void)ffd;
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
                Str_delete(_t3851, &(Bool){1});
                ;
                Str_delete(_t3853, &(Bool){1});
                ;
                Str_delete(_t3855, &(Bool){1});
                ;
                ;
                ;
                ;
                ;
                ;
                FuncType_delete(&ffd->func_type, &(Bool){0});
                { FuncType *_fa = FuncType_clone(FuncType_Func()); ffd->func_type = *_fa; free(_fa); }
                I64 _t3868 = 0;
                (void)_t3868;
                I64 _t3869 = 1;
                (void)_t3869;
                I64 _t3870 = I64_sub(_t3868, _t3869);
                (void)_t3870;
                ;
                ;
                I32 _t3871 = I64_to_i32(_t3870);
                (void)_t3871;
                ;
                ffd->variadic_index = _t3871;
                ;
                I64 _t3872 = 0;
                (void)_t3872;
                I64 _t3873 = 1;
                (void)_t3873;
                I64 _t3874 = I64_sub(_t3872, _t3873);
                (void)_t3874;
                ;
                ;
                I32 _t3875 = I64_to_i32(_t3874);
                (void)_t3875;
                ;
                ffd->kwargs_index = _t3875;
                ;
                U64 np; { U64 *_hp = (U64 *)Vec_len(pnames); np = *_hp; free(_hp); }
                (void)np;
                {
                    U64 _fi3820 = 0;
                    (void)_fi3820;
                    while (1) {
                        U64 _t3822 = 0;
                        (void)_t3822;
                        Range *_t3823 = Range_new(_t3822, np);
                        (void)_t3823;
                        ;
                        U64 _t3824; { U64 *_hp = (U64 *)Range_len(_t3823); _t3824 = *_hp; free(_hp); }
                        (void)_t3824;
                        Range_delete(_t3823, &(Bool){1});
                        Bool _wcond3821; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3820}, &(U64){_t3824}); _wcond3821 = *_hp; free(_hp); }
                        (void)_wcond3821;
                        ;
                        if (_wcond3821) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 _t3825 = 0;
                        (void)_t3825;
                        Range *_t3826 = Range_new(_t3825, np);
                        (void)_t3826;
                        ;
                        U64 _; { U64 *_hp = (U64 *)Range_get(_t3826, _fi3820); _ = *_hp; free(_hp); }
                        (void)_;
                        ;
                        Range_delete(_t3826, &(Bool){1});
                        U64 _t3827 = 1;
                        (void)_t3827;
                        U64 _t3828 = U64_add(_fi3820, _t3827);
                        (void)_t3828;
                        ;
                        _fi3820 = _t3828;
                        ;
                        Str *_t3829 = Str_lit("", 0ULL);
                        (void)_t3829;
                        Vec_push(&ffd->param_types, _t3829);
                        Bool _t3830 = 0;
                        (void)_t3830;
                        Vec_push(&ffd->param_muts, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3830; _oa; }));
                        Bool _t3831 = 0;
                        (void)_t3831;
                        Vec_push(&ffd->param_owns, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3831; _oa; }));
                        Bool _t3832 = 0;
                        (void)_t3832;
                        Vec_push(&ffd->param_shallows, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3832; _oa; }));
                        I64 _t3833 = 0;
                        (void)_t3833;
                        I64 _t3834 = 1;
                        (void)_t3834;
                        I64 _t3835 = I64_sub(_t3833, _t3834);
                        (void)_t3835;
                        ;
                        ;
                        Vec_push(&ffd->param_fn_sigs, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = _t3835; _oa; }));
                    }
                    ;
                }
                Vec_delete(&ffd->param_names, &(Bool){0});
                { Vec *_fa = Vec_clone(pnames); ffd->param_names = *_fa; free(_fa); }
                Vec_delete(pnames, &(Bool){1});
                I64 _t3876 = U64_to_i64(np);
                (void)_t3876;
                ;
                U32 _t3877 = I64_to_u32(_t3876);
                (void)_t3877;
                ;
                ffd->nparam = _t3877;
                ;
                ExprData *_t3878 = ExprData_FuncDef(ffd);
                (void)_t3878;
                FunctionDef_delete(ffd, &(Bool){1});
                Expr *fdef = Expr_new(_t3878, t_line, t_col, &p->path);
                (void)fdef;
                ExprData_delete(_t3878, &(Bool){1});
                Expr_add_child(fdef, body);
                Bool _t3879 = Bool_clone(&(Bool){is_mut});
                (void)_t3879;
                Bool _t3880 = 0;
                (void)_t3880;
                Bool _t3881 = 0;
                (void)_t3881;
                Bool _t3882 = Bool_clone(&(Bool){is_own});
                (void)_t3882;
                I32 _t3883 = 0;
                (void)_t3883;
                I32 _t3884 = 0;
                (void)_t3884;
                Declaration *dd = malloc(sizeof(Declaration));
                { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
                { Str *_ca = Str_clone(type_name); dd->explicit_type = *_ca; free(_ca); }
                dd->is_mut = _t3879;
                dd->is_namespace = _t3880;
                dd->is_ref = _t3881;
                dd->is_own = _t3882;
                dd->field_offset = _t3883;
                dd->field_size = _t3884;
                dd->field_struct_def = NULL;
                dd->fn_sig = NULL;
                (void)dd;
                ;
                ;
                ;
                ;
                ;
                ;
                ExprData *_t3885 = ExprData_Decl(dd);
                (void)_t3885;
                Declaration_delete(dd, &(Bool){1});
                Expr *decl = Expr_new(_t3885, t_line, t_col, &p->path);
                (void)decl;
                ExprData_delete(_t3885, &(Bool){1});
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
        Bool _t3900 = Bool_clone(&(Bool){is_mut});
        (void)_t3900;
        Bool _t3901 = 0;
        (void)_t3901;
        Bool _t3902 = 0;
        (void)_t3902;
        Bool _t3903 = Bool_clone(&(Bool){is_own});
        (void)_t3903;
        I32 _t3904 = 0;
        (void)_t3904;
        I32 _t3905 = 0;
        (void)_t3905;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(type_name); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3900;
        dd->is_namespace = _t3901;
        dd->is_ref = _t3902;
        dd->is_own = _t3903;
        dd->field_offset = _t3904;
        dd->field_size = _t3905;
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
        ExprData *_t3906 = ExprData_Decl(dd);
        (void)_t3906;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3906, t_line, t_col, &p->path);
        (void)decl;
        ExprData_delete(_t3906, &(Bool){1});
        Expr *_t3907 = parse_expression(p);
        (void)_t3907;
        Expr_add_child(decl, _t3907);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return decl;
    }
    ;
    Bool _t3960 = check(p, TokenType_Dot());
    (void)_t3960;
    if (_t3960) {
        Str *_t3946 = Str_clone(name);
        (void)_t3946;
        ExprData *_t3947 = ExprData_Ident(_t3946);
        (void)_t3947;
        Str_delete(_t3946, &(Bool){1});
        Expr *obj = Expr_new(_t3947, t_line, t_col, &p->path);
        (void)obj;
        ExprData_delete(_t3947, &(Bool){1});
        Str *last_field = Str_lit("", 0ULL);
        (void)last_field;
        U32 last_line = 0;
        (void)last_line;
        U32 last_col = 0;
        (void)last_col;
        while (1) {
            Bool _wcond3908 = check(p, TokenType_Dot());
            (void)_wcond3908;
            if (_wcond3908) {
            } else {
                ;
                break;
            }
            ;
            Token *_t3912 = advance(p);
            (void)_t3912;
            U32 _t3913 = peek_line(p);
            (void)_t3913;
            last_line = _t3913;
            ;
            U32 _t3914 = peek_col(p);
            (void)_t3914;
            last_col = _t3914;
            ;
            last_field = expect_text(p, TokenType_Ident());
            Bool _t3915 = check(p, TokenType_Dot());
            (void)_t3915;
            if (_t3915) {
                Str *_t3909 = Str_clone(last_field);
                (void)_t3909;
                ExprData *_t3910 = ExprData_FieldAccess(_t3909);
                (void)_t3910;
                Str_delete(_t3909, &(Bool){1});
                Expr *access = Expr_new(_t3910, last_line, last_col, &p->path);
                (void)access;
                ExprData_delete(_t3910, &(Bool){1});
                Expr *_t3911 = Expr_clone(obj);
                (void)_t3911;
                Expr_add_child(access, _t3911);
                obj = Expr_clone(access);
                Expr_delete(access, &(Bool){1});
            }
            ;
        }
        Bool _t3948 = check(p, TokenType_LParen());
        (void)_t3948;
        if (_t3948) {
            Token *_t3942 = advance(p);
            (void)_t3942;
            ExprData *_t3943 = ExprData_FieldAccess(last_field);
            (void)_t3943;
            Expr *callee = Expr_new(_t3943, last_line, last_col, &p->path);
            (void)callee;
            ExprData_delete(_t3943, &(Bool){1});
            Expr *_t3944 = Expr_clone(obj);
            (void)_t3944;
            Expr_add_child(callee, _t3944);
            Expr *mcall = Expr_new(ExprData_FCall(), last_line, last_col, &p->path);
            (void)mcall;
            Expr_add_child(mcall, callee);
            while (1) {
                Bool _t3934 = check(p, TokenType_RParen());
                (void)_t3934;
                Bool _t3935 = check(p, TokenType_Eof());
                (void)_t3935;
                Bool _t3936 = Bool_not(_t3934);
                (void)_t3936;
                ;
                Bool _t3937 = Bool_not(_t3935);
                (void)_t3937;
                ;
                Bool _wcond3916 = Bool_and(_t3936, _t3937);
                (void)_wcond3916;
                ;
                ;
                if (_wcond3916) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3938 = check(p, TokenType_Ident());
                (void)_t3938;
                if (_t3938) {
                    U64 _t3927 = 1;
                    (void)_t3927;
                    U64 _t3928 = U64_add(p->pos, _t3927);
                    (void)_t3928;
                    ;
                    U64 _t3929; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3929 = *_hp; free(_hp); }
                    (void)_t3929;
                    Bool _t3930; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3928}, &(U64){_t3929}); _t3930 = *_hp; free(_hp); }
                    (void)_t3930;
                    ;
                    ;
                    if (_t3930) {
                        U64 _t3922 = 1;
                        (void)_t3922;
                        U64 _t3923 = U64_add(p->pos, _t3922);
                        (void)_t3923;
                        ;
                        I64 _t3924 = U64_to_i64(_t3923);
                        (void)_t3924;
                        ;
                        U64 *_t3925 = malloc(sizeof(U64)); *_t3925 = I64_to_u64(_t3924);
                        (void)_t3925;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3925);
                        (void)nt;
                        Bool _t3926; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3926 = *_hp; free(_hp); }
                        (void)_t3926;
                        U64_delete(_t3925, &(Bool){1});
                        if (_t3926) {
                            U32 na_line = peek_line(p);
                            (void)na_line;
                            U32 na_col = peek_col(p);
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3918 = advance(p);
                            (void)_t3918;
                            ExprData *_t3919 = ExprData_NamedArg(aname);
                            (void)_t3919;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3919, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3919, &(Bool){1});
                            ;
                            ;
                            Expr *_t3920 = parse_expression(p);
                            (void)_t3920;
                            Expr_add_child(na, _t3920);
                            Expr_add_child(mcall, na);
                            Bool _t3921 = check(p, TokenType_Comma());
                            (void)_t3921;
                            if (_t3921) {
                                Token *_t3917 = advance(p);
                                (void)_t3917;
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
                Bool _t3939 = check(p, TokenType_KwOwn());
                (void)_t3939;
                if (_t3939) {
                    Token *_t3931 = advance(p);
                    (void)_t3931;
                    Bool _t3932 = 1;
                    (void)_t3932;
                    is_own_arg = _t3932;
                    ;
                }
                ;
                Expr *marg = parse_expression(p);
                (void)marg;
                Bool _t3940 = Bool_clone(&(Bool){is_own_arg});
                (void)_t3940;
                ;
                marg->is_own_arg = _t3940;
                ;
                Expr_add_child(mcall, marg);
                Bool _t3941 = check(p, TokenType_Comma());
                (void)_t3941;
                if (_t3941) {
                    Token *_t3933 = advance(p);
                    (void)_t3933;
                }
                ;
            }
            Token *_t3945 = expect_token(p, TokenType_RParen());
            (void)_t3945;
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
        Token *_t3949 = expect_token(p, TokenType_Eq());
        (void)_t3949;
        ExprData *_t3950 = ExprData_FieldAssign(last_field);
        (void)_t3950;
        Str_delete(last_field, &(Bool){1});
        Expr *fa = Expr_new(_t3950, t_line, t_col, &p->path);
        (void)fa;
        ExprData_delete(_t3950, &(Bool){1});
        Expr *_t3951 = Expr_clone(obj);
        (void)_t3951;
        Expr_delete(obj, &(Bool){1});
        Expr_add_child(fa, _t3951);
        Expr *_t3952 = parse_expression(p);
        (void)_t3952;
        Expr_add_child(fa, _t3952);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return fa;
    }
    ;
    Bool _t3961 = check(p, TokenType_Eq());
    (void)_t3961;
    if (_t3961) {
        Token *_t3953 = advance(p);
        (void)_t3953;
        Str *_t3954 = Str_clone(name);
        (void)_t3954;
        ExprData *_t3955 = ExprData_Assign(_t3954);
        (void)_t3955;
        Str_delete(_t3954, &(Bool){1});
        Expr *assign = Expr_new(_t3955, t_line, t_col, &p->path);
        (void)assign;
        ExprData_delete(_t3955, &(Bool){1});
        Expr *_t3956 = parse_expression(p);
        (void)_t3956;
        Expr_add_child(assign, _t3956);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return assign;
    }
    ;
    Bool _t3962 = check(p, TokenType_LParen());
    (void)_t3962;
    if (_t3962) {
        Expr *_t3957 = parse_call(p, name, t_line, t_col);
        (void)_t3957;
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return _t3957;
    }
    ;
    Str *_t3963 = Str_lit("Str", 3ULL);
    (void)_t3963;
    U64 _t3964; { U64 *_hp = (U64 *)Str_size(); _t3964 = *_hp; free(_hp); }
    (void)_t3964;
    U64 _t3965 = 8;
    (void)_t3965;
    Array *_va69 = Array_new(_t3963, &(U64){_t3964}, &(U64){_t3965});
    (void)_va69;
    Str_delete(_t3963, &(Bool){1});
    ;
    ;
    U64 _t3966 = 0;
    (void)_t3966;
    Str *_t3967 = Str_clone(&p->path);
    (void)_t3967;
    Array_set(_va69, &(U64){_t3966}, _t3967);
    ;
    U64 _t3968 = 1;
    (void)_t3968;
    Str *_t3969 = Str_lit(":", 1ULL);
    (void)_t3969;
    Array_set(_va69, &(U64){_t3968}, _t3969);
    ;
    U64 _t3970 = 2;
    (void)_t3970;
    Str *_t3971 = U32_to_str(&(U32){t_line});
    (void)_t3971;
    ;
    Array_set(_va69, &(U64){_t3970}, _t3971);
    ;
    U64 _t3972 = 3;
    (void)_t3972;
    Str *_t3973 = Str_lit(":", 1ULL);
    (void)_t3973;
    Array_set(_va69, &(U64){_t3972}, _t3973);
    ;
    U64 _t3974 = 4;
    (void)_t3974;
    Str *_t3975 = U32_to_str(&(U32){t_col});
    (void)_t3975;
    ;
    Array_set(_va69, &(U64){_t3974}, _t3975);
    ;
    U64 _t3976 = 5;
    (void)_t3976;
    Str *_t3977 = Str_lit(": expected ':=', ':', '=' or '(' after identifier '", 51ULL);
    (void)_t3977;
    Array_set(_va69, &(U64){_t3976}, _t3977);
    ;
    U64 _t3978 = 6;
    (void)_t3978;
    Str *_t3979 = Str_clone(name);
    (void)_t3979;
    Str_delete(name, &(Bool){1});
    Array_set(_va69, &(U64){_t3978}, _t3979);
    ;
    U64 _t3980 = 7;
    (void)_t3980;
    Str *_t3981 = Str_lit("'", 1ULL);
    (void)_t3981;
    Array_set(_va69, &(U64){_t3980}, _t3981);
    ;
    Str *_t3982 = Str_lit("src/self/parser.til:785:11", 26ULL);
    (void)_t3982;
    panic(_t3982, _va69);
    Str_delete(_t3982, &(Bool){1});
    U32 _t3983 = 0;
    (void)_t3983;
    U32 _t3984 = 0;
    (void)_t3984;
    Expr *_t3985 = Expr_new(ExprData_Body(), _t3983, _t3984, &p->path);
    (void)_t3985;
    ;
    ;
    return _t3985;
}

Expr * parse_statement(Parser * p) {
    (void)p;
    U32 t_line = peek_line(p);
    (void)t_line;
    U32 t_col = peek_col(p);
    (void)t_col;
    Token *t = peek(p);
    (void)t;
    Bool _t4123; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t4123 = *_hp; free(_hp); }
    (void)_t4123;
    if (_t4123) {
        Bool _t3986 = 0;
        (void)_t3986;
        Bool _t3987 = 0;
        (void)_t3987;
        Expr *_t3988 = parse_statement_ident(p, _t3986, _t3987);
        (void)_t3988;
        ;
        ;
        ;
        ;
        ;
        return _t3988;
    }
    ;
    Bool _t4124; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwRef()); _t4124 = *_hp; free(_hp); }
    (void)_t4124;
    if (_t4124) {
        Token *_t3995 = advance(p);
        (void)_t3995;
        Bool ref_mut = 0;
        (void)ref_mut;
        Bool _t3996 = check(p, TokenType_KwMut());
        (void)_t3996;
        if (_t3996) {
            Token *_t3989 = advance(p);
            (void)_t3989;
            Bool _t3990 = 1;
            (void)_t3990;
            ref_mut = _t3990;
            ;
        }
        ;
        U32 i_line = peek_line(p);
        (void)i_line;
        U32 i_col = peek_col(p);
        (void)i_col;
        Str *iname = expect_text(p, TokenType_Ident());
        (void)iname;
        Bool _t3997 = 0;
        (void)_t3997;
        Bool _t3998 = 0;
        (void)_t3998;
        Bool _t3999 = 1;
        (void)_t3999;
        Bool _t4000 = 0;
        (void)_t4000;
        I32 _t4001 = 0;
        (void)_t4001;
        I32 _t4002 = 0;
        (void)_t4002;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(iname); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3997;
        dd->is_namespace = _t3998;
        dd->is_ref = _t3999;
        dd->is_own = _t4000;
        dd->field_offset = _t4001;
        dd->field_size = _t4002;
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
            Bool _t3991 = 1;
            (void)_t3991;
            dd->is_mut = _t3991;
            ;
        }
        ;
        Bool _t4003 = check(p, TokenType_Colon());
        (void)_t4003;
        if (_t4003) {
            Token *_t3992 = advance(p);
            (void)_t3992;
            Str_delete(&dd->explicit_type, &(Bool){0});
            { Str *_fa = expect_text(p, TokenType_Ident()); dd->explicit_type = *_fa; free(_fa); }
            Token *_t3993 = expect_token(p, TokenType_Eq());
            (void)_t3993;
        } else {
            Token *_t3994 = expect_token(p, TokenType_ColonEq());
            (void)_t3994;
        }
        ;
        ExprData *_t4004 = ExprData_Decl(dd);
        (void)_t4004;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t4004, i_line, i_col, &p->path);
        (void)decl;
        ExprData_delete(_t4004, &(Bool){1});
        ;
        ;
        Expr *_t4005 = parse_expression(p);
        (void)_t4005;
        Expr_add_child(decl, _t4005);
        ;
        ;
        ;
        return decl;
    }
    ;
    Bool _t4125; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMut()); _t4125 = *_hp; free(_hp); }
    (void)_t4125;
    if (_t4125) {
        Token *_t4006 = advance(p);
        (void)_t4006;
        Bool _t4007 = 1;
        (void)_t4007;
        Bool _t4008 = 0;
        (void)_t4008;
        Expr *_t4009 = parse_statement_ident(p, _t4007, _t4008);
        (void)_t4009;
        ;
        ;
        ;
        ;
        ;
        return _t4009;
    }
    ;
    Bool _t4126; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwReturn()); _t4126 = *_hp; free(_hp); }
    (void)_t4126;
    if (_t4126) {
        Token *_t4011 = advance(p);
        (void)_t4011;
        Expr *ret = Expr_new(ExprData_Return(), t_line, t_col, &p->path);
        (void)ret;
        Bool _t4012 = check(p, TokenType_RBrace());
        (void)_t4012;
        Bool _t4013 = check(p, TokenType_Eof());
        (void)_t4013;
        Bool _t4014 = Bool_not(_t4012);
        (void)_t4014;
        ;
        Bool _t4015 = Bool_not(_t4013);
        (void)_t4015;
        ;
        Bool _t4016 = Bool_and(_t4014, _t4015);
        (void)_t4016;
        ;
        ;
        if (_t4016) {
            Expr *_t4010 = parse_expression(p);
            (void)_t4010;
            Expr_add_child(ret, _t4010);
        }
        ;
        ;
        ;
        ;
        return ret;
    }
    ;
    Bool _t4127; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwIf()); _t4127 = *_hp; free(_hp); }
    (void)_t4127;
    if (_t4127) {
        Token *_t4024 = advance(p);
        (void)_t4024;
        Expr *node = Expr_new(ExprData_If(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t4025 = parse_expression(p);
        (void)_t4025;
        Expr_add_child(node, _t4025);
        Token *_t4026 = expect_token(p, TokenType_LBrace());
        (void)_t4026;
        Expr *_t4027 = parse_block(p);
        (void)_t4027;
        Expr_add_child(node, _t4027);
        Bool _t4028 = check(p, TokenType_KwElse());
        (void)_t4028;
        if (_t4028) {
            Token *_t4022 = advance(p);
            (void)_t4022;
            Bool _t4023 = check(p, TokenType_KwIf());
            (void)_t4023;
            if (_t4023) {
                U32 _t4017 = peek_line(p);
                (void)_t4017;
                U32 _t4018 = peek_col(p);
                (void)_t4018;
                Expr *else_body = Expr_new(ExprData_Body(), _t4017, _t4018, &p->path);
                (void)else_body;
                ;
                ;
                Expr *_t4019 = parse_statement(p);
                (void)_t4019;
                Expr_add_child(else_body, _t4019);
                Expr_add_child(node, else_body);
            } else {
                Token *_t4020 = expect_token(p, TokenType_LBrace());
                (void)_t4020;
                Expr *_t4021 = parse_block(p);
                (void)_t4021;
                Expr_add_child(node, _t4021);
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
    Bool _t4128; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t4128 = *_hp; free(_hp); }
    (void)_t4128;
    Bool _t4129; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t4129 = *_hp; free(_hp); }
    (void)_t4129;
    Bool _t4130 = Bool_or(_t4128, _t4129);
    (void)_t4130;
    ;
    ;
    Bool _t4131; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t4131 = *_hp; free(_hp); }
    (void)_t4131;
    Bool _t4132 = Bool_or(_t4130, _t4131);
    (void)_t4132;
    ;
    ;
    Bool _t4133; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t4133 = *_hp; free(_hp); }
    (void)_t4133;
    Bool _t4134 = Bool_or(_t4132, _t4133);
    (void)_t4134;
    ;
    ;
    Bool _t4135; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwNull()); _t4135 = *_hp; free(_hp); }
    (void)_t4135;
    Bool _t4136 = Bool_or(_t4134, _t4135);
    (void)_t4136;
    ;
    ;
    if (_t4136) {
        Expr *_t4029 = parse_expression(p);
        (void)_t4029;
        ;
        ;
        ;
        return _t4029;
    }
    ;
    Bool _t4137; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t4137 = *_hp; free(_hp); }
    (void)_t4137;
    if (_t4137) {
        Token *_t4030 = advance(p);
        (void)_t4030;
        Expr *_t4031 = parse_block(p);
        (void)_t4031;
        ;
        ;
        ;
        return _t4031;
    }
    ;
    Bool _t4138; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwWhile()); _t4138 = *_hp; free(_hp); }
    (void)_t4138;
    if (_t4138) {
        Token *_t4032 = advance(p);
        (void)_t4032;
        Expr *node = Expr_new(ExprData_While(), t_line, t_col, &p->path);
        (void)node;
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
    Bool _t4139; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFor()); _t4139 = *_hp; free(_hp); }
    (void)_t4139;
    if (_t4139) {
        Token *_t4037 = advance(p);
        (void)_t4037;
        U32 i_line = peek_line(p);
        (void)i_line;
        U32 i_col = peek_col(p);
        (void)i_col;
        Str *iname = expect_text(p, TokenType_Ident());
        (void)iname;
        ExprData *_t4038 = ExprData_ForIn(iname);
        (void)_t4038;
        Str_delete(iname, &(Bool){1});
        Expr *node = Expr_new(_t4038, i_line, i_col, &p->path);
        (void)node;
        ExprData_delete(_t4038, &(Bool){1});
        ;
        ;
        Bool _t4039 = check(p, TokenType_Colon());
        (void)_t4039;
        if (_t4039) {
            Token *_t4036 = advance(p);
            (void)_t4036;
            Str_delete(&node->struct_name, &(Bool){0});
            { Str *_fa = expect_text(p, TokenType_Ident()); node->struct_name = *_fa; free(_fa); }
        }
        ;
        Token *_t4040 = expect_token(p, TokenType_KwIn());
        (void)_t4040;
        Expr *_t4041 = parse_expression(p);
        (void)_t4041;
        Expr_add_child(node, _t4041);
        Token *_t4042 = expect_token(p, TokenType_LBrace());
        (void)_t4042;
        Expr *_t4043 = parse_block(p);
        (void)_t4043;
        Expr_add_child(node, _t4043);
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4140; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwSwitch()); _t4140 = *_hp; free(_hp); }
    (void)_t4140;
    if (_t4140) {
        Token *_t4067 = advance(p);
        (void)_t4067;
        Expr *node = Expr_new(ExprData_Switch(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t4068 = parse_expression(p);
        (void)_t4068;
        Expr_add_child(node, _t4068);
        Token *_t4069 = expect_token(p, TokenType_LBrace());
        (void)_t4069;
        while (1) {
            Bool _t4055 = check(p, TokenType_RBrace());
            (void)_t4055;
            Bool _t4056 = check(p, TokenType_Eof());
            (void)_t4056;
            Bool _t4057 = Bool_not(_t4055);
            (void)_t4057;
            ;
            Bool _t4058 = Bool_not(_t4056);
            (void)_t4058;
            ;
            Bool _wcond4044 = Bool_and(_t4057, _t4058);
            (void)_wcond4044;
            ;
            ;
            if (_wcond4044) {
            } else {
                ;
                break;
            }
            ;
            Token *_t4059 = expect_token(p, TokenType_KwCase());
            (void)_t4059;
            U32 _t4060 = peek_line(p);
            (void)_t4060;
            U32 _t4061 = peek_col(p);
            (void)_t4061;
            Expr *cn = Expr_new(ExprData_Case(), _t4060, _t4061, &p->path);
            (void)cn;
            ;
            ;
            Bool _t4062 = check(p, TokenType_Colon());
            (void)_t4062;
            Bool _t4063 = Bool_not(_t4062);
            (void)_t4063;
            ;
            if (_t4063) {
                Expr *_t4045 = parse_expression(p);
                (void)_t4045;
                Expr_add_child(cn, _t4045);
            }
            ;
            Token *_t4064 = expect_token(p, TokenType_Colon());
            (void)_t4064;
            U32 _t4065 = peek_line(p);
            (void)_t4065;
            U32 _t4066 = peek_col(p);
            (void)_t4066;
            Expr *cb = Expr_new(ExprData_Body(), _t4065, _t4066, &p->path);
            (void)cb;
            ;
            ;
            while (1) {
                Bool _t4047 = check(p, TokenType_KwCase());
                (void)_t4047;
                Bool _t4048 = check(p, TokenType_RBrace());
                (void)_t4048;
                Bool _t4049 = Bool_not(_t4047);
                (void)_t4049;
                ;
                Bool _t4050 = Bool_not(_t4048);
                (void)_t4050;
                ;
                Bool _t4051 = check(p, TokenType_Eof());
                (void)_t4051;
                Bool _t4052 = Bool_and(_t4049, _t4050);
                (void)_t4052;
                ;
                ;
                Bool _t4053 = Bool_not(_t4051);
                (void)_t4053;
                ;
                Bool _wcond4046 = Bool_and(_t4052, _t4053);
                (void)_wcond4046;
                ;
                ;
                if (_wcond4046) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t4054 = parse_statement(p);
                (void)_t4054;
                Expr_add_child(cb, _t4054);
            }
            Expr_add_child(cn, cb);
            Expr_add_child(node, cn);
        }
        Token *_t4070 = expect_token(p, TokenType_RBrace());
        (void)_t4070;
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4141; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwOwn()); _t4141 = *_hp; free(_hp); }
    (void)_t4141;
    if (_t4141) {
        Token *_t4112 = advance(p);
        (void)_t4112;
        Bool _t4113 = check(p, TokenType_Ident());
        (void)_t4113;
        Bool _t4114 = check(p, TokenType_KwMut());
        (void)_t4114;
        Bool _t4115 = Bool_or(_t4113, _t4114);
        (void)_t4115;
        ;
        ;
        if (_t4115) {
            Bool own_mut = 0;
            (void)own_mut;
            Bool _t4102 = check(p, TokenType_KwMut());
            (void)_t4102;
            if (_t4102) {
                Token *_t4071 = advance(p);
                (void)_t4071;
                Bool _t4072 = 1;
                (void)_t4072;
                own_mut = _t4072;
                ;
            }
            ;
            Bool _t4103 = check(p, TokenType_Ident());
            (void)_t4103;
            if (_t4103) {
                U64 _t4082 = 1;
                (void)_t4082;
                U64 _t4083 = U64_add(p->pos, _t4082);
                (void)_t4083;
                ;
                U64 _t4084; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t4084 = *_hp; free(_hp); }
                (void)_t4084;
                Bool _t4085; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4083}, &(U64){_t4084}); _t4085 = *_hp; free(_hp); }
                (void)_t4085;
                ;
                ;
                if (_t4085) {
                    U64 _t4075 = 1;
                    (void)_t4075;
                    U64 _t4076 = U64_add(p->pos, _t4075);
                    (void)_t4076;
                    ;
                    I64 _t4077 = U64_to_i64(_t4076);
                    (void)_t4077;
                    ;
                    U64 *_t4078 = malloc(sizeof(U64)); *_t4078 = I64_to_u64(_t4077);
                    (void)_t4078;
                    ;
                    Token *nt = Vec_get(&p->tokens, _t4078);
                    (void)nt;
                    Bool _t4079; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_ColonEq()); _t4079 = *_hp; free(_hp); }
                    (void)_t4079;
                    Bool _t4080; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Colon()); _t4080 = *_hp; free(_hp); }
                    (void)_t4080;
                    U64_delete(_t4078, &(Bool){1});
                    Bool _t4081 = Bool_or(_t4079, _t4080);
                    (void)_t4081;
                    ;
                    ;
                    if (_t4081) {
                        Bool _t4073 = 1;
                        (void)_t4073;
                        Expr *_t4074 = parse_statement_ident(p, own_mut, _t4073);
                        (void)_t4074;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        return _t4074;
                    }
                    ;
                }
                ;
            }
            ;
            if (own_mut) {
                Str *_t4086 = Str_lit("Str", 3ULL);
                (void)_t4086;
                U64 _t4087; { U64 *_hp = (U64 *)Str_size(); _t4087 = *_hp; free(_hp); }
                (void)_t4087;
                U64 _t4088 = 6;
                (void)_t4088;
                Array *_va70 = Array_new(_t4086, &(U64){_t4087}, &(U64){_t4088});
                (void)_va70;
                Str_delete(_t4086, &(Bool){1});
                ;
                ;
                U64 _t4089 = 0;
                (void)_t4089;
                Str *_t4090 = Str_clone(&p->path);
                (void)_t4090;
                Array_set(_va70, &(U64){_t4089}, _t4090);
                ;
                U64 _t4091 = 1;
                (void)_t4091;
                Str *_t4092 = Str_lit(":", 1ULL);
                (void)_t4092;
                Array_set(_va70, &(U64){_t4091}, _t4092);
                ;
                U64 _t4093 = 2;
                (void)_t4093;
                Str *_t4094 = U32_to_str(&(U32){t_line});
                (void)_t4094;
                Array_set(_va70, &(U64){_t4093}, _t4094);
                ;
                U64 _t4095 = 3;
                (void)_t4095;
                Str *_t4096 = Str_lit(":", 1ULL);
                (void)_t4096;
                Array_set(_va70, &(U64){_t4095}, _t4096);
                ;
                U64 _t4097 = 4;
                (void)_t4097;
                Str *_t4098 = U32_to_str(&(U32){t_col});
                (void)_t4098;
                Array_set(_va70, &(U64){_t4097}, _t4098);
                ;
                U64 _t4099 = 5;
                (void)_t4099;
                Str *_t4100 = Str_lit(": expected identifier after 'own mut'", 37ULL);
                (void)_t4100;
                Array_set(_va70, &(U64){_t4099}, _t4100);
                ;
                Str *_t4101 = Str_lit("src/self/parser.til:919:23", 26ULL);
                (void)_t4101;
                panic(_t4101, _va70);
                Str_delete(_t4101, &(Bool){1});
            }
            ;
        }
        ;
        Expr *expr = parse_expression(p);
        (void)expr;
        I64 _t4116 = 0;
        (void)_t4116;
        I64 _t4117 = 1;
        (void)_t4117;
        I64 primary_idx = I64_sub(_t4116, _t4117);
        (void)primary_idx;
        ;
        ;
        ;
        Expr *cur = Expr_clone(expr);
        (void)cur;
        while (1) {
            U64 _t4105; { U64 *_hp = (U64 *)Vec_len(&cur->children); _t4105 = *_hp; free(_hp); }
            (void)_t4105;
            U64 _t4106 = 0;
            (void)_t4106;
            Bool _t4107; { Bool *_hp = (Bool *)ExprData_is_FCall(&cur->data); _t4107 = *_hp; free(_hp); }
            (void)_t4107;
            Bool _t4108; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(&cur->data); _t4108 = *_hp; free(_hp); }
            (void)_t4108;
            Bool _t4109; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4105}, &(U64){_t4106}); _t4109 = *_hp; free(_hp); }
            (void)_t4109;
            ;
            ;
            Bool _t4110 = Bool_or(_t4107, _t4108);
            (void)_t4110;
            ;
            ;
            Bool _wcond4104 = Bool_and(_t4109, _t4110);
            (void)_wcond4104;
            ;
            ;
            if (_wcond4104) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t4111 = malloc(sizeof(U64));
            *_t4111 = 0;
            (void)_t4111;
            Expr *ch = Vec_get(&cur->children, _t4111);
            (void)ch;
            cur = Expr_clone(ch);
            U64_delete(_t4111, &(Bool){1});
        }
        Bool _t4118 = 1;
        (void)_t4118;
        cur->is_own_arg = _t4118;
        ;
        Expr_delete(cur, &(Bool){1});
        ;
        ;
        ;
        ;
        return expr;
    }
    ;
    Bool _t4142; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwBreak()); _t4142 = *_hp; free(_hp); }
    (void)_t4142;
    if (_t4142) {
        Token *_t4119 = advance(p);
        (void)_t4119;
        Expr *_t4120 = Expr_new(ExprData_Break(), t_line, t_col, &p->path);
        (void)_t4120;
        ;
        ;
        ;
        return _t4120;
    }
    ;
    Bool _t4143; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwContinue()); _t4143 = *_hp; free(_hp); }
    (void)_t4143;
    if (_t4143) {
        Token *_t4121 = advance(p);
        (void)_t4121;
        Expr *_t4122 = Expr_new(ExprData_Continue(), t_line, t_col, &p->path);
        (void)_t4122;
        ;
        ;
        ;
        return _t4122;
    }
    ;
    Str *_t4144 = Str_lit("Str", 3ULL);
    (void)_t4144;
    U64 _t4145; { U64 *_hp = (U64 *)Str_size(); _t4145 = *_hp; free(_hp); }
    (void)_t4145;
    U64 _t4146 = 8;
    (void)_t4146;
    Array *_va71 = Array_new(_t4144, &(U64){_t4145}, &(U64){_t4146});
    (void)_va71;
    Str_delete(_t4144, &(Bool){1});
    ;
    ;
    U64 _t4147 = 0;
    (void)_t4147;
    Str *_t4148 = Str_clone(&p->path);
    (void)_t4148;
    Array_set(_va71, &(U64){_t4147}, _t4148);
    ;
    U64 _t4149 = 1;
    (void)_t4149;
    Str *_t4150 = Str_lit(":", 1ULL);
    (void)_t4150;
    Array_set(_va71, &(U64){_t4149}, _t4150);
    ;
    U64 _t4151 = 2;
    (void)_t4151;
    Str *_t4152 = U32_to_str(&(U32){t_line});
    (void)_t4152;
    ;
    Array_set(_va71, &(U64){_t4151}, _t4152);
    ;
    U64 _t4153 = 3;
    (void)_t4153;
    Str *_t4154 = Str_lit(":", 1ULL);
    (void)_t4154;
    Array_set(_va71, &(U64){_t4153}, _t4154);
    ;
    U64 _t4155 = 4;
    (void)_t4155;
    Str *_t4156 = U32_to_str(&(U32){t_col});
    (void)_t4156;
    ;
    Array_set(_va71, &(U64){_t4155}, _t4156);
    ;
    U64 _t4157 = 5;
    (void)_t4157;
    Str *_t4158 = Str_lit(": expected statement, found '", 29ULL);
    (void)_t4158;
    Array_set(_va71, &(U64){_t4157}, _t4158);
    ;
    U64 _t4159 = 6;
    (void)_t4159;
    Str *_t4160 = Str_clone(&t->text);
    (void)_t4160;
    Array_set(_va71, &(U64){_t4159}, _t4160);
    ;
    U64 _t4161 = 7;
    (void)_t4161;
    Str *_t4162 = Str_lit("'", 1ULL);
    (void)_t4162;
    Array_set(_va71, &(U64){_t4161}, _t4162);
    ;
    Str *_t4163 = Str_lit("src/self/parser.til:946:11", 26ULL);
    (void)_t4163;
    panic(_t4163, _va71);
    Str_delete(_t4163, &(Bool){1});
    U32 _t4164 = 0;
    (void)_t4164;
    U32 _t4165 = 0;
    (void)_t4165;
    Expr *_t4166 = Expr_new(ExprData_Body(), _t4164, _t4165, &p->path);
    (void)_t4166;
    ;
    ;
    return _t4166;
}

Expr * parse(Vec * tokens, Str * path, Str * mode_out) {
    (void)tokens;
    (void)path;
    (void)mode_out;
    I64 _t4178 = 0;
    (void)_t4178;
    Parser *p = malloc(sizeof(Parser));
    { Vec *_ca = Vec_clone(tokens); p->tokens = *_ca; free(_ca); }
    p->pos = _t4178;
    { Str *_ca = Str_clone(path); p->path = *_ca; free(_ca); }
    (void)p;
    ;
    Bool _t4179 = check(p, TokenType_KwMode());
    (void)_t4179;
    if (_t4179) {
        Token *_t4171 = advance(p);
        (void)_t4171;
        Bool _t4172 = check(p, TokenType_Ident());
        (void)_t4172;
        Bool _t4173 = check(p, TokenType_KwTest());
        (void)_t4173;
        Bool _t4174 = Bool_or(_t4172, _t4173);
        (void)_t4174;
        ;
        ;
        if (_t4174) {
            Str *_t4167 = Str_clone(&peek(p)->text);
            (void)_t4167;
            U64 _t4168; { U64 *_hp = (U64 *)Str_size(); _t4168 = *_hp; free(_hp); }
            (void)_t4168;
            swap(mode_out, _t4167, _t4168);
            Str_delete(_t4167, &(Bool){1});
            ;
            Token *_t4169 = advance(p);
            (void)_t4169;
        } else {
            Token *_t4170 = expect_token(p, TokenType_Ident());
            (void)_t4170;
        }
        ;
    }
    ;
    U32 _t4180 = 1;
    (void)_t4180;
    U32 _t4181 = 1;
    (void)_t4181;
    Expr *root = Expr_new(ExprData_Body(), _t4180, _t4181, &p->path);
    (void)root;
    ;
    ;
    while (1) {
        Bool _t4176 = check(p, TokenType_Eof());
        (void)_t4176;
        Bool _wcond4175 = Bool_not(_t4176);
        (void)_wcond4175;
        ;
        if (_wcond4175) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t4177 = parse_statement(p);
        (void)_t4177;
        Expr_add_child(root, _t4177);
    }
    Parser_delete(p, &(Bool){1});
    return root;
}

