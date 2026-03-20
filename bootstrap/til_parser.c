#include "til_parser.h"

Parser * Parser_clone(Parser * self) {
    (void)self;
    U64 _t3063 = U64_clone(&self->pos);
    (void)_t3063;
    Parser *_t3064 = malloc(sizeof(Parser));
    { Vec *_ca = Vec_clone(&self->tokens); _t3064->tokens = *_ca; free(_ca); }
    _t3064->pos = _t3063;
    { Str *_ca = Str_clone(&self->path); _t3064->path = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->fn_sig_decls); _t3064->fn_sig_decls = *_ca; free(_ca); }
    (void)_t3064;
    ;
    return _t3064;
}

void Parser_delete(Parser * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t3065 = 0;
    (void)_t3065;
    Vec_delete(&self->tokens, &(Bool){_t3065});
    ;
    Bool _t3066 = 0;
    (void)_t3066;
    U64_delete(&self->pos, &(Bool){_t3066});
    ;
    Bool _t3067 = 0;
    (void)_t3067;
    Str_delete(&self->path, &(Bool){_t3067});
    ;
    Bool _t3068 = 0;
    (void)_t3068;
    Vec_delete(&self->fn_sig_decls, &(Bool){_t3068});
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
    I64 _t3070 = U64_to_i64(p->pos);
    (void)_t3070;
    U64 *_t3071 = malloc(sizeof(U64)); *_t3071 = I64_to_u64(_t3070);
    (void)_t3071;
    ;
    Token *t = Vec_get(&p->tokens, _t3071);
    (void)t;
    U64_delete(_t3071, &(Bool){1});
    return t;
}

Token * advance(Parser * p) {
    (void)p;
    I64 _t3074 = U64_to_i64(p->pos);
    (void)_t3074;
    U64 *_t3075 = malloc(sizeof(U64)); *_t3075 = I64_to_u64(_t3074);
    (void)_t3075;
    ;
    Token *t = Vec_get(&p->tokens, _t3075);
    (void)t;
    Bool _t3076; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Eof()); _t3076 = *_hp; free(_hp); }
    (void)_t3076;
    Bool _t3077 = Bool_not(_t3076);
    (void)_t3077;
    ;
    if (_t3077) {
        U64 _t3072 = 1;
        (void)_t3072;
        U64 _t3073 = U64_add(p->pos, _t3072);
        (void)_t3073;
        ;
        p->pos = _t3073;
        ;
    }
    ;
    U64_delete(_t3075, &(Bool){1});
    return t;
}

Bool check(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Bool _t3078; { Bool *_hp = (Bool *)TokenType_eq(&peek(p)->type, type); _t3078 = *_hp; free(_hp); }
    (void)_t3078;
    return _t3078;
}

Token * expect_token(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Token *t = peek(p);
    (void)t;
    Bool _t3103; { Bool *_hp = (Bool *)TokenType_eq(&t->type, type); _t3103 = *_hp; free(_hp); }
    (void)_t3103;
    Bool _t3104 = Bool_not(_t3103);
    (void)_t3104;
    ;
    if (_t3104) {
        Str *_t3079 = Str_lit("Str", 3ULL);
        (void)_t3079;
        U64 _t3080; { U64 *_hp = (U64 *)Str_size(); _t3080 = *_hp; free(_hp); }
        (void)_t3080;
        U64 _t3081 = 10;
        (void)_t3081;
        Array *_va54 = Array_new(_t3079, &(U64){_t3080}, &(U64){_t3081});
        (void)_va54;
        Str_delete(_t3079, &(Bool){1});
        ;
        ;
        U64 _t3082 = 0;
        (void)_t3082;
        Str *_t3083 = Str_clone(&p->path);
        (void)_t3083;
        Array_set(_va54, &(U64){_t3082}, _t3083);
        ;
        U64 _t3084 = 1;
        (void)_t3084;
        Str *_t3085 = Str_lit(":", 1ULL);
        (void)_t3085;
        Array_set(_va54, &(U64){_t3084}, _t3085);
        ;
        U64 _t3086 = 2;
        (void)_t3086;
        Str *_t3087 = U32_to_str(&t->line);
        (void)_t3087;
        Array_set(_va54, &(U64){_t3086}, _t3087);
        ;
        U64 _t3088 = 3;
        (void)_t3088;
        Str *_t3089 = Str_lit(":", 1ULL);
        (void)_t3089;
        Array_set(_va54, &(U64){_t3088}, _t3089);
        ;
        U64 _t3090 = 4;
        (void)_t3090;
        Str *_t3091 = U32_to_str(&t->col);
        (void)_t3091;
        Array_set(_va54, &(U64){_t3090}, _t3091);
        ;
        U64 _t3092 = 5;
        (void)_t3092;
        Str *_t3093 = Str_lit(": expected '", 12ULL);
        (void)_t3093;
        Array_set(_va54, &(U64){_t3092}, _t3093);
        ;
        U64 _t3094 = 6;
        (void)_t3094;
        Str *_t3095 = tok_name(type);
        (void)_t3095;
        Array_set(_va54, &(U64){_t3094}, _t3095);
        ;
        U64 _t3096 = 7;
        (void)_t3096;
        Str *_t3097 = Str_lit("', found '", 10ULL);
        (void)_t3097;
        Array_set(_va54, &(U64){_t3096}, _t3097);
        ;
        U64 _t3098 = 8;
        (void)_t3098;
        Str *_t3099 = Str_clone(&t->text);
        (void)_t3099;
        Array_set(_va54, &(U64){_t3098}, _t3099);
        ;
        U64 _t3100 = 9;
        (void)_t3100;
        Str *_t3101 = Str_lit("'", 1ULL);
        (void)_t3101;
        Array_set(_va54, &(U64){_t3100}, _t3101);
        ;
        Str *_t3102 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:34:15", 63ULL);
        (void)_t3102;
        panic(_t3102, _va54);
        Str_delete(_t3102, &(Bool){1});
    }
    ;
    Token *_t3105 = advance(p);
    (void)_t3105;
    return _t3105;
}

Str * expect_text(Parser * p, TokenType * type) {
    (void)p;
    (void)type;
    Token *t = peek(p);
    (void)t;
    Bool _t3130; { Bool *_hp = (Bool *)TokenType_eq(&t->type, type); _t3130 = *_hp; free(_hp); }
    (void)_t3130;
    Bool _t3131 = Bool_not(_t3130);
    (void)_t3131;
    ;
    if (_t3131) {
        Str *_t3106 = Str_lit("Str", 3ULL);
        (void)_t3106;
        U64 _t3107; { U64 *_hp = (U64 *)Str_size(); _t3107 = *_hp; free(_hp); }
        (void)_t3107;
        U64 _t3108 = 10;
        (void)_t3108;
        Array *_va55 = Array_new(_t3106, &(U64){_t3107}, &(U64){_t3108});
        (void)_va55;
        Str_delete(_t3106, &(Bool){1});
        ;
        ;
        U64 _t3109 = 0;
        (void)_t3109;
        Str *_t3110 = Str_clone(&p->path);
        (void)_t3110;
        Array_set(_va55, &(U64){_t3109}, _t3110);
        ;
        U64 _t3111 = 1;
        (void)_t3111;
        Str *_t3112 = Str_lit(":", 1ULL);
        (void)_t3112;
        Array_set(_va55, &(U64){_t3111}, _t3112);
        ;
        U64 _t3113 = 2;
        (void)_t3113;
        Str *_t3114 = U32_to_str(&t->line);
        (void)_t3114;
        Array_set(_va55, &(U64){_t3113}, _t3114);
        ;
        U64 _t3115 = 3;
        (void)_t3115;
        Str *_t3116 = Str_lit(":", 1ULL);
        (void)_t3116;
        Array_set(_va55, &(U64){_t3115}, _t3116);
        ;
        U64 _t3117 = 4;
        (void)_t3117;
        Str *_t3118 = U32_to_str(&t->col);
        (void)_t3118;
        Array_set(_va55, &(U64){_t3117}, _t3118);
        ;
        U64 _t3119 = 5;
        (void)_t3119;
        Str *_t3120 = Str_lit(": expected '", 12ULL);
        (void)_t3120;
        Array_set(_va55, &(U64){_t3119}, _t3120);
        ;
        U64 _t3121 = 6;
        (void)_t3121;
        Str *_t3122 = tok_name(type);
        (void)_t3122;
        Array_set(_va55, &(U64){_t3121}, _t3122);
        ;
        U64 _t3123 = 7;
        (void)_t3123;
        Str *_t3124 = Str_lit("', found '", 10ULL);
        (void)_t3124;
        Array_set(_va55, &(U64){_t3123}, _t3124);
        ;
        U64 _t3125 = 8;
        (void)_t3125;
        Str *_t3126 = Str_clone(&t->text);
        (void)_t3126;
        Array_set(_va55, &(U64){_t3125}, _t3126);
        ;
        U64 _t3127 = 9;
        (void)_t3127;
        Str *_t3128 = Str_lit("'", 1ULL);
        (void)_t3128;
        Array_set(_va55, &(U64){_t3127}, _t3128);
        ;
        Str *_t3129 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:44:15", 63ULL);
        (void)_t3129;
        panic(_t3129, _va55);
        Str_delete(_t3129, &(Bool){1});
    }
    ;
    Str *text = Str_clone(&t->text);
    (void)text;
    Token *_t3132 = advance(p);
    (void)_t3132;
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
    Bool _t3174 = check(p, TokenType_LParen());
    (void)_t3174;
    Bool _t3175 = Bool_not(_t3174);
    (void)_t3175;
    ;
    if (_t3175) {
        Str *_t3133 = Str_lit("", 0ULL);
        (void)_t3133;
        ;
        return _t3133;
    }
    ;
    Token *_t3176 = advance(p);
    (void)_t3176;
    Str *_t3177 = Str_lit("Str", 3ULL);
    (void)_t3177;
    U64 _t3178; { U64 *_hp = (U64 *)Str_size(); _t3178 = *_hp; free(_hp); }
    (void)_t3178;
    Vec *ptypes = Vec_new(_t3177, &(U64){_t3178});
    (void)ptypes;
    Str_delete(_t3177, &(Bool){1});
    ;
    Str *_t3179 = Str_lit("Bool", 4ULL);
    (void)_t3179;
    U64 _t3180; { U64 *_hp = (U64 *)Bool_size(); _t3180 = *_hp; free(_hp); }
    (void)_t3180;
    Vec *pmuts = Vec_new(_t3179, &(U64){_t3180});
    (void)pmuts;
    Str_delete(_t3179, &(Bool){1});
    ;
    while (1) {
        Bool _t3138 = check(p, TokenType_RParen());
        (void)_t3138;
        Bool _t3139 = check(p, TokenType_Eof());
        (void)_t3139;
        Bool _t3140 = Bool_not(_t3138);
        (void)_t3140;
        ;
        Bool _t3141 = Bool_not(_t3139);
        (void)_t3141;
        ;
        Bool _wcond3134 = Bool_and(_t3140, _t3141);
        (void)_wcond3134;
        ;
        ;
        if (_wcond3134) {
        } else {
            ;
            break;
        }
        ;
        Bool is_mut = 0;
        (void)is_mut;
        Bool _t3142 = check(p, TokenType_KwMut());
        (void)_t3142;
        if (_t3142) {
            Token *_t3135 = advance(p);
            (void)_t3135;
            Bool _t3136 = 1;
            (void)_t3136;
            is_mut = _t3136;
            ;
        }
        ;
        Str *ptype = expect_text(p, TokenType_Ident());
        (void)ptype;
        Vec_push(ptypes, ptype);
        Vec_push(pmuts, ({ Bool *_oa = malloc(sizeof(Bool)); *_oa = is_mut; _oa; }));
        Bool _t3143 = check(p, TokenType_Comma());
        (void)_t3143;
        if (_t3143) {
            Token *_t3137 = advance(p);
            (void)_t3137;
        }
        ;
    }
    Token *_t3181 = expect_token(p, TokenType_RParen());
    (void)_t3181;
    Str *return_type = Str_lit("", 0ULL);
    (void)return_type;
    Bool _t3182 = check(p, TokenType_KwReturns());
    (void)_t3182;
    if (_t3182) {
        Token *_t3144 = advance(p);
        (void)_t3144;
        return_type = expect_text(p, TokenType_Ident());
    }
    ;
    Str *name = Str_lit("_Fn", 3ULL);
    (void)name;
    {
        U64 _fi3145 = 0;
        (void)_fi3145;
        while (1) {
            U64 _t3148 = 0;
            (void)_t3148;
            U64 _t3149; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3149 = *_hp; free(_hp); }
            (void)_t3149;
            Range *_t3150 = Range_new(_t3148, _t3149);
            (void)_t3150;
            ;
            ;
            U64 _t3151; { U64 *_hp = (U64 *)Range_len(_t3150); _t3151 = *_hp; free(_hp); }
            (void)_t3151;
            Range_delete(_t3150, &(Bool){1});
            Bool _wcond3146; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3145}, &(U64){_t3151}); _wcond3146 = *_hp; free(_hp); }
            (void)_wcond3146;
            ;
            if (_wcond3146) {
            } else {
                ;
                break;
            }
            ;
            U64 _t3152 = 0;
            (void)_t3152;
            U64 _t3153; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3153 = *_hp; free(_hp); }
            (void)_t3153;
            Range *_t3154 = Range_new(_t3152, _t3153);
            (void)_t3154;
            ;
            ;
            U64 *i = Range_get(_t3154, _fi3145);
            (void)i;
            Range_delete(_t3154, &(Bool){1});
            U64 _t3155 = 1;
            (void)_t3155;
            U64 _t3156 = U64_add(_fi3145, _t3155);
            (void)_t3156;
            ;
            _fi3145 = _t3156;
            ;
            Str *_t3157 = Str_lit("_", 1ULL);
            (void)_t3157;
            name = Str_concat(name, _t3157);
            Str_delete(_t3157, &(Bool){1});
            Bool *m = Vec_get(pmuts, i);
            (void)m;
            if (DEREF(m)) {
                Str *_t3147 = Str_lit("mut_", 4ULL);
                (void)_t3147;
                name = Str_concat(name, _t3147);
                Str_delete(_t3147, &(Bool){1});
            }
            Str *t = Vec_get(ptypes, i);
            (void)t;
            name = Str_concat(name, t);
            U64_delete(i, &(Bool){1});
        }
        ;
    }
    U64 _t3183; { U64 *_hp = (U64 *)Str_len(return_type); _t3183 = *_hp; free(_hp); }
    (void)_t3183;
    U64 _t3184 = 0;
    (void)_t3184;
    Bool _t3185; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3183}, &(U64){_t3184}); _t3185 = *_hp; free(_hp); }
    (void)_t3185;
    ;
    ;
    if (_t3185) {
        Str *_t3158 = Str_lit("_ret_", 5ULL);
        (void)_t3158;
        name = Str_concat(name, _t3158);
        Str_delete(_t3158, &(Bool){1});
        name = Str_concat(name, return_type);
    }
    ;
    Str *_t3186 = Str_lit("Param", 5ULL);
    (void)_t3186;
    U64 _t3187; { U64 *_hp = (U64 *)Param_size(); _t3187 = *_hp; free(_hp); }
    (void)_t3187;
    Str *_t3188 = Str_lit("Str", 3ULL);
    (void)_t3188;
    U64 _t3189; { U64 *_hp = (U64 *)Str_size(); _t3189 = *_hp; free(_hp); }
    (void)_t3189;
    Str *_t3190 = Str_lit("Expr", 4ULL);
    (void)_t3190;
    U64 _t3191; { U64 *_hp = (U64 *)Expr_size(); _t3191 = *_hp; free(_hp); }
    (void)_t3191;
    I64 _t3192 = 0;
    (void)_t3192;
    I64 _t3193 = 1;
    (void)_t3193;
    I64 _t3194 = I64_sub(_t3192, _t3193);
    (void)_t3194;
    ;
    ;
    I64 _t3195 = 0;
    (void)_t3195;
    I64 _t3196 = 1;
    (void)_t3196;
    I64 _t3197 = I64_sub(_t3195, _t3196);
    (void)_t3197;
    ;
    ;
    U32 _t3198 = 0;
    (void)_t3198;
    I32 _t3199 = I64_to_i32(_t3194);
    (void)_t3199;
    ;
    I32 _t3200 = I64_to_i32(_t3197);
    (void)_t3200;
    ;
    Bool _t3201 = 0;
    (void)_t3201;
    Bool _t3202 = 0;
    (void)_t3202;
    FunctionDef *fd = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(FuncType_Func()); fd->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3186, &(U64){_t3187}); fd->params = *_ca; free(_ca); }
    fd->nparam = _t3198;
    { Map *_ca = Map_new(_t3188, &(U64){_t3189}, _t3190, &(U64){_t3191}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3199;
    fd->kwargs_index = _t3200;
    fd->return_is_ref = _t3201;
    fd->return_is_shallow = _t3202;
    (void)fd;
    Str_delete(_t3186, &(Bool){1});
    ;
    Str_delete(_t3188, &(Bool){1});
    ;
    Str_delete(_t3190, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    U64 _t3203; { U64 *_hp = (U64 *)Str_len(return_type); _t3203 = *_hp; free(_hp); }
    (void)_t3203;
    U64 _t3204 = 0;
    (void)_t3204;
    Bool _t3205; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3203}, &(U64){_t3204}); _t3205 = *_hp; free(_hp); }
    (void)_t3205;
    ;
    ;
    if (_t3205) {
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
    Bool _t3206 = 0;
    (void)_t3206;
    fd->return_is_ref = _t3206;
    ;
    Bool _t3207 = 0;
    (void)_t3207;
    fd->return_is_shallow = _t3207;
    ;
    I64 _t3208 = 0;
    (void)_t3208;
    I64 _t3209 = 1;
    (void)_t3209;
    I64 _t3210 = I64_sub(_t3208, _t3209);
    (void)_t3210;
    ;
    ;
    I32 _t3211 = I64_to_i32(_t3210);
    (void)_t3211;
    ;
    fd->variadic_index = _t3211;
    ;
    I64 _t3212 = 0;
    (void)_t3212;
    I64 _t3213 = 1;
    (void)_t3213;
    I64 _t3214 = I64_sub(_t3212, _t3213);
    (void)_t3214;
    ;
    ;
    I32 _t3215 = I64_to_i32(_t3214);
    (void)_t3215;
    ;
    fd->kwargs_index = _t3215;
    ;
    {
        U64 _fi3159 = 0;
        (void)_fi3159;
        while (1) {
            U64 _t3161 = 0;
            (void)_t3161;
            U64 _t3162; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3162 = *_hp; free(_hp); }
            (void)_t3162;
            Range *_t3163 = Range_new(_t3161, _t3162);
            (void)_t3163;
            ;
            ;
            U64 _t3164; { U64 *_hp = (U64 *)Range_len(_t3163); _t3164 = *_hp; free(_hp); }
            (void)_t3164;
            Range_delete(_t3163, &(Bool){1});
            Bool _wcond3160; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3159}, &(U64){_t3164}); _wcond3160 = *_hp; free(_hp); }
            (void)_wcond3160;
            ;
            if (_wcond3160) {
            } else {
                ;
                break;
            }
            ;
            U64 _t3165 = 0;
            (void)_t3165;
            U64 _t3166; { U64 *_hp = (U64 *)Vec_len(ptypes); _t3166 = *_hp; free(_hp); }
            (void)_t3166;
            Range *_t3167 = Range_new(_t3165, _t3166);
            (void)_t3167;
            ;
            ;
            U64 *i = Range_get(_t3167, _fi3159);
            (void)i;
            Range_delete(_t3167, &(Bool){1});
            U64 _t3168 = 1;
            (void)_t3168;
            U64 _t3169 = U64_add(_fi3159, _t3168);
            (void)_t3169;
            ;
            _fi3159 = _t3169;
            ;
            Str *t = Vec_get(ptypes, i);
            (void)t;
            Bool *m = Vec_get(pmuts, i);
            (void)m;
            Bool _t3170 = Bool_clone(m);
            (void)_t3170;
            Bool _t3171 = 0;
            (void)_t3171;
            Bool _t3172 = 0;
            (void)_t3172;
            Param *_t3173 = malloc(sizeof(Param));
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t3173->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(t); _t3173->ptype = *_ca; free(_ca); }
            _t3173->is_mut = _t3170;
            _t3173->is_own = _t3171;
            _t3173->is_shallow = _t3172;
            (void)_t3173;
            ;
            ;
            ;
            U64_delete(i, &(Bool){1});
            Vec_push(&fd->params, _t3173);
        }
        ;
    }
    Vec_delete(pmuts, &(Bool){1});
    Vec_delete(ptypes, &(Bool){1});
    U64 _t3216; { U64 *_hp = (U64 *)Vec_len(&fd->params); _t3216 = *_hp; free(_hp); }
    (void)_t3216;
    I64 _t3217 = U64_to_i64(_t3216);
    (void)_t3217;
    ;
    U32 _t3218 = I64_to_u32(_t3217);
    (void)_t3218;
    ;
    fd->nparam = _t3218;
    ;
    ExprData *_t3219 = ExprData_FuncDef(fd);
    (void)_t3219;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *sig = Expr_new(_t3219, line, col, &p->path);
    (void)sig;
    ExprData_delete(_t3219, &(Bool){1});
    Bool _t3220 = 0;
    (void)_t3220;
    Bool _t3221 = 0;
    (void)_t3221;
    Bool _t3222 = 0;
    (void)_t3222;
    Bool _t3223 = 0;
    (void)_t3223;
    I32 _t3224 = 0;
    (void)_t3224;
    I32 _t3225 = 0;
    (void)_t3225;
    Declaration *_t3226 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(name); _t3226->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t3226->explicit_type = *_ca; free(_ca); }
    _t3226->is_mut = _t3220;
    _t3226->is_namespace = _t3221;
    _t3226->is_ref = _t3222;
    _t3226->is_own = _t3223;
    _t3226->field_offset = _t3224;
    _t3226->field_size = _t3225;
    _t3226->field_struct_def = NULL;
    _t3226->fn_sig = NULL;
    (void)_t3226;
    ;
    ;
    ;
    ;
    ;
    ;
    ExprData *_t3227 = ExprData_Decl(_t3226);
    (void)_t3227;
    Declaration_delete(_t3226, &(Bool){1});
    Expr *decl = Expr_new(_t3227, line, col, &p->path);
    (void)decl;
    ExprData_delete(_t3227, &(Bool){1});
    Expr_add_child(decl, sig);
    Vec_push(&p->fn_sig_decls, decl);
    return name;
}

Expr * parse_block(Parser * p) {
    (void)p;
    U32 _t3234 = peek_line(p);
    (void)_t3234;
    U32 _t3235 = peek_col(p);
    (void)_t3235;
    Expr *body = Expr_new(ExprData_Body(), _t3234, _t3235, &p->path);
    (void)body;
    ;
    ;
    while (1) {
        Bool _t3229 = check(p, TokenType_RBrace());
        (void)_t3229;
        Bool _t3230 = check(p, TokenType_Eof());
        (void)_t3230;
        Bool _t3231 = Bool_not(_t3229);
        (void)_t3231;
        ;
        Bool _t3232 = Bool_not(_t3230);
        (void)_t3232;
        ;
        Bool _wcond3228 = Bool_and(_t3231, _t3232);
        (void)_wcond3228;
        ;
        ;
        if (_wcond3228) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t3233 = parse_statement(p);
        (void)_t3233;
        Expr_add_child(body, _t3233);
    }
    Token *_t3236 = expect_token(p, TokenType_RBrace());
    (void)_t3236;
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
        TokenType *_sw3237 = TokenType_clone(&kw->type);
        (void)_sw3237;
        Bool _t3249; { Bool *_hp = (Bool *)TokenType_eq(_sw3237, TokenType_KwFunc()); _t3249 = *_hp; free(_hp); }
        (void)_t3249;
        if (_t3249) {
            ft = FuncType_clone(FuncType_Func());
        } else {
            Bool _t3248; { Bool *_hp = (Bool *)TokenType_eq(_sw3237, TokenType_KwProc()); _t3248 = *_hp; free(_hp); }
            (void)_t3248;
            if (_t3248) {
                ft = FuncType_clone(FuncType_Proc());
            } else {
                Bool _t3247; { Bool *_hp = (Bool *)TokenType_eq(_sw3237, TokenType_KwTest()); _t3247 = *_hp; free(_hp); }
                (void)_t3247;
                if (_t3247) {
                    ft = FuncType_clone(FuncType_Test());
                } else {
                    Bool _t3246; { Bool *_hp = (Bool *)TokenType_eq(_sw3237, TokenType_KwMacro()); _t3246 = *_hp; free(_hp); }
                    (void)_t3246;
                    if (_t3246) {
                        ft = FuncType_clone(FuncType_Macro());
                    } else {
                        Bool _t3245; { Bool *_hp = (Bool *)TokenType_eq(_sw3237, TokenType_KwExtFunc()); _t3245 = *_hp; free(_hp); }
                        (void)_t3245;
                        if (_t3245) {
                            ft = FuncType_clone(FuncType_ExtFunc());
                        } else {
                            Bool _t3244; { Bool *_hp = (Bool *)TokenType_eq(_sw3237, TokenType_KwExtProc()); _t3244 = *_hp; free(_hp); }
                            (void)_t3244;
                            if (_t3244) {
                                ft = FuncType_clone(FuncType_ExtProc());
                            } else {
                                Str *_t3238 = Str_lit("Str", 3ULL);
                                (void)_t3238;
                                U64 _t3239; { U64 *_hp = (U64 *)Str_size(); _t3239 = *_hp; free(_hp); }
                                (void)_t3239;
                                U64 _t3240 = 1;
                                (void)_t3240;
                                Array *_va56 = Array_new(_t3238, &(U64){_t3239}, &(U64){_t3240});
                                (void)_va56;
                                Str_delete(_t3238, &(Bool){1});
                                ;
                                ;
                                U64 _t3241 = 0;
                                (void)_t3241;
                                Str *_t3242 = Str_lit("expected function keyword", 25ULL);
                                (void)_t3242;
                                Array_set(_va56, &(U64){_t3241}, _t3242);
                                ;
                                Str *_t3243 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:150:17", 64ULL);
                                (void)_t3243;
                                panic(_t3243, _va56);
                                Str_delete(_t3243, &(Bool){1});
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
        TokenType_delete(_sw3237, &(Bool){1});
        ;
    }
    Token *_t3427 = expect_token(p, TokenType_LParen());
    (void)_t3427;
    Str *_t3428 = Str_lit("Param", 5ULL);
    (void)_t3428;
    U64 _t3429; { U64 *_hp = (U64 *)Param_size(); _t3429 = *_hp; free(_hp); }
    (void)_t3429;
    Str *_t3430 = Str_lit("Str", 3ULL);
    (void)_t3430;
    U64 _t3431; { U64 *_hp = (U64 *)Str_size(); _t3431 = *_hp; free(_hp); }
    (void)_t3431;
    Str *_t3432 = Str_lit("Expr", 4ULL);
    (void)_t3432;
    U64 _t3433; { U64 *_hp = (U64 *)Expr_size(); _t3433 = *_hp; free(_hp); }
    (void)_t3433;
    I64 _t3434 = 0;
    (void)_t3434;
    I64 _t3435 = 1;
    (void)_t3435;
    I64 _t3436 = I64_sub(_t3434, _t3435);
    (void)_t3436;
    ;
    ;
    I64 _t3437 = 0;
    (void)_t3437;
    I64 _t3438 = 1;
    (void)_t3438;
    I64 _t3439 = I64_sub(_t3437, _t3438);
    (void)_t3439;
    ;
    ;
    U32 _t3440 = 0;
    (void)_t3440;
    I32 _t3441 = I64_to_i32(_t3436);
    (void)_t3441;
    ;
    I32 _t3442 = I64_to_i32(_t3439);
    (void)_t3442;
    ;
    Bool _t3443 = 0;
    (void)_t3443;
    Bool _t3444 = 0;
    (void)_t3444;
    FunctionDef *fd = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(FuncType_Func()); fd->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t3428, &(U64){_t3429}); fd->params = *_ca; free(_ca); }
    fd->nparam = _t3440;
    { Map *_ca = Map_new(_t3430, &(U64){_t3431}, _t3432, &(U64){_t3433}); fd->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); fd->return_type = *_ca; free(_ca); }
    fd->variadic_index = _t3441;
    fd->kwargs_index = _t3442;
    fd->return_is_ref = _t3443;
    fd->return_is_shallow = _t3444;
    (void)fd;
    Str_delete(_t3428, &(Bool){1});
    ;
    Str_delete(_t3430, &(Bool){1});
    ;
    Str_delete(_t3432, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    FuncType_delete(&fd->func_type, &(Bool){0});
    { FuncType *_fa = FuncType_clone(ft); fd->func_type = *_fa; free(_fa); }
    while (1) {
        Bool _t3367 = check(p, TokenType_RParen());
        (void)_t3367;
        Bool _t3368 = check(p, TokenType_Eof());
        (void)_t3368;
        Bool _t3369 = Bool_not(_t3367);
        (void)_t3369;
        ;
        Bool _t3370 = Bool_not(_t3368);
        (void)_t3370;
        ;
        Bool _wcond3250 = Bool_and(_t3369, _t3370);
        (void)_wcond3250;
        ;
        ;
        if (_wcond3250) {
        } else {
            ;
            break;
        }
        ;
        Bool is_shallow = 0;
        (void)is_shallow;
        Bool _t3371 = check(p, TokenType_KwShallow());
        (void)_t3371;
        if (_t3371) {
            Token *_t3251 = advance(p);
            (void)_t3251;
            Bool _t3252 = 1;
            (void)_t3252;
            is_shallow = _t3252;
            ;
        }
        ;
        Bool is_own = 0;
        (void)is_own;
        Bool _t3372 = check(p, TokenType_KwOwn());
        (void)_t3372;
        if (_t3372) {
            Token *_t3253 = advance(p);
            (void)_t3253;
            Bool _t3254 = 1;
            (void)_t3254;
            is_own = _t3254;
            ;
        }
        ;
        Bool is_mut = 0;
        (void)is_mut;
        Bool _t3373 = check(p, TokenType_KwMut());
        (void)_t3373;
        if (_t3373) {
            Token *_t3255 = advance(p);
            (void)_t3255;
            Bool _t3256 = 1;
            (void)_t3256;
            is_mut = _t3256;
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
        Bool _t3374 = check(p, TokenType_Colon());
        (void)_t3374;
        Bool _t3375 = Bool_not(_t3374);
        (void)_t3375;
        ;
        if (_t3375) {
            tp = Str_clone(pname);
            nm = Str_lit("", 0ULL);
        } else {
            Token *_t3350 = expect_token(p, TokenType_Colon());
            (void)_t3350;
            Bool _t3351 = check(p, TokenType_DotDotDot());
            (void)_t3351;
            if (_t3351) {
                Token *_t3287 = advance(p);
                (void)_t3287;
                Bool _t3288 = Bool_or(is_own, is_mut);
                (void)_t3288;
                Bool _t3289 = Bool_or(_t3288, is_shallow);
                (void)_t3289;
                ;
                if (_t3289) {
                    Str *_t3257 = Str_lit("Str", 3ULL);
                    (void)_t3257;
                    U64 _t3258; { U64 *_hp = (U64 *)Str_size(); _t3258 = *_hp; free(_hp); }
                    (void)_t3258;
                    U64 _t3259 = 6;
                    (void)_t3259;
                    Array *_va57 = Array_new(_t3257, &(U64){_t3258}, &(U64){_t3259});
                    (void)_va57;
                    Str_delete(_t3257, &(Bool){1});
                    ;
                    ;
                    U64 _t3260 = 0;
                    (void)_t3260;
                    Str *_t3261 = Str_clone(&p->path);
                    (void)_t3261;
                    Array_set(_va57, &(U64){_t3260}, _t3261);
                    ;
                    U64 _t3262 = 1;
                    (void)_t3262;
                    Str *_t3263 = Str_lit(":", 1ULL);
                    (void)_t3263;
                    Array_set(_va57, &(U64){_t3262}, _t3263);
                    ;
                    U32 _t3264 = peek_line(p);
                    (void)_t3264;
                    U64 _t3265 = 2;
                    (void)_t3265;
                    Str *_t3266 = U32_to_str(&(U32){_t3264});
                    (void)_t3266;
                    ;
                    Array_set(_va57, &(U64){_t3265}, _t3266);
                    ;
                    U64 _t3267 = 3;
                    (void)_t3267;
                    Str *_t3268 = Str_lit(":", 1ULL);
                    (void)_t3268;
                    Array_set(_va57, &(U64){_t3267}, _t3268);
                    ;
                    U32 _t3269 = peek_col(p);
                    (void)_t3269;
                    U64 _t3270 = 4;
                    (void)_t3270;
                    Str *_t3271 = U32_to_str(&(U32){_t3269});
                    (void)_t3271;
                    ;
                    Array_set(_va57, &(U64){_t3270}, _t3271);
                    ;
                    U64 _t3272 = 5;
                    (void)_t3272;
                    Str *_t3273 = Str_lit(": kwargs parameter cannot be own/mut/shallow", 44ULL);
                    (void)_t3273;
                    Array_set(_va57, &(U64){_t3272}, _t3273);
                    ;
                    Str *_t3274 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:180:27", 64ULL);
                    (void)_t3274;
                    panic(_t3274, _va57);
                    Str_delete(_t3274, &(Bool){1});
                }
                ;
                I64 _t3290 = 0;
                (void)_t3290;
                I64 _t3291 = 1;
                (void)_t3291;
                I64 _t3292 = I64_sub(_t3290, _t3291);
                (void)_t3292;
                ;
                ;
                I32 _t3293 = I64_to_i32(_t3292);
                (void)_t3293;
                ;
                Bool _t3294; { Bool *_hp = (Bool *)I32_neq(&fd->kwargs_index, &(I32){_t3293}); _t3294 = *_hp; free(_hp); }
                (void)_t3294;
                ;
                if (_t3294) {
                    Str *_t3275 = Str_lit("Str", 3ULL);
                    (void)_t3275;
                    U64 _t3276; { U64 *_hp = (U64 *)Str_size(); _t3276 = *_hp; free(_hp); }
                    (void)_t3276;
                    U64 _t3277 = 1;
                    (void)_t3277;
                    Array *_va58 = Array_new(_t3275, &(U64){_t3276}, &(U64){_t3277});
                    (void)_va58;
                    Str_delete(_t3275, &(Bool){1});
                    ;
                    ;
                    U64 _t3278 = 0;
                    (void)_t3278;
                    Str *_t3279 = Str_lit("only one kwargs parameter is allowed", 36ULL);
                    (void)_t3279;
                    Array_set(_va58, &(U64){_t3278}, _t3279);
                    ;
                    Str *_t3280 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:184:27", 64ULL);
                    (void)_t3280;
                    panic(_t3280, _va58);
                    Str_delete(_t3280, &(Bool){1});
                }
                ;
                I64 _t3295 = 0;
                (void)_t3295;
                I64 _t3296 = 1;
                (void)_t3296;
                I64 _t3297 = I64_sub(_t3295, _t3296);
                (void)_t3297;
                ;
                ;
                I32 _t3298 = I64_to_i32(_t3297);
                (void)_t3298;
                ;
                Bool _t3299; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3298}); _t3299 = *_hp; free(_hp); }
                (void)_t3299;
                ;
                if (_t3299) {
                    Str *_t3281 = Str_lit("Str", 3ULL);
                    (void)_t3281;
                    U64 _t3282; { U64 *_hp = (U64 *)Str_size(); _t3282 = *_hp; free(_hp); }
                    (void)_t3282;
                    U64 _t3283 = 1;
                    (void)_t3283;
                    Array *_va59 = Array_new(_t3281, &(U64){_t3282}, &(U64){_t3283});
                    (void)_va59;
                    Str_delete(_t3281, &(Bool){1});
                    ;
                    ;
                    U64 _t3284 = 0;
                    (void)_t3284;
                    Str *_t3285 = Str_lit("cannot combine variadic and kwargs in the same function", 55ULL);
                    (void)_t3285;
                    Array_set(_va59, &(U64){_t3284}, _t3285);
                    ;
                    Str *_t3286 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:187:27", 64ULL);
                    (void)_t3286;
                    panic(_t3286, _va59);
                    Str_delete(_t3286, &(Bool){1});
                }
                ;
                U64 _t3300; { U64 *_hp = (U64 *)Vec_len(&fd->params); _t3300 = *_hp; free(_hp); }
                (void)_t3300;
                I64 _t3301 = U64_to_i64(_t3300);
                (void)_t3301;
                ;
                I32 _t3302 = I64_to_i32(_t3301);
                (void)_t3302;
                ;
                fd->kwargs_index = _t3302;
                ;
                Bool _t3303 = 1;
                (void)_t3303;
                is_own = _t3303;
                ;
                nm = Str_clone(pname);
                tp = Str_lit("Map", 3ULL);
            } else {
                Bool _t3349 = check(p, TokenType_DotDot());
                (void)_t3349;
                if (_t3349) {
                    Token *_t3334 = advance(p);
                    (void)_t3334;
                    if (is_own) {
                        Str *_t3304 = Str_lit("Str", 3ULL);
                        (void)_t3304;
                        U64 _t3305; { U64 *_hp = (U64 *)Str_size(); _t3305 = *_hp; free(_hp); }
                        (void)_t3305;
                        U64 _t3306 = 1;
                        (void)_t3306;
                        Array *_va60 = Array_new(_t3304, &(U64){_t3305}, &(U64){_t3306});
                        (void)_va60;
                        Str_delete(_t3304, &(Bool){1});
                        ;
                        ;
                        U64 _t3307 = 0;
                        (void)_t3307;
                        Str *_t3308 = Str_lit("variadic param cannot be 'own'", 30ULL);
                        (void)_t3308;
                        Array_set(_va60, &(U64){_t3307}, _t3308);
                        ;
                        Str *_t3309 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:195:35", 64ULL);
                        (void)_t3309;
                        panic(_t3309, _va60);
                        Str_delete(_t3309, &(Bool){1});
                    }
                    if (is_mut) {
                        Str *_t3310 = Str_lit("Str", 3ULL);
                        (void)_t3310;
                        U64 _t3311; { U64 *_hp = (U64 *)Str_size(); _t3311 = *_hp; free(_hp); }
                        (void)_t3311;
                        U64 _t3312 = 1;
                        (void)_t3312;
                        Array *_va61 = Array_new(_t3310, &(U64){_t3311}, &(U64){_t3312});
                        (void)_va61;
                        Str_delete(_t3310, &(Bool){1});
                        ;
                        ;
                        U64 _t3313 = 0;
                        (void)_t3313;
                        Str *_t3314 = Str_lit("variadic param cannot be 'mut'", 30ULL);
                        (void)_t3314;
                        Array_set(_va61, &(U64){_t3313}, _t3314);
                        ;
                        Str *_t3315 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:196:35", 64ULL);
                        (void)_t3315;
                        panic(_t3315, _va61);
                        Str_delete(_t3315, &(Bool){1});
                    }
                    if (is_shallow) {
                        Str *_t3316 = Str_lit("Str", 3ULL);
                        (void)_t3316;
                        U64 _t3317; { U64 *_hp = (U64 *)Str_size(); _t3317 = *_hp; free(_hp); }
                        (void)_t3317;
                        U64 _t3318 = 1;
                        (void)_t3318;
                        Array *_va62 = Array_new(_t3316, &(U64){_t3317}, &(U64){_t3318});
                        (void)_va62;
                        Str_delete(_t3316, &(Bool){1});
                        ;
                        ;
                        U64 _t3319 = 0;
                        (void)_t3319;
                        Str *_t3320 = Str_lit("variadic param cannot be 'shallow'", 34ULL);
                        (void)_t3320;
                        Array_set(_va62, &(U64){_t3319}, _t3320);
                        ;
                        Str *_t3321 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:197:39", 64ULL);
                        (void)_t3321;
                        panic(_t3321, _va62);
                        Str_delete(_t3321, &(Bool){1});
                    }
                    I64 _t3335 = 0;
                    (void)_t3335;
                    I64 _t3336 = 1;
                    (void)_t3336;
                    I64 _t3337 = I64_sub(_t3335, _t3336);
                    (void)_t3337;
                    ;
                    ;
                    I32 _t3338 = I64_to_i32(_t3337);
                    (void)_t3338;
                    ;
                    Bool _t3339; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3338}); _t3339 = *_hp; free(_hp); }
                    (void)_t3339;
                    ;
                    if (_t3339) {
                        Str *_t3322 = Str_lit("Str", 3ULL);
                        (void)_t3322;
                        U64 _t3323; { U64 *_hp = (U64 *)Str_size(); _t3323 = *_hp; free(_hp); }
                        (void)_t3323;
                        U64 _t3324 = 1;
                        (void)_t3324;
                        Array *_va63 = Array_new(_t3322, &(U64){_t3323}, &(U64){_t3324});
                        (void)_va63;
                        Str_delete(_t3322, &(Bool){1});
                        ;
                        ;
                        U64 _t3325 = 0;
                        (void)_t3325;
                        Str *_t3326 = Str_lit("only one variadic param allowed", 31ULL);
                        (void)_t3326;
                        Array_set(_va63, &(U64){_t3325}, _t3326);
                        ;
                        Str *_t3327 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:198:63", 64ULL);
                        (void)_t3327;
                        panic(_t3327, _va63);
                        Str_delete(_t3327, &(Bool){1});
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
                    Bool _t3344; { Bool *_hp = (Bool *)I32_neq(&fd->kwargs_index, &(I32){_t3343}); _t3344 = *_hp; free(_hp); }
                    (void)_t3344;
                    ;
                    if (_t3344) {
                        Str *_t3328 = Str_lit("Str", 3ULL);
                        (void)_t3328;
                        U64 _t3329; { U64 *_hp = (U64 *)Str_size(); _t3329 = *_hp; free(_hp); }
                        (void)_t3329;
                        U64 _t3330 = 1;
                        (void)_t3330;
                        Array *_va64 = Array_new(_t3328, &(U64){_t3329}, &(U64){_t3330});
                        (void)_va64;
                        Str_delete(_t3328, &(Bool){1});
                        ;
                        ;
                        U64 _t3331 = 0;
                        (void)_t3331;
                        Str *_t3332 = Str_lit("cannot combine variadic and kwargs in the same function", 55ULL);
                        (void)_t3332;
                        Array_set(_va64, &(U64){_t3331}, _t3332);
                        ;
                        Str *_t3333 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:200:27", 64ULL);
                        (void)_t3333;
                        panic(_t3333, _va64);
                        Str_delete(_t3333, &(Bool){1});
                    }
                    ;
                    U64 _t3345; { U64 *_hp = (U64 *)Vec_len(&fd->params); _t3345 = *_hp; free(_hp); }
                    (void)_t3345;
                    I64 _t3346 = U64_to_i64(_t3345);
                    (void)_t3346;
                    ;
                    I32 _t3347 = I64_to_i32(_t3346);
                    (void)_t3347;
                    ;
                    fd->variadic_index = _t3347;
                    ;
                    Bool _t3348 = 1;
                    (void)_t3348;
                    is_variadic = _t3348;
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
        Str *_t3376 = Str_lit("Fn", 2ULL);
        (void)_t3376;
        Bool _t3377; { Bool *_hp = (Bool *)Str_eq(tp, _t3376); _t3377 = *_hp; free(_hp); }
        (void)_t3377;
        Str_delete(_t3376, &(Bool){1});
        if (_t3377) {
            U32 _t3352 = peek_line(p);
            (void)_t3352;
            U32 _t3353 = peek_col(p);
            (void)_t3353;
            Str *syn_name = parse_fn_signature(p, _t3352, _t3353);
            (void)syn_name;
            ;
            ;
            U64 _t3354; { U64 *_hp = (U64 *)Str_len(syn_name); _t3354 = *_hp; free(_hp); }
            (void)_t3354;
            U64 _t3355 = 0;
            (void)_t3355;
            Bool _t3356; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3354}, &(U64){_t3355}); _t3356 = *_hp; free(_hp); }
            (void)_t3356;
            ;
            ;
            if (_t3356) {
                tp = Str_clone(syn_name);
            }
            ;
            Str_delete(syn_name, &(Bool){1});
        }
        ;
        Bool has_default = 0;
        (void)has_default;
        Bool _t3378 = check(p, TokenType_Eq());
        (void)_t3378;
        if (_t3378) {
            Token *_t3357 = advance(p);
            (void)_t3357;
            Expr *def_expr = parse_expression(p);
            (void)def_expr;
            Str *_t3358 = Str_clone(nm);
            (void)_t3358;
            Map_set(&fd->param_defaults, _t3358, def_expr);
            Bool _t3359 = 1;
            (void)_t3359;
            has_default = _t3359;
            ;
        }
        ;
        I64 _t3379 = 0;
        (void)_t3379;
        I64 _t3380 = 1;
        (void)_t3380;
        I64 _t3381 = I64_sub(_t3379, _t3380);
        (void)_t3381;
        ;
        ;
        I32 _t3382 = I64_to_i32(_t3381);
        (void)_t3382;
        ;
        Bool _t3383; { Bool *_hp = (Bool *)I32_neq(&fd->variadic_index, &(I32){_t3382}); _t3383 = *_hp; free(_hp); }
        (void)_t3383;
        ;
        Bool _t3384 = Bool_not(is_variadic);
        (void)_t3384;
        ;
        Bool _t3385 = Bool_and(_t3383, _t3384);
        (void)_t3385;
        ;
        ;
        Bool _t3386 = Bool_not(has_default);
        (void)_t3386;
        ;
        Bool _t3387 = Bool_and(_t3385, _t3386);
        (void)_t3387;
        ;
        ;
        if (_t3387) {
            Str *_t3360 = Str_lit("Str", 3ULL);
            (void)_t3360;
            U64 _t3361; { U64 *_hp = (U64 *)Str_size(); _t3361 = *_hp; free(_hp); }
            (void)_t3361;
            U64 _t3362 = 1;
            (void)_t3362;
            Array *_va65 = Array_new(_t3360, &(U64){_t3361}, &(U64){_t3362});
            (void)_va65;
            Str_delete(_t3360, &(Bool){1});
            ;
            ;
            U64 _t3363 = 0;
            (void)_t3363;
            Str *_t3364 = Str_lit("positional param not allowed after variadic", 43ULL);
            (void)_t3364;
            Array_set(_va65, &(U64){_t3363}, _t3364);
            ;
            Str *_t3365 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:227:19", 64ULL);
            (void)_t3365;
            panic(_t3365, _va65);
            Str_delete(_t3365, &(Bool){1});
        }
        ;
        Bool _t3388 = Bool_clone(&(Bool){is_mut});
        (void)_t3388;
        ;
        Bool _t3389 = Bool_clone(&(Bool){is_own});
        (void)_t3389;
        ;
        Bool _t3390 = Bool_clone(&(Bool){is_shallow});
        (void)_t3390;
        ;
        Param *_t3391 = malloc(sizeof(Param));
        { Str *_ca = Str_clone(nm); _t3391->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(tp); _t3391->ptype = *_ca; free(_ca); }
        _t3391->is_mut = _t3388;
        _t3391->is_own = _t3389;
        _t3391->is_shallow = _t3390;
        (void)_t3391;
        ;
        ;
        ;
        Str_delete(nm, &(Bool){1});
        Str_delete(tp, &(Bool){1});
        Vec_push(&fd->params, _t3391);
        Bool _t3392 = check(p, TokenType_Comma());
        (void)_t3392;
        if (_t3392) {
            Token *_t3366 = advance(p);
            (void)_t3366;
        }
        ;
    }
    Token *_t3445 = expect_token(p, TokenType_RParen());
    (void)_t3445;
    Bool _t3446 = check(p, TokenType_KwReturns());
    (void)_t3446;
    if (_t3446) {
        Token *_t3398 = advance(p);
        (void)_t3398;
        Bool _t3399 = check(p, TokenType_KwRef());
        (void)_t3399;
        if (_t3399) {
            Token *_t3393 = advance(p);
            (void)_t3393;
            Bool _t3394 = 1;
            (void)_t3394;
            fd->return_is_ref = _t3394;
            ;
        } else {
            Bool _t3397 = check(p, TokenType_KwShallow());
            (void)_t3397;
            if (_t3397) {
                Token *_t3395 = advance(p);
                (void)_t3395;
                Bool _t3396 = 1;
                (void)_t3396;
                fd->return_is_shallow = _t3396;
                ;
            }
            ;
        }
        ;
        Str_delete(&fd->return_type, &(Bool){0});
        { Str *_fa = expect_text(p, TokenType_Ident()); fd->return_type = *_fa; free(_fa); }
    }
    ;
    U64 _t3447; { U64 *_hp = (U64 *)Vec_len(&fd->params); _t3447 = *_hp; free(_hp); }
    (void)_t3447;
    I64 _t3448 = U64_to_i64(_t3447);
    (void)_t3448;
    ;
    U32 _t3449 = I64_to_u32(_t3448);
    (void)_t3449;
    ;
    fd->nparam = _t3449;
    ;
    ExprData *_t3450 = ExprData_FuncDef(fd);
    (void)_t3450;
    FunctionDef_delete(fd, &(Bool){1});
    Expr *def = Expr_new(_t3450, kw_line, kw_col, &p->path);
    (void)def;
    ExprData_delete(_t3450, &(Bool){1});
    Bool _t3451 = check(p, TokenType_LBrace());
    (void)_t3451;
    if (_t3451) {
        Token *_t3400 = expect_token(p, TokenType_LBrace());
        (void)_t3400;
        Expr *_t3401 = parse_block(p);
        (void)_t3401;
        Expr_add_child(def, _t3401);
    } else {
        Bool _t3422; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Func()); _t3422 = *_hp; free(_hp); }
        (void)_t3422;
        Bool _t3423; { Bool *_hp = (Bool *)FuncType_eq(ft, FuncType_Proc()); _t3423 = *_hp; free(_hp); }
        (void)_t3423;
        Bool _t3424 = Bool_not(_t3422);
        (void)_t3424;
        ;
        Bool _t3425 = Bool_not(_t3423);
        (void)_t3425;
        ;
        Bool _t3426 = Bool_and(_t3424, _t3425);
        (void)_t3426;
        ;
        ;
        if (_t3426) {
            Str *_t3402 = Str_lit("Str", 3ULL);
            (void)_t3402;
            U64 _t3403; { U64 *_hp = (U64 *)Str_size(); _t3403 = *_hp; free(_hp); }
            (void)_t3403;
            U64 _t3404 = 8;
            (void)_t3404;
            Array *_va66 = Array_new(_t3402, &(U64){_t3403}, &(U64){_t3404});
            (void)_va66;
            Str_delete(_t3402, &(Bool){1});
            ;
            ;
            U64 _t3405 = 0;
            (void)_t3405;
            Str *_t3406 = Str_clone(&p->path);
            (void)_t3406;
            Array_set(_va66, &(U64){_t3405}, _t3406);
            ;
            U64 _t3407 = 1;
            (void)_t3407;
            Str *_t3408 = Str_lit(":", 1ULL);
            (void)_t3408;
            Array_set(_va66, &(U64){_t3407}, _t3408);
            ;
            U64 _t3409 = 2;
            (void)_t3409;
            Str *_t3410 = U32_to_str(&(U32){kw_line});
            (void)_t3410;
            Array_set(_va66, &(U64){_t3409}, _t3410);
            ;
            U64 _t3411 = 3;
            (void)_t3411;
            Str *_t3412 = Str_lit(":", 1ULL);
            (void)_t3412;
            Array_set(_va66, &(U64){_t3411}, _t3412);
            ;
            U64 _t3413 = 4;
            (void)_t3413;
            Str *_t3414 = U32_to_str(&(U32){kw_col});
            (void)_t3414;
            Array_set(_va66, &(U64){_t3413}, _t3414);
            ;
            U64 _t3415 = 5;
            (void)_t3415;
            Str *_t3416 = Str_lit(": ", 2ULL);
            (void)_t3416;
            Array_set(_va66, &(U64){_t3415}, _t3416);
            ;
            U64 _t3417 = 6;
            (void)_t3417;
            Str *_t3418 = func_type_name(ft);
            (void)_t3418;
            Array_set(_va66, &(U64){_t3417}, _t3418);
            ;
            U64 _t3419 = 7;
            (void)_t3419;
            Str *_t3420 = Str_lit(" requires a body", 16ULL);
            (void)_t3420;
            Array_set(_va66, &(U64){_t3419}, _t3420);
            ;
            Str *_t3421 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:257:19", 64ULL);
            (void)_t3421;
            panic(_t3421, _va66);
            Str_delete(_t3421, &(Bool){1});
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
    Token *_t3465 = advance(p);
    (void)_t3465;
    Expr *def = Expr_new(ExprData_StructDef(), kw_line, kw_col, &p->path);
    (void)def;
    ;
    ;
    Bool _t3466 = Bool_clone(&(Bool){is_ext});
    (void)_t3466;
    ;
    def->is_ext = _t3466;
    ;
    Token *_t3467 = expect_token(p, TokenType_LBrace());
    (void)_t3467;
    U32 _t3468 = peek_line(p);
    (void)_t3468;
    U32 _t3469 = peek_col(p);
    (void)_t3469;
    Expr *body = Expr_new(ExprData_Body(), _t3468, _t3469, &p->path);
    (void)body;
    ;
    ;
    Bool in_namespace = 0;
    (void)in_namespace;
    while (1) {
        Bool _t3458 = check(p, TokenType_RBrace());
        (void)_t3458;
        Bool _t3459 = check(p, TokenType_Eof());
        (void)_t3459;
        Bool _t3460 = Bool_not(_t3458);
        (void)_t3460;
        ;
        Bool _t3461 = Bool_not(_t3459);
        (void)_t3461;
        ;
        Bool _wcond3452 = Bool_and(_t3460, _t3461);
        (void)_wcond3452;
        ;
        ;
        if (_wcond3452) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3462 = check(p, TokenType_KwNamespace());
        (void)_t3462;
        if (_t3462) {
            Token *_t3453 = advance(p);
            (void)_t3453;
            Token *_t3454 = expect_token(p, TokenType_Colon());
            (void)_t3454;
            Bool _t3455 = 1;
            (void)_t3455;
            in_namespace = _t3455;
            ;
            ;
            continue;
        }
        ;
        Expr *stmt = parse_statement(p);
        (void)stmt;
        Bool _t3463; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3463 = *_hp; free(_hp); }
        (void)_t3463;
        Bool _t3464 = Bool_and(in_namespace, _t3463);
        (void)_t3464;
        ;
        if (_t3464) {
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
    }
    ;
    Token *_t3470 = expect_token(p, TokenType_RBrace());
    (void)_t3470;
    Expr_add_child(def, body);
    return def;
}

Expr * parse_enum_def(Parser * p) {
    (void)p;
    U32 kw_line = peek_line(p);
    (void)kw_line;
    U32 kw_col = peek_col(p);
    (void)kw_col;
    Token *_t3494 = advance(p);
    (void)_t3494;
    Expr *def = Expr_new(ExprData_EnumDef(), kw_line, kw_col, &p->path);
    (void)def;
    ;
    ;
    Token *_t3495 = expect_token(p, TokenType_LBrace());
    (void)_t3495;
    U32 _t3496 = peek_line(p);
    (void)_t3496;
    U32 _t3497 = peek_col(p);
    (void)_t3497;
    Expr *body = Expr_new(ExprData_Body(), _t3496, _t3497, &p->path);
    (void)body;
    ;
    ;
    Bool in_namespace = 0;
    (void)in_namespace;
    while (1) {
        Bool _t3489 = check(p, TokenType_RBrace());
        (void)_t3489;
        Bool _t3490 = check(p, TokenType_Eof());
        (void)_t3490;
        Bool _t3491 = Bool_not(_t3489);
        (void)_t3491;
        ;
        Bool _t3492 = Bool_not(_t3490);
        (void)_t3492;
        ;
        Bool _wcond3471 = Bool_and(_t3491, _t3492);
        (void)_wcond3471;
        ;
        ;
        if (_wcond3471) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3493 = check(p, TokenType_KwNamespace());
        (void)_t3493;
        if (_t3493) {
            Token *_t3472 = advance(p);
            (void)_t3472;
            Token *_t3473 = expect_token(p, TokenType_Colon());
            (void)_t3473;
            Bool _t3474 = 1;
            (void)_t3474;
            in_namespace = _t3474;
            ;
            ;
            continue;
        }
        ;
        if (in_namespace) {
            Expr *stmt = parse_statement(p);
            (void)stmt;
            Bool _t3477; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3477 = *_hp; free(_hp); }
            (void)_t3477;
            if (_t3477) {
                Bool _t3476; { Bool *_hp = (Bool *)ExprData_is_Decl(&stmt->data); _t3476 = *_hp; free(_hp); }
                (void)_t3476;
                if (_t3476) {
                    Declaration *dd = ExprData_get_Decl(&stmt->data);
                    (void)dd;
                    Bool _t3475 = 1;
                    (void)_t3475;
                    dd->is_namespace = _t3475;
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
            Bool _t3480 = 0;
            (void)_t3480;
            Bool _t3481 = 0;
            (void)_t3481;
            Bool _t3482 = 0;
            (void)_t3482;
            Bool _t3483 = 0;
            (void)_t3483;
            I32 _t3484 = 0;
            (void)_t3484;
            I32 _t3485 = 0;
            (void)_t3485;
            Declaration *dd = malloc(sizeof(Declaration));
            { Str *_ca = Str_clone(vname); dd->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
            dd->is_mut = _t3480;
            dd->is_namespace = _t3481;
            dd->is_ref = _t3482;
            dd->is_own = _t3483;
            dd->field_offset = _t3484;
            dd->field_size = _t3485;
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
            Bool _t3486 = check(p, TokenType_Colon());
            (void)_t3486;
            if (_t3486) {
                Token *_t3478 = advance(p);
                (void)_t3478;
                Str_delete(&dd->explicit_type, &(Bool){0});
                { Str *_fa = expect_text(p, TokenType_Ident()); dd->explicit_type = *_fa; free(_fa); }
            }
            ;
            ExprData *_t3487 = ExprData_Decl(dd);
            (void)_t3487;
            Declaration_delete(dd, &(Bool){1});
            Expr *variant = Expr_new(_t3487, v_line, v_col, &p->path);
            (void)variant;
            ExprData_delete(_t3487, &(Bool){1});
            ;
            ;
            Expr_add_child(body, variant);
            Bool _t3488 = check(p, TokenType_Comma());
            (void)_t3488;
            if (_t3488) {
                Token *_t3479 = advance(p);
                (void)_t3479;
            }
            ;
        }
    }
    ;
    Token *_t3498 = expect_token(p, TokenType_RBrace());
    (void)_t3498;
    Expr_add_child(def, body);
    return def;
}

Expr * parse_call(Parser * p, Str * name, U32 call_line, U32 call_col) {
    (void)p;
    (void)name;
    (void)call_line;
    (void)call_col;
    Token *_t3529 = advance(p);
    (void)_t3529;
    Expr *call = Expr_new(ExprData_FCall(), call_line, call_col, &p->path);
    (void)call;
    Str *_t3530 = Str_clone(name);
    (void)_t3530;
    ExprData *_t3531 = ExprData_Ident(_t3530);
    (void)_t3531;
    Str_delete(_t3530, &(Bool){1});
    Expr *callee = Expr_new(_t3531, call_line, call_col, &p->path);
    (void)callee;
    ExprData_delete(_t3531, &(Bool){1});
    Expr_add_child(call, callee);
    while (1) {
        Bool _t3519 = check(p, TokenType_RParen());
        (void)_t3519;
        Bool _t3520 = check(p, TokenType_Eof());
        (void)_t3520;
        Bool _t3521 = Bool_not(_t3519);
        (void)_t3521;
        ;
        Bool _t3522 = Bool_not(_t3520);
        (void)_t3522;
        ;
        Bool _wcond3499 = Bool_and(_t3521, _t3522);
        (void)_wcond3499;
        ;
        ;
        if (_wcond3499) {
        } else {
            ;
            break;
        }
        ;
        Bool _t3523 = check(p, TokenType_Ident());
        (void)_t3523;
        if (_t3523) {
            U64 _t3510 = 1;
            (void)_t3510;
            U64 _t3511 = U64_add(p->pos, _t3510);
            (void)_t3511;
            ;
            U64 _t3512; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3512 = *_hp; free(_hp); }
            (void)_t3512;
            Bool _t3513; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3511}, &(U64){_t3512}); _t3513 = *_hp; free(_hp); }
            (void)_t3513;
            ;
            ;
            if (_t3513) {
                U64 _t3505 = 1;
                (void)_t3505;
                U64 _t3506 = U64_add(p->pos, _t3505);
                (void)_t3506;
                ;
                I64 _t3507 = U64_to_i64(_t3506);
                (void)_t3507;
                ;
                U64 *_t3508 = malloc(sizeof(U64)); *_t3508 = I64_to_u64(_t3507);
                (void)_t3508;
                ;
                Token *next_tok = Vec_get(&p->tokens, _t3508);
                (void)next_tok;
                Bool _t3509; { Bool *_hp = (Bool *)TokenType_eq(&next_tok->type, TokenType_Eq()); _t3509 = *_hp; free(_hp); }
                (void)_t3509;
                U64_delete(_t3508, &(Bool){1});
                if (_t3509) {
                    U32 na_line = peek_line(p);
                    (void)na_line;
                    U32 na_col = peek_col(p);
                    (void)na_col;
                    Str *aname = expect_text(p, TokenType_Ident());
                    (void)aname;
                    Token *_t3501 = advance(p);
                    (void)_t3501;
                    ExprData *_t3502 = ExprData_NamedArg(aname);
                    (void)_t3502;
                    Str_delete(aname, &(Bool){1});
                    Expr *na = Expr_new(_t3502, na_line, na_col, &p->path);
                    (void)na;
                    ExprData_delete(_t3502, &(Bool){1});
                    ;
                    ;
                    Expr *_t3503 = parse_expression(p);
                    (void)_t3503;
                    Expr_add_child(na, _t3503);
                    Expr_add_child(call, na);
                    Bool _t3504 = check(p, TokenType_Comma());
                    (void)_t3504;
                    if (_t3504) {
                        Token *_t3500 = advance(p);
                        (void)_t3500;
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
        Bool _t3524 = check(p, TokenType_DotDot());
        (void)_t3524;
        if (_t3524) {
            Token *_t3514 = advance(p);
            (void)_t3514;
            Bool _t3515 = 1;
            (void)_t3515;
            is_splat = _t3515;
            ;
        }
        ;
        Bool is_own_arg = 0;
        (void)is_own_arg;
        Bool _t3525 = check(p, TokenType_KwOwn());
        (void)_t3525;
        if (_t3525) {
            Token *_t3516 = advance(p);
            (void)_t3516;
            Bool _t3517 = 1;
            (void)_t3517;
            is_own_arg = _t3517;
            ;
        }
        ;
        Expr *arg = parse_expression(p);
        (void)arg;
        Bool _t3526 = Bool_clone(&(Bool){is_own_arg});
        (void)_t3526;
        ;
        arg->is_own_arg = _t3526;
        ;
        Bool _t3527 = Bool_clone(&(Bool){is_splat});
        (void)_t3527;
        ;
        arg->is_splat = _t3527;
        ;
        Expr_add_child(call, arg);
        Bool _t3528 = check(p, TokenType_Comma());
        (void)_t3528;
        if (_t3528) {
            Token *_t3518 = advance(p);
            (void)_t3518;
        }
        ;
    }
    Token *_t3532 = expect_token(p, TokenType_RParen());
    (void)_t3532;
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
    U32 _t3739 = 0;
    (void)_t3739;
    U32 _t3740 = 0;
    (void)_t3740;
    Expr *e = Expr_new(ExprData_Body(), _t3739, _t3740, &p->path);
    (void)e;
    ;
    ;
    Bool e_set = 0;
    (void)e_set;
    Bool _t3741; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t3741 = *_hp; free(_hp); }
    (void)_t3741;
    if (_t3741) {
        Token *_t3533 = advance(p);
        (void)_t3533;
        Str *_t3534 = Str_clone(&t->text);
        (void)_t3534;
        ExprData *_t3535 = ExprData_LiteralStr(_t3534);
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
    Bool _t3742 = Bool_not(e_set);
    (void)_t3742;
    Bool _t3743; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t3743 = *_hp; free(_hp); }
    (void)_t3743;
    Bool _t3744 = Bool_and(_t3742, _t3743);
    (void)_t3744;
    ;
    ;
    if (_t3744) {
        Token *_t3537 = advance(p);
        (void)_t3537;
        Str *_t3538 = Str_clone(&t->text);
        (void)_t3538;
        ExprData *_t3539 = ExprData_LiteralNum(_t3538);
        (void)_t3539;
        Str_delete(_t3538, &(Bool){1});
        e = Expr_new(_t3539, t_line, t_col, &p->path);
        ExprData_delete(_t3539, &(Bool){1});
        Bool _t3540 = 1;
        (void)_t3540;
        e_set = _t3540;
        ;
    }
    ;
    Bool _t3745 = Bool_not(e_set);
    (void)_t3745;
    Bool _t3746; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Minus()); _t3746 = *_hp; free(_hp); }
    (void)_t3746;
    Bool _t3747 = Bool_and(_t3745, _t3746);
    (void)_t3747;
    ;
    ;
    if (_t3747) {
        U64 _t3556 = 1;
        (void)_t3556;
        U64 _t3557 = U64_add(p->pos, _t3556);
        (void)_t3557;
        ;
        U64 _t3558; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3558 = *_hp; free(_hp); }
        (void)_t3558;
        Bool _t3559; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3557}, &(U64){_t3558}); _t3559 = *_hp; free(_hp); }
        (void)_t3559;
        ;
        ;
        if (_t3559) {
            U64 _t3551 = 1;
            (void)_t3551;
            U64 _t3552 = U64_add(p->pos, _t3551);
            (void)_t3552;
            ;
            I64 _t3553 = U64_to_i64(_t3552);
            (void)_t3553;
            ;
            U64 *_t3554 = malloc(sizeof(U64)); *_t3554 = I64_to_u64(_t3553);
            (void)_t3554;
            ;
            Token *next_tok = Vec_get(&p->tokens, _t3554);
            (void)next_tok;
            Bool _t3555; { Bool *_hp = (Bool *)TokenType_eq(&next_tok->type, TokenType_Number()); _t3555 = *_hp; free(_hp); }
            (void)_t3555;
            U64_delete(_t3554, &(Bool){1});
            if (_t3555) {
                Token *_t3541 = advance(p);
                (void)_t3541;
                Token *num_tok = advance(p);
                (void)num_tok;
                Str *_t3542 = Str_lit("0", 1ULL);
                (void)_t3542;
                Str *_t3543 = Str_clone(_t3542);
                (void)_t3543;
                Str_delete(_t3542, &(Bool){1});
                ExprData *_t3544 = ExprData_LiteralNum(_t3543);
                (void)_t3544;
                Str_delete(_t3543, &(Bool){1});
                Expr *zero = Expr_new(_t3544, t_line, t_col, &p->path);
                (void)zero;
                ExprData_delete(_t3544, &(Bool){1});
                Str *_t3545 = Str_lit("sub", 3ULL);
                (void)_t3545;
                Str *_t3546 = Str_clone(_t3545);
                (void)_t3546;
                Str_delete(_t3545, &(Bool){1});
                ExprData *_t3547 = ExprData_FieldAccess(_t3546);
                (void)_t3547;
                Str_delete(_t3546, &(Bool){1});
                Expr *sub_access = Expr_new(_t3547, t_line, t_col, &p->path);
                (void)sub_access;
                ExprData_delete(_t3547, &(Bool){1});
                Expr_add_child(sub_access, zero);
                Expr *sub_call = Expr_new(ExprData_FCall(), t_line, t_col, &p->path);
                (void)sub_call;
                Expr_add_child(sub_call, sub_access);
                Str *_t3548 = Str_clone(&num_tok->text);
                (void)_t3548;
                ExprData *_t3549 = ExprData_LiteralNum(_t3548);
                (void)_t3549;
                Str_delete(_t3548, &(Bool){1});
                Expr *num_arg = Expr_new(_t3549, t_line, t_col, &p->path);
                (void)num_arg;
                ExprData_delete(_t3549, &(Bool){1});
                Expr_add_child(sub_call, num_arg);
                e = Expr_clone(sub_call);
                Expr_delete(sub_call, &(Bool){1});
                Bool _t3550 = 1;
                (void)_t3550;
                e_set = _t3550;
                ;
            }
            ;
        }
        ;
    }
    ;
    Bool _t3748 = Bool_not(e_set);
    (void)_t3748;
    Bool _t3749; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Char()); _t3749 = *_hp; free(_hp); }
    (void)_t3749;
    Bool _t3750 = Bool_and(_t3748, _t3749);
    (void)_t3750;
    ;
    ;
    if (_t3750) {
        Token *_t3589 = advance(p);
        (void)_t3589;
        Str *ch = Str_clone(&t->text);
        (void)ch;
        I64 byte_val = 0;
        (void)byte_val;
        U64 _t3590; { U64 *_hp = (U64 *)Str_len(ch); _t3590 = *_hp; free(_hp); }
        (void)_t3590;
        U64 _t3591 = 0;
        (void)_t3591;
        U64 *_t3592 = malloc(sizeof(U64));
        *_t3592 = 0;
        (void)_t3592;
        U8 *_t3593 = Str_get(ch, _t3592);
        (void)_t3593;
        U8 _t3594 = 92;
        (void)_t3594;
        Bool _t3595; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3590}, &(U64){_t3591}); _t3595 = *_hp; free(_hp); }
        (void)_t3595;
        ;
        ;
        Bool _t3596 = U8_eq(DEREF(_t3593), _t3594);
        (void)_t3596;
        U64_delete(_t3592, &(Bool){1});
        ;
        Bool _t3597 = Bool_and(_t3595, _t3596);
        (void)_t3597;
        ;
        ;
        if (_t3597) {
            U64 _t3580; { U64 *_hp = (U64 *)Str_len(ch); _t3580 = *_hp; free(_hp); }
            (void)_t3580;
            U64 _t3581 = 1;
            (void)_t3581;
            Bool _t3582; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3580}, &(U64){_t3581}); _t3582 = *_hp; free(_hp); }
            (void)_t3582;
            ;
            ;
            if (_t3582) {
                U64 *_t3577 = malloc(sizeof(U64));
                *_t3577 = 1;
                (void)_t3577;
                U8 *c2 = Str_get(ch, _t3577);
                (void)c2;
                U8 _t3578 = 110;
                (void)_t3578;
                Bool _t3579 = U8_eq(DEREF(c2), _t3578);
                (void)_t3579;
                ;
                if (_t3579) {
                    I64 _t3560 = 10;
                    (void)_t3560;
                    byte_val = _t3560;
                    ;
                } else {
                    U8 _t3575 = 116;
                    (void)_t3575;
                    Bool _t3576 = U8_eq(DEREF(c2), _t3575);
                    (void)_t3576;
                    ;
                    if (_t3576) {
                        I64 _t3561 = 9;
                        (void)_t3561;
                        byte_val = _t3561;
                        ;
                    } else {
                        U8 _t3573 = 114;
                        (void)_t3573;
                        Bool _t3574 = U8_eq(DEREF(c2), _t3573);
                        (void)_t3574;
                        ;
                        if (_t3574) {
                            I64 _t3562 = 13;
                            (void)_t3562;
                            byte_val = _t3562;
                            ;
                        } else {
                            U8 _t3571 = 92;
                            (void)_t3571;
                            Bool _t3572 = U8_eq(DEREF(c2), _t3571);
                            (void)_t3572;
                            ;
                            if (_t3572) {
                                I64 _t3563 = 92;
                                (void)_t3563;
                                byte_val = _t3563;
                                ;
                            } else {
                                U8 _t3569 = 39;
                                (void)_t3569;
                                Bool _t3570 = U8_eq(DEREF(c2), _t3569);
                                (void)_t3570;
                                ;
                                if (_t3570) {
                                    I64 _t3564 = 39;
                                    (void)_t3564;
                                    byte_val = _t3564;
                                    ;
                                } else {
                                    U8 _t3567 = 48;
                                    (void)_t3567;
                                    Bool _t3568 = U8_eq(DEREF(c2), _t3567);
                                    (void)_t3568;
                                    ;
                                    if (_t3568) {
                                        I64 _t3565 = 0;
                                        (void)_t3565;
                                        byte_val = _t3565;
                                        ;
                                    } else {
                                        I64 _t3566 = U8_to_i64(DEREF(c2));
                                        (void)_t3566;
                                        byte_val = _t3566;
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
                U64_delete(_t3577, &(Bool){1});
                ;
            }
            ;
        } else {
            U64 _t3586; { U64 *_hp = (U64 *)Str_len(ch); _t3586 = *_hp; free(_hp); }
            (void)_t3586;
            U64 _t3587 = 0;
            (void)_t3587;
            Bool _t3588; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3586}, &(U64){_t3587}); _t3588 = *_hp; free(_hp); }
            (void)_t3588;
            ;
            ;
            if (_t3588) {
                U64 *_t3583 = malloc(sizeof(U64));
                *_t3583 = 0;
                (void)_t3583;
                U8 *_t3584 = Str_get(ch, _t3583);
                (void)_t3584;
                I64 _t3585 = U8_to_i64(DEREF(_t3584));
                (void)_t3585;
                U64_delete(_t3583, &(Bool){1});
                byte_val = _t3585;
                ;
            }
            ;
        }
        ;
        Str_delete(ch, &(Bool){1});
        Str *_t3598 = I64_to_str(&(I64){byte_val});
        (void)_t3598;
        ;
        ExprData *_t3599 = ExprData_LiteralNum(_t3598);
        (void)_t3599;
        Str_delete(_t3598, &(Bool){1});
        e = Expr_new(_t3599, t_line, t_col, &p->path);
        ExprData_delete(_t3599, &(Bool){1});
        TilType_delete(&e->til_type, &(Bool){0});
        { TilType *_fa = TilType_clone(TilType_U8()); e->til_type = *_fa; free(_fa); }
        Bool _t3600 = 1;
        (void)_t3600;
        e_set = _t3600;
        ;
    }
    ;
    Bool _t3751; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t3751 = *_hp; free(_hp); }
    (void)_t3751;
    Bool _t3752; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t3752 = *_hp; free(_hp); }
    (void)_t3752;
    Bool _t3753 = Bool_not(e_set);
    (void)_t3753;
    Bool _t3754 = Bool_or(_t3751, _t3752);
    (void)_t3754;
    ;
    ;
    Bool _t3755 = Bool_and(_t3753, _t3754);
    (void)_t3755;
    ;
    ;
    if (_t3755) {
        Token *_t3601 = advance(p);
        (void)_t3601;
        Str *_t3602 = Str_clone(&t->text);
        (void)_t3602;
        ExprData *_t3603 = ExprData_LiteralBool(_t3602);
        (void)_t3603;
        Str_delete(_t3602, &(Bool){1});
        e = Expr_new(_t3603, t_line, t_col, &p->path);
        ExprData_delete(_t3603, &(Bool){1});
        Bool _t3604 = 1;
        (void)_t3604;
        e_set = _t3604;
        ;
    }
    ;
    Bool _t3756 = Bool_not(e_set);
    (void)_t3756;
    Bool _t3757; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwNull()); _t3757 = *_hp; free(_hp); }
    (void)_t3757;
    Bool _t3758 = Bool_and(_t3756, _t3757);
    (void)_t3758;
    ;
    ;
    if (_t3758) {
        Token *_t3605 = advance(p);
        (void)_t3605;
        e = Expr_new(ExprData_LiteralNull(), t_line, t_col, &p->path);
        Bool _t3606 = 1;
        (void)_t3606;
        e_set = _t3606;
        ;
    }
    ;
    Bool _t3759 = Bool_not(e_set);
    (void)_t3759;
    Bool _t3760; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t3760 = *_hp; free(_hp); }
    (void)_t3760;
    Bool _t3761 = Bool_and(_t3759, _t3760);
    (void)_t3761;
    ;
    ;
    if (_t3761) {
        Token *_t3642 = advance(p);
        (void)_t3642;
        Str *name = Str_clone(&t->text);
        (void)name;
        Str *_t3643 = Str_lit("__LOC__", 7ULL);
        (void)_t3643;
        Bool _t3644; { Bool *_hp = (Bool *)Str_eq(name, _t3643); _t3644 = *_hp; free(_hp); }
        (void)_t3644;
        Str_delete(_t3643, &(Bool){1});
        if (_t3644) {
            Str *_t3607 = Str_lit("Str", 3ULL);
            (void)_t3607;
            U64 _t3608; { U64 *_hp = (U64 *)Str_size(); _t3608 = *_hp; free(_hp); }
            (void)_t3608;
            U64 _t3609 = 5;
            (void)_t3609;
            Array *_va67 = Array_new(_t3607, &(U64){_t3608}, &(U64){_t3609});
            (void)_va67;
            Str_delete(_t3607, &(Bool){1});
            ;
            ;
            U64 _t3610 = 0;
            (void)_t3610;
            Str *_t3611 = Str_clone(&p->path);
            (void)_t3611;
            Array_set(_va67, &(U64){_t3610}, _t3611);
            ;
            U64 _t3612 = 1;
            (void)_t3612;
            Str *_t3613 = Str_lit(":", 1ULL);
            (void)_t3613;
            Array_set(_va67, &(U64){_t3612}, _t3613);
            ;
            U64 _t3614 = 2;
            (void)_t3614;
            Str *_t3615 = U32_to_str(&(U32){t_line});
            (void)_t3615;
            Array_set(_va67, &(U64){_t3614}, _t3615);
            ;
            U64 _t3616 = 3;
            (void)_t3616;
            Str *_t3617 = Str_lit(":", 1ULL);
            (void)_t3617;
            Array_set(_va67, &(U64){_t3616}, _t3617);
            ;
            U64 _t3618 = 4;
            (void)_t3618;
            Str *_t3619 = U32_to_str(&(U32){t_col});
            (void)_t3619;
            Array_set(_va67, &(U64){_t3618}, _t3619);
            ;
            Str *_t3620 = format(_va67);
            (void)_t3620;
            ExprData *_t3621 = ExprData_LiteralStr(_t3620);
            (void)_t3621;
            Str_delete(_t3620, &(Bool){1});
            e = Expr_new(_t3621, t_line, t_col, &p->path);
            ExprData_delete(_t3621, &(Bool){1});
            Bool _t3622 = 1;
            (void)_t3622;
            e_set = _t3622;
            ;
        } else {
            Str *_t3640 = Str_lit("__FILE__", 8ULL);
            (void)_t3640;
            Bool _t3641; { Bool *_hp = (Bool *)Str_eq(name, _t3640); _t3641 = *_hp; free(_hp); }
            (void)_t3641;
            Str_delete(_t3640, &(Bool){1});
            if (_t3641) {
                Str *_t3623 = Str_clone(&p->path);
                (void)_t3623;
                ExprData *_t3624 = ExprData_LiteralStr(_t3623);
                (void)_t3624;
                Str_delete(_t3623, &(Bool){1});
                e = Expr_new(_t3624, t_line, t_col, &p->path);
                ExprData_delete(_t3624, &(Bool){1});
                Bool _t3625 = 1;
                (void)_t3625;
                e_set = _t3625;
                ;
            } else {
                Str *_t3638 = Str_lit("__LINE__", 8ULL);
                (void)_t3638;
                Bool _t3639; { Bool *_hp = (Bool *)Str_eq(name, _t3638); _t3639 = *_hp; free(_hp); }
                (void)_t3639;
                Str_delete(_t3638, &(Bool){1});
                if (_t3639) {
                    Str *_t3626 = U32_to_str(&(U32){t_line});
                    (void)_t3626;
                    ExprData *_t3627 = ExprData_LiteralNum(_t3626);
                    (void)_t3627;
                    Str_delete(_t3626, &(Bool){1});
                    e = Expr_new(_t3627, t_line, t_col, &p->path);
                    ExprData_delete(_t3627, &(Bool){1});
                    Bool _t3628 = 1;
                    (void)_t3628;
                    e_set = _t3628;
                    ;
                } else {
                    Str *_t3636 = Str_lit("__COL__", 7ULL);
                    (void)_t3636;
                    Bool _t3637; { Bool *_hp = (Bool *)Str_eq(name, _t3636); _t3637 = *_hp; free(_hp); }
                    (void)_t3637;
                    Str_delete(_t3636, &(Bool){1});
                    if (_t3637) {
                        Str *_t3629 = U32_to_str(&(U32){t_col});
                        (void)_t3629;
                        ExprData *_t3630 = ExprData_LiteralNum(_t3629);
                        (void)_t3630;
                        Str_delete(_t3629, &(Bool){1});
                        e = Expr_new(_t3630, t_line, t_col, &p->path);
                        ExprData_delete(_t3630, &(Bool){1});
                        Bool _t3631 = 1;
                        (void)_t3631;
                        e_set = _t3631;
                        ;
                    } else {
                        Bool _t3635 = check(p, TokenType_LParen());
                        (void)_t3635;
                        if (_t3635) {
                            e = parse_call(p, name, t_line, t_col);
                            Bool _t3632 = 1;
                            (void)_t3632;
                            e_set = _t3632;
                            ;
                        } else {
                            ExprData *_t3633 = ExprData_Ident(name);
                            (void)_t3633;
                            e = Expr_new(_t3633, t_line, t_col, &p->path);
                            ExprData_delete(_t3633, &(Bool){1});
                            Bool _t3634 = 1;
                            (void)_t3634;
                            e_set = _t3634;
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
    Bool _t3762; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFunc()); _t3762 = *_hp; free(_hp); }
    (void)_t3762;
    Bool _t3763; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwProc()); _t3763 = *_hp; free(_hp); }
    (void)_t3763;
    Bool _t3764 = Bool_or(_t3762, _t3763);
    (void)_t3764;
    ;
    ;
    Bool _t3765; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTest()); _t3765 = *_hp; free(_hp); }
    (void)_t3765;
    Bool _t3766 = Bool_or(_t3764, _t3765);
    (void)_t3766;
    ;
    ;
    Bool _t3767; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMacro()); _t3767 = *_hp; free(_hp); }
    (void)_t3767;
    Bool _t3768 = Bool_or(_t3766, _t3767);
    (void)_t3768;
    ;
    ;
    Bool _t3769; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtFunc()); _t3769 = *_hp; free(_hp); }
    (void)_t3769;
    Bool _t3770 = Bool_or(_t3768, _t3769);
    (void)_t3770;
    ;
    ;
    Bool _t3771; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtProc()); _t3771 = *_hp; free(_hp); }
    (void)_t3771;
    Bool _t3772 = Bool_not(e_set);
    (void)_t3772;
    Bool _t3773 = Bool_or(_t3770, _t3771);
    (void)_t3773;
    ;
    ;
    Bool _t3774 = Bool_and(_t3772, _t3773);
    (void)_t3774;
    ;
    ;
    if (_t3774) {
        Expr *_t3645 = parse_func_def(p);
        (void)_t3645;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3645;
    }
    ;
    Bool _t3775; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwStruct()); _t3775 = *_hp; free(_hp); }
    (void)_t3775;
    Bool _t3776; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwExtStruct()); _t3776 = *_hp; free(_hp); }
    (void)_t3776;
    Bool _t3777 = Bool_not(e_set);
    (void)_t3777;
    Bool _t3778 = Bool_or(_t3775, _t3776);
    (void)_t3778;
    ;
    ;
    Bool _t3779 = Bool_and(_t3777, _t3778);
    (void)_t3779;
    ;
    ;
    if (_t3779) {
        Expr *_t3646 = parse_struct_def(p);
        (void)_t3646;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3646;
    }
    ;
    Bool _t3780 = Bool_not(e_set);
    (void)_t3780;
    Bool _t3781; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwEnum()); _t3781 = *_hp; free(_hp); }
    (void)_t3781;
    Bool _t3782 = Bool_and(_t3780, _t3781);
    (void)_t3782;
    ;
    ;
    if (_t3782) {
        Expr *_t3647 = parse_enum_def(p);
        (void)_t3647;
        ;
        Expr_delete(e, &(Bool){1});
        ;
        ;
        ;
        return _t3647;
    }
    ;
    Bool _t3783 = Bool_not(e_set);
    (void)_t3783;
    Bool _t3784; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t3784 = *_hp; free(_hp); }
    (void)_t3784;
    Bool _t3785 = Bool_and(_t3783, _t3784);
    (void)_t3785;
    ;
    ;
    if (_t3785) {
        Token *_t3672 = advance(p);
        (void)_t3672;
        Expr *first = parse_expression(p);
        (void)first;
        Bool _t3673 = check(p, TokenType_Colon());
        (void)_t3673;
        if (_t3673) {
            e = Expr_new(ExprData_MapLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Token *_t3659 = advance(p);
            (void)_t3659;
            Expr *_t3660 = parse_expression(p);
            (void)_t3660;
            Expr_add_child(e, _t3660);
            Bool _t3661 = check(p, TokenType_Comma());
            (void)_t3661;
            if (_t3661) {
                Token *_t3648 = advance(p);
                (void)_t3648;
            }
            ;
            while (1) {
                Bool _t3651 = check(p, TokenType_RBrace());
                (void)_t3651;
                Bool _t3652 = check(p, TokenType_Eof());
                (void)_t3652;
                Bool _t3653 = Bool_not(_t3651);
                (void)_t3653;
                ;
                Bool _t3654 = Bool_not(_t3652);
                (void)_t3654;
                ;
                Bool _wcond3649 = Bool_and(_t3653, _t3654);
                (void)_wcond3649;
                ;
                ;
                if (_wcond3649) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3655 = parse_expression(p);
                (void)_t3655;
                Expr_add_child(e, _t3655);
                Token *_t3656 = expect_token(p, TokenType_Colon());
                (void)_t3656;
                Expr *_t3657 = parse_expression(p);
                (void)_t3657;
                Expr_add_child(e, _t3657);
                Bool _t3658 = check(p, TokenType_Comma());
                (void)_t3658;
                if (_t3658) {
                    Token *_t3650 = advance(p);
                    (void)_t3650;
                }
                ;
            }
        } else {
            e = Expr_new(ExprData_SetLit(), t_line, t_col, &p->path);
            Expr_add_child(e, first);
            Bool _t3671 = check(p, TokenType_Comma());
            (void)_t3671;
            if (_t3671) {
                Token *_t3662 = advance(p);
                (void)_t3662;
            }
            ;
            while (1) {
                Bool _t3665 = check(p, TokenType_RBrace());
                (void)_t3665;
                Bool _t3666 = check(p, TokenType_Eof());
                (void)_t3666;
                Bool _t3667 = Bool_not(_t3665);
                (void)_t3667;
                ;
                Bool _t3668 = Bool_not(_t3666);
                (void)_t3668;
                ;
                Bool _wcond3663 = Bool_and(_t3667, _t3668);
                (void)_wcond3663;
                ;
                ;
                if (_wcond3663) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t3669 = parse_expression(p);
                (void)_t3669;
                Expr_add_child(e, _t3669);
                Bool _t3670 = check(p, TokenType_Comma());
                (void)_t3670;
                if (_t3670) {
                    Token *_t3664 = advance(p);
                    (void)_t3664;
                }
                ;
            }
        }
        ;
        Token *_t3674 = expect_token(p, TokenType_RBrace());
        (void)_t3674;
        Bool _t3675 = 1;
        (void)_t3675;
        e_set = _t3675;
        ;
    }
    ;
    Bool _t3786 = Bool_not(e_set);
    (void)_t3786;
    ;
    if (_t3786) {
        Str *_t3676 = Str_lit("Str", 3ULL);
        (void)_t3676;
        U64 _t3677; { U64 *_hp = (U64 *)Str_size(); _t3677 = *_hp; free(_hp); }
        (void)_t3677;
        U64 _t3678 = 8;
        (void)_t3678;
        Array *_va68 = Array_new(_t3676, &(U64){_t3677}, &(U64){_t3678});
        (void)_va68;
        Str_delete(_t3676, &(Bool){1});
        ;
        ;
        U64 _t3679 = 0;
        (void)_t3679;
        Str *_t3680 = Str_clone(&p->path);
        (void)_t3680;
        Array_set(_va68, &(U64){_t3679}, _t3680);
        ;
        U64 _t3681 = 1;
        (void)_t3681;
        Str *_t3682 = Str_lit(":", 1ULL);
        (void)_t3682;
        Array_set(_va68, &(U64){_t3681}, _t3682);
        ;
        U64 _t3683 = 2;
        (void)_t3683;
        Str *_t3684 = U32_to_str(&(U32){t_line});
        (void)_t3684;
        Array_set(_va68, &(U64){_t3683}, _t3684);
        ;
        U64 _t3685 = 3;
        (void)_t3685;
        Str *_t3686 = Str_lit(":", 1ULL);
        (void)_t3686;
        Array_set(_va68, &(U64){_t3685}, _t3686);
        ;
        U64 _t3687 = 4;
        (void)_t3687;
        Str *_t3688 = U32_to_str(&(U32){t_col});
        (void)_t3688;
        Array_set(_va68, &(U64){_t3687}, _t3688);
        ;
        U64 _t3689 = 5;
        (void)_t3689;
        Str *_t3690 = Str_lit(": unexpected token '", 20ULL);
        (void)_t3690;
        Array_set(_va68, &(U64){_t3689}, _t3690);
        ;
        U64 _t3691 = 6;
        (void)_t3691;
        Str *_t3692 = Str_clone(&t->text);
        (void)_t3692;
        Array_set(_va68, &(U64){_t3691}, _t3692);
        ;
        U64 _t3693 = 7;
        (void)_t3693;
        Str *_t3694 = Str_lit("'", 1ULL);
        (void)_t3694;
        Array_set(_va68, &(U64){_t3693}, _t3694);
        ;
        Str *_t3695 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:536:15", 64ULL);
        (void)_t3695;
        panic(_t3695, _va68);
        Str_delete(_t3695, &(Bool){1});
    }
    ;
    ;
    ;
    while (1) {
        Bool _wcond3696 = check(p, TokenType_Dot());
        (void)_wcond3696;
        if (_wcond3696) {
        } else {
            ;
            break;
        }
        ;
        Token *_t3729 = advance(p);
        (void)_t3729;
        U32 f_line = peek_line(p);
        (void)f_line;
        U32 f_col = peek_col(p);
        (void)f_col;
        Str *fname = expect_text(p, TokenType_Ident());
        (void)fname;
        Bool _t3730 = check(p, TokenType_LParen());
        (void)_t3730;
        if (_t3730) {
            Token *_t3723 = advance(p);
            (void)_t3723;
            ExprData *_t3724 = ExprData_FieldAccess(fname);
            (void)_t3724;
            Expr *callee = Expr_new(_t3724, f_line, f_col, &p->path);
            (void)callee;
            ExprData_delete(_t3724, &(Bool){1});
            Expr *_t3725 = Expr_clone(e);
            (void)_t3725;
            Expr_add_child(callee, _t3725);
            Expr *mcall = Expr_new(ExprData_FCall(), f_line, f_col, &p->path);
            (void)mcall;
            Expr_add_child(mcall, callee);
            while (1) {
                Bool _t3715 = check(p, TokenType_RParen());
                (void)_t3715;
                Bool _t3716 = check(p, TokenType_Eof());
                (void)_t3716;
                Bool _t3717 = Bool_not(_t3715);
                (void)_t3717;
                ;
                Bool _t3718 = Bool_not(_t3716);
                (void)_t3718;
                ;
                Bool _wcond3697 = Bool_and(_t3717, _t3718);
                (void)_wcond3697;
                ;
                ;
                if (_wcond3697) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3719 = check(p, TokenType_Ident());
                (void)_t3719;
                if (_t3719) {
                    U64 _t3708 = 1;
                    (void)_t3708;
                    U64 _t3709 = U64_add(p->pos, _t3708);
                    (void)_t3709;
                    ;
                    U64 _t3710; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3710 = *_hp; free(_hp); }
                    (void)_t3710;
                    Bool _t3711; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3709}, &(U64){_t3710}); _t3711 = *_hp; free(_hp); }
                    (void)_t3711;
                    ;
                    ;
                    if (_t3711) {
                        U64 _t3703 = 1;
                        (void)_t3703;
                        U64 _t3704 = U64_add(p->pos, _t3703);
                        (void)_t3704;
                        ;
                        I64 _t3705 = U64_to_i64(_t3704);
                        (void)_t3705;
                        ;
                        U64 *_t3706 = malloc(sizeof(U64)); *_t3706 = I64_to_u64(_t3705);
                        (void)_t3706;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3706);
                        (void)nt;
                        Bool _t3707; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3707 = *_hp; free(_hp); }
                        (void)_t3707;
                        U64_delete(_t3706, &(Bool){1});
                        if (_t3707) {
                            U32 na_line = peek_line(p);
                            (void)na_line;
                            U32 na_col = peek_col(p);
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3699 = advance(p);
                            (void)_t3699;
                            ExprData *_t3700 = ExprData_NamedArg(aname);
                            (void)_t3700;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3700, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3700, &(Bool){1});
                            ;
                            ;
                            Expr *_t3701 = parse_expression(p);
                            (void)_t3701;
                            Expr_add_child(na, _t3701);
                            Expr_add_child(mcall, na);
                            Bool _t3702 = check(p, TokenType_Comma());
                            (void)_t3702;
                            if (_t3702) {
                                Token *_t3698 = advance(p);
                                (void)_t3698;
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
                Bool _t3720 = check(p, TokenType_KwOwn());
                (void)_t3720;
                if (_t3720) {
                    Token *_t3712 = advance(p);
                    (void)_t3712;
                    Bool _t3713 = 1;
                    (void)_t3713;
                    is_own_arg = _t3713;
                    ;
                }
                ;
                Expr *marg = parse_expression(p);
                (void)marg;
                Bool _t3721 = Bool_clone(&(Bool){is_own_arg});
                (void)_t3721;
                ;
                marg->is_own_arg = _t3721;
                ;
                Expr_add_child(mcall, marg);
                Bool _t3722 = check(p, TokenType_Comma());
                (void)_t3722;
                if (_t3722) {
                    Token *_t3714 = advance(p);
                    (void)_t3714;
                }
                ;
            }
            Token *_t3726 = expect_token(p, TokenType_RParen());
            (void)_t3726;
            e = Expr_clone(mcall);
            Expr_delete(mcall, &(Bool){1});
        } else {
            ExprData *_t3727 = ExprData_FieldAccess(fname);
            (void)_t3727;
            Expr *access = Expr_new(_t3727, f_line, f_col, &p->path);
            (void)access;
            ExprData_delete(_t3727, &(Bool){1});
            Expr *_t3728 = Expr_clone(e);
            (void)_t3728;
            Expr_add_child(access, _t3728);
            e = Expr_clone(access);
            Expr_delete(access, &(Bool){1});
        }
        ;
        ;
        ;
        Str_delete(fname, &(Bool){1});
    }
    Bool _t3787 = check(p, TokenType_DotDot());
    (void)_t3787;
    if (_t3787) {
        U32 dt_line = peek_line(p);
        (void)dt_line;
        U32 dt_col = peek_col(p);
        (void)dt_col;
        Token *_t3731 = advance(p);
        (void)_t3731;
        Expr *rhs = parse_expression(p);
        (void)rhs;
        Str *_t3732 = Str_lit("Range", 5ULL);
        (void)_t3732;
        Str *_t3733 = Str_clone(_t3732);
        (void)_t3733;
        Str_delete(_t3732, &(Bool){1});
        ExprData *_t3734 = ExprData_Ident(_t3733);
        (void)_t3734;
        Str_delete(_t3733, &(Bool){1});
        Expr *range_ident = Expr_new(_t3734, dt_line, dt_col, &p->path);
        (void)range_ident;
        ExprData_delete(_t3734, &(Bool){1});
        Str *_t3735 = Str_lit("new", 3ULL);
        (void)_t3735;
        Str *_t3736 = Str_clone(_t3735);
        (void)_t3736;
        Str_delete(_t3735, &(Bool){1});
        ExprData *_t3737 = ExprData_FieldAccess(_t3736);
        (void)_t3737;
        Str_delete(_t3736, &(Bool){1});
        Expr *new_access = Expr_new(_t3737, dt_line, dt_col, &p->path);
        (void)new_access;
        ExprData_delete(_t3737, &(Bool){1});
        Expr_add_child(new_access, range_ident);
        Expr *rcall = Expr_new(ExprData_FCall(), dt_line, dt_col, &p->path);
        (void)rcall;
        ;
        ;
        Expr_add_child(rcall, new_access);
        Expr *_t3738 = Expr_clone(e);
        (void)_t3738;
        Expr_add_child(rcall, _t3738);
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
    Bool _t3974 = check(p, TokenType_ColonEq());
    (void)_t3974;
    if (_t3974) {
        Token *_t3788 = advance(p);
        (void)_t3788;
        Bool _t3789 = Bool_clone(&(Bool){is_mut});
        (void)_t3789;
        Bool _t3790 = 0;
        (void)_t3790;
        Bool _t3791 = 0;
        (void)_t3791;
        Bool _t3792 = Bool_clone(&(Bool){is_own});
        (void)_t3792;
        I32 _t3793 = 0;
        (void)_t3793;
        I32 _t3794 = 0;
        (void)_t3794;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3789;
        dd->is_namespace = _t3790;
        dd->is_ref = _t3791;
        dd->is_own = _t3792;
        dd->field_offset = _t3793;
        dd->field_size = _t3794;
        dd->field_struct_def = NULL;
        dd->fn_sig = NULL;
        (void)dd;
        ;
        ;
        ;
        ;
        ;
        ;
        ExprData *_t3795 = ExprData_Decl(dd);
        (void)_t3795;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3795, t_line, t_col, &p->path);
        (void)decl;
        ExprData_delete(_t3795, &(Bool){1});
        Expr *_t3796 = parse_expression(p);
        (void)_t3796;
        Expr_add_child(decl, _t3796);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return decl;
    }
    ;
    Bool _t3975 = check(p, TokenType_Colon());
    (void)_t3975;
    if (_t3975) {
        Token *_t3908 = advance(p);
        (void)_t3908;
        Bool _t3909 = check(p, TokenType_KwFunc());
        (void)_t3909;
        Bool _t3910 = check(p, TokenType_KwProc());
        (void)_t3910;
        Bool _t3911 = Bool_or(_t3909, _t3910);
        (void)_t3911;
        ;
        ;
        if (_t3911) {
            Expr *sig = parse_func_def(p);
            (void)sig;
            Token *_t3814 = expect_token(p, TokenType_Eq());
            (void)_t3814;
            Token *_t3815 = expect_token(p, TokenType_LParen());
            (void)_t3815;
            Bool _t3816; { Bool *_hp = (Bool *)ExprData_is_FuncDef(&sig->data); _t3816 = *_hp; free(_hp); }
            (void)_t3816;
            if (_t3816) {
                FunctionDef *sfd = ExprData_get_FuncDef(&sig->data);
                (void)sfd;
                Str *_t3811 = Str_lit("Str", 3ULL);
                (void)_t3811;
                U64 _t3812; { U64 *_hp = (U64 *)Str_size(); _t3812 = *_hp; free(_hp); }
                (void)_t3812;
                Vec *new_names = Vec_new(_t3811, &(U64){_t3812});
                (void)new_names;
                Str_delete(_t3811, &(Bool){1});
                ;
                Vec_delete(new_names, &(Bool){1});
                {
                    U64 _fi3797 = 0;
                    (void)_fi3797;
                    while (1) {
                        U64 _t3800 = 0;
                        (void)_t3800;
                        U64 _t3801; { U64 *_hp = (U64 *)Vec_len(&sfd->params); _t3801 = *_hp; free(_hp); }
                        (void)_t3801;
                        Range *_t3802 = Range_new(_t3800, _t3801);
                        (void)_t3802;
                        ;
                        ;
                        U64 _t3803; { U64 *_hp = (U64 *)Range_len(_t3802); _t3803 = *_hp; free(_hp); }
                        (void)_t3803;
                        Range_delete(_t3802, &(Bool){1});
                        Bool _wcond3798; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3797}, &(U64){_t3803}); _wcond3798 = *_hp; free(_hp); }
                        (void)_wcond3798;
                        ;
                        if (_wcond3798) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 _t3804 = 0;
                        (void)_t3804;
                        U64 _t3805; { U64 *_hp = (U64 *)Vec_len(&sfd->params); _t3805 = *_hp; free(_hp); }
                        (void)_t3805;
                        Range *_t3806 = Range_new(_t3804, _t3805);
                        (void)_t3806;
                        ;
                        ;
                        U64 *pi = Range_get(_t3806, _fi3797);
                        (void)pi;
                        Range_delete(_t3806, &(Bool){1});
                        U64 _t3807 = 1;
                        (void)_t3807;
                        U64 _t3808 = U64_add(_fi3797, _t3807);
                        (void)_t3808;
                        ;
                        _fi3797 = _t3808;
                        ;
                        U64 _t3809 = 0;
                        (void)_t3809;
                        Bool _t3810; { Bool *_hp = (Bool *)U64_gt(pi, &(U64){_t3809}); _t3810 = *_hp; free(_hp); }
                        (void)_t3810;
                        ;
                        if (_t3810) {
                            Token *_t3799 = expect_token(p, TokenType_Comma());
                            (void)_t3799;
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
            Bool _t3817 = check(p, TokenType_Comma());
            (void)_t3817;
            if (_t3817) {
                Token *_t3813 = advance(p);
                (void)_t3813;
            }
            ;
            Token *_t3818 = expect_token(p, TokenType_RParen());
            (void)_t3818;
            Token *_t3819 = expect_token(p, TokenType_LBrace());
            (void)_t3819;
            Expr *_t3820 = parse_block(p);
            (void)_t3820;
            Expr_add_child(sig, _t3820);
            Bool _t3821 = Bool_clone(&(Bool){is_mut});
            (void)_t3821;
            Bool _t3822 = 0;
            (void)_t3822;
            Bool _t3823 = 0;
            (void)_t3823;
            Bool _t3824 = Bool_clone(&(Bool){is_own});
            (void)_t3824;
            I32 _t3825 = 0;
            (void)_t3825;
            I32 _t3826 = 0;
            (void)_t3826;
            Declaration *dd = malloc(sizeof(Declaration));
            { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
            { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
            dd->is_mut = _t3821;
            dd->is_namespace = _t3822;
            dd->is_ref = _t3823;
            dd->is_own = _t3824;
            dd->field_offset = _t3825;
            dd->field_size = _t3826;
            dd->field_struct_def = NULL;
            dd->fn_sig = NULL;
            (void)dd;
            ;
            ;
            ;
            ;
            ;
            ;
            ExprData *_t3827 = ExprData_Decl(dd);
            (void)_t3827;
            Declaration_delete(dd, &(Bool){1});
            Expr *decl = Expr_new(_t3827, t_line, t_col, &p->path);
            (void)decl;
            ExprData_delete(_t3827, &(Bool){1});
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
        Str *_t3912 = Str_lit("Fn", 2ULL);
        (void)_t3912;
        Bool _t3913; { Bool *_hp = (Bool *)Str_eq(type_name, _t3912); _t3913 = *_hp; free(_hp); }
        (void)_t3913;
        Str_delete(_t3912, &(Bool){1});
        if (_t3913) {
            Str *syn_name = parse_fn_signature(p, t_line, t_col);
            (void)syn_name;
            U64 _t3828; { U64 *_hp = (U64 *)Str_len(syn_name); _t3828 = *_hp; free(_hp); }
            (void)_t3828;
            U64 _t3829 = 0;
            (void)_t3829;
            Bool _t3830; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3828}, &(U64){_t3829}); _t3830 = *_hp; free(_hp); }
            (void)_t3830;
            ;
            ;
            if (_t3830) {
                type_name = Str_clone(syn_name);
            }
            ;
            Str_delete(syn_name, &(Bool){1});
        }
        ;
        Token *_t3914 = expect_token(p, TokenType_Eq());
        (void)_t3914;
        Bool _t3915 = check(p, TokenType_LParen());
        (void)_t3915;
        if (_t3915) {
            U64 saved = p->pos;
            (void)saved;
            Token *_t3904 = advance(p);
            (void)_t3904;
            Bool is_fsf = 1;
            (void)is_fsf;
            while (1) {
                Bool _t3834 = check(p, TokenType_RParen());
                (void)_t3834;
                Bool _t3835 = check(p, TokenType_Eof());
                (void)_t3835;
                Bool _t3836 = Bool_not(_t3834);
                (void)_t3836;
                ;
                Bool _t3837 = Bool_not(_t3835);
                (void)_t3837;
                ;
                Bool _wcond3831 = Bool_and(_t3836, _t3837);
                (void)_wcond3831;
                ;
                ;
                if (_wcond3831) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3838 = check(p, TokenType_Ident());
                (void)_t3838;
                Bool _t3839 = Bool_not(_t3838);
                (void)_t3839;
                ;
                if (_t3839) {
                    Bool _t3832 = 0;
                    (void)_t3832;
                    is_fsf = _t3832;
                    ;
                    ;
                    break;
                }
                ;
                Token *_t3840 = advance(p);
                (void)_t3840;
                Bool _t3841 = check(p, TokenType_Comma());
                (void)_t3841;
                if (_t3841) {
                    Token *_t3833 = advance(p);
                    (void)_t3833;
                }
                ;
            }
            Bool _t3905 = check(p, TokenType_RParen());
            (void)_t3905;
            Bool _t3906 = Bool_and(is_fsf, _t3905);
            (void)_t3906;
            ;
            if (_t3906) {
                Token *_t3843 = advance(p);
                (void)_t3843;
                Bool _t3844 = check(p, TokenType_LBrace());
                (void)_t3844;
                Bool _t3845 = Bool_not(_t3844);
                (void)_t3845;
                ;
                if (_t3845) {
                    Bool _t3842 = 0;
                    (void)_t3842;
                    is_fsf = _t3842;
                    ;
                }
                ;
            } else {
                Bool _t3846 = 0;
                (void)_t3846;
                is_fsf = _t3846;
                ;
            }
            ;
            U64 _t3907 = U64_clone(&(U64){saved});
            (void)_t3907;
            ;
            p->pos = _t3907;
            ;
            if (is_fsf) {
                Token *_t3864 = expect_token(p, TokenType_LParen());
                (void)_t3864;
                Str *_t3865 = Str_lit("Str", 3ULL);
                (void)_t3865;
                U64 _t3866; { U64 *_hp = (U64 *)Str_size(); _t3866 = *_hp; free(_hp); }
                (void)_t3866;
                Vec *pnames = Vec_new(_t3865, &(U64){_t3866});
                (void)pnames;
                Str_delete(_t3865, &(Bool){1});
                ;
                while (1) {
                    Bool _t3849 = check(p, TokenType_RParen());
                    (void)_t3849;
                    Bool _wcond3847 = Bool_not(_t3849);
                    (void)_wcond3847;
                    ;
                    if (_wcond3847) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *pn = expect_text(p, TokenType_Ident());
                    (void)pn;
                    Vec_push(pnames, pn);
                    Bool _t3850 = check(p, TokenType_Comma());
                    (void)_t3850;
                    if (_t3850) {
                        Token *_t3848 = advance(p);
                        (void)_t3848;
                    }
                    ;
                }
                Token *_t3867 = expect_token(p, TokenType_RParen());
                (void)_t3867;
                Token *_t3868 = expect_token(p, TokenType_LBrace());
                (void)_t3868;
                Expr *body = parse_block(p);
                (void)body;
                Str *_t3869 = Str_lit("Param", 5ULL);
                (void)_t3869;
                U64 _t3870; { U64 *_hp = (U64 *)Param_size(); _t3870 = *_hp; free(_hp); }
                (void)_t3870;
                Str *_t3871 = Str_lit("Str", 3ULL);
                (void)_t3871;
                U64 _t3872; { U64 *_hp = (U64 *)Str_size(); _t3872 = *_hp; free(_hp); }
                (void)_t3872;
                Str *_t3873 = Str_lit("Expr", 4ULL);
                (void)_t3873;
                U64 _t3874; { U64 *_hp = (U64 *)Expr_size(); _t3874 = *_hp; free(_hp); }
                (void)_t3874;
                I64 _t3875 = 0;
                (void)_t3875;
                I64 _t3876 = 1;
                (void)_t3876;
                I64 _t3877 = I64_sub(_t3875, _t3876);
                (void)_t3877;
                ;
                ;
                I64 _t3878 = 0;
                (void)_t3878;
                I64 _t3879 = 1;
                (void)_t3879;
                I64 _t3880 = I64_sub(_t3878, _t3879);
                (void)_t3880;
                ;
                ;
                U32 _t3881 = 0;
                (void)_t3881;
                I32 _t3882 = I64_to_i32(_t3877);
                (void)_t3882;
                ;
                I32 _t3883 = I64_to_i32(_t3880);
                (void)_t3883;
                ;
                Bool _t3884 = 0;
                (void)_t3884;
                Bool _t3885 = 0;
                (void)_t3885;
                FunctionDef *ffd = malloc(sizeof(FunctionDef));
                { FuncType *_ca = FuncType_clone(FuncType_Func()); ffd->func_type = *_ca; free(_ca); }
                { Vec *_ca = Vec_new(_t3869, &(U64){_t3870}); ffd->params = *_ca; free(_ca); }
                ffd->nparam = _t3881;
                { Map *_ca = Map_new(_t3871, &(U64){_t3872}, _t3873, &(U64){_t3874}); ffd->param_defaults = *_ca; free(_ca); }
                { Str *_ca = Str_clone(Str_lit("", 0ULL)); ffd->return_type = *_ca; free(_ca); }
                ffd->variadic_index = _t3882;
                ffd->kwargs_index = _t3883;
                ffd->return_is_ref = _t3884;
                ffd->return_is_shallow = _t3885;
                (void)ffd;
                Str_delete(_t3869, &(Bool){1});
                ;
                Str_delete(_t3871, &(Bool){1});
                ;
                Str_delete(_t3873, &(Bool){1});
                ;
                ;
                ;
                ;
                ;
                ;
                FuncType_delete(&ffd->func_type, &(Bool){0});
                { FuncType *_fa = FuncType_clone(FuncType_Func()); ffd->func_type = *_fa; free(_fa); }
                I64 _t3886 = 0;
                (void)_t3886;
                I64 _t3887 = 1;
                (void)_t3887;
                I64 _t3888 = I64_sub(_t3886, _t3887);
                (void)_t3888;
                ;
                ;
                I32 _t3889 = I64_to_i32(_t3888);
                (void)_t3889;
                ;
                ffd->variadic_index = _t3889;
                ;
                I64 _t3890 = 0;
                (void)_t3890;
                I64 _t3891 = 1;
                (void)_t3891;
                I64 _t3892 = I64_sub(_t3890, _t3891);
                (void)_t3892;
                ;
                ;
                I32 _t3893 = I64_to_i32(_t3892);
                (void)_t3893;
                ;
                ffd->kwargs_index = _t3893;
                ;
                U64 np; { U64 *_hp = (U64 *)Vec_len(pnames); np = *_hp; free(_hp); }
                (void)np;
                {
                    U64 _fi3851 = 0;
                    (void)_fi3851;
                    while (1) {
                        U64 _t3853 = 0;
                        (void)_t3853;
                        Range *_t3854 = Range_new(_t3853, np);
                        (void)_t3854;
                        ;
                        U64 _t3855; { U64 *_hp = (U64 *)Range_len(_t3854); _t3855 = *_hp; free(_hp); }
                        (void)_t3855;
                        Range_delete(_t3854, &(Bool){1});
                        Bool _wcond3852; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3851}, &(U64){_t3855}); _wcond3852 = *_hp; free(_hp); }
                        (void)_wcond3852;
                        ;
                        if (_wcond3852) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U64 _t3856 = 0;
                        (void)_t3856;
                        Range *_t3857 = Range_new(_t3856, np);
                        (void)_t3857;
                        ;
                        U64 *i = Range_get(_t3857, _fi3851);
                        (void)i;
                        Range_delete(_t3857, &(Bool){1});
                        U64 _t3858 = 1;
                        (void)_t3858;
                        U64 _t3859 = U64_add(_fi3851, _t3858);
                        (void)_t3859;
                        ;
                        _fi3851 = _t3859;
                        ;
                        Str *pn = Vec_get(pnames, i);
                        (void)pn;
                        Bool _t3860 = 0;
                        (void)_t3860;
                        Bool _t3861 = 0;
                        (void)_t3861;
                        Bool _t3862 = 0;
                        (void)_t3862;
                        Param *_t3863 = malloc(sizeof(Param));
                        { Str *_ca = Str_clone(pn); _t3863->name = *_ca; free(_ca); }
                        { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t3863->ptype = *_ca; free(_ca); }
                        _t3863->is_mut = _t3860;
                        _t3863->is_own = _t3861;
                        _t3863->is_shallow = _t3862;
                        (void)_t3863;
                        ;
                        ;
                        ;
                        U64_delete(i, &(Bool){1});
                        Vec_push(&ffd->params, _t3863);
                    }
                    ;
                }
                Vec_delete(pnames, &(Bool){1});
                I64 _t3894 = U64_to_i64(np);
                (void)_t3894;
                ;
                U32 _t3895 = I64_to_u32(_t3894);
                (void)_t3895;
                ;
                ffd->nparam = _t3895;
                ;
                ExprData *_t3896 = ExprData_FuncDef(ffd);
                (void)_t3896;
                FunctionDef_delete(ffd, &(Bool){1});
                Expr *fdef = Expr_new(_t3896, t_line, t_col, &p->path);
                (void)fdef;
                ExprData_delete(_t3896, &(Bool){1});
                Expr_add_child(fdef, body);
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
                ExprData *_t3903 = ExprData_Decl(dd);
                (void)_t3903;
                Declaration_delete(dd, &(Bool){1});
                Expr *decl = Expr_new(_t3903, t_line, t_col, &p->path);
                (void)decl;
                ExprData_delete(_t3903, &(Bool){1});
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
        Bool _t3916 = Bool_clone(&(Bool){is_mut});
        (void)_t3916;
        Bool _t3917 = 0;
        (void)_t3917;
        Bool _t3918 = 0;
        (void)_t3918;
        Bool _t3919 = Bool_clone(&(Bool){is_own});
        (void)_t3919;
        I32 _t3920 = 0;
        (void)_t3920;
        I32 _t3921 = 0;
        (void)_t3921;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(name); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(type_name); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t3916;
        dd->is_namespace = _t3917;
        dd->is_ref = _t3918;
        dd->is_own = _t3919;
        dd->field_offset = _t3920;
        dd->field_size = _t3921;
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
        ExprData *_t3922 = ExprData_Decl(dd);
        (void)_t3922;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t3922, t_line, t_col, &p->path);
        (void)decl;
        ExprData_delete(_t3922, &(Bool){1});
        Expr *_t3923 = parse_expression(p);
        (void)_t3923;
        Expr_add_child(decl, _t3923);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return decl;
    }
    ;
    Bool _t3976 = check(p, TokenType_Dot());
    (void)_t3976;
    if (_t3976) {
        Str *_t3962 = Str_clone(name);
        (void)_t3962;
        ExprData *_t3963 = ExprData_Ident(_t3962);
        (void)_t3963;
        Str_delete(_t3962, &(Bool){1});
        Expr *obj = Expr_new(_t3963, t_line, t_col, &p->path);
        (void)obj;
        ExprData_delete(_t3963, &(Bool){1});
        Str *last_field = Str_lit("", 0ULL);
        (void)last_field;
        U32 last_line = 0;
        (void)last_line;
        U32 last_col = 0;
        (void)last_col;
        while (1) {
            Bool _wcond3924 = check(p, TokenType_Dot());
            (void)_wcond3924;
            if (_wcond3924) {
            } else {
                ;
                break;
            }
            ;
            Token *_t3928 = advance(p);
            (void)_t3928;
            U32 _t3929 = peek_line(p);
            (void)_t3929;
            last_line = _t3929;
            ;
            U32 _t3930 = peek_col(p);
            (void)_t3930;
            last_col = _t3930;
            ;
            last_field = expect_text(p, TokenType_Ident());
            Bool _t3931 = check(p, TokenType_Dot());
            (void)_t3931;
            if (_t3931) {
                Str *_t3925 = Str_clone(last_field);
                (void)_t3925;
                ExprData *_t3926 = ExprData_FieldAccess(_t3925);
                (void)_t3926;
                Str_delete(_t3925, &(Bool){1});
                Expr *access = Expr_new(_t3926, last_line, last_col, &p->path);
                (void)access;
                ExprData_delete(_t3926, &(Bool){1});
                Expr *_t3927 = Expr_clone(obj);
                (void)_t3927;
                Expr_add_child(access, _t3927);
                obj = Expr_clone(access);
                Expr_delete(access, &(Bool){1});
            }
            ;
        }
        Bool _t3964 = check(p, TokenType_LParen());
        (void)_t3964;
        if (_t3964) {
            Token *_t3958 = advance(p);
            (void)_t3958;
            ExprData *_t3959 = ExprData_FieldAccess(last_field);
            (void)_t3959;
            Expr *callee = Expr_new(_t3959, last_line, last_col, &p->path);
            (void)callee;
            ExprData_delete(_t3959, &(Bool){1});
            Expr *_t3960 = Expr_clone(obj);
            (void)_t3960;
            Expr_add_child(callee, _t3960);
            Expr *mcall = Expr_new(ExprData_FCall(), last_line, last_col, &p->path);
            (void)mcall;
            Expr_add_child(mcall, callee);
            while (1) {
                Bool _t3950 = check(p, TokenType_RParen());
                (void)_t3950;
                Bool _t3951 = check(p, TokenType_Eof());
                (void)_t3951;
                Bool _t3952 = Bool_not(_t3950);
                (void)_t3952;
                ;
                Bool _t3953 = Bool_not(_t3951);
                (void)_t3953;
                ;
                Bool _wcond3932 = Bool_and(_t3952, _t3953);
                (void)_wcond3932;
                ;
                ;
                if (_wcond3932) {
                } else {
                    ;
                    break;
                }
                ;
                Bool _t3954 = check(p, TokenType_Ident());
                (void)_t3954;
                if (_t3954) {
                    U64 _t3943 = 1;
                    (void)_t3943;
                    U64 _t3944 = U64_add(p->pos, _t3943);
                    (void)_t3944;
                    ;
                    U64 _t3945; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t3945 = *_hp; free(_hp); }
                    (void)_t3945;
                    Bool _t3946; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3944}, &(U64){_t3945}); _t3946 = *_hp; free(_hp); }
                    (void)_t3946;
                    ;
                    ;
                    if (_t3946) {
                        U64 _t3938 = 1;
                        (void)_t3938;
                        U64 _t3939 = U64_add(p->pos, _t3938);
                        (void)_t3939;
                        ;
                        I64 _t3940 = U64_to_i64(_t3939);
                        (void)_t3940;
                        ;
                        U64 *_t3941 = malloc(sizeof(U64)); *_t3941 = I64_to_u64(_t3940);
                        (void)_t3941;
                        ;
                        Token *nt = Vec_get(&p->tokens, _t3941);
                        (void)nt;
                        Bool _t3942; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Eq()); _t3942 = *_hp; free(_hp); }
                        (void)_t3942;
                        U64_delete(_t3941, &(Bool){1});
                        if (_t3942) {
                            U32 na_line = peek_line(p);
                            (void)na_line;
                            U32 na_col = peek_col(p);
                            (void)na_col;
                            Str *aname = expect_text(p, TokenType_Ident());
                            (void)aname;
                            Token *_t3934 = advance(p);
                            (void)_t3934;
                            ExprData *_t3935 = ExprData_NamedArg(aname);
                            (void)_t3935;
                            Str_delete(aname, &(Bool){1});
                            Expr *na = Expr_new(_t3935, na_line, na_col, &p->path);
                            (void)na;
                            ExprData_delete(_t3935, &(Bool){1});
                            ;
                            ;
                            Expr *_t3936 = parse_expression(p);
                            (void)_t3936;
                            Expr_add_child(na, _t3936);
                            Expr_add_child(mcall, na);
                            Bool _t3937 = check(p, TokenType_Comma());
                            (void)_t3937;
                            if (_t3937) {
                                Token *_t3933 = advance(p);
                                (void)_t3933;
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
                Bool _t3955 = check(p, TokenType_KwOwn());
                (void)_t3955;
                if (_t3955) {
                    Token *_t3947 = advance(p);
                    (void)_t3947;
                    Bool _t3948 = 1;
                    (void)_t3948;
                    is_own_arg = _t3948;
                    ;
                }
                ;
                Expr *marg = parse_expression(p);
                (void)marg;
                Bool _t3956 = Bool_clone(&(Bool){is_own_arg});
                (void)_t3956;
                ;
                marg->is_own_arg = _t3956;
                ;
                Expr_add_child(mcall, marg);
                Bool _t3957 = check(p, TokenType_Comma());
                (void)_t3957;
                if (_t3957) {
                    Token *_t3949 = advance(p);
                    (void)_t3949;
                }
                ;
            }
            Token *_t3961 = expect_token(p, TokenType_RParen());
            (void)_t3961;
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
        Token *_t3965 = expect_token(p, TokenType_Eq());
        (void)_t3965;
        ExprData *_t3966 = ExprData_FieldAssign(last_field);
        (void)_t3966;
        Str_delete(last_field, &(Bool){1});
        Expr *fa = Expr_new(_t3966, t_line, t_col, &p->path);
        (void)fa;
        ExprData_delete(_t3966, &(Bool){1});
        Expr *_t3967 = Expr_clone(obj);
        (void)_t3967;
        Expr_delete(obj, &(Bool){1});
        Expr_add_child(fa, _t3967);
        Expr *_t3968 = parse_expression(p);
        (void)_t3968;
        Expr_add_child(fa, _t3968);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return fa;
    }
    ;
    Bool _t3977 = check(p, TokenType_Eq());
    (void)_t3977;
    if (_t3977) {
        Token *_t3969 = advance(p);
        (void)_t3969;
        Str *_t3970 = Str_clone(name);
        (void)_t3970;
        ExprData *_t3971 = ExprData_Assign(_t3970);
        (void)_t3971;
        Str_delete(_t3970, &(Bool){1});
        Expr *assign = Expr_new(_t3971, t_line, t_col, &p->path);
        (void)assign;
        ExprData_delete(_t3971, &(Bool){1});
        Expr *_t3972 = parse_expression(p);
        (void)_t3972;
        Expr_add_child(assign, _t3972);
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return assign;
    }
    ;
    Bool _t3978 = check(p, TokenType_LParen());
    (void)_t3978;
    if (_t3978) {
        Expr *_t3973 = parse_call(p, name, t_line, t_col);
        (void)_t3973;
        ;
        Str_delete(name, &(Bool){1});
        ;
        ;
        return _t3973;
    }
    ;
    Str *_t3979 = Str_lit("Str", 3ULL);
    (void)_t3979;
    U64 _t3980; { U64 *_hp = (U64 *)Str_size(); _t3980 = *_hp; free(_hp); }
    (void)_t3980;
    U64 _t3981 = 8;
    (void)_t3981;
    Array *_va69 = Array_new(_t3979, &(U64){_t3980}, &(U64){_t3981});
    (void)_va69;
    Str_delete(_t3979, &(Bool){1});
    ;
    ;
    U64 _t3982 = 0;
    (void)_t3982;
    Str *_t3983 = Str_clone(&p->path);
    (void)_t3983;
    Array_set(_va69, &(U64){_t3982}, _t3983);
    ;
    U64 _t3984 = 1;
    (void)_t3984;
    Str *_t3985 = Str_lit(":", 1ULL);
    (void)_t3985;
    Array_set(_va69, &(U64){_t3984}, _t3985);
    ;
    U64 _t3986 = 2;
    (void)_t3986;
    Str *_t3987 = U32_to_str(&(U32){t_line});
    (void)_t3987;
    ;
    Array_set(_va69, &(U64){_t3986}, _t3987);
    ;
    U64 _t3988 = 3;
    (void)_t3988;
    Str *_t3989 = Str_lit(":", 1ULL);
    (void)_t3989;
    Array_set(_va69, &(U64){_t3988}, _t3989);
    ;
    U64 _t3990 = 4;
    (void)_t3990;
    Str *_t3991 = U32_to_str(&(U32){t_col});
    (void)_t3991;
    ;
    Array_set(_va69, &(U64){_t3990}, _t3991);
    ;
    U64 _t3992 = 5;
    (void)_t3992;
    Str *_t3993 = Str_lit(": expected ':=', ':', '=' or '(' after identifier '", 51ULL);
    (void)_t3993;
    Array_set(_va69, &(U64){_t3992}, _t3993);
    ;
    U64 _t3994 = 6;
    (void)_t3994;
    Str *_t3995 = Str_clone(name);
    (void)_t3995;
    Str_delete(name, &(Bool){1});
    Array_set(_va69, &(U64){_t3994}, _t3995);
    ;
    U64 _t3996 = 7;
    (void)_t3996;
    Str *_t3997 = Str_lit("'", 1ULL);
    (void)_t3997;
    Array_set(_va69, &(U64){_t3996}, _t3997);
    ;
    Str *_t3998 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:797:11", 64ULL);
    (void)_t3998;
    panic(_t3998, _va69);
    Str_delete(_t3998, &(Bool){1});
    U32 _t3999 = 0;
    (void)_t3999;
    U32 _t4000 = 0;
    (void)_t4000;
    Expr *_t4001 = Expr_new(ExprData_Body(), _t3999, _t4000, &p->path);
    (void)_t4001;
    ;
    ;
    return _t4001;
}

Expr * parse_statement(Parser * p) {
    (void)p;
    U32 t_line = peek_line(p);
    (void)t_line;
    U32 t_col = peek_col(p);
    (void)t_col;
    Token *t = peek(p);
    (void)t;
    Bool _t4139; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Ident()); _t4139 = *_hp; free(_hp); }
    (void)_t4139;
    if (_t4139) {
        Bool _t4002 = 0;
        (void)_t4002;
        Bool _t4003 = 0;
        (void)_t4003;
        Expr *_t4004 = parse_statement_ident(p, _t4002, _t4003);
        (void)_t4004;
        ;
        ;
        ;
        ;
        ;
        return _t4004;
    }
    ;
    Bool _t4140; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwRef()); _t4140 = *_hp; free(_hp); }
    (void)_t4140;
    if (_t4140) {
        Token *_t4011 = advance(p);
        (void)_t4011;
        Bool ref_mut = 0;
        (void)ref_mut;
        Bool _t4012 = check(p, TokenType_KwMut());
        (void)_t4012;
        if (_t4012) {
            Token *_t4005 = advance(p);
            (void)_t4005;
            Bool _t4006 = 1;
            (void)_t4006;
            ref_mut = _t4006;
            ;
        }
        ;
        U32 i_line = peek_line(p);
        (void)i_line;
        U32 i_col = peek_col(p);
        (void)i_col;
        Str *iname = expect_text(p, TokenType_Ident());
        (void)iname;
        Bool _t4013 = 0;
        (void)_t4013;
        Bool _t4014 = 0;
        (void)_t4014;
        Bool _t4015 = 1;
        (void)_t4015;
        Bool _t4016 = 0;
        (void)_t4016;
        I32 _t4017 = 0;
        (void)_t4017;
        I32 _t4018 = 0;
        (void)_t4018;
        Declaration *dd = malloc(sizeof(Declaration));
        { Str *_ca = Str_clone(iname); dd->name = *_ca; free(_ca); }
        { Str *_ca = Str_clone(Str_lit("", 0ULL)); dd->explicit_type = *_ca; free(_ca); }
        dd->is_mut = _t4013;
        dd->is_namespace = _t4014;
        dd->is_ref = _t4015;
        dd->is_own = _t4016;
        dd->field_offset = _t4017;
        dd->field_size = _t4018;
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
            Bool _t4007 = 1;
            (void)_t4007;
            dd->is_mut = _t4007;
            ;
        }
        ;
        Bool _t4019 = check(p, TokenType_Colon());
        (void)_t4019;
        if (_t4019) {
            Token *_t4008 = advance(p);
            (void)_t4008;
            Str_delete(&dd->explicit_type, &(Bool){0});
            { Str *_fa = expect_text(p, TokenType_Ident()); dd->explicit_type = *_fa; free(_fa); }
            Token *_t4009 = expect_token(p, TokenType_Eq());
            (void)_t4009;
        } else {
            Token *_t4010 = expect_token(p, TokenType_ColonEq());
            (void)_t4010;
        }
        ;
        ExprData *_t4020 = ExprData_Decl(dd);
        (void)_t4020;
        Declaration_delete(dd, &(Bool){1});
        Expr *decl = Expr_new(_t4020, i_line, i_col, &p->path);
        (void)decl;
        ExprData_delete(_t4020, &(Bool){1});
        ;
        ;
        Expr *_t4021 = parse_expression(p);
        (void)_t4021;
        Expr_add_child(decl, _t4021);
        ;
        ;
        ;
        return decl;
    }
    ;
    Bool _t4141; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwMut()); _t4141 = *_hp; free(_hp); }
    (void)_t4141;
    if (_t4141) {
        Token *_t4022 = advance(p);
        (void)_t4022;
        Bool _t4023 = 1;
        (void)_t4023;
        Bool _t4024 = 0;
        (void)_t4024;
        Expr *_t4025 = parse_statement_ident(p, _t4023, _t4024);
        (void)_t4025;
        ;
        ;
        ;
        ;
        ;
        return _t4025;
    }
    ;
    Bool _t4142; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwReturn()); _t4142 = *_hp; free(_hp); }
    (void)_t4142;
    if (_t4142) {
        Token *_t4027 = advance(p);
        (void)_t4027;
        Expr *ret = Expr_new(ExprData_Return(), t_line, t_col, &p->path);
        (void)ret;
        Bool _t4028 = check(p, TokenType_RBrace());
        (void)_t4028;
        Bool _t4029 = check(p, TokenType_Eof());
        (void)_t4029;
        Bool _t4030 = Bool_not(_t4028);
        (void)_t4030;
        ;
        Bool _t4031 = Bool_not(_t4029);
        (void)_t4031;
        ;
        Bool _t4032 = Bool_and(_t4030, _t4031);
        (void)_t4032;
        ;
        ;
        if (_t4032) {
            Expr *_t4026 = parse_expression(p);
            (void)_t4026;
            Expr_add_child(ret, _t4026);
        }
        ;
        ;
        ;
        ;
        return ret;
    }
    ;
    Bool _t4143; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwIf()); _t4143 = *_hp; free(_hp); }
    (void)_t4143;
    if (_t4143) {
        Token *_t4040 = advance(p);
        (void)_t4040;
        Expr *node = Expr_new(ExprData_If(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t4041 = parse_expression(p);
        (void)_t4041;
        Expr_add_child(node, _t4041);
        Token *_t4042 = expect_token(p, TokenType_LBrace());
        (void)_t4042;
        Expr *_t4043 = parse_block(p);
        (void)_t4043;
        Expr_add_child(node, _t4043);
        Bool _t4044 = check(p, TokenType_KwElse());
        (void)_t4044;
        if (_t4044) {
            Token *_t4038 = advance(p);
            (void)_t4038;
            Bool _t4039 = check(p, TokenType_KwIf());
            (void)_t4039;
            if (_t4039) {
                U32 _t4033 = peek_line(p);
                (void)_t4033;
                U32 _t4034 = peek_col(p);
                (void)_t4034;
                Expr *else_body = Expr_new(ExprData_Body(), _t4033, _t4034, &p->path);
                (void)else_body;
                ;
                ;
                Expr *_t4035 = parse_statement(p);
                (void)_t4035;
                Expr_add_child(else_body, _t4035);
                Expr_add_child(node, else_body);
            } else {
                Token *_t4036 = expect_token(p, TokenType_LBrace());
                (void)_t4036;
                Expr *_t4037 = parse_block(p);
                (void)_t4037;
                Expr_add_child(node, _t4037);
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
    Bool _t4144; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_StringTok()); _t4144 = *_hp; free(_hp); }
    (void)_t4144;
    Bool _t4145; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_Number()); _t4145 = *_hp; free(_hp); }
    (void)_t4145;
    Bool _t4146 = Bool_or(_t4144, _t4145);
    (void)_t4146;
    ;
    ;
    Bool _t4147; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwTrue()); _t4147 = *_hp; free(_hp); }
    (void)_t4147;
    Bool _t4148 = Bool_or(_t4146, _t4147);
    (void)_t4148;
    ;
    ;
    Bool _t4149; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFalse()); _t4149 = *_hp; free(_hp); }
    (void)_t4149;
    Bool _t4150 = Bool_or(_t4148, _t4149);
    (void)_t4150;
    ;
    ;
    Bool _t4151; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwNull()); _t4151 = *_hp; free(_hp); }
    (void)_t4151;
    Bool _t4152 = Bool_or(_t4150, _t4151);
    (void)_t4152;
    ;
    ;
    if (_t4152) {
        Expr *_t4045 = parse_expression(p);
        (void)_t4045;
        ;
        ;
        ;
        return _t4045;
    }
    ;
    Bool _t4153; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_LBrace()); _t4153 = *_hp; free(_hp); }
    (void)_t4153;
    if (_t4153) {
        Token *_t4046 = advance(p);
        (void)_t4046;
        Expr *_t4047 = parse_block(p);
        (void)_t4047;
        ;
        ;
        ;
        return _t4047;
    }
    ;
    Bool _t4154; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwWhile()); _t4154 = *_hp; free(_hp); }
    (void)_t4154;
    if (_t4154) {
        Token *_t4048 = advance(p);
        (void)_t4048;
        Expr *node = Expr_new(ExprData_While(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t4049 = parse_expression(p);
        (void)_t4049;
        Expr_add_child(node, _t4049);
        Token *_t4050 = expect_token(p, TokenType_LBrace());
        (void)_t4050;
        Expr *_t4051 = parse_block(p);
        (void)_t4051;
        Expr_add_child(node, _t4051);
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4155; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwFor()); _t4155 = *_hp; free(_hp); }
    (void)_t4155;
    if (_t4155) {
        Token *_t4053 = advance(p);
        (void)_t4053;
        U32 i_line = peek_line(p);
        (void)i_line;
        U32 i_col = peek_col(p);
        (void)i_col;
        Str *iname = expect_text(p, TokenType_Ident());
        (void)iname;
        ExprData *_t4054 = ExprData_ForIn(iname);
        (void)_t4054;
        Str_delete(iname, &(Bool){1});
        Expr *node = Expr_new(_t4054, i_line, i_col, &p->path);
        (void)node;
        ExprData_delete(_t4054, &(Bool){1});
        ;
        ;
        Bool _t4055 = check(p, TokenType_Colon());
        (void)_t4055;
        if (_t4055) {
            Token *_t4052 = advance(p);
            (void)_t4052;
            Str_delete(&node->struct_name, &(Bool){0});
            { Str *_fa = expect_text(p, TokenType_Ident()); node->struct_name = *_fa; free(_fa); }
        }
        ;
        Token *_t4056 = expect_token(p, TokenType_KwIn());
        (void)_t4056;
        Expr *_t4057 = parse_expression(p);
        (void)_t4057;
        Expr_add_child(node, _t4057);
        Token *_t4058 = expect_token(p, TokenType_LBrace());
        (void)_t4058;
        Expr *_t4059 = parse_block(p);
        (void)_t4059;
        Expr_add_child(node, _t4059);
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4156; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwSwitch()); _t4156 = *_hp; free(_hp); }
    (void)_t4156;
    if (_t4156) {
        Token *_t4083 = advance(p);
        (void)_t4083;
        Expr *node = Expr_new(ExprData_Switch(), t_line, t_col, &p->path);
        (void)node;
        Expr *_t4084 = parse_expression(p);
        (void)_t4084;
        Expr_add_child(node, _t4084);
        Token *_t4085 = expect_token(p, TokenType_LBrace());
        (void)_t4085;
        while (1) {
            Bool _t4071 = check(p, TokenType_RBrace());
            (void)_t4071;
            Bool _t4072 = check(p, TokenType_Eof());
            (void)_t4072;
            Bool _t4073 = Bool_not(_t4071);
            (void)_t4073;
            ;
            Bool _t4074 = Bool_not(_t4072);
            (void)_t4074;
            ;
            Bool _wcond4060 = Bool_and(_t4073, _t4074);
            (void)_wcond4060;
            ;
            ;
            if (_wcond4060) {
            } else {
                ;
                break;
            }
            ;
            Token *_t4075 = expect_token(p, TokenType_KwCase());
            (void)_t4075;
            U32 _t4076 = peek_line(p);
            (void)_t4076;
            U32 _t4077 = peek_col(p);
            (void)_t4077;
            Expr *cn = Expr_new(ExprData_Case(), _t4076, _t4077, &p->path);
            (void)cn;
            ;
            ;
            Bool _t4078 = check(p, TokenType_Colon());
            (void)_t4078;
            Bool _t4079 = Bool_not(_t4078);
            (void)_t4079;
            ;
            if (_t4079) {
                Expr *_t4061 = parse_expression(p);
                (void)_t4061;
                Expr_add_child(cn, _t4061);
            }
            ;
            Token *_t4080 = expect_token(p, TokenType_Colon());
            (void)_t4080;
            U32 _t4081 = peek_line(p);
            (void)_t4081;
            U32 _t4082 = peek_col(p);
            (void)_t4082;
            Expr *cb = Expr_new(ExprData_Body(), _t4081, _t4082, &p->path);
            (void)cb;
            ;
            ;
            while (1) {
                Bool _t4063 = check(p, TokenType_KwCase());
                (void)_t4063;
                Bool _t4064 = check(p, TokenType_RBrace());
                (void)_t4064;
                Bool _t4065 = Bool_not(_t4063);
                (void)_t4065;
                ;
                Bool _t4066 = Bool_not(_t4064);
                (void)_t4066;
                ;
                Bool _t4067 = check(p, TokenType_Eof());
                (void)_t4067;
                Bool _t4068 = Bool_and(_t4065, _t4066);
                (void)_t4068;
                ;
                ;
                Bool _t4069 = Bool_not(_t4067);
                (void)_t4069;
                ;
                Bool _wcond4062 = Bool_and(_t4068, _t4069);
                (void)_wcond4062;
                ;
                ;
                if (_wcond4062) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *_t4070 = parse_statement(p);
                (void)_t4070;
                Expr_add_child(cb, _t4070);
            }
            Expr_add_child(cn, cb);
            Expr_add_child(node, cn);
        }
        Token *_t4086 = expect_token(p, TokenType_RBrace());
        (void)_t4086;
        ;
        ;
        ;
        return node;
    }
    ;
    Bool _t4157; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwOwn()); _t4157 = *_hp; free(_hp); }
    (void)_t4157;
    if (_t4157) {
        Token *_t4128 = advance(p);
        (void)_t4128;
        Bool _t4129 = check(p, TokenType_Ident());
        (void)_t4129;
        Bool _t4130 = check(p, TokenType_KwMut());
        (void)_t4130;
        Bool _t4131 = Bool_or(_t4129, _t4130);
        (void)_t4131;
        ;
        ;
        if (_t4131) {
            Bool own_mut = 0;
            (void)own_mut;
            Bool _t4118 = check(p, TokenType_KwMut());
            (void)_t4118;
            if (_t4118) {
                Token *_t4087 = advance(p);
                (void)_t4087;
                Bool _t4088 = 1;
                (void)_t4088;
                own_mut = _t4088;
                ;
            }
            ;
            Bool _t4119 = check(p, TokenType_Ident());
            (void)_t4119;
            if (_t4119) {
                U64 _t4098 = 1;
                (void)_t4098;
                U64 _t4099 = U64_add(p->pos, _t4098);
                (void)_t4099;
                ;
                U64 _t4100; { U64 *_hp = (U64 *)Vec_len(&p->tokens); _t4100 = *_hp; free(_hp); }
                (void)_t4100;
                Bool _t4101; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4099}, &(U64){_t4100}); _t4101 = *_hp; free(_hp); }
                (void)_t4101;
                ;
                ;
                if (_t4101) {
                    U64 _t4091 = 1;
                    (void)_t4091;
                    U64 _t4092 = U64_add(p->pos, _t4091);
                    (void)_t4092;
                    ;
                    I64 _t4093 = U64_to_i64(_t4092);
                    (void)_t4093;
                    ;
                    U64 *_t4094 = malloc(sizeof(U64)); *_t4094 = I64_to_u64(_t4093);
                    (void)_t4094;
                    ;
                    Token *nt = Vec_get(&p->tokens, _t4094);
                    (void)nt;
                    Bool _t4095; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_ColonEq()); _t4095 = *_hp; free(_hp); }
                    (void)_t4095;
                    Bool _t4096; { Bool *_hp = (Bool *)TokenType_eq(&nt->type, TokenType_Colon()); _t4096 = *_hp; free(_hp); }
                    (void)_t4096;
                    U64_delete(_t4094, &(Bool){1});
                    Bool _t4097 = Bool_or(_t4095, _t4096);
                    (void)_t4097;
                    ;
                    ;
                    if (_t4097) {
                        Bool _t4089 = 1;
                        (void)_t4089;
                        Expr *_t4090 = parse_statement_ident(p, own_mut, _t4089);
                        (void)_t4090;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        ;
                        return _t4090;
                    }
                    ;
                }
                ;
            }
            ;
            if (own_mut) {
                Str *_t4102 = Str_lit("Str", 3ULL);
                (void)_t4102;
                U64 _t4103; { U64 *_hp = (U64 *)Str_size(); _t4103 = *_hp; free(_hp); }
                (void)_t4103;
                U64 _t4104 = 6;
                (void)_t4104;
                Array *_va70 = Array_new(_t4102, &(U64){_t4103}, &(U64){_t4104});
                (void)_va70;
                Str_delete(_t4102, &(Bool){1});
                ;
                ;
                U64 _t4105 = 0;
                (void)_t4105;
                Str *_t4106 = Str_clone(&p->path);
                (void)_t4106;
                Array_set(_va70, &(U64){_t4105}, _t4106);
                ;
                U64 _t4107 = 1;
                (void)_t4107;
                Str *_t4108 = Str_lit(":", 1ULL);
                (void)_t4108;
                Array_set(_va70, &(U64){_t4107}, _t4108);
                ;
                U64 _t4109 = 2;
                (void)_t4109;
                Str *_t4110 = U32_to_str(&(U32){t_line});
                (void)_t4110;
                Array_set(_va70, &(U64){_t4109}, _t4110);
                ;
                U64 _t4111 = 3;
                (void)_t4111;
                Str *_t4112 = Str_lit(":", 1ULL);
                (void)_t4112;
                Array_set(_va70, &(U64){_t4111}, _t4112);
                ;
                U64 _t4113 = 4;
                (void)_t4113;
                Str *_t4114 = U32_to_str(&(U32){t_col});
                (void)_t4114;
                Array_set(_va70, &(U64){_t4113}, _t4114);
                ;
                U64 _t4115 = 5;
                (void)_t4115;
                Str *_t4116 = Str_lit(": expected identifier after 'own mut'", 37ULL);
                (void)_t4116;
                Array_set(_va70, &(U64){_t4115}, _t4116);
                ;
                Str *_t4117 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:931:23", 64ULL);
                (void)_t4117;
                panic(_t4117, _va70);
                Str_delete(_t4117, &(Bool){1});
            }
            ;
        }
        ;
        Expr *expr = parse_expression(p);
        (void)expr;
        I64 _t4132 = 0;
        (void)_t4132;
        I64 _t4133 = 1;
        (void)_t4133;
        I64 primary_idx = I64_sub(_t4132, _t4133);
        (void)primary_idx;
        ;
        ;
        ;
        Expr *cur = Expr_clone(expr);
        (void)cur;
        while (1) {
            U64 _t4121; { U64 *_hp = (U64 *)Vec_len(&cur->children); _t4121 = *_hp; free(_hp); }
            (void)_t4121;
            U64 _t4122 = 0;
            (void)_t4122;
            Bool _t4123; { Bool *_hp = (Bool *)ExprData_is_FCall(&cur->data); _t4123 = *_hp; free(_hp); }
            (void)_t4123;
            Bool _t4124; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(&cur->data); _t4124 = *_hp; free(_hp); }
            (void)_t4124;
            Bool _t4125; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4121}, &(U64){_t4122}); _t4125 = *_hp; free(_hp); }
            (void)_t4125;
            ;
            ;
            Bool _t4126 = Bool_or(_t4123, _t4124);
            (void)_t4126;
            ;
            ;
            Bool _wcond4120 = Bool_and(_t4125, _t4126);
            (void)_wcond4120;
            ;
            ;
            if (_wcond4120) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t4127 = malloc(sizeof(U64));
            *_t4127 = 0;
            (void)_t4127;
            Expr *ch = Vec_get(&cur->children, _t4127);
            (void)ch;
            cur = Expr_clone(ch);
            U64_delete(_t4127, &(Bool){1});
        }
        Bool _t4134 = 1;
        (void)_t4134;
        cur->is_own_arg = _t4134;
        ;
        Expr_delete(cur, &(Bool){1});
        ;
        ;
        ;
        ;
        return expr;
    }
    ;
    Bool _t4158; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwBreak()); _t4158 = *_hp; free(_hp); }
    (void)_t4158;
    if (_t4158) {
        Token *_t4135 = advance(p);
        (void)_t4135;
        Expr *_t4136 = Expr_new(ExprData_Break(), t_line, t_col, &p->path);
        (void)_t4136;
        ;
        ;
        ;
        return _t4136;
    }
    ;
    Bool _t4159; { Bool *_hp = (Bool *)TokenType_eq(&t->type, TokenType_KwContinue()); _t4159 = *_hp; free(_hp); }
    (void)_t4159;
    if (_t4159) {
        Token *_t4137 = advance(p);
        (void)_t4137;
        Expr *_t4138 = Expr_new(ExprData_Continue(), t_line, t_col, &p->path);
        (void)_t4138;
        ;
        ;
        ;
        return _t4138;
    }
    ;
    Str *_t4160 = Str_lit("Str", 3ULL);
    (void)_t4160;
    U64 _t4161; { U64 *_hp = (U64 *)Str_size(); _t4161 = *_hp; free(_hp); }
    (void)_t4161;
    U64 _t4162 = 8;
    (void)_t4162;
    Array *_va71 = Array_new(_t4160, &(U64){_t4161}, &(U64){_t4162});
    (void)_va71;
    Str_delete(_t4160, &(Bool){1});
    ;
    ;
    U64 _t4163 = 0;
    (void)_t4163;
    Str *_t4164 = Str_clone(&p->path);
    (void)_t4164;
    Array_set(_va71, &(U64){_t4163}, _t4164);
    ;
    U64 _t4165 = 1;
    (void)_t4165;
    Str *_t4166 = Str_lit(":", 1ULL);
    (void)_t4166;
    Array_set(_va71, &(U64){_t4165}, _t4166);
    ;
    U64 _t4167 = 2;
    (void)_t4167;
    Str *_t4168 = U32_to_str(&(U32){t_line});
    (void)_t4168;
    ;
    Array_set(_va71, &(U64){_t4167}, _t4168);
    ;
    U64 _t4169 = 3;
    (void)_t4169;
    Str *_t4170 = Str_lit(":", 1ULL);
    (void)_t4170;
    Array_set(_va71, &(U64){_t4169}, _t4170);
    ;
    U64 _t4171 = 4;
    (void)_t4171;
    Str *_t4172 = U32_to_str(&(U32){t_col});
    (void)_t4172;
    ;
    Array_set(_va71, &(U64){_t4171}, _t4172);
    ;
    U64 _t4173 = 5;
    (void)_t4173;
    Str *_t4174 = Str_lit(": expected statement, found '", 29ULL);
    (void)_t4174;
    Array_set(_va71, &(U64){_t4173}, _t4174);
    ;
    U64 _t4175 = 6;
    (void)_t4175;
    Str *_t4176 = Str_clone(&t->text);
    (void)_t4176;
    Array_set(_va71, &(U64){_t4175}, _t4176);
    ;
    U64 _t4177 = 7;
    (void)_t4177;
    Str *_t4178 = Str_lit("'", 1ULL);
    (void)_t4178;
    Array_set(_va71, &(U64){_t4177}, _t4178);
    ;
    Str *_t4179 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/self/parser.til:958:11", 64ULL);
    (void)_t4179;
    panic(_t4179, _va71);
    Str_delete(_t4179, &(Bool){1});
    U32 _t4180 = 0;
    (void)_t4180;
    U32 _t4181 = 0;
    (void)_t4181;
    Expr *_t4182 = Expr_new(ExprData_Body(), _t4180, _t4181, &p->path);
    (void)_t4182;
    ;
    ;
    return _t4182;
}

Expr * parse(Vec * tokens, Str * path, Str * mode_out) {
    (void)tokens;
    (void)path;
    (void)mode_out;
    Str *_t4206 = Str_lit("Expr", 4ULL);
    (void)_t4206;
    U64 _t4207; { U64 *_hp = (U64 *)Expr_size(); _t4207 = *_hp; free(_hp); }
    (void)_t4207;
    I64 _t4208 = 0;
    (void)_t4208;
    Parser *p = malloc(sizeof(Parser));
    { Vec *_ca = Vec_clone(tokens); p->tokens = *_ca; free(_ca); }
    p->pos = _t4208;
    { Str *_ca = Str_clone(path); p->path = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t4206, &(U64){_t4207}); p->fn_sig_decls = *_ca; free(_ca); }
    (void)p;
    Str_delete(_t4206, &(Bool){1});
    ;
    ;
    Bool _t4209 = check(p, TokenType_KwMode());
    (void)_t4209;
    if (_t4209) {
        Token *_t4187 = advance(p);
        (void)_t4187;
        Bool _t4188 = check(p, TokenType_Ident());
        (void)_t4188;
        Bool _t4189 = check(p, TokenType_KwTest());
        (void)_t4189;
        Bool _t4190 = Bool_or(_t4188, _t4189);
        (void)_t4190;
        ;
        ;
        if (_t4190) {
            Str *_t4183 = Str_clone(&peek(p)->text);
            (void)_t4183;
            U64 _t4184; { U64 *_hp = (U64 *)Str_size(); _t4184 = *_hp; free(_hp); }
            (void)_t4184;
            swap(mode_out, _t4183, _t4184);
            Str_delete(_t4183, &(Bool){1});
            ;
            Token *_t4185 = advance(p);
            (void)_t4185;
        } else {
            Token *_t4186 = expect_token(p, TokenType_Ident());
            (void)_t4186;
        }
        ;
    }
    ;
    U32 _t4210 = 1;
    (void)_t4210;
    U32 _t4211 = 1;
    (void)_t4211;
    Expr *root = Expr_new(ExprData_Body(), _t4210, _t4211, &p->path);
    (void)root;
    ;
    ;
    while (1) {
        Bool _t4192 = check(p, TokenType_Eof());
        (void)_t4192;
        Bool _wcond4191 = Bool_not(_t4192);
        (void)_wcond4191;
        ;
        if (_wcond4191) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t4193 = parse_statement(p);
        (void)_t4193;
        Expr_add_child(root, _t4193);
    }
    {
        U64 _fi4194 = 0;
        (void)_fi4194;
        while (1) {
            U64 _t4196 = 0;
            (void)_t4196;
            U64 _t4197; { U64 *_hp = (U64 *)Vec_len(&p->fn_sig_decls); _t4197 = *_hp; free(_hp); }
            (void)_t4197;
            Range *_t4198 = Range_new(_t4196, _t4197);
            (void)_t4198;
            ;
            ;
            U64 _t4199; { U64 *_hp = (U64 *)Range_len(_t4198); _t4199 = *_hp; free(_hp); }
            (void)_t4199;
            Range_delete(_t4198, &(Bool){1});
            Bool _wcond4195; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi4194}, &(U64){_t4199}); _wcond4195 = *_hp; free(_hp); }
            (void)_wcond4195;
            ;
            if (_wcond4195) {
            } else {
                ;
                break;
            }
            ;
            U64 _t4200 = 0;
            (void)_t4200;
            U64 _t4201; { U64 *_hp = (U64 *)Vec_len(&p->fn_sig_decls); _t4201 = *_hp; free(_hp); }
            (void)_t4201;
            Range *_t4202 = Range_new(_t4200, _t4201);
            (void)_t4202;
            ;
            ;
            U64 *i = Range_get(_t4202, _fi4194);
            (void)i;
            Range_delete(_t4202, &(Bool){1});
            U64 _t4203 = 1;
            (void)_t4203;
            U64 _t4204 = U64_add(_fi4194, _t4203);
            (void)_t4204;
            ;
            _fi4194 = _t4204;
            ;
            Expr *d = Vec_get(&p->fn_sig_decls, i);
            (void)d;
            Expr *_t4205 = Expr_clone(d);
            (void)_t4205;
            U64_delete(i, &(Bool){1});
            Expr_add_child(root, _t4205);
        }
        ;
    }
    Parser_delete(p, &(Bool){1});
    return root;
}

