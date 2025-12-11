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
    til_panic(((til_Str){(til_I64)"src/examples/hello_script.til:69:15:", 36}), &_tmp8);
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
    til_panic(((til_Str){(til_I64)"src/examples/hello_script.til:85:15:", 36}), &_tmp17);
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
    til_panic(((til_Str){(til_I64)"src/examples/hello_script.til:17:15:", 36}), &_tmp55);
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
    til_panic(((til_Str){(til_I64)"src/examples/hello_script.til:31:15:", 36}), &_tmp63);
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
        int _status__tmp69 = til_format(&_tmp68, &_err0__tmp69, &_err1__tmp69, &_err2__tmp69, ((til_Str){(til_I64)"src/examples/hello_script.til:357:48:", 37}), &_tmp70);
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
        int _status__tmp76 = til_format(&_tmp75, &_err0__tmp76, &_err1__tmp76, &_err2__tmp76, ((til_Str){(til_I64)"src/examples/hello_script.til:357:48:", 37}), &_tmp77);
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
        int _status__tmp84 = til_format(&_tmp83, &_err0__tmp84, &_err1__tmp84, &_err2__tmp84, ((til_Str){(til_I64)"src/examples/hello_script.til:360:48:", 37}), &_tmp85);
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
        int _status__tmp91 = til_format(&_tmp90, &_err0__tmp91, &_err1__tmp91, &_err2__tmp91, ((til_Str){(til_I64)"src/examples/hello_script.til:360:48:", 37}), &_tmp92);
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
        int _status__tmp99 = til_format(&_tmp98, &_err0__tmp99, &_err1__tmp99, &_err2__tmp99, ((til_Str){(til_I64)"src/examples/hello_script.til:363:48:", 37}), &_tmp100);
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
        int _status__tmp107 = til_format(&_tmp106, &_err0__tmp107, &_err1__tmp107, &_err2__tmp107, ((til_Str){(til_I64)"src/examples/hello_script.til:363:48:", 37}), &_tmp108);
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
        int _status__tmp116 = til_format(&_tmp115, &_err0__tmp116, &_err1__tmp116, &_err2__tmp116, ((til_Str){(til_I64)"src/examples/hello_script.til:366:48:", 37}), &_tmp117);
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
        int _status__tmp124 = til_format(&_tmp123, &_err0__tmp124, &_err1__tmp124, &_err2__tmp124, ((til_Str){(til_I64)"src/examples/hello_script.til:366:48:", 37}), &_tmp125);
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
        int _status__tmp133 = til_format(&_tmp132, &_err0__tmp133, &_err1__tmp133, &_err2__tmp133, ((til_Str){(til_I64)"src/examples/hello_script.til:369:48:", 37}), &_tmp134);
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
        int _status__tmp140 = til_format(&_tmp139, &_err0__tmp140, &_err1__tmp140, &_err2__tmp140, ((til_Str){(til_I64)"src/examples/hello_script.til:369:48:", 37}), &_tmp141);
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
        int _status__tmp149 = til_format(&_tmp148, &_err0__tmp149, &_err1__tmp149, &_err2__tmp149, ((til_Str){(til_I64)"src/examples/hello_script.til:376:37:", 37}), &_tmp150);
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
        int _status__tmp156 = til_format(&_tmp155, &_err0__tmp156, &_err1__tmp156, &_err2__tmp156, ((til_Str){(til_I64)"src/examples/hello_script.til:376:37:", 37}), &_tmp157);
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
        til_panic(((til_Str){(til_I64)"src/examples/hello_script.til:416:15:", 37}), &_tmp170);
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
        til_panic(((til_Str){(til_I64)"src/examples/hello_script.til:428:15:", 37}), &_tmp175);
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
        til_panic(((til_Str){(til_I64)"src/examples/hello_script.til:421:15:", 37}), &_tmp179);
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
    til_panic(((til_Str){(til_I64)"src/examples/hello_script.til:428:15:", 37}), &_tmp183);
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
            int _status__tmp192 = til_format(&_tmp191, &_err0__tmp192, &_err1__tmp192, &_err2__tmp192, ((til_Str){(til_I64)"src/examples/hello_script.til:444:48:", 37}), &_tmp193);
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
            int _status__tmp198 = til_format(&_tmp197, &_err0__tmp198, &_err1__tmp198, &_err2__tmp198, ((til_Str){(til_I64)"src/examples/hello_script.til:444:48:", 37}), &_tmp199);
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
        int _status__tmp206 = til_format(&_tmp205, &_err0__tmp206, &_err1__tmp206, &_err2__tmp206, ((til_Str){(til_I64)"src/examples/hello_script.til:450:37:", 37}), &_tmp207);
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
        int _status__tmp212 = til_format(&_tmp211, &_err0__tmp212, &_err1__tmp212, &_err2__tmp212, ((til_Str){(til_I64)"src/examples/hello_script.til:450:37:", 37}), &_tmp213);
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
    til_I64 _ret__tmp225;
    til_AllocError _err0__tmp225 = {};
    int _status__tmp225 = til_malloc(&_ret__tmp225, &_err0__tmp225, til_size_bytes);
    if (_status__tmp225 == 1) { *_err1 = _err0__tmp225; return 1; }
    til_arr.ptr = _ret__tmp225;
    til_U8 _tmp226;
    til_U8_OverflowError _err0__tmp227;
    int _status__tmp227 = til_U8_from_i64(&_tmp226, &_err0__tmp227, 0);
    if (_status__tmp227 != 0) {
    }
    til_memset(til_arr.ptr, _tmp226, til_size_bytes);
    til_arr._len = til_capacity;
    *_ret = til_arr;
    return 0;
}

int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array til_self, const til_I64 til_index, til_Dynamic* til_T) {
    if (til_gteq(til_index, til_self._len).data) {
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
        int _status__tmp231 = til_format(&_tmp230, &_err0__tmp231, &_err1__tmp231, &_err2__tmp231, ((til_Str){(til_I64)"src/examples/hello_script.til:41:52:", 36}), &_tmp232);
        if (_status__tmp231 != 0) {
            if (_status__tmp231 == 2) { *_err1 = _err1__tmp231; return 1; }
        }
        til_Array_delete(&_tmp232);
        til_Str _tmp235;
        til_I64_OverflowError _err0__tmp236;
        til_IndexOutOfBoundsError _err1__tmp236;
        til_AllocError _err2__tmp236;
        til_Array _tmp237;
        til_AllocError _err_alloc__tmp238;
        til_IndexOutOfBoundsError _err_idx__tmp238;
        til_Str _tmp239 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        int _arr_status__tmp238 = til_Array_new(&_tmp237, &_err_alloc__tmp238, "Str", 1);
        if (_arr_status__tmp238 != 0) {
        }
        _arr_status__tmp238 = til_Array_set(&_err_idx__tmp238, &_tmp237, 0, &_tmp239);
        if (_arr_status__tmp238 != 0) {
            *_err1 = _err_idx__tmp238; return 1;
        }
        int _status__tmp236 = til_format(&_tmp235, &_err0__tmp236, &_err1__tmp236, &_err2__tmp236, ((til_Str){(til_I64)"src/examples/hello_script.til:41:52:", 36}), &_tmp237);
        if (_status__tmp236 != 0) {
            if (_status__tmp236 == 2) { *_err1 = _err1__tmp236; return 1; }
        }
        til_Array_delete(&_tmp237);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp235);
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_gteq(til_index, til_self->_len).data) {
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
        int _status__tmp243 = til_format(&_tmp242, &_err0__tmp243, &_err1__tmp243, &_err2__tmp243, ((til_Str){(til_I64)"src/examples/hello_script.til:56:52:", 36}), &_tmp244);
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
        til_Str _tmp251 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        int _arr_status__tmp250 = til_Array_new(&_tmp249, &_err_alloc__tmp250, "Str", 1);
        if (_arr_status__tmp250 != 0) {
        }
        _arr_status__tmp250 = til_Array_set(&_err_idx__tmp250, &_tmp249, 0, &_tmp251);
        if (_arr_status__tmp250 != 0) {
            *_err1 = _err_idx__tmp250; return 1;
        }
        int _status__tmp248 = til_format(&_tmp247, &_err0__tmp248, &_err1__tmp248, &_err2__tmp248, ((til_Str){(til_I64)"src/examples/hello_script.til:56:52:", 36}), &_tmp249);
        if (_status__tmp248 != 0) {
            if (_status__tmp248 == 2) { *_err1 = _err1__tmp248; return 1; }
        }
        til_Array_delete(&_tmp249);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp247);
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
    til_I64 _ret__tmp254;
    til_AllocError _err0__tmp254 = {};
    int _status__tmp254 = til_malloc(&_ret__tmp254, &_err0__tmp254, til_total_bytes);
    if (_status__tmp254 == 1) { *_err1 = _err0__tmp254; return 1; }
    til_cloned.ptr = _ret__tmp254;
    if (til_I64_eq(til_NULL, til_cloned.ptr).data) {
        til_Str _tmp256;
        til_I64_OverflowError _err0__tmp257;
        til_IndexOutOfBoundsError _err1__tmp257;
        til_AllocError _err2__tmp257;
        til_Array _tmp258;
        til_AllocError _err_alloc__tmp259;
        til_IndexOutOfBoundsError _err_idx__tmp259;
        til_Str _tmp260 = ((til_Str){(til_I64)"Array.clone: malloc failed for ", 31});
        til_Str _tmp261 = til_I64_to_str(til_total_bytes);
        til_Str _tmp262 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp259 = til_Array_new(&_tmp258, &_err_alloc__tmp259, "Str", 3);
        if (_arr_status__tmp259 != 0) {
            *_err1 = _err_alloc__tmp259; return 1;
        }
        _arr_status__tmp259 = til_Array_set(&_err_idx__tmp259, &_tmp258, 0, &_tmp260);
        if (_arr_status__tmp259 != 0) {
        }
        _arr_status__tmp259 = til_Array_set(&_err_idx__tmp259, &_tmp258, 1, &_tmp261);
        if (_arr_status__tmp259 != 0) {
        }
        _arr_status__tmp259 = til_Array_set(&_err_idx__tmp259, &_tmp258, 2, &_tmp262);
        if (_arr_status__tmp259 != 0) {
        }
        int _status__tmp257 = til_format(&_tmp256, &_err0__tmp257, &_err1__tmp257, &_err2__tmp257, ((til_Str){(til_I64)"src/examples/hello_script.til:83:41:", 36}), &_tmp258);
        if (_status__tmp257 != 0) {
            if (_status__tmp257 == 3) { *_err1 = _err2__tmp257; return 1; }
        }
        til_Array_delete(&_tmp258);
        til_Str _tmp263;
        til_I64_OverflowError _err0__tmp264;
        til_IndexOutOfBoundsError _err1__tmp264;
        til_AllocError _err2__tmp264;
        til_Array _tmp265;
        til_AllocError _err_alloc__tmp266;
        til_IndexOutOfBoundsError _err_idx__tmp266;
        til_Str _tmp267 = ((til_Str){(til_I64)"Array.clone: malloc failed for ", 31});
        til_Str _tmp268 = til_I64_to_str(til_total_bytes);
        til_Str _tmp269 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp266 = til_Array_new(&_tmp265, &_err_alloc__tmp266, "Str", 3);
        if (_arr_status__tmp266 != 0) {
            *_err1 = _err_alloc__tmp266; return 1;
        }
        _arr_status__tmp266 = til_Array_set(&_err_idx__tmp266, &_tmp265, 0, &_tmp267);
        if (_arr_status__tmp266 != 0) {
        }
        _arr_status__tmp266 = til_Array_set(&_err_idx__tmp266, &_tmp265, 1, &_tmp268);
        if (_arr_status__tmp266 != 0) {
        }
        _arr_status__tmp266 = til_Array_set(&_err_idx__tmp266, &_tmp265, 2, &_tmp269);
        if (_arr_status__tmp266 != 0) {
        }
        int _status__tmp264 = til_format(&_tmp263, &_err0__tmp264, &_err1__tmp264, &_err2__tmp264, ((til_Str){(til_I64)"src/examples/hello_script.til:83:41:", 36}), &_tmp265);
        if (_status__tmp264 != 0) {
            if (_status__tmp264 == 3) { *_err1 = _err2__tmp264; return 1; }
        }
        til_Array_delete(&_tmp265);
        *_err1 = til_AllocError_new(_tmp263);
        return 1;
    }
    til_memcpy(til_cloned.ptr, til_self.ptr, til_total_bytes);
    *_ret = til_cloned;
    return 0;
}

til_Bool til_Array_contains(const til_Array til_self, const til_Str til_value) {
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp270;
    til_I64 til_i = 0;
    while (til_lt(til_i, til_self._len).data) {
        til_Str til_elem = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp272 = {};
        int _status__tmp272 = til_Array_get(&_err0__tmp272, til_self, til_i, (til_Dynamic*)&til_elem);
        if (_status__tmp272 == 1) { _thrown_IndexOutOfBoundsError__tmp270 = _err0__tmp272; goto _catch_IndexOutOfBoundsError__tmp270; }
        if (til_Str_eq(til_elem, til_value).data) {
            return true;
        }
        til_i = til_add(til_i, 1);
    }
    return false;
    goto _end_catches__tmp270;
_catch_IndexOutOfBoundsError__tmp270: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp270;
    }
_end_catches__tmp270:;
}

til_I64 til_Bool_len(const til_Bool til_self) {
    return 1;
}

til_Bool til_Bool_eq(const til_Bool til_a, const til_Bool til_b) {
    til_Bool _tmp277;
    til_Array _tmp278;
    til_AllocError _err_alloc__tmp279;
    til_IndexOutOfBoundsError _err_idx__tmp279;
    til_Bool _tmp280 = til_a;
    til_Bool _tmp281 = til_b;
    int _arr_status__tmp279 = til_Array_new(&_tmp278, &_err_alloc__tmp279, "Bool", 2);
    if (_arr_status__tmp279 != 0) {
    }
    _arr_status__tmp279 = til_Array_set(&_err_idx__tmp279, &_tmp278, 0, &_tmp280);
    if (_arr_status__tmp279 != 0) {
    }
    _arr_status__tmp279 = til_Array_set(&_err_idx__tmp279, &_tmp278, 1, &_tmp281);
    if (_arr_status__tmp279 != 0) {
    }
    _tmp277 = til_and(&_tmp278);
    til_Array_delete(&_tmp278);
    til_Bool _tmp282;
    til_Array _tmp283;
    til_AllocError _err_alloc__tmp284;
    til_IndexOutOfBoundsError _err_idx__tmp284;
    til_Bool _tmp285 = til_not(til_b);
    til_Bool _tmp286 = til_not(til_a);
    int _arr_status__tmp284 = til_Array_new(&_tmp283, &_err_alloc__tmp284, "Bool", 2);
    if (_arr_status__tmp284 != 0) {
    }
    _arr_status__tmp284 = til_Array_set(&_err_idx__tmp284, &_tmp283, 0, &_tmp285);
    if (_arr_status__tmp284 != 0) {
    }
    _arr_status__tmp284 = til_Array_set(&_err_idx__tmp284, &_tmp283, 1, &_tmp286);
    if (_arr_status__tmp284 != 0) {
    }
    _tmp282 = til_and(&_tmp283);
    til_Array_delete(&_tmp283);
    til_Array _tmp287;
    til_AllocError _err_alloc__tmp288;
    til_IndexOutOfBoundsError _err_idx__tmp288;
    int _arr_status__tmp288 = til_Array_new(&_tmp287, &_err_alloc__tmp288, "Bool", 2);
    if (_arr_status__tmp288 != 0) {
    }
    _arr_status__tmp288 = til_Array_set(&_err_idx__tmp288, &_tmp287, 0, &_tmp277);
    if (_arr_status__tmp288 != 0) {
    }
    _arr_status__tmp288 = til_Array_set(&_err_idx__tmp288, &_tmp287, 1, &_tmp282);
    if (_arr_status__tmp288 != 0) {
    }
    til_Bool _tmp289 = til_or(&_tmp287);
    til_Array_delete(&_tmp287);
    return _tmp289;
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
    til_I64 _ret__tmp313;
    til_AllocError _err0__tmp313 = {};
    int _status__tmp313 = til_malloc(&_ret__tmp313, &_err0__tmp313, til_size_bytes);
    if (_status__tmp313 == 1) { *_err1 = _err0__tmp313; return 1; }
    til_vec.ptr = _ret__tmp313;
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
    til_I64 _ret__tmp315;
    til_AllocError _err0__tmp315 = {};
    int _status__tmp315 = til_malloc(&_ret__tmp315, &_err0__tmp315, til_size_bytes);
    if (_status__tmp315 == 1) { *_err1 = _err0__tmp315; return 1; }
    til_vec.ptr = _ret__tmp315;
    til_vec._len = 0;
    til_vec.cap = til_Vec_INIT_CAP;
    *_ret = til_vec;
    return 0;
}

int til_Vec_push(til_AllocError* _err1, til_Vec* til_self, const til_Dynamic til_value) {
    if (til_I64_eq(til_self->_len, til_self->cap).data) {
        const til_I64 til_new_cap = til_mul(til_self->cap, 2);
        if (til_gt(til_new_cap, til_Vec_MAX_CAP).data) {
            til_Array _tmp319;
            til_AllocError _err_alloc__tmp320;
            til_IndexOutOfBoundsError _err_idx__tmp320;
            til_Str _tmp321 = ((til_Str){(til_I64)"Vec.push: capacity exceeded Vec.MAX_CAP", 39});
            int _arr_status__tmp320 = til_Array_new(&_tmp319, &_err_alloc__tmp320, "Str", 1);
            if (_arr_status__tmp320 != 0) {
                *_err1 = _err_alloc__tmp320; return 1;
            }
            _arr_status__tmp320 = til_Array_set(&_err_idx__tmp320, &_tmp319, 0, &_tmp321);
            if (_arr_status__tmp320 != 0) {
            }
            til_panic(((til_Str){(til_I64)"src/examples/hello_script.til:63:23:", 36}), &_tmp319);
            til_Array_delete(&_tmp319);
        }
        til_I64 _ret__tmp322;
        til_I64 til_new_ptr;
        til_AllocError _err0__tmp322 = {};
        int _status__tmp322 = til_malloc(&_ret__tmp322, &_err0__tmp322, til_mul(til_new_cap, til_self->type_size));
        if (_status__tmp322 == 1) { *_err1 = _err0__tmp322; return 1; }
        til_new_ptr = _ret__tmp322;
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
        til_Str _tmp325;
        til_I64_OverflowError _err0__tmp326;
        til_IndexOutOfBoundsError _err1__tmp326;
        til_AllocError _err2__tmp326;
        til_Array _tmp327;
        til_AllocError _err_alloc__tmp328;
        til_IndexOutOfBoundsError _err_idx__tmp328;
        til_Str _tmp329 = ((til_Str){(til_I64)"Vec.get: index out of bounds", 28});
        int _arr_status__tmp328 = til_Array_new(&_tmp327, &_err_alloc__tmp328, "Str", 1);
        if (_arr_status__tmp328 != 0) {
        }
        _arr_status__tmp328 = til_Array_set(&_err_idx__tmp328, &_tmp327, 0, &_tmp329);
        if (_arr_status__tmp328 != 0) {
            *_err1 = _err_idx__tmp328; return 1;
        }
        int _status__tmp326 = til_format(&_tmp325, &_err0__tmp326, &_err1__tmp326, &_err2__tmp326, ((til_Str){(til_I64)"src/examples/hello_script.til:81:52:", 36}), &_tmp327);
        if (_status__tmp326 != 0) {
            if (_status__tmp326 == 2) { *_err1 = _err1__tmp326; return 1; }
        }
        til_Array_delete(&_tmp327);
        til_Str _tmp330;
        til_I64_OverflowError _err0__tmp331;
        til_IndexOutOfBoundsError _err1__tmp331;
        til_AllocError _err2__tmp331;
        til_Array _tmp332;
        til_AllocError _err_alloc__tmp333;
        til_IndexOutOfBoundsError _err_idx__tmp333;
        til_Str _tmp334 = ((til_Str){(til_I64)"Vec.get: index out of bounds", 28});
        int _arr_status__tmp333 = til_Array_new(&_tmp332, &_err_alloc__tmp333, "Str", 1);
        if (_arr_status__tmp333 != 0) {
        }
        _arr_status__tmp333 = til_Array_set(&_err_idx__tmp333, &_tmp332, 0, &_tmp334);
        if (_arr_status__tmp333 != 0) {
            *_err1 = _err_idx__tmp333; return 1;
        }
        int _status__tmp331 = til_format(&_tmp330, &_err0__tmp331, &_err1__tmp331, &_err2__tmp331, ((til_Str){(til_I64)"src/examples/hello_script.til:81:52:", 36}), &_tmp332);
        if (_status__tmp331 != 0) {
            if (_status__tmp331 == 2) { *_err1 = _err1__tmp331; return 1; }
        }
        til_Array_delete(&_tmp332);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp330);
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Vec_set(til_IndexOutOfBoundsError* _err1, til_Vec* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_gteq(til_index, til_self->_len).data) {
        til_Str _tmp337;
        til_I64_OverflowError _err0__tmp338;
        til_IndexOutOfBoundsError _err1__tmp338;
        til_AllocError _err2__tmp338;
        til_Array _tmp339;
        til_AllocError _err_alloc__tmp340;
        til_IndexOutOfBoundsError _err_idx__tmp340;
        til_Str _tmp341 = ((til_Str){(til_I64)"Vec.set: index out of bounds", 28});
        int _arr_status__tmp340 = til_Array_new(&_tmp339, &_err_alloc__tmp340, "Str", 1);
        if (_arr_status__tmp340 != 0) {
        }
        _arr_status__tmp340 = til_Array_set(&_err_idx__tmp340, &_tmp339, 0, &_tmp341);
        if (_arr_status__tmp340 != 0) {
            *_err1 = _err_idx__tmp340; return 1;
        }
        int _status__tmp338 = til_format(&_tmp337, &_err0__tmp338, &_err1__tmp338, &_err2__tmp338, ((til_Str){(til_I64)"src/examples/hello_script.til:96:52:", 36}), &_tmp339);
        if (_status__tmp338 != 0) {
            if (_status__tmp338 == 2) { *_err1 = _err1__tmp338; return 1; }
        }
        til_Array_delete(&_tmp339);
        til_Str _tmp342;
        til_I64_OverflowError _err0__tmp343;
        til_IndexOutOfBoundsError _err1__tmp343;
        til_AllocError _err2__tmp343;
        til_Array _tmp344;
        til_AllocError _err_alloc__tmp345;
        til_IndexOutOfBoundsError _err_idx__tmp345;
        til_Str _tmp346 = ((til_Str){(til_I64)"Vec.set: index out of bounds", 28});
        int _arr_status__tmp345 = til_Array_new(&_tmp344, &_err_alloc__tmp345, "Str", 1);
        if (_arr_status__tmp345 != 0) {
        }
        _arr_status__tmp345 = til_Array_set(&_err_idx__tmp345, &_tmp344, 0, &_tmp346);
        if (_arr_status__tmp345 != 0) {
            *_err1 = _err_idx__tmp345; return 1;
        }
        int _status__tmp343 = til_format(&_tmp342, &_err0__tmp343, &_err1__tmp343, &_err2__tmp343, ((til_Str){(til_I64)"src/examples/hello_script.til:96:52:", 36}), &_tmp344);
        if (_status__tmp343 != 0) {
            if (_status__tmp343 == 2) { *_err1 = _err1__tmp343; return 1; }
        }
        til_Array_delete(&_tmp344);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp342);
        return 1;
    }
    til_I64 til_dest = til_add(til_self->ptr, til_mul(til_index, til_self->type_size));
    til_memcpy(til_dest, (til_I64)til_value, til_self->type_size);
    return 0;
}

int til_Vec_pop(til_IndexOutOfBoundsError* _err1, til_Vec* til_self, til_Dynamic* til_dest) {
    if (til_I64_eq(til_self->_len, 0).data) {
        til_Str _tmp349;
        til_I64_OverflowError _err0__tmp350;
        til_IndexOutOfBoundsError _err1__tmp350;
        til_AllocError _err2__tmp350;
        til_Array _tmp351;
        til_AllocError _err_alloc__tmp352;
        til_IndexOutOfBoundsError _err_idx__tmp352;
        til_Str _tmp353 = ((til_Str){(til_I64)"Vec.pop: cannot pop from empty Vec", 34});
        int _arr_status__tmp352 = til_Array_new(&_tmp351, &_err_alloc__tmp352, "Str", 1);
        if (_arr_status__tmp352 != 0) {
        }
        _arr_status__tmp352 = til_Array_set(&_err_idx__tmp352, &_tmp351, 0, &_tmp353);
        if (_arr_status__tmp352 != 0) {
            *_err1 = _err_idx__tmp352; return 1;
        }
        int _status__tmp350 = til_format(&_tmp349, &_err0__tmp350, &_err1__tmp350, &_err2__tmp350, ((til_Str){(til_I64)"src/examples/hello_script.til:110:52:", 37}), &_tmp351);
        if (_status__tmp350 != 0) {
            if (_status__tmp350 == 2) { *_err1 = _err1__tmp350; return 1; }
        }
        til_Array_delete(&_tmp351);
        til_Str _tmp354;
        til_I64_OverflowError _err0__tmp355;
        til_IndexOutOfBoundsError _err1__tmp355;
        til_AllocError _err2__tmp355;
        til_Array _tmp356;
        til_AllocError _err_alloc__tmp357;
        til_IndexOutOfBoundsError _err_idx__tmp357;
        til_Str _tmp358 = ((til_Str){(til_I64)"Vec.pop: cannot pop from empty Vec", 34});
        int _arr_status__tmp357 = til_Array_new(&_tmp356, &_err_alloc__tmp357, "Str", 1);
        if (_arr_status__tmp357 != 0) {
        }
        _arr_status__tmp357 = til_Array_set(&_err_idx__tmp357, &_tmp356, 0, &_tmp358);
        if (_arr_status__tmp357 != 0) {
            *_err1 = _err_idx__tmp357; return 1;
        }
        int _status__tmp355 = til_format(&_tmp354, &_err0__tmp355, &_err1__tmp355, &_err2__tmp355, ((til_Str){(til_I64)"src/examples/hello_script.til:110:52:", 37}), &_tmp356);
        if (_status__tmp355 != 0) {
            if (_status__tmp355 == 2) { *_err1 = _err1__tmp355; return 1; }
        }
        til_Array_delete(&_tmp356);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp354);
        return 1;
    }
    til_I64 til_last_index = til_sub(til_self->_len, 1);
    til_IndexOutOfBoundsError _err0__tmp359 = {};
    int _status__tmp359 = til_Vec_get(&_err0__tmp359, (*til_self), til_last_index, (til_Dynamic*)&til_dest);
    if (_status__tmp359 == 1) { *_err1 = _err0__tmp359; return 1; }
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
    til_I64 _ret__tmp362;
    til_AllocError _err0__tmp362 = {};
    int _status__tmp362 = til_malloc(&_ret__tmp362, &_err0__tmp362, til_total_bytes);
    if (_status__tmp362 == 1) { *_err1 = _err0__tmp362; return 1; }
    til_cloned.ptr = _ret__tmp362;
    if (til_I64_eq(til_NULL, til_cloned.ptr).data) {
        til_Str _tmp364;
        til_I64_OverflowError _err0__tmp365;
        til_IndexOutOfBoundsError _err1__tmp365;
        til_AllocError _err2__tmp365;
        til_Array _tmp366;
        til_AllocError _err_alloc__tmp367;
        til_IndexOutOfBoundsError _err_idx__tmp367;
        til_Str _tmp368 = ((til_Str){(til_I64)"Vec.clone: malloc failed for ", 29});
        til_Str _tmp369 = til_I64_to_str(til_total_bytes);
        til_Str _tmp370 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp367 = til_Array_new(&_tmp366, &_err_alloc__tmp367, "Str", 3);
        if (_arr_status__tmp367 != 0) {
            *_err1 = _err_alloc__tmp367; return 1;
        }
        _arr_status__tmp367 = til_Array_set(&_err_idx__tmp367, &_tmp366, 0, &_tmp368);
        if (_arr_status__tmp367 != 0) {
        }
        _arr_status__tmp367 = til_Array_set(&_err_idx__tmp367, &_tmp366, 1, &_tmp369);
        if (_arr_status__tmp367 != 0) {
        }
        _arr_status__tmp367 = til_Array_set(&_err_idx__tmp367, &_tmp366, 2, &_tmp370);
        if (_arr_status__tmp367 != 0) {
        }
        int _status__tmp365 = til_format(&_tmp364, &_err0__tmp365, &_err1__tmp365, &_err2__tmp365, ((til_Str){(til_I64)"src/examples/hello_script.til:139:41:", 37}), &_tmp366);
        if (_status__tmp365 != 0) {
            if (_status__tmp365 == 3) { *_err1 = _err2__tmp365; return 1; }
        }
        til_Array_delete(&_tmp366);
        til_Str _tmp371;
        til_I64_OverflowError _err0__tmp372;
        til_IndexOutOfBoundsError _err1__tmp372;
        til_AllocError _err2__tmp372;
        til_Array _tmp373;
        til_AllocError _err_alloc__tmp374;
        til_IndexOutOfBoundsError _err_idx__tmp374;
        til_Str _tmp375 = ((til_Str){(til_I64)"Vec.clone: malloc failed for ", 29});
        til_Str _tmp376 = til_I64_to_str(til_total_bytes);
        til_Str _tmp377 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp374 = til_Array_new(&_tmp373, &_err_alloc__tmp374, "Str", 3);
        if (_arr_status__tmp374 != 0) {
            *_err1 = _err_alloc__tmp374; return 1;
        }
        _arr_status__tmp374 = til_Array_set(&_err_idx__tmp374, &_tmp373, 0, &_tmp375);
        if (_arr_status__tmp374 != 0) {
        }
        _arr_status__tmp374 = til_Array_set(&_err_idx__tmp374, &_tmp373, 1, &_tmp376);
        if (_arr_status__tmp374 != 0) {
        }
        _arr_status__tmp374 = til_Array_set(&_err_idx__tmp374, &_tmp373, 2, &_tmp377);
        if (_arr_status__tmp374 != 0) {
        }
        int _status__tmp372 = til_format(&_tmp371, &_err0__tmp372, &_err1__tmp372, &_err2__tmp372, ((til_Str){(til_I64)"src/examples/hello_script.til:139:41:", 37}), &_tmp373);
        if (_status__tmp372 != 0) {
            if (_status__tmp372 == 3) { *_err1 = _err2__tmp372; return 1; }
        }
        til_Array_delete(&_tmp373);
        *_err1 = til_AllocError_new(_tmp371);
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
                til_Array _tmp382;
                til_AllocError _err_alloc__tmp383;
                til_IndexOutOfBoundsError _err_idx__tmp383;
                til_Str _tmp384 = ((til_Str){(til_I64)"Vec.extend: capacity exceeded Vec.MAX_CAP", 41});
                int _arr_status__tmp383 = til_Array_new(&_tmp382, &_err_alloc__tmp383, "Str", 1);
                if (_arr_status__tmp383 != 0) {
                    *_err1 = _err_alloc__tmp383; return 1;
                }
                _arr_status__tmp383 = til_Array_set(&_err_idx__tmp383, &_tmp382, 0, &_tmp384);
                if (_arr_status__tmp383 != 0) {
                }
                til_panic(((til_Str){(til_I64)"src/examples/hello_script.til:158:27:", 37}), &_tmp382);
                til_Array_delete(&_tmp382);
            }
            til_I64 _ret__tmp385;
            til_I64 til_new_ptr;
            til_AllocError _err0__tmp385 = {};
            int _status__tmp385 = til_malloc(&_ret__tmp385, &_err0__tmp385, til_mul(til_new_cap, til_self->type_size));
            if (_status__tmp385 == 1) { *_err1 = _err0__tmp385; return 1; }
            til_new_ptr = _ret__tmp385;
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
        til_Str _tmp394;
        til_I64_OverflowError _err0__tmp395;
        til_IndexOutOfBoundsError _err1__tmp395;
        til_AllocError _err2__tmp395;
        til_Array _tmp396;
        til_AllocError _err_alloc__tmp397;
        til_IndexOutOfBoundsError _err_idx__tmp397;
        til_Str _tmp398 = ((til_Str){(til_I64)"Vec.remove: index out of bounds", 31});
        int _arr_status__tmp397 = til_Array_new(&_tmp396, &_err_alloc__tmp397, "Str", 1);
        if (_arr_status__tmp397 != 0) {
        }
        _arr_status__tmp397 = til_Array_set(&_err_idx__tmp397, &_tmp396, 0, &_tmp398);
        if (_arr_status__tmp397 != 0) {
            *_err1 = _err_idx__tmp397; return 1;
        }
        int _status__tmp395 = til_format(&_tmp394, &_err0__tmp395, &_err1__tmp395, &_err2__tmp395, ((til_Str){(til_I64)"src/examples/hello_script.til:202:52:", 37}), &_tmp396);
        if (_status__tmp395 != 0) {
            if (_status__tmp395 == 2) { *_err1 = _err1__tmp395; return 1; }
        }
        til_Array_delete(&_tmp396);
        til_Str _tmp399;
        til_I64_OverflowError _err0__tmp400;
        til_IndexOutOfBoundsError _err1__tmp400;
        til_AllocError _err2__tmp400;
        til_Array _tmp401;
        til_AllocError _err_alloc__tmp402;
        til_IndexOutOfBoundsError _err_idx__tmp402;
        til_Str _tmp403 = ((til_Str){(til_I64)"Vec.remove: index out of bounds", 31});
        int _arr_status__tmp402 = til_Array_new(&_tmp401, &_err_alloc__tmp402, "Str", 1);
        if (_arr_status__tmp402 != 0) {
        }
        _arr_status__tmp402 = til_Array_set(&_err_idx__tmp402, &_tmp401, 0, &_tmp403);
        if (_arr_status__tmp402 != 0) {
            *_err1 = _err_idx__tmp402; return 1;
        }
        int _status__tmp400 = til_format(&_tmp399, &_err0__tmp400, &_err1__tmp400, &_err2__tmp400, ((til_Str){(til_I64)"src/examples/hello_script.til:202:52:", 37}), &_tmp401);
        if (_status__tmp400 != 0) {
            if (_status__tmp400 == 2) { *_err1 = _err1__tmp400; return 1; }
        }
        til_Array_delete(&_tmp401);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp399);
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
    til_I64 _ret__tmp413;
    til_AllocError _err0__tmp413 = {};
    int _status__tmp413 = til_malloc(&_ret__tmp413, &_err0__tmp413, til_cloned.cap);
    if (_status__tmp413 == 1) { *_err1 = _err0__tmp413; return 1; }
    til_cloned.c_string = _ret__tmp413;
    if (til_I64_eq(til_NULL, til_cloned.c_string).data) {
        til_Str _tmp415;
        til_I64_OverflowError _err0__tmp416;
        til_IndexOutOfBoundsError _err1__tmp416;
        til_AllocError _err2__tmp416;
        til_Array _tmp417;
        til_AllocError _err_alloc__tmp418;
        til_IndexOutOfBoundsError _err_idx__tmp418;
        til_Str _tmp419 = ((til_Str){(til_I64)"Str.clone: malloc failed for ", 29});
        til_Str _tmp420 = til_I64_to_str(til_cloned.cap);
        til_Str _tmp421 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp418 = til_Array_new(&_tmp417, &_err_alloc__tmp418, "Str", 3);
        if (_arr_status__tmp418 != 0) {
            *_err1 = _err_alloc__tmp418; return 1;
        }
        _arr_status__tmp418 = til_Array_set(&_err_idx__tmp418, &_tmp417, 0, &_tmp419);
        if (_arr_status__tmp418 != 0) {
        }
        _arr_status__tmp418 = til_Array_set(&_err_idx__tmp418, &_tmp417, 1, &_tmp420);
        if (_arr_status__tmp418 != 0) {
        }
        _arr_status__tmp418 = til_Array_set(&_err_idx__tmp418, &_tmp417, 2, &_tmp421);
        if (_arr_status__tmp418 != 0) {
        }
        int _status__tmp416 = til_format(&_tmp415, &_err0__tmp416, &_err1__tmp416, &_err2__tmp416, ((til_Str){(til_I64)"src/examples/hello_script.til:46:41:", 36}), &_tmp417);
        if (_status__tmp416 != 0) {
            if (_status__tmp416 == 3) { *_err1 = _err2__tmp416; return 1; }
        }
        til_Array_delete(&_tmp417);
        til_Str _tmp422;
        til_I64_OverflowError _err0__tmp423;
        til_IndexOutOfBoundsError _err1__tmp423;
        til_AllocError _err2__tmp423;
        til_Array _tmp424;
        til_AllocError _err_alloc__tmp425;
        til_IndexOutOfBoundsError _err_idx__tmp425;
        til_Str _tmp426 = ((til_Str){(til_I64)"Str.clone: malloc failed for ", 29});
        til_Str _tmp427 = til_I64_to_str(til_cloned.cap);
        til_Str _tmp428 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp425 = til_Array_new(&_tmp424, &_err_alloc__tmp425, "Str", 3);
        if (_arr_status__tmp425 != 0) {
            *_err1 = _err_alloc__tmp425; return 1;
        }
        _arr_status__tmp425 = til_Array_set(&_err_idx__tmp425, &_tmp424, 0, &_tmp426);
        if (_arr_status__tmp425 != 0) {
        }
        _arr_status__tmp425 = til_Array_set(&_err_idx__tmp425, &_tmp424, 1, &_tmp427);
        if (_arr_status__tmp425 != 0) {
        }
        _arr_status__tmp425 = til_Array_set(&_err_idx__tmp425, &_tmp424, 2, &_tmp428);
        if (_arr_status__tmp425 != 0) {
        }
        int _status__tmp423 = til_format(&_tmp422, &_err0__tmp423, &_err1__tmp423, &_err2__tmp423, ((til_Str){(til_I64)"src/examples/hello_script.til:46:41:", 36}), &_tmp424);
        if (_status__tmp423 != 0) {
            if (_status__tmp423 == 3) { *_err1 = _err2__tmp423; return 1; }
        }
        til_Array_delete(&_tmp424);
        *_err1 = til_AllocError_new(_tmp422);
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
        til_Str _ret__tmp465;
        til_AllocError _err0__tmp465 = {};
        int _status__tmp465 = til_Str_clone(&_ret__tmp465, &_err0__tmp465, til_self);
        if (_status__tmp465 == 1) { *_err1 = _err0__tmp465; return 1; }
        *_ret = _ret__tmp465;
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
        til_Str _ret__tmp473;
        til_AllocError _err0__tmp473 = {};
        int _status__tmp473 = til_Str_clone(&_ret__tmp473, &_err0__tmp473, til_self);
        if (_status__tmp473 == 1) { *_err1 = _err0__tmp473; return 1; }
        *_ret = _ret__tmp473;
        return 0;
    }
    til_I64 til_new_len = til_add(til_sub(til_Str_len(til_self), til_mul(til_count, til_Str_len(til_from))), til_mul(til_count, til_Str_len(til_to)));
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_new_len;
    til_I64 _ret__tmp474;
    til_AllocError _err0__tmp474 = {};
    int _status__tmp474 = til_malloc(&_ret__tmp474, &_err0__tmp474, til_new_len);
    if (_status__tmp474 == 1) { *_err1 = _err0__tmp474; return 1; }
    til_result.c_string = _ret__tmp474;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Str _tmp476;
        til_I64_OverflowError _err0__tmp477;
        til_IndexOutOfBoundsError _err1__tmp477;
        til_AllocError _err2__tmp477;
        til_Array _tmp478;
        til_AllocError _err_alloc__tmp479;
        til_IndexOutOfBoundsError _err_idx__tmp479;
        til_Str _tmp480 = ((til_Str){(til_I64)"Str.replace: malloc failed for ", 31});
        til_Str _tmp481 = til_I64_to_str(til_new_len);
        til_Str _tmp482 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp479 = til_Array_new(&_tmp478, &_err_alloc__tmp479, "Str", 3);
        if (_arr_status__tmp479 != 0) {
            *_err1 = _err_alloc__tmp479; return 1;
        }
        _arr_status__tmp479 = til_Array_set(&_err_idx__tmp479, &_tmp478, 0, &_tmp480);
        if (_arr_status__tmp479 != 0) {
        }
        _arr_status__tmp479 = til_Array_set(&_err_idx__tmp479, &_tmp478, 1, &_tmp481);
        if (_arr_status__tmp479 != 0) {
        }
        _arr_status__tmp479 = til_Array_set(&_err_idx__tmp479, &_tmp478, 2, &_tmp482);
        if (_arr_status__tmp479 != 0) {
        }
        int _status__tmp477 = til_format(&_tmp476, &_err0__tmp477, &_err1__tmp477, &_err2__tmp477, ((til_Str){(til_I64)"src/examples/hello_script.til:213:41:", 37}), &_tmp478);
        if (_status__tmp477 != 0) {
            if (_status__tmp477 == 3) { *_err1 = _err2__tmp477; return 1; }
        }
        til_Array_delete(&_tmp478);
        til_Str _tmp483;
        til_I64_OverflowError _err0__tmp484;
        til_IndexOutOfBoundsError _err1__tmp484;
        til_AllocError _err2__tmp484;
        til_Array _tmp485;
        til_AllocError _err_alloc__tmp486;
        til_IndexOutOfBoundsError _err_idx__tmp486;
        til_Str _tmp487 = ((til_Str){(til_I64)"Str.replace: malloc failed for ", 31});
        til_Str _tmp488 = til_I64_to_str(til_new_len);
        til_Str _tmp489 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp486 = til_Array_new(&_tmp485, &_err_alloc__tmp486, "Str", 3);
        if (_arr_status__tmp486 != 0) {
            *_err1 = _err_alloc__tmp486; return 1;
        }
        _arr_status__tmp486 = til_Array_set(&_err_idx__tmp486, &_tmp485, 0, &_tmp487);
        if (_arr_status__tmp486 != 0) {
        }
        _arr_status__tmp486 = til_Array_set(&_err_idx__tmp486, &_tmp485, 1, &_tmp488);
        if (_arr_status__tmp486 != 0) {
        }
        _arr_status__tmp486 = til_Array_set(&_err_idx__tmp486, &_tmp485, 2, &_tmp489);
        if (_arr_status__tmp486 != 0) {
        }
        int _status__tmp484 = til_format(&_tmp483, &_err0__tmp484, &_err1__tmp484, &_err2__tmp484, ((til_Str){(til_I64)"src/examples/hello_script.til:213:41:", 37}), &_tmp485);
        if (_status__tmp484 != 0) {
            if (_status__tmp484 == 3) { *_err1 = _err2__tmp484; return 1; }
        }
        til_Array_delete(&_tmp485);
        *_err1 = til_AllocError_new(_tmp483);
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
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp501;
    if (til_I64_eq(til_Str_len(til_from), 0).data) {
        til_Str _ret__tmp503;
        til_AllocError _err0__tmp503 = {};
        int _status__tmp503 = til_Str_clone(&_ret__tmp503, &_err0__tmp503, til_self);
        if (_status__tmp503 == 1) { *_err1 = _err0__tmp503; return 1; }
        *_ret = _ret__tmp503;
        return 0;
    }
    if (til_I64_eq(til_n, 0).data) {
        til_Str _ret__tmp505;
        til_AllocError _err0__tmp505 = {};
        int _status__tmp505 = til_Str_clone(&_ret__tmp505, &_err0__tmp505, til_self);
        if (_status__tmp505 == 1) { *_err1 = _err0__tmp505; return 1; }
        *_ret = _ret__tmp505;
        return 0;
    }
    til_I64 til_idx = til_Str_find(til_self, til_from);
    if (til_lt(til_idx, 0).data) {
        til_Str _ret__tmp507;
        til_AllocError _err0__tmp507 = {};
        int _status__tmp507 = til_Str_clone(&_ret__tmp507, &_err0__tmp507, til_self);
        if (_status__tmp507 == 1) { *_err1 = _err0__tmp507; return 1; }
        *_ret = _ret__tmp507;
        return 0;
    }
    til_Str _ret__tmp508;
    til_Str til_prefix;
    til_IndexOutOfBoundsError _err0__tmp508 = {};
    til_AllocError _err1__tmp508 = {};
    int _status__tmp508 = til_get_substr(&_ret__tmp508, &_err0__tmp508, &_err1__tmp508, til_self, 0, til_idx);
    if (_status__tmp508 == 2) { *_err1 = _err1__tmp508; return 1; }
    til_prefix = _ret__tmp508;
    til_Str _ret__tmp509;
    til_Str til_suffix;
    til_IndexOutOfBoundsError _err0__tmp509 = {};
    til_AllocError _err1__tmp509 = {};
    int _status__tmp509 = til_get_substr(&_ret__tmp509, &_err0__tmp509, &_err1__tmp509, til_self, til_add(til_idx, til_Str_len(til_from)), til_Str_len(til_self));
    if (_status__tmp509 == 2) { *_err1 = _err1__tmp509; return 1; }
    til_suffix = _ret__tmp509;
    til_Str til_result = til_concat(til_concat(til_prefix, til_to), til_suffix);
    if (til_gt(til_n, 1).data) {
        til_Str _ret__tmp511;
        til_Str til_rest;
        til_AllocError _err0__tmp511 = {};
        int _status__tmp511 = til_Str_replacen(&_ret__tmp511, &_err0__tmp511, til_suffix, til_from, til_to, til_sub(til_n, 1));
        if (_status__tmp511 == 1) { *_err1 = _err0__tmp511; return 1; }
        til_rest = _ret__tmp511;
        til_result = til_concat(til_concat(til_prefix, til_to), til_rest);
    }
    *_ret = til_result;
    return 0;
    goto _end_catches__tmp501;
_catch_IndexOutOfBoundsError__tmp501: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp501;
    til_Str _ret__tmp513;
    til_AllocError _err0__tmp513 = {};
    int _status__tmp513 = til_Str_clone(&_ret__tmp513, &_err0__tmp513, til_self);
    if (_status__tmp513 == 1) { *_err1 = _err0__tmp513; return 1; }
    til_result = _ret__tmp513;
    }
_end_catches__tmp501:;
}

int til_Str_split(til_Vec* _ret, til_AllocError* _err1, til_IndexOutOfBoundsError* _err2, const til_Str til_self, const til_Str til_delimiter) {
    til_Vec _ret__tmp515;
    til_Vec til_parts;
    til_AllocError _err0__tmp515 = {};
    int _status__tmp515 = til_Vec_new(&_ret__tmp515, &_err0__tmp515, "Str");
    if (_status__tmp515 == 1) { *_err1 = _err0__tmp515; return 1; }
    til_parts = _ret__tmp515;
    if (til_I64_eq(til_Str_len(til_delimiter), 0).data) {
        til_Str _tmp518;
        til_AllocError _err0__tmp519;
        int _status__tmp519 = til_Str_clone(&_tmp518, &_err0__tmp519, til_self);
        if (_status__tmp519 != 0) {
            if (_status__tmp519 == 1) { *_err1 = _err0__tmp519; return 1; }
        }
        til_AllocError _err0__tmp517 = {};
        int _status__tmp517 = til_Vec_push(&_err0__tmp517, &til_parts, &_tmp518);
        if (_status__tmp517 == 1) { *_err1 = _err0__tmp517; return 1; }
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
                til_Str _ret__tmp526;
                til_Str til_part;
                til_IndexOutOfBoundsError _err0__tmp526 = {};
                til_AllocError _err1__tmp526 = {};
                int _status__tmp526 = til_get_substr(&_ret__tmp526, &_err0__tmp526, &_err1__tmp526, til_self, til_start, til_pos);
                if (_status__tmp526 == 1) { *_err2 = _err0__tmp526; return 2; }
                if (_status__tmp526 == 2) { *_err1 = _err1__tmp526; return 1; }
                til_part = _ret__tmp526;
                til_AllocError _err0__tmp527 = {};
                int _status__tmp527 = til_Vec_push(&_err0__tmp527, &til_parts, (til_Dynamic*)&til_part);
                if (_status__tmp527 == 1) { *_err1 = _err0__tmp527; return 1; }
            } else {
                til_Str _tmp530 = ((til_Str){(til_I64)"", 0});
                til_AllocError _err0__tmp529 = {};
                int _status__tmp529 = til_Vec_push(&_err0__tmp529, &til_parts, &_tmp530);
                if (_status__tmp529 == 1) { *_err1 = _err0__tmp529; return 1; }
            }
            til_start = til_add(til_pos, til_Str_len(til_delimiter));
            til_pos = til_start;
        } else {
            til_pos = til_add(til_pos, 1);
        }
    }
    if (til_lt(til_start, til_Str_len(til_self)).data) {
        til_Str _ret__tmp533;
        til_Str til_part;
        til_IndexOutOfBoundsError _err0__tmp533 = {};
        til_AllocError _err1__tmp533 = {};
        int _status__tmp533 = til_get_substr(&_ret__tmp533, &_err0__tmp533, &_err1__tmp533, til_self, til_start, til_Str_len(til_self));
        if (_status__tmp533 == 1) { *_err2 = _err0__tmp533; return 2; }
        if (_status__tmp533 == 2) { *_err1 = _err1__tmp533; return 1; }
        til_part = _ret__tmp533;
        til_AllocError _err0__tmp534 = {};
        int _status__tmp534 = til_Vec_push(&_err0__tmp534, &til_parts, (til_Dynamic*)&til_part);
        if (_status__tmp534 == 1) { *_err1 = _err0__tmp534; return 1; }
    } else {
        if (til_I64_eq(til_start, til_Str_len(til_self)).data) {
            til_Str _tmp538 = ((til_Str){(til_I64)"", 0});
            til_AllocError _err0__tmp537 = {};
            int _status__tmp537 = til_Vec_push(&_err0__tmp537, &til_parts, &_tmp538);
            if (_status__tmp537 == 1) { *_err1 = _err0__tmp537; return 1; }
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
    til_U8 _ret__tmp546;
    til_U8_OverflowError _err0__tmp546 = {};
    int _status__tmp546 = til_U8_from_i64(&_ret__tmp546, &_err0__tmp546, til_add(til_U8_to_i64(til_a), til_U8_to_i64(til_b)));
    if (_status__tmp546 == 1) { *_err1 = _err0__tmp546; return 1; }
    *_ret = _ret__tmp546;
    return 0;
}

int til_U8_from_i64(til_U8* _ret, til_U8_OverflowError* _err1, const til_I64 til_self) {
    if (til_lt(til_self, 0).data) {
        til_Str _tmp549;
        til_I64_OverflowError _err0__tmp550;
        til_IndexOutOfBoundsError _err1__tmp550;
        til_AllocError _err2__tmp550;
        til_Array _tmp551;
        til_AllocError _err_alloc__tmp552;
        til_IndexOutOfBoundsError _err_idx__tmp552;
        til_Str _tmp553 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        int _arr_status__tmp552 = til_Array_new(&_tmp551, &_err_alloc__tmp552, "Str", 1);
        if (_arr_status__tmp552 != 0) {
        }
        _arr_status__tmp552 = til_Array_set(&_err_idx__tmp552, &_tmp551, 0, &_tmp553);
        if (_arr_status__tmp552 != 0) {
        }
        int _status__tmp550 = til_format(&_tmp549, &_err0__tmp550, &_err1__tmp550, &_err2__tmp550, ((til_Str){(til_I64)"src/examples/hello_script.til:56:47:", 36}), &_tmp551);
        if (_status__tmp550 != 0) {
        }
        til_Array_delete(&_tmp551);
        til_Str _tmp554;
        til_I64_OverflowError _err0__tmp555;
        til_IndexOutOfBoundsError _err1__tmp555;
        til_AllocError _err2__tmp555;
        til_Array _tmp556;
        til_AllocError _err_alloc__tmp557;
        til_IndexOutOfBoundsError _err_idx__tmp557;
        til_Str _tmp558 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        int _arr_status__tmp557 = til_Array_new(&_tmp556, &_err_alloc__tmp557, "Str", 1);
        if (_arr_status__tmp557 != 0) {
        }
        _arr_status__tmp557 = til_Array_set(&_err_idx__tmp557, &_tmp556, 0, &_tmp558);
        if (_arr_status__tmp557 != 0) {
        }
        int _status__tmp555 = til_format(&_tmp554, &_err0__tmp555, &_err1__tmp555, &_err2__tmp555, ((til_Str){(til_I64)"src/examples/hello_script.til:56:47:", 36}), &_tmp556);
        if (_status__tmp555 != 0) {
        }
        til_Array_delete(&_tmp556);
        *_err1 = til_U8_OverflowError_new(_tmp554);
        return 1;
    }
    if (til_gt(til_self, til_MAX_U8).data) {
        til_Str _tmp560;
        til_I64_OverflowError _err0__tmp561;
        til_IndexOutOfBoundsError _err1__tmp561;
        til_AllocError _err2__tmp561;
        til_Array _tmp562;
        til_AllocError _err_alloc__tmp563;
        til_IndexOutOfBoundsError _err_idx__tmp563;
        til_Str _tmp564 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp565 = til_I64_to_str(til_MAX_U8);
        int _arr_status__tmp563 = til_Array_new(&_tmp562, &_err_alloc__tmp563, "Str", 2);
        if (_arr_status__tmp563 != 0) {
        }
        _arr_status__tmp563 = til_Array_set(&_err_idx__tmp563, &_tmp562, 0, &_tmp564);
        if (_arr_status__tmp563 != 0) {
        }
        _arr_status__tmp563 = til_Array_set(&_err_idx__tmp563, &_tmp562, 1, &_tmp565);
        if (_arr_status__tmp563 != 0) {
        }
        int _status__tmp561 = til_format(&_tmp560, &_err0__tmp561, &_err1__tmp561, &_err2__tmp561, ((til_Str){(til_I64)"src/examples/hello_script.til:59:47:", 36}), &_tmp562);
        if (_status__tmp561 != 0) {
        }
        til_Array_delete(&_tmp562);
        til_Str _tmp566;
        til_I64_OverflowError _err0__tmp567;
        til_IndexOutOfBoundsError _err1__tmp567;
        til_AllocError _err2__tmp567;
        til_Array _tmp568;
        til_AllocError _err_alloc__tmp569;
        til_IndexOutOfBoundsError _err_idx__tmp569;
        til_Str _tmp570 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp571 = til_I64_to_str(til_MAX_U8);
        int _arr_status__tmp569 = til_Array_new(&_tmp568, &_err_alloc__tmp569, "Str", 2);
        if (_arr_status__tmp569 != 0) {
        }
        _arr_status__tmp569 = til_Array_set(&_err_idx__tmp569, &_tmp568, 0, &_tmp570);
        if (_arr_status__tmp569 != 0) {
        }
        _arr_status__tmp569 = til_Array_set(&_err_idx__tmp569, &_tmp568, 1, &_tmp571);
        if (_arr_status__tmp569 != 0) {
        }
        int _status__tmp567 = til_format(&_tmp566, &_err0__tmp567, &_err1__tmp567, &_err2__tmp567, ((til_Str){(til_I64)"src/examples/hello_script.til:59:47:", 36}), &_tmp568);
        if (_status__tmp567 != 0) {
        }
        til_Array_delete(&_tmp568);
        *_err1 = til_U8_OverflowError_new(_tmp566);
        return 1;
    }
    *_ret = til_i64_to_u8(til_self);
    return 0;
}

til_Str til_U8_to_str(const til_U8 til_self) {
    return til_I64_to_str(til_U8_to_i64(til_self));
}

int til_U8_from_str(til_U8* _ret, til_U8_OverflowError* _err1, const til_Str til_s) {
    til_U8 _ret__tmp574;
    til_U8_OverflowError _err0__tmp574 = {};
    int _status__tmp574 = til_U8_from_i64(&_ret__tmp574, &_err0__tmp574, til_I64_from_str(til_s));
    if (_status__tmp574 == 1) { *_err1 = _err0__tmp574; return 1; }
    *_ret = _ret__tmp574;
    return 0;
}

til_I64 til_U8_size(void) {
    return 1;
}

int main() {
    til_Array _tmp577;
    til_AllocError _err_alloc__tmp578;
    til_IndexOutOfBoundsError _err_idx__tmp578;
    til_Str _tmp579 = ((til_Str){(til_I64)"Hello World!", 12});
    int _arr_status__tmp578 = til_Array_new(&_tmp577, &_err_alloc__tmp578, "Str", 1);
    if (_arr_status__tmp578 != 0) {
    }
    _arr_status__tmp578 = til_Array_set(&_err_idx__tmp578, &_tmp577, 0, &_tmp579);
    if (_arr_status__tmp578 != 0) {
    }
    til_println(&_tmp577);
    til_Array_delete(&_tmp577);
    return 0;
}
