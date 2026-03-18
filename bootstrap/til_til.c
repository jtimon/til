#include "til_til.h"

Mode * Mode_clone(Mode * self) {
    (void)self;
    Bool _t3042 = Bool_clone(&self->needs_main);
    (void)_t3042;
    Bool _t3043 = Bool_clone(&self->decls_only);
    (void)_t3043;
    Bool _t3044 = Bool_clone(&self->is_pure);
    (void)_t3044;
    Bool _t3045 = Bool_clone(&self->debug_prints);
    (void)_t3045;
    Mode *_t3046 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(&self->name); _t3046->name = *_ca; free(_ca); }
    _t3046->needs_main = _t3042;
    _t3046->decls_only = _t3043;
    { Str *_ca = Str_clone(&self->auto_import); _t3046->auto_import = *_ca; free(_ca); }
    _t3046->is_pure = _t3044;
    _t3046->debug_prints = _t3045;
    (void)_t3046;
    ;
    ;
    ;
    ;
    return _t3046;
}

U64 *Mode_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Mode);
    return r;
}

TypeScope * TypeScope_clone(TypeScope * self) {
    (void)self;
    TypeScope *_t3054 = malloc(sizeof(TypeScope));
    (void)_t3054;
    return _t3054;
}

U64 *TypeScope_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TypeScope);
    return r;
}

Vec * extract_imports(void * body) {
    (void)body;
    Str *_t3085 = Str_lit("Str", 3ULL);
    (void)_t3085;
    U64 _t3086; { U64 *_hp = (U64 *)Str_size(); _t3086 = *_hp; free(_hp); }
    (void)_t3086;
    Vec *paths = Vec_new(_t3085, &(U64){_t3086});
    (void)paths;
    Str_delete(_t3085, &(Bool){1});
    ;
    Vec *kept = expr_vec_new();
    (void)kept;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t3060 = expr_nchildren(body);
        (void)_t3060;
        Bool _wcond3056; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3060}); _wcond3056 = *_hp; free(_hp); }
        (void)_wcond3056;
        ;
        if (_wcond3056) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(body, DEREF(i));
        (void)stmt;
        I32 _t3061 = expr_get_tag(stmt);
        (void)_t3061;
        U32 _t3062 = expr_nchildren(stmt);
        (void)_t3062;
        U32 _t3063 = 2;
        (void)_t3063;
        Bool _t3064 = I32_eq(_t3061, DEREF(NODE_FCALL));
        (void)_t3064;
        ;
        Bool _t3065 = U32_eq(_t3062, _t3063);
        (void)_t3065;
        ;
        ;
        U32 *_t3066 = malloc(sizeof(U32));
        *_t3066 = 0;
        (void)_t3066;
        Expr *_t3067 = expr_get_child(stmt, DEREF(_t3066));
        (void)_t3067;
        I32 _t3068 = expr_get_tag(_t3067);
        (void)_t3068;
        U32_delete(_t3066, &(Bool){1});
        Bool _t3069 = Bool_and(_t3064, _t3065);
        (void)_t3069;
        ;
        ;
        Bool _t3070 = I32_eq(_t3068, DEREF(NODE_IDENT));
        (void)_t3070;
        ;
        U32 *_t3071 = malloc(sizeof(U32));
        *_t3071 = 0;
        (void)_t3071;
        Expr *_t3072 = expr_get_child(stmt, DEREF(_t3071));
        (void)_t3072;
        Str *_t3073 = expr_get_str_val(_t3072);
        (void)_t3073;
        Str *_t3074 = Str_lit("import", 6ULL);
        (void)_t3074;
        Bool _t3075 = Bool_and(_t3069, _t3070);
        (void)_t3075;
        ;
        ;
        Bool _t3076; { Bool *_hp = (Bool *)Str_eq(_t3073, _t3074); _t3076 = *_hp; free(_hp); }
        (void)_t3076;
        U32_delete(_t3071, &(Bool){1});
        Str_delete(_t3074, &(Bool){1});
        U32 *_t3077 = malloc(sizeof(U32));
        *_t3077 = 1;
        (void)_t3077;
        Expr *_t3078 = expr_get_child(stmt, DEREF(_t3077));
        (void)_t3078;
        I32 _t3079 = expr_get_tag(_t3078);
        (void)_t3079;
        U32_delete(_t3077, &(Bool){1});
        Bool _t3080 = Bool_and(_t3075, _t3076);
        (void)_t3080;
        ;
        ;
        Bool _t3081 = I32_eq(_t3079, DEREF(NODE_LITERAL_STR));
        (void)_t3081;
        ;
        Bool _t3082 = Bool_and(_t3080, _t3081);
        (void)_t3082;
        ;
        ;
        if (_t3082) {
            U32 *_t3057 = malloc(sizeof(U32));
            *_t3057 = 1;
            (void)_t3057;
            Expr *_t3058 = expr_get_child(stmt, DEREF(_t3057));
            (void)_t3058;
            Str *path = expr_get_str_val(_t3058);
            (void)path;
            Str *_t3059 = Str_clone(path);
            (void)_t3059;
            U32_delete(_t3057, &(Bool){1});
            Vec_push(paths, _t3059);
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t3083 = 1;
        (void)_t3083;
        U32 _t3084 = U32_add(DEREF(i), _t3083);
        (void)_t3084;
        ;
        *i = _t3084;
        ;
    }
    U32_delete(i, &(Bool){1});
    expr_swap_children(body, kept);
    Vec_delete(kept, &(Bool){1});
    return paths;
}

I32 * resolve_imports(Vec * import_paths, Str * base_dir, void * resolved_set, void * stack, void * merged, Str * lib_dir) {
    (void)import_paths;
    (void)base_dir;
    (void)resolved_set;
    (void)stack;
    (void)merged;
    (void)lib_dir;
    {
        U64 _fi3087 = 0;
        (void)_fi3087;
        while (1) {
            U64 _t3117 = 0;
            (void)_t3117;
            U64 _t3118; { U64 *_hp = (U64 *)Vec_len(import_paths); _t3118 = *_hp; free(_hp); }
            (void)_t3118;
            Range *_t3119 = Range_new(_t3117, _t3118);
            (void)_t3119;
            ;
            ;
            U64 _t3120; { U64 *_hp = (U64 *)Range_len(_t3119); _t3120 = *_hp; free(_hp); }
            (void)_t3120;
            Range_delete(_t3119, &(Bool){1});
            Bool _wcond3088; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3087}, &(U64){_t3120}); _wcond3088 = *_hp; free(_hp); }
            (void)_wcond3088;
            ;
            if (_wcond3088) {
            } else {
                ;
                break;
            }
            ;
            U64 _t3121 = 0;
            (void)_t3121;
            U64 _t3122; { U64 *_hp = (U64 *)Vec_len(import_paths); _t3122 = *_hp; free(_hp); }
            (void)_t3122;
            Range *_t3123 = Range_new(_t3121, _t3122);
            (void)_t3123;
            ;
            ;
            U64 *i = Range_get(_t3123, _fi3087);
            (void)i;
            Range_delete(_t3123, &(Bool){1});
            U64 _t3124 = 1;
            (void)_t3124;
            U64 _t3125 = U64_add(_fi3087, _t3124);
            (void)_t3125;
            ;
            _fi3087 = _t3125;
            ;
            Str *import_path = Vec_get(import_paths, i);
            (void)import_path;
            Str *_t3126 = Str_lit("/", 1ULL);
            (void)_t3126;
            Str *_t3127 = Str_concat(base_dir, _t3126);
            (void)_t3127;
            Str_delete(_t3126, &(Bool){1});
            Str *try_path = Str_concat(_t3127, import_path);
            (void)try_path;
            Str_delete(_t3127, &(Bool){1});
            Str *abs = til_realpath(try_path);
            (void)abs;
            Str *_t3128 = Str_lit("", 0ULL);
            (void)_t3128;
            U64 _t3129; { U64 *_hp = (U64 *)Str_len(lib_dir); _t3129 = *_hp; free(_hp); }
            (void)_t3129;
            U64 _t3130 = 0;
            (void)_t3130;
            Bool _t3131; { Bool *_hp = (Bool *)Str_eq(abs, _t3128); _t3131 = *_hp; free(_hp); }
            (void)_t3131;
            Str_delete(_t3128, &(Bool){1});
            Bool _t3132; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3129}, &(U64){_t3130}); _t3132 = *_hp; free(_hp); }
            (void)_t3132;
            ;
            ;
            Bool _t3133 = Bool_and(_t3131, _t3132);
            (void)_t3133;
            ;
            ;
            if (_t3133) {
                Str *_t3089 = Str_lit("/", 1ULL);
                (void)_t3089;
                Str *_t3090 = Str_concat(lib_dir, _t3089);
                (void)_t3090;
                Str_delete(_t3089, &(Bool){1});
                try_path = Str_concat(_t3090, import_path);
                Str_delete(_t3090, &(Bool){1});
                abs = til_realpath(try_path);
            }
            ;
            Str_delete(try_path, &(Bool){1});
            Str *_t3134 = Str_lit("", 0ULL);
            (void)_t3134;
            Bool _t3135; { Bool *_hp = (Bool *)Str_eq(abs, _t3134); _t3135 = *_hp; free(_hp); }
            (void)_t3135;
            Str_delete(_t3134, &(Bool){1});
            if (_t3135) {
                Str *_t3091 = Str_lit("Str", 3ULL);
                (void)_t3091;
                U64 _t3092; { U64 *_hp = (U64 *)Str_size(); _t3092 = *_hp; free(_hp); }
                (void)_t3092;
                U64 _t3093 = 1;
                (void)_t3093;
                Array *_va54 = Array_new(_t3091, &(U64){_t3092}, &(U64){_t3093});
                (void)_va54;
                Str_delete(_t3091, &(Bool){1});
                ;
                ;
                Str *_t3094 = Str_lit("error: could not find import '", 30ULL);
                (void)_t3094;
                Str *_t3095 = Str_concat(_t3094, import_path);
                (void)_t3095;
                Str_delete(_t3094, &(Bool){1});
                Str *_t3096 = Str_lit("' (from ", 8ULL);
                (void)_t3096;
                Str *_t3097 = Str_concat(_t3095, _t3096);
                (void)_t3097;
                Str_delete(_t3095, &(Bool){1});
                Str_delete(_t3096, &(Bool){1});
                Str *_t3098 = Str_concat(_t3097, base_dir);
                (void)_t3098;
                Str_delete(_t3097, &(Bool){1});
                Str *_t3099 = Str_lit("/)", 2ULL);
                (void)_t3099;
                U64 _t3100 = 0;
                (void)_t3100;
                Str *_t3101 = Str_concat(_t3098, _t3099);
                (void)_t3101;
                Str_delete(_t3098, &(Bool){1});
                Str_delete(_t3099, &(Bool){1});
                Array_set(_va54, &(U64){_t3100}, _t3101);
                ;
                println(_va54);
                I64 _t3102 = 1;
                (void)_t3102;
                ;
                Str_delete(abs, &(Bool){1});
                U64_delete(i, &(Bool){1});
                ;
                { I32 *_r = malloc(sizeof(I32)); *_r = _t3102; return _r; }
            }
            ;
            U64_delete(i, &(Bool){1});
            Bool _t3136 = til_set_has(resolved_set, abs);
            (void)_t3136;
            if (_t3136) {
                ;
                Str_delete(abs, &(Bool){1});
                continue;
            }
            ;
            til_set_add(resolved_set, abs);
            Str *source = readfile(abs);
            (void)source;
            Vec *tokens = tokenize(source, abs);
            (void)tokens;
            Str_delete(source, &(Bool){1});
            Expr *sub_ast = til_parse(tokens, abs);
            (void)sub_ast;
            Vec_delete(tokens, &(Bool){1});
            Str *sub_mode = til_parse_mode();
            (void)sub_mode;
            Str_delete(sub_mode, &(Bool){1});
            Vec *sub_imports = extract_imports(sub_ast);
            (void)sub_imports;
            U64 _t3137; { U64 *_hp = (U64 *)Str_len(abs); _t3137 = *_hp; free(_hp); }
            (void)_t3137;
            U64 _t3138 = 1;
            (void)_t3138;
            U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t3137, _t3138);
            (void)last_slash;
            ;
            ;
            while (1) {
                U64 _t3104 = 0;
                (void)_t3104;
                U8 *_t3105 = Str_get(abs, last_slash);
                (void)_t3105;
                U8 _t3106 = 47;
                (void)_t3106;
                Bool _t3107; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t3104}); _t3107 = *_hp; free(_hp); }
                (void)_t3107;
                ;
                Bool _t3108; { Bool *_hp = (Bool *)U8_neq(_t3105, &(U8){_t3106}); _t3108 = *_hp; free(_hp); }
                (void)_t3108;
                ;
                Bool _wcond3103 = Bool_and(_t3107, _t3108);
                (void)_wcond3103;
                ;
                ;
                if (_wcond3103) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t3109 = 1;
                (void)_t3109;
                U64 _t3110 = U64_sub(DEREF(last_slash), _t3109);
                (void)_t3110;
                ;
                *last_slash = _t3110;
                ;
            }
            Str *sub_dir = til_str_left(abs, DEREF(last_slash));
            (void)sub_dir;
            Str_delete(abs, &(Bool){1});
            U64_delete(last_slash, &(Bool){1});
            U64 _t3139; { U64 *_hp = (U64 *)Vec_len(sub_imports); _t3139 = *_hp; free(_hp); }
            (void)_t3139;
            U64 _t3140 = 0;
            (void)_t3140;
            Bool _t3141; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3139}, &(U64){_t3140}); _t3141 = *_hp; free(_hp); }
            (void)_t3141;
            ;
            ;
            if (_t3141) {
                I32 err; { I32 *_hp = (I32 *)resolve_imports(sub_imports, sub_dir, resolved_set, stack, merged, lib_dir); err = *_hp; free(_hp); }
                (void)err;
                I32 _t3111 = 0;
                (void)_t3111;
                Bool _t3112; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t3111}); _t3112 = *_hp; free(_hp); }
                (void)_t3112;
                ;
                if (_t3112) {
                    ;
                    ;
                    Expr_delete(sub_ast, &(Bool){1});
                    Str_delete(sub_dir, &(Bool){1});
                    Vec_delete(sub_imports, &(Bool){1});
                    Str_delete(sub_mode, &(Bool){1});
                    ;
                    { I32 *_r = malloc(sizeof(I32)); *_r = err; return _r; }
                }
                ;
                ;
            }
            ;
            Str_delete(sub_dir, &(Bool){1});
            Vec_delete(sub_imports, &(Bool){1});
            U32 *k = malloc(sizeof(U32));
            *k = 0;
            (void)k;
            while (1) {
                U32 _t3114 = expr_nchildren(sub_ast);
                (void)_t3114;
                Bool _wcond3113; { Bool *_hp = (Bool *)U32_lt(k, &(U32){_t3114}); _wcond3113 = *_hp; free(_hp); }
                (void)_wcond3113;
                ;
                if (_wcond3113) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *ch = expr_get_child(sub_ast, DEREF(k));
                (void)ch;
                expr_vec_push(merged, ch);
                U32 _t3115 = 1;
                (void)_t3115;
                U32 _t3116 = U32_add(DEREF(k), _t3115);
                (void)_t3116;
                ;
                *k = _t3116;
                ;
            }
            U32_delete(k, &(Bool){1});
            Expr_delete(sub_ast, &(Bool){1});
        }
        ;
    }
    I64 _t3142 = 0;
    (void)_t3142;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t3142; return _r; }
}

void usage(void) {
    Str *_t3143 = Str_lit("Str", 3ULL);
    (void)_t3143;
    U64 _t3144; { U64 *_hp = (U64 *)Str_size(); _t3144 = *_hp; free(_hp); }
    (void)_t3144;
    U64 _t3145 = 1;
    (void)_t3145;
    Array *_va55 = Array_new(_t3143, &(U64){_t3144}, &(U64){_t3145});
    (void)_va55;
    Str_delete(_t3143, &(Bool){1});
    ;
    ;
    U64 _t3146 = 0;
    (void)_t3146;
    Str *_t3147 = Str_lit("Usage: til <command> <path>", 27ULL);
    (void)_t3147;
    Array_set(_va55, &(U64){_t3146}, _t3147);
    ;
    println(_va55);
    Str *_t3148 = Str_lit("Str", 3ULL);
    (void)_t3148;
    U64 _t3149; { U64 *_hp = (U64 *)Str_size(); _t3149 = *_hp; free(_hp); }
    (void)_t3149;
    U64 _t3150 = 1;
    (void)_t3150;
    Array *_va56 = Array_new(_t3148, &(U64){_t3149}, &(U64){_t3150});
    (void)_va56;
    Str_delete(_t3148, &(Bool){1});
    ;
    ;
    U64 _t3151 = 0;
    (void)_t3151;
    Str *_t3152 = Str_lit("", 0ULL);
    (void)_t3152;
    Array_set(_va56, &(U64){_t3151}, _t3152);
    ;
    println(_va56);
    Str *_t3153 = Str_lit("Str", 3ULL);
    (void)_t3153;
    U64 _t3154; { U64 *_hp = (U64 *)Str_size(); _t3154 = *_hp; free(_hp); }
    (void)_t3154;
    U64 _t3155 = 1;
    (void)_t3155;
    Array *_va57 = Array_new(_t3153, &(U64){_t3154}, &(U64){_t3155});
    (void)_va57;
    Str_delete(_t3153, &(Bool){1});
    ;
    ;
    U64 _t3156 = 0;
    (void)_t3156;
    Str *_t3157 = Str_lit("Commands:", 9ULL);
    (void)_t3157;
    Array_set(_va57, &(U64){_t3156}, _t3157);
    ;
    println(_va57);
    Str *_t3158 = Str_lit("Str", 3ULL);
    (void)_t3158;
    U64 _t3159; { U64 *_hp = (U64 *)Str_size(); _t3159 = *_hp; free(_hp); }
    (void)_t3159;
    U64 _t3160 = 1;
    (void)_t3160;
    Array *_va58 = Array_new(_t3158, &(U64){_t3159}, &(U64){_t3160});
    (void)_va58;
    Str_delete(_t3158, &(Bool){1});
    ;
    ;
    U64 _t3161 = 0;
    (void)_t3161;
    Str *_t3162 = Str_lit("  interpret  Read and interpret a .til file", 43ULL);
    (void)_t3162;
    Array_set(_va58, &(U64){_t3161}, _t3162);
    ;
    println(_va58);
    Str *_t3163 = Str_lit("Str", 3ULL);
    (void)_t3163;
    U64 _t3164; { U64 *_hp = (U64 *)Str_size(); _t3164 = *_hp; free(_hp); }
    (void)_t3164;
    U64 _t3165 = 1;
    (void)_t3165;
    Array *_va59 = Array_new(_t3163, &(U64){_t3164}, &(U64){_t3165});
    (void)_va59;
    Str_delete(_t3163, &(Bool){1});
    ;
    ;
    U64 _t3166 = 0;
    (void)_t3166;
    Str *_t3167 = Str_lit("  translate  Generate C source (no compilation)", 47ULL);
    (void)_t3167;
    Array_set(_va59, &(U64){_t3166}, _t3167);
    ;
    println(_va59);
    Str *_t3168 = Str_lit("Str", 3ULL);
    (void)_t3168;
    U64 _t3169; { U64 *_hp = (U64 *)Str_size(); _t3169 = *_hp; free(_hp); }
    (void)_t3169;
    U64 _t3170 = 1;
    (void)_t3170;
    Array *_va60 = Array_new(_t3168, &(U64){_t3169}, &(U64){_t3170});
    (void)_va60;
    Str_delete(_t3168, &(Bool){1});
    ;
    ;
    U64 _t3171 = 0;
    (void)_t3171;
    Str *_t3172 = Str_lit("  build      Compile a .til file to a binary", 44ULL);
    (void)_t3172;
    Array_set(_va60, &(U64){_t3171}, _t3172);
    ;
    println(_va60);
    Str *_t3173 = Str_lit("Str", 3ULL);
    (void)_t3173;
    U64 _t3174; { U64 *_hp = (U64 *)Str_size(); _t3174 = *_hp; free(_hp); }
    (void)_t3174;
    U64 _t3175 = 1;
    (void)_t3175;
    Array *_va61 = Array_new(_t3173, &(U64){_t3174}, &(U64){_t3175});
    (void)_va61;
    Str_delete(_t3173, &(Bool){1});
    ;
    ;
    U64 _t3176 = 0;
    (void)_t3176;
    Str *_t3177 = Str_lit("  run        Compile and run a .til file", 40ULL);
    (void)_t3177;
    Array_set(_va61, &(U64){_t3176}, _t3177);
    ;
    println(_va61);
    Str *_t3178 = Str_lit("Str", 3ULL);
    (void)_t3178;
    U64 _t3179; { U64 *_hp = (U64 *)Str_size(); _t3179 = *_hp; free(_hp); }
    (void)_t3179;
    U64 _t3180 = 1;
    (void)_t3180;
    Array *_va62 = Array_new(_t3178, &(U64){_t3179}, &(U64){_t3180});
    (void)_va62;
    Str_delete(_t3178, &(Bool){1});
    ;
    ;
    U64 _t3181 = 0;
    (void)_t3181;
    Str *_t3182 = Str_lit("  test       Run test functions in a .til file", 46ULL);
    (void)_t3182;
    Array_set(_va62, &(U64){_t3181}, _t3182);
    ;
    println(_va62);
    Str *_t3183 = Str_lit("Str", 3ULL);
    (void)_t3183;
    U64 _t3184; { U64 *_hp = (U64 *)Str_size(); _t3184 = *_hp; free(_hp); }
    (void)_t3184;
    U64 _t3185 = 1;
    (void)_t3185;
    Array *_va63 = Array_new(_t3183, &(U64){_t3184}, &(U64){_t3185});
    (void)_va63;
    Str_delete(_t3183, &(Bool){1});
    ;
    ;
    U64 _t3186 = 0;
    (void)_t3186;
    Str *_t3187 = Str_lit("  help       Print this message", 31ULL);
    (void)_t3187;
    Array_set(_va63, &(U64){_t3186}, _t3187);
    ;
    println(_va63);
}

void mark_core(Expr * e) {
    (void)e;
    Bool _t3193 = 1;
    (void)_t3193;
    e->is_core = _t3193;
    ;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t3189 = expr_nchildren(e);
        (void)_t3189;
        Bool _wcond3188; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3189}); _wcond3188 = *_hp; free(_hp); }
        (void)_wcond3188;
        ;
        if (_wcond3188) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t3190 = expr_get_child(e, DEREF(i));
        (void)_t3190;
        mark_core(_t3190);
        U32 _t3191 = 1;
        (void)_t3191;
        U32 _t3192 = U32_add(DEREF(i), _t3191);
        (void)_t3192;
        ;
        *i = _t3192;
        ;
    }
    U32_delete(i, &(Bool){1});
}

int main(int argc, char **argv) {
    if (argc - 1 < 0) { fprintf(stderr, "error: main expects at least 0 argument(s), got %d\n", argc - 1); return 1; }
    _t3649 = malloc(sizeof(I64));
    *_t3649 = 0;
    (void)_t3649;
    _t3650 = malloc(sizeof(I64));
    *_t3650 = 1;
    (void)_t3650;
    _t3651 = malloc(sizeof(I64)); *_t3651 = I64_sub(DEREF(_t3649), DEREF(_t3650));
    (void)_t3651;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t3651));
    (void)CAP_LIT;
    _t3652 = malloc(sizeof(I64));
    *_t3652 = 0;
    (void)_t3652;
    _t3653 = malloc(sizeof(I64));
    *_t3653 = 2;
    (void)_t3653;
    _t3654 = malloc(sizeof(I64)); *_t3654 = I64_sub(DEREF(_t3652), DEREF(_t3653));
    (void)_t3654;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t3654));
    (void)CAP_VIEW;
    NODE_BODY = malloc(sizeof(I32));
    *NODE_BODY = 0;
    (void)NODE_BODY;
    NODE_LITERAL_STR = malloc(sizeof(I32));
    *NODE_LITERAL_STR = 1;
    (void)NODE_LITERAL_STR;
    NODE_LITERAL_NUM = malloc(sizeof(I32));
    *NODE_LITERAL_NUM = 2;
    (void)NODE_LITERAL_NUM;
    NODE_LITERAL_BOOL = malloc(sizeof(I32));
    *NODE_LITERAL_BOOL = 3;
    (void)NODE_LITERAL_BOOL;
    NODE_LITERAL_NULL = malloc(sizeof(I32));
    *NODE_LITERAL_NULL = 4;
    (void)NODE_LITERAL_NULL;
    NODE_IDENT = malloc(sizeof(I32));
    *NODE_IDENT = 5;
    (void)NODE_IDENT;
    NODE_DECL = malloc(sizeof(I32));
    *NODE_DECL = 6;
    (void)NODE_DECL;
    NODE_ASSIGN = malloc(sizeof(I32));
    *NODE_ASSIGN = 7;
    (void)NODE_ASSIGN;
    NODE_FCALL = malloc(sizeof(I32));
    *NODE_FCALL = 8;
    (void)NODE_FCALL;
    NODE_FUNC_DEF = malloc(sizeof(I32));
    *NODE_FUNC_DEF = 9;
    (void)NODE_FUNC_DEF;
    NODE_STRUCT_DEF = malloc(sizeof(I32));
    *NODE_STRUCT_DEF = 10;
    (void)NODE_STRUCT_DEF;
    NODE_ENUM_DEF = malloc(sizeof(I32));
    *NODE_ENUM_DEF = 11;
    (void)NODE_ENUM_DEF;
    NODE_FIELD_ACCESS = malloc(sizeof(I32));
    *NODE_FIELD_ACCESS = 12;
    (void)NODE_FIELD_ACCESS;
    NODE_FIELD_ASSIGN = malloc(sizeof(I32));
    *NODE_FIELD_ASSIGN = 13;
    (void)NODE_FIELD_ASSIGN;
    NODE_RETURN = malloc(sizeof(I32));
    *NODE_RETURN = 14;
    (void)NODE_RETURN;
    NODE_IF = malloc(sizeof(I32));
    *NODE_IF = 15;
    (void)NODE_IF;
    NODE_WHILE = malloc(sizeof(I32));
    *NODE_WHILE = 16;
    (void)NODE_WHILE;
    NODE_FOR_IN = malloc(sizeof(I32));
    *NODE_FOR_IN = 17;
    (void)NODE_FOR_IN;
    NODE_NAMED_ARG = malloc(sizeof(I32));
    *NODE_NAMED_ARG = 18;
    (void)NODE_NAMED_ARG;
    NODE_BREAK = malloc(sizeof(I32));
    *NODE_BREAK = 19;
    (void)NODE_BREAK;
    NODE_CONTINUE = malloc(sizeof(I32));
    *NODE_CONTINUE = 20;
    (void)NODE_CONTINUE;
    NODE_MAP_LIT = malloc(sizeof(I32));
    *NODE_MAP_LIT = 21;
    (void)NODE_MAP_LIT;
    NODE_SET_LIT = malloc(sizeof(I32));
    *NODE_SET_LIT = 22;
    (void)NODE_SET_LIT;
    NODE_SWITCH = malloc(sizeof(I32));
    *NODE_SWITCH = 23;
    (void)NODE_SWITCH;
    NODE_CASE = malloc(sizeof(I32));
    *NODE_CASE = 24;
    (void)NODE_CASE;
    int _va_argc = argc - 1;
    U64 _va_esz = sizeof(Str);
    U64 _va_cap = _va_argc;
    Array *args = Array_new(&(Str){.c_str = (U8 *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}, &(U64){_va_esz}, &(U64){_va_cap});
    for (int _i = 0; _i < _va_argc; _i++) {
        U64 _idx = _i;
        Str *_val = Str_clone(&(Str){.c_str = (U8 *)argv[1 + _i], .count = strlen(argv[1 + _i]), .cap = TIL_CAP_LIT});
        Array_set(args, &(U64){_idx}, _val);
    }
    U64 _t3571; { U64 *_hp = (U64 *)Array_len(args); _t3571 = *_hp; free(_hp); }
    (void)_t3571;
    U64 _t3572 = 0;
    (void)_t3572;
    Bool _t3573 = U64_eq(_t3571, _t3572);
    (void)_t3573;
    ;
    ;
    if (_t3573) {
        usage();
        Str *_t3194 = Str_lit("Str", 3ULL);
        (void)_t3194;
        U64 _t3195; { U64 *_hp = (U64 *)Str_size(); _t3195 = *_hp; free(_hp); }
        (void)_t3195;
        U64 _t3196 = 1;
        (void)_t3196;
        Array *_va64 = Array_new(_t3194, &(U64){_t3195}, &(U64){_t3196});
        (void)_va64;
        Str_delete(_t3194, &(Bool){1});
        ;
        ;
        U64 _t3197 = 0;
        (void)_t3197;
        Str *_t3198 = Str_lit("no arguments", 12ULL);
        (void)_t3198;
        Array_set(_va64, &(U64){_t3197}, _t3198);
        ;
        Str *_t3199 = Str_lit("src/til.til:221:15", 18ULL);
        (void)_t3199;
        panic(_t3199, _va64);
        Str_delete(_t3199, &(Bool){1});
    }
    ;
    U64 *_t3574 = malloc(sizeof(U64));
    *_t3574 = 0;
    (void)_t3574;
    Str *cmd_ref = Array_get(args, _t3574);
    (void)cmd_ref;
    Str *command = Str_clone(cmd_ref);
    (void)command;
    U64_delete(_t3574, &(Bool){1});
    Str *path = Str_lit("", 0ULL);
    (void)path;
    Str *custom_bin = Str_lit("", 0ULL);
    (void)custom_bin;
    Str *custom_c = Str_lit("", 0ULL);
    (void)custom_c;
    U64 *path_idx = malloc(sizeof(U64));
    *path_idx = 1;
    (void)path_idx;
    U64 _t3575; { U64 *_hp = (U64 *)Array_len(args); _t3575 = *_hp; free(_hp); }
    (void)_t3575;
    U64 _t3576 = 1;
    (void)_t3576;
    Bool _t3577 = U64_eq(_t3575, _t3576);
    (void)_t3577;
    ;
    ;
    if (_t3577) {
        Str *_t3200 = Str_lit("help", 4ULL);
        (void)_t3200;
        Str *_t3201 = Str_lit("--help", 6ULL);
        (void)_t3201;
        Bool _t3202; { Bool *_hp = (Bool *)Str_eq(command, _t3200); _t3202 = *_hp; free(_hp); }
        (void)_t3202;
        Str_delete(_t3200, &(Bool){1});
        Bool _t3203; { Bool *_hp = (Bool *)Str_eq(command, _t3201); _t3203 = *_hp; free(_hp); }
        (void)_t3203;
        Str_delete(_t3201, &(Bool){1});
        Bool _t3204 = Bool_or(_t3202, _t3203);
        (void)_t3204;
        ;
        ;
        if (_t3204) {
            usage();
            ;
            ;
            Array_delete(args, &(Bool){1});
            Str_delete(command, &(Bool){1});
            Str_delete(custom_bin, &(Bool){1});
            Str_delete(custom_c, &(Bool){1});
            Str_delete(path, &(Bool){1});
            U64_delete(path_idx, &(Bool){1});
            return 0;
        }
        ;
        path = Str_clone(command);
        command = Str_lit("interpret", 9ULL);
    } else {
        while (1) {
            U64 _t3221; { U64 *_hp = (U64 *)Array_len(args); _t3221 = *_hp; free(_hp); }
            (void)_t3221;
            Bool _wcond3205; { Bool *_hp = (Bool *)U64_lt(path_idx, &(U64){_t3221}); _wcond3205 = *_hp; free(_hp); }
            (void)_wcond3205;
            ;
            if (_wcond3205) {
            } else {
                ;
                break;
            }
            ;
            Str *flag = Array_get(args, path_idx);
            (void)flag;
            Str *_t3222 = Str_lit("-o", 2ULL);
            (void)_t3222;
            U64 _t3223 = 1;
            (void)_t3223;
            U64 _t3224 = U64_add(DEREF(path_idx), _t3223);
            (void)_t3224;
            ;
            U64 _t3225; { U64 *_hp = (U64 *)Array_len(args); _t3225 = *_hp; free(_hp); }
            (void)_t3225;
            Bool _t3226; { Bool *_hp = (Bool *)Str_eq(flag, _t3222); _t3226 = *_hp; free(_hp); }
            (void)_t3226;
            Str_delete(_t3222, &(Bool){1});
            Bool _t3227; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3224}, &(U64){_t3225}); _t3227 = *_hp; free(_hp); }
            (void)_t3227;
            ;
            ;
            Bool _t3228 = Bool_and(_t3226, _t3227);
            (void)_t3228;
            ;
            ;
            if (_t3228) {
                U64 _t3206 = 1;
                (void)_t3206;
                U64 *_t3207 = malloc(sizeof(U64)); *_t3207 = U64_add(DEREF(path_idx), _t3206);
                (void)_t3207;
                ;
                Str *oval = Array_get(args, _t3207);
                (void)oval;
                custom_bin = Str_clone(oval);
                U64_delete(_t3207, &(Bool){1});
                U64 _t3208 = 2;
                (void)_t3208;
                U64 _t3209 = U64_add(DEREF(path_idx), _t3208);
                (void)_t3209;
                ;
                *path_idx = _t3209;
                ;
            } else {
                Str *_t3214 = Str_lit("-c", 2ULL);
                (void)_t3214;
                U64 _t3215 = 1;
                (void)_t3215;
                U64 _t3216 = U64_add(DEREF(path_idx), _t3215);
                (void)_t3216;
                ;
                U64 _t3217; { U64 *_hp = (U64 *)Array_len(args); _t3217 = *_hp; free(_hp); }
                (void)_t3217;
                Bool _t3218; { Bool *_hp = (Bool *)Str_eq(flag, _t3214); _t3218 = *_hp; free(_hp); }
                (void)_t3218;
                Str_delete(_t3214, &(Bool){1});
                Bool _t3219; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3216}, &(U64){_t3217}); _t3219 = *_hp; free(_hp); }
                (void)_t3219;
                ;
                ;
                Bool _t3220 = Bool_and(_t3218, _t3219);
                (void)_t3220;
                ;
                ;
                if (_t3220) {
                    U64 _t3210 = 1;
                    (void)_t3210;
                    U64 *_t3211 = malloc(sizeof(U64)); *_t3211 = U64_add(DEREF(path_idx), _t3210);
                    (void)_t3211;
                    ;
                    Str *cval = Array_get(args, _t3211);
                    (void)cval;
                    custom_c = Str_clone(cval);
                    U64_delete(_t3211, &(Bool){1});
                    U64 _t3212 = 2;
                    (void)_t3212;
                    U64 _t3213 = U64_add(DEREF(path_idx), _t3212);
                    (void)_t3213;
                    ;
                    *path_idx = _t3213;
                    ;
                } else {
                    ;
                    ;
                    break;
                }
                ;
            }
            ;
        }
        Str *p = Array_get(args, path_idx);
        (void)p;
        path = Str_clone(p);
    }
    ;
    Str *_t3578 = Str_lit("help", 4ULL);
    (void)_t3578;
    Str *_t3579 = Str_lit("--help", 6ULL);
    (void)_t3579;
    Bool _t3580; { Bool *_hp = (Bool *)Str_eq(command, _t3578); _t3580 = *_hp; free(_hp); }
    (void)_t3580;
    Str_delete(_t3578, &(Bool){1});
    Bool _t3581; { Bool *_hp = (Bool *)Str_eq(command, _t3579); _t3581 = *_hp; free(_hp); }
    (void)_t3581;
    Str_delete(_t3579, &(Bool){1});
    Bool _t3582 = Bool_or(_t3580, _t3581);
    (void)_t3582;
    ;
    ;
    if (_t3582) {
        usage();
        ;
        Array_delete(args, &(Bool){1});
        Str_delete(command, &(Bool){1});
        Str_delete(custom_bin, &(Bool){1});
        Str_delete(custom_c, &(Bool){1});
        Str_delete(path, &(Bool){1});
        U64_delete(path_idx, &(Bool){1});
        return 0;
    }
    ;
    Str *bin_dir = til_bin_dir();
    (void)bin_dir;
    Str *_t3583 = Str_lit("/src/core/core.til", 18ULL);
    (void)_t3583;
    Str *core_path = Str_concat(bin_dir, _t3583);
    (void)core_path;
    Str_delete(_t3583, &(Bool){1});
    Str *_t3584 = Str_lit("/src/c/ext.c", 12ULL);
    (void)_t3584;
    Str *ext_c_path = Str_concat(bin_dir, _t3584);
    (void)ext_c_path;
    Str_delete(_t3584, &(Bool){1});
    Set *resolved = til_set_new();
    (void)resolved;
    Vec *resolve_stack = expr_vec_new();
    (void)resolve_stack;
    Str *abs_path = til_realpath(path);
    (void)abs_path;
    Str *user_dir = Str_lit(".", 1ULL);
    (void)user_dir;
    U64 _t3585; { U64 *_hp = (U64 *)Str_len(abs_path); _t3585 = *_hp; free(_hp); }
    (void)_t3585;
    U64 _t3586 = 0;
    (void)_t3586;
    Bool _t3587; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3585}, &(U64){_t3586}); _t3587 = *_hp; free(_hp); }
    (void)_t3587;
    ;
    ;
    if (_t3587) {
        U64 _t3237; { U64 *_hp = (U64 *)Str_len(abs_path); _t3237 = *_hp; free(_hp); }
        (void)_t3237;
        U64 _t3238 = 1;
        (void)_t3238;
        U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t3237, _t3238);
        (void)last_slash;
        ;
        ;
        while (1) {
            U64 _t3230 = 0;
            (void)_t3230;
            U8 *_t3231 = Str_get(abs_path, last_slash);
            (void)_t3231;
            U8 _t3232 = 47;
            (void)_t3232;
            Bool _t3233; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t3230}); _t3233 = *_hp; free(_hp); }
            (void)_t3233;
            ;
            Bool _t3234; { Bool *_hp = (Bool *)U8_neq(_t3231, &(U8){_t3232}); _t3234 = *_hp; free(_hp); }
            (void)_t3234;
            ;
            Bool _wcond3229 = Bool_and(_t3233, _t3234);
            (void)_wcond3229;
            ;
            ;
            if (_wcond3229) {
            } else {
                ;
                break;
            }
            ;
            U64 _t3235 = 1;
            (void)_t3235;
            U64 _t3236 = U64_sub(DEREF(last_slash), _t3235);
            (void)_t3236;
            ;
            *last_slash = _t3236;
            ;
        }
        user_dir = til_str_left(abs_path, DEREF(last_slash));
        U64_delete(last_slash, &(Bool){1});
        til_set_add(resolved, abs_path);
    }
    ;
    Str_delete(abs_path, &(Bool){1});
    Str *core_source = readfile(core_path);
    (void)core_source;
    Vec *core_tokens = tokenize(core_source, core_path);
    (void)core_tokens;
    Str_delete(core_source, &(Bool){1});
    Expr *core_ast = til_parse(core_tokens, core_path);
    (void)core_ast;
    Vec_delete(core_tokens, &(Bool){1});
    Bool skip_core = 0;
    (void)skip_core;
    Str *core_abs = til_realpath(core_path);
    (void)core_abs;
    Str_delete(core_path, &(Bool){1});
    U64 _t3588; { U64 *_hp = (U64 *)Str_len(core_abs); _t3588 = *_hp; free(_hp); }
    (void)_t3588;
    U64 _t3589 = 0;
    (void)_t3589;
    Bool _t3590; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3588}, &(U64){_t3589}); _t3590 = *_hp; free(_hp); }
    (void)_t3590;
    ;
    ;
    if (_t3590) {
        Bool _t3240 = til_set_has(resolved, core_abs);
        (void)_t3240;
        if (_t3240) {
            Bool _t3239 = 1;
            (void)_t3239;
            skip_core = _t3239;
            ;
        }
        ;
        til_set_add(resolved, core_abs);
    }
    ;
    Str_delete(core_abs, &(Bool){1});
    Vec *core_import_decls = expr_vec_new();
    (void)core_import_decls;
    Vec *core_imports = extract_imports(core_ast);
    (void)core_imports;
    U64 _t3591; { U64 *_hp = (U64 *)Vec_len(core_imports); _t3591 = *_hp; free(_hp); }
    (void)_t3591;
    U64 _t3592 = 0;
    (void)_t3592;
    Bool _t3593; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3591}, &(U64){_t3592}); _t3593 = *_hp; free(_hp); }
    (void)_t3593;
    ;
    ;
    Bool _t3594 = Bool_not(skip_core);
    (void)_t3594;
    Bool _t3595 = Bool_and(_t3593, _t3594);
    (void)_t3595;
    ;
    ;
    if (_t3595) {
        Str *_t3247 = Str_lit("/src/core", 9ULL);
        (void)_t3247;
        Str *core_dir = Str_concat(bin_dir, _t3247);
        (void)core_dir;
        Str_delete(_t3247, &(Bool){1});
        Str *_t3248 = Str_lit("", 0ULL);
        (void)_t3248;
        I32 err; { I32 *_hp = (I32 *)resolve_imports(core_imports, core_dir, resolved, resolve_stack, core_import_decls, _t3248); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(_t3248, &(Bool){1});
        Str_delete(core_dir, &(Bool){1});
        I32 _t3249 = 0;
        (void)_t3249;
        Bool _t3250; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t3249}); _t3250 = *_hp; free(_hp); }
        (void)_t3250;
        ;
        ;
        if (_t3250) {
            Str *_t3241 = Str_lit("Str", 3ULL);
            (void)_t3241;
            U64 _t3242; { U64 *_hp = (U64 *)Str_size(); _t3242 = *_hp; free(_hp); }
            (void)_t3242;
            U64 _t3243 = 1;
            (void)_t3243;
            Array *_va65 = Array_new(_t3241, &(U64){_t3242}, &(U64){_t3243});
            (void)_va65;
            Str_delete(_t3241, &(Bool){1});
            ;
            ;
            U64 _t3244 = 0;
            (void)_t3244;
            Str *_t3245 = Str_lit("failed to resolve core imports", 30ULL);
            (void)_t3245;
            Array_set(_va65, &(U64){_t3244}, _t3245);
            ;
            Str *_t3246 = Str_lit("src/til.til:307:19", 18ULL);
            (void)_t3246;
            panic(_t3246, _va65);
            Str_delete(_t3246, &(Bool){1});
        }
        ;
    }
    ;
    Vec_delete(core_imports, &(Bool){1});
    Str *source = readfile(path);
    (void)source;
    Vec *tokens = tokenize(source, path);
    (void)tokens;
    Str_delete(source, &(Bool){1});
    Expr *ast = til_parse(tokens, path);
    (void)ast;
    Vec_delete(tokens, &(Bool){1});
    Vec *imports = extract_imports(ast);
    (void)imports;
    Str *mode_str = til_parse_mode();
    (void)mode_str;
    Str *_t3596 = Str_lit("script", 6ULL);
    (void)_t3596;
    Mode *cur_mode = mode_resolve(_t3596);
    (void)cur_mode;
    Str_delete(_t3596, &(Bool){1});
    U64 _t3597; { U64 *_hp = (U64 *)Str_len(mode_str); _t3597 = *_hp; free(_hp); }
    (void)_t3597;
    U64 _t3598 = 0;
    (void)_t3598;
    Bool _t3599; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3597}, &(U64){_t3598}); _t3599 = *_hp; free(_hp); }
    (void)_t3599;
    ;
    ;
    if (_t3599) {
        cur_mode = mode_resolve(mode_str);
        U64 _t3260; { U64 *_hp = (U64 *)Str_len(&cur_mode->name); _t3260 = *_hp; free(_hp); }
        (void)_t3260;
        U64 _t3261 = 0;
        (void)_t3261;
        Bool _t3262 = U64_eq(_t3260, _t3261);
        (void)_t3262;
        ;
        ;
        if (_t3262) {
            Str *_t3251 = Str_lit("Str", 3ULL);
            (void)_t3251;
            U64 _t3252; { U64 *_hp = (U64 *)Str_size(); _t3252 = *_hp; free(_hp); }
            (void)_t3252;
            U64 _t3253 = 1;
            (void)_t3253;
            Array *_va66 = Array_new(_t3251, &(U64){_t3252}, &(U64){_t3253});
            (void)_va66;
            Str_delete(_t3251, &(Bool){1});
            ;
            ;
            Str *_t3254 = Str_lit("unknown mode '", 14ULL);
            (void)_t3254;
            Str *_t3255 = Str_concat(_t3254, mode_str);
            (void)_t3255;
            Str_delete(_t3254, &(Bool){1});
            Str *_t3256 = Str_lit("'", 1ULL);
            (void)_t3256;
            U64 _t3257 = 0;
            (void)_t3257;
            Str *_t3258 = Str_concat(_t3255, _t3256);
            (void)_t3258;
            Str_delete(_t3255, &(Bool){1});
            Str_delete(_t3256, &(Bool){1});
            Array_set(_va66, &(U64){_t3257}, _t3258);
            ;
            Str *_t3259 = Str_lit("src/til.til:323:19", 18ULL);
            (void)_t3259;
            panic(_t3259, _va66);
            Str_delete(_t3259, &(Bool){1});
        }
        ;
    }
    ;
    Str_delete(mode_str, &(Bool){1});
    Str *auto_import = Str_clone(&cur_mode->auto_import);
    (void)auto_import;
    Vec *import_decls = expr_vec_new();
    (void)import_decls;
    U64 _t3600; { U64 *_hp = (U64 *)Vec_len(imports); _t3600 = *_hp; free(_hp); }
    (void)_t3600;
    U64 _t3601 = 0;
    (void)_t3601;
    Bool _t3602; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3600}, &(U64){_t3601}); _t3602 = *_hp; free(_hp); }
    (void)_t3602;
    ;
    ;
    if (_t3602) {
        Str *_t3269 = Str_lit("/src/lib", 8ULL);
        (void)_t3269;
        Str *lib_dir = Str_concat(bin_dir, _t3269);
        (void)lib_dir;
        Str_delete(_t3269, &(Bool){1});
        I32 err; { I32 *_hp = (I32 *)resolve_imports(imports, user_dir, resolved, resolve_stack, import_decls, lib_dir); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(lib_dir, &(Bool){1});
        I32 _t3270 = 0;
        (void)_t3270;
        Bool _t3271; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t3270}); _t3271 = *_hp; free(_hp); }
        (void)_t3271;
        ;
        ;
        if (_t3271) {
            Str *_t3263 = Str_lit("Str", 3ULL);
            (void)_t3263;
            U64 _t3264; { U64 *_hp = (U64 *)Str_size(); _t3264 = *_hp; free(_hp); }
            (void)_t3264;
            U64 _t3265 = 1;
            (void)_t3265;
            Array *_va67 = Array_new(_t3263, &(U64){_t3264}, &(U64){_t3265});
            (void)_va67;
            Str_delete(_t3263, &(Bool){1});
            ;
            ;
            U64 _t3266 = 0;
            (void)_t3266;
            Str *_t3267 = Str_lit("failed to resolve imports", 25ULL);
            (void)_t3267;
            Array_set(_va67, &(U64){_t3266}, _t3267);
            ;
            Str *_t3268 = Str_lit("src/til.til:337:19", 18ULL);
            (void)_t3268;
            panic(_t3268, _va67);
            Str_delete(_t3268, &(Bool){1});
        }
        ;
    }
    ;
    Vec_delete(imports, &(Bool){1});
    Vec_delete(resolve_stack, &(Bool){1});
    Set_delete(resolved, &(Bool){1});
    Str_delete(user_dir, &(Bool){1});
    Vec *merged = expr_vec_new();
    (void)merged;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    Bool _t3603 = Bool_not(skip_core);
    (void)_t3603;
    ;
    if (_t3603) {
        while (1) {
            U32 _t3273 = expr_nchildren(core_ast);
            (void)_t3273;
            Bool _wcond3272; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3273}); _wcond3272 = *_hp; free(_hp); }
            (void)_wcond3272;
            ;
            if (_wcond3272) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(core_ast, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t3274 = 1;
            (void)_t3274;
            U32 _t3275 = U32_add(DEREF(i), _t3274);
            (void)_t3275;
            ;
            *i = _t3275;
            ;
        }
        U32 _t3280 = 0;
        (void)_t3280;
        *i = _t3280;
        ;
        while (1) {
            U32 _t3277 = expr_vec_count(core_import_decls);
            (void)_t3277;
            Bool _wcond3276; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3277}); _wcond3276 = *_hp; free(_hp); }
            (void)_wcond3276;
            ;
            if (_wcond3276) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_vec_get(core_import_decls, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t3278 = 1;
            (void)_t3278;
            U32 _t3279 = U32_add(DEREF(i), _t3278);
            (void)_t3279;
            ;
            *i = _t3279;
            ;
        }
    }
    ;
    Expr_delete(core_ast, &(Bool){1});
    Vec_delete(core_import_decls, &(Bool){1});
    U64 _t3604; { U64 *_hp = (U64 *)Str_len(auto_import); _t3604 = *_hp; free(_hp); }
    (void)_t3604;
    U64 _t3605 = 0;
    (void)_t3605;
    Bool _t3606; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3604}, &(U64){_t3605}); _t3606 = *_hp; free(_hp); }
    (void)_t3606;
    ;
    ;
    if (_t3606) {
        Str *_t3285 = Str_lit("/src/modes/", 11ULL);
        (void)_t3285;
        Str *_t3286 = Str_concat(bin_dir, _t3285);
        (void)_t3286;
        Str_delete(_t3285, &(Bool){1});
        Str *_t3287 = Str_concat(_t3286, auto_import);
        (void)_t3287;
        Str_delete(_t3286, &(Bool){1});
        Str *_t3288 = Str_lit(".til", 4ULL);
        (void)_t3288;
        Str *mode_til_path = Str_concat(_t3287, _t3288);
        (void)mode_til_path;
        Str_delete(_t3287, &(Bool){1});
        Str_delete(_t3288, &(Bool){1});
        Str *mode_source = readfile(mode_til_path);
        (void)mode_source;
        Vec *mode_tokens = tokenize(mode_source, mode_til_path);
        (void)mode_tokens;
        Str_delete(mode_source, &(Bool){1});
        Expr *mode_ast = til_parse(mode_tokens, mode_til_path);
        (void)mode_ast;
        Str_delete(mode_til_path, &(Bool){1});
        Vec_delete(mode_tokens, &(Bool){1});
        U32 _t3289 = 0;
        (void)_t3289;
        *i = _t3289;
        ;
        while (1) {
            U32 _t3282 = expr_nchildren(mode_ast);
            (void)_t3282;
            Bool _wcond3281; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3282}); _wcond3281 = *_hp; free(_hp); }
            (void)_wcond3281;
            ;
            if (_wcond3281) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(mode_ast, DEREF(i));
            (void)ch;
            expr_vec_push(merged, ch);
            U32 _t3283 = 1;
            (void)_t3283;
            U32 _t3284 = U32_add(DEREF(i), _t3283);
            (void)_t3284;
            ;
            *i = _t3284;
            ;
        }
        Expr_delete(mode_ast, &(Bool){1});
    }
    ;
    Str_delete(auto_import, &(Bool){1});
    Str_delete(bin_dir, &(Bool){1});
    U32 _t3607 = 0;
    (void)_t3607;
    *i = _t3607;
    ;
    while (1) {
        U32 _t3291 = expr_vec_count(import_decls);
        (void)_t3291;
        Bool _wcond3290; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3291}); _wcond3290 = *_hp; free(_hp); }
        (void)_wcond3290;
        ;
        if (_wcond3290) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_vec_get(import_decls, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t3292 = 1;
        (void)_t3292;
        U32 _t3293 = U32_add(DEREF(i), _t3292);
        (void)_t3293;
        ;
        *i = _t3293;
        ;
    }
    Vec_delete(import_decls, &(Bool){1});
    U32 _t3608 = 0;
    (void)_t3608;
    *i = _t3608;
    ;
    while (1) {
        U32 _t3295 = expr_nchildren(ast);
        (void)_t3295;
        Bool _wcond3294; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3295}); _wcond3294 = *_hp; free(_hp); }
        (void)_wcond3294;
        ;
        if (_wcond3294) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_get_child(ast, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t3296 = 1;
        (void)_t3296;
        U32 _t3297 = U32_add(DEREF(i), _t3296);
        (void)_t3297;
        ;
        *i = _t3297;
        ;
    }
    expr_swap_children(ast, merged);
    Vec_delete(merged, &(Bool){1});
    Str *link_flags = Str_lit("", 0ULL);
    (void)link_flags;
    Str *link_c_paths = Str_lit("", 0ULL);
    (void)link_c_paths;
    Vec *kept = expr_vec_new();
    (void)kept;
    U32 _t3609 = 0;
    (void)_t3609;
    *i = _t3609;
    ;
    while (1) {
        U32 _t3313 = expr_nchildren(ast);
        (void)_t3313;
        Bool _wcond3298; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3313}); _wcond3298 = *_hp; free(_hp); }
        (void)_wcond3298;
        ;
        if (_wcond3298) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(ast, DEREF(i));
        (void)stmt;
        I32 _t3314 = expr_get_tag(stmt);
        (void)_t3314;
        U32 _t3315 = expr_nchildren(stmt);
        (void)_t3315;
        U32 _t3316 = 2;
        (void)_t3316;
        Bool _t3317 = I32_eq(_t3314, DEREF(NODE_FCALL));
        (void)_t3317;
        ;
        Bool _t3318 = U32_eq(_t3315, _t3316);
        (void)_t3318;
        ;
        ;
        U32 *_t3319 = malloc(sizeof(U32));
        *_t3319 = 0;
        (void)_t3319;
        Expr *_t3320 = expr_get_child(stmt, DEREF(_t3319));
        (void)_t3320;
        I32 _t3321 = expr_get_tag(_t3320);
        (void)_t3321;
        U32_delete(_t3319, &(Bool){1});
        Bool _t3322 = Bool_and(_t3317, _t3318);
        (void)_t3322;
        ;
        ;
        Bool _t3323 = I32_eq(_t3321, DEREF(NODE_IDENT));
        (void)_t3323;
        ;
        U32 *_t3324 = malloc(sizeof(U32));
        *_t3324 = 1;
        (void)_t3324;
        Expr *_t3325 = expr_get_child(stmt, DEREF(_t3324));
        (void)_t3325;
        I32 _t3326 = expr_get_tag(_t3325);
        (void)_t3326;
        U32_delete(_t3324, &(Bool){1});
        Bool _t3327 = Bool_and(_t3322, _t3323);
        (void)_t3327;
        ;
        ;
        Bool _t3328 = I32_eq(_t3326, DEREF(NODE_LITERAL_STR));
        (void)_t3328;
        ;
        Bool _t3329 = Bool_and(_t3327, _t3328);
        (void)_t3329;
        ;
        ;
        if (_t3329) {
            U32 *_t3307 = malloc(sizeof(U32));
            *_t3307 = 0;
            (void)_t3307;
            Expr *_t3308 = expr_get_child(stmt, DEREF(_t3307));
            (void)_t3308;
            Str *fname = expr_get_str_val(_t3308);
            (void)fname;
            U32 *_t3309 = malloc(sizeof(U32));
            *_t3309 = 1;
            (void)_t3309;
            Expr *_t3310 = expr_get_child(stmt, DEREF(_t3309));
            (void)_t3310;
            Str *arg = expr_get_str_val(_t3310);
            (void)arg;
            Str *_t3311 = Str_lit("link", 4ULL);
            (void)_t3311;
            Bool _t3312; { Bool *_hp = (Bool *)Str_eq(fname, _t3311); _t3312 = *_hp; free(_hp); }
            (void)_t3312;
            Str_delete(_t3311, &(Bool){1});
            if (_t3312) {
                Str *_t3299 = Str_lit(" -l", 3ULL);
                (void)_t3299;
                Str *_t3300 = Str_concat(link_flags, _t3299);
                (void)_t3300;
                Str_delete(_t3299, &(Bool){1});
                link_flags = Str_concat(_t3300, arg);
                Str_delete(_t3300, &(Bool){1});
            } else {
                Str *_t3305 = Str_lit("link_c", 6ULL);
                (void)_t3305;
                Bool _t3306; { Bool *_hp = (Bool *)Str_eq(fname, _t3305); _t3306 = *_hp; free(_hp); }
                (void)_t3306;
                Str_delete(_t3305, &(Bool){1});
                if (_t3306) {
                    U64 _t3302; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t3302 = *_hp; free(_hp); }
                    (void)_t3302;
                    U64 _t3303 = 0;
                    (void)_t3303;
                    Bool _t3304; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3302}, &(U64){_t3303}); _t3304 = *_hp; free(_hp); }
                    (void)_t3304;
                    ;
                    ;
                    if (_t3304) {
                        Str *_t3301 = Str_lit(" ", 1ULL);
                        (void)_t3301;
                        link_c_paths = Str_concat(link_c_paths, _t3301);
                        Str_delete(_t3301, &(Bool){1});
                    }
                    ;
                    link_c_paths = Str_concat(link_c_paths, arg);
                } else {
                    expr_vec_push(kept, stmt);
                }
                ;
            }
            U32_delete(_t3307, &(Bool){1});
            U32_delete(_t3309, &(Bool){1});
            ;
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t3330 = 1;
        (void)_t3330;
        U32 _t3331 = U32_add(DEREF(i), _t3330);
        (void)_t3331;
        ;
        *i = _t3331;
        ;
    }
    U32_delete(i, &(Bool){1});
    expr_swap_children(ast, kept);
    Vec_delete(kept, &(Bool){1});
    TypeScope *scope = tscope_new(NULL);
    (void)scope;
    I32 _t3610 = init_declarations(ast, scope);
    (void)_t3610;
    ;
    I32 type_errors = type_check(ast, scope, cur_mode);
    (void)type_errors;
    TypeScope_delete(scope, &(Bool){1});
    I32 _t3611 = 0;
    (void)_t3611;
    Bool _t3612; { Bool *_hp = (Bool *)I32_gt(&(I32){type_errors}, &(I32){_t3611}); _t3612 = *_hp; free(_hp); }
    (void)_t3612;
    ;
    if (_t3612) {
        Str *_t3332 = Str_lit("Str", 3ULL);
        (void)_t3332;
        U64 _t3333; { U64 *_hp = (U64 *)Str_size(); _t3333 = *_hp; free(_hp); }
        (void)_t3333;
        U64 _t3334 = 1;
        (void)_t3334;
        Array *_va68 = Array_new(_t3332, &(U64){_t3333}, &(U64){_t3334});
        (void)_va68;
        Str_delete(_t3332, &(Bool){1});
        ;
        ;
        Str *_t3335 = I32_to_str(&(I32){type_errors});
        (void)_t3335;
        Str *_t3336 = Str_lit(" type error(s) found", 20ULL);
        (void)_t3336;
        U64 _t3337 = 0;
        (void)_t3337;
        Str *_t3338 = Str_concat(_t3335, _t3336);
        (void)_t3338;
        Str_delete(_t3335, &(Bool){1});
        Str_delete(_t3336, &(Bool){1});
        Array_set(_va68, &(U64){_t3337}, _t3338);
        ;
        Str *_t3339 = Str_lit("src/til.til:432:15", 18ULL);
        (void)_t3339;
        panic(_t3339, _va68);
        Str_delete(_t3339, &(Bool){1});
    }
    ;
    ;
    Str *_t3613 = Str_lit("test", 4ULL);
    (void)_t3613;
    Str *_t3614 = Str_lit("test", 4ULL);
    (void)_t3614;
    Bool _t3615; { Bool *_hp = (Bool *)Str_eq(command, _t3613); _t3615 = *_hp; free(_hp); }
    (void)_t3615;
    Str_delete(_t3613, &(Bool){1});
    Bool _t3616; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t3614); _t3616 = *_hp; free(_hp); }
    (void)_t3616;
    Str_delete(_t3614, &(Bool){1});
    Str *_t3617 = Str_lit("pure", 4ULL);
    (void)_t3617;
    Bool _t3618 = Bool_or(_t3615, _t3616);
    (void)_t3618;
    ;
    ;
    Bool _t3619; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t3617); _t3619 = *_hp; free(_hp); }
    (void)_t3619;
    Str_delete(_t3617, &(Bool){1});
    Str *_t3620 = Str_lit("pura", 4ULL);
    (void)_t3620;
    Bool _t3621 = Bool_or(_t3618, _t3619);
    (void)_t3621;
    ;
    ;
    Bool _t3622; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t3620); _t3622 = *_hp; free(_hp); }
    (void)_t3622;
    Str_delete(_t3620, &(Bool){1});
    Bool run_tests = Bool_or(_t3621, _t3622);
    (void)run_tests;
    ;
    ;
    precomp(ast);
    Str *_t3623 = Str_lit("translate", 9ULL);
    (void)_t3623;
    Str *_t3624 = Str_lit("build", 5ULL);
    (void)_t3624;
    Bool _t3625; { Bool *_hp = (Bool *)Str_eq(command, _t3623); _t3625 = *_hp; free(_hp); }
    (void)_t3625;
    Str_delete(_t3623, &(Bool){1});
    Bool _t3626; { Bool *_hp = (Bool *)Str_eq(command, _t3624); _t3626 = *_hp; free(_hp); }
    (void)_t3626;
    Str_delete(_t3624, &(Bool){1});
    Bool _t3627; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t3627 = *_hp; free(_hp); }
    (void)_t3627;
    Bool _t3628 = Bool_or(_t3625, _t3626);
    (void)_t3628;
    ;
    ;
    Bool is_lib_target = Bool_and(_t3627, _t3628);
    (void)is_lib_target;
    ;
    ;
    U64 _t3629; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t3629 = *_hp; free(_hp); }
    (void)_t3629;
    U64 _t3630 = 0;
    (void)_t3630;
    Bool _t3631 = Bool_not(is_lib_target);
    (void)_t3631;
    ;
    Bool _t3632 = U64_eq(_t3629, _t3630);
    (void)_t3632;
    ;
    ;
    Bool _t3633 = Bool_and(_t3631, _t3632);
    (void)_t3633;
    ;
    ;
    if (_t3633) {
        scavenge(ast, cur_mode, run_tests);
    }
    ;
    I32 result = 0;
    (void)result;
    Str *user_c = Str_lit("", 0ULL);
    (void)user_c;
    U64 _t3634; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t3634 = *_hp; free(_hp); }
    (void)_t3634;
    U64 _t3635 = 0;
    (void)_t3635;
    Bool _t3636; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3634}, &(U64){_t3635}); _t3636 = *_hp; free(_hp); }
    (void)_t3636;
    ;
    ;
    if (_t3636) {
        user_c = Str_clone(link_c_paths);
    }
    ;
    Str_delete(link_c_paths, &(Bool){1});
    Str *_t3637 = Str_lit("Str", 3ULL);
    (void)_t3637;
    U64 _t3638; { U64 *_hp = (U64 *)Str_size(); _t3638 = *_hp; free(_hp); }
    (void)_t3638;
    Vec *user_argv = Vec_new(_t3637, &(U64){_t3638});
    (void)user_argv;
    Str_delete(_t3637, &(Bool){1});
    ;
    U64 _t3639 = 1;
    (void)_t3639;
    U64 *ai = malloc(sizeof(U64)); *ai = U64_add(DEREF(path_idx), _t3639);
    (void)ai;
    ;
    U64_delete(path_idx, &(Bool){1});
    while (1) {
        U64 _t3356; { U64 *_hp = (U64 *)Array_len(args); _t3356 = *_hp; free(_hp); }
        (void)_t3356;
        Bool _wcond3340; { Bool *_hp = (Bool *)U64_lt(ai, &(U64){_t3356}); _wcond3340 = *_hp; free(_hp); }
        (void)_wcond3340;
        ;
        if (_wcond3340) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, ai);
        (void)arg;
        Str *_t3357 = Str_lit("-l", 2ULL);
        (void)_t3357;
        Bool _t3358; { Bool *_hp = (Bool *)Str_starts_with(arg, _t3357); _t3358 = *_hp; free(_hp); }
        (void)_t3358;
        Str_delete(_t3357, &(Bool){1});
        if (_t3358) {
            U64 _t3343 = 2;
            (void)_t3343;
            U64 _t3344; { U64 *_hp = (U64 *)Str_len(arg); _t3344 = *_hp; free(_hp); }
            (void)_t3344;
            Str *lib = Str_substr(arg, &(U64){_t3343}, &(U64){_t3344});
            (void)lib;
            ;
            ;
            U64 _t3345; { U64 *_hp = (U64 *)Str_len(lib); _t3345 = *_hp; free(_hp); }
            (void)_t3345;
            U64 _t3346 = 0;
            (void)_t3346;
            U64 _t3347 = 1;
            (void)_t3347;
            U64 _t3348 = U64_add(DEREF(ai), _t3347);
            (void)_t3348;
            ;
            U64 _t3349; { U64 *_hp = (U64 *)Array_len(args); _t3349 = *_hp; free(_hp); }
            (void)_t3349;
            Bool _t3350 = U64_eq(_t3345, _t3346);
            (void)_t3350;
            ;
            ;
            Bool _t3351; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3348}, &(U64){_t3349}); _t3351 = *_hp; free(_hp); }
            (void)_t3351;
            ;
            ;
            Bool _t3352 = Bool_and(_t3350, _t3351);
            (void)_t3352;
            ;
            ;
            if (_t3352) {
                U64 _t3341 = 1;
                (void)_t3341;
                U64 _t3342 = U64_add(DEREF(ai), _t3341);
                (void)_t3342;
                ;
                *ai = _t3342;
                ;
                Str *next_arg = Array_get(args, ai);
                (void)next_arg;
                lib = Str_clone(next_arg);
            }
            ;
            Str *_t3353 = Str_lit(" -l", 3ULL);
            (void)_t3353;
            Str *_t3354 = Str_concat(link_flags, _t3353);
            (void)_t3354;
            Str_delete(_t3353, &(Bool){1});
            link_flags = Str_concat(_t3354, lib);
            Str_delete(_t3354, &(Bool){1});
            Str_delete(lib, &(Bool){1});
        } else {
            Str *_t3355 = Str_clone(arg);
            (void)_t3355;
            Vec_push(user_argv, _t3355);
        }
        ;
        U64 _t3359 = 1;
        (void)_t3359;
        U64 _t3360 = U64_add(DEREF(ai), _t3359);
        (void)_t3360;
        ;
        *ai = _t3360;
        ;
    }
    U64_delete(ai, &(Bool){1});
    Array_delete(args, &(Bool){1});
    Str *lflags = Str_lit("", 0ULL);
    (void)lflags;
    U64 _t3640; { U64 *_hp = (U64 *)Str_len(link_flags); _t3640 = *_hp; free(_hp); }
    (void)_t3640;
    U64 _t3641 = 0;
    (void)_t3641;
    Bool _t3642; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3640}, &(U64){_t3641}); _t3642 = *_hp; free(_hp); }
    (void)_t3642;
    ;
    ;
    if (_t3642) {
        lflags = Str_clone(link_flags);
    }
    ;
    Str_delete(link_flags, &(Bool){1});
    Bool is_lib_mode; { Bool *_hp = (Bool *)mode_is_lib(cur_mode); is_lib_mode = *_hp; free(_hp); }
    (void)is_lib_mode;
    Str *_t3643 = Str_lit("interpret", 9ULL);
    (void)_t3643;
    Str *_t3644 = Str_lit("test", 4ULL);
    (void)_t3644;
    Bool _t3645; { Bool *_hp = (Bool *)Str_eq(command, _t3643); _t3645 = *_hp; free(_hp); }
    (void)_t3645;
    Str_delete(_t3643, &(Bool){1});
    Bool _t3646; { Bool *_hp = (Bool *)Str_eq(command, _t3644); _t3646 = *_hp; free(_hp); }
    (void)_t3646;
    Str_delete(_t3644, &(Bool){1});
    Bool _t3647 = Bool_or(_t3645, _t3646);
    (void)_t3647;
    ;
    ;
    if (_t3647) {
        Str *_t3367 = Str_lit("interpret", 9ULL);
        (void)_t3367;
        Bool _t3368; { Bool *_hp = (Bool *)Str_eq(command, _t3367); _t3368 = *_hp; free(_hp); }
        (void)_t3368;
        Str_delete(_t3367, &(Bool){1});
        Bool _t3369 = Bool_and(is_lib_mode, _t3368);
        (void)_t3369;
        ;
        if (_t3369) {
            Str *_t3361 = Str_lit("Str", 3ULL);
            (void)_t3361;
            U64 _t3362; { U64 *_hp = (U64 *)Str_size(); _t3362 = *_hp; free(_hp); }
            (void)_t3362;
            U64 _t3363 = 1;
            (void)_t3363;
            Array *_va69 = Array_new(_t3361, &(U64){_t3362}, &(U64){_t3363});
            (void)_va69;
            Str_delete(_t3361, &(Bool){1});
            ;
            ;
            U64 _t3364 = 0;
            (void)_t3364;
            Str *_t3365 = Str_lit("cannot interpret a library — use translate or build", 53ULL);
            (void)_t3365;
            Array_set(_va69, &(U64){_t3364}, _t3365);
            ;
            Str *_t3366 = Str_lit("src/til.til:486:19", 18ULL);
            (void)_t3366;
            panic(_t3366, _va69);
            Str_delete(_t3366, &(Bool){1});
        }
        ;
        I32 _t3370 = til_interpret_v(ast, cur_mode, run_tests, path, user_c, ext_c_path, lflags, user_argv);
        (void)_t3370;
        result = _t3370;
        ;
    } else {
        Str *_t3563 = Str_lit("translate", 9ULL);
        (void)_t3563;
        Str *_t3564 = Str_lit("build", 5ULL);
        (void)_t3564;
        Bool _t3565; { Bool *_hp = (Bool *)Str_eq(command, _t3563); _t3565 = *_hp; free(_hp); }
        (void)_t3565;
        Str_delete(_t3563, &(Bool){1});
        Bool _t3566; { Bool *_hp = (Bool *)Str_eq(command, _t3564); _t3566 = *_hp; free(_hp); }
        (void)_t3566;
        Str_delete(_t3564, &(Bool){1});
        Str *_t3567 = Str_lit("run", 3ULL);
        (void)_t3567;
        Bool _t3568 = Bool_or(_t3565, _t3566);
        (void)_t3568;
        ;
        ;
        Bool _t3569; { Bool *_hp = (Bool *)Str_eq(command, _t3567); _t3569 = *_hp; free(_hp); }
        (void)_t3569;
        Str_delete(_t3567, &(Bool){1});
        Bool _t3570 = Bool_or(_t3568, _t3569);
        (void)_t3570;
        ;
        ;
        if (_t3570) {
            Str *_t3496 = Str_lit("run", 3ULL);
            (void)_t3496;
            Bool _t3497; { Bool *_hp = (Bool *)Str_eq(command, _t3496); _t3497 = *_hp; free(_hp); }
            (void)_t3497;
            Str_delete(_t3496, &(Bool){1});
            Bool _t3498 = Bool_and(is_lib_mode, _t3497);
            (void)_t3498;
            ;
            if (_t3498) {
                Str *_t3371 = Str_lit("Str", 3ULL);
                (void)_t3371;
                U64 _t3372; { U64 *_hp = (U64 *)Str_size(); _t3372 = *_hp; free(_hp); }
                (void)_t3372;
                U64 _t3373 = 1;
                (void)_t3373;
                Array *_va70 = Array_new(_t3371, &(U64){_t3372}, &(U64){_t3373});
                (void)_va70;
                Str_delete(_t3371, &(Bool){1});
                ;
                ;
                U64 _t3374 = 0;
                (void)_t3374;
                Str *_t3375 = Str_lit("cannot run a library — use translate or build", 47ULL);
                (void)_t3375;
                Array_set(_va70, &(U64){_t3374}, _t3375);
                ;
                Str *_t3376 = Str_lit("src/til.til:492:19", 18ULL);
                (void)_t3376;
                panic(_t3376, _va70);
                Str_delete(_t3376, &(Bool){1});
            }
            ;
            Str *_t3499 = Str_lit("/", 1ULL);
            (void)_t3499;
            I64 *last_slash = Str_rfind(path, _t3499);
            (void)last_slash;
            Str_delete(_t3499, &(Bool){1});
            Str *basename = Str_clone(path);
            (void)basename;
            I64 _t3500 = 0;
            (void)_t3500;
            Bool _t3501; { Bool *_hp = (Bool *)I64_gte(last_slash, &(I64){_t3500}); _t3501 = *_hp; free(_hp); }
            (void)_t3501;
            ;
            if (_t3501) {
                I64 _t3377 = 1;
                (void)_t3377;
                I64 _t3378 = I64_add(DEREF(last_slash), _t3377);
                (void)_t3378;
                ;
                U64 _t3379; { U64 *_hp = (U64 *)Str_len(path); _t3379 = *_hp; free(_hp); }
                (void)_t3379;
                U64 _t3380 = I64_to_u64(DEREF(last_slash));
                (void)_t3380;
                U64 _t3381 = U64_sub(_t3379, _t3380);
                (void)_t3381;
                ;
                ;
                U64 _t3382 = 1;
                (void)_t3382;
                U64 _t3383 = I64_to_u64(_t3378);
                (void)_t3383;
                ;
                U64 _t3384 = U64_sub(_t3381, _t3382);
                (void)_t3384;
                ;
                ;
                basename = Str_substr(path, &(U64){_t3383}, &(U64){_t3384});
                ;
                ;
            }
            ;
            I64_delete(last_slash, &(Bool){1});
            U64 name_len; { U64 *_hp = (U64 *)Str_len(basename); name_len = *_hp; free(_hp); }
            (void)name_len;
            Str *_t3502 = Str_lit(".til", 4ULL);
            (void)_t3502;
            Bool _t3503; { Bool *_hp = (Bool *)Str_ends_with(basename, _t3502); _t3503 = *_hp; free(_hp); }
            (void)_t3503;
            Str_delete(_t3502, &(Bool){1});
            if (_t3503) {
                U64 _t3385 = 4;
                (void)_t3385;
                U64 _t3386 = U64_sub(name_len, _t3385);
                (void)_t3386;
                ;
                name_len = _t3386;
                ;
            }
            ;
            U64 _t3504 = 0;
            (void)_t3504;
            Str *name = Str_substr(basename, &(U64){_t3504}, &(U64){name_len});
            (void)name;
            ;
            Str_delete(basename, &(Bool){1});
            ;
            Str *_t3505 = Str_lit("gen/til/", 8ULL);
            (void)_t3505;
            Str *_t3506 = Str_concat(_t3505, name);
            (void)_t3506;
            Str_delete(_t3505, &(Bool){1});
            Str *_t3507 = Str_lit(".c", 2ULL);
            (void)_t3507;
            Str *c_path = Str_concat(_t3506, _t3507);
            (void)c_path;
            Str_delete(_t3506, &(Bool){1});
            Str_delete(_t3507, &(Bool){1});
            U64 _t3508; { U64 *_hp = (U64 *)Str_len(custom_c); _t3508 = *_hp; free(_hp); }
            (void)_t3508;
            U64 _t3509 = 0;
            (void)_t3509;
            Bool _t3510; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3508}, &(U64){_t3509}); _t3510 = *_hp; free(_hp); }
            (void)_t3510;
            ;
            ;
            if (_t3510) {
                c_path = Str_clone(custom_c);
            }
            ;
            Str *_t3511 = Str_lit("bin/til/", 8ULL);
            (void)_t3511;
            Str *bin_path = Str_concat(_t3511, name);
            (void)bin_path;
            Str_delete(_t3511, &(Bool){1});
            U64 _t3512; { U64 *_hp = (U64 *)Str_len(custom_bin); _t3512 = *_hp; free(_hp); }
            (void)_t3512;
            U64 _t3513 = 0;
            (void)_t3513;
            Bool _t3514; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3512}, &(U64){_t3513}); _t3514 = *_hp; free(_hp); }
            (void)_t3514;
            ;
            ;
            if (_t3514) {
                bin_path = Str_clone(custom_bin);
            }
            ;
            Str *_t3515 = Str_lit("run", 3ULL);
            (void)_t3515;
            Bool _t3516; { Bool *_hp = (Bool *)Str_eq(command, _t3515); _t3516 = *_hp; free(_hp); }
            (void)_t3516;
            Str_delete(_t3515, &(Bool){1});
            Bool _t3517; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t3517 = *_hp; free(_hp); }
            (void)_t3517;
            Bool _t3518 = Bool_not(_t3516);
            (void)_t3518;
            ;
            Bool do_lib = Bool_and(_t3517, _t3518);
            (void)do_lib;
            ;
            ;
            if (do_lib) {
                Str *_t3387 = Str_lit("mkdir -p gen/til gen/lib", 24ULL);
                (void)_t3387;
                I32 _t3388 = til_system(_t3387);
                (void)_t3388;
                Str_delete(_t3387, &(Bool){1});
                ;
            } else {
                Str *_t3393 = Str_lit("/", 1ULL);
                (void)_t3393;
                I64 cp_slash; { I64 *_hp = (I64 *)Str_rfind(c_path, _t3393); cp_slash = *_hp; free(_hp); }
                (void)cp_slash;
                Str_delete(_t3393, &(Bool){1});
                Str *_t3394 = Str_lit("/", 1ULL);
                (void)_t3394;
                I64 bp_slash; { I64 *_hp = (I64 *)Str_rfind(bin_path, _t3394); bp_slash = *_hp; free(_hp); }
                (void)bp_slash;
                Str_delete(_t3394, &(Bool){1});
                Str *cp_dir = Str_lit("gen/til", 7ULL);
                (void)cp_dir;
                I64 _t3395 = 0;
                (void)_t3395;
                Bool _t3396; { Bool *_hp = (Bool *)I64_gt(&(I64){cp_slash}, &(I64){_t3395}); _t3396 = *_hp; free(_hp); }
                (void)_t3396;
                ;
                if (_t3396) {
                    U64 _t3389 = 0;
                    (void)_t3389;
                    U64 _t3390 = I64_to_u64(cp_slash);
                    (void)_t3390;
                    cp_dir = Str_substr(c_path, &(U64){_t3389}, &(U64){_t3390});
                    ;
                    ;
                }
                ;
                ;
                Str *bp_dir = Str_lit("bin/til", 7ULL);
                (void)bp_dir;
                I64 _t3397 = 0;
                (void)_t3397;
                Bool _t3398; { Bool *_hp = (Bool *)I64_gt(&(I64){bp_slash}, &(I64){_t3397}); _t3398 = *_hp; free(_hp); }
                (void)_t3398;
                ;
                if (_t3398) {
                    U64 _t3391 = 0;
                    (void)_t3391;
                    U64 _t3392 = I64_to_u64(bp_slash);
                    (void)_t3392;
                    bp_dir = Str_substr(bin_path, &(U64){_t3391}, &(U64){_t3392});
                    ;
                    ;
                }
                ;
                ;
                Str *_t3399 = Str_lit("mkdir -p ", 9ULL);
                (void)_t3399;
                Str *_t3400 = Str_concat(_t3399, cp_dir);
                (void)_t3400;
                Str_delete(_t3399, &(Bool){1});
                Str_delete(cp_dir, &(Bool){1});
                Str *_t3401 = Str_lit(" ", 1ULL);
                (void)_t3401;
                Str *_t3402 = Str_concat(_t3400, _t3401);
                (void)_t3402;
                Str_delete(_t3400, &(Bool){1});
                Str_delete(_t3401, &(Bool){1});
                Str *_t3403 = Str_concat(_t3402, bp_dir);
                (void)_t3403;
                Str_delete(_t3402, &(Bool){1});
                Str_delete(bp_dir, &(Bool){1});
                I32 _t3404 = til_system(_t3403);
                (void)_t3404;
                Str_delete(_t3403, &(Bool){1});
                ;
            }
            I32 _t3519 = build(ast, cur_mode, run_tests, path, c_path);
            (void)_t3519;
            result = _t3519;
            ;
            I32 _t3520 = 0;
            (void)_t3520;
            Bool _t3521 = I32_eq(result, _t3520);
            (void)_t3521;
            ;
            Bool _t3522 = Bool_and(_t3521, do_lib);
            (void)_t3522;
            ;
            if (_t3522) {
                Str *_t3461 = Str_lit("gen/til/", 8ULL);
                (void)_t3461;
                Str *_t3462 = Str_concat(_t3461, name);
                (void)_t3462;
                Str_delete(_t3461, &(Bool){1});
                Str *_t3463 = Str_lit(".h", 2ULL);
                (void)_t3463;
                Str *h_path = Str_concat(_t3462, _t3463);
                (void)h_path;
                Str_delete(_t3462, &(Bool){1});
                Str_delete(_t3463, &(Bool){1});
                Str *_t3464 = Str_lit("gen/til/", 8ULL);
                (void)_t3464;
                Str *_t3465 = Str_concat(_t3464, name);
                (void)_t3465;
                Str_delete(_t3464, &(Bool){1});
                Str *_t3466 = Str_lit(".til", 4ULL);
                (void)_t3466;
                Str *til_path = Str_concat(_t3465, _t3466);
                (void)til_path;
                Str_delete(_t3465, &(Bool){1});
                Str_delete(_t3466, &(Bool){1});
                I32 _t3467 = build_header(ast, h_path);
                (void)_t3467;
                result = _t3467;
                ;
                I32 _t3468 = 0;
                (void)_t3468;
                Bool _t3469 = I32_eq(result, _t3468);
                (void)_t3469;
                ;
                if (_t3469) {
                    I32 _t3405 = build_til_binding(ast, til_path, name);
                    (void)_t3405;
                    result = _t3405;
                    ;
                }
                ;
                I32 _t3470 = 0;
                (void)_t3470;
                Str *_t3471 = Str_lit("translate", 9ULL);
                (void)_t3471;
                Bool _t3472 = I32_eq(result, _t3470);
                (void)_t3472;
                ;
                Bool _t3473; { Bool *_hp = (Bool *)Str_eq(command, _t3471); _t3473 = *_hp; free(_hp); }
                (void)_t3473;
                Str_delete(_t3471, &(Bool){1});
                Bool _t3474 = Bool_and(_t3472, _t3473);
                (void)_t3474;
                ;
                ;
                if (_t3474) {
                    Str *_t3406 = Str_lit("Str", 3ULL);
                    (void)_t3406;
                    U64 _t3407; { U64 *_hp = (U64 *)Str_size(); _t3407 = *_hp; free(_hp); }
                    (void)_t3407;
                    U64 _t3408 = 1;
                    (void)_t3408;
                    Array *_va71 = Array_new(_t3406, &(U64){_t3407}, &(U64){_t3408});
                    (void)_va71;
                    Str_delete(_t3406, &(Bool){1});
                    ;
                    ;
                    Str *_t3409 = Str_lit("Generated: ", 11ULL);
                    (void)_t3409;
                    U64 _t3410 = 0;
                    (void)_t3410;
                    Str *_t3411 = Str_concat(_t3409, c_path);
                    (void)_t3411;
                    Str_delete(_t3409, &(Bool){1});
                    Array_set(_va71, &(U64){_t3410}, _t3411);
                    ;
                    println(_va71);
                    Str *_t3412 = Str_lit("Str", 3ULL);
                    (void)_t3412;
                    U64 _t3413; { U64 *_hp = (U64 *)Str_size(); _t3413 = *_hp; free(_hp); }
                    (void)_t3413;
                    U64 _t3414 = 1;
                    (void)_t3414;
                    Array *_va72 = Array_new(_t3412, &(U64){_t3413}, &(U64){_t3414});
                    (void)_va72;
                    Str_delete(_t3412, &(Bool){1});
                    ;
                    ;
                    Str *_t3415 = Str_lit("Generated: ", 11ULL);
                    (void)_t3415;
                    U64 _t3416 = 0;
                    (void)_t3416;
                    Str *_t3417 = Str_concat(_t3415, h_path);
                    (void)_t3417;
                    Str_delete(_t3415, &(Bool){1});
                    Array_set(_va72, &(U64){_t3416}, _t3417);
                    ;
                    println(_va72);
                    Str *_t3418 = Str_lit("Str", 3ULL);
                    (void)_t3418;
                    U64 _t3419; { U64 *_hp = (U64 *)Str_size(); _t3419 = *_hp; free(_hp); }
                    (void)_t3419;
                    U64 _t3420 = 1;
                    (void)_t3420;
                    Array *_va73 = Array_new(_t3418, &(U64){_t3419}, &(U64){_t3420});
                    (void)_va73;
                    Str_delete(_t3418, &(Bool){1});
                    ;
                    ;
                    Str *_t3421 = Str_lit("Generated: ", 11ULL);
                    (void)_t3421;
                    U64 _t3422 = 0;
                    (void)_t3422;
                    Str *_t3423 = Str_concat(_t3421, til_path);
                    (void)_t3423;
                    Str_delete(_t3421, &(Bool){1});
                    Array_set(_va73, &(U64){_t3422}, _t3423);
                    ;
                    println(_va73);
                }
                ;
                I32 _t3475 = 0;
                (void)_t3475;
                Str *_t3476 = Str_lit("build", 5ULL);
                (void)_t3476;
                Bool _t3477 = I32_eq(result, _t3475);
                (void)_t3477;
                ;
                Bool _t3478; { Bool *_hp = (Bool *)Str_eq(command, _t3476); _t3478 = *_hp; free(_hp); }
                (void)_t3478;
                Str_delete(_t3476, &(Bool){1});
                Bool _t3479 = Bool_and(_t3477, _t3478);
                (void)_t3479;
                ;
                ;
                if (_t3479) {
                    I32 _t3458 = til_compile_lib(c_path, name, ext_c_path, user_c, lflags);
                    (void)_t3458;
                    result = _t3458;
                    ;
                    I32 _t3459 = 0;
                    (void)_t3459;
                    Bool _t3460 = I32_eq(result, _t3459);
                    (void)_t3460;
                    ;
                    if (_t3460) {
                        Str *_t3424 = Str_lit("Str", 3ULL);
                        (void)_t3424;
                        U64 _t3425; { U64 *_hp = (U64 *)Str_size(); _t3425 = *_hp; free(_hp); }
                        (void)_t3425;
                        U64 _t3426 = 1;
                        (void)_t3426;
                        Array *_va74 = Array_new(_t3424, &(U64){_t3425}, &(U64){_t3426});
                        (void)_va74;
                        Str_delete(_t3424, &(Bool){1});
                        ;
                        ;
                        Str *_t3427 = Str_lit("Generated: ", 11ULL);
                        (void)_t3427;
                        U64 _t3428 = 0;
                        (void)_t3428;
                        Str *_t3429 = Str_concat(_t3427, c_path);
                        (void)_t3429;
                        Str_delete(_t3427, &(Bool){1});
                        Array_set(_va74, &(U64){_t3428}, _t3429);
                        ;
                        println(_va74);
                        Str *_t3430 = Str_lit("Str", 3ULL);
                        (void)_t3430;
                        U64 _t3431; { U64 *_hp = (U64 *)Str_size(); _t3431 = *_hp; free(_hp); }
                        (void)_t3431;
                        U64 _t3432 = 1;
                        (void)_t3432;
                        Array *_va75 = Array_new(_t3430, &(U64){_t3431}, &(U64){_t3432});
                        (void)_va75;
                        Str_delete(_t3430, &(Bool){1});
                        ;
                        ;
                        Str *_t3433 = Str_lit("Generated: ", 11ULL);
                        (void)_t3433;
                        U64 _t3434 = 0;
                        (void)_t3434;
                        Str *_t3435 = Str_concat(_t3433, h_path);
                        (void)_t3435;
                        Str_delete(_t3433, &(Bool){1});
                        Array_set(_va75, &(U64){_t3434}, _t3435);
                        ;
                        println(_va75);
                        Str *_t3436 = Str_lit("Str", 3ULL);
                        (void)_t3436;
                        U64 _t3437; { U64 *_hp = (U64 *)Str_size(); _t3437 = *_hp; free(_hp); }
                        (void)_t3437;
                        U64 _t3438 = 1;
                        (void)_t3438;
                        Array *_va76 = Array_new(_t3436, &(U64){_t3437}, &(U64){_t3438});
                        (void)_va76;
                        Str_delete(_t3436, &(Bool){1});
                        ;
                        ;
                        Str *_t3439 = Str_lit("Generated: ", 11ULL);
                        (void)_t3439;
                        U64 _t3440 = 0;
                        (void)_t3440;
                        Str *_t3441 = Str_concat(_t3439, til_path);
                        (void)_t3441;
                        Str_delete(_t3439, &(Bool){1});
                        Array_set(_va76, &(U64){_t3440}, _t3441);
                        ;
                        println(_va76);
                        Str *_t3442 = Str_lit("Str", 3ULL);
                        (void)_t3442;
                        U64 _t3443; { U64 *_hp = (U64 *)Str_size(); _t3443 = *_hp; free(_hp); }
                        (void)_t3443;
                        U64 _t3444 = 1;
                        (void)_t3444;
                        Array *_va77 = Array_new(_t3442, &(U64){_t3443}, &(U64){_t3444});
                        (void)_va77;
                        Str_delete(_t3442, &(Bool){1});
                        ;
                        ;
                        Str *_t3445 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t3445;
                        Str *_t3446 = Str_concat(_t3445, name);
                        (void)_t3446;
                        Str_delete(_t3445, &(Bool){1});
                        Str *_t3447 = Str_lit(".so", 3ULL);
                        (void)_t3447;
                        U64 _t3448 = 0;
                        (void)_t3448;
                        Str *_t3449 = Str_concat(_t3446, _t3447);
                        (void)_t3449;
                        Str_delete(_t3446, &(Bool){1});
                        Str_delete(_t3447, &(Bool){1});
                        Array_set(_va77, &(U64){_t3448}, _t3449);
                        ;
                        println(_va77);
                        Str *_t3450 = Str_lit("Str", 3ULL);
                        (void)_t3450;
                        U64 _t3451; { U64 *_hp = (U64 *)Str_size(); _t3451 = *_hp; free(_hp); }
                        (void)_t3451;
                        U64 _t3452 = 1;
                        (void)_t3452;
                        Array *_va78 = Array_new(_t3450, &(U64){_t3451}, &(U64){_t3452});
                        (void)_va78;
                        Str_delete(_t3450, &(Bool){1});
                        ;
                        ;
                        Str *_t3453 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t3453;
                        Str *_t3454 = Str_concat(_t3453, name);
                        (void)_t3454;
                        Str_delete(_t3453, &(Bool){1});
                        Str *_t3455 = Str_lit(".a", 2ULL);
                        (void)_t3455;
                        U64 _t3456 = 0;
                        (void)_t3456;
                        Str *_t3457 = Str_concat(_t3454, _t3455);
                        (void)_t3457;
                        Str_delete(_t3454, &(Bool){1});
                        Str_delete(_t3455, &(Bool){1});
                        Array_set(_va78, &(U64){_t3456}, _t3457);
                        ;
                        println(_va78);
                    }
                    ;
                }
                ;
                Str_delete(h_path, &(Bool){1});
                Str_delete(til_path, &(Bool){1});
            }
            ;
            Str_delete(name, &(Bool){1});
            I32 _t3523 = 0;
            (void)_t3523;
            Bool _t3524 = I32_eq(result, _t3523);
            (void)_t3524;
            ;
            Bool _t3525 = Bool_not(do_lib);
            (void)_t3525;
            Str *_t3526 = Str_lit("translate", 9ULL);
            (void)_t3526;
            Bool _t3527 = Bool_and(_t3524, _t3525);
            (void)_t3527;
            ;
            ;
            Bool _t3528; { Bool *_hp = (Bool *)Str_eq(command, _t3526); _t3528 = *_hp; free(_hp); }
            (void)_t3528;
            Str_delete(_t3526, &(Bool){1});
            Bool _t3529 = Bool_and(_t3527, _t3528);
            (void)_t3529;
            ;
            ;
            if (_t3529) {
                Str *_t3480 = Str_lit("Str", 3ULL);
                (void)_t3480;
                U64 _t3481; { U64 *_hp = (U64 *)Str_size(); _t3481 = *_hp; free(_hp); }
                (void)_t3481;
                U64 _t3482 = 1;
                (void)_t3482;
                Array *_va79 = Array_new(_t3480, &(U64){_t3481}, &(U64){_t3482});
                (void)_va79;
                Str_delete(_t3480, &(Bool){1});
                ;
                ;
                Str *_t3483 = Str_lit("Generated: ", 11ULL);
                (void)_t3483;
                U64 _t3484 = 0;
                (void)_t3484;
                Str *_t3485 = Str_concat(_t3483, c_path);
                (void)_t3485;
                Str_delete(_t3483, &(Bool){1});
                Array_set(_va79, &(U64){_t3484}, _t3485);
                ;
                println(_va79);
            }
            ;
            I32 _t3530 = 0;
            (void)_t3530;
            Bool _t3531 = I32_eq(result, _t3530);
            (void)_t3531;
            ;
            Bool _t3532 = Bool_not(do_lib);
            (void)_t3532;
            Str *_t3533 = Str_lit("translate", 9ULL);
            (void)_t3533;
            Bool _t3534; { Bool *_hp = (Bool *)Str_eq(command, _t3533); _t3534 = *_hp; free(_hp); }
            (void)_t3534;
            Str_delete(_t3533, &(Bool){1});
            Bool _t3535 = Bool_and(_t3531, _t3532);
            (void)_t3535;
            ;
            ;
            Bool _t3536 = Bool_not(_t3534);
            (void)_t3536;
            ;
            Bool _t3537 = Bool_and(_t3535, _t3536);
            (void)_t3537;
            ;
            ;
            if (_t3537) {
                I32 _t3486 = til_compile_c(c_path, bin_path, ext_c_path, user_c, lflags);
                (void)_t3486;
                result = _t3486;
                ;
            }
            ;
            Str_delete(c_path, &(Bool){1});
            I32 _t3538 = 0;
            (void)_t3538;
            Bool _t3539 = I32_eq(result, _t3538);
            (void)_t3539;
            ;
            Bool _t3540 = Bool_not(do_lib);
            (void)_t3540;
            ;
            Str *_t3541 = Str_lit("run", 3ULL);
            (void)_t3541;
            Bool _t3542 = Bool_and(_t3539, _t3540);
            (void)_t3542;
            ;
            ;
            Bool _t3543; { Bool *_hp = (Bool *)Str_eq(command, _t3541); _t3543 = *_hp; free(_hp); }
            (void)_t3543;
            Str_delete(_t3541, &(Bool){1});
            Bool _t3544 = Bool_and(_t3542, _t3543);
            (void)_t3544;
            ;
            ;
            if (_t3544) {
                Str *cmd = Str_clone(bin_path);
                (void)cmd;
                U64 *ui = malloc(sizeof(U64));
                *ui = 0;
                (void)ui;
                while (1) {
                    U64 _t3488; { U64 *_hp = (U64 *)Vec_len(user_argv); _t3488 = *_hp; free(_hp); }
                    (void)_t3488;
                    Bool _wcond3487; { Bool *_hp = (Bool *)U64_lt(ui, &(U64){_t3488}); _wcond3487 = *_hp; free(_hp); }
                    (void)_wcond3487;
                    ;
                    if (_wcond3487) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *uarg = Vec_get(user_argv, ui);
                    (void)uarg;
                    Str *_t3489 = Str_lit(" '", 2ULL);
                    (void)_t3489;
                    Str *_t3490 = Str_concat(cmd, _t3489);
                    (void)_t3490;
                    Str_delete(_t3489, &(Bool){1});
                    Str *_t3491 = Str_concat(_t3490, uarg);
                    (void)_t3491;
                    Str_delete(_t3490, &(Bool){1});
                    Str *_t3492 = Str_lit("'", 1ULL);
                    (void)_t3492;
                    cmd = Str_concat(_t3491, _t3492);
                    Str_delete(_t3491, &(Bool){1});
                    Str_delete(_t3492, &(Bool){1});
                    U64 _t3493 = 1;
                    (void)_t3493;
                    U64 _t3494 = U64_add(DEREF(ui), _t3493);
                    (void)_t3494;
                    ;
                    *ui = _t3494;
                    ;
                }
                U64_delete(ui, &(Bool){1});
                I32 _t3495 = til_system(cmd);
                (void)_t3495;
                Str_delete(cmd, &(Bool){1});
                result = _t3495;
                ;
            }
            ;
            Str_delete(bin_path, &(Bool){1});
        } else {
            Str *_t3561 = Str_lit("ast", 3ULL);
            (void)_t3561;
            Bool _t3562; { Bool *_hp = (Bool *)Str_eq(command, _t3561); _t3562 = *_hp; free(_hp); }
            (void)_t3562;
            Str_delete(_t3561, &(Bool){1});
            if (_t3562) {
                Str *_t3545 = Str_lit("Str", 3ULL);
                (void)_t3545;
                U64 _t3546; { U64 *_hp = (U64 *)Str_size(); _t3546 = *_hp; free(_hp); }
                (void)_t3546;
                U64 _t3547 = 1;
                (void)_t3547;
                Array *_va80 = Array_new(_t3545, &(U64){_t3546}, &(U64){_t3547});
                (void)_va80;
                Str_delete(_t3545, &(Bool){1});
                ;
                ;
                Str *_t3548 = Str_lit("mode: ", 6ULL);
                (void)_t3548;
                U64 _t3549 = 0;
                (void)_t3549;
                Str *_t3550 = Str_concat(_t3548, &cur_mode->name);
                (void)_t3550;
                Str_delete(_t3548, &(Bool){1});
                Array_set(_va80, &(U64){_t3549}, _t3550);
                ;
                println(_va80);
                U32 _t3551 = 0;
                (void)_t3551;
                ast_print(ast, _t3551);
                ;
            } else {
                Str *_t3552 = Str_lit("Str", 3ULL);
                (void)_t3552;
                U64 _t3553; { U64 *_hp = (U64 *)Str_size(); _t3553 = *_hp; free(_hp); }
                (void)_t3553;
                U64 _t3554 = 1;
                (void)_t3554;
                Array *_va81 = Array_new(_t3552, &(U64){_t3553}, &(U64){_t3554});
                (void)_va81;
                Str_delete(_t3552, &(Bool){1});
                ;
                ;
                Str *_t3555 = Str_lit("error: unknown command '", 24ULL);
                (void)_t3555;
                Str *_t3556 = Str_concat(_t3555, command);
                (void)_t3556;
                Str_delete(_t3555, &(Bool){1});
                Str *_t3557 = Str_lit("'", 1ULL);
                (void)_t3557;
                U64 _t3558 = 0;
                (void)_t3558;
                Str *_t3559 = Str_concat(_t3556, _t3557);
                (void)_t3559;
                Str_delete(_t3556, &(Bool){1});
                Str_delete(_t3557, &(Bool){1});
                Array_set(_va81, &(U64){_t3558}, _t3559);
                ;
                println(_va81);
                usage();
                I32 _t3560 = 1;
                (void)_t3560;
                result = _t3560;
                ;
            }
            ;
        }
        ;
    }
    ;
    Expr_delete(ast, &(Bool){1});
    Str_delete(command, &(Bool){1});
    Mode_delete(cur_mode, &(Bool){1});
    Str_delete(custom_bin, &(Bool){1});
    Str_delete(custom_c, &(Bool){1});
    Str_delete(ext_c_path, &(Bool){1});
    ;
    Str_delete(lflags, &(Bool){1});
    Str_delete(path, &(Bool){1});
    ;
    Vec_delete(user_argv, &(Bool){1});
    Str_delete(user_c, &(Bool){1});
    I64 _t3648 = I32_to_i64(result);
    (void)_t3648;
    ;
    exit(_t3648);
    ;
    return 0;
}

