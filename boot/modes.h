#pragma once
#include "ext.h"

typedef struct Array Array;
typedef struct Map Map;
typedef struct DynMap DynMap;
typedef struct Set Set;
typedef struct Str Str;
typedef struct Vec Vec;
typedef struct Tuple Tuple;
typedef struct StructDef StructDef;
typedef struct EnumDef EnumDef;
typedef enum {
    TilType_TAG_Unknown,
    TilType_TAG_None,
    TilType_TAG_I64,
    TilType_TAG_U8,
    TilType_TAG_I16,
    TilType_TAG_I32,
    TilType_TAG_U32,
    TilType_TAG_U64,
    TilType_TAG_F32,
    TilType_TAG_Bool,
    TilType_TAG_Struct,
    TilType_TAG_StructDef,
    TilType_TAG_Enum,
    TilType_TAG_EnumDef,
    TilType_TAG_FuncDef,
    TilType_TAG_FuncPtr,
    TilType_TAG_Dynamic
} TilType_tag;
typedef struct TilType TilType;
typedef struct Declaration Declaration;
typedef enum {
    FuncType_TAG_Func,
    FuncType_TAG_Proc,
    FuncType_TAG_Test,
    FuncType_TAG_Macro,
    FuncType_TAG_ExtFunc,
    FuncType_TAG_ExtProc
} FuncType_tag;
typedef struct FuncType FuncType;
typedef enum {
    OwnType_TAG_Own,
    OwnType_TAG_Ref,
    OwnType_TAG_Shallow
} OwnType_tag;
typedef struct OwnType OwnType;
typedef struct Param Param;
typedef struct FunctionDef FunctionDef;
typedef struct FCallData FCallData;
typedef struct FieldDef FieldDef;
typedef struct StructDefData StructDefData;
typedef enum {
    NodeType_TAG_Body,
    NodeType_TAG_LiteralStr,
    NodeType_TAG_LiteralNum,
    NodeType_TAG_LiteralBool,
    NodeType_TAG_LiteralNull,
    NodeType_TAG_Ident,
    NodeType_TAG_Decl,
    NodeType_TAG_Assign,
    NodeType_TAG_FCall,
    NodeType_TAG_FuncDef,
    NodeType_TAG_StructDef,
    NodeType_TAG_EnumDef,
    NodeType_TAG_FieldAccess,
    NodeType_TAG_FieldAssign,
    NodeType_TAG_Return,
    NodeType_TAG_If,
    NodeType_TAG_While,
    NodeType_TAG_ForIn,
    NodeType_TAG_NamedArg,
    NodeType_TAG_Break,
    NodeType_TAG_Continue,
    NodeType_TAG_MapLit,
    NodeType_TAG_SetLit,
    NodeType_TAG_Switch,
    NodeType_TAG_Case
} NodeType_tag;
typedef struct NodeType NodeType;
typedef struct Expr Expr;
typedef struct Range Range;
typedef struct Dynamic Dynamic;
typedef enum {
    TokenType_TAG_Eof,
    TokenType_TAG_LParen,
    TokenType_TAG_RParen,
    TokenType_TAG_LBrace,
    TokenType_TAG_RBrace,
    TokenType_TAG_LBracket,
    TokenType_TAG_RBracket,
    TokenType_TAG_Comma,
    TokenType_TAG_Colon,
    TokenType_TAG_Question,
    TokenType_TAG_Bang,
    TokenType_TAG_Minus,
    TokenType_TAG_Plus,
    TokenType_TAG_Star,
    TokenType_TAG_Slash,
    TokenType_TAG_Dot,
    TokenType_TAG_DotDot,
    TokenType_TAG_DotDotDot,
    TokenType_TAG_Eq,
    TokenType_TAG_EqEq,
    TokenType_TAG_Neq,
    TokenType_TAG_Lt,
    TokenType_TAG_LtEq,
    TokenType_TAG_Gt,
    TokenType_TAG_GtEq,
    TokenType_TAG_ColonEq,
    TokenType_TAG_Ident,
    TokenType_TAG_StringTok,
    TokenType_TAG_Number,
    TokenType_TAG_Char,
    TokenType_TAG_KwMode,
    TokenType_TAG_KwMut,
    TokenType_TAG_KwOwn,
    TokenType_TAG_KwRef,
    TokenType_TAG_KwShallow,
    TokenType_TAG_KwStruct,
    TokenType_TAG_KwEnum,
    TokenType_TAG_KwNamespace,
    TokenType_TAG_KwFunc,
    TokenType_TAG_KwProc,
    TokenType_TAG_KwTest,
    TokenType_TAG_KwMacro,
    TokenType_TAG_KwExtFunc,
    TokenType_TAG_KwExtProc,
    TokenType_TAG_KwReturns,
    TokenType_TAG_KwThrows,
    TokenType_TAG_KwIf,
    TokenType_TAG_KwElse,
    TokenType_TAG_KwWhile,
    TokenType_TAG_KwFor,
    TokenType_TAG_KwIn,
    TokenType_TAG_KwSwitch,
    TokenType_TAG_KwMatch,
    TokenType_TAG_KwCase,
    TokenType_TAG_KwDefault,
    TokenType_TAG_KwReturn,
    TokenType_TAG_KwThrow,
    TokenType_TAG_KwCatch,
    TokenType_TAG_KwBreak,
    TokenType_TAG_KwContinue,
    TokenType_TAG_KwDefer,
    TokenType_TAG_KwTrue,
    TokenType_TAG_KwFalse,
    TokenType_TAG_KwNull,
    TokenType_TAG_Error
} TokenType_tag;
typedef struct TokenType TokenType;
typedef struct Token Token;
typedef struct Parser Parser;
typedef struct TypeBinding TypeBinding;
typedef enum {
    ScopeFind_TAG_NotFound,
    ScopeFind_TAG_Found
} ScopeFind_tag;
typedef struct ScopeFind ScopeFind;
typedef struct TypeScope TypeScope;
typedef struct LocalInfo LocalInfo;
typedef enum {
    CtorArg_TAG_Unfilled,
    CtorArg_TAG_Filled
} CtorArg_tag;
typedef struct CtorArg CtorArg;
typedef struct StructInstance StructInstance;
typedef struct EnumInstance EnumInstance;
typedef enum {
    Value_TAG_None,
    Value_TAG_Int,
    Value_TAG_Byte,
    Value_TAG_Short,
    Value_TAG_Int32,
    Value_TAG_Uint32,
    Value_TAG_Uint64,
    Value_TAG_Float,
    Value_TAG_Boolean,
    Value_TAG_Func,
    Value_TAG_Struct,
    Value_TAG_Enum,
    Value_TAG_Ptr
} Value_tag;
typedef struct Value Value;
typedef struct Cell Cell;
typedef struct Binding Binding;
typedef struct Scope Scope;
typedef struct CollectionInfo CollectionInfo;
typedef struct DynCallInfo DynCallInfo;
typedef struct ExtStr ExtStr;
typedef struct FFIType FFIType;
typedef struct FFIEntry FFIEntry;
typedef struct ExprPtrBox ExprPtrBox;
typedef struct Mode Mode;
typedef struct Context Context;

typedef struct Str {
    U8 *c_str;
    U32 count;
    U32 cap;
} Str;


typedef struct Vec {
    U8 *data;
    U32 count;
    U32 cap;
    U32 elem_size;
    Str elem_type;
    void * elem_clone;
    void * elem_delete;
} Vec;


typedef struct Tuple {
    U8 *data;
    U32 total_size;
    U32 cap;
    Vec type_names;
    Vec type_sizes;
} Tuple;


typedef struct StructDef {
    char _;
} StructDef;


typedef struct EnumDef {
    char _;
} EnumDef;


struct TilType {
    TilType_tag tag;
};

typedef struct Declaration {
    Str name;
    Str explicit_type;
    Bool is_mut;
    Bool is_namespace;
    Bool is_ref;
    Bool is_own;
    I32 field_offset;
    I32 field_size;
    Expr *field_struct_def;
    Expr *fn_sig;
} Declaration;


struct FuncType {
    FuncType_tag tag;
};

struct OwnType {
    OwnType_tag tag;
};

typedef struct Param {
    Str name;
    Str ptype;
    Bool is_mut;
    OwnType own_type;
} Param;


typedef struct FCallData {
    Bool is_proc;
    I32 variadic_index;
    U32 variadic_count;
    I32 kwargs_index;
    U32 kwargs_count;
    Expr *fn_sig;
} FCallData;


typedef struct FieldDef {
    Declaration decl;
    Expr *default_value;
} FieldDef;


typedef struct StructDefData {
    I32 total_struct_size;
    Vec fields;
} StructDefData;









typedef struct Range {
    U64 start;
    U64 end;
} Range;



typedef struct Dynamic {
    char _;
} Dynamic;


struct TokenType {
    TokenType_tag tag;
};

typedef struct Token {
    TokenType type;
    Str text;
    U32 line;
    U32 col;
} Token;


typedef struct Parser {
    Vec tokens;
    U32 pos;
    Str path;
    Vec fn_sig_decls;
} Parser;


typedef struct TypeBinding {
    Str *name;
    TilType type;
    I32 is_proc;
    Bool is_mut;
    U32 line;
    U32 col;
    Bool is_param;
    Bool is_own;
    Bool is_ref;
    Bool is_alias;
    Bool is_type_alias;
    Str *alias_target;
    Expr *struct_def;
    Expr *func_def;
    Bool is_builtin;
    Str struct_name;
} TypeBinding;


struct ScopeFind {
    ScopeFind_tag tag;
    union {
        TypeBinding Found;
    } data;
};

typedef struct LocalInfo {
    Str *name;
    TilType type;
    Str *struct_name;
    I32 decl_index;
    I32 last_use;
    I32 own_transfer;
    Bool skip_scope_delete;
} LocalInfo;


typedef struct StructInstance {
    Str *struct_name;
    Expr *struct_def;
    U8 *data;
    Bool borrowed;
} StructInstance;


typedef struct EnumInstance {
    Str *enum_name;
    Expr *enum_def;
    U8 *data;
    I32 data_size;
} EnumInstance;


struct Value {
    Value_tag tag;
    union {
        I64 Int;
        U8 Byte;
        I16 Short;
        I32 Int32;
        U32 Uint32;
        U64 Uint64;
        F32 Float;
        Bool Boolean;
        void * Func;
        StructInstance Struct;
        EnumInstance Enum;
        void * Ptr;
    } data;
};

typedef struct Cell {
    Value val;
} Cell;


typedef struct Binding {
    Str *name;
    Cell *cell;
    Bool cell_is_local;
} Binding;


typedef struct CollectionInfo {
    Str *type_name;
    I32 is_vec;
} CollectionInfo;


typedef struct DynCallInfo {
    Str *method;
    I32 nargs;
    Bool has_return;
} DynCallInfo;


typedef struct ExtStr {
    U8 *data;
    U64 count;
    U64 cap;
} ExtStr;


typedef struct FFIType {
    U32 size;
    I16 alignment;
    I16 type;
    void * *elements;
} FFIType;


typedef struct FFIEntry {
    U8 *fn;
    Str *return_type;
    I32 nparam;
    U8 *param_shallows;
    Bool return_is_shallow;
    U8 *cif;
    U8 *arg_types;
} FFIEntry;


typedef struct ExprPtrBox {
    Expr *ptr;
} ExprPtrBox;


typedef struct Mode {
    Bool needs_main;
    Bool decls_only;
    Str auto_import;
    Bool is_library;
    Bool is_pure;
    Bool run_tests;
    Bool debug_prints;
} Mode;


typedef struct Array {
    U8 *data;
    U32 cap;
    U32 elem_size;
    Str elem_type;
    void * elem_clone;
    void * elem_delete;
} Array;


typedef struct Map {
    U8 *key_data;
    U8 *val_data;
    U32 count;
    U32 cap;
    U32 key_size;
    Str key_type;
    U32 val_size;
    Str val_type;
    void * key_clone;
    void * key_delete;
    void * key_cmp;
    void * val_clone;
    void * val_delete;
} Map;


typedef struct DynMap {
    Map items;
} DynMap;


typedef struct Set {
    U8 *data;
    U32 count;
    U32 cap;
    U32 elem_size;
    Str elem_type;
    void * elem_clone;
    void * elem_delete;
    void * elem_cmp;
} Set;


typedef struct FunctionDef {
    FuncType func_type;
    Vec params;
    U32 nparam;
    Map param_defaults;
    Str return_type;
    I32 variadic_index;
    I32 kwargs_index;
    OwnType return_own_type;
} FunctionDef;


struct NodeType {
    NodeType_tag tag;
    union {
        Str LiteralStr;
        Str LiteralNum;
        Bool LiteralBool;
        Str Ident;
        Declaration Decl;
        Str Assign;
        FCallData FCall;
        FunctionDef FuncDef;
        StructDefData StructDef;
        Str FieldAccess;
        Str FieldAssign;
        Str ForIn;
        Str NamedArg;
    } data;
};

typedef struct Expr {
    NodeType data;
    TilType til_type;
    Str struct_name;
    Bool is_own_arg;
    Bool is_splat;
    Bool is_own_field;
    Bool is_ref_field;
    Bool is_ns_field;
    Bool is_core;
    Bool save_old_delete;
    I32 variadic_index;
    U32 variadic_count;
    I32 kwargs_index;
    U32 kwargs_count;
    Expr *fn_sig;
    Vec children;
    U32 line;
    U32 col;
    Str path;
} Expr;


typedef struct TypeScope {
    Map bindings;
    TypeScope *parent;
} TypeScope;


struct CtorArg {
    CtorArg_tag tag;
    union {
        Expr Filled;
    } data;
};

typedef struct Scope {
    Map bindings;
    Scope *parent;
} Scope;


typedef struct Context {
    Mode mode_;
    Map path_modes;
} Context;


Array * Array_new(Str * elem_type, U32 * elem_size, U32 * cap);
U32 * Array_len(Array * self);
void * Array_get(Array * self, U32 * i);
void Array_set(Array * self, U32 * i, void * val);
void Array_delete(Array * self, Bool * call_free);
Array * Array_clone(Array * self);
U32 * Array_size(void);
Map * Map_new(Str * key_type, U32 * key_size, Str * val_type, U32 * val_size);
U32 * Map_len(Map * self);
Bool Map_has(Map * self, void * key);
void * Map_get(Map * self, void * key);
void Map_set(Map * self, void * key, void * val);
void Map_delete(Map * self, Bool * call_free);
Map * Map_clone(Map * self);
U32 * Map_size(void);
DynMap * DynMap_new(void);
U32 * DynMap_len(DynMap * self);
Bool DynMap_has(DynMap * self, Str * key);
void DynMap_set(DynMap * self, Str * key, Str * elem_type, U32 * elem_size, void * val);
void * DynMap_get(DynMap * self, Str * key);
Str * DynMap_type_at(DynMap * self, Str * key);
U32 * DynMap_size_at(DynMap * self, Str * key);
DynMap * DynMap_clone(DynMap * self);
void DynMap_delete(DynMap * self, Bool * call_free);
U32 * DynMap_size(void);
Set * Set_new(Str * elem_type, U32 * elem_size);
U32 * Set_len(Set * self);
Bool Set_has(Set * self, void * val);
void Set_add(Set * self, void * val);
void Set_delete(Set * self, Bool * call_free);
Set * Set_clone(Set * self);
U32 * Set_size(void);
Str * format(Array * parts);
U32 Str_len(Str * self);
U8 * Str_get(Str * self, U32 * i);
U8 * Str_byte_at(Str * self, U32 * i);
I64 Str_cmp(Str * a, Str * b);
Str * Str_concat(Str * a, Str * b);
Str * Str_with_capacity(U32 * n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
void Str_delete(Str * self, Bool * call_free);
Str * Str_to_str(Str * val);
Str * Str_substr(Str * s, U32 * start, U32 * n);
Bool Str_contains(Str * a, Str * b);
Bool Str_starts_with(Str * a, Str * b);
Bool Str_ends_with(Str * a, Str * b);
Bool Str_is_empty(Str * self);
I64 Str_find(Str * self, Str * needle);
I64 Str_rfind(Str * self, Str * needle);
Str * Str_replace(Str * self, Str * from, Str * to);
Str * Str_get_char(Str * self, U32 * i);
Str * Str_strip_prefix(Str * self, Str * prefix);
Str * Str_strip_suffix(Str * self, Str * suffix);
Str * Str_from_byte(U8 * byte);
I64 Str_to_i64(Str * self);
U8 Str_to_u8(Str * self);
I32 Str_to_i32(Str * self);
F32 Str_to_f32(Str * self);
Vec * Str_split(Str * self, Str * delim);
U32 * Str_size(void);
Bool Str_eq(Str * a, Str * b);
Bool Str_lt(Str * a, Str * b);
Bool Str_gt(Str * a, Str * b);
Bool Str_neq(Str * a, Str * b);
Bool Str_lte(Str * a, Str * b);
Bool Str_gte(Str * a, Str * b);
Str * join(Vec * parts, Str * sep);
Vec * Vec_new(Str * elem_type, U32 * elem_size);
U32 Vec_len(Vec * self);
void Vec_push(Vec * self, void * val);
void Vec_append(Vec * self, Vec * other);
void * Vec_get(Vec * self, U32 * i);
void * Vec_pop(Vec * self);
Vec * Vec_take_prefix(Vec * self, U32 * n);
void Vec_set(Vec * self, U32 * i, void * val);
void Vec_delete(Vec * self, Bool * call_free);
Vec * Vec_clone(Vec * self);
U32 * Vec_size(void);
Tuple * Tuple_new(void);
U32 * Tuple_len(Tuple * self);
void Tuple_push(Tuple * self, Str * elem_type, U32 * elem_size, void * val);
void * Tuple_get(Tuple * self, U32 * i);
Str * Tuple_type_at(Tuple * self, U32 * i);
U32 * Tuple_size_at(Tuple * self, U32 * i);
void Tuple_delete(Tuple * self, Bool * call_free);
Tuple * Tuple_clone(Tuple * self);
U32 * Tuple_size(void);
EnumDef * EnumDef_clone(EnumDef * self);
void EnumDef_delete(EnumDef * self, Bool * call_free);
U32 * EnumDef_size(void);
Bool * TilType_is(TilType * self, TilType * other);
Bool * TilType_eq(TilType * self, TilType * other);
void TilType_delete(TilType * self, Bool * call_free);
Str * TilType_to_str(TilType * self);
TilType * TilType_clone(TilType * self);
U32 * TilType_size(void);
Str * til_type_name_c(TilType * t);
Bool * Declaration_eq(Declaration * a, Declaration * b);
Str * Declaration_to_str(Declaration * self);
Declaration * Declaration_clone(Declaration * self);
void Declaration_delete(Declaration * self, Bool * call_free);
U32 * Declaration_size(void);
Bool * FuncType_is(FuncType * self, FuncType * other);
Bool * FuncType_eq(FuncType * self, FuncType * other);
void FuncType_delete(FuncType * self, Bool * call_free);
Str * FuncType_to_str(FuncType * self);
FuncType * FuncType_clone(FuncType * self);
U32 * FuncType_size(void);
Bool * OwnType_is(OwnType * self, OwnType * other);
Bool * OwnType_eq(OwnType * self, OwnType * other);
void OwnType_delete(OwnType * self, Bool * call_free);
Str * OwnType_to_str(OwnType * self);
OwnType * OwnType_clone(OwnType * self);
U32 * OwnType_size(void);
Param * Param_clone(Param * self);
void Param_delete(Param * self, Bool * call_free);
U32 * Param_size(void);
Bool * FunctionDef_eq(FunctionDef * a, FunctionDef * b);
Str * FunctionDef_to_str(FunctionDef * self);
FunctionDef * FunctionDef_clone(FunctionDef * self);
void FunctionDef_delete(FunctionDef * self, Bool * call_free);
U32 * FunctionDef_size(void);
Bool * FCallData_eq(FCallData * a, FCallData * b);
Str * FCallData_to_str(FCallData * self);
FCallData * FCallData_clone(FCallData * self);
void FCallData_delete(FCallData * self, Bool * call_free);
U32 * FCallData_size(void);
Bool * FieldDef_eq(FieldDef * a, FieldDef * b);
Str * FieldDef_to_str(FieldDef * self);
FieldDef * FieldDef_clone(FieldDef * self);
void FieldDef_delete(FieldDef * self, Bool * call_free);
U32 * FieldDef_size(void);
Bool * StructDefData_eq(StructDefData * a, StructDefData * b);
Str * StructDefData_to_str(StructDefData * self);
StructDefData * StructDefData_clone(StructDefData * self);
void StructDefData_delete(StructDefData * self, Bool * call_free);
U32 * StructDefData_size(void);
Bool * NodeType_is(NodeType * self, NodeType * other);
Bool * NodeType_eq(NodeType * self, NodeType * other);
void NodeType_delete(NodeType * self, Bool * call_free);
Str * NodeType_to_str(NodeType * self);
NodeType * NodeType_clone(NodeType * self);
U32 * NodeType_size(void);
void Expr_error(Expr * self, Str * msg);
void Expr_todo_error(Expr * self, Str * msg);
void Expr_lang_error(Expr * self, Str * msg);
void Expr_add_child(Expr * self, Expr * child);
void Expr_push_child_clone(Expr * self, Expr * child);
void Expr_swap_children(Expr * self, Vec * new_children);
Expr * Expr_child(Expr * parent, U32 * i);
U32 Expr_child_count(Expr * parent);
Expr * Expr_new(NodeType * data, U32 line, U32 col, Str * path);
Expr * Expr_clone(Expr * self);
Bool Expr_eq(Expr * self, Expr * other);
Str * Expr_to_str(Expr * self);
void Expr_delete(Expr * self, Bool * call_free);
U32 * Expr_size(void);
Str * node_name(NodeType * data);
Str * func_type_name(FuncType * ft);
void ast_print(Expr * e, U32 indent);
Bool enum_has_payloads(Expr * enum_def);
I32 * enum_variant_tag(Expr * enum_def, Str * variant_name);
Str * enum_variant_type(Expr * enum_def, I32 tag);
Range * Range_new(U64 start, U64 end);
U64 * Range_len(Range * self);
U64 * Range_get(Range * self, U64 i);
Range * Range_clone(Range * val);
void Range_delete(Range * self, Bool * call_free);
U32 * Range_size(void);
U32 * Dynamic_size(void);
void * default_clone(void * v);
void default_delete(void * v, Bool * cf);
I64 * default_cmp(void * a, void * b);
void default_inc(void * v);
U32 * default_distance(void * a, void * b);
void println(Array * parts);
void print(Array * parts);
void swap(void * a, void * b, U64 size);
void move(void * dest, void * src, U64 size);
I64 * wait_cmd(I64 * pid);
I64 * run_cmd(Str * output, Array * args);
void panic(Str * loc_str, Array * parts);
void TODO(Str * loc_str, Array * parts);
void UNREACHABLE(Str * loc_str);
Bool * assert(Str * loc_str, Bool * cond);
void expect(Str * loc_str, Bool * cond, Array * parts);
void assert_eq(Str * loc_str, I64 * a, I64 * b);
void assert_eq_str(Str * loc_str, Str * a, Str * b);
Bool * TokenType_is(TokenType * self, TokenType * other);
Bool * TokenType_eq(TokenType * self, TokenType * other);
void TokenType_delete(TokenType * self, Bool * call_free);
Str * TokenType_to_str(TokenType * self);
TokenType * TokenType_clone(TokenType * self);
U32 * TokenType_size(void);
Token * Token_clone(Token * self);
void Token_delete(Token * self, Bool * call_free);
U32 * Token_size(void);
Bool * is_digit(U8 * c);
Bool * is_alpha(U8 * c);
Bool * is_alnum(U8 * c);
Str * tok_name(TokenType * type);
TokenType * lookup_keyword(Str * word);
Vec * tokenize(Str * src, Str * path);
Parser * Parser_clone(Parser * self);
void Parser_delete(Parser * self, Bool * call_free);
U32 * Parser_size(void);
Token * peek(Parser * p);
Token * advance(Parser * p);
Bool check(Parser * p, TokenType * type);
Token * expect_token(Parser * p, TokenType * type);
Str * expect_text(Parser * p, TokenType * type);
U32 peek_line(Parser * p);
U32 peek_col(Parser * p);
Str * parse_fn_signature(Parser * p, U32 line, U32 col);
Expr * parse_block(Parser * p);
Expr * parse_func_def(Parser * p);
Expr * parse_struct_def(Parser * p);
Expr * parse_enum_def(Parser * p);
Expr * parse_call(Parser * p, Str * name, U32 call_line, U32 call_col);
Expr * parse_expression(Parser * p);
Expr * parse_statement_ident(Parser * p, Bool is_mut, Bool is_own);
Expr * parse_statement(Parser * p);
Expr * parse(Vec * tokens, Str * path, Str * mode_out);
Bool TypeBinding_eq(TypeBinding * a, TypeBinding * b);
Str * TypeBinding_to_str(TypeBinding * self);
TypeBinding * TypeBinding_clone(TypeBinding * self);
void TypeBinding_delete(TypeBinding * self, Bool * call_free);
U32 * TypeBinding_size(void);
I32 align_up(I32 offset, I32 align);
TilType * type_from_name_init(Str * name, TypeScope * scope);
I32 register_struct_definitions(Expr * program, TypeScope * scope);
void generate_missing_struct_clones(Expr * program, TypeScope * scope);
I32 register_enum_definition(Expr * stmt, TypeScope * scope);
void collect_enum_variants(Expr * body, Vec * variant_names, Vec * variant_types, Bool * has_payloads);
void generate_enum_variant_constructors(Expr * body, Str * ename, U32 line, U32 col, Str * path, Vec * variant_names, Vec * variant_types, Bool has_payloads);
void generate_enum_is_method(Expr * body, Str * ename, U32 line, U32 col, Str * path);
void generate_enum_eq_method(Expr * body, Str * ename, U32 line, U32 col, Str * path, Vec * variant_names, Vec * variant_types, TypeScope * scope);
void generate_enum_delete_method(Expr * body, Str * ename, U32 line, U32 col, Str * path, Vec * variant_names, Vec * variant_types, Bool has_payloads, TypeScope * scope);
void generate_enum_to_str_method(Expr * body, Str * ename, U32 line, U32 col, Str * path, Vec * variant_names, Vec * variant_types, Bool has_payloads, TypeScope * scope);
void generate_enum_clone_method(Expr * body, Str * ename, I32 line, I32 col, Str * path, Vec * variant_names, Vec * variant_types, Bool has_payloads);
I32 register_enums_and_generate_nonclone_methods(Expr * program, TypeScope * scope);
void generate_missing_enum_clones(Expr * program);
void generate_missing_struct_deletes(Expr * program, TypeScope * scope);
void register_funcsig_aliases(Expr * program, TypeScope * scope);
void register_type_aliases(Expr * program, TypeScope * scope);
void register_top_level_values(Expr * program, TypeScope * scope);
void register_function_definitions(Expr * program, TypeScope * scope);
void generate_struct_size_methods(Expr * program);
void generate_enum_size_methods(Expr * program);
void generate_unity_derived_methods(Expr * program, TypeScope * scope);
void generate_size_methods(Expr * program, TypeScope * scope);
void generate_cmp_derived_methods(Expr * program, TypeScope * scope);
void generate_derived_methods(Expr * program, TypeScope * scope);
void compute_struct_layout(Expr * struct_def, TypeScope * scope);
void compute_all_struct_layouts(Expr * program, TypeScope * scope);
Bool infer_top_level_decl_type(Expr * stmt, TypeScope * scope, TilType * out_type, Str * out_struct_name);
I32 init_declarations(Expr * program, TypeScope * scope, Context * ctx);
void * Vec_take(Vec * v);
ScopeFind * ScopeFind_NotFound(void);
ScopeFind * ScopeFind_Found(TypeBinding * val);
Bool * ScopeFind_is(ScopeFind * self, ScopeFind * other);
Bool * ScopeFind_eq(ScopeFind * self, ScopeFind * other);
void ScopeFind_delete(ScopeFind * self, Bool * call_free);
Str * ScopeFind_to_str(ScopeFind * self);
ScopeFind * ScopeFind_clone(ScopeFind * self);
U32 * ScopeFind_size(void);
TypeScope * TypeScope_new(TypeScope * parent);
TypeBinding * TypeScope_get_binding(TypeScope * self, Str * name);
ScopeFind * TypeScope_find(TypeScope * self, Str * name);
TilType * TypeScope_get_type(TypeScope * self, Str * name);
I32 TypeScope_is_proc(TypeScope * self, Str * name);
Expr * TypeScope_get_struct(TypeScope * self, Str * name);
Bool TypeScope_is_mut(TypeScope * self, Str * name);
void TypeScope_set(TypeScope * self, Str * name, TilType * type, I32 is_proc, Bool is_mut, U32 line, U32 col, Bool is_param, Bool is_own);
TypeScope * TypeScope_clone(TypeScope * self);
void TypeScope_delete(TypeScope * self, Bool * call_free);
U32 * TypeScope_size(void);
LocalInfo * LocalInfo_clone(LocalInfo * self);
void LocalInfo_delete(LocalInfo * self, Bool * call_free);
U32 * LocalInfo_size(void);
CtorArg * CtorArg_Unfilled(void);
CtorArg * CtorArg_Filled(Expr * val);
Bool * CtorArg_is(CtorArg * self, CtorArg * other);
Bool * CtorArg_eq(CtorArg * self, CtorArg * other);
void CtorArg_delete(CtorArg * self, Bool * call_free);
Str * CtorArg_to_str(CtorArg * self);
CtorArg * CtorArg_clone(CtorArg * self);
U32 * CtorArg_size(void);
void type_error(Expr * e, Str * msg);
Expr * find_namespace_func(Expr * sdef, Str * method);
Bool try_ufcs_rewrite(TypeScope * scope, Expr * e, Expr * fa, Expr * obj, Str * method, Str * type_name);
Bool infer_func_ptr_field_call(TypeScope * scope, Expr * e, Expr * fa, Expr * obj, Expr * sdef, Str * method, I32 in_func, Context * ctx);
void validate_fcall_own_args(TypeScope * scope, Expr * e, TypeBinding * callee_bind);
Bool infer_struct_constructor_fcall(TypeScope * scope, Expr * e, Str * name, I32 in_func, Context * ctx);
void desugar_user_func_fcall_args(Expr * e, Str * name, TypeBinding * callee_bind);
void infer_and_validate_fcall_args(TypeScope * scope, Expr * e, TypeBinding * callee_bind, I32 in_func, Context * ctx);
void resolve_fcall_return_type(TypeScope * scope, Expr * e, Str * name, TypeBinding * callee_bind, I32 in_func, Context * ctx);
Bool infer_field_access_fcall(TypeScope * scope, Expr * e, I32 in_func, Context * ctx);
void infer_fcall_expr(TypeScope * scope, Expr * e, I32 in_func, Context * ctx);
void infer_expr(TypeScope * scope, Expr * expr, I32 in_func, Context * ctx);
void infer_ident_expr(TypeScope * scope, Expr * expr);
void infer_named_arg_expr(TypeScope * scope, Expr * expr, I32 in_func, Context * ctx);
void infer_map_lit_expr(TypeScope * scope, Expr * expr, I32 in_func, Context * ctx);
void infer_set_lit_expr(TypeScope * scope, Expr * expr, I32 in_func, Context * ctx);
void infer_type_def_expr(TypeScope * scope, Expr * expr, Context * ctx);
void infer_func_sig_expr(TypeScope * scope, Expr * expr);
void check_ref_function_returns(TypeScope * func_scope, Expr * expr);
void infer_func_def_expr(TypeScope * scope, Expr * expr, Context * ctx);
void infer_return_stmt(TypeScope * scope, Expr * stmt, I32 in_func, I32 returns_ref, Context * ctx);
void infer_if_stmt(TypeScope * scope, Expr * stmt, I32 in_func, I32 in_loop, I32 returns_ref, Context * ctx);
void infer_field_access_expr(TypeScope * scope, Expr * expr, I32 in_func, Context * ctx);
void infer_field_assign_stmt(TypeScope * scope, Expr * stmt, I32 in_func, Context * ctx);
void infer_while_stmt(TypeScope * scope, Expr * stmt, I32 in_func, I32 returns_ref, Context * ctx);
Bool infer_decl_type_def(TypeScope * scope, Expr * stmt);
Bool infer_decl_func_def(TypeScope * scope, Expr * stmt);
Bool infer_decl_type_alias_passthrough(TypeScope * scope, Expr * stmt);
void infer_decl_typed_value(TypeScope * scope, Expr * stmt);
void infer_decl_untyped_value(Expr * stmt);
void finalize_decl_binding(TypeScope * scope, Expr * stmt, I32 in_type_body);
void infer_decl_stmt(TypeScope * scope, Expr * stmt, I32 in_func, I32 in_type_body, Context * ctx);
void mark_switch_case_covered_variant(Expr * switch_enum_def, Vec * covered_variants, I32 n_variants, Expr * sw_expr, Expr * match_expr);
Expr * make_switch_case_condition(TypeScope * scope, Expr * case_body, Expr * match_expr, Str * sw_name, U32 sw_line, U32 sw_col, Str * sw_path);
void replace_switch_stmt_with_block(Expr * body, U32 stmt_idx, Expr * block);
void append_switch_else_if(Expr * root_if, Expr * if_node);
void attach_switch_default_body(Expr * root_if, Expr * default_body);
void infer_switch_stmt(TypeScope * scope, Expr * body, U32 stmt_idx, I32 in_func, Context * ctx);
void replace_body_stmt_with_block(Expr * body, U32 stmt_idx, Expr * block);
Expr * make_field_access_call0(Expr * base, Str * field, U32 line, U32 col, Str * path);
Expr * make_field_access_call1(Expr * base, Str * field, Expr * arg, U32 line, U32 col, Str * path);
Expr * make_for_in_range_while_body(Str * var_name, Str * cur_name, Str * step, Expr * for_body, U32 line, U32 col, Str * path, Str * elem_type);
Bool desugar_for_in_range_stmt(TypeScope * scope, Expr * body, U32 stmt_idx, I32 in_func, Context * ctx);
Bool desugar_for_in_collection_stmt(TypeScope * scope, Expr * body, U32 stmt_idx, I32 in_func, Context * ctx);
void infer_body_stmt(TypeScope * scope, Expr * body, U32 * i, I32 in_func, I32 in_loop, I32 returns_ref, I32 in_type_body, Context * ctx);
void infer_body(TypeScope * scope, Expr * body, I32 in_func, I32 owns_scope, I32 in_loop, I32 returns_ref, I32 in_type_body, Context * ctx);
void infer_assign_stmt(TypeScope * scope, Expr * stmt, I32 in_func, Context * ctx);
Bool is_numeric_type(TilType * t);
Bool is_integral_numeric_type(TilType * t);
Bool type_ctor_consumes(TilType * t);
Bool is_usize_name(Str * name);
Bool can_implicit_usize_coerce(TilType * from, TilType * to, Str * to_name);
Bool literal_in_range(Str * val_str, TilType * target);
Bool can_implicit_widen(TilType * from, TilType * to);
TilType * type_from_name(Str * name, TypeScope * scope);
Str * resolve_type_alias(TypeScope * scope, Str * name);
Str * usize_name(TypeScope * scope);
TilType * usize_type(TypeScope * scope);
Bool type_has_cmp(TypeScope * scope, Str * type_name);
Bool expr_contains_fcall(Expr * e);
Bool expr_uses_var(Expr * e, Str * name);
Bool expr_contains_decl(Expr * e, Str * name);
Bool expr_used_in_nested_func(Expr * e, Str * name);
Expr * find_variadic_fcall(Expr * e);
Expr * find_kwargs_fcall(Expr * e);
Str * type_prefix(TilType * t, Str * sname);
Str * type_to_name(TilType * t, Str * struct_name);
Expr * make_field_delete(Expr * field_assign, Bool is_own);
Expr * make_delete_call(Str * var_name, TilType type, Str * struct_name, Bool arg_is_own, Bool call_free, Expr * src);
Expr * make_clone_call(Str * type_name, TilType type, Expr * arg, Expr * src);
Expr * make_ns_call(Str * sname, Str * method, TilType ret_type, Str * ret_sname, Expr * src);
Expr * build_kwargs_dynmap_decl(Expr * fcall, Str * kw_name);
Expr * build_kwargs_dynmap_set(Expr * fcall, TypeScope * scope, Str * kw_name, Expr * named_arg);
Expr * build_variadic_array_decl(Expr * fcall, TypeScope * scope, Str * elem_type, Str * va_name, U32 vc);
Expr * build_variadic_array_set(Expr * fcall, TypeScope * scope, Str * va_name, I32 vi, U32 j);
void desugar_set_literal_decl(Expr * stmt, Vec * new_ch, TypeScope * scope);
void desugar_map_literal_decl(Expr * stmt, Vec * new_ch, TypeScope * scope);
void desugar_set_literals(Expr * body, TypeScope * scope);
void desugar_map_literals(Expr * body, TypeScope * scope);
void hoist_param_swap_assign(Expr * stmt, Vec * hoisted, TypeScope * scope);
void hoist_expr(Expr * expr, Vec * hoisted, TypeScope * scope);
void hoist_decl_rhs(Expr * stmt, Vec * hoisted, TypeScope * scope);
void hoist_if_cond(Expr * stmt, Vec * hoisted, TypeScope * scope);
void hoist_return_expr(Expr * stmt, Vec * hoisted, TypeScope * scope);
void hoist_assign_rhs(Expr * stmt, Vec * hoisted, TypeScope * scope);
void hoist_field_assign_rhs(Expr * stmt, Vec * hoisted, TypeScope * scope);
Expr * hoist_stmt_fcall(Expr * stmt, Vec * hoisted, TypeScope * scope);
void hoist_fcall_args(Expr * body, TypeScope * scope);
void insert_field_deletes(Expr * body);
void rewrite_variadic_fcall_args(Expr * fcall, Str * va_name);
void desugar_variadic_calls(Expr * body, TypeScope * scope);
Str * resolve_variadic_elem_type(Expr * fcall, TypeScope * scope);
Bool desugar_pure_splat_variadic_call(Expr * fcall, Vec * new_ch, Expr * stmt);
void desugar_kwargs_calls(Expr * body, TypeScope * scope);
void rewrite_kwargs_fcall_args(Expr * fcall, Str * kw_name);
Bool check_own_args(Expr * fdef, Expr * fcall, Str * var_name);
Bool fcall_has_own_arg(Expr * fcall, Str * var_name, TypeScope * scope);
Bool expr_transfers_own(Expr * e, Str * var_name, TypeScope * scope);
Bool expr_is_borrow_source(Expr * e, TypeScope * scope);
Bool expr_is_stable_field_base(Expr * e, TypeScope * scope);
Bool expr_is_ref_decl_source(Expr * e, TypeScope * scope);
Bool field_assign_needs_delete(Expr * stmt);
Bool alias_used_in_expr(Expr * body, Str * name, Expr * expr);
void collect_scope_locals(Expr * body, TypeScope * scope, Bool is_program_scope, Vec * locals_vec);
void extend_ref_local_lifetimes(Expr * body, void * locals, U32 n_locals);
void check_use_after_own_transfer(Expr * body, void * locals, U32 n_locals);
void insert_exit_deletes(Expr * body, void * live, U32 n_live, Bool return_only);
void insert_nested_exit_deletes(Expr * stmt, void * locals, U32 n_locals, U32 stmt_idx);
void insert_exit_deletes_into_stmt(Expr * stmt, Expr * body, void * locals, U32 n_locals, U32 stmt_idx, Vec * new_ch);
void insert_post_stmt_deletes(Expr * stmt, void * locals, U32 n_locals, U32 stmt_idx, Vec * new_ch);
void insert_assign_delete(Expr * stmt, void * locals, U32 n_locals, Vec * new_ch);
void insert_free_calls(Expr * body, TypeScope * scope, I32 scope_exit);
void infer_literal_expr(Expr * expr);
void narrow_dynamic(Expr * expr, TilType * target, Str * target_struct_name);
I32 fcall_returns_ref(Expr * fcall, TypeScope * scope);
Expr * hoist_to_temp(Expr * val, Vec * hoisted, TypeScope * scope);
I32 type_check(Expr * program, TypeScope * scope, Context * ctx);
Bool precomp_has_macro(Str * name);
Bool precomp_has_func(Str * name);
Expr * value_to_expr(Value val, Expr * src);
Value expr_to_value(Expr * e);
Bool is_known(Expr * e, Value * out);
Expr * try_eval_call(Scope * scope, Expr * fcall, Bool require_known);
void track_literal(Scope * scope, Str * name, Expr * rhs);
Bool is_macro_call(Expr * e);
Bool is_func_call(Expr * e);
void process_body(Scope * scope, Expr * body);
void precomp(Expr * program);
Str * qualified_name(Str * type_name, Str * method_name);
void scavenge(Expr * program, Mode * m, Bool run_tests);
Bool StructInstance_eq(StructInstance * a, StructInstance * b);
Str * StructInstance_to_str(StructInstance * self);
StructInstance * StructInstance_clone(StructInstance * self);
void StructInstance_delete(StructInstance * self, Bool * call_free);
U32 * StructInstance_size(void);
Bool EnumInstance_eq(EnumInstance * a, EnumInstance * b);
Str * EnumInstance_to_str(EnumInstance * self);
EnumInstance * EnumInstance_clone(EnumInstance * self);
void EnumInstance_delete(EnumInstance * self, Bool * call_free);
U32 * EnumInstance_size(void);
Bool * Value_eq(Value * a, Value * b);
Str * Value_to_str(Value * self);
Value * Value_clone(Value * self);
Value * Value_None(void);
Value * Value_Int(I64 * val);
Value * Value_Byte(U8 * val);
Value * Value_Short(I16 * val);
Value * Value_Int32(I32 * val);
Value * Value_Uint32(U32 * val);
Value * Value_Uint64(U64 * val);
Value * Value_Float(F32 * val);
Value * Value_Boolean(Bool * val);
Value * Value_Func(void * val);
Value * Value_Struct(StructInstance * val);
Value * Value_Enum(EnumInstance * val);
Value * Value_Ptr(void * val);
Bool * Value_is(Value * self, Value * other);
void Value_delete(Value * self, Bool * call_free);
U32 * Value_size(void);
Cell * Cell_clone(Cell * self);
void Cell_delete(Cell * self, Bool * call_free);
U32 * Cell_size(void);
Binding * Binding_clone(Binding * self);
void Binding_delete(Binding * self, Bool * call_free);
U32 * Binding_size(void);
Scope * Scope_clone(Scope * self);
void Scope_delete(Scope * self, Bool * call_free);
U32 * Scope_size(void);
Value val_none(void);
Value val_i64(I64 v);
Value val_u8(I64 v);
Value val_i16(I64 v);
Value val_i32(I64 v);
Value val_u32(I64 v);
Value val_u64(U64 v);
Value val_f32(F32 v);
Value val_bool(Bool v);
Value val_enum_flat(Str * enum_name, Expr * enum_def, I32 etag, void * payload_data, I32 payload_size);
Value val_enum_simple(Str * enum_name, I32 etag);
Value eval_expr(Scope * scope, Expr * e);
Value eval_call(Scope * scope, Expr * e);
Value clone_value(Value v);
void free_value(Value v);
Cell * scope_get(Scope * s, Str * name);
Scope * scope_new(Scope * parent);
void scope_set_owned(Scope * s, Str * name, Value val);
void scope_free(Scope * s);
void interpreter_init_ns(Scope * global, Expr * program);
Value * ns_get(Str * sname, Str * fname);
Value make_str_value(void * data, U64 len);
Value make_str_value_own(void * data, U64 len);
Str str_view(Value v);
Expr * find_field_decl(Expr * struct_def, Str * fname);
void write_field(StructInstance * inst, Expr * fdecl, Value val);
CollectionInfo * CollectionInfo_clone(CollectionInfo * self);
void CollectionInfo_delete(CollectionInfo * self, Bool * call_free);
U32 * CollectionInfo_size(void);
DynCallInfo * DynCallInfo_clone(DynCallInfo * self);
void DynCallInfo_delete(DynCallInfo * self, Bool * call_free);
U32 * DynCallInfo_size(void);
I32 build(Expr * program, Mode * m, Bool run_tests, Str * path, Str * c_output_path);
I32 build_header(Expr * program, Str * h_path);
I32 build_til_binding(Expr * program, Str * til_path, Str * lib_name);
I32 build_forward_header(Expr * program, Str * fwd_path);
I32 compile_c(Str * c_path, Str * bin_path, Str * ext_c_path, Str * user_c_path, Str * link_flags);
I32 compile_lib(Str * c_path, Str * lib_name, Str * ext_c_path, Str * user_c_path, Str * link_flags);
ExtStr * ExtStr_clone(ExtStr * self);
void ExtStr_delete(ExtStr * self, Bool * call_free);
U32 * ExtStr_size(void);
FFIType * FFIType_clone(FFIType * self);
void FFIType_delete(FFIType * self, Bool * call_free);
U32 * FFIType_size(void);
FFIEntry * FFIEntry_clone(FFIEntry * self);
void FFIEntry_delete(FFIEntry * self, Bool * call_free);
U32 * FFIEntry_size(void);
ExprPtrBox * ExprPtrBox_clone(ExprPtrBox * self);
void ExprPtrBox_delete(ExprPtrBox * self, Bool * call_free);
U32 * ExprPtrBox_size(void);
FFIType * ffi_type_pointer_ref(void);
FFIType * ffi_type_sint64_ref(void);
FFIType * ffi_type_uint8_ref(void);
FFIType * ffi_type_sint16_ref(void);
FFIType * ffi_type_sint32_ref(void);
FFIType * ffi_type_uint32_ref(void);
FFIType * ffi_type_uint64_ref(void);
FFIType * ffi_type_float_ref(void);
void ffi_init_struct_defs(Expr * program);
I64 * value_to_i64(Value * v);
U64 * value_to_u64(Value * v);
F32 * value_to_f32(Value * v);
Value * eval_arg(Scope * s, Expr * e);
Bool h_Bool_and(Scope * s, Expr * e, Value * r);
Bool h_Bool_or(Scope * s, Expr * e, Value * r);
Bool h_Bool_not(Scope * s, Expr * e, Value * r);
Bool h_U8_from_i64(Scope * s, Expr * e, Value * r);
Bool h_I16_from_i64(Scope * s, Expr * e, Value * r);
Bool h_I32_from_i64(Scope * s, Expr * e, Value * r);
Bool h_F32_from_i64(Scope * s, Expr * e, Value * r);
Bool h_U32_from_i64(Scope * s, Expr * e, Value * r);
Bool h_print_single(Scope * s, Expr * e, Value * r);
Bool h_print_flush(Scope * s, Expr * e, Value * r);
Bool h_exit(Scope * s, Expr * e, Value * r);
Bool h_readfile(Scope * s, Expr * e, Value * r);
Bool h_writefile(Scope * s, Expr * e, Value * r);
Bool h_spawn_cmd(Scope * s, Expr * e, Value * r);
void * val_to_ptr(Value * v);
Bool h_dyn_has_method(Scope * s, Expr * e, Value * r);
Bool h_dyn_fn(Scope * s, Expr * e, Value * r);
Bool h_check_cmd_status(Scope * s, Expr * e, Value * r);
Bool h_sleep(Scope * s, Expr * e, Value * r);
Bool h_file_mtime(Scope * s, Expr * e, Value * r);
Bool h_clock_ms(Scope * s, Expr * e, Value * r);
Bool h_get_thread_count(Scope * s, Expr * e, Value * r);
Bool ext_function_dispatch(Str * name, Scope * scope, Expr * e, Value * result);
Bool enum_method_dispatch(Str * method, Scope * scope, Expr * enum_def, Str * enum_name, Expr * e, Value * result);
I32 ffi_init(Expr * program, Str * fwd_path, Str * user_c_path, Str * ext_c_path, Str * link_flags);
void ffi_cleanup(void);
Mode * Mode_clone(Mode * self);
void Mode_delete(Mode * self, Bool * call_free);
U32 * Mode_size(void);
Context * Context_clone(Context * self);
void Context_delete(Context * self, Bool * call_free);
U32 * Context_size(void);
Mode * context_mode(Context * ctx);
void context_register_path_mode(Context * ctx, Str * path, Mode * mode_);
void context_set_mode_from_path(Context * ctx, Str * path);
Mode * mode_resolve(Str * name);
Bool * TokenType_eq(TokenType *, TokenType *);
TokenType *TokenType_Eof();
TokenType *TokenType_LParen();
TokenType *TokenType_RParen();
TokenType *TokenType_LBrace();
TokenType *TokenType_RBrace();
TokenType *TokenType_LBracket();
TokenType *TokenType_RBracket();
TokenType *TokenType_Comma();
TokenType *TokenType_Colon();
TokenType *TokenType_Question();
TokenType *TokenType_Bang();
TokenType *TokenType_Minus();
TokenType *TokenType_Plus();
TokenType *TokenType_Star();
TokenType *TokenType_Slash();
TokenType *TokenType_Dot();
TokenType *TokenType_DotDot();
TokenType *TokenType_DotDotDot();
TokenType *TokenType_Eq();
TokenType *TokenType_EqEq();
TokenType *TokenType_Neq();
TokenType *TokenType_Lt();
TokenType *TokenType_LtEq();
TokenType *TokenType_Gt();
TokenType *TokenType_GtEq();
TokenType *TokenType_ColonEq();
TokenType *TokenType_Ident();
TokenType *TokenType_StringTok();
TokenType *TokenType_Number();
TokenType *TokenType_Char();
TokenType *TokenType_KwMode();
TokenType *TokenType_KwMut();
TokenType *TokenType_KwOwn();
TokenType *TokenType_KwRef();
TokenType *TokenType_KwShallow();
TokenType *TokenType_KwStruct();
TokenType *TokenType_KwEnum();
TokenType *TokenType_KwNamespace();
TokenType *TokenType_KwFunc();
TokenType *TokenType_KwProc();
TokenType *TokenType_KwTest();
TokenType *TokenType_KwMacro();
TokenType *TokenType_KwExtFunc();
TokenType *TokenType_KwExtProc();
TokenType *TokenType_KwReturns();
TokenType *TokenType_KwThrows();
TokenType *TokenType_KwIf();
TokenType *TokenType_KwElse();
TokenType *TokenType_KwWhile();
TokenType *TokenType_KwFor();
TokenType *TokenType_KwIn();
TokenType *TokenType_KwSwitch();
TokenType *TokenType_KwMatch();
TokenType *TokenType_KwCase();
TokenType *TokenType_KwDefault();
TokenType *TokenType_KwReturn();
TokenType *TokenType_KwThrow();
TokenType *TokenType_KwCatch();
TokenType *TokenType_KwBreak();
TokenType *TokenType_KwContinue();
TokenType *TokenType_KwDefer();
TokenType *TokenType_KwTrue();
TokenType *TokenType_KwFalse();
TokenType *TokenType_KwNull();
TokenType *TokenType_Error();
Bool * ScopeFind_eq(ScopeFind *, ScopeFind *);
ScopeFind *ScopeFind_NotFound();
ScopeFind *ScopeFind_Found(TypeBinding *);
Bool * CtorArg_eq(CtorArg *, CtorArg *);
CtorArg *CtorArg_Unfilled();
CtorArg *CtorArg_Filled(Expr *);
Bool * Value_eq(Value *, Value *);
Value *Value_None();
Value *Value_Int(I64 *);
Value *Value_Byte(U8 *);
Value *Value_Short(I16 *);
Value *Value_Int32(I32 *);
Value *Value_Uint32(U32 *);
Value *Value_Uint64(U64 *);
Value *Value_Float(F32 *);
Value *Value_Boolean(Bool *);
Value *Value_Func(void *);
Value *Value_Struct(StructInstance *);
Value *Value_Enum(EnumInstance *);
Value *Value_Ptr(void *);

extern U32 CAP_LIT;
extern U32 CAP_VIEW;
extern I32 hoist_counter;
extern I32 _va_counter;
extern I32 _kw_counter;
extern I32 errors;
extern Str I64Name;
extern Str U8Name;
extern Str I16Name;
extern Str I32Name;
extern Str U32Name;
extern Str U64Name;
extern Str F32Name;
extern Str BoolName;
extern Set macros;
extern Set funcs;
extern Map known;
extern Vec gc_strs;
extern Map dispatch_map;
extern Bool dispatch_inited;
extern Map ffi_map;
extern Map ffi_struct_defs;
extern Bool ffi_loaded;
extern Vec ffi_type_cache;
extern Bool ffi_type_cache_inited;
extern I16 FFI_TYPE_STRUCT;
extern Map core_modes;

#include "ext.h"

