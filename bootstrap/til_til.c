#include "til_til.h"

Mode * Mode_clone(Mode * self) {
    (void)self;
    Mode *_t3042 = malloc(sizeof(Mode));
    (void)_t3042;
    return _t3042;
}

U64 *Mode_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Mode);
    return r;
}

TypeScope * TypeScope_clone(TypeScope * self) {
    (void)self;
    TypeScope *_t3044 = malloc(sizeof(TypeScope));
    (void)_t3044;
    return _t3044;
}

U64 *TypeScope_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TypeScope);
    return r;
}

Vec * extract_imports(void * body) {
    (void)body;
    Str *_t3075 = Str_lit("Str", 3ULL);
    (void)_t3075;
    U64 _t3076; { U64 *_hp = (U64 *)Str_size(); _t3076 = *_hp; free(_hp); }
    (void)_t3076;
    Vec *paths = Vec_new(_t3075, &(U64){_t3076});
    (void)paths;
    Str_delete(_t3075, &(Bool){1});
    ;
    Vec *kept = expr_vec_new();
    (void)kept;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t3050 = expr_nchildren(body);
        (void)_t3050;
        Bool _wcond3046; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3050}); _wcond3046 = *_hp; free(_hp); }
        (void)_wcond3046;
        ;
        if (_wcond3046) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(body, DEREF(i));
        (void)stmt;
        I32 _t3051 = expr_get_tag(stmt);
        (void)_t3051;
        U32 _t3052 = expr_nchildren(stmt);
        (void)_t3052;
        U32 _t3053 = 2;
        (void)_t3053;
        Bool _t3054 = I32_eq(_t3051, DEREF(NODE_FCALL));
        (void)_t3054;
        ;
        Bool _t3055 = U32_eq(_t3052, _t3053);
        (void)_t3055;
        ;
        ;
        U32 *_t3056 = malloc(sizeof(U32));
        *_t3056 = 0;
        (void)_t3056;
        Expr *_t3057 = expr_get_child(stmt, DEREF(_t3056));
        (void)_t3057;
        I32 _t3058 = expr_get_tag(_t3057);
        (void)_t3058;
        U32_delete(_t3056, &(Bool){1});
        Bool _t3059 = Bool_and(_t3054, _t3055);
        (void)_t3059;
        ;
        ;
        Bool _t3060 = I32_eq(_t3058, DEREF(NODE_IDENT));
        (void)_t3060;
        ;
        U32 *_t3061 = malloc(sizeof(U32));
        *_t3061 = 0;
        (void)_t3061;
        Expr *_t3062 = expr_get_child(stmt, DEREF(_t3061));
        (void)_t3062;
        Str *_t3063 = expr_get_str_val(_t3062);
        (void)_t3063;
        Str *_t3064 = Str_lit("import", 6ULL);
        (void)_t3064;
        Bool _t3065 = Bool_and(_t3059, _t3060);
        (void)_t3065;
        ;
        ;
        Bool _t3066; { Bool *_hp = (Bool *)Str_eq(_t3063, _t3064); _t3066 = *_hp; free(_hp); }
        (void)_t3066;
        U32_delete(_t3061, &(Bool){1});
        Str_delete(_t3064, &(Bool){1});
        U32 *_t3067 = malloc(sizeof(U32));
        *_t3067 = 1;
        (void)_t3067;
        Expr *_t3068 = expr_get_child(stmt, DEREF(_t3067));
        (void)_t3068;
        I32 _t3069 = expr_get_tag(_t3068);
        (void)_t3069;
        U32_delete(_t3067, &(Bool){1});
        Bool _t3070 = Bool_and(_t3065, _t3066);
        (void)_t3070;
        ;
        ;
        Bool _t3071 = I32_eq(_t3069, DEREF(NODE_LITERAL_STR));
        (void)_t3071;
        ;
        Bool _t3072 = Bool_and(_t3070, _t3071);
        (void)_t3072;
        ;
        ;
        if (_t3072) {
            U32 *_t3047 = malloc(sizeof(U32));
            *_t3047 = 1;
            (void)_t3047;
            Expr *_t3048 = expr_get_child(stmt, DEREF(_t3047));
            (void)_t3048;
            Str *path = expr_get_str_val(_t3048);
            (void)path;
            Str *_t3049 = Str_clone(path);
            (void)_t3049;
            U32_delete(_t3047, &(Bool){1});
            Vec_push(paths, _t3049);
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t3073 = 1;
        (void)_t3073;
        U32 _t3074 = U32_add(DEREF(i), _t3073);
        (void)_t3074;
        ;
        *i = _t3074;
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
        U64 _fi3077 = 0;
        (void)_fi3077;
        while (1) {
            U64 _t3107 = 0;
            (void)_t3107;
            U64 _t3108; { U64 *_hp = (U64 *)Vec_len(import_paths); _t3108 = *_hp; free(_hp); }
            (void)_t3108;
            Range *_t3109 = Range_new(_t3107, _t3108);
            (void)_t3109;
            ;
            ;
            U64 _t3110; { U64 *_hp = (U64 *)Range_len(_t3109); _t3110 = *_hp; free(_hp); }
            (void)_t3110;
            Range_delete(_t3109, &(Bool){1});
            Bool _wcond3078; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3077}, &(U64){_t3110}); _wcond3078 = *_hp; free(_hp); }
            (void)_wcond3078;
            ;
            if (_wcond3078) {
            } else {
                ;
                break;
            }
            ;
            U64 _t3111 = 0;
            (void)_t3111;
            U64 _t3112; { U64 *_hp = (U64 *)Vec_len(import_paths); _t3112 = *_hp; free(_hp); }
            (void)_t3112;
            Range *_t3113 = Range_new(_t3111, _t3112);
            (void)_t3113;
            ;
            ;
            U64 *i = Range_get(_t3113, _fi3077);
            (void)i;
            Range_delete(_t3113, &(Bool){1});
            U64 _t3114 = 1;
            (void)_t3114;
            U64 _t3115 = U64_add(_fi3077, _t3114);
            (void)_t3115;
            ;
            _fi3077 = _t3115;
            ;
            Str *import_path = Vec_get(import_paths, i);
            (void)import_path;
            Str *_t3116 = Str_lit("/", 1ULL);
            (void)_t3116;
            Str *_t3117 = Str_concat(base_dir, _t3116);
            (void)_t3117;
            Str_delete(_t3116, &(Bool){1});
            Str *try_path = Str_concat(_t3117, import_path);
            (void)try_path;
            Str_delete(_t3117, &(Bool){1});
            Str *abs = til_realpath(try_path);
            (void)abs;
            Str *_t3118 = Str_lit("", 0ULL);
            (void)_t3118;
            U64 _t3119; { U64 *_hp = (U64 *)Str_len(lib_dir); _t3119 = *_hp; free(_hp); }
            (void)_t3119;
            U64 _t3120 = 0;
            (void)_t3120;
            Bool _t3121; { Bool *_hp = (Bool *)Str_eq(abs, _t3118); _t3121 = *_hp; free(_hp); }
            (void)_t3121;
            Str_delete(_t3118, &(Bool){1});
            Bool _t3122; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3119}, &(U64){_t3120}); _t3122 = *_hp; free(_hp); }
            (void)_t3122;
            ;
            ;
            Bool _t3123 = Bool_and(_t3121, _t3122);
            (void)_t3123;
            ;
            ;
            if (_t3123) {
                Str *_t3079 = Str_lit("/", 1ULL);
                (void)_t3079;
                Str *_t3080 = Str_concat(lib_dir, _t3079);
                (void)_t3080;
                Str_delete(_t3079, &(Bool){1});
                try_path = Str_concat(_t3080, import_path);
                Str_delete(_t3080, &(Bool){1});
                abs = til_realpath(try_path);
            }
            ;
            Str_delete(try_path, &(Bool){1});
            Str *_t3124 = Str_lit("", 0ULL);
            (void)_t3124;
            Bool _t3125; { Bool *_hp = (Bool *)Str_eq(abs, _t3124); _t3125 = *_hp; free(_hp); }
            (void)_t3125;
            Str_delete(_t3124, &(Bool){1});
            if (_t3125) {
                Str *_t3081 = Str_lit("Str", 3ULL);
                (void)_t3081;
                U64 _t3082; { U64 *_hp = (U64 *)Str_size(); _t3082 = *_hp; free(_hp); }
                (void)_t3082;
                U64 _t3083 = 1;
                (void)_t3083;
                Array *_va54 = Array_new(_t3081, &(U64){_t3082}, &(U64){_t3083});
                (void)_va54;
                Str_delete(_t3081, &(Bool){1});
                ;
                ;
                Str *_t3084 = Str_lit("error: could not find import '", 30ULL);
                (void)_t3084;
                Str *_t3085 = Str_concat(_t3084, import_path);
                (void)_t3085;
                Str_delete(_t3084, &(Bool){1});
                Str *_t3086 = Str_lit("' (from ", 8ULL);
                (void)_t3086;
                Str *_t3087 = Str_concat(_t3085, _t3086);
                (void)_t3087;
                Str_delete(_t3085, &(Bool){1});
                Str_delete(_t3086, &(Bool){1});
                Str *_t3088 = Str_concat(_t3087, base_dir);
                (void)_t3088;
                Str_delete(_t3087, &(Bool){1});
                Str *_t3089 = Str_lit("/)", 2ULL);
                (void)_t3089;
                U64 _t3090 = 0;
                (void)_t3090;
                Str *_t3091 = Str_concat(_t3088, _t3089);
                (void)_t3091;
                Str_delete(_t3088, &(Bool){1});
                Str_delete(_t3089, &(Bool){1});
                Array_set(_va54, &(U64){_t3090}, _t3091);
                ;
                println(_va54);
                I64 _t3092 = 1;
                (void)_t3092;
                ;
                Str_delete(abs, &(Bool){1});
                U64_delete(i, &(Bool){1});
                ;
                { I32 *_r = malloc(sizeof(I32)); *_r = _t3092; return _r; }
            }
            ;
            U64_delete(i, &(Bool){1});
            Bool _t3126 = til_set_has(resolved_set, abs);
            (void)_t3126;
            if (_t3126) {
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
            U64 _t3127; { U64 *_hp = (U64 *)Str_len(abs); _t3127 = *_hp; free(_hp); }
            (void)_t3127;
            U64 _t3128 = 1;
            (void)_t3128;
            U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t3127, _t3128);
            (void)last_slash;
            ;
            ;
            while (1) {
                U64 _t3094 = 0;
                (void)_t3094;
                U8 *_t3095 = Str_get(abs, last_slash);
                (void)_t3095;
                U8 _t3096 = 47;
                (void)_t3096;
                Bool _t3097; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t3094}); _t3097 = *_hp; free(_hp); }
                (void)_t3097;
                ;
                Bool _t3098; { Bool *_hp = (Bool *)U8_neq(_t3095, &(U8){_t3096}); _t3098 = *_hp; free(_hp); }
                (void)_t3098;
                ;
                Bool _wcond3093 = Bool_and(_t3097, _t3098);
                (void)_wcond3093;
                ;
                ;
                if (_wcond3093) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t3099 = 1;
                (void)_t3099;
                U64 _t3100 = U64_sub(DEREF(last_slash), _t3099);
                (void)_t3100;
                ;
                *last_slash = _t3100;
                ;
            }
            Str *sub_dir = til_str_left(abs, DEREF(last_slash));
            (void)sub_dir;
            Str_delete(abs, &(Bool){1});
            U64_delete(last_slash, &(Bool){1});
            U64 _t3129; { U64 *_hp = (U64 *)Vec_len(sub_imports); _t3129 = *_hp; free(_hp); }
            (void)_t3129;
            U64 _t3130 = 0;
            (void)_t3130;
            Bool _t3131; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3129}, &(U64){_t3130}); _t3131 = *_hp; free(_hp); }
            (void)_t3131;
            ;
            ;
            if (_t3131) {
                I32 err; { I32 *_hp = (I32 *)resolve_imports(sub_imports, sub_dir, resolved_set, stack, merged, lib_dir); err = *_hp; free(_hp); }
                (void)err;
                I32 _t3101 = 0;
                (void)_t3101;
                Bool _t3102; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t3101}); _t3102 = *_hp; free(_hp); }
                (void)_t3102;
                ;
                if (_t3102) {
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
                U32 _t3104 = expr_nchildren(sub_ast);
                (void)_t3104;
                Bool _wcond3103; { Bool *_hp = (Bool *)U32_lt(k, &(U32){_t3104}); _wcond3103 = *_hp; free(_hp); }
                (void)_wcond3103;
                ;
                if (_wcond3103) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *ch = expr_get_child(sub_ast, DEREF(k));
                (void)ch;
                expr_vec_push(merged, ch);
                U32 _t3105 = 1;
                (void)_t3105;
                U32 _t3106 = U32_add(DEREF(k), _t3105);
                (void)_t3106;
                ;
                *k = _t3106;
                ;
            }
            U32_delete(k, &(Bool){1});
            Expr_delete(sub_ast, &(Bool){1});
        }
        ;
    }
    I64 _t3132 = 0;
    (void)_t3132;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t3132; return _r; }
}

void usage(void) {
    Str *_t3133 = Str_lit("Str", 3ULL);
    (void)_t3133;
    U64 _t3134; { U64 *_hp = (U64 *)Str_size(); _t3134 = *_hp; free(_hp); }
    (void)_t3134;
    U64 _t3135 = 1;
    (void)_t3135;
    Array *_va55 = Array_new(_t3133, &(U64){_t3134}, &(U64){_t3135});
    (void)_va55;
    Str_delete(_t3133, &(Bool){1});
    ;
    ;
    U64 _t3136 = 0;
    (void)_t3136;
    Str *_t3137 = Str_lit("Usage: til <command> <path>", 27ULL);
    (void)_t3137;
    Array_set(_va55, &(U64){_t3136}, _t3137);
    ;
    println(_va55);
    Str *_t3138 = Str_lit("Str", 3ULL);
    (void)_t3138;
    U64 _t3139; { U64 *_hp = (U64 *)Str_size(); _t3139 = *_hp; free(_hp); }
    (void)_t3139;
    U64 _t3140 = 1;
    (void)_t3140;
    Array *_va56 = Array_new(_t3138, &(U64){_t3139}, &(U64){_t3140});
    (void)_va56;
    Str_delete(_t3138, &(Bool){1});
    ;
    ;
    U64 _t3141 = 0;
    (void)_t3141;
    Str *_t3142 = Str_lit("", 0ULL);
    (void)_t3142;
    Array_set(_va56, &(U64){_t3141}, _t3142);
    ;
    println(_va56);
    Str *_t3143 = Str_lit("Str", 3ULL);
    (void)_t3143;
    U64 _t3144; { U64 *_hp = (U64 *)Str_size(); _t3144 = *_hp; free(_hp); }
    (void)_t3144;
    U64 _t3145 = 1;
    (void)_t3145;
    Array *_va57 = Array_new(_t3143, &(U64){_t3144}, &(U64){_t3145});
    (void)_va57;
    Str_delete(_t3143, &(Bool){1});
    ;
    ;
    U64 _t3146 = 0;
    (void)_t3146;
    Str *_t3147 = Str_lit("Commands:", 9ULL);
    (void)_t3147;
    Array_set(_va57, &(U64){_t3146}, _t3147);
    ;
    println(_va57);
    Str *_t3148 = Str_lit("Str", 3ULL);
    (void)_t3148;
    U64 _t3149; { U64 *_hp = (U64 *)Str_size(); _t3149 = *_hp; free(_hp); }
    (void)_t3149;
    U64 _t3150 = 1;
    (void)_t3150;
    Array *_va58 = Array_new(_t3148, &(U64){_t3149}, &(U64){_t3150});
    (void)_va58;
    Str_delete(_t3148, &(Bool){1});
    ;
    ;
    U64 _t3151 = 0;
    (void)_t3151;
    Str *_t3152 = Str_lit("  interpret  Read and interpret a .til file", 43ULL);
    (void)_t3152;
    Array_set(_va58, &(U64){_t3151}, _t3152);
    ;
    println(_va58);
    Str *_t3153 = Str_lit("Str", 3ULL);
    (void)_t3153;
    U64 _t3154; { U64 *_hp = (U64 *)Str_size(); _t3154 = *_hp; free(_hp); }
    (void)_t3154;
    U64 _t3155 = 1;
    (void)_t3155;
    Array *_va59 = Array_new(_t3153, &(U64){_t3154}, &(U64){_t3155});
    (void)_va59;
    Str_delete(_t3153, &(Bool){1});
    ;
    ;
    U64 _t3156 = 0;
    (void)_t3156;
    Str *_t3157 = Str_lit("  translate  Generate C source (no compilation)", 47ULL);
    (void)_t3157;
    Array_set(_va59, &(U64){_t3156}, _t3157);
    ;
    println(_va59);
    Str *_t3158 = Str_lit("Str", 3ULL);
    (void)_t3158;
    U64 _t3159; { U64 *_hp = (U64 *)Str_size(); _t3159 = *_hp; free(_hp); }
    (void)_t3159;
    U64 _t3160 = 1;
    (void)_t3160;
    Array *_va60 = Array_new(_t3158, &(U64){_t3159}, &(U64){_t3160});
    (void)_va60;
    Str_delete(_t3158, &(Bool){1});
    ;
    ;
    U64 _t3161 = 0;
    (void)_t3161;
    Str *_t3162 = Str_lit("  build      Compile a .til file to a binary", 44ULL);
    (void)_t3162;
    Array_set(_va60, &(U64){_t3161}, _t3162);
    ;
    println(_va60);
    Str *_t3163 = Str_lit("Str", 3ULL);
    (void)_t3163;
    U64 _t3164; { U64 *_hp = (U64 *)Str_size(); _t3164 = *_hp; free(_hp); }
    (void)_t3164;
    U64 _t3165 = 1;
    (void)_t3165;
    Array *_va61 = Array_new(_t3163, &(U64){_t3164}, &(U64){_t3165});
    (void)_va61;
    Str_delete(_t3163, &(Bool){1});
    ;
    ;
    U64 _t3166 = 0;
    (void)_t3166;
    Str *_t3167 = Str_lit("  run        Compile and run a .til file", 40ULL);
    (void)_t3167;
    Array_set(_va61, &(U64){_t3166}, _t3167);
    ;
    println(_va61);
    Str *_t3168 = Str_lit("Str", 3ULL);
    (void)_t3168;
    U64 _t3169; { U64 *_hp = (U64 *)Str_size(); _t3169 = *_hp; free(_hp); }
    (void)_t3169;
    U64 _t3170 = 1;
    (void)_t3170;
    Array *_va62 = Array_new(_t3168, &(U64){_t3169}, &(U64){_t3170});
    (void)_va62;
    Str_delete(_t3168, &(Bool){1});
    ;
    ;
    U64 _t3171 = 0;
    (void)_t3171;
    Str *_t3172 = Str_lit("  test       Run test functions in a .til file", 46ULL);
    (void)_t3172;
    Array_set(_va62, &(U64){_t3171}, _t3172);
    ;
    println(_va62);
    Str *_t3173 = Str_lit("Str", 3ULL);
    (void)_t3173;
    U64 _t3174; { U64 *_hp = (U64 *)Str_size(); _t3174 = *_hp; free(_hp); }
    (void)_t3174;
    U64 _t3175 = 1;
    (void)_t3175;
    Array *_va63 = Array_new(_t3173, &(U64){_t3174}, &(U64){_t3175});
    (void)_va63;
    Str_delete(_t3173, &(Bool){1});
    ;
    ;
    U64 _t3176 = 0;
    (void)_t3176;
    Str *_t3177 = Str_lit("  help       Print this message", 31ULL);
    (void)_t3177;
    Array_set(_va63, &(U64){_t3176}, _t3177);
    ;
    println(_va63);
}

void mark_core(void * e) {
    (void)e;
    expr_set_core(e);
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t3179 = expr_nchildren(e);
        (void)_t3179;
        Bool _wcond3178; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3179}); _wcond3178 = *_hp; free(_hp); }
        (void)_wcond3178;
        ;
        if (_wcond3178) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t3180 = expr_get_child(e, DEREF(i));
        (void)_t3180;
        mark_core(_t3180);
        U32 _t3181 = 1;
        (void)_t3181;
        U32 _t3182 = U32_add(DEREF(i), _t3181);
        (void)_t3182;
        ;
        *i = _t3182;
        ;
    }
    U32_delete(i, &(Bool){1});
}

int main(int argc, char **argv) {
    if (argc - 1 < 0) { fprintf(stderr, "error: main expects at least 0 argument(s), got %d\n", argc - 1); return 1; }
    _t3647 = malloc(sizeof(I64));
    *_t3647 = 0;
    (void)_t3647;
    _t3648 = malloc(sizeof(I64));
    *_t3648 = 1;
    (void)_t3648;
    _t3649 = malloc(sizeof(I64)); *_t3649 = I64_sub(DEREF(_t3647), DEREF(_t3648));
    (void)_t3649;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t3649));
    (void)CAP_LIT;
    _t3650 = malloc(sizeof(I64));
    *_t3650 = 0;
    (void)_t3650;
    _t3651 = malloc(sizeof(I64));
    *_t3651 = 2;
    (void)_t3651;
    _t3652 = malloc(sizeof(I64)); *_t3652 = I64_sub(DEREF(_t3650), DEREF(_t3651));
    (void)_t3652;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t3652));
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
    U64 _t3568; { U64 *_hp = (U64 *)Array_len(args); _t3568 = *_hp; free(_hp); }
    (void)_t3568;
    U64 _t3569 = 0;
    (void)_t3569;
    Bool _t3570 = U64_eq(_t3568, _t3569);
    (void)_t3570;
    ;
    ;
    if (_t3570) {
        usage();
        Str *_t3183 = Str_lit("Str", 3ULL);
        (void)_t3183;
        U64 _t3184; { U64 *_hp = (U64 *)Str_size(); _t3184 = *_hp; free(_hp); }
        (void)_t3184;
        U64 _t3185 = 1;
        (void)_t3185;
        Array *_va64 = Array_new(_t3183, &(U64){_t3184}, &(U64){_t3185});
        (void)_va64;
        Str_delete(_t3183, &(Bool){1});
        ;
        ;
        U64 _t3186 = 0;
        (void)_t3186;
        Str *_t3187 = Str_lit("no arguments", 12ULL);
        (void)_t3187;
        Array_set(_va64, &(U64){_t3186}, _t3187);
        ;
        Str *_t3188 = Str_lit("src/til.til:231:15", 18ULL);
        (void)_t3188;
        panic(_t3188, _va64);
        Str_delete(_t3188, &(Bool){1});
    }
    ;
    U64 *_t3571 = malloc(sizeof(U64));
    *_t3571 = 0;
    (void)_t3571;
    Str *cmd_ref = Array_get(args, _t3571);
    (void)cmd_ref;
    Str *command = Str_clone(cmd_ref);
    (void)command;
    U64_delete(_t3571, &(Bool){1});
    Str *path = Str_lit("", 0ULL);
    (void)path;
    Str *custom_bin = Str_lit("", 0ULL);
    (void)custom_bin;
    Str *custom_c = Str_lit("", 0ULL);
    (void)custom_c;
    U64 *path_idx = malloc(sizeof(U64));
    *path_idx = 1;
    (void)path_idx;
    U64 _t3572; { U64 *_hp = (U64 *)Array_len(args); _t3572 = *_hp; free(_hp); }
    (void)_t3572;
    U64 _t3573 = 1;
    (void)_t3573;
    Bool _t3574 = U64_eq(_t3572, _t3573);
    (void)_t3574;
    ;
    ;
    if (_t3574) {
        Str *_t3189 = Str_lit("help", 4ULL);
        (void)_t3189;
        Str *_t3190 = Str_lit("--help", 6ULL);
        (void)_t3190;
        Bool _t3191; { Bool *_hp = (Bool *)Str_eq(command, _t3189); _t3191 = *_hp; free(_hp); }
        (void)_t3191;
        Str_delete(_t3189, &(Bool){1});
        Bool _t3192; { Bool *_hp = (Bool *)Str_eq(command, _t3190); _t3192 = *_hp; free(_hp); }
        (void)_t3192;
        Str_delete(_t3190, &(Bool){1});
        Bool _t3193 = Bool_or(_t3191, _t3192);
        (void)_t3193;
        ;
        ;
        if (_t3193) {
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
            U64 _t3210; { U64 *_hp = (U64 *)Array_len(args); _t3210 = *_hp; free(_hp); }
            (void)_t3210;
            Bool _wcond3194; { Bool *_hp = (Bool *)U64_lt(path_idx, &(U64){_t3210}); _wcond3194 = *_hp; free(_hp); }
            (void)_wcond3194;
            ;
            if (_wcond3194) {
            } else {
                ;
                break;
            }
            ;
            Str *flag = Array_get(args, path_idx);
            (void)flag;
            Str *_t3211 = Str_lit("-o", 2ULL);
            (void)_t3211;
            U64 _t3212 = 1;
            (void)_t3212;
            U64 _t3213 = U64_add(DEREF(path_idx), _t3212);
            (void)_t3213;
            ;
            U64 _t3214; { U64 *_hp = (U64 *)Array_len(args); _t3214 = *_hp; free(_hp); }
            (void)_t3214;
            Bool _t3215; { Bool *_hp = (Bool *)Str_eq(flag, _t3211); _t3215 = *_hp; free(_hp); }
            (void)_t3215;
            Str_delete(_t3211, &(Bool){1});
            Bool _t3216; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3213}, &(U64){_t3214}); _t3216 = *_hp; free(_hp); }
            (void)_t3216;
            ;
            ;
            Bool _t3217 = Bool_and(_t3215, _t3216);
            (void)_t3217;
            ;
            ;
            if (_t3217) {
                U64 _t3195 = 1;
                (void)_t3195;
                U64 *_t3196 = malloc(sizeof(U64)); *_t3196 = U64_add(DEREF(path_idx), _t3195);
                (void)_t3196;
                ;
                Str *oval = Array_get(args, _t3196);
                (void)oval;
                custom_bin = Str_clone(oval);
                U64_delete(_t3196, &(Bool){1});
                U64 _t3197 = 2;
                (void)_t3197;
                U64 _t3198 = U64_add(DEREF(path_idx), _t3197);
                (void)_t3198;
                ;
                *path_idx = _t3198;
                ;
            } else {
                Str *_t3203 = Str_lit("-c", 2ULL);
                (void)_t3203;
                U64 _t3204 = 1;
                (void)_t3204;
                U64 _t3205 = U64_add(DEREF(path_idx), _t3204);
                (void)_t3205;
                ;
                U64 _t3206; { U64 *_hp = (U64 *)Array_len(args); _t3206 = *_hp; free(_hp); }
                (void)_t3206;
                Bool _t3207; { Bool *_hp = (Bool *)Str_eq(flag, _t3203); _t3207 = *_hp; free(_hp); }
                (void)_t3207;
                Str_delete(_t3203, &(Bool){1});
                Bool _t3208; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3205}, &(U64){_t3206}); _t3208 = *_hp; free(_hp); }
                (void)_t3208;
                ;
                ;
                Bool _t3209 = Bool_and(_t3207, _t3208);
                (void)_t3209;
                ;
                ;
                if (_t3209) {
                    U64 _t3199 = 1;
                    (void)_t3199;
                    U64 *_t3200 = malloc(sizeof(U64)); *_t3200 = U64_add(DEREF(path_idx), _t3199);
                    (void)_t3200;
                    ;
                    Str *cval = Array_get(args, _t3200);
                    (void)cval;
                    custom_c = Str_clone(cval);
                    U64_delete(_t3200, &(Bool){1});
                    U64 _t3201 = 2;
                    (void)_t3201;
                    U64 _t3202 = U64_add(DEREF(path_idx), _t3201);
                    (void)_t3202;
                    ;
                    *path_idx = _t3202;
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
    Str *_t3575 = Str_lit("help", 4ULL);
    (void)_t3575;
    Str *_t3576 = Str_lit("--help", 6ULL);
    (void)_t3576;
    Bool _t3577; { Bool *_hp = (Bool *)Str_eq(command, _t3575); _t3577 = *_hp; free(_hp); }
    (void)_t3577;
    Str_delete(_t3575, &(Bool){1});
    Bool _t3578; { Bool *_hp = (Bool *)Str_eq(command, _t3576); _t3578 = *_hp; free(_hp); }
    (void)_t3578;
    Str_delete(_t3576, &(Bool){1});
    Bool _t3579 = Bool_or(_t3577, _t3578);
    (void)_t3579;
    ;
    ;
    if (_t3579) {
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
    Str *_t3580 = Str_lit("/src/core/core.til", 18ULL);
    (void)_t3580;
    Str *core_path = Str_concat(bin_dir, _t3580);
    (void)core_path;
    Str_delete(_t3580, &(Bool){1});
    Str *_t3581 = Str_lit("/src/c/ext.c", 12ULL);
    (void)_t3581;
    Str *ext_c_path = Str_concat(bin_dir, _t3581);
    (void)ext_c_path;
    Str_delete(_t3581, &(Bool){1});
    Set *resolved = til_set_new();
    (void)resolved;
    Vec *resolve_stack = expr_vec_new();
    (void)resolve_stack;
    Str *abs_path = til_realpath(path);
    (void)abs_path;
    Str *user_dir = Str_lit(".", 1ULL);
    (void)user_dir;
    U64 _t3582; { U64 *_hp = (U64 *)Str_len(abs_path); _t3582 = *_hp; free(_hp); }
    (void)_t3582;
    U64 _t3583 = 0;
    (void)_t3583;
    Bool _t3584; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3582}, &(U64){_t3583}); _t3584 = *_hp; free(_hp); }
    (void)_t3584;
    ;
    ;
    if (_t3584) {
        U64 _t3226; { U64 *_hp = (U64 *)Str_len(abs_path); _t3226 = *_hp; free(_hp); }
        (void)_t3226;
        U64 _t3227 = 1;
        (void)_t3227;
        U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t3226, _t3227);
        (void)last_slash;
        ;
        ;
        while (1) {
            U64 _t3219 = 0;
            (void)_t3219;
            U8 *_t3220 = Str_get(abs_path, last_slash);
            (void)_t3220;
            U8 _t3221 = 47;
            (void)_t3221;
            Bool _t3222; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t3219}); _t3222 = *_hp; free(_hp); }
            (void)_t3222;
            ;
            Bool _t3223; { Bool *_hp = (Bool *)U8_neq(_t3220, &(U8){_t3221}); _t3223 = *_hp; free(_hp); }
            (void)_t3223;
            ;
            Bool _wcond3218 = Bool_and(_t3222, _t3223);
            (void)_wcond3218;
            ;
            ;
            if (_wcond3218) {
            } else {
                ;
                break;
            }
            ;
            U64 _t3224 = 1;
            (void)_t3224;
            U64 _t3225 = U64_sub(DEREF(last_slash), _t3224);
            (void)_t3225;
            ;
            *last_slash = _t3225;
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
    U64 _t3585; { U64 *_hp = (U64 *)Str_len(core_abs); _t3585 = *_hp; free(_hp); }
    (void)_t3585;
    U64 _t3586 = 0;
    (void)_t3586;
    Bool _t3587; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3585}, &(U64){_t3586}); _t3587 = *_hp; free(_hp); }
    (void)_t3587;
    ;
    ;
    if (_t3587) {
        Bool _t3229 = til_set_has(resolved, core_abs);
        (void)_t3229;
        if (_t3229) {
            Bool _t3228 = 1;
            (void)_t3228;
            skip_core = _t3228;
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
    U64 _t3588; { U64 *_hp = (U64 *)Vec_len(core_imports); _t3588 = *_hp; free(_hp); }
    (void)_t3588;
    U64 _t3589 = 0;
    (void)_t3589;
    Bool _t3590; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3588}, &(U64){_t3589}); _t3590 = *_hp; free(_hp); }
    (void)_t3590;
    ;
    ;
    Bool _t3591 = Bool_not(skip_core);
    (void)_t3591;
    Bool _t3592 = Bool_and(_t3590, _t3591);
    (void)_t3592;
    ;
    ;
    if (_t3592) {
        Str *_t3236 = Str_lit("/src/core", 9ULL);
        (void)_t3236;
        Str *core_dir = Str_concat(bin_dir, _t3236);
        (void)core_dir;
        Str_delete(_t3236, &(Bool){1});
        Str *_t3237 = Str_lit("", 0ULL);
        (void)_t3237;
        I32 err; { I32 *_hp = (I32 *)resolve_imports(core_imports, core_dir, resolved, resolve_stack, core_import_decls, _t3237); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(_t3237, &(Bool){1});
        Str_delete(core_dir, &(Bool){1});
        I32 _t3238 = 0;
        (void)_t3238;
        Bool _t3239; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t3238}); _t3239 = *_hp; free(_hp); }
        (void)_t3239;
        ;
        ;
        if (_t3239) {
            Str *_t3230 = Str_lit("Str", 3ULL);
            (void)_t3230;
            U64 _t3231; { U64 *_hp = (U64 *)Str_size(); _t3231 = *_hp; free(_hp); }
            (void)_t3231;
            U64 _t3232 = 1;
            (void)_t3232;
            Array *_va65 = Array_new(_t3230, &(U64){_t3231}, &(U64){_t3232});
            (void)_va65;
            Str_delete(_t3230, &(Bool){1});
            ;
            ;
            U64 _t3233 = 0;
            (void)_t3233;
            Str *_t3234 = Str_lit("failed to resolve core imports", 30ULL);
            (void)_t3234;
            Array_set(_va65, &(U64){_t3233}, _t3234);
            ;
            Str *_t3235 = Str_lit("src/til.til:317:19", 18ULL);
            (void)_t3235;
            panic(_t3235, _va65);
            Str_delete(_t3235, &(Bool){1});
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
    Mode *cur_mode = til_mode_none();
    (void)cur_mode;
    U64 _t3593; { U64 *_hp = (U64 *)Str_len(mode_str); _t3593 = *_hp; free(_hp); }
    (void)_t3593;
    U64 _t3594 = 0;
    (void)_t3594;
    Bool _t3595; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3593}, &(U64){_t3594}); _t3595 = *_hp; free(_hp); }
    (void)_t3595;
    ;
    ;
    if (_t3595) {
        cur_mode = til_mode_resolve(mode_str);
        Mode *_t3249 = til_mode_none();
        (void)_t3249;
        Bool _t3250 = til_mode_eq(cur_mode, _t3249);
        (void)_t3250;
        Mode_delete(_t3249, &(Bool){1});
        if (_t3250) {
            Str *_t3240 = Str_lit("Str", 3ULL);
            (void)_t3240;
            U64 _t3241; { U64 *_hp = (U64 *)Str_size(); _t3241 = *_hp; free(_hp); }
            (void)_t3241;
            U64 _t3242 = 1;
            (void)_t3242;
            Array *_va66 = Array_new(_t3240, &(U64){_t3241}, &(U64){_t3242});
            (void)_va66;
            Str_delete(_t3240, &(Bool){1});
            ;
            ;
            Str *_t3243 = Str_lit("unknown mode '", 14ULL);
            (void)_t3243;
            Str *_t3244 = Str_concat(_t3243, mode_str);
            (void)_t3244;
            Str_delete(_t3243, &(Bool){1});
            Str *_t3245 = Str_lit("'", 1ULL);
            (void)_t3245;
            U64 _t3246 = 0;
            (void)_t3246;
            Str *_t3247 = Str_concat(_t3244, _t3245);
            (void)_t3247;
            Str_delete(_t3244, &(Bool){1});
            Str_delete(_t3245, &(Bool){1});
            Array_set(_va66, &(U64){_t3246}, _t3247);
            ;
            Str *_t3248 = Str_lit("src/til.til:333:19", 18ULL);
            (void)_t3248;
            panic(_t3248, _va66);
            Str_delete(_t3248, &(Bool){1});
        }
        ;
    }
    ;
    Str_delete(mode_str, &(Bool){1});
    Expr *mode_ast = expr_null();
    (void)mode_ast;
    Str *auto_import = til_mode_auto_import(cur_mode);
    (void)auto_import;
    U64 _t3596; { U64 *_hp = (U64 *)Str_len(auto_import); _t3596 = *_hp; free(_hp); }
    (void)_t3596;
    U64 _t3597 = 0;
    (void)_t3597;
    Bool _t3598; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3596}, &(U64){_t3597}); _t3598 = *_hp; free(_hp); }
    (void)_t3598;
    ;
    ;
    if (_t3598) {
        Str *_t3251 = Str_lit("/src/modes/", 11ULL);
        (void)_t3251;
        Str *_t3252 = Str_concat(bin_dir, _t3251);
        (void)_t3252;
        Str_delete(_t3251, &(Bool){1});
        Str *_t3253 = Str_concat(_t3252, auto_import);
        (void)_t3253;
        Str_delete(_t3252, &(Bool){1});
        Str *_t3254 = Str_lit(".til", 4ULL);
        (void)_t3254;
        Str *mode_til_path = Str_concat(_t3253, _t3254);
        (void)mode_til_path;
        Str_delete(_t3253, &(Bool){1});
        Str_delete(_t3254, &(Bool){1});
        Str *mode_source = readfile(mode_til_path);
        (void)mode_source;
        Vec *mode_tokens = tokenize(mode_source, mode_til_path);
        (void)mode_tokens;
        Str_delete(mode_source, &(Bool){1});
        mode_ast = til_parse(mode_tokens, mode_til_path);
        Str_delete(mode_til_path, &(Bool){1});
        Vec_delete(mode_tokens, &(Bool){1});
    }
    ;
    Str_delete(auto_import, &(Bool){1});
    Vec *import_decls = expr_vec_new();
    (void)import_decls;
    U64 _t3599; { U64 *_hp = (U64 *)Vec_len(imports); _t3599 = *_hp; free(_hp); }
    (void)_t3599;
    U64 _t3600 = 0;
    (void)_t3600;
    Bool _t3601; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3599}, &(U64){_t3600}); _t3601 = *_hp; free(_hp); }
    (void)_t3601;
    ;
    ;
    if (_t3601) {
        Str *_t3261 = Str_lit("/src/lib", 8ULL);
        (void)_t3261;
        Str *lib_dir = Str_concat(bin_dir, _t3261);
        (void)lib_dir;
        Str_delete(_t3261, &(Bool){1});
        I32 err; { I32 *_hp = (I32 *)resolve_imports(imports, user_dir, resolved, resolve_stack, import_decls, lib_dir); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(lib_dir, &(Bool){1});
        I32 _t3262 = 0;
        (void)_t3262;
        Bool _t3263; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t3262}); _t3263 = *_hp; free(_hp); }
        (void)_t3263;
        ;
        ;
        if (_t3263) {
            Str *_t3255 = Str_lit("Str", 3ULL);
            (void)_t3255;
            U64 _t3256; { U64 *_hp = (U64 *)Str_size(); _t3256 = *_hp; free(_hp); }
            (void)_t3256;
            U64 _t3257 = 1;
            (void)_t3257;
            Array *_va67 = Array_new(_t3255, &(U64){_t3256}, &(U64){_t3257});
            (void)_va67;
            Str_delete(_t3255, &(Bool){1});
            ;
            ;
            U64 _t3258 = 0;
            (void)_t3258;
            Str *_t3259 = Str_lit("failed to resolve imports", 25ULL);
            (void)_t3259;
            Array_set(_va67, &(U64){_t3258}, _t3259);
            ;
            Str *_t3260 = Str_lit("src/til.til:354:19", 18ULL);
            (void)_t3260;
            panic(_t3260, _va67);
            Str_delete(_t3260, &(Bool){1});
        }
        ;
    }
    ;
    Str_delete(bin_dir, &(Bool){1});
    Vec_delete(imports, &(Bool){1});
    Vec_delete(resolve_stack, &(Bool){1});
    Set_delete(resolved, &(Bool){1});
    Str_delete(user_dir, &(Bool){1});
    Vec *merged = expr_vec_new();
    (void)merged;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    Bool _t3602 = Bool_not(skip_core);
    (void)_t3602;
    ;
    if (_t3602) {
        while (1) {
            U32 _t3265 = expr_nchildren(core_ast);
            (void)_t3265;
            Bool _wcond3264; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3265}); _wcond3264 = *_hp; free(_hp); }
            (void)_wcond3264;
            ;
            if (_wcond3264) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(core_ast, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t3266 = 1;
            (void)_t3266;
            U32 _t3267 = U32_add(DEREF(i), _t3266);
            (void)_t3267;
            ;
            *i = _t3267;
            ;
        }
        U32 _t3272 = 0;
        (void)_t3272;
        *i = _t3272;
        ;
        while (1) {
            U32 _t3269 = expr_vec_count(core_import_decls);
            (void)_t3269;
            Bool _wcond3268; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3269}); _wcond3268 = *_hp; free(_hp); }
            (void)_wcond3268;
            ;
            if (_wcond3268) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_vec_get(core_import_decls, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t3270 = 1;
            (void)_t3270;
            U32 _t3271 = U32_add(DEREF(i), _t3270);
            (void)_t3271;
            ;
            *i = _t3271;
            ;
        }
    }
    ;
    Expr_delete(core_ast, &(Bool){1});
    Vec_delete(core_import_decls, &(Bool){1});
    Bool _t3603 = expr_is_null(mode_ast);
    (void)_t3603;
    Bool _t3604 = Bool_not(_t3603);
    (void)_t3604;
    ;
    if (_t3604) {
        U32 _t3277 = 0;
        (void)_t3277;
        *i = _t3277;
        ;
        while (1) {
            U32 _t3274 = expr_nchildren(mode_ast);
            (void)_t3274;
            Bool _wcond3273; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3274}); _wcond3273 = *_hp; free(_hp); }
            (void)_wcond3273;
            ;
            if (_wcond3273) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(mode_ast, DEREF(i));
            (void)ch;
            expr_vec_push(merged, ch);
            U32 _t3275 = 1;
            (void)_t3275;
            U32 _t3276 = U32_add(DEREF(i), _t3275);
            (void)_t3276;
            ;
            *i = _t3276;
            ;
        }
    }
    ;
    Expr_delete(mode_ast, &(Bool){1});
    U32 _t3605 = 0;
    (void)_t3605;
    *i = _t3605;
    ;
    while (1) {
        U32 _t3279 = expr_vec_count(import_decls);
        (void)_t3279;
        Bool _wcond3278; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3279}); _wcond3278 = *_hp; free(_hp); }
        (void)_wcond3278;
        ;
        if (_wcond3278) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_vec_get(import_decls, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t3280 = 1;
        (void)_t3280;
        U32 _t3281 = U32_add(DEREF(i), _t3280);
        (void)_t3281;
        ;
        *i = _t3281;
        ;
    }
    Vec_delete(import_decls, &(Bool){1});
    U32 _t3606 = 0;
    (void)_t3606;
    *i = _t3606;
    ;
    while (1) {
        U32 _t3283 = expr_nchildren(ast);
        (void)_t3283;
        Bool _wcond3282; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3283}); _wcond3282 = *_hp; free(_hp); }
        (void)_wcond3282;
        ;
        if (_wcond3282) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_get_child(ast, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t3284 = 1;
        (void)_t3284;
        U32 _t3285 = U32_add(DEREF(i), _t3284);
        (void)_t3285;
        ;
        *i = _t3285;
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
    U32 _t3607 = 0;
    (void)_t3607;
    *i = _t3607;
    ;
    while (1) {
        U32 _t3301 = expr_nchildren(ast);
        (void)_t3301;
        Bool _wcond3286; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3301}); _wcond3286 = *_hp; free(_hp); }
        (void)_wcond3286;
        ;
        if (_wcond3286) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(ast, DEREF(i));
        (void)stmt;
        I32 _t3302 = expr_get_tag(stmt);
        (void)_t3302;
        U32 _t3303 = expr_nchildren(stmt);
        (void)_t3303;
        U32 _t3304 = 2;
        (void)_t3304;
        Bool _t3305 = I32_eq(_t3302, DEREF(NODE_FCALL));
        (void)_t3305;
        ;
        Bool _t3306 = U32_eq(_t3303, _t3304);
        (void)_t3306;
        ;
        ;
        U32 *_t3307 = malloc(sizeof(U32));
        *_t3307 = 0;
        (void)_t3307;
        Expr *_t3308 = expr_get_child(stmt, DEREF(_t3307));
        (void)_t3308;
        I32 _t3309 = expr_get_tag(_t3308);
        (void)_t3309;
        U32_delete(_t3307, &(Bool){1});
        Bool _t3310 = Bool_and(_t3305, _t3306);
        (void)_t3310;
        ;
        ;
        Bool _t3311 = I32_eq(_t3309, DEREF(NODE_IDENT));
        (void)_t3311;
        ;
        U32 *_t3312 = malloc(sizeof(U32));
        *_t3312 = 1;
        (void)_t3312;
        Expr *_t3313 = expr_get_child(stmt, DEREF(_t3312));
        (void)_t3313;
        I32 _t3314 = expr_get_tag(_t3313);
        (void)_t3314;
        U32_delete(_t3312, &(Bool){1});
        Bool _t3315 = Bool_and(_t3310, _t3311);
        (void)_t3315;
        ;
        ;
        Bool _t3316 = I32_eq(_t3314, DEREF(NODE_LITERAL_STR));
        (void)_t3316;
        ;
        Bool _t3317 = Bool_and(_t3315, _t3316);
        (void)_t3317;
        ;
        ;
        if (_t3317) {
            U32 *_t3295 = malloc(sizeof(U32));
            *_t3295 = 0;
            (void)_t3295;
            Expr *_t3296 = expr_get_child(stmt, DEREF(_t3295));
            (void)_t3296;
            Str *fname = expr_get_str_val(_t3296);
            (void)fname;
            U32 *_t3297 = malloc(sizeof(U32));
            *_t3297 = 1;
            (void)_t3297;
            Expr *_t3298 = expr_get_child(stmt, DEREF(_t3297));
            (void)_t3298;
            Str *arg = expr_get_str_val(_t3298);
            (void)arg;
            Str *_t3299 = Str_lit("link", 4ULL);
            (void)_t3299;
            Bool _t3300; { Bool *_hp = (Bool *)Str_eq(fname, _t3299); _t3300 = *_hp; free(_hp); }
            (void)_t3300;
            Str_delete(_t3299, &(Bool){1});
            if (_t3300) {
                Str *_t3287 = Str_lit(" -l", 3ULL);
                (void)_t3287;
                Str *_t3288 = Str_concat(link_flags, _t3287);
                (void)_t3288;
                Str_delete(_t3287, &(Bool){1});
                link_flags = Str_concat(_t3288, arg);
                Str_delete(_t3288, &(Bool){1});
            } else {
                Str *_t3293 = Str_lit("link_c", 6ULL);
                (void)_t3293;
                Bool _t3294; { Bool *_hp = (Bool *)Str_eq(fname, _t3293); _t3294 = *_hp; free(_hp); }
                (void)_t3294;
                Str_delete(_t3293, &(Bool){1});
                if (_t3294) {
                    U64 _t3290; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t3290 = *_hp; free(_hp); }
                    (void)_t3290;
                    U64 _t3291 = 0;
                    (void)_t3291;
                    Bool _t3292; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3290}, &(U64){_t3291}); _t3292 = *_hp; free(_hp); }
                    (void)_t3292;
                    ;
                    ;
                    if (_t3292) {
                        Str *_t3289 = Str_lit(" ", 1ULL);
                        (void)_t3289;
                        link_c_paths = Str_concat(link_c_paths, _t3289);
                        Str_delete(_t3289, &(Bool){1});
                    }
                    ;
                    link_c_paths = Str_concat(link_c_paths, arg);
                } else {
                    expr_vec_push(kept, stmt);
                }
                ;
            }
            U32_delete(_t3295, &(Bool){1});
            U32_delete(_t3297, &(Bool){1});
            ;
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t3318 = 1;
        (void)_t3318;
        U32 _t3319 = U32_add(DEREF(i), _t3318);
        (void)_t3319;
        ;
        *i = _t3319;
        ;
    }
    U32_delete(i, &(Bool){1});
    expr_swap_children(ast, kept);
    Vec_delete(kept, &(Bool){1});
    TypeScope *scope = tscope_new(NULL);
    (void)scope;
    I32 _t3608 = init_declarations(ast, scope);
    (void)_t3608;
    ;
    I32 type_errors = type_check(ast, scope, cur_mode);
    (void)type_errors;
    TypeScope_delete(scope, &(Bool){1});
    I32 _t3609 = 0;
    (void)_t3609;
    Bool _t3610; { Bool *_hp = (Bool *)I32_gt(&(I32){type_errors}, &(I32){_t3609}); _t3610 = *_hp; free(_hp); }
    (void)_t3610;
    ;
    if (_t3610) {
        Str *_t3320 = Str_lit("Str", 3ULL);
        (void)_t3320;
        U64 _t3321; { U64 *_hp = (U64 *)Str_size(); _t3321 = *_hp; free(_hp); }
        (void)_t3321;
        U64 _t3322 = 1;
        (void)_t3322;
        Array *_va68 = Array_new(_t3320, &(U64){_t3321}, &(U64){_t3322});
        (void)_va68;
        Str_delete(_t3320, &(Bool){1});
        ;
        ;
        Str *_t3323 = I32_to_str(&(I32){type_errors});
        (void)_t3323;
        Str *_t3324 = Str_lit(" type error(s) found", 20ULL);
        (void)_t3324;
        U64 _t3325 = 0;
        (void)_t3325;
        Str *_t3326 = Str_concat(_t3323, _t3324);
        (void)_t3326;
        Str_delete(_t3323, &(Bool){1});
        Str_delete(_t3324, &(Bool){1});
        Array_set(_va68, &(U64){_t3325}, _t3326);
        ;
        Str *_t3327 = Str_lit("src/til.til:445:15", 18ULL);
        (void)_t3327;
        panic(_t3327, _va68);
        Str_delete(_t3327, &(Bool){1});
    }
    ;
    ;
    Str *_t3611 = Str_lit("test", 4ULL);
    (void)_t3611;
    Mode *_t3612 = til_mode_test();
    (void)_t3612;
    Bool _t3613; { Bool *_hp = (Bool *)Str_eq(command, _t3611); _t3613 = *_hp; free(_hp); }
    (void)_t3613;
    Str_delete(_t3611, &(Bool){1});
    Bool _t3614 = til_mode_eq(cur_mode, _t3612);
    (void)_t3614;
    Mode_delete(_t3612, &(Bool){1});
    Mode *_t3615 = til_mode_pure();
    (void)_t3615;
    Bool _t3616 = Bool_or(_t3613, _t3614);
    (void)_t3616;
    ;
    ;
    Bool _t3617 = til_mode_eq(cur_mode, _t3615);
    (void)_t3617;
    Mode_delete(_t3615, &(Bool){1});
    Mode *_t3618 = til_mode_pura();
    (void)_t3618;
    Bool _t3619 = Bool_or(_t3616, _t3617);
    (void)_t3619;
    ;
    ;
    Bool _t3620 = til_mode_eq(cur_mode, _t3618);
    (void)_t3620;
    Mode_delete(_t3618, &(Bool){1});
    Bool run_tests = Bool_or(_t3619, _t3620);
    (void)run_tests;
    ;
    ;
    precomp(ast);
    Str *_t3621 = Str_lit("translate", 9ULL);
    (void)_t3621;
    Str *_t3622 = Str_lit("build", 5ULL);
    (void)_t3622;
    Bool _t3623; { Bool *_hp = (Bool *)Str_eq(command, _t3621); _t3623 = *_hp; free(_hp); }
    (void)_t3623;
    Str_delete(_t3621, &(Bool){1});
    Bool _t3624; { Bool *_hp = (Bool *)Str_eq(command, _t3622); _t3624 = *_hp; free(_hp); }
    (void)_t3624;
    Str_delete(_t3622, &(Bool){1});
    Bool _t3625 = til_mode_is_lib_output(cur_mode);
    (void)_t3625;
    Bool _t3626 = Bool_or(_t3623, _t3624);
    (void)_t3626;
    ;
    ;
    Bool is_lib_target = Bool_and(_t3625, _t3626);
    (void)is_lib_target;
    ;
    ;
    U64 _t3627; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t3627 = *_hp; free(_hp); }
    (void)_t3627;
    U64 _t3628 = 0;
    (void)_t3628;
    Bool _t3629 = Bool_not(is_lib_target);
    (void)_t3629;
    ;
    Bool _t3630 = U64_eq(_t3627, _t3628);
    (void)_t3630;
    ;
    ;
    Bool _t3631 = Bool_and(_t3629, _t3630);
    (void)_t3631;
    ;
    ;
    if (_t3631) {
        scavenge(ast, cur_mode, run_tests);
    }
    ;
    I32 result = 0;
    (void)result;
    Str *user_c = Str_lit("", 0ULL);
    (void)user_c;
    U64 _t3632; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t3632 = *_hp; free(_hp); }
    (void)_t3632;
    U64 _t3633 = 0;
    (void)_t3633;
    Bool _t3634; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3632}, &(U64){_t3633}); _t3634 = *_hp; free(_hp); }
    (void)_t3634;
    ;
    ;
    if (_t3634) {
        user_c = Str_clone(link_c_paths);
    }
    ;
    Str_delete(link_c_paths, &(Bool){1});
    Str *_t3635 = Str_lit("Str", 3ULL);
    (void)_t3635;
    U64 _t3636; { U64 *_hp = (U64 *)Str_size(); _t3636 = *_hp; free(_hp); }
    (void)_t3636;
    Vec *user_argv = Vec_new(_t3635, &(U64){_t3636});
    (void)user_argv;
    Str_delete(_t3635, &(Bool){1});
    ;
    U64 _t3637 = 1;
    (void)_t3637;
    U64 *ai = malloc(sizeof(U64)); *ai = U64_add(DEREF(path_idx), _t3637);
    (void)ai;
    ;
    U64_delete(path_idx, &(Bool){1});
    while (1) {
        U64 _t3344; { U64 *_hp = (U64 *)Array_len(args); _t3344 = *_hp; free(_hp); }
        (void)_t3344;
        Bool _wcond3328; { Bool *_hp = (Bool *)U64_lt(ai, &(U64){_t3344}); _wcond3328 = *_hp; free(_hp); }
        (void)_wcond3328;
        ;
        if (_wcond3328) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, ai);
        (void)arg;
        Str *_t3345 = Str_lit("-l", 2ULL);
        (void)_t3345;
        Bool _t3346; { Bool *_hp = (Bool *)Str_starts_with(arg, _t3345); _t3346 = *_hp; free(_hp); }
        (void)_t3346;
        Str_delete(_t3345, &(Bool){1});
        if (_t3346) {
            U64 _t3331 = 2;
            (void)_t3331;
            U64 _t3332; { U64 *_hp = (U64 *)Str_len(arg); _t3332 = *_hp; free(_hp); }
            (void)_t3332;
            Str *lib = Str_substr(arg, &(U64){_t3331}, &(U64){_t3332});
            (void)lib;
            ;
            ;
            U64 _t3333; { U64 *_hp = (U64 *)Str_len(lib); _t3333 = *_hp; free(_hp); }
            (void)_t3333;
            U64 _t3334 = 0;
            (void)_t3334;
            U64 _t3335 = 1;
            (void)_t3335;
            U64 _t3336 = U64_add(DEREF(ai), _t3335);
            (void)_t3336;
            ;
            U64 _t3337; { U64 *_hp = (U64 *)Array_len(args); _t3337 = *_hp; free(_hp); }
            (void)_t3337;
            Bool _t3338 = U64_eq(_t3333, _t3334);
            (void)_t3338;
            ;
            ;
            Bool _t3339; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3336}, &(U64){_t3337}); _t3339 = *_hp; free(_hp); }
            (void)_t3339;
            ;
            ;
            Bool _t3340 = Bool_and(_t3338, _t3339);
            (void)_t3340;
            ;
            ;
            if (_t3340) {
                U64 _t3329 = 1;
                (void)_t3329;
                U64 _t3330 = U64_add(DEREF(ai), _t3329);
                (void)_t3330;
                ;
                *ai = _t3330;
                ;
                Str *next_arg = Array_get(args, ai);
                (void)next_arg;
                lib = Str_clone(next_arg);
            }
            ;
            Str *_t3341 = Str_lit(" -l", 3ULL);
            (void)_t3341;
            Str *_t3342 = Str_concat(link_flags, _t3341);
            (void)_t3342;
            Str_delete(_t3341, &(Bool){1});
            link_flags = Str_concat(_t3342, lib);
            Str_delete(_t3342, &(Bool){1});
            Str_delete(lib, &(Bool){1});
        } else {
            Str *_t3343 = Str_clone(arg);
            (void)_t3343;
            Vec_push(user_argv, _t3343);
        }
        ;
        U64 _t3347 = 1;
        (void)_t3347;
        U64 _t3348 = U64_add(DEREF(ai), _t3347);
        (void)_t3348;
        ;
        *ai = _t3348;
        ;
    }
    U64_delete(ai, &(Bool){1});
    Array_delete(args, &(Bool){1});
    Str *lflags = Str_lit("", 0ULL);
    (void)lflags;
    U64 _t3638; { U64 *_hp = (U64 *)Str_len(link_flags); _t3638 = *_hp; free(_hp); }
    (void)_t3638;
    U64 _t3639 = 0;
    (void)_t3639;
    Bool _t3640; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3638}, &(U64){_t3639}); _t3640 = *_hp; free(_hp); }
    (void)_t3640;
    ;
    ;
    if (_t3640) {
        lflags = Str_clone(link_flags);
    }
    ;
    Str_delete(link_flags, &(Bool){1});
    Bool is_lib_mode = til_mode_is_lib(cur_mode);
    (void)is_lib_mode;
    Str *_t3641 = Str_lit("interpret", 9ULL);
    (void)_t3641;
    Str *_t3642 = Str_lit("test", 4ULL);
    (void)_t3642;
    Bool _t3643; { Bool *_hp = (Bool *)Str_eq(command, _t3641); _t3643 = *_hp; free(_hp); }
    (void)_t3643;
    Str_delete(_t3641, &(Bool){1});
    Bool _t3644; { Bool *_hp = (Bool *)Str_eq(command, _t3642); _t3644 = *_hp; free(_hp); }
    (void)_t3644;
    Str_delete(_t3642, &(Bool){1});
    Bool _t3645 = Bool_or(_t3643, _t3644);
    (void)_t3645;
    ;
    ;
    if (_t3645) {
        Str *_t3355 = Str_lit("interpret", 9ULL);
        (void)_t3355;
        Bool _t3356; { Bool *_hp = (Bool *)Str_eq(command, _t3355); _t3356 = *_hp; free(_hp); }
        (void)_t3356;
        Str_delete(_t3355, &(Bool){1});
        Bool _t3357 = Bool_and(is_lib_mode, _t3356);
        (void)_t3357;
        ;
        if (_t3357) {
            Str *_t3349 = Str_lit("Str", 3ULL);
            (void)_t3349;
            U64 _t3350; { U64 *_hp = (U64 *)Str_size(); _t3350 = *_hp; free(_hp); }
            (void)_t3350;
            U64 _t3351 = 1;
            (void)_t3351;
            Array *_va69 = Array_new(_t3349, &(U64){_t3350}, &(U64){_t3351});
            (void)_va69;
            Str_delete(_t3349, &(Bool){1});
            ;
            ;
            U64 _t3352 = 0;
            (void)_t3352;
            Str *_t3353 = Str_lit("cannot interpret a library — use translate or build", 53ULL);
            (void)_t3353;
            Array_set(_va69, &(U64){_t3352}, _t3353);
            ;
            Str *_t3354 = Str_lit("src/til.til:499:19", 18ULL);
            (void)_t3354;
            panic(_t3354, _va69);
            Str_delete(_t3354, &(Bool){1});
        }
        ;
        I32 _t3358 = til_interpret_v(ast, cur_mode, run_tests, path, user_c, ext_c_path, lflags, user_argv);
        (void)_t3358;
        result = _t3358;
        ;
    } else {
        Str *_t3560 = Str_lit("translate", 9ULL);
        (void)_t3560;
        Str *_t3561 = Str_lit("build", 5ULL);
        (void)_t3561;
        Bool _t3562; { Bool *_hp = (Bool *)Str_eq(command, _t3560); _t3562 = *_hp; free(_hp); }
        (void)_t3562;
        Str_delete(_t3560, &(Bool){1});
        Bool _t3563; { Bool *_hp = (Bool *)Str_eq(command, _t3561); _t3563 = *_hp; free(_hp); }
        (void)_t3563;
        Str_delete(_t3561, &(Bool){1});
        Str *_t3564 = Str_lit("run", 3ULL);
        (void)_t3564;
        Bool _t3565 = Bool_or(_t3562, _t3563);
        (void)_t3565;
        ;
        ;
        Bool _t3566; { Bool *_hp = (Bool *)Str_eq(command, _t3564); _t3566 = *_hp; free(_hp); }
        (void)_t3566;
        Str_delete(_t3564, &(Bool){1});
        Bool _t3567 = Bool_or(_t3565, _t3566);
        (void)_t3567;
        ;
        ;
        if (_t3567) {
            Str *_t3484 = Str_lit("run", 3ULL);
            (void)_t3484;
            Bool _t3485; { Bool *_hp = (Bool *)Str_eq(command, _t3484); _t3485 = *_hp; free(_hp); }
            (void)_t3485;
            Str_delete(_t3484, &(Bool){1});
            Bool _t3486 = Bool_and(is_lib_mode, _t3485);
            (void)_t3486;
            ;
            if (_t3486) {
                Str *_t3359 = Str_lit("Str", 3ULL);
                (void)_t3359;
                U64 _t3360; { U64 *_hp = (U64 *)Str_size(); _t3360 = *_hp; free(_hp); }
                (void)_t3360;
                U64 _t3361 = 1;
                (void)_t3361;
                Array *_va70 = Array_new(_t3359, &(U64){_t3360}, &(U64){_t3361});
                (void)_va70;
                Str_delete(_t3359, &(Bool){1});
                ;
                ;
                U64 _t3362 = 0;
                (void)_t3362;
                Str *_t3363 = Str_lit("cannot run a library — use translate or build", 47ULL);
                (void)_t3363;
                Array_set(_va70, &(U64){_t3362}, _t3363);
                ;
                Str *_t3364 = Str_lit("src/til.til:505:19", 18ULL);
                (void)_t3364;
                panic(_t3364, _va70);
                Str_delete(_t3364, &(Bool){1});
            }
            ;
            Str *_t3487 = Str_lit("/", 1ULL);
            (void)_t3487;
            I64 *last_slash = Str_rfind(path, _t3487);
            (void)last_slash;
            Str_delete(_t3487, &(Bool){1});
            Str *basename = Str_clone(path);
            (void)basename;
            I64 _t3488 = 0;
            (void)_t3488;
            Bool _t3489; { Bool *_hp = (Bool *)I64_gte(last_slash, &(I64){_t3488}); _t3489 = *_hp; free(_hp); }
            (void)_t3489;
            ;
            if (_t3489) {
                I64 _t3365 = 1;
                (void)_t3365;
                I64 _t3366 = I64_add(DEREF(last_slash), _t3365);
                (void)_t3366;
                ;
                U64 _t3367; { U64 *_hp = (U64 *)Str_len(path); _t3367 = *_hp; free(_hp); }
                (void)_t3367;
                U64 _t3368 = I64_to_u64(DEREF(last_slash));
                (void)_t3368;
                U64 _t3369 = U64_sub(_t3367, _t3368);
                (void)_t3369;
                ;
                ;
                U64 _t3370 = 1;
                (void)_t3370;
                U64 _t3371 = I64_to_u64(_t3366);
                (void)_t3371;
                ;
                U64 _t3372 = U64_sub(_t3369, _t3370);
                (void)_t3372;
                ;
                ;
                basename = Str_substr(path, &(U64){_t3371}, &(U64){_t3372});
                ;
                ;
            }
            ;
            I64_delete(last_slash, &(Bool){1});
            U64 name_len; { U64 *_hp = (U64 *)Str_len(basename); name_len = *_hp; free(_hp); }
            (void)name_len;
            Str *_t3490 = Str_lit(".til", 4ULL);
            (void)_t3490;
            Bool _t3491; { Bool *_hp = (Bool *)Str_ends_with(basename, _t3490); _t3491 = *_hp; free(_hp); }
            (void)_t3491;
            Str_delete(_t3490, &(Bool){1});
            if (_t3491) {
                U64 _t3373 = 4;
                (void)_t3373;
                U64 _t3374 = U64_sub(name_len, _t3373);
                (void)_t3374;
                ;
                name_len = _t3374;
                ;
            }
            ;
            U64 _t3492 = 0;
            (void)_t3492;
            Str *name = Str_substr(basename, &(U64){_t3492}, &(U64){name_len});
            (void)name;
            ;
            Str_delete(basename, &(Bool){1});
            ;
            Str *_t3493 = Str_lit("gen/til/", 8ULL);
            (void)_t3493;
            Str *_t3494 = Str_concat(_t3493, name);
            (void)_t3494;
            Str_delete(_t3493, &(Bool){1});
            Str *_t3495 = Str_lit(".c", 2ULL);
            (void)_t3495;
            Str *c_path = Str_concat(_t3494, _t3495);
            (void)c_path;
            Str_delete(_t3494, &(Bool){1});
            Str_delete(_t3495, &(Bool){1});
            U64 _t3496; { U64 *_hp = (U64 *)Str_len(custom_c); _t3496 = *_hp; free(_hp); }
            (void)_t3496;
            U64 _t3497 = 0;
            (void)_t3497;
            Bool _t3498; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3496}, &(U64){_t3497}); _t3498 = *_hp; free(_hp); }
            (void)_t3498;
            ;
            ;
            if (_t3498) {
                c_path = Str_clone(custom_c);
            }
            ;
            Str *_t3499 = Str_lit("bin/til/", 8ULL);
            (void)_t3499;
            Str *bin_path = Str_concat(_t3499, name);
            (void)bin_path;
            Str_delete(_t3499, &(Bool){1});
            U64 _t3500; { U64 *_hp = (U64 *)Str_len(custom_bin); _t3500 = *_hp; free(_hp); }
            (void)_t3500;
            U64 _t3501 = 0;
            (void)_t3501;
            Bool _t3502; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3500}, &(U64){_t3501}); _t3502 = *_hp; free(_hp); }
            (void)_t3502;
            ;
            ;
            if (_t3502) {
                bin_path = Str_clone(custom_bin);
            }
            ;
            Str *_t3503 = Str_lit("run", 3ULL);
            (void)_t3503;
            Bool _t3504; { Bool *_hp = (Bool *)Str_eq(command, _t3503); _t3504 = *_hp; free(_hp); }
            (void)_t3504;
            Str_delete(_t3503, &(Bool){1});
            Bool _t3505 = til_mode_is_lib_output(cur_mode);
            (void)_t3505;
            Bool _t3506 = Bool_not(_t3504);
            (void)_t3506;
            ;
            Bool do_lib = Bool_and(_t3505, _t3506);
            (void)do_lib;
            ;
            ;
            if (do_lib) {
                Str *_t3375 = Str_lit("mkdir -p gen/til gen/lib", 24ULL);
                (void)_t3375;
                I32 _t3376 = til_system(_t3375);
                (void)_t3376;
                Str_delete(_t3375, &(Bool){1});
                ;
            } else {
                Str *_t3381 = Str_lit("/", 1ULL);
                (void)_t3381;
                I64 cp_slash; { I64 *_hp = (I64 *)Str_rfind(c_path, _t3381); cp_slash = *_hp; free(_hp); }
                (void)cp_slash;
                Str_delete(_t3381, &(Bool){1});
                Str *_t3382 = Str_lit("/", 1ULL);
                (void)_t3382;
                I64 bp_slash; { I64 *_hp = (I64 *)Str_rfind(bin_path, _t3382); bp_slash = *_hp; free(_hp); }
                (void)bp_slash;
                Str_delete(_t3382, &(Bool){1});
                Str *cp_dir = Str_lit("gen/til", 7ULL);
                (void)cp_dir;
                I64 _t3383 = 0;
                (void)_t3383;
                Bool _t3384; { Bool *_hp = (Bool *)I64_gt(&(I64){cp_slash}, &(I64){_t3383}); _t3384 = *_hp; free(_hp); }
                (void)_t3384;
                ;
                if (_t3384) {
                    U64 _t3377 = 0;
                    (void)_t3377;
                    U64 _t3378 = I64_to_u64(cp_slash);
                    (void)_t3378;
                    cp_dir = Str_substr(c_path, &(U64){_t3377}, &(U64){_t3378});
                    ;
                    ;
                }
                ;
                ;
                Str *bp_dir = Str_lit("bin/til", 7ULL);
                (void)bp_dir;
                I64 _t3385 = 0;
                (void)_t3385;
                Bool _t3386; { Bool *_hp = (Bool *)I64_gt(&(I64){bp_slash}, &(I64){_t3385}); _t3386 = *_hp; free(_hp); }
                (void)_t3386;
                ;
                if (_t3386) {
                    U64 _t3379 = 0;
                    (void)_t3379;
                    U64 _t3380 = I64_to_u64(bp_slash);
                    (void)_t3380;
                    bp_dir = Str_substr(bin_path, &(U64){_t3379}, &(U64){_t3380});
                    ;
                    ;
                }
                ;
                ;
                Str *_t3387 = Str_lit("mkdir -p ", 9ULL);
                (void)_t3387;
                Str *_t3388 = Str_concat(_t3387, cp_dir);
                (void)_t3388;
                Str_delete(_t3387, &(Bool){1});
                Str_delete(cp_dir, &(Bool){1});
                Str *_t3389 = Str_lit(" ", 1ULL);
                (void)_t3389;
                Str *_t3390 = Str_concat(_t3388, _t3389);
                (void)_t3390;
                Str_delete(_t3388, &(Bool){1});
                Str_delete(_t3389, &(Bool){1});
                Str *_t3391 = Str_concat(_t3390, bp_dir);
                (void)_t3391;
                Str_delete(_t3390, &(Bool){1});
                Str_delete(bp_dir, &(Bool){1});
                I32 _t3392 = til_system(_t3391);
                (void)_t3392;
                Str_delete(_t3391, &(Bool){1});
                ;
            }
            I32 _t3507 = build(ast, cur_mode, run_tests, path, c_path);
            (void)_t3507;
            result = _t3507;
            ;
            I32 _t3508 = 0;
            (void)_t3508;
            Bool _t3509 = I32_eq(result, _t3508);
            (void)_t3509;
            ;
            Bool _t3510 = Bool_and(_t3509, do_lib);
            (void)_t3510;
            ;
            if (_t3510) {
                Str *_t3449 = Str_lit("gen/til/", 8ULL);
                (void)_t3449;
                Str *_t3450 = Str_concat(_t3449, name);
                (void)_t3450;
                Str_delete(_t3449, &(Bool){1});
                Str *_t3451 = Str_lit(".h", 2ULL);
                (void)_t3451;
                Str *h_path = Str_concat(_t3450, _t3451);
                (void)h_path;
                Str_delete(_t3450, &(Bool){1});
                Str_delete(_t3451, &(Bool){1});
                Str *_t3452 = Str_lit("gen/til/", 8ULL);
                (void)_t3452;
                Str *_t3453 = Str_concat(_t3452, name);
                (void)_t3453;
                Str_delete(_t3452, &(Bool){1});
                Str *_t3454 = Str_lit(".til", 4ULL);
                (void)_t3454;
                Str *til_path = Str_concat(_t3453, _t3454);
                (void)til_path;
                Str_delete(_t3453, &(Bool){1});
                Str_delete(_t3454, &(Bool){1});
                I32 _t3455 = build_header(ast, h_path);
                (void)_t3455;
                result = _t3455;
                ;
                I32 _t3456 = 0;
                (void)_t3456;
                Bool _t3457 = I32_eq(result, _t3456);
                (void)_t3457;
                ;
                if (_t3457) {
                    I32 _t3393 = build_til_binding(ast, til_path, name);
                    (void)_t3393;
                    result = _t3393;
                    ;
                }
                ;
                I32 _t3458 = 0;
                (void)_t3458;
                Str *_t3459 = Str_lit("translate", 9ULL);
                (void)_t3459;
                Bool _t3460 = I32_eq(result, _t3458);
                (void)_t3460;
                ;
                Bool _t3461; { Bool *_hp = (Bool *)Str_eq(command, _t3459); _t3461 = *_hp; free(_hp); }
                (void)_t3461;
                Str_delete(_t3459, &(Bool){1});
                Bool _t3462 = Bool_and(_t3460, _t3461);
                (void)_t3462;
                ;
                ;
                if (_t3462) {
                    Str *_t3394 = Str_lit("Str", 3ULL);
                    (void)_t3394;
                    U64 _t3395; { U64 *_hp = (U64 *)Str_size(); _t3395 = *_hp; free(_hp); }
                    (void)_t3395;
                    U64 _t3396 = 1;
                    (void)_t3396;
                    Array *_va71 = Array_new(_t3394, &(U64){_t3395}, &(U64){_t3396});
                    (void)_va71;
                    Str_delete(_t3394, &(Bool){1});
                    ;
                    ;
                    Str *_t3397 = Str_lit("Generated: ", 11ULL);
                    (void)_t3397;
                    U64 _t3398 = 0;
                    (void)_t3398;
                    Str *_t3399 = Str_concat(_t3397, c_path);
                    (void)_t3399;
                    Str_delete(_t3397, &(Bool){1});
                    Array_set(_va71, &(U64){_t3398}, _t3399);
                    ;
                    println(_va71);
                    Str *_t3400 = Str_lit("Str", 3ULL);
                    (void)_t3400;
                    U64 _t3401; { U64 *_hp = (U64 *)Str_size(); _t3401 = *_hp; free(_hp); }
                    (void)_t3401;
                    U64 _t3402 = 1;
                    (void)_t3402;
                    Array *_va72 = Array_new(_t3400, &(U64){_t3401}, &(U64){_t3402});
                    (void)_va72;
                    Str_delete(_t3400, &(Bool){1});
                    ;
                    ;
                    Str *_t3403 = Str_lit("Generated: ", 11ULL);
                    (void)_t3403;
                    U64 _t3404 = 0;
                    (void)_t3404;
                    Str *_t3405 = Str_concat(_t3403, h_path);
                    (void)_t3405;
                    Str_delete(_t3403, &(Bool){1});
                    Array_set(_va72, &(U64){_t3404}, _t3405);
                    ;
                    println(_va72);
                    Str *_t3406 = Str_lit("Str", 3ULL);
                    (void)_t3406;
                    U64 _t3407; { U64 *_hp = (U64 *)Str_size(); _t3407 = *_hp; free(_hp); }
                    (void)_t3407;
                    U64 _t3408 = 1;
                    (void)_t3408;
                    Array *_va73 = Array_new(_t3406, &(U64){_t3407}, &(U64){_t3408});
                    (void)_va73;
                    Str_delete(_t3406, &(Bool){1});
                    ;
                    ;
                    Str *_t3409 = Str_lit("Generated: ", 11ULL);
                    (void)_t3409;
                    U64 _t3410 = 0;
                    (void)_t3410;
                    Str *_t3411 = Str_concat(_t3409, til_path);
                    (void)_t3411;
                    Str_delete(_t3409, &(Bool){1});
                    Array_set(_va73, &(U64){_t3410}, _t3411);
                    ;
                    println(_va73);
                }
                ;
                I32 _t3463 = 0;
                (void)_t3463;
                Str *_t3464 = Str_lit("build", 5ULL);
                (void)_t3464;
                Bool _t3465 = I32_eq(result, _t3463);
                (void)_t3465;
                ;
                Bool _t3466; { Bool *_hp = (Bool *)Str_eq(command, _t3464); _t3466 = *_hp; free(_hp); }
                (void)_t3466;
                Str_delete(_t3464, &(Bool){1});
                Bool _t3467 = Bool_and(_t3465, _t3466);
                (void)_t3467;
                ;
                ;
                if (_t3467) {
                    I32 _t3446 = til_compile_lib(c_path, name, ext_c_path, user_c, lflags);
                    (void)_t3446;
                    result = _t3446;
                    ;
                    I32 _t3447 = 0;
                    (void)_t3447;
                    Bool _t3448 = I32_eq(result, _t3447);
                    (void)_t3448;
                    ;
                    if (_t3448) {
                        Str *_t3412 = Str_lit("Str", 3ULL);
                        (void)_t3412;
                        U64 _t3413; { U64 *_hp = (U64 *)Str_size(); _t3413 = *_hp; free(_hp); }
                        (void)_t3413;
                        U64 _t3414 = 1;
                        (void)_t3414;
                        Array *_va74 = Array_new(_t3412, &(U64){_t3413}, &(U64){_t3414});
                        (void)_va74;
                        Str_delete(_t3412, &(Bool){1});
                        ;
                        ;
                        Str *_t3415 = Str_lit("Generated: ", 11ULL);
                        (void)_t3415;
                        U64 _t3416 = 0;
                        (void)_t3416;
                        Str *_t3417 = Str_concat(_t3415, c_path);
                        (void)_t3417;
                        Str_delete(_t3415, &(Bool){1});
                        Array_set(_va74, &(U64){_t3416}, _t3417);
                        ;
                        println(_va74);
                        Str *_t3418 = Str_lit("Str", 3ULL);
                        (void)_t3418;
                        U64 _t3419; { U64 *_hp = (U64 *)Str_size(); _t3419 = *_hp; free(_hp); }
                        (void)_t3419;
                        U64 _t3420 = 1;
                        (void)_t3420;
                        Array *_va75 = Array_new(_t3418, &(U64){_t3419}, &(U64){_t3420});
                        (void)_va75;
                        Str_delete(_t3418, &(Bool){1});
                        ;
                        ;
                        Str *_t3421 = Str_lit("Generated: ", 11ULL);
                        (void)_t3421;
                        U64 _t3422 = 0;
                        (void)_t3422;
                        Str *_t3423 = Str_concat(_t3421, h_path);
                        (void)_t3423;
                        Str_delete(_t3421, &(Bool){1});
                        Array_set(_va75, &(U64){_t3422}, _t3423);
                        ;
                        println(_va75);
                        Str *_t3424 = Str_lit("Str", 3ULL);
                        (void)_t3424;
                        U64 _t3425; { U64 *_hp = (U64 *)Str_size(); _t3425 = *_hp; free(_hp); }
                        (void)_t3425;
                        U64 _t3426 = 1;
                        (void)_t3426;
                        Array *_va76 = Array_new(_t3424, &(U64){_t3425}, &(U64){_t3426});
                        (void)_va76;
                        Str_delete(_t3424, &(Bool){1});
                        ;
                        ;
                        Str *_t3427 = Str_lit("Generated: ", 11ULL);
                        (void)_t3427;
                        U64 _t3428 = 0;
                        (void)_t3428;
                        Str *_t3429 = Str_concat(_t3427, til_path);
                        (void)_t3429;
                        Str_delete(_t3427, &(Bool){1});
                        Array_set(_va76, &(U64){_t3428}, _t3429);
                        ;
                        println(_va76);
                        Str *_t3430 = Str_lit("Str", 3ULL);
                        (void)_t3430;
                        U64 _t3431; { U64 *_hp = (U64 *)Str_size(); _t3431 = *_hp; free(_hp); }
                        (void)_t3431;
                        U64 _t3432 = 1;
                        (void)_t3432;
                        Array *_va77 = Array_new(_t3430, &(U64){_t3431}, &(U64){_t3432});
                        (void)_va77;
                        Str_delete(_t3430, &(Bool){1});
                        ;
                        ;
                        Str *_t3433 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t3433;
                        Str *_t3434 = Str_concat(_t3433, name);
                        (void)_t3434;
                        Str_delete(_t3433, &(Bool){1});
                        Str *_t3435 = Str_lit(".so", 3ULL);
                        (void)_t3435;
                        U64 _t3436 = 0;
                        (void)_t3436;
                        Str *_t3437 = Str_concat(_t3434, _t3435);
                        (void)_t3437;
                        Str_delete(_t3434, &(Bool){1});
                        Str_delete(_t3435, &(Bool){1});
                        Array_set(_va77, &(U64){_t3436}, _t3437);
                        ;
                        println(_va77);
                        Str *_t3438 = Str_lit("Str", 3ULL);
                        (void)_t3438;
                        U64 _t3439; { U64 *_hp = (U64 *)Str_size(); _t3439 = *_hp; free(_hp); }
                        (void)_t3439;
                        U64 _t3440 = 1;
                        (void)_t3440;
                        Array *_va78 = Array_new(_t3438, &(U64){_t3439}, &(U64){_t3440});
                        (void)_va78;
                        Str_delete(_t3438, &(Bool){1});
                        ;
                        ;
                        Str *_t3441 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t3441;
                        Str *_t3442 = Str_concat(_t3441, name);
                        (void)_t3442;
                        Str_delete(_t3441, &(Bool){1});
                        Str *_t3443 = Str_lit(".a", 2ULL);
                        (void)_t3443;
                        U64 _t3444 = 0;
                        (void)_t3444;
                        Str *_t3445 = Str_concat(_t3442, _t3443);
                        (void)_t3445;
                        Str_delete(_t3442, &(Bool){1});
                        Str_delete(_t3443, &(Bool){1});
                        Array_set(_va78, &(U64){_t3444}, _t3445);
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
            I32 _t3511 = 0;
            (void)_t3511;
            Bool _t3512 = I32_eq(result, _t3511);
            (void)_t3512;
            ;
            Bool _t3513 = Bool_not(do_lib);
            (void)_t3513;
            Str *_t3514 = Str_lit("translate", 9ULL);
            (void)_t3514;
            Bool _t3515 = Bool_and(_t3512, _t3513);
            (void)_t3515;
            ;
            ;
            Bool _t3516; { Bool *_hp = (Bool *)Str_eq(command, _t3514); _t3516 = *_hp; free(_hp); }
            (void)_t3516;
            Str_delete(_t3514, &(Bool){1});
            Bool _t3517 = Bool_and(_t3515, _t3516);
            (void)_t3517;
            ;
            ;
            if (_t3517) {
                Str *_t3468 = Str_lit("Str", 3ULL);
                (void)_t3468;
                U64 _t3469; { U64 *_hp = (U64 *)Str_size(); _t3469 = *_hp; free(_hp); }
                (void)_t3469;
                U64 _t3470 = 1;
                (void)_t3470;
                Array *_va79 = Array_new(_t3468, &(U64){_t3469}, &(U64){_t3470});
                (void)_va79;
                Str_delete(_t3468, &(Bool){1});
                ;
                ;
                Str *_t3471 = Str_lit("Generated: ", 11ULL);
                (void)_t3471;
                U64 _t3472 = 0;
                (void)_t3472;
                Str *_t3473 = Str_concat(_t3471, c_path);
                (void)_t3473;
                Str_delete(_t3471, &(Bool){1});
                Array_set(_va79, &(U64){_t3472}, _t3473);
                ;
                println(_va79);
            }
            ;
            I32 _t3518 = 0;
            (void)_t3518;
            Bool _t3519 = I32_eq(result, _t3518);
            (void)_t3519;
            ;
            Bool _t3520 = Bool_not(do_lib);
            (void)_t3520;
            Str *_t3521 = Str_lit("translate", 9ULL);
            (void)_t3521;
            Bool _t3522; { Bool *_hp = (Bool *)Str_eq(command, _t3521); _t3522 = *_hp; free(_hp); }
            (void)_t3522;
            Str_delete(_t3521, &(Bool){1});
            Bool _t3523 = Bool_and(_t3519, _t3520);
            (void)_t3523;
            ;
            ;
            Bool _t3524 = Bool_not(_t3522);
            (void)_t3524;
            ;
            Bool _t3525 = Bool_and(_t3523, _t3524);
            (void)_t3525;
            ;
            ;
            if (_t3525) {
                I32 _t3474 = til_compile_c(c_path, bin_path, ext_c_path, user_c, lflags);
                (void)_t3474;
                result = _t3474;
                ;
            }
            ;
            Str_delete(c_path, &(Bool){1});
            I32 _t3526 = 0;
            (void)_t3526;
            Bool _t3527 = I32_eq(result, _t3526);
            (void)_t3527;
            ;
            Bool _t3528 = Bool_not(do_lib);
            (void)_t3528;
            ;
            Str *_t3529 = Str_lit("run", 3ULL);
            (void)_t3529;
            Bool _t3530 = Bool_and(_t3527, _t3528);
            (void)_t3530;
            ;
            ;
            Bool _t3531; { Bool *_hp = (Bool *)Str_eq(command, _t3529); _t3531 = *_hp; free(_hp); }
            (void)_t3531;
            Str_delete(_t3529, &(Bool){1});
            Bool _t3532 = Bool_and(_t3530, _t3531);
            (void)_t3532;
            ;
            ;
            if (_t3532) {
                Str *cmd = Str_clone(bin_path);
                (void)cmd;
                U64 *ui = malloc(sizeof(U64));
                *ui = 0;
                (void)ui;
                while (1) {
                    U64 _t3476; { U64 *_hp = (U64 *)Vec_len(user_argv); _t3476 = *_hp; free(_hp); }
                    (void)_t3476;
                    Bool _wcond3475; { Bool *_hp = (Bool *)U64_lt(ui, &(U64){_t3476}); _wcond3475 = *_hp; free(_hp); }
                    (void)_wcond3475;
                    ;
                    if (_wcond3475) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *uarg = Vec_get(user_argv, ui);
                    (void)uarg;
                    Str *_t3477 = Str_lit(" '", 2ULL);
                    (void)_t3477;
                    Str *_t3478 = Str_concat(cmd, _t3477);
                    (void)_t3478;
                    Str_delete(_t3477, &(Bool){1});
                    Str *_t3479 = Str_concat(_t3478, uarg);
                    (void)_t3479;
                    Str_delete(_t3478, &(Bool){1});
                    Str *_t3480 = Str_lit("'", 1ULL);
                    (void)_t3480;
                    cmd = Str_concat(_t3479, _t3480);
                    Str_delete(_t3479, &(Bool){1});
                    Str_delete(_t3480, &(Bool){1});
                    U64 _t3481 = 1;
                    (void)_t3481;
                    U64 _t3482 = U64_add(DEREF(ui), _t3481);
                    (void)_t3482;
                    ;
                    *ui = _t3482;
                    ;
                }
                U64_delete(ui, &(Bool){1});
                I32 _t3483 = til_system(cmd);
                (void)_t3483;
                Str_delete(cmd, &(Bool){1});
                result = _t3483;
                ;
            }
            ;
            Str_delete(bin_path, &(Bool){1});
        } else {
            Str *_t3558 = Str_lit("ast", 3ULL);
            (void)_t3558;
            Bool _t3559; { Bool *_hp = (Bool *)Str_eq(command, _t3558); _t3559 = *_hp; free(_hp); }
            (void)_t3559;
            Str_delete(_t3558, &(Bool){1});
            if (_t3559) {
                Mode *_t3545 = til_mode_none();
                (void)_t3545;
                Bool _t3546 = til_mode_eq(cur_mode, _t3545);
                (void)_t3546;
                Mode_delete(_t3545, &(Bool){1});
                Bool _t3547 = Bool_not(_t3546);
                (void)_t3547;
                ;
                if (_t3547) {
                    Str *_t3533 = Str_lit("Str", 3ULL);
                    (void)_t3533;
                    U64 _t3534; { U64 *_hp = (U64 *)Str_size(); _t3534 = *_hp; free(_hp); }
                    (void)_t3534;
                    U64 _t3535 = 1;
                    (void)_t3535;
                    Array *_va80 = Array_new(_t3533, &(U64){_t3534}, &(U64){_t3535});
                    (void)_va80;
                    Str_delete(_t3533, &(Bool){1});
                    ;
                    ;
                    Str *_t3536 = Str_lit("mode: ", 6ULL);
                    (void)_t3536;
                    Str *_t3537 = til_mode_name(cur_mode);
                    (void)_t3537;
                    U64 _t3538 = 0;
                    (void)_t3538;
                    Str *_t3539 = Str_concat(_t3536, _t3537);
                    (void)_t3539;
                    Str_delete(_t3536, &(Bool){1});
                    Str_delete(_t3537, &(Bool){1});
                    Array_set(_va80, &(U64){_t3538}, _t3539);
                    ;
                    println(_va80);
                } else {
                    Str *_t3540 = Str_lit("Str", 3ULL);
                    (void)_t3540;
                    U64 _t3541; { U64 *_hp = (U64 *)Str_size(); _t3541 = *_hp; free(_hp); }
                    (void)_t3541;
                    U64 _t3542 = 1;
                    (void)_t3542;
                    Array *_va81 = Array_new(_t3540, &(U64){_t3541}, &(U64){_t3542});
                    (void)_va81;
                    Str_delete(_t3540, &(Bool){1});
                    ;
                    ;
                    U64 _t3543 = 0;
                    (void)_t3543;
                    Str *_t3544 = Str_lit("mode: (none)", 12ULL);
                    (void)_t3544;
                    Array_set(_va81, &(U64){_t3543}, _t3544);
                    ;
                    println(_va81);
                }
                ;
                U32 _t3548 = 0;
                (void)_t3548;
                ast_print(ast, _t3548);
                ;
            } else {
                Str *_t3549 = Str_lit("Str", 3ULL);
                (void)_t3549;
                U64 _t3550; { U64 *_hp = (U64 *)Str_size(); _t3550 = *_hp; free(_hp); }
                (void)_t3550;
                U64 _t3551 = 1;
                (void)_t3551;
                Array *_va82 = Array_new(_t3549, &(U64){_t3550}, &(U64){_t3551});
                (void)_va82;
                Str_delete(_t3549, &(Bool){1});
                ;
                ;
                Str *_t3552 = Str_lit("error: unknown command '", 24ULL);
                (void)_t3552;
                Str *_t3553 = Str_concat(_t3552, command);
                (void)_t3553;
                Str_delete(_t3552, &(Bool){1});
                Str *_t3554 = Str_lit("'", 1ULL);
                (void)_t3554;
                U64 _t3555 = 0;
                (void)_t3555;
                Str *_t3556 = Str_concat(_t3553, _t3554);
                (void)_t3556;
                Str_delete(_t3553, &(Bool){1});
                Str_delete(_t3554, &(Bool){1});
                Array_set(_va82, &(U64){_t3555}, _t3556);
                ;
                println(_va82);
                usage();
                I32 _t3557 = 1;
                (void)_t3557;
                result = _t3557;
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
    I64 _t3646 = I32_to_i64(result);
    (void)_t3646;
    ;
    exit(_t3646);
    ;
    return 0;
}

