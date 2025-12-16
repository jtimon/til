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
const til_I64 til_Vec_MAX_CAP = 1048576;
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
    til_I64 _for_i_3 = 0;
    til_Bool til_val;
    while (til_lt(_for_i_3, til_Array_len((*til_args))).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp0;
        til_val = (til_Bool){.data = 0};
        til_IndexOutOfBoundsError _err0__tmp1 = {};
        int _status__tmp1 = til_Array_get(&_err0__tmp1, (*til_args), _for_i_3, (til_Dynamic*)&til_val);
        if (_status__tmp1 == 1) { _thrown_IndexOutOfBoundsError__tmp0 = _err0__tmp1; goto _catch_IndexOutOfBoundsError__tmp0; }
        if (0) { _catch_IndexOutOfBoundsError__tmp0:
            til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp0;
            til_Array _tmp2;
            til_AllocError _err_alloc__tmp3;
            til_IndexOutOfBoundsError _err_idx__tmp3;
            til_Str _tmp4 = til_err.msg;
            int _arr_status__tmp3 = til_Array_new(&_tmp2, &_err_alloc__tmp3, "Str", 1);
            if (_arr_status__tmp3 != 0) {
            }
            _arr_status__tmp3 = til_Array_set(&_err_idx__tmp3, &_tmp2, 0, &_tmp4);
            if (_arr_status__tmp3 != 0) {
            }
            til_panic(((til_Str){(til_I64)"src/core/bool.til:74:5:", 23}), &_tmp2);
            til_Array_delete(&_tmp2);
        }
        if (til_val.data) {
            return true;
        }
        _for_i_3 = til_add(_for_i_3, 1);
    }
    return false;
}

til_Bool til_and(til_Array* til_args) {
    til_I64 _for_i_4 = 0;
    til_Bool til_val;
    while (til_lt(_for_i_4, til_Array_len((*til_args))).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp5;
        til_val = (til_Bool){.data = 0};
        til_IndexOutOfBoundsError _err0__tmp6 = {};
        int _status__tmp6 = til_Array_get(&_err0__tmp6, (*til_args), _for_i_4, (til_Dynamic*)&til_val);
        if (_status__tmp6 == 1) { _thrown_IndexOutOfBoundsError__tmp5 = _err0__tmp6; goto _catch_IndexOutOfBoundsError__tmp5; }
        if (0) { _catch_IndexOutOfBoundsError__tmp5:
            til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp5;
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
            til_panic(((til_Str){(til_I64)"src/core/bool.til:83:5:", 23}), &_tmp7);
            til_Array_delete(&_tmp7);
        }
        if (til_not(til_val).data) {
            return false;
        }
        _for_i_4 = til_add(_for_i_4, 1);
    }
    return true;
}

void til_panic(const til_Str til_loc_str, til_Array* til_msgs) {
    til_single_print(til_loc_str);
    til_I64 _for_i_5 = 0;
    til_Str til_val;
    while (til_lt(_for_i_5, til_Array_len((*til_msgs))).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp10;
        til_val = (til_Str){.c_string = 0, .cap = 0};
        til_IndexOutOfBoundsError _err0__tmp11 = {};
        int _status__tmp11 = til_Array_get(&_err0__tmp11, (*til_msgs), _for_i_5, (til_Dynamic*)&til_val);
        if (_status__tmp11 == 1) { _thrown_IndexOutOfBoundsError__tmp10 = _err0__tmp11; goto _catch_IndexOutOfBoundsError__tmp10; }
        if (0) { _catch_IndexOutOfBoundsError__tmp10:
            til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp10;
            til_Array _tmp12;
            til_AllocError _err_alloc__tmp13;
            til_IndexOutOfBoundsError _err_idx__tmp13;
            til_Str _tmp14 = til_err.msg;
            int _arr_status__tmp13 = til_Array_new(&_tmp12, &_err_alloc__tmp13, "Str", 1);
            if (_arr_status__tmp13 != 0) {
            }
            _arr_status__tmp13 = til_Array_set(&_err_idx__tmp13, &_tmp12, 0, &_tmp14);
            if (_arr_status__tmp13 != 0) {
            }
            til_panic(((til_Str){(til_I64)"src/core/exit.til:9:5:", 22}), &_tmp12);
            til_Array_delete(&_tmp12);
        }
        til_single_print(til_val);
        _for_i_5 = til_add(_for_i_5, 1);
    }
    til_single_print(((til_Str){(til_I64)"\n", 1}));
    til_print_flush();
    til_exit(1);
}

void til_assertm(const til_Str til_loc_str, const til_Bool til_cond, const til_Str til_msg) {
    if (til_not(til_cond).data) {
        til_Str _tmp15;
        til_I64_OverflowError _err0__tmp16;
        til_IndexOutOfBoundsError _err1__tmp16;
        til_AllocError _err2__tmp16;
        til_Array _tmp17;
        til_AllocError _err_alloc__tmp18;
        til_IndexOutOfBoundsError _err_idx__tmp18;
        til_Str _tmp19 = til_msg;
        int _arr_status__tmp18 = til_Array_new(&_tmp17, &_err_alloc__tmp18, "Str", 1);
        if (_arr_status__tmp18 != 0) {
        }
        _arr_status__tmp18 = til_Array_set(&_err_idx__tmp18, &_tmp17, 0, &_tmp19);
        if (_arr_status__tmp18 != 0) {
        }
        int _status__tmp16 = til_format(&_tmp15, &_err0__tmp16, &_err1__tmp16, &_err2__tmp16, ((til_Str){(til_I64)"assert failed: ", 15}), &_tmp17);
        if (_status__tmp16 != 0) {
        }
        til_Array_delete(&_tmp17);
        til_Array _tmp20;
        til_AllocError _err_alloc__tmp21;
        til_IndexOutOfBoundsError _err_idx__tmp21;
        int _arr_status__tmp21 = til_Array_new(&_tmp20, &_err_alloc__tmp21, "Str", 1);
        if (_arr_status__tmp21 != 0) {
        }
        _arr_status__tmp21 = til_Array_set(&_err_idx__tmp21, &_tmp20, 0, &_tmp15);
        if (_arr_status__tmp21 != 0) {
        }
        til_panic(til_loc_str, &_tmp20);
        til_Array_delete(&_tmp20);
    }
}

void til_println(til_Array* til_args) {
    til_I64 _for_i_7 = 0;
    til_Str til_val;
    while (til_lt(_for_i_7, til_Array_len((*til_args))).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp22;
        til_val = (til_Str){.c_string = 0, .cap = 0};
        til_IndexOutOfBoundsError _err0__tmp23 = {};
        int _status__tmp23 = til_Array_get(&_err0__tmp23, (*til_args), _for_i_7, (til_Dynamic*)&til_val);
        if (_status__tmp23 == 1) { _thrown_IndexOutOfBoundsError__tmp22 = _err0__tmp23; goto _catch_IndexOutOfBoundsError__tmp22; }
        if (0) { _catch_IndexOutOfBoundsError__tmp22:
            til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp22;
            til_Array _tmp24;
            til_AllocError _err_alloc__tmp25;
            til_IndexOutOfBoundsError _err_idx__tmp25;
            til_Str _tmp26 = til_err.msg;
            int _arr_status__tmp25 = til_Array_new(&_tmp24, &_err_alloc__tmp25, "Str", 1);
            if (_arr_status__tmp25 != 0) {
            }
            _arr_status__tmp25 = til_Array_set(&_err_idx__tmp25, &_tmp24, 0, &_tmp26);
            if (_arr_status__tmp25 != 0) {
            }
            til_panic(((til_Str){(til_I64)"src/core/print.til:16:5:", 24}), &_tmp24);
            til_Array_delete(&_tmp24);
        }
        til_single_print(til_val);
        _for_i_7 = til_add(_for_i_7, 1);
    }
    til_single_print(((til_Str){(til_I64)"\n", 1}));
    til_print_flush();
}

int til_get_substr(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_start, const til_I64 til_end) {
    if (til_lt(til_start, 0).data) {
        til_Str _tmp27;
        til_I64_OverflowError _err0__tmp28;
        til_IndexOutOfBoundsError _err1__tmp28;
        til_AllocError _err2__tmp28;
        til_Array _tmp29;
        til_AllocError _err_alloc__tmp30;
        til_IndexOutOfBoundsError _err_idx__tmp30;
        til_Str _tmp31 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp32 = til_I64_to_str(til_start);
        til_Str _tmp33 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp30 = til_Array_new(&_tmp29, &_err_alloc__tmp30, "Str", 3);
        if (_arr_status__tmp30 != 0) {
            *_err2 = _err_alloc__tmp30; return 2;
        }
        _arr_status__tmp30 = til_Array_set(&_err_idx__tmp30, &_tmp29, 0, &_tmp31);
        if (_arr_status__tmp30 != 0) {
            *_err1 = _err_idx__tmp30; return 1;
        }
        _arr_status__tmp30 = til_Array_set(&_err_idx__tmp30, &_tmp29, 1, &_tmp32);
        if (_arr_status__tmp30 != 0) {
            *_err1 = _err_idx__tmp30; return 1;
        }
        _arr_status__tmp30 = til_Array_set(&_err_idx__tmp30, &_tmp29, 2, &_tmp33);
        if (_arr_status__tmp30 != 0) {
            *_err1 = _err_idx__tmp30; return 1;
        }
        int _status__tmp28 = til_format(&_tmp27, &_err0__tmp28, &_err1__tmp28, &_err2__tmp28, ((til_Str){(til_I64)"src/core/str.til:368:48:", 24}), &_tmp29);
        if (_status__tmp28 != 0) {
            if (_status__tmp28 == 2) { *_err1 = _err1__tmp28; return 1; }
            if (_status__tmp28 == 3) { *_err2 = _err2__tmp28; return 2; }
        }
        til_Array_delete(&_tmp29);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp27};
        return 1;
    }
    if (til_lt(til_end, 0).data) {
        til_Str _tmp34;
        til_I64_OverflowError _err0__tmp35;
        til_IndexOutOfBoundsError _err1__tmp35;
        til_AllocError _err2__tmp35;
        til_Array _tmp36;
        til_AllocError _err_alloc__tmp37;
        til_IndexOutOfBoundsError _err_idx__tmp37;
        til_Str _tmp38 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp39 = til_I64_to_str(til_end);
        til_Str _tmp40 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp37 = til_Array_new(&_tmp36, &_err_alloc__tmp37, "Str", 3);
        if (_arr_status__tmp37 != 0) {
            *_err2 = _err_alloc__tmp37; return 2;
        }
        _arr_status__tmp37 = til_Array_set(&_err_idx__tmp37, &_tmp36, 0, &_tmp38);
        if (_arr_status__tmp37 != 0) {
            *_err1 = _err_idx__tmp37; return 1;
        }
        _arr_status__tmp37 = til_Array_set(&_err_idx__tmp37, &_tmp36, 1, &_tmp39);
        if (_arr_status__tmp37 != 0) {
            *_err1 = _err_idx__tmp37; return 1;
        }
        _arr_status__tmp37 = til_Array_set(&_err_idx__tmp37, &_tmp36, 2, &_tmp40);
        if (_arr_status__tmp37 != 0) {
            *_err1 = _err_idx__tmp37; return 1;
        }
        int _status__tmp35 = til_format(&_tmp34, &_err0__tmp35, &_err1__tmp35, &_err2__tmp35, ((til_Str){(til_I64)"src/core/str.til:371:48:", 24}), &_tmp36);
        if (_status__tmp35 != 0) {
            if (_status__tmp35 == 2) { *_err1 = _err1__tmp35; return 1; }
            if (_status__tmp35 == 3) { *_err2 = _err2__tmp35; return 2; }
        }
        til_Array_delete(&_tmp36);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp34};
        return 1;
    }
    if (til_gt(til_start, til_end).data) {
        til_Str _tmp41;
        til_I64_OverflowError _err0__tmp42;
        til_IndexOutOfBoundsError _err1__tmp42;
        til_AllocError _err2__tmp42;
        til_Array _tmp43;
        til_AllocError _err_alloc__tmp44;
        til_IndexOutOfBoundsError _err_idx__tmp44;
        til_Str _tmp45 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp46 = til_I64_to_str(til_start);
        til_Str _tmp47 = ((til_Str){(til_I64)" is greater than end index ", 27});
        til_Str _tmp48 = til_I64_to_str(til_end);
        int _arr_status__tmp44 = til_Array_new(&_tmp43, &_err_alloc__tmp44, "Str", 4);
        if (_arr_status__tmp44 != 0) {
            *_err2 = _err_alloc__tmp44; return 2;
        }
        _arr_status__tmp44 = til_Array_set(&_err_idx__tmp44, &_tmp43, 0, &_tmp45);
        if (_arr_status__tmp44 != 0) {
            *_err1 = _err_idx__tmp44; return 1;
        }
        _arr_status__tmp44 = til_Array_set(&_err_idx__tmp44, &_tmp43, 1, &_tmp46);
        if (_arr_status__tmp44 != 0) {
            *_err1 = _err_idx__tmp44; return 1;
        }
        _arr_status__tmp44 = til_Array_set(&_err_idx__tmp44, &_tmp43, 2, &_tmp47);
        if (_arr_status__tmp44 != 0) {
            *_err1 = _err_idx__tmp44; return 1;
        }
        _arr_status__tmp44 = til_Array_set(&_err_idx__tmp44, &_tmp43, 3, &_tmp48);
        if (_arr_status__tmp44 != 0) {
            *_err1 = _err_idx__tmp44; return 1;
        }
        int _status__tmp42 = til_format(&_tmp41, &_err0__tmp42, &_err1__tmp42, &_err2__tmp42, ((til_Str){(til_I64)"src/core/str.til:374:48:", 24}), &_tmp43);
        if (_status__tmp42 != 0) {
            if (_status__tmp42 == 2) { *_err1 = _err1__tmp42; return 1; }
            if (_status__tmp42 == 3) { *_err2 = _err2__tmp42; return 2; }
        }
        til_Array_delete(&_tmp43);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp41};
        return 1;
    }
    if (til_gt(til_end, til_Str_len(til_s)).data) {
        til_Str _tmp49;
        til_I64_OverflowError _err0__tmp50;
        til_IndexOutOfBoundsError _err1__tmp50;
        til_AllocError _err2__tmp50;
        til_Array _tmp51;
        til_AllocError _err_alloc__tmp52;
        til_IndexOutOfBoundsError _err_idx__tmp52;
        til_Str _tmp53 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp54 = til_I64_to_str(til_end);
        til_Str _tmp55 = ((til_Str){(til_I64)" is greater than string length ", 31});
        til_Str _tmp56 = til_I64_to_str(til_Str_len(til_s));
        int _arr_status__tmp52 = til_Array_new(&_tmp51, &_err_alloc__tmp52, "Str", 4);
        if (_arr_status__tmp52 != 0) {
            *_err2 = _err_alloc__tmp52; return 2;
        }
        _arr_status__tmp52 = til_Array_set(&_err_idx__tmp52, &_tmp51, 0, &_tmp53);
        if (_arr_status__tmp52 != 0) {
            *_err1 = _err_idx__tmp52; return 1;
        }
        _arr_status__tmp52 = til_Array_set(&_err_idx__tmp52, &_tmp51, 1, &_tmp54);
        if (_arr_status__tmp52 != 0) {
            *_err1 = _err_idx__tmp52; return 1;
        }
        _arr_status__tmp52 = til_Array_set(&_err_idx__tmp52, &_tmp51, 2, &_tmp55);
        if (_arr_status__tmp52 != 0) {
            *_err1 = _err_idx__tmp52; return 1;
        }
        _arr_status__tmp52 = til_Array_set(&_err_idx__tmp52, &_tmp51, 3, &_tmp56);
        if (_arr_status__tmp52 != 0) {
            *_err1 = _err_idx__tmp52; return 1;
        }
        int _status__tmp50 = til_format(&_tmp49, &_err0__tmp50, &_err1__tmp50, &_err2__tmp50, ((til_Str){(til_I64)"src/core/str.til:377:48:", 24}), &_tmp51);
        if (_status__tmp50 != 0) {
            if (_status__tmp50 == 2) { *_err1 = _err1__tmp50; return 1; }
            if (_status__tmp50 == 3) { *_err2 = _err2__tmp50; return 2; }
        }
        til_Array_delete(&_tmp51);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp49};
        return 1;
    }
    if (til_I64_eq(til_start, til_end).data) {
        til_Str _tmp57;
        til_I64_OverflowError _err0__tmp58;
        til_IndexOutOfBoundsError _err1__tmp58;
        til_AllocError _err2__tmp58;
        til_Array _tmp59;
        til_AllocError _err_alloc__tmp60;
        til_IndexOutOfBoundsError _err_idx__tmp60;
        til_Str _tmp61 = ((til_Str){(til_I64)"get_substr: start and end are the same (", 40});
        til_Str _tmp62 = til_I64_to_str(til_start);
        til_Str _tmp63 = ((til_Str){(til_I64)"), no substring", 15});
        int _arr_status__tmp60 = til_Array_new(&_tmp59, &_err_alloc__tmp60, "Str", 3);
        if (_arr_status__tmp60 != 0) {
            *_err2 = _err_alloc__tmp60; return 2;
        }
        _arr_status__tmp60 = til_Array_set(&_err_idx__tmp60, &_tmp59, 0, &_tmp61);
        if (_arr_status__tmp60 != 0) {
            *_err1 = _err_idx__tmp60; return 1;
        }
        _arr_status__tmp60 = til_Array_set(&_err_idx__tmp60, &_tmp59, 1, &_tmp62);
        if (_arr_status__tmp60 != 0) {
            *_err1 = _err_idx__tmp60; return 1;
        }
        _arr_status__tmp60 = til_Array_set(&_err_idx__tmp60, &_tmp59, 2, &_tmp63);
        if (_arr_status__tmp60 != 0) {
            *_err1 = _err_idx__tmp60; return 1;
        }
        int _status__tmp58 = til_format(&_tmp57, &_err0__tmp58, &_err1__tmp58, &_err2__tmp58, ((til_Str){(til_I64)"src/core/str.til:380:48:", 24}), &_tmp59);
        if (_status__tmp58 != 0) {
            if (_status__tmp58 == 2) { *_err1 = _err1__tmp58; return 1; }
            if (_status__tmp58 == 3) { *_err2 = _err2__tmp58; return 2; }
        }
        til_Array_delete(&_tmp59);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp57};
        return 1;
    }
    til_Str til_substr = {.c_string = 0, .cap = 0};
    til_substr.cap = til_sub(til_end, til_start);
    til_I64 _ret__tmp64;
    til_AllocError _err0__tmp64 = {};
    int _status__tmp64 = til_malloc(&_ret__tmp64, &_err0__tmp64, til_add(til_substr.cap, 1));
    if (_status__tmp64 == 1) { *_err2 = _err0__tmp64; return 2; }
    til_substr.c_string = _ret__tmp64;
    if (til_I64_eq(til_NULL, til_substr.c_string).data) {
        til_Str _tmp65;
        til_I64_OverflowError _err0__tmp66;
        til_IndexOutOfBoundsError _err1__tmp66;
        til_AllocError _err2__tmp66;
        til_Array _tmp67;
        til_AllocError _err_alloc__tmp68;
        til_IndexOutOfBoundsError _err_idx__tmp68;
        til_Str _tmp69 = ((til_Str){(til_I64)"Str.get_substr: failed to allocate ", 35});
        til_Str _tmp70 = til_I64_to_str(til_add(til_substr.cap, 1));
        til_Str _tmp71 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp68 = til_Array_new(&_tmp67, &_err_alloc__tmp68, "Str", 3);
        if (_arr_status__tmp68 != 0) {
            *_err2 = _err_alloc__tmp68; return 2;
        }
        _arr_status__tmp68 = til_Array_set(&_err_idx__tmp68, &_tmp67, 0, &_tmp69);
        if (_arr_status__tmp68 != 0) {
            *_err1 = _err_idx__tmp68; return 1;
        }
        _arr_status__tmp68 = til_Array_set(&_err_idx__tmp68, &_tmp67, 1, &_tmp70);
        if (_arr_status__tmp68 != 0) {
            *_err1 = _err_idx__tmp68; return 1;
        }
        _arr_status__tmp68 = til_Array_set(&_err_idx__tmp68, &_tmp67, 2, &_tmp71);
        if (_arr_status__tmp68 != 0) {
            *_err1 = _err_idx__tmp68; return 1;
        }
        int _status__tmp66 = til_format(&_tmp65, &_err0__tmp66, &_err1__tmp66, &_err2__tmp66, ((til_Str){(til_I64)"src/core/str.til:387:37:", 24}), &_tmp67);
        if (_status__tmp66 != 0) {
            if (_status__tmp66 == 2) { *_err1 = _err1__tmp66; return 1; }
            if (_status__tmp66 == 3) { *_err2 = _err2__tmp66; return 2; }
        }
        til_Array_delete(&_tmp67);
        *_err2 = (til_AllocError){.msg = _tmp65};
        return 2;
    }
    til_memcpy(til_substr.c_string, til_add(til_s.c_string, til_start), til_substr.cap);
    const til_I64 til_zero = 0;
    til_memset(til_add(til_substr.c_string, til_substr.cap), til_zero, 1);
    *_ret = til_substr;
    return 0;
}

til_Str til_concat(const til_Str til_a, const til_Str til_b) {
    til_AllocError _thrown_AllocError__tmp72;
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_add(til_a.cap, til_b.cap);
    if (til_lt(til_result.cap, til_a.cap).data) {
        til_Array _tmp73;
        til_AllocError _err_alloc__tmp74;
        til_IndexOutOfBoundsError _err_idx__tmp74;
        til_Str _tmp75 = ((til_Str){(til_I64)"concat: integer overflow", 24});
        int _arr_status__tmp74 = til_Array_new(&_tmp73, &_err_alloc__tmp74, "Str", 1);
        if (_arr_status__tmp74 != 0) {
        }
        _arr_status__tmp74 = til_Array_set(&_err_idx__tmp74, &_tmp73, 0, &_tmp75);
        if (_arr_status__tmp74 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:450:15:", 24}), &_tmp73);
        til_Array_delete(&_tmp73);
    }
    til_I64 _ret__tmp76;
    til_AllocError _err0__tmp76 = {};
    int _status__tmp76 = til_malloc(&_ret__tmp76, &_err0__tmp76, til_result.cap);
    if (_status__tmp76 == 1) { _thrown_AllocError__tmp72 = _err0__tmp76; goto _catch_AllocError__tmp72; }
    til_result.c_string = _ret__tmp76;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Array _tmp77;
        til_AllocError _err_alloc__tmp78;
        til_IndexOutOfBoundsError _err_idx__tmp78;
        til_Str _tmp79 = ((til_Str){(til_I64)"concat: malloc failed", 21});
        int _arr_status__tmp78 = til_Array_new(&_tmp77, &_err_alloc__tmp78, "Str", 1);
        if (_arr_status__tmp78 != 0) {
        }
        _arr_status__tmp78 = til_Array_set(&_err_idx__tmp78, &_tmp77, 0, &_tmp79);
        if (_arr_status__tmp78 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:455:15:", 24}), &_tmp77);
        til_Array_delete(&_tmp77);
    }
    til_memcpy(til_result.c_string, til_a.c_string, til_a.cap);
    til_memcpy(til_add(til_result.c_string, til_a.cap), til_b.c_string, til_b.cap);
    if (0) { _catch_AllocError__tmp72:
        til_AllocError til_err = _thrown_AllocError__tmp72;
        til_Array _tmp80;
        til_AllocError _err_alloc__tmp81;
        til_IndexOutOfBoundsError _err_idx__tmp81;
        til_Str _tmp82 = til_err.msg;
        int _arr_status__tmp81 = til_Array_new(&_tmp80, &_err_alloc__tmp81, "Str", 1);
        if (_arr_status__tmp81 != 0) {
        }
        _arr_status__tmp81 = til_Array_set(&_err_idx__tmp81, &_tmp80, 0, &_tmp82);
        if (_arr_status__tmp81 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:462:15:", 24}), &_tmp80);
        til_Array_delete(&_tmp80);
    }
    return til_result;
}

int til_format(til_Str* _ret, til_I64_OverflowError* _err1, til_IndexOutOfBoundsError* _err2, til_AllocError* _err3, const til_Str til_prefix, til_Array* til_args) {
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_prefix.cap;
    til_I64 til_i = 0;
    til_Str til_arg;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_arg = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp83 = {};
        int _status__tmp83 = til_Array_get(&_err0__tmp83, (*til_args), til_i, (til_Dynamic*)&til_arg);
        if (_status__tmp83 == 1) { *_err2 = _err0__tmp83; return 2; }
        til_result.cap = til_add(til_result.cap, til_arg.cap);
        if (til_lt(til_result.cap, til_arg.cap).data) {
            til_Str _tmp84;
            til_I64_OverflowError _err0__tmp85;
            til_IndexOutOfBoundsError _err1__tmp85;
            til_AllocError _err2__tmp85;
            til_Array _tmp86;
            til_AllocError _err_alloc__tmp87;
            til_IndexOutOfBoundsError _err_idx__tmp87;
            til_Str _tmp88 = ((til_Str){(til_I64)"format: integer overflow while summing cap for arg ", 51});
            til_Str _tmp89 = til_I64_to_str(til_i);
            int _arr_status__tmp87 = til_Array_new(&_tmp86, &_err_alloc__tmp87, "Str", 2);
            if (_arr_status__tmp87 != 0) {
                *_err3 = _err_alloc__tmp87; return 3;
            }
            _arr_status__tmp87 = til_Array_set(&_err_idx__tmp87, &_tmp86, 0, &_tmp88);
            if (_arr_status__tmp87 != 0) {
                *_err2 = _err_idx__tmp87; return 2;
            }
            _arr_status__tmp87 = til_Array_set(&_err_idx__tmp87, &_tmp86, 1, &_tmp89);
            if (_arr_status__tmp87 != 0) {
                *_err2 = _err_idx__tmp87; return 2;
            }
            int _status__tmp85 = til_format(&_tmp84, &_err0__tmp85, &_err1__tmp85, &_err2__tmp85, ((til_Str){(til_I64)"src/core/str.til:478:48:", 24}), &_tmp86);
            if (_status__tmp85 != 0) {
                if (_status__tmp85 == 1) { *_err1 = _err0__tmp85; return 1; }
                if (_status__tmp85 == 2) { *_err2 = _err1__tmp85; return 2; }
                if (_status__tmp85 == 3) { *_err3 = _err2__tmp85; return 3; }
            }
            til_Array_delete(&_tmp86);
            *_err1 = (til_I64_OverflowError){.msg = _tmp84};
            return 1;
        }
        til_I64_inc(&til_i);
    }
    til_I64 _ret__tmp90;
    til_AllocError _err0__tmp90 = {};
    int _status__tmp90 = til_malloc(&_ret__tmp90, &_err0__tmp90, til_result.cap);
    if (_status__tmp90 == 1) { *_err3 = _err0__tmp90; return 3; }
    til_result.c_string = _ret__tmp90;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Str _tmp91;
        til_I64_OverflowError _err0__tmp92;
        til_IndexOutOfBoundsError _err1__tmp92;
        til_AllocError _err2__tmp92;
        til_Array _tmp93;
        til_AllocError _err_alloc__tmp94;
        til_IndexOutOfBoundsError _err_idx__tmp94;
        til_Str _tmp95 = ((til_Str){(til_I64)"format: malloc failed for cap = ", 32});
        til_Str _tmp96 = til_I64_to_str(til_result.cap);
        int _arr_status__tmp94 = til_Array_new(&_tmp93, &_err_alloc__tmp94, "Str", 2);
        if (_arr_status__tmp94 != 0) {
            *_err3 = _err_alloc__tmp94; return 3;
        }
        _arr_status__tmp94 = til_Array_set(&_err_idx__tmp94, &_tmp93, 0, &_tmp95);
        if (_arr_status__tmp94 != 0) {
            *_err2 = _err_idx__tmp94; return 2;
        }
        _arr_status__tmp94 = til_Array_set(&_err_idx__tmp94, &_tmp93, 1, &_tmp96);
        if (_arr_status__tmp94 != 0) {
            *_err2 = _err_idx__tmp94; return 2;
        }
        int _status__tmp92 = til_format(&_tmp91, &_err0__tmp92, &_err1__tmp92, &_err2__tmp92, ((til_Str){(til_I64)"src/core/str.til:484:37:", 24}), &_tmp93);
        if (_status__tmp92 != 0) {
            if (_status__tmp92 == 1) { *_err1 = _err0__tmp92; return 1; }
            if (_status__tmp92 == 2) { *_err2 = _err1__tmp92; return 2; }
            if (_status__tmp92 == 3) { *_err3 = _err2__tmp92; return 3; }
        }
        til_Array_delete(&_tmp93);
        *_err3 = (til_AllocError){.msg = _tmp91};
        return 3;
    }
    til_I64 til_offset = 0;
    til_memcpy(til_result.c_string, til_prefix.c_string, til_prefix.cap);
    til_offset = til_prefix.cap;
    til_I64 _for_i_8 = 0;
    til_Str til_s;
    while (til_lt(_for_i_8, til_Array_len((*til_args))).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp97;
        til_s = (til_Str){.c_string = 0, .cap = 0};
        til_IndexOutOfBoundsError _err0__tmp98 = {};
        int _status__tmp98 = til_Array_get(&_err0__tmp98, (*til_args), _for_i_8, (til_Dynamic*)&til_s);
        if (_status__tmp98 == 1) { _thrown_IndexOutOfBoundsError__tmp97 = _err0__tmp98; goto _catch_IndexOutOfBoundsError__tmp97; }
        if (0) { _catch_IndexOutOfBoundsError__tmp97:
            til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp97;
            til_Array _tmp99;
            til_AllocError _err_alloc__tmp100;
            til_IndexOutOfBoundsError _err_idx__tmp100;
            til_Str _tmp101 = til_err.msg;
            int _arr_status__tmp100 = til_Array_new(&_tmp99, &_err_alloc__tmp100, "Str", 1);
            if (_arr_status__tmp100 != 0) {
                *_err3 = _err_alloc__tmp100; return 3;
            }
            _arr_status__tmp100 = til_Array_set(&_err_idx__tmp100, &_tmp99, 0, &_tmp101);
            if (_arr_status__tmp100 != 0) {
                *_err2 = _err_idx__tmp100; return 2;
            }
            til_panic(((til_Str){(til_I64)"src/core/str.til:491:5:", 23}), &_tmp99);
            til_Array_delete(&_tmp99);
        }
        til_memcpy(til_add(til_result.c_string, til_offset), til_s.c_string, til_s.cap);
        til_offset = til_add(til_offset, til_s.cap);
        _for_i_8 = til_add(_for_i_8, 1);
    }
    *_ret = til_result;
    return 0;
}

void til_test(const til_Str til_loc_str, const til_Bool til_cond, const til_Str til_msg) {
    til_assertm(til_loc_str, til_cond, til_msg);
}

void til_assert_eq(const til_Str til_loc_str, const til_I64 til_a, const til_I64 til_b) {
    if (til_not(til_I64_eq(til_a, til_b)).data) {
        til_Array _tmp102;
        til_AllocError _err_alloc__tmp103;
        til_IndexOutOfBoundsError _err_idx__tmp103;
        til_Str _tmp104 = til_loc_str;
        til_Str _tmp105 = ((til_Str){(til_I64)"assert_eq failed: expected '", 28});
        til_Str _tmp106 = til_I64_to_str(til_a);
        til_Str _tmp107 = ((til_Str){(til_I64)"', found '", 10});
        til_Str _tmp108 = til_I64_to_str(til_b);
        til_Str _tmp109 = ((til_Str){(til_I64)"'", 1});
        int _arr_status__tmp103 = til_Array_new(&_tmp102, &_err_alloc__tmp103, "Str", 6);
        if (_arr_status__tmp103 != 0) {
        }
        _arr_status__tmp103 = til_Array_set(&_err_idx__tmp103, &_tmp102, 0, &_tmp104);
        if (_arr_status__tmp103 != 0) {
        }
        _arr_status__tmp103 = til_Array_set(&_err_idx__tmp103, &_tmp102, 1, &_tmp105);
        if (_arr_status__tmp103 != 0) {
        }
        _arr_status__tmp103 = til_Array_set(&_err_idx__tmp103, &_tmp102, 2, &_tmp106);
        if (_arr_status__tmp103 != 0) {
        }
        _arr_status__tmp103 = til_Array_set(&_err_idx__tmp103, &_tmp102, 3, &_tmp107);
        if (_arr_status__tmp103 != 0) {
        }
        _arr_status__tmp103 = til_Array_set(&_err_idx__tmp103, &_tmp102, 4, &_tmp108);
        if (_arr_status__tmp103 != 0) {
        }
        _arr_status__tmp103 = til_Array_set(&_err_idx__tmp103, &_tmp102, 5, &_tmp109);
        if (_arr_status__tmp103 != 0) {
        }
        til_println(&_tmp102);
        til_Array_delete(&_tmp102);
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
    til_arr.type_name = ((til_Str){(til_I64)til_T, strlen(til_T)});
    til_arr.type_size = til_size_of(((til_Str){(til_I64)til_T, strlen(til_T)}));
    const til_I64 til_size_bytes = til_mul(til_capacity, til_arr.type_size);
    til_I64 _ret__tmp110;
    til_AllocError _err0__tmp110 = {};
    int _status__tmp110 = til_malloc(&_ret__tmp110, &_err0__tmp110, til_size_bytes);
    if (_status__tmp110 == 1) { *_err1 = _err0__tmp110; return 1; }
    til_arr.ptr = _ret__tmp110;
    til_U8 _tmp111;
    til_U8_OverflowError _err0__tmp112;
    int _status__tmp112 = til_U8_from_i64(&_tmp111, &_err0__tmp112, 0);
    if (_status__tmp112 != 0) {
    }
    til_memset(til_arr.ptr, _tmp111, til_size_bytes);
    til_arr._len = til_capacity;
    *_ret = til_arr;
    return 0;
}

int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array til_self, const til_I64 til_index, til_Dynamic* til_T) {
    if (til_I64_gteq(til_index, til_self._len).data) {
        til_Str _tmp113;
        til_I64_OverflowError _err0__tmp114;
        til_IndexOutOfBoundsError _err1__tmp114;
        til_AllocError _err2__tmp114;
        til_Array _tmp115;
        til_AllocError _err_alloc__tmp116;
        til_IndexOutOfBoundsError _err_idx__tmp116;
        til_Str _tmp117 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        int _arr_status__tmp116 = til_Array_new(&_tmp115, &_err_alloc__tmp116, "Str", 1);
        if (_arr_status__tmp116 != 0) {
        }
        _arr_status__tmp116 = til_Array_set(&_err_idx__tmp116, &_tmp115, 0, &_tmp117);
        if (_arr_status__tmp116 != 0) {
            *_err1 = _err_idx__tmp116; return 1;
        }
        int _status__tmp114 = til_format(&_tmp113, &_err0__tmp114, &_err1__tmp114, &_err2__tmp114, ((til_Str){(til_I64)"src/core/array.til:41:52:", 25}), &_tmp115);
        if (_status__tmp114 != 0) {
            if (_status__tmp114 == 2) { *_err1 = _err1__tmp114; return 1; }
        }
        til_Array_delete(&_tmp115);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp113};
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_I64_gteq(til_index, til_self->_len).data) {
        til_Str _tmp118;
        til_I64_OverflowError _err0__tmp119;
        til_IndexOutOfBoundsError _err1__tmp119;
        til_AllocError _err2__tmp119;
        til_Array _tmp120;
        til_AllocError _err_alloc__tmp121;
        til_IndexOutOfBoundsError _err_idx__tmp121;
        til_Str _tmp122 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        int _arr_status__tmp121 = til_Array_new(&_tmp120, &_err_alloc__tmp121, "Str", 1);
        if (_arr_status__tmp121 != 0) {
        }
        _arr_status__tmp121 = til_Array_set(&_err_idx__tmp121, &_tmp120, 0, &_tmp122);
        if (_arr_status__tmp121 != 0) {
            *_err1 = _err_idx__tmp121; return 1;
        }
        int _status__tmp119 = til_format(&_tmp118, &_err0__tmp119, &_err1__tmp119, &_err2__tmp119, ((til_Str){(til_I64)"src/core/array.til:56:52:", 25}), &_tmp120);
        if (_status__tmp119 != 0) {
            if (_status__tmp119 == 2) { *_err1 = _err1__tmp119; return 1; }
        }
        til_Array_delete(&_tmp120);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp118};
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
    til_vec.type_name = ((til_Str){(til_I64)til_T, strlen(til_T)});
    til_vec.type_size = til_size_of(((til_Str){(til_I64)til_T, strlen(til_T)}));
    const til_I64 til_size_bytes = til_mul(til_Vec_INIT_CAP, til_vec.type_size);
    til_I64 _ret__tmp123;
    til_AllocError _err0__tmp123 = {};
    int _status__tmp123 = til_malloc(&_ret__tmp123, &_err0__tmp123, til_size_bytes);
    if (_status__tmp123 == 1) { *_err1 = _err0__tmp123; return 1; }
    til_vec.ptr = _ret__tmp123;
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
            til_Array _tmp124;
            til_AllocError _err_alloc__tmp125;
            til_IndexOutOfBoundsError _err_idx__tmp125;
            til_Str _tmp126 = ((til_Str){(til_I64)"Vec.push: capacity exceeded Vec.MAX_CAP", 39});
            int _arr_status__tmp125 = til_Array_new(&_tmp124, &_err_alloc__tmp125, "Str", 1);
            if (_arr_status__tmp125 != 0) {
                *_err1 = _err_alloc__tmp125; return 1;
            }
            _arr_status__tmp125 = til_Array_set(&_err_idx__tmp125, &_tmp124, 0, &_tmp126);
            if (_arr_status__tmp125 != 0) {
            }
            til_panic(((til_Str){(til_I64)"src/core/vec.til:63:23:", 23}), &_tmp124);
            til_Array_delete(&_tmp124);
        }
        til_I64 _ret__tmp127;
        til_I64 til_new_ptr;
        til_AllocError _err0__tmp127 = {};
        int _status__tmp127 = til_malloc(&_ret__tmp127, &_err0__tmp127, til_mul(til_new_cap, til_self->type_size));
        if (_status__tmp127 == 1) { *_err1 = _err0__tmp127; return 1; }
        til_new_ptr = _ret__tmp127;
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
        til_Str _tmp128;
        til_I64_OverflowError _err0__tmp129;
        til_IndexOutOfBoundsError _err1__tmp129;
        til_AllocError _err2__tmp129;
        til_Array _tmp130;
        til_AllocError _err_alloc__tmp131;
        til_IndexOutOfBoundsError _err_idx__tmp131;
        til_Str _tmp132 = ((til_Str){(til_I64)"Vec.get: index out of bounds", 28});
        int _arr_status__tmp131 = til_Array_new(&_tmp130, &_err_alloc__tmp131, "Str", 1);
        if (_arr_status__tmp131 != 0) {
        }
        _arr_status__tmp131 = til_Array_set(&_err_idx__tmp131, &_tmp130, 0, &_tmp132);
        if (_arr_status__tmp131 != 0) {
            *_err1 = _err_idx__tmp131; return 1;
        }
        int _status__tmp129 = til_format(&_tmp128, &_err0__tmp129, &_err1__tmp129, &_err2__tmp129, ((til_Str){(til_I64)"src/core/vec.til:81:52:", 23}), &_tmp130);
        if (_status__tmp129 != 0) {
            if (_status__tmp129 == 2) { *_err1 = _err1__tmp129; return 1; }
        }
        til_Array_delete(&_tmp130);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp128};
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
    til_I64 _ret__tmp133;
    til_AllocError _err0__tmp133 = {};
    int _status__tmp133 = til_malloc(&_ret__tmp133, &_err0__tmp133, til_cloned.cap);
    if (_status__tmp133 == 1) { *_err1 = _err0__tmp133; return 1; }
    til_cloned.c_string = _ret__tmp133;
    if (til_I64_eq(til_NULL, til_cloned.c_string).data) {
        til_Str _tmp134;
        til_I64_OverflowError _err0__tmp135;
        til_IndexOutOfBoundsError _err1__tmp135;
        til_AllocError _err2__tmp135;
        til_Array _tmp136;
        til_AllocError _err_alloc__tmp137;
        til_IndexOutOfBoundsError _err_idx__tmp137;
        til_Str _tmp138 = ((til_Str){(til_I64)"Str.clone: malloc failed for ", 29});
        til_Str _tmp139 = til_I64_to_str(til_cloned.cap);
        til_Str _tmp140 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp137 = til_Array_new(&_tmp136, &_err_alloc__tmp137, "Str", 3);
        if (_arr_status__tmp137 != 0) {
            *_err1 = _err_alloc__tmp137; return 1;
        }
        _arr_status__tmp137 = til_Array_set(&_err_idx__tmp137, &_tmp136, 0, &_tmp138);
        if (_arr_status__tmp137 != 0) {
        }
        _arr_status__tmp137 = til_Array_set(&_err_idx__tmp137, &_tmp136, 1, &_tmp139);
        if (_arr_status__tmp137 != 0) {
        }
        _arr_status__tmp137 = til_Array_set(&_err_idx__tmp137, &_tmp136, 2, &_tmp140);
        if (_arr_status__tmp137 != 0) {
        }
        int _status__tmp135 = til_format(&_tmp134, &_err0__tmp135, &_err1__tmp135, &_err2__tmp135, ((til_Str){(til_I64)"src/core/str.til:46:41:", 23}), &_tmp136);
        if (_status__tmp135 != 0) {
            if (_status__tmp135 == 3) { *_err1 = _err2__tmp135; return 1; }
        }
        til_Array_delete(&_tmp136);
        *_err1 = (til_AllocError){.msg = _tmp134};
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
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp141;
    if (til_I64_eq(til_Str_len(til_from), 0).data) {
        til_Str _ret__tmp142;
        til_AllocError _err0__tmp142 = {};
        int _status__tmp142 = til_Str_clone(&_ret__tmp142, &_err0__tmp142, til_self);
        if (_status__tmp142 == 1) { *_err1 = _err0__tmp142; return 1; }
        *_ret = _ret__tmp142;
        return 0;
    }
    if (til_I64_eq(til_n, 0).data) {
        til_Str _ret__tmp143;
        til_AllocError _err0__tmp143 = {};
        int _status__tmp143 = til_Str_clone(&_ret__tmp143, &_err0__tmp143, til_self);
        if (_status__tmp143 == 1) { *_err1 = _err0__tmp143; return 1; }
        *_ret = _ret__tmp143;
        return 0;
    }
    til_I64 til_idx = til_Str_find(til_self, til_from);
    if (til_lt(til_idx, 0).data) {
        til_Str _ret__tmp144;
        til_AllocError _err0__tmp144 = {};
        int _status__tmp144 = til_Str_clone(&_ret__tmp144, &_err0__tmp144, til_self);
        if (_status__tmp144 == 1) { *_err1 = _err0__tmp144; return 1; }
        *_ret = _ret__tmp144;
        return 0;
    }
    til_Str _ret__tmp145;
    til_Str til_prefix;
    til_IndexOutOfBoundsError _err0__tmp145 = {};
    til_AllocError _err1__tmp145 = {};
    int _status__tmp145 = til_get_substr(&_ret__tmp145, &_err0__tmp145, &_err1__tmp145, til_self, 0, til_idx);
    if (_status__tmp145 == 1) { _thrown_IndexOutOfBoundsError__tmp141 = _err0__tmp145; goto _catch_IndexOutOfBoundsError__tmp141; }
    if (_status__tmp145 == 2) { *_err1 = _err1__tmp145; return 1; }
    til_prefix = _ret__tmp145;
    til_Str _ret__tmp146;
    til_Str til_suffix;
    til_IndexOutOfBoundsError _err0__tmp146 = {};
    til_AllocError _err1__tmp146 = {};
    int _status__tmp146 = til_get_substr(&_ret__tmp146, &_err0__tmp146, &_err1__tmp146, til_self, til_add(til_idx, til_Str_len(til_from)), til_Str_len(til_self));
    if (_status__tmp146 == 1) { _thrown_IndexOutOfBoundsError__tmp141 = _err0__tmp146; goto _catch_IndexOutOfBoundsError__tmp141; }
    if (_status__tmp146 == 2) { *_err1 = _err1__tmp146; return 1; }
    til_suffix = _ret__tmp146;
    til_Str til_result = til_concat(til_concat(til_prefix, til_to), til_suffix);
    til_Str til_rest;
    if (til_gt(til_n, 1).data) {
        til_Str _ret__tmp147;
        til_Str til_rest;
        til_AllocError _err0__tmp147 = {};
        int _status__tmp147 = til_Str_replacen(&_ret__tmp147, &_err0__tmp147, til_suffix, til_from, til_to, til_sub(til_n, 1));
        if (_status__tmp147 == 1) { *_err1 = _err0__tmp147; return 1; }
        til_rest = _ret__tmp147;
        til_result = til_concat(til_concat(til_prefix, til_to), til_rest);
    }
    if (0) { _catch_IndexOutOfBoundsError__tmp141:
        til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp141;
        til_Str _ret__tmp148;
        til_AllocError _err0__tmp148 = {};
        int _status__tmp148 = til_Str_clone(&_ret__tmp148, &_err0__tmp148, til_self);
        if (_status__tmp148 == 1) { *_err1 = _err0__tmp148; return 1; }
        til_result = _ret__tmp148;
    }
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
        til_Str _tmp149;
        til_I64_OverflowError _err0__tmp150;
        til_IndexOutOfBoundsError _err1__tmp150;
        til_AllocError _err2__tmp150;
        til_Array _tmp151;
        til_AllocError _err_alloc__tmp152;
        til_IndexOutOfBoundsError _err_idx__tmp152;
        til_Str _tmp153 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        int _arr_status__tmp152 = til_Array_new(&_tmp151, &_err_alloc__tmp152, "Str", 1);
        if (_arr_status__tmp152 != 0) {
        }
        _arr_status__tmp152 = til_Array_set(&_err_idx__tmp152, &_tmp151, 0, &_tmp153);
        if (_arr_status__tmp152 != 0) {
        }
        int _status__tmp150 = til_format(&_tmp149, &_err0__tmp150, &_err1__tmp150, &_err2__tmp150, ((til_Str){(til_I64)"src/core/u8.til:50:47:", 22}), &_tmp151);
        if (_status__tmp150 != 0) {
        }
        til_Array_delete(&_tmp151);
        *_err1 = (til_U8_OverflowError){.msg = _tmp149};
        return 1;
    }
    if (til_gt(til_self, til_MAX_U8).data) {
        til_Str _tmp154;
        til_I64_OverflowError _err0__tmp155;
        til_IndexOutOfBoundsError _err1__tmp155;
        til_AllocError _err2__tmp155;
        til_Array _tmp156;
        til_AllocError _err_alloc__tmp157;
        til_IndexOutOfBoundsError _err_idx__tmp157;
        til_Str _tmp158 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp159 = ((til_Str){(til_I64)"255", 3});
        int _arr_status__tmp157 = til_Array_new(&_tmp156, &_err_alloc__tmp157, "Str", 2);
        if (_arr_status__tmp157 != 0) {
        }
        _arr_status__tmp157 = til_Array_set(&_err_idx__tmp157, &_tmp156, 0, &_tmp158);
        if (_arr_status__tmp157 != 0) {
        }
        _arr_status__tmp157 = til_Array_set(&_err_idx__tmp157, &_tmp156, 1, &_tmp159);
        if (_arr_status__tmp157 != 0) {
        }
        int _status__tmp155 = til_format(&_tmp154, &_err0__tmp155, &_err1__tmp155, &_err2__tmp155, ((til_Str){(til_I64)"src/core/u8.til:53:47:", 22}), &_tmp156);
        if (_status__tmp155 != 0) {
        }
        til_Array_delete(&_tmp156);
        *_err1 = (til_U8_OverflowError){.msg = _tmp154};
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
