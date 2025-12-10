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
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Bool til_val = false;
        til_IndexOutOfBoundsError _err0__tmp0 = {};
        int _status__tmp0 = til_Array_get(&_err0__tmp0, (*til_args), til_i, (til_Dynamic*)&til_val);
        if (til_val.data) {
            return true;
        }
        til_I64_inc(&til_i);
    }
    return false;
}

til_Bool til_and(til_Array* til_args) {
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Bool til_val = false;
        til_IndexOutOfBoundsError _err0__tmp1 = {};
        int _status__tmp1 = til_Array_get(&_err0__tmp1, (*til_args), til_i, (til_Dynamic*)&til_val);
        if (til_not(til_val).data) {
            return false;
        }
        til_I64_inc(&til_i);
    }
    return true;
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
    til_single_print(til_loc_str);
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_msgs))).data) {
        til_Str til_val = til_Str_from_literal("");
        til_IndexOutOfBoundsError _err0__tmp2 = {};
        int _status__tmp2 = til_Array_get(&_err0__tmp2, (*til_msgs), til_i, (til_Dynamic*)&til_val);
        til_single_print(til_val);
        til_I64_inc(&til_i);
    }
    til_single_print(til_Str_from_literal("\n"));
    til_print_flush();
    til_exit(1);
}

void til_assertm(const til_Str til_loc_str, const til_Bool til_cond, const til_Str til_msg) {
    if (til_not(til_cond).data) {
        til_Str _tmp3;
        til_I64_OverflowError _err0__tmp4;
        til_IndexOutOfBoundsError _err1__tmp4;
        til_AllocError _err2__tmp4;
        til_Array _tmp5;
        til_AllocError _err_alloc__tmp6;
        til_IndexOutOfBoundsError _err_idx__tmp6;
        til_Str _tmp7 = til_msg;
        int _arr_status__tmp6 = til_Array_new(&_tmp5, &_err_alloc__tmp6, "Str", 1);
        if (_arr_status__tmp6 != 0) {
        }
        _arr_status__tmp6 = til_Array_set(&_err_idx__tmp6, &_tmp5, 0, &_tmp7);
        if (_arr_status__tmp6 != 0) {
        }
        int _status__tmp4 = til_format(&_tmp3, &_err0__tmp4, &_err1__tmp4, &_err2__tmp4, til_Str_from_literal("assert failed: "), &_tmp5);
        if (_status__tmp4 != 0) {
        }
        til_Array_delete(&_tmp5);
                til_Array _tmp8;
        til_AllocError _err_alloc__tmp9;
        til_IndexOutOfBoundsError _err_idx__tmp9;
        int _arr_status__tmp9 = til_Array_new(&_tmp8, &_err_alloc__tmp9, "Str", 1);
        if (_arr_status__tmp9 != 0) {
        }
        _arr_status__tmp9 = til_Array_set(&_err_idx__tmp9, &_tmp8, 0, &_tmp3);
        if (_arr_status__tmp9 != 0) {
        }
til_panic(til_loc_str, &_tmp8);
        til_Array_delete(&_tmp8);
    }
}

void til_assert(const til_Str til_loc_str, const til_Bool til_cond) {
    til_assertm(til_loc_str, til_cond, til_Str_from_literal(""));
}

void til_TODO(const til_Str til_loc_str, const til_Str til_msg) {
    til_Str _tmp10;
    til_I64_OverflowError _err0__tmp11;
    til_IndexOutOfBoundsError _err1__tmp11;
    til_AllocError _err2__tmp11;
    til_Array _tmp12;
    til_AllocError _err_alloc__tmp13;
    til_IndexOutOfBoundsError _err_idx__tmp13;
    til_Str _tmp14 = til_msg;
    int _arr_status__tmp13 = til_Array_new(&_tmp12, &_err_alloc__tmp13, "Str", 1);
    if (_arr_status__tmp13 != 0) {
    }
    _arr_status__tmp13 = til_Array_set(&_err_idx__tmp13, &_tmp12, 0, &_tmp14);
    if (_arr_status__tmp13 != 0) {
    }
    int _status__tmp11 = til_format(&_tmp10, &_err0__tmp11, &_err1__tmp11, &_err2__tmp11, til_Str_from_literal("TODO: "), &_tmp12);
    if (_status__tmp11 != 0) {
    }
    til_Array_delete(&_tmp12);
    til_assertm(til_loc_str, false, _tmp10);
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
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Str til_val = til_Str_from_literal("");
        til_IndexOutOfBoundsError _err0__tmp15 = {};
        int _status__tmp15 = til_Array_get(&_err0__tmp15, (*til_args), til_i, (til_Dynamic*)&til_val);
        til_single_print(til_val);
        til_I64_inc(&til_i);
    }
    til_print_flush();
}

void til_println(til_Array* til_args) {
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Str til_val = til_Str_from_literal("");
        til_IndexOutOfBoundsError _err0__tmp16 = {};
        int _status__tmp16 = til_Array_get(&_err0__tmp16, (*til_args), til_i, (til_Dynamic*)&til_val);
        til_single_print(til_val);
        til_I64_inc(&til_i);
    }
    til_single_print(til_Str_from_literal("\n"));
    til_print_flush();
}

int til_get_substr(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_start, const til_I64 til_end) {
    if (til_lt(til_start, 0).data) {
        til_Str _tmp17;
        til_I64_OverflowError _err0__tmp18;
        til_IndexOutOfBoundsError _err1__tmp18;
        til_AllocError _err2__tmp18;
        til_Array _tmp19;
        til_AllocError _err_alloc__tmp20;
        til_IndexOutOfBoundsError _err_idx__tmp20;
        til_Str _tmp21 = til_Str_from_literal("get_substr: start index ");
        til_Str _tmp22 = til_I64_to_str(til_start);
        til_Str _tmp23 = til_Str_from_literal(" cannot be negative");
        int _arr_status__tmp20 = til_Array_new(&_tmp19, &_err_alloc__tmp20, "Str", 3);
        if (_arr_status__tmp20 != 0) {
            *_err2 = _err_alloc__tmp20; return 2;
        }
        _arr_status__tmp20 = til_Array_set(&_err_idx__tmp20, &_tmp19, 0, &_tmp21);
        if (_arr_status__tmp20 != 0) {
            *_err1 = _err_idx__tmp20; return 1;
        }
        _arr_status__tmp20 = til_Array_set(&_err_idx__tmp20, &_tmp19, 1, &_tmp22);
        if (_arr_status__tmp20 != 0) {
            *_err1 = _err_idx__tmp20; return 1;
        }
        _arr_status__tmp20 = til_Array_set(&_err_idx__tmp20, &_tmp19, 2, &_tmp23);
        if (_arr_status__tmp20 != 0) {
            *_err1 = _err_idx__tmp20; return 1;
        }
        int _status__tmp18 = til_format(&_tmp17, &_err0__tmp18, &_err1__tmp18, &_err2__tmp18, til_Str_from_literal(""), &_tmp19);
        if (_status__tmp18 != 0) {
            if (_status__tmp18 == 2) { *_err1 = _err1__tmp18; return 1; }
            if (_status__tmp18 == 3) { *_err2 = _err2__tmp18; return 2; }
        }
        til_Array_delete(&_tmp19);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp17);
        return 1;
    }
    if (til_lt(til_end, 0).data) {
        til_Str _tmp24;
        til_I64_OverflowError _err0__tmp25;
        til_IndexOutOfBoundsError _err1__tmp25;
        til_AllocError _err2__tmp25;
        til_Array _tmp26;
        til_AllocError _err_alloc__tmp27;
        til_IndexOutOfBoundsError _err_idx__tmp27;
        til_Str _tmp28 = til_Str_from_literal("get_substr: end index ");
        til_Str _tmp29 = til_I64_to_str(til_end);
        til_Str _tmp30 = til_Str_from_literal(" cannot be negative");
        int _arr_status__tmp27 = til_Array_new(&_tmp26, &_err_alloc__tmp27, "Str", 3);
        if (_arr_status__tmp27 != 0) {
            *_err2 = _err_alloc__tmp27; return 2;
        }
        _arr_status__tmp27 = til_Array_set(&_err_idx__tmp27, &_tmp26, 0, &_tmp28);
        if (_arr_status__tmp27 != 0) {
            *_err1 = _err_idx__tmp27; return 1;
        }
        _arr_status__tmp27 = til_Array_set(&_err_idx__tmp27, &_tmp26, 1, &_tmp29);
        if (_arr_status__tmp27 != 0) {
            *_err1 = _err_idx__tmp27; return 1;
        }
        _arr_status__tmp27 = til_Array_set(&_err_idx__tmp27, &_tmp26, 2, &_tmp30);
        if (_arr_status__tmp27 != 0) {
            *_err1 = _err_idx__tmp27; return 1;
        }
        int _status__tmp25 = til_format(&_tmp24, &_err0__tmp25, &_err1__tmp25, &_err2__tmp25, til_Str_from_literal(""), &_tmp26);
        if (_status__tmp25 != 0) {
            if (_status__tmp25 == 2) { *_err1 = _err1__tmp25; return 1; }
            if (_status__tmp25 == 3) { *_err2 = _err2__tmp25; return 2; }
        }
        til_Array_delete(&_tmp26);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp24);
        return 1;
    }
    if (til_gt(til_start, til_end).data) {
        til_Str _tmp31;
        til_I64_OverflowError _err0__tmp32;
        til_IndexOutOfBoundsError _err1__tmp32;
        til_AllocError _err2__tmp32;
        til_Array _tmp33;
        til_AllocError _err_alloc__tmp34;
        til_IndexOutOfBoundsError _err_idx__tmp34;
        til_Str _tmp35 = til_Str_from_literal("get_substr: start index ");
        til_Str _tmp36 = til_I64_to_str(til_start);
        til_Str _tmp37 = til_Str_from_literal(" is greater than end index ");
        til_Str _tmp38 = til_I64_to_str(til_end);
        int _arr_status__tmp34 = til_Array_new(&_tmp33, &_err_alloc__tmp34, "Str", 4);
        if (_arr_status__tmp34 != 0) {
            *_err2 = _err_alloc__tmp34; return 2;
        }
        _arr_status__tmp34 = til_Array_set(&_err_idx__tmp34, &_tmp33, 0, &_tmp35);
        if (_arr_status__tmp34 != 0) {
            *_err1 = _err_idx__tmp34; return 1;
        }
        _arr_status__tmp34 = til_Array_set(&_err_idx__tmp34, &_tmp33, 1, &_tmp36);
        if (_arr_status__tmp34 != 0) {
            *_err1 = _err_idx__tmp34; return 1;
        }
        _arr_status__tmp34 = til_Array_set(&_err_idx__tmp34, &_tmp33, 2, &_tmp37);
        if (_arr_status__tmp34 != 0) {
            *_err1 = _err_idx__tmp34; return 1;
        }
        _arr_status__tmp34 = til_Array_set(&_err_idx__tmp34, &_tmp33, 3, &_tmp38);
        if (_arr_status__tmp34 != 0) {
            *_err1 = _err_idx__tmp34; return 1;
        }
        int _status__tmp32 = til_format(&_tmp31, &_err0__tmp32, &_err1__tmp32, &_err2__tmp32, til_Str_from_literal(""), &_tmp33);
        if (_status__tmp32 != 0) {
            if (_status__tmp32 == 2) { *_err1 = _err1__tmp32; return 1; }
            if (_status__tmp32 == 3) { *_err2 = _err2__tmp32; return 2; }
        }
        til_Array_delete(&_tmp33);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp31);
        return 1;
    }
    if (til_gt(til_end, til_Str_len(til_s)).data) {
        til_Str _tmp39;
        til_I64_OverflowError _err0__tmp40;
        til_IndexOutOfBoundsError _err1__tmp40;
        til_AllocError _err2__tmp40;
        til_Array _tmp41;
        til_AllocError _err_alloc__tmp42;
        til_IndexOutOfBoundsError _err_idx__tmp42;
        til_Str _tmp43 = til_Str_from_literal("get_substr: end index ");
        til_Str _tmp44 = til_I64_to_str(til_end);
        til_Str _tmp45 = til_Str_from_literal(" is greater than string length ");
        til_Str _tmp46 = til_I64_to_str(til_Str_len(til_s));
        int _arr_status__tmp42 = til_Array_new(&_tmp41, &_err_alloc__tmp42, "Str", 4);
        if (_arr_status__tmp42 != 0) {
            *_err2 = _err_alloc__tmp42; return 2;
        }
        _arr_status__tmp42 = til_Array_set(&_err_idx__tmp42, &_tmp41, 0, &_tmp43);
        if (_arr_status__tmp42 != 0) {
            *_err1 = _err_idx__tmp42; return 1;
        }
        _arr_status__tmp42 = til_Array_set(&_err_idx__tmp42, &_tmp41, 1, &_tmp44);
        if (_arr_status__tmp42 != 0) {
            *_err1 = _err_idx__tmp42; return 1;
        }
        _arr_status__tmp42 = til_Array_set(&_err_idx__tmp42, &_tmp41, 2, &_tmp45);
        if (_arr_status__tmp42 != 0) {
            *_err1 = _err_idx__tmp42; return 1;
        }
        _arr_status__tmp42 = til_Array_set(&_err_idx__tmp42, &_tmp41, 3, &_tmp46);
        if (_arr_status__tmp42 != 0) {
            *_err1 = _err_idx__tmp42; return 1;
        }
        int _status__tmp40 = til_format(&_tmp39, &_err0__tmp40, &_err1__tmp40, &_err2__tmp40, til_Str_from_literal(""), &_tmp41);
        if (_status__tmp40 != 0) {
            if (_status__tmp40 == 2) { *_err1 = _err1__tmp40; return 1; }
            if (_status__tmp40 == 3) { *_err2 = _err2__tmp40; return 2; }
        }
        til_Array_delete(&_tmp41);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp39);
        return 1;
    }
    if (til_I64_eq(til_start, til_end).data) {
        til_Str _tmp47;
        til_I64_OverflowError _err0__tmp48;
        til_IndexOutOfBoundsError _err1__tmp48;
        til_AllocError _err2__tmp48;
        til_Array _tmp49;
        til_AllocError _err_alloc__tmp50;
        til_IndexOutOfBoundsError _err_idx__tmp50;
        til_Str _tmp51 = til_Str_from_literal("get_substr: start and end are the same (");
        til_Str _tmp52 = til_I64_to_str(til_start);
        til_Str _tmp53 = til_Str_from_literal("), no substring");
        int _arr_status__tmp50 = til_Array_new(&_tmp49, &_err_alloc__tmp50, "Str", 3);
        if (_arr_status__tmp50 != 0) {
            *_err2 = _err_alloc__tmp50; return 2;
        }
        _arr_status__tmp50 = til_Array_set(&_err_idx__tmp50, &_tmp49, 0, &_tmp51);
        if (_arr_status__tmp50 != 0) {
            *_err1 = _err_idx__tmp50; return 1;
        }
        _arr_status__tmp50 = til_Array_set(&_err_idx__tmp50, &_tmp49, 1, &_tmp52);
        if (_arr_status__tmp50 != 0) {
            *_err1 = _err_idx__tmp50; return 1;
        }
        _arr_status__tmp50 = til_Array_set(&_err_idx__tmp50, &_tmp49, 2, &_tmp53);
        if (_arr_status__tmp50 != 0) {
            *_err1 = _err_idx__tmp50; return 1;
        }
        int _status__tmp48 = til_format(&_tmp47, &_err0__tmp48, &_err1__tmp48, &_err2__tmp48, til_Str_from_literal(""), &_tmp49);
        if (_status__tmp48 != 0) {
            if (_status__tmp48 == 2) { *_err1 = _err1__tmp48; return 1; }
            if (_status__tmp48 == 3) { *_err2 = _err2__tmp48; return 2; }
        }
        til_Array_delete(&_tmp49);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp47);
        return 1;
    }
    til_Str til_substr = {0};
    til_substr.cap = til_sub(til_end, til_start);
    til_I64 _ret__tmp54;
    til_AllocError _err0__tmp54 = {};
    int _status__tmp54 = til_malloc(&_ret__tmp54, &_err0__tmp54, til_substr.cap);
    if (_status__tmp54 == 1) { *_err2 = _err0__tmp54; return 2; }
    til_substr.c_string = _ret__tmp54;
    if (til_I64_eq(til_NULL, til_substr.c_string).data) {
        til_Str _tmp55;
        til_I64_OverflowError _err0__tmp56;
        til_IndexOutOfBoundsError _err1__tmp56;
        til_AllocError _err2__tmp56;
        til_Array _tmp57;
        til_AllocError _err_alloc__tmp58;
        til_IndexOutOfBoundsError _err_idx__tmp58;
        til_Str _tmp59 = til_Str_from_literal("Str.get_substr: failed to allocate ");
        til_Str _tmp60 = til_I64_to_str(til_substr.cap);
        til_Str _tmp61 = til_Str_from_literal(" bytes");
        int _arr_status__tmp58 = til_Array_new(&_tmp57, &_err_alloc__tmp58, "Str", 3);
        if (_arr_status__tmp58 != 0) {
            *_err2 = _err_alloc__tmp58; return 2;
        }
        _arr_status__tmp58 = til_Array_set(&_err_idx__tmp58, &_tmp57, 0, &_tmp59);
        if (_arr_status__tmp58 != 0) {
            *_err1 = _err_idx__tmp58; return 1;
        }
        _arr_status__tmp58 = til_Array_set(&_err_idx__tmp58, &_tmp57, 1, &_tmp60);
        if (_arr_status__tmp58 != 0) {
            *_err1 = _err_idx__tmp58; return 1;
        }
        _arr_status__tmp58 = til_Array_set(&_err_idx__tmp58, &_tmp57, 2, &_tmp61);
        if (_arr_status__tmp58 != 0) {
            *_err1 = _err_idx__tmp58; return 1;
        }
        int _status__tmp56 = til_format(&_tmp55, &_err0__tmp56, &_err1__tmp56, &_err2__tmp56, til_Str_from_literal(""), &_tmp57);
        if (_status__tmp56 != 0) {
            if (_status__tmp56 == 2) { *_err1 = _err1__tmp56; return 1; }
            if (_status__tmp56 == 3) { *_err2 = _err2__tmp56; return 2; }
        }
        til_Array_delete(&_tmp57);
        *_err2 = til_AllocError_new(_tmp55);
        return 2;
    }
    til_memcpy(til_substr.c_string, til_add(til_s.c_string, til_start), til_substr.cap);
    *_ret = til_substr;
    return 0;
}

int til_get_char(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_pos) {
    til_Str _ret__tmp62;
    til_IndexOutOfBoundsError _err0__tmp62 = {};
    til_AllocError _err1__tmp62 = {};
    int _status__tmp62 = til_get_substr(&_ret__tmp62, &_err0__tmp62, &_err1__tmp62, til_s, til_pos, til_add(til_pos, 1));
    if (_status__tmp62 == 1) { *_err1 = _err0__tmp62; return 1; }
    if (_status__tmp62 == 2) { *_err2 = _err1__tmp62; return 2; }
    *_ret = _ret__tmp62;
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
    til_Str til_result = {0};
    til_result.cap = til_add(til_a.cap, til_b.cap);
    if (til_lt(til_result.cap, til_a.cap).data) {
                til_Array _tmp63;
        til_AllocError _err_alloc__tmp64;
        til_IndexOutOfBoundsError _err_idx__tmp64;
        til_Str _tmp65 = til_Str_from_literal("concat: integer overflow");
        int _arr_status__tmp64 = til_Array_new(&_tmp63, &_err_alloc__tmp64, "Str", 1);
        if (_arr_status__tmp64 != 0) {
        }
        _arr_status__tmp64 = til_Array_set(&_err_idx__tmp64, &_tmp63, 0, &_tmp65);
        if (_arr_status__tmp64 != 0) {
        }
til_panic(til_Str_from_literal(""), &_tmp63);
        til_Array_delete(&_tmp63);
    }
    til_I64 _ret__tmp66;
    til_AllocError _err0__tmp66 = {};
    int _status__tmp66 = til_malloc(&_ret__tmp66, &_err0__tmp66, til_result.cap);
    if (_status__tmp66 == 0) {
        til_result.c_string = _ret__tmp66;
    } else if (_status__tmp66 == 1) {
        til_AllocError til_err = _err0__tmp66;
                til_Array _tmp67;
        til_AllocError _err_alloc__tmp68;
        til_IndexOutOfBoundsError _err_idx__tmp68;
        til_Str _tmp69 = til_err.msg;
        int _arr_status__tmp68 = til_Array_new(&_tmp67, &_err_alloc__tmp68, "Str", 1);
        if (_arr_status__tmp68 != 0) {
        }
        _arr_status__tmp68 = til_Array_set(&_err_idx__tmp68, &_tmp67, 0, &_tmp69);
        if (_arr_status__tmp68 != 0) {
        }
til_panic(til_Str_from_literal(""), &_tmp67);
        til_Array_delete(&_tmp67);
    }
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
                til_Array _tmp70;
        til_AllocError _err_alloc__tmp71;
        til_IndexOutOfBoundsError _err_idx__tmp71;
        til_Str _tmp72 = til_Str_from_literal("concat: malloc failed");
        int _arr_status__tmp71 = til_Array_new(&_tmp70, &_err_alloc__tmp71, "Str", 1);
        if (_arr_status__tmp71 != 0) {
        }
        _arr_status__tmp71 = til_Array_set(&_err_idx__tmp71, &_tmp70, 0, &_tmp72);
        if (_arr_status__tmp71 != 0) {
        }
til_panic(til_Str_from_literal(""), &_tmp70);
        til_Array_delete(&_tmp70);
    }
    til_memcpy(til_result.c_string, til_a.c_string, til_a.cap);
    til_memcpy(til_add(til_result.c_string, til_a.cap), til_b.c_string, til_b.cap);
    return til_result;
}

int til_format(til_Str* _ret, til_I64_OverflowError* _err1, til_IndexOutOfBoundsError* _err2, til_AllocError* _err3, const til_Str til_prefix, til_Array* til_args) {
    til_Str til_result = {0};
    til_result.cap = til_prefix.cap;
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Str til_arg = til_Str_from_literal("");
        til_IndexOutOfBoundsError _err0__tmp73 = {};
        int _status__tmp73 = til_Array_get(&_err0__tmp73, (*til_args), til_i, (til_Dynamic*)&til_arg);
        if (_status__tmp73 == 1) { *_err2 = _err0__tmp73; return 2; }
        til_result.cap = til_add(til_result.cap, til_arg.cap);
        if (til_lt(til_result.cap, til_arg.cap).data) {
            til_Str _tmp74;
            til_I64_OverflowError _err0__tmp75;
            til_IndexOutOfBoundsError _err1__tmp75;
            til_AllocError _err2__tmp75;
            til_Array _tmp76;
            til_AllocError _err_alloc__tmp77;
            til_IndexOutOfBoundsError _err_idx__tmp77;
            til_Str _tmp78 = til_Str_from_literal("format: integer overflow while summing cap for arg ");
            til_Str _tmp79 = til_I64_to_str(til_i);
            int _arr_status__tmp77 = til_Array_new(&_tmp76, &_err_alloc__tmp77, "Str", 2);
            if (_arr_status__tmp77 != 0) {
                *_err3 = _err_alloc__tmp77; return 3;
            }
            _arr_status__tmp77 = til_Array_set(&_err_idx__tmp77, &_tmp76, 0, &_tmp78);
            if (_arr_status__tmp77 != 0) {
                *_err2 = _err_idx__tmp77; return 2;
            }
            _arr_status__tmp77 = til_Array_set(&_err_idx__tmp77, &_tmp76, 1, &_tmp79);
            if (_arr_status__tmp77 != 0) {
                *_err2 = _err_idx__tmp77; return 2;
            }
            int _status__tmp75 = til_format(&_tmp74, &_err0__tmp75, &_err1__tmp75, &_err2__tmp75, til_Str_from_literal(""), &_tmp76);
            if (_status__tmp75 != 0) {
                if (_status__tmp75 == 1) { *_err1 = _err0__tmp75; return 1; }
                if (_status__tmp75 == 2) { *_err2 = _err1__tmp75; return 2; }
                if (_status__tmp75 == 3) { *_err3 = _err2__tmp75; return 3; }
            }
            til_Array_delete(&_tmp76);
            *_err1 = til_I64_OverflowError_new(_tmp74);
            return 1;
        }
        til_I64_inc(&til_i);
    }
    til_I64 _ret__tmp80;
    til_AllocError _err0__tmp80 = {};
    int _status__tmp80 = til_malloc(&_ret__tmp80, &_err0__tmp80, til_result.cap);
    if (_status__tmp80 == 1) { *_err3 = _err0__tmp80; return 3; }
    til_result.c_string = _ret__tmp80;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Str _tmp81;
        til_I64_OverflowError _err0__tmp82;
        til_IndexOutOfBoundsError _err1__tmp82;
        til_AllocError _err2__tmp82;
        til_Array _tmp83;
        til_AllocError _err_alloc__tmp84;
        til_IndexOutOfBoundsError _err_idx__tmp84;
        til_Str _tmp85 = til_Str_from_literal("format: malloc failed for cap = ");
        til_Str _tmp86 = til_I64_to_str(til_result.cap);
        int _arr_status__tmp84 = til_Array_new(&_tmp83, &_err_alloc__tmp84, "Str", 2);
        if (_arr_status__tmp84 != 0) {
            *_err3 = _err_alloc__tmp84; return 3;
        }
        _arr_status__tmp84 = til_Array_set(&_err_idx__tmp84, &_tmp83, 0, &_tmp85);
        if (_arr_status__tmp84 != 0) {
            *_err2 = _err_idx__tmp84; return 2;
        }
        _arr_status__tmp84 = til_Array_set(&_err_idx__tmp84, &_tmp83, 1, &_tmp86);
        if (_arr_status__tmp84 != 0) {
            *_err2 = _err_idx__tmp84; return 2;
        }
        int _status__tmp82 = til_format(&_tmp81, &_err0__tmp82, &_err1__tmp82, &_err2__tmp82, til_Str_from_literal(""), &_tmp83);
        if (_status__tmp82 != 0) {
            if (_status__tmp82 == 1) { *_err1 = _err0__tmp82; return 1; }
            if (_status__tmp82 == 2) { *_err2 = _err1__tmp82; return 2; }
            if (_status__tmp82 == 3) { *_err3 = _err2__tmp82; return 3; }
        }
        til_Array_delete(&_tmp83);
        *_err3 = til_AllocError_new(_tmp81);
        return 3;
    }
    til_I64 til_offset = 0;
    til_memcpy(til_result.c_string, til_prefix.c_string, til_prefix.cap);
    til_offset = til_prefix.cap;
    til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Str til_s = til_Str_from_literal("");
        til_IndexOutOfBoundsError _err0__tmp87 = {};
        int _status__tmp87 = til_Array_get(&_err0__tmp87, (*til_args), til_i, (til_Dynamic*)&til_s);
        if (_status__tmp87 == 1) { *_err2 = _err0__tmp87; return 2; }
        til_memcpy(til_add(til_result.c_string, til_offset), til_s.c_string, til_s.cap);
        til_offset = til_add(til_offset, til_s.cap);
        til_I64_inc(&til_i);
    }
    *_ret = til_result;
    return 0;
}

til_IndexOutOfBoundsError til_IndexOutOfBoundsError_new(const til_Str til_msg) {
    til_IndexOutOfBoundsError til_err = {0};
    til_err.msg = til_msg;
    return til_err;
}

til_AllocError til_AllocError_new(const til_Str til_msg) {
    til_AllocError til_err = {0};
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
    til_Array til_arr = {0};
    til_arr.type_name = til_Str_from_literal("T");
    til_arr.type_size = til_size_of(til_Str_from_literal(til_T));
    const til_I64 til_size_bytes = til_mul(til_capacity, til_arr.type_size);
    til_I64 _ret__tmp88;
    til_AllocError _err0__tmp88 = {};
    int _status__tmp88 = til_malloc(&_ret__tmp88, &_err0__tmp88, til_size_bytes);
    if (_status__tmp88 == 1) { *_err1 = _err0__tmp88; return 1; }
    til_arr.ptr = _ret__tmp88;
    til_U8 _tmp89;
    til_U8_OverflowError _err0__tmp90;
    int _status__tmp90 = til_U8_from_i64(&_tmp89, &_err0__tmp90, 0);
    if (_status__tmp90 != 0) {
    }
    til_memset(til_arr.ptr, _tmp89, til_size_bytes);
    til_arr._len = til_capacity;
    *_ret = til_arr;
    return 0;
}

int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array til_self, const til_I64 til_index, til_Dynamic* til_T) {
    if (til_gteq(til_index, til_self._len).data) {
        til_Str _tmp91;
        til_I64_OverflowError _err0__tmp92;
        til_IndexOutOfBoundsError _err1__tmp92;
        til_AllocError _err2__tmp92;
        til_Array _tmp93;
        til_AllocError _err_alloc__tmp94;
        til_IndexOutOfBoundsError _err_idx__tmp94;
        til_Str _tmp95 = til_Str_from_literal("Array.get: index out of bounds");
        int _arr_status__tmp94 = til_Array_new(&_tmp93, &_err_alloc__tmp94, "Str", 1);
        if (_arr_status__tmp94 != 0) {
        }
        _arr_status__tmp94 = til_Array_set(&_err_idx__tmp94, &_tmp93, 0, &_tmp95);
        if (_arr_status__tmp94 != 0) {
            *_err1 = _err_idx__tmp94; return 1;
        }
        int _status__tmp92 = til_format(&_tmp91, &_err0__tmp92, &_err1__tmp92, &_err2__tmp92, til_Str_from_literal(""), &_tmp93);
        if (_status__tmp92 != 0) {
            if (_status__tmp92 == 2) { *_err1 = _err1__tmp92; return 1; }
        }
        til_Array_delete(&_tmp93);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp91);
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_gteq(til_index, til_self->_len).data) {
        til_Str _tmp96;
        til_I64_OverflowError _err0__tmp97;
        til_IndexOutOfBoundsError _err1__tmp97;
        til_AllocError _err2__tmp97;
        til_Array _tmp98;
        til_AllocError _err_alloc__tmp99;
        til_IndexOutOfBoundsError _err_idx__tmp99;
        til_Str _tmp100 = til_Str_from_literal("Array.set: index out of bounds");
        int _arr_status__tmp99 = til_Array_new(&_tmp98, &_err_alloc__tmp99, "Str", 1);
        if (_arr_status__tmp99 != 0) {
        }
        _arr_status__tmp99 = til_Array_set(&_err_idx__tmp99, &_tmp98, 0, &_tmp100);
        if (_arr_status__tmp99 != 0) {
            *_err1 = _err_idx__tmp99; return 1;
        }
        int _status__tmp97 = til_format(&_tmp96, &_err0__tmp97, &_err1__tmp97, &_err2__tmp97, til_Str_from_literal(""), &_tmp98);
        if (_status__tmp97 != 0) {
            if (_status__tmp97 == 2) { *_err1 = _err1__tmp97; return 1; }
        }
        til_Array_delete(&_tmp98);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp96);
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
    til_Array til_cloned = {0};
    til_cloned.type_name = til_self.type_name;
    til_cloned.type_size = til_self.type_size;
    til_cloned._len = til_self._len;
    til_I64 til_total_bytes = til_mul(til_self._len, til_self.type_size);
    til_I64 _ret__tmp101;
    til_AllocError _err0__tmp101 = {};
    int _status__tmp101 = til_malloc(&_ret__tmp101, &_err0__tmp101, til_total_bytes);
    if (_status__tmp101 == 1) { *_err1 = _err0__tmp101; return 1; }
    til_cloned.ptr = _ret__tmp101;
    if (til_I64_eq(til_NULL, til_cloned.ptr).data) {
        til_Str _tmp102;
        til_I64_OverflowError _err0__tmp103;
        til_IndexOutOfBoundsError _err1__tmp103;
        til_AllocError _err2__tmp103;
        til_Array _tmp104;
        til_AllocError _err_alloc__tmp105;
        til_IndexOutOfBoundsError _err_idx__tmp105;
        til_Str _tmp106 = til_Str_from_literal("Array.clone: malloc failed for ");
        til_Str _tmp107 = til_I64_to_str(til_total_bytes);
        til_Str _tmp108 = til_Str_from_literal(" bytes");
        int _arr_status__tmp105 = til_Array_new(&_tmp104, &_err_alloc__tmp105, "Str", 3);
        if (_arr_status__tmp105 != 0) {
            *_err1 = _err_alloc__tmp105; return 1;
        }
        _arr_status__tmp105 = til_Array_set(&_err_idx__tmp105, &_tmp104, 0, &_tmp106);
        if (_arr_status__tmp105 != 0) {
        }
        _arr_status__tmp105 = til_Array_set(&_err_idx__tmp105, &_tmp104, 1, &_tmp107);
        if (_arr_status__tmp105 != 0) {
        }
        _arr_status__tmp105 = til_Array_set(&_err_idx__tmp105, &_tmp104, 2, &_tmp108);
        if (_arr_status__tmp105 != 0) {
        }
        int _status__tmp103 = til_format(&_tmp102, &_err0__tmp103, &_err1__tmp103, &_err2__tmp103, til_Str_from_literal(""), &_tmp104);
        if (_status__tmp103 != 0) {
            if (_status__tmp103 == 3) { *_err1 = _err2__tmp103; return 1; }
        }
        til_Array_delete(&_tmp104);
        *_err1 = til_AllocError_new(_tmp102);
        return 1;
    }
    til_memcpy(til_cloned.ptr, til_self.ptr, til_total_bytes);
    *_ret = til_cloned;
    return 0;
}

til_Bool til_Array_contains(const til_Array til_self, const til_Str til_value) {
    til_I64 til_i = 0;
    while (til_lt(til_i, til_self._len).data) {
        til_Str til_elem = til_Str_from_literal("");
        til_IndexOutOfBoundsError _err0__tmp109 = {};
        int _status__tmp109 = til_Array_get(&_err0__tmp109, til_self, til_i, (til_Dynamic*)&til_elem);
        if (til_Str_eq(til_elem, til_value).data) {
            return true;
        }
        til_i = til_add(til_i, 1);
    }
    return false;
}

til_I64 til_Bool_len(const til_Bool til_self) {
    return 1;
}

til_Bool til_Bool_eq(const til_Bool til_a, const til_Bool til_b) {
    til_Bool _tmp110;
    til_Array _tmp111;
    til_AllocError _err_alloc__tmp112;
    til_IndexOutOfBoundsError _err_idx__tmp112;
    til_Bool _tmp113 = til_a;
    til_Bool _tmp114 = til_b;
    int _arr_status__tmp112 = til_Array_new(&_tmp111, &_err_alloc__tmp112, "Bool", 2);
    if (_arr_status__tmp112 != 0) {
    }
    _arr_status__tmp112 = til_Array_set(&_err_idx__tmp112, &_tmp111, 0, &_tmp113);
    if (_arr_status__tmp112 != 0) {
    }
    _arr_status__tmp112 = til_Array_set(&_err_idx__tmp112, &_tmp111, 1, &_tmp114);
    if (_arr_status__tmp112 != 0) {
    }
    _tmp110 = til_and(&_tmp111);
    til_Array_delete(&_tmp111);
    til_Bool _tmp115;
    til_Array _tmp116;
    til_AllocError _err_alloc__tmp117;
    til_IndexOutOfBoundsError _err_idx__tmp117;
    til_Bool _tmp118 = til_not(til_b);
    til_Bool _tmp119 = til_not(til_a);
    int _arr_status__tmp117 = til_Array_new(&_tmp116, &_err_alloc__tmp117, "Bool", 2);
    if (_arr_status__tmp117 != 0) {
    }
    _arr_status__tmp117 = til_Array_set(&_err_idx__tmp117, &_tmp116, 0, &_tmp118);
    if (_arr_status__tmp117 != 0) {
    }
    _arr_status__tmp117 = til_Array_set(&_err_idx__tmp117, &_tmp116, 1, &_tmp119);
    if (_arr_status__tmp117 != 0) {
    }
    _tmp115 = til_and(&_tmp116);
    til_Array_delete(&_tmp116);
    til_Array _tmp120;
    til_AllocError _err_alloc__tmp121;
    til_IndexOutOfBoundsError _err_idx__tmp121;
    int _arr_status__tmp121 = til_Array_new(&_tmp120, &_err_alloc__tmp121, "Bool", 2);
    if (_arr_status__tmp121 != 0) {
    }
    _arr_status__tmp121 = til_Array_set(&_err_idx__tmp121, &_tmp120, 0, &_tmp110);
    if (_arr_status__tmp121 != 0) {
    }
    _arr_status__tmp121 = til_Array_set(&_err_idx__tmp121, &_tmp120, 1, &_tmp115);
    if (_arr_status__tmp121 != 0) {
    }
    til_Bool _tmp122 = til_or(&_tmp120);
    til_Array_delete(&_tmp120);
    return _tmp122;
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
    til_Bool til_b = {0};
    if (til_gt(til_i, 0).data) {
        til_b.data = 1;
    }
    return til_b;
}

til_I64 til_Bool_size(void) {
    return 1;
}

til_I64_OverflowError til_I64_OverflowError_new(const til_Str til_msg) {
    til_I64_OverflowError til_err = {0};
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
    til_Vec til_vec = {0};
    til_vec.type_name = til_Str_from_literal("T");
    til_vec.type_size = til_size_of(til_Str_from_literal(til_T));
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

int til_Vec_new_from_type_info(til_Vec* _ret, til_AllocError* _err1, const til_Str til_type_name, const til_I64 til_type_size) {
    til_Vec til_vec = {0};
    til_vec.type_name = til_type_name;
    til_vec.type_size = til_type_size;
    const til_I64 til_size_bytes = til_mul(til_Vec_INIT_CAP, til_vec.type_size);
    til_I64 _ret__tmp124;
    til_AllocError _err0__tmp124 = {};
    int _status__tmp124 = til_malloc(&_ret__tmp124, &_err0__tmp124, til_size_bytes);
    if (_status__tmp124 == 1) { *_err1 = _err0__tmp124; return 1; }
    til_vec.ptr = _ret__tmp124;
    til_vec._len = 0;
    til_vec.cap = til_Vec_INIT_CAP;
    *_ret = til_vec;
    return 0;
}

int til_Vec_push(til_AllocError* _err1, til_Vec* til_self, const til_Dynamic til_value) {
    if (til_I64_eq(til_self->_len, til_self->cap).data) {
        const til_I64 til_new_cap = til_mul(til_self->cap, 2);
        if (til_gt(til_new_cap, til_Vec_MAX_CAP).data) {
                        til_Array _tmp125;
            til_AllocError _err_alloc__tmp126;
            til_IndexOutOfBoundsError _err_idx__tmp126;
            til_Str _tmp127 = til_Str_from_literal("Vec.push: capacity exceeded Vec.MAX_CAP");
            int _arr_status__tmp126 = til_Array_new(&_tmp125, &_err_alloc__tmp126, "Str", 1);
            if (_arr_status__tmp126 != 0) {
                *_err1 = _err_alloc__tmp126; return 1;
            }
            _arr_status__tmp126 = til_Array_set(&_err_idx__tmp126, &_tmp125, 0, &_tmp127);
            if (_arr_status__tmp126 != 0) {
            }
til_panic(til_Str_from_literal(""), &_tmp125);
            til_Array_delete(&_tmp125);
        }
        til_I64 _ret__tmp128;
        til_I64 til_new_ptr;
        til_AllocError _err0__tmp128 = {};
        int _status__tmp128 = til_malloc(&_ret__tmp128, &_err0__tmp128, til_mul(til_new_cap, til_self->type_size));
        if (_status__tmp128 == 1) { *_err1 = _err0__tmp128; return 1; }
        til_new_ptr = _ret__tmp128;
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
        til_Str _tmp129;
        til_I64_OverflowError _err0__tmp130;
        til_IndexOutOfBoundsError _err1__tmp130;
        til_AllocError _err2__tmp130;
        til_Array _tmp131;
        til_AllocError _err_alloc__tmp132;
        til_IndexOutOfBoundsError _err_idx__tmp132;
        til_Str _tmp133 = til_Str_from_literal("Vec.get: index out of bounds");
        int _arr_status__tmp132 = til_Array_new(&_tmp131, &_err_alloc__tmp132, "Str", 1);
        if (_arr_status__tmp132 != 0) {
        }
        _arr_status__tmp132 = til_Array_set(&_err_idx__tmp132, &_tmp131, 0, &_tmp133);
        if (_arr_status__tmp132 != 0) {
            *_err1 = _err_idx__tmp132; return 1;
        }
        int _status__tmp130 = til_format(&_tmp129, &_err0__tmp130, &_err1__tmp130, &_err2__tmp130, til_Str_from_literal(""), &_tmp131);
        if (_status__tmp130 != 0) {
            if (_status__tmp130 == 2) { *_err1 = _err1__tmp130; return 1; }
        }
        til_Array_delete(&_tmp131);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp129);
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Vec_set(til_IndexOutOfBoundsError* _err1, til_Vec* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_gteq(til_index, til_self->_len).data) {
        til_Str _tmp134;
        til_I64_OverflowError _err0__tmp135;
        til_IndexOutOfBoundsError _err1__tmp135;
        til_AllocError _err2__tmp135;
        til_Array _tmp136;
        til_AllocError _err_alloc__tmp137;
        til_IndexOutOfBoundsError _err_idx__tmp137;
        til_Str _tmp138 = til_Str_from_literal("Vec.set: index out of bounds");
        int _arr_status__tmp137 = til_Array_new(&_tmp136, &_err_alloc__tmp137, "Str", 1);
        if (_arr_status__tmp137 != 0) {
        }
        _arr_status__tmp137 = til_Array_set(&_err_idx__tmp137, &_tmp136, 0, &_tmp138);
        if (_arr_status__tmp137 != 0) {
            *_err1 = _err_idx__tmp137; return 1;
        }
        int _status__tmp135 = til_format(&_tmp134, &_err0__tmp135, &_err1__tmp135, &_err2__tmp135, til_Str_from_literal(""), &_tmp136);
        if (_status__tmp135 != 0) {
            if (_status__tmp135 == 2) { *_err1 = _err1__tmp135; return 1; }
        }
        til_Array_delete(&_tmp136);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp134);
        return 1;
    }
    til_I64 til_dest = til_add(til_self->ptr, til_mul(til_index, til_self->type_size));
    til_memcpy(til_dest, (til_I64)til_value, til_self->type_size);
    return 0;
}

int til_Vec_pop(til_IndexOutOfBoundsError* _err1, til_Vec* til_self, til_Dynamic* til_dest) {
    if (til_I64_eq(til_self->_len, 0).data) {
        til_Str _tmp139;
        til_I64_OverflowError _err0__tmp140;
        til_IndexOutOfBoundsError _err1__tmp140;
        til_AllocError _err2__tmp140;
        til_Array _tmp141;
        til_AllocError _err_alloc__tmp142;
        til_IndexOutOfBoundsError _err_idx__tmp142;
        til_Str _tmp143 = til_Str_from_literal("Vec.pop: cannot pop from empty Vec");
        int _arr_status__tmp142 = til_Array_new(&_tmp141, &_err_alloc__tmp142, "Str", 1);
        if (_arr_status__tmp142 != 0) {
        }
        _arr_status__tmp142 = til_Array_set(&_err_idx__tmp142, &_tmp141, 0, &_tmp143);
        if (_arr_status__tmp142 != 0) {
            *_err1 = _err_idx__tmp142; return 1;
        }
        int _status__tmp140 = til_format(&_tmp139, &_err0__tmp140, &_err1__tmp140, &_err2__tmp140, til_Str_from_literal(""), &_tmp141);
        if (_status__tmp140 != 0) {
            if (_status__tmp140 == 2) { *_err1 = _err1__tmp140; return 1; }
        }
        til_Array_delete(&_tmp141);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp139);
        return 1;
    }
    til_I64 til_last_index = til_sub(til_self->_len, 1);
    til_IndexOutOfBoundsError _err0__tmp144 = {};
    int _status__tmp144 = til_Vec_get(&_err0__tmp144, (*til_self), til_last_index, (til_Dynamic*)&til_dest);
    if (_status__tmp144 == 1) { *_err1 = _err0__tmp144; return 1; }
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
    til_Vec til_cloned = {0};
    til_cloned.type_name = til_self.type_name;
    til_cloned.type_size = til_self.type_size;
    til_cloned._len = til_self._len;
    til_cloned.cap = til_self.cap;
    til_I64 til_total_bytes = til_mul(til_self.cap, til_self.type_size);
    til_I64 _ret__tmp145;
    til_AllocError _err0__tmp145 = {};
    int _status__tmp145 = til_malloc(&_ret__tmp145, &_err0__tmp145, til_total_bytes);
    if (_status__tmp145 == 1) { *_err1 = _err0__tmp145; return 1; }
    til_cloned.ptr = _ret__tmp145;
    if (til_I64_eq(til_NULL, til_cloned.ptr).data) {
        til_Str _tmp146;
        til_I64_OverflowError _err0__tmp147;
        til_IndexOutOfBoundsError _err1__tmp147;
        til_AllocError _err2__tmp147;
        til_Array _tmp148;
        til_AllocError _err_alloc__tmp149;
        til_IndexOutOfBoundsError _err_idx__tmp149;
        til_Str _tmp150 = til_Str_from_literal("Vec.clone: malloc failed for ");
        til_Str _tmp151 = til_I64_to_str(til_total_bytes);
        til_Str _tmp152 = til_Str_from_literal(" bytes");
        int _arr_status__tmp149 = til_Array_new(&_tmp148, &_err_alloc__tmp149, "Str", 3);
        if (_arr_status__tmp149 != 0) {
            *_err1 = _err_alloc__tmp149; return 1;
        }
        _arr_status__tmp149 = til_Array_set(&_err_idx__tmp149, &_tmp148, 0, &_tmp150);
        if (_arr_status__tmp149 != 0) {
        }
        _arr_status__tmp149 = til_Array_set(&_err_idx__tmp149, &_tmp148, 1, &_tmp151);
        if (_arr_status__tmp149 != 0) {
        }
        _arr_status__tmp149 = til_Array_set(&_err_idx__tmp149, &_tmp148, 2, &_tmp152);
        if (_arr_status__tmp149 != 0) {
        }
        int _status__tmp147 = til_format(&_tmp146, &_err0__tmp147, &_err1__tmp147, &_err2__tmp147, til_Str_from_literal(""), &_tmp148);
        if (_status__tmp147 != 0) {
            if (_status__tmp147 == 3) { *_err1 = _err2__tmp147; return 1; }
        }
        til_Array_delete(&_tmp148);
        *_err1 = til_AllocError_new(_tmp146);
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
                                til_Array _tmp153;
                til_AllocError _err_alloc__tmp154;
                til_IndexOutOfBoundsError _err_idx__tmp154;
                til_Str _tmp155 = til_Str_from_literal("Vec.extend: capacity exceeded Vec.MAX_CAP");
                int _arr_status__tmp154 = til_Array_new(&_tmp153, &_err_alloc__tmp154, "Str", 1);
                if (_arr_status__tmp154 != 0) {
                    *_err1 = _err_alloc__tmp154; return 1;
                }
                _arr_status__tmp154 = til_Array_set(&_err_idx__tmp154, &_tmp153, 0, &_tmp155);
                if (_arr_status__tmp154 != 0) {
                }
til_panic(til_Str_from_literal(""), &_tmp153);
                til_Array_delete(&_tmp153);
            }
            til_I64 _ret__tmp156;
            til_I64 til_new_ptr;
            til_AllocError _err0__tmp156 = {};
            int _status__tmp156 = til_malloc(&_ret__tmp156, &_err0__tmp156, til_mul(til_new_cap, til_self->type_size));
            if (_status__tmp156 == 1) { *_err1 = _err0__tmp156; return 1; }
            til_new_ptr = _ret__tmp156;
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
        til_Str _tmp157;
        til_I64_OverflowError _err0__tmp158;
        til_IndexOutOfBoundsError _err1__tmp158;
        til_AllocError _err2__tmp158;
        til_Array _tmp159;
        til_AllocError _err_alloc__tmp160;
        til_IndexOutOfBoundsError _err_idx__tmp160;
        til_Str _tmp161 = til_Str_from_literal("Vec.remove: index out of bounds");
        int _arr_status__tmp160 = til_Array_new(&_tmp159, &_err_alloc__tmp160, "Str", 1);
        if (_arr_status__tmp160 != 0) {
        }
        _arr_status__tmp160 = til_Array_set(&_err_idx__tmp160, &_tmp159, 0, &_tmp161);
        if (_arr_status__tmp160 != 0) {
            *_err1 = _err_idx__tmp160; return 1;
        }
        int _status__tmp158 = til_format(&_tmp157, &_err0__tmp158, &_err1__tmp158, &_err2__tmp158, til_Str_from_literal(""), &_tmp159);
        if (_status__tmp158 != 0) {
            if (_status__tmp158 == 2) { *_err1 = _err1__tmp158; return 1; }
        }
        til_Array_delete(&_tmp159);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp157);
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
    til_Str til_cloned = {0};
    til_cloned.cap = til_self.cap;
    til_I64 _ret__tmp162;
    til_AllocError _err0__tmp162 = {};
    int _status__tmp162 = til_malloc(&_ret__tmp162, &_err0__tmp162, til_cloned.cap);
    if (_status__tmp162 == 1) { *_err1 = _err0__tmp162; return 1; }
    til_cloned.c_string = _ret__tmp162;
    if (til_I64_eq(til_NULL, til_cloned.c_string).data) {
        til_Str _tmp163;
        til_I64_OverflowError _err0__tmp164;
        til_IndexOutOfBoundsError _err1__tmp164;
        til_AllocError _err2__tmp164;
        til_Array _tmp165;
        til_AllocError _err_alloc__tmp166;
        til_IndexOutOfBoundsError _err_idx__tmp166;
        til_Str _tmp167 = til_Str_from_literal("Str.clone: malloc failed for ");
        til_Str _tmp168 = til_I64_to_str(til_cloned.cap);
        til_Str _tmp169 = til_Str_from_literal(" bytes");
        int _arr_status__tmp166 = til_Array_new(&_tmp165, &_err_alloc__tmp166, "Str", 3);
        if (_arr_status__tmp166 != 0) {
            *_err1 = _err_alloc__tmp166; return 1;
        }
        _arr_status__tmp166 = til_Array_set(&_err_idx__tmp166, &_tmp165, 0, &_tmp167);
        if (_arr_status__tmp166 != 0) {
        }
        _arr_status__tmp166 = til_Array_set(&_err_idx__tmp166, &_tmp165, 1, &_tmp168);
        if (_arr_status__tmp166 != 0) {
        }
        _arr_status__tmp166 = til_Array_set(&_err_idx__tmp166, &_tmp165, 2, &_tmp169);
        if (_arr_status__tmp166 != 0) {
        }
        int _status__tmp164 = til_format(&_tmp163, &_err0__tmp164, &_err1__tmp164, &_err2__tmp164, til_Str_from_literal(""), &_tmp165);
        if (_status__tmp164 != 0) {
            if (_status__tmp164 == 3) { *_err1 = _err2__tmp164; return 1; }
        }
        til_Array_delete(&_tmp165);
        *_err1 = til_AllocError_new(_tmp163);
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
        return til_sub(0, 1);
    }
    if (til_I64_eq(til_Str_len(til_needle), 0).data) {
        return til_sub(0, 1);
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
    return til_sub(0, 1);
}

til_I64 til_Str_rfind(const til_Str til_self, const til_Str til_needle) {
    if (til_gt(til_Str_len(til_needle), til_Str_len(til_self)).data) {
        return til_sub(0, 1);
    }
    if (til_I64_eq(til_Str_len(til_needle), 0).data) {
        return til_sub(0, 1);
    }
    til_I64 til_last_found = til_sub(0, 1);
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
        til_Str _ret__tmp170;
        til_AllocError _err0__tmp170 = {};
        int _status__tmp170 = til_Str_clone(&_ret__tmp170, &_err0__tmp170, til_self);
        if (_status__tmp170 == 1) { *_err1 = _err0__tmp170; return 1; }
        *_ret = _ret__tmp170;
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
        til_Str _ret__tmp171;
        til_AllocError _err0__tmp171 = {};
        int _status__tmp171 = til_Str_clone(&_ret__tmp171, &_err0__tmp171, til_self);
        if (_status__tmp171 == 1) { *_err1 = _err0__tmp171; return 1; }
        *_ret = _ret__tmp171;
        return 0;
    }
    til_I64 til_new_len = til_add(til_sub(til_Str_len(til_self), til_mul(til_count, til_Str_len(til_from))), til_mul(til_count, til_Str_len(til_to)));
    til_Str til_result = {0};
    til_result.cap = til_new_len;
    til_I64 _ret__tmp172;
    til_AllocError _err0__tmp172 = {};
    int _status__tmp172 = til_malloc(&_ret__tmp172, &_err0__tmp172, til_new_len);
    if (_status__tmp172 == 1) { *_err1 = _err0__tmp172; return 1; }
    til_result.c_string = _ret__tmp172;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Str _tmp173;
        til_I64_OverflowError _err0__tmp174;
        til_IndexOutOfBoundsError _err1__tmp174;
        til_AllocError _err2__tmp174;
        til_Array _tmp175;
        til_AllocError _err_alloc__tmp176;
        til_IndexOutOfBoundsError _err_idx__tmp176;
        til_Str _tmp177 = til_Str_from_literal("Str.replace: malloc failed for ");
        til_Str _tmp178 = til_I64_to_str(til_new_len);
        til_Str _tmp179 = til_Str_from_literal(" bytes");
        int _arr_status__tmp176 = til_Array_new(&_tmp175, &_err_alloc__tmp176, "Str", 3);
        if (_arr_status__tmp176 != 0) {
            *_err1 = _err_alloc__tmp176; return 1;
        }
        _arr_status__tmp176 = til_Array_set(&_err_idx__tmp176, &_tmp175, 0, &_tmp177);
        if (_arr_status__tmp176 != 0) {
        }
        _arr_status__tmp176 = til_Array_set(&_err_idx__tmp176, &_tmp175, 1, &_tmp178);
        if (_arr_status__tmp176 != 0) {
        }
        _arr_status__tmp176 = til_Array_set(&_err_idx__tmp176, &_tmp175, 2, &_tmp179);
        if (_arr_status__tmp176 != 0) {
        }
        int _status__tmp174 = til_format(&_tmp173, &_err0__tmp174, &_err1__tmp174, &_err2__tmp174, til_Str_from_literal(""), &_tmp175);
        if (_status__tmp174 != 0) {
            if (_status__tmp174 == 3) { *_err1 = _err2__tmp174; return 1; }
        }
        til_Array_delete(&_tmp175);
        *_err1 = til_AllocError_new(_tmp173);
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
    if (til_I64_eq(til_Str_len(til_from), 0).data) {
        til_Str _ret__tmp180;
        til_AllocError _err0__tmp180 = {};
        int _status__tmp180 = til_Str_clone(&_ret__tmp180, &_err0__tmp180, til_self);
        if (_status__tmp180 == 1) { *_err1 = _err0__tmp180; return 1; }
        *_ret = _ret__tmp180;
        return 0;
    }
    if (til_I64_eq(til_n, 0).data) {
        til_Str _ret__tmp181;
        til_AllocError _err0__tmp181 = {};
        int _status__tmp181 = til_Str_clone(&_ret__tmp181, &_err0__tmp181, til_self);
        if (_status__tmp181 == 1) { *_err1 = _err0__tmp181; return 1; }
        *_ret = _ret__tmp181;
        return 0;
    }
    til_I64 til_idx = til_Str_find(til_self, til_from);
    if (til_lt(til_idx, 0).data) {
        til_Str _ret__tmp182;
        til_AllocError _err0__tmp182 = {};
        int _status__tmp182 = til_Str_clone(&_ret__tmp182, &_err0__tmp182, til_self);
        if (_status__tmp182 == 1) { *_err1 = _err0__tmp182; return 1; }
        *_ret = _ret__tmp182;
        return 0;
    }
    til_Str _ret__tmp183;
    til_Str til_prefix;
    til_IndexOutOfBoundsError _err0__tmp183 = {};
    til_AllocError _err1__tmp183 = {};
    int _status__tmp183 = til_get_substr(&_ret__tmp183, &_err0__tmp183, &_err1__tmp183, til_self, 0, til_idx);
    if (_status__tmp183 == 2) { *_err1 = _err1__tmp183; return 1; }
    til_prefix = _ret__tmp183;
    til_Str _ret__tmp184;
    til_Str til_suffix;
    til_IndexOutOfBoundsError _err0__tmp184 = {};
    til_AllocError _err1__tmp184 = {};
    int _status__tmp184 = til_get_substr(&_ret__tmp184, &_err0__tmp184, &_err1__tmp184, til_self, til_add(til_idx, til_Str_len(til_from)), til_Str_len(til_self));
    if (_status__tmp184 == 2) { *_err1 = _err1__tmp184; return 1; }
    til_suffix = _ret__tmp184;
    til_Str til_result = til_concat(til_concat(til_prefix, til_to), til_suffix);
    if (til_gt(til_n, 1).data) {
        til_Str _ret__tmp185;
        til_Str til_rest;
        til_AllocError _err0__tmp185 = {};
        int _status__tmp185 = til_Str_replacen(&_ret__tmp185, &_err0__tmp185, til_suffix, til_from, til_to, til_sub(til_n, 1));
        if (_status__tmp185 == 1) { *_err1 = _err0__tmp185; return 1; }
        til_rest = _ret__tmp185;
        til_result = til_concat(til_concat(til_prefix, til_to), til_rest);
    }
    *_ret = til_result;
    return 0;
}

int til_Str_split(til_Vec* _ret, til_AllocError* _err1, til_IndexOutOfBoundsError* _err2, const til_Str til_self, const til_Str til_delimiter) {
    til_Vec _ret__tmp186;
    til_Vec til_parts;
    til_AllocError _err0__tmp186 = {};
    int _status__tmp186 = til_Vec_new(&_ret__tmp186, &_err0__tmp186, "Str");
    if (_status__tmp186 == 1) { *_err1 = _err0__tmp186; return 1; }
    til_parts = _ret__tmp186;
    if (til_I64_eq(til_Str_len(til_delimiter), 0).data) {
        til_Str _tmp188;
        til_AllocError _err0__tmp189;
        int _status__tmp189 = til_Str_clone(&_tmp188, &_err0__tmp189, til_self);
        if (_status__tmp189 != 0) {
            if (_status__tmp189 == 1) { *_err1 = _err0__tmp189; return 1; }
        }
        til_AllocError _err0__tmp187 = {};
        int _status__tmp187 = til_Vec_push(&_err0__tmp187, &til_parts, &_tmp188);
        if (_status__tmp187 == 1) { *_err1 = _err0__tmp187; return 1; }
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
                til_Str _ret__tmp190;
                til_Str til_part;
                til_IndexOutOfBoundsError _err0__tmp190 = {};
                til_AllocError _err1__tmp190 = {};
                int _status__tmp190 = til_get_substr(&_ret__tmp190, &_err0__tmp190, &_err1__tmp190, til_self, til_start, til_pos);
                if (_status__tmp190 == 1) { *_err2 = _err0__tmp190; return 2; }
                if (_status__tmp190 == 2) { *_err1 = _err1__tmp190; return 1; }
                til_part = _ret__tmp190;
                til_AllocError _err0__tmp191 = {};
                int _status__tmp191 = til_Vec_push(&_err0__tmp191, &til_parts, (til_Dynamic*)&til_part);
                if (_status__tmp191 == 1) { *_err1 = _err0__tmp191; return 1; }
            } else {
                til_Str _tmp193 = til_Str_from_literal("");
                til_AllocError _err0__tmp192 = {};
                int _status__tmp192 = til_Vec_push(&_err0__tmp192, &til_parts, &_tmp193);
                if (_status__tmp192 == 1) { *_err1 = _err0__tmp192; return 1; }
            }
            til_start = til_add(til_pos, til_Str_len(til_delimiter));
            til_pos = til_start;
        } else {
            til_pos = til_add(til_pos, 1);
        }
    }
    if (til_lt(til_start, til_Str_len(til_self)).data) {
        til_Str _ret__tmp194;
        til_Str til_part;
        til_IndexOutOfBoundsError _err0__tmp194 = {};
        til_AllocError _err1__tmp194 = {};
        int _status__tmp194 = til_get_substr(&_ret__tmp194, &_err0__tmp194, &_err1__tmp194, til_self, til_start, til_Str_len(til_self));
        if (_status__tmp194 == 1) { *_err2 = _err0__tmp194; return 2; }
        if (_status__tmp194 == 2) { *_err1 = _err1__tmp194; return 1; }
        til_part = _ret__tmp194;
        til_AllocError _err0__tmp195 = {};
        int _status__tmp195 = til_Vec_push(&_err0__tmp195, &til_parts, (til_Dynamic*)&til_part);
        if (_status__tmp195 == 1) { *_err1 = _err0__tmp195; return 1; }
    } else {
        if (til_I64_eq(til_start, til_Str_len(til_self)).data) {
            til_Str _tmp197 = til_Str_from_literal("");
            til_AllocError _err0__tmp196 = {};
            int _status__tmp196 = til_Vec_push(&_err0__tmp196, &til_parts, &_tmp197);
            if (_status__tmp196 == 1) { *_err1 = _err0__tmp196; return 1; }
        }
    }
    *_ret = til_parts;
    return 0;
}

til_U8_OverflowError til_U8_OverflowError_new(const til_Str til_msg) {
    til_U8_OverflowError til_err = {0};
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
    til_U8 _ret__tmp198;
    til_U8_OverflowError _err0__tmp198 = {};
    int _status__tmp198 = til_U8_from_i64(&_ret__tmp198, &_err0__tmp198, til_add(til_U8_to_i64(til_a), til_U8_to_i64(til_b)));
    if (_status__tmp198 == 1) { *_err1 = _err0__tmp198; return 1; }
    *_ret = _ret__tmp198;
    return 0;
}

int til_U8_from_i64(til_U8* _ret, til_U8_OverflowError* _err1, const til_I64 til_self) {
    if (til_lt(til_self, 0).data) {
        til_Str _tmp199;
        til_I64_OverflowError _err0__tmp200;
        til_IndexOutOfBoundsError _err1__tmp200;
        til_AllocError _err2__tmp200;
        til_Array _tmp201;
        til_AllocError _err_alloc__tmp202;
        til_IndexOutOfBoundsError _err_idx__tmp202;
        til_Str _tmp203 = til_Str_from_literal("Negative values cannot be cast into 'U8'");
        int _arr_status__tmp202 = til_Array_new(&_tmp201, &_err_alloc__tmp202, "Str", 1);
        if (_arr_status__tmp202 != 0) {
        }
        _arr_status__tmp202 = til_Array_set(&_err_idx__tmp202, &_tmp201, 0, &_tmp203);
        if (_arr_status__tmp202 != 0) {
        }
        int _status__tmp200 = til_format(&_tmp199, &_err0__tmp200, &_err1__tmp200, &_err2__tmp200, til_Str_from_literal(""), &_tmp201);
        if (_status__tmp200 != 0) {
        }
        til_Array_delete(&_tmp201);
        *_err1 = til_U8_OverflowError_new(_tmp199);
        return 1;
    }
    if (til_gt(til_self, til_MAX_U8).data) {
        til_Str _tmp204;
        til_I64_OverflowError _err0__tmp205;
        til_IndexOutOfBoundsError _err1__tmp205;
        til_AllocError _err2__tmp205;
        til_Array _tmp206;
        til_AllocError _err_alloc__tmp207;
        til_IndexOutOfBoundsError _err_idx__tmp207;
        til_Str _tmp208 = til_Str_from_literal("U8: cannot be casted from an I64 greater than: ");
        til_Str _tmp209 = til_I64_to_str(til_MAX_U8);
        int _arr_status__tmp207 = til_Array_new(&_tmp206, &_err_alloc__tmp207, "Str", 2);
        if (_arr_status__tmp207 != 0) {
        }
        _arr_status__tmp207 = til_Array_set(&_err_idx__tmp207, &_tmp206, 0, &_tmp208);
        if (_arr_status__tmp207 != 0) {
        }
        _arr_status__tmp207 = til_Array_set(&_err_idx__tmp207, &_tmp206, 1, &_tmp209);
        if (_arr_status__tmp207 != 0) {
        }
        int _status__tmp205 = til_format(&_tmp204, &_err0__tmp205, &_err1__tmp205, &_err2__tmp205, til_Str_from_literal(""), &_tmp206);
        if (_status__tmp205 != 0) {
        }
        til_Array_delete(&_tmp206);
        *_err1 = til_U8_OverflowError_new(_tmp204);
        return 1;
    }
    *_ret = til_i64_to_u8(til_self);
    return 0;
}

til_Str til_U8_to_str(const til_U8 til_self) {
    return til_I64_to_str(til_U8_to_i64(til_self));
}

int til_U8_from_str(til_U8* _ret, til_U8_OverflowError* _err1, const til_Str til_s) {
    til_U8 _ret__tmp210;
    til_U8_OverflowError _err0__tmp210 = {};
    int _status__tmp210 = til_U8_from_i64(&_ret__tmp210, &_err0__tmp210, til_I64_from_str(til_s));
    if (_status__tmp210 == 1) { *_err1 = _err0__tmp210; return 1; }
    *_ret = _ret__tmp210;
    return 0;
}

til_I64 til_U8_size(void) {
    return 1;
}

int main() {
    const til_I64 til_MIN_I64 = til_sub(0, 922337203);
        til_Array _tmp211;
    til_AllocError _err_alloc__tmp212;
    til_IndexOutOfBoundsError _err_idx__tmp212;
    til_Str _tmp213 = til_Str_from_literal("Hello World!");
    int _arr_status__tmp212 = til_Array_new(&_tmp211, &_err_alloc__tmp212, "Str", 1);
    if (_arr_status__tmp212 != 0) {
    }
    _arr_status__tmp212 = til_Array_set(&_err_idx__tmp212, &_tmp211, 0, &_tmp213);
    if (_arr_status__tmp212 != 0) {
    }
til_println(&_tmp211);
    til_Array_delete(&_tmp211);
    return 0;
}
