#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char til_U8;
typedef long long til_I64;
typedef struct til_Bool { til_U8 data; } til_Bool;
typedef void* til_Dynamic;
typedef const char* til_Type;

typedef struct til_IndexOutOfBoundsError til_IndexOutOfBoundsError;
typedef struct til_BadAlloc til_BadAlloc;
typedef struct til_Array til_Array;
typedef struct til_Str til_Str;
typedef struct til_U8_OverflowError til_U8_OverflowError;
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

struct til_Str {
    til_I64 c_string;
    til_I64 cap;
};

struct til_U8_OverflowError {
    til_Str msg;
};

struct til_Array {
    til_Str type_name;
    til_I64 type_size;
    til_I64 ptr;
    til_I64 _len;
};

struct til_IndexOutOfBoundsError {
    til_Str msg;
};

struct til_BadAlloc {
};

til_Bool til_not(const til_Bool* til_b);
void til_panic(const til_Str* til_loc_str, const til_Str* til_msg, til_Array* til_extra_msgs);
void til_assertm(const til_Str* til_loc_str, const til_Bool* til_cond, const til_Str* til_msg);
void til_println(til_Array* til_args);
til_Str til_concat(const til_Str* til_a, const til_Str* til_b);
til_Str til_format(const til_Str* til_prefix, til_Array* til_args);
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
til_Array til_Array_new(til_Type til_T, const til_I64* til_capacity);
int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array* til_self, const til_I64* til_index, til_Dynamic* til_T);
int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64* til_index, const til_Dynamic* til_value);
void til_Array_delete(til_Array* til_self);
til_Bool til_I64_eq(const til_I64* til_a, const til_I64* til_b);
til_Str til_I64_to_str(const til_I64* til_self);
void til_I64_inc(til_I64* til_self);
void til_I64_dec(til_I64* til_self);
til_Bool til_I64_gteq(const til_I64* til_a, const til_I64* til_b);
til_I64 til_Str_len(const til_Str* til_self);
til_Bool til_Str_eq(const til_Str* til_self, const til_Str* til_other);
til_Bool til_Str_contains(const til_Str* til_self, const til_Str* til_needle);
til_Bool til_U8_eq(const til_U8* til_self, const til_U8* til_other);
til_I64 til_U8_to_i64(const til_U8* til_self);
int til_U8_from_i64(til_U8* _ret, til_U8_OverflowError* _err1, const til_I64* til_self);
til_CfVec2 til_CfVec2_magic(void);
til_CfVec2 til_CfVec2_at(const til_I64* til_x, const til_I64* til_y);
til_CfRect til_CfRect_sample(void);

#include <ext.c>

const til_I64 til_size_of_IndexOutOfBoundsError = sizeof(til_IndexOutOfBoundsError);
const til_I64 til_size_of_BadAlloc = sizeof(til_BadAlloc);
const til_I64 til_size_of_Array = sizeof(til_Array);
const til_I64 til_size_of_Bool = sizeof(til_Bool);
const til_I64 til_size_of_I64 = sizeof(til_I64);
const til_I64 til_size_of_Str = sizeof(til_Str);
const til_I64 til_size_of_U8_OverflowError = sizeof(til_U8_OverflowError);
const til_I64 til_size_of_U8 = sizeof(til_U8);
const til_I64 til_size_of_Dynamic = sizeof(til_Dynamic);
const til_I64 til_size_of_Type = sizeof(til_Type);
const til_I64 til_size_of_CfVec2 = sizeof(til_CfVec2);
const til_I64 til_size_of_CfRect = sizeof(til_CfRect);
const til_I64 til_NULL = 0;
const til_I64 til_I64_SIZE = 8;
const til_I64 til_MIN_I64 = -922337203;
const til_I64 til_MAX_I64 = 9223372036854775807;
const til_I64 til_U8_SIZE = 1;
const til_I64 til_MIN_U8 = 0;
const til_I64 til_MAX_U8 = 255;
const til_U8 til_ZERO_U8 = 0;

static inline til_I64 til_size_of(const til_Str* type_name) {
    if (strcmp((char*)type_name->c_string, "IndexOutOfBoundsError") == 0) return til_size_of_IndexOutOfBoundsError;
    if (strcmp((char*)type_name->c_string, "BadAlloc") == 0) return til_size_of_BadAlloc;
    if (strcmp((char*)type_name->c_string, "Array") == 0) return til_size_of_Array;
    if (strcmp((char*)type_name->c_string, "Bool") == 0) return til_size_of_Bool;
    if (strcmp((char*)type_name->c_string, "I64") == 0) return til_size_of_I64;
    if (strcmp((char*)type_name->c_string, "Str") == 0) return til_size_of_Str;
    if (strcmp((char*)type_name->c_string, "U8_OverflowError") == 0) return til_size_of_U8_OverflowError;
    if (strcmp((char*)type_name->c_string, "U8") == 0) return til_size_of_U8;
    if (strcmp((char*)type_name->c_string, "Dynamic") == 0) return til_size_of_Dynamic;
    if (strcmp((char*)type_name->c_string, "Type") == 0) return til_size_of_Type;
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

void til_panic(const til_Str* til_loc_str, const til_Str* til_msg, til_Array* til_extra_msgs) {
    til_single_print(til_loc_str);
    til_single_print(til_msg);
    til_I64 _for_i_panic_0 = 0;
    til_Str til_extra_msg;
    while (til_lt(&_for_i_panic_0, &(til_I64){til_Array_len(til_extra_msgs)}).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp_panic_0;
        til_extra_msg = (til_Str){.c_string = 0, .cap = 0};
        til_IndexOutOfBoundsError _err0__tmp_panic_1 = {};
        int _status__tmp_panic_1 = til_Array_get(&_err0__tmp_panic_1, til_extra_msgs, &_for_i_panic_0, (til_Dynamic*)&til_extra_msg);
        if (_status__tmp_panic_1 == 1) { _thrown_IndexOutOfBoundsError__tmp_panic_0 = _err0__tmp_panic_1; goto _catch_IndexOutOfBoundsError__tmp_panic_0; }
        if (0) { _catch_IndexOutOfBoundsError__tmp_panic_0:;
            til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp_panic_0;
            til_Array _tmp_panic_2;
            til_IndexOutOfBoundsError _err_idx__tmp_panic_3;
            til_Type _tmp_panic_4 = "Str";
            til_I64 _tmp_panic_5 = 0;
            _tmp_panic_2 = til_Array_new(_tmp_panic_4, &_tmp_panic_5);
            int _arr_status__tmp_panic_3;
            til_panic(&((til_Str){(til_I64)"src/core/exit.til:13:5:", 23}), &til_err.msg, &_tmp_panic_2);
            til_Array_delete(&_tmp_panic_2);
        }
        til_single_print(&til_extra_msg);
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
        til_Array _tmp_assertm_1;
        til_IndexOutOfBoundsError _err_idx__tmp_assertm_2;
        til_Str _tmp_assertm_3 = (*til_msg);
        til_Type _tmp_assertm_4 = "Str";
        til_I64 _tmp_assertm_5 = 1;
        _tmp_assertm_1 = til_Array_new(_tmp_assertm_4, &_tmp_assertm_5);
        int _arr_status__tmp_assertm_2;
        til_I64 _tmp_assertm_6 = 0;
        _arr_status__tmp_assertm_2 = til_Array_set(&_err_idx__tmp_assertm_2, &_tmp_assertm_1, &_tmp_assertm_6, (til_Dynamic*)&_tmp_assertm_3);
        if (_arr_status__tmp_assertm_2 != 0) {
        }
        _tmp_assertm_0 = til_format(&((til_Str){(til_I64)"assert failed: ", 15}), &_tmp_assertm_1);
        til_Array_delete(&_tmp_assertm_1);
        til_Array _tmp_assertm_7;
        til_IndexOutOfBoundsError _err_idx__tmp_assertm_8;
        til_Type _tmp_assertm_9 = "Str";
        til_I64 _tmp_assertm_10 = 0;
        _tmp_assertm_7 = til_Array_new(_tmp_assertm_9, &_tmp_assertm_10);
        int _arr_status__tmp_assertm_8;
        til_panic(til_loc_str, &_tmp_assertm_0, &_tmp_assertm_7);
        til_Array_delete(&_tmp_assertm_7);
    }
}

void til_println(til_Array* til_args) {
    til_I64 _for_i_println_0 = 0;
    til_Str til_print_arg;
    while (til_lt(&_for_i_println_0, &(til_I64){til_Array_len(til_args)}).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp_println_0;
        til_print_arg = (til_Str){.c_string = 0, .cap = 0};
        til_IndexOutOfBoundsError _err0__tmp_println_1 = {};
        int _status__tmp_println_1 = til_Array_get(&_err0__tmp_println_1, til_args, &_for_i_println_0, (til_Dynamic*)&til_print_arg);
        if (_status__tmp_println_1 == 1) { _thrown_IndexOutOfBoundsError__tmp_println_0 = _err0__tmp_println_1; goto _catch_IndexOutOfBoundsError__tmp_println_0; }
        if (0) { _catch_IndexOutOfBoundsError__tmp_println_0:;
            til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp_println_0;
            til_Array _tmp_println_2;
            til_IndexOutOfBoundsError _err_idx__tmp_println_3;
            til_Type _tmp_println_4 = "Str";
            til_I64 _tmp_println_5 = 0;
            _tmp_println_2 = til_Array_new(_tmp_println_4, &_tmp_println_5);
            int _arr_status__tmp_println_3;
            til_panic(&((til_Str){(til_I64)"src/core/print.til:16:5:", 24}), &til_err.msg, &_tmp_println_2);
            til_Array_delete(&_tmp_println_2);
        }
        til_single_print(&til_print_arg);
        _for_i_println_0 = til_add(&_for_i_println_0, &(til_I64){1});
    }
    til_single_print(&((til_Str){(til_I64)"\n", 1}));
    til_print_flush();
}

til_Str til_concat(const til_Str* til_a, const til_Str* til_b) {
    til_BadAlloc _thrown_BadAlloc__tmp_concat_0;
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_add(&til_a->cap, &til_b->cap);
    if (til_lt(&til_result.cap, &til_a->cap).data) {
        til_Array _tmp_concat_1;
        til_IndexOutOfBoundsError _err_idx__tmp_concat_2;
        til_Type _tmp_concat_3 = "Str";
        til_I64 _tmp_concat_4 = 0;
        _tmp_concat_1 = til_Array_new(_tmp_concat_3, &_tmp_concat_4);
        int _arr_status__tmp_concat_2;
        til_panic(&((til_Str){(til_I64)"src/core/str.til:554:15:", 24}), &((til_Str){(til_I64)"concat: integer overflow", 24}), &_tmp_concat_1);
        til_Array_delete(&_tmp_concat_1);
    }
    til_I64 _tmp_concat_6 = til_add(&til_result.cap, &(til_I64){1});
    til_I64 _ret__tmp_concat_5;
    til_BadAlloc _err0__tmp_concat_5 = {};
    int _status__tmp_concat_5 = til_malloc(&_ret__tmp_concat_5, &_err0__tmp_concat_5, &_tmp_concat_6);
    if (_status__tmp_concat_5 == 1) { _thrown_BadAlloc__tmp_concat_0 = _err0__tmp_concat_5; goto _catch_BadAlloc__tmp_concat_0; }
    til_result.c_string = _ret__tmp_concat_5;
    if (0) { _catch_BadAlloc__tmp_concat_0:;
        til_BadAlloc til_err = _thrown_BadAlloc__tmp_concat_0;
        til_Array _tmp_concat_7;
        til_IndexOutOfBoundsError _err_idx__tmp_concat_8;
        til_Type _tmp_concat_9 = "Str";
        til_I64 _tmp_concat_10 = 0;
        _tmp_concat_7 = til_Array_new(_tmp_concat_9, &_tmp_concat_10);
        int _arr_status__tmp_concat_8;
        til_panic(&((til_Str){(til_I64)"src/core/str.til:558:35:", 24}), &((til_Str){(til_I64)"concat: malloc failed", 21}), &_tmp_concat_7);
        til_Array_delete(&_tmp_concat_7);
    }
    til_memcpy(&til_result.c_string, &til_a->c_string, &til_a->cap);
    til_I64 _tmp_concat_11 = til_add(&til_result.c_string, &til_a->cap);
    til_memcpy(&_tmp_concat_11, &til_b->c_string, &til_b->cap);
    const til_U8 til_zero = 0;
    til_I64 _tmp_concat_12 = til_add(&til_result.c_string, &til_result.cap);
    til_I64 _tmp_concat_13 = 1;
    til_memset(&_tmp_concat_12, &til_zero, &_tmp_concat_13);
    return til_result;
}

til_Str til_format(const til_Str* til_prefix, til_Array* til_args) {
    til_BadAlloc _thrown_BadAlloc__tmp_format_0;
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp_format_1;
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_prefix->cap;
    til_I64 til_i = 0;
    til_Str til_arg;
    if (til_lt(&(til_I64){0}, &(til_I64){til_Array_len(til_args)}).data) {
        while (til_lt(&til_i, &(til_I64){til_Array_len(til_args)}).data) {
            til_arg = ((til_Str){(til_I64)"", 0});
            til_IndexOutOfBoundsError _err0__tmp_format_2 = {};
            int _status__tmp_format_2 = til_Array_get(&_err0__tmp_format_2, til_args, &til_i, (til_Dynamic*)&til_arg);
            til_result.cap = til_add(&til_result.cap, &til_arg.cap);
            if (til_lt(&til_result.cap, &til_arg.cap).data) {
                til_Array _tmp_format_3;
                til_IndexOutOfBoundsError _err_idx__tmp_format_4;
                til_Type _tmp_format_5 = "Str";
                til_I64 _tmp_format_6 = 0;
                _tmp_format_3 = til_Array_new(_tmp_format_5, &_tmp_format_6);
                int _arr_status__tmp_format_4;
                til_panic(&((til_Str){(til_I64)"src/core/str.til:579:19:", 24}), &((til_Str){(til_I64)"format: integer overflow while summing cap", 42}), &_tmp_format_3);
                til_Array_delete(&_tmp_format_3);
            }
            til_I64_inc(&til_i);
        }
    } else {
        while (til_gt(&til_i, &(til_I64){til_Array_len(til_args)}).data) {
            til_arg = ((til_Str){(til_I64)"", 0});
            til_IndexOutOfBoundsError _err0__tmp_format_7 = {};
            int _status__tmp_format_7 = til_Array_get(&_err0__tmp_format_7, til_args, &til_i, (til_Dynamic*)&til_arg);
            til_result.cap = til_add(&til_result.cap, &til_arg.cap);
            if (til_lt(&til_result.cap, &til_arg.cap).data) {
                til_Array _tmp_format_8;
                til_IndexOutOfBoundsError _err_idx__tmp_format_9;
                til_Type _tmp_format_10 = "Str";
                til_I64 _tmp_format_11 = 0;
                _tmp_format_8 = til_Array_new(_tmp_format_10, &_tmp_format_11);
                int _arr_status__tmp_format_9;
                til_panic(&((til_Str){(til_I64)"src/core/str.til:579:19:", 24}), &((til_Str){(til_I64)"format: integer overflow while summing cap", 42}), &_tmp_format_8);
                til_Array_delete(&_tmp_format_8);
            }
            til_I64_dec(&til_i);
        }
    }
    til_I64 _tmp_format_13 = til_add(&til_result.cap, &(til_I64){1});
    til_I64 _ret__tmp_format_12;
    til_BadAlloc _err0__tmp_format_12 = {};
    int _status__tmp_format_12 = til_malloc(&_ret__tmp_format_12, &_err0__tmp_format_12, &_tmp_format_13);
    if (_status__tmp_format_12 == 1) { _thrown_BadAlloc__tmp_format_0 = _err0__tmp_format_12; goto _catch_BadAlloc__tmp_format_0; }
    til_result.c_string = _ret__tmp_format_12;
    if (0) { _catch_BadAlloc__tmp_format_0:;
        til_BadAlloc til_err = _thrown_BadAlloc__tmp_format_0;
        til_Array _tmp_format_14;
        til_IndexOutOfBoundsError _err_idx__tmp_format_15;
        til_Type _tmp_format_16 = "Str";
        til_I64 _tmp_format_17 = 0;
        _tmp_format_14 = til_Array_new(_tmp_format_16, &_tmp_format_17);
        int _arr_status__tmp_format_15;
        til_panic(&((til_Str){(til_I64)"src/core/str.til:584:35:", 24}), &((til_Str){(til_I64)"format: malloc failed", 21}), &_tmp_format_14);
        til_Array_delete(&_tmp_format_14);
    }
    til_I64 til_offset = 0;
    til_memcpy(&til_result.c_string, &til_prefix->c_string, &til_prefix->cap);
    til_offset = til_prefix->cap;
    til_I64 _for_i_format_0 = 0;
    til_Str til_s;
    while (til_lt(&_for_i_format_0, &(til_I64){til_Array_len(til_args)}).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp_format_18;
        til_s = (til_Str){.c_string = 0, .cap = 0};
        til_IndexOutOfBoundsError _err0__tmp_format_19 = {};
        int _status__tmp_format_19 = til_Array_get(&_err0__tmp_format_19, til_args, &_for_i_format_0, (til_Dynamic*)&til_s);
        if (_status__tmp_format_19 == 1) { _thrown_IndexOutOfBoundsError__tmp_format_18 = _err0__tmp_format_19; goto _catch_IndexOutOfBoundsError__tmp_format_18; }
        if (0) { _catch_IndexOutOfBoundsError__tmp_format_18:;
            til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp_format_18;
            til_Array _tmp_format_20;
            til_IndexOutOfBoundsError _err_idx__tmp_format_21;
            til_Type _tmp_format_22 = "Str";
            til_I64 _tmp_format_23 = 0;
            _tmp_format_20 = til_Array_new(_tmp_format_22, &_tmp_format_23);
            int _arr_status__tmp_format_21;
            til_panic(&((til_Str){(til_I64)"src/core/str.til:590:5:", 23}), &til_err.msg, &_tmp_format_20);
            til_Array_delete(&_tmp_format_20);
        }
        til_I64 _tmp_format_24 = til_add(&til_result.c_string, &til_offset);
        til_memcpy(&_tmp_format_24, &til_s.c_string, &til_s.cap);
        til_offset = til_add(&til_offset, &til_s.cap);
        _for_i_format_0 = til_add(&_for_i_format_0, &(til_I64){1});
    }
    const til_U8 til_zero = 0;
    til_I64 _tmp_format_25 = til_add(&til_result.c_string, &til_result.cap);
    til_I64 _tmp_format_26 = 1;
    til_memset(&_tmp_format_25, &til_zero, &_tmp_format_26);
    if (0) { _catch_IndexOutOfBoundsError__tmp_format_1:;
        til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp_format_1;
        til_Array _tmp_format_27;
        til_IndexOutOfBoundsError _err_idx__tmp_format_28;
        til_Type _tmp_format_29 = "Str";
        til_I64 _tmp_format_30 = 0;
        _tmp_format_27 = til_Array_new(_tmp_format_29, &_tmp_format_30);
        int _arr_status__tmp_format_28;
        til_panic(&((til_Str){(til_I64)"src/core/str.til:600:15:", 24}), &til_err.msg, &_tmp_format_27);
        til_Array_delete(&_tmp_format_27);
    }
    return til_result;
}

void til_test(const til_Str* til_loc_str, const til_Bool* til_cond, const til_Str* til_msg) {
    til_assertm(til_loc_str, til_cond, til_msg);
}

void til_assert_eq(const til_Str* til_loc_str, const til_I64* til_a, const til_I64* til_b) {
    if (til_not(({ til_Bool _tmp_assert_eq_0 = til_I64_eq(til_a, til_b); &_tmp_assert_eq_0; })).data) {
        til_Array _tmp_assert_eq_1;
        til_IndexOutOfBoundsError _err_idx__tmp_assert_eq_2;
        til_Str _tmp_assert_eq_3 = (*til_loc_str);
        til_Str _tmp_assert_eq_4 = ((til_Str){(til_I64)"assert_eq failed: expected '", 28});
        til_Str _tmp_assert_eq_5 = til_I64_to_str(til_a);
        til_Str _tmp_assert_eq_6 = ((til_Str){(til_I64)"', found '", 10});
        til_Str _tmp_assert_eq_7 = til_I64_to_str(til_b);
        til_Str _tmp_assert_eq_8 = ((til_Str){(til_I64)"'", 1});
        til_Type _tmp_assert_eq_9 = "Str";
        til_I64 _tmp_assert_eq_10 = 6;
        _tmp_assert_eq_1 = til_Array_new(_tmp_assert_eq_9, &_tmp_assert_eq_10);
        int _arr_status__tmp_assert_eq_2;
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

til_Array til_Array_new(til_Type til_T, const til_I64* til_capacity) {
    til_BadAlloc _thrown_BadAlloc__tmp_til_Array_new_0;
    til_Array til_arr = {.type_name = ((til_Str){(til_I64)"", 0}), .type_size = 0, .ptr = 0, ._len = 0};
    til_arr.type_name = ((til_Str){(til_I64)til_T, strlen(til_T)});
    til_arr.type_size = til_size_of(&((til_Str){(til_I64)til_T, strlen(til_T)}));
    const til_I64 til_size_bytes = til_mul(til_capacity, &til_arr.type_size);
    til_I64 _ret__tmp_til_Array_new_1;
    til_BadAlloc _err0__tmp_til_Array_new_1 = {};
    int _status__tmp_til_Array_new_1 = til_malloc(&_ret__tmp_til_Array_new_1, &_err0__tmp_til_Array_new_1, &til_size_bytes);
    if (_status__tmp_til_Array_new_1 == 1) { _thrown_BadAlloc__tmp_til_Array_new_0 = _err0__tmp_til_Array_new_1; goto _catch_BadAlloc__tmp_til_Array_new_0; }
    til_arr.ptr = _ret__tmp_til_Array_new_1;
    if (0) { _catch_BadAlloc__tmp_til_Array_new_0:;
        til_BadAlloc til_err = _thrown_BadAlloc__tmp_til_Array_new_0;
        til_Array _tmp_til_Array_new_2;
        til_IndexOutOfBoundsError _err_idx__tmp_til_Array_new_3;
        til_Type _tmp_til_Array_new_4 = "Str";
        til_I64 _tmp_til_Array_new_5 = 0;
        _tmp_til_Array_new_2 = til_Array_new(_tmp_til_Array_new_4, &_tmp_til_Array_new_5);
        int _arr_status__tmp_til_Array_new_3;
        til_panic(&((til_Str){(til_I64)"src/core/array.til:33:39:", 25}), &((til_Str){(til_I64)"Array.new: malloc failed", 24}), &_tmp_til_Array_new_2);
        til_Array_delete(&_tmp_til_Array_new_2);
    }
    til_U8 _tmp_til_Array_new_6;
    til_U8_OverflowError _err0__tmp_til_Array_new_7;
    int _status__tmp_til_Array_new_7 = til_U8_from_i64(&_tmp_til_Array_new_6, &_err0__tmp_til_Array_new_7, &(til_I64){0});
    if (_status__tmp_til_Array_new_7 != 0) {
    }
    til_memset(&til_arr.ptr, &_tmp_til_Array_new_6, &til_size_bytes);
    til_arr._len = (*til_capacity);
    return til_arr;
}

int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array* til_self, const til_I64* til_index, til_Dynamic* til_T) {
    if (til_I64_gteq(til_index, &til_self->_len).data) {
        til_Str _tmp_til_Array_get_0;
        til_Array _tmp_til_Array_get_1;
        til_IndexOutOfBoundsError _err_idx__tmp_til_Array_get_2;
        til_Str _tmp_til_Array_get_3 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        til_Type _tmp_til_Array_get_4 = "Str";
        til_I64 _tmp_til_Array_get_5 = 1;
        _tmp_til_Array_get_1 = til_Array_new(_tmp_til_Array_get_4, &_tmp_til_Array_get_5);
        int _arr_status__tmp_til_Array_get_2;
        til_I64 _tmp_til_Array_get_6 = 0;
        _arr_status__tmp_til_Array_get_2 = til_Array_set(&_err_idx__tmp_til_Array_get_2, &_tmp_til_Array_get_1, &_tmp_til_Array_get_6, (til_Dynamic*)&_tmp_til_Array_get_3);
        if (_arr_status__tmp_til_Array_get_2 != 0) {
            *_err1 = _err_idx__tmp_til_Array_get_2; return 1;
        }
        _tmp_til_Array_get_0 = til_format(&((til_Str){(til_I64)"src/core/array.til:42:52:", 25}), &_tmp_til_Array_get_1);
        til_Array_delete(&_tmp_til_Array_get_1);
        til_Str _tmp_til_Array_get_7;
        til_Array _tmp_til_Array_get_8;
        til_IndexOutOfBoundsError _err_idx__tmp_til_Array_get_9;
        til_Str _tmp_til_Array_get_10 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        til_Type _tmp_til_Array_get_11 = "Str";
        til_I64 _tmp_til_Array_get_12 = 1;
        _tmp_til_Array_get_8 = til_Array_new(_tmp_til_Array_get_11, &_tmp_til_Array_get_12);
        int _arr_status__tmp_til_Array_get_9;
        til_I64 _tmp_til_Array_get_13 = 0;
        _arr_status__tmp_til_Array_get_9 = til_Array_set(&_err_idx__tmp_til_Array_get_9, &_tmp_til_Array_get_8, &_tmp_til_Array_get_13, (til_Dynamic*)&_tmp_til_Array_get_10);
        if (_arr_status__tmp_til_Array_get_9 != 0) {
            *_err1 = _err_idx__tmp_til_Array_get_9; return 1;
        }
        _tmp_til_Array_get_7 = til_format(&((til_Str){(til_I64)"src/core/array.til:42:52:", 25}), &_tmp_til_Array_get_8);
        til_Array_delete(&_tmp_til_Array_get_8);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_til_Array_get_7};
        return 1;
    }
    til_I64 _tmp_til_Array_get_14 = til_mul(til_index, &til_self->type_size);
    const til_I64 til_src = til_add(&til_self->ptr, &_tmp_til_Array_get_14);
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(&til_dest, &til_src, &til_self->type_size);
    return 0;
}

int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64* til_index, const til_Dynamic* til_value) {
    if (til_I64_gteq(til_index, &til_self->_len).data) {
        til_Str _tmp_til_Array_set_0;
        til_Array _tmp_til_Array_set_1;
        til_IndexOutOfBoundsError _err_idx__tmp_til_Array_set_2;
        til_Str _tmp_til_Array_set_3 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        til_Type _tmp_til_Array_set_4 = "Str";
        til_I64 _tmp_til_Array_set_5 = 1;
        _tmp_til_Array_set_1 = til_Array_new(_tmp_til_Array_set_4, &_tmp_til_Array_set_5);
        int _arr_status__tmp_til_Array_set_2;
        til_I64 _tmp_til_Array_set_6 = 0;
        _arr_status__tmp_til_Array_set_2 = til_Array_set(&_err_idx__tmp_til_Array_set_2, &_tmp_til_Array_set_1, &_tmp_til_Array_set_6, (til_Dynamic*)&_tmp_til_Array_set_3);
        if (_arr_status__tmp_til_Array_set_2 != 0) {
            *_err1 = _err_idx__tmp_til_Array_set_2; return 1;
        }
        _tmp_til_Array_set_0 = til_format(&((til_Str){(til_I64)"src/core/array.til:57:52:", 25}), &_tmp_til_Array_set_1);
        til_Array_delete(&_tmp_til_Array_set_1);
        til_Str _tmp_til_Array_set_7;
        til_Array _tmp_til_Array_set_8;
        til_IndexOutOfBoundsError _err_idx__tmp_til_Array_set_9;
        til_Str _tmp_til_Array_set_10 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        til_Type _tmp_til_Array_set_11 = "Str";
        til_I64 _tmp_til_Array_set_12 = 1;
        _tmp_til_Array_set_8 = til_Array_new(_tmp_til_Array_set_11, &_tmp_til_Array_set_12);
        int _arr_status__tmp_til_Array_set_9;
        til_I64 _tmp_til_Array_set_13 = 0;
        _arr_status__tmp_til_Array_set_9 = til_Array_set(&_err_idx__tmp_til_Array_set_9, &_tmp_til_Array_set_8, &_tmp_til_Array_set_13, (til_Dynamic*)&_tmp_til_Array_set_10);
        if (_arr_status__tmp_til_Array_set_9 != 0) {
            *_err1 = _err_idx__tmp_til_Array_set_9; return 1;
        }
        _tmp_til_Array_set_7 = til_format(&((til_Str){(til_I64)"src/core/array.til:57:52:", 25}), &_tmp_til_Array_set_8);
        til_Array_delete(&_tmp_til_Array_set_8);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_til_Array_set_7};
        return 1;
    }
    til_I64 _tmp_til_Array_set_14 = til_mul(til_index, &til_self->type_size);
    til_I64 til_dest = til_add(&til_self->ptr, &_tmp_til_Array_set_14);
    til_I64 _tmp_til_Array_set_15 = (til_I64)til_value;
    til_memcpy(&til_dest, &_tmp_til_Array_set_15, &til_self->type_size);
    return 0;
}

void til_Array_delete(til_Array* til_self) {
    til_free(&til_self->ptr);
    til_self->ptr = 0;
    til_self->_len = 0;
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

til_Bool til_U8_eq(const til_U8* til_self, const til_U8* til_other) {
    return til_I64_eq(&(til_I64){til_U8_to_i64(til_self)}, &(til_I64){til_U8_to_i64(til_other)});
}

til_I64 til_U8_to_i64(const til_U8* til_self) {
    return til_u8_to_i64(til_self);
}

int til_U8_from_i64(til_U8* _ret, til_U8_OverflowError* _err1, const til_I64* til_self) {
    if (til_lt(til_self, &(til_I64){0}).data) {
        til_Str _tmp_til_U8_from_i64_0;
        til_Array _tmp_til_U8_from_i64_1;
        til_IndexOutOfBoundsError _err_idx__tmp_til_U8_from_i64_2;
        til_Str _tmp_til_U8_from_i64_3 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        til_Type _tmp_til_U8_from_i64_4 = "Str";
        til_I64 _tmp_til_U8_from_i64_5 = 1;
        _tmp_til_U8_from_i64_1 = til_Array_new(_tmp_til_U8_from_i64_4, &_tmp_til_U8_from_i64_5);
        int _arr_status__tmp_til_U8_from_i64_2;
        til_I64 _tmp_til_U8_from_i64_6 = 0;
        _arr_status__tmp_til_U8_from_i64_2 = til_Array_set(&_err_idx__tmp_til_U8_from_i64_2, &_tmp_til_U8_from_i64_1, &_tmp_til_U8_from_i64_6, (til_Dynamic*)&_tmp_til_U8_from_i64_3);
        if (_arr_status__tmp_til_U8_from_i64_2 != 0) {
        }
        _tmp_til_U8_from_i64_0 = til_format(&((til_Str){(til_I64)"src/core/u8.til:51:47:", 22}), &_tmp_til_U8_from_i64_1);
        til_Array_delete(&_tmp_til_U8_from_i64_1);
        til_Str _tmp_til_U8_from_i64_7;
        til_Array _tmp_til_U8_from_i64_8;
        til_IndexOutOfBoundsError _err_idx__tmp_til_U8_from_i64_9;
        til_Str _tmp_til_U8_from_i64_10 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        til_Type _tmp_til_U8_from_i64_11 = "Str";
        til_I64 _tmp_til_U8_from_i64_12 = 1;
        _tmp_til_U8_from_i64_8 = til_Array_new(_tmp_til_U8_from_i64_11, &_tmp_til_U8_from_i64_12);
        int _arr_status__tmp_til_U8_from_i64_9;
        til_I64 _tmp_til_U8_from_i64_13 = 0;
        _arr_status__tmp_til_U8_from_i64_9 = til_Array_set(&_err_idx__tmp_til_U8_from_i64_9, &_tmp_til_U8_from_i64_8, &_tmp_til_U8_from_i64_13, (til_Dynamic*)&_tmp_til_U8_from_i64_10);
        if (_arr_status__tmp_til_U8_from_i64_9 != 0) {
        }
        _tmp_til_U8_from_i64_7 = til_format(&((til_Str){(til_I64)"src/core/u8.til:51:47:", 22}), &_tmp_til_U8_from_i64_8);
        til_Array_delete(&_tmp_til_U8_from_i64_8);
        *_err1 = (til_U8_OverflowError){.msg = _tmp_til_U8_from_i64_7};
        return 1;
    }
    if (til_gt(til_self, &til_MAX_U8).data) {
        til_Str _tmp_til_U8_from_i64_14;
        til_Array _tmp_til_U8_from_i64_15;
        til_IndexOutOfBoundsError _err_idx__tmp_til_U8_from_i64_16;
        til_Str _tmp_til_U8_from_i64_17 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp_til_U8_from_i64_18 = til_I64_to_str(&til_MAX_U8);
        til_Type _tmp_til_U8_from_i64_19 = "Str";
        til_I64 _tmp_til_U8_from_i64_20 = 2;
        _tmp_til_U8_from_i64_15 = til_Array_new(_tmp_til_U8_from_i64_19, &_tmp_til_U8_from_i64_20);
        int _arr_status__tmp_til_U8_from_i64_16;
        til_I64 _tmp_til_U8_from_i64_21 = 0;
        _arr_status__tmp_til_U8_from_i64_16 = til_Array_set(&_err_idx__tmp_til_U8_from_i64_16, &_tmp_til_U8_from_i64_15, &_tmp_til_U8_from_i64_21, (til_Dynamic*)&_tmp_til_U8_from_i64_17);
        if (_arr_status__tmp_til_U8_from_i64_16 != 0) {
        }
        til_I64 _tmp_til_U8_from_i64_22 = 1;
        _arr_status__tmp_til_U8_from_i64_16 = til_Array_set(&_err_idx__tmp_til_U8_from_i64_16, &_tmp_til_U8_from_i64_15, &_tmp_til_U8_from_i64_22, (til_Dynamic*)&_tmp_til_U8_from_i64_18);
        if (_arr_status__tmp_til_U8_from_i64_16 != 0) {
        }
        _tmp_til_U8_from_i64_14 = til_format(&((til_Str){(til_I64)"src/core/u8.til:54:47:", 22}), &_tmp_til_U8_from_i64_15);
        til_Array_delete(&_tmp_til_U8_from_i64_15);
        til_Str _tmp_til_U8_from_i64_23;
        til_Array _tmp_til_U8_from_i64_24;
        til_IndexOutOfBoundsError _err_idx__tmp_til_U8_from_i64_25;
        til_Str _tmp_til_U8_from_i64_26 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp_til_U8_from_i64_27 = til_I64_to_str(&til_MAX_U8);
        til_Type _tmp_til_U8_from_i64_28 = "Str";
        til_I64 _tmp_til_U8_from_i64_29 = 2;
        _tmp_til_U8_from_i64_24 = til_Array_new(_tmp_til_U8_from_i64_28, &_tmp_til_U8_from_i64_29);
        int _arr_status__tmp_til_U8_from_i64_25;
        til_I64 _tmp_til_U8_from_i64_30 = 0;
        _arr_status__tmp_til_U8_from_i64_25 = til_Array_set(&_err_idx__tmp_til_U8_from_i64_25, &_tmp_til_U8_from_i64_24, &_tmp_til_U8_from_i64_30, (til_Dynamic*)&_tmp_til_U8_from_i64_26);
        if (_arr_status__tmp_til_U8_from_i64_25 != 0) {
        }
        til_I64 _tmp_til_U8_from_i64_31 = 1;
        _arr_status__tmp_til_U8_from_i64_25 = til_Array_set(&_err_idx__tmp_til_U8_from_i64_25, &_tmp_til_U8_from_i64_24, &_tmp_til_U8_from_i64_31, (til_Dynamic*)&_tmp_til_U8_from_i64_27);
        if (_arr_status__tmp_til_U8_from_i64_25 != 0) {
        }
        _tmp_til_U8_from_i64_23 = til_format(&((til_Str){(til_I64)"src/core/u8.til:54:47:", 22}), &_tmp_til_U8_from_i64_24);
        til_Array_delete(&_tmp_til_U8_from_i64_24);
        *_err1 = (til_U8_OverflowError){.msg = _tmp_til_U8_from_i64_23};
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
