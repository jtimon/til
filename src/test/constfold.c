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

til_Bool til_not(const til_Bool* til_b);
til_Bool til_or(til_Array* til_args);
til_Bool til_and(til_Array* til_args);
void til_panic(const til_Str* til_loc_str, const til_Str* til_msg, til_Array* til_extra_msgs);
void til_assertm(const til_Str* til_loc_str, const til_Bool* til_cond, const til_Str* til_msg);
void til_println(til_Array* til_args);
int til_get_substr(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str* til_s, const til_I64* til_start, const til_I64* til_end);
til_Str til_concat(const til_Str* til_a, const til_Str* til_b);
int til_format(til_Str* _ret, til_I64_OverflowError* _err1, til_IndexOutOfBoundsError* _err2, til_AllocError* _err3, const til_Str* til_prefix, til_Array* til_args);
void til_test(const til_Str* til_loc_str, const til_Bool* til_cond, const til_Str* til_msg);
void til_assert_eq(const til_Str* til_loc_str, const til_I64* til_a, const til_I64* til_b);
void til_test_simple_add(void);
void til_test_nested_arithmetic(void);
void til_test_deeply_nested(void);
void til_test_string_concat(void);
void til_test_fold_variable(void);
void til_test_loc_folded_correctly(void);
void til_test_struct_fold_simple(void);
void til_test_struct_fold_values(void);
void til_test_struct_fold_nested(void);
til_I64 til_Array_len(const til_Array* til_self);
int til_Array_new(til_Array* _ret, til_AllocError* _err1, til_Type til_T, const til_I64* til_capacity);
int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array* til_self, const til_I64* til_index, til_Dynamic* til_T);
int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64* til_index, const til_Dynamic* til_value);
void til_Array_delete(til_Array* til_self);
til_Bool til_Bool_and(const til_Bool* til_self, const til_Bool* til_other);
til_Bool til_I64_eq(const til_I64* til_a, const til_I64* til_b);
til_Str til_I64_to_str(const til_I64* til_self);
til_I64 til_I64_from_str(const til_Str* til_str);
void til_I64_inc(til_I64* til_self);
void til_I64_dec(til_I64* til_self);
til_Bool til_I64_gteq(const til_I64* til_a, const til_I64* til_b);
til_Bool til_I64_lteq(const til_I64* til_a, const til_I64* til_b);
til_Vec til_Vec_new(til_Type til_T);
int til_Vec_push(til_AllocError* _err1, til_Vec* til_self, const til_Dynamic* til_value);
int til_Vec_get(til_IndexOutOfBoundsError* _err1, const til_Vec* til_self, const til_I64* til_index, til_Dynamic* til_T);
til_I64 til_Str_len(const til_Str* til_self);
til_Bool til_Str_eq(const til_Str* til_self, const til_Str* til_other);
int til_Str_clone(til_Str* _ret, til_AllocError* _err1, const til_Str* til_self);
til_Bool til_Str_contains(const til_Str* til_self, const til_Str* til_needle);
til_I64 til_Str_find(const til_Str* til_self, const til_Str* til_needle);
int til_Str_replacen(til_Str* _ret, til_AllocError* _err1, const til_Str* til_self, const til_Str* til_from, const til_Str* til_to, const til_I64* til_n);
til_Bool til_U8_eq(const til_U8* til_self, const til_U8* til_other);
til_I64 til_U8_to_i64(const til_U8* til_self);
int til_U8_from_i64(til_U8* _ret, til_U8_OverflowError* _err1, const til_I64* til_self);
til_Bool til_Introspection_has_const(const til_Str* til_type_name, const til_Str* til_const_name);
til_Bool til_Introspection_has_field(const til_Str* til_type_name, const til_Str* til_field_name);
til_CfVec2 til_CfVec2_magic(void);
til_CfVec2 til_CfVec2_at(const til_I64* til_x, const til_I64* til_y);
til_CfRect til_CfRect_sample(void);

#include <ext.c>

const til_I64 til_size_of_IndexOutOfBoundsError = sizeof(til_IndexOutOfBoundsError);
const til_I64 til_size_of_AllocError = sizeof(til_AllocError);
const til_I64 til_size_of_Array = sizeof(til_Array);
const til_I64 til_size_of_Bool = sizeof(til_Bool);
const til_I64 til_size_of_I64_OverflowError = sizeof(til_I64_OverflowError);
const til_I64 til_size_of_I64 = sizeof(til_I64);
const til_I64 til_Vec_INIT_CAP = 0;
const til_I64 til_Vec_MAX_CAP = 1073741824;
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

static inline til_I64 til_size_of(const til_Str* type_name) {
    if (strcmp((char*)type_name->c_string, "IndexOutOfBoundsError") == 0) return til_size_of_IndexOutOfBoundsError;
    if (strcmp((char*)type_name->c_string, "AllocError") == 0) return til_size_of_AllocError;
    if (strcmp((char*)type_name->c_string, "Array") == 0) return til_size_of_Array;
    if (strcmp((char*)type_name->c_string, "Bool") == 0) return til_size_of_Bool;
    if (strcmp((char*)type_name->c_string, "I64_OverflowError") == 0) return til_size_of_I64_OverflowError;
    if (strcmp((char*)type_name->c_string, "I64") == 0) return til_size_of_I64;
    if (strcmp((char*)type_name->c_string, "Vec") == 0) return til_size_of_Vec;
    if (strcmp((char*)type_name->c_string, "Str") == 0) return til_size_of_Str;
    if (strcmp((char*)type_name->c_string, "U8_OverflowError") == 0) return til_size_of_U8_OverflowError;
    if (strcmp((char*)type_name->c_string, "U8") == 0) return til_size_of_U8;
    if (strcmp((char*)type_name->c_string, "Dynamic") == 0) return til_size_of_Dynamic;
    if (strcmp((char*)type_name->c_string, "Type") == 0) return til_size_of_Type;
    if (strcmp((char*)type_name->c_string, "Introspection") == 0) return til_size_of_Introspection;
    if (strcmp((char*)type_name->c_string, "CfVec2") == 0) return til_size_of_CfVec2;
    if (strcmp((char*)type_name->c_string, "CfRect") == 0) return til_size_of_CfRect;
    fprintf(stderr, "size_of: unknown type %s\n", (char*)type_name->c_string);
    exit(1);
}

til_Bool til_not(const til_Bool* til_b) {
    if ((*til_b).data) {
        return false;
    }
    return true;
}

til_Bool til_or(til_Array* til_args) {
    til_I64 _for_i_or_0 = 0;
    til_Bool til_val;
    while (til_lt(&_for_i_or_0, &(til_I64){til_Array_len(til_args)}).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp_or_0;
        til_val = (til_Bool){.data = 0};
        til_IndexOutOfBoundsError _err0__tmp_or_1 = {};
        int _status__tmp_or_1 = til_Array_get(&_err0__tmp_or_1, til_args, &_for_i_or_0, (til_Dynamic*)&til_val);
        if (_status__tmp_or_1 == 1) { _thrown_IndexOutOfBoundsError__tmp_or_0 = _err0__tmp_or_1; goto _catch_IndexOutOfBoundsError__tmp_or_0; }
        if (0) { _catch_IndexOutOfBoundsError__tmp_or_0:
            til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp_or_0;
            til_Array _tmp_or_2;
            til_AllocError _err_alloc__tmp_or_3;
            til_IndexOutOfBoundsError _err_idx__tmp_or_3;
            til_Type _tmp_or_4 = "Str";
            til_I64 _tmp_or_5 = 0;
            int _arr_status__tmp_or_3 = til_Array_new(&_tmp_or_2, &_err_alloc__tmp_or_3, _tmp_or_4, &_tmp_or_5);
            if (_arr_status__tmp_or_3 != 0) {
            }
            til_panic(&((til_Str){(til_I64)"src/core/bool.til:74:5:", 23}), &til_err.msg, &_tmp_or_2);
            til_Array_delete(&_tmp_or_2);
        }
        if (til_val.data) {
            return true;
        }
        _for_i_or_0 = til_add(&_for_i_or_0, &(til_I64){1});
    }
    return false;
}

til_Bool til_and(til_Array* til_args) {
    til_I64 _for_i_and_0 = 0;
    til_Bool til_val;
    while (til_lt(&_for_i_and_0, &(til_I64){til_Array_len(til_args)}).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp_and_0;
        til_val = (til_Bool){.data = 0};
        til_IndexOutOfBoundsError _err0__tmp_and_1 = {};
        int _status__tmp_and_1 = til_Array_get(&_err0__tmp_and_1, til_args, &_for_i_and_0, (til_Dynamic*)&til_val);
        if (_status__tmp_and_1 == 1) { _thrown_IndexOutOfBoundsError__tmp_and_0 = _err0__tmp_and_1; goto _catch_IndexOutOfBoundsError__tmp_and_0; }
        if (0) { _catch_IndexOutOfBoundsError__tmp_and_0:
            til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp_and_0;
            til_Array _tmp_and_2;
            til_AllocError _err_alloc__tmp_and_3;
            til_IndexOutOfBoundsError _err_idx__tmp_and_3;
            til_Type _tmp_and_4 = "Str";
            til_I64 _tmp_and_5 = 0;
            int _arr_status__tmp_and_3 = til_Array_new(&_tmp_and_2, &_err_alloc__tmp_and_3, _tmp_and_4, &_tmp_and_5);
            if (_arr_status__tmp_and_3 != 0) {
            }
            til_panic(&((til_Str){(til_I64)"src/core/bool.til:83:5:", 23}), &til_err.msg, &_tmp_and_2);
            til_Array_delete(&_tmp_and_2);
        }
        if (til_not(&til_val).data) {
            return false;
        }
        _for_i_and_0 = til_add(&_for_i_and_0, &(til_I64){1});
    }
    return true;
}

void til_panic(const til_Str* til_loc_str, const til_Str* til_msg, til_Array* til_extra_msgs) {
    til_single_print(til_loc_str);
    til_single_print(til_msg);
    til_I64 _for_i_panic_0 = 0;
    til_Str til_val;
    while (til_lt(&_for_i_panic_0, &(til_I64){til_Array_len(til_extra_msgs)}).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp_panic_0;
        til_val = (til_Str){.c_string = 0, .cap = 0};
        til_IndexOutOfBoundsError _err0__tmp_panic_1 = {};
        int _status__tmp_panic_1 = til_Array_get(&_err0__tmp_panic_1, til_extra_msgs, &_for_i_panic_0, (til_Dynamic*)&til_val);
        if (_status__tmp_panic_1 == 1) { _thrown_IndexOutOfBoundsError__tmp_panic_0 = _err0__tmp_panic_1; goto _catch_IndexOutOfBoundsError__tmp_panic_0; }
        if (0) { _catch_IndexOutOfBoundsError__tmp_panic_0:
            til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp_panic_0;
            til_Array _tmp_panic_2;
            til_AllocError _err_alloc__tmp_panic_3;
            til_IndexOutOfBoundsError _err_idx__tmp_panic_3;
            til_Type _tmp_panic_4 = "Str";
            til_I64 _tmp_panic_5 = 0;
            int _arr_status__tmp_panic_3 = til_Array_new(&_tmp_panic_2, &_err_alloc__tmp_panic_3, _tmp_panic_4, &_tmp_panic_5);
            if (_arr_status__tmp_panic_3 != 0) {
            }
            til_panic(&((til_Str){(til_I64)"src/core/exit.til:13:5:", 23}), &til_err.msg, &_tmp_panic_2);
            til_Array_delete(&_tmp_panic_2);
        }
        til_single_print(&til_val);
        _for_i_panic_0 = til_add(&_for_i_panic_0, &(til_I64){1});
    }
    til_single_print(&((til_Str){(til_I64)"\n", 1}));
    til_print_flush();
    til_I64 _tmp_panic_6 = 1;
    til_exit(&_tmp_panic_6);
}

void til_assertm(const til_Str* til_loc_str, const til_Bool* til_cond, const til_Str* til_msg) {
    if (til_not(til_cond).data) {
        til_Str _tmp_assertm_0;
        til_I64_OverflowError _err0__tmp_assertm_1;
        til_IndexOutOfBoundsError _err1__tmp_assertm_1;
        til_AllocError _err2__tmp_assertm_1;
        til_Array _tmp_assertm_2;
        til_AllocError _err_alloc__tmp_assertm_3;
        til_IndexOutOfBoundsError _err_idx__tmp_assertm_3;
        til_Str _tmp_assertm_4 = (*til_msg);
        til_Type _tmp_assertm_5 = "Str";
        til_I64 _tmp_assertm_6 = 1;
        int _arr_status__tmp_assertm_3 = til_Array_new(&_tmp_assertm_2, &_err_alloc__tmp_assertm_3, _tmp_assertm_5, &_tmp_assertm_6);
        if (_arr_status__tmp_assertm_3 != 0) {
        }
        til_I64 _tmp_assertm_7 = 0;
        _arr_status__tmp_assertm_3 = til_Array_set(&_err_idx__tmp_assertm_3, &_tmp_assertm_2, &_tmp_assertm_7, (til_Dynamic*)&_tmp_assertm_4);
        if (_arr_status__tmp_assertm_3 != 0) {
        }
        int _status__tmp_assertm_1 = til_format(&_tmp_assertm_0, &_err0__tmp_assertm_1, &_err1__tmp_assertm_1, &_err2__tmp_assertm_1, &((til_Str){(til_I64)"assert failed: ", 15}), &_tmp_assertm_2);
        if (_status__tmp_assertm_1 != 0) {
        }
        til_Array_delete(&_tmp_assertm_2);
        til_Array _tmp_assertm_8;
        til_AllocError _err_alloc__tmp_assertm_9;
        til_IndexOutOfBoundsError _err_idx__tmp_assertm_9;
        til_Type _tmp_assertm_10 = "Str";
        til_I64 _tmp_assertm_11 = 0;
        int _arr_status__tmp_assertm_9 = til_Array_new(&_tmp_assertm_8, &_err_alloc__tmp_assertm_9, _tmp_assertm_10, &_tmp_assertm_11);
        if (_arr_status__tmp_assertm_9 != 0) {
        }
        til_panic(til_loc_str, &_tmp_assertm_0, &_tmp_assertm_8);
        til_Array_delete(&_tmp_assertm_8);
    }
}

void til_println(til_Array* til_args) {
    til_I64 _for_i_println_0 = 0;
    til_Str til_val;
    while (til_lt(&_for_i_println_0, &(til_I64){til_Array_len(til_args)}).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp_println_0;
        til_val = (til_Str){.c_string = 0, .cap = 0};
        til_IndexOutOfBoundsError _err0__tmp_println_1 = {};
        int _status__tmp_println_1 = til_Array_get(&_err0__tmp_println_1, til_args, &_for_i_println_0, (til_Dynamic*)&til_val);
        if (_status__tmp_println_1 == 1) { _thrown_IndexOutOfBoundsError__tmp_println_0 = _err0__tmp_println_1; goto _catch_IndexOutOfBoundsError__tmp_println_0; }
        if (0) { _catch_IndexOutOfBoundsError__tmp_println_0:
            til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp_println_0;
            til_Array _tmp_println_2;
            til_AllocError _err_alloc__tmp_println_3;
            til_IndexOutOfBoundsError _err_idx__tmp_println_3;
            til_Type _tmp_println_4 = "Str";
            til_I64 _tmp_println_5 = 0;
            int _arr_status__tmp_println_3 = til_Array_new(&_tmp_println_2, &_err_alloc__tmp_println_3, _tmp_println_4, &_tmp_println_5);
            if (_arr_status__tmp_println_3 != 0) {
            }
            til_panic(&((til_Str){(til_I64)"src/core/print.til:16:5:", 24}), &til_err.msg, &_tmp_println_2);
            til_Array_delete(&_tmp_println_2);
        }
        til_single_print(&til_val);
        _for_i_println_0 = til_add(&_for_i_println_0, &(til_I64){1});
    }
    til_single_print(&((til_Str){(til_I64)"\n", 1}));
    til_print_flush();
}

int til_get_substr(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str* til_s, const til_I64* til_start, const til_I64* til_end) {
    if (til_lt(til_start, &(til_I64){0}).data) {
        til_Str _tmp_get_substr_0;
        til_I64_OverflowError _err0__tmp_get_substr_1;
        til_IndexOutOfBoundsError _err1__tmp_get_substr_1;
        til_AllocError _err2__tmp_get_substr_1;
        til_Array _tmp_get_substr_2;
        til_AllocError _err_alloc__tmp_get_substr_3;
        til_IndexOutOfBoundsError _err_idx__tmp_get_substr_3;
        til_Str _tmp_get_substr_4 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp_get_substr_5 = til_I64_to_str(til_start);
        til_Str _tmp_get_substr_6 = ((til_Str){(til_I64)" cannot be negative", 19});
        til_Type _tmp_get_substr_7 = "Str";
        til_I64 _tmp_get_substr_8 = 3;
        int _arr_status__tmp_get_substr_3 = til_Array_new(&_tmp_get_substr_2, &_err_alloc__tmp_get_substr_3, _tmp_get_substr_7, &_tmp_get_substr_8);
        if (_arr_status__tmp_get_substr_3 != 0) {
            *_err2 = _err_alloc__tmp_get_substr_3; return 2;
        }
        til_I64 _tmp_get_substr_9 = 0;
        _arr_status__tmp_get_substr_3 = til_Array_set(&_err_idx__tmp_get_substr_3, &_tmp_get_substr_2, &_tmp_get_substr_9, (til_Dynamic*)&_tmp_get_substr_4);
        if (_arr_status__tmp_get_substr_3 != 0) {
            *_err1 = _err_idx__tmp_get_substr_3; return 1;
        }
        til_I64 _tmp_get_substr_10 = 1;
        _arr_status__tmp_get_substr_3 = til_Array_set(&_err_idx__tmp_get_substr_3, &_tmp_get_substr_2, &_tmp_get_substr_10, (til_Dynamic*)&_tmp_get_substr_5);
        if (_arr_status__tmp_get_substr_3 != 0) {
            *_err1 = _err_idx__tmp_get_substr_3; return 1;
        }
        til_I64 _tmp_get_substr_11 = 2;
        _arr_status__tmp_get_substr_3 = til_Array_set(&_err_idx__tmp_get_substr_3, &_tmp_get_substr_2, &_tmp_get_substr_11, (til_Dynamic*)&_tmp_get_substr_6);
        if (_arr_status__tmp_get_substr_3 != 0) {
            *_err1 = _err_idx__tmp_get_substr_3; return 1;
        }
        int _status__tmp_get_substr_1 = til_format(&_tmp_get_substr_0, &_err0__tmp_get_substr_1, &_err1__tmp_get_substr_1, &_err2__tmp_get_substr_1, &((til_Str){(til_I64)"src/core/str.til:375:48:", 24}), &_tmp_get_substr_2);
        if (_status__tmp_get_substr_1 != 0) {
            if (_status__tmp_get_substr_1 == 2) { *_err1 = _err1__tmp_get_substr_1; return 1; }
            if (_status__tmp_get_substr_1 == 3) { *_err2 = _err2__tmp_get_substr_1; return 2; }
        }
        til_Array_delete(&_tmp_get_substr_2);
        til_Str _tmp_get_substr_12;
        til_I64_OverflowError _err0__tmp_get_substr_13;
        til_IndexOutOfBoundsError _err1__tmp_get_substr_13;
        til_AllocError _err2__tmp_get_substr_13;
        til_Array _tmp_get_substr_14;
        til_AllocError _err_alloc__tmp_get_substr_15;
        til_IndexOutOfBoundsError _err_idx__tmp_get_substr_15;
        til_Str _tmp_get_substr_16 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp_get_substr_17 = til_I64_to_str(til_start);
        til_Str _tmp_get_substr_18 = ((til_Str){(til_I64)" cannot be negative", 19});
        til_Type _tmp_get_substr_19 = "Str";
        til_I64 _tmp_get_substr_20 = 3;
        int _arr_status__tmp_get_substr_15 = til_Array_new(&_tmp_get_substr_14, &_err_alloc__tmp_get_substr_15, _tmp_get_substr_19, &_tmp_get_substr_20);
        if (_arr_status__tmp_get_substr_15 != 0) {
            *_err2 = _err_alloc__tmp_get_substr_15; return 2;
        }
        til_I64 _tmp_get_substr_21 = 0;
        _arr_status__tmp_get_substr_15 = til_Array_set(&_err_idx__tmp_get_substr_15, &_tmp_get_substr_14, &_tmp_get_substr_21, (til_Dynamic*)&_tmp_get_substr_16);
        if (_arr_status__tmp_get_substr_15 != 0) {
            *_err1 = _err_idx__tmp_get_substr_15; return 1;
        }
        til_I64 _tmp_get_substr_22 = 1;
        _arr_status__tmp_get_substr_15 = til_Array_set(&_err_idx__tmp_get_substr_15, &_tmp_get_substr_14, &_tmp_get_substr_22, (til_Dynamic*)&_tmp_get_substr_17);
        if (_arr_status__tmp_get_substr_15 != 0) {
            *_err1 = _err_idx__tmp_get_substr_15; return 1;
        }
        til_I64 _tmp_get_substr_23 = 2;
        _arr_status__tmp_get_substr_15 = til_Array_set(&_err_idx__tmp_get_substr_15, &_tmp_get_substr_14, &_tmp_get_substr_23, (til_Dynamic*)&_tmp_get_substr_18);
        if (_arr_status__tmp_get_substr_15 != 0) {
            *_err1 = _err_idx__tmp_get_substr_15; return 1;
        }
        int _status__tmp_get_substr_13 = til_format(&_tmp_get_substr_12, &_err0__tmp_get_substr_13, &_err1__tmp_get_substr_13, &_err2__tmp_get_substr_13, &((til_Str){(til_I64)"src/core/str.til:375:48:", 24}), &_tmp_get_substr_14);
        if (_status__tmp_get_substr_13 != 0) {
            if (_status__tmp_get_substr_13 == 2) { *_err1 = _err1__tmp_get_substr_13; return 1; }
            if (_status__tmp_get_substr_13 == 3) { *_err2 = _err2__tmp_get_substr_13; return 2; }
        }
        til_Array_delete(&_tmp_get_substr_14);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_get_substr_12};
        return 1;
    }
    if (til_lt(til_end, &(til_I64){0}).data) {
        til_Str _tmp_get_substr_24;
        til_I64_OverflowError _err0__tmp_get_substr_25;
        til_IndexOutOfBoundsError _err1__tmp_get_substr_25;
        til_AllocError _err2__tmp_get_substr_25;
        til_Array _tmp_get_substr_26;
        til_AllocError _err_alloc__tmp_get_substr_27;
        til_IndexOutOfBoundsError _err_idx__tmp_get_substr_27;
        til_Str _tmp_get_substr_28 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp_get_substr_29 = til_I64_to_str(til_end);
        til_Str _tmp_get_substr_30 = ((til_Str){(til_I64)" cannot be negative", 19});
        til_Type _tmp_get_substr_31 = "Str";
        til_I64 _tmp_get_substr_32 = 3;
        int _arr_status__tmp_get_substr_27 = til_Array_new(&_tmp_get_substr_26, &_err_alloc__tmp_get_substr_27, _tmp_get_substr_31, &_tmp_get_substr_32);
        if (_arr_status__tmp_get_substr_27 != 0) {
            *_err2 = _err_alloc__tmp_get_substr_27; return 2;
        }
        til_I64 _tmp_get_substr_33 = 0;
        _arr_status__tmp_get_substr_27 = til_Array_set(&_err_idx__tmp_get_substr_27, &_tmp_get_substr_26, &_tmp_get_substr_33, (til_Dynamic*)&_tmp_get_substr_28);
        if (_arr_status__tmp_get_substr_27 != 0) {
            *_err1 = _err_idx__tmp_get_substr_27; return 1;
        }
        til_I64 _tmp_get_substr_34 = 1;
        _arr_status__tmp_get_substr_27 = til_Array_set(&_err_idx__tmp_get_substr_27, &_tmp_get_substr_26, &_tmp_get_substr_34, (til_Dynamic*)&_tmp_get_substr_29);
        if (_arr_status__tmp_get_substr_27 != 0) {
            *_err1 = _err_idx__tmp_get_substr_27; return 1;
        }
        til_I64 _tmp_get_substr_35 = 2;
        _arr_status__tmp_get_substr_27 = til_Array_set(&_err_idx__tmp_get_substr_27, &_tmp_get_substr_26, &_tmp_get_substr_35, (til_Dynamic*)&_tmp_get_substr_30);
        if (_arr_status__tmp_get_substr_27 != 0) {
            *_err1 = _err_idx__tmp_get_substr_27; return 1;
        }
        int _status__tmp_get_substr_25 = til_format(&_tmp_get_substr_24, &_err0__tmp_get_substr_25, &_err1__tmp_get_substr_25, &_err2__tmp_get_substr_25, &((til_Str){(til_I64)"src/core/str.til:378:48:", 24}), &_tmp_get_substr_26);
        if (_status__tmp_get_substr_25 != 0) {
            if (_status__tmp_get_substr_25 == 2) { *_err1 = _err1__tmp_get_substr_25; return 1; }
            if (_status__tmp_get_substr_25 == 3) { *_err2 = _err2__tmp_get_substr_25; return 2; }
        }
        til_Array_delete(&_tmp_get_substr_26);
        til_Str _tmp_get_substr_36;
        til_I64_OverflowError _err0__tmp_get_substr_37;
        til_IndexOutOfBoundsError _err1__tmp_get_substr_37;
        til_AllocError _err2__tmp_get_substr_37;
        til_Array _tmp_get_substr_38;
        til_AllocError _err_alloc__tmp_get_substr_39;
        til_IndexOutOfBoundsError _err_idx__tmp_get_substr_39;
        til_Str _tmp_get_substr_40 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp_get_substr_41 = til_I64_to_str(til_end);
        til_Str _tmp_get_substr_42 = ((til_Str){(til_I64)" cannot be negative", 19});
        til_Type _tmp_get_substr_43 = "Str";
        til_I64 _tmp_get_substr_44 = 3;
        int _arr_status__tmp_get_substr_39 = til_Array_new(&_tmp_get_substr_38, &_err_alloc__tmp_get_substr_39, _tmp_get_substr_43, &_tmp_get_substr_44);
        if (_arr_status__tmp_get_substr_39 != 0) {
            *_err2 = _err_alloc__tmp_get_substr_39; return 2;
        }
        til_I64 _tmp_get_substr_45 = 0;
        _arr_status__tmp_get_substr_39 = til_Array_set(&_err_idx__tmp_get_substr_39, &_tmp_get_substr_38, &_tmp_get_substr_45, (til_Dynamic*)&_tmp_get_substr_40);
        if (_arr_status__tmp_get_substr_39 != 0) {
            *_err1 = _err_idx__tmp_get_substr_39; return 1;
        }
        til_I64 _tmp_get_substr_46 = 1;
        _arr_status__tmp_get_substr_39 = til_Array_set(&_err_idx__tmp_get_substr_39, &_tmp_get_substr_38, &_tmp_get_substr_46, (til_Dynamic*)&_tmp_get_substr_41);
        if (_arr_status__tmp_get_substr_39 != 0) {
            *_err1 = _err_idx__tmp_get_substr_39; return 1;
        }
        til_I64 _tmp_get_substr_47 = 2;
        _arr_status__tmp_get_substr_39 = til_Array_set(&_err_idx__tmp_get_substr_39, &_tmp_get_substr_38, &_tmp_get_substr_47, (til_Dynamic*)&_tmp_get_substr_42);
        if (_arr_status__tmp_get_substr_39 != 0) {
            *_err1 = _err_idx__tmp_get_substr_39; return 1;
        }
        int _status__tmp_get_substr_37 = til_format(&_tmp_get_substr_36, &_err0__tmp_get_substr_37, &_err1__tmp_get_substr_37, &_err2__tmp_get_substr_37, &((til_Str){(til_I64)"src/core/str.til:378:48:", 24}), &_tmp_get_substr_38);
        if (_status__tmp_get_substr_37 != 0) {
            if (_status__tmp_get_substr_37 == 2) { *_err1 = _err1__tmp_get_substr_37; return 1; }
            if (_status__tmp_get_substr_37 == 3) { *_err2 = _err2__tmp_get_substr_37; return 2; }
        }
        til_Array_delete(&_tmp_get_substr_38);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_get_substr_36};
        return 1;
    }
    if (til_gt(til_start, til_end).data) {
        til_Str _tmp_get_substr_48;
        til_I64_OverflowError _err0__tmp_get_substr_49;
        til_IndexOutOfBoundsError _err1__tmp_get_substr_49;
        til_AllocError _err2__tmp_get_substr_49;
        til_Array _tmp_get_substr_50;
        til_AllocError _err_alloc__tmp_get_substr_51;
        til_IndexOutOfBoundsError _err_idx__tmp_get_substr_51;
        til_Str _tmp_get_substr_52 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp_get_substr_53 = til_I64_to_str(til_start);
        til_Str _tmp_get_substr_54 = ((til_Str){(til_I64)" is greater than end index ", 27});
        til_Str _tmp_get_substr_55 = til_I64_to_str(til_end);
        til_Type _tmp_get_substr_56 = "Str";
        til_I64 _tmp_get_substr_57 = 4;
        int _arr_status__tmp_get_substr_51 = til_Array_new(&_tmp_get_substr_50, &_err_alloc__tmp_get_substr_51, _tmp_get_substr_56, &_tmp_get_substr_57);
        if (_arr_status__tmp_get_substr_51 != 0) {
            *_err2 = _err_alloc__tmp_get_substr_51; return 2;
        }
        til_I64 _tmp_get_substr_58 = 0;
        _arr_status__tmp_get_substr_51 = til_Array_set(&_err_idx__tmp_get_substr_51, &_tmp_get_substr_50, &_tmp_get_substr_58, (til_Dynamic*)&_tmp_get_substr_52);
        if (_arr_status__tmp_get_substr_51 != 0) {
            *_err1 = _err_idx__tmp_get_substr_51; return 1;
        }
        til_I64 _tmp_get_substr_59 = 1;
        _arr_status__tmp_get_substr_51 = til_Array_set(&_err_idx__tmp_get_substr_51, &_tmp_get_substr_50, &_tmp_get_substr_59, (til_Dynamic*)&_tmp_get_substr_53);
        if (_arr_status__tmp_get_substr_51 != 0) {
            *_err1 = _err_idx__tmp_get_substr_51; return 1;
        }
        til_I64 _tmp_get_substr_60 = 2;
        _arr_status__tmp_get_substr_51 = til_Array_set(&_err_idx__tmp_get_substr_51, &_tmp_get_substr_50, &_tmp_get_substr_60, (til_Dynamic*)&_tmp_get_substr_54);
        if (_arr_status__tmp_get_substr_51 != 0) {
            *_err1 = _err_idx__tmp_get_substr_51; return 1;
        }
        til_I64 _tmp_get_substr_61 = 3;
        _arr_status__tmp_get_substr_51 = til_Array_set(&_err_idx__tmp_get_substr_51, &_tmp_get_substr_50, &_tmp_get_substr_61, (til_Dynamic*)&_tmp_get_substr_55);
        if (_arr_status__tmp_get_substr_51 != 0) {
            *_err1 = _err_idx__tmp_get_substr_51; return 1;
        }
        int _status__tmp_get_substr_49 = til_format(&_tmp_get_substr_48, &_err0__tmp_get_substr_49, &_err1__tmp_get_substr_49, &_err2__tmp_get_substr_49, &((til_Str){(til_I64)"src/core/str.til:381:48:", 24}), &_tmp_get_substr_50);
        if (_status__tmp_get_substr_49 != 0) {
            if (_status__tmp_get_substr_49 == 2) { *_err1 = _err1__tmp_get_substr_49; return 1; }
            if (_status__tmp_get_substr_49 == 3) { *_err2 = _err2__tmp_get_substr_49; return 2; }
        }
        til_Array_delete(&_tmp_get_substr_50);
        til_Str _tmp_get_substr_62;
        til_I64_OverflowError _err0__tmp_get_substr_63;
        til_IndexOutOfBoundsError _err1__tmp_get_substr_63;
        til_AllocError _err2__tmp_get_substr_63;
        til_Array _tmp_get_substr_64;
        til_AllocError _err_alloc__tmp_get_substr_65;
        til_IndexOutOfBoundsError _err_idx__tmp_get_substr_65;
        til_Str _tmp_get_substr_66 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp_get_substr_67 = til_I64_to_str(til_start);
        til_Str _tmp_get_substr_68 = ((til_Str){(til_I64)" is greater than end index ", 27});
        til_Str _tmp_get_substr_69 = til_I64_to_str(til_end);
        til_Type _tmp_get_substr_70 = "Str";
        til_I64 _tmp_get_substr_71 = 4;
        int _arr_status__tmp_get_substr_65 = til_Array_new(&_tmp_get_substr_64, &_err_alloc__tmp_get_substr_65, _tmp_get_substr_70, &_tmp_get_substr_71);
        if (_arr_status__tmp_get_substr_65 != 0) {
            *_err2 = _err_alloc__tmp_get_substr_65; return 2;
        }
        til_I64 _tmp_get_substr_72 = 0;
        _arr_status__tmp_get_substr_65 = til_Array_set(&_err_idx__tmp_get_substr_65, &_tmp_get_substr_64, &_tmp_get_substr_72, (til_Dynamic*)&_tmp_get_substr_66);
        if (_arr_status__tmp_get_substr_65 != 0) {
            *_err1 = _err_idx__tmp_get_substr_65; return 1;
        }
        til_I64 _tmp_get_substr_73 = 1;
        _arr_status__tmp_get_substr_65 = til_Array_set(&_err_idx__tmp_get_substr_65, &_tmp_get_substr_64, &_tmp_get_substr_73, (til_Dynamic*)&_tmp_get_substr_67);
        if (_arr_status__tmp_get_substr_65 != 0) {
            *_err1 = _err_idx__tmp_get_substr_65; return 1;
        }
        til_I64 _tmp_get_substr_74 = 2;
        _arr_status__tmp_get_substr_65 = til_Array_set(&_err_idx__tmp_get_substr_65, &_tmp_get_substr_64, &_tmp_get_substr_74, (til_Dynamic*)&_tmp_get_substr_68);
        if (_arr_status__tmp_get_substr_65 != 0) {
            *_err1 = _err_idx__tmp_get_substr_65; return 1;
        }
        til_I64 _tmp_get_substr_75 = 3;
        _arr_status__tmp_get_substr_65 = til_Array_set(&_err_idx__tmp_get_substr_65, &_tmp_get_substr_64, &_tmp_get_substr_75, (til_Dynamic*)&_tmp_get_substr_69);
        if (_arr_status__tmp_get_substr_65 != 0) {
            *_err1 = _err_idx__tmp_get_substr_65; return 1;
        }
        int _status__tmp_get_substr_63 = til_format(&_tmp_get_substr_62, &_err0__tmp_get_substr_63, &_err1__tmp_get_substr_63, &_err2__tmp_get_substr_63, &((til_Str){(til_I64)"src/core/str.til:381:48:", 24}), &_tmp_get_substr_64);
        if (_status__tmp_get_substr_63 != 0) {
            if (_status__tmp_get_substr_63 == 2) { *_err1 = _err1__tmp_get_substr_63; return 1; }
            if (_status__tmp_get_substr_63 == 3) { *_err2 = _err2__tmp_get_substr_63; return 2; }
        }
        til_Array_delete(&_tmp_get_substr_64);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_get_substr_62};
        return 1;
    }
    if (til_gt(til_end, &(til_I64){til_Str_len(til_s)}).data) {
        til_Str _tmp_get_substr_76;
        til_I64_OverflowError _err0__tmp_get_substr_77;
        til_IndexOutOfBoundsError _err1__tmp_get_substr_77;
        til_AllocError _err2__tmp_get_substr_77;
        til_Array _tmp_get_substr_78;
        til_AllocError _err_alloc__tmp_get_substr_79;
        til_IndexOutOfBoundsError _err_idx__tmp_get_substr_79;
        til_Str _tmp_get_substr_80 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp_get_substr_81 = til_I64_to_str(til_end);
        til_Str _tmp_get_substr_82 = ((til_Str){(til_I64)" is greater than string length ", 31});
        til_Str _tmp_get_substr_83 = til_I64_to_str(&(til_I64){til_Str_len(til_s)});
        til_Type _tmp_get_substr_84 = "Str";
        til_I64 _tmp_get_substr_85 = 4;
        int _arr_status__tmp_get_substr_79 = til_Array_new(&_tmp_get_substr_78, &_err_alloc__tmp_get_substr_79, _tmp_get_substr_84, &_tmp_get_substr_85);
        if (_arr_status__tmp_get_substr_79 != 0) {
            *_err2 = _err_alloc__tmp_get_substr_79; return 2;
        }
        til_I64 _tmp_get_substr_86 = 0;
        _arr_status__tmp_get_substr_79 = til_Array_set(&_err_idx__tmp_get_substr_79, &_tmp_get_substr_78, &_tmp_get_substr_86, (til_Dynamic*)&_tmp_get_substr_80);
        if (_arr_status__tmp_get_substr_79 != 0) {
            *_err1 = _err_idx__tmp_get_substr_79; return 1;
        }
        til_I64 _tmp_get_substr_87 = 1;
        _arr_status__tmp_get_substr_79 = til_Array_set(&_err_idx__tmp_get_substr_79, &_tmp_get_substr_78, &_tmp_get_substr_87, (til_Dynamic*)&_tmp_get_substr_81);
        if (_arr_status__tmp_get_substr_79 != 0) {
            *_err1 = _err_idx__tmp_get_substr_79; return 1;
        }
        til_I64 _tmp_get_substr_88 = 2;
        _arr_status__tmp_get_substr_79 = til_Array_set(&_err_idx__tmp_get_substr_79, &_tmp_get_substr_78, &_tmp_get_substr_88, (til_Dynamic*)&_tmp_get_substr_82);
        if (_arr_status__tmp_get_substr_79 != 0) {
            *_err1 = _err_idx__tmp_get_substr_79; return 1;
        }
        til_I64 _tmp_get_substr_89 = 3;
        _arr_status__tmp_get_substr_79 = til_Array_set(&_err_idx__tmp_get_substr_79, &_tmp_get_substr_78, &_tmp_get_substr_89, (til_Dynamic*)&_tmp_get_substr_83);
        if (_arr_status__tmp_get_substr_79 != 0) {
            *_err1 = _err_idx__tmp_get_substr_79; return 1;
        }
        int _status__tmp_get_substr_77 = til_format(&_tmp_get_substr_76, &_err0__tmp_get_substr_77, &_err1__tmp_get_substr_77, &_err2__tmp_get_substr_77, &((til_Str){(til_I64)"src/core/str.til:384:48:", 24}), &_tmp_get_substr_78);
        if (_status__tmp_get_substr_77 != 0) {
            if (_status__tmp_get_substr_77 == 2) { *_err1 = _err1__tmp_get_substr_77; return 1; }
            if (_status__tmp_get_substr_77 == 3) { *_err2 = _err2__tmp_get_substr_77; return 2; }
        }
        til_Array_delete(&_tmp_get_substr_78);
        til_Str _tmp_get_substr_90;
        til_I64_OverflowError _err0__tmp_get_substr_91;
        til_IndexOutOfBoundsError _err1__tmp_get_substr_91;
        til_AllocError _err2__tmp_get_substr_91;
        til_Array _tmp_get_substr_92;
        til_AllocError _err_alloc__tmp_get_substr_93;
        til_IndexOutOfBoundsError _err_idx__tmp_get_substr_93;
        til_Str _tmp_get_substr_94 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp_get_substr_95 = til_I64_to_str(til_end);
        til_Str _tmp_get_substr_96 = ((til_Str){(til_I64)" is greater than string length ", 31});
        til_Str _tmp_get_substr_97 = til_I64_to_str(&(til_I64){til_Str_len(til_s)});
        til_Type _tmp_get_substr_98 = "Str";
        til_I64 _tmp_get_substr_99 = 4;
        int _arr_status__tmp_get_substr_93 = til_Array_new(&_tmp_get_substr_92, &_err_alloc__tmp_get_substr_93, _tmp_get_substr_98, &_tmp_get_substr_99);
        if (_arr_status__tmp_get_substr_93 != 0) {
            *_err2 = _err_alloc__tmp_get_substr_93; return 2;
        }
        til_I64 _tmp_get_substr_100 = 0;
        _arr_status__tmp_get_substr_93 = til_Array_set(&_err_idx__tmp_get_substr_93, &_tmp_get_substr_92, &_tmp_get_substr_100, (til_Dynamic*)&_tmp_get_substr_94);
        if (_arr_status__tmp_get_substr_93 != 0) {
            *_err1 = _err_idx__tmp_get_substr_93; return 1;
        }
        til_I64 _tmp_get_substr_101 = 1;
        _arr_status__tmp_get_substr_93 = til_Array_set(&_err_idx__tmp_get_substr_93, &_tmp_get_substr_92, &_tmp_get_substr_101, (til_Dynamic*)&_tmp_get_substr_95);
        if (_arr_status__tmp_get_substr_93 != 0) {
            *_err1 = _err_idx__tmp_get_substr_93; return 1;
        }
        til_I64 _tmp_get_substr_102 = 2;
        _arr_status__tmp_get_substr_93 = til_Array_set(&_err_idx__tmp_get_substr_93, &_tmp_get_substr_92, &_tmp_get_substr_102, (til_Dynamic*)&_tmp_get_substr_96);
        if (_arr_status__tmp_get_substr_93 != 0) {
            *_err1 = _err_idx__tmp_get_substr_93; return 1;
        }
        til_I64 _tmp_get_substr_103 = 3;
        _arr_status__tmp_get_substr_93 = til_Array_set(&_err_idx__tmp_get_substr_93, &_tmp_get_substr_92, &_tmp_get_substr_103, (til_Dynamic*)&_tmp_get_substr_97);
        if (_arr_status__tmp_get_substr_93 != 0) {
            *_err1 = _err_idx__tmp_get_substr_93; return 1;
        }
        int _status__tmp_get_substr_91 = til_format(&_tmp_get_substr_90, &_err0__tmp_get_substr_91, &_err1__tmp_get_substr_91, &_err2__tmp_get_substr_91, &((til_Str){(til_I64)"src/core/str.til:384:48:", 24}), &_tmp_get_substr_92);
        if (_status__tmp_get_substr_91 != 0) {
            if (_status__tmp_get_substr_91 == 2) { *_err1 = _err1__tmp_get_substr_91; return 1; }
            if (_status__tmp_get_substr_91 == 3) { *_err2 = _err2__tmp_get_substr_91; return 2; }
        }
        til_Array_delete(&_tmp_get_substr_92);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_get_substr_90};
        return 1;
    }
    if (til_I64_eq(til_start, til_end).data) {
        til_Str _tmp_get_substr_104;
        til_I64_OverflowError _err0__tmp_get_substr_105;
        til_IndexOutOfBoundsError _err1__tmp_get_substr_105;
        til_AllocError _err2__tmp_get_substr_105;
        til_Array _tmp_get_substr_106;
        til_AllocError _err_alloc__tmp_get_substr_107;
        til_IndexOutOfBoundsError _err_idx__tmp_get_substr_107;
        til_Str _tmp_get_substr_108 = ((til_Str){(til_I64)"get_substr: start and end are the same (", 40});
        til_Str _tmp_get_substr_109 = til_I64_to_str(til_start);
        til_Str _tmp_get_substr_110 = ((til_Str){(til_I64)"), no substring", 15});
        til_Type _tmp_get_substr_111 = "Str";
        til_I64 _tmp_get_substr_112 = 3;
        int _arr_status__tmp_get_substr_107 = til_Array_new(&_tmp_get_substr_106, &_err_alloc__tmp_get_substr_107, _tmp_get_substr_111, &_tmp_get_substr_112);
        if (_arr_status__tmp_get_substr_107 != 0) {
            *_err2 = _err_alloc__tmp_get_substr_107; return 2;
        }
        til_I64 _tmp_get_substr_113 = 0;
        _arr_status__tmp_get_substr_107 = til_Array_set(&_err_idx__tmp_get_substr_107, &_tmp_get_substr_106, &_tmp_get_substr_113, (til_Dynamic*)&_tmp_get_substr_108);
        if (_arr_status__tmp_get_substr_107 != 0) {
            *_err1 = _err_idx__tmp_get_substr_107; return 1;
        }
        til_I64 _tmp_get_substr_114 = 1;
        _arr_status__tmp_get_substr_107 = til_Array_set(&_err_idx__tmp_get_substr_107, &_tmp_get_substr_106, &_tmp_get_substr_114, (til_Dynamic*)&_tmp_get_substr_109);
        if (_arr_status__tmp_get_substr_107 != 0) {
            *_err1 = _err_idx__tmp_get_substr_107; return 1;
        }
        til_I64 _tmp_get_substr_115 = 2;
        _arr_status__tmp_get_substr_107 = til_Array_set(&_err_idx__tmp_get_substr_107, &_tmp_get_substr_106, &_tmp_get_substr_115, (til_Dynamic*)&_tmp_get_substr_110);
        if (_arr_status__tmp_get_substr_107 != 0) {
            *_err1 = _err_idx__tmp_get_substr_107; return 1;
        }
        int _status__tmp_get_substr_105 = til_format(&_tmp_get_substr_104, &_err0__tmp_get_substr_105, &_err1__tmp_get_substr_105, &_err2__tmp_get_substr_105, &((til_Str){(til_I64)"src/core/str.til:387:48:", 24}), &_tmp_get_substr_106);
        if (_status__tmp_get_substr_105 != 0) {
            if (_status__tmp_get_substr_105 == 2) { *_err1 = _err1__tmp_get_substr_105; return 1; }
            if (_status__tmp_get_substr_105 == 3) { *_err2 = _err2__tmp_get_substr_105; return 2; }
        }
        til_Array_delete(&_tmp_get_substr_106);
        til_Str _tmp_get_substr_116;
        til_I64_OverflowError _err0__tmp_get_substr_117;
        til_IndexOutOfBoundsError _err1__tmp_get_substr_117;
        til_AllocError _err2__tmp_get_substr_117;
        til_Array _tmp_get_substr_118;
        til_AllocError _err_alloc__tmp_get_substr_119;
        til_IndexOutOfBoundsError _err_idx__tmp_get_substr_119;
        til_Str _tmp_get_substr_120 = ((til_Str){(til_I64)"get_substr: start and end are the same (", 40});
        til_Str _tmp_get_substr_121 = til_I64_to_str(til_start);
        til_Str _tmp_get_substr_122 = ((til_Str){(til_I64)"), no substring", 15});
        til_Type _tmp_get_substr_123 = "Str";
        til_I64 _tmp_get_substr_124 = 3;
        int _arr_status__tmp_get_substr_119 = til_Array_new(&_tmp_get_substr_118, &_err_alloc__tmp_get_substr_119, _tmp_get_substr_123, &_tmp_get_substr_124);
        if (_arr_status__tmp_get_substr_119 != 0) {
            *_err2 = _err_alloc__tmp_get_substr_119; return 2;
        }
        til_I64 _tmp_get_substr_125 = 0;
        _arr_status__tmp_get_substr_119 = til_Array_set(&_err_idx__tmp_get_substr_119, &_tmp_get_substr_118, &_tmp_get_substr_125, (til_Dynamic*)&_tmp_get_substr_120);
        if (_arr_status__tmp_get_substr_119 != 0) {
            *_err1 = _err_idx__tmp_get_substr_119; return 1;
        }
        til_I64 _tmp_get_substr_126 = 1;
        _arr_status__tmp_get_substr_119 = til_Array_set(&_err_idx__tmp_get_substr_119, &_tmp_get_substr_118, &_tmp_get_substr_126, (til_Dynamic*)&_tmp_get_substr_121);
        if (_arr_status__tmp_get_substr_119 != 0) {
            *_err1 = _err_idx__tmp_get_substr_119; return 1;
        }
        til_I64 _tmp_get_substr_127 = 2;
        _arr_status__tmp_get_substr_119 = til_Array_set(&_err_idx__tmp_get_substr_119, &_tmp_get_substr_118, &_tmp_get_substr_127, (til_Dynamic*)&_tmp_get_substr_122);
        if (_arr_status__tmp_get_substr_119 != 0) {
            *_err1 = _err_idx__tmp_get_substr_119; return 1;
        }
        int _status__tmp_get_substr_117 = til_format(&_tmp_get_substr_116, &_err0__tmp_get_substr_117, &_err1__tmp_get_substr_117, &_err2__tmp_get_substr_117, &((til_Str){(til_I64)"src/core/str.til:387:48:", 24}), &_tmp_get_substr_118);
        if (_status__tmp_get_substr_117 != 0) {
            if (_status__tmp_get_substr_117 == 2) { *_err1 = _err1__tmp_get_substr_117; return 1; }
            if (_status__tmp_get_substr_117 == 3) { *_err2 = _err2__tmp_get_substr_117; return 2; }
        }
        til_Array_delete(&_tmp_get_substr_118);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_get_substr_116};
        return 1;
    }
    til_Str til_substr = {.c_string = 0, .cap = 0};
    til_substr.cap = til_sub(til_end, til_start);
    til_I64 _tmp_get_substr_129 = til_add(&til_substr.cap, &(til_I64){1});
    til_I64 _ret__tmp_get_substr_128;
    til_AllocError _err0__tmp_get_substr_128 = {};
    int _status__tmp_get_substr_128 = til_malloc(&_ret__tmp_get_substr_128, &_err0__tmp_get_substr_128, &_tmp_get_substr_129);
    if (_status__tmp_get_substr_128 == 1) { *_err2 = _err0__tmp_get_substr_128; return 2; }
    til_substr.c_string = _ret__tmp_get_substr_128;
    if (til_I64_eq(&til_NULL, &til_substr.c_string).data) {
        til_Str _tmp_get_substr_130;
        til_I64_OverflowError _err0__tmp_get_substr_131;
        til_IndexOutOfBoundsError _err1__tmp_get_substr_131;
        til_AllocError _err2__tmp_get_substr_131;
        til_Array _tmp_get_substr_132;
        til_AllocError _err_alloc__tmp_get_substr_133;
        til_IndexOutOfBoundsError _err_idx__tmp_get_substr_133;
        til_Str _tmp_get_substr_134 = ((til_Str){(til_I64)"Str.get_substr: failed to allocate ", 35});
        til_Str _tmp_get_substr_135 = til_I64_to_str(&(til_I64){til_add(&til_substr.cap, &(til_I64){1})});
        til_Str _tmp_get_substr_136 = ((til_Str){(til_I64)" bytes", 6});
        til_Type _tmp_get_substr_137 = "Str";
        til_I64 _tmp_get_substr_138 = 3;
        int _arr_status__tmp_get_substr_133 = til_Array_new(&_tmp_get_substr_132, &_err_alloc__tmp_get_substr_133, _tmp_get_substr_137, &_tmp_get_substr_138);
        if (_arr_status__tmp_get_substr_133 != 0) {
            *_err2 = _err_alloc__tmp_get_substr_133; return 2;
        }
        til_I64 _tmp_get_substr_139 = 0;
        _arr_status__tmp_get_substr_133 = til_Array_set(&_err_idx__tmp_get_substr_133, &_tmp_get_substr_132, &_tmp_get_substr_139, (til_Dynamic*)&_tmp_get_substr_134);
        if (_arr_status__tmp_get_substr_133 != 0) {
            *_err1 = _err_idx__tmp_get_substr_133; return 1;
        }
        til_I64 _tmp_get_substr_140 = 1;
        _arr_status__tmp_get_substr_133 = til_Array_set(&_err_idx__tmp_get_substr_133, &_tmp_get_substr_132, &_tmp_get_substr_140, (til_Dynamic*)&_tmp_get_substr_135);
        if (_arr_status__tmp_get_substr_133 != 0) {
            *_err1 = _err_idx__tmp_get_substr_133; return 1;
        }
        til_I64 _tmp_get_substr_141 = 2;
        _arr_status__tmp_get_substr_133 = til_Array_set(&_err_idx__tmp_get_substr_133, &_tmp_get_substr_132, &_tmp_get_substr_141, (til_Dynamic*)&_tmp_get_substr_136);
        if (_arr_status__tmp_get_substr_133 != 0) {
            *_err1 = _err_idx__tmp_get_substr_133; return 1;
        }
        int _status__tmp_get_substr_131 = til_format(&_tmp_get_substr_130, &_err0__tmp_get_substr_131, &_err1__tmp_get_substr_131, &_err2__tmp_get_substr_131, &((til_Str){(til_I64)"src/core/str.til:394:37:", 24}), &_tmp_get_substr_132);
        if (_status__tmp_get_substr_131 != 0) {
            if (_status__tmp_get_substr_131 == 2) { *_err1 = _err1__tmp_get_substr_131; return 1; }
            if (_status__tmp_get_substr_131 == 3) { *_err2 = _err2__tmp_get_substr_131; return 2; }
        }
        til_Array_delete(&_tmp_get_substr_132);
        til_Str _tmp_get_substr_142;
        til_I64_OverflowError _err0__tmp_get_substr_143;
        til_IndexOutOfBoundsError _err1__tmp_get_substr_143;
        til_AllocError _err2__tmp_get_substr_143;
        til_Array _tmp_get_substr_144;
        til_AllocError _err_alloc__tmp_get_substr_145;
        til_IndexOutOfBoundsError _err_idx__tmp_get_substr_145;
        til_Str _tmp_get_substr_146 = ((til_Str){(til_I64)"Str.get_substr: failed to allocate ", 35});
        til_Str _tmp_get_substr_147 = til_I64_to_str(&(til_I64){til_add(&til_substr.cap, &(til_I64){1})});
        til_Str _tmp_get_substr_148 = ((til_Str){(til_I64)" bytes", 6});
        til_Type _tmp_get_substr_149 = "Str";
        til_I64 _tmp_get_substr_150 = 3;
        int _arr_status__tmp_get_substr_145 = til_Array_new(&_tmp_get_substr_144, &_err_alloc__tmp_get_substr_145, _tmp_get_substr_149, &_tmp_get_substr_150);
        if (_arr_status__tmp_get_substr_145 != 0) {
            *_err2 = _err_alloc__tmp_get_substr_145; return 2;
        }
        til_I64 _tmp_get_substr_151 = 0;
        _arr_status__tmp_get_substr_145 = til_Array_set(&_err_idx__tmp_get_substr_145, &_tmp_get_substr_144, &_tmp_get_substr_151, (til_Dynamic*)&_tmp_get_substr_146);
        if (_arr_status__tmp_get_substr_145 != 0) {
            *_err1 = _err_idx__tmp_get_substr_145; return 1;
        }
        til_I64 _tmp_get_substr_152 = 1;
        _arr_status__tmp_get_substr_145 = til_Array_set(&_err_idx__tmp_get_substr_145, &_tmp_get_substr_144, &_tmp_get_substr_152, (til_Dynamic*)&_tmp_get_substr_147);
        if (_arr_status__tmp_get_substr_145 != 0) {
            *_err1 = _err_idx__tmp_get_substr_145; return 1;
        }
        til_I64 _tmp_get_substr_153 = 2;
        _arr_status__tmp_get_substr_145 = til_Array_set(&_err_idx__tmp_get_substr_145, &_tmp_get_substr_144, &_tmp_get_substr_153, (til_Dynamic*)&_tmp_get_substr_148);
        if (_arr_status__tmp_get_substr_145 != 0) {
            *_err1 = _err_idx__tmp_get_substr_145; return 1;
        }
        int _status__tmp_get_substr_143 = til_format(&_tmp_get_substr_142, &_err0__tmp_get_substr_143, &_err1__tmp_get_substr_143, &_err2__tmp_get_substr_143, &((til_Str){(til_I64)"src/core/str.til:394:37:", 24}), &_tmp_get_substr_144);
        if (_status__tmp_get_substr_143 != 0) {
            if (_status__tmp_get_substr_143 == 2) { *_err1 = _err1__tmp_get_substr_143; return 1; }
            if (_status__tmp_get_substr_143 == 3) { *_err2 = _err2__tmp_get_substr_143; return 2; }
        }
        til_Array_delete(&_tmp_get_substr_144);
        *_err2 = (til_AllocError){.msg = _tmp_get_substr_142};
        return 2;
    }
    til_I64 _tmp_get_substr_154 = til_add(&til_s->c_string, til_start);
    til_memcpy(&til_substr.c_string, &_tmp_get_substr_154, &til_substr.cap);
    const til_U8 til_zero = 0;
    til_I64 _tmp_get_substr_155 = til_add(&til_substr.c_string, &til_substr.cap);
    til_I64 _tmp_get_substr_156 = 1;
    til_memset(&_tmp_get_substr_155, &til_zero, &_tmp_get_substr_156);
    *_ret = til_substr;
    return 0;
}

til_Str til_concat(const til_Str* til_a, const til_Str* til_b) {
    til_AllocError _thrown_AllocError__tmp_concat_0;
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_add(&til_a->cap, &til_b->cap);
    if (til_lt(&til_result.cap, &til_a->cap).data) {
        til_Array _tmp_concat_1;
        til_AllocError _err_alloc__tmp_concat_2;
        til_IndexOutOfBoundsError _err_idx__tmp_concat_2;
        til_Type _tmp_concat_3 = "Str";
        til_I64 _tmp_concat_4 = 0;
        int _arr_status__tmp_concat_2 = til_Array_new(&_tmp_concat_1, &_err_alloc__tmp_concat_2, _tmp_concat_3, &_tmp_concat_4);
        if (_arr_status__tmp_concat_2 != 0) {
        }
        til_panic(&((til_Str){(til_I64)"src/core/str.til:457:15:", 24}), &((til_Str){(til_I64)"concat: integer overflow", 24}), &_tmp_concat_1);
        til_Array_delete(&_tmp_concat_1);
    }
    til_I64 _tmp_concat_6 = til_add(&til_result.cap, &(til_I64){1});
    til_I64 _ret__tmp_concat_5;
    til_AllocError _err0__tmp_concat_5 = {};
    int _status__tmp_concat_5 = til_malloc(&_ret__tmp_concat_5, &_err0__tmp_concat_5, &_tmp_concat_6);
    if (_status__tmp_concat_5 == 1) { _thrown_AllocError__tmp_concat_0 = _err0__tmp_concat_5; goto _catch_AllocError__tmp_concat_0; }
    til_result.c_string = _ret__tmp_concat_5;
    if (til_I64_eq(&til_NULL, &til_result.c_string).data) {
        til_Array _tmp_concat_7;
        til_AllocError _err_alloc__tmp_concat_8;
        til_IndexOutOfBoundsError _err_idx__tmp_concat_8;
        til_Type _tmp_concat_9 = "Str";
        til_I64 _tmp_concat_10 = 0;
        int _arr_status__tmp_concat_8 = til_Array_new(&_tmp_concat_7, &_err_alloc__tmp_concat_8, _tmp_concat_9, &_tmp_concat_10);
        if (_arr_status__tmp_concat_8 != 0) {
        }
        til_panic(&((til_Str){(til_I64)"src/core/str.til:462:15:", 24}), &((til_Str){(til_I64)"concat: malloc failed", 21}), &_tmp_concat_7);
        til_Array_delete(&_tmp_concat_7);
    }
    til_memcpy(&til_result.c_string, &til_a->c_string, &til_a->cap);
    til_I64 _tmp_concat_11 = til_add(&til_result.c_string, &til_a->cap);
    til_memcpy(&_tmp_concat_11, &til_b->c_string, &til_b->cap);
    const til_U8 til_zero = 0;
    til_I64 _tmp_concat_12 = til_add(&til_result.c_string, &til_result.cap);
    til_I64 _tmp_concat_13 = 1;
    til_memset(&_tmp_concat_12, &til_zero, &_tmp_concat_13);
    if (0) { _catch_AllocError__tmp_concat_0:
        til_AllocError til_err = _thrown_AllocError__tmp_concat_0;
        til_Array _tmp_concat_14;
        til_AllocError _err_alloc__tmp_concat_15;
        til_IndexOutOfBoundsError _err_idx__tmp_concat_15;
        til_Type _tmp_concat_16 = "Str";
        til_I64 _tmp_concat_17 = 0;
        int _arr_status__tmp_concat_15 = til_Array_new(&_tmp_concat_14, &_err_alloc__tmp_concat_15, _tmp_concat_16, &_tmp_concat_17);
        if (_arr_status__tmp_concat_15 != 0) {
        }
        til_panic(&((til_Str){(til_I64)"src/core/str.til:472:15:", 24}), &til_err.msg, &_tmp_concat_14);
        til_Array_delete(&_tmp_concat_14);
    }
    return til_result;
}

int til_format(til_Str* _ret, til_I64_OverflowError* _err1, til_IndexOutOfBoundsError* _err2, til_AllocError* _err3, const til_Str* til_prefix, til_Array* til_args) {
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_prefix->cap;
    til_I64 til_i = 0;
    til_Str til_arg;
    if (til_lt(&(til_I64){0}, &(til_I64){til_Array_len(til_args)}).data) {
        while (til_lt(&til_i, &(til_I64){til_Array_len(til_args)}).data) {
            til_arg = ((til_Str){(til_I64)"", 0});
            til_IndexOutOfBoundsError _err0__tmp_format_0 = {};
            int _status__tmp_format_0 = til_Array_get(&_err0__tmp_format_0, til_args, &til_i, (til_Dynamic*)&til_arg);
            if (_status__tmp_format_0 == 1) { *_err2 = _err0__tmp_format_0; return 2; }
            til_result.cap = til_add(&til_result.cap, &til_arg.cap);
            if (til_lt(&til_result.cap, &til_arg.cap).data) {
                til_Str _tmp_format_1;
                til_I64_OverflowError _err0__tmp_format_2;
                til_IndexOutOfBoundsError _err1__tmp_format_2;
                til_AllocError _err2__tmp_format_2;
                til_Array _tmp_format_3;
                til_AllocError _err_alloc__tmp_format_4;
                til_IndexOutOfBoundsError _err_idx__tmp_format_4;
                til_Str _tmp_format_5 = ((til_Str){(til_I64)"format: integer overflow while summing cap for arg ", 51});
                til_Str _tmp_format_6 = til_I64_to_str(&til_i);
                til_Type _tmp_format_7 = "Str";
                til_I64 _tmp_format_8 = 2;
                int _arr_status__tmp_format_4 = til_Array_new(&_tmp_format_3, &_err_alloc__tmp_format_4, _tmp_format_7, &_tmp_format_8);
                if (_arr_status__tmp_format_4 != 0) {
                    *_err3 = _err_alloc__tmp_format_4; return 3;
                }
                til_I64 _tmp_format_9 = 0;
                _arr_status__tmp_format_4 = til_Array_set(&_err_idx__tmp_format_4, &_tmp_format_3, &_tmp_format_9, (til_Dynamic*)&_tmp_format_5);
                if (_arr_status__tmp_format_4 != 0) {
                    *_err2 = _err_idx__tmp_format_4; return 2;
                }
                til_I64 _tmp_format_10 = 1;
                _arr_status__tmp_format_4 = til_Array_set(&_err_idx__tmp_format_4, &_tmp_format_3, &_tmp_format_10, (til_Dynamic*)&_tmp_format_6);
                if (_arr_status__tmp_format_4 != 0) {
                    *_err2 = _err_idx__tmp_format_4; return 2;
                }
                int _status__tmp_format_2 = til_format(&_tmp_format_1, &_err0__tmp_format_2, &_err1__tmp_format_2, &_err2__tmp_format_2, &((til_Str){(til_I64)"src/core/str.til:488:48:", 24}), &_tmp_format_3);
                if (_status__tmp_format_2 != 0) {
                    if (_status__tmp_format_2 == 1) { *_err1 = _err0__tmp_format_2; return 1; }
                    if (_status__tmp_format_2 == 2) { *_err2 = _err1__tmp_format_2; return 2; }
                    if (_status__tmp_format_2 == 3) { *_err3 = _err2__tmp_format_2; return 3; }
                }
                til_Array_delete(&_tmp_format_3);
                til_Str _tmp_format_11;
                til_I64_OverflowError _err0__tmp_format_12;
                til_IndexOutOfBoundsError _err1__tmp_format_12;
                til_AllocError _err2__tmp_format_12;
                til_Array _tmp_format_13;
                til_AllocError _err_alloc__tmp_format_14;
                til_IndexOutOfBoundsError _err_idx__tmp_format_14;
                til_Str _tmp_format_15 = ((til_Str){(til_I64)"format: integer overflow while summing cap for arg ", 51});
                til_Str _tmp_format_16 = til_I64_to_str(&til_i);
                til_Type _tmp_format_17 = "Str";
                til_I64 _tmp_format_18 = 2;
                int _arr_status__tmp_format_14 = til_Array_new(&_tmp_format_13, &_err_alloc__tmp_format_14, _tmp_format_17, &_tmp_format_18);
                if (_arr_status__tmp_format_14 != 0) {
                    *_err3 = _err_alloc__tmp_format_14; return 3;
                }
                til_I64 _tmp_format_19 = 0;
                _arr_status__tmp_format_14 = til_Array_set(&_err_idx__tmp_format_14, &_tmp_format_13, &_tmp_format_19, (til_Dynamic*)&_tmp_format_15);
                if (_arr_status__tmp_format_14 != 0) {
                    *_err2 = _err_idx__tmp_format_14; return 2;
                }
                til_I64 _tmp_format_20 = 1;
                _arr_status__tmp_format_14 = til_Array_set(&_err_idx__tmp_format_14, &_tmp_format_13, &_tmp_format_20, (til_Dynamic*)&_tmp_format_16);
                if (_arr_status__tmp_format_14 != 0) {
                    *_err2 = _err_idx__tmp_format_14; return 2;
                }
                int _status__tmp_format_12 = til_format(&_tmp_format_11, &_err0__tmp_format_12, &_err1__tmp_format_12, &_err2__tmp_format_12, &((til_Str){(til_I64)"src/core/str.til:488:48:", 24}), &_tmp_format_13);
                if (_status__tmp_format_12 != 0) {
                    if (_status__tmp_format_12 == 1) { *_err1 = _err0__tmp_format_12; return 1; }
                    if (_status__tmp_format_12 == 2) { *_err2 = _err1__tmp_format_12; return 2; }
                    if (_status__tmp_format_12 == 3) { *_err3 = _err2__tmp_format_12; return 3; }
                }
                til_Array_delete(&_tmp_format_13);
                *_err1 = (til_I64_OverflowError){.msg = _tmp_format_11};
                return 1;
            }
            til_I64_inc(&til_i);
        }
    } else {
        while (til_gt(&til_i, &(til_I64){til_Array_len(til_args)}).data) {
            til_arg = ((til_Str){(til_I64)"", 0});
            til_IndexOutOfBoundsError _err0__tmp_format_21 = {};
            int _status__tmp_format_21 = til_Array_get(&_err0__tmp_format_21, til_args, &til_i, (til_Dynamic*)&til_arg);
            if (_status__tmp_format_21 == 1) { *_err2 = _err0__tmp_format_21; return 2; }
            til_result.cap = til_add(&til_result.cap, &til_arg.cap);
            if (til_lt(&til_result.cap, &til_arg.cap).data) {
                til_Str _tmp_format_22;
                til_I64_OverflowError _err0__tmp_format_23;
                til_IndexOutOfBoundsError _err1__tmp_format_23;
                til_AllocError _err2__tmp_format_23;
                til_Array _tmp_format_24;
                til_AllocError _err_alloc__tmp_format_25;
                til_IndexOutOfBoundsError _err_idx__tmp_format_25;
                til_Str _tmp_format_26 = ((til_Str){(til_I64)"format: integer overflow while summing cap for arg ", 51});
                til_Str _tmp_format_27 = til_I64_to_str(&til_i);
                til_Type _tmp_format_28 = "Str";
                til_I64 _tmp_format_29 = 2;
                int _arr_status__tmp_format_25 = til_Array_new(&_tmp_format_24, &_err_alloc__tmp_format_25, _tmp_format_28, &_tmp_format_29);
                if (_arr_status__tmp_format_25 != 0) {
                    *_err3 = _err_alloc__tmp_format_25; return 3;
                }
                til_I64 _tmp_format_30 = 0;
                _arr_status__tmp_format_25 = til_Array_set(&_err_idx__tmp_format_25, &_tmp_format_24, &_tmp_format_30, (til_Dynamic*)&_tmp_format_26);
                if (_arr_status__tmp_format_25 != 0) {
                    *_err2 = _err_idx__tmp_format_25; return 2;
                }
                til_I64 _tmp_format_31 = 1;
                _arr_status__tmp_format_25 = til_Array_set(&_err_idx__tmp_format_25, &_tmp_format_24, &_tmp_format_31, (til_Dynamic*)&_tmp_format_27);
                if (_arr_status__tmp_format_25 != 0) {
                    *_err2 = _err_idx__tmp_format_25; return 2;
                }
                int _status__tmp_format_23 = til_format(&_tmp_format_22, &_err0__tmp_format_23, &_err1__tmp_format_23, &_err2__tmp_format_23, &((til_Str){(til_I64)"src/core/str.til:488:48:", 24}), &_tmp_format_24);
                if (_status__tmp_format_23 != 0) {
                    if (_status__tmp_format_23 == 1) { *_err1 = _err0__tmp_format_23; return 1; }
                    if (_status__tmp_format_23 == 2) { *_err2 = _err1__tmp_format_23; return 2; }
                    if (_status__tmp_format_23 == 3) { *_err3 = _err2__tmp_format_23; return 3; }
                }
                til_Array_delete(&_tmp_format_24);
                til_Str _tmp_format_32;
                til_I64_OverflowError _err0__tmp_format_33;
                til_IndexOutOfBoundsError _err1__tmp_format_33;
                til_AllocError _err2__tmp_format_33;
                til_Array _tmp_format_34;
                til_AllocError _err_alloc__tmp_format_35;
                til_IndexOutOfBoundsError _err_idx__tmp_format_35;
                til_Str _tmp_format_36 = ((til_Str){(til_I64)"format: integer overflow while summing cap for arg ", 51});
                til_Str _tmp_format_37 = til_I64_to_str(&til_i);
                til_Type _tmp_format_38 = "Str";
                til_I64 _tmp_format_39 = 2;
                int _arr_status__tmp_format_35 = til_Array_new(&_tmp_format_34, &_err_alloc__tmp_format_35, _tmp_format_38, &_tmp_format_39);
                if (_arr_status__tmp_format_35 != 0) {
                    *_err3 = _err_alloc__tmp_format_35; return 3;
                }
                til_I64 _tmp_format_40 = 0;
                _arr_status__tmp_format_35 = til_Array_set(&_err_idx__tmp_format_35, &_tmp_format_34, &_tmp_format_40, (til_Dynamic*)&_tmp_format_36);
                if (_arr_status__tmp_format_35 != 0) {
                    *_err2 = _err_idx__tmp_format_35; return 2;
                }
                til_I64 _tmp_format_41 = 1;
                _arr_status__tmp_format_35 = til_Array_set(&_err_idx__tmp_format_35, &_tmp_format_34, &_tmp_format_41, (til_Dynamic*)&_tmp_format_37);
                if (_arr_status__tmp_format_35 != 0) {
                    *_err2 = _err_idx__tmp_format_35; return 2;
                }
                int _status__tmp_format_33 = til_format(&_tmp_format_32, &_err0__tmp_format_33, &_err1__tmp_format_33, &_err2__tmp_format_33, &((til_Str){(til_I64)"src/core/str.til:488:48:", 24}), &_tmp_format_34);
                if (_status__tmp_format_33 != 0) {
                    if (_status__tmp_format_33 == 1) { *_err1 = _err0__tmp_format_33; return 1; }
                    if (_status__tmp_format_33 == 2) { *_err2 = _err1__tmp_format_33; return 2; }
                    if (_status__tmp_format_33 == 3) { *_err3 = _err2__tmp_format_33; return 3; }
                }
                til_Array_delete(&_tmp_format_34);
                *_err1 = (til_I64_OverflowError){.msg = _tmp_format_32};
                return 1;
            }
            til_I64_dec(&til_i);
        }
    }
    til_I64 _tmp_format_43 = til_add(&til_result.cap, &(til_I64){1});
    til_I64 _ret__tmp_format_42;
    til_AllocError _err0__tmp_format_42 = {};
    int _status__tmp_format_42 = til_malloc(&_ret__tmp_format_42, &_err0__tmp_format_42, &_tmp_format_43);
    if (_status__tmp_format_42 == 1) { *_err3 = _err0__tmp_format_42; return 3; }
    til_result.c_string = _ret__tmp_format_42;
    if (til_I64_eq(&til_NULL, &til_result.c_string).data) {
        til_Str _tmp_format_44;
        til_I64_OverflowError _err0__tmp_format_45;
        til_IndexOutOfBoundsError _err1__tmp_format_45;
        til_AllocError _err2__tmp_format_45;
        til_Array _tmp_format_46;
        til_AllocError _err_alloc__tmp_format_47;
        til_IndexOutOfBoundsError _err_idx__tmp_format_47;
        til_Str _tmp_format_48 = ((til_Str){(til_I64)"format: malloc failed for cap = ", 32});
        til_Str _tmp_format_49 = til_I64_to_str(&(til_I64){til_add(&til_result.cap, &(til_I64){1})});
        til_Type _tmp_format_50 = "Str";
        til_I64 _tmp_format_51 = 2;
        int _arr_status__tmp_format_47 = til_Array_new(&_tmp_format_46, &_err_alloc__tmp_format_47, _tmp_format_50, &_tmp_format_51);
        if (_arr_status__tmp_format_47 != 0) {
            *_err3 = _err_alloc__tmp_format_47; return 3;
        }
        til_I64 _tmp_format_52 = 0;
        _arr_status__tmp_format_47 = til_Array_set(&_err_idx__tmp_format_47, &_tmp_format_46, &_tmp_format_52, (til_Dynamic*)&_tmp_format_48);
        if (_arr_status__tmp_format_47 != 0) {
            *_err2 = _err_idx__tmp_format_47; return 2;
        }
        til_I64 _tmp_format_53 = 1;
        _arr_status__tmp_format_47 = til_Array_set(&_err_idx__tmp_format_47, &_tmp_format_46, &_tmp_format_53, (til_Dynamic*)&_tmp_format_49);
        if (_arr_status__tmp_format_47 != 0) {
            *_err2 = _err_idx__tmp_format_47; return 2;
        }
        int _status__tmp_format_45 = til_format(&_tmp_format_44, &_err0__tmp_format_45, &_err1__tmp_format_45, &_err2__tmp_format_45, &((til_Str){(til_I64)"src/core/str.til:494:37:", 24}), &_tmp_format_46);
        if (_status__tmp_format_45 != 0) {
            if (_status__tmp_format_45 == 1) { *_err1 = _err0__tmp_format_45; return 1; }
            if (_status__tmp_format_45 == 2) { *_err2 = _err1__tmp_format_45; return 2; }
            if (_status__tmp_format_45 == 3) { *_err3 = _err2__tmp_format_45; return 3; }
        }
        til_Array_delete(&_tmp_format_46);
        til_Str _tmp_format_54;
        til_I64_OverflowError _err0__tmp_format_55;
        til_IndexOutOfBoundsError _err1__tmp_format_55;
        til_AllocError _err2__tmp_format_55;
        til_Array _tmp_format_56;
        til_AllocError _err_alloc__tmp_format_57;
        til_IndexOutOfBoundsError _err_idx__tmp_format_57;
        til_Str _tmp_format_58 = ((til_Str){(til_I64)"format: malloc failed for cap = ", 32});
        til_Str _tmp_format_59 = til_I64_to_str(&(til_I64){til_add(&til_result.cap, &(til_I64){1})});
        til_Type _tmp_format_60 = "Str";
        til_I64 _tmp_format_61 = 2;
        int _arr_status__tmp_format_57 = til_Array_new(&_tmp_format_56, &_err_alloc__tmp_format_57, _tmp_format_60, &_tmp_format_61);
        if (_arr_status__tmp_format_57 != 0) {
            *_err3 = _err_alloc__tmp_format_57; return 3;
        }
        til_I64 _tmp_format_62 = 0;
        _arr_status__tmp_format_57 = til_Array_set(&_err_idx__tmp_format_57, &_tmp_format_56, &_tmp_format_62, (til_Dynamic*)&_tmp_format_58);
        if (_arr_status__tmp_format_57 != 0) {
            *_err2 = _err_idx__tmp_format_57; return 2;
        }
        til_I64 _tmp_format_63 = 1;
        _arr_status__tmp_format_57 = til_Array_set(&_err_idx__tmp_format_57, &_tmp_format_56, &_tmp_format_63, (til_Dynamic*)&_tmp_format_59);
        if (_arr_status__tmp_format_57 != 0) {
            *_err2 = _err_idx__tmp_format_57; return 2;
        }
        int _status__tmp_format_55 = til_format(&_tmp_format_54, &_err0__tmp_format_55, &_err1__tmp_format_55, &_err2__tmp_format_55, &((til_Str){(til_I64)"src/core/str.til:494:37:", 24}), &_tmp_format_56);
        if (_status__tmp_format_55 != 0) {
            if (_status__tmp_format_55 == 1) { *_err1 = _err0__tmp_format_55; return 1; }
            if (_status__tmp_format_55 == 2) { *_err2 = _err1__tmp_format_55; return 2; }
            if (_status__tmp_format_55 == 3) { *_err3 = _err2__tmp_format_55; return 3; }
        }
        til_Array_delete(&_tmp_format_56);
        *_err3 = (til_AllocError){.msg = _tmp_format_54};
        return 3;
    }
    til_I64 til_offset = 0;
    til_memcpy(&til_result.c_string, &til_prefix->c_string, &til_prefix->cap);
    til_offset = til_prefix->cap;
    til_I64 _for_i_format_0 = 0;
    til_Str til_s;
    while (til_lt(&_for_i_format_0, &(til_I64){til_Array_len(til_args)}).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp_format_64;
        til_s = (til_Str){.c_string = 0, .cap = 0};
        til_IndexOutOfBoundsError _err0__tmp_format_65 = {};
        int _status__tmp_format_65 = til_Array_get(&_err0__tmp_format_65, til_args, &_for_i_format_0, (til_Dynamic*)&til_s);
        if (_status__tmp_format_65 == 1) { _thrown_IndexOutOfBoundsError__tmp_format_64 = _err0__tmp_format_65; goto _catch_IndexOutOfBoundsError__tmp_format_64; }
        if (0) { _catch_IndexOutOfBoundsError__tmp_format_64:
            til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp_format_64;
            til_Array _tmp_format_66;
            til_AllocError _err_alloc__tmp_format_67;
            til_IndexOutOfBoundsError _err_idx__tmp_format_67;
            til_Type _tmp_format_68 = "Str";
            til_I64 _tmp_format_69 = 0;
            int _arr_status__tmp_format_67 = til_Array_new(&_tmp_format_66, &_err_alloc__tmp_format_67, _tmp_format_68, &_tmp_format_69);
            if (_arr_status__tmp_format_67 != 0) {
                *_err3 = _err_alloc__tmp_format_67; return 3;
            }
            til_panic(&((til_Str){(til_I64)"src/core/str.til:501:5:", 23}), &til_err.msg, &_tmp_format_66);
            til_Array_delete(&_tmp_format_66);
        }
        til_I64 _tmp_format_70 = til_add(&til_result.c_string, &til_offset);
        til_memcpy(&_tmp_format_70, &til_s.c_string, &til_s.cap);
        til_offset = til_add(&til_offset, &til_s.cap);
        _for_i_format_0 = til_add(&_for_i_format_0, &(til_I64){1});
    }
    const til_U8 til_zero = 0;
    til_I64 _tmp_format_71 = til_add(&til_result.c_string, &til_result.cap);
    til_I64 _tmp_format_72 = 1;
    til_memset(&_tmp_format_71, &til_zero, &_tmp_format_72);
    *_ret = til_result;
    return 0;
}

void til_test(const til_Str* til_loc_str, const til_Bool* til_cond, const til_Str* til_msg) {
    til_assertm(til_loc_str, til_cond, til_msg);
}

void til_assert_eq(const til_Str* til_loc_str, const til_I64* til_a, const til_I64* til_b) {
    if (til_not(({ til_Bool _tmp_assert_eq_0 = til_I64_eq(til_a, til_b); &_tmp_assert_eq_0; })).data) {
        til_Array _tmp_assert_eq_1;
        til_AllocError _err_alloc__tmp_assert_eq_2;
        til_IndexOutOfBoundsError _err_idx__tmp_assert_eq_2;
        til_Str _tmp_assert_eq_3 = (*til_loc_str);
        til_Str _tmp_assert_eq_4 = ((til_Str){(til_I64)"assert_eq failed: expected '", 28});
        til_Str _tmp_assert_eq_5 = til_I64_to_str(til_a);
        til_Str _tmp_assert_eq_6 = ((til_Str){(til_I64)"', found '", 10});
        til_Str _tmp_assert_eq_7 = til_I64_to_str(til_b);
        til_Str _tmp_assert_eq_8 = ((til_Str){(til_I64)"'", 1});
        til_Type _tmp_assert_eq_9 = "Str";
        til_I64 _tmp_assert_eq_10 = 6;
        int _arr_status__tmp_assert_eq_2 = til_Array_new(&_tmp_assert_eq_1, &_err_alloc__tmp_assert_eq_2, _tmp_assert_eq_9, &_tmp_assert_eq_10);
        if (_arr_status__tmp_assert_eq_2 != 0) {
        }
        til_I64 _tmp_assert_eq_11 = 0;
        _arr_status__tmp_assert_eq_2 = til_Array_set(&_err_idx__tmp_assert_eq_2, &_tmp_assert_eq_1, &_tmp_assert_eq_11, (til_Dynamic*)&_tmp_assert_eq_3);
        if (_arr_status__tmp_assert_eq_2 != 0) {
        }
        til_I64 _tmp_assert_eq_12 = 1;
        _arr_status__tmp_assert_eq_2 = til_Array_set(&_err_idx__tmp_assert_eq_2, &_tmp_assert_eq_1, &_tmp_assert_eq_12, (til_Dynamic*)&_tmp_assert_eq_4);
        if (_arr_status__tmp_assert_eq_2 != 0) {
        }
        til_I64 _tmp_assert_eq_13 = 2;
        _arr_status__tmp_assert_eq_2 = til_Array_set(&_err_idx__tmp_assert_eq_2, &_tmp_assert_eq_1, &_tmp_assert_eq_13, (til_Dynamic*)&_tmp_assert_eq_5);
        if (_arr_status__tmp_assert_eq_2 != 0) {
        }
        til_I64 _tmp_assert_eq_14 = 3;
        _arr_status__tmp_assert_eq_2 = til_Array_set(&_err_idx__tmp_assert_eq_2, &_tmp_assert_eq_1, &_tmp_assert_eq_14, (til_Dynamic*)&_tmp_assert_eq_6);
        if (_arr_status__tmp_assert_eq_2 != 0) {
        }
        til_I64 _tmp_assert_eq_15 = 4;
        _arr_status__tmp_assert_eq_2 = til_Array_set(&_err_idx__tmp_assert_eq_2, &_tmp_assert_eq_1, &_tmp_assert_eq_15, (til_Dynamic*)&_tmp_assert_eq_7);
        if (_arr_status__tmp_assert_eq_2 != 0) {
        }
        til_I64 _tmp_assert_eq_16 = 5;
        _arr_status__tmp_assert_eq_2 = til_Array_set(&_err_idx__tmp_assert_eq_2, &_tmp_assert_eq_1, &_tmp_assert_eq_16, (til_Dynamic*)&_tmp_assert_eq_8);
        if (_arr_status__tmp_assert_eq_2 != 0) {
        }
        til_println(&_tmp_assert_eq_1);
        til_Array_delete(&_tmp_assert_eq_1);
        til_I64 _tmp_assert_eq_17 = 1;
        til_exit(&_tmp_assert_eq_17);
    }
}

void til_test_simple_add(void) {
    til_I64 _tmp_test_simple_add_0 = 1;
    til_I64 _tmp_test_simple_add_1 = 2;
    const til_I64 til_result = til_add(&_tmp_test_simple_add_0, &_tmp_test_simple_add_1);
    til_Bool _tmp_test_simple_add_2 = til_I64_eq(&til_result, &(til_I64){3});
    til_test(&((til_Str){(til_I64)"src/test/constfold.til:8:10:", 28}), &_tmp_test_simple_add_2, &((til_Str){(til_I64)"add(1, 2) should be 3", 21}));
}

void til_test_nested_arithmetic(void) {
    til_I64 _tmp_test_nested_arithmetic_0 = til_add(&(til_I64){1}, &(til_I64){2});
    til_I64 _tmp_test_nested_arithmetic_1 = til_sub(&(til_I64){10}, &(til_I64){5});
    const til_I64 til_result = til_mul(&_tmp_test_nested_arithmetic_0, &_tmp_test_nested_arithmetic_1);
    til_Bool _tmp_test_nested_arithmetic_2 = til_I64_eq(&til_result, &(til_I64){15});
    til_test(&((til_Str){(til_I64)"src/test/constfold.til:15:10:", 29}), &_tmp_test_nested_arithmetic_2, &((til_Str){(til_I64)"mul(add(1, 2), sub(10, 5)) should be 15", 39}));
}

void til_test_deeply_nested(void) {
    til_I64 _tmp_test_deeply_nested_0 = til_mul(&(til_I64){2}, &(til_I64){3});
    til_I64 _tmp_test_deeply_nested_1 = til_mul(&(til_I64){4}, &(til_I64){5});
    const til_I64 til_result = til_add(&_tmp_test_deeply_nested_0, &_tmp_test_deeply_nested_1);
    til_Bool _tmp_test_deeply_nested_2 = til_I64_eq(&til_result, &(til_I64){26});
    til_test(&((til_Str){(til_I64)"src/test/constfold.til:22:10:", 29}), &_tmp_test_deeply_nested_2, &((til_Str){(til_I64)"add(mul(2, 3), mul(4, 5)) should be 26", 38}));
}

void til_test_string_concat(void) {
    const til_Str til_result = til_concat(&((til_Str){(til_I64)"hello", 5}), &((til_Str){(til_I64)" world", 6}));
    til_Bool _tmp_test_string_concat_0 = til_Str_eq(&til_result, &((til_Str){(til_I64)"hello world", 11}));
    til_test(&((til_Str){(til_I64)"src/test/constfold.til:29:10:", 29}), &_tmp_test_string_concat_0, &((til_Str){(til_I64)"concat is folded at compile time", 32}));
}

void til_test_fold_variable(void) {
    const til_I64 til_x = 5;
    til_I64 _tmp_test_fold_variable_0 = 3;
    const til_I64 til_result = til_add(&til_x, &_tmp_test_fold_variable_0);
    til_Bool _tmp_test_fold_variable_1 = til_I64_eq(&til_result, &(til_I64){8});
    til_test(&((til_Str){(til_I64)"src/test/constfold.til:38:10:", 29}), &_tmp_test_fold_variable_1, &((til_Str){(til_I64)"add(x, 3) should fold to 8", 26}));
}

void til_test_loc_folded_correctly(void) {
    const til_Str til_location = ((til_Str){(til_I64)"src/test/constfold.til:44:17:", 29});
    til_Bool _tmp_test_loc_folded_correctly_0 = til_Str_contains(&til_location, &((til_Str){(til_I64)"constfold.til", 13}));
    til_test(&((til_Str){(til_I64)"src/test/constfold.til:45:10:", 29}), &_tmp_test_loc_folded_correctly_0, &((til_Str){(til_I64)"loc() should contain filename", 29}));
    til_Bool _tmp_test_loc_folded_correctly_1 = til_Str_contains(&til_location, &((til_Str){(til_I64)":44:", 4}));
    til_test(&((til_Str){(til_I64)"src/test/constfold.til:46:10:", 29}), &_tmp_test_loc_folded_correctly_1, &((til_Str){(til_I64)"loc() should contain correct line number", 40}));
}

void til_test_struct_fold_simple(void) {
    const til_CfVec2 til_v = til_CfVec2_magic();
    til_I64 _tmp_test_struct_fold_simple_0 = 42;
    til_assert_eq(&((til_Str){(til_I64)"src/test/constfold.til:71:15:", 29}), &_tmp_test_struct_fold_simple_0, &til_v.x);
    til_I64 _tmp_test_struct_fold_simple_1 = 99;
    til_assert_eq(&((til_Str){(til_I64)"src/test/constfold.til:72:15:", 29}), &_tmp_test_struct_fold_simple_1, &til_v.y);
}

void til_test_struct_fold_values(void) {
    til_I64 _tmp_test_struct_fold_values_0 = 10;
    til_I64 _tmp_test_struct_fold_values_1 = 20;
    const til_CfVec2 til_p = til_CfVec2_at(&_tmp_test_struct_fold_values_0, &_tmp_test_struct_fold_values_1);
    til_I64 _tmp_test_struct_fold_values_2 = 10;
    til_assert_eq(&((til_Str){(til_I64)"src/test/constfold.til:79:15:", 29}), &_tmp_test_struct_fold_values_2, &til_p.x);
    til_I64 _tmp_test_struct_fold_values_3 = 20;
    til_assert_eq(&((til_Str){(til_I64)"src/test/constfold.til:80:15:", 29}), &_tmp_test_struct_fold_values_3, &til_p.y);
}

void til_test_struct_fold_nested(void) {
    const til_CfRect til_r = til_CfRect_sample();
    til_I64 _tmp_test_struct_fold_nested_0 = 5;
    til_assert_eq(&((til_Str){(til_I64)"src/test/constfold.til:97:15:", 29}), &_tmp_test_struct_fold_nested_0, &til_r.top_left.x);
    til_I64 _tmp_test_struct_fold_nested_1 = 10;
    til_assert_eq(&((til_Str){(til_I64)"src/test/constfold.til:98:15:", 29}), &_tmp_test_struct_fold_nested_1, &til_r.top_left.y);
    til_I64 _tmp_test_struct_fold_nested_2 = 100;
    til_assert_eq(&((til_Str){(til_I64)"src/test/constfold.til:99:15:", 29}), &_tmp_test_struct_fold_nested_2, &til_r.bottom_right.x);
    til_I64 _tmp_test_struct_fold_nested_3 = 200;
    til_assert_eq(&((til_Str){(til_I64)"src/test/constfold.til:100:15:", 30}), &_tmp_test_struct_fold_nested_3, &til_r.bottom_right.y);
}

til_I64 til_Array_len(const til_Array* til_self) {
    return til_self->_len;
}

int til_Array_new(til_Array* _ret, til_AllocError* _err1, til_Type til_T, const til_I64* til_capacity) {
    til_Array til_arr = {.type_name = ((til_Str){(til_I64)"", 0}), .type_size = 0, .ptr = 0, ._len = 0};
    til_arr.type_name = ((til_Str){(til_I64)til_T, strlen(til_T)});
    til_arr.type_size = til_size_of(&((til_Str){(til_I64)til_T, strlen(til_T)}));
    const til_I64 til_size_bytes = til_mul(til_capacity, &til_arr.type_size);
    til_I64 _ret__tmp_til_Array_new_0;
    til_AllocError _err0__tmp_til_Array_new_0 = {};
    int _status__tmp_til_Array_new_0 = til_malloc(&_ret__tmp_til_Array_new_0, &_err0__tmp_til_Array_new_0, &til_size_bytes);
    if (_status__tmp_til_Array_new_0 == 1) { *_err1 = _err0__tmp_til_Array_new_0; return 1; }
    til_arr.ptr = _ret__tmp_til_Array_new_0;
    til_U8 _tmp_til_Array_new_1;
    til_U8_OverflowError _err0__tmp_til_Array_new_2;
    int _status__tmp_til_Array_new_2 = til_U8_from_i64(&_tmp_til_Array_new_1, &_err0__tmp_til_Array_new_2, &(til_I64){0});
    if (_status__tmp_til_Array_new_2 != 0) {
    }
    til_memset(&til_arr.ptr, &_tmp_til_Array_new_1, &til_size_bytes);
    til_arr._len = (*til_capacity);
    *_ret = til_arr;
    return 0;
}

int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array* til_self, const til_I64* til_index, til_Dynamic* til_T) {
    if (til_I64_gteq(til_index, &til_self->_len).data) {
        til_Str _tmp_til_Array_get_0;
        til_I64_OverflowError _err0__tmp_til_Array_get_1;
        til_IndexOutOfBoundsError _err1__tmp_til_Array_get_1;
        til_AllocError _err2__tmp_til_Array_get_1;
        til_Array _tmp_til_Array_get_2;
        til_AllocError _err_alloc__tmp_til_Array_get_3;
        til_IndexOutOfBoundsError _err_idx__tmp_til_Array_get_3;
        til_Str _tmp_til_Array_get_4 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        til_Type _tmp_til_Array_get_5 = "Str";
        til_I64 _tmp_til_Array_get_6 = 1;
        int _arr_status__tmp_til_Array_get_3 = til_Array_new(&_tmp_til_Array_get_2, &_err_alloc__tmp_til_Array_get_3, _tmp_til_Array_get_5, &_tmp_til_Array_get_6);
        if (_arr_status__tmp_til_Array_get_3 != 0) {
        }
        til_I64 _tmp_til_Array_get_7 = 0;
        _arr_status__tmp_til_Array_get_3 = til_Array_set(&_err_idx__tmp_til_Array_get_3, &_tmp_til_Array_get_2, &_tmp_til_Array_get_7, (til_Dynamic*)&_tmp_til_Array_get_4);
        if (_arr_status__tmp_til_Array_get_3 != 0) {
            *_err1 = _err_idx__tmp_til_Array_get_3; return 1;
        }
        int _status__tmp_til_Array_get_1 = til_format(&_tmp_til_Array_get_0, &_err0__tmp_til_Array_get_1, &_err1__tmp_til_Array_get_1, &_err2__tmp_til_Array_get_1, &((til_Str){(til_I64)"src/core/array.til:41:52:", 25}), &_tmp_til_Array_get_2);
        if (_status__tmp_til_Array_get_1 != 0) {
            if (_status__tmp_til_Array_get_1 == 2) { *_err1 = _err1__tmp_til_Array_get_1; return 1; }
        }
        til_Array_delete(&_tmp_til_Array_get_2);
        til_Str _tmp_til_Array_get_8;
        til_I64_OverflowError _err0__tmp_til_Array_get_9;
        til_IndexOutOfBoundsError _err1__tmp_til_Array_get_9;
        til_AllocError _err2__tmp_til_Array_get_9;
        til_Array _tmp_til_Array_get_10;
        til_AllocError _err_alloc__tmp_til_Array_get_11;
        til_IndexOutOfBoundsError _err_idx__tmp_til_Array_get_11;
        til_Str _tmp_til_Array_get_12 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        til_Type _tmp_til_Array_get_13 = "Str";
        til_I64 _tmp_til_Array_get_14 = 1;
        int _arr_status__tmp_til_Array_get_11 = til_Array_new(&_tmp_til_Array_get_10, &_err_alloc__tmp_til_Array_get_11, _tmp_til_Array_get_13, &_tmp_til_Array_get_14);
        if (_arr_status__tmp_til_Array_get_11 != 0) {
        }
        til_I64 _tmp_til_Array_get_15 = 0;
        _arr_status__tmp_til_Array_get_11 = til_Array_set(&_err_idx__tmp_til_Array_get_11, &_tmp_til_Array_get_10, &_tmp_til_Array_get_15, (til_Dynamic*)&_tmp_til_Array_get_12);
        if (_arr_status__tmp_til_Array_get_11 != 0) {
            *_err1 = _err_idx__tmp_til_Array_get_11; return 1;
        }
        int _status__tmp_til_Array_get_9 = til_format(&_tmp_til_Array_get_8, &_err0__tmp_til_Array_get_9, &_err1__tmp_til_Array_get_9, &_err2__tmp_til_Array_get_9, &((til_Str){(til_I64)"src/core/array.til:41:52:", 25}), &_tmp_til_Array_get_10);
        if (_status__tmp_til_Array_get_9 != 0) {
            if (_status__tmp_til_Array_get_9 == 2) { *_err1 = _err1__tmp_til_Array_get_9; return 1; }
        }
        til_Array_delete(&_tmp_til_Array_get_10);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_til_Array_get_8};
        return 1;
    }
    til_I64 _tmp_til_Array_get_16 = til_mul(til_index, &til_self->type_size);
    const til_I64 til_src = til_add(&til_self->ptr, &_tmp_til_Array_get_16);
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(&til_dest, &til_src, &til_self->type_size);
    return 0;
}

int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64* til_index, const til_Dynamic* til_value) {
    if (til_I64_gteq(til_index, &til_self->_len).data) {
        til_Str _tmp_til_Array_set_0;
        til_I64_OverflowError _err0__tmp_til_Array_set_1;
        til_IndexOutOfBoundsError _err1__tmp_til_Array_set_1;
        til_AllocError _err2__tmp_til_Array_set_1;
        til_Array _tmp_til_Array_set_2;
        til_AllocError _err_alloc__tmp_til_Array_set_3;
        til_IndexOutOfBoundsError _err_idx__tmp_til_Array_set_3;
        til_Str _tmp_til_Array_set_4 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        til_Type _tmp_til_Array_set_5 = "Str";
        til_I64 _tmp_til_Array_set_6 = 1;
        int _arr_status__tmp_til_Array_set_3 = til_Array_new(&_tmp_til_Array_set_2, &_err_alloc__tmp_til_Array_set_3, _tmp_til_Array_set_5, &_tmp_til_Array_set_6);
        if (_arr_status__tmp_til_Array_set_3 != 0) {
        }
        til_I64 _tmp_til_Array_set_7 = 0;
        _arr_status__tmp_til_Array_set_3 = til_Array_set(&_err_idx__tmp_til_Array_set_3, &_tmp_til_Array_set_2, &_tmp_til_Array_set_7, (til_Dynamic*)&_tmp_til_Array_set_4);
        if (_arr_status__tmp_til_Array_set_3 != 0) {
            *_err1 = _err_idx__tmp_til_Array_set_3; return 1;
        }
        int _status__tmp_til_Array_set_1 = til_format(&_tmp_til_Array_set_0, &_err0__tmp_til_Array_set_1, &_err1__tmp_til_Array_set_1, &_err2__tmp_til_Array_set_1, &((til_Str){(til_I64)"src/core/array.til:56:52:", 25}), &_tmp_til_Array_set_2);
        if (_status__tmp_til_Array_set_1 != 0) {
            if (_status__tmp_til_Array_set_1 == 2) { *_err1 = _err1__tmp_til_Array_set_1; return 1; }
        }
        til_Array_delete(&_tmp_til_Array_set_2);
        til_Str _tmp_til_Array_set_8;
        til_I64_OverflowError _err0__tmp_til_Array_set_9;
        til_IndexOutOfBoundsError _err1__tmp_til_Array_set_9;
        til_AllocError _err2__tmp_til_Array_set_9;
        til_Array _tmp_til_Array_set_10;
        til_AllocError _err_alloc__tmp_til_Array_set_11;
        til_IndexOutOfBoundsError _err_idx__tmp_til_Array_set_11;
        til_Str _tmp_til_Array_set_12 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        til_Type _tmp_til_Array_set_13 = "Str";
        til_I64 _tmp_til_Array_set_14 = 1;
        int _arr_status__tmp_til_Array_set_11 = til_Array_new(&_tmp_til_Array_set_10, &_err_alloc__tmp_til_Array_set_11, _tmp_til_Array_set_13, &_tmp_til_Array_set_14);
        if (_arr_status__tmp_til_Array_set_11 != 0) {
        }
        til_I64 _tmp_til_Array_set_15 = 0;
        _arr_status__tmp_til_Array_set_11 = til_Array_set(&_err_idx__tmp_til_Array_set_11, &_tmp_til_Array_set_10, &_tmp_til_Array_set_15, (til_Dynamic*)&_tmp_til_Array_set_12);
        if (_arr_status__tmp_til_Array_set_11 != 0) {
            *_err1 = _err_idx__tmp_til_Array_set_11; return 1;
        }
        int _status__tmp_til_Array_set_9 = til_format(&_tmp_til_Array_set_8, &_err0__tmp_til_Array_set_9, &_err1__tmp_til_Array_set_9, &_err2__tmp_til_Array_set_9, &((til_Str){(til_I64)"src/core/array.til:56:52:", 25}), &_tmp_til_Array_set_10);
        if (_status__tmp_til_Array_set_9 != 0) {
            if (_status__tmp_til_Array_set_9 == 2) { *_err1 = _err1__tmp_til_Array_set_9; return 1; }
        }
        til_Array_delete(&_tmp_til_Array_set_10);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_til_Array_set_8};
        return 1;
    }
    til_I64 _tmp_til_Array_set_16 = til_mul(til_index, &til_self->type_size);
    til_I64 til_dest = til_add(&til_self->ptr, &_tmp_til_Array_set_16);
    til_I64 _tmp_til_Array_set_17 = (til_I64)til_value;
    til_memcpy(&til_dest, &_tmp_til_Array_set_17, &til_self->type_size);
    return 0;
}

void til_Array_delete(til_Array* til_self) {
    til_free(&til_self->ptr);
    til_self->ptr = 0;
    til_self->_len = 0;
}

til_Bool til_Bool_and(const til_Bool* til_self, const til_Bool* til_other) {
    if ((*til_self).data) {
        return (*til_other);
    }
    return false;
}

til_Bool til_I64_eq(const til_I64* til_a, const til_I64* til_b) {
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

til_Str til_I64_to_str(const til_I64* til_self) {
    return til_i64_to_str(til_self);
}

til_I64 til_I64_from_str(const til_Str* til_str) {
    return til_str_to_i64(til_str);
}

void til_I64_inc(til_I64* til_self) {
    *til_self = til_add(til_self, &(til_I64){1});
}

void til_I64_dec(til_I64* til_self) {
    *til_self = til_sub(til_self, &(til_I64){1});
}

til_Bool til_I64_gteq(const til_I64* til_a, const til_I64* til_b) {
    if (til_gt(til_a, til_b).data) {
        return true;
    }
    if (til_lt(til_a, til_b).data) {
        return false;
    }
    return true;
}

til_Bool til_I64_lteq(const til_I64* til_a, const til_I64* til_b) {
    if (til_lt(til_a, til_b).data) {
        return true;
    }
    if (til_gt(til_a, til_b).data) {
        return false;
    }
    return true;
}

til_Vec til_Vec_new(til_Type til_T) {
    til_Vec til_vec = {.type_name = ((til_Str){(til_I64)"", 0}), .type_size = 0, .ptr = 0, ._len = 0, .cap = 0};
    til_vec.type_name = ((til_Str){(til_I64)til_T, strlen(til_T)});
    til_vec.type_size = til_size_of(&((til_Str){(til_I64)til_T, strlen(til_T)}));
    til_vec.ptr = til_NULL;
    til_vec._len = 0;
    til_vec.cap = 0;
    return til_vec;
}

int til_Vec_push(til_AllocError* _err1, til_Vec* til_self, const til_Dynamic* til_value) {
    til_I64 til_new_cap;
    til_I64 til_new_ptr;
    if (til_I64_eq(&til_self->_len, &til_self->cap).data) {
        til_I64 _tmp_til_Vec_push_0 = 2;
        til_new_cap = til_mul(&til_self->cap, &_tmp_til_Vec_push_0);
        if (til_lt(&til_new_cap, &(til_I64){1}).data) {
            til_new_cap = 1;
        }
        if (til_gt(&til_new_cap, &til_Vec_MAX_CAP).data) {
            til_Array _tmp_til_Vec_push_1;
            til_AllocError _err_alloc__tmp_til_Vec_push_2;
            til_IndexOutOfBoundsError _err_idx__tmp_til_Vec_push_2;
            til_Type _tmp_til_Vec_push_3 = "Str";
            til_I64 _tmp_til_Vec_push_4 = 0;
            int _arr_status__tmp_til_Vec_push_2 = til_Array_new(&_tmp_til_Vec_push_1, &_err_alloc__tmp_til_Vec_push_2, _tmp_til_Vec_push_3, &_tmp_til_Vec_push_4);
            if (_arr_status__tmp_til_Vec_push_2 != 0) {
                *_err1 = _err_alloc__tmp_til_Vec_push_2; return 1;
            }
            til_panic(&((til_Str){(til_I64)"src/core/vec.til:87:23:", 23}), &((til_Str){(til_I64)"Vec.push: capacity exceeded Vec.MAX_CAP", 39}), &_tmp_til_Vec_push_1);
            til_Array_delete(&_tmp_til_Vec_push_1);
        }
        til_I64 _tmp_til_Vec_push_6 = til_mul(&til_new_cap, &til_self->type_size);
        til_I64 _ret__tmp_til_Vec_push_5;
        til_I64 til_new_ptr;
        til_AllocError _err0__tmp_til_Vec_push_5 = {};
        int _status__tmp_til_Vec_push_5 = til_malloc(&_ret__tmp_til_Vec_push_5, &_err0__tmp_til_Vec_push_5, &_tmp_til_Vec_push_6);
        if (_status__tmp_til_Vec_push_5 == 1) { *_err1 = _err0__tmp_til_Vec_push_5; return 1; }
        til_new_ptr = _ret__tmp_til_Vec_push_5;
        if (til_gt(&til_self->_len, &(til_I64){0}).data) {
            til_I64 _tmp_til_Vec_push_7 = til_mul(&til_self->_len, &til_self->type_size);
            til_memcpy(&til_new_ptr, &til_self->ptr, &_tmp_til_Vec_push_7);
        }
        if (til_gt(&til_self->ptr, &(til_I64){0}).data) {
            til_free(&til_self->ptr);
        }
        til_self->ptr = til_new_ptr;
        til_self->cap = til_new_cap;
    }
    til_I64 _tmp_til_Vec_push_8 = til_mul(&til_self->_len, &til_self->type_size);
    til_I64 til_dest = til_add(&til_self->ptr, &_tmp_til_Vec_push_8);
    til_I64 _tmp_til_Vec_push_9 = (til_I64)til_value;
    til_memcpy(&til_dest, &_tmp_til_Vec_push_9, &til_self->type_size);
    til_self->_len = til_add(&til_self->_len, &(til_I64){1});
    return 0;
}

int til_Vec_get(til_IndexOutOfBoundsError* _err1, const til_Vec* til_self, const til_I64* til_index, til_Dynamic* til_T) {
    if (til_I64_gteq(til_index, &til_self->_len).data) {
        til_Str _tmp_til_Vec_get_0;
        til_I64_OverflowError _err0__tmp_til_Vec_get_1;
        til_IndexOutOfBoundsError _err1__tmp_til_Vec_get_1;
        til_AllocError _err2__tmp_til_Vec_get_1;
        til_Array _tmp_til_Vec_get_2;
        til_AllocError _err_alloc__tmp_til_Vec_get_3;
        til_IndexOutOfBoundsError _err_idx__tmp_til_Vec_get_3;
        til_Str _tmp_til_Vec_get_4 = ((til_Str){(til_I64)"Vec.get: index out of bounds", 28});
        til_Type _tmp_til_Vec_get_5 = "Str";
        til_I64 _tmp_til_Vec_get_6 = 1;
        int _arr_status__tmp_til_Vec_get_3 = til_Array_new(&_tmp_til_Vec_get_2, &_err_alloc__tmp_til_Vec_get_3, _tmp_til_Vec_get_5, &_tmp_til_Vec_get_6);
        if (_arr_status__tmp_til_Vec_get_3 != 0) {
        }
        til_I64 _tmp_til_Vec_get_7 = 0;
        _arr_status__tmp_til_Vec_get_3 = til_Array_set(&_err_idx__tmp_til_Vec_get_3, &_tmp_til_Vec_get_2, &_tmp_til_Vec_get_7, (til_Dynamic*)&_tmp_til_Vec_get_4);
        if (_arr_status__tmp_til_Vec_get_3 != 0) {
            *_err1 = _err_idx__tmp_til_Vec_get_3; return 1;
        }
        int _status__tmp_til_Vec_get_1 = til_format(&_tmp_til_Vec_get_0, &_err0__tmp_til_Vec_get_1, &_err1__tmp_til_Vec_get_1, &_err2__tmp_til_Vec_get_1, &((til_Str){(til_I64)"src/core/vec.til:109:52:", 24}), &_tmp_til_Vec_get_2);
        if (_status__tmp_til_Vec_get_1 != 0) {
            if (_status__tmp_til_Vec_get_1 == 2) { *_err1 = _err1__tmp_til_Vec_get_1; return 1; }
        }
        til_Array_delete(&_tmp_til_Vec_get_2);
        til_Str _tmp_til_Vec_get_8;
        til_I64_OverflowError _err0__tmp_til_Vec_get_9;
        til_IndexOutOfBoundsError _err1__tmp_til_Vec_get_9;
        til_AllocError _err2__tmp_til_Vec_get_9;
        til_Array _tmp_til_Vec_get_10;
        til_AllocError _err_alloc__tmp_til_Vec_get_11;
        til_IndexOutOfBoundsError _err_idx__tmp_til_Vec_get_11;
        til_Str _tmp_til_Vec_get_12 = ((til_Str){(til_I64)"Vec.get: index out of bounds", 28});
        til_Type _tmp_til_Vec_get_13 = "Str";
        til_I64 _tmp_til_Vec_get_14 = 1;
        int _arr_status__tmp_til_Vec_get_11 = til_Array_new(&_tmp_til_Vec_get_10, &_err_alloc__tmp_til_Vec_get_11, _tmp_til_Vec_get_13, &_tmp_til_Vec_get_14);
        if (_arr_status__tmp_til_Vec_get_11 != 0) {
        }
        til_I64 _tmp_til_Vec_get_15 = 0;
        _arr_status__tmp_til_Vec_get_11 = til_Array_set(&_err_idx__tmp_til_Vec_get_11, &_tmp_til_Vec_get_10, &_tmp_til_Vec_get_15, (til_Dynamic*)&_tmp_til_Vec_get_12);
        if (_arr_status__tmp_til_Vec_get_11 != 0) {
            *_err1 = _err_idx__tmp_til_Vec_get_11; return 1;
        }
        int _status__tmp_til_Vec_get_9 = til_format(&_tmp_til_Vec_get_8, &_err0__tmp_til_Vec_get_9, &_err1__tmp_til_Vec_get_9, &_err2__tmp_til_Vec_get_9, &((til_Str){(til_I64)"src/core/vec.til:109:52:", 24}), &_tmp_til_Vec_get_10);
        if (_status__tmp_til_Vec_get_9 != 0) {
            if (_status__tmp_til_Vec_get_9 == 2) { *_err1 = _err1__tmp_til_Vec_get_9; return 1; }
        }
        til_Array_delete(&_tmp_til_Vec_get_10);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_til_Vec_get_8};
        return 1;
    }
    til_I64 _tmp_til_Vec_get_16 = til_mul(til_index, &til_self->type_size);
    const til_I64 til_src = til_add(&til_self->ptr, &_tmp_til_Vec_get_16);
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(&til_dest, &til_src, &til_self->type_size);
    return 0;
}

til_I64 til_Str_len(const til_Str* til_self) {
    return til_self->cap;
}

til_Bool til_Str_eq(const til_Str* til_self, const til_Str* til_other) {
    if (til_not(({ til_Bool _tmp_til_Str_eq_0 = til_I64_eq(&til_self->cap, &til_other->cap); &_tmp_til_Str_eq_0; })).data) {
        return false;
    }
    til_I64 til_i = 0;
    til_U8 til_self_byte;
    til_U8 til_other_byte;
    if (til_lt(&(til_I64){0}, &til_self->cap).data) {
        while (til_lt(&til_i, &til_self->cap).data) {
            til_self_byte = 0;
            til_other_byte = 0;
            til_I64 _tmp_til_Str_eq_1 = (til_I64)&til_self_byte;
            til_I64 _tmp_til_Str_eq_2 = til_add(&til_self->c_string, &til_i);
            til_I64 _tmp_til_Str_eq_3 = 1;
            til_memcpy(&_tmp_til_Str_eq_1, &_tmp_til_Str_eq_2, &_tmp_til_Str_eq_3);
            til_I64 _tmp_til_Str_eq_4 = (til_I64)&til_other_byte;
            til_I64 _tmp_til_Str_eq_5 = til_add(&til_other->c_string, &til_i);
            til_I64 _tmp_til_Str_eq_6 = 1;
            til_memcpy(&_tmp_til_Str_eq_4, &_tmp_til_Str_eq_5, &_tmp_til_Str_eq_6);
            if (til_not(({ til_Bool _tmp_til_Str_eq_7 = til_U8_eq(&til_self_byte, &til_other_byte); &_tmp_til_Str_eq_7; })).data) {
                return false;
            }
            til_I64_inc(&til_i);
        }
    } else {
        while (til_gt(&til_i, &til_self->cap).data) {
            til_self_byte = 0;
            til_other_byte = 0;
            til_I64 _tmp_til_Str_eq_8 = (til_I64)&til_self_byte;
            til_I64 _tmp_til_Str_eq_9 = til_add(&til_self->c_string, &til_i);
            til_I64 _tmp_til_Str_eq_10 = 1;
            til_memcpy(&_tmp_til_Str_eq_8, &_tmp_til_Str_eq_9, &_tmp_til_Str_eq_10);
            til_I64 _tmp_til_Str_eq_11 = (til_I64)&til_other_byte;
            til_I64 _tmp_til_Str_eq_12 = til_add(&til_other->c_string, &til_i);
            til_I64 _tmp_til_Str_eq_13 = 1;
            til_memcpy(&_tmp_til_Str_eq_11, &_tmp_til_Str_eq_12, &_tmp_til_Str_eq_13);
            if (til_not(({ til_Bool _tmp_til_Str_eq_14 = til_U8_eq(&til_self_byte, &til_other_byte); &_tmp_til_Str_eq_14; })).data) {
                return false;
            }
            til_I64_dec(&til_i);
        }
    }
    return true;
}

int til_Str_clone(til_Str* _ret, til_AllocError* _err1, const til_Str* til_self) {
    til_Str til_cloned = {.c_string = 0, .cap = 0};
    til_cloned.cap = til_self->cap;
    til_I64 _tmp_til_Str_clone_1 = til_add(&til_cloned.cap, &(til_I64){1});
    til_I64 _ret__tmp_til_Str_clone_0;
    til_AllocError _err0__tmp_til_Str_clone_0 = {};
    int _status__tmp_til_Str_clone_0 = til_malloc(&_ret__tmp_til_Str_clone_0, &_err0__tmp_til_Str_clone_0, &_tmp_til_Str_clone_1);
    if (_status__tmp_til_Str_clone_0 == 1) { *_err1 = _err0__tmp_til_Str_clone_0; return 1; }
    til_cloned.c_string = _ret__tmp_til_Str_clone_0;
    if (til_I64_eq(&til_NULL, &til_cloned.c_string).data) {
        til_Str _tmp_til_Str_clone_2;
        til_I64_OverflowError _err0__tmp_til_Str_clone_3;
        til_IndexOutOfBoundsError _err1__tmp_til_Str_clone_3;
        til_AllocError _err2__tmp_til_Str_clone_3;
        til_Array _tmp_til_Str_clone_4;
        til_AllocError _err_alloc__tmp_til_Str_clone_5;
        til_IndexOutOfBoundsError _err_idx__tmp_til_Str_clone_5;
        til_Str _tmp_til_Str_clone_6 = ((til_Str){(til_I64)"Str.clone: malloc failed for ", 29});
        til_Str _tmp_til_Str_clone_7 = til_I64_to_str(&(til_I64){til_add(&til_cloned.cap, &(til_I64){1})});
        til_Str _tmp_til_Str_clone_8 = ((til_Str){(til_I64)" bytes", 6});
        til_Type _tmp_til_Str_clone_9 = "Str";
        til_I64 _tmp_til_Str_clone_10 = 3;
        int _arr_status__tmp_til_Str_clone_5 = til_Array_new(&_tmp_til_Str_clone_4, &_err_alloc__tmp_til_Str_clone_5, _tmp_til_Str_clone_9, &_tmp_til_Str_clone_10);
        if (_arr_status__tmp_til_Str_clone_5 != 0) {
            *_err1 = _err_alloc__tmp_til_Str_clone_5; return 1;
        }
        til_I64 _tmp_til_Str_clone_11 = 0;
        _arr_status__tmp_til_Str_clone_5 = til_Array_set(&_err_idx__tmp_til_Str_clone_5, &_tmp_til_Str_clone_4, &_tmp_til_Str_clone_11, (til_Dynamic*)&_tmp_til_Str_clone_6);
        if (_arr_status__tmp_til_Str_clone_5 != 0) {
        }
        til_I64 _tmp_til_Str_clone_12 = 1;
        _arr_status__tmp_til_Str_clone_5 = til_Array_set(&_err_idx__tmp_til_Str_clone_5, &_tmp_til_Str_clone_4, &_tmp_til_Str_clone_12, (til_Dynamic*)&_tmp_til_Str_clone_7);
        if (_arr_status__tmp_til_Str_clone_5 != 0) {
        }
        til_I64 _tmp_til_Str_clone_13 = 2;
        _arr_status__tmp_til_Str_clone_5 = til_Array_set(&_err_idx__tmp_til_Str_clone_5, &_tmp_til_Str_clone_4, &_tmp_til_Str_clone_13, (til_Dynamic*)&_tmp_til_Str_clone_8);
        if (_arr_status__tmp_til_Str_clone_5 != 0) {
        }
        int _status__tmp_til_Str_clone_3 = til_format(&_tmp_til_Str_clone_2, &_err0__tmp_til_Str_clone_3, &_err1__tmp_til_Str_clone_3, &_err2__tmp_til_Str_clone_3, &((til_Str){(til_I64)"src/core/str.til:46:41:", 23}), &_tmp_til_Str_clone_4);
        if (_status__tmp_til_Str_clone_3 != 0) {
            if (_status__tmp_til_Str_clone_3 == 3) { *_err1 = _err2__tmp_til_Str_clone_3; return 1; }
        }
        til_Array_delete(&_tmp_til_Str_clone_4);
        til_Str _tmp_til_Str_clone_14;
        til_I64_OverflowError _err0__tmp_til_Str_clone_15;
        til_IndexOutOfBoundsError _err1__tmp_til_Str_clone_15;
        til_AllocError _err2__tmp_til_Str_clone_15;
        til_Array _tmp_til_Str_clone_16;
        til_AllocError _err_alloc__tmp_til_Str_clone_17;
        til_IndexOutOfBoundsError _err_idx__tmp_til_Str_clone_17;
        til_Str _tmp_til_Str_clone_18 = ((til_Str){(til_I64)"Str.clone: malloc failed for ", 29});
        til_Str _tmp_til_Str_clone_19 = til_I64_to_str(&(til_I64){til_add(&til_cloned.cap, &(til_I64){1})});
        til_Str _tmp_til_Str_clone_20 = ((til_Str){(til_I64)" bytes", 6});
        til_Type _tmp_til_Str_clone_21 = "Str";
        til_I64 _tmp_til_Str_clone_22 = 3;
        int _arr_status__tmp_til_Str_clone_17 = til_Array_new(&_tmp_til_Str_clone_16, &_err_alloc__tmp_til_Str_clone_17, _tmp_til_Str_clone_21, &_tmp_til_Str_clone_22);
        if (_arr_status__tmp_til_Str_clone_17 != 0) {
            *_err1 = _err_alloc__tmp_til_Str_clone_17; return 1;
        }
        til_I64 _tmp_til_Str_clone_23 = 0;
        _arr_status__tmp_til_Str_clone_17 = til_Array_set(&_err_idx__tmp_til_Str_clone_17, &_tmp_til_Str_clone_16, &_tmp_til_Str_clone_23, (til_Dynamic*)&_tmp_til_Str_clone_18);
        if (_arr_status__tmp_til_Str_clone_17 != 0) {
        }
        til_I64 _tmp_til_Str_clone_24 = 1;
        _arr_status__tmp_til_Str_clone_17 = til_Array_set(&_err_idx__tmp_til_Str_clone_17, &_tmp_til_Str_clone_16, &_tmp_til_Str_clone_24, (til_Dynamic*)&_tmp_til_Str_clone_19);
        if (_arr_status__tmp_til_Str_clone_17 != 0) {
        }
        til_I64 _tmp_til_Str_clone_25 = 2;
        _arr_status__tmp_til_Str_clone_17 = til_Array_set(&_err_idx__tmp_til_Str_clone_17, &_tmp_til_Str_clone_16, &_tmp_til_Str_clone_25, (til_Dynamic*)&_tmp_til_Str_clone_20);
        if (_arr_status__tmp_til_Str_clone_17 != 0) {
        }
        int _status__tmp_til_Str_clone_15 = til_format(&_tmp_til_Str_clone_14, &_err0__tmp_til_Str_clone_15, &_err1__tmp_til_Str_clone_15, &_err2__tmp_til_Str_clone_15, &((til_Str){(til_I64)"src/core/str.til:46:41:", 23}), &_tmp_til_Str_clone_16);
        if (_status__tmp_til_Str_clone_15 != 0) {
            if (_status__tmp_til_Str_clone_15 == 3) { *_err1 = _err2__tmp_til_Str_clone_15; return 1; }
        }
        til_Array_delete(&_tmp_til_Str_clone_16);
        *_err1 = (til_AllocError){.msg = _tmp_til_Str_clone_14};
        return 1;
    }
    til_memcpy(&til_cloned.c_string, &til_self->c_string, &til_self->cap);
    const til_U8 til_zero = 0;
    til_I64 _tmp_til_Str_clone_26 = til_add(&til_cloned.c_string, &til_cloned.cap);
    til_I64 _tmp_til_Str_clone_27 = 1;
    til_memset(&_tmp_til_Str_clone_26, &til_zero, &_tmp_til_Str_clone_27);
    *_ret = til_cloned;
    return 0;
}

til_Bool til_Str_contains(const til_Str* til_self, const til_Str* til_needle) {
    if (til_gt(&(til_I64){til_Str_len(til_needle)}, &(til_I64){til_Str_len(til_self)}).data) {
        return false;
    }
    if (til_I64_eq(&(til_I64){til_Str_len(til_needle)}, &(til_I64){0}).data) {
        return false;
    }
    til_I64 _tmp_til_Str_contains_0 = til_Str_len(til_self);
    til_I64 _tmp_til_Str_contains_1 = til_Str_len(til_needle);
    til_I64 til_max_start = til_sub(&_tmp_til_Str_contains_0, &_tmp_til_Str_contains_1);
    til_I64 til_start_idx = 0;
    til_Bool til_matches;
    til_I64 til_needle_idx;
    til_U8 til_self_byte;
    til_U8 til_needle_byte;
    if (til_lt(&(til_I64){0}, &(til_I64){til_add(&til_max_start, &(til_I64){1})}).data) {
        while (til_lt(&til_start_idx, &(til_I64){til_add(&til_max_start, &(til_I64){1})}).data) {
            til_matches = true;
            til_needle_idx = 0;
            if (til_lt(&(til_I64){0}, &(til_I64){til_Str_len(til_needle)}).data) {
                while (til_lt(&til_needle_idx, &(til_I64){til_Str_len(til_needle)}).data) {
                    til_self_byte = 0;
                    til_needle_byte = 0;
                    til_I64 _tmp_til_Str_contains_2 = (til_I64)&til_self_byte;
                    til_I64 _tmp_til_Str_contains_3 = til_add(&til_self->c_string, &(til_I64){til_add(&til_start_idx, &til_needle_idx)});
                    til_I64 _tmp_til_Str_contains_4 = 1;
                    til_memcpy(&_tmp_til_Str_contains_2, &_tmp_til_Str_contains_3, &_tmp_til_Str_contains_4);
                    til_I64 _tmp_til_Str_contains_5 = (til_I64)&til_needle_byte;
                    til_I64 _tmp_til_Str_contains_6 = til_add(&til_needle->c_string, &til_needle_idx);
                    til_I64 _tmp_til_Str_contains_7 = 1;
                    til_memcpy(&_tmp_til_Str_contains_5, &_tmp_til_Str_contains_6, &_tmp_til_Str_contains_7);
                    if (til_not(({ til_Bool _tmp_til_Str_contains_8 = til_U8_eq(&til_self_byte, &til_needle_byte); &_tmp_til_Str_contains_8; })).data) {
                        til_matches = false;
                    }
                    til_I64_inc(&til_needle_idx);
                }
            } else {
                while (til_gt(&til_needle_idx, &(til_I64){til_Str_len(til_needle)}).data) {
                    til_self_byte = 0;
                    til_needle_byte = 0;
                    til_I64 _tmp_til_Str_contains_9 = (til_I64)&til_self_byte;
                    til_I64 _tmp_til_Str_contains_10 = til_add(&til_self->c_string, &(til_I64){til_add(&til_start_idx, &til_needle_idx)});
                    til_I64 _tmp_til_Str_contains_11 = 1;
                    til_memcpy(&_tmp_til_Str_contains_9, &_tmp_til_Str_contains_10, &_tmp_til_Str_contains_11);
                    til_I64 _tmp_til_Str_contains_12 = (til_I64)&til_needle_byte;
                    til_I64 _tmp_til_Str_contains_13 = til_add(&til_needle->c_string, &til_needle_idx);
                    til_I64 _tmp_til_Str_contains_14 = 1;
                    til_memcpy(&_tmp_til_Str_contains_12, &_tmp_til_Str_contains_13, &_tmp_til_Str_contains_14);
                    if (til_not(({ til_Bool _tmp_til_Str_contains_15 = til_U8_eq(&til_self_byte, &til_needle_byte); &_tmp_til_Str_contains_15; })).data) {
                        til_matches = false;
                    }
                    til_I64_dec(&til_needle_idx);
                }
            }
            if (til_matches.data) {
                return true;
            }
            til_I64_inc(&til_start_idx);
        }
    } else {
        while (til_gt(&til_start_idx, &(til_I64){til_add(&til_max_start, &(til_I64){1})}).data) {
            til_matches = true;
            til_needle_idx = 0;
            if (til_lt(&(til_I64){0}, &(til_I64){til_Str_len(til_needle)}).data) {
                while (til_lt(&til_needle_idx, &(til_I64){til_Str_len(til_needle)}).data) {
                    til_self_byte = 0;
                    til_needle_byte = 0;
                    til_I64 _tmp_til_Str_contains_16 = (til_I64)&til_self_byte;
                    til_I64 _tmp_til_Str_contains_17 = til_add(&til_self->c_string, &(til_I64){til_add(&til_start_idx, &til_needle_idx)});
                    til_I64 _tmp_til_Str_contains_18 = 1;
                    til_memcpy(&_tmp_til_Str_contains_16, &_tmp_til_Str_contains_17, &_tmp_til_Str_contains_18);
                    til_I64 _tmp_til_Str_contains_19 = (til_I64)&til_needle_byte;
                    til_I64 _tmp_til_Str_contains_20 = til_add(&til_needle->c_string, &til_needle_idx);
                    til_I64 _tmp_til_Str_contains_21 = 1;
                    til_memcpy(&_tmp_til_Str_contains_19, &_tmp_til_Str_contains_20, &_tmp_til_Str_contains_21);
                    if (til_not(({ til_Bool _tmp_til_Str_contains_22 = til_U8_eq(&til_self_byte, &til_needle_byte); &_tmp_til_Str_contains_22; })).data) {
                        til_matches = false;
                    }
                    til_I64_inc(&til_needle_idx);
                }
            } else {
                while (til_gt(&til_needle_idx, &(til_I64){til_Str_len(til_needle)}).data) {
                    til_self_byte = 0;
                    til_needle_byte = 0;
                    til_I64 _tmp_til_Str_contains_23 = (til_I64)&til_self_byte;
                    til_I64 _tmp_til_Str_contains_24 = til_add(&til_self->c_string, &(til_I64){til_add(&til_start_idx, &til_needle_idx)});
                    til_I64 _tmp_til_Str_contains_25 = 1;
                    til_memcpy(&_tmp_til_Str_contains_23, &_tmp_til_Str_contains_24, &_tmp_til_Str_contains_25);
                    til_I64 _tmp_til_Str_contains_26 = (til_I64)&til_needle_byte;
                    til_I64 _tmp_til_Str_contains_27 = til_add(&til_needle->c_string, &til_needle_idx);
                    til_I64 _tmp_til_Str_contains_28 = 1;
                    til_memcpy(&_tmp_til_Str_contains_26, &_tmp_til_Str_contains_27, &_tmp_til_Str_contains_28);
                    if (til_not(({ til_Bool _tmp_til_Str_contains_29 = til_U8_eq(&til_self_byte, &til_needle_byte); &_tmp_til_Str_contains_29; })).data) {
                        til_matches = false;
                    }
                    til_I64_dec(&til_needle_idx);
                }
            }
            if (til_matches.data) {
                return true;
            }
            til_I64_dec(&til_start_idx);
        }
    }
    return false;
}

til_I64 til_Str_find(const til_Str* til_self, const til_Str* til_needle) {
    if (til_gt(&(til_I64){til_Str_len(til_needle)}, &(til_I64){til_Str_len(til_self)}).data) {
        return til_sub(&(til_I64){0}, &(til_I64){1});
    }
    if (til_I64_eq(&(til_I64){til_Str_len(til_needle)}, &(til_I64){0}).data) {
        return til_sub(&(til_I64){0}, &(til_I64){1});
    }
    til_I64 _tmp_til_Str_find_0 = til_Str_len(til_self);
    til_I64 _tmp_til_Str_find_1 = til_Str_len(til_needle);
    til_I64 til_max_start = til_sub(&_tmp_til_Str_find_0, &_tmp_til_Str_find_1);
    til_I64 til_start_idx = 0;
    til_Bool til_matches;
    til_I64 til_needle_idx;
    til_U8 til_self_byte;
    til_U8 til_needle_byte;
    while (til_I64_lteq(&til_start_idx, &til_max_start).data) {
        til_matches = true;
        til_needle_idx = 0;
        while (til_lt(&til_needle_idx, &(til_I64){til_Str_len(til_needle)}).data) {
            if (til_not(&til_matches).data) {
                til_needle_idx = til_Str_len(til_needle);
            } else {
                til_self_byte = 0;
                til_needle_byte = 0;
                til_I64 _tmp_til_Str_find_2 = (til_I64)&til_self_byte;
                til_I64 _tmp_til_Str_find_3 = til_add(&til_self->c_string, &(til_I64){til_add(&til_start_idx, &til_needle_idx)});
                til_I64 _tmp_til_Str_find_4 = 1;
                til_memcpy(&_tmp_til_Str_find_2, &_tmp_til_Str_find_3, &_tmp_til_Str_find_4);
                til_I64 _tmp_til_Str_find_5 = (til_I64)&til_needle_byte;
                til_I64 _tmp_til_Str_find_6 = til_add(&til_needle->c_string, &til_needle_idx);
                til_I64 _tmp_til_Str_find_7 = 1;
                til_memcpy(&_tmp_til_Str_find_5, &_tmp_til_Str_find_6, &_tmp_til_Str_find_7);
                if (til_not(({ til_Bool _tmp_til_Str_find_8 = til_U8_eq(&til_self_byte, &til_needle_byte); &_tmp_til_Str_find_8; })).data) {
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
    return til_sub(&(til_I64){0}, &(til_I64){1});
}

int til_Str_replacen(til_Str* _ret, til_AllocError* _err1, const til_Str* til_self, const til_Str* til_from, const til_Str* til_to, const til_I64* til_n) {
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp_til_Str_replacen_0;
    if (til_I64_eq(&(til_I64){til_Str_len(til_from)}, &(til_I64){0}).data) {
        til_Str _ret__tmp_til_Str_replacen_1;
        til_AllocError _err0__tmp_til_Str_replacen_1 = {};
        int _status__tmp_til_Str_replacen_1 = til_Str_clone(&_ret__tmp_til_Str_replacen_1, &_err0__tmp_til_Str_replacen_1, til_self);
        if (_status__tmp_til_Str_replacen_1 == 1) { *_err1 = _err0__tmp_til_Str_replacen_1; return 1; }
        *_ret = _ret__tmp_til_Str_replacen_1;
        return 0;
    }
    if (til_I64_eq(til_n, &(til_I64){0}).data) {
        til_Str _ret__tmp_til_Str_replacen_2;
        til_AllocError _err0__tmp_til_Str_replacen_2 = {};
        int _status__tmp_til_Str_replacen_2 = til_Str_clone(&_ret__tmp_til_Str_replacen_2, &_err0__tmp_til_Str_replacen_2, til_self);
        if (_status__tmp_til_Str_replacen_2 == 1) { *_err1 = _err0__tmp_til_Str_replacen_2; return 1; }
        *_ret = _ret__tmp_til_Str_replacen_2;
        return 0;
    }
    til_I64 til_idx = til_Str_find(til_self, til_from);
    if (til_lt(&til_idx, &(til_I64){0}).data) {
        til_Str _ret__tmp_til_Str_replacen_3;
        til_AllocError _err0__tmp_til_Str_replacen_3 = {};
        int _status__tmp_til_Str_replacen_3 = til_Str_clone(&_ret__tmp_til_Str_replacen_3, &_err0__tmp_til_Str_replacen_3, til_self);
        if (_status__tmp_til_Str_replacen_3 == 1) { *_err1 = _err0__tmp_til_Str_replacen_3; return 1; }
        *_ret = _ret__tmp_til_Str_replacen_3;
        return 0;
    }
    til_I64 _tmp_til_Str_replacen_5 = 0;
    til_Str _ret__tmp_til_Str_replacen_4;
    til_Str til_prefix;
    til_IndexOutOfBoundsError _err0__tmp_til_Str_replacen_4 = {};
    til_AllocError _err1__tmp_til_Str_replacen_4 = {};
    int _status__tmp_til_Str_replacen_4 = til_get_substr(&_ret__tmp_til_Str_replacen_4, &_err0__tmp_til_Str_replacen_4, &_err1__tmp_til_Str_replacen_4, til_self, &_tmp_til_Str_replacen_5, &til_idx);
    if (_status__tmp_til_Str_replacen_4 == 1) { _thrown_IndexOutOfBoundsError__tmp_til_Str_replacen_0 = _err0__tmp_til_Str_replacen_4; goto _catch_IndexOutOfBoundsError__tmp_til_Str_replacen_0; }
    if (_status__tmp_til_Str_replacen_4 == 2) { *_err1 = _err1__tmp_til_Str_replacen_4; return 1; }
    til_prefix = _ret__tmp_til_Str_replacen_4;
    til_I64 _tmp_til_Str_replacen_7 = til_add(&til_idx, &(til_I64){til_Str_len(til_from)});
    til_I64 _tmp_til_Str_replacen_8 = til_Str_len(til_self);
    til_Str _ret__tmp_til_Str_replacen_6;
    til_Str til_suffix;
    til_IndexOutOfBoundsError _err0__tmp_til_Str_replacen_6 = {};
    til_AllocError _err1__tmp_til_Str_replacen_6 = {};
    int _status__tmp_til_Str_replacen_6 = til_get_substr(&_ret__tmp_til_Str_replacen_6, &_err0__tmp_til_Str_replacen_6, &_err1__tmp_til_Str_replacen_6, til_self, &_tmp_til_Str_replacen_7, &_tmp_til_Str_replacen_8);
    if (_status__tmp_til_Str_replacen_6 == 1) { _thrown_IndexOutOfBoundsError__tmp_til_Str_replacen_0 = _err0__tmp_til_Str_replacen_6; goto _catch_IndexOutOfBoundsError__tmp_til_Str_replacen_0; }
    if (_status__tmp_til_Str_replacen_6 == 2) { *_err1 = _err1__tmp_til_Str_replacen_6; return 1; }
    til_suffix = _ret__tmp_til_Str_replacen_6;
    til_Str _tmp_til_Str_replacen_9 = til_concat(&til_prefix, til_to);
    til_Str til_result = til_concat(&_tmp_til_Str_replacen_9, &til_suffix);
    til_Str til_rest;
    if (til_gt(til_n, &(til_I64){1}).data) {
        til_I64 _tmp_til_Str_replacen_11 = til_sub(til_n, &(til_I64){1});
        til_Str _ret__tmp_til_Str_replacen_10;
        til_Str til_rest;
        til_AllocError _err0__tmp_til_Str_replacen_10 = {};
        int _status__tmp_til_Str_replacen_10 = til_Str_replacen(&_ret__tmp_til_Str_replacen_10, &_err0__tmp_til_Str_replacen_10, &til_suffix, til_from, til_to, &_tmp_til_Str_replacen_11);
        if (_status__tmp_til_Str_replacen_10 == 1) { *_err1 = _err0__tmp_til_Str_replacen_10; return 1; }
        til_rest = _ret__tmp_til_Str_replacen_10;
        til_result = til_concat(({ til_Str _tmp_til_Str_replacen_12 = til_concat(&til_prefix, til_to); &_tmp_til_Str_replacen_12; }), &til_rest);
    }
    if (0) { _catch_IndexOutOfBoundsError__tmp_til_Str_replacen_0:
        til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp_til_Str_replacen_0;
        til_Str _ret__tmp_til_Str_replacen_13;
        til_AllocError _err0__tmp_til_Str_replacen_13 = {};
        int _status__tmp_til_Str_replacen_13 = til_Str_clone(&_ret__tmp_til_Str_replacen_13, &_err0__tmp_til_Str_replacen_13, til_self);
        if (_status__tmp_til_Str_replacen_13 == 1) { *_err1 = _err0__tmp_til_Str_replacen_13; return 1; }
        til_result = _ret__tmp_til_Str_replacen_13;
    }
    *_ret = til_result;
    return 0;
}

til_Bool til_U8_eq(const til_U8* til_self, const til_U8* til_other) {
    return til_I64_eq(&(til_I64){til_U8_to_i64(til_self)}, &(til_I64){til_U8_to_i64(til_other)});
}

til_I64 til_U8_to_i64(const til_U8* til_self) {
    return til_u8_to_i64(til_self);
}

int til_U8_from_i64(til_U8* _ret, til_U8_OverflowError* _err1, const til_I64* til_self) {
    if (til_lt(til_self, &(til_I64){0}).data) {
        til_Str _tmp_til_U8_from_i64_0;
        til_I64_OverflowError _err0__tmp_til_U8_from_i64_1;
        til_IndexOutOfBoundsError _err1__tmp_til_U8_from_i64_1;
        til_AllocError _err2__tmp_til_U8_from_i64_1;
        til_Array _tmp_til_U8_from_i64_2;
        til_AllocError _err_alloc__tmp_til_U8_from_i64_3;
        til_IndexOutOfBoundsError _err_idx__tmp_til_U8_from_i64_3;
        til_Str _tmp_til_U8_from_i64_4 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        til_Type _tmp_til_U8_from_i64_5 = "Str";
        til_I64 _tmp_til_U8_from_i64_6 = 1;
        int _arr_status__tmp_til_U8_from_i64_3 = til_Array_new(&_tmp_til_U8_from_i64_2, &_err_alloc__tmp_til_U8_from_i64_3, _tmp_til_U8_from_i64_5, &_tmp_til_U8_from_i64_6);
        if (_arr_status__tmp_til_U8_from_i64_3 != 0) {
        }
        til_I64 _tmp_til_U8_from_i64_7 = 0;
        _arr_status__tmp_til_U8_from_i64_3 = til_Array_set(&_err_idx__tmp_til_U8_from_i64_3, &_tmp_til_U8_from_i64_2, &_tmp_til_U8_from_i64_7, (til_Dynamic*)&_tmp_til_U8_from_i64_4);
        if (_arr_status__tmp_til_U8_from_i64_3 != 0) {
        }
        int _status__tmp_til_U8_from_i64_1 = til_format(&_tmp_til_U8_from_i64_0, &_err0__tmp_til_U8_from_i64_1, &_err1__tmp_til_U8_from_i64_1, &_err2__tmp_til_U8_from_i64_1, &((til_Str){(til_I64)"src/core/u8.til:50:47:", 22}), &_tmp_til_U8_from_i64_2);
        if (_status__tmp_til_U8_from_i64_1 != 0) {
        }
        til_Array_delete(&_tmp_til_U8_from_i64_2);
        til_Str _tmp_til_U8_from_i64_8;
        til_I64_OverflowError _err0__tmp_til_U8_from_i64_9;
        til_IndexOutOfBoundsError _err1__tmp_til_U8_from_i64_9;
        til_AllocError _err2__tmp_til_U8_from_i64_9;
        til_Array _tmp_til_U8_from_i64_10;
        til_AllocError _err_alloc__tmp_til_U8_from_i64_11;
        til_IndexOutOfBoundsError _err_idx__tmp_til_U8_from_i64_11;
        til_Str _tmp_til_U8_from_i64_12 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        til_Type _tmp_til_U8_from_i64_13 = "Str";
        til_I64 _tmp_til_U8_from_i64_14 = 1;
        int _arr_status__tmp_til_U8_from_i64_11 = til_Array_new(&_tmp_til_U8_from_i64_10, &_err_alloc__tmp_til_U8_from_i64_11, _tmp_til_U8_from_i64_13, &_tmp_til_U8_from_i64_14);
        if (_arr_status__tmp_til_U8_from_i64_11 != 0) {
        }
        til_I64 _tmp_til_U8_from_i64_15 = 0;
        _arr_status__tmp_til_U8_from_i64_11 = til_Array_set(&_err_idx__tmp_til_U8_from_i64_11, &_tmp_til_U8_from_i64_10, &_tmp_til_U8_from_i64_15, (til_Dynamic*)&_tmp_til_U8_from_i64_12);
        if (_arr_status__tmp_til_U8_from_i64_11 != 0) {
        }
        int _status__tmp_til_U8_from_i64_9 = til_format(&_tmp_til_U8_from_i64_8, &_err0__tmp_til_U8_from_i64_9, &_err1__tmp_til_U8_from_i64_9, &_err2__tmp_til_U8_from_i64_9, &((til_Str){(til_I64)"src/core/u8.til:50:47:", 22}), &_tmp_til_U8_from_i64_10);
        if (_status__tmp_til_U8_from_i64_9 != 0) {
        }
        til_Array_delete(&_tmp_til_U8_from_i64_10);
        *_err1 = (til_U8_OverflowError){.msg = _tmp_til_U8_from_i64_8};
        return 1;
    }
    if (til_gt(til_self, &til_MAX_U8).data) {
        til_Str _tmp_til_U8_from_i64_16;
        til_I64_OverflowError _err0__tmp_til_U8_from_i64_17;
        til_IndexOutOfBoundsError _err1__tmp_til_U8_from_i64_17;
        til_AllocError _err2__tmp_til_U8_from_i64_17;
        til_Array _tmp_til_U8_from_i64_18;
        til_AllocError _err_alloc__tmp_til_U8_from_i64_19;
        til_IndexOutOfBoundsError _err_idx__tmp_til_U8_from_i64_19;
        til_Str _tmp_til_U8_from_i64_20 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp_til_U8_from_i64_21 = til_I64_to_str(&til_MAX_U8);
        til_Type _tmp_til_U8_from_i64_22 = "Str";
        til_I64 _tmp_til_U8_from_i64_23 = 2;
        int _arr_status__tmp_til_U8_from_i64_19 = til_Array_new(&_tmp_til_U8_from_i64_18, &_err_alloc__tmp_til_U8_from_i64_19, _tmp_til_U8_from_i64_22, &_tmp_til_U8_from_i64_23);
        if (_arr_status__tmp_til_U8_from_i64_19 != 0) {
        }
        til_I64 _tmp_til_U8_from_i64_24 = 0;
        _arr_status__tmp_til_U8_from_i64_19 = til_Array_set(&_err_idx__tmp_til_U8_from_i64_19, &_tmp_til_U8_from_i64_18, &_tmp_til_U8_from_i64_24, (til_Dynamic*)&_tmp_til_U8_from_i64_20);
        if (_arr_status__tmp_til_U8_from_i64_19 != 0) {
        }
        til_I64 _tmp_til_U8_from_i64_25 = 1;
        _arr_status__tmp_til_U8_from_i64_19 = til_Array_set(&_err_idx__tmp_til_U8_from_i64_19, &_tmp_til_U8_from_i64_18, &_tmp_til_U8_from_i64_25, (til_Dynamic*)&_tmp_til_U8_from_i64_21);
        if (_arr_status__tmp_til_U8_from_i64_19 != 0) {
        }
        int _status__tmp_til_U8_from_i64_17 = til_format(&_tmp_til_U8_from_i64_16, &_err0__tmp_til_U8_from_i64_17, &_err1__tmp_til_U8_from_i64_17, &_err2__tmp_til_U8_from_i64_17, &((til_Str){(til_I64)"src/core/u8.til:53:47:", 22}), &_tmp_til_U8_from_i64_18);
        if (_status__tmp_til_U8_from_i64_17 != 0) {
        }
        til_Array_delete(&_tmp_til_U8_from_i64_18);
        til_Str _tmp_til_U8_from_i64_26;
        til_I64_OverflowError _err0__tmp_til_U8_from_i64_27;
        til_IndexOutOfBoundsError _err1__tmp_til_U8_from_i64_27;
        til_AllocError _err2__tmp_til_U8_from_i64_27;
        til_Array _tmp_til_U8_from_i64_28;
        til_AllocError _err_alloc__tmp_til_U8_from_i64_29;
        til_IndexOutOfBoundsError _err_idx__tmp_til_U8_from_i64_29;
        til_Str _tmp_til_U8_from_i64_30 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp_til_U8_from_i64_31 = til_I64_to_str(&til_MAX_U8);
        til_Type _tmp_til_U8_from_i64_32 = "Str";
        til_I64 _tmp_til_U8_from_i64_33 = 2;
        int _arr_status__tmp_til_U8_from_i64_29 = til_Array_new(&_tmp_til_U8_from_i64_28, &_err_alloc__tmp_til_U8_from_i64_29, _tmp_til_U8_from_i64_32, &_tmp_til_U8_from_i64_33);
        if (_arr_status__tmp_til_U8_from_i64_29 != 0) {
        }
        til_I64 _tmp_til_U8_from_i64_34 = 0;
        _arr_status__tmp_til_U8_from_i64_29 = til_Array_set(&_err_idx__tmp_til_U8_from_i64_29, &_tmp_til_U8_from_i64_28, &_tmp_til_U8_from_i64_34, (til_Dynamic*)&_tmp_til_U8_from_i64_30);
        if (_arr_status__tmp_til_U8_from_i64_29 != 0) {
        }
        til_I64 _tmp_til_U8_from_i64_35 = 1;
        _arr_status__tmp_til_U8_from_i64_29 = til_Array_set(&_err_idx__tmp_til_U8_from_i64_29, &_tmp_til_U8_from_i64_28, &_tmp_til_U8_from_i64_35, (til_Dynamic*)&_tmp_til_U8_from_i64_31);
        if (_arr_status__tmp_til_U8_from_i64_29 != 0) {
        }
        int _status__tmp_til_U8_from_i64_27 = til_format(&_tmp_til_U8_from_i64_26, &_err0__tmp_til_U8_from_i64_27, &_err1__tmp_til_U8_from_i64_27, &_err2__tmp_til_U8_from_i64_27, &((til_Str){(til_I64)"src/core/u8.til:53:47:", 22}), &_tmp_til_U8_from_i64_28);
        if (_status__tmp_til_U8_from_i64_27 != 0) {
        }
        til_Array_delete(&_tmp_til_U8_from_i64_28);
        *_err1 = (til_U8_OverflowError){.msg = _tmp_til_U8_from_i64_26};
        return 1;
    }
    *_ret = til_i64_to_u8(til_self);
    return 0;
}

til_CfVec2 til_CfVec2_magic(void) {
    return (til_CfVec2){.x = 42, .y = 99};
}

til_CfVec2 til_CfVec2_at(const til_I64* til_x, const til_I64* til_y) {
    return (til_CfVec2){.x = (*til_x), .y = (*til_y)};
}

til_CfRect til_CfRect_sample(void) {
    return (til_CfRect){.top_left = (til_CfVec2){.x = 5, .y = 10}, .bottom_right = (til_CfVec2){.x = 100, .y = 200}};
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
