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
til_Bool til_lteq(const til_I64 til_a, const til_I64 til_b);
til_Bool til_gteq(const til_I64 til_a, const til_I64 til_b);
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
til_I64_OverflowError til_I64_OverflowError_new(const til_Str til_msg);
til_Bool til_I64_eq(const til_I64 til_a, const til_I64 til_b);
til_Str til_I64_to_str(const til_I64 til_self);
til_I64 til_I64_from_str(const til_Str til_str);
void til_I64_inc(til_I64* til_self);
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
    til_panic(((til_Str){(til_I64)"src/core/bool.til:69:15:", 24}), &_tmp8);
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
    til_panic(((til_Str){(til_I64)"src/core/bool.til:85:15:", 24}), &_tmp17);
    til_Array_delete(&_tmp17);
    }
_end_catches__tmp11:;
}

void til_panic(const til_Str til_loc_str, til_Array* til_msgs) {
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp20;
    til_single_print(til_loc_str);
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_msgs))).data) {
        til_Str til_val = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp23 = {};
        int _status__tmp23 = til_Array_get(&_err0__tmp23, (*til_msgs), til_i, (til_Dynamic*)&til_val);
        if (_status__tmp23 == 1) { _thrown_IndexOutOfBoundsError__tmp20 = _err0__tmp23; goto _catch_IndexOutOfBoundsError__tmp20; }
        til_single_print(til_val);
        til_I64_inc(&til_i);
    }
    til_single_print(((til_Str){(til_I64)"\n", 1}));
    til_print_flush();
    til_exit(1);
    goto _end_catches__tmp20;
_catch_IndexOutOfBoundsError__tmp20: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp20;
    til_single_print(((til_Str){(til_I64)"panic: IndexOutOfBoundsError should never happen\n", 49}));
    til_print_flush();
    til_exit(1);
    }
_end_catches__tmp20:;
}

void til_assertm(const til_Str til_loc_str, const til_Bool til_cond, const til_Str til_msg) {
    if (til_not(til_cond).data) {
        til_Str _tmp27;
        til_I64_OverflowError _err0__tmp28;
        til_IndexOutOfBoundsError _err1__tmp28;
        til_AllocError _err2__tmp28;
        til_Array _tmp29;
        til_AllocError _err_alloc__tmp30;
        til_IndexOutOfBoundsError _err_idx__tmp30;
        til_Str _tmp31 = til_msg;
        int _arr_status__tmp30 = til_Array_new(&_tmp29, &_err_alloc__tmp30, "Str", 1);
        if (_arr_status__tmp30 != 0) {
        }
        _arr_status__tmp30 = til_Array_set(&_err_idx__tmp30, &_tmp29, 0, &_tmp31);
        if (_arr_status__tmp30 != 0) {
        }
        int _status__tmp28 = til_format(&_tmp27, &_err0__tmp28, &_err1__tmp28, &_err2__tmp28, ((til_Str){(til_I64)"assert failed: ", 15}), &_tmp29);
        if (_status__tmp28 != 0) {
        }
        til_Array_delete(&_tmp29);
        til_Array _tmp32;
        til_AllocError _err_alloc__tmp33;
        til_IndexOutOfBoundsError _err_idx__tmp33;
        int _arr_status__tmp33 = til_Array_new(&_tmp32, &_err_alloc__tmp33, "Str", 1);
        if (_arr_status__tmp33 != 0) {
        }
        _arr_status__tmp33 = til_Array_set(&_err_idx__tmp33, &_tmp32, 0, &_tmp27);
        if (_arr_status__tmp33 != 0) {
        }
        til_panic(til_loc_str, &_tmp32);
        til_Array_delete(&_tmp32);
    }
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

void til_println(til_Array* til_args) {
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp40;
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Str til_val = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp43 = {};
        int _status__tmp43 = til_Array_get(&_err0__tmp43, (*til_args), til_i, (til_Dynamic*)&til_val);
        if (_status__tmp43 == 1) { _thrown_IndexOutOfBoundsError__tmp40 = _err0__tmp43; goto _catch_IndexOutOfBoundsError__tmp40; }
        til_single_print(til_val);
        til_I64_inc(&til_i);
    }
    til_single_print(((til_Str){(til_I64)"\n", 1}));
    til_print_flush();
    goto _end_catches__tmp40;
_catch_IndexOutOfBoundsError__tmp40: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp40;
    til_Array _tmp45;
    til_AllocError _err_alloc__tmp46;
    til_IndexOutOfBoundsError _err_idx__tmp46;
    til_Str _tmp47 = ((til_Str){(til_I64)"println: IndexOutOfBoundsError should never happen", 50});
    int _arr_status__tmp46 = til_Array_new(&_tmp45, &_err_alloc__tmp46, "Str", 1);
    if (_arr_status__tmp46 != 0) {
    }
    _arr_status__tmp46 = til_Array_set(&_err_idx__tmp46, &_tmp45, 0, &_tmp47);
    if (_arr_status__tmp46 != 0) {
    }
    til_panic(((til_Str){(til_I64)"src/core/print.til:31:15:", 25}), &_tmp45);
    til_Array_delete(&_tmp45);
    }
_end_catches__tmp40:;
}

int til_get_substr(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_start, const til_I64 til_end) {
    if (til_lt(til_start, 0).data) {
        til_Str _tmp50;
        til_I64_OverflowError _err0__tmp51;
        til_IndexOutOfBoundsError _err1__tmp51;
        til_AllocError _err2__tmp51;
        til_Array _tmp52;
        til_AllocError _err_alloc__tmp53;
        til_IndexOutOfBoundsError _err_idx__tmp53;
        til_Str _tmp54 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp55 = til_I64_to_str(til_start);
        til_Str _tmp56 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp53 = til_Array_new(&_tmp52, &_err_alloc__tmp53, "Str", 3);
        if (_arr_status__tmp53 != 0) {
            *_err2 = _err_alloc__tmp53; return 2;
        }
        _arr_status__tmp53 = til_Array_set(&_err_idx__tmp53, &_tmp52, 0, &_tmp54);
        if (_arr_status__tmp53 != 0) {
            *_err1 = _err_idx__tmp53; return 1;
        }
        _arr_status__tmp53 = til_Array_set(&_err_idx__tmp53, &_tmp52, 1, &_tmp55);
        if (_arr_status__tmp53 != 0) {
            *_err1 = _err_idx__tmp53; return 1;
        }
        _arr_status__tmp53 = til_Array_set(&_err_idx__tmp53, &_tmp52, 2, &_tmp56);
        if (_arr_status__tmp53 != 0) {
            *_err1 = _err_idx__tmp53; return 1;
        }
        int _status__tmp51 = til_format(&_tmp50, &_err0__tmp51, &_err1__tmp51, &_err2__tmp51, ((til_Str){(til_I64)"src/core/str.til:368:48:", 24}), &_tmp52);
        if (_status__tmp51 != 0) {
            if (_status__tmp51 == 2) { *_err1 = _err1__tmp51; return 1; }
            if (_status__tmp51 == 3) { *_err2 = _err2__tmp51; return 2; }
        }
        til_Array_delete(&_tmp52);
        til_Str _tmp57;
        til_I64_OverflowError _err0__tmp58;
        til_IndexOutOfBoundsError _err1__tmp58;
        til_AllocError _err2__tmp58;
        til_Array _tmp59;
        til_AllocError _err_alloc__tmp60;
        til_IndexOutOfBoundsError _err_idx__tmp60;
        til_Str _tmp61 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp62 = til_I64_to_str(til_start);
        til_Str _tmp63 = ((til_Str){(til_I64)" cannot be negative", 19});
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
        int _status__tmp58 = til_format(&_tmp57, &_err0__tmp58, &_err1__tmp58, &_err2__tmp58, ((til_Str){(til_I64)"src/core/str.til:368:48:", 24}), &_tmp59);
        if (_status__tmp58 != 0) {
            if (_status__tmp58 == 2) { *_err1 = _err1__tmp58; return 1; }
            if (_status__tmp58 == 3) { *_err2 = _err2__tmp58; return 2; }
        }
        til_Array_delete(&_tmp59);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp57);
        return 1;
    }
    if (til_lt(til_end, 0).data) {
        til_Str _tmp65;
        til_I64_OverflowError _err0__tmp66;
        til_IndexOutOfBoundsError _err1__tmp66;
        til_AllocError _err2__tmp66;
        til_Array _tmp67;
        til_AllocError _err_alloc__tmp68;
        til_IndexOutOfBoundsError _err_idx__tmp68;
        til_Str _tmp69 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp70 = til_I64_to_str(til_end);
        til_Str _tmp71 = ((til_Str){(til_I64)" cannot be negative", 19});
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
        int _status__tmp66 = til_format(&_tmp65, &_err0__tmp66, &_err1__tmp66, &_err2__tmp66, ((til_Str){(til_I64)"src/core/str.til:371:48:", 24}), &_tmp67);
        if (_status__tmp66 != 0) {
            if (_status__tmp66 == 2) { *_err1 = _err1__tmp66; return 1; }
            if (_status__tmp66 == 3) { *_err2 = _err2__tmp66; return 2; }
        }
        til_Array_delete(&_tmp67);
        til_Str _tmp72;
        til_I64_OverflowError _err0__tmp73;
        til_IndexOutOfBoundsError _err1__tmp73;
        til_AllocError _err2__tmp73;
        til_Array _tmp74;
        til_AllocError _err_alloc__tmp75;
        til_IndexOutOfBoundsError _err_idx__tmp75;
        til_Str _tmp76 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp77 = til_I64_to_str(til_end);
        til_Str _tmp78 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp75 = til_Array_new(&_tmp74, &_err_alloc__tmp75, "Str", 3);
        if (_arr_status__tmp75 != 0) {
            *_err2 = _err_alloc__tmp75; return 2;
        }
        _arr_status__tmp75 = til_Array_set(&_err_idx__tmp75, &_tmp74, 0, &_tmp76);
        if (_arr_status__tmp75 != 0) {
            *_err1 = _err_idx__tmp75; return 1;
        }
        _arr_status__tmp75 = til_Array_set(&_err_idx__tmp75, &_tmp74, 1, &_tmp77);
        if (_arr_status__tmp75 != 0) {
            *_err1 = _err_idx__tmp75; return 1;
        }
        _arr_status__tmp75 = til_Array_set(&_err_idx__tmp75, &_tmp74, 2, &_tmp78);
        if (_arr_status__tmp75 != 0) {
            *_err1 = _err_idx__tmp75; return 1;
        }
        int _status__tmp73 = til_format(&_tmp72, &_err0__tmp73, &_err1__tmp73, &_err2__tmp73, ((til_Str){(til_I64)"src/core/str.til:371:48:", 24}), &_tmp74);
        if (_status__tmp73 != 0) {
            if (_status__tmp73 == 2) { *_err1 = _err1__tmp73; return 1; }
            if (_status__tmp73 == 3) { *_err2 = _err2__tmp73; return 2; }
        }
        til_Array_delete(&_tmp74);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp72);
        return 1;
    }
    if (til_gt(til_start, til_end).data) {
        til_Str _tmp80;
        til_I64_OverflowError _err0__tmp81;
        til_IndexOutOfBoundsError _err1__tmp81;
        til_AllocError _err2__tmp81;
        til_Array _tmp82;
        til_AllocError _err_alloc__tmp83;
        til_IndexOutOfBoundsError _err_idx__tmp83;
        til_Str _tmp84 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp85 = til_I64_to_str(til_start);
        til_Str _tmp86 = ((til_Str){(til_I64)" is greater than end index ", 27});
        til_Str _tmp87 = til_I64_to_str(til_end);
        int _arr_status__tmp83 = til_Array_new(&_tmp82, &_err_alloc__tmp83, "Str", 4);
        if (_arr_status__tmp83 != 0) {
            *_err2 = _err_alloc__tmp83; return 2;
        }
        _arr_status__tmp83 = til_Array_set(&_err_idx__tmp83, &_tmp82, 0, &_tmp84);
        if (_arr_status__tmp83 != 0) {
            *_err1 = _err_idx__tmp83; return 1;
        }
        _arr_status__tmp83 = til_Array_set(&_err_idx__tmp83, &_tmp82, 1, &_tmp85);
        if (_arr_status__tmp83 != 0) {
            *_err1 = _err_idx__tmp83; return 1;
        }
        _arr_status__tmp83 = til_Array_set(&_err_idx__tmp83, &_tmp82, 2, &_tmp86);
        if (_arr_status__tmp83 != 0) {
            *_err1 = _err_idx__tmp83; return 1;
        }
        _arr_status__tmp83 = til_Array_set(&_err_idx__tmp83, &_tmp82, 3, &_tmp87);
        if (_arr_status__tmp83 != 0) {
            *_err1 = _err_idx__tmp83; return 1;
        }
        int _status__tmp81 = til_format(&_tmp80, &_err0__tmp81, &_err1__tmp81, &_err2__tmp81, ((til_Str){(til_I64)"src/core/str.til:374:48:", 24}), &_tmp82);
        if (_status__tmp81 != 0) {
            if (_status__tmp81 == 2) { *_err1 = _err1__tmp81; return 1; }
            if (_status__tmp81 == 3) { *_err2 = _err2__tmp81; return 2; }
        }
        til_Array_delete(&_tmp82);
        til_Str _tmp88;
        til_I64_OverflowError _err0__tmp89;
        til_IndexOutOfBoundsError _err1__tmp89;
        til_AllocError _err2__tmp89;
        til_Array _tmp90;
        til_AllocError _err_alloc__tmp91;
        til_IndexOutOfBoundsError _err_idx__tmp91;
        til_Str _tmp92 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp93 = til_I64_to_str(til_start);
        til_Str _tmp94 = ((til_Str){(til_I64)" is greater than end index ", 27});
        til_Str _tmp95 = til_I64_to_str(til_end);
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
        int _status__tmp89 = til_format(&_tmp88, &_err0__tmp89, &_err1__tmp89, &_err2__tmp89, ((til_Str){(til_I64)"src/core/str.til:374:48:", 24}), &_tmp90);
        if (_status__tmp89 != 0) {
            if (_status__tmp89 == 2) { *_err1 = _err1__tmp89; return 1; }
            if (_status__tmp89 == 3) { *_err2 = _err2__tmp89; return 2; }
        }
        til_Array_delete(&_tmp90);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp88);
        return 1;
    }
    if (til_gt(til_end, til_Str_len(til_s)).data) {
        til_Str _tmp97;
        til_I64_OverflowError _err0__tmp98;
        til_IndexOutOfBoundsError _err1__tmp98;
        til_AllocError _err2__tmp98;
        til_Array _tmp99;
        til_AllocError _err_alloc__tmp100;
        til_IndexOutOfBoundsError _err_idx__tmp100;
        til_Str _tmp101 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp102 = til_I64_to_str(til_end);
        til_Str _tmp103 = ((til_Str){(til_I64)" is greater than string length ", 31});
        til_Str _tmp104 = til_I64_to_str(til_Str_len(til_s));
        int _arr_status__tmp100 = til_Array_new(&_tmp99, &_err_alloc__tmp100, "Str", 4);
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
        _arr_status__tmp100 = til_Array_set(&_err_idx__tmp100, &_tmp99, 3, &_tmp104);
        if (_arr_status__tmp100 != 0) {
            *_err1 = _err_idx__tmp100; return 1;
        }
        int _status__tmp98 = til_format(&_tmp97, &_err0__tmp98, &_err1__tmp98, &_err2__tmp98, ((til_Str){(til_I64)"src/core/str.til:377:48:", 24}), &_tmp99);
        if (_status__tmp98 != 0) {
            if (_status__tmp98 == 2) { *_err1 = _err1__tmp98; return 1; }
            if (_status__tmp98 == 3) { *_err2 = _err2__tmp98; return 2; }
        }
        til_Array_delete(&_tmp99);
        til_Str _tmp105;
        til_I64_OverflowError _err0__tmp106;
        til_IndexOutOfBoundsError _err1__tmp106;
        til_AllocError _err2__tmp106;
        til_Array _tmp107;
        til_AllocError _err_alloc__tmp108;
        til_IndexOutOfBoundsError _err_idx__tmp108;
        til_Str _tmp109 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp110 = til_I64_to_str(til_end);
        til_Str _tmp111 = ((til_Str){(til_I64)" is greater than string length ", 31});
        til_Str _tmp112 = til_I64_to_str(til_Str_len(til_s));
        int _arr_status__tmp108 = til_Array_new(&_tmp107, &_err_alloc__tmp108, "Str", 4);
        if (_arr_status__tmp108 != 0) {
            *_err2 = _err_alloc__tmp108; return 2;
        }
        _arr_status__tmp108 = til_Array_set(&_err_idx__tmp108, &_tmp107, 0, &_tmp109);
        if (_arr_status__tmp108 != 0) {
            *_err1 = _err_idx__tmp108; return 1;
        }
        _arr_status__tmp108 = til_Array_set(&_err_idx__tmp108, &_tmp107, 1, &_tmp110);
        if (_arr_status__tmp108 != 0) {
            *_err1 = _err_idx__tmp108; return 1;
        }
        _arr_status__tmp108 = til_Array_set(&_err_idx__tmp108, &_tmp107, 2, &_tmp111);
        if (_arr_status__tmp108 != 0) {
            *_err1 = _err_idx__tmp108; return 1;
        }
        _arr_status__tmp108 = til_Array_set(&_err_idx__tmp108, &_tmp107, 3, &_tmp112);
        if (_arr_status__tmp108 != 0) {
            *_err1 = _err_idx__tmp108; return 1;
        }
        int _status__tmp106 = til_format(&_tmp105, &_err0__tmp106, &_err1__tmp106, &_err2__tmp106, ((til_Str){(til_I64)"src/core/str.til:377:48:", 24}), &_tmp107);
        if (_status__tmp106 != 0) {
            if (_status__tmp106 == 2) { *_err1 = _err1__tmp106; return 1; }
            if (_status__tmp106 == 3) { *_err2 = _err2__tmp106; return 2; }
        }
        til_Array_delete(&_tmp107);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp105);
        return 1;
    }
    if (til_I64_eq(til_start, til_end).data) {
        til_Str _tmp114;
        til_I64_OverflowError _err0__tmp115;
        til_IndexOutOfBoundsError _err1__tmp115;
        til_AllocError _err2__tmp115;
        til_Array _tmp116;
        til_AllocError _err_alloc__tmp117;
        til_IndexOutOfBoundsError _err_idx__tmp117;
        til_Str _tmp118 = ((til_Str){(til_I64)"get_substr: start and end are the same (", 40});
        til_Str _tmp119 = til_I64_to_str(til_start);
        til_Str _tmp120 = ((til_Str){(til_I64)"), no substring", 15});
        int _arr_status__tmp117 = til_Array_new(&_tmp116, &_err_alloc__tmp117, "Str", 3);
        if (_arr_status__tmp117 != 0) {
            *_err2 = _err_alloc__tmp117; return 2;
        }
        _arr_status__tmp117 = til_Array_set(&_err_idx__tmp117, &_tmp116, 0, &_tmp118);
        if (_arr_status__tmp117 != 0) {
            *_err1 = _err_idx__tmp117; return 1;
        }
        _arr_status__tmp117 = til_Array_set(&_err_idx__tmp117, &_tmp116, 1, &_tmp119);
        if (_arr_status__tmp117 != 0) {
            *_err1 = _err_idx__tmp117; return 1;
        }
        _arr_status__tmp117 = til_Array_set(&_err_idx__tmp117, &_tmp116, 2, &_tmp120);
        if (_arr_status__tmp117 != 0) {
            *_err1 = _err_idx__tmp117; return 1;
        }
        int _status__tmp115 = til_format(&_tmp114, &_err0__tmp115, &_err1__tmp115, &_err2__tmp115, ((til_Str){(til_I64)"src/core/str.til:380:48:", 24}), &_tmp116);
        if (_status__tmp115 != 0) {
            if (_status__tmp115 == 2) { *_err1 = _err1__tmp115; return 1; }
            if (_status__tmp115 == 3) { *_err2 = _err2__tmp115; return 2; }
        }
        til_Array_delete(&_tmp116);
        til_Str _tmp121;
        til_I64_OverflowError _err0__tmp122;
        til_IndexOutOfBoundsError _err1__tmp122;
        til_AllocError _err2__tmp122;
        til_Array _tmp123;
        til_AllocError _err_alloc__tmp124;
        til_IndexOutOfBoundsError _err_idx__tmp124;
        til_Str _tmp125 = ((til_Str){(til_I64)"get_substr: start and end are the same (", 40});
        til_Str _tmp126 = til_I64_to_str(til_start);
        til_Str _tmp127 = ((til_Str){(til_I64)"), no substring", 15});
        int _arr_status__tmp124 = til_Array_new(&_tmp123, &_err_alloc__tmp124, "Str", 3);
        if (_arr_status__tmp124 != 0) {
            *_err2 = _err_alloc__tmp124; return 2;
        }
        _arr_status__tmp124 = til_Array_set(&_err_idx__tmp124, &_tmp123, 0, &_tmp125);
        if (_arr_status__tmp124 != 0) {
            *_err1 = _err_idx__tmp124; return 1;
        }
        _arr_status__tmp124 = til_Array_set(&_err_idx__tmp124, &_tmp123, 1, &_tmp126);
        if (_arr_status__tmp124 != 0) {
            *_err1 = _err_idx__tmp124; return 1;
        }
        _arr_status__tmp124 = til_Array_set(&_err_idx__tmp124, &_tmp123, 2, &_tmp127);
        if (_arr_status__tmp124 != 0) {
            *_err1 = _err_idx__tmp124; return 1;
        }
        int _status__tmp122 = til_format(&_tmp121, &_err0__tmp122, &_err1__tmp122, &_err2__tmp122, ((til_Str){(til_I64)"src/core/str.til:380:48:", 24}), &_tmp123);
        if (_status__tmp122 != 0) {
            if (_status__tmp122 == 2) { *_err1 = _err1__tmp122; return 1; }
            if (_status__tmp122 == 3) { *_err2 = _err2__tmp122; return 2; }
        }
        til_Array_delete(&_tmp123);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp121);
        return 1;
    }
    til_Str til_substr = {.c_string = 0, .cap = 0};
    til_substr.cap = til_sub(til_end, til_start);
    til_I64 _ret__tmp128;
    til_AllocError _err0__tmp128 = {};
    int _status__tmp128 = til_malloc(&_ret__tmp128, &_err0__tmp128, til_substr.cap);
    if (_status__tmp128 == 1) { *_err2 = _err0__tmp128; return 2; }
    til_substr.c_string = _ret__tmp128;
    if (til_I64_eq(til_NULL, til_substr.c_string).data) {
        til_Str _tmp130;
        til_I64_OverflowError _err0__tmp131;
        til_IndexOutOfBoundsError _err1__tmp131;
        til_AllocError _err2__tmp131;
        til_Array _tmp132;
        til_AllocError _err_alloc__tmp133;
        til_IndexOutOfBoundsError _err_idx__tmp133;
        til_Str _tmp134 = ((til_Str){(til_I64)"Str.get_substr: failed to allocate ", 35});
        til_Str _tmp135 = til_I64_to_str(til_substr.cap);
        til_Str _tmp136 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp133 = til_Array_new(&_tmp132, &_err_alloc__tmp133, "Str", 3);
        if (_arr_status__tmp133 != 0) {
            *_err2 = _err_alloc__tmp133; return 2;
        }
        _arr_status__tmp133 = til_Array_set(&_err_idx__tmp133, &_tmp132, 0, &_tmp134);
        if (_arr_status__tmp133 != 0) {
            *_err1 = _err_idx__tmp133; return 1;
        }
        _arr_status__tmp133 = til_Array_set(&_err_idx__tmp133, &_tmp132, 1, &_tmp135);
        if (_arr_status__tmp133 != 0) {
            *_err1 = _err_idx__tmp133; return 1;
        }
        _arr_status__tmp133 = til_Array_set(&_err_idx__tmp133, &_tmp132, 2, &_tmp136);
        if (_arr_status__tmp133 != 0) {
            *_err1 = _err_idx__tmp133; return 1;
        }
        int _status__tmp131 = til_format(&_tmp130, &_err0__tmp131, &_err1__tmp131, &_err2__tmp131, ((til_Str){(til_I64)"src/core/str.til:387:37:", 24}), &_tmp132);
        if (_status__tmp131 != 0) {
            if (_status__tmp131 == 2) { *_err1 = _err1__tmp131; return 1; }
            if (_status__tmp131 == 3) { *_err2 = _err2__tmp131; return 2; }
        }
        til_Array_delete(&_tmp132);
        til_Str _tmp137;
        til_I64_OverflowError _err0__tmp138;
        til_IndexOutOfBoundsError _err1__tmp138;
        til_AllocError _err2__tmp138;
        til_Array _tmp139;
        til_AllocError _err_alloc__tmp140;
        til_IndexOutOfBoundsError _err_idx__tmp140;
        til_Str _tmp141 = ((til_Str){(til_I64)"Str.get_substr: failed to allocate ", 35});
        til_Str _tmp142 = til_I64_to_str(til_substr.cap);
        til_Str _tmp143 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp140 = til_Array_new(&_tmp139, &_err_alloc__tmp140, "Str", 3);
        if (_arr_status__tmp140 != 0) {
            *_err2 = _err_alloc__tmp140; return 2;
        }
        _arr_status__tmp140 = til_Array_set(&_err_idx__tmp140, &_tmp139, 0, &_tmp141);
        if (_arr_status__tmp140 != 0) {
            *_err1 = _err_idx__tmp140; return 1;
        }
        _arr_status__tmp140 = til_Array_set(&_err_idx__tmp140, &_tmp139, 1, &_tmp142);
        if (_arr_status__tmp140 != 0) {
            *_err1 = _err_idx__tmp140; return 1;
        }
        _arr_status__tmp140 = til_Array_set(&_err_idx__tmp140, &_tmp139, 2, &_tmp143);
        if (_arr_status__tmp140 != 0) {
            *_err1 = _err_idx__tmp140; return 1;
        }
        int _status__tmp138 = til_format(&_tmp137, &_err0__tmp138, &_err1__tmp138, &_err2__tmp138, ((til_Str){(til_I64)"src/core/str.til:387:37:", 24}), &_tmp139);
        if (_status__tmp138 != 0) {
            if (_status__tmp138 == 2) { *_err1 = _err1__tmp138; return 1; }
            if (_status__tmp138 == 3) { *_err2 = _err2__tmp138; return 2; }
        }
        til_Array_delete(&_tmp139);
        *_err2 = til_AllocError_new(_tmp137);
        return 2;
    }
    til_memcpy(til_substr.c_string, til_add(til_s.c_string, til_start), til_substr.cap);
    *_ret = til_substr;
    return 0;
}

til_Str til_concat(const til_Str til_a, const til_Str til_b) {
    til_AllocError _thrown_AllocError__tmp144;
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_add(til_a.cap, til_b.cap);
    if (til_lt(til_result.cap, til_a.cap).data) {
        til_Array _tmp146;
        til_AllocError _err_alloc__tmp147;
        til_IndexOutOfBoundsError _err_idx__tmp147;
        til_Str _tmp148 = ((til_Str){(til_I64)"concat: integer overflow", 24});
        int _arr_status__tmp147 = til_Array_new(&_tmp146, &_err_alloc__tmp147, "Str", 1);
        if (_arr_status__tmp147 != 0) {
        }
        _arr_status__tmp147 = til_Array_set(&_err_idx__tmp147, &_tmp146, 0, &_tmp148);
        if (_arr_status__tmp147 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:427:15:", 24}), &_tmp146);
        til_Array_delete(&_tmp146);
    }
    til_I64 _ret__tmp149;
    til_AllocError _err0__tmp149 = {};
    int _status__tmp149 = til_malloc(&_ret__tmp149, &_err0__tmp149, til_result.cap);
    if (_status__tmp149 == 0) {
        til_result.c_string = _ret__tmp149;
    } else if (_status__tmp149 == 1) {
        til_AllocError til_err = _err0__tmp149;
        til_Array _tmp151;
        til_AllocError _err_alloc__tmp152;
        til_IndexOutOfBoundsError _err_idx__tmp152;
        til_Str _tmp153 = til_err.msg;
        int _arr_status__tmp152 = til_Array_new(&_tmp151, &_err_alloc__tmp152, "Str", 1);
        if (_arr_status__tmp152 != 0) {
        }
        _arr_status__tmp152 = til_Array_set(&_err_idx__tmp152, &_tmp151, 0, &_tmp153);
        if (_arr_status__tmp152 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:439:15:", 24}), &_tmp151);
        til_Array_delete(&_tmp151);
    }
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Array _tmp155;
        til_AllocError _err_alloc__tmp156;
        til_IndexOutOfBoundsError _err_idx__tmp156;
        til_Str _tmp157 = ((til_Str){(til_I64)"concat: malloc failed", 21});
        int _arr_status__tmp156 = til_Array_new(&_tmp155, &_err_alloc__tmp156, "Str", 1);
        if (_arr_status__tmp156 != 0) {
        }
        _arr_status__tmp156 = til_Array_set(&_err_idx__tmp156, &_tmp155, 0, &_tmp157);
        if (_arr_status__tmp156 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:432:15:", 24}), &_tmp155);
        til_Array_delete(&_tmp155);
    }
    til_memcpy(til_result.c_string, til_a.c_string, til_a.cap);
    til_memcpy(til_add(til_result.c_string, til_a.cap), til_b.c_string, til_b.cap);
    return til_result;
    goto _end_catches__tmp144;
_catch_AllocError__tmp144: {
    til_AllocError til_err = _thrown_AllocError__tmp144;
    til_Array _tmp159;
    til_AllocError _err_alloc__tmp160;
    til_IndexOutOfBoundsError _err_idx__tmp160;
    til_Str _tmp161 = til_err.msg;
    int _arr_status__tmp160 = til_Array_new(&_tmp159, &_err_alloc__tmp160, "Str", 1);
    if (_arr_status__tmp160 != 0) {
    }
    _arr_status__tmp160 = til_Array_set(&_err_idx__tmp160, &_tmp159, 0, &_tmp161);
    if (_arr_status__tmp160 != 0) {
    }
    til_panic(((til_Str){(til_I64)"src/core/str.til:439:15:", 24}), &_tmp159);
    til_Array_delete(&_tmp159);
    }
_end_catches__tmp144:;
}

int til_format(til_Str* _ret, til_I64_OverflowError* _err1, til_IndexOutOfBoundsError* _err2, til_AllocError* _err3, const til_Str til_prefix, til_Array* til_args) {
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_prefix.cap;
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Str til_arg = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp165 = {};
        int _status__tmp165 = til_Array_get(&_err0__tmp165, (*til_args), til_i, (til_Dynamic*)&til_arg);
        if (_status__tmp165 == 1) { *_err2 = _err0__tmp165; return 2; }
        til_result.cap = til_add(til_result.cap, til_arg.cap);
        if (til_lt(til_result.cap, til_arg.cap).data) {
            til_Str _tmp167;
            til_I64_OverflowError _err0__tmp168;
            til_IndexOutOfBoundsError _err1__tmp168;
            til_AllocError _err2__tmp168;
            til_Array _tmp169;
            til_AllocError _err_alloc__tmp170;
            til_IndexOutOfBoundsError _err_idx__tmp170;
            til_Str _tmp171 = ((til_Str){(til_I64)"format: integer overflow while summing cap for arg ", 51});
            til_Str _tmp172 = til_I64_to_str(til_i);
            int _arr_status__tmp170 = til_Array_new(&_tmp169, &_err_alloc__tmp170, "Str", 2);
            if (_arr_status__tmp170 != 0) {
                *_err3 = _err_alloc__tmp170; return 3;
            }
            _arr_status__tmp170 = til_Array_set(&_err_idx__tmp170, &_tmp169, 0, &_tmp171);
            if (_arr_status__tmp170 != 0) {
                *_err2 = _err_idx__tmp170; return 2;
            }
            _arr_status__tmp170 = til_Array_set(&_err_idx__tmp170, &_tmp169, 1, &_tmp172);
            if (_arr_status__tmp170 != 0) {
                *_err2 = _err_idx__tmp170; return 2;
            }
            int _status__tmp168 = til_format(&_tmp167, &_err0__tmp168, &_err1__tmp168, &_err2__tmp168, ((til_Str){(til_I64)"src/core/str.til:455:48:", 24}), &_tmp169);
            if (_status__tmp168 != 0) {
                if (_status__tmp168 == 1) { *_err1 = _err0__tmp168; return 1; }
                if (_status__tmp168 == 2) { *_err2 = _err1__tmp168; return 2; }
                if (_status__tmp168 == 3) { *_err3 = _err2__tmp168; return 3; }
            }
            til_Array_delete(&_tmp169);
            til_Str _tmp173;
            til_I64_OverflowError _err0__tmp174;
            til_IndexOutOfBoundsError _err1__tmp174;
            til_AllocError _err2__tmp174;
            til_Array _tmp175;
            til_AllocError _err_alloc__tmp176;
            til_IndexOutOfBoundsError _err_idx__tmp176;
            til_Str _tmp177 = ((til_Str){(til_I64)"format: integer overflow while summing cap for arg ", 51});
            til_Str _tmp178 = til_I64_to_str(til_i);
            int _arr_status__tmp176 = til_Array_new(&_tmp175, &_err_alloc__tmp176, "Str", 2);
            if (_arr_status__tmp176 != 0) {
                *_err3 = _err_alloc__tmp176; return 3;
            }
            _arr_status__tmp176 = til_Array_set(&_err_idx__tmp176, &_tmp175, 0, &_tmp177);
            if (_arr_status__tmp176 != 0) {
                *_err2 = _err_idx__tmp176; return 2;
            }
            _arr_status__tmp176 = til_Array_set(&_err_idx__tmp176, &_tmp175, 1, &_tmp178);
            if (_arr_status__tmp176 != 0) {
                *_err2 = _err_idx__tmp176; return 2;
            }
            int _status__tmp174 = til_format(&_tmp173, &_err0__tmp174, &_err1__tmp174, &_err2__tmp174, ((til_Str){(til_I64)"src/core/str.til:455:48:", 24}), &_tmp175);
            if (_status__tmp174 != 0) {
                if (_status__tmp174 == 1) { *_err1 = _err0__tmp174; return 1; }
                if (_status__tmp174 == 2) { *_err2 = _err1__tmp174; return 2; }
                if (_status__tmp174 == 3) { *_err3 = _err2__tmp174; return 3; }
            }
            til_Array_delete(&_tmp175);
            *_err1 = til_I64_OverflowError_new(_tmp173);
            return 1;
        }
        til_I64_inc(&til_i);
    }
    til_I64 _ret__tmp179;
    til_AllocError _err0__tmp179 = {};
    int _status__tmp179 = til_malloc(&_ret__tmp179, &_err0__tmp179, til_result.cap);
    if (_status__tmp179 == 1) { *_err3 = _err0__tmp179; return 3; }
    til_result.c_string = _ret__tmp179;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Str _tmp181;
        til_I64_OverflowError _err0__tmp182;
        til_IndexOutOfBoundsError _err1__tmp182;
        til_AllocError _err2__tmp182;
        til_Array _tmp183;
        til_AllocError _err_alloc__tmp184;
        til_IndexOutOfBoundsError _err_idx__tmp184;
        til_Str _tmp185 = ((til_Str){(til_I64)"format: malloc failed for cap = ", 32});
        til_Str _tmp186 = til_I64_to_str(til_result.cap);
        int _arr_status__tmp184 = til_Array_new(&_tmp183, &_err_alloc__tmp184, "Str", 2);
        if (_arr_status__tmp184 != 0) {
            *_err3 = _err_alloc__tmp184; return 3;
        }
        _arr_status__tmp184 = til_Array_set(&_err_idx__tmp184, &_tmp183, 0, &_tmp185);
        if (_arr_status__tmp184 != 0) {
            *_err2 = _err_idx__tmp184; return 2;
        }
        _arr_status__tmp184 = til_Array_set(&_err_idx__tmp184, &_tmp183, 1, &_tmp186);
        if (_arr_status__tmp184 != 0) {
            *_err2 = _err_idx__tmp184; return 2;
        }
        int _status__tmp182 = til_format(&_tmp181, &_err0__tmp182, &_err1__tmp182, &_err2__tmp182, ((til_Str){(til_I64)"src/core/str.til:461:37:", 24}), &_tmp183);
        if (_status__tmp182 != 0) {
            if (_status__tmp182 == 1) { *_err1 = _err0__tmp182; return 1; }
            if (_status__tmp182 == 2) { *_err2 = _err1__tmp182; return 2; }
            if (_status__tmp182 == 3) { *_err3 = _err2__tmp182; return 3; }
        }
        til_Array_delete(&_tmp183);
        til_Str _tmp187;
        til_I64_OverflowError _err0__tmp188;
        til_IndexOutOfBoundsError _err1__tmp188;
        til_AllocError _err2__tmp188;
        til_Array _tmp189;
        til_AllocError _err_alloc__tmp190;
        til_IndexOutOfBoundsError _err_idx__tmp190;
        til_Str _tmp191 = ((til_Str){(til_I64)"format: malloc failed for cap = ", 32});
        til_Str _tmp192 = til_I64_to_str(til_result.cap);
        int _arr_status__tmp190 = til_Array_new(&_tmp189, &_err_alloc__tmp190, "Str", 2);
        if (_arr_status__tmp190 != 0) {
            *_err3 = _err_alloc__tmp190; return 3;
        }
        _arr_status__tmp190 = til_Array_set(&_err_idx__tmp190, &_tmp189, 0, &_tmp191);
        if (_arr_status__tmp190 != 0) {
            *_err2 = _err_idx__tmp190; return 2;
        }
        _arr_status__tmp190 = til_Array_set(&_err_idx__tmp190, &_tmp189, 1, &_tmp192);
        if (_arr_status__tmp190 != 0) {
            *_err2 = _err_idx__tmp190; return 2;
        }
        int _status__tmp188 = til_format(&_tmp187, &_err0__tmp188, &_err1__tmp188, &_err2__tmp188, ((til_Str){(til_I64)"src/core/str.til:461:37:", 24}), &_tmp189);
        if (_status__tmp188 != 0) {
            if (_status__tmp188 == 1) { *_err1 = _err0__tmp188; return 1; }
            if (_status__tmp188 == 2) { *_err2 = _err1__tmp188; return 2; }
            if (_status__tmp188 == 3) { *_err3 = _err2__tmp188; return 3; }
        }
        til_Array_delete(&_tmp189);
        *_err3 = til_AllocError_new(_tmp187);
        return 3;
    }
    til_I64 til_offset = 0;
    til_memcpy(til_result.c_string, til_prefix.c_string, til_prefix.cap);
    til_offset = til_prefix.cap;
    til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Str til_s = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp195 = {};
        int _status__tmp195 = til_Array_get(&_err0__tmp195, (*til_args), til_i, (til_Dynamic*)&til_s);
        if (_status__tmp195 == 1) { *_err2 = _err0__tmp195; return 2; }
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

void til_assert_eq(const til_Str til_loc_str, const til_I64 til_a, const til_I64 til_b) {
    if (til_not(til_I64_eq(til_a, til_b)).data) {
        til_Array _tmp199;
        til_AllocError _err_alloc__tmp200;
        til_IndexOutOfBoundsError _err_idx__tmp200;
        til_Str _tmp201 = til_loc_str;
        til_Str _tmp202 = ((til_Str){(til_I64)"assert_eq failed: expected '", 28});
        til_Str _tmp203 = til_I64_to_str(til_a);
        til_Str _tmp204 = ((til_Str){(til_I64)"', found '", 10});
        til_Str _tmp205 = til_I64_to_str(til_b);
        til_Str _tmp206 = ((til_Str){(til_I64)"'", 1});
        int _arr_status__tmp200 = til_Array_new(&_tmp199, &_err_alloc__tmp200, "Str", 6);
        if (_arr_status__tmp200 != 0) {
        }
        _arr_status__tmp200 = til_Array_set(&_err_idx__tmp200, &_tmp199, 0, &_tmp201);
        if (_arr_status__tmp200 != 0) {
        }
        _arr_status__tmp200 = til_Array_set(&_err_idx__tmp200, &_tmp199, 1, &_tmp202);
        if (_arr_status__tmp200 != 0) {
        }
        _arr_status__tmp200 = til_Array_set(&_err_idx__tmp200, &_tmp199, 2, &_tmp203);
        if (_arr_status__tmp200 != 0) {
        }
        _arr_status__tmp200 = til_Array_set(&_err_idx__tmp200, &_tmp199, 3, &_tmp204);
        if (_arr_status__tmp200 != 0) {
        }
        _arr_status__tmp200 = til_Array_set(&_err_idx__tmp200, &_tmp199, 4, &_tmp205);
        if (_arr_status__tmp200 != 0) {
        }
        _arr_status__tmp200 = til_Array_set(&_err_idx__tmp200, &_tmp199, 5, &_tmp206);
        if (_arr_status__tmp200 != 0) {
        }
        til_println(&_tmp199);
        til_Array_delete(&_tmp199);
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

int til_Array_new(til_Array* _ret, til_AllocError* _err1, const til_Type til_T, const til_I64 til_capacity) {
    til_Array til_arr = {.type_name = ((til_Str){(til_I64)"", 0}), .type_size = 0, .ptr = 0, ._len = 0};
    til_arr.type_name = ((til_Str){(til_I64)"T", 1});
    til_arr.type_size = til_size_of(((til_Str){(til_I64)til_T, strlen(til_T)}));
    const til_I64 til_size_bytes = til_mul(til_capacity, til_arr.type_size);
    til_I64 _ret__tmp220;
    til_AllocError _err0__tmp220 = {};
    int _status__tmp220 = til_malloc(&_ret__tmp220, &_err0__tmp220, til_size_bytes);
    if (_status__tmp220 == 1) { *_err1 = _err0__tmp220; return 1; }
    til_arr.ptr = _ret__tmp220;
    til_U8 _tmp221;
    til_U8_OverflowError _err0__tmp222;
    int _status__tmp222 = til_U8_from_i64(&_tmp221, &_err0__tmp222, 0);
    if (_status__tmp222 != 0) {
    }
    til_memset(til_arr.ptr, _tmp221, til_size_bytes);
    til_arr._len = til_capacity;
    *_ret = til_arr;
    return 0;
}

int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array til_self, const til_I64 til_index, til_Dynamic* til_T) {
    if (til_gteq(til_index, til_self._len).data) {
        til_Str _tmp225;
        til_I64_OverflowError _err0__tmp226;
        til_IndexOutOfBoundsError _err1__tmp226;
        til_AllocError _err2__tmp226;
        til_Array _tmp227;
        til_AllocError _err_alloc__tmp228;
        til_IndexOutOfBoundsError _err_idx__tmp228;
        til_Str _tmp229 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        int _arr_status__tmp228 = til_Array_new(&_tmp227, &_err_alloc__tmp228, "Str", 1);
        if (_arr_status__tmp228 != 0) {
        }
        _arr_status__tmp228 = til_Array_set(&_err_idx__tmp228, &_tmp227, 0, &_tmp229);
        if (_arr_status__tmp228 != 0) {
            *_err1 = _err_idx__tmp228; return 1;
        }
        int _status__tmp226 = til_format(&_tmp225, &_err0__tmp226, &_err1__tmp226, &_err2__tmp226, ((til_Str){(til_I64)"src/core/array.til:41:52:", 25}), &_tmp227);
        if (_status__tmp226 != 0) {
            if (_status__tmp226 == 2) { *_err1 = _err1__tmp226; return 1; }
        }
        til_Array_delete(&_tmp227);
        til_Str _tmp230;
        til_I64_OverflowError _err0__tmp231;
        til_IndexOutOfBoundsError _err1__tmp231;
        til_AllocError _err2__tmp231;
        til_Array _tmp232;
        til_AllocError _err_alloc__tmp233;
        til_IndexOutOfBoundsError _err_idx__tmp233;
        til_Str _tmp234 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        int _arr_status__tmp233 = til_Array_new(&_tmp232, &_err_alloc__tmp233, "Str", 1);
        if (_arr_status__tmp233 != 0) {
        }
        _arr_status__tmp233 = til_Array_set(&_err_idx__tmp233, &_tmp232, 0, &_tmp234);
        if (_arr_status__tmp233 != 0) {
            *_err1 = _err_idx__tmp233; return 1;
        }
        int _status__tmp231 = til_format(&_tmp230, &_err0__tmp231, &_err1__tmp231, &_err2__tmp231, ((til_Str){(til_I64)"src/core/array.til:41:52:", 25}), &_tmp232);
        if (_status__tmp231 != 0) {
            if (_status__tmp231 == 2) { *_err1 = _err1__tmp231; return 1; }
        }
        til_Array_delete(&_tmp232);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp230);
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_gteq(til_index, til_self->_len).data) {
        til_Str _tmp237;
        til_I64_OverflowError _err0__tmp238;
        til_IndexOutOfBoundsError _err1__tmp238;
        til_AllocError _err2__tmp238;
        til_Array _tmp239;
        til_AllocError _err_alloc__tmp240;
        til_IndexOutOfBoundsError _err_idx__tmp240;
        til_Str _tmp241 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        int _arr_status__tmp240 = til_Array_new(&_tmp239, &_err_alloc__tmp240, "Str", 1);
        if (_arr_status__tmp240 != 0) {
        }
        _arr_status__tmp240 = til_Array_set(&_err_idx__tmp240, &_tmp239, 0, &_tmp241);
        if (_arr_status__tmp240 != 0) {
            *_err1 = _err_idx__tmp240; return 1;
        }
        int _status__tmp238 = til_format(&_tmp237, &_err0__tmp238, &_err1__tmp238, &_err2__tmp238, ((til_Str){(til_I64)"src/core/array.til:56:52:", 25}), &_tmp239);
        if (_status__tmp238 != 0) {
            if (_status__tmp238 == 2) { *_err1 = _err1__tmp238; return 1; }
        }
        til_Array_delete(&_tmp239);
        til_Str _tmp242;
        til_I64_OverflowError _err0__tmp243;
        til_IndexOutOfBoundsError _err1__tmp243;
        til_AllocError _err2__tmp243;
        til_Array _tmp244;
        til_AllocError _err_alloc__tmp245;
        til_IndexOutOfBoundsError _err_idx__tmp245;
        til_Str _tmp246 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        int _arr_status__tmp245 = til_Array_new(&_tmp244, &_err_alloc__tmp245, "Str", 1);
        if (_arr_status__tmp245 != 0) {
        }
        _arr_status__tmp245 = til_Array_set(&_err_idx__tmp245, &_tmp244, 0, &_tmp246);
        if (_arr_status__tmp245 != 0) {
            *_err1 = _err_idx__tmp245; return 1;
        }
        int _status__tmp243 = til_format(&_tmp242, &_err0__tmp243, &_err1__tmp243, &_err2__tmp243, ((til_Str){(til_I64)"src/core/array.til:56:52:", 25}), &_tmp244);
        if (_status__tmp243 != 0) {
            if (_status__tmp243 == 2) { *_err1 = _err1__tmp243; return 1; }
        }
        til_Array_delete(&_tmp244);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp242);
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

int til_Vec_new(til_Vec* _ret, til_AllocError* _err1, const til_Type til_T) {
    til_Vec til_vec = {.type_name = ((til_Str){(til_I64)"", 0}), .type_size = 0, .ptr = 0, ._len = 0, .cap = 0};
    til_vec.type_name = ((til_Str){(til_I64)"T", 1});
    til_vec.type_size = til_size_of(((til_Str){(til_I64)til_T, strlen(til_T)}));
    const til_I64 til_size_bytes = til_mul(til_Vec_INIT_CAP, til_vec.type_size);
    til_I64 _ret__tmp258;
    til_AllocError _err0__tmp258 = {};
    int _status__tmp258 = til_malloc(&_ret__tmp258, &_err0__tmp258, til_size_bytes);
    if (_status__tmp258 == 1) { *_err1 = _err0__tmp258; return 1; }
    til_vec.ptr = _ret__tmp258;
    til_vec._len = 0;
    til_vec.cap = til_Vec_INIT_CAP;
    *_ret = til_vec;
    return 0;
}

int til_Vec_push(til_AllocError* _err1, til_Vec* til_self, const til_Dynamic til_value) {
    if (til_I64_eq(til_self->_len, til_self->cap).data) {
        const til_I64 til_new_cap = til_mul(til_self->cap, 2);
        if (til_gt(til_new_cap, til_Vec_MAX_CAP).data) {
            til_Array _tmp262;
            til_AllocError _err_alloc__tmp263;
            til_IndexOutOfBoundsError _err_idx__tmp263;
            til_Str _tmp264 = ((til_Str){(til_I64)"Vec.push: capacity exceeded Vec.MAX_CAP", 39});
            int _arr_status__tmp263 = til_Array_new(&_tmp262, &_err_alloc__tmp263, "Str", 1);
            if (_arr_status__tmp263 != 0) {
                *_err1 = _err_alloc__tmp263; return 1;
            }
            _arr_status__tmp263 = til_Array_set(&_err_idx__tmp263, &_tmp262, 0, &_tmp264);
            if (_arr_status__tmp263 != 0) {
            }
            til_panic(((til_Str){(til_I64)"src/core/vec.til:63:23:", 23}), &_tmp262);
            til_Array_delete(&_tmp262);
        }
        til_I64 _ret__tmp265;
        til_I64 til_new_ptr;
        til_AllocError _err0__tmp265 = {};
        int _status__tmp265 = til_malloc(&_ret__tmp265, &_err0__tmp265, til_mul(til_new_cap, til_self->type_size));
        if (_status__tmp265 == 1) { *_err1 = _err0__tmp265; return 1; }
        til_new_ptr = _ret__tmp265;
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
        til_Str _tmp268;
        til_I64_OverflowError _err0__tmp269;
        til_IndexOutOfBoundsError _err1__tmp269;
        til_AllocError _err2__tmp269;
        til_Array _tmp270;
        til_AllocError _err_alloc__tmp271;
        til_IndexOutOfBoundsError _err_idx__tmp271;
        til_Str _tmp272 = ((til_Str){(til_I64)"Vec.get: index out of bounds", 28});
        int _arr_status__tmp271 = til_Array_new(&_tmp270, &_err_alloc__tmp271, "Str", 1);
        if (_arr_status__tmp271 != 0) {
        }
        _arr_status__tmp271 = til_Array_set(&_err_idx__tmp271, &_tmp270, 0, &_tmp272);
        if (_arr_status__tmp271 != 0) {
            *_err1 = _err_idx__tmp271; return 1;
        }
        int _status__tmp269 = til_format(&_tmp268, &_err0__tmp269, &_err1__tmp269, &_err2__tmp269, ((til_Str){(til_I64)"src/core/vec.til:81:52:", 23}), &_tmp270);
        if (_status__tmp269 != 0) {
            if (_status__tmp269 == 2) { *_err1 = _err1__tmp269; return 1; }
        }
        til_Array_delete(&_tmp270);
        til_Str _tmp273;
        til_I64_OverflowError _err0__tmp274;
        til_IndexOutOfBoundsError _err1__tmp274;
        til_AllocError _err2__tmp274;
        til_Array _tmp275;
        til_AllocError _err_alloc__tmp276;
        til_IndexOutOfBoundsError _err_idx__tmp276;
        til_Str _tmp277 = ((til_Str){(til_I64)"Vec.get: index out of bounds", 28});
        int _arr_status__tmp276 = til_Array_new(&_tmp275, &_err_alloc__tmp276, "Str", 1);
        if (_arr_status__tmp276 != 0) {
        }
        _arr_status__tmp276 = til_Array_set(&_err_idx__tmp276, &_tmp275, 0, &_tmp277);
        if (_arr_status__tmp276 != 0) {
            *_err1 = _err_idx__tmp276; return 1;
        }
        int _status__tmp274 = til_format(&_tmp273, &_err0__tmp274, &_err1__tmp274, &_err2__tmp274, ((til_Str){(til_I64)"src/core/vec.til:81:52:", 23}), &_tmp275);
        if (_status__tmp274 != 0) {
            if (_status__tmp274 == 2) { *_err1 = _err1__tmp274; return 1; }
        }
        til_Array_delete(&_tmp275);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp273);
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

int til_Str_clone(til_Str* _ret, til_AllocError* _err1, const til_Str til_self) {
    til_Str til_cloned = {.c_string = 0, .cap = 0};
    til_cloned.cap = til_self.cap;
    til_I64 _ret__tmp285;
    til_AllocError _err0__tmp285 = {};
    int _status__tmp285 = til_malloc(&_ret__tmp285, &_err0__tmp285, til_cloned.cap);
    if (_status__tmp285 == 1) { *_err1 = _err0__tmp285; return 1; }
    til_cloned.c_string = _ret__tmp285;
    if (til_I64_eq(til_NULL, til_cloned.c_string).data) {
        til_Str _tmp287;
        til_I64_OverflowError _err0__tmp288;
        til_IndexOutOfBoundsError _err1__tmp288;
        til_AllocError _err2__tmp288;
        til_Array _tmp289;
        til_AllocError _err_alloc__tmp290;
        til_IndexOutOfBoundsError _err_idx__tmp290;
        til_Str _tmp291 = ((til_Str){(til_I64)"Str.clone: malloc failed for ", 29});
        til_Str _tmp292 = til_I64_to_str(til_cloned.cap);
        til_Str _tmp293 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp290 = til_Array_new(&_tmp289, &_err_alloc__tmp290, "Str", 3);
        if (_arr_status__tmp290 != 0) {
            *_err1 = _err_alloc__tmp290; return 1;
        }
        _arr_status__tmp290 = til_Array_set(&_err_idx__tmp290, &_tmp289, 0, &_tmp291);
        if (_arr_status__tmp290 != 0) {
        }
        _arr_status__tmp290 = til_Array_set(&_err_idx__tmp290, &_tmp289, 1, &_tmp292);
        if (_arr_status__tmp290 != 0) {
        }
        _arr_status__tmp290 = til_Array_set(&_err_idx__tmp290, &_tmp289, 2, &_tmp293);
        if (_arr_status__tmp290 != 0) {
        }
        int _status__tmp288 = til_format(&_tmp287, &_err0__tmp288, &_err1__tmp288, &_err2__tmp288, ((til_Str){(til_I64)"src/core/str.til:46:41:", 23}), &_tmp289);
        if (_status__tmp288 != 0) {
            if (_status__tmp288 == 3) { *_err1 = _err2__tmp288; return 1; }
        }
        til_Array_delete(&_tmp289);
        til_Str _tmp294;
        til_I64_OverflowError _err0__tmp295;
        til_IndexOutOfBoundsError _err1__tmp295;
        til_AllocError _err2__tmp295;
        til_Array _tmp296;
        til_AllocError _err_alloc__tmp297;
        til_IndexOutOfBoundsError _err_idx__tmp297;
        til_Str _tmp298 = ((til_Str){(til_I64)"Str.clone: malloc failed for ", 29});
        til_Str _tmp299 = til_I64_to_str(til_cloned.cap);
        til_Str _tmp300 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp297 = til_Array_new(&_tmp296, &_err_alloc__tmp297, "Str", 3);
        if (_arr_status__tmp297 != 0) {
            *_err1 = _err_alloc__tmp297; return 1;
        }
        _arr_status__tmp297 = til_Array_set(&_err_idx__tmp297, &_tmp296, 0, &_tmp298);
        if (_arr_status__tmp297 != 0) {
        }
        _arr_status__tmp297 = til_Array_set(&_err_idx__tmp297, &_tmp296, 1, &_tmp299);
        if (_arr_status__tmp297 != 0) {
        }
        _arr_status__tmp297 = til_Array_set(&_err_idx__tmp297, &_tmp296, 2, &_tmp300);
        if (_arr_status__tmp297 != 0) {
        }
        int _status__tmp295 = til_format(&_tmp294, &_err0__tmp295, &_err1__tmp295, &_err2__tmp295, ((til_Str){(til_I64)"src/core/str.til:46:41:", 23}), &_tmp296);
        if (_status__tmp295 != 0) {
            if (_status__tmp295 == 3) { *_err1 = _err2__tmp295; return 1; }
        }
        til_Array_delete(&_tmp296);
        *_err1 = til_AllocError_new(_tmp294);
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
    while (til_lteq(til_start_idx, til_max_start).data) {
        til_Bool til_matches = true;
        til_I64 til_needle_idx = 0;
        while (til_lt(til_needle_idx, til_Str_len(til_needle)).data) {
            if (til_not(til_matches).data) {
                til_needle_idx = til_Str_len(til_needle);
            } else {
                til_I64 til_self_byte = 0;
                til_I64 til_needle_byte = 0;
                til_memcpy((til_I64)&til_self_byte, til_add(til_self.c_string, til_add(til_start_idx, til_needle_idx)), 1);
                til_memcpy((til_I64)&til_needle_byte, til_add(til_needle.c_string, til_needle_idx), 1);
                if (til_not(til_U8_eq(til_self_byte, til_needle_byte)).data) {
                    til_matches = false;
                }
                til_needle_idx = til_add(til_needle_idx, 1);
            }
        }
        if (til_matches.data) {
            return til_start_idx;
        }
        til_start_idx = til_add(til_start_idx, 1);
    }
    return -1;
}

int til_Str_replacen(til_Str* _ret, til_AllocError* _err1, const til_Str til_self, const til_Str til_from, const til_Str til_to, const til_I64 til_n) {
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp319;
    if (til_I64_eq(til_Str_len(til_from), 0).data) {
        til_Str _ret__tmp321;
        til_AllocError _err0__tmp321 = {};
        int _status__tmp321 = til_Str_clone(&_ret__tmp321, &_err0__tmp321, til_self);
        if (_status__tmp321 == 1) { *_err1 = _err0__tmp321; return 1; }
        *_ret = _ret__tmp321;
        return 0;
    }
    if (til_I64_eq(til_n, 0).data) {
        til_Str _ret__tmp323;
        til_AllocError _err0__tmp323 = {};
        int _status__tmp323 = til_Str_clone(&_ret__tmp323, &_err0__tmp323, til_self);
        if (_status__tmp323 == 1) { *_err1 = _err0__tmp323; return 1; }
        *_ret = _ret__tmp323;
        return 0;
    }
    til_I64 til_idx = til_Str_find(til_self, til_from);
    if (til_lt(til_idx, 0).data) {
        til_Str _ret__tmp325;
        til_AllocError _err0__tmp325 = {};
        int _status__tmp325 = til_Str_clone(&_ret__tmp325, &_err0__tmp325, til_self);
        if (_status__tmp325 == 1) { *_err1 = _err0__tmp325; return 1; }
        *_ret = _ret__tmp325;
        return 0;
    }
    til_Str _ret__tmp326;
    til_Str til_prefix;
    til_IndexOutOfBoundsError _err0__tmp326 = {};
    til_AllocError _err1__tmp326 = {};
    int _status__tmp326 = til_get_substr(&_ret__tmp326, &_err0__tmp326, &_err1__tmp326, til_self, 0, til_idx);
    if (_status__tmp326 == 2) { *_err1 = _err1__tmp326; return 1; }
    til_prefix = _ret__tmp326;
    til_Str _ret__tmp327;
    til_Str til_suffix;
    til_IndexOutOfBoundsError _err0__tmp327 = {};
    til_AllocError _err1__tmp327 = {};
    int _status__tmp327 = til_get_substr(&_ret__tmp327, &_err0__tmp327, &_err1__tmp327, til_self, til_add(til_idx, til_Str_len(til_from)), til_Str_len(til_self));
    if (_status__tmp327 == 2) { *_err1 = _err1__tmp327; return 1; }
    til_suffix = _ret__tmp327;
    til_Str til_result = til_concat(til_concat(til_prefix, til_to), til_suffix);
    if (til_gt(til_n, 1).data) {
        til_Str _ret__tmp329;
        til_Str til_rest;
        til_AllocError _err0__tmp329 = {};
        int _status__tmp329 = til_Str_replacen(&_ret__tmp329, &_err0__tmp329, til_suffix, til_from, til_to, til_sub(til_n, 1));
        if (_status__tmp329 == 1) { *_err1 = _err0__tmp329; return 1; }
        til_rest = _ret__tmp329;
        til_result = til_concat(til_concat(til_prefix, til_to), til_rest);
    }
    *_ret = til_result;
    return 0;
    goto _end_catches__tmp319;
_catch_IndexOutOfBoundsError__tmp319: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp319;
    til_Str _ret__tmp331;
    til_AllocError _err0__tmp331 = {};
    int _status__tmp331 = til_Str_clone(&_ret__tmp331, &_err0__tmp331, til_self);
    if (_status__tmp331 == 1) { *_err1 = _err0__tmp331; return 1; }
    til_result = _ret__tmp331;
    }
_end_catches__tmp319:;
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
        til_Str _tmp337;
        til_I64_OverflowError _err0__tmp338;
        til_IndexOutOfBoundsError _err1__tmp338;
        til_AllocError _err2__tmp338;
        til_Array _tmp339;
        til_AllocError _err_alloc__tmp340;
        til_IndexOutOfBoundsError _err_idx__tmp340;
        til_Str _tmp341 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        int _arr_status__tmp340 = til_Array_new(&_tmp339, &_err_alloc__tmp340, "Str", 1);
        if (_arr_status__tmp340 != 0) {
        }
        _arr_status__tmp340 = til_Array_set(&_err_idx__tmp340, &_tmp339, 0, &_tmp341);
        if (_arr_status__tmp340 != 0) {
        }
        int _status__tmp338 = til_format(&_tmp337, &_err0__tmp338, &_err1__tmp338, &_err2__tmp338, ((til_Str){(til_I64)"src/core/u8.til:56:47:", 22}), &_tmp339);
        if (_status__tmp338 != 0) {
        }
        til_Array_delete(&_tmp339);
        til_Str _tmp342;
        til_I64_OverflowError _err0__tmp343;
        til_IndexOutOfBoundsError _err1__tmp343;
        til_AllocError _err2__tmp343;
        til_Array _tmp344;
        til_AllocError _err_alloc__tmp345;
        til_IndexOutOfBoundsError _err_idx__tmp345;
        til_Str _tmp346 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        int _arr_status__tmp345 = til_Array_new(&_tmp344, &_err_alloc__tmp345, "Str", 1);
        if (_arr_status__tmp345 != 0) {
        }
        _arr_status__tmp345 = til_Array_set(&_err_idx__tmp345, &_tmp344, 0, &_tmp346);
        if (_arr_status__tmp345 != 0) {
        }
        int _status__tmp343 = til_format(&_tmp342, &_err0__tmp343, &_err1__tmp343, &_err2__tmp343, ((til_Str){(til_I64)"src/core/u8.til:56:47:", 22}), &_tmp344);
        if (_status__tmp343 != 0) {
        }
        til_Array_delete(&_tmp344);
        *_err1 = til_U8_OverflowError_new(_tmp342);
        return 1;
    }
    if (til_gt(til_self, til_MAX_U8).data) {
        til_Str _tmp348;
        til_I64_OverflowError _err0__tmp349;
        til_IndexOutOfBoundsError _err1__tmp349;
        til_AllocError _err2__tmp349;
        til_Array _tmp350;
        til_AllocError _err_alloc__tmp351;
        til_IndexOutOfBoundsError _err_idx__tmp351;
        til_Str _tmp352 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp353 = ((til_Str){(til_I64)"255", 3});
        int _arr_status__tmp351 = til_Array_new(&_tmp350, &_err_alloc__tmp351, "Str", 2);
        if (_arr_status__tmp351 != 0) {
        }
        _arr_status__tmp351 = til_Array_set(&_err_idx__tmp351, &_tmp350, 0, &_tmp352);
        if (_arr_status__tmp351 != 0) {
        }
        _arr_status__tmp351 = til_Array_set(&_err_idx__tmp351, &_tmp350, 1, &_tmp353);
        if (_arr_status__tmp351 != 0) {
        }
        int _status__tmp349 = til_format(&_tmp348, &_err0__tmp349, &_err1__tmp349, &_err2__tmp349, ((til_Str){(til_I64)"src/core/u8.til:59:47:", 22}), &_tmp350);
        if (_status__tmp349 != 0) {
        }
        til_Array_delete(&_tmp350);
        til_Str _tmp354;
        til_I64_OverflowError _err0__tmp355;
        til_IndexOutOfBoundsError _err1__tmp355;
        til_AllocError _err2__tmp355;
        til_Array _tmp356;
        til_AllocError _err_alloc__tmp357;
        til_IndexOutOfBoundsError _err_idx__tmp357;
        til_Str _tmp358 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp359 = ((til_Str){(til_I64)"255", 3});
        int _arr_status__tmp357 = til_Array_new(&_tmp356, &_err_alloc__tmp357, "Str", 2);
        if (_arr_status__tmp357 != 0) {
        }
        _arr_status__tmp357 = til_Array_set(&_err_idx__tmp357, &_tmp356, 0, &_tmp358);
        if (_arr_status__tmp357 != 0) {
        }
        _arr_status__tmp357 = til_Array_set(&_err_idx__tmp357, &_tmp356, 1, &_tmp359);
        if (_arr_status__tmp357 != 0) {
        }
        int _status__tmp355 = til_format(&_tmp354, &_err0__tmp355, &_err1__tmp355, &_err2__tmp355, ((til_Str){(til_I64)"src/core/u8.til:59:47:", 22}), &_tmp356);
        if (_status__tmp355 != 0) {
        }
        til_Array_delete(&_tmp356);
        *_err1 = til_U8_OverflowError_new(_tmp354);
        return 1;
    }
    *_ret = til_i64_to_u8(til_self);
    return 0;
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
