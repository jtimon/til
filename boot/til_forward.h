#pragma once
#include "ext.h"

typedef struct TilClosure TilClosure;
struct TilClosure {
    void *call;
    void *env;
    void (*drop)(void *);
};

typedef struct Mode Mode;
typedef struct Array__Dynamic Array__Dynamic;
typedef struct Str Str;
typedef struct OutOfBounds OutOfBounds;
typedef struct KeyNotFound KeyNotFound;
typedef struct Array__Str Array__Str;
typedef struct Vec__Str Vec__Str;
typedef struct Dynamic Dynamic;
typedef struct DivideByZero DivideByZero;
typedef struct IntegerOverflow IntegerOverflow;
typedef enum {
    Primitive_TAG_I16,
    Primitive_TAG_U16,
    Primitive_TAG_I8,
    Primitive_TAG_U8,
    Primitive_TAG_U32,
    Primitive_TAG_I32,
    Primitive_TAG_U64,
    Primitive_TAG_I64,
    Primitive_TAG_F32,
    Primitive_TAG_Bool
} Primitive_tag;
typedef struct Primitive Primitive;
typedef enum {
    Type_TAG_Unknown,
    Type_TAG_None,
    Type_TAG_Struct,
    Type_TAG_StructDef,
    Type_TAG_Enum,
    Type_TAG_EnumDef,
    Type_TAG_FuncDef,
    Type_TAG_FuncPtr,
    Type_TAG_Dynamic,
    Type_TAG_Custom,
    Type_TAG_Primitive,
    Type_TAG_FuncPtrSig
} Type_tag;
typedef struct Type Type;
typedef enum {
    FuncType_TAG_Func,
    FuncType_TAG_Proc,
    FuncType_TAG_Test,
    FuncType_TAG_Macro,
    FuncType_TAG_ExtFunc,
    FuncType_TAG_ExtProc,
    FuncType_TAG_LazyFunc,
    FuncType_TAG_LazyProc,
    FuncType_TAG_CoreFunc,
    FuncType_TAG_CoreProc
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
typedef struct FieldLayout FieldLayout;
typedef struct StructLayout StructLayout;
typedef struct AssignData AssignData;
typedef struct FieldAssignData FieldAssignData;
typedef struct ForInData ForInData;
typedef enum {
    Literal_TAG_Str,
    Literal_TAG_Num,
    Literal_TAG_Bool,
    Literal_TAG_Null,
    Literal_TAG_MapLit,
    Literal_TAG_SetLit
} Literal_tag;
typedef struct Literal Literal;
typedef struct MatchData MatchData;
typedef struct CaptureBlockData CaptureBlockData;
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
    NodeType_TAG_Switch,
    NodeType_TAG_Match,
    NodeType_TAG_Case,
    NodeType_TAG_NoDefaultArg,
    NodeType_TAG_Throw,
    NodeType_TAG_Catch,
    NodeType_TAG_RestPattern,
    NodeType_TAG_CaptureBlock,
    NodeType_TAG_Loc
} NodeType_tag;
typedef struct NodeType NodeType;
typedef struct Expr Expr;
typedef struct Map__I64_Str Map__I64_Str;
typedef struct Vec__Bool Vec__Bool;
typedef struct Vec__I64 Vec__I64;
typedef struct Vec__FieldLayout Vec__FieldLayout;
typedef struct Vec__Declaration Vec__Declaration;
typedef struct Vec__Expr Vec__Expr;
typedef struct Tuple Tuple;
typedef struct Vec__U32 Vec__U32;
typedef struct KwargsMap KwargsMap;
typedef struct Map__Str_Tuple Map__Str_Tuple;
typedef struct Vec__Tuple Vec__Tuple;
typedef struct File File;
typedef struct Range Range;
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
    TokenType_TAG_AmpAmp,
    TokenType_TAG_PipePipe,
    TokenType_TAG_ColonEq,
    TokenType_TAG_Ident,
    TokenType_TAG_StringTok,
    TokenType_TAG_Number,
    TokenType_TAG_Char,
    TokenType_TAG_DocComment,
    TokenType_TAG_KwMut,
    TokenType_TAG_KwConst,
    TokenType_TAG_KwOwn,
    TokenType_TAG_KwRef,
    TokenType_TAG_KwShallow,
    TokenType_TAG_KwStruct,
    TokenType_TAG_KwEnum,
    TokenType_TAG_KwNamespace,
    TokenType_TAG_KwInterface,
    TokenType_TAG_KwImplements,
    TokenType_TAG_KwFunc,
    TokenType_TAG_KwProc,
    TokenType_TAG_KwTest,
    TokenType_TAG_KwMacro,
    TokenType_TAG_KwExtFunc,
    TokenType_TAG_KwExtProc,
    TokenType_TAG_KwExtStruct,
    TokenType_TAG_KwLazyFunc,
    TokenType_TAG_KwLazyProc,
    TokenType_TAG_KwCoreFunc,
    TokenType_TAG_KwCoreProc,
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
typedef struct Map__Str_TokenType Map__Str_TokenType;
typedef struct Vec__Token Vec__Token;
typedef struct Vec__TokenType Vec__TokenType;
typedef struct priv___src_self_parser_til__Parser priv___src_self_parser_til__Parser;
typedef struct Set__Str Set__Str;
typedef struct Map__Str_Str Map__Str_Str;
typedef struct EvalHeap EvalHeap;
typedef struct TypeBinding TypeBinding;
typedef enum {
    ScopeFind_TAG_NotFound,
    ScopeFind_TAG_Found
} ScopeFind_tag;
typedef struct ScopeFind ScopeFind;
typedef struct TypeScope TypeScope;
typedef struct ImportUnit ImportUnit;
typedef struct BuilderFuncScratch BuilderFuncScratch;
typedef struct Context Context;
typedef struct Map__Str_TypeBinding Map__Str_TypeBinding;
typedef struct Map__Str_Mode Map__Str_Mode;
typedef struct Map__Str_ImportUnit Map__Str_ImportUnit;
typedef struct Map__Str_Expr Map__Str_Expr;
typedef struct Map__Str_StructLayout Map__Str_StructLayout;
typedef struct Map__Str_FuncType Map__Str_FuncType;
typedef struct Map__Str_Value Map__Str_Value;
typedef struct Vec__Dynamic Vec__Dynamic;
typedef struct Map__Str_call_Vec_Str Map__Str_call_Vec_Str;
typedef struct Map__Str_Dynamic Map__Str_Dynamic;
typedef struct Map__Str_FFIEntry Map__Str_FFIEntry;
typedef struct Map__Str_ExprPtrBox Map__Str_ExprPtrBox;
typedef struct Vec__FFITypePtrBox Vec__FFITypePtrBox;
typedef struct Vec__TypeBinding Vec__TypeBinding;
typedef struct Vec__Mode Vec__Mode;
typedef struct Vec__ImportUnit Vec__ImportUnit;
typedef struct Vec__StructLayout Vec__StructLayout;
typedef struct Vec__FuncType Vec__FuncType;
typedef struct Vec__Value Vec__Value;
typedef struct Vec__call_Vec_Str Vec__call_Vec_Str;
typedef struct Vec__FFIEntry Vec__FFIEntry;
typedef struct Vec__ExprPtrBox Vec__ExprPtrBox;
typedef struct Vec__I32 Vec__I32;
typedef struct Map__Str_I64 Map__Str_I64;
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
    Target_TAG_LinuxX86,
    Target_TAG_LinuxArm32,
    Target_TAG_LinuxRiscv32,
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
typedef struct Vec__CtorArg Vec__CtorArg;
typedef struct Vec__CoverageNode Vec__CoverageNode;
typedef struct priv___src_self_garbager_til__LocalInfo priv___src_self_garbager_til__LocalInfo;
typedef struct Vec__LocalInfo Vec__LocalInfo;
typedef struct ProgramUnit ProgramUnit;
typedef struct LoadedProgram LoadedProgram;
typedef struct priv___src_self_loader_til__DeclRef priv___src_self_loader_til__DeclRef;
typedef struct DocMeta DocMeta;
typedef struct ReplCoreDocCache ReplCoreDocCache;
typedef struct Map__Str_DeclRef Map__Str_DeclRef;
typedef struct Vec__ProgramUnit Vec__ProgramUnit;
typedef struct Vec__DeclRef Vec__DeclRef;
typedef struct priv___src_self_builder_til__CollectionInfo priv___src_self_builder_til__CollectionInfo;
typedef struct priv___src_self_builder_til__DynCallInfo priv___src_self_builder_til__DynCallInfo;
typedef struct priv___src_self_builder_til__BuildPaths priv___src_self_builder_til__BuildPaths;
typedef struct DocEntry DocEntry;
typedef struct DocCatalog DocCatalog;
typedef struct Array__Bool Array__Bool;
typedef struct Vec__DynCallInfo Vec__DynCallInfo;
typedef struct Vec__CollectionInfo Vec__CollectionInfo;
typedef struct Vec__DocEntry Vec__DocEntry;
typedef struct _ffi_type ffi_type;
typedef struct StructInstance StructInstance;
typedef struct EnumInstance EnumInstance;
typedef struct InterpClosure InterpClosure;
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
    Value_TAG_Dynamic,
    Value_TAG_Sbyte,
    Value_TAG_Ushort,
    Value_TAG_Closure
} Value_tag;
typedef struct Value Value;
typedef struct InterpCallableBox InterpCallableBox;
typedef struct Cell Cell;
typedef struct Binding Binding;
typedef struct Scope Scope;
typedef struct priv___src_self_interpreter_til__DynPtrBox priv___src_self_interpreter_til__DynPtrBox;
typedef struct priv___src_self_interpreter_til__ExtStr priv___src_self_interpreter_til__ExtStr;
typedef struct FFIEntry FFIEntry;
typedef struct ExprPtrBox ExprPtrBox;
typedef struct FFITypePtrBox FFITypePtrBox;
typedef struct Map__Str_Binding Map__Str_Binding;
typedef struct Vec__DynPtrBox Vec__DynPtrBox;
typedef struct Vec__Binding Vec__Binding;
typedef struct priv___src_self_binder_til__BinderState priv___src_self_binder_til__BinderState;
typedef struct Vector2 Vector2;
typedef struct Vector3 Vector3;
typedef struct Vector4 Vector4;
typedef struct Matrix Matrix;
typedef struct Color Color;
typedef struct Rectangle Rectangle;
typedef struct Image Image;
typedef struct Texture Texture;
typedef struct RenderTexture RenderTexture;
typedef struct NPatchInfo NPatchInfo;
typedef struct GlyphInfo GlyphInfo;
typedef struct Font Font;
typedef struct Camera3D Camera3D;
typedef struct Camera2D Camera2D;
typedef struct Mesh Mesh;
typedef struct Shader Shader;
typedef struct MaterialMap MaterialMap;
typedef struct Material Material;
typedef struct Transform Transform;
typedef struct BoneInfo BoneInfo;
typedef struct ModelSkeleton ModelSkeleton;
typedef struct Model Model;
typedef struct ModelAnimation ModelAnimation;
typedef struct Ray Ray;
typedef struct RayCollision RayCollision;
typedef struct BoundingBox BoundingBox;
typedef struct Wave Wave;
typedef struct rAudioBuffer rAudioBuffer;
typedef struct rAudioProcessor rAudioProcessor;
typedef struct AudioStream AudioStream;
typedef struct Sound Sound;
typedef struct Music Music;
typedef struct VrDeviceInfo VrDeviceInfo;
typedef struct VrStereoConfig VrStereoConfig;
typedef struct FilePathList FilePathList;
typedef struct AutomationEvent AutomationEvent;
typedef struct AutomationEventList AutomationEventList;
typedef struct nng_ctx_s nng_ctx;
typedef struct nng_dialer_s nng_dialer;
typedef struct nng_listener_s nng_listener;
typedef struct nng_pipe_s nng_pipe;
typedef struct nng_socket_s nng_socket;
typedef struct nng_msg nng_msg;
typedef struct nng_stat nng_stat;
typedef struct nng_aio nng_aio;
typedef struct nng_sockaddr_inproc nng_sockaddr_inproc;
typedef struct nng_sockaddr_path nng_sockaddr_path;
typedef struct nng_sockaddr_ipc nng_sockaddr_ipc;
typedef struct nng_sockaddr_in nng_sockaddr_in;
typedef struct nng_sockaddr_in6 nng_sockaddr_in6;
typedef struct nng_sockaddr_zt nng_sockaddr_zt;
typedef struct nng_sockaddr_abstract nng_sockaddr_abstract;
typedef struct nng_sockaddr_storage nng_sockaddr_storage;
typedef struct nng_iov nng_iov;
typedef struct nng_url nng_url;
typedef struct nng_stream nng_stream;
typedef struct nng_stream_dialer nng_stream_dialer;
typedef struct nng_stream_listener nng_stream_listener;
typedef struct nng_udp nng_udp;
typedef struct nng_thread nng_thread;
typedef struct nng_mtx nng_mtx;
typedef struct nng_cv nng_cv;
typedef struct CliArgs CliArgs;

typedef TilClosure *HashFn;
typedef TilClosure *priv___src_self_interpreter_til__DispatchFn;

typedef struct Array__Dynamic {
    U8 *data;
    U32 cap;
} Array__Dynamic;


typedef struct Str {
    I8 *c_str;
    U32 count;
    U32 cap;
} Str;


typedef struct OutOfBounds {
    Str msg;
} OutOfBounds;


typedef struct KeyNotFound {
    Str msg;
} KeyNotFound;


typedef struct Array__Str {
    U8 *data;
    U32 cap;
} Array__Str;


typedef struct Vec__Str {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__Str;


typedef struct Dynamic {
    char _;
} Dynamic;











typedef struct DivideByZero {
    Str msg;
} DivideByZero;


typedef struct IntegerOverflow {
    Str msg;
} IntegerOverflow;



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
        Str FuncPtrSig;
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
    Bool redundant_mut;
    Bool is_priv;
    Bool used;
    OwnType own_type;
    Type til_type;
    Expr *default_value;
    Str orig_name;
} Declaration;


typedef struct FCallData {
    Bool is_splat;
    Bool does_throw;
    Bool is_bang;
    U64 own_args;
    Bool swap_replace;
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


typedef struct FieldLayout {
    U32 offset;
    U32 size;
    Str struct_name;
    OwnType own_type;
    Bool is_str;
    Bool is_enum;
    Bool is_funcptr;
} FieldLayout;


typedef struct AssignData {
    Str name;
    Bool save_old_delete;
    Bool is_payload_alias;
    Bool swap_replace;
} AssignData;


typedef struct FieldAssignData {
    Str name;
    Bool save_old_delete;
} FieldAssignData;


typedef struct ForInData {
    Str name;
    Bool is_mut;
    Type til_type;
    Str name2;
    Bool is_mut2;
} ForInData;


struct Literal {
    Literal_tag tag;
    union {
        Str Str;
        LiteralNumData Num;
        Bool Bool;
    } data;
};

typedef struct MatchData {
    Type til_type;
    Str result_temp;
} MatchData;


typedef struct Vec__Bool {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__Bool;


typedef struct Vec__I64 {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__I64;


typedef struct Vec__FieldLayout {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__FieldLayout;


typedef struct Vec__Declaration {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__Declaration;


typedef struct Vec__Expr {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__Expr;


typedef struct Vec__U32 {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__U32;


typedef struct Vec__Tuple {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__Tuple;


typedef struct File {
    U8 *handle;
    Bool is_write;
    Bool is_update;
} File;


typedef struct Range {
    U64 start;
    U64 end;
} Range;


struct TokenType {
    TokenType_tag tag;
};

typedef struct Token {
    TokenType type;
    U32 start;
    U32 len;
    U32 line;
    U32 col;
} Token;


typedef struct Vec__Token {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__Token;


typedef struct Vec__TokenType {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__TokenType;


typedef struct Set__Str {
    U8 *data;
    U32 count;
    U32 cap;
} Set__Str;


typedef struct Map__Str_Str {
    Vec__Str keys;
    Vec__Str values;
} Map__Str_Str;


typedef struct EvalHeap {
    U8 unused;
} EvalHeap;


typedef struct TypeBinding {
    Str name;
    Type type;
    Bool is_mut;
    Bool is_priv;
    Str path;
    U32 line;
    U32 col;
    Bool is_param;
    OwnType own_type;
    Bool is_alias;
    Bool is_type_alias;
    Bool is_func_decl;
    Str alias_target;
    FuncType func_type;
    Bool is_builtin;
    Bool used;
    Bool written;
    Bool mut_explicit;
    Str orig_name;
} TypeBinding;


struct ScopeFind {
    ScopeFind_tag tag;
    union {
        TypeBinding Found;
    } data;
};

typedef struct Map__Str_Expr {
    Vec__Str keys;
    Vec__Expr values;
} Map__Str_Expr;


typedef struct Vec__Dynamic {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__Dynamic;


typedef struct Map__Str_Dynamic {
    Vec__Str keys;
    Vec__Dynamic values;
} Map__Str_Dynamic;


typedef struct Vec__FFITypePtrBox {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__FFITypePtrBox;


typedef struct Vec__TypeBinding {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__TypeBinding;


typedef struct Vec__Mode {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__Mode;


typedef struct Vec__ImportUnit {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__ImportUnit;


typedef struct Vec__StructLayout {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__StructLayout;


typedef struct Vec__FuncType {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__FuncType;


typedef struct Vec__Value {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__Value;


typedef struct Vec__call_Vec_Str {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__call_Vec_Str;


typedef struct Vec__FFIEntry {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__FFIEntry;


typedef struct Vec__ExprPtrBox {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__ExprPtrBox;


typedef struct Vec__I32 {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__I32;


typedef struct Map__Str_I64 {
    Vec__Str keys;
    Vec__I64 values;
} Map__Str_I64;


struct Lang {
    Lang_tag tag;
};

struct Target {
    Target_tag tag;
};

typedef struct Vec__CtorArg {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__CtorArg;


typedef struct Vec__CoverageNode {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__CoverageNode;


typedef struct priv___src_self_garbager_til__LocalInfo {
    Str *name;
    Type type;
    I32 decl_index;
    I32 last_use;
    I32 own_transfer;
    Bool skip_scope_delete;
    Bool is_heap;
} priv___src_self_garbager_til__LocalInfo;


typedef struct Vec__LocalInfo {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__LocalInfo;


typedef struct priv___src_self_loader_til__DeclRef {
    Str path;
    U32 idx;
} priv___src_self_loader_til__DeclRef;


typedef struct DocMeta {
    Str body;
    Str group;
    Str since;
    Str deprecated;
    Bool hidden;
} DocMeta;


typedef struct ReplCoreDocCache {
    Str escaped_info;
    Str escaped_docs;
} ReplCoreDocCache;


typedef struct Vec__ProgramUnit {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__ProgramUnit;


typedef struct Vec__DeclRef {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__DeclRef;


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


typedef struct DocEntry {
    Str name;
    Str id;
    Str unit_path;
    Str group;
    Str page;
    Str body;
    Str info;
    Str since;
    Str deprecated;
} DocEntry;


typedef struct Array__Bool {
    U8 *data;
    U32 cap;
} Array__Bool;


typedef struct Vec__DynCallInfo {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__DynCallInfo;


typedef struct Vec__CollectionInfo {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__CollectionInfo;


typedef struct Vec__DocEntry {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__DocEntry;


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


typedef struct {
    char _;
} ffi_closure;


typedef struct {
    char _;
} ffi_raw_closure;


typedef struct {
    char _;
} ffi_java_raw_closure;


typedef struct {
    char _;
} ffi_go_closure;


typedef struct StructInstance {
    Str *struct_name;
    Bool is_str;
    Bool is_str_container;
    Context *ctx;
    U8 *data;
    Bool borrowed;
} StructInstance;


typedef struct EnumInstance {
    Str *enum_name;
    U8 *data;
    U32 data_size;
    Bool borrowed;
    Bool is_str;
} EnumInstance;


typedef struct InterpClosure {
    Expr *func_def;
    Scope *env;
    Bool borrowed;
} InterpClosure;


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
        I8 Sbyte;
        U16 Ushort;
        InterpClosure Closure;
    } data;
};

typedef struct InterpCallableBox {
    U64 magic;
    Value val;
} InterpCallableBox;


typedef struct Cell {
    Value val;
} Cell;


typedef struct Binding {
    Str *name;
    Cell *cell;
    Bool cell_is_local;
} Binding;


typedef struct priv___src_self_interpreter_til__DynPtrBox {
    U8 *p;
} priv___src_self_interpreter_til__DynPtrBox;


typedef struct priv___src_self_interpreter_til__ExtStr {
    U8 *data;
    U32 count;
    U32 cap;
} priv___src_self_interpreter_til__ExtStr;


typedef struct FFIEntry {
    U8 *fn;
    Str *return_type;
    U32 nparam;
    U8 *param_shallows;
    Bool return_is_shallow;
    Bool return_is_ref;
    ffi_cif *cif;
    void * *arg_types;
} FFIEntry;


typedef struct ExprPtrBox {
    Expr *ptr;
} ExprPtrBox;


typedef struct FFITypePtrBox {
    ffi_type *ptr;
} FFITypePtrBox;


typedef struct Vec__DynPtrBox {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__DynPtrBox;


typedef struct Vec__Binding {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__Binding;


typedef struct priv___src_self_binder_til__BinderState {
    Str alias_to_primitive;
    Str alias_to_dynamic;
} priv___src_self_binder_til__BinderState;


typedef struct Vector2 {
    F32 x;
    F32 y;
} Vector2;


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


typedef struct Matrix {
    char _;
} Matrix;


typedef struct Color {
    U8 r;
    U8 g;
    U8 b;
    U8 a;
} Color;


typedef struct Rectangle {
    F32 x;
    F32 y;
    F32 width;
    F32 height;
} Rectangle;


typedef struct Image {
    void * *data;
    I32 width;
    I32 height;
    I32 mipmaps;
    I32 format;
} Image;


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


typedef struct NPatchInfo {
    Rectangle source;
    I32 left;
    I32 top;
    I32 right;
    I32 bottom;
    I32 layout;
} NPatchInfo;


typedef struct GlyphInfo {
    I32 value;
    I32 offsetX;
    I32 offsetY;
    I32 advanceX;
    Image image;
} GlyphInfo;


typedef struct Font {
    I32 baseSize;
    I32 glyphCount;
    I32 glyphPadding;
    Texture texture;
    Rectangle *recs;
    GlyphInfo *glyphs;
} Font;


typedef struct Camera3D {
    Vector3 position;
    Vector3 target;
    Vector3 up;
    F32 fovy;
    I32 projection;
} Camera3D;


typedef struct Camera2D {
    Vector2 offset;
    Vector2 target;
    F32 rotation;
    F32 zoom;
} Camera2D;


typedef struct Mesh {
    I32 vertexCount;
    I32 triangleCount;
    F32 *vertices;
    F32 *texcoords;
    F32 *texcoords2;
    F32 *normals;
    F32 *tangents;
    U8 *colors;
    I16 *indices;
    I32 boneCount;
    U8 *boneIndices;
    F32 *boneWeights;
    F32 *animVertices;
    F32 *animNormals;
    U32 vaoId;
    U32 *vboId;
} Mesh;


typedef struct Shader {
    U32 id;
    I32 *locs;
} Shader;


typedef struct MaterialMap {
    Texture texture;
    Color color;
    F32 value;
} MaterialMap;


typedef struct Material {
    char _;
} Material;


typedef struct Transform {
    Vector3 translation;
    Vector4 rotation;
    Vector3 scale;
} Transform;


typedef struct BoneInfo {
    char _;
} BoneInfo;


typedef struct ModelSkeleton {
    I32 boneCount;
    BoneInfo *bones;
    void * *bindPose;
} ModelSkeleton;


typedef struct Model {
    Matrix transform;
    I32 meshCount;
    I32 materialCount;
    Mesh *meshes;
    Material *materials;
    I32 *meshMaterial;
    ModelSkeleton skeleton;
    void * *currentPose;
    Matrix *boneMatrices;
} Model;


typedef struct ModelAnimation {
    char _;
} ModelAnimation;


typedef struct Ray {
    Vector3 position;
    Vector3 direction;
} Ray;


typedef struct RayCollision {
    Bool hit;
    F32 distance;
    Vector3 point;
    Vector3 normal;
} RayCollision;


typedef struct BoundingBox {
    Vector3 min;
    Vector3 max;
} BoundingBox;


typedef struct Wave {
    U32 frameCount;
    U32 sampleRate;
    U32 sampleSize;
    U32 channels;
    void * *data;
} Wave;


typedef struct rAudioBuffer {
    char _;
} rAudioBuffer;


typedef struct rAudioProcessor {
    char _;
} rAudioProcessor;


typedef struct AudioStream {
    rAudioBuffer *buffer;
    rAudioProcessor *processor;
    U32 sampleRate;
    U32 sampleSize;
    U32 channels;
} AudioStream;


typedef struct Sound {
    AudioStream stream;
    U32 frameCount;
} Sound;


typedef struct Music {
    AudioStream stream;
    U32 frameCount;
    Bool looping;
    I32 ctxType;
    void * *ctxData;
} Music;


typedef struct VrDeviceInfo {
    char _;
} VrDeviceInfo;


typedef struct VrStereoConfig {
    char _;
} VrStereoConfig;


typedef struct FilePathList {
    U32 count;
    void * *paths;
} FilePathList;


typedef struct AutomationEvent {
    char _;
} AutomationEvent;


typedef struct AutomationEventList {
    U32 capacity;
    U32 count;
    AutomationEvent *events;
} AutomationEventList;


typedef struct nng_ctx_s {
    U32 id;
} nng_ctx;


typedef struct nng_dialer_s {
    U32 id;
} nng_dialer;


typedef struct nng_listener_s {
    U32 id;
} nng_listener;


typedef struct nng_pipe_s {
    U32 id;
} nng_pipe;


typedef struct nng_socket_s {
    U32 id;
} nng_socket;


typedef struct nng_msg {
    char _;
} nng_msg;


typedef struct nng_stat {
    char _;
} nng_stat;


typedef struct nng_aio {
    char _;
} nng_aio;


typedef struct nng_sockaddr_inproc {
    char _;
} nng_sockaddr_inproc;


typedef struct nng_sockaddr_path {
    char _;
} nng_sockaddr_path;


typedef struct nng_sockaddr_ipc {
    char _;
} nng_sockaddr_ipc;


typedef struct nng_sockaddr_in {
    char _;
} nng_sockaddr_in;


typedef struct nng_sockaddr_in6 {
    char _;
} nng_sockaddr_in6;


typedef struct nng_sockaddr_zt {
    char _;
} nng_sockaddr_zt;


typedef struct nng_sockaddr_abstract {
    char _;
} nng_sockaddr_abstract;


typedef struct nng_sockaddr_storage {
    char _;
} nng_sockaddr_storage;


typedef struct nng_iov {
    void * *iov_buf;
    U32 iov_len;
} nng_iov;


typedef struct nng_url {
    I8 *u_rawurl;
    I8 *u_scheme;
    I8 *u_userinfo;
    I8 *u_host;
    I8 *u_hostname;
    I8 *u_port;
    I8 *u_path;
    I8 *u_query;
    I8 *u_fragment;
    I8 *u_requri;
} nng_url;


typedef struct nng_stream {
    char _;
} nng_stream;


typedef struct nng_stream_dialer {
    char _;
} nng_stream_dialer;


typedef struct nng_stream_listener {
    char _;
} nng_stream_listener;


typedef struct nng_udp {
    char _;
} nng_udp;


typedef struct nng_thread {
    char _;
} nng_thread;


typedef struct nng_mtx {
    char _;
} nng_mtx;


typedef struct nng_cv {
    char _;
} nng_cv;


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
    Bool prof;
    Vec__Str *extra_modes;
} CliArgs;


typedef struct Mode {
    Bool needs_main;
    Bool decls_only;
    Str auto_import;
    Bool is_library;
    Bool is_pure;
    Bool run_tests;
    Bool debug_prints;
} Mode;


typedef struct FunctionDef {
    FuncType func_type;
    Vec__Declaration params;
    Str return_type;
    Vec__Str throw_types;
    I32 variadic_index;
    I32 kwargs_index;
    OwnType return_own_type;
    Bool auto_generated;
    Bool is_enum_variant_ctor;
    Vec__Declaration captures;
    Str closure_name;
} FunctionDef;


typedef struct StructDef {
    Vec__Declaration fields;
    Vec__Declaration ns_decls;
    Str c_tag;
    Bool is_interface;
    Bool interface_ns_marker;
    Str implements_name;
} StructDef;


typedef struct StructLayout {
    U32 total_size;
    U32 align;
    Vec__FieldLayout fields;
} StructLayout;


typedef struct CaptureBlockData {
    Vec__Declaration captures;
} CaptureBlockData;


typedef struct Map__I64_Str {
    Vec__I64 keys;
    Vec__Str values;
} Map__I64_Str;


typedef struct Tuple {
    U8 *data;
    U32 total_size;
    U32 cap;
    Vec__Str type_names;
    Vec__U32 type_sizes;
} Tuple;


typedef struct Map__Str_Tuple {
    Vec__Str keys;
    Vec__Tuple values;
} Map__Str_Tuple;


typedef struct Map__Str_TokenType {
    Vec__Str keys;
    Vec__TokenType values;
} Map__Str_TokenType;


typedef struct priv___src_self_parser_til__Parser {
    Vec__Token tokens;
    U32 pos;
    Str path;
    Vec__Expr fn_sig_decls;
    Vec__Expr type_gen_decls;
    Set__Str type_gen_seen;
    Vec__Str active_type_params;
    Vec__Expr anon_decls;
    Map__Str_Str anon_cache;
    I64 anon_type_counter;
    Str pending_doc;
    Str source;
} priv___src_self_parser_til__Parser;


typedef struct ImportUnit {
    Str mode_str;
    Mode mode;
    Expr *ast;
    Vec__Str imports;
} ImportUnit;


typedef struct BuilderFuncScratch {
    Map__Str_Dynamic local_fn_sigs;
    Set__Str stack_locals;
    Map__Str_Str stack_local_types;
    Set__Str stack_lit_str_locals;
    Bool force_heap_stack_lit_str_own;
    Set__Str unsafe_to_hoist;
    Set__Str ref_locals;
    Set__Str ref_dyn_locals;
    Set__Str ptr_locals;
} BuilderFuncScratch;


typedef struct Map__Str_TypeBinding {
    Vec__Str keys;
    Vec__TypeBinding values;
} Map__Str_TypeBinding;


typedef struct Map__Str_Mode {
    Vec__Str keys;
    Vec__Mode values;
} Map__Str_Mode;


typedef struct Map__Str_ImportUnit {
    Vec__Str keys;
    Vec__ImportUnit values;
} Map__Str_ImportUnit;


typedef struct Map__Str_StructLayout {
    Vec__Str keys;
    Vec__StructLayout values;
} Map__Str_StructLayout;


typedef struct Map__Str_FuncType {
    Vec__Str keys;
    Vec__FuncType values;
} Map__Str_FuncType;


typedef struct Map__Str_Value {
    Vec__Str keys;
    Vec__Value values;
} Map__Str_Value;


typedef struct Map__Str_call_Vec_Str {
    Vec__Str keys;
    Vec__call_Vec_Str values;
} Map__Str_call_Vec_Str;


typedef struct Map__Str_FFIEntry {
    Vec__Str keys;
    Vec__FFIEntry values;
} Map__Str_FFIEntry;


typedef struct Map__Str_ExprPtrBox {
    Vec__Str keys;
    Vec__ExprPtrBox values;
} Map__Str_ExprPtrBox;


typedef struct priv___src_self_typer_til__CoverageNode {
    Bool fully_covered;
    Vec__Str sub_names;
    Vec__CoverageNode sub_nodes;
} priv___src_self_typer_til__CoverageNode;


typedef struct ProgramUnit {
    Str path;
    Mode mode;
    Vec__Str imports;
} ProgramUnit;


typedef struct Map__Str_DeclRef {
    Vec__Str keys;
    Vec__DeclRef values;
} Map__Str_DeclRef;


typedef struct DocCatalog {
    Vec__DocEntry entries;
} DocCatalog;


typedef struct Map__Str_Binding {
    Vec__Str keys;
    Vec__Binding values;
} Map__Str_Binding;


typedef struct EnumDef {
    Vec__Declaration ns_decls;
    Vec__Str variants;
    Map__I64_Str payload_types;
    Vec__Bool payload_consts;
    Str implements_name;
    Str tag_type;
    Vec__I64 tag_values;
} EnumDef;


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
        MatchData Match;
        CaptureBlockData CaptureBlock;
    } data;
};

typedef struct Expr {
    NodeType node_type;
    Vec__Expr children;
    U32 line;
    U32 col;
} Expr;


typedef struct KwargsMap {
    Map__Str_Tuple items;
} KwargsMap;


typedef struct TypeScope {
    Map__Str_TypeBinding bindings;
    Str target_usize_pname;
    Str target_uptr_pname;
    Map__Str_Dynamic func_defs;
    Map__Str_Dynamic struct_defs;
    TypeScope *parent;
} TypeScope;


typedef struct Context {
    Mode mode;
    Str path;
    Map__Str_Mode path_modes;
    Map__Str_Mode mode_registry;
    EvalHeap eval_heap;
    Str target_usize_pname;
    Str target_uptr_pname;
    I64 anon_type_counter;
    Bool compile_mode;
    Map__Str_ImportUnit imported;
    Set__Str imports_init_seed_done;
    Set__Str imports_init_active;
    Set__Str imports_init_done;
    Set__Str imports_typer_decls_done;
    Set__Str imports_typer_bodies_done;
    Set__Str type_gen_synths;
    Map__Str_Expr generic_funcs;
    Set__Str generic_func_synths;
    TypeScope scope;
    Bool is_repl;
    Map__Str_StructLayout struct_layouts;
    Map__Str_FuncType constfolder_foldables;
    Map__Str_Value constfolder_known;
    Set__Str constfolder_assigned;
    Bool has_return;
    Bool has_break;
    Bool has_continue;
    Value return_value;
    Bool constfold_active;
    Bool constfold_aborted;
    Map__Str_Value ns_fields;
    Vec__Dynamic ns_keys;
    Bool ns_inited;
    Bool typing_namespace_member;
    Str closure_emit_env;
    Set__Str closure_emit_captures;
    Map__Str_Dynamic func_defs;
    Map__Str_Dynamic struct_def_exprs;
    Set__Str funcsig_names;
    Set__Str closure_value_names;
    Set__Str script_globals;
    Set__Str ref_globals;
    Vec__Str throw_type_registry;
    Map__Str_call_Vec_Str throws_global;
    I64 bang_counter;
    Map__Str_Str lowering_param_types;
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
    Set__Str throw_used_local_names;
    BuilderFuncScratch builder_func;
    Map__Str_Str builder_str_lit_symbols;
    Vec__Str builder_str_lit_values;
    Map__Str_Str builder_str_lit_alias_symbols;
    Vec__Str builder_str_lit_alias_names;
    Set__Str swap_freed;
    Expr *current_fdef;
    Expr *cached_str_def;
    Str *cached_str_name;
    Expr *cached_array_def;
    Str *cached_array_name;
    Expr *cached_vec_def;
    Str *cached_vec_name;
    Map__Str_Dynamic interp_type_defs;
    Map__Str_Dynamic dispatch_map;
    Bool dispatch_inited;
    Map__Str_FFIEntry ffi_map;
    Bool ffi_map_inited;
    Bool ffi_loaded;
    Map__Str_ExprPtrBox ffi_struct_defs;
    Vec__FFITypePtrBox ffi_type_cache;
    Bool ffi_type_cache_inited;
} Context;


struct priv___src_self_typer_til__CtorArg {
    priv___src_self_typer_til__CtorArg_tag tag;
    union {
        Expr Filled;
    } data;
};

typedef struct LoadedProgram {
    Vec__ProgramUnit *core_units;
    Vec__ProgramUnit *units;
    Vec__Str mode_files;
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
    Map__Str_Binding bindings;
    Map__Str_Dynamic heap_index;
    Scope *parent;
    Map__Str_Str payload_aliases;
    Map__Str_Dynamic ref_primitive_ptrs;
    Vec__DynPtrBox box_owned_dynamics;
    Vec__DynPtrBox box_owned_callables;
} Scope;


Mode * Mode_clone(Mode * self);
void Mode_delete(Mode * self, Bool call_free);
U64 Mode_hash(Mode * self, HashFn hasher);
U32 Mode_size(void);
void Array__Dynamic_delete(Array__Dynamic * self, Bool call_free);
Array__Dynamic * Array__Dynamic_clone(Array__Dynamic * self);
U32 Array__Dynamic_size(void);
Str * format(Array__Str * parts);
Str * concat3(Str * a, Str * b, Str * c);
U32 Str_len(Str * self);
I8 * Str_get(Str * self, U32 * i);
I8 * Str_unsafe_get(Str * self, U32 * i);
I64 Str_cmp(Str * a, Str * b);
Str * Str_with_capacity(U32 n);
Str * Str_from_c_str(void * s);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
void Str_delete(Str * self, Bool call_free);
Str * Str_substr(Str * s, U32 start, U32 n);
Str * Str_trim(Str * s);
Bool Str_contains(Str * a, Str * b);
Bool Str_starts_with(Str * a, Str * b);
Bool Str_ends_with(Str * a, Str * b);
Bool Str_is_empty(Str * self);
I64 Str_find(Str * self, Str * needle);
I64 Str_rfind(Str * self, Str * needle);
Str * Str_replace(Str * self, Str * from, Str * to);
U64 Str_hash(Str * self, HashFn hasher);
Str * Str_strip_prefix(Str * self, Str * prefix);
Str * Str_strip_suffix(Str * self, Str * suffix);
Str * Str_from_byte(U8 byte);
I64 Str_to_i64(Str * self);
U8 Str_to_u8(Str * self);
I8 Str_to_i8(Str * self);
I16 Str_to_i16(Str * self);
U16 Str_to_u16(Str * self);
I32 Str_to_i32(Str * self);
U32 Str_to_u32(Str * self);
U64 Str_to_u64(Str * self);
U32 Str_to_usize(Str * self);
F32 Str_to_f32(Str * self);
Vec__Str * Str_split(Str * self, Str * delim);
U32 Str_size(void);
Bool Str_eq(Str * a, Str * b);
I64 digit_value(I8 ch);
U32 c_str_len(void * s);
OutOfBounds * OutOfBounds_clone(OutOfBounds * self);
void OutOfBounds_delete(OutOfBounds * self, Bool call_free);
U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher);
U32 OutOfBounds_size(void);
KeyNotFound * KeyNotFound_clone(KeyNotFound * self);
void KeyNotFound_delete(KeyNotFound * self, Bool call_free);
U64 KeyNotFound_hash(KeyNotFound * self, HashFn hasher);
U32 KeyNotFound_size(void);
Array__Str * Array__Str_new(U32 cap);
U32 Array__Str_len(Array__Str * self);
Str * Array__Str_unsafe_get(Array__Str * self, U32 * i);
Str * Array__Str_get(Array__Str * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
void Array__Str_unsafe_set(Array__Str * self, U32 i, Str * val);
void Array__Str_set(Array__Str * self, U32 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
void Array__Str_delete(Array__Str * self, Bool call_free);
Array__Str * Array__Str_clone(Array__Str * self);
U32 Array__Str_size(void);
Vec__Str * Vec__Str_new(void);
U32 Vec__Str_len(Vec__Str * self);
void Vec__Str_clear(Vec__Str * self);
void Vec__Str_push(Vec__Str * self, Str * val);
void Vec__Str_move_from(Vec__Str * self, Vec__Str * other);
Str * Vec__Str_unsafe_get(Vec__Str * self, U32 * i);
Str * Vec__Str_get(Vec__Str * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
Str * Vec__Str_pop(Vec__Str * self);
void Vec__Str_unsafe_set(Vec__Str * self, U32 i, Str * val);
void Vec__Str_set(Vec__Str * self, U32 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
void Vec__Str_delete(Vec__Str * self, Bool call_free);
Vec__Str * Vec__Str_clone(Vec__Str * self);
U32 Vec__Str_size(void);
U32 Dynamic_size(void);
void * Dynamic_clone(void * self);
void Dynamic_delete(void * self, Bool call_free);
Str * U8_to_str(U8 val);
void U8_delete(U8 * self, Bool call_free);
U32 U8_size(void);
U64 U8_hash(U8 self, HashFn hasher);
Str * U16_to_str(U16 val);
void U16_delete(U16 * self, Bool call_free);
U32 U16_size(void);
U64 U16_hash(U16 self, HashFn hasher);
Str * U32_to_str(U32 val);
void U32_inc(U32 * self);
void U32_dec(U32 * self);
void U32_delete(U32 * self, Bool call_free);
U32 U32_size(void);
U64 U32_hash(U32 self, HashFn hasher);
Str * U64_to_str(U64 val);
void U64_inc(U64 * self);
void U64_dec(U64 * self);
void U64_delete(U64 * self, Bool call_free);
U32 U64_size(void);
U64 U64_hash(U64 self, HashFn hasher);
Str * I8_to_str(I8 val);
void I8_delete(I8 * self, Bool call_free);
U32 I8_size(void);
U64 I8_hash(I8 self, HashFn hasher);
Str * I16_to_str(I16 val);
void I16_delete(I16 * self, Bool call_free);
U32 I16_size(void);
U64 I16_hash(I16 self, HashFn hasher);
Str * I32_to_str(I32 val);
void I32_inc(I32 * self);
void I32_dec(I32 * self);
void I32_delete(I32 * self, Bool call_free);
U32 I32_size(void);
U64 I32_hash(I32 self, HashFn hasher);
Str * I64_to_str(I64 val);
void I64_inc(I64 * self);
void I64_dec(I64 * self);
void I64_delete(I64 * self, Bool call_free);
U32 I64_size(void);
U64 I64_hash(I64 self, HashFn hasher);
void F32_delete(F32 * self, Bool call_free);
U32 F32_size(void);
U64 F32_hash(F32 self, HashFn hasher);
DivideByZero * DivideByZero_clone(DivideByZero * self);
void DivideByZero_delete(DivideByZero * self, Bool call_free);
U64 DivideByZero_hash(DivideByZero * self, HashFn hasher);
U32 DivideByZero_size(void);
IntegerOverflow * IntegerOverflow_clone(IntegerOverflow * self);
void IntegerOverflow_delete(IntegerOverflow * self, Bool call_free);
U64 IntegerOverflow_hash(IntegerOverflow * self, HashFn hasher);
U32 IntegerOverflow_size(void);
Bool and(Bool a, Bool b);
Bool or(Bool a, Bool b);
I64 Bool_cmp(Bool a, Bool b);
void Bool_delete(Bool * self, Bool call_free);
U32 Bool_size(void);
U64 Bool_hash(Bool self, HashFn hasher);
Bool Primitive_is(Primitive * self, Primitive * other);
Bool Primitive_eq(Primitive * self, Primitive * other);
void Primitive_delete(Primitive * self, Bool call_free);
Primitive * Primitive_clone(Primitive * self);
U32 Primitive_size(void);
Bool Type_is(Type * self, Type * other);
Bool Type_eq(Type * self, Type * other);
void Type_delete(Type * self, Bool call_free);
Type * Type_clone(Type * self);
U32 Type_size(void);
Str * til_type_name_c(Type * t);
Str * til_type_name(Type * t);
Bool is_primitive(Type * t);
Bool is_funcptr(Type * t);
Bool is_aggregate(Type * t);
Bool FuncType_is(FuncType * self, FuncType * other);
Bool FuncType_eq(FuncType * self, FuncType * other);
void FuncType_delete(FuncType * self, Bool call_free);
FuncType * FuncType_clone(FuncType * self);
U32 FuncType_size(void);
Bool OwnType_is(OwnType * self, OwnType * other);
Bool OwnType_eq(OwnType * self, OwnType * other);
void OwnType_delete(OwnType * self, Bool call_free);
OwnType * OwnType_clone(OwnType * self);
U32 OwnType_size(void);
Declaration * Declaration_clone(Declaration * self);
void Declaration_delete(Declaration * self, Bool call_free);
U32 Declaration_size(void);
FunctionDef * FunctionDef_clone(FunctionDef * self);
void FunctionDef_delete(FunctionDef * self, Bool call_free);
U64 FunctionDef_hash(FunctionDef * self, HashFn hasher);
U32 FunctionDef_size(void);
FCallData * FCallData_clone(FCallData * self);
void FCallData_delete(FCallData * self, Bool call_free);
U64 FCallData_hash(FCallData * self, HashFn hasher);
U32 FCallData_size(void);
I64 LiteralNumData_to_i64(LiteralNumData * self);
U8 LiteralNumData_to_u8(LiteralNumData * self);
I8 LiteralNumData_to_i8(LiteralNumData * self);
I16 LiteralNumData_to_i16(LiteralNumData * self);
U16 LiteralNumData_to_u16(LiteralNumData * self);
I32 LiteralNumData_to_i32(LiteralNumData * self);
U32 LiteralNumData_to_u32(LiteralNumData * self);
U64 LiteralNumData_to_u64(LiteralNumData * self);
F32 LiteralNumData_to_f32(LiteralNumData * self);
LiteralNumData * LiteralNumData_clone(LiteralNumData * self);
void LiteralNumData_delete(LiteralNumData * self, Bool call_free);
U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher);
U32 LiteralNumData_size(void);
U32 IdentData_len(IdentData * self);
Bool IdentData_starts_with(IdentData * self, Str * prefix);
I8 * IdentData_unsafe_get(IdentData * self, U32 * i);
I8 * IdentData_get(IdentData * self, U32 * i);
IdentData * IdentData_clone(IdentData * self);
void IdentData_delete(IdentData * self, Bool call_free);
U64 IdentData_hash(IdentData * self, HashFn hasher);
U32 IdentData_size(void);
Bool FieldAccessData_starts_with(FieldAccessData * self, Str * prefix);
FieldAccessData * FieldAccessData_clone(FieldAccessData * self);
void FieldAccessData_delete(FieldAccessData * self, Bool call_free);
U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher);
U32 FieldAccessData_size(void);
Str * literal_num_text(LiteralNumData * n);
Str * ident_name(IdentData * id);
Str * field_access_name(FieldAccessData * fa);
void set_own_arg(Expr * fcall, U32 arg_index);
Bool get_own_arg(Expr * fcall, U32 arg_index);
Bool is_range_new_call(Expr * e);
StructDef * StructDef_clone(StructDef * self);
void StructDef_delete(StructDef * self, Bool call_free);
U64 StructDef_hash(StructDef * self, HashFn hasher);
U32 StructDef_size(void);
EnumDef * EnumDef_clone(EnumDef * self);
void EnumDef_delete(EnumDef * self, Bool call_free);
U64 EnumDef_hash(EnumDef * self, HashFn hasher);
U32 EnumDef_size(void);
FieldLayout * FieldLayout_clone(FieldLayout * self);
void FieldLayout_delete(FieldLayout * self, Bool call_free);
U64 FieldLayout_hash(FieldLayout * self, HashFn hasher);
U32 FieldLayout_size(void);
StructLayout * StructLayout_clone(StructLayout * self);
void StructLayout_delete(StructLayout * self, Bool call_free);
U64 StructLayout_hash(StructLayout * self, HashFn hasher);
U32 StructLayout_size(void);
AssignData * AssignData_clone(AssignData * self);
void AssignData_delete(AssignData * self, Bool call_free);
U64 AssignData_hash(AssignData * self, HashFn hasher);
U32 AssignData_size(void);
FieldAssignData * FieldAssignData_clone(FieldAssignData * self);
void FieldAssignData_delete(FieldAssignData * self, Bool call_free);
U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher);
U32 FieldAssignData_size(void);
ForInData * ForInData_clone(ForInData * self);
void ForInData_delete(ForInData * self, Bool call_free);
U64 ForInData_hash(ForInData * self, HashFn hasher);
U32 ForInData_size(void);
void Literal_delete(Literal * self, Bool call_free);
Literal * Literal_clone(Literal * self);
U32 Literal_size(void);
MatchData * MatchData_clone(MatchData * self);
void MatchData_delete(MatchData * self, Bool call_free);
U64 MatchData_hash(MatchData * self, HashFn hasher);
U32 MatchData_size(void);
CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self);
void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free);
U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher);
U32 CaptureBlockData_size(void);
Bool NodeType_is_literal_str(NodeType * self);
Bool NodeType_is_literal_num(NodeType * self);
Bool NodeType_is_literal_bool(NodeType * self);
Bool NodeType_is_literal_null(NodeType * self);
Bool NodeType_is_map_lit(NodeType * self);
Bool NodeType_is_set_lit(NodeType * self);
Bool NodeType_is_nonnull_literal(NodeType * self);
Bool NodeType_is(NodeType * self, NodeType * other);
void NodeType_delete(NodeType * self, Bool call_free);
NodeType * NodeType_clone(NodeType * self);
U32 NodeType_size(void);
void Expr_delete(Expr * self, Bool call_free);
void Expr_error(Expr * self, Str * path, Str * msg);
void Expr_add_child(Expr * self, Expr * child);
void Expr_push_child_clone(Expr * self, Expr * child);
void Expr_take_children(Expr * self, Expr * other);
Expr * Expr_new(NodeType * data, U32 line, U32 col);
Str * Expr_to_str(Expr * self);
Expr * Expr_clone(Expr * self);
U64 Expr_hash(Expr * self, HashFn hasher);
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
Bool priv___src_core_ast_til__lazy_single_return_body(Expr * body);
Bool priv___src_core_ast_til__lazy_is_guard(Expr * stmt);
Bool priv___src_core_ast_til__lazy_stmts_inlinable(Expr * body, U32 start);
Bool lazy_body_inlinable(Expr * body);
Bool priv___src_core_ast_til__lazy_is_safe_prelude(Expr * stmt);
I32 lazy_body_split_point(Expr * body);
Bool lazy_body_stmt_inlinable(Expr * body);
U32 fcall_kwargs_count(Expr * fcall);
U32 fcall_variadic_count(Expr * fcall, U32 nparam, Bool callee_has_kwargs);
Map__I64_Str * Map__I64_Str_new(void);
U32 Map__I64_Str_len(Map__I64_Str * self);
Bool Map__I64_Str_has(Map__I64_Str * self, I64 key);
Str * Map__I64_Str_get(Map__I64_Str * self, I64 * key, I64 * _err_kind, KeyNotFound * _err_KeyNotFound, Str * loc);
void Map__I64_Str_set(Map__I64_Str * self, I64 key, Str * val);
void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free);
Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self);
U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher);
U32 Map__I64_Str_size(void);
Vec__Bool * Vec__Bool_new(void);
U32 Vec__Bool_len(Vec__Bool * self);
void Vec__Bool_clear(Vec__Bool * self);
void Vec__Bool_push(Vec__Bool * self, Bool * val);
Bool * Vec__Bool_unsafe_get(Vec__Bool * self, U32 * i);
Bool * Vec__Bool_get(Vec__Bool * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
void Vec__Bool_delete(Vec__Bool * self, Bool call_free);
Vec__Bool * Vec__Bool_clone(Vec__Bool * self);
U32 Vec__Bool_size(void);
Vec__I64 * Vec__I64_new(void);
U32 Vec__I64_len(Vec__I64 * self);
void Vec__I64_clear(Vec__I64 * self);
void Vec__I64_push(Vec__I64 * self, I64 * val);
I64 * Vec__I64_unsafe_get(Vec__I64 * self, U32 * i);
I64 * Vec__I64_get(Vec__I64 * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
void Vec__I64_unsafe_set(Vec__I64 * self, U32 i, I64 * val);
void Vec__I64_delete(Vec__I64 * self, Bool call_free);
Vec__I64 * Vec__I64_clone(Vec__I64 * self);
U32 Vec__I64_size(void);
Vec__FieldLayout * Vec__FieldLayout_new(void);
U32 Vec__FieldLayout_len(Vec__FieldLayout * self);
void Vec__FieldLayout_clear(Vec__FieldLayout * self);
void Vec__FieldLayout_push(Vec__FieldLayout * self, FieldLayout * val);
FieldLayout * Vec__FieldLayout_unsafe_get(Vec__FieldLayout * self, U32 * i);
FieldLayout * Vec__FieldLayout_get(Vec__FieldLayout * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
void Vec__FieldLayout_delete(Vec__FieldLayout * self, Bool call_free);
Vec__FieldLayout * Vec__FieldLayout_clone(Vec__FieldLayout * self);
U32 Vec__FieldLayout_size(void);
Vec__Declaration * Vec__Declaration_new(void);
U32 Vec__Declaration_len(Vec__Declaration * self);
void Vec__Declaration_clear(Vec__Declaration * self);
void Vec__Declaration_push(Vec__Declaration * self, Declaration * val);
void Vec__Declaration_move_from(Vec__Declaration * self, Vec__Declaration * other);
Declaration * Vec__Declaration_unsafe_get(Vec__Declaration * self, U32 * i);
Declaration * Vec__Declaration_get(Vec__Declaration * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
Declaration * Vec__Declaration_pop(Vec__Declaration * self);
void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free);
Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self);
U32 Vec__Declaration_size(void);
Vec__Expr * Vec__Expr_new(void);
Vec__Expr * Vec__Expr_with_capacity(U32 n);
U32 Vec__Expr_len(Vec__Expr * self);
void Vec__Expr_clear(Vec__Expr * self);
void Vec__Expr_push(Vec__Expr * self, Expr * val);
void Vec__Expr_append(Vec__Expr * self, Vec__Expr * other);
void Vec__Expr_move_from(Vec__Expr * self, Vec__Expr * other);
Expr * Vec__Expr_unsafe_get(Vec__Expr * self, U32 * i);
Expr * Vec__Expr_get(Vec__Expr * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
Expr * Vec__Expr_pop(Vec__Expr * self);
void Vec__Expr_unsafe_set(Vec__Expr * self, U32 i, Expr * val);
void Vec__Expr_set(Vec__Expr * self, U32 i, Expr * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
void Vec__Expr_push_take(Vec__Expr * self, Vec__Expr * src, U32 i);
void Vec__Expr_delete(Vec__Expr * self, Bool call_free);
Vec__Expr * Vec__Expr_clone(Vec__Expr * self);
U32 Vec__Expr_size(void);
void Tuple_delete(Tuple * self, Bool call_free);
Tuple * Tuple_clone(Tuple * self);
U32 Tuple_size(void);
Vec__U32 * Vec__U32_new(void);
U32 Vec__U32_len(Vec__U32 * self);
void Vec__U32_clear(Vec__U32 * self);
void Vec__U32_push(Vec__U32 * self, U32 * val);
U32 * Vec__U32_unsafe_get(Vec__U32 * self, U32 * i);
U32 * Vec__U32_get(Vec__U32 * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
void Vec__U32_delete(Vec__U32 * self, Bool call_free);
Vec__U32 * Vec__U32_clone(Vec__U32 * self);
U32 Vec__U32_size(void);
KwargsMap * KwargsMap_clone(KwargsMap * self);
void KwargsMap_delete(KwargsMap * self, Bool call_free);
U64 KwargsMap_hash(KwargsMap * self, HashFn hasher);
U32 KwargsMap_size(void);
Map__Str_Tuple * Map__Str_Tuple_new(void);
void Map__Str_Tuple_delete(Map__Str_Tuple * self, Bool call_free);
Map__Str_Tuple * Map__Str_Tuple_clone(Map__Str_Tuple * self);
U64 Map__Str_Tuple_hash(Map__Str_Tuple * self, HashFn hasher);
U32 Map__Str_Tuple_size(void);
Vec__Tuple * Vec__Tuple_new(void);
void Vec__Tuple_clear(Vec__Tuple * self);
void Vec__Tuple_delete(Vec__Tuple * self, Bool call_free);
Vec__Tuple * Vec__Tuple_clone(Vec__Tuple * self);
U32 Vec__Tuple_size(void);
void panic(Array__Str * parts, Str * loc);
void UNREACHABLE(Str * loc);
void expect(Bool cond, Array__Str * parts, Str * loc);
void println(Array__Str * parts);
File * File_new(Str * path, Bool is_write);
File * File_write(File * self, Str * s);
void File_close(File * self);
void File_delete(File * self, Bool call_free);
File * File_clone(File * self);
U32 File_size(void);
Bool is_null(void * p);
void swap(void * a, void * b, U64 size);
void move(void * dest, void * src, U64 size);
Range * Range_clone(Range * val);
void Range_delete(Range * self, Bool call_free);
U64 Range_hash(Range * self, HashFn hasher);
U32 Range_size(void);
I64 wait_cmd(I64 pid);
I64 run_cmd(Str * output, Array__Str * args);
Bool TokenType_is(TokenType * self, TokenType * other);
Bool TokenType_eq(TokenType * self, TokenType * other);
void TokenType_delete(TokenType * self, Bool call_free);
TokenType * TokenType_clone(TokenType * self);
U32 TokenType_size(void);
Token * Token_clone(Token * self);
void Token_delete(Token * self, Bool call_free);
U64 Token_hash(Token * self, HashFn hasher);
U32 Token_size(void);
Bool priv___src_self_lexer_til__is_digit(I8 c);
Bool priv___src_self_lexer_til__is_alpha(I8 c);
Bool is_alnum(I8 c);
Bool priv___src_self_lexer_til__is_hex_digit(I8 c);
Bool priv___src_self_lexer_til__is_bin_digit(I8 c);
Bool priv___src_self_lexer_til__is_oct_digit(I8 c);
Bool priv___src_self_lexer_til__is_doc_ws(I8 c);
Map__Str_TokenType * priv___src_self_lexer_til__keyword_map(void);
void lexer_cleanup(void);
Str * tok_name(TokenType * type);
TokenType priv___src_self_lexer_til__lookup_single_char(I8 c);
TokenType priv___src_self_lexer_til__lookup_two_char(I8 c, I8 c2);
TokenType * priv___src_self_lexer_til__lookup_keyword(Str * word, Map__Str_TokenType * kw);
U32 priv___src_self_lexer_til__scan_to_eol(Str * src, U32 from, U32 src_len);
void priv___src_self_lexer_til__push_tok(Vec__Token * tokens, TokenType * type, U32 start, U32 len, U32 line, U32 col);
void priv___src_self_lexer_til__emit_doc_block_lines(Vec__Token * tokens, Str * src, U32 from, U32 to, U32 doc_line, U32 col);
Vec__Token * tokenize(Str * src, Str * path);
Map__Str_TokenType * Map__Str_TokenType_new(void);
Bool Map__Str_TokenType_has(Map__Str_TokenType * self, Str * key);
TokenType * Map__Str_TokenType_get(Map__Str_TokenType * self, Str * key, I64 * _err_kind, KeyNotFound * _err_KeyNotFound, Str * loc);
void Map__Str_TokenType_set(Map__Str_TokenType * self, Str * key, TokenType * val);
void Map__Str_TokenType_delete(Map__Str_TokenType * self, Bool call_free);
Map__Str_TokenType * Map__Str_TokenType_clone(Map__Str_TokenType * self);
U64 Map__Str_TokenType_hash(Map__Str_TokenType * self, HashFn hasher);
U32 Map__Str_TokenType_size(void);
Vec__Token * Vec__Token_new(void);
U32 Vec__Token_len(Vec__Token * self);
void Vec__Token_clear(Vec__Token * self);
void Vec__Token_push(Vec__Token * self, Token * val);
Token * Vec__Token_unsafe_get(Vec__Token * self, U32 * i);
Token * Vec__Token_get(Vec__Token * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
void Vec__Token_delete(Vec__Token * self, Bool call_free);
Vec__Token * Vec__Token_clone(Vec__Token * self);
U32 Vec__Token_size(void);
Vec__TokenType * Vec__TokenType_new(void);
void Vec__TokenType_clear(Vec__TokenType * self);
TokenType * Vec__TokenType_unsafe_get(Vec__TokenType * self, U32 * i);
void Vec__TokenType_unsafe_set(Vec__TokenType * self, U32 i, TokenType * val);
void Vec__TokenType_delete(Vec__TokenType * self, Bool call_free);
Vec__TokenType * Vec__TokenType_clone(Vec__TokenType * self);
U32 Vec__TokenType_size(void);
priv___src_self_parser_til__Parser * priv___src_self_parser_til__Parser_clone(priv___src_self_parser_til__Parser * self);
void priv___src_self_parser_til__Parser_delete(priv___src_self_parser_til__Parser * self, Bool call_free);
U64 priv___src_self_parser_til__Parser_hash(priv___src_self_parser_til__Parser * self, HashFn hasher);
U32 priv___src_self_parser_til__Parser_size(void);
Token * priv___src_self_parser_til__peek(priv___src_self_parser_til__Parser * p);
Str * priv___src_self_parser_til__tok_text(priv___src_self_parser_til__Parser * p, Token * t);
Token * priv___src_self_parser_til__advance(priv___src_self_parser_til__Parser * p);
Bool priv___src_self_parser_til__check(priv___src_self_parser_til__Parser * p, TokenType * type);
Token * priv___src_self_parser_til__expect_token(priv___src_self_parser_til__Parser * p, TokenType * type);
Str * priv___src_self_parser_til__expect_text(priv___src_self_parser_til__Parser * p, TokenType * type);
U32 priv___src_self_parser_til__peek_line(priv___src_self_parser_til__Parser * p);
U32 priv___src_self_parser_til__peek_col(priv___src_self_parser_til__Parser * p);
Bool builtin_primitive_from_name(Str * name, Primitive * out);
void builtin_primitive_size_align(Primitive * prim, U32 * sz, U32 * al);
Bool builtin_type_from_name(Str * name, Type * out);
Type * til_type_from_explicit_type(Str * name);
Declaration * decl_typed(Str * explicit_type, Str * name, Str * doc, Bool is_mut, Bool redundant_mut, Bool is_priv, Bool used, OwnType * own_type);
void priv___src_self_parser_til__set_decl_type(Declaration * d, Str * name);
Str * priv___src_self_parser_til__anon_decl_key(Declaration * d);
Str * priv___src_self_parser_til__anon_def_key(Expr * def);
Str * priv___src_self_parser_til__anon_lift(priv___src_self_parser_til__Parser * p, Expr * def, U32 line, U32 col);
void priv___src_self_parser_til__type_gen_lift(priv___src_self_parser_til__Parser * p, Str * name, Vec__Str * args, Str * mangled, U32 line, U32 col);
Bool priv___src_self_parser_til__parser_has_active_type_param(priv___src_self_parser_til__Parser * p, Str * name);
Str * priv___src_self_parser_til__parse_type_ref(priv___src_self_parser_til__Parser * p);
Str * priv___src_self_parser_til__parse_fn_signature(priv___src_self_parser_til__Parser * p, U32 line, U32 col);
Expr * priv___src_self_parser_til__parse_block(priv___src_self_parser_til__Parser * p);
Vec__Declaration * priv___src_self_parser_til__parse_capture_list(priv___src_self_parser_til__Parser * p, Bool allow_modes);
Vec__Declaration * priv___src_self_parser_til__parse_generic_params(priv___src_self_parser_til__Parser * p);
Expr * priv___src_self_parser_til__parse_func_def(priv___src_self_parser_til__Parser * p);
Declaration * priv___src_self_parser_til__parse_ns_decl(priv___src_self_parser_til__Parser * p, Bool member_priv);
StructDef * priv___src_self_parser_til__structdef_of(Expr * def);
EnumDef * priv___src_self_parser_til__enumdef_of(Expr * def);
Expr * priv___src_self_parser_til__wrap_struct_def_in_macro(Expr * sdef, Vec__Declaration * gparams, U32 line, U32 col);
Expr * priv___src_self_parser_til__wrap_func_def_in_macro(Expr * fdef, Vec__Declaration * gparams, U32 line, U32 col);
Expr * priv___src_self_parser_til__parse_struct_def(priv___src_self_parser_til__Parser * p, Str * c_tag);
Expr * priv___src_self_parser_til__parse_interface_def(priv___src_self_parser_til__Parser * p);
Expr * priv___src_self_parser_til__parse_enum_def(priv___src_self_parser_til__Parser * p);
void priv___src_self_parser_til__set_fcall_throw(Expr * fcall);
void priv___src_self_parser_til__set_fcall_bang(Expr * fcall);
void priv___src_self_parser_til__set_fcall_splat(Expr * fcall);
Bool priv___src_self_parser_til__parse_named_arg(priv___src_self_parser_til__Parser * p, Expr * call);
void priv___src_self_parser_til__append_arg(priv___src_self_parser_til__Parser * p, Expr * call, Expr * arg, Bool is_own_arg);
void priv___src_self_parser_til__parse_throw_bang_suffix(priv___src_self_parser_til__Parser * p, Expr * call);
Expr * priv___src_self_parser_til__parse_subscript_assign(priv___src_self_parser_til__Parser * p, Expr * lhs);
Expr * priv___src_self_parser_til__parse_call(priv___src_self_parser_til__Parser * p, Expr * callee, U32 call_line, U32 call_col);
Expr * priv___src_self_parser_til__make_binop_call(Expr * lhs, Str * method, U32 op_line, U32 op_col, Expr * rhs);
Expr * priv___src_self_parser_til__take_expr(Expr * e);
Expr * priv___src_self_parser_til__parse_primary(priv___src_self_parser_til__Parser * p);
I64 priv___src_self_parser_til__binop_prec(TokenType * tt);
Str * priv___src_self_parser_til__binop_method(TokenType * tt);
Expr * priv___src_self_parser_til__parse_binop(priv___src_self_parser_til__Parser * p, I64 min_prec);
Expr * priv___src_self_parser_til__parse_expression(priv___src_self_parser_til__Parser * p);
Expr * priv___src_self_parser_til__parse_statement_ident(priv___src_self_parser_til__Parser * p, Bool is_mut, OwnType own_type);
void priv___src_self_parser_til__drain_doc_comments(priv___src_self_parser_til__Parser * p);
Expr * priv___src_self_parser_til__parse_statement(priv___src_self_parser_til__Parser * p);
Expr * priv___src_self_parser_til__parse_case_head(priv___src_self_parser_til__Parser * p);
Expr * priv___src_self_parser_til__parse_switch(priv___src_self_parser_til__Parser * p);
Expr * priv___src_self_parser_til__parse_statement_body(priv___src_self_parser_til__Parser * p);
Expr * parse(Vec__Token * tokens, Str * source, Str * path, Str * mode_out, I64 * anon_type_counter);
Set__Str * Set__Str_new(void);
U32 Set__Str_len(Set__Str * self);
void Set__Str_clear(Set__Str * self);
Bool Set__Str_has(Set__Str * self, Str * val);
void Set__Str_add(Set__Str * self, Str * val);
void Set__Str_delete(Set__Str * self, Bool call_free);
Set__Str * Set__Str_clone(Set__Str * self);
U32 Set__Str_size(void);
Map__Str_Str * Map__Str_Str_new(void);
U32 Map__Str_Str_len(Map__Str_Str * self);
Bool Map__Str_Str_has(Map__Str_Str * self, Str * key);
Str * Map__Str_Str_get(Map__Str_Str * self, Str * key, I64 * _err_kind, KeyNotFound * _err_KeyNotFound, Str * loc);
void Map__Str_Str_set(Map__Str_Str * self, Str * key, Str * val);
void Map__Str_Str_delete(Map__Str_Str * self, Bool call_free);
Map__Str_Str * Map__Str_Str_clone(Map__Str_Str * self);
U64 Map__Str_Str_hash(Map__Str_Str * self, HashFn hasher);
U32 Map__Str_Str_size(void);
EvalHeap EvalHeap_new(void);
void * EvalHeap_heap_alloc(U32 size);
void EvalHeap_heap_free(void * ptr);
void EvalHeap_delete(EvalHeap * self, Bool call_free);
EvalHeap EvalHeap_clone(EvalHeap self);
U64 EvalHeap_hash(EvalHeap self, HashFn hasher);
U32 EvalHeap_size(void);
TypeBinding * TypeBinding_clone(TypeBinding * self);
void TypeBinding_delete(TypeBinding * self, Bool call_free);
U64 TypeBinding_hash(TypeBinding * self, HashFn hasher);
U32 TypeBinding_size(void);
ScopeFind * ScopeFind_NotFound(void);
ScopeFind * ScopeFind_Found(TypeBinding * val);
Bool ScopeFind_is(ScopeFind * self, ScopeFind * other);
void ScopeFind_delete(ScopeFind * self, Bool call_free);
ScopeFind * ScopeFind_clone(ScopeFind * self);
U32 ScopeFind_size(void);
Expr * priv___src_self_context_til__func_defs_lookup_one(Map__Str_Dynamic * m, Str * name);
TypeBinding * TypeScope_get_binding(TypeScope * self, Str * name);
ScopeFind * TypeScope_find(TypeScope * self, Str * name);
Type * TypeScope_get_type(TypeScope * self, Str * name);
FuncType TypeScope_get_func_type(TypeScope * self, Str * name);
Expr * TypeScope_get_struct(TypeScope * self, Str * name);
Expr * TypeScope_struct_def_of(TypeScope * self, Str * name);
Expr * TypeScope_lookup_func(TypeScope * self, Str * name);
void TypeScope_set_func_def(TypeScope * self, Str * name, Expr * fdef);
void TypeScope_set_struct_def(TypeScope * self, Str * name, Expr * sdef);
Bool TypeScope_is_mut(TypeScope * self, Str * name);
void TypeScope_set(TypeScope * self, Str * name, Type * type, Bool is_mut, Str * path, U32 line, U32 col, Bool is_param, OwnType own_type);
TypeScope * TypeScope_clone(TypeScope * self);
void TypeScope_delete(TypeScope * self, Bool call_free);
U32 TypeScope_size(void);
FuncType binding_func_type(TypeBinding * b);
FuncType func_def_type(Expr * fdef);
ImportUnit * ImportUnit_clone(ImportUnit * self);
void ImportUnit_delete(ImportUnit * self, Bool call_free);
U32 ImportUnit_size(void);
BuilderFuncScratch * BuilderFuncScratch_clone(BuilderFuncScratch * self);
void BuilderFuncScratch_delete(BuilderFuncScratch * self, Bool call_free);
U64 BuilderFuncScratch_hash(BuilderFuncScratch * self, HashFn hasher);
U32 BuilderFuncScratch_size(void);
Context * Context_clone(Context * self);
void Context_delete(Context * self, Bool call_free);
U32 Context_size(void);
void context_register_target_int_alias_types(Context * ctx, Str * usize_name, Str * uptr_name);
void context_reset_type_scope(Context * ctx);
Str * scope_target_usize_pname(TypeScope * scope);
Str * scope_target_uptr_pname(TypeScope * scope);
Str * priv_c_name(Str * path, Str * name);
U32 align_up(U32 offset, U32 align);
void constfolder_classify_stmt(Expr * stmt, Context * ctx);
Expr * make_method_call_fcall(Expr * recv, Str * method, U32 line, U32 col);
Expr * make_get_payload_fcall(Expr * arg, Type payload_type, U32 line, U32 col);
Expr * make_is_tag_check_fcall(Str * arg_name, Str * ename, Str * vname, U32 tag_size, U32 line, U32 col);
Expr * make_payload_ref_decl(Expr * arg, Str * bind_name, Str * vtype, U32 line, U32 col, Bool is_mut);
Bool type_is_primitive(Type * t, Primitive * p);
Bool is_type_metatype(Type * t);
Bool funcptr_eq(Type * a, Type * b);
Type * type_from_name_init(Str * name, TypeScope * scope);
Type * init_type_from_explicit_type(Str * name, TypeScope * scope);
Str * field_inferred_type_name(Declaration * fd);
Str * array_vec_elem_type_name(Expr * fcall);
Bool is_pod_type_for_clone(Str * type_name, TypeScope * scope);
Bool priv___src_self_context_til__is_decl_with_child(Expr * stmt);
Bool is_struct_or_enum(Expr * stmt);
Bool is_func_decl(Expr * stmt);
Bool is_def(Expr * stmt);
Vec__Declaration * def_ns_decls(Expr * sdef);
Bool enum_has_payloads(Expr * enum_def);
Str * enum_tag_type(Expr * enum_def);
U32 enum_tag_size(Expr * enum_def);
I64 enum_variant_tag(Expr * enum_def, Str * variant_name);
I32 enum_variant_index(Expr * enum_def, Str * variant_name);
Str * enum_variant_type(Expr * enum_def, I32 idx);
Bool enum_variant_payload_const(Expr * enum_def, I32 idx);
Map__Str_TypeBinding * Map__Str_TypeBinding_new(void);
Bool Map__Str_TypeBinding_has(Map__Str_TypeBinding * self, Str * key);
TypeBinding * Map__Str_TypeBinding_get(Map__Str_TypeBinding * self, Str * key, I64 * _err_kind, KeyNotFound * _err_KeyNotFound, Str * loc);
void Map__Str_TypeBinding_set(Map__Str_TypeBinding * self, Str * key, TypeBinding * val);
void Map__Str_TypeBinding_delete(Map__Str_TypeBinding * self, Bool call_free);
Map__Str_TypeBinding * Map__Str_TypeBinding_clone(Map__Str_TypeBinding * self);
U64 Map__Str_TypeBinding_hash(Map__Str_TypeBinding * self, HashFn hasher);
U32 Map__Str_TypeBinding_size(void);
Map__Str_Mode * Map__Str_Mode_new(void);
Bool Map__Str_Mode_has(Map__Str_Mode * self, Str * key);
Mode * Map__Str_Mode_get(Map__Str_Mode * self, Str * key, I64 * _err_kind, KeyNotFound * _err_KeyNotFound, Str * loc);
void Map__Str_Mode_set(Map__Str_Mode * self, Str * key, Mode * val);
void Map__Str_Mode_delete(Map__Str_Mode * self, Bool call_free);
Map__Str_Mode * Map__Str_Mode_clone(Map__Str_Mode * self);
U64 Map__Str_Mode_hash(Map__Str_Mode * self, HashFn hasher);
U32 Map__Str_Mode_size(void);
Map__Str_ImportUnit * Map__Str_ImportUnit_new(void);
Bool Map__Str_ImportUnit_has(Map__Str_ImportUnit * self, Str * key);
ImportUnit * Map__Str_ImportUnit_get(Map__Str_ImportUnit * self, Str * key, I64 * _err_kind, KeyNotFound * _err_KeyNotFound, Str * loc);
void Map__Str_ImportUnit_set(Map__Str_ImportUnit * self, Str * key, ImportUnit * val);
void Map__Str_ImportUnit_delete(Map__Str_ImportUnit * self, Bool call_free);
Map__Str_ImportUnit * Map__Str_ImportUnit_clone(Map__Str_ImportUnit * self);
U64 Map__Str_ImportUnit_hash(Map__Str_ImportUnit * self, HashFn hasher);
U32 Map__Str_ImportUnit_size(void);
Map__Str_Expr * Map__Str_Expr_new(void);
U32 Map__Str_Expr_len(Map__Str_Expr * self);
Bool Map__Str_Expr_has(Map__Str_Expr * self, Str * key);
Expr * Map__Str_Expr_get(Map__Str_Expr * self, Str * key, I64 * _err_kind, KeyNotFound * _err_KeyNotFound, Str * loc);
void Map__Str_Expr_set(Map__Str_Expr * self, Str * key, Expr * val);
void Map__Str_Expr_delete(Map__Str_Expr * self, Bool call_free);
Map__Str_Expr * Map__Str_Expr_clone(Map__Str_Expr * self);
U64 Map__Str_Expr_hash(Map__Str_Expr * self, HashFn hasher);
U32 Map__Str_Expr_size(void);
Map__Str_StructLayout * Map__Str_StructLayout_new(void);
Bool Map__Str_StructLayout_has(Map__Str_StructLayout * self, Str * key);
StructLayout * Map__Str_StructLayout_get(Map__Str_StructLayout * self, Str * key, I64 * _err_kind, KeyNotFound * _err_KeyNotFound, Str * loc);
void Map__Str_StructLayout_set(Map__Str_StructLayout * self, Str * key, StructLayout * val);
void Map__Str_StructLayout_delete(Map__Str_StructLayout * self, Bool call_free);
Map__Str_StructLayout * Map__Str_StructLayout_clone(Map__Str_StructLayout * self);
U64 Map__Str_StructLayout_hash(Map__Str_StructLayout * self, HashFn hasher);
U32 Map__Str_StructLayout_size(void);
Map__Str_FuncType * Map__Str_FuncType_new(void);
U32 Map__Str_FuncType_len(Map__Str_FuncType * self);
Bool Map__Str_FuncType_has(Map__Str_FuncType * self, Str * key);
FuncType * Map__Str_FuncType_get(Map__Str_FuncType * self, Str * key, I64 * _err_kind, KeyNotFound * _err_KeyNotFound, Str * loc);
void Map__Str_FuncType_set(Map__Str_FuncType * self, Str * key, FuncType * val);
void Map__Str_FuncType_delete(Map__Str_FuncType * self, Bool call_free);
Map__Str_FuncType * Map__Str_FuncType_clone(Map__Str_FuncType * self);
U64 Map__Str_FuncType_hash(Map__Str_FuncType * self, HashFn hasher);
U32 Map__Str_FuncType_size(void);
Map__Str_Value * Map__Str_Value_new(void);
void Map__Str_Value_clear(Map__Str_Value * self);
Bool Map__Str_Value_has(Map__Str_Value * self, Str * key);
Value * Map__Str_Value_get(Map__Str_Value * self, Str * key, I64 * _err_kind, KeyNotFound * _err_KeyNotFound, Str * loc);
void Map__Str_Value_set(Map__Str_Value * self, Str * key, Value * val);
void Map__Str_Value_delete(Map__Str_Value * self, Bool call_free);
Map__Str_Value * Map__Str_Value_clone(Map__Str_Value * self);
U64 Map__Str_Value_hash(Map__Str_Value * self, HashFn hasher);
U32 Map__Str_Value_size(void);
Vec__Dynamic * Vec__Dynamic_new(void);
U32 Vec__Dynamic_len(Vec__Dynamic * self);
void Vec__Dynamic_clear(Vec__Dynamic * self);
void Vec__Dynamic_push(Vec__Dynamic * self, void * val);
void * Vec__Dynamic_unsafe_get(Vec__Dynamic * self, U32 * i);
void * Vec__Dynamic_get(Vec__Dynamic * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
void Vec__Dynamic_unsafe_set(Vec__Dynamic * self, U32 i, void * val);
void Vec__Dynamic_delete(Vec__Dynamic * self, Bool call_free);
Vec__Dynamic * Vec__Dynamic_clone(Vec__Dynamic * self);
U32 Vec__Dynamic_size(void);
Map__Str_call_Vec_Str * Map__Str_call_Vec_Str_new(void);
Bool Map__Str_call_Vec_Str_has(Map__Str_call_Vec_Str * self, Str * key);
Vec__Str * Map__Str_call_Vec_Str_get(Map__Str_call_Vec_Str * self, Str * key, I64 * _err_kind, KeyNotFound * _err_KeyNotFound, Str * loc);
void Map__Str_call_Vec_Str_set(Map__Str_call_Vec_Str * self, Str * key, Vec__Str * val);
void Map__Str_call_Vec_Str_delete(Map__Str_call_Vec_Str * self, Bool call_free);
Map__Str_call_Vec_Str * Map__Str_call_Vec_Str_clone(Map__Str_call_Vec_Str * self);
U64 Map__Str_call_Vec_Str_hash(Map__Str_call_Vec_Str * self, HashFn hasher);
U32 Map__Str_call_Vec_Str_size(void);
Map__Str_Dynamic * Map__Str_Dynamic_new(void);
Bool Map__Str_Dynamic_has(Map__Str_Dynamic * self, Str * key);
void * Map__Str_Dynamic_get(Map__Str_Dynamic * self, Str * key, I64 * _err_kind, KeyNotFound * _err_KeyNotFound, Str * loc);
void Map__Str_Dynamic_set(Map__Str_Dynamic * self, Str * key, void * val);
void Map__Str_Dynamic_delete(Map__Str_Dynamic * self, Bool call_free);
Map__Str_Dynamic * Map__Str_Dynamic_clone(Map__Str_Dynamic * self);
U64 Map__Str_Dynamic_hash(Map__Str_Dynamic * self, HashFn hasher);
U32 Map__Str_Dynamic_size(void);
Map__Str_FFIEntry * Map__Str_FFIEntry_new(void);
Bool Map__Str_FFIEntry_has(Map__Str_FFIEntry * self, Str * key);
FFIEntry * Map__Str_FFIEntry_get(Map__Str_FFIEntry * self, Str * key, I64 * _err_kind, KeyNotFound * _err_KeyNotFound, Str * loc);
void Map__Str_FFIEntry_set(Map__Str_FFIEntry * self, Str * key, FFIEntry * val);
void Map__Str_FFIEntry_delete(Map__Str_FFIEntry * self, Bool call_free);
Map__Str_FFIEntry * Map__Str_FFIEntry_clone(Map__Str_FFIEntry * self);
U64 Map__Str_FFIEntry_hash(Map__Str_FFIEntry * self, HashFn hasher);
U32 Map__Str_FFIEntry_size(void);
Map__Str_ExprPtrBox * Map__Str_ExprPtrBox_new(void);
Bool Map__Str_ExprPtrBox_has(Map__Str_ExprPtrBox * self, Str * key);
ExprPtrBox * Map__Str_ExprPtrBox_get(Map__Str_ExprPtrBox * self, Str * key, I64 * _err_kind, KeyNotFound * _err_KeyNotFound, Str * loc);
void Map__Str_ExprPtrBox_set(Map__Str_ExprPtrBox * self, Str * key, ExprPtrBox * val);
void Map__Str_ExprPtrBox_delete(Map__Str_ExprPtrBox * self, Bool call_free);
Map__Str_ExprPtrBox * Map__Str_ExprPtrBox_clone(Map__Str_ExprPtrBox * self);
U64 Map__Str_ExprPtrBox_hash(Map__Str_ExprPtrBox * self, HashFn hasher);
U32 Map__Str_ExprPtrBox_size(void);
Vec__FFITypePtrBox * Vec__FFITypePtrBox_new(void);
U32 Vec__FFITypePtrBox_len(Vec__FFITypePtrBox * self);
void Vec__FFITypePtrBox_clear(Vec__FFITypePtrBox * self);
void Vec__FFITypePtrBox_push(Vec__FFITypePtrBox * self, FFITypePtrBox * val);
FFITypePtrBox * Vec__FFITypePtrBox_unsafe_get(Vec__FFITypePtrBox * self, U32 * i);
void Vec__FFITypePtrBox_delete(Vec__FFITypePtrBox * self, Bool call_free);
Vec__FFITypePtrBox * Vec__FFITypePtrBox_clone(Vec__FFITypePtrBox * self);
U32 Vec__FFITypePtrBox_size(void);
Vec__TypeBinding * Vec__TypeBinding_new(void);
U32 Vec__TypeBinding_len(Vec__TypeBinding * self);
void Vec__TypeBinding_clear(Vec__TypeBinding * self);
TypeBinding * Vec__TypeBinding_unsafe_get(Vec__TypeBinding * self, U32 * i);
void Vec__TypeBinding_unsafe_set(Vec__TypeBinding * self, U32 i, TypeBinding * val);
void Vec__TypeBinding_delete(Vec__TypeBinding * self, Bool call_free);
Vec__TypeBinding * Vec__TypeBinding_clone(Vec__TypeBinding * self);
U32 Vec__TypeBinding_size(void);
Vec__Mode * Vec__Mode_new(void);
void Vec__Mode_clear(Vec__Mode * self);
Mode * Vec__Mode_unsafe_get(Vec__Mode * self, U32 * i);
void Vec__Mode_unsafe_set(Vec__Mode * self, U32 i, Mode * val);
void Vec__Mode_delete(Vec__Mode * self, Bool call_free);
Vec__Mode * Vec__Mode_clone(Vec__Mode * self);
U32 Vec__Mode_size(void);
Vec__ImportUnit * Vec__ImportUnit_new(void);
void Vec__ImportUnit_clear(Vec__ImportUnit * self);
ImportUnit * Vec__ImportUnit_unsafe_get(Vec__ImportUnit * self, U32 * i);
void Vec__ImportUnit_unsafe_set(Vec__ImportUnit * self, U32 i, ImportUnit * val);
void Vec__ImportUnit_delete(Vec__ImportUnit * self, Bool call_free);
Vec__ImportUnit * Vec__ImportUnit_clone(Vec__ImportUnit * self);
U32 Vec__ImportUnit_size(void);
Vec__StructLayout * Vec__StructLayout_new(void);
void Vec__StructLayout_clear(Vec__StructLayout * self);
StructLayout * Vec__StructLayout_unsafe_get(Vec__StructLayout * self, U32 * i);
void Vec__StructLayout_unsafe_set(Vec__StructLayout * self, U32 i, StructLayout * val);
void Vec__StructLayout_delete(Vec__StructLayout * self, Bool call_free);
Vec__StructLayout * Vec__StructLayout_clone(Vec__StructLayout * self);
U32 Vec__StructLayout_size(void);
Vec__FuncType * Vec__FuncType_new(void);
void Vec__FuncType_clear(Vec__FuncType * self);
FuncType * Vec__FuncType_unsafe_get(Vec__FuncType * self, U32 * i);
void Vec__FuncType_unsafe_set(Vec__FuncType * self, U32 i, FuncType * val);
void Vec__FuncType_delete(Vec__FuncType * self, Bool call_free);
Vec__FuncType * Vec__FuncType_clone(Vec__FuncType * self);
U32 Vec__FuncType_size(void);
Vec__Value * Vec__Value_new(void);
U32 Vec__Value_len(Vec__Value * self);
void Vec__Value_clear(Vec__Value * self);
void Vec__Value_push(Vec__Value * self, Value * val);
Value * Vec__Value_unsafe_get(Vec__Value * self, U32 * i);
void Vec__Value_unsafe_set(Vec__Value * self, U32 i, Value * val);
void Vec__Value_delete(Vec__Value * self, Bool call_free);
Vec__Value * Vec__Value_clone(Vec__Value * self);
U32 Vec__Value_size(void);
Vec__call_Vec_Str * Vec__call_Vec_Str_new(void);
void Vec__call_Vec_Str_clear(Vec__call_Vec_Str * self);
Vec__Str * Vec__call_Vec_Str_unsafe_get(Vec__call_Vec_Str * self, U32 * i);
void Vec__call_Vec_Str_unsafe_set(Vec__call_Vec_Str * self, U32 i, Vec__Str * val);
void Vec__call_Vec_Str_delete(Vec__call_Vec_Str * self, Bool call_free);
Vec__call_Vec_Str * Vec__call_Vec_Str_clone(Vec__call_Vec_Str * self);
U32 Vec__call_Vec_Str_size(void);
Vec__FFIEntry * Vec__FFIEntry_new(void);
U32 Vec__FFIEntry_len(Vec__FFIEntry * self);
void Vec__FFIEntry_clear(Vec__FFIEntry * self);
FFIEntry * Vec__FFIEntry_unsafe_get(Vec__FFIEntry * self, U32 * i);
void Vec__FFIEntry_unsafe_set(Vec__FFIEntry * self, U32 i, FFIEntry * val);
void Vec__FFIEntry_delete(Vec__FFIEntry * self, Bool call_free);
Vec__FFIEntry * Vec__FFIEntry_clone(Vec__FFIEntry * self);
U32 Vec__FFIEntry_size(void);
Vec__ExprPtrBox * Vec__ExprPtrBox_new(void);
void Vec__ExprPtrBox_clear(Vec__ExprPtrBox * self);
ExprPtrBox * Vec__ExprPtrBox_unsafe_get(Vec__ExprPtrBox * self, U32 * i);
void Vec__ExprPtrBox_unsafe_set(Vec__ExprPtrBox * self, U32 i, ExprPtrBox * val);
void Vec__ExprPtrBox_delete(Vec__ExprPtrBox * self, Bool call_free);
Vec__ExprPtrBox * Vec__ExprPtrBox_clone(Vec__ExprPtrBox * self);
U32 Vec__ExprPtrBox_size(void);
Bool priv___src_self_initer_til__is_dynamic_type(Str * name);
Bool priv___src_self_initer_til__primitive_type_info(Str * name, TypeScope * scope, Primitive * prim, U32 * sz, U32 * al, Bool * is_builtin);
I32 priv___src_self_initer_til__register_struct_def_for_stmt(Context * ctx, Expr * stmt, TypeScope * scope);
Bool priv___src_self_initer_til__struct_field_supports_generated_method(Declaration * fd, Str * method, TypeScope * scope);
Bool priv___src_self_initer_til__struct_fields_support_generated_method(StructDef * sdd, Str * method, TypeScope * scope);
Expr * priv___src_self_initer_til__make_struct_field_access(Str * receiver_name, Str * field_name, U32 line, U32 col);
void priv___src_self_initer_til__generate_struct_eq_method(Expr * struct_def, Str * sname, U32 line, U32 col);
void priv___src_self_initer_til__generate_struct_to_str_method(Expr * struct_def, Str * sname, U32 line, U32 col);
void priv___src_self_initer_til__gen_struct_clone_delete_for_stmt(Expr * stmt, TypeScope * scope, Context * ctx);
I32 priv___src_self_initer_til__register_enum_definition(Context * ctx, Expr * stmt, TypeScope * scope);
void collect_enum_variants(Expr * enum_def, Vec__Str * variant_names, Vec__Str * variant_types, Bool * has_payloads);
void priv___src_self_initer_til__generate_enum_variant_constructors(Expr * enum_def, Str * ename, U32 line, U32 col, Vec__Str * variant_names, Vec__Str * variant_types, Bool has_payloads, TypeScope * scope);
void priv___src_self_initer_til__generate_enum_is_method(Expr * enum_def, Str * ename, U32 line, U32 col);
void priv___src_self_initer_til__generate_enum_eq_method(Expr * enum_def, Str * ename, U32 line, U32 col, Vec__Str * variant_names, Vec__Str * variant_types, TypeScope * scope);
void priv___src_self_initer_til__generate_enum_delete_method(Expr * enum_def, Str * ename, U32 line, U32 col, Vec__Str * variant_names, Vec__Str * variant_types, Bool has_payloads, TypeScope * scope);
void priv___src_self_initer_til__generate_enum_to_str_method(Expr * enum_def, Str * ename, U32 line, U32 col, Vec__Str * variant_names, Vec__Str * variant_types, Bool has_payloads, TypeScope * scope);
Bool priv___src_self_initer_til__init_ns_has_func(Expr * def, Str * method);
Bool priv___src_self_initer_til__init_type_supports_generated_method(Str * type_name, Str * method, TypeScope * scope);
Bool priv___src_self_initer_til__enum_payloads_support_generated_method(Vec__Str * variant_types, Str * method, TypeScope * scope);
void priv___src_self_initer_til__generate_enum_clone_method(Expr * enum_def, Str * ename, U32 line, U32 col, Vec__Str * variant_names, Vec__Str * variant_types, Bool has_payloads, TypeScope * scope);
I32 priv___src_self_initer_til__register_enum_def_for_stmt(Context * ctx, Expr * stmt, TypeScope * scope);
void priv___src_self_initer_til__gen_enum_nonclone_methods_for_stmt(Expr * stmt, TypeScope * scope);
void priv___src_self_initer_til__gen_missing_enum_clone_for_stmt(Expr * stmt, TypeScope * scope);
void priv___src_self_initer_til__register_funcsig_alias_for_stmt(Context * ctx, Expr * stmt, TypeScope * scope);
void priv___src_self_initer_til__register_type_alias_for_stmt(Context * ctx, Expr * stmt, TypeScope * scope);
void priv___src_self_initer_til__register_top_level_value_for_stmt(Context * ctx, Expr * stmt, TypeScope * scope);
void priv___src_self_initer_til__register_function_def_for_stmt(Context * ctx, Expr * stmt, TypeScope * scope);
void gen_struct_size_method_for_stmt(Expr * stmt, Context * ctx);
void gen_enum_size_method_for_stmt(Expr * stmt, TypeScope * scope, Context * ctx);
void gen_unity_derived_for_stmt(Expr * stmt);
void gen_cmp_derived_for_stmt(Expr * stmt);
void compute_struct_layout(Str * name, Expr * struct_def, TypeScope * scope, Context * ctx);
void priv___src_self_initer_til__type_size_align(Str * ftype, TypeScope * scope, Context * ctx, U32 * sz, U32 * al);
U32 compute_enum_layout(Str * name, Expr * enum_def, TypeScope * scope, Context * ctx);
U32 ctx_total_size(Str * name, Context * ctx);
FieldLayout * ctx_field_layout(Str * sname, Str * field_name, Context * ctx);
Bool priv___src_self_initer_til__infer_top_level_decl_type(Expr * stmt, TypeScope * scope, Type * out_type);
Bool priv___src_self_initer_til__init_is_lift_target(Expr * stmt);
Str * priv___src_self_initer_til__init_lookup_name(Map__Str_Str * renamings, Str * name);
void priv___src_self_initer_til__init_rename_ident_in_place(Expr * e, Map__Str_Str * renamings);
void priv___src_self_initer_til__init_rename_decl_in_place(Declaration * dd, Map__Str_Str * renamings);
void priv___src_self_initer_til__init_rewrite_refs(Expr * e, Map__Str_Str * renamings);
void priv___src_self_initer_til__init_lift_in_body(Expr * body, Str * parent_prefix, Vec__Expr * top_level);
void priv___src_self_initer_til__init_lift_in_ns_decls(Expr * def, Str * parent_prefix, Vec__Expr * top_level);
void priv___src_self_initer_til__init_recurse_into_subbodies(Expr * body, Str * parent_prefix, Vec__Expr * top_level);
void priv___src_self_initer_til__init_recurse_into_expr(Expr * e, Str * parent_prefix, Vec__Expr * top_level);
Str * priv___src_self_initer_til__init_subst_ident_name(Map__Str_Expr * subs, Str * name);
void priv___src_self_initer_til__init_substitute_idents(Expr * e, Map__Str_Expr * subs);
void priv___src_self_initer_til__init_subst_default_slot(Declaration * holder, Map__Str_Expr * subs);
void priv___src_self_initer_til__init_subst_struct_params(StructDef * sdef, Map__Str_Expr * subs);
void priv___src_self_initer_til__init_subst_enum_params(EnumDef * edef, Map__Str_Expr * subs);
void priv___src_self_initer_til__init_subst_func_params(FunctionDef * fdd, Map__Str_Expr * subs);
void priv___src_self_initer_til__init_substitute_type_params(Expr * def, Map__Str_Expr * subs);
I32 priv___src_self_initer_til__init_macro_cond_eval(Expr * cond);
Expr * priv___src_self_initer_til__init_macro_pick_return(Expr * body, Map__Str_Expr * subs);
Bool priv___src_self_initer_til__init_is_type_gen_macro_def(Expr * fdef);
Expr * priv___src_self_initer_til__init_lookup_type_gen_macro(Str * name, Map__Str_Expr * macros, TypeScope * scope, Context * ctx);
Bool priv___src_self_initer_til__init_is_macro_inst_call(Expr * e, Map__Str_Expr * macros, TypeScope * scope, Context * ctx);
Bool priv___src_self_initer_til__init_is_direct_macro_inst_decl(Expr * stmt, Map__Str_Expr * macros, TypeScope * scope, Context * ctx);
Bool priv___src_self_initer_til__init_macro_inst_uses_own_type_param(Expr * rhs, Expr * macro_fdef);
Str * priv___src_self_initer_til__init_macro_inst_name_byte(I8 b);
Str * priv___src_self_initer_til__init_macro_inst_text_name(Str * prefix, Str * text);
Str * priv___src_self_initer_til__init_type_arg_name(TypeScope * scope, Str * name);
Str * priv___src_self_initer_til__init_macro_inst_type_arg_name(Expr * arg, TypeScope * scope);
Str * priv___src_self_initer_til__init_macro_inst_arg_name(Expr * arg);
Str * priv___src_self_initer_til__init_macro_inst_name(Expr * e);
Str * priv___src_self_initer_til__init_macro_inst_name_for_macro(Expr * e, Expr * macro_fdef, TypeScope * scope);
Str * priv___src_self_initer_til__init_macro_inst_name_in_scope(Expr * e, Map__Str_Expr * macros, TypeScope * scope, Context * ctx);
void priv___src_self_initer_til__init_hoist_walk(Expr * e, Map__Str_Expr * macros, TypeScope * scope, Context * ctx, Vec__Expr * synthesized, Bool mark_ctx);
void priv___src_self_initer_til__init_hoist_inline_macros(Expr * program, Map__Str_Expr * macros, TypeScope * scope, Context * ctx);
void priv___src_self_initer_til__init_normalize_direct_type_gen_aliases(Expr * program, Map__Str_Expr * macros, TypeScope * scope, Context * ctx);
Expr * priv___src_self_initer_til__init_synth_array_inst_decl(Str * elem_type, U32 line, U32 col);
Expr * priv___src_self_initer_til__init_synth_vec_inst_decl(Str * elem_type, U32 line, U32 col);
Expr * priv___src_self_initer_til__init_synth_set_inst_decl(Str * elem_type, U32 line, U32 col);
Expr * priv___src_self_initer_til__init_synth_map_inst_decl(Str * key_type, Str * val_type, U32 line, U32 col);
Str * priv___src_self_initer_til__init_set_literal_elem_type(Expr * e);
Str * priv___src_self_initer_til__init_literal_child_type(Expr * e);
void priv___src_self_initer_til__init_collect_variadic_arrays(Expr * e, Vec__Expr * synthesized, Map__Str_Str * seen, Bool synth_array, Bool synth_vec, Bool synth_set, Bool synth_map);
void priv___src_self_initer_til__init_synthesize_variadic_arrays(Expr * program, Context * ctx);
void priv___src_self_initer_til__init_dedup_direct_type_gen_decls(Expr * program, Map__Str_Expr * macros, TypeScope * scope, Context * ctx);
void priv___src_self_initer_til__init_refresh_seeded_scope_defs(Expr * program, TypeScope * scope);
Bool priv___src_self_initer_til__init_func_is_generic(Expr * rhs);
void priv___src_self_initer_til__init_generic_expand_call(Expr * parent, U32 call_idx, Str * gname, Expr * gfd_expr, Map__Str_Expr * generics, Map__Str_Str * seen, Vec__Expr * synthesized, Context * ctx);
void priv___src_self_initer_til__init_generic_walk(Expr * e, Map__Str_Expr * generics, Map__Str_Str * seen, Vec__Expr * synthesized, Context * ctx);
void priv___src_self_initer_til__init_expand_generic_funcs(Expr * program, Context * ctx);
void priv___src_self_initer_til__init_expand_type_gen_macros(Expr * program, TypeScope * scope, Context * ctx);
I32 priv___src_self_initer_til__init_seed_declarations_unit(Str * path, Expr * program, TypeScope * scope, Context * ctx);
I32 priv___src_self_initer_til__init_declarations_unit(Str * path, Expr * program, TypeScope * scope, Context * ctx);
void priv___src_self_initer_til__gen_interface_box_fields_for_stmt(Expr * stmt);
Expr * priv___src_self_initer_til__iface_self_field(Expr * stmt, Str * fname);
Expr * priv___src_self_initer_til__iface_dyn_clone_call(Expr * stmt);
Expr * priv___src_self_initer_til__iface_dyn_delete_call(Expr * stmt);
Expr * priv___src_self_initer_til__iface_box_ctor(Expr * stmt, Str * sname, Expr * tn, Expr * val, Bool owned);
void priv___src_self_initer_til__gen_interface_clone_delete_for_stmt(Expr * stmt);
void priv___src_self_initer_til__gen_implements_defaults_for_stmt(Expr * stmt, TypeScope * scope);
void priv___src_self_initer_til__gen_substitute_self_type(Expr * fexpr, Str * from_name, Str * to_name);
I32 init_declarations_global(Context * ctx, Expr * program, TypeScope * scope);
U32 count_ast_imports(Expr * body);
I32 init_file(Str * path, Context * ctx);
Bool priv___src_self_initer_til__enum_variant_is_payload_less(Expr * enum_def, Str * variant_name);
Str * clone_call_type_name(Expr * e);
Bool is_pod_enum_clone_of(Expr * e, Expr * edef);
Vec__I32 * Vec__I32_new(void);
void Vec__I32_clear(Vec__I32 * self);
void Vec__I32_push(Vec__I32 * self, I32 * val);
I32 * Vec__I32_unsafe_get(Vec__I32 * self, U32 * i);
I32 * Vec__I32_get(Vec__I32 * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
void Vec__I32_delete(Vec__I32 * self, Bool call_free);
Vec__I32 * Vec__I32_clone(Vec__I32 * self);
U32 Vec__I32_size(void);
Map__Str_I64 * Map__Str_I64_new(void);
Bool Map__Str_I64_has(Map__Str_I64 * self, Str * key);
I64 * Map__Str_I64_get(Map__Str_I64 * self, Str * key, I64 * _err_kind, KeyNotFound * _err_KeyNotFound, Str * loc);
void Map__Str_I64_set(Map__Str_I64 * self, Str * key, I64 * val);
void Map__Str_I64_delete(Map__Str_I64 * self, Bool call_free);
Map__Str_I64 * Map__Str_I64_clone(Map__Str_I64 * self);
U64 Map__Str_I64_hash(Map__Str_I64 * self, HashFn hasher);
U32 Map__Str_I64_size(void);
void context_register_path_mode(Context * ctx, Str * path, Mode * mode);
void context_set_mode_from_path(Context * ctx, Str * path);
void context_enter_file(Context * ctx, Str * path);
void context_init_mode_registry(Context * ctx);
Mode * mode_resolve(Context * ctx, Str * name);
Bool Lang_is(Lang * self, Lang * other);
Bool Lang_eq(Lang * self, Lang * other);
void Lang_delete(Lang * self, Bool call_free);
Lang * Lang_clone(Lang * self);
U32 Lang_size(void);
Str * priv___src_self_targets_til__lang_to_str(Lang * lang);
Bool Target_is(Target * self, Target * other);
Bool Target_eq(Target * self, Target * other);
void Target_delete(Target * self, Bool call_free);
Target * Target_clone(Target * self);
U32 Target_size(void);
Target * target_from_str(Str * s);
Str * priv___src_self_targets_til__target_to_str(Target * target);
Bool priv___src_self_targets_til__target_is_32bit(Target * target);
Str * target_uptr_name(Target * target);
Str * target_usize_name(Target * target);
Lang * priv___src_self_targets_til__default_lang_for_target(Target * target);
Bool priv___src_self_targets_til__is_lang_supported_for_target(Lang * lang, Target * target);
void priv___src_self_targets_til__validate_lang_for_target(Lang * lang, Target * target);
Str * toolchain_command(Target * target, Lang * lang);
Str * priv___src_self_targets_til__target_prefix_args(Target * target);
Str * toolchain_extra_args(Target * target, Str * compiler);
Str * executable_extension(Target * target);
Str * target_system_libs(Target * target);
Str * target_ffi_lib(Target * target);
Str * target_gui_libs(Target * target);
Target * detect_current_target(void);
Bool fa_is_ns(Expr * e, TypeScope * scope);
Bool priv___src_self_typer_til__type_binding_is_type_token(TypeScope * scope, TypeBinding * b);
Expr * make_til_type_expr(Expr * src, Type * t);
void priv___src_self_typer_til__rewrite_til_type_arg(TypeScope * scope, Expr * parent, U32 arg_idx, Type * ptype, I32 in_func, Context * ctx);
OwnType fa_own_type(Expr * e, TypeScope * scope);
priv___src_self_typer_til__CtorArg * priv___src_self_typer_til__CtorArg_Unfilled(void);
priv___src_self_typer_til__CtorArg * priv___src_self_typer_til__CtorArg_Filled(Expr * val);
Bool priv___src_self_typer_til__CtorArg_is(priv___src_self_typer_til__CtorArg * self, priv___src_self_typer_til__CtorArg * other);
void priv___src_self_typer_til__CtorArg_delete(priv___src_self_typer_til__CtorArg * self, Bool call_free);
priv___src_self_typer_til__CtorArg * priv___src_self_typer_til__CtorArg_clone(priv___src_self_typer_til__CtorArg * self);
U32 priv___src_self_typer_til__CtorArg_size(void);
void type_error(Expr * e, Str * msg, Context * ctx);
void type_error_at(Str * path, U32 line, U32 col, Str * msg, Context * ctx);
Expr * find_namespace_func(Expr * sdef, Str * method, TypeScope * scope);
Bool priv___src_self_typer_til__expr_is_comptime(Expr * e, TypeScope * scope);
Declaration * find_ns_decl(Expr * sdef, Str * method);
Bool priv___src_self_typer_til__try_ufcs_rewrite(TypeScope * scope, Expr * e, Expr * fa, Expr * obj, Str * method, Str * type_name, Context * ctx);
Expr * resolve_fn_sig(Expr * fcall, TypeScope * scope);
Bool priv___src_self_typer_til__fdef_returns_unborrowable(FunctionDef * fd, TypeScope * scope);
Bool fcall_returns_own(Expr * fcall, TypeScope * scope);
void priv___src_self_typer_til__check_ref_decl_owned_init(Expr * stmt, TypeScope * scope, Context * ctx);
void priv___src_self_typer_til__check_ref_field_owned_default(Declaration * fd, TypeScope * scope, Context * ctx);
void priv___src_self_typer_til__check_ref_assign_owned_rhs(Expr * stmt, Str * target_name, Expr * rhs, TypeScope * scope, Context * ctx);
void priv___src_self_typer_til__check_ref_local_null_init(Expr * stmt, Context * ctx);
Bool priv___src_self_typer_til__infer_func_ptr_field_call(TypeScope * scope, Expr * e, Expr * fa, Expr * obj, Expr * sdef, Str * method, I32 in_func, Context * ctx);
Bool is_clone_fcall(Expr * e);
void priv___src_self_typer_til__validate_fcall_own_args(TypeScope * scope, Expr * e, TypeBinding * callee_bind, Context * ctx);
Bool priv___src_self_typer_til__infer_struct_constructor_fcall(TypeScope * scope, Expr * e, Str * name, I32 in_func, Context * ctx);
Bool priv___src_self_typer_til__infer_struct_constructor_fcall_impl(TypeScope * scope, Expr * sdef, Expr * e, Str * name, I32 in_func, Context * ctx);
Expr * resolve_default_value(Expr * default_value, Expr * call_expr, Context * ctx);
Bool priv___src_self_typer_til__name_is_interface(Str * name, TypeScope * scope);
Bool priv___src_self_typer_til__type_implements_iface(Str * cname, Str * iface, TypeScope * scope);
void priv___src_self_typer_til__validate_fcall_arg(Expr * arg, Type * ptype, Str * ptype_name, Str * param_name, Context * ctx);
void priv___src_self_typer_til__infer_and_validate_fcall_args(TypeScope * scope, Expr * e, TypeBinding * callee_bind, I32 in_func, Context * ctx);
void priv___src_self_typer_til__resolve_fcall_return_type(TypeScope * scope, Expr * e, Str * name, TypeBinding * callee_bind, I32 in_func, Context * ctx);
Bool priv___src_self_typer_til__is_self_conversion_method(Str * method, Str * type_name);
Str * priv___src_self_typer_til__obj_method_type_name(Expr * obj);
Str * priv___src_self_typer_til__numeric_conv_target_name(Str * method);
Bool priv___src_self_typer_til__infer_field_access_fcall(TypeScope * scope, Expr * e, I32 in_func, Context * ctx);
void priv___src_self_typer_til__check_priv_access(Expr * e, Str * name, TypeBinding * b, Context * ctx);
void priv___src_self_typer_til__check_priv_type_name(Expr * e, Str * name, TypeScope * scope, Context * ctx);
void priv___src_self_typer_til__check_member_priv(Expr * e, Str * owner_name, Str * member_name, Bool member_is_priv, Context * ctx);
void priv___src_self_typer_til__check_free_managed_local(TypeScope * scope, Expr * e, Context * ctx);
void priv___src_self_typer_til__check_move_managed_dest(TypeScope * scope, Expr * e, Context * ctx);
U32 priv___src_self_typer_til__cast_int_size(Type * t);
Bool priv___src_self_typer_til__cast_is_signed(Type * t);
Bool priv___src_self_typer_til__cast_pair_ok(Type * src, Type * target);
void priv___src_self_typer_til__infer_cast_fcall(TypeScope * scope, Expr * e, I32 in_func, Context * ctx);
Bool priv___src_self_typer_til__infer_funcptr_call_via_cast(TypeScope * scope, Expr * e, I32 in_func, Context * ctx);
void priv___src_self_typer_til__infer_array_vec_fcall(TypeScope * scope, Expr * e, Str * name, I32 in_func, Context * ctx);
void priv___src_self_typer_til__infer_fcall_expr(TypeScope * scope, Expr * e, I32 in_func, Context * ctx);
void infer_expr(TypeScope * scope, Expr * expr, I32 in_func, Context * ctx);
void priv___src_self_typer_til__infer_ident_expr(TypeScope * scope, Expr * expr, Context * ctx);
void priv___src_self_typer_til__infer_named_arg_expr(TypeScope * scope, Expr * expr, I32 in_func, Context * ctx);
void priv___src_self_typer_til__infer_map_lit_expr(TypeScope * scope, Expr * expr, I32 in_func, Context * ctx);
void priv___src_self_typer_til__infer_set_lit_expr(TypeScope * scope, Expr * expr, I32 in_func, Context * ctx);
Bool priv___src_self_typer_til__expr_uses_self_field(Expr * e, Str * field_name);
void priv___src_self_typer_til__check_user_delete_frees_own_fields(Str * struct_name, Expr * sdef, Context * ctx);
void priv___src_self_typer_til__typer_resolve_enum_payload_types(EnumDef * edef, TypeScope * scope, Context * ctx);
Bool priv___src_self_typer_til__interface_method_conforms(Str * iface_name, Str * impl_name, Expr * iface_fd, Expr * impl_fd);
void priv___src_self_typer_til__infer_type_def_expr(TypeScope * scope, Expr * expr, Context * ctx);
Bool priv___src_self_typer_til__is_shallow_struct(Str * type_name, TypeScope * scope, Context * ctx);
Bool priv___src_self_typer_til__is_auto_shallow_type(Type * t, Str * type_name, TypeScope * scope, Context * ctx);
void priv___src_self_typer_til__infer_func_sig_expr(TypeScope * scope, Expr * expr);
void priv___src_self_typer_til__check_ref_function_returns(TypeScope * func_scope, Expr * expr, Context * ctx);
Str * priv___src_self_typer_til__first_borrowed_capture_name(Expr * e);
Str * priv___src_self_typer_til__closure_borrowed_capture_name(Expr * e, TypeScope * scope);
void priv___src_self_typer_til__check_returned_borrowed_closure_captures_in(Expr * e, TypeScope * func_scope, Context * ctx);
void priv___src_self_typer_til__check_returned_borrowed_closure_captures(TypeScope * func_scope, Expr * expr, Context * ctx);
void priv___src_self_typer_til__infer_func_def_expr(TypeScope * scope, Expr * expr, Context * ctx);
void priv___src_self_typer_til__check_unused_params(TypeScope * func_scope, Expr * expr, Context * ctx);
void priv___src_self_typer_til__check_unused_mut_params(TypeScope * func_scope, Expr * expr, Str * path, Context * ctx);
void check_unused_locals(TypeScope * scope, Str * path, Context * ctx);
void check_unused_mut_locals(TypeScope * scope, Str * path, Context * ctx);
I32 check_unused_priv_top_level(TypeScope * scope, Context * ctx);
I32 check_unused_priv_members_in_program(Expr * program, Str * path, Context * ctx);
void priv___src_self_typer_til__narrow_return_literal(TypeScope * scope, Expr * rv, Context * ctx);
Expr * priv___src_self_typer_til__make_owned_iface_box(Str * iface_name, Str * concrete_name, Expr * value, U32 line, U32 col);
void priv___src_self_typer_til__box_return_value(TypeScope * scope, Expr * stmt, I32 in_func, Context * ctx);
Bool priv___src_self_typer_til__fcall_has_injected_err_arg(Expr * e);
void priv___src_self_typer_til__infer_return_stmt(TypeScope * scope, Expr * stmt, I32 in_func, I32 returns_ref, Context * ctx);
void priv___src_self_typer_til__infer_if_stmt(TypeScope * scope, Expr * stmt, I32 in_func, I32 in_loop, I32 returns_ref, Context * ctx);
void priv___src_self_typer_til__infer_field_access_expr(TypeScope * scope, Expr * expr, I32 in_func, Context * ctx);
void priv___src_self_typer_til__mark_field_assign_root_written(TypeScope * scope, Expr * obj);
void priv___src_self_typer_til__infer_field_assign_stmt(TypeScope * scope, Expr * stmt, I32 in_func, Context * ctx);
void priv___src_self_typer_til__infer_while_stmt(TypeScope * scope, Expr * stmt, I32 in_func, I32 returns_ref, Context * ctx);
Bool priv___src_self_typer_til__infer_decl_type_def(TypeScope * scope, Expr * stmt, Context * ctx);
Bool priv___src_self_typer_til__infer_decl_func_def(TypeScope * scope, Expr * stmt, Context * ctx);
Bool priv___src_self_typer_til__infer_decl_type_alias_passthrough(TypeScope * scope, Expr * stmt);
Type * priv___src_self_typer_til__declared_type_for_decl(TypeScope * scope, Expr * stmt, Context * ctx);
void priv___src_self_typer_til__pre_coerce_decl_numeric_literals(Expr * expr, Type * target);
void priv___src_self_typer_til__infer_decl_typed_value(TypeScope * scope, Expr * stmt, I32 in_func, Context * ctx);
void priv___src_self_typer_til__infer_decl_untyped_value(Expr * stmt, Context * ctx);
void priv___src_self_typer_til__finalize_decl_binding(TypeScope * scope, Expr * stmt, I32 in_type_body, Context * ctx);
void priv___src_self_typer_til__infer_decl_stmt(TypeScope * scope, Expr * stmt, I32 in_func, I32 in_type_body, Context * ctx);
Bool is_simple_lvalue_expr(Expr * e);
Bool is_compile_directive(Expr * e);
Bool priv___src_self_typer_til__capture_listed(Vec__Declaration * captures, Str * name);
Bool priv___src_self_typer_til__capture_is_mut(Vec__Declaration * captures, Str * name);
TypeScope * priv___src_self_typer_til__scope_root_ref(TypeScope * s);
void priv___src_self_typer_til__capture_block_check_name(Expr * e, Str * name, I32 is_write, TypeScope * enclosing, TypeScope * block_scope, TypeScope * root, Vec__Declaration * captures, Context * ctx);
void priv___src_self_typer_til__capture_block_check_refs(Expr * e, TypeScope * enclosing, TypeScope * block_scope, TypeScope * root, Vec__Declaration * captures, Context * ctx);
void priv___src_self_typer_til__validate_captures(TypeScope * scope, Vec__Declaration * captures, Expr * errnode, Context * ctx);
void priv___src_self_typer_til__infer_capture_block(TypeScope * scope, Expr * stmt, I32 in_func, I32 in_loop, I32 returns_ref, Context * ctx);
void infer_body_stmt(TypeScope * scope, Expr * body, U32 * i, I32 in_func, I32 in_loop, I32 returns_ref, I32 in_type_body, Context * ctx);
void priv___src_self_typer_til__reregister_scope_defs(Expr * body, TypeScope * scope);
void infer_body(TypeScope * scope, Expr * body, I32 in_func, I32 owns_scope, I32 in_loop, I32 returns_ref, I32 in_type_body, Context * ctx);
void priv___src_self_typer_til__infer_body_unit(TypeScope * scope, Expr * body, I32 in_func, I32 owns_scope, I32 in_loop, I32 returns_ref, I32 in_type_body, Context * ctx);
void normalize_scope_bindings(TypeScope * scope);
I32 priv___src_self_typer_til__type_check_unit(Str * path, Expr * program, TypeScope * scope, Context * ctx);
I32 type_file(Str * path, Context * ctx);
I32 priv___src_self_typer_til__type_decls_file(Str * path, Context * ctx);
I32 priv___src_self_typer_til__type_bodies_file(Str * path, Context * ctx);
void priv___src_self_typer_til__infer_assign_stmt(TypeScope * scope, Expr * stmt, I32 in_func, Context * ctx);
Bool rhs_is_clone_fcall(Expr * rhs);
Bool priv___src_self_typer_til__assign_target_is_func_local(TypeScope * scope, Str * name);
Bool is_numeric_type(Type * t);
Bool is_integral_numeric_type(Type * t);
Bool priv___src_self_typer_til__type_ctor_consumes(Type * t);
Bool priv___src_self_typer_til__is_usize_name(Str * name);
Bool priv___src_self_typer_til__is_uptr_name(Str * name);
Bool priv___src_self_typer_til__can_implicit_usize_coerce(Type * from, Type * to, Str * to_name);
Bool literal_in_range(Str * val_str, Type * target);
Type * priv___src_self_typer_til__type_from_name_at(Str * name, TypeScope * scope, Expr * e, Context * ctx);
Type * type_from_name(Str * name, TypeScope * scope, Context * ctx);
Str * resolve_type_alias(TypeScope * scope, Str * name);
Str * priv___src_self_typer_til__usize_name(TypeScope * scope);
Type * usize_type(TypeScope * scope, Context * ctx);
Bool type_has_cmp(TypeScope * scope, Str * type_name);
Bool priv___src_self_typer_til__type_has_to_str(TypeScope * scope, Str * type_name);
Bool priv___src_self_typer_til__expr_contains_fcall(Expr * e);
Bool expr_uses_var(Expr * e, Str * name);
Bool expr_contains_decl(Expr * e, Str * name);
Bool expr_used_in_nested_func(Expr * e, Str * name);
Str * type_prefix(Type * t);
Str * type_to_name(Type * t);
Expr * make_closure_delete_call(Str * var_name, Expr * src);
Expr * make_delete_call(Str * var_name, Type type, Bool arg_is_own, Bool call_free, Expr * src);
Bool transfer_is_shallow_field_value_copy(Expr * e, Str * var_name, TypeScope * scope);
Expr * make_free_call(Str * var_name, Type type, Expr * src);
Expr * make_clone_call(Str * type_name, Type type, Expr * arg, Expr * src);
Expr * priv___src_self_typer_til__make_to_str_call(Str * type_name, Expr * arg);
Expr * make_ns_call(Str * sname, Str * method, Type ret_type, Expr * src);
Str * variadic_array_type_name(TypeScope * scope, Str * elem_type);
Str * priv___src_self_typer_til__variadic_vec_type_name(TypeScope * scope, Str * elem_type);
Bool priv___src_self_typer_til__is_enum_variant_ctor_with_payload(Expr * expr, TypeScope * scope);
Bool priv___src_self_typer_til__check_own_args(Expr * fdef, Expr * fcall, Str * var_name);
Bool priv___src_self_typer_til__fcall_has_own_arg(Expr * fcall, Str * var_name, TypeScope * scope);
Bool expr_transfers_own(Expr * e, Str * var_name, TypeScope * scope, Context * ctx);
Bool priv___src_self_typer_til__expr_is_borrow_source(Expr * e, TypeScope * scope);
Bool priv___src_self_typer_til__expr_is_stable_field_base(Expr * e, TypeScope * scope);
Bool priv___src_self_typer_til__expr_is_ref_decl_source(Expr * e, TypeScope * scope);
void priv___src_self_typer_til__infer_literal_expr(Expr * expr);
void priv___src_self_typer_til__narrow_dynamic(Expr * expr, Type * target);
Bool fcall_is_get_method(Expr * fcall);
I32 fcall_returns_ref(Expr * fcall, TypeScope * scope);
I32 fcall_returns_shallow(Expr * fcall, TypeScope * scope);
priv___src_self_typer_til__CoverageNode * priv___src_self_typer_til__CoverageNode_clone(priv___src_self_typer_til__CoverageNode * self);
void priv___src_self_typer_til__CoverageNode_delete(priv___src_self_typer_til__CoverageNode * self, Bool call_free);
U64 priv___src_self_typer_til__CoverageNode_hash(priv___src_self_typer_til__CoverageNode * self, HashFn hasher);
U32 priv___src_self_typer_til__CoverageNode_size(void);
void priv___src_self_typer_til__init_coverage_for_enum(priv___src_self_typer_til__CoverageNode * node, Expr * enum_def);
I32 priv___src_self_typer_til__coverage_sub_index(priv___src_self_typer_til__CoverageNode * coverage, Str * variant_name);
Bool priv___src_self_typer_til__is_pattern_covered(TypeScope * scope, priv___src_self_typer_til__CoverageNode * coverage, Str * expected_type_name, Expr * pattern);
void priv___src_self_typer_til__mark_pattern_coverage(TypeScope * scope, priv___src_self_typer_til__CoverageNode * coverage, Str * expected_type_name, Expr * pattern);
void priv___src_self_typer_til__collect_missing_paths(TypeScope * scope, priv___src_self_typer_til__CoverageNode * coverage, Expr * enum_def, Str * prefix, Vec__Str * out, Context * ctx);
void priv___src_self_typer_til__infer_match_expr(TypeScope * scope, Expr * expr, I32 in_func, Context * ctx);
Type * priv___src_self_typer_til__match_arm_value_type(TypeScope * scope, Expr * case_node, Expr * subj, I32 in_func, Context * ctx);
U32 priv___src_self_typer_til__lower_matches_in_stmt(TypeScope * scope, Expr * body, U32 stmt_idx, I32 in_func, I32 in_loop, I32 returns_ref, Context * ctx);
void priv___src_self_typer_til__replace_matches_rec(TypeScope * scope, Expr * node, I32 in_func, I32 in_loop, I32 returns_ref, Context * ctx, Vec__Expr * pre);
Str * priv___src_self_typer_til__lower_one_match(TypeScope * scope, Expr * match_node, I32 in_func, I32 in_loop, I32 returns_ref, Context * ctx, Vec__Expr * pre);
void priv___src_self_typer_til__validate_struct_pattern_rest(TypeScope * scope, Expr * pattern, Context * ctx);
void priv___src_self_typer_til__infer_clike_switch(TypeScope * scope, Expr * stmt, I32 in_func, I32 in_loop, I32 returns_ref, Context * ctx);
Bool priv___src_self_typer_til__infer_switch_stmt(TypeScope * scope, Expr * body, U32 stmt_idx, I32 in_func, I32 in_loop, I32 returns_ref, Context * ctx);
Bool priv___src_self_typer_til__desugar_for_in_range_stmt(TypeScope * scope, Expr * body, U32 stmt_idx, I32 in_func, Context * ctx);
Bool priv___src_self_typer_til__desugar_for_in_collection_stmt(TypeScope * scope, Expr * body, U32 stmt_idx, I32 in_func, Context * ctx);
Bool priv___src_self_typer_til__struct_def_has_field(Expr * sdef, Str * field_name);
Str * priv___src_self_typer_til__collection_elem_type_of(TypeScope * scope, Str * col_type_name);
Bool priv___src_self_typer_til__desugar_for_in_kv_stmt(TypeScope * scope, Expr * body, U32 stmt_idx, I32 in_func, Context * ctx);
Vec__CtorArg * Vec__CtorArg_new(void);
U32 Vec__CtorArg_len(Vec__CtorArg * self);
void Vec__CtorArg_clear(Vec__CtorArg * self);
void Vec__CtorArg_push(Vec__CtorArg * self, priv___src_self_typer_til__CtorArg * val);
priv___src_self_typer_til__CtorArg * Vec__CtorArg_unsafe_get(Vec__CtorArg * self, U32 * i);
priv___src_self_typer_til__CtorArg * Vec__CtorArg_get(Vec__CtorArg * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
void Vec__CtorArg_unsafe_set(Vec__CtorArg * self, U32 i, priv___src_self_typer_til__CtorArg * val);
void Vec__CtorArg_set(Vec__CtorArg * self, U32 i, priv___src_self_typer_til__CtorArg * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
void Vec__CtorArg_delete(Vec__CtorArg * self, Bool call_free);
Vec__CtorArg * Vec__CtorArg_clone(Vec__CtorArg * self);
U32 Vec__CtorArg_size(void);
Vec__CoverageNode * Vec__CoverageNode_new(void);
void Vec__CoverageNode_clear(Vec__CoverageNode * self);
void Vec__CoverageNode_push(Vec__CoverageNode * self, priv___src_self_typer_til__CoverageNode * val);
priv___src_self_typer_til__CoverageNode * Vec__CoverageNode_unsafe_get(Vec__CoverageNode * self, U32 * i);
priv___src_self_typer_til__CoverageNode * Vec__CoverageNode_get(Vec__CoverageNode * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
void Vec__CoverageNode_delete(Vec__CoverageNode * self, Bool call_free);
Vec__CoverageNode * Vec__CoverageNode_clone(Vec__CoverageNode * self);
U32 Vec__CoverageNode_size(void);
void desugar_user_func_fcall_args(TypeScope * scope, Expr * e, Str * name, TypeBinding * callee_bind, Context * ctx);
Bool priv___src_self_desugarer_til__typer_is_lambda_target(Expr * e);
I64 priv___src_self_desugarer_til__typer_lift_one_default_value(Declaration * dd, Vec__Expr * top_level, I64 * counter);
I64 priv___src_self_desugarer_til__typer_lift_lambdas_in_expr(Expr * e, Vec__Expr * top_level, I64 * counter);
void priv___src_self_desugarer_til__typer_register_lifted_lambda(TypeScope * scope, Expr * lifted, Context * ctx);
void typer_lift_lambdas(TypeScope * scope, Expr * prog, Context * ctx);
void priv___src_self_desugarer_til__seed_guard_receiver_types(Context * ctx, Expr * e, TypeScope * scope);
void lower_guard_bang_calls(TypeScope * scope, Expr * guard_if, Vec__Expr * dest, Expr * resolve_body, Context * ctx);
Bool subtree_references_name(Expr * e, Str * name);
Str * priv___src_self_desugarer_til__guess_expr_type_name(Expr * e);
Str * priv___src_self_desugarer_til__guess_local_type(Expr * e, Str * var_name);
Str * priv___src_self_desugarer_til__guess_prior_local_type_in_vec(Vec__Expr * stmts, U32 upto, Str * var_name);
void priv___src_self_desugarer_til__seed_prior_local_types(Context * ctx, Vec__Expr * stmts, U32 upto);
void priv___src_self_desugarer_til__collect_throw_ident_names(Expr * e, Set__Str * names);
void priv___src_self_desugarer_til__annotate_throw_ident_expr_types(Expr * e, Expr * root_body);
Bool priv___src_self_desugarer_til__subtree_has_throw_type(Expr * e, Expr * root_body, Str * type_name);
Bool priv___src_self_desugarer_til__has_prior_throw_type_in_vec(Vec__Expr * stmts, Expr * root_body, U32 upto, Str * type_name);
Str * priv___src_self_desugarer_til__throw_type_name_for_with_body(Expr * e, Expr * body);
Bool priv___src_self_desugarer_til__subtree_has_throw_catch(Expr * e);
Bool priv___src_self_desugarer_til__subtree_has_pending_throw(Expr * e);
Bool subtree_has_bang(Expr * e);
void priv___src_self_desugarer_til__annotate_throw_types_in(Expr * e, Expr * root_body);
Str * priv___src_self_desugarer_til__err_slot_name(Str * t);
void append_err_out_params(Vec__Declaration * params, Vec__Str * throw_types);
Expr * make_int_lit(I64 n, U32 line, U32 col);
Expr * priv___src_self_desugarer_til__make_typed_mut_decl(Str * name, Str * type_name, Expr * init, U32 line, U32 col);
Expr * priv___src_self_desugarer_til__make_assign_stmt(Str * name, Expr * rhs, U32 line, U32 col);
Expr * make_default_value_expr(Str * type_name, U32 line, U32 col);
I64 priv___src_self_desugarer_til__tag_for_type(Context * ctx, Str * type_name, Vec__Str * _type_to_tag_names);
void priv___src_self_desugarer_til__register_throw_type(Context * ctx, Str * name);
Expr * make_if_kind_eq_zero_wrap(Expr * stmt, U32 line, U32 col);
void priv___src_self_desugarer_til__rewrite_ident(Expr * e, Str * old_name, Str * new_name);
Expr * priv___src_self_desugarer_til__lower_catch_node(Context * ctx, Expr * catch_node, Vec__Str * type_to_tag_names);
void priv___src_self_desugarer_til__register_func_throws(Context * ctx, Str * name, Vec__Str * throws_list);
void extend_throwing_func_sigs(Context * ctx, Expr * e);
void priv___src_self_desugarer_til__clear_bang_flag(Expr * e);
Str * priv___src_self_desugarer_til__find_bang_callee_name(Expr * e);
Expr * priv___src_self_desugarer_til__find_bang_fcall(Expr * e);
Str * priv___src_self_desugarer_til__normalize_ctor_type(Str * tn);
Str * priv___src_self_desugarer_til__struct_field_type(Context * ctx, Str * type_name, Str * field_name);
Str * priv___src_self_desugarer_til__resolve_value_type(Context * ctx, Expr * e, Expr * body);
Str * priv___src_self_desugarer_til__callee_owning_type(Context * ctx, Expr * fcall, Expr * body);
Str * priv___src_self_desugarer_til__registry_exact_key(Context * ctx, Str * key);
Str * priv___src_self_desugarer_til__register_method_throws_from_scope(Context * ctx, Str * owner, Str * method);
Str * priv___src_self_desugarer_til__registry_suffix_key(Context * ctx, Str * method);
Str * priv___src_self_desugarer_til__find_callee_throws_key(Context * ctx, Expr * fcall, Expr * body);
Bool priv___src_self_desugarer_til__pending_remove_all_matching(Vec__Str * pending, Str * type_name);
Bool priv___src_self_desugarer_til__vec_str_contains(Vec__Str * v, Str * name);
void priv___src_self_desugarer_til__vec_str_push_uniq(Vec__Str * v, Str * name);
void priv___src_self_desugarer_til__validate_one_fcall_consolidated(Context * ctx, Expr * e, Expr * body, Vec__Str * pending, Vec__Str * seen, Vec__Str * types_to_declare, Str * path);
void priv___src_self_desugarer_til__inject_err_args_on_one_fcall_consolidated(Context * ctx, Expr * e, Expr * body);
void priv___src_self_desugarer_til__validate_and_inject_expr_consolidated(Context * ctx, Expr * e, Expr * body, Vec__Str * pending, Vec__Str * seen, Vec__Str * types_to_declare, Str * path);
Expr * priv___src_self_desugarer_til__build_bang_lowered(Context * ctx, Str * error_type, U32 line, U32 col);
void priv___src_self_desugarer_til__hoist_walk_consolidated(Context * ctx, Expr * parent, U32 child_idx, Expr * body, Vec__Expr * pre_stmts, Vec__Str * types_to_declare, Vec__Str * seen);
void priv___src_self_desugarer_til__hoist_nested_bangs_consolidated(Context * ctx, Expr * stmt, Expr * body, Vec__Expr * pre_stmts, Vec__Str * types_to_declare, Vec__Str * seen);
void priv___src_self_desugarer_til__register_bang_guard_throws(Context * ctx, Expr * guard, Expr * root_body, Vec__Str * types_to_declare, Vec__Str * seen);
void priv___src_self_desugarer_til__process_match_arms_in(Context * ctx, Expr * e, Expr * root_body, Vec__Str * fdef_throws, Vec__Str * pending, Vec__Str * seen, Vec__Str * types_to_declare, Str * path, Str * return_type, OwnType * return_own_type);
void priv___src_self_desugarer_til__process_throw_catch_in_body(Context * ctx, Expr * body, Expr * root_body, Vec__Str * fdef_throws, Vec__Str * pending, Vec__Str * seen, Vec__Str * types_to_declare, Str * path, Str * return_type, OwnType * return_own_type);
void process_throw_catch_in_func_body(Context * ctx, Expr * body, Vec__Str * fdef_throws, Str * return_type, OwnType * return_own_type);
Bool stmt_contains_match(Expr * e);
void splice_stmts_before(Expr * body, U32 idx, Vec__Expr * pre);
Str * priv___src_self_desugarer_til__lookup_variant_payload_type(TypeScope * scope, Str * enum_name, Str * variant_name);
void collect_switch_case_bindings(Context * ctx, Expr * e);
Expr * priv___src_self_desugarer_til__fold_and_chain(Vec__Expr * conds, U32 line, U32 col);
Expr * make_switch_case_condition(TypeScope * scope, Expr * case_body, Expr * match_expr, Expr * sw_ref, U32 sw_line, U32 sw_col);
void replace_switch_stmt_with_block(Expr * body, U32 stmt_idx, Expr * block);
void append_switch_else_if(Expr * root_if, Expr * if_node);
void attach_switch_default_body(Expr * root_if, Expr * default_body);
Bool priv___src_self_desugarer_til__expr_has_unguarded_break(Expr * e);
Bool switch_is_clike(TypeScope * scope, Expr * stmt, Expr * sw_expr, Bool is_match);
Str * priv___src_self_desugarer_til__lvalue_root_name(Expr * e);
void prepend_clike_payload_binding(TypeScope * scope, Expr * sw_expr, Expr * case_node, Str * sw_sname);
void replace_body_stmt_with_block(Expr * body, U32 stmt_idx, Expr * block);
Expr * make_for_in_range_while_body(Str * var_name, Str * cur_name, Str * step, Expr * for_body, U32 line, U32 col, Str * elem_type, Bool var_is_mut);
Expr * priv___src_self_desugarer_til__find_variadic_fcall(Expr * e, TypeScope * scope);
Expr * priv___src_self_desugarer_til__find_kwargs_fcall(Expr * e, TypeScope * scope);
Expr * priv___src_self_desugarer_til__find_array_vec_fcall(Expr * e);
Str * priv___src_self_desugarer_til__set_literal_type_name(TypeScope * scope, Str * elem_type);
Str * priv___src_self_desugarer_til__map_literal_type_name(Str * key_type, Str * val_type);
void priv___src_self_desugarer_til__sync_own_args_from_callee(Expr * call, TypeScope * scope);
Expr * priv___src_self_desugarer_til__build_kwargs_map_decl(Expr * fcall, Str * kw_name);
Expr * priv___src_self_desugarer_til__build_kwargs_map_set(Expr * fcall, TypeScope * scope, Str * kw_name, Expr * named_arg, Context * ctx);
Expr * priv___src_self_desugarer_til__build_variadic_array_decl(Expr * fcall, TypeScope * scope, Str * elem_type, Str * va_name, U32 vc, Context * ctx);
Str * priv___src_self_desugarer_til__variadic_err_slot_name(Str * va_name, Str * suffix);
Expr * priv___src_self_desugarer_til__build_resolved_struct_default(Str * name, TypeScope * scope, U32 line, U32 col);
void priv___src_self_desugarer_til__build_variadic_err_slots(Str * va_name, Vec__Expr * new_ch, TypeScope * scope, Context * ctx, U32 line, U32 col);
Expr * priv___src_self_desugarer_til__build_variadic_array_set(Expr * fcall, TypeScope * scope, Str * elem_type, Str * va_name, I32 vi, U32 j, Context * ctx);
Expr * priv___src_self_desugarer_til__build_builtin_vec_decl(Expr * fcall, Str * elem_type, Str * vec_name);
Expr * priv___src_self_desugarer_til__build_builtin_vec_push(Expr * fcall, TypeScope * scope, Str * elem_type, Str * vec_name, U32 j, Context * ctx);
void priv___src_self_desugarer_til__rewrite_collection_fcall_to_ident(Expr * fcall, Str * coll_name, Type * coll_type);
Bool priv___src_self_desugarer_til__desugar_array_vec_fcall(Context * ctx, Expr * fcall, Vec__Expr * new_ch, TypeScope * scope);
Bool priv___src_self_desugarer_til__desugar_array_vec_decl(Expr * stmt, Vec__Expr * new_ch, TypeScope * scope, Context * ctx);
Bool priv___src_self_desugarer_til__desugar_set_literal_decl(Expr * stmt, Vec__Expr * new_ch, TypeScope * scope, Context * ctx);
Bool priv___src_self_desugarer_til__desugar_map_literal_decl(Expr * stmt, Vec__Expr * new_ch, TypeScope * scope, Context * ctx);
void priv___src_self_desugarer_til__desugar_one_variadic_fcall(Context * ctx, Expr * e, Vec__Expr * new_ch, TypeScope * scope);
void priv___src_self_desugarer_til__process_call_desugars(Context * ctx, Expr * e, Vec__Expr * new_ch, TypeScope * scope, Bool has_array_vec, Bool has_variadic, Bool has_kwargs);
Bool body_pre_passes(Context * ctx, Expr * body, TypeScope * scope, I32 owns_scope);
void priv___src_self_desugarer_til__apply_hoist_to_stmt(Context * ctx, Expr * stmt, Vec__Expr * new_ch, TypeScope * scope);
void priv___src_self_desugarer_til__apply_call_hoist_delete(Context * ctx, Expr * stmt, Vec__Expr * new_ch, TypeScope * scope, Bool has_array_vec, Bool has_variadic, Bool has_kwargs, Bool do_hoist, Bool needs_delete);
void priv___src_self_desugarer_til__hoist_param_swap_assign(Context * ctx, Expr * stmt, Vec__Expr * hoisted, TypeScope * scope);
Bool priv___src_self_desugarer_til__fcall_variant_ctor_arg_is_own(Expr * expr, U32 i, TypeScope * scope);
void priv___src_self_desugarer_til__hoist_expr(Context * ctx, Expr * expr, Vec__Expr * hoisted, TypeScope * scope);
void priv___src_self_desugarer_til__hoist_decl_rhs(Context * ctx, Expr * stmt, Vec__Expr * hoisted, TypeScope * scope);
void priv___src_self_desugarer_til__hoist_if_cond(Context * ctx, Expr * stmt, Vec__Expr * hoisted, TypeScope * scope);
void priv___src_self_desugarer_til__hoist_return_expr(Context * ctx, Expr * stmt, Vec__Expr * hoisted, TypeScope * scope);
void priv___src_self_desugarer_til__hoist_assign_rhs(Context * ctx, Expr * stmt, Vec__Expr * hoisted, TypeScope * scope);
void priv___src_self_desugarer_til__hoist_field_assign_rhs(Context * ctx, Expr * stmt, Vec__Expr * hoisted, TypeScope * scope);
void priv___src_self_desugarer_til__hoist_stmt_fcall(Context * ctx, Expr * stmt, Vec__Expr * hoisted, TypeScope * scope);
void priv___src_self_desugarer_til__rewrite_variadic_fcall_args(Expr * fcall, Str * va_name, Str * array_type, I32 vi, U32 vc);
U32 priv___src_self_desugarer_til__fcall_variadic_count_via_scope(Expr * fcall, TypeScope * scope);
Bool priv___src_self_desugarer_til__fcall_callee_has_variadic_via_scope(Expr * fcall, TypeScope * scope);
I32 priv___src_self_desugarer_til__fcall_variadic_index_via_scope(Expr * fcall, TypeScope * scope);
I32 priv___src_self_desugarer_til__fcall_kwargs_index_via_scope(Expr * fcall, TypeScope * scope);
I32 priv___src_self_desugarer_til__derive_fcall_kwargs_index(Expr * _fcall, FunctionDef * fdef_data);
Str * priv___src_self_desugarer_til__resolve_variadic_elem_type(Expr * fcall, TypeScope * scope);
Bool priv___src_self_desugarer_til__desugar_pure_splat_variadic_call(Expr * fcall, Str * array_type, I32 vi, U32 vc);
void priv___src_self_desugarer_til__rewrite_kwargs_fcall_args(Expr * fcall, Str * kw_name, I32 ki);
Bool priv___src_self_desugarer_til__field_assign_needs_delete(Expr * stmt, TypeScope * scope);
Expr * priv___src_self_desugarer_til__hoist_to_temp(Context * ctx, Expr * val, Vec__Expr * hoisted, TypeScope * scope, Bool is_own);
priv___src_self_garbager_til__LocalInfo * priv___src_self_garbager_til__LocalInfo_clone(priv___src_self_garbager_til__LocalInfo * self);
void priv___src_self_garbager_til__LocalInfo_delete(priv___src_self_garbager_til__LocalInfo * self, Bool call_free);
U32 priv___src_self_garbager_til__LocalInfo_size(void);
Bool priv___src_self_garbager_til__alias_used_in_stmts(Vec__Expr * stmts, Str * name, Expr * expr);
Vec__Str * priv___src_self_garbager_til__collect_hoist_taint(Str * target, Vec__Expr * preceding);
Bool priv___src_self_garbager_til__rhs_depends_on_var(Expr * rhs, Str * vname, Vec__Expr * preceding);
Bool priv___src_self_garbager_til__var_aliases_target(Str * varname, Str * target, Vec__Expr * preceding);
Bool priv___src_self_garbager_til__is_pod_enum_clone_wrap(Expr * e, TypeScope * scope);
void priv___src_self_garbager_til__collect_scope_locals(Context * ctx, Expr * body, TypeScope * scope, Bool is_program_scope, Vec__LocalInfo * locals_vec);
void priv___src_self_garbager_til__extend_ref_local_lifetimes(Expr * body, Vec__LocalInfo * locals, TypeScope * scope);
void priv___src_self_garbager_til__extend_hoist_view_lifetimes(Expr * body, Vec__LocalInfo * locals);
void priv___src_self_garbager_til__check_use_after_own_transfer(Expr * body, Vec__LocalInfo * locals, Context * ctx);
void priv___src_self_garbager_til__insert_exit_deletes(Expr * body, Vec__LocalInfo * live, Bool return_only);
void priv___src_self_garbager_til__insert_nested_exit_deletes(Expr * stmt, Vec__LocalInfo * locals, U32 stmt_idx);
void priv___src_self_garbager_til__insert_exit_deletes_into_stmt(Expr * stmt, Vec__Expr * body_stmts, Vec__LocalInfo * locals, U32 stmt_idx, Vec__Expr * new_ch);
void priv___src_self_garbager_til__insert_post_stmt_deletes(Expr * stmt, Vec__LocalInfo * locals, U32 stmt_idx, Vec__Expr * new_ch, TypeScope * scope, Vec__Expr * preceding);
void priv___src_self_garbager_til__insert_assign_delete(Expr * stmt, Vec__LocalInfo * locals, Vec__Expr * new_ch);
void priv___src_self_garbager_til__promote_own_transferred_locals(Context * ctx, Expr * body, Vec__LocalInfo * locals);
Bool priv___src_self_garbager_til__stmt_is_conditional_container(Expr * stmt);
Bool priv___src_self_garbager_til__add_delete_to_branch(Expr * branch, priv___src_self_garbager_til__LocalInfo * local, Expr * src);
Bool priv___src_self_garbager_til__sink_nontransfer_paths(Expr * node, priv___src_self_garbager_til__LocalInfo * local, TypeScope * scope, Context * ctx);
void priv___src_self_garbager_til__sink_conditional_transfer_deletes(Expr * body, Vec__LocalInfo * locals, TypeScope * scope, Context * ctx);
Bool priv___src_self_garbager_til__insert_free_calls(Context * ctx, Expr * body, TypeScope * scope, I32 scope_exit);
Bool garbager_destroy_body(Context * ctx, Expr * body, TypeScope * scope);
void garbager_destroy(Context * ctx);
Vec__LocalInfo * Vec__LocalInfo_new(void);
U32 Vec__LocalInfo_len(Vec__LocalInfo * self);
void Vec__LocalInfo_clear(Vec__LocalInfo * self);
void Vec__LocalInfo_push(Vec__LocalInfo * self, priv___src_self_garbager_til__LocalInfo * val);
priv___src_self_garbager_til__LocalInfo * Vec__LocalInfo_unsafe_get(Vec__LocalInfo * self, U32 * i);
void Vec__LocalInfo_delete(Vec__LocalInfo * self, Bool call_free);
Vec__LocalInfo * Vec__LocalInfo_clone(Vec__LocalInfo * self);
U32 Vec__LocalInfo_size(void);
void constfolder_clear_known(Context * ctx);
void constfolder_reset_state(Context * ctx);
void priv___src_self_constfolder_til__collect_assign_targets(Expr * e, Set__Str * names);
Bool priv___src_self_constfolder_til__constfolder_has_macro(Context * ctx, Str * name);
Bool priv___src_self_constfolder_til__constfolder_has_func(Context * ctx, Str * name);
U8 priv___src_self_constfolder_til__hex_digit_value(I8 b);
Str * priv___src_self_constfolder_til__from_source_form(Str * s);
Bool priv___src_self_constfolder_til__needs_source_escape(Str * s);
Str * priv___src_self_constfolder_til__str_to_source_form(Str * s);
Expr * priv___src_self_constfolder_til__value_to_expr(Value val, Expr * src, Context * ctx);
Bool priv___src_self_constfolder_til__result_type_can_fold_to_expr(Type * t, Context * ctx);
Bool priv___src_self_constfolder_til__struct_result_can_fold_to_expr(Str * sname, Context * ctx);
Value priv___src_self_constfolder_til__expr_to_value(Expr * e, Context * ctx);
Bool priv___src_self_constfolder_til__is_known(Context * ctx, Expr * e, Value * out);
Bool priv___src_self_constfolder_til__func_sig_has_dynamic(Expr * fdef);
Bool priv___src_self_constfolder_til__is_known_check(Context * ctx, Expr * e);
Bool priv___src_self_constfolder_til__body_has_local(Expr * body, Str * name);
Bool priv___src_self_constfolder_til__func_uses_unknown_globals(Expr * e, Expr * func_def, Scope * constfolder_scope, Expr * body_root, Bool lenient, Set__Str * visiting, Context * ctx);
Expr * priv___src_self_constfolder_til__extract_trivial_literal_return(Expr * fdef);
void * priv___src_self_constfolder_til__ns_lookup_flat(Str * name, Context * ctx);
Str * priv___src_self_constfolder_til__fa_recv_type_name(Expr * callee, Context * ctx);
Expr * priv___src_self_constfolder_til__try_fast_fold_call(Scope * scope, Expr * fcall, Context * ctx);
Expr * priv___src_self_constfolder_til__try_eval_call(Scope * scope, Expr * fcall, Bool require_known, Context * ctx);
void priv___src_self_constfolder_til__track_literal(Scope * scope, Str * name, Expr * rhs, Context * ctx);
void priv___src_self_constfolder_til__track_literal_known_only(Str * name, Expr * rhs, Context * ctx);
Bool is_macro_call(Expr * e, Context * ctx);
Bool priv___src_self_constfolder_til__is_func_call(Expr * e, Context * ctx);
Bool priv___src_self_constfolder_til__is_va_array_decl(Expr * stmt);
Bool priv___src_self_constfolder_til__is_va_set(Expr * stmt, Str * va);
Bool priv___src_self_constfolder_til__va_name_in(Vec__Str * names, Str * name);
Bool priv___src_self_constfolder_til__va_elements_known(Expr * body, U32 decl_idx, Str * va, Context * ctx);
void priv___src_self_constfolder_til__bind_known_idents_in(Scope * scope, Expr * e, Context * ctx);
void priv___src_self_constfolder_til__interp_va_build_stmt(Scope * scope, Expr * stmt, Str * va, Str * ek, Str * eo, Context * ctx);
Bool priv___src_self_constfolder_til__materialize_va(Scope * scope, Expr * body, U32 decl_idx, Str * va, Context * ctx);
Bool priv___src_self_constfolder_til__va_consumer_args_ok(Expr * call, Str * va, Context * ctx);
void priv___src_self_constfolder_til__fold_va_calls(Scope * scope, Expr * e, Str * va, Context * ctx);
Bool priv___src_self_constfolder_til__is_delete_call_on(Expr * s, Str * name);
I32 priv___src_self_constfolder_til__va_stmt_class(Expr * s, Str * va, Str * ek, Str * eo, Context * ctx);
void priv___src_self_constfolder_til__va_build_dce(Expr * body, Vec__Str * va_done, Context * ctx);
void priv___src_self_constfolder_til__fold_subtree(Scope * scope, Expr * e, Context * ctx);
void process_body(Scope * scope, Expr * body, Context * ctx, Bool at_global);
Bool priv___src_self_constfolder_til__expr_uses_var_p(Expr * e, Str * name, Context * ctx);
void constfolder_register_fold_scope(Scope * global, Expr * prog, Context * ctx);
void constfolder_register_core_constants(Scope * global);
Bool priv___src_self_scavenger_til__scav_fa_is_ns(Expr * e);
Str * priv___src_self_scavenger_til__qualified_name(Str * type_name, Str * method_name);
void vec_push_str(Vec__Str * v, Str * s);
void priv___src_self_scavenger_til__children_filter_expr(Vec__Expr * v, void * marks, U32 n);
void priv___src_self_scavenger_til__children_filter_decl(Vec__Declaration * v, void * marks, U32 n);
void push_qn(Vec__Str * v, Str * type_name, Str * method);
void priv___src_self_scavenger_til__push_builtin_methods(Vec__Str * v, Str * builtin_name, Str * m1, Str * m2, Str * m3);
void collect_refs(Expr * e, Vec__Str * refs);
void scavenge_filter(Expr * program, Set__Str * visited);
U32 priv___src_self_scavenger_til__dyn_call_real_arg_count(Expr * e);
void priv___src_self_scavenger_til__collect_body_refs(Expr * e, Set__Str * refs, Set__Str * candidates);
Str * priv___src_self_scavenger_til__match_trivial_delete(Expr * stmt);
Bool priv___src_self_scavenger_til__rhs_is_pure_byvalue(Expr * e);
void priv___src_self_scavenger_til__prune_trivial_deletes(Expr * e, Set__Str * dropped);
Bool priv___src_self_scavenger_til__dce_one_body(Expr * body, Bool at_top_level);
Bool priv___src_self_scavenger_til__match_named_delete(Expr * stmt, Str * name);
void priv___src_self_scavenger_til__fix_stale_litstr_in_body(Expr * body);
void priv___src_self_scavenger_til__body_dce_walk(Expr * e, Bool at_top_level);
void priv___src_self_scavenger_til__body_dce_ns(Expr * rhs);
void dce_program_bodies(Expr * program);
Str * priv___src_self_loader_til__normalize_mode_name(Str * mode_name);
Str * priv___src_self_loader_til__display_path(Str * p, Str * cwd);
Mode * priv___src_self_loader_til__require_mode(Context * ctx, Str * path, Str * mode_name);
Str * forward_header_path(Str * path);
Str * priv___src_self_loader_til__dir_of(Str * abs);
Str * priv___src_self_loader_til__resolve_link_path(Str * base_dir, Str * root_dir, Str * path);
ProgramUnit * ProgramUnit_clone(ProgramUnit * self);
void ProgramUnit_delete(ProgramUnit * self, Bool call_free);
U64 ProgramUnit_hash(ProgramUnit * self, HashFn hasher);
U32 ProgramUnit_size(void);
Vec__Str * priv___src_self_loader_til__resolve_import_disps(Vec__Str * import_paths, Str * base_dir, Str * lib_dir, Str * cwd);
void priv___src_self_loader_til__extract_one_import(Expr * imp_stmt, Str * path, Vec__Str * paths);
Vec__Str * priv___src_self_loader_til__extract_imports(Expr * body, Str * path);
I32 priv___src_self_loader_til__resolve_imports(Vec__Str * import_paths, Str * base_dir, Set__Str * resolved_set, Vec__Expr * stack, Vec__ProgramUnit * units, Str * lib_dir, Context * ctx, Str * default_mode, Str * cwd);
LoadedProgram * LoadedProgram_clone(LoadedProgram * self);
void LoadedProgram_delete(LoadedProgram * self, Bool call_free);
U32 LoadedProgram_size(void);
void priv___src_self_loader_til__retarget_alias_binding(TypeScope * scope, Str * alias_name, Str * target_name);
void retarget_loaded_aliases(LoadedProgram * lp);
void priv___src_self_loader_til__constfolder_imported(LoadedProgram * lp);
priv___src_self_loader_til__DeclRef * priv___src_self_loader_til__DeclRef_clone(priv___src_self_loader_til__DeclRef * self);
void priv___src_self_loader_til__DeclRef_delete(priv___src_self_loader_til__DeclRef * self, Bool call_free);
U64 priv___src_self_loader_til__DeclRef_hash(priv___src_self_loader_til__DeclRef * self, HashFn hasher);
U32 priv___src_self_loader_til__DeclRef_size(void);
Expr * priv___src_self_loader_til__find_ns_decl_fdef_imported(Context * ctx, Map__Str_DeclRef * top, Str * name);
Set__Str * priv___src_self_loader_til__scavenge_visited_imported(LoadedProgram * lp);
void priv___src_self_loader_til__validate_cli_main(LoadedProgram * lp);
void priv___src_self_loader_til__scavenge_imported(LoadedProgram * lp);
void priv___src_self_loader_til__extract_link_info(LoadedProgram * lp);
void priv___src_self_loader_til__load_mode_file(LoadedProgram * lp, Str * path, Str * cwd);
LoadedProgram * load_program(Str * path, Str * bin_dir, Str * cwd, Str * ext_c_path, Vec__Str * extra_modes);
Str * priv___src_self_loader_til__escape_doc_for_literal_str(Str * raw);
Str * priv___src_self_loader_til__func_kind(FuncType * ft);
Str * priv___src_self_loader_til__til_type_user(Type * t);
void priv___src_self_loader_til__append_packed_entry(Str * packed, Str * name, Str * value);
void priv___src_self_loader_til__append_qualifier_prefix(Str * out, Declaration * d, OwnType * default_own);
void priv___src_self_loader_til__append_fn_signature(Str * out, FunctionDef * fd);
void priv___src_self_loader_til__append_doc_lines_indented(Str * out, Str * doc, Str * indent);
DocMeta * DocMeta_clone(DocMeta * self);
void DocMeta_delete(DocMeta * self, Bool call_free);
U64 DocMeta_hash(DocMeta * self, HashFn hasher);
U32 DocMeta_size(void);
Str * doc_keyword_value(Str * line, Str * key);
Bool doc_false_value(Str * value);
Bool doc_meta_line(Str * line, DocMeta * meta);
DocMeta * parse_doc_meta(Str * doc);
Str * format_doc_for_help(Str * doc);
void priv___src_self_loader_til__append_field_indented(Str * out, Declaration * d);
void priv___src_self_loader_til__append_ns_method_indented(Str * out, Declaration * d);
Str * priv___src_self_loader_til__format_var_info(Str * name, Declaration * dd, TypeScope * scope);
Str * priv___src_self_loader_til__format_func_info(Str * name, FunctionDef * fd);
Str * priv___src_self_loader_til__format_struct_info(Str * name, StructDef * sdef);
Str * priv___src_self_loader_til__format_enum_info(Str * name, EnumDef * edef);
Str * format_decl_info(Expr * stmt, TypeScope * scope);
void priv___src_self_loader_til__collect_member_method_packed(Str * type_name, Declaration * d, Str * info, Str * docs);
void priv___src_self_loader_til__collect_struct_members_packed(Str * type_name, StructDef * sdef, Str * info, Str * docs);
void priv___src_self_loader_til__collect_enum_members_packed(Str * type_name, EnumDef * edef, Str * info, Str * docs);
void collect_decl_packed(Expr * body, TypeScope * scope, Str * info, Str * docs);
Str * build_doc_init_line_cached(Str * escaped_core_info, Str * escaped_core_docs, Str * packed_user_info, Str * packed_user_docs);
ReplCoreDocCache * ReplCoreDocCache_clone(ReplCoreDocCache * self);
void ReplCoreDocCache_delete(ReplCoreDocCache * self, Bool call_free);
U64 ReplCoreDocCache_hash(ReplCoreDocCache * self, HashFn hasher);
U32 ReplCoreDocCache_size(void);
ReplCoreDocCache * build_repl_core_doc_cache(LoadedProgram * lp);
Bool priv___src_self_loader_til__desugar_one_import(Expr * imp_stmt, Vec__Expr * new_ch, Bool is_decl_rhs, Str * decl_name, Bool is_mut, U32 decl_line, U32 decl_col, Context * ctx, Str * resolved_path);
void priv___src_self_loader_til__desugar_namespace_imports(ImportUnit * iu, Context * ctx);
void priv___src_self_loader_til__lazy_substitute_idents(Expr * e, Map__Str_Expr * subs);
Expr * priv___src_self_loader_til__lazy_single_return_value(Expr * body);
Expr * priv___src_self_loader_til__lazy_make_bool_match(Expr * cond, Expr * x, Expr * y, U32 line, U32 col);
Expr * priv___src_self_loader_til__lazy_build_guard_chain(Expr * body, U32 i, U32 n);
Expr * priv___src_self_loader_til__lazy_body_as_expr(Expr * body);
Bool priv___src_self_loader_til__inline_lazy_call(Expr * parent, U32 call_idx, Expr * fdef);
Expr * priv___src_self_loader_til__lazy_eff_arg_clone(Expr * call, Bool is_method, U32 k);
Expr * priv___src_self_loader_til__lazy_build_fold(Expr * call, Bool is_method, U32 lo, U32 hi, Str * name, U32 line, U32 col);
void priv___src_self_loader_til__lazy_try_fold_nary(Expr * parent, U32 idx, Expr * fdef, Str * name);
Bool priv___src_self_loader_til__lazy_call_arity_ok(Expr * call, Expr * fdef);
Map__Str_Expr * priv___src_self_loader_til__lazy_build_subs(Expr * call, Expr * fdef);
Expr * priv___src_self_loader_til__lazy_make_temp_decl(Str * name, Str * type_name, Expr * init, U32 line, U32 col);
Expr * priv___src_self_loader_til__lazy_make_assign(Str * name, Expr * rhs, U32 line, U32 col);
Expr * priv___src_self_loader_til__lazy_stmt_inlinable_call(Expr * call, TypeScope * scope);
Expr * priv___src_self_loader_til__lazy_build_prelude(Expr * call, Expr * fdef, Vec__Expr * new);
Expr * priv___src_self_loader_til__lazy_stmt_value_slot(Expr * s);
void priv___src_self_loader_til__lazy_stmt_inline_body(Expr * body, TypeScope * scope);
void priv___src_self_loader_til__lazy_stmt_inline_walk(Expr * e, TypeScope * scope, I32 depth);
void priv___src_self_loader_til__expand_lazy_in_expr(Expr * e, TypeScope * scope, I32 depth);
void priv___src_self_loader_til__expand_lazy_calls_in_program(LoadedProgram * lp);
I32 type_program_errors(LoadedProgram * lp, Bool run_tests);
void finish_init_and_type_program(LoadedProgram * lp);
I32 init_and_type_program_errors(LoadedProgram * lp, Bool run_tests);
void init_and_type_program(LoadedProgram * lp, Bool run_tests);
void finish_prepare_program(LoadedProgram * lp);
void prepare_program(LoadedProgram * lp, Bool run_tests);
void cmd_ast(LoadedProgram * lp);
Map__Str_DeclRef * Map__Str_DeclRef_new(void);
Bool Map__Str_DeclRef_has(Map__Str_DeclRef * self, Str * key);
priv___src_self_loader_til__DeclRef * Map__Str_DeclRef_get(Map__Str_DeclRef * self, Str * key, I64 * _err_kind, KeyNotFound * _err_KeyNotFound, Str * loc);
void Map__Str_DeclRef_set(Map__Str_DeclRef * self, Str * key, priv___src_self_loader_til__DeclRef * val);
void Map__Str_DeclRef_delete(Map__Str_DeclRef * self, Bool call_free);
Map__Str_DeclRef * Map__Str_DeclRef_clone(Map__Str_DeclRef * self);
U64 Map__Str_DeclRef_hash(Map__Str_DeclRef * self, HashFn hasher);
U32 Map__Str_DeclRef_size(void);
Vec__ProgramUnit * Vec__ProgramUnit_new(void);
U32 Vec__ProgramUnit_len(Vec__ProgramUnit * self);
void Vec__ProgramUnit_clear(Vec__ProgramUnit * self);
void Vec__ProgramUnit_push(Vec__ProgramUnit * self, ProgramUnit * val);
ProgramUnit * Vec__ProgramUnit_unsafe_get(Vec__ProgramUnit * self, U32 * i);
ProgramUnit * Vec__ProgramUnit_get(Vec__ProgramUnit * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
void Vec__ProgramUnit_delete(Vec__ProgramUnit * self, Bool call_free);
Vec__ProgramUnit * Vec__ProgramUnit_clone(Vec__ProgramUnit * self);
U32 Vec__ProgramUnit_size(void);
Vec__DeclRef * Vec__DeclRef_new(void);
void Vec__DeclRef_clear(Vec__DeclRef * self);
priv___src_self_loader_til__DeclRef * Vec__DeclRef_unsafe_get(Vec__DeclRef * self, U32 * i);
void Vec__DeclRef_unsafe_set(Vec__DeclRef * self, U32 i, priv___src_self_loader_til__DeclRef * val);
void Vec__DeclRef_delete(Vec__DeclRef * self, Bool call_free);
Vec__DeclRef * Vec__DeclRef_clone(Vec__DeclRef * self);
U32 Vec__DeclRef_size(void);
priv___src_self_builder_til__CollectionInfo * priv___src_self_builder_til__CollectionInfo_clone(priv___src_self_builder_til__CollectionInfo * self);
void priv___src_self_builder_til__CollectionInfo_delete(priv___src_self_builder_til__CollectionInfo * self, Bool call_free);
U32 priv___src_self_builder_til__CollectionInfo_size(void);
priv___src_self_builder_til__DynCallInfo * priv___src_self_builder_til__DynCallInfo_clone(priv___src_self_builder_til__DynCallInfo * self);
void priv___src_self_builder_til__DynCallInfo_delete(priv___src_self_builder_til__DynCallInfo * self, Bool call_free);
U32 priv___src_self_builder_til__DynCallInfo_size(void);
Str * closure_call_name(Str * name);
Str * closure_value_name(Str * name);
Expr * priv___src_self_builder_til__resolve_local_fn_sig(Context * ctx, Str * name);
Expr * priv___src_self_builder_til__resolve_decl_fn_sig(Expr * rhs, Declaration * dd, TypeScope * scope, Context * ctx);
Expr * priv___src_self_builder_til__fcall_fn_sig(Expr * fcall, Context * ctx);
Bool priv___src_self_builder_til__is_stack_local(Str * name, Context * ctx);
Bool priv___src_self_builder_til__is_stack_lit_str_local(Str * name, Context * ctx);
Bool priv___src_self_builder_til__is_current_func_param(Str * name, Context * ctx);
Bool priv___src_self_builder_til__is_value_global(Str * name, Context * ctx);
Bool priv___src_self_builder_til__is_ref_global(Str * name, Context * ctx);
Bool priv___src_self_builder_til__is_ref_local(Str * name, Context * ctx);
Bool priv___src_self_builder_til__use_dot_access(Expr * obj, Context * ctx);
Bool priv___src_self_builder_til__is_primitive_type(Str * name);
Bool priv___src_self_builder_til__is_pod_enum(Str * enum_name, Context * ctx);
Bool priv___src_self_builder_til__is_pod_enum_clone_call(Expr * e, Context * ctx);
Bool priv___src_self_builder_til__is_pod_struct_user_clone(Expr * e, Context * ctx);
void priv___src_self_builder_til__emit_pod_struct_user_clone_arg(File * f, Expr * e, I32 depth, Context * ctx);
void priv___src_self_builder_til__emit_pod_enum_clone_arg(File * f, Expr * e, I32 depth, Context * ctx);
Bool priv___src_self_builder_til__is_pod_struct(Str * struct_name, Context * ctx);
Bool priv___src_self_builder_til__is_funcsig_type(Str * name, Context * ctx);
Bool priv___src_self_builder_til__is_ext_h_type(Str * name);
Bool priv___src_self_builder_til__is_exported_top_level_global(Expr * stmt);
Expr * priv___src_self_builder_til__find_struct_def(Str * name, Context * ctx);
Expr * priv___src_self_builder_til__find_callee_fdef(Str * name, Context * ctx);
Bool priv___src_self_builder_til__builder_callee_is_core(Str * name, Context * ctx);
Str * priv___src_self_builder_til__core_binop_to_c(Str * op);
Str * priv___src_self_builder_til__fa_struct_name(Expr * e);
Bool priv___src_self_builder_til__builder_fa_is_ptr_with_fname(Str * sname, Str * fname, Context * ctx);
Bool priv___src_self_builder_til__builder_fa_is_ptr(Expr * e, Context * ctx);
Bool priv___src_self_builder_til__builder_fa_is_ns_with_fname(Expr * e, Str * sname, Str * fname, Context * ctx);
Bool priv___src_self_builder_til__builder_fa_is_ns(Expr * e, Context * ctx);
Bool priv___src_self_builder_til__is_shallow_param(Str * name, Context * ctx);
Bool priv___src_self_builder_til__callee_returns_shallow(Str * callee_name, Context * ctx);
Bool priv___src_self_builder_til__callee_returns_dynamic(Str * callee_name, Context * ctx);
Str * priv___src_self_builder_til__delete_call_free_lit(Str * type_name, Bool set_free, Context * ctx);
Bool priv___src_self_builder_til__callee_param_is_shallow(Str * callee_name, U32 arg_index, Context * ctx);
Bool priv___src_self_builder_til__callee_param_is_usize(Str * callee_name, U32 arg_index, Context * ctx);
Bool priv___src_self_builder_til__callee_param_is_uptr(Str * callee_name, U32 arg_index, Context * ctx);
Bool priv___src_self_builder_til__callee_param_is_own(Str * callee_name, U32 arg_index, Context * ctx);
Str * priv___src_self_builder_til__callee_param_explicit_type(Str * callee_name, U32 arg_index, Context * ctx);
Bool priv___src_self_builder_til__fcall_is_shallow_return(Expr * fcall, Context * ctx);
Bool priv___src_self_builder_til__fcall_returns_dynamic(Expr * fcall, Context * ctx);
Str * priv___src_self_builder_til__til_type_to_c(Type t);
void priv___src_self_builder_til__seed_primitive_names(Set__Str * emitted);
Str * priv___src_self_builder_til__extern_decl_ctype(Type t, Type rhs_t, Context * ctx);
Str * priv___src_self_builder_til__resolve_decl_ctype(Type t, Type rhs_t, Str * explicit, Context * ctx);
Str * priv___src_self_builder_til__c_type_name(Type t, Str * struct_name, Context * ctx);
Str * priv___src_self_builder_til__func_to_c(Str * name);
Str * priv___src_self_builder_til__type_name_to_c(Str * name, Context * ctx);
Str * priv___src_self_builder_til__type_name_to_c_value(Str * name, Context * ctx);
Bool priv___src_self_builder_til__builder_is_type_gen_macro_def(Expr * fdef);
Str * priv___src_self_builder_til__builder_variadic_array_type_name(Context * ctx, Str * elem_type);
Str * priv___src_self_builder_til__builder_variadic_vec_type_name(Context * ctx, Str * elem_type);
Str * priv___src_self_builder_til__builder_variadic_array_ctype(Context * ctx, Str * elem_type);
Str * priv___src_self_builder_til__builder_variadic_vec_ctype(Context * ctx, Str * elem_type);
Bool priv___src_self_builder_til__enum_ctor_payload_is_own(Str * callee_name, Expr * fcall, Context * ctx);
Bool priv___src_self_builder_til__templated_container_method_arg_is_own(Str * sname, Str * method, U32 arg_index);
Bool priv___src_self_builder_til__templated_container_fcall_arg_is_own(Str * callee_name, U32 arg_index);
File * priv___src_self_builder_til__emit_usize(File * f, U32 v);
File * priv___src_self_builder_til__emit_i32(File * f, I32 v);
File * priv___src_self_builder_til__emit_indent(File * f, I32 depth);
U32 priv___src_self_builder_til__c_lit_byte_count(Str * s);
void priv___src_self_builder_til__collect_ident_refs(Expr * e, Set__Str * refs);
void priv___src_self_builder_til__emit_til_default(File * f, Type t);
Str * priv___src_self_builder_til__param_ctype(FunctionDef * fd, U32 i, Context * ctx);
void priv___src_self_builder_til__emit_param_list(File * f, Expr * fdef, Bool with_names, Bool for_ext_decl, Context * ctx);
void priv___src_self_builder_til__collect_dyn_methods(Expr * e, Vec__DynCallInfo * methods);
void priv___src_self_builder_til__collect_collection_builtins(Expr * e, Vec__CollectionInfo * infos);
void priv___src_self_builder_til__emit_field(File * f, Str * var, Str * field, Context * ctx);
Str * priv___src_self_builder_til__get_stack_local_ctype(Str * name, Context * ctx);
Str * priv___src_self_builder_til__resolve_callee_name(Expr * fcall);
Str * priv___src_self_builder_til__fcall_return_ctype(Expr * fcall, Context * ctx);
Bool priv___src_self_builder_til__fcall_has_inline_capturing_func_arg(Expr * e);
void priv___src_self_builder_til__emit_til_closure_cleanup(File * f, Str * name);
void priv___src_self_builder_til__emit_user_fcall_args(File * f, Expr * e, Str * callee_name, I32 depth, Context * ctx, Bool wrap_inline_closures);
void priv___src_self_builder_til__emit_user_fcall_with_inline_closure_cleanup(File * f, Expr * e, Str * source_name, Str * cname, I32 depth, Context * ctx);
void priv___src_self_builder_til__check_fcall_mut_args(Context * ctx, Expr * e);
void priv___src_self_builder_til__collect_unsafe_to_hoist(Context * ctx, Expr * body);
void priv___src_self_builder_til__builder_reset_func_scratch(Context * ctx);
Bool priv___src_self_builder_til__builder_is_file_static_str_lit_name(Str * name);
void priv___src_self_builder_til__builder_reset_str_lit_pool(Context * ctx);
Str * priv___src_self_builder_til__builder_register_str_lit(Context * ctx, Str * s);
void priv___src_self_builder_til__builder_register_str_lit_alias(Context * ctx, Str * name, Str * s);
void priv___src_self_builder_til__builder_emit_str_lit_decl(File * f, Str * name, Str * s);
void priv___src_self_builder_til__builder_register_str_lits_for_expr(Expr * e, Context * ctx);
void priv___src_self_builder_til__builder_register_dyn_type_to_str_lits(LoadedProgram * lp);
void priv___src_self_builder_til__builder_register_str_lits(LoadedProgram * lp);
void priv___src_self_builder_til__builder_emit_str_lit_pool(File * f, Context * ctx);
void priv___src_self_builder_til__collect_dyn_has_methods(Expr * e, Vec__Str * methods);
Bool priv___src_self_builder_til__fcall_is_struct_ctor(Expr * e);
Bool priv___src_self_builder_til__pod_ctor_args_are_safe(Expr * ctor, Context * ctx);
void priv___src_self_builder_til__emit_pod_compound_literal(File * f, Expr * ctor, I32 depth, Context * ctx);
void priv___src_self_builder_til__emit_stmt_decl(File * f, Expr * e, I32 depth, Context * ctx);
Str * priv___src_self_builder_til__builder_get_c_return_type(Context * ctx);
Str * priv___src_self_builder_til__emit_return_ctype(Expr * rv, Context * ctx);
void priv___src_self_builder_til__emit_return_box(File * f, Expr * e, I32 depth, Context * ctx);
void priv___src_self_builder_til__emit_stmt_return(File * f, Expr * e, I32 depth, Context * ctx);
Bool priv___src_self_builder_til__is_noop_delete_stmt(Expr * e, Context * ctx);
void priv___src_self_builder_til__emit_stmt_switch(File * f, Expr * e, I32 depth, Context * ctx);
void priv___src_self_builder_til__emit_stmt(File * f, Expr * e, I32 depth, Context * ctx);
void priv___src_self_builder_til__emit_fcall_funcptr_cast(File * f, Expr * e, Expr * sig);
void emit_fcall_closure_call(File * f, Expr * e, Expr * callee, Expr * sig, I32 depth, Context * ctx);
void priv___src_self_builder_til__emit_fcall_funcptr_args(File * f, Expr * e, Expr * sig, I32 depth, Context * ctx);
File * emit_capturing_closure_value(File * f, Expr * e, I32 * _depth, Context * _ctx);
void priv___src_self_builder_til__emit_str_lit_expr(File * f, Str * s, Context * ctx);
void priv___src_self_builder_til__emit_str_lit_temp_expr(File * f, Str * s);
Str * priv___src_self_builder_til__num_lit_to_c(Str * text);
File * priv___src_self_builder_til__emit_expr(File * f, Expr * e, I32 depth, Context * ctx);
void priv___src_self_builder_til__emit_body(File * f, Expr * body, I32 depth, Context * ctx);
void priv___src_self_builder_til__emit_ctor_fields(File * f, Str * var, Expr * ctor, I32 depth, Context * ctx);
void priv___src_self_builder_til__emit_ns_inits(File * f, I32 depth, LoadedProgram * lp);
void priv___src_self_builder_til__emit_body_scoped(File * f, Expr * body, I32 depth, Context * ctx);
File * priv___src_self_builder_til__emit_deref(File * f, Expr * e, I32 depth, Context * ctx);
File * priv___src_self_builder_til__emit_as_ptr(File * f, Expr * e, I32 depth, Bool is_own, Context * ctx);
Str * priv___src_self_builder_til__cli_view_box(Str * ctype, Str * conv, Str * arg);
Str * priv___src_self_builder_til__cli_box_expr(Str * ttype, Str * arg);
void priv___src_self_builder_til__emit_cli_parse_value(File * f, Str * ind, Str * ttype, Str * var, Str * arg);
void priv___src_self_builder_til__emit_func_def(File * f, Str * name, Expr * func_def, Mode * mode, Bool is_static, LoadedProgram * lp);
void emit_capturing_closure_func(File * f, Expr * closure_expr, Set__Str * emitted, LoadedProgram * lp);
void emit_capturing_closures_in_expr(File * f, Expr * e, Set__Str * emitted, LoadedProgram * lp);
void emit_capturing_closures_lp(File * f, LoadedProgram * lp);
void priv___src_self_builder_til__emit_struct_typedef(File * f, Str * name, Expr * struct_def, Set__Str * emitted_tags);
void priv___src_self_builder_til__emit_ns_method(File * f, Str * name, Str * dd_name, Expr * fdef, LoadedProgram * lp);
void priv___src_self_builder_til__emit_struct_funcs(File * f, Str * name, Expr * struct_def, LoadedProgram * lp);
void priv___src_self_builder_til__emit_enum_def(File * f, Str * name, Expr * enum_def, LoadedProgram * lp);
void priv___src_self_builder_til__emit_enum_struct_body(File * f, Str * ename, Expr * enum_def, Context * ctx);
void priv___src_self_builder_til__topo_emit_struct_enum_defs_lp(File * f, Set__Str * emitted, LoadedProgram * lp);
Str * priv___src_self_builder_til__func_return_ctype(FunctionDef * fd, Context * ctx);
void priv___src_self_builder_til__emit_func_forward_decl(File * f, Str * name, Expr * fdef, Bool top_level, Context * ctx);
void priv___src_self_builder_til__emit_closure_forward_decl(File * f, Str * name, Expr * fdef, Context * ctx);
void priv___src_self_builder_til__emit_closure_wrapper_def(File * f, Str * name, Expr * fdef, Context * ctx);
void priv___src_self_builder_til__emit_funcsig_typedef(File * f, Str * name, Expr * fdef, Context * _ctx);
void emit_closure_runtime_types(File * f);
void priv___src_self_builder_til__emit_funcsig_typedefs_lp(File * f, LoadedProgram * lp);
void priv___src_self_builder_til__emit_header_forward_decls_lp(File * f, LoadedProgram * lp);
Bool priv___src_self_builder_til__builder_ns_has_func(Expr * def, Str * method);
Bool priv___src_self_builder_til__builder_ns_func_returns_shallow(Expr * def, Str * method);
void priv___src_self_builder_til__emit_enum_eq_ext_decl(File * f, Str * enum_name, Expr * enum_def);
void priv___src_self_builder_til__emit_header_defs_and_funcs_lp(File * f, LoadedProgram * lp);
void priv___src_self_builder_til__emit_header_global_decls_lp(File * f, LoadedProgram * lp);
I32 build_forward_header_lp(Str * fwd_path, LoadedProgram * lp);
I32 priv___src_self_builder_til__build_header_lp(Str * h_path, LoadedProgram * lp);
Bool priv___src_self_builder_til__emit_binding_ns_method(File * f, Str * fdd_name, FunctionDef * fd, Bool * has_ns);
void priv___src_self_builder_til__emit_binding_ns_methods(File * f, Expr * def);
I32 priv___src_self_builder_til__build_til_binding(LoadedProgram * lp, Str * til_path, Str * lib_name);
Str * priv___src_self_builder_til__type_name_to_ctypes(Str * name);
Str * priv___src_self_builder_til__type_name_to_ctypes_param(Str * name, Bool is_shallow);
Str * priv___src_self_builder_til__type_name_to_ctypes_return(Str * name, Bool is_shallow);
I32 priv___src_self_builder_til__build_python_binding(LoadedProgram * lp, Str * py_path, Str * lib_name);
I32 priv___src_self_builder_til__compile_lib(Str * c_path, Str * lib_name, Str * ext_c_path, Str * user_c_path, Str * link_flags, Str * include_flags, Target * target, Str * cc_override, Bool asan);
Bool priv___src_self_builder_til__is_gui_auto_import(Str * auto_import);
I32 priv___src_self_builder_til__compile_c(Str * c_path, Str * bin_path, Str * ext_c_path, Str * user_c_path, Str * link_flags, Str * include_flags, Target * target, Str * cc_override, Str * mode_auto_import, Bool asan, Bool prof);
void priv___src_self_builder_til__register_funcsig_prog(Expr * prog, Context * ctx);
void priv___src_self_builder_til__emit_global_inits_prog(File * f, Expr * prog, Context * ctx);
void priv___src_self_builder_til__emit_global_inits(File * f, LoadedProgram * lp);
void priv___src_self_builder_til__build_register_funcsig_names_lp(LoadedProgram * lp);
void priv___src_self_builder_til__register_lookups_prog(Expr * prog, Context * ctx);
void collect_closure_value_names(Expr * e, Set__Str * names, Context * ctx);
void build_register_closure_values_lp(LoadedProgram * lp);
void priv___src_self_builder_til__build_register_lookups_lp(LoadedProgram * lp);
void priv___src_self_builder_til__emit_monolithic_header_lp(File * f, Mode * mode, LoadedProgram * lp);
void priv___src_self_builder_til__emit_all_forward_declarations(File * f, Mode * mode, LoadedProgram * lp);
void priv___src_self_builder_til__emit_dyn_fn_wrapper(File * f, Str * type_name, Str * method_name, FunctionDef * fd, Context * ctx);
Bool priv___src_self_builder_til__def_is_interface(Expr * def);
Bool priv___src_self_builder_til__func_type_is_core(FuncType * ft);
void emit_dyn_fn_closure_value(File * f, Str * type_name, Str * method_name, Str * suffix);
void priv___src_self_builder_til__emit_dyn_fn_wrappers(File * f, LoadedProgram * lp);
void priv___src_self_builder_til__emit_dyn_size_of_body(File * f, LoadedProgram * lp);
void priv___src_self_builder_til__emit_struct_field_branch_for_stmt(File * f, Expr * stmt, I32 kind, Context * ctx);
void priv___src_self_builder_til__emit_struct_field_branches(File * f, I32 kind, LoadedProgram * lp);
void priv___src_self_builder_til__emit_struct_introspection_bodies(File * f, LoadedProgram * lp);
void priv___src_self_builder_til__emit_enum_variant_branch_for_stmt(File * f, Expr * stmt, I32 kind, Context * ctx);
void priv___src_self_builder_til__emit_enum_variant_branches(File * f, I32 kind, LoadedProgram * lp);
void priv___src_self_builder_til__emit_enum_introspection_bodies(File * f, LoadedProgram * lp);
void priv___src_self_builder_til__emit_funcsig_branch_for_stmt(File * f, Expr * stmt, I32 kind, Context * ctx);
void priv___src_self_builder_til__emit_funcsig_branches(File * f, I32 kind, LoadedProgram * lp);
void priv___src_self_builder_til__emit_funcsig_introspection_bodies(File * f, LoadedProgram * lp);
Str * priv___src_self_builder_til__dyn_type_str_display(Str * vn);
Bool priv___src_self_builder_til__find_loaded_enum_variants(Str * ename, Vec__Str * variant_names, Vec__Str * variant_types, LoadedProgram * lp);
void priv___src_self_builder_til__emit_dyn_type_to_str_body(File * f, LoadedProgram * lp);
void priv___src_self_builder_til__emit_dyn_call_bodies(File * f, LoadedProgram * lp);
void priv___src_self_builder_til__emit_dyn_has_bodies(File * f, LoadedProgram * lp);
void priv___src_self_builder_til__emit_collection_helpers(File * f, LoadedProgram * lp);
void priv___src_self_builder_til__emit_global_declarations(File * f, LoadedProgram * lp);
void priv___src_self_builder_til__emit_ns_const_defs_for_stmt(File * f, Expr * stmt);
void priv___src_self_builder_til__emit_ns_const_global_defs(File * f, LoadedProgram * lp);
void priv___src_self_builder_til__emit_test_main(File * f, LoadedProgram * lp);
void priv___src_self_builder_til__emit_script_main(File * f, LoadedProgram * lp);
void priv___src_self_builder_til__emit_function_bodies(File * f, Mode * mode, LoadedProgram * lp);
void priv___src_self_builder_til__emit_ext_func_declarations(File * f, Expr * program, Context * ctx);
void priv___src_self_builder_til__emit_lib_init(File * f, LoadedProgram * lp);
I32 priv___src_self_builder_til__build(Mode * mode, Bool run_tests, Str * c_output_path, LoadedProgram * lp);
priv___src_self_builder_til__BuildPaths * priv___src_self_builder_til__BuildPaths_clone(priv___src_self_builder_til__BuildPaths * self);
void priv___src_self_builder_til__BuildPaths_delete(priv___src_self_builder_til__BuildPaths * self, Bool call_free);
U64 priv___src_self_builder_til__BuildPaths_hash(priv___src_self_builder_til__BuildPaths * self, HashFn hasher);
U32 priv___src_self_builder_til__BuildPaths_size(void);
priv___src_self_builder_til__BuildPaths * priv___src_self_builder_til__derive_build_paths(LoadedProgram * lp, Str * custom_bin, Str * custom_c, Target * target);
void priv___src_self_builder_til__make_build_dirs(priv___src_self_builder_til__BuildPaths * paths);
I32 priv___src_self_builder_til__translate_ast(LoadedProgram * lp, priv___src_self_builder_til__BuildPaths * paths);
void priv___src_self_builder_til__print_translate_success(priv___src_self_builder_til__BuildPaths * paths);
I32 priv___src_self_builder_til__compile_ast(LoadedProgram * lp, priv___src_self_builder_til__BuildPaths * paths, Target * target, Str * cc_override, Bool asan, Bool prof);
I32 cmd_translate(LoadedProgram * lp, Str * custom_c, Target * target);
I32 cmd_build(LoadedProgram * lp, Str * custom_bin, Str * custom_c, Target * target, Str * cc_override, Bool asan, Bool prof);
Str * priv___src_self_builder_til__default_install_prefix(void);
I32 priv___src_self_builder_til__check_install_rc(I32 rc, Str * what);
Str * priv___src_self_builder_til__builder_compiler_root(LoadedProgram * lp);
Str * priv___src_self_builder_til__support_root(Str * prefix);
I32 priv___src_self_builder_til__install_file(Str * src, Str * dst, Str * what);
I32 priv___src_self_builder_til__install_tree(Str * src, Str * dst, Str * what);
Bool priv___src_self_builder_til__is_compiler_install(LoadedProgram * lp, priv___src_self_builder_til__BuildPaths * paths);
I32 priv___src_self_builder_til__install_compiler_support(LoadedProgram * lp, Str * prefix);
void priv___src_self_builder_til__print_install_success(Str * path);
I32 cmd_install(LoadedProgram * lp, Str * install_prefix_in, Target * target, Str * cc_override, Bool asan, Bool prof);
Str * priv___src_self_builder_til__asan_child_prefix(Bool asan);
I32 cmd_run(LoadedProgram * lp, Str * custom_bin, Str * custom_c, Vec__Str * user_argv, Target * target, Str * cc_override, Bool asan, Bool prof);
I32 cmd_test_build_run(LoadedProgram * lp, Str * custom_bin, Str * custom_c, Target * target, Str * cc_override, Bool asan, Bool prof);
DocEntry * DocEntry_clone(DocEntry * self);
void DocEntry_delete(DocEntry * self, Bool call_free);
U64 DocEntry_hash(DocEntry * self, HashFn hasher);
U32 DocEntry_size(void);
DocCatalog * DocCatalog_clone(DocCatalog * self);
void DocCatalog_delete(DocCatalog * self, Bool call_free);
U64 DocCatalog_hash(DocCatalog * self, HashFn hasher);
U32 DocCatalog_size(void);
Bool priv___src_self_builder_til__doc_decl_hidden(Declaration * dd, DocMeta * meta);
Str * priv___src_self_builder_til__doc_index_link_path(Str * out_path);
Str * priv___src_self_builder_til__doc_unit_path_normalized(Str * unit_path);
Str * priv___src_self_builder_til__doc_unit_key(Str * unit_path);
Str * priv___src_self_builder_til__doc_entry_id(Str * unit_path, Str * name);
Str * priv___src_self_builder_til__doc_default_group(Str * unit_path);
Str * priv___src_self_builder_til__doc_effective_group(Str * unit_path, DocMeta * meta);
void priv___src_self_builder_til__collect_unit_doc_catalog(ProgramUnit * u, Context * ctx, DocCatalog * catalog);
DocEntry * priv___src_self_builder_til__doc_catalog_lookup(DocCatalog * catalog, Str * name, Str * loc);
Str * priv___src_self_builder_til__doc_entry_org_link(DocEntry * e, Str * label);
U32 priv___src_self_builder_til__doc_find_link_end(Str * body, U32 start, Str * loc);
Str * priv___src_self_builder_til__doc_expand_til_links(Str * body, DocCatalog * catalog, Str * loc);
void priv___src_self_builder_til__expand_doc_catalog_links(DocCatalog * catalog);
DocCatalog * priv___src_self_builder_til__build_doc_catalog(LoadedProgram * lp);
void priv___src_self_builder_til__append_doc_properties(Str * out, DocEntry * e, Bool include_group, Bool include_id);
U32 priv___src_self_builder_til__doc_unit_entry_capacity(DocEntry * e);
void priv___src_self_builder_til__append_doc_unit_entry(Str * out, DocEntry * e);
Str * priv___src_self_builder_til__format_unit_doc_org(Str * unit_path, DocCatalog * catalog);
Bool priv___src_self_builder_til__doc_index_has_group(Vec__Str * groups, Str * group);
void priv___src_self_builder_til__append_doc_index_entry(Str * out, DocEntry * e);
U32 priv___src_self_builder_til__doc_index_entry_capacity(DocEntry * e);
void priv___src_self_builder_til__doc_index_add_group_if_present(Vec__Str * groups, DocCatalog * catalog, Str * group);
Vec__Str * priv___src_self_builder_til__doc_index_collect_groups(DocCatalog * catalog);
Str * priv___src_self_builder_til__format_doc_index_org(DocCatalog * catalog);
void priv___src_self_builder_til__emit_doc_index(DocCatalog * catalog);
Str * priv___src_self_builder_til__til_doc_out_path(Str * unit_path);
void priv___src_self_builder_til__ensure_parent_dir(Str * path);
void priv___src_self_builder_til__emit_unit_doc(ProgramUnit * u, DocCatalog * catalog);
I32 cmd_doc(LoadedProgram * lp);
I32 cmd_doc_cache(LoadedProgram * lp);
Array__Bool * Array__Bool_new(U32 cap);
Bool * Array__Bool_unsafe_get(Array__Bool * self, U32 * i);
Bool * Array__Bool_get(Array__Bool * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
void Array__Bool_unsafe_set(Array__Bool * self, U32 i, Bool * val);
void Array__Bool_set(Array__Bool * self, U32 i, Bool * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
void Array__Bool_delete(Array__Bool * self, Bool call_free);
Array__Bool * Array__Bool_clone(Array__Bool * self);
U32 Array__Bool_size(void);
Vec__DynCallInfo * Vec__DynCallInfo_new(void);
U32 Vec__DynCallInfo_len(Vec__DynCallInfo * self);
void Vec__DynCallInfo_clear(Vec__DynCallInfo * self);
void Vec__DynCallInfo_push(Vec__DynCallInfo * self, priv___src_self_builder_til__DynCallInfo * val);
priv___src_self_builder_til__DynCallInfo * Vec__DynCallInfo_unsafe_get(Vec__DynCallInfo * self, U32 * i);
void Vec__DynCallInfo_delete(Vec__DynCallInfo * self, Bool call_free);
Vec__DynCallInfo * Vec__DynCallInfo_clone(Vec__DynCallInfo * self);
U32 Vec__DynCallInfo_size(void);
Vec__CollectionInfo * Vec__CollectionInfo_new(void);
U32 Vec__CollectionInfo_len(Vec__CollectionInfo * self);
void Vec__CollectionInfo_clear(Vec__CollectionInfo * self);
void Vec__CollectionInfo_push(Vec__CollectionInfo * self, priv___src_self_builder_til__CollectionInfo * val);
priv___src_self_builder_til__CollectionInfo * Vec__CollectionInfo_unsafe_get(Vec__CollectionInfo * self, U32 * i);
void Vec__CollectionInfo_delete(Vec__CollectionInfo * self, Bool call_free);
Vec__CollectionInfo * Vec__CollectionInfo_clone(Vec__CollectionInfo * self);
U32 Vec__CollectionInfo_size(void);
Vec__DocEntry * Vec__DocEntry_new(void);
U32 Vec__DocEntry_len(Vec__DocEntry * self);
void Vec__DocEntry_clear(Vec__DocEntry * self);
void Vec__DocEntry_push(Vec__DocEntry * self, DocEntry * val);
DocEntry * Vec__DocEntry_unsafe_get(Vec__DocEntry * self, U32 * i);
DocEntry * Vec__DocEntry_get(Vec__DocEntry * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
void Vec__DocEntry_delete(Vec__DocEntry * self, Bool call_free);
Vec__DocEntry * Vec__DocEntry_clone(Vec__DocEntry * self);
U32 Vec__DocEntry_size(void);
ffi_type * ffi_type_clone(ffi_type * self);
void ffi_type_delete(ffi_type * self, Bool call_free);
U32 ffi_type_size(void);
ffi_cif * ffi_cif_clone(ffi_cif * self);
void ffi_cif_delete(ffi_cif * self, Bool call_free);
U32 ffi_cif_size(void);
ffi_closure * ffi_closure_clone(ffi_closure * _self);
void ffi_closure_delete(ffi_closure * self, Bool call_free);
U64 ffi_closure_hash(ffi_closure * self, HashFn hasher);
U32 ffi_closure_size(void);
ffi_raw_closure * ffi_raw_closure_clone(ffi_raw_closure * _self);
void ffi_raw_closure_delete(ffi_raw_closure * self, Bool call_free);
U64 ffi_raw_closure_hash(ffi_raw_closure * self, HashFn hasher);
U32 ffi_raw_closure_size(void);
ffi_java_raw_closure * ffi_java_raw_closure_clone(ffi_java_raw_closure * _self);
void ffi_java_raw_closure_delete(ffi_java_raw_closure * self, Bool call_free);
U64 ffi_java_raw_closure_hash(ffi_java_raw_closure * self, HashFn hasher);
U32 ffi_java_raw_closure_size(void);
ffi_go_closure * ffi_go_closure_clone(ffi_go_closure * _self);
void ffi_go_closure_delete(ffi_go_closure * self, Bool call_free);
U64 ffi_go_closure_hash(ffi_go_closure * self, HashFn hasher);
U32 ffi_go_closure_size(void);
Str * priv___src_self_interpreter_til__interp_error_path(Context * ctx);
void priv___src_self_interpreter_til__interp_error(Expr * e, Str * msg, Context * ctx);
void priv___src_self_interpreter_til__interp_lang_error(Expr * e, Str * msg, Context * ctx);
Expr * priv___src_self_interpreter_til__field_nested_def(Declaration * dd, Context * ctx);
Bool priv___src_self_interpreter_til__decl_is_funcsig(Declaration * dd, Context * ctx);
Str * priv___src_self_interpreter_til__stable_type_name(Str * name, Context * ctx);
Bool priv___src_self_interpreter_til__struct_def_shallow_safe(StructDef * sdef_data, Context * ctx);
Bool priv___src_self_interpreter_til__str_owns_c_str(Str s);
void * priv___src_self_interpreter_til__heap_clone(Str * struct_name, void * data, Context * ctx);
Str * StructInstance_to_str(StructInstance * self);
StructInstance * StructInstance_clone(StructInstance * self);
void StructInstance_delete(StructInstance * self, Bool call_free);
U32 StructInstance_size(void);
EnumInstance * EnumInstance_clone(EnumInstance * self);
void EnumInstance_delete(EnumInstance * self, Bool call_free);
U32 EnumInstance_size(void);
InterpClosure * InterpClosure_clone(InterpClosure * self);
void InterpClosure_delete(InterpClosure * self, Bool call_free);
U32 InterpClosure_size(void);
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
Value * Value_Sbyte(I8 * val);
Value * Value_Ushort(U16 * val);
Value * Value_Closure(InterpClosure * val);
Bool Value_is(Value * self, Value * other);
void Value_delete(Value * self, Bool call_free);
U32 Value_size(void);
InterpCallableBox * InterpCallableBox_clone(InterpCallableBox * self);
void InterpCallableBox_delete(InterpCallableBox * self, Bool call_free);
U64 InterpCallableBox_hash(InterpCallableBox * self, HashFn hasher);
U32 InterpCallableBox_size(void);
Cell * Cell_clone(Cell * self);
void Cell_delete(Cell * self, Bool call_free);
U64 Cell_hash(Cell * self, HashFn hasher);
U32 Cell_size(void);
Binding * Binding_clone(Binding * self);
void Binding_delete(Binding * self, Bool call_free);
U32 Binding_size(void);
Scope * Scope_clone(Scope * self);
void Scope_delete(Scope * self, Bool call_free);
U32 Scope_size(void);
Expr * lookup_interp_type_def(Str * name, Context * ctx);
Value val_none(void);
Value priv___src_self_interpreter_til__val_u8(I64 v);
Value priv___src_self_interpreter_til__val_i8(I64 v);
Value priv___src_self_interpreter_til__val_i16(I64 v);
Value priv___src_self_interpreter_til__val_u16(I64 v);
Value priv___src_self_interpreter_til__val_i32(I64 v);
Value priv___src_self_interpreter_til__val_u32(I64 v);
Value priv___src_self_interpreter_til__make_enum_value(Str * enum_name, void * data, U32 data_size, Bool borrowed, Bool is_str, Context * ctx);
Bool priv___src_self_interpreter_til__enum_variant_is_str(Str * enum_name, I32 etag, Context * ctx);
void priv___src_self_interpreter_til__enum_clone_str_payload(void * data);
void priv___src_self_interpreter_til__enum_free_str_payload(void * data);
Value priv___src_self_interpreter_til__val_enum_flat(Str * enum_name, I64 etag, void * payload_data, U32 payload_size, U32 total_enum_size, Bool str_payload, Bool move_src, Context * ctx);
Value priv___src_self_interpreter_til__val_enum_simple(Str * enum_name, I64 etag, U32 total_enum_size, Context * ctx);
U32 priv___src_self_interpreter_til__elem_size_for_type(Str * type_name);
Value priv___src_self_interpreter_til__parse_cli_arg(Str * s, Str * type_name, Context * ctx);
void * priv___src_self_interpreter_til__value_ptr_view(Value * v);
Bool priv___src_self_interpreter_til__is_value_ptr(Value * v);
void priv___src_self_interpreter_til__resolve_ptr_to_struct(Value * obj, Scope * scope, Str * obj_sname, Context * ctx);
Value eval_expr(Scope * scope, Expr * e, Context * ctx);
Expr * priv___src_self_interpreter_til__lookup_type_def_helper(Str * type_name, Scope * scope, Context * ctx);
Value * priv___src_self_interpreter_til__reinterpret_ptr_value(Value * val, Str * type_name, Scope * scope, Context * ctx, Bool borrow);
Bool priv___src_self_interpreter_til__guard_own_param_skip(Scope * scope, Expr * e, Expr * func_def);
void * priv___src_self_interpreter_til__resolve_field_assign_base(Scope * scope, Expr * obj_expr);
Expr * priv___src_self_interpreter_til__resolve_field_assign_sdef(Scope * scope, Expr * obj_expr);
I64 priv___src_self_interpreter_til__value_as_i64(Value * v);
I64 priv___src_self_interpreter_til__value_switch_key(Value * v);
Str * priv___src_self_interpreter_til__clike_case_variant_name(Expr * pat);
void priv___src_self_interpreter_til__eval_switch(Scope * scope, Expr * stmt, Context * ctx);
void priv___src_self_interpreter_til__eval_declaration(Scope * scope, Expr * stmt, Declaration * dd, Context * ctx);
void priv___src_self_interpreter_til__eval_fcall(Scope * scope, Expr * stmt, FCallData * fcd, Context * ctx);
void priv___src_self_interpreter_til__eval_if(Scope * scope, Expr * stmt, Context * ctx);
void priv___src_self_interpreter_til__eval_while(Scope * scope, Expr * stmt, Context * ctx);
void priv___src_self_interpreter_til__eval_body(Scope * scope, Expr * body, Context * ctx);
void priv___src_self_interpreter_til__materialize_str_result(Value * v);
void priv___src_self_interpreter_til__free_struct_contents_keep_outer(StructInstance * si);
Value priv___src_self_interpreter_til__eval_user_func_call(Scope * caller_scope, Expr * e, Expr * func_def, Scope * parent_scope, Context * ctx);
Value priv___src_self_interpreter_til__eval_callable_call(Scope * caller_scope, Expr * e, Value * callable, Context * ctx);
Value priv___src_self_interpreter_til__eval_call(Scope * scope, Expr * e, Context * ctx);
void priv___src_self_interpreter_til__free_value(Value v);
priv___src_self_interpreter_til__DynPtrBox * priv___src_self_interpreter_til__DynPtrBox_clone(priv___src_self_interpreter_til__DynPtrBox * self);
void priv___src_self_interpreter_til__DynPtrBox_delete(priv___src_self_interpreter_til__DynPtrBox * self, Bool call_free);
U32 priv___src_self_interpreter_til__DynPtrBox_size(void);
void * priv___src_self_interpreter_til__dynamic_value_payload_copy(Value * v);
void priv___src_self_interpreter_til__free_value_full(Value v);
Str * priv___src_self_interpreter_til__container_elem_type(Str * struct_name);
void priv___src_self_interpreter_til__struct_deep_free(Str * struct_name, void * data, Context * ctx);
void priv___src_self_interpreter_til__free_container_str_data(Str * struct_name, void * data, Context * ctx);
void priv___src_self_interpreter_til__free_container_str_data_cached(void * data);
void priv___src_self_interpreter_til__clone_container_str_buffer(Str * struct_name, void * src_data, void * dst_data, Context * ctx);
void priv___src_self_interpreter_til__free_temp_arg_value(Value v);
void priv___src_self_interpreter_til__reclone_return(Context * ctx);
void priv___src_self_interpreter_til__free_non_own_temp_args(Scope * call_scope, Expr * call_expr, Expr * func_def);
Bool priv___src_self_interpreter_til__needs_widen(Value * val, Str * ptype);
Value priv___src_self_interpreter_til__shallow_copy_value(Value * v);
Value priv___src_self_interpreter_til__borrow_value(Value * v);
Value * priv___src_self_interpreter_til__box_scalar_to_dynamic(Scope * call_scope, Value * v, Bool track_for_free);
Value priv___src_self_interpreter_til__make_struct_value(Str * sname, void * data, Bool borrowed, Context * ctx);
Bool priv___src_self_interpreter_til__value_is_borrowed(Value * v);
Value * priv___src_self_interpreter_til__widen_numeric(Value * v, Str * ptype, Context * ctx);
Cell * scope_get(Scope * s, Str * name);
Scope * scope_new(Scope * parent);
Scope * priv___src_self_interpreter_til__scope_new_boxed(Scope * parent);
Str * priv___src_self_interpreter_til__scope_get_payload_alias(Scope * s, Str * name);
Bool priv___src_self_interpreter_til__interp_is_primitive_type_name(Str * name);
void * priv___src_self_interpreter_til__scope_get_ref_primitive_ptr(Scope * s, Str * name);
void scope_set_owned(Scope * s, Str * name, Value * val);
void priv___src_self_interpreter_til__scope_set_borrowed(Scope * s, Str * name, Cell * cell);
void scope_free(Scope * s);
Scope * priv___src_self_interpreter_til__scope_root_ref(Scope * s);
Scope * priv___src_self_interpreter_til__closure_env_clone(Scope * env);
InterpClosure * priv___src_self_interpreter_til__interp_closure_clone(InterpClosure * cl);
void priv___src_self_interpreter_til__interp_closure_free(InterpClosure * cl);
Value * priv___src_self_interpreter_til__make_interp_closure(Expr * func_def, Scope * scope);
Bool priv___src_self_interpreter_til__callable_box_is(void * ptr);
Bool priv___src_self_interpreter_til__value_is_callable(Value * v);
void * priv___src_self_interpreter_til__callable_box_new(Value * v);
Value * priv___src_self_interpreter_til__callable_box_read(void * ptr);
Value * priv___src_self_interpreter_til__callable_from_pointer_value(void * ptr);
void * priv___src_self_interpreter_til__callable_box_clone_ptr(void * ptr);
void priv___src_self_interpreter_til__callable_box_free(void * ptr);
Bool priv___src_self_interpreter_til__interp_fa_is_ns_with_fname(Expr * obj_expr, Str * sname, Expr * sdef, Str * fname);
Bool priv___src_self_interpreter_til__interp_fa_is_ns_inner(Scope * scope, Expr * e, Str * sname);
Cell * priv___src_self_interpreter_til__field_assign_dyn_move_src(Scope * scope, Expr * val_expr);
Bool priv___src_self_interpreter_til__interp_fa_is_ns(Scope * scope, Expr * e);
void priv___src_self_interpreter_til__value_to_buf(void * dest, Value * val, Str * type_name);
Value priv___src_self_interpreter_til__build_argv_array(Vec__Str * argv, U32 offset, U32 count, Str * elem_type, Context * ctx);
void populate_cached_aggregate_defs(Context * ctx, Expr * program);
void interpreter_init_ns(Context * ctx, Scope * global, Expr * program);
Str * priv___src_self_interpreter_til__ns_qname(Str * sname, Str * fname);
Value * ns_get(Str * sname, Str * fname, Context * ctx);
void priv___src_self_interpreter_til__ns_set(Str * sname, Str * fname, Value val, Context * ctx);
Value make_str_value(void * data, U32 len, Context * ctx);
Value make_str_value_view(void * data, U32 len, Context * ctx);
Value priv___src_self_interpreter_til__make_str_value_own(void * data, U32 len, Context * ctx);
Str str_view(Value v);
Declaration * priv___src_self_interpreter_til__find_field_decl(Expr * struct_def, Str * fname);
Value read_field(void * inst_data, Declaration * dd, U32 field_offset, Context * ctx);
void priv___src_self_interpreter_til__free_owned_struct_slot(void * ptr, Str * struct_name, Context * ctx);
void priv___src_self_interpreter_til__write_field(void * inst_data, Declaration * dd, U32 field_offset, U32 field_size, Value * val, Context * ctx);
void priv___src_self_interpreter_til__interpret_register_defs(Scope * global, Expr * prog);
void priv___src_self_interpreter_til__interpret_register_aliases(Scope * global, Expr * prog);
void priv___src_self_interpreter_til__interpret_copy_alias_ns(Expr * prog, Scope * global, Context * ctx);
I32 priv___src_self_interpreter_til__interpret_units(LoadedProgram * lp, Vec__Str * user_argv, Str * fwd_path);
I32 cmd_interpret(LoadedProgram * lp, Vec__Str * user_argv);
priv___src_self_interpreter_til__ExtStr * priv___src_self_interpreter_til__ExtStr_clone(priv___src_self_interpreter_til__ExtStr * self);
void priv___src_self_interpreter_til__ExtStr_delete(priv___src_self_interpreter_til__ExtStr * self, Bool call_free);
U32 priv___src_self_interpreter_til__ExtStr_size(void);
FFIEntry * FFIEntry_clone(FFIEntry * self);
void FFIEntry_delete(FFIEntry * self, Bool call_free);
U32 FFIEntry_size(void);
ExprPtrBox * ExprPtrBox_clone(ExprPtrBox * self);
void ExprPtrBox_delete(ExprPtrBox * self, Bool call_free);
U32 ExprPtrBox_size(void);
FFITypePtrBox * FFITypePtrBox_clone(FFITypePtrBox * self);
void FFITypePtrBox_delete(FFITypePtrBox * self, Bool call_free);
U32 FFITypePtrBox_size(void);
void ffi_reset(Context * ctx);
ffi_type * priv___src_self_interpreter_til__ffi_type_ref(Str * name);
void * priv___src_self_interpreter_til__ffi_alloc_cif(void);
Bool priv___src_self_interpreter_til__ffi_cif_rtype_is_struct(ffi_cif * cif);
U8 * priv___src_self_interpreter_til__ffi_dlsym(Str * name);
void priv___src_self_interpreter_til__ffi_init_link_libs(Str * link_flags);
I32 priv___src_self_interpreter_til__ffi_init_user_so(Str * fwd_path, Str * user_c_path, Str * ext_c_path, Str * link_flags, Str * so_path_out);
void priv___src_self_interpreter_til__ffi_init_struct_defs(Expr * program, Context * ctx);
void ffi_init_struct_defs_append(Expr * program, Context * ctx);
U64 priv___src_self_interpreter_til__value_to_u64(Value * v);
ffi_type * priv___src_self_interpreter_til__uptr_ffi_type(Context * ctx);
ffi_type * priv___src_self_interpreter_til__usize_ffi_type(Context * ctx);
F32 priv___src_self_interpreter_til__value_to_f32(Value * v);
Str * priv___src_self_interpreter_til__value_variant_name(Value * v);
Bool priv___src_self_interpreter_til__narrow_bool_arg(Scope * s, Expr * e, Context * ctx);
Bool priv___src_self_interpreter_til__h_Bool_and(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_Bool_or(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_Bool_not(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_U8_from_i64(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_I16_from_i64(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_U16_from_i64(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_I32_from_i64(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_F32_from_i64(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_U32_from_i64(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_cast(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_print_single(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_print_flush(Scope * _s, Expr * _e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_exit(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_readfile(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_writefile(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_spawn_cmd(Scope * s, Expr * e, Value * r, Context * ctx);
void * priv___src_self_interpreter_til__val_to_ptr(Value * v);
Bool priv___src_self_interpreter_til__h_dyn_has_method(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_dyn_fn(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_dyn_size_of(Scope * s, Expr * e, Value * r, Context * ctx);
Value priv___src_self_interpreter_til__str_to_owned_value(Str * src, Context * ctx);
Str * priv___src_self_interpreter_til__value_str_clone(Value * v);
Str * priv___src_self_interpreter_til__eval_str_owned(Scope * s, Expr * arg, Context * ctx);
Expr * priv___src_self_interpreter_til__interp_lookup_struct(Scope * s, Expr * e, Str * type_name, Str * who, Context * ctx);
Bool priv___src_self_interpreter_til__h_struct_field_count(Scope * s, Expr * e, Value * r, Context * ctx);
U32 priv___src_self_interpreter_til__eval_index_arg(Scope * s, Expr * e, Context * ctx);
Bool priv___src_self_interpreter_til__h_struct_field_name(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_struct_field_is_mut(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_struct_field_type(Scope * s, Expr * e, Value * r, Context * ctx);
Expr * priv___src_self_interpreter_til__interp_lookup_enum(Scope * s, Expr * e, Str * type_name, Str * who, Context * ctx);
Bool priv___src_self_interpreter_til__h_enum_variant_count(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_enum_variant_name(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_enum_variant_has_payload(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_enum_variant_payload_type(Scope * s, Expr * e, Value * r, Context * ctx);
Expr * priv___src_self_interpreter_til__interp_lookup_funcsig(Scope * s, Expr * e, Str * type_name, Str * who, Context * ctx);
Bool priv___src_self_interpreter_til__h_func_sig_param_count(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_func_sig_param_type(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_func_sig_return_count(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_func_sig_return_type(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_func_sig_throw_count(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_func_sig_throw_type(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_dyn_type_to_str(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_check_cmd_status(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_sleep(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_file_mtime(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_str_parse_f32(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_clock_ms(Scope * _s, Expr * _e, Value * r);
Bool priv___src_self_interpreter_til__h_get_thread_count(Scope * _s, Expr * _e, Value * r);
Bool priv___src_self_interpreter_til__h_cfile_open(Scope * s, Expr * e, Value * r, Context * ctx);
ffi_type * priv___src_self_interpreter_til__known_ffi_type(Str * type_name, Context * ctx);
ffi_type * priv___src_self_interpreter_til__shallow_ffi_type(Str * type_name, Context * ctx);
ffi_type * priv___src_self_interpreter_til__field_ffi_type(Declaration * dd, Context * ctx);
ffi_type * priv___src_self_interpreter_til__build_struct_ffi_type(Expr * struct_def, Context * ctx);
Bool priv___src_self_interpreter_til__h_free(Scope * s, Expr * e, Value * r, Context * ctx);
void priv___src_self_interpreter_til__free_callable_storage(Value * v);
Bool priv___src_self_interpreter_til__h_til_closure_delete(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_til_closure_slot_delete(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_cfile_close(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_cfile_write_str(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_ptr_add(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_cfile_read_all(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_cfile_open_update(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_cfile_tell(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_cfile_seek(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_cfile_seek_cur(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_cfile_seek_end(Scope * s, Expr * e, Value * r, Context * ctx);
Bool priv___src_self_interpreter_til__h_cfile_read_n(Scope * s, Expr * e, Value * r, Context * ctx);
void priv___src_self_interpreter_til__reg_dispatch(Str * name, priv___src_self_interpreter_til__DispatchFn handler, Context * ctx);
void priv___src_self_interpreter_til__dispatch_init(Context * ctx);
Bool priv___src_self_interpreter_til__ext_dispatch_builtin(Str * name, Scope * scope, Expr * e, Value * result, Context * ctx);
Bool priv___src_self_interpreter_til__h_dyn_call(Scope * s, Expr * e, Value * r, Context * ctx);
U32 priv___src_self_interpreter_til__get_elem_size(Scope * s, Str * type_name, Expr * src, Context * ctx);
Bool priv___src_self_interpreter_til__enum_method_dispatch(Str * method, Scope * scope, Expr * enum_def, Str * enum_name, Expr * e, Value * result, Context * ctx);
Bool priv___src_self_interpreter_til__ffi_decode_scalar(Str * rtype, void * p, Value * result, Context * ctx);
Expr * priv___src_self_interpreter_til__ffi_call_ret_struct_def(FFIEntry * fe, Context * ctx);
Bool priv___src_self_interpreter_til__ffi_shallow_type_info(void * atype, Str * type_name, U32 * size);
Bool priv___src_self_interpreter_til__ffi_write_shallow_arg(Scope * scope, Value * v, void * atype, void * dst, Context * ctx);
Bool priv___src_self_interpreter_til__ext_dispatch_ffi(Str * name, Scope * scope, Expr * e, Value * result, Context * ctx);
Str * priv___src_self_interpreter_til__scalar_op_cat(Str * t);
Bool priv___src_self_interpreter_til__scalar_is_binop(Str * op);
U64 priv___src_self_interpreter_til__scalar_apply_u64(Str * op, U64 a, U64 b);
I64 priv___src_self_interpreter_til__scalar_apply_i64(Str * op, I64 a, I64 b);
F32 priv___src_self_interpreter_til__scalar_apply_f32(Str * op, F32 a, F32 b);
Bool priv___src_self_interpreter_til__scalar_is_cmp(Str * op);
Bool priv___src_self_interpreter_til__scalar_cmp_u64(Str * op, U64 a, U64 b);
Bool priv___src_self_interpreter_til__scalar_cmp_i64(Str * op, I64 a, I64 b);
Bool priv___src_self_interpreter_til__scalar_cmp_f32(Str * op, F32 a, F32 b);
Value priv___src_self_interpreter_til__scalar_build(Str * t, I64 v);
Value priv___src_self_interpreter_til__scalar_read_arg(Scope * scope, Expr * arg, Str * type_str, Context * ctx);
Bool priv___src_self_interpreter_til__scalar_core_op_eval(Str * name, Scope * scope, Expr * e, Value * result, Context * ctx);
Bool priv___src_self_interpreter_til__ext_function_dispatch(Str * name, Scope * scope, Expr * e, Value * result, Context * ctx);
void priv___src_self_interpreter_til__ffi_register(Str * name, void * fn, Expr * fdef, Context * ctx);
void ffi_init_scan_program(Expr * program, Context * ctx);
I32 priv___src_self_interpreter_til__ffi_init(Expr * program, Str * fwd_path, Str * user_c_path, Str * ext_c_path, Str * link_flags, Context * ctx);
void ffi_cleanup(Context * ctx);
Map__Str_Binding * Map__Str_Binding_new(void);
Bool Map__Str_Binding_has(Map__Str_Binding * self, Str * key);
Binding * Map__Str_Binding_get(Map__Str_Binding * self, Str * key, I64 * _err_kind, KeyNotFound * _err_KeyNotFound, Str * loc);
void Map__Str_Binding_set(Map__Str_Binding * self, Str * key, Binding * val);
void Map__Str_Binding_delete(Map__Str_Binding * self, Bool call_free);
Map__Str_Binding * Map__Str_Binding_clone(Map__Str_Binding * self);
U64 Map__Str_Binding_hash(Map__Str_Binding * self, HashFn hasher);
U32 Map__Str_Binding_size(void);
Vec__DynPtrBox * Vec__DynPtrBox_new(void);
U32 Vec__DynPtrBox_len(Vec__DynPtrBox * self);
void Vec__DynPtrBox_clear(Vec__DynPtrBox * self);
void Vec__DynPtrBox_push(Vec__DynPtrBox * self, priv___src_self_interpreter_til__DynPtrBox * val);
priv___src_self_interpreter_til__DynPtrBox * Vec__DynPtrBox_unsafe_get(Vec__DynPtrBox * self, U32 * i);
void Vec__DynPtrBox_delete(Vec__DynPtrBox * self, Bool call_free);
Vec__DynPtrBox * Vec__DynPtrBox_clone(Vec__DynPtrBox * self);
U32 Vec__DynPtrBox_size(void);
Vec__Binding * Vec__Binding_new(void);
U32 Vec__Binding_len(Vec__Binding * self);
void Vec__Binding_clear(Vec__Binding * self);
Binding * Vec__Binding_unsafe_get(Vec__Binding * self, U32 * i);
void Vec__Binding_unsafe_set(Vec__Binding * self, U32 i, Binding * val);
void Vec__Binding_delete(Vec__Binding * self, Bool call_free);
Vec__Binding * Vec__Binding_clone(Vec__Binding * self);
U32 Vec__Binding_size(void);
Bool priv___src_self_binder_til__bind_is_ws(I8 c);
U32 priv___src_self_binder_til__skip_ws(Str * s, U32 from);
U32 priv___src_self_binder_til__skip_word(Str * s, U32 from);
U32 priv___src_self_binder_til__trim_right(Str * s, U32 from, U32 to);
Bool priv___src_self_binder_til__range_eq_lit(Str * s, U32 start, U32 end, Str * lit);
I64 priv___src_self_binder_til__parse_c_int_literal(Str * s, U32 from, U32 to, Bool * success);
Bool priv___src_self_binder_til__push_til_base(Str * out, Str * c);
priv___src_self_binder_til__BinderState * priv___src_self_binder_til__BinderState_clone(priv___src_self_binder_til__BinderState * self);
void priv___src_self_binder_til__BinderState_delete(priv___src_self_binder_til__BinderState * self, Bool call_free);
U64 priv___src_self_binder_til__BinderState_hash(priv___src_self_binder_til__BinderState * self, HashFn hasher);
U32 priv___src_self_binder_til__BinderState_size(void);
void priv___src_self_binder_til__register_alias(priv___src_self_binder_til__BinderState * bs, Str * name);
void priv___src_self_binder_til__register_dynamic_alias(priv___src_self_binder_til__BinderState * bs, Str * name);
Bool priv___src_self_binder_til__is_alias_to_primitive(priv___src_self_binder_til__BinderState * bs, Str * name);
Bool priv___src_self_binder_til__is_alias_to_dynamic(priv___src_self_binder_til__BinderState * bs, Str * name);
void priv___src_self_binder_til__push_til_default(priv___src_self_binder_til__BinderState * bs, Str * out, Str * c);
Bool priv___src_self_binder_til__bind_emit_field(priv___src_self_binder_til__BinderState * bs, Str * out, Str * line, Str * comment);
void priv___src_self_binder_til__emit_comment_line(Str * out, Str * line);
Bool priv___src_self_binder_til__emit_struct_body(priv___src_self_binder_til__BinderState * bs, Str * out, Vec__Str * lines, U32 open, U32 close);
U32 priv___src_self_binder_til__emit_typedef_struct(priv___src_self_binder_til__BinderState * bs, Str * out, Vec__Str * lines, U32 start, U32 open, U32 close);
U32 priv___src_self_binder_til__emit_typedef_enum(priv___src_self_binder_til__BinderState * bs, Str * out, Vec__Str * lines, U32 start, U32 open, U32 close);
Bool priv___src_self_binder_til__emit_typedef_alias(priv___src_self_binder_til__BinderState * bs, Str * out, Str * line);
Bool priv___src_self_binder_til__emit_typedef_fnptr(priv___src_self_binder_til__BinderState * bs, Str * out, Str * line);
Bool priv___src_self_binder_til__emit_define(Str * out, Str * line);
Bool priv___src_self_binder_til__emit_function(priv___src_self_binder_til__BinderState * bs, Str * out, Vec__Str * lines, U32 start, U32 end);
void priv___src_self_binder_til__walk_header(priv___src_self_binder_til__BinderState * bs, Str * out, Vec__Str * lines);
Str * priv___src_self_binder_til__header_dir_of(Str * path);
Bool priv___src_self_binder_til__path_in_dir(Str * marker_path, Str * incdir);
Bool priv___src_self_binder_til__looks_like_macro_fragment(Str * line);
Vec__Str * priv___src_self_binder_til__filter_preprocessed(Str * pre, Str * incdir);
Str * priv___src_self_binder_til__collapse_blank_runs(Str * s);
void generate_bindings(Str * in_path, Str * out_path);
Vector2 Vector2_clone(Vector2 self);
void Vector2_delete(Vector2 * self, Bool call_free);
U64 Vector2_hash(Vector2 self, HashFn hasher);
U32 Vector2_size(void);
Vector3 * Vector3_clone(Vector3 * self);
void Vector3_delete(Vector3 * self, Bool call_free);
U64 Vector3_hash(Vector3 * self, HashFn hasher);
U32 Vector3_size(void);
Vector4 * Vector4_clone(Vector4 * self);
void Vector4_delete(Vector4 * self, Bool call_free);
U64 Vector4_hash(Vector4 * self, HashFn hasher);
U32 Vector4_size(void);
Matrix * Matrix_clone(Matrix * _self);
void Matrix_delete(Matrix * self, Bool call_free);
U64 Matrix_hash(Matrix * self, HashFn hasher);
U32 Matrix_size(void);
Color Color_clone(Color self);
void Color_delete(Color * self, Bool call_free);
U64 Color_hash(Color self, HashFn hasher);
U32 Color_size(void);
Rectangle * Rectangle_clone(Rectangle * self);
void Rectangle_delete(Rectangle * self, Bool call_free);
U64 Rectangle_hash(Rectangle * self, HashFn hasher);
U32 Rectangle_size(void);
Image * Image_clone(Image * self);
void Image_delete(Image * self, Bool call_free);
U32 Image_size(void);
Texture * Texture_clone(Texture * self);
void Texture_delete(Texture * self, Bool call_free);
U64 Texture_hash(Texture * self, HashFn hasher);
U32 Texture_size(void);
RenderTexture * RenderTexture_clone(RenderTexture * self);
void RenderTexture_delete(RenderTexture * self, Bool call_free);
U64 RenderTexture_hash(RenderTexture * self, HashFn hasher);
U32 RenderTexture_size(void);
NPatchInfo * NPatchInfo_clone(NPatchInfo * self);
void NPatchInfo_delete(NPatchInfo * self, Bool call_free);
U64 NPatchInfo_hash(NPatchInfo * self, HashFn hasher);
U32 NPatchInfo_size(void);
GlyphInfo * GlyphInfo_clone(GlyphInfo * self);
void GlyphInfo_delete(GlyphInfo * self, Bool call_free);
U64 GlyphInfo_hash(GlyphInfo * self, HashFn hasher);
U32 GlyphInfo_size(void);
Font * Font_clone(Font * self);
void Font_delete(Font * self, Bool call_free);
U32 Font_size(void);
Camera3D * Camera3D_clone(Camera3D * self);
void Camera3D_delete(Camera3D * self, Bool call_free);
U64 Camera3D_hash(Camera3D * self, HashFn hasher);
U32 Camera3D_size(void);
Camera2D * Camera2D_clone(Camera2D * self);
void Camera2D_delete(Camera2D * self, Bool call_free);
U64 Camera2D_hash(Camera2D * self, HashFn hasher);
U32 Camera2D_size(void);
Mesh * Mesh_clone(Mesh * self);
void Mesh_delete(Mesh * self, Bool call_free);
U32 Mesh_size(void);
Shader * Shader_clone(Shader * self);
void Shader_delete(Shader * self, Bool call_free);
U32 Shader_size(void);
MaterialMap * MaterialMap_clone(MaterialMap * self);
void MaterialMap_delete(MaterialMap * self, Bool call_free);
U64 MaterialMap_hash(MaterialMap * self, HashFn hasher);
U32 MaterialMap_size(void);
Material * Material_clone(Material * _self);
void Material_delete(Material * self, Bool call_free);
U64 Material_hash(Material * self, HashFn hasher);
U32 Material_size(void);
Transform * Transform_clone(Transform * self);
void Transform_delete(Transform * self, Bool call_free);
U64 Transform_hash(Transform * self, HashFn hasher);
U32 Transform_size(void);
BoneInfo * BoneInfo_clone(BoneInfo * _self);
void BoneInfo_delete(BoneInfo * self, Bool call_free);
U64 BoneInfo_hash(BoneInfo * self, HashFn hasher);
U32 BoneInfo_size(void);
ModelSkeleton * ModelSkeleton_clone(ModelSkeleton * self);
void ModelSkeleton_delete(ModelSkeleton * self, Bool call_free);
U32 ModelSkeleton_size(void);
Model * Model_clone(Model * self);
void Model_delete(Model * self, Bool call_free);
U32 Model_size(void);
ModelAnimation * ModelAnimation_clone(ModelAnimation * _self);
void ModelAnimation_delete(ModelAnimation * self, Bool call_free);
U64 ModelAnimation_hash(ModelAnimation * self, HashFn hasher);
U32 ModelAnimation_size(void);
Ray * Ray_clone(Ray * self);
void Ray_delete(Ray * self, Bool call_free);
U64 Ray_hash(Ray * self, HashFn hasher);
U32 Ray_size(void);
RayCollision * RayCollision_clone(RayCollision * self);
void RayCollision_delete(RayCollision * self, Bool call_free);
U64 RayCollision_hash(RayCollision * self, HashFn hasher);
U32 RayCollision_size(void);
BoundingBox * BoundingBox_clone(BoundingBox * self);
void BoundingBox_delete(BoundingBox * self, Bool call_free);
U64 BoundingBox_hash(BoundingBox * self, HashFn hasher);
U32 BoundingBox_size(void);
Wave * Wave_clone(Wave * self);
void Wave_delete(Wave * self, Bool call_free);
U32 Wave_size(void);
rAudioBuffer * rAudioBuffer_clone(rAudioBuffer * _self);
void rAudioBuffer_delete(rAudioBuffer * self, Bool call_free);
U64 rAudioBuffer_hash(rAudioBuffer * self, HashFn hasher);
U32 rAudioBuffer_size(void);
rAudioProcessor * rAudioProcessor_clone(rAudioProcessor * _self);
void rAudioProcessor_delete(rAudioProcessor * self, Bool call_free);
U64 rAudioProcessor_hash(rAudioProcessor * self, HashFn hasher);
U32 rAudioProcessor_size(void);
AudioStream * AudioStream_clone(AudioStream * self);
void AudioStream_delete(AudioStream * self, Bool call_free);
U32 AudioStream_size(void);
Sound * Sound_clone(Sound * self);
void Sound_delete(Sound * self, Bool call_free);
U64 Sound_hash(Sound * self, HashFn hasher);
U32 Sound_size(void);
Music * Music_clone(Music * self);
void Music_delete(Music * self, Bool call_free);
U32 Music_size(void);
VrDeviceInfo * VrDeviceInfo_clone(VrDeviceInfo * _self);
void VrDeviceInfo_delete(VrDeviceInfo * self, Bool call_free);
U64 VrDeviceInfo_hash(VrDeviceInfo * self, HashFn hasher);
U32 VrDeviceInfo_size(void);
VrStereoConfig * VrStereoConfig_clone(VrStereoConfig * _self);
void VrStereoConfig_delete(VrStereoConfig * self, Bool call_free);
U64 VrStereoConfig_hash(VrStereoConfig * self, HashFn hasher);
U32 VrStereoConfig_size(void);
FilePathList * FilePathList_clone(FilePathList * self);
void FilePathList_delete(FilePathList * self, Bool call_free);
U32 FilePathList_size(void);
AutomationEvent * AutomationEvent_clone(AutomationEvent * _self);
void AutomationEvent_delete(AutomationEvent * self, Bool call_free);
U64 AutomationEvent_hash(AutomationEvent * self, HashFn hasher);
U32 AutomationEvent_size(void);
AutomationEventList * AutomationEventList_clone(AutomationEventList * self);
void AutomationEventList_delete(AutomationEventList * self, Bool call_free);
U32 AutomationEventList_size(void);
nng_ctx nng_ctx_clone(nng_ctx self);
void nng_ctx_delete(nng_ctx * self, Bool call_free);
U64 nng_ctx_hash(nng_ctx self, HashFn hasher);
U32 nng_ctx_size(void);
nng_dialer nng_dialer_clone(nng_dialer self);
void nng_dialer_delete(nng_dialer * self, Bool call_free);
U64 nng_dialer_hash(nng_dialer self, HashFn hasher);
U32 nng_dialer_size(void);
nng_listener nng_listener_clone(nng_listener self);
void nng_listener_delete(nng_listener * self, Bool call_free);
U64 nng_listener_hash(nng_listener self, HashFn hasher);
U32 nng_listener_size(void);
nng_pipe nng_pipe_clone(nng_pipe self);
void nng_pipe_delete(nng_pipe * self, Bool call_free);
U64 nng_pipe_hash(nng_pipe self, HashFn hasher);
U32 nng_pipe_size(void);
nng_socket nng_socket_clone(nng_socket self);
void nng_socket_delete(nng_socket * self, Bool call_free);
U64 nng_socket_hash(nng_socket self, HashFn hasher);
U32 nng_socket_size(void);
nng_msg * nng_msg_clone(nng_msg * _self);
void nng_msg_delete(nng_msg * self, Bool call_free);
U64 nng_msg_hash(nng_msg * self, HashFn hasher);
U32 nng_msg_size(void);
nng_stat * nng_stat_clone(nng_stat * _self);
void nng_stat_delete(nng_stat * self, Bool call_free);
U64 nng_stat_hash(nng_stat * self, HashFn hasher);
U32 nng_stat_size(void);
nng_aio * nng_aio_clone(nng_aio * _self);
void nng_aio_delete(nng_aio * self, Bool call_free);
U64 nng_aio_hash(nng_aio * self, HashFn hasher);
U32 nng_aio_size(void);
nng_sockaddr_inproc * nng_sockaddr_inproc_clone(nng_sockaddr_inproc * _self);
void nng_sockaddr_inproc_delete(nng_sockaddr_inproc * self, Bool call_free);
U64 nng_sockaddr_inproc_hash(nng_sockaddr_inproc * self, HashFn hasher);
U32 nng_sockaddr_inproc_size(void);
nng_sockaddr_path * nng_sockaddr_path_clone(nng_sockaddr_path * _self);
void nng_sockaddr_path_delete(nng_sockaddr_path * self, Bool call_free);
U64 nng_sockaddr_path_hash(nng_sockaddr_path * self, HashFn hasher);
U32 nng_sockaddr_path_size(void);
nng_sockaddr_ipc * nng_sockaddr_ipc_clone(nng_sockaddr_ipc * _self);
void nng_sockaddr_ipc_delete(nng_sockaddr_ipc * self, Bool call_free);
U64 nng_sockaddr_ipc_hash(nng_sockaddr_ipc * self, HashFn hasher);
U32 nng_sockaddr_ipc_size(void);
nng_sockaddr_in * nng_sockaddr_in_clone(nng_sockaddr_in * _self);
void nng_sockaddr_in_delete(nng_sockaddr_in * self, Bool call_free);
U64 nng_sockaddr_in_hash(nng_sockaddr_in * self, HashFn hasher);
U32 nng_sockaddr_in_size(void);
nng_sockaddr_in6 * nng_sockaddr_in6_clone(nng_sockaddr_in6 * _self);
void nng_sockaddr_in6_delete(nng_sockaddr_in6 * self, Bool call_free);
U64 nng_sockaddr_in6_hash(nng_sockaddr_in6 * self, HashFn hasher);
U32 nng_sockaddr_in6_size(void);
nng_sockaddr_zt * nng_sockaddr_zt_clone(nng_sockaddr_zt * _self);
void nng_sockaddr_zt_delete(nng_sockaddr_zt * self, Bool call_free);
U64 nng_sockaddr_zt_hash(nng_sockaddr_zt * self, HashFn hasher);
U32 nng_sockaddr_zt_size(void);
nng_sockaddr_abstract * nng_sockaddr_abstract_clone(nng_sockaddr_abstract * _self);
void nng_sockaddr_abstract_delete(nng_sockaddr_abstract * self, Bool call_free);
U64 nng_sockaddr_abstract_hash(nng_sockaddr_abstract * self, HashFn hasher);
U32 nng_sockaddr_abstract_size(void);
nng_sockaddr_storage * nng_sockaddr_storage_clone(nng_sockaddr_storage * _self);
void nng_sockaddr_storage_delete(nng_sockaddr_storage * self, Bool call_free);
U64 nng_sockaddr_storage_hash(nng_sockaddr_storage * self, HashFn hasher);
U32 nng_sockaddr_storage_size(void);
nng_iov * nng_iov_clone(nng_iov * self);
void nng_iov_delete(nng_iov * self, Bool call_free);
U32 nng_iov_size(void);
nng_url * nng_url_clone(nng_url * self);
void nng_url_delete(nng_url * self, Bool call_free);
U32 nng_url_size(void);
nng_stream * nng_stream_clone(nng_stream * _self);
void nng_stream_delete(nng_stream * self, Bool call_free);
U64 nng_stream_hash(nng_stream * self, HashFn hasher);
U32 nng_stream_size(void);
nng_stream_dialer * nng_stream_dialer_clone(nng_stream_dialer * _self);
void nng_stream_dialer_delete(nng_stream_dialer * self, Bool call_free);
U64 nng_stream_dialer_hash(nng_stream_dialer * self, HashFn hasher);
U32 nng_stream_dialer_size(void);
nng_stream_listener * nng_stream_listener_clone(nng_stream_listener * _self);
void nng_stream_listener_delete(nng_stream_listener * self, Bool call_free);
U64 nng_stream_listener_hash(nng_stream_listener * self, HashFn hasher);
U32 nng_stream_listener_size(void);
nng_udp * nng_udp_clone(nng_udp * _self);
void nng_udp_delete(nng_udp * self, Bool call_free);
U64 nng_udp_hash(nng_udp * self, HashFn hasher);
U32 nng_udp_size(void);
nng_thread * nng_thread_clone(nng_thread * _self);
void nng_thread_delete(nng_thread * self, Bool call_free);
U64 nng_thread_hash(nng_thread * self, HashFn hasher);
U32 nng_thread_size(void);
nng_mtx * nng_mtx_clone(nng_mtx * _self);
void nng_mtx_delete(nng_mtx * self, Bool call_free);
U64 nng_mtx_hash(nng_mtx * self, HashFn hasher);
U32 nng_mtx_size(void);
nng_cv * nng_cv_clone(nng_cv * _self);
void nng_cv_delete(nng_cv * self, Bool call_free);
U64 nng_cv_hash(nng_cv * self, HashFn hasher);
U32 nng_cv_size(void);
Str * repl_read_line(Str * mode_name);
I32 repl_typecheck(LoadedProgram * lp);
Str * repl_capture_interpret(LoadedProgram * lp, Str * out_path);
Bool repl_parse_allows_wrap(Expr * peek_ast);
Bool repl_ast_has_help_call(Expr * e);
void run_repl_session(Str * mode_name_in, Str * next_mode_out, Vec__Str * extra_modes);
void run_repl(Str * initial_mode, Vec__Str * extra_modes);
void usage(void);
CliArgs * CliArgs_clone(CliArgs * self);
void CliArgs_delete(CliArgs * self, Bool call_free);
U32 CliArgs_size(void);
CliArgs * parse_args(Array__Str * args);
Vec__Str * collect_user_argv(LoadedProgram * lp, Array__Str * args, U32 start_idx);
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
TokenType *TokenType_AmpAmp();
TokenType *TokenType_PipePipe();
TokenType *TokenType_ColonEq();
TokenType *TokenType_Ident();
TokenType *TokenType_StringTok();
TokenType *TokenType_Number();
TokenType *TokenType_Char();
TokenType *TokenType_DocComment();
TokenType *TokenType_KwMut();
TokenType *TokenType_KwConst();
TokenType *TokenType_KwOwn();
TokenType *TokenType_KwRef();
TokenType *TokenType_KwShallow();
TokenType *TokenType_KwStruct();
TokenType *TokenType_KwEnum();
TokenType *TokenType_KwNamespace();
TokenType *TokenType_KwInterface();
TokenType *TokenType_KwImplements();
TokenType *TokenType_KwFunc();
TokenType *TokenType_KwProc();
TokenType *TokenType_KwTest();
TokenType *TokenType_KwMacro();
TokenType *TokenType_KwExtFunc();
TokenType *TokenType_KwExtProc();
TokenType *TokenType_KwExtStruct();
TokenType *TokenType_KwLazyFunc();
TokenType *TokenType_KwLazyProc();
TokenType *TokenType_KwCoreFunc();
TokenType *TokenType_KwCoreProc();
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
Target *Target_LinuxX86();
Target *Target_LinuxArm32();
Target *Target_LinuxRiscv32();
Target *Target_WindowsX64();
Target *Target_MacosX64();
Target *Target_MacosArm64();
Target *Target_Wasm32();
Target *Target_TempleosX86();
priv___src_self_typer_til__CtorArg *priv___src_self_typer_til__CtorArg_Unfilled();
priv___src_self_typer_til__CtorArg *priv___src_self_typer_til__CtorArg_Filled(Expr *);
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
Value *Value_Sbyte(I8 *);
Value *Value_Ushort(U16 *);
Value *Value_Closure(InterpClosure *);

extern U32 CAP_LIT;
extern U32 CAP_VIEW;
extern U32 ELEM_POD;
extern U32 ELEM_BOXED;
extern U32 ELEM_FN;
extern Str __til_docs_blob__;
extern Str __til_info_blob__;
extern Map__Str_TokenType priv___src_self_lexer_til__KEYWORDS;
extern Str I64Name;
extern Str U8Name;
extern Str I8Name;
extern Str I16Name;
extern Str U16Name;
extern Str I32Name;
extern Str U32Name;
extern Str U64Name;
extern Str F32Name;
extern Str BoolName;
extern U32 PTR_SIZE_BYTES;
extern U8 priv___src_self_scavenger_til__MARK_DELETE;
extern U8 priv___src_self_scavenger_til__MARK_REPLACE_RHS;
extern Str REPL_CORE_INFO_CACHE;
extern Str REPL_CORE_DOCS_CACHE;
extern I64 lazy_stmt_temp_counter;
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
extern U64 CALLABLE_BOX_MAGIC;
extern U32 ENUM_PAYLOAD_OFFSET;
extern U32 ENUM_PAYLOAD_OFFSET;
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
extern I64 NNG_MAJOR_VERSION;
extern I64 NNG_MINOR_VERSION;
extern I64 NNG_PATCH_VERSION;
extern I32 NNG_PIPE_EV_ADD_PRE;
extern I32 NNG_PIPE_EV_ADD_POST;
extern I32 NNG_PIPE_EV_REM_POST;
extern I32 NNG_PIPE_EV_NUM;
extern I32 NNG_LOG_NONE;
extern I32 NNG_LOG_ERR;
extern I32 NNG_LOG_WARN;
extern I32 NNG_LOG_NOTICE;
extern I32 NNG_LOG_INFO;
extern I32 NNG_LOG_DEBUG;
extern I32 NNG_LOG_USER;
extern I32 NNG_LOG_DAEMON;
extern I32 NNG_LOG_AUTH;
extern I32 NNG_LOG_LOCAL0;
extern I32 NNG_LOG_LOCAL1;
extern I32 NNG_LOG_LOCAL2;
extern I32 NNG_LOG_LOCAL3;
extern I32 NNG_LOG_LOCAL4;
extern I32 NNG_LOG_LOCAL5;
extern I32 NNG_LOG_LOCAL6;
extern I32 NNG_LOG_LOCAL7;
extern Str BASE_VERSION;
extern Str VERSION;

