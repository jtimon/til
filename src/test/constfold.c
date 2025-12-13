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
    goto _end_catches__tmp2;
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
    goto _end_catches__tmp11;
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
    goto _end_catches__tmp20;
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

void til_println(til_Array* til_args) {
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp34;
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Str til_val = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp37 = {};
        int _status__tmp37 = til_Array_get(&_err0__tmp37, (*til_args), til_i, (til_Dynamic*)&til_val);
        if (_status__tmp37 == 1) { _thrown_IndexOutOfBoundsError__tmp34 = _err0__tmp37; goto _catch_IndexOutOfBoundsError__tmp34; }
        til_single_print(til_val);
        til_I64_inc(&til_i);
    }
    til_single_print(((til_Str){(til_I64)"\n", 1}));
    til_print_flush();
    goto _end_catches__tmp34;
_catch_IndexOutOfBoundsError__tmp34: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp34;
    til_Array _tmp39;
    til_AllocError _err_alloc__tmp40;
    til_IndexOutOfBoundsError _err_idx__tmp40;
    til_Str _tmp41 = ((til_Str){(til_I64)"println: IndexOutOfBoundsError should never happen", 50});
    int _arr_status__tmp40 = til_Array_new(&_tmp39, &_err_alloc__tmp40, "Str", 1);
    if (_arr_status__tmp40 != 0) {
    }
    _arr_status__tmp40 = til_Array_set(&_err_idx__tmp40, &_tmp39, 0, &_tmp41);
    if (_arr_status__tmp40 != 0) {
    }
    til_panic(((til_Str){(til_I64)"src/core/print.til:31:15:", 25}), &_tmp39);
    til_Array_delete(&_tmp39);
    goto _end_catches__tmp34;
    }
_end_catches__tmp34:;
}

int til_get_substr(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_start, const til_I64 til_end) {
    if (til_lt(til_start, 0).data) {
        til_Str _tmp44;
        til_I64_OverflowError _err0__tmp45;
        til_IndexOutOfBoundsError _err1__tmp45;
        til_AllocError _err2__tmp45;
        til_Array _tmp46;
        til_AllocError _err_alloc__tmp47;
        til_IndexOutOfBoundsError _err_idx__tmp47;
        til_Str _tmp48 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp49 = til_I64_to_str(til_start);
        til_Str _tmp50 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp47 = til_Array_new(&_tmp46, &_err_alloc__tmp47, "Str", 3);
        if (_arr_status__tmp47 != 0) {
            *_err2 = _err_alloc__tmp47; return 2;
        }
        _arr_status__tmp47 = til_Array_set(&_err_idx__tmp47, &_tmp46, 0, &_tmp48);
        if (_arr_status__tmp47 != 0) {
            *_err1 = _err_idx__tmp47; return 1;
        }
        _arr_status__tmp47 = til_Array_set(&_err_idx__tmp47, &_tmp46, 1, &_tmp49);
        if (_arr_status__tmp47 != 0) {
            *_err1 = _err_idx__tmp47; return 1;
        }
        _arr_status__tmp47 = til_Array_set(&_err_idx__tmp47, &_tmp46, 2, &_tmp50);
        if (_arr_status__tmp47 != 0) {
            *_err1 = _err_idx__tmp47; return 1;
        }
        int _status__tmp45 = til_format(&_tmp44, &_err0__tmp45, &_err1__tmp45, &_err2__tmp45, ((til_Str){(til_I64)"src/core/str.til:368:48:", 24}), &_tmp46);
        if (_status__tmp45 != 0) {
            if (_status__tmp45 == 2) { *_err1 = _err1__tmp45; return 1; }
            if (_status__tmp45 == 3) { *_err2 = _err2__tmp45; return 2; }
        }
        til_Array_delete(&_tmp46);
        til_Str _tmp51;
        til_I64_OverflowError _err0__tmp52;
        til_IndexOutOfBoundsError _err1__tmp52;
        til_AllocError _err2__tmp52;
        til_Array _tmp53;
        til_AllocError _err_alloc__tmp54;
        til_IndexOutOfBoundsError _err_idx__tmp54;
        til_Str _tmp55 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp56 = til_I64_to_str(til_start);
        til_Str _tmp57 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp54 = til_Array_new(&_tmp53, &_err_alloc__tmp54, "Str", 3);
        if (_arr_status__tmp54 != 0) {
            *_err2 = _err_alloc__tmp54; return 2;
        }
        _arr_status__tmp54 = til_Array_set(&_err_idx__tmp54, &_tmp53, 0, &_tmp55);
        if (_arr_status__tmp54 != 0) {
            *_err1 = _err_idx__tmp54; return 1;
        }
        _arr_status__tmp54 = til_Array_set(&_err_idx__tmp54, &_tmp53, 1, &_tmp56);
        if (_arr_status__tmp54 != 0) {
            *_err1 = _err_idx__tmp54; return 1;
        }
        _arr_status__tmp54 = til_Array_set(&_err_idx__tmp54, &_tmp53, 2, &_tmp57);
        if (_arr_status__tmp54 != 0) {
            *_err1 = _err_idx__tmp54; return 1;
        }
        int _status__tmp52 = til_format(&_tmp51, &_err0__tmp52, &_err1__tmp52, &_err2__tmp52, ((til_Str){(til_I64)"src/core/str.til:368:48:", 24}), &_tmp53);
        if (_status__tmp52 != 0) {
            if (_status__tmp52 == 2) { *_err1 = _err1__tmp52; return 1; }
            if (_status__tmp52 == 3) { *_err2 = _err2__tmp52; return 2; }
        }
        til_Array_delete(&_tmp53);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp51);
        return 1;
    }
    if (til_lt(til_end, 0).data) {
        til_Str _tmp59;
        til_I64_OverflowError _err0__tmp60;
        til_IndexOutOfBoundsError _err1__tmp60;
        til_AllocError _err2__tmp60;
        til_Array _tmp61;
        til_AllocError _err_alloc__tmp62;
        til_IndexOutOfBoundsError _err_idx__tmp62;
        til_Str _tmp63 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp64 = til_I64_to_str(til_end);
        til_Str _tmp65 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp62 = til_Array_new(&_tmp61, &_err_alloc__tmp62, "Str", 3);
        if (_arr_status__tmp62 != 0) {
            *_err2 = _err_alloc__tmp62; return 2;
        }
        _arr_status__tmp62 = til_Array_set(&_err_idx__tmp62, &_tmp61, 0, &_tmp63);
        if (_arr_status__tmp62 != 0) {
            *_err1 = _err_idx__tmp62; return 1;
        }
        _arr_status__tmp62 = til_Array_set(&_err_idx__tmp62, &_tmp61, 1, &_tmp64);
        if (_arr_status__tmp62 != 0) {
            *_err1 = _err_idx__tmp62; return 1;
        }
        _arr_status__tmp62 = til_Array_set(&_err_idx__tmp62, &_tmp61, 2, &_tmp65);
        if (_arr_status__tmp62 != 0) {
            *_err1 = _err_idx__tmp62; return 1;
        }
        int _status__tmp60 = til_format(&_tmp59, &_err0__tmp60, &_err1__tmp60, &_err2__tmp60, ((til_Str){(til_I64)"src/core/str.til:371:48:", 24}), &_tmp61);
        if (_status__tmp60 != 0) {
            if (_status__tmp60 == 2) { *_err1 = _err1__tmp60; return 1; }
            if (_status__tmp60 == 3) { *_err2 = _err2__tmp60; return 2; }
        }
        til_Array_delete(&_tmp61);
        til_Str _tmp66;
        til_I64_OverflowError _err0__tmp67;
        til_IndexOutOfBoundsError _err1__tmp67;
        til_AllocError _err2__tmp67;
        til_Array _tmp68;
        til_AllocError _err_alloc__tmp69;
        til_IndexOutOfBoundsError _err_idx__tmp69;
        til_Str _tmp70 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp71 = til_I64_to_str(til_end);
        til_Str _tmp72 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp69 = til_Array_new(&_tmp68, &_err_alloc__tmp69, "Str", 3);
        if (_arr_status__tmp69 != 0) {
            *_err2 = _err_alloc__tmp69; return 2;
        }
        _arr_status__tmp69 = til_Array_set(&_err_idx__tmp69, &_tmp68, 0, &_tmp70);
        if (_arr_status__tmp69 != 0) {
            *_err1 = _err_idx__tmp69; return 1;
        }
        _arr_status__tmp69 = til_Array_set(&_err_idx__tmp69, &_tmp68, 1, &_tmp71);
        if (_arr_status__tmp69 != 0) {
            *_err1 = _err_idx__tmp69; return 1;
        }
        _arr_status__tmp69 = til_Array_set(&_err_idx__tmp69, &_tmp68, 2, &_tmp72);
        if (_arr_status__tmp69 != 0) {
            *_err1 = _err_idx__tmp69; return 1;
        }
        int _status__tmp67 = til_format(&_tmp66, &_err0__tmp67, &_err1__tmp67, &_err2__tmp67, ((til_Str){(til_I64)"src/core/str.til:371:48:", 24}), &_tmp68);
        if (_status__tmp67 != 0) {
            if (_status__tmp67 == 2) { *_err1 = _err1__tmp67; return 1; }
            if (_status__tmp67 == 3) { *_err2 = _err2__tmp67; return 2; }
        }
        til_Array_delete(&_tmp68);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp66);
        return 1;
    }
    if (til_gt(til_start, til_end).data) {
        til_Str _tmp74;
        til_I64_OverflowError _err0__tmp75;
        til_IndexOutOfBoundsError _err1__tmp75;
        til_AllocError _err2__tmp75;
        til_Array _tmp76;
        til_AllocError _err_alloc__tmp77;
        til_IndexOutOfBoundsError _err_idx__tmp77;
        til_Str _tmp78 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp79 = til_I64_to_str(til_start);
        til_Str _tmp80 = ((til_Str){(til_I64)" is greater than end index ", 27});
        til_Str _tmp81 = til_I64_to_str(til_end);
        int _arr_status__tmp77 = til_Array_new(&_tmp76, &_err_alloc__tmp77, "Str", 4);
        if (_arr_status__tmp77 != 0) {
            *_err2 = _err_alloc__tmp77; return 2;
        }
        _arr_status__tmp77 = til_Array_set(&_err_idx__tmp77, &_tmp76, 0, &_tmp78);
        if (_arr_status__tmp77 != 0) {
            *_err1 = _err_idx__tmp77; return 1;
        }
        _arr_status__tmp77 = til_Array_set(&_err_idx__tmp77, &_tmp76, 1, &_tmp79);
        if (_arr_status__tmp77 != 0) {
            *_err1 = _err_idx__tmp77; return 1;
        }
        _arr_status__tmp77 = til_Array_set(&_err_idx__tmp77, &_tmp76, 2, &_tmp80);
        if (_arr_status__tmp77 != 0) {
            *_err1 = _err_idx__tmp77; return 1;
        }
        _arr_status__tmp77 = til_Array_set(&_err_idx__tmp77, &_tmp76, 3, &_tmp81);
        if (_arr_status__tmp77 != 0) {
            *_err1 = _err_idx__tmp77; return 1;
        }
        int _status__tmp75 = til_format(&_tmp74, &_err0__tmp75, &_err1__tmp75, &_err2__tmp75, ((til_Str){(til_I64)"src/core/str.til:374:48:", 24}), &_tmp76);
        if (_status__tmp75 != 0) {
            if (_status__tmp75 == 2) { *_err1 = _err1__tmp75; return 1; }
            if (_status__tmp75 == 3) { *_err2 = _err2__tmp75; return 2; }
        }
        til_Array_delete(&_tmp76);
        til_Str _tmp82;
        til_I64_OverflowError _err0__tmp83;
        til_IndexOutOfBoundsError _err1__tmp83;
        til_AllocError _err2__tmp83;
        til_Array _tmp84;
        til_AllocError _err_alloc__tmp85;
        til_IndexOutOfBoundsError _err_idx__tmp85;
        til_Str _tmp86 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp87 = til_I64_to_str(til_start);
        til_Str _tmp88 = ((til_Str){(til_I64)" is greater than end index ", 27});
        til_Str _tmp89 = til_I64_to_str(til_end);
        int _arr_status__tmp85 = til_Array_new(&_tmp84, &_err_alloc__tmp85, "Str", 4);
        if (_arr_status__tmp85 != 0) {
            *_err2 = _err_alloc__tmp85; return 2;
        }
        _arr_status__tmp85 = til_Array_set(&_err_idx__tmp85, &_tmp84, 0, &_tmp86);
        if (_arr_status__tmp85 != 0) {
            *_err1 = _err_idx__tmp85; return 1;
        }
        _arr_status__tmp85 = til_Array_set(&_err_idx__tmp85, &_tmp84, 1, &_tmp87);
        if (_arr_status__tmp85 != 0) {
            *_err1 = _err_idx__tmp85; return 1;
        }
        _arr_status__tmp85 = til_Array_set(&_err_idx__tmp85, &_tmp84, 2, &_tmp88);
        if (_arr_status__tmp85 != 0) {
            *_err1 = _err_idx__tmp85; return 1;
        }
        _arr_status__tmp85 = til_Array_set(&_err_idx__tmp85, &_tmp84, 3, &_tmp89);
        if (_arr_status__tmp85 != 0) {
            *_err1 = _err_idx__tmp85; return 1;
        }
        int _status__tmp83 = til_format(&_tmp82, &_err0__tmp83, &_err1__tmp83, &_err2__tmp83, ((til_Str){(til_I64)"src/core/str.til:374:48:", 24}), &_tmp84);
        if (_status__tmp83 != 0) {
            if (_status__tmp83 == 2) { *_err1 = _err1__tmp83; return 1; }
            if (_status__tmp83 == 3) { *_err2 = _err2__tmp83; return 2; }
        }
        til_Array_delete(&_tmp84);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp82);
        return 1;
    }
    if (til_gt(til_end, til_Str_len(til_s)).data) {
        til_Str _tmp91;
        til_I64_OverflowError _err0__tmp92;
        til_IndexOutOfBoundsError _err1__tmp92;
        til_AllocError _err2__tmp92;
        til_Array _tmp93;
        til_AllocError _err_alloc__tmp94;
        til_IndexOutOfBoundsError _err_idx__tmp94;
        til_Str _tmp95 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp96 = til_I64_to_str(til_end);
        til_Str _tmp97 = ((til_Str){(til_I64)" is greater than string length ", 31});
        til_Str _tmp98 = til_I64_to_str(til_Str_len(til_s));
        int _arr_status__tmp94 = til_Array_new(&_tmp93, &_err_alloc__tmp94, "Str", 4);
        if (_arr_status__tmp94 != 0) {
            *_err2 = _err_alloc__tmp94; return 2;
        }
        _arr_status__tmp94 = til_Array_set(&_err_idx__tmp94, &_tmp93, 0, &_tmp95);
        if (_arr_status__tmp94 != 0) {
            *_err1 = _err_idx__tmp94; return 1;
        }
        _arr_status__tmp94 = til_Array_set(&_err_idx__tmp94, &_tmp93, 1, &_tmp96);
        if (_arr_status__tmp94 != 0) {
            *_err1 = _err_idx__tmp94; return 1;
        }
        _arr_status__tmp94 = til_Array_set(&_err_idx__tmp94, &_tmp93, 2, &_tmp97);
        if (_arr_status__tmp94 != 0) {
            *_err1 = _err_idx__tmp94; return 1;
        }
        _arr_status__tmp94 = til_Array_set(&_err_idx__tmp94, &_tmp93, 3, &_tmp98);
        if (_arr_status__tmp94 != 0) {
            *_err1 = _err_idx__tmp94; return 1;
        }
        int _status__tmp92 = til_format(&_tmp91, &_err0__tmp92, &_err1__tmp92, &_err2__tmp92, ((til_Str){(til_I64)"src/core/str.til:377:48:", 24}), &_tmp93);
        if (_status__tmp92 != 0) {
            if (_status__tmp92 == 2) { *_err1 = _err1__tmp92; return 1; }
            if (_status__tmp92 == 3) { *_err2 = _err2__tmp92; return 2; }
        }
        til_Array_delete(&_tmp93);
        til_Str _tmp99;
        til_I64_OverflowError _err0__tmp100;
        til_IndexOutOfBoundsError _err1__tmp100;
        til_AllocError _err2__tmp100;
        til_Array _tmp101;
        til_AllocError _err_alloc__tmp102;
        til_IndexOutOfBoundsError _err_idx__tmp102;
        til_Str _tmp103 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp104 = til_I64_to_str(til_end);
        til_Str _tmp105 = ((til_Str){(til_I64)" is greater than string length ", 31});
        til_Str _tmp106 = til_I64_to_str(til_Str_len(til_s));
        int _arr_status__tmp102 = til_Array_new(&_tmp101, &_err_alloc__tmp102, "Str", 4);
        if (_arr_status__tmp102 != 0) {
            *_err2 = _err_alloc__tmp102; return 2;
        }
        _arr_status__tmp102 = til_Array_set(&_err_idx__tmp102, &_tmp101, 0, &_tmp103);
        if (_arr_status__tmp102 != 0) {
            *_err1 = _err_idx__tmp102; return 1;
        }
        _arr_status__tmp102 = til_Array_set(&_err_idx__tmp102, &_tmp101, 1, &_tmp104);
        if (_arr_status__tmp102 != 0) {
            *_err1 = _err_idx__tmp102; return 1;
        }
        _arr_status__tmp102 = til_Array_set(&_err_idx__tmp102, &_tmp101, 2, &_tmp105);
        if (_arr_status__tmp102 != 0) {
            *_err1 = _err_idx__tmp102; return 1;
        }
        _arr_status__tmp102 = til_Array_set(&_err_idx__tmp102, &_tmp101, 3, &_tmp106);
        if (_arr_status__tmp102 != 0) {
            *_err1 = _err_idx__tmp102; return 1;
        }
        int _status__tmp100 = til_format(&_tmp99, &_err0__tmp100, &_err1__tmp100, &_err2__tmp100, ((til_Str){(til_I64)"src/core/str.til:377:48:", 24}), &_tmp101);
        if (_status__tmp100 != 0) {
            if (_status__tmp100 == 2) { *_err1 = _err1__tmp100; return 1; }
            if (_status__tmp100 == 3) { *_err2 = _err2__tmp100; return 2; }
        }
        til_Array_delete(&_tmp101);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp99);
        return 1;
    }
    if (til_I64_eq(til_start, til_end).data) {
        til_Str _tmp108;
        til_I64_OverflowError _err0__tmp109;
        til_IndexOutOfBoundsError _err1__tmp109;
        til_AllocError _err2__tmp109;
        til_Array _tmp110;
        til_AllocError _err_alloc__tmp111;
        til_IndexOutOfBoundsError _err_idx__tmp111;
        til_Str _tmp112 = ((til_Str){(til_I64)"get_substr: start and end are the same (", 40});
        til_Str _tmp113 = til_I64_to_str(til_start);
        til_Str _tmp114 = ((til_Str){(til_I64)"), no substring", 15});
        int _arr_status__tmp111 = til_Array_new(&_tmp110, &_err_alloc__tmp111, "Str", 3);
        if (_arr_status__tmp111 != 0) {
            *_err2 = _err_alloc__tmp111; return 2;
        }
        _arr_status__tmp111 = til_Array_set(&_err_idx__tmp111, &_tmp110, 0, &_tmp112);
        if (_arr_status__tmp111 != 0) {
            *_err1 = _err_idx__tmp111; return 1;
        }
        _arr_status__tmp111 = til_Array_set(&_err_idx__tmp111, &_tmp110, 1, &_tmp113);
        if (_arr_status__tmp111 != 0) {
            *_err1 = _err_idx__tmp111; return 1;
        }
        _arr_status__tmp111 = til_Array_set(&_err_idx__tmp111, &_tmp110, 2, &_tmp114);
        if (_arr_status__tmp111 != 0) {
            *_err1 = _err_idx__tmp111; return 1;
        }
        int _status__tmp109 = til_format(&_tmp108, &_err0__tmp109, &_err1__tmp109, &_err2__tmp109, ((til_Str){(til_I64)"src/core/str.til:380:48:", 24}), &_tmp110);
        if (_status__tmp109 != 0) {
            if (_status__tmp109 == 2) { *_err1 = _err1__tmp109; return 1; }
            if (_status__tmp109 == 3) { *_err2 = _err2__tmp109; return 2; }
        }
        til_Array_delete(&_tmp110);
        til_Str _tmp115;
        til_I64_OverflowError _err0__tmp116;
        til_IndexOutOfBoundsError _err1__tmp116;
        til_AllocError _err2__tmp116;
        til_Array _tmp117;
        til_AllocError _err_alloc__tmp118;
        til_IndexOutOfBoundsError _err_idx__tmp118;
        til_Str _tmp119 = ((til_Str){(til_I64)"get_substr: start and end are the same (", 40});
        til_Str _tmp120 = til_I64_to_str(til_start);
        til_Str _tmp121 = ((til_Str){(til_I64)"), no substring", 15});
        int _arr_status__tmp118 = til_Array_new(&_tmp117, &_err_alloc__tmp118, "Str", 3);
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
        int _status__tmp116 = til_format(&_tmp115, &_err0__tmp116, &_err1__tmp116, &_err2__tmp116, ((til_Str){(til_I64)"src/core/str.til:380:48:", 24}), &_tmp117);
        if (_status__tmp116 != 0) {
            if (_status__tmp116 == 2) { *_err1 = _err1__tmp116; return 1; }
            if (_status__tmp116 == 3) { *_err2 = _err2__tmp116; return 2; }
        }
        til_Array_delete(&_tmp117);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp115);
        return 1;
    }
    til_Str til_substr = {.c_string = 0, .cap = 0};
    til_substr.cap = til_sub(til_end, til_start);
    til_I64 _ret__tmp122;
    til_AllocError _err0__tmp122 = {};
    int _status__tmp122 = til_malloc(&_ret__tmp122, &_err0__tmp122, til_substr.cap);
    if (_status__tmp122 == 1) { *_err2 = _err0__tmp122; return 2; }
    til_substr.c_string = _ret__tmp122;
    if (til_I64_eq(til_NULL, til_substr.c_string).data) {
        til_Str _tmp124;
        til_I64_OverflowError _err0__tmp125;
        til_IndexOutOfBoundsError _err1__tmp125;
        til_AllocError _err2__tmp125;
        til_Array _tmp126;
        til_AllocError _err_alloc__tmp127;
        til_IndexOutOfBoundsError _err_idx__tmp127;
        til_Str _tmp128 = ((til_Str){(til_I64)"Str.get_substr: failed to allocate ", 35});
        til_Str _tmp129 = til_I64_to_str(til_substr.cap);
        til_Str _tmp130 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp127 = til_Array_new(&_tmp126, &_err_alloc__tmp127, "Str", 3);
        if (_arr_status__tmp127 != 0) {
            *_err2 = _err_alloc__tmp127; return 2;
        }
        _arr_status__tmp127 = til_Array_set(&_err_idx__tmp127, &_tmp126, 0, &_tmp128);
        if (_arr_status__tmp127 != 0) {
            *_err1 = _err_idx__tmp127; return 1;
        }
        _arr_status__tmp127 = til_Array_set(&_err_idx__tmp127, &_tmp126, 1, &_tmp129);
        if (_arr_status__tmp127 != 0) {
            *_err1 = _err_idx__tmp127; return 1;
        }
        _arr_status__tmp127 = til_Array_set(&_err_idx__tmp127, &_tmp126, 2, &_tmp130);
        if (_arr_status__tmp127 != 0) {
            *_err1 = _err_idx__tmp127; return 1;
        }
        int _status__tmp125 = til_format(&_tmp124, &_err0__tmp125, &_err1__tmp125, &_err2__tmp125, ((til_Str){(til_I64)"src/core/str.til:387:37:", 24}), &_tmp126);
        if (_status__tmp125 != 0) {
            if (_status__tmp125 == 2) { *_err1 = _err1__tmp125; return 1; }
            if (_status__tmp125 == 3) { *_err2 = _err2__tmp125; return 2; }
        }
        til_Array_delete(&_tmp126);
        til_Str _tmp131;
        til_I64_OverflowError _err0__tmp132;
        til_IndexOutOfBoundsError _err1__tmp132;
        til_AllocError _err2__tmp132;
        til_Array _tmp133;
        til_AllocError _err_alloc__tmp134;
        til_IndexOutOfBoundsError _err_idx__tmp134;
        til_Str _tmp135 = ((til_Str){(til_I64)"Str.get_substr: failed to allocate ", 35});
        til_Str _tmp136 = til_I64_to_str(til_substr.cap);
        til_Str _tmp137 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp134 = til_Array_new(&_tmp133, &_err_alloc__tmp134, "Str", 3);
        if (_arr_status__tmp134 != 0) {
            *_err2 = _err_alloc__tmp134; return 2;
        }
        _arr_status__tmp134 = til_Array_set(&_err_idx__tmp134, &_tmp133, 0, &_tmp135);
        if (_arr_status__tmp134 != 0) {
            *_err1 = _err_idx__tmp134; return 1;
        }
        _arr_status__tmp134 = til_Array_set(&_err_idx__tmp134, &_tmp133, 1, &_tmp136);
        if (_arr_status__tmp134 != 0) {
            *_err1 = _err_idx__tmp134; return 1;
        }
        _arr_status__tmp134 = til_Array_set(&_err_idx__tmp134, &_tmp133, 2, &_tmp137);
        if (_arr_status__tmp134 != 0) {
            *_err1 = _err_idx__tmp134; return 1;
        }
        int _status__tmp132 = til_format(&_tmp131, &_err0__tmp132, &_err1__tmp132, &_err2__tmp132, ((til_Str){(til_I64)"src/core/str.til:387:37:", 24}), &_tmp133);
        if (_status__tmp132 != 0) {
            if (_status__tmp132 == 2) { *_err1 = _err1__tmp132; return 1; }
            if (_status__tmp132 == 3) { *_err2 = _err2__tmp132; return 2; }
        }
        til_Array_delete(&_tmp133);
        *_err2 = til_AllocError_new(_tmp131);
        return 2;
    }
    til_memcpy(til_substr.c_string, til_add(til_s.c_string, til_start), til_substr.cap);
    *_ret = til_substr;
    return 0;
}

til_Str til_concat(const til_Str til_a, const til_Str til_b) {
    til_AllocError _thrown_AllocError__tmp138;
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_add(til_a.cap, til_b.cap);
    if (til_lt(til_result.cap, til_a.cap).data) {
        til_Array _tmp140;
        til_AllocError _err_alloc__tmp141;
        til_IndexOutOfBoundsError _err_idx__tmp141;
        til_Str _tmp142 = ((til_Str){(til_I64)"concat: integer overflow", 24});
        int _arr_status__tmp141 = til_Array_new(&_tmp140, &_err_alloc__tmp141, "Str", 1);
        if (_arr_status__tmp141 != 0) {
        }
        _arr_status__tmp141 = til_Array_set(&_err_idx__tmp141, &_tmp140, 0, &_tmp142);
        if (_arr_status__tmp141 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:427:15:", 24}), &_tmp140);
        til_Array_delete(&_tmp140);
    }
    til_I64 _ret__tmp143;
    til_AllocError _err0__tmp143 = {};
    int _status__tmp143 = til_malloc(&_ret__tmp143, &_err0__tmp143, til_result.cap);
    if (_status__tmp143 == 1) { _thrown_AllocError__tmp138 = _err0__tmp143; goto _catch_AllocError__tmp138; }
    til_result.c_string = _ret__tmp143;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Array _tmp145;
        til_AllocError _err_alloc__tmp146;
        til_IndexOutOfBoundsError _err_idx__tmp146;
        til_Str _tmp147 = ((til_Str){(til_I64)"concat: malloc failed", 21});
        int _arr_status__tmp146 = til_Array_new(&_tmp145, &_err_alloc__tmp146, "Str", 1);
        if (_arr_status__tmp146 != 0) {
        }
        _arr_status__tmp146 = til_Array_set(&_err_idx__tmp146, &_tmp145, 0, &_tmp147);
        if (_arr_status__tmp146 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:432:15:", 24}), &_tmp145);
        til_Array_delete(&_tmp145);
    }
    til_memcpy(til_result.c_string, til_a.c_string, til_a.cap);
    til_memcpy(til_add(til_result.c_string, til_a.cap), til_b.c_string, til_b.cap);
    return til_result;
    goto _end_catches__tmp138;
_catch_AllocError__tmp138: {
    til_AllocError til_err = _thrown_AllocError__tmp138;
    til_Array _tmp149;
    til_AllocError _err_alloc__tmp150;
    til_IndexOutOfBoundsError _err_idx__tmp150;
    til_Str _tmp151 = til_err.msg;
    int _arr_status__tmp150 = til_Array_new(&_tmp149, &_err_alloc__tmp150, "Str", 1);
    if (_arr_status__tmp150 != 0) {
    }
    _arr_status__tmp150 = til_Array_set(&_err_idx__tmp150, &_tmp149, 0, &_tmp151);
    if (_arr_status__tmp150 != 0) {
    }
    til_panic(((til_Str){(til_I64)"src/core/str.til:439:15:", 24}), &_tmp149);
    til_Array_delete(&_tmp149);
    goto _end_catches__tmp138;
    }
_end_catches__tmp138:;
}

int til_format(til_Str* _ret, til_I64_OverflowError* _err1, til_IndexOutOfBoundsError* _err2, til_AllocError* _err3, const til_Str til_prefix, til_Array* til_args) {
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_prefix.cap;
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Str til_arg = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp155 = {};
        int _status__tmp155 = til_Array_get(&_err0__tmp155, (*til_args), til_i, (til_Dynamic*)&til_arg);
        if (_status__tmp155 == 1) { *_err2 = _err0__tmp155; return 2; }
        til_result.cap = til_add(til_result.cap, til_arg.cap);
        if (til_lt(til_result.cap, til_arg.cap).data) {
            til_Str _tmp157;
            til_I64_OverflowError _err0__tmp158;
            til_IndexOutOfBoundsError _err1__tmp158;
            til_AllocError _err2__tmp158;
            til_Array _tmp159;
            til_AllocError _err_alloc__tmp160;
            til_IndexOutOfBoundsError _err_idx__tmp160;
            til_Str _tmp161 = ((til_Str){(til_I64)"format: integer overflow while summing cap for arg ", 51});
            til_Str _tmp162 = til_I64_to_str(til_i);
            int _arr_status__tmp160 = til_Array_new(&_tmp159, &_err_alloc__tmp160, "Str", 2);
            if (_arr_status__tmp160 != 0) {
                *_err3 = _err_alloc__tmp160; return 3;
            }
            _arr_status__tmp160 = til_Array_set(&_err_idx__tmp160, &_tmp159, 0, &_tmp161);
            if (_arr_status__tmp160 != 0) {
                *_err2 = _err_idx__tmp160; return 2;
            }
            _arr_status__tmp160 = til_Array_set(&_err_idx__tmp160, &_tmp159, 1, &_tmp162);
            if (_arr_status__tmp160 != 0) {
                *_err2 = _err_idx__tmp160; return 2;
            }
            int _status__tmp158 = til_format(&_tmp157, &_err0__tmp158, &_err1__tmp158, &_err2__tmp158, ((til_Str){(til_I64)"src/core/str.til:455:48:", 24}), &_tmp159);
            if (_status__tmp158 != 0) {
                if (_status__tmp158 == 1) { *_err1 = _err0__tmp158; return 1; }
                if (_status__tmp158 == 2) { *_err2 = _err1__tmp158; return 2; }
                if (_status__tmp158 == 3) { *_err3 = _err2__tmp158; return 3; }
            }
            til_Array_delete(&_tmp159);
            til_Str _tmp163;
            til_I64_OverflowError _err0__tmp164;
            til_IndexOutOfBoundsError _err1__tmp164;
            til_AllocError _err2__tmp164;
            til_Array _tmp165;
            til_AllocError _err_alloc__tmp166;
            til_IndexOutOfBoundsError _err_idx__tmp166;
            til_Str _tmp167 = ((til_Str){(til_I64)"format: integer overflow while summing cap for arg ", 51});
            til_Str _tmp168 = til_I64_to_str(til_i);
            int _arr_status__tmp166 = til_Array_new(&_tmp165, &_err_alloc__tmp166, "Str", 2);
            if (_arr_status__tmp166 != 0) {
                *_err3 = _err_alloc__tmp166; return 3;
            }
            _arr_status__tmp166 = til_Array_set(&_err_idx__tmp166, &_tmp165, 0, &_tmp167);
            if (_arr_status__tmp166 != 0) {
                *_err2 = _err_idx__tmp166; return 2;
            }
            _arr_status__tmp166 = til_Array_set(&_err_idx__tmp166, &_tmp165, 1, &_tmp168);
            if (_arr_status__tmp166 != 0) {
                *_err2 = _err_idx__tmp166; return 2;
            }
            int _status__tmp164 = til_format(&_tmp163, &_err0__tmp164, &_err1__tmp164, &_err2__tmp164, ((til_Str){(til_I64)"src/core/str.til:455:48:", 24}), &_tmp165);
            if (_status__tmp164 != 0) {
                if (_status__tmp164 == 1) { *_err1 = _err0__tmp164; return 1; }
                if (_status__tmp164 == 2) { *_err2 = _err1__tmp164; return 2; }
                if (_status__tmp164 == 3) { *_err3 = _err2__tmp164; return 3; }
            }
            til_Array_delete(&_tmp165);
            *_err1 = til_I64_OverflowError_new(_tmp163);
            return 1;
        }
        til_I64_inc(&til_i);
    }
    til_I64 _ret__tmp169;
    til_AllocError _err0__tmp169 = {};
    int _status__tmp169 = til_malloc(&_ret__tmp169, &_err0__tmp169, til_result.cap);
    if (_status__tmp169 == 1) { *_err3 = _err0__tmp169; return 3; }
    til_result.c_string = _ret__tmp169;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Str _tmp171;
        til_I64_OverflowError _err0__tmp172;
        til_IndexOutOfBoundsError _err1__tmp172;
        til_AllocError _err2__tmp172;
        til_Array _tmp173;
        til_AllocError _err_alloc__tmp174;
        til_IndexOutOfBoundsError _err_idx__tmp174;
        til_Str _tmp175 = ((til_Str){(til_I64)"format: malloc failed for cap = ", 32});
        til_Str _tmp176 = til_I64_to_str(til_result.cap);
        int _arr_status__tmp174 = til_Array_new(&_tmp173, &_err_alloc__tmp174, "Str", 2);
        if (_arr_status__tmp174 != 0) {
            *_err3 = _err_alloc__tmp174; return 3;
        }
        _arr_status__tmp174 = til_Array_set(&_err_idx__tmp174, &_tmp173, 0, &_tmp175);
        if (_arr_status__tmp174 != 0) {
            *_err2 = _err_idx__tmp174; return 2;
        }
        _arr_status__tmp174 = til_Array_set(&_err_idx__tmp174, &_tmp173, 1, &_tmp176);
        if (_arr_status__tmp174 != 0) {
            *_err2 = _err_idx__tmp174; return 2;
        }
        int _status__tmp172 = til_format(&_tmp171, &_err0__tmp172, &_err1__tmp172, &_err2__tmp172, ((til_Str){(til_I64)"src/core/str.til:461:37:", 24}), &_tmp173);
        if (_status__tmp172 != 0) {
            if (_status__tmp172 == 1) { *_err1 = _err0__tmp172; return 1; }
            if (_status__tmp172 == 2) { *_err2 = _err1__tmp172; return 2; }
            if (_status__tmp172 == 3) { *_err3 = _err2__tmp172; return 3; }
        }
        til_Array_delete(&_tmp173);
        til_Str _tmp177;
        til_I64_OverflowError _err0__tmp178;
        til_IndexOutOfBoundsError _err1__tmp178;
        til_AllocError _err2__tmp178;
        til_Array _tmp179;
        til_AllocError _err_alloc__tmp180;
        til_IndexOutOfBoundsError _err_idx__tmp180;
        til_Str _tmp181 = ((til_Str){(til_I64)"format: malloc failed for cap = ", 32});
        til_Str _tmp182 = til_I64_to_str(til_result.cap);
        int _arr_status__tmp180 = til_Array_new(&_tmp179, &_err_alloc__tmp180, "Str", 2);
        if (_arr_status__tmp180 != 0) {
            *_err3 = _err_alloc__tmp180; return 3;
        }
        _arr_status__tmp180 = til_Array_set(&_err_idx__tmp180, &_tmp179, 0, &_tmp181);
        if (_arr_status__tmp180 != 0) {
            *_err2 = _err_idx__tmp180; return 2;
        }
        _arr_status__tmp180 = til_Array_set(&_err_idx__tmp180, &_tmp179, 1, &_tmp182);
        if (_arr_status__tmp180 != 0) {
            *_err2 = _err_idx__tmp180; return 2;
        }
        int _status__tmp178 = til_format(&_tmp177, &_err0__tmp178, &_err1__tmp178, &_err2__tmp178, ((til_Str){(til_I64)"src/core/str.til:461:37:", 24}), &_tmp179);
        if (_status__tmp178 != 0) {
            if (_status__tmp178 == 1) { *_err1 = _err0__tmp178; return 1; }
            if (_status__tmp178 == 2) { *_err2 = _err1__tmp178; return 2; }
            if (_status__tmp178 == 3) { *_err3 = _err2__tmp178; return 3; }
        }
        til_Array_delete(&_tmp179);
        *_err3 = til_AllocError_new(_tmp177);
        return 3;
    }
    til_I64 til_offset = 0;
    til_memcpy(til_result.c_string, til_prefix.c_string, til_prefix.cap);
    til_offset = til_prefix.cap;
    til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Str til_s = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp185 = {};
        int _status__tmp185 = til_Array_get(&_err0__tmp185, (*til_args), til_i, (til_Dynamic*)&til_s);
        if (_status__tmp185 == 1) { *_err2 = _err0__tmp185; return 2; }
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
        til_Array _tmp189;
        til_AllocError _err_alloc__tmp190;
        til_IndexOutOfBoundsError _err_idx__tmp190;
        til_Str _tmp191 = til_loc_str;
        til_Str _tmp192 = ((til_Str){(til_I64)"assert_eq failed: expected '", 28});
        til_Str _tmp193 = til_I64_to_str(til_a);
        til_Str _tmp194 = ((til_Str){(til_I64)"', found '", 10});
        til_Str _tmp195 = til_I64_to_str(til_b);
        til_Str _tmp196 = ((til_Str){(til_I64)"'", 1});
        int _arr_status__tmp190 = til_Array_new(&_tmp189, &_err_alloc__tmp190, "Str", 6);
        if (_arr_status__tmp190 != 0) {
        }
        _arr_status__tmp190 = til_Array_set(&_err_idx__tmp190, &_tmp189, 0, &_tmp191);
        if (_arr_status__tmp190 != 0) {
        }
        _arr_status__tmp190 = til_Array_set(&_err_idx__tmp190, &_tmp189, 1, &_tmp192);
        if (_arr_status__tmp190 != 0) {
        }
        _arr_status__tmp190 = til_Array_set(&_err_idx__tmp190, &_tmp189, 2, &_tmp193);
        if (_arr_status__tmp190 != 0) {
        }
        _arr_status__tmp190 = til_Array_set(&_err_idx__tmp190, &_tmp189, 3, &_tmp194);
        if (_arr_status__tmp190 != 0) {
        }
        _arr_status__tmp190 = til_Array_set(&_err_idx__tmp190, &_tmp189, 4, &_tmp195);
        if (_arr_status__tmp190 != 0) {
        }
        _arr_status__tmp190 = til_Array_set(&_err_idx__tmp190, &_tmp189, 5, &_tmp196);
        if (_arr_status__tmp190 != 0) {
        }
        til_println(&_tmp189);
        til_Array_delete(&_tmp189);
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
    til_I64 _ret__tmp210;
    til_AllocError _err0__tmp210 = {};
    int _status__tmp210 = til_malloc(&_ret__tmp210, &_err0__tmp210, til_size_bytes);
    if (_status__tmp210 == 1) { *_err1 = _err0__tmp210; return 1; }
    til_arr.ptr = _ret__tmp210;
    til_U8 _tmp211;
    til_U8_OverflowError _err0__tmp212;
    int _status__tmp212 = til_U8_from_i64(&_tmp211, &_err0__tmp212, 0);
    if (_status__tmp212 != 0) {
    }
    til_memset(til_arr.ptr, _tmp211, til_size_bytes);
    til_arr._len = til_capacity;
    *_ret = til_arr;
    return 0;
}

int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array til_self, const til_I64 til_index, til_Dynamic* til_T) {
    if (til_I64_gteq(til_index, til_self._len).data) {
        til_Str _tmp215;
        til_I64_OverflowError _err0__tmp216;
        til_IndexOutOfBoundsError _err1__tmp216;
        til_AllocError _err2__tmp216;
        til_Array _tmp217;
        til_AllocError _err_alloc__tmp218;
        til_IndexOutOfBoundsError _err_idx__tmp218;
        til_Str _tmp219 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        int _arr_status__tmp218 = til_Array_new(&_tmp217, &_err_alloc__tmp218, "Str", 1);
        if (_arr_status__tmp218 != 0) {
        }
        _arr_status__tmp218 = til_Array_set(&_err_idx__tmp218, &_tmp217, 0, &_tmp219);
        if (_arr_status__tmp218 != 0) {
            *_err1 = _err_idx__tmp218; return 1;
        }
        int _status__tmp216 = til_format(&_tmp215, &_err0__tmp216, &_err1__tmp216, &_err2__tmp216, ((til_Str){(til_I64)"src/core/array.til:41:52:", 25}), &_tmp217);
        if (_status__tmp216 != 0) {
            if (_status__tmp216 == 2) { *_err1 = _err1__tmp216; return 1; }
        }
        til_Array_delete(&_tmp217);
        til_Str _tmp220;
        til_I64_OverflowError _err0__tmp221;
        til_IndexOutOfBoundsError _err1__tmp221;
        til_AllocError _err2__tmp221;
        til_Array _tmp222;
        til_AllocError _err_alloc__tmp223;
        til_IndexOutOfBoundsError _err_idx__tmp223;
        til_Str _tmp224 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        int _arr_status__tmp223 = til_Array_new(&_tmp222, &_err_alloc__tmp223, "Str", 1);
        if (_arr_status__tmp223 != 0) {
        }
        _arr_status__tmp223 = til_Array_set(&_err_idx__tmp223, &_tmp222, 0, &_tmp224);
        if (_arr_status__tmp223 != 0) {
            *_err1 = _err_idx__tmp223; return 1;
        }
        int _status__tmp221 = til_format(&_tmp220, &_err0__tmp221, &_err1__tmp221, &_err2__tmp221, ((til_Str){(til_I64)"src/core/array.til:41:52:", 25}), &_tmp222);
        if (_status__tmp221 != 0) {
            if (_status__tmp221 == 2) { *_err1 = _err1__tmp221; return 1; }
        }
        til_Array_delete(&_tmp222);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp220);
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_I64_gteq(til_index, til_self->_len).data) {
        til_Str _tmp227;
        til_I64_OverflowError _err0__tmp228;
        til_IndexOutOfBoundsError _err1__tmp228;
        til_AllocError _err2__tmp228;
        til_Array _tmp229;
        til_AllocError _err_alloc__tmp230;
        til_IndexOutOfBoundsError _err_idx__tmp230;
        til_Str _tmp231 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        int _arr_status__tmp230 = til_Array_new(&_tmp229, &_err_alloc__tmp230, "Str", 1);
        if (_arr_status__tmp230 != 0) {
        }
        _arr_status__tmp230 = til_Array_set(&_err_idx__tmp230, &_tmp229, 0, &_tmp231);
        if (_arr_status__tmp230 != 0) {
            *_err1 = _err_idx__tmp230; return 1;
        }
        int _status__tmp228 = til_format(&_tmp227, &_err0__tmp228, &_err1__tmp228, &_err2__tmp228, ((til_Str){(til_I64)"src/core/array.til:56:52:", 25}), &_tmp229);
        if (_status__tmp228 != 0) {
            if (_status__tmp228 == 2) { *_err1 = _err1__tmp228; return 1; }
        }
        til_Array_delete(&_tmp229);
        til_Str _tmp232;
        til_I64_OverflowError _err0__tmp233;
        til_IndexOutOfBoundsError _err1__tmp233;
        til_AllocError _err2__tmp233;
        til_Array _tmp234;
        til_AllocError _err_alloc__tmp235;
        til_IndexOutOfBoundsError _err_idx__tmp235;
        til_Str _tmp236 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        int _arr_status__tmp235 = til_Array_new(&_tmp234, &_err_alloc__tmp235, "Str", 1);
        if (_arr_status__tmp235 != 0) {
        }
        _arr_status__tmp235 = til_Array_set(&_err_idx__tmp235, &_tmp234, 0, &_tmp236);
        if (_arr_status__tmp235 != 0) {
            *_err1 = _err_idx__tmp235; return 1;
        }
        int _status__tmp233 = til_format(&_tmp232, &_err0__tmp233, &_err1__tmp233, &_err2__tmp233, ((til_Str){(til_I64)"src/core/array.til:56:52:", 25}), &_tmp234);
        if (_status__tmp233 != 0) {
            if (_status__tmp233 == 2) { *_err1 = _err1__tmp233; return 1; }
        }
        til_Array_delete(&_tmp234);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp232);
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
    til_I64 _ret__tmp254;
    til_AllocError _err0__tmp254 = {};
    int _status__tmp254 = til_malloc(&_ret__tmp254, &_err0__tmp254, til_size_bytes);
    if (_status__tmp254 == 1) { *_err1 = _err0__tmp254; return 1; }
    til_vec.ptr = _ret__tmp254;
    til_vec._len = 0;
    til_vec.cap = til_Vec_INIT_CAP;
    *_ret = til_vec;
    return 0;
}

int til_Vec_push(til_AllocError* _err1, til_Vec* til_self, const til_Dynamic til_value) {
    if (til_I64_eq(til_self->_len, til_self->cap).data) {
        const til_I64 til_new_cap = til_mul(til_self->cap, 2);
        if (til_gt(til_new_cap, til_Vec_MAX_CAP).data) {
            til_Array _tmp258;
            til_AllocError _err_alloc__tmp259;
            til_IndexOutOfBoundsError _err_idx__tmp259;
            til_Str _tmp260 = ((til_Str){(til_I64)"Vec.push: capacity exceeded Vec.MAX_CAP", 39});
            int _arr_status__tmp259 = til_Array_new(&_tmp258, &_err_alloc__tmp259, "Str", 1);
            if (_arr_status__tmp259 != 0) {
                *_err1 = _err_alloc__tmp259; return 1;
            }
            _arr_status__tmp259 = til_Array_set(&_err_idx__tmp259, &_tmp258, 0, &_tmp260);
            if (_arr_status__tmp259 != 0) {
            }
            til_panic(((til_Str){(til_I64)"src/core/vec.til:63:23:", 23}), &_tmp258);
            til_Array_delete(&_tmp258);
        }
        til_I64 _ret__tmp261;
        til_I64 til_new_ptr;
        til_AllocError _err0__tmp261 = {};
        int _status__tmp261 = til_malloc(&_ret__tmp261, &_err0__tmp261, til_mul(til_new_cap, til_self->type_size));
        if (_status__tmp261 == 1) { *_err1 = _err0__tmp261; return 1; }
        til_new_ptr = _ret__tmp261;
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
        til_Str _tmp264;
        til_I64_OverflowError _err0__tmp265;
        til_IndexOutOfBoundsError _err1__tmp265;
        til_AllocError _err2__tmp265;
        til_Array _tmp266;
        til_AllocError _err_alloc__tmp267;
        til_IndexOutOfBoundsError _err_idx__tmp267;
        til_Str _tmp268 = ((til_Str){(til_I64)"Vec.get: index out of bounds", 28});
        int _arr_status__tmp267 = til_Array_new(&_tmp266, &_err_alloc__tmp267, "Str", 1);
        if (_arr_status__tmp267 != 0) {
        }
        _arr_status__tmp267 = til_Array_set(&_err_idx__tmp267, &_tmp266, 0, &_tmp268);
        if (_arr_status__tmp267 != 0) {
            *_err1 = _err_idx__tmp267; return 1;
        }
        int _status__tmp265 = til_format(&_tmp264, &_err0__tmp265, &_err1__tmp265, &_err2__tmp265, ((til_Str){(til_I64)"src/core/vec.til:81:52:", 23}), &_tmp266);
        if (_status__tmp265 != 0) {
            if (_status__tmp265 == 2) { *_err1 = _err1__tmp265; return 1; }
        }
        til_Array_delete(&_tmp266);
        til_Str _tmp269;
        til_I64_OverflowError _err0__tmp270;
        til_IndexOutOfBoundsError _err1__tmp270;
        til_AllocError _err2__tmp270;
        til_Array _tmp271;
        til_AllocError _err_alloc__tmp272;
        til_IndexOutOfBoundsError _err_idx__tmp272;
        til_Str _tmp273 = ((til_Str){(til_I64)"Vec.get: index out of bounds", 28});
        int _arr_status__tmp272 = til_Array_new(&_tmp271, &_err_alloc__tmp272, "Str", 1);
        if (_arr_status__tmp272 != 0) {
        }
        _arr_status__tmp272 = til_Array_set(&_err_idx__tmp272, &_tmp271, 0, &_tmp273);
        if (_arr_status__tmp272 != 0) {
            *_err1 = _err_idx__tmp272; return 1;
        }
        int _status__tmp270 = til_format(&_tmp269, &_err0__tmp270, &_err1__tmp270, &_err2__tmp270, ((til_Str){(til_I64)"src/core/vec.til:81:52:", 23}), &_tmp271);
        if (_status__tmp270 != 0) {
            if (_status__tmp270 == 2) { *_err1 = _err1__tmp270; return 1; }
        }
        til_Array_delete(&_tmp271);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp269);
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
    til_I64 _ret__tmp281;
    til_AllocError _err0__tmp281 = {};
    int _status__tmp281 = til_malloc(&_ret__tmp281, &_err0__tmp281, til_cloned.cap);
    if (_status__tmp281 == 1) { *_err1 = _err0__tmp281; return 1; }
    til_cloned.c_string = _ret__tmp281;
    if (til_I64_eq(til_NULL, til_cloned.c_string).data) {
        til_Str _tmp283;
        til_I64_OverflowError _err0__tmp284;
        til_IndexOutOfBoundsError _err1__tmp284;
        til_AllocError _err2__tmp284;
        til_Array _tmp285;
        til_AllocError _err_alloc__tmp286;
        til_IndexOutOfBoundsError _err_idx__tmp286;
        til_Str _tmp287 = ((til_Str){(til_I64)"Str.clone: malloc failed for ", 29});
        til_Str _tmp288 = til_I64_to_str(til_cloned.cap);
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
        int _status__tmp284 = til_format(&_tmp283, &_err0__tmp284, &_err1__tmp284, &_err2__tmp284, ((til_Str){(til_I64)"src/core/str.til:46:41:", 23}), &_tmp285);
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
        til_Str _tmp294 = ((til_Str){(til_I64)"Str.clone: malloc failed for ", 29});
        til_Str _tmp295 = til_I64_to_str(til_cloned.cap);
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
        int _status__tmp291 = til_format(&_tmp290, &_err0__tmp291, &_err1__tmp291, &_err2__tmp291, ((til_Str){(til_I64)"src/core/str.til:46:41:", 23}), &_tmp292);
        if (_status__tmp291 != 0) {
            if (_status__tmp291 == 3) { *_err1 = _err2__tmp291; return 1; }
        }
        til_Array_delete(&_tmp292);
        *_err1 = til_AllocError_new(_tmp290);
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
    while (til_I64_lteq(til_start_idx, til_max_start).data) {
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
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp315;
    if (til_I64_eq(til_Str_len(til_from), 0).data) {
        til_Str _ret__tmp317;
        til_AllocError _err0__tmp317 = {};
        int _status__tmp317 = til_Str_clone(&_ret__tmp317, &_err0__tmp317, til_self);
        if (_status__tmp317 == 1) { *_err1 = _err0__tmp317; return 1; }
        *_ret = _ret__tmp317;
        return 0;
    }
    if (til_I64_eq(til_n, 0).data) {
        til_Str _ret__tmp319;
        til_AllocError _err0__tmp319 = {};
        int _status__tmp319 = til_Str_clone(&_ret__tmp319, &_err0__tmp319, til_self);
        if (_status__tmp319 == 1) { *_err1 = _err0__tmp319; return 1; }
        *_ret = _ret__tmp319;
        return 0;
    }
    til_I64 til_idx = til_Str_find(til_self, til_from);
    if (til_lt(til_idx, 0).data) {
        til_Str _ret__tmp321;
        til_AllocError _err0__tmp321 = {};
        int _status__tmp321 = til_Str_clone(&_ret__tmp321, &_err0__tmp321, til_self);
        if (_status__tmp321 == 1) { *_err1 = _err0__tmp321; return 1; }
        *_ret = _ret__tmp321;
        return 0;
    }
    til_Str _ret__tmp322;
    til_Str til_prefix;
    til_IndexOutOfBoundsError _err0__tmp322 = {};
    til_AllocError _err1__tmp322 = {};
    int _status__tmp322 = til_get_substr(&_ret__tmp322, &_err0__tmp322, &_err1__tmp322, til_self, 0, til_idx);
    if (_status__tmp322 == 2) { *_err1 = _err1__tmp322; return 1; }
    til_prefix = _ret__tmp322;
    til_Str _ret__tmp323;
    til_Str til_suffix;
    til_IndexOutOfBoundsError _err0__tmp323 = {};
    til_AllocError _err1__tmp323 = {};
    int _status__tmp323 = til_get_substr(&_ret__tmp323, &_err0__tmp323, &_err1__tmp323, til_self, til_add(til_idx, til_Str_len(til_from)), til_Str_len(til_self));
    if (_status__tmp323 == 2) { *_err1 = _err1__tmp323; return 1; }
    til_suffix = _ret__tmp323;
    til_Str til_result = til_concat(til_concat(til_prefix, til_to), til_suffix);
    if (til_gt(til_n, 1).data) {
        til_Str _ret__tmp325;
        til_Str til_rest;
        til_AllocError _err0__tmp325 = {};
        int _status__tmp325 = til_Str_replacen(&_ret__tmp325, &_err0__tmp325, til_suffix, til_from, til_to, til_sub(til_n, 1));
        if (_status__tmp325 == 1) { *_err1 = _err0__tmp325; return 1; }
        til_rest = _ret__tmp325;
        til_result = til_concat(til_concat(til_prefix, til_to), til_rest);
    }
    *_ret = til_result;
    return 0;
    goto _end_catches__tmp315;
_catch_IndexOutOfBoundsError__tmp315: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp315;
    til_Str _ret__tmp327;
    til_AllocError _err0__tmp327 = {};
    int _status__tmp327 = til_Str_clone(&_ret__tmp327, &_err0__tmp327, til_self);
    if (_status__tmp327 == 1) { *_err1 = _err0__tmp327; return 1; }
    til_result = _ret__tmp327;
    goto _end_catches__tmp315;
    }
_end_catches__tmp315:;
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
        til_Str _tmp333;
        til_I64_OverflowError _err0__tmp334;
        til_IndexOutOfBoundsError _err1__tmp334;
        til_AllocError _err2__tmp334;
        til_Array _tmp335;
        til_AllocError _err_alloc__tmp336;
        til_IndexOutOfBoundsError _err_idx__tmp336;
        til_Str _tmp337 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        int _arr_status__tmp336 = til_Array_new(&_tmp335, &_err_alloc__tmp336, "Str", 1);
        if (_arr_status__tmp336 != 0) {
        }
        _arr_status__tmp336 = til_Array_set(&_err_idx__tmp336, &_tmp335, 0, &_tmp337);
        if (_arr_status__tmp336 != 0) {
        }
        int _status__tmp334 = til_format(&_tmp333, &_err0__tmp334, &_err1__tmp334, &_err2__tmp334, ((til_Str){(til_I64)"src/core/u8.til:56:47:", 22}), &_tmp335);
        if (_status__tmp334 != 0) {
        }
        til_Array_delete(&_tmp335);
        til_Str _tmp338;
        til_I64_OverflowError _err0__tmp339;
        til_IndexOutOfBoundsError _err1__tmp339;
        til_AllocError _err2__tmp339;
        til_Array _tmp340;
        til_AllocError _err_alloc__tmp341;
        til_IndexOutOfBoundsError _err_idx__tmp341;
        til_Str _tmp342 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        int _arr_status__tmp341 = til_Array_new(&_tmp340, &_err_alloc__tmp341, "Str", 1);
        if (_arr_status__tmp341 != 0) {
        }
        _arr_status__tmp341 = til_Array_set(&_err_idx__tmp341, &_tmp340, 0, &_tmp342);
        if (_arr_status__tmp341 != 0) {
        }
        int _status__tmp339 = til_format(&_tmp338, &_err0__tmp339, &_err1__tmp339, &_err2__tmp339, ((til_Str){(til_I64)"src/core/u8.til:56:47:", 22}), &_tmp340);
        if (_status__tmp339 != 0) {
        }
        til_Array_delete(&_tmp340);
        *_err1 = til_U8_OverflowError_new(_tmp338);
        return 1;
    }
    if (til_gt(til_self, til_MAX_U8).data) {
        til_Str _tmp344;
        til_I64_OverflowError _err0__tmp345;
        til_IndexOutOfBoundsError _err1__tmp345;
        til_AllocError _err2__tmp345;
        til_Array _tmp346;
        til_AllocError _err_alloc__tmp347;
        til_IndexOutOfBoundsError _err_idx__tmp347;
        til_Str _tmp348 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp349 = ((til_Str){(til_I64)"255", 3});
        int _arr_status__tmp347 = til_Array_new(&_tmp346, &_err_alloc__tmp347, "Str", 2);
        if (_arr_status__tmp347 != 0) {
        }
        _arr_status__tmp347 = til_Array_set(&_err_idx__tmp347, &_tmp346, 0, &_tmp348);
        if (_arr_status__tmp347 != 0) {
        }
        _arr_status__tmp347 = til_Array_set(&_err_idx__tmp347, &_tmp346, 1, &_tmp349);
        if (_arr_status__tmp347 != 0) {
        }
        int _status__tmp345 = til_format(&_tmp344, &_err0__tmp345, &_err1__tmp345, &_err2__tmp345, ((til_Str){(til_I64)"src/core/u8.til:59:47:", 22}), &_tmp346);
        if (_status__tmp345 != 0) {
        }
        til_Array_delete(&_tmp346);
        til_Str _tmp350;
        til_I64_OverflowError _err0__tmp351;
        til_IndexOutOfBoundsError _err1__tmp351;
        til_AllocError _err2__tmp351;
        til_Array _tmp352;
        til_AllocError _err_alloc__tmp353;
        til_IndexOutOfBoundsError _err_idx__tmp353;
        til_Str _tmp354 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp355 = ((til_Str){(til_I64)"255", 3});
        int _arr_status__tmp353 = til_Array_new(&_tmp352, &_err_alloc__tmp353, "Str", 2);
        if (_arr_status__tmp353 != 0) {
        }
        _arr_status__tmp353 = til_Array_set(&_err_idx__tmp353, &_tmp352, 0, &_tmp354);
        if (_arr_status__tmp353 != 0) {
        }
        _arr_status__tmp353 = til_Array_set(&_err_idx__tmp353, &_tmp352, 1, &_tmp355);
        if (_arr_status__tmp353 != 0) {
        }
        int _status__tmp351 = til_format(&_tmp350, &_err0__tmp351, &_err1__tmp351, &_err2__tmp351, ((til_Str){(til_I64)"src/core/u8.til:59:47:", 22}), &_tmp352);
        if (_status__tmp351 != 0) {
        }
        til_Array_delete(&_tmp352);
        *_err1 = til_U8_OverflowError_new(_tmp350);
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
