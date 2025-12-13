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
    til_Bool til_val;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_val = false;
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
    til_panic(((til_Str){(til_I64)"src/core/bool.til:83:15:", 24}), &_tmp8);
    til_Array_delete(&_tmp8);
    goto _end_catches__tmp2;
    }
_end_catches__tmp2:;
}

til_Bool til_and(til_Array* til_args) {
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp11;
    til_I64 til_i = 0;
    til_Bool til_val;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_val = false;
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
    til_panic(((til_Str){(til_I64)"src/core/bool.til:99:15:", 24}), &_tmp17);
    til_Array_delete(&_tmp17);
    goto _end_catches__tmp11;
    }
_end_catches__tmp11:;
}

void til_panic(const til_Str til_loc_str, til_Array* til_msgs) {
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp20;
    til_single_print(til_loc_str);
    til_I64 til_i = 0;
    til_Str til_val;
    while (til_lt(til_i, til_Array_len((*til_msgs))).data) {
        til_val = ((til_Str){(til_I64)"", 0});
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

void til_println(til_Array* til_args) {
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp25;
    til_I64 til_i = 0;
    til_Str til_val;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_val = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp28 = {};
        int _status__tmp28 = til_Array_get(&_err0__tmp28, (*til_args), til_i, (til_Dynamic*)&til_val);
        if (_status__tmp28 == 1) { _thrown_IndexOutOfBoundsError__tmp25 = _err0__tmp28; goto _catch_IndexOutOfBoundsError__tmp25; }
        til_single_print(til_val);
        til_I64_inc(&til_i);
    }
    til_single_print(((til_Str){(til_I64)"\n", 1}));
    til_print_flush();
    goto _end_catches__tmp25;
_catch_IndexOutOfBoundsError__tmp25: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp25;
    til_Array _tmp30;
    til_AllocError _err_alloc__tmp31;
    til_IndexOutOfBoundsError _err_idx__tmp31;
    til_Str _tmp32 = ((til_Str){(til_I64)"println: IndexOutOfBoundsError should never happen", 50});
    int _arr_status__tmp31 = til_Array_new(&_tmp30, &_err_alloc__tmp31, "Str", 1);
    if (_arr_status__tmp31 != 0) {
    }
    _arr_status__tmp31 = til_Array_set(&_err_idx__tmp31, &_tmp30, 0, &_tmp32);
    if (_arr_status__tmp31 != 0) {
    }
    til_panic(((til_Str){(til_I64)"src/core/print.til:31:15:", 25}), &_tmp30);
    til_Array_delete(&_tmp30);
    goto _end_catches__tmp25;
    }
_end_catches__tmp25:;
}

int til_get_substr(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_start, const til_I64 til_end) {
    if (til_lt(til_start, 0).data) {
        til_Str _tmp35;
        til_I64_OverflowError _err0__tmp36;
        til_IndexOutOfBoundsError _err1__tmp36;
        til_AllocError _err2__tmp36;
        til_Array _tmp37;
        til_AllocError _err_alloc__tmp38;
        til_IndexOutOfBoundsError _err_idx__tmp38;
        til_Str _tmp39 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp40 = til_I64_to_str(til_start);
        til_Str _tmp41 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp38 = til_Array_new(&_tmp37, &_err_alloc__tmp38, "Str", 3);
        if (_arr_status__tmp38 != 0) {
            *_err2 = _err_alloc__tmp38; return 2;
        }
        _arr_status__tmp38 = til_Array_set(&_err_idx__tmp38, &_tmp37, 0, &_tmp39);
        if (_arr_status__tmp38 != 0) {
            *_err1 = _err_idx__tmp38; return 1;
        }
        _arr_status__tmp38 = til_Array_set(&_err_idx__tmp38, &_tmp37, 1, &_tmp40);
        if (_arr_status__tmp38 != 0) {
            *_err1 = _err_idx__tmp38; return 1;
        }
        _arr_status__tmp38 = til_Array_set(&_err_idx__tmp38, &_tmp37, 2, &_tmp41);
        if (_arr_status__tmp38 != 0) {
            *_err1 = _err_idx__tmp38; return 1;
        }
        int _status__tmp36 = til_format(&_tmp35, &_err0__tmp36, &_err1__tmp36, &_err2__tmp36, ((til_Str){(til_I64)"src/core/str.til:368:48:", 24}), &_tmp37);
        if (_status__tmp36 != 0) {
            if (_status__tmp36 == 2) { *_err1 = _err1__tmp36; return 1; }
            if (_status__tmp36 == 3) { *_err2 = _err2__tmp36; return 2; }
        }
        til_Array_delete(&_tmp37);
        til_Str _tmp42;
        til_I64_OverflowError _err0__tmp43;
        til_IndexOutOfBoundsError _err1__tmp43;
        til_AllocError _err2__tmp43;
        til_Array _tmp44;
        til_AllocError _err_alloc__tmp45;
        til_IndexOutOfBoundsError _err_idx__tmp45;
        til_Str _tmp46 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp47 = til_I64_to_str(til_start);
        til_Str _tmp48 = ((til_Str){(til_I64)" cannot be negative", 19});
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
        int _status__tmp43 = til_format(&_tmp42, &_err0__tmp43, &_err1__tmp43, &_err2__tmp43, ((til_Str){(til_I64)"src/core/str.til:368:48:", 24}), &_tmp44);
        if (_status__tmp43 != 0) {
            if (_status__tmp43 == 2) { *_err1 = _err1__tmp43; return 1; }
            if (_status__tmp43 == 3) { *_err2 = _err2__tmp43; return 2; }
        }
        til_Array_delete(&_tmp44);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp42);
        return 1;
    }
    if (til_lt(til_end, 0).data) {
        til_Str _tmp50;
        til_I64_OverflowError _err0__tmp51;
        til_IndexOutOfBoundsError _err1__tmp51;
        til_AllocError _err2__tmp51;
        til_Array _tmp52;
        til_AllocError _err_alloc__tmp53;
        til_IndexOutOfBoundsError _err_idx__tmp53;
        til_Str _tmp54 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp55 = til_I64_to_str(til_end);
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
        int _status__tmp51 = til_format(&_tmp50, &_err0__tmp51, &_err1__tmp51, &_err2__tmp51, ((til_Str){(til_I64)"src/core/str.til:371:48:", 24}), &_tmp52);
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
        til_Str _tmp61 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp62 = til_I64_to_str(til_end);
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
        int _status__tmp58 = til_format(&_tmp57, &_err0__tmp58, &_err1__tmp58, &_err2__tmp58, ((til_Str){(til_I64)"src/core/str.til:371:48:", 24}), &_tmp59);
        if (_status__tmp58 != 0) {
            if (_status__tmp58 == 2) { *_err1 = _err1__tmp58; return 1; }
            if (_status__tmp58 == 3) { *_err2 = _err2__tmp58; return 2; }
        }
        til_Array_delete(&_tmp59);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp57);
        return 1;
    }
    if (til_gt(til_start, til_end).data) {
        til_Str _tmp65;
        til_I64_OverflowError _err0__tmp66;
        til_IndexOutOfBoundsError _err1__tmp66;
        til_AllocError _err2__tmp66;
        til_Array _tmp67;
        til_AllocError _err_alloc__tmp68;
        til_IndexOutOfBoundsError _err_idx__tmp68;
        til_Str _tmp69 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp70 = til_I64_to_str(til_start);
        til_Str _tmp71 = ((til_Str){(til_I64)" is greater than end index ", 27});
        til_Str _tmp72 = til_I64_to_str(til_end);
        int _arr_status__tmp68 = til_Array_new(&_tmp67, &_err_alloc__tmp68, "Str", 4);
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
        _arr_status__tmp68 = til_Array_set(&_err_idx__tmp68, &_tmp67, 3, &_tmp72);
        if (_arr_status__tmp68 != 0) {
            *_err1 = _err_idx__tmp68; return 1;
        }
        int _status__tmp66 = til_format(&_tmp65, &_err0__tmp66, &_err1__tmp66, &_err2__tmp66, ((til_Str){(til_I64)"src/core/str.til:374:48:", 24}), &_tmp67);
        if (_status__tmp66 != 0) {
            if (_status__tmp66 == 2) { *_err1 = _err1__tmp66; return 1; }
            if (_status__tmp66 == 3) { *_err2 = _err2__tmp66; return 2; }
        }
        til_Array_delete(&_tmp67);
        til_Str _tmp73;
        til_I64_OverflowError _err0__tmp74;
        til_IndexOutOfBoundsError _err1__tmp74;
        til_AllocError _err2__tmp74;
        til_Array _tmp75;
        til_AllocError _err_alloc__tmp76;
        til_IndexOutOfBoundsError _err_idx__tmp76;
        til_Str _tmp77 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp78 = til_I64_to_str(til_start);
        til_Str _tmp79 = ((til_Str){(til_I64)" is greater than end index ", 27});
        til_Str _tmp80 = til_I64_to_str(til_end);
        int _arr_status__tmp76 = til_Array_new(&_tmp75, &_err_alloc__tmp76, "Str", 4);
        if (_arr_status__tmp76 != 0) {
            *_err2 = _err_alloc__tmp76; return 2;
        }
        _arr_status__tmp76 = til_Array_set(&_err_idx__tmp76, &_tmp75, 0, &_tmp77);
        if (_arr_status__tmp76 != 0) {
            *_err1 = _err_idx__tmp76; return 1;
        }
        _arr_status__tmp76 = til_Array_set(&_err_idx__tmp76, &_tmp75, 1, &_tmp78);
        if (_arr_status__tmp76 != 0) {
            *_err1 = _err_idx__tmp76; return 1;
        }
        _arr_status__tmp76 = til_Array_set(&_err_idx__tmp76, &_tmp75, 2, &_tmp79);
        if (_arr_status__tmp76 != 0) {
            *_err1 = _err_idx__tmp76; return 1;
        }
        _arr_status__tmp76 = til_Array_set(&_err_idx__tmp76, &_tmp75, 3, &_tmp80);
        if (_arr_status__tmp76 != 0) {
            *_err1 = _err_idx__tmp76; return 1;
        }
        int _status__tmp74 = til_format(&_tmp73, &_err0__tmp74, &_err1__tmp74, &_err2__tmp74, ((til_Str){(til_I64)"src/core/str.til:374:48:", 24}), &_tmp75);
        if (_status__tmp74 != 0) {
            if (_status__tmp74 == 2) { *_err1 = _err1__tmp74; return 1; }
            if (_status__tmp74 == 3) { *_err2 = _err2__tmp74; return 2; }
        }
        til_Array_delete(&_tmp75);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp73);
        return 1;
    }
    if (til_gt(til_end, til_Str_len(til_s)).data) {
        til_Str _tmp82;
        til_I64_OverflowError _err0__tmp83;
        til_IndexOutOfBoundsError _err1__tmp83;
        til_AllocError _err2__tmp83;
        til_Array _tmp84;
        til_AllocError _err_alloc__tmp85;
        til_IndexOutOfBoundsError _err_idx__tmp85;
        til_Str _tmp86 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp87 = til_I64_to_str(til_end);
        til_Str _tmp88 = ((til_Str){(til_I64)" is greater than string length ", 31});
        til_Str _tmp89 = til_I64_to_str(til_Str_len(til_s));
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
        int _status__tmp83 = til_format(&_tmp82, &_err0__tmp83, &_err1__tmp83, &_err2__tmp83, ((til_Str){(til_I64)"src/core/str.til:377:48:", 24}), &_tmp84);
        if (_status__tmp83 != 0) {
            if (_status__tmp83 == 2) { *_err1 = _err1__tmp83; return 1; }
            if (_status__tmp83 == 3) { *_err2 = _err2__tmp83; return 2; }
        }
        til_Array_delete(&_tmp84);
        til_Str _tmp90;
        til_I64_OverflowError _err0__tmp91;
        til_IndexOutOfBoundsError _err1__tmp91;
        til_AllocError _err2__tmp91;
        til_Array _tmp92;
        til_AllocError _err_alloc__tmp93;
        til_IndexOutOfBoundsError _err_idx__tmp93;
        til_Str _tmp94 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp95 = til_I64_to_str(til_end);
        til_Str _tmp96 = ((til_Str){(til_I64)" is greater than string length ", 31});
        til_Str _tmp97 = til_I64_to_str(til_Str_len(til_s));
        int _arr_status__tmp93 = til_Array_new(&_tmp92, &_err_alloc__tmp93, "Str", 4);
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
        _arr_status__tmp93 = til_Array_set(&_err_idx__tmp93, &_tmp92, 3, &_tmp97);
        if (_arr_status__tmp93 != 0) {
            *_err1 = _err_idx__tmp93; return 1;
        }
        int _status__tmp91 = til_format(&_tmp90, &_err0__tmp91, &_err1__tmp91, &_err2__tmp91, ((til_Str){(til_I64)"src/core/str.til:377:48:", 24}), &_tmp92);
        if (_status__tmp91 != 0) {
            if (_status__tmp91 == 2) { *_err1 = _err1__tmp91; return 1; }
            if (_status__tmp91 == 3) { *_err2 = _err2__tmp91; return 2; }
        }
        til_Array_delete(&_tmp92);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp90);
        return 1;
    }
    if (til_I64_eq(til_start, til_end).data) {
        til_Str _tmp99;
        til_I64_OverflowError _err0__tmp100;
        til_IndexOutOfBoundsError _err1__tmp100;
        til_AllocError _err2__tmp100;
        til_Array _tmp101;
        til_AllocError _err_alloc__tmp102;
        til_IndexOutOfBoundsError _err_idx__tmp102;
        til_Str _tmp103 = ((til_Str){(til_I64)"get_substr: start and end are the same (", 40});
        til_Str _tmp104 = til_I64_to_str(til_start);
        til_Str _tmp105 = ((til_Str){(til_I64)"), no substring", 15});
        int _arr_status__tmp102 = til_Array_new(&_tmp101, &_err_alloc__tmp102, "Str", 3);
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
        int _status__tmp100 = til_format(&_tmp99, &_err0__tmp100, &_err1__tmp100, &_err2__tmp100, ((til_Str){(til_I64)"src/core/str.til:380:48:", 24}), &_tmp101);
        if (_status__tmp100 != 0) {
            if (_status__tmp100 == 2) { *_err1 = _err1__tmp100; return 1; }
            if (_status__tmp100 == 3) { *_err2 = _err2__tmp100; return 2; }
        }
        til_Array_delete(&_tmp101);
        til_Str _tmp106;
        til_I64_OverflowError _err0__tmp107;
        til_IndexOutOfBoundsError _err1__tmp107;
        til_AllocError _err2__tmp107;
        til_Array _tmp108;
        til_AllocError _err_alloc__tmp109;
        til_IndexOutOfBoundsError _err_idx__tmp109;
        til_Str _tmp110 = ((til_Str){(til_I64)"get_substr: start and end are the same (", 40});
        til_Str _tmp111 = til_I64_to_str(til_start);
        til_Str _tmp112 = ((til_Str){(til_I64)"), no substring", 15});
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
        int _status__tmp107 = til_format(&_tmp106, &_err0__tmp107, &_err1__tmp107, &_err2__tmp107, ((til_Str){(til_I64)"src/core/str.til:380:48:", 24}), &_tmp108);
        if (_status__tmp107 != 0) {
            if (_status__tmp107 == 2) { *_err1 = _err1__tmp107; return 1; }
            if (_status__tmp107 == 3) { *_err2 = _err2__tmp107; return 2; }
        }
        til_Array_delete(&_tmp108);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp106);
        return 1;
    }
    til_Str til_substr = {.c_string = 0, .cap = 0};
    til_substr.cap = til_sub(til_end, til_start);
    til_I64 _ret__tmp113;
    til_AllocError _err0__tmp113 = {};
    int _status__tmp113 = til_malloc(&_ret__tmp113, &_err0__tmp113, til_substr.cap);
    if (_status__tmp113 == 1) { *_err2 = _err0__tmp113; return 2; }
    til_substr.c_string = _ret__tmp113;
    if (til_I64_eq(til_NULL, til_substr.c_string).data) {
        til_Str _tmp115;
        til_I64_OverflowError _err0__tmp116;
        til_IndexOutOfBoundsError _err1__tmp116;
        til_AllocError _err2__tmp116;
        til_Array _tmp117;
        til_AllocError _err_alloc__tmp118;
        til_IndexOutOfBoundsError _err_idx__tmp118;
        til_Str _tmp119 = ((til_Str){(til_I64)"Str.get_substr: failed to allocate ", 35});
        til_Str _tmp120 = til_I64_to_str(til_substr.cap);
        til_Str _tmp121 = ((til_Str){(til_I64)" bytes", 6});
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
        int _status__tmp116 = til_format(&_tmp115, &_err0__tmp116, &_err1__tmp116, &_err2__tmp116, ((til_Str){(til_I64)"src/core/str.til:387:37:", 24}), &_tmp117);
        if (_status__tmp116 != 0) {
            if (_status__tmp116 == 2) { *_err1 = _err1__tmp116; return 1; }
            if (_status__tmp116 == 3) { *_err2 = _err2__tmp116; return 2; }
        }
        til_Array_delete(&_tmp117);
        til_Str _tmp122;
        til_I64_OverflowError _err0__tmp123;
        til_IndexOutOfBoundsError _err1__tmp123;
        til_AllocError _err2__tmp123;
        til_Array _tmp124;
        til_AllocError _err_alloc__tmp125;
        til_IndexOutOfBoundsError _err_idx__tmp125;
        til_Str _tmp126 = ((til_Str){(til_I64)"Str.get_substr: failed to allocate ", 35});
        til_Str _tmp127 = til_I64_to_str(til_substr.cap);
        til_Str _tmp128 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp125 = til_Array_new(&_tmp124, &_err_alloc__tmp125, "Str", 3);
        if (_arr_status__tmp125 != 0) {
            *_err2 = _err_alloc__tmp125; return 2;
        }
        _arr_status__tmp125 = til_Array_set(&_err_idx__tmp125, &_tmp124, 0, &_tmp126);
        if (_arr_status__tmp125 != 0) {
            *_err1 = _err_idx__tmp125; return 1;
        }
        _arr_status__tmp125 = til_Array_set(&_err_idx__tmp125, &_tmp124, 1, &_tmp127);
        if (_arr_status__tmp125 != 0) {
            *_err1 = _err_idx__tmp125; return 1;
        }
        _arr_status__tmp125 = til_Array_set(&_err_idx__tmp125, &_tmp124, 2, &_tmp128);
        if (_arr_status__tmp125 != 0) {
            *_err1 = _err_idx__tmp125; return 1;
        }
        int _status__tmp123 = til_format(&_tmp122, &_err0__tmp123, &_err1__tmp123, &_err2__tmp123, ((til_Str){(til_I64)"src/core/str.til:387:37:", 24}), &_tmp124);
        if (_status__tmp123 != 0) {
            if (_status__tmp123 == 2) { *_err1 = _err1__tmp123; return 1; }
            if (_status__tmp123 == 3) { *_err2 = _err2__tmp123; return 2; }
        }
        til_Array_delete(&_tmp124);
        *_err2 = til_AllocError_new(_tmp122);
        return 2;
    }
    til_memcpy(til_substr.c_string, til_add(til_s.c_string, til_start), til_substr.cap);
    *_ret = til_substr;
    return 0;
}

til_Str til_concat(const til_Str til_a, const til_Str til_b) {
    til_AllocError _thrown_AllocError__tmp129;
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_add(til_a.cap, til_b.cap);
    if (til_lt(til_result.cap, til_a.cap).data) {
        til_Array _tmp131;
        til_AllocError _err_alloc__tmp132;
        til_IndexOutOfBoundsError _err_idx__tmp132;
        til_Str _tmp133 = ((til_Str){(til_I64)"concat: integer overflow", 24});
        int _arr_status__tmp132 = til_Array_new(&_tmp131, &_err_alloc__tmp132, "Str", 1);
        if (_arr_status__tmp132 != 0) {
        }
        _arr_status__tmp132 = til_Array_set(&_err_idx__tmp132, &_tmp131, 0, &_tmp133);
        if (_arr_status__tmp132 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:427:15:", 24}), &_tmp131);
        til_Array_delete(&_tmp131);
    }
    til_I64 _ret__tmp134;
    til_AllocError _err0__tmp134 = {};
    int _status__tmp134 = til_malloc(&_ret__tmp134, &_err0__tmp134, til_result.cap);
    if (_status__tmp134 == 1) { _thrown_AllocError__tmp129 = _err0__tmp134; goto _catch_AllocError__tmp129; }
    til_result.c_string = _ret__tmp134;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Array _tmp136;
        til_AllocError _err_alloc__tmp137;
        til_IndexOutOfBoundsError _err_idx__tmp137;
        til_Str _tmp138 = ((til_Str){(til_I64)"concat: malloc failed", 21});
        int _arr_status__tmp137 = til_Array_new(&_tmp136, &_err_alloc__tmp137, "Str", 1);
        if (_arr_status__tmp137 != 0) {
        }
        _arr_status__tmp137 = til_Array_set(&_err_idx__tmp137, &_tmp136, 0, &_tmp138);
        if (_arr_status__tmp137 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:432:15:", 24}), &_tmp136);
        til_Array_delete(&_tmp136);
    }
    til_memcpy(til_result.c_string, til_a.c_string, til_a.cap);
    til_memcpy(til_add(til_result.c_string, til_a.cap), til_b.c_string, til_b.cap);
    return til_result;
    goto _end_catches__tmp129;
_catch_AllocError__tmp129: {
    til_AllocError til_err = _thrown_AllocError__tmp129;
    til_Array _tmp140;
    til_AllocError _err_alloc__tmp141;
    til_IndexOutOfBoundsError _err_idx__tmp141;
    til_Str _tmp142 = til_err.msg;
    int _arr_status__tmp141 = til_Array_new(&_tmp140, &_err_alloc__tmp141, "Str", 1);
    if (_arr_status__tmp141 != 0) {
    }
    _arr_status__tmp141 = til_Array_set(&_err_idx__tmp141, &_tmp140, 0, &_tmp142);
    if (_arr_status__tmp141 != 0) {
    }
    til_panic(((til_Str){(til_I64)"src/core/str.til:439:15:", 24}), &_tmp140);
    til_Array_delete(&_tmp140);
    goto _end_catches__tmp129;
    }
_end_catches__tmp129:;
}

int til_format(til_Str* _ret, til_I64_OverflowError* _err1, til_IndexOutOfBoundsError* _err2, til_AllocError* _err3, const til_Str til_prefix, til_Array* til_args) {
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_prefix.cap;
    til_I64 til_i = 0;
    til_Str til_arg;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_arg = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp146 = {};
        int _status__tmp146 = til_Array_get(&_err0__tmp146, (*til_args), til_i, (til_Dynamic*)&til_arg);
        if (_status__tmp146 == 1) { *_err2 = _err0__tmp146; return 2; }
        til_result.cap = til_add(til_result.cap, til_arg.cap);
        if (til_lt(til_result.cap, til_arg.cap).data) {
            til_Str _tmp148;
            til_I64_OverflowError _err0__tmp149;
            til_IndexOutOfBoundsError _err1__tmp149;
            til_AllocError _err2__tmp149;
            til_Array _tmp150;
            til_AllocError _err_alloc__tmp151;
            til_IndexOutOfBoundsError _err_idx__tmp151;
            til_Str _tmp152 = ((til_Str){(til_I64)"format: integer overflow while summing cap for arg ", 51});
            til_Str _tmp153 = til_I64_to_str(til_i);
            int _arr_status__tmp151 = til_Array_new(&_tmp150, &_err_alloc__tmp151, "Str", 2);
            if (_arr_status__tmp151 != 0) {
                *_err3 = _err_alloc__tmp151; return 3;
            }
            _arr_status__tmp151 = til_Array_set(&_err_idx__tmp151, &_tmp150, 0, &_tmp152);
            if (_arr_status__tmp151 != 0) {
                *_err2 = _err_idx__tmp151; return 2;
            }
            _arr_status__tmp151 = til_Array_set(&_err_idx__tmp151, &_tmp150, 1, &_tmp153);
            if (_arr_status__tmp151 != 0) {
                *_err2 = _err_idx__tmp151; return 2;
            }
            int _status__tmp149 = til_format(&_tmp148, &_err0__tmp149, &_err1__tmp149, &_err2__tmp149, ((til_Str){(til_I64)"src/core/str.til:455:48:", 24}), &_tmp150);
            if (_status__tmp149 != 0) {
                if (_status__tmp149 == 1) { *_err1 = _err0__tmp149; return 1; }
                if (_status__tmp149 == 2) { *_err2 = _err1__tmp149; return 2; }
                if (_status__tmp149 == 3) { *_err3 = _err2__tmp149; return 3; }
            }
            til_Array_delete(&_tmp150);
            til_Str _tmp154;
            til_I64_OverflowError _err0__tmp155;
            til_IndexOutOfBoundsError _err1__tmp155;
            til_AllocError _err2__tmp155;
            til_Array _tmp156;
            til_AllocError _err_alloc__tmp157;
            til_IndexOutOfBoundsError _err_idx__tmp157;
            til_Str _tmp158 = ((til_Str){(til_I64)"format: integer overflow while summing cap for arg ", 51});
            til_Str _tmp159 = til_I64_to_str(til_i);
            int _arr_status__tmp157 = til_Array_new(&_tmp156, &_err_alloc__tmp157, "Str", 2);
            if (_arr_status__tmp157 != 0) {
                *_err3 = _err_alloc__tmp157; return 3;
            }
            _arr_status__tmp157 = til_Array_set(&_err_idx__tmp157, &_tmp156, 0, &_tmp158);
            if (_arr_status__tmp157 != 0) {
                *_err2 = _err_idx__tmp157; return 2;
            }
            _arr_status__tmp157 = til_Array_set(&_err_idx__tmp157, &_tmp156, 1, &_tmp159);
            if (_arr_status__tmp157 != 0) {
                *_err2 = _err_idx__tmp157; return 2;
            }
            int _status__tmp155 = til_format(&_tmp154, &_err0__tmp155, &_err1__tmp155, &_err2__tmp155, ((til_Str){(til_I64)"src/core/str.til:455:48:", 24}), &_tmp156);
            if (_status__tmp155 != 0) {
                if (_status__tmp155 == 1) { *_err1 = _err0__tmp155; return 1; }
                if (_status__tmp155 == 2) { *_err2 = _err1__tmp155; return 2; }
                if (_status__tmp155 == 3) { *_err3 = _err2__tmp155; return 3; }
            }
            til_Array_delete(&_tmp156);
            *_err1 = til_I64_OverflowError_new(_tmp154);
            return 1;
        }
        til_I64_inc(&til_i);
    }
    til_I64 _ret__tmp160;
    til_AllocError _err0__tmp160 = {};
    int _status__tmp160 = til_malloc(&_ret__tmp160, &_err0__tmp160, til_result.cap);
    if (_status__tmp160 == 1) { *_err3 = _err0__tmp160; return 3; }
    til_result.c_string = _ret__tmp160;
    if (til_I64_eq(til_NULL, til_result.c_string).data) {
        til_Str _tmp162;
        til_I64_OverflowError _err0__tmp163;
        til_IndexOutOfBoundsError _err1__tmp163;
        til_AllocError _err2__tmp163;
        til_Array _tmp164;
        til_AllocError _err_alloc__tmp165;
        til_IndexOutOfBoundsError _err_idx__tmp165;
        til_Str _tmp166 = ((til_Str){(til_I64)"format: malloc failed for cap = ", 32});
        til_Str _tmp167 = til_I64_to_str(til_result.cap);
        int _arr_status__tmp165 = til_Array_new(&_tmp164, &_err_alloc__tmp165, "Str", 2);
        if (_arr_status__tmp165 != 0) {
            *_err3 = _err_alloc__tmp165; return 3;
        }
        _arr_status__tmp165 = til_Array_set(&_err_idx__tmp165, &_tmp164, 0, &_tmp166);
        if (_arr_status__tmp165 != 0) {
            *_err2 = _err_idx__tmp165; return 2;
        }
        _arr_status__tmp165 = til_Array_set(&_err_idx__tmp165, &_tmp164, 1, &_tmp167);
        if (_arr_status__tmp165 != 0) {
            *_err2 = _err_idx__tmp165; return 2;
        }
        int _status__tmp163 = til_format(&_tmp162, &_err0__tmp163, &_err1__tmp163, &_err2__tmp163, ((til_Str){(til_I64)"src/core/str.til:461:37:", 24}), &_tmp164);
        if (_status__tmp163 != 0) {
            if (_status__tmp163 == 1) { *_err1 = _err0__tmp163; return 1; }
            if (_status__tmp163 == 2) { *_err2 = _err1__tmp163; return 2; }
            if (_status__tmp163 == 3) { *_err3 = _err2__tmp163; return 3; }
        }
        til_Array_delete(&_tmp164);
        til_Str _tmp168;
        til_I64_OverflowError _err0__tmp169;
        til_IndexOutOfBoundsError _err1__tmp169;
        til_AllocError _err2__tmp169;
        til_Array _tmp170;
        til_AllocError _err_alloc__tmp171;
        til_IndexOutOfBoundsError _err_idx__tmp171;
        til_Str _tmp172 = ((til_Str){(til_I64)"format: malloc failed for cap = ", 32});
        til_Str _tmp173 = til_I64_to_str(til_result.cap);
        int _arr_status__tmp171 = til_Array_new(&_tmp170, &_err_alloc__tmp171, "Str", 2);
        if (_arr_status__tmp171 != 0) {
            *_err3 = _err_alloc__tmp171; return 3;
        }
        _arr_status__tmp171 = til_Array_set(&_err_idx__tmp171, &_tmp170, 0, &_tmp172);
        if (_arr_status__tmp171 != 0) {
            *_err2 = _err_idx__tmp171; return 2;
        }
        _arr_status__tmp171 = til_Array_set(&_err_idx__tmp171, &_tmp170, 1, &_tmp173);
        if (_arr_status__tmp171 != 0) {
            *_err2 = _err_idx__tmp171; return 2;
        }
        int _status__tmp169 = til_format(&_tmp168, &_err0__tmp169, &_err1__tmp169, &_err2__tmp169, ((til_Str){(til_I64)"src/core/str.til:461:37:", 24}), &_tmp170);
        if (_status__tmp169 != 0) {
            if (_status__tmp169 == 1) { *_err1 = _err0__tmp169; return 1; }
            if (_status__tmp169 == 2) { *_err2 = _err1__tmp169; return 2; }
            if (_status__tmp169 == 3) { *_err3 = _err2__tmp169; return 3; }
        }
        til_Array_delete(&_tmp170);
        *_err3 = til_AllocError_new(_tmp168);
        return 3;
    }
    til_I64 til_offset = 0;
    til_memcpy(til_result.c_string, til_prefix.c_string, til_prefix.cap);
    til_offset = til_prefix.cap;
    til_i = 0;
    til_Str til_s;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_s = ((til_Str){(til_I64)"", 0});
        til_IndexOutOfBoundsError _err0__tmp176 = {};
        int _status__tmp176 = til_Array_get(&_err0__tmp176, (*til_args), til_i, (til_Dynamic*)&til_s);
        if (_status__tmp176 == 1) { *_err2 = _err0__tmp176; return 2; }
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
    til_I64 _ret__tmp181;
    til_AllocError _err0__tmp181 = {};
    int _status__tmp181 = til_malloc(&_ret__tmp181, &_err0__tmp181, til_size_bytes);
    if (_status__tmp181 == 1) { *_err1 = _err0__tmp181; return 1; }
    til_arr.ptr = _ret__tmp181;
    til_U8 _tmp182;
    til_U8_OverflowError _err0__tmp183;
    int _status__tmp183 = til_U8_from_i64(&_tmp182, &_err0__tmp183, 0);
    if (_status__tmp183 != 0) {
    }
    til_memset(til_arr.ptr, _tmp182, til_size_bytes);
    til_arr._len = til_capacity;
    *_ret = til_arr;
    return 0;
}

int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array til_self, const til_I64 til_index, til_Dynamic* til_T) {
    if (til_I64_gteq(til_index, til_self._len).data) {
        til_Str _tmp186;
        til_I64_OverflowError _err0__tmp187;
        til_IndexOutOfBoundsError _err1__tmp187;
        til_AllocError _err2__tmp187;
        til_Array _tmp188;
        til_AllocError _err_alloc__tmp189;
        til_IndexOutOfBoundsError _err_idx__tmp189;
        til_Str _tmp190 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        int _arr_status__tmp189 = til_Array_new(&_tmp188, &_err_alloc__tmp189, "Str", 1);
        if (_arr_status__tmp189 != 0) {
        }
        _arr_status__tmp189 = til_Array_set(&_err_idx__tmp189, &_tmp188, 0, &_tmp190);
        if (_arr_status__tmp189 != 0) {
            *_err1 = _err_idx__tmp189; return 1;
        }
        int _status__tmp187 = til_format(&_tmp186, &_err0__tmp187, &_err1__tmp187, &_err2__tmp187, ((til_Str){(til_I64)"src/core/array.til:41:52:", 25}), &_tmp188);
        if (_status__tmp187 != 0) {
            if (_status__tmp187 == 2) { *_err1 = _err1__tmp187; return 1; }
        }
        til_Array_delete(&_tmp188);
        til_Str _tmp191;
        til_I64_OverflowError _err0__tmp192;
        til_IndexOutOfBoundsError _err1__tmp192;
        til_AllocError _err2__tmp192;
        til_Array _tmp193;
        til_AllocError _err_alloc__tmp194;
        til_IndexOutOfBoundsError _err_idx__tmp194;
        til_Str _tmp195 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        int _arr_status__tmp194 = til_Array_new(&_tmp193, &_err_alloc__tmp194, "Str", 1);
        if (_arr_status__tmp194 != 0) {
        }
        _arr_status__tmp194 = til_Array_set(&_err_idx__tmp194, &_tmp193, 0, &_tmp195);
        if (_arr_status__tmp194 != 0) {
            *_err1 = _err_idx__tmp194; return 1;
        }
        int _status__tmp192 = til_format(&_tmp191, &_err0__tmp192, &_err1__tmp192, &_err2__tmp192, ((til_Str){(til_I64)"src/core/array.til:41:52:", 25}), &_tmp193);
        if (_status__tmp192 != 0) {
            if (_status__tmp192 == 2) { *_err1 = _err1__tmp192; return 1; }
        }
        til_Array_delete(&_tmp193);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp191);
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_I64_gteq(til_index, til_self->_len).data) {
        til_Str _tmp198;
        til_I64_OverflowError _err0__tmp199;
        til_IndexOutOfBoundsError _err1__tmp199;
        til_AllocError _err2__tmp199;
        til_Array _tmp200;
        til_AllocError _err_alloc__tmp201;
        til_IndexOutOfBoundsError _err_idx__tmp201;
        til_Str _tmp202 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        int _arr_status__tmp201 = til_Array_new(&_tmp200, &_err_alloc__tmp201, "Str", 1);
        if (_arr_status__tmp201 != 0) {
        }
        _arr_status__tmp201 = til_Array_set(&_err_idx__tmp201, &_tmp200, 0, &_tmp202);
        if (_arr_status__tmp201 != 0) {
            *_err1 = _err_idx__tmp201; return 1;
        }
        int _status__tmp199 = til_format(&_tmp198, &_err0__tmp199, &_err1__tmp199, &_err2__tmp199, ((til_Str){(til_I64)"src/core/array.til:56:52:", 25}), &_tmp200);
        if (_status__tmp199 != 0) {
            if (_status__tmp199 == 2) { *_err1 = _err1__tmp199; return 1; }
        }
        til_Array_delete(&_tmp200);
        til_Str _tmp203;
        til_I64_OverflowError _err0__tmp204;
        til_IndexOutOfBoundsError _err1__tmp204;
        til_AllocError _err2__tmp204;
        til_Array _tmp205;
        til_AllocError _err_alloc__tmp206;
        til_IndexOutOfBoundsError _err_idx__tmp206;
        til_Str _tmp207 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        int _arr_status__tmp206 = til_Array_new(&_tmp205, &_err_alloc__tmp206, "Str", 1);
        if (_arr_status__tmp206 != 0) {
        }
        _arr_status__tmp206 = til_Array_set(&_err_idx__tmp206, &_tmp205, 0, &_tmp207);
        if (_arr_status__tmp206 != 0) {
            *_err1 = _err_idx__tmp206; return 1;
        }
        int _status__tmp204 = til_format(&_tmp203, &_err0__tmp204, &_err1__tmp204, &_err2__tmp204, ((til_Str){(til_I64)"src/core/array.til:56:52:", 25}), &_tmp205);
        if (_status__tmp204 != 0) {
            if (_status__tmp204 == 2) { *_err1 = _err1__tmp204; return 1; }
        }
        til_Array_delete(&_tmp205);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp203);
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
    til_I64 _ret__tmp227;
    til_AllocError _err0__tmp227 = {};
    int _status__tmp227 = til_malloc(&_ret__tmp227, &_err0__tmp227, til_size_bytes);
    if (_status__tmp227 == 1) { *_err1 = _err0__tmp227; return 1; }
    til_vec.ptr = _ret__tmp227;
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
            til_Array _tmp231;
            til_AllocError _err_alloc__tmp232;
            til_IndexOutOfBoundsError _err_idx__tmp232;
            til_Str _tmp233 = ((til_Str){(til_I64)"Vec.push: capacity exceeded Vec.MAX_CAP", 39});
            int _arr_status__tmp232 = til_Array_new(&_tmp231, &_err_alloc__tmp232, "Str", 1);
            if (_arr_status__tmp232 != 0) {
                *_err1 = _err_alloc__tmp232; return 1;
            }
            _arr_status__tmp232 = til_Array_set(&_err_idx__tmp232, &_tmp231, 0, &_tmp233);
            if (_arr_status__tmp232 != 0) {
            }
            til_panic(((til_Str){(til_I64)"src/core/vec.til:63:23:", 23}), &_tmp231);
            til_Array_delete(&_tmp231);
        }
        til_I64 _ret__tmp234;
        til_I64 til_new_ptr;
        til_AllocError _err0__tmp234 = {};
        int _status__tmp234 = til_malloc(&_ret__tmp234, &_err0__tmp234, til_mul(til_new_cap, til_self->type_size));
        if (_status__tmp234 == 1) { *_err1 = _err0__tmp234; return 1; }
        til_new_ptr = _ret__tmp234;
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
        til_Str _tmp237;
        til_I64_OverflowError _err0__tmp238;
        til_IndexOutOfBoundsError _err1__tmp238;
        til_AllocError _err2__tmp238;
        til_Array _tmp239;
        til_AllocError _err_alloc__tmp240;
        til_IndexOutOfBoundsError _err_idx__tmp240;
        til_Str _tmp241 = ((til_Str){(til_I64)"Vec.get: index out of bounds", 28});
        int _arr_status__tmp240 = til_Array_new(&_tmp239, &_err_alloc__tmp240, "Str", 1);
        if (_arr_status__tmp240 != 0) {
        }
        _arr_status__tmp240 = til_Array_set(&_err_idx__tmp240, &_tmp239, 0, &_tmp241);
        if (_arr_status__tmp240 != 0) {
            *_err1 = _err_idx__tmp240; return 1;
        }
        int _status__tmp238 = til_format(&_tmp237, &_err0__tmp238, &_err1__tmp238, &_err2__tmp238, ((til_Str){(til_I64)"src/core/vec.til:81:52:", 23}), &_tmp239);
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
        til_Str _tmp246 = ((til_Str){(til_I64)"Vec.get: index out of bounds", 28});
        int _arr_status__tmp245 = til_Array_new(&_tmp244, &_err_alloc__tmp245, "Str", 1);
        if (_arr_status__tmp245 != 0) {
        }
        _arr_status__tmp245 = til_Array_set(&_err_idx__tmp245, &_tmp244, 0, &_tmp246);
        if (_arr_status__tmp245 != 0) {
            *_err1 = _err_idx__tmp245; return 1;
        }
        int _status__tmp243 = til_format(&_tmp242, &_err0__tmp243, &_err1__tmp243, &_err2__tmp243, ((til_Str){(til_I64)"src/core/vec.til:81:52:", 23}), &_tmp244);
        if (_status__tmp243 != 0) {
            if (_status__tmp243 == 2) { *_err1 = _err1__tmp243; return 1; }
        }
        til_Array_delete(&_tmp244);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp242);
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
    til_I64 _ret__tmp254;
    til_AllocError _err0__tmp254 = {};
    int _status__tmp254 = til_malloc(&_ret__tmp254, &_err0__tmp254, til_cloned.cap);
    if (_status__tmp254 == 1) { *_err1 = _err0__tmp254; return 1; }
    til_cloned.c_string = _ret__tmp254;
    if (til_I64_eq(til_NULL, til_cloned.c_string).data) {
        til_Str _tmp256;
        til_I64_OverflowError _err0__tmp257;
        til_IndexOutOfBoundsError _err1__tmp257;
        til_AllocError _err2__tmp257;
        til_Array _tmp258;
        til_AllocError _err_alloc__tmp259;
        til_IndexOutOfBoundsError _err_idx__tmp259;
        til_Str _tmp260 = ((til_Str){(til_I64)"Str.clone: malloc failed for ", 29});
        til_Str _tmp261 = til_I64_to_str(til_cloned.cap);
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
        int _status__tmp257 = til_format(&_tmp256, &_err0__tmp257, &_err1__tmp257, &_err2__tmp257, ((til_Str){(til_I64)"src/core/str.til:46:41:", 23}), &_tmp258);
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
        til_Str _tmp267 = ((til_Str){(til_I64)"Str.clone: malloc failed for ", 29});
        til_Str _tmp268 = til_I64_to_str(til_cloned.cap);
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
        int _status__tmp264 = til_format(&_tmp263, &_err0__tmp264, &_err1__tmp264, &_err2__tmp264, ((til_Str){(til_I64)"src/core/str.til:46:41:", 23}), &_tmp265);
        if (_status__tmp264 != 0) {
            if (_status__tmp264 == 3) { *_err1 = _err2__tmp264; return 1; }
        }
        til_Array_delete(&_tmp265);
        *_err1 = til_AllocError_new(_tmp263);
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
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp279;
    if (til_I64_eq(til_Str_len(til_from), 0).data) {
        til_Str _ret__tmp281;
        til_AllocError _err0__tmp281 = {};
        int _status__tmp281 = til_Str_clone(&_ret__tmp281, &_err0__tmp281, til_self);
        if (_status__tmp281 == 1) { *_err1 = _err0__tmp281; return 1; }
        *_ret = _ret__tmp281;
        return 0;
    }
    if (til_I64_eq(til_n, 0).data) {
        til_Str _ret__tmp283;
        til_AllocError _err0__tmp283 = {};
        int _status__tmp283 = til_Str_clone(&_ret__tmp283, &_err0__tmp283, til_self);
        if (_status__tmp283 == 1) { *_err1 = _err0__tmp283; return 1; }
        *_ret = _ret__tmp283;
        return 0;
    }
    til_I64 til_idx = til_Str_find(til_self, til_from);
    if (til_lt(til_idx, 0).data) {
        til_Str _ret__tmp285;
        til_AllocError _err0__tmp285 = {};
        int _status__tmp285 = til_Str_clone(&_ret__tmp285, &_err0__tmp285, til_self);
        if (_status__tmp285 == 1) { *_err1 = _err0__tmp285; return 1; }
        *_ret = _ret__tmp285;
        return 0;
    }
    til_Str _ret__tmp286;
    til_Str til_prefix;
    til_IndexOutOfBoundsError _err0__tmp286 = {};
    til_AllocError _err1__tmp286 = {};
    int _status__tmp286 = til_get_substr(&_ret__tmp286, &_err0__tmp286, &_err1__tmp286, til_self, 0, til_idx);
    if (_status__tmp286 == 2) { *_err1 = _err1__tmp286; return 1; }
    til_prefix = _ret__tmp286;
    til_Str _ret__tmp287;
    til_Str til_suffix;
    til_IndexOutOfBoundsError _err0__tmp287 = {};
    til_AllocError _err1__tmp287 = {};
    int _status__tmp287 = til_get_substr(&_ret__tmp287, &_err0__tmp287, &_err1__tmp287, til_self, til_add(til_idx, til_Str_len(til_from)), til_Str_len(til_self));
    if (_status__tmp287 == 2) { *_err1 = _err1__tmp287; return 1; }
    til_suffix = _ret__tmp287;
    til_Str til_result = til_concat(til_concat(til_prefix, til_to), til_suffix);
    til_Str til_rest;
    if (til_gt(til_n, 1).data) {
        til_Str _ret__tmp289;
        til_Str til_rest;
        til_AllocError _err0__tmp289 = {};
        int _status__tmp289 = til_Str_replacen(&_ret__tmp289, &_err0__tmp289, til_suffix, til_from, til_to, til_sub(til_n, 1));
        if (_status__tmp289 == 1) { *_err1 = _err0__tmp289; return 1; }
        til_rest = _ret__tmp289;
        til_result = til_concat(til_concat(til_prefix, til_to), til_rest);
    }
    *_ret = til_result;
    return 0;
    goto _end_catches__tmp279;
_catch_IndexOutOfBoundsError__tmp279: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp279;
    til_Str _ret__tmp291;
    til_AllocError _err0__tmp291 = {};
    int _status__tmp291 = til_Str_clone(&_ret__tmp291, &_err0__tmp291, til_self);
    if (_status__tmp291 == 1) { *_err1 = _err0__tmp291; return 1; }
    til_result = _ret__tmp291;
    goto _end_catches__tmp279;
    }
_end_catches__tmp279:;
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
        til_Str _tmp297;
        til_I64_OverflowError _err0__tmp298;
        til_IndexOutOfBoundsError _err1__tmp298;
        til_AllocError _err2__tmp298;
        til_Array _tmp299;
        til_AllocError _err_alloc__tmp300;
        til_IndexOutOfBoundsError _err_idx__tmp300;
        til_Str _tmp301 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        int _arr_status__tmp300 = til_Array_new(&_tmp299, &_err_alloc__tmp300, "Str", 1);
        if (_arr_status__tmp300 != 0) {
        }
        _arr_status__tmp300 = til_Array_set(&_err_idx__tmp300, &_tmp299, 0, &_tmp301);
        if (_arr_status__tmp300 != 0) {
        }
        int _status__tmp298 = til_format(&_tmp297, &_err0__tmp298, &_err1__tmp298, &_err2__tmp298, ((til_Str){(til_I64)"src/core/u8.til:56:47:", 22}), &_tmp299);
        if (_status__tmp298 != 0) {
        }
        til_Array_delete(&_tmp299);
        til_Str _tmp302;
        til_I64_OverflowError _err0__tmp303;
        til_IndexOutOfBoundsError _err1__tmp303;
        til_AllocError _err2__tmp303;
        til_Array _tmp304;
        til_AllocError _err_alloc__tmp305;
        til_IndexOutOfBoundsError _err_idx__tmp305;
        til_Str _tmp306 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        int _arr_status__tmp305 = til_Array_new(&_tmp304, &_err_alloc__tmp305, "Str", 1);
        if (_arr_status__tmp305 != 0) {
        }
        _arr_status__tmp305 = til_Array_set(&_err_idx__tmp305, &_tmp304, 0, &_tmp306);
        if (_arr_status__tmp305 != 0) {
        }
        int _status__tmp303 = til_format(&_tmp302, &_err0__tmp303, &_err1__tmp303, &_err2__tmp303, ((til_Str){(til_I64)"src/core/u8.til:56:47:", 22}), &_tmp304);
        if (_status__tmp303 != 0) {
        }
        til_Array_delete(&_tmp304);
        *_err1 = til_U8_OverflowError_new(_tmp302);
        return 1;
    }
    if (til_gt(til_self, til_MAX_U8).data) {
        til_Str _tmp308;
        til_I64_OverflowError _err0__tmp309;
        til_IndexOutOfBoundsError _err1__tmp309;
        til_AllocError _err2__tmp309;
        til_Array _tmp310;
        til_AllocError _err_alloc__tmp311;
        til_IndexOutOfBoundsError _err_idx__tmp311;
        til_Str _tmp312 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp313 = ((til_Str){(til_I64)"255", 3});
        int _arr_status__tmp311 = til_Array_new(&_tmp310, &_err_alloc__tmp311, "Str", 2);
        if (_arr_status__tmp311 != 0) {
        }
        _arr_status__tmp311 = til_Array_set(&_err_idx__tmp311, &_tmp310, 0, &_tmp312);
        if (_arr_status__tmp311 != 0) {
        }
        _arr_status__tmp311 = til_Array_set(&_err_idx__tmp311, &_tmp310, 1, &_tmp313);
        if (_arr_status__tmp311 != 0) {
        }
        int _status__tmp309 = til_format(&_tmp308, &_err0__tmp309, &_err1__tmp309, &_err2__tmp309, ((til_Str){(til_I64)"src/core/u8.til:59:47:", 22}), &_tmp310);
        if (_status__tmp309 != 0) {
        }
        til_Array_delete(&_tmp310);
        til_Str _tmp314;
        til_I64_OverflowError _err0__tmp315;
        til_IndexOutOfBoundsError _err1__tmp315;
        til_AllocError _err2__tmp315;
        til_Array _tmp316;
        til_AllocError _err_alloc__tmp317;
        til_IndexOutOfBoundsError _err_idx__tmp317;
        til_Str _tmp318 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp319 = ((til_Str){(til_I64)"255", 3});
        int _arr_status__tmp317 = til_Array_new(&_tmp316, &_err_alloc__tmp317, "Str", 2);
        if (_arr_status__tmp317 != 0) {
        }
        _arr_status__tmp317 = til_Array_set(&_err_idx__tmp317, &_tmp316, 0, &_tmp318);
        if (_arr_status__tmp317 != 0) {
        }
        _arr_status__tmp317 = til_Array_set(&_err_idx__tmp317, &_tmp316, 1, &_tmp319);
        if (_arr_status__tmp317 != 0) {
        }
        int _status__tmp315 = til_format(&_tmp314, &_err0__tmp315, &_err1__tmp315, &_err2__tmp315, ((til_Str){(til_I64)"src/core/u8.til:59:47:", 22}), &_tmp316);
        if (_status__tmp315 != 0) {
        }
        til_Array_delete(&_tmp316);
        *_err1 = til_U8_OverflowError_new(_tmp314);
        return 1;
    }
    *_ret = til_i64_to_u8(til_self);
    return 0;
}

int main() {
    til_Array _tmp321;
    til_AllocError _err_alloc__tmp322;
    til_IndexOutOfBoundsError _err_idx__tmp322;
    til_Str _tmp323 = ((til_Str){(til_I64)"Hello World!", 12});
    int _arr_status__tmp322 = til_Array_new(&_tmp321, &_err_alloc__tmp322, "Str", 1);
    if (_arr_status__tmp322 != 0) {
    }
    _arr_status__tmp322 = til_Array_set(&_err_idx__tmp322, &_tmp321, 0, &_tmp323);
    if (_arr_status__tmp322 != 0) {
    }
    til_println(&_tmp321);
    til_Array_delete(&_tmp321);
    return 0;
}
