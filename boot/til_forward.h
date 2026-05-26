#pragma once
#include "ext.h"

typedef struct Vec Vec;
typedef struct Str Str;
typedef struct Dynamic Dynamic;
typedef struct Map Map;
typedef enum {
    Primitive_TAG_I16
} Primitive_tag;
typedef struct Primitive Primitive;
typedef enum {
    Type_TAG_Unknown,
    Type_TAG_None,
    Type_TAG_I64,
    Type_TAG_U8,
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
    Type_TAG_Custom,
    Type_TAG_I8,
    Type_TAG_Primitive
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
typedef struct LiteralNumData LiteralNumData;
typedef struct IdentData IdentData;
typedef struct FieldAccessData FieldAccessData;
typedef struct StructDef StructDef;
typedef struct EnumDef EnumDef;
typedef struct AssignData AssignData;
typedef struct FieldAssignData FieldAssignData;
typedef struct ForInData ForInData;
typedef enum {
    Literal_TAG_Str,
    Literal_TAG_Num,
    Literal_TAG_Bool,
    Literal_TAG_Null
} Literal_tag;
typedef struct Literal Literal;
typedef enum {
    NodeType_TAG_Body,
    NodeType_TAG_Literal,
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
    NodeType_TAG_Catch,
    NodeType_TAG_RestPattern
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
typedef struct priv___src_self_parser_til__Parser priv___src_self_parser_til__Parser;
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
typedef enum {
    priv___src_self_typer_til__CtorArg_TAG_Unfilled,
    priv___src_self_typer_til__CtorArg_TAG_Filled
} priv___src_self_typer_til__CtorArg_tag;
typedef struct priv___src_self_typer_til__CtorArg priv___src_self_typer_til__CtorArg;
typedef struct priv___src_self_typer_til__CoverageNode priv___src_self_typer_til__CoverageNode;
typedef struct priv___src_self_asaper_til__LocalInfo priv___src_self_asaper_til__LocalInfo;
typedef struct ProgramUnit ProgramUnit;
typedef struct LoadedProgram LoadedProgram;
typedef struct priv___src_self_loader_til__DeclRef priv___src_self_loader_til__DeclRef;
typedef struct priv___src_self_builder_til__CollectionInfo priv___src_self_builder_til__CollectionInfo;
typedef struct priv___src_self_builder_til__DynCallInfo priv___src_self_builder_til__DynCallInfo;
typedef struct priv___src_self_builder_til__BuildPaths priv___src_self_builder_til__BuildPaths;
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
    Value_TAG_Ref,
    Value_TAG_Dynamic
} Value_tag;
typedef struct Value Value;
typedef struct Cell Cell;
typedef struct Binding Binding;
typedef struct Scope Scope;
typedef struct priv___src_self_interpreter_til__DynPtrBox priv___src_self_interpreter_til__DynPtrBox;
typedef struct _ffi_type ffi_type;
typedef struct priv___src_self_dispatch_til__ExtStr priv___src_self_dispatch_til__ExtStr;
typedef struct FFIEntry FFIEntry;
typedef struct ExprPtrBox ExprPtrBox;
typedef struct FFITypePtrBox FFITypePtrBox;
typedef struct priv___src_self_binder_til__BinderState priv___src_self_binder_til__BinderState;
typedef struct Vector3 Vector3;
typedef struct Vector4 Vector4;
typedef struct Texture Texture;
typedef struct RenderTexture RenderTexture;
typedef struct Camera3D Camera3D;
typedef struct CliArgs CliArgs;

typedef void * (*CloneFn)(void *);
typedef void (*DeleteFn)(void *, Bool *);
typedef I64 * (*CmpFn)(void *, void *);
typedef Bool (*DispatchFn)(Scope *, Expr *, Value *, Context *);







typedef struct Vec {
    U8 *data;
    U32 count;
    U32 cap;
    U32 elem_size;
    U32 elem_kind;
    void * elem_clone;
    void * elem_delete;
} Vec;


typedef struct Str {
    I8 *c_str;
    U32 count;
    U32 cap;
} Str;


typedef struct Dynamic {
    char _;
} Dynamic;





typedef struct Map {
    Vec keys;
    Vec values;
    void * key_cmp;
} Map;


struct Primitive {
    Primitive_tag tag;
};

struct Type {
    Type_tag tag;
    union {
        Str Struct;
        Str Enum;
        Str Custom;
        Primitive Primitive;
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


typedef struct FunctionDef {
    FuncType func_type;
    Vec params;
    Str return_type;
    Vec throw_types;
    I32 variadic_index;
    I32 kwargs_index;
    OwnType return_own_type;
    Bool auto_generated;
    Bool is_enum_variant_ctor;
} FunctionDef;


typedef struct FCallData {
    I32 variadic_index;
    U32 variadic_count;
    I32 kwargs_index;
    U32 kwargs_count;
    Bool is_splat;
    Bool does_throw;
    Bool is_bang;
    U64 own_args;
    Type til_type;
} FCallData;


typedef struct LiteralNumData {
    Str text;
    Type til_type;
} LiteralNumData;


typedef struct IdentData {
    Str name;
    Type til_type;
} IdentData;


typedef struct FieldAccessData {
    Str name;
    Type til_type;
} FieldAccessData;


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


typedef struct AssignData {
    Str name;
    Bool save_old_delete;
} AssignData;


typedef struct FieldAssignData {
    Str name;
    Bool save_old_delete;
} FieldAssignData;


typedef struct ForInData {
    Str name;
    Bool is_mut;
    Type til_type;
} ForInData;


struct Literal {
    Literal_tag tag;
    union {
        Str Str;
        LiteralNumData Num;
        Bool Bool;
    } data;
};

struct NodeType {
    NodeType_tag tag;
    union {
        Literal Literal;
        IdentData Ident;
        Declaration Decl;
        AssignData Assign;
        FCallData FCall;
        FunctionDef FuncDef;
        StructDef StructDef;
        EnumDef EnumDef;
        FieldAccessData FieldAccess;
        FieldAssignData FieldAssign;
        ForInData ForIn;
        Str NamedArg;
    } data;
};

typedef struct Expr {
    NodeType node_type;
    Vec children;
    U32 line;
    U32 col;
} Expr;


typedef struct Array {
    U8 *data;
    U32 cap;
    U32 elem_size;
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


typedef struct priv___src_self_parser_til__Parser {
    Vec tokens;
    U32 pos;
    Str path;
    Vec fn_sig_decls;
    Str pending_doc;
} priv___src_self_parser_til__Parser;


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


struct Lang {
    Lang_tag tag;
};

struct Target {
    Target_tag tag;
};

struct priv___src_self_typer_til__CtorArg {
    priv___src_self_typer_til__CtorArg_tag tag;
    union {
        Expr Filled;
    } data;
};

typedef struct priv___src_self_typer_til__CoverageNode {
    Bool fully_covered;
    Vec sub_names;
    Vec sub_nodes;
} priv___src_self_typer_til__CoverageNode;


typedef struct priv___src_self_asaper_til__LocalInfo {
    Str *name;
    Type type;
    I32 decl_index;
    I32 last_use;
    I32 own_transfer;
    Bool skip_scope_delete;
    Bool is_heap;
} priv___src_self_asaper_til__LocalInfo;


typedef struct ProgramUnit {
    Str path;
    Mode mode;
    Vec imports;
} ProgramUnit;


typedef struct priv___src_self_loader_til__DeclRef {
    Str path;
    U32 idx;
} priv___src_self_loader_til__DeclRef;


typedef struct priv___src_self_builder_til__CollectionInfo {
    Str *type_name;
    I32 is_vec;
} priv___src_self_builder_til__CollectionInfo;


typedef struct priv___src_self_builder_til__DynCallInfo {
    Str *method;
    I32 nargs;
    Bool has_return;
} priv___src_self_builder_til__DynCallInfo;


typedef struct priv___src_self_builder_til__BuildPaths {
    Str name;
    Str c_path;
    Str bin_path;
    Str fwd_path;
    Str h_path;
    Str til_path;
    Str py_path;
    Bool do_lib;
} priv___src_self_builder_til__BuildPaths;


typedef struct StructInstance {
    Str *struct_name;
    Expr *struct_def;
    U8 *data;
    Bool borrowed;
} StructInstance;


typedef struct EnumInstance {
    Str *enum_name;
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
        void * Ref;
        void * Dynamic;
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


typedef struct priv___src_self_interpreter_til__DynPtrBox {
    U8 *p;
} priv___src_self_interpreter_til__DynPtrBox;


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
    ffi_type *rtype;
    U32 bytes;
    U32 flags;
} ffi_cif;


typedef struct priv___src_self_dispatch_til__ExtStr {
    U8 *data;
    U64 count;
    U64 cap;
} priv___src_self_dispatch_til__ExtStr;


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


typedef struct priv___src_self_binder_til__BinderState {
    Str alias_to_primitive;
    Str alias_to_dynamic;
} priv___src_self_binder_til__BinderState;


typedef struct Vector3 {
    F32 x;
    F32 y;
    F32 z;
} Vector3;


typedef struct Vector4 {
    F32 x;
    F32 y;
    F32 z;
    F32 w;
} Vector4;


typedef struct Texture {
    U32 id;
    I32 width;
    I32 height;
    I32 mipmaps;
    I32 format;
} Texture;


typedef struct RenderTexture {
    U32 id;
    Texture texture;
    Texture depth;
} RenderTexture;


typedef struct Camera3D {
    Vector3 position;
    Vector3 target;
    Vector3 up;
    F32 fovy;
    I32 projection;
} Camera3D;


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
    Bool asan;
} CliArgs;


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
    Set precomp_macros;
    Set precomp_funcs;
    Map precomp_known;
    Bool has_return;
    Bool has_break;
    Bool has_continue;
    Value return_value;
    Map ns_fields;
    Vec ns_keys;
    Bool ns_inited;
    Bool typing_namespace_member;
    Map local_fn_sigs;
    Map func_defs;
    Map struct_def_exprs;
    Set funcsig_names;
    Set script_globals;
    Set ref_globals;
    Vec throw_type_registry;
    Vec throws_names_global;
    Vec throws_per_global;
    I64 bang_counter;
    Bool typer_in_shallow_return;
    Bool typer_in_main_func;
    Str typer_return_type_name;
    I32 ctor_seq;
    Bool in_func_def;
    Bool in_main_func;
    I32 proc_calls_count;
    I32 proc_def_depth;
    I32 hoist_counter;
    I32 va_counter;
    I32 kw_counter;
    I32 coll_counter;
    I32 errors;
    Str current_type_name;
    Str current_top_func_name;
    I32 auto_gen_depth;
    Set throw_used_local_names;
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
    Map interp_type_defs;
    Map dispatch_map;
    Bool dispatch_inited;
    Map ffi_map;
    Bool ffi_map_inited;
    Bool ffi_loaded;
    Map ffi_struct_defs;
    Vec ffi_type_cache;
    Bool ffi_type_cache_inited;
} Context;


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
void I8_delete(I8 * self, Bool * call_free);
U32 * I8_size(void);
Bool I8_lt(I8 * a, I8 * b);
Bool I8_gt(I8 * a, I8 * b);
Bool I8_neq(I8 * a, I8 * b);
Bool I8_lte(I8 * a, I8 * b);
Bool I8_gte(I8 * a, I8 * b);
Str * U8_to_str(U8 * val);
void U8_delete(U8 * self, Bool * call_free);
U32 * U8_size(void);
Vec * Vec_new_type_name(Str * elem_type);
Vec * Vec_new(Type * T);
U32 Vec_len(Vec * self);
void Vec_clear(Vec * self);
void Vec_push(Vec * self, void * val);
void Vec_append(Vec * self, Vec * other);
void Vec_move_from(Vec * self, Vec * other);
void * Vec_get(Vec * self, U32 * i);
void * Vec_pop(Vec * self);
void Vec_set(Vec * self, U32 * i, void * val);
void Vec_replace(Vec * self, U32 * i, void * val);
void Vec_push_take(Vec * self, Vec * src, U32 i);
void Vec_delete(Vec * self, Bool * call_free);
Vec * Vec_clone(Vec * self);
U32 Vec_size(void);
Str * format(Array * parts);
U32 Str_len(Str * self);
I8 * Str_get(Str * self, U32 * i);
I8 * Str_byte_at(Str * self, U32 * i);
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
U32 c_str_len(I8 * s);
Str * priv___src_core_str_til__cli_view(I8 * s);
I64 * cli_parse_i64(I8 * s);
U8 * cli_parse_u8(I8 * s);
I8 * cli_parse_i8(I8 * s);
I16 * cli_parse_i16(I8 * s);
I32 * cli_parse_i32(I8 * s);
U32 * cli_parse_u32(I8 * s);
U64 * cli_parse_u64(I8 * s);
U64 * cli_parse_uptr(I8 * s);
Bool * cli_parse_bool(I8 * s);
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
void Map_clear(Map * self);
void * Map_key_ptr(Map * self, U32 * i);
void * Map_val_ptr(Map * self, U32 * i);
Bool Map_has(Map * self, void * key);
void * Map_get(Map * self, void * key);
void Map_set(Map * self, void * key, void * val);
void Map_delete(Map * self, Bool * call_free);
Map * Map_clone(Map * self);
U32 Map_size(void);
Bool Primitive_eq(Primitive * self, Primitive * other);
void Primitive_delete(Primitive * self, Bool * call_free);
Primitive * Primitive_clone(Primitive * self);
U32 Primitive_size(void);
Bool Type_eq(Type * a, Type * b);
Bool Type_is(Type * self, Type * other);
void Type_delete(Type * self, Bool * call_free);
Type * Type_clone(Type * self);
U32 Type_size(void);
Str * til_type_name_c(Type * t);
Str * til_type_name(Type * t);
Bool is_primitive(Type * t);
Bool is_aggregate(Type * t);
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
I64 LiteralNumData_to_i64(LiteralNumData * self);
U8 LiteralNumData_to_u8(LiteralNumData * self);
U64 LiteralNumData_to_u64(LiteralNumData * self);
F32 LiteralNumData_to_f32(LiteralNumData * self);
LiteralNumData * LiteralNumData_clone(LiteralNumData * self);
void LiteralNumData_delete(LiteralNumData * self, Bool * call_free);
U32 LiteralNumData_size(void);
U32 IdentData_len(IdentData * self);
Bool IdentData_starts_with(IdentData * self, Str * prefix);
Str * IdentData_concat(IdentData * self, Str * tail);
I8 * IdentData_byte_at(IdentData * self, U32 * i);
I8 * IdentData_get(IdentData * self, U32 * i);
IdentData * IdentData_clone(IdentData * self);
void IdentData_delete(IdentData * self, Bool * call_free);
U32 IdentData_size(void);
Bool FieldAccessData_starts_with(FieldAccessData * self, Str * prefix);
FieldAccessData * FieldAccessData_clone(FieldAccessData * self);
void FieldAccessData_delete(FieldAccessData * self, Bool * call_free);
U32 FieldAccessData_size(void);
Str * literal_num_text(LiteralNumData * n);
Str * ident_name(IdentData * id);
Str * field_access_name(FieldAccessData * fa);
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
FieldAssignData * FieldAssignData_clone(FieldAssignData * self);
void FieldAssignData_delete(FieldAssignData * self, Bool * call_free);
U32 FieldAssignData_size(void);
ForInData * ForInData_clone(ForInData * self);
void ForInData_delete(ForInData * self, Bool * call_free);
U32 ForInData_size(void);
void Literal_delete(Literal * self, Bool * call_free);
Literal * Literal_clone(Literal * self);
U32 Literal_size(void);
Bool NodeType_is_literal_str(NodeType * self);
Bool NodeType_is_literal_num(NodeType * self);
Bool NodeType_is_literal_bool(NodeType * self);
Bool NodeType_is_literal_null(NodeType * self);
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
NodeType * ident_node(Str * name);
NodeType * literal_num_node(Str * text);
NodeType * field_access_node(Str * name);
Type * expr_til_type(Expr * e);
void set_expr_til_type(Expr * e, Type t);
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
File * File_write(File * self, Str * s);
void File_close(File * self);
File * File_clone(File * self);
void File_delete(File * self, Bool * call_free);
U32 File_size(void);
Bool is_null(void * p);
void swap(void * a, void * b, U64 size);
void move(void * dest, void * src, U64 size);
Set * Set_new(Type * T);
U32 * Set_len(Set * self);
void Set_clear(Set * self);
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
Bool * is_digit(I8 * c);
Bool * is_alpha(I8 * c);
Bool * is_alnum(I8 * c);
Str * tok_name(TokenType * type);
TokenType priv___src_self_lexer_til__lookup_single_char(I8 * c);
TokenType lookup_two_char(I8 * c, I8 * c2);
TokenType * priv___src_self_lexer_til__lookup_keyword(Str * word);
Vec * tokenize(Str * src, Str * path);
priv___src_self_parser_til__Parser * priv___src_self_parser_til__Parser_clone(priv___src_self_parser_til__Parser * self);
void priv___src_self_parser_til__Parser_delete(priv___src_self_parser_til__Parser * self, Bool * call_free);
U32 priv___src_self_parser_til__Parser_size(void);
Token * priv___src_self_parser_til__peek(priv___src_self_parser_til__Parser * p);
Token * advance(priv___src_self_parser_til__Parser * p);
Bool check(priv___src_self_parser_til__Parser * p, TokenType * type);
Token * expect_token(priv___src_self_parser_til__Parser * p, TokenType * type);
Str * expect_text(priv___src_self_parser_til__Parser * p, TokenType * type);
U32 peek_line(priv___src_self_parser_til__Parser * p);
U32 peek_col(priv___src_self_parser_til__Parser * p);
Type * til_type_from_explicit_type(Str * name);
Str * priv___src_self_parser_til__parse_fn_signature(priv___src_self_parser_til__Parser * p, U32 line, U32 col);
Expr * priv___src_self_parser_til__parse_block(priv___src_self_parser_til__Parser * p);
Expr * parse_func_def(priv___src_self_parser_til__Parser * p);
Expr * parse_struct_def(priv___src_self_parser_til__Parser * p, Str * c_tag);
Expr * parse_enum_def(priv___src_self_parser_til__Parser * p);
Expr * parse_call(priv___src_self_parser_til__Parser * p, Str * name, U32 call_line, U32 call_col);
Expr * make_binop_call(Expr * lhs, Str * method, U32 op_line, U32 op_col, Expr * rhs);
Expr * parse_primary(priv___src_self_parser_til__Parser * p);
Expr * priv___src_self_parser_til__parse_multiplicative(priv___src_self_parser_til__Parser * p);
Expr * parse_additive(priv___src_self_parser_til__Parser * p);
Expr * parse_comparison(priv___src_self_parser_til__Parser * p);
Expr * parse_bitand(priv___src_self_parser_til__Parser * p);
Expr * parse_bitxor(priv___src_self_parser_til__Parser * p);
Expr * parse_bitor(priv___src_self_parser_til__Parser * p);
Expr * parse_expression(priv___src_self_parser_til__Parser * p);
Expr * parse_statement_ident(priv___src_self_parser_til__Parser * p, Bool is_mut, OwnType own_type);
void drain_doc_comments(priv___src_self_parser_til__Parser * p);
Expr * priv___src_self_parser_til__parse_statement(priv___src_self_parser_til__Parser * p);
Expr * parse_statement_body(priv___src_self_parser_til__Parser * p);
Expr * parse(Vec * tokens, Str * path, Str * mode_out);
TypeBinding * TypeBinding_clone(TypeBinding * self);
void TypeBinding_delete(TypeBinding * self, Bool * call_free);
U32 TypeBinding_size(void);
Str * priv_c_name(Str * path, Str * name);
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
I32 priv___src_self_initer_til__align_up(I32 offset, I32 align);
void precomp_classify_stmt(Expr * stmt, Context * ctx);
Expr * make_method_call_fcall(Expr * recv, Str * method, U32 line, U32 col);
Expr * make_get_payload_fcall(Expr * arg, Type payload_type, U32 line, U32 col);
Expr * make_is_tag_check_fcall(Str * arg_name, Str * ename, Str * vname, U32 line, U32 col);
Expr * make_payload_ref_decl(Expr * arg, Str * bind_name, Str * vtype, U32 line, U32 col);
Type * type_from_name_init(Str * name, TypeScope * scope);
Type * init_type_from_explicit_type(Str * name, TypeScope * scope);
I32 register_struct_def_for_stmt(Context * ctx, Expr * stmt, TypeScope * scope);
Str * priv___src_self_initer_til__field_inferred_type_name(Declaration * fd);
Bool priv___src_self_initer_til__is_pod_type_for_clone(Str * type_name, TypeScope * scope);
void gen_struct_clone_delete_for_stmt(Expr * stmt, TypeScope * scope);
I32 register_enum_definition(Context * ctx, Expr * stmt, TypeScope * scope);
void collect_enum_variants(Expr * enum_def, Vec * variant_names, Vec * variant_types, Bool * has_payloads);
void priv___src_self_initer_til__generate_enum_variant_constructors(Expr * enum_def, Str * ename, U32 line, U32 col, Vec * variant_names, Vec * variant_types, Bool has_payloads, TypeScope * scope);
void priv___src_self_initer_til__generate_enum_is_method(Expr * enum_def, Str * ename, U32 line, U32 col);
void generate_enum_eq_method(Expr * enum_def, Str * ename, U32 line, U32 col, Vec * variant_names, Vec * variant_types, TypeScope * scope);
void generate_enum_delete_method(Expr * enum_def, Str * ename, U32 line, U32 col, Vec * variant_names, Vec * variant_types, Bool has_payloads, TypeScope * scope);
void generate_enum_to_str_method(Expr * enum_def, Str * ename, U32 line, U32 col, Vec * variant_names, Vec * variant_types, Bool has_payloads, TypeScope * scope);
void generate_enum_clone_method(Expr * enum_def, Str * ename, U32 line, U32 col, Vec * variant_names, Vec * variant_types, Bool has_payloads, TypeScope * scope);
I32 register_enum_def_for_stmt(Context * ctx, Expr * stmt, TypeScope * scope);
void gen_enum_nonclone_methods_for_stmt(Expr * stmt, TypeScope * scope);
void gen_missing_enum_clone_for_stmt(Expr * stmt, TypeScope * scope);
void register_funcsig_alias_for_stmt(Context * ctx, Expr * stmt, TypeScope * scope);
void register_type_alias_for_stmt(Context * ctx, Expr * stmt, TypeScope * scope);
void register_top_level_value_for_stmt(Context * ctx, Expr * stmt, TypeScope * scope);
void register_function_def_for_stmt(Context * ctx, Expr * stmt, TypeScope * scope);
void gen_struct_size_method_for_stmt(Expr * stmt);
void gen_enum_size_method_for_stmt(Expr * stmt, TypeScope * scope);
void gen_unity_derived_for_stmt(Expr * stmt);
void gen_cmp_derived_for_stmt(Expr * stmt);
void compute_struct_layout(Expr * struct_def, TypeScope * scope);
void type_size_align(Str * ftype, TypeScope * scope, I32 * sz, I32 * al);
I32 compute_enum_layout(Expr * enum_def, TypeScope * scope);
void resolve_field_struct_defs(Expr * program, TypeScope * scope);
Bool infer_top_level_decl_type(Expr * stmt, TypeScope * scope, Type * out_type);
Bool priv___src_self_initer_til__init_is_lift_target(Expr * stmt);
Str * priv___src_self_initer_til__init_lookup_name(Map * renamings, Str * name);
void priv___src_self_initer_til__init_rename_ident_in_place(Expr * e, Map * renamings);
void priv___src_self_initer_til__init_rename_decl_in_place(Declaration * dd, Map * renamings);
void priv___src_self_initer_til__init_rewrite_refs(Expr * e, Map * renamings);
void priv___src_self_initer_til__init_lift_in_body(Expr * body, Str * parent_prefix, Vec * top_level);
void priv___src_self_initer_til__init_lift_in_ns_decls(Expr * def, Str * parent_prefix, Vec * top_level);
void priv___src_self_initer_til__init_recurse_into_subbodies(Expr * body, Str * parent_prefix, Vec * top_level);
void priv___src_self_initer_til__init_recurse_into_expr(Expr * e, Str * parent_prefix, Vec * top_level);
I32 init_declarations_unit(Str * path, Expr * program, TypeScope * scope, Context * ctx);
I32 init_declarations_global(Context * ctx, Expr * program, TypeScope * scope);
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
Str * priv___src_self_targets_til__lang_to_str(Lang * lang);
Bool Target_is(Target * self, Target * other);
Bool Target_eq(Target * self, Target * other);
void Target_delete(Target * self, Bool * call_free);
Target * Target_clone(Target * self);
U32 Target_size(void);
Target * target_from_str(Str * s);
Str * priv___src_self_targets_til__target_to_str(Target * target);
Bool * priv___src_self_targets_til__target_is_32bit(Target * target);
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
void free_expr_slot_in_place(Expr * e);
priv___src_self_typer_til__CtorArg * priv___src_self_typer_til__CtorArg_Unfilled(void);
priv___src_self_typer_til__CtorArg * priv___src_self_typer_til__CtorArg_Filled(Expr * val);
Bool priv___src_self_typer_til__CtorArg_is(priv___src_self_typer_til__CtorArg * self, priv___src_self_typer_til__CtorArg * other);
void priv___src_self_typer_til__CtorArg_delete(priv___src_self_typer_til__CtorArg * self, Bool * call_free);
priv___src_self_typer_til__CtorArg * priv___src_self_typer_til__CtorArg_clone(priv___src_self_typer_til__CtorArg * self);
U32 priv___src_self_typer_til__CtorArg_size(void);
priv___src_self_typer_til__CoverageNode * priv___src_self_typer_til__CoverageNode_clone(priv___src_self_typer_til__CoverageNode * self);
void priv___src_self_typer_til__CoverageNode_delete(priv___src_self_typer_til__CoverageNode * self, Bool * call_free);
U32 priv___src_self_typer_til__CoverageNode_size(void);
void priv___src_self_typer_til__init_coverage_for_enum(priv___src_self_typer_til__CoverageNode * node, Expr * enum_def);
I32 priv___src_self_typer_til__coverage_sub_index(priv___src_self_typer_til__CoverageNode * coverage, Str * variant_name);
Bool priv___src_self_typer_til__is_pattern_covered(TypeScope * scope, priv___src_self_typer_til__CoverageNode * coverage, Str * expected_type_name, Expr * pattern);
void priv___src_self_typer_til__mark_pattern_coverage(TypeScope * scope, priv___src_self_typer_til__CoverageNode * coverage, Str * expected_type_name, Expr * pattern);
void priv___src_self_typer_til__collect_missing_paths(TypeScope * scope, priv___src_self_typer_til__CoverageNode * coverage, Expr * enum_def, Str * prefix, Vec * out, Context * ctx);
void type_error(Expr * e, Str * msg, Context * ctx);
void type_error_at(Str * path, U32 line, U32 col, Str * msg, Context * ctx);
Expr * find_namespace_func(Expr * sdef, Str * method);
Bool expr_is_comptime(Expr * e, TypeScope * scope);
Bool namespace_member_is_priv(Expr * sdef, Str * method);
Bool mark_ns_member_used(Expr * sdef, Str * method);
Bool try_ufcs_rewrite(TypeScope * scope, Expr * e, Expr * fa, Expr * obj, Str * method, Str * type_name, Context * ctx);
Expr * resolve_fn_sig(Expr * fcall, TypeScope * scope);
Bool fcall_returns_own(Expr * fcall, TypeScope * scope);
void check_ref_decl_owned_init(Expr * stmt, TypeScope * scope, Context * ctx);
void check_ref_field_owned_default(Declaration * fd, TypeScope * scope, Context * ctx);
void check_ref_assign_owned_rhs(Expr * stmt, Str * target_name, Expr * rhs, TypeScope * scope, Context * ctx);
void check_ref_local_null_init(Expr * stmt, Context * ctx);
Bool infer_func_ptr_field_call(TypeScope * scope, Expr * e, Expr * fa, Expr * obj, Expr * sdef, Str * method, I32 in_func, Context * ctx);
Bool is_clone_fcall(Expr * e);
void validate_fcall_own_args(TypeScope * scope, Expr * e, TypeBinding * callee_bind, Context * ctx);
Bool infer_struct_constructor_fcall(TypeScope * scope, Expr * e, Str * name, I32 in_func, Context * ctx);
void desugar_user_func_fcall_args(Expr * e, Str * name, TypeBinding * callee_bind, Context * ctx);
Bool redundant_literal_conversion(Expr * e, Type * expected);
void redundant_conversion_error(Expr * at, Type * expected, Context * ctx);
void validate_fcall_arg(Expr * arg, Type * ptype, Str * ptype_name, Str * param_name, Context * ctx);
void infer_and_validate_fcall_args(TypeScope * scope, Expr * e, TypeBinding * callee_bind, I32 in_func, Context * ctx);
void resolve_fcall_return_type(TypeScope * scope, Expr * e, Str * name, TypeBinding * callee_bind, I32 in_func, Context * ctx);
Bool is_self_conversion_method(Str * method, Str * type_name);
Str * obj_method_type_name(Expr * obj);
Bool infer_field_access_fcall(TypeScope * scope, Expr * e, I32 in_func, Context * ctx);
void priv___src_self_typer_til__check_priv_access(Expr * e, Str * name, TypeBinding * b, Context * ctx);
void priv___src_self_typer_til__check_priv_type_name(Expr * e, Str * name, TypeScope * scope, Context * ctx);
void check_member_priv(Expr * e, Str * owner_name, Str * member_name, Bool * member_is_priv, Context * ctx);
void infer_fcall_expr(TypeScope * scope, Expr * e, I32 in_func, Context * ctx);
void priv___src_self_typer_til__infer_expr(TypeScope * scope, Expr * expr, I32 in_func, Context * ctx);
void infer_ident_expr(TypeScope * scope, Expr * expr, Context * ctx);
void infer_named_arg_expr(TypeScope * scope, Expr * expr, I32 in_func, Context * ctx);
void infer_map_lit_expr(TypeScope * scope, Expr * expr, I32 in_func, Context * ctx);
void infer_set_lit_expr(TypeScope * scope, Expr * expr, I32 in_func, Context * ctx);
Bool priv___src_self_typer_til__expr_uses_self_field(Expr * e, Str * field_name);
void priv___src_self_typer_til__check_user_delete_frees_own_fields(Str * struct_name, Expr * sdef, Context * ctx);
void infer_type_def_expr(TypeScope * scope, Expr * expr, Context * ctx);
void infer_func_sig_expr(TypeScope * scope, Expr * expr);
void check_ref_function_returns(TypeScope * func_scope, Expr * expr, Context * ctx);
void infer_func_def_expr(TypeScope * scope, Expr * expr, Context * ctx);
void check_unused_params(TypeScope * func_scope, Expr * expr, Context * ctx);
void check_unused_locals(TypeScope * scope, Str * path, Context * ctx);
I32 check_unused_priv_top_level(TypeScope * scope, Context * ctx);
I32 check_unused_priv_members_in_program(Expr * program, Str * path, Context * ctx);
void narrow_return_literal(TypeScope * scope, Expr * rv, Context * ctx);
void infer_return_stmt(TypeScope * scope, Expr * stmt, I32 in_func, I32 returns_ref, Context * ctx);
void infer_if_stmt(TypeScope * scope, Expr * stmt, I32 in_func, I32 in_loop, I32 returns_ref, Context * ctx);
void infer_field_access_expr(TypeScope * scope, Expr * expr, I32 in_func, Context * ctx);
void infer_field_assign_stmt(TypeScope * scope, Expr * stmt, I32 in_func, Context * ctx);
void infer_while_stmt(TypeScope * scope, Expr * stmt, I32 in_func, I32 returns_ref, Context * ctx);
Bool infer_decl_type_def(TypeScope * scope, Expr * stmt, Context * ctx);
Bool infer_decl_func_def(TypeScope * scope, Expr * stmt, Context * ctx);
Bool infer_decl_type_alias_passthrough(TypeScope * scope, Expr * stmt);
Type * declared_type_for_decl(TypeScope * scope, Expr * stmt, Context * ctx);
void pre_coerce_decl_numeric_literals(Expr * expr, Type * target);
void infer_decl_typed_value(TypeScope * scope, Expr * stmt, Context * ctx);
void infer_decl_untyped_value(Expr * stmt, Context * ctx);
void finalize_decl_binding(TypeScope * scope, Expr * stmt, I32 in_type_body, Context * ctx);
void infer_decl_stmt(TypeScope * scope, Expr * stmt, I32 in_func, I32 in_type_body, Context * ctx);
Bool is_simple_lvalue_expr(Expr * e);
Expr * priv___src_self_typer_til__fold_and_chain(Vec * conds, U32 line, U32 col);
Expr * make_switch_case_condition(TypeScope * scope, Expr * case_body, Expr * match_expr, Expr * sw_ref, U32 sw_line, U32 sw_col);
void replace_switch_stmt_with_block(Expr * body, U32 stmt_idx, Expr * block);
void append_switch_else_if(Expr * root_if, Expr * if_node);
void attach_switch_default_body(Expr * root_if, Expr * default_body);
void priv___src_self_typer_til__validate_struct_pattern_rest(TypeScope * scope, Expr * pattern, Context * ctx);
void infer_switch_stmt(TypeScope * scope, Expr * body, U32 stmt_idx, I32 in_func, Context * ctx);
void replace_body_stmt_with_block(Expr * body, U32 stmt_idx, Expr * block);
Expr * make_for_in_range_while_body(Str * var_name, Str * cur_name, Str * step, Expr * for_body, U32 line, U32 col, Str * elem_type, Bool var_is_mut);
Bool desugar_for_in_range_stmt(TypeScope * scope, Expr * body, U32 stmt_idx, I32 in_func, Context * ctx);
Bool desugar_for_in_collection_stmt(TypeScope * scope, Expr * body, U32 stmt_idx, I32 in_func, Context * ctx);
Str * priv___src_self_typer_til__guess_local_type(Expr * e, Str * var_name);
Str * priv___src_self_typer_til__guess_prior_local_type_in_vec(Vec * stmts, U32 upto, Str * var_name);
void priv___src_self_typer_til__collect_throw_ident_names(Expr * e, Set * names);
void priv___src_self_typer_til__annotate_throw_ident_expr_types(Expr * e, Expr * root_body);
Bool priv___src_self_typer_til__subtree_has_throw_type(Expr * e, Expr * root_body, Str * type_name);
Bool priv___src_self_typer_til__has_prior_throw_type_in_vec(Vec * stmts, Expr * root_body, U32 upto, Str * type_name);
Str * priv___src_self_typer_til__throw_type_name_for_with_body(Expr * e, Expr * body);
Bool priv___src_self_typer_til__subtree_has_throw_catch(Expr * e);
Bool priv___src_self_typer_til__subtree_has_bang(Expr * e);
void priv___src_self_typer_til__annotate_throw_types_in(Expr * e, Expr * root_body);
Str * priv___src_self_typer_til__err_slot_name(Str * t);
Expr * priv___src_self_typer_til__make_int_lit(I64 n, U32 line, U32 col);
Expr * priv___src_self_typer_til__make_typed_mut_decl(Str * name, Str * type_name, Expr * init, U32 line, U32 col);
Expr * priv___src_self_typer_til__make_assign_stmt(Str * name, Expr * rhs, U32 line, U32 col);
Expr * priv___src_self_typer_til__make_default_value_expr(Str * type_name, U32 line, U32 col);
I64 * priv___src_self_typer_til__tag_for_type(Context * ctx, Str * type_name, Vec * _type_to_tag_names);
void priv___src_self_typer_til__register_throw_type(Context * ctx, Str * name);
Expr * priv___src_self_typer_til__make_if_kind_eq_zero_wrap(Expr * stmt, U32 line, U32 col);
void priv___src_self_typer_til__rewrite_ident(Expr * e, Str * old_name, Str * new_name);
Expr * priv___src_self_typer_til__lower_catch_node(Context * ctx, Expr * catch_node, Vec * type_to_tag_names);
void priv___src_self_typer_til__register_func_throws(Context * ctx, Str * name, Vec * throws_list);
void extend_throwing_func_sigs(Context * ctx, Expr * e);
void priv___src_self_typer_til__clear_bang_flag(Expr * e);
Str * priv___src_self_typer_til__find_bang_callee_name(Expr * e);
I64 * priv___src_self_typer_til__find_callee_throws_idx(Context * ctx, Expr * fcall);
Bool priv___src_self_typer_til__pending_remove_all_matching(Vec * pending, Str * type_name);
Bool priv___src_self_typer_til__vec_str_contains(Vec * v, Str * name);
void priv___src_self_typer_til__vec_str_push_uniq(Vec * v, Str * name);
void priv___src_self_typer_til__validate_one_fcall_consolidated(Context * ctx, Expr * e, Vec * pending, Vec * seen, Vec * types_to_declare, Str * path);
void priv___src_self_typer_til__inject_err_args_on_one_fcall_consolidated(Context * ctx, Expr * e);
void priv___src_self_typer_til__validate_and_inject_expr_consolidated(Context * ctx, Expr * e, Vec * pending, Vec * seen, Vec * types_to_declare, Str * path);
Expr * priv___src_self_typer_til__build_bang_lowered(Context * ctx, Str * error_type, U32 line, U32 col);
void priv___src_self_typer_til__hoist_walk_consolidated(Context * ctx, Expr * parent, U32 * child_idx, Vec * pre_stmts, Vec * types_to_declare, Vec * seen);
void priv___src_self_typer_til__hoist_nested_bangs_consolidated(Context * ctx, Expr * stmt, Vec * pre_stmts, Vec * types_to_declare, Vec * seen);
void priv___src_self_typer_til__process_throw_catch_in_body(Context * ctx, Expr * body, Expr * root_body, Vec * fdef_throws, Vec * pending, Vec * seen, Vec * types_to_declare, Str * path);
void process_throw_catch_in_func_body(Context * ctx, Expr * body, Vec * fdef_throws, Str * return_type);
Bool is_compile_directive(Expr * e);
void infer_body_stmt(TypeScope * scope, Expr * body, U32 * i, I32 in_func, I32 in_loop, I32 returns_ref, I32 in_type_body, Context * ctx);
void reregister_scope_defs(Expr * body, TypeScope * scope);
void reregister_field_struct_defs(Expr * body, TypeScope * scope);
void infer_body(TypeScope * scope, Expr * body, I32 in_func, I32 owns_scope, I32 in_loop, I32 returns_ref, I32 in_type_body, Context * ctx);
void infer_body_unit(TypeScope * scope, Expr * body, I32 in_func, I32 owns_scope, I32 in_loop, I32 returns_ref, I32 in_type_body, Context * ctx);
void normalize_scope_bindings(TypeScope * scope);
Bool priv___src_self_typer_til__typer_is_lambda_target(Expr * e);
I64 * priv___src_self_typer_til__typer_lift_one_default_value(Declaration * dd, Vec * top_level, I64 * counter);
I64 * priv___src_self_typer_til__typer_lift_lambdas_in_expr(Expr * e, Vec * top_level, I64 * counter);
void priv___src_self_typer_til__typer_register_lifted_lambda(TypeScope * scope, Expr * lifted, Context * ctx);
void priv___src_self_typer_til__typer_lift_lambdas(TypeScope * scope, Expr * prog, Context * ctx);
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
Type * type_from_name_at(Str * name, TypeScope * scope, Expr * e, Context * ctx);
Type * type_from_name(Str * name, TypeScope * scope, Context * ctx);
Str * resolve_type_alias(TypeScope * scope, Str * name);
Str * usize_name(TypeScope * scope);
Type * usize_type(TypeScope * scope, Context * ctx);
Bool type_has_cmp(TypeScope * scope, Str * type_name);
Bool type_has_to_str(TypeScope * scope, Str * type_name);
Bool expr_contains_fcall(Expr * e);
Bool expr_uses_var(Expr * e, Str * name);
Bool expr_contains_decl(Expr * e, Str * name);
Bool expr_used_in_nested_func(Expr * e, Str * name);
Expr * priv___src_self_typer_til__find_variadic_fcall(Expr * e);
Expr * find_kwargs_fcall(Expr * e);
Expr * find_array_vec_fcall(Expr * e);
Str * type_prefix(Type * t);
Str * type_to_name(Type * t);
Expr * make_delete_call(Str * var_name, Type type, Bool arg_is_own, Bool call_free, Expr * src);
Bool transfer_is_shallow_field_value_copy(Expr * e, Str * var_name, TypeScope * scope);
Expr * make_free_call(Str * var_name, Type type, Expr * src);
Expr * make_clone_call(Str * type_name, Type type, Expr * arg, Expr * src);
Expr * make_to_str_call(Str * type_name, Expr * arg);
Expr * make_ns_call(Str * sname, Str * method, Type ret_type, Expr * src);
void sync_own_args_from_callee(Expr * call, TypeScope * scope);
Expr * build_kwargs_dynmap_decl(Expr * fcall, Str * kw_name);
Expr * build_kwargs_dynmap_set(Expr * fcall, TypeScope * scope, Str * kw_name, Expr * named_arg, Context * ctx);
Expr * build_variadic_array_decl(Expr * fcall, TypeScope * scope, Str * elem_type, Str * va_name, U32 vc, Context * ctx);
Expr * build_variadic_array_set(Expr * fcall, TypeScope * scope, Str * va_name, I32 vi, U32 j, Context * ctx);
Expr * build_builtin_vec_decl(Expr * fcall, TypeScope * scope, Str * elem_type, Str * vec_name, Context * ctx);
Expr * build_builtin_vec_push(Expr * fcall, TypeScope * scope, Str * vec_name, U32 j);
void rewrite_collection_fcall_to_ident(Expr * fcall, Str * coll_name, Type * coll_type);
Bool desugar_array_vec_fcall(Context * ctx, Expr * fcall, Vec * new_ch, TypeScope * scope);
Bool desugar_array_vec_decl(Expr * stmt, Vec * new_ch, TypeScope * scope, Context * ctx);
Bool desugar_set_literal_decl(Expr * stmt, Vec * new_ch, TypeScope * scope, Context * ctx);
Bool desugar_map_literal_decl(Expr * stmt, Vec * new_ch, TypeScope * scope, Context * ctx);
void process_call_desugars(Context * ctx, Expr * e, Vec * new_ch, TypeScope * scope, Bool has_array_vec, Bool has_variadic, Bool has_kwargs);
Bool priv___src_self_typer_til__body_pre_passes(Context * ctx, Expr * body, TypeScope * scope, I32 owns_scope);
void apply_hoist_to_stmt(Context * ctx, Expr * stmt, Vec * new_ch, TypeScope * scope);
void apply_call_hoist_delete(Context * ctx, Expr * stmt, Vec * new_ch, TypeScope * scope, Bool has_array_vec, Bool has_variadic, Bool has_kwargs, Bool do_hoist, Bool needs_delete);
void hoist_param_swap_assign(Context * ctx, Expr * stmt, Vec * hoisted, TypeScope * scope);
Bool fcall_variant_ctor_arg_is_own(Expr * expr, U32 i, TypeScope * scope);
void hoist_expr(Context * ctx, Expr * expr, Vec * hoisted, TypeScope * scope);
void hoist_decl_rhs(Context * ctx, Expr * stmt, Vec * hoisted, TypeScope * scope);
void hoist_if_cond(Context * ctx, Expr * stmt, Vec * hoisted, TypeScope * scope);
void hoist_return_expr(Context * ctx, Expr * stmt, Vec * hoisted, TypeScope * scope);
void hoist_assign_rhs(Context * ctx, Expr * stmt, Vec * hoisted, TypeScope * scope);
void hoist_field_assign_rhs(Context * ctx, Expr * stmt, Vec * hoisted, TypeScope * scope);
void hoist_stmt_fcall(Context * ctx, Expr * stmt, Vec * hoisted, TypeScope * scope);
void rewrite_variadic_fcall_args(Expr * fcall, Str * va_name);
Str * resolve_variadic_elem_type(Expr * fcall, TypeScope * scope);
Bool desugar_pure_splat_variadic_call(Expr * fcall);
void rewrite_kwargs_fcall_args(Expr * fcall, Str * kw_name);
Bool check_own_args(Expr * fdef, Expr * fcall, Str * var_name);
Bool fcall_has_own_arg(Expr * fcall, Str * var_name, TypeScope * scope);
Bool expr_transfers_own(Expr * e, Str * var_name, TypeScope * scope, Context * ctx);
Bool expr_is_borrow_source(Expr * e, TypeScope * scope);
Bool expr_is_stable_field_base(Expr * e, TypeScope * scope);
Bool expr_is_ref_decl_source(Expr * e, TypeScope * scope);
Bool field_assign_needs_delete(Expr * stmt, TypeScope * scope);
void infer_literal_expr(Expr * expr);
void narrow_dynamic(Expr * expr, Type * target);
I32 fcall_returns_ref(Expr * fcall, TypeScope * scope);
I32 fcall_returns_shallow(Expr * fcall, TypeScope * scope);
Expr * hoist_to_temp(Context * ctx, Expr * val, Vec * hoisted, TypeScope * scope, Bool is_own);
priv___src_self_asaper_til__LocalInfo * priv___src_self_asaper_til__LocalInfo_clone(priv___src_self_asaper_til__LocalInfo * self);
void priv___src_self_asaper_til__LocalInfo_delete(priv___src_self_asaper_til__LocalInfo * self, Bool * call_free);
U32 priv___src_self_asaper_til__LocalInfo_size(void);
Bool alias_used_in_stmts(Vec * stmts, Str * name, Expr * expr);
void collect_scope_locals(Context * ctx, Expr * body, TypeScope * scope, Bool is_program_scope, Vec * locals_vec);
void extend_ref_local_lifetimes(Expr * body, Vec * locals, TypeScope * scope);
void check_use_after_own_transfer(Expr * body, Vec * locals, Context * ctx);
void insert_exit_deletes(Expr * body, Vec * live, Bool return_only);
void insert_nested_exit_deletes(Expr * stmt, Vec * locals, U32 stmt_idx);
void insert_exit_deletes_into_stmt(Expr * stmt, Vec * body_stmts, Vec * locals, U32 stmt_idx, Vec * new_ch);
void insert_post_stmt_deletes(Expr * stmt, Vec * locals, U32 stmt_idx, Vec * new_ch, TypeScope * scope);
void insert_assign_delete(Expr * stmt, Vec * locals, Vec * new_ch);
void promote_own_transferred_locals(Context * ctx, Expr * body, Vec * locals);
Bool insert_free_calls(Context * ctx, Expr * body, TypeScope * scope, I32 scope_exit);
Bool asap_destroy_body(Context * ctx, Expr * body, TypeScope * scope);
void asap_destroy(Context * ctx);
void precomp_clear_known(Context * ctx);
void precomp_reset_state(Context * ctx);
Bool precomp_has_macro(Context * ctx, Str * name);
Bool precomp_has_func(Context * ctx, Str * name);
Bool is_side_effecting_name(Str * name);
U8 * priv___src_self_precomp_til__hex_digit_value(I8 * b);
Str * priv___src_self_precomp_til__from_source_form(Str * s);
Bool priv___src_self_precomp_til__needs_source_escape(Str * s);
Str * priv___src_self_precomp_til__str_to_source_form(Str * s);
Expr * value_to_expr(Value val, Expr * src);
Value expr_to_value(Expr * e, Context * ctx);
Bool is_known(Context * ctx, Expr * e, Value * out);
Bool is_known_check(Context * ctx, Expr * e);
Bool body_has_local(Expr * body, Str * name);
Bool func_uses_unknown_globals(Expr * e, Expr * func_def, Scope * precomp_scope, Expr * body_root, Bool lenient, Set * visiting, Context * ctx);
Expr * priv___src_self_precomp_til__extract_trivial_literal_return(Expr * fdef);
void * ns_lookup_flat(Str * name, Context * ctx);
Str * fa_recv_type_name(Expr * callee, Context * ctx);
Expr * try_fast_fold_call(Scope * scope, Expr * fcall, Context * ctx);
Expr * try_eval_call(Scope * scope, Expr * fcall, Bool require_known, Context * ctx);
void track_literal(Scope * scope, Str * name, Expr * rhs, Context * ctx);
void track_literal_known_only(Str * name, Expr * rhs, Context * ctx);
Bool is_macro_call(Expr * e, Context * ctx);
Bool is_func_call(Expr * e, Context * ctx);
void fold_subtree(Scope * scope, Expr * e, Context * ctx);
void process_body(Scope * scope, Expr * body, Context * ctx, Bool at_global);
Bool priv___src_self_precomp_til__expr_uses_var_p(Expr * e, Str * name, Context * ctx);
void precomp_register_fold_scope(Scope * global, Expr * prog, Context * ctx);
void precomp_register_core_constants(Scope * global);
Bool priv___src_self_scavenger_til__scav_fa_is_ns(Expr * e);
Str * priv___src_self_scavenger_til__qualified_name(Str * type_name, Str * method_name);
void vec_push_str(Vec * v, Str * s);
void priv___src_self_scavenger_til__children_filter(Vec * v, void * marks, U32 n);
void push_qn(Vec * v, Str * type_name, Str * method);
void priv___src_self_scavenger_til__push_builtin_methods(Vec * v, Str * builtin_name, Str * m1, Str * m2, Str * m3);
void collect_refs(Expr * e, Vec * refs);
void scavenge_filter(Expr * program, Set * visited);
U32 priv___src_self_scavenger_til__dyn_call_real_arg_count(Expr * e);
void priv___src_self_scavenger_til__collect_body_refs(Expr * e, Set * refs, Set * candidates);
Str * priv___src_self_scavenger_til__match_trivial_delete(Expr * stmt);
Bool priv___src_self_scavenger_til__rhs_is_pure_byvalue(Expr * e);
void priv___src_self_scavenger_til__prune_trivial_deletes(Expr * e, Set * dropped);
Bool priv___src_self_scavenger_til__dce_one_body(Expr * body, Bool at_top_level);
Bool priv___src_self_scavenger_til__match_named_delete(Expr * stmt, Str * name);
void priv___src_self_scavenger_til__fix_stale_litstr_in_body(Expr * body);
void priv___src_self_scavenger_til__body_dce_walk(Expr * e, Bool at_top_level);
void priv___src_self_scavenger_til__body_dce_ns(Expr * rhs);
void dce_program_bodies(Expr * program);
Str * priv___src_self_loader_til__str_left(Str * s, U32 * n);
Str * priv___src_self_loader_til__normalize_mode_name(Str * mode_name);
Str * display_path(Str * p, Str * cwd);
Mode * priv___src_self_loader_til__require_mode(Str * path, Str * mode_name);
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
priv___src_self_loader_til__DeclRef * priv___src_self_loader_til__DeclRef_clone(priv___src_self_loader_til__DeclRef * self);
void priv___src_self_loader_til__DeclRef_delete(priv___src_self_loader_til__DeclRef * self, Bool * call_free);
U32 priv___src_self_loader_til__DeclRef_size(void);
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
priv___src_self_builder_til__CollectionInfo * priv___src_self_builder_til__CollectionInfo_clone(priv___src_self_builder_til__CollectionInfo * self);
void priv___src_self_builder_til__CollectionInfo_delete(priv___src_self_builder_til__CollectionInfo * self, Bool * call_free);
U32 priv___src_self_builder_til__CollectionInfo_size(void);
priv___src_self_builder_til__DynCallInfo * priv___src_self_builder_til__DynCallInfo_clone(priv___src_self_builder_til__DynCallInfo * self);
void priv___src_self_builder_til__DynCallInfo_delete(priv___src_self_builder_til__DynCallInfo * self, Bool * call_free);
U32 priv___src_self_builder_til__DynCallInfo_size(void);
Bool priv___src_self_builder_til__is_dyn_call_name(Str * name, Bool * has_ret);
Expr * priv___src_self_builder_til__resolve_local_fn_sig(Context * ctx, Str * name);
Expr * resolve_decl_fn_sig(Expr * rhs, Declaration * dd, TypeScope * scope, Context * ctx);
Expr * fcall_fn_sig(Expr * fcall, Context * ctx);
Bool priv___src_self_builder_til__is_stack_local(Str * name, Context * ctx);
Bool priv___src_self_builder_til__is_current_func_param(Str * name, Context * ctx);
Bool priv___src_self_builder_til__is_value_global(Str * name, Context * ctx);
Bool is_ref_global(Str * name, Context * ctx);
Bool is_ref_local(Str * name, Context * ctx);
Bool use_dot_access(Expr * obj, Context * ctx);
Bool is_primitive_type(Str * name);
Bool is_pod_enum(Str * enum_name, Context * ctx);
Bool priv___src_self_builder_til__variant_is_payload_less(Str * enum_name, Str * variant_name, Context * ctx);
Bool priv___src_self_builder_til__is_pod_enum_clone_call(Expr * e, Context * ctx);
Bool is_pod_struct(Str * struct_name, Context * ctx);
Bool is_funcsig_type(Str * name, Context * ctx);
Bool is_ext_h_type(Str * name);
Bool is_skip_ext_decl(Str * name);
Bool is_exported_top_level_global(Expr * stmt);
Expr * priv___src_self_builder_til__find_struct_def(Str * name, Context * ctx);
Expr * priv___src_self_builder_til__find_callee_fdef(Str * name, Context * ctx);
Str * fa_struct_name(Expr * e);
Bool priv___src_self_builder_til__builder_fa_is_ptr_with_fname(Str * sname, Str * fname, Context * ctx);
Bool builder_fa_is_ptr(Expr * e, Context * ctx);
Bool priv___src_self_builder_til__builder_fa_is_ns_with_fname(Expr * e, Str * sname, Str * fname, Context * ctx);
Bool builder_fa_is_ns(Expr * e, Context * ctx);
Bool is_shallow_param(Str * name, Context * ctx);
Bool callee_returns_shallow(Str * callee_name, Context * ctx);
Bool callee_returns_dynamic(Str * callee_name, Context * ctx);
Bool callee_param_is_shallow(Str * callee_name, U32 arg_index, Context * ctx);
Bool callee_param_is_usize(Str * callee_name, U32 arg_index, Context * ctx);
Bool callee_param_is_uptr(Str * callee_name, U32 arg_index, Context * ctx);
Bool callee_param_is_own(Str * callee_name, U32 arg_index, Context * ctx);
Bool priv___src_self_builder_til__fcall_is_shallow_return(Expr * fcall, Context * ctx);
Bool fcall_returns_dynamic(Expr * fcall, Context * ctx);
Str * priv___src_self_builder_til__til_type_to_c(Type t);
Str * extern_decl_ctype(Type t, Type rhs_t, Context * ctx);
Str * resolve_decl_ctype(Type t, Type rhs_t, Str * explicit, Context * ctx);
Str * c_type_name(Type t, Str * struct_name, Context * ctx);
Str * func_to_c(Str * name);
Str * type_name_to_c(Str * name, Context * ctx);
Str * type_name_to_c_value(Str * name, Context * ctx);
File * emit_u64(File * f, U64 v);
File * emit_i32(File * f, I32 v);
File * priv___src_self_builder_til__emit_indent(File * f, I32 depth);
U32 * priv___src_self_builder_til__c_lit_byte_count(Str * s);
void priv___src_self_builder_til__collect_ident_refs(Expr * e, Set * refs);
void emit_til_default(File * f, Type t);
Str * param_ctype(FunctionDef * fd, U32 i, Context * ctx);
void emit_param_list(File * f, Expr * fdef, Bool with_names, Bool for_ext_decl, Context * ctx);
void priv___src_self_builder_til__collect_dyn_methods(Expr * e, Vec * methods);
void collect_collection_builtins(Expr * e, Vec * infos);
void emit_field(File * f, Str * var, Str * field, Context * ctx);
Str * get_stack_local_ctype(Str * name, Context * ctx);
Str * resolve_ident_ctype(Str * ident, Type * ttype, Str * sname, Context * ctx);
Str * resolve_callee_name(Expr * fcall);
Str * callee_return_ctype(Str * callee_name, Context * ctx);
Str * fcall_return_ctype(Expr * fcall, Context * ctx);
void check_fcall_mut_args(Context * ctx, Expr * e);
void collect_unsafe_to_hoist(Context * ctx, Expr * body);
void collect_dyn_has_methods(Expr * e, Vec * methods);
Bool priv___src_self_builder_til__fcall_is_struct_ctor(Expr * e);
Bool priv___src_self_builder_til__pod_ctor_args_are_safe(Expr * ctor, Context * ctx);
void emit_pod_compound_literal(File * f, Expr * ctor, I32 depth, Context * ctx);
void emit_stmt_decl(File * f, Expr * e, I32 depth, Context * ctx);
Str * emit_return_ctype(Expr * rv, Context * ctx);
void emit_return_box(File * f, Expr * rv, I32 depth, Context * ctx);
void emit_stmt_return(File * f, Expr * e, I32 depth, Context * ctx);
Bool priv___src_self_builder_til__is_noop_delete_stmt(Expr * e, Context * ctx);
void priv___src_self_builder_til__emit_stmt(File * f, Expr * e, I32 depth, Context * ctx);
void emit_fcall_funcptr_cast(File * f, Expr * e, Expr * sig);
void emit_fcall_funcptr_args(File * f, Expr * e, Expr * sig, I32 depth, Context * ctx);
void emit_str_lit_expr(File * f, Str * s);
File * emit_expr(File * f, Expr * e, I32 depth, Context * ctx);
void priv___src_self_builder_til__emit_body(File * f, Expr * body, I32 depth, Context * ctx);
void emit_ctor_fields(File * f, Str * var, Expr * ctor, I32 depth, Context * ctx);
void emit_ns_inits(File * f, I32 depth, LoadedProgram * lp);
void emit_body_scoped(File * f, Expr * body, I32 depth, Context * ctx);
File * priv___src_self_builder_til__emit_deref(File * f, Expr * e, I32 depth, Context * ctx);
File * emit_as_ptr(File * f, Expr * e, I32 depth, Bool is_own, Context * ctx);
void emit_usize_ref(File * f, Expr * e, I32 depth, Context * ctx);
void emit_uptr_ref(File * f, Expr * e, I32 depth, Context * ctx);
void emit_cli_parse_arg(File * f, Str * pname, Str * ptype, I32 argi);
void emit_func_def(File * f, Str * name, Expr * func_def, Mode * mode, Bool is_static, LoadedProgram * lp);
void emit_struct_typedef(File * f, Str * name, Expr * struct_def);
void emit_ns_method(File * f, Str * name, Str * dd_name, Expr * fdef, LoadedProgram * lp);
void emit_struct_funcs(File * f, Str * name, Expr * struct_def, LoadedProgram * lp);
void emit_enum_def(File * f, Str * name, Expr * enum_def, LoadedProgram * lp);
void emit_enum_struct_body(File * f, Str * ename, Expr * enum_def, Context * ctx);
void topo_emit_struct_enum_defs_lp(File * f, Set * emitted, LoadedProgram * lp);
Str * func_return_ctype(FunctionDef * fd, Context * ctx);
void priv___src_self_builder_til__emit_func_forward_decl(File * f, Str * name, Expr * fdef, Bool top_level, Context * ctx);
void emit_funcsig_typedef(File * f, Str * name, Expr * fdef, Context * ctx);
void emit_funcsig_typedefs_lp(File * f, LoadedProgram * lp);
void emit_header_forward_decls_lp(File * f, LoadedProgram * lp);
void emit_header_defs_and_funcs_lp(File * f, LoadedProgram * lp);
void emit_header_global_decls_lp(File * f, LoadedProgram * lp);
I32 build_forward_header_lp(Str * fwd_path, LoadedProgram * lp);
I32 build_header_lp(Str * h_path, LoadedProgram * lp);
Bool emit_binding_ns_method(File * f, Str * fdd_name, FunctionDef * fd, Bool * has_ns);
void emit_binding_ns_methods(File * f, Expr * def);
I32 build_til_binding(LoadedProgram * lp, Str * til_path, Str * lib_name);
Str * type_name_to_ctypes(Str * name);
Str * type_name_to_ctypes_param(Str * name, Bool is_shallow);
Str * type_name_to_ctypes_return(Str * name, Bool is_shallow);
I32 build_python_binding(LoadedProgram * lp, Str * py_path, Str * lib_name);
I32 compile_lib(Str * c_path, Str * lib_name, Str * ext_c_path, Str * user_c_path, Str * link_flags, Str * include_flags, Target * target, Str * cc_override, Bool * asan);
I32 compile_c(Str * c_path, Str * bin_path, Str * ext_c_path, Str * user_c_path, Str * link_flags, Str * include_flags, Target * target, Str * cc_override, Str * mode_auto_import, Bool * asan);
void register_funcsig_prog(Expr * prog, Context * ctx);
void emit_global_inits_prog(File * f, Expr * prog, Context * ctx);
void emit_global_inits(File * f, LoadedProgram * lp);
void build_register_funcsig_names_lp(LoadedProgram * lp);
void register_lookups_prog(Expr * prog, Context * ctx);
void build_register_lookups_lp(LoadedProgram * lp);
void emit_monolithic_header_lp(File * f, Mode * mode, LoadedProgram * lp);
void emit_all_forward_declarations(File * f, Mode * mode, LoadedProgram * lp);
void emit_dyn_fn_wrapper(File * f, Str * type_name, Str * method_name, FunctionDef * fd, Context * ctx);
void emit_dyn_fn_wrappers(File * f, LoadedProgram * lp);
void emit_dyn_size_of_body(File * f, LoadedProgram * lp);
void priv___src_self_builder_til__emit_struct_field_branch_for_stmt(File * f, Expr * stmt, I32 kind);
void priv___src_self_builder_til__emit_struct_field_branches(File * f, I32 kind, LoadedProgram * lp);
void emit_struct_introspection_bodies(File * f, LoadedProgram * lp);
void priv___src_self_builder_til__emit_enum_variant_branch_for_stmt(File * f, Expr * stmt, I32 kind);
void priv___src_self_builder_til__emit_enum_variant_branches(File * f, I32 kind, LoadedProgram * lp);
void emit_enum_introspection_bodies(File * f, LoadedProgram * lp);
void priv___src_self_builder_til__emit_funcsig_branch_for_stmt(File * f, Expr * stmt, I32 kind);
void priv___src_self_builder_til__emit_funcsig_branches(File * f, I32 kind, LoadedProgram * lp);
void emit_funcsig_introspection_bodies(File * f, LoadedProgram * lp);
Str * priv___src_self_builder_til__dyn_type_str_display(Str * vn);
Bool priv___src_self_builder_til__find_loaded_enum_variants(Str * ename, Vec * variant_names, Vec * variant_types, LoadedProgram * lp);
void emit_dyn_type_to_str_body(File * f, LoadedProgram * lp);
void emit_dyn_call_bodies(File * f, LoadedProgram * lp);
void emit_dyn_has_bodies(File * f, LoadedProgram * lp);
void emit_collection_helpers(File * f, LoadedProgram * lp);
void emit_global_declarations(File * f, LoadedProgram * lp);
void emit_test_main(File * f, LoadedProgram * lp);
void emit_script_main(File * f, LoadedProgram * lp);
void emit_function_bodies(File * f, Mode * mode, LoadedProgram * lp);
void emit_ext_func_declarations(File * f, Expr * program, Context * ctx);
void emit_lib_init(File * f, LoadedProgram * lp);
I32 build(Mode * mode, Bool run_tests, Str * c_output_path, LoadedProgram * lp);
priv___src_self_builder_til__BuildPaths * priv___src_self_builder_til__BuildPaths_clone(priv___src_self_builder_til__BuildPaths * self);
void priv___src_self_builder_til__BuildPaths_delete(priv___src_self_builder_til__BuildPaths * self, Bool * call_free);
U32 priv___src_self_builder_til__BuildPaths_size(void);
priv___src_self_builder_til__BuildPaths * derive_build_paths(LoadedProgram * lp, Str * custom_bin, Str * custom_c, Target * target);
void make_build_dirs(priv___src_self_builder_til__BuildPaths * paths);
I32 priv___src_self_builder_til__translate_ast(LoadedProgram * lp, priv___src_self_builder_til__BuildPaths * paths);
void print_translate_success(priv___src_self_builder_til__BuildPaths * paths);
I32 compile_ast(LoadedProgram * lp, priv___src_self_builder_til__BuildPaths * paths, Target * target, Str * cc_override, Bool * asan);
I32 cmd_translate(LoadedProgram * lp, Str * custom_c, Target * target);
I32 cmd_build(LoadedProgram * lp, Str * custom_bin, Str * custom_c, Target * target, Str * cc_override, Bool * asan);
I32 check_install_rc(I32 * rc, Str * what);
Str * builder_compiler_root(LoadedProgram * lp);
Str * support_root(Str * prefix);
I32 install_file(Str * src, Str * dst, Str * what);
I32 install_tree(Str * src, Str * dst, Str * what);
Bool is_compiler_install(LoadedProgram * lp, priv___src_self_builder_til__BuildPaths * paths);
I32 install_compiler_support(LoadedProgram * lp, Str * prefix);
void print_install_success(Str * path);
I32 cmd_install(LoadedProgram * lp, Str * install_prefix_in, Target * target, Str * cc_override, Bool * asan);
Str * asan_child_prefix(Bool * asan);
I32 cmd_run(LoadedProgram * lp, Str * custom_bin, Str * custom_c, Vec * user_argv, Target * target, Str * cc_override, Bool * asan);
I32 cmd_test_build_run(LoadedProgram * lp, Str * custom_bin, Str * custom_c, Target * target, Str * cc_override, Bool * asan);
Str * format_unit_doc_org(Str * unit_path, Expr * ast, TypeScope * scope);
Str * til_doc_out_path(Str * unit_path);
void ensure_parent_dir(Str * path);
void emit_unit_doc(ProgramUnit * u, Context * ctx);
I32 cmd_doc(LoadedProgram * lp);
Str * interp_error_path(Context * ctx);
void interp_error(Expr * e, Str * msg, Context * ctx);
void interp_lang_error(Expr * e, Str * msg, Context * ctx);
Bool priv___src_self_interpreter_til__struct_def_shallow_safe(StructDef * sdef_data);
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
Value * Value_Ref(void * val);
Value * Value_Dynamic(void * val);
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
Expr * lookup_interp_type_def(Str * name, Context * ctx);
Value val_none(void);
Value val_i64(I64 v);
Value val_u8(I64 v);
Value val_i16(I64 v);
Value val_i32(I64 v);
Value val_u32(I64 v);
Value val_u64(U64 v);
Value val_f32(F32 v);
Value val_bool(Bool v);
Value val_enum_flat(Str * enum_name, I32 etag, void * payload_data, I32 payload_size);
Value val_enum_simple(Str * enum_name, I32 etag);
I32 elem_size_for_type(Str * type_name);
Value parse_cli_arg(Str * s, Str * type_name, Context * ctx);
void * value_ptr_view(Value * v);
Bool is_value_ptr(Value * v);
void priv___src_self_interpreter_til__resolve_ptr_to_struct(Value * obj, Scope * scope, Str * obj_sname);
Value eval_expr(Scope * scope, Expr * e, Context * ctx);
Value * reinterpret_ptr_value(Value * val, Str * type_name, Scope * scope, Context * ctx);
Bool guard_own_param_skip(Scope * scope, Expr * e, Expr * func_def);
void * resolve_field_assign_base(Scope * scope, Expr * obj_expr);
Expr * resolve_field_assign_sdef(Scope * scope, Expr * obj_expr);
void eval_body(Scope * scope, Expr * body, Context * ctx);
Value eval_call(Scope * scope, Expr * e, Context * ctx);
void free_value(Value v);
void cleanup_value_payload(Value v);
priv___src_self_interpreter_til__DynPtrBox * priv___src_self_interpreter_til__DynPtrBox_clone(priv___src_self_interpreter_til__DynPtrBox * self);
void priv___src_self_interpreter_til__DynPtrBox_delete(priv___src_self_interpreter_til__DynPtrBox * self, Bool * call_free);
U32 priv___src_self_interpreter_til__DynPtrBox_size(void);
void free_value_full(Value v);
Bool needs_widen(Value * val, Str * ptype);
Value shallow_copy_value(Value * v);
Value make_struct_value(Str * sname, Expr * sdef, void * data, Bool borrowed);
Value * widen_numeric(Value * v, Str * ptype, Context * ctx);
Cell * scope_get(Scope * s, Str * name);
Scope * scope_new(Scope * parent);
void scope_set_owned(Scope * s, Str * name, Value * val);
void scope_set_borrowed(Scope * s, Str * name, Cell * cell);
void scope_free(Scope * s);
Bool priv___src_self_interpreter_til__interp_fa_is_ns_with_fname(Expr * obj_expr, Str * sname, Expr * sdef, Str * fname);
Bool interp_fa_is_ns_inner(Scope * scope, Expr * e, Str * sname);
Cell * field_assign_dyn_move_src(Scope * scope, Expr * val_expr);
Bool interp_fa_is_ns(Scope * scope, Expr * e);
void value_to_buf(void * dest, Value * val, Str * type_name);
Value build_argv_array(Vec * argv, U32 offset, U32 count, Str * elem_type, Context * ctx);
void interpreter_init_ns(Context * ctx, Scope * global, Expr * program);
Str * priv___src_self_interpreter_til__ns_qname(Str * sname, Str * fname);
Value * ns_get(Str * sname, Str * fname, Context * ctx);
void ns_set(Str * sname, Str * fname, Value val, Context * ctx);
Value make_str_value(void * data, U64 len, Context * ctx);
Value make_str_value_view(void * data, U64 len, Context * ctx);
Value make_str_value_own(void * data, U64 len, Context * ctx);
Str str_view(Value v);
Declaration * find_field_decl(Expr * struct_def, Str * fname);
Value read_field(void * inst_data, Declaration * dd, Context * ctx);
void write_field(void * inst_data, Declaration * dd, Value * val);
void interpret_register_defs(Scope * global, Expr * prog);
void interpret_register_aliases(Scope * global, Expr * prog);
void interpret_copy_alias_ns(Expr * prog, Scope * global, Context * ctx);
I32 priv___src_self_interpreter_til__interpret_units(LoadedProgram * lp, Vec * user_argv, Str * fwd_path);
I32 cmd_interpret(LoadedProgram * lp, Vec * user_argv);
ffi_type * ffi_type_clone(ffi_type * self);
void ffi_type_delete(ffi_type * self, Bool * call_free);
U32 ffi_type_size(void);
ffi_cif * ffi_cif_clone(ffi_cif * self);
void ffi_cif_delete(ffi_cif * self, Bool * call_free);
U32 ffi_cif_size(void);
priv___src_self_dispatch_til__ExtStr * priv___src_self_dispatch_til__ExtStr_clone(priv___src_self_dispatch_til__ExtStr * self);
void priv___src_self_dispatch_til__ExtStr_delete(priv___src_self_dispatch_til__ExtStr * self, Bool * call_free);
U32 priv___src_self_dispatch_til__ExtStr_size(void);
FFIEntry * FFIEntry_clone(FFIEntry * self);
void FFIEntry_delete(FFIEntry * self, Bool * call_free);
U32 FFIEntry_size(void);
ExprPtrBox * ExprPtrBox_clone(ExprPtrBox * self);
void ExprPtrBox_delete(ExprPtrBox * self, Bool * call_free);
U32 ExprPtrBox_size(void);
FFITypePtrBox * FFITypePtrBox_clone(FFITypePtrBox * self);
void FFITypePtrBox_delete(FFITypePtrBox * self, Bool * call_free);
U32 FFITypePtrBox_size(void);
void ffi_reset(Context * ctx);
ffi_type * priv___src_self_dispatch_til__ffi_type_ref(Str * name);
void * ffi_alloc_cif(void);
Bool ffi_cif_rtype_is_struct(ffi_cif * cif);
U8 * ffi_dlsym(Str * name);
void ffi_init_link_libs(Str * link_flags);
I32 ffi_init_user_so(Str * fwd_path, Str * user_c_path, Str * ext_c_path, Str * link_flags, Str * so_path_out);
void ffi_init_struct_defs(Expr * program, Context * ctx);
void ffi_init_struct_defs_append(Expr * program, Context * ctx);
U64 * value_to_u64(Value * v);
ffi_type * uptr_ffi_type(Context * ctx);
ffi_type * usize_ffi_type(Context * ctx);
F32 * priv___src_self_dispatch_til__value_to_f32(Value * v);
Str * priv___src_self_dispatch_til__value_variant_name(Value * v);
Bool * priv___src_self_dispatch_til__narrow_bool_arg(Scope * s, Expr * e, Context * ctx);
Bool h_Bool_and(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_Bool_or(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_Bool_not(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_U8_from_i64(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_I16_from_i64(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_I32_from_i64(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_F32_from_i64(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_U32_from_i64(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_dispatch_til__h_print_single(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_print_flush(Scope * _s, Expr * _e, Value * r, Context * _ctx);
Bool h_exit(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_readfile(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_writefile(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_spawn_cmd(Scope * s, Expr * e, Value * r, Context * ctx);
void * val_to_ptr(Value * v);
Bool h_dyn_has_method(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_dyn_fn(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_dyn_size_of(Scope * s, Expr * e, Value * r, Context * ctx);
Value priv___src_self_dispatch_til__str_to_owned_value(Str * src, Context * ctx);
Expr * interp_lookup_struct(Scope * s, Expr * e, Str * type_name, Str * who, Context * ctx);
Bool h_struct_field_count(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_struct_field_name(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_struct_field_is_mut(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_struct_field_type(Scope * s, Expr * e, Value * r, Context * ctx);
Expr * interp_lookup_enum(Scope * s, Expr * e, Str * type_name, Str * who, Context * ctx);
Bool h_enum_variant_count(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_enum_variant_name(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_enum_variant_has_payload(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_enum_variant_payload_type(Scope * s, Expr * e, Value * r, Context * ctx);
Expr * interp_lookup_funcsig(Scope * s, Expr * e, Str * type_name, Str * who, Context * ctx);
Bool h_func_sig_param_count(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_func_sig_param_type(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_func_sig_return_count(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_func_sig_return_type(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_func_sig_throw_count(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_func_sig_throw_type(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_dyn_type_to_str(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_check_cmd_status(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_sleep(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_file_mtime(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_str_parse_f32(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_clock_ms(Scope * _s, Expr * _e, Value * r);
Bool h_get_thread_count(Scope * _s, Expr * _e, Value * r);
Bool h_cfile_open(Scope * s, Expr * e, Value * r, Context * ctx);
ffi_type * priv___src_self_dispatch_til__known_ffi_type(Str * type_name, Context * ctx);
ffi_type * priv___src_self_dispatch_til__shallow_ffi_type(Str * type_name, Context * ctx);
ffi_type * field_ffi_type(Declaration * dd, Context * ctx);
ffi_type * build_struct_ffi_type(Expr * struct_def, Context * ctx);
Bool h_free(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_cfile_close(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_cfile_write_str(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_ptr_add(Scope * s, Expr * e, Value * r, Context * ctx);
Bool h_cfile_read_all(Scope * s, Expr * e, Value * r, Context * ctx);
void reg_dispatch(Str * name, DispatchFn handler, Context * ctx);
void dispatch_init(Context * ctx);
Bool ext_dispatch_builtin(Str * name, Scope * scope, Expr * e, Value * result, Context * ctx);
Bool h_dyn_call(Scope * s, Expr * e, Value * r, Context * ctx);
I32 get_elem_size(Scope * s, Str * type_name, Expr * src, Context * ctx);
Bool enum_method_dispatch(Str * method, Scope * scope, Expr * enum_def, Str * enum_name, Expr * e, Value * result, Context * ctx);
Bool ffi_decode_scalar(Str * rtype, void * p, Value * result, Context * ctx);
Expr * ffi_call_ret_struct_def(FFIEntry * fe, Context * ctx);
Bool priv___src_self_dispatch_til__ffi_shallow_type_info(void * atype, Str * type_name, I32 * size);
Bool priv___src_self_dispatch_til__ffi_write_shallow_arg(Scope * scope, Value * v, void * atype, void * dst, Context * ctx);
Bool ext_dispatch_ffi(Str * name, Scope * scope, Expr * e, Value * result, Context * ctx);
Bool ext_function_dispatch(Str * name, Scope * scope, Expr * e, Value * result, Context * ctx);
void ffi_register(Str * name, void * fn, Expr * fdef, Context * ctx);
void ffi_init_scan_program(Expr * program, Context * ctx);
I32 ffi_init(Expr * program, Str * fwd_path, Str * user_c_path, Str * ext_c_path, Str * link_flags, Context * ctx);
void ffi_cleanup(Context * ctx);
Bool priv___src_self_binder_til__bind_is_ws(I8 * c);
U32 * priv___src_self_binder_til__skip_ws(Str * s, U32 from);
U32 * priv___src_self_binder_til__skip_word(Str * s, U32 from);
U32 * priv___src_self_binder_til__trim_right(Str * s, U32 from, U32 to);
Bool priv___src_self_binder_til__range_eq_lit(Str * s, U32 start, U32 end, Str * lit);
I64 * priv___src_self_binder_til__parse_c_int_literal(Str * s, U32 from, U32 to, Bool * success);
Bool * priv___src_self_binder_til__push_til_base(Str * out, Str * c);
priv___src_self_binder_til__BinderState * priv___src_self_binder_til__BinderState_clone(priv___src_self_binder_til__BinderState * self);
void priv___src_self_binder_til__BinderState_delete(priv___src_self_binder_til__BinderState * self, Bool * call_free);
U32 priv___src_self_binder_til__BinderState_size(void);
void priv___src_self_binder_til__register_alias(priv___src_self_binder_til__BinderState * bs, Str * name);
void priv___src_self_binder_til__register_dynamic_alias(priv___src_self_binder_til__BinderState * bs, Str * name);
Bool priv___src_self_binder_til__is_alias_to_primitive(priv___src_self_binder_til__BinderState * bs, Str * name);
Bool priv___src_self_binder_til__is_alias_to_dynamic(priv___src_self_binder_til__BinderState * bs, Str * name);
void priv___src_self_binder_til__push_til_default(priv___src_self_binder_til__BinderState * bs, Str * out, Str * c);
Bool * priv___src_self_binder_til__bind_emit_field(priv___src_self_binder_til__BinderState * bs, Str * out, Str * line, Str * comment);
void priv___src_self_binder_til__emit_comment_line(Str * out, Str * line);
Bool * priv___src_self_binder_til__emit_struct_body(priv___src_self_binder_til__BinderState * bs, Str * out, Vec * lines, U32 open, U32 close);
U32 * priv___src_self_binder_til__emit_typedef_struct(priv___src_self_binder_til__BinderState * bs, Str * out, Vec * lines, U32 start, U32 open, U32 close);
U32 * priv___src_self_binder_til__emit_typedef_enum(priv___src_self_binder_til__BinderState * bs, Str * out, Vec * lines, U32 start, U32 open, U32 close);
Bool * priv___src_self_binder_til__emit_typedef_alias(priv___src_self_binder_til__BinderState * bs, Str * out, Str * line);
Bool * priv___src_self_binder_til__emit_typedef_fnptr(priv___src_self_binder_til__BinderState * bs, Str * out, Str * line);
Bool * priv___src_self_binder_til__emit_define(Str * out, Str * line);
Bool * priv___src_self_binder_til__emit_function(priv___src_self_binder_til__BinderState * bs, Str * out, Vec * lines, U32 start, U32 end);
void priv___src_self_binder_til__walk_header(priv___src_self_binder_til__BinderState * bs, Str * out, Vec * lines);
Str * priv___src_self_binder_til__header_dir_of(Str * path);
Bool priv___src_self_binder_til__path_in_dir(Str * marker_path, Str * incdir);
Bool priv___src_self_binder_til__looks_like_macro_fragment(Str * line);
Vec * priv___src_self_binder_til__filter_preprocessed(Str * pre, Str * incdir);
Str * priv___src_self_binder_til__collapse_blank_runs(Str * s);
void generate_bindings(Str * in_path, Str * out_path);
Vector3 * Vector3_clone(Vector3 * self);
void Vector3_delete(Vector3 * self, Bool * call_free);
U32 Vector3_size(void);
Vector4 * Vector4_clone(Vector4 * self);
void Vector4_delete(Vector4 * self, Bool * call_free);
U32 Vector4_size(void);
Texture * Texture_clone(Texture * self);
void Texture_delete(Texture * self, Bool * call_free);
U32 Texture_size(void);
RenderTexture * RenderTexture_clone(RenderTexture * self);
void RenderTexture_delete(RenderTexture * self, Bool * call_free);
U32 RenderTexture_size(void);
Camera3D * Camera3D_clone(Camera3D * self);
void Camera3D_delete(Camera3D * self, Bool * call_free);
U32 Camera3D_size(void);
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
Bool * priv___src_self_typer_til__CtorArg_eq(priv___src_self_typer_til__CtorArg *, priv___src_self_typer_til__CtorArg *);
priv___src_self_typer_til__CtorArg *priv___src_self_typer_til__CtorArg_Unfilled();
priv___src_self_typer_til__CtorArg *priv___src_self_typer_til__CtorArg_Filled(Expr *);
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
Value *Value_Ref(void *);
Value *Value_Dynamic(void *);

extern U32 CAP_LIT;
extern U32 CAP_VIEW;
extern U32 ELEM_POD;
extern U32 ELEM_BOXED;
extern U32 ELEM_FN;
extern Str __til_docs_blob__;
extern Str __til_info_blob__;
extern Map core_modes;
extern Str I64Name;
extern Str U8Name;
extern Str I8Name;
extern Str I16Name;
extern Str I32Name;
extern Str U32Name;
extern Str U64Name;
extern Str F32Name;
extern Str BoolName;
extern U8 priv___src_self_scavenger_til__MARK_DELETE;
extern U8 priv___src_self_scavenger_til__MARK_REPLACE_RHS;
extern I32 ENUM_PAYLOAD_OFFSET;
extern I32 ENUM_PAYLOAD_OFFSET;
extern I64 FFI_TYPE_VOID;
extern I64 FFI_TYPE_INT;
extern I64 FFI_TYPE_FLOAT;
extern I64 FFI_TYPE_DOUBLE;
extern I64 FFI_TYPE_LONGDOUBLE;
extern I64 FFI_TYPE_UINT8;
extern I64 FFI_TYPE_SINT8;
extern I64 FFI_TYPE_UINT16;
extern I64 FFI_TYPE_SINT16;
extern I64 FFI_TYPE_UINT32;
extern I64 FFI_TYPE_SINT32;
extern I64 FFI_TYPE_UINT64;
extern I64 FFI_TYPE_SINT64;
extern I64 FFI_TYPE_STRUCT;
extern I64 FFI_TYPE_POINTER;
extern I64 FFI_TYPE_COMPLEX;
extern I32 FFI_FIRST_ABI;
extern I32 FFI_UNIX64;
extern I32 FFI_WIN64;
extern I32 FFI_EFI64;
extern I32 FFI_GNUW64;
extern I32 FFI_LAST_ABI;
extern I32 FFI_DEFAULT_ABI;
extern I64 FFI_CLOSURES;
extern I64 FFI_GO_CLOSURES;
extern I64 FFI_TRAMPOLINE_SIZE;
extern I64 FFI_NATIVE_RAW_API;
extern I64 FFI_64_BIT_MAX;
extern I32 FFI_OK;
extern I32 FFI_BAD_TYPEDEF;
extern I32 FFI_BAD_ABI;
extern I32 FFI_BAD_ARGTYPE;
extern I64 FFI_SIZEOF_ARG;
extern I64 RAYLIB_VERSION_MAJOR;
extern I64 RAYLIB_VERSION_MINOR;
extern I64 RAYLIB_VERSION_PATCH;
extern I32 FLAG_VSYNC_HINT;
extern I32 FLAG_FULLSCREEN_MODE;
extern I32 FLAG_WINDOW_RESIZABLE;
extern I32 FLAG_WINDOW_UNDECORATED;
extern I32 FLAG_WINDOW_HIDDEN;
extern I32 FLAG_WINDOW_MINIMIZED;
extern I32 FLAG_WINDOW_MAXIMIZED;
extern I32 FLAG_WINDOW_UNFOCUSED;
extern I32 FLAG_WINDOW_TOPMOST;
extern I32 FLAG_WINDOW_ALWAYS_RUN;
extern I32 FLAG_WINDOW_TRANSPARENT;
extern I32 FLAG_WINDOW_HIGHDPI;
extern I32 FLAG_WINDOW_MOUSE_PASSTHROUGH;
extern I32 FLAG_BORDERLESS_WINDOWED_MODE;
extern I32 FLAG_MSAA_4X_HINT;
extern I32 FLAG_INTERLACED_HINT;
extern I32 LOG_ALL;
extern I32 LOG_TRACE;
extern I32 LOG_DEBUG;
extern I32 LOG_INFO;
extern I32 LOG_WARNING;
extern I32 LOG_ERROR;
extern I32 LOG_FATAL;
extern I32 LOG_NONE;
extern I32 KEY_NULL;
extern I32 KEY_APOSTROPHE;
extern I32 KEY_COMMA;
extern I32 KEY_MINUS;
extern I32 KEY_PERIOD;
extern I32 KEY_SLASH;
extern I32 KEY_ZERO;
extern I32 KEY_ONE;
extern I32 KEY_TWO;
extern I32 KEY_THREE;
extern I32 KEY_FOUR;
extern I32 KEY_FIVE;
extern I32 KEY_SIX;
extern I32 KEY_SEVEN;
extern I32 KEY_EIGHT;
extern I32 KEY_NINE;
extern I32 KEY_SEMICOLON;
extern I32 KEY_EQUAL;
extern I32 KEY_A;
extern I32 KEY_B;
extern I32 KEY_C;
extern I32 KEY_D;
extern I32 KEY_E;
extern I32 KEY_F;
extern I32 KEY_G;
extern I32 KEY_H;
extern I32 KEY_I;
extern I32 KEY_J;
extern I32 KEY_K;
extern I32 KEY_L;
extern I32 KEY_M;
extern I32 KEY_N;
extern I32 KEY_O;
extern I32 KEY_P;
extern I32 KEY_Q;
extern I32 KEY_R;
extern I32 KEY_S;
extern I32 KEY_T;
extern I32 KEY_U;
extern I32 KEY_V;
extern I32 KEY_W;
extern I32 KEY_X;
extern I32 KEY_Y;
extern I32 KEY_Z;
extern I32 KEY_LEFT_BRACKET;
extern I32 KEY_BACKSLASH;
extern I32 KEY_RIGHT_BRACKET;
extern I32 KEY_GRAVE;
extern I32 KEY_SPACE;
extern I32 KEY_ESCAPE;
extern I32 KEY_ENTER;
extern I32 KEY_TAB;
extern I32 KEY_BACKSPACE;
extern I32 KEY_INSERT;
extern I32 KEY_DELETE;
extern I32 KEY_RIGHT;
extern I32 KEY_LEFT;
extern I32 KEY_DOWN;
extern I32 KEY_UP;
extern I32 KEY_PAGE_UP;
extern I32 KEY_PAGE_DOWN;
extern I32 KEY_HOME;
extern I32 KEY_END;
extern I32 KEY_CAPS_LOCK;
extern I32 KEY_SCROLL_LOCK;
extern I32 KEY_NUM_LOCK;
extern I32 KEY_PRINT_SCREEN;
extern I32 KEY_PAUSE;
extern I32 KEY_F1;
extern I32 KEY_F2;
extern I32 KEY_F3;
extern I32 KEY_F4;
extern I32 KEY_F5;
extern I32 KEY_F6;
extern I32 KEY_F7;
extern I32 KEY_F8;
extern I32 KEY_F9;
extern I32 KEY_F10;
extern I32 KEY_F11;
extern I32 KEY_F12;
extern I32 KEY_LEFT_SHIFT;
extern I32 KEY_LEFT_CONTROL;
extern I32 KEY_LEFT_ALT;
extern I32 KEY_LEFT_SUPER;
extern I32 KEY_RIGHT_SHIFT;
extern I32 KEY_RIGHT_CONTROL;
extern I32 KEY_RIGHT_ALT;
extern I32 KEY_RIGHT_SUPER;
extern I32 KEY_KB_MENU;
extern I32 KEY_KP_0;
extern I32 KEY_KP_1;
extern I32 KEY_KP_2;
extern I32 KEY_KP_3;
extern I32 KEY_KP_4;
extern I32 KEY_KP_5;
extern I32 KEY_KP_6;
extern I32 KEY_KP_7;
extern I32 KEY_KP_8;
extern I32 KEY_KP_9;
extern I32 KEY_KP_DECIMAL;
extern I32 KEY_KP_DIVIDE;
extern I32 KEY_KP_MULTIPLY;
extern I32 KEY_KP_SUBTRACT;
extern I32 KEY_KP_ADD;
extern I32 KEY_KP_ENTER;
extern I32 KEY_KP_EQUAL;
extern I32 KEY_BACK;
extern I32 KEY_MENU;
extern I32 KEY_VOLUME_UP;
extern I32 KEY_VOLUME_DOWN;
extern I32 MOUSE_BUTTON_LEFT;
extern I32 MOUSE_BUTTON_RIGHT;
extern I32 MOUSE_BUTTON_MIDDLE;
extern I32 MOUSE_BUTTON_SIDE;
extern I32 MOUSE_BUTTON_EXTRA;
extern I32 MOUSE_BUTTON_FORWARD;
extern I32 MOUSE_BUTTON_BACK;
extern I32 MOUSE_CURSOR_DEFAULT;
extern I32 MOUSE_CURSOR_ARROW;
extern I32 MOUSE_CURSOR_IBEAM;
extern I32 MOUSE_CURSOR_CROSSHAIR;
extern I32 MOUSE_CURSOR_POINTING_HAND;
extern I32 MOUSE_CURSOR_RESIZE_EW;
extern I32 MOUSE_CURSOR_RESIZE_NS;
extern I32 MOUSE_CURSOR_RESIZE_NWSE;
extern I32 MOUSE_CURSOR_RESIZE_NESW;
extern I32 MOUSE_CURSOR_RESIZE_ALL;
extern I32 MOUSE_CURSOR_NOT_ALLOWED;
extern I32 GAMEPAD_BUTTON_UNKNOWN;
extern I32 GAMEPAD_BUTTON_LEFT_FACE_UP;
extern I32 GAMEPAD_BUTTON_LEFT_FACE_RIGHT;
extern I32 GAMEPAD_BUTTON_LEFT_FACE_DOWN;
extern I32 GAMEPAD_BUTTON_LEFT_FACE_LEFT;
extern I32 GAMEPAD_BUTTON_RIGHT_FACE_UP;
extern I32 GAMEPAD_BUTTON_RIGHT_FACE_RIGHT;
extern I32 GAMEPAD_BUTTON_RIGHT_FACE_DOWN;
extern I32 GAMEPAD_BUTTON_RIGHT_FACE_LEFT;
extern I32 GAMEPAD_BUTTON_LEFT_TRIGGER_1;
extern I32 GAMEPAD_BUTTON_LEFT_TRIGGER_2;
extern I32 GAMEPAD_BUTTON_RIGHT_TRIGGER_1;
extern I32 GAMEPAD_BUTTON_RIGHT_TRIGGER_2;
extern I32 GAMEPAD_BUTTON_MIDDLE_LEFT;
extern I32 GAMEPAD_BUTTON_MIDDLE;
extern I32 GAMEPAD_BUTTON_MIDDLE_RIGHT;
extern I32 GAMEPAD_BUTTON_LEFT_THUMB;
extern I32 GAMEPAD_BUTTON_RIGHT_THUMB;
extern I32 GAMEPAD_AXIS_LEFT_X;
extern I32 GAMEPAD_AXIS_LEFT_Y;
extern I32 GAMEPAD_AXIS_RIGHT_X;
extern I32 GAMEPAD_AXIS_RIGHT_Y;
extern I32 GAMEPAD_AXIS_LEFT_TRIGGER;
extern I32 GAMEPAD_AXIS_RIGHT_TRIGGER;
extern I32 MATERIAL_MAP_ALBEDO;
extern I32 MATERIAL_MAP_METALNESS;
extern I32 MATERIAL_MAP_NORMAL;
extern I32 MATERIAL_MAP_ROUGHNESS;
extern I32 MATERIAL_MAP_OCCLUSION;
extern I32 MATERIAL_MAP_EMISSION;
extern I32 MATERIAL_MAP_HEIGHT;
extern I32 MATERIAL_MAP_CUBEMAP;
extern I32 MATERIAL_MAP_IRRADIANCE;
extern I32 MATERIAL_MAP_PREFILTER;
extern I32 MATERIAL_MAP_BRDF;
extern I32 SHADER_LOC_VERTEX_POSITION;
extern I32 SHADER_LOC_VERTEX_TEXCOORD01;
extern I32 SHADER_LOC_VERTEX_TEXCOORD02;
extern I32 SHADER_LOC_VERTEX_NORMAL;
extern I32 SHADER_LOC_VERTEX_TANGENT;
extern I32 SHADER_LOC_VERTEX_COLOR;
extern I32 SHADER_LOC_MATRIX_MVP;
extern I32 SHADER_LOC_MATRIX_VIEW;
extern I32 SHADER_LOC_MATRIX_PROJECTION;
extern I32 SHADER_LOC_MATRIX_MODEL;
extern I32 SHADER_LOC_MATRIX_NORMAL;
extern I32 SHADER_LOC_VECTOR_VIEW;
extern I32 SHADER_LOC_COLOR_DIFFUSE;
extern I32 SHADER_LOC_COLOR_SPECULAR;
extern I32 SHADER_LOC_COLOR_AMBIENT;
extern I32 SHADER_LOC_MAP_ALBEDO;
extern I32 SHADER_LOC_MAP_METALNESS;
extern I32 SHADER_LOC_MAP_NORMAL;
extern I32 SHADER_LOC_MAP_ROUGHNESS;
extern I32 SHADER_LOC_MAP_OCCLUSION;
extern I32 SHADER_LOC_MAP_EMISSION;
extern I32 SHADER_LOC_MAP_HEIGHT;
extern I32 SHADER_LOC_MAP_CUBEMAP;
extern I32 SHADER_LOC_MAP_IRRADIANCE;
extern I32 SHADER_LOC_MAP_PREFILTER;
extern I32 SHADER_LOC_MAP_BRDF;
extern I32 SHADER_LOC_VERTEX_BONEIDS;
extern I32 SHADER_LOC_VERTEX_BONEWEIGHTS;
extern I32 SHADER_LOC_MATRIX_BONETRANSFORMS;
extern I32 SHADER_LOC_VERTEX_INSTANCETRANSFORM;
extern I32 SHADER_UNIFORM_FLOAT;
extern I32 SHADER_UNIFORM_VEC2;
extern I32 SHADER_UNIFORM_VEC3;
extern I32 SHADER_UNIFORM_VEC4;
extern I32 SHADER_UNIFORM_INT;
extern I32 SHADER_UNIFORM_IVEC2;
extern I32 SHADER_UNIFORM_IVEC3;
extern I32 SHADER_UNIFORM_IVEC4;
extern I32 SHADER_UNIFORM_UINT;
extern I32 SHADER_UNIFORM_UIVEC2;
extern I32 SHADER_UNIFORM_UIVEC3;
extern I32 SHADER_UNIFORM_UIVEC4;
extern I32 SHADER_UNIFORM_SAMPLER2D;
extern I32 SHADER_ATTRIB_FLOAT;
extern I32 SHADER_ATTRIB_VEC2;
extern I32 SHADER_ATTRIB_VEC3;
extern I32 SHADER_ATTRIB_VEC4;
extern I32 PIXELFORMAT_UNCOMPRESSED_GRAYSCALE;
extern I32 PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA;
extern I32 PIXELFORMAT_UNCOMPRESSED_R5G6B5;
extern I32 PIXELFORMAT_UNCOMPRESSED_R8G8B8;
extern I32 PIXELFORMAT_UNCOMPRESSED_R5G5B5A1;
extern I32 PIXELFORMAT_UNCOMPRESSED_R4G4B4A4;
extern I32 PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
extern I32 PIXELFORMAT_UNCOMPRESSED_R32;
extern I32 PIXELFORMAT_UNCOMPRESSED_R32G32B32;
extern I32 PIXELFORMAT_UNCOMPRESSED_R32G32B32A32;
extern I32 PIXELFORMAT_UNCOMPRESSED_R16;
extern I32 PIXELFORMAT_UNCOMPRESSED_R16G16B16;
extern I32 PIXELFORMAT_UNCOMPRESSED_R16G16B16A16;
extern I32 PIXELFORMAT_COMPRESSED_DXT1_RGB;
extern I32 PIXELFORMAT_COMPRESSED_DXT1_RGBA;
extern I32 PIXELFORMAT_COMPRESSED_DXT3_RGBA;
extern I32 PIXELFORMAT_COMPRESSED_DXT5_RGBA;
extern I32 PIXELFORMAT_COMPRESSED_ETC1_RGB;
extern I32 PIXELFORMAT_COMPRESSED_ETC2_RGB;
extern I32 PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA;
extern I32 PIXELFORMAT_COMPRESSED_PVRT_RGB;
extern I32 PIXELFORMAT_COMPRESSED_PVRT_RGBA;
extern I32 PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA;
extern I32 PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA;
extern I32 TEXTURE_FILTER_POINT;
extern I32 TEXTURE_FILTER_BILINEAR;
extern I32 TEXTURE_FILTER_TRILINEAR;
extern I32 TEXTURE_FILTER_ANISOTROPIC_4X;
extern I32 TEXTURE_FILTER_ANISOTROPIC_8X;
extern I32 TEXTURE_FILTER_ANISOTROPIC_16X;
extern I32 TEXTURE_WRAP_REPEAT;
extern I32 TEXTURE_WRAP_CLAMP;
extern I32 TEXTURE_WRAP_MIRROR_REPEAT;
extern I32 TEXTURE_WRAP_MIRROR_CLAMP;
extern I32 CUBEMAP_LAYOUT_AUTO_DETECT;
extern I32 CUBEMAP_LAYOUT_LINE_VERTICAL;
extern I32 CUBEMAP_LAYOUT_LINE_HORIZONTAL;
extern I32 CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR;
extern I32 CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE;
extern I32 FONT_DEFAULT;
extern I32 FONT_BITMAP;
extern I32 FONT_SDF;
extern I32 BLEND_ALPHA;
extern I32 BLEND_ADDITIVE;
extern I32 BLEND_MULTIPLIED;
extern I32 BLEND_ADD_COLORS;
extern I32 BLEND_SUBTRACT_COLORS;
extern I32 BLEND_ALPHA_PREMULTIPLY;
extern I32 BLEND_CUSTOM;
extern I32 BLEND_CUSTOM_SEPARATE;
extern I32 GESTURE_NONE;
extern I32 GESTURE_TAP;
extern I32 GESTURE_DOUBLETAP;
extern I32 GESTURE_HOLD;
extern I32 GESTURE_DRAG;
extern I32 GESTURE_SWIPE_RIGHT;
extern I32 GESTURE_SWIPE_LEFT;
extern I32 GESTURE_SWIPE_UP;
extern I32 GESTURE_SWIPE_DOWN;
extern I32 GESTURE_PINCH_IN;
extern I32 GESTURE_PINCH_OUT;
extern I32 CAMERA_CUSTOM;
extern I32 CAMERA_FREE;
extern I32 CAMERA_ORBITAL;
extern I32 CAMERA_FIRST_PERSON;
extern I32 CAMERA_THIRD_PERSON;
extern I32 CAMERA_PERSPECTIVE;
extern I32 CAMERA_ORTHOGRAPHIC;
extern I32 NPATCH_NINE_PATCH;
extern I32 NPATCH_THREE_PATCH_VERTICAL;
extern I32 NPATCH_THREE_PATCH_HORIZONTAL;
extern Str BASE_VERSION;
extern Str VERSION;

