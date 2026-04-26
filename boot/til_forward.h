#pragma once
#include "ext.h"

typedef struct Array Array;
typedef struct Map Map;
typedef struct Set Set;
typedef struct Str Str;
typedef struct Vec Vec;
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
    TilType_TAG_Dynamic,
    TilType_TAG_Custom
} TilType_tag;
typedef struct TilType TilType;
typedef enum {
    FuncType_TAG_None,
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
typedef struct Declaration Declaration;
typedef struct FunctionDef FunctionDef;
typedef struct FCallData FCallData;
typedef struct StructDef StructDef;
typedef struct EnumDef EnumDef;
typedef struct AssignData AssignData;
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
    NodeType_TAG_Case,
    NodeType_TAG_NoDefaultArg
} NodeType_tag;
typedef struct NodeType NodeType;
typedef struct Expr Expr;
typedef struct Dynamic Dynamic;
typedef struct File File;
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
    TokenType_TAG_Percent,
    TokenType_TAG_Ampersand,
    TokenType_TAG_Pipe,
    TokenType_TAG_Caret,
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
    TokenType_TAG_PlusPlus,
    TokenType_TAG_MinusMinus,
    TokenType_TAG_ColonEq,
    TokenType_TAG_Ident,
    TokenType_TAG_StringTok,
    TokenType_TAG_Number,
    TokenType_TAG_Char,
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
    TokenType_TAG_KwExtStruct,
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
typedef struct Context Context;
typedef struct Mode Mode;
typedef struct LocalInfo LocalInfo;
typedef enum {
    CtorArg_TAG_Unfilled,
    CtorArg_TAG_Filled
} CtorArg_tag;
typedef struct CtorArg CtorArg;
typedef struct LoadedProgram LoadedProgram;
typedef enum {
    Lang_TAG_C,
    Lang_TAG_HolyC,
    Lang_TAG_TIL
} Lang_tag;
typedef struct Lang Lang;
typedef enum {
    Target_TAG_LinuxX64,
    Target_TAG_LinuxArm64,
    Target_TAG_LinuxRiscv64,
    Target_TAG_WindowsX64,
    Target_TAG_MacosX64,
    Target_TAG_MacosArm64,
    Target_TAG_Wasm32,
    Target_TAG_TempleosX86
} Target_tag;
typedef struct Target Target;
typedef struct CollectionInfo CollectionInfo;
typedef struct DynCallInfo DynCallInfo;
typedef struct BuildPaths BuildPaths;
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
typedef struct ExtStr ExtStr;
typedef struct _ffi_type ffi_type;
typedef struct FFIEntry FFIEntry;
typedef struct ExprPtrBox ExprPtrBox;
typedef struct FFITypePtrBox FFITypePtrBox;
typedef struct CliArgs CliArgs;

typedef void * (*CloneFn)(void *);
typedef void (*DeleteFn)(void *, Bool *);
typedef I64 * (*CmpFn)(void *, void *);
typedef Bool (*DispatchFn)(Scope *, Expr *, Value *);

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


struct TilType {
    TilType_tag tag;
    union {
        Str Struct;
        Str Enum;
        Str Custom;
    } data;
};

struct FuncType {
    FuncType_tag tag;
};

struct OwnType {
    OwnType_tag tag;
};

typedef struct Declaration {
    Str name;
    Str explicit_type;
    Bool is_mut;
    Bool is_namespace;
    OwnType own_type;
    TilType til_type;
    I32 field_offset;
    I32 field_size;
    Expr *field_struct_def;
    Expr *default_value;
} Declaration;


typedef struct FunctionDef {
    FuncType func_type;
    Vec params;
    Str return_type;
    I32 variadic_index;
    I32 kwargs_index;
    OwnType return_own_type;
} FunctionDef;


typedef struct FCallData {
    I32 variadic_index;
    U32 variadic_count;
    I32 kwargs_index;
    U32 kwargs_count;
    Bool is_splat;
    U64 own_args;
    Expr *fn_sig;
} FCallData;


typedef struct StructDef {
    I32 total_struct_size;
    Vec fields;
    Vec ns_decls;
    Str c_tag;
} StructDef;


typedef struct AssignData {
    Str name;
    Bool save_old_delete;
} AssignData;










typedef struct Dynamic {
    char _;
} Dynamic;


typedef struct File {
    U8 *handle;
    Bool is_write;
} File;


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


typedef struct EnumDef {
    Vec ns_decls;
    Vec variants;
    Map payload_types;
} EnumDef;


struct NodeType {
    NodeType_tag tag;
    union {
        Str LiteralStr;
        Str LiteralNum;
        Bool LiteralBool;
        Str Ident;
        Declaration Decl;
        AssignData Assign;
        FCallData FCall;
        FunctionDef FuncDef;
        StructDef StructDef;
        EnumDef EnumDef;
        Str FieldAccess;
        Str FieldAssign;
        Str ForIn;
        Str NamedArg;
    } data;
};

typedef struct Expr {
    NodeType data;
    TilType til_type;
    Vec children;
    U32 line;
    U32 col;
    Str path;
} Expr;


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
    Str name;
    TilType type;
    FuncType func_type;
    Bool is_mut;
    U32 line;
    U32 col;
    Bool is_param;
    OwnType own_type;
    Bool is_alias;
    Bool is_type_alias;
    Str *alias_target;
    Expr *struct_def;
    Expr *func_def;
    Bool is_builtin;
    Bool used;
} TypeBinding;


struct ScopeFind {
    ScopeFind_tag tag;
    union {
        TypeBinding Found;
    } data;
};

typedef struct TypeScope {
    Map bindings;
    TypeScope *parent;
} TypeScope;


typedef struct Mode {
    Bool needs_main;
    Bool decls_only;
    Str auto_import;
    Bool is_library;
    Bool is_pure;
    Bool run_tests;
    Bool debug_prints;
} Mode;


typedef struct LocalInfo {
    Str *name;
    TilType type;
    I32 decl_index;
    I32 last_use;
    I32 own_transfer;
    Bool skip_scope_delete;
    Bool is_heap;
} LocalInfo;


struct CtorArg {
    CtorArg_tag tag;
    union {
        Expr Filled;
    } data;
};

struct Lang {
    Lang_tag tag;
};

struct Target {
    Target_tag tag;
};

typedef struct CollectionInfo {
    Str *type_name;
    I32 is_vec;
} CollectionInfo;


typedef struct DynCallInfo {
    Str *method;
    I32 nargs;
    Bool has_return;
} DynCallInfo;


typedef struct BuildPaths {
    Str name;
    Str c_path;
    Str bin_path;
    Str fwd_path;
    Str h_path;
    Str til_path;
    Str py_path;
    Bool do_lib;
} BuildPaths;


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


typedef struct Scope {
    Map bindings;
    Scope *parent;
} Scope;


typedef struct ExtStr {
    U8 *data;
    U64 count;
    U64 cap;
} ExtStr;


typedef struct _ffi_type {
    U32 size;
    I16 alignment;
    I16 type;
    void * *elements;
} ffi_type;


typedef struct {
    I32 abi;
    U32 nargs;
    void * *arg_types;
    void * *rtype;
    U32 bytes;
    U32 flags;
} ffi_cif;


typedef struct FFIEntry {
    U8 *fn;
    Str *return_type;
    I32 nparam;
    U8 *param_shallows;
    Bool return_is_shallow;
    ffi_cif *cif;
    void * *arg_types;
} FFIEntry;


typedef struct ExprPtrBox {
    Expr *ptr;
} ExprPtrBox;


typedef struct FFITypePtrBox {
    ffi_type *ptr;
} FFITypePtrBox;


typedef struct CliArgs {
    Str command;
    Str path;
    Str custom_bin;
    Str custom_c;
    Str target_str;
    Str cc;
    U32 path_idx;
    Bool early_return;
} CliArgs;


typedef struct Context {
    Mode mode;
    Map path_modes;
    TypeScope scope;
    Bool is_repl;
} Context;


typedef struct LoadedProgram {
    Expr *core_ast;
    Expr *ast;
    Mode cur_mode;
    Context ctx;
    Bool skip_core;
    Str mode_str;
    Str path;
    Str ext_c_path;
    Str link_flags;
    Str include_flags;
    Str link_c_paths;
    Bool run_tests;
} LoadedProgram;


Array * Array_new(Str * elem_type, U32 * elem_size, U32 * cap);
U32 * Array_len(Array * self);
void * Array_get(Array * self, U32 * i);
void Array_set(Array * self, U32 * i, void * val);
void Array_delete(Array * self, Bool * call_free);
Array * Array_clone(Array * self);
U32 Array_size(void);
Map * Map_new(Str * key_type, U32 * key_size, Str * val_type, U32 * val_size);
U32 * Map_len(Map * self);
Bool Map_has(Map * self, void * key);
void * Map_get(Map * self, void * key);
void Map_set(Map * self, void * key, void * val);
void Map_delete(Map * self, Bool * call_free);
Map * Map_clone(Map * self);
U32 Map_size(void);
Set * Set_new(Str * elem_type, U32 * elem_size);
U32 * Set_len(Set * self);
Bool Set_has(Set * self, void * val);
void Set_add(Set * self, void * val);
void Set_delete(Set * self, Bool * call_free);
Set * Set_clone(Set * self);
U32 Set_size(void);
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
U32 Str_size(void);
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
void Vec_move_from(Vec * self, Vec * other);
void * Vec_get(Vec * self, U32 * i);
void * Vec_pop(Vec * self);
Vec * Vec_take_prefix(Vec * self, U32 * n);
void Vec_set(Vec * self, U32 * i, void * val);
void Vec_delete(Vec * self, Bool * call_free);
Vec * Vec_clone(Vec * self);
U32 Vec_size(void);
Bool TilType_is(TilType * self, TilType * other);
Bool TilType_eq(TilType * self, TilType * other);
void TilType_delete(TilType * self, Bool * call_free);
Str * TilType_to_str(TilType * self);
TilType * TilType_clone(TilType * self);
U32 TilType_size(void);
Str * til_type_name_c(TilType * t);
Str * til_type_name(TilType * t);
Bool FuncType_is(FuncType * self, FuncType * other);
Bool FuncType_eq(FuncType * self, FuncType * other);
void FuncType_delete(FuncType * self, Bool * call_free);
Str * FuncType_to_str(FuncType * self);
FuncType * FuncType_clone(FuncType * self);
U32 FuncType_size(void);
Bool OwnType_is(OwnType * self, OwnType * other);
Bool OwnType_eq(OwnType * self, OwnType * other);
void OwnType_delete(OwnType * self, Bool * call_free);
Str * OwnType_to_str(OwnType * self);
OwnType * OwnType_clone(OwnType * self);
U32 OwnType_size(void);
Bool * Declaration_eq(Declaration * a, Declaration * b);
Str * Declaration_to_str(Declaration * self);
Declaration * Declaration_clone(Declaration * self);
void Declaration_delete(Declaration * self, Bool * call_free);
U32 Declaration_size(void);
Bool * FunctionDef_eq(FunctionDef * a, FunctionDef * b);
Str * FunctionDef_to_str(FunctionDef * self);
FunctionDef * FunctionDef_clone(FunctionDef * self);
void FunctionDef_delete(FunctionDef * self, Bool * call_free);
U32 FunctionDef_size(void);
Bool * FCallData_eq(FCallData * a, FCallData * b);
Str * FCallData_to_str(FCallData * _self);
FCallData * FCallData_clone(FCallData * self);
void FCallData_delete(FCallData * self, Bool * call_free);
U32 FCallData_size(void);
void set_own_arg(Expr * fcall, U32 arg_index);
Bool get_own_arg(Expr * fcall, U32 arg_index);
Bool * StructDef_eq(StructDef * a, StructDef * b);
Str * StructDef_to_str(StructDef * _self);
StructDef * StructDef_clone(StructDef * self);
void StructDef_delete(StructDef * self, Bool * call_free);
U32 StructDef_size(void);
Bool * EnumDef_eq(EnumDef * a, EnumDef * b);
Str * EnumDef_to_str(EnumDef * _self);
EnumDef * EnumDef_clone(EnumDef * self);
void EnumDef_delete(EnumDef * self, Bool * call_free);
U32 EnumDef_size(void);
Bool * AssignData_eq(AssignData * a, AssignData * b);
Str * AssignData_to_str(AssignData * self);
AssignData * AssignData_clone(AssignData * self);
void AssignData_delete(AssignData * self, Bool * call_free);
U32 AssignData_size(void);
Bool NodeType_is(NodeType * self, NodeType * other);
Bool NodeType_eq(NodeType * self, NodeType * other);
void NodeType_delete(NodeType * self, Bool * call_free);
Str * NodeType_to_str(NodeType * self);
NodeType * NodeType_clone(NodeType * self);
U32 NodeType_size(void);
void Expr_error(Expr * self, Str * msg);
void Expr_todo_error(Expr * self, Str * msg);
void Expr_lang_error(Expr * self, Str * msg);
void Expr_add_child(Expr * self, Expr * child);
void Expr_push_child_clone(Expr * self, Expr * child);
void Expr_take_children(Expr * self, Expr * other);
Expr * Expr_child(Expr * parent, U32 * i);
Expr * Expr_new(NodeType * data, U32 line, U32 col, Str * path);
Bool Expr_eq(Expr * _self, Expr * _other);
Str * Expr_to_str(Expr * self);
Expr * Expr_clone(Expr * self);
void Expr_delete(Expr * self, Bool * call_free);
U32 Expr_size(void);
Str * func_type_pascal(FuncType * ft);
Str * node_head_str(NodeType * data);
Str * expr_to_str_indent(Expr * self, U32 indent);
Str * func_type_name(FuncType * ft);
Bool is_decl_with_child(Expr * stmt);
Bool is_struct_or_enum(Expr * stmt);
Bool is_func_decl(Expr * stmt);
Bool is_def(Expr * stmt);
Expr * decl_body(Expr * stmt);
Bool is_namespace_method(Expr * field);
Vec * def_ns_decls(Expr * sdef);
Bool enum_has_payloads(Expr * enum_def);
I32 * enum_variant_tag(Expr * enum_def, Str * variant_name);
Str * enum_variant_type(Expr * enum_def, I32 tag);
Str * U8_to_str(U8 * val);
void U8_inc(U8 * self);
void U8_dec(U8 * self);
U8 * U8_unity(U8 * _self);
U64 U8_distance(void * a, void * b);
void U8_delete(U8 * self, Bool * call_free);
U32 * U8_size(void);
Bool U8_lt(U8 * a, U8 * b);
Bool U8_gt(U8 * a, U8 * b);
Bool U8_neq(U8 * a, U8 * b);
Bool U8_lte(U8 * a, U8 * b);
Bool U8_gte(U8 * a, U8 * b);
Str * I16_to_str(I16 * val);
void I16_inc(I16 * self);
void I16_dec(I16 * self);
I16 * I16_unity(I16 * _self);
I16 * I16_neg(I16 * a);
I16 * I16_abs(I16 * a);
U64 I16_distance(void * a, void * b);
void I16_delete(I16 * self, Bool * call_free);
U32 * I16_size(void);
Bool I16_lt(I16 * a, I16 * b);
Bool I16_gt(I16 * a, I16 * b);
Bool I16_neq(I16 * a, I16 * b);
Bool I16_lte(I16 * a, I16 * b);
Bool I16_gte(I16 * a, I16 * b);
Str * I32_to_str(I32 * val);
void I32_inc(I32 * self);
void I32_dec(I32 * self);
I32 * I32_unity(I32 * _self);
I32 * I32_neg(I32 * a);
I32 * I32_abs(I32 * a);
U64 I32_distance(void * a, void * b);
void I32_delete(I32 * self, Bool * call_free);
U32 * I32_size(void);
Bool I32_lt(I32 * a, I32 * b);
Bool I32_gt(I32 * a, I32 * b);
Bool I32_neq(I32 * a, I32 * b);
Bool I32_lte(I32 * a, I32 * b);
Bool I32_gte(I32 * a, I32 * b);
F32 * F32_from_i64(I64 * val);
void F32_delete(F32 * self, Bool * call_free);
U32 * F32_size(void);
Bool F32_lt(F32 * a, F32 * b);
Bool F32_gt(F32 * a, F32 * b);
Bool F32_neq(F32 * a, F32 * b);
Bool F32_lte(F32 * a, F32 * b);
Bool F32_gte(F32 * a, F32 * b);
Str * U32_to_str(U32 * val);
void U32_inc(U32 * self);
void U32_dec(U32 * self);
U32 * U32_unity(U32 * _self);
U64 U32_distance(void * a, void * b);
void U32_delete(U32 * self, Bool * call_free);
U32 * U32_size(void);
Bool U32_lt(U32 * a, U32 * b);
Bool U32_gt(U32 * a, U32 * b);
Bool U32_neq(U32 * a, U32 * b);
Bool U32_lte(U32 * a, U32 * b);
Bool U32_gte(U32 * a, U32 * b);
Str * U64_to_str(U64 val);
U64 * U64_from_i64(I64 * val);
void U64_inc(U64 * self);
void U64_dec(U64 * self);
U64 * U64_unity(U64 * _self);
U64 U64_distance(void * a, void * b);
void U64_delete(U64 * self, Bool * call_free);
U32 * U64_size(void);
Bool U64_lt(U64 * a, U64 * b);
Bool U64_gt(U64 * a, U64 * b);
Bool U64_neq(U64 * a, U64 * b);
Bool U64_lte(U64 * a, U64 * b);
Bool U64_gte(U64 * a, U64 * b);
Str * I64_to_str(I64 * val);
U32 I64_to_usize(I64 val);
void I64_inc(I64 * self);
void I64_dec(I64 * self);
I64 * I64_unity(I64 * _self);
I64 * I64_neg(I64 * a);
I64 * I64_abs(I64 * a);
U64 I64_distance(void * a, void * b);
void I64_delete(I64 * self, Bool * call_free);
U32 * I64_size(void);
Bool I64_lt(I64 * a, I64 * b);
Bool I64_gt(I64 * a, I64 * b);
Bool I64_neq(I64 * a, I64 * b);
Bool I64_lte(I64 * a, I64 * b);
Bool I64_gte(I64 * a, I64 * b);
Str * Bool_to_str(Bool * b);
I64 * Bool_cmp(Bool * a, Bool * b);
void Bool_delete(Bool * self, Bool * call_free);
U32 * Bool_size(void);
Bool Bool_lt(Bool * a, Bool * b);
Bool Bool_gt(Bool * a, Bool * b);
Bool Bool_neq(Bool * a, Bool * b);
Bool Bool_lte(Bool * a, Bool * b);
Bool Bool_gte(Bool * a, Bool * b);
U32 * Dynamic_size(void);
void * default_clone(void * v);
void default_delete(void * _v, Bool * _cf);
I64 * default_cmp(void * _a, void * _b);
void println(Array * parts);
File * File_new(Str * path, Bool is_write);
void File_write_str(File * self, Str * s);
Str * File_read_all(File * self);
void File_close(File * self);
File * File_clone(File * self);
void File_delete(File * self, Bool * call_free);
U32 File_size(void);
void swap(void * a, void * b, U64 size);
I64 * wait_cmd(I64 * pid);
I64 * run_cmd(Str * output, Array * args);
void panic(Str * loc_str, Array * parts);
void TODO(Str * loc_str, Array * parts);
Bool TokenType_is(TokenType * self, TokenType * other);
Bool TokenType_eq(TokenType * self, TokenType * other);
void TokenType_delete(TokenType * self, Bool * call_free);
Str * TokenType_to_str(TokenType * self);
TokenType * TokenType_clone(TokenType * self);
U32 TokenType_size(void);
Token * Token_clone(Token * self);
void Token_delete(Token * self, Bool * call_free);
U32 Token_size(void);
Bool * is_digit(U8 * c);
Bool * is_alpha(U8 * c);
Bool * is_alnum(U8 * c);
Str * tok_name(TokenType * type);
TokenType lookup_single_char(U8 * c);
TokenType lookup_two_char(U8 * c, U8 * c2);
TokenType * lookup_keyword(Str * word);
Vec * tokenize(Str * src, Str * path);
Parser * Parser_clone(Parser * self);
void Parser_delete(Parser * self, Bool * call_free);
U32 Parser_size(void);
Token * peek(Parser * p);
Token * advance(Parser * p);
Bool check(Parser * p, TokenType * type);
Token * expect_token(Parser * p, TokenType * type);
Str * expect_text(Parser * p, TokenType * type);
U32 peek_line(Parser * p);
U32 peek_col(Parser * p);
TilType * til_type_from_explicit_type(Str * name);
Str * parse_fn_signature(Parser * p, U32 line, U32 col);
Expr * parse_block(Parser * p);
Expr * parse_func_def(Parser * p);
Expr * parse_struct_def(Parser * p, Str * c_tag);
Expr * parse_enum_def(Parser * p);
Expr * parse_call(Parser * p, Str * name, U32 call_line, U32 call_col);
Expr * make_binop_call(Expr * lhs, Str * method, U32 op_line, U32 op_col, Str * path, Expr * rhs);
Expr * parse_primary(Parser * p);
Expr * parse_multiplicative(Parser * p);
Expr * parse_additive(Parser * p);
Expr * parse_comparison(Parser * p);
Expr * parse_bitand(Parser * p);
Expr * parse_bitxor(Parser * p);
Expr * parse_bitor(Parser * p);
Expr * parse_expression(Parser * p);
Expr * parse_statement_ident(Parser * p, Bool is_mut, OwnType own_type);
Expr * parse_statement(Parser * p);
Expr * parse(Vec * tokens, Str * path, Str * mode_out);
Bool TypeBinding_eq(TypeBinding * a, TypeBinding * b);
Str * TypeBinding_to_str(TypeBinding * self);
TypeBinding * TypeBinding_clone(TypeBinding * self);
void TypeBinding_delete(TypeBinding * self, Bool * call_free);
U32 TypeBinding_size(void);
ScopeFind * ScopeFind_NotFound(void);
ScopeFind * ScopeFind_Found(TypeBinding * val);
Bool ScopeFind_is(ScopeFind * self, ScopeFind * other);
Bool ScopeFind_eq(ScopeFind * self, ScopeFind * other);
void ScopeFind_delete(ScopeFind * self, Bool * call_free);
Str * ScopeFind_to_str(ScopeFind * self);
ScopeFind * ScopeFind_clone(ScopeFind * self);
U32 ScopeFind_size(void);
TypeBinding * TypeScope_get_binding(TypeScope * self, Str * name);
ScopeFind * TypeScope_find(TypeScope * self, Str * name);
TilType * TypeScope_get_type(TypeScope * self, Str * name);
FuncType TypeScope_get_func_type(TypeScope * self, Str * name);
Expr * TypeScope_get_struct(TypeScope * self, Str * name);
Bool TypeScope_is_mut(TypeScope * self, Str * name);
void TypeScope_set(TypeScope * self, Str * name, TilType * type, FuncType func_type, Bool is_mut, U32 line, U32 col, Bool is_param, OwnType own_type);
TypeScope * TypeScope_clone(TypeScope * self);
void TypeScope_delete(TypeScope * self, Bool * call_free);
U32 TypeScope_size(void);
Context * Context_clone(Context * self);
void Context_delete(Context * self, Bool * call_free);
U32 Context_size(void);
I32 align_up(I32 offset, I32 align);
TilType * type_from_name_init(Str * name, TypeScope * scope);
I32 register_struct_definitions(Expr * program, TypeScope * scope);
void generate_missing_struct_clones(Expr * program, TypeScope * scope);
I32 register_enum_definition(Expr * stmt, TypeScope * scope);
void collect_enum_variants(Expr * enum_def, Vec * variant_names, Vec * variant_types, Bool * has_payloads);
void generate_enum_variant_constructors(Expr * enum_def, Str * ename, U32 line, U32 col, Str * path, Vec * variant_names, Vec * variant_types, Bool has_payloads);
void generate_enum_is_method(Expr * enum_def, Str * ename, U32 line, U32 col, Str * path);
void generate_enum_eq_method(Expr * enum_def, Str * ename, U32 line, U32 col, Str * path, Vec * variant_names, Vec * variant_types, TypeScope * scope);
void generate_enum_delete_method(Expr * enum_def, Str * ename, U32 line, U32 col, Str * path, Vec * variant_names, Vec * variant_types, Bool has_payloads, TypeScope * scope);
void generate_enum_to_str_method(Expr * enum_def, Str * ename, U32 line, U32 col, Str * path, Vec * variant_names, Vec * variant_types, Bool has_payloads, TypeScope * scope);
void generate_enum_clone_method(Expr * enum_def, Str * ename, I32 line, I32 col, Str * path, Vec * variant_names, Vec * variant_types, Bool has_payloads);
I32 register_enums_and_generate_nonclone_methods(Expr * program, TypeScope * scope);
void generate_missing_enum_clones(Expr * program);
void generate_missing_struct_deletes(Expr * program, TypeScope * scope);
void register_funcsig_aliases(Expr * program, TypeScope * scope);
void register_type_aliases(Expr * program, TypeScope * scope);
void register_top_level_values(Expr * program, TypeScope * scope);
void register_function_definitions(Expr * program, TypeScope * scope);
void generate_struct_size_methods(Expr * program);
void generate_enum_size_methods(Expr * program);
void generate_unity_derived_methods(Expr * program);
void generate_size_methods(Expr * program);
void generate_cmp_derived_methods(Expr * program);
void generate_derived_methods(Expr * program);
void compute_struct_layout(Expr * struct_def, TypeScope * scope);
void compute_all_struct_layouts(Expr * program, TypeScope * scope);
Bool infer_top_level_decl_type(Expr * stmt, TypeScope * scope, TilType * out_type);
I32 init_declarations(Expr * program, TypeScope * scope);
Mode * Mode_clone(Mode * self);
void Mode_delete(Mode * self, Bool * call_free);
U32 Mode_size(void);
void context_register_path_mode(Context * ctx, Str * path, Mode * mode);
void context_set_mode_from_path(Context * ctx, Str * path);
Mode * mode_resolve(Str * name);
Bool fa_is_ns(Expr * e, TypeScope * scope);
OwnType fa_own_type(Expr * e, TypeScope * scope);
LocalInfo * LocalInfo_clone(LocalInfo * self);
void LocalInfo_delete(LocalInfo * self, Bool * call_free);
U32 LocalInfo_size(void);
CtorArg * CtorArg_Unfilled(void);
CtorArg * CtorArg_Filled(Expr * val);
Bool CtorArg_is(CtorArg * self, CtorArg * other);
Bool CtorArg_eq(CtorArg * self, CtorArg * other);
void CtorArg_delete(CtorArg * self, Bool * call_free);
Str * CtorArg_to_str(CtorArg * self);
CtorArg * CtorArg_clone(CtorArg * self);
U32 CtorArg_size(void);
void type_error(Expr * e, Str * msg);
void type_error_at(Str * path, U32 line, U32 col, Str * msg);
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
void check_unused_params(TypeScope * func_scope, Expr * expr);
void check_unused_locals(TypeScope * scope, Str * path);
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
Bool is_compile_directive(Expr * e);
void infer_body_stmt(TypeScope * scope, Expr * body, U32 * i, I32 in_func, I32 in_loop, I32 returns_ref, I32 in_type_body, Context * ctx);
void reregister_scope_defs(Expr * body, TypeScope * scope);
void reregister_field_struct_defs(Expr * body, TypeScope * scope);
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
Str * type_prefix(TilType * t);
Str * type_to_name(TilType * t);
Expr * make_field_delete(Expr * field_assign, OwnType field_own_type);
Expr * make_delete_call(Str * var_name, TilType type, Bool arg_is_own, Bool call_free, Expr * src);
Expr * make_clone_call(Str * type_name, TilType type, Expr * arg, Expr * src);
Expr * make_ns_call(Str * sname, Str * method, TilType ret_type, Expr * src);
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
void hoist_stmt_fcall(Expr * stmt, Vec * hoisted, TypeScope * scope);
void hoist_fcall_args(Expr * body, TypeScope * scope);
void insert_field_deletes(Expr * body, TypeScope * scope);
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
Bool field_assign_needs_delete(Expr * stmt, TypeScope * scope);
Bool alias_used_in_expr(Expr * body, Str * name, Expr * expr);
void collect_scope_locals(Expr * body, TypeScope * scope, Bool is_program_scope, Vec * locals_vec);
void extend_ref_local_lifetimes(Expr * body, Vec * locals);
void check_use_after_own_transfer(Expr * body, Vec * locals);
void insert_exit_deletes(Expr * body, Vec * live, Bool return_only);
void insert_nested_exit_deletes(Expr * stmt, Vec * locals, U32 stmt_idx);
void insert_exit_deletes_into_stmt(Expr * stmt, Expr * body, Vec * locals, U32 stmt_idx, Vec * new_ch);
void insert_post_stmt_deletes(Expr * stmt, Vec * locals, U32 stmt_idx, Vec * new_ch);
void insert_assign_delete(Expr * stmt, Vec * locals, Vec * new_ch);
void promote_own_transferred_locals(Expr * body, Vec * locals);
void insert_free_calls(Expr * body, TypeScope * scope, I32 scope_exit);
void infer_literal_expr(Expr * expr);
void narrow_dynamic(Expr * expr, TilType * target);
I32 fcall_returns_ref(Expr * fcall, TypeScope * scope);
Expr * hoist_to_temp(Expr * val, Vec * hoisted, TypeScope * scope, Bool is_own);
I32 type_check(Expr * program, TypeScope * scope, Context * ctx);
Bool precomp_has_macro(Str * name);
Bool precomp_has_func(Str * name);
Expr * value_to_expr(Value val, Expr * src);
Value expr_to_value(Expr * e);
Bool is_known(Expr * e, Value * out);
Bool func_uses_unknown_globals(Expr * e, Expr * func_def, Scope * precomp_scope);
Expr * try_eval_call(Scope * scope, Expr * fcall, Bool require_known);
void track_literal(Scope * scope, Str * name, Expr * rhs);
Bool is_macro_call(Expr * e);
Bool is_func_call(Expr * e);
void process_body(Scope * scope, Expr * body);
void precomp_scan_names(Expr * prog);
void precomp_register_defs(Scope * global, Expr * prog);
void precomp(Expr * core_program, Expr * program);
Bool scav_fa_is_ns(Expr * e);
Str * qualified_name(Str * type_name, Str * method_name);
void gc_free_all(void);
void vec_push_str(Vec * v, Str * s);
void children_filter(Vec * v, void * marks, U32 n);
void push_qn(Vec * v, Str * type_name, Str * method);
void push_builtin_methods(Vec * v, Str * builtin_name, Str * m1, Str * m2, Str * m3);
void collect_refs(Expr * e, Vec * refs);
Expr * find_ns_decl_fdef(Expr * program, Map * top, Str * name);
void scavenge(Expr * core_program, Expr * program, Mode * mode, Bool run_tests);
Str * realpath_str(Str * path);
Str * str_left(Str * s, U32 * n);
Str * normalize_mode_name(Str * mode_name);
Str * display_path(Str * p, Str * cwd);
Mode * require_mode(Str * path, Str * mode_name);
Str * forward_header_path(Str * path);
Str * dir_of(Str * abs);
Vec * extract_imports(Expr * body);
I32 * resolve_imports(Vec * import_paths, Str * base_dir, Set * resolved_set, Vec * stack, Vec * merged, Str * lib_dir, Context * ctx, Str * default_mode, Str * cwd);
LoadedProgram * LoadedProgram_clone(LoadedProgram * self);
void LoadedProgram_delete(LoadedProgram * self, Bool * call_free);
U32 LoadedProgram_size(void);
void extract_link_info(LoadedProgram * lp);
LoadedProgram * load_program(Str * path, Str * bin_dir, Str * cwd, Str * ext_c_path);
void loaded_add_lflag(LoadedProgram * lp, Str * lib);
void prepare_program(LoadedProgram * lp, Bool run_tests);
void cmd_ast(LoadedProgram * lp);
Bool Lang_is(Lang * self, Lang * other);
Bool Lang_eq(Lang * self, Lang * other);
void Lang_delete(Lang * self, Bool * call_free);
Str * Lang_to_str(Lang * self);
Lang * Lang_clone(Lang * self);
U32 Lang_size(void);
Str * lang_to_str(Lang * lang);
Bool Target_is(Target * self, Target * other);
Bool Target_eq(Target * self, Target * other);
void Target_delete(Target * self, Bool * call_free);
Str * Target_to_str(Target * self);
Target * Target_clone(Target * self);
U32 Target_size(void);
Target * target_from_str(Str * s);
Str * target_to_str(Target * target);
Lang * default_lang_for_target(Target * target);
Bool * is_lang_supported_for_target(Lang * lang, Target * target);
void validate_lang_for_target(Lang * lang, Target * target);
Bool * is_clang(Str * cmd);
Str * toolchain_command(Target * target, Lang * lang);
Str * target_prefix_args(Target * target);
Str * common_warning_flags(void);
Str * clang_warning_flags(void);
Str * toolchain_extra_args(Target * target, Str * compiler);
Str * executable_extension(Target * target);
Target * detect_current_target(void);
I32 system_cmd(Str * cmd);
CollectionInfo * CollectionInfo_clone(CollectionInfo * self);
void CollectionInfo_delete(CollectionInfo * self, Bool * call_free);
U32 CollectionInfo_size(void);
DynCallInfo * DynCallInfo_clone(DynCallInfo * self);
void DynCallInfo_delete(DynCallInfo * self, Bool * call_free);
U32 DynCallInfo_size(void);
Bool is_dyn_call_name(Str * name, Bool * has_ret);
Expr * fcall_fn_sig(Expr * fcall);
Bool is_stack_local(Str * name);
Bool is_value_global(Str * name);
Bool is_ref_global(Str * name);
Bool is_ref_local(Str * name);
Bool use_dot_access(Expr * obj);
Bool is_primitive_type(Str * name);
Bool is_funcsig_type(Str * name);
Bool is_ext_h_type(Str * name);
Bool is_skip_ext_decl(Str * name);
Bool is_exported_top_level_global(Expr * stmt);
Expr * find_struct_body(Str * name);
Expr * find_struct_def(Str * name);
Expr * find_callee_fdef(Str * name);
Str * fa_struct_name(Expr * e);
Bool builder_fa_is_ptr(Expr * e);
Bool builder_fa_is_ns(Expr * e);
Bool is_shallow_param(Str * name);
Bool callee_returns_shallow(Str * callee_name);
Bool callee_returns_dynamic(Str * callee_name);
Bool callee_param_is_shallow(Str * callee_name, U32 arg_index);
Bool callee_param_is_usize(Str * callee_name, U32 arg_index);
Bool callee_param_is_own(Str * callee_name, U32 arg_index);
Bool fcall_is_shallow_return(Expr * fcall);
Bool fcall_returns_dynamic(Expr * fcall);
Str * til_type_to_c(TilType t);
Str * c_type_name(TilType t, Str * struct_name);
Str * func_to_c(Str * name);
Str * type_name_to_c(Str * name);
Str * type_name_to_c_value(Str * name);
void emit_u64(File * f, U64 v);
void emit_i32(File * f, I32 v);
void emit_indent(File * f, I32 depth);
void emit_til_default(File * f, TilType t);
Str * callee_return_ctype(Str * callee_name);
void emit_param_list(File * f, Expr * fdef, Bool with_names);
void collect_dyn_methods(Expr * e, Vec * methods);
void collect_collection_builtins(Expr * e, Vec * infos);
void emit_field(File * f, Str * var, Str * field);
Str * get_stack_local_ctype(Str * name);
Str * resolve_callee_name(Expr * fcall);
Str * resolve_callee_name(Expr * fcall);
Str * callee_return_ctype(Str * callee_name);
Str * fcall_return_ctype(Expr * fcall);
void check_fcall_mut_args(Expr * e);
void collect_unsafe_to_hoist(Expr * body);
void collect_dyn_has_methods(Expr * e, Vec * methods);
void emit_stmt_decl(File * f, Expr * e, I32 depth);
Str * emit_return_ctype(Expr * rv);
void emit_return_box(File * f, Expr * rv, I32 depth);
void emit_stmt_return(File * f, Expr * e, I32 depth);
void emit_stmt(File * f, Expr * e, I32 depth);
void emit_fcall_funcptr_cast(File * f, Expr * e, Expr * sig);
void emit_fcall_funcptr_args(File * f, Expr * e, Expr * sig, I32 depth);
void emit_expr(File * f, Expr * e, I32 depth);
void emit_body(File * f, Expr * body, I32 depth);
void emit_ctor_fields(File * f, Str * var, Expr * ctor, I32 depth);
void emit_ns_inits(File * f, I32 depth);
void emit_body_scoped(File * f, Expr * body, I32 depth);
void emit_deref(File * f, Expr * e, I32 depth);
void emit_as_ptr(File * f, Expr * e, I32 depth, Bool is_own);
void emit_usize_ref(File * f, Expr * e, I32 depth);
void emit_cli_parse_arg(File * f, Str * pname, Str * ptype, I32 argi);
void emit_func_def(File * f, Str * name, Expr * func_def, Mode * mode, Bool is_static);
void emit_struct_typedef(File * f, Str * name, Expr * struct_def);
void emit_ns_method(File * f, Str * name, Str * dd_name, Expr * fdef);
void emit_struct_funcs(File * f, Str * name, Expr * struct_def);
void emit_enum_def(File * f, Str * name, Expr * enum_def);
void emit_enum_struct_body(File * f, Str * ename, Expr * enum_def);
void topo_emit_struct_enum_defs(File * f, Expr * prog, Set * emitted);
void emit_func_forward_decl(File * f, Str * name, Expr * fdef);
void emit_funcsig_typedef(File * f, Str * name, Expr * fdef);
void emit_funcsig_typedefs(File * f, Expr * core_program, Expr * program);
void emit_header_forward_decls(File * f, Expr * core_program, Expr * program);
void emit_header_defs_and_funcs(File * f, Expr * core_program, Expr * program);
void emit_header_global_decls(File * f, Expr * core_program, Expr * program);
I32 build_forward_header(Expr * core_program, Expr * program, Str * fwd_path);
I32 build_header(Expr * core_program, Expr * program, Str * h_path);
Bool emit_binding_ns_method(File * f, Str * fdd_name, FunctionDef * fd, Bool * has_ns);
void emit_binding_ns_methods(File * f, Expr * def);
I32 build_til_binding(Expr * program, Str * til_path, Str * lib_name);
Str * type_name_to_ctypes(Str * name);
Str * type_name_to_ctypes_param(Str * name, Bool is_shallow);
Str * type_name_to_ctypes_return(Str * name, Bool is_shallow);
I32 build_python_binding(Expr * program, Str * py_path, Str * lib_name);
I32 compile_lib(Str * c_path, Str * lib_name, Str * ext_c_path, Str * user_c_path, Str * link_flags, Str * include_flags, Target * target, Str * cc_override);
I32 compile_c(Str * c_path, Str * bin_path, Str * ext_c_path, Str * user_c_path, Str * link_flags, Str * include_flags, Target * target, Str * cc_override);
void emit_global_inits_prog(File * f, Expr * prog);
void emit_global_inits(File * f);
void build_register_funcsig_names(Expr * core_program, Expr * program);
void register_lookups_prog(Expr * prog);
void build_register_lookups(Expr * core_program, Expr * program);
void emit_monolithic_header(File * f, Expr * core_program, Expr * program, Mode * mode);
void emit_all_forward_declarations(File * f, Expr * core_program, Expr * program, Mode * mode);
void emit_dyn_fn_wrapper(File * f, Str * type_name, Str * method_name, FunctionDef * fd);
void emit_dyn_fn_wrappers(File * f, Expr * core_program, Expr * program);
void emit_dyn_call_bodies(File * f, Expr * core_program, Expr * program);
void emit_dyn_has_bodies(File * f, Expr * core_program, Expr * program);
void emit_collection_helpers(File * f, Expr * core_program, Expr * program);
void emit_global_declarations(File * f, Expr * core_program, Expr * program);
void emit_test_main(File * f, Expr * program);
void emit_script_main(File * f, Expr * program);
void emit_function_bodies(File * f, Expr * core_program, Expr * program, Mode * mode);
void emit_ext_func_declarations(File * f, Expr * program);
void emit_lib_init(File * f);
I32 build(Expr * core_program, Expr * program, Mode * mode, Bool run_tests, Str * c_output_path);
BuildPaths * BuildPaths_clone(BuildPaths * self);
void BuildPaths_delete(BuildPaths * self, Bool * call_free);
U32 BuildPaths_size(void);
BuildPaths * derive_build_paths(LoadedProgram * lp, Str * custom_bin, Str * custom_c, Target * target);
void make_build_dirs(BuildPaths * paths);
I32 translate_ast(LoadedProgram * lp, BuildPaths * paths);
void print_translate_success(BuildPaths * paths);
I32 compile_ast(LoadedProgram * lp, BuildPaths * paths, Target * target, Str * cc_override);
I32 cmd_translate(LoadedProgram * lp, Str * custom_c);
I32 cmd_build(LoadedProgram * lp, Str * custom_bin, Str * custom_c, Target * target, Str * cc_override);
I32 cmd_run(LoadedProgram * lp, Str * custom_bin, Str * custom_c, Vec * user_argv, Target * target, Str * cc_override);
I32 system_cmd(Str * cmd);
Bool StructInstance_eq(StructInstance * a, StructInstance * b);
Str * StructInstance_to_str(StructInstance * self);
StructInstance * StructInstance_clone(StructInstance * self);
void StructInstance_delete(StructInstance * self, Bool * call_free);
U32 StructInstance_size(void);
Bool EnumInstance_eq(EnumInstance * a, EnumInstance * b);
Str * EnumInstance_to_str(EnumInstance * self);
EnumInstance * EnumInstance_clone(EnumInstance * self);
void EnumInstance_delete(EnumInstance * self, Bool * call_free);
U32 EnumInstance_size(void);
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
Bool Value_is(Value * self, Value * other);
void Value_delete(Value * self, Bool * call_free);
U32 Value_size(void);
Cell * Cell_clone(Cell * self);
void Cell_delete(Cell * self, Bool * call_free);
U32 Cell_size(void);
Binding * Binding_clone(Binding * self);
void Binding_delete(Binding * self, Bool * call_free);
U32 Binding_size(void);
Scope * Scope_clone(Scope * self);
void Scope_delete(Scope * self, Bool * call_free);
U32 Scope_size(void);
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
I32 elem_size_for_type(Str * type_name);
Value parse_cli_arg(Str * s, Str * type_name);
Value eval_expr(Scope * scope, Expr * e);
Value * reinterpret_ptr_value(Value * val, Str * type_name, Scope * scope);
Bool guard_own_param_skip(Scope * scope, Expr * e, Expr * func_def);
void * resolve_field_assign_base(Scope * scope, Expr * obj_expr);
Expr * resolve_field_assign_sdef(Scope * scope, Expr * obj_expr);
void eval_body(Scope * scope, Expr * body);
Value eval_call(Scope * scope, Expr * e);
void free_value(Value v);
Bool needs_widen(Value * val, Str * ptype);
Value shallow_copy_value(Value * v);
Value make_struct_value(Str * sname, Expr * sdef, void * data, Bool borrowed);
Value * widen_numeric(Value * v, Str * ptype);
Cell * scope_get(Scope * s, Str * name);
Scope * scope_new(Scope * parent);
void scope_set_owned(Scope * s, Str * name, Value * val);
void scope_set_borrowed(Scope * s, Str * name, Cell * cell);
void scope_free(Scope * s);
Bool interp_fa_is_ns_inner(Scope * scope, Expr * e, Str * sname);
Bool interp_fa_is_ns(Scope * scope, Expr * e);
void value_to_buf(void * dest, Value * val, Str * type_name);
Value build_argv_array(Vec * argv, U32 offset, U32 count, Str * elem_type);
void interpreter_init_ns(Scope * global, Expr * program);
Str * ns_qname(Str * sname, Str * fname);
Value * ns_get(Str * sname, Str * fname);
void ns_set(Str * sname, Str * fname, Value val);
Value make_str_value(void * data, U64 len);
Value make_str_value_own(void * data, U64 len);
Str str_view(Value v);
Expr * find_field_decl(Expr * struct_def, Str * fname);
Value read_field(StructInstance * inst, Expr * fdecl);
void write_field(StructInstance * inst, Expr * fdecl, Value * val);
void interpret_register_defs(Scope * global, Expr * prog);
void interpret_register_aliases(Scope * global, Expr * prog);
void interpret_copy_alias_ns(Expr * prog, Scope * global);
I32 interpret(Expr * core_program, Expr * program, Mode * mode, Bool run_tests, Str * path, Str * user_c, Str * ext_c, Str * link_flags, Vec * user_argv, Str * fwd_path);
I32 cmd_interpret(LoadedProgram * lp, Vec * user_argv);
ExtStr * ExtStr_clone(ExtStr * self);
void ExtStr_delete(ExtStr * self, Bool * call_free);
U32 ExtStr_size(void);
ffi_type * ffi_type_clone(ffi_type * self);
void ffi_type_delete(ffi_type * self, Bool * call_free);
U32 ffi_type_size(void);
ffi_cif * ffi_cif_clone(ffi_cif * self);
void ffi_cif_delete(ffi_cif * self, Bool * call_free);
U32 ffi_cif_size(void);
FFIEntry * FFIEntry_clone(FFIEntry * self);
void FFIEntry_delete(FFIEntry * self, Bool * call_free);
U32 FFIEntry_size(void);
ExprPtrBox * ExprPtrBox_clone(ExprPtrBox * self);
void ExprPtrBox_delete(ExprPtrBox * self, Bool * call_free);
U32 ExprPtrBox_size(void);
FFITypePtrBox * FFITypePtrBox_clone(FFITypePtrBox * self);
void FFITypePtrBox_delete(FFITypePtrBox * self, Bool * call_free);
U32 FFITypePtrBox_size(void);
ffi_type * ffi_type_pointer_ref(void);
ffi_type * ffi_type_sint64_ref(void);
ffi_type * ffi_type_uint8_ref(void);
ffi_type * ffi_type_sint16_ref(void);
ffi_type * ffi_type_sint32_ref(void);
ffi_type * ffi_type_uint32_ref(void);
ffi_type * ffi_type_uint64_ref(void);
ffi_type * ffi_type_float_ref(void);
ffi_type * ffi_type_void_ref(void);
I32 ffi_prep_cif(ffi_cif * cif, I32 abi, U32 nargs, ffi_type * rtype, void * atypes);
void ffi_call(ffi_cif * cif, void * fn, void * rvalue, void * avalue);
void * ffi_alloc_cif(void);
Bool ffi_cif_rtype_is_struct(ffi_cif * cif);
Bool ffi_load_global_lib(Str * soname);
Bool ffi_open_user_so(Str * path);
void ffi_close_user_so(void);
U8 * ffi_user_symbol(Str * name);
U8 * ffi_global_symbol(Str * name);
Str * ffi_last_error(void);
I32 stderr_print(Str * msg);
I32 system_cmd(Str * cmd);
void unlink_path(Str * path);
I32 process_id(void);
U8 * ffi_dlsym(Str * name);
void ffi_init_link_libs(Str * link_flags);
I32 ffi_init_user_so(Str * fwd_path, Str * user_c_path, Str * ext_c_path, Str * link_flags, Str * so_path_out);
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
Bool h_print_flush(Scope * _s, Expr * _e, Value * r);
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
Bool h_clock_ms(Scope * _s, Expr * _e, Value * r);
Bool h_get_thread_count(Scope * _s, Expr * _e, Value * r);
Bool h_cfile_open(Scope * s, Expr * e, Value * r);
ffi_type * shallow_ffi_type(Str * type_name);
ffi_type * field_ffi_type(Expr * field);
ffi_type * build_struct_ffi_type(Expr * struct_def);
Bool h_free(Scope * s, Expr * e, Value * r);
Bool h_cfile_close(Scope * s, Expr * e, Value * r);
Bool h_cfile_write_str(Scope * s, Expr * e, Value * r);
Bool h_ptr_add(Scope * s, Expr * e, Value * r);
Bool h_cfile_read_all(Scope * s, Expr * e, Value * r);
void reg_dispatch(Str * name, DispatchFn handler);
void dispatch_init(void);
Bool ext_dispatch_builtin(Str * name, Scope * scope, Expr * e, Value * result);
Bool h_dyn_call(Scope * s, Expr * e, Value * r);
I32 get_elem_size(Scope * s, Str * type_name, Expr * src);
Bool h_array(Scope * s, Expr * e, Value * r);
Bool h_vec(Scope * s, Expr * e, Value * r);
Bool enum_method_dispatch(Str * method, Scope * scope, Expr * enum_def, Str * enum_name, Expr * e, Value * result);
Bool ext_dispatch_ffi(Str * name, Scope * scope, Expr * e, Value * result);
Bool ext_function_dispatch(Str * name, Scope * scope, Expr * e, Value * result);
void ffi_register(Str * name, void * fn, Expr * fdef);
void ffi_init_scan_program(Expr * program);
I32 ffi_init(Expr * program, Str * fwd_path, Str * user_c_path, Str * ext_c_path, Str * link_flags);
void ffi_cleanup(void);
Str get_version(void);
Str * get_bin_dir(void);
Str * get_cwd_str(void);
Str * repl_read_line(Str * mode_name);
void run_repl_session(Str * mode_name_in, Str * next_mode_out);
void run_repl(Str * initial_mode);
void usage(void);
CliArgs * CliArgs_clone(CliArgs * self);
void CliArgs_delete(CliArgs * self, Bool * call_free);
U32 CliArgs_size(void);
CliArgs * parse_args(Array * args);
Vec * collect_user_argv(LoadedProgram * lp, Array * args, U32 start_idx);
void main(Array * args);
Bool TokenType_eq(TokenType *, TokenType *);
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
TokenType *TokenType_Percent();
TokenType *TokenType_Ampersand();
TokenType *TokenType_Pipe();
TokenType *TokenType_Caret();
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
TokenType *TokenType_PlusPlus();
TokenType *TokenType_MinusMinus();
TokenType *TokenType_ColonEq();
TokenType *TokenType_Ident();
TokenType *TokenType_StringTok();
TokenType *TokenType_Number();
TokenType *TokenType_Char();
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
TokenType *TokenType_KwExtStruct();
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
Bool ScopeFind_eq(ScopeFind *, ScopeFind *);
ScopeFind *ScopeFind_NotFound();
ScopeFind *ScopeFind_Found(TypeBinding *);
Bool CtorArg_eq(CtorArg *, CtorArg *);
CtorArg *CtorArg_Unfilled();
CtorArg *CtorArg_Filled(Expr *);
Bool Lang_eq(Lang *, Lang *);
Lang *Lang_C();
Lang *Lang_HolyC();
Lang *Lang_TIL();
Bool Target_eq(Target *, Target *);
Target *Target_LinuxX64();
Target *Target_LinuxArm64();
Target *Target_LinuxRiscv64();
Target *Target_WindowsX64();
Target *Target_MacosX64();
Target *Target_MacosArm64();
Target *Target_Wasm32();
Target *Target_TempleosX86();
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
extern Map core_modes;
extern I32 hoist_counter;
extern I32 _va_counter;
extern I32 _kw_counter;
extern I32 errors;
extern Str _current_type_name;
extern Expr *_current_struct_def;
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
extern Expr *codegen_core_program;
extern Expr *codegen_program;
extern Expr *current_fdef;
extern Map struct_bodies;
extern Map func_defs;
extern Map struct_def_exprs;
extern Set script_globals;
extern Bool has_script_globals;
extern Set ref_globals;
extern Bool has_ref_globals;
extern Bool in_func_def;
extern Bool in_main_func;
extern Set funcsig_names;
extern Bool has_funcsig_names;
extern I32 _ctor_seq;
extern Set stack_locals;
extern Map stack_local_types;
extern Set unsafe_to_hoist;
extern Set ref_locals;
extern Bool has_return;
extern Bool has_break;
extern Bool has_continue;
extern Value return_value;
extern Expr *cached_str_def;
extern Str *cached_str_name;
extern Expr *cached_array_def;
extern Str *cached_array_name;
extern Expr *cached_vec_def;
extern Str *cached_vec_name;
extern Map ns_fields;
extern Vec ns_keys;
extern I32 ENUM_PAYLOAD_OFFSET;
extern Bool ns_inited;
extern I32 ENUM_PAYLOAD_OFFSET;
extern I32 FFI_DEFAULT_ABI;
extern I16 FFI_TYPE_STRUCT;
extern Map dispatch_map;
extern Bool dispatch_inited;
extern Map ffi_map;
extern Map ffi_struct_defs;
extern Bool ffi_loaded;
extern Vec ffi_type_cache;
extern Bool ffi_type_cache_inited;
extern Bool ffi_map_inited;
extern Str BASE_VERSION;
extern Str VERSION;

