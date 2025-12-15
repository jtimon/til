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
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp63};
        return 1;
    }
    if (til_lt(til_end, 0).data) {
        til_Str _tmp71;
        til_I64_OverflowError _err0__tmp72;
        til_IndexOutOfBoundsError _err1__tmp72;
        til_AllocError _err2__tmp72;
        til_Array _tmp73;
        til_AllocError _err_alloc__tmp74;
        til_IndexOutOfBoundsError _err_idx__tmp74;
        til_Str _tmp75 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp76 = til_I64_to_str(til_end);
        til_Str _tmp77 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp74 = til_Array_new(&_tmp73, &_err_alloc__tmp74, "Str", 3);
        if (_arr_status__tmp74 != 0) {
            *_err2 = _err_alloc__tmp74; return 2;
        }
        _arr_status__tmp74 = til_Array_set(&_err_idx__tmp74, &_tmp73, 0, &_tmp75);
        if (_arr_status__tmp74 != 0) {
            *_err1 = _err_idx__tmp74; return 1;
        }
        _arr_status__tmp74 = til_Array_set(&_err_idx__tmp74, &_tmp73, 1, &_tmp76);
        if (_arr_status__tmp74 != 0) {
            *_err1 = _err_idx__tmp74; return 1;
        }
        _arr_status__tmp74 = til_Array_set(&_err_idx__tmp74, &_tmp73, 2, &_tmp77);
        if (_arr_status__tmp74 != 0) {
            *_err1 = _err_idx__tmp74; return 1;
        }
        int _status__tmp72 = til_format(&_tmp71, &_err0__tmp72, &_err1__tmp72, &_err2__tmp72, ((til_Str){(til_I64)"src/core/str.til:371:48:", 24}), &_tmp73);
        if (_status__tmp72 != 0) {
            if (_status__tmp72 == 2) { *_err1 = _err1__tmp72; return 1; }
            if (_status__tmp72 == 3) { *_err2 = _err2__tmp72; return 2; }
        }
        til_Array_delete(&_tmp73);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp71};
        return 1;
    }
    if (til_gt(til_start, til_end).data) {
        til_Str _tmp79;
        til_I64_OverflowError _err0__tmp80;
        til_IndexOutOfBoundsError _err1__tmp80;
        til_AllocError _err2__tmp80;
        til_Array _tmp81;
        til_AllocError _err_alloc__tmp82;
        til_IndexOutOfBoundsError _err_idx__tmp82;
        til_Str _tmp83 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp84 = til_I64_to_str(til_start);
        til_Str _tmp85 = ((til_Str){(til_I64)" is greater than end index ", 27});
        til_Str _tmp86 = til_I64_to_str(til_end);
        int _arr_status__tmp82 = til_Array_new(&_tmp81, &_err_alloc__tmp82, "Str", 4);
        if (_arr_status__tmp82 != 0) {
            *_err2 = _err_alloc__tmp82; return 2;
        }
        _arr_status__tmp82 = til_Array_set(&_err_idx__tmp82, &_tmp81, 0, &_tmp83);
        if (_arr_status__tmp82 != 0) {
            *_err1 = _err_idx__tmp82; return 1;
        }
        _arr_status__tmp82 = til_Array_set(&_err_idx__tmp82, &_tmp81, 1, &_tmp84);
        if (_arr_status__tmp82 != 0) {
            *_err1 = _err_idx__tmp82; return 1;
        }
        _arr_status__tmp82 = til_Array_set(&_err_idx__tmp82, &_tmp81, 2, &_tmp85);
        if (_arr_status__tmp82 != 0) {
            *_err1 = _err_idx__tmp82; return 1;
        }
        _arr_status__tmp82 = til_Array_set(&_err_idx__tmp82, &_tmp81, 3, &_tmp86);
        if (_arr_status__tmp82 != 0) {
            *_err1 = _err_idx__tmp82; return 1;
        }
        int _status__tmp80 = til_format(&_tmp79, &_err0__tmp80, &_err1__tmp80, &_err2__tmp80, ((til_Str){(til_I64)"src/core/str.til:374:48:", 24}), &_tmp81);
        if (_status__tmp80 != 0) {
            if (_status__tmp80 == 2) { *_err1 = _err1__tmp80; return 1; }
            if (_status__tmp80 == 3) { *_err2 = _err2__tmp80; return 2; }
        }
        til_Array_delete(&_tmp81);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp79};
        return 1;
    }
    if (til_gt(til_end, til_Str_len(til_s)).data) {
        til_Str _tmp88;
        til_I64_OverflowError _err0__tmp89;
        til_IndexOutOfBoundsError _err1__tmp89;
        til_AllocError _err2__tmp89;
        til_Array _tmp90;
        til_AllocError _err_alloc__tmp91;
        til_IndexOutOfBoundsError _err_idx__tmp91;
        til_Str _tmp92 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp93 = til_I64_to_str(til_end);
        til_Str _tmp94 = ((til_Str){(til_I64)" is greater than string length ", 31});
        til_Str _tmp95 = til_I64_to_str(til_Str_len(til_s));
        int _arr_status__tmp91 = til_Array_new(&_tmp90, &_err_alloc__tmp91, "Str", 4);
        if (_arr_status__tmp91 != 0) {
            *_err2 = _err_alloc__tmp91; return 2;
        }
        _arr_status__tmp91 = til_Array_set(&_err_idx__tmp91, &_tmp90, 0, &_tmp92);
        if (_arr_status__tmp91 != 0) {
            *_err1 = _err_idx__tmp91; return 1;
        }
        _arr_status__tmp91 = til_Array_set(&_err_idx__tmp91, &_tmp90, 1, &_tmp93);
        if (_arr_status__tmp91 != 0) {
            *_err1 = _err_idx__tmp91; return 1;
        }
        _arr_status__tmp91 = til_Array_set(&_err_idx__tmp91, &_tmp90, 2, &_tmp94);
        if (_arr_status__tmp91 != 0) {
            *_err1 = _err_idx__tmp91; return 1;
        }
        _arr_status__tmp91 = til_Array_set(&_err_idx__tmp91, &_tmp90, 3, &_tmp95);
        if (_arr_status__tmp91 != 0) {
            *_err1 = _err_idx__tmp91; return 1;
        }
        int _status__tmp89 = til_format(&_tmp88, &_err0__tmp89, &_err1__tmp89, &_err2__tmp89, ((til_Str){(til_I64)"src/core/str.til:377:48:", 24}), &_tmp90);
        if (_status__tmp89 != 0) {
            if (_status__tmp89 == 2) { *_err1 = _err1__tmp89; return 1; }
            if (_status__tmp89 == 3) { *_err2 = _err2__tmp89; return 2; }
        }
        til_Array_delete(&_tmp90);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp88};
        return 1;
    }
    if (til_I64_eq(til_start, til_end).data) {
        til_Str _tmp97;
        til_I64_OverflowError _err0__tmp98;
        til_IndexOutOfBoundsError _err1__tmp98;
        til_AllocError _err2__tmp98;
        til_Array _tmp99;
        til_AllocError _err_alloc__tmp100;
        til_IndexOutOfBoundsError _err_idx__tmp100;
        til_Str _tmp101 = ((til_Str){(til_I64)"get_substr: start and end are the same (", 40});
        til_Str _tmp102 = til_I64_to_str(til_start);
        til_Str _tmp103 = ((til_Str){(til_I64)"), no substring", 15});
        int _arr_status__tmp100 = til_Array_new(&_tmp99, &_err_alloc__tmp100, "Str", 3);
        if (_arr_status__tmp100 != 0) {
            *_err2 = _err_alloc__tmp100; return 2;
        }
        _arr_status__tmp100 = til_Array_set(&_err_idx__tmp100, &_tmp99, 0, &_tmp101);
        if (_arr_status__tmp100 != 0) {
            *_err1 = _err_idx__tmp100; return 1;
        }
        _arr_status__tmp100 = til_Array_set(&_err_idx__tmp100, &_tmp99, 1, &_tmp102);
        if (_arr_status__tmp100 != 0) {
            *_err1 = _err_idx__tmp100; return 1;
        }
        _arr_status__tmp100 = til_Array_set(&_err_idx__tmp100, &_tmp99, 2, &_tmp103);
        if (_arr_status__tmp100 != 0) {
            *_err1 = _err_idx__tmp100; return 1;
        }
        int _status__tmp98 = til_format(&_tmp97, &_err0__tmp98, &_err1__tmp98, &_err2__tmp98, ((til_Str){(til_I64)"src/core/str.til:380:48:", 24}), &_tmp99);
        if (_status__tmp98 != 0) {
            if (_status__tmp98 == 2) { *_err1 = _err1__tmp98; return 1; }
            if (_status__tmp98 == 3) { *_err2 = _err2__tmp98; return 2; }
        }
        til_Array_delete(&_tmp99);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp97};
        return 1;
    }
    til_Str til_substr = {.c_string = 0, .cap = 0};
    til_substr.cap = til_sub(til_end, til_start);
    til_I64 _ret__tmp104;
    til_AllocError _err0__tmp104 = {};
    int _status__tmp104 = til_malloc(&_ret__tmp104, &_err0__tmp104, til_substr.cap);
    if (_status__tmp104 == 1) { *_err2 = _err0__tmp104; return 2; }
    til_substr.c_string = _ret__tmp104;
    if (til_I64_eq(til_NULL, til_substr.c_string).data) {
        til_Str _tmp106;
        til_I64_OverflowError _err0__tmp107;
        til_IndexOutOfBoundsError _err1__tmp107;
        til_AllocError _err2__tmp107;
        til_Array _tmp108;
        til_AllocError _err_alloc__tmp109;
        til_IndexOutOfBoundsError _err_idx__tmp109;
        til_Str _tmp110 = ((til_Str){(til_I64)"Str.get_substr: failed to allocate ", 35});
        til_Str _tmp111 = til_I64_to_str(til_substr.cap);
        til_Str _tmp112 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp109 = til_Array_new(&_tmp108, &_err_alloc__tmp109, "Str", 3);
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
        int _status__tmp107 = til_format(&_tmp106, &_err0__tmp107, &_err1__tmp107, &_err2__tmp107, ((til_Str){(til_I64)"src/core/str.til:387:37:", 24}), &_tmp108);
        if (_status__tmp107 != 0) {
            if (_status__tmp107 == 2) { *_err1 = _err1__tmp107; return 1; }
            if (_status__tmp107 == 3) { *_err2 = _err2__tmp107; return 2; }
        }
        til_Array_delete(&_tmp108);
        *_err2 = (til_AllocError){.msg = _tmp106};
        return 2;
    }
    til_memcpy(til_substr.c_string, til_add(til_s.c_string, til_start), til_substr.cap);
    *_ret = til_substr;
    return 0;
}

til_Str til_concat(const til_Str til_a, const til_Str til_b) {
    til_AllocError _thrown_AllocError__tmp113;
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_add(til_a.cap, til_b.cap);
    if (til_lt(til_result.cap, til_a.cap).data) {
        til_Array _tmp115;
        til_AllocError _err_alloc__tmp116;
        til_IndexOutOfBoundsError _err_idx__tmp116;
        til_Str _tmp117 = ((til_Str){(til_I64)"concat: integer overflow", 24});
        int _arr_status__tmp116 = til_Array_new(&_tmp115, &_err_alloc__tmp116, "Str", 1);
        if (_arr_status__tmp116 != 0) {
        }
        _arr_status__tmp116 = til_Array_set(&_err_idx__tmp116, &_tmp115, 0, &_tmp117);
        if (_arr_status__tmp116 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:447:15:", 24}), &_tmp115);
        til_Array_delete(&_tmp115);
    }
    til_I64 _ret__tmp118;
    til_AllocError _err0__tmp118 = {};
    int _status__tmp118 = til_malloc(&_ret__tmp118, &_err0__tmp118, til_result.cap);
    if (_status__tmp118 == 1) { _thrown_AllocError__tmp113 = _err0__tmp118; goto _catch_AllocError__tmp113; }
    til_result.c_string = _ret__tmp118;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Array _tmp120;
        til_AllocError _err_alloc__tmp121;
        til_IndexOutOfBoundsError _err_idx__tmp121;
        til_Str _tmp122 = ((til_Str){(til_I64)"concat: malloc failed", 21});
        int _arr_status__tmp121 = til_Array_new(&_tmp120, &_err_alloc__tmp121, "Str", 1);
        if (_arr_status__tmp121 != 0) {
        }
        _arr_status__tmp121 = til_Array_set(&_err_idx__tmp121, &_tmp120, 0, &_tmp122);
        if (_arr_status__tmp121 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:452:15:", 24}), &_tmp120);
        til_Array_delete(&_tmp120);
    }
    til_memcpy(til_result.c_string, til_a.c_string, til_a.cap);
    til_memcpy(til_add(til_result.c_string, til_a.cap), til_b.c_string, til_b.cap);
    return til_result;
    goto _end_catches__tmp113;
_catch_AllocError__tmp113: {
    til_AllocError til_err = _thrown_AllocError__tmp113;
    til_Array _tmp124;
    til_AllocError _err_alloc__tmp125;
    til_IndexOutOfBoundsError _err_idx__tmp125;
    til_Str _tmp126 = til_err.msg;
    int _arr_status__tmp125 = til_Array_new(&_tmp124, &_err_alloc__tmp125, "Str", 1);
    if (_arr_status__tmp125 != 0) {
    }
    _arr_status__tmp125 = til_Array_set(&_err_idx__tmp125, &_tmp124, 0, &_tmp126);
    if (_arr_status__tmp125 != 0) {
    }
    til_panic(((til_Str){(til_I64)"src/core/str.til:459:15:", 24}), &_tmp124);
    til_Array_delete(&_tmp124);
    goto _end_catches__tmp113;
    }
_end_catches__tmp113:;
}

int til_format(til_Str* _ret, til_I64_OverflowError* _err1, til_IndexOutOfBoundsError* _err2, til_AllocError* _err3, const til_Str til_prefix, til_Array* til_args) {
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_prefix.cap;
    til_I64 til_i = 0;
    til_Str til_arg;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_arg = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp130 = {};
        int _status__tmp130 = til_Array_get(&_err0__tmp130, (*til_args), til_i, (til_Dynamic*)&til_arg);
        if (_status__tmp130 == 1) { *_err2 = _err0__tmp130; return 2; }
        til_result.cap = til_add(til_result.cap, til_arg.cap);
        if (til_lt(til_result.cap, til_arg.cap).data) {
            til_Str _tmp132;
            til_I64_OverflowError _err0__tmp133;
            til_IndexOutOfBoundsError _err1__tmp133;
            til_AllocError _err2__tmp133;
            til_Array _tmp134;
            til_AllocError _err_alloc__tmp135;
            til_IndexOutOfBoundsError _err_idx__tmp135;
            til_Str _tmp136 = ((til_Str){(til_I64)"format: integer overflow while summing cap for arg ", 51});
            til_Str _tmp137 = til_I64_to_str(til_i);
            int _arr_status__tmp135 = til_Array_new(&_tmp134, &_err_alloc__tmp135, "Str", 2);
            if (_arr_status__tmp135 != 0) {
                *_err3 = _err_alloc__tmp135; return 3;
            }
            _arr_status__tmp135 = til_Array_set(&_err_idx__tmp135, &_tmp134, 0, &_tmp136);
            if (_arr_status__tmp135 != 0) {
                *_err2 = _err_idx__tmp135; return 2;
            }
            _arr_status__tmp135 = til_Array_set(&_err_idx__tmp135, &_tmp134, 1, &_tmp137);
            if (_arr_status__tmp135 != 0) {
                *_err2 = _err_idx__tmp135; return 2;
            }
            int _status__tmp133 = til_format(&_tmp132, &_err0__tmp133, &_err1__tmp133, &_err2__tmp133, ((til_Str){(til_I64)"src/core/str.til:475:48:", 24}), &_tmp134);
            if (_status__tmp133 != 0) {
                if (_status__tmp133 == 1) { *_err1 = _err0__tmp133; return 1; }
                if (_status__tmp133 == 2) { *_err2 = _err1__tmp133; return 2; }
                if (_status__tmp133 == 3) { *_err3 = _err2__tmp133; return 3; }
            }
            til_Array_delete(&_tmp134);
            *_err1 = (til_I64_OverflowError){.msg = _tmp132};
            return 1;
        }
        til_I64_inc(&til_i);
    }
    til_I64 _ret__tmp138;
    til_AllocError _err0__tmp138 = {};
    int _status__tmp138 = til_malloc(&_ret__tmp138, &_err0__tmp138, til_result.cap);
    if (_status__tmp138 == 1) { *_err3 = _err0__tmp138; return 3; }
    til_result.c_string = _ret__tmp138;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Str _tmp140;
        til_I64_OverflowError _err0__tmp141;
        til_IndexOutOfBoundsError _err1__tmp141;
        til_AllocError _err2__tmp141;
        til_Array _tmp142;
        til_AllocError _err_alloc__tmp143;
        til_IndexOutOfBoundsError _err_idx__tmp143;
        til_Str _tmp144 = ((til_Str){(til_I64)"format: malloc failed for cap = ", 32});
        til_Str _tmp145 = til_I64_to_str(til_result.cap);
        int _arr_status__tmp143 = til_Array_new(&_tmp142, &_err_alloc__tmp143, "Str", 2);
        if (_arr_status__tmp143 != 0) {
            *_err3 = _err_alloc__tmp143; return 3;
        }
        _arr_status__tmp143 = til_Array_set(&_err_idx__tmp143, &_tmp142, 0, &_tmp144);
        if (_arr_status__tmp143 != 0) {
            *_err2 = _err_idx__tmp143; return 2;
        }
        _arr_status__tmp143 = til_Array_set(&_err_idx__tmp143, &_tmp142, 1, &_tmp145);
        if (_arr_status__tmp143 != 0) {
            *_err2 = _err_idx__tmp143; return 2;
        }
        int _status__tmp141 = til_format(&_tmp140, &_err0__tmp141, &_err1__tmp141, &_err2__tmp141, ((til_Str){(til_I64)"src/core/str.til:481:37:", 24}), &_tmp142);
        if (_status__tmp141 != 0) {
            if (_status__tmp141 == 1) { *_err1 = _err0__tmp141; return 1; }
            if (_status__tmp141 == 2) { *_err2 = _err1__tmp141; return 2; }
            if (_status__tmp141 == 3) { *_err3 = _err2__tmp141; return 3; }
        }
        til_Array_delete(&_tmp142);
        *_err3 = (til_AllocError){.msg = _tmp140};
        return 3;
    }
    til_I64 til_offset = 0;
    til_memcpy(til_result.c_string, til_prefix.c_string, til_prefix.cap);
    til_offset = til_prefix.cap;
    til_I64 _for_i_10 = 0;
    til_Str til_s;
    while (til_lt(_for_i_10, til_Array_len((*til_args))).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp147;
        til_s = (til_Str){.c_string = 0, .cap = 0};
        til_IndexOutOfBoundsError _err0__tmp148 = {};
        int _status__tmp148 = til_Array_get(&_err0__tmp148, (*til_args), _for_i_10, (til_Dynamic*)&til_s);
        if (_status__tmp148 == 0) {
        } else if (_status__tmp148 == 1) {
            til_IndexOutOfBoundsError til_err = _err0__tmp148;
            til_Array _tmp150;
            til_AllocError _err_alloc__tmp151;
            til_IndexOutOfBoundsError _err_idx__tmp151;
            til_Str _tmp152 = til_err.msg;
            int _arr_status__tmp151 = til_Array_new(&_tmp150, &_err_alloc__tmp151, "Str", 1);
            if (_arr_status__tmp151 != 0) {
                *_err3 = _err_alloc__tmp151; return 3;
            }
            _arr_status__tmp151 = til_Array_set(&_err_idx__tmp151, &_tmp150, 0, &_tmp152);
            if (_arr_status__tmp151 != 0) {
                *_err2 = _err_idx__tmp151; return 2;
            }
            til_panic(((til_Str){(til_I64)"src/core/str.til:488:5:", 23}), &_tmp150);
            til_Array_delete(&_tmp150);
        }
        til_memcpy(til_add(til_result.c_string, til_offset), til_s.c_string, til_s.cap);
        til_offset = til_add(til_offset, til_s.cap);
        _for_i_10 = til_add(_for_i_10, 1);
        goto _end_catches__tmp147;
_catch_IndexOutOfBoundsError__tmp147: {
        til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp147;
        til_Array _tmp154;
        til_AllocError _err_alloc__tmp155;
        til_IndexOutOfBoundsError _err_idx__tmp155;
        til_Str _tmp156 = til_err.msg;
        int _arr_status__tmp155 = til_Array_new(&_tmp154, &_err_alloc__tmp155, "Str", 1);
        if (_arr_status__tmp155 != 0) {
            *_err3 = _err_alloc__tmp155; return 3;
        }
        _arr_status__tmp155 = til_Array_set(&_err_idx__tmp155, &_tmp154, 0, &_tmp156);
        if (_arr_status__tmp155 != 0) {
            *_err2 = _err_idx__tmp155; return 2;
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:488:5:", 23}), &_tmp154);
        til_Array_delete(&_tmp154);
        goto _end_catches__tmp147;
        }
_end_catches__tmp147:;
    }
    *_ret = til_result;
    return 0;
}

void til_test(const til_Str til_loc_str, const til_Bool til_cond, const til_Str til_msg) {
    til_assertm(til_loc_str, til_cond, til_msg);
}

void til_assert_eq(const til_Str til_loc_str, const til_I64 til_a, const til_I64 til_b) {
    if (til_not(til_I64_eq(til_a, til_b)).data) {
        til_Array _tmp160;
        til_AllocError _err_alloc__tmp161;
        til_IndexOutOfBoundsError _err_idx__tmp161;
        til_Str _tmp162 = til_loc_str;
        til_Str _tmp163 = ((til_Str){(til_I64)"assert_eq failed: expected '", 28});
        til_Str _tmp164 = til_I64_to_str(til_a);
        til_Str _tmp165 = ((til_Str){(til_I64)"', found '", 10});
        til_Str _tmp166 = til_I64_to_str(til_b);
        til_Str _tmp167 = ((til_Str){(til_I64)"'", 1});
        int _arr_status__tmp161 = til_Array_new(&_tmp160, &_err_alloc__tmp161, "Str", 6);
        if (_arr_status__tmp161 != 0) {
        }
        _arr_status__tmp161 = til_Array_set(&_err_idx__tmp161, &_tmp160, 0, &_tmp162);
        if (_arr_status__tmp161 != 0) {
        }
        _arr_status__tmp161 = til_Array_set(&_err_idx__tmp161, &_tmp160, 1, &_tmp163);
        if (_arr_status__tmp161 != 0) {
        }
        _arr_status__tmp161 = til_Array_set(&_err_idx__tmp161, &_tmp160, 2, &_tmp164);
        if (_arr_status__tmp161 != 0) {
        }
        _arr_status__tmp161 = til_Array_set(&_err_idx__tmp161, &_tmp160, 3, &_tmp165);
        if (_arr_status__tmp161 != 0) {
        }
        _arr_status__tmp161 = til_Array_set(&_err_idx__tmp161, &_tmp160, 4, &_tmp166);
        if (_arr_status__tmp161 != 0) {
        }
        _arr_status__tmp161 = til_Array_set(&_err_idx__tmp161, &_tmp160, 5, &_tmp167);
        if (_arr_status__tmp161 != 0) {
        }
        til_println(&_tmp160);
        til_Array_delete(&_tmp160);
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
    til_I64 _ret__tmp179;
    til_AllocError _err0__tmp179 = {};
    int _status__tmp179 = til_malloc(&_ret__tmp179, &_err0__tmp179, til_size_bytes);
    if (_status__tmp179 == 1) { *_err1 = _err0__tmp179; return 1; }
    til_arr.ptr = _ret__tmp179;
    til_U8 _tmp180;
    til_U8_OverflowError _err0__tmp181;
    int _status__tmp181 = til_U8_from_i64(&_tmp180, &_err0__tmp181, 0);
    if (_status__tmp181 != 0) {
    }
    til_memset(til_arr.ptr, _tmp180, til_size_bytes);
    til_arr._len = til_capacity;
    *_ret = til_arr;
    return 0;
}

int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array til_self, const til_I64 til_index, til_Dynamic* til_T) {
    if (til_I64_gteq(til_index, til_self._len).data) {
        til_Str _tmp184;
        til_I64_OverflowError _err0__tmp185;
        til_IndexOutOfBoundsError _err1__tmp185;
        til_AllocError _err2__tmp185;
        til_Array _tmp186;
        til_AllocError _err_alloc__tmp187;
        til_IndexOutOfBoundsError _err_idx__tmp187;
        til_Str _tmp188 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        int _arr_status__tmp187 = til_Array_new(&_tmp186, &_err_alloc__tmp187, "Str", 1);
        if (_arr_status__tmp187 != 0) {
        }
        _arr_status__tmp187 = til_Array_set(&_err_idx__tmp187, &_tmp186, 0, &_tmp188);
        if (_arr_status__tmp187 != 0) {
            *_err1 = _err_idx__tmp187; return 1;
        }
        int _status__tmp185 = til_format(&_tmp184, &_err0__tmp185, &_err1__tmp185, &_err2__tmp185, ((til_Str){(til_I64)"src/core/array.til:41:52:", 25}), &_tmp186);
        if (_status__tmp185 != 0) {
            if (_status__tmp185 == 2) { *_err1 = _err1__tmp185; return 1; }
        }
        til_Array_delete(&_tmp186);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp184};
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_I64_gteq(til_index, til_self->_len).data) {
        til_Str _tmp191;
        til_I64_OverflowError _err0__tmp192;
        til_IndexOutOfBoundsError _err1__tmp192;
        til_AllocError _err2__tmp192;
        til_Array _tmp193;
        til_AllocError _err_alloc__tmp194;
        til_IndexOutOfBoundsError _err_idx__tmp194;
        til_Str _tmp195 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        int _arr_status__tmp194 = til_Array_new(&_tmp193, &_err_alloc__tmp194, "Str", 1);
        if (_arr_status__tmp194 != 0) {
        }
        _arr_status__tmp194 = til_Array_set(&_err_idx__tmp194, &_tmp193, 0, &_tmp195);
        if (_arr_status__tmp194 != 0) {
            *_err1 = _err_idx__tmp194; return 1;
        }
        int _status__tmp192 = til_format(&_tmp191, &_err0__tmp192, &_err1__tmp192, &_err2__tmp192, ((til_Str){(til_I64)"src/core/array.til:56:52:", 25}), &_tmp193);
        if (_status__tmp192 != 0) {
            if (_status__tmp192 == 2) { *_err1 = _err1__tmp192; return 1; }
        }
        til_Array_delete(&_tmp193);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp191};
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
    til_I64 _ret__tmp214;
    til_AllocError _err0__tmp214 = {};
    int _status__tmp214 = til_malloc(&_ret__tmp214, &_err0__tmp214, til_size_bytes);
    if (_status__tmp214 == 1) { *_err1 = _err0__tmp214; return 1; }
    til_vec.ptr = _ret__tmp214;
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
            til_Array _tmp218;
            til_AllocError _err_alloc__tmp219;
            til_IndexOutOfBoundsError _err_idx__tmp219;
            til_Str _tmp220 = ((til_Str){(til_I64)"Vec.push: capacity exceeded Vec.MAX_CAP", 39});
            int _arr_status__tmp219 = til_Array_new(&_tmp218, &_err_alloc__tmp219, "Str", 1);
            if (_arr_status__tmp219 != 0) {
                *_err1 = _err_alloc__tmp219; return 1;
            }
            _arr_status__tmp219 = til_Array_set(&_err_idx__tmp219, &_tmp218, 0, &_tmp220);
            if (_arr_status__tmp219 != 0) {
            }
            til_panic(((til_Str){(til_I64)"src/core/vec.til:63:23:", 23}), &_tmp218);
            til_Array_delete(&_tmp218);
        }
        til_I64 _ret__tmp221;
        til_I64 til_new_ptr;
        til_AllocError _err0__tmp221 = {};
        int _status__tmp221 = til_malloc(&_ret__tmp221, &_err0__tmp221, til_mul(til_new_cap, til_self->type_size));
        if (_status__tmp221 == 1) { *_err1 = _err0__tmp221; return 1; }
        til_new_ptr = _ret__tmp221;
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
        til_Str _tmp224;
        til_I64_OverflowError _err0__tmp225;
        til_IndexOutOfBoundsError _err1__tmp225;
        til_AllocError _err2__tmp225;
        til_Array _tmp226;
        til_AllocError _err_alloc__tmp227;
        til_IndexOutOfBoundsError _err_idx__tmp227;
        til_Str _tmp228 = ((til_Str){(til_I64)"Vec.get: index out of bounds", 28});
        int _arr_status__tmp227 = til_Array_new(&_tmp226, &_err_alloc__tmp227, "Str", 1);
        if (_arr_status__tmp227 != 0) {
        }
        _arr_status__tmp227 = til_Array_set(&_err_idx__tmp227, &_tmp226, 0, &_tmp228);
        if (_arr_status__tmp227 != 0) {
            *_err1 = _err_idx__tmp227; return 1;
        }
        int _status__tmp225 = til_format(&_tmp224, &_err0__tmp225, &_err1__tmp225, &_err2__tmp225, ((til_Str){(til_I64)"src/core/vec.til:81:52:", 23}), &_tmp226);
        if (_status__tmp225 != 0) {
            if (_status__tmp225 == 2) { *_err1 = _err1__tmp225; return 1; }
        }
        til_Array_delete(&_tmp226);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp224};
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
    til_I64 _ret__tmp236;
    til_AllocError _err0__tmp236 = {};
    int _status__tmp236 = til_malloc(&_ret__tmp236, &_err0__tmp236, til_cloned.cap);
    if (_status__tmp236 == 1) { *_err1 = _err0__tmp236; return 1; }
    til_cloned.c_string = _ret__tmp236;
    if (til_I64_eq(til_NULL, til_cloned.c_string).data) {
        til_Str _tmp238;
        til_I64_OverflowError _err0__tmp239;
        til_IndexOutOfBoundsError _err1__tmp239;
        til_AllocError _err2__tmp239;
        til_Array _tmp240;
        til_AllocError _err_alloc__tmp241;
        til_IndexOutOfBoundsError _err_idx__tmp241;
        til_Str _tmp242 = ((til_Str){(til_I64)"Str.clone: malloc failed for ", 29});
        til_Str _tmp243 = til_I64_to_str(til_cloned.cap);
        til_Str _tmp244 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp241 = til_Array_new(&_tmp240, &_err_alloc__tmp241, "Str", 3);
        if (_arr_status__tmp241 != 0) {
            *_err1 = _err_alloc__tmp241; return 1;
        }
        _arr_status__tmp241 = til_Array_set(&_err_idx__tmp241, &_tmp240, 0, &_tmp242);
        if (_arr_status__tmp241 != 0) {
        }
        _arr_status__tmp241 = til_Array_set(&_err_idx__tmp241, &_tmp240, 1, &_tmp243);
        if (_arr_status__tmp241 != 0) {
        }
        _arr_status__tmp241 = til_Array_set(&_err_idx__tmp241, &_tmp240, 2, &_tmp244);
        if (_arr_status__tmp241 != 0) {
        }
        int _status__tmp239 = til_format(&_tmp238, &_err0__tmp239, &_err1__tmp239, &_err2__tmp239, ((til_Str){(til_I64)"src/core/str.til:46:41:", 23}), &_tmp240);
        if (_status__tmp239 != 0) {
            if (_status__tmp239 == 3) { *_err1 = _err2__tmp239; return 1; }
        }
        til_Array_delete(&_tmp240);
        *_err1 = (til_AllocError){.msg = _tmp238};
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
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp263;
    if (til_I64_eq(til_Str_len(til_from), 0).data) {
        til_Str _ret__tmp265;
        til_AllocError _err0__tmp265 = {};
        int _status__tmp265 = til_Str_clone(&_ret__tmp265, &_err0__tmp265, til_self);
        if (_status__tmp265 == 1) { *_err1 = _err0__tmp265; return 1; }
        *_ret = _ret__tmp265;
        return 0;
    }
    if (til_I64_eq(til_n, 0).data) {
        til_Str _ret__tmp267;
        til_AllocError _err0__tmp267 = {};
        int _status__tmp267 = til_Str_clone(&_ret__tmp267, &_err0__tmp267, til_self);
        if (_status__tmp267 == 1) { *_err1 = _err0__tmp267; return 1; }
        *_ret = _ret__tmp267;
        return 0;
    }
    til_I64 til_idx = til_Str_find(til_self, til_from);
    if (til_lt(til_idx, 0).data) {
        til_Str _ret__tmp269;
        til_AllocError _err0__tmp269 = {};
        int _status__tmp269 = til_Str_clone(&_ret__tmp269, &_err0__tmp269, til_self);
        if (_status__tmp269 == 1) { *_err1 = _err0__tmp269; return 1; }
        *_ret = _ret__tmp269;
        return 0;
    }
    til_Str _ret__tmp270;
    til_Str til_prefix;
    til_IndexOutOfBoundsError _err0__tmp270 = {};
    til_AllocError _err1__tmp270 = {};
    int _status__tmp270 = til_get_substr(&_ret__tmp270, &_err0__tmp270, &_err1__tmp270, til_self, 0, til_idx);
    if (_status__tmp270 == 2) { *_err1 = _err1__tmp270; return 1; }
    til_prefix = _ret__tmp270;
    til_Str _ret__tmp271;
    til_Str til_suffix;
    til_IndexOutOfBoundsError _err0__tmp271 = {};
    til_AllocError _err1__tmp271 = {};
    int _status__tmp271 = til_get_substr(&_ret__tmp271, &_err0__tmp271, &_err1__tmp271, til_self, til_add(til_idx, til_Str_len(til_from)), til_Str_len(til_self));
    if (_status__tmp271 == 2) { *_err1 = _err1__tmp271; return 1; }
    til_suffix = _ret__tmp271;
    til_Str til_result = til_concat(til_concat(til_prefix, til_to), til_suffix);
    til_Str til_rest;
    if (til_gt(til_n, 1).data) {
        til_Str _ret__tmp273;
        til_Str til_rest;
        til_AllocError _err0__tmp273 = {};
        int _status__tmp273 = til_Str_replacen(&_ret__tmp273, &_err0__tmp273, til_suffix, til_from, til_to, til_sub(til_n, 1));
        if (_status__tmp273 == 1) { *_err1 = _err0__tmp273; return 1; }
        til_rest = _ret__tmp273;
        til_result = til_concat(til_concat(til_prefix, til_to), til_rest);
    }
    *_ret = til_result;
    return 0;
    goto _end_catches__tmp263;
_catch_IndexOutOfBoundsError__tmp263: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp263;
    til_Str _ret__tmp275;
    til_AllocError _err0__tmp275 = {};
    int _status__tmp275 = til_Str_clone(&_ret__tmp275, &_err0__tmp275, til_self);
    if (_status__tmp275 == 1) { *_err1 = _err0__tmp275; return 1; }
    til_result = _ret__tmp275;
    goto _end_catches__tmp263;
    }
_end_catches__tmp263:;
}

til_Bool til_U8_eq(const til_U8 til_self, const til_U8 til_other) {
    return til_I64_eq(til_U8_to_i64(til_self), til_U8_to_i64(til_other));
}

til_I64 til_U8_to_i64(const til_U8 til_self) {
    return til_u8_to_i64(til_self);
}

int til_U8_from_i64(til_U8* _ret, til_U8_OverflowError* _err1, const til_I64 til_self) {
    if (til_lt(til_self, 0).data) {
        til_Str _tmp280;
        til_I64_OverflowError _err0__tmp281;
        til_IndexOutOfBoundsError _err1__tmp281;
        til_AllocError _err2__tmp281;
        til_Array _tmp282;
        til_AllocError _err_alloc__tmp283;
        til_IndexOutOfBoundsError _err_idx__tmp283;
        til_Str _tmp284 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        int _arr_status__tmp283 = til_Array_new(&_tmp282, &_err_alloc__tmp283, "Str", 1);
        if (_arr_status__tmp283 != 0) {
        }
        _arr_status__tmp283 = til_Array_set(&_err_idx__tmp283, &_tmp282, 0, &_tmp284);
        if (_arr_status__tmp283 != 0) {
        }
        int _status__tmp281 = til_format(&_tmp280, &_err0__tmp281, &_err1__tmp281, &_err2__tmp281, ((til_Str){(til_I64)"src/core/u8.til:50:47:", 22}), &_tmp282);
        if (_status__tmp281 != 0) {
        }
        til_Array_delete(&_tmp282);
        *_err1 = (til_U8_OverflowError){.msg = _tmp280};
        return 1;
    }
    if (til_gt(til_self, til_MAX_U8).data) {
        til_Str _tmp286;
        til_I64_OverflowError _err0__tmp287;
        til_IndexOutOfBoundsError _err1__tmp287;
        til_AllocError _err2__tmp287;
        til_Array _tmp288;
        til_AllocError _err_alloc__tmp289;
        til_IndexOutOfBoundsError _err_idx__tmp289;
        til_Str _tmp290 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp291 = ((til_Str){(til_I64)"255", 3});
        int _arr_status__tmp289 = til_Array_new(&_tmp288, &_err_alloc__tmp289, "Str", 2);
        if (_arr_status__tmp289 != 0) {
        }
        _arr_status__tmp289 = til_Array_set(&_err_idx__tmp289, &_tmp288, 0, &_tmp290);
        if (_arr_status__tmp289 != 0) {
        }
        _arr_status__tmp289 = til_Array_set(&_err_idx__tmp289, &_tmp288, 1, &_tmp291);
        if (_arr_status__tmp289 != 0) {
        }
        int _status__tmp287 = til_format(&_tmp286, &_err0__tmp287, &_err1__tmp287, &_err2__tmp287, ((til_Str){(til_I64)"src/core/u8.til:53:47:", 22}), &_tmp288);
        if (_status__tmp287 != 0) {
        }
        til_Array_delete(&_tmp288);
        *_err1 = (til_U8_OverflowError){.msg = _tmp286};
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
