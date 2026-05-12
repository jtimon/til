#pragma once
#include "ext.h"

typedef struct Vec Vec;
typedef struct Str Str;
typedef struct Dynamic Dynamic;
typedef struct Map Map;
typedef enum {
    Type_TAG_Unknown,
    Type_TAG_None,
    Type_TAG_I64,
    Type_TAG_U8,
    Type_TAG_I16,
    Type_TAG_I32,
    Type_TAG_U32,
    Type_TAG_U64,
    Type_TAG_F32,
    Type_TAG_Bool,
    Type_TAG_Struct,
    Type_TAG_StructDef,
    Type_TAG_Enum,
    Type_TAG_EnumDef,
    Type_TAG_FuncDef,
    Type_TAG_FuncPtr,
    Type_TAG_Dynamic,
    Type_TAG_Custom
} Type_tag;
typedef struct Type Type;
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
typedef struct ForInData ForInData;
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
    NodeType_TAG_NoDefaultArg,
    NodeType_TAG_Throw,
    NodeType_TAG_Catch
} NodeType_tag;
typedef struct NodeType NodeType;
typedef struct Expr Expr;
typedef struct Array Array;
typedef struct File File;
typedef struct Set Set;
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
    TokenType_TAG_DocComment,
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
    TokenType_TAG_KwPriv,
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
typedef struct ImportUnit ImportUnit;
typedef struct Context Context;
typedef struct Mode Mode;
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
typedef struct LocalInfo LocalInfo;
typedef enum {
    CtorArg_TAG_Unfilled,
    CtorArg_TAG_Filled
} CtorArg_tag;
typedef struct CtorArg CtorArg;
typedef struct CoverageNode CoverageNode;
typedef struct ProgramUnit ProgramUnit;
typedef struct LoadedProgram LoadedProgram;
typedef struct DeclRef DeclRef;
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
typedef struct _ffi_type ffi_type;
typedef struct ExtStr ExtStr;
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


typedef struct Dynamic {
    char _;
} Dynamic;





struct Type {
    Type_tag tag;
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
    Str doc;
    Str explicit_type;
    Bool is_mut;
    Bool is_priv;
    Bool used;
    OwnType own_type;
    Type til_type;
    I32 field_offset;
    I32 field_size;
    Expr *field_struct_def;
    Expr *default_value;
    Str orig_name;
} Declaration;


typedef struct FCallData {
    I32 variadic_index;
    U32 variadic_count;
    I32 kwargs_index;
    U32 kwargs_count;
    Bool is_splat;
    Bool does_throw;
    U64 own_args;
} FCallData;


typedef struct AssignData {
    Str name;
    Bool save_old_delete;
} AssignData;


typedef struct ForInData {
    Str name;
    Bool is_mut;
} ForInData;


typedef struct Array {
    U8 *data;
    U32 cap;
    U32 elem_size;
    Str elem_type;
    void * elem_clone;
    void * elem_delete;
} Array;


typedef struct File {
    U8 *handle;
    Bool is_write;
} File;


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


struct TokenType {
    TokenType_tag tag;
};

typedef struct Token {
    TokenType type;
    Str text;
    U32 line;
    U32 col;
} Token;


typedef struct TypeBinding {
    Str name;
    Type type;
    FuncType func_type;
    Bool is_mut;
    Bool is_priv;
    Str path;
    U32 line;
    U32 col;
    Bool is_param;
    OwnType own_type;
    Bool is_alias;
    Bool is_type_alias;
    Str alias_target;
    Expr *struct_def;
    Expr *func_def;
    Bool is_builtin;
    Bool used;
    Str orig_name;
} TypeBinding;


struct ScopeFind {
    ScopeFind_tag tag;
    union {
        TypeBinding Found;
    } data;
};

typedef struct Mode {
    Bool needs_main;
    Bool decls_only;
    Str auto_import;
    Bool is_library;
    Bool is_pure;
    Bool run_tests;
    Bool debug_prints;
} Mode;


struct Lang {
    Lang_tag tag;
};

struct Target {
    Target_tag tag;
};

typedef struct LocalInfo {
    Str *name;
    Type type;
    I32 decl_index;
    I32 last_use;
    I32 own_transfer;
    Bool skip_scope_delete;
    Bool is_heap;
} LocalInfo;


typedef struct DeclRef {
    Str path;
    U32 idx;
} DeclRef;


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


typedef struct ExtStr {
    U8 *data;
    U64 count;
    U64 cap;
} ExtStr;


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
    Str install_prefix;
    U32 path_idx;
    Bool early_return;
} CliArgs;


typedef struct Vec {
    U8 *data;
    U32 count;
    U32 cap;
    U32 elem_size;
    Str elem_type;
    void * elem_clone;
    void * elem_delete;
} Vec;


typedef struct Map {
    Vec keys;
    Vec values;
    void * key_cmp;
} Map;


typedef struct FunctionDef {
    FuncType func_type;
    Vec params;
    Str return_type;
    Vec throw_types;
    I32 variadic_index;
    I32 kwargs_index;
    OwnType return_own_type;
    Bool auto_generated;
} FunctionDef;


typedef struct StructDef {
    I32 total_struct_size;
    Vec fields;
    Vec ns_decls;
    Str c_tag;
} StructDef;


typedef struct EnumDef {
    Vec ns_decls;
    Vec variants;
    Map payload_types;
    I32 total_enum_size;
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
        ForInData ForIn;
        Str NamedArg;
    } data;
};

typedef struct Expr {
    NodeType node_type;
    Type til_type;
    Vec children;
    U32 line;
    U32 col;
} Expr;


typedef struct Parser {
    Vec tokens;
    U32 pos;
    Str path;
    Vec fn_sig_decls;
    Str pending_doc;
} Parser;


typedef struct TypeScope {
    Map bindings;
    TypeScope *parent;
} TypeScope;


typedef struct ImportUnit {
    Mode mode;
    Expr *ast;
    Vec imports;
} ImportUnit;


typedef struct Context {
    Mode mode;
    Str path;
    Map path_modes;
    Map imported;
    Set imports_init_done;
    Set imports_typer_done;
    Set imports_precomp_done;
    Set imports_eval_done;
    TypeScope scope;
    Bool is_repl;
    Bool typing_namespace_member;
    Map local_fn_sigs;
    Map func_defs;
    Map struct_def_exprs;
    Set funcsig_names;
    Set script_globals;
    Set ref_globals;
    Set stack_locals;
    Map stack_local_types;
    Set unsafe_to_hoist;
    Set ref_locals;
    Set ref_dyn_locals;
    Expr *current_fdef;
    Expr *cached_str_def;
    Str *cached_str_name;
    Expr *cached_array_def;
    Str *cached_array_name;
    Expr *cached_vec_def;
    Str *cached_vec_name;
} Context;


struct CtorArg {
    CtorArg_tag tag;
    union {
        Expr Filled;
    } data;
};

typedef struct CoverageNode {
    Bool fully_covered;
    Vec sub_names;
    Vec sub_nodes;
} CoverageNode;


typedef struct ProgramUnit {
    Str path;
    Mode mode;
    Vec imports;
} ProgramUnit;


typedef struct LoadedProgram {
    Vec *core_units;
    Vec *units;
    Target target;
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


typedef struct Scope {
    Map bindings;
    Scope *parent;
} Scope;


void F32_delete(F32 * self, Bool * call_free);
U32 * F32_size(void);
Str * U64_to_str(U64 val);
void U64_inc(U64 * self);
void U64_dec(U64 * self);
void U64_delete(U64 * self, Bool * call_free);
U32 * U64_size(void);
Bool U64_lt(U64 * a, U64 * b);
Bool U64_gt(U64 * a, U64 * b);
Bool U64_lte(U64 * a, U64 * b);
Str * U32_to_str(U32 * val);
void U32_inc(U32 * self);
void U32_dec(U32 * self);
void U32_delete(U32 * self, Bool * call_free);
U32 * U32_size(void);
Bool U32_lt(U32 * a, U32 * b);
Bool U32_gt(U32 * a, U32 * b);
Bool U32_neq(U32 * a, U32 * b);
Bool U32_lte(U32 * a, U32 * b);
Bool U32_gte(U32 * a, U32 * b);
Str * I32_to_str(I32 * val);
void I32_inc(I32 * self);
void I32_dec(I32 * self);
void I32_delete(I32 * self, Bool * call_free);
U32 * I32_size(void);
Bool I32_lt(I32 * a, I32 * b);
Bool I32_gt(I32 * a, I32 * b);
Bool I32_neq(I32 * a, I32 * b);
Bool I32_lte(I32 * a, I32 * b);
Bool I32_gte(I32 * a, I32 * b);
Str * U8_to_str(U8 * val);
void U8_delete(U8 * self, Bool * call_free);
U32 * U8_size(void);
Bool U8_lt(U8 * a, U8 * b);
Bool U8_gt(U8 * a, U8 * b);
Bool U8_neq(U8 * a, U8 * b);
Bool U8_lte(U8 * a, U8 * b);
Bool U8_gte(U8 * a, U8 * b);
Vec * Vec_new_type_name(Str * elem_type);
Vec * Vec_new(Type * T);
U32 Vec_len(Vec * self);
void Vec_push(Vec * self, void * val);
void Vec_append(Vec * self, Vec * other);
void Vec_move_from(Vec * self, Vec * other);
void * Vec_get(Vec * self, U32 * i);
void * Vec_pop(Vec * self);
void Vec_set(Vec * self, U32 * i, void * val);
void Vec_push_take(Vec * self, Vec * src, U32 i);
void Vec_delete(Vec * self, Bool * call_free);
Vec * Vec_clone(Vec * self);
U32 Vec_size(void);
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
Str * Str_substr(Str * s, U32 * start, U32 * n);
Bool Str_contains(Str * a, Str * b);
Bool Str_starts_with(Str * a, Str * b);
Bool Str_ends_with(Str * a, Str * b);
Bool Str_is_empty(Str * self);
I64 Str_find(Str * self, Str * needle);
I64 Str_rfind(Str * self, Str * needle);
Str * Str_replace(Str * self, Str * from, Str * to);
Str * Str_strip_prefix(Str * self, Str * prefix);
Str * Str_strip_suffix(Str * self, Str * suffix);
Str * Str_from_byte(U8 * byte);
I64 Str_to_i64(Str * self);
U8 Str_to_u8(Str * self);
I32 Str_to_i32(Str * self);
U32 Str_to_u32(Str * self);
U64 Str_to_u64(Str * self);
U32 Str_to_usize(Str * self);
F32 Str_to_f32(Str * self);
Vec * Str_split(Str * self, Str * delim);
U32 Str_size(void);
Bool Str_eq(Str * a, Str * b);
Str * join(Vec * parts, Str * sep);
U32 * Dynamic_size(void);
void * default_clone(void * v);
void default_delete(void * _v, Bool * _cf);
I64 * default_cmp(void * _a, void * _b);
Str * I16_to_str(I16 * val);
void I16_delete(I16 * self, Bool * call_free);
U32 * I16_size(void);
Str * I64_to_str(I64 * val);
void I64_inc(I64 * self);
void I64_dec(I64 * self);
void I64_delete(I64 * self, Bool * call_free);
U32 * I64_size(void);
Bool I64_lt(I64 * a, I64 * b);
Bool I64_gt(I64 * a, I64 * b);
Bool I64_neq(I64 * a, I64 * b);
Bool I64_lte(I64 * a, I64 * b);
Bool I64_gte(I64 * a, I64 * b);
I64 * Bool_cmp(Bool * a, Bool * b);
void Bool_delete(Bool * self, Bool * call_free);
U32 * Bool_size(void);
Map * Map_new_type_names(Str * key_type, Str * val_type);
Map * Map_new(Type * K, Type * V);
U32 * Map_len(Map * self);
void * Map_key_ptr(Map * self, U32 * i);
void * Map_val_ptr(Map * self, U32 * i);
Bool Map_has(Map * self, void * key);
void * Map_get(Map * self, void * key);
void Map_set(Map * self, void * key, void * val);
void Map_delete(Map * self, Bool * call_free);
Map * Map_clone(Map * self);
U32 Map_size(void);
Bool Type_eq(Type * a, Type * b);
Bool Type_is(Type * self, Type * other);
void Type_delete(Type * self, Bool * call_free);
Type * Type_clone(Type * self);
U32 Type_size(void);
Str * til_type_name_c(Type * t);
Str * til_type_name(Type * t);
Bool FuncType_is(FuncType * self, FuncType * other);
Bool FuncType_eq(FuncType * self, FuncType * other);
void FuncType_delete(FuncType * self, Bool * call_free);
FuncType * FuncType_clone(FuncType * self);
U32 FuncType_size(void);
Bool OwnType_is(OwnType * self, OwnType * other);
Bool OwnType_eq(OwnType * self, OwnType * other);
void OwnType_delete(OwnType * self, Bool * call_free);
OwnType * OwnType_clone(OwnType * self);
U32 OwnType_size(void);
Declaration * Declaration_clone(Declaration * self);
void Declaration_delete(Declaration * self, Bool * call_free);
U32 Declaration_size(void);
FunctionDef * FunctionDef_clone(FunctionDef * self);
void FunctionDef_delete(FunctionDef * self, Bool * call_free);
U32 FunctionDef_size(void);
FCallData * FCallData_clone(FCallData * self);
void FCallData_delete(FCallData * self, Bool * call_free);
U32 FCallData_size(void);
void set_own_arg(Expr * fcall, U32 arg_index);
Bool get_own_arg(Expr * fcall, U32 arg_index);
StructDef * StructDef_clone(StructDef * self);
void StructDef_delete(StructDef * self, Bool * call_free);
U32 StructDef_size(void);
EnumDef * EnumDef_clone(EnumDef * self);
void EnumDef_delete(EnumDef * self, Bool * call_free);
U32 EnumDef_size(void);
AssignData * AssignData_clone(AssignData * self);
void AssignData_delete(AssignData * self, Bool * call_free);
U32 AssignData_size(void);
ForInData * ForInData_clone(ForInData * self);
void ForInData_delete(ForInData * self, Bool * call_free);
U32 ForInData_size(void);
Bool NodeType_is(NodeType * self, NodeType * other);
void NodeType_delete(NodeType * self, Bool * call_free);
NodeType * NodeType_clone(NodeType * self);
U32 NodeType_size(void);
void Expr_error(Expr * self, Str * path, Str * msg);
void Expr_add_child(Expr * self, Expr * child);
void Expr_push_child_clone(Expr * self, Expr * child);
void Expr_take_children(Expr * self, Expr * other);
Expr * Expr_child(Expr * parent, U32 * i);
Expr * Expr_new(NodeType * data, U32 line, U32 col);
Str * Expr_to_str(Expr * self);
Expr * Expr_clone(Expr * self);
void Expr_delete(Expr * self, Bool * call_free);
U32 Expr_size(void);
Str * func_type_variant_name(FuncType * ft);
Str * node_head_str(NodeType * data);
Str * expr_to_str_indent(Expr * self, U32 indent);
Str * func_type_name(FuncType * ft);
Bool is_decl_with_child(Expr * stmt);
Bool is_struct_or_enum(Expr * stmt);
Bool is_func_decl(Expr * stmt);
Bool is_def(Expr * stmt);
Vec * def_ns_decls(Expr * sdef);
Bool enum_has_payloads(Expr * enum_def);
I32 * enum_variant_tag(Expr * enum_def, Str * variant_name);
Str * enum_variant_type(Expr * enum_def, I32 tag);
Array * Array_new_type_name(Str * elem_type, U32 * cap);
Array * Array_new(Type * T, U32 * cap);
U32 * Array_len(Array * self);
void * Array_get(Array * self, U32 * i);
void Array_set(Array * self, U32 * i, void * val);
void Array_delete(Array * self, Bool * call_free);
Array * Array_clone(Array * self);
U32 Array_size(void);
void panic(Str * loc_str, Array * parts);
void UNREACHABLE(Str * loc_str);
void println(Array * parts);
File * File_new(Str * path, Bool is_write);
void File_write(File * self, Str * s);
void File_close(File * self);
File * File_clone(File * self);
void File_delete(File * self, Bool * call_free);
U32 File_size(void);
void swap(void * a, void * b, U64 size);
void move(void * dest, void * src, U64 size);
Set * Set_new(Type * T);
U32 * Set_len(Set * self);
Bool Set_has(Set * self, void * val);
void Set_add(Set * self, void * val);
void Set_delete(Set * self, Bool * call_free);
Set * Set_clone(Set * self);
U32 Set_size(void);
I64 * wait_cmd(I64 * pid);
I64 * run_cmd(Str * output, Array * args);
Bool TokenType_is(TokenType * self, TokenType * other);
Bool TokenType_eq(TokenType * self, TokenType * other);
void TokenType_delete(TokenType * self, Bool * call_free);
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
Type * til_type_from_explicit_type(Str * name);
Str * parse_fn_signature(Parser * p, U32 line, U32 col);
Expr * parse_block(Parser * p);
Expr * parse_func_def(Parser * p);
Expr * parse_struct_def(Parser * p, Str * c_tag);
Expr * parse_enum_def(Parser * p);
Expr * parse_call(Parser * p, Str * name, U32 call_line, U32 call_col);
Expr * make_binop_call(Expr * lhs, Str * method, U32 op_line, U32 op_col, Expr * rhs);
Expr * parse_primary(Parser * p);
Expr * parse_multiplicative(Parser * p);
Expr * parse_additive(Parser * p);
Expr * parse_comparison(Parser * p);
Expr * parse_bitand(Parser * p);
Expr * parse_bitxor(Parser * p);
Expr * parse_bitor(Parser * p);
Expr * parse_expression(Parser * p);
Expr * parse_statement_ident(Parser * p, Bool is_mut, OwnType own_type);
void drain_doc_comments(Parser * p);
Expr * parse_statement(Parser * p);
Expr * parse_statement_body(Parser * p);
Expr * parse(Vec * tokens, Str * path, Str * mode_out);
Bool is_lift_target(Expr * stmt);
Str * lookup_name(Map * renamings, Str * name);
void rename_ident_in_place(Expr * e, Map * renamings);
void rename_decl_in_place(Declaration * dd, Map * renamings);
void rewrite_refs(Expr * e, Map * renamings);
void lift_in_body(Expr * body, Str * parent_prefix, Vec * top_level);
void lift_in_ns_decls(Expr * def, Str * parent_prefix, Vec * top_level);
void recurse_into_subbodies(Expr * body, Str * parent_prefix, Vec * top_level);
void recurse_into_expr(Expr * e, Str * parent_prefix, Vec * top_level);
void lift_nested_defs(Expr * prog);
TypeBinding * TypeBinding_clone(TypeBinding * self);
void TypeBinding_delete(TypeBinding * self, Bool * call_free);
U32 TypeBinding_size(void);
ScopeFind * ScopeFind_NotFound(void);
ScopeFind * ScopeFind_Found(TypeBinding * val);
Bool ScopeFind_is(ScopeFind * self, ScopeFind * other);
void ScopeFind_delete(ScopeFind * self, Bool * call_free);
ScopeFind * ScopeFind_clone(ScopeFind * self);
U32 ScopeFind_size(void);
TypeBinding * TypeScope_get_binding(TypeScope * self, Str * name);
ScopeFind * TypeScope_find(TypeScope * self, Str * name);
Type * TypeScope_get_type(TypeScope * self, Str * name);
FuncType TypeScope_get_func_type(TypeScope * self, Str * name);
Expr * TypeScope_get_struct(TypeScope * self, Str * name);
Bool TypeScope_is_mut(TypeScope * self, Str * name);
void TypeScope_set(TypeScope * self, Str * name, Type * type, FuncType func_type, Bool is_mut, Str * path, U32 line, U32 col, Bool is_param, OwnType own_type);
TypeScope * TypeScope_clone(TypeScope * self);
void TypeScope_delete(TypeScope * self, Bool * call_free);
U32 TypeScope_size(void);
ImportUnit * ImportUnit_clone(ImportUnit * self);
void ImportUnit_delete(ImportUnit * self, Bool * call_free);
U32 ImportUnit_size(void);
Context * Context_clone(Context * self);
void Context_delete(Context * self, Bool * call_free);
U32 Context_size(void);
I32 align_up(I32 offset, I32 align);
Expr * make_get_payload_fcall(Expr * arg, Type payload_type, U32 line, U32 col);
Expr * make_payload_ref_decl(Expr * arg, Str * bind_name, Str * vtype, U32 line, U32 col);
Type * type_from_name_init(Str * name, TypeScope * scope);
Type * init_type_from_explicit_type(Str * name, TypeScope * scope);
I32 register_struct_def_for_stmt(Expr * stmt, TypeScope * scope);
void gen_struct_clone_delete_for_stmt(Expr * stmt, TypeScope * scope);
I32 register_enum_definition(Expr * stmt, TypeScope * scope);
void collect_enum_variants(Expr * enum_def, Vec * variant_names, Vec * variant_types, Bool * has_payloads);
void generate_enum_variant_constructors(Expr * enum_def, Str * ename, U32 line, U32 col, Vec * variant_names, Vec * variant_types, Bool has_payloads);
void generate_enum_is_method(Expr * enum_def, Str * ename, U32 line, U32 col);
void generate_enum_eq_method(Expr * enum_def, Str * ename, U32 line, U32 col, Vec * variant_names, Vec * variant_types, TypeScope * scope);
void generate_enum_delete_method(Expr * enum_def, Str * ename, U32 line, U32 col, Vec * variant_names, Vec * variant_types, Bool has_payloads, TypeScope * scope);
void generate_enum_to_str_method(Expr * enum_def, Str * ename, U32 line, U32 col, Vec * variant_names, Vec * variant_types, Bool has_payloads, TypeScope * scope);
void generate_enum_clone_method(Expr * enum_def, Str * ename, I32 line, I32 col, Vec * variant_names, Vec * variant_types, Bool has_payloads);
I32 register_enum_def_for_stmt(Expr * stmt, TypeScope * scope);
void gen_enum_nonclone_methods_for_stmt(Expr * stmt, TypeScope * scope);
void gen_missing_enum_clone_for_stmt(Expr * stmt);
void register_funcsig_alias_for_stmt(Expr * stmt, TypeScope * scope);
void register_type_alias_for_stmt(Expr * stmt, TypeScope * scope);
void register_top_level_value_for_stmt(Expr * stmt, TypeScope * scope);
void register_function_def_for_stmt(Expr * stmt, TypeScope * scope);
void gen_struct_size_method_for_stmt(Expr * stmt);
void gen_enum_size_method_for_stmt(Expr * stmt, TypeScope * scope);
void gen_unity_derived_for_stmt(Expr * stmt);
void gen_cmp_derived_for_stmt(Expr * stmt);
void compute_struct_layout(Expr * struct_def, TypeScope * scope);
void type_size_align(Str * ftype, TypeScope * scope, I32 * sz, I32 * al);
I32 compute_enum_layout(Expr * enum_def, TypeScope * scope);
void resolve_field_struct_defs(Expr * program, TypeScope * scope);
Bool infer_top_level_decl_type(Expr * stmt, TypeScope * scope, Type * out_type);
I32 init_declarations_unit(Str * path, Expr * program, TypeScope * scope, Context * ctx);
I32 init_declarations_global(Expr * program, TypeScope * scope);
U32 count_ast_imports(Expr * body);
I32 init_file(Str * path, Context * ctx);
Mode * Mode_clone(Mode * self);
void Mode_delete(Mode * self, Bool * call_free);
U32 Mode_size(void);
void context_register_path_mode(Context * ctx, Str * path, Mode * mode);
void context_set_mode_from_path(Context * ctx, Str * path);
void context_enter_file(Context * ctx, Str * path);
Mode * mode_resolve(Str * name);
Bool Lang_is(Lang * self, Lang * other);
Bool Lang_eq(Lang * self, Lang * other);
void Lang_delete(Lang * self, Bool * call_free);
Lang * Lang_clone(Lang * self);
U32 Lang_size(void);
Str * lang_to_str(Lang * lang);
Bool Target_is(Target * self, Target * other);
Bool Target_eq(Target * self, Target * other);
void Target_delete(Target * self, Bool * call_free);
Target * Target_clone(Target * self);
U32 Target_size(void);
Target * target_from_str(Str * s);
Str * target_to_str(Target * target);
Bool * target_is_32bit(Target * target);
Str * target_uptr_name(Target * target);
Str * target_usize_name(Target * target);
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
Str * target_system_libs(Target * target);
Str * target_ffi_lib(Target * target);
Str * target_gui_libs(Target * target);
Target * detect_current_target(void);
Bool fa_is_ns(Expr * e, TypeScope * scope);
Bool type_binding_is_type_token(TypeBinding * b);
Expr * make_til_type_expr(Expr * src, Type * t);
void rewrite_til_type_arg(TypeScope * scope, Expr * arg, Type * ptype, I32 in_func, Context * ctx);
OwnType fa_own_type(Expr * e, TypeScope * scope);
LocalInfo * LocalInfo_clone(LocalInfo * self);
void LocalInfo_delete(LocalInfo * self, Bool * call_free);
U32 LocalInfo_size(void);
CtorArg * CtorArg_Unfilled(void);
CtorArg * CtorArg_Filled(Expr * val);
Bool CtorArg_is(CtorArg * self, CtorArg * other);
void CtorArg_delete(CtorArg * self, Bool * call_free);
CtorArg * CtorArg_clone(CtorArg * self);
U32 CtorArg_size(void);
CoverageNode * CoverageNode_clone(CoverageNode * self);
void CoverageNode_delete(CoverageNode * self, Bool * call_free);
U32 CoverageNode_size(void);
void init_coverage_for_enum(CoverageNode * node, Expr * enum_def);
I32 coverage_sub_index(CoverageNode * coverage, Str * variant_name);
Bool is_pattern_covered(TypeScope * scope, CoverageNode * coverage, Str * expected_type_name, Expr * pattern);
void mark_pattern_coverage(TypeScope * scope, CoverageNode * coverage, Str * expected_type_name, Expr * pattern);
void collect_missing_paths(TypeScope * scope, CoverageNode * coverage, Expr * enum_def, Str * prefix, Vec * out);
void type_error(Expr * e, Str * msg);
void type_error_at(Str * path, U32 line, U32 col, Str * msg);
Expr * find_namespace_func(Expr * sdef, Str * method);
Bool expr_is_comptime(Expr * e, TypeScope * scope);
Bool namespace_member_is_priv(Expr * sdef, Str * method);
Bool mark_ns_member_used(Expr * sdef, Str * method);
Bool try_ufcs_rewrite(TypeScope * scope, Expr * e, Expr * fa, Expr * obj, Str * method, Str * type_name);
Expr * resolve_fn_sig(Expr * fcall, TypeScope * scope);
Bool fcall_returns_own(Expr * fcall, TypeScope * scope);
void check_ref_decl_owned_init(Expr * stmt, TypeScope * scope);
void check_ref_field_owned_default(Declaration * fd, TypeScope * scope);
void check_ref_assign_owned_rhs(Expr * stmt, Str * target_name, Expr * rhs, TypeScope * scope);
void check_ref_local_null_init(Expr * stmt);
Bool infer_func_ptr_field_call(TypeScope * scope, Expr * e, Expr * fa, Expr * obj, Expr * sdef, Str * method, I32 in_func, Context * ctx);
void validate_fcall_own_args(TypeScope * scope, Expr * e, TypeBinding * callee_bind);
Bool infer_struct_constructor_fcall(TypeScope * scope, Expr * e, Str * name, I32 in_func, Context * ctx);
void desugar_user_func_fcall_args(Expr * e, Str * name, TypeBinding * callee_bind);
void validate_fcall_arg(Expr * arg, Type * ptype, Str * ptype_name, Str * param_name);
void infer_and_validate_fcall_args(TypeScope * scope, Expr * e, TypeBinding * callee_bind, I32 in_func, Context * ctx);
void resolve_fcall_return_type(TypeScope * scope, Expr * e, Str * name, TypeBinding * callee_bind, I32 in_func, Context * ctx);
Str * obj_method_type_name(Expr * obj);
Bool infer_field_access_fcall(TypeScope * scope, Expr * e, I32 in_func, Context * ctx);
void check_priv_access(Expr * e, Str * name, TypeBinding * b);
void check_priv_type_name(Expr * e, Str * name, TypeScope * scope);
void check_member_priv(Expr * e, Str * owner_name, Str * member_name, Bool * member_is_priv);
void infer_fcall_expr(TypeScope * scope, Expr * e, I32 in_func, Context * ctx);
void infer_expr(TypeScope * scope, Expr * expr, I32 in_func, Context * ctx);
void infer_ident_expr(TypeScope * scope, Expr * expr);
void infer_named_arg_expr(TypeScope * scope, Expr * expr, I32 in_func, Context * ctx);
void infer_map_lit_expr(TypeScope * scope, Expr * expr, I32 in_func, Context * ctx);
void infer_set_lit_expr(TypeScope * scope, Expr * expr, I32 in_func, Context * ctx);
Bool expr_uses_self_field(Expr * e, Str * field_name);
void check_user_delete_frees_own_fields(Str * struct_name, Expr * sdef);
void infer_type_def_expr(TypeScope * scope, Expr * expr, Context * ctx);
void infer_func_sig_expr(TypeScope * scope, Expr * expr);
void check_ref_function_returns(TypeScope * func_scope, Expr * expr);
void infer_func_def_expr(TypeScope * scope, Expr * expr, Context * ctx);
void check_unused_params(TypeScope * func_scope, Expr * expr);
void check_unused_locals(TypeScope * scope, Str * path);
I32 check_unused_priv_top_level(TypeScope * scope);
I32 check_unused_priv_members_in_program(Expr * program, Str * path);
void infer_return_stmt(TypeScope * scope, Expr * stmt, I32 in_func, I32 returns_ref, Context * ctx);
void infer_if_stmt(TypeScope * scope, Expr * stmt, I32 in_func, I32 in_loop, I32 returns_ref, Context * ctx);
void infer_field_access_expr(TypeScope * scope, Expr * expr, I32 in_func, Context * ctx);
void infer_field_assign_stmt(TypeScope * scope, Expr * stmt, I32 in_func, Context * ctx);
void infer_while_stmt(TypeScope * scope, Expr * stmt, I32 in_func, I32 returns_ref, Context * ctx);
Bool infer_decl_type_def(TypeScope * scope, Expr * stmt);
Bool infer_decl_func_def(TypeScope * scope, Expr * stmt);
Bool infer_decl_type_alias_passthrough(TypeScope * scope, Expr * stmt);
Type * declared_type_for_decl(TypeScope * scope, Expr * stmt);
void pre_coerce_decl_numeric_literals(Expr * expr, Type * target);
void infer_decl_typed_value(TypeScope * scope, Expr * stmt);
void infer_decl_untyped_value(Expr * stmt);
void finalize_decl_binding(TypeScope * scope, Expr * stmt, I32 in_type_body);
void infer_decl_stmt(TypeScope * scope, Expr * stmt, I32 in_func, I32 in_type_body, Context * ctx);
Bool is_simple_lvalue_expr(Expr * e);
Expr * fold_and_chain(Vec * conds, U32 line, U32 col);
Expr * make_switch_case_condition(TypeScope * scope, Expr * case_body, Expr * match_expr, Expr * sw_ref, U32 sw_line, U32 sw_col);
void replace_switch_stmt_with_block(Expr * body, U32 stmt_idx, Expr * block);
void append_switch_else_if(Expr * root_if, Expr * if_node);
void attach_switch_default_body(Expr * root_if, Expr * default_body);
void infer_switch_stmt(TypeScope * scope, Expr * body, U32 stmt_idx, I32 in_func, Context * ctx);
void replace_body_stmt_with_block(Expr * body, U32 stmt_idx, Expr * block);
Expr * make_field_access_call0(Expr * base, Str * field, U32 line, U32 col);
Expr * make_field_access_call1(Expr * base, Str * field, Expr * arg, U32 line, U32 col);
Expr * make_for_in_range_while_body(Str * var_name, Str * cur_name, Str * step, Expr * for_body, U32 line, U32 col, Str * elem_type, Bool var_is_mut);
Bool desugar_for_in_range_stmt(TypeScope * scope, Expr * body, U32 stmt_idx, I32 in_func, Context * ctx);
Bool desugar_for_in_collection_stmt(TypeScope * scope, Expr * body, U32 stmt_idx, I32 in_func, Context * ctx);
Bool is_compile_directive(Expr * e);
void infer_body_stmt(TypeScope * scope, Expr * body, U32 * i, I32 in_func, I32 in_loop, I32 returns_ref, I32 in_type_body, Context * ctx);
void reregister_scope_defs(Expr * body, TypeScope * scope);
void reregister_field_struct_defs(Expr * body, TypeScope * scope);
void infer_body(TypeScope * scope, Expr * body, I32 in_func, I32 owns_scope, I32 in_loop, I32 returns_ref, I32 in_type_body, Context * ctx);
void infer_body_unit(TypeScope * scope, Expr * body, I32 in_func, I32 owns_scope, I32 in_loop, I32 returns_ref, I32 in_type_body, Context * ctx);
void normalize_scope_bindings(TypeScope * scope);
Bool typer_is_lambda_target(Expr * e);
I64 * typer_lift_one_default_value(Declaration * dd, Vec * top_level, I64 * counter);
I64 * typer_lift_lambdas_in_expr(Expr * e, Vec * top_level, I64 * counter);
void typer_register_lifted_lambda(TypeScope * scope, Expr * lifted);
void typer_lift_lambdas(TypeScope * scope, Expr * prog);
I32 type_check_unit(Str * path, Expr * program, TypeScope * scope, Context * ctx);
I32 type_file(Str * path, Context * ctx);
void infer_assign_stmt(TypeScope * scope, Expr * stmt, I32 in_func, Context * ctx);
Bool rhs_is_clone_fcall(Expr * rhs);
Bool assign_target_is_func_local(TypeScope * scope, Str * name);
Bool is_numeric_type(Type * t);
Bool is_integral_numeric_type(Type * t);
Bool type_ctor_consumes(Type * t);
Bool is_usize_name(Str * name);
Bool is_uptr_name(Str * name);
Bool can_implicit_usize_coerce(Type * from, Type * to, Str * to_name);
Bool literal_in_range(Str * val_str, Type * target);
Bool can_implicit_widen(Type * from, Type * to);
Type * type_from_name_at(Str * name, TypeScope * scope, Expr * e);
Type * type_from_name(Str * name, TypeScope * scope);
Str * resolve_type_alias(TypeScope * scope, Str * name);
Str * usize_name(TypeScope * scope);
Type * usize_type(TypeScope * scope);
Bool type_has_cmp(TypeScope * scope, Str * type_name);
Bool type_has_to_str(TypeScope * scope, Str * type_name);
Bool expr_contains_fcall(Expr * e);
Bool expr_uses_var(Expr * e, Str * name);
Bool expr_contains_decl(Expr * e, Str * name);
Bool expr_used_in_nested_func(Expr * e, Str * name);
Expr * find_variadic_fcall(Expr * e);
Expr * find_kwargs_fcall(Expr * e);
Expr * find_array_vec_fcall(Expr * e);
Str * type_prefix(Type * t);
Str * type_to_name(Type * t);
Expr * make_field_delete(Expr * field_assign, OwnType field_own_type);
Expr * make_delete_call(Str * var_name, Type type, Bool arg_is_own, Bool call_free, Expr * src);
Bool transfer_is_shallow_field_value_copy(Expr * e, Str * var_name, TypeScope * scope);
Expr * make_free_call(Str * var_name, Type type, Expr * src);
Expr * make_clone_call(Str * type_name, Type type, Expr * arg, Expr * src);
Expr * make_to_str_call(Str * type_name, Expr * arg);
Expr * make_ns_call(Str * sname, Str * method, Type ret_type, Expr * src);
Expr * build_kwargs_dynmap_decl(Expr * fcall, Str * kw_name);
Expr * build_kwargs_dynmap_set(Expr * fcall, TypeScope * scope, Str * kw_name, Expr * named_arg);
Expr * build_variadic_array_decl(Expr * fcall, TypeScope * scope, Str * elem_type, Str * va_name, U32 vc);
Expr * build_variadic_array_set(Expr * fcall, TypeScope * scope, Str * va_name, I32 vi, U32 j);
Expr * build_builtin_vec_decl(Expr * fcall, TypeScope * scope, Str * elem_type, Str * vec_name);
Expr * build_builtin_vec_push(Expr * fcall, Str * vec_name, U32 j);
void rewrite_collection_fcall_to_ident(Expr * fcall, Str * coll_name, Type * coll_type);
Bool desugar_array_vec_fcall(Expr * fcall, Vec * new_ch, TypeScope * scope);
Bool desugar_array_vec_decl(Expr * stmt, Vec * new_ch, TypeScope * scope);
Bool desugar_set_literal_decl(Expr * stmt, Vec * new_ch, TypeScope * scope);
Bool desugar_map_literal_decl(Expr * stmt, Vec * new_ch, TypeScope * scope);
void process_call_desugars(Expr * e, Vec * new_ch, TypeScope * scope, Bool has_array_vec, Bool has_variadic, Bool has_kwargs);
Bool desugar_body(Expr * body, TypeScope * scope);
void hoist_param_swap_assign(Expr * stmt, Vec * hoisted, TypeScope * scope);
void hoist_expr(Expr * expr, Vec * hoisted, TypeScope * scope);
void hoist_decl_rhs(Expr * stmt, Vec * hoisted, TypeScope * scope);
void hoist_if_cond(Expr * stmt, Vec * hoisted, TypeScope * scope);
void hoist_return_expr(Expr * stmt, Vec * hoisted, TypeScope * scope);
void hoist_assign_rhs(Expr * stmt, Vec * hoisted, TypeScope * scope);
void hoist_field_assign_rhs(Expr * stmt, Vec * hoisted, TypeScope * scope);
void hoist_stmt_fcall(Expr * stmt, Vec * hoisted, TypeScope * scope);
Bool hoist_and_insert_field_deletes(Expr * body, TypeScope * scope, I32 do_hoist);
void rewrite_variadic_fcall_args(Expr * fcall, Str * va_name);
Str * resolve_variadic_elem_type(Expr * fcall, TypeScope * scope);
Bool desugar_pure_splat_variadic_call(Expr * fcall);
void rewrite_kwargs_fcall_args(Expr * fcall, Str * kw_name);
Bool check_own_args(Expr * fdef, Expr * fcall, Str * var_name);
Bool fcall_has_own_arg(Expr * fcall, Str * var_name, TypeScope * scope);
Bool expr_transfers_own(Expr * e, Str * var_name, TypeScope * scope);
Bool expr_is_borrow_source(Expr * e, TypeScope * scope);
Bool expr_is_stable_field_base(Expr * e, TypeScope * scope);
Bool expr_is_ref_decl_source(Expr * e, TypeScope * scope);
Bool field_assign_needs_delete(Expr * stmt, TypeScope * scope);
Bool alias_used_in_stmts(Vec * stmts, Str * name, Expr * expr);
void collect_scope_locals(Expr * body, TypeScope * scope, Bool is_program_scope, Vec * locals_vec);
void extend_ref_local_lifetimes(Expr * body, Vec * locals);
void check_use_after_own_transfer(Expr * body, Vec * locals);
void insert_exit_deletes(Expr * body, Vec * live, Bool return_only);
void insert_nested_exit_deletes(Expr * stmt, Vec * locals, U32 stmt_idx);
void insert_exit_deletes_into_stmt(Expr * stmt, Vec * body_stmts, Vec * locals, U32 stmt_idx, Vec * new_ch);
void insert_post_stmt_deletes(Expr * stmt, Vec * locals, U32 stmt_idx, Vec * new_ch, TypeScope * scope);
void insert_assign_delete(Expr * stmt, Vec * locals, Vec * new_ch);
void promote_own_transferred_locals(Expr * body, Vec * locals);
Bool insert_free_calls(Expr * body, TypeScope * scope, I32 scope_exit);
void infer_literal_expr(Expr * expr);
void narrow_dynamic(Expr * expr, Type * target);
I32 fcall_returns_ref(Expr * fcall, TypeScope * scope);
Expr * hoist_to_temp(Expr * val, Vec * hoisted, TypeScope * scope, Bool is_own);
Bool precomp_has_macro(Str * name);
Bool precomp_has_func(Str * name);
Bool is_side_effecting_name(Str * name);
U8 * hex_digit_value(U8 * b);
Str * from_source_form(Str * s);
Bool needs_source_escape(Str * s);
Str * str_to_source_form(Str * s);
Expr * value_to_expr(Value val, Expr * src);
Value expr_to_value(Expr * e);
Bool is_known(Expr * e, Value * out);
Bool is_known_check(Expr * e);
Bool body_has_local(Expr * body, Str * name);
Bool func_uses_unknown_globals(Expr * e, Expr * func_def, Scope * precomp_scope, Expr * body_root, Bool lenient, Set * visiting);
Expr * extract_trivial_literal_return(Expr * fdef);
void * ns_lookup_flat(Str * name);
Str * fa_recv_type_name(Expr * callee);
Expr * try_fast_fold_call(Scope * scope, Expr * fcall);
Expr * try_eval_call(Scope * scope, Expr * fcall, Bool require_known, Context * ctx);
void track_literal(Scope * scope, Str * name, Expr * rhs);
void track_literal_known_only(Str * name, Expr * rhs);
Bool is_macro_call(Expr * e);
Bool is_func_call(Expr * e);
void fold_subtree(Scope * scope, Expr * e, Context * ctx);
void process_body(Scope * scope, Expr * body, Context * ctx, Bool at_global);
void precomp_scan_names(Expr * prog);
void precomp_register_defs(Scope * global, Expr * prog);
void precomp_register_globals(Scope * global, Expr * prog);
Bool scav_fa_is_ns(Expr * e);
Str * qualified_name(Str * type_name, Str * method_name);
void vec_push_str(Vec * v, Str * s);
void children_filter(Vec * v, void * marks, U32 n);
void push_qn(Vec * v, Str * type_name, Str * method);
void push_builtin_methods(Vec * v, Str * builtin_name, Str * m1, Str * m2, Str * m3);
void collect_refs(Expr * e, Vec * refs);
void scavenge_filter(Expr * program, Set * visited);
U32 dyn_call_real_arg_count(Expr * e);
void collect_body_refs(Expr * e, Set * refs, Set * candidates);
Str * match_trivial_delete(Expr * stmt);
Bool rhs_is_pure_byvalue(Expr * e);
void prune_trivial_deletes(Expr * e, Set * dropped);
Bool dce_one_body(Expr * body);
void body_dce_walk(Expr * e);
void body_dce_ns(Expr * rhs);
void dce_program_bodies(Expr * program);
Str * realpath_str(Str * path);
Str * str_left(Str * s, U32 * n);
Str * normalize_mode_name(Str * mode_name);
Str * display_path(Str * p, Str * cwd);
Mode * require_mode(Str * path, Str * mode_name);
Str * forward_header_path(Str * path);
Str * dir_of(Str * abs);
Str * compiler_root(Str * ext_c_path);
Str * resolve_link_path(Str * base_dir, Str * root_dir, Str * path);
ProgramUnit * ProgramUnit_clone(ProgramUnit * self);
void ProgramUnit_delete(ProgramUnit * self, Bool * call_free);
U32 ProgramUnit_size(void);
Vec * resolve_import_disps(Vec * import_paths, Str * base_dir, Str * lib_dir, Str * cwd);
Vec * extract_imports(Expr * body, Str * path);
I32 * resolve_imports(Vec * import_paths, Str * base_dir, Set * resolved_set, Vec * stack, Vec * units, Str * lib_dir, Context * ctx, Str * default_mode, Str * cwd);
LoadedProgram * LoadedProgram_clone(LoadedProgram * self);
void LoadedProgram_delete(LoadedProgram * self, Bool * call_free);
U32 LoadedProgram_size(void);
void retarget_alias_binding(TypeScope * scope, Str * alias_name, Str * target_name);
void retarget_loaded_aliases(LoadedProgram * lp);
void precomp_imported(LoadedProgram * lp);
DeclRef * DeclRef_clone(DeclRef * self);
void DeclRef_delete(DeclRef * self, Bool * call_free);
U32 DeclRef_size(void);
Expr * find_ns_decl_fdef_imported(Context * ctx, Map * top, Str * name);
Set * scavenge_visited_imported(LoadedProgram * lp);
void scavenge_imported(LoadedProgram * lp);
void extract_link_info(LoadedProgram * lp);
LoadedProgram * load_program(Str * path, Str * bin_dir, Str * cwd, Str * ext_c_path);
Str * escape_doc_for_literal_str(Str * raw);
Str * func_kind(FuncType * ft);
Str * til_type_user(Type * t);
void append_packed_entry(Str * packed, Str * name, Str * value);
void append_qualifier_prefix(Str * out, Declaration * d, OwnType * default_own);
void append_fn_signature(Str * out, FunctionDef * fd);
void append_doc_lines_indented(Str * out, Str * doc, Str * indent);
void append_field_indented(Str * out, Declaration * d);
void append_ns_method_indented(Str * out, Declaration * d);
Str * format_var_info(Str * name, Declaration * dd, TypeScope * scope);
Str * format_func_info(Str * name, FunctionDef * fd);
Str * format_struct_info(Str * name, StructDef * sdef);
Str * format_enum_info(Str * name, EnumDef * edef);
Str * format_decl_info(Expr * stmt, TypeScope * scope);
void collect_member_method_packed(Str * type_name, Declaration * d, Str * info, Str * docs);
void collect_struct_members_packed(Str * type_name, StructDef * sdef, Str * info, Str * docs);
void collect_enum_members_packed(Str * type_name, EnumDef * edef, Str * info, Str * docs);
void collect_decl_packed(Expr * body, TypeScope * scope, Str * info, Str * docs);
Str * build_doc_init_line(Str * packed_info, Str * packed_docs);
void loaded_add_lflag(LoadedProgram * lp, Str * lib);
void init_and_type_program(LoadedProgram * lp, Bool run_tests);
void prepare_program(LoadedProgram * lp, Bool run_tests);
void cmd_ast(LoadedProgram * lp);
I32 system_cmd(Str * cmd);
CollectionInfo * CollectionInfo_clone(CollectionInfo * self);
void CollectionInfo_delete(CollectionInfo * self, Bool * call_free);
U32 CollectionInfo_size(void);
DynCallInfo * DynCallInfo_clone(DynCallInfo * self);
void DynCallInfo_delete(DynCallInfo * self, Bool * call_free);
U32 DynCallInfo_size(void);
LoadedProgram * codegen_lp(void);
void codegen_set_lp(LoadedProgram * lp);
void codegen_clear_lp(void);
Bool is_dyn_call_name(Str * name, Bool * has_ret);
Expr * resolve_local_fn_sig(Str * name);
Expr * resolve_decl_fn_sig(Expr * rhs, Declaration * dd, TypeScope * scope);
Expr * fcall_fn_sig(Expr * fcall);
Bool is_stack_local(Str * name);
Bool is_current_func_param(Str * name);
Bool is_value_global(Str * name);
Bool is_ref_global(Str * name);
Bool is_ref_local(Str * name);
Bool use_dot_access(Expr * obj);
Bool is_primitive_type(Str * name);
Bool is_funcsig_type(Str * name);
Bool is_ext_h_type(Str * name);
Bool is_skip_ext_decl(Str * name);
Bool is_exported_top_level_global(Expr * stmt);
Expr * find_struct_def(Str * name);
Expr * find_callee_fdef(Str * name);
Str * fa_struct_name(Expr * e);
Bool builder_fa_is_ptr_with_fname(Str * sname, Str * fname);
Bool builder_fa_is_ptr(Expr * e);
Bool builder_fa_is_ns_with_fname(Expr * e, Str * sname, Str * fname);
Bool builder_fa_is_ns(Expr * e);
Bool is_shallow_param(Str * name);
Bool callee_returns_shallow(Str * callee_name);
Bool callee_returns_dynamic(Str * callee_name);
Bool callee_param_is_shallow(Str * callee_name, U32 arg_index);
Bool callee_param_is_usize(Str * callee_name, U32 arg_index);
Bool callee_param_is_uptr(Str * callee_name, U32 arg_index);
Bool callee_param_is_own(Str * callee_name, U32 arg_index);
Bool fcall_is_shallow_return(Expr * fcall);
Bool fcall_returns_dynamic(Expr * fcall);
Str * til_type_to_c(Type t);
Str * extern_decl_ctype(Type t, Type rhs_t);
Str * resolve_decl_ctype(Type t, Type rhs_t, Str * explicit);
Str * c_type_name(Type t, Str * struct_name);
Str * func_to_c(Str * name);
Str * type_name_to_c(Str * name);
Str * type_name_to_c_value(Str * name);
void emit_u64(File * f, U64 v);
void emit_i32(File * f, I32 v);
void emit_indent(File * f, I32 depth);
U32 * c_lit_byte_count(Str * s);
Bool rhs_is_pure_byvalue_for_emit(Expr * e);
void emit_til_default(File * f, Type t);
Str * callee_return_ctype(Str * callee_name);
Str * param_ctype(FunctionDef * fd, U32 i);
void emit_param_list(File * f, Expr * fdef, Bool with_names);
void collect_dyn_methods(Expr * e, Vec * methods);
void collect_collection_builtins(Expr * e, Vec * infos);
void emit_field(File * f, Str * var, Str * field);
Str * get_stack_local_ctype(Str * name);
Str * resolve_ident_ctype(Str * ident, Type * ttype, Str * sname);
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
void emit_str_lit_expr(File * f, Str * s);
void emit_expr(File * f, Expr * e, I32 depth);
void emit_body(File * f, Expr * body, I32 depth);
void emit_ctor_fields(File * f, Str * var, Expr * ctor, I32 depth);
void emit_ns_inits(File * f, I32 depth);
void emit_body_scoped(File * f, Expr * body, I32 depth);
void emit_deref(File * f, Expr * e, I32 depth);
void emit_as_ptr(File * f, Expr * e, I32 depth, Bool is_own);
void emit_usize_ref(File * f, Expr * e, I32 depth);
void emit_uptr_ref(File * f, Expr * e, I32 depth);
void emit_cli_parse_arg(File * f, Str * pname, Str * ptype, I32 argi);
void emit_func_def(File * f, Str * name, Expr * func_def, Mode * mode, Bool is_static);
void emit_struct_typedef(File * f, Str * name, Expr * struct_def);
void emit_ns_method(File * f, Str * name, Str * dd_name, Expr * fdef);
void emit_struct_funcs(File * f, Str * name, Expr * struct_def);
void emit_enum_def(File * f, Str * name, Expr * enum_def);
void emit_enum_struct_body(File * f, Str * ename, Expr * enum_def);
void topo_emit_struct_enum_defs_lp(File * f, Set * emitted);
Str * func_return_ctype(FunctionDef * fd);
void emit_func_forward_decl(File * f, Str * name, Expr * fdef);
void emit_funcsig_typedef(File * f, Str * name, Expr * fdef);
void emit_funcsig_typedefs_lp(File * f);
void emit_header_forward_decls_lp(File * f);
void emit_header_defs_and_funcs_lp(File * f);
void emit_header_global_decls_lp(File * f);
I32 build_forward_header_lp(Str * fwd_path);
I32 build_header_lp(Str * h_path);
Bool emit_binding_ns_method(File * f, Str * fdd_name, FunctionDef * fd, Bool * has_ns);
void emit_binding_ns_methods(File * f, Expr * def);
I32 build_til_binding(Expr * program, Str * til_path, Str * lib_name);
Str * type_name_to_ctypes(Str * name);
Str * type_name_to_ctypes_param(Str * name, Bool is_shallow);
Str * type_name_to_ctypes_return(Str * name, Bool is_shallow);
I32 build_python_binding(Expr * program, Str * py_path, Str * lib_name);
I32 compile_lib(Str * c_path, Str * lib_name, Str * ext_c_path, Str * user_c_path, Str * link_flags, Str * include_flags, Target * target, Str * cc_override);
I32 compile_c(Str * c_path, Str * bin_path, Str * ext_c_path, Str * user_c_path, Str * link_flags, Str * include_flags, Target * target, Str * cc_override, Str * mode_auto_import);
void register_funcsig_prog(Expr * prog);
void emit_global_inits_prog(File * f, Expr * prog);
void emit_global_inits(File * f);
void build_register_funcsig_names_lp(void);
void register_lookups_prog(Expr * prog);
void build_register_lookups_lp(void);
void emit_monolithic_header_lp(File * f, Mode * mode);
void emit_all_forward_declarations(File * f, Mode * mode);
void emit_dyn_fn_wrapper(File * f, Str * type_name, Str * method_name, FunctionDef * fd);
void emit_dyn_fn_wrappers(File * f);
void emit_dyn_size_of_body(File * f);
void emit_tag_case(File * f, Str * tag, Str * name);
void emit_dyn_type_to_str_body(File * f);
void emit_dyn_call_bodies(File * f);
void emit_dyn_has_bodies(File * f);
void emit_collection_helpers(File * f);
void emit_global_declarations(File * f);
void emit_test_main(File * f, LoadedProgram * lp);
void emit_script_main(File * f);
void emit_function_bodies(File * f, Mode * mode);
void emit_ext_func_declarations(File * f, Expr * program);
void emit_lib_init(File * f);
I32 build(Mode * mode, Bool run_tests, Str * c_output_path);
BuildPaths * BuildPaths_clone(BuildPaths * self);
void BuildPaths_delete(BuildPaths * self, Bool * call_free);
U32 BuildPaths_size(void);
BuildPaths * derive_build_paths(LoadedProgram * lp, Str * custom_bin, Str * custom_c, Target * target);
void make_build_dirs(BuildPaths * paths);
I32 translate_ast(LoadedProgram * lp, BuildPaths * paths);
void print_translate_success(BuildPaths * paths);
I32 compile_ast(LoadedProgram * lp, BuildPaths * paths, Target * target, Str * cc_override);
I32 cmd_translate(LoadedProgram * lp, Str * custom_c, Target * target);
I32 cmd_build(LoadedProgram * lp, Str * custom_bin, Str * custom_c, Target * target, Str * cc_override);
I32 check_install_rc(I32 * rc, Str * what);
Str * builder_compiler_root(LoadedProgram * lp);
Str * support_root(Str * prefix);
I32 install_file(Str * src, Str * dst, Str * what);
I32 install_tree(Str * src, Str * dst, Str * what);
Bool is_compiler_install(LoadedProgram * lp, BuildPaths * paths);
I32 install_compiler_support(LoadedProgram * lp, Str * prefix);
void print_install_success(Str * path);
I32 cmd_install(LoadedProgram * lp, Str * install_prefix_in, Target * target, Str * cc_override);
I32 cmd_run(LoadedProgram * lp, Str * custom_bin, Str * custom_c, Vec * user_argv, Target * target, Str * cc_override);
I32 cmd_test_build_run(LoadedProgram * lp, Str * custom_bin, Str * custom_c, Target * target, Str * cc_override);
Str * format_unit_doc_org(Str * unit_path, Expr * ast, TypeScope * scope);
Str * til_doc_out_path(Str * unit_path);
void ensure_parent_dir(Str * path);
void emit_unit_doc(ProgramUnit * u, LoadedProgram * lp);
I32 cmd_doc(LoadedProgram * lp);
I32 system_cmd(Str * cmd);
void interp_error(Expr * e, Str * msg);
void interp_lang_error(Expr * e, Str * msg);
Str * StructInstance_to_str(StructInstance * self);
StructInstance * StructInstance_clone(StructInstance * self);
void StructInstance_delete(StructInstance * self, Bool * call_free);
U32 StructInstance_size(void);
EnumInstance * EnumInstance_clone(EnumInstance * self);
void EnumInstance_delete(EnumInstance * self, Bool * call_free);
U32 EnumInstance_size(void);
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
Expr * lookup_interp_type_def(Str * name);
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
void resolve_ptr_to_struct(Value * obj, Scope * scope, Str * obj_sname);
Value eval_expr(Scope * scope, Expr * e);
Value * reinterpret_ptr_value(Value * val, Str * type_name, Scope * scope);
Bool guard_own_param_skip(Scope * scope, Expr * e, Expr * func_def);
void * resolve_field_assign_base(Scope * scope, Expr * obj_expr);
Expr * resolve_field_assign_sdef(Scope * scope, Expr * obj_expr);
void eval_body(Scope * scope, Expr * body);
Value eval_call(Scope * scope, Expr * e);
void free_value(Value v);
void cleanup_value_payload(Value v);
Bool needs_widen(Value * val, Str * ptype);
Value shallow_copy_value(Value * v);
Value make_struct_value(Str * sname, Expr * sdef, void * data, Bool borrowed);
Value * widen_numeric(Value * v, Str * ptype);
Cell * scope_get(Scope * s, Str * name);
Scope * scope_new(Scope * parent);
void scope_set_owned(Scope * s, Str * name, Value * val);
void scope_set_borrowed(Scope * s, Str * name, Cell * cell);
void free_expr_in_place(Expr * e);
void scope_free(Scope * s);
Bool interp_fa_is_ns_with_fname(Expr * obj_expr, Str * sname, Expr * sdef, Str * fname);
Bool interp_fa_is_ns_inner(Scope * scope, Expr * e, Str * sname);
Cell * field_assign_dyn_move_src(Scope * scope, Expr * val_expr);
Bool interp_fa_is_ns(Scope * scope, Expr * e);
void value_to_buf(void * dest, Value * val, Str * type_name);
Value build_argv_array(Vec * argv, U32 offset, U32 count, Str * elem_type);
void interpreter_init_ns(Context * ctx, Scope * global, Expr * program);
Str * ns_qname(Str * sname, Str * fname);
Value * ns_get(Str * sname, Str * fname);
void ns_set(Str * sname, Str * fname, Value val);
Value make_str_value(void * data, U64 len);
Value make_str_value_view(void * data, U64 len);
Value make_str_value_own(void * data, U64 len);
Str str_view(Value v);
Declaration * find_field_decl(Expr * struct_def, Str * fname);
Value read_field(StructInstance * inst, Declaration * dd);
void write_field(StructInstance * inst, Declaration * dd, Value * val);
void interpret_register_defs(Scope * global, Expr * prog);
void interpret_register_aliases(Scope * global, Expr * prog);
void interpret_copy_alias_ns(Expr * prog, Scope * global);
I32 interpret_units(LoadedProgram * lp, Vec * user_argv, Str * fwd_path);
I32 cmd_interpret(LoadedProgram * lp, Vec * user_argv);
ffi_type * ffi_type_clone(ffi_type * self);
void ffi_type_delete(ffi_type * self, Bool * call_free);
U32 ffi_type_size(void);
ffi_cif * ffi_cif_clone(ffi_cif * self);
void ffi_cif_delete(ffi_cif * self, Bool * call_free);
U32 ffi_cif_size(void);
I32 ffi_prep_cif(ffi_cif * cif, I32 abi, U32 nargs, ffi_type * rtype, void * atypes);
void ffi_call(ffi_cif * cif, void * fn, void * rvalue, void * avalue);
ExtStr * ExtStr_clone(ExtStr * self);
void ExtStr_delete(ExtStr * self, Bool * call_free);
U32 ExtStr_size(void);
FFIEntry * FFIEntry_clone(FFIEntry * self);
void FFIEntry_delete(FFIEntry * self, Bool * call_free);
U32 FFIEntry_size(void);
ExprPtrBox * ExprPtrBox_clone(ExprPtrBox * self);
void ExprPtrBox_delete(ExprPtrBox * self, Bool * call_free);
U32 ExprPtrBox_size(void);
FFITypePtrBox * FFITypePtrBox_clone(FFITypePtrBox * self);
void FFITypePtrBox_delete(FFITypePtrBox * self, Bool * call_free);
U32 FFITypePtrBox_size(void);
void ffi_reset(void);
ffi_type * ffi_type_pointer_ref(void);
ffi_type * ffi_type_sint64_ref(void);
ffi_type * ffi_type_uint8_ref(void);
ffi_type * ffi_type_sint16_ref(void);
ffi_type * ffi_type_sint32_ref(void);
ffi_type * ffi_type_uint32_ref(void);
ffi_type * ffi_type_uint64_ref(void);
ffi_type * ffi_type_float_ref(void);
ffi_type * ffi_type_void_ref(void);
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
void ffi_init_struct_defs_append(Expr * program);
U64 * value_to_u64(Value * v);
ffi_type * uptr_ffi_type(void);
ffi_type * usize_ffi_type(void);
F32 * value_to_f32(Value * v);
Str * value_variant_name(Value * v);
Bool * narrow_bool_arg(Scope * s, Expr * e);
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
Bool h_dyn_size_of(Scope * s, Expr * e, Value * r);
Bool h_dyn_type_to_str(Scope * s, Expr * e, Value * r);
Bool h_check_cmd_status(Scope * s, Expr * e, Value * r);
Bool h_sleep(Scope * s, Expr * e, Value * r);
Bool h_file_mtime(Scope * s, Expr * e, Value * r);
Bool h_clock_ms(Scope * _s, Expr * _e, Value * r);
Bool h_get_thread_count(Scope * _s, Expr * _e, Value * r);
Bool h_cfile_open(Scope * s, Expr * e, Value * r);
ffi_type * shallow_ffi_type(Str * type_name);
ffi_type * field_ffi_type(Declaration * dd);
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
Bool enum_method_dispatch(Str * method, Scope * scope, Expr * enum_def, Str * enum_name, Expr * e, Value * result);
Bool ffi_decode_scalar(Str * rtype, void * p, Value * result);
Expr * ffi_call_ret_struct_def(FFIEntry * fe);
Bool ffi_shallow_type_info(void * atype, Str * type_name, I32 * size);
Bool ffi_write_shallow_arg(Scope * scope, Value * v, void * atype, void * dst);
Bool ext_dispatch_ffi(Str * name, Scope * scope, Expr * e, Value * result);
Bool ext_function_dispatch(Str * name, Scope * scope, Expr * e, Value * result);
void ffi_register(Str * name, void * fn, Expr * fdef);
void ffi_init_scan_program(Expr * program);
I32 ffi_init(Expr * program, Str * fwd_path, Str * user_c_path, Str * ext_c_path, Str * link_flags);
void ffi_cleanup(void);
Str * get_bin_dir(void);
Str * get_cwd_str(void);
Str * repl_read_line(Str * mode_name);
I32 repl_typecheck(LoadedProgram * lp);
Bool * repl_should_wrap(Expr * peek_ast, Expr * typed_ast);
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
TokenType *TokenType_DocComment();
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
TokenType *TokenType_KwPriv();
TokenType *TokenType_Error();
Bool * ScopeFind_eq(ScopeFind *, ScopeFind *);
ScopeFind *ScopeFind_NotFound();
ScopeFind *ScopeFind_Found(TypeBinding *);
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
extern Str __til_docs_blob__;
extern Str __til_info_blob__;
extern Str initer_path;
extern Map core_modes;
extern I32 hoist_counter;
extern I32 va_counter;
extern I32 kw_counter;
extern I32 coll_counter;
extern I32 errors;
extern I32 proc_calls_count;
extern I32 proc_def_depth;
extern Str current_type_name;
extern Str current_top_func_name;
extern I32 auto_gen_depth;
extern Bool typer_in_shallow_return;
extern Str I64Name;
extern Str U8Name;
extern Str I16Name;
extern Str I32Name;
extern Str U32Name;
extern Str U64Name;
extern Str F32Name;
extern Str BoolName;
extern Str typer_path;
extern Set macros;
extern Set funcs;
extern Map known;
extern U8 MARK_DELETE;
extern U8 MARK_REPLACE_RHS;
extern void * codegen_lp_slot;
extern Bool in_func_def;
extern Bool in_main_func;
extern I32 ctor_seq;
extern Str interp_path;
extern Bool has_return;
extern Bool has_break;
extern Bool has_continue;
extern Value return_value;
extern Map ns_fields;
extern Vec ns_keys;
extern Map interp_type_defs;
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

