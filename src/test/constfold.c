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
void til_test_no_fold_variable(void);
void til_test_loc_folded_correctly(void);
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

void til_test_no_fold_variable(void) {
    const til_I64 til_x = 5;
    const til_I64 til_result = til_add(til_x, 3);
    til_test(((til_Str){(til_I64)"src/test/constfold.til:39:10:", 29}), til_I64_eq(til_result, 8), ((til_Str){(til_I64)"add(x, 3) should still work at runtime", 38}));
}

void til_test_loc_folded_correctly(void) {
    const til_Str til_location = ((til_Str){(til_I64)"src/test/constfold.til:45:17:", 29});
    til_test(((til_Str){(til_I64)"src/test/constfold.til:46:10:", 29}), til_Str_contains(til_location, ((til_Str){(til_I64)"constfold.til", 13})), ((til_Str){(til_I64)"loc() should contain filename", 29}));
    til_test(((til_Str){(til_I64)"src/test/constfold.til:47:10:", 29}), til_Str_contains(til_location, ((til_Str){(til_I64)":45:", 4})), ((til_Str){(til_I64)"loc() should contain correct line number", 40}));
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
    til_I64 _ret__tmp252;
    til_AllocError _err0__tmp252 = {};
    int _status__tmp252 = til_malloc(&_ret__tmp252, &_err0__tmp252, til_size_bytes);
    if (_status__tmp252 == 1) { *_err1 = _err0__tmp252; return 1; }
    til_arr.ptr = _ret__tmp252;
    til_U8 _tmp253;
    til_U8_OverflowError _err0__tmp254;
    int _status__tmp254 = til_U8_from_i64(&_tmp253, &_err0__tmp254, 0);
    if (_status__tmp254 != 0) {
    }
    til_memset(til_arr.ptr, _tmp253, til_size_bytes);
    til_arr._len = til_capacity;
    *_ret = til_arr;
    return 0;
}

int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array til_self, const til_I64 til_index, til_Dynamic* til_T) {
    if (til_gteq(til_index, til_self._len).data) {
        til_Str _tmp257;
        til_I64_OverflowError _err0__tmp258;
        til_IndexOutOfBoundsError _err1__tmp258;
        til_AllocError _err2__tmp258;
        til_Array _tmp259;
        til_AllocError _err_alloc__tmp260;
        til_IndexOutOfBoundsError _err_idx__tmp260;
        til_Str _tmp261 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        int _arr_status__tmp260 = til_Array_new(&_tmp259, &_err_alloc__tmp260, "Str", 1);
        if (_arr_status__tmp260 != 0) {
        }
        _arr_status__tmp260 = til_Array_set(&_err_idx__tmp260, &_tmp259, 0, &_tmp261);
        if (_arr_status__tmp260 != 0) {
            *_err1 = _err_idx__tmp260; return 1;
        }
        int _status__tmp258 = til_format(&_tmp257, &_err0__tmp258, &_err1__tmp258, &_err2__tmp258, ((til_Str){(til_I64)"src/test/constfold.til:41:52:", 29}), &_tmp259);
        if (_status__tmp258 != 0) {
            if (_status__tmp258 == 2) { *_err1 = _err1__tmp258; return 1; }
        }
        til_Array_delete(&_tmp259);
        til_Str _tmp262;
        til_I64_OverflowError _err0__tmp263;
        til_IndexOutOfBoundsError _err1__tmp263;
        til_AllocError _err2__tmp263;
        til_Array _tmp264;
        til_AllocError _err_alloc__tmp265;
        til_IndexOutOfBoundsError _err_idx__tmp265;
        til_Str _tmp266 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        int _arr_status__tmp265 = til_Array_new(&_tmp264, &_err_alloc__tmp265, "Str", 1);
        if (_arr_status__tmp265 != 0) {
        }
        _arr_status__tmp265 = til_Array_set(&_err_idx__tmp265, &_tmp264, 0, &_tmp266);
        if (_arr_status__tmp265 != 0) {
            *_err1 = _err_idx__tmp265; return 1;
        }
        int _status__tmp263 = til_format(&_tmp262, &_err0__tmp263, &_err1__tmp263, &_err2__tmp263, ((til_Str){(til_I64)"src/test/constfold.til:41:52:", 29}), &_tmp264);
        if (_status__tmp263 != 0) {
            if (_status__tmp263 == 2) { *_err1 = _err1__tmp263; return 1; }
        }
        til_Array_delete(&_tmp264);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp262);
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_gteq(til_index, til_self->_len).data) {
        til_Str _tmp269;
        til_I64_OverflowError _err0__tmp270;
        til_IndexOutOfBoundsError _err1__tmp270;
        til_AllocError _err2__tmp270;
        til_Array _tmp271;
        til_AllocError _err_alloc__tmp272;
        til_IndexOutOfBoundsError _err_idx__tmp272;
        til_Str _tmp273 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        int _arr_status__tmp272 = til_Array_new(&_tmp271, &_err_alloc__tmp272, "Str", 1);
        if (_arr_status__tmp272 != 0) {
        }
        _arr_status__tmp272 = til_Array_set(&_err_idx__tmp272, &_tmp271, 0, &_tmp273);
        if (_arr_status__tmp272 != 0) {
            *_err1 = _err_idx__tmp272; return 1;
        }
        int _status__tmp270 = til_format(&_tmp269, &_err0__tmp270, &_err1__tmp270, &_err2__tmp270, ((til_Str){(til_I64)"src/test/constfold.til:56:52:", 29}), &_tmp271);
        if (_status__tmp270 != 0) {
            if (_status__tmp270 == 2) { *_err1 = _err1__tmp270; return 1; }
        }
        til_Array_delete(&_tmp271);
        til_Str _tmp274;
        til_I64_OverflowError _err0__tmp275;
        til_IndexOutOfBoundsError _err1__tmp275;
        til_AllocError _err2__tmp275;
        til_Array _tmp276;
        til_AllocError _err_alloc__tmp277;
        til_IndexOutOfBoundsError _err_idx__tmp277;
        til_Str _tmp278 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        int _arr_status__tmp277 = til_Array_new(&_tmp276, &_err_alloc__tmp277, "Str", 1);
        if (_arr_status__tmp277 != 0) {
        }
        _arr_status__tmp277 = til_Array_set(&_err_idx__tmp277, &_tmp276, 0, &_tmp278);
        if (_arr_status__tmp277 != 0) {
            *_err1 = _err_idx__tmp277; return 1;
        }
        int _status__tmp275 = til_format(&_tmp274, &_err0__tmp275, &_err1__tmp275, &_err2__tmp275, ((til_Str){(til_I64)"src/test/constfold.til:56:52:", 29}), &_tmp276);
        if (_status__tmp275 != 0) {
            if (_status__tmp275 == 2) { *_err1 = _err1__tmp275; return 1; }
        }
        til_Array_delete(&_tmp276);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp274);
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
    til_I64 _ret__tmp281;
    til_AllocError _err0__tmp281 = {};
    int _status__tmp281 = til_malloc(&_ret__tmp281, &_err0__tmp281, til_total_bytes);
    if (_status__tmp281 == 1) { *_err1 = _err0__tmp281; return 1; }
    til_cloned.ptr = _ret__tmp281;
    if (til_I64_eq(til_NULL, til_cloned.ptr).data) {
        til_Str _tmp283;
        til_I64_OverflowError _err0__tmp284;
        til_IndexOutOfBoundsError _err1__tmp284;
        til_AllocError _err2__tmp284;
        til_Array _tmp285;
        til_AllocError _err_alloc__tmp286;
        til_IndexOutOfBoundsError _err_idx__tmp286;
        til_Str _tmp287 = ((til_Str){(til_I64)"Array.clone: malloc failed for ", 31});
        til_Str _tmp288 = til_I64_to_str(til_total_bytes);
        til_Str _tmp289 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp286 = til_Array_new(&_tmp285, &_err_alloc__tmp286, "Str", 3);
        if (_arr_status__tmp286 != 0) {
            *_err1 = _err_alloc__tmp286; return 1;
        }
        _arr_status__tmp286 = til_Array_set(&_err_idx__tmp286, &_tmp285, 0, &_tmp287);
        if (_arr_status__tmp286 != 0) {
        }
        _arr_status__tmp286 = til_Array_set(&_err_idx__tmp286, &_tmp285, 1, &_tmp288);
        if (_arr_status__tmp286 != 0) {
        }
        _arr_status__tmp286 = til_Array_set(&_err_idx__tmp286, &_tmp285, 2, &_tmp289);
        if (_arr_status__tmp286 != 0) {
        }
        int _status__tmp284 = til_format(&_tmp283, &_err0__tmp284, &_err1__tmp284, &_err2__tmp284, ((til_Str){(til_I64)"src/test/constfold.til:83:41:", 29}), &_tmp285);
        if (_status__tmp284 != 0) {
            if (_status__tmp284 == 3) { *_err1 = _err2__tmp284; return 1; }
        }
        til_Array_delete(&_tmp285);
        til_Str _tmp290;
        til_I64_OverflowError _err0__tmp291;
        til_IndexOutOfBoundsError _err1__tmp291;
        til_AllocError _err2__tmp291;
        til_Array _tmp292;
        til_AllocError _err_alloc__tmp293;
        til_IndexOutOfBoundsError _err_idx__tmp293;
        til_Str _tmp294 = ((til_Str){(til_I64)"Array.clone: malloc failed for ", 31});
        til_Str _tmp295 = til_I64_to_str(til_total_bytes);
        til_Str _tmp296 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp293 = til_Array_new(&_tmp292, &_err_alloc__tmp293, "Str", 3);
        if (_arr_status__tmp293 != 0) {
            *_err1 = _err_alloc__tmp293; return 1;
        }
        _arr_status__tmp293 = til_Array_set(&_err_idx__tmp293, &_tmp292, 0, &_tmp294);
        if (_arr_status__tmp293 != 0) {
        }
        _arr_status__tmp293 = til_Array_set(&_err_idx__tmp293, &_tmp292, 1, &_tmp295);
        if (_arr_status__tmp293 != 0) {
        }
        _arr_status__tmp293 = til_Array_set(&_err_idx__tmp293, &_tmp292, 2, &_tmp296);
        if (_arr_status__tmp293 != 0) {
        }
        int _status__tmp291 = til_format(&_tmp290, &_err0__tmp291, &_err1__tmp291, &_err2__tmp291, ((til_Str){(til_I64)"src/test/constfold.til:83:41:", 29}), &_tmp292);
        if (_status__tmp291 != 0) {
            if (_status__tmp291 == 3) { *_err1 = _err2__tmp291; return 1; }
        }
        til_Array_delete(&_tmp292);
        *_err1 = til_AllocError_new(_tmp290);
        return 1;
    }
    til_memcpy(til_cloned.ptr, til_self.ptr, til_total_bytes);
    *_ret = til_cloned;
    return 0;
}

til_Bool til_Array_contains(const til_Array til_self, const til_Str til_value) {
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp297;
    til_I64 til_i = 0;
    while (til_lt(til_i, til_self._len).data) {
        til_Str til_elem = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp299 = {};
        int _status__tmp299 = til_Array_get(&_err0__tmp299, til_self, til_i, (til_Dynamic*)&til_elem);
        if (_status__tmp299 == 1) { _thrown_IndexOutOfBoundsError__tmp297 = _err0__tmp299; goto _catch_IndexOutOfBoundsError__tmp297; }
        if (til_Str_eq(til_elem, til_value).data) {
            return true;
        }
        til_i = til_add(til_i, 1);
    }
    return false;
    goto _end_catches__tmp297;
_catch_IndexOutOfBoundsError__tmp297: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp297;
    }
_end_catches__tmp297:;
}

til_I64 til_Bool_len(const til_Bool til_self) {
    return 1;
}

til_Bool til_Bool_eq(const til_Bool til_a, const til_Bool til_b) {
    til_Bool _tmp304;
    til_Array _tmp305;
    til_AllocError _err_alloc__tmp306;
    til_IndexOutOfBoundsError _err_idx__tmp306;
    til_Bool _tmp307 = til_a;
    til_Bool _tmp308 = til_b;
    int _arr_status__tmp306 = til_Array_new(&_tmp305, &_err_alloc__tmp306, "Bool", 2);
    if (_arr_status__tmp306 != 0) {
    }
    _arr_status__tmp306 = til_Array_set(&_err_idx__tmp306, &_tmp305, 0, &_tmp307);
    if (_arr_status__tmp306 != 0) {
    }
    _arr_status__tmp306 = til_Array_set(&_err_idx__tmp306, &_tmp305, 1, &_tmp308);
    if (_arr_status__tmp306 != 0) {
    }
    _tmp304 = til_and(&_tmp305);
    til_Array_delete(&_tmp305);
    til_Bool _tmp309;
    til_Array _tmp310;
    til_AllocError _err_alloc__tmp311;
    til_IndexOutOfBoundsError _err_idx__tmp311;
    til_Bool _tmp312 = til_not(til_b);
    til_Bool _tmp313 = til_not(til_a);
    int _arr_status__tmp311 = til_Array_new(&_tmp310, &_err_alloc__tmp311, "Bool", 2);
    if (_arr_status__tmp311 != 0) {
    }
    _arr_status__tmp311 = til_Array_set(&_err_idx__tmp311, &_tmp310, 0, &_tmp312);
    if (_arr_status__tmp311 != 0) {
    }
    _arr_status__tmp311 = til_Array_set(&_err_idx__tmp311, &_tmp310, 1, &_tmp313);
    if (_arr_status__tmp311 != 0) {
    }
    _tmp309 = til_and(&_tmp310);
    til_Array_delete(&_tmp310);
    til_Array _tmp314;
    til_AllocError _err_alloc__tmp315;
    til_IndexOutOfBoundsError _err_idx__tmp315;
    int _arr_status__tmp315 = til_Array_new(&_tmp314, &_err_alloc__tmp315, "Bool", 2);
    if (_arr_status__tmp315 != 0) {
    }
    _arr_status__tmp315 = til_Array_set(&_err_idx__tmp315, &_tmp314, 0, &_tmp304);
    if (_arr_status__tmp315 != 0) {
    }
    _arr_status__tmp315 = til_Array_set(&_err_idx__tmp315, &_tmp314, 1, &_tmp309);
    if (_arr_status__tmp315 != 0) {
    }
    til_Bool _tmp316 = til_or(&_tmp314);
    til_Array_delete(&_tmp314);
    return _tmp316;
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
    til_I64 _ret__tmp340;
    til_AllocError _err0__tmp340 = {};
    int _status__tmp340 = til_malloc(&_ret__tmp340, &_err0__tmp340, til_size_bytes);
    if (_status__tmp340 == 1) { *_err1 = _err0__tmp340; return 1; }
    til_vec.ptr = _ret__tmp340;
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
    til_I64 _ret__tmp342;
    til_AllocError _err0__tmp342 = {};
    int _status__tmp342 = til_malloc(&_ret__tmp342, &_err0__tmp342, til_size_bytes);
    if (_status__tmp342 == 1) { *_err1 = _err0__tmp342; return 1; }
    til_vec.ptr = _ret__tmp342;
    til_vec._len = 0;
    til_vec.cap = til_Vec_INIT_CAP;
    *_ret = til_vec;
    return 0;
}

int til_Vec_push(til_AllocError* _err1, til_Vec* til_self, const til_Dynamic til_value) {
    if (til_I64_eq(til_self->_len, til_self->cap).data) {
        const til_I64 til_new_cap = til_mul(til_self->cap, 2);
        if (til_gt(til_new_cap, til_Vec_MAX_CAP).data) {
            til_Array _tmp346;
            til_AllocError _err_alloc__tmp347;
            til_IndexOutOfBoundsError _err_idx__tmp347;
            til_Str _tmp348 = ((til_Str){(til_I64)"Vec.push: capacity exceeded Vec.MAX_CAP", 39});
            int _arr_status__tmp347 = til_Array_new(&_tmp346, &_err_alloc__tmp347, "Str", 1);
            if (_arr_status__tmp347 != 0) {
                *_err1 = _err_alloc__tmp347; return 1;
            }
            _arr_status__tmp347 = til_Array_set(&_err_idx__tmp347, &_tmp346, 0, &_tmp348);
            if (_arr_status__tmp347 != 0) {
            }
            til_panic(((til_Str){(til_I64)"src/test/constfold.til:63:23:", 29}), &_tmp346);
            til_Array_delete(&_tmp346);
        }
        til_I64 _ret__tmp349;
        til_I64 til_new_ptr;
        til_AllocError _err0__tmp349 = {};
        int _status__tmp349 = til_malloc(&_ret__tmp349, &_err0__tmp349, til_mul(til_new_cap, til_self->type_size));
        if (_status__tmp349 == 1) { *_err1 = _err0__tmp349; return 1; }
        til_new_ptr = _ret__tmp349;
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
        til_Str _tmp352;
        til_I64_OverflowError _err0__tmp353;
        til_IndexOutOfBoundsError _err1__tmp353;
        til_AllocError _err2__tmp353;
        til_Array _tmp354;
        til_AllocError _err_alloc__tmp355;
        til_IndexOutOfBoundsError _err_idx__tmp355;
        til_Str _tmp356 = ((til_Str){(til_I64)"Vec.get: index out of bounds", 28});
        int _arr_status__tmp355 = til_Array_new(&_tmp354, &_err_alloc__tmp355, "Str", 1);
        if (_arr_status__tmp355 != 0) {
        }
        _arr_status__tmp355 = til_Array_set(&_err_idx__tmp355, &_tmp354, 0, &_tmp356);
        if (_arr_status__tmp355 != 0) {
            *_err1 = _err_idx__tmp355; return 1;
        }
        int _status__tmp353 = til_format(&_tmp352, &_err0__tmp353, &_err1__tmp353, &_err2__tmp353, ((til_Str){(til_I64)"src/test/constfold.til:81:52:", 29}), &_tmp354);
        if (_status__tmp353 != 0) {
            if (_status__tmp353 == 2) { *_err1 = _err1__tmp353; return 1; }
        }
        til_Array_delete(&_tmp354);
        til_Str _tmp357;
        til_I64_OverflowError _err0__tmp358;
        til_IndexOutOfBoundsError _err1__tmp358;
        til_AllocError _err2__tmp358;
        til_Array _tmp359;
        til_AllocError _err_alloc__tmp360;
        til_IndexOutOfBoundsError _err_idx__tmp360;
        til_Str _tmp361 = ((til_Str){(til_I64)"Vec.get: index out of bounds", 28});
        int _arr_status__tmp360 = til_Array_new(&_tmp359, &_err_alloc__tmp360, "Str", 1);
        if (_arr_status__tmp360 != 0) {
        }
        _arr_status__tmp360 = til_Array_set(&_err_idx__tmp360, &_tmp359, 0, &_tmp361);
        if (_arr_status__tmp360 != 0) {
            *_err1 = _err_idx__tmp360; return 1;
        }
        int _status__tmp358 = til_format(&_tmp357, &_err0__tmp358, &_err1__tmp358, &_err2__tmp358, ((til_Str){(til_I64)"src/test/constfold.til:81:52:", 29}), &_tmp359);
        if (_status__tmp358 != 0) {
            if (_status__tmp358 == 2) { *_err1 = _err1__tmp358; return 1; }
        }
        til_Array_delete(&_tmp359);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp357);
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Vec_set(til_IndexOutOfBoundsError* _err1, til_Vec* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_gteq(til_index, til_self->_len).data) {
        til_Str _tmp364;
        til_I64_OverflowError _err0__tmp365;
        til_IndexOutOfBoundsError _err1__tmp365;
        til_AllocError _err2__tmp365;
        til_Array _tmp366;
        til_AllocError _err_alloc__tmp367;
        til_IndexOutOfBoundsError _err_idx__tmp367;
        til_Str _tmp368 = ((til_Str){(til_I64)"Vec.set: index out of bounds", 28});
        int _arr_status__tmp367 = til_Array_new(&_tmp366, &_err_alloc__tmp367, "Str", 1);
        if (_arr_status__tmp367 != 0) {
        }
        _arr_status__tmp367 = til_Array_set(&_err_idx__tmp367, &_tmp366, 0, &_tmp368);
        if (_arr_status__tmp367 != 0) {
            *_err1 = _err_idx__tmp367; return 1;
        }
        int _status__tmp365 = til_format(&_tmp364, &_err0__tmp365, &_err1__tmp365, &_err2__tmp365, ((til_Str){(til_I64)"src/test/constfold.til:96:52:", 29}), &_tmp366);
        if (_status__tmp365 != 0) {
            if (_status__tmp365 == 2) { *_err1 = _err1__tmp365; return 1; }
        }
        til_Array_delete(&_tmp366);
        til_Str _tmp369;
        til_I64_OverflowError _err0__tmp370;
        til_IndexOutOfBoundsError _err1__tmp370;
        til_AllocError _err2__tmp370;
        til_Array _tmp371;
        til_AllocError _err_alloc__tmp372;
        til_IndexOutOfBoundsError _err_idx__tmp372;
        til_Str _tmp373 = ((til_Str){(til_I64)"Vec.set: index out of bounds", 28});
        int _arr_status__tmp372 = til_Array_new(&_tmp371, &_err_alloc__tmp372, "Str", 1);
        if (_arr_status__tmp372 != 0) {
        }
        _arr_status__tmp372 = til_Array_set(&_err_idx__tmp372, &_tmp371, 0, &_tmp373);
        if (_arr_status__tmp372 != 0) {
            *_err1 = _err_idx__tmp372; return 1;
        }
        int _status__tmp370 = til_format(&_tmp369, &_err0__tmp370, &_err1__tmp370, &_err2__tmp370, ((til_Str){(til_I64)"src/test/constfold.til:96:52:", 29}), &_tmp371);
        if (_status__tmp370 != 0) {
            if (_status__tmp370 == 2) { *_err1 = _err1__tmp370; return 1; }
        }
        til_Array_delete(&_tmp371);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp369);
        return 1;
    }
    til_I64 til_dest = til_add(til_self->ptr, til_mul(til_index, til_self->type_size));
    til_memcpy(til_dest, (til_I64)til_value, til_self->type_size);
    return 0;
}

int til_Vec_pop(til_IndexOutOfBoundsError* _err1, til_Vec* til_self, til_Dynamic* til_dest) {
    if (til_I64_eq(til_self->_len, 0).data) {
        til_Str _tmp376;
        til_I64_OverflowError _err0__tmp377;
        til_IndexOutOfBoundsError _err1__tmp377;
        til_AllocError _err2__tmp377;
        til_Array _tmp378;
        til_AllocError _err_alloc__tmp379;
        til_IndexOutOfBoundsError _err_idx__tmp379;
        til_Str _tmp380 = ((til_Str){(til_I64)"Vec.pop: cannot pop from empty Vec", 34});
        int _arr_status__tmp379 = til_Array_new(&_tmp378, &_err_alloc__tmp379, "Str", 1);
        if (_arr_status__tmp379 != 0) {
        }
        _arr_status__tmp379 = til_Array_set(&_err_idx__tmp379, &_tmp378, 0, &_tmp380);
        if (_arr_status__tmp379 != 0) {
            *_err1 = _err_idx__tmp379; return 1;
        }
        int _status__tmp377 = til_format(&_tmp376, &_err0__tmp377, &_err1__tmp377, &_err2__tmp377, ((til_Str){(til_I64)"src/test/constfold.til:110:52:", 30}), &_tmp378);
        if (_status__tmp377 != 0) {
            if (_status__tmp377 == 2) { *_err1 = _err1__tmp377; return 1; }
        }
        til_Array_delete(&_tmp378);
        til_Str _tmp381;
        til_I64_OverflowError _err0__tmp382;
        til_IndexOutOfBoundsError _err1__tmp382;
        til_AllocError _err2__tmp382;
        til_Array _tmp383;
        til_AllocError _err_alloc__tmp384;
        til_IndexOutOfBoundsError _err_idx__tmp384;
        til_Str _tmp385 = ((til_Str){(til_I64)"Vec.pop: cannot pop from empty Vec", 34});
        int _arr_status__tmp384 = til_Array_new(&_tmp383, &_err_alloc__tmp384, "Str", 1);
        if (_arr_status__tmp384 != 0) {
        }
        _arr_status__tmp384 = til_Array_set(&_err_idx__tmp384, &_tmp383, 0, &_tmp385);
        if (_arr_status__tmp384 != 0) {
            *_err1 = _err_idx__tmp384; return 1;
        }
        int _status__tmp382 = til_format(&_tmp381, &_err0__tmp382, &_err1__tmp382, &_err2__tmp382, ((til_Str){(til_I64)"src/test/constfold.til:110:52:", 30}), &_tmp383);
        if (_status__tmp382 != 0) {
            if (_status__tmp382 == 2) { *_err1 = _err1__tmp382; return 1; }
        }
        til_Array_delete(&_tmp383);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp381);
        return 1;
    }
    til_I64 til_last_index = til_sub(til_self->_len, 1);
    til_IndexOutOfBoundsError _err0__tmp386 = {};
    int _status__tmp386 = til_Vec_get(&_err0__tmp386, (*til_self), til_last_index, (til_Dynamic*)&til_dest);
    if (_status__tmp386 == 1) { *_err1 = _err0__tmp386; return 1; }
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
    til_I64 _ret__tmp389;
    til_AllocError _err0__tmp389 = {};
    int _status__tmp389 = til_malloc(&_ret__tmp389, &_err0__tmp389, til_total_bytes);
    if (_status__tmp389 == 1) { *_err1 = _err0__tmp389; return 1; }
    til_cloned.ptr = _ret__tmp389;
    if (til_I64_eq(til_NULL, til_cloned.ptr).data) {
        til_Str _tmp391;
        til_I64_OverflowError _err0__tmp392;
        til_IndexOutOfBoundsError _err1__tmp392;
        til_AllocError _err2__tmp392;
        til_Array _tmp393;
        til_AllocError _err_alloc__tmp394;
        til_IndexOutOfBoundsError _err_idx__tmp394;
        til_Str _tmp395 = ((til_Str){(til_I64)"Vec.clone: malloc failed for ", 29});
        til_Str _tmp396 = til_I64_to_str(til_total_bytes);
        til_Str _tmp397 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp394 = til_Array_new(&_tmp393, &_err_alloc__tmp394, "Str", 3);
        if (_arr_status__tmp394 != 0) {
            *_err1 = _err_alloc__tmp394; return 1;
        }
        _arr_status__tmp394 = til_Array_set(&_err_idx__tmp394, &_tmp393, 0, &_tmp395);
        if (_arr_status__tmp394 != 0) {
        }
        _arr_status__tmp394 = til_Array_set(&_err_idx__tmp394, &_tmp393, 1, &_tmp396);
        if (_arr_status__tmp394 != 0) {
        }
        _arr_status__tmp394 = til_Array_set(&_err_idx__tmp394, &_tmp393, 2, &_tmp397);
        if (_arr_status__tmp394 != 0) {
        }
        int _status__tmp392 = til_format(&_tmp391, &_err0__tmp392, &_err1__tmp392, &_err2__tmp392, ((til_Str){(til_I64)"src/test/constfold.til:139:41:", 30}), &_tmp393);
        if (_status__tmp392 != 0) {
            if (_status__tmp392 == 3) { *_err1 = _err2__tmp392; return 1; }
        }
        til_Array_delete(&_tmp393);
        til_Str _tmp398;
        til_I64_OverflowError _err0__tmp399;
        til_IndexOutOfBoundsError _err1__tmp399;
        til_AllocError _err2__tmp399;
        til_Array _tmp400;
        til_AllocError _err_alloc__tmp401;
        til_IndexOutOfBoundsError _err_idx__tmp401;
        til_Str _tmp402 = ((til_Str){(til_I64)"Vec.clone: malloc failed for ", 29});
        til_Str _tmp403 = til_I64_to_str(til_total_bytes);
        til_Str _tmp404 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp401 = til_Array_new(&_tmp400, &_err_alloc__tmp401, "Str", 3);
        if (_arr_status__tmp401 != 0) {
            *_err1 = _err_alloc__tmp401; return 1;
        }
        _arr_status__tmp401 = til_Array_set(&_err_idx__tmp401, &_tmp400, 0, &_tmp402);
        if (_arr_status__tmp401 != 0) {
        }
        _arr_status__tmp401 = til_Array_set(&_err_idx__tmp401, &_tmp400, 1, &_tmp403);
        if (_arr_status__tmp401 != 0) {
        }
        _arr_status__tmp401 = til_Array_set(&_err_idx__tmp401, &_tmp400, 2, &_tmp404);
        if (_arr_status__tmp401 != 0) {
        }
        int _status__tmp399 = til_format(&_tmp398, &_err0__tmp399, &_err1__tmp399, &_err2__tmp399, ((til_Str){(til_I64)"src/test/constfold.til:139:41:", 30}), &_tmp400);
        if (_status__tmp399 != 0) {
            if (_status__tmp399 == 3) { *_err1 = _err2__tmp399; return 1; }
        }
        til_Array_delete(&_tmp400);
        *_err1 = til_AllocError_new(_tmp398);
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
                til_Array _tmp409;
                til_AllocError _err_alloc__tmp410;
                til_IndexOutOfBoundsError _err_idx__tmp410;
                til_Str _tmp411 = ((til_Str){(til_I64)"Vec.extend: capacity exceeded Vec.MAX_CAP", 41});
                int _arr_status__tmp410 = til_Array_new(&_tmp409, &_err_alloc__tmp410, "Str", 1);
                if (_arr_status__tmp410 != 0) {
                    *_err1 = _err_alloc__tmp410; return 1;
                }
                _arr_status__tmp410 = til_Array_set(&_err_idx__tmp410, &_tmp409, 0, &_tmp411);
                if (_arr_status__tmp410 != 0) {
                }
                til_panic(((til_Str){(til_I64)"src/test/constfold.til:158:27:", 30}), &_tmp409);
                til_Array_delete(&_tmp409);
            }
            til_I64 _ret__tmp412;
            til_I64 til_new_ptr;
            til_AllocError _err0__tmp412 = {};
            int _status__tmp412 = til_malloc(&_ret__tmp412, &_err0__tmp412, til_mul(til_new_cap, til_self->type_size));
            if (_status__tmp412 == 1) { *_err1 = _err0__tmp412; return 1; }
            til_new_ptr = _ret__tmp412;
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
        til_Str _tmp421;
        til_I64_OverflowError _err0__tmp422;
        til_IndexOutOfBoundsError _err1__tmp422;
        til_AllocError _err2__tmp422;
        til_Array _tmp423;
        til_AllocError _err_alloc__tmp424;
        til_IndexOutOfBoundsError _err_idx__tmp424;
        til_Str _tmp425 = ((til_Str){(til_I64)"Vec.remove: index out of bounds", 31});
        int _arr_status__tmp424 = til_Array_new(&_tmp423, &_err_alloc__tmp424, "Str", 1);
        if (_arr_status__tmp424 != 0) {
        }
        _arr_status__tmp424 = til_Array_set(&_err_idx__tmp424, &_tmp423, 0, &_tmp425);
        if (_arr_status__tmp424 != 0) {
            *_err1 = _err_idx__tmp424; return 1;
        }
        int _status__tmp422 = til_format(&_tmp421, &_err0__tmp422, &_err1__tmp422, &_err2__tmp422, ((til_Str){(til_I64)"src/test/constfold.til:202:52:", 30}), &_tmp423);
        if (_status__tmp422 != 0) {
            if (_status__tmp422 == 2) { *_err1 = _err1__tmp422; return 1; }
        }
        til_Array_delete(&_tmp423);
        til_Str _tmp426;
        til_I64_OverflowError _err0__tmp427;
        til_IndexOutOfBoundsError _err1__tmp427;
        til_AllocError _err2__tmp427;
        til_Array _tmp428;
        til_AllocError _err_alloc__tmp429;
        til_IndexOutOfBoundsError _err_idx__tmp429;
        til_Str _tmp430 = ((til_Str){(til_I64)"Vec.remove: index out of bounds", 31});
        int _arr_status__tmp429 = til_Array_new(&_tmp428, &_err_alloc__tmp429, "Str", 1);
        if (_arr_status__tmp429 != 0) {
        }
        _arr_status__tmp429 = til_Array_set(&_err_idx__tmp429, &_tmp428, 0, &_tmp430);
        if (_arr_status__tmp429 != 0) {
            *_err1 = _err_idx__tmp429; return 1;
        }
        int _status__tmp427 = til_format(&_tmp426, &_err0__tmp427, &_err1__tmp427, &_err2__tmp427, ((til_Str){(til_I64)"src/test/constfold.til:202:52:", 30}), &_tmp428);
        if (_status__tmp427 != 0) {
            if (_status__tmp427 == 2) { *_err1 = _err1__tmp427; return 1; }
        }
        til_Array_delete(&_tmp428);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp426);
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
    til_I64 _ret__tmp440;
    til_AllocError _err0__tmp440 = {};
    int _status__tmp440 = til_malloc(&_ret__tmp440, &_err0__tmp440, til_cloned.cap);
    if (_status__tmp440 == 1) { *_err1 = _err0__tmp440; return 1; }
    til_cloned.c_string = _ret__tmp440;
    if (til_I64_eq(til_NULL, til_cloned.c_string).data) {
        til_Str _tmp442;
        til_I64_OverflowError _err0__tmp443;
        til_IndexOutOfBoundsError _err1__tmp443;
        til_AllocError _err2__tmp443;
        til_Array _tmp444;
        til_AllocError _err_alloc__tmp445;
        til_IndexOutOfBoundsError _err_idx__tmp445;
        til_Str _tmp446 = ((til_Str){(til_I64)"Str.clone: malloc failed for ", 29});
        til_Str _tmp447 = til_I64_to_str(til_cloned.cap);
        til_Str _tmp448 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp445 = til_Array_new(&_tmp444, &_err_alloc__tmp445, "Str", 3);
        if (_arr_status__tmp445 != 0) {
            *_err1 = _err_alloc__tmp445; return 1;
        }
        _arr_status__tmp445 = til_Array_set(&_err_idx__tmp445, &_tmp444, 0, &_tmp446);
        if (_arr_status__tmp445 != 0) {
        }
        _arr_status__tmp445 = til_Array_set(&_err_idx__tmp445, &_tmp444, 1, &_tmp447);
        if (_arr_status__tmp445 != 0) {
        }
        _arr_status__tmp445 = til_Array_set(&_err_idx__tmp445, &_tmp444, 2, &_tmp448);
        if (_arr_status__tmp445 != 0) {
        }
        int _status__tmp443 = til_format(&_tmp442, &_err0__tmp443, &_err1__tmp443, &_err2__tmp443, ((til_Str){(til_I64)"src/test/constfold.til:46:41:", 29}), &_tmp444);
        if (_status__tmp443 != 0) {
            if (_status__tmp443 == 3) { *_err1 = _err2__tmp443; return 1; }
        }
        til_Array_delete(&_tmp444);
        til_Str _tmp449;
        til_I64_OverflowError _err0__tmp450;
        til_IndexOutOfBoundsError _err1__tmp450;
        til_AllocError _err2__tmp450;
        til_Array _tmp451;
        til_AllocError _err_alloc__tmp452;
        til_IndexOutOfBoundsError _err_idx__tmp452;
        til_Str _tmp453 = ((til_Str){(til_I64)"Str.clone: malloc failed for ", 29});
        til_Str _tmp454 = til_I64_to_str(til_cloned.cap);
        til_Str _tmp455 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp452 = til_Array_new(&_tmp451, &_err_alloc__tmp452, "Str", 3);
        if (_arr_status__tmp452 != 0) {
            *_err1 = _err_alloc__tmp452; return 1;
        }
        _arr_status__tmp452 = til_Array_set(&_err_idx__tmp452, &_tmp451, 0, &_tmp453);
        if (_arr_status__tmp452 != 0) {
        }
        _arr_status__tmp452 = til_Array_set(&_err_idx__tmp452, &_tmp451, 1, &_tmp454);
        if (_arr_status__tmp452 != 0) {
        }
        _arr_status__tmp452 = til_Array_set(&_err_idx__tmp452, &_tmp451, 2, &_tmp455);
        if (_arr_status__tmp452 != 0) {
        }
        int _status__tmp450 = til_format(&_tmp449, &_err0__tmp450, &_err1__tmp450, &_err2__tmp450, ((til_Str){(til_I64)"src/test/constfold.til:46:41:", 29}), &_tmp451);
        if (_status__tmp450 != 0) {
            if (_status__tmp450 == 3) { *_err1 = _err2__tmp450; return 1; }
        }
        til_Array_delete(&_tmp451);
        *_err1 = til_AllocError_new(_tmp449);
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
        til_Str _ret__tmp492;
        til_AllocError _err0__tmp492 = {};
        int _status__tmp492 = til_Str_clone(&_ret__tmp492, &_err0__tmp492, til_self);
        if (_status__tmp492 == 1) { *_err1 = _err0__tmp492; return 1; }
        *_ret = _ret__tmp492;
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
        til_Str _ret__tmp500;
        til_AllocError _err0__tmp500 = {};
        int _status__tmp500 = til_Str_clone(&_ret__tmp500, &_err0__tmp500, til_self);
        if (_status__tmp500 == 1) { *_err1 = _err0__tmp500; return 1; }
        *_ret = _ret__tmp500;
        return 0;
    }
    til_I64 til_new_len = til_add(til_sub(til_Str_len(til_self), til_mul(til_count, til_Str_len(til_from))), til_mul(til_count, til_Str_len(til_to)));
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_new_len;
    til_I64 _ret__tmp501;
    til_AllocError _err0__tmp501 = {};
    int _status__tmp501 = til_malloc(&_ret__tmp501, &_err0__tmp501, til_new_len);
    if (_status__tmp501 == 1) { *_err1 = _err0__tmp501; return 1; }
    til_result.c_string = _ret__tmp501;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Str _tmp503;
        til_I64_OverflowError _err0__tmp504;
        til_IndexOutOfBoundsError _err1__tmp504;
        til_AllocError _err2__tmp504;
        til_Array _tmp505;
        til_AllocError _err_alloc__tmp506;
        til_IndexOutOfBoundsError _err_idx__tmp506;
        til_Str _tmp507 = ((til_Str){(til_I64)"Str.replace: malloc failed for ", 31});
        til_Str _tmp508 = til_I64_to_str(til_new_len);
        til_Str _tmp509 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp506 = til_Array_new(&_tmp505, &_err_alloc__tmp506, "Str", 3);
        if (_arr_status__tmp506 != 0) {
            *_err1 = _err_alloc__tmp506; return 1;
        }
        _arr_status__tmp506 = til_Array_set(&_err_idx__tmp506, &_tmp505, 0, &_tmp507);
        if (_arr_status__tmp506 != 0) {
        }
        _arr_status__tmp506 = til_Array_set(&_err_idx__tmp506, &_tmp505, 1, &_tmp508);
        if (_arr_status__tmp506 != 0) {
        }
        _arr_status__tmp506 = til_Array_set(&_err_idx__tmp506, &_tmp505, 2, &_tmp509);
        if (_arr_status__tmp506 != 0) {
        }
        int _status__tmp504 = til_format(&_tmp503, &_err0__tmp504, &_err1__tmp504, &_err2__tmp504, ((til_Str){(til_I64)"src/test/constfold.til:213:41:", 30}), &_tmp505);
        if (_status__tmp504 != 0) {
            if (_status__tmp504 == 3) { *_err1 = _err2__tmp504; return 1; }
        }
        til_Array_delete(&_tmp505);
        til_Str _tmp510;
        til_I64_OverflowError _err0__tmp511;
        til_IndexOutOfBoundsError _err1__tmp511;
        til_AllocError _err2__tmp511;
        til_Array _tmp512;
        til_AllocError _err_alloc__tmp513;
        til_IndexOutOfBoundsError _err_idx__tmp513;
        til_Str _tmp514 = ((til_Str){(til_I64)"Str.replace: malloc failed for ", 31});
        til_Str _tmp515 = til_I64_to_str(til_new_len);
        til_Str _tmp516 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp513 = til_Array_new(&_tmp512, &_err_alloc__tmp513, "Str", 3);
        if (_arr_status__tmp513 != 0) {
            *_err1 = _err_alloc__tmp513; return 1;
        }
        _arr_status__tmp513 = til_Array_set(&_err_idx__tmp513, &_tmp512, 0, &_tmp514);
        if (_arr_status__tmp513 != 0) {
        }
        _arr_status__tmp513 = til_Array_set(&_err_idx__tmp513, &_tmp512, 1, &_tmp515);
        if (_arr_status__tmp513 != 0) {
        }
        _arr_status__tmp513 = til_Array_set(&_err_idx__tmp513, &_tmp512, 2, &_tmp516);
        if (_arr_status__tmp513 != 0) {
        }
        int _status__tmp511 = til_format(&_tmp510, &_err0__tmp511, &_err1__tmp511, &_err2__tmp511, ((til_Str){(til_I64)"src/test/constfold.til:213:41:", 30}), &_tmp512);
        if (_status__tmp511 != 0) {
            if (_status__tmp511 == 3) { *_err1 = _err2__tmp511; return 1; }
        }
        til_Array_delete(&_tmp512);
        *_err1 = til_AllocError_new(_tmp510);
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
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp528;
    if (til_I64_eq(til_Str_len(til_from), 0).data) {
        til_Str _ret__tmp530;
        til_AllocError _err0__tmp530 = {};
        int _status__tmp530 = til_Str_clone(&_ret__tmp530, &_err0__tmp530, til_self);
        if (_status__tmp530 == 1) { *_err1 = _err0__tmp530; return 1; }
        *_ret = _ret__tmp530;
        return 0;
    }
    if (til_I64_eq(til_n, 0).data) {
        til_Str _ret__tmp532;
        til_AllocError _err0__tmp532 = {};
        int _status__tmp532 = til_Str_clone(&_ret__tmp532, &_err0__tmp532, til_self);
        if (_status__tmp532 == 1) { *_err1 = _err0__tmp532; return 1; }
        *_ret = _ret__tmp532;
        return 0;
    }
    til_I64 til_idx = til_Str_find(til_self, til_from);
    if (til_lt(til_idx, 0).data) {
        til_Str _ret__tmp534;
        til_AllocError _err0__tmp534 = {};
        int _status__tmp534 = til_Str_clone(&_ret__tmp534, &_err0__tmp534, til_self);
        if (_status__tmp534 == 1) { *_err1 = _err0__tmp534; return 1; }
        *_ret = _ret__tmp534;
        return 0;
    }
    til_Str _ret__tmp535;
    til_Str til_prefix;
    til_IndexOutOfBoundsError _err0__tmp535 = {};
    til_AllocError _err1__tmp535 = {};
    int _status__tmp535 = til_get_substr(&_ret__tmp535, &_err0__tmp535, &_err1__tmp535, til_self, 0, til_idx);
    if (_status__tmp535 == 2) { *_err1 = _err1__tmp535; return 1; }
    til_prefix = _ret__tmp535;
    til_Str _ret__tmp536;
    til_Str til_suffix;
    til_IndexOutOfBoundsError _err0__tmp536 = {};
    til_AllocError _err1__tmp536 = {};
    int _status__tmp536 = til_get_substr(&_ret__tmp536, &_err0__tmp536, &_err1__tmp536, til_self, til_add(til_idx, til_Str_len(til_from)), til_Str_len(til_self));
    if (_status__tmp536 == 2) { *_err1 = _err1__tmp536; return 1; }
    til_suffix = _ret__tmp536;
    til_Str til_result = til_concat(til_concat(til_prefix, til_to), til_suffix);
    if (til_gt(til_n, 1).data) {
        til_Str _ret__tmp538;
        til_Str til_rest;
        til_AllocError _err0__tmp538 = {};
        int _status__tmp538 = til_Str_replacen(&_ret__tmp538, &_err0__tmp538, til_suffix, til_from, til_to, til_sub(til_n, 1));
        if (_status__tmp538 == 1) { *_err1 = _err0__tmp538; return 1; }
        til_rest = _ret__tmp538;
        til_result = til_concat(til_concat(til_prefix, til_to), til_rest);
    }
    *_ret = til_result;
    return 0;
    goto _end_catches__tmp528;
_catch_IndexOutOfBoundsError__tmp528: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp528;
    til_Str _ret__tmp540;
    til_AllocError _err0__tmp540 = {};
    int _status__tmp540 = til_Str_clone(&_ret__tmp540, &_err0__tmp540, til_self);
    if (_status__tmp540 == 1) { *_err1 = _err0__tmp540; return 1; }
    til_result = _ret__tmp540;
    }
_end_catches__tmp528:;
}

int til_Str_split(til_Vec* _ret, til_AllocError* _err1, til_IndexOutOfBoundsError* _err2, const til_Str til_self, const til_Str til_delimiter) {
    til_Vec _ret__tmp542;
    til_Vec til_parts;
    til_AllocError _err0__tmp542 = {};
    int _status__tmp542 = til_Vec_new(&_ret__tmp542, &_err0__tmp542, "Str");
    if (_status__tmp542 == 1) { *_err1 = _err0__tmp542; return 1; }
    til_parts = _ret__tmp542;
    if (til_I64_eq(til_Str_len(til_delimiter), 0).data) {
        til_Str _tmp545;
        til_AllocError _err0__tmp546;
        int _status__tmp546 = til_Str_clone(&_tmp545, &_err0__tmp546, til_self);
        if (_status__tmp546 != 0) {
            if (_status__tmp546 == 1) { *_err1 = _err0__tmp546; return 1; }
        }
        til_AllocError _err0__tmp544 = {};
        int _status__tmp544 = til_Vec_push(&_err0__tmp544, &til_parts, &_tmp545);
        if (_status__tmp544 == 1) { *_err1 = _err0__tmp544; return 1; }
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
                til_Str _ret__tmp553;
                til_Str til_part;
                til_IndexOutOfBoundsError _err0__tmp553 = {};
                til_AllocError _err1__tmp553 = {};
                int _status__tmp553 = til_get_substr(&_ret__tmp553, &_err0__tmp553, &_err1__tmp553, til_self, til_start, til_pos);
                if (_status__tmp553 == 1) { *_err2 = _err0__tmp553; return 2; }
                if (_status__tmp553 == 2) { *_err1 = _err1__tmp553; return 1; }
                til_part = _ret__tmp553;
                til_AllocError _err0__tmp554 = {};
                int _status__tmp554 = til_Vec_push(&_err0__tmp554, &til_parts, (til_Dynamic*)&til_part);
                if (_status__tmp554 == 1) { *_err1 = _err0__tmp554; return 1; }
            } else {
                til_Str _tmp557 = ((til_Str){(til_I64)"", 0});
                til_AllocError _err0__tmp556 = {};
                int _status__tmp556 = til_Vec_push(&_err0__tmp556, &til_parts, &_tmp557);
                if (_status__tmp556 == 1) { *_err1 = _err0__tmp556; return 1; }
            }
            til_start = til_add(til_pos, til_Str_len(til_delimiter));
            til_pos = til_start;
        } else {
            til_pos = til_add(til_pos, 1);
        }
    }
    if (til_lt(til_start, til_Str_len(til_self)).data) {
        til_Str _ret__tmp560;
        til_Str til_part;
        til_IndexOutOfBoundsError _err0__tmp560 = {};
        til_AllocError _err1__tmp560 = {};
        int _status__tmp560 = til_get_substr(&_ret__tmp560, &_err0__tmp560, &_err1__tmp560, til_self, til_start, til_Str_len(til_self));
        if (_status__tmp560 == 1) { *_err2 = _err0__tmp560; return 2; }
        if (_status__tmp560 == 2) { *_err1 = _err1__tmp560; return 1; }
        til_part = _ret__tmp560;
        til_AllocError _err0__tmp561 = {};
        int _status__tmp561 = til_Vec_push(&_err0__tmp561, &til_parts, (til_Dynamic*)&til_part);
        if (_status__tmp561 == 1) { *_err1 = _err0__tmp561; return 1; }
    } else {
        if (til_I64_eq(til_start, til_Str_len(til_self)).data) {
            til_Str _tmp565 = ((til_Str){(til_I64)"", 0});
            til_AllocError _err0__tmp564 = {};
            int _status__tmp564 = til_Vec_push(&_err0__tmp564, &til_parts, &_tmp565);
            if (_status__tmp564 == 1) { *_err1 = _err0__tmp564; return 1; }
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
    til_U8 _ret__tmp573;
    til_U8_OverflowError _err0__tmp573 = {};
    int _status__tmp573 = til_U8_from_i64(&_ret__tmp573, &_err0__tmp573, til_add(til_U8_to_i64(til_a), til_U8_to_i64(til_b)));
    if (_status__tmp573 == 1) { *_err1 = _err0__tmp573; return 1; }
    *_ret = _ret__tmp573;
    return 0;
}

int til_U8_from_i64(til_U8* _ret, til_U8_OverflowError* _err1, const til_I64 til_self) {
    if (til_lt(til_self, 0).data) {
        til_Str _tmp576;
        til_I64_OverflowError _err0__tmp577;
        til_IndexOutOfBoundsError _err1__tmp577;
        til_AllocError _err2__tmp577;
        til_Array _tmp578;
        til_AllocError _err_alloc__tmp579;
        til_IndexOutOfBoundsError _err_idx__tmp579;
        til_Str _tmp580 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        int _arr_status__tmp579 = til_Array_new(&_tmp578, &_err_alloc__tmp579, "Str", 1);
        if (_arr_status__tmp579 != 0) {
        }
        _arr_status__tmp579 = til_Array_set(&_err_idx__tmp579, &_tmp578, 0, &_tmp580);
        if (_arr_status__tmp579 != 0) {
        }
        int _status__tmp577 = til_format(&_tmp576, &_err0__tmp577, &_err1__tmp577, &_err2__tmp577, ((til_Str){(til_I64)"src/test/constfold.til:56:47:", 29}), &_tmp578);
        if (_status__tmp577 != 0) {
        }
        til_Array_delete(&_tmp578);
        til_Str _tmp581;
        til_I64_OverflowError _err0__tmp582;
        til_IndexOutOfBoundsError _err1__tmp582;
        til_AllocError _err2__tmp582;
        til_Array _tmp583;
        til_AllocError _err_alloc__tmp584;
        til_IndexOutOfBoundsError _err_idx__tmp584;
        til_Str _tmp585 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        int _arr_status__tmp584 = til_Array_new(&_tmp583, &_err_alloc__tmp584, "Str", 1);
        if (_arr_status__tmp584 != 0) {
        }
        _arr_status__tmp584 = til_Array_set(&_err_idx__tmp584, &_tmp583, 0, &_tmp585);
        if (_arr_status__tmp584 != 0) {
        }
        int _status__tmp582 = til_format(&_tmp581, &_err0__tmp582, &_err1__tmp582, &_err2__tmp582, ((til_Str){(til_I64)"src/test/constfold.til:56:47:", 29}), &_tmp583);
        if (_status__tmp582 != 0) {
        }
        til_Array_delete(&_tmp583);
        *_err1 = til_U8_OverflowError_new(_tmp581);
        return 1;
    }
    if (til_gt(til_self, til_MAX_U8).data) {
        til_Str _tmp587;
        til_I64_OverflowError _err0__tmp588;
        til_IndexOutOfBoundsError _err1__tmp588;
        til_AllocError _err2__tmp588;
        til_Array _tmp589;
        til_AllocError _err_alloc__tmp590;
        til_IndexOutOfBoundsError _err_idx__tmp590;
        til_Str _tmp591 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp592 = til_I64_to_str(til_MAX_U8);
        int _arr_status__tmp590 = til_Array_new(&_tmp589, &_err_alloc__tmp590, "Str", 2);
        if (_arr_status__tmp590 != 0) {
        }
        _arr_status__tmp590 = til_Array_set(&_err_idx__tmp590, &_tmp589, 0, &_tmp591);
        if (_arr_status__tmp590 != 0) {
        }
        _arr_status__tmp590 = til_Array_set(&_err_idx__tmp590, &_tmp589, 1, &_tmp592);
        if (_arr_status__tmp590 != 0) {
        }
        int _status__tmp588 = til_format(&_tmp587, &_err0__tmp588, &_err1__tmp588, &_err2__tmp588, ((til_Str){(til_I64)"src/test/constfold.til:59:47:", 29}), &_tmp589);
        if (_status__tmp588 != 0) {
        }
        til_Array_delete(&_tmp589);
        til_Str _tmp593;
        til_I64_OverflowError _err0__tmp594;
        til_IndexOutOfBoundsError _err1__tmp594;
        til_AllocError _err2__tmp594;
        til_Array _tmp595;
        til_AllocError _err_alloc__tmp596;
        til_IndexOutOfBoundsError _err_idx__tmp596;
        til_Str _tmp597 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp598 = til_I64_to_str(til_MAX_U8);
        int _arr_status__tmp596 = til_Array_new(&_tmp595, &_err_alloc__tmp596, "Str", 2);
        if (_arr_status__tmp596 != 0) {
        }
        _arr_status__tmp596 = til_Array_set(&_err_idx__tmp596, &_tmp595, 0, &_tmp597);
        if (_arr_status__tmp596 != 0) {
        }
        _arr_status__tmp596 = til_Array_set(&_err_idx__tmp596, &_tmp595, 1, &_tmp598);
        if (_arr_status__tmp596 != 0) {
        }
        int _status__tmp594 = til_format(&_tmp593, &_err0__tmp594, &_err1__tmp594, &_err2__tmp594, ((til_Str){(til_I64)"src/test/constfold.til:59:47:", 29}), &_tmp595);
        if (_status__tmp594 != 0) {
        }
        til_Array_delete(&_tmp595);
        *_err1 = til_U8_OverflowError_new(_tmp593);
        return 1;
    }
    *_ret = til_i64_to_u8(til_self);
    return 0;
}

til_Str til_U8_to_str(const til_U8 til_self) {
    return til_I64_to_str(til_U8_to_i64(til_self));
}

int til_U8_from_str(til_U8* _ret, til_U8_OverflowError* _err1, const til_Str til_s) {
    til_U8 _ret__tmp601;
    til_U8_OverflowError _err0__tmp601 = {};
    int _status__tmp601 = til_U8_from_i64(&_ret__tmp601, &_err0__tmp601, til_I64_from_str(til_s));
    if (_status__tmp601 == 1) { *_err1 = _err0__tmp601; return 1; }
    *_ret = _ret__tmp601;
    return 0;
}

til_I64 til_U8_size(void) {
    return 1;
}

int main() {
    til_test_simple_add();
    til_test_nested_arithmetic();
    til_test_deeply_nested();
    til_test_string_concat();
    til_test_no_fold_variable();
    til_test_loc_folded_correctly();
    return 0;
}
