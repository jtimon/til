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

Bool * check(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Bool _t3058; { Bool *_hp = (Bool *)TokenType_eq(&peek(p)->type, type); _t3058 = *_hp; free(_hp); }
    (void)_t3058;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t3058; return _r; }
}

void expect_token(Parser * p, TokenType * type) {
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

Expr * parse_fn_signature(Parser * p, U32 * line, U32 * col) {
    (void)p;
    (void)line;
    (void)col;
    Bool _t3148; { Bool *_hp = (Bool *)check(p, TokenType_LParen()); _t3148 = *_hp; free(_hp); }
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
        Bool _t3121; { Bool *_hp = (Bool *)check(p, TokenType_RParen()); _t3121 = *_hp; free(_hp); }
        (void)_t3121;
        Bool _t3122; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3122 = *_hp; free(_hp); }
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
        Bool _t3125; { Bool *_hp = (Bool *)check(p, TokenType_KwMut()); _t3125 = *_hp; free(_hp); }
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
        Bool _t3126; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3126 = *_hp; free(_hp); }
        (void)_t3126;
        if (_t3126) {
            Token *_t3120 = advance(p);
            (void)_t3120;
        }
        ;
    }
    expect_token(p, TokenType_RParen());
    Str *return_type = Str_lit("", 0ULL);
    (void)return_type;
    Bool _t3155; { Bool *_hp = (Bool *)check(p, TokenType_KwReturns()); _t3155 = *_hp; free(_hp); }
    (void)_t3155;
    if (_t3155) {
        Token *_t3127 = advance(p);
        (void)_t3127;
        return_type = expect_text(p, TokenType_Ident());
    }
    ;
    Str *_t3156 = Str_lit("Str", 3ULL);
    (void)_t3156;
    U64 _t3157; { U64 *_hp = (U64 *)Str_size(); _t3157 = *_hp; free(_hp); }
    (void)_t3157;
    Str *_t3158 = Str_lit("Str", 3ULL);
    (void)_t3158;
    U64 _t3159; { U64 *_hp = (U64 *)Str_size(); _t3159 = *_hp; free(_hp); }
    (void)_t3159;
    Str *_t3160 = Str_lit("Bool", 4ULL);
    (void)_t3160;
    U64 _t3161; { U64 *_hp = (U64 *)Bool_size(); _t3161 = *_hp; free(_hp); }
    (void)_t3161;
    Str *_t3162 = Str_lit("Bool", 4ULL);
    (void)_t3162;
    U64 _t3163; { U64 *_hp = (U64 *)Bool_size(); _t3163 = *_hp; free(_hp); }
    (void)_t3163;
    Str *_t3164 = Str_lit("Bool", 4ULL);
    (void)_t3164;
    U64 _t3165; { U64 *_hp = (U64 *)Bool_size(); _t3165 = *_hp; free(_hp); }
    (void)_t3165;
    Str *_t3166 = Str_lit("I64", 3ULL);
    (void)_t3166;
    U64 _t3167; { U64 *_hp = (U64 *)I64_size(); _t3167 = *_hp; free(_hp); }
    (void)_t3167;
    Str *_t3168 = Str_lit("I64", 3ULL);
    (void)_t3168;
    U64 _t3169; { U64 *_hp = (U64 *)I64_size(); _t3169 = *_hp; free(_hp); }
    (void)_t3169;
    I64 _t3170 = 0;
    (void)_t3170;
    I64 _t3171 = 1;
    (void)_t3171;
    I64 _t3172 = I64_sub(_t3170, _t3171);
    (void)_t3172;
    ;
    ;
    I64 _t3173 = 0;
    (void)_t3173;
    I64 _t3174 = 1;
    (void)_t3174;
    I64 _t3175 = I64_sub(_t3173, _t3174);
    (void)_t3175;
    ;
    ;
    U32 _t3176 = 0;
    (void)_t3176;
    I32 _t3177 = I64_to_i32(_t3172);
    (void)_t3177;
    ;
    I32 _t3178 = I64_to_i32(_t3175);
    (void)_t3178;
    ;
    Bool _t3179 = 0;
    (void)_t3179;
    Bool _t3180 = 0;
    (void)_t3180;
    FunctionDef *fd = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(FuncType_Func()); fd->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3156, &(U64){_t3157}); fd->param_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3158, &(U64){_t3159}); fd->param_types = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3160, &(U64){_t3161}); fd->param_muts = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3162, &(U64){_t3163}); fd->param_owns = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3164, &(U64){_t3165}); fd->param_shallows = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3166, &(U64){_t3167}); fd->param_fn_sigs = *_ca; free(_ca); }
    fd->nparam = _t3176;
    { Vec *_ca = Vec_new(_t3168, &(U64){_t3169}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3177;
    fd->kwargs_index = _t3178;
    fd->return_is_ref = _t3179;
    fd->return_is_shallow = _t3180;
    (void)fd;
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
    Str_delete(_t3168, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    U64 _t3181; { U64 *_hp = (U64 *)Str_len(return_type); _t3181 = *_hp; free(_hp); }
    (void)_t3181;
    U64 _t3182 = 0;
    (void)_t3182;
    Bool _t3183; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3181}, &(U64){_t3182}); _t3183 = *_hp; free(_hp); }
    (void)_t3183;
    ;
    ;
    if (_t3183) {
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
    Bool _t3184 = 0;
    (void)_t3184;
    fd->return_is_ref = _t3184;
    ;
    Bool _t3185 = 0;
    (void)_t3185;
    fd->return_is_shallow = _t3185;
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
    fd->variadic_index = _t3189;
    ;
    I64 _t3190 = 0;
    (void)_t3190;
    I64 _t3191 = 1;
    (void)_t3191;
    I64 _t3192 = I64_sub(_t3190, _t3191);
    (void)_t3192;
    ;
    ;
    I32 _t3193 = I64_to_i32(_t3192);
    (void)_t3193;
    ;
    fd->kwargs_index = _t3193;
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
    ExprData *_t3194 = ExprData_FuncDef(fd);
    (void)_t3194;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *sig = Expr_new(_t3194, DEREF(line), DEREF(col), &p->path);
    (void)sig;
    ExprData_delete(_t3194, &(Bool){1});
    return sig;
}

Expr * parse_block(Parser * p) {
    (void)p;
    U32 _t3201; { U32 *_hp = (U32 *)peek_line(p); _t3201 = *_hp; free(_hp); }
    (void)_t3201;
    U32 _t3202; { U32 *_hp = (U32 *)peek_col(p); _t3202 = *_hp; free(_hp); }
    (void)_t3202;
    Expr *body = Expr_new(ExprData_Body(), _t3201, _t3202, &p->path);
    (void)body;
    ;
    ;
    while (1) {
        Bool _t3196; { Bool *_hp = (Bool *)check(p, TokenType_RBrace()); _t3196 = *_hp; free(_hp); }
        (void)_t3196;
        Bool _t3197; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3197 = *_hp; free(_hp); }
        (void)_t3197;
        Bool _t3198 = Bool_not(_t3196);
        (void)_t3198;
        ;
        Bool _t3199 = Bool_not(_t3197);
        (void)_t3199;
        ;
        Bool _wcond3195 = Bool_and(_t3198, _t3199);
        (void)_wcond3195;
        ;
        ;
        if (_wcond3195) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t3200 = parse_statement(p);
        (void)_t3200;
        Expr_add_child(body, _t3200);
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
                                Str *_t3209 = Str_lit("src/self/parser.til:136:17", 26ULL);
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
    expect_token(p, TokenType_LParen());
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
    Str *_t3419 = Str_lit("I64", 3ULL);
    (void)_t3419;
    U64 _t3420; { U64 *_hp = (U64 *)I64_size(); _t3420 = *_hp; free(_hp); }
    (void)_t3420;
    I64 _t3421 = 0;
    (void)_t3421;
    I64 _t3422 = 1;
    (void)_t3422;
    I64 _t3423 = I64_sub(_t3421, _t3422);
    (void)_t3423;
    ;
    ;
    I64 _t3424 = 0;
    (void)_t3424;
    I64 _t3425 = 1;
    (void)_t3425;
    I64 _t3426 = I64_sub(_t3424, _t3425);
    (void)_t3426;
    ;
    ;
    U32 _t3427 = 0;
    (void)_t3427;
    I32 _t3428 = I64_to_i32(_t3423);
    (void)_t3428;
    ;
    I32 _t3429 = I64_to_i32(_t3426);
    (void)_t3429;
    ;
    Bool _t3430 = 0;
    (void)_t3430;
    Bool _t3431 = 0;
    (void)_t3431;
    FunctionDef *fd = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(FuncType_Func()); fd->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3407, &(U64){_t3408}); fd->param_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3409, &(U64){_t3410}); fd->param_types = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3411, &(U64){_t3412}); fd->param_muts = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3413, &(U64){_t3414}); fd->param_owns = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3415, &(U64){_t3416}); fd->param_shallows = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3417, &(U64){_t3418}); fd->param_fn_sigs = *_ca; free(_ca); }
    fd->nparam = _t3427;
    { Vec *_ca = Vec_new(_t3419, &(U64){_t3420}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3428;
    fd->kwargs_index = _t3429;
    fd->return_is_ref = _t3430;
    fd->return_is_shallow = _t3431;
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
    ;
    ;
    ;
    ;
    ;
    FuncType_delete(&fd->func_type, &(Bool){0});
    { FuncType *_fa = FuncType_clone(ft); fd->func_type = *_fa; free(_fa); }
    Str *_t3432 = Str_lit("Expr", 4ULL);
    (void)_t3432;
    U64 _t3433; { U64 *_hp = (U64 *)Expr_size(); _t3433 = *_hp; free(_hp); }
    (void)_t3433;
    Vec *def_exprs = Vec_new(_t3432, &(U64){_t3433});
    (void)def_exprs;
    Str_delete(_t3432, &(Bool){1});
    ;
    while (1) {
        Bool _t3333; { Bool *_hp = (Bool *)check(p, TokenType_RParen()); _t3333 = *_hp; free(_hp); }
        (void)_t3333;
        Bool _t3334; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3334 = *_hp; free(_hp); }
        (void)_t3334;
        Bool _t3335 = Bool_not(_t3333);
        (void)_t3335;
        ;
        Bool _t3336 = Bool_not(_t3334);
        (void)_t3336;
        ;
        Bool _wcond3216 = Bool_and(_t3335, _t3336);
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
        Bool _t3337; { Bool *_hp = (Bool *)check(p, TokenType_KwShallow()); _t3337 = *_hp; free(_hp); }
        (void)_t3337;
        if (_t3337) {
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
        Bool _t3338; { Bool *_hp = (Bool *)check(p, TokenType_KwOwn()); _t3338 = *_hp; free(_hp); }
        (void)_t3338;
        if (_t3338) {
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
        Bool _t3339; { Bool *_hp = (Bool *)check(p, TokenType_KwMut()); _t3339 = *_hp; free(_hp); }
        (void)_t3339;
        if (_t3339) {
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
        Bool _t3340; { Bool *_hp = (Bool *)check(p, TokenType_Colon()); _t3340 = *_hp; free(_hp); }
        (void)_t3340;
        Bool _t3341 = Bool_not(_t3340);
        (void)_t3341;
        ;
        if (_t3341) {
            tp = Str_clone(pname);
            nm = Str_lit("", 0ULL);
        } else {
            expect_token(p, TokenType_Colon());
            Bool _t3316; { Bool *_hp = (Bool *)check(p, TokenType_DotDotDot()); _t3316 = *_hp; free(_hp); }
            (void)_t3316;
            if (_t3316) {
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
                    U32 _t3230; { U32 *_hp = (U32 *)peek_line(p); _t3230 = *_hp; free(_hp); }
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
                    U32 _t3235; { U32 *_hp = (U32 *)peek_col(p); _t3235 = *_hp; free(_hp); }
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
                    Str *_t3240 = Str_lit("src/self/parser.til:167:27", 26ULL);
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
                    Str *_t3246 = Str_lit("src/self/parser.til:171:27", 26ULL);
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
                    Str *_t3252 = Str_lit("src/self/parser.til:174:27", 26ULL);
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
                Bool _t3315; { Bool *_hp = (Bool *)check(p, TokenType_DotDot()); _t3315 = *_hp; free(_hp); }
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
                        Str *_t3275 = Str_lit("src/self/parser.til:182:35", 26ULL);
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
                        Str *_t3281 = Str_lit("src/self/parser.til:183:35", 26ULL);
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
                        Str *_t3287 = Str_lit("src/self/parser.til:184:39", 26ULL);
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
                        Str *_t3293 = Str_lit("src/self/parser.til:185:69", 26ULL);
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
                        Str *_t3299 = Str_lit("src/self/parser.til:187:27", 26ULL);
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
        I64 _t3342 = 0;
        (void)_t3342;
        I64 _t3343 = 1;
        (void)_t3343;
        I64 fn_sig_idx = I64_sub(_t3342, _t3343);
        (void)fn_sig_idx;
        ;
        ;
        Str *_t3344 = Str_lit("Fn", 2ULL);
        (void)_t3344;
        Bool _t3345; { Bool *_hp = (Bool *)Str_eq(tp, _t3344); _t3345 = *_hp; free(_hp); }
        (void)_t3345;
        Str_delete(_t3344, &(Bool){1});
        if (_t3345) {
            U32 _t3319; { U32 *_hp = (U32 *)peek_line(p); _t3319 = *_hp; free(_hp); }
            (void)_t3319;
            U32 _t3320; { U32 *_hp = (U32 *)peek_col(p); _t3320 = *_hp; free(_hp); }
            (void)_t3320;
            Expr *sig = parse_fn_signature(p, &(U32){_t3319}, &(U32){_t3320});
            (void)sig;
            ;
            ;
            U32 _t3321 = 0;
            (void)_t3321;
            Bool _t3322; { Bool *_hp = (Bool *)U32_neq(&sig->line, &(U32){_t3321}); _t3322 = *_hp; free(_hp); }
            (void)_t3322;
            ;
            if (_t3322) {
                U64 _t3317; { U64 *_hp = (U64 *)Vec_len(def_exprs); _t3317 = *_hp; free(_hp); }
                (void)_t3317;
                I64 _t3318 = U64_to_i64(_t3317);
                (void)_t3318;
                ;
                fn_sig_idx = _t3318;
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
        I64 _t3346 = 0;
        (void)_t3346;
        I64 _t3347 = 1;
        (void)_t3347;
        I64 has_default = I64_sub(_t3346, _t3347);
        (void)has_default;
        ;
        ;
        Bool _t3348; { Bool *_hp = (Bool *)check(p, TokenType_Eq()); _t3348 = *_hp; free(_hp); }
        (void)_t3348;
        if (_t3348) {
            Token *_t3323 = advance(p);
            (void)_t3323;
            U64 _t3324; { U64 *_hp = (U64 *)Vec_len(def_exprs); _t3324 = *_hp; free(_hp); }
            (void)_t3324;
            I64 _t3325 = U64_to_i64(_t3324);
            (void)_t3325;
            ;
            has_default = _t3325;
            ;
            Expr *def_expr = parse_expression(p);
            (void)def_expr;
            Vec_push(def_exprs, def_expr);
        }
        ;
        I64 _t3349 = 0;
        (void)_t3349;
        I64 _t3350 = 1;
        (void)_t3350;
        I64 _t3351 = I64_sub(_t3349, _t3350);
        (void)_t3351;
        ;
        ;
        I32 _t3352 = I64_to_i32(_t3351);
        (void)_t3352;
        ;
        Bool _t3353; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3352}); _t3353 = *_hp; free(_hp); }
        (void)_t3353;
        ;
        Bool _t3354 = Bool_not(is_variadic);
        (void)_t3354;
        ;
        I64 _t3355 = 0;
        (void)_t3355;
        I64 _t3356 = 1;
        (void)_t3356;
        I64 _t3357 = I64_sub(_t3355, _t3356);
        (void)_t3357;
        ;
        ;
        Bool _t3358 = Bool_and(_t3353, _t3354);
        (void)_t3358;
        ;
        ;
        Bool _t3359 = I64_eq(has_default, _t3357);
        (void)_t3359;
        ;
        Bool _t3360 = Bool_and(_t3358, _t3359);
        (void)_t3360;
        ;
        ;
        if (_t3360) {
            Str *_t3326 = Str_lit("Str", 3ULL);
            (void)_t3326;
            U64 _t3327; { U64 *_hp = (U64 *)Str_size(); _t3327 = *_hp; free(_hp); }
            (void)_t3327;
            U64 _t3328 = 1;
            (void)_t3328;
            Array *_va65 = Array_new(_t3326, &(U64){_t3327}, &(U64){_t3328});
            (void)_va65;
            Str_delete(_t3326, &(Bool){1});
            ;
            ;
            U64 _t3329 = 0;
            (void)_t3329;
            Str *_t3330 = Str_lit("positional param not allowed after variadic", 43ULL);
            (void)_t3330;
            Array_set(_va65, &(U64){_t3329}, _t3330);
            ;
            Str *_t3331 = Str_lit("src/self/parser.til:226:19", 26ULL);
            (void)_t3331;
            panic(_t3331, _va65);
            Str_delete(_t3331, &(Bool){1});
        }
        ;
        Vec_push(&fd->param_defaults, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = has_default; _oa; }));
        Bool _t3361; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3361 = *_hp; free(_hp); }
        (void)_t3361;
        if (_t3361) {
            Token *_t3332 = advance(p);
            (void)_t3332;
        }
        ;
    }
    expect_token(p, TokenType_RParen());
    Bool _t3434; { Bool *_hp = (Bool *)check(p, TokenType_KwReturns()); _t3434 = *_hp; free(_hp); }
    (void)_t3434;
    if (_t3434) {
        Token *_t3367 = advance(p);
        (void)_t3367;
        Bool _t3368; { Bool *_hp = (Bool *)check(p, TokenType_KwRef()); _t3368 = *_hp; free(_hp); }
        (void)_t3368;
        if (_t3368) {
            Token *_t3362 = advance(p);
            (void)_t3362;
            Bool _t3363 = 1;
            (void)_t3363;
            fd->return_is_ref = _t3363;
            ;
        } else {
            Bool _t3366; { Bool *_hp = (Bool *)check(p, TokenType_KwShallow()); _t3366 = *_hp; free(_hp); }
            (void)_t3366;
            if (_t3366) {
                Token *_t3364 = advance(p);
                (void)_t3364;
                Bool _t3365 = 1;
                (void)_t3365;
                fd->return_is_shallow = _t3365;
                ;
            }
            ;
        }
        ;
        Str_delete(&fd->return_type, &(Bool){0});
        { Str *_fa = expect_text(p, TokenType_Ident()); fd->return_type = *_fa; free(_fa); }
    }
    ;
    ExprData *_t3435 = ExprData_FuncDef(fd);
    (void)_t3435;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *def = Expr_new(_t3435, kw_line, kw_col, &p->path);
    (void)def;
    ExprData_delete(_t3435, &(Bool){1});
    Bool _t3436; { Bool *_hp = (Bool *)check(p, TokenType_LBrace()); _t3436 = *_hp; free(_hp); }
    (void)_t3436;
    if (_t3436) {
        expect_token(p, TokenType_LBrace());
        Expr *_t3369 = parse_block(p);
        (void)_t3369;
        Expr_add_child(def, _t3369);
    } else {
        Bool _t3390; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Func()); _t3390 = *_hp; free(_hp); }
        (void)_t3390;
        Bool _t3391; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Proc()); _t3391 = *_hp; free(_hp); }
        (void)_t3391;
        Bool _t3392 = Bool_not(_t3390);
        (void)_t3392;
        ;
        Bool _t3393 = Bool_not(_t3391);
        (void)_t3393;
        ;
        Bool _t3394 = Bool_and(_t3392, _t3393);
        (void)_t3394;
        ;
        ;
        if (_t3394) {
            Str *_t3370 = Str_lit("Str", 3ULL);
            (void)_t3370;
            U64 _t3371; { U64 *_hp = (U64 *)Str_size(); _t3371 = *_hp; free(_hp); }
            (void)_t3371;
            U64 _t3372 = 8;
            (void)_t3372;
            Array *_va66 = Array_new(_t3370, &(U64){_t3371}, &(U64){_t3372});
            (void)_va66;
            Str_delete(_t3370, &(Bool){1});
            ;
            ;
            U64 _t3373 = 0;
            (void)_t3373;
            Str *_t3374 = Str_clone(&p->path);
            (void)_t3374;
            Array_set(_va66, &(U64){_t3373}, _t3374);
            ;
            U64 _t3375 = 1;
            (void)_t3375;
            Str *_t3376 = Str_lit(":", 1ULL);
            (void)_t3376;
            Array_set(_va66, &(U64){_t3375}, _t3376);
            ;
            U64 _t3377 = 2;
            (void)_t3377;
            Str *_t3378 = U32_to_str(&(U32){kw_line});
            (void)_t3378;
            Array_set(_va66, &(U64){_t3377}, _t3378);
            ;
            U64 _t3379 = 3;
            (void)_t3379;
            Str *_t3380 = Str_lit(":", 1ULL);
            (void)_t3380;
            Array_set(_va66, &(U64){_t3379}, _t3380);
            ;
            U64 _t3381 = 4;
            (void)_t3381;
            Str *_t3382 = U32_to_str(&(U32){kw_col});
            (void)_t3382;
            Array_set(_va66, &(U64){_t3381}, _t3382);
            ;
            U64 _t3383 = 5;
            (void)_t3383;
            Str *_t3384 = Str_lit(": ", 2ULL);
            (void)_t3384;
            Array_set(_va66, &(U64){_t3383}, _t3384);
            ;
            U64 _t3385 = 6;
            (void)_t3385;
            Str *_t3386 = func_type_name(ft);
            (void)_t3386;
            Array_set(_va66, &(U64){_t3385}, _t3386);
            ;
            U64 _t3387 = 7;
            (void)_t3387;
            Str *_t3388 = Str_lit(" requires a body", 16ULL);
            (void)_t3388;
            Array_set(_va66, &(U64){_t3387}, _t3388);
            ;
            Str *_t3389 = Str_lit("src/self/parser.til:254:19", 26ULL);
            (void)_t3389;
            panic(_t3389, _va66);
            Str_delete(_t3389, &(Bool){1});
        }
        ;
    }
    ;
    FuncType_delete(ft, &(Bool){1});
    ;
    ;
    {
        U64 _fi3395 = 0;
        (void)_fi3395;
        while (1) {
            U64 _t3397 = 0;
            (void)_t3397;
            U64 _t3398; { U64 *_hp = (U64 *)Vec_len(def_exprs); _t3398 = *_hp; free(_hp); }
            (void)_t3398;
            Range *_t3399 = Range_new(_t3397, _t3398);
            (void)_t3399;
            ;
            ;
            U64 _t3400; { U64 *_hp = (U64 *)Range_len(_t3399); _t3400 = *_hp; free(_hp); }
            (void)_t3400;
            Range_delete(_t3399, &(Bool){1});
            Bool _wcond3396; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3395}, &(U64){_t3400}); _wcond3396 = *_hp; free(_hp); }
            (void)_wcond3396;
            ;
            if (_wcond3396) {
            } else {
                ;
                break;
            }
            ;
            U64 _t3401 = 0;
            (void)_t3401;
            U64 _t3402; { U64 *_hp = (U64 *)Vec_len(def_exprs); _t3402 = *_hp; free(_hp); }
            (void)_t3402;
            Range *_t3403 = Range_new(_t3401, _t3402);
            (void)_t3403;
            ;
            ;
            U64 *i = Range_get(_t3403, _fi3395);
            (void)i;
            Range_delete(_t3403, &(Bool){1});
            U64 _t3404 = 1;
            (void)_t3404;
            U64 _t3405 = U64_add(_fi3395, _t3404);
            (void)_t3405;
            ;
            _fi3395 = _t3405;
            ;
            Expr *de = Vec_get(def_exprs, i);
            (void)de;
            Expr *_t3406 = Expr_clone(de);
            (void)_t3406;
            U64_delete(i, &(Bool){1});
            Expr_add_child(def, _t3406);
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
    Token *_t3449 = advance(p);
    (void)_t3449;
    Expr *def = Expr_new(ExprData_StructDef(), kw_line, kw_col, &p->path);
    (void)def;
    ;
    ;
    Bool _t3450 = Bool_clone(&(Bool){is_ext});
    (void)_t3450;
    ;
    def->is_ext = _t3450;
    ;
    expect_token(p, TokenType_LBrace());
    U32 _t3451; { U32 *_hp = (U32 *)peek_line(p); _t3451 = *_hp; free(_hp); }
    (void)_t3451;
    U32 _t3452; { U32 *_hp = (U32 *)peek_col(p); _t3452 = *_hp; free(_hp); }
    (void)_t3452;
    Expr *body = Expr_new(ExprData_Body(), _t3451, _t3452, &p->path);
    (void)body;
    ;
    ;
    Bool in_namespace = 0;
    (void)in_namespace;
    while (1) {
        Bool _t3442; { Bool *_hp = (Bool *)check(p, TokenType_RBrace()); _t3442 = *_hp; free(_hp); }
        (void)_t3442;
        Bool _t3443; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3443 = *_hp; free(_hp); }
        (void)_t3443;
        Bool _t3444 = Bool_not(_t3442);
        (void)_t3444;
        ;
        Bool _t3445 = Bool_not(_t3443);
        (void)_t3445;
        ;
        Bool _wcond3437 = Bool_and(_t3444, _t3445);
        (void)_wcond3437;
        ;
        ;
        if (_wcond3437) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3446; { Bool *_hp = (Bool *)check(p, TokenType_KwNamespace()); _t3446 = *_hp; free(_hp); }
        (void)_t3446;
        if (_t3446) {
            Token *_t3438 = advance(p);
            (void)_t3438;
            expect_token(p, TokenType_Colon());
            Bool _t3439 = 1;
            (void)_t3439;
            in_namespace = _t3439;
            ;
            ;
            continue;
        }
        ;
        Expr *stmt = parse_statement(p);
        (void)stmt;
        Bool _t3447; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3447 = *_hp; free(_hp); }
        (void)_t3447;
        Bool _t3448 = Bool_and(in_namespace, _t3447);
        (void)_t3448;
        ;
        if (_t3448) {
            Bool _t3441; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3441 = *_hp; free(_hp); }
            (void)_t3441;
            if (_t3441) {
                Declaration *dd = ExprData_get_Decl(&stmt->data);
                (void)dd;
                Bool _t3440 = 1;
                (void)_t3440;
                dd->is_namespace = _t3440;
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
    Token *_t3475 = advance(p);
    (void)_t3475;
    Expr *def = Expr_new(ExprData_EnumDef(), kw_line, kw_col, &p->path);
    (void)def;
    ;
    ;
    expect_token(p, TokenType_LBrace());
    U32 _t3476; { U32 *_hp = (U32 *)peek_line(p); _t3476 = *_hp; free(_hp); }
    (void)_t3476;
    U32 _t3477; { U32 *_hp = (U32 *)peek_col(p); _t3477 = *_hp; free(_hp); }
    (void)_t3477;
    Expr *body = Expr_new(ExprData_Body(), _t3476, _t3477, &p->path);
    (void)body;
    ;
    ;
    Bool in_namespace = 0;
    (void)in_namespace;
    while (1) {
        Bool _t3470; { Bool *_hp = (Bool *)check(p, TokenType_RBrace()); _t3470 = *_hp; free(_hp); }
        (void)_t3470;
        Bool _t3471; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3471 = *_hp; free(_hp); }
        (void)_t3471;
        Bool _t3472 = Bool_not(_t3470);
        (void)_t3472;
        ;
        Bool _t3473 = Bool_not(_t3471);
        (void)_t3473;
        ;
        Bool _wcond3453 = Bool_and(_t3472, _t3473);
        (void)_wcond3453;
        ;
        ;
        if (_wcond3453) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3474; { Bool *_hp = (Bool *)check(p, TokenType_KwNamespace()); _t3474 = *_hp; free(_hp); }
        (void)_t3474;
        if (_t3474) {
            Token *_t3454 = advance(p);
            (void)_t3454;
            expect_token(p, TokenType_Colon());
            Bool _t3455 = 1;
            (void)_t3455;
            in_namespace = _t3455;
            ;
            ;
            continue;
        }
        ;
        if (in_namespace) {
            Expr *stmt = parse_statement(p);
            (void)stmt;
            Bool _t3458; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3458 = *_hp; free(_hp); }
            (void)_t3458;
            if (_t3458) {
                Bool _t3457; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3457 = *_hp; free(_hp); }
                (void)_t3457;
                if (_t3457) {
                    Declaration *dd = ExprData_get_Decl(&stmt->data);
                    (void)dd;
                    Bool _t3456 = 1;
                    (void)_t3456;
                    dd->is_namespace = _t3456;
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
            Bool _t3461 = 0;
            (void)_t3461;
            Bool _t3462 = 0;
            (void)_t3462;
            Bool _t3463 = 0;
            (void)_t3463;
            Bool _t3464 = 0;
            (void)_t3464;
            I32 _t3465 = 0;
            (void)_t3465;
            I32 _t3466 = 0;
            (void)_t3466;
            Declaration *dd = malloc(sizeof(Declaration));
            { Str *_ca = Str_clone(vname); dd->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
            dd->is_mut = _t3461;
            dd->is_namespace = _t3462;
            dd->is_ref = _t3463;
            dd->is_own = _t3464;
            dd->field_offset = _t3465;
            dd->field_size = _t3466;
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
            Bool _t3467; { Bool *_hp = (Bool *)check(p, TokenType_Colon()); _t3467 = *_hp; free(_hp); }
            (void)_t3467;
            if (_t3467) {
                Token *_t3459 = advance(p);
                (void)_t3459;
                Str_delete(&dd->explicit_type, &(Bool){0});
                { Str *_fa = expect_text(p, TokenType_Ident()); dd->explicit_type = *_fa; free(_fa); }
            }
            ;
            ExprData *_t3468 = ExprData_Decl(dd);
            (void)_t3468;
            Declaration_delete(dd, &(Bool){1});
            Expr *variant = Expr_new(_t3468, v_line, v_col, &p->path);
            (void)variant;
            ExprData_delete(_t3468, &(Bool){1});
            ;
            ;
            Expr_add_child(body, variant);
            Bool _t3469; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3469 = *_hp; free(_hp); }
            (void)_t3469;
            if (_t3469) {
                Token *_t3460 = advance(p);
                (void)_t3460;
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
    Token *_t3507 = advance(p);
    (void)_t3507;
    Expr *call = Expr_new(ExprData_FCall(), DEREF(call_line), DEREF(call_col), &p->path);
    (void)call;
    Str *_t3508 = Str_clone(name);
    (void)_t3508;
    ExprData *_t3509 = ExprData_Ident(_t3508);
    (void)_t3509;
    Str_delete(_t3508, &(Bool){1});
    Expr *callee = Expr_new(_t3509, DEREF(call_line), DEREF(call_col), &p->path);
    (void)callee;
    ExprData_delete(_t3509, &(Bool){1});
    Expr_add_child(call, callee);
    while (1) {
        Bool _t3497; { Bool *_hp = (Bool *)check(p, TokenType_RParen()); _t3497 = *_hp; free(_hp); }
        (void)_t3497;
        Bool _t3498; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3498 = *_hp; free(_hp); }
        (void)_t3498;
        Bool _t3499 = Bool_not(_t3497);
        (void)_t3499;
        ;
        Bool _t3500 = Bool_not(_t3498);
        (void)_t3500;
        ;
        Bool _wcond3478 = Bool_and(_t3499, _t3500);
        (void)_wcond3478;
        ;
        ;
        if (_wcond3478) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3501; { Bool *_hp = (Bool *)check(p, TokenType_Ident()); _t3501 = *_hp; free(_hp); }
        (void)_t3501;
        if (_t3501) {
            U32 _t3489 = 1;
            (void)_t3489;
            U32 _t3490 = U32_add(p->pos, _t3489);
            (void)_t3490;
            ;
            Bool _t3491; { Bool *_hp = (Bool *)U32_lt(&(U32){_t3490}, &p->count); _t3491 = *_hp; free(_hp); }
            (void)_t3491;
            ;
            if (_t3491) {
                U32 _t3484 = 1;
                (void)_t3484;
                U32 _t3485 = U32_add(p->pos, _t3484);
                (void)_t3485;
                ;
                I64 _t3486 = U32_to_i64(_t3485);
                (void)_t3486;
                ;
                U64 *_t3487 = malloc(sizeof(U64)); *_t3487 = I64_to_u64(_t3486);
                (void)_t3487;
                ;
                Token *next_tok = Vec_get(&p->tokens, _t3487);
                (void)next_tok;
                Bool _t3488; { Bool *_hp = (Bool *)TokenType_eq(&next_tok->type, TokenType_Eq()); _t3488 = *_hp; free(_hp); }
                (void)_t3488;
                U64_delete(_t3487, &(Bool){1});
                if (_t3488) {
                    U32 na_line; { U32 *_hp = (U32 *)peek_line(p); na_line = *_hp; free(_hp); }
                    (void)na_line;
                    U32 na_col; { U32 *_hp = (U32 *)peek_col(p); na_col = *_hp; free(_hp); }
                    (void)na_col;
                    Str *aname = expect_text(p, TokenType_Ident());
                    (void)aname;
                    Token *_t3480 = advance(p);
                    (void)_t3480;
                    ExprData *_t3481 = ExprData_NamedArg(aname);
                    (void)_t3481;
                    Str_delete(aname, &(Bool){1});
                    Expr *na = Expr_new(_t3481, na_line, na_col, &p->path);
                    (void)na;
                    ExprData_delete(_t3481, &(Bool){1});
                    ;
                    ;
                    Expr *_t3482 = parse_expression(p);
                    (void)_t3482;
                    Expr_add_child(na, _t3482);
                    Expr_add_child(call, na);
                    Bool _t3483; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3483 = *_hp; free(_hp); }
                    (void)_t3483;
                    if (_t3483) {
                        Token *_t3479 = advance(p);
                        (void)_t3479;
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
        Bool _t3502; { Bool *_hp = (Bool *)check(p, TokenType_DotDot()); _t3502 = *_hp; free(_hp); }
        (void)_t3502;
        if (_t3502) {
            Token *_t3492 = advance(p);
            (void)_t3492;
            Bool _t3493 = 1;
            (void)_t3493;
            is_splat = _t3493;
            ;
        }
        ;
        Bool is_own_arg = 0;
        (void)is_own_arg;
        Bool _t3503; { Bool *_hp = (Bool *)check(p, TokenType_KwOwn()); _t3503 = *_hp; free(_hp); }
        (void)_t3503;
        if (_t3503) {
            Token *_t3494 = advance(p);
            (void)_t3494;
            Bool _t3495 = 1;
            (void)_t3495;
            is_own_arg = _t3495;
            ;
        }
        ;
        Expr *arg = parse_expression(p);
        (void)arg;
        Bool _t3504 = Bool_clone(&(Bool){is_own_arg});
        (void)_t3504;
        ;
        arg->is_own_arg = _t3504;
        ;
        Bool _t3505 = Bool_clone(&(Bool){is_splat});
        (void)_t3505;
        ;
        arg->is_splat = _t3505;
        ;
        Expr_add_child(call, arg);
        Bool _t3506; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3506 = *_hp; free(_hp); }
        (void)_t3506;
        if (_t3506) {
            Token *_t3496 = advance(p);
            (void)_t3496;
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
    U32 _t3691 = 0;
    (void)_t3691;
    U32 _t3692 = 0;
    (void)_t3692;
    Expr *e = Expr_new(ExprData_Body(), _t3691, _t3692, &p->path);
    (void)e;
    ;
    ;
    Bool e_set = 0;
    (void)e_set;
    Bool _t3693; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t3693 = *_hp; free(_hp); }
    (void)_t3693;
    if (_t3693) {
        Token *_t3510 = advance(p);
        (void)_t3510;
        Str *_t3511 = Str_clone(&t->text);
        (void)_t3511;
        ExprData *_t3512 = ExprData_LiteralStr(_t3511);
        (void)_t3512;
        Str_delete(_t3511, &(Bool){1});
        e = Expr_new(_t3512, t_line, t_col, &p->path);
        ExprData_delete(_t3512, &(Bool){1});
        Bool _t3513 = 1;
        (void)_t3513;
        e_set = _t3513;
        ;
    }
    ;
    Bool _t3694 = Bool_not(e_set);
    (void)_t3694;
    Bool _t3695; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t3695 = *_hp; free(_hp); }
    (void)_t3695;
    Bool _t3696 = Bool_and(_t3694, _t3695);
    (void)_t3696;
    ;
    ;
    if (_t3696) {
        Token *_t3514 = advance(p);
        (void)_t3514;
        Str *_t3515 = Str_clone(&t->text);
        (void)_t3515;
        ExprData *_t3516 = ExprData_LiteralNum(_t3515);
        (void)_t3516;
        Str_delete(_t3515, &(Bool){1});
        e = Expr_new(_t3516, t_line, t_col, &p->path);
        ExprData_delete(_t3516, &(Bool){1});
        Bool _t3517 = 1;
        (void)_t3517;
        e_set = _t3517;
        ;
    }
    ;
    Bool _t3697 = Bool_not(e_set);
    (void)_t3697;
    Bool _t3698; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Char()); _t3698 = *_hp; free(_hp); }
    (void)_t3698;
    Bool _t3699 = Bool_and(_t3697, _t3698);
    (void)_t3699;
    ;
    ;
    if (_t3699) {
        Token *_t3547 = advance(p);
        (void)_t3547;
        Str *ch = Str_clone(&t->text);
        (void)ch;
        I64 byte_val = 0;
        (void)byte_val;
        U64 _t3548; { U64 *_hp = (U64 *)Str_len(ch); _t3548 = *_hp; free(_hp); }
        (void)_t3548;
        U64 _t3549 = 0;
        (void)_t3549;
        U64 *_t3550 = malloc(sizeof(U64));
        *_t3550 = 0;
        (void)_t3550;
        U8 *_t3551 = Str_get(ch, _t3550);
        (void)_t3551;
        U8 _t3552 = 92;
        (void)_t3552;
        Bool _t3553; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3548}, &(U64){_t3549}); _t3553 = *_hp; free(_hp); }
        (void)_t3553;
        ;
        ;
        Bool _t3554 = U8_eq(DEREF(_t3551), _t3552);
        (void)_t3554;
        U64_delete(_t3550, &(Bool){1});
        ;
        Bool _t3555 = Bool_and(_t3553, _t3554);
        (void)_t3555;
        ;
        ;
        if (_t3555) {
            U64 _t3538; { U64 *_hp = (U64 *)Str_len(ch); _t3538 = *_hp; free(_hp); }
            (void)_t3538;
            U64 _t3539 = 1;
            (void)_t3539;
            Bool _t3540; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3538}, &(U64){_t3539}); _t3540 = *_hp; free(_hp); }
            (void)_t3540;
            ;
            ;
            if (_t3540) {
                U64 *_t3535 = malloc(sizeof(U64));
                *_t3535 = 1;
                (void)_t3535;
                U8 *c2 = Str_get(ch, _t3535);
                (void)c2;
                U8 _t3536 = 110;
                (void)_t3536;
                Bool _t3537 = U8_eq(DEREF(c2), _t3536);
                (void)_t3537;
                ;
                if (_t3537) {
                    I64 _t3518 = 10;
                    (void)_t3518;
                    byte_val = _t3518;
                    ;
                } else {
                    U8 _t3533 = 116;
                    (void)_t3533;
                    Bool _t3534 = U8_eq(DEREF(c2), _t3533);
                    (void)_t3534;
                    ;
                    if (_t3534) {
                        I64 _t3519 = 9;
                        (void)_t3519;
                        byte_val = _t3519;
                        ;
                    } else {
                        U8 _t3531 = 114;
                        (void)_t3531;
                        Bool _t3532 = U8_eq(DEREF(c2), _t3531);
                        (void)_t3532;
                        ;
                        if (_t3532) {
                            I64 _t3520 = 13;
                            (void)_t3520;
                            byte_val = _t3520;
                            ;
                        } else {
                            U8 _t3529 = 92;
                            (void)_t3529;
                            Bool _t3530 = U8_eq(DEREF(c2), _t3529);
                            (void)_t3530;
                            ;
                            if (_t3530) {
                                I64 _t3521 = 92;
                                (void)_t3521;
                                byte_val = _t3521;
                                ;
                            } else {
                                U8 _t3527 = 39;
                                (void)_t3527;
                                Bool _t3528 = U8_eq(DEREF(c2), _t3527);
                                (void)_t3528;
                                ;
                                if (_t3528) {
                                    I64 _t3522 = 39;
                                    (void)_t3522;
                                    byte_val = _t3522;
                                    ;
                                } else {
                                    U8 _t3525 = 48;
                                    (void)_t3525;
                                    Bool _t3526 = U8_eq(DEREF(c2), _t3525);
                                    (void)_t3526;
                                    ;
                                    if (_t3526) {
                                        I64 _t3523 = 0;
                                        (void)_t3523;
                                        byte_val = _t3523;
                                        ;
                                    } else {
                                        I64 _t3524 = U8_to_i64(DEREF(c2));
                                        (void)_t3524;
                                        byte_val = _t3524;
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
                U64_delete(_t3535, &(Bool){1});
                ;
            }
            ;
        } else {
            U64 _t3544; { U64 *_hp = (U64 *)Str_len(ch); _t3544 = *_hp; free(_hp); }
            (void)_t3544;
            U64 _t3545 = 0;
            (void)_t3545;
            Bool _t3546; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3544}, &(U64){_t3545}); _t3546 = *_hp; free(_hp); }
            (void)_t3546;
            ;
            ;
            if (_t3546) {
                U64 *_t3541 = malloc(sizeof(U64));
                *_t3541 = 0;
                (void)_t3541;
                U8 *_t3542 = Str_get(ch, _t3541);
                (void)_t3542;
                I64 _t3543 = U8_to_i64(DEREF(_t3542));
                (void)_t3543;
                U64_delete(_t3541, &(Bool){1});
                byte_val = _t3543;
                ;
            }
            ;
        }
        ;
        Str_delete(ch, &(Bool){1});
        Str *_t3556 = I64_to_str(&(I64){byte_val});
        (void)_t3556;
        ;
        ExprData *_t3557 = ExprData_LiteralNum(_t3556);
        (void)_t3557;
        Str_delete(_t3556, &(Bool){1});
        e = Expr_new(_t3557, t_line, t_col, &p->path);
        ExprData_delete(_t3557, &(Bool){1});
        TilType_delete(&e->til_type, &(Bool){0});
        { TilType *_fa = TilType_clone(TilType_U8()); e->til_type = *_fa; free(_fa); }
        Bool _t3558 = 1;
        (void)_t3558;
        e_set = _t3558;
        ;
    }
    ;
    Bool _t3700; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t3700 = *_hp; free(_hp); }
    (void)_t3700;
    Bool _t3701; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t3701 = *_hp; free(_hp); }
    (void)_t3701;
    Bool _t3702 = Bool_not(e_set);
    (void)_t3702;
    Bool _t3703 = Bool_or(_t3700, _t3701);
    (void)_t3703;
    ;
    ;
    Bool _t3704 = Bool_and(_t3702, _t3703);
    (void)_t3704;
    ;
    ;
    if (_t3704) {
        Token *_t3559 = advance(p);
        (void)_t3559;
        Str *_t3560 = Str_clone(&t->text);
        (void)_t3560;
        ExprData *_t3561 = ExprData_LiteralBool(_t3560);
        (void)_t3561;
        Str_delete(_t3560, &(Bool){1});
        e = Expr_new(_t3561, t_line, t_col, &p->path);
        ExprData_delete(_t3561, &(Bool){1});
        Bool _t3562 = 1;
        (void)_t3562;
        e_set = _t3562;
        ;
    }
    ;
    Bool _t3705 = Bool_not(e_set);
    (void)_t3705;
    Bool _t3706; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t3706 = *_hp; free(_hp); }
    (void)_t3706;
    Bool _t3707 = Bool_and(_t3705, _t3706);
    (void)_t3707;
    ;
    ;
    if (_t3707) {
        Token *_t3598 = advance(p);
        (void)_t3598;
        Str *name = Str_clone(&t->text);
        (void)name;
        Str *_t3599 = Str_lit("__LOC__", 7ULL);
        (void)_t3599;
        Bool _t3600; { Bool *_hp = (Bool *)Str_eq(name, _t3599); _t3600 = *_hp; free(_hp); }
        (void)_t3600;
        Str_delete(_t3599, &(Bool){1});
        if (_t3600) {
            Str *_t3563 = Str_lit("Str", 3ULL);
            (void)_t3563;
            U64 _t3564; { U64 *_hp = (U64 *)Str_size(); _t3564 = *_hp; free(_hp); }
            (void)_t3564;
            U64 _t3565 = 5;
            (void)_t3565;
            Array *_va67 = Array_new(_t3563, &(U64){_t3564}, &(U64){_t3565});
            (void)_va67;
            Str_delete(_t3563, &(Bool){1});
            ;
            ;
            U64 _t3566 = 0;
            (void)_t3566;
            Str *_t3567 = Str_clone(&p->path);
            (void)_t3567;
            Array_set(_va67, &(U64){_t3566}, _t3567);
            ;
            U64 _t3568 = 1;
            (void)_t3568;
            Str *_t3569 = Str_lit(":", 1ULL);
            (void)_t3569;
            Array_set(_va67, &(U64){_t3568}, _t3569);
            ;
            U64 _t3570 = 2;
            (void)_t3570;
            Str *_t3571 = U32_to_str(&(U32){t_line});
            (void)_t3571;
            Array_set(_va67, &(U64){_t3570}, _t3571);
            ;
            U64 _t3572 = 3;
            (void)_t3572;
            Str *_t3573 = Str_lit(":", 1ULL);
            (void)_t3573;
            Array_set(_va67, &(U64){_t3572}, _t3573);
            ;
            U64 _t3574 = 4;
            (void)_t3574;
            Str *_t3575 = U32_to_str(&(U32){t_col});
            (void)_t3575;
            Array_set(_va67, &(U64){_t3574}, _t3575);
            ;
            Str *_t3576 = format(_va67);
            (void)_t3576;
            ExprData *_t3577 = ExprData_LiteralStr(_t3576);
            (void)_t3577;
            Str_delete(_t3576, &(Bool){1});
            e = Expr_new(_t3577, t_line, t_col, &p->path);
            ExprData_delete(_t3577, &(Bool){1});
            Bool _t3578 = 1;
            (void)_t3578;
            e_set = _t3578;
            ;
        } else {
            Str *_t3596 = Str_lit("__FILE__", 8ULL);
            (void)_t3596;
            Bool _t3597; { Bool *_hp = (Bool *)Str_eq(name, _t3596); _t3597 = *_hp; free(_hp); }
            (void)_t3597;
            Str_delete(_t3596, &(Bool){1});
            if (_t3597) {
                Str *_t3579 = Str_clone(&p->path);
                (void)_t3579;
                ExprData *_t3580 = ExprData_LiteralStr(_t3579);
                (void)_t3580;
                Str_delete(_t3579, &(Bool){1});
                e = Expr_new(_t3580, t_line, t_col, &p->path);
                ExprData_delete(_t3580, &(Bool){1});
                Bool _t3581 = 1;
                (void)_t3581;
                e_set = _t3581;
                ;
            } else {
                Str *_t3594 = Str_lit("__LINE__", 8ULL);
                (void)_t3594;
                Bool _t3595; { Bool *_hp = (Bool *)Str_eq(name, _t3594); _t3595 = *_hp; free(_hp); }
                (void)_t3595;
                Str_delete(_t3594, &(Bool){1});
                if (_t3595) {
                    Str *_t3582 = U32_to_str(&(U32){t_line});
                    (void)_t3582;
                    ExprData *_t3583 = ExprData_LiteralNum(_t3582);
                    (void)_t3583;
                    Str_delete(_t3582, &(Bool){1});
                    e = Expr_new(_t3583, t_line, t_col, &p->path);
                    ExprData_delete(_t3583, &(Bool){1});
                    Bool _t3584 = 1;
                    (void)_t3584;
                    e_set = _t3584;
                    ;
                } else {
                    Str *_t3592 = Str_lit("__COL__", 7ULL);
                    (void)_t3592;
                    Bool _t3593; { Bool *_hp = (Bool *)Str_eq(name, _t3592); _t3593 = *_hp; free(_hp); }
                    (void)_t3593;
                    Str_delete(_t3592, &(Bool){1});
                    if (_t3593) {
                        Str *_t3585 = U32_to_str(&(U32){t_col});
                        (void)_t3585;
                        ExprData *_t3586 = ExprData_LiteralNum(_t3585);
                        (void)_t3586;
                        Str_delete(_t3585, &(Bool){1});
                        e = Expr_new(_t3586, t_line, t_col, &p->path);
                        ExprData_delete(_t3586, &(Bool){1});
                        Bool _t3587 = 1;
                        (void)_t3587;
                        e_set = _t3587;
                        ;
                    } else {
                        Bool _t3591; { Bool *_hp = (Bool *)check(p, TokenType_LParen()); _t3591 = *_hp; free(_hp); }
                        (void)_t3591;
                        if (_t3591) {
                            e = parse_call(p, name, &(U32){t_line}, &(U32){t_col});
                            Bool _t3588 = 1;
                            (void)_t3588;
                            e_set = _t3588;
                            ;
                        } else {
                            ExprData *_t3589 = ExprData_Ident(name);
                            (void)_t3589;
                            e = Expr_new(_t3589, t_line, t_col, &p->path);
                            ExprData_delete(_t3589, &(Bool){1});
                            Bool _t3590 = 1;
                            (void)_t3590;
                            e_set = _t3590;
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
    Bool _t3708; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFunc()); _t3708 = *_hp; free(_hp); }
    (void)_t3708;
    Bool _t3709; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwProc()); _t3709 = *_hp; free(_hp); }
    (void)_t3709;
    Bool _t3710 = Bool_or(_t3708, _t3709);
    (void)_t3710;
    ;
    ;
    Bool _t3711; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTest()); _t3711 = *_hp; free(_hp); }
    (void)_t3711;
    Bool _t3712 = Bool_or(_t3710, _t3711);
    (void)_t3712;
    ;
    ;
    Bool _t3713; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMacro()); _t3713 = *_hp; free(_hp); }
    (void)_t3713;
    Bool _t3714 = Bool_or(_t3712, _t3713);
    (void)_t3714;
    ;
    ;
    Bool _t3715; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtFunc()); _t3715 = *_hp; free(_hp); }
    (void)_t3715;
    Bool _t3716 = Bool_or(_t3714, _t3715);
    (void)_t3716;
    ;
    ;
    Bool _t3717; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtProc()); _t3717 = *_hp; free(_hp); }
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
        Expr *_t3601 = parse_func_def(p);
        (void)_t3601;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3601;
    }
    ;
    Bool _t3721; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwStruct()); _t3721 = *_hp; free(_hp); }
    (void)_t3721;
    Bool _t3722; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtStruct()); _t3722 = *_hp; free(_hp); }
    (void)_t3722;
    Bool _t3723 = Bool_not(e_set);
    (void)_t3723;
    Bool _t3724 = Bool_or(_t3721, _t3722);
    (void)_t3724;
    ;
    ;
    Bool _t3725 = Bool_and(_t3723, _t3724);
    (void)_t3725;
    ;
    ;
    if (_t3725) {
        Expr *_t3602 = parse_struct_def(p);
        (void)_t3602;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3602;
    }
    ;
    Bool _t3726 = Bool_not(e_set);
    (void)_t3726;
    Bool _t3727; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwEnum()); _t3727 = *_hp; free(_hp); }
    (void)_t3727;
    Bool _t3728 = Bool_and(_t3726, _t3727);
    (void)_t3728;
    ;
    ;
    if (_t3728) {
        Expr *_t3603 = parse_enum_def(p);
        (void)_t3603;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3603;
    }
    ;
    Bool _t3729 = Bool_not(e_set);
    (void)_t3729;
    Bool _t3730; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t3730 = *_hp; free(_hp); }
    (void)_t3730;
    Bool _t3731 = Bool_and(_t3729, _t3730);
    (void)_t3731;
    ;
    ;
    if (_t3731) {
        Token *_t3627 = advance(p);
        (void)_t3627;
        Expr *first = parse_expression(p);
        (void)first;
        Bool _t3628; { Bool *_hp = (Bool *)check(p, TokenType_Colon()); _t3628 = *_hp; free(_hp); }
        (void)_t3628;
        if (_t3628) {
            e = Expr_new(ExprData_MapLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Token *_t3614 = advance(p);
            (void)_t3614;
            Expr *_t3615 = parse_expression(p);
            (void)_t3615;
            Expr_add_child(e, _t3615);
            Bool _t3616; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3616 = *_hp; free(_hp); }
            (void)_t3616;
            if (_t3616) {
                Token *_t3604 = advance(p);
                (void)_t3604;
            }
            ;
            while (1) {
                Bool _t3607; { Bool *_hp = (Bool *)check(p, TokenType_RBrace()); _t3607 = *_hp; free(_hp); }
                (void)_t3607;
                Bool _t3608; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3608 = *_hp; free(_hp); }
                (void)_t3608;
                Bool _t3609 = Bool_not(_t3607);
                (void)_t3609;
                ;
                Bool _t3610 = Bool_not(_t3608);
                (void)_t3610;
                ;
                Bool _wcond3605 = Bool_and(_t3609, _t3610);
                (void)_wcond3605;
                ;
                ;
                if (_wcond3605) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3611 = parse_expression(p);
                (void)_t3611;
                Expr_add_child(e, _t3611);
                expect_token(p, TokenType_Colon());
                Expr *_t3612 = parse_expression(p);
                (void)_t3612;
                Expr_add_child(e, _t3612);
                Bool _t3613; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3613 = *_hp; free(_hp); }
                (void)_t3613;
                if (_t3613) {
                    Token *_t3606 = advance(p);
                    (void)_t3606;
                }
                ;
            }
        } else {
            e = Expr_new(ExprData_SetLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Bool _t3626; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3626 = *_hp; free(_hp); }
            (void)_t3626;
            if (_t3626) {
                Token *_t3617 = advance(p);
                (void)_t3617;
            }
            ;
            while (1) {
                Bool _t3620; { Bool *_hp = (Bool *)check(p, TokenType_RBrace()); _t3620 = *_hp; free(_hp); }
                (void)_t3620;
                Bool _t3621; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3621 = *_hp; free(_hp); }
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
                Bool _t3625; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3625 = *_hp; free(_hp); }
                (void)_t3625;
                if (_t3625) {
                    Token *_t3619 = advance(p);
                    (void)_t3619;
                }
                ;
            }
        }
        ;
        expect_token(p, TokenType_RBrace());
        Bool _t3629 = 1;
        (void)_t3629;
        e_set = _t3629;
        ;
    }
    ;
    Bool _t3732 = Bool_not(e_set);
    (void)_t3732;
    ;
    if (_t3732) {
        Str *_t3630 = Str_lit("Str", 3ULL);
        (void)_t3630;
        U64 _t3631; { U64 *_hp = (U64 *)Str_size(); _t3631 = *_hp; free(_hp); }
        (void)_t3631;
        U64 _t3632 = 8;
        (void)_t3632;
        Array *_va68 = Array_new(_t3630, &(U64){_t3631}, &(U64){_t3632});
        (void)_va68;
        Str_delete(_t3630, &(Bool){1});
        ;
        ;
        U64 _t3633 = 0;
        (void)_t3633;
        Str *_t3634 = Str_clone(&p->path);
        (void)_t3634;
        Array_set(_va68, &(U64){_t3633}, _t3634);
        ;
        U64 _t3635 = 1;
        (void)_t3635;
        Str *_t3636 = Str_lit(":", 1ULL);
        (void)_t3636;
        Array_set(_va68, &(U64){_t3635}, _t3636);
        ;
        U64 _t3637 = 2;
        (void)_t3637;
        Str *_t3638 = U32_to_str(&(U32){t_line});
        (void)_t3638;
        Array_set(_va68, &(U64){_t3637}, _t3638);
        ;
        U64 _t3639 = 3;
        (void)_t3639;
        Str *_t3640 = Str_lit(":", 1ULL);
        (void)_t3640;
        Array_set(_va68, &(U64){_t3639}, _t3640);
        ;
        U64 _t3641 = 4;
        (void)_t3641;
        Str *_t3642 = U32_to_str(&(U32){t_col});
        (void)_t3642;
        Array_set(_va68, &(U64){_t3641}, _t3642);
        ;
        U64 _t3643 = 5;
        (void)_t3643;
        Str *_t3644 = Str_lit(": unexpected token '", 20ULL);
        (void)_t3644;
        Array_set(_va68, &(U64){_t3643}, _t3644);
        ;
        U64 _t3645 = 6;
        (void)_t3645;
        Str *_t3646 = Str_clone(&t->text);
        (void)_t3646;
        Array_set(_va68, &(U64){_t3645}, _t3646);
        ;
        U64 _t3647 = 7;
        (void)_t3647;
        Str *_t3648 = Str_lit("'", 1ULL);
        (void)_t3648;
        Array_set(_va68, &(U64){_t3647}, _t3648);
        ;
        Str *_t3649 = Str_lit("src/self/parser.til:514:15", 26ULL);
        (void)_t3649;
        panic(_t3649, _va68);
        Str_delete(_t3649, &(Bool){1});
    }
    ;
    ;
    ;
    while (1) {
        Bool _wcond3650; { Bool *_hp = (Bool *)check(p, TokenType_Dot()); _wcond3650 = *_hp; free(_hp); }
        (void)_wcond3650;
        if (_wcond3650) {
        } else {
            ;
            break;
        }
        ;
        Token *_t3681 = advance(p);
        (void)_t3681;
        U32 f_line; { U32 *_hp = (U32 *)peek_line(p); f_line = *_hp; free(_hp); }
        (void)f_line;
        U32 f_col; { U32 *_hp = (U32 *)peek_col(p); f_col = *_hp; free(_hp); }
        (void)f_col;
        Str *fname = expect_text(p, TokenType_Ident());
        (void)fname;
        Bool _t3682; { Bool *_hp = (Bool *)check(p, TokenType_LParen()); _t3682 = *_hp; free(_hp); }
        (void)_t3682;
        if (_t3682) {
            Token *_t3676 = advance(p);
            (void)_t3676;
            ExprData *_t3677 = ExprData_FieldAccess(fname);
            (void)_t3677;
            Expr *callee = Expr_new(_t3677, f_line, f_col, &p->path);
            (void)callee;
            ExprData_delete(_t3677, &(Bool){1});
            Expr *_t3678 = Expr_clone(e);
            (void)_t3678;
            Expr_add_child(callee, _t3678);
            Expr *mcall = Expr_new(ExprData_FCall(), f_line, f_col, &p->path);
            (void)mcall;
            Expr_add_child(mcall, callee);
            while (1) {
                Bool _t3668; { Bool *_hp = (Bool *)check(p, TokenType_RParen()); _t3668 = *_hp; free(_hp); }
                (void)_t3668;
                Bool _t3669; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3669 = *_hp; free(_hp); }
                (void)_t3669;
                Bool _t3670 = Bool_not(_t3668);
                (void)_t3670;
                ;
                Bool _t3671 = Bool_not(_t3669);
                (void)_t3671;
                ;
                Bool _wcond3651 = Bool_and(_t3670, _t3671);
                (void)_wcond3651;
                ;
                ;
                if (_wcond3651) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3672; { Bool *_hp = (Bool *)check(p, TokenType_Ident()); _t3672 = *_hp; free(_hp); }
                (void)_t3672;
                if (_t3672) {
                    U32 _t3662 = 1;
                    (void)_t3662;
                    U32 _t3663 = U32_add(p->pos, _t3662);
                    (void)_t3663;
                    ;
                    Bool _t3664; { Bool *_hp = (Bool *)U32_lt(&(U32){_t3663}, &p->count); _t3664 = *_hp; free(_hp); }
                    (void)_t3664;
                    ;
                    if (_t3664) {
                        U32 _t3657 = 1;
                        (void)_t3657;
                        U32 _t3658 = U32_add(p->pos, _t3657);
                        (void)_t3658;
                        ;
                        I64 _t3659 = U32_to_i64(_t3658);
                        (void)_t3659;
                        ;
                        U64 *_t3660 = malloc(sizeof(U64)); *_t3660 = I64_to_u64(_t3659);
                        (void)_t3660;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3660);
                        (void)nt;
                        Bool _t3661; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3661 = *_hp; free(_hp); }
                        (void)_t3661;
                        U64_delete(_t3660, &(Bool){1});
                        if (_t3661) {
                            U32 na_line; { U32 *_hp = (U32 *)peek_line(p); na_line = *_hp; free(_hp); }
                            (void)na_line;
                            U32 na_col; { U32 *_hp = (U32 *)peek_col(p); na_col = *_hp; free(_hp); }
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3653 = advance(p);
                            (void)_t3653;
                            ExprData *_t3654 = ExprData_NamedArg(aname);
                            (void)_t3654;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3654, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3654, &(Bool){1});
                            ;
                            ;
                            Expr *_t3655 = parse_expression(p);
                            (void)_t3655;
                            Expr_add_child(na, _t3655);
                            Expr_add_child(mcall, na);
                            Bool _t3656; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3656 = *_hp; free(_hp); }
                            (void)_t3656;
                            if (_t3656) {
                                Token *_t3652 = advance(p);
                                (void)_t3652;
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
                Bool _t3673; { Bool *_hp = (Bool *)check(p, TokenType_KwOwn()); _t3673 = *_hp; free(_hp); }
                (void)_t3673;
                if (_t3673) {
                    Token *_t3665 = advance(p);
                    (void)_t3665;
                    Bool _t3666 = 1;
                    (void)_t3666;
                    is_own_arg = _t3666;
                    ;
                }
                ;
                Expr *marg = parse_expression(p);
                (void)marg;
                Bool _t3674 = Bool_clone(&(Bool){is_own_arg});
                (void)_t3674;
                ;
                marg->is_own_arg = _t3674;
                ;
                Expr_add_child(mcall, marg);
                Bool _t3675; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3675 = *_hp; free(_hp); }
                (void)_t3675;
                if (_t3675) {
                    Token *_t3667 = advance(p);
                    (void)_t3667;
                }
                ;
            }
            expect_token(p, TokenType_RParen());
            e = Expr_clone(mcall);
            Expr_delete(mcall, &(Bool){1});
        } else {
            ExprData *_t3679 = ExprData_FieldAccess(fname);
            (void)_t3679;
            Expr *access = Expr_new(_t3679, f_line, f_col, &p->path);
            (void)access;
            ExprData_delete(_t3679, &(Bool){1});
            Expr *_t3680 = Expr_clone(e);
            (void)_t3680;
            Expr_add_child(access, _t3680);
            e = Expr_clone(access);
            Expr_delete(access, &(Bool){1});
        }
        ;
        ;
        ;
        Str_delete(fname, &(Bool){1});
    }
    Bool _t3733; { Bool *_hp = (Bool *)check(p, TokenType_DotDot()); _t3733 = *_hp; free(_hp); }
    (void)_t3733;
    if (_t3733) {
        U32 dt_line; { U32 *_hp = (U32 *)peek_line(p); dt_line = *_hp; free(_hp); }
        (void)dt_line;
        U32 dt_col; { U32 *_hp = (U32 *)peek_col(p); dt_col = *_hp; free(_hp); }
        (void)dt_col;
        Token *_t3683 = advance(p);
        (void)_t3683;
        Expr *rhs = parse_expression(p);
        (void)rhs;
        Str *_t3684 = Str_lit("Range", 5ULL);
        (void)_t3684;
        Str *_t3685 = Str_clone(_t3684);
        (void)_t3685;
        Str_delete(_t3684, &(Bool){1});
        ExprData *_t3686 = ExprData_Ident(_t3685);
        (void)_t3686;
        Str_delete(_t3685, &(Bool){1});
        Expr *range_ident = Expr_new(_t3686, dt_line, dt_col, &p->path);
        (void)range_ident;
        ExprData_delete(_t3686, &(Bool){1});
        Str *_t3687 = Str_lit("new", 3ULL);
        (void)_t3687;
        Str *_t3688 = Str_clone(_t3687);
        (void)_t3688;
        Str_delete(_t3687, &(Bool){1});
        ExprData *_t3689 = ExprData_FieldAccess(_t3688);
        (void)_t3689;
        Str_delete(_t3688, &(Bool){1});
        Expr *new_access = Expr_new(_t3689, dt_line, dt_col, &p->path);
        (void)new_access;
        ExprData_delete(_t3689, &(Bool){1});
        Expr_add_child(new_access, range_ident);
        Expr *rcall = Expr_new(ExprData_FCall(), dt_line, dt_col, &p->path);
        (void)rcall;
        ;
        ;
        Expr_add_child(rcall, new_access);
        Expr *_t3690 = Expr_clone(e);
        (void)_t3690;
        Expr_add_child(rcall, _t3690);
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
    Bool _t3922; { Bool *_hp = (Bool *)check(p, TokenType_ColonEq()); _t3922 = *_hp; free(_hp); }
    (void)_t3922;
    if (_t3922) {
        Token *_t3734 = advance(p);
        (void)_t3734;
        Bool _t3735 = Bool_clone(is_mut);
        (void)_t3735;
        Bool _t3736 = 0;
        (void)_t3736;
        Bool _t3737 = 0;
        (void)_t3737;
        Bool _t3738 = Bool_clone(is_own);
        (void)_t3738;
        I32 _t3739 = 0;
        (void)_t3739;
        I32 _t3740 = 0;
        (void)_t3740;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3735;
        dd->is_namespace = _t3736;
        dd->is_ref = _t3737;
        dd->is_own = _t3738;
        dd->field_offset = _t3739;
        dd->field_size = _t3740;
        dd->field_struct_def = NULL;
        dd->fn_sig = NULL;
        (void)dd;
        ;
        ;
        ;
        ;
        ;
        ;
        ExprData *_t3741 = ExprData_Decl(dd);
        (void)_t3741;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3741, t_line, t_col, &p->path);
        (void)decl;
        ExprData_delete(_t3741, &(Bool){1});
        Expr *_t3742 = parse_expression(p);
        (void)_t3742;
        Expr_add_child(decl, _t3742);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return decl;
    }
    ;
    Bool _t3923; { Bool *_hp = (Bool *)check(p, TokenType_Colon()); _t3923 = *_hp; free(_hp); }
    (void)_t3923;
    if (_t3923) {
        Token *_t3858 = advance(p);
        (void)_t3858;
        Bool _t3859; { Bool *_hp = (Bool *)check(p, TokenType_KwFunc()); _t3859 = *_hp; free(_hp); }
        (void)_t3859;
        Bool _t3860; { Bool *_hp = (Bool *)check(p, TokenType_KwProc()); _t3860 = *_hp; free(_hp); }
        (void)_t3860;
        Bool _t3861 = Bool_or(_t3859, _t3860);
        (void)_t3861;
        ;
        ;
        if (_t3861) {
            Expr *sig = parse_func_def(p);
            (void)sig;
            expect_token(p, TokenType_Eq());
            expect_token(p, TokenType_LParen());
            Bool _t3759; { Bool *_hp = (Bool *)ExprData_is_FuncDef(&sig->data); _t3759 = *_hp; free(_hp); }
            (void)_t3759;
            if (_t3759) {
                FunctionDef *sfd = ExprData_get_FuncDef(&sig->data);
                (void)sfd;
                Str *_t3756 = Str_lit("Str", 3ULL);
                (void)_t3756;
                U64 _t3757; { U64 *_hp = (U64 *)Str_size(); _t3757 = *_hp; free(_hp); }
                (void)_t3757;
                Vec *new_names = Vec_new(_t3756, &(U64){_t3757});
                (void)new_names;
                Str_delete(_t3756, &(Bool){1});
                ;
                {
                    U64 _fi3743 = 0;
                    (void)_fi3743;
                    while (1) {
                        U64 _t3745 = 0;
                        (void)_t3745;
                        U64 _t3746; { U64 *_hp = (U64 *)Vec_len(&sfd->param_names); _t3746 = *_hp; free(_hp); }
                        (void)_t3746;
                        Range *_t3747 = Range_new(_t3745, _t3746);
                        (void)_t3747;
                        ;
                        ;
                        U64 _t3748; { U64 *_hp = (U64 *)Range_len(_t3747); _t3748 = *_hp; free(_hp); }
                        (void)_t3748;
                        Range_delete(_t3747, &(Bool){1});
                        Bool _wcond3744; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3743}, &(U64){_t3748}); _wcond3744 = *_hp; free(_hp); }
                        (void)_wcond3744;
                        ;
                        if (_wcond3744) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 _t3749 = 0;
                        (void)_t3749;
                        U64 _t3750; { U64 *_hp = (U64 *)Vec_len(&sfd->param_names); _t3750 = *_hp; free(_hp); }
                        (void)_t3750;
                        Range *_t3751 = Range_new(_t3749, _t3750);
                        (void)_t3751;
                        ;
                        ;
                        U64 pi; { U64 *_hp = (U64 *)Range_get(_t3751, _fi3743); pi = *_hp; free(_hp); }
                        (void)pi;
                        Range_delete(_t3751, &(Bool){1});
                        U64 _t3752 = 1;
                        (void)_t3752;
                        U64 _t3753 = U64_add(_fi3743, _t3752);
                        (void)_t3753;
                        ;
                        _fi3743 = _t3753;
                        ;
                        U64 _t3754 = 0;
                        (void)_t3754;
                        Bool _t3755; { Bool *_hp = (Bool *)U64_gt(&(U64){pi}, &(U64){_t3754}); _t3755 = *_hp; free(_hp); }
                        (void)_t3755;
                        ;
                        ;
                        if (_t3755) {
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
            Bool _t3760; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3760 = *_hp; free(_hp); }
            (void)_t3760;
            if (_t3760) {
                Token *_t3758 = advance(p);
                (void)_t3758;
            }
            ;
            expect_token(p, TokenType_RParen());
            expect_token(p, TokenType_LBrace());
            Expr *_t3761 = parse_block(p);
            (void)_t3761;
            Expr_add_child(sig, _t3761);
            Bool _t3762 = Bool_clone(is_mut);
            (void)_t3762;
            Bool _t3763 = 0;
            (void)_t3763;
            Bool _t3764 = 0;
            (void)_t3764;
            Bool _t3765 = Bool_clone(is_own);
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
        I64 _t3862 = 0;
        (void)_t3862;
        I64 _t3863 = 1;
        (void)_t3863;
        I64 fn_sig_idx = I64_sub(_t3862, _t3863);
        (void)fn_sig_idx;
        ;
        ;
        Str *_t3864 = Str_lit("Fn", 2ULL);
        (void)_t3864;
        Bool _t3865; { Bool *_hp = (Bool *)Str_eq(type_name, _t3864); _t3865 = *_hp; free(_hp); }
        (void)_t3865;
        Str_delete(_t3864, &(Bool){1});
        if (_t3865) {
            Expr *sig = parse_fn_signature(p, &(U32){t_line}, &(U32){t_col});
            (void)sig;
            U32 _t3770 = 0;
            (void)_t3770;
            Bool _t3771; { Bool *_hp = (Bool *)U32_neq(&sig->line, &(U32){_t3770}); _t3771 = *_hp; free(_hp); }
            (void)_t3771;
            ;
            Expr_delete(sig, &(Bool){1});
            if (_t3771) {
                I64 _t3769 = 0;
                (void)_t3769;
                fn_sig_idx = _t3769;
                ;
            }
            ;
        }
        ;
        ;
        expect_token(p, TokenType_Eq());
        Bool _t3866; { Bool *_hp = (Bool *)check(p, TokenType_LParen()); _t3866 = *_hp; free(_hp); }
        (void)_t3866;
        if (_t3866) {
            U32 saved = p->pos;
            (void)saved;
            Token *_t3854 = advance(p);
            (void)_t3854;
            Bool is_fsf = 1;
            (void)is_fsf;
            while (1) {
                Bool _t3775; { Bool *_hp = (Bool *)check(p, TokenType_RParen()); _t3775 = *_hp; free(_hp); }
                (void)_t3775;
                Bool _t3776; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3776 = *_hp; free(_hp); }
                (void)_t3776;
                Bool _t3777 = Bool_not(_t3775);
                (void)_t3777;
                ;
                Bool _t3778 = Bool_not(_t3776);
                (void)_t3778;
                ;
                Bool _wcond3772 = Bool_and(_t3777, _t3778);
                (void)_wcond3772;
                ;
                ;
                if (_wcond3772) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3779; { Bool *_hp = (Bool *)check(p, TokenType_Ident()); _t3779 = *_hp; free(_hp); }
                (void)_t3779;
                Bool _t3780 = Bool_not(_t3779);
                (void)_t3780;
                ;
                if (_t3780) {
                    Bool _t3773 = 0;
                    (void)_t3773;
                    is_fsf = _t3773;
                    ;
                    ;
                    break;
                }
                ;
                Token *_t3781 = advance(p);
                (void)_t3781;
                Bool _t3782; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3782 = *_hp; free(_hp); }
                (void)_t3782;
                if (_t3782) {
                    Token *_t3774 = advance(p);
                    (void)_t3774;
                }
                ;
            }
            Bool _t3855; { Bool *_hp = (Bool *)check(p, TokenType_RParen()); _t3855 = *_hp; free(_hp); }
            (void)_t3855;
            Bool _t3856 = Bool_and(is_fsf, _t3855);
            (void)_t3856;
            ;
            if (_t3856) {
                Token *_t3784 = advance(p);
                (void)_t3784;
                Bool _t3785; { Bool *_hp = (Bool *)check(p, TokenType_LBrace()); _t3785 = *_hp; free(_hp); }
                (void)_t3785;
                Bool _t3786 = Bool_not(_t3785);
                (void)_t3786;
                ;
                if (_t3786) {
                    Bool _t3783 = 0;
                    (void)_t3783;
                    is_fsf = _t3783;
                    ;
                }
                ;
            } else {
                Bool _t3787 = 0;
                (void)_t3787;
                is_fsf = _t3787;
                ;
            }
            ;
            U32 _t3857 = U32_clone(&(U32){saved});
            (void)_t3857;
            ;
            p->pos = _t3857;
            ;
            if (is_fsf) {
                expect_token(p, TokenType_LParen());
                Str *_t3811 = Str_lit("Str", 3ULL);
                (void)_t3811;
                U64 _t3812; { U64 *_hp = (U64 *)Str_size(); _t3812 = *_hp; free(_hp); }
                (void)_t3812;
                Vec *pnames = Vec_new(_t3811, &(U64){_t3812});
                (void)pnames;
                Str_delete(_t3811, &(Bool){1});
                ;
                while (1) {
                    Bool _t3790; { Bool *_hp = (Bool *)check(p, TokenType_RParen()); _t3790 = *_hp; free(_hp); }
                    (void)_t3790;
                    Bool _wcond3788 = Bool_not(_t3790);
                    (void)_wcond3788;
                    ;
                    if (_wcond3788) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *pn = expect_text(p, TokenType_Ident());
                    (void)pn;
                    Vec_push(pnames, pn);
                    Bool _t3791; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3791 = *_hp; free(_hp); }
                    (void)_t3791;
                    if (_t3791) {
                        Token *_t3789 = advance(p);
                        (void)_t3789;
                    }
                    ;
                }
                expect_token(p, TokenType_RParen());
                expect_token(p, TokenType_LBrace());
                Expr *body = parse_block(p);
                (void)body;
                Str *_t3813 = Str_lit("Str", 3ULL);
                (void)_t3813;
                U64 _t3814; { U64 *_hp = (U64 *)Str_size(); _t3814 = *_hp; free(_hp); }
                (void)_t3814;
                Str *_t3815 = Str_lit("Str", 3ULL);
                (void)_t3815;
                U64 _t3816; { U64 *_hp = (U64 *)Str_size(); _t3816 = *_hp; free(_hp); }
                (void)_t3816;
                Str *_t3817 = Str_lit("Bool", 4ULL);
                (void)_t3817;
                U64 _t3818; { U64 *_hp = (U64 *)Bool_size(); _t3818 = *_hp; free(_hp); }
                (void)_t3818;
                Str *_t3819 = Str_lit("Bool", 4ULL);
                (void)_t3819;
                U64 _t3820; { U64 *_hp = (U64 *)Bool_size(); _t3820 = *_hp; free(_hp); }
                (void)_t3820;
                Str *_t3821 = Str_lit("Bool", 4ULL);
                (void)_t3821;
                U64 _t3822; { U64 *_hp = (U64 *)Bool_size(); _t3822 = *_hp; free(_hp); }
                (void)_t3822;
                Str *_t3823 = Str_lit("I64", 3ULL);
                (void)_t3823;
                U64 _t3824; { U64 *_hp = (U64 *)I64_size(); _t3824 = *_hp; free(_hp); }
                (void)_t3824;
                Str *_t3825 = Str_lit("I64", 3ULL);
                (void)_t3825;
                U64 _t3826; { U64 *_hp = (U64 *)I64_size(); _t3826 = *_hp; free(_hp); }
                (void)_t3826;
                I64 _t3827 = 0;
                (void)_t3827;
                I64 _t3828 = 1;
                (void)_t3828;
                I64 _t3829 = I64_sub(_t3827, _t3828);
                (void)_t3829;
                ;
                ;
                I64 _t3830 = 0;
                (void)_t3830;
                I64 _t3831 = 1;
                (void)_t3831;
                I64 _t3832 = I64_sub(_t3830, _t3831);
                (void)_t3832;
                ;
                ;
                U32 _t3833 = 0;
                (void)_t3833;
                I32 _t3834 = I64_to_i32(_t3829);
                (void)_t3834;
                ;
                I32 _t3835 = I64_to_i32(_t3832);
                (void)_t3835;
                ;
                Bool _t3836 = 0;
                (void)_t3836;
                Bool _t3837 = 0;
                (void)_t3837;
                FunctionDef *ffd = malloc(sizeof(FunctionDef));
                { FuncType *_ca = FuncType_clone(FuncType_Func()); ffd->func_type = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3813, &(U64){_t3814}); ffd->param_names = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3815, &(U64){_t3816}); ffd->param_types = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3817, &(U64){_t3818}); ffd->param_muts = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3819, &(U64){_t3820}); ffd->param_owns = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3821, &(U64){_t3822}); ffd->param_shallows = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3823, &(U64){_t3824}); ffd->param_fn_sigs = *_ca; free(_ca); }
                ffd->nparam = _t3833;
                { Vec *_ca = Vec_new(_t3825, &(U64){_t3826}); ffd->param_defaults = *_ca; free(_ca); }
                { Str *_ca = Str_clone(Str_lit("", 0ULL)); ffd->return_type = *_ca; free(_ca); }
                ffd->variadic_index = _t3834;
                ffd->kwargs_index = _t3835;
                ffd->return_is_ref = _t3836;
                ffd->return_is_shallow = _t3837;
                (void)ffd;
                Str_delete(_t3813, &(Bool){1});
                ;
                Str_delete(_t3815, &(Bool){1});
                ;
                Str_delete(_t3817, &(Bool){1});
                ;
                Str_delete(_t3819, &(Bool){1});
                ;
                Str_delete(_t3821, &(Bool){1});
                ;
                Str_delete(_t3823, &(Bool){1});
                ;
                Str_delete(_t3825, &(Bool){1});
                ;
                ;
                ;
                ;
                ;
                ;
                FuncType_delete(&ffd->func_type, &(Bool){0});
                { FuncType *_fa = FuncType_clone(FuncType_Func()); ffd->func_type = *_fa; free(_fa); }
                I64 _t3838 = 0;
                (void)_t3838;
                I64 _t3839 = 1;
                (void)_t3839;
                I64 _t3840 = I64_sub(_t3838, _t3839);
                (void)_t3840;
                ;
                ;
                I32 _t3841 = I64_to_i32(_t3840);
                (void)_t3841;
                ;
                ffd->variadic_index = _t3841;
                ;
                I64 _t3842 = 0;
                (void)_t3842;
                I64 _t3843 = 1;
                (void)_t3843;
                I64 _t3844 = I64_sub(_t3842, _t3843);
                (void)_t3844;
                ;
                ;
                I32 _t3845 = I64_to_i32(_t3844);
                (void)_t3845;
                ;
                ffd->kwargs_index = _t3845;
                ;
                U64 np; { U64 *_hp = (U64 *)Vec_len(pnames); np = *_hp; free(_hp); }
                (void)np;
                {
                    U64 _fi3792 = 0;
                    (void)_fi3792;
                    while (1) {
                        U64 _t3794 = 0;
                        (void)_t3794;
                        Range *_t3795 = Range_new(_t3794, np);
                        (void)_t3795;
                        ;
                        U64 _t3796; { U64 *_hp = (U64 *)Range_len(_t3795); _t3796 = *_hp; free(_hp); }
                        (void)_t3796;
                        Range_delete(_t3795, &(Bool){1});
                        Bool _wcond3793; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3792}, &(U64){_t3796}); _wcond3793 = *_hp; free(_hp); }
                        (void)_wcond3793;
                        ;
                        if (_wcond3793) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 _t3797 = 0;
                        (void)_t3797;
                        Range *_t3798 = Range_new(_t3797, np);
                        (void)_t3798;
                        ;
                        U64 _; { U64 *_hp = (U64 *)Range_get(_t3798, _fi3792); _ = *_hp; free(_hp); }
                        (void)_;
                        ;
                        Range_delete(_t3798, &(Bool){1});
                        U64 _t3799 = 1;
                        (void)_t3799;
                        U64 _t3800 = U64_add(_fi3792, _t3799);
                        (void)_t3800;
                        ;
                        _fi3792 = _t3800;
                        ;
                        Str *_t3801 = Str_lit("", 0ULL);
                        (void)_t3801;
                        Vec_push(&ffd->param_types, _t3801);
                        Bool _t3802 = 0;
                        (void)_t3802;
                        Vec_push(&ffd->param_muts, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3802; _oa; }));
                        Bool _t3803 = 0;
                        (void)_t3803;
                        Vec_push(&ffd->param_owns, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3803; _oa; }));
                        Bool _t3804 = 0;
                        (void)_t3804;
                        Vec_push(&ffd->param_shallows, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3804; _oa; }));
                        I64 _t3805 = 0;
                        (void)_t3805;
                        I64 _t3806 = 1;
                        (void)_t3806;
                        I64 _t3807 = I64_sub(_t3805, _t3806);
                        (void)_t3807;
                        ;
                        ;
                        Vec_push(&ffd->param_defaults, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = _t3807; _oa; }));
                        I64 _t3808 = 0;
                        (void)_t3808;
                        I64 _t3809 = 1;
                        (void)_t3809;
                        I64 _t3810 = I64_sub(_t3808, _t3809);
                        (void)_t3810;
                        ;
                        ;
                        Vec_push(&ffd->param_fn_sigs, ({ I64 *_oa = malloc(sizeof(I64)); *_oa = _t3810; _oa; }));
                    }
                    ;
                }
                ;
                Vec_delete(&ffd->param_names, &(Bool){0});
                { Vec *_fa = Vec_clone(pnames); ffd->param_names = *_fa; free(_fa); }
                Vec_delete(pnames, &(Bool){1});
                ExprData *_t3846 = ExprData_FuncDef(ffd);
                (void)_t3846;
                FunctionDef_delete(ffd, &(Bool){1});
                Expr *fdef = Expr_new(_t3846, t_line, t_col, &p->path);
                (void)fdef;
                ExprData_delete(_t3846, &(Bool){1});
                Expr_add_child(fdef, body);
                Bool _t3847 = Bool_clone(is_mut);
                (void)_t3847;
                Bool _t3848 = 0;
                (void)_t3848;
                Bool _t3849 = 0;
                (void)_t3849;
                Bool _t3850 = Bool_clone(is_own);
                (void)_t3850;
                I32 _t3851 = 0;
                (void)_t3851;
                I32 _t3852 = 0;
                (void)_t3852;
                Declaration *dd = malloc(sizeof(Declaration));
                { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
                { Str *_ca = Str_clone(type_name); dd->explicit_type = *_ca; free(_ca); }
                dd->is_mut = _t3847;
                dd->is_namespace = _t3848;
                dd->is_ref = _t3849;
                dd->is_own = _t3850;
                dd->field_offset = _t3851;
                dd->field_size = _t3852;
                dd->field_struct_def = NULL;
                dd->fn_sig = NULL;
                (void)dd;
                ;
                ;
                ;
                ;
                ;
                ;
                ExprData *_t3853 = ExprData_Decl(dd);
                (void)_t3853;
                Declaration_delete(dd, &(Bool){1});
                Expr *decl = Expr_new(_t3853, t_line, t_col, &p->path);
                (void)decl;
                ExprData_delete(_t3853, &(Bool){1});
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
        Bool _t3867 = Bool_clone(is_mut);
        (void)_t3867;
        Bool _t3868 = 0;
        (void)_t3868;
        Bool _t3869 = 0;
        (void)_t3869;
        Bool _t3870 = Bool_clone(is_own);
        (void)_t3870;
        I32 _t3871 = 0;
        (void)_t3871;
        I32 _t3872 = 0;
        (void)_t3872;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(type_name); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3867;
        dd->is_namespace = _t3868;
        dd->is_ref = _t3869;
        dd->is_own = _t3870;
        dd->field_offset = _t3871;
        dd->field_size = _t3872;
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
        ExprData *_t3873 = ExprData_Decl(dd);
        (void)_t3873;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3873, t_line, t_col, &p->path);
        (void)decl;
        ExprData_delete(_t3873, &(Bool){1});
        Expr *_t3874 = parse_expression(p);
        (void)_t3874;
        Expr_add_child(decl, _t3874);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return decl;
    }
    ;
    Bool _t3924; { Bool *_hp = (Bool *)check(p, TokenType_Dot()); _t3924 = *_hp; free(_hp); }
    (void)_t3924;
    if (_t3924) {
        Str *_t3911 = Str_clone(name);
        (void)_t3911;
        ExprData *_t3912 = ExprData_Ident(_t3911);
        (void)_t3912;
        Str_delete(_t3911, &(Bool){1});
        Expr *obj = Expr_new(_t3912, t_line, t_col, &p->path);
        (void)obj;
        ExprData_delete(_t3912, &(Bool){1});
        Str *last_field = Str_lit("", 0ULL);
        (void)last_field;
        U32 last_line = 0;
        (void)last_line;
        U32 last_col = 0;
        (void)last_col;
        while (1) {
            Bool _wcond3875; { Bool *_hp = (Bool *)check(p, TokenType_Dot()); _wcond3875 = *_hp; free(_hp); }
            (void)_wcond3875;
            if (_wcond3875) {
            } else {
                ;
                break;
            }
            ;
            Token *_t3879 = advance(p);
            (void)_t3879;
            U32 _t3880; { U32 *_hp = (U32 *)peek_line(p); _t3880 = *_hp; free(_hp); }
            (void)_t3880;
            last_line = _t3880;
            ;
            U32 _t3881; { U32 *_hp = (U32 *)peek_col(p); _t3881 = *_hp; free(_hp); }
            (void)_t3881;
            last_col = _t3881;
            ;
            last_field = expect_text(p, TokenType_Ident());
            Bool _t3882; { Bool *_hp = (Bool *)check(p, TokenType_Dot()); _t3882 = *_hp; free(_hp); }
            (void)_t3882;
            if (_t3882) {
                Str *_t3876 = Str_clone(last_field);
                (void)_t3876;
                ExprData *_t3877 = ExprData_FieldAccess(_t3876);
                (void)_t3877;
                Str_delete(_t3876, &(Bool){1});
                Expr *access = Expr_new(_t3877, last_line, last_col, &p->path);
                (void)access;
                ExprData_delete(_t3877, &(Bool){1});
                Expr *_t3878 = Expr_clone(obj);
                (void)_t3878;
                Expr_add_child(access, _t3878);
                obj = Expr_clone(access);
                Expr_delete(access, &(Bool){1});
            }
            ;
        }
        Bool _t3913; { Bool *_hp = (Bool *)check(p, TokenType_LParen()); _t3913 = *_hp; free(_hp); }
        (void)_t3913;
        if (_t3913) {
            Token *_t3908 = advance(p);
            (void)_t3908;
            ExprData *_t3909 = ExprData_FieldAccess(last_field);
            (void)_t3909;
            Expr *callee = Expr_new(_t3909, last_line, last_col, &p->path);
            (void)callee;
            ExprData_delete(_t3909, &(Bool){1});
            Expr *_t3910 = Expr_clone(obj);
            (void)_t3910;
            Expr_add_child(callee, _t3910);
            Expr *mcall = Expr_new(ExprData_FCall(), last_line, last_col, &p->path);
            (void)mcall;
            Expr_add_child(mcall, callee);
            while (1) {
                Bool _t3900; { Bool *_hp = (Bool *)check(p, TokenType_RParen()); _t3900 = *_hp; free(_hp); }
                (void)_t3900;
                Bool _t3901; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3901 = *_hp; free(_hp); }
                (void)_t3901;
                Bool _t3902 = Bool_not(_t3900);
                (void)_t3902;
                ;
                Bool _t3903 = Bool_not(_t3901);
                (void)_t3903;
                ;
                Bool _wcond3883 = Bool_and(_t3902, _t3903);
                (void)_wcond3883;
                ;
                ;
                if (_wcond3883) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3904; { Bool *_hp = (Bool *)check(p, TokenType_Ident()); _t3904 = *_hp; free(_hp); }
                (void)_t3904;
                if (_t3904) {
                    U32 _t3894 = 1;
                    (void)_t3894;
                    U32 _t3895 = U32_add(p->pos, _t3894);
                    (void)_t3895;
                    ;
                    Bool _t3896; { Bool *_hp = (Bool *)U32_lt(&(U32){_t3895}, &p->count); _t3896 = *_hp; free(_hp); }
                    (void)_t3896;
                    ;
                    if (_t3896) {
                        U32 _t3889 = 1;
                        (void)_t3889;
                        U32 _t3890 = U32_add(p->pos, _t3889);
                        (void)_t3890;
                        ;
                        I64 _t3891 = U32_to_i64(_t3890);
                        (void)_t3891;
                        ;
                        U64 *_t3892 = malloc(sizeof(U64)); *_t3892 = I64_to_u64(_t3891);
                        (void)_t3892;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3892);
                        (void)nt;
                        Bool _t3893; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3893 = *_hp; free(_hp); }
                        (void)_t3893;
                        U64_delete(_t3892, &(Bool){1});
                        if (_t3893) {
                            U32 na_line; { U32 *_hp = (U32 *)peek_line(p); na_line = *_hp; free(_hp); }
                            (void)na_line;
                            U32 na_col; { U32 *_hp = (U32 *)peek_col(p); na_col = *_hp; free(_hp); }
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3885 = advance(p);
                            (void)_t3885;
                            ExprData *_t3886 = ExprData_NamedArg(aname);
                            (void)_t3886;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3886, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3886, &(Bool){1});
                            ;
                            ;
                            Expr *_t3887 = parse_expression(p);
                            (void)_t3887;
                            Expr_add_child(na, _t3887);
                            Expr_add_child(mcall, na);
                            Bool _t3888; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3888 = *_hp; free(_hp); }
                            (void)_t3888;
                            if (_t3888) {
                                Token *_t3884 = advance(p);
                                (void)_t3884;
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
                Bool _t3905; { Bool *_hp = (Bool *)check(p, TokenType_KwOwn()); _t3905 = *_hp; free(_hp); }
                (void)_t3905;
                if (_t3905) {
                    Token *_t3897 = advance(p);
                    (void)_t3897;
                    Bool _t3898 = 1;
                    (void)_t3898;
                    is_own_arg = _t3898;
                    ;
                }
                ;
                Expr *marg = parse_expression(p);
                (void)marg;
                Bool _t3906 = Bool_clone(&(Bool){is_own_arg});
                (void)_t3906;
                ;
                marg->is_own_arg = _t3906;
                ;
                Expr_add_child(mcall, marg);
                Bool _t3907; { Bool *_hp = (Bool *)check(p, TokenType_Comma()); _t3907 = *_hp; free(_hp); }
                (void)_t3907;
                if (_t3907) {
                    Token *_t3899 = advance(p);
                    (void)_t3899;
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
        ExprData *_t3914 = ExprData_FieldAssign(last_field);
        (void)_t3914;
        Str_delete(last_field, &(Bool){1});
        Expr *fa = Expr_new(_t3914, t_line, t_col, &p->path);
        (void)fa;
        ExprData_delete(_t3914, &(Bool){1});
        Expr *_t3915 = Expr_clone(obj);
        (void)_t3915;
        Expr_delete(obj, &(Bool){1});
        Expr_add_child(fa, _t3915);
        Expr *_t3916 = parse_expression(p);
        (void)_t3916;
        Expr_add_child(fa, _t3916);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return fa;
    }
    ;
    Bool _t3925; { Bool *_hp = (Bool *)check(p, TokenType_Eq()); _t3925 = *_hp; free(_hp); }
    (void)_t3925;
    if (_t3925) {
        Token *_t3917 = advance(p);
        (void)_t3917;
        Str *_t3918 = Str_clone(name);
        (void)_t3918;
        ExprData *_t3919 = ExprData_Assign(_t3918);
        (void)_t3919;
        Str_delete(_t3918, &(Bool){1});
        Expr *assign = Expr_new(_t3919, t_line, t_col, &p->path);
        (void)assign;
        ExprData_delete(_t3919, &(Bool){1});
        Expr *_t3920 = parse_expression(p);
        (void)_t3920;
        Expr_add_child(assign, _t3920);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return assign;
    }
    ;
    Bool _t3926; { Bool *_hp = (Bool *)check(p, TokenType_LParen()); _t3926 = *_hp; free(_hp); }
    (void)_t3926;
    if (_t3926) {
        Expr *_t3921 = parse_call(p, name, &(U32){t_line}, &(U32){t_col});
        (void)_t3921;
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return _t3921;
    }
    ;
    Str *_t3927 = Str_lit("Str", 3ULL);
    (void)_t3927;
    U64 _t3928; { U64 *_hp = (U64 *)Str_size(); _t3928 = *_hp; free(_hp); }
    (void)_t3928;
    U64 _t3929 = 8;
    (void)_t3929;
    Array *_va69 = Array_new(_t3927, &(U64){_t3928}, &(U64){_t3929});
    (void)_va69;
    Str_delete(_t3927, &(Bool){1});
    ;
    ;
    U64 _t3930 = 0;
    (void)_t3930;
    Str *_t3931 = Str_clone(&p->path);
    (void)_t3931;
    Array_set(_va69, &(U64){_t3930}, _t3931);
    ;
    U64 _t3932 = 1;
    (void)_t3932;
    Str *_t3933 = Str_lit(":", 1ULL);
    (void)_t3933;
    Array_set(_va69, &(U64){_t3932}, _t3933);
    ;
    U64 _t3934 = 2;
    (void)_t3934;
    Str *_t3935 = U32_to_str(&(U32){t_line});
    (void)_t3935;
    ;
    Array_set(_va69, &(U64){_t3934}, _t3935);
    ;
    U64 _t3936 = 3;
    (void)_t3936;
    Str *_t3937 = Str_lit(":", 1ULL);
    (void)_t3937;
    Array_set(_va69, &(U64){_t3936}, _t3937);
    ;
    U64 _t3938 = 4;
    (void)_t3938;
    Str *_t3939 = U32_to_str(&(U32){t_col});
    (void)_t3939;
    ;
    Array_set(_va69, &(U64){_t3938}, _t3939);
    ;
    U64 _t3940 = 5;
    (void)_t3940;
    Str *_t3941 = Str_lit(": expected ':=', ':', '=' or '(' after identifier '", 51ULL);
    (void)_t3941;
    Array_set(_va69, &(U64){_t3940}, _t3941);
    ;
    U64 _t3942 = 6;
    (void)_t3942;
    Str *_t3943 = Str_clone(name);
    (void)_t3943;
    Str_delete(name, &(Bool){1});
    Array_set(_va69, &(U64){_t3942}, _t3943);
    ;
    U64 _t3944 = 7;
    (void)_t3944;
    Str *_t3945 = Str_lit("'", 1ULL);
    (void)_t3945;
    Array_set(_va69, &(U64){_t3944}, _t3945);
    ;
    Str *_t3946 = Str_lit("src/self/parser.til:782:11", 26ULL);
    (void)_t3946;
    panic(_t3946, _va69);
    Str_delete(_t3946, &(Bool){1});
    U32 _t3947 = 0;
    (void)_t3947;
    U32 _t3948 = 0;
    (void)_t3948;
    Expr *_t3949 = Expr_new(ExprData_Body(), _t3947, _t3948, &p->path);
    (void)_t3949;
    ;
    ;
    return _t3949;
}

Expr * parse_statement(Parser * p) {
    (void)p;
    U32 t_line; { U32 *_hp = (U32 *)peek_line(p); t_line = *_hp; free(_hp); }
    (void)t_line;
    U32 t_col; { U32 *_hp = (U32 *)peek_col(p); t_col = *_hp; free(_hp); }
    (void)t_col;
    Token *t = peek(p);
    (void)t;
    Bool _t4075; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t4075 = *_hp; free(_hp); }
    (void)_t4075;
    if (_t4075) {
        Bool _t3950 = 0;
        (void)_t3950;
        Bool _t3951 = 0;
        (void)_t3951;
        Expr *_t3952 = parse_statement_ident(p, &(Bool){_t3950}, &(Bool){_t3951});
        (void)_t3952;
        ;
        ;
        ;
        ;
        ;
        return _t3952;
    }
    ;
    Bool _t4076; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwRef()); _t4076 = *_hp; free(_hp); }
    (void)_t4076;
    if (_t4076) {
        Token *_t3957 = advance(p);
        (void)_t3957;
        Bool ref_mut = 0;
        (void)ref_mut;
        Bool _t3958; { Bool *_hp = (Bool *)check(p, TokenType_KwMut()); _t3958 = *_hp; free(_hp); }
        (void)_t3958;
        if (_t3958) {
            Token *_t3953 = advance(p);
            (void)_t3953;
            Bool _t3954 = 1;
            (void)_t3954;
            ref_mut = _t3954;
            ;
        }
        ;
        U32 i_line; { U32 *_hp = (U32 *)peek_line(p); i_line = *_hp; free(_hp); }
        (void)i_line;
        U32 i_col; { U32 *_hp = (U32 *)peek_col(p); i_col = *_hp; free(_hp); }
        (void)i_col;
        Str *iname = expect_text(p, TokenType_Ident());
        (void)iname;
        Bool _t3959 = 0;
        (void)_t3959;
        Bool _t3960 = 0;
        (void)_t3960;
        Bool _t3961 = 1;
        (void)_t3961;
        Bool _t3962 = 0;
        (void)_t3962;
        I32 _t3963 = 0;
        (void)_t3963;
        I32 _t3964 = 0;
        (void)_t3964;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(iname); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3959;
        dd->is_namespace = _t3960;
        dd->is_ref = _t3961;
        dd->is_own = _t3962;
        dd->field_offset = _t3963;
        dd->field_size = _t3964;
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
            Bool _t3955 = 1;
            (void)_t3955;
            dd->is_mut = _t3955;
            ;
        }
        ;
        Bool _t3965; { Bool *_hp = (Bool *)check(p, TokenType_Colon()); _t3965 = *_hp; free(_hp); }
        (void)_t3965;
        if (_t3965) {
            Token *_t3956 = advance(p);
            (void)_t3956;
            Str_delete(&dd->explicit_type, &(Bool){0});
            { Str *_fa = expect_text(p, TokenType_Ident()); dd->explicit_type = *_fa; free(_fa); }
            expect_token(p, TokenType_Eq());
        } else {
            expect_token(p, TokenType_ColonEq());
        }
        ;
        ExprData *_t3966 = ExprData_Decl(dd);
        (void)_t3966;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3966, i_line, i_col, &p->path);
        (void)decl;
        ExprData_delete(_t3966, &(Bool){1});
        ;
        ;
        Expr *_t3967 = parse_expression(p);
        (void)_t3967;
        Expr_add_child(decl, _t3967);
        ;
        ;
        ;
        return decl;
    }
    ;
    Bool _t4077; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMut()); _t4077 = *_hp; free(_hp); }
    (void)_t4077;
    if (_t4077) {
        Token *_t3968 = advance(p);
        (void)_t3968;
        Bool _t3969 = 1;
        (void)_t3969;
        Bool _t3970 = 0;
        (void)_t3970;
        Expr *_t3971 = parse_statement_ident(p, &(Bool){_t3969}, &(Bool){_t3970});
        (void)_t3971;
        ;
        ;
        ;
        ;
        ;
        return _t3971;
    }
    ;
    Bool _t4078; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwReturn()); _t4078 = *_hp; free(_hp); }
    (void)_t4078;
    if (_t4078) {
        Token *_t3973 = advance(p);
        (void)_t3973;
        Expr *ret = Expr_new(ExprData_Return(), t_line, t_col, &p->path);
        (void)ret;
        Bool _t3974; { Bool *_hp = (Bool *)check(p, TokenType_RBrace()); _t3974 = *_hp; free(_hp); }
        (void)_t3974;
        Bool _t3975; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t3975 = *_hp; free(_hp); }
        (void)_t3975;
        Bool _t3976 = Bool_not(_t3974);
        (void)_t3976;
        ;
        Bool _t3977 = Bool_not(_t3975);
        (void)_t3977;
        ;
        Bool _t3978 = Bool_and(_t3976, _t3977);
        (void)_t3978;
        ;
        ;
        if (_t3978) {
            Expr *_t3972 = parse_expression(p);
            (void)_t3972;
            Expr_add_child(ret, _t3972);
        }
        ;
        ;
        ;
        ;
        return ret;
    }
    ;
    Bool _t4079; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwIf()); _t4079 = *_hp; free(_hp); }
    (void)_t4079;
    if (_t4079) {
        Token *_t3985 = advance(p);
        (void)_t3985;
        Expr *node = Expr_new(ExprData_If(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t3986 = parse_expression(p);
        (void)_t3986;
        Expr_add_child(node, _t3986);
        expect_token(p, TokenType_LBrace());
        Expr *_t3987 = parse_block(p);
        (void)_t3987;
        Expr_add_child(node, _t3987);
        Bool _t3988; { Bool *_hp = (Bool *)check(p, TokenType_KwElse()); _t3988 = *_hp; free(_hp); }
        (void)_t3988;
        if (_t3988) {
            Token *_t3983 = advance(p);
            (void)_t3983;
            Bool _t3984; { Bool *_hp = (Bool *)check(p, TokenType_KwIf()); _t3984 = *_hp; free(_hp); }
            (void)_t3984;
            if (_t3984) {
                U32 _t3979; { U32 *_hp = (U32 *)peek_line(p); _t3979 = *_hp; free(_hp); }
                (void)_t3979;
                U32 _t3980; { U32 *_hp = (U32 *)peek_col(p); _t3980 = *_hp; free(_hp); }
                (void)_t3980;
                Expr *else_body = Expr_new(ExprData_Body(), _t3979, _t3980, &p->path);
                (void)else_body;
                ;
                ;
                Expr *_t3981 = parse_statement(p);
                (void)_t3981;
                Expr_add_child(else_body, _t3981);
                Expr_add_child(node, else_body);
            } else {
                expect_token(p, TokenType_LBrace());
                Expr *_t3982 = parse_block(p);
                (void)_t3982;
                Expr_add_child(node, _t3982);
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
    Bool _t4080; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t4080 = *_hp; free(_hp); }
    (void)_t4080;
    Bool _t4081; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t4081 = *_hp; free(_hp); }
    (void)_t4081;
    Bool _t4082 = Bool_or(_t4080, _t4081);
    (void)_t4082;
    ;
    ;
    Bool _t4083; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t4083 = *_hp; free(_hp); }
    (void)_t4083;
    Bool _t4084 = Bool_or(_t4082, _t4083);
    (void)_t4084;
    ;
    ;
    Bool _t4085; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t4085 = *_hp; free(_hp); }
    (void)_t4085;
    Bool _t4086 = Bool_or(_t4084, _t4085);
    (void)_t4086;
    ;
    ;
    if (_t4086) {
        Expr *_t3989 = parse_expression(p);
        (void)_t3989;
        ;
        ;
        ;
        return _t3989;
    }
    ;
    Bool _t4087; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t4087 = *_hp; free(_hp); }
    (void)_t4087;
    if (_t4087) {
        Token *_t3990 = advance(p);
        (void)_t3990;
        Expr *_t3991 = parse_block(p);
        (void)_t3991;
        ;
        ;
        ;
        return _t3991;
    }
    ;
    Bool _t4088; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwWhile()); _t4088 = *_hp; free(_hp); }
    (void)_t4088;
    if (_t4088) {
        Token *_t3992 = advance(p);
        (void)_t3992;
        Expr *node = Expr_new(ExprData_While(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t3993 = parse_expression(p);
        (void)_t3993;
        Expr_add_child(node, _t3993);
        expect_token(p, TokenType_LBrace());
        Expr *_t3994 = parse_block(p);
        (void)_t3994;
        Expr_add_child(node, _t3994);
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4089; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFor()); _t4089 = *_hp; free(_hp); }
    (void)_t4089;
    if (_t4089) {
        Token *_t3996 = advance(p);
        (void)_t3996;
        U32 i_line; { U32 *_hp = (U32 *)peek_line(p); i_line = *_hp; free(_hp); }
        (void)i_line;
        U32 i_col; { U32 *_hp = (U32 *)peek_col(p); i_col = *_hp; free(_hp); }
        (void)i_col;
        Str *iname = expect_text(p, TokenType_Ident());
        (void)iname;
        ExprData *_t3997 = ExprData_ForIn(iname);
        (void)_t3997;
        Str_delete(iname, &(Bool){1});
        Expr *node = Expr_new(_t3997, i_line, i_col, &p->path);
        (void)node;
        ExprData_delete(_t3997, &(Bool){1});
        ;
        ;
        Bool _t3998; { Bool *_hp = (Bool *)check(p, TokenType_Colon()); _t3998 = *_hp; free(_hp); }
        (void)_t3998;
        if (_t3998) {
            Token *_t3995 = advance(p);
            (void)_t3995;
            Str_delete(&node->struct_name, &(Bool){0});
            { Str *_fa = expect_text(p, TokenType_Ident()); node->struct_name = *_fa; free(_fa); }
        }
        ;
        expect_token(p, TokenType_KwIn());
        Expr *_t3999 = parse_expression(p);
        (void)_t3999;
        Expr_add_child(node, _t3999);
        expect_token(p, TokenType_LBrace());
        Expr *_t4000 = parse_block(p);
        (void)_t4000;
        Expr_add_child(node, _t4000);
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4090; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwSwitch()); _t4090 = *_hp; free(_hp); }
    (void)_t4090;
    if (_t4090) {
        Token *_t4022 = advance(p);
        (void)_t4022;
        Expr *node = Expr_new(ExprData_Switch(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t4023 = parse_expression(p);
        (void)_t4023;
        Expr_add_child(node, _t4023);
        expect_token(p, TokenType_LBrace());
        while (1) {
            Bool _t4012; { Bool *_hp = (Bool *)check(p, TokenType_RBrace()); _t4012 = *_hp; free(_hp); }
            (void)_t4012;
            Bool _t4013; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t4013 = *_hp; free(_hp); }
            (void)_t4013;
            Bool _t4014 = Bool_not(_t4012);
            (void)_t4014;
            ;
            Bool _t4015 = Bool_not(_t4013);
            (void)_t4015;
            ;
            Bool _wcond4001 = Bool_and(_t4014, _t4015);
            (void)_wcond4001;
            ;
            ;
            if (_wcond4001) {
            } else {
                ;
                break;
            }
            ;
            expect_token(p, TokenType_KwCase());
            U32 _t4016; { U32 *_hp = (U32 *)peek_line(p); _t4016 = *_hp; free(_hp); }
            (void)_t4016;
            U32 _t4017; { U32 *_hp = (U32 *)peek_col(p); _t4017 = *_hp; free(_hp); }
            (void)_t4017;
            Expr *cn = Expr_new(ExprData_Case(), _t4016, _t4017, &p->path);
            (void)cn;
            ;
            ;
            Bool _t4018; { Bool *_hp = (Bool *)check(p, TokenType_Colon()); _t4018 = *_hp; free(_hp); }
            (void)_t4018;
            Bool _t4019 = Bool_not(_t4018);
            (void)_t4019;
            ;
            if (_t4019) {
                Expr *_t4002 = parse_expression(p);
                (void)_t4002;
                Expr_add_child(cn, _t4002);
            }
            ;
            expect_token(p, TokenType_Colon());
            U32 _t4020; { U32 *_hp = (U32 *)peek_line(p); _t4020 = *_hp; free(_hp); }
            (void)_t4020;
            U32 _t4021; { U32 *_hp = (U32 *)peek_col(p); _t4021 = *_hp; free(_hp); }
            (void)_t4021;
            Expr *cb = Expr_new(ExprData_Body(), _t4020, _t4021, &p->path);
            (void)cb;
            ;
            ;
            while (1) {
                Bool _t4004; { Bool *_hp = (Bool *)check(p, TokenType_KwCase()); _t4004 = *_hp; free(_hp); }
                (void)_t4004;
                Bool _t4005; { Bool *_hp = (Bool *)check(p, TokenType_RBrace()); _t4005 = *_hp; free(_hp); }
                (void)_t4005;
                Bool _t4006 = Bool_not(_t4004);
                (void)_t4006;
                ;
                Bool _t4007 = Bool_not(_t4005);
                (void)_t4007;
                ;
                Bool _t4008; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t4008 = *_hp; free(_hp); }
                (void)_t4008;
                Bool _t4009 = Bool_and(_t4006, _t4007);
                (void)_t4009;
                ;
                ;
                Bool _t4010 = Bool_not(_t4008);
                (void)_t4010;
                ;
                Bool _wcond4003 = Bool_and(_t4009, _t4010);
                (void)_wcond4003;
                ;
                ;
                if (_wcond4003) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t4011 = parse_statement(p);
                (void)_t4011;
                Expr_add_child(cb, _t4011);
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
    Bool _t4091; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwOwn()); _t4091 = *_hp; free(_hp); }
    (void)_t4091;
    if (_t4091) {
        Token *_t4064 = advance(p);
        (void)_t4064;
        Bool _t4065; { Bool *_hp = (Bool *)check(p, TokenType_Ident()); _t4065 = *_hp; free(_hp); }
        (void)_t4065;
        Bool _t4066; { Bool *_hp = (Bool *)check(p, TokenType_KwMut()); _t4066 = *_hp; free(_hp); }
        (void)_t4066;
        Bool _t4067 = Bool_or(_t4065, _t4066);
        (void)_t4067;
        ;
        ;
        if (_t4067) {
            Bool own_mut = 0;
            (void)own_mut;
            Bool _t4054; { Bool *_hp = (Bool *)check(p, TokenType_KwMut()); _t4054 = *_hp; free(_hp); }
            (void)_t4054;
            if (_t4054) {
                Token *_t4024 = advance(p);
                (void)_t4024;
                Bool _t4025 = 1;
                (void)_t4025;
                own_mut = _t4025;
                ;
            }
            ;
            Bool _t4055; { Bool *_hp = (Bool *)check(p, TokenType_Ident()); _t4055 = *_hp; free(_hp); }
            (void)_t4055;
            if (_t4055) {
                U32 _t4035 = 1;
                (void)_t4035;
                U32 _t4036 = U32_add(p->pos, _t4035);
                (void)_t4036;
                ;
                Bool _t4037; { Bool *_hp = (Bool *)U32_lt(&(U32){_t4036}, &p->count); _t4037 = *_hp; free(_hp); }
                (void)_t4037;
                ;
                if (_t4037) {
                    U32 _t4028 = 1;
                    (void)_t4028;
                    U32 _t4029 = U32_add(p->pos, _t4028);
                    (void)_t4029;
                    ;
                    I64 _t4030 = U32_to_i64(_t4029);
                    (void)_t4030;
                    ;
                    U64 *_t4031 = malloc(sizeof(U64)); *_t4031 = I64_to_u64(_t4030);
                    (void)_t4031;
                    ;
                    Token *nt = Vec_get(&p->tokens, _t4031);
                    (void)nt;
                    Bool _t4032; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_ColonEq()); _t4032 = *_hp; free(_hp); }
                    (void)_t4032;
                    Bool _t4033; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Colon()); _t4033 = *_hp; free(_hp); }
                    (void)_t4033;
                    U64_delete(_t4031, &(Bool){1});
                    Bool _t4034 = Bool_or(_t4032, _t4033);
                    (void)_t4034;
                    ;
                    ;
                    if (_t4034) {
                        Bool _t4026 = 1;
                        (void)_t4026;
                        Expr *_t4027 = parse_statement_ident(p, &(Bool){own_mut}, &(Bool){_t4026});
                        (void)_t4027;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        return _t4027;
                    }
                    ;
                }
                ;
            }
            ;
            if (own_mut) {
                Str *_t4038 = Str_lit("Str", 3ULL);
                (void)_t4038;
                U64 _t4039; { U64 *_hp = (U64 *)Str_size(); _t4039 = *_hp; free(_hp); }
                (void)_t4039;
                U64 _t4040 = 6;
                (void)_t4040;
                Array *_va70 = Array_new(_t4038, &(U64){_t4039}, &(U64){_t4040});
                (void)_va70;
                Str_delete(_t4038, &(Bool){1});
                ;
                ;
                U64 _t4041 = 0;
                (void)_t4041;
                Str *_t4042 = Str_clone(&p->path);
                (void)_t4042;
                Array_set(_va70, &(U64){_t4041}, _t4042);
                ;
                U64 _t4043 = 1;
                (void)_t4043;
                Str *_t4044 = Str_lit(":", 1ULL);
                (void)_t4044;
                Array_set(_va70, &(U64){_t4043}, _t4044);
                ;
                U64 _t4045 = 2;
                (void)_t4045;
                Str *_t4046 = U32_to_str(&(U32){t_line});
                (void)_t4046;
                Array_set(_va70, &(U64){_t4045}, _t4046);
                ;
                U64 _t4047 = 3;
                (void)_t4047;
                Str *_t4048 = Str_lit(":", 1ULL);
                (void)_t4048;
                Array_set(_va70, &(U64){_t4047}, _t4048);
                ;
                U64 _t4049 = 4;
                (void)_t4049;
                Str *_t4050 = U32_to_str(&(U32){t_col});
                (void)_t4050;
                Array_set(_va70, &(U64){_t4049}, _t4050);
                ;
                U64 _t4051 = 5;
                (void)_t4051;
                Str *_t4052 = Str_lit(": expected identifier after 'own mut'", 37ULL);
                (void)_t4052;
                Array_set(_va70, &(U64){_t4051}, _t4052);
                ;
                Str *_t4053 = Str_lit("src/self/parser.til:915:23", 26ULL);
                (void)_t4053;
                panic(_t4053, _va70);
                Str_delete(_t4053, &(Bool){1});
            }
            ;
        }
        ;
        Expr *expr = parse_expression(p);
        (void)expr;
        I64 _t4068 = 0;
        (void)_t4068;
        I64 _t4069 = 1;
        (void)_t4069;
        I64 primary_idx = I64_sub(_t4068, _t4069);
        (void)primary_idx;
        ;
        ;
        ;
        Expr *cur = Expr_clone(expr);
        (void)cur;
        while (1) {
            U64 _t4057; { U64 *_hp = (U64 *)Vec_len(&cur->children); _t4057 = *_hp; free(_hp); }
            (void)_t4057;
            U64 _t4058 = 0;
            (void)_t4058;
            Bool _t4059; { Bool *_hp = (Bool *)ExprData_is_FCall(&cur->data); _t4059 = *_hp; free(_hp); }
            (void)_t4059;
            Bool _t4060; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(&cur->data); _t4060 = *_hp; free(_hp); }
            (void)_t4060;
            Bool _t4061; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4057}, &(U64){_t4058}); _t4061 = *_hp; free(_hp); }
            (void)_t4061;
            ;
            ;
            Bool _t4062 = Bool_or(_t4059, _t4060);
            (void)_t4062;
            ;
            ;
            Bool _wcond4056 = Bool_and(_t4061, _t4062);
            (void)_wcond4056;
            ;
            ;
            if (_wcond4056) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t4063 = malloc(sizeof(U64));
            *_t4063 = 0;
            (void)_t4063;
            Expr *ch = Vec_get(&cur->children, _t4063);
            (void)ch;
            cur = Expr_clone(ch);
            U64_delete(_t4063, &(Bool){1});
        }
        Bool _t4070 = 1;
        (void)_t4070;
        cur->is_own_arg = _t4070;
        ;
        Expr_delete(cur, &(Bool){1});
        ;
        ;
        ;
        ;
        return expr;
    }
    ;
    Bool _t4092; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwBreak()); _t4092 = *_hp; free(_hp); }
    (void)_t4092;
    if (_t4092) {
        Token *_t4071 = advance(p);
        (void)_t4071;
        Expr *_t4072 = Expr_new(ExprData_Break(), t_line, t_col, &p->path);
        (void)_t4072;
        ;
        ;
        ;
        return _t4072;
    }
    ;
    Bool _t4093; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwContinue()); _t4093 = *_hp; free(_hp); }
    (void)_t4093;
    if (_t4093) {
        Token *_t4073 = advance(p);
        (void)_t4073;
        Expr *_t4074 = Expr_new(ExprData_Continue(), t_line, t_col, &p->path);
        (void)_t4074;
        ;
        ;
        ;
        return _t4074;
    }
    ;
    Str *_t4094 = Str_lit("Str", 3ULL);
    (void)_t4094;
    U64 _t4095; { U64 *_hp = (U64 *)Str_size(); _t4095 = *_hp; free(_hp); }
    (void)_t4095;
    U64 _t4096 = 8;
    (void)_t4096;
    Array *_va71 = Array_new(_t4094, &(U64){_t4095}, &(U64){_t4096});
    (void)_va71;
    Str_delete(_t4094, &(Bool){1});
    ;
    ;
    U64 _t4097 = 0;
    (void)_t4097;
    Str *_t4098 = Str_clone(&p->path);
    (void)_t4098;
    Array_set(_va71, &(U64){_t4097}, _t4098);
    ;
    U64 _t4099 = 1;
    (void)_t4099;
    Str *_t4100 = Str_lit(":", 1ULL);
    (void)_t4100;
    Array_set(_va71, &(U64){_t4099}, _t4100);
    ;
    U64 _t4101 = 2;
    (void)_t4101;
    Str *_t4102 = U32_to_str(&(U32){t_line});
    (void)_t4102;
    ;
    Array_set(_va71, &(U64){_t4101}, _t4102);
    ;
    U64 _t4103 = 3;
    (void)_t4103;
    Str *_t4104 = Str_lit(":", 1ULL);
    (void)_t4104;
    Array_set(_va71, &(U64){_t4103}, _t4104);
    ;
    U64 _t4105 = 4;
    (void)_t4105;
    Str *_t4106 = U32_to_str(&(U32){t_col});
    (void)_t4106;
    ;
    Array_set(_va71, &(U64){_t4105}, _t4106);
    ;
    U64 _t4107 = 5;
    (void)_t4107;
    Str *_t4108 = Str_lit(": expected statement, found '", 29ULL);
    (void)_t4108;
    Array_set(_va71, &(U64){_t4107}, _t4108);
    ;
    U64 _t4109 = 6;
    (void)_t4109;
    Str *_t4110 = Str_clone(&t->text);
    (void)_t4110;
    Array_set(_va71, &(U64){_t4109}, _t4110);
    ;
    U64 _t4111 = 7;
    (void)_t4111;
    Str *_t4112 = Str_lit("'", 1ULL);
    (void)_t4112;
    Array_set(_va71, &(U64){_t4111}, _t4112);
    ;
    Str *_t4113 = Str_lit("src/self/parser.til:942:11", 26ULL);
    (void)_t4113;
    panic(_t4113, _va71);
    Str_delete(_t4113, &(Bool){1});
    U32 _t4114 = 0;
    (void)_t4114;
    U32 _t4115 = 0;
    (void)_t4115;
    Expr *_t4116 = Expr_new(ExprData_Body(), _t4114, _t4115, &p->path);
    (void)_t4116;
    ;
    ;
    return _t4116;
}

Expr * parse(Vec * tokens, Str * path, Str * mode_out) {
    (void)tokens;
    (void)path;
    (void)mode_out;
    U64 _t4127; { U64 *_hp = (U64 *)Vec_len(tokens); _t4127 = *_hp; free(_hp); }
    (void)_t4127;
    I64 _t4128 = 0;
    (void)_t4128;
    Parser *p = malloc(sizeof(Parser));
    { Vec *_ca = Vec_clone(tokens); p->tokens = *_ca; free(_ca); }
    p->count = _t4127;
    p->pos = _t4128;
    { Str *_ca = Str_clone(path); p->path = *_ca; free(_ca); }
    (void)p;
    ;
    ;
    Bool _t4129; { Bool *_hp = (Bool *)check(p, TokenType_KwMode()); _t4129 = *_hp; free(_hp); }
    (void)_t4129;
    if (_t4129) {
        Token *_t4120 = advance(p);
        (void)_t4120;
        Bool _t4121; { Bool *_hp = (Bool *)check(p, TokenType_Ident()); _t4121 = *_hp; free(_hp); }
        (void)_t4121;
        Bool _t4122; { Bool *_hp = (Bool *)check(p, TokenType_KwTest()); _t4122 = *_hp; free(_hp); }
        (void)_t4122;
        Bool _t4123 = Bool_or(_t4121, _t4122);
        (void)_t4123;
        ;
        ;
        if (_t4123) {
            Str *_t4117 = Str_clone(&peek(p)->text);
            (void)_t4117;
            U64 _t4118; { U64 *_hp = (U64 *)Str_size(); _t4118 = *_hp; free(_hp); }
            (void)_t4118;
            swap(mode_out, _t4117, _t4118);
            Str_delete(_t4117, &(Bool){1});
            ;
            Token *_t4119 = advance(p);
            (void)_t4119;
        } else {
            expect_token(p, TokenType_Ident());
        }
        ;
    }
    ;
    U32 _t4130 = 1;
    (void)_t4130;
    U32 _t4131 = 1;
    (void)_t4131;
    Expr *root = Expr_new(ExprData_Body(), _t4130, _t4131, &p->path);
    (void)root;
    ;
    ;
    while (1) {
        Bool _t4125; { Bool *_hp = (Bool *)check(p, TokenType_Eof()); _t4125 = *_hp; free(_hp); }
        (void)_t4125;
        Bool _wcond4124 = Bool_not(_t4125);
        (void)_wcond4124;
        ;
        if (_wcond4124) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t4126 = parse_statement(p);
        (void)_t4126;
        Expr_add_child(root, _t4126);
    }
    Parser_delete(p, &(Bool){1});
    return root;
}

