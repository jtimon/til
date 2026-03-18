#include "parser_parser.h"

Parser * Parser_clone(Parser * self) {
    (void)self;
    U32 _t3042 = U32_clone(&self->count);
    (void)_t3042;
    U32 _t3043 = U32_clone(&self->pos);
    (void)_t3043;
    Parser *_t3044 = malloc(sizeof(Parser));
    { Vec *_ca = Vec_clone(&self->tokens); _t3044->tokens = *_ca; free(_ca); }
    _t3044->count = _t3042;
    _t3044->pos = _t3043;
    { Str *_ca = Str_clone(&self->path); _t3044->path = *_ca; free(_ca); }
    (void)_t3044;
    ;
    ;
    return _t3044;
}

U64 *Parser_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Parser);
    return r;
}

Token * peek(Parser * p) {
    (void)p;
    I64 _t3050 = U32_to_i64(p->pos);
    (void)_t3050;
    U64 *_t3051 = malloc(sizeof(U64)); *_t3051 = I64_to_u64(_t3050);
    (void)_t3051;
    ;
    Token *t = Vec_get(&p->tokens, _t3051);
    (void)t;
    U64_delete(_t3051, &(Bool){1});
    return t;
}

Token * advance(Parser * p) {
    (void)p;
    I64 _t3054 = U32_to_i64(p->pos);
    (void)_t3054;
    U64 *_t3055 = malloc(sizeof(U64)); *_t3055 = I64_to_u64(_t3054);
    (void)_t3055;
    ;
    Token *t = Vec_get(&p->tokens, _t3055);
    (void)t;
    Bool _t3056; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Eof()); _t3056 = *_hp; free(_hp); }
    (void)_t3056;
    Bool _t3057 = Bool_not(_t3056);
    (void)_t3057;
    ;
    if (_t3057) {
        U32 _t3052 = 1;
        (void)_t3052;
        U32 _t3053 = U32_add(p->pos, _t3052);
        (void)_t3053;
        ;
        p->pos = _t3053;
        ;
    }
    ;
    U64_delete(_t3055, &(Bool){1});
    return t;
}

Bool check(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Bool _t3058; { Bool *_hp = (Bool *)TokenType_eq(&peek(p)->type, type); _t3058 = *_hp; free(_hp); }
    (void)_t3058;
    return _t3058;
}

Token * expect_token(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Token *t = peek(p);
    (void)t;
    Bool _t3083; { Bool *_hp = (Bool *)TokenType_eq(&t->type, type); _t3083 = *_hp; free(_hp); }
    (void)_t3083;
    Bool _t3084 = Bool_not(_t3083);
    (void)_t3084;
    ;
    if (_t3084) {
        Str *_t3059 = Str_lit("Str", 3ULL);
        (void)_t3059;
        U64 _t3060; { U64 *_hp = (U64 *)Str_size(); _t3060 = *_hp; free(_hp); }
        (void)_t3060;
        U64 _t3061 = 10;
        (void)_t3061;
        Array *_va54 = Array_new(_t3059, &(U64){_t3060}, &(U64){_t3061});
        (void)_va54;
        Str_delete(_t3059, &(Bool){1});
        ;
        ;
        U64 _t3062 = 0;
        (void)_t3062;
        Str *_t3063 = Str_clone(&p->path);
        (void)_t3063;
        Array_set(_va54, &(U64){_t3062}, _t3063);
        ;
        U64 _t3064 = 1;
        (void)_t3064;
        Str *_t3065 = Str_lit(":", 1ULL);
        (void)_t3065;
        Array_set(_va54, &(U64){_t3064}, _t3065);
        ;
        U64 _t3066 = 2;
        (void)_t3066;
        Str *_t3067 = U32_to_str(&t->line);
        (void)_t3067;
        Array_set(_va54, &(U64){_t3066}, _t3067);
        ;
        U64 _t3068 = 3;
        (void)_t3068;
        Str *_t3069 = Str_lit(":", 1ULL);
        (void)_t3069;
        Array_set(_va54, &(U64){_t3068}, _t3069);
        ;
        U64 _t3070 = 4;
        (void)_t3070;
        Str *_t3071 = U32_to_str(&t->col);
        (void)_t3071;
        Array_set(_va54, &(U64){_t3070}, _t3071);
        ;
        U64 _t3072 = 5;
        (void)_t3072;
        Str *_t3073 = Str_lit(": expected '", 12ULL);
        (void)_t3073;
        Array_set(_va54, &(U64){_t3072}, _t3073);
        ;
        U64 _t3074 = 6;
        (void)_t3074;
        Str *_t3075 = tok_name(type);
        (void)_t3075;
        Array_set(_va54, &(U64){_t3074}, _t3075);
        ;
        U64 _t3076 = 7;
        (void)_t3076;
        Str *_t3077 = Str_lit("', found '", 10ULL);
        (void)_t3077;
        Array_set(_va54, &(U64){_t3076}, _t3077);
        ;
        U64 _t3078 = 8;
        (void)_t3078;
        Str *_t3079 = Str_clone(&t->text);
        (void)_t3079;
        Array_set(_va54, &(U64){_t3078}, _t3079);
        ;
        U64 _t3080 = 9;
        (void)_t3080;
        Str *_t3081 = Str_lit("'", 1ULL);
        (void)_t3081;
        Array_set(_va54, &(U64){_t3080}, _t3081);
        ;
        Str *_t3082 = Str_lit("src/self/parser.til:35:15", 25ULL);
        (void)_t3082;
        panic(_t3082, _va54);
        Str_delete(_t3082, &(Bool){1});
    }
    ;
    Token *_t3085 = advance(p);
    (void)_t3085;
    return _t3085;
}

Str * expect_text(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Token *t = peek(p);
    (void)t;
    Bool _t3110; { Bool *_hp = (Bool *)TokenType_eq(&t->type, type); _t3110 = *_hp; free(_hp); }
    (void)_t3110;
    Bool _t3111 = Bool_not(_t3110);
    (void)_t3111;
    ;
    if (_t3111) {
        Str *_t3086 = Str_lit("Str", 3ULL);
        (void)_t3086;
        U64 _t3087; { U64 *_hp = (U64 *)Str_size(); _t3087 = *_hp; free(_hp); }
        (void)_t3087;
        U64 _t3088 = 10;
        (void)_t3088;
        Array *_va55 = Array_new(_t3086, &(U64){_t3087}, &(U64){_t3088});
        (void)_va55;
        Str_delete(_t3086, &(Bool){1});
        ;
        ;
        U64 _t3089 = 0;
        (void)_t3089;
        Str *_t3090 = Str_clone(&p->path);
        (void)_t3090;
        Array_set(_va55, &(U64){_t3089}, _t3090);
        ;
        U64 _t3091 = 1;
        (void)_t3091;
        Str *_t3092 = Str_lit(":", 1ULL);
        (void)_t3092;
        Array_set(_va55, &(U64){_t3091}, _t3092);
        ;
        U64 _t3093 = 2;
        (void)_t3093;
        Str *_t3094 = U32_to_str(&t->line);
        (void)_t3094;
        Array_set(_va55, &(U64){_t3093}, _t3094);
        ;
        U64 _t3095 = 3;
        (void)_t3095;
        Str *_t3096 = Str_lit(":", 1ULL);
        (void)_t3096;
        Array_set(_va55, &(U64){_t3095}, _t3096);
        ;
        U64 _t3097 = 4;
        (void)_t3097;
        Str *_t3098 = U32_to_str(&t->col);
        (void)_t3098;
        Array_set(_va55, &(U64){_t3097}, _t3098);
        ;
        U64 _t3099 = 5;
        (void)_t3099;
        Str *_t3100 = Str_lit(": expected '", 12ULL);
        (void)_t3100;
        Array_set(_va55, &(U64){_t3099}, _t3100);
        ;
        U64 _t3101 = 6;
        (void)_t3101;
        Str *_t3102 = tok_name(type);
        (void)_t3102;
        Array_set(_va55, &(U64){_t3101}, _t3102);
        ;
        U64 _t3103 = 7;
        (void)_t3103;
        Str *_t3104 = Str_lit("', found '", 10ULL);
        (void)_t3104;
        Array_set(_va55, &(U64){_t3103}, _t3104);
        ;
        U64 _t3105 = 8;
        (void)_t3105;
        Str *_t3106 = Str_clone(&t->text);
        (void)_t3106;
        Array_set(_va55, &(U64){_t3105}, _t3106);
        ;
        U64 _t3107 = 9;
        (void)_t3107;
        Str *_t3108 = Str_lit("'", 1ULL);
        (void)_t3108;
        Array_set(_va55, &(U64){_t3107}, _t3108);
        ;
        Str *_t3109 = Str_lit("src/self/parser.til:45:15", 25ULL);
        (void)_t3109;
        panic(_t3109, _va55);
        Str_delete(_t3109, &(Bool){1});
    }
    ;
    Str *text = Str_clone(&t->text);
    (void)text;
    Token *_t3112 = advance(p);
    (void)_t3112;
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

Expr * parse_fn_signature(Parser * p, U32 line, U32 col) {
    (void)p;
    (void)line;
    (void)col;
    Bool _t3148 = check(p, TokenType_LParen());
    (void)_t3148;
    Bool _t3149 = Bool_not(_t3148);
    (void)_t3149;
    ;
    if (_t3149) {
        U32 _t3113 = 0;
        (void)_t3113;
        U32 _t3114 = 0;
        (void)_t3114;
        Str *_t3115 = Str_lit("", 0ULL);
        (void)_t3115;
        Expr *_t3116 = Expr_new(ExprData_Body(), _t3113, _t3114, _t3115);
        (void)_t3116;
        ;
        ;
        Str_delete(_t3115, &(Bool){1});
        ;
        return _t3116;
    }
    ;
    Token *_t3150 = advance(p);
    (void)_t3150;
    Str *_t3151 = Str_lit("Str", 3ULL);
    (void)_t3151;
    U64 _t3152; { U64 *_hp = (U64 *)Str_size(); _t3152 = *_hp; free(_hp); }
    (void)_t3152;
    Vec *ptypes = Vec_new(_t3151, &(U64){_t3152});
    (void)ptypes;
    Str_delete(_t3151, &(Bool){1});
    ;
    Str *_t3153 = Str_lit("Bool", 4ULL);
    (void)_t3153;
    U64 _t3154; { U64 *_hp = (U64 *)Bool_size(); _t3154 = *_hp; free(_hp); }
    (void)_t3154;
    Vec *pmuts = Vec_new(_t3153, &(U64){_t3154});
    (void)pmuts;
    Str_delete(_t3153, &(Bool){1});
    ;
    while (1) {
        Bool _t3121 = check(p, TokenType_RParen());
        (void)_t3121;
        Bool _t3122 = check(p, TokenType_Eof());
        (void)_t3122;
        Bool _t3123 = Bool_not(_t3121);
        (void)_t3123;
        ;
        Bool _t3124 = Bool_not(_t3122);
        (void)_t3124;
        ;
        Bool _wcond3117 = Bool_and(_t3123, _t3124);
        (void)_wcond3117;
        ;
        ;
        if (_wcond3117) {
        } else {
            ;
            break;
        }
        ;
        Bool is_mut = 0;
        (void)is_mut;
        Bool _t3125 = check(p, TokenType_KwMut());
        (void)_t3125;
        if (_t3125) {
            Token *_t3118 = advance(p);
            (void)_t3118;
            Bool _t3119 = 1;
            (void)_t3119;
            is_mut = _t3119;
            ;
        }
        ;
        Str *ptype = expect_text(p, TokenType_Ident());
        (void)ptype;
        Vec_push(ptypes, ptype);
        Vec_push(pmuts, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = is_mut; _oa; }));
        Bool _t3126 = check(p, TokenType_Comma());
        (void)_t3126;
        if (_t3126) {
            Token *_t3120 = advance(p);
            (void)_t3120;
        }
        ;
    }
    Token *_t3155 = expect_token(p, TokenType_RParen());
    (void)_t3155;
    Token_delete(_t3155, &(Bool){1});
    Str *return_type = Str_lit("", 0ULL);
    (void)return_type;
    Bool _t3156 = check(p, TokenType_KwReturns());
    (void)_t3156;
    if (_t3156) {
        Token *_t3127 = advance(p);
        (void)_t3127;
        return_type = expect_text(p, TokenType_Ident());
    }
    ;
    Str *_t3157 = Str_lit("Str", 3ULL);
    (void)_t3157;
    U64 _t3158; { U64 *_hp = (U64 *)Str_size(); _t3158 = *_hp; free(_hp); }
    (void)_t3158;
    Str *_t3159 = Str_lit("Str", 3ULL);
    (void)_t3159;
    U64 _t3160; { U64 *_hp = (U64 *)Str_size(); _t3160 = *_hp; free(_hp); }
    (void)_t3160;
    Str *_t3161 = Str_lit("Bool", 4ULL);
    (void)_t3161;
    U64 _t3162; { U64 *_hp = (U64 *)Bool_size(); _t3162 = *_hp; free(_hp); }
    (void)_t3162;
    Str *_t3163 = Str_lit("Bool", 4ULL);
    (void)_t3163;
    U64 _t3164; { U64 *_hp = (U64 *)Bool_size(); _t3164 = *_hp; free(_hp); }
    (void)_t3164;
    Str *_t3165 = Str_lit("Bool", 4ULL);
    (void)_t3165;
    U64 _t3166; { U64 *_hp = (U64 *)Bool_size(); _t3166 = *_hp; free(_hp); }
    (void)_t3166;
    Str *_t3167 = Str_lit("I64", 3ULL);
    (void)_t3167;
    U64 _t3168; { U64 *_hp = (U64 *)I64_size(); _t3168 = *_hp; free(_hp); }
    (void)_t3168;
    Str *_t3169 = Str_lit("I64", 3ULL);
    (void)_t3169;
    U64 _t3170; { U64 *_hp = (U64 *)I64_size(); _t3170 = *_hp; free(_hp); }
    (void)_t3170;
    I64 _t3171 = 0;
    (void)_t3171;
    I64 _t3172 = 1;
    (void)_t3172;
    I64 _t3173 = I64_sub(_t3171, _t3172);
    (void)_t3173;
    ;
    ;
    I64 _t3174 = 0;
    (void)_t3174;
    I64 _t3175 = 1;
    (void)_t3175;
    I64 _t3176 = I64_sub(_t3174, _t3175);
    (void)_t3176;
    ;
    ;
    U32 _t3177 = 0;
    (void)_t3177;
    I32 _t3178 = I64_to_i32(_t3173);
    (void)_t3178;
    ;
    I32 _t3179 = I64_to_i32(_t3176);
    (void)_t3179;
    ;
    Bool _t3180 = 0;
    (void)_t3180;
    Bool _t3181 = 0;
    (void)_t3181;
    FunctionDef *fd = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(FuncType_Func()); fd->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3157, &(U64){_t3158}); fd->param_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3159, &(U64){_t3160}); fd->param_types = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3161, &(U64){_t3162}); fd->param_muts = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3163, &(U64){_t3164}); fd->param_owns = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3165, &(U64){_t3166}); fd->param_shallows = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3167, &(U64){_t3168}); fd->param_fn_sigs = *_ca; free(_ca); }
    fd->nparam = _t3177;
    { Vec *_ca = Vec_new(_t3169, &(U64){_t3170}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3178;
    fd->kwargs_index = _t3179;
    fd->return_is_ref = _t3180;
    fd->return_is_shallow = _t3181;
    (void)fd;
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
    Str_delete(_t3169, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    U64 _t3182; { U64 *_hp = (U64 *)Str_len(return_type); _t3182 = *_hp; free(_hp); }
    (void)_t3182;
    U64 _t3183 = 0;
    (void)_t3183;
    Bool _t3184; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3182}, &(U64){_t3183}); _t3184 = *_hp; free(_hp); }
    (void)_t3184;
    ;
    ;
    if (_t3184) {
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
    Bool _t3185 = 0;
    (void)_t3185;
    fd->return_is_ref = _t3185;
    ;
    Bool _t3186 = 0;
    (void)_t3186;
    fd->return_is_shallow = _t3186;
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
    fd->variadic_index = _t3190;
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
    fd->kwargs_index = _t3194;
    ;
    {
        U64 _fi3128 = 0;
        (void)_fi3128;
        while (1) {
            U64 _t3130 = 0;
            (void)_t3130;
            U64 _t3131; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3131 = *_hp; free(_hp); }
            (void)_t3131;
            Range *_t3132 = Range_new(_t3130, _t3131);
            (void)_t3132;
            ;
            ;
            U64 _t3133; { U64 *_hp = (U64 *)Range_len(_t3132); _t3133 = *_hp; free(_hp); }
            (void)_t3133;
            Range_delete(_t3132, &(Bool){1});
            Bool _wcond3129; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3128}, &(U64){_t3133}); _wcond3129 = *_hp; free(_hp); }
            (void)_wcond3129;
            ;
            if (_wcond3129) {
            } else {
                ;
                break;
            }
            ;
            U64 _t3134 = 0;
            (void)_t3134;
            U64 _t3135; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3135 = *_hp; free(_hp); }
            (void)_t3135;
            Range *_t3136 = Range_new(_t3134, _t3135);
            (void)_t3136;
            ;
            ;
            U64 _; { U64 *_hp = (U64 *)Range_get(_t3136, _fi3128); _ = *_hp; free(_hp); }
            (void)_;
            ;
            Range_delete(_t3136, &(Bool){1});
            U64 _t3137 = 1;
            (void)_t3137;
            U64 _t3138 = U64_add(_fi3128, _t3137);
            (void)_t3138;
            ;
            _fi3128 = _t3138;
            ;
            Str *_t3139 = Str_lit("", 0ULL);
            (void)_t3139;
            Vec_push(&fd->param_names, _t3139);
            Bool _t3140 = 0;
            (void)_t3140;
            Vec_push(&fd->param_owns, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3140; _oa; }));
            Bool _t3141 = 0;
            (void)_t3141;
            Vec_push(&fd->param_shallows, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3141; _oa; }));
            I64 _t3142 = 0;
            (void)_t3142;
            I64 _t3143 = 1;
            (void)_t3143;
            I64 _t3144 = I64_sub(_t3142, _t3143);
            (void)_t3144;
            ;
            ;
            Vec_push(&fd->param_defaults, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = _t3144; _oa; }));
            I64 _t3145 = 0;
            (void)_t3145;
            I64 _t3146 = 1;
            (void)_t3146;
            I64 _t3147 = I64_sub(_t3145, _t3146);
            (void)_t3147;
            ;
            ;
            Vec_push(&fd->param_fn_sigs, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = _t3147; _oa; }));
        }
        ;
    }
    Vec_delete(&fd->param_types, &(Bool){0});
    { Vec *_fa = Vec_clone(ptypes); fd->param_types = *_fa; free(_fa); }
    Vec_delete(ptypes, &(Bool){1});
    Vec_delete(&fd->param_muts, &(Bool){0});
    { Vec *_fa = Vec_clone(pmuts); fd->param_muts = *_fa; free(_fa); }
    Vec_delete(pmuts, &(Bool){1});
    ExprData *_t3195 = ExprData_FuncDef(fd);
    (void)_t3195;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *sig = Expr_new(_t3195, line, col, &p->path);
    (void)sig;
    ExprData_delete(_t3195, &(Bool){1});
    Token_delete(_t3155, &(Bool){1});
    return sig;
}

Expr * parse_block(Parser * p) {
    (void)p;
    U32 _t3202; { U32 *_hp = (U32 *)peek_line(p); _t3202 = *_hp; free(_hp); }
    (void)_t3202;
    U32 _t3203; { U32 *_hp = (U32 *)peek_col(p); _t3203 = *_hp; free(_hp); }
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
    Token_delete(_t3204, &(Bool){1});
    Token_delete(_t3204, &(Bool){1});
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
                                Str *_t3211 = Str_lit("src/self/parser.til:136:17", 26ULL);
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
    Token_delete(_t3411, &(Bool){1});
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
    Str *_t3424 = Str_lit("I64", 3ULL);
    (void)_t3424;
    U64 _t3425; { U64 *_hp = (U64 *)I64_size(); _t3425 = *_hp; free(_hp); }
    (void)_t3425;
    I64 _t3426 = 0;
    (void)_t3426;
    I64 _t3427 = 1;
    (void)_t3427;
    I64 _t3428 = I64_sub(_t3426, _t3427);
    (void)_t3428;
    ;
    ;
    I64 _t3429 = 0;
    (void)_t3429;
    I64 _t3430 = 1;
    (void)_t3430;
    I64 _t3431 = I64_sub(_t3429, _t3430);
    (void)_t3431;
    ;
    ;
    U32 _t3432 = 0;
    (void)_t3432;
    I32 _t3433 = I64_to_i32(_t3428);
    (void)_t3433;
    ;
    I32 _t3434 = I64_to_i32(_t3431);
    (void)_t3434;
    ;
    Bool _t3435 = 0;
    (void)_t3435;
    Bool _t3436 = 0;
    (void)_t3436;
    FunctionDef *fd = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(FuncType_Func()); fd->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3412, &(U64){_t3413}); fd->param_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3414, &(U64){_t3415}); fd->param_types = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3416, &(U64){_t3417}); fd->param_muts = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3418, &(U64){_t3419}); fd->param_owns = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3420, &(U64){_t3421}); fd->param_shallows = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3422, &(U64){_t3423}); fd->param_fn_sigs = *_ca; free(_ca); }
    fd->nparam = _t3432;
    { Vec *_ca = Vec_new(_t3424, &(U64){_t3425}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3433;
    fd->kwargs_index = _t3434;
    fd->return_is_ref = _t3435;
    fd->return_is_shallow = _t3436;
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
    ;
    ;
    ;
    ;
    ;
    FuncType_delete(&fd->func_type, &(Bool){0});
    { FuncType *_fa = FuncType_clone(ft); fd->func_type = *_fa; free(_fa); }
    Str *_t3437 = Str_lit("Expr", 4ULL);
    (void)_t3437;
    U64 _t3438; { U64 *_hp = (U64 *)Expr_size(); _t3438 = *_hp; free(_hp); }
    (void)_t3438;
    Vec *def_exprs = Vec_new(_t3437, &(U64){_t3438});
    (void)def_exprs;
    Str_delete(_t3437, &(Bool){1});
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
            Token_delete(_t3318, &(Bool){1});
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
                    U32 _t3232; { U32 *_hp = (U32 *)peek_line(p); _t3232 = *_hp; free(_hp); }
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
                    U32 _t3237; { U32 *_hp = (U32 *)peek_col(p); _t3237 = *_hp; free(_hp); }
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
                    Str *_t3242 = Str_lit("src/self/parser.til:167:27", 26ULL);
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
                    Str *_t3248 = Str_lit("src/self/parser.til:171:27", 26ULL);
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
                    Str *_t3254 = Str_lit("src/self/parser.til:174:27", 26ULL);
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
                        Str *_t3277 = Str_lit("src/self/parser.til:182:35", 26ULL);
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
                        Str *_t3283 = Str_lit("src/self/parser.til:183:35", 26ULL);
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
                        Str *_t3289 = Str_lit("src/self/parser.til:184:39", 26ULL);
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
                        Str *_t3295 = Str_lit("src/self/parser.til:185:69", 26ULL);
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
                        Str *_t3301 = Str_lit("src/self/parser.til:187:27", 26ULL);
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
            U32 _t3322; { U32 *_hp = (U32 *)peek_line(p); _t3322 = *_hp; free(_hp); }
            (void)_t3322;
            U32 _t3323; { U32 *_hp = (U32 *)peek_col(p); _t3323 = *_hp; free(_hp); }
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
            Str *_t3334 = Str_lit("src/self/parser.til:226:19", 26ULL);
            (void)_t3334;
            panic(_t3334, _va65);
            Str_delete(_t3334, &(Bool){1});
        }
        ;
        Vec_push(&fd->param_defaults, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = has_default; _oa; }));
        Bool _t3364 = check(p, TokenType_Comma());
        (void)_t3364;
        if (_t3364) {
            Token *_t3335 = advance(p);
            (void)_t3335;
        }
        ;
    }
    Token *_t3439 = expect_token(p, TokenType_RParen());
    (void)_t3439;
    Token_delete(_t3439, &(Bool){1});
    Bool _t3440 = check(p, TokenType_KwReturns());
    (void)_t3440;
    if (_t3440) {
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
    ExprData *_t3441 = ExprData_FuncDef(fd);
    (void)_t3441;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *def = Expr_new(_t3441, kw_line, kw_col, &p->path);
    (void)def;
    ExprData_delete(_t3441, &(Bool){1});
    Bool _t3442 = check(p, TokenType_LBrace());
    (void)_t3442;
    if (_t3442) {
        Token *_t3372 = expect_token(p, TokenType_LBrace());
        (void)_t3372;
        Token_delete(_t3372, &(Bool){1});
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
            Str *_t3393 = Str_lit("src/self/parser.til:254:19", 26ULL);
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
    Token_delete(_t3411, &(Bool){1});
    Token_delete(_t3439, &(Bool){1});
    return def;
}

Expr * parse_struct_def(Parser * p) {
    (void)p;
    U32 kw_line; { U32 *_hp = (U32 *)peek_line(p); kw_line = *_hp; free(_hp); }
    (void)kw_line;
    U32 kw_col; { U32 *_hp = (U32 *)peek_col(p); kw_col = *_hp; free(_hp); }
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
    Token_delete(_t3458, &(Bool){1});
    U32 _t3459; { U32 *_hp = (U32 *)peek_line(p); _t3459 = *_hp; free(_hp); }
    (void)_t3459;
    U32 _t3460; { U32 *_hp = (U32 *)peek_col(p); _t3460 = *_hp; free(_hp); }
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
            Token_delete(_t3445, &(Bool){1});
            Bool _t3446 = 1;
            (void)_t3446;
            in_namespace = _t3446;
            ;
            Token_delete(_t3445, &(Bool){1});
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
    Token_delete(_t3461, &(Bool){1});
    Expr_add_child(def, body);
    Token_delete(_t3458, &(Bool){1});
    Token_delete(_t3461, &(Bool){1});
    return def;
}

Expr * parse_enum_def(Parser * p) {
    (void)p;
    U32 kw_line; { U32 *_hp = (U32 *)peek_line(p); kw_line = *_hp; free(_hp); }
    (void)kw_line;
    U32 kw_col; { U32 *_hp = (U32 *)peek_col(p); kw_col = *_hp; free(_hp); }
    (void)kw_col;
    Token *_t3485 = advance(p);
    (void)_t3485;
    Expr *def = Expr_new(ExprData_EnumDef(), kw_line, kw_col, &p->path);
    (void)def;
    ;
    ;
    Token *_t3486 = expect_token(p, TokenType_LBrace());
    (void)_t3486;
    Token_delete(_t3486, &(Bool){1});
    U32 _t3487; { U32 *_hp = (U32 *)peek_line(p); _t3487 = *_hp; free(_hp); }
    (void)_t3487;
    U32 _t3488; { U32 *_hp = (U32 *)peek_col(p); _t3488 = *_hp; free(_hp); }
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
            Token_delete(_t3464, &(Bool){1});
            Bool _t3465 = 1;
            (void)_t3465;
            in_namespace = _t3465;
            ;
            Token_delete(_t3464, &(Bool){1});
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
            U32 v_line; { U32 *_hp = (U32 *)peek_line(p); v_line = *_hp; free(_hp); }
            (void)v_line;
            U32 v_col; { U32 *_hp = (U32 *)peek_col(p); v_col = *_hp; free(_hp); }
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
    Token_delete(_t3489, &(Bool){1});
    Expr_add_child(def, body);
    Token_delete(_t3486, &(Bool){1});
    Token_delete(_t3489, &(Bool){1});
    return def;
}

Expr * parse_call(Parser * p, Str * name, U32 call_line, U32 call_col) {
    (void)p;
    (void)name;
    (void)call_line;
    (void)call_col;
    Token *_t3519 = advance(p);
    (void)_t3519;
    Expr *call = Expr_new(ExprData_FCall(), call_line, call_col, &p->path);
    (void)call;
    Str *_t3520 = Str_clone(name);
    (void)_t3520;
    ExprData *_t3521 = ExprData_Ident(_t3520);
    (void)_t3521;
    Str_delete(_t3520, &(Bool){1});
    Expr *callee = Expr_new(_t3521, call_line, call_col, &p->path);
    (void)callee;
    ExprData_delete(_t3521, &(Bool){1});
    Expr_add_child(call, callee);
    while (1) {
        Bool _t3509 = check(p, TokenType_RParen());
        (void)_t3509;
        Bool _t3510 = check(p, TokenType_Eof());
        (void)_t3510;
        Bool _t3511 = Bool_not(_t3509);
        (void)_t3511;
        ;
        Bool _t3512 = Bool_not(_t3510);
        (void)_t3512;
        ;
        Bool _wcond3490 = Bool_and(_t3511, _t3512);
        (void)_wcond3490;
        ;
        ;
        if (_wcond3490) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3513 = check(p, TokenType_Ident());
        (void)_t3513;
        if (_t3513) {
            U32 _t3501 = 1;
            (void)_t3501;
            U32 _t3502 = U32_add(p->pos, _t3501);
            (void)_t3502;
            ;
            Bool _t3503; { Bool *_hp = (Bool *)U32_lt(&(U32){_t3502}, &p->count); _t3503 = *_hp; free(_hp); }
            (void)_t3503;
            ;
            if (_t3503) {
                U32 _t3496 = 1;
                (void)_t3496;
                U32 _t3497 = U32_add(p->pos, _t3496);
                (void)_t3497;
                ;
                I64 _t3498 = U32_to_i64(_t3497);
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
                    U32 na_line; { U32 *_hp = (U32 *)peek_line(p); na_line = *_hp; free(_hp); }
                    (void)na_line;
                    U32 na_col; { U32 *_hp = (U32 *)peek_col(p); na_col = *_hp; free(_hp); }
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
        Bool _t3514 = check(p, TokenType_DotDot());
        (void)_t3514;
        if (_t3514) {
            Token *_t3504 = advance(p);
            (void)_t3504;
            Bool _t3505 = 1;
            (void)_t3505;
            is_splat = _t3505;
            ;
        }
        ;
        Bool is_own_arg = 0;
        (void)is_own_arg;
        Bool _t3515 = check(p, TokenType_KwOwn());
        (void)_t3515;
        if (_t3515) {
            Token *_t3506 = advance(p);
            (void)_t3506;
            Bool _t3507 = 1;
            (void)_t3507;
            is_own_arg = _t3507;
            ;
        }
        ;
        Expr *arg = parse_expression(p);
        (void)arg;
        Bool _t3516 = Bool_clone(&(Bool){is_own_arg});
        (void)_t3516;
        ;
        arg->is_own_arg = _t3516;
        ;
        Bool _t3517 = Bool_clone(&(Bool){is_splat});
        (void)_t3517;
        ;
        arg->is_splat = _t3517;
        ;
        Expr_add_child(call, arg);
        Bool _t3518 = check(p, TokenType_Comma());
        (void)_t3518;
        if (_t3518) {
            Token *_t3508 = advance(p);
            (void)_t3508;
        }
        ;
    }
    Token *_t3522 = expect_token(p, TokenType_RParen());
    (void)_t3522;
    Token_delete(_t3522, &(Bool){1});
    Token_delete(_t3522, &(Bool){1});
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
        Token *_t3523 = advance(p);
        (void)_t3523;
        Str *_t3524 = Str_clone(&t->text);
        (void)_t3524;
        ExprData *_t3525 = ExprData_LiteralStr(_t3524);
        (void)_t3525;
        Str_delete(_t3524, &(Bool){1});
        e = Expr_new(_t3525, t_line, t_col, &p->path);
        ExprData_delete(_t3525, &(Bool){1});
        Bool _t3526 = 1;
        (void)_t3526;
        e_set = _t3526;
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
        Token *_t3527 = advance(p);
        (void)_t3527;
        Str *_t3528 = Str_clone(&t->text);
        (void)_t3528;
        ExprData *_t3529 = ExprData_LiteralNum(_t3528);
        (void)_t3529;
        Str_delete(_t3528, &(Bool){1});
        e = Expr_new(_t3529, t_line, t_col, &p->path);
        ExprData_delete(_t3529, &(Bool){1});
        Bool _t3530 = 1;
        (void)_t3530;
        e_set = _t3530;
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
        Token *_t3560 = advance(p);
        (void)_t3560;
        Str *ch = Str_clone(&t->text);
        (void)ch;
        I64 byte_val = 0;
        (void)byte_val;
        U64 _t3561; { U64 *_hp = (U64 *)Str_len(ch); _t3561 = *_hp; free(_hp); }
        (void)_t3561;
        U64 _t3562 = 0;
        (void)_t3562;
        U64 *_t3563 = malloc(sizeof(U64));
        *_t3563 = 0;
        (void)_t3563;
        U8 *_t3564 = Str_get(ch, _t3563);
        (void)_t3564;
        U8 _t3565 = 92;
        (void)_t3565;
        Bool _t3566; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3561}, &(U64){_t3562}); _t3566 = *_hp; free(_hp); }
        (void)_t3566;
        ;
        ;
        Bool _t3567 = U8_eq(DEREF(_t3564), _t3565);
        (void)_t3567;
        U64_delete(_t3563, &(Bool){1});
        ;
        Bool _t3568 = Bool_and(_t3566, _t3567);
        (void)_t3568;
        ;
        ;
        if (_t3568) {
            U64 _t3551; { U64 *_hp = (U64 *)Str_len(ch); _t3551 = *_hp; free(_hp); }
            (void)_t3551;
            U64 _t3552 = 1;
            (void)_t3552;
            Bool _t3553; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3551}, &(U64){_t3552}); _t3553 = *_hp; free(_hp); }
            (void)_t3553;
            ;
            ;
            if (_t3553) {
                U64 *_t3548 = malloc(sizeof(U64));
                *_t3548 = 1;
                (void)_t3548;
                U8 *c2 = Str_get(ch, _t3548);
                (void)c2;
                U8 _t3549 = 110;
                (void)_t3549;
                Bool _t3550 = U8_eq(DEREF(c2), _t3549);
                (void)_t3550;
                ;
                if (_t3550) {
                    I64 _t3531 = 10;
                    (void)_t3531;
                    byte_val = _t3531;
                    ;
                } else {
                    U8 _t3546 = 116;
                    (void)_t3546;
                    Bool _t3547 = U8_eq(DEREF(c2), _t3546);
                    (void)_t3547;
                    ;
                    if (_t3547) {
                        I64 _t3532 = 9;
                        (void)_t3532;
                        byte_val = _t3532;
                        ;
                    } else {
                        U8 _t3544 = 114;
                        (void)_t3544;
                        Bool _t3545 = U8_eq(DEREF(c2), _t3544);
                        (void)_t3545;
                        ;
                        if (_t3545) {
                            I64 _t3533 = 13;
                            (void)_t3533;
                            byte_val = _t3533;
                            ;
                        } else {
                            U8 _t3542 = 92;
                            (void)_t3542;
                            Bool _t3543 = U8_eq(DEREF(c2), _t3542);
                            (void)_t3543;
                            ;
                            if (_t3543) {
                                I64 _t3534 = 92;
                                (void)_t3534;
                                byte_val = _t3534;
                                ;
                            } else {
                                U8 _t3540 = 39;
                                (void)_t3540;
                                Bool _t3541 = U8_eq(DEREF(c2), _t3540);
                                (void)_t3541;
                                ;
                                if (_t3541) {
                                    I64 _t3535 = 39;
                                    (void)_t3535;
                                    byte_val = _t3535;
                                    ;
                                } else {
                                    U8 _t3538 = 48;
                                    (void)_t3538;
                                    Bool _t3539 = U8_eq(DEREF(c2), _t3538);
                                    (void)_t3539;
                                    ;
                                    if (_t3539) {
                                        I64 _t3536 = 0;
                                        (void)_t3536;
                                        byte_val = _t3536;
                                        ;
                                    } else {
                                        I64 _t3537 = U8_to_i64(DEREF(c2));
                                        (void)_t3537;
                                        byte_val = _t3537;
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
                U64_delete(_t3548, &(Bool){1});
                ;
            }
            ;
        } else {
            U64 _t3557; { U64 *_hp = (U64 *)Str_len(ch); _t3557 = *_hp; free(_hp); }
            (void)_t3557;
            U64 _t3558 = 0;
            (void)_t3558;
            Bool _t3559; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3557}, &(U64){_t3558}); _t3559 = *_hp; free(_hp); }
            (void)_t3559;
            ;
            ;
            if (_t3559) {
                U64 *_t3554 = malloc(sizeof(U64));
                *_t3554 = 0;
                (void)_t3554;
                U8 *_t3555 = Str_get(ch, _t3554);
                (void)_t3555;
                I64 _t3556 = U8_to_i64(DEREF(_t3555));
                (void)_t3556;
                U64_delete(_t3554, &(Bool){1});
                byte_val = _t3556;
                ;
            }
            ;
        }
        ;
        Str_delete(ch, &(Bool){1});
        Str *_t3569 = I64_to_str(&(I64){byte_val});
        (void)_t3569;
        ;
        ExprData *_t3570 = ExprData_LiteralNum(_t3569);
        (void)_t3570;
        Str_delete(_t3569, &(Bool){1});
        e = Expr_new(_t3570, t_line, t_col, &p->path);
        ExprData_delete(_t3570, &(Bool){1});
        TilType_delete(&e->til_type, &(Bool){0});
        { TilType *_fa = TilType_clone(TilType_U8()); e->til_type = *_fa; free(_fa); }
        Bool _t3571 = 1;
        (void)_t3571;
        e_set = _t3571;
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
        Token *_t3572 = advance(p);
        (void)_t3572;
        Str *_t3573 = Str_clone(&t->text);
        (void)_t3573;
        ExprData *_t3574 = ExprData_LiteralBool(_t3573);
        (void)_t3574;
        Str_delete(_t3573, &(Bool){1});
        e = Expr_new(_t3574, t_line, t_col, &p->path);
        ExprData_delete(_t3574, &(Bool){1});
        Bool _t3575 = 1;
        (void)_t3575;
        e_set = _t3575;
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
        Token *_t3611 = advance(p);
        (void)_t3611;
        Str *name = Str_clone(&t->text);
        (void)name;
        Str *_t3612 = Str_lit("__LOC__", 7ULL);
        (void)_t3612;
        Bool _t3613; { Bool *_hp = (Bool *)Str_eq(name, _t3612); _t3613 = *_hp; free(_hp); }
        (void)_t3613;
        Str_delete(_t3612, &(Bool){1});
        if (_t3613) {
            Str *_t3576 = Str_lit("Str", 3ULL);
            (void)_t3576;
            U64 _t3577; { U64 *_hp = (U64 *)Str_size(); _t3577 = *_hp; free(_hp); }
            (void)_t3577;
            U64 _t3578 = 5;
            (void)_t3578;
            Array *_va67 = Array_new(_t3576, &(U64){_t3577}, &(U64){_t3578});
            (void)_va67;
            Str_delete(_t3576, &(Bool){1});
            ;
            ;
            U64 _t3579 = 0;
            (void)_t3579;
            Str *_t3580 = Str_clone(&p->path);
            (void)_t3580;
            Array_set(_va67, &(U64){_t3579}, _t3580);
            ;
            U64 _t3581 = 1;
            (void)_t3581;
            Str *_t3582 = Str_lit(":", 1ULL);
            (void)_t3582;
            Array_set(_va67, &(U64){_t3581}, _t3582);
            ;
            U64 _t3583 = 2;
            (void)_t3583;
            Str *_t3584 = U32_to_str(&(U32){t_line});
            (void)_t3584;
            Array_set(_va67, &(U64){_t3583}, _t3584);
            ;
            U64 _t3585 = 3;
            (void)_t3585;
            Str *_t3586 = Str_lit(":", 1ULL);
            (void)_t3586;
            Array_set(_va67, &(U64){_t3585}, _t3586);
            ;
            U64 _t3587 = 4;
            (void)_t3587;
            Str *_t3588 = U32_to_str(&(U32){t_col});
            (void)_t3588;
            Array_set(_va67, &(U64){_t3587}, _t3588);
            ;
            Str *_t3589 = format(_va67);
            (void)_t3589;
            ExprData *_t3590 = ExprData_LiteralStr(_t3589);
            (void)_t3590;
            Str_delete(_t3589, &(Bool){1});
            e = Expr_new(_t3590, t_line, t_col, &p->path);
            ExprData_delete(_t3590, &(Bool){1});
            Bool _t3591 = 1;
            (void)_t3591;
            e_set = _t3591;
            ;
        } else {
            Str *_t3609 = Str_lit("__FILE__", 8ULL);
            (void)_t3609;
            Bool _t3610; { Bool *_hp = (Bool *)Str_eq(name, _t3609); _t3610 = *_hp; free(_hp); }
            (void)_t3610;
            Str_delete(_t3609, &(Bool){1});
            if (_t3610) {
                Str *_t3592 = Str_clone(&p->path);
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
                Str *_t3607 = Str_lit("__LINE__", 8ULL);
                (void)_t3607;
                Bool _t3608; { Bool *_hp = (Bool *)Str_eq(name, _t3607); _t3608 = *_hp; free(_hp); }
                (void)_t3608;
                Str_delete(_t3607, &(Bool){1});
                if (_t3608) {
                    Str *_t3595 = U32_to_str(&(U32){t_line});
                    (void)_t3595;
                    ExprData *_t3596 = ExprData_LiteralNum(_t3595);
                    (void)_t3596;
                    Str_delete(_t3595, &(Bool){1});
                    e = Expr_new(_t3596, t_line, t_col, &p->path);
                    ExprData_delete(_t3596, &(Bool){1});
                    Bool _t3597 = 1;
                    (void)_t3597;
                    e_set = _t3597;
                    ;
                } else {
                    Str *_t3605 = Str_lit("__COL__", 7ULL);
                    (void)_t3605;
                    Bool _t3606; { Bool *_hp = (Bool *)Str_eq(name, _t3605); _t3606 = *_hp; free(_hp); }
                    (void)_t3606;
                    Str_delete(_t3605, &(Bool){1});
                    if (_t3606) {
                        Str *_t3598 = U32_to_str(&(U32){t_col});
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
                        Bool _t3604 = check(p, TokenType_LParen());
                        (void)_t3604;
                        if (_t3604) {
                            e = parse_call(p, name, t_line, t_col);
                            Bool _t3601 = 1;
                            (void)_t3601;
                            e_set = _t3601;
                            ;
                        } else {
                            ExprData *_t3602 = ExprData_Ident(name);
                            (void)_t3602;
                            e = Expr_new(_t3602, t_line, t_col, &p->path);
                            ExprData_delete(_t3602, &(Bool){1});
                            Bool _t3603 = 1;
                            (void)_t3603;
                            e_set = _t3603;
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
        Expr *_t3614 = parse_func_def(p);
        (void)_t3614;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3614;
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
        Expr *_t3615 = parse_struct_def(p);
        (void)_t3615;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3615;
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
        Expr *_t3616 = parse_enum_def(p);
        (void)_t3616;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3616;
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
        Token *_t3641 = advance(p);
        (void)_t3641;
        Expr *first = parse_expression(p);
        (void)first;
        Bool _t3642 = check(p, TokenType_Colon());
        (void)_t3642;
        if (_t3642) {
            e = Expr_new(ExprData_MapLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Token *_t3628 = advance(p);
            (void)_t3628;
            Expr *_t3629 = parse_expression(p);
            (void)_t3629;
            Expr_add_child(e, _t3629);
            Bool _t3630 = check(p, TokenType_Comma());
            (void)_t3630;
            if (_t3630) {
                Token *_t3617 = advance(p);
                (void)_t3617;
            }
            ;
            while (1) {
                Bool _t3620 = check(p, TokenType_RBrace());
                (void)_t3620;
                Bool _t3621 = check(p, TokenType_Eof());
                (void)_t3621;
                Bool _t3622 = Bool_not(_t3620);
                (void)_t3622;
                ;
                Bool _t3623 = Bool_not(_t3621);
                (void)_t3623;
                ;
                Bool _wcond3618 = Bool_and(_t3622, _t3623);
                (void)_wcond3618;
                ;
                ;
                if (_wcond3618) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3624 = parse_expression(p);
                (void)_t3624;
                Expr_add_child(e, _t3624);
                Token *_t3625 = expect_token(p, TokenType_Colon());
                (void)_t3625;
                Token_delete(_t3625, &(Bool){1});
                Expr *_t3626 = parse_expression(p);
                (void)_t3626;
                Expr_add_child(e, _t3626);
                Bool _t3627 = check(p, TokenType_Comma());
                (void)_t3627;
                if (_t3627) {
                    Token *_t3619 = advance(p);
                    (void)_t3619;
                }
                ;
            }
        } else {
            e = Expr_new(ExprData_SetLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Bool _t3640 = check(p, TokenType_Comma());
            (void)_t3640;
            if (_t3640) {
                Token *_t3631 = advance(p);
                (void)_t3631;
            }
            ;
            while (1) {
                Bool _t3634 = check(p, TokenType_RBrace());
                (void)_t3634;
                Bool _t3635 = check(p, TokenType_Eof());
                (void)_t3635;
                Bool _t3636 = Bool_not(_t3634);
                (void)_t3636;
                ;
                Bool _t3637 = Bool_not(_t3635);
                (void)_t3637;
                ;
                Bool _wcond3632 = Bool_and(_t3636, _t3637);
                (void)_wcond3632;
                ;
                ;
                if (_wcond3632) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3638 = parse_expression(p);
                (void)_t3638;
                Expr_add_child(e, _t3638);
                Bool _t3639 = check(p, TokenType_Comma());
                (void)_t3639;
                if (_t3639) {
                    Token *_t3633 = advance(p);
                    (void)_t3633;
                }
                ;
            }
        }
        ;
        Token *_t3643 = expect_token(p, TokenType_RBrace());
        (void)_t3643;
        Token_delete(_t3643, &(Bool){1});
        Bool _t3644 = 1;
        (void)_t3644;
        e_set = _t3644;
        ;
    }
    ;
    Bool _t3748 = Bool_not(e_set);
    (void)_t3748;
    ;
    if (_t3748) {
        Str *_t3645 = Str_lit("Str", 3ULL);
        (void)_t3645;
        U64 _t3646; { U64 *_hp = (U64 *)Str_size(); _t3646 = *_hp; free(_hp); }
        (void)_t3646;
        U64 _t3647 = 8;
        (void)_t3647;
        Array *_va68 = Array_new(_t3645, &(U64){_t3646}, &(U64){_t3647});
        (void)_va68;
        Str_delete(_t3645, &(Bool){1});
        ;
        ;
        U64 _t3648 = 0;
        (void)_t3648;
        Str *_t3649 = Str_clone(&p->path);
        (void)_t3649;
        Array_set(_va68, &(U64){_t3648}, _t3649);
        ;
        U64 _t3650 = 1;
        (void)_t3650;
        Str *_t3651 = Str_lit(":", 1ULL);
        (void)_t3651;
        Array_set(_va68, &(U64){_t3650}, _t3651);
        ;
        U64 _t3652 = 2;
        (void)_t3652;
        Str *_t3653 = U32_to_str(&(U32){t_line});
        (void)_t3653;
        Array_set(_va68, &(U64){_t3652}, _t3653);
        ;
        U64 _t3654 = 3;
        (void)_t3654;
        Str *_t3655 = Str_lit(":", 1ULL);
        (void)_t3655;
        Array_set(_va68, &(U64){_t3654}, _t3655);
        ;
        U64 _t3656 = 4;
        (void)_t3656;
        Str *_t3657 = U32_to_str(&(U32){t_col});
        (void)_t3657;
        Array_set(_va68, &(U64){_t3656}, _t3657);
        ;
        U64 _t3658 = 5;
        (void)_t3658;
        Str *_t3659 = Str_lit(": unexpected token '", 20ULL);
        (void)_t3659;
        Array_set(_va68, &(U64){_t3658}, _t3659);
        ;
        U64 _t3660 = 6;
        (void)_t3660;
        Str *_t3661 = Str_clone(&t->text);
        (void)_t3661;
        Array_set(_va68, &(U64){_t3660}, _t3661);
        ;
        U64 _t3662 = 7;
        (void)_t3662;
        Str *_t3663 = Str_lit("'", 1ULL);
        (void)_t3663;
        Array_set(_va68, &(U64){_t3662}, _t3663);
        ;
        Str *_t3664 = Str_lit("src/self/parser.til:514:15", 26ULL);
        (void)_t3664;
        panic(_t3664, _va68);
        Str_delete(_t3664, &(Bool){1});
    }
    ;
    ;
    ;
    while (1) {
        Bool _wcond3665 = check(p, TokenType_Dot());
        (void)_wcond3665;
        if (_wcond3665) {
        } else {
            ;
            break;
        }
        ;
        Token *_t3697 = advance(p);
        (void)_t3697;
        U32 f_line; { U32 *_hp = (U32 *)peek_line(p); f_line = *_hp; free(_hp); }
        (void)f_line;
        U32 f_col; { U32 *_hp = (U32 *)peek_col(p); f_col = *_hp; free(_hp); }
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
                Bool _wcond3666 = Bool_and(_t3685, _t3686);
                (void)_wcond3666;
                ;
                ;
                if (_wcond3666) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3687 = check(p, TokenType_Ident());
                (void)_t3687;
                if (_t3687) {
                    U32 _t3677 = 1;
                    (void)_t3677;
                    U32 _t3678 = U32_add(p->pos, _t3677);
                    (void)_t3678;
                    ;
                    Bool _t3679; { Bool *_hp = (Bool *)U32_lt(&(U32){_t3678}, &p->count); _t3679 = *_hp; free(_hp); }
                    (void)_t3679;
                    ;
                    if (_t3679) {
                        U32 _t3672 = 1;
                        (void)_t3672;
                        U32 _t3673 = U32_add(p->pos, _t3672);
                        (void)_t3673;
                        ;
                        I64 _t3674 = U32_to_i64(_t3673);
                        (void)_t3674;
                        ;
                        U64 *_t3675 = malloc(sizeof(U64)); *_t3675 = I64_to_u64(_t3674);
                        (void)_t3675;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3675);
                        (void)nt;
                        Bool _t3676; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3676 = *_hp; free(_hp); }
                        (void)_t3676;
                        U64_delete(_t3675, &(Bool){1});
                        if (_t3676) {
                            U32 na_line; { U32 *_hp = (U32 *)peek_line(p); na_line = *_hp; free(_hp); }
                            (void)na_line;
                            U32 na_col; { U32 *_hp = (U32 *)peek_col(p); na_col = *_hp; free(_hp); }
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3668 = advance(p);
                            (void)_t3668;
                            ExprData *_t3669 = ExprData_NamedArg(aname);
                            (void)_t3669;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3669, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3669, &(Bool){1});
                            ;
                            ;
                            Expr *_t3670 = parse_expression(p);
                            (void)_t3670;
                            Expr_add_child(na, _t3670);
                            Expr_add_child(mcall, na);
                            Bool _t3671 = check(p, TokenType_Comma());
                            (void)_t3671;
                            if (_t3671) {
                                Token *_t3667 = advance(p);
                                (void)_t3667;
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
            Token_delete(_t3694, &(Bool){1});
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
        U32 dt_line; { U32 *_hp = (U32 *)peek_line(p); dt_line = *_hp; free(_hp); }
        (void)dt_line;
        U32 dt_col; { U32 *_hp = (U32 *)peek_col(p); dt_col = *_hp; free(_hp); }
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
    Bool _t3949 = check(p, TokenType_ColonEq());
    (void)_t3949;
    if (_t3949) {
        Token *_t3750 = advance(p);
        (void)_t3750;
        Bool _t3751 = Bool_clone(is_mut);
        (void)_t3751;
        Bool _t3752 = 0;
        (void)_t3752;
        Bool _t3753 = 0;
        (void)_t3753;
        Bool _t3754 = Bool_clone(is_own);
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
    Bool _t3950 = check(p, TokenType_Colon());
    (void)_t3950;
    if (_t3950) {
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
            Token_delete(_t3776, &(Bool){1});
            Token *_t3777 = expect_token(p, TokenType_LParen());
            (void)_t3777;
            Token_delete(_t3777, &(Bool){1});
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
                            Token_delete(_t3761, &(Bool){1});
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
            Token_delete(_t3780, &(Bool){1});
            Token *_t3781 = expect_token(p, TokenType_LBrace());
            (void)_t3781;
            Token_delete(_t3781, &(Bool){1});
            Expr *_t3782 = parse_block(p);
            (void)_t3782;
            Expr_add_child(sig, _t3782);
            Bool _t3783 = Bool_clone(is_mut);
            (void)_t3783;
            Bool _t3784 = 0;
            (void)_t3784;
            Bool _t3785 = 0;
            (void)_t3785;
            Bool _t3786 = Bool_clone(is_own);
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
            Token_delete(_t3776, &(Bool){1});
            Token_delete(_t3777, &(Bool){1});
            Token_delete(_t3780, &(Bool){1});
            Token_delete(_t3781, &(Bool){1});
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
        Token_delete(_t3890, &(Bool){1});
        Bool _t3891 = check(p, TokenType_LParen());
        (void)_t3891;
        if (_t3891) {
            U32 saved = p->pos;
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
            U32 _t3881 = U32_clone(&(U32){saved});
            (void)_t3881;
            ;
            p->pos = _t3881;
            ;
            if (is_fsf) {
                Token *_t3832 = expect_token(p, TokenType_LParen());
                (void)_t3832;
                Token_delete(_t3832, &(Bool){1});
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
                Token_delete(_t3835, &(Bool){1});
                Token *_t3836 = expect_token(p, TokenType_LBrace());
                (void)_t3836;
                Token_delete(_t3836, &(Bool){1});
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
                Bool _t3871 = Bool_clone(is_mut);
                (void)_t3871;
                Bool _t3872 = 0;
                (void)_t3872;
                Bool _t3873 = 0;
                (void)_t3873;
                Bool _t3874 = Bool_clone(is_own);
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
                Token_delete(_t3832, &(Bool){1});
                Token_delete(_t3835, &(Bool){1});
                Token_delete(_t3836, &(Bool){1});
                ;
                Token_delete(_t3890, &(Bool){1});
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
        Bool _t3892 = Bool_clone(is_mut);
        (void)_t3892;
        Bool _t3893 = 0;
        (void)_t3893;
        Bool _t3894 = 0;
        (void)_t3894;
        Bool _t3895 = Bool_clone(is_own);
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
        Token_delete(_t3890, &(Bool){1});
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return decl;
    }
    ;
    Bool _t3951 = check(p, TokenType_Dot());
    (void)_t3951;
    if (_t3951) {
        Str *_t3937 = Str_clone(name);
        (void)_t3937;
        ExprData *_t3938 = ExprData_Ident(_t3937);
        (void)_t3938;
        Str_delete(_t3937, &(Bool){1});
        Expr *obj = Expr_new(_t3938, t_line, t_col, &p->path);
        (void)obj;
        ExprData_delete(_t3938, &(Bool){1});
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
            U32 _t3905; { U32 *_hp = (U32 *)peek_line(p); _t3905 = *_hp; free(_hp); }
            (void)_t3905;
            last_line = _t3905;
            ;
            U32 _t3906; { U32 *_hp = (U32 *)peek_col(p); _t3906 = *_hp; free(_hp); }
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
        Bool _t3939 = check(p, TokenType_LParen());
        (void)_t3939;
        if (_t3939) {
            Token *_t3933 = advance(p);
            (void)_t3933;
            ExprData *_t3934 = ExprData_FieldAccess(last_field);
            (void)_t3934;
            Expr *callee = Expr_new(_t3934, last_line, last_col, &p->path);
            (void)callee;
            ExprData_delete(_t3934, &(Bool){1});
            Expr *_t3935 = Expr_clone(obj);
            (void)_t3935;
            Expr_add_child(callee, _t3935);
            Expr *mcall = Expr_new(ExprData_FCall(), last_line, last_col, &p->path);
            (void)mcall;
            Expr_add_child(mcall, callee);
            while (1) {
                Bool _t3925 = check(p, TokenType_RParen());
                (void)_t3925;
                Bool _t3926 = check(p, TokenType_Eof());
                (void)_t3926;
                Bool _t3927 = Bool_not(_t3925);
                (void)_t3927;
                ;
                Bool _t3928 = Bool_not(_t3926);
                (void)_t3928;
                ;
                Bool _wcond3908 = Bool_and(_t3927, _t3928);
                (void)_wcond3908;
                ;
                ;
                if (_wcond3908) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3929 = check(p, TokenType_Ident());
                (void)_t3929;
                if (_t3929) {
                    U32 _t3919 = 1;
                    (void)_t3919;
                    U32 _t3920 = U32_add(p->pos, _t3919);
                    (void)_t3920;
                    ;
                    Bool _t3921; { Bool *_hp = (Bool *)U32_lt(&(U32){_t3920}, &p->count); _t3921 = *_hp; free(_hp); }
                    (void)_t3921;
                    ;
                    if (_t3921) {
                        U32 _t3914 = 1;
                        (void)_t3914;
                        U32 _t3915 = U32_add(p->pos, _t3914);
                        (void)_t3915;
                        ;
                        I64 _t3916 = U32_to_i64(_t3915);
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
                            U32 na_line; { U32 *_hp = (U32 *)peek_line(p); na_line = *_hp; free(_hp); }
                            (void)na_line;
                            U32 na_col; { U32 *_hp = (U32 *)peek_col(p); na_col = *_hp; free(_hp); }
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
                Bool _t3930 = check(p, TokenType_KwOwn());
                (void)_t3930;
                if (_t3930) {
                    Token *_t3922 = advance(p);
                    (void)_t3922;
                    Bool _t3923 = 1;
                    (void)_t3923;
                    is_own_arg = _t3923;
                    ;
                }
                ;
                Expr *marg = parse_expression(p);
                (void)marg;
                Bool _t3931 = Bool_clone(&(Bool){is_own_arg});
                (void)_t3931;
                ;
                marg->is_own_arg = _t3931;
                ;
                Expr_add_child(mcall, marg);
                Bool _t3932 = check(p, TokenType_Comma());
                (void)_t3932;
                if (_t3932) {
                    Token *_t3924 = advance(p);
                    (void)_t3924;
                }
                ;
            }
            Token *_t3936 = expect_token(p, TokenType_RParen());
            (void)_t3936;
            Token_delete(_t3936, &(Bool){1});
            Token_delete(_t3936, &(Bool){1});
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
        Token *_t3940 = expect_token(p, TokenType_Eq());
        (void)_t3940;
        Token_delete(_t3940, &(Bool){1});
        ExprData *_t3941 = ExprData_FieldAssign(last_field);
        (void)_t3941;
        Str_delete(last_field, &(Bool){1});
        Expr *fa = Expr_new(_t3941, t_line, t_col, &p->path);
        (void)fa;
        ExprData_delete(_t3941, &(Bool){1});
        Expr *_t3942 = Expr_clone(obj);
        (void)_t3942;
        Expr_delete(obj, &(Bool){1});
        Expr_add_child(fa, _t3942);
        Expr *_t3943 = parse_expression(p);
        (void)_t3943;
        Expr_add_child(fa, _t3943);
        Token_delete(_t3940, &(Bool){1});
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return fa;
    }
    ;
    Bool _t3952 = check(p, TokenType_Eq());
    (void)_t3952;
    if (_t3952) {
        Token *_t3944 = advance(p);
        (void)_t3944;
        Str *_t3945 = Str_clone(name);
        (void)_t3945;
        ExprData *_t3946 = ExprData_Assign(_t3945);
        (void)_t3946;
        Str_delete(_t3945, &(Bool){1});
        Expr *assign = Expr_new(_t3946, t_line, t_col, &p->path);
        (void)assign;
        ExprData_delete(_t3946, &(Bool){1});
        Expr *_t3947 = parse_expression(p);
        (void)_t3947;
        Expr_add_child(assign, _t3947);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return assign;
    }
    ;
    Bool _t3953 = check(p, TokenType_LParen());
    (void)_t3953;
    if (_t3953) {
        Expr *_t3948 = parse_call(p, name, t_line, t_col);
        (void)_t3948;
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return _t3948;
    }
    ;
    Str *_t3954 = Str_lit("Str", 3ULL);
    (void)_t3954;
    U64 _t3955; { U64 *_hp = (U64 *)Str_size(); _t3955 = *_hp; free(_hp); }
    (void)_t3955;
    U64 _t3956 = 8;
    (void)_t3956;
    Array *_va69 = Array_new(_t3954, &(U64){_t3955}, &(U64){_t3956});
    (void)_va69;
    Str_delete(_t3954, &(Bool){1});
    ;
    ;
    U64 _t3957 = 0;
    (void)_t3957;
    Str *_t3958 = Str_clone(&p->path);
    (void)_t3958;
    Array_set(_va69, &(U64){_t3957}, _t3958);
    ;
    U64 _t3959 = 1;
    (void)_t3959;
    Str *_t3960 = Str_lit(":", 1ULL);
    (void)_t3960;
    Array_set(_va69, &(U64){_t3959}, _t3960);
    ;
    U64 _t3961 = 2;
    (void)_t3961;
    Str *_t3962 = U32_to_str(&(U32){t_line});
    (void)_t3962;
    ;
    Array_set(_va69, &(U64){_t3961}, _t3962);
    ;
    U64 _t3963 = 3;
    (void)_t3963;
    Str *_t3964 = Str_lit(":", 1ULL);
    (void)_t3964;
    Array_set(_va69, &(U64){_t3963}, _t3964);
    ;
    U64 _t3965 = 4;
    (void)_t3965;
    Str *_t3966 = U32_to_str(&(U32){t_col});
    (void)_t3966;
    ;
    Array_set(_va69, &(U64){_t3965}, _t3966);
    ;
    U64 _t3967 = 5;
    (void)_t3967;
    Str *_t3968 = Str_lit(": expected ':=', ':', '=' or '(' after identifier '", 51ULL);
    (void)_t3968;
    Array_set(_va69, &(U64){_t3967}, _t3968);
    ;
    U64 _t3969 = 6;
    (void)_t3969;
    Str *_t3970 = Str_clone(name);
    (void)_t3970;
    Str_delete(name, &(Bool){1});
    Array_set(_va69, &(U64){_t3969}, _t3970);
    ;
    U64 _t3971 = 7;
    (void)_t3971;
    Str *_t3972 = Str_lit("'", 1ULL);
    (void)_t3972;
    Array_set(_va69, &(U64){_t3971}, _t3972);
    ;
    Str *_t3973 = Str_lit("src/self/parser.til:782:11", 26ULL);
    (void)_t3973;
    panic(_t3973, _va69);
    Str_delete(_t3973, &(Bool){1});
    U32 _t3974 = 0;
    (void)_t3974;
    U32 _t3975 = 0;
    (void)_t3975;
    Expr *_t3976 = Expr_new(ExprData_Body(), _t3974, _t3975, &p->path);
    (void)_t3976;
    ;
    ;
    return _t3976;
}

Expr * parse_statement(Parser * p) {
    (void)p;
    U32 t_line; { U32 *_hp = (U32 *)peek_line(p); t_line = *_hp; free(_hp); }
    (void)t_line;
    U32 t_col; { U32 *_hp = (U32 *)peek_col(p); t_col = *_hp; free(_hp); }
    (void)t_col;
    Token *t = peek(p);
    (void)t;
    Bool _t4113; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t4113 = *_hp; free(_hp); }
    (void)_t4113;
    if (_t4113) {
        Bool _t3977 = 0;
        (void)_t3977;
        Bool _t3978 = 0;
        (void)_t3978;
        Expr *_t3979 = parse_statement_ident(p, &(Bool){_t3977}, &(Bool){_t3978});
        (void)_t3979;
        ;
        ;
        ;
        ;
        ;
        return _t3979;
    }
    ;
    Bool _t4114; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwRef()); _t4114 = *_hp; free(_hp); }
    (void)_t4114;
    if (_t4114) {
        Token *_t3986 = advance(p);
        (void)_t3986;
        Bool ref_mut = 0;
        (void)ref_mut;
        Bool _t3987 = check(p, TokenType_KwMut());
        (void)_t3987;
        if (_t3987) {
            Token *_t3980 = advance(p);
            (void)_t3980;
            Bool _t3981 = 1;
            (void)_t3981;
            ref_mut = _t3981;
            ;
        }
        ;
        U32 i_line; { U32 *_hp = (U32 *)peek_line(p); i_line = *_hp; free(_hp); }
        (void)i_line;
        U32 i_col; { U32 *_hp = (U32 *)peek_col(p); i_col = *_hp; free(_hp); }
        (void)i_col;
        Str *iname = expect_text(p, TokenType_Ident());
        (void)iname;
        Bool _t3988 = 0;
        (void)_t3988;
        Bool _t3989 = 0;
        (void)_t3989;
        Bool _t3990 = 1;
        (void)_t3990;
        Bool _t3991 = 0;
        (void)_t3991;
        I32 _t3992 = 0;
        (void)_t3992;
        I32 _t3993 = 0;
        (void)_t3993;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(iname); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3988;
        dd->is_namespace = _t3989;
        dd->is_ref = _t3990;
        dd->is_own = _t3991;
        dd->field_offset = _t3992;
        dd->field_size = _t3993;
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
            Bool _t3982 = 1;
            (void)_t3982;
            dd->is_mut = _t3982;
            ;
        }
        ;
        Bool _t3994 = check(p, TokenType_Colon());
        (void)_t3994;
        if (_t3994) {
            Token *_t3983 = advance(p);
            (void)_t3983;
            Str_delete(&dd->explicit_type, &(Bool){0});
            { Str *_fa = expect_text(p, TokenType_Ident()); dd->explicit_type = *_fa; free(_fa); }
            Token *_t3984 = expect_token(p, TokenType_Eq());
            (void)_t3984;
            Token_delete(_t3984, &(Bool){1});
        } else {
            Token *_t3985 = expect_token(p, TokenType_ColonEq());
            (void)_t3985;
            Token_delete(_t3985, &(Bool){1});
        }
        ;
        ExprData *_t3995 = ExprData_Decl(dd);
        (void)_t3995;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3995, i_line, i_col, &p->path);
        (void)decl;
        ExprData_delete(_t3995, &(Bool){1});
        ;
        ;
        Expr *_t3996 = parse_expression(p);
        (void)_t3996;
        Expr_add_child(decl, _t3996);
        ;
        ;
        ;
        return decl;
    }
    ;
    Bool _t4115; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMut()); _t4115 = *_hp; free(_hp); }
    (void)_t4115;
    if (_t4115) {
        Token *_t3997 = advance(p);
        (void)_t3997;
        Bool _t3998 = 1;
        (void)_t3998;
        Bool _t3999 = 0;
        (void)_t3999;
        Expr *_t4000 = parse_statement_ident(p, &(Bool){_t3998}, &(Bool){_t3999});
        (void)_t4000;
        ;
        ;
        ;
        ;
        ;
        return _t4000;
    }
    ;
    Bool _t4116; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwReturn()); _t4116 = *_hp; free(_hp); }
    (void)_t4116;
    if (_t4116) {
        Token *_t4002 = advance(p);
        (void)_t4002;
        Expr *ret = Expr_new(ExprData_Return(), t_line, t_col, &p->path);
        (void)ret;
        Bool _t4003 = check(p, TokenType_RBrace());
        (void)_t4003;
        Bool _t4004 = check(p, TokenType_Eof());
        (void)_t4004;
        Bool _t4005 = Bool_not(_t4003);
        (void)_t4005;
        ;
        Bool _t4006 = Bool_not(_t4004);
        (void)_t4006;
        ;
        Bool _t4007 = Bool_and(_t4005, _t4006);
        (void)_t4007;
        ;
        ;
        if (_t4007) {
            Expr *_t4001 = parse_expression(p);
            (void)_t4001;
            Expr_add_child(ret, _t4001);
        }
        ;
        ;
        ;
        ;
        return ret;
    }
    ;
    Bool _t4117; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwIf()); _t4117 = *_hp; free(_hp); }
    (void)_t4117;
    if (_t4117) {
        Token *_t4015 = advance(p);
        (void)_t4015;
        Expr *node = Expr_new(ExprData_If(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t4016 = parse_expression(p);
        (void)_t4016;
        Expr_add_child(node, _t4016);
        Token *_t4017 = expect_token(p, TokenType_LBrace());
        (void)_t4017;
        Token_delete(_t4017, &(Bool){1});
        Expr *_t4018 = parse_block(p);
        (void)_t4018;
        Expr_add_child(node, _t4018);
        Bool _t4019 = check(p, TokenType_KwElse());
        (void)_t4019;
        if (_t4019) {
            Token *_t4013 = advance(p);
            (void)_t4013;
            Bool _t4014 = check(p, TokenType_KwIf());
            (void)_t4014;
            if (_t4014) {
                U32 _t4008; { U32 *_hp = (U32 *)peek_line(p); _t4008 = *_hp; free(_hp); }
                (void)_t4008;
                U32 _t4009; { U32 *_hp = (U32 *)peek_col(p); _t4009 = *_hp; free(_hp); }
                (void)_t4009;
                Expr *else_body = Expr_new(ExprData_Body(), _t4008, _t4009, &p->path);
                (void)else_body;
                ;
                ;
                Expr *_t4010 = parse_statement(p);
                (void)_t4010;
                Expr_add_child(else_body, _t4010);
                Expr_add_child(node, else_body);
            } else {
                Token *_t4011 = expect_token(p, TokenType_LBrace());
                (void)_t4011;
                Token_delete(_t4011, &(Bool){1});
                Expr *_t4012 = parse_block(p);
                (void)_t4012;
                Expr_add_child(node, _t4012);
            }
            ;
        }
        ;
        Token_delete(_t4017, &(Bool){1});
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4118; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t4118 = *_hp; free(_hp); }
    (void)_t4118;
    Bool _t4119; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t4119 = *_hp; free(_hp); }
    (void)_t4119;
    Bool _t4120 = Bool_or(_t4118, _t4119);
    (void)_t4120;
    ;
    ;
    Bool _t4121; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t4121 = *_hp; free(_hp); }
    (void)_t4121;
    Bool _t4122 = Bool_or(_t4120, _t4121);
    (void)_t4122;
    ;
    ;
    Bool _t4123; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t4123 = *_hp; free(_hp); }
    (void)_t4123;
    Bool _t4124 = Bool_or(_t4122, _t4123);
    (void)_t4124;
    ;
    ;
    if (_t4124) {
        Expr *_t4020 = parse_expression(p);
        (void)_t4020;
        ;
        ;
        ;
        return _t4020;
    }
    ;
    Bool _t4125; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t4125 = *_hp; free(_hp); }
    (void)_t4125;
    if (_t4125) {
        Token *_t4021 = advance(p);
        (void)_t4021;
        Expr *_t4022 = parse_block(p);
        (void)_t4022;
        ;
        ;
        ;
        return _t4022;
    }
    ;
    Bool _t4126; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwWhile()); _t4126 = *_hp; free(_hp); }
    (void)_t4126;
    if (_t4126) {
        Token *_t4023 = advance(p);
        (void)_t4023;
        Expr *node = Expr_new(ExprData_While(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t4024 = parse_expression(p);
        (void)_t4024;
        Expr_add_child(node, _t4024);
        Token *_t4025 = expect_token(p, TokenType_LBrace());
        (void)_t4025;
        Token_delete(_t4025, &(Bool){1});
        Expr *_t4026 = parse_block(p);
        (void)_t4026;
        Expr_add_child(node, _t4026);
        Token_delete(_t4025, &(Bool){1});
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4127; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFor()); _t4127 = *_hp; free(_hp); }
    (void)_t4127;
    if (_t4127) {
        Token *_t4028 = advance(p);
        (void)_t4028;
        U32 i_line; { U32 *_hp = (U32 *)peek_line(p); i_line = *_hp; free(_hp); }
        (void)i_line;
        U32 i_col; { U32 *_hp = (U32 *)peek_col(p); i_col = *_hp; free(_hp); }
        (void)i_col;
        Str *iname = expect_text(p, TokenType_Ident());
        (void)iname;
        ExprData *_t4029 = ExprData_ForIn(iname);
        (void)_t4029;
        Str_delete(iname, &(Bool){1});
        Expr *node = Expr_new(_t4029, i_line, i_col, &p->path);
        (void)node;
        ExprData_delete(_t4029, &(Bool){1});
        ;
        ;
        Bool _t4030 = check(p, TokenType_Colon());
        (void)_t4030;
        if (_t4030) {
            Token *_t4027 = advance(p);
            (void)_t4027;
            Str_delete(&node->struct_name, &(Bool){0});
            { Str *_fa = expect_text(p, TokenType_Ident()); node->struct_name = *_fa; free(_fa); }
        }
        ;
        Token *_t4031 = expect_token(p, TokenType_KwIn());
        (void)_t4031;
        Token_delete(_t4031, &(Bool){1});
        Expr *_t4032 = parse_expression(p);
        (void)_t4032;
        Expr_add_child(node, _t4032);
        Token *_t4033 = expect_token(p, TokenType_LBrace());
        (void)_t4033;
        Token_delete(_t4033, &(Bool){1});
        Expr *_t4034 = parse_block(p);
        (void)_t4034;
        Expr_add_child(node, _t4034);
        Token_delete(_t4031, &(Bool){1});
        Token_delete(_t4033, &(Bool){1});
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4128; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwSwitch()); _t4128 = *_hp; free(_hp); }
    (void)_t4128;
    if (_t4128) {
        Token *_t4058 = advance(p);
        (void)_t4058;
        Expr *node = Expr_new(ExprData_Switch(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t4059 = parse_expression(p);
        (void)_t4059;
        Expr_add_child(node, _t4059);
        Token *_t4060 = expect_token(p, TokenType_LBrace());
        (void)_t4060;
        Token_delete(_t4060, &(Bool){1});
        while (1) {
            Bool _t4046 = check(p, TokenType_RBrace());
            (void)_t4046;
            Bool _t4047 = check(p, TokenType_Eof());
            (void)_t4047;
            Bool _t4048 = Bool_not(_t4046);
            (void)_t4048;
            ;
            Bool _t4049 = Bool_not(_t4047);
            (void)_t4049;
            ;
            Bool _wcond4035 = Bool_and(_t4048, _t4049);
            (void)_wcond4035;
            ;
            ;
            if (_wcond4035) {
            } else {
                ;
                break;
            }
            ;
            Token *_t4050 = expect_token(p, TokenType_KwCase());
            (void)_t4050;
            Token_delete(_t4050, &(Bool){1});
            U32 _t4051; { U32 *_hp = (U32 *)peek_line(p); _t4051 = *_hp; free(_hp); }
            (void)_t4051;
            U32 _t4052; { U32 *_hp = (U32 *)peek_col(p); _t4052 = *_hp; free(_hp); }
            (void)_t4052;
            Expr *cn = Expr_new(ExprData_Case(), _t4051, _t4052, &p->path);
            (void)cn;
            ;
            ;
            Bool _t4053 = check(p, TokenType_Colon());
            (void)_t4053;
            Bool _t4054 = Bool_not(_t4053);
            (void)_t4054;
            ;
            if (_t4054) {
                Expr *_t4036 = parse_expression(p);
                (void)_t4036;
                Expr_add_child(cn, _t4036);
            }
            ;
            Token *_t4055 = expect_token(p, TokenType_Colon());
            (void)_t4055;
            Token_delete(_t4055, &(Bool){1});
            U32 _t4056; { U32 *_hp = (U32 *)peek_line(p); _t4056 = *_hp; free(_hp); }
            (void)_t4056;
            U32 _t4057; { U32 *_hp = (U32 *)peek_col(p); _t4057 = *_hp; free(_hp); }
            (void)_t4057;
            Expr *cb = Expr_new(ExprData_Body(), _t4056, _t4057, &p->path);
            (void)cb;
            ;
            ;
            while (1) {
                Bool _t4038 = check(p, TokenType_KwCase());
                (void)_t4038;
                Bool _t4039 = check(p, TokenType_RBrace());
                (void)_t4039;
                Bool _t4040 = Bool_not(_t4038);
                (void)_t4040;
                ;
                Bool _t4041 = Bool_not(_t4039);
                (void)_t4041;
                ;
                Bool _t4042 = check(p, TokenType_Eof());
                (void)_t4042;
                Bool _t4043 = Bool_and(_t4040, _t4041);
                (void)_t4043;
                ;
                ;
                Bool _t4044 = Bool_not(_t4042);
                (void)_t4044;
                ;
                Bool _wcond4037 = Bool_and(_t4043, _t4044);
                (void)_wcond4037;
                ;
                ;
                if (_wcond4037) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t4045 = parse_statement(p);
                (void)_t4045;
                Expr_add_child(cb, _t4045);
            }
            Expr_add_child(cn, cb);
            Expr_add_child(node, cn);
        }
        Token *_t4061 = expect_token(p, TokenType_RBrace());
        (void)_t4061;
        Token_delete(_t4061, &(Bool){1});
        Token_delete(_t4060, &(Bool){1});
        Token_delete(_t4061, &(Bool){1});
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4129; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwOwn()); _t4129 = *_hp; free(_hp); }
    (void)_t4129;
    if (_t4129) {
        Token *_t4102 = advance(p);
        (void)_t4102;
        Bool _t4103 = check(p, TokenType_Ident());
        (void)_t4103;
        Bool _t4104 = check(p, TokenType_KwMut());
        (void)_t4104;
        Bool _t4105 = Bool_or(_t4103, _t4104);
        (void)_t4105;
        ;
        ;
        if (_t4105) {
            Bool own_mut = 0;
            (void)own_mut;
            Bool _t4092 = check(p, TokenType_KwMut());
            (void)_t4092;
            if (_t4092) {
                Token *_t4062 = advance(p);
                (void)_t4062;
                Bool _t4063 = 1;
                (void)_t4063;
                own_mut = _t4063;
                ;
            }
            ;
            Bool _t4093 = check(p, TokenType_Ident());
            (void)_t4093;
            if (_t4093) {
                U32 _t4073 = 1;
                (void)_t4073;
                U32 _t4074 = U32_add(p->pos, _t4073);
                (void)_t4074;
                ;
                Bool _t4075; { Bool *_hp = (Bool *)U32_lt(&(U32){_t4074}, &p->count); _t4075 = *_hp; free(_hp); }
                (void)_t4075;
                ;
                if (_t4075) {
                    U32 _t4066 = 1;
                    (void)_t4066;
                    U32 _t4067 = U32_add(p->pos, _t4066);
                    (void)_t4067;
                    ;
                    I64 _t4068 = U32_to_i64(_t4067);
                    (void)_t4068;
                    ;
                    U64 *_t4069 = malloc(sizeof(U64)); *_t4069 = I64_to_u64(_t4068);
                    (void)_t4069;
                    ;
                    Token *nt = Vec_get(&p->tokens, _t4069);
                    (void)nt;
                    Bool _t4070; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_ColonEq()); _t4070 = *_hp; free(_hp); }
                    (void)_t4070;
                    Bool _t4071; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Colon()); _t4071 = *_hp; free(_hp); }
                    (void)_t4071;
                    U64_delete(_t4069, &(Bool){1});
                    Bool _t4072 = Bool_or(_t4070, _t4071);
                    (void)_t4072;
                    ;
                    ;
                    if (_t4072) {
                        Bool _t4064 = 1;
                        (void)_t4064;
                        Expr *_t4065 = parse_statement_ident(p, &(Bool){own_mut}, &(Bool){_t4064});
                        (void)_t4065;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        return _t4065;
                    }
                    ;
                }
                ;
            }
            ;
            if (own_mut) {
                Str *_t4076 = Str_lit("Str", 3ULL);
                (void)_t4076;
                U64 _t4077; { U64 *_hp = (U64 *)Str_size(); _t4077 = *_hp; free(_hp); }
                (void)_t4077;
                U64 _t4078 = 6;
                (void)_t4078;
                Array *_va70 = Array_new(_t4076, &(U64){_t4077}, &(U64){_t4078});
                (void)_va70;
                Str_delete(_t4076, &(Bool){1});
                ;
                ;
                U64 _t4079 = 0;
                (void)_t4079;
                Str *_t4080 = Str_clone(&p->path);
                (void)_t4080;
                Array_set(_va70, &(U64){_t4079}, _t4080);
                ;
                U64 _t4081 = 1;
                (void)_t4081;
                Str *_t4082 = Str_lit(":", 1ULL);
                (void)_t4082;
                Array_set(_va70, &(U64){_t4081}, _t4082);
                ;
                U64 _t4083 = 2;
                (void)_t4083;
                Str *_t4084 = U32_to_str(&(U32){t_line});
                (void)_t4084;
                Array_set(_va70, &(U64){_t4083}, _t4084);
                ;
                U64 _t4085 = 3;
                (void)_t4085;
                Str *_t4086 = Str_lit(":", 1ULL);
                (void)_t4086;
                Array_set(_va70, &(U64){_t4085}, _t4086);
                ;
                U64 _t4087 = 4;
                (void)_t4087;
                Str *_t4088 = U32_to_str(&(U32){t_col});
                (void)_t4088;
                Array_set(_va70, &(U64){_t4087}, _t4088);
                ;
                U64 _t4089 = 5;
                (void)_t4089;
                Str *_t4090 = Str_lit(": expected identifier after 'own mut'", 37ULL);
                (void)_t4090;
                Array_set(_va70, &(U64){_t4089}, _t4090);
                ;
                Str *_t4091 = Str_lit("src/self/parser.til:915:23", 26ULL);
                (void)_t4091;
                panic(_t4091, _va70);
                Str_delete(_t4091, &(Bool){1});
            }
            ;
        }
        ;
        Expr *expr = parse_expression(p);
        (void)expr;
        I64 _t4106 = 0;
        (void)_t4106;
        I64 _t4107 = 1;
        (void)_t4107;
        I64 primary_idx = I64_sub(_t4106, _t4107);
        (void)primary_idx;
        ;
        ;
        ;
        Expr *cur = Expr_clone(expr);
        (void)cur;
        while (1) {
            U64 _t4095; { U64 *_hp = (U64 *)Vec_len(&cur->children); _t4095 = *_hp; free(_hp); }
            (void)_t4095;
            U64 _t4096 = 0;
            (void)_t4096;
            Bool _t4097; { Bool *_hp = (Bool *)ExprData_is_FCall(&cur->data); _t4097 = *_hp; free(_hp); }
            (void)_t4097;
            Bool _t4098; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(&cur->data); _t4098 = *_hp; free(_hp); }
            (void)_t4098;
            Bool _t4099; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4095}, &(U64){_t4096}); _t4099 = *_hp; free(_hp); }
            (void)_t4099;
            ;
            ;
            Bool _t4100 = Bool_or(_t4097, _t4098);
            (void)_t4100;
            ;
            ;
            Bool _wcond4094 = Bool_and(_t4099, _t4100);
            (void)_wcond4094;
            ;
            ;
            if (_wcond4094) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t4101 = malloc(sizeof(U64));
            *_t4101 = 0;
            (void)_t4101;
            Expr *ch = Vec_get(&cur->children, _t4101);
            (void)ch;
            cur = Expr_clone(ch);
            U64_delete(_t4101, &(Bool){1});
        }
        Bool _t4108 = 1;
        (void)_t4108;
        cur->is_own_arg = _t4108;
        ;
        Expr_delete(cur, &(Bool){1});
        ;
        ;
        ;
        ;
        return expr;
    }
    ;
    Bool _t4130; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwBreak()); _t4130 = *_hp; free(_hp); }
    (void)_t4130;
    if (_t4130) {
        Token *_t4109 = advance(p);
        (void)_t4109;
        Expr *_t4110 = Expr_new(ExprData_Break(), t_line, t_col, &p->path);
        (void)_t4110;
        ;
        ;
        ;
        return _t4110;
    }
    ;
    Bool _t4131; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwContinue()); _t4131 = *_hp; free(_hp); }
    (void)_t4131;
    if (_t4131) {
        Token *_t4111 = advance(p);
        (void)_t4111;
        Expr *_t4112 = Expr_new(ExprData_Continue(), t_line, t_col, &p->path);
        (void)_t4112;
        ;
        ;
        ;
        return _t4112;
    }
    ;
    Str *_t4132 = Str_lit("Str", 3ULL);
    (void)_t4132;
    U64 _t4133; { U64 *_hp = (U64 *)Str_size(); _t4133 = *_hp; free(_hp); }
    (void)_t4133;
    U64 _t4134 = 8;
    (void)_t4134;
    Array *_va71 = Array_new(_t4132, &(U64){_t4133}, &(U64){_t4134});
    (void)_va71;
    Str_delete(_t4132, &(Bool){1});
    ;
    ;
    U64 _t4135 = 0;
    (void)_t4135;
    Str *_t4136 = Str_clone(&p->path);
    (void)_t4136;
    Array_set(_va71, &(U64){_t4135}, _t4136);
    ;
    U64 _t4137 = 1;
    (void)_t4137;
    Str *_t4138 = Str_lit(":", 1ULL);
    (void)_t4138;
    Array_set(_va71, &(U64){_t4137}, _t4138);
    ;
    U64 _t4139 = 2;
    (void)_t4139;
    Str *_t4140 = U32_to_str(&(U32){t_line});
    (void)_t4140;
    ;
    Array_set(_va71, &(U64){_t4139}, _t4140);
    ;
    U64 _t4141 = 3;
    (void)_t4141;
    Str *_t4142 = Str_lit(":", 1ULL);
    (void)_t4142;
    Array_set(_va71, &(U64){_t4141}, _t4142);
    ;
    U64 _t4143 = 4;
    (void)_t4143;
    Str *_t4144 = U32_to_str(&(U32){t_col});
    (void)_t4144;
    ;
    Array_set(_va71, &(U64){_t4143}, _t4144);
    ;
    U64 _t4145 = 5;
    (void)_t4145;
    Str *_t4146 = Str_lit(": expected statement, found '", 29ULL);
    (void)_t4146;
    Array_set(_va71, &(U64){_t4145}, _t4146);
    ;
    U64 _t4147 = 6;
    (void)_t4147;
    Str *_t4148 = Str_clone(&t->text);
    (void)_t4148;
    Array_set(_va71, &(U64){_t4147}, _t4148);
    ;
    U64 _t4149 = 7;
    (void)_t4149;
    Str *_t4150 = Str_lit("'", 1ULL);
    (void)_t4150;
    Array_set(_va71, &(U64){_t4149}, _t4150);
    ;
    Str *_t4151 = Str_lit("src/self/parser.til:942:11", 26ULL);
    (void)_t4151;
    panic(_t4151, _va71);
    Str_delete(_t4151, &(Bool){1});
    U32 _t4152 = 0;
    (void)_t4152;
    U32 _t4153 = 0;
    (void)_t4153;
    Expr *_t4154 = Expr_new(ExprData_Body(), _t4152, _t4153, &p->path);
    (void)_t4154;
    ;
    ;
    return _t4154;
}

Expr * parse(Vec * tokens, Str * path, Str * mode_out) {
    (void)tokens;
    (void)path;
    (void)mode_out;
    U64 _t4166; { U64 *_hp = (U64 *)Vec_len(tokens); _t4166 = *_hp; free(_hp); }
    (void)_t4166;
    I64 _t4167 = 0;
    (void)_t4167;
    Parser *p = malloc(sizeof(Parser));
    { Vec *_ca = Vec_clone(tokens); p->tokens = *_ca; free(_ca); }
    p->count = _t4166;
    p->pos = _t4167;
    { Str *_ca = Str_clone(path); p->path = *_ca; free(_ca); }
    (void)p;
    ;
    ;
    Bool _t4168 = check(p, TokenType_KwMode());
    (void)_t4168;
    if (_t4168) {
        Token *_t4159 = advance(p);
        (void)_t4159;
        Bool _t4160 = check(p, TokenType_Ident());
        (void)_t4160;
        Bool _t4161 = check(p, TokenType_KwTest());
        (void)_t4161;
        Bool _t4162 = Bool_or(_t4160, _t4161);
        (void)_t4162;
        ;
        ;
        if (_t4162) {
            Str *_t4155 = Str_clone(&peek(p)->text);
            (void)_t4155;
            U64 _t4156; { U64 *_hp = (U64 *)Str_size(); _t4156 = *_hp; free(_hp); }
            (void)_t4156;
            swap(mode_out, _t4155, _t4156);
            Str_delete(_t4155, &(Bool){1});
            ;
            Token *_t4157 = advance(p);
            (void)_t4157;
        } else {
            Token *_t4158 = expect_token(p, TokenType_Ident());
            (void)_t4158;
            Token_delete(_t4158, &(Bool){1});
        }
        ;
    }
    ;
    U32 _t4169 = 1;
    (void)_t4169;
    U32 _t4170 = 1;
    (void)_t4170;
    Expr *root = Expr_new(ExprData_Body(), _t4169, _t4170, &p->path);
    (void)root;
    ;
    ;
    while (1) {
        Bool _t4164 = check(p, TokenType_Eof());
        (void)_t4164;
        Bool _wcond4163 = Bool_not(_t4164);
        (void)_wcond4163;
        ;
        if (_wcond4163) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t4165 = parse_statement(p);
        (void)_t4165;
        Expr_add_child(root, _t4165);
    }
    Parser_delete(p, &(Bool){1});
    return root;
}

