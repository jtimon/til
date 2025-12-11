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
        til_Str _tmp80 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp81 = til_I64_to_str(til_end);
        til_Str _tmp82 = ((til_Str){(til_I64)" cannot be negative", 19});
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
        int _status__tmp77 = til_format(&_tmp76, &_err0__tmp77, &_err1__tmp77, &_err2__tmp77, ((til_Str){(til_I64)"src/examples/hello_script.til:360:48:", 37}), &_tmp78);
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
        til_Str _tmp88 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp89 = til_I64_to_str(til_start);
        til_Str _tmp90 = ((til_Str){(til_I64)" is greater than end index ", 27});
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
        int _status__tmp85 = til_format(&_tmp84, &_err0__tmp85, &_err1__tmp85, &_err2__tmp85, ((til_Str){(til_I64)"src/examples/hello_script.til:363:48:", 37}), &_tmp86);
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
        til_Str _tmp97 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp98 = til_I64_to_str(til_end);
        til_Str _tmp99 = ((til_Str){(til_I64)" is greater than string length ", 31});
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
        int _status__tmp94 = til_format(&_tmp93, &_err0__tmp94, &_err1__tmp94, &_err2__tmp94, ((til_Str){(til_I64)"src/examples/hello_script.til:366:48:", 37}), &_tmp95);
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
        til_Str _tmp106 = ((til_Str){(til_I64)"get_substr: start and end are the same (", 40});
        til_Str _tmp107 = til_I64_to_str(til_start);
        til_Str _tmp108 = ((til_Str){(til_I64)"), no substring", 15});
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
        int _status__tmp103 = til_format(&_tmp102, &_err0__tmp103, &_err1__tmp103, &_err2__tmp103, ((til_Str){(til_I64)"src/examples/hello_script.til:369:48:", 37}), &_tmp104);
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
        til_Str _tmp115 = ((til_Str){(til_I64)"Str.get_substr: failed to allocate ", 35});
        til_Str _tmp116 = til_I64_to_str(til_substr.cap);
        til_Str _tmp117 = ((til_Str){(til_I64)" bytes", 6});
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
        int _status__tmp112 = til_format(&_tmp111, &_err0__tmp112, &_err1__tmp112, &_err2__tmp112, ((til_Str){(til_I64)"src/examples/hello_script.til:376:37:", 37}), &_tmp113);
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
        til_Str _tmp128 = ((til_Str){(til_I64)"concat: integer overflow", 24});
        int _arr_status__tmp127 = til_Array_new(&_tmp126, &_err_alloc__tmp127, "Str", 1);
        if (_arr_status__tmp127 != 0) {
        }
        _arr_status__tmp127 = til_Array_set(&_err_idx__tmp127, &_tmp126, 0, &_tmp128);
        if (_arr_status__tmp127 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/examples/hello_script.til:416:15:", 37}), &_tmp126);
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
        til_panic(((til_Str){(til_I64)"src/examples/hello_script.til:428:15:", 37}), &_tmp131);
        til_Array_delete(&_tmp131);
    }
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Array _tmp135;
        til_AllocError _err_alloc__tmp136;
        til_IndexOutOfBoundsError _err_idx__tmp136;
        til_Str _tmp137 = ((til_Str){(til_I64)"concat: malloc failed", 21});
        int _arr_status__tmp136 = til_Array_new(&_tmp135, &_err_alloc__tmp136, "Str", 1);
        if (_arr_status__tmp136 != 0) {
        }
        _arr_status__tmp136 = til_Array_set(&_err_idx__tmp136, &_tmp135, 0, &_tmp137);
        if (_arr_status__tmp136 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/examples/hello_script.til:421:15:", 37}), &_tmp135);
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
    til_panic(((til_Str){(til_I64)"src/examples/hello_script.til:428:15:", 37}), &_tmp139);
    til_Array_delete(&_tmp139);
    }
_end_catches__tmp124:;
}

int til_format(til_Str* _ret, til_I64_OverflowError* _err1, til_IndexOutOfBoundsError* _err2, til_AllocError* _err3, const til_Str til_prefix, til_Array* til_args) {
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_prefix.cap;
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Str til_arg = ((til_Str){(til_I64)"", 0});
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
            til_Str _tmp151 = ((til_Str){(til_I64)"format: integer overflow while summing cap for arg ", 51});
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
            int _status__tmp148 = til_format(&_tmp147, &_err0__tmp148, &_err1__tmp148, &_err2__tmp148, ((til_Str){(til_I64)"src/examples/hello_script.til:444:48:", 37}), &_tmp149);
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
        til_Str _tmp159 = ((til_Str){(til_I64)"format: malloc failed for cap = ", 32});
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
        int _status__tmp156 = til_format(&_tmp155, &_err0__tmp156, &_err1__tmp156, &_err2__tmp156, ((til_Str){(til_I64)"src/examples/hello_script.til:450:37:", 37}), &_tmp157);
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
        til_Str til_s = ((til_Str){(til_I64)"", 0});
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
    til_I64 _ret__tmp169;
    til_AllocError _err0__tmp169 = {};
    int _status__tmp169 = til_malloc(&_ret__tmp169, &_err0__tmp169, til_size_bytes);
    if (_status__tmp169 == 1) { *_err1 = _err0__tmp169; return 1; }
    til_arr.ptr = _ret__tmp169;
    til_U8 _tmp170;
    til_U8_OverflowError _err0__tmp171;
    int _status__tmp171 = til_U8_from_i64(&_tmp170, &_err0__tmp171, 0);
    if (_status__tmp171 != 0) {
    }
    til_memset(til_arr.ptr, _tmp170, til_size_bytes);
    til_arr._len = til_capacity;
    *_ret = til_arr;
    return 0;
}

int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array til_self, const til_I64 til_index, til_Dynamic* til_T) {
    if (til_gteq(til_index, til_self._len).data) {
        til_Str _tmp174;
        til_I64_OverflowError _err0__tmp175;
        til_IndexOutOfBoundsError _err1__tmp175;
        til_AllocError _err2__tmp175;
        til_Array _tmp176;
        til_AllocError _err_alloc__tmp177;
        til_IndexOutOfBoundsError _err_idx__tmp177;
        til_Str _tmp178 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        int _arr_status__tmp177 = til_Array_new(&_tmp176, &_err_alloc__tmp177, "Str", 1);
        if (_arr_status__tmp177 != 0) {
        }
        _arr_status__tmp177 = til_Array_set(&_err_idx__tmp177, &_tmp176, 0, &_tmp178);
        if (_arr_status__tmp177 != 0) {
            *_err1 = _err_idx__tmp177; return 1;
        }
        int _status__tmp175 = til_format(&_tmp174, &_err0__tmp175, &_err1__tmp175, &_err2__tmp175, ((til_Str){(til_I64)"src/examples/hello_script.til:41:52:", 36}), &_tmp176);
        if (_status__tmp175 != 0) {
            if (_status__tmp175 == 2) { *_err1 = _err1__tmp175; return 1; }
        }
        til_Array_delete(&_tmp176);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp174);
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_gteq(til_index, til_self->_len).data) {
        til_Str _tmp181;
        til_I64_OverflowError _err0__tmp182;
        til_IndexOutOfBoundsError _err1__tmp182;
        til_AllocError _err2__tmp182;
        til_Array _tmp183;
        til_AllocError _err_alloc__tmp184;
        til_IndexOutOfBoundsError _err_idx__tmp184;
        til_Str _tmp185 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        int _arr_status__tmp184 = til_Array_new(&_tmp183, &_err_alloc__tmp184, "Str", 1);
        if (_arr_status__tmp184 != 0) {
        }
        _arr_status__tmp184 = til_Array_set(&_err_idx__tmp184, &_tmp183, 0, &_tmp185);
        if (_arr_status__tmp184 != 0) {
            *_err1 = _err_idx__tmp184; return 1;
        }
        int _status__tmp182 = til_format(&_tmp181, &_err0__tmp182, &_err1__tmp182, &_err2__tmp182, ((til_Str){(til_I64)"src/examples/hello_script.til:56:52:", 36}), &_tmp183);
        if (_status__tmp182 != 0) {
            if (_status__tmp182 == 2) { *_err1 = _err1__tmp182; return 1; }
        }
        til_Array_delete(&_tmp183);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp181);
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
    til_I64 _ret__tmp188;
    til_AllocError _err0__tmp188 = {};
    int _status__tmp188 = til_malloc(&_ret__tmp188, &_err0__tmp188, til_total_bytes);
    if (_status__tmp188 == 1) { *_err1 = _err0__tmp188; return 1; }
    til_cloned.ptr = _ret__tmp188;
    if (til_I64_eq(til_NULL, til_cloned.ptr).data) {
        til_Str _tmp190;
        til_I64_OverflowError _err0__tmp191;
        til_IndexOutOfBoundsError _err1__tmp191;
        til_AllocError _err2__tmp191;
        til_Array _tmp192;
        til_AllocError _err_alloc__tmp193;
        til_IndexOutOfBoundsError _err_idx__tmp193;
        til_Str _tmp194 = ((til_Str){(til_I64)"Array.clone: malloc failed for ", 31});
        til_Str _tmp195 = til_I64_to_str(til_total_bytes);
        til_Str _tmp196 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp193 = til_Array_new(&_tmp192, &_err_alloc__tmp193, "Str", 3);
        if (_arr_status__tmp193 != 0) {
            *_err1 = _err_alloc__tmp193; return 1;
        }
        _arr_status__tmp193 = til_Array_set(&_err_idx__tmp193, &_tmp192, 0, &_tmp194);
        if (_arr_status__tmp193 != 0) {
        }
        _arr_status__tmp193 = til_Array_set(&_err_idx__tmp193, &_tmp192, 1, &_tmp195);
        if (_arr_status__tmp193 != 0) {
        }
        _arr_status__tmp193 = til_Array_set(&_err_idx__tmp193, &_tmp192, 2, &_tmp196);
        if (_arr_status__tmp193 != 0) {
        }
        int _status__tmp191 = til_format(&_tmp190, &_err0__tmp191, &_err1__tmp191, &_err2__tmp191, ((til_Str){(til_I64)"src/examples/hello_script.til:83:41:", 36}), &_tmp192);
        if (_status__tmp191 != 0) {
            if (_status__tmp191 == 3) { *_err1 = _err2__tmp191; return 1; }
        }
        til_Array_delete(&_tmp192);
        *_err1 = til_AllocError_new(_tmp190);
        return 1;
    }
    til_memcpy(til_cloned.ptr, til_self.ptr, til_total_bytes);
    *_ret = til_cloned;
    return 0;
}

til_Bool til_Array_contains(const til_Array til_self, const til_Str til_value) {
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp197;
    til_I64 til_i = 0;
    while (til_lt(til_i, til_self._len).data) {
        til_Str til_elem = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp199 = {};
        int _status__tmp199 = til_Array_get(&_err0__tmp199, til_self, til_i, (til_Dynamic*)&til_elem);
        if (_status__tmp199 == 1) { _thrown_IndexOutOfBoundsError__tmp197 = _err0__tmp199; goto _catch_IndexOutOfBoundsError__tmp197; }
        if (til_Str_eq(til_elem, til_value).data) {
            return true;
        }
        til_i = til_add(til_i, 1);
    }
    return false;
    goto _end_catches__tmp197;
_catch_IndexOutOfBoundsError__tmp197: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp197;
    }
_end_catches__tmp197:;
}

til_I64 til_Bool_len(const til_Bool til_self) {
    return 1;
}

til_Bool til_Bool_eq(const til_Bool til_a, const til_Bool til_b) {
    til_Bool _tmp204;
    til_Array _tmp205;
    til_AllocError _err_alloc__tmp206;
    til_IndexOutOfBoundsError _err_idx__tmp206;
    til_Bool _tmp207 = til_a;
    til_Bool _tmp208 = til_b;
    int _arr_status__tmp206 = til_Array_new(&_tmp205, &_err_alloc__tmp206, "Bool", 2);
    if (_arr_status__tmp206 != 0) {
    }
    _arr_status__tmp206 = til_Array_set(&_err_idx__tmp206, &_tmp205, 0, &_tmp207);
    if (_arr_status__tmp206 != 0) {
    }
    _arr_status__tmp206 = til_Array_set(&_err_idx__tmp206, &_tmp205, 1, &_tmp208);
    if (_arr_status__tmp206 != 0) {
    }
    _tmp204 = til_and(&_tmp205);
    til_Array_delete(&_tmp205);
    til_Bool _tmp209;
    til_Array _tmp210;
    til_AllocError _err_alloc__tmp211;
    til_IndexOutOfBoundsError _err_idx__tmp211;
    til_Bool _tmp212 = til_not(til_b);
    til_Bool _tmp213 = til_not(til_a);
    int _arr_status__tmp211 = til_Array_new(&_tmp210, &_err_alloc__tmp211, "Bool", 2);
    if (_arr_status__tmp211 != 0) {
    }
    _arr_status__tmp211 = til_Array_set(&_err_idx__tmp211, &_tmp210, 0, &_tmp212);
    if (_arr_status__tmp211 != 0) {
    }
    _arr_status__tmp211 = til_Array_set(&_err_idx__tmp211, &_tmp210, 1, &_tmp213);
    if (_arr_status__tmp211 != 0) {
    }
    _tmp209 = til_and(&_tmp210);
    til_Array_delete(&_tmp210);
    til_Array _tmp214;
    til_AllocError _err_alloc__tmp215;
    til_IndexOutOfBoundsError _err_idx__tmp215;
    int _arr_status__tmp215 = til_Array_new(&_tmp214, &_err_alloc__tmp215, "Bool", 2);
    if (_arr_status__tmp215 != 0) {
    }
    _arr_status__tmp215 = til_Array_set(&_err_idx__tmp215, &_tmp214, 0, &_tmp204);
    if (_arr_status__tmp215 != 0) {
    }
    _arr_status__tmp215 = til_Array_set(&_err_idx__tmp215, &_tmp214, 1, &_tmp209);
    if (_arr_status__tmp215 != 0) {
    }
    til_Bool _tmp216 = til_or(&_tmp214);
    til_Array_delete(&_tmp214);
    return _tmp216;
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
    til_I64 _ret__tmp240;
    til_AllocError _err0__tmp240 = {};
    int _status__tmp240 = til_malloc(&_ret__tmp240, &_err0__tmp240, til_size_bytes);
    if (_status__tmp240 == 1) { *_err1 = _err0__tmp240; return 1; }
    til_vec.ptr = _ret__tmp240;
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
    til_I64 _ret__tmp242;
    til_AllocError _err0__tmp242 = {};
    int _status__tmp242 = til_malloc(&_ret__tmp242, &_err0__tmp242, til_size_bytes);
    if (_status__tmp242 == 1) { *_err1 = _err0__tmp242; return 1; }
    til_vec.ptr = _ret__tmp242;
    til_vec._len = 0;
    til_vec.cap = til_Vec_INIT_CAP;
    *_ret = til_vec;
    return 0;
}

int til_Vec_push(til_AllocError* _err1, til_Vec* til_self, const til_Dynamic til_value) {
    if (til_I64_eq(til_self->_len, til_self->cap).data) {
        const til_I64 til_new_cap = til_mul(til_self->cap, 2);
        if (til_gt(til_new_cap, til_Vec_MAX_CAP).data) {
            til_Array _tmp246;
            til_AllocError _err_alloc__tmp247;
            til_IndexOutOfBoundsError _err_idx__tmp247;
            til_Str _tmp248 = ((til_Str){(til_I64)"Vec.push: capacity exceeded Vec.MAX_CAP", 39});
            int _arr_status__tmp247 = til_Array_new(&_tmp246, &_err_alloc__tmp247, "Str", 1);
            if (_arr_status__tmp247 != 0) {
                *_err1 = _err_alloc__tmp247; return 1;
            }
            _arr_status__tmp247 = til_Array_set(&_err_idx__tmp247, &_tmp246, 0, &_tmp248);
            if (_arr_status__tmp247 != 0) {
            }
            til_panic(((til_Str){(til_I64)"src/examples/hello_script.til:63:23:", 36}), &_tmp246);
            til_Array_delete(&_tmp246);
        }
        til_I64 _ret__tmp249;
        til_I64 til_new_ptr;
        til_AllocError _err0__tmp249 = {};
        int _status__tmp249 = til_malloc(&_ret__tmp249, &_err0__tmp249, til_mul(til_new_cap, til_self->type_size));
        if (_status__tmp249 == 1) { *_err1 = _err0__tmp249; return 1; }
        til_new_ptr = _ret__tmp249;
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
        til_Str _tmp252;
        til_I64_OverflowError _err0__tmp253;
        til_IndexOutOfBoundsError _err1__tmp253;
        til_AllocError _err2__tmp253;
        til_Array _tmp254;
        til_AllocError _err_alloc__tmp255;
        til_IndexOutOfBoundsError _err_idx__tmp255;
        til_Str _tmp256 = ((til_Str){(til_I64)"Vec.get: index out of bounds", 28});
        int _arr_status__tmp255 = til_Array_new(&_tmp254, &_err_alloc__tmp255, "Str", 1);
        if (_arr_status__tmp255 != 0) {
        }
        _arr_status__tmp255 = til_Array_set(&_err_idx__tmp255, &_tmp254, 0, &_tmp256);
        if (_arr_status__tmp255 != 0) {
            *_err1 = _err_idx__tmp255; return 1;
        }
        int _status__tmp253 = til_format(&_tmp252, &_err0__tmp253, &_err1__tmp253, &_err2__tmp253, ((til_Str){(til_I64)"src/examples/hello_script.til:81:52:", 36}), &_tmp254);
        if (_status__tmp253 != 0) {
            if (_status__tmp253 == 2) { *_err1 = _err1__tmp253; return 1; }
        }
        til_Array_delete(&_tmp254);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp252);
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Vec_set(til_IndexOutOfBoundsError* _err1, til_Vec* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_gteq(til_index, til_self->_len).data) {
        til_Str _tmp259;
        til_I64_OverflowError _err0__tmp260;
        til_IndexOutOfBoundsError _err1__tmp260;
        til_AllocError _err2__tmp260;
        til_Array _tmp261;
        til_AllocError _err_alloc__tmp262;
        til_IndexOutOfBoundsError _err_idx__tmp262;
        til_Str _tmp263 = ((til_Str){(til_I64)"Vec.set: index out of bounds", 28});
        int _arr_status__tmp262 = til_Array_new(&_tmp261, &_err_alloc__tmp262, "Str", 1);
        if (_arr_status__tmp262 != 0) {
        }
        _arr_status__tmp262 = til_Array_set(&_err_idx__tmp262, &_tmp261, 0, &_tmp263);
        if (_arr_status__tmp262 != 0) {
            *_err1 = _err_idx__tmp262; return 1;
        }
        int _status__tmp260 = til_format(&_tmp259, &_err0__tmp260, &_err1__tmp260, &_err2__tmp260, ((til_Str){(til_I64)"src/examples/hello_script.til:96:52:", 36}), &_tmp261);
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

int til_Vec_pop(til_IndexOutOfBoundsError* _err1, til_Vec* til_self, til_Dynamic* til_dest) {
    if (til_I64_eq(til_self->_len, 0).data) {
        til_Str _tmp266;
        til_I64_OverflowError _err0__tmp267;
        til_IndexOutOfBoundsError _err1__tmp267;
        til_AllocError _err2__tmp267;
        til_Array _tmp268;
        til_AllocError _err_alloc__tmp269;
        til_IndexOutOfBoundsError _err_idx__tmp269;
        til_Str _tmp270 = ((til_Str){(til_I64)"Vec.pop: cannot pop from empty Vec", 34});
        int _arr_status__tmp269 = til_Array_new(&_tmp268, &_err_alloc__tmp269, "Str", 1);
        if (_arr_status__tmp269 != 0) {
        }
        _arr_status__tmp269 = til_Array_set(&_err_idx__tmp269, &_tmp268, 0, &_tmp270);
        if (_arr_status__tmp269 != 0) {
            *_err1 = _err_idx__tmp269; return 1;
        }
        int _status__tmp267 = til_format(&_tmp266, &_err0__tmp267, &_err1__tmp267, &_err2__tmp267, ((til_Str){(til_I64)"src/examples/hello_script.til:110:52:", 37}), &_tmp268);
        if (_status__tmp267 != 0) {
            if (_status__tmp267 == 2) { *_err1 = _err1__tmp267; return 1; }
        }
        til_Array_delete(&_tmp268);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp266);
        return 1;
    }
    til_I64 til_last_index = til_sub(til_self->_len, 1);
    til_IndexOutOfBoundsError _err0__tmp271 = {};
    int _status__tmp271 = til_Vec_get(&_err0__tmp271, (*til_self), til_last_index, (til_Dynamic*)&til_dest);
    if (_status__tmp271 == 1) { *_err1 = _err0__tmp271; return 1; }
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
    til_I64 _ret__tmp274;
    til_AllocError _err0__tmp274 = {};
    int _status__tmp274 = til_malloc(&_ret__tmp274, &_err0__tmp274, til_total_bytes);
    if (_status__tmp274 == 1) { *_err1 = _err0__tmp274; return 1; }
    til_cloned.ptr = _ret__tmp274;
    if (til_I64_eq(til_NULL, til_cloned.ptr).data) {
        til_Str _tmp276;
        til_I64_OverflowError _err0__tmp277;
        til_IndexOutOfBoundsError _err1__tmp277;
        til_AllocError _err2__tmp277;
        til_Array _tmp278;
        til_AllocError _err_alloc__tmp279;
        til_IndexOutOfBoundsError _err_idx__tmp279;
        til_Str _tmp280 = ((til_Str){(til_I64)"Vec.clone: malloc failed for ", 29});
        til_Str _tmp281 = til_I64_to_str(til_total_bytes);
        til_Str _tmp282 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp279 = til_Array_new(&_tmp278, &_err_alloc__tmp279, "Str", 3);
        if (_arr_status__tmp279 != 0) {
            *_err1 = _err_alloc__tmp279; return 1;
        }
        _arr_status__tmp279 = til_Array_set(&_err_idx__tmp279, &_tmp278, 0, &_tmp280);
        if (_arr_status__tmp279 != 0) {
        }
        _arr_status__tmp279 = til_Array_set(&_err_idx__tmp279, &_tmp278, 1, &_tmp281);
        if (_arr_status__tmp279 != 0) {
        }
        _arr_status__tmp279 = til_Array_set(&_err_idx__tmp279, &_tmp278, 2, &_tmp282);
        if (_arr_status__tmp279 != 0) {
        }
        int _status__tmp277 = til_format(&_tmp276, &_err0__tmp277, &_err1__tmp277, &_err2__tmp277, ((til_Str){(til_I64)"src/examples/hello_script.til:139:41:", 37}), &_tmp278);
        if (_status__tmp277 != 0) {
            if (_status__tmp277 == 3) { *_err1 = _err2__tmp277; return 1; }
        }
        til_Array_delete(&_tmp278);
        *_err1 = til_AllocError_new(_tmp276);
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
                til_Array _tmp287;
                til_AllocError _err_alloc__tmp288;
                til_IndexOutOfBoundsError _err_idx__tmp288;
                til_Str _tmp289 = ((til_Str){(til_I64)"Vec.extend: capacity exceeded Vec.MAX_CAP", 41});
                int _arr_status__tmp288 = til_Array_new(&_tmp287, &_err_alloc__tmp288, "Str", 1);
                if (_arr_status__tmp288 != 0) {
                    *_err1 = _err_alloc__tmp288; return 1;
                }
                _arr_status__tmp288 = til_Array_set(&_err_idx__tmp288, &_tmp287, 0, &_tmp289);
                if (_arr_status__tmp288 != 0) {
                }
                til_panic(((til_Str){(til_I64)"src/examples/hello_script.til:158:27:", 37}), &_tmp287);
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
        til_Str _tmp299;
        til_I64_OverflowError _err0__tmp300;
        til_IndexOutOfBoundsError _err1__tmp300;
        til_AllocError _err2__tmp300;
        til_Array _tmp301;
        til_AllocError _err_alloc__tmp302;
        til_IndexOutOfBoundsError _err_idx__tmp302;
        til_Str _tmp303 = ((til_Str){(til_I64)"Vec.remove: index out of bounds", 31});
        int _arr_status__tmp302 = til_Array_new(&_tmp301, &_err_alloc__tmp302, "Str", 1);
        if (_arr_status__tmp302 != 0) {
        }
        _arr_status__tmp302 = til_Array_set(&_err_idx__tmp302, &_tmp301, 0, &_tmp303);
        if (_arr_status__tmp302 != 0) {
            *_err1 = _err_idx__tmp302; return 1;
        }
        int _status__tmp300 = til_format(&_tmp299, &_err0__tmp300, &_err1__tmp300, &_err2__tmp300, ((til_Str){(til_I64)"src/examples/hello_script.til:202:52:", 37}), &_tmp301);
        if (_status__tmp300 != 0) {
            if (_status__tmp300 == 2) { *_err1 = _err1__tmp300; return 1; }
        }
        til_Array_delete(&_tmp301);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp299);
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
    til_I64 _ret__tmp313;
    til_AllocError _err0__tmp313 = {};
    int _status__tmp313 = til_malloc(&_ret__tmp313, &_err0__tmp313, til_cloned.cap);
    if (_status__tmp313 == 1) { *_err1 = _err0__tmp313; return 1; }
    til_cloned.c_string = _ret__tmp313;
    if (til_I64_eq(til_NULL, til_cloned.c_string).data) {
        til_Str _tmp315;
        til_I64_OverflowError _err0__tmp316;
        til_IndexOutOfBoundsError _err1__tmp316;
        til_AllocError _err2__tmp316;
        til_Array _tmp317;
        til_AllocError _err_alloc__tmp318;
        til_IndexOutOfBoundsError _err_idx__tmp318;
        til_Str _tmp319 = ((til_Str){(til_I64)"Str.clone: malloc failed for ", 29});
        til_Str _tmp320 = til_I64_to_str(til_cloned.cap);
        til_Str _tmp321 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp318 = til_Array_new(&_tmp317, &_err_alloc__tmp318, "Str", 3);
        if (_arr_status__tmp318 != 0) {
            *_err1 = _err_alloc__tmp318; return 1;
        }
        _arr_status__tmp318 = til_Array_set(&_err_idx__tmp318, &_tmp317, 0, &_tmp319);
        if (_arr_status__tmp318 != 0) {
        }
        _arr_status__tmp318 = til_Array_set(&_err_idx__tmp318, &_tmp317, 1, &_tmp320);
        if (_arr_status__tmp318 != 0) {
        }
        _arr_status__tmp318 = til_Array_set(&_err_idx__tmp318, &_tmp317, 2, &_tmp321);
        if (_arr_status__tmp318 != 0) {
        }
        int _status__tmp316 = til_format(&_tmp315, &_err0__tmp316, &_err1__tmp316, &_err2__tmp316, ((til_Str){(til_I64)"src/examples/hello_script.til:46:41:", 36}), &_tmp317);
        if (_status__tmp316 != 0) {
            if (_status__tmp316 == 3) { *_err1 = _err2__tmp316; return 1; }
        }
        til_Array_delete(&_tmp317);
        *_err1 = til_AllocError_new(_tmp315);
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
        til_Str _ret__tmp358;
        til_AllocError _err0__tmp358 = {};
        int _status__tmp358 = til_Str_clone(&_ret__tmp358, &_err0__tmp358, til_self);
        if (_status__tmp358 == 1) { *_err1 = _err0__tmp358; return 1; }
        *_ret = _ret__tmp358;
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
        til_Str _ret__tmp366;
        til_AllocError _err0__tmp366 = {};
        int _status__tmp366 = til_Str_clone(&_ret__tmp366, &_err0__tmp366, til_self);
        if (_status__tmp366 == 1) { *_err1 = _err0__tmp366; return 1; }
        *_ret = _ret__tmp366;
        return 0;
    }
    til_I64 til_new_len = til_add(til_sub(til_Str_len(til_self), til_mul(til_count, til_Str_len(til_from))), til_mul(til_count, til_Str_len(til_to)));
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_new_len;
    til_I64 _ret__tmp367;
    til_AllocError _err0__tmp367 = {};
    int _status__tmp367 = til_malloc(&_ret__tmp367, &_err0__tmp367, til_new_len);
    if (_status__tmp367 == 1) { *_err1 = _err0__tmp367; return 1; }
    til_result.c_string = _ret__tmp367;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Str _tmp369;
        til_I64_OverflowError _err0__tmp370;
        til_IndexOutOfBoundsError _err1__tmp370;
        til_AllocError _err2__tmp370;
        til_Array _tmp371;
        til_AllocError _err_alloc__tmp372;
        til_IndexOutOfBoundsError _err_idx__tmp372;
        til_Str _tmp373 = ((til_Str){(til_I64)"Str.replace: malloc failed for ", 31});
        til_Str _tmp374 = til_I64_to_str(til_new_len);
        til_Str _tmp375 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp372 = til_Array_new(&_tmp371, &_err_alloc__tmp372, "Str", 3);
        if (_arr_status__tmp372 != 0) {
            *_err1 = _err_alloc__tmp372; return 1;
        }
        _arr_status__tmp372 = til_Array_set(&_err_idx__tmp372, &_tmp371, 0, &_tmp373);
        if (_arr_status__tmp372 != 0) {
        }
        _arr_status__tmp372 = til_Array_set(&_err_idx__tmp372, &_tmp371, 1, &_tmp374);
        if (_arr_status__tmp372 != 0) {
        }
        _arr_status__tmp372 = til_Array_set(&_err_idx__tmp372, &_tmp371, 2, &_tmp375);
        if (_arr_status__tmp372 != 0) {
        }
        int _status__tmp370 = til_format(&_tmp369, &_err0__tmp370, &_err1__tmp370, &_err2__tmp370, ((til_Str){(til_I64)"src/examples/hello_script.til:213:41:", 37}), &_tmp371);
        if (_status__tmp370 != 0) {
            if (_status__tmp370 == 3) { *_err1 = _err2__tmp370; return 1; }
        }
        til_Array_delete(&_tmp371);
        *_err1 = til_AllocError_new(_tmp369);
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
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp387;
    if (til_I64_eq(til_Str_len(til_from), 0).data) {
        til_Str _ret__tmp389;
        til_AllocError _err0__tmp389 = {};
        int _status__tmp389 = til_Str_clone(&_ret__tmp389, &_err0__tmp389, til_self);
        if (_status__tmp389 == 1) { *_err1 = _err0__tmp389; return 1; }
        *_ret = _ret__tmp389;
        return 0;
    }
    if (til_I64_eq(til_n, 0).data) {
        til_Str _ret__tmp391;
        til_AllocError _err0__tmp391 = {};
        int _status__tmp391 = til_Str_clone(&_ret__tmp391, &_err0__tmp391, til_self);
        if (_status__tmp391 == 1) { *_err1 = _err0__tmp391; return 1; }
        *_ret = _ret__tmp391;
        return 0;
    }
    til_I64 til_idx = til_Str_find(til_self, til_from);
    if (til_lt(til_idx, 0).data) {
        til_Str _ret__tmp393;
        til_AllocError _err0__tmp393 = {};
        int _status__tmp393 = til_Str_clone(&_ret__tmp393, &_err0__tmp393, til_self);
        if (_status__tmp393 == 1) { *_err1 = _err0__tmp393; return 1; }
        *_ret = _ret__tmp393;
        return 0;
    }
    til_Str _ret__tmp394;
    til_Str til_prefix;
    til_IndexOutOfBoundsError _err0__tmp394 = {};
    til_AllocError _err1__tmp394 = {};
    int _status__tmp394 = til_get_substr(&_ret__tmp394, &_err0__tmp394, &_err1__tmp394, til_self, 0, til_idx);
    if (_status__tmp394 == 2) { *_err1 = _err1__tmp394; return 1; }
    til_prefix = _ret__tmp394;
    til_Str _ret__tmp395;
    til_Str til_suffix;
    til_IndexOutOfBoundsError _err0__tmp395 = {};
    til_AllocError _err1__tmp395 = {};
    int _status__tmp395 = til_get_substr(&_ret__tmp395, &_err0__tmp395, &_err1__tmp395, til_self, til_add(til_idx, til_Str_len(til_from)), til_Str_len(til_self));
    if (_status__tmp395 == 2) { *_err1 = _err1__tmp395; return 1; }
    til_suffix = _ret__tmp395;
    til_Str til_result = til_concat(til_concat(til_prefix, til_to), til_suffix);
    if (til_gt(til_n, 1).data) {
        til_Str _ret__tmp397;
        til_Str til_rest;
        til_AllocError _err0__tmp397 = {};
        int _status__tmp397 = til_Str_replacen(&_ret__tmp397, &_err0__tmp397, til_suffix, til_from, til_to, til_sub(til_n, 1));
        if (_status__tmp397 == 1) { *_err1 = _err0__tmp397; return 1; }
        til_rest = _ret__tmp397;
        til_result = til_concat(til_concat(til_prefix, til_to), til_rest);
    }
    *_ret = til_result;
    return 0;
    goto _end_catches__tmp387;
_catch_IndexOutOfBoundsError__tmp387: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp387;
    til_Str _ret__tmp399;
    til_AllocError _err0__tmp399 = {};
    int _status__tmp399 = til_Str_clone(&_ret__tmp399, &_err0__tmp399, til_self);
    if (_status__tmp399 == 1) { *_err1 = _err0__tmp399; return 1; }
    til_result = _ret__tmp399;
    }
_end_catches__tmp387:;
}

int til_Str_split(til_Vec* _ret, til_AllocError* _err1, til_IndexOutOfBoundsError* _err2, const til_Str til_self, const til_Str til_delimiter) {
    til_Vec _ret__tmp401;
    til_Vec til_parts;
    til_AllocError _err0__tmp401 = {};
    int _status__tmp401 = til_Vec_new(&_ret__tmp401, &_err0__tmp401, "Str");
    if (_status__tmp401 == 1) { *_err1 = _err0__tmp401; return 1; }
    til_parts = _ret__tmp401;
    if (til_I64_eq(til_Str_len(til_delimiter), 0).data) {
        til_Str _tmp404;
        til_AllocError _err0__tmp405;
        int _status__tmp405 = til_Str_clone(&_tmp404, &_err0__tmp405, til_self);
        if (_status__tmp405 != 0) {
            if (_status__tmp405 == 1) { *_err1 = _err0__tmp405; return 1; }
        }
        til_AllocError _err0__tmp403 = {};
        int _status__tmp403 = til_Vec_push(&_err0__tmp403, &til_parts, &_tmp404);
        if (_status__tmp403 == 1) { *_err1 = _err0__tmp403; return 1; }
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
                til_Str _ret__tmp412;
                til_Str til_part;
                til_IndexOutOfBoundsError _err0__tmp412 = {};
                til_AllocError _err1__tmp412 = {};
                int _status__tmp412 = til_get_substr(&_ret__tmp412, &_err0__tmp412, &_err1__tmp412, til_self, til_start, til_pos);
                if (_status__tmp412 == 1) { *_err2 = _err0__tmp412; return 2; }
                if (_status__tmp412 == 2) { *_err1 = _err1__tmp412; return 1; }
                til_part = _ret__tmp412;
                til_AllocError _err0__tmp413 = {};
                int _status__tmp413 = til_Vec_push(&_err0__tmp413, &til_parts, (til_Dynamic*)&til_part);
                if (_status__tmp413 == 1) { *_err1 = _err0__tmp413; return 1; }
            } else {
                til_Str _tmp416 = ((til_Str){(til_I64)"", 0});
                til_AllocError _err0__tmp415 = {};
                int _status__tmp415 = til_Vec_push(&_err0__tmp415, &til_parts, &_tmp416);
                if (_status__tmp415 == 1) { *_err1 = _err0__tmp415; return 1; }
            }
            til_start = til_add(til_pos, til_Str_len(til_delimiter));
            til_pos = til_start;
        } else {
            til_pos = til_add(til_pos, 1);
        }
    }
    if (til_lt(til_start, til_Str_len(til_self)).data) {
        til_Str _ret__tmp419;
        til_Str til_part;
        til_IndexOutOfBoundsError _err0__tmp419 = {};
        til_AllocError _err1__tmp419 = {};
        int _status__tmp419 = til_get_substr(&_ret__tmp419, &_err0__tmp419, &_err1__tmp419, til_self, til_start, til_Str_len(til_self));
        if (_status__tmp419 == 1) { *_err2 = _err0__tmp419; return 2; }
        if (_status__tmp419 == 2) { *_err1 = _err1__tmp419; return 1; }
        til_part = _ret__tmp419;
        til_AllocError _err0__tmp420 = {};
        int _status__tmp420 = til_Vec_push(&_err0__tmp420, &til_parts, (til_Dynamic*)&til_part);
        if (_status__tmp420 == 1) { *_err1 = _err0__tmp420; return 1; }
    } else {
        if (til_I64_eq(til_start, til_Str_len(til_self)).data) {
            til_Str _tmp424 = ((til_Str){(til_I64)"", 0});
            til_AllocError _err0__tmp423 = {};
            int _status__tmp423 = til_Vec_push(&_err0__tmp423, &til_parts, &_tmp424);
            if (_status__tmp423 == 1) { *_err1 = _err0__tmp423; return 1; }
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
    til_U8 _ret__tmp432;
    til_U8_OverflowError _err0__tmp432 = {};
    int _status__tmp432 = til_U8_from_i64(&_ret__tmp432, &_err0__tmp432, til_add(til_U8_to_i64(til_a), til_U8_to_i64(til_b)));
    if (_status__tmp432 == 1) { *_err1 = _err0__tmp432; return 1; }
    *_ret = _ret__tmp432;
    return 0;
}

int til_U8_from_i64(til_U8* _ret, til_U8_OverflowError* _err1, const til_I64 til_self) {
    if (til_lt(til_self, 0).data) {
        til_Str _tmp435;
        til_I64_OverflowError _err0__tmp436;
        til_IndexOutOfBoundsError _err1__tmp436;
        til_AllocError _err2__tmp436;
        til_Array _tmp437;
        til_AllocError _err_alloc__tmp438;
        til_IndexOutOfBoundsError _err_idx__tmp438;
        til_Str _tmp439 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        int _arr_status__tmp438 = til_Array_new(&_tmp437, &_err_alloc__tmp438, "Str", 1);
        if (_arr_status__tmp438 != 0) {
        }
        _arr_status__tmp438 = til_Array_set(&_err_idx__tmp438, &_tmp437, 0, &_tmp439);
        if (_arr_status__tmp438 != 0) {
        }
        int _status__tmp436 = til_format(&_tmp435, &_err0__tmp436, &_err1__tmp436, &_err2__tmp436, ((til_Str){(til_I64)"src/examples/hello_script.til:56:47:", 36}), &_tmp437);
        if (_status__tmp436 != 0) {
        }
        til_Array_delete(&_tmp437);
        *_err1 = til_U8_OverflowError_new(_tmp435);
        return 1;
    }
    if (til_gt(til_self, til_MAX_U8).data) {
        til_Str _tmp441;
        til_I64_OverflowError _err0__tmp442;
        til_IndexOutOfBoundsError _err1__tmp442;
        til_AllocError _err2__tmp442;
        til_Array _tmp443;
        til_AllocError _err_alloc__tmp444;
        til_IndexOutOfBoundsError _err_idx__tmp444;
        til_Str _tmp445 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp446 = til_I64_to_str(til_MAX_U8);
        int _arr_status__tmp444 = til_Array_new(&_tmp443, &_err_alloc__tmp444, "Str", 2);
        if (_arr_status__tmp444 != 0) {
        }
        _arr_status__tmp444 = til_Array_set(&_err_idx__tmp444, &_tmp443, 0, &_tmp445);
        if (_arr_status__tmp444 != 0) {
        }
        _arr_status__tmp444 = til_Array_set(&_err_idx__tmp444, &_tmp443, 1, &_tmp446);
        if (_arr_status__tmp444 != 0) {
        }
        int _status__tmp442 = til_format(&_tmp441, &_err0__tmp442, &_err1__tmp442, &_err2__tmp442, ((til_Str){(til_I64)"src/examples/hello_script.til:59:47:", 36}), &_tmp443);
        if (_status__tmp442 != 0) {
        }
        til_Array_delete(&_tmp443);
        *_err1 = til_U8_OverflowError_new(_tmp441);
        return 1;
    }
    *_ret = til_i64_to_u8(til_self);
    return 0;
}

til_Str til_U8_to_str(const til_U8 til_self) {
    return til_I64_to_str(til_U8_to_i64(til_self));
}

int til_U8_from_str(til_U8* _ret, til_U8_OverflowError* _err1, const til_Str til_s) {
    til_U8 _ret__tmp449;
    til_U8_OverflowError _err0__tmp449 = {};
    int _status__tmp449 = til_U8_from_i64(&_ret__tmp449, &_err0__tmp449, til_I64_from_str(til_s));
    if (_status__tmp449 == 1) { *_err1 = _err0__tmp449; return 1; }
    *_ret = _ret__tmp449;
    return 0;
}

til_I64 til_U8_size(void) {
    return 1;
}

int main() {
    til_Array _tmp452;
    til_AllocError _err_alloc__tmp453;
    til_IndexOutOfBoundsError _err_idx__tmp453;
    til_Str _tmp454 = ((til_Str){(til_I64)"Hello World!", 12});
    int _arr_status__tmp453 = til_Array_new(&_tmp452, &_err_alloc__tmp453, "Str", 1);
    if (_arr_status__tmp453 != 0) {
    }
    _arr_status__tmp453 = til_Array_set(&_err_idx__tmp453, &_tmp452, 0, &_tmp454);
    if (_arr_status__tmp453 != 0) {
    }
    til_println(&_tmp452);
    til_Array_delete(&_tmp452);
    return 0;
}
