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
til_Bool til_lteq(const til_I64 til_a, const til_I64 til_b);
til_Bool til_gteq(const til_I64 til_a, const til_I64 til_b);
void til_print(til_Array* til_args);
void til_println(til_Array* til_args);
int til_get_substr(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_start, const til_I64 til_end);
int til_get_char(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_pos);
til_Bool til_starts_with(const til_Str til_s, const til_Str til_prefix);
til_Str til_concat(const til_Str til_a, const til_Str til_b);
int til_format(til_Str* _ret, til_I64_OverflowError* _err1, til_IndexOutOfBoundsError* _err2, til_AllocError* _err3, const til_Str til_prefix, til_Array* til_args);
void til_panic(const til_Str til_loc_str, til_Array* til_msgs);
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
int til_Str_split(til_Vec* _ret, til_AllocError* _err1, til_IndexOutOfBoundsError* _err2, const til_Str til_self, const til_Str til_delimiter);
til_U8_OverflowError til_U8_OverflowError_new(const til_Str til_msg);
til_I64 til_U8_len(const til_I64 til_self);
til_Bool til_U8_eq(const til_U8 til_self, const til_U8 til_other);
til_I64 til_U8_to_i64(const til_U8 til_self);
int til_U8_u8_add(til_U8* _ret, til_U8_OverflowError* _err1, const til_U8 til_a, const til_U8 til_b);
int til_U8_from_i64(til_U8* _ret, til_U8_OverflowError* _err1, const til_I64 til_self);
til_Str til_U8_to_str(const til_U8 til_self);
int til_U8_from_str(til_U8* _ret, til_U8_OverflowError* _err1, const til_Str til_s);
til_I64 til_U8_size(void);

#include "ext.c"

const til_I64 til_Vec_INIT_CAP = 16;
const til_I64 til_Vec_MAX_CAP = 1024;
const til_I64 til_NULL = 0;
const til_I64 til_I64_SIZE = 8;
const til_I64 til_MAX_I64 = 9223372036854775807;
const til_I64 til_U8_SIZE = 1;
const til_I64 til_MIN_U8 = 0;
const til_I64 til_MAX_U8 = 255;

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
        til_I64_inc(til_i);
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
        til_I64_inc(til_i);
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
        til_IndexOutOfBoundsError _err0__tmp2 = {};
        int _status__tmp2 = til_Array_get(&_err0__tmp2, (*til_args), til_i, (til_Dynamic*)&til_val);
        til_single_print(til_val);
        til_I64_inc(til_i);
    }
    til_print_flush();
}

void til_println(til_Array* til_args) {
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Str til_val = til_Str_from_literal("");
        til_IndexOutOfBoundsError _err0__tmp3 = {};
        int _status__tmp3 = til_Array_get(&_err0__tmp3, (*til_args), til_i, (til_Dynamic*)&til_val);
        til_single_print(til_val);
        til_I64_inc(til_i);
    }
    til_single_print(til_Str_from_literal("\n"));
    til_print_flush();
}

int til_get_substr(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_start, const til_I64 til_end) {
    if (til_lt(til_start, 0).data) {
        til_Str _tmp4;
        til_I64_OverflowError _err0__tmp5;
        til_IndexOutOfBoundsError _err1__tmp5;
        til_AllocError _err2__tmp5;
        til_Array _tmp6;
        til_AllocError _err_alloc__tmp7;
        til_IndexOutOfBoundsError _err_idx__tmp7;
        til_Str _tmp8 = til_Str_from_literal("get_substr: start index ");
        til_Str _tmp9 = til_I64_to_str(til_start);
        til_Str _tmp10 = til_Str_from_literal(" cannot be negative");
        int _arr_status__tmp7 = til_Array_new(&_tmp6, &_err_alloc__tmp7, "Str", 3);
        if (_arr_status__tmp7 != 0) {
            *_err2 = _err_alloc__tmp7; return 2;
        }
        _arr_status__tmp7 = til_Array_set(&_err_idx__tmp7, &_tmp6, 0, &_tmp8);
        if (_arr_status__tmp7 != 0) {
            *_err1 = _err_idx__tmp7; return 1;
        }
        _arr_status__tmp7 = til_Array_set(&_err_idx__tmp7, &_tmp6, 1, &_tmp9);
        if (_arr_status__tmp7 != 0) {
            *_err1 = _err_idx__tmp7; return 1;
        }
        _arr_status__tmp7 = til_Array_set(&_err_idx__tmp7, &_tmp6, 2, &_tmp10);
        if (_arr_status__tmp7 != 0) {
            *_err1 = _err_idx__tmp7; return 1;
        }
        int _status__tmp5 = til_format(&_tmp4, &_err0__tmp5, &_err1__tmp5, &_err2__tmp5, til_Str_from_literal(""), &_tmp6);
        if (_status__tmp5 != 0) {
            if (_status__tmp5 == 2) { *_err1 = _err1__tmp5; return 1; }
            if (_status__tmp5 == 3) { *_err2 = _err2__tmp5; return 2; }
        }
        til_Array_delete(&_tmp6);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp4);
        return 1;
    }
    if (til_lt(til_end, 0).data) {
        til_Str _tmp11;
        til_I64_OverflowError _err0__tmp12;
        til_IndexOutOfBoundsError _err1__tmp12;
        til_AllocError _err2__tmp12;
        til_Array _tmp13;
        til_AllocError _err_alloc__tmp14;
        til_IndexOutOfBoundsError _err_idx__tmp14;
        til_Str _tmp15 = til_Str_from_literal("get_substr: end index ");
        til_Str _tmp16 = til_I64_to_str(til_end);
        til_Str _tmp17 = til_Str_from_literal(" cannot be negative");
        int _arr_status__tmp14 = til_Array_new(&_tmp13, &_err_alloc__tmp14, "Str", 3);
        if (_arr_status__tmp14 != 0) {
            *_err2 = _err_alloc__tmp14; return 2;
        }
        _arr_status__tmp14 = til_Array_set(&_err_idx__tmp14, &_tmp13, 0, &_tmp15);
        if (_arr_status__tmp14 != 0) {
            *_err1 = _err_idx__tmp14; return 1;
        }
        _arr_status__tmp14 = til_Array_set(&_err_idx__tmp14, &_tmp13, 1, &_tmp16);
        if (_arr_status__tmp14 != 0) {
            *_err1 = _err_idx__tmp14; return 1;
        }
        _arr_status__tmp14 = til_Array_set(&_err_idx__tmp14, &_tmp13, 2, &_tmp17);
        if (_arr_status__tmp14 != 0) {
            *_err1 = _err_idx__tmp14; return 1;
        }
        int _status__tmp12 = til_format(&_tmp11, &_err0__tmp12, &_err1__tmp12, &_err2__tmp12, til_Str_from_literal(""), &_tmp13);
        if (_status__tmp12 != 0) {
            if (_status__tmp12 == 2) { *_err1 = _err1__tmp12; return 1; }
            if (_status__tmp12 == 3) { *_err2 = _err2__tmp12; return 2; }
        }
        til_Array_delete(&_tmp13);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp11);
        return 1;
    }
    if (til_gt(til_start, til_end).data) {
        til_Str _tmp18;
        til_I64_OverflowError _err0__tmp19;
        til_IndexOutOfBoundsError _err1__tmp19;
        til_AllocError _err2__tmp19;
        til_Array _tmp20;
        til_AllocError _err_alloc__tmp21;
        til_IndexOutOfBoundsError _err_idx__tmp21;
        til_Str _tmp22 = til_Str_from_literal("get_substr: start index ");
        til_Str _tmp23 = til_I64_to_str(til_start);
        til_Str _tmp24 = til_Str_from_literal(" is greater than end index ");
        til_Str _tmp25 = til_I64_to_str(til_end);
        int _arr_status__tmp21 = til_Array_new(&_tmp20, &_err_alloc__tmp21, "Str", 4);
        if (_arr_status__tmp21 != 0) {
            *_err2 = _err_alloc__tmp21; return 2;
        }
        _arr_status__tmp21 = til_Array_set(&_err_idx__tmp21, &_tmp20, 0, &_tmp22);
        if (_arr_status__tmp21 != 0) {
            *_err1 = _err_idx__tmp21; return 1;
        }
        _arr_status__tmp21 = til_Array_set(&_err_idx__tmp21, &_tmp20, 1, &_tmp23);
        if (_arr_status__tmp21 != 0) {
            *_err1 = _err_idx__tmp21; return 1;
        }
        _arr_status__tmp21 = til_Array_set(&_err_idx__tmp21, &_tmp20, 2, &_tmp24);
        if (_arr_status__tmp21 != 0) {
            *_err1 = _err_idx__tmp21; return 1;
        }
        _arr_status__tmp21 = til_Array_set(&_err_idx__tmp21, &_tmp20, 3, &_tmp25);
        if (_arr_status__tmp21 != 0) {
            *_err1 = _err_idx__tmp21; return 1;
        }
        int _status__tmp19 = til_format(&_tmp18, &_err0__tmp19, &_err1__tmp19, &_err2__tmp19, til_Str_from_literal(""), &_tmp20);
        if (_status__tmp19 != 0) {
            if (_status__tmp19 == 2) { *_err1 = _err1__tmp19; return 1; }
            if (_status__tmp19 == 3) { *_err2 = _err2__tmp19; return 2; }
        }
        til_Array_delete(&_tmp20);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp18);
        return 1;
    }
    if (til_gt(til_end, til_Str_len(til_s)).data) {
        til_Str _tmp26;
        til_I64_OverflowError _err0__tmp27;
        til_IndexOutOfBoundsError _err1__tmp27;
        til_AllocError _err2__tmp27;
        til_Array _tmp28;
        til_AllocError _err_alloc__tmp29;
        til_IndexOutOfBoundsError _err_idx__tmp29;
        til_Str _tmp30 = til_Str_from_literal("get_substr: end index ");
        til_Str _tmp31 = til_I64_to_str(til_end);
        til_Str _tmp32 = til_Str_from_literal(" is greater than string length ");
        til_Str _tmp33 = til_I64_to_str(til_Str_len(til_s));
        int _arr_status__tmp29 = til_Array_new(&_tmp28, &_err_alloc__tmp29, "Str", 4);
        if (_arr_status__tmp29 != 0) {
            *_err2 = _err_alloc__tmp29; return 2;
        }
        _arr_status__tmp29 = til_Array_set(&_err_idx__tmp29, &_tmp28, 0, &_tmp30);
        if (_arr_status__tmp29 != 0) {
            *_err1 = _err_idx__tmp29; return 1;
        }
        _arr_status__tmp29 = til_Array_set(&_err_idx__tmp29, &_tmp28, 1, &_tmp31);
        if (_arr_status__tmp29 != 0) {
            *_err1 = _err_idx__tmp29; return 1;
        }
        _arr_status__tmp29 = til_Array_set(&_err_idx__tmp29, &_tmp28, 2, &_tmp32);
        if (_arr_status__tmp29 != 0) {
            *_err1 = _err_idx__tmp29; return 1;
        }
        _arr_status__tmp29 = til_Array_set(&_err_idx__tmp29, &_tmp28, 3, &_tmp33);
        if (_arr_status__tmp29 != 0) {
            *_err1 = _err_idx__tmp29; return 1;
        }
        int _status__tmp27 = til_format(&_tmp26, &_err0__tmp27, &_err1__tmp27, &_err2__tmp27, til_Str_from_literal(""), &_tmp28);
        if (_status__tmp27 != 0) {
            if (_status__tmp27 == 2) { *_err1 = _err1__tmp27; return 1; }
            if (_status__tmp27 == 3) { *_err2 = _err2__tmp27; return 2; }
        }
        til_Array_delete(&_tmp28);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp26);
        return 1;
    }
    if (til_I64_eq(til_start, til_end).data) {
        til_Str _tmp34;
        til_I64_OverflowError _err0__tmp35;
        til_IndexOutOfBoundsError _err1__tmp35;
        til_AllocError _err2__tmp35;
        til_Array _tmp36;
        til_AllocError _err_alloc__tmp37;
        til_IndexOutOfBoundsError _err_idx__tmp37;
        til_Str _tmp38 = til_Str_from_literal("get_substr: start and end are the same (");
        til_Str _tmp39 = til_I64_to_str(til_start);
        til_Str _tmp40 = til_Str_from_literal("), no substring");
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
        int _status__tmp35 = til_format(&_tmp34, &_err0__tmp35, &_err1__tmp35, &_err2__tmp35, til_Str_from_literal(""), &_tmp36);
        if (_status__tmp35 != 0) {
            if (_status__tmp35 == 2) { *_err1 = _err1__tmp35; return 1; }
            if (_status__tmp35 == 3) { *_err2 = _err2__tmp35; return 2; }
        }
        til_Array_delete(&_tmp36);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp34);
        return 1;
    }
    til_Str til_substr = {0};
    til_substr.cap = til_sub(til_end, til_start);
    til_I64 _ret__tmp41;
    til_AllocError _err0__tmp41 = {};
    int _status__tmp41 = til_malloc(&_ret__tmp41, &_err0__tmp41, til_substr.cap);
    if (_status__tmp41 == 1) { *_err2 = _err0__tmp41; return 2; }
    til_substr.c_string = _ret__tmp41;
    if (til_I64_eq(til_NULL, til_substr.c_string).data) {
        til_Str _tmp42;
        til_I64_OverflowError _err0__tmp43;
        til_IndexOutOfBoundsError _err1__tmp43;
        til_AllocError _err2__tmp43;
        til_Array _tmp44;
        til_AllocError _err_alloc__tmp45;
        til_IndexOutOfBoundsError _err_idx__tmp45;
        til_Str _tmp46 = til_Str_from_literal("Str.get_substr: failed to allocate ");
        til_Str _tmp47 = til_I64_to_str(til_substr.cap);
        til_Str _tmp48 = til_Str_from_literal(" bytes");
        int _arr_status__tmp45 = til_Array_new(&_tmp44, &_err_alloc__tmp45, "Str", 3);
        if (_arr_status__tmp45 != 0) {
            *_err2 = _err_alloc__tmp45; return 2;
        }
        _arr_status__tmp45 = til_Array_set(&_err_idx__tmp45, &_tmp44, 0, &_tmp46);
        if (_arr_status__tmp45 != 0) {
            *_err1 = _err_idx__tmp45; return 1;
        }
        _arr_status__tmp45 = til_Array_set(&_err_idx__tmp45, &_tmp44, 1, &_tmp47);
        if (_arr_status__tmp45 != 0) {
            *_err1 = _err_idx__tmp45; return 1;
        }
        _arr_status__tmp45 = til_Array_set(&_err_idx__tmp45, &_tmp44, 2, &_tmp48);
        if (_arr_status__tmp45 != 0) {
            *_err1 = _err_idx__tmp45; return 1;
        }
        int _status__tmp43 = til_format(&_tmp42, &_err0__tmp43, &_err1__tmp43, &_err2__tmp43, til_Str_from_literal(""), &_tmp44);
        if (_status__tmp43 != 0) {
            if (_status__tmp43 == 2) { *_err1 = _err1__tmp43; return 1; }
            if (_status__tmp43 == 3) { *_err2 = _err2__tmp43; return 2; }
        }
        til_Array_delete(&_tmp44);
        *_err2 = til_AllocError_new(_tmp42);
        return 2;
    }
    til_memcpy(til_substr.c_string, til_add(til_s.c_string, til_start), til_substr.cap);
    *_ret = til_substr;
    return 0;
}

int til_get_char(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_pos) {
    til_Str _ret__tmp49;
    til_IndexOutOfBoundsError _err0__tmp49 = {};
    til_AllocError _err1__tmp49 = {};
    int _status__tmp49 = til_get_substr(&_ret__tmp49, &_err0__tmp49, &_err1__tmp49, til_s, til_pos, til_add(til_pos, 1));
    if (_status__tmp49 == 1) { *_err1 = _err0__tmp49; return 1; }
    if (_status__tmp49 == 2) { *_err2 = _err1__tmp49; return 2; }
    *_ret = _ret__tmp49;
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
                til_Array _tmp50;
        til_AllocError _err_alloc__tmp51;
        til_IndexOutOfBoundsError _err_idx__tmp51;
        til_Str _tmp52 = til_Str_from_literal("concat: integer overflow");
        int _arr_status__tmp51 = til_Array_new(&_tmp50, &_err_alloc__tmp51, "Str", 1);
        if (_arr_status__tmp51 != 0) {
        }
        _arr_status__tmp51 = til_Array_set(&_err_idx__tmp51, &_tmp50, 0, &_tmp52);
        if (_arr_status__tmp51 != 0) {
        }
til_panic(til_Str_from_literal(""), &_tmp50);
        til_Array_delete(&_tmp50);
    }
    til_I64 _ret__tmp53;
    til_AllocError _err0__tmp53 = {};
    int _status__tmp53 = til_malloc(&_ret__tmp53, &_err0__tmp53, til_result.cap);
    if (_status__tmp53 == 0) {
        til_result.c_string = _ret__tmp53;
    } else if (_status__tmp53 == 1) {
        til_AllocError til_err = _err0__tmp53;
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
til_panic(til_Str_from_literal(""), &_tmp54);
        til_Array_delete(&_tmp54);
    }
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
                til_Array _tmp57;
        til_AllocError _err_alloc__tmp58;
        til_IndexOutOfBoundsError _err_idx__tmp58;
        til_Str _tmp59 = til_Str_from_literal("concat: malloc failed");
        int _arr_status__tmp58 = til_Array_new(&_tmp57, &_err_alloc__tmp58, "Str", 1);
        if (_arr_status__tmp58 != 0) {
        }
        _arr_status__tmp58 = til_Array_set(&_err_idx__tmp58, &_tmp57, 0, &_tmp59);
        if (_arr_status__tmp58 != 0) {
        }
til_panic(til_Str_from_literal(""), &_tmp57);
        til_Array_delete(&_tmp57);
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
        til_IndexOutOfBoundsError _err0__tmp60 = {};
        int _status__tmp60 = til_Array_get(&_err0__tmp60, (*til_args), til_i, (til_Dynamic*)&til_arg);
        if (_status__tmp60 == 1) { *_err2 = _err0__tmp60; return 2; }
        til_result.cap = til_add(til_result.cap, til_arg.cap);
        if (til_lt(til_result.cap, til_arg.cap).data) {
            til_Str _tmp61;
            til_I64_OverflowError _err0__tmp62;
            til_IndexOutOfBoundsError _err1__tmp62;
            til_AllocError _err2__tmp62;
            til_Array _tmp63;
            til_AllocError _err_alloc__tmp64;
            til_IndexOutOfBoundsError _err_idx__tmp64;
            til_Str _tmp65 = til_Str_from_literal("format: integer overflow while summing cap for arg ");
            til_Str _tmp66 = til_I64_to_str(til_i);
            int _arr_status__tmp64 = til_Array_new(&_tmp63, &_err_alloc__tmp64, "Str", 2);
            if (_arr_status__tmp64 != 0) {
                *_err3 = _err_alloc__tmp64; return 3;
            }
            _arr_status__tmp64 = til_Array_set(&_err_idx__tmp64, &_tmp63, 0, &_tmp65);
            if (_arr_status__tmp64 != 0) {
                *_err2 = _err_idx__tmp64; return 2;
            }
            _arr_status__tmp64 = til_Array_set(&_err_idx__tmp64, &_tmp63, 1, &_tmp66);
            if (_arr_status__tmp64 != 0) {
                *_err2 = _err_idx__tmp64; return 2;
            }
            int _status__tmp62 = til_format(&_tmp61, &_err0__tmp62, &_err1__tmp62, &_err2__tmp62, til_Str_from_literal(""), &_tmp63);
            if (_status__tmp62 != 0) {
                if (_status__tmp62 == 1) { *_err1 = _err0__tmp62; return 1; }
                if (_status__tmp62 == 2) { *_err2 = _err1__tmp62; return 2; }
                if (_status__tmp62 == 3) { *_err3 = _err2__tmp62; return 3; }
            }
            til_Array_delete(&_tmp63);
            *_err1 = til_I64_OverflowError_new(_tmp61);
            return 1;
        }
        til_I64_inc(til_i);
    }
    til_I64 _ret__tmp67;
    til_AllocError _err0__tmp67 = {};
    int _status__tmp67 = til_malloc(&_ret__tmp67, &_err0__tmp67, til_result.cap);
    if (_status__tmp67 == 1) { *_err3 = _err0__tmp67; return 3; }
    til_result.c_string = _ret__tmp67;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Str _tmp68;
        til_I64_OverflowError _err0__tmp69;
        til_IndexOutOfBoundsError _err1__tmp69;
        til_AllocError _err2__tmp69;
        til_Array _tmp70;
        til_AllocError _err_alloc__tmp71;
        til_IndexOutOfBoundsError _err_idx__tmp71;
        til_Str _tmp72 = til_Str_from_literal("format: malloc failed for cap = ");
        til_Str _tmp73 = til_I64_to_str(til_result.cap);
        int _arr_status__tmp71 = til_Array_new(&_tmp70, &_err_alloc__tmp71, "Str", 2);
        if (_arr_status__tmp71 != 0) {
            *_err3 = _err_alloc__tmp71; return 3;
        }
        _arr_status__tmp71 = til_Array_set(&_err_idx__tmp71, &_tmp70, 0, &_tmp72);
        if (_arr_status__tmp71 != 0) {
            *_err2 = _err_idx__tmp71; return 2;
        }
        _arr_status__tmp71 = til_Array_set(&_err_idx__tmp71, &_tmp70, 1, &_tmp73);
        if (_arr_status__tmp71 != 0) {
            *_err2 = _err_idx__tmp71; return 2;
        }
        int _status__tmp69 = til_format(&_tmp68, &_err0__tmp69, &_err1__tmp69, &_err2__tmp69, til_Str_from_literal(""), &_tmp70);
        if (_status__tmp69 != 0) {
            if (_status__tmp69 == 1) { *_err1 = _err0__tmp69; return 1; }
            if (_status__tmp69 == 2) { *_err2 = _err1__tmp69; return 2; }
            if (_status__tmp69 == 3) { *_err3 = _err2__tmp69; return 3; }
        }
        til_Array_delete(&_tmp70);
        *_err3 = til_AllocError_new(_tmp68);
        return 3;
    }
    til_I64 til_offset = 0;
    til_memcpy(til_result.c_string, til_prefix.c_string, til_prefix.cap);
    til_offset = til_prefix.cap;
    til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Str til_s = til_Str_from_literal("");
        til_IndexOutOfBoundsError _err0__tmp74 = {};
        int _status__tmp74 = til_Array_get(&_err0__tmp74, (*til_args), til_i, (til_Dynamic*)&til_s);
        if (_status__tmp74 == 1) { *_err2 = _err0__tmp74; return 2; }
        til_memcpy(til_add(til_result.c_string, til_offset), til_s.c_string, til_s.cap);
        til_offset = til_add(til_offset, til_s.cap);
        til_I64_inc(til_i);
    }
    *_ret = til_result;
    return 0;
}

void til_panic(const til_Str til_loc_str, til_Array* til_msgs) {
    til_single_print(til_loc_str);
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_msgs))).data) {
        til_Str til_val = til_Str_from_literal("");
        til_IndexOutOfBoundsError _err0__tmp75 = {};
        int _status__tmp75 = til_Array_get(&_err0__tmp75, (*til_msgs), til_i, (til_Dynamic*)&til_val);
        til_single_print(til_val);
        til_I64_inc(til_i);
    }
    til_single_print(til_Str_from_literal("\n"));
    til_print_flush();
    til_exit(1);
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
    til_arr.type_size = sizeof(til_T);
    const til_I64 til_size_bytes = til_mul(til_capacity, til_arr.type_size);
    til_I64 _ret__tmp76;
    til_AllocError _err0__tmp76 = {};
    int _status__tmp76 = til_malloc(&_ret__tmp76, &_err0__tmp76, til_size_bytes);
    if (_status__tmp76 == 1) { *_err1 = _err0__tmp76; return 1; }
    til_arr.ptr = _ret__tmp76;
    til_U8 _tmp77;
    til_U8_OverflowError _err0__tmp78;
    int _status__tmp78 = til_U8_from_i64(&_tmp77, &_err0__tmp78, 0);
    if (_status__tmp78 != 0) {
    }
    til_memset(til_arr.ptr, _tmp77, til_size_bytes);
    til_arr._len = til_capacity;
    *_ret = til_arr;
    return 0;
}

int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array til_self, const til_I64 til_index, til_Dynamic* til_T) {
    if (til_gteq(til_index, til_self._len).data) {
        til_Str _tmp79;
        til_I64_OverflowError _err0__tmp80;
        til_IndexOutOfBoundsError _err1__tmp80;
        til_AllocError _err2__tmp80;
        til_Array _tmp81;
        til_AllocError _err_alloc__tmp82;
        til_IndexOutOfBoundsError _err_idx__tmp82;
        til_Str _tmp83 = til_Str_from_literal("Array.get: index out of bounds");
        int _arr_status__tmp82 = til_Array_new(&_tmp81, &_err_alloc__tmp82, "Str", 1);
        if (_arr_status__tmp82 != 0) {
        }
        _arr_status__tmp82 = til_Array_set(&_err_idx__tmp82, &_tmp81, 0, &_tmp83);
        if (_arr_status__tmp82 != 0) {
            *_err1 = _err_idx__tmp82; return 1;
        }
        int _status__tmp80 = til_format(&_tmp79, &_err0__tmp80, &_err1__tmp80, &_err2__tmp80, til_Str_from_literal(""), &_tmp81);
        if (_status__tmp80 != 0) {
            if (_status__tmp80 == 2) { *_err1 = _err1__tmp80; return 1; }
        }
        til_Array_delete(&_tmp81);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp79);
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)(*til_T);
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_gteq(til_index, til_self->_len).data) {
        til_Str _tmp84;
        til_I64_OverflowError _err0__tmp85;
        til_IndexOutOfBoundsError _err1__tmp85;
        til_AllocError _err2__tmp85;
        til_Array _tmp86;
        til_AllocError _err_alloc__tmp87;
        til_IndexOutOfBoundsError _err_idx__tmp87;
        til_Str _tmp88 = til_Str_from_literal("Array.set: index out of bounds");
        int _arr_status__tmp87 = til_Array_new(&_tmp86, &_err_alloc__tmp87, "Str", 1);
        if (_arr_status__tmp87 != 0) {
        }
        _arr_status__tmp87 = til_Array_set(&_err_idx__tmp87, &_tmp86, 0, &_tmp88);
        if (_arr_status__tmp87 != 0) {
            *_err1 = _err_idx__tmp87; return 1;
        }
        int _status__tmp85 = til_format(&_tmp84, &_err0__tmp85, &_err1__tmp85, &_err2__tmp85, til_Str_from_literal(""), &_tmp86);
        if (_status__tmp85 != 0) {
            if (_status__tmp85 == 2) { *_err1 = _err1__tmp85; return 1; }
        }
        til_Array_delete(&_tmp86);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp84);
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
    til_I64 _ret__tmp89;
    til_AllocError _err0__tmp89 = {};
    int _status__tmp89 = til_malloc(&_ret__tmp89, &_err0__tmp89, til_total_bytes);
    if (_status__tmp89 == 1) { *_err1 = _err0__tmp89; return 1; }
    til_cloned.ptr = _ret__tmp89;
    if (til_I64_eq(til_NULL, til_cloned.ptr).data) {
        til_Str _tmp90;
        til_I64_OverflowError _err0__tmp91;
        til_IndexOutOfBoundsError _err1__tmp91;
        til_AllocError _err2__tmp91;
        til_Array _tmp92;
        til_AllocError _err_alloc__tmp93;
        til_IndexOutOfBoundsError _err_idx__tmp93;
        til_Str _tmp94 = til_Str_from_literal("Array.clone: malloc failed for ");
        til_Str _tmp95 = til_I64_to_str(til_total_bytes);
        til_Str _tmp96 = til_Str_from_literal(" bytes");
        int _arr_status__tmp93 = til_Array_new(&_tmp92, &_err_alloc__tmp93, "Str", 3);
        if (_arr_status__tmp93 != 0) {
            *_err1 = _err_alloc__tmp93; return 1;
        }
        _arr_status__tmp93 = til_Array_set(&_err_idx__tmp93, &_tmp92, 0, &_tmp94);
        if (_arr_status__tmp93 != 0) {
        }
        _arr_status__tmp93 = til_Array_set(&_err_idx__tmp93, &_tmp92, 1, &_tmp95);
        if (_arr_status__tmp93 != 0) {
        }
        _arr_status__tmp93 = til_Array_set(&_err_idx__tmp93, &_tmp92, 2, &_tmp96);
        if (_arr_status__tmp93 != 0) {
        }
        int _status__tmp91 = til_format(&_tmp90, &_err0__tmp91, &_err1__tmp91, &_err2__tmp91, til_Str_from_literal(""), &_tmp92);
        if (_status__tmp91 != 0) {
            if (_status__tmp91 == 3) { *_err1 = _err2__tmp91; return 1; }
        }
        til_Array_delete(&_tmp92);
        *_err1 = til_AllocError_new(_tmp90);
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
        til_IndexOutOfBoundsError _err0__tmp97 = {};
        int _status__tmp97 = til_Array_get(&_err0__tmp97, til_self, til_i, (til_Dynamic*)&til_elem);
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
    til_Bool _tmp98;
    til_Array _tmp99;
    til_AllocError _err_alloc__tmp100;
    til_IndexOutOfBoundsError _err_idx__tmp100;
    til_Bool _tmp101 = til_a;
    til_Bool _tmp102 = til_b;
    int _arr_status__tmp100 = til_Array_new(&_tmp99, &_err_alloc__tmp100, "Bool", 2);
    if (_arr_status__tmp100 != 0) {
    }
    _arr_status__tmp100 = til_Array_set(&_err_idx__tmp100, &_tmp99, 0, &_tmp101);
    if (_arr_status__tmp100 != 0) {
    }
    _arr_status__tmp100 = til_Array_set(&_err_idx__tmp100, &_tmp99, 1, &_tmp102);
    if (_arr_status__tmp100 != 0) {
    }
    _tmp98 = til_and(&_tmp99);
    til_Array_delete(&_tmp99);
    til_Bool _tmp103;
    til_Array _tmp104;
    til_AllocError _err_alloc__tmp105;
    til_IndexOutOfBoundsError _err_idx__tmp105;
    til_Bool _tmp106 = til_not(til_b);
    til_Bool _tmp107 = til_not(til_a);
    int _arr_status__tmp105 = til_Array_new(&_tmp104, &_err_alloc__tmp105, "Bool", 2);
    if (_arr_status__tmp105 != 0) {
    }
    _arr_status__tmp105 = til_Array_set(&_err_idx__tmp105, &_tmp104, 0, &_tmp106);
    if (_arr_status__tmp105 != 0) {
    }
    _arr_status__tmp105 = til_Array_set(&_err_idx__tmp105, &_tmp104, 1, &_tmp107);
    if (_arr_status__tmp105 != 0) {
    }
    _tmp103 = til_and(&_tmp104);
    til_Array_delete(&_tmp104);
    til_Array _tmp108;
    til_AllocError _err_alloc__tmp109;
    til_IndexOutOfBoundsError _err_idx__tmp109;
    int _arr_status__tmp109 = til_Array_new(&_tmp108, &_err_alloc__tmp109, "Bool", 2);
    if (_arr_status__tmp109 != 0) {
    }
    _arr_status__tmp109 = til_Array_set(&_err_idx__tmp109, &_tmp108, 0, &_tmp98);
    if (_arr_status__tmp109 != 0) {
    }
    _arr_status__tmp109 = til_Array_set(&_err_idx__tmp109, &_tmp108, 1, &_tmp103);
    if (_arr_status__tmp109 != 0) {
    }
    til_Bool _tmp110 = til_or(&_tmp108);
    til_Array_delete(&_tmp108);
    return _tmp110;
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
    til_vec.type_size = sizeof(til_T);
    const til_I64 til_size_bytes = til_mul(til_Vec_INIT_CAP, til_vec.type_size);
    til_I64 _ret__tmp111;
    til_AllocError _err0__tmp111 = {};
    int _status__tmp111 = til_malloc(&_ret__tmp111, &_err0__tmp111, til_size_bytes);
    if (_status__tmp111 == 1) { *_err1 = _err0__tmp111; return 1; }
    til_vec.ptr = _ret__tmp111;
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
    til_I64 _ret__tmp112;
    til_AllocError _err0__tmp112 = {};
    int _status__tmp112 = til_malloc(&_ret__tmp112, &_err0__tmp112, til_size_bytes);
    if (_status__tmp112 == 1) { *_err1 = _err0__tmp112; return 1; }
    til_vec.ptr = _ret__tmp112;
    til_vec._len = 0;
    til_vec.cap = til_Vec_INIT_CAP;
    *_ret = til_vec;
    return 0;
}

int til_Vec_push(til_AllocError* _err1, til_Vec* til_self, const til_Dynamic til_value) {
    if (til_I64_eq(til_self->_len, til_self->cap).data) {
        const til_I64 til_new_cap = til_mul(til_self->cap, 2);
        if (til_gt(til_new_cap, til_Vec_MAX_CAP).data) {
                        til_Array _tmp113;
            til_AllocError _err_alloc__tmp114;
            til_IndexOutOfBoundsError _err_idx__tmp114;
            til_Str _tmp115 = til_Str_from_literal("Vec.push: capacity exceeded Vec.MAX_CAP");
            int _arr_status__tmp114 = til_Array_new(&_tmp113, &_err_alloc__tmp114, "Str", 1);
            if (_arr_status__tmp114 != 0) {
                *_err1 = _err_alloc__tmp114; return 1;
            }
            _arr_status__tmp114 = til_Array_set(&_err_idx__tmp114, &_tmp113, 0, &_tmp115);
            if (_arr_status__tmp114 != 0) {
            }
til_panic(til_Str_from_literal(""), &_tmp113);
            til_Array_delete(&_tmp113);
        }
        til_I64 _ret__tmp116;
        til_I64 til_new_ptr;
        til_AllocError _err0__tmp116 = {};
        int _status__tmp116 = til_malloc(&_ret__tmp116, &_err0__tmp116, til_mul(til_new_cap, til_self->type_size));
        if (_status__tmp116 == 1) { *_err1 = _err0__tmp116; return 1; }
        til_new_ptr = _ret__tmp116;
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
        til_Str _tmp117;
        til_I64_OverflowError _err0__tmp118;
        til_IndexOutOfBoundsError _err1__tmp118;
        til_AllocError _err2__tmp118;
        til_Array _tmp119;
        til_AllocError _err_alloc__tmp120;
        til_IndexOutOfBoundsError _err_idx__tmp120;
        til_Str _tmp121 = til_Str_from_literal("Vec.get: index out of bounds");
        int _arr_status__tmp120 = til_Array_new(&_tmp119, &_err_alloc__tmp120, "Str", 1);
        if (_arr_status__tmp120 != 0) {
        }
        _arr_status__tmp120 = til_Array_set(&_err_idx__tmp120, &_tmp119, 0, &_tmp121);
        if (_arr_status__tmp120 != 0) {
            *_err1 = _err_idx__tmp120; return 1;
        }
        int _status__tmp118 = til_format(&_tmp117, &_err0__tmp118, &_err1__tmp118, &_err2__tmp118, til_Str_from_literal(""), &_tmp119);
        if (_status__tmp118 != 0) {
            if (_status__tmp118 == 2) { *_err1 = _err1__tmp118; return 1; }
        }
        til_Array_delete(&_tmp119);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp117);
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)(*til_T);
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Vec_set(til_IndexOutOfBoundsError* _err1, til_Vec* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_gteq(til_index, til_self->_len).data) {
        til_Str _tmp122;
        til_I64_OverflowError _err0__tmp123;
        til_IndexOutOfBoundsError _err1__tmp123;
        til_AllocError _err2__tmp123;
        til_Array _tmp124;
        til_AllocError _err_alloc__tmp125;
        til_IndexOutOfBoundsError _err_idx__tmp125;
        til_Str _tmp126 = til_Str_from_literal("Vec.set: index out of bounds");
        int _arr_status__tmp125 = til_Array_new(&_tmp124, &_err_alloc__tmp125, "Str", 1);
        if (_arr_status__tmp125 != 0) {
        }
        _arr_status__tmp125 = til_Array_set(&_err_idx__tmp125, &_tmp124, 0, &_tmp126);
        if (_arr_status__tmp125 != 0) {
            *_err1 = _err_idx__tmp125; return 1;
        }
        int _status__tmp123 = til_format(&_tmp122, &_err0__tmp123, &_err1__tmp123, &_err2__tmp123, til_Str_from_literal(""), &_tmp124);
        if (_status__tmp123 != 0) {
            if (_status__tmp123 == 2) { *_err1 = _err1__tmp123; return 1; }
        }
        til_Array_delete(&_tmp124);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp122);
        return 1;
    }
    til_I64 til_dest = til_add(til_self->ptr, til_mul(til_index, til_self->type_size));
    til_memcpy(til_dest, (til_I64)til_value, til_self->type_size);
    return 0;
}

int til_Vec_pop(til_IndexOutOfBoundsError* _err1, til_Vec* til_self, til_Dynamic* til_dest) {
    if (til_I64_eq(til_self->_len, 0).data) {
        til_Str _tmp127;
        til_I64_OverflowError _err0__tmp128;
        til_IndexOutOfBoundsError _err1__tmp128;
        til_AllocError _err2__tmp128;
        til_Array _tmp129;
        til_AllocError _err_alloc__tmp130;
        til_IndexOutOfBoundsError _err_idx__tmp130;
        til_Str _tmp131 = til_Str_from_literal("Vec.pop: cannot pop from empty Vec");
        int _arr_status__tmp130 = til_Array_new(&_tmp129, &_err_alloc__tmp130, "Str", 1);
        if (_arr_status__tmp130 != 0) {
        }
        _arr_status__tmp130 = til_Array_set(&_err_idx__tmp130, &_tmp129, 0, &_tmp131);
        if (_arr_status__tmp130 != 0) {
            *_err1 = _err_idx__tmp130; return 1;
        }
        int _status__tmp128 = til_format(&_tmp127, &_err0__tmp128, &_err1__tmp128, &_err2__tmp128, til_Str_from_literal(""), &_tmp129);
        if (_status__tmp128 != 0) {
            if (_status__tmp128 == 2) { *_err1 = _err1__tmp128; return 1; }
        }
        til_Array_delete(&_tmp129);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp127);
        return 1;
    }
    til_I64 til_last_index = til_sub(til_self->_len, 1);
    til_IndexOutOfBoundsError _err0__tmp132 = {};
    int _status__tmp132 = til_Vec_get(&_err0__tmp132, (*til_self), til_last_index, (til_Dynamic*)&til_dest);
    if (_status__tmp132 == 1) { *_err1 = _err0__tmp132; return 1; }
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
    til_I64 _ret__tmp133;
    til_AllocError _err0__tmp133 = {};
    int _status__tmp133 = til_malloc(&_ret__tmp133, &_err0__tmp133, til_total_bytes);
    if (_status__tmp133 == 1) { *_err1 = _err0__tmp133; return 1; }
    til_cloned.ptr = _ret__tmp133;
    if (til_I64_eq(til_NULL, til_cloned.ptr).data) {
        til_Str _tmp134;
        til_I64_OverflowError _err0__tmp135;
        til_IndexOutOfBoundsError _err1__tmp135;
        til_AllocError _err2__tmp135;
        til_Array _tmp136;
        til_AllocError _err_alloc__tmp137;
        til_IndexOutOfBoundsError _err_idx__tmp137;
        til_Str _tmp138 = til_Str_from_literal("Vec.clone: malloc failed for ");
        til_Str _tmp139 = til_I64_to_str(til_total_bytes);
        til_Str _tmp140 = til_Str_from_literal(" bytes");
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
        int _status__tmp135 = til_format(&_tmp134, &_err0__tmp135, &_err1__tmp135, &_err2__tmp135, til_Str_from_literal(""), &_tmp136);
        if (_status__tmp135 != 0) {
            if (_status__tmp135 == 3) { *_err1 = _err2__tmp135; return 1; }
        }
        til_Array_delete(&_tmp136);
        *_err1 = til_AllocError_new(_tmp134);
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
                                til_Array _tmp141;
                til_AllocError _err_alloc__tmp142;
                til_IndexOutOfBoundsError _err_idx__tmp142;
                til_Str _tmp143 = til_Str_from_literal("Vec.extend: capacity exceeded Vec.MAX_CAP");
                int _arr_status__tmp142 = til_Array_new(&_tmp141, &_err_alloc__tmp142, "Str", 1);
                if (_arr_status__tmp142 != 0) {
                    *_err1 = _err_alloc__tmp142; return 1;
                }
                _arr_status__tmp142 = til_Array_set(&_err_idx__tmp142, &_tmp141, 0, &_tmp143);
                if (_arr_status__tmp142 != 0) {
                }
til_panic(til_Str_from_literal(""), &_tmp141);
                til_Array_delete(&_tmp141);
            }
            til_I64 _ret__tmp144;
            til_I64 til_new_ptr;
            til_AllocError _err0__tmp144 = {};
            int _status__tmp144 = til_malloc(&_ret__tmp144, &_err0__tmp144, til_mul(til_new_cap, til_self->type_size));
            if (_status__tmp144 == 1) { *_err1 = _err0__tmp144; return 1; }
            til_new_ptr = _ret__tmp144;
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
        til_Str _tmp145;
        til_I64_OverflowError _err0__tmp146;
        til_IndexOutOfBoundsError _err1__tmp146;
        til_AllocError _err2__tmp146;
        til_Array _tmp147;
        til_AllocError _err_alloc__tmp148;
        til_IndexOutOfBoundsError _err_idx__tmp148;
        til_Str _tmp149 = til_Str_from_literal("Vec.remove: index out of bounds");
        int _arr_status__tmp148 = til_Array_new(&_tmp147, &_err_alloc__tmp148, "Str", 1);
        if (_arr_status__tmp148 != 0) {
        }
        _arr_status__tmp148 = til_Array_set(&_err_idx__tmp148, &_tmp147, 0, &_tmp149);
        if (_arr_status__tmp148 != 0) {
            *_err1 = _err_idx__tmp148; return 1;
        }
        int _status__tmp146 = til_format(&_tmp145, &_err0__tmp146, &_err1__tmp146, &_err2__tmp146, til_Str_from_literal(""), &_tmp147);
        if (_status__tmp146 != 0) {
            if (_status__tmp146 == 2) { *_err1 = _err1__tmp146; return 1; }
        }
        til_Array_delete(&_tmp147);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp145);
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
        til_I64_inc(til_i);
    }
    return true;
}

til_I64 til_Str_to_i64(const til_Str til_self) {
    return til_I64_from_str(til_self);
}

int til_Str_clone(til_Str* _ret, til_AllocError* _err1, const til_Str til_self) {
    til_Str til_cloned = {0};
    til_cloned.cap = til_self.cap;
    til_I64 _ret__tmp150;
    til_AllocError _err0__tmp150 = {};
    int _status__tmp150 = til_malloc(&_ret__tmp150, &_err0__tmp150, til_cloned.cap);
    if (_status__tmp150 == 1) { *_err1 = _err0__tmp150; return 1; }
    til_cloned.c_string = _ret__tmp150;
    if (til_I64_eq(til_NULL, til_cloned.c_string).data) {
        til_Str _tmp151;
        til_I64_OverflowError _err0__tmp152;
        til_IndexOutOfBoundsError _err1__tmp152;
        til_AllocError _err2__tmp152;
        til_Array _tmp153;
        til_AllocError _err_alloc__tmp154;
        til_IndexOutOfBoundsError _err_idx__tmp154;
        til_Str _tmp155 = til_Str_from_literal("Str.clone: malloc failed for ");
        til_Str _tmp156 = til_I64_to_str(til_cloned.cap);
        til_Str _tmp157 = til_Str_from_literal(" bytes");
        int _arr_status__tmp154 = til_Array_new(&_tmp153, &_err_alloc__tmp154, "Str", 3);
        if (_arr_status__tmp154 != 0) {
            *_err1 = _err_alloc__tmp154; return 1;
        }
        _arr_status__tmp154 = til_Array_set(&_err_idx__tmp154, &_tmp153, 0, &_tmp155);
        if (_arr_status__tmp154 != 0) {
        }
        _arr_status__tmp154 = til_Array_set(&_err_idx__tmp154, &_tmp153, 1, &_tmp156);
        if (_arr_status__tmp154 != 0) {
        }
        _arr_status__tmp154 = til_Array_set(&_err_idx__tmp154, &_tmp153, 2, &_tmp157);
        if (_arr_status__tmp154 != 0) {
        }
        int _status__tmp152 = til_format(&_tmp151, &_err0__tmp152, &_err1__tmp152, &_err2__tmp152, til_Str_from_literal(""), &_tmp153);
        if (_status__tmp152 != 0) {
            if (_status__tmp152 == 3) { *_err1 = _err2__tmp152; return 1; }
        }
        til_Array_delete(&_tmp153);
        *_err1 = til_AllocError_new(_tmp151);
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
        til_I64_inc(til_i);
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
            til_I64_inc(til_needle_idx);
        }
        if (til_matches.data) {
            return true;
        }
        til_I64_inc(til_start_idx);
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
            til_I64_inc(til_needle_idx);
        }
        if (til_matches.data) {
            return til_start_idx;
        }
        til_I64_inc(til_start_idx);
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
            til_I64_inc(til_needle_idx);
        }
        if (til_matches.data) {
            til_last_found = til_start_idx;
        }
        til_I64_inc(til_start_idx);
    }
    return til_last_found;
}

int til_Str_replace(til_Str* _ret, til_AllocError* _err1, const til_Str til_self, const til_Str til_from, const til_Str til_to) {
    if (til_I64_eq(til_Str_len(til_from), 0).data) {
        til_Str _ret__tmp158;
        til_AllocError _err0__tmp158 = {};
        int _status__tmp158 = til_Str_clone(&_ret__tmp158, &_err0__tmp158, til_self);
        if (_status__tmp158 == 1) { *_err1 = _err0__tmp158; return 1; }
        *_ret = _ret__tmp158;
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
            til_I64_inc(til_i);
        }
        if (til_matches.data) {
            til_count = til_add(til_count, 1);
            til_search_start = til_add(til_search_start, til_Str_len(til_from));
        } else {
            til_search_start = til_add(til_search_start, 1);
        }
    }
    if (til_I64_eq(til_count, 0).data) {
        til_Str _ret__tmp159;
        til_AllocError _err0__tmp159 = {};
        int _status__tmp159 = til_Str_clone(&_ret__tmp159, &_err0__tmp159, til_self);
        if (_status__tmp159 == 1) { *_err1 = _err0__tmp159; return 1; }
        *_ret = _ret__tmp159;
        return 0;
    }
    til_I64 til_new_len = til_add(til_sub(til_Str_len(til_self), til_mul(til_count, til_Str_len(til_from))), til_mul(til_count, til_Str_len(til_to)));
    til_Str til_result = {0};
    til_result.cap = til_new_len;
    til_I64 _ret__tmp160;
    til_AllocError _err0__tmp160 = {};
    int _status__tmp160 = til_malloc(&_ret__tmp160, &_err0__tmp160, til_new_len);
    if (_status__tmp160 == 1) { *_err1 = _err0__tmp160; return 1; }
    til_result.c_string = _ret__tmp160;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Str _tmp161;
        til_I64_OverflowError _err0__tmp162;
        til_IndexOutOfBoundsError _err1__tmp162;
        til_AllocError _err2__tmp162;
        til_Array _tmp163;
        til_AllocError _err_alloc__tmp164;
        til_IndexOutOfBoundsError _err_idx__tmp164;
        til_Str _tmp165 = til_Str_from_literal("Str.replace: malloc failed for ");
        til_Str _tmp166 = til_I64_to_str(til_new_len);
        til_Str _tmp167 = til_Str_from_literal(" bytes");
        int _arr_status__tmp164 = til_Array_new(&_tmp163, &_err_alloc__tmp164, "Str", 3);
        if (_arr_status__tmp164 != 0) {
            *_err1 = _err_alloc__tmp164; return 1;
        }
        _arr_status__tmp164 = til_Array_set(&_err_idx__tmp164, &_tmp163, 0, &_tmp165);
        if (_arr_status__tmp164 != 0) {
        }
        _arr_status__tmp164 = til_Array_set(&_err_idx__tmp164, &_tmp163, 1, &_tmp166);
        if (_arr_status__tmp164 != 0) {
        }
        _arr_status__tmp164 = til_Array_set(&_err_idx__tmp164, &_tmp163, 2, &_tmp167);
        if (_arr_status__tmp164 != 0) {
        }
        int _status__tmp162 = til_format(&_tmp161, &_err0__tmp162, &_err1__tmp162, &_err2__tmp162, til_Str_from_literal(""), &_tmp163);
        if (_status__tmp162 != 0) {
            if (_status__tmp162 == 3) { *_err1 = _err2__tmp162; return 1; }
        }
        til_Array_delete(&_tmp163);
        *_err1 = til_AllocError_new(_tmp161);
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
                til_I64_inc(til_i);
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

int til_Str_split(til_Vec* _ret, til_AllocError* _err1, til_IndexOutOfBoundsError* _err2, const til_Str til_self, const til_Str til_delimiter) {
    til_Vec _ret__tmp168;
    til_Vec til_parts;
    til_AllocError _err0__tmp168 = {};
    int _status__tmp168 = til_Vec_new(&_ret__tmp168, &_err0__tmp168, "Str");
    if (_status__tmp168 == 1) { *_err1 = _err0__tmp168; return 1; }
    til_parts = _ret__tmp168;
    if (til_I64_eq(til_Str_len(til_delimiter), 0).data) {
        til_Str _tmp170;
        til_AllocError _err0__tmp171;
        int _status__tmp171 = til_Str_clone(&_tmp170, &_err0__tmp171, til_self);
        if (_status__tmp171 != 0) {
            if (_status__tmp171 == 1) { *_err1 = _err0__tmp171; return 1; }
        }
        til_AllocError _err0__tmp169 = {};
        int _status__tmp169 = til_Vec_push(&_err0__tmp169, &til_parts, &_tmp170);
        if (_status__tmp169 == 1) { *_err1 = _err0__tmp169; return 1; }
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
            til_I64_inc(til_i);
        }
        if (til_matches.data) {
            if (til_gt(til_pos, til_start).data) {
                til_Str _ret__tmp172;
                til_Str til_part;
                til_IndexOutOfBoundsError _err0__tmp172 = {};
                til_AllocError _err1__tmp172 = {};
                int _status__tmp172 = til_get_substr(&_ret__tmp172, &_err0__tmp172, &_err1__tmp172, til_self, til_start, til_pos);
                if (_status__tmp172 == 1) { *_err2 = _err0__tmp172; return 2; }
                if (_status__tmp172 == 2) { *_err1 = _err1__tmp172; return 1; }
                til_part = _ret__tmp172;
                til_AllocError _err0__tmp173 = {};
                int _status__tmp173 = til_Vec_push(&_err0__tmp173, &til_parts, (til_Dynamic*)&til_part);
                if (_status__tmp173 == 1) { *_err1 = _err0__tmp173; return 1; }
            } else {
                til_Str _tmp175 = til_Str_from_literal("");
                til_AllocError _err0__tmp174 = {};
                int _status__tmp174 = til_Vec_push(&_err0__tmp174, &til_parts, &_tmp175);
                if (_status__tmp174 == 1) { *_err1 = _err0__tmp174; return 1; }
            }
            til_start = til_add(til_pos, til_Str_len(til_delimiter));
            til_pos = til_start;
        } else {
            til_pos = til_add(til_pos, 1);
        }
    }
    if (til_lt(til_start, til_Str_len(til_self)).data) {
        til_Str _ret__tmp176;
        til_Str til_part;
        til_IndexOutOfBoundsError _err0__tmp176 = {};
        til_AllocError _err1__tmp176 = {};
        int _status__tmp176 = til_get_substr(&_ret__tmp176, &_err0__tmp176, &_err1__tmp176, til_self, til_start, til_Str_len(til_self));
        if (_status__tmp176 == 1) { *_err2 = _err0__tmp176; return 2; }
        if (_status__tmp176 == 2) { *_err1 = _err1__tmp176; return 1; }
        til_part = _ret__tmp176;
        til_AllocError _err0__tmp177 = {};
        int _status__tmp177 = til_Vec_push(&_err0__tmp177, &til_parts, (til_Dynamic*)&til_part);
        if (_status__tmp177 == 1) { *_err1 = _err0__tmp177; return 1; }
    } else {
        if (til_I64_eq(til_start, til_Str_len(til_self)).data) {
            til_Str _tmp179 = til_Str_from_literal("");
            til_AllocError _err0__tmp178 = {};
            int _status__tmp178 = til_Vec_push(&_err0__tmp178, &til_parts, &_tmp179);
            if (_status__tmp178 == 1) { *_err1 = _err0__tmp178; return 1; }
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

til_I64 til_U8_to_i64(const til_U8 til_self) {
    return til_u8_to_i64(til_self);
}

int til_U8_u8_add(til_U8* _ret, til_U8_OverflowError* _err1, const til_U8 til_a, const til_U8 til_b) {
    til_U8 _ret__tmp180;
    til_U8_OverflowError _err0__tmp180 = {};
    int _status__tmp180 = til_U8_from_i64(&_ret__tmp180, &_err0__tmp180, til_add(til_U8_to_i64(til_a), til_U8_to_i64(til_b)));
    if (_status__tmp180 == 1) { *_err1 = _err0__tmp180; return 1; }
    *_ret = _ret__tmp180;
    return 0;
}

int til_U8_from_i64(til_U8* _ret, til_U8_OverflowError* _err1, const til_I64 til_self) {
    if (til_lt(til_self, 0).data) {
        til_Str _tmp181;
        til_I64_OverflowError _err0__tmp182;
        til_IndexOutOfBoundsError _err1__tmp182;
        til_AllocError _err2__tmp182;
        til_Array _tmp183;
        til_AllocError _err_alloc__tmp184;
        til_IndexOutOfBoundsError _err_idx__tmp184;
        til_Str _tmp185 = til_Str_from_literal("Negative values cannot be cast into 'U8'");
        int _arr_status__tmp184 = til_Array_new(&_tmp183, &_err_alloc__tmp184, "Str", 1);
        if (_arr_status__tmp184 != 0) {
        }
        _arr_status__tmp184 = til_Array_set(&_err_idx__tmp184, &_tmp183, 0, &_tmp185);
        if (_arr_status__tmp184 != 0) {
        }
        int _status__tmp182 = til_format(&_tmp181, &_err0__tmp182, &_err1__tmp182, &_err2__tmp182, til_Str_from_literal(""), &_tmp183);
        if (_status__tmp182 != 0) {
        }
        til_Array_delete(&_tmp183);
        *_err1 = til_U8_OverflowError_new(_tmp181);
        return 1;
    }
    if (til_gt(til_self, til_MAX_U8).data) {
        til_Str _tmp186;
        til_I64_OverflowError _err0__tmp187;
        til_IndexOutOfBoundsError _err1__tmp187;
        til_AllocError _err2__tmp187;
        til_Array _tmp188;
        til_AllocError _err_alloc__tmp189;
        til_IndexOutOfBoundsError _err_idx__tmp189;
        til_Str _tmp190 = til_Str_from_literal("U8: cannot be casted from an I64 greater than: ");
        til_Str _tmp191 = til_I64_to_str(til_MAX_U8);
        int _arr_status__tmp189 = til_Array_new(&_tmp188, &_err_alloc__tmp189, "Str", 2);
        if (_arr_status__tmp189 != 0) {
        }
        _arr_status__tmp189 = til_Array_set(&_err_idx__tmp189, &_tmp188, 0, &_tmp190);
        if (_arr_status__tmp189 != 0) {
        }
        _arr_status__tmp189 = til_Array_set(&_err_idx__tmp189, &_tmp188, 1, &_tmp191);
        if (_arr_status__tmp189 != 0) {
        }
        int _status__tmp187 = til_format(&_tmp186, &_err0__tmp187, &_err1__tmp187, &_err2__tmp187, til_Str_from_literal(""), &_tmp188);
        if (_status__tmp187 != 0) {
        }
        til_Array_delete(&_tmp188);
        *_err1 = til_U8_OverflowError_new(_tmp186);
        return 1;
    }
    *_ret = til_i64_to_u8(til_self);
    return 0;
}

til_Str til_U8_to_str(const til_U8 til_self) {
    return til_I64_to_str(til_U8_to_i64(til_self));
}

int til_U8_from_str(til_U8* _ret, til_U8_OverflowError* _err1, const til_Str til_s) {
    til_U8 _ret__tmp192;
    til_U8_OverflowError _err0__tmp192 = {};
    int _status__tmp192 = til_U8_from_i64(&_ret__tmp192, &_err0__tmp192, til_I64_from_str(til_s));
    if (_status__tmp192 == 1) { *_err1 = _err0__tmp192; return 1; }
    *_ret = _ret__tmp192;
    return 0;
}

til_I64 til_U8_size(void) {
    return 1;
}

int main() {
    const til_I64 til_MIN_I64 = til_sub(0, 922337203);
    return 0;
}
