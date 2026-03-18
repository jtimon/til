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

void mark_core(Expr * e) {
    (void)e;
    Bool _t3183 = 1;
    (void)_t3183;
    e->is_core = _t3183;
    ;
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
    _t3646 = malloc(sizeof(I64));
    *_t3646 = 0;
    (void)_t3646;
    _t3647 = malloc(sizeof(I64));
    *_t3647 = 1;
    (void)_t3647;
    _t3648 = malloc(sizeof(I64)); *_t3648 = I64_sub(DEREF(_t3646), DEREF(_t3647));
    (void)_t3648;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t3648));
    (void)CAP_LIT;
    _t3649 = malloc(sizeof(I64));
    *_t3649 = 0;
    (void)_t3649;
    _t3650 = malloc(sizeof(I64));
    *_t3650 = 2;
    (void)_t3650;
    _t3651 = malloc(sizeof(I64)); *_t3651 = I64_sub(DEREF(_t3649), DEREF(_t3650));
    (void)_t3651;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t3651));
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
    U64 _t3569; { U64 *_hp = (U64 *)Array_len(args); _t3569 = *_hp; free(_hp); }
    (void)_t3569;
    U64 _t3570 = 0;
    (void)_t3570;
    Bool _t3571 = U64_eq(_t3569, _t3570);
    (void)_t3571;
    ;
    ;
    if (_t3571) {
        usage();
        Str *_t3184 = Str_lit("Str", 3ULL);
        (void)_t3184;
        U64 _t3185; { U64 *_hp = (U64 *)Str_size(); _t3185 = *_hp; free(_hp); }
        (void)_t3185;
        U64 _t3186 = 1;
        (void)_t3186;
        Array *_va64 = Array_new(_t3184, &(U64){_t3185}, &(U64){_t3186});
        (void)_va64;
        Str_delete(_t3184, &(Bool){1});
        ;
        ;
        U64 _t3187 = 0;
        (void)_t3187;
        Str *_t3188 = Str_lit("no arguments", 12ULL);
        (void)_t3188;
        Array_set(_va64, &(U64){_t3187}, _t3188);
        ;
        Str *_t3189 = Str_lit("src/til.til:229:15", 18ULL);
        (void)_t3189;
        panic(_t3189, _va64);
        Str_delete(_t3189, &(Bool){1});
    }
    ;
    U64 *_t3572 = malloc(sizeof(U64));
    *_t3572 = 0;
    (void)_t3572;
    Str *cmd_ref = Array_get(args, _t3572);
    (void)cmd_ref;
    Str *command = Str_clone(cmd_ref);
    (void)command;
    U64_delete(_t3572, &(Bool){1});
    Str *path = Str_lit("", 0ULL);
    (void)path;
    Str *custom_bin = Str_lit("", 0ULL);
    (void)custom_bin;
    Str *custom_c = Str_lit("", 0ULL);
    (void)custom_c;
    U64 *path_idx = malloc(sizeof(U64));
    *path_idx = 1;
    (void)path_idx;
    U64 _t3573; { U64 *_hp = (U64 *)Array_len(args); _t3573 = *_hp; free(_hp); }
    (void)_t3573;
    U64 _t3574 = 1;
    (void)_t3574;
    Bool _t3575 = U64_eq(_t3573, _t3574);
    (void)_t3575;
    ;
    ;
    if (_t3575) {
        Str *_t3190 = Str_lit("help", 4ULL);
        (void)_t3190;
        Str *_t3191 = Str_lit("--help", 6ULL);
        (void)_t3191;
        Bool _t3192; { Bool *_hp = (Bool *)Str_eq(command, _t3190); _t3192 = *_hp; free(_hp); }
        (void)_t3192;
        Str_delete(_t3190, &(Bool){1});
        Bool _t3193; { Bool *_hp = (Bool *)Str_eq(command, _t3191); _t3193 = *_hp; free(_hp); }
        (void)_t3193;
        Str_delete(_t3191, &(Bool){1});
        Bool _t3194 = Bool_or(_t3192, _t3193);
        (void)_t3194;
        ;
        ;
        if (_t3194) {
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
            U64 _t3211; { U64 *_hp = (U64 *)Array_len(args); _t3211 = *_hp; free(_hp); }
            (void)_t3211;
            Bool _wcond3195; { Bool *_hp = (Bool *)U64_lt(path_idx, &(U64){_t3211}); _wcond3195 = *_hp; free(_hp); }
            (void)_wcond3195;
            ;
            if (_wcond3195) {
            } else {
                ;
                break;
            }
            ;
            Str *flag = Array_get(args, path_idx);
            (void)flag;
            Str *_t3212 = Str_lit("-o", 2ULL);
            (void)_t3212;
            U64 _t3213 = 1;
            (void)_t3213;
            U64 _t3214 = U64_add(DEREF(path_idx), _t3213);
            (void)_t3214;
            ;
            U64 _t3215; { U64 *_hp = (U64 *)Array_len(args); _t3215 = *_hp; free(_hp); }
            (void)_t3215;
            Bool _t3216; { Bool *_hp = (Bool *)Str_eq(flag, _t3212); _t3216 = *_hp; free(_hp); }
            (void)_t3216;
            Str_delete(_t3212, &(Bool){1});
            Bool _t3217; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3214}, &(U64){_t3215}); _t3217 = *_hp; free(_hp); }
            (void)_t3217;
            ;
            ;
            Bool _t3218 = Bool_and(_t3216, _t3217);
            (void)_t3218;
            ;
            ;
            if (_t3218) {
                U64 _t3196 = 1;
                (void)_t3196;
                U64 *_t3197 = malloc(sizeof(U64)); *_t3197 = U64_add(DEREF(path_idx), _t3196);
                (void)_t3197;
                ;
                Str *oval = Array_get(args, _t3197);
                (void)oval;
                custom_bin = Str_clone(oval);
                U64_delete(_t3197, &(Bool){1});
                U64 _t3198 = 2;
                (void)_t3198;
                U64 _t3199 = U64_add(DEREF(path_idx), _t3198);
                (void)_t3199;
                ;
                *path_idx = _t3199;
                ;
            } else {
                Str *_t3204 = Str_lit("-c", 2ULL);
                (void)_t3204;
                U64 _t3205 = 1;
                (void)_t3205;
                U64 _t3206 = U64_add(DEREF(path_idx), _t3205);
                (void)_t3206;
                ;
                U64 _t3207; { U64 *_hp = (U64 *)Array_len(args); _t3207 = *_hp; free(_hp); }
                (void)_t3207;
                Bool _t3208; { Bool *_hp = (Bool *)Str_eq(flag, _t3204); _t3208 = *_hp; free(_hp); }
                (void)_t3208;
                Str_delete(_t3204, &(Bool){1});
                Bool _t3209; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3206}, &(U64){_t3207}); _t3209 = *_hp; free(_hp); }
                (void)_t3209;
                ;
                ;
                Bool _t3210 = Bool_and(_t3208, _t3209);
                (void)_t3210;
                ;
                ;
                if (_t3210) {
                    U64 _t3200 = 1;
                    (void)_t3200;
                    U64 *_t3201 = malloc(sizeof(U64)); *_t3201 = U64_add(DEREF(path_idx), _t3200);
                    (void)_t3201;
                    ;
                    Str *cval = Array_get(args, _t3201);
                    (void)cval;
                    custom_c = Str_clone(cval);
                    U64_delete(_t3201, &(Bool){1});
                    U64 _t3202 = 2;
                    (void)_t3202;
                    U64 _t3203 = U64_add(DEREF(path_idx), _t3202);
                    (void)_t3203;
                    ;
                    *path_idx = _t3203;
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
    Str *_t3576 = Str_lit("help", 4ULL);
    (void)_t3576;
    Str *_t3577 = Str_lit("--help", 6ULL);
    (void)_t3577;
    Bool _t3578; { Bool *_hp = (Bool *)Str_eq(command, _t3576); _t3578 = *_hp; free(_hp); }
    (void)_t3578;
    Str_delete(_t3576, &(Bool){1});
    Bool _t3579; { Bool *_hp = (Bool *)Str_eq(command, _t3577); _t3579 = *_hp; free(_hp); }
    (void)_t3579;
    Str_delete(_t3577, &(Bool){1});
    Bool _t3580 = Bool_or(_t3578, _t3579);
    (void)_t3580;
    ;
    ;
    if (_t3580) {
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
    Str *_t3581 = Str_lit("/src/core/core.til", 18ULL);
    (void)_t3581;
    Str *core_path = Str_concat(bin_dir, _t3581);
    (void)core_path;
    Str_delete(_t3581, &(Bool){1});
    Str *_t3582 = Str_lit("/src/c/ext.c", 12ULL);
    (void)_t3582;
    Str *ext_c_path = Str_concat(bin_dir, _t3582);
    (void)ext_c_path;
    Str_delete(_t3582, &(Bool){1});
    Set *resolved = til_set_new();
    (void)resolved;
    Vec *resolve_stack = expr_vec_new();
    (void)resolve_stack;
    Str *abs_path = til_realpath(path);
    (void)abs_path;
    Str *user_dir = Str_lit(".", 1ULL);
    (void)user_dir;
    U64 _t3583; { U64 *_hp = (U64 *)Str_len(abs_path); _t3583 = *_hp; free(_hp); }
    (void)_t3583;
    U64 _t3584 = 0;
    (void)_t3584;
    Bool _t3585; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3583}, &(U64){_t3584}); _t3585 = *_hp; free(_hp); }
    (void)_t3585;
    ;
    ;
    if (_t3585) {
        U64 _t3227; { U64 *_hp = (U64 *)Str_len(abs_path); _t3227 = *_hp; free(_hp); }
        (void)_t3227;
        U64 _t3228 = 1;
        (void)_t3228;
        U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t3227, _t3228);
        (void)last_slash;
        ;
        ;
        while (1) {
            U64 _t3220 = 0;
            (void)_t3220;
            U8 *_t3221 = Str_get(abs_path, last_slash);
            (void)_t3221;
            U8 _t3222 = 47;
            (void)_t3222;
            Bool _t3223; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t3220}); _t3223 = *_hp; free(_hp); }
            (void)_t3223;
            ;
            Bool _t3224; { Bool *_hp = (Bool *)U8_neq(_t3221, &(U8){_t3222}); _t3224 = *_hp; free(_hp); }
            (void)_t3224;
            ;
            Bool _wcond3219 = Bool_and(_t3223, _t3224);
            (void)_wcond3219;
            ;
            ;
            if (_wcond3219) {
            } else {
                ;
                break;
            }
            ;
            U64 _t3225 = 1;
            (void)_t3225;
            U64 _t3226 = U64_sub(DEREF(last_slash), _t3225);
            (void)_t3226;
            ;
            *last_slash = _t3226;
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
    U64 _t3586; { U64 *_hp = (U64 *)Str_len(core_abs); _t3586 = *_hp; free(_hp); }
    (void)_t3586;
    U64 _t3587 = 0;
    (void)_t3587;
    Bool _t3588; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3586}, &(U64){_t3587}); _t3588 = *_hp; free(_hp); }
    (void)_t3588;
    ;
    ;
    if (_t3588) {
        Bool _t3230 = til_set_has(resolved, core_abs);
        (void)_t3230;
        if (_t3230) {
            Bool _t3229 = 1;
            (void)_t3229;
            skip_core = _t3229;
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
    U64 _t3589; { U64 *_hp = (U64 *)Vec_len(core_imports); _t3589 = *_hp; free(_hp); }
    (void)_t3589;
    U64 _t3590 = 0;
    (void)_t3590;
    Bool _t3591; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3589}, &(U64){_t3590}); _t3591 = *_hp; free(_hp); }
    (void)_t3591;
    ;
    ;
    Bool _t3592 = Bool_not(skip_core);
    (void)_t3592;
    Bool _t3593 = Bool_and(_t3591, _t3592);
    (void)_t3593;
    ;
    ;
    if (_t3593) {
        Str *_t3237 = Str_lit("/src/core", 9ULL);
        (void)_t3237;
        Str *core_dir = Str_concat(bin_dir, _t3237);
        (void)core_dir;
        Str_delete(_t3237, &(Bool){1});
        Str *_t3238 = Str_lit("", 0ULL);
        (void)_t3238;
        I32 err; { I32 *_hp = (I32 *)resolve_imports(core_imports, core_dir, resolved, resolve_stack, core_import_decls, _t3238); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(_t3238, &(Bool){1});
        Str_delete(core_dir, &(Bool){1});
        I32 _t3239 = 0;
        (void)_t3239;
        Bool _t3240; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t3239}); _t3240 = *_hp; free(_hp); }
        (void)_t3240;
        ;
        ;
        if (_t3240) {
            Str *_t3231 = Str_lit("Str", 3ULL);
            (void)_t3231;
            U64 _t3232; { U64 *_hp = (U64 *)Str_size(); _t3232 = *_hp; free(_hp); }
            (void)_t3232;
            U64 _t3233 = 1;
            (void)_t3233;
            Array *_va65 = Array_new(_t3231, &(U64){_t3232}, &(U64){_t3233});
            (void)_va65;
            Str_delete(_t3231, &(Bool){1});
            ;
            ;
            U64 _t3234 = 0;
            (void)_t3234;
            Str *_t3235 = Str_lit("failed to resolve core imports", 30ULL);
            (void)_t3235;
            Array_set(_va65, &(U64){_t3234}, _t3235);
            ;
            Str *_t3236 = Str_lit("src/til.til:315:19", 18ULL);
            (void)_t3236;
            panic(_t3236, _va65);
            Str_delete(_t3236, &(Bool){1});
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
    Mode *cur_mode = mode_none();
    (void)cur_mode;
    U64 _t3594; { U64 *_hp = (U64 *)Str_len(mode_str); _t3594 = *_hp; free(_hp); }
    (void)_t3594;
    U64 _t3595 = 0;
    (void)_t3595;
    Bool _t3596; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3594}, &(U64){_t3595}); _t3596 = *_hp; free(_hp); }
    (void)_t3596;
    ;
    ;
    if (_t3596) {
        cur_mode = mode_resolve(mode_str);
        Mode *_t3250 = mode_none();
        (void)_t3250;
        Bool _t3251 = mode_eq(cur_mode, _t3250);
        (void)_t3251;
        Mode_delete(_t3250, &(Bool){1});
        if (_t3251) {
            Str *_t3241 = Str_lit("Str", 3ULL);
            (void)_t3241;
            U64 _t3242; { U64 *_hp = (U64 *)Str_size(); _t3242 = *_hp; free(_hp); }
            (void)_t3242;
            U64 _t3243 = 1;
            (void)_t3243;
            Array *_va66 = Array_new(_t3241, &(U64){_t3242}, &(U64){_t3243});
            (void)_va66;
            Str_delete(_t3241, &(Bool){1});
            ;
            ;
            Str *_t3244 = Str_lit("unknown mode '", 14ULL);
            (void)_t3244;
            Str *_t3245 = Str_concat(_t3244, mode_str);
            (void)_t3245;
            Str_delete(_t3244, &(Bool){1});
            Str *_t3246 = Str_lit("'", 1ULL);
            (void)_t3246;
            U64 _t3247 = 0;
            (void)_t3247;
            Str *_t3248 = Str_concat(_t3245, _t3246);
            (void)_t3248;
            Str_delete(_t3245, &(Bool){1});
            Str_delete(_t3246, &(Bool){1});
            Array_set(_va66, &(U64){_t3247}, _t3248);
            ;
            Str *_t3249 = Str_lit("src/til.til:331:19", 18ULL);
            (void)_t3249;
            panic(_t3249, _va66);
            Str_delete(_t3249, &(Bool){1});
        }
        ;
    }
    ;
    Str_delete(mode_str, &(Bool){1});
    Str *auto_import = mode_auto_import(cur_mode);
    (void)auto_import;
    Vec *import_decls = expr_vec_new();
    (void)import_decls;
    U64 _t3597; { U64 *_hp = (U64 *)Vec_len(imports); _t3597 = *_hp; free(_hp); }
    (void)_t3597;
    U64 _t3598 = 0;
    (void)_t3598;
    Bool _t3599; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3597}, &(U64){_t3598}); _t3599 = *_hp; free(_hp); }
    (void)_t3599;
    ;
    ;
    if (_t3599) {
        Str *_t3258 = Str_lit("/src/lib", 8ULL);
        (void)_t3258;
        Str *lib_dir = Str_concat(bin_dir, _t3258);
        (void)lib_dir;
        Str_delete(_t3258, &(Bool){1});
        I32 err; { I32 *_hp = (I32 *)resolve_imports(imports, user_dir, resolved, resolve_stack, import_decls, lib_dir); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(lib_dir, &(Bool){1});
        I32 _t3259 = 0;
        (void)_t3259;
        Bool _t3260; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t3259}); _t3260 = *_hp; free(_hp); }
        (void)_t3260;
        ;
        ;
        if (_t3260) {
            Str *_t3252 = Str_lit("Str", 3ULL);
            (void)_t3252;
            U64 _t3253; { U64 *_hp = (U64 *)Str_size(); _t3253 = *_hp; free(_hp); }
            (void)_t3253;
            U64 _t3254 = 1;
            (void)_t3254;
            Array *_va67 = Array_new(_t3252, &(U64){_t3253}, &(U64){_t3254});
            (void)_va67;
            Str_delete(_t3252, &(Bool){1});
            ;
            ;
            U64 _t3255 = 0;
            (void)_t3255;
            Str *_t3256 = Str_lit("failed to resolve imports", 25ULL);
            (void)_t3256;
            Array_set(_va67, &(U64){_t3255}, _t3256);
            ;
            Str *_t3257 = Str_lit("src/til.til:345:19", 18ULL);
            (void)_t3257;
            panic(_t3257, _va67);
            Str_delete(_t3257, &(Bool){1});
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
    Bool _t3600 = Bool_not(skip_core);
    (void)_t3600;
    ;
    if (_t3600) {
        while (1) {
            U32 _t3262 = expr_nchildren(core_ast);
            (void)_t3262;
            Bool _wcond3261; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3262}); _wcond3261 = *_hp; free(_hp); }
            (void)_wcond3261;
            ;
            if (_wcond3261) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(core_ast, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t3263 = 1;
            (void)_t3263;
            U32 _t3264 = U32_add(DEREF(i), _t3263);
            (void)_t3264;
            ;
            *i = _t3264;
            ;
        }
        U32 _t3269 = 0;
        (void)_t3269;
        *i = _t3269;
        ;
        while (1) {
            U32 _t3266 = expr_vec_count(core_import_decls);
            (void)_t3266;
            Bool _wcond3265; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3266}); _wcond3265 = *_hp; free(_hp); }
            (void)_wcond3265;
            ;
            if (_wcond3265) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_vec_get(core_import_decls, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t3267 = 1;
            (void)_t3267;
            U32 _t3268 = U32_add(DEREF(i), _t3267);
            (void)_t3268;
            ;
            *i = _t3268;
            ;
        }
    }
    ;
    Expr_delete(core_ast, &(Bool){1});
    Vec_delete(core_import_decls, &(Bool){1});
    U64 _t3601; { U64 *_hp = (U64 *)Str_len(auto_import); _t3601 = *_hp; free(_hp); }
    (void)_t3601;
    U64 _t3602 = 0;
    (void)_t3602;
    Bool _t3603; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3601}, &(U64){_t3602}); _t3603 = *_hp; free(_hp); }
    (void)_t3603;
    ;
    ;
    if (_t3603) {
        Str *_t3274 = Str_lit("/src/modes/", 11ULL);
        (void)_t3274;
        Str *_t3275 = Str_concat(bin_dir, _t3274);
        (void)_t3275;
        Str_delete(_t3274, &(Bool){1});
        Str *_t3276 = Str_concat(_t3275, auto_import);
        (void)_t3276;
        Str_delete(_t3275, &(Bool){1});
        Str *_t3277 = Str_lit(".til", 4ULL);
        (void)_t3277;
        Str *mode_til_path = Str_concat(_t3276, _t3277);
        (void)mode_til_path;
        Str_delete(_t3276, &(Bool){1});
        Str_delete(_t3277, &(Bool){1});
        Str *mode_source = readfile(mode_til_path);
        (void)mode_source;
        Vec *mode_tokens = tokenize(mode_source, mode_til_path);
        (void)mode_tokens;
        Str_delete(mode_source, &(Bool){1});
        Expr *mode_ast = til_parse(mode_tokens, mode_til_path);
        (void)mode_ast;
        Str_delete(mode_til_path, &(Bool){1});
        Vec_delete(mode_tokens, &(Bool){1});
        U32 _t3278 = 0;
        (void)_t3278;
        *i = _t3278;
        ;
        while (1) {
            U32 _t3271 = expr_nchildren(mode_ast);
            (void)_t3271;
            Bool _wcond3270; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3271}); _wcond3270 = *_hp; free(_hp); }
            (void)_wcond3270;
            ;
            if (_wcond3270) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(mode_ast, DEREF(i));
            (void)ch;
            expr_vec_push(merged, ch);
            U32 _t3272 = 1;
            (void)_t3272;
            U32 _t3273 = U32_add(DEREF(i), _t3272);
            (void)_t3273;
            ;
            *i = _t3273;
            ;
        }
        Expr_delete(mode_ast, &(Bool){1});
    }
    ;
    Str_delete(auto_import, &(Bool){1});
    Str_delete(bin_dir, &(Bool){1});
    U32 _t3604 = 0;
    (void)_t3604;
    *i = _t3604;
    ;
    while (1) {
        U32 _t3280 = expr_vec_count(import_decls);
        (void)_t3280;
        Bool _wcond3279; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3280}); _wcond3279 = *_hp; free(_hp); }
        (void)_wcond3279;
        ;
        if (_wcond3279) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_vec_get(import_decls, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t3281 = 1;
        (void)_t3281;
        U32 _t3282 = U32_add(DEREF(i), _t3281);
        (void)_t3282;
        ;
        *i = _t3282;
        ;
    }
    Vec_delete(import_decls, &(Bool){1});
    U32 _t3605 = 0;
    (void)_t3605;
    *i = _t3605;
    ;
    while (1) {
        U32 _t3284 = expr_nchildren(ast);
        (void)_t3284;
        Bool _wcond3283; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3284}); _wcond3283 = *_hp; free(_hp); }
        (void)_wcond3283;
        ;
        if (_wcond3283) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_get_child(ast, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t3285 = 1;
        (void)_t3285;
        U32 _t3286 = U32_add(DEREF(i), _t3285);
        (void)_t3286;
        ;
        *i = _t3286;
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
    U32 _t3606 = 0;
    (void)_t3606;
    *i = _t3606;
    ;
    while (1) {
        U32 _t3302 = expr_nchildren(ast);
        (void)_t3302;
        Bool _wcond3287; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3302}); _wcond3287 = *_hp; free(_hp); }
        (void)_wcond3287;
        ;
        if (_wcond3287) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(ast, DEREF(i));
        (void)stmt;
        I32 _t3303 = expr_get_tag(stmt);
        (void)_t3303;
        U32 _t3304 = expr_nchildren(stmt);
        (void)_t3304;
        U32 _t3305 = 2;
        (void)_t3305;
        Bool _t3306 = I32_eq(_t3303, DEREF(NODE_FCALL));
        (void)_t3306;
        ;
        Bool _t3307 = U32_eq(_t3304, _t3305);
        (void)_t3307;
        ;
        ;
        U32 *_t3308 = malloc(sizeof(U32));
        *_t3308 = 0;
        (void)_t3308;
        Expr *_t3309 = expr_get_child(stmt, DEREF(_t3308));
        (void)_t3309;
        I32 _t3310 = expr_get_tag(_t3309);
        (void)_t3310;
        U32_delete(_t3308, &(Bool){1});
        Bool _t3311 = Bool_and(_t3306, _t3307);
        (void)_t3311;
        ;
        ;
        Bool _t3312 = I32_eq(_t3310, DEREF(NODE_IDENT));
        (void)_t3312;
        ;
        U32 *_t3313 = malloc(sizeof(U32));
        *_t3313 = 1;
        (void)_t3313;
        Expr *_t3314 = expr_get_child(stmt, DEREF(_t3313));
        (void)_t3314;
        I32 _t3315 = expr_get_tag(_t3314);
        (void)_t3315;
        U32_delete(_t3313, &(Bool){1});
        Bool _t3316 = Bool_and(_t3311, _t3312);
        (void)_t3316;
        ;
        ;
        Bool _t3317 = I32_eq(_t3315, DEREF(NODE_LITERAL_STR));
        (void)_t3317;
        ;
        Bool _t3318 = Bool_and(_t3316, _t3317);
        (void)_t3318;
        ;
        ;
        if (_t3318) {
            U32 *_t3296 = malloc(sizeof(U32));
            *_t3296 = 0;
            (void)_t3296;
            Expr *_t3297 = expr_get_child(stmt, DEREF(_t3296));
            (void)_t3297;
            Str *fname = expr_get_str_val(_t3297);
            (void)fname;
            U32 *_t3298 = malloc(sizeof(U32));
            *_t3298 = 1;
            (void)_t3298;
            Expr *_t3299 = expr_get_child(stmt, DEREF(_t3298));
            (void)_t3299;
            Str *arg = expr_get_str_val(_t3299);
            (void)arg;
            Str *_t3300 = Str_lit("link", 4ULL);
            (void)_t3300;
            Bool _t3301; { Bool *_hp = (Bool *)Str_eq(fname, _t3300); _t3301 = *_hp; free(_hp); }
            (void)_t3301;
            Str_delete(_t3300, &(Bool){1});
            if (_t3301) {
                Str *_t3288 = Str_lit(" -l", 3ULL);
                (void)_t3288;
                Str *_t3289 = Str_concat(link_flags, _t3288);
                (void)_t3289;
                Str_delete(_t3288, &(Bool){1});
                link_flags = Str_concat(_t3289, arg);
                Str_delete(_t3289, &(Bool){1});
            } else {
                Str *_t3294 = Str_lit("link_c", 6ULL);
                (void)_t3294;
                Bool _t3295; { Bool *_hp = (Bool *)Str_eq(fname, _t3294); _t3295 = *_hp; free(_hp); }
                (void)_t3295;
                Str_delete(_t3294, &(Bool){1});
                if (_t3295) {
                    U64 _t3291; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t3291 = *_hp; free(_hp); }
                    (void)_t3291;
                    U64 _t3292 = 0;
                    (void)_t3292;
                    Bool _t3293; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3291}, &(U64){_t3292}); _t3293 = *_hp; free(_hp); }
                    (void)_t3293;
                    ;
                    ;
                    if (_t3293) {
                        Str *_t3290 = Str_lit(" ", 1ULL);
                        (void)_t3290;
                        link_c_paths = Str_concat(link_c_paths, _t3290);
                        Str_delete(_t3290, &(Bool){1});
                    }
                    ;
                    link_c_paths = Str_concat(link_c_paths, arg);
                } else {
                    expr_vec_push(kept, stmt);
                }
                ;
            }
            U32_delete(_t3296, &(Bool){1});
            U32_delete(_t3298, &(Bool){1});
            ;
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t3319 = 1;
        (void)_t3319;
        U32 _t3320 = U32_add(DEREF(i), _t3319);
        (void)_t3320;
        ;
        *i = _t3320;
        ;
    }
    U32_delete(i, &(Bool){1});
    expr_swap_children(ast, kept);
    Vec_delete(kept, &(Bool){1});
    TypeScope *scope = tscope_new(NULL);
    (void)scope;
    I32 _t3607 = init_declarations(ast, scope);
    (void)_t3607;
    ;
    I32 type_errors = type_check(ast, scope, cur_mode);
    (void)type_errors;
    TypeScope_delete(scope, &(Bool){1});
    I32 _t3608 = 0;
    (void)_t3608;
    Bool _t3609; { Bool *_hp = (Bool *)I32_gt(&(I32){type_errors}, &(I32){_t3608}); _t3609 = *_hp; free(_hp); }
    (void)_t3609;
    ;
    if (_t3609) {
        Str *_t3321 = Str_lit("Str", 3ULL);
        (void)_t3321;
        U64 _t3322; { U64 *_hp = (U64 *)Str_size(); _t3322 = *_hp; free(_hp); }
        (void)_t3322;
        U64 _t3323 = 1;
        (void)_t3323;
        Array *_va68 = Array_new(_t3321, &(U64){_t3322}, &(U64){_t3323});
        (void)_va68;
        Str_delete(_t3321, &(Bool){1});
        ;
        ;
        Str *_t3324 = I32_to_str(&(I32){type_errors});
        (void)_t3324;
        Str *_t3325 = Str_lit(" type error(s) found", 20ULL);
        (void)_t3325;
        U64 _t3326 = 0;
        (void)_t3326;
        Str *_t3327 = Str_concat(_t3324, _t3325);
        (void)_t3327;
        Str_delete(_t3324, &(Bool){1});
        Str_delete(_t3325, &(Bool){1});
        Array_set(_va68, &(U64){_t3326}, _t3327);
        ;
        Str *_t3328 = Str_lit("src/til.til:440:15", 18ULL);
        (void)_t3328;
        panic(_t3328, _va68);
        Str_delete(_t3328, &(Bool){1});
    }
    ;
    ;
    Str *_t3610 = Str_lit("test", 4ULL);
    (void)_t3610;
    Mode *_t3611 = mode_test();
    (void)_t3611;
    Bool _t3612; { Bool *_hp = (Bool *)Str_eq(command, _t3610); _t3612 = *_hp; free(_hp); }
    (void)_t3612;
    Str_delete(_t3610, &(Bool){1});
    Bool _t3613 = mode_eq(cur_mode, _t3611);
    (void)_t3613;
    Mode_delete(_t3611, &(Bool){1});
    Mode *_t3614 = mode_pure();
    (void)_t3614;
    Bool _t3615 = Bool_or(_t3612, _t3613);
    (void)_t3615;
    ;
    ;
    Bool _t3616 = mode_eq(cur_mode, _t3614);
    (void)_t3616;
    Mode_delete(_t3614, &(Bool){1});
    Mode *_t3617 = mode_pura();
    (void)_t3617;
    Bool _t3618 = Bool_or(_t3615, _t3616);
    (void)_t3618;
    ;
    ;
    Bool _t3619 = mode_eq(cur_mode, _t3617);
    (void)_t3619;
    Mode_delete(_t3617, &(Bool){1});
    Bool run_tests = Bool_or(_t3618, _t3619);
    (void)run_tests;
    ;
    ;
    precomp(ast);
    Str *_t3620 = Str_lit("translate", 9ULL);
    (void)_t3620;
    Str *_t3621 = Str_lit("build", 5ULL);
    (void)_t3621;
    Bool _t3622; { Bool *_hp = (Bool *)Str_eq(command, _t3620); _t3622 = *_hp; free(_hp); }
    (void)_t3622;
    Str_delete(_t3620, &(Bool){1});
    Bool _t3623; { Bool *_hp = (Bool *)Str_eq(command, _t3621); _t3623 = *_hp; free(_hp); }
    (void)_t3623;
    Str_delete(_t3621, &(Bool){1});
    Bool _t3624 = mode_is_lib_output(cur_mode);
    (void)_t3624;
    Bool _t3625 = Bool_or(_t3622, _t3623);
    (void)_t3625;
    ;
    ;
    Bool is_lib_target = Bool_and(_t3624, _t3625);
    (void)is_lib_target;
    ;
    ;
    U64 _t3626; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t3626 = *_hp; free(_hp); }
    (void)_t3626;
    U64 _t3627 = 0;
    (void)_t3627;
    Bool _t3628 = Bool_not(is_lib_target);
    (void)_t3628;
    ;
    Bool _t3629 = U64_eq(_t3626, _t3627);
    (void)_t3629;
    ;
    ;
    Bool _t3630 = Bool_and(_t3628, _t3629);
    (void)_t3630;
    ;
    ;
    if (_t3630) {
        scavenge(ast, cur_mode, run_tests);
    }
    ;
    I32 result = 0;
    (void)result;
    Str *user_c = Str_lit("", 0ULL);
    (void)user_c;
    U64 _t3631; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t3631 = *_hp; free(_hp); }
    (void)_t3631;
    U64 _t3632 = 0;
    (void)_t3632;
    Bool _t3633; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3631}, &(U64){_t3632}); _t3633 = *_hp; free(_hp); }
    (void)_t3633;
    ;
    ;
    if (_t3633) {
        user_c = Str_clone(link_c_paths);
    }
    ;
    Str_delete(link_c_paths, &(Bool){1});
    Str *_t3634 = Str_lit("Str", 3ULL);
    (void)_t3634;
    U64 _t3635; { U64 *_hp = (U64 *)Str_size(); _t3635 = *_hp; free(_hp); }
    (void)_t3635;
    Vec *user_argv = Vec_new(_t3634, &(U64){_t3635});
    (void)user_argv;
    Str_delete(_t3634, &(Bool){1});
    ;
    U64 _t3636 = 1;
    (void)_t3636;
    U64 *ai = malloc(sizeof(U64)); *ai = U64_add(DEREF(path_idx), _t3636);
    (void)ai;
    ;
    U64_delete(path_idx, &(Bool){1});
    while (1) {
        U64 _t3345; { U64 *_hp = (U64 *)Array_len(args); _t3345 = *_hp; free(_hp); }
        (void)_t3345;
        Bool _wcond3329; { Bool *_hp = (Bool *)U64_lt(ai, &(U64){_t3345}); _wcond3329 = *_hp; free(_hp); }
        (void)_wcond3329;
        ;
        if (_wcond3329) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, ai);
        (void)arg;
        Str *_t3346 = Str_lit("-l", 2ULL);
        (void)_t3346;
        Bool _t3347; { Bool *_hp = (Bool *)Str_starts_with(arg, _t3346); _t3347 = *_hp; free(_hp); }
        (void)_t3347;
        Str_delete(_t3346, &(Bool){1});
        if (_t3347) {
            U64 _t3332 = 2;
            (void)_t3332;
            U64 _t3333; { U64 *_hp = (U64 *)Str_len(arg); _t3333 = *_hp; free(_hp); }
            (void)_t3333;
            Str *lib = Str_substr(arg, &(U64){_t3332}, &(U64){_t3333});
            (void)lib;
            ;
            ;
            U64 _t3334; { U64 *_hp = (U64 *)Str_len(lib); _t3334 = *_hp; free(_hp); }
            (void)_t3334;
            U64 _t3335 = 0;
            (void)_t3335;
            U64 _t3336 = 1;
            (void)_t3336;
            U64 _t3337 = U64_add(DEREF(ai), _t3336);
            (void)_t3337;
            ;
            U64 _t3338; { U64 *_hp = (U64 *)Array_len(args); _t3338 = *_hp; free(_hp); }
            (void)_t3338;
            Bool _t3339 = U64_eq(_t3334, _t3335);
            (void)_t3339;
            ;
            ;
            Bool _t3340; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3337}, &(U64){_t3338}); _t3340 = *_hp; free(_hp); }
            (void)_t3340;
            ;
            ;
            Bool _t3341 = Bool_and(_t3339, _t3340);
            (void)_t3341;
            ;
            ;
            if (_t3341) {
                U64 _t3330 = 1;
                (void)_t3330;
                U64 _t3331 = U64_add(DEREF(ai), _t3330);
                (void)_t3331;
                ;
                *ai = _t3331;
                ;
                Str *next_arg = Array_get(args, ai);
                (void)next_arg;
                lib = Str_clone(next_arg);
            }
            ;
            Str *_t3342 = Str_lit(" -l", 3ULL);
            (void)_t3342;
            Str *_t3343 = Str_concat(link_flags, _t3342);
            (void)_t3343;
            Str_delete(_t3342, &(Bool){1});
            link_flags = Str_concat(_t3343, lib);
            Str_delete(_t3343, &(Bool){1});
            Str_delete(lib, &(Bool){1});
        } else {
            Str *_t3344 = Str_clone(arg);
            (void)_t3344;
            Vec_push(user_argv, _t3344);
        }
        ;
        U64 _t3348 = 1;
        (void)_t3348;
        U64 _t3349 = U64_add(DEREF(ai), _t3348);
        (void)_t3349;
        ;
        *ai = _t3349;
        ;
    }
    U64_delete(ai, &(Bool){1});
    Array_delete(args, &(Bool){1});
    Str *lflags = Str_lit("", 0ULL);
    (void)lflags;
    U64 _t3637; { U64 *_hp = (U64 *)Str_len(link_flags); _t3637 = *_hp; free(_hp); }
    (void)_t3637;
    U64 _t3638 = 0;
    (void)_t3638;
    Bool _t3639; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3637}, &(U64){_t3638}); _t3639 = *_hp; free(_hp); }
    (void)_t3639;
    ;
    ;
    if (_t3639) {
        lflags = Str_clone(link_flags);
    }
    ;
    Str_delete(link_flags, &(Bool){1});
    Bool is_lib_mode = mode_is_lib(cur_mode);
    (void)is_lib_mode;
    Str *_t3640 = Str_lit("interpret", 9ULL);
    (void)_t3640;
    Str *_t3641 = Str_lit("test", 4ULL);
    (void)_t3641;
    Bool _t3642; { Bool *_hp = (Bool *)Str_eq(command, _t3640); _t3642 = *_hp; free(_hp); }
    (void)_t3642;
    Str_delete(_t3640, &(Bool){1});
    Bool _t3643; { Bool *_hp = (Bool *)Str_eq(command, _t3641); _t3643 = *_hp; free(_hp); }
    (void)_t3643;
    Str_delete(_t3641, &(Bool){1});
    Bool _t3644 = Bool_or(_t3642, _t3643);
    (void)_t3644;
    ;
    ;
    if (_t3644) {
        Str *_t3356 = Str_lit("interpret", 9ULL);
        (void)_t3356;
        Bool _t3357; { Bool *_hp = (Bool *)Str_eq(command, _t3356); _t3357 = *_hp; free(_hp); }
        (void)_t3357;
        Str_delete(_t3356, &(Bool){1});
        Bool _t3358 = Bool_and(is_lib_mode, _t3357);
        (void)_t3358;
        ;
        if (_t3358) {
            Str *_t3350 = Str_lit("Str", 3ULL);
            (void)_t3350;
            U64 _t3351; { U64 *_hp = (U64 *)Str_size(); _t3351 = *_hp; free(_hp); }
            (void)_t3351;
            U64 _t3352 = 1;
            (void)_t3352;
            Array *_va69 = Array_new(_t3350, &(U64){_t3351}, &(U64){_t3352});
            (void)_va69;
            Str_delete(_t3350, &(Bool){1});
            ;
            ;
            U64 _t3353 = 0;
            (void)_t3353;
            Str *_t3354 = Str_lit("cannot interpret a library — use translate or build", 53ULL);
            (void)_t3354;
            Array_set(_va69, &(U64){_t3353}, _t3354);
            ;
            Str *_t3355 = Str_lit("src/til.til:494:19", 18ULL);
            (void)_t3355;
            panic(_t3355, _va69);
            Str_delete(_t3355, &(Bool){1});
        }
        ;
        I32 _t3359 = til_interpret_v(ast, cur_mode, run_tests, path, user_c, ext_c_path, lflags, user_argv);
        (void)_t3359;
        result = _t3359;
        ;
    } else {
        Str *_t3561 = Str_lit("translate", 9ULL);
        (void)_t3561;
        Str *_t3562 = Str_lit("build", 5ULL);
        (void)_t3562;
        Bool _t3563; { Bool *_hp = (Bool *)Str_eq(command, _t3561); _t3563 = *_hp; free(_hp); }
        (void)_t3563;
        Str_delete(_t3561, &(Bool){1});
        Bool _t3564; { Bool *_hp = (Bool *)Str_eq(command, _t3562); _t3564 = *_hp; free(_hp); }
        (void)_t3564;
        Str_delete(_t3562, &(Bool){1});
        Str *_t3565 = Str_lit("run", 3ULL);
        (void)_t3565;
        Bool _t3566 = Bool_or(_t3563, _t3564);
        (void)_t3566;
        ;
        ;
        Bool _t3567; { Bool *_hp = (Bool *)Str_eq(command, _t3565); _t3567 = *_hp; free(_hp); }
        (void)_t3567;
        Str_delete(_t3565, &(Bool){1});
        Bool _t3568 = Bool_or(_t3566, _t3567);
        (void)_t3568;
        ;
        ;
        if (_t3568) {
            Str *_t3485 = Str_lit("run", 3ULL);
            (void)_t3485;
            Bool _t3486; { Bool *_hp = (Bool *)Str_eq(command, _t3485); _t3486 = *_hp; free(_hp); }
            (void)_t3486;
            Str_delete(_t3485, &(Bool){1});
            Bool _t3487 = Bool_and(is_lib_mode, _t3486);
            (void)_t3487;
            ;
            if (_t3487) {
                Str *_t3360 = Str_lit("Str", 3ULL);
                (void)_t3360;
                U64 _t3361; { U64 *_hp = (U64 *)Str_size(); _t3361 = *_hp; free(_hp); }
                (void)_t3361;
                U64 _t3362 = 1;
                (void)_t3362;
                Array *_va70 = Array_new(_t3360, &(U64){_t3361}, &(U64){_t3362});
                (void)_va70;
                Str_delete(_t3360, &(Bool){1});
                ;
                ;
                U64 _t3363 = 0;
                (void)_t3363;
                Str *_t3364 = Str_lit("cannot run a library — use translate or build", 47ULL);
                (void)_t3364;
                Array_set(_va70, &(U64){_t3363}, _t3364);
                ;
                Str *_t3365 = Str_lit("src/til.til:500:19", 18ULL);
                (void)_t3365;
                panic(_t3365, _va70);
                Str_delete(_t3365, &(Bool){1});
            }
            ;
            Str *_t3488 = Str_lit("/", 1ULL);
            (void)_t3488;
            I64 *last_slash = Str_rfind(path, _t3488);
            (void)last_slash;
            Str_delete(_t3488, &(Bool){1});
            Str *basename = Str_clone(path);
            (void)basename;
            I64 _t3489 = 0;
            (void)_t3489;
            Bool _t3490; { Bool *_hp = (Bool *)I64_gte(last_slash, &(I64){_t3489}); _t3490 = *_hp; free(_hp); }
            (void)_t3490;
            ;
            if (_t3490) {
                I64 _t3366 = 1;
                (void)_t3366;
                I64 _t3367 = I64_add(DEREF(last_slash), _t3366);
                (void)_t3367;
                ;
                U64 _t3368; { U64 *_hp = (U64 *)Str_len(path); _t3368 = *_hp; free(_hp); }
                (void)_t3368;
                U64 _t3369 = I64_to_u64(DEREF(last_slash));
                (void)_t3369;
                U64 _t3370 = U64_sub(_t3368, _t3369);
                (void)_t3370;
                ;
                ;
                U64 _t3371 = 1;
                (void)_t3371;
                U64 _t3372 = I64_to_u64(_t3367);
                (void)_t3372;
                ;
                U64 _t3373 = U64_sub(_t3370, _t3371);
                (void)_t3373;
                ;
                ;
                basename = Str_substr(path, &(U64){_t3372}, &(U64){_t3373});
                ;
                ;
            }
            ;
            I64_delete(last_slash, &(Bool){1});
            U64 name_len; { U64 *_hp = (U64 *)Str_len(basename); name_len = *_hp; free(_hp); }
            (void)name_len;
            Str *_t3491 = Str_lit(".til", 4ULL);
            (void)_t3491;
            Bool _t3492; { Bool *_hp = (Bool *)Str_ends_with(basename, _t3491); _t3492 = *_hp; free(_hp); }
            (void)_t3492;
            Str_delete(_t3491, &(Bool){1});
            if (_t3492) {
                U64 _t3374 = 4;
                (void)_t3374;
                U64 _t3375 = U64_sub(name_len, _t3374);
                (void)_t3375;
                ;
                name_len = _t3375;
                ;
            }
            ;
            U64 _t3493 = 0;
            (void)_t3493;
            Str *name = Str_substr(basename, &(U64){_t3493}, &(U64){name_len});
            (void)name;
            ;
            Str_delete(basename, &(Bool){1});
            ;
            Str *_t3494 = Str_lit("gen/til/", 8ULL);
            (void)_t3494;
            Str *_t3495 = Str_concat(_t3494, name);
            (void)_t3495;
            Str_delete(_t3494, &(Bool){1});
            Str *_t3496 = Str_lit(".c", 2ULL);
            (void)_t3496;
            Str *c_path = Str_concat(_t3495, _t3496);
            (void)c_path;
            Str_delete(_t3495, &(Bool){1});
            Str_delete(_t3496, &(Bool){1});
            U64 _t3497; { U64 *_hp = (U64 *)Str_len(custom_c); _t3497 = *_hp; free(_hp); }
            (void)_t3497;
            U64 _t3498 = 0;
            (void)_t3498;
            Bool _t3499; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3497}, &(U64){_t3498}); _t3499 = *_hp; free(_hp); }
            (void)_t3499;
            ;
            ;
            if (_t3499) {
                c_path = Str_clone(custom_c);
            }
            ;
            Str *_t3500 = Str_lit("bin/til/", 8ULL);
            (void)_t3500;
            Str *bin_path = Str_concat(_t3500, name);
            (void)bin_path;
            Str_delete(_t3500, &(Bool){1});
            U64 _t3501; { U64 *_hp = (U64 *)Str_len(custom_bin); _t3501 = *_hp; free(_hp); }
            (void)_t3501;
            U64 _t3502 = 0;
            (void)_t3502;
            Bool _t3503; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3501}, &(U64){_t3502}); _t3503 = *_hp; free(_hp); }
            (void)_t3503;
            ;
            ;
            if (_t3503) {
                bin_path = Str_clone(custom_bin);
            }
            ;
            Str *_t3504 = Str_lit("run", 3ULL);
            (void)_t3504;
            Bool _t3505; { Bool *_hp = (Bool *)Str_eq(command, _t3504); _t3505 = *_hp; free(_hp); }
            (void)_t3505;
            Str_delete(_t3504, &(Bool){1});
            Bool _t3506 = mode_is_lib_output(cur_mode);
            (void)_t3506;
            Bool _t3507 = Bool_not(_t3505);
            (void)_t3507;
            ;
            Bool do_lib = Bool_and(_t3506, _t3507);
            (void)do_lib;
            ;
            ;
            if (do_lib) {
                Str *_t3376 = Str_lit("mkdir -p gen/til gen/lib", 24ULL);
                (void)_t3376;
                I32 _t3377 = til_system(_t3376);
                (void)_t3377;
                Str_delete(_t3376, &(Bool){1});
                ;
            } else {
                Str *_t3382 = Str_lit("/", 1ULL);
                (void)_t3382;
                I64 cp_slash; { I64 *_hp = (I64 *)Str_rfind(c_path, _t3382); cp_slash = *_hp; free(_hp); }
                (void)cp_slash;
                Str_delete(_t3382, &(Bool){1});
                Str *_t3383 = Str_lit("/", 1ULL);
                (void)_t3383;
                I64 bp_slash; { I64 *_hp = (I64 *)Str_rfind(bin_path, _t3383); bp_slash = *_hp; free(_hp); }
                (void)bp_slash;
                Str_delete(_t3383, &(Bool){1});
                Str *cp_dir = Str_lit("gen/til", 7ULL);
                (void)cp_dir;
                I64 _t3384 = 0;
                (void)_t3384;
                Bool _t3385; { Bool *_hp = (Bool *)I64_gt(&(I64){cp_slash}, &(I64){_t3384}); _t3385 = *_hp; free(_hp); }
                (void)_t3385;
                ;
                if (_t3385) {
                    U64 _t3378 = 0;
                    (void)_t3378;
                    U64 _t3379 = I64_to_u64(cp_slash);
                    (void)_t3379;
                    cp_dir = Str_substr(c_path, &(U64){_t3378}, &(U64){_t3379});
                    ;
                    ;
                }
                ;
                ;
                Str *bp_dir = Str_lit("bin/til", 7ULL);
                (void)bp_dir;
                I64 _t3386 = 0;
                (void)_t3386;
                Bool _t3387; { Bool *_hp = (Bool *)I64_gt(&(I64){bp_slash}, &(I64){_t3386}); _t3387 = *_hp; free(_hp); }
                (void)_t3387;
                ;
                if (_t3387) {
                    U64 _t3380 = 0;
                    (void)_t3380;
                    U64 _t3381 = I64_to_u64(bp_slash);
                    (void)_t3381;
                    bp_dir = Str_substr(bin_path, &(U64){_t3380}, &(U64){_t3381});
                    ;
                    ;
                }
                ;
                ;
                Str *_t3388 = Str_lit("mkdir -p ", 9ULL);
                (void)_t3388;
                Str *_t3389 = Str_concat(_t3388, cp_dir);
                (void)_t3389;
                Str_delete(_t3388, &(Bool){1});
                Str_delete(cp_dir, &(Bool){1});
                Str *_t3390 = Str_lit(" ", 1ULL);
                (void)_t3390;
                Str *_t3391 = Str_concat(_t3389, _t3390);
                (void)_t3391;
                Str_delete(_t3389, &(Bool){1});
                Str_delete(_t3390, &(Bool){1});
                Str *_t3392 = Str_concat(_t3391, bp_dir);
                (void)_t3392;
                Str_delete(_t3391, &(Bool){1});
                Str_delete(bp_dir, &(Bool){1});
                I32 _t3393 = til_system(_t3392);
                (void)_t3393;
                Str_delete(_t3392, &(Bool){1});
                ;
            }
            I32 _t3508 = build(ast, cur_mode, run_tests, path, c_path);
            (void)_t3508;
            result = _t3508;
            ;
            I32 _t3509 = 0;
            (void)_t3509;
            Bool _t3510 = I32_eq(result, _t3509);
            (void)_t3510;
            ;
            Bool _t3511 = Bool_and(_t3510, do_lib);
            (void)_t3511;
            ;
            if (_t3511) {
                Str *_t3450 = Str_lit("gen/til/", 8ULL);
                (void)_t3450;
                Str *_t3451 = Str_concat(_t3450, name);
                (void)_t3451;
                Str_delete(_t3450, &(Bool){1});
                Str *_t3452 = Str_lit(".h", 2ULL);
                (void)_t3452;
                Str *h_path = Str_concat(_t3451, _t3452);
                (void)h_path;
                Str_delete(_t3451, &(Bool){1});
                Str_delete(_t3452, &(Bool){1});
                Str *_t3453 = Str_lit("gen/til/", 8ULL);
                (void)_t3453;
                Str *_t3454 = Str_concat(_t3453, name);
                (void)_t3454;
                Str_delete(_t3453, &(Bool){1});
                Str *_t3455 = Str_lit(".til", 4ULL);
                (void)_t3455;
                Str *til_path = Str_concat(_t3454, _t3455);
                (void)til_path;
                Str_delete(_t3454, &(Bool){1});
                Str_delete(_t3455, &(Bool){1});
                I32 _t3456 = build_header(ast, h_path);
                (void)_t3456;
                result = _t3456;
                ;
                I32 _t3457 = 0;
                (void)_t3457;
                Bool _t3458 = I32_eq(result, _t3457);
                (void)_t3458;
                ;
                if (_t3458) {
                    I32 _t3394 = build_til_binding(ast, til_path, name);
                    (void)_t3394;
                    result = _t3394;
                    ;
                }
                ;
                I32 _t3459 = 0;
                (void)_t3459;
                Str *_t3460 = Str_lit("translate", 9ULL);
                (void)_t3460;
                Bool _t3461 = I32_eq(result, _t3459);
                (void)_t3461;
                ;
                Bool _t3462; { Bool *_hp = (Bool *)Str_eq(command, _t3460); _t3462 = *_hp; free(_hp); }
                (void)_t3462;
                Str_delete(_t3460, &(Bool){1});
                Bool _t3463 = Bool_and(_t3461, _t3462);
                (void)_t3463;
                ;
                ;
                if (_t3463) {
                    Str *_t3395 = Str_lit("Str", 3ULL);
                    (void)_t3395;
                    U64 _t3396; { U64 *_hp = (U64 *)Str_size(); _t3396 = *_hp; free(_hp); }
                    (void)_t3396;
                    U64 _t3397 = 1;
                    (void)_t3397;
                    Array *_va71 = Array_new(_t3395, &(U64){_t3396}, &(U64){_t3397});
                    (void)_va71;
                    Str_delete(_t3395, &(Bool){1});
                    ;
                    ;
                    Str *_t3398 = Str_lit("Generated: ", 11ULL);
                    (void)_t3398;
                    U64 _t3399 = 0;
                    (void)_t3399;
                    Str *_t3400 = Str_concat(_t3398, c_path);
                    (void)_t3400;
                    Str_delete(_t3398, &(Bool){1});
                    Array_set(_va71, &(U64){_t3399}, _t3400);
                    ;
                    println(_va71);
                    Str *_t3401 = Str_lit("Str", 3ULL);
                    (void)_t3401;
                    U64 _t3402; { U64 *_hp = (U64 *)Str_size(); _t3402 = *_hp; free(_hp); }
                    (void)_t3402;
                    U64 _t3403 = 1;
                    (void)_t3403;
                    Array *_va72 = Array_new(_t3401, &(U64){_t3402}, &(U64){_t3403});
                    (void)_va72;
                    Str_delete(_t3401, &(Bool){1});
                    ;
                    ;
                    Str *_t3404 = Str_lit("Generated: ", 11ULL);
                    (void)_t3404;
                    U64 _t3405 = 0;
                    (void)_t3405;
                    Str *_t3406 = Str_concat(_t3404, h_path);
                    (void)_t3406;
                    Str_delete(_t3404, &(Bool){1});
                    Array_set(_va72, &(U64){_t3405}, _t3406);
                    ;
                    println(_va72);
                    Str *_t3407 = Str_lit("Str", 3ULL);
                    (void)_t3407;
                    U64 _t3408; { U64 *_hp = (U64 *)Str_size(); _t3408 = *_hp; free(_hp); }
                    (void)_t3408;
                    U64 _t3409 = 1;
                    (void)_t3409;
                    Array *_va73 = Array_new(_t3407, &(U64){_t3408}, &(U64){_t3409});
                    (void)_va73;
                    Str_delete(_t3407, &(Bool){1});
                    ;
                    ;
                    Str *_t3410 = Str_lit("Generated: ", 11ULL);
                    (void)_t3410;
                    U64 _t3411 = 0;
                    (void)_t3411;
                    Str *_t3412 = Str_concat(_t3410, til_path);
                    (void)_t3412;
                    Str_delete(_t3410, &(Bool){1});
                    Array_set(_va73, &(U64){_t3411}, _t3412);
                    ;
                    println(_va73);
                }
                ;
                I32 _t3464 = 0;
                (void)_t3464;
                Str *_t3465 = Str_lit("build", 5ULL);
                (void)_t3465;
                Bool _t3466 = I32_eq(result, _t3464);
                (void)_t3466;
                ;
                Bool _t3467; { Bool *_hp = (Bool *)Str_eq(command, _t3465); _t3467 = *_hp; free(_hp); }
                (void)_t3467;
                Str_delete(_t3465, &(Bool){1});
                Bool _t3468 = Bool_and(_t3466, _t3467);
                (void)_t3468;
                ;
                ;
                if (_t3468) {
                    I32 _t3447 = til_compile_lib(c_path, name, ext_c_path, user_c, lflags);
                    (void)_t3447;
                    result = _t3447;
                    ;
                    I32 _t3448 = 0;
                    (void)_t3448;
                    Bool _t3449 = I32_eq(result, _t3448);
                    (void)_t3449;
                    ;
                    if (_t3449) {
                        Str *_t3413 = Str_lit("Str", 3ULL);
                        (void)_t3413;
                        U64 _t3414; { U64 *_hp = (U64 *)Str_size(); _t3414 = *_hp; free(_hp); }
                        (void)_t3414;
                        U64 _t3415 = 1;
                        (void)_t3415;
                        Array *_va74 = Array_new(_t3413, &(U64){_t3414}, &(U64){_t3415});
                        (void)_va74;
                        Str_delete(_t3413, &(Bool){1});
                        ;
                        ;
                        Str *_t3416 = Str_lit("Generated: ", 11ULL);
                        (void)_t3416;
                        U64 _t3417 = 0;
                        (void)_t3417;
                        Str *_t3418 = Str_concat(_t3416, c_path);
                        (void)_t3418;
                        Str_delete(_t3416, &(Bool){1});
                        Array_set(_va74, &(U64){_t3417}, _t3418);
                        ;
                        println(_va74);
                        Str *_t3419 = Str_lit("Str", 3ULL);
                        (void)_t3419;
                        U64 _t3420; { U64 *_hp = (U64 *)Str_size(); _t3420 = *_hp; free(_hp); }
                        (void)_t3420;
                        U64 _t3421 = 1;
                        (void)_t3421;
                        Array *_va75 = Array_new(_t3419, &(U64){_t3420}, &(U64){_t3421});
                        (void)_va75;
                        Str_delete(_t3419, &(Bool){1});
                        ;
                        ;
                        Str *_t3422 = Str_lit("Generated: ", 11ULL);
                        (void)_t3422;
                        U64 _t3423 = 0;
                        (void)_t3423;
                        Str *_t3424 = Str_concat(_t3422, h_path);
                        (void)_t3424;
                        Str_delete(_t3422, &(Bool){1});
                        Array_set(_va75, &(U64){_t3423}, _t3424);
                        ;
                        println(_va75);
                        Str *_t3425 = Str_lit("Str", 3ULL);
                        (void)_t3425;
                        U64 _t3426; { U64 *_hp = (U64 *)Str_size(); _t3426 = *_hp; free(_hp); }
                        (void)_t3426;
                        U64 _t3427 = 1;
                        (void)_t3427;
                        Array *_va76 = Array_new(_t3425, &(U64){_t3426}, &(U64){_t3427});
                        (void)_va76;
                        Str_delete(_t3425, &(Bool){1});
                        ;
                        ;
                        Str *_t3428 = Str_lit("Generated: ", 11ULL);
                        (void)_t3428;
                        U64 _t3429 = 0;
                        (void)_t3429;
                        Str *_t3430 = Str_concat(_t3428, til_path);
                        (void)_t3430;
                        Str_delete(_t3428, &(Bool){1});
                        Array_set(_va76, &(U64){_t3429}, _t3430);
                        ;
                        println(_va76);
                        Str *_t3431 = Str_lit("Str", 3ULL);
                        (void)_t3431;
                        U64 _t3432; { U64 *_hp = (U64 *)Str_size(); _t3432 = *_hp; free(_hp); }
                        (void)_t3432;
                        U64 _t3433 = 1;
                        (void)_t3433;
                        Array *_va77 = Array_new(_t3431, &(U64){_t3432}, &(U64){_t3433});
                        (void)_va77;
                        Str_delete(_t3431, &(Bool){1});
                        ;
                        ;
                        Str *_t3434 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t3434;
                        Str *_t3435 = Str_concat(_t3434, name);
                        (void)_t3435;
                        Str_delete(_t3434, &(Bool){1});
                        Str *_t3436 = Str_lit(".so", 3ULL);
                        (void)_t3436;
                        U64 _t3437 = 0;
                        (void)_t3437;
                        Str *_t3438 = Str_concat(_t3435, _t3436);
                        (void)_t3438;
                        Str_delete(_t3435, &(Bool){1});
                        Str_delete(_t3436, &(Bool){1});
                        Array_set(_va77, &(U64){_t3437}, _t3438);
                        ;
                        println(_va77);
                        Str *_t3439 = Str_lit("Str", 3ULL);
                        (void)_t3439;
                        U64 _t3440; { U64 *_hp = (U64 *)Str_size(); _t3440 = *_hp; free(_hp); }
                        (void)_t3440;
                        U64 _t3441 = 1;
                        (void)_t3441;
                        Array *_va78 = Array_new(_t3439, &(U64){_t3440}, &(U64){_t3441});
                        (void)_va78;
                        Str_delete(_t3439, &(Bool){1});
                        ;
                        ;
                        Str *_t3442 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t3442;
                        Str *_t3443 = Str_concat(_t3442, name);
                        (void)_t3443;
                        Str_delete(_t3442, &(Bool){1});
                        Str *_t3444 = Str_lit(".a", 2ULL);
                        (void)_t3444;
                        U64 _t3445 = 0;
                        (void)_t3445;
                        Str *_t3446 = Str_concat(_t3443, _t3444);
                        (void)_t3446;
                        Str_delete(_t3443, &(Bool){1});
                        Str_delete(_t3444, &(Bool){1});
                        Array_set(_va78, &(U64){_t3445}, _t3446);
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
            I32 _t3512 = 0;
            (void)_t3512;
            Bool _t3513 = I32_eq(result, _t3512);
            (void)_t3513;
            ;
            Bool _t3514 = Bool_not(do_lib);
            (void)_t3514;
            Str *_t3515 = Str_lit("translate", 9ULL);
            (void)_t3515;
            Bool _t3516 = Bool_and(_t3513, _t3514);
            (void)_t3516;
            ;
            ;
            Bool _t3517; { Bool *_hp = (Bool *)Str_eq(command, _t3515); _t3517 = *_hp; free(_hp); }
            (void)_t3517;
            Str_delete(_t3515, &(Bool){1});
            Bool _t3518 = Bool_and(_t3516, _t3517);
            (void)_t3518;
            ;
            ;
            if (_t3518) {
                Str *_t3469 = Str_lit("Str", 3ULL);
                (void)_t3469;
                U64 _t3470; { U64 *_hp = (U64 *)Str_size(); _t3470 = *_hp; free(_hp); }
                (void)_t3470;
                U64 _t3471 = 1;
                (void)_t3471;
                Array *_va79 = Array_new(_t3469, &(U64){_t3470}, &(U64){_t3471});
                (void)_va79;
                Str_delete(_t3469, &(Bool){1});
                ;
                ;
                Str *_t3472 = Str_lit("Generated: ", 11ULL);
                (void)_t3472;
                U64 _t3473 = 0;
                (void)_t3473;
                Str *_t3474 = Str_concat(_t3472, c_path);
                (void)_t3474;
                Str_delete(_t3472, &(Bool){1});
                Array_set(_va79, &(U64){_t3473}, _t3474);
                ;
                println(_va79);
            }
            ;
            I32 _t3519 = 0;
            (void)_t3519;
            Bool _t3520 = I32_eq(result, _t3519);
            (void)_t3520;
            ;
            Bool _t3521 = Bool_not(do_lib);
            (void)_t3521;
            Str *_t3522 = Str_lit("translate", 9ULL);
            (void)_t3522;
            Bool _t3523; { Bool *_hp = (Bool *)Str_eq(command, _t3522); _t3523 = *_hp; free(_hp); }
            (void)_t3523;
            Str_delete(_t3522, &(Bool){1});
            Bool _t3524 = Bool_and(_t3520, _t3521);
            (void)_t3524;
            ;
            ;
            Bool _t3525 = Bool_not(_t3523);
            (void)_t3525;
            ;
            Bool _t3526 = Bool_and(_t3524, _t3525);
            (void)_t3526;
            ;
            ;
            if (_t3526) {
                I32 _t3475 = til_compile_c(c_path, bin_path, ext_c_path, user_c, lflags);
                (void)_t3475;
                result = _t3475;
                ;
            }
            ;
            Str_delete(c_path, &(Bool){1});
            I32 _t3527 = 0;
            (void)_t3527;
            Bool _t3528 = I32_eq(result, _t3527);
            (void)_t3528;
            ;
            Bool _t3529 = Bool_not(do_lib);
            (void)_t3529;
            ;
            Str *_t3530 = Str_lit("run", 3ULL);
            (void)_t3530;
            Bool _t3531 = Bool_and(_t3528, _t3529);
            (void)_t3531;
            ;
            ;
            Bool _t3532; { Bool *_hp = (Bool *)Str_eq(command, _t3530); _t3532 = *_hp; free(_hp); }
            (void)_t3532;
            Str_delete(_t3530, &(Bool){1});
            Bool _t3533 = Bool_and(_t3531, _t3532);
            (void)_t3533;
            ;
            ;
            if (_t3533) {
                Str *cmd = Str_clone(bin_path);
                (void)cmd;
                U64 *ui = malloc(sizeof(U64));
                *ui = 0;
                (void)ui;
                while (1) {
                    U64 _t3477; { U64 *_hp = (U64 *)Vec_len(user_argv); _t3477 = *_hp; free(_hp); }
                    (void)_t3477;
                    Bool _wcond3476; { Bool *_hp = (Bool *)U64_lt(ui, &(U64){_t3477}); _wcond3476 = *_hp; free(_hp); }
                    (void)_wcond3476;
                    ;
                    if (_wcond3476) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *uarg = Vec_get(user_argv, ui);
                    (void)uarg;
                    Str *_t3478 = Str_lit(" '", 2ULL);
                    (void)_t3478;
                    Str *_t3479 = Str_concat(cmd, _t3478);
                    (void)_t3479;
                    Str_delete(_t3478, &(Bool){1});
                    Str *_t3480 = Str_concat(_t3479, uarg);
                    (void)_t3480;
                    Str_delete(_t3479, &(Bool){1});
                    Str *_t3481 = Str_lit("'", 1ULL);
                    (void)_t3481;
                    cmd = Str_concat(_t3480, _t3481);
                    Str_delete(_t3480, &(Bool){1});
                    Str_delete(_t3481, &(Bool){1});
                    U64 _t3482 = 1;
                    (void)_t3482;
                    U64 _t3483 = U64_add(DEREF(ui), _t3482);
                    (void)_t3483;
                    ;
                    *ui = _t3483;
                    ;
                }
                U64_delete(ui, &(Bool){1});
                I32 _t3484 = til_system(cmd);
                (void)_t3484;
                Str_delete(cmd, &(Bool){1});
                result = _t3484;
                ;
            }
            ;
            Str_delete(bin_path, &(Bool){1});
        } else {
            Str *_t3559 = Str_lit("ast", 3ULL);
            (void)_t3559;
            Bool _t3560; { Bool *_hp = (Bool *)Str_eq(command, _t3559); _t3560 = *_hp; free(_hp); }
            (void)_t3560;
            Str_delete(_t3559, &(Bool){1});
            if (_t3560) {
                Mode *_t3546 = mode_none();
                (void)_t3546;
                Bool _t3547 = mode_eq(cur_mode, _t3546);
                (void)_t3547;
                Mode_delete(_t3546, &(Bool){1});
                Bool _t3548 = Bool_not(_t3547);
                (void)_t3548;
                ;
                if (_t3548) {
                    Str *_t3534 = Str_lit("Str", 3ULL);
                    (void)_t3534;
                    U64 _t3535; { U64 *_hp = (U64 *)Str_size(); _t3535 = *_hp; free(_hp); }
                    (void)_t3535;
                    U64 _t3536 = 1;
                    (void)_t3536;
                    Array *_va80 = Array_new(_t3534, &(U64){_t3535}, &(U64){_t3536});
                    (void)_va80;
                    Str_delete(_t3534, &(Bool){1});
                    ;
                    ;
                    Str *_t3537 = Str_lit("mode: ", 6ULL);
                    (void)_t3537;
                    Str *_t3538 = mode_name(cur_mode);
                    (void)_t3538;
                    U64 _t3539 = 0;
                    (void)_t3539;
                    Str *_t3540 = Str_concat(_t3537, _t3538);
                    (void)_t3540;
                    Str_delete(_t3537, &(Bool){1});
                    Str_delete(_t3538, &(Bool){1});
                    Array_set(_va80, &(U64){_t3539}, _t3540);
                    ;
                    println(_va80);
                } else {
                    Str *_t3541 = Str_lit("Str", 3ULL);
                    (void)_t3541;
                    U64 _t3542; { U64 *_hp = (U64 *)Str_size(); _t3542 = *_hp; free(_hp); }
                    (void)_t3542;
                    U64 _t3543 = 1;
                    (void)_t3543;
                    Array *_va81 = Array_new(_t3541, &(U64){_t3542}, &(U64){_t3543});
                    (void)_va81;
                    Str_delete(_t3541, &(Bool){1});
                    ;
                    ;
                    U64 _t3544 = 0;
                    (void)_t3544;
                    Str *_t3545 = Str_lit("mode: (none)", 12ULL);
                    (void)_t3545;
                    Array_set(_va81, &(U64){_t3544}, _t3545);
                    ;
                    println(_va81);
                }
                ;
                U32 _t3549 = 0;
                (void)_t3549;
                ast_print(ast, _t3549);
                ;
            } else {
                Str *_t3550 = Str_lit("Str", 3ULL);
                (void)_t3550;
                U64 _t3551; { U64 *_hp = (U64 *)Str_size(); _t3551 = *_hp; free(_hp); }
                (void)_t3551;
                U64 _t3552 = 1;
                (void)_t3552;
                Array *_va82 = Array_new(_t3550, &(U64){_t3551}, &(U64){_t3552});
                (void)_va82;
                Str_delete(_t3550, &(Bool){1});
                ;
                ;
                Str *_t3553 = Str_lit("error: unknown command '", 24ULL);
                (void)_t3553;
                Str *_t3554 = Str_concat(_t3553, command);
                (void)_t3554;
                Str_delete(_t3553, &(Bool){1});
                Str *_t3555 = Str_lit("'", 1ULL);
                (void)_t3555;
                U64 _t3556 = 0;
                (void)_t3556;
                Str *_t3557 = Str_concat(_t3554, _t3555);
                (void)_t3557;
                Str_delete(_t3554, &(Bool){1});
                Str_delete(_t3555, &(Bool){1});
                Array_set(_va82, &(U64){_t3556}, _t3557);
                ;
                println(_va82);
                usage();
                I32 _t3558 = 1;
                (void)_t3558;
                result = _t3558;
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
    I64 _t3645 = I32_to_i64(result);
    (void)_t3645;
    ;
    exit(_t3645);
    ;
    return 0;
}

