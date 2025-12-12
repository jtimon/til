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
void til_panic(const til_Str til_loc_str, til_Array* til_msgs);
til_Bool til_lteq(const til_I64 til_a, const til_I64 til_b);
til_Bool til_gteq(const til_I64 til_a, const til_I64 til_b);
void til_println(til_Array* til_args);
int til_get_substr(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_start, const til_I64 til_end);
til_Str til_concat(const til_Str til_a, const til_Str til_b);
int til_format(til_Str* _ret, til_I64_OverflowError* _err1, til_IndexOutOfBoundsError* _err2, til_AllocError* _err3, const til_Str til_prefix, til_Array* til_args);
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
til_I64 til_Str_find(const til_Str til_self, const til_Str til_needle);
int til_Str_replacen(til_Str* _ret, til_AllocError* _err1, const til_Str til_self, const til_Str til_from, const til_Str til_to, const til_I64 til_n);
til_U8_OverflowError til_U8_OverflowError_new(const til_Str til_msg);
til_Bool til_U8_eq(const til_U8 til_self, const til_U8 til_other);
til_I64 til_U8_to_i64(const til_U8 til_self);
int til_U8_from_i64(til_U8* _ret, til_U8_OverflowError* _err1, const til_I64 til_self);

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
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp31;
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Str til_val = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp34 = {};
        int _status__tmp34 = til_Array_get(&_err0__tmp34, (*til_args), til_i, (til_Dynamic*)&til_val);
        if (_status__tmp34 == 1) { _thrown_IndexOutOfBoundsError__tmp31 = _err0__tmp34; goto _catch_IndexOutOfBoundsError__tmp31; }
        til_single_print(til_val);
        til_I64_inc(&til_i);
    }
    til_single_print(((til_Str){(til_I64)"\n", 1}));
    til_print_flush();
    goto _end_catches__tmp31;
_catch_IndexOutOfBoundsError__tmp31: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp31;
    til_Array _tmp36;
    til_AllocError _err_alloc__tmp37;
    til_IndexOutOfBoundsError _err_idx__tmp37;
    til_Str _tmp38 = ((til_Str){(til_I64)"println: IndexOutOfBoundsError should never happen", 50});
    int _arr_status__tmp37 = til_Array_new(&_tmp36, &_err_alloc__tmp37, "Str", 1);
    if (_arr_status__tmp37 != 0) {
    }
    _arr_status__tmp37 = til_Array_set(&_err_idx__tmp37, &_tmp36, 0, &_tmp38);
    if (_arr_status__tmp37 != 0) {
    }
    til_panic(((til_Str){(til_I64)"src/core/print.til:31:15:", 25}), &_tmp36);
    til_Array_delete(&_tmp36);
    }
_end_catches__tmp31:;
}

int til_get_substr(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_start, const til_I64 til_end) {
    if (til_lt(til_start, 0).data) {
        til_Str _tmp41;
        til_I64_OverflowError _err0__tmp42;
        til_IndexOutOfBoundsError _err1__tmp42;
        til_AllocError _err2__tmp42;
        til_Array _tmp43;
        til_AllocError _err_alloc__tmp44;
        til_IndexOutOfBoundsError _err_idx__tmp44;
        til_Str _tmp45 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp46 = til_I64_to_str(til_start);
        til_Str _tmp47 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp44 = til_Array_new(&_tmp43, &_err_alloc__tmp44, "Str", 3);
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
        int _status__tmp42 = til_format(&_tmp41, &_err0__tmp42, &_err1__tmp42, &_err2__tmp42, ((til_Str){(til_I64)"src/core/str.til:368:48:", 24}), &_tmp43);
        if (_status__tmp42 != 0) {
            if (_status__tmp42 == 2) { *_err1 = _err1__tmp42; return 1; }
            if (_status__tmp42 == 3) { *_err2 = _err2__tmp42; return 2; }
        }
        til_Array_delete(&_tmp43);
        til_Str _tmp48;
        til_I64_OverflowError _err0__tmp49;
        til_IndexOutOfBoundsError _err1__tmp49;
        til_AllocError _err2__tmp49;
        til_Array _tmp50;
        til_AllocError _err_alloc__tmp51;
        til_IndexOutOfBoundsError _err_idx__tmp51;
        til_Str _tmp52 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp53 = til_I64_to_str(til_start);
        til_Str _tmp54 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp51 = til_Array_new(&_tmp50, &_err_alloc__tmp51, "Str", 3);
        if (_arr_status__tmp51 != 0) {
            *_err2 = _err_alloc__tmp51; return 2;
        }
        _arr_status__tmp51 = til_Array_set(&_err_idx__tmp51, &_tmp50, 0, &_tmp52);
        if (_arr_status__tmp51 != 0) {
            *_err1 = _err_idx__tmp51; return 1;
        }
        _arr_status__tmp51 = til_Array_set(&_err_idx__tmp51, &_tmp50, 1, &_tmp53);
        if (_arr_status__tmp51 != 0) {
            *_err1 = _err_idx__tmp51; return 1;
        }
        _arr_status__tmp51 = til_Array_set(&_err_idx__tmp51, &_tmp50, 2, &_tmp54);
        if (_arr_status__tmp51 != 0) {
            *_err1 = _err_idx__tmp51; return 1;
        }
        int _status__tmp49 = til_format(&_tmp48, &_err0__tmp49, &_err1__tmp49, &_err2__tmp49, ((til_Str){(til_I64)"src/core/str.til:368:48:", 24}), &_tmp50);
        if (_status__tmp49 != 0) {
            if (_status__tmp49 == 2) { *_err1 = _err1__tmp49; return 1; }
            if (_status__tmp49 == 3) { *_err2 = _err2__tmp49; return 2; }
        }
        til_Array_delete(&_tmp50);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp48);
        return 1;
    }
    if (til_lt(til_end, 0).data) {
        til_Str _tmp56;
        til_I64_OverflowError _err0__tmp57;
        til_IndexOutOfBoundsError _err1__tmp57;
        til_AllocError _err2__tmp57;
        til_Array _tmp58;
        til_AllocError _err_alloc__tmp59;
        til_IndexOutOfBoundsError _err_idx__tmp59;
        til_Str _tmp60 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp61 = til_I64_to_str(til_end);
        til_Str _tmp62 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp59 = til_Array_new(&_tmp58, &_err_alloc__tmp59, "Str", 3);
        if (_arr_status__tmp59 != 0) {
            *_err2 = _err_alloc__tmp59; return 2;
        }
        _arr_status__tmp59 = til_Array_set(&_err_idx__tmp59, &_tmp58, 0, &_tmp60);
        if (_arr_status__tmp59 != 0) {
            *_err1 = _err_idx__tmp59; return 1;
        }
        _arr_status__tmp59 = til_Array_set(&_err_idx__tmp59, &_tmp58, 1, &_tmp61);
        if (_arr_status__tmp59 != 0) {
            *_err1 = _err_idx__tmp59; return 1;
        }
        _arr_status__tmp59 = til_Array_set(&_err_idx__tmp59, &_tmp58, 2, &_tmp62);
        if (_arr_status__tmp59 != 0) {
            *_err1 = _err_idx__tmp59; return 1;
        }
        int _status__tmp57 = til_format(&_tmp56, &_err0__tmp57, &_err1__tmp57, &_err2__tmp57, ((til_Str){(til_I64)"src/core/str.til:371:48:", 24}), &_tmp58);
        if (_status__tmp57 != 0) {
            if (_status__tmp57 == 2) { *_err1 = _err1__tmp57; return 1; }
            if (_status__tmp57 == 3) { *_err2 = _err2__tmp57; return 2; }
        }
        til_Array_delete(&_tmp58);
        til_Str _tmp63;
        til_I64_OverflowError _err0__tmp64;
        til_IndexOutOfBoundsError _err1__tmp64;
        til_AllocError _err2__tmp64;
        til_Array _tmp65;
        til_AllocError _err_alloc__tmp66;
        til_IndexOutOfBoundsError _err_idx__tmp66;
        til_Str _tmp67 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp68 = til_I64_to_str(til_end);
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
        int _status__tmp64 = til_format(&_tmp63, &_err0__tmp64, &_err1__tmp64, &_err2__tmp64, ((til_Str){(til_I64)"src/core/str.til:371:48:", 24}), &_tmp65);
        if (_status__tmp64 != 0) {
            if (_status__tmp64 == 2) { *_err1 = _err1__tmp64; return 1; }
            if (_status__tmp64 == 3) { *_err2 = _err2__tmp64; return 2; }
        }
        til_Array_delete(&_tmp65);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp63);
        return 1;
    }
    if (til_gt(til_start, til_end).data) {
        til_Str _tmp71;
        til_I64_OverflowError _err0__tmp72;
        til_IndexOutOfBoundsError _err1__tmp72;
        til_AllocError _err2__tmp72;
        til_Array _tmp73;
        til_AllocError _err_alloc__tmp74;
        til_IndexOutOfBoundsError _err_idx__tmp74;
        til_Str _tmp75 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp76 = til_I64_to_str(til_start);
        til_Str _tmp77 = ((til_Str){(til_I64)" is greater than end index ", 27});
        til_Str _tmp78 = til_I64_to_str(til_end);
        int _arr_status__tmp74 = til_Array_new(&_tmp73, &_err_alloc__tmp74, "Str", 4);
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
        _arr_status__tmp74 = til_Array_set(&_err_idx__tmp74, &_tmp73, 3, &_tmp78);
        if (_arr_status__tmp74 != 0) {
            *_err1 = _err_idx__tmp74; return 1;
        }
        int _status__tmp72 = til_format(&_tmp71, &_err0__tmp72, &_err1__tmp72, &_err2__tmp72, ((til_Str){(til_I64)"src/core/str.til:374:48:", 24}), &_tmp73);
        if (_status__tmp72 != 0) {
            if (_status__tmp72 == 2) { *_err1 = _err1__tmp72; return 1; }
            if (_status__tmp72 == 3) { *_err2 = _err2__tmp72; return 2; }
        }
        til_Array_delete(&_tmp73);
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
        *_err1 = til_IndexOutOfBoundsError_new(_tmp79);
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
        til_Str _tmp96;
        til_I64_OverflowError _err0__tmp97;
        til_IndexOutOfBoundsError _err1__tmp97;
        til_AllocError _err2__tmp97;
        til_Array _tmp98;
        til_AllocError _err_alloc__tmp99;
        til_IndexOutOfBoundsError _err_idx__tmp99;
        til_Str _tmp100 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp101 = til_I64_to_str(til_end);
        til_Str _tmp102 = ((til_Str){(til_I64)" is greater than string length ", 31});
        til_Str _tmp103 = til_I64_to_str(til_Str_len(til_s));
        int _arr_status__tmp99 = til_Array_new(&_tmp98, &_err_alloc__tmp99, "Str", 4);
        if (_arr_status__tmp99 != 0) {
            *_err2 = _err_alloc__tmp99; return 2;
        }
        _arr_status__tmp99 = til_Array_set(&_err_idx__tmp99, &_tmp98, 0, &_tmp100);
        if (_arr_status__tmp99 != 0) {
            *_err1 = _err_idx__tmp99; return 1;
        }
        _arr_status__tmp99 = til_Array_set(&_err_idx__tmp99, &_tmp98, 1, &_tmp101);
        if (_arr_status__tmp99 != 0) {
            *_err1 = _err_idx__tmp99; return 1;
        }
        _arr_status__tmp99 = til_Array_set(&_err_idx__tmp99, &_tmp98, 2, &_tmp102);
        if (_arr_status__tmp99 != 0) {
            *_err1 = _err_idx__tmp99; return 1;
        }
        _arr_status__tmp99 = til_Array_set(&_err_idx__tmp99, &_tmp98, 3, &_tmp103);
        if (_arr_status__tmp99 != 0) {
            *_err1 = _err_idx__tmp99; return 1;
        }
        int _status__tmp97 = til_format(&_tmp96, &_err0__tmp97, &_err1__tmp97, &_err2__tmp97, ((til_Str){(til_I64)"src/core/str.til:377:48:", 24}), &_tmp98);
        if (_status__tmp97 != 0) {
            if (_status__tmp97 == 2) { *_err1 = _err1__tmp97; return 1; }
            if (_status__tmp97 == 3) { *_err2 = _err2__tmp97; return 2; }
        }
        til_Array_delete(&_tmp98);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp96);
        return 1;
    }
    if (til_I64_eq(til_start, til_end).data) {
        til_Str _tmp105;
        til_I64_OverflowError _err0__tmp106;
        til_IndexOutOfBoundsError _err1__tmp106;
        til_AllocError _err2__tmp106;
        til_Array _tmp107;
        til_AllocError _err_alloc__tmp108;
        til_IndexOutOfBoundsError _err_idx__tmp108;
        til_Str _tmp109 = ((til_Str){(til_I64)"get_substr: start and end are the same (", 40});
        til_Str _tmp110 = til_I64_to_str(til_start);
        til_Str _tmp111 = ((til_Str){(til_I64)"), no substring", 15});
        int _arr_status__tmp108 = til_Array_new(&_tmp107, &_err_alloc__tmp108, "Str", 3);
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
        int _status__tmp106 = til_format(&_tmp105, &_err0__tmp106, &_err1__tmp106, &_err2__tmp106, ((til_Str){(til_I64)"src/core/str.til:380:48:", 24}), &_tmp107);
        if (_status__tmp106 != 0) {
            if (_status__tmp106 == 2) { *_err1 = _err1__tmp106; return 1; }
            if (_status__tmp106 == 3) { *_err2 = _err2__tmp106; return 2; }
        }
        til_Array_delete(&_tmp107);
        til_Str _tmp112;
        til_I64_OverflowError _err0__tmp113;
        til_IndexOutOfBoundsError _err1__tmp113;
        til_AllocError _err2__tmp113;
        til_Array _tmp114;
        til_AllocError _err_alloc__tmp115;
        til_IndexOutOfBoundsError _err_idx__tmp115;
        til_Str _tmp116 = ((til_Str){(til_I64)"get_substr: start and end are the same (", 40});
        til_Str _tmp117 = til_I64_to_str(til_start);
        til_Str _tmp118 = ((til_Str){(til_I64)"), no substring", 15});
        int _arr_status__tmp115 = til_Array_new(&_tmp114, &_err_alloc__tmp115, "Str", 3);
        if (_arr_status__tmp115 != 0) {
            *_err2 = _err_alloc__tmp115; return 2;
        }
        _arr_status__tmp115 = til_Array_set(&_err_idx__tmp115, &_tmp114, 0, &_tmp116);
        if (_arr_status__tmp115 != 0) {
            *_err1 = _err_idx__tmp115; return 1;
        }
        _arr_status__tmp115 = til_Array_set(&_err_idx__tmp115, &_tmp114, 1, &_tmp117);
        if (_arr_status__tmp115 != 0) {
            *_err1 = _err_idx__tmp115; return 1;
        }
        _arr_status__tmp115 = til_Array_set(&_err_idx__tmp115, &_tmp114, 2, &_tmp118);
        if (_arr_status__tmp115 != 0) {
            *_err1 = _err_idx__tmp115; return 1;
        }
        int _status__tmp113 = til_format(&_tmp112, &_err0__tmp113, &_err1__tmp113, &_err2__tmp113, ((til_Str){(til_I64)"src/core/str.til:380:48:", 24}), &_tmp114);
        if (_status__tmp113 != 0) {
            if (_status__tmp113 == 2) { *_err1 = _err1__tmp113; return 1; }
            if (_status__tmp113 == 3) { *_err2 = _err2__tmp113; return 2; }
        }
        til_Array_delete(&_tmp114);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp112);
        return 1;
    }
    til_Str til_substr = {.c_string = 0, .cap = 0};
    til_substr.cap = til_sub(til_end, til_start);
    til_I64 _ret__tmp119;
    til_AllocError _err0__tmp119 = {};
    int _status__tmp119 = til_malloc(&_ret__tmp119, &_err0__tmp119, til_substr.cap);
    if (_status__tmp119 == 1) { *_err2 = _err0__tmp119; return 2; }
    til_substr.c_string = _ret__tmp119;
    if (til_I64_eq(til_NULL, til_substr.c_string).data) {
        til_Str _tmp121;
        til_I64_OverflowError _err0__tmp122;
        til_IndexOutOfBoundsError _err1__tmp122;
        til_AllocError _err2__tmp122;
        til_Array _tmp123;
        til_AllocError _err_alloc__tmp124;
        til_IndexOutOfBoundsError _err_idx__tmp124;
        til_Str _tmp125 = ((til_Str){(til_I64)"Str.get_substr: failed to allocate ", 35});
        til_Str _tmp126 = til_I64_to_str(til_substr.cap);
        til_Str _tmp127 = ((til_Str){(til_I64)" bytes", 6});
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
        int _status__tmp122 = til_format(&_tmp121, &_err0__tmp122, &_err1__tmp122, &_err2__tmp122, ((til_Str){(til_I64)"src/core/str.til:387:37:", 24}), &_tmp123);
        if (_status__tmp122 != 0) {
            if (_status__tmp122 == 2) { *_err1 = _err1__tmp122; return 1; }
            if (_status__tmp122 == 3) { *_err2 = _err2__tmp122; return 2; }
        }
        til_Array_delete(&_tmp123);
        til_Str _tmp128;
        til_I64_OverflowError _err0__tmp129;
        til_IndexOutOfBoundsError _err1__tmp129;
        til_AllocError _err2__tmp129;
        til_Array _tmp130;
        til_AllocError _err_alloc__tmp131;
        til_IndexOutOfBoundsError _err_idx__tmp131;
        til_Str _tmp132 = ((til_Str){(til_I64)"Str.get_substr: failed to allocate ", 35});
        til_Str _tmp133 = til_I64_to_str(til_substr.cap);
        til_Str _tmp134 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp131 = til_Array_new(&_tmp130, &_err_alloc__tmp131, "Str", 3);
        if (_arr_status__tmp131 != 0) {
            *_err2 = _err_alloc__tmp131; return 2;
        }
        _arr_status__tmp131 = til_Array_set(&_err_idx__tmp131, &_tmp130, 0, &_tmp132);
        if (_arr_status__tmp131 != 0) {
            *_err1 = _err_idx__tmp131; return 1;
        }
        _arr_status__tmp131 = til_Array_set(&_err_idx__tmp131, &_tmp130, 1, &_tmp133);
        if (_arr_status__tmp131 != 0) {
            *_err1 = _err_idx__tmp131; return 1;
        }
        _arr_status__tmp131 = til_Array_set(&_err_idx__tmp131, &_tmp130, 2, &_tmp134);
        if (_arr_status__tmp131 != 0) {
            *_err1 = _err_idx__tmp131; return 1;
        }
        int _status__tmp129 = til_format(&_tmp128, &_err0__tmp129, &_err1__tmp129, &_err2__tmp129, ((til_Str){(til_I64)"src/core/str.til:387:37:", 24}), &_tmp130);
        if (_status__tmp129 != 0) {
            if (_status__tmp129 == 2) { *_err1 = _err1__tmp129; return 1; }
            if (_status__tmp129 == 3) { *_err2 = _err2__tmp129; return 2; }
        }
        til_Array_delete(&_tmp130);
        *_err2 = til_AllocError_new(_tmp128);
        return 2;
    }
    til_memcpy(til_substr.c_string, til_add(til_s.c_string, til_start), til_substr.cap);
    *_ret = til_substr;
    return 0;
}

til_Str til_concat(const til_Str til_a, const til_Str til_b) {
    til_AllocError _thrown_AllocError__tmp135;
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_add(til_a.cap, til_b.cap);
    if (til_lt(til_result.cap, til_a.cap).data) {
        til_Array _tmp137;
        til_AllocError _err_alloc__tmp138;
        til_IndexOutOfBoundsError _err_idx__tmp138;
        til_Str _tmp139 = ((til_Str){(til_I64)"concat: integer overflow", 24});
        int _arr_status__tmp138 = til_Array_new(&_tmp137, &_err_alloc__tmp138, "Str", 1);
        if (_arr_status__tmp138 != 0) {
        }
        _arr_status__tmp138 = til_Array_set(&_err_idx__tmp138, &_tmp137, 0, &_tmp139);
        if (_arr_status__tmp138 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:427:15:", 24}), &_tmp137);
        til_Array_delete(&_tmp137);
    }
    til_I64 _ret__tmp140;
    til_AllocError _err0__tmp140 = {};
    int _status__tmp140 = til_malloc(&_ret__tmp140, &_err0__tmp140, til_result.cap);
    if (_status__tmp140 == 0) {
        til_result.c_string = _ret__tmp140;
    } else if (_status__tmp140 == 1) {
        til_AllocError til_err = _err0__tmp140;
        til_Array _tmp142;
        til_AllocError _err_alloc__tmp143;
        til_IndexOutOfBoundsError _err_idx__tmp143;
        til_Str _tmp144 = til_err.msg;
        int _arr_status__tmp143 = til_Array_new(&_tmp142, &_err_alloc__tmp143, "Str", 1);
        if (_arr_status__tmp143 != 0) {
        }
        _arr_status__tmp143 = til_Array_set(&_err_idx__tmp143, &_tmp142, 0, &_tmp144);
        if (_arr_status__tmp143 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:439:15:", 24}), &_tmp142);
        til_Array_delete(&_tmp142);
    }
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Array _tmp146;
        til_AllocError _err_alloc__tmp147;
        til_IndexOutOfBoundsError _err_idx__tmp147;
        til_Str _tmp148 = ((til_Str){(til_I64)"concat: malloc failed", 21});
        int _arr_status__tmp147 = til_Array_new(&_tmp146, &_err_alloc__tmp147, "Str", 1);
        if (_arr_status__tmp147 != 0) {
        }
        _arr_status__tmp147 = til_Array_set(&_err_idx__tmp147, &_tmp146, 0, &_tmp148);
        if (_arr_status__tmp147 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:432:15:", 24}), &_tmp146);
        til_Array_delete(&_tmp146);
    }
    til_memcpy(til_result.c_string, til_a.c_string, til_a.cap);
    til_memcpy(til_add(til_result.c_string, til_a.cap), til_b.c_string, til_b.cap);
    return til_result;
    goto _end_catches__tmp135;
_catch_AllocError__tmp135: {
    til_AllocError til_err = _thrown_AllocError__tmp135;
    til_Array _tmp150;
    til_AllocError _err_alloc__tmp151;
    til_IndexOutOfBoundsError _err_idx__tmp151;
    til_Str _tmp152 = til_err.msg;
    int _arr_status__tmp151 = til_Array_new(&_tmp150, &_err_alloc__tmp151, "Str", 1);
    if (_arr_status__tmp151 != 0) {
    }
    _arr_status__tmp151 = til_Array_set(&_err_idx__tmp151, &_tmp150, 0, &_tmp152);
    if (_arr_status__tmp151 != 0) {
    }
    til_panic(((til_Str){(til_I64)"src/core/str.til:439:15:", 24}), &_tmp150);
    til_Array_delete(&_tmp150);
    }
_end_catches__tmp135:;
}

int til_format(til_Str* _ret, til_I64_OverflowError* _err1, til_IndexOutOfBoundsError* _err2, til_AllocError* _err3, const til_Str til_prefix, til_Array* til_args) {
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_prefix.cap;
    til_I64 til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Str til_arg = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp156 = {};
        int _status__tmp156 = til_Array_get(&_err0__tmp156, (*til_args), til_i, (til_Dynamic*)&til_arg);
        if (_status__tmp156 == 1) { *_err2 = _err0__tmp156; return 2; }
        til_result.cap = til_add(til_result.cap, til_arg.cap);
        if (til_lt(til_result.cap, til_arg.cap).data) {
            til_Str _tmp158;
            til_I64_OverflowError _err0__tmp159;
            til_IndexOutOfBoundsError _err1__tmp159;
            til_AllocError _err2__tmp159;
            til_Array _tmp160;
            til_AllocError _err_alloc__tmp161;
            til_IndexOutOfBoundsError _err_idx__tmp161;
            til_Str _tmp162 = ((til_Str){(til_I64)"format: integer overflow while summing cap for arg ", 51});
            til_Str _tmp163 = til_I64_to_str(til_i);
            int _arr_status__tmp161 = til_Array_new(&_tmp160, &_err_alloc__tmp161, "Str", 2);
            if (_arr_status__tmp161 != 0) {
                *_err3 = _err_alloc__tmp161; return 3;
            }
            _arr_status__tmp161 = til_Array_set(&_err_idx__tmp161, &_tmp160, 0, &_tmp162);
            if (_arr_status__tmp161 != 0) {
                *_err2 = _err_idx__tmp161; return 2;
            }
            _arr_status__tmp161 = til_Array_set(&_err_idx__tmp161, &_tmp160, 1, &_tmp163);
            if (_arr_status__tmp161 != 0) {
                *_err2 = _err_idx__tmp161; return 2;
            }
            int _status__tmp159 = til_format(&_tmp158, &_err0__tmp159, &_err1__tmp159, &_err2__tmp159, ((til_Str){(til_I64)"src/core/str.til:455:48:", 24}), &_tmp160);
            if (_status__tmp159 != 0) {
                if (_status__tmp159 == 1) { *_err1 = _err0__tmp159; return 1; }
                if (_status__tmp159 == 2) { *_err2 = _err1__tmp159; return 2; }
                if (_status__tmp159 == 3) { *_err3 = _err2__tmp159; return 3; }
            }
            til_Array_delete(&_tmp160);
            til_Str _tmp164;
            til_I64_OverflowError _err0__tmp165;
            til_IndexOutOfBoundsError _err1__tmp165;
            til_AllocError _err2__tmp165;
            til_Array _tmp166;
            til_AllocError _err_alloc__tmp167;
            til_IndexOutOfBoundsError _err_idx__tmp167;
            til_Str _tmp168 = ((til_Str){(til_I64)"format: integer overflow while summing cap for arg ", 51});
            til_Str _tmp169 = til_I64_to_str(til_i);
            int _arr_status__tmp167 = til_Array_new(&_tmp166, &_err_alloc__tmp167, "Str", 2);
            if (_arr_status__tmp167 != 0) {
                *_err3 = _err_alloc__tmp167; return 3;
            }
            _arr_status__tmp167 = til_Array_set(&_err_idx__tmp167, &_tmp166, 0, &_tmp168);
            if (_arr_status__tmp167 != 0) {
                *_err2 = _err_idx__tmp167; return 2;
            }
            _arr_status__tmp167 = til_Array_set(&_err_idx__tmp167, &_tmp166, 1, &_tmp169);
            if (_arr_status__tmp167 != 0) {
                *_err2 = _err_idx__tmp167; return 2;
            }
            int _status__tmp165 = til_format(&_tmp164, &_err0__tmp165, &_err1__tmp165, &_err2__tmp165, ((til_Str){(til_I64)"src/core/str.til:455:48:", 24}), &_tmp166);
            if (_status__tmp165 != 0) {
                if (_status__tmp165 == 1) { *_err1 = _err0__tmp165; return 1; }
                if (_status__tmp165 == 2) { *_err2 = _err1__tmp165; return 2; }
                if (_status__tmp165 == 3) { *_err3 = _err2__tmp165; return 3; }
            }
            til_Array_delete(&_tmp166);
            *_err1 = til_I64_OverflowError_new(_tmp164);
            return 1;
        }
        til_I64_inc(&til_i);
    }
    til_I64 _ret__tmp170;
    til_AllocError _err0__tmp170 = {};
    int _status__tmp170 = til_malloc(&_ret__tmp170, &_err0__tmp170, til_result.cap);
    if (_status__tmp170 == 1) { *_err3 = _err0__tmp170; return 3; }
    til_result.c_string = _ret__tmp170;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Str _tmp172;
        til_I64_OverflowError _err0__tmp173;
        til_IndexOutOfBoundsError _err1__tmp173;
        til_AllocError _err2__tmp173;
        til_Array _tmp174;
        til_AllocError _err_alloc__tmp175;
        til_IndexOutOfBoundsError _err_idx__tmp175;
        til_Str _tmp176 = ((til_Str){(til_I64)"format: malloc failed for cap = ", 32});
        til_Str _tmp177 = til_I64_to_str(til_result.cap);
        int _arr_status__tmp175 = til_Array_new(&_tmp174, &_err_alloc__tmp175, "Str", 2);
        if (_arr_status__tmp175 != 0) {
            *_err3 = _err_alloc__tmp175; return 3;
        }
        _arr_status__tmp175 = til_Array_set(&_err_idx__tmp175, &_tmp174, 0, &_tmp176);
        if (_arr_status__tmp175 != 0) {
            *_err2 = _err_idx__tmp175; return 2;
        }
        _arr_status__tmp175 = til_Array_set(&_err_idx__tmp175, &_tmp174, 1, &_tmp177);
        if (_arr_status__tmp175 != 0) {
            *_err2 = _err_idx__tmp175; return 2;
        }
        int _status__tmp173 = til_format(&_tmp172, &_err0__tmp173, &_err1__tmp173, &_err2__tmp173, ((til_Str){(til_I64)"src/core/str.til:461:37:", 24}), &_tmp174);
        if (_status__tmp173 != 0) {
            if (_status__tmp173 == 1) { *_err1 = _err0__tmp173; return 1; }
            if (_status__tmp173 == 2) { *_err2 = _err1__tmp173; return 2; }
            if (_status__tmp173 == 3) { *_err3 = _err2__tmp173; return 3; }
        }
        til_Array_delete(&_tmp174);
        til_Str _tmp178;
        til_I64_OverflowError _err0__tmp179;
        til_IndexOutOfBoundsError _err1__tmp179;
        til_AllocError _err2__tmp179;
        til_Array _tmp180;
        til_AllocError _err_alloc__tmp181;
        til_IndexOutOfBoundsError _err_idx__tmp181;
        til_Str _tmp182 = ((til_Str){(til_I64)"format: malloc failed for cap = ", 32});
        til_Str _tmp183 = til_I64_to_str(til_result.cap);
        int _arr_status__tmp181 = til_Array_new(&_tmp180, &_err_alloc__tmp181, "Str", 2);
        if (_arr_status__tmp181 != 0) {
            *_err3 = _err_alloc__tmp181; return 3;
        }
        _arr_status__tmp181 = til_Array_set(&_err_idx__tmp181, &_tmp180, 0, &_tmp182);
        if (_arr_status__tmp181 != 0) {
            *_err2 = _err_idx__tmp181; return 2;
        }
        _arr_status__tmp181 = til_Array_set(&_err_idx__tmp181, &_tmp180, 1, &_tmp183);
        if (_arr_status__tmp181 != 0) {
            *_err2 = _err_idx__tmp181; return 2;
        }
        int _status__tmp179 = til_format(&_tmp178, &_err0__tmp179, &_err1__tmp179, &_err2__tmp179, ((til_Str){(til_I64)"src/core/str.til:461:37:", 24}), &_tmp180);
        if (_status__tmp179 != 0) {
            if (_status__tmp179 == 1) { *_err1 = _err0__tmp179; return 1; }
            if (_status__tmp179 == 2) { *_err2 = _err1__tmp179; return 2; }
            if (_status__tmp179 == 3) { *_err3 = _err2__tmp179; return 3; }
        }
        til_Array_delete(&_tmp180);
        *_err3 = til_AllocError_new(_tmp178);
        return 3;
    }
    til_I64 til_offset = 0;
    til_memcpy(til_result.c_string, til_prefix.c_string, til_prefix.cap);
    til_offset = til_prefix.cap;
    til_i = 0;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_Str til_s = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp186 = {};
        int _status__tmp186 = til_Array_get(&_err0__tmp186, (*til_args), til_i, (til_Dynamic*)&til_s);
        if (_status__tmp186 == 1) { *_err2 = _err0__tmp186; return 2; }
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

int til_Array_new(til_Array* _ret, til_AllocError* _err1, const til_Type til_T, const til_I64 til_capacity) {
    til_Array til_arr = {.type_name = ((til_Str){(til_I64)"", 0}), .type_size = 0, .ptr = 0, ._len = 0};
    til_arr.type_name = ((til_Str){(til_I64)"T", 1});
    til_arr.type_size = til_size_of(((til_Str){(til_I64)til_T, strlen(til_T)}));
    const til_I64 til_size_bytes = til_mul(til_capacity, til_arr.type_size);
    til_I64 _ret__tmp191;
    til_AllocError _err0__tmp191 = {};
    int _status__tmp191 = til_malloc(&_ret__tmp191, &_err0__tmp191, til_size_bytes);
    if (_status__tmp191 == 1) { *_err1 = _err0__tmp191; return 1; }
    til_arr.ptr = _ret__tmp191;
    til_U8 _tmp192;
    til_U8_OverflowError _err0__tmp193;
    int _status__tmp193 = til_U8_from_i64(&_tmp192, &_err0__tmp193, 0);
    if (_status__tmp193 != 0) {
    }
    til_memset(til_arr.ptr, _tmp192, til_size_bytes);
    til_arr._len = til_capacity;
    *_ret = til_arr;
    return 0;
}

int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array til_self, const til_I64 til_index, til_Dynamic* til_T) {
    if (til_gteq(til_index, til_self._len).data) {
        til_Str _tmp196;
        til_I64_OverflowError _err0__tmp197;
        til_IndexOutOfBoundsError _err1__tmp197;
        til_AllocError _err2__tmp197;
        til_Array _tmp198;
        til_AllocError _err_alloc__tmp199;
        til_IndexOutOfBoundsError _err_idx__tmp199;
        til_Str _tmp200 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        int _arr_status__tmp199 = til_Array_new(&_tmp198, &_err_alloc__tmp199, "Str", 1);
        if (_arr_status__tmp199 != 0) {
        }
        _arr_status__tmp199 = til_Array_set(&_err_idx__tmp199, &_tmp198, 0, &_tmp200);
        if (_arr_status__tmp199 != 0) {
            *_err1 = _err_idx__tmp199; return 1;
        }
        int _status__tmp197 = til_format(&_tmp196, &_err0__tmp197, &_err1__tmp197, &_err2__tmp197, ((til_Str){(til_I64)"src/core/array.til:41:52:", 25}), &_tmp198);
        if (_status__tmp197 != 0) {
            if (_status__tmp197 == 2) { *_err1 = _err1__tmp197; return 1; }
        }
        til_Array_delete(&_tmp198);
        til_Str _tmp201;
        til_I64_OverflowError _err0__tmp202;
        til_IndexOutOfBoundsError _err1__tmp202;
        til_AllocError _err2__tmp202;
        til_Array _tmp203;
        til_AllocError _err_alloc__tmp204;
        til_IndexOutOfBoundsError _err_idx__tmp204;
        til_Str _tmp205 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        int _arr_status__tmp204 = til_Array_new(&_tmp203, &_err_alloc__tmp204, "Str", 1);
        if (_arr_status__tmp204 != 0) {
        }
        _arr_status__tmp204 = til_Array_set(&_err_idx__tmp204, &_tmp203, 0, &_tmp205);
        if (_arr_status__tmp204 != 0) {
            *_err1 = _err_idx__tmp204; return 1;
        }
        int _status__tmp202 = til_format(&_tmp201, &_err0__tmp202, &_err1__tmp202, &_err2__tmp202, ((til_Str){(til_I64)"src/core/array.til:41:52:", 25}), &_tmp203);
        if (_status__tmp202 != 0) {
            if (_status__tmp202 == 2) { *_err1 = _err1__tmp202; return 1; }
        }
        til_Array_delete(&_tmp203);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp201);
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_gteq(til_index, til_self->_len).data) {
        til_Str _tmp208;
        til_I64_OverflowError _err0__tmp209;
        til_IndexOutOfBoundsError _err1__tmp209;
        til_AllocError _err2__tmp209;
        til_Array _tmp210;
        til_AllocError _err_alloc__tmp211;
        til_IndexOutOfBoundsError _err_idx__tmp211;
        til_Str _tmp212 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        int _arr_status__tmp211 = til_Array_new(&_tmp210, &_err_alloc__tmp211, "Str", 1);
        if (_arr_status__tmp211 != 0) {
        }
        _arr_status__tmp211 = til_Array_set(&_err_idx__tmp211, &_tmp210, 0, &_tmp212);
        if (_arr_status__tmp211 != 0) {
            *_err1 = _err_idx__tmp211; return 1;
        }
        int _status__tmp209 = til_format(&_tmp208, &_err0__tmp209, &_err1__tmp209, &_err2__tmp209, ((til_Str){(til_I64)"src/core/array.til:56:52:", 25}), &_tmp210);
        if (_status__tmp209 != 0) {
            if (_status__tmp209 == 2) { *_err1 = _err1__tmp209; return 1; }
        }
        til_Array_delete(&_tmp210);
        til_Str _tmp213;
        til_I64_OverflowError _err0__tmp214;
        til_IndexOutOfBoundsError _err1__tmp214;
        til_AllocError _err2__tmp214;
        til_Array _tmp215;
        til_AllocError _err_alloc__tmp216;
        til_IndexOutOfBoundsError _err_idx__tmp216;
        til_Str _tmp217 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        int _arr_status__tmp216 = til_Array_new(&_tmp215, &_err_alloc__tmp216, "Str", 1);
        if (_arr_status__tmp216 != 0) {
        }
        _arr_status__tmp216 = til_Array_set(&_err_idx__tmp216, &_tmp215, 0, &_tmp217);
        if (_arr_status__tmp216 != 0) {
            *_err1 = _err_idx__tmp216; return 1;
        }
        int _status__tmp214 = til_format(&_tmp213, &_err0__tmp214, &_err1__tmp214, &_err2__tmp214, ((til_Str){(til_I64)"src/core/array.til:56:52:", 25}), &_tmp215);
        if (_status__tmp214 != 0) {
            if (_status__tmp214 == 2) { *_err1 = _err1__tmp214; return 1; }
        }
        til_Array_delete(&_tmp215);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp213);
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
    til_I64 _ret__tmp229;
    til_AllocError _err0__tmp229 = {};
    int _status__tmp229 = til_malloc(&_ret__tmp229, &_err0__tmp229, til_size_bytes);
    if (_status__tmp229 == 1) { *_err1 = _err0__tmp229; return 1; }
    til_vec.ptr = _ret__tmp229;
    til_vec._len = 0;
    til_vec.cap = til_Vec_INIT_CAP;
    *_ret = til_vec;
    return 0;
}

int til_Vec_push(til_AllocError* _err1, til_Vec* til_self, const til_Dynamic til_value) {
    if (til_I64_eq(til_self->_len, til_self->cap).data) {
        const til_I64 til_new_cap = til_mul(til_self->cap, 2);
        if (til_gt(til_new_cap, til_Vec_MAX_CAP).data) {
            til_Array _tmp233;
            til_AllocError _err_alloc__tmp234;
            til_IndexOutOfBoundsError _err_idx__tmp234;
            til_Str _tmp235 = ((til_Str){(til_I64)"Vec.push: capacity exceeded Vec.MAX_CAP", 39});
            int _arr_status__tmp234 = til_Array_new(&_tmp233, &_err_alloc__tmp234, "Str", 1);
            if (_arr_status__tmp234 != 0) {
                *_err1 = _err_alloc__tmp234; return 1;
            }
            _arr_status__tmp234 = til_Array_set(&_err_idx__tmp234, &_tmp233, 0, &_tmp235);
            if (_arr_status__tmp234 != 0) {
            }
            til_panic(((til_Str){(til_I64)"src/core/vec.til:63:23:", 23}), &_tmp233);
            til_Array_delete(&_tmp233);
        }
        til_I64 _ret__tmp236;
        til_I64 til_new_ptr;
        til_AllocError _err0__tmp236 = {};
        int _status__tmp236 = til_malloc(&_ret__tmp236, &_err0__tmp236, til_mul(til_new_cap, til_self->type_size));
        if (_status__tmp236 == 1) { *_err1 = _err0__tmp236; return 1; }
        til_new_ptr = _ret__tmp236;
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
        til_Str _tmp239;
        til_I64_OverflowError _err0__tmp240;
        til_IndexOutOfBoundsError _err1__tmp240;
        til_AllocError _err2__tmp240;
        til_Array _tmp241;
        til_AllocError _err_alloc__tmp242;
        til_IndexOutOfBoundsError _err_idx__tmp242;
        til_Str _tmp243 = ((til_Str){(til_I64)"Vec.get: index out of bounds", 28});
        int _arr_status__tmp242 = til_Array_new(&_tmp241, &_err_alloc__tmp242, "Str", 1);
        if (_arr_status__tmp242 != 0) {
        }
        _arr_status__tmp242 = til_Array_set(&_err_idx__tmp242, &_tmp241, 0, &_tmp243);
        if (_arr_status__tmp242 != 0) {
            *_err1 = _err_idx__tmp242; return 1;
        }
        int _status__tmp240 = til_format(&_tmp239, &_err0__tmp240, &_err1__tmp240, &_err2__tmp240, ((til_Str){(til_I64)"src/core/vec.til:81:52:", 23}), &_tmp241);
        if (_status__tmp240 != 0) {
            if (_status__tmp240 == 2) { *_err1 = _err1__tmp240; return 1; }
        }
        til_Array_delete(&_tmp241);
        til_Str _tmp244;
        til_I64_OverflowError _err0__tmp245;
        til_IndexOutOfBoundsError _err1__tmp245;
        til_AllocError _err2__tmp245;
        til_Array _tmp246;
        til_AllocError _err_alloc__tmp247;
        til_IndexOutOfBoundsError _err_idx__tmp247;
        til_Str _tmp248 = ((til_Str){(til_I64)"Vec.get: index out of bounds", 28});
        int _arr_status__tmp247 = til_Array_new(&_tmp246, &_err_alloc__tmp247, "Str", 1);
        if (_arr_status__tmp247 != 0) {
        }
        _arr_status__tmp247 = til_Array_set(&_err_idx__tmp247, &_tmp246, 0, &_tmp248);
        if (_arr_status__tmp247 != 0) {
            *_err1 = _err_idx__tmp247; return 1;
        }
        int _status__tmp245 = til_format(&_tmp244, &_err0__tmp245, &_err1__tmp245, &_err2__tmp245, ((til_Str){(til_I64)"src/core/vec.til:81:52:", 23}), &_tmp246);
        if (_status__tmp245 != 0) {
            if (_status__tmp245 == 2) { *_err1 = _err1__tmp245; return 1; }
        }
        til_Array_delete(&_tmp246);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp244);
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
    til_I64 _ret__tmp256;
    til_AllocError _err0__tmp256 = {};
    int _status__tmp256 = til_malloc(&_ret__tmp256, &_err0__tmp256, til_cloned.cap);
    if (_status__tmp256 == 1) { *_err1 = _err0__tmp256; return 1; }
    til_cloned.c_string = _ret__tmp256;
    if (til_I64_eq(til_NULL, til_cloned.c_string).data) {
        til_Str _tmp258;
        til_I64_OverflowError _err0__tmp259;
        til_IndexOutOfBoundsError _err1__tmp259;
        til_AllocError _err2__tmp259;
        til_Array _tmp260;
        til_AllocError _err_alloc__tmp261;
        til_IndexOutOfBoundsError _err_idx__tmp261;
        til_Str _tmp262 = ((til_Str){(til_I64)"Str.clone: malloc failed for ", 29});
        til_Str _tmp263 = til_I64_to_str(til_cloned.cap);
        til_Str _tmp264 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp261 = til_Array_new(&_tmp260, &_err_alloc__tmp261, "Str", 3);
        if (_arr_status__tmp261 != 0) {
            *_err1 = _err_alloc__tmp261; return 1;
        }
        _arr_status__tmp261 = til_Array_set(&_err_idx__tmp261, &_tmp260, 0, &_tmp262);
        if (_arr_status__tmp261 != 0) {
        }
        _arr_status__tmp261 = til_Array_set(&_err_idx__tmp261, &_tmp260, 1, &_tmp263);
        if (_arr_status__tmp261 != 0) {
        }
        _arr_status__tmp261 = til_Array_set(&_err_idx__tmp261, &_tmp260, 2, &_tmp264);
        if (_arr_status__tmp261 != 0) {
        }
        int _status__tmp259 = til_format(&_tmp258, &_err0__tmp259, &_err1__tmp259, &_err2__tmp259, ((til_Str){(til_I64)"src/core/str.til:46:41:", 23}), &_tmp260);
        if (_status__tmp259 != 0) {
            if (_status__tmp259 == 3) { *_err1 = _err2__tmp259; return 1; }
        }
        til_Array_delete(&_tmp260);
        til_Str _tmp265;
        til_I64_OverflowError _err0__tmp266;
        til_IndexOutOfBoundsError _err1__tmp266;
        til_AllocError _err2__tmp266;
        til_Array _tmp267;
        til_AllocError _err_alloc__tmp268;
        til_IndexOutOfBoundsError _err_idx__tmp268;
        til_Str _tmp269 = ((til_Str){(til_I64)"Str.clone: malloc failed for ", 29});
        til_Str _tmp270 = til_I64_to_str(til_cloned.cap);
        til_Str _tmp271 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp268 = til_Array_new(&_tmp267, &_err_alloc__tmp268, "Str", 3);
        if (_arr_status__tmp268 != 0) {
            *_err1 = _err_alloc__tmp268; return 1;
        }
        _arr_status__tmp268 = til_Array_set(&_err_idx__tmp268, &_tmp267, 0, &_tmp269);
        if (_arr_status__tmp268 != 0) {
        }
        _arr_status__tmp268 = til_Array_set(&_err_idx__tmp268, &_tmp267, 1, &_tmp270);
        if (_arr_status__tmp268 != 0) {
        }
        _arr_status__tmp268 = til_Array_set(&_err_idx__tmp268, &_tmp267, 2, &_tmp271);
        if (_arr_status__tmp268 != 0) {
        }
        int _status__tmp266 = til_format(&_tmp265, &_err0__tmp266, &_err1__tmp266, &_err2__tmp266, ((til_Str){(til_I64)"src/core/str.til:46:41:", 23}), &_tmp267);
        if (_status__tmp266 != 0) {
            if (_status__tmp266 == 3) { *_err1 = _err2__tmp266; return 1; }
        }
        til_Array_delete(&_tmp267);
        *_err1 = til_AllocError_new(_tmp265);
        return 1;
    }
    til_memcpy(til_cloned.c_string, til_self.c_string, til_self.cap);
    *_ret = til_cloned;
    return 0;
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
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp281;
    if (til_I64_eq(til_Str_len(til_from), 0).data) {
        til_Str _ret__tmp283;
        til_AllocError _err0__tmp283 = {};
        int _status__tmp283 = til_Str_clone(&_ret__tmp283, &_err0__tmp283, til_self);
        if (_status__tmp283 == 1) { *_err1 = _err0__tmp283; return 1; }
        *_ret = _ret__tmp283;
        return 0;
    }
    if (til_I64_eq(til_n, 0).data) {
        til_Str _ret__tmp285;
        til_AllocError _err0__tmp285 = {};
        int _status__tmp285 = til_Str_clone(&_ret__tmp285, &_err0__tmp285, til_self);
        if (_status__tmp285 == 1) { *_err1 = _err0__tmp285; return 1; }
        *_ret = _ret__tmp285;
        return 0;
    }
    til_I64 til_idx = til_Str_find(til_self, til_from);
    if (til_lt(til_idx, 0).data) {
        til_Str _ret__tmp287;
        til_AllocError _err0__tmp287 = {};
        int _status__tmp287 = til_Str_clone(&_ret__tmp287, &_err0__tmp287, til_self);
        if (_status__tmp287 == 1) { *_err1 = _err0__tmp287; return 1; }
        *_ret = _ret__tmp287;
        return 0;
    }
    til_Str _ret__tmp288;
    til_Str til_prefix;
    til_IndexOutOfBoundsError _err0__tmp288 = {};
    til_AllocError _err1__tmp288 = {};
    int _status__tmp288 = til_get_substr(&_ret__tmp288, &_err0__tmp288, &_err1__tmp288, til_self, 0, til_idx);
    if (_status__tmp288 == 2) { *_err1 = _err1__tmp288; return 1; }
    til_prefix = _ret__tmp288;
    til_Str _ret__tmp289;
    til_Str til_suffix;
    til_IndexOutOfBoundsError _err0__tmp289 = {};
    til_AllocError _err1__tmp289 = {};
    int _status__tmp289 = til_get_substr(&_ret__tmp289, &_err0__tmp289, &_err1__tmp289, til_self, til_add(til_idx, til_Str_len(til_from)), til_Str_len(til_self));
    if (_status__tmp289 == 2) { *_err1 = _err1__tmp289; return 1; }
    til_suffix = _ret__tmp289;
    til_Str til_result = til_concat(til_concat(til_prefix, til_to), til_suffix);
    if (til_gt(til_n, 1).data) {
        til_Str _ret__tmp291;
        til_Str til_rest;
        til_AllocError _err0__tmp291 = {};
        int _status__tmp291 = til_Str_replacen(&_ret__tmp291, &_err0__tmp291, til_suffix, til_from, til_to, til_sub(til_n, 1));
        if (_status__tmp291 == 1) { *_err1 = _err0__tmp291; return 1; }
        til_rest = _ret__tmp291;
        til_result = til_concat(til_concat(til_prefix, til_to), til_rest);
    }
    *_ret = til_result;
    return 0;
    goto _end_catches__tmp281;
_catch_IndexOutOfBoundsError__tmp281: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp281;
    til_Str _ret__tmp293;
    til_AllocError _err0__tmp293 = {};
    int _status__tmp293 = til_Str_clone(&_ret__tmp293, &_err0__tmp293, til_self);
    if (_status__tmp293 == 1) { *_err1 = _err0__tmp293; return 1; }
    til_result = _ret__tmp293;
    }
_end_catches__tmp281:;
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
        til_Str _tmp299;
        til_I64_OverflowError _err0__tmp300;
        til_IndexOutOfBoundsError _err1__tmp300;
        til_AllocError _err2__tmp300;
        til_Array _tmp301;
        til_AllocError _err_alloc__tmp302;
        til_IndexOutOfBoundsError _err_idx__tmp302;
        til_Str _tmp303 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        int _arr_status__tmp302 = til_Array_new(&_tmp301, &_err_alloc__tmp302, "Str", 1);
        if (_arr_status__tmp302 != 0) {
        }
        _arr_status__tmp302 = til_Array_set(&_err_idx__tmp302, &_tmp301, 0, &_tmp303);
        if (_arr_status__tmp302 != 0) {
        }
        int _status__tmp300 = til_format(&_tmp299, &_err0__tmp300, &_err1__tmp300, &_err2__tmp300, ((til_Str){(til_I64)"src/core/u8.til:56:47:", 22}), &_tmp301);
        if (_status__tmp300 != 0) {
        }
        til_Array_delete(&_tmp301);
        til_Str _tmp304;
        til_I64_OverflowError _err0__tmp305;
        til_IndexOutOfBoundsError _err1__tmp305;
        til_AllocError _err2__tmp305;
        til_Array _tmp306;
        til_AllocError _err_alloc__tmp307;
        til_IndexOutOfBoundsError _err_idx__tmp307;
        til_Str _tmp308 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        int _arr_status__tmp307 = til_Array_new(&_tmp306, &_err_alloc__tmp307, "Str", 1);
        if (_arr_status__tmp307 != 0) {
        }
        _arr_status__tmp307 = til_Array_set(&_err_idx__tmp307, &_tmp306, 0, &_tmp308);
        if (_arr_status__tmp307 != 0) {
        }
        int _status__tmp305 = til_format(&_tmp304, &_err0__tmp305, &_err1__tmp305, &_err2__tmp305, ((til_Str){(til_I64)"src/core/u8.til:56:47:", 22}), &_tmp306);
        if (_status__tmp305 != 0) {
        }
        til_Array_delete(&_tmp306);
        *_err1 = til_U8_OverflowError_new(_tmp304);
        return 1;
    }
    if (til_gt(til_self, til_MAX_U8).data) {
        til_Str _tmp310;
        til_I64_OverflowError _err0__tmp311;
        til_IndexOutOfBoundsError _err1__tmp311;
        til_AllocError _err2__tmp311;
        til_Array _tmp312;
        til_AllocError _err_alloc__tmp313;
        til_IndexOutOfBoundsError _err_idx__tmp313;
        til_Str _tmp314 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp315 = ((til_Str){(til_I64)"255", 3});
        int _arr_status__tmp313 = til_Array_new(&_tmp312, &_err_alloc__tmp313, "Str", 2);
        if (_arr_status__tmp313 != 0) {
        }
        _arr_status__tmp313 = til_Array_set(&_err_idx__tmp313, &_tmp312, 0, &_tmp314);
        if (_arr_status__tmp313 != 0) {
        }
        _arr_status__tmp313 = til_Array_set(&_err_idx__tmp313, &_tmp312, 1, &_tmp315);
        if (_arr_status__tmp313 != 0) {
        }
        int _status__tmp311 = til_format(&_tmp310, &_err0__tmp311, &_err1__tmp311, &_err2__tmp311, ((til_Str){(til_I64)"src/core/u8.til:59:47:", 22}), &_tmp312);
        if (_status__tmp311 != 0) {
        }
        til_Array_delete(&_tmp312);
        til_Str _tmp316;
        til_I64_OverflowError _err0__tmp317;
        til_IndexOutOfBoundsError _err1__tmp317;
        til_AllocError _err2__tmp317;
        til_Array _tmp318;
        til_AllocError _err_alloc__tmp319;
        til_IndexOutOfBoundsError _err_idx__tmp319;
        til_Str _tmp320 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp321 = ((til_Str){(til_I64)"255", 3});
        int _arr_status__tmp319 = til_Array_new(&_tmp318, &_err_alloc__tmp319, "Str", 2);
        if (_arr_status__tmp319 != 0) {
        }
        _arr_status__tmp319 = til_Array_set(&_err_idx__tmp319, &_tmp318, 0, &_tmp320);
        if (_arr_status__tmp319 != 0) {
        }
        _arr_status__tmp319 = til_Array_set(&_err_idx__tmp319, &_tmp318, 1, &_tmp321);
        if (_arr_status__tmp319 != 0) {
        }
        int _status__tmp317 = til_format(&_tmp316, &_err0__tmp317, &_err1__tmp317, &_err2__tmp317, ((til_Str){(til_I64)"src/core/u8.til:59:47:", 22}), &_tmp318);
        if (_status__tmp317 != 0) {
        }
        til_Array_delete(&_tmp318);
        *_err1 = til_U8_OverflowError_new(_tmp316);
        return 1;
    }
    *_ret = til_i64_to_u8(til_self);
    return 0;
}

int main() {
    til_Array _tmp323;
    til_AllocError _err_alloc__tmp324;
    til_IndexOutOfBoundsError _err_idx__tmp324;
    til_Str _tmp325 = ((til_Str){(til_I64)"Hello World!", 12});
    int _arr_status__tmp324 = til_Array_new(&_tmp323, &_err_alloc__tmp324, "Str", 1);
    if (_arr_status__tmp324 != 0) {
    }
    _arr_status__tmp324 = til_Array_set(&_err_idx__tmp324, &_tmp323, 0, &_tmp325);
    if (_arr_status__tmp324 != 0) {
    }
    til_println(&_tmp323);
    til_Array_delete(&_tmp323);
    return 0;
}
