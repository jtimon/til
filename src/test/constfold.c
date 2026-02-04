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
typedef struct til_I64_Overflow til_I64_Overflow;
typedef struct til_DivideByZero til_DivideByZero;
typedef struct til_Ptr til_Ptr;
typedef struct til_Str til_Str;
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

struct til_Ptr {
    til_I64 data;
    til_I64 is_borrowed;
};

struct til_Str {
    til_Ptr c_string;
    til_I64 _len;
    til_I64 cap;
};

struct til_I64_Overflow {
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

struct til_DivideByZero {
};

struct til_BadAlloc {
};

til_Bool til_not(const til_Bool* til_Bool_b);
void til_panic(const til_Str* til_Str_loc_str, const til_Str* til_Str_msg, til_Array* til_Array_extra_msgs);
void til_assertm(const til_Str* til_Str_loc_str, const til_Bool* til_Bool_cond, const til_Str* til_Str_msg);
void til_println(til_Array* til_Array_args);
til_Str til_concat(const til_Str* til_Str_a, const til_Str* til_Str_b);
til_Str til_format(const til_Str* til_Str_prefix, til_Array* til_Array_args);
void til_test(const til_Str* til_Str_loc_str, const til_Bool* til_Bool_cond, const til_Str* til_Str_msg);
void til_assert_eq(const til_Str* til_Str_loc_str, const til_I64* til_I64_a, const til_I64* til_I64_b);
void til_test_simple_add(void);
void til_test_nested_arithmetic(void);
void til_test_deeply_nested(void);
void til_test_string_concat(void);
void til_test_fold_variable(void);
void til_test_loc_folded_correctly(void);
void til_test_struct_fold_simple(void);
void til_test_struct_fold_values(void);
void til_test_struct_fold_nested(void);
til_Ptr til_Ptr_new_by_size(const til_I64* til_I64_size);
void til_Ptr_delete(til_Ptr* til_Ptr_self);
til_Ptr til_Ptr_offset(const til_Ptr* til_Ptr_self, const til_I64* til_I64_offset);
void til_Ptr_copy_from(til_Ptr* til_Ptr_self, const til_Ptr* til_Ptr_src, const til_I64* til_I64_size);
til_I64 til_Str_len(const til_Str* til_Str_self);
til_Bool til_Str_eq(const til_Str* til_Str_self, const til_Str* til_Str_other);
til_Str til_Str_clone(const til_Str* til_Str_self);
void til_Str_delete(til_Str* til_Str_self);
til_Bool til_Str_contains(const til_Str* til_Str_self, const til_Str* til_Str_needle);
til_Bool til_U8_lt(const til_U8* til_U8_self, const til_U8* til_U8_other);
til_Bool til_U8_gt(const til_U8* til_U8_self, const til_U8* til_U8_other);
til_Bool til_U8_eq(const til_U8* til_U8_a, const til_U8* til_U8_b);
til_CfVec2 til_CfVec2_magic(void);
til_CfVec2 til_CfVec2_at(const til_I64* til_I64_x, const til_I64* til_I64_y);
til_CfRect til_CfRect_sample(void);
void til_IndexOutOfBoundsError_delete(til_IndexOutOfBoundsError* til_IndexOutOfBoundsError_self);
til_IndexOutOfBoundsError til_IndexOutOfBoundsError_clone(const til_IndexOutOfBoundsError* til_IndexOutOfBoundsError_self);
til_I64 til_Array_len(const til_Array* til_Array_self);
til_I64 til_Array_size(const til_Array* til_Array_self);
til_Array til_Array_new(til_Type til_Type_T, const til_I64* til_I64_capacity);
int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array* til_Array_self, const til_I64* til_I64_index, til_Dynamic* til_Dynamic_T);
int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_Array_self, const til_I64* til_I64_index, const til_Dynamic* til_Dynamic_value);
void til_Array_delete(til_Array* til_Array_self);
til_Array til_Array_clone(const til_Array* til_Array_self);
til_Bool til_Array_contains(const til_Array* til_Array_self, const til_Str* til_Str_value);
til_I64 til_Bool_len(const til_Bool* _self);
til_Bool til_Bool_eq(const til_Bool* til_Bool_a, const til_Bool* til_Bool_b);
til_Bool til_Bool_and(const til_Bool* til_Bool_self, const til_Bool* til_Bool_other);
til_Bool til_Bool_or(const til_Bool* til_Bool_self, const til_Bool* til_Bool_other);
til_Str til_Bool_to_str(const til_Bool* til_Bool_self);
til_I64 til_Bool_to_i64(const til_Bool* til_Bool_self);
til_U8 til_Bool_to_u8(const til_Bool* til_Bool_self);
til_Bool til_Bool_from_i64(const til_I64* til_I64_i);
til_I64 til_Bool_size(void);
void til_Bool_delete(til_Bool* _self);
til_Bool til_Bool_clone(const til_Bool* til_Bool_self);
int til_I64_safe_div(til_I64* _ret, const til_I64* til_I64_a, const til_I64* til_I64_b);
int til_I64_safe_add(til_I64* _ret, til_I64_Overflow* _err1, const til_I64* til_I64_a, const til_I64* til_I64_b);
int til_I64_safe_sub(til_I64* _ret, til_I64_Overflow* _err1, const til_I64* til_I64_a, const til_I64* til_I64_b);
int til_I64_safe_mul(til_I64* _ret, til_I64_Overflow* _err1, const til_I64* til_I64_a, const til_I64* til_I64_b);
til_I64 til_I64_xor(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_I64 til_I64_and(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_I64 til_I64_or(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_I64 til_I64_mod(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_I64 til_I64_sub(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_I64 til_I64_mul(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_I64 til_I64_div(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_I64 til_I64_add(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_Bool til_I64_eq(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_Bool til_I64_lt(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_Bool til_I64_gt(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_Str til_I64_to_str(const til_I64* til_I64_self);
til_I64 til_I64_from_str(const til_Str* til_Str_str);
void til_I64_inc(til_I64* til_I64_self);
void til_I64_dec(til_I64* til_I64_self);
til_Bool til_I64_gteq(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_Bool til_I64_lteq(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_I64 til_I64_size(void);
void til_I64_delete(til_I64* _self);
til_I64 til_I64_clone(const til_I64* til_I64_self);
til_I64 til_Ptr_size_of(void);
til_Bool til_Ptr_is_null(const til_Ptr* til_Ptr_self);
void til_CfVec2_delete(til_CfVec2* _self);
til_CfVec2 til_CfVec2_clone(const til_CfVec2* til_CfVec2_self);
void til_CfRect_delete(til_CfRect* til_CfRect_self);
til_CfRect til_CfRect_clone(const til_CfRect* til_CfRect_self);

#include <ext.c>

const til_I64 til_size_of_IndexOutOfBoundsError = sizeof(til_IndexOutOfBoundsError);
const til_I64 til_size_of_BadAlloc = sizeof(til_BadAlloc);
const til_I64 til_size_of_Array = sizeof(til_Array);
const til_I64 til_size_of_Bool = sizeof(til_Bool);
const til_I64 til_size_of_I64_Overflow = sizeof(til_I64_Overflow);
const til_I64 til_size_of_DivideByZero = sizeof(til_DivideByZero);
const til_I64 til_size_of_I64 = sizeof(til_I64);
const til_I64 til_size_of_Ptr = sizeof(til_Ptr);
const til_I64 til_size_of_Str = sizeof(til_Str);
const til_I64 til_size_of_U8 = sizeof(til_U8);
const til_I64 til_size_of_Dynamic = sizeof(til_Dynamic);
const til_I64 til_size_of_Type = sizeof(til_Type);
const til_I64 til_size_of_CfVec2 = sizeof(til_CfVec2);
const til_I64 til_size_of_CfRect = sizeof(til_CfRect);
const til_I64 til_I64_NULL = 0;
const til_I64 til_I64_I64_SIZE = 8;
const til_I64 til_I64_MIN_I64 = -922337203;
const til_I64 til_I64_MAX_I64 = 9223372036854775807;
const til_I64 til_I64_U8_SIZE = 1;
const til_I64 til_I64_MIN_U8 = 0;
const til_I64 til_I64_MAX_U8 = 255;
const til_U8 til_U8_ZERO_U8 = 0;

static inline til_I64 til_size_of(const til_Str* type_name) {
    if (strcmp((char*)type_name->c_string.data, "IndexOutOfBoundsError") == 0) return til_size_of_IndexOutOfBoundsError;
    if (strcmp((char*)type_name->c_string.data, "BadAlloc") == 0) return til_size_of_BadAlloc;
    if (strcmp((char*)type_name->c_string.data, "Array") == 0) return til_size_of_Array;
    if (strcmp((char*)type_name->c_string.data, "Bool") == 0) return til_size_of_Bool;
    if (strcmp((char*)type_name->c_string.data, "I64_Overflow") == 0) return til_size_of_I64_Overflow;
    if (strcmp((char*)type_name->c_string.data, "DivideByZero") == 0) return til_size_of_DivideByZero;
    if (strcmp((char*)type_name->c_string.data, "I64") == 0) return til_size_of_I64;
    if (strcmp((char*)type_name->c_string.data, "Ptr") == 0) return til_size_of_Ptr;
    if (strcmp((char*)type_name->c_string.data, "Str") == 0) return til_size_of_Str;
    if (strcmp((char*)type_name->c_string.data, "U8") == 0) return til_size_of_U8;
    if (strcmp((char*)type_name->c_string.data, "Dynamic") == 0) return til_size_of_Dynamic;
    if (strcmp((char*)type_name->c_string.data, "Type") == 0) return til_size_of_Type;
    if (strcmp((char*)type_name->c_string.data, "CfVec2") == 0) return til_size_of_CfVec2;
    if (strcmp((char*)type_name->c_string.data, "CfRect") == 0) return til_size_of_CfRect;
    fprintf(stderr, "size_of: unknown type %s\n", (char*)type_name->c_string.data);
    exit(1);
}

til_Bool til_not(const til_Bool* til_Bool_b) {
    if ((*til_Bool_b).data) {
        return false;
    }
    return true;
    return (til_Bool){0};
}

void til_panic(const til_Str* til_Str_loc_str, const til_Str* til_Str_msg, til_Array* til_Array_extra_msgs) {
    til_single_print(til_Str_loc_str);
    til_single_print(til_Str_msg);
    til_I64 _for_i_panic_0 = 0;
    til_Str til_Str_extra_msg;
    while (1) {
        til_I64 _tmp_panic_0 = til_Array_len(til_Array_extra_msgs);
        if (!(til_I64_lt(&_for_i_panic_0, &_tmp_panic_0).data)) break;
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp_panic_1;
        til_Ptr _tmp_panic_2 = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0};
        til_Str_extra_msg = (til_Str){.c_string = _tmp_panic_2, ._len = 0, .cap = 0};
        til_IndexOutOfBoundsError _err0__tmp_panic_3 = {};
        int __attribute__((unused)) _status__tmp_panic_3 = til_Array_get(&_err0__tmp_panic_3, til_Array_extra_msgs, &_for_i_panic_0, (til_Dynamic*)&til_Str_extra_msg);
        if (_status__tmp_panic_3 == 1) { _thrown_IndexOutOfBoundsError__tmp_panic_1 = _err0__tmp_panic_3; goto _catch_IndexOutOfBoundsError__tmp_panic_1; }
        if (0) { _catch_IndexOutOfBoundsError__tmp_panic_1:;
            til_IndexOutOfBoundsError _err_forin_0 = _thrown_IndexOutOfBoundsError__tmp_panic_1;
            til_Array _tmp_panic_4;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_panic_5;
            til_Type _tmp_panic_6 = "Str";
            til_I64 _tmp_panic_7 = 0;
            _tmp_panic_4 = til_Array_new(_tmp_panic_6, &_tmp_panic_7);
            int __attribute__((unused)) _arr_status__tmp_panic_5;
            til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/exit.til:13:5:", 1}), 23, 0}), &_err_forin_0.msg, &_tmp_panic_4);
            til_Array_delete(&_tmp_panic_4);
        }
        til_single_print(&til_Str_extra_msg);
        til_I64 _tmp_panic_8 = 1;
        _for_i_panic_0 = til_I64_add(&_for_i_panic_0, &_tmp_panic_8);
    }
    til_single_print(&((til_Str){((til_Ptr){(til_I64)"\n", 1}), 1, 0}));
    til_print_flush();
    til_I64 _tmp_panic_9 = 1;
    til_exit(&_tmp_panic_9);
}

void til_assertm(const til_Str* til_Str_loc_str, const til_Bool* til_Bool_cond, const til_Str* til_Str_msg) {
    if (til_not(til_Bool_cond).data) {
        til_Str _tmp_assertm_0;
        til_Array _tmp_assertm_1;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_assertm_2;
        til_Str _tmp_assertm_3 = (*til_Str_msg);
        til_Type _tmp_assertm_4 = "Str";
        til_I64 _tmp_assertm_5 = 1;
        _tmp_assertm_1 = til_Array_new(_tmp_assertm_4, &_tmp_assertm_5);
        int __attribute__((unused)) _arr_status__tmp_assertm_2;
        til_I64 _tmp_assertm_6 = 0;
        _arr_status__tmp_assertm_2 = til_Array_set(&_err_idx__tmp_assertm_2, &_tmp_assertm_1, &_tmp_assertm_6, (til_Dynamic*)&_tmp_assertm_3);
        _tmp_assertm_0 = til_format(&((til_Str){((til_Ptr){(til_I64)"assert failed: ", 1}), 15, 0}), &_tmp_assertm_1);
        til_Array_delete(&_tmp_assertm_1);
        til_Array _tmp_assertm_7;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_assertm_8;
        til_Type _tmp_assertm_9 = "Str";
        til_I64 _tmp_assertm_10 = 0;
        _tmp_assertm_7 = til_Array_new(_tmp_assertm_9, &_tmp_assertm_10);
        int __attribute__((unused)) _arr_status__tmp_assertm_8;
        til_panic(til_Str_loc_str, &_tmp_assertm_0, &_tmp_assertm_7);
        til_Array_delete(&_tmp_assertm_7);
    }
}

void til_println(til_Array* til_Array_args) {
    til_I64 _for_i_println_0 = 0;
    til_Str til_Str_print_arg;
    while (1) {
        til_I64 _tmp_println_0 = til_Array_len(til_Array_args);
        if (!(til_I64_lt(&_for_i_println_0, &_tmp_println_0).data)) break;
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp_println_1;
        til_Ptr _tmp_println_2 = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0};
        til_Str_print_arg = (til_Str){.c_string = _tmp_println_2, ._len = 0, .cap = 0};
        til_IndexOutOfBoundsError _err0__tmp_println_3 = {};
        int __attribute__((unused)) _status__tmp_println_3 = til_Array_get(&_err0__tmp_println_3, til_Array_args, &_for_i_println_0, (til_Dynamic*)&til_Str_print_arg);
        if (_status__tmp_println_3 == 1) { _thrown_IndexOutOfBoundsError__tmp_println_1 = _err0__tmp_println_3; goto _catch_IndexOutOfBoundsError__tmp_println_1; }
        if (0) { _catch_IndexOutOfBoundsError__tmp_println_1:;
            til_IndexOutOfBoundsError _err_forin_0 = _thrown_IndexOutOfBoundsError__tmp_println_1;
            til_Array _tmp_println_4;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_println_5;
            til_Type _tmp_println_6 = "Str";
            til_I64 _tmp_println_7 = 0;
            _tmp_println_4 = til_Array_new(_tmp_println_6, &_tmp_println_7);
            int __attribute__((unused)) _arr_status__tmp_println_5;
            til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/print.til:16:5:", 1}), 24, 0}), &_err_forin_0.msg, &_tmp_println_4);
            til_Array_delete(&_tmp_println_4);
        }
        til_single_print(&til_Str_print_arg);
        til_I64 _tmp_println_8 = 1;
        _for_i_println_0 = til_I64_add(&_for_i_println_0, &_tmp_println_8);
    }
    til_single_print(&((til_Str){((til_Ptr){(til_I64)"\n", 1}), 1, 0}));
    til_print_flush();
}

til_Str til_concat(const til_Str* til_Str_a, const til_Str* til_Str_b) {
    til_Ptr _tmp_concat_0 = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0};
    til_Str til_Str_result = {.c_string = _tmp_concat_0, ._len = 0, .cap = 0};
    til_Str_result._len = til_I64_add(&til_Str_a->_len, &til_Str_b->_len);
    if (til_I64_lt(&til_Str_result._len, &til_Str_a->_len).data) {
        til_Array _tmp_concat_1;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_concat_2;
        til_Type _tmp_concat_3 = "Str";
        til_I64 _tmp_concat_4 = 0;
        _tmp_concat_1 = til_Array_new(_tmp_concat_3, &_tmp_concat_4);
        int __attribute__((unused)) _arr_status__tmp_concat_2;
        til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/str.til:664:15:", 1}), 24, 0}), &((til_Str){((til_Ptr){(til_I64)"concat: integer overflow", 1}), 24, 0}), &_tmp_concat_1);
        til_Array_delete(&_tmp_concat_1);
    }
    til_I64 _tmp_concat_5 = 1;
    til_Str_result.cap = til_I64_add(&til_Str_result._len, &_tmp_concat_5);
    til_Str_result.c_string = til_Ptr_new_by_size(&til_Str_result.cap);
    til_Str_result.c_string.is_borrowed = 0;
    til_memcpy(&til_Str_result.c_string.data, &til_Str_a->c_string.data, &til_Str_a->_len);
    til_I64 _tmp_concat_6 = til_Ptr_offset(&til_Str_result.c_string, &til_Str_a->_len).data;
    til_memcpy(&_tmp_concat_6, &til_Str_b->c_string.data, &til_Str_b->_len);
    const til_U8 til_U8_zero = 0;
    til_I64 _tmp_concat_7 = til_Ptr_offset(&til_Str_result.c_string, &til_Str_result._len).data;
    til_I64 _tmp_concat_8 = 1;
    til_memset(&_tmp_concat_7, &til_U8_zero, &_tmp_concat_8);
    return til_Str_result;
    return (til_Str){0};
}

til_Str til_format(const til_Str* til_Str_prefix, til_Array* til_Array_args) {
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp_format_0;
    til_Ptr _tmp_format_1 = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0};
    til_Str til_Str_result = {.c_string = _tmp_format_1, ._len = 0, .cap = 0};
    til_Str_result._len = til_Str_prefix->_len;
    til_I64 til_I64_i = 0;
    til_Str til_Str_arg;
    til_I64 _tmp_format_2 = 0;
    til_I64 _tmp_format_3 = til_Array_len(til_Array_args);
    if (til_I64_lt(&_tmp_format_2, &_tmp_format_3).data) {
        while (1) {
            til_I64 _tmp_format_4 = til_Array_len(til_Array_args);
            if (!(til_I64_lt(&til_I64_i, &_tmp_format_4).data)) break;
            til_Str_arg = ((til_Str){((til_Ptr){(til_I64)"", 1}), 0, 0});
            til_IndexOutOfBoundsError _err0__tmp_format_5 = {};
            int __attribute__((unused)) _status__tmp_format_5 = til_Array_get(&_err0__tmp_format_5, til_Array_args, &til_I64_i, (til_Dynamic*)&til_Str_arg);
            til_Str_result._len = til_I64_add(&til_Str_result._len, &til_Str_arg._len);
            if (til_I64_lt(&til_Str_result._len, &til_Str_arg._len).data) {
                til_Array _tmp_format_6;
                til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_format_7;
                til_Type _tmp_format_8 = "Str";
                til_I64 _tmp_format_9 = 0;
                _tmp_format_6 = til_Array_new(_tmp_format_8, &_tmp_format_9);
                int __attribute__((unused)) _arr_status__tmp_format_7;
                til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/str.til:690:19:", 1}), 24, 0}), &((til_Str){((til_Ptr){(til_I64)"format: integer overflow while summing cap", 1}), 42, 0}), &_tmp_format_6);
                til_Array_delete(&_tmp_format_6);
            }
            til_I64_inc(&til_I64_i);
        }
    } else {
        while (1) {
            til_I64 _tmp_format_10 = til_Array_len(til_Array_args);
            if (!(til_I64_gt(&til_I64_i, &_tmp_format_10).data)) break;
            til_Str_arg = ((til_Str){((til_Ptr){(til_I64)"", 1}), 0, 0});
            til_IndexOutOfBoundsError _err0__tmp_format_11 = {};
            int __attribute__((unused)) _status__tmp_format_11 = til_Array_get(&_err0__tmp_format_11, til_Array_args, &til_I64_i, (til_Dynamic*)&til_Str_arg);
            til_Str_result._len = til_I64_add(&til_Str_result._len, &til_Str_arg._len);
            if (til_I64_lt(&til_Str_result._len, &til_Str_arg._len).data) {
                til_Array _tmp_format_12;
                til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_format_13;
                til_Type _tmp_format_14 = "Str";
                til_I64 _tmp_format_15 = 0;
                _tmp_format_12 = til_Array_new(_tmp_format_14, &_tmp_format_15);
                int __attribute__((unused)) _arr_status__tmp_format_13;
                til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/str.til:690:19:", 1}), 24, 0}), &((til_Str){((til_Ptr){(til_I64)"format: integer overflow while summing cap", 1}), 42, 0}), &_tmp_format_12);
                til_Array_delete(&_tmp_format_12);
            }
            til_I64_dec(&til_I64_i);
        }
    }
    til_I64 _tmp_format_16 = 1;
    til_Str_result.cap = til_I64_add(&til_Str_result._len, &_tmp_format_16);
    til_Str_result.c_string = til_Ptr_new_by_size(&til_Str_result.cap);
    til_Str_result.c_string.is_borrowed = 0;
    til_I64 til_I64_fmt_offset = 0;
    til_memcpy(&til_Str_result.c_string.data, &til_Str_prefix->c_string.data, &til_Str_prefix->_len);
    til_I64_fmt_offset = til_Str_prefix->_len;
    til_I64 _for_i_format_0 = 0;
    til_Str til_Str_s;
    while (1) {
        til_I64 _tmp_format_17 = til_Array_len(til_Array_args);
        if (!(til_I64_lt(&_for_i_format_0, &_tmp_format_17).data)) break;
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp_format_18;
        til_Ptr _tmp_format_19 = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0};
        til_Str_s = (til_Str){.c_string = _tmp_format_19, ._len = 0, .cap = 0};
        til_IndexOutOfBoundsError _err0__tmp_format_20 = {};
        int __attribute__((unused)) _status__tmp_format_20 = til_Array_get(&_err0__tmp_format_20, til_Array_args, &_for_i_format_0, (til_Dynamic*)&til_Str_s);
        if (_status__tmp_format_20 == 1) { _thrown_IndexOutOfBoundsError__tmp_format_18 = _err0__tmp_format_20; goto _catch_IndexOutOfBoundsError__tmp_format_18; }
        if (0) { _catch_IndexOutOfBoundsError__tmp_format_18:;
            til_IndexOutOfBoundsError _err_forin_0 = _thrown_IndexOutOfBoundsError__tmp_format_18;
            til_Array _tmp_format_21;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_format_22;
            til_Type _tmp_format_23 = "Str";
            til_I64 _tmp_format_24 = 0;
            _tmp_format_21 = til_Array_new(_tmp_format_23, &_tmp_format_24);
            int __attribute__((unused)) _arr_status__tmp_format_22;
            til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/str.til:702:5:", 1}), 23, 0}), &_err_forin_0.msg, &_tmp_format_21);
            til_Array_delete(&_tmp_format_21);
        }
        til_I64 _tmp_format_25 = til_Ptr_offset(&til_Str_result.c_string, &til_I64_fmt_offset).data;
        til_memcpy(&_tmp_format_25, &til_Str_s.c_string.data, &til_Str_s._len);
        til_I64_fmt_offset = til_I64_add(&til_I64_fmt_offset, &til_Str_s._len);
        til_I64 _tmp_format_26 = 1;
        _for_i_format_0 = til_I64_add(&_for_i_format_0, &_tmp_format_26);
    }
    const til_U8 til_U8_zero = 0;
    til_I64 _tmp_format_27 = til_Ptr_offset(&til_Str_result.c_string, &til_Str_result._len).data;
    til_I64 _tmp_format_28 = 1;
    til_memset(&_tmp_format_27, &til_U8_zero, &_tmp_format_28);
    if (0) { _catch_IndexOutOfBoundsError__tmp_format_0:;
        til_IndexOutOfBoundsError til_IndexOutOfBoundsError_err = _thrown_IndexOutOfBoundsError__tmp_format_0;
        til_Array _tmp_format_29;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_format_30;
        til_Type _tmp_format_31 = "Str";
        til_I64 _tmp_format_32 = 0;
        _tmp_format_29 = til_Array_new(_tmp_format_31, &_tmp_format_32);
        int __attribute__((unused)) _arr_status__tmp_format_30;
        til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/str.til:712:15:", 1}), 24, 0}), &til_IndexOutOfBoundsError_err.msg, &_tmp_format_29);
        til_Array_delete(&_tmp_format_29);
    }
    return til_Str_result;
    return (til_Str){0};
}

void til_test(const til_Str* til_Str_loc_str, const til_Bool* til_Bool_cond, const til_Str* til_Str_msg) {
    til_assertm(til_Str_loc_str, til_Bool_cond, til_Str_msg);
}

void til_assert_eq(const til_Str* til_Str_loc_str, const til_I64* til_I64_a, const til_I64* til_I64_b) {
    til_Bool _tmp_assert_eq_0 = til_I64_eq(til_I64_a, til_I64_b);
    if (til_not(&_tmp_assert_eq_0).data) {
        til_Array _tmp_assert_eq_1;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_assert_eq_2;
        til_Str _tmp_assert_eq_3 = (*til_Str_loc_str);
        til_Str _tmp_assert_eq_4 = ((til_Str){((til_Ptr){(til_I64)"assert_eq failed: expected '", 1}), 28, 0});
        til_Str _tmp_assert_eq_5 = til_I64_to_str(til_I64_a);
        til_Str _tmp_assert_eq_6 = ((til_Str){((til_Ptr){(til_I64)"', found '", 1}), 10, 0});
        til_Str _tmp_assert_eq_7 = til_I64_to_str(til_I64_b);
        til_Str _tmp_assert_eq_8 = ((til_Str){((til_Ptr){(til_I64)"'", 1}), 1, 0});
        til_Type _tmp_assert_eq_9 = "Str";
        til_I64 _tmp_assert_eq_10 = 6;
        _tmp_assert_eq_1 = til_Array_new(_tmp_assert_eq_9, &_tmp_assert_eq_10);
        int __attribute__((unused)) _arr_status__tmp_assert_eq_2;
        til_I64 _tmp_assert_eq_11 = 0;
        _arr_status__tmp_assert_eq_2 = til_Array_set(&_err_idx__tmp_assert_eq_2, &_tmp_assert_eq_1, &_tmp_assert_eq_11, (til_Dynamic*)&_tmp_assert_eq_3);
        til_I64 _tmp_assert_eq_12 = 1;
        _arr_status__tmp_assert_eq_2 = til_Array_set(&_err_idx__tmp_assert_eq_2, &_tmp_assert_eq_1, &_tmp_assert_eq_12, (til_Dynamic*)&_tmp_assert_eq_4);
        til_I64 _tmp_assert_eq_13 = 2;
        _arr_status__tmp_assert_eq_2 = til_Array_set(&_err_idx__tmp_assert_eq_2, &_tmp_assert_eq_1, &_tmp_assert_eq_13, (til_Dynamic*)&_tmp_assert_eq_5);
        til_I64 _tmp_assert_eq_14 = 3;
        _arr_status__tmp_assert_eq_2 = til_Array_set(&_err_idx__tmp_assert_eq_2, &_tmp_assert_eq_1, &_tmp_assert_eq_14, (til_Dynamic*)&_tmp_assert_eq_6);
        til_I64 _tmp_assert_eq_15 = 4;
        _arr_status__tmp_assert_eq_2 = til_Array_set(&_err_idx__tmp_assert_eq_2, &_tmp_assert_eq_1, &_tmp_assert_eq_15, (til_Dynamic*)&_tmp_assert_eq_7);
        til_I64 _tmp_assert_eq_16 = 5;
        _arr_status__tmp_assert_eq_2 = til_Array_set(&_err_idx__tmp_assert_eq_2, &_tmp_assert_eq_1, &_tmp_assert_eq_16, (til_Dynamic*)&_tmp_assert_eq_8);
        til_println(&_tmp_assert_eq_1);
        til_Array_delete(&_tmp_assert_eq_1);
        til_I64 _tmp_assert_eq_17 = 1;
        til_exit(&_tmp_assert_eq_17);
    }
}

void til_test_simple_add(void) {
    til_I64 _tmp_test_simple_add_0 = 1;
    til_I64 _tmp_test_simple_add_1 = 2;
    const til_I64 til_I64_result = til_I64_add(&_tmp_test_simple_add_0, &_tmp_test_simple_add_1);
    til_I64 _tmp_test_simple_add_2 = 3;
    til_Bool _tmp_test_simple_add_3 = til_I64_eq(&til_I64_result, &_tmp_test_simple_add_2);
    til_test(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:8:10:", 1}), 28, 0}), &_tmp_test_simple_add_3, &((til_Str){((til_Ptr){(til_I64)"add(1, 2) should be 3", 1}), 21, 0}));
}

void til_test_nested_arithmetic(void) {
    til_I64 _tmp_test_nested_arithmetic_0 = 1;
    til_I64 _tmp_test_nested_arithmetic_1 = 2;
    til_I64 _tmp_test_nested_arithmetic_2 = til_I64_add(&_tmp_test_nested_arithmetic_0, &_tmp_test_nested_arithmetic_1);
    til_I64 _tmp_test_nested_arithmetic_3 = 10;
    til_I64 _tmp_test_nested_arithmetic_4 = 5;
    til_I64 _tmp_test_nested_arithmetic_5 = til_I64_sub(&_tmp_test_nested_arithmetic_3, &_tmp_test_nested_arithmetic_4);
    const til_I64 til_I64_result = til_I64_mul(&_tmp_test_nested_arithmetic_2, &_tmp_test_nested_arithmetic_5);
    til_I64 _tmp_test_nested_arithmetic_6 = 15;
    til_Bool _tmp_test_nested_arithmetic_7 = til_I64_eq(&til_I64_result, &_tmp_test_nested_arithmetic_6);
    til_test(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:15:10:", 1}), 29, 0}), &_tmp_test_nested_arithmetic_7, &((til_Str){((til_Ptr){(til_I64)"mul(add(1, 2), sub(10, 5)) should be 15", 1}), 39, 0}));
}

void til_test_deeply_nested(void) {
    til_I64 _tmp_test_deeply_nested_0 = 2;
    til_I64 _tmp_test_deeply_nested_1 = 3;
    til_I64 _tmp_test_deeply_nested_2 = til_I64_mul(&_tmp_test_deeply_nested_0, &_tmp_test_deeply_nested_1);
    til_I64 _tmp_test_deeply_nested_3 = 4;
    til_I64 _tmp_test_deeply_nested_4 = 5;
    til_I64 _tmp_test_deeply_nested_5 = til_I64_mul(&_tmp_test_deeply_nested_3, &_tmp_test_deeply_nested_4);
    const til_I64 til_I64_result = til_I64_add(&_tmp_test_deeply_nested_2, &_tmp_test_deeply_nested_5);
    til_I64 _tmp_test_deeply_nested_6 = 26;
    til_Bool _tmp_test_deeply_nested_7 = til_I64_eq(&til_I64_result, &_tmp_test_deeply_nested_6);
    til_test(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:22:10:", 1}), 29, 0}), &_tmp_test_deeply_nested_7, &((til_Str){((til_Ptr){(til_I64)"add(mul(2, 3), mul(4, 5)) should be 26", 1}), 38, 0}));
}

void til_test_string_concat(void) {
    const til_Str til_Str_result = til_concat(&((til_Str){((til_Ptr){(til_I64)"hello", 1}), 5, 0}), &((til_Str){((til_Ptr){(til_I64)" world", 1}), 6, 0}));
    til_Bool _tmp_test_string_concat_0 = til_Str_eq(&til_Str_result, &((til_Str){((til_Ptr){(til_I64)"hello world", 1}), 11, 0}));
    til_test(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:29:10:", 1}), 29, 0}), &_tmp_test_string_concat_0, &((til_Str){((til_Ptr){(til_I64)"concat is folded at compile time", 1}), 32, 0}));
}

void til_test_fold_variable(void) {
    const til_I64 til_I64_x = 5;
    til_I64 _tmp_test_fold_variable_0 = 3;
    const til_I64 til_I64_result = til_I64_add(&til_I64_x, &_tmp_test_fold_variable_0);
    til_I64 _tmp_test_fold_variable_1 = 8;
    til_Bool _tmp_test_fold_variable_2 = til_I64_eq(&til_I64_result, &_tmp_test_fold_variable_1);
    til_test(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:38:10:", 1}), 29, 0}), &_tmp_test_fold_variable_2, &((til_Str){((til_Ptr){(til_I64)"add(x, 3) should fold to 8", 1}), 26, 0}));
}

void til_test_loc_folded_correctly(void) {
    const til_Str til_Str_location = ((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:44:17:", 1}), 29, 0});
    til_Bool _tmp_test_loc_folded_correctly_0 = til_Str_contains(&til_Str_location, &((til_Str){((til_Ptr){(til_I64)"constfold.til", 1}), 13, 0}));
    til_test(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:45:10:", 1}), 29, 0}), &_tmp_test_loc_folded_correctly_0, &((til_Str){((til_Ptr){(til_I64)"loc() should contain filename", 1}), 29, 0}));
    til_Bool _tmp_test_loc_folded_correctly_1 = til_Str_contains(&til_Str_location, &((til_Str){((til_Ptr){(til_I64)":44:", 1}), 4, 0}));
    til_test(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:46:10:", 1}), 29, 0}), &_tmp_test_loc_folded_correctly_1, &((til_Str){((til_Ptr){(til_I64)"loc() should contain correct line number", 1}), 40, 0}));
}

void til_test_struct_fold_simple(void) {
    const til_CfVec2 til_CfVec2_v = til_CfVec2_magic();
    til_I64 _tmp_test_struct_fold_simple_0 = 42;
    til_assert_eq(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:71:15:", 1}), 29, 0}), &_tmp_test_struct_fold_simple_0, &til_CfVec2_v.x);
    til_I64 _tmp_test_struct_fold_simple_1 = 99;
    til_assert_eq(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:72:15:", 1}), 29, 0}), &_tmp_test_struct_fold_simple_1, &til_CfVec2_v.y);
}

void til_test_struct_fold_values(void) {
    til_I64 _tmp_test_struct_fold_values_0 = 10;
    til_I64 _tmp_test_struct_fold_values_1 = 20;
    const til_CfVec2 til_CfVec2_p = til_CfVec2_at(&_tmp_test_struct_fold_values_0, &_tmp_test_struct_fold_values_1);
    til_I64 _tmp_test_struct_fold_values_2 = 10;
    til_assert_eq(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:79:15:", 1}), 29, 0}), &_tmp_test_struct_fold_values_2, &til_CfVec2_p.x);
    til_I64 _tmp_test_struct_fold_values_3 = 20;
    til_assert_eq(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:80:15:", 1}), 29, 0}), &_tmp_test_struct_fold_values_3, &til_CfVec2_p.y);
}

void til_test_struct_fold_nested(void) {
    const til_CfRect til_CfRect_r = til_CfRect_sample();
    til_I64 _tmp_test_struct_fold_nested_0 = 5;
    til_assert_eq(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:97:15:", 1}), 29, 0}), &_tmp_test_struct_fold_nested_0, &til_CfRect_r.top_left.x);
    til_I64 _tmp_test_struct_fold_nested_1 = 10;
    til_assert_eq(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:98:15:", 1}), 29, 0}), &_tmp_test_struct_fold_nested_1, &til_CfRect_r.top_left.y);
    til_I64 _tmp_test_struct_fold_nested_2 = 100;
    til_assert_eq(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:99:15:", 1}), 29, 0}), &_tmp_test_struct_fold_nested_2, &til_CfRect_r.bottom_right.x);
    til_I64 _tmp_test_struct_fold_nested_3 = 200;
    til_assert_eq(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:100:15:", 1}), 30, 0}), &_tmp_test_struct_fold_nested_3, &til_CfRect_r.bottom_right.y);
}

til_Ptr til_Ptr_new_by_size(const til_I64* til_I64_size) {
    til_BadAlloc _thrown_BadAlloc__tmp_til_Ptr_new_by_size_0;
    til_I64 _tmp_til_Ptr_new_by_size_1 = 0;
    if (til_I64_lteq(til_I64_size, &_tmp_til_Ptr_new_by_size_1).data) {
        til_Array _tmp_til_Ptr_new_by_size_2;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Ptr_new_by_size_3;
        til_Type _tmp_til_Ptr_new_by_size_4 = "Str";
        til_I64 _tmp_til_Ptr_new_by_size_5 = 0;
        _tmp_til_Ptr_new_by_size_2 = til_Array_new(_tmp_til_Ptr_new_by_size_4, &_tmp_til_Ptr_new_by_size_5);
        int __attribute__((unused)) _arr_status__tmp_til_Ptr_new_by_size_3;
        til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/ptr.til:12:19:", 1}), 23, 0}), &((til_Str){((til_Ptr){(til_I64)"Ptr.new_by_size: invalid size", 1}), 29, 0}), &_tmp_til_Ptr_new_by_size_2);
        til_Array_delete(&_tmp_til_Ptr_new_by_size_2);
    }
    til_Ptr til_Ptr_p = {.data = til_I64_NULL, .is_borrowed = 0};
    til_I64 _ret__tmp_til_Ptr_new_by_size_6;
    int __attribute__((unused)) _status__tmp_til_Ptr_new_by_size_6 = til_malloc(&_ret__tmp_til_Ptr_new_by_size_6, til_I64_size);
    if (_status__tmp_til_Ptr_new_by_size_6 == 1) { goto _catch_BadAlloc__tmp_til_Ptr_new_by_size_0; }
    til_Ptr_p.data = _ret__tmp_til_Ptr_new_by_size_6;
    if (0) { _catch_BadAlloc__tmp_til_Ptr_new_by_size_0:;
        til_BadAlloc til_BadAlloc_err = _thrown_BadAlloc__tmp_til_Ptr_new_by_size_0;
        til_Array _tmp_til_Ptr_new_by_size_7;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Ptr_new_by_size_8;
        til_Type _tmp_til_Ptr_new_by_size_9 = "Str";
        til_I64 _tmp_til_Ptr_new_by_size_10 = 0;
        _tmp_til_Ptr_new_by_size_7 = til_Array_new(_tmp_til_Ptr_new_by_size_9, &_tmp_til_Ptr_new_by_size_10);
        int __attribute__((unused)) _arr_status__tmp_til_Ptr_new_by_size_8;
        til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/ptr.til:16:39:", 1}), 23, 0}), &((til_Str){((til_Ptr){(til_I64)"Ptr.new_by_size: malloc failed", 1}), 30, 0}), &_tmp_til_Ptr_new_by_size_7);
        til_Array_delete(&_tmp_til_Ptr_new_by_size_7);
    }
    return til_Ptr_p;
    return (til_Ptr){0};
}

void til_Ptr_delete(til_Ptr* til_Ptr_self) {
    if (til_I64_eq(&til_I64_NULL, &til_Ptr_self->data).data) {
        return;
    }
    til_I64 _tmp_til_Ptr_delete_0 = 0;
    if (til_I64_eq(&til_Ptr_self->is_borrowed, &_tmp_til_Ptr_delete_0).data) {
        til_free(&til_Ptr_self->data);
    }
    til_Ptr_self->data = til_I64_NULL;
}

til_Ptr til_Ptr_offset(const til_Ptr* til_Ptr_self, const til_I64* til_I64_offset) {
    til_Ptr til_Ptr_p = {.data = til_I64_NULL, .is_borrowed = 0};
    til_Ptr_p.data = til_I64_add(&til_Ptr_self->data, til_I64_offset);
    return til_Ptr_p;
    return (til_Ptr){0};
}

void til_Ptr_copy_from(til_Ptr* til_Ptr_self, const til_Ptr* til_Ptr_src, const til_I64* til_I64_size) {
    til_memcpy(&til_Ptr_self->data, &til_Ptr_src->data, til_I64_size);
}

til_I64 til_Str_len(const til_Str* til_Str_self) {
    return til_Str_self->_len;
    return (til_I64){0};
}

til_Bool til_Str_eq(const til_Str* til_Str_self, const til_Str* til_Str_other) {
    til_Bool _tmp_til_Str_eq_0 = til_I64_eq(&til_Str_self->_len, &til_Str_other->_len);
    if (til_not(&_tmp_til_Str_eq_0).data) {
        return false;
    }
    til_I64 til_I64_i = 0;
    til_U8 til_U8_self_byte;
    til_U8 til_U8_other_byte;
    til_I64 _tmp_til_Str_eq_1 = 0;
    if (til_I64_lt(&_tmp_til_Str_eq_1, &til_Str_self->_len).data) {
        while (til_I64_lt(&til_I64_i, &til_Str_self->_len).data) {
            til_U8_self_byte = 0;
            til_U8_other_byte = 0;
            til_I64 _tmp_til_Str_eq_2 = (til_I64)&til_U8_self_byte;
            til_I64 _tmp_til_Str_eq_3 = til_Ptr_offset(&til_Str_self->c_string, &til_I64_i).data;
            til_I64 _tmp_til_Str_eq_4 = 1;
            til_memcpy(&_tmp_til_Str_eq_2, &_tmp_til_Str_eq_3, &_tmp_til_Str_eq_4);
            til_I64 _tmp_til_Str_eq_5 = (til_I64)&til_U8_other_byte;
            til_I64 _tmp_til_Str_eq_6 = til_Ptr_offset(&til_Str_other->c_string, &til_I64_i).data;
            til_I64 _tmp_til_Str_eq_7 = 1;
            til_memcpy(&_tmp_til_Str_eq_5, &_tmp_til_Str_eq_6, &_tmp_til_Str_eq_7);
            til_Bool _tmp_til_Str_eq_8 = til_U8_eq(&til_U8_self_byte, &til_U8_other_byte);
            if (til_not(&_tmp_til_Str_eq_8).data) {
                return false;
            }
            til_I64_inc(&til_I64_i);
        }
    } else {
        while (til_I64_gt(&til_I64_i, &til_Str_self->_len).data) {
            til_U8_self_byte = 0;
            til_U8_other_byte = 0;
            til_I64 _tmp_til_Str_eq_9 = (til_I64)&til_U8_self_byte;
            til_I64 _tmp_til_Str_eq_10 = til_Ptr_offset(&til_Str_self->c_string, &til_I64_i).data;
            til_I64 _tmp_til_Str_eq_11 = 1;
            til_memcpy(&_tmp_til_Str_eq_9, &_tmp_til_Str_eq_10, &_tmp_til_Str_eq_11);
            til_I64 _tmp_til_Str_eq_12 = (til_I64)&til_U8_other_byte;
            til_I64 _tmp_til_Str_eq_13 = til_Ptr_offset(&til_Str_other->c_string, &til_I64_i).data;
            til_I64 _tmp_til_Str_eq_14 = 1;
            til_memcpy(&_tmp_til_Str_eq_12, &_tmp_til_Str_eq_13, &_tmp_til_Str_eq_14);
            til_Bool _tmp_til_Str_eq_15 = til_U8_eq(&til_U8_self_byte, &til_U8_other_byte);
            if (til_not(&_tmp_til_Str_eq_15).data) {
                return false;
            }
            til_I64_dec(&til_I64_i);
        }
    }
    return true;
    return (til_Bool){0};
}

til_Str til_Str_clone(const til_Str* til_Str_self) {
    til_Ptr _tmp_til_Str_clone_0 = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0};
    til_Str til_Str_cloned = {.c_string = _tmp_til_Str_clone_0, ._len = 0, .cap = 0};
    til_Str_cloned._len = til_Str_self->_len;
    til_I64 _tmp_til_Str_clone_1 = 1;
    til_Str_cloned.cap = til_I64_add(&til_Str_cloned._len, &_tmp_til_Str_clone_1);
    til_Str_cloned.c_string = til_Ptr_new_by_size(&til_Str_cloned.cap);
    til_Str_cloned.c_string.is_borrowed = 0;
    til_Ptr_copy_from(&til_Str_cloned.c_string, &til_Str_self->c_string, &til_Str_self->_len);
    const til_U8 til_U8_zero = 0;
    til_I64 _tmp_til_Str_clone_2 = til_Ptr_offset(&til_Str_cloned.c_string, &til_Str_cloned._len).data;
    til_I64 _tmp_til_Str_clone_3 = 1;
    til_memset(&_tmp_til_Str_clone_2, &til_U8_zero, &_tmp_til_Str_clone_3);
    return til_Str_cloned;
    return (til_Str){0};
}

void til_Str_delete(til_Str* til_Str_self) {
    til_I64 _tmp_til_Str_delete_0 = 0;
    if (til_I64_gt(&til_Str_self->cap, &_tmp_til_Str_delete_0).data) {
        til_Ptr_delete(&til_Str_self->c_string);
    }
    til_Str_self->c_string = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0};
    til_Str_self->_len = 0;
    til_Str_self->cap = 0;
}

til_Bool til_Str_contains(const til_Str* til_Str_self, const til_Str* til_Str_needle) {
    til_I64 _tmp_til_Str_contains_0 = til_Str_len(til_Str_needle);
    til_I64 _tmp_til_Str_contains_1 = til_Str_len(til_Str_self);
    if (til_I64_gt(&_tmp_til_Str_contains_0, &_tmp_til_Str_contains_1).data) {
        return false;
    }
    til_I64 _tmp_til_Str_contains_2 = til_Str_len(til_Str_needle);
    til_I64 _tmp_til_Str_contains_3 = 0;
    if (til_I64_eq(&_tmp_til_Str_contains_2, &_tmp_til_Str_contains_3).data) {
        return false;
    }
    til_I64 _tmp_til_Str_contains_4 = til_Str_len(til_Str_self);
    til_I64 _tmp_til_Str_contains_5 = til_Str_len(til_Str_needle);
    til_I64 til_I64_max_start = til_I64_sub(&_tmp_til_Str_contains_4, &_tmp_til_Str_contains_5);
    til_I64 til_I64_start_idx = 0;
    til_Bool til_Bool_matches;
    til_I64 til_I64_needle_idx;
    til_U8 til_U8_self_byte;
    til_U8 til_U8_needle_byte;
    til_I64 _tmp_til_Str_contains_6 = 0;
    til_I64 _tmp_til_Str_contains_7 = 1;
    til_I64 _tmp_til_Str_contains_8 = til_I64_add(&til_I64_max_start, &_tmp_til_Str_contains_7);
    if (til_I64_lt(&_tmp_til_Str_contains_6, &_tmp_til_Str_contains_8).data) {
        while (1) {
            til_I64 _tmp_til_Str_contains_9 = 1;
            til_I64 _tmp_til_Str_contains_10 = til_I64_add(&til_I64_max_start, &_tmp_til_Str_contains_9);
            if (!(til_I64_lt(&til_I64_start_idx, &_tmp_til_Str_contains_10).data)) break;
            til_Bool_matches = true;
            til_I64_needle_idx = 0;
            til_I64 _tmp_til_Str_contains_11 = 0;
            til_I64 _tmp_til_Str_contains_12 = til_Str_len(til_Str_needle);
            if (til_I64_lt(&_tmp_til_Str_contains_11, &_tmp_til_Str_contains_12).data) {
                while (1) {
                    til_I64 _tmp_til_Str_contains_13 = til_Str_len(til_Str_needle);
                    if (!(til_I64_lt(&til_I64_needle_idx, &_tmp_til_Str_contains_13).data)) break;
                    til_U8_self_byte = 0;
                    til_U8_needle_byte = 0;
                    til_I64 _tmp_til_Str_contains_14 = (til_I64)&til_U8_self_byte;
                    til_I64 _tmp_til_Str_contains_15 = til_I64_add(&til_I64_start_idx, &til_I64_needle_idx);
                    til_I64 _tmp_til_Str_contains_16 = til_Ptr_offset(&til_Str_self->c_string, &_tmp_til_Str_contains_15).data;
                    til_I64 _tmp_til_Str_contains_17 = 1;
                    til_memcpy(&_tmp_til_Str_contains_14, &_tmp_til_Str_contains_16, &_tmp_til_Str_contains_17);
                    til_I64 _tmp_til_Str_contains_18 = (til_I64)&til_U8_needle_byte;
                    til_I64 _tmp_til_Str_contains_19 = til_Ptr_offset(&til_Str_needle->c_string, &til_I64_needle_idx).data;
                    til_I64 _tmp_til_Str_contains_20 = 1;
                    til_memcpy(&_tmp_til_Str_contains_18, &_tmp_til_Str_contains_19, &_tmp_til_Str_contains_20);
                    til_Bool _tmp_til_Str_contains_21 = til_U8_eq(&til_U8_self_byte, &til_U8_needle_byte);
                    if (til_not(&_tmp_til_Str_contains_21).data) {
                        til_Bool_matches = false;
                    }
                    til_I64_inc(&til_I64_needle_idx);
                }
            } else {
                while (1) {
                    til_I64 _tmp_til_Str_contains_22 = til_Str_len(til_Str_needle);
                    if (!(til_I64_gt(&til_I64_needle_idx, &_tmp_til_Str_contains_22).data)) break;
                    til_U8_self_byte = 0;
                    til_U8_needle_byte = 0;
                    til_I64 _tmp_til_Str_contains_23 = (til_I64)&til_U8_self_byte;
                    til_I64 _tmp_til_Str_contains_24 = til_I64_add(&til_I64_start_idx, &til_I64_needle_idx);
                    til_I64 _tmp_til_Str_contains_25 = til_Ptr_offset(&til_Str_self->c_string, &_tmp_til_Str_contains_24).data;
                    til_I64 _tmp_til_Str_contains_26 = 1;
                    til_memcpy(&_tmp_til_Str_contains_23, &_tmp_til_Str_contains_25, &_tmp_til_Str_contains_26);
                    til_I64 _tmp_til_Str_contains_27 = (til_I64)&til_U8_needle_byte;
                    til_I64 _tmp_til_Str_contains_28 = til_Ptr_offset(&til_Str_needle->c_string, &til_I64_needle_idx).data;
                    til_I64 _tmp_til_Str_contains_29 = 1;
                    til_memcpy(&_tmp_til_Str_contains_27, &_tmp_til_Str_contains_28, &_tmp_til_Str_contains_29);
                    til_Bool _tmp_til_Str_contains_30 = til_U8_eq(&til_U8_self_byte, &til_U8_needle_byte);
                    if (til_not(&_tmp_til_Str_contains_30).data) {
                        til_Bool_matches = false;
                    }
                    til_I64_dec(&til_I64_needle_idx);
                }
            }
            if (til_Bool_matches.data) {
                return true;
            }
            til_I64_inc(&til_I64_start_idx);
        }
    } else {
        while (1) {
            til_I64 _tmp_til_Str_contains_31 = 1;
            til_I64 _tmp_til_Str_contains_32 = til_I64_add(&til_I64_max_start, &_tmp_til_Str_contains_31);
            if (!(til_I64_gt(&til_I64_start_idx, &_tmp_til_Str_contains_32).data)) break;
            til_Bool_matches = true;
            til_I64_needle_idx = 0;
            til_I64 _tmp_til_Str_contains_33 = 0;
            til_I64 _tmp_til_Str_contains_34 = til_Str_len(til_Str_needle);
            if (til_I64_lt(&_tmp_til_Str_contains_33, &_tmp_til_Str_contains_34).data) {
                while (1) {
                    til_I64 _tmp_til_Str_contains_35 = til_Str_len(til_Str_needle);
                    if (!(til_I64_lt(&til_I64_needle_idx, &_tmp_til_Str_contains_35).data)) break;
                    til_U8_self_byte = 0;
                    til_U8_needle_byte = 0;
                    til_I64 _tmp_til_Str_contains_36 = (til_I64)&til_U8_self_byte;
                    til_I64 _tmp_til_Str_contains_37 = til_I64_add(&til_I64_start_idx, &til_I64_needle_idx);
                    til_I64 _tmp_til_Str_contains_38 = til_Ptr_offset(&til_Str_self->c_string, &_tmp_til_Str_contains_37).data;
                    til_I64 _tmp_til_Str_contains_39 = 1;
                    til_memcpy(&_tmp_til_Str_contains_36, &_tmp_til_Str_contains_38, &_tmp_til_Str_contains_39);
                    til_I64 _tmp_til_Str_contains_40 = (til_I64)&til_U8_needle_byte;
                    til_I64 _tmp_til_Str_contains_41 = til_Ptr_offset(&til_Str_needle->c_string, &til_I64_needle_idx).data;
                    til_I64 _tmp_til_Str_contains_42 = 1;
                    til_memcpy(&_tmp_til_Str_contains_40, &_tmp_til_Str_contains_41, &_tmp_til_Str_contains_42);
                    til_Bool _tmp_til_Str_contains_43 = til_U8_eq(&til_U8_self_byte, &til_U8_needle_byte);
                    if (til_not(&_tmp_til_Str_contains_43).data) {
                        til_Bool_matches = false;
                    }
                    til_I64_inc(&til_I64_needle_idx);
                }
            } else {
                while (1) {
                    til_I64 _tmp_til_Str_contains_44 = til_Str_len(til_Str_needle);
                    if (!(til_I64_gt(&til_I64_needle_idx, &_tmp_til_Str_contains_44).data)) break;
                    til_U8_self_byte = 0;
                    til_U8_needle_byte = 0;
                    til_I64 _tmp_til_Str_contains_45 = (til_I64)&til_U8_self_byte;
                    til_I64 _tmp_til_Str_contains_46 = til_I64_add(&til_I64_start_idx, &til_I64_needle_idx);
                    til_I64 _tmp_til_Str_contains_47 = til_Ptr_offset(&til_Str_self->c_string, &_tmp_til_Str_contains_46).data;
                    til_I64 _tmp_til_Str_contains_48 = 1;
                    til_memcpy(&_tmp_til_Str_contains_45, &_tmp_til_Str_contains_47, &_tmp_til_Str_contains_48);
                    til_I64 _tmp_til_Str_contains_49 = (til_I64)&til_U8_needle_byte;
                    til_I64 _tmp_til_Str_contains_50 = til_Ptr_offset(&til_Str_needle->c_string, &til_I64_needle_idx).data;
                    til_I64 _tmp_til_Str_contains_51 = 1;
                    til_memcpy(&_tmp_til_Str_contains_49, &_tmp_til_Str_contains_50, &_tmp_til_Str_contains_51);
                    til_Bool _tmp_til_Str_contains_52 = til_U8_eq(&til_U8_self_byte, &til_U8_needle_byte);
                    if (til_not(&_tmp_til_Str_contains_52).data) {
                        til_Bool_matches = false;
                    }
                    til_I64_dec(&til_I64_needle_idx);
                }
            }
            if (til_Bool_matches.data) {
                return true;
            }
            til_I64_dec(&til_I64_start_idx);
        }
    }
    return false;
    return (til_Bool){0};
}

til_Bool til_U8_lt(const til_U8* til_U8_self, const til_U8* til_U8_other) {
    return til_u8_lt(til_U8_self, til_U8_other);
    return (til_Bool){0};
}

til_Bool til_U8_gt(const til_U8* til_U8_self, const til_U8* til_U8_other) {
    return til_u8_gt(til_U8_self, til_U8_other);
    return (til_Bool){0};
}

til_Bool til_U8_eq(const til_U8* til_U8_a, const til_U8* til_U8_b) {
    if (til_U8_gt(til_U8_a, til_U8_b).data) {
        return false;
    }
    if (til_U8_gt(til_U8_b, til_U8_a).data) {
        return false;
    }
    if (til_U8_lt(til_U8_a, til_U8_b).data) {
        return false;
    }
    if (til_U8_lt(til_U8_b, til_U8_a).data) {
        return false;
    }
    return true;
    return (til_Bool){0};
}

til_CfVec2 til_CfVec2_magic(void) {
    return (til_CfVec2){.x = 42, .y = 99};
    return (til_CfVec2){0};
}

til_CfVec2 til_CfVec2_at(const til_I64* til_I64_x, const til_I64* til_I64_y) {
    return (til_CfVec2){.x = (*til_I64_x), .y = (*til_I64_y)};
    return (til_CfVec2){0};
}

til_CfRect til_CfRect_sample(void) {
    return (til_CfRect){.top_left = (til_CfVec2){.x = 5, .y = 10}, .bottom_right = (til_CfVec2){.x = 100, .y = 200}};
    return (til_CfRect){0};
}

void til_IndexOutOfBoundsError_delete(til_IndexOutOfBoundsError* til_IndexOutOfBoundsError_self) {
    til_Str_delete(&til_IndexOutOfBoundsError_self->msg);
}

til_IndexOutOfBoundsError til_IndexOutOfBoundsError_clone(const til_IndexOutOfBoundsError* til_IndexOutOfBoundsError_self) {
    return (til_IndexOutOfBoundsError){.msg = til_Str_clone(&til_IndexOutOfBoundsError_self->msg)};
    return (til_IndexOutOfBoundsError){0};
}

til_I64 til_Array_len(const til_Array* til_Array_self) {
    return til_Array_self->_len;
    return (til_I64){0};
}

til_I64 til_Array_size(const til_Array* til_Array_self) {
    return til_I64_mul(&til_Array_self->_len, &til_Array_self->type_size);
    return (til_I64){0};
}

til_Array til_Array_new(til_Type til_Type_T, const til_I64* til_I64_capacity) {
    til_BadAlloc _thrown_BadAlloc__tmp_til_Array_new_0;
    til_Array til_Array_arr = {.type_name = ((til_Str){((til_Ptr){(til_I64)"", 1}), 0, 0}), .type_size = 0, .ptr = 0, ._len = 0};
    til_Array_arr.type_name = ((til_Str){((til_Ptr){(til_I64)til_Type_T, 1}), strlen(til_Type_T), 0});
    til_Array_arr.type_size = til_size_of(&((til_Str){((til_Ptr){(til_I64)til_Type_T, 1}), strlen(til_Type_T), 0}));
    const til_I64 til_I64_size_bytes = til_I64_mul(til_I64_capacity, &til_Array_arr.type_size);
    til_I64 _ret__tmp_til_Array_new_1;
    int __attribute__((unused)) _status__tmp_til_Array_new_1 = til_malloc(&_ret__tmp_til_Array_new_1, &til_I64_size_bytes);
    if (_status__tmp_til_Array_new_1 == 1) { goto _catch_BadAlloc__tmp_til_Array_new_0; }
    til_Array_arr.ptr = _ret__tmp_til_Array_new_1;
    if (0) { _catch_BadAlloc__tmp_til_Array_new_0:;
        til_BadAlloc til_BadAlloc_err = _thrown_BadAlloc__tmp_til_Array_new_0;
        til_Array _tmp_til_Array_new_2;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Array_new_3;
        til_Type _tmp_til_Array_new_4 = "Str";
        til_I64 _tmp_til_Array_new_5 = 0;
        _tmp_til_Array_new_2 = til_Array_new(_tmp_til_Array_new_4, &_tmp_til_Array_new_5);
        int __attribute__((unused)) _arr_status__tmp_til_Array_new_3;
        til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/array.til:35:39:", 1}), 25, 0}), &((til_Str){((til_Ptr){(til_I64)"Array.new: malloc failed", 1}), 24, 0}), &_tmp_til_Array_new_2);
        til_Array_delete(&_tmp_til_Array_new_2);
    }
    const til_U8 til_U8_zero = 0;
    til_memset(&til_Array_arr.ptr, &til_U8_zero, &til_I64_size_bytes);
    til_Array_arr._len = (*til_I64_capacity);
    return til_Array_arr;
    return (til_Array){0};
}

int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array* til_Array_self, const til_I64* til_I64_index, til_Dynamic* til_Dynamic_T) {
    if (til_I64_gteq(til_I64_index, &til_Array_self->_len).data) {
        til_Str _tmp_til_Array_get_0;
        til_Array _tmp_til_Array_get_1;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Array_get_2;
        til_Str _tmp_til_Array_get_3 = ((til_Str){((til_Ptr){(til_I64)"Array.get: index out of bounds", 1}), 30, 0});
        til_Type _tmp_til_Array_get_4 = "Str";
        til_I64 _tmp_til_Array_get_5 = 1;
        _tmp_til_Array_get_1 = til_Array_new(_tmp_til_Array_get_4, &_tmp_til_Array_get_5);
        int __attribute__((unused)) _arr_status__tmp_til_Array_get_2;
        til_I64 _tmp_til_Array_get_6 = 0;
        _arr_status__tmp_til_Array_get_2 = til_Array_set(&_err_idx__tmp_til_Array_get_2, &_tmp_til_Array_get_1, &_tmp_til_Array_get_6, (til_Dynamic*)&_tmp_til_Array_get_3);
        _tmp_til_Array_get_0 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/array.til:45:52:", 1}), 25, 0}), &_tmp_til_Array_get_1);
        til_Array_delete(&_tmp_til_Array_get_1);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_til_Array_get_0};
        return 1;
    }
    til_I64 _tmp_til_Array_get_7 = til_I64_mul(til_I64_index, &til_Array_self->type_size);
    const til_I64 til_I64_src = til_I64_add(&til_Array_self->ptr, &_tmp_til_Array_get_7);
    til_I64 til_I64_dest = (til_I64)til_Dynamic_T;
    til_memcpy(&til_I64_dest, &til_I64_src, &til_Array_self->type_size);
    return 0;
}

int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_Array_self, const til_I64* til_I64_index, const til_Dynamic* til_Dynamic_value) {
    if (til_I64_gteq(til_I64_index, &til_Array_self->_len).data) {
        til_Str _tmp_til_Array_set_0;
        til_Array _tmp_til_Array_set_1;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Array_set_2;
        til_Str _tmp_til_Array_set_3 = ((til_Str){((til_Ptr){(til_I64)"Array.set: index out of bounds", 1}), 30, 0});
        til_Type _tmp_til_Array_set_4 = "Str";
        til_I64 _tmp_til_Array_set_5 = 1;
        _tmp_til_Array_set_1 = til_Array_new(_tmp_til_Array_set_4, &_tmp_til_Array_set_5);
        int __attribute__((unused)) _arr_status__tmp_til_Array_set_2;
        til_I64 _tmp_til_Array_set_6 = 0;
        _arr_status__tmp_til_Array_set_2 = til_Array_set(&_err_idx__tmp_til_Array_set_2, &_tmp_til_Array_set_1, &_tmp_til_Array_set_6, (til_Dynamic*)&_tmp_til_Array_set_3);
        _tmp_til_Array_set_0 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/array.til:60:52:", 1}), 25, 0}), &_tmp_til_Array_set_1);
        til_Array_delete(&_tmp_til_Array_set_1);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_til_Array_set_0};
        return 1;
    }
    til_I64 _tmp_til_Array_set_7 = til_I64_mul(til_I64_index, &til_Array_self->type_size);
    til_I64 til_I64_dest = til_I64_add(&til_Array_self->ptr, &_tmp_til_Array_set_7);
    til_I64 _tmp_til_Array_set_8 = (til_I64)til_Dynamic_value;
    til_memcpy(&til_I64_dest, &_tmp_til_Array_set_8, &til_Array_self->type_size);
    return 0;
}

void til_Array_delete(til_Array* til_Array_self) {
    til_free(&til_Array_self->ptr);
    til_Array_self->ptr = 0;
    til_Array_self->_len = 0;
}

til_Array til_Array_clone(const til_Array* til_Array_self) {
    til_BadAlloc _thrown_BadAlloc__tmp_til_Array_clone_0;
    til_Array til_Array_cloned = {.type_name = ((til_Str){((til_Ptr){(til_I64)"", 1}), 0, 0}), .type_size = 0, .ptr = 0, ._len = 0};
    til_Array_cloned.type_name = til_Array_self->type_name;
    til_Array_cloned.type_size = til_Array_self->type_size;
    til_Array_cloned._len = til_Array_self->_len;
    til_I64 til_I64_total_bytes = til_I64_mul(&til_Array_self->_len, &til_Array_self->type_size);
    til_I64 _ret__tmp_til_Array_clone_1;
    int __attribute__((unused)) _status__tmp_til_Array_clone_1 = til_malloc(&_ret__tmp_til_Array_clone_1, &til_I64_total_bytes);
    if (_status__tmp_til_Array_clone_1 == 1) { goto _catch_BadAlloc__tmp_til_Array_clone_0; }
    til_Array_cloned.ptr = _ret__tmp_til_Array_clone_1;
    if (0) { _catch_BadAlloc__tmp_til_Array_clone_0:;
        til_BadAlloc til_BadAlloc_err = _thrown_BadAlloc__tmp_til_Array_clone_0;
        til_Array _tmp_til_Array_clone_2;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Array_clone_3;
        til_Type _tmp_til_Array_clone_4 = "Str";
        til_I64 _tmp_til_Array_clone_5 = 0;
        _tmp_til_Array_clone_2 = til_Array_new(_tmp_til_Array_clone_4, &_tmp_til_Array_clone_5);
        int __attribute__((unused)) _arr_status__tmp_til_Array_clone_3;
        til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/array.til:86:39:", 1}), 25, 0}), &((til_Str){((til_Ptr){(til_I64)"Array.clone: malloc failed", 1}), 26, 0}), &_tmp_til_Array_clone_2);
        til_Array_delete(&_tmp_til_Array_clone_2);
    }
    til_memcpy(&til_Array_cloned.ptr, &til_Array_self->ptr, &til_I64_total_bytes);
    return til_Array_cloned;
    return (til_Array){0};
}

til_Bool til_Array_contains(const til_Array* til_Array_self, const til_Str* til_Str_value) {
    til_I64 _for_i_0 = 0;
    til_Str til_Str_elem;
    while (1) {
        til_I64 _tmp_til_Array_contains_0 = til_Array_len(til_Array_self);
        if (!(til_I64_lt(&_for_i_0, &_tmp_til_Array_contains_0).data)) break;
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp_til_Array_contains_1;
        til_Ptr _tmp_til_Array_contains_2 = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0};
        til_Str_elem = (til_Str){.c_string = _tmp_til_Array_contains_2, ._len = 0, .cap = 0};
        til_IndexOutOfBoundsError _err0__tmp_til_Array_contains_3 = {};
        int __attribute__((unused)) _status__tmp_til_Array_contains_3 = til_Array_get(&_err0__tmp_til_Array_contains_3, til_Array_self, &_for_i_0, (til_Dynamic*)&til_Str_elem);
        if (_status__tmp_til_Array_contains_3 == 1) { _thrown_IndexOutOfBoundsError__tmp_til_Array_contains_1 = _err0__tmp_til_Array_contains_3; goto _catch_IndexOutOfBoundsError__tmp_til_Array_contains_1; }
        if (0) { _catch_IndexOutOfBoundsError__tmp_til_Array_contains_1:;
            til_IndexOutOfBoundsError _err_forin_0 = _thrown_IndexOutOfBoundsError__tmp_til_Array_contains_1;
            til_Array _tmp_til_Array_contains_4;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Array_contains_5;
            til_Type _tmp_til_Array_contains_6 = "Str";
            til_I64 _tmp_til_Array_contains_7 = 0;
            _tmp_til_Array_contains_4 = til_Array_new(_tmp_til_Array_contains_6, &_tmp_til_Array_contains_7);
            int __attribute__((unused)) _arr_status__tmp_til_Array_contains_5;
            til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/array.til:93:9:", 1}), 24, 0}), &_err_forin_0.msg, &_tmp_til_Array_contains_4);
            til_Array_delete(&_tmp_til_Array_contains_4);
        }
        if (til_Str_eq(&til_Str_elem, til_Str_value).data) {
            return true;
        }
        til_I64 _tmp_til_Array_contains_8 = 1;
        _for_i_0 = til_I64_add(&_for_i_0, &_tmp_til_Array_contains_8);
    }
    return false;
    return (til_Bool){0};
}

til_I64 til_Bool_len(const til_Bool* _self) {
    return 1;
    return (til_I64){0};
}

til_Bool til_Bool_eq(const til_Bool* til_Bool_a, const til_Bool* til_Bool_b) {
    til_Bool _tmp_til_Bool_eq_0 = til_Bool_and(til_Bool_a, til_Bool_b);
    til_Bool _tmp_til_Bool_eq_1 = til_not(til_Bool_b);
    til_Bool _tmp_til_Bool_eq_2 = til_not(til_Bool_a);
    til_Bool _tmp_til_Bool_eq_3 = til_Bool_and(&_tmp_til_Bool_eq_1, &_tmp_til_Bool_eq_2);
    return til_Bool_or(&_tmp_til_Bool_eq_0, &_tmp_til_Bool_eq_3);
    return (til_Bool){0};
}

til_Bool til_Bool_and(const til_Bool* til_Bool_self, const til_Bool* til_Bool_other) {
    if ((*til_Bool_self).data) {
        return (*til_Bool_other);
    }
    return false;
    return (til_Bool){0};
}

til_Bool til_Bool_or(const til_Bool* til_Bool_self, const til_Bool* til_Bool_other) {
    if ((*til_Bool_self).data) {
        return true;
    }
    return (*til_Bool_other);
    return (til_Bool){0};
}

til_Str til_Bool_to_str(const til_Bool* til_Bool_self) {
    if ((*til_Bool_self).data) {
        return ((til_Str){((til_Ptr){(til_I64)"true", 1}), 4, 0});
    }
    return ((til_Str){((til_Ptr){(til_I64)"false", 1}), 5, 0});
    return (til_Str){0};
}

til_I64 til_Bool_to_i64(const til_Bool* til_Bool_self) {
    if ((*til_Bool_self).data) {
        return 1;
    }
    return 0;
    return (til_I64){0};
}

til_U8 til_Bool_to_u8(const til_Bool* til_Bool_self) {
    return til_Bool_self->data;
    return (til_U8){0};
}

til_Bool til_Bool_from_i64(const til_I64* til_I64_i) {
    til_Bool til_Bool_b = {.data = 0};
    til_I64 _tmp_til_Bool_from_i64_0 = 0;
    if (til_I64_gt(til_I64_i, &_tmp_til_Bool_from_i64_0).data) {
        til_Bool_b.data = 1;
    }
    return til_Bool_b;
    return (til_Bool){0};
}

til_I64 til_Bool_size(void) {
    return 1;
    return (til_I64){0};
}

void til_Bool_delete(til_Bool* _self) {
}

til_Bool til_Bool_clone(const til_Bool* til_Bool_self) {
    return (til_Bool){.data = til_Bool_self->data};
    return (til_Bool){0};
}

int til_I64_safe_div(til_I64* _ret, const til_I64* til_I64_a, const til_I64* til_I64_b) {
    til_I64 _tmp_til_I64_safe_div_0 = 0;
    if (til_I64_eq(til_I64_b, &_tmp_til_I64_safe_div_0).data) {
        return 1;
    }
    *_ret = til_I64_div(til_I64_a, til_I64_b);
    return 0;
    return 0;
}

int til_I64_safe_add(til_I64* _ret, til_I64_Overflow* _err1, const til_I64* til_I64_a, const til_I64* til_I64_b) {
    const til_I64 til_I64_result = til_I64_add(til_I64_a, til_I64_b);
    til_I64 _tmp_til_I64_safe_add_0 = 0;
    if (til_I64_gt(til_I64_b, &_tmp_til_I64_safe_add_0).data) {
        if (til_I64_lt(&til_I64_result, til_I64_a).data) {
            til_Str _tmp_til_I64_safe_add_1;
            til_Array _tmp_til_I64_safe_add_2;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_I64_safe_add_3;
            til_Str _tmp_til_I64_safe_add_4 = ((til_Str){((til_Ptr){(til_I64)"I64 overflow: ", 1}), 14, 0});
            til_Str _tmp_til_I64_safe_add_5 = til_I64_to_str(til_I64_a);
            til_Str _tmp_til_I64_safe_add_6 = ((til_Str){((til_Ptr){(til_I64)" + ", 1}), 3, 0});
            til_Str _tmp_til_I64_safe_add_7 = til_I64_to_str(til_I64_b);
            til_Type _tmp_til_I64_safe_add_8 = "Str";
            til_I64 _tmp_til_I64_safe_add_9 = 4;
            _tmp_til_I64_safe_add_2 = til_Array_new(_tmp_til_I64_safe_add_8, &_tmp_til_I64_safe_add_9);
            int __attribute__((unused)) _arr_status__tmp_til_I64_safe_add_3;
            til_I64 _tmp_til_I64_safe_add_10 = 0;
            _arr_status__tmp_til_I64_safe_add_3 = til_Array_set(&_err_idx__tmp_til_I64_safe_add_3, &_tmp_til_I64_safe_add_2, &_tmp_til_I64_safe_add_10, (til_Dynamic*)&_tmp_til_I64_safe_add_4);
            til_I64 _tmp_til_I64_safe_add_11 = 1;
            _arr_status__tmp_til_I64_safe_add_3 = til_Array_set(&_err_idx__tmp_til_I64_safe_add_3, &_tmp_til_I64_safe_add_2, &_tmp_til_I64_safe_add_11, (til_Dynamic*)&_tmp_til_I64_safe_add_5);
            til_I64 _tmp_til_I64_safe_add_12 = 2;
            _arr_status__tmp_til_I64_safe_add_3 = til_Array_set(&_err_idx__tmp_til_I64_safe_add_3, &_tmp_til_I64_safe_add_2, &_tmp_til_I64_safe_add_12, (til_Dynamic*)&_tmp_til_I64_safe_add_6);
            til_I64 _tmp_til_I64_safe_add_13 = 3;
            _arr_status__tmp_til_I64_safe_add_3 = til_Array_set(&_err_idx__tmp_til_I64_safe_add_3, &_tmp_til_I64_safe_add_2, &_tmp_til_I64_safe_add_13, (til_Dynamic*)&_tmp_til_I64_safe_add_7);
            _tmp_til_I64_safe_add_1 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/i64.til:37:47:", 1}), 23, 0}), &_tmp_til_I64_safe_add_2);
            til_Array_delete(&_tmp_til_I64_safe_add_2);
            *_err1 = (til_I64_Overflow){.msg = _tmp_til_I64_safe_add_1};
            return 1;
        }
    }
    til_I64 _tmp_til_I64_safe_add_14 = 0;
    if (til_I64_lt(til_I64_b, &_tmp_til_I64_safe_add_14).data) {
        if (til_I64_gt(&til_I64_result, til_I64_a).data) {
            til_Str _tmp_til_I64_safe_add_15;
            til_Array _tmp_til_I64_safe_add_16;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_I64_safe_add_17;
            til_Str _tmp_til_I64_safe_add_18 = ((til_Str){((til_Ptr){(til_I64)"I64 overflow: ", 1}), 14, 0});
            til_Str _tmp_til_I64_safe_add_19 = til_I64_to_str(til_I64_a);
            til_Str _tmp_til_I64_safe_add_20 = ((til_Str){((til_Ptr){(til_I64)" + ", 1}), 3, 0});
            til_Str _tmp_til_I64_safe_add_21 = til_I64_to_str(til_I64_b);
            til_Type _tmp_til_I64_safe_add_22 = "Str";
            til_I64 _tmp_til_I64_safe_add_23 = 4;
            _tmp_til_I64_safe_add_16 = til_Array_new(_tmp_til_I64_safe_add_22, &_tmp_til_I64_safe_add_23);
            int __attribute__((unused)) _arr_status__tmp_til_I64_safe_add_17;
            til_I64 _tmp_til_I64_safe_add_24 = 0;
            _arr_status__tmp_til_I64_safe_add_17 = til_Array_set(&_err_idx__tmp_til_I64_safe_add_17, &_tmp_til_I64_safe_add_16, &_tmp_til_I64_safe_add_24, (til_Dynamic*)&_tmp_til_I64_safe_add_18);
            til_I64 _tmp_til_I64_safe_add_25 = 1;
            _arr_status__tmp_til_I64_safe_add_17 = til_Array_set(&_err_idx__tmp_til_I64_safe_add_17, &_tmp_til_I64_safe_add_16, &_tmp_til_I64_safe_add_25, (til_Dynamic*)&_tmp_til_I64_safe_add_19);
            til_I64 _tmp_til_I64_safe_add_26 = 2;
            _arr_status__tmp_til_I64_safe_add_17 = til_Array_set(&_err_idx__tmp_til_I64_safe_add_17, &_tmp_til_I64_safe_add_16, &_tmp_til_I64_safe_add_26, (til_Dynamic*)&_tmp_til_I64_safe_add_20);
            til_I64 _tmp_til_I64_safe_add_27 = 3;
            _arr_status__tmp_til_I64_safe_add_17 = til_Array_set(&_err_idx__tmp_til_I64_safe_add_17, &_tmp_til_I64_safe_add_16, &_tmp_til_I64_safe_add_27, (til_Dynamic*)&_tmp_til_I64_safe_add_21);
            _tmp_til_I64_safe_add_15 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/i64.til:42:47:", 1}), 23, 0}), &_tmp_til_I64_safe_add_16);
            til_Array_delete(&_tmp_til_I64_safe_add_16);
            *_err1 = (til_I64_Overflow){.msg = _tmp_til_I64_safe_add_15};
            return 1;
        }
    }
    *_ret = til_I64_result;
    return 0;
    return 0;
}

int til_I64_safe_sub(til_I64* _ret, til_I64_Overflow* _err1, const til_I64* til_I64_a, const til_I64* til_I64_b) {
    const til_I64 til_I64_result = til_I64_sub(til_I64_a, til_I64_b);
    til_I64 _tmp_til_I64_safe_sub_0 = 0;
    if (til_I64_gt(til_I64_b, &_tmp_til_I64_safe_sub_0).data) {
        if (til_I64_gt(&til_I64_result, til_I64_a).data) {
            til_Str _tmp_til_I64_safe_sub_1;
            til_Array _tmp_til_I64_safe_sub_2;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_I64_safe_sub_3;
            til_Str _tmp_til_I64_safe_sub_4 = ((til_Str){((til_Ptr){(til_I64)"I64 underflow: ", 1}), 15, 0});
            til_Str _tmp_til_I64_safe_sub_5 = til_I64_to_str(til_I64_a);
            til_Str _tmp_til_I64_safe_sub_6 = ((til_Str){((til_Ptr){(til_I64)" - ", 1}), 3, 0});
            til_Str _tmp_til_I64_safe_sub_7 = til_I64_to_str(til_I64_b);
            til_Type _tmp_til_I64_safe_sub_8 = "Str";
            til_I64 _tmp_til_I64_safe_sub_9 = 4;
            _tmp_til_I64_safe_sub_2 = til_Array_new(_tmp_til_I64_safe_sub_8, &_tmp_til_I64_safe_sub_9);
            int __attribute__((unused)) _arr_status__tmp_til_I64_safe_sub_3;
            til_I64 _tmp_til_I64_safe_sub_10 = 0;
            _arr_status__tmp_til_I64_safe_sub_3 = til_Array_set(&_err_idx__tmp_til_I64_safe_sub_3, &_tmp_til_I64_safe_sub_2, &_tmp_til_I64_safe_sub_10, (til_Dynamic*)&_tmp_til_I64_safe_sub_4);
            til_I64 _tmp_til_I64_safe_sub_11 = 1;
            _arr_status__tmp_til_I64_safe_sub_3 = til_Array_set(&_err_idx__tmp_til_I64_safe_sub_3, &_tmp_til_I64_safe_sub_2, &_tmp_til_I64_safe_sub_11, (til_Dynamic*)&_tmp_til_I64_safe_sub_5);
            til_I64 _tmp_til_I64_safe_sub_12 = 2;
            _arr_status__tmp_til_I64_safe_sub_3 = til_Array_set(&_err_idx__tmp_til_I64_safe_sub_3, &_tmp_til_I64_safe_sub_2, &_tmp_til_I64_safe_sub_12, (til_Dynamic*)&_tmp_til_I64_safe_sub_6);
            til_I64 _tmp_til_I64_safe_sub_13 = 3;
            _arr_status__tmp_til_I64_safe_sub_3 = til_Array_set(&_err_idx__tmp_til_I64_safe_sub_3, &_tmp_til_I64_safe_sub_2, &_tmp_til_I64_safe_sub_13, (til_Dynamic*)&_tmp_til_I64_safe_sub_7);
            _tmp_til_I64_safe_sub_1 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/i64.til:55:47:", 1}), 23, 0}), &_tmp_til_I64_safe_sub_2);
            til_Array_delete(&_tmp_til_I64_safe_sub_2);
            *_err1 = (til_I64_Overflow){.msg = _tmp_til_I64_safe_sub_1};
            return 1;
        }
    }
    til_I64 _tmp_til_I64_safe_sub_14 = 0;
    if (til_I64_lt(til_I64_b, &_tmp_til_I64_safe_sub_14).data) {
        if (til_I64_lt(&til_I64_result, til_I64_a).data) {
            til_Str _tmp_til_I64_safe_sub_15;
            til_Array _tmp_til_I64_safe_sub_16;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_I64_safe_sub_17;
            til_Str _tmp_til_I64_safe_sub_18 = ((til_Str){((til_Ptr){(til_I64)"I64 underflow: ", 1}), 15, 0});
            til_Str _tmp_til_I64_safe_sub_19 = til_I64_to_str(til_I64_a);
            til_Str _tmp_til_I64_safe_sub_20 = ((til_Str){((til_Ptr){(til_I64)" - ", 1}), 3, 0});
            til_Str _tmp_til_I64_safe_sub_21 = til_I64_to_str(til_I64_b);
            til_Type _tmp_til_I64_safe_sub_22 = "Str";
            til_I64 _tmp_til_I64_safe_sub_23 = 4;
            _tmp_til_I64_safe_sub_16 = til_Array_new(_tmp_til_I64_safe_sub_22, &_tmp_til_I64_safe_sub_23);
            int __attribute__((unused)) _arr_status__tmp_til_I64_safe_sub_17;
            til_I64 _tmp_til_I64_safe_sub_24 = 0;
            _arr_status__tmp_til_I64_safe_sub_17 = til_Array_set(&_err_idx__tmp_til_I64_safe_sub_17, &_tmp_til_I64_safe_sub_16, &_tmp_til_I64_safe_sub_24, (til_Dynamic*)&_tmp_til_I64_safe_sub_18);
            til_I64 _tmp_til_I64_safe_sub_25 = 1;
            _arr_status__tmp_til_I64_safe_sub_17 = til_Array_set(&_err_idx__tmp_til_I64_safe_sub_17, &_tmp_til_I64_safe_sub_16, &_tmp_til_I64_safe_sub_25, (til_Dynamic*)&_tmp_til_I64_safe_sub_19);
            til_I64 _tmp_til_I64_safe_sub_26 = 2;
            _arr_status__tmp_til_I64_safe_sub_17 = til_Array_set(&_err_idx__tmp_til_I64_safe_sub_17, &_tmp_til_I64_safe_sub_16, &_tmp_til_I64_safe_sub_26, (til_Dynamic*)&_tmp_til_I64_safe_sub_20);
            til_I64 _tmp_til_I64_safe_sub_27 = 3;
            _arr_status__tmp_til_I64_safe_sub_17 = til_Array_set(&_err_idx__tmp_til_I64_safe_sub_17, &_tmp_til_I64_safe_sub_16, &_tmp_til_I64_safe_sub_27, (til_Dynamic*)&_tmp_til_I64_safe_sub_21);
            _tmp_til_I64_safe_sub_15 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/i64.til:60:47:", 1}), 23, 0}), &_tmp_til_I64_safe_sub_16);
            til_Array_delete(&_tmp_til_I64_safe_sub_16);
            *_err1 = (til_I64_Overflow){.msg = _tmp_til_I64_safe_sub_15};
            return 1;
        }
    }
    *_ret = til_I64_result;
    return 0;
    return 0;
}

int til_I64_safe_mul(til_I64* _ret, til_I64_Overflow* _err1, const til_I64* til_I64_a, const til_I64* til_I64_b) {
    const til_I64 til_I64_result = til_I64_mul(til_I64_a, til_I64_b);
    til_I64 _tmp_til_I64_safe_mul_0 = 0;
    til_Bool _tmp_til_I64_safe_mul_1 = til_I64_eq(til_I64_a, &_tmp_til_I64_safe_mul_0);
    if (til_not(&_tmp_til_I64_safe_mul_1).data) {
        til_I64 _tmp_til_I64_safe_mul_2 = til_I64_div(&til_I64_result, til_I64_a);
        til_Bool _tmp_til_I64_safe_mul_3 = til_I64_eq(&_tmp_til_I64_safe_mul_2, til_I64_b);
        if (til_not(&_tmp_til_I64_safe_mul_3).data) {
            til_Str _tmp_til_I64_safe_mul_4;
            til_Array _tmp_til_I64_safe_mul_5;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_I64_safe_mul_6;
            til_Str _tmp_til_I64_safe_mul_7 = ((til_Str){((til_Ptr){(til_I64)"I64 overflow: ", 1}), 14, 0});
            til_Str _tmp_til_I64_safe_mul_8 = til_I64_to_str(til_I64_a);
            til_Str _tmp_til_I64_safe_mul_9 = ((til_Str){((til_Ptr){(til_I64)" * ", 1}), 3, 0});
            til_Str _tmp_til_I64_safe_mul_10 = til_I64_to_str(til_I64_b);
            til_Type _tmp_til_I64_safe_mul_11 = "Str";
            til_I64 _tmp_til_I64_safe_mul_12 = 4;
            _tmp_til_I64_safe_mul_5 = til_Array_new(_tmp_til_I64_safe_mul_11, &_tmp_til_I64_safe_mul_12);
            int __attribute__((unused)) _arr_status__tmp_til_I64_safe_mul_6;
            til_I64 _tmp_til_I64_safe_mul_13 = 0;
            _arr_status__tmp_til_I64_safe_mul_6 = til_Array_set(&_err_idx__tmp_til_I64_safe_mul_6, &_tmp_til_I64_safe_mul_5, &_tmp_til_I64_safe_mul_13, (til_Dynamic*)&_tmp_til_I64_safe_mul_7);
            til_I64 _tmp_til_I64_safe_mul_14 = 1;
            _arr_status__tmp_til_I64_safe_mul_6 = til_Array_set(&_err_idx__tmp_til_I64_safe_mul_6, &_tmp_til_I64_safe_mul_5, &_tmp_til_I64_safe_mul_14, (til_Dynamic*)&_tmp_til_I64_safe_mul_8);
            til_I64 _tmp_til_I64_safe_mul_15 = 2;
            _arr_status__tmp_til_I64_safe_mul_6 = til_Array_set(&_err_idx__tmp_til_I64_safe_mul_6, &_tmp_til_I64_safe_mul_5, &_tmp_til_I64_safe_mul_15, (til_Dynamic*)&_tmp_til_I64_safe_mul_9);
            til_I64 _tmp_til_I64_safe_mul_16 = 3;
            _arr_status__tmp_til_I64_safe_mul_6 = til_Array_set(&_err_idx__tmp_til_I64_safe_mul_6, &_tmp_til_I64_safe_mul_5, &_tmp_til_I64_safe_mul_16, (til_Dynamic*)&_tmp_til_I64_safe_mul_10);
            _tmp_til_I64_safe_mul_4 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/i64.til:73:47:", 1}), 23, 0}), &_tmp_til_I64_safe_mul_5);
            til_Array_delete(&_tmp_til_I64_safe_mul_5);
            *_err1 = (til_I64_Overflow){.msg = _tmp_til_I64_safe_mul_4};
            return 1;
        }
    }
    *_ret = til_I64_result;
    return 0;
    return 0;
}

til_I64 til_I64_xor(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    return til_i64_xor(til_I64_a, til_I64_b);
    return (til_I64){0};
}

til_I64 til_I64_and(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    return til_i64_and(til_I64_a, til_I64_b);
    return (til_I64){0};
}

til_I64 til_I64_or(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    return til_i64_or(til_I64_a, til_I64_b);
    return (til_I64){0};
}

til_I64 til_I64_mod(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    return til_i64_mod(til_I64_a, til_I64_b);
    return (til_I64){0};
}

til_I64 til_I64_sub(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    return til_i64_sub(til_I64_a, til_I64_b);
    return (til_I64){0};
}

til_I64 til_I64_mul(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    return til_i64_mul(til_I64_a, til_I64_b);
    return (til_I64){0};
}

til_I64 til_I64_div(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    return til_i64_div(til_I64_a, til_I64_b);
    return (til_I64){0};
}

til_I64 til_I64_add(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    return til_i64_add(til_I64_a, til_I64_b);
    return (til_I64){0};
}

til_Bool til_I64_eq(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    if (til_I64_gt(til_I64_a, til_I64_b).data) {
        return false;
    }
    if (til_I64_gt(til_I64_b, til_I64_a).data) {
        return false;
    }
    if (til_I64_lt(til_I64_a, til_I64_b).data) {
        return false;
    }
    if (til_I64_lt(til_I64_b, til_I64_a).data) {
        return false;
    }
    return true;
    return (til_Bool){0};
}

til_Bool til_I64_lt(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    return til_i64_lt(til_I64_a, til_I64_b);
    return (til_Bool){0};
}

til_Bool til_I64_gt(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    return til_i64_gt(til_I64_a, til_I64_b);
    return (til_Bool){0};
}

til_Str til_I64_to_str(const til_I64* til_I64_self) {
    return til_i64_to_str(til_I64_self);
    return (til_Str){0};
}

til_I64 til_I64_from_str(const til_Str* til_Str_str) {
    return til_str_to_i64(til_Str_str);
    return (til_I64){0};
}

void til_I64_inc(til_I64* til_I64_self) {
    til_I64 _tmp_til_I64_inc_0 = 1;
    *til_I64_self = til_I64_add(til_I64_self, &_tmp_til_I64_inc_0);
}

void til_I64_dec(til_I64* til_I64_self) {
    til_I64 _tmp_til_I64_dec_0 = 1;
    *til_I64_self = til_I64_sub(til_I64_self, &_tmp_til_I64_dec_0);
}

til_Bool til_I64_gteq(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    if (til_I64_gt(til_I64_a, til_I64_b).data) {
        return true;
    }
    if (til_I64_lt(til_I64_a, til_I64_b).data) {
        return false;
    }
    return true;
    return (til_Bool){0};
}

til_Bool til_I64_lteq(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    if (til_I64_lt(til_I64_a, til_I64_b).data) {
        return true;
    }
    if (til_I64_gt(til_I64_a, til_I64_b).data) {
        return false;
    }
    return true;
    return (til_Bool){0};
}

til_I64 til_I64_size(void) {
    return 8;
    return (til_I64){0};
}

void til_I64_delete(til_I64* _self) {
}

til_I64 til_I64_clone(const til_I64* til_I64_self) {
    return (*til_I64_self);
    return (til_I64){0};
}

til_I64 til_Ptr_size_of(void) {
    return til_size_of(&((til_Str){((til_Ptr){(til_I64)"I64", 1}), 3, 0}));
    return (til_I64){0};
}

til_Bool til_Ptr_is_null(const til_Ptr* til_Ptr_self) {
    return til_I64_eq(&til_I64_NULL, &til_Ptr_self->data);
    return (til_Bool){0};
}

void til_CfVec2_delete(til_CfVec2* _self) {
}

til_CfVec2 til_CfVec2_clone(const til_CfVec2* til_CfVec2_self) {
    return (til_CfVec2){.x = til_CfVec2_self->x, .y = til_CfVec2_self->y};
    return (til_CfVec2){0};
}

void til_CfRect_delete(til_CfRect* til_CfRect_self) {
    til_CfVec2_delete(&til_CfRect_self->bottom_right);
    til_CfVec2_delete(&til_CfRect_self->top_left);
}

til_CfRect til_CfRect_clone(const til_CfRect* til_CfRect_self) {
    return (til_CfRect){.top_left = til_CfVec2_clone(&til_CfRect_self->top_left), .bottom_right = til_CfVec2_clone(&til_CfRect_self->bottom_right)};
    return (til_CfRect){0};
}

int main(int argc, char** argv) {
    (void)argc; (void)argv;
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
