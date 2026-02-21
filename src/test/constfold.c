#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char til_U8;
typedef long long til_I64;
typedef struct til_Bool { til_U8 data; } til_Bool;
typedef void* til_Dynamic;
typedef const char* til_Type;

typedef struct til_IndexOutOfBoundsError til_IndexOutOfBoundsError;
typedef struct til_BadAlloc til_BadAlloc;
typedef struct til_Ptr til_Ptr;
typedef struct til_Array til_Array;
typedef struct til_I64_Overflow til_I64_Overflow;
typedef struct til_DivideByZero til_DivideByZero;
typedef struct til_Vec til_Vec;
typedef struct til_Str til_Str;
typedef struct til_U8_Overflow til_U8_Overflow;
typedef struct til_HeapEntry til_HeapEntry;
typedef struct til_HeapState til_HeapState;
typedef struct til_Map til_Map;
typedef struct til_SEnumDef til_SEnumDef;
typedef struct til_Declaration til_Declaration;
typedef struct til_PatternInfo til_PatternInfo;
typedef struct til_SFuncDef til_SFuncDef;
typedef struct til_SStructDef til_SStructDef;
typedef struct til_SNamespaceDef til_SNamespaceDef;
typedef struct til_Literal til_Literal;
typedef struct til_NodeType til_NodeType;
typedef struct til_ValueType til_ValueType;
typedef struct til_CfVec2 til_CfVec2;
typedef struct til_CfRect til_CfRect;

typedef enum {
    til_FunctionType_FTFunc = 0,
    til_FunctionType_FTFuncExt = 1,
    til_FunctionType_FTMacro = 2,
    til_FunctionType_FTProc = 3,
    til_FunctionType_FTProcExt = 4,
} til_FunctionType;

static inline til_FunctionType til_FunctionType_make_FTFunc(void) { return til_FunctionType_FTFunc; }
static inline til_FunctionType til_FunctionType_make_FTFuncExt(void) { return til_FunctionType_FTFuncExt; }
static inline til_FunctionType til_FunctionType_make_FTMacro(void) { return til_FunctionType_FTMacro; }
static inline til_FunctionType til_FunctionType_make_FTProc(void) { return til_FunctionType_FTProc; }
static inline til_FunctionType til_FunctionType_make_FTProcExt(void) { return til_FunctionType_FTProcExt; }

typedef enum {
    til_TTypeDef_TEnumDef = 0,
    til_TTypeDef_TFuncSig = 1,
    til_TTypeDef_TStructDef = 2,
} til_TTypeDef;

static inline til_TTypeDef til_TTypeDef_make_TEnumDef(void) { return til_TTypeDef_TEnumDef; }
static inline til_TTypeDef til_TTypeDef_make_TFuncSig(void) { return til_TTypeDef_TFuncSig; }
static inline til_TTypeDef til_TTypeDef_make_TStructDef(void) { return til_TTypeDef_TStructDef; }

struct til_CfVec2 {
    til_I64 x;
    til_I64 y;
};

struct til_CfRect {
    til_CfVec2 top_left;
    til_CfVec2 bottom_right;
};

struct til_HeapState {
};

struct til_HeapEntry {
    til_I64 ptr;
    til_I64 size;
};

struct til_DivideByZero {
};

struct til_Ptr {
    til_I64 data;
    til_I64 is_borrowed;
    til_I64 alloc_size;
    til_I64 elem_type;
    til_I64 elem_size;
};

struct til_Str {
    til_Ptr c_string;
    til_I64 _len;
    til_I64 cap;
};

typedef enum {
    til_ValueType_TCustom = 0,
    til_ValueType_TFunction = 1,
    til_ValueType_TMulti = 2,
    til_ValueType_TType = 3,
} til_ValueType_Tag;

typedef union {
    til_Str TCustom;
    til_FunctionType TFunction;
    til_Str TMulti;
    til_TTypeDef TType;
} til_ValueType_Payload;

struct til_ValueType {
    til_I64 tag;
    til_ValueType_Payload payload;
};

static inline til_ValueType til_ValueType_make_TCustom(til_Str value) {
    til_ValueType result = { .tag = til_ValueType_TCustom };
    result.payload.TCustom = value;
    return result;
}

static inline til_ValueType til_ValueType_make_TFunction(til_FunctionType value) {
    til_ValueType result = { .tag = til_ValueType_TFunction };
    result.payload.TFunction = value;
    return result;
}

static inline til_ValueType til_ValueType_make_TMulti(til_Str value) {
    til_ValueType result = { .tag = til_ValueType_TMulti };
    result.payload.TMulti = value;
    return result;
}

static inline til_ValueType til_ValueType_make_TType(til_TTypeDef value) {
    til_ValueType result = { .tag = til_ValueType_TType };
    result.payload.TType = value;
    return result;
}

struct til_Declaration {
    til_Str name;
    til_ValueType value_type;
    til_Bool is_mut;
    til_Bool is_copy;
    til_Bool is_own;
    til_Ptr default_value;
};

typedef enum {
    til_Literal_List = 0,
    til_Literal_Number = 1,
    til_Literal_Str = 2,
} til_Literal_Tag;

typedef union {
    til_Str List;
    til_Str Number;
    til_Str Str;
} til_Literal_Payload;

struct til_Literal {
    til_I64 tag;
    til_Literal_Payload payload;
};

static inline til_Literal til_Literal_make_List(til_Str value) {
    til_Literal result = { .tag = til_Literal_List };
    result.payload.List = value;
    return result;
}

static inline til_Literal til_Literal_make_Number(til_Str value) {
    til_Literal result = { .tag = til_Literal_Number };
    result.payload.Number = value;
    return result;
}

static inline til_Literal til_Literal_make_Str(til_Str value) {
    til_Literal result = { .tag = til_Literal_Str };
    result.payload.Str = value;
    return result;
}

struct til_PatternInfo {
    til_Str variant_name;
    til_Str binding_var;
};

struct til_U8_Overflow {
    til_Str msg;
};

struct til_I64_Overflow {
    til_Str msg;
};

struct til_IndexOutOfBoundsError {
    til_Str msg;
};

struct til_Vec {
    til_Ptr ptr;
    til_I64 _len;
    til_I64 cap;
};

struct til_SFuncDef {
    til_FunctionType function_type;
    til_Vec args;
    til_Vec return_types;
    til_Vec throw_types;
    til_Vec body;
    til_Str source_path;
};

struct til_Map {
    til_Vec keys;
    til_Vec values;
    til_I64 _size;
};

struct til_SNamespaceDef {
    til_Str type_name;
    til_Vec members;
    til_Map default_values;
};

struct til_SStructDef {
    til_Vec members;
    til_Map default_values;
};

struct til_SEnumDef {
    til_Vec variants;
    til_Map methods;
};

typedef enum {
    til_NodeType_Assignment = 0,
    til_NodeType_Body = 1,
    til_NodeType_Break = 2,
    til_NodeType_Catch = 3,
    til_NodeType_Continue = 4,
    til_NodeType_Declaration = 5,
    til_NodeType_DefaultCase = 6,
    til_NodeType_EnumDef = 7,
    til_NodeType_FCall = 8,
    til_NodeType_ForIn = 9,
    til_NodeType_FuncDef = 10,
    til_NodeType_Identifier = 11,
    til_NodeType_If = 12,
    til_NodeType_LLiteral = 13,
    til_NodeType_NamedArg = 14,
    til_NodeType_NamespaceDef = 15,
    til_NodeType_Pattern = 16,
    til_NodeType_Range = 17,
    til_NodeType_Return = 18,
    til_NodeType_StructDef = 19,
    til_NodeType_Switch = 20,
    til_NodeType_Throw = 21,
    til_NodeType_While = 22,
} til_NodeType_Tag;

typedef union {
    til_Str Assignment;
    til_Declaration Declaration;
    til_SEnumDef EnumDef;
    til_Bool FCall;
    til_Str ForIn;
    til_SFuncDef FuncDef;
    til_Str Identifier;
    til_Literal LLiteral;
    til_Str NamedArg;
    til_SNamespaceDef NamespaceDef;
    til_PatternInfo Pattern;
    til_SStructDef StructDef;
} til_NodeType_Payload;

struct til_NodeType {
    til_I64 tag;
    til_NodeType_Payload payload;
};

static inline til_NodeType til_NodeType_make_Assignment(til_Str value) {
    til_NodeType result = { .tag = til_NodeType_Assignment };
    result.payload.Assignment = value;
    return result;
}

static inline til_NodeType til_NodeType_make_Body(void) {
    til_NodeType result = { .tag = til_NodeType_Body };
    return result;
}

static inline til_NodeType til_NodeType_make_Break(void) {
    til_NodeType result = { .tag = til_NodeType_Break };
    return result;
}

static inline til_NodeType til_NodeType_make_Catch(void) {
    til_NodeType result = { .tag = til_NodeType_Catch };
    return result;
}

static inline til_NodeType til_NodeType_make_Continue(void) {
    til_NodeType result = { .tag = til_NodeType_Continue };
    return result;
}

static inline til_NodeType til_NodeType_make_Declaration(til_Declaration value) {
    til_NodeType result = { .tag = til_NodeType_Declaration };
    result.payload.Declaration = value;
    return result;
}

static inline til_NodeType til_NodeType_make_DefaultCase(void) {
    til_NodeType result = { .tag = til_NodeType_DefaultCase };
    return result;
}

static inline til_NodeType til_NodeType_make_EnumDef(til_SEnumDef value) {
    til_NodeType result = { .tag = til_NodeType_EnumDef };
    result.payload.EnumDef = value;
    return result;
}

static inline til_NodeType til_NodeType_make_FCall(til_Bool value) {
    til_NodeType result = { .tag = til_NodeType_FCall };
    result.payload.FCall = value;
    return result;
}

static inline til_NodeType til_NodeType_make_ForIn(til_Str value) {
    til_NodeType result = { .tag = til_NodeType_ForIn };
    result.payload.ForIn = value;
    return result;
}

static inline til_NodeType til_NodeType_make_FuncDef(til_SFuncDef value) {
    til_NodeType result = { .tag = til_NodeType_FuncDef };
    result.payload.FuncDef = value;
    return result;
}

static inline til_NodeType til_NodeType_make_Identifier(til_Str value) {
    til_NodeType result = { .tag = til_NodeType_Identifier };
    result.payload.Identifier = value;
    return result;
}

static inline til_NodeType til_NodeType_make_If(void) {
    til_NodeType result = { .tag = til_NodeType_If };
    return result;
}

static inline til_NodeType til_NodeType_make_LLiteral(til_Literal value) {
    til_NodeType result = { .tag = til_NodeType_LLiteral };
    result.payload.LLiteral = value;
    return result;
}

static inline til_NodeType til_NodeType_make_NamedArg(til_Str value) {
    til_NodeType result = { .tag = til_NodeType_NamedArg };
    result.payload.NamedArg = value;
    return result;
}

static inline til_NodeType til_NodeType_make_NamespaceDef(til_SNamespaceDef value) {
    til_NodeType result = { .tag = til_NodeType_NamespaceDef };
    result.payload.NamespaceDef = value;
    return result;
}

static inline til_NodeType til_NodeType_make_Pattern(til_PatternInfo value) {
    til_NodeType result = { .tag = til_NodeType_Pattern };
    result.payload.Pattern = value;
    return result;
}

static inline til_NodeType til_NodeType_make_Range(void) {
    til_NodeType result = { .tag = til_NodeType_Range };
    return result;
}

static inline til_NodeType til_NodeType_make_Return(void) {
    til_NodeType result = { .tag = til_NodeType_Return };
    return result;
}

static inline til_NodeType til_NodeType_make_StructDef(til_SStructDef value) {
    til_NodeType result = { .tag = til_NodeType_StructDef };
    result.payload.StructDef = value;
    return result;
}

static inline til_NodeType til_NodeType_make_Switch(void) {
    til_NodeType result = { .tag = til_NodeType_Switch };
    return result;
}

static inline til_NodeType til_NodeType_make_Throw(void) {
    til_NodeType result = { .tag = til_NodeType_Throw };
    return result;
}

static inline til_NodeType til_NodeType_make_While(void) {
    til_NodeType result = { .tag = til_NodeType_While };
    return result;
}

struct til_Array {
    til_Ptr ptr;
    til_I64 _len;
};

struct til_BadAlloc {
};

til_I64 til_memcmp(const til_I64* til_I64_ptr1, const til_I64* til_I64_ptr2, const til_I64* til_I64_size);
til_Bool til_not(const til_Bool* til_Bool_b);
void til_panic(const til_Str* til_Str_loc_str, const til_Str* til_Str_msg, til_Array* til_Array_extra_msgs);
void til_assertm(const til_Str* til_Str_loc_str, const til_Bool* til_Bool_cond, const til_Str* til_Str_msg);
void til_println(til_Array* til_Array_args);
int til_get_substr(til_Str* _ret, til_IndexOutOfBoundsError* _err1, const til_Str* til_Str_s, const til_I64* til_I64_start, const til_I64* til_I64_end);
til_Str til_concat(const til_Str* til_Str_a, const til_Str* til_Str_b);
til_Str til_format(const til_Str* til_Str_prefix, til_Array* til_Array_args);
void til_test(const til_Str* til_Str_loc_str, const til_Bool* til_Bool_cond, const til_Str* til_Str_msg);
void til_assert_eq(const til_Str* til_Str_loc_str, const til_I64* til_I64_a, const til_I64* til_I64_b);
void til_test_simple_add(void);
void til_test_nested_arithmetic(void);
void til_test_deeply_nested(void);
void til_test_string_concat(void);
void til_test_fold_variable(void);
void til_test_loc_folded_correctly(void);
void til_test_struct_fold_simple(void);
void til_test_struct_fold_values(void);
void til_test_struct_fold_nested(void);
til_FunctionType til_FunctionType_clone(const til_FunctionType* til_FunctionType_self);
void til_FunctionType_delete(til_FunctionType* _self);
til_Literal til_Literal_clone(const til_Literal* til_Literal_self);
void til_Literal_delete(til_Literal* _self);
til_NodeType til_NodeType_clone(const til_NodeType* til_NodeType_self);
void til_NodeType_delete(til_NodeType* _self);
til_TTypeDef til_TTypeDef_clone(const til_TTypeDef* til_TTypeDef_self);
void til_TTypeDef_delete(til_TTypeDef* _self);
til_ValueType til_ValueType_clone(const til_ValueType* til_ValueType_self);
void til_ValueType_delete(til_ValueType* _self);
void til_IndexOutOfBoundsError_delete(til_IndexOutOfBoundsError* til_IndexOutOfBoundsError_self);
til_IndexOutOfBoundsError til_IndexOutOfBoundsError_clone(const til_IndexOutOfBoundsError* til_IndexOutOfBoundsError_self);
void til_BadAlloc_delete(til_BadAlloc* _self);
til_BadAlloc til_BadAlloc_clone(const til_BadAlloc* _self);
til_Ptr til_Ptr_new_by_size(const til_I64* til_I64_size);
til_Ptr til_Ptr_new(til_Type til_Type_T);
til_Ptr til_Ptr_new_array(til_Type til_Type_T, const til_I64* til_I64_count);
void til_Ptr_delete(til_Ptr* til_Ptr_self);
til_Ptr til_Ptr_clone(const til_Ptr* til_Ptr_self);
til_Ptr til_Ptr_offset(const til_Ptr* til_Ptr_self, const til_I64* til_I64_byte_offset);
void til_Ptr_copy_from(til_Ptr* til_Ptr_self, const til_Ptr* til_Ptr_src, const til_I64* til_I64_size);
void til_Ptr_copy_to(const til_Ptr* til_Ptr_self, til_Ptr* til_Ptr_dest, const til_I64* til_I64_size);
void til_Ptr_set_zero(til_Ptr* til_Ptr_self, const til_I64* til_I64_size);
void til_Ptr_copy_from_dynamic(til_Ptr* til_Ptr_self, const til_Dynamic* til_Dynamic_value, const til_I64* til_I64_size);
void til_Ptr_copy_to_dynamic(const til_Ptr* til_Ptr_self, til_Dynamic* til_Dynamic_dest, const til_I64* til_I64_size);
void til_Ptr_dereference(const til_Ptr* til_Ptr_self, til_Type til_Type_T, til_Dynamic* til_Dynamic_dest);
til_I64 til_Ptr_size_of(void);
til_Bool til_Ptr_is_null(const til_Ptr* til_Ptr_self);
til_I64 til_Array_len(const til_Array* til_Array_self);
til_I64 til_Array_size(const til_Array* til_Array_self);
til_Array til_Array_new(til_Type til_Type_T, const til_I64* til_I64_capacity);
int til_Array_get(til_Ptr* _ret, til_IndexOutOfBoundsError* _err1, const til_Array* til_Array_self, const til_I64* til_I64_index);
int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_Array_self, const til_I64* til_I64_index, til_Dynamic* til_Dynamic_value);
void til_Array_delete(til_Array* til_Array_self);
til_Array til_Array_clone(const til_Array* til_Array_self);
til_Bool til_Array_contains(const til_Array* til_Array_self, const til_Str* til_Str_value);
til_I64 til_Bool_len(const til_Bool* _self);
til_Bool til_Bool_eq(const til_Bool* til_Bool_a, const til_Bool* til_Bool_b);
til_Bool til_Bool_and(const til_Bool* til_Bool_self, const til_Bool* til_Bool_other);
til_Bool til_Bool_or(const til_Bool* til_Bool_self, const til_Bool* til_Bool_other);
til_Str til_Bool_to_str(const til_Bool* til_Bool_self);
til_I64 til_Bool_to_i64(const til_Bool* til_Bool_self);
til_U8 til_Bool_to_u8(const til_Bool* til_Bool_self);
til_Bool til_Bool_from_i64(const til_I64* til_I64_i);
til_I64 til_Bool_size(void);
void til_Bool_delete(til_Bool* _self);
til_Bool til_Bool_clone(const til_Bool* til_Bool_self);
int til_I64_safe_div(til_I64* _ret, const til_I64* til_I64_a, const til_I64* til_I64_b);
int til_I64_safe_add(til_I64* _ret, til_I64_Overflow* _err1, const til_I64* til_I64_a, const til_I64* til_I64_b);
int til_I64_safe_sub(til_I64* _ret, til_I64_Overflow* _err1, const til_I64* til_I64_a, const til_I64* til_I64_b);
int til_I64_safe_mul(til_I64* _ret, til_I64_Overflow* _err1, const til_I64* til_I64_a, const til_I64* til_I64_b);
til_I64 til_I64_xor(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_I64 til_I64_and(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_I64 til_I64_or(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_I64 til_I64_mod(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_I64 til_I64_sub(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_I64 til_I64_mul(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_I64 til_I64_div(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_I64 til_I64_add(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_Bool til_I64_eq(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_Bool til_I64_lt(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_Bool til_I64_gt(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_Str til_I64_to_str(const til_I64* til_I64_self);
til_I64 til_I64_from_str(const til_Str* til_Str_str);
void til_I64_inc(til_I64* til_I64_self);
void til_I64_dec(til_I64* til_I64_self);
til_Bool til_I64_gteq(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_Bool til_I64_lteq(const til_I64* til_I64_a, const til_I64* til_I64_b);
til_I64 til_I64_size(void);
void til_I64_delete(til_I64* _self);
til_I64 til_I64_clone(const til_I64* til_I64_self);
til_I64 til_Vec_len(const til_Vec* til_Vec_self);
til_I64 til_Vec_size(const til_Vec* til_Vec_self);
til_Bool til_Vec__is_str_type(const til_Vec* til_Vec_self);
til_Vec til_Vec_new(til_Type til_Type_T);
til_Vec til_Vec_new_from_type_info(const til_Str* til_Str_type_name, const til_I64* til_I64_type_size);
til_Ptr til_Vec__alloc_ptr(til_Vec* til_Vec_self, const til_I64* til_I64_capacity);
til_Vec til_Vec_with_capacity(til_Type til_Type_T, const til_I64* til_I64_capacity);
void til_Vec_push(til_Vec* til_Vec_self, til_Dynamic* til_Dynamic_value);
int til_Vec_get(til_Ptr* _ret, til_IndexOutOfBoundsError* _err1, const til_Vec* til_Vec_self, const til_I64* til_I64_index);
int til_Vec_set(til_IndexOutOfBoundsError* _err1, til_Vec* til_Vec_self, const til_I64* til_I64_index, til_Dynamic* til_Dynamic_value);
int til_Vec_pop(til_IndexOutOfBoundsError* _err1, til_Vec* til_Vec_self, til_Dynamic* til_Dynamic_dest);
void til_Vec_delete(til_Vec* til_Vec_self);
til_Vec til_Vec_clone(const til_Vec* til_Vec_self);
void til_Vec_extend(til_Vec* til_Vec_self, const til_Vec* til_Vec_other);
void til_Vec_extend_with(til_Vec* til_Vec_self, til_Dynamic* til_Dynamic_value, const til_I64* til_I64_count);
til_Bool til_Vec_contains(const til_Vec* til_Vec_self, const til_Dynamic* til_Dynamic_value);
int til_Vec_remove(til_IndexOutOfBoundsError* _err1, til_Vec* til_Vec_self, const til_I64* til_I64_index);
int til_Vec_insert_at(til_IndexOutOfBoundsError* _err1, til_Vec* til_Vec_self, const til_I64* til_I64_index, til_Dynamic* til_Dynamic_value);
til_Str til_Vec_to_str(const til_Vec* til_Vec_self);
til_Bool til_Vec_is_empty(const til_Vec* til_Vec_self);
int til_Vec_split_off(til_Vec* _ret, til_IndexOutOfBoundsError* _err1, til_Vec* til_Vec_self, const til_I64* til_I64_at);
void til_Vec_clear(til_Vec* til_Vec_self);
til_I64 til_Str_len(const til_Str* til_Str_self);
til_Bool til_Str_is_empty(const til_Str* til_Str_self);
til_Bool til_Str_eq(const til_Str* til_Str_self, const til_Str* til_Str_other);
til_I64 til_Str_to_i64(const til_Str* til_Str_self);
til_Str til_Str_clone(const til_Str* til_Str_self);
void til_Str_delete(til_Str* til_Str_self);
til_Str til_Str_from_byte(const til_U8* til_U8_byte);
void til_Str_push_str(til_Str* til_Str_self, const til_Str* til_Str_s);
til_I64 til_Str_size(const til_Str* til_Str_self);
til_Bool til_Str_is_uppercase(const til_Str* til_Str_self);
til_Str til_Str_to_lowercase(const til_Str* til_Str_self);
til_Bool til_Str_contains(const til_Str* til_Str_self, const til_Str* til_Str_needle);
til_I64 til_Str_find(const til_Str* til_Str_self, const til_Str* til_Str_needle);
til_I64 til_Str_rfind(const til_Str* til_Str_self, const til_Str* til_Str_needle);
til_Str til_Str_replace(const til_Str* til_Str_self, const til_Str* til_Str_from, const til_Str* til_Str_to);
til_U8 til_Str_char_at(const til_Str* til_Str_self, const til_I64* til_I64_index);
til_I64 til_Str_cmp(const til_Str* til_Str_self, const til_Str* til_Str_other);
til_Bool til_Str_lt(const til_Str* til_Str_self, const til_Str* til_Str_other);
til_Bool til_Str_gt(const til_Str* til_Str_self, const til_Str* til_Str_other);
til_Bool til_Str_lteq(const til_Str* til_Str_self, const til_Str* til_Str_other);
til_Bool til_Str_gteq(const til_Str* til_Str_self, const til_Str* til_Str_other);
void til_Str_inc(til_Str* til_Str_self);
void til_Str_dec(til_Str* til_Str_self);
til_Str til_Str_replacen(const til_Str* til_Str_self, const til_Str* til_Str_from, const til_Str* til_Str_to, const til_I64* til_I64_n);
int til_Str_split(til_Vec* _ret, til_IndexOutOfBoundsError* _err1, const til_Str* til_Str_self, const til_Str* til_Str_delimiter);
til_Str til_Str_repeat(const til_Str* til_Str_self, const til_I64* til_I64_n);
til_I64 til_Str_hash(const til_Str* til_Str_self);
til_I64 til_U8_len(const til_U8* _self);
til_Bool til_U8_lt(const til_U8* til_U8_self, const til_U8* til_U8_other);
til_Bool til_U8_gt(const til_U8* til_U8_self, const til_U8* til_U8_other);
til_Bool til_U8_eq(const til_U8* til_U8_a, const til_U8* til_U8_b);
til_I64 til_U8_to_i64(const til_U8* til_U8_self);
til_U8 til_U8_add(const til_U8* til_U8_a, const til_U8* til_U8_b);
int til_U8_safe_add(til_U8* _ret, til_U8_Overflow* _err1, const til_U8* til_U8_a, const til_U8* til_U8_b);
til_U8 til_U8_sub(const til_U8* til_U8_a, const til_U8* til_U8_b);
int til_U8_safe_sub(til_U8* _ret, til_U8_Overflow* _err1, const til_U8* til_U8_a, const til_U8* til_U8_b);
til_U8 til_U8_mul(const til_U8* til_U8_a, const til_U8* til_U8_b);
int til_U8_safe_mul(til_U8* _ret, til_U8_Overflow* _err1, const til_U8* til_U8_a, const til_U8* til_U8_b);
til_U8 til_U8_div(const til_U8* til_U8_a, const til_U8* til_U8_b);
int til_U8_safe_div(til_U8* _ret, const til_U8* til_U8_a, const til_U8* til_U8_b);
til_U8 til_U8_mod(const til_U8* til_U8_a, const til_U8* til_U8_b);
til_U8 til_U8_xor(const til_U8* til_U8_a, const til_U8* til_U8_b);
til_U8 til_U8_and(const til_U8* til_U8_a, const til_U8* til_U8_b);
til_U8 til_U8_or(const til_U8* til_U8_a, const til_U8* til_U8_b);
int til_U8_from_i64(til_U8* _ret, til_U8_Overflow* _err1, const til_I64* til_I64_self);
til_Str til_U8_to_str(const til_U8* til_U8_self);
int til_U8_from_str(til_U8* _ret, til_U8_Overflow* _err1, const til_Str* til_Str_s);
void til_U8_inc(til_U8* til_U8_self);
void til_U8_dec(til_U8* til_U8_self);
til_Bool til_U8_gteq(const til_U8* til_U8_a, const til_U8* til_U8_b);
til_Bool til_U8_lteq(const til_U8* til_U8_a, const til_U8* til_U8_b);
til_I64 til_U8_size(void);
void til_U8_delete(til_U8* _self);
til_U8 til_U8_clone(const til_U8* til_U8_self);
void til_HeapState_enable(void);
void til_HeapState_disable(void);
void til_HeapState_add(const til_I64* til_I64_ptr, const til_I64* til_I64_size);
void til_HeapState_remove(const til_I64* til_I64_ptr);
void til_HeapState_report(void);
void til_HeapEntry_delete(til_HeapEntry* _self);
til_HeapEntry til_HeapEntry_clone(const til_HeapEntry* til_HeapEntry_self);
void til_HeapState_delete(til_HeapState* _self);
til_HeapState til_HeapState_clone(const til_HeapState* _self);
void til_Dynamic_delete(til_Dynamic* _self);
til_Dynamic til_Dynamic_clone(const til_Dynamic* _self);
void til_Type_delete(til_Type* _self);
til_Type til_Type_clone(til_Type _self);
til_CfVec2 til_CfVec2_magic(void);
til_CfVec2 til_CfVec2_at(const til_I64* til_I64_x, const til_I64* til_I64_y);
til_CfRect til_CfRect_sample(void);
void til_CfVec2_delete(til_CfVec2* _self);
til_CfVec2 til_CfVec2_clone(const til_CfVec2* til_CfVec2_self);
void til_CfRect_delete(til_CfRect* til_CfRect_self);
til_CfRect til_CfRect_clone(const til_CfRect* til_CfRect_self);

#include <ext.c>

const til_I64 til_size_of_IndexOutOfBoundsError = sizeof(til_IndexOutOfBoundsError);
const til_I64 til_size_of_BadAlloc = sizeof(til_BadAlloc);
const til_I64 til_size_of_Ptr = sizeof(til_Ptr);
const til_I64 til_size_of_Array = sizeof(til_Array);
const til_I64 til_size_of_Bool = sizeof(til_Bool);
const til_I64 til_size_of_I64_Overflow = sizeof(til_I64_Overflow);
const til_I64 til_size_of_DivideByZero = sizeof(til_DivideByZero);
const til_I64 til_size_of_I64 = sizeof(til_I64);
const til_I64 til_Vec_INIT_CAP = 0;
const til_I64 til_Vec_MAX_CAP = 1073741824;
const til_I64 til_size_of_Vec = sizeof(til_Vec);
const til_I64 til_size_of_Str = sizeof(til_Str);
const til_I64 til_size_of_U8_Overflow = sizeof(til_U8_Overflow);
const til_I64 til_size_of_U8 = sizeof(til_U8);
const til_I64 til_size_of_HeapEntry = sizeof(til_HeapEntry);
const til_I64 til_size_of_HeapState = sizeof(til_HeapState);
const til_I64 til_size_of_Map = sizeof(til_Map);
const til_I64 til_size_of_SEnumDef = sizeof(til_SEnumDef);
const til_I64 til_size_of_Declaration = sizeof(til_Declaration);
const til_I64 til_size_of_PatternInfo = sizeof(til_PatternInfo);
const til_I64 til_size_of_SFuncDef = sizeof(til_SFuncDef);
const til_I64 til_size_of_SStructDef = sizeof(til_SStructDef);
const til_I64 til_size_of_SNamespaceDef = sizeof(til_SNamespaceDef);
const til_I64 til_size_of_Dynamic = sizeof(til_Dynamic);
const til_I64 til_size_of_Type = sizeof(til_Type);
const til_I64 til_size_of_CfVec2 = sizeof(til_CfVec2);
const til_I64 til_size_of_CfRect = sizeof(til_CfRect);
const til_I64 til_size_of_FunctionType = sizeof(til_FunctionType);
const til_I64 til_size_of_Literal = sizeof(til_Literal);
const til_I64 til_size_of_NodeType = sizeof(til_NodeType);
const til_I64 til_size_of_TTypeDef = sizeof(til_TTypeDef);
const til_I64 til_size_of_ValueType = sizeof(til_ValueType);
static inline til_Str til_FunctionType_to_str(const til_FunctionType* e) {
    switch(*e) {
        case til_FunctionType_FTFunc: return ((til_Str){((til_Ptr){(til_I64)"FunctionType.FTFunc", 1, 0, 0, 0}), 19, 0});
        case til_FunctionType_FTFuncExt: return ((til_Str){((til_Ptr){(til_I64)"FunctionType.FTFuncExt", 1, 0, 0, 0}), 22, 0});
        case til_FunctionType_FTMacro: return ((til_Str){((til_Ptr){(til_I64)"FunctionType.FTMacro", 1, 0, 0, 0}), 20, 0});
        case til_FunctionType_FTProc: return ((til_Str){((til_Ptr){(til_I64)"FunctionType.FTProc", 1, 0, 0, 0}), 19, 0});
        case til_FunctionType_FTProcExt: return ((til_Str){((til_Ptr){(til_I64)"FunctionType.FTProcExt", 1, 0, 0, 0}), 22, 0});
    }
    return ((til_Str){((til_Ptr){(til_I64)"FunctionType.?", 1, 0, 0, 0}), 14, 0});
}

static inline til_Str til_Literal_to_str(const til_Literal* e) {
    switch(e->tag) {
        case til_Literal_List: return ((til_Str){((til_Ptr){(til_I64)"Literal.List", 1, 0, 0, 0}), 12, 0});
        case til_Literal_Number: return ((til_Str){((til_Ptr){(til_I64)"Literal.Number", 1, 0, 0, 0}), 14, 0});
        case til_Literal_Str: return ((til_Str){((til_Ptr){(til_I64)"Literal.Str", 1, 0, 0, 0}), 11, 0});
    }
    return ((til_Str){((til_Ptr){(til_I64)"Literal.?", 1, 0, 0, 0}), 9, 0});
}

static inline til_Str til_NodeType_to_str(const til_NodeType* e) {
    switch(e->tag) {
        case til_NodeType_Assignment: return ((til_Str){((til_Ptr){(til_I64)"NodeType.Assignment", 1, 0, 0, 0}), 19, 0});
        case til_NodeType_Body: return ((til_Str){((til_Ptr){(til_I64)"NodeType.Body", 1, 0, 0, 0}), 13, 0});
        case til_NodeType_Break: return ((til_Str){((til_Ptr){(til_I64)"NodeType.Break", 1, 0, 0, 0}), 14, 0});
        case til_NodeType_Catch: return ((til_Str){((til_Ptr){(til_I64)"NodeType.Catch", 1, 0, 0, 0}), 14, 0});
        case til_NodeType_Continue: return ((til_Str){((til_Ptr){(til_I64)"NodeType.Continue", 1, 0, 0, 0}), 17, 0});
        case til_NodeType_Declaration: return ((til_Str){((til_Ptr){(til_I64)"NodeType.Declaration", 1, 0, 0, 0}), 20, 0});
        case til_NodeType_DefaultCase: return ((til_Str){((til_Ptr){(til_I64)"NodeType.DefaultCase", 1, 0, 0, 0}), 20, 0});
        case til_NodeType_EnumDef: return ((til_Str){((til_Ptr){(til_I64)"NodeType.EnumDef", 1, 0, 0, 0}), 16, 0});
        case til_NodeType_FCall: return ((til_Str){((til_Ptr){(til_I64)"NodeType.FCall", 1, 0, 0, 0}), 14, 0});
        case til_NodeType_ForIn: return ((til_Str){((til_Ptr){(til_I64)"NodeType.ForIn", 1, 0, 0, 0}), 14, 0});
        case til_NodeType_FuncDef: return ((til_Str){((til_Ptr){(til_I64)"NodeType.FuncDef", 1, 0, 0, 0}), 16, 0});
        case til_NodeType_Identifier: return ((til_Str){((til_Ptr){(til_I64)"NodeType.Identifier", 1, 0, 0, 0}), 19, 0});
        case til_NodeType_If: return ((til_Str){((til_Ptr){(til_I64)"NodeType.If", 1, 0, 0, 0}), 11, 0});
        case til_NodeType_LLiteral: return ((til_Str){((til_Ptr){(til_I64)"NodeType.LLiteral", 1, 0, 0, 0}), 17, 0});
        case til_NodeType_NamedArg: return ((til_Str){((til_Ptr){(til_I64)"NodeType.NamedArg", 1, 0, 0, 0}), 17, 0});
        case til_NodeType_NamespaceDef: return ((til_Str){((til_Ptr){(til_I64)"NodeType.NamespaceDef", 1, 0, 0, 0}), 21, 0});
        case til_NodeType_Pattern: return ((til_Str){((til_Ptr){(til_I64)"NodeType.Pattern", 1, 0, 0, 0}), 16, 0});
        case til_NodeType_Range: return ((til_Str){((til_Ptr){(til_I64)"NodeType.Range", 1, 0, 0, 0}), 14, 0});
        case til_NodeType_Return: return ((til_Str){((til_Ptr){(til_I64)"NodeType.Return", 1, 0, 0, 0}), 15, 0});
        case til_NodeType_StructDef: return ((til_Str){((til_Ptr){(til_I64)"NodeType.StructDef", 1, 0, 0, 0}), 18, 0});
        case til_NodeType_Switch: return ((til_Str){((til_Ptr){(til_I64)"NodeType.Switch", 1, 0, 0, 0}), 15, 0});
        case til_NodeType_Throw: return ((til_Str){((til_Ptr){(til_I64)"NodeType.Throw", 1, 0, 0, 0}), 14, 0});
        case til_NodeType_While: return ((til_Str){((til_Ptr){(til_I64)"NodeType.While", 1, 0, 0, 0}), 14, 0});
    }
    return ((til_Str){((til_Ptr){(til_I64)"NodeType.?", 1, 0, 0, 0}), 10, 0});
}

static inline til_Str til_TTypeDef_to_str(const til_TTypeDef* e) {
    switch(*e) {
        case til_TTypeDef_TEnumDef: return ((til_Str){((til_Ptr){(til_I64)"TTypeDef.TEnumDef", 1, 0, 0, 0}), 17, 0});
        case til_TTypeDef_TFuncSig: return ((til_Str){((til_Ptr){(til_I64)"TTypeDef.TFuncSig", 1, 0, 0, 0}), 17, 0});
        case til_TTypeDef_TStructDef: return ((til_Str){((til_Ptr){(til_I64)"TTypeDef.TStructDef", 1, 0, 0, 0}), 19, 0});
    }
    return ((til_Str){((til_Ptr){(til_I64)"TTypeDef.?", 1, 0, 0, 0}), 10, 0});
}

static inline til_Str til_ValueType_to_str(const til_ValueType* e) {
    switch(e->tag) {
        case til_ValueType_TCustom: return ((til_Str){((til_Ptr){(til_I64)"ValueType.TCustom", 1, 0, 0, 0}), 17, 0});
        case til_ValueType_TFunction: return ((til_Str){((til_Ptr){(til_I64)"ValueType.TFunction", 1, 0, 0, 0}), 19, 0});
        case til_ValueType_TMulti: return ((til_Str){((til_Ptr){(til_I64)"ValueType.TMulti", 1, 0, 0, 0}), 16, 0});
        case til_ValueType_TType: return ((til_Str){((til_Ptr){(til_I64)"ValueType.TType", 1, 0, 0, 0}), 15, 0});
    }
    return ((til_Str){((til_Ptr){(til_I64)"ValueType.?", 1, 0, 0, 0}), 11, 0});
}

const til_I64 til_I64_NULL = 0;
const til_I64 til_I64_I64_SIZE = 8;
const til_I64 til_I64_I64_MINUS1 = -1;
const til_I64 til_I64_MIN_I64 = -922337203;
const til_I64 til_I64_MAX_I64 = 9223372036854775807;
const til_I64 til_I64_U8_SIZE = 1;
const til_I64 til_I64_MIN_U8 = 0;
const til_I64 til_I64_MAX_U8 = 255;
const til_U8 til_U8_ZERO_U8 = 0;
static til_Vec til_Vec_g_entries;
static til_Bool til_Bool_g_enabled;

static inline til_I64 til_size_of(const til_Str* type_name) {
    if (strcmp((char*)type_name->c_string.data, "IndexOutOfBoundsError") == 0) return til_size_of_IndexOutOfBoundsError;
    if (strcmp((char*)type_name->c_string.data, "BadAlloc") == 0) return til_size_of_BadAlloc;
    if (strcmp((char*)type_name->c_string.data, "Ptr") == 0) return til_size_of_Ptr;
    if (strcmp((char*)type_name->c_string.data, "Array") == 0) return til_size_of_Array;
    if (strcmp((char*)type_name->c_string.data, "Bool") == 0) return til_size_of_Bool;
    if (strcmp((char*)type_name->c_string.data, "I64_Overflow") == 0) return til_size_of_I64_Overflow;
    if (strcmp((char*)type_name->c_string.data, "DivideByZero") == 0) return til_size_of_DivideByZero;
    if (strcmp((char*)type_name->c_string.data, "I64") == 0) return til_size_of_I64;
    if (strcmp((char*)type_name->c_string.data, "Vec") == 0) return til_size_of_Vec;
    if (strcmp((char*)type_name->c_string.data, "Str") == 0) return til_size_of_Str;
    if (strcmp((char*)type_name->c_string.data, "U8_Overflow") == 0) return til_size_of_U8_Overflow;
    if (strcmp((char*)type_name->c_string.data, "U8") == 0) return til_size_of_U8;
    if (strcmp((char*)type_name->c_string.data, "HeapEntry") == 0) return til_size_of_HeapEntry;
    if (strcmp((char*)type_name->c_string.data, "HeapState") == 0) return til_size_of_HeapState;
    if (strcmp((char*)type_name->c_string.data, "Map") == 0) return til_size_of_Map;
    if (strcmp((char*)type_name->c_string.data, "SEnumDef") == 0) return til_size_of_SEnumDef;
    if (strcmp((char*)type_name->c_string.data, "Declaration") == 0) return til_size_of_Declaration;
    if (strcmp((char*)type_name->c_string.data, "PatternInfo") == 0) return til_size_of_PatternInfo;
    if (strcmp((char*)type_name->c_string.data, "SFuncDef") == 0) return til_size_of_SFuncDef;
    if (strcmp((char*)type_name->c_string.data, "SStructDef") == 0) return til_size_of_SStructDef;
    if (strcmp((char*)type_name->c_string.data, "SNamespaceDef") == 0) return til_size_of_SNamespaceDef;
    if (strcmp((char*)type_name->c_string.data, "Dynamic") == 0) return til_size_of_Dynamic;
    if (strcmp((char*)type_name->c_string.data, "Type") == 0) return til_size_of_Type;
    if (strcmp((char*)type_name->c_string.data, "CfVec2") == 0) return til_size_of_CfVec2;
    if (strcmp((char*)type_name->c_string.data, "CfRect") == 0) return til_size_of_CfRect;
    if (strcmp((char*)type_name->c_string.data, "FunctionType") == 0) return til_size_of_FunctionType;
    if (strcmp((char*)type_name->c_string.data, "Literal") == 0) return til_size_of_Literal;
    if (strcmp((char*)type_name->c_string.data, "NodeType") == 0) return til_size_of_NodeType;
    if (strcmp((char*)type_name->c_string.data, "TTypeDef") == 0) return til_size_of_TTypeDef;
    if (strcmp((char*)type_name->c_string.data, "ValueType") == 0) return til_size_of_ValueType;
    fprintf(stderr, "size_of: unknown type %s\n", (char*)type_name->c_string.data);
    exit(1);
}

til_I64 til_memcmp(const til_I64* til_I64_ptr1, const til_I64* til_I64_ptr2, const til_I64* til_I64_size) {
    til_I64 til_I64_i = 0;
    til_U8 til_U8_byte1;
    til_U8 til_U8_byte2;
    til_I64 til_I64_b1;
    til_I64 til_I64_b2;
    til_I64 _tmp_memcmp_0 = 0;
    if (til_I64_lt(&_tmp_memcmp_0, til_I64_size).data) {
        while (til_I64_lt(&til_I64_i, til_I64_size).data) {
            til_U8_byte1 = 0;
            til_U8_byte2 = 0;
            til_I64 _tmp_memcmp_1 = (til_I64)&til_U8_byte1;
            til_I64 _tmp_memcmp_2 = til_I64_add(til_I64_ptr1, &til_I64_i);
            til_I64 _tmp_memcmp_3 = 1;
            til_memcpy(&_tmp_memcmp_1, &_tmp_memcmp_2, &_tmp_memcmp_3);
            til_I64 _tmp_memcmp_4 = (til_I64)&til_U8_byte2;
            til_I64 _tmp_memcmp_5 = til_I64_add(til_I64_ptr2, &til_I64_i);
            til_I64 _tmp_memcmp_6 = 1;
            til_memcpy(&_tmp_memcmp_4, &_tmp_memcmp_5, &_tmp_memcmp_6);
            til_I64_b1 = til_U8_to_i64(&til_U8_byte1);
            til_I64_b2 = til_U8_to_i64(&til_U8_byte2);
            if (til_I64_lt(&til_I64_b1, &til_I64_b2).data) {
                til_I64 _tmp_memcmp_7 = 0;
                til_I64 _tmp_memcmp_8 = 1;
                return til_I64_sub(&_tmp_memcmp_7, &_tmp_memcmp_8);
            } else {
                if (til_I64_gt(&til_I64_b1, &til_I64_b2).data) {
                    return 1;
                }
            }
            til_I64_inc(&til_I64_i);
        }
    } else {
        while (til_I64_gt(&til_I64_i, til_I64_size).data) {
            til_U8_byte1 = 0;
            til_U8_byte2 = 0;
            til_I64 _tmp_memcmp_9 = (til_I64)&til_U8_byte1;
            til_I64 _tmp_memcmp_10 = til_I64_add(til_I64_ptr1, &til_I64_i);
            til_I64 _tmp_memcmp_11 = 1;
            til_memcpy(&_tmp_memcmp_9, &_tmp_memcmp_10, &_tmp_memcmp_11);
            til_I64 _tmp_memcmp_12 = (til_I64)&til_U8_byte2;
            til_I64 _tmp_memcmp_13 = til_I64_add(til_I64_ptr2, &til_I64_i);
            til_I64 _tmp_memcmp_14 = 1;
            til_memcpy(&_tmp_memcmp_12, &_tmp_memcmp_13, &_tmp_memcmp_14);
            til_I64_b1 = til_U8_to_i64(&til_U8_byte1);
            til_I64_b2 = til_U8_to_i64(&til_U8_byte2);
            if (til_I64_lt(&til_I64_b1, &til_I64_b2).data) {
                til_I64 _tmp_memcmp_15 = 0;
                til_I64 _tmp_memcmp_16 = 1;
                return til_I64_sub(&_tmp_memcmp_15, &_tmp_memcmp_16);
            } else {
                if (til_I64_gt(&til_I64_b1, &til_I64_b2).data) {
                    return 1;
                }
            }
            til_I64_dec(&til_I64_i);
        }
    }
    return 0;
    return (til_I64){};
}

til_Bool til_not(const til_Bool* til_Bool_b) {
    if ((*til_Bool_b).data) {
        return false;
    }
    return true;
    return (til_Bool){};
}

void til_panic(const til_Str* til_Str_loc_str, const til_Str* til_Str_msg, til_Array* til_Array_extra_msgs) {
    til_single_print(til_Str_loc_str);
    til_single_print(til_Str_msg);
    til_I64 _for_i_panic_0 = 0;
    til_Ptr _ref_forin_panic_0;
    til_Str til_Str_extra_msg;
    while (1) {
        til_I64 _tmp_panic_0 = til_Array_len(til_Array_extra_msgs);
        if (!(til_I64_lt(&_for_i_panic_0, &_tmp_panic_0).data)) break;
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp_panic_1 = {};
        til_IndexOutOfBoundsError _err0__tmp_panic_2 = {};
        int __attribute__((unused)) _status__tmp_panic_2 = til_Array_get(&_ref_forin_panic_0, &_err0__tmp_panic_2, til_Array_extra_msgs, &_for_i_panic_0);
        if (_status__tmp_panic_2 == 1) { _thrown_IndexOutOfBoundsError__tmp_panic_1 = _err0__tmp_panic_2; goto _catch_IndexOutOfBoundsError__tmp_panic_1; }
        if (0) { _catch_IndexOutOfBoundsError__tmp_panic_1:;
            til_IndexOutOfBoundsError _err_forin_0 = _thrown_IndexOutOfBoundsError__tmp_panic_1;
            til_Array _tmp_panic_3;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_panic_4;
            til_Type _tmp_panic_5 = "Str";
            til_I64 _tmp_panic_6 = 0;
            _tmp_panic_3 = til_Array_new(_tmp_panic_5, &_tmp_panic_6);
            int __attribute__((unused)) _arr_status__tmp_panic_4;
            til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/exit.til:13:5:", 1, 0, 0, 0}), 23, 0}), &_err_forin_0.msg, &_tmp_panic_3);
            til_Array_delete(&_tmp_panic_3);
        }
        til_Str* til_Str_extra_msg;
        til_Str_extra_msg = (til_Str*)_ref_forin_panic_0.data;
        til_single_print(til_Str_extra_msg);
        til_I64 _tmp_panic_7 = 1;
        _for_i_panic_0 = til_I64_add(&_for_i_panic_0, &_tmp_panic_7);
    }
    til_single_print(&((til_Str){((til_Ptr){(til_I64)"\n", 1, 0, 0, 0}), 1, 0}));
    til_print_flush();
    til_I64 _tmp_panic_8 = 1;
    til_exit(&_tmp_panic_8);
}

void til_assertm(const til_Str* til_Str_loc_str, const til_Bool* til_Bool_cond, const til_Str* til_Str_msg) {
    if (til_not(til_Bool_cond).data) {
        til_Str _tmp_assertm_0;
        til_Array _tmp_assertm_1;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_assertm_2;
        til_Str _tmp_assertm_3 = (*til_Str_msg);
        til_Type _tmp_assertm_4 = "Str";
        til_I64 _tmp_assertm_5 = 1;
        _tmp_assertm_1 = til_Array_new(_tmp_assertm_4, &_tmp_assertm_5);
        int __attribute__((unused)) _arr_status__tmp_assertm_2;
        til_I64 _tmp_assertm_6 = 0;
        _arr_status__tmp_assertm_2 = til_Array_set(&_err_idx__tmp_assertm_2, &_tmp_assertm_1, &_tmp_assertm_6, (til_Dynamic*)&_tmp_assertm_3);
        _tmp_assertm_0 = til_format(&((til_Str){((til_Ptr){(til_I64)"assert failed: ", 1, 0, 0, 0}), 15, 0}), &_tmp_assertm_1);
        til_Array_delete(&_tmp_assertm_1);
        til_Array _tmp_assertm_7;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_assertm_8;
        til_Type _tmp_assertm_9 = "Str";
        til_I64 _tmp_assertm_10 = 0;
        _tmp_assertm_7 = til_Array_new(_tmp_assertm_9, &_tmp_assertm_10);
        int __attribute__((unused)) _arr_status__tmp_assertm_8;
        til_panic(til_Str_loc_str, &_tmp_assertm_0, &_tmp_assertm_7);
        til_Array_delete(&_tmp_assertm_7);
    }
}

void til_println(til_Array* til_Array_args) {
    til_I64 _for_i_println_0 = 0;
    til_Ptr _ref_forin_println_0;
    til_Str til_Str_print_arg;
    while (1) {
        til_I64 _tmp_println_0 = til_Array_len(til_Array_args);
        if (!(til_I64_lt(&_for_i_println_0, &_tmp_println_0).data)) break;
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp_println_1 = {};
        til_IndexOutOfBoundsError _err0__tmp_println_2 = {};
        int __attribute__((unused)) _status__tmp_println_2 = til_Array_get(&_ref_forin_println_0, &_err0__tmp_println_2, til_Array_args, &_for_i_println_0);
        if (_status__tmp_println_2 == 1) { _thrown_IndexOutOfBoundsError__tmp_println_1 = _err0__tmp_println_2; goto _catch_IndexOutOfBoundsError__tmp_println_1; }
        if (0) { _catch_IndexOutOfBoundsError__tmp_println_1:;
            til_IndexOutOfBoundsError _err_forin_0 = _thrown_IndexOutOfBoundsError__tmp_println_1;
            til_Array _tmp_println_3;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_println_4;
            til_Type _tmp_println_5 = "Str";
            til_I64 _tmp_println_6 = 0;
            _tmp_println_3 = til_Array_new(_tmp_println_5, &_tmp_println_6);
            int __attribute__((unused)) _arr_status__tmp_println_4;
            til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/print.til:16:5:", 1, 0, 0, 0}), 24, 0}), &_err_forin_0.msg, &_tmp_println_3);
            til_Array_delete(&_tmp_println_3);
        }
        til_Str* til_Str_print_arg;
        til_Str_print_arg = (til_Str*)_ref_forin_println_0.data;
        til_single_print(til_Str_print_arg);
        til_I64 _tmp_println_7 = 1;
        _for_i_println_0 = til_I64_add(&_for_i_println_0, &_tmp_println_7);
    }
    til_single_print(&((til_Str){((til_Ptr){(til_I64)"\n", 1, 0, 0, 0}), 1, 0}));
    til_print_flush();
}

int til_get_substr(til_Str* _ret, til_IndexOutOfBoundsError* _err1, const til_Str* til_Str_s, const til_I64* til_I64_start, const til_I64* til_I64_end) {
    til_I64 _tmp_get_substr_0 = 0;
    if (til_I64_lt(til_I64_start, &_tmp_get_substr_0).data) {
        til_Str _tmp_get_substr_1;
        til_Array _tmp_get_substr_2;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_get_substr_3;
        til_Str _tmp_get_substr_4 = ((til_Str){((til_Ptr){(til_I64)"get_substr: start index ", 1, 0, 0, 0}), 24, 0});
        til_Str _tmp_get_substr_5 = til_I64_to_str(til_I64_start);
        til_Str _tmp_get_substr_6 = ((til_Str){((til_Ptr){(til_I64)" cannot be negative", 1, 0, 0, 0}), 19, 0});
        til_Type _tmp_get_substr_7 = "Str";
        til_I64 _tmp_get_substr_8 = 3;
        _tmp_get_substr_2 = til_Array_new(_tmp_get_substr_7, &_tmp_get_substr_8);
        int __attribute__((unused)) _arr_status__tmp_get_substr_3;
        til_I64 _tmp_get_substr_9 = 0;
        _arr_status__tmp_get_substr_3 = til_Array_set(&_err_idx__tmp_get_substr_3, &_tmp_get_substr_2, &_tmp_get_substr_9, (til_Dynamic*)&_tmp_get_substr_4);
        til_I64 _tmp_get_substr_10 = 1;
        _arr_status__tmp_get_substr_3 = til_Array_set(&_err_idx__tmp_get_substr_3, &_tmp_get_substr_2, &_tmp_get_substr_10, (til_Dynamic*)&_tmp_get_substr_5);
        til_I64 _tmp_get_substr_11 = 2;
        _arr_status__tmp_get_substr_3 = til_Array_set(&_err_idx__tmp_get_substr_3, &_tmp_get_substr_2, &_tmp_get_substr_11, (til_Dynamic*)&_tmp_get_substr_6);
        _tmp_get_substr_1 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/str.til:559:48:", 1, 0, 0, 0}), 24, 0}), &_tmp_get_substr_2);
        til_Array_delete(&_tmp_get_substr_2);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_get_substr_1};
        return 1;
    }
    til_I64 _tmp_get_substr_12 = 0;
    if (til_I64_lt(til_I64_end, &_tmp_get_substr_12).data) {
        til_Str _tmp_get_substr_13;
        til_Array _tmp_get_substr_14;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_get_substr_15;
        til_Str _tmp_get_substr_16 = ((til_Str){((til_Ptr){(til_I64)"get_substr: end index ", 1, 0, 0, 0}), 22, 0});
        til_Str _tmp_get_substr_17 = til_I64_to_str(til_I64_end);
        til_Str _tmp_get_substr_18 = ((til_Str){((til_Ptr){(til_I64)" cannot be negative", 1, 0, 0, 0}), 19, 0});
        til_Type _tmp_get_substr_19 = "Str";
        til_I64 _tmp_get_substr_20 = 3;
        _tmp_get_substr_14 = til_Array_new(_tmp_get_substr_19, &_tmp_get_substr_20);
        int __attribute__((unused)) _arr_status__tmp_get_substr_15;
        til_I64 _tmp_get_substr_21 = 0;
        _arr_status__tmp_get_substr_15 = til_Array_set(&_err_idx__tmp_get_substr_15, &_tmp_get_substr_14, &_tmp_get_substr_21, (til_Dynamic*)&_tmp_get_substr_16);
        til_I64 _tmp_get_substr_22 = 1;
        _arr_status__tmp_get_substr_15 = til_Array_set(&_err_idx__tmp_get_substr_15, &_tmp_get_substr_14, &_tmp_get_substr_22, (til_Dynamic*)&_tmp_get_substr_17);
        til_I64 _tmp_get_substr_23 = 2;
        _arr_status__tmp_get_substr_15 = til_Array_set(&_err_idx__tmp_get_substr_15, &_tmp_get_substr_14, &_tmp_get_substr_23, (til_Dynamic*)&_tmp_get_substr_18);
        _tmp_get_substr_13 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/str.til:562:48:", 1, 0, 0, 0}), 24, 0}), &_tmp_get_substr_14);
        til_Array_delete(&_tmp_get_substr_14);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_get_substr_13};
        return 1;
    }
    if (til_I64_gt(til_I64_start, til_I64_end).data) {
        til_Str _tmp_get_substr_24;
        til_Array _tmp_get_substr_25;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_get_substr_26;
        til_Str _tmp_get_substr_27 = ((til_Str){((til_Ptr){(til_I64)"get_substr: start index ", 1, 0, 0, 0}), 24, 0});
        til_Str _tmp_get_substr_28 = til_I64_to_str(til_I64_start);
        til_Str _tmp_get_substr_29 = ((til_Str){((til_Ptr){(til_I64)" is greater than end index ", 1, 0, 0, 0}), 27, 0});
        til_Str _tmp_get_substr_30 = til_I64_to_str(til_I64_end);
        til_Type _tmp_get_substr_31 = "Str";
        til_I64 _tmp_get_substr_32 = 4;
        _tmp_get_substr_25 = til_Array_new(_tmp_get_substr_31, &_tmp_get_substr_32);
        int __attribute__((unused)) _arr_status__tmp_get_substr_26;
        til_I64 _tmp_get_substr_33 = 0;
        _arr_status__tmp_get_substr_26 = til_Array_set(&_err_idx__tmp_get_substr_26, &_tmp_get_substr_25, &_tmp_get_substr_33, (til_Dynamic*)&_tmp_get_substr_27);
        til_I64 _tmp_get_substr_34 = 1;
        _arr_status__tmp_get_substr_26 = til_Array_set(&_err_idx__tmp_get_substr_26, &_tmp_get_substr_25, &_tmp_get_substr_34, (til_Dynamic*)&_tmp_get_substr_28);
        til_I64 _tmp_get_substr_35 = 2;
        _arr_status__tmp_get_substr_26 = til_Array_set(&_err_idx__tmp_get_substr_26, &_tmp_get_substr_25, &_tmp_get_substr_35, (til_Dynamic*)&_tmp_get_substr_29);
        til_I64 _tmp_get_substr_36 = 3;
        _arr_status__tmp_get_substr_26 = til_Array_set(&_err_idx__tmp_get_substr_26, &_tmp_get_substr_25, &_tmp_get_substr_36, (til_Dynamic*)&_tmp_get_substr_30);
        _tmp_get_substr_24 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/str.til:565:48:", 1, 0, 0, 0}), 24, 0}), &_tmp_get_substr_25);
        til_Array_delete(&_tmp_get_substr_25);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_get_substr_24};
        return 1;
    }
    til_I64 _tmp_get_substr_37 = til_Str_len(til_Str_s);
    if (til_I64_gt(til_I64_end, &_tmp_get_substr_37).data) {
        til_I64 _tmp_get_substr_38 = til_Str_len(til_Str_s);
        til_Str _tmp_get_substr_39;
        til_Array _tmp_get_substr_40;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_get_substr_41;
        til_Str _tmp_get_substr_42 = ((til_Str){((til_Ptr){(til_I64)"get_substr: end index ", 1, 0, 0, 0}), 22, 0});
        til_Str _tmp_get_substr_43 = til_I64_to_str(til_I64_end);
        til_Str _tmp_get_substr_44 = ((til_Str){((til_Ptr){(til_I64)" is greater than string length ", 1, 0, 0, 0}), 31, 0});
        til_Str _tmp_get_substr_45 = til_I64_to_str(&_tmp_get_substr_38);
        til_Type _tmp_get_substr_46 = "Str";
        til_I64 _tmp_get_substr_47 = 4;
        _tmp_get_substr_40 = til_Array_new(_tmp_get_substr_46, &_tmp_get_substr_47);
        int __attribute__((unused)) _arr_status__tmp_get_substr_41;
        til_I64 _tmp_get_substr_48 = 0;
        _arr_status__tmp_get_substr_41 = til_Array_set(&_err_idx__tmp_get_substr_41, &_tmp_get_substr_40, &_tmp_get_substr_48, (til_Dynamic*)&_tmp_get_substr_42);
        til_I64 _tmp_get_substr_49 = 1;
        _arr_status__tmp_get_substr_41 = til_Array_set(&_err_idx__tmp_get_substr_41, &_tmp_get_substr_40, &_tmp_get_substr_49, (til_Dynamic*)&_tmp_get_substr_43);
        til_I64 _tmp_get_substr_50 = 2;
        _arr_status__tmp_get_substr_41 = til_Array_set(&_err_idx__tmp_get_substr_41, &_tmp_get_substr_40, &_tmp_get_substr_50, (til_Dynamic*)&_tmp_get_substr_44);
        til_I64 _tmp_get_substr_51 = 3;
        _arr_status__tmp_get_substr_41 = til_Array_set(&_err_idx__tmp_get_substr_41, &_tmp_get_substr_40, &_tmp_get_substr_51, (til_Dynamic*)&_tmp_get_substr_45);
        _tmp_get_substr_39 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/str.til:568:48:", 1, 0, 0, 0}), 24, 0}), &_tmp_get_substr_40);
        til_Array_delete(&_tmp_get_substr_40);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_get_substr_39};
        return 1;
    }
    if (til_I64_eq(til_I64_start, til_I64_end).data) {
        *_ret = ((til_Str){((til_Ptr){(til_I64)"", 1, 0, 0, 0}), 0, 0});
        return 0;
    }
    til_Ptr _tmp_get_substr_52 = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    til_Str til_Str_substr = {.c_string = _tmp_get_substr_52, ._len = 0, .cap = 0};
    til_Str_substr._len = til_I64_sub(til_I64_end, til_I64_start);
    til_I64 _tmp_get_substr_53 = 1;
    til_Str_substr.cap = til_I64_add(&til_Str_substr._len, &_tmp_get_substr_53);
    til_Str_substr.c_string = til_Ptr_new_by_size(&til_Str_substr.cap);
    til_Str_substr.c_string.is_borrowed = 0;
    til_I64 _tmp_get_substr_54 = til_Ptr_offset(&til_Str_s->c_string, til_I64_start).data;
    til_memcpy(&til_Str_substr.c_string.data, &_tmp_get_substr_54, &til_Str_substr._len);
    til_U8 til_U8_zero = 0;
    til_I64 _tmp_get_substr_55 = til_Ptr_offset(&til_Str_substr.c_string, &til_Str_substr._len).data;
    til_I64 _tmp_get_substr_56 = 1;
    til_memset(&_tmp_get_substr_55, &til_U8_zero, &_tmp_get_substr_56);
    *_ret = til_Str_substr;
    return 0;
    return 0;
}

til_Str til_concat(const til_Str* til_Str_a, const til_Str* til_Str_b) {
    til_Ptr _tmp_concat_0 = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    til_Str til_Str_result = {.c_string = _tmp_concat_0, ._len = 0, .cap = 0};
    til_Str_result._len = til_I64_add(&til_Str_a->_len, &til_Str_b->_len);
    if (til_I64_lt(&til_Str_result._len, &til_Str_a->_len).data) {
        til_Array _tmp_concat_1;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_concat_2;
        til_Type _tmp_concat_3 = "Str";
        til_I64 _tmp_concat_4 = 0;
        _tmp_concat_1 = til_Array_new(_tmp_concat_3, &_tmp_concat_4);
        int __attribute__((unused)) _arr_status__tmp_concat_2;
        til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/str.til:665:15:", 1, 0, 0, 0}), 24, 0}), &((til_Str){((til_Ptr){(til_I64)"concat: integer overflow", 1, 0, 0, 0}), 24, 0}), &_tmp_concat_1);
        til_Array_delete(&_tmp_concat_1);
    }
    til_I64 _tmp_concat_5 = 1;
    til_Str_result.cap = til_I64_add(&til_Str_result._len, &_tmp_concat_5);
    til_Str_result.c_string = til_Ptr_new_by_size(&til_Str_result.cap);
    til_Str_result.c_string.is_borrowed = 0;
    til_memcpy(&til_Str_result.c_string.data, &til_Str_a->c_string.data, &til_Str_a->_len);
    til_I64 _tmp_concat_6 = til_Ptr_offset(&til_Str_result.c_string, &til_Str_a->_len).data;
    til_memcpy(&_tmp_concat_6, &til_Str_b->c_string.data, &til_Str_b->_len);
    til_U8 til_U8_zero = 0;
    til_I64 _tmp_concat_7 = til_Ptr_offset(&til_Str_result.c_string, &til_Str_result._len).data;
    til_I64 _tmp_concat_8 = 1;
    til_memset(&_tmp_concat_7, &til_U8_zero, &_tmp_concat_8);
    return til_Str_result;
    return (til_Str){};
}

til_Str til_format(const til_Str* til_Str_prefix, til_Array* til_Array_args) {
    til_Ptr _tmp_format_0 = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    til_Str til_Str_result = {.c_string = _tmp_format_0, ._len = 0, .cap = 0};
    til_Str_result._len = til_Str_prefix->_len;
    til_I64 _for_i_format_0 = 0;
    til_Ptr _ref_forin_format_0;
    til_Str til_Str_arg;
    while (1) {
        til_I64 _tmp_format_1 = til_Array_len(til_Array_args);
        if (!(til_I64_lt(&_for_i_format_0, &_tmp_format_1).data)) break;
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp_format_2 = {};
        til_IndexOutOfBoundsError _err0__tmp_format_3 = {};
        int __attribute__((unused)) _status__tmp_format_3 = til_Array_get(&_ref_forin_format_0, &_err0__tmp_format_3, til_Array_args, &_for_i_format_0);
        if (_status__tmp_format_3 == 1) { _thrown_IndexOutOfBoundsError__tmp_format_2 = _err0__tmp_format_3; goto _catch_IndexOutOfBoundsError__tmp_format_2; }
        if (0) { _catch_IndexOutOfBoundsError__tmp_format_2:;
            til_IndexOutOfBoundsError _err_forin_0 = _thrown_IndexOutOfBoundsError__tmp_format_2;
            til_Array _tmp_format_4;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_format_5;
            til_Type _tmp_format_6 = "Str";
            til_I64 _tmp_format_7 = 0;
            _tmp_format_4 = til_Array_new(_tmp_format_6, &_tmp_format_7);
            int __attribute__((unused)) _arr_status__tmp_format_5;
            til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/str.til:686:5:", 1, 0, 0, 0}), 23, 0}), &_err_forin_0.msg, &_tmp_format_4);
            til_Array_delete(&_tmp_format_4);
        }
        til_Str* til_Str_arg;
        til_Str_arg = (til_Str*)_ref_forin_format_0.data;
        til_Str_result._len = til_I64_add(&til_Str_result._len, &til_Str_arg->_len);
        if (til_I64_lt(&til_Str_result._len, &til_Str_arg->_len).data) {
            til_Array _tmp_format_8;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_format_9;
            til_Type _tmp_format_10 = "Str";
            til_I64 _tmp_format_11 = 0;
            _tmp_format_8 = til_Array_new(_tmp_format_10, &_tmp_format_11);
            int __attribute__((unused)) _arr_status__tmp_format_9;
            til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/str.til:689:19:", 1, 0, 0, 0}), 24, 0}), &((til_Str){((til_Ptr){(til_I64)"format: integer overflow while summing cap", 1, 0, 0, 0}), 42, 0}), &_tmp_format_8);
            til_Array_delete(&_tmp_format_8);
        }
        til_I64 _tmp_format_12 = 1;
        _for_i_format_0 = til_I64_add(&_for_i_format_0, &_tmp_format_12);
    }
    til_I64 _tmp_format_13 = 1;
    til_Str_result.cap = til_I64_add(&til_Str_result._len, &_tmp_format_13);
    til_Str_result.c_string = til_Ptr_new_by_size(&til_Str_result.cap);
    til_Str_result.c_string.is_borrowed = 0;
    til_I64 til_I64_fmt_offset = 0;
    til_memcpy(&til_Str_result.c_string.data, &til_Str_prefix->c_string.data, &til_Str_prefix->_len);
    til_I64_fmt_offset = til_Str_prefix->_len;
    til_I64 _for_i_format_1 = 0;
    til_Ptr _ref_forin_format_1;
    til_Str til_Str_s;
    while (1) {
        til_I64 _tmp_format_14 = til_Array_len(til_Array_args);
        if (!(til_I64_lt(&_for_i_format_1, &_tmp_format_14).data)) break;
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp_format_15 = {};
        til_IndexOutOfBoundsError _err0__tmp_format_16 = {};
        int __attribute__((unused)) _status__tmp_format_16 = til_Array_get(&_ref_forin_format_1, &_err0__tmp_format_16, til_Array_args, &_for_i_format_1);
        if (_status__tmp_format_16 == 1) { _thrown_IndexOutOfBoundsError__tmp_format_15 = _err0__tmp_format_16; goto _catch_IndexOutOfBoundsError__tmp_format_15; }
        if (0) { _catch_IndexOutOfBoundsError__tmp_format_15:;
            til_IndexOutOfBoundsError _err_forin_1 = _thrown_IndexOutOfBoundsError__tmp_format_15;
            til_Array _tmp_format_17;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_format_18;
            til_Type _tmp_format_19 = "Str";
            til_I64 _tmp_format_20 = 0;
            _tmp_format_17 = til_Array_new(_tmp_format_19, &_tmp_format_20);
            int __attribute__((unused)) _arr_status__tmp_format_18;
            til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/str.til:701:5:", 1, 0, 0, 0}), 23, 0}), &_err_forin_1.msg, &_tmp_format_17);
            til_Array_delete(&_tmp_format_17);
        }
        til_Str* til_Str_s;
        til_Str_s = (til_Str*)_ref_forin_format_1.data;
        til_I64 _tmp_format_21 = til_Ptr_offset(&til_Str_result.c_string, &til_I64_fmt_offset).data;
        til_memcpy(&_tmp_format_21, &til_Str_s->c_string.data, &til_Str_s->_len);
        til_I64_fmt_offset = til_I64_add(&til_I64_fmt_offset, &til_Str_s->_len);
        til_I64 _tmp_format_22 = 1;
        _for_i_format_1 = til_I64_add(&_for_i_format_1, &_tmp_format_22);
    }
    til_U8 til_U8_zero = 0;
    til_I64 _tmp_format_23 = til_Ptr_offset(&til_Str_result.c_string, &til_Str_result._len).data;
    til_I64 _tmp_format_24 = 1;
    til_memset(&_tmp_format_23, &til_U8_zero, &_tmp_format_24);
    return til_Str_result;
    return (til_Str){};
}

void til_test(const til_Str* til_Str_loc_str, const til_Bool* til_Bool_cond, const til_Str* til_Str_msg) {
    til_assertm(til_Str_loc_str, til_Bool_cond, til_Str_msg);
}

void til_assert_eq(const til_Str* til_Str_loc_str, const til_I64* til_I64_a, const til_I64* til_I64_b) {
    til_Bool _tmp_assert_eq_0 = til_I64_eq(til_I64_a, til_I64_b);
    if (til_not(&_tmp_assert_eq_0).data) {
        til_Array _tmp_assert_eq_1;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_assert_eq_2;
        til_Str _tmp_assert_eq_3 = (*til_Str_loc_str);
        til_Str _tmp_assert_eq_4 = ((til_Str){((til_Ptr){(til_I64)"assert_eq failed: expected '", 1, 0, 0, 0}), 28, 0});
        til_Str _tmp_assert_eq_5 = til_I64_to_str(til_I64_a);
        til_Str _tmp_assert_eq_6 = ((til_Str){((til_Ptr){(til_I64)"', found '", 1, 0, 0, 0}), 10, 0});
        til_Str _tmp_assert_eq_7 = til_I64_to_str(til_I64_b);
        til_Str _tmp_assert_eq_8 = ((til_Str){((til_Ptr){(til_I64)"'", 1, 0, 0, 0}), 1, 0});
        til_Type _tmp_assert_eq_9 = "Str";
        til_I64 _tmp_assert_eq_10 = 6;
        _tmp_assert_eq_1 = til_Array_new(_tmp_assert_eq_9, &_tmp_assert_eq_10);
        int __attribute__((unused)) _arr_status__tmp_assert_eq_2;
        til_I64 _tmp_assert_eq_11 = 0;
        _arr_status__tmp_assert_eq_2 = til_Array_set(&_err_idx__tmp_assert_eq_2, &_tmp_assert_eq_1, &_tmp_assert_eq_11, (til_Dynamic*)&_tmp_assert_eq_3);
        til_I64 _tmp_assert_eq_12 = 1;
        _arr_status__tmp_assert_eq_2 = til_Array_set(&_err_idx__tmp_assert_eq_2, &_tmp_assert_eq_1, &_tmp_assert_eq_12, (til_Dynamic*)&_tmp_assert_eq_4);
        til_I64 _tmp_assert_eq_13 = 2;
        _arr_status__tmp_assert_eq_2 = til_Array_set(&_err_idx__tmp_assert_eq_2, &_tmp_assert_eq_1, &_tmp_assert_eq_13, (til_Dynamic*)&_tmp_assert_eq_5);
        til_I64 _tmp_assert_eq_14 = 3;
        _arr_status__tmp_assert_eq_2 = til_Array_set(&_err_idx__tmp_assert_eq_2, &_tmp_assert_eq_1, &_tmp_assert_eq_14, (til_Dynamic*)&_tmp_assert_eq_6);
        til_I64 _tmp_assert_eq_15 = 4;
        _arr_status__tmp_assert_eq_2 = til_Array_set(&_err_idx__tmp_assert_eq_2, &_tmp_assert_eq_1, &_tmp_assert_eq_15, (til_Dynamic*)&_tmp_assert_eq_7);
        til_I64 _tmp_assert_eq_16 = 5;
        _arr_status__tmp_assert_eq_2 = til_Array_set(&_err_idx__tmp_assert_eq_2, &_tmp_assert_eq_1, &_tmp_assert_eq_16, (til_Dynamic*)&_tmp_assert_eq_8);
        til_println(&_tmp_assert_eq_1);
        til_Array_delete(&_tmp_assert_eq_1);
        til_I64 _tmp_assert_eq_17 = 1;
        til_exit(&_tmp_assert_eq_17);
    }
}

void til_test_simple_add(void) {
    til_I64 _tmp_test_simple_add_0 = 1;
    til_I64 _tmp_test_simple_add_1 = 2;
    til_I64 til_I64_result = til_I64_add(&_tmp_test_simple_add_0, &_tmp_test_simple_add_1);
    til_I64 _tmp_test_simple_add_2 = 3;
    til_Bool _tmp_test_simple_add_3 = til_I64_eq(&til_I64_result, &_tmp_test_simple_add_2);
    til_test(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:8:10:", 1, 0, 0, 0}), 28, 0}), &_tmp_test_simple_add_3, &((til_Str){((til_Ptr){(til_I64)"add(1, 2) should be 3", 1, 0, 0, 0}), 21, 0}));
}

void til_test_nested_arithmetic(void) {
    til_I64 _tmp_test_nested_arithmetic_0 = 1;
    til_I64 _tmp_test_nested_arithmetic_1 = 2;
    til_I64 _tmp_test_nested_arithmetic_2 = til_I64_add(&_tmp_test_nested_arithmetic_0, &_tmp_test_nested_arithmetic_1);
    til_I64 _tmp_test_nested_arithmetic_3 = 10;
    til_I64 _tmp_test_nested_arithmetic_4 = 5;
    til_I64 _tmp_test_nested_arithmetic_5 = til_I64_sub(&_tmp_test_nested_arithmetic_3, &_tmp_test_nested_arithmetic_4);
    til_I64 til_I64_result = til_I64_mul(&_tmp_test_nested_arithmetic_2, &_tmp_test_nested_arithmetic_5);
    til_I64 _tmp_test_nested_arithmetic_6 = 15;
    til_Bool _tmp_test_nested_arithmetic_7 = til_I64_eq(&til_I64_result, &_tmp_test_nested_arithmetic_6);
    til_test(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:15:10:", 1, 0, 0, 0}), 29, 0}), &_tmp_test_nested_arithmetic_7, &((til_Str){((til_Ptr){(til_I64)"mul(add(1, 2), sub(10, 5)) should be 15", 1, 0, 0, 0}), 39, 0}));
}

void til_test_deeply_nested(void) {
    til_I64 _tmp_test_deeply_nested_0 = 2;
    til_I64 _tmp_test_deeply_nested_1 = 3;
    til_I64 _tmp_test_deeply_nested_2 = til_I64_mul(&_tmp_test_deeply_nested_0, &_tmp_test_deeply_nested_1);
    til_I64 _tmp_test_deeply_nested_3 = 4;
    til_I64 _tmp_test_deeply_nested_4 = 5;
    til_I64 _tmp_test_deeply_nested_5 = til_I64_mul(&_tmp_test_deeply_nested_3, &_tmp_test_deeply_nested_4);
    til_I64 til_I64_result = til_I64_add(&_tmp_test_deeply_nested_2, &_tmp_test_deeply_nested_5);
    til_I64 _tmp_test_deeply_nested_6 = 26;
    til_Bool _tmp_test_deeply_nested_7 = til_I64_eq(&til_I64_result, &_tmp_test_deeply_nested_6);
    til_test(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:22:10:", 1, 0, 0, 0}), 29, 0}), &_tmp_test_deeply_nested_7, &((til_Str){((til_Ptr){(til_I64)"add(mul(2, 3), mul(4, 5)) should be 26", 1, 0, 0, 0}), 38, 0}));
}

void til_test_string_concat(void) {
    til_Str til_Str_result = til_concat(&((til_Str){((til_Ptr){(til_I64)"hello", 1, 0, 0, 0}), 5, 0}), &((til_Str){((til_Ptr){(til_I64)" world", 1, 0, 0, 0}), 6, 0}));
    til_Bool _tmp_test_string_concat_0 = til_Str_eq(&til_Str_result, &((til_Str){((til_Ptr){(til_I64)"hello world", 1, 0, 0, 0}), 11, 0}));
    til_test(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:29:10:", 1, 0, 0, 0}), 29, 0}), &_tmp_test_string_concat_0, &((til_Str){((til_Ptr){(til_I64)"concat is folded at compile time", 1, 0, 0, 0}), 32, 0}));
}

void til_test_fold_variable(void) {
    til_I64 til_I64_x = 5;
    til_I64 _tmp_test_fold_variable_0 = 3;
    til_I64 til_I64_result = til_I64_add(&til_I64_x, &_tmp_test_fold_variable_0);
    til_I64 _tmp_test_fold_variable_1 = 8;
    til_Bool _tmp_test_fold_variable_2 = til_I64_eq(&til_I64_result, &_tmp_test_fold_variable_1);
    til_test(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:38:10:", 1, 0, 0, 0}), 29, 0}), &_tmp_test_fold_variable_2, &((til_Str){((til_Ptr){(til_I64)"add(x, 3) should fold to 8", 1, 0, 0, 0}), 26, 0}));
}

void til_test_loc_folded_correctly(void) {
    til_Str til_Str_location = ((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:44:17:", 1, 0, 0, 0}), 29, 0});
    til_Bool _tmp_test_loc_folded_correctly_0 = til_Str_contains(&til_Str_location, &((til_Str){((til_Ptr){(til_I64)"constfold.til", 1, 0, 0, 0}), 13, 0}));
    til_test(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:45:10:", 1, 0, 0, 0}), 29, 0}), &_tmp_test_loc_folded_correctly_0, &((til_Str){((til_Ptr){(til_I64)"loc() should contain filename", 1, 0, 0, 0}), 29, 0}));
    til_Bool _tmp_test_loc_folded_correctly_1 = til_Str_contains(&til_Str_location, &((til_Str){((til_Ptr){(til_I64)":44:", 1, 0, 0, 0}), 4, 0}));
    til_test(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:46:10:", 1, 0, 0, 0}), 29, 0}), &_tmp_test_loc_folded_correctly_1, &((til_Str){((til_Ptr){(til_I64)"loc() should contain correct line number", 1, 0, 0, 0}), 40, 0}));
}

void til_test_struct_fold_simple(void) {
    til_CfVec2 til_CfVec2_v = til_CfVec2_magic();
    til_I64 _tmp_test_struct_fold_simple_0 = 42;
    til_assert_eq(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:72:15:", 1, 0, 0, 0}), 29, 0}), &_tmp_test_struct_fold_simple_0, &til_CfVec2_v.x);
    til_I64 _tmp_test_struct_fold_simple_1 = 99;
    til_assert_eq(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:73:15:", 1, 0, 0, 0}), 29, 0}), &_tmp_test_struct_fold_simple_1, &til_CfVec2_v.y);
}

void til_test_struct_fold_values(void) {
    til_I64 _tmp_test_struct_fold_values_0 = 10;
    til_I64 _tmp_test_struct_fold_values_1 = 20;
    til_CfVec2 til_CfVec2_p = til_CfVec2_at(&_tmp_test_struct_fold_values_0, &_tmp_test_struct_fold_values_1);
    til_I64 _tmp_test_struct_fold_values_2 = 10;
    til_assert_eq(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:80:15:", 1, 0, 0, 0}), 29, 0}), &_tmp_test_struct_fold_values_2, &til_CfVec2_p.x);
    til_I64 _tmp_test_struct_fold_values_3 = 20;
    til_assert_eq(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:81:15:", 1, 0, 0, 0}), 29, 0}), &_tmp_test_struct_fold_values_3, &til_CfVec2_p.y);
}

void til_test_struct_fold_nested(void) {
    til_CfRect til_CfRect_r = til_CfRect_sample();
    til_I64 _tmp_test_struct_fold_nested_0 = 5;
    til_assert_eq(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:99:15:", 1, 0, 0, 0}), 29, 0}), &_tmp_test_struct_fold_nested_0, &til_CfRect_r.top_left.x);
    til_I64 _tmp_test_struct_fold_nested_1 = 10;
    til_assert_eq(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:100:15:", 1, 0, 0, 0}), 30, 0}), &_tmp_test_struct_fold_nested_1, &til_CfRect_r.top_left.y);
    til_I64 _tmp_test_struct_fold_nested_2 = 100;
    til_assert_eq(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:101:15:", 1, 0, 0, 0}), 30, 0}), &_tmp_test_struct_fold_nested_2, &til_CfRect_r.bottom_right.x);
    til_I64 _tmp_test_struct_fold_nested_3 = 200;
    til_assert_eq(&((til_Str){((til_Ptr){(til_I64)"src/test/constfold.til:102:15:", 1, 0, 0, 0}), 30, 0}), &_tmp_test_struct_fold_nested_3, &til_CfRect_r.bottom_right.y);
}

til_FunctionType til_FunctionType_clone(const til_FunctionType* til_FunctionType_self) {
    return (*til_FunctionType_self);
    return (til_FunctionType){};
}

void til_FunctionType_delete(til_FunctionType* _self) {
    (void)_self;
}

til_Literal til_Literal_clone(const til_Literal* til_Literal_self) {
    return (*til_Literal_self);
    return (til_Literal){};
}

void til_Literal_delete(til_Literal* _self) {
    (void)_self;
}

til_NodeType til_NodeType_clone(const til_NodeType* til_NodeType_self) {
    return (*til_NodeType_self);
    return (til_NodeType){};
}

void til_NodeType_delete(til_NodeType* _self) {
    (void)_self;
}

til_TTypeDef til_TTypeDef_clone(const til_TTypeDef* til_TTypeDef_self) {
    return (*til_TTypeDef_self);
    return (til_TTypeDef){};
}

void til_TTypeDef_delete(til_TTypeDef* _self) {
    (void)_self;
}

til_ValueType til_ValueType_clone(const til_ValueType* til_ValueType_self) {
    return (*til_ValueType_self);
    return (til_ValueType){};
}

void til_ValueType_delete(til_ValueType* _self) {
    (void)_self;
}

void til_IndexOutOfBoundsError_delete(til_IndexOutOfBoundsError* til_IndexOutOfBoundsError_self) {
    til_Str_delete(&til_IndexOutOfBoundsError_self->msg);
}

til_IndexOutOfBoundsError til_IndexOutOfBoundsError_clone(const til_IndexOutOfBoundsError* til_IndexOutOfBoundsError_self) {
    return (til_IndexOutOfBoundsError){.msg = til_Str_clone(&til_IndexOutOfBoundsError_self->msg)};
    return (til_IndexOutOfBoundsError){};
}

void til_BadAlloc_delete(til_BadAlloc* _self) {
    (void)_self;
}

til_BadAlloc til_BadAlloc_clone(const til_BadAlloc* _self) {
    (void)_self;
    return (til_BadAlloc){};
    return (til_BadAlloc){};
}

til_Ptr til_Ptr_new_by_size(const til_I64* til_I64_size) {
    til_Ptr til_Ptr_p = {};
    til_BadAlloc _thrown_BadAlloc__tmp_til_Ptr_new_by_size_0 = {};
    til_I64 _tmp_til_Ptr_new_by_size_1 = 0;
    if (til_I64_lteq(til_I64_size, &_tmp_til_Ptr_new_by_size_1).data) {
        til_Array _tmp_til_Ptr_new_by_size_2;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Ptr_new_by_size_3;
        til_Type _tmp_til_Ptr_new_by_size_4 = "Str";
        til_I64 _tmp_til_Ptr_new_by_size_5 = 0;
        _tmp_til_Ptr_new_by_size_2 = til_Array_new(_tmp_til_Ptr_new_by_size_4, &_tmp_til_Ptr_new_by_size_5);
        int __attribute__((unused)) _arr_status__tmp_til_Ptr_new_by_size_3;
        til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/ptr.til:17:19:", 1, 0, 0, 0}), 23, 0}), &((til_Str){((til_Ptr){(til_I64)"Ptr.new_by_size: invalid size", 1, 0, 0, 0}), 29, 0}), &_tmp_til_Ptr_new_by_size_2);
        til_Array_delete(&_tmp_til_Ptr_new_by_size_2);
    }
    til_Ptr_p = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    int __attribute__((unused)) _status__tmp_til_Ptr_new_by_size_6 = til_malloc(&(til_Ptr_p.data), til_I64_size);
    if (_status__tmp_til_Ptr_new_by_size_6 == 1) { goto _catch_BadAlloc__tmp_til_Ptr_new_by_size_0; }
    if (0) { _catch_BadAlloc__tmp_til_Ptr_new_by_size_0:;
        til_BadAlloc til_BadAlloc_err = _thrown_BadAlloc__tmp_til_Ptr_new_by_size_0;
        til_Array _tmp_til_Ptr_new_by_size_7;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Ptr_new_by_size_8;
        til_Type _tmp_til_Ptr_new_by_size_9 = "Str";
        til_I64 _tmp_til_Ptr_new_by_size_10 = 0;
        _tmp_til_Ptr_new_by_size_7 = til_Array_new(_tmp_til_Ptr_new_by_size_9, &_tmp_til_Ptr_new_by_size_10);
        int __attribute__((unused)) _arr_status__tmp_til_Ptr_new_by_size_8;
        til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/ptr.til:21:39:", 1, 0, 0, 0}), 23, 0}), &((til_Str){((til_Ptr){(til_I64)"Ptr.new_by_size: malloc failed", 1, 0, 0, 0}), 30, 0}), &_tmp_til_Ptr_new_by_size_7);
        til_Array_delete(&_tmp_til_Ptr_new_by_size_7);
    }
    til_Ptr_p.alloc_size = (*til_I64_size);
    return til_Ptr_p;
    return (til_Ptr){};
}

til_Ptr til_Ptr_new(til_Type til_Type_T) {
    til_I64 _tmp_til_Ptr_new_0 = til_size_of(&((til_Str){((til_Ptr){(til_I64)til_Type_T, 1, 0, 0, 0}), strlen(til_Type_T), 0}));
    til_Ptr til_Ptr_p = til_Ptr_new_by_size(&_tmp_til_Ptr_new_0);
    til_Ptr_p.elem_size = til_size_of(&((til_Str){((til_Ptr){(til_I64)til_Type_T, 1, 0, 0, 0}), strlen(til_Type_T), 0}));
    return til_Ptr_p;
    return (til_Ptr){};
}

til_Ptr til_Ptr_new_array(til_Type til_Type_T, const til_I64* til_I64_count) {
    til_I64 til_I64_elem_sz = til_size_of(&((til_Str){((til_Ptr){(til_I64)til_Type_T, 1, 0, 0, 0}), strlen(til_Type_T), 0}));
    til_I64 til_I64_total = til_I64_mul(&til_I64_elem_sz, til_I64_count);
    til_Ptr til_Ptr_p = til_Ptr_new_by_size(&til_I64_total);
    til_Ptr_p.elem_size = til_I64_elem_sz;
    return til_Ptr_p;
    return (til_Ptr){};
}

void til_Ptr_delete(til_Ptr* til_Ptr_self) {
    if (til_I64_eq(&til_I64_NULL, &til_Ptr_self->data).data) {
        return;
    }
    til_I64 _tmp_til_Ptr_delete_0 = 0;
    if (til_I64_eq(&til_Ptr_self->is_borrowed, &_tmp_til_Ptr_delete_0).data) {
        til_free(&til_Ptr_self->data);
    }
    til_Ptr_self->data = til_I64_clone(&til_I64_NULL);
}

til_Ptr til_Ptr_clone(const til_Ptr* til_Ptr_self) {
    if (til_I64_eq(&til_I64_NULL, &til_Ptr_self->data).data) {
        return (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    }
    til_Ptr til_Ptr_borrowed;
    til_I64 _tmp_til_Ptr_clone_0 = 0;
    if (til_I64_lteq(&til_Ptr_self->alloc_size, &_tmp_til_Ptr_clone_0).data) {
        til_Ptr_borrowed = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
        til_Ptr_borrowed.data = til_Ptr_self->data;
        til_Ptr_borrowed.is_borrowed = 1;
        return til_Ptr_borrowed;
    }
    til_Ptr til_Ptr_cloned = til_Ptr_new_by_size(&til_Ptr_self->alloc_size);
    til_Ptr_cloned.elem_type = til_Ptr_self->elem_type;
    til_Ptr_cloned.elem_size = til_Ptr_self->elem_size;
    til_memcpy(&til_Ptr_cloned.data, &til_Ptr_self->data, &til_Ptr_self->alloc_size);
    return til_Ptr_cloned;
    return (til_Ptr){};
}

til_Ptr til_Ptr_offset(const til_Ptr* til_Ptr_self, const til_I64* til_I64_byte_offset) {
    til_Ptr til_Ptr_p = {.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    til_Ptr_p.data = til_I64_add(&til_Ptr_self->data, til_I64_byte_offset);
    til_Ptr_p.is_borrowed = 1;
    til_Ptr_p.elem_type = til_Ptr_self->elem_type;
    til_Ptr_p.elem_size = til_Ptr_self->elem_size;
    return til_Ptr_p;
    return (til_Ptr){};
}

void til_Ptr_copy_from(til_Ptr* til_Ptr_self, const til_Ptr* til_Ptr_src, const til_I64* til_I64_size) {
    til_memcpy(&til_Ptr_self->data, &til_Ptr_src->data, til_I64_size);
}

void til_Ptr_copy_to(const til_Ptr* til_Ptr_self, til_Ptr* til_Ptr_dest, const til_I64* til_I64_size) {
    til_memcpy(&til_Ptr_dest->data, &til_Ptr_self->data, til_I64_size);
}

void til_Ptr_set_zero(til_Ptr* til_Ptr_self, const til_I64* til_I64_size) {
    til_U8 til_U8_zero = 0;
    til_memset(&til_Ptr_self->data, &til_U8_zero, til_I64_size);
}

void til_Ptr_copy_from_dynamic(til_Ptr* til_Ptr_self, const til_Dynamic* til_Dynamic_value, const til_I64* til_I64_size) {
    til_I64 _tmp_til_Ptr_copy_from_dynamic_0 = (til_I64)til_Dynamic_value;
    til_memcpy(&til_Ptr_self->data, &_tmp_til_Ptr_copy_from_dynamic_0, til_I64_size);
}

void til_Ptr_copy_to_dynamic(const til_Ptr* til_Ptr_self, til_Dynamic* til_Dynamic_dest, const til_I64* til_I64_size) {
    til_I64 _tmp_til_Ptr_copy_to_dynamic_0 = (til_I64)til_Dynamic_dest;
    til_memcpy(&_tmp_til_Ptr_copy_to_dynamic_0, &til_Ptr_self->data, til_I64_size);
}

void til_Ptr_dereference(const til_Ptr* til_Ptr_self, til_Type til_Type_T, til_Dynamic* til_Dynamic_dest) {
    til_I64 _tmp_til_Ptr_dereference_0 = (til_I64)til_Dynamic_dest;
    til_I64 _tmp_til_Ptr_dereference_1 = til_size_of(&((til_Str){((til_Ptr){(til_I64)til_Type_T, 1, 0, 0, 0}), strlen(til_Type_T), 0}));
    til_memcpy(&_tmp_til_Ptr_dereference_0, &til_Ptr_self->data, &_tmp_til_Ptr_dereference_1);
}

til_I64 til_Ptr_size_of(void) {
    return til_size_of(&((til_Str){((til_Ptr){(til_I64)"I64", 1, 0, 0, 0}), 3, 0}));
    return (til_I64){};
}

til_Bool til_Ptr_is_null(const til_Ptr* til_Ptr_self) {
    return til_I64_eq(&til_I64_NULL, &til_Ptr_self->data);
    return (til_Bool){};
}

til_I64 til_Array_len(const til_Array* til_Array_self) {
    return til_Array_self->_len;
    return (til_I64){};
}

til_I64 til_Array_size(const til_Array* til_Array_self) {
    return til_I64_mul(&til_Array_self->_len, &til_Array_self->ptr.elem_size);
    return (til_I64){};
}

til_Array til_Array_new(til_Type til_Type_T, const til_I64* til_I64_capacity) {
    til_Array til_Array_arr = {};
    til_I64 til_I64_size_bytes = {};
    til_Ptr til_Ptr_p = {};
    til_U8 til_U8_zero = {};
    til_BadAlloc _thrown_BadAlloc__tmp_til_Array_new_0 = {};
    til_Ptr _tmp_til_Array_new_1 = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    til_Array_arr = (til_Array){.ptr = _tmp_til_Array_new_1, ._len = 0};
    til_I64 _tmp_til_Array_new_2 = til_size_of(&((til_Str){((til_Ptr){(til_I64)til_Type_T, 1, 0, 0, 0}), strlen(til_Type_T), 0}));
    til_I64_size_bytes = til_I64_mul(til_I64_capacity, &_tmp_til_Array_new_2);
    til_Ptr_p = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    int __attribute__((unused)) _status__tmp_til_Array_new_3 = til_malloc(&(til_Ptr_p.data), &til_I64_size_bytes);
    if (_status__tmp_til_Array_new_3 == 1) { goto _catch_BadAlloc__tmp_til_Array_new_0; }
    if (0) { _catch_BadAlloc__tmp_til_Array_new_0:;
        til_BadAlloc til_BadAlloc_err = _thrown_BadAlloc__tmp_til_Array_new_0;
        til_Array _tmp_til_Array_new_4;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Array_new_5;
        til_Type _tmp_til_Array_new_6 = "Str";
        til_I64 _tmp_til_Array_new_7 = 0;
        _tmp_til_Array_new_4 = til_Array_new(_tmp_til_Array_new_6, &_tmp_til_Array_new_7);
        int __attribute__((unused)) _arr_status__tmp_til_Array_new_5;
        til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/array.til:34:39:", 1, 0, 0, 0}), 25, 0}), &((til_Str){((til_Ptr){(til_I64)"Array.new: malloc failed", 1, 0, 0, 0}), 24, 0}), &_tmp_til_Array_new_4);
        til_Array_delete(&_tmp_til_Array_new_4);
    }
    til_Ptr_p.alloc_size = til_I64_size_bytes;
    til_Ptr_p.elem_size = til_size_of(&((til_Str){((til_Ptr){(til_I64)til_Type_T, 1, 0, 0, 0}), strlen(til_Type_T), 0}));
    til_U8_zero = 0;
    til_memset(&til_Ptr_p.data, &til_U8_zero, &til_I64_size_bytes);
    til_Array_arr.ptr = til_Ptr_p;
    til_Array_arr._len = (*til_I64_capacity);
    return til_Array_arr;
    return (til_Array){};
}

int til_Array_get(til_Ptr* _ret, til_IndexOutOfBoundsError* _err1, const til_Array* til_Array_self, const til_I64* til_I64_index) {
    if (til_I64_gteq(til_I64_index, &til_Array_self->_len).data) {
        til_Str _tmp_til_Array_get_0;
        til_Array _tmp_til_Array_get_1;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Array_get_2;
        til_Str _tmp_til_Array_get_3 = ((til_Str){((til_Ptr){(til_I64)"Array.get: index out of bounds", 1, 0, 0, 0}), 30, 0});
        til_Type _tmp_til_Array_get_4 = "Str";
        til_I64 _tmp_til_Array_get_5 = 1;
        _tmp_til_Array_get_1 = til_Array_new(_tmp_til_Array_get_4, &_tmp_til_Array_get_5);
        int __attribute__((unused)) _arr_status__tmp_til_Array_get_2;
        til_I64 _tmp_til_Array_get_6 = 0;
        _arr_status__tmp_til_Array_get_2 = til_Array_set(&_err_idx__tmp_til_Array_get_2, &_tmp_til_Array_get_1, &_tmp_til_Array_get_6, (til_Dynamic*)&_tmp_til_Array_get_3);
        _tmp_til_Array_get_0 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/array.til:47:52:", 1, 0, 0, 0}), 25, 0}), &_tmp_til_Array_get_1);
        til_Array_delete(&_tmp_til_Array_get_1);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_til_Array_get_0};
        return 1;
    }
    til_I64 _tmp_til_Array_get_7 = til_I64_mul(til_I64_index, &til_Array_self->ptr.elem_size);
    *_ret = til_Ptr_offset(&til_Array_self->ptr, &_tmp_til_Array_get_7);
    return 0;
    return 0;
}

int til_Array_set(til_IndexOutOfBoundsError* _err1, til_Array* til_Array_self, const til_I64* til_I64_index, til_Dynamic* til_Dynamic_value) {
    if (til_I64_gteq(til_I64_index, &til_Array_self->_len).data) {
        til_Str _tmp_til_Array_set_0;
        til_Array _tmp_til_Array_set_1;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Array_set_2;
        til_Str _tmp_til_Array_set_3 = ((til_Str){((til_Ptr){(til_I64)"Array.set: index out of bounds", 1, 0, 0, 0}), 30, 0});
        til_Type _tmp_til_Array_set_4 = "Str";
        til_I64 _tmp_til_Array_set_5 = 1;
        _tmp_til_Array_set_1 = til_Array_new(_tmp_til_Array_set_4, &_tmp_til_Array_set_5);
        int __attribute__((unused)) _arr_status__tmp_til_Array_set_2;
        til_I64 _tmp_til_Array_set_6 = 0;
        _arr_status__tmp_til_Array_set_2 = til_Array_set(&_err_idx__tmp_til_Array_set_2, &_tmp_til_Array_set_1, &_tmp_til_Array_set_6, (til_Dynamic*)&_tmp_til_Array_set_3);
        _tmp_til_Array_set_0 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/array.til:56:52:", 1, 0, 0, 0}), 25, 0}), &_tmp_til_Array_set_1);
        til_Array_delete(&_tmp_til_Array_set_1);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_til_Array_set_0};
        return 1;
    }
    til_I64 _tmp_til_Array_set_7 = til_I64_mul(til_I64_index, &til_Array_self->ptr.elem_size);
    til_Ptr til_Ptr_dest = til_Ptr_offset(&til_Array_self->ptr, &_tmp_til_Array_set_7);
    til_Ptr_copy_from_dynamic(&til_Ptr_dest, (til_Dynamic*)til_Dynamic_value, &til_Array_self->ptr.elem_size);
    return 0;
}

void til_Array_delete(til_Array* til_Array_self) {
    til_Bool _tmp_til_Array_delete_0 = til_Ptr_is_null(&til_Array_self->ptr);
    if (til_not(&_tmp_til_Array_delete_0).data) {
        til_Ptr_delete(&til_Array_self->ptr);
    }
    til_Array_self->_len = 0;
}

til_Array til_Array_clone(const til_Array* til_Array_self) {
    til_Array til_Array_cloned = {};
    til_I64 til_I64_total_bytes = {};
    til_Ptr til_Ptr_p = {};
    til_BadAlloc _thrown_BadAlloc__tmp_til_Array_clone_0 = {};
    til_Ptr _tmp_til_Array_clone_1 = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    til_Array_cloned = (til_Array){.ptr = _tmp_til_Array_clone_1, ._len = 0};
    til_Array_cloned._len = til_Array_self->_len;
    til_I64_total_bytes = til_I64_mul(&til_Array_self->_len, &til_Array_self->ptr.elem_size);
    til_Ptr_p = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    int __attribute__((unused)) _status__tmp_til_Array_clone_2 = til_malloc(&(til_Ptr_p.data), &til_I64_total_bytes);
    if (_status__tmp_til_Array_clone_2 == 1) { goto _catch_BadAlloc__tmp_til_Array_clone_0; }
    if (0) { _catch_BadAlloc__tmp_til_Array_clone_0:;
        til_BadAlloc til_BadAlloc_err = _thrown_BadAlloc__tmp_til_Array_clone_0;
        til_Array _tmp_til_Array_clone_3;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Array_clone_4;
        til_Type _tmp_til_Array_clone_5 = "Str";
        til_I64 _tmp_til_Array_clone_6 = 0;
        _tmp_til_Array_clone_3 = til_Array_new(_tmp_til_Array_clone_5, &_tmp_til_Array_clone_6);
        int __attribute__((unused)) _arr_status__tmp_til_Array_clone_4;
        til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/array.til:79:39:", 1, 0, 0, 0}), 25, 0}), &((til_Str){((til_Ptr){(til_I64)"Array.clone: malloc failed", 1, 0, 0, 0}), 26, 0}), &_tmp_til_Array_clone_3);
        til_Array_delete(&_tmp_til_Array_clone_3);
    }
    til_Ptr_p.alloc_size = til_I64_total_bytes;
    til_Ptr_p.elem_size = til_Array_self->ptr.elem_size;
    til_memcpy(&til_Ptr_p.data, &til_Array_self->ptr.data, &til_I64_total_bytes);
    til_Array_cloned.ptr = til_Ptr_p;
    return til_Array_cloned;
    return (til_Array){};
}

til_Bool til_Array_contains(const til_Array* til_Array_self, const til_Str* til_Str_value) {
    til_I64 _for_i_0 = 0;
    til_Ptr _ref_forin_0;
    til_Str til_Str_elem;
    while (1) {
        til_I64 _tmp_til_Array_contains_0 = til_Array_len(til_Array_self);
        if (!(til_I64_lt(&_for_i_0, &_tmp_til_Array_contains_0).data)) break;
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp_til_Array_contains_1 = {};
        til_IndexOutOfBoundsError _err0__tmp_til_Array_contains_2 = {};
        int __attribute__((unused)) _status__tmp_til_Array_contains_2 = til_Array_get(&_ref_forin_0, &_err0__tmp_til_Array_contains_2, til_Array_self, &_for_i_0);
        if (_status__tmp_til_Array_contains_2 == 1) { _thrown_IndexOutOfBoundsError__tmp_til_Array_contains_1 = _err0__tmp_til_Array_contains_2; goto _catch_IndexOutOfBoundsError__tmp_til_Array_contains_1; }
        if (0) { _catch_IndexOutOfBoundsError__tmp_til_Array_contains_1:;
            til_IndexOutOfBoundsError _err_forin_0 = _thrown_IndexOutOfBoundsError__tmp_til_Array_contains_1;
            til_Array _tmp_til_Array_contains_3;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Array_contains_4;
            til_Type _tmp_til_Array_contains_5 = "Str";
            til_I64 _tmp_til_Array_contains_6 = 0;
            _tmp_til_Array_contains_3 = til_Array_new(_tmp_til_Array_contains_5, &_tmp_til_Array_contains_6);
            int __attribute__((unused)) _arr_status__tmp_til_Array_contains_4;
            til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/array.til:89:9:", 1, 0, 0, 0}), 24, 0}), &_err_forin_0.msg, &_tmp_til_Array_contains_3);
            til_Array_delete(&_tmp_til_Array_contains_3);
        }
        til_Str* til_Str_elem;
        til_Str_elem = (til_Str*)_ref_forin_0.data;
        if (til_Str_eq(til_Str_elem, til_Str_value).data) {
            return true;
        }
        til_I64 _tmp_til_Array_contains_7 = 1;
        _for_i_0 = til_I64_add(&_for_i_0, &_tmp_til_Array_contains_7);
    }
    return false;
    return (til_Bool){};
}

til_I64 til_Bool_len(const til_Bool* _self) {
    (void)_self;
    return 1;
    return (til_I64){};
}

til_Bool til_Bool_eq(const til_Bool* til_Bool_a, const til_Bool* til_Bool_b) {
    til_Bool _tmp_til_Bool_eq_0 = til_Bool_and(til_Bool_a, til_Bool_b);
    til_Bool _tmp_til_Bool_eq_1 = til_not(til_Bool_b);
    til_Bool _tmp_til_Bool_eq_2 = til_not(til_Bool_a);
    til_Bool _tmp_til_Bool_eq_3 = til_Bool_and(&_tmp_til_Bool_eq_1, &_tmp_til_Bool_eq_2);
    return til_Bool_or(&_tmp_til_Bool_eq_0, &_tmp_til_Bool_eq_3);
    return (til_Bool){};
}

til_Bool til_Bool_and(const til_Bool* til_Bool_self, const til_Bool* til_Bool_other) {
    if ((*til_Bool_self).data) {
        return (*til_Bool_other);
    }
    return false;
    return (til_Bool){};
}

til_Bool til_Bool_or(const til_Bool* til_Bool_self, const til_Bool* til_Bool_other) {
    if ((*til_Bool_self).data) {
        return true;
    }
    return (*til_Bool_other);
    return (til_Bool){};
}

til_Str til_Bool_to_str(const til_Bool* til_Bool_self) {
    if ((*til_Bool_self).data) {
        return ((til_Str){((til_Ptr){(til_I64)"true", 1, 0, 0, 0}), 4, 0});
    }
    return ((til_Str){((til_Ptr){(til_I64)"false", 1, 0, 0, 0}), 5, 0});
    return (til_Str){};
}

til_I64 til_Bool_to_i64(const til_Bool* til_Bool_self) {
    if ((*til_Bool_self).data) {
        return 1;
    }
    return 0;
    return (til_I64){};
}

til_U8 til_Bool_to_u8(const til_Bool* til_Bool_self) {
    return til_Bool_self->data;
    return (til_U8){};
}

til_Bool til_Bool_from_i64(const til_I64* til_I64_i) {
    til_Bool til_Bool_b = {.data = 0};
    til_I64 _tmp_til_Bool_from_i64_0 = 0;
    if (til_I64_gt(til_I64_i, &_tmp_til_Bool_from_i64_0).data) {
        til_Bool_b.data = 1;
    }
    return til_Bool_b;
    return (til_Bool){};
}

til_I64 til_Bool_size(void) {
    return 1;
    return (til_I64){};
}

void til_Bool_delete(til_Bool* _self) {
    (void)_self;
}

til_Bool til_Bool_clone(const til_Bool* til_Bool_self) {
    return (til_Bool){.data = til_U8_clone(&til_Bool_self->data)};
    return (til_Bool){};
}

int til_I64_safe_div(til_I64* _ret, const til_I64* til_I64_a, const til_I64* til_I64_b) {
    til_I64 _tmp_til_I64_safe_div_0 = 0;
    if (til_I64_eq(til_I64_b, &_tmp_til_I64_safe_div_0).data) {
        return 1;
    }
    *_ret = til_I64_div(til_I64_a, til_I64_b);
    return 0;
    return 0;
}

int til_I64_safe_add(til_I64* _ret, til_I64_Overflow* _err1, const til_I64* til_I64_a, const til_I64* til_I64_b) {
    til_I64 til_I64_result = til_I64_add(til_I64_a, til_I64_b);
    til_I64 _tmp_til_I64_safe_add_0 = 0;
    if (til_I64_gt(til_I64_b, &_tmp_til_I64_safe_add_0).data) {
        if (til_I64_lt(&til_I64_result, til_I64_a).data) {
            til_Str _tmp_til_I64_safe_add_1;
            til_Array _tmp_til_I64_safe_add_2;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_I64_safe_add_3;
            til_Str _tmp_til_I64_safe_add_4 = ((til_Str){((til_Ptr){(til_I64)"I64 overflow: ", 1, 0, 0, 0}), 14, 0});
            til_Str _tmp_til_I64_safe_add_5 = til_I64_to_str(til_I64_a);
            til_Str _tmp_til_I64_safe_add_6 = ((til_Str){((til_Ptr){(til_I64)" + ", 1, 0, 0, 0}), 3, 0});
            til_Str _tmp_til_I64_safe_add_7 = til_I64_to_str(til_I64_b);
            til_Type _tmp_til_I64_safe_add_8 = "Str";
            til_I64 _tmp_til_I64_safe_add_9 = 4;
            _tmp_til_I64_safe_add_2 = til_Array_new(_tmp_til_I64_safe_add_8, &_tmp_til_I64_safe_add_9);
            int __attribute__((unused)) _arr_status__tmp_til_I64_safe_add_3;
            til_I64 _tmp_til_I64_safe_add_10 = 0;
            _arr_status__tmp_til_I64_safe_add_3 = til_Array_set(&_err_idx__tmp_til_I64_safe_add_3, &_tmp_til_I64_safe_add_2, &_tmp_til_I64_safe_add_10, (til_Dynamic*)&_tmp_til_I64_safe_add_4);
            til_I64 _tmp_til_I64_safe_add_11 = 1;
            _arr_status__tmp_til_I64_safe_add_3 = til_Array_set(&_err_idx__tmp_til_I64_safe_add_3, &_tmp_til_I64_safe_add_2, &_tmp_til_I64_safe_add_11, (til_Dynamic*)&_tmp_til_I64_safe_add_5);
            til_I64 _tmp_til_I64_safe_add_12 = 2;
            _arr_status__tmp_til_I64_safe_add_3 = til_Array_set(&_err_idx__tmp_til_I64_safe_add_3, &_tmp_til_I64_safe_add_2, &_tmp_til_I64_safe_add_12, (til_Dynamic*)&_tmp_til_I64_safe_add_6);
            til_I64 _tmp_til_I64_safe_add_13 = 3;
            _arr_status__tmp_til_I64_safe_add_3 = til_Array_set(&_err_idx__tmp_til_I64_safe_add_3, &_tmp_til_I64_safe_add_2, &_tmp_til_I64_safe_add_13, (til_Dynamic*)&_tmp_til_I64_safe_add_7);
            _tmp_til_I64_safe_add_1 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/i64.til:36:47:", 1, 0, 0, 0}), 23, 0}), &_tmp_til_I64_safe_add_2);
            til_Array_delete(&_tmp_til_I64_safe_add_2);
            *_err1 = (til_I64_Overflow){.msg = _tmp_til_I64_safe_add_1};
            return 1;
        }
    }
    til_I64 _tmp_til_I64_safe_add_14 = 0;
    if (til_I64_lt(til_I64_b, &_tmp_til_I64_safe_add_14).data) {
        if (til_I64_gt(&til_I64_result, til_I64_a).data) {
            til_Str _tmp_til_I64_safe_add_15;
            til_Array _tmp_til_I64_safe_add_16;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_I64_safe_add_17;
            til_Str _tmp_til_I64_safe_add_18 = ((til_Str){((til_Ptr){(til_I64)"I64 overflow: ", 1, 0, 0, 0}), 14, 0});
            til_Str _tmp_til_I64_safe_add_19 = til_I64_to_str(til_I64_a);
            til_Str _tmp_til_I64_safe_add_20 = ((til_Str){((til_Ptr){(til_I64)" + ", 1, 0, 0, 0}), 3, 0});
            til_Str _tmp_til_I64_safe_add_21 = til_I64_to_str(til_I64_b);
            til_Type _tmp_til_I64_safe_add_22 = "Str";
            til_I64 _tmp_til_I64_safe_add_23 = 4;
            _tmp_til_I64_safe_add_16 = til_Array_new(_tmp_til_I64_safe_add_22, &_tmp_til_I64_safe_add_23);
            int __attribute__((unused)) _arr_status__tmp_til_I64_safe_add_17;
            til_I64 _tmp_til_I64_safe_add_24 = 0;
            _arr_status__tmp_til_I64_safe_add_17 = til_Array_set(&_err_idx__tmp_til_I64_safe_add_17, &_tmp_til_I64_safe_add_16, &_tmp_til_I64_safe_add_24, (til_Dynamic*)&_tmp_til_I64_safe_add_18);
            til_I64 _tmp_til_I64_safe_add_25 = 1;
            _arr_status__tmp_til_I64_safe_add_17 = til_Array_set(&_err_idx__tmp_til_I64_safe_add_17, &_tmp_til_I64_safe_add_16, &_tmp_til_I64_safe_add_25, (til_Dynamic*)&_tmp_til_I64_safe_add_19);
            til_I64 _tmp_til_I64_safe_add_26 = 2;
            _arr_status__tmp_til_I64_safe_add_17 = til_Array_set(&_err_idx__tmp_til_I64_safe_add_17, &_tmp_til_I64_safe_add_16, &_tmp_til_I64_safe_add_26, (til_Dynamic*)&_tmp_til_I64_safe_add_20);
            til_I64 _tmp_til_I64_safe_add_27 = 3;
            _arr_status__tmp_til_I64_safe_add_17 = til_Array_set(&_err_idx__tmp_til_I64_safe_add_17, &_tmp_til_I64_safe_add_16, &_tmp_til_I64_safe_add_27, (til_Dynamic*)&_tmp_til_I64_safe_add_21);
            _tmp_til_I64_safe_add_15 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/i64.til:41:47:", 1, 0, 0, 0}), 23, 0}), &_tmp_til_I64_safe_add_16);
            til_Array_delete(&_tmp_til_I64_safe_add_16);
            *_err1 = (til_I64_Overflow){.msg = _tmp_til_I64_safe_add_15};
            return 1;
        }
    }
    *_ret = til_I64_result;
    return 0;
    return 0;
}

int til_I64_safe_sub(til_I64* _ret, til_I64_Overflow* _err1, const til_I64* til_I64_a, const til_I64* til_I64_b) {
    til_I64 til_I64_result = til_I64_sub(til_I64_a, til_I64_b);
    til_I64 _tmp_til_I64_safe_sub_0 = 0;
    if (til_I64_gt(til_I64_b, &_tmp_til_I64_safe_sub_0).data) {
        if (til_I64_gt(&til_I64_result, til_I64_a).data) {
            til_Str _tmp_til_I64_safe_sub_1;
            til_Array _tmp_til_I64_safe_sub_2;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_I64_safe_sub_3;
            til_Str _tmp_til_I64_safe_sub_4 = ((til_Str){((til_Ptr){(til_I64)"I64 underflow: ", 1, 0, 0, 0}), 15, 0});
            til_Str _tmp_til_I64_safe_sub_5 = til_I64_to_str(til_I64_a);
            til_Str _tmp_til_I64_safe_sub_6 = ((til_Str){((til_Ptr){(til_I64)" - ", 1, 0, 0, 0}), 3, 0});
            til_Str _tmp_til_I64_safe_sub_7 = til_I64_to_str(til_I64_b);
            til_Type _tmp_til_I64_safe_sub_8 = "Str";
            til_I64 _tmp_til_I64_safe_sub_9 = 4;
            _tmp_til_I64_safe_sub_2 = til_Array_new(_tmp_til_I64_safe_sub_8, &_tmp_til_I64_safe_sub_9);
            int __attribute__((unused)) _arr_status__tmp_til_I64_safe_sub_3;
            til_I64 _tmp_til_I64_safe_sub_10 = 0;
            _arr_status__tmp_til_I64_safe_sub_3 = til_Array_set(&_err_idx__tmp_til_I64_safe_sub_3, &_tmp_til_I64_safe_sub_2, &_tmp_til_I64_safe_sub_10, (til_Dynamic*)&_tmp_til_I64_safe_sub_4);
            til_I64 _tmp_til_I64_safe_sub_11 = 1;
            _arr_status__tmp_til_I64_safe_sub_3 = til_Array_set(&_err_idx__tmp_til_I64_safe_sub_3, &_tmp_til_I64_safe_sub_2, &_tmp_til_I64_safe_sub_11, (til_Dynamic*)&_tmp_til_I64_safe_sub_5);
            til_I64 _tmp_til_I64_safe_sub_12 = 2;
            _arr_status__tmp_til_I64_safe_sub_3 = til_Array_set(&_err_idx__tmp_til_I64_safe_sub_3, &_tmp_til_I64_safe_sub_2, &_tmp_til_I64_safe_sub_12, (til_Dynamic*)&_tmp_til_I64_safe_sub_6);
            til_I64 _tmp_til_I64_safe_sub_13 = 3;
            _arr_status__tmp_til_I64_safe_sub_3 = til_Array_set(&_err_idx__tmp_til_I64_safe_sub_3, &_tmp_til_I64_safe_sub_2, &_tmp_til_I64_safe_sub_13, (til_Dynamic*)&_tmp_til_I64_safe_sub_7);
            _tmp_til_I64_safe_sub_1 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/i64.til:54:47:", 1, 0, 0, 0}), 23, 0}), &_tmp_til_I64_safe_sub_2);
            til_Array_delete(&_tmp_til_I64_safe_sub_2);
            *_err1 = (til_I64_Overflow){.msg = _tmp_til_I64_safe_sub_1};
            return 1;
        }
    }
    til_I64 _tmp_til_I64_safe_sub_14 = 0;
    if (til_I64_lt(til_I64_b, &_tmp_til_I64_safe_sub_14).data) {
        if (til_I64_lt(&til_I64_result, til_I64_a).data) {
            til_Str _tmp_til_I64_safe_sub_15;
            til_Array _tmp_til_I64_safe_sub_16;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_I64_safe_sub_17;
            til_Str _tmp_til_I64_safe_sub_18 = ((til_Str){((til_Ptr){(til_I64)"I64 underflow: ", 1, 0, 0, 0}), 15, 0});
            til_Str _tmp_til_I64_safe_sub_19 = til_I64_to_str(til_I64_a);
            til_Str _tmp_til_I64_safe_sub_20 = ((til_Str){((til_Ptr){(til_I64)" - ", 1, 0, 0, 0}), 3, 0});
            til_Str _tmp_til_I64_safe_sub_21 = til_I64_to_str(til_I64_b);
            til_Type _tmp_til_I64_safe_sub_22 = "Str";
            til_I64 _tmp_til_I64_safe_sub_23 = 4;
            _tmp_til_I64_safe_sub_16 = til_Array_new(_tmp_til_I64_safe_sub_22, &_tmp_til_I64_safe_sub_23);
            int __attribute__((unused)) _arr_status__tmp_til_I64_safe_sub_17;
            til_I64 _tmp_til_I64_safe_sub_24 = 0;
            _arr_status__tmp_til_I64_safe_sub_17 = til_Array_set(&_err_idx__tmp_til_I64_safe_sub_17, &_tmp_til_I64_safe_sub_16, &_tmp_til_I64_safe_sub_24, (til_Dynamic*)&_tmp_til_I64_safe_sub_18);
            til_I64 _tmp_til_I64_safe_sub_25 = 1;
            _arr_status__tmp_til_I64_safe_sub_17 = til_Array_set(&_err_idx__tmp_til_I64_safe_sub_17, &_tmp_til_I64_safe_sub_16, &_tmp_til_I64_safe_sub_25, (til_Dynamic*)&_tmp_til_I64_safe_sub_19);
            til_I64 _tmp_til_I64_safe_sub_26 = 2;
            _arr_status__tmp_til_I64_safe_sub_17 = til_Array_set(&_err_idx__tmp_til_I64_safe_sub_17, &_tmp_til_I64_safe_sub_16, &_tmp_til_I64_safe_sub_26, (til_Dynamic*)&_tmp_til_I64_safe_sub_20);
            til_I64 _tmp_til_I64_safe_sub_27 = 3;
            _arr_status__tmp_til_I64_safe_sub_17 = til_Array_set(&_err_idx__tmp_til_I64_safe_sub_17, &_tmp_til_I64_safe_sub_16, &_tmp_til_I64_safe_sub_27, (til_Dynamic*)&_tmp_til_I64_safe_sub_21);
            _tmp_til_I64_safe_sub_15 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/i64.til:59:47:", 1, 0, 0, 0}), 23, 0}), &_tmp_til_I64_safe_sub_16);
            til_Array_delete(&_tmp_til_I64_safe_sub_16);
            *_err1 = (til_I64_Overflow){.msg = _tmp_til_I64_safe_sub_15};
            return 1;
        }
    }
    *_ret = til_I64_result;
    return 0;
    return 0;
}

int til_I64_safe_mul(til_I64* _ret, til_I64_Overflow* _err1, const til_I64* til_I64_a, const til_I64* til_I64_b) {
    til_I64 til_I64_result = til_I64_mul(til_I64_a, til_I64_b);
    til_I64 _tmp_til_I64_safe_mul_0 = 0;
    til_Bool _tmp_til_I64_safe_mul_1 = til_I64_eq(til_I64_a, &_tmp_til_I64_safe_mul_0);
    if (til_not(&_tmp_til_I64_safe_mul_1).data) {
        til_I64 _tmp_til_I64_safe_mul_2 = til_I64_div(&til_I64_result, til_I64_a);
        til_Bool _tmp_til_I64_safe_mul_3 = til_I64_eq(&_tmp_til_I64_safe_mul_2, til_I64_b);
        if (til_not(&_tmp_til_I64_safe_mul_3).data) {
            til_Str _tmp_til_I64_safe_mul_4;
            til_Array _tmp_til_I64_safe_mul_5;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_I64_safe_mul_6;
            til_Str _tmp_til_I64_safe_mul_7 = ((til_Str){((til_Ptr){(til_I64)"I64 overflow: ", 1, 0, 0, 0}), 14, 0});
            til_Str _tmp_til_I64_safe_mul_8 = til_I64_to_str(til_I64_a);
            til_Str _tmp_til_I64_safe_mul_9 = ((til_Str){((til_Ptr){(til_I64)" * ", 1, 0, 0, 0}), 3, 0});
            til_Str _tmp_til_I64_safe_mul_10 = til_I64_to_str(til_I64_b);
            til_Type _tmp_til_I64_safe_mul_11 = "Str";
            til_I64 _tmp_til_I64_safe_mul_12 = 4;
            _tmp_til_I64_safe_mul_5 = til_Array_new(_tmp_til_I64_safe_mul_11, &_tmp_til_I64_safe_mul_12);
            int __attribute__((unused)) _arr_status__tmp_til_I64_safe_mul_6;
            til_I64 _tmp_til_I64_safe_mul_13 = 0;
            _arr_status__tmp_til_I64_safe_mul_6 = til_Array_set(&_err_idx__tmp_til_I64_safe_mul_6, &_tmp_til_I64_safe_mul_5, &_tmp_til_I64_safe_mul_13, (til_Dynamic*)&_tmp_til_I64_safe_mul_7);
            til_I64 _tmp_til_I64_safe_mul_14 = 1;
            _arr_status__tmp_til_I64_safe_mul_6 = til_Array_set(&_err_idx__tmp_til_I64_safe_mul_6, &_tmp_til_I64_safe_mul_5, &_tmp_til_I64_safe_mul_14, (til_Dynamic*)&_tmp_til_I64_safe_mul_8);
            til_I64 _tmp_til_I64_safe_mul_15 = 2;
            _arr_status__tmp_til_I64_safe_mul_6 = til_Array_set(&_err_idx__tmp_til_I64_safe_mul_6, &_tmp_til_I64_safe_mul_5, &_tmp_til_I64_safe_mul_15, (til_Dynamic*)&_tmp_til_I64_safe_mul_9);
            til_I64 _tmp_til_I64_safe_mul_16 = 3;
            _arr_status__tmp_til_I64_safe_mul_6 = til_Array_set(&_err_idx__tmp_til_I64_safe_mul_6, &_tmp_til_I64_safe_mul_5, &_tmp_til_I64_safe_mul_16, (til_Dynamic*)&_tmp_til_I64_safe_mul_10);
            _tmp_til_I64_safe_mul_4 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/i64.til:72:47:", 1, 0, 0, 0}), 23, 0}), &_tmp_til_I64_safe_mul_5);
            til_Array_delete(&_tmp_til_I64_safe_mul_5);
            *_err1 = (til_I64_Overflow){.msg = _tmp_til_I64_safe_mul_4};
            return 1;
        }
    }
    *_ret = til_I64_result;
    return 0;
    return 0;
}

til_I64 til_I64_xor(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    return til_i64_xor(til_I64_a, til_I64_b);
    return (til_I64){};
}

til_I64 til_I64_and(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    return til_i64_and(til_I64_a, til_I64_b);
    return (til_I64){};
}

til_I64 til_I64_or(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    return til_i64_or(til_I64_a, til_I64_b);
    return (til_I64){};
}

til_I64 til_I64_mod(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    return til_i64_mod(til_I64_a, til_I64_b);
    return (til_I64){};
}

til_I64 til_I64_sub(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    return til_i64_sub(til_I64_a, til_I64_b);
    return (til_I64){};
}

til_I64 til_I64_mul(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    return til_i64_mul(til_I64_a, til_I64_b);
    return (til_I64){};
}

til_I64 til_I64_div(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    return til_i64_div(til_I64_a, til_I64_b);
    return (til_I64){};
}

til_I64 til_I64_add(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    return til_i64_add(til_I64_a, til_I64_b);
    return (til_I64){};
}

til_Bool til_I64_eq(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    if (til_I64_gt(til_I64_a, til_I64_b).data) {
        return false;
    }
    if (til_I64_gt(til_I64_b, til_I64_a).data) {
        return false;
    }
    if (til_I64_lt(til_I64_a, til_I64_b).data) {
        return false;
    }
    if (til_I64_lt(til_I64_b, til_I64_a).data) {
        return false;
    }
    return true;
    return (til_Bool){};
}

til_Bool til_I64_lt(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    return til_i64_lt(til_I64_a, til_I64_b);
    return (til_Bool){};
}

til_Bool til_I64_gt(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    return til_i64_gt(til_I64_a, til_I64_b);
    return (til_Bool){};
}

til_Str til_I64_to_str(const til_I64* til_I64_self) {
    return til_i64_to_str(til_I64_self);
    return (til_Str){};
}

til_I64 til_I64_from_str(const til_Str* til_Str_str) {
    return til_str_to_i64(til_Str_str);
    return (til_I64){};
}

void til_I64_inc(til_I64* til_I64_self) {
    til_I64 _tmp_til_I64_inc_0 = 1;
    *til_I64_self = til_I64_add(til_I64_self, &_tmp_til_I64_inc_0);
}

void til_I64_dec(til_I64* til_I64_self) {
    til_I64 _tmp_til_I64_dec_0 = 1;
    *til_I64_self = til_I64_sub(til_I64_self, &_tmp_til_I64_dec_0);
}

til_Bool til_I64_gteq(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    if (til_I64_gt(til_I64_a, til_I64_b).data) {
        return true;
    }
    if (til_I64_lt(til_I64_a, til_I64_b).data) {
        return false;
    }
    return true;
    return (til_Bool){};
}

til_Bool til_I64_lteq(const til_I64* til_I64_a, const til_I64* til_I64_b) {
    if (til_I64_lt(til_I64_a, til_I64_b).data) {
        return true;
    }
    if (til_I64_gt(til_I64_a, til_I64_b).data) {
        return false;
    }
    return true;
    return (til_Bool){};
}

til_I64 til_I64_size(void) {
    return 8;
    return (til_I64){};
}

void til_I64_delete(til_I64* _self) {
    (void)_self;
}

til_I64 til_I64_clone(const til_I64* til_I64_self) {
    return (*til_I64_self);
    return (til_I64){};
}

til_I64 til_Vec_len(const til_Vec* til_Vec_self) {
    return til_Vec_self->_len;
    return (til_I64){};
}

til_I64 til_Vec_size(const til_Vec* til_Vec_self) {
    return til_I64_mul(&til_Vec_self->_len, &til_Vec_self->ptr.elem_size);
    return (til_I64){};
}

til_Bool til_Vec__is_str_type(const til_Vec* til_Vec_self) {
    if (til_I64_eq(&til_I64_NULL, &til_Vec_self->ptr.elem_type).data) {
        return false;
    }
    til_Str til_Str_str_ref = ((til_Str){((til_Ptr){(til_I64)"Str", 1, 0, 0, 0}), 3, 0});
    til_Ptr til_Ptr_str_ref_ptr = til_Str_str_ref.c_string;
    til_I64 _tmp_til_Vec__is_str_type_0 = 4;
    til_I64 _tmp_til_Vec__is_str_type_1 = til_memcmp(&til_Vec_self->ptr.elem_type, &til_Ptr_str_ref_ptr.data, &_tmp_til_Vec__is_str_type_0);
    til_I64 _tmp_til_Vec__is_str_type_2 = 0;
    return til_I64_eq(&_tmp_til_Vec__is_str_type_1, &_tmp_til_Vec__is_str_type_2);
    return (til_Bool){};
}

til_Vec til_Vec_new(til_Type til_Type_T) {
    til_Ptr _tmp_til_Vec_new_0 = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    til_Vec til_Vec_vec = {.ptr = _tmp_til_Vec_new_0, ._len = 0, .cap = 0};
    til_Str til_Str_type_str = ((til_Str){((til_Ptr){(til_I64)til_Type_T, 1, 0, 0, 0}), strlen(til_Type_T), 0});
    til_Ptr til_Ptr_type_c = til_Str_type_str.c_string;
    til_Ptr til_Ptr_p = {.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    til_Ptr_p.elem_type = til_Ptr_type_c.data;
    til_Ptr_p.elem_size = til_size_of(&((til_Str){((til_Ptr){(til_I64)til_Type_T, 1, 0, 0, 0}), strlen(til_Type_T), 0}));
    til_Vec_vec.ptr = til_Ptr_p;
    til_Vec_vec._len = 0;
    til_Vec_vec.cap = 0;
    return til_Vec_vec;
    return (til_Vec){};
}

til_Vec til_Vec_new_from_type_info(const til_Str* til_Str_type_name, const til_I64* til_I64_type_size) {
    til_Ptr _tmp_til_Vec_new_from_type_info_0 = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    til_Vec til_Vec_vec = {.ptr = _tmp_til_Vec_new_from_type_info_0, ._len = 0, .cap = 0};
    til_Ptr til_Ptr_type_c = til_Str_type_name->c_string;
    til_Ptr til_Ptr_p = {.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    til_Ptr_p.elem_type = til_Ptr_type_c.data;
    til_Ptr_p.elem_size = (*til_I64_type_size);
    til_Vec_vec.ptr = til_Ptr_p;
    til_Vec_vec._len = 0;
    til_Vec_vec.cap = 0;
    return til_Vec_vec;
    return (til_Vec){};
}

til_Ptr til_Vec__alloc_ptr(til_Vec* til_Vec_self, const til_I64* til_I64_capacity) {
    til_I64 _tmp_til_Vec__alloc_ptr_0 = til_I64_mul(til_I64_capacity, &til_Vec_self->ptr.elem_size);
    til_Ptr til_Ptr_p = til_Ptr_new_by_size(&_tmp_til_Vec__alloc_ptr_0);
    til_Ptr_p.elem_type = til_Vec_self->ptr.elem_type;
    til_Ptr_p.elem_size = til_Vec_self->ptr.elem_size;
    return til_Ptr_p;
    return (til_Ptr){};
}

til_Vec til_Vec_with_capacity(til_Type til_Type_T, const til_I64* til_I64_capacity) {
    til_Ptr _tmp_til_Vec_with_capacity_0 = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    til_Vec til_Vec_vec = {.ptr = _tmp_til_Vec_with_capacity_0, ._len = 0, .cap = 0};
    til_Str til_Str_type_str = ((til_Str){((til_Ptr){(til_I64)til_Type_T, 1, 0, 0, 0}), strlen(til_Type_T), 0});
    til_Ptr til_Ptr_type_c = til_Str_type_str.c_string;
    til_Ptr til_Ptr_p = {.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    til_Ptr_p.elem_type = til_Ptr_type_c.data;
    til_Ptr_p.elem_size = til_size_of(&((til_Str){((til_Ptr){(til_I64)til_Type_T, 1, 0, 0, 0}), strlen(til_Type_T), 0}));
    til_Vec_vec.ptr = til_Ptr_p;
    til_Vec_vec._len = 0;
    til_Vec_vec.cap = (*til_I64_capacity);
    til_I64 _tmp_til_Vec_with_capacity_1 = 0;
    if (til_I64_gt(til_I64_capacity, &_tmp_til_Vec_with_capacity_1).data) {
        til_I64 _tmp_til_Vec_with_capacity_2 = til_Vec_MAX_CAP;
        if (til_I64_gt(til_I64_capacity, &_tmp_til_Vec_with_capacity_2).data) {
            til_Array _tmp_til_Vec_with_capacity_3;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Vec_with_capacity_4;
            til_Type _tmp_til_Vec_with_capacity_5 = "Str";
            til_I64 _tmp_til_Vec_with_capacity_6 = 0;
            _tmp_til_Vec_with_capacity_3 = til_Array_new(_tmp_til_Vec_with_capacity_5, &_tmp_til_Vec_with_capacity_6);
            int __attribute__((unused)) _arr_status__tmp_til_Vec_with_capacity_4;
            til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/vec.til:88:23:", 1, 0, 0, 0}), 23, 0}), &((til_Str){((til_Ptr){(til_I64)"Vec.with_capacity: capacity exceeded Vec.MAX_CAP", 1, 0, 0, 0}), 48, 0}), &_tmp_til_Vec_with_capacity_3);
            til_Array_delete(&_tmp_til_Vec_with_capacity_3);
        }
        til_Vec_vec.ptr = til_Vec__alloc_ptr(&til_Vec_vec, til_I64_capacity);
    }
    return til_Vec_vec;
    return (til_Vec){};
}

void til_Vec_push(til_Vec* til_Vec_self, til_Dynamic* til_Dynamic_value) {
    til_I64 til_I64_new_cap;
    til_Ptr til_Ptr_new_ptr;
    if (til_I64_eq(&til_Vec_self->_len, &til_Vec_self->cap).data) {
        til_I64 _tmp_til_Vec_push_0 = 2;
        til_I64_new_cap = til_I64_mul(&til_Vec_self->cap, &_tmp_til_Vec_push_0);
        til_I64 _tmp_til_Vec_push_1 = 1;
        if (til_I64_lt(&til_I64_new_cap, &_tmp_til_Vec_push_1).data) {
            til_I64_new_cap = 1;
        }
        til_I64 _tmp_til_Vec_push_2 = til_Vec_MAX_CAP;
        if (til_I64_gt(&til_I64_new_cap, &_tmp_til_Vec_push_2).data) {
            til_Array _tmp_til_Vec_push_3;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Vec_push_4;
            til_Type _tmp_til_Vec_push_5 = "Str";
            til_I64 _tmp_til_Vec_push_6 = 0;
            _tmp_til_Vec_push_3 = til_Array_new(_tmp_til_Vec_push_5, &_tmp_til_Vec_push_6);
            int __attribute__((unused)) _arr_status__tmp_til_Vec_push_4;
            til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/vec.til:106:23:", 1, 0, 0, 0}), 24, 0}), &((til_Str){((til_Ptr){(til_I64)"Vec.push: capacity exceeded Vec.MAX_CAP", 1, 0, 0, 0}), 39, 0}), &_tmp_til_Vec_push_3);
            til_Array_delete(&_tmp_til_Vec_push_3);
        }
        til_Ptr_new_ptr = til_Vec__alloc_ptr(til_Vec_self, &til_I64_new_cap);
        til_I64 _tmp_til_Vec_push_7 = 0;
        if (til_I64_gt(&til_Vec_self->_len, &_tmp_til_Vec_push_7).data) {
            til_I64 _tmp_til_Vec_push_8 = til_I64_mul(&til_Vec_self->_len, &til_Vec_self->ptr.elem_size);
            til_Ptr_copy_from(&til_Ptr_new_ptr, &til_Vec_self->ptr, &_tmp_til_Vec_push_8);
        }
        til_Bool _tmp_til_Vec_push_9 = til_Ptr_is_null(&til_Vec_self->ptr);
        if (til_not(&_tmp_til_Vec_push_9).data) {
            til_Ptr_delete(&til_Vec_self->ptr);
        }
        til_Vec_self->ptr = til_Ptr_new_ptr;
        til_Vec_self->cap = til_I64_new_cap;
    }
    til_I64 _tmp_til_Vec_push_10 = til_I64_mul(&til_Vec_self->_len, &til_Vec_self->ptr.elem_size);
    til_Ptr til_Ptr_dest = til_Ptr_offset(&til_Vec_self->ptr, &_tmp_til_Vec_push_10);
    til_Ptr_copy_from_dynamic(&til_Ptr_dest, (til_Dynamic*)til_Dynamic_value, &til_Vec_self->ptr.elem_size);
    til_I64 _tmp_til_Vec_push_11 = 1;
    til_Vec_self->_len = til_I64_add(&til_Vec_self->_len, &_tmp_til_Vec_push_11);
}

int til_Vec_get(til_Ptr* _ret, til_IndexOutOfBoundsError* _err1, const til_Vec* til_Vec_self, const til_I64* til_I64_index) {
    if (til_I64_gteq(til_I64_index, &til_Vec_self->_len).data) {
        til_Str _tmp_til_Vec_get_0;
        til_Array _tmp_til_Vec_get_1;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Vec_get_2;
        til_Str _tmp_til_Vec_get_3 = ((til_Str){((til_Ptr){(til_I64)"Vec.get: index out of bounds", 1, 0, 0, 0}), 28, 0});
        til_Type _tmp_til_Vec_get_4 = "Str";
        til_I64 _tmp_til_Vec_get_5 = 1;
        _tmp_til_Vec_get_1 = til_Array_new(_tmp_til_Vec_get_4, &_tmp_til_Vec_get_5);
        int __attribute__((unused)) _arr_status__tmp_til_Vec_get_2;
        til_I64 _tmp_til_Vec_get_6 = 0;
        _arr_status__tmp_til_Vec_get_2 = til_Array_set(&_err_idx__tmp_til_Vec_get_2, &_tmp_til_Vec_get_1, &_tmp_til_Vec_get_6, (til_Dynamic*)&_tmp_til_Vec_get_3);
        _tmp_til_Vec_get_0 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/vec.til:128:52:", 1, 0, 0, 0}), 24, 0}), &_tmp_til_Vec_get_1);
        til_Array_delete(&_tmp_til_Vec_get_1);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_til_Vec_get_0};
        return 1;
    }
    til_I64 _tmp_til_Vec_get_7 = til_I64_mul(til_I64_index, &til_Vec_self->ptr.elem_size);
    *_ret = til_Ptr_offset(&til_Vec_self->ptr, &_tmp_til_Vec_get_7);
    return 0;
    return 0;
}

int til_Vec_set(til_IndexOutOfBoundsError* _err1, til_Vec* til_Vec_self, const til_I64* til_I64_index, til_Dynamic* til_Dynamic_value) {
    if (til_I64_gteq(til_I64_index, &til_Vec_self->_len).data) {
        til_Str _tmp_til_Vec_set_0;
        til_Array _tmp_til_Vec_set_1;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Vec_set_2;
        til_Str _tmp_til_Vec_set_3 = ((til_Str){((til_Ptr){(til_I64)"Vec.set: index out of bounds", 1, 0, 0, 0}), 28, 0});
        til_Type _tmp_til_Vec_set_4 = "Str";
        til_I64 _tmp_til_Vec_set_5 = 1;
        _tmp_til_Vec_set_1 = til_Array_new(_tmp_til_Vec_set_4, &_tmp_til_Vec_set_5);
        int __attribute__((unused)) _arr_status__tmp_til_Vec_set_2;
        til_I64 _tmp_til_Vec_set_6 = 0;
        _arr_status__tmp_til_Vec_set_2 = til_Array_set(&_err_idx__tmp_til_Vec_set_2, &_tmp_til_Vec_set_1, &_tmp_til_Vec_set_6, (til_Dynamic*)&_tmp_til_Vec_set_3);
        _tmp_til_Vec_set_0 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/vec.til:137:52:", 1, 0, 0, 0}), 24, 0}), &_tmp_til_Vec_set_1);
        til_Array_delete(&_tmp_til_Vec_set_1);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_til_Vec_set_0};
        return 1;
    }
    til_I64 _tmp_til_Vec_set_7 = til_I64_mul(til_I64_index, &til_Vec_self->ptr.elem_size);
    til_Ptr til_Ptr_dest = til_Ptr_offset(&til_Vec_self->ptr, &_tmp_til_Vec_set_7);
    til_Ptr_copy_from_dynamic(&til_Ptr_dest, (til_Dynamic*)til_Dynamic_value, &til_Vec_self->ptr.elem_size);
    return 0;
}

int til_Vec_pop(til_IndexOutOfBoundsError* _err1, til_Vec* til_Vec_self, til_Dynamic* til_Dynamic_dest) {
    til_I64 _tmp_til_Vec_pop_0 = 0;
    if (til_I64_eq(&til_Vec_self->_len, &_tmp_til_Vec_pop_0).data) {
        til_Str _tmp_til_Vec_pop_1;
        til_Array _tmp_til_Vec_pop_2;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Vec_pop_3;
        til_Str _tmp_til_Vec_pop_4 = ((til_Str){((til_Ptr){(til_I64)"Vec.pop: cannot pop from empty Vec", 1, 0, 0, 0}), 34, 0});
        til_Type _tmp_til_Vec_pop_5 = "Str";
        til_I64 _tmp_til_Vec_pop_6 = 1;
        _tmp_til_Vec_pop_2 = til_Array_new(_tmp_til_Vec_pop_5, &_tmp_til_Vec_pop_6);
        int __attribute__((unused)) _arr_status__tmp_til_Vec_pop_3;
        til_I64 _tmp_til_Vec_pop_7 = 0;
        _arr_status__tmp_til_Vec_pop_3 = til_Array_set(&_err_idx__tmp_til_Vec_pop_3, &_tmp_til_Vec_pop_2, &_tmp_til_Vec_pop_7, (til_Dynamic*)&_tmp_til_Vec_pop_4);
        _tmp_til_Vec_pop_1 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/vec.til:147:52:", 1, 0, 0, 0}), 24, 0}), &_tmp_til_Vec_pop_2);
        til_Array_delete(&_tmp_til_Vec_pop_2);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_til_Vec_pop_1};
        return 1;
    }
    til_I64 _tmp_til_Vec_pop_8 = 1;
    til_I64 til_I64_last_index = til_I64_sub(&til_Vec_self->_len, &_tmp_til_Vec_pop_8);
    til_I64 _tmp_til_Vec_pop_9 = til_I64_mul(&til_I64_last_index, &til_Vec_self->ptr.elem_size);
    til_Ptr til_Ptr_src = til_Ptr_offset(&til_Vec_self->ptr, &_tmp_til_Vec_pop_9);
    til_Ptr_copy_to_dynamic(&til_Ptr_src, (til_Dynamic*)til_Dynamic_dest, &til_Vec_self->ptr.elem_size);
    til_Vec_self->_len = til_I64_last_index;
    return 0;
}

void til_Vec_delete(til_Vec* til_Vec_self) {
    til_Bool _tmp_til_Vec_delete_0 = til_Ptr_is_null(&til_Vec_self->ptr);
    if (til_not(&_tmp_til_Vec_delete_0).data) {
        til_Ptr_delete(&til_Vec_self->ptr);
    }
    til_Vec_self->_len = 0;
    til_Vec_self->cap = 0;
}

til_Vec til_Vec_clone(const til_Vec* til_Vec_self) {
    til_Ptr _tmp_til_Vec_clone_0 = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    til_Vec til_Vec_cloned = {.ptr = _tmp_til_Vec_clone_0, ._len = 0, .cap = 0};
    til_Ptr til_Ptr_p = {.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    til_Ptr_p.elem_type = til_Vec_self->ptr.elem_type;
    til_Ptr_p.elem_size = til_Vec_self->ptr.elem_size;
    til_Vec_cloned.ptr = til_Ptr_p;
    til_Vec_cloned._len = til_Vec_self->_len;
    til_Vec_cloned.cap = til_Vec_self->cap;
    til_I64 _tmp_til_Vec_clone_1 = 0;
    if (til_I64_gt(&til_Vec_self->cap, &_tmp_til_Vec_clone_1).data) {
        til_Vec_cloned.ptr = til_Vec__alloc_ptr(&til_Vec_cloned, &til_Vec_self->cap);
        til_I64 _tmp_til_Vec_clone_2 = 0;
        if (til_I64_gt(&til_Vec_self->_len, &_tmp_til_Vec_clone_2).data) {
            til_I64 _tmp_til_Vec_clone_3 = til_I64_mul(&til_Vec_self->_len, &til_Vec_self->ptr.elem_size);
            til_Ptr_copy_from(&til_Vec_cloned.ptr, &til_Vec_self->ptr, &_tmp_til_Vec_clone_3);
        }
    }
    return til_Vec_cloned;
    return (til_Vec){};
}

void til_Vec_extend(til_Vec* til_Vec_self, const til_Vec* til_Vec_other) {
    til_I64 til_I64_i = 0;
    til_Ptr til_Ptr_src;
    til_I64 til_I64_new_cap;
    til_Ptr til_Ptr_new_ptr;
    til_Ptr til_Ptr_dest;
    while (til_I64_lt(&til_I64_i, &til_Vec_other->_len).data) {
        til_I64 _tmp_til_Vec_extend_0 = til_I64_mul(&til_I64_i, &til_Vec_other->ptr.elem_size);
        til_Ptr_src = til_Ptr_offset(&til_Vec_other->ptr, &_tmp_til_Vec_extend_0);
        if (til_I64_eq(&til_Vec_self->_len, &til_Vec_self->cap).data) {
            til_I64 _tmp_til_Vec_extend_1 = 2;
            til_I64_new_cap = til_I64_mul(&til_Vec_self->cap, &_tmp_til_Vec_extend_1);
            til_I64 _tmp_til_Vec_extend_2 = 1;
            if (til_I64_lt(&til_I64_new_cap, &_tmp_til_Vec_extend_2).data) {
                til_I64_new_cap = 1;
            }
            til_I64 _tmp_til_Vec_extend_3 = til_Vec_MAX_CAP;
            if (til_I64_gt(&til_I64_new_cap, &_tmp_til_Vec_extend_3).data) {
                til_Array _tmp_til_Vec_extend_4;
                til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Vec_extend_5;
                til_Type _tmp_til_Vec_extend_6 = "Str";
                til_I64 _tmp_til_Vec_extend_7 = 0;
                _tmp_til_Vec_extend_4 = til_Array_new(_tmp_til_Vec_extend_6, &_tmp_til_Vec_extend_7);
                int __attribute__((unused)) _arr_status__tmp_til_Vec_extend_5;
                til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/vec.til:202:27:", 1, 0, 0, 0}), 24, 0}), &((til_Str){((til_Ptr){(til_I64)"Vec.extend: capacity exceeded Vec.MAX_CAP", 1, 0, 0, 0}), 41, 0}), &_tmp_til_Vec_extend_4);
                til_Array_delete(&_tmp_til_Vec_extend_4);
            }
            til_Ptr_new_ptr = til_Vec__alloc_ptr(til_Vec_self, &til_I64_new_cap);
            til_I64 _tmp_til_Vec_extend_8 = 0;
            if (til_I64_gt(&til_Vec_self->_len, &_tmp_til_Vec_extend_8).data) {
                til_I64 _tmp_til_Vec_extend_9 = til_I64_mul(&til_Vec_self->_len, &til_Vec_self->ptr.elem_size);
                til_Ptr_copy_from(&til_Ptr_new_ptr, &til_Vec_self->ptr, &_tmp_til_Vec_extend_9);
            }
            til_Bool _tmp_til_Vec_extend_10 = til_Ptr_is_null(&til_Vec_self->ptr);
            if (til_not(&_tmp_til_Vec_extend_10).data) {
                til_Ptr_delete(&til_Vec_self->ptr);
            }
            til_Vec_self->ptr = til_Ptr_new_ptr;
            til_Vec_self->cap = til_I64_new_cap;
        }
        til_I64 _tmp_til_Vec_extend_11 = til_I64_mul(&til_Vec_self->_len, &til_Vec_self->ptr.elem_size);
        til_Ptr_dest = til_Ptr_offset(&til_Vec_self->ptr, &_tmp_til_Vec_extend_11);
        til_Ptr_copy_from(&til_Ptr_dest, &til_Ptr_src, &til_Vec_self->ptr.elem_size);
        til_I64 _tmp_til_Vec_extend_12 = 1;
        til_Vec_self->_len = til_I64_add(&til_Vec_self->_len, &_tmp_til_Vec_extend_12);
        til_I64 _tmp_til_Vec_extend_13 = 1;
        til_I64_i = til_I64_add(&til_I64_i, &_tmp_til_Vec_extend_13);
    }
}

void til_Vec_extend_with(til_Vec* til_Vec_self, til_Dynamic* til_Dynamic_value, const til_I64* til_I64_count) {
    til_I64 _loop_0 = 0;
    til_I64 til_I64_new_cap;
    til_Ptr til_Ptr_new_ptr;
    til_Ptr til_Ptr_dest;
    til_I64 _tmp_til_Vec_extend_with_0 = 0;
    if (til_I64_lt(&_tmp_til_Vec_extend_with_0, til_I64_count).data) {
        while (til_I64_lt(&_loop_0, til_I64_count).data) {
            if (til_I64_eq(&til_Vec_self->_len, &til_Vec_self->cap).data) {
                til_I64 _tmp_til_Vec_extend_with_1 = 2;
                til_I64_new_cap = til_I64_mul(&til_Vec_self->cap, &_tmp_til_Vec_extend_with_1);
                til_I64 _tmp_til_Vec_extend_with_2 = 1;
                if (til_I64_lt(&til_I64_new_cap, &_tmp_til_Vec_extend_with_2).data) {
                    til_I64_new_cap = 1;
                }
                til_I64 _tmp_til_Vec_extend_with_3 = til_Vec_MAX_CAP;
                if (til_I64_gt(&til_I64_new_cap, &_tmp_til_Vec_extend_with_3).data) {
                    til_Array _tmp_til_Vec_extend_with_4;
                    til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Vec_extend_with_5;
                    til_Type _tmp_til_Vec_extend_with_6 = "Str";
                    til_I64 _tmp_til_Vec_extend_with_7 = 0;
                    _tmp_til_Vec_extend_with_4 = til_Array_new(_tmp_til_Vec_extend_with_6, &_tmp_til_Vec_extend_with_7);
                    int __attribute__((unused)) _arr_status__tmp_til_Vec_extend_with_5;
                    til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/vec.til:234:27:", 1, 0, 0, 0}), 24, 0}), &((til_Str){((til_Ptr){(til_I64)"Vec.extend_with: capacity exceeded Vec.MAX_CAP", 1, 0, 0, 0}), 46, 0}), &_tmp_til_Vec_extend_with_4);
                    til_Array_delete(&_tmp_til_Vec_extend_with_4);
                }
                til_Ptr_new_ptr = til_Vec__alloc_ptr(til_Vec_self, &til_I64_new_cap);
                til_I64 _tmp_til_Vec_extend_with_8 = 0;
                if (til_I64_gt(&til_Vec_self->_len, &_tmp_til_Vec_extend_with_8).data) {
                    til_I64 _tmp_til_Vec_extend_with_9 = til_I64_mul(&til_Vec_self->_len, &til_Vec_self->ptr.elem_size);
                    til_Ptr_copy_from(&til_Ptr_new_ptr, &til_Vec_self->ptr, &_tmp_til_Vec_extend_with_9);
                }
                til_Bool _tmp_til_Vec_extend_with_10 = til_Ptr_is_null(&til_Vec_self->ptr);
                if (til_not(&_tmp_til_Vec_extend_with_10).data) {
                    til_Ptr_delete(&til_Vec_self->ptr);
                }
                til_Vec_self->ptr = til_Ptr_new_ptr;
                til_Vec_self->cap = til_I64_new_cap;
            }
            til_I64 _tmp_til_Vec_extend_with_11 = til_I64_mul(&til_Vec_self->_len, &til_Vec_self->ptr.elem_size);
            til_Ptr_dest = til_Ptr_offset(&til_Vec_self->ptr, &_tmp_til_Vec_extend_with_11);
            til_Ptr_copy_from_dynamic(&til_Ptr_dest, (til_Dynamic*)til_Dynamic_value, &til_Vec_self->ptr.elem_size);
            til_I64 _tmp_til_Vec_extend_with_12 = 1;
            til_Vec_self->_len = til_I64_add(&til_Vec_self->_len, &_tmp_til_Vec_extend_with_12);
            til_I64_inc(&_loop_0);
        }
    } else {
        while (til_I64_gt(&_loop_0, til_I64_count).data) {
            if (til_I64_eq(&til_Vec_self->_len, &til_Vec_self->cap).data) {
                til_I64 _tmp_til_Vec_extend_with_13 = 2;
                til_I64_new_cap = til_I64_mul(&til_Vec_self->cap, &_tmp_til_Vec_extend_with_13);
                til_I64 _tmp_til_Vec_extend_with_14 = 1;
                if (til_I64_lt(&til_I64_new_cap, &_tmp_til_Vec_extend_with_14).data) {
                    til_I64_new_cap = 1;
                }
                til_I64 _tmp_til_Vec_extend_with_15 = til_Vec_MAX_CAP;
                if (til_I64_gt(&til_I64_new_cap, &_tmp_til_Vec_extend_with_15).data) {
                    til_Array _tmp_til_Vec_extend_with_16;
                    til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Vec_extend_with_17;
                    til_Type _tmp_til_Vec_extend_with_18 = "Str";
                    til_I64 _tmp_til_Vec_extend_with_19 = 0;
                    _tmp_til_Vec_extend_with_16 = til_Array_new(_tmp_til_Vec_extend_with_18, &_tmp_til_Vec_extend_with_19);
                    int __attribute__((unused)) _arr_status__tmp_til_Vec_extend_with_17;
                    til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/vec.til:234:27:", 1, 0, 0, 0}), 24, 0}), &((til_Str){((til_Ptr){(til_I64)"Vec.extend_with: capacity exceeded Vec.MAX_CAP", 1, 0, 0, 0}), 46, 0}), &_tmp_til_Vec_extend_with_16);
                    til_Array_delete(&_tmp_til_Vec_extend_with_16);
                }
                til_Ptr_new_ptr = til_Vec__alloc_ptr(til_Vec_self, &til_I64_new_cap);
                til_I64 _tmp_til_Vec_extend_with_20 = 0;
                if (til_I64_gt(&til_Vec_self->_len, &_tmp_til_Vec_extend_with_20).data) {
                    til_I64 _tmp_til_Vec_extend_with_21 = til_I64_mul(&til_Vec_self->_len, &til_Vec_self->ptr.elem_size);
                    til_Ptr_copy_from(&til_Ptr_new_ptr, &til_Vec_self->ptr, &_tmp_til_Vec_extend_with_21);
                }
                til_Bool _tmp_til_Vec_extend_with_22 = til_Ptr_is_null(&til_Vec_self->ptr);
                if (til_not(&_tmp_til_Vec_extend_with_22).data) {
                    til_Ptr_delete(&til_Vec_self->ptr);
                }
                til_Vec_self->ptr = til_Ptr_new_ptr;
                til_Vec_self->cap = til_I64_new_cap;
            }
            til_I64 _tmp_til_Vec_extend_with_23 = til_I64_mul(&til_Vec_self->_len, &til_Vec_self->ptr.elem_size);
            til_Ptr_dest = til_Ptr_offset(&til_Vec_self->ptr, &_tmp_til_Vec_extend_with_23);
            til_Ptr_copy_from_dynamic(&til_Ptr_dest, (til_Dynamic*)til_Dynamic_value, &til_Vec_self->ptr.elem_size);
            til_I64 _tmp_til_Vec_extend_with_24 = 1;
            til_Vec_self->_len = til_I64_add(&til_Vec_self->_len, &_tmp_til_Vec_extend_with_24);
            til_I64_dec(&_loop_0);
        }
    }
}

til_Bool til_Vec_contains(const til_Vec* til_Vec_self, const til_Dynamic* til_Dynamic_value) {
    til_I64 til_I64_i = 0;
    til_Ptr til_Ptr_src;
    til_Str til_Str_existing;
    til_Str til_Str_val_str;
    while (til_I64_lt(&til_I64_i, &til_Vec_self->_len).data) {
        til_I64 _tmp_til_Vec_contains_0 = til_I64_mul(&til_I64_i, &til_Vec_self->ptr.elem_size);
        til_Ptr_src = til_Ptr_offset(&til_Vec_self->ptr, &_tmp_til_Vec_contains_0);
        if (til_Vec__is_str_type(til_Vec_self).data) {
            til_Str_existing = ((til_Str){((til_Ptr){(til_I64)"", 1, 0, 0, 0}), 0, 0});
            til_Ptr_copy_to_dynamic(&til_Ptr_src, (til_Dynamic*)&til_Str_existing, &til_Vec_self->ptr.elem_size);
            til_Str_val_str = ((til_Str){((til_Ptr){(til_I64)"", 1, 0, 0, 0}), 0, 0});
            til_I64 _tmp_til_Vec_contains_1 = (til_I64)&til_Str_val_str;
            til_I64 _tmp_til_Vec_contains_2 = (til_I64)til_Dynamic_value;
            til_memcpy(&_tmp_til_Vec_contains_1, &_tmp_til_Vec_contains_2, &til_Vec_self->ptr.elem_size);
            if (til_Str_eq(&til_Str_val_str, &til_Str_existing).data) {
                return true;
            }
        } else {
            til_I64 _tmp_til_Vec_contains_3 = (til_I64)til_Dynamic_value;
            til_I64 _tmp_til_Vec_contains_4 = til_memcmp(&_tmp_til_Vec_contains_3, &til_Ptr_src.data, &til_Vec_self->ptr.elem_size);
            til_I64 _tmp_til_Vec_contains_5 = 0;
            if (til_I64_eq(&_tmp_til_Vec_contains_4, &_tmp_til_Vec_contains_5).data) {
                return true;
            }
        }
        til_I64 _tmp_til_Vec_contains_6 = 1;
        til_I64_i = til_I64_add(&til_I64_i, &_tmp_til_Vec_contains_6);
    }
    return false;
    return (til_Bool){};
}

int til_Vec_remove(til_IndexOutOfBoundsError* _err1, til_Vec* til_Vec_self, const til_I64* til_I64_index) {
    if (til_I64_gteq(til_I64_index, &til_Vec_self->_len).data) {
        til_Str _tmp_til_Vec_remove_0;
        til_Array _tmp_til_Vec_remove_1;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Vec_remove_2;
        til_Str _tmp_til_Vec_remove_3 = ((til_Str){((til_Ptr){(til_I64)"Vec.remove: index out of bounds", 1, 0, 0, 0}), 31, 0});
        til_Type _tmp_til_Vec_remove_4 = "Str";
        til_I64 _tmp_til_Vec_remove_5 = 1;
        _tmp_til_Vec_remove_1 = til_Array_new(_tmp_til_Vec_remove_4, &_tmp_til_Vec_remove_5);
        int __attribute__((unused)) _arr_status__tmp_til_Vec_remove_2;
        til_I64 _tmp_til_Vec_remove_6 = 0;
        _arr_status__tmp_til_Vec_remove_2 = til_Array_set(&_err_idx__tmp_til_Vec_remove_2, &_tmp_til_Vec_remove_1, &_tmp_til_Vec_remove_6, (til_Dynamic*)&_tmp_til_Vec_remove_3);
        _tmp_til_Vec_remove_0 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/vec.til:282:52:", 1, 0, 0, 0}), 24, 0}), &_tmp_til_Vec_remove_1);
        til_Array_delete(&_tmp_til_Vec_remove_1);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_til_Vec_remove_0};
        return 1;
    }
    til_I64 til_I64_i = til_I64_clone(til_I64_index);
    til_Ptr til_Ptr_src;
    til_Ptr til_Ptr_dest;
    while (1) {
        til_I64 _tmp_til_Vec_remove_7 = 1;
        til_I64 _tmp_til_Vec_remove_8 = til_I64_sub(&til_Vec_self->_len, &_tmp_til_Vec_remove_7);
        if (!(til_I64_lt(&til_I64_i, &_tmp_til_Vec_remove_8).data)) break;
        til_I64 _tmp_til_Vec_remove_9 = 1;
        til_I64 _tmp_til_Vec_remove_10 = til_I64_add(&til_I64_i, &_tmp_til_Vec_remove_9);
        til_I64 _tmp_til_Vec_remove_11 = til_I64_mul(&_tmp_til_Vec_remove_10, &til_Vec_self->ptr.elem_size);
        til_Ptr_src = til_Ptr_offset(&til_Vec_self->ptr, &_tmp_til_Vec_remove_11);
        til_I64 _tmp_til_Vec_remove_12 = til_I64_mul(&til_I64_i, &til_Vec_self->ptr.elem_size);
        til_Ptr_dest = til_Ptr_offset(&til_Vec_self->ptr, &_tmp_til_Vec_remove_12);
        til_Ptr_copy_from(&til_Ptr_dest, &til_Ptr_src, &til_Vec_self->ptr.elem_size);
        til_I64 _tmp_til_Vec_remove_13 = 1;
        til_I64_i = til_I64_add(&til_I64_i, &_tmp_til_Vec_remove_13);
    }
    til_I64 _tmp_til_Vec_remove_14 = 1;
    til_Vec_self->_len = til_I64_sub(&til_Vec_self->_len, &_tmp_til_Vec_remove_14);
    return 0;
}

int til_Vec_insert_at(til_IndexOutOfBoundsError* _err1, til_Vec* til_Vec_self, const til_I64* til_I64_index, til_Dynamic* til_Dynamic_value) {
    if (til_I64_gt(til_I64_index, &til_Vec_self->_len).data) {
        til_Str _tmp_til_Vec_insert_at_0;
        til_Array _tmp_til_Vec_insert_at_1;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Vec_insert_at_2;
        til_Str _tmp_til_Vec_insert_at_3 = ((til_Str){((til_Ptr){(til_I64)"Vec.insert_at: index out of bounds", 1, 0, 0, 0}), 34, 0});
        til_Type _tmp_til_Vec_insert_at_4 = "Str";
        til_I64 _tmp_til_Vec_insert_at_5 = 1;
        _tmp_til_Vec_insert_at_1 = til_Array_new(_tmp_til_Vec_insert_at_4, &_tmp_til_Vec_insert_at_5);
        int __attribute__((unused)) _arr_status__tmp_til_Vec_insert_at_2;
        til_I64 _tmp_til_Vec_insert_at_6 = 0;
        _arr_status__tmp_til_Vec_insert_at_2 = til_Array_set(&_err_idx__tmp_til_Vec_insert_at_2, &_tmp_til_Vec_insert_at_1, &_tmp_til_Vec_insert_at_6, (til_Dynamic*)&_tmp_til_Vec_insert_at_3);
        _tmp_til_Vec_insert_at_0 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/vec.til:302:52:", 1, 0, 0, 0}), 24, 0}), &_tmp_til_Vec_insert_at_1);
        til_Array_delete(&_tmp_til_Vec_insert_at_1);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_til_Vec_insert_at_0};
        return 1;
    }
    til_I64 til_I64_new_cap;
    til_Ptr til_Ptr_new_ptr;
    if (til_I64_eq(&til_Vec_self->_len, &til_Vec_self->cap).data) {
        til_I64 _tmp_til_Vec_insert_at_7 = 2;
        til_I64_new_cap = til_I64_mul(&til_Vec_self->cap, &_tmp_til_Vec_insert_at_7);
        til_I64 _tmp_til_Vec_insert_at_8 = 1;
        if (til_I64_lt(&til_I64_new_cap, &_tmp_til_Vec_insert_at_8).data) {
            til_I64_new_cap = 1;
        }
        til_I64 _tmp_til_Vec_insert_at_9 = til_Vec_MAX_CAP;
        if (til_I64_gt(&til_I64_new_cap, &_tmp_til_Vec_insert_at_9).data) {
            til_Array _tmp_til_Vec_insert_at_10;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Vec_insert_at_11;
            til_Type _tmp_til_Vec_insert_at_12 = "Str";
            til_I64 _tmp_til_Vec_insert_at_13 = 0;
            _tmp_til_Vec_insert_at_10 = til_Array_new(_tmp_til_Vec_insert_at_12, &_tmp_til_Vec_insert_at_13);
            int __attribute__((unused)) _arr_status__tmp_til_Vec_insert_at_11;
            til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/vec.til:312:23:", 1, 0, 0, 0}), 24, 0}), &((til_Str){((til_Ptr){(til_I64)"Vec.insert_at: capacity exceeded Vec.MAX_CAP", 1, 0, 0, 0}), 44, 0}), &_tmp_til_Vec_insert_at_10);
            til_Array_delete(&_tmp_til_Vec_insert_at_10);
        }
        til_Ptr_new_ptr = til_Vec__alloc_ptr(til_Vec_self, &til_I64_new_cap);
        til_I64 _tmp_til_Vec_insert_at_14 = 0;
        if (til_I64_gt(&til_Vec_self->_len, &_tmp_til_Vec_insert_at_14).data) {
            til_I64 _tmp_til_Vec_insert_at_15 = til_I64_mul(&til_Vec_self->_len, &til_Vec_self->ptr.elem_size);
            til_Ptr_copy_from(&til_Ptr_new_ptr, &til_Vec_self->ptr, &_tmp_til_Vec_insert_at_15);
        }
        til_Bool _tmp_til_Vec_insert_at_16 = til_Ptr_is_null(&til_Vec_self->ptr);
        if (til_not(&_tmp_til_Vec_insert_at_16).data) {
            til_Ptr_delete(&til_Vec_self->ptr);
        }
        til_Vec_self->ptr = til_Ptr_new_ptr;
        til_Vec_self->cap = til_I64_new_cap;
    }
    til_I64 til_I64_i = til_I64_clone(&til_Vec_self->_len);
    til_Ptr til_Ptr_shift_src;
    til_Ptr til_Ptr_shift_dest;
    while (til_I64_gt(&til_I64_i, til_I64_index).data) {
        til_I64 _tmp_til_Vec_insert_at_17 = 1;
        til_I64 _tmp_til_Vec_insert_at_18 = til_I64_sub(&til_I64_i, &_tmp_til_Vec_insert_at_17);
        til_I64 _tmp_til_Vec_insert_at_19 = til_I64_mul(&_tmp_til_Vec_insert_at_18, &til_Vec_self->ptr.elem_size);
        til_Ptr_shift_src = til_Ptr_offset(&til_Vec_self->ptr, &_tmp_til_Vec_insert_at_19);
        til_I64 _tmp_til_Vec_insert_at_20 = til_I64_mul(&til_I64_i, &til_Vec_self->ptr.elem_size);
        til_Ptr_shift_dest = til_Ptr_offset(&til_Vec_self->ptr, &_tmp_til_Vec_insert_at_20);
        til_Ptr_copy_from(&til_Ptr_shift_dest, &til_Ptr_shift_src, &til_Vec_self->ptr.elem_size);
        til_I64 _tmp_til_Vec_insert_at_21 = 1;
        til_I64_i = til_I64_sub(&til_I64_i, &_tmp_til_Vec_insert_at_21);
    }
    til_I64 _tmp_til_Vec_insert_at_22 = til_I64_mul(til_I64_index, &til_Vec_self->ptr.elem_size);
    til_Ptr til_Ptr_insert_dest = til_Ptr_offset(&til_Vec_self->ptr, &_tmp_til_Vec_insert_at_22);
    til_Ptr_copy_from_dynamic(&til_Ptr_insert_dest, (til_Dynamic*)til_Dynamic_value, &til_Vec_self->ptr.elem_size);
    til_I64 _tmp_til_Vec_insert_at_23 = 1;
    til_Vec_self->_len = til_I64_add(&til_Vec_self->_len, &_tmp_til_Vec_insert_at_23);
    return 0;
}

til_Str til_Vec_to_str(const til_Vec* til_Vec_self) {
    til_Str til_Str_result = ((til_Str){((til_Ptr){(til_I64)"[", 1, 0, 0, 0}), 1, 0});
    til_I64 til_I64_i = 0;
    til_Str til_Str_elem;
    til_Ptr til_Ptr_src;
    til_I64 _tmp_til_Vec_to_str_0 = 0;
    if (til_I64_lt(&_tmp_til_Vec_to_str_0, &til_Vec_self->_len).data) {
        while (til_I64_lt(&til_I64_i, &til_Vec_self->_len).data) {
            til_I64 _tmp_til_Vec_to_str_1 = 0;
            if (til_I64_gt(&til_I64_i, &_tmp_til_Vec_to_str_1).data) {
                til_Str_result = til_concat(&til_Str_result, &((til_Str){((til_Ptr){(til_I64)", ", 1, 0, 0, 0}), 2, 0}));
            }
            if (til_Vec__is_str_type(til_Vec_self).data) {
                til_Str_elem = ((til_Str){((til_Ptr){(til_I64)"", 1, 0, 0, 0}), 0, 0});
                til_I64 _tmp_til_Vec_to_str_2 = til_I64_mul(&til_I64_i, &til_Vec_self->ptr.elem_size);
                til_Ptr_src = til_Ptr_offset(&til_Vec_self->ptr, &_tmp_til_Vec_to_str_2);
                til_Ptr_copy_to_dynamic(&til_Ptr_src, (til_Dynamic*)&til_Str_elem, &til_Vec_self->ptr.elem_size);
                til_Str _tmp_til_Vec_to_str_3 = til_concat(&til_Str_result, &((til_Str){((til_Ptr){(til_I64)"\"", 1, 0, 0, 0}), 1, 0}));
                til_Str _tmp_til_Vec_to_str_4 = til_concat(&_tmp_til_Vec_to_str_3, &til_Str_elem);
                til_Str_result = til_concat(&_tmp_til_Vec_to_str_4, &((til_Str){((til_Ptr){(til_I64)"\"", 1, 0, 0, 0}), 1, 0}));
            }
            til_I64_inc(&til_I64_i);
        }
    } else {
        while (til_I64_gt(&til_I64_i, &til_Vec_self->_len).data) {
            til_I64 _tmp_til_Vec_to_str_5 = 0;
            if (til_I64_gt(&til_I64_i, &_tmp_til_Vec_to_str_5).data) {
                til_Str_result = til_concat(&til_Str_result, &((til_Str){((til_Ptr){(til_I64)", ", 1, 0, 0, 0}), 2, 0}));
            }
            if (til_Vec__is_str_type(til_Vec_self).data) {
                til_Str_elem = ((til_Str){((til_Ptr){(til_I64)"", 1, 0, 0, 0}), 0, 0});
                til_I64 _tmp_til_Vec_to_str_6 = til_I64_mul(&til_I64_i, &til_Vec_self->ptr.elem_size);
                til_Ptr_src = til_Ptr_offset(&til_Vec_self->ptr, &_tmp_til_Vec_to_str_6);
                til_Ptr_copy_to_dynamic(&til_Ptr_src, (til_Dynamic*)&til_Str_elem, &til_Vec_self->ptr.elem_size);
                til_Str _tmp_til_Vec_to_str_7 = til_concat(&til_Str_result, &((til_Str){((til_Ptr){(til_I64)"\"", 1, 0, 0, 0}), 1, 0}));
                til_Str _tmp_til_Vec_to_str_8 = til_concat(&_tmp_til_Vec_to_str_7, &til_Str_elem);
                til_Str_result = til_concat(&_tmp_til_Vec_to_str_8, &((til_Str){((til_Ptr){(til_I64)"\"", 1, 0, 0, 0}), 1, 0}));
            }
            til_I64_dec(&til_I64_i);
        }
    }
    til_Str_result = til_concat(&til_Str_result, &((til_Str){((til_Ptr){(til_I64)"]", 1, 0, 0, 0}), 1, 0}));
    return til_Str_result;
    return (til_Str){};
}

til_Bool til_Vec_is_empty(const til_Vec* til_Vec_self) {
    til_I64 _tmp_til_Vec_is_empty_0 = 0;
    return til_I64_eq(&til_Vec_self->_len, &_tmp_til_Vec_is_empty_0);
    return (til_Bool){};
}

int til_Vec_split_off(til_Vec* _ret, til_IndexOutOfBoundsError* _err1, til_Vec* til_Vec_self, const til_I64* til_I64_at) {
    if (til_I64_gt(til_I64_at, &til_Vec_self->_len).data) {
        til_Str _tmp_til_Vec_split_off_0;
        til_Array _tmp_til_Vec_split_off_1;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Vec_split_off_2;
        til_Str _tmp_til_Vec_split_off_3 = ((til_Str){((til_Ptr){(til_I64)"Vec.split_off: index out of bounds", 1, 0, 0, 0}), 34, 0});
        til_Type _tmp_til_Vec_split_off_4 = "Str";
        til_I64 _tmp_til_Vec_split_off_5 = 1;
        _tmp_til_Vec_split_off_1 = til_Array_new(_tmp_til_Vec_split_off_4, &_tmp_til_Vec_split_off_5);
        int __attribute__((unused)) _arr_status__tmp_til_Vec_split_off_2;
        til_I64 _tmp_til_Vec_split_off_6 = 0;
        _arr_status__tmp_til_Vec_split_off_2 = til_Array_set(&_err_idx__tmp_til_Vec_split_off_2, &_tmp_til_Vec_split_off_1, &_tmp_til_Vec_split_off_6, (til_Dynamic*)&_tmp_til_Vec_split_off_3);
        _tmp_til_Vec_split_off_0 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/vec.til:371:52:", 1, 0, 0, 0}), 24, 0}), &_tmp_til_Vec_split_off_1);
        til_Array_delete(&_tmp_til_Vec_split_off_1);
        *_err1 = (til_IndexOutOfBoundsError){.msg = _tmp_til_Vec_split_off_0};
        return 1;
    }
    til_I64 til_I64_tail_len = til_I64_sub(&til_Vec_self->_len, til_I64_at);
    til_Ptr _tmp_til_Vec_split_off_7 = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    til_Vec til_Vec_result = {.ptr = _tmp_til_Vec_split_off_7, ._len = 0, .cap = 0};
    til_Ptr til_Ptr_p = {.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    til_Ptr_p.elem_type = til_Vec_self->ptr.elem_type;
    til_Ptr_p.elem_size = til_Vec_self->ptr.elem_size;
    til_Vec_result.ptr = til_Ptr_p;
    til_Vec_result._len = til_I64_tail_len;
    til_Ptr til_Ptr_src;
    til_I64 _tmp_til_Vec_split_off_8 = 0;
    if (til_I64_gt(&til_I64_tail_len, &_tmp_til_Vec_split_off_8).data) {
        til_Vec_result.cap = til_I64_tail_len;
        til_Vec_result.ptr = til_Vec__alloc_ptr(&til_Vec_result, &til_I64_tail_len);
        til_I64 _tmp_til_Vec_split_off_9 = til_I64_mul(til_I64_at, &til_Vec_self->ptr.elem_size);
        til_Ptr_src = til_Ptr_offset(&til_Vec_self->ptr, &_tmp_til_Vec_split_off_9);
        til_I64 _tmp_til_Vec_split_off_10 = til_I64_mul(&til_I64_tail_len, &til_Vec_self->ptr.elem_size);
        til_Ptr_copy_from(&til_Vec_result.ptr, &til_Ptr_src, &_tmp_til_Vec_split_off_10);
    }
    til_Vec_self->_len = (*til_I64_at);
    *_ret = til_Vec_result;
    return 0;
    return 0;
}

void til_Vec_clear(til_Vec* til_Vec_self) {
    til_Vec_self->_len = 0;
}

til_I64 til_Str_len(const til_Str* til_Str_self) {
    return til_Str_self->_len;
    return (til_I64){};
}

til_Bool til_Str_is_empty(const til_Str* til_Str_self) {
    til_I64 _tmp_til_Str_is_empty_0 = 0;
    return til_I64_eq(&til_Str_self->_len, &_tmp_til_Str_is_empty_0);
    return (til_Bool){};
}

til_Bool til_Str_eq(const til_Str* til_Str_self, const til_Str* til_Str_other) {
    til_Bool _tmp_til_Str_eq_0 = til_I64_eq(&til_Str_self->_len, &til_Str_other->_len);
    if (til_not(&_tmp_til_Str_eq_0).data) {
        return false;
    }
    til_I64 til_I64_i = 0;
    til_U8 til_U8_self_byte;
    til_U8 til_U8_other_byte;
    til_I64 _tmp_til_Str_eq_1 = 0;
    if (til_I64_lt(&_tmp_til_Str_eq_1, &til_Str_self->_len).data) {
        while (til_I64_lt(&til_I64_i, &til_Str_self->_len).data) {
            til_U8_self_byte = 0;
            til_U8_other_byte = 0;
            til_I64 _tmp_til_Str_eq_2 = (til_I64)&til_U8_self_byte;
            til_I64 _tmp_til_Str_eq_3 = til_Ptr_offset(&til_Str_self->c_string, &til_I64_i).data;
            til_I64 _tmp_til_Str_eq_4 = 1;
            til_memcpy(&_tmp_til_Str_eq_2, &_tmp_til_Str_eq_3, &_tmp_til_Str_eq_4);
            til_I64 _tmp_til_Str_eq_5 = (til_I64)&til_U8_other_byte;
            til_I64 _tmp_til_Str_eq_6 = til_Ptr_offset(&til_Str_other->c_string, &til_I64_i).data;
            til_I64 _tmp_til_Str_eq_7 = 1;
            til_memcpy(&_tmp_til_Str_eq_5, &_tmp_til_Str_eq_6, &_tmp_til_Str_eq_7);
            til_Bool _tmp_til_Str_eq_8 = til_U8_eq(&til_U8_self_byte, &til_U8_other_byte);
            if (til_not(&_tmp_til_Str_eq_8).data) {
                return false;
            }
            til_I64_inc(&til_I64_i);
        }
    } else {
        while (til_I64_gt(&til_I64_i, &til_Str_self->_len).data) {
            til_U8_self_byte = 0;
            til_U8_other_byte = 0;
            til_I64 _tmp_til_Str_eq_9 = (til_I64)&til_U8_self_byte;
            til_I64 _tmp_til_Str_eq_10 = til_Ptr_offset(&til_Str_self->c_string, &til_I64_i).data;
            til_I64 _tmp_til_Str_eq_11 = 1;
            til_memcpy(&_tmp_til_Str_eq_9, &_tmp_til_Str_eq_10, &_tmp_til_Str_eq_11);
            til_I64 _tmp_til_Str_eq_12 = (til_I64)&til_U8_other_byte;
            til_I64 _tmp_til_Str_eq_13 = til_Ptr_offset(&til_Str_other->c_string, &til_I64_i).data;
            til_I64 _tmp_til_Str_eq_14 = 1;
            til_memcpy(&_tmp_til_Str_eq_12, &_tmp_til_Str_eq_13, &_tmp_til_Str_eq_14);
            til_Bool _tmp_til_Str_eq_15 = til_U8_eq(&til_U8_self_byte, &til_U8_other_byte);
            if (til_not(&_tmp_til_Str_eq_15).data) {
                return false;
            }
            til_I64_dec(&til_I64_i);
        }
    }
    return true;
    return (til_Bool){};
}

til_I64 til_Str_to_i64(const til_Str* til_Str_self) {
    return til_I64_from_str(til_Str_self);
    return (til_I64){};
}

til_Str til_Str_clone(const til_Str* til_Str_self) {
    til_Ptr _tmp_til_Str_clone_0 = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    til_Str til_Str_cloned = {.c_string = _tmp_til_Str_clone_0, ._len = 0, .cap = 0};
    til_Str_cloned._len = til_Str_self->_len;
    til_I64 _tmp_til_Str_clone_1 = 1;
    til_Str_cloned.cap = til_I64_add(&til_Str_cloned._len, &_tmp_til_Str_clone_1);
    til_Str_cloned.c_string = til_Ptr_new_by_size(&til_Str_cloned.cap);
    til_Str_cloned.c_string.is_borrowed = 0;
    til_Ptr_copy_from(&til_Str_cloned.c_string, &til_Str_self->c_string, &til_Str_self->_len);
    til_U8 til_U8_zero = 0;
    til_I64 _tmp_til_Str_clone_2 = til_Ptr_offset(&til_Str_cloned.c_string, &til_Str_cloned._len).data;
    til_I64 _tmp_til_Str_clone_3 = 1;
    til_memset(&_tmp_til_Str_clone_2, &til_U8_zero, &_tmp_til_Str_clone_3);
    return til_Str_cloned;
    return (til_Str){};
}

void til_Str_delete(til_Str* til_Str_self) {
    til_I64 _tmp_til_Str_delete_0 = 0;
    if (til_I64_gt(&til_Str_self->cap, &_tmp_til_Str_delete_0).data) {
        til_Ptr_delete(&til_Str_self->c_string);
    }
    til_Str_self->c_string = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    til_Str_self->_len = 0;
    til_Str_self->cap = 0;
}

til_Str til_Str_from_byte(const til_U8* til_U8_byte) {
    til_Ptr _tmp_til_Str_from_byte_0 = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    til_Str til_Str_s = {.c_string = _tmp_til_Str_from_byte_0, ._len = 0, .cap = 0};
    til_I64 _tmp_til_Str_from_byte_1 = 2;
    til_Str_s.c_string = til_Ptr_new_by_size(&_tmp_til_Str_from_byte_1);
    til_Str_s.c_string.is_borrowed = 0;
    til_Str_s._len = 1;
    til_Str_s.cap = 2;
    til_I64 _tmp_til_Str_from_byte_2 = (til_I64)&(*til_U8_byte);
    til_I64 _tmp_til_Str_from_byte_3 = 1;
    til_memcpy(&til_Str_s.c_string.data, &_tmp_til_Str_from_byte_2, &_tmp_til_Str_from_byte_3);
    til_U8 til_U8_zero = 0;
    til_I64 _tmp_til_Str_from_byte_4 = 1;
    til_I64 _tmp_til_Str_from_byte_5 = til_Ptr_offset(&til_Str_s.c_string, &_tmp_til_Str_from_byte_4).data;
    til_I64 _tmp_til_Str_from_byte_6 = (til_I64)&til_U8_zero;
    til_I64 _tmp_til_Str_from_byte_7 = 1;
    til_memcpy(&_tmp_til_Str_from_byte_5, &_tmp_til_Str_from_byte_6, &_tmp_til_Str_from_byte_7);
    return til_Str_s;
    return (til_Str){};
}

void til_Str_push_str(til_Str* til_Str_self, const til_Str* til_Str_s) {
    *til_Str_self = til_concat(til_Str_self, til_Str_s);
}

til_I64 til_Str_size(const til_Str* til_Str_self) {
    return til_Str_self->_len;
    return (til_I64){};
}

til_Bool til_Str_is_uppercase(const til_Str* til_Str_self) {
    til_I64 _tmp_til_Str_is_uppercase_0 = 0;
    if (til_I64_eq(&til_Str_self->_len, &_tmp_til_Str_is_uppercase_0).data) {
        return false;
    }
    til_I64 til_I64_i = 0;
    til_U8 til_U8_byte;
    til_I64 til_I64_byte_val;
    til_I64 _tmp_til_Str_is_uppercase_1 = 0;
    if (til_I64_lt(&_tmp_til_Str_is_uppercase_1, &til_Str_self->_len).data) {
        while (til_I64_lt(&til_I64_i, &til_Str_self->_len).data) {
            til_U8_byte = 0;
            til_I64 _tmp_til_Str_is_uppercase_2 = (til_I64)&til_U8_byte;
            til_I64 _tmp_til_Str_is_uppercase_3 = til_Ptr_offset(&til_Str_self->c_string, &til_I64_i).data;
            til_I64 _tmp_til_Str_is_uppercase_4 = 1;
            til_memcpy(&_tmp_til_Str_is_uppercase_2, &_tmp_til_Str_is_uppercase_3, &_tmp_til_Str_is_uppercase_4);
            til_I64_byte_val = 0;
            til_I64_byte_val = til_U8_to_i64(&til_U8_byte);
            til_I64 _tmp_til_Str_is_uppercase_5 = 65;
            if (til_I64_lt(&til_I64_byte_val, &_tmp_til_Str_is_uppercase_5).data) {
                return false;
            }
            til_I64 _tmp_til_Str_is_uppercase_6 = 90;
            if (til_I64_gt(&til_I64_byte_val, &_tmp_til_Str_is_uppercase_6).data) {
                return false;
            }
            til_I64_inc(&til_I64_i);
        }
    } else {
        while (til_I64_gt(&til_I64_i, &til_Str_self->_len).data) {
            til_U8_byte = 0;
            til_I64 _tmp_til_Str_is_uppercase_7 = (til_I64)&til_U8_byte;
            til_I64 _tmp_til_Str_is_uppercase_8 = til_Ptr_offset(&til_Str_self->c_string, &til_I64_i).data;
            til_I64 _tmp_til_Str_is_uppercase_9 = 1;
            til_memcpy(&_tmp_til_Str_is_uppercase_7, &_tmp_til_Str_is_uppercase_8, &_tmp_til_Str_is_uppercase_9);
            til_I64_byte_val = 0;
            til_I64_byte_val = til_U8_to_i64(&til_U8_byte);
            til_I64 _tmp_til_Str_is_uppercase_10 = 65;
            if (til_I64_lt(&til_I64_byte_val, &_tmp_til_Str_is_uppercase_10).data) {
                return false;
            }
            til_I64 _tmp_til_Str_is_uppercase_11 = 90;
            if (til_I64_gt(&til_I64_byte_val, &_tmp_til_Str_is_uppercase_11).data) {
                return false;
            }
            til_I64_dec(&til_I64_i);
        }
    }
    return true;
    return (til_Bool){};
}

til_Str til_Str_to_lowercase(const til_Str* til_Str_self) {
    til_Str til_Str_result = {};
    til_U8_Overflow _thrown_U8_Overflow__tmp_til_Str_to_lowercase_0 = {};
    til_Str_result = til_Str_clone(til_Str_self);
    til_I64 til_I64_i = 0;
    til_U8 til_U8_byte;
    til_I64 til_I64_byte_val;
    til_I64 _tmp_til_Str_to_lowercase_1 = 0;
    if (til_I64_lt(&_tmp_til_Str_to_lowercase_1, &til_Str_result._len).data) {
        while (til_I64_lt(&til_I64_i, &til_Str_result._len).data) {
            til_U8_byte = 0;
            til_I64 _tmp_til_Str_to_lowercase_2 = (til_I64)&til_U8_byte;
            til_I64 _tmp_til_Str_to_lowercase_3 = til_Ptr_offset(&til_Str_result.c_string, &til_I64_i).data;
            til_I64 _tmp_til_Str_to_lowercase_4 = 1;
            til_memcpy(&_tmp_til_Str_to_lowercase_2, &_tmp_til_Str_to_lowercase_3, &_tmp_til_Str_to_lowercase_4);
            til_I64_byte_val = 0;
            til_I64_byte_val = til_U8_to_i64(&til_U8_byte);
            til_I64 _tmp_til_Str_to_lowercase_5 = 65;
            if (til_I64_gteq(&til_I64_byte_val, &_tmp_til_Str_to_lowercase_5).data) {
                til_I64 _tmp_til_Str_to_lowercase_6 = 90;
                if (til_I64_lteq(&til_I64_byte_val, &_tmp_til_Str_to_lowercase_6).data) {
                    til_I64 _tmp_til_Str_to_lowercase_7 = 32;
                    til_I64_byte_val = til_I64_add(&til_I64_byte_val, &_tmp_til_Str_to_lowercase_7);
                    til_U8_Overflow _err0__tmp_til_Str_to_lowercase_8 = {};
                    int __attribute__((unused)) _status__tmp_til_Str_to_lowercase_8 = til_U8_from_i64(&til_U8_byte, &_err0__tmp_til_Str_to_lowercase_8, &til_I64_byte_val);
                    til_I64 _tmp_til_Str_to_lowercase_9 = til_Ptr_offset(&til_Str_result.c_string, &til_I64_i).data;
                    til_I64 _tmp_til_Str_to_lowercase_10 = (til_I64)&til_U8_byte;
                    til_I64 _tmp_til_Str_to_lowercase_11 = 1;
                    til_memcpy(&_tmp_til_Str_to_lowercase_9, &_tmp_til_Str_to_lowercase_10, &_tmp_til_Str_to_lowercase_11);
                }
            }
            til_I64_inc(&til_I64_i);
        }
    } else {
        while (til_I64_gt(&til_I64_i, &til_Str_result._len).data) {
            til_U8_byte = 0;
            til_I64 _tmp_til_Str_to_lowercase_12 = (til_I64)&til_U8_byte;
            til_I64 _tmp_til_Str_to_lowercase_13 = til_Ptr_offset(&til_Str_result.c_string, &til_I64_i).data;
            til_I64 _tmp_til_Str_to_lowercase_14 = 1;
            til_memcpy(&_tmp_til_Str_to_lowercase_12, &_tmp_til_Str_to_lowercase_13, &_tmp_til_Str_to_lowercase_14);
            til_I64_byte_val = 0;
            til_I64_byte_val = til_U8_to_i64(&til_U8_byte);
            til_I64 _tmp_til_Str_to_lowercase_15 = 65;
            if (til_I64_gteq(&til_I64_byte_val, &_tmp_til_Str_to_lowercase_15).data) {
                til_I64 _tmp_til_Str_to_lowercase_16 = 90;
                if (til_I64_lteq(&til_I64_byte_val, &_tmp_til_Str_to_lowercase_16).data) {
                    til_I64 _tmp_til_Str_to_lowercase_17 = 32;
                    til_I64_byte_val = til_I64_add(&til_I64_byte_val, &_tmp_til_Str_to_lowercase_17);
                    til_U8_Overflow _err0__tmp_til_Str_to_lowercase_18 = {};
                    int __attribute__((unused)) _status__tmp_til_Str_to_lowercase_18 = til_U8_from_i64(&til_U8_byte, &_err0__tmp_til_Str_to_lowercase_18, &til_I64_byte_val);
                    til_I64 _tmp_til_Str_to_lowercase_19 = til_Ptr_offset(&til_Str_result.c_string, &til_I64_i).data;
                    til_I64 _tmp_til_Str_to_lowercase_20 = (til_I64)&til_U8_byte;
                    til_I64 _tmp_til_Str_to_lowercase_21 = 1;
                    til_memcpy(&_tmp_til_Str_to_lowercase_19, &_tmp_til_Str_to_lowercase_20, &_tmp_til_Str_to_lowercase_21);
                }
            }
            til_I64_dec(&til_I64_i);
        }
    }
    if (0) { _catch_U8_Overflow__tmp_til_Str_to_lowercase_0:;
        til_U8_Overflow til_U8_Overflow_err = _thrown_U8_Overflow__tmp_til_Str_to_lowercase_0;
        til_Array _tmp_til_Str_to_lowercase_22;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_Str_to_lowercase_23;
        til_Type _tmp_til_Str_to_lowercase_24 = "Str";
        til_I64 _tmp_til_Str_to_lowercase_25 = 0;
        _tmp_til_Str_to_lowercase_22 = til_Array_new(_tmp_til_Str_to_lowercase_24, &_tmp_til_Str_to_lowercase_25);
        int __attribute__((unused)) _arr_status__tmp_til_Str_to_lowercase_23;
        til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/str.til:137:19:", 1, 0, 0, 0}), 24, 0}), &til_U8_Overflow_err.msg, &_tmp_til_Str_to_lowercase_22);
        til_Array_delete(&_tmp_til_Str_to_lowercase_22);
    }
    return til_Str_result;
    return (til_Str){};
}

til_Bool til_Str_contains(const til_Str* til_Str_self, const til_Str* til_Str_needle) {
    til_I64 _tmp_til_Str_contains_0 = til_Str_len(til_Str_needle);
    til_I64 _tmp_til_Str_contains_1 = til_Str_len(til_Str_self);
    if (til_I64_gt(&_tmp_til_Str_contains_0, &_tmp_til_Str_contains_1).data) {
        return false;
    }
    til_I64 _tmp_til_Str_contains_2 = til_Str_len(til_Str_needle);
    til_I64 _tmp_til_Str_contains_3 = 0;
    if (til_I64_eq(&_tmp_til_Str_contains_2, &_tmp_til_Str_contains_3).data) {
        return false;
    }
    til_I64 _tmp_til_Str_contains_4 = til_Str_len(til_Str_self);
    til_I64 _tmp_til_Str_contains_5 = til_Str_len(til_Str_needle);
    til_I64 til_I64_max_start = til_I64_sub(&_tmp_til_Str_contains_4, &_tmp_til_Str_contains_5);
    til_I64 til_I64_start_idx = 0;
    til_Bool til_Bool_matches;
    til_I64 til_I64_needle_idx;
    til_U8 til_U8_self_byte;
    til_U8 til_U8_needle_byte;
    til_I64 _tmp_til_Str_contains_6 = 0;
    til_I64 _tmp_til_Str_contains_7 = 1;
    til_I64 _tmp_til_Str_contains_8 = til_I64_add(&til_I64_max_start, &_tmp_til_Str_contains_7);
    if (til_I64_lt(&_tmp_til_Str_contains_6, &_tmp_til_Str_contains_8).data) {
        while (1) {
            til_I64 _tmp_til_Str_contains_9 = 1;
            til_I64 _tmp_til_Str_contains_10 = til_I64_add(&til_I64_max_start, &_tmp_til_Str_contains_9);
            if (!(til_I64_lt(&til_I64_start_idx, &_tmp_til_Str_contains_10).data)) break;
            til_Bool_matches = til_Bool_clone(&true);
            til_I64_needle_idx = 0;
            til_I64 _tmp_til_Str_contains_11 = 0;
            til_I64 _tmp_til_Str_contains_12 = til_Str_len(til_Str_needle);
            if (til_I64_lt(&_tmp_til_Str_contains_11, &_tmp_til_Str_contains_12).data) {
                while (1) {
                    til_I64 _tmp_til_Str_contains_13 = til_Str_len(til_Str_needle);
                    if (!(til_I64_lt(&til_I64_needle_idx, &_tmp_til_Str_contains_13).data)) break;
                    til_U8_self_byte = 0;
                    til_U8_needle_byte = 0;
                    til_I64 _tmp_til_Str_contains_14 = (til_I64)&til_U8_self_byte;
                    til_I64 _tmp_til_Str_contains_15 = til_I64_add(&til_I64_start_idx, &til_I64_needle_idx);
                    til_I64 _tmp_til_Str_contains_16 = til_Ptr_offset(&til_Str_self->c_string, &_tmp_til_Str_contains_15).data;
                    til_I64 _tmp_til_Str_contains_17 = 1;
                    til_memcpy(&_tmp_til_Str_contains_14, &_tmp_til_Str_contains_16, &_tmp_til_Str_contains_17);
                    til_I64 _tmp_til_Str_contains_18 = (til_I64)&til_U8_needle_byte;
                    til_I64 _tmp_til_Str_contains_19 = til_Ptr_offset(&til_Str_needle->c_string, &til_I64_needle_idx).data;
                    til_I64 _tmp_til_Str_contains_20 = 1;
                    til_memcpy(&_tmp_til_Str_contains_18, &_tmp_til_Str_contains_19, &_tmp_til_Str_contains_20);
                    til_Bool _tmp_til_Str_contains_21 = til_U8_eq(&til_U8_self_byte, &til_U8_needle_byte);
                    if (til_not(&_tmp_til_Str_contains_21).data) {
                        til_Bool_matches = til_Bool_clone(&false);
                    }
                    til_I64_inc(&til_I64_needle_idx);
                }
            } else {
                while (1) {
                    til_I64 _tmp_til_Str_contains_22 = til_Str_len(til_Str_needle);
                    if (!(til_I64_gt(&til_I64_needle_idx, &_tmp_til_Str_contains_22).data)) break;
                    til_U8_self_byte = 0;
                    til_U8_needle_byte = 0;
                    til_I64 _tmp_til_Str_contains_23 = (til_I64)&til_U8_self_byte;
                    til_I64 _tmp_til_Str_contains_24 = til_I64_add(&til_I64_start_idx, &til_I64_needle_idx);
                    til_I64 _tmp_til_Str_contains_25 = til_Ptr_offset(&til_Str_self->c_string, &_tmp_til_Str_contains_24).data;
                    til_I64 _tmp_til_Str_contains_26 = 1;
                    til_memcpy(&_tmp_til_Str_contains_23, &_tmp_til_Str_contains_25, &_tmp_til_Str_contains_26);
                    til_I64 _tmp_til_Str_contains_27 = (til_I64)&til_U8_needle_byte;
                    til_I64 _tmp_til_Str_contains_28 = til_Ptr_offset(&til_Str_needle->c_string, &til_I64_needle_idx).data;
                    til_I64 _tmp_til_Str_contains_29 = 1;
                    til_memcpy(&_tmp_til_Str_contains_27, &_tmp_til_Str_contains_28, &_tmp_til_Str_contains_29);
                    til_Bool _tmp_til_Str_contains_30 = til_U8_eq(&til_U8_self_byte, &til_U8_needle_byte);
                    if (til_not(&_tmp_til_Str_contains_30).data) {
                        til_Bool_matches = til_Bool_clone(&false);
                    }
                    til_I64_dec(&til_I64_needle_idx);
                }
            }
            if (til_Bool_matches.data) {
                return true;
            }
            til_I64_inc(&til_I64_start_idx);
        }
    } else {
        while (1) {
            til_I64 _tmp_til_Str_contains_31 = 1;
            til_I64 _tmp_til_Str_contains_32 = til_I64_add(&til_I64_max_start, &_tmp_til_Str_contains_31);
            if (!(til_I64_gt(&til_I64_start_idx, &_tmp_til_Str_contains_32).data)) break;
            til_Bool_matches = til_Bool_clone(&true);
            til_I64_needle_idx = 0;
            til_I64 _tmp_til_Str_contains_33 = 0;
            til_I64 _tmp_til_Str_contains_34 = til_Str_len(til_Str_needle);
            if (til_I64_lt(&_tmp_til_Str_contains_33, &_tmp_til_Str_contains_34).data) {
                while (1) {
                    til_I64 _tmp_til_Str_contains_35 = til_Str_len(til_Str_needle);
                    if (!(til_I64_lt(&til_I64_needle_idx, &_tmp_til_Str_contains_35).data)) break;
                    til_U8_self_byte = 0;
                    til_U8_needle_byte = 0;
                    til_I64 _tmp_til_Str_contains_36 = (til_I64)&til_U8_self_byte;
                    til_I64 _tmp_til_Str_contains_37 = til_I64_add(&til_I64_start_idx, &til_I64_needle_idx);
                    til_I64 _tmp_til_Str_contains_38 = til_Ptr_offset(&til_Str_self->c_string, &_tmp_til_Str_contains_37).data;
                    til_I64 _tmp_til_Str_contains_39 = 1;
                    til_memcpy(&_tmp_til_Str_contains_36, &_tmp_til_Str_contains_38, &_tmp_til_Str_contains_39);
                    til_I64 _tmp_til_Str_contains_40 = (til_I64)&til_U8_needle_byte;
                    til_I64 _tmp_til_Str_contains_41 = til_Ptr_offset(&til_Str_needle->c_string, &til_I64_needle_idx).data;
                    til_I64 _tmp_til_Str_contains_42 = 1;
                    til_memcpy(&_tmp_til_Str_contains_40, &_tmp_til_Str_contains_41, &_tmp_til_Str_contains_42);
                    til_Bool _tmp_til_Str_contains_43 = til_U8_eq(&til_U8_self_byte, &til_U8_needle_byte);
                    if (til_not(&_tmp_til_Str_contains_43).data) {
                        til_Bool_matches = til_Bool_clone(&false);
                    }
                    til_I64_inc(&til_I64_needle_idx);
                }
            } else {
                while (1) {
                    til_I64 _tmp_til_Str_contains_44 = til_Str_len(til_Str_needle);
                    if (!(til_I64_gt(&til_I64_needle_idx, &_tmp_til_Str_contains_44).data)) break;
                    til_U8_self_byte = 0;
                    til_U8_needle_byte = 0;
                    til_I64 _tmp_til_Str_contains_45 = (til_I64)&til_U8_self_byte;
                    til_I64 _tmp_til_Str_contains_46 = til_I64_add(&til_I64_start_idx, &til_I64_needle_idx);
                    til_I64 _tmp_til_Str_contains_47 = til_Ptr_offset(&til_Str_self->c_string, &_tmp_til_Str_contains_46).data;
                    til_I64 _tmp_til_Str_contains_48 = 1;
                    til_memcpy(&_tmp_til_Str_contains_45, &_tmp_til_Str_contains_47, &_tmp_til_Str_contains_48);
                    til_I64 _tmp_til_Str_contains_49 = (til_I64)&til_U8_needle_byte;
                    til_I64 _tmp_til_Str_contains_50 = til_Ptr_offset(&til_Str_needle->c_string, &til_I64_needle_idx).data;
                    til_I64 _tmp_til_Str_contains_51 = 1;
                    til_memcpy(&_tmp_til_Str_contains_49, &_tmp_til_Str_contains_50, &_tmp_til_Str_contains_51);
                    til_Bool _tmp_til_Str_contains_52 = til_U8_eq(&til_U8_self_byte, &til_U8_needle_byte);
                    if (til_not(&_tmp_til_Str_contains_52).data) {
                        til_Bool_matches = til_Bool_clone(&false);
                    }
                    til_I64_dec(&til_I64_needle_idx);
                }
            }
            if (til_Bool_matches.data) {
                return true;
            }
            til_I64_dec(&til_I64_start_idx);
        }
    }
    return false;
    return (til_Bool){};
}

til_I64 til_Str_find(const til_Str* til_Str_self, const til_Str* til_Str_needle) {
    til_I64 _tmp_til_Str_find_0 = til_Str_len(til_Str_needle);
    til_I64 _tmp_til_Str_find_1 = til_Str_len(til_Str_self);
    if (til_I64_gt(&_tmp_til_Str_find_0, &_tmp_til_Str_find_1).data) {
        til_I64 _tmp_til_Str_find_2 = 0;
        til_I64 _tmp_til_Str_find_3 = 1;
        return til_I64_sub(&_tmp_til_Str_find_2, &_tmp_til_Str_find_3);
    }
    til_I64 _tmp_til_Str_find_4 = til_Str_len(til_Str_needle);
    til_I64 _tmp_til_Str_find_5 = 0;
    if (til_I64_eq(&_tmp_til_Str_find_4, &_tmp_til_Str_find_5).data) {
        til_I64 _tmp_til_Str_find_6 = 0;
        til_I64 _tmp_til_Str_find_7 = 1;
        return til_I64_sub(&_tmp_til_Str_find_6, &_tmp_til_Str_find_7);
    }
    til_I64 _tmp_til_Str_find_8 = til_Str_len(til_Str_self);
    til_I64 _tmp_til_Str_find_9 = til_Str_len(til_Str_needle);
    til_I64 til_I64_max_start = til_I64_sub(&_tmp_til_Str_find_8, &_tmp_til_Str_find_9);
    til_I64 til_I64_start_idx = 0;
    til_Bool til_Bool_matches;
    til_I64 til_I64_needle_idx;
    til_U8 til_U8_self_byte;
    til_U8 til_U8_needle_byte;
    while (til_I64_lteq(&til_I64_start_idx, &til_I64_max_start).data) {
        til_Bool_matches = til_Bool_clone(&true);
        til_I64_needle_idx = 0;
        while (1) {
            til_I64 _tmp_til_Str_find_10 = til_Str_len(til_Str_needle);
            if (!(til_I64_lt(&til_I64_needle_idx, &_tmp_til_Str_find_10).data)) break;
            if (til_not(&til_Bool_matches).data) {
                til_I64_needle_idx = til_Str_len(til_Str_needle);
            } else {
                til_U8_self_byte = 0;
                til_U8_needle_byte = 0;
                til_I64 _tmp_til_Str_find_11 = (til_I64)&til_U8_self_byte;
                til_I64 _tmp_til_Str_find_12 = til_I64_add(&til_I64_start_idx, &til_I64_needle_idx);
                til_I64 _tmp_til_Str_find_13 = til_Ptr_offset(&til_Str_self->c_string, &_tmp_til_Str_find_12).data;
                til_I64 _tmp_til_Str_find_14 = 1;
                til_memcpy(&_tmp_til_Str_find_11, &_tmp_til_Str_find_13, &_tmp_til_Str_find_14);
                til_I64 _tmp_til_Str_find_15 = (til_I64)&til_U8_needle_byte;
                til_I64 _tmp_til_Str_find_16 = til_Ptr_offset(&til_Str_needle->c_string, &til_I64_needle_idx).data;
                til_I64 _tmp_til_Str_find_17 = 1;
                til_memcpy(&_tmp_til_Str_find_15, &_tmp_til_Str_find_16, &_tmp_til_Str_find_17);
                til_Bool _tmp_til_Str_find_18 = til_U8_eq(&til_U8_self_byte, &til_U8_needle_byte);
                if (til_not(&_tmp_til_Str_find_18).data) {
                    til_Bool_matches = til_Bool_clone(&false);
                }
                til_I64_inc(&til_I64_needle_idx);
            }
        }
        if (til_Bool_matches.data) {
            return til_I64_start_idx;
        }
        til_I64_inc(&til_I64_start_idx);
    }
    til_I64 _tmp_til_Str_find_19 = 0;
    til_I64 _tmp_til_Str_find_20 = 1;
    return til_I64_sub(&_tmp_til_Str_find_19, &_tmp_til_Str_find_20);
    return (til_I64){};
}

til_I64 til_Str_rfind(const til_Str* til_Str_self, const til_Str* til_Str_needle) {
    til_I64 _tmp_til_Str_rfind_0 = til_Str_len(til_Str_needle);
    til_I64 _tmp_til_Str_rfind_1 = til_Str_len(til_Str_self);
    if (til_I64_gt(&_tmp_til_Str_rfind_0, &_tmp_til_Str_rfind_1).data) {
        til_I64 _tmp_til_Str_rfind_2 = 0;
        til_I64 _tmp_til_Str_rfind_3 = 1;
        return til_I64_sub(&_tmp_til_Str_rfind_2, &_tmp_til_Str_rfind_3);
    }
    til_I64 _tmp_til_Str_rfind_4 = til_Str_len(til_Str_needle);
    til_I64 _tmp_til_Str_rfind_5 = 0;
    if (til_I64_eq(&_tmp_til_Str_rfind_4, &_tmp_til_Str_rfind_5).data) {
        til_I64 _tmp_til_Str_rfind_6 = 0;
        til_I64 _tmp_til_Str_rfind_7 = 1;
        return til_I64_sub(&_tmp_til_Str_rfind_6, &_tmp_til_Str_rfind_7);
    }
    til_I64 _tmp_til_Str_rfind_8 = 0;
    til_I64 _tmp_til_Str_rfind_9 = 1;
    til_I64 til_I64_last_found = til_I64_sub(&_tmp_til_Str_rfind_8, &_tmp_til_Str_rfind_9);
    til_I64 _tmp_til_Str_rfind_10 = til_Str_len(til_Str_self);
    til_I64 _tmp_til_Str_rfind_11 = til_Str_len(til_Str_needle);
    til_I64 til_I64_max_start = til_I64_sub(&_tmp_til_Str_rfind_10, &_tmp_til_Str_rfind_11);
    til_I64 til_I64_start_idx = 0;
    til_Bool til_Bool_matches;
    til_I64 til_I64_needle_idx;
    til_U8 til_U8_self_byte;
    til_U8 til_U8_needle_byte;
    til_I64 _tmp_til_Str_rfind_12 = 0;
    til_I64 _tmp_til_Str_rfind_13 = 1;
    til_I64 _tmp_til_Str_rfind_14 = til_I64_add(&til_I64_max_start, &_tmp_til_Str_rfind_13);
    if (til_I64_lt(&_tmp_til_Str_rfind_12, &_tmp_til_Str_rfind_14).data) {
        while (1) {
            til_I64 _tmp_til_Str_rfind_15 = 1;
            til_I64 _tmp_til_Str_rfind_16 = til_I64_add(&til_I64_max_start, &_tmp_til_Str_rfind_15);
            if (!(til_I64_lt(&til_I64_start_idx, &_tmp_til_Str_rfind_16).data)) break;
            til_Bool_matches = til_Bool_clone(&true);
            til_I64_needle_idx = 0;
            til_I64 _tmp_til_Str_rfind_17 = 0;
            til_I64 _tmp_til_Str_rfind_18 = til_Str_len(til_Str_needle);
            if (til_I64_lt(&_tmp_til_Str_rfind_17, &_tmp_til_Str_rfind_18).data) {
                while (1) {
                    til_I64 _tmp_til_Str_rfind_19 = til_Str_len(til_Str_needle);
                    if (!(til_I64_lt(&til_I64_needle_idx, &_tmp_til_Str_rfind_19).data)) break;
                    til_U8_self_byte = 0;
                    til_U8_needle_byte = 0;
                    til_I64 _tmp_til_Str_rfind_20 = (til_I64)&til_U8_self_byte;
                    til_I64 _tmp_til_Str_rfind_21 = til_I64_add(&til_I64_start_idx, &til_I64_needle_idx);
                    til_I64 _tmp_til_Str_rfind_22 = til_Ptr_offset(&til_Str_self->c_string, &_tmp_til_Str_rfind_21).data;
                    til_I64 _tmp_til_Str_rfind_23 = 1;
                    til_memcpy(&_tmp_til_Str_rfind_20, &_tmp_til_Str_rfind_22, &_tmp_til_Str_rfind_23);
                    til_I64 _tmp_til_Str_rfind_24 = (til_I64)&til_U8_needle_byte;
                    til_I64 _tmp_til_Str_rfind_25 = til_Ptr_offset(&til_Str_needle->c_string, &til_I64_needle_idx).data;
                    til_I64 _tmp_til_Str_rfind_26 = 1;
                    til_memcpy(&_tmp_til_Str_rfind_24, &_tmp_til_Str_rfind_25, &_tmp_til_Str_rfind_26);
                    til_Bool _tmp_til_Str_rfind_27 = til_U8_eq(&til_U8_self_byte, &til_U8_needle_byte);
                    if (til_not(&_tmp_til_Str_rfind_27).data) {
                        til_Bool_matches = til_Bool_clone(&false);
                    }
                    til_I64_inc(&til_I64_needle_idx);
                }
            } else {
                while (1) {
                    til_I64 _tmp_til_Str_rfind_28 = til_Str_len(til_Str_needle);
                    if (!(til_I64_gt(&til_I64_needle_idx, &_tmp_til_Str_rfind_28).data)) break;
                    til_U8_self_byte = 0;
                    til_U8_needle_byte = 0;
                    til_I64 _tmp_til_Str_rfind_29 = (til_I64)&til_U8_self_byte;
                    til_I64 _tmp_til_Str_rfind_30 = til_I64_add(&til_I64_start_idx, &til_I64_needle_idx);
                    til_I64 _tmp_til_Str_rfind_31 = til_Ptr_offset(&til_Str_self->c_string, &_tmp_til_Str_rfind_30).data;
                    til_I64 _tmp_til_Str_rfind_32 = 1;
                    til_memcpy(&_tmp_til_Str_rfind_29, &_tmp_til_Str_rfind_31, &_tmp_til_Str_rfind_32);
                    til_I64 _tmp_til_Str_rfind_33 = (til_I64)&til_U8_needle_byte;
                    til_I64 _tmp_til_Str_rfind_34 = til_Ptr_offset(&til_Str_needle->c_string, &til_I64_needle_idx).data;
                    til_I64 _tmp_til_Str_rfind_35 = 1;
                    til_memcpy(&_tmp_til_Str_rfind_33, &_tmp_til_Str_rfind_34, &_tmp_til_Str_rfind_35);
                    til_Bool _tmp_til_Str_rfind_36 = til_U8_eq(&til_U8_self_byte, &til_U8_needle_byte);
                    if (til_not(&_tmp_til_Str_rfind_36).data) {
                        til_Bool_matches = til_Bool_clone(&false);
                    }
                    til_I64_dec(&til_I64_needle_idx);
                }
            }
            if (til_Bool_matches.data) {
                til_I64_last_found = til_I64_start_idx;
            }
            til_I64_inc(&til_I64_start_idx);
        }
    } else {
        while (1) {
            til_I64 _tmp_til_Str_rfind_37 = 1;
            til_I64 _tmp_til_Str_rfind_38 = til_I64_add(&til_I64_max_start, &_tmp_til_Str_rfind_37);
            if (!(til_I64_gt(&til_I64_start_idx, &_tmp_til_Str_rfind_38).data)) break;
            til_Bool_matches = til_Bool_clone(&true);
            til_I64_needle_idx = 0;
            til_I64 _tmp_til_Str_rfind_39 = 0;
            til_I64 _tmp_til_Str_rfind_40 = til_Str_len(til_Str_needle);
            if (til_I64_lt(&_tmp_til_Str_rfind_39, &_tmp_til_Str_rfind_40).data) {
                while (1) {
                    til_I64 _tmp_til_Str_rfind_41 = til_Str_len(til_Str_needle);
                    if (!(til_I64_lt(&til_I64_needle_idx, &_tmp_til_Str_rfind_41).data)) break;
                    til_U8_self_byte = 0;
                    til_U8_needle_byte = 0;
                    til_I64 _tmp_til_Str_rfind_42 = (til_I64)&til_U8_self_byte;
                    til_I64 _tmp_til_Str_rfind_43 = til_I64_add(&til_I64_start_idx, &til_I64_needle_idx);
                    til_I64 _tmp_til_Str_rfind_44 = til_Ptr_offset(&til_Str_self->c_string, &_tmp_til_Str_rfind_43).data;
                    til_I64 _tmp_til_Str_rfind_45 = 1;
                    til_memcpy(&_tmp_til_Str_rfind_42, &_tmp_til_Str_rfind_44, &_tmp_til_Str_rfind_45);
                    til_I64 _tmp_til_Str_rfind_46 = (til_I64)&til_U8_needle_byte;
                    til_I64 _tmp_til_Str_rfind_47 = til_Ptr_offset(&til_Str_needle->c_string, &til_I64_needle_idx).data;
                    til_I64 _tmp_til_Str_rfind_48 = 1;
                    til_memcpy(&_tmp_til_Str_rfind_46, &_tmp_til_Str_rfind_47, &_tmp_til_Str_rfind_48);
                    til_Bool _tmp_til_Str_rfind_49 = til_U8_eq(&til_U8_self_byte, &til_U8_needle_byte);
                    if (til_not(&_tmp_til_Str_rfind_49).data) {
                        til_Bool_matches = til_Bool_clone(&false);
                    }
                    til_I64_inc(&til_I64_needle_idx);
                }
            } else {
                while (1) {
                    til_I64 _tmp_til_Str_rfind_50 = til_Str_len(til_Str_needle);
                    if (!(til_I64_gt(&til_I64_needle_idx, &_tmp_til_Str_rfind_50).data)) break;
                    til_U8_self_byte = 0;
                    til_U8_needle_byte = 0;
                    til_I64 _tmp_til_Str_rfind_51 = (til_I64)&til_U8_self_byte;
                    til_I64 _tmp_til_Str_rfind_52 = til_I64_add(&til_I64_start_idx, &til_I64_needle_idx);
                    til_I64 _tmp_til_Str_rfind_53 = til_Ptr_offset(&til_Str_self->c_string, &_tmp_til_Str_rfind_52).data;
                    til_I64 _tmp_til_Str_rfind_54 = 1;
                    til_memcpy(&_tmp_til_Str_rfind_51, &_tmp_til_Str_rfind_53, &_tmp_til_Str_rfind_54);
                    til_I64 _tmp_til_Str_rfind_55 = (til_I64)&til_U8_needle_byte;
                    til_I64 _tmp_til_Str_rfind_56 = til_Ptr_offset(&til_Str_needle->c_string, &til_I64_needle_idx).data;
                    til_I64 _tmp_til_Str_rfind_57 = 1;
                    til_memcpy(&_tmp_til_Str_rfind_55, &_tmp_til_Str_rfind_56, &_tmp_til_Str_rfind_57);
                    til_Bool _tmp_til_Str_rfind_58 = til_U8_eq(&til_U8_self_byte, &til_U8_needle_byte);
                    if (til_not(&_tmp_til_Str_rfind_58).data) {
                        til_Bool_matches = til_Bool_clone(&false);
                    }
                    til_I64_dec(&til_I64_needle_idx);
                }
            }
            if (til_Bool_matches.data) {
                til_I64_last_found = til_I64_start_idx;
            }
            til_I64_dec(&til_I64_start_idx);
        }
    }
    return til_I64_last_found;
    return (til_I64){};
}

til_Str til_Str_replace(const til_Str* til_Str_self, const til_Str* til_Str_from, const til_Str* til_Str_to) {
    til_I64 _tmp_til_Str_replace_0 = til_Str_len(til_Str_from);
    til_I64 _tmp_til_Str_replace_1 = 0;
    if (til_I64_eq(&_tmp_til_Str_replace_0, &_tmp_til_Str_replace_1).data) {
        return til_Str_clone(til_Str_self);
    }
    til_I64 til_I64_count = 0;
    til_I64 til_I64_search_start = 0;
    til_Bool til_Bool_matches;
    til_I64 til_I64_i;
    til_U8 til_U8_self_byte;
    til_U8 til_U8_from_byte;
    while (1) {
        til_I64 _tmp_til_Str_replace_2 = til_Str_len(til_Str_self);
        til_I64 _tmp_til_Str_replace_3 = til_Str_len(til_Str_from);
        til_I64 _tmp_til_Str_replace_4 = til_I64_sub(&_tmp_til_Str_replace_2, &_tmp_til_Str_replace_3);
        if (!(til_I64_lteq(&til_I64_search_start, &_tmp_til_Str_replace_4).data)) break;
        til_Bool_matches = til_Bool_clone(&true);
        til_I64_i = 0;
        til_I64 _tmp_til_Str_replace_5 = 0;
        til_I64 _tmp_til_Str_replace_6 = til_Str_len(til_Str_from);
        if (til_I64_lt(&_tmp_til_Str_replace_5, &_tmp_til_Str_replace_6).data) {
            while (1) {
                til_I64 _tmp_til_Str_replace_7 = til_Str_len(til_Str_from);
                if (!(til_I64_lt(&til_I64_i, &_tmp_til_Str_replace_7).data)) break;
                til_U8_self_byte = 0;
                til_U8_from_byte = 0;
                til_I64 _tmp_til_Str_replace_8 = (til_I64)&til_U8_self_byte;
                til_I64 _tmp_til_Str_replace_9 = til_I64_add(&til_I64_search_start, &til_I64_i);
                til_I64 _tmp_til_Str_replace_10 = til_Ptr_offset(&til_Str_self->c_string, &_tmp_til_Str_replace_9).data;
                til_I64 _tmp_til_Str_replace_11 = 1;
                til_memcpy(&_tmp_til_Str_replace_8, &_tmp_til_Str_replace_10, &_tmp_til_Str_replace_11);
                til_I64 _tmp_til_Str_replace_12 = (til_I64)&til_U8_from_byte;
                til_I64 _tmp_til_Str_replace_13 = til_Ptr_offset(&til_Str_from->c_string, &til_I64_i).data;
                til_I64 _tmp_til_Str_replace_14 = 1;
                til_memcpy(&_tmp_til_Str_replace_12, &_tmp_til_Str_replace_13, &_tmp_til_Str_replace_14);
                til_Bool _tmp_til_Str_replace_15 = til_U8_eq(&til_U8_self_byte, &til_U8_from_byte);
                if (til_not(&_tmp_til_Str_replace_15).data) {
                    til_Bool_matches = til_Bool_clone(&false);
                }
                til_I64_inc(&til_I64_i);
            }
        } else {
            while (1) {
                til_I64 _tmp_til_Str_replace_16 = til_Str_len(til_Str_from);
                if (!(til_I64_gt(&til_I64_i, &_tmp_til_Str_replace_16).data)) break;
                til_U8_self_byte = 0;
                til_U8_from_byte = 0;
                til_I64 _tmp_til_Str_replace_17 = (til_I64)&til_U8_self_byte;
                til_I64 _tmp_til_Str_replace_18 = til_I64_add(&til_I64_search_start, &til_I64_i);
                til_I64 _tmp_til_Str_replace_19 = til_Ptr_offset(&til_Str_self->c_string, &_tmp_til_Str_replace_18).data;
                til_I64 _tmp_til_Str_replace_20 = 1;
                til_memcpy(&_tmp_til_Str_replace_17, &_tmp_til_Str_replace_19, &_tmp_til_Str_replace_20);
                til_I64 _tmp_til_Str_replace_21 = (til_I64)&til_U8_from_byte;
                til_I64 _tmp_til_Str_replace_22 = til_Ptr_offset(&til_Str_from->c_string, &til_I64_i).data;
                til_I64 _tmp_til_Str_replace_23 = 1;
                til_memcpy(&_tmp_til_Str_replace_21, &_tmp_til_Str_replace_22, &_tmp_til_Str_replace_23);
                til_Bool _tmp_til_Str_replace_24 = til_U8_eq(&til_U8_self_byte, &til_U8_from_byte);
                if (til_not(&_tmp_til_Str_replace_24).data) {
                    til_Bool_matches = til_Bool_clone(&false);
                }
                til_I64_dec(&til_I64_i);
            }
        }
        if (til_Bool_matches.data) {
            til_I64_inc(&til_I64_count);
            til_I64 _tmp_til_Str_replace_25 = til_Str_len(til_Str_from);
            til_I64_search_start = til_I64_add(&til_I64_search_start, &_tmp_til_Str_replace_25);
        } else {
            til_I64_inc(&til_I64_search_start);
        }
    }
    til_I64 _tmp_til_Str_replace_26 = 0;
    if (til_I64_eq(&til_I64_count, &_tmp_til_Str_replace_26).data) {
        return til_Str_clone(til_Str_self);
    }
    til_I64 _tmp_til_Str_replace_27 = til_Str_len(til_Str_self);
    til_I64 _tmp_til_Str_replace_28 = til_Str_len(til_Str_from);
    til_I64 _tmp_til_Str_replace_29 = til_I64_mul(&til_I64_count, &_tmp_til_Str_replace_28);
    til_I64 _tmp_til_Str_replace_30 = til_I64_sub(&_tmp_til_Str_replace_27, &_tmp_til_Str_replace_29);
    til_I64 _tmp_til_Str_replace_31 = til_Str_len(til_Str_to);
    til_I64 _tmp_til_Str_replace_32 = til_I64_mul(&til_I64_count, &_tmp_til_Str_replace_31);
    til_I64 til_I64_new_len = til_I64_add(&_tmp_til_Str_replace_30, &_tmp_til_Str_replace_32);
    til_Ptr _tmp_til_Str_replace_33 = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    til_Str til_Str_result = {.c_string = _tmp_til_Str_replace_33, ._len = 0, .cap = 0};
    til_Str_result._len = til_I64_new_len;
    til_I64 _tmp_til_Str_replace_34 = 1;
    til_Str_result.cap = til_I64_add(&til_I64_new_len, &_tmp_til_Str_replace_34);
    til_Str_result.c_string = til_Ptr_new_by_size(&til_Str_result.cap);
    til_Str_result.c_string.is_borrowed = 0;
    til_I64 til_I64_src_idx = 0;
    til_I64 til_I64_dst_idx = 0;
    til_Bool til_Bool_found_match;
    til_I64 til_I64_j;
    til_U8 til_U8_src_byte;
    til_U8 til_U8_pattern_byte;
    while (1) {
        til_I64 _tmp_til_Str_replace_35 = til_Str_len(til_Str_self);
        if (!(til_I64_lt(&til_I64_src_idx, &_tmp_til_Str_replace_35).data)) break;
        til_Bool_found_match = til_Bool_clone(&true);
        til_I64 _tmp_til_Str_replace_36 = til_Str_len(til_Str_self);
        til_I64 _tmp_til_Str_replace_37 = til_Str_len(til_Str_from);
        til_I64 _tmp_til_Str_replace_38 = til_I64_sub(&_tmp_til_Str_replace_36, &_tmp_til_Str_replace_37);
        if (til_I64_lteq(&til_I64_src_idx, &_tmp_til_Str_replace_38).data) {
            til_I64_j = 0;
            til_I64 _tmp_til_Str_replace_39 = 0;
            til_I64 _tmp_til_Str_replace_40 = til_Str_len(til_Str_from);
            if (til_I64_lt(&_tmp_til_Str_replace_39, &_tmp_til_Str_replace_40).data) {
                while (1) {
                    til_I64 _tmp_til_Str_replace_41 = til_Str_len(til_Str_from);
                    if (!(til_I64_lt(&til_I64_j, &_tmp_til_Str_replace_41).data)) break;
                    til_U8_src_byte = 0;
                    til_U8_pattern_byte = 0;
                    til_I64 _tmp_til_Str_replace_42 = (til_I64)&til_U8_src_byte;
                    til_I64 _tmp_til_Str_replace_43 = til_I64_add(&til_I64_src_idx, &til_I64_j);
                    til_I64 _tmp_til_Str_replace_44 = til_Ptr_offset(&til_Str_self->c_string, &_tmp_til_Str_replace_43).data;
                    til_I64 _tmp_til_Str_replace_45 = 1;
                    til_memcpy(&_tmp_til_Str_replace_42, &_tmp_til_Str_replace_44, &_tmp_til_Str_replace_45);
                    til_I64 _tmp_til_Str_replace_46 = (til_I64)&til_U8_pattern_byte;
                    til_I64 _tmp_til_Str_replace_47 = til_Ptr_offset(&til_Str_from->c_string, &til_I64_j).data;
                    til_I64 _tmp_til_Str_replace_48 = 1;
                    til_memcpy(&_tmp_til_Str_replace_46, &_tmp_til_Str_replace_47, &_tmp_til_Str_replace_48);
                    til_Bool _tmp_til_Str_replace_49 = til_U8_eq(&til_U8_src_byte, &til_U8_pattern_byte);
                    if (til_not(&_tmp_til_Str_replace_49).data) {
                        til_Bool_found_match = til_Bool_clone(&false);
                    }
                    til_I64_inc(&til_I64_j);
                }
            } else {
                while (1) {
                    til_I64 _tmp_til_Str_replace_50 = til_Str_len(til_Str_from);
                    if (!(til_I64_gt(&til_I64_j, &_tmp_til_Str_replace_50).data)) break;
                    til_U8_src_byte = 0;
                    til_U8_pattern_byte = 0;
                    til_I64 _tmp_til_Str_replace_51 = (til_I64)&til_U8_src_byte;
                    til_I64 _tmp_til_Str_replace_52 = til_I64_add(&til_I64_src_idx, &til_I64_j);
                    til_I64 _tmp_til_Str_replace_53 = til_Ptr_offset(&til_Str_self->c_string, &_tmp_til_Str_replace_52).data;
                    til_I64 _tmp_til_Str_replace_54 = 1;
                    til_memcpy(&_tmp_til_Str_replace_51, &_tmp_til_Str_replace_53, &_tmp_til_Str_replace_54);
                    til_I64 _tmp_til_Str_replace_55 = (til_I64)&til_U8_pattern_byte;
                    til_I64 _tmp_til_Str_replace_56 = til_Ptr_offset(&til_Str_from->c_string, &til_I64_j).data;
                    til_I64 _tmp_til_Str_replace_57 = 1;
                    til_memcpy(&_tmp_til_Str_replace_55, &_tmp_til_Str_replace_56, &_tmp_til_Str_replace_57);
                    til_Bool _tmp_til_Str_replace_58 = til_U8_eq(&til_U8_src_byte, &til_U8_pattern_byte);
                    if (til_not(&_tmp_til_Str_replace_58).data) {
                        til_Bool_found_match = til_Bool_clone(&false);
                    }
                    til_I64_dec(&til_I64_j);
                }
            }
        } else {
            til_Bool_found_match = til_Bool_clone(&false);
        }
        if (til_Bool_found_match.data) {
            til_I64 _tmp_til_Str_replace_59 = til_Ptr_offset(&til_Str_result.c_string, &til_I64_dst_idx).data;
            til_I64 _tmp_til_Str_replace_60 = til_Str_len(til_Str_to);
            til_memcpy(&_tmp_til_Str_replace_59, &til_Str_to->c_string.data, &_tmp_til_Str_replace_60);
            til_I64 _tmp_til_Str_replace_61 = til_Str_len(til_Str_to);
            til_I64_dst_idx = til_I64_add(&til_I64_dst_idx, &_tmp_til_Str_replace_61);
            til_I64 _tmp_til_Str_replace_62 = til_Str_len(til_Str_from);
            til_I64_src_idx = til_I64_add(&til_I64_src_idx, &_tmp_til_Str_replace_62);
        } else {
            til_I64 _tmp_til_Str_replace_63 = til_Ptr_offset(&til_Str_result.c_string, &til_I64_dst_idx).data;
            til_I64 _tmp_til_Str_replace_64 = til_Ptr_offset(&til_Str_self->c_string, &til_I64_src_idx).data;
            til_I64 _tmp_til_Str_replace_65 = 1;
            til_memcpy(&_tmp_til_Str_replace_63, &_tmp_til_Str_replace_64, &_tmp_til_Str_replace_65);
            til_I64_inc(&til_I64_dst_idx);
            til_I64_inc(&til_I64_src_idx);
        }
    }
    til_U8 til_U8_zero = 0;
    til_I64 _tmp_til_Str_replace_66 = til_Ptr_offset(&til_Str_result.c_string, &til_Str_result._len).data;
    til_I64 _tmp_til_Str_replace_67 = 1;
    til_memset(&_tmp_til_Str_replace_66, &til_U8_zero, &_tmp_til_Str_replace_67);
    return til_Str_result;
    return (til_Str){};
}

til_U8 til_Str_char_at(const til_Str* til_Str_self, const til_I64* til_I64_index) {
    til_U8 til_U8_result = 0;
    til_I64 _tmp_til_Str_char_at_0 = 0;
    if (til_I64_lt(til_I64_index, &_tmp_til_Str_char_at_0).data) {
        return til_U8_result;
    }
    til_I64 _tmp_til_Str_char_at_1 = til_Str_len(til_Str_self);
    if (til_I64_gteq(til_I64_index, &_tmp_til_Str_char_at_1).data) {
        return til_U8_result;
    }
    til_I64 _tmp_til_Str_char_at_2 = (til_I64)&til_U8_result;
    til_I64 _tmp_til_Str_char_at_3 = til_Ptr_offset(&til_Str_self->c_string, til_I64_index).data;
    til_I64 _tmp_til_Str_char_at_4 = 1;
    til_memcpy(&_tmp_til_Str_char_at_2, &_tmp_til_Str_char_at_3, &_tmp_til_Str_char_at_4);
    return til_U8_result;
    return (til_U8){};
}

til_I64 til_Str_cmp(const til_Str* til_Str_self, const til_Str* til_Str_other) {
    til_I64 til_I64_min_len = til_Str_len(til_Str_self);
    til_I64 _tmp_til_Str_cmp_0 = til_Str_len(til_Str_other);
    if (til_I64_lt(&_tmp_til_Str_cmp_0, &til_I64_min_len).data) {
        til_I64_min_len = til_Str_len(til_Str_other);
    }
    til_I64 til_I64_i = 0;
    til_U8 til_U8_a_byte;
    til_U8 til_U8_b_byte;
    til_I64 til_I64_a_val;
    til_I64 til_I64_b_val;
    til_I64 _tmp_til_Str_cmp_1 = 0;
    if (til_I64_lt(&_tmp_til_Str_cmp_1, &til_I64_min_len).data) {
        while (til_I64_lt(&til_I64_i, &til_I64_min_len).data) {
            til_U8_a_byte = til_Str_char_at(til_Str_self, &til_I64_i);
            til_U8_b_byte = til_Str_char_at(til_Str_other, &til_I64_i);
            til_I64_a_val = til_U8_to_i64(&til_U8_a_byte);
            til_I64_b_val = til_U8_to_i64(&til_U8_b_byte);
            if (til_I64_lt(&til_I64_a_val, &til_I64_b_val).data) {
                til_I64 _tmp_til_Str_cmp_2 = 0;
                til_I64 _tmp_til_Str_cmp_3 = 1;
                return til_I64_sub(&_tmp_til_Str_cmp_2, &_tmp_til_Str_cmp_3);
            }
            if (til_I64_gt(&til_I64_a_val, &til_I64_b_val).data) {
                return 1;
            }
            til_I64_inc(&til_I64_i);
        }
    } else {
        while (til_I64_gt(&til_I64_i, &til_I64_min_len).data) {
            til_U8_a_byte = til_Str_char_at(til_Str_self, &til_I64_i);
            til_U8_b_byte = til_Str_char_at(til_Str_other, &til_I64_i);
            til_I64_a_val = til_U8_to_i64(&til_U8_a_byte);
            til_I64_b_val = til_U8_to_i64(&til_U8_b_byte);
            if (til_I64_lt(&til_I64_a_val, &til_I64_b_val).data) {
                til_I64 _tmp_til_Str_cmp_4 = 0;
                til_I64 _tmp_til_Str_cmp_5 = 1;
                return til_I64_sub(&_tmp_til_Str_cmp_4, &_tmp_til_Str_cmp_5);
            }
            if (til_I64_gt(&til_I64_a_val, &til_I64_b_val).data) {
                return 1;
            }
            til_I64_dec(&til_I64_i);
        }
    }
    til_I64 _tmp_til_Str_cmp_6 = til_Str_len(til_Str_self);
    til_I64 _tmp_til_Str_cmp_7 = til_Str_len(til_Str_other);
    return til_I64_sub(&_tmp_til_Str_cmp_6, &_tmp_til_Str_cmp_7);
    return (til_I64){};
}

til_Bool til_Str_lt(const til_Str* til_Str_self, const til_Str* til_Str_other) {
    til_I64 _tmp_til_Str_lt_0 = til_Str_cmp(til_Str_self, til_Str_other);
    til_I64 _tmp_til_Str_lt_1 = 0;
    return til_I64_lt(&_tmp_til_Str_lt_0, &_tmp_til_Str_lt_1);
    return (til_Bool){};
}

til_Bool til_Str_gt(const til_Str* til_Str_self, const til_Str* til_Str_other) {
    til_I64 _tmp_til_Str_gt_0 = til_Str_cmp(til_Str_self, til_Str_other);
    til_I64 _tmp_til_Str_gt_1 = 0;
    return til_I64_gt(&_tmp_til_Str_gt_0, &_tmp_til_Str_gt_1);
    return (til_Bool){};
}

til_Bool til_Str_lteq(const til_Str* til_Str_self, const til_Str* til_Str_other) {
    til_I64 _tmp_til_Str_lteq_0 = til_Str_cmp(til_Str_self, til_Str_other);
    til_I64 _tmp_til_Str_lteq_1 = 0;
    return til_I64_lteq(&_tmp_til_Str_lteq_0, &_tmp_til_Str_lteq_1);
    return (til_Bool){};
}

til_Bool til_Str_gteq(const til_Str* til_Str_self, const til_Str* til_Str_other) {
    til_I64 _tmp_til_Str_gteq_0 = til_Str_cmp(til_Str_self, til_Str_other);
    til_I64 _tmp_til_Str_gteq_1 = 0;
    return til_I64_gteq(&_tmp_til_Str_gteq_0, &_tmp_til_Str_gteq_1);
    return (til_Bool){};
}

void til_Str_inc(til_Str* til_Str_self) {
    til_U8 til_U8_byte_val;
    til_U8 til_U8_one;
    til_Ptr til_Ptr_new_ptr;
    til_I64 _tmp_til_Str_inc_0 = til_Str_len(til_Str_self);
    til_I64 _tmp_til_Str_inc_1 = 1;
    if (til_I64_eq(&_tmp_til_Str_inc_0, &_tmp_til_Str_inc_1).data) {
        til_U8_byte_val = 0;
        til_I64 _tmp_til_Str_inc_2 = (til_I64)&til_U8_byte_val;
        til_I64 _tmp_til_Str_inc_3 = 1;
        til_memcpy(&_tmp_til_Str_inc_2, &til_Str_self->c_string.data, &_tmp_til_Str_inc_3);
        til_U8_one = 1;
        til_U8_byte_val = til_U8_add(&til_U8_byte_val, &til_U8_one);
        til_I64 _tmp_til_Str_inc_4 = 2;
        til_Ptr_new_ptr = til_Ptr_new_by_size(&_tmp_til_Str_inc_4);
        til_Ptr_new_ptr.is_borrowed = 0;
        til_I64 _tmp_til_Str_inc_5 = (til_I64)&til_U8_byte_val;
        til_I64 _tmp_til_Str_inc_6 = 1;
        til_memcpy(&til_Ptr_new_ptr.data, &_tmp_til_Str_inc_5, &_tmp_til_Str_inc_6);
        til_I64 _tmp_til_Str_inc_7 = 1;
        til_I64 _tmp_til_Str_inc_8 = til_Ptr_offset(&til_Ptr_new_ptr, &_tmp_til_Str_inc_7).data;
        til_I64 _tmp_til_Str_inc_9 = 1;
        til_memset(&_tmp_til_Str_inc_8, &til_U8_ZERO_U8, &_tmp_til_Str_inc_9);
        til_Str_self->c_string = til_Ptr_new_ptr;
        til_Str_self->cap = 2;
    }
}

void til_Str_dec(til_Str* til_Str_self) {
    til_U8 til_U8_byte_val;
    til_U8 til_U8_one;
    til_Ptr til_Ptr_new_ptr;
    til_I64 _tmp_til_Str_dec_0 = til_Str_len(til_Str_self);
    til_I64 _tmp_til_Str_dec_1 = 1;
    if (til_I64_eq(&_tmp_til_Str_dec_0, &_tmp_til_Str_dec_1).data) {
        til_U8_byte_val = 0;
        til_I64 _tmp_til_Str_dec_2 = (til_I64)&til_U8_byte_val;
        til_I64 _tmp_til_Str_dec_3 = 1;
        til_memcpy(&_tmp_til_Str_dec_2, &til_Str_self->c_string.data, &_tmp_til_Str_dec_3);
        til_U8_one = 1;
        til_U8_byte_val = til_U8_sub(&til_U8_byte_val, &til_U8_one);
        til_I64 _tmp_til_Str_dec_4 = 2;
        til_Ptr_new_ptr = til_Ptr_new_by_size(&_tmp_til_Str_dec_4);
        til_Ptr_new_ptr.is_borrowed = 0;
        til_I64 _tmp_til_Str_dec_5 = (til_I64)&til_U8_byte_val;
        til_I64 _tmp_til_Str_dec_6 = 1;
        til_memcpy(&til_Ptr_new_ptr.data, &_tmp_til_Str_dec_5, &_tmp_til_Str_dec_6);
        til_I64 _tmp_til_Str_dec_7 = 1;
        til_I64 _tmp_til_Str_dec_8 = til_Ptr_offset(&til_Ptr_new_ptr, &_tmp_til_Str_dec_7).data;
        til_I64 _tmp_til_Str_dec_9 = 1;
        til_memset(&_tmp_til_Str_dec_8, &til_U8_ZERO_U8, &_tmp_til_Str_dec_9);
        til_Str_self->c_string = til_Ptr_new_ptr;
        til_Str_self->cap = 2;
    }
}

til_Str til_Str_replacen(const til_Str* til_Str_self, const til_Str* til_Str_from, const til_Str* til_Str_to, const til_I64* til_I64_n) {
    til_I64 til_I64_idx = {};
    til_Str til_Str_prefix = {};
    til_Str til_Str_suffix = {};
    til_Str til_Str_result = {};
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp_til_Str_replacen_0 = {};
    til_I64 _tmp_til_Str_replacen_1 = til_Str_len(til_Str_from);
    til_I64 _tmp_til_Str_replacen_2 = 0;
    if (til_I64_eq(&_tmp_til_Str_replacen_1, &_tmp_til_Str_replacen_2).data) {
        return til_Str_clone(til_Str_self);
    }
    til_I64 _tmp_til_Str_replacen_3 = 0;
    if (til_I64_eq(til_I64_n, &_tmp_til_Str_replacen_3).data) {
        return til_Str_clone(til_Str_self);
    }
    til_I64_idx = til_Str_find(til_Str_self, til_Str_from);
    til_I64 _tmp_til_Str_replacen_4 = 0;
    if (til_I64_lt(&til_I64_idx, &_tmp_til_Str_replacen_4).data) {
        return til_Str_clone(til_Str_self);
    }
    til_I64 _tmp_til_Str_replacen_6 = 0;
    til_IndexOutOfBoundsError _err0__tmp_til_Str_replacen_5 = {};
    int __attribute__((unused)) _status__tmp_til_Str_replacen_5 = til_get_substr(&til_Str_prefix, &_err0__tmp_til_Str_replacen_5, til_Str_self, &_tmp_til_Str_replacen_6, &til_I64_idx);
    if (_status__tmp_til_Str_replacen_5 == 1) { _thrown_IndexOutOfBoundsError__tmp_til_Str_replacen_0 = _err0__tmp_til_Str_replacen_5; goto _catch_IndexOutOfBoundsError__tmp_til_Str_replacen_0; }
    til_I64 _tmp_til_Str_replacen_8 = til_Str_len(til_Str_from);
    til_I64 _tmp_til_Str_replacen_9 = til_I64_add(&til_I64_idx, &_tmp_til_Str_replacen_8);
    til_I64 _tmp_til_Str_replacen_10 = til_Str_len(til_Str_self);
    til_IndexOutOfBoundsError _err0__tmp_til_Str_replacen_7 = {};
    int __attribute__((unused)) _status__tmp_til_Str_replacen_7 = til_get_substr(&til_Str_suffix, &_err0__tmp_til_Str_replacen_7, til_Str_self, &_tmp_til_Str_replacen_9, &_tmp_til_Str_replacen_10);
    if (_status__tmp_til_Str_replacen_7 == 1) { _thrown_IndexOutOfBoundsError__tmp_til_Str_replacen_0 = _err0__tmp_til_Str_replacen_7; goto _catch_IndexOutOfBoundsError__tmp_til_Str_replacen_0; }
    til_Str _tmp_til_Str_replacen_11 = til_concat(&til_Str_prefix, til_Str_to);
    til_Str_result = til_concat(&_tmp_til_Str_replacen_11, &til_Str_suffix);
    til_Str til_Str_rest;
    til_I64 _tmp_til_Str_replacen_12 = 1;
    if (til_I64_gt(til_I64_n, &_tmp_til_Str_replacen_12).data) {
        til_I64 _tmp_til_Str_replacen_13 = 1;
        til_I64 _tmp_til_Str_replacen_14 = til_I64_sub(til_I64_n, &_tmp_til_Str_replacen_13);
        til_Str_rest = til_Str_replacen(&til_Str_suffix, til_Str_from, til_Str_to, &_tmp_til_Str_replacen_14);
        til_Str _tmp_til_Str_replacen_15 = til_concat(&til_Str_prefix, til_Str_to);
        til_Str_result = til_concat(&_tmp_til_Str_replacen_15, &til_Str_rest);
    }
    if (0) { _catch_IndexOutOfBoundsError__tmp_til_Str_replacen_0:;
        til_IndexOutOfBoundsError til_IndexOutOfBoundsError_err = _thrown_IndexOutOfBoundsError__tmp_til_Str_replacen_0;
        til_Str_result = til_Str_clone(til_Str_self);
    }
    return til_Str_result;
    return (til_Str){};
}

int til_Str_split(til_Vec* _ret, til_IndexOutOfBoundsError* _err1, const til_Str* til_Str_self, const til_Str* til_Str_delimiter) {
    (*_ret) = til_Vec_new("Str");
    til_I64 _tmp_til_Str_split_0 = til_Str_len(til_Str_delimiter);
    til_I64 _tmp_til_Str_split_1 = 0;
    if (til_I64_eq(&_tmp_til_Str_split_0, &_tmp_til_Str_split_1).data) {
        til_Str _tmp_til_Str_split_2 = til_Str_clone(til_Str_self);
        til_Vec_push(_ret, (til_Dynamic*)&_tmp_til_Str_split_2);
        return 0;
    }
    til_I64 til_I64_start = 0;
    til_I64 til_I64_pos = 0;
    til_Bool til_Bool_matches;
    til_I64 til_I64_i;
    til_U8 til_U8_self_byte;
    til_U8 til_U8_delim_byte;
    til_Str til_Str_part;
    while (1) {
        til_I64 _tmp_til_Str_split_3 = til_Str_len(til_Str_self);
        til_I64 _tmp_til_Str_split_4 = til_Str_len(til_Str_delimiter);
        til_I64 _tmp_til_Str_split_5 = til_I64_sub(&_tmp_til_Str_split_3, &_tmp_til_Str_split_4);
        if (!(til_I64_lteq(&til_I64_pos, &_tmp_til_Str_split_5).data)) break;
        til_Bool_matches = til_Bool_clone(&true);
        til_I64_i = 0;
        til_I64 _tmp_til_Str_split_6 = 0;
        til_I64 _tmp_til_Str_split_7 = til_Str_len(til_Str_delimiter);
        if (til_I64_lt(&_tmp_til_Str_split_6, &_tmp_til_Str_split_7).data) {
            while (1) {
                til_I64 _tmp_til_Str_split_8 = til_Str_len(til_Str_delimiter);
                if (!(til_I64_lt(&til_I64_i, &_tmp_til_Str_split_8).data)) break;
                til_U8_self_byte = 0;
                til_U8_delim_byte = 0;
                til_I64 _tmp_til_Str_split_9 = (til_I64)&til_U8_self_byte;
                til_I64 _tmp_til_Str_split_10 = til_I64_add(&til_I64_pos, &til_I64_i);
                til_I64 _tmp_til_Str_split_11 = til_Ptr_offset(&til_Str_self->c_string, &_tmp_til_Str_split_10).data;
                til_I64 _tmp_til_Str_split_12 = 1;
                til_memcpy(&_tmp_til_Str_split_9, &_tmp_til_Str_split_11, &_tmp_til_Str_split_12);
                til_I64 _tmp_til_Str_split_13 = (til_I64)&til_U8_delim_byte;
                til_I64 _tmp_til_Str_split_14 = til_Ptr_offset(&til_Str_delimiter->c_string, &til_I64_i).data;
                til_I64 _tmp_til_Str_split_15 = 1;
                til_memcpy(&_tmp_til_Str_split_13, &_tmp_til_Str_split_14, &_tmp_til_Str_split_15);
                til_Bool _tmp_til_Str_split_16 = til_U8_eq(&til_U8_self_byte, &til_U8_delim_byte);
                if (til_not(&_tmp_til_Str_split_16).data) {
                    til_Bool_matches = til_Bool_clone(&false);
                }
                til_I64_inc(&til_I64_i);
            }
        } else {
            while (1) {
                til_I64 _tmp_til_Str_split_17 = til_Str_len(til_Str_delimiter);
                if (!(til_I64_gt(&til_I64_i, &_tmp_til_Str_split_17).data)) break;
                til_U8_self_byte = 0;
                til_U8_delim_byte = 0;
                til_I64 _tmp_til_Str_split_18 = (til_I64)&til_U8_self_byte;
                til_I64 _tmp_til_Str_split_19 = til_I64_add(&til_I64_pos, &til_I64_i);
                til_I64 _tmp_til_Str_split_20 = til_Ptr_offset(&til_Str_self->c_string, &_tmp_til_Str_split_19).data;
                til_I64 _tmp_til_Str_split_21 = 1;
                til_memcpy(&_tmp_til_Str_split_18, &_tmp_til_Str_split_20, &_tmp_til_Str_split_21);
                til_I64 _tmp_til_Str_split_22 = (til_I64)&til_U8_delim_byte;
                til_I64 _tmp_til_Str_split_23 = til_Ptr_offset(&til_Str_delimiter->c_string, &til_I64_i).data;
                til_I64 _tmp_til_Str_split_24 = 1;
                til_memcpy(&_tmp_til_Str_split_22, &_tmp_til_Str_split_23, &_tmp_til_Str_split_24);
                til_Bool _tmp_til_Str_split_25 = til_U8_eq(&til_U8_self_byte, &til_U8_delim_byte);
                if (til_not(&_tmp_til_Str_split_25).data) {
                    til_Bool_matches = til_Bool_clone(&false);
                }
                til_I64_dec(&til_I64_i);
            }
        }
        if (til_Bool_matches.data) {
            if (til_I64_gt(&til_I64_pos, &til_I64_start).data) {
                til_IndexOutOfBoundsError _err0__tmp_til_Str_split_26 = {};
                int __attribute__((unused)) _status__tmp_til_Str_split_26 = til_get_substr(&til_Str_part, &_err0__tmp_til_Str_split_26, til_Str_self, &til_I64_start, &til_I64_pos);
                if (_status__tmp_til_Str_split_26 == 1) { *_err1 = _err0__tmp_til_Str_split_26; return 1; }
                til_Vec_push(_ret, (til_Dynamic*)&til_Str_part);
            } else {
                til_Vec_push(_ret, (til_Dynamic*)&((til_Str){((til_Ptr){(til_I64)"", 1, 0, 0, 0}), 0, 0}));
            }
            til_I64 _tmp_til_Str_split_27 = til_Str_len(til_Str_delimiter);
            til_I64_start = til_I64_add(&til_I64_pos, &_tmp_til_Str_split_27);
            til_I64_pos = til_I64_start;
        } else {
            til_I64_inc(&til_I64_pos);
        }
    }
    til_Str til_Str_remaining_part;
    til_I64 _tmp_til_Str_split_28 = til_Str_len(til_Str_self);
    if (til_I64_lt(&til_I64_start, &_tmp_til_Str_split_28).data) {
        til_I64 _tmp_til_Str_split_30 = til_Str_len(til_Str_self);
        til_IndexOutOfBoundsError _err0__tmp_til_Str_split_29 = {};
        int __attribute__((unused)) _status__tmp_til_Str_split_29 = til_get_substr(&til_Str_remaining_part, &_err0__tmp_til_Str_split_29, til_Str_self, &til_I64_start, &_tmp_til_Str_split_30);
        if (_status__tmp_til_Str_split_29 == 1) { *_err1 = _err0__tmp_til_Str_split_29; return 1; }
        til_Vec_push(_ret, (til_Dynamic*)&til_Str_remaining_part);
    } else {
        til_I64 _tmp_til_Str_split_31 = til_Str_len(til_Str_self);
        if (til_I64_eq(&til_I64_start, &_tmp_til_Str_split_31).data) {
            til_Vec_push(_ret, (til_Dynamic*)&((til_Str){((til_Ptr){(til_I64)"", 1, 0, 0, 0}), 0, 0}));
        }
    }
    return 0;
    return 0;
}

til_Str til_Str_repeat(const til_Str* til_Str_self, const til_I64* til_I64_n) {
    til_I64 _tmp_til_Str_repeat_0 = 0;
    if (til_I64_lteq(til_I64_n, &_tmp_til_Str_repeat_0).data) {
        return ((til_Str){((til_Ptr){(til_I64)"", 1, 0, 0, 0}), 0, 0});
    }
    til_I64 _tmp_til_Str_repeat_1 = 1;
    if (til_I64_eq(til_I64_n, &_tmp_til_Str_repeat_1).data) {
        return til_Str_clone(til_Str_self);
    }
    til_Ptr _tmp_til_Str_repeat_2 = (til_Ptr){.data = til_I64_NULL, .is_borrowed = 0, .alloc_size = 0, .elem_type = til_I64_NULL, .elem_size = 0};
    til_Str til_Str_result = {.c_string = _tmp_til_Str_repeat_2, ._len = 0, .cap = 0};
    til_Str_result._len = til_I64_mul(&til_Str_self->_len, til_I64_n);
    til_I64 _tmp_til_Str_repeat_3 = 1;
    til_Str_result.cap = til_I64_add(&til_Str_result._len, &_tmp_til_Str_repeat_3);
    til_Str_result.c_string = til_Ptr_new_by_size(&til_Str_result.cap);
    til_Str_result.c_string.is_borrowed = 0;
    til_I64 til_I64_offset = 0;
    til_I64 til_I64_i = 0;
    til_I64 _tmp_til_Str_repeat_4 = 0;
    if (til_I64_lt(&_tmp_til_Str_repeat_4, til_I64_n).data) {
        while (til_I64_lt(&til_I64_i, til_I64_n).data) {
            til_I64 _tmp_til_Str_repeat_5 = til_Ptr_offset(&til_Str_result.c_string, &til_I64_offset).data;
            til_memcpy(&_tmp_til_Str_repeat_5, &til_Str_self->c_string.data, &til_Str_self->_len);
            til_I64_offset = til_I64_add(&til_I64_offset, &til_Str_self->_len);
            til_I64_inc(&til_I64_i);
        }
    } else {
        while (til_I64_gt(&til_I64_i, til_I64_n).data) {
            til_I64 _tmp_til_Str_repeat_6 = til_Ptr_offset(&til_Str_result.c_string, &til_I64_offset).data;
            til_memcpy(&_tmp_til_Str_repeat_6, &til_Str_self->c_string.data, &til_Str_self->_len);
            til_I64_offset = til_I64_add(&til_I64_offset, &til_Str_self->_len);
            til_I64_dec(&til_I64_i);
        }
    }
    til_I64 _tmp_til_Str_repeat_7 = til_Ptr_offset(&til_Str_result.c_string, &til_Str_result._len).data;
    til_I64 _tmp_til_Str_repeat_8 = 1;
    til_memset(&_tmp_til_Str_repeat_7, &til_U8_ZERO_U8, &_tmp_til_Str_repeat_8);
    return til_Str_result;
    return (til_Str){};
}

til_I64 til_Str_hash(const til_Str* til_Str_self) {
    til_I64 _tmp_til_Str_hash_0 = 0;
    til_I64 _tmp_til_Str_hash_1 = 3750763034362895579;
    til_I64 til_I64_FNV_OFFSET_BASIS = til_I64_sub(&_tmp_til_Str_hash_0, &_tmp_til_Str_hash_1);
    til_I64 til_I64_FNV_PRIME = 1099511628211;
    til_I64 til_I64_h = til_I64_clone(&til_I64_FNV_OFFSET_BASIS);
    til_I64 til_I64_i = 0;
    til_U8 til_U8_byte_val;
    til_I64 _tmp_til_Str_hash_2 = 0;
    if (til_I64_lt(&_tmp_til_Str_hash_2, &til_Str_self->_len).data) {
        while (til_I64_lt(&til_I64_i, &til_Str_self->_len).data) {
            til_U8_byte_val = 0;
            til_I64 _tmp_til_Str_hash_3 = (til_I64)&til_U8_byte_val;
            til_I64 _tmp_til_Str_hash_4 = til_Ptr_offset(&til_Str_self->c_string, &til_I64_i).data;
            til_I64 _tmp_til_Str_hash_5 = 1;
            til_memcpy(&_tmp_til_Str_hash_3, &_tmp_til_Str_hash_4, &_tmp_til_Str_hash_5);
            til_I64 _tmp_til_Str_hash_6 = til_U8_to_i64(&til_U8_byte_val);
            til_I64_h = til_I64_xor(&til_I64_h, &_tmp_til_Str_hash_6);
            til_I64_h = til_I64_mul(&til_I64_h, &til_I64_FNV_PRIME);
            til_I64_inc(&til_I64_i);
        }
    } else {
        while (til_I64_gt(&til_I64_i, &til_Str_self->_len).data) {
            til_U8_byte_val = 0;
            til_I64 _tmp_til_Str_hash_7 = (til_I64)&til_U8_byte_val;
            til_I64 _tmp_til_Str_hash_8 = til_Ptr_offset(&til_Str_self->c_string, &til_I64_i).data;
            til_I64 _tmp_til_Str_hash_9 = 1;
            til_memcpy(&_tmp_til_Str_hash_7, &_tmp_til_Str_hash_8, &_tmp_til_Str_hash_9);
            til_I64 _tmp_til_Str_hash_10 = til_U8_to_i64(&til_U8_byte_val);
            til_I64_h = til_I64_xor(&til_I64_h, &_tmp_til_Str_hash_10);
            til_I64_h = til_I64_mul(&til_I64_h, &til_I64_FNV_PRIME);
            til_I64_dec(&til_I64_i);
        }
    }
    return til_I64_h;
    return (til_I64){};
}

til_I64 til_U8_len(const til_U8* _self) {
    (void)_self;
    return 1;
    return (til_I64){};
}

til_Bool til_U8_lt(const til_U8* til_U8_self, const til_U8* til_U8_other) {
    return til_u8_lt(til_U8_self, til_U8_other);
    return (til_Bool){};
}

til_Bool til_U8_gt(const til_U8* til_U8_self, const til_U8* til_U8_other) {
    return til_u8_gt(til_U8_self, til_U8_other);
    return (til_Bool){};
}

til_Bool til_U8_eq(const til_U8* til_U8_a, const til_U8* til_U8_b) {
    if (til_U8_gt(til_U8_a, til_U8_b).data) {
        return false;
    }
    if (til_U8_gt(til_U8_b, til_U8_a).data) {
        return false;
    }
    if (til_U8_lt(til_U8_a, til_U8_b).data) {
        return false;
    }
    if (til_U8_lt(til_U8_b, til_U8_a).data) {
        return false;
    }
    return true;
    return (til_Bool){};
}

til_I64 til_U8_to_i64(const til_U8* til_U8_self) {
    return til_u8_to_i64(til_U8_self);
    return (til_I64){};
}

til_U8 til_U8_add(const til_U8* til_U8_a, const til_U8* til_U8_b) {
    return til_u8_add(til_U8_a, til_U8_b);
    return (til_U8){};
}

int til_U8_safe_add(til_U8* _ret, til_U8_Overflow* _err1, const til_U8* til_U8_a, const til_U8* til_U8_b) {
    til_I64 _tmp_til_U8_safe_add_0 = til_U8_to_i64(til_U8_a);
    til_I64 _tmp_til_U8_safe_add_1 = til_U8_to_i64(til_U8_b);
    til_I64 til_I64_sum = til_I64_add(&_tmp_til_U8_safe_add_0, &_tmp_til_U8_safe_add_1);
    if (til_I64_gt(&til_I64_sum, &til_I64_MAX_U8).data) {
        til_Str _tmp_til_U8_safe_add_2;
        til_Array _tmp_til_U8_safe_add_3;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_U8_safe_add_4;
        til_Str _tmp_til_U8_safe_add_5 = ((til_Str){((til_Ptr){(til_I64)"U8 overflow: ", 1, 0, 0, 0}), 13, 0});
        til_Str _tmp_til_U8_safe_add_6 = til_U8_to_str(til_U8_a);
        til_Str _tmp_til_U8_safe_add_7 = ((til_Str){((til_Ptr){(til_I64)" + ", 1, 0, 0, 0}), 3, 0});
        til_Str _tmp_til_U8_safe_add_8 = til_U8_to_str(til_U8_b);
        til_Str _tmp_til_U8_safe_add_9 = ((til_Str){((til_Ptr){(til_I64)" = ", 1, 0, 0, 0}), 3, 0});
        til_Str _tmp_til_U8_safe_add_10 = til_I64_to_str(&til_I64_sum);
        til_Type _tmp_til_U8_safe_add_11 = "Str";
        til_I64 _tmp_til_U8_safe_add_12 = 6;
        _tmp_til_U8_safe_add_3 = til_Array_new(_tmp_til_U8_safe_add_11, &_tmp_til_U8_safe_add_12);
        int __attribute__((unused)) _arr_status__tmp_til_U8_safe_add_4;
        til_I64 _tmp_til_U8_safe_add_13 = 0;
        _arr_status__tmp_til_U8_safe_add_4 = til_Array_set(&_err_idx__tmp_til_U8_safe_add_4, &_tmp_til_U8_safe_add_3, &_tmp_til_U8_safe_add_13, (til_Dynamic*)&_tmp_til_U8_safe_add_5);
        til_I64 _tmp_til_U8_safe_add_14 = 1;
        _arr_status__tmp_til_U8_safe_add_4 = til_Array_set(&_err_idx__tmp_til_U8_safe_add_4, &_tmp_til_U8_safe_add_3, &_tmp_til_U8_safe_add_14, (til_Dynamic*)&_tmp_til_U8_safe_add_6);
        til_I64 _tmp_til_U8_safe_add_15 = 2;
        _arr_status__tmp_til_U8_safe_add_4 = til_Array_set(&_err_idx__tmp_til_U8_safe_add_4, &_tmp_til_U8_safe_add_3, &_tmp_til_U8_safe_add_15, (til_Dynamic*)&_tmp_til_U8_safe_add_7);
        til_I64 _tmp_til_U8_safe_add_16 = 3;
        _arr_status__tmp_til_U8_safe_add_4 = til_Array_set(&_err_idx__tmp_til_U8_safe_add_4, &_tmp_til_U8_safe_add_3, &_tmp_til_U8_safe_add_16, (til_Dynamic*)&_tmp_til_U8_safe_add_8);
        til_I64 _tmp_til_U8_safe_add_17 = 4;
        _arr_status__tmp_til_U8_safe_add_4 = til_Array_set(&_err_idx__tmp_til_U8_safe_add_4, &_tmp_til_U8_safe_add_3, &_tmp_til_U8_safe_add_17, (til_Dynamic*)&_tmp_til_U8_safe_add_9);
        til_I64 _tmp_til_U8_safe_add_18 = 5;
        _arr_status__tmp_til_U8_safe_add_4 = til_Array_set(&_err_idx__tmp_til_U8_safe_add_4, &_tmp_til_U8_safe_add_3, &_tmp_til_U8_safe_add_18, (til_Dynamic*)&_tmp_til_U8_safe_add_10);
        _tmp_til_U8_safe_add_2 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/u8.til:71:42:", 1, 0, 0, 0}), 22, 0}), &_tmp_til_U8_safe_add_3);
        til_Array_delete(&_tmp_til_U8_safe_add_3);
        *_err1 = (til_U8_Overflow){.msg = _tmp_til_U8_safe_add_2};
        return 1;
    }
    *_ret = til_i64_to_u8(&til_I64_sum);
    return 0;
    return 0;
}

til_U8 til_U8_sub(const til_U8* til_U8_a, const til_U8* til_U8_b) {
    return til_u8_sub(til_U8_a, til_U8_b);
    return (til_U8){};
}

int til_U8_safe_sub(til_U8* _ret, til_U8_Overflow* _err1, const til_U8* til_U8_a, const til_U8* til_U8_b) {
    til_I64 _tmp_til_U8_safe_sub_0 = til_U8_to_i64(til_U8_a);
    til_I64 _tmp_til_U8_safe_sub_1 = til_U8_to_i64(til_U8_b);
    til_I64 til_I64_diff = til_I64_sub(&_tmp_til_U8_safe_sub_0, &_tmp_til_U8_safe_sub_1);
    til_I64 _tmp_til_U8_safe_sub_2 = 0;
    if (til_I64_lt(&til_I64_diff, &_tmp_til_U8_safe_sub_2).data) {
        til_Str _tmp_til_U8_safe_sub_3;
        til_Array _tmp_til_U8_safe_sub_4;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_U8_safe_sub_5;
        til_Str _tmp_til_U8_safe_sub_6 = ((til_Str){((til_Ptr){(til_I64)"U8 underflow: ", 1, 0, 0, 0}), 14, 0});
        til_Str _tmp_til_U8_safe_sub_7 = til_U8_to_str(til_U8_a);
        til_Str _tmp_til_U8_safe_sub_8 = ((til_Str){((til_Ptr){(til_I64)" - ", 1, 0, 0, 0}), 3, 0});
        til_Str _tmp_til_U8_safe_sub_9 = til_U8_to_str(til_U8_b);
        til_Str _tmp_til_U8_safe_sub_10 = ((til_Str){((til_Ptr){(til_I64)" = ", 1, 0, 0, 0}), 3, 0});
        til_Str _tmp_til_U8_safe_sub_11 = til_I64_to_str(&til_I64_diff);
        til_Type _tmp_til_U8_safe_sub_12 = "Str";
        til_I64 _tmp_til_U8_safe_sub_13 = 6;
        _tmp_til_U8_safe_sub_4 = til_Array_new(_tmp_til_U8_safe_sub_12, &_tmp_til_U8_safe_sub_13);
        int __attribute__((unused)) _arr_status__tmp_til_U8_safe_sub_5;
        til_I64 _tmp_til_U8_safe_sub_14 = 0;
        _arr_status__tmp_til_U8_safe_sub_5 = til_Array_set(&_err_idx__tmp_til_U8_safe_sub_5, &_tmp_til_U8_safe_sub_4, &_tmp_til_U8_safe_sub_14, (til_Dynamic*)&_tmp_til_U8_safe_sub_6);
        til_I64 _tmp_til_U8_safe_sub_15 = 1;
        _arr_status__tmp_til_U8_safe_sub_5 = til_Array_set(&_err_idx__tmp_til_U8_safe_sub_5, &_tmp_til_U8_safe_sub_4, &_tmp_til_U8_safe_sub_15, (til_Dynamic*)&_tmp_til_U8_safe_sub_7);
        til_I64 _tmp_til_U8_safe_sub_16 = 2;
        _arr_status__tmp_til_U8_safe_sub_5 = til_Array_set(&_err_idx__tmp_til_U8_safe_sub_5, &_tmp_til_U8_safe_sub_4, &_tmp_til_U8_safe_sub_16, (til_Dynamic*)&_tmp_til_U8_safe_sub_8);
        til_I64 _tmp_til_U8_safe_sub_17 = 3;
        _arr_status__tmp_til_U8_safe_sub_5 = til_Array_set(&_err_idx__tmp_til_U8_safe_sub_5, &_tmp_til_U8_safe_sub_4, &_tmp_til_U8_safe_sub_17, (til_Dynamic*)&_tmp_til_U8_safe_sub_9);
        til_I64 _tmp_til_U8_safe_sub_18 = 4;
        _arr_status__tmp_til_U8_safe_sub_5 = til_Array_set(&_err_idx__tmp_til_U8_safe_sub_5, &_tmp_til_U8_safe_sub_4, &_tmp_til_U8_safe_sub_18, (til_Dynamic*)&_tmp_til_U8_safe_sub_10);
        til_I64 _tmp_til_U8_safe_sub_19 = 5;
        _arr_status__tmp_til_U8_safe_sub_5 = til_Array_set(&_err_idx__tmp_til_U8_safe_sub_5, &_tmp_til_U8_safe_sub_4, &_tmp_til_U8_safe_sub_19, (til_Dynamic*)&_tmp_til_U8_safe_sub_11);
        _tmp_til_U8_safe_sub_3 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/u8.til:90:42:", 1, 0, 0, 0}), 22, 0}), &_tmp_til_U8_safe_sub_4);
        til_Array_delete(&_tmp_til_U8_safe_sub_4);
        *_err1 = (til_U8_Overflow){.msg = _tmp_til_U8_safe_sub_3};
        return 1;
    }
    *_ret = til_i64_to_u8(&til_I64_diff);
    return 0;
    return 0;
}

til_U8 til_U8_mul(const til_U8* til_U8_a, const til_U8* til_U8_b) {
    return til_u8_mul(til_U8_a, til_U8_b);
    return (til_U8){};
}

int til_U8_safe_mul(til_U8* _ret, til_U8_Overflow* _err1, const til_U8* til_U8_a, const til_U8* til_U8_b) {
    til_I64 _tmp_til_U8_safe_mul_0 = til_U8_to_i64(til_U8_a);
    til_I64 _tmp_til_U8_safe_mul_1 = til_U8_to_i64(til_U8_b);
    til_I64 til_I64_product = til_I64_mul(&_tmp_til_U8_safe_mul_0, &_tmp_til_U8_safe_mul_1);
    if (til_I64_gt(&til_I64_product, &til_I64_MAX_U8).data) {
        til_Str _tmp_til_U8_safe_mul_2;
        til_Array _tmp_til_U8_safe_mul_3;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_U8_safe_mul_4;
        til_Str _tmp_til_U8_safe_mul_5 = ((til_Str){((til_Ptr){(til_I64)"U8 overflow: ", 1, 0, 0, 0}), 13, 0});
        til_Str _tmp_til_U8_safe_mul_6 = til_U8_to_str(til_U8_a);
        til_Str _tmp_til_U8_safe_mul_7 = ((til_Str){((til_Ptr){(til_I64)" * ", 1, 0, 0, 0}), 3, 0});
        til_Str _tmp_til_U8_safe_mul_8 = til_U8_to_str(til_U8_b);
        til_Str _tmp_til_U8_safe_mul_9 = ((til_Str){((til_Ptr){(til_I64)" = ", 1, 0, 0, 0}), 3, 0});
        til_Str _tmp_til_U8_safe_mul_10 = til_I64_to_str(&til_I64_product);
        til_Type _tmp_til_U8_safe_mul_11 = "Str";
        til_I64 _tmp_til_U8_safe_mul_12 = 6;
        _tmp_til_U8_safe_mul_3 = til_Array_new(_tmp_til_U8_safe_mul_11, &_tmp_til_U8_safe_mul_12);
        int __attribute__((unused)) _arr_status__tmp_til_U8_safe_mul_4;
        til_I64 _tmp_til_U8_safe_mul_13 = 0;
        _arr_status__tmp_til_U8_safe_mul_4 = til_Array_set(&_err_idx__tmp_til_U8_safe_mul_4, &_tmp_til_U8_safe_mul_3, &_tmp_til_U8_safe_mul_13, (til_Dynamic*)&_tmp_til_U8_safe_mul_5);
        til_I64 _tmp_til_U8_safe_mul_14 = 1;
        _arr_status__tmp_til_U8_safe_mul_4 = til_Array_set(&_err_idx__tmp_til_U8_safe_mul_4, &_tmp_til_U8_safe_mul_3, &_tmp_til_U8_safe_mul_14, (til_Dynamic*)&_tmp_til_U8_safe_mul_6);
        til_I64 _tmp_til_U8_safe_mul_15 = 2;
        _arr_status__tmp_til_U8_safe_mul_4 = til_Array_set(&_err_idx__tmp_til_U8_safe_mul_4, &_tmp_til_U8_safe_mul_3, &_tmp_til_U8_safe_mul_15, (til_Dynamic*)&_tmp_til_U8_safe_mul_7);
        til_I64 _tmp_til_U8_safe_mul_16 = 3;
        _arr_status__tmp_til_U8_safe_mul_4 = til_Array_set(&_err_idx__tmp_til_U8_safe_mul_4, &_tmp_til_U8_safe_mul_3, &_tmp_til_U8_safe_mul_16, (til_Dynamic*)&_tmp_til_U8_safe_mul_8);
        til_I64 _tmp_til_U8_safe_mul_17 = 4;
        _arr_status__tmp_til_U8_safe_mul_4 = til_Array_set(&_err_idx__tmp_til_U8_safe_mul_4, &_tmp_til_U8_safe_mul_3, &_tmp_til_U8_safe_mul_17, (til_Dynamic*)&_tmp_til_U8_safe_mul_9);
        til_I64 _tmp_til_U8_safe_mul_18 = 5;
        _arr_status__tmp_til_U8_safe_mul_4 = til_Array_set(&_err_idx__tmp_til_U8_safe_mul_4, &_tmp_til_U8_safe_mul_3, &_tmp_til_U8_safe_mul_18, (til_Dynamic*)&_tmp_til_U8_safe_mul_10);
        _tmp_til_U8_safe_mul_2 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/u8.til:109:42:", 1, 0, 0, 0}), 23, 0}), &_tmp_til_U8_safe_mul_3);
        til_Array_delete(&_tmp_til_U8_safe_mul_3);
        *_err1 = (til_U8_Overflow){.msg = _tmp_til_U8_safe_mul_2};
        return 1;
    }
    *_ret = til_i64_to_u8(&til_I64_product);
    return 0;
    return 0;
}

til_U8 til_U8_div(const til_U8* til_U8_a, const til_U8* til_U8_b) {
    return til_u8_div(til_U8_a, til_U8_b);
    return (til_U8){};
}

int til_U8_safe_div(til_U8* _ret, const til_U8* til_U8_a, const til_U8* til_U8_b) {
    if (til_U8_eq(til_U8_b, &til_U8_ZERO_U8).data) {
        return 1;
    }
    *_ret = til_u8_div(til_U8_a, til_U8_b);
    return 0;
    return 0;
}

til_U8 til_U8_mod(const til_U8* til_U8_a, const til_U8* til_U8_b) {
    return til_u8_mod(til_U8_a, til_U8_b);
    return (til_U8){};
}

til_U8 til_U8_xor(const til_U8* til_U8_a, const til_U8* til_U8_b) {
    return til_u8_xor(til_U8_a, til_U8_b);
    return (til_U8){};
}

til_U8 til_U8_and(const til_U8* til_U8_a, const til_U8* til_U8_b) {
    return til_u8_and(til_U8_a, til_U8_b);
    return (til_U8){};
}

til_U8 til_U8_or(const til_U8* til_U8_a, const til_U8* til_U8_b) {
    return til_u8_or(til_U8_a, til_U8_b);
    return (til_U8){};
}

int til_U8_from_i64(til_U8* _ret, til_U8_Overflow* _err1, const til_I64* til_I64_self) {
    til_I64 _tmp_til_U8_from_i64_0 = 0;
    if (til_I64_lt(til_I64_self, &_tmp_til_U8_from_i64_0).data) {
        til_Str _tmp_til_U8_from_i64_1;
        til_Array _tmp_til_U8_from_i64_2;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_U8_from_i64_3;
        til_Str _tmp_til_U8_from_i64_4 = ((til_Str){((til_Ptr){(til_I64)"Negative values cannot be cast into 'U8'", 1, 0, 0, 0}), 40, 0});
        til_Type _tmp_til_U8_from_i64_5 = "Str";
        til_I64 _tmp_til_U8_from_i64_6 = 1;
        _tmp_til_U8_from_i64_2 = til_Array_new(_tmp_til_U8_from_i64_5, &_tmp_til_U8_from_i64_6);
        int __attribute__((unused)) _arr_status__tmp_til_U8_from_i64_3;
        til_I64 _tmp_til_U8_from_i64_7 = 0;
        _arr_status__tmp_til_U8_from_i64_3 = til_Array_set(&_err_idx__tmp_til_U8_from_i64_3, &_tmp_til_U8_from_i64_2, &_tmp_til_U8_from_i64_7, (til_Dynamic*)&_tmp_til_U8_from_i64_4);
        _tmp_til_U8_from_i64_1 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/u8.til:157:42:", 1, 0, 0, 0}), 23, 0}), &_tmp_til_U8_from_i64_2);
        til_Array_delete(&_tmp_til_U8_from_i64_2);
        *_err1 = (til_U8_Overflow){.msg = _tmp_til_U8_from_i64_1};
        return 1;
    }
    if (til_I64_gt(til_I64_self, &til_I64_MAX_U8).data) {
        til_Str _tmp_til_U8_from_i64_8;
        til_Array _tmp_til_U8_from_i64_9;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_U8_from_i64_10;
        til_Str _tmp_til_U8_from_i64_11 = ((til_Str){((til_Ptr){(til_I64)"U8: cannot be casted from an I64 greater than: ", 1, 0, 0, 0}), 47, 0});
        til_Str _tmp_til_U8_from_i64_12 = til_I64_to_str(&til_I64_MAX_U8);
        til_Type _tmp_til_U8_from_i64_13 = "Str";
        til_I64 _tmp_til_U8_from_i64_14 = 2;
        _tmp_til_U8_from_i64_9 = til_Array_new(_tmp_til_U8_from_i64_13, &_tmp_til_U8_from_i64_14);
        int __attribute__((unused)) _arr_status__tmp_til_U8_from_i64_10;
        til_I64 _tmp_til_U8_from_i64_15 = 0;
        _arr_status__tmp_til_U8_from_i64_10 = til_Array_set(&_err_idx__tmp_til_U8_from_i64_10, &_tmp_til_U8_from_i64_9, &_tmp_til_U8_from_i64_15, (til_Dynamic*)&_tmp_til_U8_from_i64_11);
        til_I64 _tmp_til_U8_from_i64_16 = 1;
        _arr_status__tmp_til_U8_from_i64_10 = til_Array_set(&_err_idx__tmp_til_U8_from_i64_10, &_tmp_til_U8_from_i64_9, &_tmp_til_U8_from_i64_16, (til_Dynamic*)&_tmp_til_U8_from_i64_12);
        _tmp_til_U8_from_i64_8 = til_format(&((til_Str){((til_Ptr){(til_I64)"src/core/u8.til:160:42:", 1, 0, 0, 0}), 23, 0}), &_tmp_til_U8_from_i64_9);
        til_Array_delete(&_tmp_til_U8_from_i64_9);
        *_err1 = (til_U8_Overflow){.msg = _tmp_til_U8_from_i64_8};
        return 1;
    }
    *_ret = til_i64_to_u8(til_I64_self);
    return 0;
    return 0;
}

til_Str til_U8_to_str(const til_U8* til_U8_self) {
    til_I64 _tmp_til_U8_to_str_0 = til_U8_to_i64(til_U8_self);
    return til_I64_to_str(&_tmp_til_U8_to_str_0);
    return (til_Str){};
}

int til_U8_from_str(til_U8* _ret, til_U8_Overflow* _err1, const til_Str* til_Str_s) {
    til_I64 _tmp_til_U8_from_str_1 = til_I64_from_str(til_Str_s);
    til_U8_Overflow _err0__tmp_til_U8_from_str_0 = {};
    int __attribute__((unused)) _status__tmp_til_U8_from_str_0 = til_U8_from_i64(_ret, &_err0__tmp_til_U8_from_str_0, &_tmp_til_U8_from_str_1);
    if (_status__tmp_til_U8_from_str_0 == 1) { *_err1 = _err0__tmp_til_U8_from_str_0; return 1; }
    return 0;
    return 0;
}

void til_U8_inc(til_U8* til_U8_self) {
    til_U8 til_U8_one = 1;
    *til_U8_self = til_U8_add(til_U8_self, &til_U8_one);
}

void til_U8_dec(til_U8* til_U8_self) {
    til_U8 til_U8_one = 1;
    *til_U8_self = til_U8_sub(til_U8_self, &til_U8_one);
}

til_Bool til_U8_gteq(const til_U8* til_U8_a, const til_U8* til_U8_b) {
    if (til_U8_gt(til_U8_a, til_U8_b).data) {
        return true;
    }
    if (til_U8_lt(til_U8_a, til_U8_b).data) {
        return false;
    }
    return true;
    return (til_Bool){};
}

til_Bool til_U8_lteq(const til_U8* til_U8_a, const til_U8* til_U8_b) {
    if (til_U8_lt(til_U8_a, til_U8_b).data) {
        return true;
    }
    if (til_U8_gt(til_U8_a, til_U8_b).data) {
        return false;
    }
    return true;
    return (til_Bool){};
}

til_I64 til_U8_size(void) {
    return 1;
    return (til_I64){};
}

void til_U8_delete(til_U8* _self) {
    (void)_self;
}

til_U8 til_U8_clone(const til_U8* til_U8_self) {
    return (*til_U8_self);
    return (til_U8){};
}

void til_HeapState_enable(void) {
    til_Vec_g_entries = til_Vec_new("HeapEntry");
    til_Bool_g_enabled = til_Bool_clone(&true);
}

void til_HeapState_disable(void) {
    til_Bool_g_enabled = til_Bool_clone(&false);
}

void til_HeapState_add(const til_I64* til_I64_ptr, const til_I64* til_I64_size) {
    if (til_not(&til_Bool_g_enabled).data) {
        return;
    }
    til_I64 _tmp_til_HeapState_add_0 = til_I64_clone(til_I64_ptr);
    til_I64 _tmp_til_HeapState_add_1 = til_I64_clone(til_I64_size);
    til_HeapEntry til_HeapEntry_entry = {.ptr = _tmp_til_HeapState_add_0, .size = _tmp_til_HeapState_add_1};
    til_Vec_push(&til_Vec_g_entries, (til_Dynamic*)&til_HeapEntry_entry);
}

void til_HeapState_remove(const til_I64* til_I64_ptr) {
    til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp_til_HeapState_remove_0 = {};
    if (til_not(&til_Bool_g_enabled).data) {
        return;
    }
    til_I64 _tmp_til_HeapState_remove_1 = 0;
    if (til_I64_eq(til_I64_ptr, &_tmp_til_HeapState_remove_1).data) {
        return;
    }
    til_I64 til_I64_i = 0;
    til_HeapEntry til_HeapEntry_entry;
    til_HeapEntry til_HeapEntry_freed;
    til_I64 _tmp_til_HeapState_remove_2 = 0;
    til_I64 _tmp_til_HeapState_remove_3 = til_Vec_len(&til_Vec_g_entries);
    if (til_I64_lt(&_tmp_til_HeapState_remove_2, &_tmp_til_HeapState_remove_3).data) {
        while (1) {
            til_I64 _tmp_til_HeapState_remove_4 = til_Vec_len(&til_Vec_g_entries);
            if (!(til_I64_lt(&til_I64_i, &_tmp_til_HeapState_remove_4).data)) break;
            til_Ptr _tmp_til_HeapState_remove_5;
            til_IndexOutOfBoundsError _err0__tmp_til_HeapState_remove_6;
            int __attribute__((unused)) _status__tmp_til_HeapState_remove_6 = til_Vec_get(&_tmp_til_HeapState_remove_5, &_err0__tmp_til_HeapState_remove_6, &til_Vec_g_entries, &til_I64_i);
            if (_status__tmp_til_HeapState_remove_6 == 1) { _thrown_IndexOutOfBoundsError__tmp_til_HeapState_remove_0 = _err0__tmp_til_HeapState_remove_6; goto _catch_IndexOutOfBoundsError__tmp_til_HeapState_remove_0; }
            til_HeapEntry* til_HeapEntry_entry;
            til_HeapEntry_entry = (til_HeapEntry*)_tmp_til_HeapState_remove_5.data;
            if (til_I64_eq(&til_HeapEntry_entry->ptr, til_I64_ptr).data) {
                til_I64 _tmp_til_HeapState_remove_7 = til_I64_clone(&til_HeapEntry_entry->size);
                til_HeapEntry_freed = (til_HeapEntry){.ptr = 0, .size = _tmp_til_HeapState_remove_7};
                til_IndexOutOfBoundsError _err0__tmp_til_HeapState_remove_8 = {};
                int __attribute__((unused)) _status__tmp_til_HeapState_remove_8 = til_Vec_set(&_err0__tmp_til_HeapState_remove_8, &til_Vec_g_entries, &til_I64_i, (til_Dynamic*)&til_HeapEntry_freed);
                return;
            }
            til_I64_inc(&til_I64_i);
        }
    } else {
        while (1) {
            til_I64 _tmp_til_HeapState_remove_9 = til_Vec_len(&til_Vec_g_entries);
            if (!(til_I64_gt(&til_I64_i, &_tmp_til_HeapState_remove_9).data)) break;
            til_Ptr _tmp_til_HeapState_remove_10;
            til_IndexOutOfBoundsError _err0__tmp_til_HeapState_remove_11;
            int __attribute__((unused)) _status__tmp_til_HeapState_remove_11 = til_Vec_get(&_tmp_til_HeapState_remove_10, &_err0__tmp_til_HeapState_remove_11, &til_Vec_g_entries, &til_I64_i);
            if (_status__tmp_til_HeapState_remove_11 == 1) { _thrown_IndexOutOfBoundsError__tmp_til_HeapState_remove_0 = _err0__tmp_til_HeapState_remove_11; goto _catch_IndexOutOfBoundsError__tmp_til_HeapState_remove_0; }
            til_HeapEntry* til_HeapEntry_entry;
            til_HeapEntry_entry = (til_HeapEntry*)_tmp_til_HeapState_remove_10.data;
            if (til_I64_eq(&til_HeapEntry_entry->ptr, til_I64_ptr).data) {
                til_I64 _tmp_til_HeapState_remove_12 = til_I64_clone(&til_HeapEntry_entry->size);
                til_HeapEntry_freed = (til_HeapEntry){.ptr = 0, .size = _tmp_til_HeapState_remove_12};
                til_IndexOutOfBoundsError _err0__tmp_til_HeapState_remove_13 = {};
                int __attribute__((unused)) _status__tmp_til_HeapState_remove_13 = til_Vec_set(&_err0__tmp_til_HeapState_remove_13, &til_Vec_g_entries, &til_I64_i, (til_Dynamic*)&til_HeapEntry_freed);
                return;
            }
            til_I64_dec(&til_I64_i);
        }
    }
    til_Array _tmp_til_HeapState_remove_14;
    til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_HeapState_remove_15;
    til_Str _tmp_til_HeapState_remove_16 = ((til_Str){((til_Ptr){(til_I64)"HEAP_STATE PANIC: double-free for pointer", 1, 0, 0, 0}), 41, 0});
    til_Str _tmp_til_HeapState_remove_17 = til_I64_to_str(til_I64_ptr);
    til_Type _tmp_til_HeapState_remove_18 = "Str";
    til_I64 _tmp_til_HeapState_remove_19 = 2;
    _tmp_til_HeapState_remove_14 = til_Array_new(_tmp_til_HeapState_remove_18, &_tmp_til_HeapState_remove_19);
    int __attribute__((unused)) _arr_status__tmp_til_HeapState_remove_15;
    til_I64 _tmp_til_HeapState_remove_20 = 0;
    _arr_status__tmp_til_HeapState_remove_15 = til_Array_set(&_err_idx__tmp_til_HeapState_remove_15, &_tmp_til_HeapState_remove_14, &_tmp_til_HeapState_remove_20, (til_Dynamic*)&_tmp_til_HeapState_remove_16);
    til_I64 _tmp_til_HeapState_remove_21 = 1;
    _arr_status__tmp_til_HeapState_remove_15 = til_Array_set(&_err_idx__tmp_til_HeapState_remove_15, &_tmp_til_HeapState_remove_14, &_tmp_til_HeapState_remove_21, (til_Dynamic*)&_tmp_til_HeapState_remove_17);
    til_println(&_tmp_til_HeapState_remove_14);
    til_Array_delete(&_tmp_til_HeapState_remove_14);
    til_I64 _tmp_til_HeapState_remove_22 = 1;
    til_exit(&_tmp_til_HeapState_remove_22);
    if (0) { _catch_IndexOutOfBoundsError__tmp_til_HeapState_remove_0:;
        til_IndexOutOfBoundsError til_IndexOutOfBoundsError_err = _thrown_IndexOutOfBoundsError__tmp_til_HeapState_remove_0;
        til_Array _tmp_til_HeapState_remove_23;
        til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_HeapState_remove_24;
        til_Str _tmp_til_HeapState_remove_25 = ((til_Str){((til_Ptr){(til_I64)"HEAP_STATE: unexpected index error in remove", 1, 0, 0, 0}), 44, 0});
        til_Type _tmp_til_HeapState_remove_26 = "Str";
        til_I64 _tmp_til_HeapState_remove_27 = 1;
        _tmp_til_HeapState_remove_23 = til_Array_new(_tmp_til_HeapState_remove_26, &_tmp_til_HeapState_remove_27);
        int __attribute__((unused)) _arr_status__tmp_til_HeapState_remove_24;
        til_I64 _tmp_til_HeapState_remove_28 = 0;
        _arr_status__tmp_til_HeapState_remove_24 = til_Array_set(&_err_idx__tmp_til_HeapState_remove_24, &_tmp_til_HeapState_remove_23, &_tmp_til_HeapState_remove_28, (til_Dynamic*)&_tmp_til_HeapState_remove_25);
        til_println(&_tmp_til_HeapState_remove_23);
        til_Array_delete(&_tmp_til_HeapState_remove_23);
        til_I64 _tmp_til_HeapState_remove_29 = 1;
        til_exit(&_tmp_til_HeapState_remove_29);
    }
}

void til_HeapState_report(void) {
    if (til_not(&til_Bool_g_enabled).data) {
        return;
    }
    til_I64 til_I64_leaked = 0;
    til_I64 til_I64_leaked_bytes = 0;
    til_I64 _for_i_0 = 0;
    til_Ptr _ref_forin_0;
    til_HeapEntry til_HeapEntry_entry;
    while (1) {
        til_I64 _tmp_til_HeapState_report_0 = til_Vec_len(&til_Vec_g_entries);
        if (!(til_I64_lt(&_for_i_0, &_tmp_til_HeapState_report_0).data)) break;
        til_IndexOutOfBoundsError _thrown_IndexOutOfBoundsError__tmp_til_HeapState_report_1 = {};
        til_IndexOutOfBoundsError _err0__tmp_til_HeapState_report_2 = {};
        int __attribute__((unused)) _status__tmp_til_HeapState_report_2 = til_Vec_get(&_ref_forin_0, &_err0__tmp_til_HeapState_report_2, &til_Vec_g_entries, &_for_i_0);
        if (_status__tmp_til_HeapState_report_2 == 1) { _thrown_IndexOutOfBoundsError__tmp_til_HeapState_report_1 = _err0__tmp_til_HeapState_report_2; goto _catch_IndexOutOfBoundsError__tmp_til_HeapState_report_1; }
        if (0) { _catch_IndexOutOfBoundsError__tmp_til_HeapState_report_1:;
            til_IndexOutOfBoundsError _err_forin_0 = _thrown_IndexOutOfBoundsError__tmp_til_HeapState_report_1;
            til_Array _tmp_til_HeapState_report_3;
            til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_HeapState_report_4;
            til_Type _tmp_til_HeapState_report_5 = "Str";
            til_I64 _tmp_til_HeapState_report_6 = 0;
            _tmp_til_HeapState_report_3 = til_Array_new(_tmp_til_HeapState_report_5, &_tmp_til_HeapState_report_6);
            int __attribute__((unused)) _arr_status__tmp_til_HeapState_report_4;
            til_panic(&((til_Str){((til_Ptr){(til_I64)"src/core/heap_state.til:57:9:", 1, 0, 0, 0}), 29, 0}), &_err_forin_0.msg, &_tmp_til_HeapState_report_3);
            til_Array_delete(&_tmp_til_HeapState_report_3);
        }
        til_HeapEntry* til_HeapEntry_entry;
        til_HeapEntry_entry = (til_HeapEntry*)_ref_forin_0.data;
        til_I64 _tmp_til_HeapState_report_7 = 0;
        til_Bool _tmp_til_HeapState_report_8 = til_I64_eq(&til_HeapEntry_entry->ptr, &_tmp_til_HeapState_report_7);
        if (til_not(&_tmp_til_HeapState_report_8).data) {
            til_I64 _tmp_til_HeapState_report_9 = 1;
            til_I64_leaked = til_I64_add(&til_I64_leaked, &_tmp_til_HeapState_report_9);
            til_I64_leaked_bytes = til_I64_add(&til_I64_leaked_bytes, &til_HeapEntry_entry->size);
        }
        til_I64 _tmp_til_HeapState_report_10 = 1;
        _for_i_0 = til_I64_add(&_for_i_0, &_tmp_til_HeapState_report_10);
    }
    til_Str _tmp_til_HeapState_report_11;
    til_Array _tmp_til_HeapState_report_12;
    til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_HeapState_report_13;
    til_Str _tmp_til_HeapState_report_14 = til_I64_to_str(&til_I64_leaked);
    til_Str _tmp_til_HeapState_report_15 = ((til_Str){((til_Ptr){(til_I64)" allocations, ", 1, 0, 0, 0}), 14, 0});
    til_Str _tmp_til_HeapState_report_16 = til_I64_to_str(&til_I64_leaked_bytes);
    til_Str _tmp_til_HeapState_report_17 = ((til_Str){((til_Ptr){(til_I64)" bytes", 1, 0, 0, 0}), 6, 0});
    til_Type _tmp_til_HeapState_report_18 = "Str";
    til_I64 _tmp_til_HeapState_report_19 = 4;
    _tmp_til_HeapState_report_12 = til_Array_new(_tmp_til_HeapState_report_18, &_tmp_til_HeapState_report_19);
    int __attribute__((unused)) _arr_status__tmp_til_HeapState_report_13;
    til_I64 _tmp_til_HeapState_report_20 = 0;
    _arr_status__tmp_til_HeapState_report_13 = til_Array_set(&_err_idx__tmp_til_HeapState_report_13, &_tmp_til_HeapState_report_12, &_tmp_til_HeapState_report_20, (til_Dynamic*)&_tmp_til_HeapState_report_14);
    til_I64 _tmp_til_HeapState_report_21 = 1;
    _arr_status__tmp_til_HeapState_report_13 = til_Array_set(&_err_idx__tmp_til_HeapState_report_13, &_tmp_til_HeapState_report_12, &_tmp_til_HeapState_report_21, (til_Dynamic*)&_tmp_til_HeapState_report_15);
    til_I64 _tmp_til_HeapState_report_22 = 2;
    _arr_status__tmp_til_HeapState_report_13 = til_Array_set(&_err_idx__tmp_til_HeapState_report_13, &_tmp_til_HeapState_report_12, &_tmp_til_HeapState_report_22, (til_Dynamic*)&_tmp_til_HeapState_report_16);
    til_I64 _tmp_til_HeapState_report_23 = 3;
    _arr_status__tmp_til_HeapState_report_13 = til_Array_set(&_err_idx__tmp_til_HeapState_report_13, &_tmp_til_HeapState_report_12, &_tmp_til_HeapState_report_23, (til_Dynamic*)&_tmp_til_HeapState_report_17);
    _tmp_til_HeapState_report_11 = til_format(&((til_Str){((til_Ptr){(til_I64)"HEAP_STATE: leaked ", 1, 0, 0, 0}), 19, 0}), &_tmp_til_HeapState_report_12);
    til_Array_delete(&_tmp_til_HeapState_report_12);
    til_Array _tmp_til_HeapState_report_24;
    til_IndexOutOfBoundsError __attribute__((unused)) _err_idx__tmp_til_HeapState_report_25;
    til_Str _tmp_til_HeapState_report_26 = _tmp_til_HeapState_report_11;
    til_Type _tmp_til_HeapState_report_27 = "Str";
    til_I64 _tmp_til_HeapState_report_28 = 1;
    _tmp_til_HeapState_report_24 = til_Array_new(_tmp_til_HeapState_report_27, &_tmp_til_HeapState_report_28);
    int __attribute__((unused)) _arr_status__tmp_til_HeapState_report_25;
    til_I64 _tmp_til_HeapState_report_29 = 0;
    _arr_status__tmp_til_HeapState_report_25 = til_Array_set(&_err_idx__tmp_til_HeapState_report_25, &_tmp_til_HeapState_report_24, &_tmp_til_HeapState_report_29, (til_Dynamic*)&_tmp_til_HeapState_report_26);
    til_println(&_tmp_til_HeapState_report_24);
    til_Array_delete(&_tmp_til_HeapState_report_24);
}

void til_HeapEntry_delete(til_HeapEntry* _self) {
    (void)_self;
}

til_HeapEntry til_HeapEntry_clone(const til_HeapEntry* til_HeapEntry_self) {
    return (til_HeapEntry){.ptr = til_I64_clone(&til_HeapEntry_self->ptr), .size = til_I64_clone(&til_HeapEntry_self->size)};
    return (til_HeapEntry){};
}

void til_HeapState_delete(til_HeapState* _self) {
    (void)_self;
}

til_HeapState til_HeapState_clone(const til_HeapState* _self) {
    (void)_self;
    return (til_HeapState){};
    return (til_HeapState){};
}

void til_Dynamic_delete(til_Dynamic* _self) {
    (void)_self;
}

til_Dynamic til_Dynamic_clone(const til_Dynamic* _self) {
    (void)_self;
    return (til_Dynamic){};
    return (til_Dynamic){};
}

void til_Type_delete(til_Type* _self) {
    (void)_self;
}

til_Type til_Type_clone(til_Type _self) {
    (void)_self;
    return (til_Type){};
    return (til_Type){};
}

til_CfVec2 til_CfVec2_magic(void) {
    return (til_CfVec2){.x = 42, .y = 99};
    return (til_CfVec2){};
}

til_CfVec2 til_CfVec2_at(const til_I64* til_I64_x, const til_I64* til_I64_y) {
    return (til_CfVec2){.x = til_I64_clone(til_I64_x), .y = til_I64_clone(til_I64_y)};
    return (til_CfVec2){};
}

til_CfRect til_CfRect_sample(void) {
    return (til_CfRect){.top_left = (til_CfVec2){.x = 5, .y = 10}, .bottom_right = (til_CfVec2){.x = 100, .y = 200}};
    return (til_CfRect){};
}

void til_CfVec2_delete(til_CfVec2* _self) {
    (void)_self;
}

til_CfVec2 til_CfVec2_clone(const til_CfVec2* til_CfVec2_self) {
    return (til_CfVec2){.x = til_I64_clone(&til_CfVec2_self->x), .y = til_I64_clone(&til_CfVec2_self->y)};
    return (til_CfVec2){};
}

void til_CfRect_delete(til_CfRect* til_CfRect_self) {
    til_CfVec2_delete(&til_CfRect_self->bottom_right);
    til_CfVec2_delete(&til_CfRect_self->top_left);
}

til_CfRect til_CfRect_clone(const til_CfRect* til_CfRect_self) {
    return (til_CfRect){.top_left = til_CfVec2_clone(&til_CfRect_self->top_left), .bottom_right = til_CfVec2_clone(&til_CfRect_self->bottom_right)};
    return (til_CfRect){};
}

int main(int argc, char** argv) {
    (void)argc; (void)argv;
    til_Ptr _tmp_0 = (til_Ptr){.data = 0, .is_borrowed = 0, .alloc_size = 0, .elem_type = 0, .elem_size = 0};
    til_Vec_g_entries = (til_Vec){.ptr = _tmp_0, ._len = 0, .cap = 0};
    til_Bool_g_enabled = til_Bool_clone(&false);
    til_test_simple_add();
    til_test_nested_arithmetic();
    til_test_deeply_nested();
    til_test_string_concat();
    til_test_fold_variable();
    til_test_loc_folded_correctly();
    til_test_struct_fold_simple();
    til_test_struct_fold_values();
    til_test_struct_fold_nested();
    for (int _i = 1; _i < argc; _i++) {
        if (strcmp(argv[_i], "--mem-report") == 0) {
            til_HeapState_enable();
            for (int _j = _i; _j < argc - 1; _j++) argv[_j] = argv[_j + 1];
            argc--; _i--;
        }
    }
    til_HeapState_report();
    return 0;
}
