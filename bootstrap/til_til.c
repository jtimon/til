#include "til_til.h"

Mode * Mode_clone(Mode * self) {
    (void)self;
    Mode *_t3033 = malloc(sizeof(Mode));
    (void)_t3033;
    return _t3033;
}

U64 *Mode_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Mode);
    return r;
}

TypeScope * TypeScope_clone(TypeScope * self) {
    (void)self;
    TypeScope *_t3035 = malloc(sizeof(TypeScope));
    (void)_t3035;
    return _t3035;
}

U64 *TypeScope_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TypeScope);
    return r;
}

Vec * extract_imports(void * body) {
    (void)body;
    Str *_t3066 = Str_lit("Str", 3ULL);
    (void)_t3066;
    U64 _t3067; { U64 *_hp = (U64 *)Str_size(); _t3067 = *_hp; free(_hp); }
    (void)_t3067;
    Vec *paths = Vec_new(_t3066, &(U64){_t3067});
    (void)paths;
    Str_delete(_t3066, &(Bool){1});
    ;
    Vec *kept = expr_vec_new();
    (void)kept;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t3041 = expr_nchildren(body);
        (void)_t3041;
        Bool _wcond3037; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3041}); _wcond3037 = *_hp; free(_hp); }
        (void)_wcond3037;
        ;
        if (_wcond3037) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(body, DEREF(i));
        (void)stmt;
        I32 _t3042 = expr_get_tag(stmt);
        (void)_t3042;
        U32 _t3043 = expr_nchildren(stmt);
        (void)_t3043;
        U32 _t3044 = 2;
        (void)_t3044;
        Bool _t3045 = I32_eq(_t3042, DEREF(NODE_FCALL));
        (void)_t3045;
        ;
        Bool _t3046 = U32_eq(_t3043, _t3044);
        (void)_t3046;
        ;
        ;
        U32 *_t3047 = malloc(sizeof(U32));
        *_t3047 = 0;
        (void)_t3047;
        Expr *_t3048 = expr_get_child(stmt, DEREF(_t3047));
        (void)_t3048;
        I32 _t3049 = expr_get_tag(_t3048);
        (void)_t3049;
        U32_delete(_t3047, &(Bool){1});
        Bool _t3050 = Bool_and(_t3045, _t3046);
        (void)_t3050;
        ;
        ;
        Bool _t3051 = I32_eq(_t3049, DEREF(NODE_IDENT));
        (void)_t3051;
        ;
        U32 *_t3052 = malloc(sizeof(U32));
        *_t3052 = 0;
        (void)_t3052;
        Expr *_t3053 = expr_get_child(stmt, DEREF(_t3052));
        (void)_t3053;
        Str *_t3054 = expr_get_str_val(_t3053);
        (void)_t3054;
        Str *_t3055 = Str_lit("import", 6ULL);
        (void)_t3055;
        Bool _t3056 = Bool_and(_t3050, _t3051);
        (void)_t3056;
        ;
        ;
        Bool _t3057; { Bool *_hp = (Bool *)Str_eq(_t3054, _t3055); _t3057 = *_hp; free(_hp); }
        (void)_t3057;
        U32_delete(_t3052, &(Bool){1});
        Str_delete(_t3055, &(Bool){1});
        U32 *_t3058 = malloc(sizeof(U32));
        *_t3058 = 1;
        (void)_t3058;
        Expr *_t3059 = expr_get_child(stmt, DEREF(_t3058));
        (void)_t3059;
        I32 _t3060 = expr_get_tag(_t3059);
        (void)_t3060;
        U32_delete(_t3058, &(Bool){1});
        Bool _t3061 = Bool_and(_t3056, _t3057);
        (void)_t3061;
        ;
        ;
        Bool _t3062 = I32_eq(_t3060, DEREF(NODE_LITERAL_STR));
        (void)_t3062;
        ;
        Bool _t3063 = Bool_and(_t3061, _t3062);
        (void)_t3063;
        ;
        ;
        if (_t3063) {
            U32 *_t3038 = malloc(sizeof(U32));
            *_t3038 = 1;
            (void)_t3038;
            Expr *_t3039 = expr_get_child(stmt, DEREF(_t3038));
            (void)_t3039;
            Str *path = expr_get_str_val(_t3039);
            (void)path;
            Str *_t3040 = Str_clone(path);
            (void)_t3040;
            U32_delete(_t3038, &(Bool){1});
            Vec_push(paths, _t3040);
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t3064 = 1;
        (void)_t3064;
        U32 _t3065 = U32_add(DEREF(i), _t3064);
        (void)_t3065;
        ;
        *i = _t3065;
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
        U64 _fi3068 = 0;
        (void)_fi3068;
        while (1) {
            U64 _t3098 = 0;
            (void)_t3098;
            U64 _t3099; { U64 *_hp = (U64 *)Vec_len(import_paths); _t3099 = *_hp; free(_hp); }
            (void)_t3099;
            Range *_t3100 = Range_new(_t3098, _t3099);
            (void)_t3100;
            ;
            ;
            U64 _t3101; { U64 *_hp = (U64 *)Range_len(_t3100); _t3101 = *_hp; free(_hp); }
            (void)_t3101;
            Range_delete(_t3100, &(Bool){1});
            Bool _wcond3069; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3068}, &(U64){_t3101}); _wcond3069 = *_hp; free(_hp); }
            (void)_wcond3069;
            ;
            if (_wcond3069) {
            } else {
                ;
                break;
            }
            ;
            U64 _t3102 = 0;
            (void)_t3102;
            U64 _t3103; { U64 *_hp = (U64 *)Vec_len(import_paths); _t3103 = *_hp; free(_hp); }
            (void)_t3103;
            Range *_t3104 = Range_new(_t3102, _t3103);
            (void)_t3104;
            ;
            ;
            U64 *i = Range_get(_t3104, _fi3068);
            (void)i;
            Range_delete(_t3104, &(Bool){1});
            U64 _t3105 = 1;
            (void)_t3105;
            U64 _t3106 = U64_add(_fi3068, _t3105);
            (void)_t3106;
            ;
            _fi3068 = _t3106;
            ;
            Str *import_path = Vec_get(import_paths, i);
            (void)import_path;
            Str *_t3107 = Str_lit("/", 1ULL);
            (void)_t3107;
            Str *_t3108 = Str_concat(base_dir, _t3107);
            (void)_t3108;
            Str_delete(_t3107, &(Bool){1});
            Str *try_path = Str_concat(_t3108, import_path);
            (void)try_path;
            Str_delete(_t3108, &(Bool){1});
            Str *abs = til_realpath(try_path);
            (void)abs;
            Str *_t3109 = Str_lit("", 0ULL);
            (void)_t3109;
            U64 _t3110; { U64 *_hp = (U64 *)Str_len(lib_dir); _t3110 = *_hp; free(_hp); }
            (void)_t3110;
            U64 _t3111 = 0;
            (void)_t3111;
            Bool _t3112; { Bool *_hp = (Bool *)Str_eq(abs, _t3109); _t3112 = *_hp; free(_hp); }
            (void)_t3112;
            Str_delete(_t3109, &(Bool){1});
            Bool _t3113; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3110}, &(U64){_t3111}); _t3113 = *_hp; free(_hp); }
            (void)_t3113;
            ;
            ;
            Bool _t3114 = Bool_and(_t3112, _t3113);
            (void)_t3114;
            ;
            ;
            if (_t3114) {
                Str *_t3070 = Str_lit("/", 1ULL);
                (void)_t3070;
                Str *_t3071 = Str_concat(lib_dir, _t3070);
                (void)_t3071;
                Str_delete(_t3070, &(Bool){1});
                try_path = Str_concat(_t3071, import_path);
                Str_delete(_t3071, &(Bool){1});
                abs = til_realpath(try_path);
            }
            ;
            Str_delete(try_path, &(Bool){1});
            Str *_t3115 = Str_lit("", 0ULL);
            (void)_t3115;
            Bool _t3116; { Bool *_hp = (Bool *)Str_eq(abs, _t3115); _t3116 = *_hp; free(_hp); }
            (void)_t3116;
            Str_delete(_t3115, &(Bool){1});
            if (_t3116) {
                Str *_t3072 = Str_lit("Str", 3ULL);
                (void)_t3072;
                U64 _t3073; { U64 *_hp = (U64 *)Str_size(); _t3073 = *_hp; free(_hp); }
                (void)_t3073;
                U64 _t3074 = 1;
                (void)_t3074;
                Array *_va54 = Array_new(_t3072, &(U64){_t3073}, &(U64){_t3074});
                (void)_va54;
                Str_delete(_t3072, &(Bool){1});
                ;
                ;
                Str *_t3075 = Str_lit("error: could not find import '", 30ULL);
                (void)_t3075;
                Str *_t3076 = Str_concat(_t3075, import_path);
                (void)_t3076;
                Str_delete(_t3075, &(Bool){1});
                Str *_t3077 = Str_lit("' (from ", 8ULL);
                (void)_t3077;
                Str *_t3078 = Str_concat(_t3076, _t3077);
                (void)_t3078;
                Str_delete(_t3076, &(Bool){1});
                Str_delete(_t3077, &(Bool){1});
                Str *_t3079 = Str_concat(_t3078, base_dir);
                (void)_t3079;
                Str_delete(_t3078, &(Bool){1});
                Str *_t3080 = Str_lit("/)", 2ULL);
                (void)_t3080;
                U64 _t3081 = 0;
                (void)_t3081;
                Str *_t3082 = Str_concat(_t3079, _t3080);
                (void)_t3082;
                Str_delete(_t3079, &(Bool){1});
                Str_delete(_t3080, &(Bool){1});
                Array_set(_va54, &(U64){_t3081}, _t3082);
                ;
                println(_va54);
                I64 _t3083 = 1;
                (void)_t3083;
                ;
                Str_delete(abs, &(Bool){1});
                U64_delete(i, &(Bool){1});
                ;
                { I32 *_r = malloc(sizeof(I32)); *_r = _t3083; return _r; }
            }
            ;
            U64_delete(i, &(Bool){1});
            Bool _t3117 = til_set_has(resolved_set, abs);
            (void)_t3117;
            if (_t3117) {
                ;
                Str_delete(abs, &(Bool){1});
                continue;
            }
            ;
            til_set_add(resolved_set, abs);
            Str *source = readfile(abs);
            (void)source;
            Token *tokens = til_tokenize(source, abs);
            (void)tokens;
            Str_delete(source, &(Bool){1});
            U32 count = til_tok_count();
            (void)count;
            Expr *sub_ast = til_parse(tokens, count, abs);
            (void)sub_ast;
            ;
            Token_delete(tokens, &(Bool){1});
            Str *sub_mode = til_parse_mode();
            (void)sub_mode;
            Str_delete(sub_mode, &(Bool){1});
            Vec *sub_imports = extract_imports(sub_ast);
            (void)sub_imports;
            U64 _t3118; { U64 *_hp = (U64 *)Str_len(abs); _t3118 = *_hp; free(_hp); }
            (void)_t3118;
            U64 _t3119 = 1;
            (void)_t3119;
            U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t3118, _t3119);
            (void)last_slash;
            ;
            ;
            while (1) {
                U64 _t3085 = 0;
                (void)_t3085;
                U8 *_t3086 = Str_get(abs, last_slash);
                (void)_t3086;
                U8 _t3087 = 47;
                (void)_t3087;
                Bool _t3088; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t3085}); _t3088 = *_hp; free(_hp); }
                (void)_t3088;
                ;
                Bool _t3089; { Bool *_hp = (Bool *)U8_neq(_t3086, &(U8){_t3087}); _t3089 = *_hp; free(_hp); }
                (void)_t3089;
                ;
                Bool _wcond3084 = Bool_and(_t3088, _t3089);
                (void)_wcond3084;
                ;
                ;
                if (_wcond3084) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t3090 = 1;
                (void)_t3090;
                U64 _t3091 = U64_sub(DEREF(last_slash), _t3090);
                (void)_t3091;
                ;
                *last_slash = _t3091;
                ;
            }
            Str *sub_dir = til_str_left(abs, DEREF(last_slash));
            (void)sub_dir;
            Str_delete(abs, &(Bool){1});
            U64_delete(last_slash, &(Bool){1});
            U64 _t3120; { U64 *_hp = (U64 *)Vec_len(sub_imports); _t3120 = *_hp; free(_hp); }
            (void)_t3120;
            U64 _t3121 = 0;
            (void)_t3121;
            Bool _t3122; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3120}, &(U64){_t3121}); _t3122 = *_hp; free(_hp); }
            (void)_t3122;
            ;
            ;
            if (_t3122) {
                I32 err; { I32 *_hp = (I32 *)resolve_imports(sub_imports, sub_dir, resolved_set, stack, merged, lib_dir); err = *_hp; free(_hp); }
                (void)err;
                I32 _t3092 = 0;
                (void)_t3092;
                Bool _t3093; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t3092}); _t3093 = *_hp; free(_hp); }
                (void)_t3093;
                ;
                if (_t3093) {
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
                U32 _t3095 = expr_nchildren(sub_ast);
                (void)_t3095;
                Bool _wcond3094; { Bool *_hp = (Bool *)U32_lt(k, &(U32){_t3095}); _wcond3094 = *_hp; free(_hp); }
                (void)_wcond3094;
                ;
                if (_wcond3094) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *ch = expr_get_child(sub_ast, DEREF(k));
                (void)ch;
                expr_vec_push(merged, ch);
                U32 _t3096 = 1;
                (void)_t3096;
                U32 _t3097 = U32_add(DEREF(k), _t3096);
                (void)_t3097;
                ;
                *k = _t3097;
                ;
            }
            U32_delete(k, &(Bool){1});
            Expr_delete(sub_ast, &(Bool){1});
        }
        ;
    }
    I64 _t3123 = 0;
    (void)_t3123;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t3123; return _r; }
}

void usage(void) {
    Str *_t3124 = Str_lit("Str", 3ULL);
    (void)_t3124;
    U64 _t3125; { U64 *_hp = (U64 *)Str_size(); _t3125 = *_hp; free(_hp); }
    (void)_t3125;
    U64 _t3126 = 1;
    (void)_t3126;
    Array *_va55 = Array_new(_t3124, &(U64){_t3125}, &(U64){_t3126});
    (void)_va55;
    Str_delete(_t3124, &(Bool){1});
    ;
    ;
    U64 _t3127 = 0;
    (void)_t3127;
    Str *_t3128 = Str_lit("Usage: til <command> <path>", 27ULL);
    (void)_t3128;
    Array_set(_va55, &(U64){_t3127}, _t3128);
    ;
    println(_va55);
    Str *_t3129 = Str_lit("Str", 3ULL);
    (void)_t3129;
    U64 _t3130; { U64 *_hp = (U64 *)Str_size(); _t3130 = *_hp; free(_hp); }
    (void)_t3130;
    U64 _t3131 = 1;
    (void)_t3131;
    Array *_va56 = Array_new(_t3129, &(U64){_t3130}, &(U64){_t3131});
    (void)_va56;
    Str_delete(_t3129, &(Bool){1});
    ;
    ;
    U64 _t3132 = 0;
    (void)_t3132;
    Str *_t3133 = Str_lit("", 0ULL);
    (void)_t3133;
    Array_set(_va56, &(U64){_t3132}, _t3133);
    ;
    println(_va56);
    Str *_t3134 = Str_lit("Str", 3ULL);
    (void)_t3134;
    U64 _t3135; { U64 *_hp = (U64 *)Str_size(); _t3135 = *_hp; free(_hp); }
    (void)_t3135;
    U64 _t3136 = 1;
    (void)_t3136;
    Array *_va57 = Array_new(_t3134, &(U64){_t3135}, &(U64){_t3136});
    (void)_va57;
    Str_delete(_t3134, &(Bool){1});
    ;
    ;
    U64 _t3137 = 0;
    (void)_t3137;
    Str *_t3138 = Str_lit("Commands:", 9ULL);
    (void)_t3138;
    Array_set(_va57, &(U64){_t3137}, _t3138);
    ;
    println(_va57);
    Str *_t3139 = Str_lit("Str", 3ULL);
    (void)_t3139;
    U64 _t3140; { U64 *_hp = (U64 *)Str_size(); _t3140 = *_hp; free(_hp); }
    (void)_t3140;
    U64 _t3141 = 1;
    (void)_t3141;
    Array *_va58 = Array_new(_t3139, &(U64){_t3140}, &(U64){_t3141});
    (void)_va58;
    Str_delete(_t3139, &(Bool){1});
    ;
    ;
    U64 _t3142 = 0;
    (void)_t3142;
    Str *_t3143 = Str_lit("  interpret  Read and interpret a .til file", 43ULL);
    (void)_t3143;
    Array_set(_va58, &(U64){_t3142}, _t3143);
    ;
    println(_va58);
    Str *_t3144 = Str_lit("Str", 3ULL);
    (void)_t3144;
    U64 _t3145; { U64 *_hp = (U64 *)Str_size(); _t3145 = *_hp; free(_hp); }
    (void)_t3145;
    U64 _t3146 = 1;
    (void)_t3146;
    Array *_va59 = Array_new(_t3144, &(U64){_t3145}, &(U64){_t3146});
    (void)_va59;
    Str_delete(_t3144, &(Bool){1});
    ;
    ;
    U64 _t3147 = 0;
    (void)_t3147;
    Str *_t3148 = Str_lit("  translate  Generate C source (no compilation)", 47ULL);
    (void)_t3148;
    Array_set(_va59, &(U64){_t3147}, _t3148);
    ;
    println(_va59);
    Str *_t3149 = Str_lit("Str", 3ULL);
    (void)_t3149;
    U64 _t3150; { U64 *_hp = (U64 *)Str_size(); _t3150 = *_hp; free(_hp); }
    (void)_t3150;
    U64 _t3151 = 1;
    (void)_t3151;
    Array *_va60 = Array_new(_t3149, &(U64){_t3150}, &(U64){_t3151});
    (void)_va60;
    Str_delete(_t3149, &(Bool){1});
    ;
    ;
    U64 _t3152 = 0;
    (void)_t3152;
    Str *_t3153 = Str_lit("  build      Compile a .til file to a binary", 44ULL);
    (void)_t3153;
    Array_set(_va60, &(U64){_t3152}, _t3153);
    ;
    println(_va60);
    Str *_t3154 = Str_lit("Str", 3ULL);
    (void)_t3154;
    U64 _t3155; { U64 *_hp = (U64 *)Str_size(); _t3155 = *_hp; free(_hp); }
    (void)_t3155;
    U64 _t3156 = 1;
    (void)_t3156;
    Array *_va61 = Array_new(_t3154, &(U64){_t3155}, &(U64){_t3156});
    (void)_va61;
    Str_delete(_t3154, &(Bool){1});
    ;
    ;
    U64 _t3157 = 0;
    (void)_t3157;
    Str *_t3158 = Str_lit("  run        Compile and run a .til file", 40ULL);
    (void)_t3158;
    Array_set(_va61, &(U64){_t3157}, _t3158);
    ;
    println(_va61);
    Str *_t3159 = Str_lit("Str", 3ULL);
    (void)_t3159;
    U64 _t3160; { U64 *_hp = (U64 *)Str_size(); _t3160 = *_hp; free(_hp); }
    (void)_t3160;
    U64 _t3161 = 1;
    (void)_t3161;
    Array *_va62 = Array_new(_t3159, &(U64){_t3160}, &(U64){_t3161});
    (void)_va62;
    Str_delete(_t3159, &(Bool){1});
    ;
    ;
    U64 _t3162 = 0;
    (void)_t3162;
    Str *_t3163 = Str_lit("  test       Run test functions in a .til file", 46ULL);
    (void)_t3163;
    Array_set(_va62, &(U64){_t3162}, _t3163);
    ;
    println(_va62);
    Str *_t3164 = Str_lit("Str", 3ULL);
    (void)_t3164;
    U64 _t3165; { U64 *_hp = (U64 *)Str_size(); _t3165 = *_hp; free(_hp); }
    (void)_t3165;
    U64 _t3166 = 1;
    (void)_t3166;
    Array *_va63 = Array_new(_t3164, &(U64){_t3165}, &(U64){_t3166});
    (void)_va63;
    Str_delete(_t3164, &(Bool){1});
    ;
    ;
    U64 _t3167 = 0;
    (void)_t3167;
    Str *_t3168 = Str_lit("  help       Print this message", 31ULL);
    (void)_t3168;
    Array_set(_va63, &(U64){_t3167}, _t3168);
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
        U32 _t3170 = expr_nchildren(e);
        (void)_t3170;
        Bool _wcond3169; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3170}); _wcond3169 = *_hp; free(_hp); }
        (void)_wcond3169;
        ;
        if (_wcond3169) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t3171 = expr_get_child(e, DEREF(i));
        (void)_t3171;
        mark_core(_t3171);
        U32 _t3172 = 1;
        (void)_t3172;
        U32 _t3173 = U32_add(DEREF(i), _t3172);
        (void)_t3173;
        ;
        *i = _t3173;
        ;
    }
    U32_delete(i, &(Bool){1});
}

int main(int argc, char **argv) {
    if (argc - 1 < 0) { fprintf(stderr, "error: main expects at least 0 argument(s), got %d\n", argc - 1); return 1; }
    _t3638 = malloc(sizeof(I64));
    *_t3638 = 0;
    (void)_t3638;
    _t3639 = malloc(sizeof(I64));
    *_t3639 = 1;
    (void)_t3639;
    _t3640 = malloc(sizeof(I64)); *_t3640 = I64_sub(DEREF(_t3638), DEREF(_t3639));
    (void)_t3640;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t3640));
    (void)CAP_LIT;
    _t3641 = malloc(sizeof(I64));
    *_t3641 = 0;
    (void)_t3641;
    _t3642 = malloc(sizeof(I64));
    *_t3642 = 2;
    (void)_t3642;
    _t3643 = malloc(sizeof(I64)); *_t3643 = I64_sub(DEREF(_t3641), DEREF(_t3642));
    (void)_t3643;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t3643));
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
    U64 _t3559; { U64 *_hp = (U64 *)Array_len(args); _t3559 = *_hp; free(_hp); }
    (void)_t3559;
    U64 _t3560 = 0;
    (void)_t3560;
    Bool _t3561 = U64_eq(_t3559, _t3560);
    (void)_t3561;
    ;
    ;
    if (_t3561) {
        usage();
        Str *_t3174 = Str_lit("Str", 3ULL);
        (void)_t3174;
        U64 _t3175; { U64 *_hp = (U64 *)Str_size(); _t3175 = *_hp; free(_hp); }
        (void)_t3175;
        U64 _t3176 = 1;
        (void)_t3176;
        Array *_va64 = Array_new(_t3174, &(U64){_t3175}, &(U64){_t3176});
        (void)_va64;
        Str_delete(_t3174, &(Bool){1});
        ;
        ;
        U64 _t3177 = 0;
        (void)_t3177;
        Str *_t3178 = Str_lit("no arguments", 12ULL);
        (void)_t3178;
        Array_set(_va64, &(U64){_t3177}, _t3178);
        ;
        Str *_t3179 = Str_lit("src/til.til:233:15", 18ULL);
        (void)_t3179;
        panic(_t3179, _va64);
        Str_delete(_t3179, &(Bool){1});
    }
    ;
    U64 *_t3562 = malloc(sizeof(U64));
    *_t3562 = 0;
    (void)_t3562;
    Str *cmd_ref = Array_get(args, _t3562);
    (void)cmd_ref;
    Str *command = Str_clone(cmd_ref);
    (void)command;
    U64_delete(_t3562, &(Bool){1});
    Str *path = Str_lit("", 0ULL);
    (void)path;
    Str *custom_bin = Str_lit("", 0ULL);
    (void)custom_bin;
    Str *custom_c = Str_lit("", 0ULL);
    (void)custom_c;
    U64 *path_idx = malloc(sizeof(U64));
    *path_idx = 1;
    (void)path_idx;
    U64 _t3563; { U64 *_hp = (U64 *)Array_len(args); _t3563 = *_hp; free(_hp); }
    (void)_t3563;
    U64 _t3564 = 1;
    (void)_t3564;
    Bool _t3565 = U64_eq(_t3563, _t3564);
    (void)_t3565;
    ;
    ;
    if (_t3565) {
        Str *_t3180 = Str_lit("help", 4ULL);
        (void)_t3180;
        Str *_t3181 = Str_lit("--help", 6ULL);
        (void)_t3181;
        Bool _t3182; { Bool *_hp = (Bool *)Str_eq(command, _t3180); _t3182 = *_hp; free(_hp); }
        (void)_t3182;
        Str_delete(_t3180, &(Bool){1});
        Bool _t3183; { Bool *_hp = (Bool *)Str_eq(command, _t3181); _t3183 = *_hp; free(_hp); }
        (void)_t3183;
        Str_delete(_t3181, &(Bool){1});
        Bool _t3184 = Bool_or(_t3182, _t3183);
        (void)_t3184;
        ;
        ;
        if (_t3184) {
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
            U64 _t3201; { U64 *_hp = (U64 *)Array_len(args); _t3201 = *_hp; free(_hp); }
            (void)_t3201;
            Bool _wcond3185; { Bool *_hp = (Bool *)U64_lt(path_idx, &(U64){_t3201}); _wcond3185 = *_hp; free(_hp); }
            (void)_wcond3185;
            ;
            if (_wcond3185) {
            } else {
                ;
                break;
            }
            ;
            Str *flag = Array_get(args, path_idx);
            (void)flag;
            Str *_t3202 = Str_lit("-o", 2ULL);
            (void)_t3202;
            U64 _t3203 = 1;
            (void)_t3203;
            U64 _t3204 = U64_add(DEREF(path_idx), _t3203);
            (void)_t3204;
            ;
            U64 _t3205; { U64 *_hp = (U64 *)Array_len(args); _t3205 = *_hp; free(_hp); }
            (void)_t3205;
            Bool _t3206; { Bool *_hp = (Bool *)Str_eq(flag, _t3202); _t3206 = *_hp; free(_hp); }
            (void)_t3206;
            Str_delete(_t3202, &(Bool){1});
            Bool _t3207; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3204}, &(U64){_t3205}); _t3207 = *_hp; free(_hp); }
            (void)_t3207;
            ;
            ;
            Bool _t3208 = Bool_and(_t3206, _t3207);
            (void)_t3208;
            ;
            ;
            if (_t3208) {
                U64 _t3186 = 1;
                (void)_t3186;
                U64 *_t3187 = malloc(sizeof(U64)); *_t3187 = U64_add(DEREF(path_idx), _t3186);
                (void)_t3187;
                ;
                Str *oval = Array_get(args, _t3187);
                (void)oval;
                custom_bin = Str_clone(oval);
                U64_delete(_t3187, &(Bool){1});
                U64 _t3188 = 2;
                (void)_t3188;
                U64 _t3189 = U64_add(DEREF(path_idx), _t3188);
                (void)_t3189;
                ;
                *path_idx = _t3189;
                ;
            } else {
                Str *_t3194 = Str_lit("-c", 2ULL);
                (void)_t3194;
                U64 _t3195 = 1;
                (void)_t3195;
                U64 _t3196 = U64_add(DEREF(path_idx), _t3195);
                (void)_t3196;
                ;
                U64 _t3197; { U64 *_hp = (U64 *)Array_len(args); _t3197 = *_hp; free(_hp); }
                (void)_t3197;
                Bool _t3198; { Bool *_hp = (Bool *)Str_eq(flag, _t3194); _t3198 = *_hp; free(_hp); }
                (void)_t3198;
                Str_delete(_t3194, &(Bool){1});
                Bool _t3199; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3196}, &(U64){_t3197}); _t3199 = *_hp; free(_hp); }
                (void)_t3199;
                ;
                ;
                Bool _t3200 = Bool_and(_t3198, _t3199);
                (void)_t3200;
                ;
                ;
                if (_t3200) {
                    U64 _t3190 = 1;
                    (void)_t3190;
                    U64 *_t3191 = malloc(sizeof(U64)); *_t3191 = U64_add(DEREF(path_idx), _t3190);
                    (void)_t3191;
                    ;
                    Str *cval = Array_get(args, _t3191);
                    (void)cval;
                    custom_c = Str_clone(cval);
                    U64_delete(_t3191, &(Bool){1});
                    U64 _t3192 = 2;
                    (void)_t3192;
                    U64 _t3193 = U64_add(DEREF(path_idx), _t3192);
                    (void)_t3193;
                    ;
                    *path_idx = _t3193;
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
    Str *_t3566 = Str_lit("help", 4ULL);
    (void)_t3566;
    Str *_t3567 = Str_lit("--help", 6ULL);
    (void)_t3567;
    Bool _t3568; { Bool *_hp = (Bool *)Str_eq(command, _t3566); _t3568 = *_hp; free(_hp); }
    (void)_t3568;
    Str_delete(_t3566, &(Bool){1});
    Bool _t3569; { Bool *_hp = (Bool *)Str_eq(command, _t3567); _t3569 = *_hp; free(_hp); }
    (void)_t3569;
    Str_delete(_t3567, &(Bool){1});
    Bool _t3570 = Bool_or(_t3568, _t3569);
    (void)_t3570;
    ;
    ;
    if (_t3570) {
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
    Str *_t3571 = Str_lit("/src/core/core.til", 18ULL);
    (void)_t3571;
    Str *core_path = Str_concat(bin_dir, _t3571);
    (void)core_path;
    Str_delete(_t3571, &(Bool){1});
    Str *_t3572 = Str_lit("/src/c/ext.c", 12ULL);
    (void)_t3572;
    Str *ext_c_path = Str_concat(bin_dir, _t3572);
    (void)ext_c_path;
    Str_delete(_t3572, &(Bool){1});
    Set *resolved = til_set_new();
    (void)resolved;
    Vec *resolve_stack = expr_vec_new();
    (void)resolve_stack;
    Str *abs_path = til_realpath(path);
    (void)abs_path;
    Str *user_dir = Str_lit(".", 1ULL);
    (void)user_dir;
    U64 _t3573; { U64 *_hp = (U64 *)Str_len(abs_path); _t3573 = *_hp; free(_hp); }
    (void)_t3573;
    U64 _t3574 = 0;
    (void)_t3574;
    Bool _t3575; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3573}, &(U64){_t3574}); _t3575 = *_hp; free(_hp); }
    (void)_t3575;
    ;
    ;
    if (_t3575) {
        U64 _t3217; { U64 *_hp = (U64 *)Str_len(abs_path); _t3217 = *_hp; free(_hp); }
        (void)_t3217;
        U64 _t3218 = 1;
        (void)_t3218;
        U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t3217, _t3218);
        (void)last_slash;
        ;
        ;
        while (1) {
            U64 _t3210 = 0;
            (void)_t3210;
            U8 *_t3211 = Str_get(abs_path, last_slash);
            (void)_t3211;
            U8 _t3212 = 47;
            (void)_t3212;
            Bool _t3213; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t3210}); _t3213 = *_hp; free(_hp); }
            (void)_t3213;
            ;
            Bool _t3214; { Bool *_hp = (Bool *)U8_neq(_t3211, &(U8){_t3212}); _t3214 = *_hp; free(_hp); }
            (void)_t3214;
            ;
            Bool _wcond3209 = Bool_and(_t3213, _t3214);
            (void)_wcond3209;
            ;
            ;
            if (_wcond3209) {
            } else {
                ;
                break;
            }
            ;
            U64 _t3215 = 1;
            (void)_t3215;
            U64 _t3216 = U64_sub(DEREF(last_slash), _t3215);
            (void)_t3216;
            ;
            *last_slash = _t3216;
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
    Token *core_tokens = til_tokenize(core_source, core_path);
    (void)core_tokens;
    Str_delete(core_source, &(Bool){1});
    U32 core_count = til_tok_count();
    (void)core_count;
    Expr *core_ast = til_parse(core_tokens, core_count, core_path);
    (void)core_ast;
    ;
    Token_delete(core_tokens, &(Bool){1});
    Bool skip_core = 0;
    (void)skip_core;
    Str *core_abs = til_realpath(core_path);
    (void)core_abs;
    Str_delete(core_path, &(Bool){1});
    U64 _t3576; { U64 *_hp = (U64 *)Str_len(core_abs); _t3576 = *_hp; free(_hp); }
    (void)_t3576;
    U64 _t3577 = 0;
    (void)_t3577;
    Bool _t3578; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3576}, &(U64){_t3577}); _t3578 = *_hp; free(_hp); }
    (void)_t3578;
    ;
    ;
    if (_t3578) {
        Bool _t3220 = til_set_has(resolved, core_abs);
        (void)_t3220;
        if (_t3220) {
            Bool _t3219 = 1;
            (void)_t3219;
            skip_core = _t3219;
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
    U64 _t3579; { U64 *_hp = (U64 *)Vec_len(core_imports); _t3579 = *_hp; free(_hp); }
    (void)_t3579;
    U64 _t3580 = 0;
    (void)_t3580;
    Bool _t3581; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3579}, &(U64){_t3580}); _t3581 = *_hp; free(_hp); }
    (void)_t3581;
    ;
    ;
    Bool _t3582 = Bool_not(skip_core);
    (void)_t3582;
    Bool _t3583 = Bool_and(_t3581, _t3582);
    (void)_t3583;
    ;
    ;
    if (_t3583) {
        Str *_t3227 = Str_lit("/src/core", 9ULL);
        (void)_t3227;
        Str *core_dir = Str_concat(bin_dir, _t3227);
        (void)core_dir;
        Str_delete(_t3227, &(Bool){1});
        Str *_t3228 = Str_lit("", 0ULL);
        (void)_t3228;
        I32 err; { I32 *_hp = (I32 *)resolve_imports(core_imports, core_dir, resolved, resolve_stack, core_import_decls, _t3228); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(_t3228, &(Bool){1});
        Str_delete(core_dir, &(Bool){1});
        I32 _t3229 = 0;
        (void)_t3229;
        Bool _t3230; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t3229}); _t3230 = *_hp; free(_hp); }
        (void)_t3230;
        ;
        ;
        if (_t3230) {
            Str *_t3221 = Str_lit("Str", 3ULL);
            (void)_t3221;
            U64 _t3222; { U64 *_hp = (U64 *)Str_size(); _t3222 = *_hp; free(_hp); }
            (void)_t3222;
            U64 _t3223 = 1;
            (void)_t3223;
            Array *_va65 = Array_new(_t3221, &(U64){_t3222}, &(U64){_t3223});
            (void)_va65;
            Str_delete(_t3221, &(Bool){1});
            ;
            ;
            U64 _t3224 = 0;
            (void)_t3224;
            Str *_t3225 = Str_lit("failed to resolve core imports", 30ULL);
            (void)_t3225;
            Array_set(_va65, &(U64){_t3224}, _t3225);
            ;
            Str *_t3226 = Str_lit("src/til.til:320:19", 18ULL);
            (void)_t3226;
            panic(_t3226, _va65);
            Str_delete(_t3226, &(Bool){1});
        }
        ;
    }
    ;
    Vec_delete(core_imports, &(Bool){1});
    Str *source = readfile(path);
    (void)source;
    Token *tokens = til_tokenize(source, path);
    (void)tokens;
    Str_delete(source, &(Bool){1});
    U32 count = til_tok_count();
    (void)count;
    Expr *ast = til_parse(tokens, count, path);
    (void)ast;
    ;
    Token_delete(tokens, &(Bool){1});
    Vec *imports = extract_imports(ast);
    (void)imports;
    Str *mode_str = til_parse_mode();
    (void)mode_str;
    Mode *cur_mode = til_mode_none();
    (void)cur_mode;
    U64 _t3584; { U64 *_hp = (U64 *)Str_len(mode_str); _t3584 = *_hp; free(_hp); }
    (void)_t3584;
    U64 _t3585 = 0;
    (void)_t3585;
    Bool _t3586; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3584}, &(U64){_t3585}); _t3586 = *_hp; free(_hp); }
    (void)_t3586;
    ;
    ;
    if (_t3586) {
        cur_mode = til_mode_resolve(mode_str);
        Mode *_t3240 = til_mode_none();
        (void)_t3240;
        Bool _t3241 = til_mode_eq(cur_mode, _t3240);
        (void)_t3241;
        Mode_delete(_t3240, &(Bool){1});
        if (_t3241) {
            Str *_t3231 = Str_lit("Str", 3ULL);
            (void)_t3231;
            U64 _t3232; { U64 *_hp = (U64 *)Str_size(); _t3232 = *_hp; free(_hp); }
            (void)_t3232;
            U64 _t3233 = 1;
            (void)_t3233;
            Array *_va66 = Array_new(_t3231, &(U64){_t3232}, &(U64){_t3233});
            (void)_va66;
            Str_delete(_t3231, &(Bool){1});
            ;
            ;
            Str *_t3234 = Str_lit("unknown mode '", 14ULL);
            (void)_t3234;
            Str *_t3235 = Str_concat(_t3234, mode_str);
            (void)_t3235;
            Str_delete(_t3234, &(Bool){1});
            Str *_t3236 = Str_lit("'", 1ULL);
            (void)_t3236;
            U64 _t3237 = 0;
            (void)_t3237;
            Str *_t3238 = Str_concat(_t3235, _t3236);
            (void)_t3238;
            Str_delete(_t3235, &(Bool){1});
            Str_delete(_t3236, &(Bool){1});
            Array_set(_va66, &(U64){_t3237}, _t3238);
            ;
            Str *_t3239 = Str_lit("src/til.til:337:19", 18ULL);
            (void)_t3239;
            panic(_t3239, _va66);
            Str_delete(_t3239, &(Bool){1});
        }
        ;
    }
    ;
    Str_delete(mode_str, &(Bool){1});
    Expr *mode_ast = expr_null();
    (void)mode_ast;
    Str *auto_import = til_mode_auto_import(cur_mode);
    (void)auto_import;
    U64 _t3587; { U64 *_hp = (U64 *)Str_len(auto_import); _t3587 = *_hp; free(_hp); }
    (void)_t3587;
    U64 _t3588 = 0;
    (void)_t3588;
    Bool _t3589; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3587}, &(U64){_t3588}); _t3589 = *_hp; free(_hp); }
    (void)_t3589;
    ;
    ;
    if (_t3589) {
        Str *_t3242 = Str_lit("/src/modes/", 11ULL);
        (void)_t3242;
        Str *_t3243 = Str_concat(bin_dir, _t3242);
        (void)_t3243;
        Str_delete(_t3242, &(Bool){1});
        Str *_t3244 = Str_concat(_t3243, auto_import);
        (void)_t3244;
        Str_delete(_t3243, &(Bool){1});
        Str *_t3245 = Str_lit(".til", 4ULL);
        (void)_t3245;
        Str *mode_til_path = Str_concat(_t3244, _t3245);
        (void)mode_til_path;
        Str_delete(_t3244, &(Bool){1});
        Str_delete(_t3245, &(Bool){1});
        Str *mode_source = readfile(mode_til_path);
        (void)mode_source;
        Token *mode_tokens = til_tokenize(mode_source, mode_til_path);
        (void)mode_tokens;
        Str_delete(mode_source, &(Bool){1});
        U32 mode_count = til_tok_count();
        (void)mode_count;
        mode_ast = til_parse(mode_tokens, mode_count, mode_til_path);
        ;
        Str_delete(mode_til_path, &(Bool){1});
        Token_delete(mode_tokens, &(Bool){1});
    }
    ;
    Str_delete(auto_import, &(Bool){1});
    Vec *import_decls = expr_vec_new();
    (void)import_decls;
    U64 _t3590; { U64 *_hp = (U64 *)Vec_len(imports); _t3590 = *_hp; free(_hp); }
    (void)_t3590;
    U64 _t3591 = 0;
    (void)_t3591;
    Bool _t3592; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3590}, &(U64){_t3591}); _t3592 = *_hp; free(_hp); }
    (void)_t3592;
    ;
    ;
    if (_t3592) {
        Str *_t3252 = Str_lit("/src/lib", 8ULL);
        (void)_t3252;
        Str *lib_dir = Str_concat(bin_dir, _t3252);
        (void)lib_dir;
        Str_delete(_t3252, &(Bool){1});
        I32 err; { I32 *_hp = (I32 *)resolve_imports(imports, user_dir, resolved, resolve_stack, import_decls, lib_dir); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(lib_dir, &(Bool){1});
        I32 _t3253 = 0;
        (void)_t3253;
        Bool _t3254; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t3253}); _t3254 = *_hp; free(_hp); }
        (void)_t3254;
        ;
        ;
        if (_t3254) {
            Str *_t3246 = Str_lit("Str", 3ULL);
            (void)_t3246;
            U64 _t3247; { U64 *_hp = (U64 *)Str_size(); _t3247 = *_hp; free(_hp); }
            (void)_t3247;
            U64 _t3248 = 1;
            (void)_t3248;
            Array *_va67 = Array_new(_t3246, &(U64){_t3247}, &(U64){_t3248});
            (void)_va67;
            Str_delete(_t3246, &(Bool){1});
            ;
            ;
            U64 _t3249 = 0;
            (void)_t3249;
            Str *_t3250 = Str_lit("failed to resolve imports", 25ULL);
            (void)_t3250;
            Array_set(_va67, &(U64){_t3249}, _t3250);
            ;
            Str *_t3251 = Str_lit("src/til.til:359:19", 18ULL);
            (void)_t3251;
            panic(_t3251, _va67);
            Str_delete(_t3251, &(Bool){1});
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
    Bool _t3593 = Bool_not(skip_core);
    (void)_t3593;
    ;
    if (_t3593) {
        while (1) {
            U32 _t3256 = expr_nchildren(core_ast);
            (void)_t3256;
            Bool _wcond3255; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3256}); _wcond3255 = *_hp; free(_hp); }
            (void)_wcond3255;
            ;
            if (_wcond3255) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(core_ast, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t3257 = 1;
            (void)_t3257;
            U32 _t3258 = U32_add(DEREF(i), _t3257);
            (void)_t3258;
            ;
            *i = _t3258;
            ;
        }
        U32 _t3263 = 0;
        (void)_t3263;
        *i = _t3263;
        ;
        while (1) {
            U32 _t3260 = expr_vec_count(core_import_decls);
            (void)_t3260;
            Bool _wcond3259; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3260}); _wcond3259 = *_hp; free(_hp); }
            (void)_wcond3259;
            ;
            if (_wcond3259) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_vec_get(core_import_decls, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t3261 = 1;
            (void)_t3261;
            U32 _t3262 = U32_add(DEREF(i), _t3261);
            (void)_t3262;
            ;
            *i = _t3262;
            ;
        }
    }
    ;
    Expr_delete(core_ast, &(Bool){1});
    Vec_delete(core_import_decls, &(Bool){1});
    Bool _t3594 = expr_is_null(mode_ast);
    (void)_t3594;
    Bool _t3595 = Bool_not(_t3594);
    (void)_t3595;
    ;
    if (_t3595) {
        U32 _t3268 = 0;
        (void)_t3268;
        *i = _t3268;
        ;
        while (1) {
            U32 _t3265 = expr_nchildren(mode_ast);
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
            Expr *ch = expr_get_child(mode_ast, DEREF(i));
            (void)ch;
            expr_vec_push(merged, ch);
            U32 _t3266 = 1;
            (void)_t3266;
            U32 _t3267 = U32_add(DEREF(i), _t3266);
            (void)_t3267;
            ;
            *i = _t3267;
            ;
        }
    }
    ;
    Expr_delete(mode_ast, &(Bool){1});
    U32 _t3596 = 0;
    (void)_t3596;
    *i = _t3596;
    ;
    while (1) {
        U32 _t3270 = expr_vec_count(import_decls);
        (void)_t3270;
        Bool _wcond3269; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3270}); _wcond3269 = *_hp; free(_hp); }
        (void)_wcond3269;
        ;
        if (_wcond3269) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_vec_get(import_decls, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t3271 = 1;
        (void)_t3271;
        U32 _t3272 = U32_add(DEREF(i), _t3271);
        (void)_t3272;
        ;
        *i = _t3272;
        ;
    }
    Vec_delete(import_decls, &(Bool){1});
    U32 _t3597 = 0;
    (void)_t3597;
    *i = _t3597;
    ;
    while (1) {
        U32 _t3274 = expr_nchildren(ast);
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
        Expr *ch = expr_get_child(ast, DEREF(i));
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
    expr_swap_children(ast, merged);
    Vec_delete(merged, &(Bool){1});
    Str *link_flags = Str_lit("", 0ULL);
    (void)link_flags;
    Str *link_c_paths = Str_lit("", 0ULL);
    (void)link_c_paths;
    Vec *kept = expr_vec_new();
    (void)kept;
    U32 _t3598 = 0;
    (void)_t3598;
    *i = _t3598;
    ;
    while (1) {
        U32 _t3292 = expr_nchildren(ast);
        (void)_t3292;
        Bool _wcond3277; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t3292}); _wcond3277 = *_hp; free(_hp); }
        (void)_wcond3277;
        ;
        if (_wcond3277) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(ast, DEREF(i));
        (void)stmt;
        I32 _t3293 = expr_get_tag(stmt);
        (void)_t3293;
        U32 _t3294 = expr_nchildren(stmt);
        (void)_t3294;
        U32 _t3295 = 2;
        (void)_t3295;
        Bool _t3296 = I32_eq(_t3293, DEREF(NODE_FCALL));
        (void)_t3296;
        ;
        Bool _t3297 = U32_eq(_t3294, _t3295);
        (void)_t3297;
        ;
        ;
        U32 *_t3298 = malloc(sizeof(U32));
        *_t3298 = 0;
        (void)_t3298;
        Expr *_t3299 = expr_get_child(stmt, DEREF(_t3298));
        (void)_t3299;
        I32 _t3300 = expr_get_tag(_t3299);
        (void)_t3300;
        U32_delete(_t3298, &(Bool){1});
        Bool _t3301 = Bool_and(_t3296, _t3297);
        (void)_t3301;
        ;
        ;
        Bool _t3302 = I32_eq(_t3300, DEREF(NODE_IDENT));
        (void)_t3302;
        ;
        U32 *_t3303 = malloc(sizeof(U32));
        *_t3303 = 1;
        (void)_t3303;
        Expr *_t3304 = expr_get_child(stmt, DEREF(_t3303));
        (void)_t3304;
        I32 _t3305 = expr_get_tag(_t3304);
        (void)_t3305;
        U32_delete(_t3303, &(Bool){1});
        Bool _t3306 = Bool_and(_t3301, _t3302);
        (void)_t3306;
        ;
        ;
        Bool _t3307 = I32_eq(_t3305, DEREF(NODE_LITERAL_STR));
        (void)_t3307;
        ;
        Bool _t3308 = Bool_and(_t3306, _t3307);
        (void)_t3308;
        ;
        ;
        if (_t3308) {
            U32 *_t3286 = malloc(sizeof(U32));
            *_t3286 = 0;
            (void)_t3286;
            Expr *_t3287 = expr_get_child(stmt, DEREF(_t3286));
            (void)_t3287;
            Str *fname = expr_get_str_val(_t3287);
            (void)fname;
            U32 *_t3288 = malloc(sizeof(U32));
            *_t3288 = 1;
            (void)_t3288;
            Expr *_t3289 = expr_get_child(stmt, DEREF(_t3288));
            (void)_t3289;
            Str *arg = expr_get_str_val(_t3289);
            (void)arg;
            Str *_t3290 = Str_lit("link", 4ULL);
            (void)_t3290;
            Bool _t3291; { Bool *_hp = (Bool *)Str_eq(fname, _t3290); _t3291 = *_hp; free(_hp); }
            (void)_t3291;
            Str_delete(_t3290, &(Bool){1});
            if (_t3291) {
                Str *_t3278 = Str_lit(" -l", 3ULL);
                (void)_t3278;
                Str *_t3279 = Str_concat(link_flags, _t3278);
                (void)_t3279;
                Str_delete(_t3278, &(Bool){1});
                link_flags = Str_concat(_t3279, arg);
                Str_delete(_t3279, &(Bool){1});
            } else {
                Str *_t3284 = Str_lit("link_c", 6ULL);
                (void)_t3284;
                Bool _t3285; { Bool *_hp = (Bool *)Str_eq(fname, _t3284); _t3285 = *_hp; free(_hp); }
                (void)_t3285;
                Str_delete(_t3284, &(Bool){1});
                if (_t3285) {
                    U64 _t3281; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t3281 = *_hp; free(_hp); }
                    (void)_t3281;
                    U64 _t3282 = 0;
                    (void)_t3282;
                    Bool _t3283; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3281}, &(U64){_t3282}); _t3283 = *_hp; free(_hp); }
                    (void)_t3283;
                    ;
                    ;
                    if (_t3283) {
                        Str *_t3280 = Str_lit(" ", 1ULL);
                        (void)_t3280;
                        link_c_paths = Str_concat(link_c_paths, _t3280);
                        Str_delete(_t3280, &(Bool){1});
                    }
                    ;
                    link_c_paths = Str_concat(link_c_paths, arg);
                } else {
                    expr_vec_push(kept, stmt);
                }
                ;
            }
            U32_delete(_t3286, &(Bool){1});
            U32_delete(_t3288, &(Bool){1});
            ;
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t3309 = 1;
        (void)_t3309;
        U32 _t3310 = U32_add(DEREF(i), _t3309);
        (void)_t3310;
        ;
        *i = _t3310;
        ;
    }
    U32_delete(i, &(Bool){1});
    expr_swap_children(ast, kept);
    Vec_delete(kept, &(Bool){1});
    TypeScope *scope = tscope_new(NULL);
    (void)scope;
    I32 _t3599 = til_init_declarations(ast, scope);
    (void)_t3599;
    ;
    I32 type_errors = til_type_check(ast, scope, cur_mode);
    (void)type_errors;
    TypeScope_delete(scope, &(Bool){1});
    I32 _t3600 = 0;
    (void)_t3600;
    Bool _t3601; { Bool *_hp = (Bool *)I32_gt(&(I32){type_errors}, &(I32){_t3600}); _t3601 = *_hp; free(_hp); }
    (void)_t3601;
    ;
    if (_t3601) {
        Str *_t3311 = Str_lit("Str", 3ULL);
        (void)_t3311;
        U64 _t3312; { U64 *_hp = (U64 *)Str_size(); _t3312 = *_hp; free(_hp); }
        (void)_t3312;
        U64 _t3313 = 1;
        (void)_t3313;
        Array *_va68 = Array_new(_t3311, &(U64){_t3312}, &(U64){_t3313});
        (void)_va68;
        Str_delete(_t3311, &(Bool){1});
        ;
        ;
        Str *_t3314 = I32_to_str(&(I32){type_errors});
        (void)_t3314;
        Str *_t3315 = Str_lit(" type error(s) found", 20ULL);
        (void)_t3315;
        U64 _t3316 = 0;
        (void)_t3316;
        Str *_t3317 = Str_concat(_t3314, _t3315);
        (void)_t3317;
        Str_delete(_t3314, &(Bool){1});
        Str_delete(_t3315, &(Bool){1});
        Array_set(_va68, &(U64){_t3316}, _t3317);
        ;
        Str *_t3318 = Str_lit("src/til.til:450:15", 18ULL);
        (void)_t3318;
        panic(_t3318, _va68);
        Str_delete(_t3318, &(Bool){1});
    }
    ;
    ;
    Str *_t3602 = Str_lit("test", 4ULL);
    (void)_t3602;
    Mode *_t3603 = til_mode_test();
    (void)_t3603;
    Bool _t3604; { Bool *_hp = (Bool *)Str_eq(command, _t3602); _t3604 = *_hp; free(_hp); }
    (void)_t3604;
    Str_delete(_t3602, &(Bool){1});
    Bool _t3605 = til_mode_eq(cur_mode, _t3603);
    (void)_t3605;
    Mode_delete(_t3603, &(Bool){1});
    Mode *_t3606 = til_mode_pure();
    (void)_t3606;
    Bool _t3607 = Bool_or(_t3604, _t3605);
    (void)_t3607;
    ;
    ;
    Bool _t3608 = til_mode_eq(cur_mode, _t3606);
    (void)_t3608;
    Mode_delete(_t3606, &(Bool){1});
    Mode *_t3609 = til_mode_pura();
    (void)_t3609;
    Bool _t3610 = Bool_or(_t3607, _t3608);
    (void)_t3610;
    ;
    ;
    Bool _t3611 = til_mode_eq(cur_mode, _t3609);
    (void)_t3611;
    Mode_delete(_t3609, &(Bool){1});
    Bool run_tests = Bool_or(_t3610, _t3611);
    (void)run_tests;
    ;
    ;
    til_precomp(ast);
    Str *_t3612 = Str_lit("translate", 9ULL);
    (void)_t3612;
    Str *_t3613 = Str_lit("build", 5ULL);
    (void)_t3613;
    Bool _t3614; { Bool *_hp = (Bool *)Str_eq(command, _t3612); _t3614 = *_hp; free(_hp); }
    (void)_t3614;
    Str_delete(_t3612, &(Bool){1});
    Bool _t3615; { Bool *_hp = (Bool *)Str_eq(command, _t3613); _t3615 = *_hp; free(_hp); }
    (void)_t3615;
    Str_delete(_t3613, &(Bool){1});
    Bool _t3616 = til_mode_is_lib_output(cur_mode);
    (void)_t3616;
    Bool _t3617 = Bool_or(_t3614, _t3615);
    (void)_t3617;
    ;
    ;
    Bool is_lib_target = Bool_and(_t3616, _t3617);
    (void)is_lib_target;
    ;
    ;
    U64 _t3618; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t3618 = *_hp; free(_hp); }
    (void)_t3618;
    U64 _t3619 = 0;
    (void)_t3619;
    Bool _t3620 = Bool_not(is_lib_target);
    (void)_t3620;
    ;
    Bool _t3621 = U64_eq(_t3618, _t3619);
    (void)_t3621;
    ;
    ;
    Bool _t3622 = Bool_and(_t3620, _t3621);
    (void)_t3622;
    ;
    ;
    if (_t3622) {
        til_scavenge(ast, cur_mode, run_tests);
    }
    ;
    I32 result = 0;
    (void)result;
    Str *user_c = Str_lit("", 0ULL);
    (void)user_c;
    U64 _t3623; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t3623 = *_hp; free(_hp); }
    (void)_t3623;
    U64 _t3624 = 0;
    (void)_t3624;
    Bool _t3625; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3623}, &(U64){_t3624}); _t3625 = *_hp; free(_hp); }
    (void)_t3625;
    ;
    ;
    if (_t3625) {
        user_c = Str_clone(link_c_paths);
    }
    ;
    Str_delete(link_c_paths, &(Bool){1});
    Str *_t3626 = Str_lit("Str", 3ULL);
    (void)_t3626;
    U64 _t3627; { U64 *_hp = (U64 *)Str_size(); _t3627 = *_hp; free(_hp); }
    (void)_t3627;
    Vec *user_argv = Vec_new(_t3626, &(U64){_t3627});
    (void)user_argv;
    Str_delete(_t3626, &(Bool){1});
    ;
    U64 _t3628 = 1;
    (void)_t3628;
    U64 *ai = malloc(sizeof(U64)); *ai = U64_add(DEREF(path_idx), _t3628);
    (void)ai;
    ;
    U64_delete(path_idx, &(Bool){1});
    while (1) {
        U64 _t3335; { U64 *_hp = (U64 *)Array_len(args); _t3335 = *_hp; free(_hp); }
        (void)_t3335;
        Bool _wcond3319; { Bool *_hp = (Bool *)U64_lt(ai, &(U64){_t3335}); _wcond3319 = *_hp; free(_hp); }
        (void)_wcond3319;
        ;
        if (_wcond3319) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, ai);
        (void)arg;
        Str *_t3336 = Str_lit("-l", 2ULL);
        (void)_t3336;
        Bool _t3337; { Bool *_hp = (Bool *)Str_starts_with(arg, _t3336); _t3337 = *_hp; free(_hp); }
        (void)_t3337;
        Str_delete(_t3336, &(Bool){1});
        if (_t3337) {
            U64 _t3322 = 2;
            (void)_t3322;
            U64 _t3323; { U64 *_hp = (U64 *)Str_len(arg); _t3323 = *_hp; free(_hp); }
            (void)_t3323;
            Str *lib = Str_substr(arg, &(U64){_t3322}, &(U64){_t3323});
            (void)lib;
            ;
            ;
            U64 _t3324; { U64 *_hp = (U64 *)Str_len(lib); _t3324 = *_hp; free(_hp); }
            (void)_t3324;
            U64 _t3325 = 0;
            (void)_t3325;
            U64 _t3326 = 1;
            (void)_t3326;
            U64 _t3327 = U64_add(DEREF(ai), _t3326);
            (void)_t3327;
            ;
            U64 _t3328; { U64 *_hp = (U64 *)Array_len(args); _t3328 = *_hp; free(_hp); }
            (void)_t3328;
            Bool _t3329 = U64_eq(_t3324, _t3325);
            (void)_t3329;
            ;
            ;
            Bool _t3330; { Bool *_hp = (Bool *)U64_lt(&(U64){_t3327}, &(U64){_t3328}); _t3330 = *_hp; free(_hp); }
            (void)_t3330;
            ;
            ;
            Bool _t3331 = Bool_and(_t3329, _t3330);
            (void)_t3331;
            ;
            ;
            if (_t3331) {
                U64 _t3320 = 1;
                (void)_t3320;
                U64 _t3321 = U64_add(DEREF(ai), _t3320);
                (void)_t3321;
                ;
                *ai = _t3321;
                ;
                Str *next_arg = Array_get(args, ai);
                (void)next_arg;
                lib = Str_clone(next_arg);
            }
            ;
            Str *_t3332 = Str_lit(" -l", 3ULL);
            (void)_t3332;
            Str *_t3333 = Str_concat(link_flags, _t3332);
            (void)_t3333;
            Str_delete(_t3332, &(Bool){1});
            link_flags = Str_concat(_t3333, lib);
            Str_delete(_t3333, &(Bool){1});
            Str_delete(lib, &(Bool){1});
        } else {
            Str *_t3334 = Str_clone(arg);
            (void)_t3334;
            Vec_push(user_argv, _t3334);
        }
        ;
        U64 _t3338 = 1;
        (void)_t3338;
        U64 _t3339 = U64_add(DEREF(ai), _t3338);
        (void)_t3339;
        ;
        *ai = _t3339;
        ;
    }
    U64_delete(ai, &(Bool){1});
    Array_delete(args, &(Bool){1});
    Str *lflags = Str_lit("", 0ULL);
    (void)lflags;
    U64 _t3629; { U64 *_hp = (U64 *)Str_len(link_flags); _t3629 = *_hp; free(_hp); }
    (void)_t3629;
    U64 _t3630 = 0;
    (void)_t3630;
    Bool _t3631; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3629}, &(U64){_t3630}); _t3631 = *_hp; free(_hp); }
    (void)_t3631;
    ;
    ;
    if (_t3631) {
        lflags = Str_clone(link_flags);
    }
    ;
    Str_delete(link_flags, &(Bool){1});
    Bool is_lib_mode = til_mode_is_lib(cur_mode);
    (void)is_lib_mode;
    Str *_t3632 = Str_lit("interpret", 9ULL);
    (void)_t3632;
    Str *_t3633 = Str_lit("test", 4ULL);
    (void)_t3633;
    Bool _t3634; { Bool *_hp = (Bool *)Str_eq(command, _t3632); _t3634 = *_hp; free(_hp); }
    (void)_t3634;
    Str_delete(_t3632, &(Bool){1});
    Bool _t3635; { Bool *_hp = (Bool *)Str_eq(command, _t3633); _t3635 = *_hp; free(_hp); }
    (void)_t3635;
    Str_delete(_t3633, &(Bool){1});
    Bool _t3636 = Bool_or(_t3634, _t3635);
    (void)_t3636;
    ;
    ;
    if (_t3636) {
        Str *_t3346 = Str_lit("interpret", 9ULL);
        (void)_t3346;
        Bool _t3347; { Bool *_hp = (Bool *)Str_eq(command, _t3346); _t3347 = *_hp; free(_hp); }
        (void)_t3347;
        Str_delete(_t3346, &(Bool){1});
        Bool _t3348 = Bool_and(is_lib_mode, _t3347);
        (void)_t3348;
        ;
        if (_t3348) {
            Str *_t3340 = Str_lit("Str", 3ULL);
            (void)_t3340;
            U64 _t3341; { U64 *_hp = (U64 *)Str_size(); _t3341 = *_hp; free(_hp); }
            (void)_t3341;
            U64 _t3342 = 1;
            (void)_t3342;
            Array *_va69 = Array_new(_t3340, &(U64){_t3341}, &(U64){_t3342});
            (void)_va69;
            Str_delete(_t3340, &(Bool){1});
            ;
            ;
            U64 _t3343 = 0;
            (void)_t3343;
            Str *_t3344 = Str_lit("cannot interpret a library — use translate or build", 53ULL);
            (void)_t3344;
            Array_set(_va69, &(U64){_t3343}, _t3344);
            ;
            Str *_t3345 = Str_lit("src/til.til:504:19", 18ULL);
            (void)_t3345;
            panic(_t3345, _va69);
            Str_delete(_t3345, &(Bool){1});
        }
        ;
        I32 _t3349 = til_interpret_v(ast, cur_mode, run_tests, path, user_c, ext_c_path, lflags, user_argv);
        (void)_t3349;
        result = _t3349;
        ;
    } else {
        Str *_t3551 = Str_lit("translate", 9ULL);
        (void)_t3551;
        Str *_t3552 = Str_lit("build", 5ULL);
        (void)_t3552;
        Bool _t3553; { Bool *_hp = (Bool *)Str_eq(command, _t3551); _t3553 = *_hp; free(_hp); }
        (void)_t3553;
        Str_delete(_t3551, &(Bool){1});
        Bool _t3554; { Bool *_hp = (Bool *)Str_eq(command, _t3552); _t3554 = *_hp; free(_hp); }
        (void)_t3554;
        Str_delete(_t3552, &(Bool){1});
        Str *_t3555 = Str_lit("run", 3ULL);
        (void)_t3555;
        Bool _t3556 = Bool_or(_t3553, _t3554);
        (void)_t3556;
        ;
        ;
        Bool _t3557; { Bool *_hp = (Bool *)Str_eq(command, _t3555); _t3557 = *_hp; free(_hp); }
        (void)_t3557;
        Str_delete(_t3555, &(Bool){1});
        Bool _t3558 = Bool_or(_t3556, _t3557);
        (void)_t3558;
        ;
        ;
        if (_t3558) {
            Str *_t3475 = Str_lit("run", 3ULL);
            (void)_t3475;
            Bool _t3476; { Bool *_hp = (Bool *)Str_eq(command, _t3475); _t3476 = *_hp; free(_hp); }
            (void)_t3476;
            Str_delete(_t3475, &(Bool){1});
            Bool _t3477 = Bool_and(is_lib_mode, _t3476);
            (void)_t3477;
            ;
            if (_t3477) {
                Str *_t3350 = Str_lit("Str", 3ULL);
                (void)_t3350;
                U64 _t3351; { U64 *_hp = (U64 *)Str_size(); _t3351 = *_hp; free(_hp); }
                (void)_t3351;
                U64 _t3352 = 1;
                (void)_t3352;
                Array *_va70 = Array_new(_t3350, &(U64){_t3351}, &(U64){_t3352});
                (void)_va70;
                Str_delete(_t3350, &(Bool){1});
                ;
                ;
                U64 _t3353 = 0;
                (void)_t3353;
                Str *_t3354 = Str_lit("cannot run a library — use translate or build", 47ULL);
                (void)_t3354;
                Array_set(_va70, &(U64){_t3353}, _t3354);
                ;
                Str *_t3355 = Str_lit("src/til.til:510:19", 18ULL);
                (void)_t3355;
                panic(_t3355, _va70);
                Str_delete(_t3355, &(Bool){1});
            }
            ;
            Str *_t3478 = Str_lit("/", 1ULL);
            (void)_t3478;
            I64 *last_slash = Str_rfind(path, _t3478);
            (void)last_slash;
            Str_delete(_t3478, &(Bool){1});
            Str *basename = Str_clone(path);
            (void)basename;
            I64 _t3479 = 0;
            (void)_t3479;
            Bool _t3480; { Bool *_hp = (Bool *)I64_gte(last_slash, &(I64){_t3479}); _t3480 = *_hp; free(_hp); }
            (void)_t3480;
            ;
            if (_t3480) {
                I64 _t3356 = 1;
                (void)_t3356;
                I64 _t3357 = I64_add(DEREF(last_slash), _t3356);
                (void)_t3357;
                ;
                U64 _t3358; { U64 *_hp = (U64 *)Str_len(path); _t3358 = *_hp; free(_hp); }
                (void)_t3358;
                U64 _t3359 = I64_to_u64(DEREF(last_slash));
                (void)_t3359;
                U64 _t3360 = U64_sub(_t3358, _t3359);
                (void)_t3360;
                ;
                ;
                U64 _t3361 = 1;
                (void)_t3361;
                U64 _t3362 = I64_to_u64(_t3357);
                (void)_t3362;
                ;
                U64 _t3363 = U64_sub(_t3360, _t3361);
                (void)_t3363;
                ;
                ;
                basename = Str_substr(path, &(U64){_t3362}, &(U64){_t3363});
                ;
                ;
            }
            ;
            I64_delete(last_slash, &(Bool){1});
            U64 name_len; { U64 *_hp = (U64 *)Str_len(basename); name_len = *_hp; free(_hp); }
            (void)name_len;
            Str *_t3481 = Str_lit(".til", 4ULL);
            (void)_t3481;
            Bool _t3482; { Bool *_hp = (Bool *)Str_ends_with(basename, _t3481); _t3482 = *_hp; free(_hp); }
            (void)_t3482;
            Str_delete(_t3481, &(Bool){1});
            if (_t3482) {
                U64 _t3364 = 4;
                (void)_t3364;
                U64 _t3365 = U64_sub(name_len, _t3364);
                (void)_t3365;
                ;
                name_len = _t3365;
                ;
            }
            ;
            U64 _t3483 = 0;
            (void)_t3483;
            Str *name = Str_substr(basename, &(U64){_t3483}, &(U64){name_len});
            (void)name;
            ;
            Str_delete(basename, &(Bool){1});
            ;
            Str *_t3484 = Str_lit("gen/til/", 8ULL);
            (void)_t3484;
            Str *_t3485 = Str_concat(_t3484, name);
            (void)_t3485;
            Str_delete(_t3484, &(Bool){1});
            Str *_t3486 = Str_lit(".c", 2ULL);
            (void)_t3486;
            Str *c_path = Str_concat(_t3485, _t3486);
            (void)c_path;
            Str_delete(_t3485, &(Bool){1});
            Str_delete(_t3486, &(Bool){1});
            U64 _t3487; { U64 *_hp = (U64 *)Str_len(custom_c); _t3487 = *_hp; free(_hp); }
            (void)_t3487;
            U64 _t3488 = 0;
            (void)_t3488;
            Bool _t3489; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3487}, &(U64){_t3488}); _t3489 = *_hp; free(_hp); }
            (void)_t3489;
            ;
            ;
            if (_t3489) {
                c_path = Str_clone(custom_c);
            }
            ;
            Str *_t3490 = Str_lit("bin/til/", 8ULL);
            (void)_t3490;
            Str *bin_path = Str_concat(_t3490, name);
            (void)bin_path;
            Str_delete(_t3490, &(Bool){1});
            U64 _t3491; { U64 *_hp = (U64 *)Str_len(custom_bin); _t3491 = *_hp; free(_hp); }
            (void)_t3491;
            U64 _t3492 = 0;
            (void)_t3492;
            Bool _t3493; { Bool *_hp = (Bool *)U64_gt(&(U64){_t3491}, &(U64){_t3492}); _t3493 = *_hp; free(_hp); }
            (void)_t3493;
            ;
            ;
            if (_t3493) {
                bin_path = Str_clone(custom_bin);
            }
            ;
            Str *_t3494 = Str_lit("run", 3ULL);
            (void)_t3494;
            Bool _t3495; { Bool *_hp = (Bool *)Str_eq(command, _t3494); _t3495 = *_hp; free(_hp); }
            (void)_t3495;
            Str_delete(_t3494, &(Bool){1});
            Bool _t3496 = til_mode_is_lib_output(cur_mode);
            (void)_t3496;
            Bool _t3497 = Bool_not(_t3495);
            (void)_t3497;
            ;
            Bool do_lib = Bool_and(_t3496, _t3497);
            (void)do_lib;
            ;
            ;
            if (do_lib) {
                Str *_t3366 = Str_lit("mkdir -p gen/til gen/lib", 24ULL);
                (void)_t3366;
                I32 _t3367 = til_system(_t3366);
                (void)_t3367;
                Str_delete(_t3366, &(Bool){1});
                ;
            } else {
                Str *_t3372 = Str_lit("/", 1ULL);
                (void)_t3372;
                I64 cp_slash; { I64 *_hp = (I64 *)Str_rfind(c_path, _t3372); cp_slash = *_hp; free(_hp); }
                (void)cp_slash;
                Str_delete(_t3372, &(Bool){1});
                Str *_t3373 = Str_lit("/", 1ULL);
                (void)_t3373;
                I64 bp_slash; { I64 *_hp = (I64 *)Str_rfind(bin_path, _t3373); bp_slash = *_hp; free(_hp); }
                (void)bp_slash;
                Str_delete(_t3373, &(Bool){1});
                Str *cp_dir = Str_lit("gen/til", 7ULL);
                (void)cp_dir;
                I64 _t3374 = 0;
                (void)_t3374;
                Bool _t3375; { Bool *_hp = (Bool *)I64_gt(&(I64){cp_slash}, &(I64){_t3374}); _t3375 = *_hp; free(_hp); }
                (void)_t3375;
                ;
                if (_t3375) {
                    U64 _t3368 = 0;
                    (void)_t3368;
                    U64 _t3369 = I64_to_u64(cp_slash);
                    (void)_t3369;
                    cp_dir = Str_substr(c_path, &(U64){_t3368}, &(U64){_t3369});
                    ;
                    ;
                }
                ;
                ;
                Str *bp_dir = Str_lit("bin/til", 7ULL);
                (void)bp_dir;
                I64 _t3376 = 0;
                (void)_t3376;
                Bool _t3377; { Bool *_hp = (Bool *)I64_gt(&(I64){bp_slash}, &(I64){_t3376}); _t3377 = *_hp; free(_hp); }
                (void)_t3377;
                ;
                if (_t3377) {
                    U64 _t3370 = 0;
                    (void)_t3370;
                    U64 _t3371 = I64_to_u64(bp_slash);
                    (void)_t3371;
                    bp_dir = Str_substr(bin_path, &(U64){_t3370}, &(U64){_t3371});
                    ;
                    ;
                }
                ;
                ;
                Str *_t3378 = Str_lit("mkdir -p ", 9ULL);
                (void)_t3378;
                Str *_t3379 = Str_concat(_t3378, cp_dir);
                (void)_t3379;
                Str_delete(_t3378, &(Bool){1});
                Str_delete(cp_dir, &(Bool){1});
                Str *_t3380 = Str_lit(" ", 1ULL);
                (void)_t3380;
                Str *_t3381 = Str_concat(_t3379, _t3380);
                (void)_t3381;
                Str_delete(_t3379, &(Bool){1});
                Str_delete(_t3380, &(Bool){1});
                Str *_t3382 = Str_concat(_t3381, bp_dir);
                (void)_t3382;
                Str_delete(_t3381, &(Bool){1});
                Str_delete(bp_dir, &(Bool){1});
                I32 _t3383 = til_system(_t3382);
                (void)_t3383;
                Str_delete(_t3382, &(Bool){1});
                ;
            }
            I32 _t3498 = til_build(ast, cur_mode, run_tests, path, c_path);
            (void)_t3498;
            result = _t3498;
            ;
            I32 _t3499 = 0;
            (void)_t3499;
            Bool _t3500 = I32_eq(result, _t3499);
            (void)_t3500;
            ;
            Bool _t3501 = Bool_and(_t3500, do_lib);
            (void)_t3501;
            ;
            if (_t3501) {
                Str *_t3440 = Str_lit("gen/til/", 8ULL);
                (void)_t3440;
                Str *_t3441 = Str_concat(_t3440, name);
                (void)_t3441;
                Str_delete(_t3440, &(Bool){1});
                Str *_t3442 = Str_lit(".h", 2ULL);
                (void)_t3442;
                Str *h_path = Str_concat(_t3441, _t3442);
                (void)h_path;
                Str_delete(_t3441, &(Bool){1});
                Str_delete(_t3442, &(Bool){1});
                Str *_t3443 = Str_lit("gen/til/", 8ULL);
                (void)_t3443;
                Str *_t3444 = Str_concat(_t3443, name);
                (void)_t3444;
                Str_delete(_t3443, &(Bool){1});
                Str *_t3445 = Str_lit(".til", 4ULL);
                (void)_t3445;
                Str *til_path = Str_concat(_t3444, _t3445);
                (void)til_path;
                Str_delete(_t3444, &(Bool){1});
                Str_delete(_t3445, &(Bool){1});
                I32 _t3446 = til_build_header(ast, h_path);
                (void)_t3446;
                result = _t3446;
                ;
                I32 _t3447 = 0;
                (void)_t3447;
                Bool _t3448 = I32_eq(result, _t3447);
                (void)_t3448;
                ;
                if (_t3448) {
                    I32 _t3384 = til_build_til_binding(ast, til_path, name);
                    (void)_t3384;
                    result = _t3384;
                    ;
                }
                ;
                I32 _t3449 = 0;
                (void)_t3449;
                Str *_t3450 = Str_lit("translate", 9ULL);
                (void)_t3450;
                Bool _t3451 = I32_eq(result, _t3449);
                (void)_t3451;
                ;
                Bool _t3452; { Bool *_hp = (Bool *)Str_eq(command, _t3450); _t3452 = *_hp; free(_hp); }
                (void)_t3452;
                Str_delete(_t3450, &(Bool){1});
                Bool _t3453 = Bool_and(_t3451, _t3452);
                (void)_t3453;
                ;
                ;
                if (_t3453) {
                    Str *_t3385 = Str_lit("Str", 3ULL);
                    (void)_t3385;
                    U64 _t3386; { U64 *_hp = (U64 *)Str_size(); _t3386 = *_hp; free(_hp); }
                    (void)_t3386;
                    U64 _t3387 = 1;
                    (void)_t3387;
                    Array *_va71 = Array_new(_t3385, &(U64){_t3386}, &(U64){_t3387});
                    (void)_va71;
                    Str_delete(_t3385, &(Bool){1});
                    ;
                    ;
                    Str *_t3388 = Str_lit("Generated: ", 11ULL);
                    (void)_t3388;
                    U64 _t3389 = 0;
                    (void)_t3389;
                    Str *_t3390 = Str_concat(_t3388, c_path);
                    (void)_t3390;
                    Str_delete(_t3388, &(Bool){1});
                    Array_set(_va71, &(U64){_t3389}, _t3390);
                    ;
                    println(_va71);
                    Str *_t3391 = Str_lit("Str", 3ULL);
                    (void)_t3391;
                    U64 _t3392; { U64 *_hp = (U64 *)Str_size(); _t3392 = *_hp; free(_hp); }
                    (void)_t3392;
                    U64 _t3393 = 1;
                    (void)_t3393;
                    Array *_va72 = Array_new(_t3391, &(U64){_t3392}, &(U64){_t3393});
                    (void)_va72;
                    Str_delete(_t3391, &(Bool){1});
                    ;
                    ;
                    Str *_t3394 = Str_lit("Generated: ", 11ULL);
                    (void)_t3394;
                    U64 _t3395 = 0;
                    (void)_t3395;
                    Str *_t3396 = Str_concat(_t3394, h_path);
                    (void)_t3396;
                    Str_delete(_t3394, &(Bool){1});
                    Array_set(_va72, &(U64){_t3395}, _t3396);
                    ;
                    println(_va72);
                    Str *_t3397 = Str_lit("Str", 3ULL);
                    (void)_t3397;
                    U64 _t3398; { U64 *_hp = (U64 *)Str_size(); _t3398 = *_hp; free(_hp); }
                    (void)_t3398;
                    U64 _t3399 = 1;
                    (void)_t3399;
                    Array *_va73 = Array_new(_t3397, &(U64){_t3398}, &(U64){_t3399});
                    (void)_va73;
                    Str_delete(_t3397, &(Bool){1});
                    ;
                    ;
                    Str *_t3400 = Str_lit("Generated: ", 11ULL);
                    (void)_t3400;
                    U64 _t3401 = 0;
                    (void)_t3401;
                    Str *_t3402 = Str_concat(_t3400, til_path);
                    (void)_t3402;
                    Str_delete(_t3400, &(Bool){1});
                    Array_set(_va73, &(U64){_t3401}, _t3402);
                    ;
                    println(_va73);
                }
                ;
                I32 _t3454 = 0;
                (void)_t3454;
                Str *_t3455 = Str_lit("build", 5ULL);
                (void)_t3455;
                Bool _t3456 = I32_eq(result, _t3454);
                (void)_t3456;
                ;
                Bool _t3457; { Bool *_hp = (Bool *)Str_eq(command, _t3455); _t3457 = *_hp; free(_hp); }
                (void)_t3457;
                Str_delete(_t3455, &(Bool){1});
                Bool _t3458 = Bool_and(_t3456, _t3457);
                (void)_t3458;
                ;
                ;
                if (_t3458) {
                    I32 _t3437 = til_compile_lib(c_path, name, ext_c_path, user_c, lflags);
                    (void)_t3437;
                    result = _t3437;
                    ;
                    I32 _t3438 = 0;
                    (void)_t3438;
                    Bool _t3439 = I32_eq(result, _t3438);
                    (void)_t3439;
                    ;
                    if (_t3439) {
                        Str *_t3403 = Str_lit("Str", 3ULL);
                        (void)_t3403;
                        U64 _t3404; { U64 *_hp = (U64 *)Str_size(); _t3404 = *_hp; free(_hp); }
                        (void)_t3404;
                        U64 _t3405 = 1;
                        (void)_t3405;
                        Array *_va74 = Array_new(_t3403, &(U64){_t3404}, &(U64){_t3405});
                        (void)_va74;
                        Str_delete(_t3403, &(Bool){1});
                        ;
                        ;
                        Str *_t3406 = Str_lit("Generated: ", 11ULL);
                        (void)_t3406;
                        U64 _t3407 = 0;
                        (void)_t3407;
                        Str *_t3408 = Str_concat(_t3406, c_path);
                        (void)_t3408;
                        Str_delete(_t3406, &(Bool){1});
                        Array_set(_va74, &(U64){_t3407}, _t3408);
                        ;
                        println(_va74);
                        Str *_t3409 = Str_lit("Str", 3ULL);
                        (void)_t3409;
                        U64 _t3410; { U64 *_hp = (U64 *)Str_size(); _t3410 = *_hp; free(_hp); }
                        (void)_t3410;
                        U64 _t3411 = 1;
                        (void)_t3411;
                        Array *_va75 = Array_new(_t3409, &(U64){_t3410}, &(U64){_t3411});
                        (void)_va75;
                        Str_delete(_t3409, &(Bool){1});
                        ;
                        ;
                        Str *_t3412 = Str_lit("Generated: ", 11ULL);
                        (void)_t3412;
                        U64 _t3413 = 0;
                        (void)_t3413;
                        Str *_t3414 = Str_concat(_t3412, h_path);
                        (void)_t3414;
                        Str_delete(_t3412, &(Bool){1});
                        Array_set(_va75, &(U64){_t3413}, _t3414);
                        ;
                        println(_va75);
                        Str *_t3415 = Str_lit("Str", 3ULL);
                        (void)_t3415;
                        U64 _t3416; { U64 *_hp = (U64 *)Str_size(); _t3416 = *_hp; free(_hp); }
                        (void)_t3416;
                        U64 _t3417 = 1;
                        (void)_t3417;
                        Array *_va76 = Array_new(_t3415, &(U64){_t3416}, &(U64){_t3417});
                        (void)_va76;
                        Str_delete(_t3415, &(Bool){1});
                        ;
                        ;
                        Str *_t3418 = Str_lit("Generated: ", 11ULL);
                        (void)_t3418;
                        U64 _t3419 = 0;
                        (void)_t3419;
                        Str *_t3420 = Str_concat(_t3418, til_path);
                        (void)_t3420;
                        Str_delete(_t3418, &(Bool){1});
                        Array_set(_va76, &(U64){_t3419}, _t3420);
                        ;
                        println(_va76);
                        Str *_t3421 = Str_lit("Str", 3ULL);
                        (void)_t3421;
                        U64 _t3422; { U64 *_hp = (U64 *)Str_size(); _t3422 = *_hp; free(_hp); }
                        (void)_t3422;
                        U64 _t3423 = 1;
                        (void)_t3423;
                        Array *_va77 = Array_new(_t3421, &(U64){_t3422}, &(U64){_t3423});
                        (void)_va77;
                        Str_delete(_t3421, &(Bool){1});
                        ;
                        ;
                        Str *_t3424 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t3424;
                        Str *_t3425 = Str_concat(_t3424, name);
                        (void)_t3425;
                        Str_delete(_t3424, &(Bool){1});
                        Str *_t3426 = Str_lit(".so", 3ULL);
                        (void)_t3426;
                        U64 _t3427 = 0;
                        (void)_t3427;
                        Str *_t3428 = Str_concat(_t3425, _t3426);
                        (void)_t3428;
                        Str_delete(_t3425, &(Bool){1});
                        Str_delete(_t3426, &(Bool){1});
                        Array_set(_va77, &(U64){_t3427}, _t3428);
                        ;
                        println(_va77);
                        Str *_t3429 = Str_lit("Str", 3ULL);
                        (void)_t3429;
                        U64 _t3430; { U64 *_hp = (U64 *)Str_size(); _t3430 = *_hp; free(_hp); }
                        (void)_t3430;
                        U64 _t3431 = 1;
                        (void)_t3431;
                        Array *_va78 = Array_new(_t3429, &(U64){_t3430}, &(U64){_t3431});
                        (void)_va78;
                        Str_delete(_t3429, &(Bool){1});
                        ;
                        ;
                        Str *_t3432 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t3432;
                        Str *_t3433 = Str_concat(_t3432, name);
                        (void)_t3433;
                        Str_delete(_t3432, &(Bool){1});
                        Str *_t3434 = Str_lit(".a", 2ULL);
                        (void)_t3434;
                        U64 _t3435 = 0;
                        (void)_t3435;
                        Str *_t3436 = Str_concat(_t3433, _t3434);
                        (void)_t3436;
                        Str_delete(_t3433, &(Bool){1});
                        Str_delete(_t3434, &(Bool){1});
                        Array_set(_va78, &(U64){_t3435}, _t3436);
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
            I32 _t3502 = 0;
            (void)_t3502;
            Bool _t3503 = I32_eq(result, _t3502);
            (void)_t3503;
            ;
            Bool _t3504 = Bool_not(do_lib);
            (void)_t3504;
            Str *_t3505 = Str_lit("translate", 9ULL);
            (void)_t3505;
            Bool _t3506 = Bool_and(_t3503, _t3504);
            (void)_t3506;
            ;
            ;
            Bool _t3507; { Bool *_hp = (Bool *)Str_eq(command, _t3505); _t3507 = *_hp; free(_hp); }
            (void)_t3507;
            Str_delete(_t3505, &(Bool){1});
            Bool _t3508 = Bool_and(_t3506, _t3507);
            (void)_t3508;
            ;
            ;
            if (_t3508) {
                Str *_t3459 = Str_lit("Str", 3ULL);
                (void)_t3459;
                U64 _t3460; { U64 *_hp = (U64 *)Str_size(); _t3460 = *_hp; free(_hp); }
                (void)_t3460;
                U64 _t3461 = 1;
                (void)_t3461;
                Array *_va79 = Array_new(_t3459, &(U64){_t3460}, &(U64){_t3461});
                (void)_va79;
                Str_delete(_t3459, &(Bool){1});
                ;
                ;
                Str *_t3462 = Str_lit("Generated: ", 11ULL);
                (void)_t3462;
                U64 _t3463 = 0;
                (void)_t3463;
                Str *_t3464 = Str_concat(_t3462, c_path);
                (void)_t3464;
                Str_delete(_t3462, &(Bool){1});
                Array_set(_va79, &(U64){_t3463}, _t3464);
                ;
                println(_va79);
            }
            ;
            I32 _t3509 = 0;
            (void)_t3509;
            Bool _t3510 = I32_eq(result, _t3509);
            (void)_t3510;
            ;
            Bool _t3511 = Bool_not(do_lib);
            (void)_t3511;
            Str *_t3512 = Str_lit("translate", 9ULL);
            (void)_t3512;
            Bool _t3513; { Bool *_hp = (Bool *)Str_eq(command, _t3512); _t3513 = *_hp; free(_hp); }
            (void)_t3513;
            Str_delete(_t3512, &(Bool){1});
            Bool _t3514 = Bool_and(_t3510, _t3511);
            (void)_t3514;
            ;
            ;
            Bool _t3515 = Bool_not(_t3513);
            (void)_t3515;
            ;
            Bool _t3516 = Bool_and(_t3514, _t3515);
            (void)_t3516;
            ;
            ;
            if (_t3516) {
                I32 _t3465 = til_compile_c(c_path, bin_path, ext_c_path, user_c, lflags);
                (void)_t3465;
                result = _t3465;
                ;
            }
            ;
            Str_delete(c_path, &(Bool){1});
            I32 _t3517 = 0;
            (void)_t3517;
            Bool _t3518 = I32_eq(result, _t3517);
            (void)_t3518;
            ;
            Bool _t3519 = Bool_not(do_lib);
            (void)_t3519;
            ;
            Str *_t3520 = Str_lit("run", 3ULL);
            (void)_t3520;
            Bool _t3521 = Bool_and(_t3518, _t3519);
            (void)_t3521;
            ;
            ;
            Bool _t3522; { Bool *_hp = (Bool *)Str_eq(command, _t3520); _t3522 = *_hp; free(_hp); }
            (void)_t3522;
            Str_delete(_t3520, &(Bool){1});
            Bool _t3523 = Bool_and(_t3521, _t3522);
            (void)_t3523;
            ;
            ;
            if (_t3523) {
                Str *cmd = Str_clone(bin_path);
                (void)cmd;
                U64 *ui = malloc(sizeof(U64));
                *ui = 0;
                (void)ui;
                while (1) {
                    U64 _t3467; { U64 *_hp = (U64 *)Vec_len(user_argv); _t3467 = *_hp; free(_hp); }
                    (void)_t3467;
                    Bool _wcond3466; { Bool *_hp = (Bool *)U64_lt(ui, &(U64){_t3467}); _wcond3466 = *_hp; free(_hp); }
                    (void)_wcond3466;
                    ;
                    if (_wcond3466) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *uarg = Vec_get(user_argv, ui);
                    (void)uarg;
                    Str *_t3468 = Str_lit(" '", 2ULL);
                    (void)_t3468;
                    Str *_t3469 = Str_concat(cmd, _t3468);
                    (void)_t3469;
                    Str_delete(_t3468, &(Bool){1});
                    Str *_t3470 = Str_concat(_t3469, uarg);
                    (void)_t3470;
                    Str_delete(_t3469, &(Bool){1});
                    Str *_t3471 = Str_lit("'", 1ULL);
                    (void)_t3471;
                    cmd = Str_concat(_t3470, _t3471);
                    Str_delete(_t3470, &(Bool){1});
                    Str_delete(_t3471, &(Bool){1});
                    U64 _t3472 = 1;
                    (void)_t3472;
                    U64 _t3473 = U64_add(DEREF(ui), _t3472);
                    (void)_t3473;
                    ;
                    *ui = _t3473;
                    ;
                }
                U64_delete(ui, &(Bool){1});
                I32 _t3474 = til_system(cmd);
                (void)_t3474;
                Str_delete(cmd, &(Bool){1});
                result = _t3474;
                ;
            }
            ;
            Str_delete(bin_path, &(Bool){1});
        } else {
            Str *_t3549 = Str_lit("ast", 3ULL);
            (void)_t3549;
            Bool _t3550; { Bool *_hp = (Bool *)Str_eq(command, _t3549); _t3550 = *_hp; free(_hp); }
            (void)_t3550;
            Str_delete(_t3549, &(Bool){1});
            if (_t3550) {
                Mode *_t3536 = til_mode_none();
                (void)_t3536;
                Bool _t3537 = til_mode_eq(cur_mode, _t3536);
                (void)_t3537;
                Mode_delete(_t3536, &(Bool){1});
                Bool _t3538 = Bool_not(_t3537);
                (void)_t3538;
                ;
                if (_t3538) {
                    Str *_t3524 = Str_lit("Str", 3ULL);
                    (void)_t3524;
                    U64 _t3525; { U64 *_hp = (U64 *)Str_size(); _t3525 = *_hp; free(_hp); }
                    (void)_t3525;
                    U64 _t3526 = 1;
                    (void)_t3526;
                    Array *_va80 = Array_new(_t3524, &(U64){_t3525}, &(U64){_t3526});
                    (void)_va80;
                    Str_delete(_t3524, &(Bool){1});
                    ;
                    ;
                    Str *_t3527 = Str_lit("mode: ", 6ULL);
                    (void)_t3527;
                    Str *_t3528 = til_mode_name(cur_mode);
                    (void)_t3528;
                    U64 _t3529 = 0;
                    (void)_t3529;
                    Str *_t3530 = Str_concat(_t3527, _t3528);
                    (void)_t3530;
                    Str_delete(_t3527, &(Bool){1});
                    Str_delete(_t3528, &(Bool){1});
                    Array_set(_va80, &(U64){_t3529}, _t3530);
                    ;
                    println(_va80);
                } else {
                    Str *_t3531 = Str_lit("Str", 3ULL);
                    (void)_t3531;
                    U64 _t3532; { U64 *_hp = (U64 *)Str_size(); _t3532 = *_hp; free(_hp); }
                    (void)_t3532;
                    U64 _t3533 = 1;
                    (void)_t3533;
                    Array *_va81 = Array_new(_t3531, &(U64){_t3532}, &(U64){_t3533});
                    (void)_va81;
                    Str_delete(_t3531, &(Bool){1});
                    ;
                    ;
                    U64 _t3534 = 0;
                    (void)_t3534;
                    Str *_t3535 = Str_lit("mode: (none)", 12ULL);
                    (void)_t3535;
                    Array_set(_va81, &(U64){_t3534}, _t3535);
                    ;
                    println(_va81);
                }
                ;
                U32 _t3539 = 0;
                (void)_t3539;
                til_ast_print(ast, _t3539);
                ;
            } else {
                Str *_t3540 = Str_lit("Str", 3ULL);
                (void)_t3540;
                U64 _t3541; { U64 *_hp = (U64 *)Str_size(); _t3541 = *_hp; free(_hp); }
                (void)_t3541;
                U64 _t3542 = 1;
                (void)_t3542;
                Array *_va82 = Array_new(_t3540, &(U64){_t3541}, &(U64){_t3542});
                (void)_va82;
                Str_delete(_t3540, &(Bool){1});
                ;
                ;
                Str *_t3543 = Str_lit("error: unknown command '", 24ULL);
                (void)_t3543;
                Str *_t3544 = Str_concat(_t3543, command);
                (void)_t3544;
                Str_delete(_t3543, &(Bool){1});
                Str *_t3545 = Str_lit("'", 1ULL);
                (void)_t3545;
                U64 _t3546 = 0;
                (void)_t3546;
                Str *_t3547 = Str_concat(_t3544, _t3545);
                (void)_t3547;
                Str_delete(_t3544, &(Bool){1});
                Str_delete(_t3545, &(Bool){1});
                Array_set(_va82, &(U64){_t3546}, _t3547);
                ;
                println(_va82);
                usage();
                I32 _t3548 = 1;
                (void)_t3548;
                result = _t3548;
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
    I64 _t3637 = I32_to_i64(result);
    (void)_t3637;
    ;
    exit(_t3637);
    ;
    return 0;
}

