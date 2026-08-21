#pragma once
#include "ext.h"

typedef struct TilClosure TilClosure;
struct TilClosure {
    void *call;
    void *env;
    void (*drop)(void *);
    void *(*clone)(void *);
};

typedef struct Mode Mode;
typedef struct Vec__Dynamic Vec__Dynamic;
typedef struct Str Str;
typedef struct Array__Str Array__Str;
typedef struct Vec__Str Vec__Str;
enum {
    Primitive_TAG_I16,
    Primitive_TAG_U16,
    Primitive_TAG_I8,
    Primitive_TAG_U8,
    Primitive_TAG_U32,
    Primitive_TAG_I32,
    Primitive_TAG_U64,
    Primitive_TAG_I64,
    Primitive_TAG_F32,
    Primitive_TAG_Bool,
    Primitive_TAG_F64
};
typedef struct Primitive Primitive;
enum {
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
    Type_TAG_FuncPtrSig,
    Type_TAG_Body
};
typedef struct Type Type;
enum {
    FuncType_TAG_Func,
    FuncType_TAG_Proc,
    FuncType_TAG_Test,
    FuncType_TAG_Macro,
    FuncType_TAG_ExtFunc,
    FuncType_TAG_ExtProc,
    FuncType_TAG_LazyFunc,
    FuncType_TAG_LazyProc,
    FuncType_TAG_CoreFunc,
    FuncType_TAG_CoreProc,
    FuncType_TAG_CoreLazyFunc
};
typedef struct FuncType FuncType;
enum {
    OwnType_TAG_Own,
    OwnType_TAG_Ref,
    OwnType_TAG_Shallow
};
typedef struct OwnType OwnType;
enum {
    GcStorage_TAG_Unset,
    GcStorage_TAG_Stack,
    GcStorage_TAG_HeapBox
};
typedef struct GcStorage GcStorage;
typedef struct Option__Expr Option__Expr;
typedef struct Declaration Declaration;
typedef struct FuncSig FuncSig;
typedef struct FunctionDef FunctionDef;
typedef struct FCallData FCallData;
typedef struct LiteralNumData LiteralNumData;
typedef struct IdentData IdentData;
typedef struct FieldAccessData FieldAccessData;
typedef struct StructDef StructDef;
typedef struct VariantDef VariantDef;
typedef struct EnumDef EnumDef;
typedef struct FieldLayout FieldLayout;
typedef struct StructLayout StructLayout;
typedef struct AssignData AssignData;
typedef struct FieldAssignData FieldAssignData;
typedef struct ForInData ForInData;
enum {
    Literal_TAG_Str,
    Literal_TAG_Num,
    Literal_TAG_Bool,
    Literal_TAG_Null,
    Literal_TAG_MapLit,
    Literal_TAG_SetLit
};
typedef struct Literal Literal;
typedef struct MatchData MatchData;
typedef struct CaseData CaseData;
typedef struct CaptureBlockData CaptureBlockData;
typedef struct PrecomputedSequenceData PrecomputedSequenceData;
enum {
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
    NodeType_TAG_Loc,
    NodeType_TAG_BodyValue,
    NodeType_TAG_ListPattern,
    NodeType_TAG_PrecomputedSequence
};
typedef struct NodeType NodeType;
typedef struct Expr Expr;
typedef struct Option__ref_Declaration Option__ref_Declaration;
typedef struct Option__ref_Str Option__ref_Str;
typedef struct Map__Str_USize Map__Str_USize;
typedef struct Vec__VariantDef Vec__VariantDef;
typedef struct Vec__FieldLayout Vec__FieldLayout;
typedef struct Vec__Declaration Vec__Declaration;
typedef struct Vec__Expr Vec__Expr;
typedef struct Vec__USize Vec__USize;
typedef struct File File;
enum {
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
    TokenType_TAG_KwCoreLazyFunc,
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
    TokenType_TAG_KwPriv,
    TokenType_TAG_Error
};
typedef struct TokenType TokenType;
typedef struct Token Token;
typedef struct Map__Str_TokenType Map__Str_TokenType;
typedef struct Vec__Token Vec__Token;
typedef struct Vec__TokenType Vec__TokenType;
typedef struct SymbolPool SymbolPool;
typedef struct priv___src_self_parser_til__Parser priv___src_self_parser_til__Parser;
typedef struct Vec__U32 Vec__U32;
enum {
    Option__U32_TAG_None,
    Option__U32_TAG_Some
};
typedef struct Option__U32 Option__U32;
typedef struct Set__Str Set__Str;
typedef struct Map__Str_Str Map__Str_Str;
typedef struct Vec__Bool Vec__Bool;
typedef struct EvalHeap EvalHeap;
typedef struct Vec__I64 Vec__I64;
typedef struct Vec__U64 Vec__U64;
typedef struct BorrowRoot BorrowRoot;
typedef struct TypeBinding TypeBinding;
typedef struct ScopeFind ScopeFind;
typedef struct TyperFuncState TyperFuncState;
typedef struct TypeScope TypeScope;
typedef struct GenericFuncSource GenericFuncSource;
typedef struct ImportUnit ImportUnit;
typedef struct BuilderFuncScratch BuilderFuncScratch;
typedef struct FfiState FfiState;
typedef struct InternedTypes InternedTypes;
typedef struct EvalState EvalState;
typedef struct Context Context;
typedef struct Vec__BorrowRoot Vec__BorrowRoot;
typedef struct Map__U32_TypeBinding Map__U32_TypeBinding;
typedef struct Map__U32_Dynamic Map__U32_Dynamic;
typedef struct Option__ref_TypeScope Option__ref_TypeScope;
typedef struct Option__ref_TypeBinding Option__ref_TypeBinding;
typedef struct Map__U32_Str Map__U32_Str;
typedef struct Map__Str_FFIEntry Map__Str_FFIEntry;
typedef struct Map__Str_ExprPtrBox Map__Str_ExprPtrBox;
typedef struct Vec__FFITypePtrBox Vec__FFITypePtrBox;
typedef struct Map__Str_Mode Map__Str_Mode;
typedef struct Map__Str_FuncType Map__Str_FuncType;
typedef struct Option__Scope Option__Scope;
typedef struct Map__Str_ImportUnit Map__Str_ImportUnit;
typedef struct Map__Str_StructLayout Map__Str_StructLayout;
typedef struct Set__U32 Set__U32;
typedef struct Map__Str_I64 Map__Str_I64;
typedef struct Map__Str_call_Vec_Str Map__Str_call_Vec_Str;
typedef struct HashMap__Str_Str HashMap__Str_Str;
typedef struct HashMap__Str_USize HashMap__Str_USize;
typedef struct Map__Str_Bool Map__Str_Bool;
typedef struct Map__Str_Dynamic Map__Str_Dynamic;
typedef struct Map__Str_Expr Map__Str_Expr;
typedef struct Option__ref_Expr Option__ref_Expr;
typedef struct Vec__TypeBinding Vec__TypeBinding;
typedef struct Vec__FFIEntry Vec__FFIEntry;
typedef struct Vec__ExprPtrBox Vec__ExprPtrBox;
typedef struct Vec__Mode Vec__Mode;
typedef struct Vec__FuncType Vec__FuncType;
typedef struct Vec__ImportUnit Vec__ImportUnit;
typedef struct Vec__StructLayout Vec__StructLayout;
typedef struct Vec__call_Vec_Str Vec__call_Vec_Str;
typedef struct Option__ref_Mode Option__ref_Mode;
typedef struct GenericSources GenericSources;
typedef struct Map__Str_GenericFuncSource Map__Str_GenericFuncSource;
typedef struct Vec__GenericFuncSource Vec__GenericFuncSource;
enum {
    Lang_TAG_C,
    Lang_TAG_HolyC,
    Lang_TAG_TIL,
    Lang_TAG_Java
};
typedef struct Lang Lang;
enum {
    Target_TAG_LinuxX64,
    Target_TAG_LinuxArm64,
    Target_TAG_LinuxRiscv64,
    Target_TAG_LinuxX86,
    Target_TAG_LinuxArm32,
    Target_TAG_LinuxRiscv32,
    Target_TAG_WindowsX64,
    Target_TAG_WindowsX86,
    Target_TAG_MacosX64,
    Target_TAG_MacosArm64,
    Target_TAG_Wasm32,
    Target_TAG_TempleosX86,
    Target_TAG_Jvm
};
typedef struct Target Target;
typedef struct priv___src_self_typer_til__CtorArg priv___src_self_typer_til__CtorArg;
typedef struct priv___src_self_typer_til__ReturnEscapeRoots priv___src_self_typer_til__ReturnEscapeRoots;
typedef struct FactIndex FactIndex;
typedef struct RootBits RootBits;
typedef struct DepositAcc DepositAcc;
typedef struct priv___src_self_typer_til__CoverageNode priv___src_self_typer_til__CoverageNode;
typedef struct Vec__priv___src_self_typer_til__CtorArg Vec__priv___src_self_typer_til__CtorArg;
typedef struct Map__Str_RootBits Map__Str_RootBits;
typedef struct Vec__priv___src_self_typer_til__CoverageNode Vec__priv___src_self_typer_til__CoverageNode;
typedef struct Vec__RootBits Vec__RootBits;
typedef struct priv___src_self_desugarer_til__StmtDesugarNeeds priv___src_self_desugarer_til__StmtDesugarNeeds;
typedef struct Vec__I32 Vec__I32;
typedef struct priv___src_self_garbager_til__LocalInfo priv___src_self_garbager_til__LocalInfo;
typedef struct priv___src_self_garbager_til__GcCfgBlock priv___src_self_garbager_til__GcCfgBlock;
typedef struct priv___src_self_garbager_til__BodyFacts priv___src_self_garbager_til__BodyFacts;
typedef struct priv___src_self_garbager_til__GcBorrowEdge priv___src_self_garbager_til__GcBorrowEdge;
typedef struct Array__USize Array__USize;
typedef struct Array__Bool Array__Bool;
typedef struct Array__U8 Array__U8;
typedef struct Vec__priv___src_self_garbager_til__GcBorrowEdge Vec__priv___src_self_garbager_til__GcBorrowEdge;
typedef struct Vec__priv___src_self_garbager_til__LocalInfo Vec__priv___src_self_garbager_til__LocalInfo;
typedef struct Vec__priv___src_self_garbager_til__GcCfgBlock Vec__priv___src_self_garbager_til__GcCfgBlock;
typedef struct Option__ref_FunctionDef Option__ref_FunctionDef;
typedef struct Option__ref_Scope Option__ref_Scope;
typedef struct priv___src_self_scavenger_til__DeclRef priv___src_self_scavenger_til__DeclRef;
typedef struct Map__Str_priv___src_self_scavenger_til__DeclRef Map__Str_priv___src_self_scavenger_til__DeclRef;
typedef struct Vec__priv___src_self_scavenger_til__DeclRef Vec__priv___src_self_scavenger_til__DeclRef;
typedef struct ProgramUnit ProgramUnit;
typedef struct LoadedProgram LoadedProgram;
typedef struct DocMeta DocMeta;
typedef struct priv___src_self_loader_til__ImportCheckEntry priv___src_self_loader_til__ImportCheckEntry;
typedef struct Vec__ProgramUnit Vec__ProgramUnit;
typedef struct Vec__priv___src_self_loader_til__ImportCheckEntry Vec__priv___src_self_loader_til__ImportCheckEntry;
typedef struct priv___src_self_c_codegen_til__CollectionInfo priv___src_self_c_codegen_til__CollectionInfo;
typedef struct priv___src_self_c_codegen_til__DynCallInfo priv___src_self_c_codegen_til__DynCallInfo;
typedef struct Set__USize Set__USize;
typedef struct Vec__priv___src_self_c_codegen_til__CollectionInfo Vec__priv___src_self_c_codegen_til__CollectionInfo;
typedef struct Vec__priv___src_self_c_codegen_til__DynCallInfo Vec__priv___src_self_c_codegen_til__DynCallInfo;
typedef struct priv___src_self_holyc_codegen_til__HolyCEmitState priv___src_self_holyc_codegen_til__HolyCEmitState;
typedef struct priv___src_self_holyc_codegen_til__HolyCLocalState priv___src_self_holyc_codegen_til__HolyCLocalState;
typedef struct priv___src_self_jvm_codegen_til__JvmEmitState priv___src_self_jvm_codegen_til__JvmEmitState;
typedef struct priv___src_self_theme_codegen_til__ThemeColorSpec priv___src_self_theme_codegen_til__ThemeColorSpec;
typedef struct priv___src_self_theme_codegen_til__ThemeSpec priv___src_self_theme_codegen_til__ThemeSpec;
typedef struct Vec__priv___src_self_theme_codegen_til__ThemeColorSpec Vec__priv___src_self_theme_codegen_til__ThemeColorSpec;
typedef struct priv___src_self_builder_til__BuildPaths priv___src_self_builder_til__BuildPaths;
typedef struct DocEntry DocEntry;
typedef struct DocCatalog DocCatalog;
typedef struct Vec__DocEntry Vec__DocEntry;
typedef struct _ffi_type ffi_type;
typedef struct InterpCallableBox InterpCallableBox;
typedef struct HeapBinding HeapBinding;
typedef struct Scope Scope;
typedef struct InterpSession InterpSession;
typedef struct priv___src_self_interpreter_til__RawResultInfo priv___src_self_interpreter_til__RawResultInfo;
typedef struct priv___src_self_interpreter_til__DynPtrBox priv___src_self_interpreter_til__DynPtrBox;
typedef struct priv___src_self_interpreter_til__InterpAlias priv___src_self_interpreter_til__InterpAlias;
typedef struct priv___src_self_interpreter_til__ExtStr priv___src_self_interpreter_til__ExtStr;
typedef struct FFIEntry FFIEntry;
typedef struct ExprPtrBox ExprPtrBox;
typedef struct FFITypePtrBox FFITypePtrBox;
typedef struct Map__Str_HeapBinding Map__Str_HeapBinding;
typedef struct Option__ref_HeapBinding Option__ref_HeapBinding;
typedef struct Option__ref_Dynamic Option__ref_Dynamic;
typedef struct Vec__priv___src_self_interpreter_til__DynPtrBox Vec__priv___src_self_interpreter_til__DynPtrBox;
typedef struct Vec__priv___src_self_interpreter_til__InterpAlias Vec__priv___src_self_interpreter_til__InterpAlias;
typedef struct Option__ref_ffi_type Option__ref_ffi_type;
typedef struct Vec__HeapBinding Vec__HeapBinding;
typedef struct priv___src_self_binder_til__BinderState priv___src_self_binder_til__BinderState;
typedef struct priv___src_self_binder_til__AuditedDecl priv___src_self_binder_til__AuditedDecl;
typedef struct Map__Str_priv___src_self_binder_til__AuditedDecl Map__Str_priv___src_self_binder_til__AuditedDecl;
typedef struct Vec__priv___src_self_binder_til__AuditedDecl Vec__priv___src_self_binder_til__AuditedDecl;
enum {
    EditAction_TAG_Continue,
    EditAction_TAG_Submit,
    EditAction_TAG_Eof,
    EditAction_TAG_Bell,
    EditAction_TAG_ClearScreen
};
typedef struct EditAction EditAction;
typedef struct ReplEditor ReplEditor;
typedef struct AnsiDecoder AnsiDecoder;
typedef struct CliArgs CliArgs;

typedef TilClosure *HashFn;
typedef TilClosure *priv___src_self_interpreter_til__DispatchFn;

typedef struct Vec__Dynamic {
    U8 *data;
    USize count;
    USize cap;
} Vec__Dynamic;


typedef struct Str {
    I8 *c_str;
    USize count;
    USize cap;
} Str;


typedef struct Array__Str {
    U8 *data;
    USize cap;
} Array__Str;


typedef struct Vec__Str {
    U8 *data;
    USize count;
    USize cap;
} Vec__Str;












struct Primitive {
    U8 tag;
};

struct Type {
    U8 tag;
    union {
        Str Struct;
        Str Enum;
        Str Custom;
        Primitive Primitive;
        Str FuncPtrSig;
        void *_til_payload_align;
    } data;
};

struct FuncType {
    U8 tag;
};

struct OwnType {
    U8 tag;
};

struct GcStorage {
    U8 tag;
};

struct Option__Expr {
    Expr *data;
};

typedef struct Declaration {
    Str name;
    Str doc;
    Bool is_mut;
    Bool redundant_mut;
    Bool is_priv;
    Bool used;
    OwnType own_type;
    Type til_type;
    Option__Expr default_value;
    Str orig_name;
    GcStorage gc_storage;
    Str external_symbol;
} Declaration;


typedef struct FCallData {
    Bool constfold_value;
    Bool does_throw;
    Bool is_bang;
    U64 own_args;
    U64 keep_outer_args;
    Bool swap_replace;
    Type til_type;
    U64 ref_args;
    U64 splat_args;
} FCallData;


typedef struct LiteralNumData {
    Str text;
    Type til_type;
} LiteralNumData;


typedef struct IdentData {
    U32 name;
    Type til_type;
} IdentData;


typedef struct FieldAccessData {
    U32 name;
    Type til_type;
} FieldAccessData;


typedef struct StructDef {
    Vec__Declaration *fields;
    Vec__Declaration *ns_decls;
    Map__Str_USize *fields_index;
    Map__Str_USize *ns_index;
    Str c_tag;
    Bool is_interface;
    Bool interface_ns_marker;
    Str implements_name;
} StructDef;


typedef struct VariantDef {
    Str name;
    Str doc;
    Str payload_type;
    Bool payload_const;
    I64 tag_value;
    Bool payload_ref;
    Bool payload_funcsig;
} VariantDef;


typedef struct FieldLayout {
    USize offset;
    USize size;
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
    Bool is_move;
} AssignData;


typedef struct FieldAssignData {
    Str name;
    Bool save_old_delete;
    Bool transfers_own;
    Bool is_move;
} FieldAssignData;


typedef struct ForInData {
    Str name;
    Bool is_mut;
    Type til_type;
    Str name2;
    Bool is_mut2;
} ForInData;


struct Literal {
    U8 tag;
    union {
        Str Str;
        LiteralNumData Num;
        Bool Bool;
        void *_til_payload_align;
    } data;
};

typedef struct MatchData {
    Type til_type;
    Str result_temp;
} MatchData;


typedef struct CaseData {
    USize pattern_count;
} CaseData;


typedef struct PrecomputedSequenceData {
    Type til_type;
    Type element_type;
    USize capacity;
    USize ordinal;
} PrecomputedSequenceData;


struct Option__ref_Declaration {
    Declaration *data;
};

struct Option__ref_Str {
    Str *data;
};

typedef struct Vec__VariantDef {
    U8 *data;
    USize count;
    USize cap;
} Vec__VariantDef;


typedef struct Vec__FieldLayout {
    U8 *data;
    USize count;
    USize cap;
} Vec__FieldLayout;


typedef struct Vec__Declaration {
    U8 *data;
    USize count;
    USize cap;
} Vec__Declaration;


typedef struct Vec__Expr {
    U8 *data;
    USize count;
    USize cap;
} Vec__Expr;


typedef struct Vec__USize {
    U8 *data;
    USize count;
    USize cap;
} Vec__USize;


typedef struct File {
    U8 *handle;
    Bool is_write;
    Bool is_update;
} File;


struct TokenType {
    U8 tag;
};

typedef struct Token {
    TokenType type;
    USize start;
    USize len;
    U32 line;
    U32 col;
} Token;


typedef struct Vec__Token {
    U8 *data;
    USize count;
    USize cap;
} Vec__Token;


typedef struct Vec__TokenType {
    U8 *data;
    USize count;
    USize cap;
} Vec__TokenType;


typedef struct Vec__U32 {
    U8 *data;
    USize count;
    USize cap;
} Vec__U32;


struct Option__U32 {
    U8 tag;
    union {
        U32 Some;
        void *_til_payload_align;
    } data;
};

typedef struct Set__Str {
    U8 *data;
    USize count;
    USize cap;
} Set__Str;


typedef struct Map__Str_Str {
    Vec__Str keys;
    Vec__Str values;
} Map__Str_Str;


typedef struct Vec__Bool {
    U8 *data;
    USize count;
    USize cap;
} Vec__Bool;


typedef struct EvalHeap {
    U8 unused;
} EvalHeap;


typedef struct Vec__I64 {
    U8 *data;
    USize count;
    USize cap;
} Vec__I64;


typedef struct Vec__U64 {
    U8 *data;
    USize count;
    USize cap;
} Vec__U64;


typedef struct BorrowRoot {
    Str name;
    Str path;
    U32 line;
    U32 col;
    Bool carried;
    Bool deposited;
    Str field;
} BorrowRoot;


struct ScopeFind {
    TypeBinding *data;
};

typedef struct TyperFuncState {
    Str current_top_func_name;
    Str typer_return_type_name;
    I32 proc_calls_count;
    I32 proc_def_depth;
    I32 auto_gen_depth;
    Set__Str throw_used_local_names;
    Map__Str_Str lowering_param_types;
} TyperFuncState;


typedef struct GenericFuncSource {
    Str name;
    Str path;
    Bool is_priv;
    Str identity_name;
} GenericFuncSource;


typedef struct Vec__BorrowRoot {
    U8 *data;
    USize count;
    USize cap;
} Vec__BorrowRoot;


typedef struct Map__U32_Dynamic {
    Vec__U32 keys;
    Vec__Dynamic values;
} Map__U32_Dynamic;


struct Option__ref_TypeScope {
    TypeScope *data;
};

struct Option__ref_TypeBinding {
    TypeBinding *data;
};

typedef struct Map__U32_Str {
    Vec__U32 keys;
    Vec__Str values;
} Map__U32_Str;


typedef struct Vec__FFITypePtrBox {
    U8 *data;
    USize count;
    USize cap;
} Vec__FFITypePtrBox;


struct Option__Scope {
    Scope *data;
};

typedef struct Set__U32 {
    U8 *data;
    USize count;
    USize cap;
} Set__U32;


typedef struct Map__Str_I64 {
    Vec__Str keys;
    Vec__I64 values;
} Map__Str_I64;


typedef struct HashMap__Str_Str {
    Vec__Str keys;
    Vec__Str values;
    Vec__I64 buckets;
    Vec__I64 nexts;
    Vec__U64 hashes;
} HashMap__Str_Str;


typedef struct HashMap__Str_USize {
    Vec__Str keys;
    Vec__USize values;
    Vec__I64 buckets;
    Vec__I64 nexts;
    Vec__U64 hashes;
} HashMap__Str_USize;


typedef struct Map__Str_Bool {
    Vec__Str keys;
    Vec__Bool values;
} Map__Str_Bool;


typedef struct Map__Str_Dynamic {
    Vec__Str keys;
    Vec__Dynamic values;
} Map__Str_Dynamic;


typedef struct Map__Str_Expr {
    Vec__Str keys;
    Vec__Expr values;
} Map__Str_Expr;


struct Option__ref_Expr {
    Expr *data;
};

typedef struct Vec__TypeBinding {
    U8 *data;
    USize count;
    USize cap;
} Vec__TypeBinding;


typedef struct Vec__FFIEntry {
    U8 *data;
    USize count;
    USize cap;
} Vec__FFIEntry;


typedef struct Vec__ExprPtrBox {
    U8 *data;
    USize count;
    USize cap;
} Vec__ExprPtrBox;


typedef struct Vec__Mode {
    U8 *data;
    USize count;
    USize cap;
} Vec__Mode;


typedef struct Vec__FuncType {
    U8 *data;
    USize count;
    USize cap;
} Vec__FuncType;


typedef struct Vec__ImportUnit {
    U8 *data;
    USize count;
    USize cap;
} Vec__ImportUnit;


typedef struct Vec__StructLayout {
    U8 *data;
    USize count;
    USize cap;
} Vec__StructLayout;


typedef struct Vec__call_Vec_Str {
    U8 *data;
    USize count;
    USize cap;
} Vec__call_Vec_Str;


struct Option__ref_Mode {
    Mode *data;
};

typedef struct Vec__GenericFuncSource {
    U8 *data;
    USize count;
    USize cap;
} Vec__GenericFuncSource;


struct Lang {
    U8 tag;
};

struct Target {
    U8 tag;
};

struct priv___src_self_typer_til__CtorArg {
    Expr *data;
};

typedef struct priv___src_self_typer_til__ReturnEscapeRoots {
    Vec__BorrowRoot direct;
    Vec__BorrowRoot indirect;
} priv___src_self_typer_til__ReturnEscapeRoots;


typedef struct RootBits {
    U64 alias;
    U64 into;
    U64 carried;
} RootBits;


typedef struct DepositAcc {
    U64 m;
} DepositAcc;


typedef struct Vec__priv___src_self_typer_til__CtorArg {
    U8 *data;
    USize count;
    USize cap;
} Vec__priv___src_self_typer_til__CtorArg;


typedef struct Vec__priv___src_self_typer_til__CoverageNode {
    U8 *data;
    USize count;
    USize cap;
} Vec__priv___src_self_typer_til__CoverageNode;


typedef struct Vec__RootBits {
    U8 *data;
    USize count;
    USize cap;
} Vec__RootBits;


typedef struct priv___src_self_desugarer_til__StmtDesugarNeeds {
    Bool array_vec;
    Bool variadic;
    Bool kwargs;
} priv___src_self_desugarer_til__StmtDesugarNeeds;


typedef struct Vec__I32 {
    U8 *data;
    USize count;
    USize cap;
} Vec__I32;


typedef struct priv___src_self_garbager_til__LocalInfo {
    Str name;
    Type type;
    I32 decl_index;
    I32 last_use;
    I32 own_transfer;
    Bool has_transfer;
    Bool skip_scope_delete;
    Bool is_heap;
    Bool dtor_transfer;
    Bool shallow_copy_transfer;
    Bool raw_alloc;
} priv___src_self_garbager_til__LocalInfo;


typedef struct priv___src_self_garbager_til__GcCfgBlock {
    Option__ref_Expr body;
    I32 start;
    I32 end;
    Bool is_root;
    Vec__I32 succs;
} priv___src_self_garbager_til__GcCfgBlock;


typedef struct priv___src_self_garbager_til__BodyFacts {
    USize words;
    USize n_stmts;
    Vec__U64 uses;
    Vec__U64 decls;
    Vec__U64 nested;
    Vec__U64 transfers;
    Vec__U64 escapes;
    Vec__Str def_names;
    Vec__I64 def_bits;
    Vec__Bool directives;
} priv___src_self_garbager_til__BodyFacts;


typedef struct priv___src_self_garbager_til__GcBorrowEdge {
    Str owner;
    Str borrower;
    I32 fixed_reach;
} priv___src_self_garbager_til__GcBorrowEdge;


typedef struct Array__USize {
    U8 *data;
    USize cap;
} Array__USize;


typedef struct Array__Bool {
    U8 *data;
    USize cap;
} Array__Bool;


typedef struct Array__U8 {
    U8 *data;
    USize cap;
} Array__U8;


typedef struct Vec__priv___src_self_garbager_til__GcBorrowEdge {
    U8 *data;
    USize count;
    USize cap;
} Vec__priv___src_self_garbager_til__GcBorrowEdge;


typedef struct Vec__priv___src_self_garbager_til__LocalInfo {
    U8 *data;
    USize count;
    USize cap;
} Vec__priv___src_self_garbager_til__LocalInfo;


typedef struct Vec__priv___src_self_garbager_til__GcCfgBlock {
    U8 *data;
    USize count;
    USize cap;
} Vec__priv___src_self_garbager_til__GcCfgBlock;


struct Option__ref_FunctionDef {
    FunctionDef *data;
};

struct Option__ref_Scope {
    Scope *data;
};

typedef struct priv___src_self_scavenger_til__DeclRef {
    Str path;
    USize idx;
} priv___src_self_scavenger_til__DeclRef;


typedef struct Vec__priv___src_self_scavenger_til__DeclRef {
    U8 *data;
    USize count;
    USize cap;
} Vec__priv___src_self_scavenger_til__DeclRef;


typedef struct ProgramUnit {
    Str path;
} ProgramUnit;


typedef struct DocMeta {
    Str body;
    Str group;
    Str since;
    Str deprecated;
    Bool hidden;
} DocMeta;


typedef struct priv___src_self_loader_til__ImportCheckEntry {
    Str path;
    U32 line;
    U32 col;
    Str label;
    Str dep;
    Str decl_name;
} priv___src_self_loader_til__ImportCheckEntry;


typedef struct Vec__ProgramUnit {
    U8 *data;
    USize count;
    USize cap;
} Vec__ProgramUnit;


typedef struct Vec__priv___src_self_loader_til__ImportCheckEntry {
    U8 *data;
    USize count;
    USize cap;
} Vec__priv___src_self_loader_til__ImportCheckEntry;


typedef struct priv___src_self_c_codegen_til__CollectionInfo {
    Str *type_name;
    I32 is_vec;
} priv___src_self_c_codegen_til__CollectionInfo;


typedef struct priv___src_self_c_codegen_til__DynCallInfo {
    Str *method;
    I32 nargs;
    Bool has_return;
} priv___src_self_c_codegen_til__DynCallInfo;


typedef struct Set__USize {
    U8 *data;
    USize count;
    USize cap;
} Set__USize;


typedef struct Vec__priv___src_self_c_codegen_til__CollectionInfo {
    U8 *data;
    USize count;
    USize cap;
} Vec__priv___src_self_c_codegen_til__CollectionInfo;


typedef struct Vec__priv___src_self_c_codegen_til__DynCallInfo {
    U8 *data;
    USize count;
    USize cap;
} Vec__priv___src_self_c_codegen_til__DynCallInfo;


typedef struct priv___src_self_holyc_codegen_til__HolyCEmitState {
    Set__Str user_functions;
    Bool needs_i64_div;
    Bool needs_i64_mod;
} priv___src_self_holyc_codegen_til__HolyCEmitState;


typedef struct priv___src_self_holyc_codegen_til__HolyCLocalState {
    Map__Str_Str pointer_types;
    Set__Str str_names;
} priv___src_self_holyc_codegen_til__HolyCLocalState;


typedef struct priv___src_self_jvm_codegen_til__JvmEmitState {
    Str path;
    I32 errors;
    Set__Str cells;
    Map__Str_Str cell_types;
    Set__Str raw_refs;
    Map__Str_Str callable_defs;
    Bool return_cell;
} priv___src_self_jvm_codegen_til__JvmEmitState;


typedef struct priv___src_self_theme_codegen_til__ThemeColorSpec {
    Str name;
    Str value;
    Str note;
} priv___src_self_theme_codegen_til__ThemeColorSpec;


typedef struct Vec__priv___src_self_theme_codegen_til__ThemeColorSpec {
    U8 *data;
    USize count;
    USize cap;
} Vec__priv___src_self_theme_codegen_til__ThemeColorSpec;


typedef struct priv___src_self_builder_til__BuildPaths {
    Str name;
    Str c_path;
    Str bin_path;
    Str fwd_path;
    Str h_path;
    Str til_path;
    Str py_path;
    Str jvm_root;
    Str jvm_source_dir;
    Str jvm_package_dir;
    Str jvm_source_path;
    Str jvm_classes_dir;
    Str jvm_args_path;
    Str jvm_package;
    Str jvm_entry_class;
    Str theme_path;
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


typedef struct Vec__DocEntry {
    U8 *data;
    USize count;
    USize cap;
} Vec__DocEntry;


typedef struct _ffi_type {
    U64 size;
    U16 alignment;
    U16 type;
    U8 *elements;
} ffi_type;


typedef struct {
    I32 abi;
    U32 nargs;
    void * *arg_types;
    ffi_type *rtype;
    U32 bytes;
    U32 flags;
    U32 extra_cif_fields;
} ffi_cif;


typedef struct InterpCallableBox {
    U64 magic;
    Expr *func_def;
    Option__Scope env;
} InterpCallableBox;


typedef struct HeapBinding {
    U8 *ptr;
    U8 *til_type_p;
    OwnType own_type;
    Context *ctx;
    Bool is_local;
    Bool is_borrowed;
    Bool is_erased_dynamic;
    Bool is_static_callable;
    Bool moved_out;
    Bool is_raw_alloc;
    Bool payload_released;
} HeapBinding;


typedef struct priv___src_self_interpreter_til__RawResultInfo {
    U8 *source_type_p;
    Bool is_ref;
    Bool is_word;
    Bool arg_deref;
} priv___src_self_interpreter_til__RawResultInfo;


typedef struct priv___src_self_interpreter_til__DynPtrBox {
    U8 *p;
} priv___src_self_interpreter_til__DynPtrBox;


typedef struct priv___src_self_interpreter_til__InterpAlias {
    Str *name;
    Str *target;
} priv___src_self_interpreter_til__InterpAlias;


typedef struct priv___src_self_interpreter_til__ExtStr {
    U8 *data;
    USize count;
    USize cap;
} priv___src_self_interpreter_til__ExtStr;


typedef struct FFIEntry {
    U8 *fn;
    Option__ref_Str return_type;
    USize nparam;
    U8 *param_shallows;
    U8 *param_dynamics;
    Bool return_is_shallow;
    Bool return_is_ref;
    ffi_cif *cif;
    U8 *arg_types;
} FFIEntry;


typedef struct ExprPtrBox {
    Expr *ptr;
} ExprPtrBox;


typedef struct FFITypePtrBox {
    ffi_type *ptr;
} FFITypePtrBox;


struct Option__ref_HeapBinding {
    HeapBinding *data;
};

struct Option__ref_Dynamic {
    void *data;
};

typedef struct Vec__priv___src_self_interpreter_til__DynPtrBox {
    U8 *data;
    USize count;
    USize cap;
} Vec__priv___src_self_interpreter_til__DynPtrBox;


typedef struct Vec__priv___src_self_interpreter_til__InterpAlias {
    U8 *data;
    USize count;
    USize cap;
} Vec__priv___src_self_interpreter_til__InterpAlias;


struct Option__ref_ffi_type {
    ffi_type *data;
};

typedef struct Vec__HeapBinding {
    U8 *data;
    USize count;
    USize cap;
} Vec__HeapBinding;


typedef struct priv___src_self_binder_til__BinderState {
    Str alias_to_primitive;
    Str alias_to_dynamic;
} priv___src_self_binder_til__BinderState;


typedef struct priv___src_self_binder_til__AuditedDecl {
    Str comments;
    Str line;
    Bool seen;
} priv___src_self_binder_til__AuditedDecl;


typedef struct Vec__priv___src_self_binder_til__AuditedDecl {
    U8 *data;
    USize count;
    USize cap;
} Vec__priv___src_self_binder_til__AuditedDecl;


struct EditAction {
    U8 tag;
};

typedef struct ReplEditor {
    Bool interactive;
    Str hist_path;
    Bool persist;
    Vec__Str *history;
    Str prompt;
    Str line;
    USize cursor;
    USize view_start;
    USize hist_idx;
    Str draft;
    Bool searching;
    Str search_query;
    I64 search_idx;
    Str saved_line;
    USize saved_cursor;
} ReplEditor;


typedef struct AnsiDecoder {
    I64 state;
    Str params;
} AnsiDecoder;


typedef struct CliArgs {
    Str command;
    Str path;
    Str custom_bin;
    Str custom_c;
    Bool custom_c_set;
    Str target_str;
    Str cc;
    Bool cc_set;
    Str install_prefix;
    USize path_idx;
    Bool early_return;
    Bool asan;
    Bool prof;
    I64 usize_bits;
    Bool check_unused_imports;
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


typedef struct FuncSig {
    FuncType func_type;
    Vec__Declaration params;
    Str return_type;
    Vec__Str throw_types;
    I32 variadic_index;
    I32 kwargs_index;
    OwnType return_own_type;
    Bool return_shallow_explicit;
} FuncSig;


typedef struct FunctionDef {
    FuncSig sig;
    Bool auto_generated;
    Bool is_enum_variant_ctor;
    Bool noreturn;
    Vec__Declaration captures;
    Str closure_name;
    U64 ref_return_params;
    U64 ref_return_into_params;
    U64 ref_return_carried_params;
    Option__ref_Declaration namespace_decl;
    U64 deposit_matrix;
} FunctionDef;


typedef struct EnumDef {
    Vec__Declaration *ns_decls;
    Map__Str_USize *ns_index;
    Vec__VariantDef variants;
    Str implements_name;
    Str tag_type;
} EnumDef;


typedef struct StructLayout {
    USize total_size;
    USize align;
    Vec__FieldLayout fields;
    Bool is_interface;
} StructLayout;


typedef struct CaptureBlockData {
    Vec__Declaration captures;
    Str closure_name;
} CaptureBlockData;


struct NodeType {
    U8 tag;
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
        CaseData Case;
        CaptureBlockData CaptureBlock;
        CaptureBlockData BodyValue;
        PrecomputedSequenceData PrecomputedSequence;
        void *_til_payload_align;
    } data;
};

typedef struct Expr {
    NodeType node_type;
    Vec__Expr children;
    U32 line;
    U32 col;
} Expr;


typedef struct Map__Str_USize {
    Vec__Str keys;
    Vec__USize values;
} Map__Str_USize;


typedef struct Map__Str_TokenType {
    Vec__Str keys;
    Vec__TokenType values;
} Map__Str_TokenType;


typedef struct SymbolPool {
    Vec__Str names;
    Vec__U32 buckets;
    U32 next;
} SymbolPool;


typedef struct priv___src_self_parser_til__Parser {
    Vec__Token tokens;
    USize pos;
    Str path;
    Vec__Expr fn_sig_decls;
    Vec__Expr type_gen_decls;
    Set__Str type_gen_seen;
    Vec__Str active_type_params;
    Vec__Expr anon_decls;
    Map__Str_Str anon_cache;
    I64 anon_type_counter;
    Str pending_doc;
    I32 error_count;
    Str error_msg;
    Str source;
    SymbolPool *symbols;
} priv___src_self_parser_til__Parser;


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
    Bool is_raw_alloc;
    Bool is_str_view;
    Str str_view_base;
    Str orig_name;
    Str dynvec_elem;
    Str declared_type_name;
    Vec__BorrowRoot borrow_roots;
    Bool is_external_global;
} TypeBinding;


typedef struct ImportUnit {
    Str mode_str;
    Mode mode;
    Expr *ast;
    Str import_dir;
    Str import_lib_dir;
    Str mode_import;
} ImportUnit;


typedef struct BuilderFuncScratch {
    Map__Str_Dynamic local_fn_sigs;
    Set__U32 body_refs;
    Set__U32 body_multi_decls;
    Set__U32 stack_locals;
    Set__U32 heap_locals;
    Map__U32_Str stack_local_types;
    Set__U32 stack_lit_str_locals;
    Bool force_heap_stack_lit_str_own;
    Set__U32 unsafe_to_hoist;
    Set__U32 ref_locals;
    Set__U32 ref_dyn_locals;
    Set__U32 ptr_locals;
    Set__U32 shadowed_params;
    I32 ctor_seq;
    Bool in_func_def;
    Bool in_main_func;
    Option__ref_Expr current_fdef;
} BuilderFuncScratch;


typedef struct InternedTypes {
    Vec__Dynamic simples;
    Vec__Dynamic prims;
    Map__Str_Dynamic structs;
    Map__Str_Dynamic enums;
    Map__Str_Dynamic customs;
    Map__Str_Dynamic funcsigs;
} InternedTypes;


typedef struct EvalState {
    Bool has_return;
    Bool has_break;
    Bool has_continue;
    void * *return_value;
    Bool interp_ret_is_ref;
    void * *interp_ret_dest;
    Option__ref_Str interp_ret_type;
    OwnType interp_ret_own_type;
    Bool interp_cstr_arg;
    Bool constfold_active;
    Bool eval_aborted;
    Bool repl_session;
    Option__Scope ns_fields;
    Str cached_str_name;
} EvalState;


typedef struct Map__U32_TypeBinding {
    Vec__U32 keys;
    Vec__TypeBinding values;
} Map__U32_TypeBinding;


typedef struct Map__Str_FFIEntry {
    Vec__Str keys;
    Vec__FFIEntry values;
} Map__Str_FFIEntry;


typedef struct Map__Str_ExprPtrBox {
    Vec__Str keys;
    Vec__ExprPtrBox values;
} Map__Str_ExprPtrBox;


typedef struct Map__Str_Mode {
    Vec__Str keys;
    Vec__Mode values;
} Map__Str_Mode;


typedef struct Map__Str_FuncType {
    Vec__Str keys;
    Vec__FuncType values;
} Map__Str_FuncType;


typedef struct Map__Str_ImportUnit {
    Vec__Str keys;
    Vec__ImportUnit values;
} Map__Str_ImportUnit;


typedef struct Map__Str_StructLayout {
    Vec__Str keys;
    Vec__StructLayout values;
} Map__Str_StructLayout;


typedef struct Map__Str_call_Vec_Str {
    Vec__Str keys;
    Vec__call_Vec_Str values;
} Map__Str_call_Vec_Str;


typedef struct Map__Str_GenericFuncSource {
    Vec__Str keys;
    Vec__GenericFuncSource values;
} Map__Str_GenericFuncSource;


typedef struct FactIndex {
    U64 filt;
    Map__Str_USize idx;
} FactIndex;


typedef struct priv___src_self_typer_til__CoverageNode {
    Bool fully_covered;
    Vec__Str sub_names;
    Vec__priv___src_self_typer_til__CoverageNode sub_nodes;
} priv___src_self_typer_til__CoverageNode;


typedef struct Map__Str_RootBits {
    Vec__Str keys;
    Vec__RootBits values;
} Map__Str_RootBits;


typedef struct Map__Str_priv___src_self_scavenger_til__DeclRef {
    Vec__Str keys;
    Vec__priv___src_self_scavenger_til__DeclRef values;
} Map__Str_priv___src_self_scavenger_til__DeclRef;


typedef struct priv___src_self_theme_codegen_til__ThemeSpec {
    Str name;
    Str header;
    Str description;
    Str source_theme;
    Str source_package;
    Str source_url;
    Str source_license;
    Str palette_note;
    Str palette_footer;
    Str constant_face_note;
    Str type_face_note;
    Vec__priv___src_self_theme_codegen_til__ThemeColorSpec colors;
} priv___src_self_theme_codegen_til__ThemeSpec;


typedef struct DocCatalog {
    Vec__DocEntry entries;
} DocCatalog;


typedef struct InterpSession {
    Option__Scope global;
    Bool core_evaluated;
    USize user_argc;
    Vec__priv___src_self_interpreter_til__DynPtrBox retained_programs;
    Bool is_repl;
    Set__Str evaluated_units;
} InterpSession;


typedef struct Map__Str_HeapBinding {
    Vec__Str keys;
    Vec__HeapBinding values;
} Map__Str_HeapBinding;


typedef struct Map__Str_priv___src_self_binder_til__AuditedDecl {
    Vec__Str keys;
    Vec__priv___src_self_binder_til__AuditedDecl values;
} Map__Str_priv___src_self_binder_til__AuditedDecl;


typedef struct TypeScope {
    Map__U32_TypeBinding bindings;
    Str target_usize_pname;
    Str target_uptr_pname;
    Map__U32_Dynamic func_defs;
    Map__U32_Dynamic struct_defs;
    Option__ref_TypeScope parent;
    Bool is_func_root;
    Str current_type_name;
    TyperFuncState typer_func;
    U64 bindings_filt;
    U64 func_defs_filt;
    U64 struct_defs_filt;
} TypeScope;


typedef struct FfiState {
    Map__Str_Dynamic dispatch_map;
    Bool dispatch_inited;
    Map__Str_FFIEntry entries;
    Bool entries_inited;
    Bool loaded;
    Map__Str_ExprPtrBox struct_defs;
    Vec__FFITypePtrBox type_cache;
    Bool type_cache_inited;
} FfiState;


typedef struct Context {
    Mode mode;
    Str path;
    Map__Str_Mode path_modes;
    Map__Str_Mode mode_registry;
    EvalHeap eval_heap;
    Str target_usize_pname;
    Str target_uptr_pname;
    USize target_usize_bytes;
    I64 anon_type_counter;
    Bool compile_mode;
    Map__Str_FuncType constfolder_foldables;
    Option__Scope constfolder_known;
    Set__Str constfolder_assigned;
    USize precomputed_sequence_counter;
    EvalState eval;
    Map__Str_ImportUnit imported;
    Str import_cwd;
    Bool check_unused_imports;
    Set__Str import_use_edges;
    Set__Str imports_init_seed_done;
    Set__Str imports_init_active;
    Set__Str imports_init_done;
    Set__Str imports_typer_methods_done;
    Set__Str imports_typer_fields_done;
    Set__Str imports_typer_decls_done;
    Set__Str imports_typer_bodies_done;
    Bool infer_struct_fields_only;
    Set__Str type_gen_synths;
    Map__Str_Expr generic_funcs;
    Set__Str generic_func_synths;
    Set__Str generic_func_synth_names;
    Map__Str_Expr generic_type_deps;
    Expr *generic_pending;
    Expr *func_gen_twins;
    Str generic_expected_type;
    void * *generic_expected_for;
    TypeScope scope;
    Bool is_repl;
    Map__Str_StructLayout struct_layouts;
    Str closure_emit_env;
    Set__U32 closure_emit_captures;
    Set__U32 funcsig_names;
    Set__U32 closure_value_names;
    Set__U32 script_globals;
    Set__U32 ref_globals;
    Vec__Str throw_type_registry;
    Map__Str_call_Vec_Str throws_global;
    I64 bang_counter;
    I32 hoist_counter;
    I32 va_counter;
    I32 kw_counter;
    I32 coll_counter;
    Str synth_owner;
    Map__Str_I64 synth_symbol_seq;
    I64 lazy_stmt_temp_counter;
    I32 errors;
    Map__Str_call_Vec_Str priv_ref_edges;
    BuilderFuncScratch builder_func;
    HashMap__Str_Str builder_str_lit_symbols;
    Vec__Str builder_str_lit_values;
    HashMap__Str_Str builder_str_lit_ident_symbols;
    HashMap__Str_USize builder_str_lit_counts;
    HashMap__Str_Str builder_str_lit_ident_contents;
    Vec__Str builder_str_lit_members;
    HashMap__Str_USize builder_str_lit_member_seq;
    Set__Str builder_reflect_inventory;
    Set__Str builder_dyn_fn_targets;
    Set__Str builder_ns_member_sites;
    Set__Str builder_collection_elem_types;
    Set__Str builder_used_ctypes;
    Set__Str builder_omitted_core_funcs;
    Set__Str builder_forward_declared;
    Map__Str_Bool builder_free_only_delete;
    Bool builder_static_ok;
    Bool param_value_abi_ok;
    Bool builder_keep_all_exports;
    Str builder_lib_c_prefix;
    Vec__Str builder_lib_c_names;
    Bool builder_lit_guard_used;
    Bool builder_cstr_used;
    Bool builder_closure_rt_used;
    Bool builder_prog_closed_world;
    Map__Str_Dynamic interp_type_defs;
    InternedTypes interned_types;
    FfiState ffi;
    Map__Str_Expr type_gen_binding_sources;
    Map__Str_Str builder_external_globals;
    SymbolPool symbols;
} Context;


typedef struct GenericSources {
    Map__Str_Dynamic defs;
    Map__Str_GenericFuncSource sources;
    Bool late;
} GenericSources;


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
    I32 load_errors;
    I64 usize_override_bits;
} LoadedProgram;


typedef struct Scope {
    Map__Str_HeapBinding heap_bindings;
    Map__Str_Str heap_aliases;
    Option__ref_Scope parent;
    Bool is_call_scope;
} Scope;


Str Str_clone(Str * val);

extern USize CAP_LIT;
extern USize CAP_VIEW;

