#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char til_U8;
typedef long long til_I64;
typedef struct til_Bool { til_U8 data; } til_Bool;
typedef void* til_Dynamic;
typedef const char* til_Type;

typedef struct til_IndexOutOfBoundsError til_IndexOutOfBoundsError;
typedef struct til_AllocError til_AllocError;
typedef struct til_Array til_Array;
typedef struct til_I64_OverflowError til_I64_OverflowError;
typedef struct til_Vec til_Vec;
typedef struct til_Str til_Str;
typedef struct til_U8_OverflowError til_U8_OverflowError;
typedef struct til_Introspection til_Introspection;
typedef struct til_CfVec2 til_CfVec2;
typedef struct til_CfRect til_CfRect;

struct til_CfVec2 {
    til_I64 x;
    til_I64 y;
};

struct til_CfRect {
    til_CfVec2 top_left;
    til_CfVec2 bottom_right;
};

struct til_Introspection {
};

struct til_Str {
    til_I64 c_string;
    til_I64 cap;
};

struct til_U8_OverflowError {
    til_Str msg;
};

struct til_Vec {
    til_Str type_name;
    til_I64 type_size;
    til_I64 ptr;
    til_I64 _len;
    til_I64 cap;
};

struct til_I64_OverflowError {
    til_Str msg;
};

struct til_Array {
    til_Str type_name;
    til_I64 type_size;
    til_I64 ptr;
    til_I64 _len;
};

struct til_AllocError {
    til_Str msg;
};

struct til_IndexOutOfBoundsError {
    til_Str msg;
};

til_Bool til_not(const til_Bool til_b);
til_Bool til_or(til_Array* til_args);
til_Bool til_and(til_Array* til_args);
void til_panic(const til_Str til_loc_str, til_Array* til_msgs);
void til_assertm(const til_Str til_loc_str, const til_Bool til_cond, const til_Str til_msg);
void til_println(til_Array* til_args);
int til_get_substr(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_start, const til_I64 til_end);
til_Str til_concat(const til_Str til_a, const til_Str til_b);
int til_format(til_Str* _ret, til_I64_OverflowError* _err1, til_IndexOutOfBoundsError* _err2, til_AllocError* _err3, const til_Str til_prefix, til_Array* til_args);
void til_test(const til_Str til_loc_str, const til_Bool til_cond, const til_Str til_msg);
void til_assert_eq(const til_Str til_loc_str, const til_I64 til_a, const til_I64 til_b);
void til_test_simple_add(void);
void til_test_nested_arithmetic(void);
void til_test_deeply_nested(void);
void til_test_string_concat(void);
void til_test_fold_variable(void);
void til_test_loc_folded_correctly(void);
void til_test_struct_fold_simple(void);
void til_test_struct_fold_values(void);
void til_test_struct_fold_nested(void);
til_I64 til_Array_len(const til_Array til_self);
int til_Array_new(til_Array* _ret, til_AllocError* _err1, const til_Type til_T, const til_I64 til_capacity);
int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array til_self, const til_I64 til_index, til_Dynamic* til_T);
int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64 til_index, const til_Dynamic til_value);
void til_Array_delete(til_Array* til_self);
til_Bool til_Bool_and(const til_Bool til_self, const til_Bool til_other);
til_Bool til_I64_eq(const til_I64 til_a, const til_I64 til_b);
til_Str til_I64_to_str(const til_I64 til_self);
til_I64 til_I64_from_str(const til_Str til_str);
void til_I64_inc(til_I64* til_self);
til_Bool til_I64_gteq(const til_I64 til_a, const til_I64 til_b);
til_Bool til_I64_lteq(const til_I64 til_a, const til_I64 til_b);
int til_Vec_new(til_Vec* _ret, til_AllocError* _err1, const til_Type til_T);
int til_Vec_push(til_AllocError* _err1, til_Vec* til_self, const til_Dynamic til_value);
int til_Vec_get(til_IndexOutOfBoundsError* _err1, const til_Vec til_self, const til_I64 til_index, til_Dynamic* til_T);
til_I64 til_Str_len(const til_Str til_self);
til_Bool til_Str_eq(const til_Str til_self, const til_Str til_other);
int til_Str_clone(til_Str* _ret, til_AllocError* _err1, const til_Str til_self);
til_Bool til_Str_contains(const til_Str til_self, const til_Str til_needle);
til_I64 til_Str_find(const til_Str til_self, const til_Str til_needle);
int til_Str_replacen(til_Str* _ret, til_AllocError* _err1, const til_Str til_self, const til_Str til_from, const til_Str til_to, const til_I64 til_n);
til_Bool til_U8_eq(const til_U8 til_self, const til_U8 til_other);
til_I64 til_U8_to_i64(const til_U8 til_self);
int til_U8_from_i64(til_U8* _ret, til_U8_OverflowError* _err1, const til_I64 til_self);
til_Bool til_Introspection_has_const(const til_Str til_type_name, const til_Str til_const_name);
til_Bool til_Introspection_has_field(const til_Str til_type_name, const til_Str til_field_name);

#include <ext.c>

const til_I64 til_size_of_IndexOutOfBoundsError = sizeof(til_IndexOutOfBoundsError);
const til_I64 til_size_of_AllocError = sizeof(til_AllocError);
const til_I64 til_size_of_Array = sizeof(til_Array);
const til_I64 til_size_of_Bool = sizeof(til_Bool);
const til_I64 til_size_of_I64_OverflowError = sizeof(til_I64_OverflowError);
const til_I64 til_size_of_I64 = sizeof(til_I64);
const til_I64 til_Vec_INIT_CAP = 16;
const til_I64 til_Vec_MAX_CAP = 1024;
const til_I64 til_size_of_Vec = sizeof(til_Vec);
const til_I64 til_size_of_Str = sizeof(til_Str);
const til_I64 til_size_of_U8_OverflowError = sizeof(til_U8_OverflowError);
const til_I64 til_size_of_U8 = sizeof(til_U8);
const til_I64 til_size_of_Dynamic = sizeof(til_Dynamic);
const til_I64 til_size_of_Type = sizeof(til_Type);
const til_I64 til_size_of_Introspection = sizeof(til_Introspection);
const til_I64 til_size_of_CfVec2 = sizeof(til_CfVec2);
const til_I64 til_size_of_CfRect = sizeof(til_CfRect);
const til_I64 til_NULL = 0;
const til_I64 til_I64_SIZE = 8;
const til_I64 til_MIN_I64 = -922337203;
const til_I64 til_MAX_I64 = 9223372036854775807;
const til_I64 til_U8_SIZE = 1;
const til_I64 til_MIN_U8 = 0;
const til_I64 til_MAX_U8 = 255;

static inline til_I64 til_size_of(til_Str type_name) {
    if (strcmp((char*)type_name.c_string, "IndexOutOfBoundsError") == 0) return til_size_of_IndexOutOfBoundsError;
    if (strcmp((char*)type_name.c_string, "AllocError") == 0) return til_size_of_AllocError;
    if (strcmp((char*)type_name.c_string, "Array") == 0) return til_size_of_Array;
    if (strcmp((char*)type_name.c_string, "Bool") == 0) return til_size_of_Bool;
    if (strcmp((char*)type_name.c_string, "I64_OverflowError") == 0) return til_size_of_I64_OverflowError;
    if (strcmp((char*)type_name.c_string, "I64") == 0) return til_size_of_I64;
    if (strcmp((char*)type_name.c_string, "Vec") == 0) return til_size_of_Vec;
    if (strcmp((char*)type_name.c_string, "Str") == 0) return til_size_of_Str;
    if (strcmp((char*)type_name.c_string, "U8_OverflowError") == 0) return til_size_of_U8_OverflowError;
    if (strcmp((char*)type_name.c_string, "U8") == 0) return til_size_of_U8;
    if (strcmp((char*)type_name.c_string, "Dynamic") == 0) return til_size_of_Dynamic;
    if (strcmp((char*)type_name.c_string, "Type") == 0) return til_size_of_Type;
    if (strcmp((char*)type_name.c_string, "Introspection") == 0) return til_size_of_Introspection;
    if (strcmp((char*)type_name.c_string, "CfVec2") == 0) return til_size_of_CfVec2;
    if (strcmp((char*)type_name.c_string, "CfRect") == 0) return til_size_of_CfRect;
    fprintf(stderr, "size_of: unknown type %s\n", (char*)type_name.c_string);
    exit(1);
}

til_Bool til_not(const til_Bool til_b) {
    if (til_b.data) {
        return false;
    }
    return true;
}

til_Bool til_or(til_Array* til_args) {
    til_I64 _for_i_5 = 0;
    til_Bool til_val;
    while (til_lt(_for_i_5, til_Array_len((*til_args))).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp4;
        til_val = (til_Bool){.data = 0};
        til_IndexOutOfBoundsError _err0__tmp5 = {};
        int _status__tmp5 = til_Array_get(&_err0__tmp5, (*til_args), _for_i_5, (til_Dynamic*)&til_val);
        if (_status__tmp5 == 0) {
        } else if (_status__tmp5 == 1) {
            til_IndexOutOfBoundsError til_err = _err0__tmp5;
            til_Array _tmp7;
            til_AllocError _err_alloc__tmp8;
            til_IndexOutOfBoundsError _err_idx__tmp8;
            til_Str _tmp9 = til_err.msg;
            int _arr_status__tmp8 = til_Array_new(&_tmp7, &_err_alloc__tmp8, "Str", 1);
            if (_arr_status__tmp8 != 0) {
            }
            _arr_status__tmp8 = til_Array_set(&_err_idx__tmp8, &_tmp7, 0, &_tmp9);
            if (_arr_status__tmp8 != 0) {
            }
            til_panic(((til_Str){(til_I64)"src/core/bool.til:74:5:", 23}), &_tmp7);
            til_Array_delete(&_tmp7);
        }
        goto _end_catches__tmp4;
_catch_IndexOutOfBoundsError__tmp4: {
        til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp4;
        til_Array _tmp11;
        til_AllocError _err_alloc__tmp12;
        til_IndexOutOfBoundsError _err_idx__tmp12;
        til_Str _tmp13 = til_err.msg;
        int _arr_status__tmp12 = til_Array_new(&_tmp11, &_err_alloc__tmp12, "Str", 1);
        if (_arr_status__tmp12 != 0) {
        }
        _arr_status__tmp12 = til_Array_set(&_err_idx__tmp12, &_tmp11, 0, &_tmp13);
        if (_arr_status__tmp12 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/bool.til:74:5:", 23}), &_tmp11);
        til_Array_delete(&_tmp11);
        goto _end_catches__tmp4;
        }
_end_catches__tmp4:;
        if (til_val.data) {
            return true;
        }
        _for_i_5 = til_add(_for_i_5, 1);
    }
    return false;
}

til_Bool til_and(til_Array* til_args) {
    til_I64 _for_i_6 = 0;
    til_Bool til_val;
    while (til_lt(_for_i_6, til_Array_len((*til_args))).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp18;
        til_val = (til_Bool){.data = 0};
        til_IndexOutOfBoundsError _err0__tmp19 = {};
        int _status__tmp19 = til_Array_get(&_err0__tmp19, (*til_args), _for_i_6, (til_Dynamic*)&til_val);
        if (_status__tmp19 == 0) {
        } else if (_status__tmp19 == 1) {
            til_IndexOutOfBoundsError til_err = _err0__tmp19;
            til_Array _tmp21;
            til_AllocError _err_alloc__tmp22;
            til_IndexOutOfBoundsError _err_idx__tmp22;
            til_Str _tmp23 = til_err.msg;
            int _arr_status__tmp22 = til_Array_new(&_tmp21, &_err_alloc__tmp22, "Str", 1);
            if (_arr_status__tmp22 != 0) {
            }
            _arr_status__tmp22 = til_Array_set(&_err_idx__tmp22, &_tmp21, 0, &_tmp23);
            if (_arr_status__tmp22 != 0) {
            }
            til_panic(((til_Str){(til_I64)"src/core/bool.til:83:5:", 23}), &_tmp21);
            til_Array_delete(&_tmp21);
        }
        goto _end_catches__tmp18;
_catch_IndexOutOfBoundsError__tmp18: {
        til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp18;
        til_Array _tmp25;
        til_AllocError _err_alloc__tmp26;
        til_IndexOutOfBoundsError _err_idx__tmp26;
        til_Str _tmp27 = til_err.msg;
        int _arr_status__tmp26 = til_Array_new(&_tmp25, &_err_alloc__tmp26, "Str", 1);
        if (_arr_status__tmp26 != 0) {
        }
        _arr_status__tmp26 = til_Array_set(&_err_idx__tmp26, &_tmp25, 0, &_tmp27);
        if (_arr_status__tmp26 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/bool.til:83:5:", 23}), &_tmp25);
        til_Array_delete(&_tmp25);
        goto _end_catches__tmp18;
        }
_end_catches__tmp18:;
        if (til_not(til_val).data) {
            return false;
        }
        _for_i_6 = til_add(_for_i_6, 1);
    }
    return true;
}

void til_panic(const til_Str til_loc_str, til_Array* til_msgs) {
    til_single_print(til_loc_str);
    til_I64 _for_i_7 = 0;
    til_Str til_val;
    while (til_lt(_for_i_7, til_Array_len((*til_msgs))).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp32;
        til_val = (til_Str){.c_string = 0, .cap = 0};
        til_IndexOutOfBoundsError _err0__tmp33 = {};
        int _status__tmp33 = til_Array_get(&_err0__tmp33, (*til_msgs), _for_i_7, (til_Dynamic*)&til_val);
        if (_status__tmp33 == 0) {
        } else if (_status__tmp33 == 1) {
            til_IndexOutOfBoundsError til_err = _err0__tmp33;
            til_Array _tmp35;
            til_AllocError _err_alloc__tmp36;
            til_IndexOutOfBoundsError _err_idx__tmp36;
            til_Str _tmp37 = til_err.msg;
            int _arr_status__tmp36 = til_Array_new(&_tmp35, &_err_alloc__tmp36, "Str", 1);
            if (_arr_status__tmp36 != 0) {
            }
            _arr_status__tmp36 = til_Array_set(&_err_idx__tmp36, &_tmp35, 0, &_tmp37);
            if (_arr_status__tmp36 != 0) {
            }
            til_panic(((til_Str){(til_I64)"src/core/exit.til:9:5:", 22}), &_tmp35);
            til_Array_delete(&_tmp35);
        }
        goto _end_catches__tmp32;
_catch_IndexOutOfBoundsError__tmp32: {
        til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp32;
        til_Array _tmp39;
        til_AllocError _err_alloc__tmp40;
        til_IndexOutOfBoundsError _err_idx__tmp40;
        til_Str _tmp41 = til_err.msg;
        int _arr_status__tmp40 = til_Array_new(&_tmp39, &_err_alloc__tmp40, "Str", 1);
        if (_arr_status__tmp40 != 0) {
        }
        _arr_status__tmp40 = til_Array_set(&_err_idx__tmp40, &_tmp39, 0, &_tmp41);
        if (_arr_status__tmp40 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/exit.til:9:5:", 22}), &_tmp39);
        til_Array_delete(&_tmp39);
        goto _end_catches__tmp32;
        }
_end_catches__tmp32:;
        til_single_print(til_val);
        _for_i_7 = til_add(_for_i_7, 1);
    }
    til_single_print(((til_Str){(til_I64)"\n", 1}));
    til_print_flush();
    til_exit(1);
}

void til_assertm(const til_Str til_loc_str, const til_Bool til_cond, const til_Str til_msg) {
    if (til_not(til_cond).data) {
        til_Str _tmp45;
        til_I64_OverflowError _err0__tmp46;
        til_IndexOutOfBoundsError _err1__tmp46;
        til_AllocError _err2__tmp46;
        til_Array _tmp47;
        til_AllocError _err_alloc__tmp48;
        til_IndexOutOfBoundsError _err_idx__tmp48;
        til_Str _tmp49 = til_msg;
        int _arr_status__tmp48 = til_Array_new(&_tmp47, &_err_alloc__tmp48, "Str", 1);
        if (_arr_status__tmp48 != 0) {
        }
        _arr_status__tmp48 = til_Array_set(&_err_idx__tmp48, &_tmp47, 0, &_tmp49);
        if (_arr_status__tmp48 != 0) {
        }
        int _status__tmp46 = til_format(&_tmp45, &_err0__tmp46, &_err1__tmp46, &_err2__tmp46, ((til_Str){(til_I64)"assert failed: ", 15}), &_tmp47);
        if (_status__tmp46 != 0) {
        }
        til_Array_delete(&_tmp47);
        til_Array _tmp50;
        til_AllocError _err_alloc__tmp51;
        til_IndexOutOfBoundsError _err_idx__tmp51;
        int _arr_status__tmp51 = til_Array_new(&_tmp50, &_err_alloc__tmp51, "Str", 1);
        if (_arr_status__tmp51 != 0) {
        }
        _arr_status__tmp51 = til_Array_set(&_err_idx__tmp51, &_tmp50, 0, &_tmp45);
        if (_arr_status__tmp51 != 0) {
        }
        til_panic(til_loc_str, &_tmp50);
        til_Array_delete(&_tmp50);
    }
}

void til_println(til_Array* til_args) {
    til_I64 _for_i_9 = 0;
    til_Str til_val;
    while (til_lt(_for_i_9, til_Array_len((*til_args))).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp54;
        til_val = (til_Str){.c_string = 0, .cap = 0};
        til_IndexOutOfBoundsError _err0__tmp55 = {};
        int _status__tmp55 = til_Array_get(&_err0__tmp55, (*til_args), _for_i_9, (til_Dynamic*)&til_val);
        if (_status__tmp55 == 0) {
        } else if (_status__tmp55 == 1) {
            til_IndexOutOfBoundsError til_err = _err0__tmp55;
            til_Array _tmp57;
            til_AllocError _err_alloc__tmp58;
            til_IndexOutOfBoundsError _err_idx__tmp58;
            til_Str _tmp59 = til_err.msg;
            int _arr_status__tmp58 = til_Array_new(&_tmp57, &_err_alloc__tmp58, "Str", 1);
            if (_arr_status__tmp58 != 0) {
            }
            _arr_status__tmp58 = til_Array_set(&_err_idx__tmp58, &_tmp57, 0, &_tmp59);
            if (_arr_status__tmp58 != 0) {
            }
            til_panic(((til_Str){(til_I64)"src/core/print.til:16:5:", 24}), &_tmp57);
            til_Array_delete(&_tmp57);
        }
        goto _end_catches__tmp54;
_catch_IndexOutOfBoundsError__tmp54: {
        til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp54;
        til_Array _tmp61;
        til_AllocError _err_alloc__tmp62;
        til_IndexOutOfBoundsError _err_idx__tmp62;
        til_Str _tmp63 = til_err.msg;
        int _arr_status__tmp62 = til_Array_new(&_tmp61, &_err_alloc__tmp62, "Str", 1);
        if (_arr_status__tmp62 != 0) {
        }
        _arr_status__tmp62 = til_Array_set(&_err_idx__tmp62, &_tmp61, 0, &_tmp63);
        if (_arr_status__tmp62 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/print.til:16:5:", 24}), &_tmp61);
        til_Array_delete(&_tmp61);
        goto _end_catches__tmp54;
        }
_end_catches__tmp54:;
        til_single_print(til_val);
        _for_i_9 = til_add(_for_i_9, 1);
    }
    til_single_print(((til_Str){(til_I64)"\n", 1}));
    til_print_flush();
}

int til_get_substr(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_start, const til_I64 til_end) {
    if (til_lt(til_start, 0).data) {
        til_Str _tmp67;
        til_I64_OverflowError _err0__tmp68;
        til_IndexOutOfBoundsError _err1__tmp68;
        til_AllocError _err2__tmp68;
        til_Array _tmp69;
        til_AllocError _err_alloc__tmp70;
        til_IndexOutOfBoundsError _err_idx__tmp70;
        til_Str _tmp71 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp72 = til_I64_to_str(til_start);
        til_Str _tmp73 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp70 = til_Array_new(&_tmp69, &_err_alloc__tmp70, "Str", 3);
        if (_arr_status__tmp70 != 0) {
            *_err2 = _err_alloc__tmp70; return 2;
        }
        _arr_status__tmp70 = til_Array_set(&_err_idx__tmp70, &_tmp69, 0, &_tmp71);
        if (_arr_status__tmp70 != 0) {
            *_err1 = _err_idx__tmp70; return 1;
        }
        _arr_status__tmp70 = til_Array_set(&_err_idx__tmp70, &_tmp69, 1, &_tmp72);
        if (_arr_status__tmp70 != 0) {
            *_err1 = _err_idx__tmp70; return 1;
        }
        _arr_status__tmp70 = til_Array_set(&_err_idx__tmp70, &_tmp69, 2, &_tmp73);
        if (_arr_status__tmp70 != 0) {
            *_err1 = _err_idx__tmp70; return 1;
        }
        int _status__tmp68 = til_format(&_tmp67, &_err0__tmp68, &_err1__tmp68, &_err2__tmp68, ((til_Str){(til_I64)"src/core/str.til:368:48:", 24}), &_tmp69);
        if (_status__tmp68 != 0) {
            if (_status__tmp68 == 2) { *_err1 = _err1__tmp68; return 1; }
            if (_status__tmp68 == 3) { *_err2 = _err2__tmp68; return 2; }
        }
        til_Array_delete(&_tmp69);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp67};
        return 1;
    }
    if (til_lt(til_end, 0).data) {
        til_Str _tmp75;
        til_I64_OverflowError _err0__tmp76;
        til_IndexOutOfBoundsError _err1__tmp76;
        til_AllocError _err2__tmp76;
        til_Array _tmp77;
        til_AllocError _err_alloc__tmp78;
        til_IndexOutOfBoundsError _err_idx__tmp78;
        til_Str _tmp79 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp80 = til_I64_to_str(til_end);
        til_Str _tmp81 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp78 = til_Array_new(&_tmp77, &_err_alloc__tmp78, "Str", 3);
        if (_arr_status__tmp78 != 0) {
            *_err2 = _err_alloc__tmp78; return 2;
        }
        _arr_status__tmp78 = til_Array_set(&_err_idx__tmp78, &_tmp77, 0, &_tmp79);
        if (_arr_status__tmp78 != 0) {
            *_err1 = _err_idx__tmp78; return 1;
        }
        _arr_status__tmp78 = til_Array_set(&_err_idx__tmp78, &_tmp77, 1, &_tmp80);
        if (_arr_status__tmp78 != 0) {
            *_err1 = _err_idx__tmp78; return 1;
        }
        _arr_status__tmp78 = til_Array_set(&_err_idx__tmp78, &_tmp77, 2, &_tmp81);
        if (_arr_status__tmp78 != 0) {
            *_err1 = _err_idx__tmp78; return 1;
        }
        int _status__tmp76 = til_format(&_tmp75, &_err0__tmp76, &_err1__tmp76, &_err2__tmp76, ((til_Str){(til_I64)"src/core/str.til:371:48:", 24}), &_tmp77);
        if (_status__tmp76 != 0) {
            if (_status__tmp76 == 2) { *_err1 = _err1__tmp76; return 1; }
            if (_status__tmp76 == 3) { *_err2 = _err2__tmp76; return 2; }
        }
        til_Array_delete(&_tmp77);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp75};
        return 1;
    }
    if (til_gt(til_start, til_end).data) {
        til_Str _tmp83;
        til_I64_OverflowError _err0__tmp84;
        til_IndexOutOfBoundsError _err1__tmp84;
        til_AllocError _err2__tmp84;
        til_Array _tmp85;
        til_AllocError _err_alloc__tmp86;
        til_IndexOutOfBoundsError _err_idx__tmp86;
        til_Str _tmp87 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp88 = til_I64_to_str(til_start);
        til_Str _tmp89 = ((til_Str){(til_I64)" is greater than end index ", 27});
        til_Str _tmp90 = til_I64_to_str(til_end);
        int _arr_status__tmp86 = til_Array_new(&_tmp85, &_err_alloc__tmp86, "Str", 4);
        if (_arr_status__tmp86 != 0) {
            *_err2 = _err_alloc__tmp86; return 2;
        }
        _arr_status__tmp86 = til_Array_set(&_err_idx__tmp86, &_tmp85, 0, &_tmp87);
        if (_arr_status__tmp86 != 0) {
            *_err1 = _err_idx__tmp86; return 1;
        }
        _arr_status__tmp86 = til_Array_set(&_err_idx__tmp86, &_tmp85, 1, &_tmp88);
        if (_arr_status__tmp86 != 0) {
            *_err1 = _err_idx__tmp86; return 1;
        }
        _arr_status__tmp86 = til_Array_set(&_err_idx__tmp86, &_tmp85, 2, &_tmp89);
        if (_arr_status__tmp86 != 0) {
            *_err1 = _err_idx__tmp86; return 1;
        }
        _arr_status__tmp86 = til_Array_set(&_err_idx__tmp86, &_tmp85, 3, &_tmp90);
        if (_arr_status__tmp86 != 0) {
            *_err1 = _err_idx__tmp86; return 1;
        }
        int _status__tmp84 = til_format(&_tmp83, &_err0__tmp84, &_err1__tmp84, &_err2__tmp84, ((til_Str){(til_I64)"src/core/str.til:374:48:", 24}), &_tmp85);
        if (_status__tmp84 != 0) {
            if (_status__tmp84 == 2) { *_err1 = _err1__tmp84; return 1; }
            if (_status__tmp84 == 3) { *_err2 = _err2__tmp84; return 2; }
        }
        til_Array_delete(&_tmp85);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp83};
        return 1;
    }
    if (til_gt(til_end, til_Str_len(til_s)).data) {
        til_Str _tmp92;
        til_I64_OverflowError _err0__tmp93;
        til_IndexOutOfBoundsError _err1__tmp93;
        til_AllocError _err2__tmp93;
        til_Array _tmp94;
        til_AllocError _err_alloc__tmp95;
        til_IndexOutOfBoundsError _err_idx__tmp95;
        til_Str _tmp96 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp97 = til_I64_to_str(til_end);
        til_Str _tmp98 = ((til_Str){(til_I64)" is greater than string length ", 31});
        til_Str _tmp99 = til_I64_to_str(til_Str_len(til_s));
        int _arr_status__tmp95 = til_Array_new(&_tmp94, &_err_alloc__tmp95, "Str", 4);
        if (_arr_status__tmp95 != 0) {
            *_err2 = _err_alloc__tmp95; return 2;
        }
        _arr_status__tmp95 = til_Array_set(&_err_idx__tmp95, &_tmp94, 0, &_tmp96);
        if (_arr_status__tmp95 != 0) {
            *_err1 = _err_idx__tmp95; return 1;
        }
        _arr_status__tmp95 = til_Array_set(&_err_idx__tmp95, &_tmp94, 1, &_tmp97);
        if (_arr_status__tmp95 != 0) {
            *_err1 = _err_idx__tmp95; return 1;
        }
        _arr_status__tmp95 = til_Array_set(&_err_idx__tmp95, &_tmp94, 2, &_tmp98);
        if (_arr_status__tmp95 != 0) {
            *_err1 = _err_idx__tmp95; return 1;
        }
        _arr_status__tmp95 = til_Array_set(&_err_idx__tmp95, &_tmp94, 3, &_tmp99);
        if (_arr_status__tmp95 != 0) {
            *_err1 = _err_idx__tmp95; return 1;
        }
        int _status__tmp93 = til_format(&_tmp92, &_err0__tmp93, &_err1__tmp93, &_err2__tmp93, ((til_Str){(til_I64)"src/core/str.til:377:48:", 24}), &_tmp94);
        if (_status__tmp93 != 0) {
            if (_status__tmp93 == 2) { *_err1 = _err1__tmp93; return 1; }
            if (_status__tmp93 == 3) { *_err2 = _err2__tmp93; return 2; }
        }
        til_Array_delete(&_tmp94);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp92};
        return 1;
    }
    if (til_I64_eq(til_start, til_end).data) {
        til_Str _tmp101;
        til_I64_OverflowError _err0__tmp102;
        til_IndexOutOfBoundsError _err1__tmp102;
        til_AllocError _err2__tmp102;
        til_Array _tmp103;
        til_AllocError _err_alloc__tmp104;
        til_IndexOutOfBoundsError _err_idx__tmp104;
        til_Str _tmp105 = ((til_Str){(til_I64)"get_substr: start and end are the same (", 40});
        til_Str _tmp106 = til_I64_to_str(til_start);
        til_Str _tmp107 = ((til_Str){(til_I64)"), no substring", 15});
        int _arr_status__tmp104 = til_Array_new(&_tmp103, &_err_alloc__tmp104, "Str", 3);
        if (_arr_status__tmp104 != 0) {
            *_err2 = _err_alloc__tmp104; return 2;
        }
        _arr_status__tmp104 = til_Array_set(&_err_idx__tmp104, &_tmp103, 0, &_tmp105);
        if (_arr_status__tmp104 != 0) {
            *_err1 = _err_idx__tmp104; return 1;
        }
        _arr_status__tmp104 = til_Array_set(&_err_idx__tmp104, &_tmp103, 1, &_tmp106);
        if (_arr_status__tmp104 != 0) {
            *_err1 = _err_idx__tmp104; return 1;
        }
        _arr_status__tmp104 = til_Array_set(&_err_idx__tmp104, &_tmp103, 2, &_tmp107);
        if (_arr_status__tmp104 != 0) {
            *_err1 = _err_idx__tmp104; return 1;
        }
        int _status__tmp102 = til_format(&_tmp101, &_err0__tmp102, &_err1__tmp102, &_err2__tmp102, ((til_Str){(til_I64)"src/core/str.til:380:48:", 24}), &_tmp103);
        if (_status__tmp102 != 0) {
            if (_status__tmp102 == 2) { *_err1 = _err1__tmp102; return 1; }
            if (_status__tmp102 == 3) { *_err2 = _err2__tmp102; return 2; }
        }
        til_Array_delete(&_tmp103);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp101};
        return 1;
    }
    til_Str til_substr = {.c_string = 0, .cap = 0};
    til_substr.cap = til_sub(til_end, til_start);
    til_I64 _ret__tmp108;
    til_AllocError _err0__tmp108 = {};
    int _status__tmp108 = til_malloc(&_ret__tmp108, &_err0__tmp108, til_substr.cap);
    if (_status__tmp108 == 1) { *_err2 = _err0__tmp108; return 2; }
    til_substr.c_string = _ret__tmp108;
    if (til_I64_eq(til_NULL, til_substr.c_string).data) {
        til_Str _tmp110;
        til_I64_OverflowError _err0__tmp111;
        til_IndexOutOfBoundsError _err1__tmp111;
        til_AllocError _err2__tmp111;
        til_Array _tmp112;
        til_AllocError _err_alloc__tmp113;
        til_IndexOutOfBoundsError _err_idx__tmp113;
        til_Str _tmp114 = ((til_Str){(til_I64)"Str.get_substr: failed to allocate ", 35});
        til_Str _tmp115 = til_I64_to_str(til_substr.cap);
        til_Str _tmp116 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp113 = til_Array_new(&_tmp112, &_err_alloc__tmp113, "Str", 3);
        if (_arr_status__tmp113 != 0) {
            *_err2 = _err_alloc__tmp113; return 2;
        }
        _arr_status__tmp113 = til_Array_set(&_err_idx__tmp113, &_tmp112, 0, &_tmp114);
        if (_arr_status__tmp113 != 0) {
            *_err1 = _err_idx__tmp113; return 1;
        }
        _arr_status__tmp113 = til_Array_set(&_err_idx__tmp113, &_tmp112, 1, &_tmp115);
        if (_arr_status__tmp113 != 0) {
            *_err1 = _err_idx__tmp113; return 1;
        }
        _arr_status__tmp113 = til_Array_set(&_err_idx__tmp113, &_tmp112, 2, &_tmp116);
        if (_arr_status__tmp113 != 0) {
            *_err1 = _err_idx__tmp113; return 1;
        }
        int _status__tmp111 = til_format(&_tmp110, &_err0__tmp111, &_err1__tmp111, &_err2__tmp111, ((til_Str){(til_I64)"src/core/str.til:387:37:", 24}), &_tmp112);
        if (_status__tmp111 != 0) {
            if (_status__tmp111 == 2) { *_err1 = _err1__tmp111; return 1; }
            if (_status__tmp111 == 3) { *_err2 = _err2__tmp111; return 2; }
        }
        til_Array_delete(&_tmp112);
        *_err2 = (til_AllocError){.msg = _tmp110};
        return 2;
    }
    til_memcpy(til_substr.c_string, til_add(til_s.c_string, til_start), til_substr.cap);
    *_ret = til_substr;
    return 0;
}

til_Str til_concat(const til_Str til_a, const til_Str til_b) {
    til_AllocError _thrown_AllocError__tmp117;
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_add(til_a.cap, til_b.cap);
    if (til_lt(til_result.cap, til_a.cap).data) {
        til_Array _tmp119;
        til_AllocError _err_alloc__tmp120;
        til_IndexOutOfBoundsError _err_idx__tmp120;
        til_Str _tmp121 = ((til_Str){(til_I64)"concat: integer overflow", 24});
        int _arr_status__tmp120 = til_Array_new(&_tmp119, &_err_alloc__tmp120, "Str", 1);
        if (_arr_status__tmp120 != 0) {
        }
        _arr_status__tmp120 = til_Array_set(&_err_idx__tmp120, &_tmp119, 0, &_tmp121);
        if (_arr_status__tmp120 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:447:15:", 24}), &_tmp119);
        til_Array_delete(&_tmp119);
    }
    til_I64 _ret__tmp122;
    til_AllocError _err0__tmp122 = {};
    int _status__tmp122 = til_malloc(&_ret__tmp122, &_err0__tmp122, til_result.cap);
    if (_status__tmp122 == 1) { _thrown_AllocError__tmp117 = _err0__tmp122; goto _catch_AllocError__tmp117; }
    til_result.c_string = _ret__tmp122;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Array _tmp124;
        til_AllocError _err_alloc__tmp125;
        til_IndexOutOfBoundsError _err_idx__tmp125;
        til_Str _tmp126 = ((til_Str){(til_I64)"concat: malloc failed", 21});
        int _arr_status__tmp125 = til_Array_new(&_tmp124, &_err_alloc__tmp125, "Str", 1);
        if (_arr_status__tmp125 != 0) {
        }
        _arr_status__tmp125 = til_Array_set(&_err_idx__tmp125, &_tmp124, 0, &_tmp126);
        if (_arr_status__tmp125 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:452:15:", 24}), &_tmp124);
        til_Array_delete(&_tmp124);
    }
    til_memcpy(til_result.c_string, til_a.c_string, til_a.cap);
    til_memcpy(til_add(til_result.c_string, til_a.cap), til_b.c_string, til_b.cap);
    goto _end_catches__tmp117;
_catch_AllocError__tmp117: {
    til_AllocError til_err = _thrown_AllocError__tmp117;
    til_Array _tmp128;
    til_AllocError _err_alloc__tmp129;
    til_IndexOutOfBoundsError _err_idx__tmp129;
    til_Str _tmp130 = til_err.msg;
    int _arr_status__tmp129 = til_Array_new(&_tmp128, &_err_alloc__tmp129, "Str", 1);
    if (_arr_status__tmp129 != 0) {
    }
    _arr_status__tmp129 = til_Array_set(&_err_idx__tmp129, &_tmp128, 0, &_tmp130);
    if (_arr_status__tmp129 != 0) {
    }
    til_panic(((til_Str){(til_I64)"src/core/str.til:459:15:", 24}), &_tmp128);
    til_Array_delete(&_tmp128);
    goto _end_catches__tmp117;
    }
_end_catches__tmp117:;
    return til_result;
}

int til_format(til_Str* _ret, til_I64_OverflowError* _err1, til_IndexOutOfBoundsError* _err2, til_AllocError* _err3, const til_Str til_prefix, til_Array* til_args) {
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_prefix.cap;
    til_I64 til_i = 0;
    til_Str til_arg;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_arg = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp135 = {};
        int _status__tmp135 = til_Array_get(&_err0__tmp135, (*til_args), til_i, (til_Dynamic*)&til_arg);
        if (_status__tmp135 == 1) { *_err2 = _err0__tmp135; return 2; }
        til_result.cap = til_add(til_result.cap, til_arg.cap);
        if (til_lt(til_result.cap, til_arg.cap).data) {
            til_Str _tmp137;
            til_I64_OverflowError _err0__tmp138;
            til_IndexOutOfBoundsError _err1__tmp138;
            til_AllocError _err2__tmp138;
            til_Array _tmp139;
            til_AllocError _err_alloc__tmp140;
            til_IndexOutOfBoundsError _err_idx__tmp140;
            til_Str _tmp141 = ((til_Str){(til_I64)"format: integer overflow while summing cap for arg ", 51});
            til_Str _tmp142 = til_I64_to_str(til_i);
            int _arr_status__tmp140 = til_Array_new(&_tmp139, &_err_alloc__tmp140, "Str", 2);
            if (_arr_status__tmp140 != 0) {
                *_err3 = _err_alloc__tmp140; return 3;
            }
            _arr_status__tmp140 = til_Array_set(&_err_idx__tmp140, &_tmp139, 0, &_tmp141);
            if (_arr_status__tmp140 != 0) {
                *_err2 = _err_idx__tmp140; return 2;
            }
            _arr_status__tmp140 = til_Array_set(&_err_idx__tmp140, &_tmp139, 1, &_tmp142);
            if (_arr_status__tmp140 != 0) {
                *_err2 = _err_idx__tmp140; return 2;
            }
            int _status__tmp138 = til_format(&_tmp137, &_err0__tmp138, &_err1__tmp138, &_err2__tmp138, ((til_Str){(til_I64)"src/core/str.til:475:48:", 24}), &_tmp139);
            if (_status__tmp138 != 0) {
                if (_status__tmp138 == 1) { *_err1 = _err0__tmp138; return 1; }
                if (_status__tmp138 == 2) { *_err2 = _err1__tmp138; return 2; }
                if (_status__tmp138 == 3) { *_err3 = _err2__tmp138; return 3; }
            }
            til_Array_delete(&_tmp139);
            *_err1 = (til_I64_OverflowError){.msg = _tmp137};
            return 1;
        }
        til_I64_inc(&til_i);
    }
    til_I64 _ret__tmp143;
    til_AllocError _err0__tmp143 = {};
    int _status__tmp143 = til_malloc(&_ret__tmp143, &_err0__tmp143, til_result.cap);
    if (_status__tmp143 == 1) { *_err3 = _err0__tmp143; return 3; }
    til_result.c_string = _ret__tmp143;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Str _tmp145;
        til_I64_OverflowError _err0__tmp146;
        til_IndexOutOfBoundsError _err1__tmp146;
        til_AllocError _err2__tmp146;
        til_Array _tmp147;
        til_AllocError _err_alloc__tmp148;
        til_IndexOutOfBoundsError _err_idx__tmp148;
        til_Str _tmp149 = ((til_Str){(til_I64)"format: malloc failed for cap = ", 32});
        til_Str _tmp150 = til_I64_to_str(til_result.cap);
        int _arr_status__tmp148 = til_Array_new(&_tmp147, &_err_alloc__tmp148, "Str", 2);
        if (_arr_status__tmp148 != 0) {
            *_err3 = _err_alloc__tmp148; return 3;
        }
        _arr_status__tmp148 = til_Array_set(&_err_idx__tmp148, &_tmp147, 0, &_tmp149);
        if (_arr_status__tmp148 != 0) {
            *_err2 = _err_idx__tmp148; return 2;
        }
        _arr_status__tmp148 = til_Array_set(&_err_idx__tmp148, &_tmp147, 1, &_tmp150);
        if (_arr_status__tmp148 != 0) {
            *_err2 = _err_idx__tmp148; return 2;
        }
        int _status__tmp146 = til_format(&_tmp145, &_err0__tmp146, &_err1__tmp146, &_err2__tmp146, ((til_Str){(til_I64)"src/core/str.til:481:37:", 24}), &_tmp147);
        if (_status__tmp146 != 0) {
            if (_status__tmp146 == 1) { *_err1 = _err0__tmp146; return 1; }
            if (_status__tmp146 == 2) { *_err2 = _err1__tmp146; return 2; }
            if (_status__tmp146 == 3) { *_err3 = _err2__tmp146; return 3; }
        }
        til_Array_delete(&_tmp147);
        *_err3 = (til_AllocError){.msg = _tmp145};
        return 3;
    }
    til_I64 til_offset = 0;
    til_memcpy(til_result.c_string, til_prefix.c_string, til_prefix.cap);
    til_offset = til_prefix.cap;
    til_I64 _for_i_10 = 0;
    til_Str til_s;
    while (til_lt(_for_i_10, til_Array_len((*til_args))).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp152;
        til_s = (til_Str){.c_string = 0, .cap = 0};
        til_IndexOutOfBoundsError _err0__tmp153 = {};
        int _status__tmp153 = til_Array_get(&_err0__tmp153, (*til_args), _for_i_10, (til_Dynamic*)&til_s);
        if (_status__tmp153 == 0) {
        } else if (_status__tmp153 == 1) {
            til_IndexOutOfBoundsError til_err = _err0__tmp153;
            til_Array _tmp155;
            til_AllocError _err_alloc__tmp156;
            til_IndexOutOfBoundsError _err_idx__tmp156;
            til_Str _tmp157 = til_err.msg;
            int _arr_status__tmp156 = til_Array_new(&_tmp155, &_err_alloc__tmp156, "Str", 1);
            if (_arr_status__tmp156 != 0) {
                *_err3 = _err_alloc__tmp156; return 3;
            }
            _arr_status__tmp156 = til_Array_set(&_err_idx__tmp156, &_tmp155, 0, &_tmp157);
            if (_arr_status__tmp156 != 0) {
                *_err2 = _err_idx__tmp156; return 2;
            }
            til_panic(((til_Str){(til_I64)"src/core/str.til:488:5:", 23}), &_tmp155);
            til_Array_delete(&_tmp155);
        }
        goto _end_catches__tmp152;
_catch_IndexOutOfBoundsError__tmp152: {
        til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp152;
        til_Array _tmp159;
        til_AllocError _err_alloc__tmp160;
        til_IndexOutOfBoundsError _err_idx__tmp160;
        til_Str _tmp161 = til_err.msg;
        int _arr_status__tmp160 = til_Array_new(&_tmp159, &_err_alloc__tmp160, "Str", 1);
        if (_arr_status__tmp160 != 0) {
            *_err3 = _err_alloc__tmp160; return 3;
        }
        _arr_status__tmp160 = til_Array_set(&_err_idx__tmp160, &_tmp159, 0, &_tmp161);
        if (_arr_status__tmp160 != 0) {
            *_err2 = _err_idx__tmp160; return 2;
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:488:5:", 23}), &_tmp159);
        til_Array_delete(&_tmp159);
        goto _end_catches__tmp152;
        }
_end_catches__tmp152:;
        til_memcpy(til_add(til_result.c_string, til_offset), til_s.c_string, til_s.cap);
        til_offset = til_add(til_offset, til_s.cap);
        _for_i_10 = til_add(_for_i_10, 1);
    }
    *_ret = til_result;
    return 0;
}

void til_test(const til_Str til_loc_str, const til_Bool til_cond, const til_Str til_msg) {
    til_assertm(til_loc_str, til_cond, til_msg);
}

void til_assert_eq(const til_Str til_loc_str, const til_I64 til_a, const til_I64 til_b) {
    if (til_not(til_I64_eq(til_a, til_b)).data) {
        til_Array _tmp166;
        til_AllocError _err_alloc__tmp167;
        til_IndexOutOfBoundsError _err_idx__tmp167;
        til_Str _tmp168 = til_loc_str;
        til_Str _tmp169 = ((til_Str){(til_I64)"assert_eq failed: expected '", 28});
        til_Str _tmp170 = til_I64_to_str(til_a);
        til_Str _tmp171 = ((til_Str){(til_I64)"', found '", 10});
        til_Str _tmp172 = til_I64_to_str(til_b);
        til_Str _tmp173 = ((til_Str){(til_I64)"'", 1});
        int _arr_status__tmp167 = til_Array_new(&_tmp166, &_err_alloc__tmp167, "Str", 6);
        if (_arr_status__tmp167 != 0) {
        }
        _arr_status__tmp167 = til_Array_set(&_err_idx__tmp167, &_tmp166, 0, &_tmp168);
        if (_arr_status__tmp167 != 0) {
        }
        _arr_status__tmp167 = til_Array_set(&_err_idx__tmp167, &_tmp166, 1, &_tmp169);
        if (_arr_status__tmp167 != 0) {
        }
        _arr_status__tmp167 = til_Array_set(&_err_idx__tmp167, &_tmp166, 2, &_tmp170);
        if (_arr_status__tmp167 != 0) {
        }
        _arr_status__tmp167 = til_Array_set(&_err_idx__tmp167, &_tmp166, 3, &_tmp171);
        if (_arr_status__tmp167 != 0) {
        }
        _arr_status__tmp167 = til_Array_set(&_err_idx__tmp167, &_tmp166, 4, &_tmp172);
        if (_arr_status__tmp167 != 0) {
        }
        _arr_status__tmp167 = til_Array_set(&_err_idx__tmp167, &_tmp166, 5, &_tmp173);
        if (_arr_status__tmp167 != 0) {
        }
        til_println(&_tmp166);
        til_Array_delete(&_tmp166);
        til_exit(1);
    }
}

void til_test_simple_add(void) {
    const til_I64 til_result = 3;
    til_test(((til_Str){(til_I64)"src/test/constfold.til:8:10:", 28}), til_I64_eq(til_result, 3), ((til_Str){(til_I64)"add(1, 2) should be 3", 21}));
}

void til_test_nested_arithmetic(void) {
    const til_I64 til_result = 15;
    til_test(((til_Str){(til_I64)"src/test/constfold.til:15:10:", 29}), til_I64_eq(til_result, 15), ((til_Str){(til_I64)"mul(add(1, 2), sub(10, 5)) should be 15", 39}));
}

void til_test_deeply_nested(void) {
    const til_I64 til_result = 26;
    til_test(((til_Str){(til_I64)"src/test/constfold.til:22:10:", 29}), til_I64_eq(til_result, 26), ((til_Str){(til_I64)"add(mul(2, 3), mul(4, 5)) should be 26", 38}));
}

void til_test_string_concat(void) {
    const til_Str til_result = ((til_Str){(til_I64)"hello world", 11});
    til_test(((til_Str){(til_I64)"src/test/constfold.til:29:10:", 29}), til_Str_eq(til_result, ((til_Str){(til_I64)"hello world", 11})), ((til_Str){(til_I64)"concat is folded at compile time", 32}));
}

void til_test_fold_variable(void) {
    const til_I64 til_x = 5;
    const til_I64 til_result = 8;
    til_test(((til_Str){(til_I64)"src/test/constfold.til:38:10:", 29}), til_I64_eq(til_result, 8), ((til_Str){(til_I64)"add(x, 3) should fold to 8", 26}));
}

void til_test_loc_folded_correctly(void) {
    const til_Str til_location = ((til_Str){(til_I64)"src/test/constfold.til:44:17:", 29});
    til_test(((til_Str){(til_I64)"src/test/constfold.til:45:10:", 29}), til_Str_contains(til_location, ((til_Str){(til_I64)"constfold.til", 13})), ((til_Str){(til_I64)"loc() should contain filename", 29}));
    til_test(((til_Str){(til_I64)"src/test/constfold.til:46:10:", 29}), til_Str_contains(til_location, ((til_Str){(til_I64)":44:", 4})), ((til_Str){(til_I64)"loc() should contain correct line number", 40}));
}

void til_test_struct_fold_simple(void) {
    const til_CfVec2 til_v = {.x = 42, .y = 99};
    til_assert_eq(((til_Str){(til_I64)"src/test/constfold.til:71:15:", 29}), 42, til_v.x);
    til_assert_eq(((til_Str){(til_I64)"src/test/constfold.til:72:15:", 29}), 99, til_v.y);
}

void til_test_struct_fold_values(void) {
    const til_CfVec2 til_p = {.x = 10, .y = 20};
    til_assert_eq(((til_Str){(til_I64)"src/test/constfold.til:79:15:", 29}), 10, til_p.x);
    til_assert_eq(((til_Str){(til_I64)"src/test/constfold.til:80:15:", 29}), 20, til_p.y);
}

void til_test_struct_fold_nested(void) {
    const til_CfRect til_r = {.top_left = (til_CfVec2){.x = 5, .y = 10}, .bottom_right = (til_CfVec2){.x = 100, .y = 200}};
    til_assert_eq(((til_Str){(til_I64)"src/test/constfold.til:97:15:", 29}), 5, til_r.top_left.x);
    til_assert_eq(((til_Str){(til_I64)"src/test/constfold.til:98:15:", 29}), 10, til_r.top_left.y);
    til_assert_eq(((til_Str){(til_I64)"src/test/constfold.til:99:15:", 29}), 100, til_r.bottom_right.x);
    til_assert_eq(((til_Str){(til_I64)"src/test/constfold.til:100:15:", 30}), 200, til_r.bottom_right.y);
}

til_I64 til_Array_len(const til_Array til_self) {
    return til_self._len;
}

int til_Array_new(til_Array* _ret, til_AllocError* _err1, const til_Type til_T, const til_I64 til_capacity) {
    til_Array til_arr = {.type_name = ((til_Str){(til_I64)"", 0}), .type_size = 0, .ptr = 0, ._len = 0};
    til_arr.type_name = ((til_Str){(til_I64)"T", 1});
    til_arr.type_size = til_size_of(((til_Str){(til_I64)til_T, strlen(til_T)}));
    const til_I64 til_size_bytes = til_mul(til_capacity, til_arr.type_size);
    til_I64 _ret__tmp185;
    til_AllocError _err0__tmp185 = {};
    int _status__tmp185 = til_malloc(&_ret__tmp185, &_err0__tmp185, til_size_bytes);
    if (_status__tmp185 == 1) { *_err1 = _err0__tmp185; return 1; }
    til_arr.ptr = _ret__tmp185;
    til_U8 _tmp186;
    til_U8_OverflowError _err0__tmp187;
    int _status__tmp187 = til_U8_from_i64(&_tmp186, &_err0__tmp187, 0);
    if (_status__tmp187 != 0) {
    }
    til_memset(til_arr.ptr, _tmp186, til_size_bytes);
    til_arr._len = til_capacity;
    *_ret = til_arr;
    return 0;
}

int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array til_self, const til_I64 til_index, til_Dynamic* til_T) {
    if (til_I64_gteq(til_index, til_self._len).data) {
        til_Str _tmp190;
        til_I64_OverflowError _err0__tmp191;
        til_IndexOutOfBoundsError _err1__tmp191;
        til_AllocError _err2__tmp191;
        til_Array _tmp192;
        til_AllocError _err_alloc__tmp193;
        til_IndexOutOfBoundsError _err_idx__tmp193;
        til_Str _tmp194 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        int _arr_status__tmp193 = til_Array_new(&_tmp192, &_err_alloc__tmp193, "Str", 1);
        if (_arr_status__tmp193 != 0) {
        }
        _arr_status__tmp193 = til_Array_set(&_err_idx__tmp193, &_tmp192, 0, &_tmp194);
        if (_arr_status__tmp193 != 0) {
            *_err1 = _err_idx__tmp193; return 1;
        }
        int _status__tmp191 = til_format(&_tmp190, &_err0__tmp191, &_err1__tmp191, &_err2__tmp191, ((til_Str){(til_I64)"src/core/array.til:41:52:", 25}), &_tmp192);
        if (_status__tmp191 != 0) {
            if (_status__tmp191 == 2) { *_err1 = _err1__tmp191; return 1; }
        }
        til_Array_delete(&_tmp192);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp190};
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_I64_gteq(til_index, til_self->_len).data) {
        til_Str _tmp197;
        til_I64_OverflowError _err0__tmp198;
        til_IndexOutOfBoundsError _err1__tmp198;
        til_AllocError _err2__tmp198;
        til_Array _tmp199;
        til_AllocError _err_alloc__tmp200;
        til_IndexOutOfBoundsError _err_idx__tmp200;
        til_Str _tmp201 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        int _arr_status__tmp200 = til_Array_new(&_tmp199, &_err_alloc__tmp200, "Str", 1);
        if (_arr_status__tmp200 != 0) {
        }
        _arr_status__tmp200 = til_Array_set(&_err_idx__tmp200, &_tmp199, 0, &_tmp201);
        if (_arr_status__tmp200 != 0) {
            *_err1 = _err_idx__tmp200; return 1;
        }
        int _status__tmp198 = til_format(&_tmp197, &_err0__tmp198, &_err1__tmp198, &_err2__tmp198, ((til_Str){(til_I64)"src/core/array.til:56:52:", 25}), &_tmp199);
        if (_status__tmp198 != 0) {
            if (_status__tmp198 == 2) { *_err1 = _err1__tmp198; return 1; }
        }
        til_Array_delete(&_tmp199);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp197};
        return 1;
    }
    til_I64 til_dest = til_add(til_self->ptr, til_mul(til_index, til_self->type_size));
    til_memcpy(til_dest, (til_I64)til_value, til_self->type_size);
    return 0;
}

void til_Array_delete(til_Array* til_self) {
    til_free(til_self->ptr);
    til_self->ptr = 0;
    til_self->_len = 0;
}

til_Bool til_Bool_and(const til_Bool til_self, const til_Bool til_other) {
    if (til_self.data) {
        return til_other;
    }
    return false;
}

til_Bool til_I64_eq(const til_I64 til_a, const til_I64 til_b) {
    if (til_gt(til_a, til_b).data) {
        return false;
    }
    if (til_gt(til_b, til_a).data) {
        return false;
    }
    if (til_lt(til_a, til_b).data) {
        return false;
    }
    if (til_lt(til_b, til_a).data) {
        return false;
    }
    return true;
}

til_Str til_I64_to_str(const til_I64 til_self) {
    return til_i64_to_str(til_self);
}

til_I64 til_I64_from_str(const til_Str til_str) {
    return til_str_to_i64(til_str);
}

void til_I64_inc(til_I64* til_self) {
    *til_self = til_add((*til_self), 1);
}

til_Bool til_I64_gteq(const til_I64 til_a, const til_I64 til_b) {
    if (til_gt(til_a, til_b).data) {
        return true;
    }
    if (til_lt(til_a, til_b).data) {
        return false;
    }
    return true;
}

til_Bool til_I64_lteq(const til_I64 til_a, const til_I64 til_b) {
    if (til_lt(til_a, til_b).data) {
        return true;
    }
    if (til_gt(til_a, til_b).data) {
        return false;
    }
    return true;
}

int til_Vec_new(til_Vec* _ret, til_AllocError* _err1, const til_Type til_T) {
    til_Vec til_vec = {.type_name = ((til_Str){(til_I64)"", 0}), .type_size = 0, .ptr = 0, ._len = 0, .cap = 0};
    til_vec.type_name = ((til_Str){(til_I64)"T", 1});
    til_vec.type_size = til_size_of(((til_Str){(til_I64)til_T, strlen(til_T)}));
    const til_I64 til_size_bytes = til_mul(til_Vec_INIT_CAP, til_vec.type_size);
    til_I64 _ret__tmp220;
    til_AllocError _err0__tmp220 = {};
    int _status__tmp220 = til_malloc(&_ret__tmp220, &_err0__tmp220, til_size_bytes);
    if (_status__tmp220 == 1) { *_err1 = _err0__tmp220; return 1; }
    til_vec.ptr = _ret__tmp220;
    til_vec._len = 0;
    til_vec.cap = til_Vec_INIT_CAP;
    *_ret = til_vec;
    return 0;
}

int til_Vec_push(til_AllocError* _err1, til_Vec* til_self, const til_Dynamic til_value) {
    til_I64 til_new_cap;
    til_I64 til_new_ptr;
    if (til_I64_eq(til_self->_len, til_self->cap).data) {
        til_new_cap = til_mul(til_self->cap, 2);
        if (til_gt(til_new_cap, til_Vec_MAX_CAP).data) {
            til_Array _tmp224;
            til_AllocError _err_alloc__tmp225;
            til_IndexOutOfBoundsError _err_idx__tmp225;
            til_Str _tmp226 = ((til_Str){(til_I64)"Vec.push: capacity exceeded Vec.MAX_CAP", 39});
            int _arr_status__tmp225 = til_Array_new(&_tmp224, &_err_alloc__tmp225, "Str", 1);
            if (_arr_status__tmp225 != 0) {
                *_err1 = _err_alloc__tmp225; return 1;
            }
            _arr_status__tmp225 = til_Array_set(&_err_idx__tmp225, &_tmp224, 0, &_tmp226);
            if (_arr_status__tmp225 != 0) {
            }
            til_panic(((til_Str){(til_I64)"src/core/vec.til:63:23:", 23}), &_tmp224);
            til_Array_delete(&_tmp224);
        }
        til_I64 _ret__tmp227;
        til_I64 til_new_ptr;
        til_AllocError _err0__tmp227 = {};
        int _status__tmp227 = til_malloc(&_ret__tmp227, &_err0__tmp227, til_mul(til_new_cap, til_self->type_size));
        if (_status__tmp227 == 1) { *_err1 = _err0__tmp227; return 1; }
        til_new_ptr = _ret__tmp227;
        til_memcpy(til_new_ptr, til_self->ptr, til_mul(til_self->_len, til_self->type_size));
        til_free(til_self->ptr);
        til_self->ptr = til_new_ptr;
        til_self->cap = til_new_cap;
    }
    til_I64 til_dest = til_add(til_self->ptr, til_mul(til_self->_len, til_self->type_size));
    til_memcpy(til_dest, (til_I64)til_value, til_self->type_size);
    til_self->_len = til_add(til_self->_len, 1);
    return 0;
}

int til_Vec_get(til_IndexOutOfBoundsError* _err1, const til_Vec til_self, const til_I64 til_index, til_Dynamic* til_T) {
    if (til_I64_gteq(til_index, til_self._len).data) {
        til_Str _tmp230;
        til_I64_OverflowError _err0__tmp231;
        til_IndexOutOfBoundsError _err1__tmp231;
        til_AllocError _err2__tmp231;
        til_Array _tmp232;
        til_AllocError _err_alloc__tmp233;
        til_IndexOutOfBoundsError _err_idx__tmp233;
        til_Str _tmp234 = ((til_Str){(til_I64)"Vec.get: index out of bounds", 28});
        int _arr_status__tmp233 = til_Array_new(&_tmp232, &_err_alloc__tmp233, "Str", 1);
        if (_arr_status__tmp233 != 0) {
        }
        _arr_status__tmp233 = til_Array_set(&_err_idx__tmp233, &_tmp232, 0, &_tmp234);
        if (_arr_status__tmp233 != 0) {
            *_err1 = _err_idx__tmp233; return 1;
        }
        int _status__tmp231 = til_format(&_tmp230, &_err0__tmp231, &_err1__tmp231, &_err2__tmp231, ((til_Str){(til_I64)"src/core/vec.til:81:52:", 23}), &_tmp232);
        if (_status__tmp231 != 0) {
            if (_status__tmp231 == 2) { *_err1 = _err1__tmp231; return 1; }
        }
        til_Array_delete(&_tmp232);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp230};
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

til_I64 til_Str_len(const til_Str til_self) {
    return til_self.cap;
}

til_Bool til_Str_eq(const til_Str til_self, const til_Str til_other) {
    if (til_not(til_I64_eq(til_self.cap, til_other.cap)).data) {
        return false;
    }
    til_I64 til_i = 0;
    til_U8 til_self_byte;
    til_U8 til_other_byte;
    while (til_lt(til_i, til_self.cap).data) {
        til_self_byte = 0;
        til_other_byte = 0;
        til_memcpy((til_I64)&til_self_byte, til_add(til_self.c_string, til_i), 1);
        til_memcpy((til_I64)&til_other_byte, til_add(til_other.c_string, til_i), 1);
        if (til_not(til_U8_eq(til_self_byte, til_other_byte)).data) {
            return false;
        }
        til_I64_inc(&til_i);
    }
    return true;
}

int til_Str_clone(til_Str* _ret, til_AllocError* _err1, const til_Str til_self) {
    til_Str til_cloned = {.c_string = 0, .cap = 0};
    til_cloned.cap = til_self.cap;
    til_I64 _ret__tmp242;
    til_AllocError _err0__tmp242 = {};
    int _status__tmp242 = til_malloc(&_ret__tmp242, &_err0__tmp242, til_cloned.cap);
    if (_status__tmp242 == 1) { *_err1 = _err0__tmp242; return 1; }
    til_cloned.c_string = _ret__tmp242;
    if (til_I64_eq(til_NULL, til_cloned.c_string).data) {
        til_Str _tmp244;
        til_I64_OverflowError _err0__tmp245;
        til_IndexOutOfBoundsError _err1__tmp245;
        til_AllocError _err2__tmp245;
        til_Array _tmp246;
        til_AllocError _err_alloc__tmp247;
        til_IndexOutOfBoundsError _err_idx__tmp247;
        til_Str _tmp248 = ((til_Str){(til_I64)"Str.clone: malloc failed for ", 29});
        til_Str _tmp249 = til_I64_to_str(til_cloned.cap);
        til_Str _tmp250 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp247 = til_Array_new(&_tmp246, &_err_alloc__tmp247, "Str", 3);
        if (_arr_status__tmp247 != 0) {
            *_err1 = _err_alloc__tmp247; return 1;
        }
        _arr_status__tmp247 = til_Array_set(&_err_idx__tmp247, &_tmp246, 0, &_tmp248);
        if (_arr_status__tmp247 != 0) {
        }
        _arr_status__tmp247 = til_Array_set(&_err_idx__tmp247, &_tmp246, 1, &_tmp249);
        if (_arr_status__tmp247 != 0) {
        }
        _arr_status__tmp247 = til_Array_set(&_err_idx__tmp247, &_tmp246, 2, &_tmp250);
        if (_arr_status__tmp247 != 0) {
        }
        int _status__tmp245 = til_format(&_tmp244, &_err0__tmp245, &_err1__tmp245, &_err2__tmp245, ((til_Str){(til_I64)"src/core/str.til:46:41:", 23}), &_tmp246);
        if (_status__tmp245 != 0) {
            if (_status__tmp245 == 3) { *_err1 = _err2__tmp245; return 1; }
        }
        til_Array_delete(&_tmp246);
        *_err1 = (til_AllocError){.msg = _tmp244};
        return 1;
    }
    til_memcpy(til_cloned.c_string, til_self.c_string, til_self.cap);
    *_ret = til_cloned;
    return 0;
}

til_Bool til_Str_contains(const til_Str til_self, const til_Str til_needle) {
    if (til_gt(til_Str_len(til_needle), til_Str_len(til_self)).data) {
        return false;
    }
    if (til_I64_eq(til_Str_len(til_needle), 0).data) {
        return false;
    }
    til_I64 til_max_start = til_sub(til_Str_len(til_self), til_Str_len(til_needle));
    til_I64 til_start_idx = 0;
    til_Bool til_matches;
    til_I64 til_needle_idx;
    til_U8 til_self_byte;
    til_U8 til_needle_byte;
    while (til_lt(til_start_idx, til_add(til_max_start, 1)).data) {
        til_matches = true;
        til_needle_idx = 0;
        while (til_lt(til_needle_idx, til_Str_len(til_needle)).data) {
            til_self_byte = 0;
            til_needle_byte = 0;
            til_memcpy((til_I64)&til_self_byte, til_add(til_self.c_string, til_add(til_start_idx, til_needle_idx)), 1);
            til_memcpy((til_I64)&til_needle_byte, til_add(til_needle.c_string, til_needle_idx), 1);
            if (til_not(til_U8_eq(til_self_byte, til_needle_byte)).data) {
                til_matches = false;
            }
            til_I64_inc(&til_needle_idx);
        }
        if (til_matches.data) {
            return true;
        }
        til_I64_inc(&til_start_idx);
    }
    return false;
}

til_I64 til_Str_find(const til_Str til_self, const til_Str til_needle) {
    if (til_gt(til_Str_len(til_needle), til_Str_len(til_self)).data) {
        return -1;
    }
    if (til_I64_eq(til_Str_len(til_needle), 0).data) {
        return -1;
    }
    til_I64 til_max_start = til_sub(til_Str_len(til_self), til_Str_len(til_needle));
    til_I64 til_start_idx = 0;
    til_Bool til_matches;
    til_I64 til_needle_idx;
    til_U8 til_self_byte;
    til_U8 til_needle_byte;
    while (til_I64_lteq(til_start_idx, til_max_start).data) {
        til_matches = true;
        til_needle_idx = 0;
        while (til_lt(til_needle_idx, til_Str_len(til_needle)).data) {
            if (til_not(til_matches).data) {
                til_needle_idx = til_Str_len(til_needle);
            } else {
                til_self_byte = 0;
                til_needle_byte = 0;
                til_memcpy((til_I64)&til_self_byte, til_add(til_self.c_string, til_add(til_start_idx, til_needle_idx)), 1);
                til_memcpy((til_I64)&til_needle_byte, til_add(til_needle.c_string, til_needle_idx), 1);
                if (til_not(til_U8_eq(til_self_byte, til_needle_byte)).data) {
                    til_matches = false;
                }
                til_I64_inc(&til_needle_idx);
            }
        }
        if (til_matches.data) {
            return til_start_idx;
        }
        til_I64_inc(&til_start_idx);
    }
    return -1;
}

int til_Str_replacen(til_Str* _ret, til_AllocError* _err1, const til_Str til_self, const til_Str til_from, const til_Str til_to, const til_I64 til_n) {
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp269;
    if (til_I64_eq(til_Str_len(til_from), 0).data) {
        til_Str _ret__tmp271;
        til_AllocError _err0__tmp271 = {};
        int _status__tmp271 = til_Str_clone(&_ret__tmp271, &_err0__tmp271, til_self);
        if (_status__tmp271 == 1) { *_err1 = _err0__tmp271; return 1; }
        *_ret = _ret__tmp271;
        return 0;
    }
    if (til_I64_eq(til_n, 0).data) {
        til_Str _ret__tmp273;
        til_AllocError _err0__tmp273 = {};
        int _status__tmp273 = til_Str_clone(&_ret__tmp273, &_err0__tmp273, til_self);
        if (_status__tmp273 == 1) { *_err1 = _err0__tmp273; return 1; }
        *_ret = _ret__tmp273;
        return 0;
    }
    til_I64 til_idx = til_Str_find(til_self, til_from);
    if (til_lt(til_idx, 0).data) {
        til_Str _ret__tmp275;
        til_AllocError _err0__tmp275 = {};
        int _status__tmp275 = til_Str_clone(&_ret__tmp275, &_err0__tmp275, til_self);
        if (_status__tmp275 == 1) { *_err1 = _err0__tmp275; return 1; }
        *_ret = _ret__tmp275;
        return 0;
    }
    til_Str _ret__tmp276;
    til_Str til_prefix;
    til_IndexOutOfBoundsError _err0__tmp276 = {};
    til_AllocError _err1__tmp276 = {};
    int _status__tmp276 = til_get_substr(&_ret__tmp276, &_err0__tmp276, &_err1__tmp276, til_self, 0, til_idx);
    if (_status__tmp276 == 2) { *_err1 = _err1__tmp276; return 1; }
    til_prefix = _ret__tmp276;
    til_Str _ret__tmp277;
    til_Str til_suffix;
    til_IndexOutOfBoundsError _err0__tmp277 = {};
    til_AllocError _err1__tmp277 = {};
    int _status__tmp277 = til_get_substr(&_ret__tmp277, &_err0__tmp277, &_err1__tmp277, til_self, til_add(til_idx, til_Str_len(til_from)), til_Str_len(til_self));
    if (_status__tmp277 == 2) { *_err1 = _err1__tmp277; return 1; }
    til_suffix = _ret__tmp277;
    til_Str til_result = til_concat(til_concat(til_prefix, til_to), til_suffix);
    til_Str til_rest;
    if (til_gt(til_n, 1).data) {
        til_Str _ret__tmp279;
        til_Str til_rest;
        til_AllocError _err0__tmp279 = {};
        int _status__tmp279 = til_Str_replacen(&_ret__tmp279, &_err0__tmp279, til_suffix, til_from, til_to, til_sub(til_n, 1));
        if (_status__tmp279 == 1) { *_err1 = _err0__tmp279; return 1; }
        til_rest = _ret__tmp279;
        til_result = til_concat(til_concat(til_prefix, til_to), til_rest);
    }
    goto _end_catches__tmp269;
_catch_IndexOutOfBoundsError__tmp269: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp269;
    til_Str _ret__tmp281;
    til_AllocError _err0__tmp281 = {};
    int _status__tmp281 = til_Str_clone(&_ret__tmp281, &_err0__tmp281, til_self);
    if (_status__tmp281 == 1) { *_err1 = _err0__tmp281; return 1; }
    til_result = _ret__tmp281;
    goto _end_catches__tmp269;
    }
_end_catches__tmp269:;
    *_ret = til_result;
    return 0;
}

til_Bool til_U8_eq(const til_U8 til_self, const til_U8 til_other) {
    return til_I64_eq(til_U8_to_i64(til_self), til_U8_to_i64(til_other));
}

til_I64 til_U8_to_i64(const til_U8 til_self) {
    return til_u8_to_i64(til_self);
}

int til_U8_from_i64(til_U8* _ret, til_U8_OverflowError* _err1, const til_I64 til_self) {
    if (til_lt(til_self, 0).data) {
        til_Str _tmp287;
        til_I64_OverflowError _err0__tmp288;
        til_IndexOutOfBoundsError _err1__tmp288;
        til_AllocError _err2__tmp288;
        til_Array _tmp289;
        til_AllocError _err_alloc__tmp290;
        til_IndexOutOfBoundsError _err_idx__tmp290;
        til_Str _tmp291 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        int _arr_status__tmp290 = til_Array_new(&_tmp289, &_err_alloc__tmp290, "Str", 1);
        if (_arr_status__tmp290 != 0) {
        }
        _arr_status__tmp290 = til_Array_set(&_err_idx__tmp290, &_tmp289, 0, &_tmp291);
        if (_arr_status__tmp290 != 0) {
        }
        int _status__tmp288 = til_format(&_tmp287, &_err0__tmp288, &_err1__tmp288, &_err2__tmp288, ((til_Str){(til_I64)"src/core/u8.til:50:47:", 22}), &_tmp289);
        if (_status__tmp288 != 0) {
        }
        til_Array_delete(&_tmp289);
        *_err1 = (til_U8_OverflowError){.msg = _tmp287};
        return 1;
    }
    if (til_gt(til_self, til_MAX_U8).data) {
        til_Str _tmp293;
        til_I64_OverflowError _err0__tmp294;
        til_IndexOutOfBoundsError _err1__tmp294;
        til_AllocError _err2__tmp294;
        til_Array _tmp295;
        til_AllocError _err_alloc__tmp296;
        til_IndexOutOfBoundsError _err_idx__tmp296;
        til_Str _tmp297 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp298 = ((til_Str){(til_I64)"255", 3});
        int _arr_status__tmp296 = til_Array_new(&_tmp295, &_err_alloc__tmp296, "Str", 2);
        if (_arr_status__tmp296 != 0) {
        }
        _arr_status__tmp296 = til_Array_set(&_err_idx__tmp296, &_tmp295, 0, &_tmp297);
        if (_arr_status__tmp296 != 0) {
        }
        _arr_status__tmp296 = til_Array_set(&_err_idx__tmp296, &_tmp295, 1, &_tmp298);
        if (_arr_status__tmp296 != 0) {
        }
        int _status__tmp294 = til_format(&_tmp293, &_err0__tmp294, &_err1__tmp294, &_err2__tmp294, ((til_Str){(til_I64)"src/core/u8.til:53:47:", 22}), &_tmp295);
        if (_status__tmp294 != 0) {
        }
        til_Array_delete(&_tmp295);
        *_err1 = (til_U8_OverflowError){.msg = _tmp293};
        return 1;
    }
    *_ret = til_i64_to_u8(til_self);
    return 0;
}

int main(int argc, char** argv) {
    til_test_simple_add();
    til_test_nested_arithmetic();
    til_test_deeply_nested();
    til_test_string_concat();
    til_test_fold_variable();
    til_test_loc_folded_correctly();
    til_test_struct_fold_simple();
    til_test_struct_fold_values();
    til_test_struct_fold_nested();
    return 0;
}
