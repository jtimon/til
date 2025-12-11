#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char til_U8;
typedef long long til_I64;
typedef struct til_Bool { til_U8 data; } til_Bool;
#define true ((til_Bool){1})
#define false ((til_Bool){0})
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
    til_Str _tmp10 = til_Str_from_literal("or: IndexOutOfBoundsError should never happen");
    int _arr_status__tmp9 = til_Array_new(&_tmp8, &_err_alloc__tmp9, "Str", 1);
    if (_arr_status__tmp9 != 0) {
    }
    _arr_status__tmp9 = til_Array_set(&_err_idx__tmp9, &_tmp8, 0, &_tmp10);
    if (_arr_status__tmp9 != 0) {
    }
    til_panic(til_Str_from_literal("src/test/constfold.til:69:15:"), &_tmp8);
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
    til_Str _tmp19 = til_Str_from_literal("and: IndexOutOfBoundsError should never happen");
    int _arr_status__tmp18 = til_Array_new(&_tmp17, &_err_alloc__tmp18, "Str", 1);
    if (_arr_status__tmp18 != 0) {
    }
    _arr_status__tmp18 = til_Array_set(&_err_idx__tmp18, &_tmp17, 0, &_tmp19);
    if (_arr_status__tmp18 != 0) {
    }
    til_panic(til_Str_from_literal("src/test/constfold.til:85:15:"), &_tmp17);
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
        til_Str til_val = til_Str_from_literal("");
        til_IndexOutOfBoundsError _err0__tmp26 = {};
        int _status__tmp26 = til_Array_get(&_err0__tmp26, (*til_msgs), til_i, (til_Dynamic*)&til_val);
        if (_status__tmp26 == 1) { _thrown_IndexOutOfBoundsError__tmp23 = _err0__tmp26; goto _catch_IndexOutOfBoundsError__tmp23; }
        til_single_print(til_val);
        til_I64_inc(&til_i);
    }
    til_single_print(til_Str_from_literal("\n"));
    til_print_flush();
    til_exit(1);
    goto _end_catches__tmp23;
_catch_IndexOutOfBoundsError__tmp23: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp23;
    til_single_print(til_Str_from_literal("panic: IndexOutOfBoundsError should never happen\n"));
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
        int _status__tmp31 = til_format(&_tmp30, &_err0__tmp31, &_err1__tmp31, &_err2__tmp31, til_Str_from_literal("assert failed: "), &_tmp32);
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
    til_assertm(til_loc_str, til_cond, til_Str_from_literal(""));
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
    int _status__tmp40 = til_format(&_tmp39, &_err0__tmp40, &_err1__tmp40, &_err2__tmp40, til_Str_from_literal("TODO: "), &_tmp41);
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
        til_Str til_val = til_Str_from_literal("");
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
    til_Str _tmp57 = til_Str_from_literal("print: IndexOutOfBoundsError should never happen");
    int _arr_status__tmp56 = til_Array_new(&_tmp55, &_err_alloc__tmp56, "Str", 1);
    if (_arr_status__tmp56 != 0) {
    }
    _arr_status__tmp56 = til_Array_set(&_err_idx__tmp56, &_tmp55, 0, &_tmp57);
    if (_arr_status__tmp56 != 0) {
    }
    til_panic(til_Str_from_literal("src/test/constfold.til:17:15:"), &_tmp55);
    til_Array_delete(&_tmp55);
    }
_end_catches__tmp50:;
}

void til_println(til_Array* til_args) {
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp58;
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Str til_val = til_Str_from_literal("");
        til_IndexOutOfBoundsError _err0__tmp61 = {};
        int _status__tmp61 = til_Array_get(&_err0__tmp61, (*til_args), til_i, (til_Dynamic*)&til_val);
        if (_status__tmp61 == 1) { _thrown_IndexOutOfBoundsError__tmp58 = _err0__tmp61; goto _catch_IndexOutOfBoundsError__tmp58; }
        til_single_print(til_val);
        til_I64_inc(&til_i);
    }
    til_single_print(til_Str_from_literal("\n"));
    til_print_flush();
    goto _end_catches__tmp58;
_catch_IndexOutOfBoundsError__tmp58: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp58;
    til_Array _tmp63;
    til_AllocError _err_alloc__tmp64;
    til_IndexOutOfBoundsError _err_idx__tmp64;
    til_Str _tmp65 = til_Str_from_literal("println: IndexOutOfBoundsError should never happen");
    int _arr_status__tmp64 = til_Array_new(&_tmp63, &_err_alloc__tmp64, "Str", 1);
    if (_arr_status__tmp64 != 0) {
    }
    _arr_status__tmp64 = til_Array_set(&_err_idx__tmp64, &_tmp63, 0, &_tmp65);
    if (_arr_status__tmp64 != 0) {
    }
    til_panic(til_Str_from_literal("src/test/constfold.til:31:15:"), &_tmp63);
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
        til_Str _tmp72 = til_Str_from_literal("get_substr: start index ");
        til_Str _tmp73 = til_I64_to_str(til_start);
        til_Str _tmp74 = til_Str_from_literal(" cannot be negative");
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
        int _status__tmp69 = til_format(&_tmp68, &_err0__tmp69, &_err1__tmp69, &_err2__tmp69, til_Str_from_literal("src/test/constfold.til:357:48:"), &_tmp70);
        if (_status__tmp69 != 0) {
            if (_status__tmp69 == 2) { *_err1 = _err1__tmp69; return 1; }
            if (_status__tmp69 == 3) { *_err2 = _err2__tmp69; return 2; }
        }
        til_Array_delete(&_tmp70);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp68);
        return 1;
    }
    if (til_lt(til_end, 0).data) {
        til_Str _tmp76;
        til_I64_OverflowError _err0__tmp77;
        til_IndexOutOfBoundsError _err1__tmp77;
        til_AllocError _err2__tmp77;
        til_Array _tmp78;
        til_AllocError _err_alloc__tmp79;
        til_IndexOutOfBoundsError _err_idx__tmp79;
        til_Str _tmp80 = til_Str_from_literal("get_substr: end index ");
        til_Str _tmp81 = til_I64_to_str(til_end);
        til_Str _tmp82 = til_Str_from_literal(" cannot be negative");
        int _arr_status__tmp79 = til_Array_new(&_tmp78, &_err_alloc__tmp79, "Str", 3);
        if (_arr_status__tmp79 != 0) {
            *_err2 = _err_alloc__tmp79; return 2;
        }
        _arr_status__tmp79 = til_Array_set(&_err_idx__tmp79, &_tmp78, 0, &_tmp80);
        if (_arr_status__tmp79 != 0) {
            *_err1 = _err_idx__tmp79; return 1;
        }
        _arr_status__tmp79 = til_Array_set(&_err_idx__tmp79, &_tmp78, 1, &_tmp81);
        if (_arr_status__tmp79 != 0) {
            *_err1 = _err_idx__tmp79; return 1;
        }
        _arr_status__tmp79 = til_Array_set(&_err_idx__tmp79, &_tmp78, 2, &_tmp82);
        if (_arr_status__tmp79 != 0) {
            *_err1 = _err_idx__tmp79; return 1;
        }
        int _status__tmp77 = til_format(&_tmp76, &_err0__tmp77, &_err1__tmp77, &_err2__tmp77, til_Str_from_literal("src/test/constfold.til:360:48:"), &_tmp78);
        if (_status__tmp77 != 0) {
            if (_status__tmp77 == 2) { *_err1 = _err1__tmp77; return 1; }
            if (_status__tmp77 == 3) { *_err2 = _err2__tmp77; return 2; }
        }
        til_Array_delete(&_tmp78);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp76);
        return 1;
    }
    if (til_gt(til_start, til_end).data) {
        til_Str _tmp84;
        til_I64_OverflowError _err0__tmp85;
        til_IndexOutOfBoundsError _err1__tmp85;
        til_AllocError _err2__tmp85;
        til_Array _tmp86;
        til_AllocError _err_alloc__tmp87;
        til_IndexOutOfBoundsError _err_idx__tmp87;
        til_Str _tmp88 = til_Str_from_literal("get_substr: start index ");
        til_Str _tmp89 = til_I64_to_str(til_start);
        til_Str _tmp90 = til_Str_from_literal(" is greater than end index ");
        til_Str _tmp91 = til_I64_to_str(til_end);
        int _arr_status__tmp87 = til_Array_new(&_tmp86, &_err_alloc__tmp87, "Str", 4);
        if (_arr_status__tmp87 != 0) {
            *_err2 = _err_alloc__tmp87; return 2;
        }
        _arr_status__tmp87 = til_Array_set(&_err_idx__tmp87, &_tmp86, 0, &_tmp88);
        if (_arr_status__tmp87 != 0) {
            *_err1 = _err_idx__tmp87; return 1;
        }
        _arr_status__tmp87 = til_Array_set(&_err_idx__tmp87, &_tmp86, 1, &_tmp89);
        if (_arr_status__tmp87 != 0) {
            *_err1 = _err_idx__tmp87; return 1;
        }
        _arr_status__tmp87 = til_Array_set(&_err_idx__tmp87, &_tmp86, 2, &_tmp90);
        if (_arr_status__tmp87 != 0) {
            *_err1 = _err_idx__tmp87; return 1;
        }
        _arr_status__tmp87 = til_Array_set(&_err_idx__tmp87, &_tmp86, 3, &_tmp91);
        if (_arr_status__tmp87 != 0) {
            *_err1 = _err_idx__tmp87; return 1;
        }
        int _status__tmp85 = til_format(&_tmp84, &_err0__tmp85, &_err1__tmp85, &_err2__tmp85, til_Str_from_literal("src/test/constfold.til:363:48:"), &_tmp86);
        if (_status__tmp85 != 0) {
            if (_status__tmp85 == 2) { *_err1 = _err1__tmp85; return 1; }
            if (_status__tmp85 == 3) { *_err2 = _err2__tmp85; return 2; }
        }
        til_Array_delete(&_tmp86);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp84);
        return 1;
    }
    if (til_gt(til_end, til_Str_len(til_s)).data) {
        til_Str _tmp93;
        til_I64_OverflowError _err0__tmp94;
        til_IndexOutOfBoundsError _err1__tmp94;
        til_AllocError _err2__tmp94;
        til_Array _tmp95;
        til_AllocError _err_alloc__tmp96;
        til_IndexOutOfBoundsError _err_idx__tmp96;
        til_Str _tmp97 = til_Str_from_literal("get_substr: end index ");
        til_Str _tmp98 = til_I64_to_str(til_end);
        til_Str _tmp99 = til_Str_from_literal(" is greater than string length ");
        til_Str _tmp100 = til_I64_to_str(til_Str_len(til_s));
        int _arr_status__tmp96 = til_Array_new(&_tmp95, &_err_alloc__tmp96, "Str", 4);
        if (_arr_status__tmp96 != 0) {
            *_err2 = _err_alloc__tmp96; return 2;
        }
        _arr_status__tmp96 = til_Array_set(&_err_idx__tmp96, &_tmp95, 0, &_tmp97);
        if (_arr_status__tmp96 != 0) {
            *_err1 = _err_idx__tmp96; return 1;
        }
        _arr_status__tmp96 = til_Array_set(&_err_idx__tmp96, &_tmp95, 1, &_tmp98);
        if (_arr_status__tmp96 != 0) {
            *_err1 = _err_idx__tmp96; return 1;
        }
        _arr_status__tmp96 = til_Array_set(&_err_idx__tmp96, &_tmp95, 2, &_tmp99);
        if (_arr_status__tmp96 != 0) {
            *_err1 = _err_idx__tmp96; return 1;
        }
        _arr_status__tmp96 = til_Array_set(&_err_idx__tmp96, &_tmp95, 3, &_tmp100);
        if (_arr_status__tmp96 != 0) {
            *_err1 = _err_idx__tmp96; return 1;
        }
        int _status__tmp94 = til_format(&_tmp93, &_err0__tmp94, &_err1__tmp94, &_err2__tmp94, til_Str_from_literal("src/test/constfold.til:366:48:"), &_tmp95);
        if (_status__tmp94 != 0) {
            if (_status__tmp94 == 2) { *_err1 = _err1__tmp94; return 1; }
            if (_status__tmp94 == 3) { *_err2 = _err2__tmp94; return 2; }
        }
        til_Array_delete(&_tmp95);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp93);
        return 1;
    }
    if (til_I64_eq(til_start, til_end).data) {
        til_Str _tmp102;
        til_I64_OverflowError _err0__tmp103;
        til_IndexOutOfBoundsError _err1__tmp103;
        til_AllocError _err2__tmp103;
        til_Array _tmp104;
        til_AllocError _err_alloc__tmp105;
        til_IndexOutOfBoundsError _err_idx__tmp105;
        til_Str _tmp106 = til_Str_from_literal("get_substr: start and end are the same (");
        til_Str _tmp107 = til_I64_to_str(til_start);
        til_Str _tmp108 = til_Str_from_literal("), no substring");
        int _arr_status__tmp105 = til_Array_new(&_tmp104, &_err_alloc__tmp105, "Str", 3);
        if (_arr_status__tmp105 != 0) {
            *_err2 = _err_alloc__tmp105; return 2;
        }
        _arr_status__tmp105 = til_Array_set(&_err_idx__tmp105, &_tmp104, 0, &_tmp106);
        if (_arr_status__tmp105 != 0) {
            *_err1 = _err_idx__tmp105; return 1;
        }
        _arr_status__tmp105 = til_Array_set(&_err_idx__tmp105, &_tmp104, 1, &_tmp107);
        if (_arr_status__tmp105 != 0) {
            *_err1 = _err_idx__tmp105; return 1;
        }
        _arr_status__tmp105 = til_Array_set(&_err_idx__tmp105, &_tmp104, 2, &_tmp108);
        if (_arr_status__tmp105 != 0) {
            *_err1 = _err_idx__tmp105; return 1;
        }
        int _status__tmp103 = til_format(&_tmp102, &_err0__tmp103, &_err1__tmp103, &_err2__tmp103, til_Str_from_literal("src/test/constfold.til:369:48:"), &_tmp104);
        if (_status__tmp103 != 0) {
            if (_status__tmp103 == 2) { *_err1 = _err1__tmp103; return 1; }
            if (_status__tmp103 == 3) { *_err2 = _err2__tmp103; return 2; }
        }
        til_Array_delete(&_tmp104);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp102);
        return 1;
    }
    til_Str til_substr = {.c_string = 0, .cap = 0};
    til_substr.cap = til_sub(til_end, til_start);
    til_I64 _ret__tmp109;
    til_AllocError _err0__tmp109 = {};
    int _status__tmp109 = til_malloc(&_ret__tmp109, &_err0__tmp109, til_substr.cap);
    if (_status__tmp109 == 1) { *_err2 = _err0__tmp109; return 2; }
    til_substr.c_string = _ret__tmp109;
    if (til_I64_eq(til_NULL, til_substr.c_string).data) {
        til_Str _tmp111;
        til_I64_OverflowError _err0__tmp112;
        til_IndexOutOfBoundsError _err1__tmp112;
        til_AllocError _err2__tmp112;
        til_Array _tmp113;
        til_AllocError _err_alloc__tmp114;
        til_IndexOutOfBoundsError _err_idx__tmp114;
        til_Str _tmp115 = til_Str_from_literal("Str.get_substr: failed to allocate ");
        til_Str _tmp116 = til_I64_to_str(til_substr.cap);
        til_Str _tmp117 = til_Str_from_literal(" bytes");
        int _arr_status__tmp114 = til_Array_new(&_tmp113, &_err_alloc__tmp114, "Str", 3);
        if (_arr_status__tmp114 != 0) {
            *_err2 = _err_alloc__tmp114; return 2;
        }
        _arr_status__tmp114 = til_Array_set(&_err_idx__tmp114, &_tmp113, 0, &_tmp115);
        if (_arr_status__tmp114 != 0) {
            *_err1 = _err_idx__tmp114; return 1;
        }
        _arr_status__tmp114 = til_Array_set(&_err_idx__tmp114, &_tmp113, 1, &_tmp116);
        if (_arr_status__tmp114 != 0) {
            *_err1 = _err_idx__tmp114; return 1;
        }
        _arr_status__tmp114 = til_Array_set(&_err_idx__tmp114, &_tmp113, 2, &_tmp117);
        if (_arr_status__tmp114 != 0) {
            *_err1 = _err_idx__tmp114; return 1;
        }
        int _status__tmp112 = til_format(&_tmp111, &_err0__tmp112, &_err1__tmp112, &_err2__tmp112, til_Str_from_literal("src/test/constfold.til:376:37:"), &_tmp113);
        if (_status__tmp112 != 0) {
            if (_status__tmp112 == 2) { *_err1 = _err1__tmp112; return 1; }
            if (_status__tmp112 == 3) { *_err2 = _err2__tmp112; return 2; }
        }
        til_Array_delete(&_tmp113);
        *_err2 = til_AllocError_new(_tmp111);
        return 2;
    }
    til_memcpy(til_substr.c_string, til_add(til_s.c_string, til_start), til_substr.cap);
    *_ret = til_substr;
    return 0;
}

int til_get_char(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_pos) {
    til_Str _ret__tmp119;
    til_IndexOutOfBoundsError _err0__tmp119 = {};
    til_AllocError _err1__tmp119 = {};
    int _status__tmp119 = til_get_substr(&_ret__tmp119, &_err0__tmp119, &_err1__tmp119, til_s, til_pos, til_add(til_pos, 1));
    if (_status__tmp119 == 1) { *_err1 = _err0__tmp119; return 1; }
    if (_status__tmp119 == 2) { *_err2 = _err1__tmp119; return 2; }
    *_ret = _ret__tmp119;
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
    til_AllocError _thrown_AllocError__tmp124;
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_add(til_a.cap, til_b.cap);
    if (til_lt(til_result.cap, til_a.cap).data) {
        til_Array _tmp126;
        til_AllocError _err_alloc__tmp127;
        til_IndexOutOfBoundsError _err_idx__tmp127;
        til_Str _tmp128 = til_Str_from_literal("concat: integer overflow");
        int _arr_status__tmp127 = til_Array_new(&_tmp126, &_err_alloc__tmp127, "Str", 1);
        if (_arr_status__tmp127 != 0) {
        }
        _arr_status__tmp127 = til_Array_set(&_err_idx__tmp127, &_tmp126, 0, &_tmp128);
        if (_arr_status__tmp127 != 0) {
        }
        til_panic(til_Str_from_literal("src/test/constfold.til:416:15:"), &_tmp126);
        til_Array_delete(&_tmp126);
    }
    til_I64 _ret__tmp129;
    til_AllocError _err0__tmp129 = {};
    int _status__tmp129 = til_malloc(&_ret__tmp129, &_err0__tmp129, til_result.cap);
    if (_status__tmp129 == 0) {
        til_result.c_string = _ret__tmp129;
    } else if (_status__tmp129 == 1) {
        til_AllocError til_err = _err0__tmp129;
        til_Array _tmp131;
        til_AllocError _err_alloc__tmp132;
        til_IndexOutOfBoundsError _err_idx__tmp132;
        til_Str _tmp133 = til_err.msg;
        int _arr_status__tmp132 = til_Array_new(&_tmp131, &_err_alloc__tmp132, "Str", 1);
        if (_arr_status__tmp132 != 0) {
        }
        _arr_status__tmp132 = til_Array_set(&_err_idx__tmp132, &_tmp131, 0, &_tmp133);
        if (_arr_status__tmp132 != 0) {
        }
        til_panic(til_Str_from_literal("src/test/constfold.til:428:15:"), &_tmp131);
        til_Array_delete(&_tmp131);
    }
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Array _tmp135;
        til_AllocError _err_alloc__tmp136;
        til_IndexOutOfBoundsError _err_idx__tmp136;
        til_Str _tmp137 = til_Str_from_literal("concat: malloc failed");
        int _arr_status__tmp136 = til_Array_new(&_tmp135, &_err_alloc__tmp136, "Str", 1);
        if (_arr_status__tmp136 != 0) {
        }
        _arr_status__tmp136 = til_Array_set(&_err_idx__tmp136, &_tmp135, 0, &_tmp137);
        if (_arr_status__tmp136 != 0) {
        }
        til_panic(til_Str_from_literal("src/test/constfold.til:421:15:"), &_tmp135);
        til_Array_delete(&_tmp135);
    }
    til_memcpy(til_result.c_string, til_a.c_string, til_a.cap);
    til_memcpy(til_add(til_result.c_string, til_a.cap), til_b.c_string, til_b.cap);
    return til_result;
    goto _end_catches__tmp124;
_catch_AllocError__tmp124: {
    til_AllocError til_err = _thrown_AllocError__tmp124;
    til_Array _tmp139;
    til_AllocError _err_alloc__tmp140;
    til_IndexOutOfBoundsError _err_idx__tmp140;
    til_Str _tmp141 = til_err.msg;
    int _arr_status__tmp140 = til_Array_new(&_tmp139, &_err_alloc__tmp140, "Str", 1);
    if (_arr_status__tmp140 != 0) {
    }
    _arr_status__tmp140 = til_Array_set(&_err_idx__tmp140, &_tmp139, 0, &_tmp141);
    if (_arr_status__tmp140 != 0) {
    }
    til_panic(til_Str_from_literal("src/test/constfold.til:428:15:"), &_tmp139);
    til_Array_delete(&_tmp139);
    }
_end_catches__tmp124:;
}

int til_format(til_Str* _ret, til_I64_OverflowError* _err1, til_IndexOutOfBoundsError* _err2, til_AllocError* _err3, const til_Str til_prefix, til_Array* til_args) {
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_prefix.cap;
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Str til_arg = til_Str_from_literal("");
        til_IndexOutOfBoundsError _err0__tmp145 = {};
        int _status__tmp145 = til_Array_get(&_err0__tmp145, (*til_args), til_i, (til_Dynamic*)&til_arg);
        if (_status__tmp145 == 1) { *_err2 = _err0__tmp145; return 2; }
        til_result.cap = til_add(til_result.cap, til_arg.cap);
        if (til_lt(til_result.cap, til_arg.cap).data) {
            til_Str _tmp147;
            til_I64_OverflowError _err0__tmp148;
            til_IndexOutOfBoundsError _err1__tmp148;
            til_AllocError _err2__tmp148;
            til_Array _tmp149;
            til_AllocError _err_alloc__tmp150;
            til_IndexOutOfBoundsError _err_idx__tmp150;
            til_Str _tmp151 = til_Str_from_literal("format: integer overflow while summing cap for arg ");
            til_Str _tmp152 = til_I64_to_str(til_i);
            int _arr_status__tmp150 = til_Array_new(&_tmp149, &_err_alloc__tmp150, "Str", 2);
            if (_arr_status__tmp150 != 0) {
                *_err3 = _err_alloc__tmp150; return 3;
            }
            _arr_status__tmp150 = til_Array_set(&_err_idx__tmp150, &_tmp149, 0, &_tmp151);
            if (_arr_status__tmp150 != 0) {
                *_err2 = _err_idx__tmp150; return 2;
            }
            _arr_status__tmp150 = til_Array_set(&_err_idx__tmp150, &_tmp149, 1, &_tmp152);
            if (_arr_status__tmp150 != 0) {
                *_err2 = _err_idx__tmp150; return 2;
            }
            int _status__tmp148 = til_format(&_tmp147, &_err0__tmp148, &_err1__tmp148, &_err2__tmp148, til_Str_from_literal("src/test/constfold.til:444:48:"), &_tmp149);
            if (_status__tmp148 != 0) {
                if (_status__tmp148 == 1) { *_err1 = _err0__tmp148; return 1; }
                if (_status__tmp148 == 2) { *_err2 = _err1__tmp148; return 2; }
                if (_status__tmp148 == 3) { *_err3 = _err2__tmp148; return 3; }
            }
            til_Array_delete(&_tmp149);
            *_err1 = til_I64_OverflowError_new(_tmp147);
            return 1;
        }
        til_I64_inc(&til_i);
    }
    til_I64 _ret__tmp153;
    til_AllocError _err0__tmp153 = {};
    int _status__tmp153 = til_malloc(&_ret__tmp153, &_err0__tmp153, til_result.cap);
    if (_status__tmp153 == 1) { *_err3 = _err0__tmp153; return 3; }
    til_result.c_string = _ret__tmp153;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Str _tmp155;
        til_I64_OverflowError _err0__tmp156;
        til_IndexOutOfBoundsError _err1__tmp156;
        til_AllocError _err2__tmp156;
        til_Array _tmp157;
        til_AllocError _err_alloc__tmp158;
        til_IndexOutOfBoundsError _err_idx__tmp158;
        til_Str _tmp159 = til_Str_from_literal("format: malloc failed for cap = ");
        til_Str _tmp160 = til_I64_to_str(til_result.cap);
        int _arr_status__tmp158 = til_Array_new(&_tmp157, &_err_alloc__tmp158, "Str", 2);
        if (_arr_status__tmp158 != 0) {
            *_err3 = _err_alloc__tmp158; return 3;
        }
        _arr_status__tmp158 = til_Array_set(&_err_idx__tmp158, &_tmp157, 0, &_tmp159);
        if (_arr_status__tmp158 != 0) {
            *_err2 = _err_idx__tmp158; return 2;
        }
        _arr_status__tmp158 = til_Array_set(&_err_idx__tmp158, &_tmp157, 1, &_tmp160);
        if (_arr_status__tmp158 != 0) {
            *_err2 = _err_idx__tmp158; return 2;
        }
        int _status__tmp156 = til_format(&_tmp155, &_err0__tmp156, &_err1__tmp156, &_err2__tmp156, til_Str_from_literal("src/test/constfold.til:450:37:"), &_tmp157);
        if (_status__tmp156 != 0) {
            if (_status__tmp156 == 1) { *_err1 = _err0__tmp156; return 1; }
            if (_status__tmp156 == 2) { *_err2 = _err1__tmp156; return 2; }
            if (_status__tmp156 == 3) { *_err3 = _err2__tmp156; return 3; }
        }
        til_Array_delete(&_tmp157);
        *_err3 = til_AllocError_new(_tmp155);
        return 3;
    }
    til_I64 til_offset = 0;
    til_memcpy(til_result.c_string, til_prefix.c_string, til_prefix.cap);
    til_offset = til_prefix.cap;
    til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Str til_s = til_Str_from_literal("");
        til_IndexOutOfBoundsError _err0__tmp163 = {};
        int _status__tmp163 = til_Array_get(&_err0__tmp163, (*til_args), til_i, (til_Dynamic*)&til_s);
        if (_status__tmp163 == 1) { *_err2 = _err0__tmp163; return 2; }
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
        til_Array _tmp167;
        til_AllocError _err_alloc__tmp168;
        til_IndexOutOfBoundsError _err_idx__tmp168;
        til_Str _tmp169 = til_loc_str;
        til_Str _tmp170 = til_Str_from_literal("assert_eq_str failed: expected '");
        til_Str _tmp171 = til_a;
        til_Str _tmp172 = til_Str_from_literal("', found '");
        til_Str _tmp173 = til_b;
        til_Str _tmp174 = til_Str_from_literal("'");
        int _arr_status__tmp168 = til_Array_new(&_tmp167, &_err_alloc__tmp168, "Str", 6);
        if (_arr_status__tmp168 != 0) {
        }
        _arr_status__tmp168 = til_Array_set(&_err_idx__tmp168, &_tmp167, 0, &_tmp169);
        if (_arr_status__tmp168 != 0) {
        }
        _arr_status__tmp168 = til_Array_set(&_err_idx__tmp168, &_tmp167, 1, &_tmp170);
        if (_arr_status__tmp168 != 0) {
        }
        _arr_status__tmp168 = til_Array_set(&_err_idx__tmp168, &_tmp167, 2, &_tmp171);
        if (_arr_status__tmp168 != 0) {
        }
        _arr_status__tmp168 = til_Array_set(&_err_idx__tmp168, &_tmp167, 3, &_tmp172);
        if (_arr_status__tmp168 != 0) {
        }
        _arr_status__tmp168 = til_Array_set(&_err_idx__tmp168, &_tmp167, 4, &_tmp173);
        if (_arr_status__tmp168 != 0) {
        }
        _arr_status__tmp168 = til_Array_set(&_err_idx__tmp168, &_tmp167, 5, &_tmp174);
        if (_arr_status__tmp168 != 0) {
        }
        til_println(&_tmp167);
        til_Array_delete(&_tmp167);
        til_exit(1);
    }
}

void til_assert_eq(const til_Str til_loc_str, const til_I64 til_a, const til_I64 til_b) {
    if (til_not(til_I64_eq(til_a, til_b)).data) {
        til_Array _tmp177;
        til_AllocError _err_alloc__tmp178;
        til_IndexOutOfBoundsError _err_idx__tmp178;
        til_Str _tmp179 = til_loc_str;
        til_Str _tmp180 = til_Str_from_literal("assert_eq failed: expected '");
        til_Str _tmp181 = til_I64_to_str(til_a);
        til_Str _tmp182 = til_Str_from_literal("', found '");
        til_Str _tmp183 = til_I64_to_str(til_b);
        til_Str _tmp184 = til_Str_from_literal("'");
        int _arr_status__tmp178 = til_Array_new(&_tmp177, &_err_alloc__tmp178, "Str", 6);
        if (_arr_status__tmp178 != 0) {
        }
        _arr_status__tmp178 = til_Array_set(&_err_idx__tmp178, &_tmp177, 0, &_tmp179);
        if (_arr_status__tmp178 != 0) {
        }
        _arr_status__tmp178 = til_Array_set(&_err_idx__tmp178, &_tmp177, 1, &_tmp180);
        if (_arr_status__tmp178 != 0) {
        }
        _arr_status__tmp178 = til_Array_set(&_err_idx__tmp178, &_tmp177, 2, &_tmp181);
        if (_arr_status__tmp178 != 0) {
        }
        _arr_status__tmp178 = til_Array_set(&_err_idx__tmp178, &_tmp177, 3, &_tmp182);
        if (_arr_status__tmp178 != 0) {
        }
        _arr_status__tmp178 = til_Array_set(&_err_idx__tmp178, &_tmp177, 4, &_tmp183);
        if (_arr_status__tmp178 != 0) {
        }
        _arr_status__tmp178 = til_Array_set(&_err_idx__tmp178, &_tmp177, 5, &_tmp184);
        if (_arr_status__tmp178 != 0) {
        }
        til_println(&_tmp177);
        til_Array_delete(&_tmp177);
        til_exit(1);
    }
}

void til_test_simple_add(void) {
    const til_I64 til_result = 3;
    til_test(til_Str_from_literal("src/test/constfold.til:8:10:"), til_I64_eq(til_result, 3), til_Str_from_literal("add(1, 2) should be 3"));
}

void til_test_nested_arithmetic(void) {
    const til_I64 til_result = 15;
    til_test(til_Str_from_literal("src/test/constfold.til:15:10:"), til_I64_eq(til_result, 15), til_Str_from_literal("mul(add(1, 2), sub(10, 5)) should be 15"));
}

void til_test_deeply_nested(void) {
    const til_I64 til_result = 26;
    til_test(til_Str_from_literal("src/test/constfold.til:22:10:"), til_I64_eq(til_result, 26), til_Str_from_literal("add(mul(2, 3), mul(4, 5)) should be 26"));
}

void til_test_string_concat(void) {
    const til_Str til_result = til_concat(til_Str_from_literal("hello"), til_Str_from_literal(" world"));
    til_test(til_Str_from_literal("src/test/constfold.til:30:10:"), til_Str_eq(til_result, til_Str_from_literal("hello world")), til_Str_from_literal("concat works at runtime"));
}

void til_test_no_fold_variable(void) {
    const til_I64 til_x = 5;
    const til_I64 til_result = til_add(til_x, 3);
    til_test(til_Str_from_literal("src/test/constfold.til:39:10:"), til_I64_eq(til_result, 8), til_Str_from_literal("add(x, 3) should still work at runtime"));
}

void til_test_loc_folded_correctly(void) {
    const til_Str til_location = til_Str_from_literal("src/test/constfold.til:45:17:");
    til_test(til_Str_from_literal("src/test/constfold.til:46:10:"), til_Str_contains(til_location, til_Str_from_literal("constfold.til")), til_Str_from_literal("loc() should contain filename"));
    til_test(til_Str_from_literal("src/test/constfold.til:47:10:"), til_Str_contains(til_location, til_Str_from_literal(":45:")), til_Str_from_literal("loc() should contain correct line number"));
}

til_IndexOutOfBoundsError til_IndexOutOfBoundsError_new(const til_Str til_msg) {
    til_IndexOutOfBoundsError til_err = {.msg = til_Str_from_literal("")};
    til_err.msg = til_msg;
    return til_err;
}

til_AllocError til_AllocError_new(const til_Str til_msg) {
    til_AllocError til_err = {.msg = til_Str_from_literal("")};
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
    til_Array til_arr = {.type_name = til_Str_from_literal(""), .type_size = 0, .ptr = 0, ._len = 0};
    til_arr.type_name = til_Str_from_literal("T");
    til_arr.type_size = til_size_of(til_Str_from_literal(til_T));
    const til_I64 til_size_bytes = til_mul(til_capacity, til_arr.type_size);
    til_I64 _ret__tmp196;
    til_AllocError _err0__tmp196 = {};
    int _status__tmp196 = til_malloc(&_ret__tmp196, &_err0__tmp196, til_size_bytes);
    if (_status__tmp196 == 1) { *_err1 = _err0__tmp196; return 1; }
    til_arr.ptr = _ret__tmp196;
    til_U8 _tmp197;
    til_U8_OverflowError _err0__tmp198;
    int _status__tmp198 = til_U8_from_i64(&_tmp197, &_err0__tmp198, 0);
    if (_status__tmp198 != 0) {
    }
    til_memset(til_arr.ptr, _tmp197, til_size_bytes);
    til_arr._len = til_capacity;
    *_ret = til_arr;
    return 0;
}

int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array til_self, const til_I64 til_index, til_Dynamic* til_T) {
    if (til_gteq(til_index, til_self._len).data) {
        til_Str _tmp201;
        til_I64_OverflowError _err0__tmp202;
        til_IndexOutOfBoundsError _err1__tmp202;
        til_AllocError _err2__tmp202;
        til_Array _tmp203;
        til_AllocError _err_alloc__tmp204;
        til_IndexOutOfBoundsError _err_idx__tmp204;
        til_Str _tmp205 = til_Str_from_literal("Array.get: index out of bounds");
        int _arr_status__tmp204 = til_Array_new(&_tmp203, &_err_alloc__tmp204, "Str", 1);
        if (_arr_status__tmp204 != 0) {
        }
        _arr_status__tmp204 = til_Array_set(&_err_idx__tmp204, &_tmp203, 0, &_tmp205);
        if (_arr_status__tmp204 != 0) {
            *_err1 = _err_idx__tmp204; return 1;
        }
        int _status__tmp202 = til_format(&_tmp201, &_err0__tmp202, &_err1__tmp202, &_err2__tmp202, til_Str_from_literal("src/test/constfold.til:41:52:"), &_tmp203);
        if (_status__tmp202 != 0) {
            if (_status__tmp202 == 2) { *_err1 = _err1__tmp202; return 1; }
        }
        til_Array_delete(&_tmp203);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp201);
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_gteq(til_index, til_self->_len).data) {
        til_Str _tmp208;
        til_I64_OverflowError _err0__tmp209;
        til_IndexOutOfBoundsError _err1__tmp209;
        til_AllocError _err2__tmp209;
        til_Array _tmp210;
        til_AllocError _err_alloc__tmp211;
        til_IndexOutOfBoundsError _err_idx__tmp211;
        til_Str _tmp212 = til_Str_from_literal("Array.set: index out of bounds");
        int _arr_status__tmp211 = til_Array_new(&_tmp210, &_err_alloc__tmp211, "Str", 1);
        if (_arr_status__tmp211 != 0) {
        }
        _arr_status__tmp211 = til_Array_set(&_err_idx__tmp211, &_tmp210, 0, &_tmp212);
        if (_arr_status__tmp211 != 0) {
            *_err1 = _err_idx__tmp211; return 1;
        }
        int _status__tmp209 = til_format(&_tmp208, &_err0__tmp209, &_err1__tmp209, &_err2__tmp209, til_Str_from_literal("src/test/constfold.til:56:52:"), &_tmp210);
        if (_status__tmp209 != 0) {
            if (_status__tmp209 == 2) { *_err1 = _err1__tmp209; return 1; }
        }
        til_Array_delete(&_tmp210);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp208);
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
    til_Array til_cloned = {.type_name = til_Str_from_literal(""), .type_size = 0, .ptr = 0, ._len = 0};
    til_cloned.type_name = til_self.type_name;
    til_cloned.type_size = til_self.type_size;
    til_cloned._len = til_self._len;
    til_I64 til_total_bytes = til_mul(til_self._len, til_self.type_size);
    til_I64 _ret__tmp215;
    til_AllocError _err0__tmp215 = {};
    int _status__tmp215 = til_malloc(&_ret__tmp215, &_err0__tmp215, til_total_bytes);
    if (_status__tmp215 == 1) { *_err1 = _err0__tmp215; return 1; }
    til_cloned.ptr = _ret__tmp215;
    if (til_I64_eq(til_NULL, til_cloned.ptr).data) {
        til_Str _tmp217;
        til_I64_OverflowError _err0__tmp218;
        til_IndexOutOfBoundsError _err1__tmp218;
        til_AllocError _err2__tmp218;
        til_Array _tmp219;
        til_AllocError _err_alloc__tmp220;
        til_IndexOutOfBoundsError _err_idx__tmp220;
        til_Str _tmp221 = til_Str_from_literal("Array.clone: malloc failed for ");
        til_Str _tmp222 = til_I64_to_str(til_total_bytes);
        til_Str _tmp223 = til_Str_from_literal(" bytes");
        int _arr_status__tmp220 = til_Array_new(&_tmp219, &_err_alloc__tmp220, "Str", 3);
        if (_arr_status__tmp220 != 0) {
            *_err1 = _err_alloc__tmp220; return 1;
        }
        _arr_status__tmp220 = til_Array_set(&_err_idx__tmp220, &_tmp219, 0, &_tmp221);
        if (_arr_status__tmp220 != 0) {
        }
        _arr_status__tmp220 = til_Array_set(&_err_idx__tmp220, &_tmp219, 1, &_tmp222);
        if (_arr_status__tmp220 != 0) {
        }
        _arr_status__tmp220 = til_Array_set(&_err_idx__tmp220, &_tmp219, 2, &_tmp223);
        if (_arr_status__tmp220 != 0) {
        }
        int _status__tmp218 = til_format(&_tmp217, &_err0__tmp218, &_err1__tmp218, &_err2__tmp218, til_Str_from_literal("src/test/constfold.til:83:41:"), &_tmp219);
        if (_status__tmp218 != 0) {
            if (_status__tmp218 == 3) { *_err1 = _err2__tmp218; return 1; }
        }
        til_Array_delete(&_tmp219);
        *_err1 = til_AllocError_new(_tmp217);
        return 1;
    }
    til_memcpy(til_cloned.ptr, til_self.ptr, til_total_bytes);
    *_ret = til_cloned;
    return 0;
}

til_Bool til_Array_contains(const til_Array til_self, const til_Str til_value) {
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp224;
    til_I64 til_i = 0;
    while (til_lt(til_i, til_self._len).data) {
        til_Str til_elem = til_Str_from_literal("");
        til_IndexOutOfBoundsError _err0__tmp226 = {};
        int _status__tmp226 = til_Array_get(&_err0__tmp226, til_self, til_i, (til_Dynamic*)&til_elem);
        if (_status__tmp226 == 1) { _thrown_IndexOutOfBoundsError__tmp224 = _err0__tmp226; goto _catch_IndexOutOfBoundsError__tmp224; }
        if (til_Str_eq(til_elem, til_value).data) {
            return true;
        }
        til_i = til_add(til_i, 1);
    }
    return false;
    goto _end_catches__tmp224;
_catch_IndexOutOfBoundsError__tmp224: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp224;
    }
_end_catches__tmp224:;
}

til_I64 til_Bool_len(const til_Bool til_self) {
    return 1;
}

til_Bool til_Bool_eq(const til_Bool til_a, const til_Bool til_b) {
    til_Bool _tmp231;
    til_Array _tmp232;
    til_AllocError _err_alloc__tmp233;
    til_IndexOutOfBoundsError _err_idx__tmp233;
    til_Bool _tmp234 = til_a;
    til_Bool _tmp235 = til_b;
    int _arr_status__tmp233 = til_Array_new(&_tmp232, &_err_alloc__tmp233, "Bool", 2);
    if (_arr_status__tmp233 != 0) {
    }
    _arr_status__tmp233 = til_Array_set(&_err_idx__tmp233, &_tmp232, 0, &_tmp234);
    if (_arr_status__tmp233 != 0) {
    }
    _arr_status__tmp233 = til_Array_set(&_err_idx__tmp233, &_tmp232, 1, &_tmp235);
    if (_arr_status__tmp233 != 0) {
    }
    _tmp231 = til_and(&_tmp232);
    til_Array_delete(&_tmp232);
    til_Bool _tmp236;
    til_Array _tmp237;
    til_AllocError _err_alloc__tmp238;
    til_IndexOutOfBoundsError _err_idx__tmp238;
    til_Bool _tmp239 = til_not(til_b);
    til_Bool _tmp240 = til_not(til_a);
    int _arr_status__tmp238 = til_Array_new(&_tmp237, &_err_alloc__tmp238, "Bool", 2);
    if (_arr_status__tmp238 != 0) {
    }
    _arr_status__tmp238 = til_Array_set(&_err_idx__tmp238, &_tmp237, 0, &_tmp239);
    if (_arr_status__tmp238 != 0) {
    }
    _arr_status__tmp238 = til_Array_set(&_err_idx__tmp238, &_tmp237, 1, &_tmp240);
    if (_arr_status__tmp238 != 0) {
    }
    _tmp236 = til_and(&_tmp237);
    til_Array_delete(&_tmp237);
    til_Array _tmp241;
    til_AllocError _err_alloc__tmp242;
    til_IndexOutOfBoundsError _err_idx__tmp242;
    int _arr_status__tmp242 = til_Array_new(&_tmp241, &_err_alloc__tmp242, "Bool", 2);
    if (_arr_status__tmp242 != 0) {
    }
    _arr_status__tmp242 = til_Array_set(&_err_idx__tmp242, &_tmp241, 0, &_tmp231);
    if (_arr_status__tmp242 != 0) {
    }
    _arr_status__tmp242 = til_Array_set(&_err_idx__tmp242, &_tmp241, 1, &_tmp236);
    if (_arr_status__tmp242 != 0) {
    }
    til_Bool _tmp243 = til_or(&_tmp241);
    til_Array_delete(&_tmp241);
    return _tmp243;
}

til_Str til_Bool_to_str(const til_Bool til_self) {
    if (til_self.data) {
        return til_Str_from_literal("true");
    }
    return til_Str_from_literal("false");
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
    til_I64_OverflowError til_err = {.msg = til_Str_from_literal("")};
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
    til_Vec til_vec = {.type_name = til_Str_from_literal(""), .type_size = 0, .ptr = 0, ._len = 0, .cap = 0};
    til_vec.type_name = til_Str_from_literal("T");
    til_vec.type_size = til_size_of(til_Str_from_literal(til_T));
    const til_I64 til_size_bytes = til_mul(til_Vec_INIT_CAP, til_vec.type_size);
    til_I64 _ret__tmp267;
    til_AllocError _err0__tmp267 = {};
    int _status__tmp267 = til_malloc(&_ret__tmp267, &_err0__tmp267, til_size_bytes);
    if (_status__tmp267 == 1) { *_err1 = _err0__tmp267; return 1; }
    til_vec.ptr = _ret__tmp267;
    til_vec._len = 0;
    til_vec.cap = til_Vec_INIT_CAP;
    *_ret = til_vec;
    return 0;
}

int til_Vec_new_from_type_info(til_Vec* _ret, til_AllocError* _err1, const til_Str til_type_name, const til_I64 til_type_size) {
    til_Vec til_vec = {.type_name = til_Str_from_literal(""), .type_size = 0, .ptr = 0, ._len = 0, .cap = 0};
    til_vec.type_name = til_type_name;
    til_vec.type_size = til_type_size;
    const til_I64 til_size_bytes = til_mul(til_Vec_INIT_CAP, til_vec.type_size);
    til_I64 _ret__tmp269;
    til_AllocError _err0__tmp269 = {};
    int _status__tmp269 = til_malloc(&_ret__tmp269, &_err0__tmp269, til_size_bytes);
    if (_status__tmp269 == 1) { *_err1 = _err0__tmp269; return 1; }
    til_vec.ptr = _ret__tmp269;
    til_vec._len = 0;
    til_vec.cap = til_Vec_INIT_CAP;
    *_ret = til_vec;
    return 0;
}

int til_Vec_push(til_AllocError* _err1, til_Vec* til_self, const til_Dynamic til_value) {
    if (til_I64_eq(til_self->_len, til_self->cap).data) {
        const til_I64 til_new_cap = til_mul(til_self->cap, 2);
        if (til_gt(til_new_cap, til_Vec_MAX_CAP).data) {
            til_Array _tmp273;
            til_AllocError _err_alloc__tmp274;
            til_IndexOutOfBoundsError _err_idx__tmp274;
            til_Str _tmp275 = til_Str_from_literal("Vec.push: capacity exceeded Vec.MAX_CAP");
            int _arr_status__tmp274 = til_Array_new(&_tmp273, &_err_alloc__tmp274, "Str", 1);
            if (_arr_status__tmp274 != 0) {
                *_err1 = _err_alloc__tmp274; return 1;
            }
            _arr_status__tmp274 = til_Array_set(&_err_idx__tmp274, &_tmp273, 0, &_tmp275);
            if (_arr_status__tmp274 != 0) {
            }
            til_panic(til_Str_from_literal("src/test/constfold.til:63:23:"), &_tmp273);
            til_Array_delete(&_tmp273);
        }
        til_I64 _ret__tmp276;
        til_I64 til_new_ptr;
        til_AllocError _err0__tmp276 = {};
        int _status__tmp276 = til_malloc(&_ret__tmp276, &_err0__tmp276, til_mul(til_new_cap, til_self->type_size));
        if (_status__tmp276 == 1) { *_err1 = _err0__tmp276; return 1; }
        til_new_ptr = _ret__tmp276;
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
        til_Str _tmp279;
        til_I64_OverflowError _err0__tmp280;
        til_IndexOutOfBoundsError _err1__tmp280;
        til_AllocError _err2__tmp280;
        til_Array _tmp281;
        til_AllocError _err_alloc__tmp282;
        til_IndexOutOfBoundsError _err_idx__tmp282;
        til_Str _tmp283 = til_Str_from_literal("Vec.get: index out of bounds");
        int _arr_status__tmp282 = til_Array_new(&_tmp281, &_err_alloc__tmp282, "Str", 1);
        if (_arr_status__tmp282 != 0) {
        }
        _arr_status__tmp282 = til_Array_set(&_err_idx__tmp282, &_tmp281, 0, &_tmp283);
        if (_arr_status__tmp282 != 0) {
            *_err1 = _err_idx__tmp282; return 1;
        }
        int _status__tmp280 = til_format(&_tmp279, &_err0__tmp280, &_err1__tmp280, &_err2__tmp280, til_Str_from_literal("src/test/constfold.til:81:52:"), &_tmp281);
        if (_status__tmp280 != 0) {
            if (_status__tmp280 == 2) { *_err1 = _err1__tmp280; return 1; }
        }
        til_Array_delete(&_tmp281);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp279);
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Vec_set(til_IndexOutOfBoundsError* _err1, til_Vec* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_gteq(til_index, til_self->_len).data) {
        til_Str _tmp286;
        til_I64_OverflowError _err0__tmp287;
        til_IndexOutOfBoundsError _err1__tmp287;
        til_AllocError _err2__tmp287;
        til_Array _tmp288;
        til_AllocError _err_alloc__tmp289;
        til_IndexOutOfBoundsError _err_idx__tmp289;
        til_Str _tmp290 = til_Str_from_literal("Vec.set: index out of bounds");
        int _arr_status__tmp289 = til_Array_new(&_tmp288, &_err_alloc__tmp289, "Str", 1);
        if (_arr_status__tmp289 != 0) {
        }
        _arr_status__tmp289 = til_Array_set(&_err_idx__tmp289, &_tmp288, 0, &_tmp290);
        if (_arr_status__tmp289 != 0) {
            *_err1 = _err_idx__tmp289; return 1;
        }
        int _status__tmp287 = til_format(&_tmp286, &_err0__tmp287, &_err1__tmp287, &_err2__tmp287, til_Str_from_literal("src/test/constfold.til:96:52:"), &_tmp288);
        if (_status__tmp287 != 0) {
            if (_status__tmp287 == 2) { *_err1 = _err1__tmp287; return 1; }
        }
        til_Array_delete(&_tmp288);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp286);
        return 1;
    }
    til_I64 til_dest = til_add(til_self->ptr, til_mul(til_index, til_self->type_size));
    til_memcpy(til_dest, (til_I64)til_value, til_self->type_size);
    return 0;
}

int til_Vec_pop(til_IndexOutOfBoundsError* _err1, til_Vec* til_self, til_Dynamic* til_dest) {
    if (til_I64_eq(til_self->_len, 0).data) {
        til_Str _tmp293;
        til_I64_OverflowError _err0__tmp294;
        til_IndexOutOfBoundsError _err1__tmp294;
        til_AllocError _err2__tmp294;
        til_Array _tmp295;
        til_AllocError _err_alloc__tmp296;
        til_IndexOutOfBoundsError _err_idx__tmp296;
        til_Str _tmp297 = til_Str_from_literal("Vec.pop: cannot pop from empty Vec");
        int _arr_status__tmp296 = til_Array_new(&_tmp295, &_err_alloc__tmp296, "Str", 1);
        if (_arr_status__tmp296 != 0) {
        }
        _arr_status__tmp296 = til_Array_set(&_err_idx__tmp296, &_tmp295, 0, &_tmp297);
        if (_arr_status__tmp296 != 0) {
            *_err1 = _err_idx__tmp296; return 1;
        }
        int _status__tmp294 = til_format(&_tmp293, &_err0__tmp294, &_err1__tmp294, &_err2__tmp294, til_Str_from_literal("src/test/constfold.til:110:52:"), &_tmp295);
        if (_status__tmp294 != 0) {
            if (_status__tmp294 == 2) { *_err1 = _err1__tmp294; return 1; }
        }
        til_Array_delete(&_tmp295);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp293);
        return 1;
    }
    til_I64 til_last_index = til_sub(til_self->_len, 1);
    til_IndexOutOfBoundsError _err0__tmp298 = {};
    int _status__tmp298 = til_Vec_get(&_err0__tmp298, (*til_self), til_last_index, (til_Dynamic*)&til_dest);
    if (_status__tmp298 == 1) { *_err1 = _err0__tmp298; return 1; }
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
    til_Vec til_cloned = {.type_name = til_Str_from_literal(""), .type_size = 0, .ptr = 0, ._len = 0, .cap = 0};
    til_cloned.type_name = til_self.type_name;
    til_cloned.type_size = til_self.type_size;
    til_cloned._len = til_self._len;
    til_cloned.cap = til_self.cap;
    til_I64 til_total_bytes = til_mul(til_self.cap, til_self.type_size);
    til_I64 _ret__tmp301;
    til_AllocError _err0__tmp301 = {};
    int _status__tmp301 = til_malloc(&_ret__tmp301, &_err0__tmp301, til_total_bytes);
    if (_status__tmp301 == 1) { *_err1 = _err0__tmp301; return 1; }
    til_cloned.ptr = _ret__tmp301;
    if (til_I64_eq(til_NULL, til_cloned.ptr).data) {
        til_Str _tmp303;
        til_I64_OverflowError _err0__tmp304;
        til_IndexOutOfBoundsError _err1__tmp304;
        til_AllocError _err2__tmp304;
        til_Array _tmp305;
        til_AllocError _err_alloc__tmp306;
        til_IndexOutOfBoundsError _err_idx__tmp306;
        til_Str _tmp307 = til_Str_from_literal("Vec.clone: malloc failed for ");
        til_Str _tmp308 = til_I64_to_str(til_total_bytes);
        til_Str _tmp309 = til_Str_from_literal(" bytes");
        int _arr_status__tmp306 = til_Array_new(&_tmp305, &_err_alloc__tmp306, "Str", 3);
        if (_arr_status__tmp306 != 0) {
            *_err1 = _err_alloc__tmp306; return 1;
        }
        _arr_status__tmp306 = til_Array_set(&_err_idx__tmp306, &_tmp305, 0, &_tmp307);
        if (_arr_status__tmp306 != 0) {
        }
        _arr_status__tmp306 = til_Array_set(&_err_idx__tmp306, &_tmp305, 1, &_tmp308);
        if (_arr_status__tmp306 != 0) {
        }
        _arr_status__tmp306 = til_Array_set(&_err_idx__tmp306, &_tmp305, 2, &_tmp309);
        if (_arr_status__tmp306 != 0) {
        }
        int _status__tmp304 = til_format(&_tmp303, &_err0__tmp304, &_err1__tmp304, &_err2__tmp304, til_Str_from_literal("src/test/constfold.til:139:41:"), &_tmp305);
        if (_status__tmp304 != 0) {
            if (_status__tmp304 == 3) { *_err1 = _err2__tmp304; return 1; }
        }
        til_Array_delete(&_tmp305);
        *_err1 = til_AllocError_new(_tmp303);
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
                til_Array _tmp314;
                til_AllocError _err_alloc__tmp315;
                til_IndexOutOfBoundsError _err_idx__tmp315;
                til_Str _tmp316 = til_Str_from_literal("Vec.extend: capacity exceeded Vec.MAX_CAP");
                int _arr_status__tmp315 = til_Array_new(&_tmp314, &_err_alloc__tmp315, "Str", 1);
                if (_arr_status__tmp315 != 0) {
                    *_err1 = _err_alloc__tmp315; return 1;
                }
                _arr_status__tmp315 = til_Array_set(&_err_idx__tmp315, &_tmp314, 0, &_tmp316);
                if (_arr_status__tmp315 != 0) {
                }
                til_panic(til_Str_from_literal("src/test/constfold.til:158:27:"), &_tmp314);
                til_Array_delete(&_tmp314);
            }
            til_I64 _ret__tmp317;
            til_I64 til_new_ptr;
            til_AllocError _err0__tmp317 = {};
            int _status__tmp317 = til_malloc(&_ret__tmp317, &_err0__tmp317, til_mul(til_new_cap, til_self->type_size));
            if (_status__tmp317 == 1) { *_err1 = _err0__tmp317; return 1; }
            til_new_ptr = _ret__tmp317;
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
        if (til_Str_eq(til_self.type_name, til_Str_from_literal("Str")).data) {
            til_Str til_existing = til_Str_from_literal("");
            til_memcpy((til_I64)&til_existing, til_src, til_self.type_size);
            til_Str til_val_str = til_Str_from_literal("");
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
        til_Str _tmp326;
        til_I64_OverflowError _err0__tmp327;
        til_IndexOutOfBoundsError _err1__tmp327;
        til_AllocError _err2__tmp327;
        til_Array _tmp328;
        til_AllocError _err_alloc__tmp329;
        til_IndexOutOfBoundsError _err_idx__tmp329;
        til_Str _tmp330 = til_Str_from_literal("Vec.remove: index out of bounds");
        int _arr_status__tmp329 = til_Array_new(&_tmp328, &_err_alloc__tmp329, "Str", 1);
        if (_arr_status__tmp329 != 0) {
        }
        _arr_status__tmp329 = til_Array_set(&_err_idx__tmp329, &_tmp328, 0, &_tmp330);
        if (_arr_status__tmp329 != 0) {
            *_err1 = _err_idx__tmp329; return 1;
        }
        int _status__tmp327 = til_format(&_tmp326, &_err0__tmp327, &_err1__tmp327, &_err2__tmp327, til_Str_from_literal("src/test/constfold.til:202:52:"), &_tmp328);
        if (_status__tmp327 != 0) {
            if (_status__tmp327 == 2) { *_err1 = _err1__tmp327; return 1; }
        }
        til_Array_delete(&_tmp328);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp326);
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
    til_I64 _ret__tmp340;
    til_AllocError _err0__tmp340 = {};
    int _status__tmp340 = til_malloc(&_ret__tmp340, &_err0__tmp340, til_cloned.cap);
    if (_status__tmp340 == 1) { *_err1 = _err0__tmp340; return 1; }
    til_cloned.c_string = _ret__tmp340;
    if (til_I64_eq(til_NULL, til_cloned.c_string).data) {
        til_Str _tmp342;
        til_I64_OverflowError _err0__tmp343;
        til_IndexOutOfBoundsError _err1__tmp343;
        til_AllocError _err2__tmp343;
        til_Array _tmp344;
        til_AllocError _err_alloc__tmp345;
        til_IndexOutOfBoundsError _err_idx__tmp345;
        til_Str _tmp346 = til_Str_from_literal("Str.clone: malloc failed for ");
        til_Str _tmp347 = til_I64_to_str(til_cloned.cap);
        til_Str _tmp348 = til_Str_from_literal(" bytes");
        int _arr_status__tmp345 = til_Array_new(&_tmp344, &_err_alloc__tmp345, "Str", 3);
        if (_arr_status__tmp345 != 0) {
            *_err1 = _err_alloc__tmp345; return 1;
        }
        _arr_status__tmp345 = til_Array_set(&_err_idx__tmp345, &_tmp344, 0, &_tmp346);
        if (_arr_status__tmp345 != 0) {
        }
        _arr_status__tmp345 = til_Array_set(&_err_idx__tmp345, &_tmp344, 1, &_tmp347);
        if (_arr_status__tmp345 != 0) {
        }
        _arr_status__tmp345 = til_Array_set(&_err_idx__tmp345, &_tmp344, 2, &_tmp348);
        if (_arr_status__tmp345 != 0) {
        }
        int _status__tmp343 = til_format(&_tmp342, &_err0__tmp343, &_err1__tmp343, &_err2__tmp343, til_Str_from_literal("src/test/constfold.til:46:41:"), &_tmp344);
        if (_status__tmp343 != 0) {
            if (_status__tmp343 == 3) { *_err1 = _err2__tmp343; return 1; }
        }
        til_Array_delete(&_tmp344);
        *_err1 = til_AllocError_new(_tmp342);
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
        til_Str _ret__tmp385;
        til_AllocError _err0__tmp385 = {};
        int _status__tmp385 = til_Str_clone(&_ret__tmp385, &_err0__tmp385, til_self);
        if (_status__tmp385 == 1) { *_err1 = _err0__tmp385; return 1; }
        *_ret = _ret__tmp385;
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
        til_Str _ret__tmp393;
        til_AllocError _err0__tmp393 = {};
        int _status__tmp393 = til_Str_clone(&_ret__tmp393, &_err0__tmp393, til_self);
        if (_status__tmp393 == 1) { *_err1 = _err0__tmp393; return 1; }
        *_ret = _ret__tmp393;
        return 0;
    }
    til_I64 til_new_len = til_add(til_sub(til_Str_len(til_self), til_mul(til_count, til_Str_len(til_from))), til_mul(til_count, til_Str_len(til_to)));
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_new_len;
    til_I64 _ret__tmp394;
    til_AllocError _err0__tmp394 = {};
    int _status__tmp394 = til_malloc(&_ret__tmp394, &_err0__tmp394, til_new_len);
    if (_status__tmp394 == 1) { *_err1 = _err0__tmp394; return 1; }
    til_result.c_string = _ret__tmp394;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Str _tmp396;
        til_I64_OverflowError _err0__tmp397;
        til_IndexOutOfBoundsError _err1__tmp397;
        til_AllocError _err2__tmp397;
        til_Array _tmp398;
        til_AllocError _err_alloc__tmp399;
        til_IndexOutOfBoundsError _err_idx__tmp399;
        til_Str _tmp400 = til_Str_from_literal("Str.replace: malloc failed for ");
        til_Str _tmp401 = til_I64_to_str(til_new_len);
        til_Str _tmp402 = til_Str_from_literal(" bytes");
        int _arr_status__tmp399 = til_Array_new(&_tmp398, &_err_alloc__tmp399, "Str", 3);
        if (_arr_status__tmp399 != 0) {
            *_err1 = _err_alloc__tmp399; return 1;
        }
        _arr_status__tmp399 = til_Array_set(&_err_idx__tmp399, &_tmp398, 0, &_tmp400);
        if (_arr_status__tmp399 != 0) {
        }
        _arr_status__tmp399 = til_Array_set(&_err_idx__tmp399, &_tmp398, 1, &_tmp401);
        if (_arr_status__tmp399 != 0) {
        }
        _arr_status__tmp399 = til_Array_set(&_err_idx__tmp399, &_tmp398, 2, &_tmp402);
        if (_arr_status__tmp399 != 0) {
        }
        int _status__tmp397 = til_format(&_tmp396, &_err0__tmp397, &_err1__tmp397, &_err2__tmp397, til_Str_from_literal("src/test/constfold.til:213:41:"), &_tmp398);
        if (_status__tmp397 != 0) {
            if (_status__tmp397 == 3) { *_err1 = _err2__tmp397; return 1; }
        }
        til_Array_delete(&_tmp398);
        *_err1 = til_AllocError_new(_tmp396);
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
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp414;
    if (til_I64_eq(til_Str_len(til_from), 0).data) {
        til_Str _ret__tmp416;
        til_AllocError _err0__tmp416 = {};
        int _status__tmp416 = til_Str_clone(&_ret__tmp416, &_err0__tmp416, til_self);
        if (_status__tmp416 == 1) { *_err1 = _err0__tmp416; return 1; }
        *_ret = _ret__tmp416;
        return 0;
    }
    if (til_I64_eq(til_n, 0).data) {
        til_Str _ret__tmp418;
        til_AllocError _err0__tmp418 = {};
        int _status__tmp418 = til_Str_clone(&_ret__tmp418, &_err0__tmp418, til_self);
        if (_status__tmp418 == 1) { *_err1 = _err0__tmp418; return 1; }
        *_ret = _ret__tmp418;
        return 0;
    }
    til_I64 til_idx = til_Str_find(til_self, til_from);
    if (til_lt(til_idx, 0).data) {
        til_Str _ret__tmp420;
        til_AllocError _err0__tmp420 = {};
        int _status__tmp420 = til_Str_clone(&_ret__tmp420, &_err0__tmp420, til_self);
        if (_status__tmp420 == 1) { *_err1 = _err0__tmp420; return 1; }
        *_ret = _ret__tmp420;
        return 0;
    }
    til_Str _ret__tmp421;
    til_Str til_prefix;
    til_IndexOutOfBoundsError _err0__tmp421 = {};
    til_AllocError _err1__tmp421 = {};
    int _status__tmp421 = til_get_substr(&_ret__tmp421, &_err0__tmp421, &_err1__tmp421, til_self, 0, til_idx);
    if (_status__tmp421 == 2) { *_err1 = _err1__tmp421; return 1; }
    til_prefix = _ret__tmp421;
    til_Str _ret__tmp422;
    til_Str til_suffix;
    til_IndexOutOfBoundsError _err0__tmp422 = {};
    til_AllocError _err1__tmp422 = {};
    int _status__tmp422 = til_get_substr(&_ret__tmp422, &_err0__tmp422, &_err1__tmp422, til_self, til_add(til_idx, til_Str_len(til_from)), til_Str_len(til_self));
    if (_status__tmp422 == 2) { *_err1 = _err1__tmp422; return 1; }
    til_suffix = _ret__tmp422;
    til_Str til_result = til_concat(til_concat(til_prefix, til_to), til_suffix);
    if (til_gt(til_n, 1).data) {
        til_Str _ret__tmp424;
        til_Str til_rest;
        til_AllocError _err0__tmp424 = {};
        int _status__tmp424 = til_Str_replacen(&_ret__tmp424, &_err0__tmp424, til_suffix, til_from, til_to, til_sub(til_n, 1));
        if (_status__tmp424 == 1) { *_err1 = _err0__tmp424; return 1; }
        til_rest = _ret__tmp424;
        til_result = til_concat(til_concat(til_prefix, til_to), til_rest);
    }
    *_ret = til_result;
    return 0;
    goto _end_catches__tmp414;
_catch_IndexOutOfBoundsError__tmp414: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp414;
    til_Str _ret__tmp426;
    til_AllocError _err0__tmp426 = {};
    int _status__tmp426 = til_Str_clone(&_ret__tmp426, &_err0__tmp426, til_self);
    if (_status__tmp426 == 1) { *_err1 = _err0__tmp426; return 1; }
    til_result = _ret__tmp426;
    }
_end_catches__tmp414:;
}

int til_Str_split(til_Vec* _ret, til_AllocError* _err1, til_IndexOutOfBoundsError* _err2, const til_Str til_self, const til_Str til_delimiter) {
    til_Vec _ret__tmp428;
    til_Vec til_parts;
    til_AllocError _err0__tmp428 = {};
    int _status__tmp428 = til_Vec_new(&_ret__tmp428, &_err0__tmp428, "Str");
    if (_status__tmp428 == 1) { *_err1 = _err0__tmp428; return 1; }
    til_parts = _ret__tmp428;
    if (til_I64_eq(til_Str_len(til_delimiter), 0).data) {
        til_Str _tmp431;
        til_AllocError _err0__tmp432;
        int _status__tmp432 = til_Str_clone(&_tmp431, &_err0__tmp432, til_self);
        if (_status__tmp432 != 0) {
            if (_status__tmp432 == 1) { *_err1 = _err0__tmp432; return 1; }
        }
        til_AllocError _err0__tmp430 = {};
        int _status__tmp430 = til_Vec_push(&_err0__tmp430, &til_parts, &_tmp431);
        if (_status__tmp430 == 1) { *_err1 = _err0__tmp430; return 1; }
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
                til_Str _ret__tmp439;
                til_Str til_part;
                til_IndexOutOfBoundsError _err0__tmp439 = {};
                til_AllocError _err1__tmp439 = {};
                int _status__tmp439 = til_get_substr(&_ret__tmp439, &_err0__tmp439, &_err1__tmp439, til_self, til_start, til_pos);
                if (_status__tmp439 == 1) { *_err2 = _err0__tmp439; return 2; }
                if (_status__tmp439 == 2) { *_err1 = _err1__tmp439; return 1; }
                til_part = _ret__tmp439;
                til_AllocError _err0__tmp440 = {};
                int _status__tmp440 = til_Vec_push(&_err0__tmp440, &til_parts, (til_Dynamic*)&til_part);
                if (_status__tmp440 == 1) { *_err1 = _err0__tmp440; return 1; }
            } else {
                til_Str _tmp443 = til_Str_from_literal("");
                til_AllocError _err0__tmp442 = {};
                int _status__tmp442 = til_Vec_push(&_err0__tmp442, &til_parts, &_tmp443);
                if (_status__tmp442 == 1) { *_err1 = _err0__tmp442; return 1; }
            }
            til_start = til_add(til_pos, til_Str_len(til_delimiter));
            til_pos = til_start;
        } else {
            til_pos = til_add(til_pos, 1);
        }
    }
    if (til_lt(til_start, til_Str_len(til_self)).data) {
        til_Str _ret__tmp446;
        til_Str til_part;
        til_IndexOutOfBoundsError _err0__tmp446 = {};
        til_AllocError _err1__tmp446 = {};
        int _status__tmp446 = til_get_substr(&_ret__tmp446, &_err0__tmp446, &_err1__tmp446, til_self, til_start, til_Str_len(til_self));
        if (_status__tmp446 == 1) { *_err2 = _err0__tmp446; return 2; }
        if (_status__tmp446 == 2) { *_err1 = _err1__tmp446; return 1; }
        til_part = _ret__tmp446;
        til_AllocError _err0__tmp447 = {};
        int _status__tmp447 = til_Vec_push(&_err0__tmp447, &til_parts, (til_Dynamic*)&til_part);
        if (_status__tmp447 == 1) { *_err1 = _err0__tmp447; return 1; }
    } else {
        if (til_I64_eq(til_start, til_Str_len(til_self)).data) {
            til_Str _tmp451 = til_Str_from_literal("");
            til_AllocError _err0__tmp450 = {};
            int _status__tmp450 = til_Vec_push(&_err0__tmp450, &til_parts, &_tmp451);
            if (_status__tmp450 == 1) { *_err1 = _err0__tmp450; return 1; }
        }
    }
    *_ret = til_parts;
    return 0;
}

til_U8_OverflowError til_U8_OverflowError_new(const til_Str til_msg) {
    til_U8_OverflowError til_err = {.msg = til_Str_from_literal("")};
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
    til_U8 _ret__tmp459;
    til_U8_OverflowError _err0__tmp459 = {};
    int _status__tmp459 = til_U8_from_i64(&_ret__tmp459, &_err0__tmp459, til_add(til_U8_to_i64(til_a), til_U8_to_i64(til_b)));
    if (_status__tmp459 == 1) { *_err1 = _err0__tmp459; return 1; }
    *_ret = _ret__tmp459;
    return 0;
}

int til_U8_from_i64(til_U8* _ret, til_U8_OverflowError* _err1, const til_I64 til_self) {
    if (til_lt(til_self, 0).data) {
        til_Str _tmp462;
        til_I64_OverflowError _err0__tmp463;
        til_IndexOutOfBoundsError _err1__tmp463;
        til_AllocError _err2__tmp463;
        til_Array _tmp464;
        til_AllocError _err_alloc__tmp465;
        til_IndexOutOfBoundsError _err_idx__tmp465;
        til_Str _tmp466 = til_Str_from_literal("Negative values cannot be cast into 'U8'");
        int _arr_status__tmp465 = til_Array_new(&_tmp464, &_err_alloc__tmp465, "Str", 1);
        if (_arr_status__tmp465 != 0) {
        }
        _arr_status__tmp465 = til_Array_set(&_err_idx__tmp465, &_tmp464, 0, &_tmp466);
        if (_arr_status__tmp465 != 0) {
        }
        int _status__tmp463 = til_format(&_tmp462, &_err0__tmp463, &_err1__tmp463, &_err2__tmp463, til_Str_from_literal("src/test/constfold.til:56:47:"), &_tmp464);
        if (_status__tmp463 != 0) {
        }
        til_Array_delete(&_tmp464);
        *_err1 = til_U8_OverflowError_new(_tmp462);
        return 1;
    }
    if (til_gt(til_self, til_MAX_U8).data) {
        til_Str _tmp468;
        til_I64_OverflowError _err0__tmp469;
        til_IndexOutOfBoundsError _err1__tmp469;
        til_AllocError _err2__tmp469;
        til_Array _tmp470;
        til_AllocError _err_alloc__tmp471;
        til_IndexOutOfBoundsError _err_idx__tmp471;
        til_Str _tmp472 = til_Str_from_literal("U8: cannot be casted from an I64 greater than: ");
        til_Str _tmp473 = til_I64_to_str(til_MAX_U8);
        int _arr_status__tmp471 = til_Array_new(&_tmp470, &_err_alloc__tmp471, "Str", 2);
        if (_arr_status__tmp471 != 0) {
        }
        _arr_status__tmp471 = til_Array_set(&_err_idx__tmp471, &_tmp470, 0, &_tmp472);
        if (_arr_status__tmp471 != 0) {
        }
        _arr_status__tmp471 = til_Array_set(&_err_idx__tmp471, &_tmp470, 1, &_tmp473);
        if (_arr_status__tmp471 != 0) {
        }
        int _status__tmp469 = til_format(&_tmp468, &_err0__tmp469, &_err1__tmp469, &_err2__tmp469, til_Str_from_literal("src/test/constfold.til:59:47:"), &_tmp470);
        if (_status__tmp469 != 0) {
        }
        til_Array_delete(&_tmp470);
        *_err1 = til_U8_OverflowError_new(_tmp468);
        return 1;
    }
    *_ret = til_i64_to_u8(til_self);
    return 0;
}

til_Str til_U8_to_str(const til_U8 til_self) {
    return til_I64_to_str(til_U8_to_i64(til_self));
}

int til_U8_from_str(til_U8* _ret, til_U8_OverflowError* _err1, const til_Str til_s) {
    til_U8 _ret__tmp476;
    til_U8_OverflowError _err0__tmp476 = {};
    int _status__tmp476 = til_U8_from_i64(&_ret__tmp476, &_err0__tmp476, til_I64_from_str(til_s));
    if (_status__tmp476 == 1) { *_err1 = _err0__tmp476; return 1; }
    *_ret = _ret__tmp476;
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
