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
til_IndexOutOfBoundsError til_IndexOutOfBoundsError_new(const til_Str til_msg);
til_AllocError til_AllocError_new(const til_Str til_msg);
til_I64 til_Array_len(const til_Array til_self);
int til_Array_new(til_Array* _ret, til_AllocError* _err1, const til_Type til_T, const til_I64 til_capacity);
int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array til_self, const til_I64 til_index, til_Dynamic* til_T);
int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64 til_index, const til_Dynamic til_value);
void til_Array_delete(til_Array* til_self);
til_Bool til_Bool_and(const til_Bool til_self, const til_Bool til_other);
til_I64_OverflowError til_I64_OverflowError_new(const til_Str til_msg);
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
til_U8_OverflowError til_U8_OverflowError_new(const til_Str til_msg);
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
        if (til_val.data) {
            return true;
        }
        _for_i_5 = til_add(_for_i_5, 1);
        goto _end_catches__tmp4;
_catch_IndexOutOfBoundsError__tmp4: {
        til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp4;
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
        til_panic(((til_Str){(til_I64)"src/core/bool.til:74:5:", 23}), &_tmp12);
        til_Array_delete(&_tmp12);
        goto _end_catches__tmp4;
        }
_end_catches__tmp4:;
    }
    return false;
}

til_Bool til_and(til_Array* til_args) {
    til_I64 _for_i_6 = 0;
    til_Bool til_val;
    while (til_lt(_for_i_6, til_Array_len((*til_args))).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp17;
        til_val = (til_Bool){.data = 0};
        til_IndexOutOfBoundsError _err0__tmp18 = {};
        int _status__tmp18 = til_Array_get(&_err0__tmp18, (*til_args), _for_i_6, (til_Dynamic*)&til_val);
        if (_status__tmp18 == 0) {
        } else if (_status__tmp18 == 1) {
            til_IndexOutOfBoundsError til_err = _err0__tmp18;
            til_Array _tmp20;
            til_AllocError _err_alloc__tmp21;
            til_IndexOutOfBoundsError _err_idx__tmp21;
            til_Str _tmp22 = til_err.msg;
            int _arr_status__tmp21 = til_Array_new(&_tmp20, &_err_alloc__tmp21, "Str", 1);
            if (_arr_status__tmp21 != 0) {
            }
            _arr_status__tmp21 = til_Array_set(&_err_idx__tmp21, &_tmp20, 0, &_tmp22);
            if (_arr_status__tmp21 != 0) {
            }
            til_panic(((til_Str){(til_I64)"src/core/bool.til:83:5:", 23}), &_tmp20);
            til_Array_delete(&_tmp20);
        }
        if (til_not(til_val).data) {
            return false;
        }
        _for_i_6 = til_add(_for_i_6, 1);
        goto _end_catches__tmp17;
_catch_IndexOutOfBoundsError__tmp17: {
        til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp17;
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
        goto _end_catches__tmp17;
        }
_end_catches__tmp17:;
    }
    return true;
}

void til_panic(const til_Str til_loc_str, til_Array* til_msgs) {
    til_single_print(til_loc_str);
    til_I64 _for_i_7 = 0;
    til_Str til_val;
    while (til_lt(_for_i_7, til_Array_len((*til_msgs))).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp30;
        til_val = (til_Str){.c_string = 0, .cap = 0};
        til_IndexOutOfBoundsError _err0__tmp31 = {};
        int _status__tmp31 = til_Array_get(&_err0__tmp31, (*til_msgs), _for_i_7, (til_Dynamic*)&til_val);
        if (_status__tmp31 == 0) {
        } else if (_status__tmp31 == 1) {
            til_IndexOutOfBoundsError til_err = _err0__tmp31;
            til_Array _tmp33;
            til_AllocError _err_alloc__tmp34;
            til_IndexOutOfBoundsError _err_idx__tmp34;
            til_Str _tmp35 = til_err.msg;
            int _arr_status__tmp34 = til_Array_new(&_tmp33, &_err_alloc__tmp34, "Str", 1);
            if (_arr_status__tmp34 != 0) {
            }
            _arr_status__tmp34 = til_Array_set(&_err_idx__tmp34, &_tmp33, 0, &_tmp35);
            if (_arr_status__tmp34 != 0) {
            }
            til_panic(((til_Str){(til_I64)"src/core/exit.til:9:5:", 22}), &_tmp33);
            til_Array_delete(&_tmp33);
        }
        til_single_print(til_val);
        _for_i_7 = til_add(_for_i_7, 1);
        goto _end_catches__tmp30;
_catch_IndexOutOfBoundsError__tmp30: {
        til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp30;
        til_Array _tmp37;
        til_AllocError _err_alloc__tmp38;
        til_IndexOutOfBoundsError _err_idx__tmp38;
        til_Str _tmp39 = til_err.msg;
        int _arr_status__tmp38 = til_Array_new(&_tmp37, &_err_alloc__tmp38, "Str", 1);
        if (_arr_status__tmp38 != 0) {
        }
        _arr_status__tmp38 = til_Array_set(&_err_idx__tmp38, &_tmp37, 0, &_tmp39);
        if (_arr_status__tmp38 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/exit.til:9:5:", 22}), &_tmp37);
        til_Array_delete(&_tmp37);
        goto _end_catches__tmp30;
        }
_end_catches__tmp30:;
    }
    til_single_print(((til_Str){(til_I64)"\n", 1}));
    til_print_flush();
    til_exit(1);
}

void til_assertm(const til_Str til_loc_str, const til_Bool til_cond, const til_Str til_msg) {
    if (til_not(til_cond).data) {
        til_Str _tmp42;
        til_I64_OverflowError _err0__tmp43;
        til_IndexOutOfBoundsError _err1__tmp43;
        til_AllocError _err2__tmp43;
        til_Array _tmp44;
        til_AllocError _err_alloc__tmp45;
        til_IndexOutOfBoundsError _err_idx__tmp45;
        til_Str _tmp46 = til_msg;
        int _arr_status__tmp45 = til_Array_new(&_tmp44, &_err_alloc__tmp45, "Str", 1);
        if (_arr_status__tmp45 != 0) {
        }
        _arr_status__tmp45 = til_Array_set(&_err_idx__tmp45, &_tmp44, 0, &_tmp46);
        if (_arr_status__tmp45 != 0) {
        }
        int _status__tmp43 = til_format(&_tmp42, &_err0__tmp43, &_err1__tmp43, &_err2__tmp43, ((til_Str){(til_I64)"assert failed: ", 15}), &_tmp44);
        if (_status__tmp43 != 0) {
        }
        til_Array_delete(&_tmp44);
        til_Array _tmp47;
        til_AllocError _err_alloc__tmp48;
        til_IndexOutOfBoundsError _err_idx__tmp48;
        int _arr_status__tmp48 = til_Array_new(&_tmp47, &_err_alloc__tmp48, "Str", 1);
        if (_arr_status__tmp48 != 0) {
        }
        _arr_status__tmp48 = til_Array_set(&_err_idx__tmp48, &_tmp47, 0, &_tmp42);
        if (_arr_status__tmp48 != 0) {
        }
        til_panic(til_loc_str, &_tmp47);
        til_Array_delete(&_tmp47);
    }
}

void til_println(til_Array* til_args) {
    til_I64 _for_i_9 = 0;
    til_Str til_val;
    while (til_lt(_for_i_9, til_Array_len((*til_args))).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp51;
        til_val = (til_Str){.c_string = 0, .cap = 0};
        til_IndexOutOfBoundsError _err0__tmp52 = {};
        int _status__tmp52 = til_Array_get(&_err0__tmp52, (*til_args), _for_i_9, (til_Dynamic*)&til_val);
        if (_status__tmp52 == 0) {
        } else if (_status__tmp52 == 1) {
            til_IndexOutOfBoundsError til_err = _err0__tmp52;
            til_Array _tmp54;
            til_AllocError _err_alloc__tmp55;
            til_IndexOutOfBoundsError _err_idx__tmp55;
            til_Str _tmp56 = til_err.msg;
            int _arr_status__tmp55 = til_Array_new(&_tmp54, &_err_alloc__tmp55, "Str", 1);
            if (_arr_status__tmp55 != 0) {
            }
            _arr_status__tmp55 = til_Array_set(&_err_idx__tmp55, &_tmp54, 0, &_tmp56);
            if (_arr_status__tmp55 != 0) {
            }
            til_panic(((til_Str){(til_I64)"src/core/print.til:16:5:", 24}), &_tmp54);
            til_Array_delete(&_tmp54);
        }
        til_single_print(til_val);
        _for_i_9 = til_add(_for_i_9, 1);
        goto _end_catches__tmp51;
_catch_IndexOutOfBoundsError__tmp51: {
        til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp51;
        til_Array _tmp58;
        til_AllocError _err_alloc__tmp59;
        til_IndexOutOfBoundsError _err_idx__tmp59;
        til_Str _tmp60 = til_err.msg;
        int _arr_status__tmp59 = til_Array_new(&_tmp58, &_err_alloc__tmp59, "Str", 1);
        if (_arr_status__tmp59 != 0) {
        }
        _arr_status__tmp59 = til_Array_set(&_err_idx__tmp59, &_tmp58, 0, &_tmp60);
        if (_arr_status__tmp59 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/print.til:16:5:", 24}), &_tmp58);
        til_Array_delete(&_tmp58);
        goto _end_catches__tmp51;
        }
_end_catches__tmp51:;
    }
    til_single_print(((til_Str){(til_I64)"\n", 1}));
    til_print_flush();
}

int til_get_substr(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_start, const til_I64 til_end) {
    if (til_lt(til_start, 0).data) {
        til_Str _tmp63;
        til_I64_OverflowError _err0__tmp64;
        til_IndexOutOfBoundsError _err1__tmp64;
        til_AllocError _err2__tmp64;
        til_Array _tmp65;
        til_AllocError _err_alloc__tmp66;
        til_IndexOutOfBoundsError _err_idx__tmp66;
        til_Str _tmp67 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp68 = til_I64_to_str(til_start);
        til_Str _tmp69 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp66 = til_Array_new(&_tmp65, &_err_alloc__tmp66, "Str", 3);
        if (_arr_status__tmp66 != 0) {
            *_err2 = _err_alloc__tmp66; return 2;
        }
        _arr_status__tmp66 = til_Array_set(&_err_idx__tmp66, &_tmp65, 0, &_tmp67);
        if (_arr_status__tmp66 != 0) {
            *_err1 = _err_idx__tmp66; return 1;
        }
        _arr_status__tmp66 = til_Array_set(&_err_idx__tmp66, &_tmp65, 1, &_tmp68);
        if (_arr_status__tmp66 != 0) {
            *_err1 = _err_idx__tmp66; return 1;
        }
        _arr_status__tmp66 = til_Array_set(&_err_idx__tmp66, &_tmp65, 2, &_tmp69);
        if (_arr_status__tmp66 != 0) {
            *_err1 = _err_idx__tmp66; return 1;
        }
        int _status__tmp64 = til_format(&_tmp63, &_err0__tmp64, &_err1__tmp64, &_err2__tmp64, ((til_Str){(til_I64)"src/core/str.til:368:48:", 24}), &_tmp65);
        if (_status__tmp64 != 0) {
            if (_status__tmp64 == 2) { *_err1 = _err1__tmp64; return 1; }
            if (_status__tmp64 == 3) { *_err2 = _err2__tmp64; return 2; }
        }
        til_Array_delete(&_tmp65);
        til_Str _tmp70;
        til_I64_OverflowError _err0__tmp71;
        til_IndexOutOfBoundsError _err1__tmp71;
        til_AllocError _err2__tmp71;
        til_Array _tmp72;
        til_AllocError _err_alloc__tmp73;
        til_IndexOutOfBoundsError _err_idx__tmp73;
        til_Str _tmp74 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp75 = til_I64_to_str(til_start);
        til_Str _tmp76 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp73 = til_Array_new(&_tmp72, &_err_alloc__tmp73, "Str", 3);
        if (_arr_status__tmp73 != 0) {
            *_err2 = _err_alloc__tmp73; return 2;
        }
        _arr_status__tmp73 = til_Array_set(&_err_idx__tmp73, &_tmp72, 0, &_tmp74);
        if (_arr_status__tmp73 != 0) {
            *_err1 = _err_idx__tmp73; return 1;
        }
        _arr_status__tmp73 = til_Array_set(&_err_idx__tmp73, &_tmp72, 1, &_tmp75);
        if (_arr_status__tmp73 != 0) {
            *_err1 = _err_idx__tmp73; return 1;
        }
        _arr_status__tmp73 = til_Array_set(&_err_idx__tmp73, &_tmp72, 2, &_tmp76);
        if (_arr_status__tmp73 != 0) {
            *_err1 = _err_idx__tmp73; return 1;
        }
        int _status__tmp71 = til_format(&_tmp70, &_err0__tmp71, &_err1__tmp71, &_err2__tmp71, ((til_Str){(til_I64)"src/core/str.til:368:48:", 24}), &_tmp72);
        if (_status__tmp71 != 0) {
            if (_status__tmp71 == 2) { *_err1 = _err1__tmp71; return 1; }
            if (_status__tmp71 == 3) { *_err2 = _err2__tmp71; return 2; }
        }
        til_Array_delete(&_tmp72);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp70);
        return 1;
    }
    if (til_lt(til_end, 0).data) {
        til_Str _tmp78;
        til_I64_OverflowError _err0__tmp79;
        til_IndexOutOfBoundsError _err1__tmp79;
        til_AllocError _err2__tmp79;
        til_Array _tmp80;
        til_AllocError _err_alloc__tmp81;
        til_IndexOutOfBoundsError _err_idx__tmp81;
        til_Str _tmp82 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp83 = til_I64_to_str(til_end);
        til_Str _tmp84 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp81 = til_Array_new(&_tmp80, &_err_alloc__tmp81, "Str", 3);
        if (_arr_status__tmp81 != 0) {
            *_err2 = _err_alloc__tmp81; return 2;
        }
        _arr_status__tmp81 = til_Array_set(&_err_idx__tmp81, &_tmp80, 0, &_tmp82);
        if (_arr_status__tmp81 != 0) {
            *_err1 = _err_idx__tmp81; return 1;
        }
        _arr_status__tmp81 = til_Array_set(&_err_idx__tmp81, &_tmp80, 1, &_tmp83);
        if (_arr_status__tmp81 != 0) {
            *_err1 = _err_idx__tmp81; return 1;
        }
        _arr_status__tmp81 = til_Array_set(&_err_idx__tmp81, &_tmp80, 2, &_tmp84);
        if (_arr_status__tmp81 != 0) {
            *_err1 = _err_idx__tmp81; return 1;
        }
        int _status__tmp79 = til_format(&_tmp78, &_err0__tmp79, &_err1__tmp79, &_err2__tmp79, ((til_Str){(til_I64)"src/core/str.til:371:48:", 24}), &_tmp80);
        if (_status__tmp79 != 0) {
            if (_status__tmp79 == 2) { *_err1 = _err1__tmp79; return 1; }
            if (_status__tmp79 == 3) { *_err2 = _err2__tmp79; return 2; }
        }
        til_Array_delete(&_tmp80);
        til_Str _tmp85;
        til_I64_OverflowError _err0__tmp86;
        til_IndexOutOfBoundsError _err1__tmp86;
        til_AllocError _err2__tmp86;
        til_Array _tmp87;
        til_AllocError _err_alloc__tmp88;
        til_IndexOutOfBoundsError _err_idx__tmp88;
        til_Str _tmp89 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp90 = til_I64_to_str(til_end);
        til_Str _tmp91 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp88 = til_Array_new(&_tmp87, &_err_alloc__tmp88, "Str", 3);
        if (_arr_status__tmp88 != 0) {
            *_err2 = _err_alloc__tmp88; return 2;
        }
        _arr_status__tmp88 = til_Array_set(&_err_idx__tmp88, &_tmp87, 0, &_tmp89);
        if (_arr_status__tmp88 != 0) {
            *_err1 = _err_idx__tmp88; return 1;
        }
        _arr_status__tmp88 = til_Array_set(&_err_idx__tmp88, &_tmp87, 1, &_tmp90);
        if (_arr_status__tmp88 != 0) {
            *_err1 = _err_idx__tmp88; return 1;
        }
        _arr_status__tmp88 = til_Array_set(&_err_idx__tmp88, &_tmp87, 2, &_tmp91);
        if (_arr_status__tmp88 != 0) {
            *_err1 = _err_idx__tmp88; return 1;
        }
        int _status__tmp86 = til_format(&_tmp85, &_err0__tmp86, &_err1__tmp86, &_err2__tmp86, ((til_Str){(til_I64)"src/core/str.til:371:48:", 24}), &_tmp87);
        if (_status__tmp86 != 0) {
            if (_status__tmp86 == 2) { *_err1 = _err1__tmp86; return 1; }
            if (_status__tmp86 == 3) { *_err2 = _err2__tmp86; return 2; }
        }
        til_Array_delete(&_tmp87);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp85);
        return 1;
    }
    if (til_gt(til_start, til_end).data) {
        til_Str _tmp93;
        til_I64_OverflowError _err0__tmp94;
        til_IndexOutOfBoundsError _err1__tmp94;
        til_AllocError _err2__tmp94;
        til_Array _tmp95;
        til_AllocError _err_alloc__tmp96;
        til_IndexOutOfBoundsError _err_idx__tmp96;
        til_Str _tmp97 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp98 = til_I64_to_str(til_start);
        til_Str _tmp99 = ((til_Str){(til_I64)" is greater than end index ", 27});
        til_Str _tmp100 = til_I64_to_str(til_end);
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
        int _status__tmp94 = til_format(&_tmp93, &_err0__tmp94, &_err1__tmp94, &_err2__tmp94, ((til_Str){(til_I64)"src/core/str.til:374:48:", 24}), &_tmp95);
        if (_status__tmp94 != 0) {
            if (_status__tmp94 == 2) { *_err1 = _err1__tmp94; return 1; }
            if (_status__tmp94 == 3) { *_err2 = _err2__tmp94; return 2; }
        }
        til_Array_delete(&_tmp95);
        til_Str _tmp101;
        til_I64_OverflowError _err0__tmp102;
        til_IndexOutOfBoundsError _err1__tmp102;
        til_AllocError _err2__tmp102;
        til_Array _tmp103;
        til_AllocError _err_alloc__tmp104;
        til_IndexOutOfBoundsError _err_idx__tmp104;
        til_Str _tmp105 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp106 = til_I64_to_str(til_start);
        til_Str _tmp107 = ((til_Str){(til_I64)" is greater than end index ", 27});
        til_Str _tmp108 = til_I64_to_str(til_end);
        int _arr_status__tmp104 = til_Array_new(&_tmp103, &_err_alloc__tmp104, "Str", 4);
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
        _arr_status__tmp104 = til_Array_set(&_err_idx__tmp104, &_tmp103, 3, &_tmp108);
        if (_arr_status__tmp104 != 0) {
            *_err1 = _err_idx__tmp104; return 1;
        }
        int _status__tmp102 = til_format(&_tmp101, &_err0__tmp102, &_err1__tmp102, &_err2__tmp102, ((til_Str){(til_I64)"src/core/str.til:374:48:", 24}), &_tmp103);
        if (_status__tmp102 != 0) {
            if (_status__tmp102 == 2) { *_err1 = _err1__tmp102; return 1; }
            if (_status__tmp102 == 3) { *_err2 = _err2__tmp102; return 2; }
        }
        til_Array_delete(&_tmp103);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp101);
        return 1;
    }
    if (til_gt(til_end, til_Str_len(til_s)).data) {
        til_Str _tmp110;
        til_I64_OverflowError _err0__tmp111;
        til_IndexOutOfBoundsError _err1__tmp111;
        til_AllocError _err2__tmp111;
        til_Array _tmp112;
        til_AllocError _err_alloc__tmp113;
        til_IndexOutOfBoundsError _err_idx__tmp113;
        til_Str _tmp114 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp115 = til_I64_to_str(til_end);
        til_Str _tmp116 = ((til_Str){(til_I64)" is greater than string length ", 31});
        til_Str _tmp117 = til_I64_to_str(til_Str_len(til_s));
        int _arr_status__tmp113 = til_Array_new(&_tmp112, &_err_alloc__tmp113, "Str", 4);
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
        _arr_status__tmp113 = til_Array_set(&_err_idx__tmp113, &_tmp112, 3, &_tmp117);
        if (_arr_status__tmp113 != 0) {
            *_err1 = _err_idx__tmp113; return 1;
        }
        int _status__tmp111 = til_format(&_tmp110, &_err0__tmp111, &_err1__tmp111, &_err2__tmp111, ((til_Str){(til_I64)"src/core/str.til:377:48:", 24}), &_tmp112);
        if (_status__tmp111 != 0) {
            if (_status__tmp111 == 2) { *_err1 = _err1__tmp111; return 1; }
            if (_status__tmp111 == 3) { *_err2 = _err2__tmp111; return 2; }
        }
        til_Array_delete(&_tmp112);
        til_Str _tmp118;
        til_I64_OverflowError _err0__tmp119;
        til_IndexOutOfBoundsError _err1__tmp119;
        til_AllocError _err2__tmp119;
        til_Array _tmp120;
        til_AllocError _err_alloc__tmp121;
        til_IndexOutOfBoundsError _err_idx__tmp121;
        til_Str _tmp122 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp123 = til_I64_to_str(til_end);
        til_Str _tmp124 = ((til_Str){(til_I64)" is greater than string length ", 31});
        til_Str _tmp125 = til_I64_to_str(til_Str_len(til_s));
        int _arr_status__tmp121 = til_Array_new(&_tmp120, &_err_alloc__tmp121, "Str", 4);
        if (_arr_status__tmp121 != 0) {
            *_err2 = _err_alloc__tmp121; return 2;
        }
        _arr_status__tmp121 = til_Array_set(&_err_idx__tmp121, &_tmp120, 0, &_tmp122);
        if (_arr_status__tmp121 != 0) {
            *_err1 = _err_idx__tmp121; return 1;
        }
        _arr_status__tmp121 = til_Array_set(&_err_idx__tmp121, &_tmp120, 1, &_tmp123);
        if (_arr_status__tmp121 != 0) {
            *_err1 = _err_idx__tmp121; return 1;
        }
        _arr_status__tmp121 = til_Array_set(&_err_idx__tmp121, &_tmp120, 2, &_tmp124);
        if (_arr_status__tmp121 != 0) {
            *_err1 = _err_idx__tmp121; return 1;
        }
        _arr_status__tmp121 = til_Array_set(&_err_idx__tmp121, &_tmp120, 3, &_tmp125);
        if (_arr_status__tmp121 != 0) {
            *_err1 = _err_idx__tmp121; return 1;
        }
        int _status__tmp119 = til_format(&_tmp118, &_err0__tmp119, &_err1__tmp119, &_err2__tmp119, ((til_Str){(til_I64)"src/core/str.til:377:48:", 24}), &_tmp120);
        if (_status__tmp119 != 0) {
            if (_status__tmp119 == 2) { *_err1 = _err1__tmp119; return 1; }
            if (_status__tmp119 == 3) { *_err2 = _err2__tmp119; return 2; }
        }
        til_Array_delete(&_tmp120);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp118);
        return 1;
    }
    if (til_I64_eq(til_start, til_end).data) {
        til_Str _tmp127;
        til_I64_OverflowError _err0__tmp128;
        til_IndexOutOfBoundsError _err1__tmp128;
        til_AllocError _err2__tmp128;
        til_Array _tmp129;
        til_AllocError _err_alloc__tmp130;
        til_IndexOutOfBoundsError _err_idx__tmp130;
        til_Str _tmp131 = ((til_Str){(til_I64)"get_substr: start and end are the same (", 40});
        til_Str _tmp132 = til_I64_to_str(til_start);
        til_Str _tmp133 = ((til_Str){(til_I64)"), no substring", 15});
        int _arr_status__tmp130 = til_Array_new(&_tmp129, &_err_alloc__tmp130, "Str", 3);
        if (_arr_status__tmp130 != 0) {
            *_err2 = _err_alloc__tmp130; return 2;
        }
        _arr_status__tmp130 = til_Array_set(&_err_idx__tmp130, &_tmp129, 0, &_tmp131);
        if (_arr_status__tmp130 != 0) {
            *_err1 = _err_idx__tmp130; return 1;
        }
        _arr_status__tmp130 = til_Array_set(&_err_idx__tmp130, &_tmp129, 1, &_tmp132);
        if (_arr_status__tmp130 != 0) {
            *_err1 = _err_idx__tmp130; return 1;
        }
        _arr_status__tmp130 = til_Array_set(&_err_idx__tmp130, &_tmp129, 2, &_tmp133);
        if (_arr_status__tmp130 != 0) {
            *_err1 = _err_idx__tmp130; return 1;
        }
        int _status__tmp128 = til_format(&_tmp127, &_err0__tmp128, &_err1__tmp128, &_err2__tmp128, ((til_Str){(til_I64)"src/core/str.til:380:48:", 24}), &_tmp129);
        if (_status__tmp128 != 0) {
            if (_status__tmp128 == 2) { *_err1 = _err1__tmp128; return 1; }
            if (_status__tmp128 == 3) { *_err2 = _err2__tmp128; return 2; }
        }
        til_Array_delete(&_tmp129);
        til_Str _tmp134;
        til_I64_OverflowError _err0__tmp135;
        til_IndexOutOfBoundsError _err1__tmp135;
        til_AllocError _err2__tmp135;
        til_Array _tmp136;
        til_AllocError _err_alloc__tmp137;
        til_IndexOutOfBoundsError _err_idx__tmp137;
        til_Str _tmp138 = ((til_Str){(til_I64)"get_substr: start and end are the same (", 40});
        til_Str _tmp139 = til_I64_to_str(til_start);
        til_Str _tmp140 = ((til_Str){(til_I64)"), no substring", 15});
        int _arr_status__tmp137 = til_Array_new(&_tmp136, &_err_alloc__tmp137, "Str", 3);
        if (_arr_status__tmp137 != 0) {
            *_err2 = _err_alloc__tmp137; return 2;
        }
        _arr_status__tmp137 = til_Array_set(&_err_idx__tmp137, &_tmp136, 0, &_tmp138);
        if (_arr_status__tmp137 != 0) {
            *_err1 = _err_idx__tmp137; return 1;
        }
        _arr_status__tmp137 = til_Array_set(&_err_idx__tmp137, &_tmp136, 1, &_tmp139);
        if (_arr_status__tmp137 != 0) {
            *_err1 = _err_idx__tmp137; return 1;
        }
        _arr_status__tmp137 = til_Array_set(&_err_idx__tmp137, &_tmp136, 2, &_tmp140);
        if (_arr_status__tmp137 != 0) {
            *_err1 = _err_idx__tmp137; return 1;
        }
        int _status__tmp135 = til_format(&_tmp134, &_err0__tmp135, &_err1__tmp135, &_err2__tmp135, ((til_Str){(til_I64)"src/core/str.til:380:48:", 24}), &_tmp136);
        if (_status__tmp135 != 0) {
            if (_status__tmp135 == 2) { *_err1 = _err1__tmp135; return 1; }
            if (_status__tmp135 == 3) { *_err2 = _err2__tmp135; return 2; }
        }
        til_Array_delete(&_tmp136);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp134);
        return 1;
    }
    til_Str til_substr = {.c_string = 0, .cap = 0};
    til_substr.cap = til_sub(til_end, til_start);
    til_I64 _ret__tmp141;
    til_AllocError _err0__tmp141 = {};
    int _status__tmp141 = til_malloc(&_ret__tmp141, &_err0__tmp141, til_substr.cap);
    if (_status__tmp141 == 1) { *_err2 = _err0__tmp141; return 2; }
    til_substr.c_string = _ret__tmp141;
    if (til_I64_eq(til_NULL, til_substr.c_string).data) {
        til_Str _tmp143;
        til_I64_OverflowError _err0__tmp144;
        til_IndexOutOfBoundsError _err1__tmp144;
        til_AllocError _err2__tmp144;
        til_Array _tmp145;
        til_AllocError _err_alloc__tmp146;
        til_IndexOutOfBoundsError _err_idx__tmp146;
        til_Str _tmp147 = ((til_Str){(til_I64)"Str.get_substr: failed to allocate ", 35});
        til_Str _tmp148 = til_I64_to_str(til_substr.cap);
        til_Str _tmp149 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp146 = til_Array_new(&_tmp145, &_err_alloc__tmp146, "Str", 3);
        if (_arr_status__tmp146 != 0) {
            *_err2 = _err_alloc__tmp146; return 2;
        }
        _arr_status__tmp146 = til_Array_set(&_err_idx__tmp146, &_tmp145, 0, &_tmp147);
        if (_arr_status__tmp146 != 0) {
            *_err1 = _err_idx__tmp146; return 1;
        }
        _arr_status__tmp146 = til_Array_set(&_err_idx__tmp146, &_tmp145, 1, &_tmp148);
        if (_arr_status__tmp146 != 0) {
            *_err1 = _err_idx__tmp146; return 1;
        }
        _arr_status__tmp146 = til_Array_set(&_err_idx__tmp146, &_tmp145, 2, &_tmp149);
        if (_arr_status__tmp146 != 0) {
            *_err1 = _err_idx__tmp146; return 1;
        }
        int _status__tmp144 = til_format(&_tmp143, &_err0__tmp144, &_err1__tmp144, &_err2__tmp144, ((til_Str){(til_I64)"src/core/str.til:387:37:", 24}), &_tmp145);
        if (_status__tmp144 != 0) {
            if (_status__tmp144 == 2) { *_err1 = _err1__tmp144; return 1; }
            if (_status__tmp144 == 3) { *_err2 = _err2__tmp144; return 2; }
        }
        til_Array_delete(&_tmp145);
        til_Str _tmp150;
        til_I64_OverflowError _err0__tmp151;
        til_IndexOutOfBoundsError _err1__tmp151;
        til_AllocError _err2__tmp151;
        til_Array _tmp152;
        til_AllocError _err_alloc__tmp153;
        til_IndexOutOfBoundsError _err_idx__tmp153;
        til_Str _tmp154 = ((til_Str){(til_I64)"Str.get_substr: failed to allocate ", 35});
        til_Str _tmp155 = til_I64_to_str(til_substr.cap);
        til_Str _tmp156 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp153 = til_Array_new(&_tmp152, &_err_alloc__tmp153, "Str", 3);
        if (_arr_status__tmp153 != 0) {
            *_err2 = _err_alloc__tmp153; return 2;
        }
        _arr_status__tmp153 = til_Array_set(&_err_idx__tmp153, &_tmp152, 0, &_tmp154);
        if (_arr_status__tmp153 != 0) {
            *_err1 = _err_idx__tmp153; return 1;
        }
        _arr_status__tmp153 = til_Array_set(&_err_idx__tmp153, &_tmp152, 1, &_tmp155);
        if (_arr_status__tmp153 != 0) {
            *_err1 = _err_idx__tmp153; return 1;
        }
        _arr_status__tmp153 = til_Array_set(&_err_idx__tmp153, &_tmp152, 2, &_tmp156);
        if (_arr_status__tmp153 != 0) {
            *_err1 = _err_idx__tmp153; return 1;
        }
        int _status__tmp151 = til_format(&_tmp150, &_err0__tmp151, &_err1__tmp151, &_err2__tmp151, ((til_Str){(til_I64)"src/core/str.til:387:37:", 24}), &_tmp152);
        if (_status__tmp151 != 0) {
            if (_status__tmp151 == 2) { *_err1 = _err1__tmp151; return 1; }
            if (_status__tmp151 == 3) { *_err2 = _err2__tmp151; return 2; }
        }
        til_Array_delete(&_tmp152);
        *_err2 = til_AllocError_new(_tmp150);
        return 2;
    }
    til_memcpy(til_substr.c_string, til_add(til_s.c_string, til_start), til_substr.cap);
    *_ret = til_substr;
    return 0;
}

til_Str til_concat(const til_Str til_a, const til_Str til_b) {
    til_AllocError _thrown_AllocError__tmp157;
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_add(til_a.cap, til_b.cap);
    if (til_lt(til_result.cap, til_a.cap).data) {
        til_Array _tmp159;
        til_AllocError _err_alloc__tmp160;
        til_IndexOutOfBoundsError _err_idx__tmp160;
        til_Str _tmp161 = ((til_Str){(til_I64)"concat: integer overflow", 24});
        int _arr_status__tmp160 = til_Array_new(&_tmp159, &_err_alloc__tmp160, "Str", 1);
        if (_arr_status__tmp160 != 0) {
        }
        _arr_status__tmp160 = til_Array_set(&_err_idx__tmp160, &_tmp159, 0, &_tmp161);
        if (_arr_status__tmp160 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:447:15:", 24}), &_tmp159);
        til_Array_delete(&_tmp159);
    }
    til_I64 _ret__tmp162;
    til_AllocError _err0__tmp162 = {};
    int _status__tmp162 = til_malloc(&_ret__tmp162, &_err0__tmp162, til_result.cap);
    if (_status__tmp162 == 1) { _thrown_AllocError__tmp157 = _err0__tmp162; goto _catch_AllocError__tmp157; }
    til_result.c_string = _ret__tmp162;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Array _tmp164;
        til_AllocError _err_alloc__tmp165;
        til_IndexOutOfBoundsError _err_idx__tmp165;
        til_Str _tmp166 = ((til_Str){(til_I64)"concat: malloc failed", 21});
        int _arr_status__tmp165 = til_Array_new(&_tmp164, &_err_alloc__tmp165, "Str", 1);
        if (_arr_status__tmp165 != 0) {
        }
        _arr_status__tmp165 = til_Array_set(&_err_idx__tmp165, &_tmp164, 0, &_tmp166);
        if (_arr_status__tmp165 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:452:15:", 24}), &_tmp164);
        til_Array_delete(&_tmp164);
    }
    til_memcpy(til_result.c_string, til_a.c_string, til_a.cap);
    til_memcpy(til_add(til_result.c_string, til_a.cap), til_b.c_string, til_b.cap);
    return til_result;
    goto _end_catches__tmp157;
_catch_AllocError__tmp157: {
    til_AllocError til_err = _thrown_AllocError__tmp157;
    til_Array _tmp168;
    til_AllocError _err_alloc__tmp169;
    til_IndexOutOfBoundsError _err_idx__tmp169;
    til_Str _tmp170 = til_err.msg;
    int _arr_status__tmp169 = til_Array_new(&_tmp168, &_err_alloc__tmp169, "Str", 1);
    if (_arr_status__tmp169 != 0) {
    }
    _arr_status__tmp169 = til_Array_set(&_err_idx__tmp169, &_tmp168, 0, &_tmp170);
    if (_arr_status__tmp169 != 0) {
    }
    til_panic(((til_Str){(til_I64)"src/core/str.til:459:15:", 24}), &_tmp168);
    til_Array_delete(&_tmp168);
    goto _end_catches__tmp157;
    }
_end_catches__tmp157:;
}

int til_format(til_Str* _ret, til_I64_OverflowError* _err1, til_IndexOutOfBoundsError* _err2, til_AllocError* _err3, const til_Str til_prefix, til_Array* til_args) {
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_prefix.cap;
    til_I64 til_i = 0;
    til_Str til_arg;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_arg = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp174 = {};
        int _status__tmp174 = til_Array_get(&_err0__tmp174, (*til_args), til_i, (til_Dynamic*)&til_arg);
        if (_status__tmp174 == 1) { *_err2 = _err0__tmp174; return 2; }
        til_result.cap = til_add(til_result.cap, til_arg.cap);
        if (til_lt(til_result.cap, til_arg.cap).data) {
            til_Str _tmp176;
            til_I64_OverflowError _err0__tmp177;
            til_IndexOutOfBoundsError _err1__tmp177;
            til_AllocError _err2__tmp177;
            til_Array _tmp178;
            til_AllocError _err_alloc__tmp179;
            til_IndexOutOfBoundsError _err_idx__tmp179;
            til_Str _tmp180 = ((til_Str){(til_I64)"format: integer overflow while summing cap for arg ", 51});
            til_Str _tmp181 = til_I64_to_str(til_i);
            int _arr_status__tmp179 = til_Array_new(&_tmp178, &_err_alloc__tmp179, "Str", 2);
            if (_arr_status__tmp179 != 0) {
                *_err3 = _err_alloc__tmp179; return 3;
            }
            _arr_status__tmp179 = til_Array_set(&_err_idx__tmp179, &_tmp178, 0, &_tmp180);
            if (_arr_status__tmp179 != 0) {
                *_err2 = _err_idx__tmp179; return 2;
            }
            _arr_status__tmp179 = til_Array_set(&_err_idx__tmp179, &_tmp178, 1, &_tmp181);
            if (_arr_status__tmp179 != 0) {
                *_err2 = _err_idx__tmp179; return 2;
            }
            int _status__tmp177 = til_format(&_tmp176, &_err0__tmp177, &_err1__tmp177, &_err2__tmp177, ((til_Str){(til_I64)"src/core/str.til:475:48:", 24}), &_tmp178);
            if (_status__tmp177 != 0) {
                if (_status__tmp177 == 1) { *_err1 = _err0__tmp177; return 1; }
                if (_status__tmp177 == 2) { *_err2 = _err1__tmp177; return 2; }
                if (_status__tmp177 == 3) { *_err3 = _err2__tmp177; return 3; }
            }
            til_Array_delete(&_tmp178);
            til_Str _tmp182;
            til_I64_OverflowError _err0__tmp183;
            til_IndexOutOfBoundsError _err1__tmp183;
            til_AllocError _err2__tmp183;
            til_Array _tmp184;
            til_AllocError _err_alloc__tmp185;
            til_IndexOutOfBoundsError _err_idx__tmp185;
            til_Str _tmp186 = ((til_Str){(til_I64)"format: integer overflow while summing cap for arg ", 51});
            til_Str _tmp187 = til_I64_to_str(til_i);
            int _arr_status__tmp185 = til_Array_new(&_tmp184, &_err_alloc__tmp185, "Str", 2);
            if (_arr_status__tmp185 != 0) {
                *_err3 = _err_alloc__tmp185; return 3;
            }
            _arr_status__tmp185 = til_Array_set(&_err_idx__tmp185, &_tmp184, 0, &_tmp186);
            if (_arr_status__tmp185 != 0) {
                *_err2 = _err_idx__tmp185; return 2;
            }
            _arr_status__tmp185 = til_Array_set(&_err_idx__tmp185, &_tmp184, 1, &_tmp187);
            if (_arr_status__tmp185 != 0) {
                *_err2 = _err_idx__tmp185; return 2;
            }
            int _status__tmp183 = til_format(&_tmp182, &_err0__tmp183, &_err1__tmp183, &_err2__tmp183, ((til_Str){(til_I64)"src/core/str.til:475:48:", 24}), &_tmp184);
            if (_status__tmp183 != 0) {
                if (_status__tmp183 == 1) { *_err1 = _err0__tmp183; return 1; }
                if (_status__tmp183 == 2) { *_err2 = _err1__tmp183; return 2; }
                if (_status__tmp183 == 3) { *_err3 = _err2__tmp183; return 3; }
            }
            til_Array_delete(&_tmp184);
            *_err1 = til_I64_OverflowError_new(_tmp182);
            return 1;
        }
        til_I64_inc(&til_i);
    }
    til_I64 _ret__tmp188;
    til_AllocError _err0__tmp188 = {};
    int _status__tmp188 = til_malloc(&_ret__tmp188, &_err0__tmp188, til_result.cap);
    if (_status__tmp188 == 1) { *_err3 = _err0__tmp188; return 3; }
    til_result.c_string = _ret__tmp188;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Str _tmp190;
        til_I64_OverflowError _err0__tmp191;
        til_IndexOutOfBoundsError _err1__tmp191;
        til_AllocError _err2__tmp191;
        til_Array _tmp192;
        til_AllocError _err_alloc__tmp193;
        til_IndexOutOfBoundsError _err_idx__tmp193;
        til_Str _tmp194 = ((til_Str){(til_I64)"format: malloc failed for cap = ", 32});
        til_Str _tmp195 = til_I64_to_str(til_result.cap);
        int _arr_status__tmp193 = til_Array_new(&_tmp192, &_err_alloc__tmp193, "Str", 2);
        if (_arr_status__tmp193 != 0) {
            *_err3 = _err_alloc__tmp193; return 3;
        }
        _arr_status__tmp193 = til_Array_set(&_err_idx__tmp193, &_tmp192, 0, &_tmp194);
        if (_arr_status__tmp193 != 0) {
            *_err2 = _err_idx__tmp193; return 2;
        }
        _arr_status__tmp193 = til_Array_set(&_err_idx__tmp193, &_tmp192, 1, &_tmp195);
        if (_arr_status__tmp193 != 0) {
            *_err2 = _err_idx__tmp193; return 2;
        }
        int _status__tmp191 = til_format(&_tmp190, &_err0__tmp191, &_err1__tmp191, &_err2__tmp191, ((til_Str){(til_I64)"src/core/str.til:481:37:", 24}), &_tmp192);
        if (_status__tmp191 != 0) {
            if (_status__tmp191 == 1) { *_err1 = _err0__tmp191; return 1; }
            if (_status__tmp191 == 2) { *_err2 = _err1__tmp191; return 2; }
            if (_status__tmp191 == 3) { *_err3 = _err2__tmp191; return 3; }
        }
        til_Array_delete(&_tmp192);
        til_Str _tmp196;
        til_I64_OverflowError _err0__tmp197;
        til_IndexOutOfBoundsError _err1__tmp197;
        til_AllocError _err2__tmp197;
        til_Array _tmp198;
        til_AllocError _err_alloc__tmp199;
        til_IndexOutOfBoundsError _err_idx__tmp199;
        til_Str _tmp200 = ((til_Str){(til_I64)"format: malloc failed for cap = ", 32});
        til_Str _tmp201 = til_I64_to_str(til_result.cap);
        int _arr_status__tmp199 = til_Array_new(&_tmp198, &_err_alloc__tmp199, "Str", 2);
        if (_arr_status__tmp199 != 0) {
            *_err3 = _err_alloc__tmp199; return 3;
        }
        _arr_status__tmp199 = til_Array_set(&_err_idx__tmp199, &_tmp198, 0, &_tmp200);
        if (_arr_status__tmp199 != 0) {
            *_err2 = _err_idx__tmp199; return 2;
        }
        _arr_status__tmp199 = til_Array_set(&_err_idx__tmp199, &_tmp198, 1, &_tmp201);
        if (_arr_status__tmp199 != 0) {
            *_err2 = _err_idx__tmp199; return 2;
        }
        int _status__tmp197 = til_format(&_tmp196, &_err0__tmp197, &_err1__tmp197, &_err2__tmp197, ((til_Str){(til_I64)"src/core/str.til:481:37:", 24}), &_tmp198);
        if (_status__tmp197 != 0) {
            if (_status__tmp197 == 1) { *_err1 = _err0__tmp197; return 1; }
            if (_status__tmp197 == 2) { *_err2 = _err1__tmp197; return 2; }
            if (_status__tmp197 == 3) { *_err3 = _err2__tmp197; return 3; }
        }
        til_Array_delete(&_tmp198);
        *_err3 = til_AllocError_new(_tmp196);
        return 3;
    }
    til_I64 til_offset = 0;
    til_memcpy(til_result.c_string, til_prefix.c_string, til_prefix.cap);
    til_offset = til_prefix.cap;
    til_I64 _for_i_10 = 0;
    til_Str til_s;
    while (til_lt(_for_i_10, til_Array_len((*til_args))).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp203;
        til_s = (til_Str){.c_string = 0, .cap = 0};
        til_IndexOutOfBoundsError _err0__tmp204 = {};
        int _status__tmp204 = til_Array_get(&_err0__tmp204, (*til_args), _for_i_10, (til_Dynamic*)&til_s);
        if (_status__tmp204 == 0) {
        } else if (_status__tmp204 == 1) {
            til_IndexOutOfBoundsError til_err = _err0__tmp204;
            til_Array _tmp206;
            til_AllocError _err_alloc__tmp207;
            til_IndexOutOfBoundsError _err_idx__tmp207;
            til_Str _tmp208 = til_err.msg;
            int _arr_status__tmp207 = til_Array_new(&_tmp206, &_err_alloc__tmp207, "Str", 1);
            if (_arr_status__tmp207 != 0) {
                *_err3 = _err_alloc__tmp207; return 3;
            }
            _arr_status__tmp207 = til_Array_set(&_err_idx__tmp207, &_tmp206, 0, &_tmp208);
            if (_arr_status__tmp207 != 0) {
                *_err2 = _err_idx__tmp207; return 2;
            }
            til_panic(((til_Str){(til_I64)"src/core/str.til:488:5:", 23}), &_tmp206);
            til_Array_delete(&_tmp206);
        }
        til_memcpy(til_add(til_result.c_string, til_offset), til_s.c_string, til_s.cap);
        til_offset = til_add(til_offset, til_s.cap);
        _for_i_10 = til_add(_for_i_10, 1);
        goto _end_catches__tmp203;
_catch_IndexOutOfBoundsError__tmp203: {
        til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp203;
        til_Array _tmp210;
        til_AllocError _err_alloc__tmp211;
        til_IndexOutOfBoundsError _err_idx__tmp211;
        til_Str _tmp212 = til_err.msg;
        int _arr_status__tmp211 = til_Array_new(&_tmp210, &_err_alloc__tmp211, "Str", 1);
        if (_arr_status__tmp211 != 0) {
            *_err3 = _err_alloc__tmp211; return 3;
        }
        _arr_status__tmp211 = til_Array_set(&_err_idx__tmp211, &_tmp210, 0, &_tmp212);
        if (_arr_status__tmp211 != 0) {
            *_err2 = _err_idx__tmp211; return 2;
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:488:5:", 23}), &_tmp210);
        til_Array_delete(&_tmp210);
        goto _end_catches__tmp203;
        }
_end_catches__tmp203:;
    }
    *_ret = til_result;
    return 0;
}

void til_test(const til_Str til_loc_str, const til_Bool til_cond, const til_Str til_msg) {
    til_assertm(til_loc_str, til_cond, til_msg);
}

void til_assert_eq(const til_Str til_loc_str, const til_I64 til_a, const til_I64 til_b) {
    if (til_not(til_I64_eq(til_a, til_b)).data) {
        til_Array _tmp216;
        til_AllocError _err_alloc__tmp217;
        til_IndexOutOfBoundsError _err_idx__tmp217;
        til_Str _tmp218 = til_loc_str;
        til_Str _tmp219 = ((til_Str){(til_I64)"assert_eq failed: expected '", 28});
        til_Str _tmp220 = til_I64_to_str(til_a);
        til_Str _tmp221 = ((til_Str){(til_I64)"', found '", 10});
        til_Str _tmp222 = til_I64_to_str(til_b);
        til_Str _tmp223 = ((til_Str){(til_I64)"'", 1});
        int _arr_status__tmp217 = til_Array_new(&_tmp216, &_err_alloc__tmp217, "Str", 6);
        if (_arr_status__tmp217 != 0) {
        }
        _arr_status__tmp217 = til_Array_set(&_err_idx__tmp217, &_tmp216, 0, &_tmp218);
        if (_arr_status__tmp217 != 0) {
        }
        _arr_status__tmp217 = til_Array_set(&_err_idx__tmp217, &_tmp216, 1, &_tmp219);
        if (_arr_status__tmp217 != 0) {
        }
        _arr_status__tmp217 = til_Array_set(&_err_idx__tmp217, &_tmp216, 2, &_tmp220);
        if (_arr_status__tmp217 != 0) {
        }
        _arr_status__tmp217 = til_Array_set(&_err_idx__tmp217, &_tmp216, 3, &_tmp221);
        if (_arr_status__tmp217 != 0) {
        }
        _arr_status__tmp217 = til_Array_set(&_err_idx__tmp217, &_tmp216, 4, &_tmp222);
        if (_arr_status__tmp217 != 0) {
        }
        _arr_status__tmp217 = til_Array_set(&_err_idx__tmp217, &_tmp216, 5, &_tmp223);
        if (_arr_status__tmp217 != 0) {
        }
        til_println(&_tmp216);
        til_Array_delete(&_tmp216);
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

int til_Array_new(til_Array* _ret, til_AllocError* _err1, const til_Type til_T, const til_I64 til_capacity) {
    til_Array til_arr = {.type_name = ((til_Str){(til_I64)"", 0}), .type_size = 0, .ptr = 0, ._len = 0};
    til_arr.type_name = ((til_Str){(til_I64)"T", 1});
    til_arr.type_size = til_size_of(((til_Str){(til_I64)til_T, strlen(til_T)}));
    const til_I64 til_size_bytes = til_mul(til_capacity, til_arr.type_size);
    til_I64 _ret__tmp237;
    til_AllocError _err0__tmp237 = {};
    int _status__tmp237 = til_malloc(&_ret__tmp237, &_err0__tmp237, til_size_bytes);
    if (_status__tmp237 == 1) { *_err1 = _err0__tmp237; return 1; }
    til_arr.ptr = _ret__tmp237;
    til_U8 _tmp238;
    til_U8_OverflowError _err0__tmp239;
    int _status__tmp239 = til_U8_from_i64(&_tmp238, &_err0__tmp239, 0);
    if (_status__tmp239 != 0) {
    }
    til_memset(til_arr.ptr, _tmp238, til_size_bytes);
    til_arr._len = til_capacity;
    *_ret = til_arr;
    return 0;
}

int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array til_self, const til_I64 til_index, til_Dynamic* til_T) {
    if (til_I64_gteq(til_index, til_self._len).data) {
        til_Str _tmp242;
        til_I64_OverflowError _err0__tmp243;
        til_IndexOutOfBoundsError _err1__tmp243;
        til_AllocError _err2__tmp243;
        til_Array _tmp244;
        til_AllocError _err_alloc__tmp245;
        til_IndexOutOfBoundsError _err_idx__tmp245;
        til_Str _tmp246 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        int _arr_status__tmp245 = til_Array_new(&_tmp244, &_err_alloc__tmp245, "Str", 1);
        if (_arr_status__tmp245 != 0) {
        }
        _arr_status__tmp245 = til_Array_set(&_err_idx__tmp245, &_tmp244, 0, &_tmp246);
        if (_arr_status__tmp245 != 0) {
            *_err1 = _err_idx__tmp245; return 1;
        }
        int _status__tmp243 = til_format(&_tmp242, &_err0__tmp243, &_err1__tmp243, &_err2__tmp243, ((til_Str){(til_I64)"src/core/array.til:41:52:", 25}), &_tmp244);
        if (_status__tmp243 != 0) {
            if (_status__tmp243 == 2) { *_err1 = _err1__tmp243; return 1; }
        }
        til_Array_delete(&_tmp244);
        til_Str _tmp247;
        til_I64_OverflowError _err0__tmp248;
        til_IndexOutOfBoundsError _err1__tmp248;
        til_AllocError _err2__tmp248;
        til_Array _tmp249;
        til_AllocError _err_alloc__tmp250;
        til_IndexOutOfBoundsError _err_idx__tmp250;
        til_Str _tmp251 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        int _arr_status__tmp250 = til_Array_new(&_tmp249, &_err_alloc__tmp250, "Str", 1);
        if (_arr_status__tmp250 != 0) {
        }
        _arr_status__tmp250 = til_Array_set(&_err_idx__tmp250, &_tmp249, 0, &_tmp251);
        if (_arr_status__tmp250 != 0) {
            *_err1 = _err_idx__tmp250; return 1;
        }
        int _status__tmp248 = til_format(&_tmp247, &_err0__tmp248, &_err1__tmp248, &_err2__tmp248, ((til_Str){(til_I64)"src/core/array.til:41:52:", 25}), &_tmp249);
        if (_status__tmp248 != 0) {
            if (_status__tmp248 == 2) { *_err1 = _err1__tmp248; return 1; }
        }
        til_Array_delete(&_tmp249);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp247);
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_I64_gteq(til_index, til_self->_len).data) {
        til_Str _tmp254;
        til_I64_OverflowError _err0__tmp255;
        til_IndexOutOfBoundsError _err1__tmp255;
        til_AllocError _err2__tmp255;
        til_Array _tmp256;
        til_AllocError _err_alloc__tmp257;
        til_IndexOutOfBoundsError _err_idx__tmp257;
        til_Str _tmp258 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        int _arr_status__tmp257 = til_Array_new(&_tmp256, &_err_alloc__tmp257, "Str", 1);
        if (_arr_status__tmp257 != 0) {
        }
        _arr_status__tmp257 = til_Array_set(&_err_idx__tmp257, &_tmp256, 0, &_tmp258);
        if (_arr_status__tmp257 != 0) {
            *_err1 = _err_idx__tmp257; return 1;
        }
        int _status__tmp255 = til_format(&_tmp254, &_err0__tmp255, &_err1__tmp255, &_err2__tmp255, ((til_Str){(til_I64)"src/core/array.til:56:52:", 25}), &_tmp256);
        if (_status__tmp255 != 0) {
            if (_status__tmp255 == 2) { *_err1 = _err1__tmp255; return 1; }
        }
        til_Array_delete(&_tmp256);
        til_Str _tmp259;
        til_I64_OverflowError _err0__tmp260;
        til_IndexOutOfBoundsError _err1__tmp260;
        til_AllocError _err2__tmp260;
        til_Array _tmp261;
        til_AllocError _err_alloc__tmp262;
        til_IndexOutOfBoundsError _err_idx__tmp262;
        til_Str _tmp263 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        int _arr_status__tmp262 = til_Array_new(&_tmp261, &_err_alloc__tmp262, "Str", 1);
        if (_arr_status__tmp262 != 0) {
        }
        _arr_status__tmp262 = til_Array_set(&_err_idx__tmp262, &_tmp261, 0, &_tmp263);
        if (_arr_status__tmp262 != 0) {
            *_err1 = _err_idx__tmp262; return 1;
        }
        int _status__tmp260 = til_format(&_tmp259, &_err0__tmp260, &_err1__tmp260, &_err2__tmp260, ((til_Str){(til_I64)"src/core/array.til:56:52:", 25}), &_tmp261);
        if (_status__tmp260 != 0) {
            if (_status__tmp260 == 2) { *_err1 = _err1__tmp260; return 1; }
        }
        til_Array_delete(&_tmp261);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp259);
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
    til_I64 _ret__tmp283;
    til_AllocError _err0__tmp283 = {};
    int _status__tmp283 = til_malloc(&_ret__tmp283, &_err0__tmp283, til_size_bytes);
    if (_status__tmp283 == 1) { *_err1 = _err0__tmp283; return 1; }
    til_vec.ptr = _ret__tmp283;
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
            til_Array _tmp287;
            til_AllocError _err_alloc__tmp288;
            til_IndexOutOfBoundsError _err_idx__tmp288;
            til_Str _tmp289 = ((til_Str){(til_I64)"Vec.push: capacity exceeded Vec.MAX_CAP", 39});
            int _arr_status__tmp288 = til_Array_new(&_tmp287, &_err_alloc__tmp288, "Str", 1);
            if (_arr_status__tmp288 != 0) {
                *_err1 = _err_alloc__tmp288; return 1;
            }
            _arr_status__tmp288 = til_Array_set(&_err_idx__tmp288, &_tmp287, 0, &_tmp289);
            if (_arr_status__tmp288 != 0) {
            }
            til_panic(((til_Str){(til_I64)"src/core/vec.til:63:23:", 23}), &_tmp287);
            til_Array_delete(&_tmp287);
        }
        til_I64 _ret__tmp290;
        til_I64 til_new_ptr;
        til_AllocError _err0__tmp290 = {};
        int _status__tmp290 = til_malloc(&_ret__tmp290, &_err0__tmp290, til_mul(til_new_cap, til_self->type_size));
        if (_status__tmp290 == 1) { *_err1 = _err0__tmp290; return 1; }
        til_new_ptr = _ret__tmp290;
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
        til_Str _tmp293;
        til_I64_OverflowError _err0__tmp294;
        til_IndexOutOfBoundsError _err1__tmp294;
        til_AllocError _err2__tmp294;
        til_Array _tmp295;
        til_AllocError _err_alloc__tmp296;
        til_IndexOutOfBoundsError _err_idx__tmp296;
        til_Str _tmp297 = ((til_Str){(til_I64)"Vec.get: index out of bounds", 28});
        int _arr_status__tmp296 = til_Array_new(&_tmp295, &_err_alloc__tmp296, "Str", 1);
        if (_arr_status__tmp296 != 0) {
        }
        _arr_status__tmp296 = til_Array_set(&_err_idx__tmp296, &_tmp295, 0, &_tmp297);
        if (_arr_status__tmp296 != 0) {
            *_err1 = _err_idx__tmp296; return 1;
        }
        int _status__tmp294 = til_format(&_tmp293, &_err0__tmp294, &_err1__tmp294, &_err2__tmp294, ((til_Str){(til_I64)"src/core/vec.til:81:52:", 23}), &_tmp295);
        if (_status__tmp294 != 0) {
            if (_status__tmp294 == 2) { *_err1 = _err1__tmp294; return 1; }
        }
        til_Array_delete(&_tmp295);
        til_Str _tmp298;
        til_I64_OverflowError _err0__tmp299;
        til_IndexOutOfBoundsError _err1__tmp299;
        til_AllocError _err2__tmp299;
        til_Array _tmp300;
        til_AllocError _err_alloc__tmp301;
        til_IndexOutOfBoundsError _err_idx__tmp301;
        til_Str _tmp302 = ((til_Str){(til_I64)"Vec.get: index out of bounds", 28});
        int _arr_status__tmp301 = til_Array_new(&_tmp300, &_err_alloc__tmp301, "Str", 1);
        if (_arr_status__tmp301 != 0) {
        }
        _arr_status__tmp301 = til_Array_set(&_err_idx__tmp301, &_tmp300, 0, &_tmp302);
        if (_arr_status__tmp301 != 0) {
            *_err1 = _err_idx__tmp301; return 1;
        }
        int _status__tmp299 = til_format(&_tmp298, &_err0__tmp299, &_err1__tmp299, &_err2__tmp299, ((til_Str){(til_I64)"src/core/vec.til:81:52:", 23}), &_tmp300);
        if (_status__tmp299 != 0) {
            if (_status__tmp299 == 2) { *_err1 = _err1__tmp299; return 1; }
        }
        til_Array_delete(&_tmp300);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp298);
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
    til_I64 _ret__tmp310;
    til_AllocError _err0__tmp310 = {};
    int _status__tmp310 = til_malloc(&_ret__tmp310, &_err0__tmp310, til_cloned.cap);
    if (_status__tmp310 == 1) { *_err1 = _err0__tmp310; return 1; }
    til_cloned.c_string = _ret__tmp310;
    if (til_I64_eq(til_NULL, til_cloned.c_string).data) {
        til_Str _tmp312;
        til_I64_OverflowError _err0__tmp313;
        til_IndexOutOfBoundsError _err1__tmp313;
        til_AllocError _err2__tmp313;
        til_Array _tmp314;
        til_AllocError _err_alloc__tmp315;
        til_IndexOutOfBoundsError _err_idx__tmp315;
        til_Str _tmp316 = ((til_Str){(til_I64)"Str.clone: malloc failed for ", 29});
        til_Str _tmp317 = til_I64_to_str(til_cloned.cap);
        til_Str _tmp318 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp315 = til_Array_new(&_tmp314, &_err_alloc__tmp315, "Str", 3);
        if (_arr_status__tmp315 != 0) {
            *_err1 = _err_alloc__tmp315; return 1;
        }
        _arr_status__tmp315 = til_Array_set(&_err_idx__tmp315, &_tmp314, 0, &_tmp316);
        if (_arr_status__tmp315 != 0) {
        }
        _arr_status__tmp315 = til_Array_set(&_err_idx__tmp315, &_tmp314, 1, &_tmp317);
        if (_arr_status__tmp315 != 0) {
        }
        _arr_status__tmp315 = til_Array_set(&_err_idx__tmp315, &_tmp314, 2, &_tmp318);
        if (_arr_status__tmp315 != 0) {
        }
        int _status__tmp313 = til_format(&_tmp312, &_err0__tmp313, &_err1__tmp313, &_err2__tmp313, ((til_Str){(til_I64)"src/core/str.til:46:41:", 23}), &_tmp314);
        if (_status__tmp313 != 0) {
            if (_status__tmp313 == 3) { *_err1 = _err2__tmp313; return 1; }
        }
        til_Array_delete(&_tmp314);
        til_Str _tmp319;
        til_I64_OverflowError _err0__tmp320;
        til_IndexOutOfBoundsError _err1__tmp320;
        til_AllocError _err2__tmp320;
        til_Array _tmp321;
        til_AllocError _err_alloc__tmp322;
        til_IndexOutOfBoundsError _err_idx__tmp322;
        til_Str _tmp323 = ((til_Str){(til_I64)"Str.clone: malloc failed for ", 29});
        til_Str _tmp324 = til_I64_to_str(til_cloned.cap);
        til_Str _tmp325 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp322 = til_Array_new(&_tmp321, &_err_alloc__tmp322, "Str", 3);
        if (_arr_status__tmp322 != 0) {
            *_err1 = _err_alloc__tmp322; return 1;
        }
        _arr_status__tmp322 = til_Array_set(&_err_idx__tmp322, &_tmp321, 0, &_tmp323);
        if (_arr_status__tmp322 != 0) {
        }
        _arr_status__tmp322 = til_Array_set(&_err_idx__tmp322, &_tmp321, 1, &_tmp324);
        if (_arr_status__tmp322 != 0) {
        }
        _arr_status__tmp322 = til_Array_set(&_err_idx__tmp322, &_tmp321, 2, &_tmp325);
        if (_arr_status__tmp322 != 0) {
        }
        int _status__tmp320 = til_format(&_tmp319, &_err0__tmp320, &_err1__tmp320, &_err2__tmp320, ((til_Str){(til_I64)"src/core/str.til:46:41:", 23}), &_tmp321);
        if (_status__tmp320 != 0) {
            if (_status__tmp320 == 3) { *_err1 = _err2__tmp320; return 1; }
        }
        til_Array_delete(&_tmp321);
        *_err1 = til_AllocError_new(_tmp319);
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
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp344;
    if (til_I64_eq(til_Str_len(til_from), 0).data) {
        til_Str _ret__tmp346;
        til_AllocError _err0__tmp346 = {};
        int _status__tmp346 = til_Str_clone(&_ret__tmp346, &_err0__tmp346, til_self);
        if (_status__tmp346 == 1) { *_err1 = _err0__tmp346; return 1; }
        *_ret = _ret__tmp346;
        return 0;
    }
    if (til_I64_eq(til_n, 0).data) {
        til_Str _ret__tmp348;
        til_AllocError _err0__tmp348 = {};
        int _status__tmp348 = til_Str_clone(&_ret__tmp348, &_err0__tmp348, til_self);
        if (_status__tmp348 == 1) { *_err1 = _err0__tmp348; return 1; }
        *_ret = _ret__tmp348;
        return 0;
    }
    til_I64 til_idx = til_Str_find(til_self, til_from);
    if (til_lt(til_idx, 0).data) {
        til_Str _ret__tmp350;
        til_AllocError _err0__tmp350 = {};
        int _status__tmp350 = til_Str_clone(&_ret__tmp350, &_err0__tmp350, til_self);
        if (_status__tmp350 == 1) { *_err1 = _err0__tmp350; return 1; }
        *_ret = _ret__tmp350;
        return 0;
    }
    til_Str _ret__tmp351;
    til_Str til_prefix;
    til_IndexOutOfBoundsError _err0__tmp351 = {};
    til_AllocError _err1__tmp351 = {};
    int _status__tmp351 = til_get_substr(&_ret__tmp351, &_err0__tmp351, &_err1__tmp351, til_self, 0, til_idx);
    if (_status__tmp351 == 2) { *_err1 = _err1__tmp351; return 1; }
    til_prefix = _ret__tmp351;
    til_Str _ret__tmp352;
    til_Str til_suffix;
    til_IndexOutOfBoundsError _err0__tmp352 = {};
    til_AllocError _err1__tmp352 = {};
    int _status__tmp352 = til_get_substr(&_ret__tmp352, &_err0__tmp352, &_err1__tmp352, til_self, til_add(til_idx, til_Str_len(til_from)), til_Str_len(til_self));
    if (_status__tmp352 == 2) { *_err1 = _err1__tmp352; return 1; }
    til_suffix = _ret__tmp352;
    til_Str til_result = til_concat(til_concat(til_prefix, til_to), til_suffix);
    til_Str til_rest;
    if (til_gt(til_n, 1).data) {
        til_Str _ret__tmp354;
        til_Str til_rest;
        til_AllocError _err0__tmp354 = {};
        int _status__tmp354 = til_Str_replacen(&_ret__tmp354, &_err0__tmp354, til_suffix, til_from, til_to, til_sub(til_n, 1));
        if (_status__tmp354 == 1) { *_err1 = _err0__tmp354; return 1; }
        til_rest = _ret__tmp354;
        til_result = til_concat(til_concat(til_prefix, til_to), til_rest);
    }
    *_ret = til_result;
    return 0;
    goto _end_catches__tmp344;
_catch_IndexOutOfBoundsError__tmp344: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp344;
    til_Str _ret__tmp356;
    til_AllocError _err0__tmp356 = {};
    int _status__tmp356 = til_Str_clone(&_ret__tmp356, &_err0__tmp356, til_self);
    if (_status__tmp356 == 1) { *_err1 = _err0__tmp356; return 1; }
    til_result = _ret__tmp356;
    goto _end_catches__tmp344;
    }
_end_catches__tmp344:;
}

til_U8_OverflowError til_U8_OverflowError_new(const til_Str til_msg) {
    til_U8_OverflowError til_err = {.msg = ((til_Str){(til_I64)"", 0})};
    til_err.msg = til_msg;
    return til_err;
}

til_Bool til_U8_eq(const til_U8 til_self, const til_U8 til_other) {
    return til_I64_eq(til_U8_to_i64(til_self), til_U8_to_i64(til_other));
}

til_I64 til_U8_to_i64(const til_U8 til_self) {
    return til_u8_to_i64(til_self);
}

int til_U8_from_i64(til_U8* _ret, til_U8_OverflowError* _err1, const til_I64 til_self) {
    if (til_lt(til_self, 0).data) {
        til_Str _tmp362;
        til_I64_OverflowError _err0__tmp363;
        til_IndexOutOfBoundsError _err1__tmp363;
        til_AllocError _err2__tmp363;
        til_Array _tmp364;
        til_AllocError _err_alloc__tmp365;
        til_IndexOutOfBoundsError _err_idx__tmp365;
        til_Str _tmp366 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        int _arr_status__tmp365 = til_Array_new(&_tmp364, &_err_alloc__tmp365, "Str", 1);
        if (_arr_status__tmp365 != 0) {
        }
        _arr_status__tmp365 = til_Array_set(&_err_idx__tmp365, &_tmp364, 0, &_tmp366);
        if (_arr_status__tmp365 != 0) {
        }
        int _status__tmp363 = til_format(&_tmp362, &_err0__tmp363, &_err1__tmp363, &_err2__tmp363, ((til_Str){(til_I64)"src/core/u8.til:56:47:", 22}), &_tmp364);
        if (_status__tmp363 != 0) {
        }
        til_Array_delete(&_tmp364);
        til_Str _tmp367;
        til_I64_OverflowError _err0__tmp368;
        til_IndexOutOfBoundsError _err1__tmp368;
        til_AllocError _err2__tmp368;
        til_Array _tmp369;
        til_AllocError _err_alloc__tmp370;
        til_IndexOutOfBoundsError _err_idx__tmp370;
        til_Str _tmp371 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        int _arr_status__tmp370 = til_Array_new(&_tmp369, &_err_alloc__tmp370, "Str", 1);
        if (_arr_status__tmp370 != 0) {
        }
        _arr_status__tmp370 = til_Array_set(&_err_idx__tmp370, &_tmp369, 0, &_tmp371);
        if (_arr_status__tmp370 != 0) {
        }
        int _status__tmp368 = til_format(&_tmp367, &_err0__tmp368, &_err1__tmp368, &_err2__tmp368, ((til_Str){(til_I64)"src/core/u8.til:56:47:", 22}), &_tmp369);
        if (_status__tmp368 != 0) {
        }
        til_Array_delete(&_tmp369);
        *_err1 = til_U8_OverflowError_new(_tmp367);
        return 1;
    }
    if (til_gt(til_self, til_MAX_U8).data) {
        til_Str _tmp373;
        til_I64_OverflowError _err0__tmp374;
        til_IndexOutOfBoundsError _err1__tmp374;
        til_AllocError _err2__tmp374;
        til_Array _tmp375;
        til_AllocError _err_alloc__tmp376;
        til_IndexOutOfBoundsError _err_idx__tmp376;
        til_Str _tmp377 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp378 = ((til_Str){(til_I64)"255", 3});
        int _arr_status__tmp376 = til_Array_new(&_tmp375, &_err_alloc__tmp376, "Str", 2);
        if (_arr_status__tmp376 != 0) {
        }
        _arr_status__tmp376 = til_Array_set(&_err_idx__tmp376, &_tmp375, 0, &_tmp377);
        if (_arr_status__tmp376 != 0) {
        }
        _arr_status__tmp376 = til_Array_set(&_err_idx__tmp376, &_tmp375, 1, &_tmp378);
        if (_arr_status__tmp376 != 0) {
        }
        int _status__tmp374 = til_format(&_tmp373, &_err0__tmp374, &_err1__tmp374, &_err2__tmp374, ((til_Str){(til_I64)"src/core/u8.til:59:47:", 22}), &_tmp375);
        if (_status__tmp374 != 0) {
        }
        til_Array_delete(&_tmp375);
        til_Str _tmp379;
        til_I64_OverflowError _err0__tmp380;
        til_IndexOutOfBoundsError _err1__tmp380;
        til_AllocError _err2__tmp380;
        til_Array _tmp381;
        til_AllocError _err_alloc__tmp382;
        til_IndexOutOfBoundsError _err_idx__tmp382;
        til_Str _tmp383 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp384 = ((til_Str){(til_I64)"255", 3});
        int _arr_status__tmp382 = til_Array_new(&_tmp381, &_err_alloc__tmp382, "Str", 2);
        if (_arr_status__tmp382 != 0) {
        }
        _arr_status__tmp382 = til_Array_set(&_err_idx__tmp382, &_tmp381, 0, &_tmp383);
        if (_arr_status__tmp382 != 0) {
        }
        _arr_status__tmp382 = til_Array_set(&_err_idx__tmp382, &_tmp381, 1, &_tmp384);
        if (_arr_status__tmp382 != 0) {
        }
        int _status__tmp380 = til_format(&_tmp379, &_err0__tmp380, &_err1__tmp380, &_err2__tmp380, ((til_Str){(til_I64)"src/core/u8.til:59:47:", 22}), &_tmp381);
        if (_status__tmp380 != 0) {
        }
        til_Array_delete(&_tmp381);
        *_err1 = til_U8_OverflowError_new(_tmp379);
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
