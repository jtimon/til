#include "til_parser.h"

Parser * Parser_clone(Parser * self) {
    (void)self;
    U64 _t3047 = U64_clone(&self->pos);
    (void)_t3047;
    Parser *_t3048 = malloc(sizeof(Parser));
    { Vec *_ca = Vec_clone(&self->tokens); _t3048->tokens = *_ca; free(_ca); }
    _t3048->pos = _t3047;
    { Str *_ca = Str_clone(&self->path); _t3048->path = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->fn_sig_decls); _t3048->fn_sig_decls = *_ca; free(_ca); }
    (void)_t3048;
    ;
    return _t3048;
}

void Parser_delete(Parser * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t3049 = 0;
    (void)_t3049;
    Vec_delete(&self->tokens, &(Bool){_t3049});
    ;
    Bool _t3050 = 0;
    (void)_t3050;
    U64_delete(&self->pos, &(Bool){_t3050});
    ;
    Bool _t3051 = 0;
    (void)_t3051;
    Str_delete(&self->path, &(Bool){_t3051});
    ;
    Bool _t3052 = 0;
    (void)_t3052;
    Vec_delete(&self->fn_sig_decls, &(Bool){_t3052});
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
    I64 _t3054 = U64_to_i64(p->pos);
    (void)_t3054;
    U64 *_t3055 = malloc(sizeof(U64)); *_t3055 = I64_to_u64(_t3054);
    (void)_t3055;
    ;
    Token *t = Vec_get(&p->tokens, _t3055);
    (void)t;
    U64_delete(_t3055, &(Bool){1});
    return t;
}

Token * advance(Parser * p) {
    (void)p;
    I64 _t3058 = U64_to_i64(p->pos);
    (void)_t3058;
    U64 *_t3059 = malloc(sizeof(U64)); *_t3059 = I64_to_u64(_t3058);
    (void)_t3059;
    ;
    Token *t = Vec_get(&p->tokens, _t3059);
    (void)t;
    Bool _t3060; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Eof()); _t3060 = *_hp; free(_hp); }
    (void)_t3060;
    Bool _t3061 = Bool_not(_t3060);
    (void)_t3061;
    ;
    if (_t3061) {
        U64 _t3056 = 1;
        (void)_t3056;
        U64 _t3057 = U64_add(p->pos, _t3056);
        (void)_t3057;
        ;
        p->pos = _t3057;
        ;
    }
    ;
    U64_delete(_t3059, &(Bool){1});
    return t;
}

Bool check(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Bool _t3062; { Bool *_hp = (Bool *)TokenType_eq(&peek(p)->type, type); _t3062 = *_hp; free(_hp); }
    (void)_t3062;
    return _t3062;
}

Token * expect_token(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Token *t = peek(p);
    (void)t;
    Bool _t3087; { Bool *_hp = (Bool *)TokenType_eq(&t->type, type); _t3087 = *_hp; free(_hp); }
    (void)_t3087;
    Bool _t3088 = Bool_not(_t3087);
    (void)_t3088;
    ;
    if (_t3088) {
        Str *_t3063 = Str_lit("Str", 3ULL);
        (void)_t3063;
        U64 _t3064; { U64 *_hp = (U64 *)Str_size(); _t3064 = *_hp; free(_hp); }
        (void)_t3064;
        U64 _t3065 = 10;
        (void)_t3065;
        Array *_va54 = Array_new(_t3063, &(U64){_t3064}, &(U64){_t3065});
        (void)_va54;
        Str_delete(_t3063, &(Bool){1});
        ;
        ;
        U64 _t3066 = 0;
        (void)_t3066;
        Str *_t3067 = Str_clone(&p->path);
        (void)_t3067;
        Array_set(_va54, &(U64){_t3066}, _t3067);
        ;
        U64 _t3068 = 1;
        (void)_t3068;
        Str *_t3069 = Str_lit(":", 1ULL);
        (void)_t3069;
        Array_set(_va54, &(U64){_t3068}, _t3069);
        ;
        U64 _t3070 = 2;
        (void)_t3070;
        Str *_t3071 = U32_to_str(&t->line);
        (void)_t3071;
        Array_set(_va54, &(U64){_t3070}, _t3071);
        ;
        U64 _t3072 = 3;
        (void)_t3072;
        Str *_t3073 = Str_lit(":", 1ULL);
        (void)_t3073;
        Array_set(_va54, &(U64){_t3072}, _t3073);
        ;
        U64 _t3074 = 4;
        (void)_t3074;
        Str *_t3075 = U32_to_str(&t->col);
        (void)_t3075;
        Array_set(_va54, &(U64){_t3074}, _t3075);
        ;
        U64 _t3076 = 5;
        (void)_t3076;
        Str *_t3077 = Str_lit(": expected '", 12ULL);
        (void)_t3077;
        Array_set(_va54, &(U64){_t3076}, _t3077);
        ;
        U64 _t3078 = 6;
        (void)_t3078;
        Str *_t3079 = tok_name(type);
        (void)_t3079;
        Array_set(_va54, &(U64){_t3078}, _t3079);
        ;
        U64 _t3080 = 7;
        (void)_t3080;
        Str *_t3081 = Str_lit("', found '", 10ULL);
        (void)_t3081;
        Array_set(_va54, &(U64){_t3080}, _t3081);
        ;
        U64 _t3082 = 8;
        (void)_t3082;
        Str *_t3083 = Str_clone(&t->text);
        (void)_t3083;
        Array_set(_va54, &(U64){_t3082}, _t3083);
        ;
        U64 _t3084 = 9;
        (void)_t3084;
        Str *_t3085 = Str_lit("'", 1ULL);
        (void)_t3085;
        Array_set(_va54, &(U64){_t3084}, _t3085);
        ;
        Str *_t3086 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:34:15", 63ULL);
        (void)_t3086;
        panic(_t3086, _va54);
        Str_delete(_t3086, &(Bool){1});
    }
    ;
    Token *_t3089 = advance(p);
    (void)_t3089;
    return _t3089;
}

Str * expect_text(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Token *t = peek(p);
    (void)t;
    Bool _t3114; { Bool *_hp = (Bool *)TokenType_eq(&t->type, type); _t3114 = *_hp; free(_hp); }
    (void)_t3114;
    Bool _t3115 = Bool_not(_t3114);
    (void)_t3115;
    ;
    if (_t3115) {
        Str *_t3090 = Str_lit("Str", 3ULL);
        (void)_t3090;
        U64 _t3091; { U64 *_hp = (U64 *)Str_size(); _t3091 = *_hp; free(_hp); }
        (void)_t3091;
        U64 _t3092 = 10;
        (void)_t3092;
        Array *_va55 = Array_new(_t3090, &(U64){_t3091}, &(U64){_t3092});
        (void)_va55;
        Str_delete(_t3090, &(Bool){1});
        ;
        ;
        U64 _t3093 = 0;
        (void)_t3093;
        Str *_t3094 = Str_clone(&p->path);
        (void)_t3094;
        Array_set(_va55, &(U64){_t3093}, _t3094);
        ;
        U64 _t3095 = 1;
        (void)_t3095;
        Str *_t3096 = Str_lit(":", 1ULL);
        (void)_t3096;
        Array_set(_va55, &(U64){_t3095}, _t3096);
        ;
        U64 _t3097 = 2;
        (void)_t3097;
        Str *_t3098 = U32_to_str(&t->line);
        (void)_t3098;
        Array_set(_va55, &(U64){_t3097}, _t3098);
        ;
        U64 _t3099 = 3;
        (void)_t3099;
        Str *_t3100 = Str_lit(":", 1ULL);
        (void)_t3100;
        Array_set(_va55, &(U64){_t3099}, _t3100);
        ;
        U64 _t3101 = 4;
        (void)_t3101;
        Str *_t3102 = U32_to_str(&t->col);
        (void)_t3102;
        Array_set(_va55, &(U64){_t3101}, _t3102);
        ;
        U64 _t3103 = 5;
        (void)_t3103;
        Str *_t3104 = Str_lit(": expected '", 12ULL);
        (void)_t3104;
        Array_set(_va55, &(U64){_t3103}, _t3104);
        ;
        U64 _t3105 = 6;
        (void)_t3105;
        Str *_t3106 = tok_name(type);
        (void)_t3106;
        Array_set(_va55, &(U64){_t3105}, _t3106);
        ;
        U64 _t3107 = 7;
        (void)_t3107;
        Str *_t3108 = Str_lit("', found '", 10ULL);
        (void)_t3108;
        Array_set(_va55, &(U64){_t3107}, _t3108);
        ;
        U64 _t3109 = 8;
        (void)_t3109;
        Str *_t3110 = Str_clone(&t->text);
        (void)_t3110;
        Array_set(_va55, &(U64){_t3109}, _t3110);
        ;
        U64 _t3111 = 9;
        (void)_t3111;
        Str *_t3112 = Str_lit("'", 1ULL);
        (void)_t3112;
        Array_set(_va55, &(U64){_t3111}, _t3112);
        ;
        Str *_t3113 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:44:15", 63ULL);
        (void)_t3113;
        panic(_t3113, _va55);
        Str_delete(_t3113, &(Bool){1});
    }
    ;
    Str *text = Str_clone(&t->text);
    (void)text;
    Token *_t3116 = advance(p);
    (void)_t3116;
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
    Bool _t3158 = check(p, TokenType_LParen());
    (void)_t3158;
    Bool _t3159 = Bool_not(_t3158);
    (void)_t3159;
    ;
    if (_t3159) {
        Str *_t3117 = Str_lit("", 0ULL);
        (void)_t3117;
        ;
        return _t3117;
    }
    ;
    Token *_t3160 = advance(p);
    (void)_t3160;
    Str *_t3161 = Str_lit("Str", 3ULL);
    (void)_t3161;
    U64 _t3162; { U64 *_hp = (U64 *)Str_size(); _t3162 = *_hp; free(_hp); }
    (void)_t3162;
    Vec *ptypes = Vec_new(_t3161, &(U64){_t3162});
    (void)ptypes;
    Str_delete(_t3161, &(Bool){1});
    ;
    Str *_t3163 = Str_lit("Bool", 4ULL);
    (void)_t3163;
    U64 _t3164; { U64 *_hp = (U64 *)Bool_size(); _t3164 = *_hp; free(_hp); }
    (void)_t3164;
    Vec *pmuts = Vec_new(_t3163, &(U64){_t3164});
    (void)pmuts;
    Str_delete(_t3163, &(Bool){1});
    ;
    while (1) {
        Bool _t3122 = check(p, TokenType_RParen());
        (void)_t3122;
        Bool _t3123 = check(p, TokenType_Eof());
        (void)_t3123;
        Bool _t3124 = Bool_not(_t3122);
        (void)_t3124;
        ;
        Bool _t3125 = Bool_not(_t3123);
        (void)_t3125;
        ;
        Bool _wcond3118 = Bool_and(_t3124, _t3125);
        (void)_wcond3118;
        ;
        ;
        if (_wcond3118) {
        } else {
            ;
            break;
        }
        ;
        Bool is_mut = 0;
        (void)is_mut;
        Bool _t3126 = check(p, TokenType_KwMut());
        (void)_t3126;
        if (_t3126) {
            Token *_t3119 = advance(p);
            (void)_t3119;
            Bool _t3120 = 1;
            (void)_t3120;
            is_mut = _t3120;
            ;
        }
        ;
        Str *ptype = expect_text(p, TokenType_Ident());
        (void)ptype;
        Vec_push(ptypes, ptype);
        Vec_push(pmuts, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = is_mut; _oa; }));
        Bool _t3127 = check(p, TokenType_Comma());
        (void)_t3127;
        if (_t3127) {
            Token *_t3121 = advance(p);
            (void)_t3121;
        }
        ;
    }
    Token *_t3165 = expect_token(p, TokenType_RParen());
    (void)_t3165;
    Str *return_type = Str_lit("", 0ULL);
    (void)return_type;
    Bool _t3166 = check(p, TokenType_KwReturns());
    (void)_t3166;
    if (_t3166) {
        Token *_t3128 = advance(p);
        (void)_t3128;
        return_type = expect_text(p, TokenType_Ident());
    }
    ;
    Str *name = Str_lit("_Fn", 3ULL);
    (void)name;
    {
        U64 _fi3129 = 0;
        (void)_fi3129;
        while (1) {
            U64 _t3132 = 0;
            (void)_t3132;
            U64 _t3133; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3133 = *_hp; free(_hp); }
            (void)_t3133;
            Range *_t3134 = Range_new(_t3132, _t3133);
            (void)_t3134;
            ;
            ;
            U64 _t3135; { U64 *_hp = (U64 *)Range_len(_t3134); _t3135 = *_hp; free(_hp); }
            (void)_t3135;
            Range_delete(_t3134, &(Bool){1});
            Bool _wcond3130; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3129}, &(U64){_t3135}); _wcond3130 = *_hp; free(_hp); }
            (void)_wcond3130;
            ;
            if (_wcond3130) {
            } else {
                ;
                break;
            }
            ;
            U64 _t3136 = 0;
            (void)_t3136;
            U64 _t3137; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3137 = *_hp; free(_hp); }
            (void)_t3137;
            Range *_t3138 = Range_new(_t3136, _t3137);
            (void)_t3138;
            ;
            ;
            U64 *i = Range_get(_t3138, _fi3129);
            (void)i;
            Range_delete(_t3138, &(Bool){1});
            U64 _t3139 = 1;
            (void)_t3139;
            U64 _t3140 = U64_add(_fi3129, _t3139);
            (void)_t3140;
            ;
            _fi3129 = _t3140;
            ;
            Str *_t3141 = Str_lit("_", 1ULL);
            (void)_t3141;
            name = Str_concat(name, _t3141);
            Str_delete(_t3141, &(Bool){1});
            Bool *m = Vec_get(pmuts, i);
            (void)m;
            if (DEREF(m)) {
                Str *_t3131 = Str_lit("mut_", 4ULL);
                (void)_t3131;
                name = Str_concat(name, _t3131);
                Str_delete(_t3131, &(Bool){1});
            }
            Str *t = Vec_get(ptypes, i);
            (void)t;
            name = Str_concat(name, t);
            U64_delete(i, &(Bool){1});
        }
        ;
    }
    U64 _t3167; { U64 *_hp = (U64 *)Str_len(return_type); _t3167 = *_hp; free(_hp); }
    (void)_t3167;
    U64 _t3168 = 0;
    (void)_t3168;
    Bool _t3169; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3167}, &(U64){_t3168}); _t3169 = *_hp; free(_hp); }
    (void)_t3169;
    ;
    ;
    if (_t3169) {
        Str *_t3142 = Str_lit("_ret_", 5ULL);
        (void)_t3142;
        name = Str_concat(name, _t3142);
        Str_delete(_t3142, &(Bool){1});
        name = Str_concat(name, return_type);
    }
    ;
    Str *_t3170 = Str_lit("Param", 5ULL);
    (void)_t3170;
    U64 _t3171; { U64 *_hp = (U64 *)Param_size(); _t3171 = *_hp; free(_hp); }
    (void)_t3171;
    Str *_t3172 = Str_lit("Str", 3ULL);
    (void)_t3172;
    U64 _t3173; { U64 *_hp = (U64 *)Str_size(); _t3173 = *_hp; free(_hp); }
    (void)_t3173;
    Str *_t3174 = Str_lit("Expr", 4ULL);
    (void)_t3174;
    U64 _t3175; { U64 *_hp = (U64 *)Expr_size(); _t3175 = *_hp; free(_hp); }
    (void)_t3175;
    I64 _t3176 = 0;
    (void)_t3176;
    I64 _t3177 = 1;
    (void)_t3177;
    I64 _t3178 = I64_sub(_t3176, _t3177);
    (void)_t3178;
    ;
    ;
    I64 _t3179 = 0;
    (void)_t3179;
    I64 _t3180 = 1;
    (void)_t3180;
    I64 _t3181 = I64_sub(_t3179, _t3180);
    (void)_t3181;
    ;
    ;
    U32 _t3182 = 0;
    (void)_t3182;
    I32 _t3183 = I64_to_i32(_t3178);
    (void)_t3183;
    ;
    I32 _t3184 = I64_to_i32(_t3181);
    (void)_t3184;
    ;
    Bool _t3185 = 0;
    (void)_t3185;
    Bool _t3186 = 0;
    (void)_t3186;
    FunctionDef *fd = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(FuncType_Func()); fd->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3170, &(U64){_t3171}); fd->params = *_ca; free(_ca); }
    fd->nparam = _t3182;
    { Map *_ca = Map_new(_t3172, &(U64){_t3173}, _t3174, &(U64){_t3175}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3183;
    fd->kwargs_index = _t3184;
    fd->return_is_ref = _t3185;
    fd->return_is_shallow = _t3186;
    (void)fd;
    Str_delete(_t3170, &(Bool){1});
    ;
    Str_delete(_t3172, &(Bool){1});
    ;
    Str_delete(_t3174, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    U64 _t3187; { U64 *_hp = (U64 *)Str_len(return_type); _t3187 = *_hp; free(_hp); }
    (void)_t3187;
    U64 _t3188 = 0;
    (void)_t3188;
    Bool _t3189; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3187}, &(U64){_t3188}); _t3189 = *_hp; free(_hp); }
    (void)_t3189;
    ;
    ;
    if (_t3189) {
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
    Bool _t3190 = 0;
    (void)_t3190;
    fd->return_is_ref = _t3190;
    ;
    Bool _t3191 = 0;
    (void)_t3191;
    fd->return_is_shallow = _t3191;
    ;
    I64 _t3192 = 0;
    (void)_t3192;
    I64 _t3193 = 1;
    (void)_t3193;
    I64 _t3194 = I64_sub(_t3192, _t3193);
    (void)_t3194;
    ;
    ;
    I32 _t3195 = I64_to_i32(_t3194);
    (void)_t3195;
    ;
    fd->variadic_index = _t3195;
    ;
    I64 _t3196 = 0;
    (void)_t3196;
    I64 _t3197 = 1;
    (void)_t3197;
    I64 _t3198 = I64_sub(_t3196, _t3197);
    (void)_t3198;
    ;
    ;
    I32 _t3199 = I64_to_i32(_t3198);
    (void)_t3199;
    ;
    fd->kwargs_index = _t3199;
    ;
    {
        U64 _fi3143 = 0;
        (void)_fi3143;
        while (1) {
            U64 _t3145 = 0;
            (void)_t3145;
            U64 _t3146; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3146 = *_hp; free(_hp); }
            (void)_t3146;
            Range *_t3147 = Range_new(_t3145, _t3146);
            (void)_t3147;
            ;
            ;
            U64 _t3148; { U64 *_hp = (U64 *)Range_len(_t3147); _t3148 = *_hp; free(_hp); }
            (void)_t3148;
            Range_delete(_t3147, &(Bool){1});
            Bool _wcond3144; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3143}, &(U64){_t3148}); _wcond3144 = *_hp; free(_hp); }
            (void)_wcond3144;
            ;
            if (_wcond3144) {
            } else {
                ;
                break;
            }
            ;
            U64 _t3149 = 0;
            (void)_t3149;
            U64 _t3150; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3150 = *_hp; free(_hp); }
            (void)_t3150;
            Range *_t3151 = Range_new(_t3149, _t3150);
            (void)_t3151;
            ;
            ;
            U64 *i = Range_get(_t3151, _fi3143);
            (void)i;
            Range_delete(_t3151, &(Bool){1});
            U64 _t3152 = 1;
            (void)_t3152;
            U64 _t3153 = U64_add(_fi3143, _t3152);
            (void)_t3153;
            ;
            _fi3143 = _t3153;
            ;
            Str *t = Vec_get(ptypes, i);
            (void)t;
            Bool *m = Vec_get(pmuts, i);
            (void)m;
            Bool _t3154 = Bool_clone(m);
            (void)_t3154;
            Bool _t3155 = 0;
            (void)_t3155;
            Bool _t3156 = 0;
            (void)_t3156;
            Param *_t3157 = malloc(sizeof(Param));
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t3157->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(t); _t3157->ptype = *_ca; free(_ca); }
            _t3157->is_mut = _t3154;
            _t3157->is_own = _t3155;
            _t3157->is_shallow = _t3156;
            (void)_t3157;
            ;
            ;
            ;
            U64_delete(i, &(Bool){1});
            Vec_push(&fd->params, _t3157);
        }
        ;
    }
    Vec_delete(pmuts, &(Bool){1});
    Vec_delete(ptypes, &(Bool){1});
    U64 _t3200; { U64 *_hp = (U64 *)Vec_len(&fd->params); _t3200 = *_hp; free(_hp); }
    (void)_t3200;
    I64 _t3201 = U64_to_i64(_t3200);
    (void)_t3201;
    ;
    U32 _t3202 = I64_to_u32(_t3201);
    (void)_t3202;
    ;
    fd->nparam = _t3202;
    ;
    ExprData *_t3203 = ExprData_FuncDef(fd);
    (void)_t3203;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *sig = Expr_new(_t3203, line, col, &p->path);
    (void)sig;
    ExprData_delete(_t3203, &(Bool){1});
    Bool _t3204 = 0;
    (void)_t3204;
    Bool _t3205 = 0;
    (void)_t3205;
    Bool _t3206 = 0;
    (void)_t3206;
    Bool _t3207 = 0;
    (void)_t3207;
    I32 _t3208 = 0;
    (void)_t3208;
    I32 _t3209 = 0;
    (void)_t3209;
    Declaration *_t3210 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(name); _t3210->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t3210->explicit_type = *_ca; free(_ca); }
    _t3210->is_mut = _t3204;
    _t3210->is_namespace = _t3205;
    _t3210->is_ref = _t3206;
    _t3210->is_own = _t3207;
    _t3210->field_offset = _t3208;
    _t3210->field_size = _t3209;
    _t3210->field_struct_def = NULL;
    _t3210->fn_sig = NULL;
    (void)_t3210;
    ;
    ;
    ;
    ;
    ;
    ;
    ExprData *_t3211 = ExprData_Decl(_t3210);
    (void)_t3211;
    Declaration_delete(_t3210, &(Bool){1});
    Expr *decl = Expr_new(_t3211, line, col, &p->path);
    (void)decl;
    ExprData_delete(_t3211, &(Bool){1});
    Expr_add_child(decl, sig);
    Vec_push(&p->fn_sig_decls, decl);
    return name;
}

Expr * parse_block(Parser * p) {
    (void)p;
    U32 _t3218 = peek_line(p);
    (void)_t3218;
    U32 _t3219 = peek_col(p);
    (void)_t3219;
    Expr *body = Expr_new(ExprData_Body(), _t3218, _t3219, &p->path);
    (void)body;
    ;
    ;
    while (1) {
        Bool _t3213 = check(p, TokenType_RBrace());
        (void)_t3213;
        Bool _t3214 = check(p, TokenType_Eof());
        (void)_t3214;
        Bool _t3215 = Bool_not(_t3213);
        (void)_t3215;
        ;
        Bool _t3216 = Bool_not(_t3214);
        (void)_t3216;
        ;
        Bool _wcond3212 = Bool_and(_t3215, _t3216);
        (void)_wcond3212;
        ;
        ;
        if (_wcond3212) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t3217 = parse_statement(p);
        (void)_t3217;
        Expr_add_child(body, _t3217);
    }
    Token *_t3220 = expect_token(p, TokenType_RBrace());
    (void)_t3220;
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
        TokenType *_sw3221 = TokenType_clone(&kw->type);
        (void)_sw3221;
        Bool _t3233; { Bool *_hp = (Bool *)TokenType_eq(_sw3221, TokenType_KwFunc()); _t3233 = *_hp; free(_hp); }
        (void)_t3233;
        if (_t3233) {
            ft = FuncType_clone(FuncType_Func());
        } else {
            Bool _t3232; { Bool *_hp = (Bool *)TokenType_eq(_sw3221, TokenType_KwProc()); _t3232 = *_hp; free(_hp); }
            (void)_t3232;
            if (_t3232) {
                ft = FuncType_clone(FuncType_Proc());
            } else {
                Bool _t3231; { Bool *_hp = (Bool *)TokenType_eq(_sw3221, TokenType_KwTest()); _t3231 = *_hp; free(_hp); }
                (void)_t3231;
                if (_t3231) {
                    ft = FuncType_clone(FuncType_Test());
                } else {
                    Bool _t3230; { Bool *_hp = (Bool *)TokenType_eq(_sw3221, TokenType_KwMacro()); _t3230 = *_hp; free(_hp); }
                    (void)_t3230;
                    if (_t3230) {
                        ft = FuncType_clone(FuncType_Macro());
                    } else {
                        Bool _t3229; { Bool *_hp = (Bool *)TokenType_eq(_sw3221, TokenType_KwExtFunc()); _t3229 = *_hp; free(_hp); }
                        (void)_t3229;
                        if (_t3229) {
                            ft = FuncType_clone(FuncType_ExtFunc());
                        } else {
                            Bool _t3228; { Bool *_hp = (Bool *)TokenType_eq(_sw3221, TokenType_KwExtProc()); _t3228 = *_hp; free(_hp); }
                            (void)_t3228;
                            if (_t3228) {
                                ft = FuncType_clone(FuncType_ExtProc());
                            } else {
                                Str *_t3222 = Str_lit("Str", 3ULL);
                                (void)_t3222;
                                U64 _t3223; { U64 *_hp = (U64 *)Str_size(); _t3223 = *_hp; free(_hp); }
                                (void)_t3223;
                                U64 _t3224 = 1;
                                (void)_t3224;
                                Array *_va56 = Array_new(_t3222, &(U64){_t3223}, &(U64){_t3224});
                                (void)_va56;
                                Str_delete(_t3222, &(Bool){1});
                                ;
                                ;
                                U64 _t3225 = 0;
                                (void)_t3225;
                                Str *_t3226 = Str_lit("expected function keyword", 25ULL);
                                (void)_t3226;
                                Array_set(_va56, &(U64){_t3225}, _t3226);
                                ;
                                Str *_t3227 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:150:17", 64ULL);
                                (void)_t3227;
                                panic(_t3227, _va56);
                                Str_delete(_t3227, &(Bool){1});
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
        TokenType_delete(_sw3221, &(Bool){1});
        ;
    }
    Token *_t3411 = expect_token(p, TokenType_LParen());
    (void)_t3411;
    Str *_t3412 = Str_lit("Param", 5ULL);
    (void)_t3412;
    U64 _t3413; { U64 *_hp = (U64 *)Param_size(); _t3413 = *_hp; free(_hp); }
    (void)_t3413;
    Str *_t3414 = Str_lit("Str", 3ULL);
    (void)_t3414;
    U64 _t3415; { U64 *_hp = (U64 *)Str_size(); _t3415 = *_hp; free(_hp); }
    (void)_t3415;
    Str *_t3416 = Str_lit("Expr", 4ULL);
    (void)_t3416;
    U64 _t3417; { U64 *_hp = (U64 *)Expr_size(); _t3417 = *_hp; free(_hp); }
    (void)_t3417;
    I64 _t3418 = 0;
    (void)_t3418;
    I64 _t3419 = 1;
    (void)_t3419;
    I64 _t3420 = I64_sub(_t3418, _t3419);
    (void)_t3420;
    ;
    ;
    I64 _t3421 = 0;
    (void)_t3421;
    I64 _t3422 = 1;
    (void)_t3422;
    I64 _t3423 = I64_sub(_t3421, _t3422);
    (void)_t3423;
    ;
    ;
    U32 _t3424 = 0;
    (void)_t3424;
    I32 _t3425 = I64_to_i32(_t3420);
    (void)_t3425;
    ;
    I32 _t3426 = I64_to_i32(_t3423);
    (void)_t3426;
    ;
    Bool _t3427 = 0;
    (void)_t3427;
    Bool _t3428 = 0;
    (void)_t3428;
    FunctionDef *fd = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(FuncType_Func()); fd->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3412, &(U64){_t3413}); fd->params = *_ca; free(_ca); }
    fd->nparam = _t3424;
    { Map *_ca = Map_new(_t3414, &(U64){_t3415}, _t3416, &(U64){_t3417}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3425;
    fd->kwargs_index = _t3426;
    fd->return_is_ref = _t3427;
    fd->return_is_shallow = _t3428;
    (void)fd;
    Str_delete(_t3412, &(Bool){1});
    ;
    Str_delete(_t3414, &(Bool){1});
    ;
    Str_delete(_t3416, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    FuncType_delete(&fd->func_type, &(Bool){0});
    { FuncType *_fa = FuncType_clone(ft); fd->func_type = *_fa; free(_fa); }
    while (1) {
        Bool _t3351 = check(p, TokenType_RParen());
        (void)_t3351;
        Bool _t3352 = check(p, TokenType_Eof());
        (void)_t3352;
        Bool _t3353 = Bool_not(_t3351);
        (void)_t3353;
        ;
        Bool _t3354 = Bool_not(_t3352);
        (void)_t3354;
        ;
        Bool _wcond3234 = Bool_and(_t3353, _t3354);
        (void)_wcond3234;
        ;
        ;
        if (_wcond3234) {
        } else {
            ;
            break;
        }
        ;
        Bool is_shallow = 0;
        (void)is_shallow;
        Bool _t3355 = check(p, TokenType_KwShallow());
        (void)_t3355;
        if (_t3355) {
            Token *_t3235 = advance(p);
            (void)_t3235;
            Bool _t3236 = 1;
            (void)_t3236;
            is_shallow = _t3236;
            ;
        }
        ;
        Bool is_own = 0;
        (void)is_own;
        Bool _t3356 = check(p, TokenType_KwOwn());
        (void)_t3356;
        if (_t3356) {
            Token *_t3237 = advance(p);
            (void)_t3237;
            Bool _t3238 = 1;
            (void)_t3238;
            is_own = _t3238;
            ;
        }
        ;
        Bool is_mut = 0;
        (void)is_mut;
        Bool _t3357 = check(p, TokenType_KwMut());
        (void)_t3357;
        if (_t3357) {
            Token *_t3239 = advance(p);
            (void)_t3239;
            Bool _t3240 = 1;
            (void)_t3240;
            is_mut = _t3240;
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
        Bool _t3358 = check(p, TokenType_Colon());
        (void)_t3358;
        Bool _t3359 = Bool_not(_t3358);
        (void)_t3359;
        ;
        if (_t3359) {
            tp = Str_clone(pname);
            nm = Str_lit("", 0ULL);
        } else {
            Token *_t3334 = expect_token(p, TokenType_Colon());
            (void)_t3334;
            Bool _t3335 = check(p, TokenType_DotDotDot());
            (void)_t3335;
            if (_t3335) {
                Token *_t3271 = advance(p);
                (void)_t3271;
                Bool _t3272 = Bool_or(is_own, is_mut);
                (void)_t3272;
                Bool _t3273 = Bool_or(_t3272, is_shallow);
                (void)_t3273;
                ;
                if (_t3273) {
                    Str *_t3241 = Str_lit("Str", 3ULL);
                    (void)_t3241;
                    U64 _t3242; { U64 *_hp = (U64 *)Str_size(); _t3242 = *_hp; free(_hp); }
                    (void)_t3242;
                    U64 _t3243 = 6;
                    (void)_t3243;
                    Array *_va57 = Array_new(_t3241, &(U64){_t3242}, &(U64){_t3243});
                    (void)_va57;
                    Str_delete(_t3241, &(Bool){1});
                    ;
                    ;
                    U64 _t3244 = 0;
                    (void)_t3244;
                    Str *_t3245 = Str_clone(&p->path);
                    (void)_t3245;
                    Array_set(_va57, &(U64){_t3244}, _t3245);
                    ;
                    U64 _t3246 = 1;
                    (void)_t3246;
                    Str *_t3247 = Str_lit(":", 1ULL);
                    (void)_t3247;
                    Array_set(_va57, &(U64){_t3246}, _t3247);
                    ;
                    U32 _t3248 = peek_line(p);
                    (void)_t3248;
                    U64 _t3249 = 2;
                    (void)_t3249;
                    Str *_t3250 = U32_to_str(&(U32){_t3248});
                    (void)_t3250;
                    ;
                    Array_set(_va57, &(U64){_t3249}, _t3250);
                    ;
                    U64 _t3251 = 3;
                    (void)_t3251;
                    Str *_t3252 = Str_lit(":", 1ULL);
                    (void)_t3252;
                    Array_set(_va57, &(U64){_t3251}, _t3252);
                    ;
                    U32 _t3253 = peek_col(p);
                    (void)_t3253;
                    U64 _t3254 = 4;
                    (void)_t3254;
                    Str *_t3255 = U32_to_str(&(U32){_t3253});
                    (void)_t3255;
                    ;
                    Array_set(_va57, &(U64){_t3254}, _t3255);
                    ;
                    U64 _t3256 = 5;
                    (void)_t3256;
                    Str *_t3257 = Str_lit(": kwargs parameter cannot be own/mut/shallow", 44ULL);
                    (void)_t3257;
                    Array_set(_va57, &(U64){_t3256}, _t3257);
                    ;
                    Str *_t3258 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:180:27", 64ULL);
                    (void)_t3258;
                    panic(_t3258, _va57);
                    Str_delete(_t3258, &(Bool){1});
                }
                ;
                I64 _t3274 = 0;
                (void)_t3274;
                I64 _t3275 = 1;
                (void)_t3275;
                I64 _t3276 = I64_sub(_t3274, _t3275);
                (void)_t3276;
                ;
                ;
                I32 _t3277 = I64_to_i32(_t3276);
                (void)_t3277;
                ;
                Bool _t3278; { Bool *_hp = (Bool *)I32_neq(&fd->kwargs_index, &(I32){_t3277}); _t3278 = *_hp; free(_hp); }
                (void)_t3278;
                ;
                if (_t3278) {
                    Str *_t3259 = Str_lit("Str", 3ULL);
                    (void)_t3259;
                    U64 _t3260; { U64 *_hp = (U64 *)Str_size(); _t3260 = *_hp; free(_hp); }
                    (void)_t3260;
                    U64 _t3261 = 1;
                    (void)_t3261;
                    Array *_va58 = Array_new(_t3259, &(U64){_t3260}, &(U64){_t3261});
                    (void)_va58;
                    Str_delete(_t3259, &(Bool){1});
                    ;
                    ;
                    U64 _t3262 = 0;
                    (void)_t3262;
                    Str *_t3263 = Str_lit("only one kwargs parameter is allowed", 36ULL);
                    (void)_t3263;
                    Array_set(_va58, &(U64){_t3262}, _t3263);
                    ;
                    Str *_t3264 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:184:27", 64ULL);
                    (void)_t3264;
                    panic(_t3264, _va58);
                    Str_delete(_t3264, &(Bool){1});
                }
                ;
                I64 _t3279 = 0;
                (void)_t3279;
                I64 _t3280 = 1;
                (void)_t3280;
                I64 _t3281 = I64_sub(_t3279, _t3280);
                (void)_t3281;
                ;
                ;
                I32 _t3282 = I64_to_i32(_t3281);
                (void)_t3282;
                ;
                Bool _t3283; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3282}); _t3283 = *_hp; free(_hp); }
                (void)_t3283;
                ;
                if (_t3283) {
                    Str *_t3265 = Str_lit("Str", 3ULL);
                    (void)_t3265;
                    U64 _t3266; { U64 *_hp = (U64 *)Str_size(); _t3266 = *_hp; free(_hp); }
                    (void)_t3266;
                    U64 _t3267 = 1;
                    (void)_t3267;
                    Array *_va59 = Array_new(_t3265, &(U64){_t3266}, &(U64){_t3267});
                    (void)_va59;
                    Str_delete(_t3265, &(Bool){1});
                    ;
                    ;
                    U64 _t3268 = 0;
                    (void)_t3268;
                    Str *_t3269 = Str_lit("cannot combine variadic and kwargs in the same function", 55ULL);
                    (void)_t3269;
                    Array_set(_va59, &(U64){_t3268}, _t3269);
                    ;
                    Str *_t3270 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:187:27", 64ULL);
                    (void)_t3270;
                    panic(_t3270, _va59);
                    Str_delete(_t3270, &(Bool){1});
                }
                ;
                U64 _t3284; { U64 *_hp = (U64 *)Vec_len(&fd->params); _t3284 = *_hp; free(_hp); }
                (void)_t3284;
                I64 _t3285 = U64_to_i64(_t3284);
                (void)_t3285;
                ;
                I32 _t3286 = I64_to_i32(_t3285);
                (void)_t3286;
                ;
                fd->kwargs_index = _t3286;
                ;
                Bool _t3287 = 1;
                (void)_t3287;
                is_own = _t3287;
                ;
                nm = Str_clone(pname);
                tp = Str_lit("Map", 3ULL);
            } else {
                Bool _t3333 = check(p, TokenType_DotDot());
                (void)_t3333;
                if (_t3333) {
                    Token *_t3318 = advance(p);
                    (void)_t3318;
                    if (is_own) {
                        Str *_t3288 = Str_lit("Str", 3ULL);
                        (void)_t3288;
                        U64 _t3289; { U64 *_hp = (U64 *)Str_size(); _t3289 = *_hp; free(_hp); }
                        (void)_t3289;
                        U64 _t3290 = 1;
                        (void)_t3290;
                        Array *_va60 = Array_new(_t3288, &(U64){_t3289}, &(U64){_t3290});
                        (void)_va60;
                        Str_delete(_t3288, &(Bool){1});
                        ;
                        ;
                        U64 _t3291 = 0;
                        (void)_t3291;
                        Str *_t3292 = Str_lit("variadic param cannot be 'own'", 30ULL);
                        (void)_t3292;
                        Array_set(_va60, &(U64){_t3291}, _t3292);
                        ;
                        Str *_t3293 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:195:35", 64ULL);
                        (void)_t3293;
                        panic(_t3293, _va60);
                        Str_delete(_t3293, &(Bool){1});
                    }
                    if (is_mut) {
                        Str *_t3294 = Str_lit("Str", 3ULL);
                        (void)_t3294;
                        U64 _t3295; { U64 *_hp = (U64 *)Str_size(); _t3295 = *_hp; free(_hp); }
                        (void)_t3295;
                        U64 _t3296 = 1;
                        (void)_t3296;
                        Array *_va61 = Array_new(_t3294, &(U64){_t3295}, &(U64){_t3296});
                        (void)_va61;
                        Str_delete(_t3294, &(Bool){1});
                        ;
                        ;
                        U64 _t3297 = 0;
                        (void)_t3297;
                        Str *_t3298 = Str_lit("variadic param cannot be 'mut'", 30ULL);
                        (void)_t3298;
                        Array_set(_va61, &(U64){_t3297}, _t3298);
                        ;
                        Str *_t3299 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:196:35", 64ULL);
                        (void)_t3299;
                        panic(_t3299, _va61);
                        Str_delete(_t3299, &(Bool){1});
                    }
                    if (is_shallow) {
                        Str *_t3300 = Str_lit("Str", 3ULL);
                        (void)_t3300;
                        U64 _t3301; { U64 *_hp = (U64 *)Str_size(); _t3301 = *_hp; free(_hp); }
                        (void)_t3301;
                        U64 _t3302 = 1;
                        (void)_t3302;
                        Array *_va62 = Array_new(_t3300, &(U64){_t3301}, &(U64){_t3302});
                        (void)_va62;
                        Str_delete(_t3300, &(Bool){1});
                        ;
                        ;
                        U64 _t3303 = 0;
                        (void)_t3303;
                        Str *_t3304 = Str_lit("variadic param cannot be 'shallow'", 34ULL);
                        (void)_t3304;
                        Array_set(_va62, &(U64){_t3303}, _t3304);
                        ;
                        Str *_t3305 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:197:39", 64ULL);
                        (void)_t3305;
                        panic(_t3305, _va62);
                        Str_delete(_t3305, &(Bool){1});
                    }
                    I64 _t3319 = 0;
                    (void)_t3319;
                    I64 _t3320 = 1;
                    (void)_t3320;
                    I64 _t3321 = I64_sub(_t3319, _t3320);
                    (void)_t3321;
                    ;
                    ;
                    I32 _t3322 = I64_to_i32(_t3321);
                    (void)_t3322;
                    ;
                    Bool _t3323; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3322}); _t3323 = *_hp; free(_hp); }
                    (void)_t3323;
                    ;
                    if (_t3323) {
                        Str *_t3306 = Str_lit("Str", 3ULL);
                        (void)_t3306;
                        U64 _t3307; { U64 *_hp = (U64 *)Str_size(); _t3307 = *_hp; free(_hp); }
                        (void)_t3307;
                        U64 _t3308 = 1;
                        (void)_t3308;
                        Array *_va63 = Array_new(_t3306, &(U64){_t3307}, &(U64){_t3308});
                        (void)_va63;
                        Str_delete(_t3306, &(Bool){1});
                        ;
                        ;
                        U64 _t3309 = 0;
                        (void)_t3309;
                        Str *_t3310 = Str_lit("only one variadic param allowed", 31ULL);
                        (void)_t3310;
                        Array_set(_va63, &(U64){_t3309}, _t3310);
                        ;
                        Str *_t3311 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:198:63", 64ULL);
                        (void)_t3311;
                        panic(_t3311, _va63);
                        Str_delete(_t3311, &(Bool){1});
                    }
                    ;
                    I64 _t3324 = 0;
                    (void)_t3324;
                    I64 _t3325 = 1;
                    (void)_t3325;
                    I64 _t3326 = I64_sub(_t3324, _t3325);
                    (void)_t3326;
                    ;
                    ;
                    I32 _t3327 = I64_to_i32(_t3326);
                    (void)_t3327;
                    ;
                    Bool _t3328; { Bool *_hp = (Bool *)I32_neq(&fd->kwargs_index, &(I32){_t3327}); _t3328 = *_hp; free(_hp); }
                    (void)_t3328;
                    ;
                    if (_t3328) {
                        Str *_t3312 = Str_lit("Str", 3ULL);
                        (void)_t3312;
                        U64 _t3313; { U64 *_hp = (U64 *)Str_size(); _t3313 = *_hp; free(_hp); }
                        (void)_t3313;
                        U64 _t3314 = 1;
                        (void)_t3314;
                        Array *_va64 = Array_new(_t3312, &(U64){_t3313}, &(U64){_t3314});
                        (void)_va64;
                        Str_delete(_t3312, &(Bool){1});
                        ;
                        ;
                        U64 _t3315 = 0;
                        (void)_t3315;
                        Str *_t3316 = Str_lit("cannot combine variadic and kwargs in the same function", 55ULL);
                        (void)_t3316;
                        Array_set(_va64, &(U64){_t3315}, _t3316);
                        ;
                        Str *_t3317 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:200:27", 64ULL);
                        (void)_t3317;
                        panic(_t3317, _va64);
                        Str_delete(_t3317, &(Bool){1});
                    }
                    ;
                    U64 _t3329; { U64 *_hp = (U64 *)Vec_len(&fd->params); _t3329 = *_hp; free(_hp); }
                    (void)_t3329;
                    I64 _t3330 = U64_to_i64(_t3329);
                    (void)_t3330;
                    ;
                    I32 _t3331 = I64_to_i32(_t3330);
                    (void)_t3331;
                    ;
                    fd->variadic_index = _t3331;
                    ;
                    Bool _t3332 = 1;
                    (void)_t3332;
                    is_variadic = _t3332;
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
        Str *_t3360 = Str_lit("Fn", 2ULL);
        (void)_t3360;
        Bool _t3361; { Bool *_hp = (Bool *)Str_eq(tp, _t3360); _t3361 = *_hp; free(_hp); }
        (void)_t3361;
        Str_delete(_t3360, &(Bool){1});
        if (_t3361) {
            U32 _t3336 = peek_line(p);
            (void)_t3336;
            U32 _t3337 = peek_col(p);
            (void)_t3337;
            Str *syn_name = parse_fn_signature(p, _t3336, _t3337);
            (void)syn_name;
            ;
            ;
            U64 _t3338; { U64 *_hp = (U64 *)Str_len(syn_name); _t3338 = *_hp; free(_hp); }
            (void)_t3338;
            U64 _t3339 = 0;
            (void)_t3339;
            Bool _t3340; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3338}, &(U64){_t3339}); _t3340 = *_hp; free(_hp); }
            (void)_t3340;
            ;
            ;
            if (_t3340) {
                tp = Str_clone(syn_name);
            }
            ;
            Str_delete(syn_name, &(Bool){1});
        }
        ;
        Bool has_default = 0;
        (void)has_default;
        Bool _t3362 = check(p, TokenType_Eq());
        (void)_t3362;
        if (_t3362) {
            Token *_t3341 = advance(p);
            (void)_t3341;
            Expr *def_expr = parse_expression(p);
            (void)def_expr;
            Str *_t3342 = Str_clone(nm);
            (void)_t3342;
            Map_set(&fd->param_defaults, _t3342, def_expr);
            Bool _t3343 = 1;
            (void)_t3343;
            has_default = _t3343;
            ;
        }
        ;
        I64 _t3363 = 0;
        (void)_t3363;
        I64 _t3364 = 1;
        (void)_t3364;
        I64 _t3365 = I64_sub(_t3363, _t3364);
        (void)_t3365;
        ;
        ;
        I32 _t3366 = I64_to_i32(_t3365);
        (void)_t3366;
        ;
        Bool _t3367; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3366}); _t3367 = *_hp; free(_hp); }
        (void)_t3367;
        ;
        Bool _t3368 = Bool_not(is_variadic);
        (void)_t3368;
        ;
        Bool _t3369 = Bool_and(_t3367, _t3368);
        (void)_t3369;
        ;
        ;
        Bool _t3370 = Bool_not(has_default);
        (void)_t3370;
        ;
        Bool _t3371 = Bool_and(_t3369, _t3370);
        (void)_t3371;
        ;
        ;
        if (_t3371) {
            Str *_t3344 = Str_lit("Str", 3ULL);
            (void)_t3344;
            U64 _t3345; { U64 *_hp = (U64 *)Str_size(); _t3345 = *_hp; free(_hp); }
            (void)_t3345;
            U64 _t3346 = 1;
            (void)_t3346;
            Array *_va65 = Array_new(_t3344, &(U64){_t3345}, &(U64){_t3346});
            (void)_va65;
            Str_delete(_t3344, &(Bool){1});
            ;
            ;
            U64 _t3347 = 0;
            (void)_t3347;
            Str *_t3348 = Str_lit("positional param not allowed after variadic", 43ULL);
            (void)_t3348;
            Array_set(_va65, &(U64){_t3347}, _t3348);
            ;
            Str *_t3349 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:227:19", 64ULL);
            (void)_t3349;
            panic(_t3349, _va65);
            Str_delete(_t3349, &(Bool){1});
        }
        ;
        Bool _t3372 = Bool_clone(&(Bool){is_mut});
        (void)_t3372;
        ;
        Bool _t3373 = Bool_clone(&(Bool){is_own});
        (void)_t3373;
        ;
        Bool _t3374 = Bool_clone(&(Bool){is_shallow});
        (void)_t3374;
        ;
        Param *_t3375 = malloc(sizeof(Param));
        { Str *_ca = Str_clone(nm); _t3375->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(tp); _t3375->ptype = *_ca; free(_ca); }
        _t3375->is_mut = _t3372;
        _t3375->is_own = _t3373;
        _t3375->is_shallow = _t3374;
        (void)_t3375;
        ;
        ;
        ;
        Str_delete(nm, &(Bool){1});
        Str_delete(tp, &(Bool){1});
        Vec_push(&fd->params, _t3375);
        Bool _t3376 = check(p, TokenType_Comma());
        (void)_t3376;
        if (_t3376) {
            Token *_t3350 = advance(p);
            (void)_t3350;
        }
        ;
    }
    Token *_t3429 = expect_token(p, TokenType_RParen());
    (void)_t3429;
    Bool _t3430 = check(p, TokenType_KwReturns());
    (void)_t3430;
    if (_t3430) {
        Token *_t3382 = advance(p);
        (void)_t3382;
        Bool _t3383 = check(p, TokenType_KwRef());
        (void)_t3383;
        if (_t3383) {
            Token *_t3377 = advance(p);
            (void)_t3377;
            Bool _t3378 = 1;
            (void)_t3378;
            fd->return_is_ref = _t3378;
            ;
        } else {
            Bool _t3381 = check(p, TokenType_KwShallow());
            (void)_t3381;
            if (_t3381) {
                Token *_t3379 = advance(p);
                (void)_t3379;
                Bool _t3380 = 1;
                (void)_t3380;
                fd->return_is_shallow = _t3380;
                ;
            }
            ;
        }
        ;
        Str_delete(&fd->return_type, &(Bool){0});
        { Str *_fa = expect_text(p, TokenType_Ident()); fd->return_type = *_fa; free(_fa); }
    }
    ;
    U64 _t3431; { U64 *_hp = (U64 *)Vec_len(&fd->params); _t3431 = *_hp; free(_hp); }
    (void)_t3431;
    I64 _t3432 = U64_to_i64(_t3431);
    (void)_t3432;
    ;
    U32 _t3433 = I64_to_u32(_t3432);
    (void)_t3433;
    ;
    fd->nparam = _t3433;
    ;
    ExprData *_t3434 = ExprData_FuncDef(fd);
    (void)_t3434;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *def = Expr_new(_t3434, kw_line, kw_col, &p->path);
    (void)def;
    ExprData_delete(_t3434, &(Bool){1});
    Bool _t3435 = check(p, TokenType_LBrace());
    (void)_t3435;
    if (_t3435) {
        Token *_t3384 = expect_token(p, TokenType_LBrace());
        (void)_t3384;
        Expr *_t3385 = parse_block(p);
        (void)_t3385;
        Expr_add_child(def, _t3385);
    } else {
        Bool _t3406; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Func()); _t3406 = *_hp; free(_hp); }
        (void)_t3406;
        Bool _t3407; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Proc()); _t3407 = *_hp; free(_hp); }
        (void)_t3407;
        Bool _t3408 = Bool_not(_t3406);
        (void)_t3408;
        ;
        Bool _t3409 = Bool_not(_t3407);
        (void)_t3409;
        ;
        Bool _t3410 = Bool_and(_t3408, _t3409);
        (void)_t3410;
        ;
        ;
        if (_t3410) {
            Str *_t3386 = Str_lit("Str", 3ULL);
            (void)_t3386;
            U64 _t3387; { U64 *_hp = (U64 *)Str_size(); _t3387 = *_hp; free(_hp); }
            (void)_t3387;
            U64 _t3388 = 8;
            (void)_t3388;
            Array *_va66 = Array_new(_t3386, &(U64){_t3387}, &(U64){_t3388});
            (void)_va66;
            Str_delete(_t3386, &(Bool){1});
            ;
            ;
            U64 _t3389 = 0;
            (void)_t3389;
            Str *_t3390 = Str_clone(&p->path);
            (void)_t3390;
            Array_set(_va66, &(U64){_t3389}, _t3390);
            ;
            U64 _t3391 = 1;
            (void)_t3391;
            Str *_t3392 = Str_lit(":", 1ULL);
            (void)_t3392;
            Array_set(_va66, &(U64){_t3391}, _t3392);
            ;
            U64 _t3393 = 2;
            (void)_t3393;
            Str *_t3394 = U32_to_str(&(U32){kw_line});
            (void)_t3394;
            Array_set(_va66, &(U64){_t3393}, _t3394);
            ;
            U64 _t3395 = 3;
            (void)_t3395;
            Str *_t3396 = Str_lit(":", 1ULL);
            (void)_t3396;
            Array_set(_va66, &(U64){_t3395}, _t3396);
            ;
            U64 _t3397 = 4;
            (void)_t3397;
            Str *_t3398 = U32_to_str(&(U32){kw_col});
            (void)_t3398;
            Array_set(_va66, &(U64){_t3397}, _t3398);
            ;
            U64 _t3399 = 5;
            (void)_t3399;
            Str *_t3400 = Str_lit(": ", 2ULL);
            (void)_t3400;
            Array_set(_va66, &(U64){_t3399}, _t3400);
            ;
            U64 _t3401 = 6;
            (void)_t3401;
            Str *_t3402 = func_type_name(ft);
            (void)_t3402;
            Array_set(_va66, &(U64){_t3401}, _t3402);
            ;
            U64 _t3403 = 7;
            (void)_t3403;
            Str *_t3404 = Str_lit(" requires a body", 16ULL);
            (void)_t3404;
            Array_set(_va66, &(U64){_t3403}, _t3404);
            ;
            Str *_t3405 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:257:19", 64ULL);
            (void)_t3405;
            panic(_t3405, _va66);
            Str_delete(_t3405, &(Bool){1});
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
    Token *_t3451 = expect_token(p, TokenType_LBrace());
    (void)_t3451;
    U32 _t3452 = peek_line(p);
    (void)_t3452;
    U32 _t3453 = peek_col(p);
    (void)_t3453;
    Expr *body = Expr_new(ExprData_Body(), _t3452, _t3453, &p->path);
    (void)body;
    ;
    ;
    Bool in_namespace = 0;
    (void)in_namespace;
    while (1) {
        Bool _t3442 = check(p, TokenType_RBrace());
        (void)_t3442;
        Bool _t3443 = check(p, TokenType_Eof());
        (void)_t3443;
        Bool _t3444 = Bool_not(_t3442);
        (void)_t3444;
        ;
        Bool _t3445 = Bool_not(_t3443);
        (void)_t3445;
        ;
        Bool _wcond3436 = Bool_and(_t3444, _t3445);
        (void)_wcond3436;
        ;
        ;
        if (_wcond3436) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3446 = check(p, TokenType_KwNamespace());
        (void)_t3446;
        if (_t3446) {
            Token *_t3437 = advance(p);
            (void)_t3437;
            Token *_t3438 = expect_token(p, TokenType_Colon());
            (void)_t3438;
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
    Token *_t3454 = expect_token(p, TokenType_RBrace());
    (void)_t3454;
    Expr_add_child(def, body);
    return def;
}

Expr * parse_enum_def(Parser * p) {
    (void)p;
    U32 kw_line = peek_line(p);
    (void)kw_line;
    U32 kw_col = peek_col(p);
    (void)kw_col;
    Token *_t3478 = advance(p);
    (void)_t3478;
    Expr *def = Expr_new(ExprData_EnumDef(), kw_line, kw_col, &p->path);
    (void)def;
    ;
    ;
    Token *_t3479 = expect_token(p, TokenType_LBrace());
    (void)_t3479;
    U32 _t3480 = peek_line(p);
    (void)_t3480;
    U32 _t3481 = peek_col(p);
    (void)_t3481;
    Expr *body = Expr_new(ExprData_Body(), _t3480, _t3481, &p->path);
    (void)body;
    ;
    ;
    Bool in_namespace = 0;
    (void)in_namespace;
    while (1) {
        Bool _t3473 = check(p, TokenType_RBrace());
        (void)_t3473;
        Bool _t3474 = check(p, TokenType_Eof());
        (void)_t3474;
        Bool _t3475 = Bool_not(_t3473);
        (void)_t3475;
        ;
        Bool _t3476 = Bool_not(_t3474);
        (void)_t3476;
        ;
        Bool _wcond3455 = Bool_and(_t3475, _t3476);
        (void)_wcond3455;
        ;
        ;
        if (_wcond3455) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3477 = check(p, TokenType_KwNamespace());
        (void)_t3477;
        if (_t3477) {
            Token *_t3456 = advance(p);
            (void)_t3456;
            Token *_t3457 = expect_token(p, TokenType_Colon());
            (void)_t3457;
            Bool _t3458 = 1;
            (void)_t3458;
            in_namespace = _t3458;
            ;
            ;
            continue;
        }
        ;
        if (in_namespace) {
            Expr *stmt = parse_statement(p);
            (void)stmt;
            Bool _t3461; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3461 = *_hp; free(_hp); }
            (void)_t3461;
            if (_t3461) {
                Bool _t3460; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3460 = *_hp; free(_hp); }
                (void)_t3460;
                if (_t3460) {
                    Declaration *dd = ExprData_get_Decl(&stmt->data);
                    (void)dd;
                    Bool _t3459 = 1;
                    (void)_t3459;
                    dd->is_namespace = _t3459;
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
            Bool _t3464 = 0;
            (void)_t3464;
            Bool _t3465 = 0;
            (void)_t3465;
            Bool _t3466 = 0;
            (void)_t3466;
            Bool _t3467 = 0;
            (void)_t3467;
            I32 _t3468 = 0;
            (void)_t3468;
            I32 _t3469 = 0;
            (void)_t3469;
            Declaration *dd = malloc(sizeof(Declaration));
            { Str *_ca = Str_clone(vname); dd->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
            dd->is_mut = _t3464;
            dd->is_namespace = _t3465;
            dd->is_ref = _t3466;
            dd->is_own = _t3467;
            dd->field_offset = _t3468;
            dd->field_size = _t3469;
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
            Bool _t3470 = check(p, TokenType_Colon());
            (void)_t3470;
            if (_t3470) {
                Token *_t3462 = advance(p);
                (void)_t3462;
                Str_delete(&dd->explicit_type, &(Bool){0});
                { Str *_fa = expect_text(p, TokenType_Ident()); dd->explicit_type = *_fa; free(_fa); }
            }
            ;
            ExprData *_t3471 = ExprData_Decl(dd);
            (void)_t3471;
            Declaration_delete(dd, &(Bool){1});
            Expr *variant = Expr_new(_t3471, v_line, v_col, &p->path);
            (void)variant;
            ExprData_delete(_t3471, &(Bool){1});
            ;
            ;
            Expr_add_child(body, variant);
            Bool _t3472 = check(p, TokenType_Comma());
            (void)_t3472;
            if (_t3472) {
                Token *_t3463 = advance(p);
                (void)_t3463;
            }
            ;
        }
    }
    ;
    Token *_t3482 = expect_token(p, TokenType_RBrace());
    (void)_t3482;
    Expr_add_child(def, body);
    return def;
}

Expr * parse_call(Parser * p, Str * name, U32 call_line, U32 call_col) {
    (void)p;
    (void)name;
    (void)call_line;
    (void)call_col;
    Token *_t3513 = advance(p);
    (void)_t3513;
    Expr *call = Expr_new(ExprData_FCall(), call_line, call_col, &p->path);
    (void)call;
    Str *_t3514 = Str_clone(name);
    (void)_t3514;
    ExprData *_t3515 = ExprData_Ident(_t3514);
    (void)_t3515;
    Str_delete(_t3514, &(Bool){1});
    Expr *callee = Expr_new(_t3515, call_line, call_col, &p->path);
    (void)callee;
    ExprData_delete(_t3515, &(Bool){1});
    Expr_add_child(call, callee);
    while (1) {
        Bool _t3503 = check(p, TokenType_RParen());
        (void)_t3503;
        Bool _t3504 = check(p, TokenType_Eof());
        (void)_t3504;
        Bool _t3505 = Bool_not(_t3503);
        (void)_t3505;
        ;
        Bool _t3506 = Bool_not(_t3504);
        (void)_t3506;
        ;
        Bool _wcond3483 = Bool_and(_t3505, _t3506);
        (void)_wcond3483;
        ;
        ;
        if (_wcond3483) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3507 = check(p, TokenType_Ident());
        (void)_t3507;
        if (_t3507) {
            U64 _t3494 = 1;
            (void)_t3494;
            U64 _t3495 = U64_add(p->pos, _t3494);
            (void)_t3495;
            ;
            U64 _t3496; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3496 = *_hp; free(_hp); }
            (void)_t3496;
            Bool _t3497; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3495}, &(U64){_t3496}); _t3497 = *_hp; free(_hp); }
            (void)_t3497;
            ;
            ;
            if (_t3497) {
                U64 _t3489 = 1;
                (void)_t3489;
                U64 _t3490 = U64_add(p->pos, _t3489);
                (void)_t3490;
                ;
                I64 _t3491 = U64_to_i64(_t3490);
                (void)_t3491;
                ;
                U64 *_t3492 = malloc(sizeof(U64)); *_t3492 = I64_to_u64(_t3491);
                (void)_t3492;
                ;
                Token *next_tok = Vec_get(&p->tokens, _t3492);
                (void)next_tok;
                Bool _t3493; { Bool *_hp = (Bool *)TokenType_eq(&next_tok->type, TokenType_Eq()); _t3493 = *_hp; free(_hp); }
                (void)_t3493;
                U64_delete(_t3492, &(Bool){1});
                if (_t3493) {
                    U32 na_line = peek_line(p);
                    (void)na_line;
                    U32 na_col = peek_col(p);
                    (void)na_col;
                    Str *aname = expect_text(p, TokenType_Ident());
                    (void)aname;
                    Token *_t3485 = advance(p);
                    (void)_t3485;
                    ExprData *_t3486 = ExprData_NamedArg(aname);
                    (void)_t3486;
                    Str_delete(aname, &(Bool){1});
                    Expr *na = Expr_new(_t3486, na_line, na_col, &p->path);
                    (void)na;
                    ExprData_delete(_t3486, &(Bool){1});
                    ;
                    ;
                    Expr *_t3487 = parse_expression(p);
                    (void)_t3487;
                    Expr_add_child(na, _t3487);
                    Expr_add_child(call, na);
                    Bool _t3488 = check(p, TokenType_Comma());
                    (void)_t3488;
                    if (_t3488) {
                        Token *_t3484 = advance(p);
                        (void)_t3484;
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
        Bool _t3508 = check(p, TokenType_DotDot());
        (void)_t3508;
        if (_t3508) {
            Token *_t3498 = advance(p);
            (void)_t3498;
            Bool _t3499 = 1;
            (void)_t3499;
            is_splat = _t3499;
            ;
        }
        ;
        Bool is_own_arg = 0;
        (void)is_own_arg;
        Bool _t3509 = check(p, TokenType_KwOwn());
        (void)_t3509;
        if (_t3509) {
            Token *_t3500 = advance(p);
            (void)_t3500;
            Bool _t3501 = 1;
            (void)_t3501;
            is_own_arg = _t3501;
            ;
        }
        ;
        Expr *arg = parse_expression(p);
        (void)arg;
        Bool _t3510 = Bool_clone(&(Bool){is_own_arg});
        (void)_t3510;
        ;
        arg->is_own_arg = _t3510;
        ;
        Bool _t3511 = Bool_clone(&(Bool){is_splat});
        (void)_t3511;
        ;
        arg->is_splat = _t3511;
        ;
        Expr_add_child(call, arg);
        Bool _t3512 = check(p, TokenType_Comma());
        (void)_t3512;
        if (_t3512) {
            Token *_t3502 = advance(p);
            (void)_t3502;
        }
        ;
    }
    Token *_t3516 = expect_token(p, TokenType_RParen());
    (void)_t3516;
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
    U32 _t3723 = 0;
    (void)_t3723;
    U32 _t3724 = 0;
    (void)_t3724;
    Expr *e = Expr_new(ExprData_Body(), _t3723, _t3724, &p->path);
    (void)e;
    ;
    ;
    Bool e_set = 0;
    (void)e_set;
    Bool _t3725; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t3725 = *_hp; free(_hp); }
    (void)_t3725;
    if (_t3725) {
        Token *_t3517 = advance(p);
        (void)_t3517;
        Str *_t3518 = Str_clone(&t->text);
        (void)_t3518;
        ExprData *_t3519 = ExprData_LiteralStr(_t3518);
        (void)_t3519;
        Str_delete(_t3518, &(Bool){1});
        e = Expr_new(_t3519, t_line, t_col, &p->path);
        ExprData_delete(_t3519, &(Bool){1});
        Bool _t3520 = 1;
        (void)_t3520;
        e_set = _t3520;
        ;
    }
    ;
    Bool _t3726 = Bool_not(e_set);
    (void)_t3726;
    Bool _t3727; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t3727 = *_hp; free(_hp); }
    (void)_t3727;
    Bool _t3728 = Bool_and(_t3726, _t3727);
    (void)_t3728;
    ;
    ;
    if (_t3728) {
        Token *_t3521 = advance(p);
        (void)_t3521;
        Str *_t3522 = Str_clone(&t->text);
        (void)_t3522;
        ExprData *_t3523 = ExprData_LiteralNum(_t3522);
        (void)_t3523;
        Str_delete(_t3522, &(Bool){1});
        e = Expr_new(_t3523, t_line, t_col, &p->path);
        ExprData_delete(_t3523, &(Bool){1});
        Bool _t3524 = 1;
        (void)_t3524;
        e_set = _t3524;
        ;
    }
    ;
    Bool _t3729 = Bool_not(e_set);
    (void)_t3729;
    Bool _t3730; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Minus()); _t3730 = *_hp; free(_hp); }
    (void)_t3730;
    Bool _t3731 = Bool_and(_t3729, _t3730);
    (void)_t3731;
    ;
    ;
    if (_t3731) {
        U64 _t3540 = 1;
        (void)_t3540;
        U64 _t3541 = U64_add(p->pos, _t3540);
        (void)_t3541;
        ;
        U64 _t3542; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3542 = *_hp; free(_hp); }
        (void)_t3542;
        Bool _t3543; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3541}, &(U64){_t3542}); _t3543 = *_hp; free(_hp); }
        (void)_t3543;
        ;
        ;
        if (_t3543) {
            U64 _t3535 = 1;
            (void)_t3535;
            U64 _t3536 = U64_add(p->pos, _t3535);
            (void)_t3536;
            ;
            I64 _t3537 = U64_to_i64(_t3536);
            (void)_t3537;
            ;
            U64 *_t3538 = malloc(sizeof(U64)); *_t3538 = I64_to_u64(_t3537);
            (void)_t3538;
            ;
            Token *next_tok = Vec_get(&p->tokens, _t3538);
            (void)next_tok;
            Bool _t3539; { Bool *_hp = (Bool *)TokenType_eq(&next_tok->type, TokenType_Number()); _t3539 = *_hp; free(_hp); }
            (void)_t3539;
            U64_delete(_t3538, &(Bool){1});
            if (_t3539) {
                Token *_t3525 = advance(p);
                (void)_t3525;
                Token *num_tok = advance(p);
                (void)num_tok;
                Str *_t3526 = Str_lit("0", 1ULL);
                (void)_t3526;
                Str *_t3527 = Str_clone(_t3526);
                (void)_t3527;
                Str_delete(_t3526, &(Bool){1});
                ExprData *_t3528 = ExprData_LiteralNum(_t3527);
                (void)_t3528;
                Str_delete(_t3527, &(Bool){1});
                Expr *zero = Expr_new(_t3528, t_line, t_col, &p->path);
                (void)zero;
                ExprData_delete(_t3528, &(Bool){1});
                Str *_t3529 = Str_lit("sub", 3ULL);
                (void)_t3529;
                Str *_t3530 = Str_clone(_t3529);
                (void)_t3530;
                Str_delete(_t3529, &(Bool){1});
                ExprData *_t3531 = ExprData_FieldAccess(_t3530);
                (void)_t3531;
                Str_delete(_t3530, &(Bool){1});
                Expr *sub_access = Expr_new(_t3531, t_line, t_col, &p->path);
                (void)sub_access;
                ExprData_delete(_t3531, &(Bool){1});
                Expr_add_child(sub_access, zero);
                Expr *sub_call = Expr_new(ExprData_FCall(), t_line, t_col, &p->path);
                (void)sub_call;
                Expr_add_child(sub_call, sub_access);
                Str *_t3532 = Str_clone(&num_tok->text);
                (void)_t3532;
                ExprData *_t3533 = ExprData_LiteralNum(_t3532);
                (void)_t3533;
                Str_delete(_t3532, &(Bool){1});
                Expr *num_arg = Expr_new(_t3533, t_line, t_col, &p->path);
                (void)num_arg;
                ExprData_delete(_t3533, &(Bool){1});
                Expr_add_child(sub_call, num_arg);
                e = Expr_clone(sub_call);
                Expr_delete(sub_call, &(Bool){1});
                Bool _t3534 = 1;
                (void)_t3534;
                e_set = _t3534;
                ;
            }
            ;
        }
        ;
    }
    ;
    Bool _t3732 = Bool_not(e_set);
    (void)_t3732;
    Bool _t3733; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Char()); _t3733 = *_hp; free(_hp); }
    (void)_t3733;
    Bool _t3734 = Bool_and(_t3732, _t3733);
    (void)_t3734;
    ;
    ;
    if (_t3734) {
        Token *_t3573 = advance(p);
        (void)_t3573;
        Str *ch = Str_clone(&t->text);
        (void)ch;
        I64 byte_val = 0;
        (void)byte_val;
        U64 _t3574; { U64 *_hp = (U64 *)Str_len(ch); _t3574 = *_hp; free(_hp); }
        (void)_t3574;
        U64 _t3575 = 0;
        (void)_t3575;
        U64 *_t3576 = malloc(sizeof(U64));
        *_t3576 = 0;
        (void)_t3576;
        U8 *_t3577 = Str_get(ch, _t3576);
        (void)_t3577;
        U8 _t3578 = 92;
        (void)_t3578;
        Bool _t3579; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3574}, &(U64){_t3575}); _t3579 = *_hp; free(_hp); }
        (void)_t3579;
        ;
        ;
        Bool _t3580 = U8_eq(DEREF(_t3577), _t3578);
        (void)_t3580;
        U64_delete(_t3576, &(Bool){1});
        ;
        Bool _t3581 = Bool_and(_t3579, _t3580);
        (void)_t3581;
        ;
        ;
        if (_t3581) {
            U64 _t3564; { U64 *_hp = (U64 *)Str_len(ch); _t3564 = *_hp; free(_hp); }
            (void)_t3564;
            U64 _t3565 = 1;
            (void)_t3565;
            Bool _t3566; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3564}, &(U64){_t3565}); _t3566 = *_hp; free(_hp); }
            (void)_t3566;
            ;
            ;
            if (_t3566) {
                U64 *_t3561 = malloc(sizeof(U64));
                *_t3561 = 1;
                (void)_t3561;
                U8 *c2 = Str_get(ch, _t3561);
                (void)c2;
                U8 _t3562 = 110;
                (void)_t3562;
                Bool _t3563 = U8_eq(DEREF(c2), _t3562);
                (void)_t3563;
                ;
                if (_t3563) {
                    I64 _t3544 = 10;
                    (void)_t3544;
                    byte_val = _t3544;
                    ;
                } else {
                    U8 _t3559 = 116;
                    (void)_t3559;
                    Bool _t3560 = U8_eq(DEREF(c2), _t3559);
                    (void)_t3560;
                    ;
                    if (_t3560) {
                        I64 _t3545 = 9;
                        (void)_t3545;
                        byte_val = _t3545;
                        ;
                    } else {
                        U8 _t3557 = 114;
                        (void)_t3557;
                        Bool _t3558 = U8_eq(DEREF(c2), _t3557);
                        (void)_t3558;
                        ;
                        if (_t3558) {
                            I64 _t3546 = 13;
                            (void)_t3546;
                            byte_val = _t3546;
                            ;
                        } else {
                            U8 _t3555 = 92;
                            (void)_t3555;
                            Bool _t3556 = U8_eq(DEREF(c2), _t3555);
                            (void)_t3556;
                            ;
                            if (_t3556) {
                                I64 _t3547 = 92;
                                (void)_t3547;
                                byte_val = _t3547;
                                ;
                            } else {
                                U8 _t3553 = 39;
                                (void)_t3553;
                                Bool _t3554 = U8_eq(DEREF(c2), _t3553);
                                (void)_t3554;
                                ;
                                if (_t3554) {
                                    I64 _t3548 = 39;
                                    (void)_t3548;
                                    byte_val = _t3548;
                                    ;
                                } else {
                                    U8 _t3551 = 48;
                                    (void)_t3551;
                                    Bool _t3552 = U8_eq(DEREF(c2), _t3551);
                                    (void)_t3552;
                                    ;
                                    if (_t3552) {
                                        I64 _t3549 = 0;
                                        (void)_t3549;
                                        byte_val = _t3549;
                                        ;
                                    } else {
                                        I64 _t3550 = U8_to_i64(DEREF(c2));
                                        (void)_t3550;
                                        byte_val = _t3550;
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
                U64_delete(_t3561, &(Bool){1});
                ;
            }
            ;
        } else {
            U64 _t3570; { U64 *_hp = (U64 *)Str_len(ch); _t3570 = *_hp; free(_hp); }
            (void)_t3570;
            U64 _t3571 = 0;
            (void)_t3571;
            Bool _t3572; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3570}, &(U64){_t3571}); _t3572 = *_hp; free(_hp); }
            (void)_t3572;
            ;
            ;
            if (_t3572) {
                U64 *_t3567 = malloc(sizeof(U64));
                *_t3567 = 0;
                (void)_t3567;
                U8 *_t3568 = Str_get(ch, _t3567);
                (void)_t3568;
                I64 _t3569 = U8_to_i64(DEREF(_t3568));
                (void)_t3569;
                U64_delete(_t3567, &(Bool){1});
                byte_val = _t3569;
                ;
            }
            ;
        }
        ;
        Str_delete(ch, &(Bool){1});
        Str *_t3582 = I64_to_str(&(I64){byte_val});
        (void)_t3582;
        ;
        ExprData *_t3583 = ExprData_LiteralNum(_t3582);
        (void)_t3583;
        Str_delete(_t3582, &(Bool){1});
        e = Expr_new(_t3583, t_line, t_col, &p->path);
        ExprData_delete(_t3583, &(Bool){1});
        TilType_delete(&e->til_type, &(Bool){0});
        { TilType *_fa = TilType_clone(TilType_U8()); e->til_type = *_fa; free(_fa); }
        Bool _t3584 = 1;
        (void)_t3584;
        e_set = _t3584;
        ;
    }
    ;
    Bool _t3735; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t3735 = *_hp; free(_hp); }
    (void)_t3735;
    Bool _t3736; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t3736 = *_hp; free(_hp); }
    (void)_t3736;
    Bool _t3737 = Bool_not(e_set);
    (void)_t3737;
    Bool _t3738 = Bool_or(_t3735, _t3736);
    (void)_t3738;
    ;
    ;
    Bool _t3739 = Bool_and(_t3737, _t3738);
    (void)_t3739;
    ;
    ;
    if (_t3739) {
        Token *_t3585 = advance(p);
        (void)_t3585;
        Str *_t3586 = Str_clone(&t->text);
        (void)_t3586;
        ExprData *_t3587 = ExprData_LiteralBool(_t3586);
        (void)_t3587;
        Str_delete(_t3586, &(Bool){1});
        e = Expr_new(_t3587, t_line, t_col, &p->path);
        ExprData_delete(_t3587, &(Bool){1});
        Bool _t3588 = 1;
        (void)_t3588;
        e_set = _t3588;
        ;
    }
    ;
    Bool _t3740 = Bool_not(e_set);
    (void)_t3740;
    Bool _t3741; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwNull()); _t3741 = *_hp; free(_hp); }
    (void)_t3741;
    Bool _t3742 = Bool_and(_t3740, _t3741);
    (void)_t3742;
    ;
    ;
    if (_t3742) {
        Token *_t3589 = advance(p);
        (void)_t3589;
        e = Expr_new(ExprData_LiteralNull(), t_line, t_col, &p->path);
        Bool _t3590 = 1;
        (void)_t3590;
        e_set = _t3590;
        ;
    }
    ;
    Bool _t3743 = Bool_not(e_set);
    (void)_t3743;
    Bool _t3744; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t3744 = *_hp; free(_hp); }
    (void)_t3744;
    Bool _t3745 = Bool_and(_t3743, _t3744);
    (void)_t3745;
    ;
    ;
    if (_t3745) {
        Token *_t3626 = advance(p);
        (void)_t3626;
        Str *name = Str_clone(&t->text);
        (void)name;
        Str *_t3627 = Str_lit("__LOC__", 7ULL);
        (void)_t3627;
        Bool _t3628; { Bool *_hp = (Bool *)Str_eq(name, _t3627); _t3628 = *_hp; free(_hp); }
        (void)_t3628;
        Str_delete(_t3627, &(Bool){1});
        if (_t3628) {
            Str *_t3591 = Str_lit("Str", 3ULL);
            (void)_t3591;
            U64 _t3592; { U64 *_hp = (U64 *)Str_size(); _t3592 = *_hp; free(_hp); }
            (void)_t3592;
            U64 _t3593 = 5;
            (void)_t3593;
            Array *_va67 = Array_new(_t3591, &(U64){_t3592}, &(U64){_t3593});
            (void)_va67;
            Str_delete(_t3591, &(Bool){1});
            ;
            ;
            U64 _t3594 = 0;
            (void)_t3594;
            Str *_t3595 = Str_clone(&p->path);
            (void)_t3595;
            Array_set(_va67, &(U64){_t3594}, _t3595);
            ;
            U64 _t3596 = 1;
            (void)_t3596;
            Str *_t3597 = Str_lit(":", 1ULL);
            (void)_t3597;
            Array_set(_va67, &(U64){_t3596}, _t3597);
            ;
            U64 _t3598 = 2;
            (void)_t3598;
            Str *_t3599 = U32_to_str(&(U32){t_line});
            (void)_t3599;
            Array_set(_va67, &(U64){_t3598}, _t3599);
            ;
            U64 _t3600 = 3;
            (void)_t3600;
            Str *_t3601 = Str_lit(":", 1ULL);
            (void)_t3601;
            Array_set(_va67, &(U64){_t3600}, _t3601);
            ;
            U64 _t3602 = 4;
            (void)_t3602;
            Str *_t3603 = U32_to_str(&(U32){t_col});
            (void)_t3603;
            Array_set(_va67, &(U64){_t3602}, _t3603);
            ;
            Str *_t3604 = format(_va67);
            (void)_t3604;
            ExprData *_t3605 = ExprData_LiteralStr(_t3604);
            (void)_t3605;
            Str_delete(_t3604, &(Bool){1});
            e = Expr_new(_t3605, t_line, t_col, &p->path);
            ExprData_delete(_t3605, &(Bool){1});
            Bool _t3606 = 1;
            (void)_t3606;
            e_set = _t3606;
            ;
        } else {
            Str *_t3624 = Str_lit("__FILE__", 8ULL);
            (void)_t3624;
            Bool _t3625; { Bool *_hp = (Bool *)Str_eq(name, _t3624); _t3625 = *_hp; free(_hp); }
            (void)_t3625;
            Str_delete(_t3624, &(Bool){1});
            if (_t3625) {
                Str *_t3607 = Str_clone(&p->path);
                (void)_t3607;
                ExprData *_t3608 = ExprData_LiteralStr(_t3607);
                (void)_t3608;
                Str_delete(_t3607, &(Bool){1});
                e = Expr_new(_t3608, t_line, t_col, &p->path);
                ExprData_delete(_t3608, &(Bool){1});
                Bool _t3609 = 1;
                (void)_t3609;
                e_set = _t3609;
                ;
            } else {
                Str *_t3622 = Str_lit("__LINE__", 8ULL);
                (void)_t3622;
                Bool _t3623; { Bool *_hp = (Bool *)Str_eq(name, _t3622); _t3623 = *_hp; free(_hp); }
                (void)_t3623;
                Str_delete(_t3622, &(Bool){1});
                if (_t3623) {
                    Str *_t3610 = U32_to_str(&(U32){t_line});
                    (void)_t3610;
                    ExprData *_t3611 = ExprData_LiteralNum(_t3610);
                    (void)_t3611;
                    Str_delete(_t3610, &(Bool){1});
                    e = Expr_new(_t3611, t_line, t_col, &p->path);
                    ExprData_delete(_t3611, &(Bool){1});
                    Bool _t3612 = 1;
                    (void)_t3612;
                    e_set = _t3612;
                    ;
                } else {
                    Str *_t3620 = Str_lit("__COL__", 7ULL);
                    (void)_t3620;
                    Bool _t3621; { Bool *_hp = (Bool *)Str_eq(name, _t3620); _t3621 = *_hp; free(_hp); }
                    (void)_t3621;
                    Str_delete(_t3620, &(Bool){1});
                    if (_t3621) {
                        Str *_t3613 = U32_to_str(&(U32){t_col});
                        (void)_t3613;
                        ExprData *_t3614 = ExprData_LiteralNum(_t3613);
                        (void)_t3614;
                        Str_delete(_t3613, &(Bool){1});
                        e = Expr_new(_t3614, t_line, t_col, &p->path);
                        ExprData_delete(_t3614, &(Bool){1});
                        Bool _t3615 = 1;
                        (void)_t3615;
                        e_set = _t3615;
                        ;
                    } else {
                        Bool _t3619 = check(p, TokenType_LParen());
                        (void)_t3619;
                        if (_t3619) {
                            e = parse_call(p, name, t_line, t_col);
                            Bool _t3616 = 1;
                            (void)_t3616;
                            e_set = _t3616;
                            ;
                        } else {
                            ExprData *_t3617 = ExprData_Ident(name);
                            (void)_t3617;
                            e = Expr_new(_t3617, t_line, t_col, &p->path);
                            ExprData_delete(_t3617, &(Bool){1});
                            Bool _t3618 = 1;
                            (void)_t3618;
                            e_set = _t3618;
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
    Bool _t3746; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFunc()); _t3746 = *_hp; free(_hp); }
    (void)_t3746;
    Bool _t3747; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwProc()); _t3747 = *_hp; free(_hp); }
    (void)_t3747;
    Bool _t3748 = Bool_or(_t3746, _t3747);
    (void)_t3748;
    ;
    ;
    Bool _t3749; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTest()); _t3749 = *_hp; free(_hp); }
    (void)_t3749;
    Bool _t3750 = Bool_or(_t3748, _t3749);
    (void)_t3750;
    ;
    ;
    Bool _t3751; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMacro()); _t3751 = *_hp; free(_hp); }
    (void)_t3751;
    Bool _t3752 = Bool_or(_t3750, _t3751);
    (void)_t3752;
    ;
    ;
    Bool _t3753; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtFunc()); _t3753 = *_hp; free(_hp); }
    (void)_t3753;
    Bool _t3754 = Bool_or(_t3752, _t3753);
    (void)_t3754;
    ;
    ;
    Bool _t3755; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtProc()); _t3755 = *_hp; free(_hp); }
    (void)_t3755;
    Bool _t3756 = Bool_not(e_set);
    (void)_t3756;
    Bool _t3757 = Bool_or(_t3754, _t3755);
    (void)_t3757;
    ;
    ;
    Bool _t3758 = Bool_and(_t3756, _t3757);
    (void)_t3758;
    ;
    ;
    if (_t3758) {
        Expr *_t3629 = parse_func_def(p);
        (void)_t3629;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3629;
    }
    ;
    Bool _t3759; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwStruct()); _t3759 = *_hp; free(_hp); }
    (void)_t3759;
    Bool _t3760; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtStruct()); _t3760 = *_hp; free(_hp); }
    (void)_t3760;
    Bool _t3761 = Bool_not(e_set);
    (void)_t3761;
    Bool _t3762 = Bool_or(_t3759, _t3760);
    (void)_t3762;
    ;
    ;
    Bool _t3763 = Bool_and(_t3761, _t3762);
    (void)_t3763;
    ;
    ;
    if (_t3763) {
        Expr *_t3630 = parse_struct_def(p);
        (void)_t3630;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3630;
    }
    ;
    Bool _t3764 = Bool_not(e_set);
    (void)_t3764;
    Bool _t3765; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwEnum()); _t3765 = *_hp; free(_hp); }
    (void)_t3765;
    Bool _t3766 = Bool_and(_t3764, _t3765);
    (void)_t3766;
    ;
    ;
    if (_t3766) {
        Expr *_t3631 = parse_enum_def(p);
        (void)_t3631;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3631;
    }
    ;
    Bool _t3767 = Bool_not(e_set);
    (void)_t3767;
    Bool _t3768; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t3768 = *_hp; free(_hp); }
    (void)_t3768;
    Bool _t3769 = Bool_and(_t3767, _t3768);
    (void)_t3769;
    ;
    ;
    if (_t3769) {
        Token *_t3656 = advance(p);
        (void)_t3656;
        Expr *first = parse_expression(p);
        (void)first;
        Bool _t3657 = check(p, TokenType_Colon());
        (void)_t3657;
        if (_t3657) {
            e = Expr_new(ExprData_MapLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Token *_t3643 = advance(p);
            (void)_t3643;
            Expr *_t3644 = parse_expression(p);
            (void)_t3644;
            Expr_add_child(e, _t3644);
            Bool _t3645 = check(p, TokenType_Comma());
            (void)_t3645;
            if (_t3645) {
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
                Token *_t3640 = expect_token(p, TokenType_Colon());
                (void)_t3640;
                Expr *_t3641 = parse_expression(p);
                (void)_t3641;
                Expr_add_child(e, _t3641);
                Bool _t3642 = check(p, TokenType_Comma());
                (void)_t3642;
                if (_t3642) {
                    Token *_t3634 = advance(p);
                    (void)_t3634;
                }
                ;
            }
        } else {
            e = Expr_new(ExprData_SetLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Bool _t3655 = check(p, TokenType_Comma());
            (void)_t3655;
            if (_t3655) {
                Token *_t3646 = advance(p);
                (void)_t3646;
            }
            ;
            while (1) {
                Bool _t3649 = check(p, TokenType_RBrace());
                (void)_t3649;
                Bool _t3650 = check(p, TokenType_Eof());
                (void)_t3650;
                Bool _t3651 = Bool_not(_t3649);
                (void)_t3651;
                ;
                Bool _t3652 = Bool_not(_t3650);
                (void)_t3652;
                ;
                Bool _wcond3647 = Bool_and(_t3651, _t3652);
                (void)_wcond3647;
                ;
                ;
                if (_wcond3647) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3653 = parse_expression(p);
                (void)_t3653;
                Expr_add_child(e, _t3653);
                Bool _t3654 = check(p, TokenType_Comma());
                (void)_t3654;
                if (_t3654) {
                    Token *_t3648 = advance(p);
                    (void)_t3648;
                }
                ;
            }
        }
        ;
        Token *_t3658 = expect_token(p, TokenType_RBrace());
        (void)_t3658;
        Bool _t3659 = 1;
        (void)_t3659;
        e_set = _t3659;
        ;
    }
    ;
    Bool _t3770 = Bool_not(e_set);
    (void)_t3770;
    ;
    if (_t3770) {
        Str *_t3660 = Str_lit("Str", 3ULL);
        (void)_t3660;
        U64 _t3661; { U64 *_hp = (U64 *)Str_size(); _t3661 = *_hp; free(_hp); }
        (void)_t3661;
        U64 _t3662 = 8;
        (void)_t3662;
        Array *_va68 = Array_new(_t3660, &(U64){_t3661}, &(U64){_t3662});
        (void)_va68;
        Str_delete(_t3660, &(Bool){1});
        ;
        ;
        U64 _t3663 = 0;
        (void)_t3663;
        Str *_t3664 = Str_clone(&p->path);
        (void)_t3664;
        Array_set(_va68, &(U64){_t3663}, _t3664);
        ;
        U64 _t3665 = 1;
        (void)_t3665;
        Str *_t3666 = Str_lit(":", 1ULL);
        (void)_t3666;
        Array_set(_va68, &(U64){_t3665}, _t3666);
        ;
        U64 _t3667 = 2;
        (void)_t3667;
        Str *_t3668 = U32_to_str(&(U32){t_line});
        (void)_t3668;
        Array_set(_va68, &(U64){_t3667}, _t3668);
        ;
        U64 _t3669 = 3;
        (void)_t3669;
        Str *_t3670 = Str_lit(":", 1ULL);
        (void)_t3670;
        Array_set(_va68, &(U64){_t3669}, _t3670);
        ;
        U64 _t3671 = 4;
        (void)_t3671;
        Str *_t3672 = U32_to_str(&(U32){t_col});
        (void)_t3672;
        Array_set(_va68, &(U64){_t3671}, _t3672);
        ;
        U64 _t3673 = 5;
        (void)_t3673;
        Str *_t3674 = Str_lit(": unexpected token '", 20ULL);
        (void)_t3674;
        Array_set(_va68, &(U64){_t3673}, _t3674);
        ;
        U64 _t3675 = 6;
        (void)_t3675;
        Str *_t3676 = Str_clone(&t->text);
        (void)_t3676;
        Array_set(_va68, &(U64){_t3675}, _t3676);
        ;
        U64 _t3677 = 7;
        (void)_t3677;
        Str *_t3678 = Str_lit("'", 1ULL);
        (void)_t3678;
        Array_set(_va68, &(U64){_t3677}, _t3678);
        ;
        Str *_t3679 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:536:15", 64ULL);
        (void)_t3679;
        panic(_t3679, _va68);
        Str_delete(_t3679, &(Bool){1});
    }
    ;
    ;
    ;
    while (1) {
        Bool _wcond3680 = check(p, TokenType_Dot());
        (void)_wcond3680;
        if (_wcond3680) {
        } else {
            ;
            break;
        }
        ;
        Token *_t3713 = advance(p);
        (void)_t3713;
        U32 f_line = peek_line(p);
        (void)f_line;
        U32 f_col = peek_col(p);
        (void)f_col;
        Str *fname = expect_text(p, TokenType_Ident());
        (void)fname;
        Bool _t3714 = check(p, TokenType_LParen());
        (void)_t3714;
        if (_t3714) {
            Token *_t3707 = advance(p);
            (void)_t3707;
            ExprData *_t3708 = ExprData_FieldAccess(fname);
            (void)_t3708;
            Expr *callee = Expr_new(_t3708, f_line, f_col, &p->path);
            (void)callee;
            ExprData_delete(_t3708, &(Bool){1});
            Expr *_t3709 = Expr_clone(e);
            (void)_t3709;
            Expr_add_child(callee, _t3709);
            Expr *mcall = Expr_new(ExprData_FCall(), f_line, f_col, &p->path);
            (void)mcall;
            Expr_add_child(mcall, callee);
            while (1) {
                Bool _t3699 = check(p, TokenType_RParen());
                (void)_t3699;
                Bool _t3700 = check(p, TokenType_Eof());
                (void)_t3700;
                Bool _t3701 = Bool_not(_t3699);
                (void)_t3701;
                ;
                Bool _t3702 = Bool_not(_t3700);
                (void)_t3702;
                ;
                Bool _wcond3681 = Bool_and(_t3701, _t3702);
                (void)_wcond3681;
                ;
                ;
                if (_wcond3681) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3703 = check(p, TokenType_Ident());
                (void)_t3703;
                if (_t3703) {
                    U64 _t3692 = 1;
                    (void)_t3692;
                    U64 _t3693 = U64_add(p->pos, _t3692);
                    (void)_t3693;
                    ;
                    U64 _t3694; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3694 = *_hp; free(_hp); }
                    (void)_t3694;
                    Bool _t3695; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3693}, &(U64){_t3694}); _t3695 = *_hp; free(_hp); }
                    (void)_t3695;
                    ;
                    ;
                    if (_t3695) {
                        U64 _t3687 = 1;
                        (void)_t3687;
                        U64 _t3688 = U64_add(p->pos, _t3687);
                        (void)_t3688;
                        ;
                        I64 _t3689 = U64_to_i64(_t3688);
                        (void)_t3689;
                        ;
                        U64 *_t3690 = malloc(sizeof(U64)); *_t3690 = I64_to_u64(_t3689);
                        (void)_t3690;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3690);
                        (void)nt;
                        Bool _t3691; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3691 = *_hp; free(_hp); }
                        (void)_t3691;
                        U64_delete(_t3690, &(Bool){1});
                        if (_t3691) {
                            U32 na_line = peek_line(p);
                            (void)na_line;
                            U32 na_col = peek_col(p);
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3683 = advance(p);
                            (void)_t3683;
                            ExprData *_t3684 = ExprData_NamedArg(aname);
                            (void)_t3684;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3684, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3684, &(Bool){1});
                            ;
                            ;
                            Expr *_t3685 = parse_expression(p);
                            (void)_t3685;
                            Expr_add_child(na, _t3685);
                            Expr_add_child(mcall, na);
                            Bool _t3686 = check(p, TokenType_Comma());
                            (void)_t3686;
                            if (_t3686) {
                                Token *_t3682 = advance(p);
                                (void)_t3682;
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
                Bool _t3704 = check(p, TokenType_KwOwn());
                (void)_t3704;
                if (_t3704) {
                    Token *_t3696 = advance(p);
                    (void)_t3696;
                    Bool _t3697 = 1;
                    (void)_t3697;
                    is_own_arg = _t3697;
                    ;
                }
                ;
                Expr *marg = parse_expression(p);
                (void)marg;
                Bool _t3705 = Bool_clone(&(Bool){is_own_arg});
                (void)_t3705;
                ;
                marg->is_own_arg = _t3705;
                ;
                Expr_add_child(mcall, marg);
                Bool _t3706 = check(p, TokenType_Comma());
                (void)_t3706;
                if (_t3706) {
                    Token *_t3698 = advance(p);
                    (void)_t3698;
                }
                ;
            }
            Token *_t3710 = expect_token(p, TokenType_RParen());
            (void)_t3710;
            e = Expr_clone(mcall);
            Expr_delete(mcall, &(Bool){1});
        } else {
            ExprData *_t3711 = ExprData_FieldAccess(fname);
            (void)_t3711;
            Expr *access = Expr_new(_t3711, f_line, f_col, &p->path);
            (void)access;
            ExprData_delete(_t3711, &(Bool){1});
            Expr *_t3712 = Expr_clone(e);
            (void)_t3712;
            Expr_add_child(access, _t3712);
            e = Expr_clone(access);
            Expr_delete(access, &(Bool){1});
        }
        ;
        ;
        ;
        Str_delete(fname, &(Bool){1});
    }
    Bool _t3771 = check(p, TokenType_DotDot());
    (void)_t3771;
    if (_t3771) {
        U32 dt_line = peek_line(p);
        (void)dt_line;
        U32 dt_col = peek_col(p);
        (void)dt_col;
        Token *_t3715 = advance(p);
        (void)_t3715;
        Expr *rhs = parse_expression(p);
        (void)rhs;
        Str *_t3716 = Str_lit("Range", 5ULL);
        (void)_t3716;
        Str *_t3717 = Str_clone(_t3716);
        (void)_t3717;
        Str_delete(_t3716, &(Bool){1});
        ExprData *_t3718 = ExprData_Ident(_t3717);
        (void)_t3718;
        Str_delete(_t3717, &(Bool){1});
        Expr *range_ident = Expr_new(_t3718, dt_line, dt_col, &p->path);
        (void)range_ident;
        ExprData_delete(_t3718, &(Bool){1});
        Str *_t3719 = Str_lit("new", 3ULL);
        (void)_t3719;
        Str *_t3720 = Str_clone(_t3719);
        (void)_t3720;
        Str_delete(_t3719, &(Bool){1});
        ExprData *_t3721 = ExprData_FieldAccess(_t3720);
        (void)_t3721;
        Str_delete(_t3720, &(Bool){1});
        Expr *new_access = Expr_new(_t3721, dt_line, dt_col, &p->path);
        (void)new_access;
        ExprData_delete(_t3721, &(Bool){1});
        Expr_add_child(new_access, range_ident);
        Expr *rcall = Expr_new(ExprData_FCall(), dt_line, dt_col, &p->path);
        (void)rcall;
        ;
        ;
        Expr_add_child(rcall, new_access);
        Expr *_t3722 = Expr_clone(e);
        (void)_t3722;
        Expr_add_child(rcall, _t3722);
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
        Token *_t3772 = advance(p);
        (void)_t3772;
        Bool _t3773 = Bool_clone(&(Bool){is_mut});
        (void)_t3773;
        Bool _t3774 = 0;
        (void)_t3774;
        Bool _t3775 = 0;
        (void)_t3775;
        Bool _t3776 = Bool_clone(&(Bool){is_own});
        (void)_t3776;
        I32 _t3777 = 0;
        (void)_t3777;
        I32 _t3778 = 0;
        (void)_t3778;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3773;
        dd->is_namespace = _t3774;
        dd->is_ref = _t3775;
        dd->is_own = _t3776;
        dd->field_offset = _t3777;
        dd->field_size = _t3778;
        dd->field_struct_def = NULL;
        dd->fn_sig = NULL;
        (void)dd;
        ;
        ;
        ;
        ;
        ;
        ;
        ExprData *_t3779 = ExprData_Decl(dd);
        (void)_t3779;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3779, t_line, t_col, &p->path);
        (void)decl;
        ExprData_delete(_t3779, &(Bool){1});
        Expr *_t3780 = parse_expression(p);
        (void)_t3780;
        Expr_add_child(decl, _t3780);
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
        Token *_t3892 = advance(p);
        (void)_t3892;
        Bool _t3893 = check(p, TokenType_KwFunc());
        (void)_t3893;
        Bool _t3894 = check(p, TokenType_KwProc());
        (void)_t3894;
        Bool _t3895 = Bool_or(_t3893, _t3894);
        (void)_t3895;
        ;
        ;
        if (_t3895) {
            Expr *sig = parse_func_def(p);
            (void)sig;
            Token *_t3798 = expect_token(p, TokenType_Eq());
            (void)_t3798;
            Token *_t3799 = expect_token(p, TokenType_LParen());
            (void)_t3799;
            Bool _t3800; { Bool *_hp = (Bool *)ExprData_is_FuncDef(&sig->data); _t3800 = *_hp; free(_hp); }
            (void)_t3800;
            if (_t3800) {
                FunctionDef *sfd = ExprData_get_FuncDef(&sig->data);
                (void)sfd;
                Str *_t3795 = Str_lit("Str", 3ULL);
                (void)_t3795;
                U64 _t3796; { U64 *_hp = (U64 *)Str_size(); _t3796 = *_hp; free(_hp); }
                (void)_t3796;
                Vec *new_names = Vec_new(_t3795, &(U64){_t3796});
                (void)new_names;
                Str_delete(_t3795, &(Bool){1});
                ;
                Vec_delete(new_names, &(Bool){1});
                {
                    U64 _fi3781 = 0;
                    (void)_fi3781;
                    while (1) {
                        U64 _t3784 = 0;
                        (void)_t3784;
                        U64 _t3785; { U64 *_hp = (U64 *)Vec_len(&sfd->params); _t3785 = *_hp; free(_hp); }
                        (void)_t3785;
                        Range *_t3786 = Range_new(_t3784, _t3785);
                        (void)_t3786;
                        ;
                        ;
                        U64 _t3787; { U64 *_hp = (U64 *)Range_len(_t3786); _t3787 = *_hp; free(_hp); }
                        (void)_t3787;
                        Range_delete(_t3786, &(Bool){1});
                        Bool _wcond3782; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3781}, &(U64){_t3787}); _wcond3782 = *_hp; free(_hp); }
                        (void)_wcond3782;
                        ;
                        if (_wcond3782) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 _t3788 = 0;
                        (void)_t3788;
                        U64 _t3789; { U64 *_hp = (U64 *)Vec_len(&sfd->params); _t3789 = *_hp; free(_hp); }
                        (void)_t3789;
                        Range *_t3790 = Range_new(_t3788, _t3789);
                        (void)_t3790;
                        ;
                        ;
                        U64 *pi = Range_get(_t3790, _fi3781);
                        (void)pi;
                        Range_delete(_t3790, &(Bool){1});
                        U64 _t3791 = 1;
                        (void)_t3791;
                        U64 _t3792 = U64_add(_fi3781, _t3791);
                        (void)_t3792;
                        ;
                        _fi3781 = _t3792;
                        ;
                        U64 _t3793 = 0;
                        (void)_t3793;
                        Bool _t3794; { Bool *_hp = (Bool *)U64_gt(pi, &(U64){_t3793}); _t3794 = *_hp; free(_hp); }
                        (void)_t3794;
                        ;
                        if (_t3794) {
                            Token *_t3783 = expect_token(p, TokenType_Comma());
                            (void)_t3783;
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
                    ;
                }
                ExprData_delete(&sig->data, &(Bool){0});
                { ExprData *_fa = ExprData_FuncDef(sfd); sig->data = *_fa; free(_fa); }
                FunctionDef_delete(sfd, &(Bool){1});
            }
            ;
            Bool _t3801 = check(p, TokenType_Comma());
            (void)_t3801;
            if (_t3801) {
                Token *_t3797 = advance(p);
                (void)_t3797;
            }
            ;
            Token *_t3802 = expect_token(p, TokenType_RParen());
            (void)_t3802;
            Token *_t3803 = expect_token(p, TokenType_LBrace());
            (void)_t3803;
            Expr *_t3804 = parse_block(p);
            (void)_t3804;
            Expr_add_child(sig, _t3804);
            Bool _t3805 = Bool_clone(&(Bool){is_mut});
            (void)_t3805;
            Bool _t3806 = 0;
            (void)_t3806;
            Bool _t3807 = 0;
            (void)_t3807;
            Bool _t3808 = Bool_clone(&(Bool){is_own});
            (void)_t3808;
            I32 _t3809 = 0;
            (void)_t3809;
            I32 _t3810 = 0;
            (void)_t3810;
            Declaration *dd = malloc(sizeof(Declaration));
            { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
            dd->is_mut = _t3805;
            dd->is_namespace = _t3806;
            dd->is_ref = _t3807;
            dd->is_own = _t3808;
            dd->field_offset = _t3809;
            dd->field_size = _t3810;
            dd->field_struct_def = NULL;
            dd->fn_sig = NULL;
            (void)dd;
            ;
            ;
            ;
            ;
            ;
            ;
            ExprData *_t3811 = ExprData_Decl(dd);
            (void)_t3811;
            Declaration_delete(dd, &(Bool){1});
            Expr *decl = Expr_new(_t3811, t_line, t_col, &p->path);
            (void)decl;
            ExprData_delete(_t3811, &(Bool){1});
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
        Str *_t3896 = Str_lit("Fn", 2ULL);
        (void)_t3896;
        Bool _t3897; { Bool *_hp = (Bool *)Str_eq(type_name, _t3896); _t3897 = *_hp; free(_hp); }
        (void)_t3897;
        Str_delete(_t3896, &(Bool){1});
        if (_t3897) {
            Str *syn_name = parse_fn_signature(p, t_line, t_col);
            (void)syn_name;
            U64 _t3812; { U64 *_hp = (U64 *)Str_len(syn_name); _t3812 = *_hp; free(_hp); }
            (void)_t3812;
            U64 _t3813 = 0;
            (void)_t3813;
            Bool _t3814; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3812}, &(U64){_t3813}); _t3814 = *_hp; free(_hp); }
            (void)_t3814;
            ;
            ;
            if (_t3814) {
                type_name = Str_clone(syn_name);
            }
            ;
            Str_delete(syn_name, &(Bool){1});
        }
        ;
        Token *_t3898 = expect_token(p, TokenType_Eq());
        (void)_t3898;
        Bool _t3899 = check(p, TokenType_LParen());
        (void)_t3899;
        if (_t3899) {
            U64 saved = p->pos;
            (void)saved;
            Token *_t3888 = advance(p);
            (void)_t3888;
            Bool is_fsf = 1;
            (void)is_fsf;
            while (1) {
                Bool _t3818 = check(p, TokenType_RParen());
                (void)_t3818;
                Bool _t3819 = check(p, TokenType_Eof());
                (void)_t3819;
                Bool _t3820 = Bool_not(_t3818);
                (void)_t3820;
                ;
                Bool _t3821 = Bool_not(_t3819);
                (void)_t3821;
                ;
                Bool _wcond3815 = Bool_and(_t3820, _t3821);
                (void)_wcond3815;
                ;
                ;
                if (_wcond3815) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3822 = check(p, TokenType_Ident());
                (void)_t3822;
                Bool _t3823 = Bool_not(_t3822);
                (void)_t3823;
                ;
                if (_t3823) {
                    Bool _t3816 = 0;
                    (void)_t3816;
                    is_fsf = _t3816;
                    ;
                    ;
                    break;
                }
                ;
                Token *_t3824 = advance(p);
                (void)_t3824;
                Bool _t3825 = check(p, TokenType_Comma());
                (void)_t3825;
                if (_t3825) {
                    Token *_t3817 = advance(p);
                    (void)_t3817;
                }
                ;
            }
            Bool _t3889 = check(p, TokenType_RParen());
            (void)_t3889;
            Bool _t3890 = Bool_and(is_fsf, _t3889);
            (void)_t3890;
            ;
            if (_t3890) {
                Token *_t3827 = advance(p);
                (void)_t3827;
                Bool _t3828 = check(p, TokenType_LBrace());
                (void)_t3828;
                Bool _t3829 = Bool_not(_t3828);
                (void)_t3829;
                ;
                if (_t3829) {
                    Bool _t3826 = 0;
                    (void)_t3826;
                    is_fsf = _t3826;
                    ;
                }
                ;
            } else {
                Bool _t3830 = 0;
                (void)_t3830;
                is_fsf = _t3830;
                ;
            }
            ;
            U64 _t3891 = U64_clone(&(U64){saved});
            (void)_t3891;
            ;
            p->pos = _t3891;
            ;
            if (is_fsf) {
                Token *_t3848 = expect_token(p, TokenType_LParen());
                (void)_t3848;
                Str *_t3849 = Str_lit("Str", 3ULL);
                (void)_t3849;
                U64 _t3850; { U64 *_hp = (U64 *)Str_size(); _t3850 = *_hp; free(_hp); }
                (void)_t3850;
                Vec *pnames = Vec_new(_t3849, &(U64){_t3850});
                (void)pnames;
                Str_delete(_t3849, &(Bool){1});
                ;
                while (1) {
                    Bool _t3833 = check(p, TokenType_RParen());
                    (void)_t3833;
                    Bool _wcond3831 = Bool_not(_t3833);
                    (void)_wcond3831;
                    ;
                    if (_wcond3831) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *pn = expect_text(p, TokenType_Ident());
                    (void)pn;
                    Vec_push(pnames, pn);
                    Bool _t3834 = check(p, TokenType_Comma());
                    (void)_t3834;
                    if (_t3834) {
                        Token *_t3832 = advance(p);
                        (void)_t3832;
                    }
                    ;
                }
                Token *_t3851 = expect_token(p, TokenType_RParen());
                (void)_t3851;
                Token *_t3852 = expect_token(p, TokenType_LBrace());
                (void)_t3852;
                Expr *body = parse_block(p);
                (void)body;
                Str *_t3853 = Str_lit("Param", 5ULL);
                (void)_t3853;
                U64 _t3854; { U64 *_hp = (U64 *)Param_size(); _t3854 = *_hp; free(_hp); }
                (void)_t3854;
                Str *_t3855 = Str_lit("Str", 3ULL);
                (void)_t3855;
                U64 _t3856; { U64 *_hp = (U64 *)Str_size(); _t3856 = *_hp; free(_hp); }
                (void)_t3856;
                Str *_t3857 = Str_lit("Expr", 4ULL);
                (void)_t3857;
                U64 _t3858; { U64 *_hp = (U64 *)Expr_size(); _t3858 = *_hp; free(_hp); }
                (void)_t3858;
                I64 _t3859 = 0;
                (void)_t3859;
                I64 _t3860 = 1;
                (void)_t3860;
                I64 _t3861 = I64_sub(_t3859, _t3860);
                (void)_t3861;
                ;
                ;
                I64 _t3862 = 0;
                (void)_t3862;
                I64 _t3863 = 1;
                (void)_t3863;
                I64 _t3864 = I64_sub(_t3862, _t3863);
                (void)_t3864;
                ;
                ;
                U32 _t3865 = 0;
                (void)_t3865;
                I32 _t3866 = I64_to_i32(_t3861);
                (void)_t3866;
                ;
                I32 _t3867 = I64_to_i32(_t3864);
                (void)_t3867;
                ;
                Bool _t3868 = 0;
                (void)_t3868;
                Bool _t3869 = 0;
                (void)_t3869;
                FunctionDef *ffd = malloc(sizeof(FunctionDef));
                { FuncType *_ca = FuncType_clone(FuncType_Func()); ffd->func_type = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3853, &(U64){_t3854}); ffd->params = *_ca; free(_ca); }
                ffd->nparam = _t3865;
                { Map *_ca = Map_new(_t3855, &(U64){_t3856}, _t3857, &(U64){_t3858}); ffd->param_defaults = *_ca; free(_ca); }
                { Str *_ca = Str_clone(Str_lit("", 0ULL)); ffd->return_type = *_ca; free(_ca); }
                ffd->variadic_index = _t3866;
                ffd->kwargs_index = _t3867;
                ffd->return_is_ref = _t3868;
                ffd->return_is_shallow = _t3869;
                (void)ffd;
                Str_delete(_t3853, &(Bool){1});
                ;
                Str_delete(_t3855, &(Bool){1});
                ;
                Str_delete(_t3857, &(Bool){1});
                ;
                ;
                ;
                ;
                ;
                ;
                FuncType_delete(&ffd->func_type, &(Bool){0});
                { FuncType *_fa = FuncType_clone(FuncType_Func()); ffd->func_type = *_fa; free(_fa); }
                I64 _t3870 = 0;
                (void)_t3870;
                I64 _t3871 = 1;
                (void)_t3871;
                I64 _t3872 = I64_sub(_t3870, _t3871);
                (void)_t3872;
                ;
                ;
                I32 _t3873 = I64_to_i32(_t3872);
                (void)_t3873;
                ;
                ffd->variadic_index = _t3873;
                ;
                I64 _t3874 = 0;
                (void)_t3874;
                I64 _t3875 = 1;
                (void)_t3875;
                I64 _t3876 = I64_sub(_t3874, _t3875);
                (void)_t3876;
                ;
                ;
                I32 _t3877 = I64_to_i32(_t3876);
                (void)_t3877;
                ;
                ffd->kwargs_index = _t3877;
                ;
                U64 np; { U64 *_hp = (U64 *)Vec_len(pnames); np = *_hp; free(_hp); }
                (void)np;
                {
                    U64 _fi3835 = 0;
                    (void)_fi3835;
                    while (1) {
                        U64 _t3837 = 0;
                        (void)_t3837;
                        Range *_t3838 = Range_new(_t3837, np);
                        (void)_t3838;
                        ;
                        U64 _t3839; { U64 *_hp = (U64 *)Range_len(_t3838); _t3839 = *_hp; free(_hp); }
                        (void)_t3839;
                        Range_delete(_t3838, &(Bool){1});
                        Bool _wcond3836; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3835}, &(U64){_t3839}); _wcond3836 = *_hp; free(_hp); }
                        (void)_wcond3836;
                        ;
                        if (_wcond3836) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 _t3840 = 0;
                        (void)_t3840;
                        Range *_t3841 = Range_new(_t3840, np);
                        (void)_t3841;
                        ;
                        U64 *i = Range_get(_t3841, _fi3835);
                        (void)i;
                        Range_delete(_t3841, &(Bool){1});
                        U64 _t3842 = 1;
                        (void)_t3842;
                        U64 _t3843 = U64_add(_fi3835, _t3842);
                        (void)_t3843;
                        ;
                        _fi3835 = _t3843;
                        ;
                        Str *pn = Vec_get(pnames, i);
                        (void)pn;
                        Bool _t3844 = 0;
                        (void)_t3844;
                        Bool _t3845 = 0;
                        (void)_t3845;
                        Bool _t3846 = 0;
                        (void)_t3846;
                        Param *_t3847 = malloc(sizeof(Param));
                        { Str *_ca = Str_clone(pn); _t3847->name = *_ca; free(_ca); }
                        { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t3847->ptype = *_ca; free(_ca); }
                        _t3847->is_mut = _t3844;
                        _t3847->is_own = _t3845;
                        _t3847->is_shallow = _t3846;
                        (void)_t3847;
                        ;
                        ;
                        ;
                        U64_delete(i, &(Bool){1});
                        Vec_push(&ffd->params, _t3847);
                    }
                    ;
                }
                Vec_delete(pnames, &(Bool){1});
                I64 _t3878 = U64_to_i64(np);
                (void)_t3878;
                ;
                U32 _t3879 = I64_to_u32(_t3878);
                (void)_t3879;
                ;
                ffd->nparam = _t3879;
                ;
                ExprData *_t3880 = ExprData_FuncDef(ffd);
                (void)_t3880;
                FunctionDef_delete(ffd, &(Bool){1});
                Expr *fdef = Expr_new(_t3880, t_line, t_col, &p->path);
                (void)fdef;
                ExprData_delete(_t3880, &(Bool){1});
                Expr_add_child(fdef, body);
                Bool _t3881 = Bool_clone(&(Bool){is_mut});
                (void)_t3881;
                Bool _t3882 = 0;
                (void)_t3882;
                Bool _t3883 = 0;
                (void)_t3883;
                Bool _t3884 = Bool_clone(&(Bool){is_own});
                (void)_t3884;
                I32 _t3885 = 0;
                (void)_t3885;
                I32 _t3886 = 0;
                (void)_t3886;
                Declaration *dd = malloc(sizeof(Declaration));
                { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
                { Str *_ca = Str_clone(type_name); dd->explicit_type = *_ca; free(_ca); }
                dd->is_mut = _t3881;
                dd->is_namespace = _t3882;
                dd->is_ref = _t3883;
                dd->is_own = _t3884;
                dd->field_offset = _t3885;
                dd->field_size = _t3886;
                dd->field_struct_def = NULL;
                dd->fn_sig = NULL;
                (void)dd;
                ;
                ;
                ;
                ;
                ;
                ;
                ExprData *_t3887 = ExprData_Decl(dd);
                (void)_t3887;
                Declaration_delete(dd, &(Bool){1});
                Expr *decl = Expr_new(_t3887, t_line, t_col, &p->path);
                (void)decl;
                ExprData_delete(_t3887, &(Bool){1});
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
    Str *_t3982 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:797:11", 64ULL);
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
                Str *_t4101 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:931:23", 64ULL);
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
    Str *_t4163 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:958:11", 64ULL);
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
    Str *_t4190 = Str_lit("Expr", 4ULL);
    (void)_t4190;
    U64 _t4191; { U64 *_hp = (U64 *)Expr_size(); _t4191 = *_hp; free(_hp); }
    (void)_t4191;
    I64 _t4192 = 0;
    (void)_t4192;
    Parser *p = malloc(sizeof(Parser));
    { Vec *_ca = Vec_clone(tokens); p->tokens = *_ca; free(_ca); }
    p->pos = _t4192;
    { Str *_ca = Str_clone(path); p->path = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t4190, &(U64){_t4191}); p->fn_sig_decls = *_ca; free(_ca); }
    (void)p;
    Str_delete(_t4190, &(Bool){1});
    ;
    ;
    Bool _t4193 = check(p, TokenType_KwMode());
    (void)_t4193;
    if (_t4193) {
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
    U32 _t4194 = 1;
    (void)_t4194;
    U32 _t4195 = 1;
    (void)_t4195;
    Expr *root = Expr_new(ExprData_Body(), _t4194, _t4195, &p->path);
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
    {
        U64 _fi4178 = 0;
        (void)_fi4178;
        while (1) {
            U64 _t4180 = 0;
            (void)_t4180;
            U64 _t4181; { U64 *_hp = (U64 *)Vec_len(&p->fn_sig_decls); _t4181 = *_hp; free(_hp); }
            (void)_t4181;
            Range *_t4182 = Range_new(_t4180, _t4181);
            (void)_t4182;
            ;
            ;
            U64 _t4183; { U64 *_hp = (U64 *)Range_len(_t4182); _t4183 = *_hp; free(_hp); }
            (void)_t4183;
            Range_delete(_t4182, &(Bool){1});
            Bool _wcond4179; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi4178}, &(U64){_t4183}); _wcond4179 = *_hp; free(_hp); }
            (void)_wcond4179;
            ;
            if (_wcond4179) {
            } else {
                ;
                break;
            }
            ;
            U64 _t4184 = 0;
            (void)_t4184;
            U64 _t4185; { U64 *_hp = (U64 *)Vec_len(&p->fn_sig_decls); _t4185 = *_hp; free(_hp); }
            (void)_t4185;
            Range *_t4186 = Range_new(_t4184, _t4185);
            (void)_t4186;
            ;
            ;
            U64 *i = Range_get(_t4186, _fi4178);
            (void)i;
            Range_delete(_t4186, &(Bool){1});
            U64 _t4187 = 1;
            (void)_t4187;
            U64 _t4188 = U64_add(_fi4178, _t4187);
            (void)_t4188;
            ;
            _fi4178 = _t4188;
            ;
            Expr *d = Vec_get(&p->fn_sig_decls, i);
            (void)d;
            Expr *_t4189 = Expr_clone(d);
            (void)_t4189;
            U64_delete(i, &(Bool){1});
            Expr_add_child(root, _t4189);
        }
        ;
    }
    Parser_delete(p, &(Bool){1});
    return root;
}

