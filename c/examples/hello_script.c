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
    til_I64 _for_i = 0;
    til_Bool til_val;
    while (til_lt(_for_i, til_Array_len((*til_args))).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp4;
        til_val = (til_Bool){.data = 0};
        til_IndexOutOfBoundsError _err0__tmp5 = {};
        int _status__tmp5 = til_Array_get(&_err0__tmp5, (*til_args), _for_i, (til_Dynamic*)&til_val);
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
        _for_i = til_add(_for_i, 1);
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
    til_I64 _for_i = 0;
    til_Bool til_val;
    while (til_lt(_for_i, til_Array_len((*til_args))).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp17;
        til_val = (til_Bool){.data = 0};
        til_IndexOutOfBoundsError _err0__tmp18 = {};
        int _status__tmp18 = til_Array_get(&_err0__tmp18, (*til_args), _for_i, (til_Dynamic*)&til_val);
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
        _for_i = til_add(_for_i, 1);
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
    til_I64 _for_i = 0;
    til_Str til_val;
    while (til_lt(_for_i, til_Array_len((*til_msgs))).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp30;
        til_val = (til_Str){.c_string = 0, .cap = 0};
        til_IndexOutOfBoundsError _err0__tmp31 = {};
        int _status__tmp31 = til_Array_get(&_err0__tmp31, (*til_msgs), _for_i, (til_Dynamic*)&til_val);
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
        _for_i = til_add(_for_i, 1);
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

void til_println(til_Array* til_args) {
    til_I64 _for_i = 0;
    til_Str til_val;
    while (til_lt(_for_i, til_Array_len((*til_args))).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp42;
        til_val = (til_Str){.c_string = 0, .cap = 0};
        til_IndexOutOfBoundsError _err0__tmp43 = {};
        int _status__tmp43 = til_Array_get(&_err0__tmp43, (*til_args), _for_i, (til_Dynamic*)&til_val);
        if (_status__tmp43 == 0) {
        } else if (_status__tmp43 == 1) {
            til_IndexOutOfBoundsError til_err = _err0__tmp43;
            til_Array _tmp45;
            til_AllocError _err_alloc__tmp46;
            til_IndexOutOfBoundsError _err_idx__tmp46;
            til_Str _tmp47 = til_err.msg;
            int _arr_status__tmp46 = til_Array_new(&_tmp45, &_err_alloc__tmp46, "Str", 1);
            if (_arr_status__tmp46 != 0) {
            }
            _arr_status__tmp46 = til_Array_set(&_err_idx__tmp46, &_tmp45, 0, &_tmp47);
            if (_arr_status__tmp46 != 0) {
            }
            til_panic(((til_Str){(til_I64)"src/core/print.til:16:5:", 24}), &_tmp45);
            til_Array_delete(&_tmp45);
        }
        til_single_print(til_val);
        _for_i = til_add(_for_i, 1);
        goto _end_catches__tmp42;
_catch_IndexOutOfBoundsError__tmp42: {
        til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp42;
        til_Array _tmp49;
        til_AllocError _err_alloc__tmp50;
        til_IndexOutOfBoundsError _err_idx__tmp50;
        til_Str _tmp51 = til_err.msg;
        int _arr_status__tmp50 = til_Array_new(&_tmp49, &_err_alloc__tmp50, "Str", 1);
        if (_arr_status__tmp50 != 0) {
        }
        _arr_status__tmp50 = til_Array_set(&_err_idx__tmp50, &_tmp49, 0, &_tmp51);
        if (_arr_status__tmp50 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/print.til:16:5:", 24}), &_tmp49);
        til_Array_delete(&_tmp49);
        goto _end_catches__tmp42;
        }
_end_catches__tmp42:;
    }
    til_single_print(((til_Str){(til_I64)"\n", 1}));
    til_print_flush();
}

int til_get_substr(til_Str* _ret, til_IndexOutOfBoundsError* _err1, til_AllocError* _err2, const til_Str til_s, const til_I64 til_start, const til_I64 til_end) {
    if (til_lt(til_start, 0).data) {
        til_Str _tmp54;
        til_I64_OverflowError _err0__tmp55;
        til_IndexOutOfBoundsError _err1__tmp55;
        til_AllocError _err2__tmp55;
        til_Array _tmp56;
        til_AllocError _err_alloc__tmp57;
        til_IndexOutOfBoundsError _err_idx__tmp57;
        til_Str _tmp58 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp59 = til_I64_to_str(til_start);
        til_Str _tmp60 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp57 = til_Array_new(&_tmp56, &_err_alloc__tmp57, "Str", 3);
        if (_arr_status__tmp57 != 0) {
            *_err2 = _err_alloc__tmp57; return 2;
        }
        _arr_status__tmp57 = til_Array_set(&_err_idx__tmp57, &_tmp56, 0, &_tmp58);
        if (_arr_status__tmp57 != 0) {
            *_err1 = _err_idx__tmp57; return 1;
        }
        _arr_status__tmp57 = til_Array_set(&_err_idx__tmp57, &_tmp56, 1, &_tmp59);
        if (_arr_status__tmp57 != 0) {
            *_err1 = _err_idx__tmp57; return 1;
        }
        _arr_status__tmp57 = til_Array_set(&_err_idx__tmp57, &_tmp56, 2, &_tmp60);
        if (_arr_status__tmp57 != 0) {
            *_err1 = _err_idx__tmp57; return 1;
        }
        int _status__tmp55 = til_format(&_tmp54, &_err0__tmp55, &_err1__tmp55, &_err2__tmp55, ((til_Str){(til_I64)"src/core/str.til:368:48:", 24}), &_tmp56);
        if (_status__tmp55 != 0) {
            if (_status__tmp55 == 2) { *_err1 = _err1__tmp55; return 1; }
            if (_status__tmp55 == 3) { *_err2 = _err2__tmp55; return 2; }
        }
        til_Array_delete(&_tmp56);
        til_Str _tmp61;
        til_I64_OverflowError _err0__tmp62;
        til_IndexOutOfBoundsError _err1__tmp62;
        til_AllocError _err2__tmp62;
        til_Array _tmp63;
        til_AllocError _err_alloc__tmp64;
        til_IndexOutOfBoundsError _err_idx__tmp64;
        til_Str _tmp65 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp66 = til_I64_to_str(til_start);
        til_Str _tmp67 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp64 = til_Array_new(&_tmp63, &_err_alloc__tmp64, "Str", 3);
        if (_arr_status__tmp64 != 0) {
            *_err2 = _err_alloc__tmp64; return 2;
        }
        _arr_status__tmp64 = til_Array_set(&_err_idx__tmp64, &_tmp63, 0, &_tmp65);
        if (_arr_status__tmp64 != 0) {
            *_err1 = _err_idx__tmp64; return 1;
        }
        _arr_status__tmp64 = til_Array_set(&_err_idx__tmp64, &_tmp63, 1, &_tmp66);
        if (_arr_status__tmp64 != 0) {
            *_err1 = _err_idx__tmp64; return 1;
        }
        _arr_status__tmp64 = til_Array_set(&_err_idx__tmp64, &_tmp63, 2, &_tmp67);
        if (_arr_status__tmp64 != 0) {
            *_err1 = _err_idx__tmp64; return 1;
        }
        int _status__tmp62 = til_format(&_tmp61, &_err0__tmp62, &_err1__tmp62, &_err2__tmp62, ((til_Str){(til_I64)"src/core/str.til:368:48:", 24}), &_tmp63);
        if (_status__tmp62 != 0) {
            if (_status__tmp62 == 2) { *_err1 = _err1__tmp62; return 1; }
            if (_status__tmp62 == 3) { *_err2 = _err2__tmp62; return 2; }
        }
        til_Array_delete(&_tmp63);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp61);
        return 1;
    }
    if (til_lt(til_end, 0).data) {
        til_Str _tmp69;
        til_I64_OverflowError _err0__tmp70;
        til_IndexOutOfBoundsError _err1__tmp70;
        til_AllocError _err2__tmp70;
        til_Array _tmp71;
        til_AllocError _err_alloc__tmp72;
        til_IndexOutOfBoundsError _err_idx__tmp72;
        til_Str _tmp73 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp74 = til_I64_to_str(til_end);
        til_Str _tmp75 = ((til_Str){(til_I64)" cannot be negative", 19});
        int _arr_status__tmp72 = til_Array_new(&_tmp71, &_err_alloc__tmp72, "Str", 3);
        if (_arr_status__tmp72 != 0) {
            *_err2 = _err_alloc__tmp72; return 2;
        }
        _arr_status__tmp72 = til_Array_set(&_err_idx__tmp72, &_tmp71, 0, &_tmp73);
        if (_arr_status__tmp72 != 0) {
            *_err1 = _err_idx__tmp72; return 1;
        }
        _arr_status__tmp72 = til_Array_set(&_err_idx__tmp72, &_tmp71, 1, &_tmp74);
        if (_arr_status__tmp72 != 0) {
            *_err1 = _err_idx__tmp72; return 1;
        }
        _arr_status__tmp72 = til_Array_set(&_err_idx__tmp72, &_tmp71, 2, &_tmp75);
        if (_arr_status__tmp72 != 0) {
            *_err1 = _err_idx__tmp72; return 1;
        }
        int _status__tmp70 = til_format(&_tmp69, &_err0__tmp70, &_err1__tmp70, &_err2__tmp70, ((til_Str){(til_I64)"src/core/str.til:371:48:", 24}), &_tmp71);
        if (_status__tmp70 != 0) {
            if (_status__tmp70 == 2) { *_err1 = _err1__tmp70; return 1; }
            if (_status__tmp70 == 3) { *_err2 = _err2__tmp70; return 2; }
        }
        til_Array_delete(&_tmp71);
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
        int _status__tmp77 = til_format(&_tmp76, &_err0__tmp77, &_err1__tmp77, &_err2__tmp77, ((til_Str){(til_I64)"src/core/str.til:371:48:", 24}), &_tmp78);
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
        int _status__tmp85 = til_format(&_tmp84, &_err0__tmp85, &_err1__tmp85, &_err2__tmp85, ((til_Str){(til_I64)"src/core/str.til:374:48:", 24}), &_tmp86);
        if (_status__tmp85 != 0) {
            if (_status__tmp85 == 2) { *_err1 = _err1__tmp85; return 1; }
            if (_status__tmp85 == 3) { *_err2 = _err2__tmp85; return 2; }
        }
        til_Array_delete(&_tmp86);
        til_Str _tmp92;
        til_I64_OverflowError _err0__tmp93;
        til_IndexOutOfBoundsError _err1__tmp93;
        til_AllocError _err2__tmp93;
        til_Array _tmp94;
        til_AllocError _err_alloc__tmp95;
        til_IndexOutOfBoundsError _err_idx__tmp95;
        til_Str _tmp96 = ((til_Str){(til_I64)"get_substr: start index ", 24});
        til_Str _tmp97 = til_I64_to_str(til_start);
        til_Str _tmp98 = ((til_Str){(til_I64)" is greater than end index ", 27});
        til_Str _tmp99 = til_I64_to_str(til_end);
        int _arr_status__tmp95 = til_Array_new(&_tmp94, &_err_alloc__tmp95, "Str", 4);
        if (_arr_status__tmp95 != 0) {
            *_err2 = _err_alloc__tmp95; return 2;
        }
        _arr_status__tmp95 = til_Array_set(&_err_idx__tmp95, &_tmp94, 0, &_tmp96);
        if (_arr_status__tmp95 != 0) {
            *_err1 = _err_idx__tmp95; return 1;
        }
        _arr_status__tmp95 = til_Array_set(&_err_idx__tmp95, &_tmp94, 1, &_tmp97);
        if (_arr_status__tmp95 != 0) {
            *_err1 = _err_idx__tmp95; return 1;
        }
        _arr_status__tmp95 = til_Array_set(&_err_idx__tmp95, &_tmp94, 2, &_tmp98);
        if (_arr_status__tmp95 != 0) {
            *_err1 = _err_idx__tmp95; return 1;
        }
        _arr_status__tmp95 = til_Array_set(&_err_idx__tmp95, &_tmp94, 3, &_tmp99);
        if (_arr_status__tmp95 != 0) {
            *_err1 = _err_idx__tmp95; return 1;
        }
        int _status__tmp93 = til_format(&_tmp92, &_err0__tmp93, &_err1__tmp93, &_err2__tmp93, ((til_Str){(til_I64)"src/core/str.til:374:48:", 24}), &_tmp94);
        if (_status__tmp93 != 0) {
            if (_status__tmp93 == 2) { *_err1 = _err1__tmp93; return 1; }
            if (_status__tmp93 == 3) { *_err2 = _err2__tmp93; return 2; }
        }
        til_Array_delete(&_tmp94);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp92);
        return 1;
    }
    if (til_gt(til_end, til_Str_len(til_s)).data) {
        til_Str _tmp101;
        til_I64_OverflowError _err0__tmp102;
        til_IndexOutOfBoundsError _err1__tmp102;
        til_AllocError _err2__tmp102;
        til_Array _tmp103;
        til_AllocError _err_alloc__tmp104;
        til_IndexOutOfBoundsError _err_idx__tmp104;
        til_Str _tmp105 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp106 = til_I64_to_str(til_end);
        til_Str _tmp107 = ((til_Str){(til_I64)" is greater than string length ", 31});
        til_Str _tmp108 = til_I64_to_str(til_Str_len(til_s));
        int _arr_status__tmp104 = til_Array_new(&_tmp103, &_err_alloc__tmp104, "Str", 4);
        if (_arr_status__tmp104 != 0) {
            *_err2 = _err_alloc__tmp104; return 2;
        }
        _arr_status__tmp104 = til_Array_set(&_err_idx__tmp104, &_tmp103, 0, &_tmp105);
        if (_arr_status__tmp104 != 0) {
            *_err1 = _err_idx__tmp104; return 1;
        }
        _arr_status__tmp104 = til_Array_set(&_err_idx__tmp104, &_tmp103, 1, &_tmp106);
        if (_arr_status__tmp104 != 0) {
            *_err1 = _err_idx__tmp104; return 1;
        }
        _arr_status__tmp104 = til_Array_set(&_err_idx__tmp104, &_tmp103, 2, &_tmp107);
        if (_arr_status__tmp104 != 0) {
            *_err1 = _err_idx__tmp104; return 1;
        }
        _arr_status__tmp104 = til_Array_set(&_err_idx__tmp104, &_tmp103, 3, &_tmp108);
        if (_arr_status__tmp104 != 0) {
            *_err1 = _err_idx__tmp104; return 1;
        }
        int _status__tmp102 = til_format(&_tmp101, &_err0__tmp102, &_err1__tmp102, &_err2__tmp102, ((til_Str){(til_I64)"src/core/str.til:377:48:", 24}), &_tmp103);
        if (_status__tmp102 != 0) {
            if (_status__tmp102 == 2) { *_err1 = _err1__tmp102; return 1; }
            if (_status__tmp102 == 3) { *_err2 = _err2__tmp102; return 2; }
        }
        til_Array_delete(&_tmp103);
        til_Str _tmp109;
        til_I64_OverflowError _err0__tmp110;
        til_IndexOutOfBoundsError _err1__tmp110;
        til_AllocError _err2__tmp110;
        til_Array _tmp111;
        til_AllocError _err_alloc__tmp112;
        til_IndexOutOfBoundsError _err_idx__tmp112;
        til_Str _tmp113 = ((til_Str){(til_I64)"get_substr: end index ", 22});
        til_Str _tmp114 = til_I64_to_str(til_end);
        til_Str _tmp115 = ((til_Str){(til_I64)" is greater than string length ", 31});
        til_Str _tmp116 = til_I64_to_str(til_Str_len(til_s));
        int _arr_status__tmp112 = til_Array_new(&_tmp111, &_err_alloc__tmp112, "Str", 4);
        if (_arr_status__tmp112 != 0) {
            *_err2 = _err_alloc__tmp112; return 2;
        }
        _arr_status__tmp112 = til_Array_set(&_err_idx__tmp112, &_tmp111, 0, &_tmp113);
        if (_arr_status__tmp112 != 0) {
            *_err1 = _err_idx__tmp112; return 1;
        }
        _arr_status__tmp112 = til_Array_set(&_err_idx__tmp112, &_tmp111, 1, &_tmp114);
        if (_arr_status__tmp112 != 0) {
            *_err1 = _err_idx__tmp112; return 1;
        }
        _arr_status__tmp112 = til_Array_set(&_err_idx__tmp112, &_tmp111, 2, &_tmp115);
        if (_arr_status__tmp112 != 0) {
            *_err1 = _err_idx__tmp112; return 1;
        }
        _arr_status__tmp112 = til_Array_set(&_err_idx__tmp112, &_tmp111, 3, &_tmp116);
        if (_arr_status__tmp112 != 0) {
            *_err1 = _err_idx__tmp112; return 1;
        }
        int _status__tmp110 = til_format(&_tmp109, &_err0__tmp110, &_err1__tmp110, &_err2__tmp110, ((til_Str){(til_I64)"src/core/str.til:377:48:", 24}), &_tmp111);
        if (_status__tmp110 != 0) {
            if (_status__tmp110 == 2) { *_err1 = _err1__tmp110; return 1; }
            if (_status__tmp110 == 3) { *_err2 = _err2__tmp110; return 2; }
        }
        til_Array_delete(&_tmp111);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp109);
        return 1;
    }
    if (til_I64_eq(til_start, til_end).data) {
        til_Str _tmp118;
        til_I64_OverflowError _err0__tmp119;
        til_IndexOutOfBoundsError _err1__tmp119;
        til_AllocError _err2__tmp119;
        til_Array _tmp120;
        til_AllocError _err_alloc__tmp121;
        til_IndexOutOfBoundsError _err_idx__tmp121;
        til_Str _tmp122 = ((til_Str){(til_I64)"get_substr: start and end are the same (", 40});
        til_Str _tmp123 = til_I64_to_str(til_start);
        til_Str _tmp124 = ((til_Str){(til_I64)"), no substring", 15});
        int _arr_status__tmp121 = til_Array_new(&_tmp120, &_err_alloc__tmp121, "Str", 3);
        if (_arr_status__tmp121 != 0) {
            *_err2 = _err_alloc__tmp121; return 2;
        }
        _arr_status__tmp121 = til_Array_set(&_err_idx__tmp121, &_tmp120, 0, &_tmp122);
        if (_arr_status__tmp121 != 0) {
            *_err1 = _err_idx__tmp121; return 1;
        }
        _arr_status__tmp121 = til_Array_set(&_err_idx__tmp121, &_tmp120, 1, &_tmp123);
        if (_arr_status__tmp121 != 0) {
            *_err1 = _err_idx__tmp121; return 1;
        }
        _arr_status__tmp121 = til_Array_set(&_err_idx__tmp121, &_tmp120, 2, &_tmp124);
        if (_arr_status__tmp121 != 0) {
            *_err1 = _err_idx__tmp121; return 1;
        }
        int _status__tmp119 = til_format(&_tmp118, &_err0__tmp119, &_err1__tmp119, &_err2__tmp119, ((til_Str){(til_I64)"src/core/str.til:380:48:", 24}), &_tmp120);
        if (_status__tmp119 != 0) {
            if (_status__tmp119 == 2) { *_err1 = _err1__tmp119; return 1; }
            if (_status__tmp119 == 3) { *_err2 = _err2__tmp119; return 2; }
        }
        til_Array_delete(&_tmp120);
        til_Str _tmp125;
        til_I64_OverflowError _err0__tmp126;
        til_IndexOutOfBoundsError _err1__tmp126;
        til_AllocError _err2__tmp126;
        til_Array _tmp127;
        til_AllocError _err_alloc__tmp128;
        til_IndexOutOfBoundsError _err_idx__tmp128;
        til_Str _tmp129 = ((til_Str){(til_I64)"get_substr: start and end are the same (", 40});
        til_Str _tmp130 = til_I64_to_str(til_start);
        til_Str _tmp131 = ((til_Str){(til_I64)"), no substring", 15});
        int _arr_status__tmp128 = til_Array_new(&_tmp127, &_err_alloc__tmp128, "Str", 3);
        if (_arr_status__tmp128 != 0) {
            *_err2 = _err_alloc__tmp128; return 2;
        }
        _arr_status__tmp128 = til_Array_set(&_err_idx__tmp128, &_tmp127, 0, &_tmp129);
        if (_arr_status__tmp128 != 0) {
            *_err1 = _err_idx__tmp128; return 1;
        }
        _arr_status__tmp128 = til_Array_set(&_err_idx__tmp128, &_tmp127, 1, &_tmp130);
        if (_arr_status__tmp128 != 0) {
            *_err1 = _err_idx__tmp128; return 1;
        }
        _arr_status__tmp128 = til_Array_set(&_err_idx__tmp128, &_tmp127, 2, &_tmp131);
        if (_arr_status__tmp128 != 0) {
            *_err1 = _err_idx__tmp128; return 1;
        }
        int _status__tmp126 = til_format(&_tmp125, &_err0__tmp126, &_err1__tmp126, &_err2__tmp126, ((til_Str){(til_I64)"src/core/str.til:380:48:", 24}), &_tmp127);
        if (_status__tmp126 != 0) {
            if (_status__tmp126 == 2) { *_err1 = _err1__tmp126; return 1; }
            if (_status__tmp126 == 3) { *_err2 = _err2__tmp126; return 2; }
        }
        til_Array_delete(&_tmp127);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp125);
        return 1;
    }
    til_Str til_substr = {.c_string = 0, .cap = 0};
    til_substr.cap = til_sub(til_end, til_start);
    til_I64 _ret__tmp132;
    til_AllocError _err0__tmp132 = {};
    int _status__tmp132 = til_malloc(&_ret__tmp132, &_err0__tmp132, til_substr.cap);
    if (_status__tmp132 == 1) { *_err2 = _err0__tmp132; return 2; }
    til_substr.c_string = _ret__tmp132;
    if (til_I64_eq(til_NULL, til_substr.c_string).data) {
        til_Str _tmp134;
        til_I64_OverflowError _err0__tmp135;
        til_IndexOutOfBoundsError _err1__tmp135;
        til_AllocError _err2__tmp135;
        til_Array _tmp136;
        til_AllocError _err_alloc__tmp137;
        til_IndexOutOfBoundsError _err_idx__tmp137;
        til_Str _tmp138 = ((til_Str){(til_I64)"Str.get_substr: failed to allocate ", 35});
        til_Str _tmp139 = til_I64_to_str(til_substr.cap);
        til_Str _tmp140 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp137 = til_Array_new(&_tmp136, &_err_alloc__tmp137, "Str", 3);
        if (_arr_status__tmp137 != 0) {
            *_err2 = _err_alloc__tmp137; return 2;
        }
        _arr_status__tmp137 = til_Array_set(&_err_idx__tmp137, &_tmp136, 0, &_tmp138);
        if (_arr_status__tmp137 != 0) {
            *_err1 = _err_idx__tmp137; return 1;
        }
        _arr_status__tmp137 = til_Array_set(&_err_idx__tmp137, &_tmp136, 1, &_tmp139);
        if (_arr_status__tmp137 != 0) {
            *_err1 = _err_idx__tmp137; return 1;
        }
        _arr_status__tmp137 = til_Array_set(&_err_idx__tmp137, &_tmp136, 2, &_tmp140);
        if (_arr_status__tmp137 != 0) {
            *_err1 = _err_idx__tmp137; return 1;
        }
        int _status__tmp135 = til_format(&_tmp134, &_err0__tmp135, &_err1__tmp135, &_err2__tmp135, ((til_Str){(til_I64)"src/core/str.til:387:37:", 24}), &_tmp136);
        if (_status__tmp135 != 0) {
            if (_status__tmp135 == 2) { *_err1 = _err1__tmp135; return 1; }
            if (_status__tmp135 == 3) { *_err2 = _err2__tmp135; return 2; }
        }
        til_Array_delete(&_tmp136);
        til_Str _tmp141;
        til_I64_OverflowError _err0__tmp142;
        til_IndexOutOfBoundsError _err1__tmp142;
        til_AllocError _err2__tmp142;
        til_Array _tmp143;
        til_AllocError _err_alloc__tmp144;
        til_IndexOutOfBoundsError _err_idx__tmp144;
        til_Str _tmp145 = ((til_Str){(til_I64)"Str.get_substr: failed to allocate ", 35});
        til_Str _tmp146 = til_I64_to_str(til_substr.cap);
        til_Str _tmp147 = ((til_Str){(til_I64)" bytes", 6});
        int _arr_status__tmp144 = til_Array_new(&_tmp143, &_err_alloc__tmp144, "Str", 3);
        if (_arr_status__tmp144 != 0) {
            *_err2 = _err_alloc__tmp144; return 2;
        }
        _arr_status__tmp144 = til_Array_set(&_err_idx__tmp144, &_tmp143, 0, &_tmp145);
        if (_arr_status__tmp144 != 0) {
            *_err1 = _err_idx__tmp144; return 1;
        }
        _arr_status__tmp144 = til_Array_set(&_err_idx__tmp144, &_tmp143, 1, &_tmp146);
        if (_arr_status__tmp144 != 0) {
            *_err1 = _err_idx__tmp144; return 1;
        }
        _arr_status__tmp144 = til_Array_set(&_err_idx__tmp144, &_tmp143, 2, &_tmp147);
        if (_arr_status__tmp144 != 0) {
            *_err1 = _err_idx__tmp144; return 1;
        }
        int _status__tmp142 = til_format(&_tmp141, &_err0__tmp142, &_err1__tmp142, &_err2__tmp142, ((til_Str){(til_I64)"src/core/str.til:387:37:", 24}), &_tmp143);
        if (_status__tmp142 != 0) {
            if (_status__tmp142 == 2) { *_err1 = _err1__tmp142; return 1; }
            if (_status__tmp142 == 3) { *_err2 = _err2__tmp142; return 2; }
        }
        til_Array_delete(&_tmp143);
        *_err2 = til_AllocError_new(_tmp141);
        return 2;
    }
    til_memcpy(til_substr.c_string, til_add(til_s.c_string, til_start), til_substr.cap);
    *_ret = til_substr;
    return 0;
}

til_Str til_concat(const til_Str til_a, const til_Str til_b) {
    til_AllocError _thrown_AllocError__tmp148;
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_add(til_a.cap, til_b.cap);
    if (til_lt(til_result.cap, til_a.cap).data) {
        til_Array _tmp150;
        til_AllocError _err_alloc__tmp151;
        til_IndexOutOfBoundsError _err_idx__tmp151;
        til_Str _tmp152 = ((til_Str){(til_I64)"concat: integer overflow", 24});
        int _arr_status__tmp151 = til_Array_new(&_tmp150, &_err_alloc__tmp151, "Str", 1);
        if (_arr_status__tmp151 != 0) {
        }
        _arr_status__tmp151 = til_Array_set(&_err_idx__tmp151, &_tmp150, 0, &_tmp152);
        if (_arr_status__tmp151 != 0) {
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:447:15:", 24}), &_tmp150);
        til_Array_delete(&_tmp150);
    }
    til_I64 _ret__tmp153;
    til_AllocError _err0__tmp153 = {};
    int _status__tmp153 = til_malloc(&_ret__tmp153, &_err0__tmp153, til_result.cap);
    if (_status__tmp153 == 1) { _thrown_AllocError__tmp148 = _err0__tmp153; goto _catch_AllocError__tmp148; }
    til_result.c_string = _ret__tmp153;
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
        til_panic(((til_Str){(til_I64)"src/core/str.til:452:15:", 24}), &_tmp155);
        til_Array_delete(&_tmp155);
    }
    til_memcpy(til_result.c_string, til_a.c_string, til_a.cap);
    til_memcpy(til_add(til_result.c_string, til_a.cap), til_b.c_string, til_b.cap);
    return til_result;
    goto _end_catches__tmp148;
_catch_AllocError__tmp148: {
    til_AllocError til_err = _thrown_AllocError__tmp148;
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
    til_panic(((til_Str){(til_I64)"src/core/str.til:459:15:", 24}), &_tmp159);
    til_Array_delete(&_tmp159);
    goto _end_catches__tmp148;
    }
_end_catches__tmp148:;
}

int til_format(til_Str* _ret, til_I64_OverflowError* _err1, til_IndexOutOfBoundsError* _err2, til_AllocError* _err3, const til_Str til_prefix, til_Array* til_args) {
    til_Str til_result = {.c_string = 0, .cap = 0};
    til_result.cap = til_prefix.cap;
    til_I64 til_i = 0;
    til_Str til_arg;
    while (til_lt(til_i, til_Array_len((*til_args))).data) {
        til_arg = ((til_Str){(til_I64)"", 0});
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
            int _status__tmp168 = til_format(&_tmp167, &_err0__tmp168, &_err1__tmp168, &_err2__tmp168, ((til_Str){(til_I64)"src/core/str.til:475:48:", 24}), &_tmp169);
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
            int _status__tmp174 = til_format(&_tmp173, &_err0__tmp174, &_err1__tmp174, &_err2__tmp174, ((til_Str){(til_I64)"src/core/str.til:475:48:", 24}), &_tmp175);
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
        int _status__tmp182 = til_format(&_tmp181, &_err0__tmp182, &_err1__tmp182, &_err2__tmp182, ((til_Str){(til_I64)"src/core/str.til:481:37:", 24}), &_tmp183);
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
        int _status__tmp188 = til_format(&_tmp187, &_err0__tmp188, &_err1__tmp188, &_err2__tmp188, ((til_Str){(til_I64)"src/core/str.til:481:37:", 24}), &_tmp189);
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
    til_I64 _for_i = 0;
    til_Str til_s;
    while (til_lt(_for_i, til_Array_len((*til_args))).data) {
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp194;
        til_s = (til_Str){.c_string = 0, .cap = 0};
        til_IndexOutOfBoundsError _err0__tmp195 = {};
        int _status__tmp195 = til_Array_get(&_err0__tmp195, (*til_args), _for_i, (til_Dynamic*)&til_s);
        if (_status__tmp195 == 0) {
        } else if (_status__tmp195 == 1) {
            til_IndexOutOfBoundsError til_err = _err0__tmp195;
            til_Array _tmp197;
            til_AllocError _err_alloc__tmp198;
            til_IndexOutOfBoundsError _err_idx__tmp198;
            til_Str _tmp199 = til_err.msg;
            int _arr_status__tmp198 = til_Array_new(&_tmp197, &_err_alloc__tmp198, "Str", 1);
            if (_arr_status__tmp198 != 0) {
                *_err3 = _err_alloc__tmp198; return 3;
            }
            _arr_status__tmp198 = til_Array_set(&_err_idx__tmp198, &_tmp197, 0, &_tmp199);
            if (_arr_status__tmp198 != 0) {
                *_err2 = _err_idx__tmp198; return 2;
            }
            til_panic(((til_Str){(til_I64)"src/core/str.til:488:5:", 23}), &_tmp197);
            til_Array_delete(&_tmp197);
        }
        til_memcpy(til_add(til_result.c_string, til_offset), til_s.c_string, til_s.cap);
        til_offset = til_add(til_offset, til_s.cap);
        _for_i = til_add(_for_i, 1);
        goto _end_catches__tmp194;
_catch_IndexOutOfBoundsError__tmp194: {
        til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp194;
        til_Array _tmp201;
        til_AllocError _err_alloc__tmp202;
        til_IndexOutOfBoundsError _err_idx__tmp202;
        til_Str _tmp203 = til_err.msg;
        int _arr_status__tmp202 = til_Array_new(&_tmp201, &_err_alloc__tmp202, "Str", 1);
        if (_arr_status__tmp202 != 0) {
            *_err3 = _err_alloc__tmp202; return 3;
        }
        _arr_status__tmp202 = til_Array_set(&_err_idx__tmp202, &_tmp201, 0, &_tmp203);
        if (_arr_status__tmp202 != 0) {
            *_err2 = _err_idx__tmp202; return 2;
        }
        til_panic(((til_Str){(til_I64)"src/core/str.til:488:5:", 23}), &_tmp201);
        til_Array_delete(&_tmp201);
        goto _end_catches__tmp194;
        }
_end_catches__tmp194:;
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
    til_I64 _ret__tmp208;
    til_AllocError _err0__tmp208 = {};
    int _status__tmp208 = til_malloc(&_ret__tmp208, &_err0__tmp208, til_size_bytes);
    if (_status__tmp208 == 1) { *_err1 = _err0__tmp208; return 1; }
    til_arr.ptr = _ret__tmp208;
    til_U8 _tmp209;
    til_U8_OverflowError _err0__tmp210;
    int _status__tmp210 = til_U8_from_i64(&_tmp209, &_err0__tmp210, 0);
    if (_status__tmp210 != 0) {
    }
    til_memset(til_arr.ptr, _tmp209, til_size_bytes);
    til_arr._len = til_capacity;
    *_ret = til_arr;
    return 0;
}

int til_Array_get(til_IndexOutOfBoundsError* _err1, const til_Array til_self, const til_I64 til_index, til_Dynamic* til_T) {
    if (til_I64_gteq(til_index, til_self._len).data) {
        til_Str _tmp213;
        til_I64_OverflowError _err0__tmp214;
        til_IndexOutOfBoundsError _err1__tmp214;
        til_AllocError _err2__tmp214;
        til_Array _tmp215;
        til_AllocError _err_alloc__tmp216;
        til_IndexOutOfBoundsError _err_idx__tmp216;
        til_Str _tmp217 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        int _arr_status__tmp216 = til_Array_new(&_tmp215, &_err_alloc__tmp216, "Str", 1);
        if (_arr_status__tmp216 != 0) {
        }
        _arr_status__tmp216 = til_Array_set(&_err_idx__tmp216, &_tmp215, 0, &_tmp217);
        if (_arr_status__tmp216 != 0) {
            *_err1 = _err_idx__tmp216; return 1;
        }
        int _status__tmp214 = til_format(&_tmp213, &_err0__tmp214, &_err1__tmp214, &_err2__tmp214, ((til_Str){(til_I64)"src/core/array.til:41:52:", 25}), &_tmp215);
        if (_status__tmp214 != 0) {
            if (_status__tmp214 == 2) { *_err1 = _err1__tmp214; return 1; }
        }
        til_Array_delete(&_tmp215);
        til_Str _tmp218;
        til_I64_OverflowError _err0__tmp219;
        til_IndexOutOfBoundsError _err1__tmp219;
        til_AllocError _err2__tmp219;
        til_Array _tmp220;
        til_AllocError _err_alloc__tmp221;
        til_IndexOutOfBoundsError _err_idx__tmp221;
        til_Str _tmp222 = ((til_Str){(til_I64)"Array.get: index out of bounds", 30});
        int _arr_status__tmp221 = til_Array_new(&_tmp220, &_err_alloc__tmp221, "Str", 1);
        if (_arr_status__tmp221 != 0) {
        }
        _arr_status__tmp221 = til_Array_set(&_err_idx__tmp221, &_tmp220, 0, &_tmp222);
        if (_arr_status__tmp221 != 0) {
            *_err1 = _err_idx__tmp221; return 1;
        }
        int _status__tmp219 = til_format(&_tmp218, &_err0__tmp219, &_err1__tmp219, &_err2__tmp219, ((til_Str){(til_I64)"src/core/array.til:41:52:", 25}), &_tmp220);
        if (_status__tmp219 != 0) {
            if (_status__tmp219 == 2) { *_err1 = _err1__tmp219; return 1; }
        }
        til_Array_delete(&_tmp220);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp218);
        return 1;
    }
    const til_I64 til_src = til_add(til_self.ptr, til_mul(til_index, til_self.type_size));
    til_I64 til_dest = (til_I64)til_T;
    til_memcpy(til_dest, til_src, til_self.type_size);
    return 0;
}

int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_self, const til_I64 til_index, const til_Dynamic til_value) {
    if (til_I64_gteq(til_index, til_self->_len).data) {
        til_Str _tmp225;
        til_I64_OverflowError _err0__tmp226;
        til_IndexOutOfBoundsError _err1__tmp226;
        til_AllocError _err2__tmp226;
        til_Array _tmp227;
        til_AllocError _err_alloc__tmp228;
        til_IndexOutOfBoundsError _err_idx__tmp228;
        til_Str _tmp229 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        int _arr_status__tmp228 = til_Array_new(&_tmp227, &_err_alloc__tmp228, "Str", 1);
        if (_arr_status__tmp228 != 0) {
        }
        _arr_status__tmp228 = til_Array_set(&_err_idx__tmp228, &_tmp227, 0, &_tmp229);
        if (_arr_status__tmp228 != 0) {
            *_err1 = _err_idx__tmp228; return 1;
        }
        int _status__tmp226 = til_format(&_tmp225, &_err0__tmp226, &_err1__tmp226, &_err2__tmp226, ((til_Str){(til_I64)"src/core/array.til:56:52:", 25}), &_tmp227);
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
        til_Str _tmp234 = ((til_Str){(til_I64)"Array.set: index out of bounds", 30});
        int _arr_status__tmp233 = til_Array_new(&_tmp232, &_err_alloc__tmp233, "Str", 1);
        if (_arr_status__tmp233 != 0) {
        }
        _arr_status__tmp233 = til_Array_set(&_err_idx__tmp233, &_tmp232, 0, &_tmp234);
        if (_arr_status__tmp233 != 0) {
            *_err1 = _err_idx__tmp233; return 1;
        }
        int _status__tmp231 = til_format(&_tmp230, &_err0__tmp231, &_err1__tmp231, &_err2__tmp231, ((til_Str){(til_I64)"src/core/array.til:56:52:", 25}), &_tmp232);
        if (_status__tmp231 != 0) {
            if (_status__tmp231 == 2) { *_err1 = _err1__tmp231; return 1; }
        }
        til_Array_delete(&_tmp232);
        *_err1 = til_IndexOutOfBoundsError_new(_tmp230);
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
    til_I64 til_new_cap;
    til_I64 til_new_ptr;
    if (til_I64_eq(til_self->_len, til_self->cap).data) {
        til_new_cap = til_mul(til_self->cap, 2);
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
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp306;
    if (til_I64_eq(til_Str_len(til_from), 0).data) {
        til_Str _ret__tmp308;
        til_AllocError _err0__tmp308 = {};
        int _status__tmp308 = til_Str_clone(&_ret__tmp308, &_err0__tmp308, til_self);
        if (_status__tmp308 == 1) { *_err1 = _err0__tmp308; return 1; }
        *_ret = _ret__tmp308;
        return 0;
    }
    if (til_I64_eq(til_n, 0).data) {
        til_Str _ret__tmp310;
        til_AllocError _err0__tmp310 = {};
        int _status__tmp310 = til_Str_clone(&_ret__tmp310, &_err0__tmp310, til_self);
        if (_status__tmp310 == 1) { *_err1 = _err0__tmp310; return 1; }
        *_ret = _ret__tmp310;
        return 0;
    }
    til_I64 til_idx = til_Str_find(til_self, til_from);
    if (til_lt(til_idx, 0).data) {
        til_Str _ret__tmp312;
        til_AllocError _err0__tmp312 = {};
        int _status__tmp312 = til_Str_clone(&_ret__tmp312, &_err0__tmp312, til_self);
        if (_status__tmp312 == 1) { *_err1 = _err0__tmp312; return 1; }
        *_ret = _ret__tmp312;
        return 0;
    }
    til_Str _ret__tmp313;
    til_Str til_prefix;
    til_IndexOutOfBoundsError _err0__tmp313 = {};
    til_AllocError _err1__tmp313 = {};
    int _status__tmp313 = til_get_substr(&_ret__tmp313, &_err0__tmp313, &_err1__tmp313, til_self, 0, til_idx);
    if (_status__tmp313 == 2) { *_err1 = _err1__tmp313; return 1; }
    til_prefix = _ret__tmp313;
    til_Str _ret__tmp314;
    til_Str til_suffix;
    til_IndexOutOfBoundsError _err0__tmp314 = {};
    til_AllocError _err1__tmp314 = {};
    int _status__tmp314 = til_get_substr(&_ret__tmp314, &_err0__tmp314, &_err1__tmp314, til_self, til_add(til_idx, til_Str_len(til_from)), til_Str_len(til_self));
    if (_status__tmp314 == 2) { *_err1 = _err1__tmp314; return 1; }
    til_suffix = _ret__tmp314;
    til_Str til_result = til_concat(til_concat(til_prefix, til_to), til_suffix);
    til_Str til_rest;
    if (til_gt(til_n, 1).data) {
        til_Str _ret__tmp316;
        til_Str til_rest;
        til_AllocError _err0__tmp316 = {};
        int _status__tmp316 = til_Str_replacen(&_ret__tmp316, &_err0__tmp316, til_suffix, til_from, til_to, til_sub(til_n, 1));
        if (_status__tmp316 == 1) { *_err1 = _err0__tmp316; return 1; }
        til_rest = _ret__tmp316;
        til_result = til_concat(til_concat(til_prefix, til_to), til_rest);
    }
    *_ret = til_result;
    return 0;
    goto _end_catches__tmp306;
_catch_IndexOutOfBoundsError__tmp306: {
    til_IndexOutOfBoundsError til_err = _thrown_IndexOutOfBoundsError__tmp306;
    til_Str _ret__tmp318;
    til_AllocError _err0__tmp318 = {};
    int _status__tmp318 = til_Str_clone(&_ret__tmp318, &_err0__tmp318, til_self);
    if (_status__tmp318 == 1) { *_err1 = _err0__tmp318; return 1; }
    til_result = _ret__tmp318;
    goto _end_catches__tmp306;
    }
_end_catches__tmp306:;
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
        til_Str _tmp324;
        til_I64_OverflowError _err0__tmp325;
        til_IndexOutOfBoundsError _err1__tmp325;
        til_AllocError _err2__tmp325;
        til_Array _tmp326;
        til_AllocError _err_alloc__tmp327;
        til_IndexOutOfBoundsError _err_idx__tmp327;
        til_Str _tmp328 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        int _arr_status__tmp327 = til_Array_new(&_tmp326, &_err_alloc__tmp327, "Str", 1);
        if (_arr_status__tmp327 != 0) {
        }
        _arr_status__tmp327 = til_Array_set(&_err_idx__tmp327, &_tmp326, 0, &_tmp328);
        if (_arr_status__tmp327 != 0) {
        }
        int _status__tmp325 = til_format(&_tmp324, &_err0__tmp325, &_err1__tmp325, &_err2__tmp325, ((til_Str){(til_I64)"src/core/u8.til:56:47:", 22}), &_tmp326);
        if (_status__tmp325 != 0) {
        }
        til_Array_delete(&_tmp326);
        til_Str _tmp329;
        til_I64_OverflowError _err0__tmp330;
        til_IndexOutOfBoundsError _err1__tmp330;
        til_AllocError _err2__tmp330;
        til_Array _tmp331;
        til_AllocError _err_alloc__tmp332;
        til_IndexOutOfBoundsError _err_idx__tmp332;
        til_Str _tmp333 = ((til_Str){(til_I64)"Negative values cannot be cast into 'U8'", 40});
        int _arr_status__tmp332 = til_Array_new(&_tmp331, &_err_alloc__tmp332, "Str", 1);
        if (_arr_status__tmp332 != 0) {
        }
        _arr_status__tmp332 = til_Array_set(&_err_idx__tmp332, &_tmp331, 0, &_tmp333);
        if (_arr_status__tmp332 != 0) {
        }
        int _status__tmp330 = til_format(&_tmp329, &_err0__tmp330, &_err1__tmp330, &_err2__tmp330, ((til_Str){(til_I64)"src/core/u8.til:56:47:", 22}), &_tmp331);
        if (_status__tmp330 != 0) {
        }
        til_Array_delete(&_tmp331);
        *_err1 = til_U8_OverflowError_new(_tmp329);
        return 1;
    }
    if (til_gt(til_self, til_MAX_U8).data) {
        til_Str _tmp335;
        til_I64_OverflowError _err0__tmp336;
        til_IndexOutOfBoundsError _err1__tmp336;
        til_AllocError _err2__tmp336;
        til_Array _tmp337;
        til_AllocError _err_alloc__tmp338;
        til_IndexOutOfBoundsError _err_idx__tmp338;
        til_Str _tmp339 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp340 = ((til_Str){(til_I64)"255", 3});
        int _arr_status__tmp338 = til_Array_new(&_tmp337, &_err_alloc__tmp338, "Str", 2);
        if (_arr_status__tmp338 != 0) {
        }
        _arr_status__tmp338 = til_Array_set(&_err_idx__tmp338, &_tmp337, 0, &_tmp339);
        if (_arr_status__tmp338 != 0) {
        }
        _arr_status__tmp338 = til_Array_set(&_err_idx__tmp338, &_tmp337, 1, &_tmp340);
        if (_arr_status__tmp338 != 0) {
        }
        int _status__tmp336 = til_format(&_tmp335, &_err0__tmp336, &_err1__tmp336, &_err2__tmp336, ((til_Str){(til_I64)"src/core/u8.til:59:47:", 22}), &_tmp337);
        if (_status__tmp336 != 0) {
        }
        til_Array_delete(&_tmp337);
        til_Str _tmp341;
        til_I64_OverflowError _err0__tmp342;
        til_IndexOutOfBoundsError _err1__tmp342;
        til_AllocError _err2__tmp342;
        til_Array _tmp343;
        til_AllocError _err_alloc__tmp344;
        til_IndexOutOfBoundsError _err_idx__tmp344;
        til_Str _tmp345 = ((til_Str){(til_I64)"U8: cannot be casted from an I64 greater than: ", 47});
        til_Str _tmp346 = ((til_Str){(til_I64)"255", 3});
        int _arr_status__tmp344 = til_Array_new(&_tmp343, &_err_alloc__tmp344, "Str", 2);
        if (_arr_status__tmp344 != 0) {
        }
        _arr_status__tmp344 = til_Array_set(&_err_idx__tmp344, &_tmp343, 0, &_tmp345);
        if (_arr_status__tmp344 != 0) {
        }
        _arr_status__tmp344 = til_Array_set(&_err_idx__tmp344, &_tmp343, 1, &_tmp346);
        if (_arr_status__tmp344 != 0) {
        }
        int _status__tmp342 = til_format(&_tmp341, &_err0__tmp342, &_err1__tmp342, &_err2__tmp342, ((til_Str){(til_I64)"src/core/u8.til:59:47:", 22}), &_tmp343);
        if (_status__tmp342 != 0) {
        }
        til_Array_delete(&_tmp343);
        *_err1 = til_U8_OverflowError_new(_tmp341);
        return 1;
    }
    *_ret = til_i64_to_u8(til_self);
    return 0;
}

int main() {
    til_Array _tmp348;
    til_AllocError _err_alloc__tmp349;
    til_IndexOutOfBoundsError _err_idx__tmp349;
    til_Str _tmp350 = ((til_Str){(til_I64)"Hello World!", 12});
    int _arr_status__tmp349 = til_Array_new(&_tmp348, &_err_alloc__tmp349, "Str", 1);
    if (_arr_status__tmp349 != 0) {
    }
    _arr_status__tmp349 = til_Array_set(&_err_idx__tmp349, &_tmp348, 0, &_tmp350);
    if (_arr_status__tmp349 != 0) {
    }
    til_println(&_tmp348);
    til_Array_delete(&_tmp348);
    return 0;
}
