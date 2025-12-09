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
til_Bool til_or(int _til_args_len, til_Bool* til_args);
til_Bool til_and(int _til_args_len, til_Bool* til_args);
til_Bool til_xor(const til_Bool til_a, const til_Bool til_b);
til_Bool til_xnor(const til_Bool til_a, const til_Bool til_b);
til_I64 til_branchless(const til_Bool til_cond, const til_I64 til_a, const til_I64 til_b);
til_Bool til_lteq(const til_I64 til_a, const til_I64 til_b);
til_Bool til_gteq(const til_I64 til_a, const til_I64 til_b);
void til_print(int _til_args_len, til_Str* til_args);
void til_println(int _til_args_len, til_Str* til_args);
int til_get_substr(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_start, const til_I64 til_end);
int til_get_char(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_pos);
til_Bool til_starts_with(const til_Str til_s, const til_Str til_prefix);
til_Str til_concat(const til_Str til_a, const til_Str til_b);
int til_format(til_Str* _ret, til_I64_OverflowError* _err1, til_IndexOutOfBoundsError* _err2, til_AllocError* _err3, const til_Str til_prefix, int _til_args_len, til_Str* til_args);
void til_panic(const til_Str til_loc_str, int _til_msgs_len, til_Str* til_msgs);
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

til_Bool til_or(int _til_args_len, til_Bool* til_args) {
    til_I64 til_i = 0;
    while (til_lt(til_i, _til_args_len).data) {
        til_Bool til_val = false;
        til_val = til_args[til_i];
        if (til_val.data) {
            return true;
        }
        til_I64_inc(&til_i);
    }
    return false;
}

til_Bool til_and(int _til_args_len, til_Bool* til_args) {
    til_I64 til_i = 0;
    while (til_lt(til_i, _til_args_len).data) {
        til_Bool til_val = false;
        til_val = til_args[til_i];
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

void til_print(int _til_args_len, til_Str* til_args) {
    til_I64 til_i = 0;
    while (til_lt(til_i, _til_args_len).data) {
        til_Str til_val = til_Str_from_literal("");
        til_val = til_args[til_i];
        til_single_print(til_val);
        til_I64_inc(&til_i);
    }
    til_print_flush();
}

void til_println(int _til_args_len, til_Str* til_args) {
    til_I64 til_i = 0;
    while (til_lt(til_i, _til_args_len).data) {
        til_Str til_val = til_Str_from_literal("");
        til_val = til_args[til_i];
        til_single_print(til_val);
        til_I64_inc(&til_i);
    }
    til_single_print(til_Str_from_literal("\n"));
    til_print_flush();
}

int til_get_substr(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_start, const til_I64 til_end) {
    if (til_lt(til_start, 0).data) {
        til_Str _tmp0;
        til_I64_OverflowError _err0__tmp1;
        til_IndexOutOfBoundsError _err1__tmp1;
        til_AllocError _err2__tmp1;
        int _status__tmp1 = til_format(&_tmp0, &_err0__tmp1, &_err1__tmp1, &_err2__tmp1, til_Str_from_literal(""), 3, (til_Str[]){til_Str_from_literal("get_substr: start index "), til_I64_to_str(til_start), til_Str_from_literal(" cannot be negative")});
        if (_status__tmp1 != 0) {
            if (_status__tmp1 == 2) { *_err1 = _err1__tmp1; return 1; }
            if (_status__tmp1 == 3) { *_err2 = _err2__tmp1; return 2; }
        }
        *_err1 = til_IndexOutOfBoundsError_new(_tmp0);
        return 1;
    }
    if (til_lt(til_end, 0).data) {
        til_Str _tmp2;
        til_I64_OverflowError _err0__tmp3;
        til_IndexOutOfBoundsError _err1__tmp3;
        til_AllocError _err2__tmp3;
        int _status__tmp3 = til_format(&_tmp2, &_err0__tmp3, &_err1__tmp3, &_err2__tmp3, til_Str_from_literal(""), 3, (til_Str[]){til_Str_from_literal("get_substr: end index "), til_I64_to_str(til_end), til_Str_from_literal(" cannot be negative")});
        if (_status__tmp3 != 0) {
            if (_status__tmp3 == 2) { *_err1 = _err1__tmp3; return 1; }
            if (_status__tmp3 == 3) { *_err2 = _err2__tmp3; return 2; }
        }
        *_err1 = til_IndexOutOfBoundsError_new(_tmp2);
        return 1;
    }
    if (til_gt(til_start, til_end).data) {
        til_Str _tmp4;
        til_I64_OverflowError _err0__tmp5;
        til_IndexOutOfBoundsError _err1__tmp5;
        til_AllocError _err2__tmp5;
        int _status__tmp5 = til_format(&_tmp4, &_err0__tmp5, &_err1__tmp5, &_err2__tmp5, til_Str_from_literal(""), 4, (til_Str[]){til_Str_from_literal("get_substr: start index "), til_I64_to_str(til_start), til_Str_from_literal(" is greater than end index "), til_I64_to_str(til_end)});
        if (_status__tmp5 != 0) {
            if (_status__tmp5 == 2) { *_err1 = _err1__tmp5; return 1; }
            if (_status__tmp5 == 3) { *_err2 = _err2__tmp5; return 2; }
        }
        *_err1 = til_IndexOutOfBoundsError_new(_tmp4);
        return 1;
    }
    if (til_gt(til_end, til_Str_len(til_s)).data) {
        til_Str _tmp6;
        til_I64_OverflowError _err0__tmp7;
        til_IndexOutOfBoundsError _err1__tmp7;
        til_AllocError _err2__tmp7;
        int _status__tmp7 = til_format(&_tmp6, &_err0__tmp7, &_err1__tmp7, &_err2__tmp7, til_Str_from_literal(""), 4, (til_Str[]){til_Str_from_literal("get_substr: end index "), til_I64_to_str(til_end), til_Str_from_literal(" is greater than string length "), til_I64_to_str(til_Str_len(til_s))});
        if (_status__tmp7 != 0) {
            if (_status__tmp7 == 2) { *_err1 = _err1__tmp7; return 1; }
            if (_status__tmp7 == 3) { *_err2 = _err2__tmp7; return 2; }
        }
        *_err1 = til_IndexOutOfBoundsError_new(_tmp6);
        return 1;
    }
    if (til_I64_eq(til_start, til_end).data) {
        til_Str _tmp8;
        til_I64_OverflowError _err0__tmp9;
        til_IndexOutOfBoundsError _err1__tmp9;
        til_AllocError _err2__tmp9;
        int _status__tmp9 = til_format(&_tmp8, &_err0__tmp9, &_err1__tmp9, &_err2__tmp9, til_Str_from_literal(""), 3, (til_Str[]){til_Str_from_literal("get_substr: start and end are the same ("), til_I64_to_str(til_start), til_Str_from_literal("), no substring")});
        if (_status__tmp9 != 0) {
            if (_status__tmp9 == 2) { *_err1 = _err1__tmp9; return 1; }
            if (_status__tmp9 == 3) { *_err2 = _err2__tmp9; return 2; }
        }
        *_err1 = til_IndexOutOfBoundsError_new(_tmp8);
        return 1;
    }
    til_Str til_substr = {0};
    til_substr.cap = til_sub(til_end, til_start);
    til_I64 _ret__tmp10;
    til_AllocError _err0__tmp10 = {};
    int _status__tmp10 = til_malloc(&_ret__tmp10, &_err0__tmp10, til_substr.cap);
    if (_status__tmp10 == 1) { *_err2 = _err0__tmp10; return 2; }
    til_substr.c_string = _ret__tmp10;
    if (til_I64_eq(til_NULL, til_substr.c_string).data) {
        til_Str _tmp11;
        til_I64_OverflowError _err0__tmp12;
        til_IndexOutOfBoundsError _err1__tmp12;
        til_AllocError _err2__tmp12;
        int _status__tmp12 = til_format(&_tmp11, &_err0__tmp12, &_err1__tmp12, &_err2__tmp12, til_Str_from_literal(""), 3, (til_Str[]){til_Str_from_literal("Str.get_substr: failed to allocate "), til_I64_to_str(til_substr.cap), til_Str_from_literal(" bytes")});
        if (_status__tmp12 != 0) {
            if (_status__tmp12 == 2) { *_err1 = _err1__tmp12; return 1; }
            if (_status__tmp12 == 3) { *_err2 = _err2__tmp12; return 2; }
        }
        *_err2 = til_AllocError_new(_tmp11);
        return 2;
    }
    til_memcpy(til_substr.c_string, til_add(til_s.c_string, til_start), til_substr.cap);
    *_ret = til_substr;
    return 0;
}

int til_get_char(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_pos) {
    til_Str _ret__tmp13;
    til_IndexOutOfBoundsError _err0__tmp13 = {};
    til_AllocError _err1__tmp13 = {};
    int _status__tmp13 = til_get_substr(&_ret__tmp13, &_err0__tmp13, &_err1__tmp13, til_s, til_pos, til_add(til_pos, 1));
    if (_status__tmp13 == 1) { *_err1 = _err0__tmp13; return 1; }
    if (_status__tmp13 == 2) { *_err2 = _err1__tmp13; return 2; }
    *_ret = _ret__tmp13;
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
        til_panic(til_Str_from_literal(""), 1, (til_Str[]){til_Str_from_literal("concat: integer overflow")});
    }
    til_I64 _ret__tmp14;
    til_AllocError _err0__tmp14 = {};
    int _status__tmp14 = til_malloc(&_ret__tmp14, &_err0__tmp14, til_result.cap);
    if (_status__tmp14 == 0) {
        til_result.c_string = _ret__tmp14;
    } else if (_status__tmp14 == 1) {
        til_AllocError til_err = _err0__tmp14;
        til_panic(til_Str_from_literal(""), 1, (til_Str[]){til_err.msg});
    }
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_panic(til_Str_from_literal(""), 1, (til_Str[]){til_Str_from_literal("concat: malloc failed")});
    }
    til_memcpy(til_result.c_string, til_a.c_string, til_a.cap);
    til_memcpy(til_add(til_result.c_string, til_a.cap), til_b.c_string, til_b.cap);
    return til_result;
}

int til_format(til_Str* _ret, til_I64_OverflowError* _err1, til_IndexOutOfBoundsError* _err2, til_AllocError* _err3, const til_Str til_prefix, int _til_args_len, til_Str* til_args) {
    til_Str til_result = {0};
    til_result.cap = til_prefix.cap;
    til_I64 til_i = 0;
    while (til_lt(til_i, _til_args_len).data) {
        til_Str til_arg = til_Str_from_literal("");
        til_arg = til_args[til_i];
        til_result.cap = til_add(til_result.cap, til_arg.cap);
        if (til_lt(til_result.cap, til_arg.cap).data) {
            til_Str _tmp15;
            til_I64_OverflowError _err0__tmp16;
            til_IndexOutOfBoundsError _err1__tmp16;
            til_AllocError _err2__tmp16;
            int _status__tmp16 = til_format(&_tmp15, &_err0__tmp16, &_err1__tmp16, &_err2__tmp16, til_Str_from_literal(""), 2, (til_Str[]){til_Str_from_literal("format: integer overflow while summing cap for arg "), til_I64_to_str(til_i)});
            if (_status__tmp16 != 0) {
                if (_status__tmp16 == 1) { *_err1 = _err0__tmp16; return 1; }
                if (_status__tmp16 == 2) { *_err2 = _err1__tmp16; return 2; }
                if (_status__tmp16 == 3) { *_err3 = _err2__tmp16; return 3; }
            }
            *_err1 = til_I64_OverflowError_new(_tmp15);
            return 1;
        }
        til_I64_inc(&til_i);
    }
    til_I64 _ret__tmp17;
    til_AllocError _err0__tmp17 = {};
    int _status__tmp17 = til_malloc(&_ret__tmp17, &_err0__tmp17, til_result.cap);
    if (_status__tmp17 == 1) { *_err3 = _err0__tmp17; return 3; }
    til_result.c_string = _ret__tmp17;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Str _tmp18;
        til_I64_OverflowError _err0__tmp19;
        til_IndexOutOfBoundsError _err1__tmp19;
        til_AllocError _err2__tmp19;
        int _status__tmp19 = til_format(&_tmp18, &_err0__tmp19, &_err1__tmp19, &_err2__tmp19, til_Str_from_literal(""), 2, (til_Str[]){til_Str_from_literal("format: malloc failed for cap = "), til_I64_to_str(til_result.cap)});
        if (_status__tmp19 != 0) {
            if (_status__tmp19 == 1) { *_err1 = _err0__tmp19; return 1; }
            if (_status__tmp19 == 2) { *_err2 = _err1__tmp19; return 2; }
            if (_status__tmp19 == 3) { *_err3 = _err2__tmp19; return 3; }
        }
        *_err3 = til_AllocError_new(_tmp18);
        return 3;
    }
    til_I64 til_offset = 0;
    til_memcpy(til_result.c_string, til_prefix.c_string, til_prefix.cap);
    til_offset = til_prefix.cap;
    til_i = 0;
    while (til_lt(til_i, _til_args_len).data) {
        til_Str til_s = til_Str_from_literal("");
        til_s = til_args[til_i];
        til_memcpy(til_add(til_result.c_string, til_offset), til_s.c_string, til_s.cap);
        til_offset = til_add(til_offset, til_s.cap);
        til_I64_inc(&til_i);
    }
    *_ret = til_result;
    return 0;
}

void til_panic(const til_Str til_loc_str, int _til_msgs_len, til_Str* til_msgs) {
    til_single_print(til_loc_str);
    til_I64 til_i = 0;
    while (til_lt(til_i, _til_msgs_len).data) {
        til_Str til_val = til_Str_from_literal("");
        til_val = til_msgs[til_i];
        til_single_print(til_val);
        til_I64_inc(&til_i);
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
    til_I64 _ret__tmp20;
    til_AllocError _err0__tmp20 = {};
    int _status__tmp20 = til_malloc(&_ret__tmp20, &_err0__tmp20, til_size_bytes);
    if (_status__tmp20 == 1) { *_err1 = _err0__tmp20; return 1; }
    til_arr.ptr = _ret__tmp20;
    til_U8 _tmp21;
    til_U8_OverflowError _err0__tmp22;
    int _status__tmp22 = til_U8_from_i64(&_tmp21, &_err0__tmp22, 0);
    if (_status__tmp22 != 0) {
    }
    til_memset(til_arr.ptr, _tmp21, til_size_bytes);
    til_arr._len = til_capacity;
    *_ret = til_arr;
    return 0;
}

int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array til_self, const til_I64 til_index, til_Dynamic* til_T) {
    if (til_gteq(til_index, til_self._len).data) {
        til_Str _tmp23;
        til_I64_OverflowError _err0__tmp24;
        til_IndexOutOfBoundsError _err1__tmp24;
        til_AllocError _err2__tmp24;
        int _status__tmp24 = til_format(&_tmp23, &_err0__tmp24, &_err1__tmp24, &_err2__tmp24, til_Str_from_literal(""), 1, (til_Str[]){til_Str_from_literal("Array.get: index out of bounds")});
        if (_status__tmp24 != 0) {
            if (_status__tmp24 == 2) { *_err1 = _err1__tmp24; return 1; }
        }
        *_err1 = til_IndexOutOfBoundsError_new(_tmp23);
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)(*til_T);
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_gteq(til_index, til_self->_len).data) {
        til_Str _tmp25;
        til_I64_OverflowError _err0__tmp26;
        til_IndexOutOfBoundsError _err1__tmp26;
        til_AllocError _err2__tmp26;
        int _status__tmp26 = til_format(&_tmp25, &_err0__tmp26, &_err1__tmp26, &_err2__tmp26, til_Str_from_literal(""), 1, (til_Str[]){til_Str_from_literal("Array.set: index out of bounds")});
        if (_status__tmp26 != 0) {
            if (_status__tmp26 == 2) { *_err1 = _err1__tmp26; return 1; }
        }
        *_err1 = til_IndexOutOfBoundsError_new(_tmp25);
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
    til_I64 _ret__tmp27;
    til_AllocError _err0__tmp27 = {};
    int _status__tmp27 = til_malloc(&_ret__tmp27, &_err0__tmp27, til_total_bytes);
    if (_status__tmp27 == 1) { *_err1 = _err0__tmp27; return 1; }
    til_cloned.ptr = _ret__tmp27;
    if (til_I64_eq(til_NULL, til_cloned.ptr).data) {
        til_Str _tmp28;
        til_I64_OverflowError _err0__tmp29;
        til_IndexOutOfBoundsError _err1__tmp29;
        til_AllocError _err2__tmp29;
        int _status__tmp29 = til_format(&_tmp28, &_err0__tmp29, &_err1__tmp29, &_err2__tmp29, til_Str_from_literal(""), 3, (til_Str[]){til_Str_from_literal("Array.clone: malloc failed for "), til_I64_to_str(til_total_bytes), til_Str_from_literal(" bytes")});
        if (_status__tmp29 != 0) {
            if (_status__tmp29 == 3) { *_err1 = _err2__tmp29; return 1; }
        }
        *_err1 = til_AllocError_new(_tmp28);
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
        til_IndexOutOfBoundsError _err0__tmp30 = {};
        int _status__tmp30 = til_Array_get(&_err0__tmp30, til_self, til_i, &til_elem);
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
    return til_or(2, (til_Bool[]){til_and(2, (til_Bool[]){til_a, til_b}), til_and(2, (til_Bool[]){til_not(til_b), til_not(til_a)})});
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
    til_I64 _ret__tmp31;
    til_AllocError _err0__tmp31 = {};
    int _status__tmp31 = til_malloc(&_ret__tmp31, &_err0__tmp31, til_size_bytes);
    if (_status__tmp31 == 1) { *_err1 = _err0__tmp31; return 1; }
    til_vec.ptr = _ret__tmp31;
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
    til_I64 _ret__tmp32;
    til_AllocError _err0__tmp32 = {};
    int _status__tmp32 = til_malloc(&_ret__tmp32, &_err0__tmp32, til_size_bytes);
    if (_status__tmp32 == 1) { *_err1 = _err0__tmp32; return 1; }
    til_vec.ptr = _ret__tmp32;
    til_vec._len = 0;
    til_vec.cap = til_Vec_INIT_CAP;
    *_ret = til_vec;
    return 0;
}

int til_Vec_push(til_AllocError* _err1, til_Vec* til_self, const til_Dynamic til_value) {
    if (til_I64_eq(til_self->_len, til_self->cap).data) {
        const til_I64 til_new_cap = til_mul(til_self->cap, 2);
        if (til_gt(til_new_cap, til_Vec_MAX_CAP).data) {
            til_panic(til_Str_from_literal(""), 1, (til_Str[]){til_Str_from_literal("Vec.push: capacity exceeded Vec.MAX_CAP")});
        }
        til_I64 _ret__tmp33;
        til_I64 til_new_ptr;
        til_AllocError _err0__tmp33 = {};
        int _status__tmp33 = til_malloc(&_ret__tmp33, &_err0__tmp33, til_mul(til_new_cap, til_self->type_size));
        if (_status__tmp33 == 1) { *_err1 = _err0__tmp33; return 1; }
        til_new_ptr = _ret__tmp33;
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
        til_Str _tmp34;
        til_I64_OverflowError _err0__tmp35;
        til_IndexOutOfBoundsError _err1__tmp35;
        til_AllocError _err2__tmp35;
        int _status__tmp35 = til_format(&_tmp34, &_err0__tmp35, &_err1__tmp35, &_err2__tmp35, til_Str_from_literal(""), 1, (til_Str[]){til_Str_from_literal("Vec.get: index out of bounds")});
        if (_status__tmp35 != 0) {
            if (_status__tmp35 == 2) { *_err1 = _err1__tmp35; return 1; }
        }
        *_err1 = til_IndexOutOfBoundsError_new(_tmp34);
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)(*til_T);
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Vec_set(til_IndexOutOfBoundsError* _err1, til_Vec* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_gteq(til_index, til_self->_len).data) {
        til_Str _tmp36;
        til_I64_OverflowError _err0__tmp37;
        til_IndexOutOfBoundsError _err1__tmp37;
        til_AllocError _err2__tmp37;
        int _status__tmp37 = til_format(&_tmp36, &_err0__tmp37, &_err1__tmp37, &_err2__tmp37, til_Str_from_literal(""), 1, (til_Str[]){til_Str_from_literal("Vec.set: index out of bounds")});
        if (_status__tmp37 != 0) {
            if (_status__tmp37 == 2) { *_err1 = _err1__tmp37; return 1; }
        }
        *_err1 = til_IndexOutOfBoundsError_new(_tmp36);
        return 1;
    }
    til_I64 til_dest = til_add(til_self->ptr, til_mul(til_index, til_self->type_size));
    til_memcpy(til_dest, (til_I64)til_value, til_self->type_size);
    return 0;
}

int til_Vec_pop(til_IndexOutOfBoundsError* _err1, til_Vec* til_self, til_Dynamic* til_dest) {
    if (til_I64_eq(til_self->_len, 0).data) {
        til_Str _tmp38;
        til_I64_OverflowError _err0__tmp39;
        til_IndexOutOfBoundsError _err1__tmp39;
        til_AllocError _err2__tmp39;
        int _status__tmp39 = til_format(&_tmp38, &_err0__tmp39, &_err1__tmp39, &_err2__tmp39, til_Str_from_literal(""), 1, (til_Str[]){til_Str_from_literal("Vec.pop: cannot pop from empty Vec")});
        if (_status__tmp39 != 0) {
            if (_status__tmp39 == 2) { *_err1 = _err1__tmp39; return 1; }
        }
        *_err1 = til_IndexOutOfBoundsError_new(_tmp38);
        return 1;
    }
    til_I64 til_last_index = til_sub(til_self->_len, 1);
    til_IndexOutOfBoundsError _err0__tmp40 = {};
    int _status__tmp40 = til_Vec_get(&_err0__tmp40, (*til_self), til_last_index, &til_dest);
    if (_status__tmp40 == 1) { *_err1 = _err0__tmp40; return 1; }
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
    til_I64 _ret__tmp41;
    til_AllocError _err0__tmp41 = {};
    int _status__tmp41 = til_malloc(&_ret__tmp41, &_err0__tmp41, til_total_bytes);
    if (_status__tmp41 == 1) { *_err1 = _err0__tmp41; return 1; }
    til_cloned.ptr = _ret__tmp41;
    if (til_I64_eq(til_NULL, til_cloned.ptr).data) {
        til_Str _tmp42;
        til_I64_OverflowError _err0__tmp43;
        til_IndexOutOfBoundsError _err1__tmp43;
        til_AllocError _err2__tmp43;
        int _status__tmp43 = til_format(&_tmp42, &_err0__tmp43, &_err1__tmp43, &_err2__tmp43, til_Str_from_literal(""), 3, (til_Str[]){til_Str_from_literal("Vec.clone: malloc failed for "), til_I64_to_str(til_total_bytes), til_Str_from_literal(" bytes")});
        if (_status__tmp43 != 0) {
            if (_status__tmp43 == 3) { *_err1 = _err2__tmp43; return 1; }
        }
        *_err1 = til_AllocError_new(_tmp42);
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
                til_panic(til_Str_from_literal(""), 1, (til_Str[]){til_Str_from_literal("Vec.extend: capacity exceeded Vec.MAX_CAP")});
            }
            til_I64 _ret__tmp44;
            til_I64 til_new_ptr;
            til_AllocError _err0__tmp44 = {};
            int _status__tmp44 = til_malloc(&_ret__tmp44, &_err0__tmp44, til_mul(til_new_cap, til_self->type_size));
            if (_status__tmp44 == 1) { *_err1 = _err0__tmp44; return 1; }
            til_new_ptr = _ret__tmp44;
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
        til_Str _tmp45;
        til_I64_OverflowError _err0__tmp46;
        til_IndexOutOfBoundsError _err1__tmp46;
        til_AllocError _err2__tmp46;
        int _status__tmp46 = til_format(&_tmp45, &_err0__tmp46, &_err1__tmp46, &_err2__tmp46, til_Str_from_literal(""), 1, (til_Str[]){til_Str_from_literal("Vec.remove: index out of bounds")});
        if (_status__tmp46 != 0) {
            if (_status__tmp46 == 2) { *_err1 = _err1__tmp46; return 1; }
        }
        *_err1 = til_IndexOutOfBoundsError_new(_tmp45);
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
    til_I64 _ret__tmp47;
    til_AllocError _err0__tmp47 = {};
    int _status__tmp47 = til_malloc(&_ret__tmp47, &_err0__tmp47, til_cloned.cap);
    if (_status__tmp47 == 1) { *_err1 = _err0__tmp47; return 1; }
    til_cloned.c_string = _ret__tmp47;
    if (til_I64_eq(til_NULL, til_cloned.c_string).data) {
        til_Str _tmp48;
        til_I64_OverflowError _err0__tmp49;
        til_IndexOutOfBoundsError _err1__tmp49;
        til_AllocError _err2__tmp49;
        int _status__tmp49 = til_format(&_tmp48, &_err0__tmp49, &_err1__tmp49, &_err2__tmp49, til_Str_from_literal(""), 3, (til_Str[]){til_Str_from_literal("Str.clone: malloc failed for "), til_I64_to_str(til_cloned.cap), til_Str_from_literal(" bytes")});
        if (_status__tmp49 != 0) {
            if (_status__tmp49 == 3) { *_err1 = _err2__tmp49; return 1; }
        }
        *_err1 = til_AllocError_new(_tmp48);
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
        til_Str _ret__tmp50;
        til_AllocError _err0__tmp50 = {};
        int _status__tmp50 = til_Str_clone(&_ret__tmp50, &_err0__tmp50, til_self);
        if (_status__tmp50 == 1) { *_err1 = _err0__tmp50; return 1; }
        *_ret = _ret__tmp50;
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
        til_Str _ret__tmp51;
        til_AllocError _err0__tmp51 = {};
        int _status__tmp51 = til_Str_clone(&_ret__tmp51, &_err0__tmp51, til_self);
        if (_status__tmp51 == 1) { *_err1 = _err0__tmp51; return 1; }
        *_ret = _ret__tmp51;
        return 0;
    }
    til_I64 til_new_len = til_add(til_sub(til_Str_len(til_self), til_mul(til_count, til_Str_len(til_from))), til_mul(til_count, til_Str_len(til_to)));
    til_Str til_result = {0};
    til_result.cap = til_new_len;
    til_I64 _ret__tmp52;
    til_AllocError _err0__tmp52 = {};
    int _status__tmp52 = til_malloc(&_ret__tmp52, &_err0__tmp52, til_new_len);
    if (_status__tmp52 == 1) { *_err1 = _err0__tmp52; return 1; }
    til_result.c_string = _ret__tmp52;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Str _tmp53;
        til_I64_OverflowError _err0__tmp54;
        til_IndexOutOfBoundsError _err1__tmp54;
        til_AllocError _err2__tmp54;
        int _status__tmp54 = til_format(&_tmp53, &_err0__tmp54, &_err1__tmp54, &_err2__tmp54, til_Str_from_literal(""), 3, (til_Str[]){til_Str_from_literal("Str.replace: malloc failed for "), til_I64_to_str(til_new_len), til_Str_from_literal(" bytes")});
        if (_status__tmp54 != 0) {
            if (_status__tmp54 == 3) { *_err1 = _err2__tmp54; return 1; }
        }
        *_err1 = til_AllocError_new(_tmp53);
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

int til_Str_split(til_Vec* _ret, til_AllocError* _err1, til_IndexOutOfBoundsError* _err2, const til_Str til_self, const til_Str til_delimiter) {
    til_Vec _ret__tmp55;
    til_Vec til_parts;
    til_AllocError _err0__tmp55 = {};
    int _status__tmp55 = til_Vec_new(&_ret__tmp55, &_err0__tmp55, "Str");
    if (_status__tmp55 == 1) { *_err1 = _err0__tmp55; return 1; }
    til_parts = _ret__tmp55;
    if (til_I64_eq(til_Str_len(til_delimiter), 0).data) {
        til_Str _tmp57;
        til_AllocError _err0__tmp58;
        int _status__tmp58 = til_Str_clone(&_tmp57, &_err0__tmp58, til_self);
        if (_status__tmp58 != 0) {
            if (_status__tmp58 == 1) { *_err1 = _err0__tmp58; return 1; }
        }
        til_AllocError _err0__tmp56 = {};
        int _status__tmp56 = til_Vec_push(&_err0__tmp56, &til_parts, &_tmp57);
        if (_status__tmp56 == 1) { *_err1 = _err0__tmp56; return 1; }
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
                til_Str _ret__tmp59;
                til_Str til_part;
                til_IndexOutOfBoundsError _err0__tmp59 = {};
                til_AllocError _err1__tmp59 = {};
                int _status__tmp59 = til_get_substr(&_ret__tmp59, &_err0__tmp59, &_err1__tmp59, til_self, til_start, til_pos);
                if (_status__tmp59 == 1) { *_err2 = _err0__tmp59; return 2; }
                if (_status__tmp59 == 2) { *_err1 = _err1__tmp59; return 1; }
                til_part = _ret__tmp59;
                til_AllocError _err0__tmp60 = {};
                int _status__tmp60 = til_Vec_push(&_err0__tmp60, &til_parts, &til_part);
                if (_status__tmp60 == 1) { *_err1 = _err0__tmp60; return 1; }
            } else {
                til_Str _tmp62 = til_Str_from_literal("");
                til_AllocError _err0__tmp61 = {};
                int _status__tmp61 = til_Vec_push(&_err0__tmp61, &til_parts, &_tmp62);
                if (_status__tmp61 == 1) { *_err1 = _err0__tmp61; return 1; }
            }
            til_start = til_add(til_pos, til_Str_len(til_delimiter));
            til_pos = til_start;
        } else {
            til_pos = til_add(til_pos, 1);
        }
    }
    if (til_lt(til_start, til_Str_len(til_self)).data) {
        til_Str _ret__tmp63;
        til_Str til_part;
        til_IndexOutOfBoundsError _err0__tmp63 = {};
        til_AllocError _err1__tmp63 = {};
        int _status__tmp63 = til_get_substr(&_ret__tmp63, &_err0__tmp63, &_err1__tmp63, til_self, til_start, til_Str_len(til_self));
        if (_status__tmp63 == 1) { *_err2 = _err0__tmp63; return 2; }
        if (_status__tmp63 == 2) { *_err1 = _err1__tmp63; return 1; }
        til_part = _ret__tmp63;
        til_AllocError _err0__tmp64 = {};
        int _status__tmp64 = til_Vec_push(&_err0__tmp64, &til_parts, &til_part);
        if (_status__tmp64 == 1) { *_err1 = _err0__tmp64; return 1; }
    } else {
        if (til_I64_eq(til_start, til_Str_len(til_self)).data) {
            til_Str _tmp66 = til_Str_from_literal("");
            til_AllocError _err0__tmp65 = {};
            int _status__tmp65 = til_Vec_push(&_err0__tmp65, &til_parts, &_tmp66);
            if (_status__tmp65 == 1) { *_err1 = _err0__tmp65; return 1; }
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
    til_U8 _ret__tmp67;
    til_U8_OverflowError _err0__tmp67 = {};
    int _status__tmp67 = til_U8_from_i64(&_ret__tmp67, &_err0__tmp67, til_add(til_U8_to_i64(til_a), til_U8_to_i64(til_b)));
    if (_status__tmp67 == 1) { *_err1 = _err0__tmp67; return 1; }
    *_ret = _ret__tmp67;
    return 0;
}

int til_U8_from_i64(til_U8* _ret, til_U8_OverflowError* _err1, const til_I64 til_self) {
    if (til_lt(til_self, 0).data) {
        til_Str _tmp68;
        til_I64_OverflowError _err0__tmp69;
        til_IndexOutOfBoundsError _err1__tmp69;
        til_AllocError _err2__tmp69;
        int _status__tmp69 = til_format(&_tmp68, &_err0__tmp69, &_err1__tmp69, &_err2__tmp69, til_Str_from_literal(""), 1, (til_Str[]){til_Str_from_literal("Negative values cannot be cast into 'U8'")});
        if (_status__tmp69 != 0) {
        }
        *_err1 = til_U8_OverflowError_new(_tmp68);
        return 1;
    }
    if (til_gt(til_self, til_MAX_U8).data) {
        til_Str _tmp70;
        til_I64_OverflowError _err0__tmp71;
        til_IndexOutOfBoundsError _err1__tmp71;
        til_AllocError _err2__tmp71;
        int _status__tmp71 = til_format(&_tmp70, &_err0__tmp71, &_err1__tmp71, &_err2__tmp71, til_Str_from_literal(""), 2, (til_Str[]){til_Str_from_literal("U8: cannot be casted from an I64 greater than: "), til_I64_to_str(til_MAX_U8)});
        if (_status__tmp71 != 0) {
        }
        *_err1 = til_U8_OverflowError_new(_tmp70);
        return 1;
    }
    *_ret = til_i64_to_u8(til_self);
    return 0;
}

til_Str til_U8_to_str(const til_U8 til_self) {
    return til_I64_to_str(til_U8_to_i64(til_self));
}

int til_U8_from_str(til_U8* _ret, til_U8_OverflowError* _err1, const til_Str til_s) {
    til_U8 _ret__tmp72;
    til_U8_OverflowError _err0__tmp72 = {};
    int _status__tmp72 = til_U8_from_i64(&_ret__tmp72, &_err0__tmp72, til_I64_from_str(til_s));
    if (_status__tmp72 == 1) { *_err1 = _err0__tmp72; return 1; }
    *_ret = _ret__tmp72;
    return 0;
}

til_I64 til_U8_size(void) {
    return 1;
}

int main() {
    const til_I64 til_MIN_I64 = til_sub(0, 922337203);
    return 0;
}
