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
til_Bool til_xor(const til_Bool til_a, const til_Bool til_b);
til_Bool til_xnor(const til_Bool til_a, const til_Bool til_b);
til_I64 til_branchless(const til_Bool til_cond, const til_I64 til_a, const til_I64 til_b);
void til_panic(const til_Str til_loc_str, til_Array* til_msgs);
void til_assertm(const til_Str til_loc_str, const til_Bool til_cond, const til_Str til_msg);
void til_assert(const til_Str til_loc_str, const til_Bool til_cond);
void til_TODO(const til_Str til_loc_str, const til_Str til_msg);
til_Bool til_lteq(const til_I64 til_a, const til_I64 til_b);
til_Bool til_gteq(const til_I64 til_a, const til_I64 til_b);
void til_print(til_Array* til_args);
void til_println(til_Array* til_args);
int til_get_substr(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_start, const til_I64 til_end);
int til_get_char(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_pos);
til_Bool til_starts_with(const til_Str til_s, const til_Str til_prefix);
til_Str til_concat(const til_Str til_a, const til_Str til_b);
int til_format(til_Str* _ret, til_I64_OverflowError* _err1, til_IndexOutOfBoundsError* _err2, til_AllocError* _err3, const til_Str til_prefix, til_Array* til_args);
void til_test(const til_Str til_loc_str, const til_Bool til_cond, const til_Str til_msg);
void til_assert_eq_str(const til_Str til_loc_str, const til_Str til_a, const til_Str til_b);
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
til_IndexOutOfBoundsError til_IndexOutOfBoundsError_new(const til_Str til_msg);
til_AllocError til_AllocError_new(const til_Str til_msg);
til_I64 til_Array_len(const til_Array til_self);
til_I64 til_Array_size(const til_Array til_self);
int til_Array_new(til_Array* _ret, til_AllocError* _err1, const til_Type til_T, const til_I64 til_capacity);
int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array til_self, const til_I64 til_index, til_Dynamic* til_T);
int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64 til_index, const til_Dynamic til_value);
void til_Array_delete(til_Array* til_self);
int til_Array_clone(til_Array* _ret, til_AllocError* _err1, const til_Array til_self);
til_Bool til_Array_contains(const til_Array til_self, const til_Str til_value);
til_I64 til_Bool_len(const til_Bool til_self);
til_Bool til_Bool_eq(const til_Bool til_a, const til_Bool til_b);
til_Str til_Bool_to_str(const til_Bool til_self);
til_I64 til_Bool_to_i64(const til_Bool til_self);
til_U8 til_Bool_to_u8(const til_Bool til_self);
til_Bool til_Bool_from_i64(const til_I64 til_i);
til_I64 til_Bool_size(void);
til_I64_OverflowError til_I64_OverflowError_new(const til_Str til_msg);
til_Bool til_I64_eq(const til_I64 til_a, const til_I64 til_b);
til_Str til_I64_to_str(const til_I64 til_self);
til_I64 til_I64_from_str(const til_Str til_str);
void til_I64_inc(til_I64* til_self);
void til_I64_dec(til_I64* til_self);
til_I64 til_I64___add__(const til_I64 til_self, const til_I64 til_other);
til_I64 til_I64_size(void);
til_I64 til_Vec_len(const til_Vec til_self);
til_I64 til_Vec_size(const til_Vec til_self);
int til_Vec_new(til_Vec* _ret, til_AllocError* _err1, const til_Type til_T);
int til_Vec_new_from_type_info(til_Vec* _ret, til_AllocError* _err1, const til_Str til_type_name, const til_I64 til_type_size);
int til_Vec_push(til_AllocError* _err1, til_Vec* til_self, const til_Dynamic til_value);
int til_Vec_get(til_IndexOutOfBoundsError* _err1, const til_Vec til_self, const til_I64 til_index, til_Dynamic* til_T);
int til_Vec_set(til_IndexOutOfBoundsError* _err1, til_Vec* til_self, const til_I64 til_index, const til_Dynamic til_value);
int til_Vec_pop(til_IndexOutOfBoundsError* _err1, til_Vec* til_self, til_Dynamic* til_dest);
void til_Vec_delete(til_Vec* til_self);
int til_Vec_clone(til_Vec* _ret, til_AllocError* _err1, const til_Vec til_self);
int til_Vec_extend(til_AllocError* _err1, til_Vec* til_self, const til_Vec til_other);
til_Bool til_Vec_contains(const til_Vec til_self, const til_Dynamic til_value);
int til_Vec_remove(til_IndexOutOfBoundsError* _err1, til_Vec* til_self, const til_I64 til_index);
til_I64 til_Str_len(const til_Str til_self);
til_Bool til_Str_eq(const til_Str til_self, const til_Str til_other);
til_I64 til_Str_to_i64(const til_Str til_self);
int til_Str_clone(til_Str* _ret, til_AllocError* _err1, const til_Str til_self);
til_I64 til_Str_size(const til_Str til_self);
til_Bool til_Str_is_uppercase(const til_Str til_self);
til_Bool til_Str_contains(const til_Str til_self, const til_Str til_needle);
til_I64 til_Str_find(const til_Str til_self, const til_Str til_needle);
til_I64 til_Str_rfind(const til_Str til_self, const til_Str til_needle);
int til_Str_replace(til_Str* _ret, til_AllocError* _err1, const til_Str til_self, const til_Str til_from, const til_Str til_to);
til_U8 til_Str_char_at(const til_Str til_self, const til_I64 til_index);
int til_Str_replacen(til_Str* _ret, til_AllocError* _err1, const til_Str til_self, const til_Str til_from, const til_Str til_to, const til_I64 til_n);
int til_Str_split(til_Vec* _ret, til_AllocError* _err1, til_IndexOutOfBoundsError* _err2, const til_Str til_self, const til_Str til_delimiter);
til_U8_OverflowError til_U8_OverflowError_new(const til_Str til_msg);
til_I64 til_U8_len(const til_I64 til_self);
til_Bool til_U8_eq(const til_U8 til_self, const til_U8 til_other);
til_Bool til_U8_lt(const til_U8 til_self, const til_U8 til_other);
til_Bool til_U8_gt(const til_U8 til_self, const til_U8 til_other);
til_I64 til_U8_to_i64(const til_U8 til_self);
int til_U8_u8_add(til_U8* _ret, til_U8_OverflowError* _err1, const til_U8 til_a, const til_U8 til_b);
int til_U8_from_i64(til_U8* _ret, til_U8_OverflowError* _err1, const til_I64 til_self);
til_Str til_U8_to_str(const til_U8 til_self);
int til_U8_from_str(til_U8* _ret, til_U8_OverflowError* _err1, const til_Str til_s);
til_I64 til_U8_size(void);
til_Bool til_Introspection_has_const(const til_Str til_type_name, const til_Str til_const_name);
til_Bool til_Introspection_has_field(const til_Str til_type_name, const til_Str til_field_name);
til_CfVec2 til_CfVec2_magic(void);
til_CfVec2 til_CfVec2_at(const til_I64 til_x, const til_I64 til_y);
til_CfRect til_CfRect_sample(void);

#include "ext.c"

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
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp2;
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Bool til_val = false;
        til_IndexOutOfBoundsError _err0__tmp5 = {};
        int _status__tmp5 = til_Array_get(&_err0__tmp5, (*til_args), til_i, (til_Dynamic*)&til_val);
        if (_status__tmp5 == 1) { _thrown_IndexOutOfBoundsError__tmp2 = _err0__tmp5; goto _catch_IndexOutOfBoundsError__tmp2; }
        if (til_val.data) {
            return true;
        }
        til_I64_inc(&til_i);
    }
    return false;
    goto _end_catches__tmp2;
_catch_IndexOutOfBoundsError__tmp2: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp2;
    til_Array _tmp8;
    til_AllocError _err_alloc__tmp9;
    til_IndexOutOfBoundsError _err_idx__tmp9;
    til_Str _tmp10 = ((til_Str){(til_I64)"or: IndexOutOfBoundsError should never happen", 45});
    int _arr_status__tmp9 = til_Array_new(&_tmp8, &_err_alloc__tmp9, "Str", 1);
    if (_arr_status__tmp9 != 0) {
    }
    _arr_status__tmp9 = til_Array_set(&_err_idx__tmp9, &_tmp8, 0, &_tmp10);
    if (_arr_status__tmp9 != 0) {
    }
    til_panic(((til_Str){(til_I64)"src/test/constfold.til:69:15:", 29}), &_tmp8);
    til_Array_delete(&_tmp8);
    }
_end_catches__tmp2:;
}

til_Bool til_and(til_Array* til_args) {
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp11;
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Bool til_val = false;
        til_IndexOutOfBoundsError _err0__tmp14 = {};
        int _status__tmp14 = til_Array_get(&_err0__tmp14, (*til_args), til_i, (til_Dynamic*)&til_val);
        if (_status__tmp14 == 1) { _thrown_IndexOutOfBoundsError__tmp11 = _err0__tmp14; goto _catch_IndexOutOfBoundsError__tmp11; }
        if (til_not(til_val).data) {
            return false;
        }
        til_I64_inc(&til_i);
    }
    return true;
    goto _end_catches__tmp11;
_catch_IndexOutOfBoundsError__tmp11: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp11;
    til_Array _tmp17;
    til_AllocError _err_alloc__tmp18;
    til_IndexOutOfBoundsError _err_idx__tmp18;
    til_Str _tmp19 = ((til_Str){(til_I64)"and: IndexOutOfBoundsError should never happen", 46});
    int _arr_status__tmp18 = til_Array_new(&_tmp17, &_err_alloc__tmp18, "Str", 1);
    if (_arr_status__tmp18 != 0) {
    }
    _arr_status__tmp18 = til_Array_set(&_err_idx__tmp18, &_tmp17, 0, &_tmp19);
    if (_arr_status__tmp18 != 0) {
    }
    til_panic(((til_Str){(til_I64)"src/test/constfold.til:85:15:", 29}), &_tmp17);
    til_Array_delete(&_tmp17);
    }
_end_catches__tmp11:;
}

til_Bool til_xor(const til_Bool til_a, const til_Bool til_b) {
    return til_not(til_Bool_eq(til_a, til_b));
}

til_Bool til_xnor(const til_Bool til_a, const til_Bool til_b) {
    return til_Bool_eq(til_a, til_b);
}

til_I64 til_branchless(const til_Bool til_cond, const til_I64 til_a, const til_I64 til_b) {
    return til_add(til_mul(til_a, til_Bool_to_i64(til_cond)), til_mul(til_b, til_Bool_to_i64(til_not(til_cond))));
}

void til_panic(const til_Str til_loc_str, til_Array* til_msgs) {
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp23;
    til_single_print(til_loc_str);
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_msgs))).data) {
        til_Str til_val = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp26 = {};
        int _status__tmp26 = til_Array_get(&_err0__tmp26, (*til_msgs), til_i, (til_Dynamic*)&til_val);
        if (_status__tmp26 == 1) { _thrown_IndexOutOfBoundsError__tmp23 = _err0__tmp26; goto _catch_IndexOutOfBoundsError__tmp23; }
        til_single_print(til_val);
        til_I64_inc(&til_i);
    }
    til_single_print(((til_Str){(til_I64)"\n", 1}));
    til_print_flush();
    til_exit(1);
    goto _end_catches__tmp23;
_catch_IndexOutOfBoundsError__tmp23: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp23;
    til_single_print(((til_Str){(til_I64)"panic: IndexOutOfBoundsError should never happen\n", 49}));
    til_print_flush();
    til_exit(1);
    }
_end_catches__tmp23:;
}

void til_assertm(const til_Str til_loc_str, const til_Bool til_cond, const til_Str til_msg) {
    if (til_not(til_cond).data) {
        til_Str _tmp30;
        til_I64_OverflowError _err0__tmp31;
        til_IndexOutOfBoundsError _err1__tmp31;
        til_AllocError _err2__tmp31;
        til_Array _tmp32;
        til_AllocError _err_alloc__tmp33;
        til_IndexOutOfBoundsError _err_idx__tmp33;
        til_Str _tmp34 = til_msg;
        int _arr_status__tmp33 = til_Array_new(&_tmp32, &_err_alloc__tmp33, "Str", 1);
        if (_arr_status__tmp33 != 0) {
        }
        _arr_status__tmp33 = til_Array_set(&_err_idx__tmp33, &_tmp32, 0, &_tmp34);
        if (_arr_status__tmp33 != 0) {
        }
        int _status__tmp31 = til_format(&_tmp30, &_err0__tmp31, &_err1__tmp31, &_err2__tmp31, ((til_Str){(til_I64)"assert failed: ", 15}), &_tmp32);
        if (_status__tmp31 != 0) {
        }
        til_Array_delete(&_tmp32);
        til_Array _tmp35;
        til_AllocError _err_alloc__tmp36;
        til_IndexOutOfBoundsError _err_idx__tmp36;
        int _arr_status__tmp36 = til_Array_new(&_tmp35, &_err_alloc__tmp36, "Str", 1);
        if (_arr_status__tmp36 != 0) {
        }
        _arr_status__tmp36 = til_Array_set(&_err_idx__tmp36, &_tmp35, 0, &_tmp30);
        if (_arr_status__tmp36 != 0) {
        }
        til_panic(til_loc_str, &_tmp35);
        til_Array_delete(&_tmp35);
    }
}

void til_assert(const til_Str til_loc_str, const til_Bool til_cond) {
    til_assertm(til_loc_str, til_cond, ((til_Str){(til_I64)"", 0}));
}

void til_TODO(const til_Str til_loc_str, const til_Str til_msg) {
    til_Str _tmp39;
    til_I64_OverflowError _err0__tmp40;
    til_IndexOutOfBoundsError _err1__tmp40;
    til_AllocError _err2__tmp40;
    til_Array _tmp41;
    til_AllocError _err_alloc__tmp42;
    til_IndexOutOfBoundsError _err_idx__tmp42;
    til_Str _tmp43 = til_msg;
    int _arr_status__tmp42 = til_Array_new(&_tmp41, &_err_alloc__tmp42, "Str", 1);
    if (_arr_status__tmp42 != 0) {
    }
    _arr_status__tmp42 = til_Array_set(&_err_idx__tmp42, &_tmp41, 0, &_tmp43);
    if (_arr_status__tmp42 != 0) {
    }
    int _status__tmp40 = til_format(&_tmp39, &_err0__tmp40, &_err1__tmp40, &_err2__tmp40, ((til_Str){(til_I64)"TODO: ", 6}), &_tmp41);
    if (_status__tmp40 != 0) {
    }
    til_Array_delete(&_tmp41);
    til_assertm(til_loc_str, false, _tmp39);
}

til_Bool til_lteq(const til_I64 til_a, const til_I64 til_b) {
    if (til_lt(til_a, til_b).data) {
        return true;
    }
    if (til_I64_eq(til_a, til_b).data) {
        return true;
    }
    return false;
}

til_Bool til_gteq(const til_I64 til_a, const til_I64 til_b) {
    if (til_gt(til_a, til_b).data) {
        return true;
    }
    if (til_I64_eq(til_a, til_b).data) {
        return true;
    }
    return false;
}

void til_print(til_Array* til_args) {
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp50;
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Str til_val = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp53 = {};
        int _status__tmp53 = til_Array_get(&_err0__tmp53, (*til_args), til_i, (til_Dynamic*)&til_val);
        if (_status__tmp53 == 1) { _thrown_IndexOutOfBoundsError__tmp50 = _err0__tmp53; goto _catch_IndexOutOfBoundsError__tmp50; }
        til_single_print(til_val);
        til_I64_inc(&til_i);
    }
    til_print_flush();
    goto _end_catches__tmp50;
_catch_IndexOutOfBoundsError__tmp50: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp50;
    til_Array _tmp55;
    til_AllocError _err_alloc__tmp56;
    til_IndexOutOfBoundsError _err_idx__tmp56;
    til_Str _tmp57 = ((til_Str){(til_I64)"print: IndexOutOfBoundsError should never happen", 48});
    int _arr_status__tmp56 = til_Array_new(&_tmp55, &_err_alloc__tmp56, "Str", 1);
    if (_arr_status__tmp56 != 0) {
    }
    _arr_status__tmp56 = til_Array_set(&_err_idx__tmp56, &_tmp55, 0, &_tmp57);
    if (_arr_status__tmp56 != 0) {
    }
    til_panic(((til_Str){(til_I64)"src/test/constfold.til:17:15:", 29}), &_tmp55);
    til_Array_delete(&_tmp55);
    }
_end_catches__tmp50:;
}

void til_println(til_Array* til_args) {
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp58;
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Str til_val = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp61 = {};
        int _status__tmp61 = til_Array_get(&_err0__tmp61, (*til_args), til_i, (til_Dynamic*)&til_val);
        if (_status__tmp61 == 1) { _thrown_IndexOutOfBoundsError__tmp58 = _err0__tmp61; goto _catch_IndexOutOfBoundsError__tmp58; }
        til_single_print(til_val);
        til_I64_inc(&til_i);
    }
    til_single_print(((til_Str){(til_I64)"\n", 1}));
    til_print_flush();
    goto _end_catches__tmp58;
_catch_IndexOutOfBoundsError__tmp58: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp58;
    til_Array _tmp63;
    til_AllocError _err_alloc__tmp64;
    til_IndexOutOfBoundsError _err_idx__tmp64;
    til_Str _tmp65 = ((til_Str){(til_I64)"println: IndexOutOfBoundsError should never happen", 50});
    int _arr_status__tmp64 = til_Array_new(&_tmp63, &_err_alloc__tmp64, "Str", 1);
    if (_arr_status__tmp64 != 0) {
    }
    _arr_status__tmp64 = til_Array_set(&_err_idx__tmp64, &_tmp63, 0, &_tmp65);
    if (_arr_status__tmp64 != 0) {
    }
    til_panic(((til_Str){(til_I64)"src/test/constfold.til:31:15:", 29}), &_tmp63);
    til_Array_delete(&_tmp63);
    }
_end_catches__tmp58:;
}

int til_get_substr(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_start, const til_I64 til_end) {
    if (til_lt(til_start, 0).data) {
        til_Str _tmp68;
        til_I64_OverflowError _err0__tmp69;
        til_IndexOutOfBoundsError _err1__tmp69;
        til_AllocError _err2__tmp69;
        til_Array _tmp70;
        til_AllocError _err_alloc__tmp71;
        til_IndexOutOfBoundsError _err_idx__tmp71;
        til_Str _tmp72 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp73 = til_I64_to_str(til_start);
        til_Str _tmp74 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp71 = til_Array_new(&_tmp70, &_err_alloc__tmp71, "Str", 3);
        if (_arr_status__tmp71 != 0) {
            *_err2 = _err_alloc__tmp71; return 2;
        }
        _arr_status__tmp71 = til_Array_set(&_err_idx__tmp71, &_tmp70, 0, &_tmp72);
        if (_arr_status__tmp71 != 0) {
            *_err1 = _err_idx__tmp71; return 1;
        }
        _arr_status__tmp71 = til_Array_set(&_err_idx__tmp71, &_tmp70, 1, &_tmp73);
        if (_arr_status__tmp71 != 0) {
            *_err1 = _err_idx__tmp71; return 1;
        }
        _arr_status__tmp71 = til_Array_set(&_err_idx__tmp71, &_tmp70, 2, &_tmp74);
        if (_arr_status__tmp71 != 0) {
            *_err1 = _err_idx__tmp71; return 1;
        }
        int _status__tmp69 = til_format(&_tmp68, &_err0__tmp69, &_err1__tmp69, &_err2__tmp69, ((til_Str){(til_I64)"src/test/constfold.til:357:48:", 30}), &_tmp70);
        if (_status__tmp69 != 0) {
            if (_status__tmp69 == 2) { *_err1 = _err1__tmp69; return 1; }
            if (_status__tmp69 == 3) { *_err2 = _err2__tmp69; return 2; }
        }
        til_Array_delete(&_tmp70);
        til_Str _tmp75;
        til_I64_OverflowError _err0__tmp76;
        til_IndexOutOfBoundsError _err1__tmp76;
        til_AllocError _err2__tmp76;
        til_Array _tmp77;
        til_AllocError _err_alloc__tmp78;
        til_IndexOutOfBoundsError _err_idx__tmp78;
        til_Str _tmp79 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp80 = til_I64_to_str(til_start);
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
        int _status__tmp76 = til_format(&_tmp75, &_err0__tmp76, &_err1__tmp76, &_err2__tmp76, ((til_Str){(til_I64)"src/test/constfold.til:357:48:", 30}), &_tmp77);
        if (_status__tmp76 != 0) {
            if (_status__tmp76 == 2) { *_err1 = _err1__tmp76; return 1; }
            if (_status__tmp76 == 3) { *_err2 = _err2__tmp76; return 2; }
        }
        til_Array_delete(&_tmp77);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp75);
        return 1;
    }
    if (til_lt(til_end, 0).data) {
        til_Str _tmp83;
        til_I64_OverflowError _err0__tmp84;
        til_IndexOutOfBoundsError _err1__tmp84;
        til_AllocError _err2__tmp84;
        til_Array _tmp85;
        til_AllocError _err_alloc__tmp86;
        til_IndexOutOfBoundsError _err_idx__tmp86;
        til_Str _tmp87 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp88 = til_I64_to_str(til_end);
        til_Str _tmp89 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp86 = til_Array_new(&_tmp85, &_err_alloc__tmp86, "Str", 3);
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
        int _status__tmp84 = til_format(&_tmp83, &_err0__tmp84, &_err1__tmp84, &_err2__tmp84, ((til_Str){(til_I64)"src/test/constfold.til:360:48:", 30}), &_tmp85);
        if (_status__tmp84 != 0) {
            if (_status__tmp84 == 2) { *_err1 = _err1__tmp84; return 1; }
            if (_status__tmp84 == 3) { *_err2 = _err2__tmp84; return 2; }
        }
        til_Array_delete(&_tmp85);
        til_Str _tmp90;
        til_I64_OverflowError _err0__tmp91;
        til_IndexOutOfBoundsError _err1__tmp91;
        til_AllocError _err2__tmp91;
        til_Array _tmp92;
        til_AllocError _err_alloc__tmp93;
        til_IndexOutOfBoundsError _err_idx__tmp93;
        til_Str _tmp94 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp95 = til_I64_to_str(til_end);
        til_Str _tmp96 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp93 = til_Array_new(&_tmp92, &_err_alloc__tmp93, "Str", 3);
        if (_arr_status__tmp93 != 0) {
            *_err2 = _err_alloc__tmp93; return 2;
        }
        _arr_status__tmp93 = til_Array_set(&_err_idx__tmp93, &_tmp92, 0, &_tmp94);
        if (_arr_status__tmp93 != 0) {
            *_err1 = _err_idx__tmp93; return 1;
        }
        _arr_status__tmp93 = til_Array_set(&_err_idx__tmp93, &_tmp92, 1, &_tmp95);
        if (_arr_status__tmp93 != 0) {
            *_err1 = _err_idx__tmp93; return 1;
        }
        _arr_status__tmp93 = til_Array_set(&_err_idx__tmp93, &_tmp92, 2, &_tmp96);
        if (_arr_status__tmp93 != 0) {
            *_err1 = _err_idx__tmp93; return 1;
        }
        int _status__tmp91 = til_format(&_tmp90, &_err0__tmp91, &_err1__tmp91, &_err2__tmp91, ((til_Str){(til_I64)"src/test/constfold.til:360:48:", 30}), &_tmp92);
        if (_status__tmp91 != 0) {
            if (_status__tmp91 == 2) { *_err1 = _err1__tmp91; return 1; }
            if (_status__tmp91 == 3) { *_err2 = _err2__tmp91; return 2; }
        }
        til_Array_delete(&_tmp92);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp90);
        return 1;
    }
    if (til_gt(til_start, til_end).data) {
        til_Str _tmp98;
        til_I64_OverflowError _err0__tmp99;
        til_IndexOutOfBoundsError _err1__tmp99;
        til_AllocError _err2__tmp99;
        til_Array _tmp100;
        til_AllocError _err_alloc__tmp101;
        til_IndexOutOfBoundsError _err_idx__tmp101;
        til_Str _tmp102 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp103 = til_I64_to_str(til_start);
        til_Str _tmp104 = ((til_Str){(til_I64)" is greater than end index ", 27});
        til_Str _tmp105 = til_I64_to_str(til_end);
        int _arr_status__tmp101 = til_Array_new(&_tmp100, &_err_alloc__tmp101, "Str", 4);
        if (_arr_status__tmp101 != 0) {
            *_err2 = _err_alloc__tmp101; return 2;
        }
        _arr_status__tmp101 = til_Array_set(&_err_idx__tmp101, &_tmp100, 0, &_tmp102);
        if (_arr_status__tmp101 != 0) {
            *_err1 = _err_idx__tmp101; return 1;
        }
        _arr_status__tmp101 = til_Array_set(&_err_idx__tmp101, &_tmp100, 1, &_tmp103);
        if (_arr_status__tmp101 != 0) {
            *_err1 = _err_idx__tmp101; return 1;
        }
        _arr_status__tmp101 = til_Array_set(&_err_idx__tmp101, &_tmp100, 2, &_tmp104);
        if (_arr_status__tmp101 != 0) {
            *_err1 = _err_idx__tmp101; return 1;
        }
        _arr_status__tmp101 = til_Array_set(&_err_idx__tmp101, &_tmp100, 3, &_tmp105);
        if (_arr_status__tmp101 != 0) {
            *_err1 = _err_idx__tmp101; return 1;
        }
        int _status__tmp99 = til_format(&_tmp98, &_err0__tmp99, &_err1__tmp99, &_err2__tmp99, ((til_Str){(til_I64)"src/test/constfold.til:363:48:", 30}), &_tmp100);
        if (_status__tmp99 != 0) {
            if (_status__tmp99 == 2) { *_err1 = _err1__tmp99; return 1; }
            if (_status__tmp99 == 3) { *_err2 = _err2__tmp99; return 2; }
        }
        til_Array_delete(&_tmp100);
        til_Str _tmp106;
        til_I64_OverflowError _err0__tmp107;
        til_IndexOutOfBoundsError _err1__tmp107;
        til_AllocError _err2__tmp107;
        til_Array _tmp108;
        til_AllocError _err_alloc__tmp109;
        til_IndexOutOfBoundsError _err_idx__tmp109;
        til_Str _tmp110 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp111 = til_I64_to_str(til_start);
        til_Str _tmp112 = ((til_Str){(til_I64)" is greater than end index ", 27});
        til_Str _tmp113 = til_I64_to_str(til_end);
        int _arr_status__tmp109 = til_Array_new(&_tmp108, &_err_alloc__tmp109, "Str", 4);
        if (_arr_status__tmp109 != 0) {
            *_err2 = _err_alloc__tmp109; return 2;
        }
        _arr_status__tmp109 = til_Array_set(&_err_idx__tmp109, &_tmp108, 0, &_tmp110);
        if (_arr_status__tmp109 != 0) {
            *_err1 = _err_idx__tmp109; return 1;
        }
        _arr_status__tmp109 = til_Array_set(&_err_idx__tmp109, &_tmp108, 1, &_tmp111);
        if (_arr_status__tmp109 != 0) {
            *_err1 = _err_idx__tmp109; return 1;
        }
        _arr_status__tmp109 = til_Array_set(&_err_idx__tmp109, &_tmp108, 2, &_tmp112);
        if (_arr_status__tmp109 != 0) {
            *_err1 = _err_idx__tmp109; return 1;
        }
        _arr_status__tmp109 = til_Array_set(&_err_idx__tmp109, &_tmp108, 3, &_tmp113);
        if (_arr_status__tmp109 != 0) {
            *_err1 = _err_idx__tmp109; return 1;
        }
        int _status__tmp107 = til_format(&_tmp106, &_err0__tmp107, &_err1__tmp107, &_err2__tmp107, ((til_Str){(til_I64)"src/test/constfold.til:363:48:", 30}), &_tmp108);
        if (_status__tmp107 != 0) {
            if (_status__tmp107 == 2) { *_err1 = _err1__tmp107; return 1; }
            if (_status__tmp107 == 3) { *_err2 = _err2__tmp107; return 2; }
        }
        til_Array_delete(&_tmp108);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp106);
        return 1;
    }
    if (til_gt(til_end, til_Str_len(til_s)).data) {
        til_Str _tmp115;
        til_I64_OverflowError _err0__tmp116;
        til_IndexOutOfBoundsError _err1__tmp116;
        til_AllocError _err2__tmp116;
        til_Array _tmp117;
        til_AllocError _err_alloc__tmp118;
        til_IndexOutOfBoundsError _err_idx__tmp118;
        til_Str _tmp119 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp120 = til_I64_to_str(til_end);
        til_Str _tmp121 = ((til_Str){(til_I64)" is greater than string length ", 31});
        til_Str _tmp122 = til_I64_to_str(til_Str_len(til_s));
        int _arr_status__tmp118 = til_Array_new(&_tmp117, &_err_alloc__tmp118, "Str", 4);
        if (_arr_status__tmp118 != 0) {
            *_err2 = _err_alloc__tmp118; return 2;
        }
        _arr_status__tmp118 = til_Array_set(&_err_idx__tmp118, &_tmp117, 0, &_tmp119);
        if (_arr_status__tmp118 != 0) {
            *_err1 = _err_idx__tmp118; return 1;
        }
        _arr_status__tmp118 = til_Array_set(&_err_idx__tmp118, &_tmp117, 1, &_tmp120);
        if (_arr_status__tmp118 != 0) {
            *_err1 = _err_idx__tmp118; return 1;
        }
        _arr_status__tmp118 = til_Array_set(&_err_idx__tmp118, &_tmp117, 2, &_tmp121);
        if (_arr_status__tmp118 != 0) {
            *_err1 = _err_idx__tmp118; return 1;
        }
        _arr_status__tmp118 = til_Array_set(&_err_idx__tmp118, &_tmp117, 3, &_tmp122);
        if (_arr_status__tmp118 != 0) {
            *_err1 = _err_idx__tmp118; return 1;
        }
        int _status__tmp116 = til_format(&_tmp115, &_err0__tmp116, &_err1__tmp116, &_err2__tmp116, ((til_Str){(til_I64)"src/test/constfold.til:366:48:", 30}), &_tmp117);
        if (_status__tmp116 != 0) {
            if (_status__tmp116 == 2) { *_err1 = _err1__tmp116; return 1; }
            if (_status__tmp116 == 3) { *_err2 = _err2__tmp116; return 2; }
        }
        til_Array_delete(&_tmp117);
        til_Str _tmp123;
        til_I64_OverflowError _err0__tmp124;
        til_IndexOutOfBoundsError _err1__tmp124;
        til_AllocError _err2__tmp124;
        til_Array _tmp125;
        til_AllocError _err_alloc__tmp126;
        til_IndexOutOfBoundsError _err_idx__tmp126;
        til_Str _tmp127 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp128 = til_I64_to_str(til_end);
        til_Str _tmp129 = ((til_Str){(til_I64)" is greater than string length ", 31});
        til_Str _tmp130 = til_I64_to_str(til_Str_len(til_s));
        int _arr_status__tmp126 = til_Array_new(&_tmp125, &_err_alloc__tmp126, "Str", 4);
        if (_arr_status__tmp126 != 0) {
            *_err2 = _err_alloc__tmp126; return 2;
        }
        _arr_status__tmp126 = til_Array_set(&_err_idx__tmp126, &_tmp125, 0, &_tmp127);
        if (_arr_status__tmp126 != 0) {
            *_err1 = _err_idx__tmp126; return 1;
        }
        _arr_status__tmp126 = til_Array_set(&_err_idx__tmp126, &_tmp125, 1, &_tmp128);
        if (_arr_status__tmp126 != 0) {
            *_err1 = _err_idx__tmp126; return 1;
        }
        _arr_status__tmp126 = til_Array_set(&_err_idx__tmp126, &_tmp125, 2, &_tmp129);
        if (_arr_status__tmp126 != 0) {
            *_err1 = _err_idx__tmp126; return 1;
        }
        _arr_status__tmp126 = til_Array_set(&_err_idx__tmp126, &_tmp125, 3, &_tmp130);
        if (_arr_status__tmp126 != 0) {
            *_err1 = _err_idx__tmp126; return 1;
        }
        int _status__tmp124 = til_format(&_tmp123, &_err0__tmp124, &_err1__tmp124, &_err2__tmp124, ((til_Str){(til_I64)"src/test/constfold.til:366:48:", 30}), &_tmp125);
        if (_status__tmp124 != 0) {
            if (_status__tmp124 == 2) { *_err1 = _err1__tmp124; return 1; }
            if (_status__tmp124 == 3) { *_err2 = _err2__tmp124; return 2; }
        }
        til_Array_delete(&_tmp125);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp123);
        return 1;
    }
    if (til_I64_eq(til_start, til_end).data) {
        til_Str _tmp132;
        til_I64_OverflowError _err0__tmp133;
        til_IndexOutOfBoundsError _err1__tmp133;
        til_AllocError _err2__tmp133;
        til_Array _tmp134;
        til_AllocError _err_alloc__tmp135;
        til_IndexOutOfBoundsError _err_idx__tmp135;
        til_Str _tmp136 = ((til_Str){(til_I64)"get_substr: start and end are the same (", 40});
        til_Str _tmp137 = til_I64_to_str(til_start);
        til_Str _tmp138 = ((til_Str){(til_I64)"), no substring", 15});
        int _arr_status__tmp135 = til_Array_new(&_tmp134, &_err_alloc__tmp135, "Str", 3);
        if (_arr_status__tmp135 != 0) {
            *_err2 = _err_alloc__tmp135; return 2;
        }
        _arr_status__tmp135 = til_Array_set(&_err_idx__tmp135, &_tmp134, 0, &_tmp136);
        if (_arr_status__tmp135 != 0) {
            *_err1 = _err_idx__tmp135; return 1;
        }
        _arr_status__tmp135 = til_Array_set(&_err_idx__tmp135, &_tmp134, 1, &_tmp137);
        if (_arr_status__tmp135 != 0) {
            *_err1 = _err_idx__tmp135; return 1;
        }
        _arr_status__tmp135 = til_Array_set(&_err_idx__tmp135, &_tmp134, 2, &_tmp138);
        if (_arr_status__tmp135 != 0) {
            *_err1 = _err_idx__tmp135; return 1;
        }
        int _status__tmp133 = til_format(&_tmp132, &_err0__tmp133, &_err1__tmp133, &_err2__tmp133, ((til_Str){(til_I64)"src/test/constfold.til:369:48:", 30}), &_tmp134);
        if (_status__tmp133 != 0) {
            if (_status__tmp133 == 2) { *_err1 = _err1__tmp133; return 1; }
            if (_status__tmp133 == 3) { *_err2 = _err2__tmp133; return 2; }
        }
        til_Array_delete(&_tmp134);
        til_Str _tmp139;
        til_I64_OverflowError _err0__tmp140;
        til_IndexOutOfBoundsError _err1__tmp140;
        til_AllocError _err2__tmp140;
        til_Array _tmp141;
        til_AllocError _err_alloc__tmp142;
        til_IndexOutOfBoundsError _err_idx__tmp142;
        til_Str _tmp143 = ((til_Str){(til_I64)"get_substr: start and end are the same (", 40});
        til_Str _tmp144 = til_I64_to_str(til_start);
        til_Str _tmp145 = ((til_Str){(til_I64)"), no substring", 15});
        int _arr_status__tmp142 = til_Array_new(&_tmp141, &_err_alloc__tmp142, "Str", 3);
        if (_arr_status__tmp142 != 0) {
            *_err2 = _err_alloc__tmp142; return 2;
        }
        _arr_status__tmp142 = til_Array_set(&_err_idx__tmp142, &_tmp141, 0, &_tmp143);
        if (_arr_status__tmp142 != 0) {
            *_err1 = _err_idx__tmp142; return 1;
        }
        _arr_status__tmp142 = til_Array_set(&_err_idx__tmp142, &_tmp141, 1, &_tmp144);
        if (_arr_status__tmp142 != 0) {
            *_err1 = _err_idx__tmp142; return 1;
        }
        _arr_status__tmp142 = til_Array_set(&_err_idx__tmp142, &_tmp141, 2, &_tmp145);
        if (_arr_status__tmp142 != 0) {
            *_err1 = _err_idx__tmp142; return 1;
        }
        int _status__tmp140 = til_format(&_tmp139, &_err0__tmp140, &_err1__tmp140, &_err2__tmp140, ((til_Str){(til_I64)"src/test/constfold.til:369:48:", 30}), &_tmp141);
        if (_status__tmp140 != 0) {
            if (_status__tmp140 == 2) { *_err1 = _err1__tmp140; return 1; }
            if (_status__tmp140 == 3) { *_err2 = _err2__tmp140; return 2; }
        }
        til_Array_delete(&_tmp141);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp139);
        return 1;
    }
    til_Str til_substr = {.c_string = 0, .cap = 0};
    til_substr.cap = til_sub(til_end, til_start);
    til_I64 _ret__tmp146;
    til_AllocError _err0__tmp146 = {};
    int _status__tmp146 = til_malloc(&_ret__tmp146, &_err0__tmp146, til_substr.cap);
    if (_status__tmp146 == 1) { *_err2 = _err0__tmp146; return 2; }
    til_substr.c_string = _ret__tmp146;
    if (til_I64_eq(til_NULL, til_substr.c_string).data) {
        til_Str _tmp148;
        til_I64_OverflowError _err0__tmp149;
        til_IndexOutOfBoundsError _err1__tmp149;
        til_AllocError _err2__tmp149;
        til_Array _tmp150;
        til_AllocError _err_alloc__tmp151;
        til_IndexOutOfBoundsError _err_idx__tmp151;
        til_Str _tmp152 = ((til_Str){(til_I64)"Str.get_substr: failed to allocate ", 35});
        til_Str _tmp153 = til_I64_to_str(til_substr.cap);
        til_Str _tmp154 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp151 = til_Array_new(&_tmp150, &_err_alloc__tmp151, "Str", 3);
        if (_arr_status__tmp151 != 0) {
            *_err2 = _err_alloc__tmp151; return 2;
        }
        _arr_status__tmp151 = til_Array_set(&_err_idx__tmp151, &_tmp150, 0, &_tmp152);
        if (_arr_status__tmp151 != 0) {
            *_err1 = _err_idx__tmp151; return 1;
        }
        _arr_status__tmp151 = til_Array_set(&_err_idx__tmp151, &_tmp150, 1, &_tmp153);
        if (_arr_status__tmp151 != 0) {
            *_err1 = _err_idx__tmp151; return 1;
        }
        _arr_status__tmp151 = til_Array_set(&_err_idx__tmp151, &_tmp150, 2, &_tmp154);
        if (_arr_status__tmp151 != 0) {
            *_err1 = _err_idx__tmp151; return 1;
        }
        int _status__tmp149 = til_format(&_tmp148, &_err0__tmp149, &_err1__tmp149, &_err2__tmp149, ((til_Str){(til_I64)"src/test/constfold.til:376:37:", 30}), &_tmp150);
        if (_status__tmp149 != 0) {
            if (_status__tmp149 == 2) { *_err1 = _err1__tmp149; return 1; }
            if (_status__tmp149 == 3) { *_err2 = _err2__tmp149; return 2; }
        }
        til_Array_delete(&_tmp150);
        til_Str _tmp155;
        til_I64_OverflowError _err0__tmp156;
        til_IndexOutOfBoundsError _err1__tmp156;
        til_AllocError _err2__tmp156;
        til_Array _tmp157;
        til_AllocError _err_alloc__tmp158;
        til_IndexOutOfBoundsError _err_idx__tmp158;
        til_Str _tmp159 = ((til_Str){(til_I64)"Str.get_substr: failed to allocate ", 35});
        til_Str _tmp160 = til_I64_to_str(til_substr.cap);
        til_Str _tmp161 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp158 = til_Array_new(&_tmp157, &_err_alloc__tmp158, "Str", 3);
        if (_arr_status__tmp158 != 0) {
            *_err2 = _err_alloc__tmp158; return 2;
        }
        _arr_status__tmp158 = til_Array_set(&_err_idx__tmp158, &_tmp157, 0, &_tmp159);
        if (_arr_status__tmp158 != 0) {
            *_err1 = _err_idx__tmp158; return 1;
        }
        _arr_status__tmp158 = til_Array_set(&_err_idx__tmp158, &_tmp157, 1, &_tmp160);
        if (_arr_status__tmp158 != 0) {
            *_err1 = _err_idx__tmp158; return 1;
        }
        _arr_status__tmp158 = til_Array_set(&_err_idx__tmp158, &_tmp157, 2, &_tmp161);
        if (_arr_status__tmp158 != 0) {
            *_err1 = _err_idx__tmp158; return 1;
        }
        int _status__tmp156 = til_format(&_tmp155, &_err0__tmp156, &_err1__tmp156, &_err2__tmp156, ((til_Str){(til_I64)"src/test/constfold.til:376:37:", 30}), &_tmp157);
        if (_status__tmp156 != 0) {
            if (_status__tmp156 == 2) { *_err1 = _err1__tmp156; return 1; }
            if (_status__tmp156 == 3) { *_err2 = _err2__tmp156; return 2; }
        }
        til_Array_delete(&_tmp157);
        *_err2 = til_AllocError_new(_tmp155);
        return 2;
    }
    til_memcpy(til_substr.c_string, til_add(til_s.c_string, til_start), til_substr.cap);
    *_ret = til_substr;
    return 0;
}

int til_get_char(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_pos) {
    til_Str _ret__tmp163;
    til_IndexOutOfBoundsError _err0__tmp163 = {};
    til_AllocError _err1__tmp163 = {};
    int _status__tmp163 = til_get_substr(&_ret__tmp163, &_err0__tmp163, &_err1__tmp163, til_s, til_pos, til_add(til_pos, 1));
    if (_status__tmp163 == 1) { *_err1 = _err0__tmp163; return 1; }
    if (_status__tmp163 == 2) { *_err2 = _err1__tmp163; return 2; }
    *_ret = _ret__tmp163;
    return 0;
}

til_Bool til_starts_with(const til_Str til_s, const til_Str til_prefix) {
    if (til_gt(til_Str_len(til_prefix), til_Str_len(til_s)).data) {
        return false;
    }
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Str_len(til_prefix)).data) {
        til_I64 til_s_byte = 0;
        til_I64 til_p_byte = 0;
        til_memcpy((til_I64)&til_s_byte, til_add(til_s.c_string, til_i), 1);
        til_memcpy((til_I64)&til_p_byte, til_add(til_prefix.c_string, til_i), 1);
        if (til_not(til_U8_eq(til_s_byte, til_p_byte)).data) {
            return false;
        }
        til_i = til_add(til_i, 1);
    }
    return true;
}

til_Str til_concat(const til_Str til_a, const til_Str til_b) {
    til_AllocError _thrown_AllocError__tmp168;
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_add(til_a.cap, til_b.cap);
    if (til_lt(til_result.cap, til_a.cap).data) {
        til_Array _tmp170;
        til_AllocError _err_alloc__tmp171;
        til_IndexOutOfBoundsError _err_idx__tmp171;
        til_Str _tmp172 = ((til_Str){(til_I64)"concat: integer overflow", 24});
        int _arr_status__tmp171 = til_Array_new(&_tmp170, &_err_alloc__tmp171, "Str", 1);
        if (_arr_status__tmp171 != 0) {
        }
        _arr_status__tmp171 = til_Array_set(&_err_idx__tmp171, &_tmp170, 0, &_tmp172);
        if (_arr_status__tmp171 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/test/constfold.til:416:15:", 30}), &_tmp170);
        til_Array_delete(&_tmp170);
    }
    til_I64 _ret__tmp173;
    til_AllocError _err0__tmp173 = {};
    int _status__tmp173 = til_malloc(&_ret__tmp173, &_err0__tmp173, til_result.cap);
    if (_status__tmp173 == 0) {
        til_result.c_string = _ret__tmp173;
    } else if (_status__tmp173 == 1) {
        til_AllocError til_err = _err0__tmp173;
        til_Array _tmp175;
        til_AllocError _err_alloc__tmp176;
        til_IndexOutOfBoundsError _err_idx__tmp176;
        til_Str _tmp177 = til_err.msg;
        int _arr_status__tmp176 = til_Array_new(&_tmp175, &_err_alloc__tmp176, "Str", 1);
        if (_arr_status__tmp176 != 0) {
        }
        _arr_status__tmp176 = til_Array_set(&_err_idx__tmp176, &_tmp175, 0, &_tmp177);
        if (_arr_status__tmp176 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/test/constfold.til:428:15:", 30}), &_tmp175);
        til_Array_delete(&_tmp175);
    }
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Array _tmp179;
        til_AllocError _err_alloc__tmp180;
        til_IndexOutOfBoundsError _err_idx__tmp180;
        til_Str _tmp181 = ((til_Str){(til_I64)"concat: malloc failed", 21});
        int _arr_status__tmp180 = til_Array_new(&_tmp179, &_err_alloc__tmp180, "Str", 1);
        if (_arr_status__tmp180 != 0) {
        }
        _arr_status__tmp180 = til_Array_set(&_err_idx__tmp180, &_tmp179, 0, &_tmp181);
        if (_arr_status__tmp180 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/test/constfold.til:421:15:", 30}), &_tmp179);
        til_Array_delete(&_tmp179);
    }
    til_memcpy(til_result.c_string, til_a.c_string, til_a.cap);
    til_memcpy(til_add(til_result.c_string, til_a.cap), til_b.c_string, til_b.cap);
    return til_result;
    goto _end_catches__tmp168;
_catch_AllocError__tmp168: {
    til_AllocError til_err = _thrown_AllocError__tmp168;
    til_Array _tmp183;
    til_AllocError _err_alloc__tmp184;
    til_IndexOutOfBoundsError _err_idx__tmp184;
    til_Str _tmp185 = til_err.msg;
    int _arr_status__tmp184 = til_Array_new(&_tmp183, &_err_alloc__tmp184, "Str", 1);
    if (_arr_status__tmp184 != 0) {
    }
    _arr_status__tmp184 = til_Array_set(&_err_idx__tmp184, &_tmp183, 0, &_tmp185);
    if (_arr_status__tmp184 != 0) {
    }
    til_panic(((til_Str){(til_I64)"src/test/constfold.til:428:15:", 30}), &_tmp183);
    til_Array_delete(&_tmp183);
    }
_end_catches__tmp168:;
}

int til_format(til_Str* _ret, til_I64_OverflowError* _err1, til_IndexOutOfBoundsError* _err2, til_AllocError* _err3, const til_Str til_prefix, til_Array* til_args) {
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_prefix.cap;
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Str til_arg = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp189 = {};
        int _status__tmp189 = til_Array_get(&_err0__tmp189, (*til_args), til_i, (til_Dynamic*)&til_arg);
        if (_status__tmp189 == 1) { *_err2 = _err0__tmp189; return 2; }
        til_result.cap = til_add(til_result.cap, til_arg.cap);
        if (til_lt(til_result.cap, til_arg.cap).data) {
            til_Str _tmp191;
            til_I64_OverflowError _err0__tmp192;
            til_IndexOutOfBoundsError _err1__tmp192;
            til_AllocError _err2__tmp192;
            til_Array _tmp193;
            til_AllocError _err_alloc__tmp194;
            til_IndexOutOfBoundsError _err_idx__tmp194;
            til_Str _tmp195 = ((til_Str){(til_I64)"format: integer overflow while summing cap for arg ", 51});
            til_Str _tmp196 = til_I64_to_str(til_i);
            int _arr_status__tmp194 = til_Array_new(&_tmp193, &_err_alloc__tmp194, "Str", 2);
            if (_arr_status__tmp194 != 0) {
                *_err3 = _err_alloc__tmp194; return 3;
            }
            _arr_status__tmp194 = til_Array_set(&_err_idx__tmp194, &_tmp193, 0, &_tmp195);
            if (_arr_status__tmp194 != 0) {
                *_err2 = _err_idx__tmp194; return 2;
            }
            _arr_status__tmp194 = til_Array_set(&_err_idx__tmp194, &_tmp193, 1, &_tmp196);
            if (_arr_status__tmp194 != 0) {
                *_err2 = _err_idx__tmp194; return 2;
            }
            int _status__tmp192 = til_format(&_tmp191, &_err0__tmp192, &_err1__tmp192, &_err2__tmp192, ((til_Str){(til_I64)"src/test/constfold.til:444:48:", 30}), &_tmp193);
            if (_status__tmp192 != 0) {
                if (_status__tmp192 == 1) { *_err1 = _err0__tmp192; return 1; }
                if (_status__tmp192 == 2) { *_err2 = _err1__tmp192; return 2; }
                if (_status__tmp192 == 3) { *_err3 = _err2__tmp192; return 3; }
            }
            til_Array_delete(&_tmp193);
            til_Str _tmp197;
            til_I64_OverflowError _err0__tmp198;
            til_IndexOutOfBoundsError _err1__tmp198;
            til_AllocError _err2__tmp198;
            til_Array _tmp199;
            til_AllocError _err_alloc__tmp200;
            til_IndexOutOfBoundsError _err_idx__tmp200;
            til_Str _tmp201 = ((til_Str){(til_I64)"format: integer overflow while summing cap for arg ", 51});
            til_Str _tmp202 = til_I64_to_str(til_i);
            int _arr_status__tmp200 = til_Array_new(&_tmp199, &_err_alloc__tmp200, "Str", 2);
            if (_arr_status__tmp200 != 0) {
                *_err3 = _err_alloc__tmp200; return 3;
            }
            _arr_status__tmp200 = til_Array_set(&_err_idx__tmp200, &_tmp199, 0, &_tmp201);
            if (_arr_status__tmp200 != 0) {
                *_err2 = _err_idx__tmp200; return 2;
            }
            _arr_status__tmp200 = til_Array_set(&_err_idx__tmp200, &_tmp199, 1, &_tmp202);
            if (_arr_status__tmp200 != 0) {
                *_err2 = _err_idx__tmp200; return 2;
            }
            int _status__tmp198 = til_format(&_tmp197, &_err0__tmp198, &_err1__tmp198, &_err2__tmp198, ((til_Str){(til_I64)"src/test/constfold.til:444:48:", 30}), &_tmp199);
            if (_status__tmp198 != 0) {
                if (_status__tmp198 == 1) { *_err1 = _err0__tmp198; return 1; }
                if (_status__tmp198 == 2) { *_err2 = _err1__tmp198; return 2; }
                if (_status__tmp198 == 3) { *_err3 = _err2__tmp198; return 3; }
            }
            til_Array_delete(&_tmp199);
            *_err1 = til_I64_OverflowError_new(_tmp197);
            return 1;
        }
        til_I64_inc(&til_i);
    }
    til_I64 _ret__tmp203;
    til_AllocError _err0__tmp203 = {};
    int _status__tmp203 = til_malloc(&_ret__tmp203, &_err0__tmp203, til_result.cap);
    if (_status__tmp203 == 1) { *_err3 = _err0__tmp203; return 3; }
    til_result.c_string = _ret__tmp203;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Str _tmp205;
        til_I64_OverflowError _err0__tmp206;
        til_IndexOutOfBoundsError _err1__tmp206;
        til_AllocError _err2__tmp206;
        til_Array _tmp207;
        til_AllocError _err_alloc__tmp208;
        til_IndexOutOfBoundsError _err_idx__tmp208;
        til_Str _tmp209 = ((til_Str){(til_I64)"format: malloc failed for cap = ", 32});
        til_Str _tmp210 = til_I64_to_str(til_result.cap);
        int _arr_status__tmp208 = til_Array_new(&_tmp207, &_err_alloc__tmp208, "Str", 2);
        if (_arr_status__tmp208 != 0) {
            *_err3 = _err_alloc__tmp208; return 3;
        }
        _arr_status__tmp208 = til_Array_set(&_err_idx__tmp208, &_tmp207, 0, &_tmp209);
        if (_arr_status__tmp208 != 0) {
            *_err2 = _err_idx__tmp208; return 2;
        }
        _arr_status__tmp208 = til_Array_set(&_err_idx__tmp208, &_tmp207, 1, &_tmp210);
        if (_arr_status__tmp208 != 0) {
            *_err2 = _err_idx__tmp208; return 2;
        }
        int _status__tmp206 = til_format(&_tmp205, &_err0__tmp206, &_err1__tmp206, &_err2__tmp206, ((til_Str){(til_I64)"src/test/constfold.til:450:37:", 30}), &_tmp207);
        if (_status__tmp206 != 0) {
            if (_status__tmp206 == 1) { *_err1 = _err0__tmp206; return 1; }
            if (_status__tmp206 == 2) { *_err2 = _err1__tmp206; return 2; }
            if (_status__tmp206 == 3) { *_err3 = _err2__tmp206; return 3; }
        }
        til_Array_delete(&_tmp207);
        til_Str _tmp211;
        til_I64_OverflowError _err0__tmp212;
        til_IndexOutOfBoundsError _err1__tmp212;
        til_AllocError _err2__tmp212;
        til_Array _tmp213;
        til_AllocError _err_alloc__tmp214;
        til_IndexOutOfBoundsError _err_idx__tmp214;
        til_Str _tmp215 = ((til_Str){(til_I64)"format: malloc failed for cap = ", 32});
        til_Str _tmp216 = til_I64_to_str(til_result.cap);
        int _arr_status__tmp214 = til_Array_new(&_tmp213, &_err_alloc__tmp214, "Str", 2);
        if (_arr_status__tmp214 != 0) {
            *_err3 = _err_alloc__tmp214; return 3;
        }
        _arr_status__tmp214 = til_Array_set(&_err_idx__tmp214, &_tmp213, 0, &_tmp215);
        if (_arr_status__tmp214 != 0) {
            *_err2 = _err_idx__tmp214; return 2;
        }
        _arr_status__tmp214 = til_Array_set(&_err_idx__tmp214, &_tmp213, 1, &_tmp216);
        if (_arr_status__tmp214 != 0) {
            *_err2 = _err_idx__tmp214; return 2;
        }
        int _status__tmp212 = til_format(&_tmp211, &_err0__tmp212, &_err1__tmp212, &_err2__tmp212, ((til_Str){(til_I64)"src/test/constfold.til:450:37:", 30}), &_tmp213);
        if (_status__tmp212 != 0) {
            if (_status__tmp212 == 1) { *_err1 = _err0__tmp212; return 1; }
            if (_status__tmp212 == 2) { *_err2 = _err1__tmp212; return 2; }
            if (_status__tmp212 == 3) { *_err3 = _err2__tmp212; return 3; }
        }
        til_Array_delete(&_tmp213);
        *_err3 = til_AllocError_new(_tmp211);
        return 3;
    }
    til_I64 til_offset = 0;
    til_memcpy(til_result.c_string, til_prefix.c_string, til_prefix.cap);
    til_offset = til_prefix.cap;
    til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Str til_s = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp219 = {};
        int _status__tmp219 = til_Array_get(&_err0__tmp219, (*til_args), til_i, (til_Dynamic*)&til_s);
        if (_status__tmp219 == 1) { *_err2 = _err0__tmp219; return 2; }
        til_memcpy(til_add(til_result.c_string, til_offset), til_s.c_string, til_s.cap);
        til_offset = til_add(til_offset, til_s.cap);
        til_I64_inc(&til_i);
    }
    *_ret = til_result;
    return 0;
}

void til_test(const til_Str til_loc_str, const til_Bool til_cond, const til_Str til_msg) {
    til_assertm(til_loc_str, til_cond, til_msg);
}

void til_assert_eq_str(const til_Str til_loc_str, const til_Str til_a, const til_Str til_b) {
    if (til_not(til_Str_eq(til_a, til_b)).data) {
        til_Array _tmp223;
        til_AllocError _err_alloc__tmp224;
        til_IndexOutOfBoundsError _err_idx__tmp224;
        til_Str _tmp225 = til_loc_str;
        til_Str _tmp226 = ((til_Str){(til_I64)"assert_eq_str failed: expected '", 32});
        til_Str _tmp227 = til_a;
        til_Str _tmp228 = ((til_Str){(til_I64)"', found '", 10});
        til_Str _tmp229 = til_b;
        til_Str _tmp230 = ((til_Str){(til_I64)"'", 1});
        int _arr_status__tmp224 = til_Array_new(&_tmp223, &_err_alloc__tmp224, "Str", 6);
        if (_arr_status__tmp224 != 0) {
        }
        _arr_status__tmp224 = til_Array_set(&_err_idx__tmp224, &_tmp223, 0, &_tmp225);
        if (_arr_status__tmp224 != 0) {
        }
        _arr_status__tmp224 = til_Array_set(&_err_idx__tmp224, &_tmp223, 1, &_tmp226);
        if (_arr_status__tmp224 != 0) {
        }
        _arr_status__tmp224 = til_Array_set(&_err_idx__tmp224, &_tmp223, 2, &_tmp227);
        if (_arr_status__tmp224 != 0) {
        }
        _arr_status__tmp224 = til_Array_set(&_err_idx__tmp224, &_tmp223, 3, &_tmp228);
        if (_arr_status__tmp224 != 0) {
        }
        _arr_status__tmp224 = til_Array_set(&_err_idx__tmp224, &_tmp223, 4, &_tmp229);
        if (_arr_status__tmp224 != 0) {
        }
        _arr_status__tmp224 = til_Array_set(&_err_idx__tmp224, &_tmp223, 5, &_tmp230);
        if (_arr_status__tmp224 != 0) {
        }
        til_println(&_tmp223);
        til_Array_delete(&_tmp223);
        til_exit(1);
    }
}

void til_assert_eq(const til_Str til_loc_str, const til_I64 til_a, const til_I64 til_b) {
    if (til_not(til_I64_eq(til_a, til_b)).data) {
        til_Array _tmp233;
        til_AllocError _err_alloc__tmp234;
        til_IndexOutOfBoundsError _err_idx__tmp234;
        til_Str _tmp235 = til_loc_str;
        til_Str _tmp236 = ((til_Str){(til_I64)"assert_eq failed: expected '", 28});
        til_Str _tmp237 = til_I64_to_str(til_a);
        til_Str _tmp238 = ((til_Str){(til_I64)"', found '", 10});
        til_Str _tmp239 = til_I64_to_str(til_b);
        til_Str _tmp240 = ((til_Str){(til_I64)"'", 1});
        int _arr_status__tmp234 = til_Array_new(&_tmp233, &_err_alloc__tmp234, "Str", 6);
        if (_arr_status__tmp234 != 0) {
        }
        _arr_status__tmp234 = til_Array_set(&_err_idx__tmp234, &_tmp233, 0, &_tmp235);
        if (_arr_status__tmp234 != 0) {
        }
        _arr_status__tmp234 = til_Array_set(&_err_idx__tmp234, &_tmp233, 1, &_tmp236);
        if (_arr_status__tmp234 != 0) {
        }
        _arr_status__tmp234 = til_Array_set(&_err_idx__tmp234, &_tmp233, 2, &_tmp237);
        if (_arr_status__tmp234 != 0) {
        }
        _arr_status__tmp234 = til_Array_set(&_err_idx__tmp234, &_tmp233, 3, &_tmp238);
        if (_arr_status__tmp234 != 0) {
        }
        _arr_status__tmp234 = til_Array_set(&_err_idx__tmp234, &_tmp233, 4, &_tmp239);
        if (_arr_status__tmp234 != 0) {
        }
        _arr_status__tmp234 = til_Array_set(&_err_idx__tmp234, &_tmp233, 5, &_tmp240);
        if (_arr_status__tmp234 != 0) {
        }
        til_println(&_tmp233);
        til_Array_delete(&_tmp233);
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
    const til_Str til_result = til_concat(((til_Str){(til_I64)"hello", 5}), ((til_Str){(til_I64)" world", 6}));
    til_test(((til_Str){(til_I64)"src/test/constfold.til:30:10:", 29}), til_Str_eq(til_result, ((til_Str){(til_I64)"hello world", 11})), ((til_Str){(til_I64)"concat works at runtime", 23}));
}

void til_test_fold_variable(void) {
    const til_I64 til_x = 5;
    const til_I64 til_result = 8;
    til_test(((til_Str){(til_I64)"src/test/constfold.til:39:10:", 29}), til_I64_eq(til_result, 8), ((til_Str){(til_I64)"add(x, 3) should fold to 8", 26}));
}

void til_test_loc_folded_correctly(void) {
    const til_Str til_location = ((til_Str){(til_I64)"src/test/constfold.til:45:17:", 29});
    til_test(((til_Str){(til_I64)"src/test/constfold.til:46:10:", 29}), til_Str_contains(til_location, ((til_Str){(til_I64)"constfold.til", 13})), ((til_Str){(til_I64)"loc() should contain filename", 29}));
    til_test(((til_Str){(til_I64)"src/test/constfold.til:47:10:", 29}), til_Str_contains(til_location, ((til_Str){(til_I64)":45:", 4})), ((til_Str){(til_I64)"loc() should contain correct line number", 40}));
}

void til_test_struct_fold_simple(void) {
    const til_CfVec2 til_v = {.x = 42, .y = 99};
    til_assert_eq(((til_Str){(til_I64)"src/test/constfold.til:72:15:", 29}), 42, til_v.x);
    til_assert_eq(((til_Str){(til_I64)"src/test/constfold.til:73:15:", 29}), 99, til_v.y);
}

void til_test_struct_fold_values(void) {
    const til_CfVec2 til_p = {.x = 10, .y = 20};
    til_assert_eq(((til_Str){(til_I64)"src/test/constfold.til:80:15:", 29}), 10, til_p.x);
    til_assert_eq(((til_Str){(til_I64)"src/test/constfold.til:81:15:", 29}), 20, til_p.y);
}

void til_test_struct_fold_nested(void) {
    const til_CfRect til_r = {.top_left = (til_CfVec2){.x = 5, .y = 10}, .bottom_right = (til_CfVec2){.x = 100, .y = 200}};
    til_assert_eq(((til_Str){(til_I64)"src/test/constfold.til:98:15:", 29}), 5, til_r.top_left.x);
    til_assert_eq(((til_Str){(til_I64)"src/test/constfold.til:99:15:", 29}), 10, til_r.top_left.y);
    til_assert_eq(((til_Str){(til_I64)"src/test/constfold.til:100:15:", 30}), 100, til_r.bottom_right.x);
    til_assert_eq(((til_Str){(til_I64)"src/test/constfold.til:101:15:", 30}), 200, til_r.bottom_right.y);
}

til_IndexOutOfBoundsError til_IndexOutOfBoundsError_new(const til_Str til_msg) {
    til_IndexOutOfBoundsError til_err = {.msg = ((til_Str){(til_I64)"", 0})};
    til_err.msg = til_msg;
    return til_err;
}

til_AllocError til_AllocError_new(const til_Str til_msg) {
    til_AllocError til_err = {.msg = ((til_Str){(til_I64)"", 0})};
    til_err.msg = til_msg;
    return til_err;
}

til_I64 til_Array_len(const til_Array til_self) {
    return til_self._len;
}

til_I64 til_Array_size(const til_Array til_self) {
    return til_mul(til_self._len, til_self.type_size);
}

int til_Array_new(til_Array* _ret, til_AllocError* _err1, const til_Type til_T, const til_I64 til_capacity) {
    til_Array til_arr = {.type_name = ((til_Str){(til_I64)"", 0}), .type_size = 0, .ptr = 0, ._len = 0};
    til_arr.type_name = ((til_Str){(til_I64)"T", 1});
    til_arr.type_size = til_size_of(((til_Str){(til_I64)til_T, strlen(til_T)}));
    const til_I64 til_size_bytes = til_mul(til_capacity, til_arr.type_size);
    til_I64 _ret__tmp255;
    til_AllocError _err0__tmp255 = {};
    int _status__tmp255 = til_malloc(&_ret__tmp255, &_err0__tmp255, til_size_bytes);
    if (_status__tmp255 == 1) { *_err1 = _err0__tmp255; return 1; }
    til_arr.ptr = _ret__tmp255;
    til_U8 _tmp256;
    til_U8_OverflowError _err0__tmp257;
    int _status__tmp257 = til_U8_from_i64(&_tmp256, &_err0__tmp257, 0);
    if (_status__tmp257 != 0) {
    }
    til_memset(til_arr.ptr, _tmp256, til_size_bytes);
    til_arr._len = til_capacity;
    *_ret = til_arr;
    return 0;
}

int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array til_self, const til_I64 til_index, til_Dynamic* til_T) {
    if (til_gteq(til_index, til_self._len).data) {
        til_Str _tmp260;
        til_I64_OverflowError _err0__tmp261;
        til_IndexOutOfBoundsError _err1__tmp261;
        til_AllocError _err2__tmp261;
        til_Array _tmp262;
        til_AllocError _err_alloc__tmp263;
        til_IndexOutOfBoundsError _err_idx__tmp263;
        til_Str _tmp264 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        int _arr_status__tmp263 = til_Array_new(&_tmp262, &_err_alloc__tmp263, "Str", 1);
        if (_arr_status__tmp263 != 0) {
        }
        _arr_status__tmp263 = til_Array_set(&_err_idx__tmp263, &_tmp262, 0, &_tmp264);
        if (_arr_status__tmp263 != 0) {
            *_err1 = _err_idx__tmp263; return 1;
        }
        int _status__tmp261 = til_format(&_tmp260, &_err0__tmp261, &_err1__tmp261, &_err2__tmp261, ((til_Str){(til_I64)"src/test/constfold.til:41:52:", 29}), &_tmp262);
        if (_status__tmp261 != 0) {
            if (_status__tmp261 == 2) { *_err1 = _err1__tmp261; return 1; }
        }
        til_Array_delete(&_tmp262);
        til_Str _tmp265;
        til_I64_OverflowError _err0__tmp266;
        til_IndexOutOfBoundsError _err1__tmp266;
        til_AllocError _err2__tmp266;
        til_Array _tmp267;
        til_AllocError _err_alloc__tmp268;
        til_IndexOutOfBoundsError _err_idx__tmp268;
        til_Str _tmp269 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        int _arr_status__tmp268 = til_Array_new(&_tmp267, &_err_alloc__tmp268, "Str", 1);
        if (_arr_status__tmp268 != 0) {
        }
        _arr_status__tmp268 = til_Array_set(&_err_idx__tmp268, &_tmp267, 0, &_tmp269);
        if (_arr_status__tmp268 != 0) {
            *_err1 = _err_idx__tmp268; return 1;
        }
        int _status__tmp266 = til_format(&_tmp265, &_err0__tmp266, &_err1__tmp266, &_err2__tmp266, ((til_Str){(til_I64)"src/test/constfold.til:41:52:", 29}), &_tmp267);
        if (_status__tmp266 != 0) {
            if (_status__tmp266 == 2) { *_err1 = _err1__tmp266; return 1; }
        }
        til_Array_delete(&_tmp267);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp265);
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_gteq(til_index, til_self->_len).data) {
        til_Str _tmp272;
        til_I64_OverflowError _err0__tmp273;
        til_IndexOutOfBoundsError _err1__tmp273;
        til_AllocError _err2__tmp273;
        til_Array _tmp274;
        til_AllocError _err_alloc__tmp275;
        til_IndexOutOfBoundsError _err_idx__tmp275;
        til_Str _tmp276 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        int _arr_status__tmp275 = til_Array_new(&_tmp274, &_err_alloc__tmp275, "Str", 1);
        if (_arr_status__tmp275 != 0) {
        }
        _arr_status__tmp275 = til_Array_set(&_err_idx__tmp275, &_tmp274, 0, &_tmp276);
        if (_arr_status__tmp275 != 0) {
            *_err1 = _err_idx__tmp275; return 1;
        }
        int _status__tmp273 = til_format(&_tmp272, &_err0__tmp273, &_err1__tmp273, &_err2__tmp273, ((til_Str){(til_I64)"src/test/constfold.til:56:52:", 29}), &_tmp274);
        if (_status__tmp273 != 0) {
            if (_status__tmp273 == 2) { *_err1 = _err1__tmp273; return 1; }
        }
        til_Array_delete(&_tmp274);
        til_Str _tmp277;
        til_I64_OverflowError _err0__tmp278;
        til_IndexOutOfBoundsError _err1__tmp278;
        til_AllocError _err2__tmp278;
        til_Array _tmp279;
        til_AllocError _err_alloc__tmp280;
        til_IndexOutOfBoundsError _err_idx__tmp280;
        til_Str _tmp281 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        int _arr_status__tmp280 = til_Array_new(&_tmp279, &_err_alloc__tmp280, "Str", 1);
        if (_arr_status__tmp280 != 0) {
        }
        _arr_status__tmp280 = til_Array_set(&_err_idx__tmp280, &_tmp279, 0, &_tmp281);
        if (_arr_status__tmp280 != 0) {
            *_err1 = _err_idx__tmp280; return 1;
        }
        int _status__tmp278 = til_format(&_tmp277, &_err0__tmp278, &_err1__tmp278, &_err2__tmp278, ((til_Str){(til_I64)"src/test/constfold.til:56:52:", 29}), &_tmp279);
        if (_status__tmp278 != 0) {
            if (_status__tmp278 == 2) { *_err1 = _err1__tmp278; return 1; }
        }
        til_Array_delete(&_tmp279);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp277);
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

int til_Array_clone(til_Array* _ret, til_AllocError* _err1, const til_Array til_self) {
    til_Array til_cloned = {.type_name = ((til_Str){(til_I64)"", 0}), .type_size = 0, .ptr = 0, ._len = 0};
    til_cloned.type_name = til_self.type_name;
    til_cloned.type_size = til_self.type_size;
    til_cloned._len = til_self._len;
    til_I64 til_total_bytes = til_mul(til_self._len, til_self.type_size);
    til_I64 _ret__tmp284;
    til_AllocError _err0__tmp284 = {};
    int _status__tmp284 = til_malloc(&_ret__tmp284, &_err0__tmp284, til_total_bytes);
    if (_status__tmp284 == 1) { *_err1 = _err0__tmp284; return 1; }
    til_cloned.ptr = _ret__tmp284;
    if (til_I64_eq(til_NULL, til_cloned.ptr).data) {
        til_Str _tmp286;
        til_I64_OverflowError _err0__tmp287;
        til_IndexOutOfBoundsError _err1__tmp287;
        til_AllocError _err2__tmp287;
        til_Array _tmp288;
        til_AllocError _err_alloc__tmp289;
        til_IndexOutOfBoundsError _err_idx__tmp289;
        til_Str _tmp290 = ((til_Str){(til_I64)"Array.clone: malloc failed for ", 31});
        til_Str _tmp291 = til_I64_to_str(til_total_bytes);
        til_Str _tmp292 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp289 = til_Array_new(&_tmp288, &_err_alloc__tmp289, "Str", 3);
        if (_arr_status__tmp289 != 0) {
            *_err1 = _err_alloc__tmp289; return 1;
        }
        _arr_status__tmp289 = til_Array_set(&_err_idx__tmp289, &_tmp288, 0, &_tmp290);
        if (_arr_status__tmp289 != 0) {
        }
        _arr_status__tmp289 = til_Array_set(&_err_idx__tmp289, &_tmp288, 1, &_tmp291);
        if (_arr_status__tmp289 != 0) {
        }
        _arr_status__tmp289 = til_Array_set(&_err_idx__tmp289, &_tmp288, 2, &_tmp292);
        if (_arr_status__tmp289 != 0) {
        }
        int _status__tmp287 = til_format(&_tmp286, &_err0__tmp287, &_err1__tmp287, &_err2__tmp287, ((til_Str){(til_I64)"src/test/constfold.til:83:41:", 29}), &_tmp288);
        if (_status__tmp287 != 0) {
            if (_status__tmp287 == 3) { *_err1 = _err2__tmp287; return 1; }
        }
        til_Array_delete(&_tmp288);
        til_Str _tmp293;
        til_I64_OverflowError _err0__tmp294;
        til_IndexOutOfBoundsError _err1__tmp294;
        til_AllocError _err2__tmp294;
        til_Array _tmp295;
        til_AllocError _err_alloc__tmp296;
        til_IndexOutOfBoundsError _err_idx__tmp296;
        til_Str _tmp297 = ((til_Str){(til_I64)"Array.clone: malloc failed for ", 31});
        til_Str _tmp298 = til_I64_to_str(til_total_bytes);
        til_Str _tmp299 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp296 = til_Array_new(&_tmp295, &_err_alloc__tmp296, "Str", 3);
        if (_arr_status__tmp296 != 0) {
            *_err1 = _err_alloc__tmp296; return 1;
        }
        _arr_status__tmp296 = til_Array_set(&_err_idx__tmp296, &_tmp295, 0, &_tmp297);
        if (_arr_status__tmp296 != 0) {
        }
        _arr_status__tmp296 = til_Array_set(&_err_idx__tmp296, &_tmp295, 1, &_tmp298);
        if (_arr_status__tmp296 != 0) {
        }
        _arr_status__tmp296 = til_Array_set(&_err_idx__tmp296, &_tmp295, 2, &_tmp299);
        if (_arr_status__tmp296 != 0) {
        }
        int _status__tmp294 = til_format(&_tmp293, &_err0__tmp294, &_err1__tmp294, &_err2__tmp294, ((til_Str){(til_I64)"src/test/constfold.til:83:41:", 29}), &_tmp295);
        if (_status__tmp294 != 0) {
            if (_status__tmp294 == 3) { *_err1 = _err2__tmp294; return 1; }
        }
        til_Array_delete(&_tmp295);
        *_err1 = til_AllocError_new(_tmp293);
        return 1;
    }
    til_memcpy(til_cloned.ptr, til_self.ptr, til_total_bytes);
    *_ret = til_cloned;
    return 0;
}

til_Bool til_Array_contains(const til_Array til_self, const til_Str til_value) {
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp300;
    til_I64 til_i = 0;
    while (til_lt(til_i, til_self._len).data) {
        til_Str til_elem = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp302 = {};
        int _status__tmp302 = til_Array_get(&_err0__tmp302, til_self, til_i, (til_Dynamic*)&til_elem);
        if (_status__tmp302 == 1) { _thrown_IndexOutOfBoundsError__tmp300 = _err0__tmp302; goto _catch_IndexOutOfBoundsError__tmp300; }
        if (til_Str_eq(til_elem, til_value).data) {
            return true;
        }
        til_i = til_add(til_i, 1);
    }
    return false;
    goto _end_catches__tmp300;
_catch_IndexOutOfBoundsError__tmp300: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp300;
    }
_end_catches__tmp300:;
}

til_I64 til_Bool_len(const til_Bool til_self) {
    return 1;
}

til_Bool til_Bool_eq(const til_Bool til_a, const til_Bool til_b) {
    til_Bool _tmp307;
    til_Array _tmp308;
    til_AllocError _err_alloc__tmp309;
    til_IndexOutOfBoundsError _err_idx__tmp309;
    til_Bool _tmp310 = til_a;
    til_Bool _tmp311 = til_b;
    int _arr_status__tmp309 = til_Array_new(&_tmp308, &_err_alloc__tmp309, "Bool", 2);
    if (_arr_status__tmp309 != 0) {
    }
    _arr_status__tmp309 = til_Array_set(&_err_idx__tmp309, &_tmp308, 0, &_tmp310);
    if (_arr_status__tmp309 != 0) {
    }
    _arr_status__tmp309 = til_Array_set(&_err_idx__tmp309, &_tmp308, 1, &_tmp311);
    if (_arr_status__tmp309 != 0) {
    }
    _tmp307 = til_and(&_tmp308);
    til_Array_delete(&_tmp308);
    til_Bool _tmp312;
    til_Array _tmp313;
    til_AllocError _err_alloc__tmp314;
    til_IndexOutOfBoundsError _err_idx__tmp314;
    til_Bool _tmp315 = til_not(til_b);
    til_Bool _tmp316 = til_not(til_a);
    int _arr_status__tmp314 = til_Array_new(&_tmp313, &_err_alloc__tmp314, "Bool", 2);
    if (_arr_status__tmp314 != 0) {
    }
    _arr_status__tmp314 = til_Array_set(&_err_idx__tmp314, &_tmp313, 0, &_tmp315);
    if (_arr_status__tmp314 != 0) {
    }
    _arr_status__tmp314 = til_Array_set(&_err_idx__tmp314, &_tmp313, 1, &_tmp316);
    if (_arr_status__tmp314 != 0) {
    }
    _tmp312 = til_and(&_tmp313);
    til_Array_delete(&_tmp313);
    til_Array _tmp317;
    til_AllocError _err_alloc__tmp318;
    til_IndexOutOfBoundsError _err_idx__tmp318;
    int _arr_status__tmp318 = til_Array_new(&_tmp317, &_err_alloc__tmp318, "Bool", 2);
    if (_arr_status__tmp318 != 0) {
    }
    _arr_status__tmp318 = til_Array_set(&_err_idx__tmp318, &_tmp317, 0, &_tmp307);
    if (_arr_status__tmp318 != 0) {
    }
    _arr_status__tmp318 = til_Array_set(&_err_idx__tmp318, &_tmp317, 1, &_tmp312);
    if (_arr_status__tmp318 != 0) {
    }
    til_Bool _tmp319 = til_or(&_tmp317);
    til_Array_delete(&_tmp317);
    return _tmp319;
}

til_Str til_Bool_to_str(const til_Bool til_self) {
    if (til_self.data) {
        return ((til_Str){(til_I64)"true", 4});
    }
    return ((til_Str){(til_I64)"false", 5});
}

til_I64 til_Bool_to_i64(const til_Bool til_self) {
    if (til_self.data) {
        return 1;
    }
    return 0;
}

til_U8 til_Bool_to_u8(const til_Bool til_self) {
    return til_self.data;
}

til_Bool til_Bool_from_i64(const til_I64 til_i) {
    til_Bool til_b = {.data = 0};
    if (til_gt(til_i, 0).data) {
        til_b.data = 1;
    }
    return til_b;
}

til_I64 til_Bool_size(void) {
    return 1;
}

til_I64_OverflowError til_I64_OverflowError_new(const til_Str til_msg) {
    til_I64_OverflowError til_err = {.msg = ((til_Str){(til_I64)"", 0})};
    til_err.msg = til_msg;
    return til_err;
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

void til_I64_dec(til_I64* til_self) {
    *til_self = til_sub((*til_self), 1);
}

til_I64 til_I64___add__(const til_I64 til_self, const til_I64 til_other) {
    return til_add(til_self, til_other);
}

til_I64 til_I64_size(void) {
    return 8;
}

til_I64 til_Vec_len(const til_Vec til_self) {
    return til_self._len;
}

til_I64 til_Vec_size(const til_Vec til_self) {
    return til_mul(til_self._len, til_self.type_size);
}

int til_Vec_new(til_Vec* _ret, til_AllocError* _err1, const til_Type til_T) {
    til_Vec til_vec = {.type_name = ((til_Str){(til_I64)"", 0}), .type_size = 0, .ptr = 0, ._len = 0, .cap = 0};
    til_vec.type_name = ((til_Str){(til_I64)"T", 1});
    til_vec.type_size = til_size_of(((til_Str){(til_I64)til_T, strlen(til_T)}));
    const til_I64 til_size_bytes = til_mul(til_Vec_INIT_CAP, til_vec.type_size);
    til_I64 _ret__tmp343;
    til_AllocError _err0__tmp343 = {};
    int _status__tmp343 = til_malloc(&_ret__tmp343, &_err0__tmp343, til_size_bytes);
    if (_status__tmp343 == 1) { *_err1 = _err0__tmp343; return 1; }
    til_vec.ptr = _ret__tmp343;
    til_vec._len = 0;
    til_vec.cap = til_Vec_INIT_CAP;
    *_ret = til_vec;
    return 0;
}

int til_Vec_new_from_type_info(til_Vec* _ret, til_AllocError* _err1, const til_Str til_type_name, const til_I64 til_type_size) {
    til_Vec til_vec = {.type_name = ((til_Str){(til_I64)"", 0}), .type_size = 0, .ptr = 0, ._len = 0, .cap = 0};
    til_vec.type_name = til_type_name;
    til_vec.type_size = til_type_size;
    const til_I64 til_size_bytes = til_mul(til_Vec_INIT_CAP, til_vec.type_size);
    til_I64 _ret__tmp345;
    til_AllocError _err0__tmp345 = {};
    int _status__tmp345 = til_malloc(&_ret__tmp345, &_err0__tmp345, til_size_bytes);
    if (_status__tmp345 == 1) { *_err1 = _err0__tmp345; return 1; }
    til_vec.ptr = _ret__tmp345;
    til_vec._len = 0;
    til_vec.cap = til_Vec_INIT_CAP;
    *_ret = til_vec;
    return 0;
}

int til_Vec_push(til_AllocError* _err1, til_Vec* til_self, const til_Dynamic til_value) {
    if (til_I64_eq(til_self->_len, til_self->cap).data) {
        const til_I64 til_new_cap = til_mul(til_self->cap, 2);
        if (til_gt(til_new_cap, til_Vec_MAX_CAP).data) {
            til_Array _tmp349;
            til_AllocError _err_alloc__tmp350;
            til_IndexOutOfBoundsError _err_idx__tmp350;
            til_Str _tmp351 = ((til_Str){(til_I64)"Vec.push: capacity exceeded Vec.MAX_CAP", 39});
            int _arr_status__tmp350 = til_Array_new(&_tmp349, &_err_alloc__tmp350, "Str", 1);
            if (_arr_status__tmp350 != 0) {
                *_err1 = _err_alloc__tmp350; return 1;
            }
            _arr_status__tmp350 = til_Array_set(&_err_idx__tmp350, &_tmp349, 0, &_tmp351);
            if (_arr_status__tmp350 != 0) {
            }
            til_panic(((til_Str){(til_I64)"src/test/constfold.til:63:23:", 29}), &_tmp349);
            til_Array_delete(&_tmp349);
        }
        til_I64 _ret__tmp352;
        til_I64 til_new_ptr;
        til_AllocError _err0__tmp352 = {};
        int _status__tmp352 = til_malloc(&_ret__tmp352, &_err0__tmp352, til_mul(til_new_cap, til_self->type_size));
        if (_status__tmp352 == 1) { *_err1 = _err0__tmp352; return 1; }
        til_new_ptr = _ret__tmp352;
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
    if (til_gteq(til_index, til_self._len).data) {
        til_Str _tmp355;
        til_I64_OverflowError _err0__tmp356;
        til_IndexOutOfBoundsError _err1__tmp356;
        til_AllocError _err2__tmp356;
        til_Array _tmp357;
        til_AllocError _err_alloc__tmp358;
        til_IndexOutOfBoundsError _err_idx__tmp358;
        til_Str _tmp359 = ((til_Str){(til_I64)"Vec.get: index out of bounds", 28});
        int _arr_status__tmp358 = til_Array_new(&_tmp357, &_err_alloc__tmp358, "Str", 1);
        if (_arr_status__tmp358 != 0) {
        }
        _arr_status__tmp358 = til_Array_set(&_err_idx__tmp358, &_tmp357, 0, &_tmp359);
        if (_arr_status__tmp358 != 0) {
            *_err1 = _err_idx__tmp358; return 1;
        }
        int _status__tmp356 = til_format(&_tmp355, &_err0__tmp356, &_err1__tmp356, &_err2__tmp356, ((til_Str){(til_I64)"src/test/constfold.til:81:52:", 29}), &_tmp357);
        if (_status__tmp356 != 0) {
            if (_status__tmp356 == 2) { *_err1 = _err1__tmp356; return 1; }
        }
        til_Array_delete(&_tmp357);
        til_Str _tmp360;
        til_I64_OverflowError _err0__tmp361;
        til_IndexOutOfBoundsError _err1__tmp361;
        til_AllocError _err2__tmp361;
        til_Array _tmp362;
        til_AllocError _err_alloc__tmp363;
        til_IndexOutOfBoundsError _err_idx__tmp363;
        til_Str _tmp364 = ((til_Str){(til_I64)"Vec.get: index out of bounds", 28});
        int _arr_status__tmp363 = til_Array_new(&_tmp362, &_err_alloc__tmp363, "Str", 1);
        if (_arr_status__tmp363 != 0) {
        }
        _arr_status__tmp363 = til_Array_set(&_err_idx__tmp363, &_tmp362, 0, &_tmp364);
        if (_arr_status__tmp363 != 0) {
            *_err1 = _err_idx__tmp363; return 1;
        }
        int _status__tmp361 = til_format(&_tmp360, &_err0__tmp361, &_err1__tmp361, &_err2__tmp361, ((til_Str){(til_I64)"src/test/constfold.til:81:52:", 29}), &_tmp362);
        if (_status__tmp361 != 0) {
            if (_status__tmp361 == 2) { *_err1 = _err1__tmp361; return 1; }
        }
        til_Array_delete(&_tmp362);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp360);
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Vec_set(til_IndexOutOfBoundsError* _err1, til_Vec* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_gteq(til_index, til_self->_len).data) {
        til_Str _tmp367;
        til_I64_OverflowError _err0__tmp368;
        til_IndexOutOfBoundsError _err1__tmp368;
        til_AllocError _err2__tmp368;
        til_Array _tmp369;
        til_AllocError _err_alloc__tmp370;
        til_IndexOutOfBoundsError _err_idx__tmp370;
        til_Str _tmp371 = ((til_Str){(til_I64)"Vec.set: index out of bounds", 28});
        int _arr_status__tmp370 = til_Array_new(&_tmp369, &_err_alloc__tmp370, "Str", 1);
        if (_arr_status__tmp370 != 0) {
        }
        _arr_status__tmp370 = til_Array_set(&_err_idx__tmp370, &_tmp369, 0, &_tmp371);
        if (_arr_status__tmp370 != 0) {
            *_err1 = _err_idx__tmp370; return 1;
        }
        int _status__tmp368 = til_format(&_tmp367, &_err0__tmp368, &_err1__tmp368, &_err2__tmp368, ((til_Str){(til_I64)"src/test/constfold.til:96:52:", 29}), &_tmp369);
        if (_status__tmp368 != 0) {
            if (_status__tmp368 == 2) { *_err1 = _err1__tmp368; return 1; }
        }
        til_Array_delete(&_tmp369);
        til_Str _tmp372;
        til_I64_OverflowError _err0__tmp373;
        til_IndexOutOfBoundsError _err1__tmp373;
        til_AllocError _err2__tmp373;
        til_Array _tmp374;
        til_AllocError _err_alloc__tmp375;
        til_IndexOutOfBoundsError _err_idx__tmp375;
        til_Str _tmp376 = ((til_Str){(til_I64)"Vec.set: index out of bounds", 28});
        int _arr_status__tmp375 = til_Array_new(&_tmp374, &_err_alloc__tmp375, "Str", 1);
        if (_arr_status__tmp375 != 0) {
        }
        _arr_status__tmp375 = til_Array_set(&_err_idx__tmp375, &_tmp374, 0, &_tmp376);
        if (_arr_status__tmp375 != 0) {
            *_err1 = _err_idx__tmp375; return 1;
        }
        int _status__tmp373 = til_format(&_tmp372, &_err0__tmp373, &_err1__tmp373, &_err2__tmp373, ((til_Str){(til_I64)"src/test/constfold.til:96:52:", 29}), &_tmp374);
        if (_status__tmp373 != 0) {
            if (_status__tmp373 == 2) { *_err1 = _err1__tmp373; return 1; }
        }
        til_Array_delete(&_tmp374);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp372);
        return 1;
    }
    til_I64 til_dest = til_add(til_self->ptr, til_mul(til_index, til_self->type_size));
    til_memcpy(til_dest, (til_I64)til_value, til_self->type_size);
    return 0;
}

int til_Vec_pop(til_IndexOutOfBoundsError* _err1, til_Vec* til_self, til_Dynamic* til_dest) {
    if (til_I64_eq(til_self->_len, 0).data) {
        til_Str _tmp379;
        til_I64_OverflowError _err0__tmp380;
        til_IndexOutOfBoundsError _err1__tmp380;
        til_AllocError _err2__tmp380;
        til_Array _tmp381;
        til_AllocError _err_alloc__tmp382;
        til_IndexOutOfBoundsError _err_idx__tmp382;
        til_Str _tmp383 = ((til_Str){(til_I64)"Vec.pop: cannot pop from empty Vec", 34});
        int _arr_status__tmp382 = til_Array_new(&_tmp381, &_err_alloc__tmp382, "Str", 1);
        if (_arr_status__tmp382 != 0) {
        }
        _arr_status__tmp382 = til_Array_set(&_err_idx__tmp382, &_tmp381, 0, &_tmp383);
        if (_arr_status__tmp382 != 0) {
            *_err1 = _err_idx__tmp382; return 1;
        }
        int _status__tmp380 = til_format(&_tmp379, &_err0__tmp380, &_err1__tmp380, &_err2__tmp380, ((til_Str){(til_I64)"src/test/constfold.til:110:52:", 30}), &_tmp381);
        if (_status__tmp380 != 0) {
            if (_status__tmp380 == 2) { *_err1 = _err1__tmp380; return 1; }
        }
        til_Array_delete(&_tmp381);
        til_Str _tmp384;
        til_I64_OverflowError _err0__tmp385;
        til_IndexOutOfBoundsError _err1__tmp385;
        til_AllocError _err2__tmp385;
        til_Array _tmp386;
        til_AllocError _err_alloc__tmp387;
        til_IndexOutOfBoundsError _err_idx__tmp387;
        til_Str _tmp388 = ((til_Str){(til_I64)"Vec.pop: cannot pop from empty Vec", 34});
        int _arr_status__tmp387 = til_Array_new(&_tmp386, &_err_alloc__tmp387, "Str", 1);
        if (_arr_status__tmp387 != 0) {
        }
        _arr_status__tmp387 = til_Array_set(&_err_idx__tmp387, &_tmp386, 0, &_tmp388);
        if (_arr_status__tmp387 != 0) {
            *_err1 = _err_idx__tmp387; return 1;
        }
        int _status__tmp385 = til_format(&_tmp384, &_err0__tmp385, &_err1__tmp385, &_err2__tmp385, ((til_Str){(til_I64)"src/test/constfold.til:110:52:", 30}), &_tmp386);
        if (_status__tmp385 != 0) {
            if (_status__tmp385 == 2) { *_err1 = _err1__tmp385; return 1; }
        }
        til_Array_delete(&_tmp386);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp384);
        return 1;
    }
    til_I64 til_last_index = til_sub(til_self->_len, 1);
    til_IndexOutOfBoundsError _err0__tmp389 = {};
    int _status__tmp389 = til_Vec_get(&_err0__tmp389, (*til_self), til_last_index, (til_Dynamic*)&til_dest);
    if (_status__tmp389 == 1) { *_err1 = _err0__tmp389; return 1; }
    til_self->_len = til_last_index;
    return 0;
}

void til_Vec_delete(til_Vec* til_self) {
    til_free(til_self->ptr);
    til_self->ptr = 0;
    til_self->_len = 0;
    til_self->cap = 0;
}

int til_Vec_clone(til_Vec* _ret, til_AllocError* _err1, const til_Vec til_self) {
    til_Vec til_cloned = {.type_name = ((til_Str){(til_I64)"", 0}), .type_size = 0, .ptr = 0, ._len = 0, .cap = 0};
    til_cloned.type_name = til_self.type_name;
    til_cloned.type_size = til_self.type_size;
    til_cloned._len = til_self._len;
    til_cloned.cap = til_self.cap;
    til_I64 til_total_bytes = til_mul(til_self.cap, til_self.type_size);
    til_I64 _ret__tmp392;
    til_AllocError _err0__tmp392 = {};
    int _status__tmp392 = til_malloc(&_ret__tmp392, &_err0__tmp392, til_total_bytes);
    if (_status__tmp392 == 1) { *_err1 = _err0__tmp392; return 1; }
    til_cloned.ptr = _ret__tmp392;
    if (til_I64_eq(til_NULL, til_cloned.ptr).data) {
        til_Str _tmp394;
        til_I64_OverflowError _err0__tmp395;
        til_IndexOutOfBoundsError _err1__tmp395;
        til_AllocError _err2__tmp395;
        til_Array _tmp396;
        til_AllocError _err_alloc__tmp397;
        til_IndexOutOfBoundsError _err_idx__tmp397;
        til_Str _tmp398 = ((til_Str){(til_I64)"Vec.clone: malloc failed for ", 29});
        til_Str _tmp399 = til_I64_to_str(til_total_bytes);
        til_Str _tmp400 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp397 = til_Array_new(&_tmp396, &_err_alloc__tmp397, "Str", 3);
        if (_arr_status__tmp397 != 0) {
            *_err1 = _err_alloc__tmp397; return 1;
        }
        _arr_status__tmp397 = til_Array_set(&_err_idx__tmp397, &_tmp396, 0, &_tmp398);
        if (_arr_status__tmp397 != 0) {
        }
        _arr_status__tmp397 = til_Array_set(&_err_idx__tmp397, &_tmp396, 1, &_tmp399);
        if (_arr_status__tmp397 != 0) {
        }
        _arr_status__tmp397 = til_Array_set(&_err_idx__tmp397, &_tmp396, 2, &_tmp400);
        if (_arr_status__tmp397 != 0) {
        }
        int _status__tmp395 = til_format(&_tmp394, &_err0__tmp395, &_err1__tmp395, &_err2__tmp395, ((til_Str){(til_I64)"src/test/constfold.til:139:41:", 30}), &_tmp396);
        if (_status__tmp395 != 0) {
            if (_status__tmp395 == 3) { *_err1 = _err2__tmp395; return 1; }
        }
        til_Array_delete(&_tmp396);
        til_Str _tmp401;
        til_I64_OverflowError _err0__tmp402;
        til_IndexOutOfBoundsError _err1__tmp402;
        til_AllocError _err2__tmp402;
        til_Array _tmp403;
        til_AllocError _err_alloc__tmp404;
        til_IndexOutOfBoundsError _err_idx__tmp404;
        til_Str _tmp405 = ((til_Str){(til_I64)"Vec.clone: malloc failed for ", 29});
        til_Str _tmp406 = til_I64_to_str(til_total_bytes);
        til_Str _tmp407 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp404 = til_Array_new(&_tmp403, &_err_alloc__tmp404, "Str", 3);
        if (_arr_status__tmp404 != 0) {
            *_err1 = _err_alloc__tmp404; return 1;
        }
        _arr_status__tmp404 = til_Array_set(&_err_idx__tmp404, &_tmp403, 0, &_tmp405);
        if (_arr_status__tmp404 != 0) {
        }
        _arr_status__tmp404 = til_Array_set(&_err_idx__tmp404, &_tmp403, 1, &_tmp406);
        if (_arr_status__tmp404 != 0) {
        }
        _arr_status__tmp404 = til_Array_set(&_err_idx__tmp404, &_tmp403, 2, &_tmp407);
        if (_arr_status__tmp404 != 0) {
        }
        int _status__tmp402 = til_format(&_tmp401, &_err0__tmp402, &_err1__tmp402, &_err2__tmp402, ((til_Str){(til_I64)"src/test/constfold.til:139:41:", 30}), &_tmp403);
        if (_status__tmp402 != 0) {
            if (_status__tmp402 == 3) { *_err1 = _err2__tmp402; return 1; }
        }
        til_Array_delete(&_tmp403);
        *_err1 = til_AllocError_new(_tmp401);
        return 1;
    }
    til_I64 til_used_bytes = til_mul(til_self._len, til_self.type_size);
    til_memcpy(til_cloned.ptr, til_self.ptr, til_used_bytes);
    *_ret = til_cloned;
    return 0;
}

int til_Vec_extend(til_AllocError* _err1, til_Vec* til_self, const til_Vec til_other) {
    til_I64 til_i = 0;
    while (til_lt(til_i, til_other._len).data) {
        const til_I64 til_src = til_add(til_other.ptr, til_mul(til_i, til_other.type_size));
        if (til_I64_eq(til_self->_len, til_self->cap).data) {
            const til_I64 til_new_cap = til_mul(til_self->cap, 2);
            if (til_gt(til_new_cap, til_Vec_MAX_CAP).data) {
                til_Array _tmp412;
                til_AllocError _err_alloc__tmp413;
                til_IndexOutOfBoundsError _err_idx__tmp413;
                til_Str _tmp414 = ((til_Str){(til_I64)"Vec.extend: capacity exceeded Vec.MAX_CAP", 41});
                int _arr_status__tmp413 = til_Array_new(&_tmp412, &_err_alloc__tmp413, "Str", 1);
                if (_arr_status__tmp413 != 0) {
                    *_err1 = _err_alloc__tmp413; return 1;
                }
                _arr_status__tmp413 = til_Array_set(&_err_idx__tmp413, &_tmp412, 0, &_tmp414);
                if (_arr_status__tmp413 != 0) {
                }
                til_panic(((til_Str){(til_I64)"src/test/constfold.til:158:27:", 30}), &_tmp412);
                til_Array_delete(&_tmp412);
            }
            til_I64 _ret__tmp415;
            til_I64 til_new_ptr;
            til_AllocError _err0__tmp415 = {};
            int _status__tmp415 = til_malloc(&_ret__tmp415, &_err0__tmp415, til_mul(til_new_cap, til_self->type_size));
            if (_status__tmp415 == 1) { *_err1 = _err0__tmp415; return 1; }
            til_new_ptr = _ret__tmp415;
            til_memcpy(til_new_ptr, til_self->ptr, til_mul(til_self->_len, til_self->type_size));
            til_free(til_self->ptr);
            til_self->ptr = til_new_ptr;
            til_self->cap = til_new_cap;
        }
        til_I64 til_dest = til_add(til_self->ptr, til_mul(til_self->_len, til_self->type_size));
        til_memcpy(til_dest, til_src, til_self->type_size);
        til_self->_len = til_add(til_self->_len, 1);
        til_i = til_add(til_i, 1);
    }
    return 0;
}

til_Bool til_Vec_contains(const til_Vec til_self, const til_Dynamic til_value) {
    til_I64 til_i = 0;
    while (til_lt(til_i, til_self._len).data) {
        const til_I64 til_src = til_add(til_self.ptr, til_mul(til_i, til_self.type_size));
        if (til_Str_eq(til_self.type_name, ((til_Str){(til_I64)"Str", 3})).data) {
            til_Str til_existing = ((til_Str){(til_I64)"", 0});
            til_memcpy((til_I64)&til_existing, til_src, til_self.type_size);
            til_Str til_val_str = ((til_Str){(til_I64)"", 0});
            til_memcpy((til_I64)&til_val_str, (til_I64)til_value, til_self.type_size);
            if (til_Str_eq(til_val_str, til_existing).data) {
                return true;
            }
        } else {
            if (til_I64_eq(til_memcmp((til_I64)til_value, til_src, til_self.type_size), 0).data) {
                return true;
            }
        }
        til_i = til_add(til_i, 1);
    }
    return false;
}

int til_Vec_remove(til_IndexOutOfBoundsError* _err1, til_Vec* til_self, const til_I64 til_index) {
    if (til_gteq(til_index, til_self->_len).data) {
        til_Str _tmp424;
        til_I64_OverflowError _err0__tmp425;
        til_IndexOutOfBoundsError _err1__tmp425;
        til_AllocError _err2__tmp425;
        til_Array _tmp426;
        til_AllocError _err_alloc__tmp427;
        til_IndexOutOfBoundsError _err_idx__tmp427;
        til_Str _tmp428 = ((til_Str){(til_I64)"Vec.remove: index out of bounds", 31});
        int _arr_status__tmp427 = til_Array_new(&_tmp426, &_err_alloc__tmp427, "Str", 1);
        if (_arr_status__tmp427 != 0) {
        }
        _arr_status__tmp427 = til_Array_set(&_err_idx__tmp427, &_tmp426, 0, &_tmp428);
        if (_arr_status__tmp427 != 0) {
            *_err1 = _err_idx__tmp427; return 1;
        }
        int _status__tmp425 = til_format(&_tmp424, &_err0__tmp425, &_err1__tmp425, &_err2__tmp425, ((til_Str){(til_I64)"src/test/constfold.til:202:52:", 30}), &_tmp426);
        if (_status__tmp425 != 0) {
            if (_status__tmp425 == 2) { *_err1 = _err1__tmp425; return 1; }
        }
        til_Array_delete(&_tmp426);
        til_Str _tmp429;
        til_I64_OverflowError _err0__tmp430;
        til_IndexOutOfBoundsError _err1__tmp430;
        til_AllocError _err2__tmp430;
        til_Array _tmp431;
        til_AllocError _err_alloc__tmp432;
        til_IndexOutOfBoundsError _err_idx__tmp432;
        til_Str _tmp433 = ((til_Str){(til_I64)"Vec.remove: index out of bounds", 31});
        int _arr_status__tmp432 = til_Array_new(&_tmp431, &_err_alloc__tmp432, "Str", 1);
        if (_arr_status__tmp432 != 0) {
        }
        _arr_status__tmp432 = til_Array_set(&_err_idx__tmp432, &_tmp431, 0, &_tmp433);
        if (_arr_status__tmp432 != 0) {
            *_err1 = _err_idx__tmp432; return 1;
        }
        int _status__tmp430 = til_format(&_tmp429, &_err0__tmp430, &_err1__tmp430, &_err2__tmp430, ((til_Str){(til_I64)"src/test/constfold.til:202:52:", 30}), &_tmp431);
        if (_status__tmp430 != 0) {
            if (_status__tmp430 == 2) { *_err1 = _err1__tmp430; return 1; }
        }
        til_Array_delete(&_tmp431);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp429);
        return 1;
    }
    til_I64 til_i = til_index;
    while (til_lt(til_i, til_sub(til_self->_len, 1)).data) {
        const til_I64 til_src = til_add(til_self->ptr, til_mul(til_add(til_i, 1), til_self->type_size));
        til_I64 til_dest = til_add(til_self->ptr, til_mul(til_i, til_self->type_size));
        til_memcpy(til_dest, til_src, til_self->type_size);
        til_i = til_add(til_i, 1);
    }
    til_self->_len = til_sub(til_self->_len, 1);
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
    while (til_lt(til_i, til_self.cap).data) {
        til_I64 til_self_byte = 0;
        til_I64 til_other_byte = 0;
        til_memcpy((til_I64)&til_self_byte, til_add(til_self.c_string, til_i), 1);
        til_memcpy((til_I64)&til_other_byte, til_add(til_other.c_string, til_i), 1);
        if (til_not(til_U8_eq(til_self_byte, til_other_byte)).data) {
            return false;
        }
        til_I64_inc(&til_i);
    }
    return true;
}

til_I64 til_Str_to_i64(const til_Str til_self) {
    return til_I64_from_str(til_self);
}

int til_Str_clone(til_Str* _ret, til_AllocError* _err1, const til_Str til_self) {
    til_Str til_cloned = {.c_string = 0, .cap = 0};
    til_cloned.cap = til_self.cap;
    til_I64 _ret__tmp443;
    til_AllocError _err0__tmp443 = {};
    int _status__tmp443 = til_malloc(&_ret__tmp443, &_err0__tmp443, til_cloned.cap);
    if (_status__tmp443 == 1) { *_err1 = _err0__tmp443; return 1; }
    til_cloned.c_string = _ret__tmp443;
    if (til_I64_eq(til_NULL, til_cloned.c_string).data) {
        til_Str _tmp445;
        til_I64_OverflowError _err0__tmp446;
        til_IndexOutOfBoundsError _err1__tmp446;
        til_AllocError _err2__tmp446;
        til_Array _tmp447;
        til_AllocError _err_alloc__tmp448;
        til_IndexOutOfBoundsError _err_idx__tmp448;
        til_Str _tmp449 = ((til_Str){(til_I64)"Str.clone: malloc failed for ", 29});
        til_Str _tmp450 = til_I64_to_str(til_cloned.cap);
        til_Str _tmp451 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp448 = til_Array_new(&_tmp447, &_err_alloc__tmp448, "Str", 3);
        if (_arr_status__tmp448 != 0) {
            *_err1 = _err_alloc__tmp448; return 1;
        }
        _arr_status__tmp448 = til_Array_set(&_err_idx__tmp448, &_tmp447, 0, &_tmp449);
        if (_arr_status__tmp448 != 0) {
        }
        _arr_status__tmp448 = til_Array_set(&_err_idx__tmp448, &_tmp447, 1, &_tmp450);
        if (_arr_status__tmp448 != 0) {
        }
        _arr_status__tmp448 = til_Array_set(&_err_idx__tmp448, &_tmp447, 2, &_tmp451);
        if (_arr_status__tmp448 != 0) {
        }
        int _status__tmp446 = til_format(&_tmp445, &_err0__tmp446, &_err1__tmp446, &_err2__tmp446, ((til_Str){(til_I64)"src/test/constfold.til:46:41:", 29}), &_tmp447);
        if (_status__tmp446 != 0) {
            if (_status__tmp446 == 3) { *_err1 = _err2__tmp446; return 1; }
        }
        til_Array_delete(&_tmp447);
        til_Str _tmp452;
        til_I64_OverflowError _err0__tmp453;
        til_IndexOutOfBoundsError _err1__tmp453;
        til_AllocError _err2__tmp453;
        til_Array _tmp454;
        til_AllocError _err_alloc__tmp455;
        til_IndexOutOfBoundsError _err_idx__tmp455;
        til_Str _tmp456 = ((til_Str){(til_I64)"Str.clone: malloc failed for ", 29});
        til_Str _tmp457 = til_I64_to_str(til_cloned.cap);
        til_Str _tmp458 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp455 = til_Array_new(&_tmp454, &_err_alloc__tmp455, "Str", 3);
        if (_arr_status__tmp455 != 0) {
            *_err1 = _err_alloc__tmp455; return 1;
        }
        _arr_status__tmp455 = til_Array_set(&_err_idx__tmp455, &_tmp454, 0, &_tmp456);
        if (_arr_status__tmp455 != 0) {
        }
        _arr_status__tmp455 = til_Array_set(&_err_idx__tmp455, &_tmp454, 1, &_tmp457);
        if (_arr_status__tmp455 != 0) {
        }
        _arr_status__tmp455 = til_Array_set(&_err_idx__tmp455, &_tmp454, 2, &_tmp458);
        if (_arr_status__tmp455 != 0) {
        }
        int _status__tmp453 = til_format(&_tmp452, &_err0__tmp453, &_err1__tmp453, &_err2__tmp453, ((til_Str){(til_I64)"src/test/constfold.til:46:41:", 29}), &_tmp454);
        if (_status__tmp453 != 0) {
            if (_status__tmp453 == 3) { *_err1 = _err2__tmp453; return 1; }
        }
        til_Array_delete(&_tmp454);
        *_err1 = til_AllocError_new(_tmp452);
        return 1;
    }
    til_memcpy(til_cloned.c_string, til_self.c_string, til_self.cap);
    *_ret = til_cloned;
    return 0;
}

til_I64 til_Str_size(const til_Str til_self) {
    return til_self.cap;
}

til_Bool til_Str_is_uppercase(const til_Str til_self) {
    if (til_I64_eq(til_self.cap, 0).data) {
        return false;
    }
    til_I64 til_i = 0;
    while (til_lt(til_i, til_self.cap).data) {
        til_I64 til_byte = 0;
        til_memcpy((til_I64)&til_byte, til_add(til_self.c_string, til_i), 1);
        til_I64 til_byte_val = 0;
        til_byte_val = til_U8_to_i64(til_byte);
        if (til_lt(til_byte_val, 65).data) {
            return false;
        }
        if (til_gt(til_byte_val, 90).data) {
            return false;
        }
        til_I64_inc(&til_i);
    }
    return true;
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
    while (til_lt(til_start_idx, til_add(til_max_start, 1)).data) {
        til_Bool til_matches = true;
        til_I64 til_needle_idx = 0;
        while (til_lt(til_needle_idx, til_Str_len(til_needle)).data) {
            til_I64 til_self_byte = 0;
            til_I64 til_needle_byte = 0;
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
    while (til_lt(til_start_idx, til_add(til_max_start, 1)).data) {
        til_Bool til_matches = true;
        til_I64 til_needle_idx = 0;
        while (til_lt(til_needle_idx, til_Str_len(til_needle)).data) {
            til_I64 til_self_byte = 0;
            til_I64 til_needle_byte = 0;
            til_memcpy((til_I64)&til_self_byte, til_add(til_self.c_string, til_add(til_start_idx, til_needle_idx)), 1);
            til_memcpy((til_I64)&til_needle_byte, til_add(til_needle.c_string, til_needle_idx), 1);
            if (til_not(til_U8_eq(til_self_byte, til_needle_byte)).data) {
                til_matches = false;
            }
            til_I64_inc(&til_needle_idx);
        }
        if (til_matches.data) {
            return til_start_idx;
        }
        til_I64_inc(&til_start_idx);
    }
    return -1;
}

til_I64 til_Str_rfind(const til_Str til_self, const til_Str til_needle) {
    if (til_gt(til_Str_len(til_needle), til_Str_len(til_self)).data) {
        return -1;
    }
    if (til_I64_eq(til_Str_len(til_needle), 0).data) {
        return -1;
    }
    til_I64 til_last_found = -1;
    til_I64 til_max_start = til_sub(til_Str_len(til_self), til_Str_len(til_needle));
    til_I64 til_start_idx = 0;
    while (til_lt(til_start_idx, til_add(til_max_start, 1)).data) {
        til_Bool til_matches = true;
        til_I64 til_needle_idx = 0;
        while (til_lt(til_needle_idx, til_Str_len(til_needle)).data) {
            til_I64 til_self_byte = 0;
            til_I64 til_needle_byte = 0;
            til_memcpy((til_I64)&til_self_byte, til_add(til_self.c_string, til_add(til_start_idx, til_needle_idx)), 1);
            til_memcpy((til_I64)&til_needle_byte, til_add(til_needle.c_string, til_needle_idx), 1);
            if (til_not(til_U8_eq(til_self_byte, til_needle_byte)).data) {
                til_matches = false;
            }
            til_I64_inc(&til_needle_idx);
        }
        if (til_matches.data) {
            til_last_found = til_start_idx;
        }
        til_I64_inc(&til_start_idx);
    }
    return til_last_found;
}

int til_Str_replace(til_Str* _ret, til_AllocError* _err1, const til_Str til_self, const til_Str til_from, const til_Str til_to) {
    if (til_I64_eq(til_Str_len(til_from), 0).data) {
        til_Str _ret__tmp495;
        til_AllocError _err0__tmp495 = {};
        int _status__tmp495 = til_Str_clone(&_ret__tmp495, &_err0__tmp495, til_self);
        if (_status__tmp495 == 1) { *_err1 = _err0__tmp495; return 1; }
        *_ret = _ret__tmp495;
        return 0;
    }
    til_I64 til_count = 0;
    til_I64 til_search_start = 0;
    while (til_lteq(til_search_start, til_sub(til_Str_len(til_self), til_Str_len(til_from))).data) {
        til_Bool til_matches = true;
        til_I64 til_i = 0;
        while (til_lt(til_i, til_Str_len(til_from)).data) {
            til_I64 til_self_byte = 0;
            til_I64 til_from_byte = 0;
            til_memcpy((til_I64)&til_self_byte, til_add(til_self.c_string, til_add(til_search_start, til_i)), 1);
            til_memcpy((til_I64)&til_from_byte, til_add(til_from.c_string, til_i), 1);
            if (til_not(til_U8_eq(til_self_byte, til_from_byte)).data) {
                til_matches = false;
            }
            til_I64_inc(&til_i);
        }
        if (til_matches.data) {
            til_count = til_add(til_count, 1);
            til_search_start = til_add(til_search_start, til_Str_len(til_from));
        } else {
            til_search_start = til_add(til_search_start, 1);
        }
    }
    if (til_I64_eq(til_count, 0).data) {
        til_Str _ret__tmp503;
        til_AllocError _err0__tmp503 = {};
        int _status__tmp503 = til_Str_clone(&_ret__tmp503, &_err0__tmp503, til_self);
        if (_status__tmp503 == 1) { *_err1 = _err0__tmp503; return 1; }
        *_ret = _ret__tmp503;
        return 0;
    }
    til_I64 til_new_len = til_add(til_sub(til_Str_len(til_self), til_mul(til_count, til_Str_len(til_from))), til_mul(til_count, til_Str_len(til_to)));
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_new_len;
    til_I64 _ret__tmp504;
    til_AllocError _err0__tmp504 = {};
    int _status__tmp504 = til_malloc(&_ret__tmp504, &_err0__tmp504, til_new_len);
    if (_status__tmp504 == 1) { *_err1 = _err0__tmp504; return 1; }
    til_result.c_string = _ret__tmp504;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Str _tmp506;
        til_I64_OverflowError _err0__tmp507;
        til_IndexOutOfBoundsError _err1__tmp507;
        til_AllocError _err2__tmp507;
        til_Array _tmp508;
        til_AllocError _err_alloc__tmp509;
        til_IndexOutOfBoundsError _err_idx__tmp509;
        til_Str _tmp510 = ((til_Str){(til_I64)"Str.replace: malloc failed for ", 31});
        til_Str _tmp511 = til_I64_to_str(til_new_len);
        til_Str _tmp512 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp509 = til_Array_new(&_tmp508, &_err_alloc__tmp509, "Str", 3);
        if (_arr_status__tmp509 != 0) {
            *_err1 = _err_alloc__tmp509; return 1;
        }
        _arr_status__tmp509 = til_Array_set(&_err_idx__tmp509, &_tmp508, 0, &_tmp510);
        if (_arr_status__tmp509 != 0) {
        }
        _arr_status__tmp509 = til_Array_set(&_err_idx__tmp509, &_tmp508, 1, &_tmp511);
        if (_arr_status__tmp509 != 0) {
        }
        _arr_status__tmp509 = til_Array_set(&_err_idx__tmp509, &_tmp508, 2, &_tmp512);
        if (_arr_status__tmp509 != 0) {
        }
        int _status__tmp507 = til_format(&_tmp506, &_err0__tmp507, &_err1__tmp507, &_err2__tmp507, ((til_Str){(til_I64)"src/test/constfold.til:213:41:", 30}), &_tmp508);
        if (_status__tmp507 != 0) {
            if (_status__tmp507 == 3) { *_err1 = _err2__tmp507; return 1; }
        }
        til_Array_delete(&_tmp508);
        til_Str _tmp513;
        til_I64_OverflowError _err0__tmp514;
        til_IndexOutOfBoundsError _err1__tmp514;
        til_AllocError _err2__tmp514;
        til_Array _tmp515;
        til_AllocError _err_alloc__tmp516;
        til_IndexOutOfBoundsError _err_idx__tmp516;
        til_Str _tmp517 = ((til_Str){(til_I64)"Str.replace: malloc failed for ", 31});
        til_Str _tmp518 = til_I64_to_str(til_new_len);
        til_Str _tmp519 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp516 = til_Array_new(&_tmp515, &_err_alloc__tmp516, "Str", 3);
        if (_arr_status__tmp516 != 0) {
            *_err1 = _err_alloc__tmp516; return 1;
        }
        _arr_status__tmp516 = til_Array_set(&_err_idx__tmp516, &_tmp515, 0, &_tmp517);
        if (_arr_status__tmp516 != 0) {
        }
        _arr_status__tmp516 = til_Array_set(&_err_idx__tmp516, &_tmp515, 1, &_tmp518);
        if (_arr_status__tmp516 != 0) {
        }
        _arr_status__tmp516 = til_Array_set(&_err_idx__tmp516, &_tmp515, 2, &_tmp519);
        if (_arr_status__tmp516 != 0) {
        }
        int _status__tmp514 = til_format(&_tmp513, &_err0__tmp514, &_err1__tmp514, &_err2__tmp514, ((til_Str){(til_I64)"src/test/constfold.til:213:41:", 30}), &_tmp515);
        if (_status__tmp514 != 0) {
            if (_status__tmp514 == 3) { *_err1 = _err2__tmp514; return 1; }
        }
        til_Array_delete(&_tmp515);
        *_err1 = til_AllocError_new(_tmp513);
        return 1;
    }
    til_I64 til_src_idx = 0;
    til_I64 til_dst_idx = 0;
    while (til_lt(til_src_idx, til_Str_len(til_self)).data) {
        til_Bool til_matches = true;
        if (til_lteq(til_src_idx, til_sub(til_Str_len(til_self), til_Str_len(til_from))).data) {
            til_I64 til_i = 0;
            while (til_lt(til_i, til_Str_len(til_from)).data) {
                til_I64 til_self_byte = 0;
                til_I64 til_from_byte = 0;
                til_memcpy((til_I64)&til_self_byte, til_add(til_self.c_string, til_add(til_src_idx, til_i)), 1);
                til_memcpy((til_I64)&til_from_byte, til_add(til_from.c_string, til_i), 1);
                if (til_not(til_U8_eq(til_self_byte, til_from_byte)).data) {
                    til_matches = false;
                }
                til_I64_inc(&til_i);
            }
        } else {
            til_matches = false;
        }
        if (til_matches.data) {
            til_memcpy(til_add(til_result.c_string, til_dst_idx), til_to.c_string, til_Str_len(til_to));
            til_dst_idx = til_add(til_dst_idx, til_Str_len(til_to));
            til_src_idx = til_add(til_src_idx, til_Str_len(til_from));
        } else {
            til_memcpy(til_add(til_result.c_string, til_dst_idx), til_add(til_self.c_string, til_src_idx), 1);
            til_dst_idx = til_add(til_dst_idx, 1);
            til_src_idx = til_add(til_src_idx, 1);
        }
    }
    *_ret = til_result;
    return 0;
}

til_U8 til_Str_char_at(const til_Str til_self, const til_I64 til_index) {
    if (til_lt(til_index, 0).data) {
        til_I64 til_zero = 0;
        return til_zero;
    }
    if (til_gteq(til_index, til_Str_len(til_self)).data) {
        til_I64 til_zero = 0;
        return til_zero;
    }
    til_I64 til_byte_val = 0;
    til_memcpy((til_I64)&til_byte_val, til_add(til_self.c_string, til_index), 1);
    return til_byte_val;
}

int til_Str_replacen(til_Str* _ret, til_AllocError* _err1, const til_Str til_self, const til_Str til_from, const til_Str til_to, const til_I64 til_n) {
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp531;
    if (til_I64_eq(til_Str_len(til_from), 0).data) {
        til_Str _ret__tmp533;
        til_AllocError _err0__tmp533 = {};
        int _status__tmp533 = til_Str_clone(&_ret__tmp533, &_err0__tmp533, til_self);
        if (_status__tmp533 == 1) { *_err1 = _err0__tmp533; return 1; }
        *_ret = _ret__tmp533;
        return 0;
    }
    if (til_I64_eq(til_n, 0).data) {
        til_Str _ret__tmp535;
        til_AllocError _err0__tmp535 = {};
        int _status__tmp535 = til_Str_clone(&_ret__tmp535, &_err0__tmp535, til_self);
        if (_status__tmp535 == 1) { *_err1 = _err0__tmp535; return 1; }
        *_ret = _ret__tmp535;
        return 0;
    }
    til_I64 til_idx = til_Str_find(til_self, til_from);
    if (til_lt(til_idx, 0).data) {
        til_Str _ret__tmp537;
        til_AllocError _err0__tmp537 = {};
        int _status__tmp537 = til_Str_clone(&_ret__tmp537, &_err0__tmp537, til_self);
        if (_status__tmp537 == 1) { *_err1 = _err0__tmp537; return 1; }
        *_ret = _ret__tmp537;
        return 0;
    }
    til_Str _ret__tmp538;
    til_Str til_prefix;
    til_IndexOutOfBoundsError _err0__tmp538 = {};
    til_AllocError _err1__tmp538 = {};
    int _status__tmp538 = til_get_substr(&_ret__tmp538, &_err0__tmp538, &_err1__tmp538, til_self, 0, til_idx);
    if (_status__tmp538 == 2) { *_err1 = _err1__tmp538; return 1; }
    til_prefix = _ret__tmp538;
    til_Str _ret__tmp539;
    til_Str til_suffix;
    til_IndexOutOfBoundsError _err0__tmp539 = {};
    til_AllocError _err1__tmp539 = {};
    int _status__tmp539 = til_get_substr(&_ret__tmp539, &_err0__tmp539, &_err1__tmp539, til_self, til_add(til_idx, til_Str_len(til_from)), til_Str_len(til_self));
    if (_status__tmp539 == 2) { *_err1 = _err1__tmp539; return 1; }
    til_suffix = _ret__tmp539;
    til_Str til_result = til_concat(til_concat(til_prefix, til_to), til_suffix);
    if (til_gt(til_n, 1).data) {
        til_Str _ret__tmp541;
        til_Str til_rest;
        til_AllocError _err0__tmp541 = {};
        int _status__tmp541 = til_Str_replacen(&_ret__tmp541, &_err0__tmp541, til_suffix, til_from, til_to, til_sub(til_n, 1));
        if (_status__tmp541 == 1) { *_err1 = _err0__tmp541; return 1; }
        til_rest = _ret__tmp541;
        til_result = til_concat(til_concat(til_prefix, til_to), til_rest);
    }
    *_ret = til_result;
    return 0;
    goto _end_catches__tmp531;
_catch_IndexOutOfBoundsError__tmp531: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp531;
    til_Str _ret__tmp543;
    til_AllocError _err0__tmp543 = {};
    int _status__tmp543 = til_Str_clone(&_ret__tmp543, &_err0__tmp543, til_self);
    if (_status__tmp543 == 1) { *_err1 = _err0__tmp543; return 1; }
    til_result = _ret__tmp543;
    }
_end_catches__tmp531:;
}

int til_Str_split(til_Vec* _ret, til_AllocError* _err1, til_IndexOutOfBoundsError* _err2, const til_Str til_self, const til_Str til_delimiter) {
    til_Vec _ret__tmp545;
    til_Vec til_parts;
    til_AllocError _err0__tmp545 = {};
    int _status__tmp545 = til_Vec_new(&_ret__tmp545, &_err0__tmp545, "Str");
    if (_status__tmp545 == 1) { *_err1 = _err0__tmp545; return 1; }
    til_parts = _ret__tmp545;
    if (til_I64_eq(til_Str_len(til_delimiter), 0).data) {
        til_Str _tmp548;
        til_AllocError _err0__tmp549;
        int _status__tmp549 = til_Str_clone(&_tmp548, &_err0__tmp549, til_self);
        if (_status__tmp549 != 0) {
            if (_status__tmp549 == 1) { *_err1 = _err0__tmp549; return 1; }
        }
        til_AllocError _err0__tmp547 = {};
        int _status__tmp547 = til_Vec_push(&_err0__tmp547, &til_parts, &_tmp548);
        if (_status__tmp547 == 1) { *_err1 = _err0__tmp547; return 1; }
        *_ret = til_parts;
        return 0;
    }
    til_I64 til_start = 0;
    til_I64 til_pos = 0;
    while (til_lteq(til_pos, til_sub(til_Str_len(til_self), til_Str_len(til_delimiter))).data) {
        til_Bool til_matches = true;
        til_I64 til_i = 0;
        while (til_lt(til_i, til_Str_len(til_delimiter)).data) {
            til_I64 til_self_byte = 0;
            til_I64 til_delim_byte = 0;
            til_memcpy((til_I64)&til_self_byte, til_add(til_self.c_string, til_add(til_pos, til_i)), 1);
            til_memcpy((til_I64)&til_delim_byte, til_add(til_delimiter.c_string, til_i), 1);
            if (til_not(til_U8_eq(til_self_byte, til_delim_byte)).data) {
                til_matches = false;
            }
            til_I64_inc(&til_i);
        }
        if (til_matches.data) {
            if (til_gt(til_pos, til_start).data) {
                til_Str _ret__tmp556;
                til_Str til_part;
                til_IndexOutOfBoundsError _err0__tmp556 = {};
                til_AllocError _err1__tmp556 = {};
                int _status__tmp556 = til_get_substr(&_ret__tmp556, &_err0__tmp556, &_err1__tmp556, til_self, til_start, til_pos);
                if (_status__tmp556 == 1) { *_err2 = _err0__tmp556; return 2; }
                if (_status__tmp556 == 2) { *_err1 = _err1__tmp556; return 1; }
                til_part = _ret__tmp556;
                til_AllocError _err0__tmp557 = {};
                int _status__tmp557 = til_Vec_push(&_err0__tmp557, &til_parts, (til_Dynamic*)&til_part);
                if (_status__tmp557 == 1) { *_err1 = _err0__tmp557; return 1; }
            } else {
                til_Str _tmp560 = ((til_Str){(til_I64)"", 0});
                til_AllocError _err0__tmp559 = {};
                int _status__tmp559 = til_Vec_push(&_err0__tmp559, &til_parts, &_tmp560);
                if (_status__tmp559 == 1) { *_err1 = _err0__tmp559; return 1; }
            }
            til_start = til_add(til_pos, til_Str_len(til_delimiter));
            til_pos = til_start;
        } else {
            til_pos = til_add(til_pos, 1);
        }
    }
    if (til_lt(til_start, til_Str_len(til_self)).data) {
        til_Str _ret__tmp563;
        til_Str til_part;
        til_IndexOutOfBoundsError _err0__tmp563 = {};
        til_AllocError _err1__tmp563 = {};
        int _status__tmp563 = til_get_substr(&_ret__tmp563, &_err0__tmp563, &_err1__tmp563, til_self, til_start, til_Str_len(til_self));
        if (_status__tmp563 == 1) { *_err2 = _err0__tmp563; return 2; }
        if (_status__tmp563 == 2) { *_err1 = _err1__tmp563; return 1; }
        til_part = _ret__tmp563;
        til_AllocError _err0__tmp564 = {};
        int _status__tmp564 = til_Vec_push(&_err0__tmp564, &til_parts, (til_Dynamic*)&til_part);
        if (_status__tmp564 == 1) { *_err1 = _err0__tmp564; return 1; }
    } else {
        if (til_I64_eq(til_start, til_Str_len(til_self)).data) {
            til_Str _tmp568 = ((til_Str){(til_I64)"", 0});
            til_AllocError _err0__tmp567 = {};
            int _status__tmp567 = til_Vec_push(&_err0__tmp567, &til_parts, &_tmp568);
            if (_status__tmp567 == 1) { *_err1 = _err0__tmp567; return 1; }
        }
    }
    *_ret = til_parts;
    return 0;
}

til_U8_OverflowError til_U8_OverflowError_new(const til_Str til_msg) {
    til_U8_OverflowError til_err = {.msg = ((til_Str){(til_I64)"", 0})};
    til_err.msg = til_msg;
    return til_err;
}

til_I64 til_U8_len(const til_I64 til_self) {
    return 1;
}

til_Bool til_U8_eq(const til_U8 til_self, const til_U8 til_other) {
    return til_I64_eq(til_U8_to_i64(til_self), til_U8_to_i64(til_other));
}

til_Bool til_U8_lt(const til_U8 til_self, const til_U8 til_other) {
    return til_lt(til_U8_to_i64(til_self), til_U8_to_i64(til_other));
}

til_Bool til_U8_gt(const til_U8 til_self, const til_U8 til_other) {
    return til_gt(til_U8_to_i64(til_self), til_U8_to_i64(til_other));
}

til_I64 til_U8_to_i64(const til_U8 til_self) {
    return til_u8_to_i64(til_self);
}

int til_U8_u8_add(til_U8* _ret, til_U8_OverflowError* _err1, const til_U8 til_a, const til_U8 til_b) {
    til_U8 _ret__tmp576;
    til_U8_OverflowError _err0__tmp576 = {};
    int _status__tmp576 = til_U8_from_i64(&_ret__tmp576, &_err0__tmp576, til_add(til_U8_to_i64(til_a), til_U8_to_i64(til_b)));
    if (_status__tmp576 == 1) { *_err1 = _err0__tmp576; return 1; }
    *_ret = _ret__tmp576;
    return 0;
}

int til_U8_from_i64(til_U8* _ret, til_U8_OverflowError* _err1, const til_I64 til_self) {
    if (til_lt(til_self, 0).data) {
        til_Str _tmp579;
        til_I64_OverflowError _err0__tmp580;
        til_IndexOutOfBoundsError _err1__tmp580;
        til_AllocError _err2__tmp580;
        til_Array _tmp581;
        til_AllocError _err_alloc__tmp582;
        til_IndexOutOfBoundsError _err_idx__tmp582;
        til_Str _tmp583 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        int _arr_status__tmp582 = til_Array_new(&_tmp581, &_err_alloc__tmp582, "Str", 1);
        if (_arr_status__tmp582 != 0) {
        }
        _arr_status__tmp582 = til_Array_set(&_err_idx__tmp582, &_tmp581, 0, &_tmp583);
        if (_arr_status__tmp582 != 0) {
        }
        int _status__tmp580 = til_format(&_tmp579, &_err0__tmp580, &_err1__tmp580, &_err2__tmp580, ((til_Str){(til_I64)"src/test/constfold.til:56:47:", 29}), &_tmp581);
        if (_status__tmp580 != 0) {
        }
        til_Array_delete(&_tmp581);
        til_Str _tmp584;
        til_I64_OverflowError _err0__tmp585;
        til_IndexOutOfBoundsError _err1__tmp585;
        til_AllocError _err2__tmp585;
        til_Array _tmp586;
        til_AllocError _err_alloc__tmp587;
        til_IndexOutOfBoundsError _err_idx__tmp587;
        til_Str _tmp588 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        int _arr_status__tmp587 = til_Array_new(&_tmp586, &_err_alloc__tmp587, "Str", 1);
        if (_arr_status__tmp587 != 0) {
        }
        _arr_status__tmp587 = til_Array_set(&_err_idx__tmp587, &_tmp586, 0, &_tmp588);
        if (_arr_status__tmp587 != 0) {
        }
        int _status__tmp585 = til_format(&_tmp584, &_err0__tmp585, &_err1__tmp585, &_err2__tmp585, ((til_Str){(til_I64)"src/test/constfold.til:56:47:", 29}), &_tmp586);
        if (_status__tmp585 != 0) {
        }
        til_Array_delete(&_tmp586);
        *_err1 = til_U8_OverflowError_new(_tmp584);
        return 1;
    }
    if (til_gt(til_self, til_MAX_U8).data) {
        til_Str _tmp590;
        til_I64_OverflowError _err0__tmp591;
        til_IndexOutOfBoundsError _err1__tmp591;
        til_AllocError _err2__tmp591;
        til_Array _tmp592;
        til_AllocError _err_alloc__tmp593;
        til_IndexOutOfBoundsError _err_idx__tmp593;
        til_Str _tmp594 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp595 = ((til_Str){(til_I64)"255", 3});
        int _arr_status__tmp593 = til_Array_new(&_tmp592, &_err_alloc__tmp593, "Str", 2);
        if (_arr_status__tmp593 != 0) {
        }
        _arr_status__tmp593 = til_Array_set(&_err_idx__tmp593, &_tmp592, 0, &_tmp594);
        if (_arr_status__tmp593 != 0) {
        }
        _arr_status__tmp593 = til_Array_set(&_err_idx__tmp593, &_tmp592, 1, &_tmp595);
        if (_arr_status__tmp593 != 0) {
        }
        int _status__tmp591 = til_format(&_tmp590, &_err0__tmp591, &_err1__tmp591, &_err2__tmp591, ((til_Str){(til_I64)"src/test/constfold.til:59:47:", 29}), &_tmp592);
        if (_status__tmp591 != 0) {
        }
        til_Array_delete(&_tmp592);
        til_Str _tmp596;
        til_I64_OverflowError _err0__tmp597;
        til_IndexOutOfBoundsError _err1__tmp597;
        til_AllocError _err2__tmp597;
        til_Array _tmp598;
        til_AllocError _err_alloc__tmp599;
        til_IndexOutOfBoundsError _err_idx__tmp599;
        til_Str _tmp600 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp601 = ((til_Str){(til_I64)"255", 3});
        int _arr_status__tmp599 = til_Array_new(&_tmp598, &_err_alloc__tmp599, "Str", 2);
        if (_arr_status__tmp599 != 0) {
        }
        _arr_status__tmp599 = til_Array_set(&_err_idx__tmp599, &_tmp598, 0, &_tmp600);
        if (_arr_status__tmp599 != 0) {
        }
        _arr_status__tmp599 = til_Array_set(&_err_idx__tmp599, &_tmp598, 1, &_tmp601);
        if (_arr_status__tmp599 != 0) {
        }
        int _status__tmp597 = til_format(&_tmp596, &_err0__tmp597, &_err1__tmp597, &_err2__tmp597, ((til_Str){(til_I64)"src/test/constfold.til:59:47:", 29}), &_tmp598);
        if (_status__tmp597 != 0) {
        }
        til_Array_delete(&_tmp598);
        *_err1 = til_U8_OverflowError_new(_tmp596);
        return 1;
    }
    *_ret = til_i64_to_u8(til_self);
    return 0;
}

til_Str til_U8_to_str(const til_U8 til_self) {
    return til_I64_to_str(til_U8_to_i64(til_self));
}

int til_U8_from_str(til_U8* _ret, til_U8_OverflowError* _err1, const til_Str til_s) {
    til_U8 _ret__tmp604;
    til_U8_OverflowError _err0__tmp604 = {};
    int _status__tmp604 = til_U8_from_i64(&_ret__tmp604, &_err0__tmp604, til_I64_from_str(til_s));
    if (_status__tmp604 == 1) { *_err1 = _err0__tmp604; return 1; }
    *_ret = _ret__tmp604;
    return 0;
}

til_I64 til_U8_size(void) {
    return 1;
}

til_CfVec2 til_CfVec2_magic(void) {
    return (til_CfVec2){.x = 42, .y = 99};
}

til_CfVec2 til_CfVec2_at(const til_I64 til_x, const til_I64 til_y) {
    return (til_CfVec2){.x = til_x, .y = til_y};
}

til_CfRect til_CfRect_sample(void) {
    return (til_CfRect){.top_left = (til_CfVec2){.x = 5, .y = 10}, .bottom_right = (til_CfVec2){.x = 100, .y = 200}};
}

int main() {
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
