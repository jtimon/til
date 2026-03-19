#include "parser_parser.h"

Parser * Parser_clone(Parser * self) {
    (void)self;
    U64 _t3041 = U64_clone(&self->pos);
    (void)_t3041;
    Parser *_t3042 = malloc(sizeof(Parser));
    { Vec *_ca = Vec_clone(&self->tokens); _t3042->tokens = *_ca; free(_ca); }
    _t3042->pos = _t3041;
    { Str *_ca = Str_clone(&self->path); _t3042->path = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->fn_sig_decls); _t3042->fn_sig_decls = *_ca; free(_ca); }
    (void)_t3042;
    ;
    return _t3042;
}

void Parser_delete(Parser * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t3043 = 0;
    (void)_t3043;
    Vec_delete(&self->tokens, &(Bool){_t3043});
    ;
    Bool _t3044 = 0;
    (void)_t3044;
    U64_delete(&self->pos, &(Bool){_t3044});
    ;
    Bool _t3045 = 0;
    (void)_t3045;
    Str_delete(&self->path, &(Bool){_t3045});
    ;
    Bool _t3046 = 0;
    (void)_t3046;
    Vec_delete(&self->fn_sig_decls, &(Bool){_t3046});
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

Str * parse_fn_signature(Parser * p, U32 line, U32 col) {
    (void)p;
    (void)line;
    (void)col;
    Bool _t3151 = check(p, TokenType_LParen());
    (void)_t3151;
    Bool _t3152 = Bool_not(_t3151);
    (void)_t3152;
    ;
    if (_t3152) {
        Str *_t3111 = Str_lit("", 0ULL);
        (void)_t3111;
        ;
        return _t3111;
    }
    ;
    Token *_t3153 = advance(p);
    (void)_t3153;
    Str *_t3154 = Str_lit("Str", 3ULL);
    (void)_t3154;
    U64 _t3155; { U64 *_hp = (U64 *)Str_size(); _t3155 = *_hp; free(_hp); }
    (void)_t3155;
    Vec *ptypes = Vec_new(_t3154, &(U64){_t3155});
    (void)ptypes;
    Str_delete(_t3154, &(Bool){1});
    ;
    Str *_t3156 = Str_lit("Bool", 4ULL);
    (void)_t3156;
    U64 _t3157; { U64 *_hp = (U64 *)Bool_size(); _t3157 = *_hp; free(_hp); }
    (void)_t3157;
    Vec *pmuts = Vec_new(_t3156, &(U64){_t3157});
    (void)pmuts;
    Str_delete(_t3156, &(Bool){1});
    ;
    while (1) {
        Bool _t3116 = check(p, TokenType_RParen());
        (void)_t3116;
        Bool _t3117 = check(p, TokenType_Eof());
        (void)_t3117;
        Bool _t3118 = Bool_not(_t3116);
        (void)_t3118;
        ;
        Bool _t3119 = Bool_not(_t3117);
        (void)_t3119;
        ;
        Bool _wcond3112 = Bool_and(_t3118, _t3119);
        (void)_wcond3112;
        ;
        ;
        if (_wcond3112) {
        } else {
            ;
            break;
        }
        ;
        Bool is_mut = 0;
        (void)is_mut;
        Bool _t3120 = check(p, TokenType_KwMut());
        (void)_t3120;
        if (_t3120) {
            Token *_t3113 = advance(p);
            (void)_t3113;
            Bool _t3114 = 1;
            (void)_t3114;
            is_mut = _t3114;
            ;
        }
        ;
        Str *ptype = expect_text(p, TokenType_Ident());
        (void)ptype;
        Vec_push(ptypes, ptype);
        Vec_push(pmuts, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = is_mut; _oa; }));
        Bool _t3121 = check(p, TokenType_Comma());
        (void)_t3121;
        if (_t3121) {
            Token *_t3115 = advance(p);
            (void)_t3115;
        }
        ;
    }
    Token *_t3158 = expect_token(p, TokenType_RParen());
    (void)_t3158;
    Str *return_type = Str_lit("", 0ULL);
    (void)return_type;
    Bool _t3159 = check(p, TokenType_KwReturns());
    (void)_t3159;
    if (_t3159) {
        Token *_t3122 = advance(p);
        (void)_t3122;
        return_type = expect_text(p, TokenType_Ident());
    }
    ;
    Str *name = Str_lit("_Fn", 3ULL);
    (void)name;
    {
        U64 _fi3123 = 0;
        (void)_fi3123;
        while (1) {
            U64 _t3126 = 0;
            (void)_t3126;
            U64 _t3127; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3127 = *_hp; free(_hp); }
            (void)_t3127;
            Range *_t3128 = Range_new(_t3126, _t3127);
            (void)_t3128;
            ;
            ;
            U64 _t3129; { U64 *_hp = (U64 *)Range_len(_t3128); _t3129 = *_hp; free(_hp); }
            (void)_t3129;
            Range_delete(_t3128, &(Bool){1});
            Bool _wcond3124; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3123}, &(U64){_t3129}); _wcond3124 = *_hp; free(_hp); }
            (void)_wcond3124;
            ;
            if (_wcond3124) {
            } else {
                ;
                break;
            }
            ;
            U64 _t3130 = 0;
            (void)_t3130;
            U64 _t3131; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3131 = *_hp; free(_hp); }
            (void)_t3131;
            Range *_t3132 = Range_new(_t3130, _t3131);
            (void)_t3132;
            ;
            ;
            U64 *i = Range_get(_t3132, _fi3123);
            (void)i;
            Range_delete(_t3132, &(Bool){1});
            U64 _t3133 = 1;
            (void)_t3133;
            U64 _t3134 = U64_add(_fi3123, _t3133);
            (void)_t3134;
            ;
            _fi3123 = _t3134;
            ;
            Str *_t3135 = Str_lit("_", 1ULL);
            (void)_t3135;
            name = Str_concat(name, _t3135);
            Str_delete(_t3135, &(Bool){1});
            Bool *m = Vec_get(pmuts, i);
            (void)m;
            if (DEREF(m)) {
                Str *_t3125 = Str_lit("mut_", 4ULL);
                (void)_t3125;
                name = Str_concat(name, _t3125);
                Str_delete(_t3125, &(Bool){1});
            }
            Str *t = Vec_get(ptypes, i);
            (void)t;
            name = Str_concat(name, t);
            U64_delete(i, &(Bool){1});
        }
        ;
    }
    U64 _t3160; { U64 *_hp = (U64 *)Str_len(return_type); _t3160 = *_hp; free(_hp); }
    (void)_t3160;
    U64 _t3161 = 0;
    (void)_t3161;
    Bool _t3162; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3160}, &(U64){_t3161}); _t3162 = *_hp; free(_hp); }
    (void)_t3162;
    ;
    ;
    if (_t3162) {
        Str *_t3136 = Str_lit("_ret_", 5ULL);
        (void)_t3136;
        name = Str_concat(name, _t3136);
        Str_delete(_t3136, &(Bool){1});
        name = Str_concat(name, return_type);
    }
    ;
    Str *_t3163 = Str_lit("Str", 3ULL);
    (void)_t3163;
    U64 _t3164; { U64 *_hp = (U64 *)Str_size(); _t3164 = *_hp; free(_hp); }
    (void)_t3164;
    Str *_t3165 = Str_lit("Str", 3ULL);
    (void)_t3165;
    U64 _t3166; { U64 *_hp = (U64 *)Str_size(); _t3166 = *_hp; free(_hp); }
    (void)_t3166;
    Str *_t3167 = Str_lit("Bool", 4ULL);
    (void)_t3167;
    U64 _t3168; { U64 *_hp = (U64 *)Bool_size(); _t3168 = *_hp; free(_hp); }
    (void)_t3168;
    Str *_t3169 = Str_lit("Bool", 4ULL);
    (void)_t3169;
    U64 _t3170; { U64 *_hp = (U64 *)Bool_size(); _t3170 = *_hp; free(_hp); }
    (void)_t3170;
    Str *_t3171 = Str_lit("Bool", 4ULL);
    (void)_t3171;
    U64 _t3172; { U64 *_hp = (U64 *)Bool_size(); _t3172 = *_hp; free(_hp); }
    (void)_t3172;
    Str *_t3173 = Str_lit("Str", 3ULL);
    (void)_t3173;
    U64 _t3174; { U64 *_hp = (U64 *)Str_size(); _t3174 = *_hp; free(_hp); }
    (void)_t3174;
    Str *_t3175 = Str_lit("Expr", 4ULL);
    (void)_t3175;
    U64 _t3176; { U64 *_hp = (U64 *)Expr_size(); _t3176 = *_hp; free(_hp); }
    (void)_t3176;
    I64 _t3177 = 0;
    (void)_t3177;
    I64 _t3178 = 1;
    (void)_t3178;
    I64 _t3179 = I64_sub(_t3177, _t3178);
    (void)_t3179;
    ;
    ;
    I64 _t3180 = 0;
    (void)_t3180;
    I64 _t3181 = 1;
    (void)_t3181;
    I64 _t3182 = I64_sub(_t3180, _t3181);
    (void)_t3182;
    ;
    ;
    U32 _t3183 = 0;
    (void)_t3183;
    I32 _t3184 = I64_to_i32(_t3179);
    (void)_t3184;
    ;
    I32 _t3185 = I64_to_i32(_t3182);
    (void)_t3185;
    ;
    Bool _t3186 = 0;
    (void)_t3186;
    Bool _t3187 = 0;
    (void)_t3187;
    FunctionDef *fd = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(FuncType_Func()); fd->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3163, &(U64){_t3164}); fd->param_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3165, &(U64){_t3166}); fd->param_types = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3167, &(U64){_t3168}); fd->param_muts = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3169, &(U64){_t3170}); fd->param_owns = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3171, &(U64){_t3172}); fd->param_shallows = *_ca; free(_ca); }
    fd->nparam = _t3183;
    { Map *_ca = Map_new(_t3173, &(U64){_t3174}, _t3175, &(U64){_t3176}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3184;
    fd->kwargs_index = _t3185;
    fd->return_is_ref = _t3186;
    fd->return_is_shallow = _t3187;
    (void)fd;
    Str_delete(_t3163, &(Bool){1});
    ;
    Str_delete(_t3165, &(Bool){1});
    ;
    Str_delete(_t3167, &(Bool){1});
    ;
    Str_delete(_t3169, &(Bool){1});
    ;
    Str_delete(_t3171, &(Bool){1});
    ;
    Str_delete(_t3173, &(Bool){1});
    ;
    Str_delete(_t3175, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    U64 _t3188; { U64 *_hp = (U64 *)Str_len(return_type); _t3188 = *_hp; free(_hp); }
    (void)_t3188;
    U64 _t3189 = 0;
    (void)_t3189;
    Bool _t3190; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3188}, &(U64){_t3189}); _t3190 = *_hp; free(_hp); }
    (void)_t3190;
    ;
    ;
    if (_t3190) {
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
    Bool _t3191 = 0;
    (void)_t3191;
    fd->return_is_ref = _t3191;
    ;
    Bool _t3192 = 0;
    (void)_t3192;
    fd->return_is_shallow = _t3192;
    ;
    I64 _t3193 = 0;
    (void)_t3193;
    I64 _t3194 = 1;
    (void)_t3194;
    I64 _t3195 = I64_sub(_t3193, _t3194);
    (void)_t3195;
    ;
    ;
    I32 _t3196 = I64_to_i32(_t3195);
    (void)_t3196;
    ;
    fd->variadic_index = _t3196;
    ;
    I64 _t3197 = 0;
    (void)_t3197;
    I64 _t3198 = 1;
    (void)_t3198;
    I64 _t3199 = I64_sub(_t3197, _t3198);
    (void)_t3199;
    ;
    ;
    I32 _t3200 = I64_to_i32(_t3199);
    (void)_t3200;
    ;
    fd->kwargs_index = _t3200;
    ;
    {
        U64 _fi3137 = 0;
        (void)_fi3137;
        while (1) {
            U64 _t3139 = 0;
            (void)_t3139;
            U64 _t3140; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3140 = *_hp; free(_hp); }
            (void)_t3140;
            Range *_t3141 = Range_new(_t3139, _t3140);
            (void)_t3141;
            ;
            ;
            U64 _t3142; { U64 *_hp = (U64 *)Range_len(_t3141); _t3142 = *_hp; free(_hp); }
            (void)_t3142;
            Range_delete(_t3141, &(Bool){1});
            Bool _wcond3138; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3137}, &(U64){_t3142}); _wcond3138 = *_hp; free(_hp); }
            (void)_wcond3138;
            ;
            if (_wcond3138) {
            } else {
                ;
                break;
            }
            ;
            U64 _t3143 = 0;
            (void)_t3143;
            U64 _t3144; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3144 = *_hp; free(_hp); }
            (void)_t3144;
            Range *_t3145 = Range_new(_t3143, _t3144);
            (void)_t3145;
            ;
            ;
            U64 _; { U64 *_hp = (U64 *)Range_get(_t3145, _fi3137); _ = *_hp; free(_hp); }
            (void)_;
            ;
            Range_delete(_t3145, &(Bool){1});
            U64 _t3146 = 1;
            (void)_t3146;
            U64 _t3147 = U64_add(_fi3137, _t3146);
            (void)_t3147;
            ;
            _fi3137 = _t3147;
            ;
            Str *_t3148 = Str_lit("", 0ULL);
            (void)_t3148;
            Vec_push(&fd->param_names, _t3148);
            Bool _t3149 = 0;
            (void)_t3149;
            Vec_push(&fd->param_owns, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3149; _oa; }));
            Bool _t3150 = 0;
            (void)_t3150;
            Vec_push(&fd->param_shallows, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = _t3150; _oa; }));
        }
        ;
    }
    Vec_delete(&fd->param_types, &(Bool){0});
    { Vec *_fa = Vec_clone(ptypes); fd->param_types = *_fa; free(_fa); }
    Vec_delete(ptypes, &(Bool){1});
    Vec_delete(&fd->param_muts, &(Bool){0});
    { Vec *_fa = Vec_clone(pmuts); fd->param_muts = *_fa; free(_fa); }
    Vec_delete(pmuts, &(Bool){1});
    U64 _t3201; { U64 *_hp = (U64 *)Vec_len(&fd->param_types); _t3201 = *_hp; free(_hp); }
    (void)_t3201;
    I64 _t3202 = U64_to_i64(_t3201);
    (void)_t3202;
    ;
    U32 _t3203 = I64_to_u32(_t3202);
    (void)_t3203;
    ;
    fd->nparam = _t3203;
    ;
    ExprData *_t3204 = ExprData_FuncDef(fd);
    (void)_t3204;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *sig = Expr_new(_t3204, line, col, &p->path);
    (void)sig;
    ExprData_delete(_t3204, &(Bool){1});
    Bool _t3205 = 0;
    (void)_t3205;
    Bool _t3206 = 0;
    (void)_t3206;
    Bool _t3207 = 0;
    (void)_t3207;
    Bool _t3208 = 0;
    (void)_t3208;
    I32 _t3209 = 0;
    (void)_t3209;
    I32 _t3210 = 0;
    (void)_t3210;
    Declaration *_t3211 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(name); _t3211->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t3211->explicit_type = *_ca; free(_ca); }
    _t3211->is_mut = _t3205;
    _t3211->is_namespace = _t3206;
    _t3211->is_ref = _t3207;
    _t3211->is_own = _t3208;
    _t3211->field_offset = _t3209;
    _t3211->field_size = _t3210;
    _t3211->field_struct_def = NULL;
    _t3211->fn_sig = NULL;
    (void)_t3211;
    ;
    ;
    ;
    ;
    ;
    ;
    ExprData *_t3212 = ExprData_Decl(_t3211);
    (void)_t3212;
    Declaration_delete(_t3211, &(Bool){1});
    Expr *decl = Expr_new(_t3212, line, col, &p->path);
    (void)decl;
    ExprData_delete(_t3212, &(Bool){1});
    Expr_add_child(decl, sig);
    Vec_push(&p->fn_sig_decls, decl);
    return name;
}

Expr * parse_block(Parser * p) {
    (void)p;
    U32 _t3219 = peek_line(p);
    (void)_t3219;
    U32 _t3220 = peek_col(p);
    (void)_t3220;
    Expr *body = Expr_new(ExprData_Body(), _t3219, _t3220, &p->path);
    (void)body;
    ;
    ;
    while (1) {
        Bool _t3214 = check(p, TokenType_RBrace());
        (void)_t3214;
        Bool _t3215 = check(p, TokenType_Eof());
        (void)_t3215;
        Bool _t3216 = Bool_not(_t3214);
        (void)_t3216;
        ;
        Bool _t3217 = Bool_not(_t3215);
        (void)_t3217;
        ;
        Bool _wcond3213 = Bool_and(_t3216, _t3217);
        (void)_wcond3213;
        ;
        ;
        if (_wcond3213) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t3218 = parse_statement(p);
        (void)_t3218;
        Expr_add_child(body, _t3218);
    }
    Token *_t3221 = expect_token(p, TokenType_RBrace());
    (void)_t3221;
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
        TokenType *_sw3222 = TokenType_clone(&kw->type);
        (void)_sw3222;
        Bool _t3234; { Bool *_hp = (Bool *)TokenType_eq(_sw3222, TokenType_KwFunc()); _t3234 = *_hp; free(_hp); }
        (void)_t3234;
        if (_t3234) {
            ft = FuncType_clone(FuncType_Func());
        } else {
            Bool _t3233; { Bool *_hp = (Bool *)TokenType_eq(_sw3222, TokenType_KwProc()); _t3233 = *_hp; free(_hp); }
            (void)_t3233;
            if (_t3233) {
                ft = FuncType_clone(FuncType_Proc());
            } else {
                Bool _t3232; { Bool *_hp = (Bool *)TokenType_eq(_sw3222, TokenType_KwTest()); _t3232 = *_hp; free(_hp); }
                (void)_t3232;
                if (_t3232) {
                    ft = FuncType_clone(FuncType_Test());
                } else {
                    Bool _t3231; { Bool *_hp = (Bool *)TokenType_eq(_sw3222, TokenType_KwMacro()); _t3231 = *_hp; free(_hp); }
                    (void)_t3231;
                    if (_t3231) {
                        ft = FuncType_clone(FuncType_Macro());
                    } else {
                        Bool _t3230; { Bool *_hp = (Bool *)TokenType_eq(_sw3222, TokenType_KwExtFunc()); _t3230 = *_hp; free(_hp); }
                        (void)_t3230;
                        if (_t3230) {
                            ft = FuncType_clone(FuncType_ExtFunc());
                        } else {
                            Bool _t3229; { Bool *_hp = (Bool *)TokenType_eq(_sw3222, TokenType_KwExtProc()); _t3229 = *_hp; free(_hp); }
                            (void)_t3229;
                            if (_t3229) {
                                ft = FuncType_clone(FuncType_ExtProc());
                            } else {
                                Str *_t3223 = Str_lit("Str", 3ULL);
                                (void)_t3223;
                                U64 _t3224; { U64 *_hp = (U64 *)Str_size(); _t3224 = *_hp; free(_hp); }
                                (void)_t3224;
                                U64 _t3225 = 1;
                                (void)_t3225;
                                Array *_va56 = Array_new(_t3223, &(U64){_t3224}, &(U64){_t3225});
                                (void)_va56;
                                Str_delete(_t3223, &(Bool){1});
                                ;
                                ;
                                U64 _t3226 = 0;
                                (void)_t3226;
                                Str *_t3227 = Str_lit("expected function keyword", 25ULL);
                                (void)_t3227;
                                Array_set(_va56, &(U64){_t3226}, _t3227);
                                ;
                                Str *_t3228 = Str_lit("src/self/parser.til:152:17", 26ULL);
                                (void)_t3228;
                                panic(_t3228, _va56);
                                Str_delete(_t3228, &(Bool){1});
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
        TokenType_delete(_sw3222, &(Bool){1});
        ;
    }
    Token *_t3408 = expect_token(p, TokenType_LParen());
    (void)_t3408;
    Str *_t3409 = Str_lit("Str", 3ULL);
    (void)_t3409;
    U64 _t3410; { U64 *_hp = (U64 *)Str_size(); _t3410 = *_hp; free(_hp); }
    (void)_t3410;
    Str *_t3411 = Str_lit("Str", 3ULL);
    (void)_t3411;
    U64 _t3412; { U64 *_hp = (U64 *)Str_size(); _t3412 = *_hp; free(_hp); }
    (void)_t3412;
    Str *_t3413 = Str_lit("Bool", 4ULL);
    (void)_t3413;
    U64 _t3414; { U64 *_hp = (U64 *)Bool_size(); _t3414 = *_hp; free(_hp); }
    (void)_t3414;
    Str *_t3415 = Str_lit("Bool", 4ULL);
    (void)_t3415;
    U64 _t3416; { U64 *_hp = (U64 *)Bool_size(); _t3416 = *_hp; free(_hp); }
    (void)_t3416;
    Str *_t3417 = Str_lit("Bool", 4ULL);
    (void)_t3417;
    U64 _t3418; { U64 *_hp = (U64 *)Bool_size(); _t3418 = *_hp; free(_hp); }
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
    { Vec *_ca = Vec_new(_t3409, &(U64){_t3410}); fd->param_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3411, &(U64){_t3412}); fd->param_types = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3413, &(U64){_t3414}); fd->param_muts = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3415, &(U64){_t3416}); fd->param_owns = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3417, &(U64){_t3418}); fd->param_shallows = *_ca; free(_ca); }
    fd->nparam = _t3429;
    { Map *_ca = Map_new(_t3419, &(U64){_t3420}, _t3421, &(U64){_t3422}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3430;
    fd->kwargs_index = _t3431;
    fd->return_is_ref = _t3432;
    fd->return_is_shallow = _t3433;
    (void)fd;
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
    while (1) {
        Bool _t3352 = check(p, TokenType_RParen());
        (void)_t3352;
        Bool _t3353 = check(p, TokenType_Eof());
        (void)_t3353;
        Bool _t3354 = Bool_not(_t3352);
        (void)_t3354;
        ;
        Bool _t3355 = Bool_not(_t3353);
        (void)_t3355;
        ;
        Bool _wcond3235 = Bool_and(_t3354, _t3355);
        (void)_wcond3235;
        ;
        ;
        if (_wcond3235) {
        } else {
            ;
            break;
        }
        ;
        Bool is_shallow = 0;
        (void)is_shallow;
        Bool _t3356 = check(p, TokenType_KwShallow());
        (void)_t3356;
        if (_t3356) {
            Token *_t3236 = advance(p);
            (void)_t3236;
            Bool _t3237 = 1;
            (void)_t3237;
            is_shallow = _t3237;
            ;
        }
        ;
        Bool is_own = 0;
        (void)is_own;
        Bool _t3357 = check(p, TokenType_KwOwn());
        (void)_t3357;
        if (_t3357) {
            Token *_t3238 = advance(p);
            (void)_t3238;
            Bool _t3239 = 1;
            (void)_t3239;
            is_own = _t3239;
            ;
        }
        ;
        Bool is_mut = 0;
        (void)is_mut;
        Bool _t3358 = check(p, TokenType_KwMut());
        (void)_t3358;
        if (_t3358) {
            Token *_t3240 = advance(p);
            (void)_t3240;
            Bool _t3241 = 1;
            (void)_t3241;
            is_mut = _t3241;
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
        Bool _t3359 = check(p, TokenType_Colon());
        (void)_t3359;
        Bool _t3360 = Bool_not(_t3359);
        (void)_t3360;
        ;
        if (_t3360) {
            tp = Str_clone(pname);
            nm = Str_lit("", 0ULL);
        } else {
            Token *_t3335 = expect_token(p, TokenType_Colon());
            (void)_t3335;
            Bool _t3336 = check(p, TokenType_DotDotDot());
            (void)_t3336;
            if (_t3336) {
                Token *_t3272 = advance(p);
                (void)_t3272;
                Bool _t3273 = Bool_or(is_own, is_mut);
                (void)_t3273;
                Bool _t3274 = Bool_or(_t3273, is_shallow);
                (void)_t3274;
                ;
                if (_t3274) {
                    Str *_t3242 = Str_lit("Str", 3ULL);
                    (void)_t3242;
                    U64 _t3243; { U64 *_hp = (U64 *)Str_size(); _t3243 = *_hp; free(_hp); }
                    (void)_t3243;
                    U64 _t3244 = 6;
                    (void)_t3244;
                    Array *_va57 = Array_new(_t3242, &(U64){_t3243}, &(U64){_t3244});
                    (void)_va57;
                    Str_delete(_t3242, &(Bool){1});
                    ;
                    ;
                    U64 _t3245 = 0;
                    (void)_t3245;
                    Str *_t3246 = Str_clone(&p->path);
                    (void)_t3246;
                    Array_set(_va57, &(U64){_t3245}, _t3246);
                    ;
                    U64 _t3247 = 1;
                    (void)_t3247;
                    Str *_t3248 = Str_lit(":", 1ULL);
                    (void)_t3248;
                    Array_set(_va57, &(U64){_t3247}, _t3248);
                    ;
                    U32 _t3249 = peek_line(p);
                    (void)_t3249;
                    U64 _t3250 = 2;
                    (void)_t3250;
                    Str *_t3251 = U32_to_str(&(U32){_t3249});
                    (void)_t3251;
                    ;
                    Array_set(_va57, &(U64){_t3250}, _t3251);
                    ;
                    U64 _t3252 = 3;
                    (void)_t3252;
                    Str *_t3253 = Str_lit(":", 1ULL);
                    (void)_t3253;
                    Array_set(_va57, &(U64){_t3252}, _t3253);
                    ;
                    U32 _t3254 = peek_col(p);
                    (void)_t3254;
                    U64 _t3255 = 4;
                    (void)_t3255;
                    Str *_t3256 = U32_to_str(&(U32){_t3254});
                    (void)_t3256;
                    ;
                    Array_set(_va57, &(U64){_t3255}, _t3256);
                    ;
                    U64 _t3257 = 5;
                    (void)_t3257;
                    Str *_t3258 = Str_lit(": kwargs parameter cannot be own/mut/shallow", 44ULL);
                    (void)_t3258;
                    Array_set(_va57, &(U64){_t3257}, _t3258);
                    ;
                    Str *_t3259 = Str_lit("src/self/parser.til:182:27", 26ULL);
                    (void)_t3259;
                    panic(_t3259, _va57);
                    Str_delete(_t3259, &(Bool){1});
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
                Bool _t3279; { Bool *_hp = (Bool *)I32_neq(&fd->kwargs_index, &(I32){_t3278}); _t3279 = *_hp; free(_hp); }
                (void)_t3279;
                ;
                if (_t3279) {
                    Str *_t3260 = Str_lit("Str", 3ULL);
                    (void)_t3260;
                    U64 _t3261; { U64 *_hp = (U64 *)Str_size(); _t3261 = *_hp; free(_hp); }
                    (void)_t3261;
                    U64 _t3262 = 1;
                    (void)_t3262;
                    Array *_va58 = Array_new(_t3260, &(U64){_t3261}, &(U64){_t3262});
                    (void)_va58;
                    Str_delete(_t3260, &(Bool){1});
                    ;
                    ;
                    U64 _t3263 = 0;
                    (void)_t3263;
                    Str *_t3264 = Str_lit("only one kwargs parameter is allowed", 36ULL);
                    (void)_t3264;
                    Array_set(_va58, &(U64){_t3263}, _t3264);
                    ;
                    Str *_t3265 = Str_lit("src/self/parser.til:186:27", 26ULL);
                    (void)_t3265;
                    panic(_t3265, _va58);
                    Str_delete(_t3265, &(Bool){1});
                }
                ;
                I64 _t3280 = 0;
                (void)_t3280;
                I64 _t3281 = 1;
                (void)_t3281;
                I64 _t3282 = I64_sub(_t3280, _t3281);
                (void)_t3282;
                ;
                ;
                I32 _t3283 = I64_to_i32(_t3282);
                (void)_t3283;
                ;
                Bool _t3284; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3283}); _t3284 = *_hp; free(_hp); }
                (void)_t3284;
                ;
                if (_t3284) {
                    Str *_t3266 = Str_lit("Str", 3ULL);
                    (void)_t3266;
                    U64 _t3267; { U64 *_hp = (U64 *)Str_size(); _t3267 = *_hp; free(_hp); }
                    (void)_t3267;
                    U64 _t3268 = 1;
                    (void)_t3268;
                    Array *_va59 = Array_new(_t3266, &(U64){_t3267}, &(U64){_t3268});
                    (void)_va59;
                    Str_delete(_t3266, &(Bool){1});
                    ;
                    ;
                    U64 _t3269 = 0;
                    (void)_t3269;
                    Str *_t3270 = Str_lit("cannot combine variadic and kwargs in the same function", 55ULL);
                    (void)_t3270;
                    Array_set(_va59, &(U64){_t3269}, _t3270);
                    ;
                    Str *_t3271 = Str_lit("src/self/parser.til:189:27", 26ULL);
                    (void)_t3271;
                    panic(_t3271, _va59);
                    Str_delete(_t3271, &(Bool){1});
                }
                ;
                U64 _t3285; { U64 *_hp = (U64 *)Vec_len(&fd->param_names); _t3285 = *_hp; free(_hp); }
                (void)_t3285;
                I64 _t3286 = U64_to_i64(_t3285);
                (void)_t3286;
                ;
                I32 _t3287 = I64_to_i32(_t3286);
                (void)_t3287;
                ;
                fd->kwargs_index = _t3287;
                ;
                Bool _t3288 = 1;
                (void)_t3288;
                is_own = _t3288;
                ;
                nm = Str_clone(pname);
                tp = Str_lit("Map", 3ULL);
            } else {
                Bool _t3334 = check(p, TokenType_DotDot());
                (void)_t3334;
                if (_t3334) {
                    Token *_t3319 = advance(p);
                    (void)_t3319;
                    if (is_own) {
                        Str *_t3289 = Str_lit("Str", 3ULL);
                        (void)_t3289;
                        U64 _t3290; { U64 *_hp = (U64 *)Str_size(); _t3290 = *_hp; free(_hp); }
                        (void)_t3290;
                        U64 _t3291 = 1;
                        (void)_t3291;
                        Array *_va60 = Array_new(_t3289, &(U64){_t3290}, &(U64){_t3291});
                        (void)_va60;
                        Str_delete(_t3289, &(Bool){1});
                        ;
                        ;
                        U64 _t3292 = 0;
                        (void)_t3292;
                        Str *_t3293 = Str_lit("variadic param cannot be 'own'", 30ULL);
                        (void)_t3293;
                        Array_set(_va60, &(U64){_t3292}, _t3293);
                        ;
                        Str *_t3294 = Str_lit("src/self/parser.til:197:35", 26ULL);
                        (void)_t3294;
                        panic(_t3294, _va60);
                        Str_delete(_t3294, &(Bool){1});
                    }
                    if (is_mut) {
                        Str *_t3295 = Str_lit("Str", 3ULL);
                        (void)_t3295;
                        U64 _t3296; { U64 *_hp = (U64 *)Str_size(); _t3296 = *_hp; free(_hp); }
                        (void)_t3296;
                        U64 _t3297 = 1;
                        (void)_t3297;
                        Array *_va61 = Array_new(_t3295, &(U64){_t3296}, &(U64){_t3297});
                        (void)_va61;
                        Str_delete(_t3295, &(Bool){1});
                        ;
                        ;
                        U64 _t3298 = 0;
                        (void)_t3298;
                        Str *_t3299 = Str_lit("variadic param cannot be 'mut'", 30ULL);
                        (void)_t3299;
                        Array_set(_va61, &(U64){_t3298}, _t3299);
                        ;
                        Str *_t3300 = Str_lit("src/self/parser.til:198:35", 26ULL);
                        (void)_t3300;
                        panic(_t3300, _va61);
                        Str_delete(_t3300, &(Bool){1});
                    }
                    if (is_shallow) {
                        Str *_t3301 = Str_lit("Str", 3ULL);
                        (void)_t3301;
                        U64 _t3302; { U64 *_hp = (U64 *)Str_size(); _t3302 = *_hp; free(_hp); }
                        (void)_t3302;
                        U64 _t3303 = 1;
                        (void)_t3303;
                        Array *_va62 = Array_new(_t3301, &(U64){_t3302}, &(U64){_t3303});
                        (void)_va62;
                        Str_delete(_t3301, &(Bool){1});
                        ;
                        ;
                        U64 _t3304 = 0;
                        (void)_t3304;
                        Str *_t3305 = Str_lit("variadic param cannot be 'shallow'", 34ULL);
                        (void)_t3305;
                        Array_set(_va62, &(U64){_t3304}, _t3305);
                        ;
                        Str *_t3306 = Str_lit("src/self/parser.til:199:39", 26ULL);
                        (void)_t3306;
                        panic(_t3306, _va62);
                        Str_delete(_t3306, &(Bool){1});
                    }
                    I64 _t3320 = 0;
                    (void)_t3320;
                    I64 _t3321 = 1;
                    (void)_t3321;
                    I64 _t3322 = I64_sub(_t3320, _t3321);
                    (void)_t3322;
                    ;
                    ;
                    I32 _t3323 = I64_to_i32(_t3322);
                    (void)_t3323;
                    ;
                    Bool _t3324; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3323}); _t3324 = *_hp; free(_hp); }
                    (void)_t3324;
                    ;
                    if (_t3324) {
                        Str *_t3307 = Str_lit("Str", 3ULL);
                        (void)_t3307;
                        U64 _t3308; { U64 *_hp = (U64 *)Str_size(); _t3308 = *_hp; free(_hp); }
                        (void)_t3308;
                        U64 _t3309 = 1;
                        (void)_t3309;
                        Array *_va63 = Array_new(_t3307, &(U64){_t3308}, &(U64){_t3309});
                        (void)_va63;
                        Str_delete(_t3307, &(Bool){1});
                        ;
                        ;
                        U64 _t3310 = 0;
                        (void)_t3310;
                        Str *_t3311 = Str_lit("only one variadic param allowed", 31ULL);
                        (void)_t3311;
                        Array_set(_va63, &(U64){_t3310}, _t3311);
                        ;
                        Str *_t3312 = Str_lit("src/self/parser.til:200:69", 26ULL);
                        (void)_t3312;
                        panic(_t3312, _va63);
                        Str_delete(_t3312, &(Bool){1});
                    }
                    ;
                    I64 _t3325 = 0;
                    (void)_t3325;
                    I64 _t3326 = 1;
                    (void)_t3326;
                    I64 _t3327 = I64_sub(_t3325, _t3326);
                    (void)_t3327;
                    ;
                    ;
                    I32 _t3328 = I64_to_i32(_t3327);
                    (void)_t3328;
                    ;
                    Bool _t3329; { Bool *_hp = (Bool *)I32_neq(&fd->kwargs_index, &(I32){_t3328}); _t3329 = *_hp; free(_hp); }
                    (void)_t3329;
                    ;
                    if (_t3329) {
                        Str *_t3313 = Str_lit("Str", 3ULL);
                        (void)_t3313;
                        U64 _t3314; { U64 *_hp = (U64 *)Str_size(); _t3314 = *_hp; free(_hp); }
                        (void)_t3314;
                        U64 _t3315 = 1;
                        (void)_t3315;
                        Array *_va64 = Array_new(_t3313, &(U64){_t3314}, &(U64){_t3315});
                        (void)_va64;
                        Str_delete(_t3313, &(Bool){1});
                        ;
                        ;
                        U64 _t3316 = 0;
                        (void)_t3316;
                        Str *_t3317 = Str_lit("cannot combine variadic and kwargs in the same function", 55ULL);
                        (void)_t3317;
                        Array_set(_va64, &(U64){_t3316}, _t3317);
                        ;
                        Str *_t3318 = Str_lit("src/self/parser.til:202:27", 26ULL);
                        (void)_t3318;
                        panic(_t3318, _va64);
                        Str_delete(_t3318, &(Bool){1});
                    }
                    ;
                    U64 _t3330; { U64 *_hp = (U64 *)Vec_len(&fd->param_names); _t3330 = *_hp; free(_hp); }
                    (void)_t3330;
                    I64 _t3331 = U64_to_i64(_t3330);
                    (void)_t3331;
                    ;
                    I32 _t3332 = I64_to_i32(_t3331);
                    (void)_t3332;
                    ;
                    fd->variadic_index = _t3332;
                    ;
                    Bool _t3333 = 1;
                    (void)_t3333;
                    is_variadic = _t3333;
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
        Str *_t3361 = Str_lit("Fn", 2ULL);
        (void)_t3361;
        Bool _t3362; { Bool *_hp = (Bool *)Str_eq(tp, _t3361); _t3362 = *_hp; free(_hp); }
        (void)_t3362;
        Str_delete(_t3361, &(Bool){1});
        if (_t3362) {
            U32 _t3337 = peek_line(p);
            (void)_t3337;
            U32 _t3338 = peek_col(p);
            (void)_t3338;
            Str *syn_name = parse_fn_signature(p, _t3337, _t3338);
            (void)syn_name;
            ;
            ;
            U64 _t3339; { U64 *_hp = (U64 *)Str_len(syn_name); _t3339 = *_hp; free(_hp); }
            (void)_t3339;
            U64 _t3340 = 0;
            (void)_t3340;
            Bool _t3341; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3339}, &(U64){_t3340}); _t3341 = *_hp; free(_hp); }
            (void)_t3341;
            ;
            ;
            if (_t3341) {
                tp = Str_clone(syn_name);
            }
            ;
            Str_delete(syn_name, &(Bool){1});
        }
        ;
        Bool has_default = 0;
        (void)has_default;
        Bool _t3363 = check(p, TokenType_Eq());
        (void)_t3363;
        if (_t3363) {
            Token *_t3342 = advance(p);
            (void)_t3342;
            Expr *def_expr = parse_expression(p);
            (void)def_expr;
            Str *_t3343 = Str_clone(nm);
            (void)_t3343;
            Map_set(&fd->param_defaults, _t3343, def_expr);
            Bool _t3344 = 1;
            (void)_t3344;
            has_default = _t3344;
            ;
        }
        ;
        I64 _t3364 = 0;
        (void)_t3364;
        I64 _t3365 = 1;
        (void)_t3365;
        I64 _t3366 = I64_sub(_t3364, _t3365);
        (void)_t3366;
        ;
        ;
        I32 _t3367 = I64_to_i32(_t3366);
        (void)_t3367;
        ;
        Bool _t3368; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3367}); _t3368 = *_hp; free(_hp); }
        (void)_t3368;
        ;
        Bool _t3369 = Bool_not(is_variadic);
        (void)_t3369;
        ;
        Bool _t3370 = Bool_and(_t3368, _t3369);
        (void)_t3370;
        ;
        ;
        Bool _t3371 = Bool_not(has_default);
        (void)_t3371;
        ;
        Bool _t3372 = Bool_and(_t3370, _t3371);
        (void)_t3372;
        ;
        ;
        if (_t3372) {
            Str *_t3345 = Str_lit("Str", 3ULL);
            (void)_t3345;
            U64 _t3346; { U64 *_hp = (U64 *)Str_size(); _t3346 = *_hp; free(_hp); }
            (void)_t3346;
            U64 _t3347 = 1;
            (void)_t3347;
            Array *_va65 = Array_new(_t3345, &(U64){_t3346}, &(U64){_t3347});
            (void)_va65;
            Str_delete(_t3345, &(Bool){1});
            ;
            ;
            U64 _t3348 = 0;
            (void)_t3348;
            Str *_t3349 = Str_lit("positional param not allowed after variadic", 43ULL);
            (void)_t3349;
            Array_set(_va65, &(U64){_t3348}, _t3349);
            ;
            Str *_t3350 = Str_lit("src/self/parser.til:229:19", 26ULL);
            (void)_t3350;
            panic(_t3350, _va65);
            Str_delete(_t3350, &(Bool){1});
        }
        ;
        Vec_push(&fd->param_names, nm);
        Vec_push(&fd->param_types, tp);
        Vec_push(&fd->param_muts, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = is_mut; _oa; }));
        Vec_push(&fd->param_owns, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = is_own; _oa; }));
        Vec_push(&fd->param_shallows, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = is_shallow; _oa; }));
        Bool _t3373 = check(p, TokenType_Comma());
        (void)_t3373;
        if (_t3373) {
            Token *_t3351 = advance(p);
            (void)_t3351;
        }
        ;
    }
    Token *_t3434 = expect_token(p, TokenType_RParen());
    (void)_t3434;
    Bool _t3435 = check(p, TokenType_KwReturns());
    (void)_t3435;
    if (_t3435) {
        Token *_t3379 = advance(p);
        (void)_t3379;
        Bool _t3380 = check(p, TokenType_KwRef());
        (void)_t3380;
        if (_t3380) {
            Token *_t3374 = advance(p);
            (void)_t3374;
            Bool _t3375 = 1;
            (void)_t3375;
            fd->return_is_ref = _t3375;
            ;
        } else {
            Bool _t3378 = check(p, TokenType_KwShallow());
            (void)_t3378;
            if (_t3378) {
                Token *_t3376 = advance(p);
                (void)_t3376;
                Bool _t3377 = 1;
                (void)_t3377;
                fd->return_is_shallow = _t3377;
                ;
            }
            ;
        }
        ;
        Str_delete(&fd->return_type, &(Bool){0});
        { Str *_fa = expect_text(p, TokenType_Ident()); fd->return_type = *_fa; free(_fa); }
    }
    ;
    U64 _t3436; { U64 *_hp = (U64 *)Vec_len(&fd->param_names); _t3436 = *_hp; free(_hp); }
    (void)_t3436;
    I64 _t3437 = U64_to_i64(_t3436);
    (void)_t3437;
    ;
    U32 _t3438 = I64_to_u32(_t3437);
    (void)_t3438;
    ;
    fd->nparam = _t3438;
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
        Token *_t3381 = expect_token(p, TokenType_LBrace());
        (void)_t3381;
        Expr *_t3382 = parse_block(p);
        (void)_t3382;
        Expr_add_child(def, _t3382);
    } else {
        Bool _t3403; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Func()); _t3403 = *_hp; free(_hp); }
        (void)_t3403;
        Bool _t3404; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Proc()); _t3404 = *_hp; free(_hp); }
        (void)_t3404;
        Bool _t3405 = Bool_not(_t3403);
        (void)_t3405;
        ;
        Bool _t3406 = Bool_not(_t3404);
        (void)_t3406;
        ;
        Bool _t3407 = Bool_and(_t3405, _t3406);
        (void)_t3407;
        ;
        ;
        if (_t3407) {
            Str *_t3383 = Str_lit("Str", 3ULL);
            (void)_t3383;
            U64 _t3384; { U64 *_hp = (U64 *)Str_size(); _t3384 = *_hp; free(_hp); }
            (void)_t3384;
            U64 _t3385 = 8;
            (void)_t3385;
            Array *_va66 = Array_new(_t3383, &(U64){_t3384}, &(U64){_t3385});
            (void)_va66;
            Str_delete(_t3383, &(Bool){1});
            ;
            ;
            U64 _t3386 = 0;
            (void)_t3386;
            Str *_t3387 = Str_clone(&p->path);
            (void)_t3387;
            Array_set(_va66, &(U64){_t3386}, _t3387);
            ;
            U64 _t3388 = 1;
            (void)_t3388;
            Str *_t3389 = Str_lit(":", 1ULL);
            (void)_t3389;
            Array_set(_va66, &(U64){_t3388}, _t3389);
            ;
            U64 _t3390 = 2;
            (void)_t3390;
            Str *_t3391 = U32_to_str(&(U32){kw_line});
            (void)_t3391;
            Array_set(_va66, &(U64){_t3390}, _t3391);
            ;
            U64 _t3392 = 3;
            (void)_t3392;
            Str *_t3393 = Str_lit(":", 1ULL);
            (void)_t3393;
            Array_set(_va66, &(U64){_t3392}, _t3393);
            ;
            U64 _t3394 = 4;
            (void)_t3394;
            Str *_t3395 = U32_to_str(&(U32){kw_col});
            (void)_t3395;
            Array_set(_va66, &(U64){_t3394}, _t3395);
            ;
            U64 _t3396 = 5;
            (void)_t3396;
            Str *_t3397 = Str_lit(": ", 2ULL);
            (void)_t3397;
            Array_set(_va66, &(U64){_t3396}, _t3397);
            ;
            U64 _t3398 = 6;
            (void)_t3398;
            Str *_t3399 = func_type_name(ft);
            (void)_t3399;
            Array_set(_va66, &(U64){_t3398}, _t3399);
            ;
            U64 _t3400 = 7;
            (void)_t3400;
            Str *_t3401 = Str_lit(" requires a body", 16ULL);
            (void)_t3401;
            Array_set(_va66, &(U64){_t3400}, _t3401);
            ;
            Str *_t3402 = Str_lit("src/self/parser.til:263:19", 26ULL);
            (void)_t3402;
            panic(_t3402, _va66);
            Str_delete(_t3402, &(Bool){1});
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
        Str *_t3665 = Str_lit("src/self/parser.til:522:15", 26ULL);
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
    Bool _t3949 = check(p, TokenType_ColonEq());
    (void)_t3949;
    if (_t3949) {
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
    Bool _t3950 = check(p, TokenType_Colon());
    (void)_t3950;
    if (_t3950) {
        Token *_t3883 = advance(p);
        (void)_t3883;
        Bool _t3884 = check(p, TokenType_KwFunc());
        (void)_t3884;
        Bool _t3885 = check(p, TokenType_KwProc());
        (void)_t3885;
        Bool _t3886 = Bool_or(_t3884, _t3885);
        (void)_t3886;
        ;
        ;
        if (_t3886) {
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
        Str *_t3887 = Str_lit("Fn", 2ULL);
        (void)_t3887;
        Bool _t3888; { Bool *_hp = (Bool *)Str_eq(type_name, _t3887); _t3888 = *_hp; free(_hp); }
        (void)_t3888;
        Str_delete(_t3887, &(Bool){1});
        if (_t3888) {
            Str *syn_name = parse_fn_signature(p, t_line, t_col);
            (void)syn_name;
            U64 _t3795; { U64 *_hp = (U64 *)Str_len(syn_name); _t3795 = *_hp; free(_hp); }
            (void)_t3795;
            U64 _t3796 = 0;
            (void)_t3796;
            Bool _t3797; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3795}, &(U64){_t3796}); _t3797 = *_hp; free(_hp); }
            (void)_t3797;
            ;
            ;
            if (_t3797) {
                type_name = Str_clone(syn_name);
            }
            ;
            Str_delete(syn_name, &(Bool){1});
        }
        ;
        Token *_t3889 = expect_token(p, TokenType_Eq());
        (void)_t3889;
        Bool _t3890 = check(p, TokenType_LParen());
        (void)_t3890;
        if (_t3890) {
            U64 saved = p->pos;
            (void)saved;
            Token *_t3879 = advance(p);
            (void)_t3879;
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
            Bool _t3880 = check(p, TokenType_RParen());
            (void)_t3880;
            Bool _t3881 = Bool_and(is_fsf, _t3880);
            (void)_t3881;
            ;
            if (_t3881) {
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
            U64 _t3882 = U64_clone(&(U64){saved});
            (void)_t3882;
            ;
            p->pos = _t3882;
            ;
            if (is_fsf) {
                Token *_t3831 = expect_token(p, TokenType_LParen());
                (void)_t3831;
                Str *_t3832 = Str_lit("Str", 3ULL);
                (void)_t3832;
                U64 _t3833; { U64 *_hp = (U64 *)Str_size(); _t3833 = *_hp; free(_hp); }
                (void)_t3833;
                Vec *pnames = Vec_new(_t3832, &(U64){_t3833});
                (void)pnames;
                Str_delete(_t3832, &(Bool){1});
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
                Token *_t3834 = expect_token(p, TokenType_RParen());
                (void)_t3834;
                Token *_t3835 = expect_token(p, TokenType_LBrace());
                (void)_t3835;
                Expr *body = parse_block(p);
                (void)body;
                Str *_t3836 = Str_lit("Str", 3ULL);
                (void)_t3836;
                U64 _t3837; { U64 *_hp = (U64 *)Str_size(); _t3837 = *_hp; free(_hp); }
                (void)_t3837;
                Str *_t3838 = Str_lit("Str", 3ULL);
                (void)_t3838;
                U64 _t3839; { U64 *_hp = (U64 *)Str_size(); _t3839 = *_hp; free(_hp); }
                (void)_t3839;
                Str *_t3840 = Str_lit("Bool", 4ULL);
                (void)_t3840;
                U64 _t3841; { U64 *_hp = (U64 *)Bool_size(); _t3841 = *_hp; free(_hp); }
                (void)_t3841;
                Str *_t3842 = Str_lit("Bool", 4ULL);
                (void)_t3842;
                U64 _t3843; { U64 *_hp = (U64 *)Bool_size(); _t3843 = *_hp; free(_hp); }
                (void)_t3843;
                Str *_t3844 = Str_lit("Bool", 4ULL);
                (void)_t3844;
                U64 _t3845; { U64 *_hp = (U64 *)Bool_size(); _t3845 = *_hp; free(_hp); }
                (void)_t3845;
                Str *_t3846 = Str_lit("Str", 3ULL);
                (void)_t3846;
                U64 _t3847; { U64 *_hp = (U64 *)Str_size(); _t3847 = *_hp; free(_hp); }
                (void)_t3847;
                Str *_t3848 = Str_lit("Expr", 4ULL);
                (void)_t3848;
                U64 _t3849; { U64 *_hp = (U64 *)Expr_size(); _t3849 = *_hp; free(_hp); }
                (void)_t3849;
                I64 _t3850 = 0;
                (void)_t3850;
                I64 _t3851 = 1;
                (void)_t3851;
                I64 _t3852 = I64_sub(_t3850, _t3851);
                (void)_t3852;
                ;
                ;
                I64 _t3853 = 0;
                (void)_t3853;
                I64 _t3854 = 1;
                (void)_t3854;
                I64 _t3855 = I64_sub(_t3853, _t3854);
                (void)_t3855;
                ;
                ;
                U32 _t3856 = 0;
                (void)_t3856;
                I32 _t3857 = I64_to_i32(_t3852);
                (void)_t3857;
                ;
                I32 _t3858 = I64_to_i32(_t3855);
                (void)_t3858;
                ;
                Bool _t3859 = 0;
                (void)_t3859;
                Bool _t3860 = 0;
                (void)_t3860;
                FunctionDef *ffd = malloc(sizeof(FunctionDef));
                { FuncType *_ca = FuncType_clone(FuncType_Func()); ffd->func_type = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3836, &(U64){_t3837}); ffd->param_names = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3838, &(U64){_t3839}); ffd->param_types = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3840, &(U64){_t3841}); ffd->param_muts = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3842, &(U64){_t3843}); ffd->param_owns = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3844, &(U64){_t3845}); ffd->param_shallows = *_ca; free(_ca); }
                ffd->nparam = _t3856;
                { Map *_ca = Map_new(_t3846, &(U64){_t3847}, _t3848, &(U64){_t3849}); ffd->param_defaults = *_ca; free(_ca); }
                { Str *_ca = Str_clone(Str_lit("", 0ULL)); ffd->return_type = *_ca; free(_ca); }
                ffd->variadic_index = _t3857;
                ffd->kwargs_index = _t3858;
                ffd->return_is_ref = _t3859;
                ffd->return_is_shallow = _t3860;
                (void)ffd;
                Str_delete(_t3836, &(Bool){1});
                ;
                Str_delete(_t3838, &(Bool){1});
                ;
                Str_delete(_t3840, &(Bool){1});
                ;
                Str_delete(_t3842, &(Bool){1});
                ;
                Str_delete(_t3844, &(Bool){1});
                ;
                Str_delete(_t3846, &(Bool){1});
                ;
                Str_delete(_t3848, &(Bool){1});
                ;
                ;
                ;
                ;
                ;
                ;
                FuncType_delete(&ffd->func_type, &(Bool){0});
                { FuncType *_fa = FuncType_clone(FuncType_Func()); ffd->func_type = *_fa; free(_fa); }
                I64 _t3861 = 0;
                (void)_t3861;
                I64 _t3862 = 1;
                (void)_t3862;
                I64 _t3863 = I64_sub(_t3861, _t3862);
                (void)_t3863;
                ;
                ;
                I32 _t3864 = I64_to_i32(_t3863);
                (void)_t3864;
                ;
                ffd->variadic_index = _t3864;
                ;
                I64 _t3865 = 0;
                (void)_t3865;
                I64 _t3866 = 1;
                (void)_t3866;
                I64 _t3867 = I64_sub(_t3865, _t3866);
                (void)_t3867;
                ;
                ;
                I32 _t3868 = I64_to_i32(_t3867);
                (void)_t3868;
                ;
                ffd->kwargs_index = _t3868;
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
                    }
                    ;
                }
                Vec_delete(&ffd->param_names, &(Bool){0});
                { Vec *_fa = Vec_clone(pnames); ffd->param_names = *_fa; free(_fa); }
                Vec_delete(pnames, &(Bool){1});
                I64 _t3869 = U64_to_i64(np);
                (void)_t3869;
                ;
                U32 _t3870 = I64_to_u32(_t3869);
                (void)_t3870;
                ;
                ffd->nparam = _t3870;
                ;
                ExprData *_t3871 = ExprData_FuncDef(ffd);
                (void)_t3871;
                FunctionDef_delete(ffd, &(Bool){1});
                Expr *fdef = Expr_new(_t3871, t_line, t_col, &p->path);
                (void)fdef;
                ExprData_delete(_t3871, &(Bool){1});
                Expr_add_child(fdef, body);
                Bool _t3872 = Bool_clone(&(Bool){is_mut});
                (void)_t3872;
                Bool _t3873 = 0;
                (void)_t3873;
                Bool _t3874 = 0;
                (void)_t3874;
                Bool _t3875 = Bool_clone(&(Bool){is_own});
                (void)_t3875;
                I32 _t3876 = 0;
                (void)_t3876;
                I32 _t3877 = 0;
                (void)_t3877;
                Declaration *dd = malloc(sizeof(Declaration));
                { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
                { Str *_ca = Str_clone(type_name); dd->explicit_type = *_ca; free(_ca); }
                dd->is_mut = _t3872;
                dd->is_namespace = _t3873;
                dd->is_ref = _t3874;
                dd->is_own = _t3875;
                dd->field_offset = _t3876;
                dd->field_size = _t3877;
                dd->field_struct_def = NULL;
                dd->fn_sig = NULL;
                (void)dd;
                ;
                ;
                ;
                ;
                ;
                ;
                ExprData *_t3878 = ExprData_Decl(dd);
                (void)_t3878;
                Declaration_delete(dd, &(Bool){1});
                Expr *decl = Expr_new(_t3878, t_line, t_col, &p->path);
                (void)decl;
                ExprData_delete(_t3878, &(Bool){1});
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
        Bool _t3891 = Bool_clone(&(Bool){is_mut});
        (void)_t3891;
        Bool _t3892 = 0;
        (void)_t3892;
        Bool _t3893 = 0;
        (void)_t3893;
        Bool _t3894 = Bool_clone(&(Bool){is_own});
        (void)_t3894;
        I32 _t3895 = 0;
        (void)_t3895;
        I32 _t3896 = 0;
        (void)_t3896;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(type_name); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3891;
        dd->is_namespace = _t3892;
        dd->is_ref = _t3893;
        dd->is_own = _t3894;
        dd->field_offset = _t3895;
        dd->field_size = _t3896;
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
        ExprData *_t3897 = ExprData_Decl(dd);
        (void)_t3897;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3897, t_line, t_col, &p->path);
        (void)decl;
        ExprData_delete(_t3897, &(Bool){1});
        Expr *_t3898 = parse_expression(p);
        (void)_t3898;
        Expr_add_child(decl, _t3898);
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
            Bool _wcond3899 = check(p, TokenType_Dot());
            (void)_wcond3899;
            if (_wcond3899) {
            } else {
                ;
                break;
            }
            ;
            Token *_t3903 = advance(p);
            (void)_t3903;
            U32 _t3904 = peek_line(p);
            (void)_t3904;
            last_line = _t3904;
            ;
            U32 _t3905 = peek_col(p);
            (void)_t3905;
            last_col = _t3905;
            ;
            last_field = expect_text(p, TokenType_Ident());
            Bool _t3906 = check(p, TokenType_Dot());
            (void)_t3906;
            if (_t3906) {
                Str *_t3900 = Str_clone(last_field);
                (void)_t3900;
                ExprData *_t3901 = ExprData_FieldAccess(_t3900);
                (void)_t3901;
                Str_delete(_t3900, &(Bool){1});
                Expr *access = Expr_new(_t3901, last_line, last_col, &p->path);
                (void)access;
                ExprData_delete(_t3901, &(Bool){1});
                Expr *_t3902 = Expr_clone(obj);
                (void)_t3902;
                Expr_add_child(access, _t3902);
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
                Bool _wcond3907 = Bool_and(_t3927, _t3928);
                (void)_wcond3907;
                ;
                ;
                if (_wcond3907) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3929 = check(p, TokenType_Ident());
                (void)_t3929;
                if (_t3929) {
                    U64 _t3918 = 1;
                    (void)_t3918;
                    U64 _t3919 = U64_add(p->pos, _t3918);
                    (void)_t3919;
                    ;
                    U64 _t3920; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3920 = *_hp; free(_hp); }
                    (void)_t3920;
                    Bool _t3921; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3919}, &(U64){_t3920}); _t3921 = *_hp; free(_hp); }
                    (void)_t3921;
                    ;
                    ;
                    if (_t3921) {
                        U64 _t3913 = 1;
                        (void)_t3913;
                        U64 _t3914 = U64_add(p->pos, _t3913);
                        (void)_t3914;
                        ;
                        I64 _t3915 = U64_to_i64(_t3914);
                        (void)_t3915;
                        ;
                        U64 *_t3916 = malloc(sizeof(U64)); *_t3916 = I64_to_u64(_t3915);
                        (void)_t3916;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3916);
                        (void)nt;
                        Bool _t3917; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3917 = *_hp; free(_hp); }
                        (void)_t3917;
                        U64_delete(_t3916, &(Bool){1});
                        if (_t3917) {
                            U32 na_line = peek_line(p);
                            (void)na_line;
                            U32 na_col = peek_col(p);
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3909 = advance(p);
                            (void)_t3909;
                            ExprData *_t3910 = ExprData_NamedArg(aname);
                            (void)_t3910;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3910, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3910, &(Bool){1});
                            ;
                            ;
                            Expr *_t3911 = parse_expression(p);
                            (void)_t3911;
                            Expr_add_child(na, _t3911);
                            Expr_add_child(mcall, na);
                            Bool _t3912 = check(p, TokenType_Comma());
                            (void)_t3912;
                            if (_t3912) {
                                Token *_t3908 = advance(p);
                                (void)_t3908;
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
    Str *_t3973 = Str_lit("src/self/parser.til:786:11", 26ULL);
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
    U32 t_line = peek_line(p);
    (void)t_line;
    U32 t_col = peek_col(p);
    (void)t_col;
    Token *t = peek(p);
    (void)t;
    Bool _t4114; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t4114 = *_hp; free(_hp); }
    (void)_t4114;
    if (_t4114) {
        Bool _t3977 = 0;
        (void)_t3977;
        Bool _t3978 = 0;
        (void)_t3978;
        Expr *_t3979 = parse_statement_ident(p, _t3977, _t3978);
        (void)_t3979;
        ;
        ;
        ;
        ;
        ;
        return _t3979;
    }
    ;
    Bool _t4115; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwRef()); _t4115 = *_hp; free(_hp); }
    (void)_t4115;
    if (_t4115) {
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
        U32 i_line = peek_line(p);
        (void)i_line;
        U32 i_col = peek_col(p);
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
        } else {
            Token *_t3985 = expect_token(p, TokenType_ColonEq());
            (void)_t3985;
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
    Bool _t4116; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMut()); _t4116 = *_hp; free(_hp); }
    (void)_t4116;
    if (_t4116) {
        Token *_t3997 = advance(p);
        (void)_t3997;
        Bool _t3998 = 1;
        (void)_t3998;
        Bool _t3999 = 0;
        (void)_t3999;
        Expr *_t4000 = parse_statement_ident(p, _t3998, _t3999);
        (void)_t4000;
        ;
        ;
        ;
        ;
        ;
        return _t4000;
    }
    ;
    Bool _t4117; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwReturn()); _t4117 = *_hp; free(_hp); }
    (void)_t4117;
    if (_t4117) {
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
    Bool _t4118; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwIf()); _t4118 = *_hp; free(_hp); }
    (void)_t4118;
    if (_t4118) {
        Token *_t4015 = advance(p);
        (void)_t4015;
        Expr *node = Expr_new(ExprData_If(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t4016 = parse_expression(p);
        (void)_t4016;
        Expr_add_child(node, _t4016);
        Token *_t4017 = expect_token(p, TokenType_LBrace());
        (void)_t4017;
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
                U32 _t4008 = peek_line(p);
                (void)_t4008;
                U32 _t4009 = peek_col(p);
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
                Expr *_t4012 = parse_block(p);
                (void)_t4012;
                Expr_add_child(node, _t4012);
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
    Bool _t4119; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t4119 = *_hp; free(_hp); }
    (void)_t4119;
    Bool _t4120; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t4120 = *_hp; free(_hp); }
    (void)_t4120;
    Bool _t4121 = Bool_or(_t4119, _t4120);
    (void)_t4121;
    ;
    ;
    Bool _t4122; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t4122 = *_hp; free(_hp); }
    (void)_t4122;
    Bool _t4123 = Bool_or(_t4121, _t4122);
    (void)_t4123;
    ;
    ;
    Bool _t4124; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t4124 = *_hp; free(_hp); }
    (void)_t4124;
    Bool _t4125 = Bool_or(_t4123, _t4124);
    (void)_t4125;
    ;
    ;
    Bool _t4126; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwNull()); _t4126 = *_hp; free(_hp); }
    (void)_t4126;
    Bool _t4127 = Bool_or(_t4125, _t4126);
    (void)_t4127;
    ;
    ;
    if (_t4127) {
        Expr *_t4020 = parse_expression(p);
        (void)_t4020;
        ;
        ;
        ;
        return _t4020;
    }
    ;
    Bool _t4128; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t4128 = *_hp; free(_hp); }
    (void)_t4128;
    if (_t4128) {
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
    Bool _t4129; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwWhile()); _t4129 = *_hp; free(_hp); }
    (void)_t4129;
    if (_t4129) {
        Token *_t4023 = advance(p);
        (void)_t4023;
        Expr *node = Expr_new(ExprData_While(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t4024 = parse_expression(p);
        (void)_t4024;
        Expr_add_child(node, _t4024);
        Token *_t4025 = expect_token(p, TokenType_LBrace());
        (void)_t4025;
        Expr *_t4026 = parse_block(p);
        (void)_t4026;
        Expr_add_child(node, _t4026);
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4130; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFor()); _t4130 = *_hp; free(_hp); }
    (void)_t4130;
    if (_t4130) {
        Token *_t4028 = advance(p);
        (void)_t4028;
        U32 i_line = peek_line(p);
        (void)i_line;
        U32 i_col = peek_col(p);
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
        Expr *_t4032 = parse_expression(p);
        (void)_t4032;
        Expr_add_child(node, _t4032);
        Token *_t4033 = expect_token(p, TokenType_LBrace());
        (void)_t4033;
        Expr *_t4034 = parse_block(p);
        (void)_t4034;
        Expr_add_child(node, _t4034);
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4131; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwSwitch()); _t4131 = *_hp; free(_hp); }
    (void)_t4131;
    if (_t4131) {
        Token *_t4058 = advance(p);
        (void)_t4058;
        Expr *node = Expr_new(ExprData_Switch(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t4059 = parse_expression(p);
        (void)_t4059;
        Expr_add_child(node, _t4059);
        Token *_t4060 = expect_token(p, TokenType_LBrace());
        (void)_t4060;
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
            U32 _t4051 = peek_line(p);
            (void)_t4051;
            U32 _t4052 = peek_col(p);
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
            U32 _t4056 = peek_line(p);
            (void)_t4056;
            U32 _t4057 = peek_col(p);
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
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4132; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwOwn()); _t4132 = *_hp; free(_hp); }
    (void)_t4132;
    if (_t4132) {
        Token *_t4103 = advance(p);
        (void)_t4103;
        Bool _t4104 = check(p, TokenType_Ident());
        (void)_t4104;
        Bool _t4105 = check(p, TokenType_KwMut());
        (void)_t4105;
        Bool _t4106 = Bool_or(_t4104, _t4105);
        (void)_t4106;
        ;
        ;
        if (_t4106) {
            Bool own_mut = 0;
            (void)own_mut;
            Bool _t4093 = check(p, TokenType_KwMut());
            (void)_t4093;
            if (_t4093) {
                Token *_t4062 = advance(p);
                (void)_t4062;
                Bool _t4063 = 1;
                (void)_t4063;
                own_mut = _t4063;
                ;
            }
            ;
            Bool _t4094 = check(p, TokenType_Ident());
            (void)_t4094;
            if (_t4094) {
                U64 _t4073 = 1;
                (void)_t4073;
                U64 _t4074 = U64_add(p->pos, _t4073);
                (void)_t4074;
                ;
                U64 _t4075; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t4075 = *_hp; free(_hp); }
                (void)_t4075;
                Bool _t4076; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4074}, &(U64){_t4075}); _t4076 = *_hp; free(_hp); }
                (void)_t4076;
                ;
                ;
                if (_t4076) {
                    U64 _t4066 = 1;
                    (void)_t4066;
                    U64 _t4067 = U64_add(p->pos, _t4066);
                    (void)_t4067;
                    ;
                    I64 _t4068 = U64_to_i64(_t4067);
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
                        Expr *_t4065 = parse_statement_ident(p, own_mut, _t4064);
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
                Str *_t4077 = Str_lit("Str", 3ULL);
                (void)_t4077;
                U64 _t4078; { U64 *_hp = (U64 *)Str_size(); _t4078 = *_hp; free(_hp); }
                (void)_t4078;
                U64 _t4079 = 6;
                (void)_t4079;
                Array *_va70 = Array_new(_t4077, &(U64){_t4078}, &(U64){_t4079});
                (void)_va70;
                Str_delete(_t4077, &(Bool){1});
                ;
                ;
                U64 _t4080 = 0;
                (void)_t4080;
                Str *_t4081 = Str_clone(&p->path);
                (void)_t4081;
                Array_set(_va70, &(U64){_t4080}, _t4081);
                ;
                U64 _t4082 = 1;
                (void)_t4082;
                Str *_t4083 = Str_lit(":", 1ULL);
                (void)_t4083;
                Array_set(_va70, &(U64){_t4082}, _t4083);
                ;
                U64 _t4084 = 2;
                (void)_t4084;
                Str *_t4085 = U32_to_str(&(U32){t_line});
                (void)_t4085;
                Array_set(_va70, &(U64){_t4084}, _t4085);
                ;
                U64 _t4086 = 3;
                (void)_t4086;
                Str *_t4087 = Str_lit(":", 1ULL);
                (void)_t4087;
                Array_set(_va70, &(U64){_t4086}, _t4087);
                ;
                U64 _t4088 = 4;
                (void)_t4088;
                Str *_t4089 = U32_to_str(&(U32){t_col});
                (void)_t4089;
                Array_set(_va70, &(U64){_t4088}, _t4089);
                ;
                U64 _t4090 = 5;
                (void)_t4090;
                Str *_t4091 = Str_lit(": expected identifier after 'own mut'", 37ULL);
                (void)_t4091;
                Array_set(_va70, &(U64){_t4090}, _t4091);
                ;
                Str *_t4092 = Str_lit("src/self/parser.til:920:23", 26ULL);
                (void)_t4092;
                panic(_t4092, _va70);
                Str_delete(_t4092, &(Bool){1});
            }
            ;
        }
        ;
        Expr *expr = parse_expression(p);
        (void)expr;
        I64 _t4107 = 0;
        (void)_t4107;
        I64 _t4108 = 1;
        (void)_t4108;
        I64 primary_idx = I64_sub(_t4107, _t4108);
        (void)primary_idx;
        ;
        ;
        ;
        Expr *cur = Expr_clone(expr);
        (void)cur;
        while (1) {
            U64 _t4096; { U64 *_hp = (U64 *)Vec_len(&cur->children); _t4096 = *_hp; free(_hp); }
            (void)_t4096;
            U64 _t4097 = 0;
            (void)_t4097;
            Bool _t4098; { Bool *_hp = (Bool *)ExprData_is_FCall(&cur->data); _t4098 = *_hp; free(_hp); }
            (void)_t4098;
            Bool _t4099; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(&cur->data); _t4099 = *_hp; free(_hp); }
            (void)_t4099;
            Bool _t4100; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4096}, &(U64){_t4097}); _t4100 = *_hp; free(_hp); }
            (void)_t4100;
            ;
            ;
            Bool _t4101 = Bool_or(_t4098, _t4099);
            (void)_t4101;
            ;
            ;
            Bool _wcond4095 = Bool_and(_t4100, _t4101);
            (void)_wcond4095;
            ;
            ;
            if (_wcond4095) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t4102 = malloc(sizeof(U64));
            *_t4102 = 0;
            (void)_t4102;
            Expr *ch = Vec_get(&cur->children, _t4102);
            (void)ch;
            cur = Expr_clone(ch);
            U64_delete(_t4102, &(Bool){1});
        }
        Bool _t4109 = 1;
        (void)_t4109;
        cur->is_own_arg = _t4109;
        ;
        Expr_delete(cur, &(Bool){1});
        ;
        ;
        ;
        ;
        return expr;
    }
    ;
    Bool _t4133; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwBreak()); _t4133 = *_hp; free(_hp); }
    (void)_t4133;
    if (_t4133) {
        Token *_t4110 = advance(p);
        (void)_t4110;
        Expr *_t4111 = Expr_new(ExprData_Break(), t_line, t_col, &p->path);
        (void)_t4111;
        ;
        ;
        ;
        return _t4111;
    }
    ;
    Bool _t4134; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwContinue()); _t4134 = *_hp; free(_hp); }
    (void)_t4134;
    if (_t4134) {
        Token *_t4112 = advance(p);
        (void)_t4112;
        Expr *_t4113 = Expr_new(ExprData_Continue(), t_line, t_col, &p->path);
        (void)_t4113;
        ;
        ;
        ;
        return _t4113;
    }
    ;
    Str *_t4135 = Str_lit("Str", 3ULL);
    (void)_t4135;
    U64 _t4136; { U64 *_hp = (U64 *)Str_size(); _t4136 = *_hp; free(_hp); }
    (void)_t4136;
    U64 _t4137 = 8;
    (void)_t4137;
    Array *_va71 = Array_new(_t4135, &(U64){_t4136}, &(U64){_t4137});
    (void)_va71;
    Str_delete(_t4135, &(Bool){1});
    ;
    ;
    U64 _t4138 = 0;
    (void)_t4138;
    Str *_t4139 = Str_clone(&p->path);
    (void)_t4139;
    Array_set(_va71, &(U64){_t4138}, _t4139);
    ;
    U64 _t4140 = 1;
    (void)_t4140;
    Str *_t4141 = Str_lit(":", 1ULL);
    (void)_t4141;
    Array_set(_va71, &(U64){_t4140}, _t4141);
    ;
    U64 _t4142 = 2;
    (void)_t4142;
    Str *_t4143 = U32_to_str(&(U32){t_line});
    (void)_t4143;
    ;
    Array_set(_va71, &(U64){_t4142}, _t4143);
    ;
    U64 _t4144 = 3;
    (void)_t4144;
    Str *_t4145 = Str_lit(":", 1ULL);
    (void)_t4145;
    Array_set(_va71, &(U64){_t4144}, _t4145);
    ;
    U64 _t4146 = 4;
    (void)_t4146;
    Str *_t4147 = U32_to_str(&(U32){t_col});
    (void)_t4147;
    ;
    Array_set(_va71, &(U64){_t4146}, _t4147);
    ;
    U64 _t4148 = 5;
    (void)_t4148;
    Str *_t4149 = Str_lit(": expected statement, found '", 29ULL);
    (void)_t4149;
    Array_set(_va71, &(U64){_t4148}, _t4149);
    ;
    U64 _t4150 = 6;
    (void)_t4150;
    Str *_t4151 = Str_clone(&t->text);
    (void)_t4151;
    Array_set(_va71, &(U64){_t4150}, _t4151);
    ;
    U64 _t4152 = 7;
    (void)_t4152;
    Str *_t4153 = Str_lit("'", 1ULL);
    (void)_t4153;
    Array_set(_va71, &(U64){_t4152}, _t4153);
    ;
    Str *_t4154 = Str_lit("src/self/parser.til:947:11", 26ULL);
    (void)_t4154;
    panic(_t4154, _va71);
    Str_delete(_t4154, &(Bool){1});
    U32 _t4155 = 0;
    (void)_t4155;
    U32 _t4156 = 0;
    (void)_t4156;
    Expr *_t4157 = Expr_new(ExprData_Body(), _t4155, _t4156, &p->path);
    (void)_t4157;
    ;
    ;
    return _t4157;
}

Expr * parse(Vec * tokens, Str * path, Str * mode_out) {
    (void)tokens;
    (void)path;
    (void)mode_out;
    Str *_t4181 = Str_lit("Expr", 4ULL);
    (void)_t4181;
    U64 _t4182; { U64 *_hp = (U64 *)Expr_size(); _t4182 = *_hp; free(_hp); }
    (void)_t4182;
    I64 _t4183 = 0;
    (void)_t4183;
    Parser *p = malloc(sizeof(Parser));
    { Vec *_ca = Vec_clone(tokens); p->tokens = *_ca; free(_ca); }
    p->pos = _t4183;
    { Str *_ca = Str_clone(path); p->path = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t4181, &(U64){_t4182}); p->fn_sig_decls = *_ca; free(_ca); }
    (void)p;
    Str_delete(_t4181, &(Bool){1});
    ;
    ;
    Bool _t4184 = check(p, TokenType_KwMode());
    (void)_t4184;
    if (_t4184) {
        Token *_t4162 = advance(p);
        (void)_t4162;
        Bool _t4163 = check(p, TokenType_Ident());
        (void)_t4163;
        Bool _t4164 = check(p, TokenType_KwTest());
        (void)_t4164;
        Bool _t4165 = Bool_or(_t4163, _t4164);
        (void)_t4165;
        ;
        ;
        if (_t4165) {
            Str *_t4158 = Str_clone(&peek(p)->text);
            (void)_t4158;
            U64 _t4159; { U64 *_hp = (U64 *)Str_size(); _t4159 = *_hp; free(_hp); }
            (void)_t4159;
            swap(mode_out, _t4158, _t4159);
            Str_delete(_t4158, &(Bool){1});
            ;
            Token *_t4160 = advance(p);
            (void)_t4160;
        } else {
            Token *_t4161 = expect_token(p, TokenType_Ident());
            (void)_t4161;
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
        Bool _t4167 = check(p, TokenType_Eof());
        (void)_t4167;
        Bool _wcond4166 = Bool_not(_t4167);
        (void)_wcond4166;
        ;
        if (_wcond4166) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t4168 = parse_statement(p);
        (void)_t4168;
        Expr_add_child(root, _t4168);
    }
    {
        U64 _fi4169 = 0;
        (void)_fi4169;
        while (1) {
            U64 _t4171 = 0;
            (void)_t4171;
            U64 _t4172; { U64 *_hp = (U64 *)Vec_len(&p->fn_sig_decls); _t4172 = *_hp; free(_hp); }
            (void)_t4172;
            Range *_t4173 = Range_new(_t4171, _t4172);
            (void)_t4173;
            ;
            ;
            U64 _t4174; { U64 *_hp = (U64 *)Range_len(_t4173); _t4174 = *_hp; free(_hp); }
            (void)_t4174;
            Range_delete(_t4173, &(Bool){1});
            Bool _wcond4170; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi4169}, &(U64){_t4174}); _wcond4170 = *_hp; free(_hp); }
            (void)_wcond4170;
            ;
            if (_wcond4170) {
            } else {
                ;
                break;
            }
            ;
            U64 _t4175 = 0;
            (void)_t4175;
            U64 _t4176; { U64 *_hp = (U64 *)Vec_len(&p->fn_sig_decls); _t4176 = *_hp; free(_hp); }
            (void)_t4176;
            Range *_t4177 = Range_new(_t4175, _t4176);
            (void)_t4177;
            ;
            ;
            U64 *i = Range_get(_t4177, _fi4169);
            (void)i;
            Range_delete(_t4177, &(Bool){1});
            U64 _t4178 = 1;
            (void)_t4178;
            U64 _t4179 = U64_add(_fi4169, _t4178);
            (void)_t4179;
            ;
            _fi4169 = _t4179;
            ;
            Expr *d = Vec_get(&p->fn_sig_decls, i);
            (void)d;
            Expr *_t4180 = Expr_clone(d);
            (void)_t4180;
            U64_delete(i, &(Bool){1});
            Expr_add_child(root, _t4180);
        }
        ;
    }
    Parser_delete(p, &(Bool){1});
    return root;
}

