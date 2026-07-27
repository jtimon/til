#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <stddef.h>

#include "ext.h"

typedef struct TilClosure TilClosure;
struct TilClosure {
    void *call;
    void *env;
    void (*drop)(void *);
};

typedef struct Str Str;
typedef struct OutOfBounds OutOfBounds;
typedef struct KeyNotFound KeyNotFound;
typedef struct Array__Str Array__Str;
typedef struct Vec__Str Vec__Str;
typedef struct Dynamic Dynamic;
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
    Type_TAG_FuncPtrSig,
    Type_TAG_Body
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
    FuncType_TAG_CoreProc,
    FuncType_TAG_CoreLazyFunc
} FuncType_tag;
typedef struct FuncType FuncType;
typedef enum {
    OwnType_TAG_Own,
    OwnType_TAG_Ref,
    OwnType_TAG_Shallow
} OwnType_tag;
typedef struct OwnType OwnType;
typedef enum {
    GcStorage_TAG_Unset,
    GcStorage_TAG_Stack,
    GcStorage_TAG_HeapBox
} GcStorage_tag;
typedef struct GcStorage GcStorage;
typedef struct Declaration Declaration;
typedef struct FunctionDef FunctionDef;
typedef struct FCallData FCallData;
typedef struct LiteralNumData LiteralNumData;
typedef struct IdentData IdentData;
typedef struct FieldAccessData FieldAccessData;
typedef struct StructDef StructDef;
typedef struct VariantDef VariantDef;
typedef struct EnumDef EnumDef;
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
    NodeType_TAG_Loc,
    NodeType_TAG_BodyValue,
    NodeType_TAG_ListPattern
} NodeType_tag;
typedef struct NodeType NodeType;
typedef struct Expr Expr;
typedef struct Map__Str_USize Map__Str_USize;
typedef struct Vec__VariantDef Vec__VariantDef;
typedef struct Vec__Declaration Vec__Declaration;
typedef struct Vec__Expr Vec__Expr;
typedef struct Vec__USize Vec__USize;
typedef struct Range Range;
typedef struct CfVec2 CfVec2;
typedef struct CfRect CfRect;
typedef struct CfVec3f CfVec3f;
typedef enum {
    Color_TAG_Red,
    Color_TAG_Green,
    Color_TAG_Blue
} Color_tag;
typedef struct Color Color;
typedef enum {
    Token_TAG_Num,
    Token_TAG_Name,
    Token_TAG_Eof
} Token_tag;
typedef struct Token Token;

typedef TilClosure *HashFn;

typedef struct Str {
    I8 *c_str;
    USize count;
    USize cap;
} Str;


typedef struct OutOfBounds {
    char _;
} OutOfBounds;


typedef struct KeyNotFound {
    char _;
} KeyNotFound;


typedef struct Array__Str {
    U8 *data;
    USize cap;
} Array__Str;


typedef struct Vec__Str {
    U8 *data;
    USize count;
    USize cap;
} Vec__Str;


typedef struct Dynamic {
    char _;
} Dynamic;










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
    GcStorage gc_storage;
} Declaration;


typedef struct FCallData {
    Bool is_splat;
    Bool does_throw;
    Bool is_bang;
    U64 own_args;
    U64 keep_outer_args;
    Bool swap_replace;
    Type til_type;
    Bool noreturn_call;
    U64 ref_args;
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
} VariantDef;


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


typedef struct Vec__VariantDef {
    U8 *data;
    USize count;
    USize cap;
} Vec__VariantDef;


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


typedef struct Range {
    U64 start;
    U64 end;
} Range;


typedef struct CfVec2 {
    I64 x;
    I64 y;
} CfVec2;


typedef struct CfRect {
    CfVec2 top_left;
    CfVec2 bottom_right;
} CfRect;


typedef struct CfVec3f {
    F32 x;
    F32 y;
    F32 z;
} CfVec3f;


struct Color {
    U8 tag;
};

struct Token {
    U8 tag;
    union {
        I64 Num;
        Str Name;
        void *_til_payload_align;
    } data;
};

typedef struct FunctionDef {
    FuncType func_type;
    Vec__Declaration params;
    Str return_type;
    Vec__Str throw_types;
    I32 variadic_index;
    I32 kwargs_index;
    OwnType return_own_type;
    Bool return_shallow_explicit;
    Bool auto_generated;
    Bool is_enum_variant_ctor;
    Vec__Declaration captures;
    Str closure_name;
    Bool noreturn;
} FunctionDef;


typedef struct EnumDef {
    Vec__Declaration *ns_decls;
    Map__Str_USize *ns_index;
    Vec__VariantDef variants;
    Str implements_name;
    Str tag_type;
} EnumDef;


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
        CaptureBlockData CaptureBlock;
        CaptureBlockData BodyValue;
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


Str * format(Array__Str * parts);
USize Str_len(Str * self);
I64 Str_cmp(Str * a, Str * b);
Bool Str_eq(Str * a, Str * b);
Str * Str_with_capacity(USize n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
Str * Str_to_str(Str * self);
void Str_delete(Str * self, Bool call_free);
U64 Str_hash(Str * self, HashFn hasher);
USize Str_size(void);
Bool Str_neq(Str * a, Str * b);
OutOfBounds * OutOfBounds_clone(OutOfBounds * _self);
void OutOfBounds_delete(OutOfBounds * self, Bool call_free);
U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher);
USize OutOfBounds_size(void);
KeyNotFound * KeyNotFound_clone(KeyNotFound * _self);
void KeyNotFound_delete(KeyNotFound * self, Bool call_free);
U64 KeyNotFound_hash(KeyNotFound * self, HashFn hasher);
USize KeyNotFound_size(void);
Array__Str * Array__Str_new(USize cap);
USize Array__Str_len(Array__Str * self);
Str * Array__Str_unsafe_get(Array__Str * self, USize * i);
void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val);
void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind);
void Array__Str_delete(Array__Str * self, Bool call_free);
Array__Str * Array__Str_clone(Array__Str * self);
USize Array__Str_size(void);
Vec__Str * Vec__Str_new(void);
void Vec__Str_clear(Vec__Str * self);
void Vec__Str_delete(Vec__Str * self, Bool call_free);
Vec__Str * Vec__Str_clone(Vec__Str * self);
USize Vec__Str_size(void);
USize Dynamic_size(void);
void * Dynamic_clone(void * self);
void Dynamic_delete(void * self, Bool call_free);
void U8_delete(U8 * self, Bool call_free);
USize U8_size(void);
U64 U8_hash(U8 self, HashFn hasher);
void U32_delete(U32 * self, Bool call_free);
USize U32_size(void);
U64 U32_hash(U32 self, HashFn hasher);
Str * U64_to_str(U64 val);
void U64_delete(U64 * self, Bool call_free);
USize U64_size(void);
U64 U64_hash(U64 self, HashFn hasher);
void I8_delete(I8 * self, Bool call_free);
USize I8_size(void);
U64 I8_hash(I8 self, HashFn hasher);
void I32_delete(I32 * self, Bool call_free);
USize I32_size(void);
U64 I32_hash(I32 self, HashFn hasher);
Str * I64_to_str(I64 val);
void I64_delete(I64 * self, Bool call_free);
USize I64_size(void);
U64 I64_hash(I64 self, HashFn hasher);
void F32_delete(F32 * self, Bool call_free);
USize F32_size(void);
U64 F32_hash(F32 self, HashFn hasher);
I64 Bool_cmp(Bool a, Bool b);
void Bool_delete(Bool * self, Bool call_free);
USize Bool_size(void);
U64 Bool_hash(Bool self, HashFn hasher);
Bool Primitive_eq(Primitive * self, Primitive * other);
void Primitive_delete(Primitive * self, Bool call_free);
Primitive * Primitive_clone(Primitive * self);
USize Primitive_size(void);
void Type_delete(Type * self, Bool call_free);
Type * Type_clone(Type * self);
USize Type_size(void);
Bool FuncType_eq(FuncType * self, FuncType * other);
void FuncType_delete(FuncType * self, Bool call_free);
FuncType * FuncType_clone(FuncType * self);
USize FuncType_size(void);
Bool OwnType_eq(OwnType * self, OwnType * other);
void OwnType_delete(OwnType * self, Bool call_free);
OwnType * OwnType_clone(OwnType * self);
USize OwnType_size(void);
Bool GcStorage_eq(GcStorage * self, GcStorage * other);
void GcStorage_delete(GcStorage * self, Bool call_free);
GcStorage * GcStorage_clone(GcStorage * self);
USize GcStorage_size(void);
Declaration * Declaration_clone(Declaration * self);
void Declaration_delete(Declaration * self, Bool call_free);
USize Declaration_size(void);
FunctionDef * FunctionDef_clone(FunctionDef * self);
void FunctionDef_delete(FunctionDef * self, Bool call_free);
U64 FunctionDef_hash(FunctionDef * self, HashFn hasher);
USize FunctionDef_size(void);
FCallData * FCallData_clone(FCallData * self);
void FCallData_delete(FCallData * self, Bool call_free);
U64 FCallData_hash(FCallData * self, HashFn hasher);
USize FCallData_size(void);
LiteralNumData * LiteralNumData_clone(LiteralNumData * self);
void LiteralNumData_delete(LiteralNumData * self, Bool call_free);
U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher);
USize LiteralNumData_size(void);
IdentData * IdentData_clone(IdentData * self);
void IdentData_delete(IdentData * self, Bool call_free);
U64 IdentData_hash(IdentData * self, HashFn hasher);
USize IdentData_size(void);
FieldAccessData * FieldAccessData_clone(FieldAccessData * self);
void FieldAccessData_delete(FieldAccessData * self, Bool call_free);
U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher);
USize FieldAccessData_size(void);
StructDef * StructDef_clone(StructDef * self);
void StructDef_delete(StructDef * self, Bool call_free);
USize StructDef_size(void);
VariantDef * VariantDef_clone(VariantDef * self);
void VariantDef_delete(VariantDef * self, Bool call_free);
U64 VariantDef_hash(VariantDef * self, HashFn hasher);
USize VariantDef_size(void);
EnumDef * EnumDef_clone(EnumDef * self);
void EnumDef_delete(EnumDef * self, Bool call_free);
USize EnumDef_size(void);
AssignData * AssignData_clone(AssignData * self);
void AssignData_delete(AssignData * self, Bool call_free);
U64 AssignData_hash(AssignData * self, HashFn hasher);
USize AssignData_size(void);
FieldAssignData * FieldAssignData_clone(FieldAssignData * self);
void FieldAssignData_delete(FieldAssignData * self, Bool call_free);
U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher);
USize FieldAssignData_size(void);
ForInData * ForInData_clone(ForInData * self);
void ForInData_delete(ForInData * self, Bool call_free);
U64 ForInData_hash(ForInData * self, HashFn hasher);
USize ForInData_size(void);
void Literal_delete(Literal * self, Bool call_free);
Literal * Literal_clone(Literal * self);
USize Literal_size(void);
MatchData * MatchData_clone(MatchData * self);
void MatchData_delete(MatchData * self, Bool call_free);
U64 MatchData_hash(MatchData * self, HashFn hasher);
USize MatchData_size(void);
CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self);
void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free);
U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher);
USize CaptureBlockData_size(void);
void NodeType_delete(NodeType * self, Bool call_free);
NodeType * NodeType_clone(NodeType * self);
USize NodeType_size(void);
void Expr_delete(Expr * self, Bool call_free);
Expr * Expr_new(NodeType * data, U32 line, U32 col);
Expr * Expr_clone(Expr * self);
U64 Expr_hash(Expr * self, HashFn hasher);
USize Expr_size(void);
Map__Str_USize * Map__Str_USize_new(void);
void Map__Str_USize_delete(Map__Str_USize * self, Bool call_free);
Map__Str_USize * Map__Str_USize_clone(Map__Str_USize * self);
U64 Map__Str_USize_hash(Map__Str_USize * self, HashFn hasher);
USize Map__Str_USize_size(void);
Vec__VariantDef * Vec__VariantDef_new(void);
void Vec__VariantDef_clear(Vec__VariantDef * self);
void Vec__VariantDef_delete(Vec__VariantDef * self, Bool call_free);
Vec__VariantDef * Vec__VariantDef_clone(Vec__VariantDef * self);
USize Vec__VariantDef_size(void);
Vec__Declaration * Vec__Declaration_new(void);
void Vec__Declaration_clear(Vec__Declaration * self);
void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free);
Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self);
USize Vec__Declaration_size(void);
Vec__Expr * Vec__Expr_new(void);
void Vec__Expr_clear(Vec__Expr * self);
void Vec__Expr_delete(Vec__Expr * self, Bool call_free);
Vec__Expr * Vec__Expr_clone(Vec__Expr * self);
USize Vec__Expr_size(void);
Vec__USize * Vec__USize_new(void);
void Vec__USize_clear(Vec__USize * self);
void Vec__USize_delete(Vec__USize * self, Bool call_free);
Vec__USize * Vec__USize_clone(Vec__USize * self);
USize Vec__USize_size(void);
__attribute__((noreturn)) void panic(Array__Str * parts, Str * loc);
__attribute__((noreturn)) void UNREACHABLE(Str * loc);
void assert(Bool cond, Str * loc);
void println(Array__Str * parts);
Range * Range_clone(Range * val);
void Range_delete(Range * self, Bool call_free);
U64 Range_hash(Range * self, HashFn hasher);
USize Range_size(void);
void test_simple_add(void);
void test_nested_arithmetic(void);
void test_deeply_nested(void);
void test_string_concat(void);
void test_variadic_fold(void);
void test_variadic_direct_fold(void);
void test_lolalalo(void);
void test_fold_variable(void);
void test_loc_folded(void);
void test_fold_f32(void);
CfVec2 * CfVec2_clone(CfVec2 * self);
void CfVec2_delete(CfVec2 * self, Bool call_free);
U64 CfVec2_hash(CfVec2 * self, HashFn hasher);
USize CfVec2_size(void);
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
CfRect * CfRect_clone(CfRect * self);
void CfRect_delete(CfRect * self, Bool call_free);
U64 CfRect_hash(CfRect * self, HashFn hasher);
USize CfRect_size(void);
void test_struct_fold_nested(void);
CfVec3f * CfVec3f_clone(CfVec3f * self);
void CfVec3f_delete(CfVec3f * self, Bool call_free);
U64 CfVec3f_hash(CfVec3f * self, HashFn hasher);
USize CfVec3f_size(void);
void test_struct_fold_f32(void);
Bool Color_eq(Color * self, Color * other);
void Color_delete(Color * self, Bool call_free);
Color * Color_clone(Color * self);
USize Color_size(void);
void test_enum_fold(void);
void Token_delete(Token * self, Bool call_free);
Token * Token_clone(Token * self);
USize Token_size(void);
void test_enum_payload_fold(void);
void test_enum_return_fold(void);
void test_enum_payload_return_fold(void);
void assert_eq__I64(I64 a, I64 b, Str * loc);
void assert_eq__Str(Str * a, Str * b, Str * loc);
Bool Color_eq(Color *, Color *);
Color *Color_Red();
Color *Color_Green();
Color *Color_Blue();
Token *Token_Num(I64 *);
Token *Token_Name(Str *);
Token *Token_Eof();
#include "ext.h"


void print_single(Str *s);
void print_flush();

Str * format(Array__Str * parts);
USize Str_len(Str * self);
I64 Str_cmp(Str * a, Str * b);
Bool Str_eq(Str * a, Str * b);
Str * Str_with_capacity(USize n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
Str * Str_to_str(Str * self);
void Str_delete(Str * self, Bool call_free);
U64 Str_hash(Str * self, HashFn hasher);
USize Str_size(void);
Bool Str_neq(Str * a, Str * b);
OutOfBounds * OutOfBounds_clone(OutOfBounds * _self);
void OutOfBounds_delete(OutOfBounds * self, Bool call_free);
U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher);
USize OutOfBounds_size(void);
KeyNotFound * KeyNotFound_clone(KeyNotFound * _self);
void KeyNotFound_delete(KeyNotFound * self, Bool call_free);
U64 KeyNotFound_hash(KeyNotFound * self, HashFn hasher);
USize KeyNotFound_size(void);
Array__Str * Array__Str_new(USize cap);
USize Array__Str_len(Array__Str * self);
Str * Array__Str_unsafe_get(Array__Str * self, USize * i);
void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val);
void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind);
void Array__Str_delete(Array__Str * self, Bool call_free);
Array__Str * Array__Str_clone(Array__Str * self);
USize Array__Str_size(void);
Vec__Str * Vec__Str_new(void);
void Vec__Str_clear(Vec__Str * self);
void Vec__Str_delete(Vec__Str * self, Bool call_free);
Vec__Str * Vec__Str_clone(Vec__Str * self);
USize Vec__Str_size(void);
USize Dynamic_size(void);
void * Dynamic_clone(void * self);
void Dynamic_delete(void * self, Bool call_free);
void U8_delete(U8 * self, Bool call_free);
USize U8_size(void);
U64 U8_hash(U8 self, HashFn hasher);
void U32_delete(U32 * self, Bool call_free);
USize U32_size(void);
U64 U32_hash(U32 self, HashFn hasher);
Str * U64_to_str(U64 val);
void U64_delete(U64 * self, Bool call_free);
USize U64_size(void);
U64 U64_hash(U64 self, HashFn hasher);
void I8_delete(I8 * self, Bool call_free);
USize I8_size(void);
U64 I8_hash(I8 self, HashFn hasher);
void I32_delete(I32 * self, Bool call_free);
USize I32_size(void);
U64 I32_hash(I32 self, HashFn hasher);
Str * I64_to_str(I64 val);
void I64_delete(I64 * self, Bool call_free);
USize I64_size(void);
U64 I64_hash(I64 self, HashFn hasher);
void F32_delete(F32 * self, Bool call_free);
USize F32_size(void);
U64 F32_hash(F32 self, HashFn hasher);
I64 Bool_cmp(Bool a, Bool b);
void Bool_delete(Bool * self, Bool call_free);
USize Bool_size(void);
U64 Bool_hash(Bool self, HashFn hasher);
Bool Primitive_eq(Primitive * self, Primitive * other);
void Primitive_delete(Primitive * self, Bool call_free);
Primitive * Primitive_clone(Primitive * self);
USize Primitive_size(void);
void Type_delete(Type * self, Bool call_free);
Type * Type_clone(Type * self);
USize Type_size(void);
Bool FuncType_eq(FuncType * self, FuncType * other);
void FuncType_delete(FuncType * self, Bool call_free);
FuncType * FuncType_clone(FuncType * self);
USize FuncType_size(void);
Bool OwnType_eq(OwnType * self, OwnType * other);
void OwnType_delete(OwnType * self, Bool call_free);
OwnType * OwnType_clone(OwnType * self);
USize OwnType_size(void);
Bool GcStorage_eq(GcStorage * self, GcStorage * other);
void GcStorage_delete(GcStorage * self, Bool call_free);
GcStorage * GcStorage_clone(GcStorage * self);
USize GcStorage_size(void);
Declaration * Declaration_clone(Declaration * self);
void Declaration_delete(Declaration * self, Bool call_free);
USize Declaration_size(void);
FunctionDef * FunctionDef_clone(FunctionDef * self);
void FunctionDef_delete(FunctionDef * self, Bool call_free);
U64 FunctionDef_hash(FunctionDef * self, HashFn hasher);
USize FunctionDef_size(void);
FCallData * FCallData_clone(FCallData * self);
void FCallData_delete(FCallData * self, Bool call_free);
U64 FCallData_hash(FCallData * self, HashFn hasher);
USize FCallData_size(void);
LiteralNumData * LiteralNumData_clone(LiteralNumData * self);
void LiteralNumData_delete(LiteralNumData * self, Bool call_free);
U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher);
USize LiteralNumData_size(void);
IdentData * IdentData_clone(IdentData * self);
void IdentData_delete(IdentData * self, Bool call_free);
U64 IdentData_hash(IdentData * self, HashFn hasher);
USize IdentData_size(void);
FieldAccessData * FieldAccessData_clone(FieldAccessData * self);
void FieldAccessData_delete(FieldAccessData * self, Bool call_free);
U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher);
USize FieldAccessData_size(void);
StructDef * StructDef_clone(StructDef * self);
void StructDef_delete(StructDef * self, Bool call_free);
USize StructDef_size(void);
VariantDef * VariantDef_clone(VariantDef * self);
void VariantDef_delete(VariantDef * self, Bool call_free);
U64 VariantDef_hash(VariantDef * self, HashFn hasher);
USize VariantDef_size(void);
EnumDef * EnumDef_clone(EnumDef * self);
void EnumDef_delete(EnumDef * self, Bool call_free);
USize EnumDef_size(void);
AssignData * AssignData_clone(AssignData * self);
void AssignData_delete(AssignData * self, Bool call_free);
U64 AssignData_hash(AssignData * self, HashFn hasher);
USize AssignData_size(void);
FieldAssignData * FieldAssignData_clone(FieldAssignData * self);
void FieldAssignData_delete(FieldAssignData * self, Bool call_free);
U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher);
USize FieldAssignData_size(void);
ForInData * ForInData_clone(ForInData * self);
void ForInData_delete(ForInData * self, Bool call_free);
U64 ForInData_hash(ForInData * self, HashFn hasher);
USize ForInData_size(void);
void Literal_delete(Literal * self, Bool call_free);
Literal * Literal_clone(Literal * self);
USize Literal_size(void);
MatchData * MatchData_clone(MatchData * self);
void MatchData_delete(MatchData * self, Bool call_free);
U64 MatchData_hash(MatchData * self, HashFn hasher);
USize MatchData_size(void);
CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self);
void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free);
U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher);
USize CaptureBlockData_size(void);
void NodeType_delete(NodeType * self, Bool call_free);
NodeType * NodeType_clone(NodeType * self);
USize NodeType_size(void);
void Expr_delete(Expr * self, Bool call_free);
Expr * Expr_new(NodeType * data, U32 line, U32 col);
Expr * Expr_clone(Expr * self);
U64 Expr_hash(Expr * self, HashFn hasher);
USize Expr_size(void);
Map__Str_USize * Map__Str_USize_new(void);
void Map__Str_USize_delete(Map__Str_USize * self, Bool call_free);
Map__Str_USize * Map__Str_USize_clone(Map__Str_USize * self);
U64 Map__Str_USize_hash(Map__Str_USize * self, HashFn hasher);
USize Map__Str_USize_size(void);
Vec__VariantDef * Vec__VariantDef_new(void);
void Vec__VariantDef_clear(Vec__VariantDef * self);
void Vec__VariantDef_delete(Vec__VariantDef * self, Bool call_free);
Vec__VariantDef * Vec__VariantDef_clone(Vec__VariantDef * self);
USize Vec__VariantDef_size(void);
Vec__Declaration * Vec__Declaration_new(void);
void Vec__Declaration_clear(Vec__Declaration * self);
void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free);
Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self);
USize Vec__Declaration_size(void);
Vec__Expr * Vec__Expr_new(void);
void Vec__Expr_clear(Vec__Expr * self);
void Vec__Expr_delete(Vec__Expr * self, Bool call_free);
Vec__Expr * Vec__Expr_clone(Vec__Expr * self);
USize Vec__Expr_size(void);
Vec__USize * Vec__USize_new(void);
void Vec__USize_clear(Vec__USize * self);
void Vec__USize_delete(Vec__USize * self, Bool call_free);
Vec__USize * Vec__USize_clone(Vec__USize * self);
USize Vec__USize_size(void);
__attribute__((noreturn)) void panic(Array__Str * parts, Str * loc);
__attribute__((noreturn)) void UNREACHABLE(Str * loc);
void assert(Bool cond, Str * loc);
void println(Array__Str * parts);
Range * Range_clone(Range * val);
void Range_delete(Range * self, Bool call_free);
U64 Range_hash(Range * self, HashFn hasher);
USize Range_size(void);
void test_simple_add(void);
void test_nested_arithmetic(void);
void test_deeply_nested(void);
void test_string_concat(void);
void test_variadic_fold(void);
void test_variadic_direct_fold(void);
void test_lolalalo(void);
void test_fold_variable(void);
void test_loc_folded(void);
void test_fold_f32(void);
CfVec2 * CfVec2_clone(CfVec2 * self);
void CfVec2_delete(CfVec2 * self, Bool call_free);
U64 CfVec2_hash(CfVec2 * self, HashFn hasher);
USize CfVec2_size(void);
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
CfRect * CfRect_clone(CfRect * self);
void CfRect_delete(CfRect * self, Bool call_free);
U64 CfRect_hash(CfRect * self, HashFn hasher);
USize CfRect_size(void);
void test_struct_fold_nested(void);
CfVec3f * CfVec3f_clone(CfVec3f * self);
void CfVec3f_delete(CfVec3f * self, Bool call_free);
U64 CfVec3f_hash(CfVec3f * self, HashFn hasher);
USize CfVec3f_size(void);
void test_struct_fold_f32(void);
Bool Color_eq(Color * self, Color * other);
void Color_delete(Color * self, Bool call_free);
Color * Color_clone(Color * self);
USize Color_size(void);
void test_enum_fold(void);
Token * Token_Num(I64 * val);
Token * Token_Name(Str * val);
Token * Token_Eof(void);
Bool Token_is(Token * self, Token * other);
void Token_delete(Token * self, Bool call_free);
Token * Token_clone(Token * self);
USize Token_size(void);
void test_enum_payload_fold(void);
void test_enum_return_fold(void);
void test_enum_payload_return_fold(void);
void assert_eq__I64(I64 a, I64 b, Str * loc);
void assert_eq__Str(Str * a, Str * b, Str * loc);
Bool Primitive_eq(Primitive *, Primitive *);
Primitive *Primitive_I16();
Primitive *Primitive_U16();
Primitive *Primitive_I8();
Primitive *Primitive_U8();
Primitive *Primitive_U32();
Primitive *Primitive_I32();
Primitive *Primitive_U64();
Primitive *Primitive_I64();
Primitive *Primitive_F32();
Primitive *Primitive_Bool();
Type *Type_Unknown();
Type *Type_None();
Type *Type_Struct(Str *);
Type *Type_StructDef();
Type *Type_Enum(Str *);
Type *Type_EnumDef();
Type *Type_FuncDef();
Type *Type_FuncPtr();
Type *Type_Dynamic();
Type *Type_Custom(Str *);
Type *Type_Primitive(Primitive *);
Type *Type_FuncPtrSig(Str *);
Type *Type_Body();
Bool FuncType_eq(FuncType *, FuncType *);
FuncType *FuncType_Func();
FuncType *FuncType_Proc();
FuncType *FuncType_Test();
FuncType *FuncType_Macro();
FuncType *FuncType_ExtFunc();
FuncType *FuncType_ExtProc();
FuncType *FuncType_LazyFunc();
FuncType *FuncType_LazyProc();
FuncType *FuncType_CoreFunc();
FuncType *FuncType_CoreProc();
FuncType *FuncType_CoreLazyFunc();
Bool OwnType_eq(OwnType *, OwnType *);
OwnType *OwnType_Own();
OwnType *OwnType_Ref();
OwnType *OwnType_Shallow();
Bool GcStorage_eq(GcStorage *, GcStorage *);
GcStorage *GcStorage_Unset();
GcStorage *GcStorage_Stack();
GcStorage *GcStorage_HeapBox();
Literal *Literal_Str(Str *);
Literal *Literal_Num(LiteralNumData *);
Literal *Literal_Bool(Bool *);
Literal *Literal_Null();
Literal *Literal_MapLit();
Literal *Literal_SetLit();
NodeType *NodeType_Body();
NodeType *NodeType_Literal(Literal *);
NodeType *NodeType_Ident(IdentData *);
NodeType *NodeType_Decl(Declaration *);
NodeType *NodeType_Assign(AssignData *);
NodeType *NodeType_FCall(FCallData *);
NodeType *NodeType_FuncDef(FunctionDef *);
NodeType *NodeType_StructDef(StructDef *);
NodeType *NodeType_EnumDef(EnumDef *);
NodeType *NodeType_FieldAccess(FieldAccessData *);
NodeType *NodeType_FieldAssign(FieldAssignData *);
NodeType *NodeType_Return();
NodeType *NodeType_If();
NodeType *NodeType_While();
NodeType *NodeType_ForIn(ForInData *);
NodeType *NodeType_NamedArg(Str *);
NodeType *NodeType_Break();
NodeType *NodeType_Continue();
NodeType *NodeType_Switch();
NodeType *NodeType_Match(MatchData *);
NodeType *NodeType_Case();
NodeType *NodeType_NoDefaultArg();
NodeType *NodeType_Throw();
NodeType *NodeType_Catch();
NodeType *NodeType_RestPattern();
NodeType *NodeType_CaptureBlock(CaptureBlockData *);
NodeType *NodeType_Loc();
NodeType *NodeType_BodyValue(CaptureBlockData *);
NodeType *NodeType_ListPattern();
Bool Color_eq(Color *, Color *);
Color *Color_Red();
Color *Color_Green();
Color *Color_Blue();
Token *Token_Num(I64 *);
Token *Token_Name(Str *);
Token *Token_Eof();

void *dyn_fn(Str *type_name, Str *method);
U32 dyn_size_of(Str *type_name);
I64 struct_field_count(Str *type_name);
Str *struct_field_name(Str *type_name, I64 *index);
I64 struct_field_is_mut(Str *type_name, I64 *index);
Str *struct_field_type(Str *type_name, I64 *index);
I64 enum_variant_count(Str *type_name);
Str *enum_variant_name(Str *type_name, I64 *index);
I64 enum_variant_has_payload(Str *type_name, I64 *index);
Str *enum_variant_payload_type(Str *type_name, I64 *index);
I64 enum_variant_tag_value(Str *type_name, I64 *index);
I64 enum_variant_payload_is_const(Str *type_name, I64 *index);
I64 enum_variant_payload_is_ref(Str *type_name, I64 *index);
I64 func_sig_param_count(Str *type_name);
Str *func_sig_param_type(Str *type_name, I64 *index);
I64 func_sig_return_count(Str *type_name);
Str *func_sig_return_type(Str *type_name, I64 *index);
I64 func_sig_throw_count(Str *type_name);
Str *func_sig_throw_type(Str *type_name, I64 *index);

#define DEREF(p) (*(p ? p : (fprintf(stderr, "panic: null deref\n"), exit(1), p)))
#define TIL_CAP_LIT ((USize)-1)
#define TIL_CAP_VIEW ((USize)-2)
void print_single(Str *s) {
    fwrite(s->c_str, 1, (size_t)s->count, stdout);
}
void print_flush() {
    putchar('\n');
}

static Str _til_str_lits[229] = {
    (Str){.c_str = (void *)"c_str", .count = 5ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"I8", .count = 2ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"USize", .count = 5ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"I16", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"U16", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Unknown", .count = 7ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"None", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Struct", .count = 6ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Enum", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"FuncDef", .count = 7ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"FuncPtr", .count = 7ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Custom", .count = 6ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Primitive", .count = 9ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"FuncPtrSig", .count = 10ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Body", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Func", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Proc", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Test", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Macro", .count = 5ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"ExtFunc", .count = 7ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"ExtProc", .count = 7ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"LazyFunc", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"LazyProc", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"CoreFunc", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"CoreProc", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"CoreLazyFunc", .count = 12ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Own", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Ref", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Shallow", .count = 7ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Unset", .count = 5ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Stack", .count = 5ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"HeapBox", .count = 7ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"doc", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"explicit_type", .count = 13ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"is_mut", .count = 6ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"redundant_mut", .count = 13ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"is_priv", .count = 7ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"used", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"own_type", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"OwnType", .count = 7ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"default_value", .count = 13ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Expr", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"orig_name", .count = 9ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"gc_storage", .count = 10ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"GcStorage", .count = 9ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"func_type", .count = 9ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"FuncType", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"params", .count = 6ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"return_type", .count = 11ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"throw_types", .count = 11ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Vec__Str", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"variadic_index", .count = 14ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"kwargs_index", .count = 12ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"return_own_type", .count = 15ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"return_shallow_explicit", .count = 23ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"auto_generated", .count = 14ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"is_enum_variant_ctor", .count = 20ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"captures", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"closure_name", .count = 12ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"noreturn", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"is_splat", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"does_throw", .count = 10ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"is_bang", .count = 7ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"own_args", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"keep_outer_args", .count = 15ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"swap_replace", .count = 12ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"noreturn_call", .count = 13ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"ref_args", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"text", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"fields", .count = 6ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"ns_decls", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"fields_index", .count = 12ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Map__Str_USize", .count = 14ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"ns_index", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"c_tag", .count = 5ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"is_interface", .count = 12ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"interface_ns_marker", .count = 19ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"implements_name", .count = 15ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"payload_type", .count = 12ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"payload_const", .count = 13ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"tag_value", .count = 9ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"payload_ref", .count = 11ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"variants", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Vec__VariantDef", .count = 15ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"tag_type", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"save_old_delete", .count = 15ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"is_payload_alias", .count = 16ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"is_move", .count = 7ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"transfers_own", .count = 13ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"name2", .count = 5ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"is_mut2", .count = 7ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Num", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"LiteralNumData", .count = 14ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Null", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"MapLit", .count = 6ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"SetLit", .count = 6ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"result_temp", .count = 11ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Map", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Set", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Literal", .count = 7ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Ident", .count = 5ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"IdentData", .count = 9ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Decl", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Declaration", .count = 11ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Assign", .count = 6ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"AssignData", .count = 10ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"FCall", .count = 5ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"FCallData", .count = 9ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"FunctionDef", .count = 11ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"FieldAccess", .count = 11ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"FieldAccessData", .count = 15ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"FieldAssign", .count = 11ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"FieldAssignData", .count = 15ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Return", .count = 6ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"If", .count = 2ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"While", .count = 5ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"ForIn", .count = 5ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"ForInData", .count = 9ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"NamedArg", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Break", .count = 5ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Continue", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Switch", .count = 6ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Match", .count = 5ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"MatchData", .count = 9ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Case", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"NoDefaultArg", .count = 12ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Throw", .count = 5ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Catch", .count = 5ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"RestPattern", .count = 11ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"CaptureBlock", .count = 12ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"CaptureBlockData", .count = 16ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Loc", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"BodyValue", .count = 9ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"ListPattern", .count = 11ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"node_type", .count = 9ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"NodeType", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"children", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Vec__Expr", .count = 9ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"line", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"col", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"keys", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"values", .count = 6ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Vec__USize", .count = 10ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"start", .count = 5ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"end", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:72:5", .count = 23ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:74:5", .count = 23ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:76:5", .count = 23ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:130:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:137:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:142:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:143:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:156:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"x", .count = 1ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"y", .count = 1ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:186:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"top_left", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"CfVec2", .count = 6ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"bottom_right", .count = 12ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:202:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"z", .count = 1ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:228:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:229:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:230:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Red", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Green", .count = 5ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Blue", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:241:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Name", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Eof", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:249:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:259:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:260:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:271:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:272:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Fn", .count = 2ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"?", .count = 1ULL, .cap = TIL_CAP_LIT},
};
#define TIL_LIT_GUARD(p) do { UPtr _g = (UPtr)(const void *)(p); if (_g >= (UPtr)(const void *)_til_str_lits && _g < (UPtr)(const void *)(_til_str_lits + 229)) { fprintf(stderr, "panic: write through a shared string literal\n"); exit(1); } } while (0)

U32 CAP_LIT;
U32 CAP_VIEW;
U32 ELEM_POD;
U32 ELEM_BOXED;
U32 ELEM_FN;
Type TYPE_NONE;
Type TYPE_UNKNOWN;
Type TYPE_DYNAMIC;
Type TYPE_FUNCPTR;
Type TYPE_BODY;
Type TYPE_BOOL;
Type TYPE_I64;
Type TYPE_STR;
Type TYPE_STRUCTDEF;
Type TYPE_ENUMDEF;
Type TYPE_MAP;
Type TYPE_SET;

Str * format(Array__Str * parts) {
    U32 total = 0;
    {
        Array__Str *_fc_Array__Str_57 = parts;
        (void)_fc_Array__Str_57;
        (void)_fc_Array__Str_57;
        U32 _fi_USize_57 = 0;
        (void)_fi_USize_57;
        while (1) {
            USize hoisted__U32_59 = (_fc_Array__Str_57->cap);
            (void)hoisted__U32_59;
            Bool _wcond_Bool_58 = ((Bool)(_fi_USize_57 < hoisted__U32_59));
            (void)_wcond_Bool_58;
            if (_wcond_Bool_58) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_57->data) + (((U32)(_fi_USize_57 * 16))))));
            U32 hoisted__U32_60 = 1;
            (void)hoisted__U32_60;
            U32 hoisted__U32_61 = ((U32)(_fi_USize_57 + hoisted__U32_60));
            (void)hoisted__U32_61;
            _fi_USize_57 = hoisted__U32_61;
            USize hoisted__U32_62 = (s->count);
            (void)hoisted__U32_62;
            U32 hoisted__U32_63 = ((U32)(total + hoisted__U32_62));
            (void)hoisted__U32_63;
            total = hoisted__U32_63;
        }
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_64 = parts;
        (void)_fc_Array__Str_64;
        (void)_fc_Array__Str_64;
        U32 _fi_USize_64 = 0;
        (void)_fi_USize_64;
        while (1) {
            USize hoisted__U32_66 = (_fc_Array__Str_64->cap);
            (void)hoisted__U32_66;
            Bool _wcond_Bool_65 = ((Bool)(_fi_USize_64 < hoisted__U32_66));
            (void)_wcond_Bool_65;
            if (_wcond_Bool_65) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_64->data) + (((U32)(_fi_USize_64 * 16))))));
            U32 hoisted__U32_67 = 1;
            (void)hoisted__U32_67;
            U32 hoisted__U32_68 = ((U32)(_fi_USize_64 + hoisted__U32_67));
            (void)hoisted__U32_68;
            _fi_USize_64 = hoisted__U32_68;
            Str_push_str(out, s);
        }
    }
    Array__Str_delete(parts, 1);
    return out;
    __builtin_unreachable();
}

USize Str_len(Str * self) {
    return self->count;
    __builtin_unreachable();
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_83 = ((Bool)(b->count < a->count));
    (void)hoisted__Bool_83;
    if (hoisted__Bool_83) {
        min_len = b->count;
    }
    I32 c = memcmp(a->c_str, b->c_str, min_len);
    I32 hoisted__I32_84 = 0;
    (void)hoisted__I32_84;
    Bool hoisted__Bool_85 = ((Bool)(c < hoisted__I32_84));
    (void)hoisted__Bool_85;
    if (hoisted__Bool_85) {
        I64 hoisted__I64_81 = -1;
        (void)hoisted__I64_81;
        return hoisted__I64_81;
    }
    I32 hoisted__I32_86 = 0;
    (void)hoisted__I32_86;
    Bool hoisted__Bool_87 = ((Bool)(c > hoisted__I32_86));
    (void)hoisted__Bool_87;
    if (hoisted__Bool_87) {
        I64 hoisted__I64_82 = 1;
        (void)hoisted__I64_82;
        return hoisted__I64_82;
    }
    I64 hoisted__I64_88 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_88;
    return hoisted__I64_88;
    __builtin_unreachable();
}

Bool Str_eq(Str * a, Str * b) {
    Bool hoisted__Bool_91 = ((Bool)(a->count != b->count));
    (void)hoisted__Bool_91;
    if (hoisted__Bool_91) {
        Bool hoisted__Bool_89 = 0;
        (void)hoisted__Bool_89;
        return hoisted__Bool_89;
    }
    Bool hoisted__Bool_92 = ptr_eq(a->c_str, b->c_str);
    (void)hoisted__Bool_92;
    if (hoisted__Bool_92) {
        Bool hoisted__Bool_90 = 1;
        (void)hoisted__Bool_90;
        return hoisted__Bool_90;
    }
    I32 hoisted__I32_93 = memcmp(a->c_str, b->c_str, a->count);
    (void)hoisted__I32_93;
    I32 hoisted__I32_94 = 0;
    (void)hoisted__I32_94;
    Bool hoisted__Bool_95 = ((Bool)(hoisted__I32_93 == hoisted__I32_94));
    (void)hoisted__Bool_95;
    return hoisted__Bool_95;
    __builtin_unreachable();
}

Str * Str_with_capacity(USize n) {
    U32 hoisted__U32_97 = 0;
    (void)hoisted__U32_97;
    Bool hoisted__Bool_98 = ((Bool)(n == hoisted__U32_97));
    (void)hoisted__Bool_98;
    if (hoisted__Bool_98) {
        static Str hoisted__Str_96 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_96;
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_96; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_99 = 1;
    (void)hoisted__U32_99;
    U32 hoisted__U32_100 = ((U32)(n + hoisted__U32_99));
    (void)hoisted__U32_100;
    I8 *buf = malloc(hoisted__U32_100);
    I32 hoisted__I32_101 = 0;
    (void)hoisted__I32_101;
    U64 hoisted__U64_102 = 1ULL;
    (void)hoisted__U64_102;
    memset(buf, hoisted__I32_101, hoisted__U64_102);
    I64 hoisted__I64_103 = 0;
    (void)hoisted__I64_103;
    Str *hoisted__Str_104 = malloc(sizeof(Str));
    hoisted__Str_104->c_str = buf;
    hoisted__Str_104->count = hoisted__I64_103;
    hoisted__Str_104->cap = n;
    (void)hoisted__Str_104;
    return hoisted__Str_104;
    __builtin_unreachable();
}

void Str_push_str(Str * self, Str * s) {
    U32 hoisted__U32_115 = 0;
    (void)hoisted__U32_115;
    Bool hoisted__Bool_116 = ((Bool)(s->count == hoisted__U32_115));
    (void)hoisted__Bool_116;
    if (hoisted__Bool_116) {
        return;
    }
    Bool hoisted__Bool_117 = ((Bool)(self->cap >= CAP_VIEW));
    (void)hoisted__Bool_117;
    if (hoisted__Bool_117) {
        U32 hoisted__U32_107 = 1;
        (void)hoisted__U32_107;
        Array__Str *_va_Array_1 = Array__Str_new(hoisted__U32_107);
        (void)_va_Array_1;
        I64 _va_Array_1_ek = 0;
        (void)_va_Array_1_ek;
        U32 hoisted__U32_108 = 0;
        (void)hoisted__U32_108;
        static Str hoisted__Str_109 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_109;
        Array__Str_set(_va_Array_1, hoisted__U32_108, &hoisted__Str_109, &_va_Array_1_ek);
        static Str hoisted__Str_110 = (Str){.c_str = (void *)"./src/core/str.til:118:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_110;
        panic(_va_Array_1, &hoisted__Str_110);
        Str_delete(&hoisted__Str_110, (Bool){0});
    }
    U32 new_len = ((U32)(self->count + s->count));
    Bool hoisted__Bool_118 = ((Bool)(new_len > self->cap));
    (void)hoisted__Bool_118;
    if (hoisted__Bool_118) {
        U32 hoisted__U32_111 = 1;
        (void)hoisted__U32_111;
        Array__Str *_va_Array_2 = Array__Str_new(hoisted__U32_111);
        (void)_va_Array_2;
        I64 _va_Array_2_ek = 0;
        (void)_va_Array_2_ek;
        U32 hoisted__U32_112 = 0;
        (void)hoisted__U32_112;
        static Str hoisted__Str_113 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_113;
        Array__Str_set(_va_Array_2, hoisted__U32_112, &hoisted__Str_113, &_va_Array_2_ek);
        static Str hoisted__Str_114 = (Str){.c_str = (void *)"./src/core/str.til:122:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_114;
        panic(_va_Array_2, &hoisted__Str_114);
        Str_delete(&hoisted__Str_114, (Bool){0});
    }
    void *hoisted__v_119 = ((void *)((U8 *)(self->c_str) + (self->count)));
    (void)hoisted__v_119;
    (void)hoisted__v_119;
    memcpy(hoisted__v_119, s->c_str, s->count);
    self->count = (new_len);
    void *hoisted__v_120 = ((void *)((U8 *)(self->c_str) + (new_len)));
    (void)hoisted__v_120;
    (void)hoisted__v_120;
    I32 hoisted__I32_121 = 0;
    (void)hoisted__I32_121;
    U64 hoisted__U64_122 = 1ULL;
    (void)hoisted__U64_122;
    memset(hoisted__v_120, hoisted__I32_121, hoisted__U64_122);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_124 = 0;
    (void)hoisted__U32_124;
    Bool hoisted__Bool_125 = ((Bool)(val->count == hoisted__U32_124));
    (void)hoisted__Bool_125;
    if (hoisted__Bool_125) {
        static Str hoisted__Str_123 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_123;
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_123; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_126 = 1;
    (void)hoisted__U32_126;
    U32 hoisted__U32_127 = ((U32)(val->count + hoisted__U32_126));
    (void)hoisted__U32_127;
    I8 *new_data = malloc(hoisted__U32_127);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_128 = ((void *)((U8 *)(new_data) + (val->count)));
    (void)hoisted__v_128;
    (void)hoisted__v_128;
    I32 hoisted__I32_129 = 0;
    (void)hoisted__I32_129;
    U64 hoisted__U64_130 = 1ULL;
    (void)hoisted__U64_130;
    memset(hoisted__v_128, hoisted__I32_129, hoisted__U64_130);
    Str *hoisted__Str_131 = malloc(sizeof(Str));
    hoisted__Str_131->c_str = new_data;
    hoisted__Str_131->count = val->count;
    hoisted__Str_131->cap = val->count;
    (void)hoisted__Str_131;
    return hoisted__Str_131;
    __builtin_unreachable();
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_132 = Str_clone(self);
    (void)hoisted__Str_132;
    return hoisted__Str_132;
    __builtin_unreachable();
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_133 = ((Bool)(self->cap < CAP_VIEW));
    (void)hoisted__Bool_133;
    if (hoisted__Bool_133) {
        free(self->c_str);
    }
    Bool hoisted__Bool_134 = ((Bool)(self->cap != CAP_LIT));
    (void)hoisted__Bool_134;
    Bool hoisted__Bool_135 = ((Bool)((call_free) && (hoisted__Bool_134)));
    (void)hoisted__Bool_135;
    if (hoisted__Bool_135) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_330 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, self->c_str, self->count); });
    (void)hoisted__U64_330;
    return hoisted__U64_330;
    __builtin_unreachable();
}

USize Str_size(void) {
    U32 hoisted__U32_503 = 16;
    (void)hoisted__U32_503;
    return hoisted__U32_503;
    __builtin_unreachable();
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_512 = Str_eq(a, b);
    (void)hoisted__Bool_512;
    Bool hoisted__Bool_513 = ((Bool)(!(hoisted__Bool_512)));
    (void)hoisted__Bool_513;
    return hoisted__Bool_513;
    __builtin_unreachable();
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * _self) {
    (void)_self;
    OutOfBounds *hoisted__OutOfBounds_602 = malloc(sizeof(OutOfBounds));
    (void)hoisted__OutOfBounds_602;
    return hoisted__OutOfBounds_602;
    __builtin_unreachable();
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_603 = 0;
    (void)hoisted__U32_603;
    U64 hoisted__U64_604 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_603); });
    (void)hoisted__U64_604;
    return hoisted__U64_604;
    __builtin_unreachable();
}

USize OutOfBounds_size(void) {
    U32 hoisted__U32_612 = 1;
    (void)hoisted__U32_612;
    return hoisted__U32_612;
    __builtin_unreachable();
}

KeyNotFound * KeyNotFound_clone(KeyNotFound * _self) {
    (void)_self;
    KeyNotFound *hoisted__KeyNotFound_613 = malloc(sizeof(KeyNotFound));
    (void)hoisted__KeyNotFound_613;
    return hoisted__KeyNotFound_613;
    __builtin_unreachable();
}

void KeyNotFound_delete(KeyNotFound * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 KeyNotFound_hash(KeyNotFound * self, HashFn hasher) {
    U32 hoisted__U32_614 = 0;
    (void)hoisted__U32_614;
    U64 hoisted__U64_615 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, KeyNotFound *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_614); });
    (void)hoisted__U64_615;
    return hoisted__U64_615;
    __builtin_unreachable();
}

USize KeyNotFound_size(void) {
    U32 hoisted__U32_623 = 1;
    (void)hoisted__U32_623;
    return hoisted__U32_623;
    __builtin_unreachable();
}

Array__Str * Array__Str_new(USize cap) {
    U32 hoisted__U32_624 = 16;
    (void)hoisted__U32_624;
    void * hoisted__v_625 = calloc(cap, hoisted__U32_624);
    (void)hoisted__v_625;
    Array__Str *hoisted__Array__Str_626 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_626->data = hoisted__v_625;
    hoisted__Array__Str_626->cap = cap;
    (void)hoisted__Array__Str_626;
    return hoisted__Array__Str_626;
    __builtin_unreachable();
}

USize Array__Str_len(Array__Str * self) {
    return self->cap;
    __builtin_unreachable();
}

Str * Array__Str_unsafe_get(Array__Str * self, USize * i) {
    U32 hoisted__U32_627 = 16;
    (void)hoisted__U32_627;
    U32 hoisted__U32_628 = ((U32)(DEREF(i) * hoisted__U32_627));
    (void)hoisted__U32_628;
    void *hoisted__v_629 = ((void *)((U8 *)(self->data) + (hoisted__U32_628)));
    (void)hoisted__v_629;
    (void)hoisted__v_629;
    return hoisted__v_629;
    __builtin_unreachable();
}

void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val) {
    Str *hoisted__Str_635 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    (void)hoisted__Str_635;
    (void)hoisted__Str_635;
    Bool hoisted__Bool_636 = 0;
    (void)hoisted__Bool_636;
    Str_delete(hoisted__Str_635, hoisted__Bool_636);
    Str *hoisted__Str_637 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    (void)hoisted__Str_637;
    (void)hoisted__Str_637;
    U32 hoisted__U32_638 = 16;
    (void)hoisted__U32_638;
    memcpy(hoisted__Str_637, val, hoisted__U32_638);
    I32 hoisted__I32_639 = 0;
    (void)hoisted__I32_639;
    U32 hoisted__U32_640 = 16;
    (void)hoisted__U32_640;
    if ((val)->cap != TIL_CAP_LIT) { memset(val, hoisted__I32_639, hoisted__U32_640); };
    Str_delete(val, 1);
}

void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind) {
    Bool hoisted__Bool_642 = ((Bool)(i >= self->cap));
    (void)hoisted__Bool_642;
    if (hoisted__Bool_642) {
        I64 hoisted__I64_641 = 1;
        (void)hoisted__I64_641;
        *_err_kind = hoisted__I64_641;
    }
    I64 hoisted__I64_643 = 0;
    (void)hoisted__I64_643;
    Bool hoisted__Bool_644 = ((Bool)(DEREF(_err_kind) == hoisted__I64_643));
    (void)hoisted__Bool_644;
    if (hoisted__Bool_644) {
        Array__Str_unsafe_set(self, i, val);
    } else {
        Str_delete(val, 1);
    }
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_645 = self->cap;
        (void)_re_U32_645;
        U32 _rc_U32_645 = 0;
        (void)_rc_U32_645;
        Bool hoisted__Bool_656 = ((Bool)(_rc_U32_645 <= _re_U32_645));
        (void)hoisted__Bool_656;
        if (hoisted__Bool_656) {
            while (1) {
                Bool _wcond_Bool_646 = ((Bool)(_rc_U32_645 < _re_U32_645));
                (void)_wcond_Bool_646;
                if (_wcond_Bool_646) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_645);
                (++_rc_U32_645);
                U32 hoisted__U32_647 = 16;
                (void)hoisted__U32_647;
                U32 hoisted__U32_648 = ((U32)(i * hoisted__U32_647));
                (void)hoisted__U32_648;
                Str *hoisted__Str_649 = ((void *)((U8 *)(self->data) + (hoisted__U32_648)));
                (void)hoisted__Str_649;
                (void)hoisted__Str_649;
                Bool hoisted__Bool_650 = 0;
                (void)hoisted__Bool_650;
                Str_delete(hoisted__Str_649, hoisted__Bool_650);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_651 = ((Bool)(_rc_U32_645 > _re_U32_645));
                (void)_wcond_Bool_651;
                if (_wcond_Bool_651) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_645);
                (--_rc_U32_645);
                U32 hoisted__U32_652 = 16;
                (void)hoisted__U32_652;
                U32 hoisted__U32_653 = ((U32)(i * hoisted__U32_652));
                (void)hoisted__U32_653;
                Str *hoisted__Str_654 = ((void *)((U8 *)(self->data) + (hoisted__U32_653)));
                (void)hoisted__Str_654;
                (void)hoisted__Str_654;
                Bool hoisted__Bool_655 = 0;
                (void)hoisted__Bool_655;
                Str_delete(hoisted__Str_654, hoisted__Bool_655);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_677 = 16;
    (void)hoisted__U32_677;
    U32 hoisted__U32_678 = ((U32)(self->cap * hoisted__U32_677));
    (void)hoisted__U32_678;
    U8 *new_data = malloc(hoisted__U32_678);
    {
        U32 _re_U32_657 = self->cap;
        (void)_re_U32_657;
        U32 _rc_U32_657 = 0;
        (void)_rc_U32_657;
        Bool hoisted__Bool_676 = ((Bool)(_rc_U32_657 <= _re_U32_657));
        (void)hoisted__Bool_676;
        if (hoisted__Bool_676) {
            while (1) {
                Bool _wcond_Bool_658 = ((Bool)(_rc_U32_657 < _re_U32_657));
                (void)_wcond_Bool_658;
                if (_wcond_Bool_658) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_657);
                (++_rc_U32_657);
                U32 hoisted__U32_659 = 16;
                (void)hoisted__U32_659;
                U32 hoisted__U32_660 = ((U32)(i * hoisted__U32_659));
                (void)hoisted__U32_660;
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_660)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_661 = 16;
                (void)hoisted__U32_661;
                U32 hoisted__U32_662 = ((U32)(i * hoisted__U32_661));
                (void)hoisted__U32_662;
                void *hoisted__v_663 = ((void *)((U8 *)(new_data) + (hoisted__U32_662)));
                (void)hoisted__v_663;
                (void)hoisted__v_663;
                U32 hoisted__U32_664 = 16;
                (void)hoisted__U32_664;
                memcpy(hoisted__v_663, cloned, hoisted__U32_664);
                I32 hoisted__I32_665 = 0;
                (void)hoisted__I32_665;
                U32 hoisted__U32_666 = 16;
                (void)hoisted__U32_666;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_665, hoisted__U32_666); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_667 = ((Bool)(_rc_U32_657 > _re_U32_657));
                (void)_wcond_Bool_667;
                if (_wcond_Bool_667) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_657);
                (--_rc_U32_657);
                U32 hoisted__U32_668 = 16;
                (void)hoisted__U32_668;
                U32 hoisted__U32_669 = ((U32)(i * hoisted__U32_668));
                (void)hoisted__U32_669;
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_669)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_670 = 16;
                (void)hoisted__U32_670;
                U32 hoisted__U32_671 = ((U32)(i * hoisted__U32_670));
                (void)hoisted__U32_671;
                void *hoisted__v_672 = ((void *)((U8 *)(new_data) + (hoisted__U32_671)));
                (void)hoisted__v_672;
                (void)hoisted__v_672;
                U32 hoisted__U32_673 = 16;
                (void)hoisted__U32_673;
                memcpy(hoisted__v_672, cloned, hoisted__U32_673);
                I32 hoisted__I32_674 = 0;
                (void)hoisted__I32_674;
                U32 hoisted__U32_675 = 16;
                (void)hoisted__U32_675;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_674, hoisted__U32_675); };
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_679 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_679->data = new_data;
    hoisted__Array__Str_679->cap = self->cap;
    (void)hoisted__Array__Str_679;
    return hoisted__Array__Str_679;
    __builtin_unreachable();
}

USize Array__Str_size(void) {
    U32 hoisted__U32_680 = 16;
    (void)hoisted__U32_680;
    return hoisted__U32_680;
    __builtin_unreachable();
}

Vec__Str * Vec__Str_new(void) {
    U8 *hoisted__U8_681 = malloc(sizeof(U8));
    *hoisted__U8_681 = 0;
    (void)hoisted__U8_681;
    U32 hoisted__U32_682 = 0;
    (void)hoisted__U32_682;
    I64 hoisted__I64_683 = 0;
    (void)hoisted__I64_683;
    Vec__Str *hoisted__Vec__Str_684 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_684->data = hoisted__U8_681;
    hoisted__Vec__Str_684->count = hoisted__U32_682;
    hoisted__Vec__Str_684->cap = hoisted__I64_683;
    (void)hoisted__Vec__Str_684;
    return hoisted__Vec__Str_684;
    __builtin_unreachable();
}

void Vec__Str_clear(Vec__Str * self) {
    {
        U32 _re_U32_696 = self->count;
        (void)_re_U32_696;
        U32 _rc_U32_696 = 0;
        (void)_rc_U32_696;
        Bool hoisted__Bool_707 = ((Bool)(_rc_U32_696 <= _re_U32_696));
        (void)hoisted__Bool_707;
        if (hoisted__Bool_707) {
            while (1) {
                Bool _wcond_Bool_697 = ((Bool)(_rc_U32_696 < _re_U32_696));
                (void)_wcond_Bool_697;
                if (_wcond_Bool_697) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_696);
                (++_rc_U32_696);
                U32 hoisted__U32_698 = 16;
                (void)hoisted__U32_698;
                U32 hoisted__U32_699 = ((U32)(i * hoisted__U32_698));
                (void)hoisted__U32_699;
                Str *hoisted__Str_700 = ((void *)((U8 *)(self->data) + (hoisted__U32_699)));
                (void)hoisted__Str_700;
                (void)hoisted__Str_700;
                Bool hoisted__Bool_701 = 0;
                (void)hoisted__Bool_701;
                Str_delete(hoisted__Str_700, hoisted__Bool_701);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_702 = ((Bool)(_rc_U32_696 > _re_U32_696));
                (void)_wcond_Bool_702;
                if (_wcond_Bool_702) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_696);
                (--_rc_U32_696);
                U32 hoisted__U32_703 = 16;
                (void)hoisted__U32_703;
                U32 hoisted__U32_704 = ((U32)(i * hoisted__U32_703));
                (void)hoisted__U32_704;
                Str *hoisted__Str_705 = ((void *)((U8 *)(self->data) + (hoisted__U32_704)));
                (void)hoisted__Str_705;
                (void)hoisted__Str_705;
                Bool hoisted__Bool_706 = 0;
                (void)hoisted__Bool_706;
                Str_delete(hoisted__Str_705, hoisted__Bool_706);
            }
        }
    }
    U32 hoisted__U32_708 = 0;
    (void)hoisted__U32_708;
    self->count = hoisted__U32_708;
}

void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Str * Vec__Str_clone(Vec__Str * self) {
    U32 hoisted__U32_968 = 0;
    (void)hoisted__U32_968;
    Bool hoisted__Bool_969 = ((Bool)(self->cap == hoisted__U32_968));
    (void)hoisted__Bool_969;
    if (hoisted__Bool_969) {
        U8 *hoisted__U8_944 = malloc(sizeof(U8));
        *hoisted__U8_944 = 0;
        (void)hoisted__U8_944;
        U32 hoisted__U32_945 = 0;
        (void)hoisted__U32_945;
        I64 hoisted__I64_946 = 0;
        (void)hoisted__I64_946;
        Vec__Str *hoisted__Vec__Str_947 = malloc(sizeof(Vec__Str));
        hoisted__Vec__Str_947->data = hoisted__U8_944;
        hoisted__Vec__Str_947->count = hoisted__U32_945;
        hoisted__Vec__Str_947->cap = hoisted__I64_946;
        (void)hoisted__Vec__Str_947;
        return hoisted__Vec__Str_947;
    }
    U32 hoisted__U32_970 = 16;
    (void)hoisted__U32_970;
    U32 hoisted__U32_971 = ((U32)(self->cap * hoisted__U32_970));
    (void)hoisted__U32_971;
    U8 *new_data = malloc(hoisted__U32_971);
    {
        U32 _re_U32_948 = self->count;
        (void)_re_U32_948;
        U32 _rc_U32_948 = 0;
        (void)_rc_U32_948;
        Bool hoisted__Bool_967 = ((Bool)(_rc_U32_948 <= _re_U32_948));
        (void)hoisted__Bool_967;
        if (hoisted__Bool_967) {
            while (1) {
                Bool _wcond_Bool_949 = ((Bool)(_rc_U32_948 < _re_U32_948));
                (void)_wcond_Bool_949;
                if (_wcond_Bool_949) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_948);
                (++_rc_U32_948);
                U32 hoisted__U32_950 = 16;
                (void)hoisted__U32_950;
                U32 hoisted__U32_951 = ((U32)(i * hoisted__U32_950));
                (void)hoisted__U32_951;
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_951)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_952 = 16;
                (void)hoisted__U32_952;
                U32 hoisted__U32_953 = ((U32)(i * hoisted__U32_952));
                (void)hoisted__U32_953;
                void *hoisted__v_954 = ((void *)((U8 *)(new_data) + (hoisted__U32_953)));
                (void)hoisted__v_954;
                (void)hoisted__v_954;
                U32 hoisted__U32_955 = 16;
                (void)hoisted__U32_955;
                memcpy(hoisted__v_954, cloned, hoisted__U32_955);
                I32 hoisted__I32_956 = 0;
                (void)hoisted__I32_956;
                U32 hoisted__U32_957 = 16;
                (void)hoisted__U32_957;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_956, hoisted__U32_957); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_958 = ((Bool)(_rc_U32_948 > _re_U32_948));
                (void)_wcond_Bool_958;
                if (_wcond_Bool_958) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_948);
                (--_rc_U32_948);
                U32 hoisted__U32_959 = 16;
                (void)hoisted__U32_959;
                U32 hoisted__U32_960 = ((U32)(i * hoisted__U32_959));
                (void)hoisted__U32_960;
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_960)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_961 = 16;
                (void)hoisted__U32_961;
                U32 hoisted__U32_962 = ((U32)(i * hoisted__U32_961));
                (void)hoisted__U32_962;
                void *hoisted__v_963 = ((void *)((U8 *)(new_data) + (hoisted__U32_962)));
                (void)hoisted__v_963;
                (void)hoisted__v_963;
                U32 hoisted__U32_964 = 16;
                (void)hoisted__U32_964;
                memcpy(hoisted__v_963, cloned, hoisted__U32_964);
                I32 hoisted__I32_965 = 0;
                (void)hoisted__I32_965;
                U32 hoisted__U32_966 = 16;
                (void)hoisted__U32_966;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_965, hoisted__U32_966); };
                Str_delete(cloned, 1);
            }
        }
    }
    Vec__Str *hoisted__Vec__Str_972 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_972->data = new_data;
    hoisted__Vec__Str_972->count = self->count;
    hoisted__Vec__Str_972->cap = self->cap;
    (void)hoisted__Vec__Str_972;
    return hoisted__Vec__Str_972;
    __builtin_unreachable();
}

USize Vec__Str_size(void) {
    U32 hoisted__U32_973 = 16;
    (void)hoisted__U32_973;
    return hoisted__U32_973;
    __builtin_unreachable();
}

USize Dynamic_size(void) {
    U32 hoisted__U32_976 = 8;
    (void)hoisted__U32_976;
    return hoisted__U32_976;
    __builtin_unreachable();
}

void * Dynamic_clone(void * self) {
    U32 hoisted__U32_977 = 8;
    (void)hoisted__U32_977;
    U8 *out = malloc(hoisted__U32_977);
    U32 hoisted__U32_978 = 8;
    (void)hoisted__U32_978;
    memcpy(out, self, hoisted__U32_978);
    return out;
    __builtin_unreachable();
}

void Dynamic_delete(void * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

void U8_delete(U8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize U8_size(void) {
    U32 hoisted__U32_1085 = 1;
    (void)hoisted__U32_1085;
    return hoisted__U32_1085;
    __builtin_unreachable();
}

U64 U8_hash(U8 self, HashFn hasher) {
    U32 hoisted__U32_1152 = 1;
    (void)hoisted__U32_1152;
    U64 hoisted__U64_1153 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1152); });
    (void)hoisted__U64_1153;
    return hoisted__U64_1153;
    __builtin_unreachable();
}

void U32_delete(U32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize U32_size(void) {
    U32 hoisted__U32_1239 = 4;
    (void)hoisted__U32_1239;
    return hoisted__U32_1239;
    __builtin_unreachable();
}

U64 U32_hash(U32 self, HashFn hasher) {
    U32 hoisted__U32_1306 = 4;
    (void)hoisted__U32_1306;
    U64 hoisted__U64_1307 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1306); });
    (void)hoisted__U64_1307;
    return hoisted__U64_1307;
    __builtin_unreachable();
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *hoisted__Str_1308 = U64_to_str_ext(val);
    (void)hoisted__Str_1308;
    return hoisted__Str_1308;
    __builtin_unreachable();
}

void U64_delete(U64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize U64_size(void) {
    U32 hoisted__U32_1313 = 8;
    (void)hoisted__U32_1313;
    return hoisted__U32_1313;
    __builtin_unreachable();
}

U64 U64_hash(U64 self, HashFn hasher) {
    U32 hoisted__U32_1380 = 8;
    (void)hoisted__U32_1380;
    U64 hoisted__U64_1381 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1380); });
    (void)hoisted__U64_1381;
    return hoisted__U64_1381;
    __builtin_unreachable();
}

void I8_delete(I8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize I8_size(void) {
    U32 hoisted__U32_1398 = 1;
    (void)hoisted__U32_1398;
    return hoisted__U32_1398;
    __builtin_unreachable();
}

U64 I8_hash(I8 self, HashFn hasher) {
    U32 hoisted__U32_1399 = 1;
    (void)hoisted__U32_1399;
    U64 hoisted__U64_1400 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1399); });
    (void)hoisted__U64_1400;
    return hoisted__U64_1400;
    __builtin_unreachable();
}

void I32_delete(I32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize I32_size(void) {
    U32 hoisted__U32_1547 = 4;
    (void)hoisted__U32_1547;
    return hoisted__U32_1547;
    __builtin_unreachable();
}

U64 I32_hash(I32 self, HashFn hasher) {
    U32 hoisted__U32_1659 = 4;
    (void)hoisted__U32_1659;
    U64 hoisted__U64_1660 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1659); });
    (void)hoisted__U64_1660;
    return hoisted__U64_1660;
    __builtin_unreachable();
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1669 = 0;
    (void)hoisted__I64_1669;
    Bool hoisted__Bool_1670 = ((Bool)(val < hoisted__I64_1669));
    (void)hoisted__Bool_1670;
    if (hoisted__Bool_1670) {
        U64 hoisted__U64_1661 = 0ULL;
        (void)hoisted__U64_1661;
        U64 hoisted__U64_1662 = (U64)(val);
        (void)hoisted__U64_1662;
        U64 mag = ((U64)(hoisted__U64_1661 - hoisted__U64_1662));
        U32 hoisted__U32_1663 = 2;
        (void)hoisted__U32_1663;
        Array__Str *_va_Array_39 = Array__Str_new(hoisted__U32_1663);
        (void)_va_Array_39;
        I64 _va_Array_39_ek = 0;
        (void)_va_Array_39_ek;
        U32 hoisted__U32_1664 = 0;
        (void)hoisted__U32_1664;
        static Str hoisted__Str_1665 = (Str){.c_str = (void *)"-", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1665;
        Array__Str_set(_va_Array_39, hoisted__U32_1664, &hoisted__Str_1665, &_va_Array_39_ek);
        U32 hoisted__U32_1666 = 1;
        (void)hoisted__U32_1666;
        Str *hoisted__Str_1667 = U64_to_str(mag);
        (void)hoisted__Str_1667;
        Array__Str_set(_va_Array_39, hoisted__U32_1666, hoisted__Str_1667, &_va_Array_39_ek);
        Str *hoisted__Str_1668 = format(_va_Array_39);
        (void)hoisted__Str_1668;
        return hoisted__Str_1668;
    }
    U64 hoisted__U64_1671 = (U64)(val);
    (void)hoisted__U64_1671;
    Str *hoisted__Str_1672 = U64_to_str(hoisted__U64_1671);
    (void)hoisted__Str_1672;
    return hoisted__Str_1672;
    __builtin_unreachable();
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize I64_size(void) {
    U32 hoisted__U32_1686 = 8;
    (void)hoisted__U32_1686;
    return hoisted__U32_1686;
    __builtin_unreachable();
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_1812 = 8;
    (void)hoisted__U32_1812;
    U64 hoisted__U64_1813 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1812); });
    (void)hoisted__U64_1813;
    return hoisted__U64_1813;
    __builtin_unreachable();
}

void F32_delete(F32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize F32_size(void) {
    U32 hoisted__U32_1815 = 4;
    (void)hoisted__U32_1815;
    return hoisted__U32_1815;
    __builtin_unreachable();
}

U64 F32_hash(F32 self, HashFn hasher) {
    U32 hoisted__U32_1831 = 4;
    (void)hoisted__U32_1831;
    U64 hoisted__U64_1832 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, F32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1831); });
    (void)hoisted__U64_1832;
    return hoisted__U64_1832;
    __builtin_unreachable();
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_1875 = ((Bool)(a == b));
    (void)hoisted__Bool_1875;
    if (hoisted__Bool_1875) {
        I64 hoisted__I64_1873 = 0;
        (void)hoisted__I64_1873;
        return hoisted__I64_1873;
    }
    if (b) {
        I64 hoisted__I64_1874 = -1;
        (void)hoisted__I64_1874;
        return hoisted__I64_1874;
    }
    I64 hoisted__I64_1876 = 1;
    (void)hoisted__I64_1876;
    return hoisted__I64_1876;
    __builtin_unreachable();
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize Bool_size(void) {
    U32 hoisted__U32_1877 = 1;
    (void)hoisted__U32_1877;
    return hoisted__U32_1877;
    __builtin_unreachable();
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_1878 = 1;
    (void)hoisted__U32_1878;
    U64 hoisted__U64_1879 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1878); });
    (void)hoisted__U64_1879;
    return hoisted__U64_1879;
    __builtin_unreachable();
}

Primitive *Primitive_I16() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_I16 };
    return r;
}
Primitive *Primitive_U16() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_U16 };
    return r;
}
Primitive *Primitive_I8() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_I8 };
    return r;
}
Primitive *Primitive_U8() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_U8 };
    return r;
}
Primitive *Primitive_U32() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_U32 };
    return r;
}
Primitive *Primitive_I32() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_I32 };
    return r;
}
Primitive *Primitive_U64() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_U64 };
    return r;
}
Primitive *Primitive_I64() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_I64 };
    return r;
}
Primitive *Primitive_F32() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_F32 };
    return r;
}
Primitive *Primitive_Bool() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_Bool };
    return r;
}
Bool Primitive_eq(Primitive * self, Primitive * other) {
    U32 hoisted__U32_1951 = 1;
    (void)hoisted__U32_1951;
    Bool hoisted__Bool_1952 = ((Bool)((((Primitive *)(self))->tag) == (((Primitive *)(other))->tag)));
    (void)hoisted__Bool_1952;
    return hoisted__Bool_1952;
    __builtin_unreachable();
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1974 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1974;
    if (hoisted__Bool_1974) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
        return _r; }
    }
    Bool hoisted__Bool_1975 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1975;
    if (hoisted__Bool_1975) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
        return _r; }
    }
    Bool hoisted__Bool_1976 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_1976;
    if (hoisted__Bool_1976) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
        return _r; }
    }
    Bool hoisted__Bool_1977 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_1977;
    if (hoisted__Bool_1977) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
        return _r; }
    }
    Bool hoisted__Bool_1978 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_1978;
    if (hoisted__Bool_1978) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
        return _r; }
    }
    Bool hoisted__Bool_1979 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_1979;
    if (hoisted__Bool_1979) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
        return _r; }
    }
    Bool hoisted__Bool_1980 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_1980;
    if (hoisted__Bool_1980) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
        return _r; }
    }
    Bool hoisted__Bool_1981 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_1981;
    if (hoisted__Bool_1981) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
        return _r; }
    }
    Bool hoisted__Bool_1982 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_1982;
    if (hoisted__Bool_1982) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
        return _r; }
    }
    Bool hoisted__Bool_1983 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_1983;
    if (hoisted__Bool_1983) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
        return _r; }
    }
    static Str hoisted__Str_1984 = (Str){.c_str = (void *)"Primitive.clone:15:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_1984;
    UNREACHABLE(&hoisted__Str_1984);
    Str_delete(&hoisted__Str_1984, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
    __builtin_unreachable();
}

USize Primitive_size(void) {
    U32 hoisted__U32_1985 = 1;
    (void)hoisted__U32_1985;
    return hoisted__U32_1985;
    __builtin_unreachable();
}


Type *Type_Unknown() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_Unknown;
    return r;
}
Type *Type_None() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_None;
    return r;
}
Type *Type_Struct(Str * val) {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_Struct;
    r->data.Struct = *val;
    if (val->cap != TIL_CAP_LIT) { free(val); }
    return r;
}
Type *Type_StructDef() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_StructDef;
    return r;
}
Type *Type_Enum(Str * val) {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_Enum;
    r->data.Enum = *val;
    if (val->cap != TIL_CAP_LIT) { free(val); }
    return r;
}
Type *Type_EnumDef() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_EnumDef;
    return r;
}
Type *Type_FuncDef() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_FuncDef;
    return r;
}
Type *Type_FuncPtr() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_FuncPtr;
    return r;
}
Type *Type_Dynamic() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_Dynamic;
    return r;
}
Type *Type_Custom(Str * val) {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_Custom;
    r->data.Custom = *val;
    if (val->cap != TIL_CAP_LIT) { free(val); }
    return r;
}
Type *Type_Primitive(Primitive * val) {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_Primitive;
    r->data.Primitive = *val;
    free(val);
    return r;
}
Type *Type_FuncPtrSig(Str * val) {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_FuncPtrSig;
    r->data.FuncPtrSig = *val;
    if (val->cap != TIL_CAP_LIT) { free(val); }
    return r;
}
Type *Type_Body() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_Body;
    return r;
}
void Type_delete(Type * self, Bool call_free) {
    U32 hoisted__U32_2064 = 1;
    (void)hoisted__U32_2064;
    Bool hoisted__Bool_2065 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Struct}))->tag)));
    (void)hoisted__Bool_2065;
    if (hoisted__Bool_2065) {
        Str *hoisted__Str_2054 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)hoisted__Str_2054;
        (void)hoisted__Str_2054;
        Bool hoisted__Bool_2055 = 0;
        (void)hoisted__Bool_2055;
        Str_delete(hoisted__Str_2054, hoisted__Bool_2055);
    }
    U32 hoisted__U32_2066 = 1;
    (void)hoisted__U32_2066;
    Bool hoisted__Bool_2067 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Enum}))->tag)));
    (void)hoisted__Bool_2067;
    if (hoisted__Bool_2067) {
        Str *hoisted__Str_2056 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)hoisted__Str_2056;
        (void)hoisted__Str_2056;
        Bool hoisted__Bool_2057 = 0;
        (void)hoisted__Bool_2057;
        Str_delete(hoisted__Str_2056, hoisted__Bool_2057);
    }
    U32 hoisted__U32_2068 = 1;
    (void)hoisted__U32_2068;
    Bool hoisted__Bool_2069 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Custom}))->tag)));
    (void)hoisted__Bool_2069;
    if (hoisted__Bool_2069) {
        Str *hoisted__Str_2058 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)hoisted__Str_2058;
        (void)hoisted__Str_2058;
        Bool hoisted__Bool_2059 = 0;
        (void)hoisted__Bool_2059;
        Str_delete(hoisted__Str_2058, hoisted__Bool_2059);
    }
    U32 hoisted__U32_2070 = 1;
    (void)hoisted__U32_2070;
    Bool hoisted__Bool_2071 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Primitive}))->tag)));
    (void)hoisted__Bool_2071;
    if (hoisted__Bool_2071) {
        Primitive *hoisted__Primitive_2060 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)hoisted__Primitive_2060;
        (void)hoisted__Primitive_2060;
        Bool hoisted__Bool_2061 = 0;
        (void)hoisted__Bool_2061;
        Primitive_delete(hoisted__Primitive_2060, hoisted__Bool_2061);
    }
    U32 hoisted__U32_2072 = 1;
    (void)hoisted__U32_2072;
    Bool hoisted__Bool_2073 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_FuncPtrSig}))->tag)));
    (void)hoisted__Bool_2073;
    if (hoisted__Bool_2073) {
        Str *hoisted__Str_2062 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)hoisted__Str_2062;
        (void)hoisted__Str_2062;
        Bool hoisted__Bool_2063 = 0;
        (void)hoisted__Bool_2063;
        Str_delete(hoisted__Str_2062, hoisted__Bool_2063);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    U32 hoisted__U32_2159 = 1;
    (void)hoisted__U32_2159;
    Bool hoisted__Bool_2160 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Unknown}))->tag)));
    (void)hoisted__Bool_2160;
    if (hoisted__Bool_2160) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
        return _r; }
    }
    U32 hoisted__U32_2161 = 1;
    (void)hoisted__U32_2161;
    Bool hoisted__Bool_2162 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_None}))->tag)));
    (void)hoisted__Bool_2162;
    if (hoisted__Bool_2162) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
        return _r; }
    }
    U32 hoisted__U32_2163 = 1;
    (void)hoisted__U32_2163;
    Bool hoisted__Bool_2164 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Struct}))->tag)));
    (void)hoisted__Bool_2164;
    if (hoisted__Bool_2164) {
        Str *_clone_payload_Struct_2 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2149 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2149;
        Type *hoisted__Type_2150 = Type_Struct(hoisted__Str_2149);
        (void)hoisted__Type_2150;
        return hoisted__Type_2150;
    }
    U32 hoisted__U32_2165 = 1;
    (void)hoisted__U32_2165;
    Bool hoisted__Bool_2166 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_StructDef}))->tag)));
    (void)hoisted__Bool_2166;
    if (hoisted__Bool_2166) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
        return _r; }
    }
    U32 hoisted__U32_2167 = 1;
    (void)hoisted__U32_2167;
    Bool hoisted__Bool_2168 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Enum}))->tag)));
    (void)hoisted__Bool_2168;
    if (hoisted__Bool_2168) {
        Str *_clone_payload_Enum_4 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2151 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2151;
        Type *hoisted__Type_2152 = Type_Enum(hoisted__Str_2151);
        (void)hoisted__Type_2152;
        return hoisted__Type_2152;
    }
    U32 hoisted__U32_2169 = 1;
    (void)hoisted__U32_2169;
    Bool hoisted__Bool_2170 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_EnumDef}))->tag)));
    (void)hoisted__Bool_2170;
    if (hoisted__Bool_2170) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
        return _r; }
    }
    U32 hoisted__U32_2171 = 1;
    (void)hoisted__U32_2171;
    Bool hoisted__Bool_2172 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_FuncDef}))->tag)));
    (void)hoisted__Bool_2172;
    if (hoisted__Bool_2172) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
        return _r; }
    }
    U32 hoisted__U32_2173 = 1;
    (void)hoisted__U32_2173;
    Bool hoisted__Bool_2174 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_FuncPtr}))->tag)));
    (void)hoisted__Bool_2174;
    if (hoisted__Bool_2174) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
        return _r; }
    }
    U32 hoisted__U32_2175 = 1;
    (void)hoisted__U32_2175;
    Bool hoisted__Bool_2176 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Dynamic}))->tag)));
    (void)hoisted__Bool_2176;
    if (hoisted__Bool_2176) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
        return _r; }
    }
    U32 hoisted__U32_2177 = 1;
    (void)hoisted__U32_2177;
    Bool hoisted__Bool_2178 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Custom}))->tag)));
    (void)hoisted__Bool_2178;
    if (hoisted__Bool_2178) {
        Str *_clone_payload_Custom_9 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2153 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2153;
        Type *hoisted__Type_2154 = Type_Custom(hoisted__Str_2153);
        (void)hoisted__Type_2154;
        return hoisted__Type_2154;
    }
    U32 hoisted__U32_2179 = 1;
    (void)hoisted__U32_2179;
    Bool hoisted__Bool_2180 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Primitive}))->tag)));
    (void)hoisted__Bool_2180;
    if (hoisted__Bool_2180) {
        Primitive *_clone_payload_Primitive_10 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2155 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2155;
        Type *hoisted__Type_2156 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2155; _oa; }));
        (void)hoisted__Type_2156;
        return hoisted__Type_2156;
    }
    U32 hoisted__U32_2181 = 1;
    (void)hoisted__U32_2181;
    Bool hoisted__Bool_2182 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_FuncPtrSig}))->tag)));
    (void)hoisted__Bool_2182;
    if (hoisted__Bool_2182) {
        Str *_clone_payload_FuncPtrSig_11 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)_clone_payload_FuncPtrSig_11;
        (void)_clone_payload_FuncPtrSig_11;
        Str *hoisted__Str_2157 = Str_clone(_clone_payload_FuncPtrSig_11);
        (void)hoisted__Str_2157;
        Type *hoisted__Type_2158 = Type_FuncPtrSig(hoisted__Str_2157);
        (void)hoisted__Type_2158;
        return hoisted__Type_2158;
    }
    { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Body;
    return _r; }
    __builtin_unreachable();
}

USize Type_size(void) {
    U32 hoisted__U32_2183 = 24;
    (void)hoisted__U32_2183;
    return hoisted__U32_2183;
    __builtin_unreachable();
}


FuncType *FuncType_Func() {
    FuncType *r = malloc(sizeof(FuncType));
    *r = (FuncType){ .tag = FuncType_TAG_Func };
    return r;
}
FuncType *FuncType_Proc() {
    FuncType *r = malloc(sizeof(FuncType));
    *r = (FuncType){ .tag = FuncType_TAG_Proc };
    return r;
}
FuncType *FuncType_Test() {
    FuncType *r = malloc(sizeof(FuncType));
    *r = (FuncType){ .tag = FuncType_TAG_Test };
    return r;
}
FuncType *FuncType_Macro() {
    FuncType *r = malloc(sizeof(FuncType));
    *r = (FuncType){ .tag = FuncType_TAG_Macro };
    return r;
}
FuncType *FuncType_ExtFunc() {
    FuncType *r = malloc(sizeof(FuncType));
    *r = (FuncType){ .tag = FuncType_TAG_ExtFunc };
    return r;
}
FuncType *FuncType_ExtProc() {
    FuncType *r = malloc(sizeof(FuncType));
    *r = (FuncType){ .tag = FuncType_TAG_ExtProc };
    return r;
}
FuncType *FuncType_LazyFunc() {
    FuncType *r = malloc(sizeof(FuncType));
    *r = (FuncType){ .tag = FuncType_TAG_LazyFunc };
    return r;
}
FuncType *FuncType_LazyProc() {
    FuncType *r = malloc(sizeof(FuncType));
    *r = (FuncType){ .tag = FuncType_TAG_LazyProc };
    return r;
}
FuncType *FuncType_CoreFunc() {
    FuncType *r = malloc(sizeof(FuncType));
    *r = (FuncType){ .tag = FuncType_TAG_CoreFunc };
    return r;
}
FuncType *FuncType_CoreProc() {
    FuncType *r = malloc(sizeof(FuncType));
    *r = (FuncType){ .tag = FuncType_TAG_CoreProc };
    return r;
}
FuncType *FuncType_CoreLazyFunc() {
    FuncType *r = malloc(sizeof(FuncType));
    *r = (FuncType){ .tag = FuncType_TAG_CoreLazyFunc };
    return r;
}
Bool FuncType_eq(FuncType * self, FuncType * other) {
    U32 hoisted__U32_2195 = 1;
    (void)hoisted__U32_2195;
    Bool hoisted__Bool_2196 = ((Bool)((((FuncType *)(self))->tag) == (((FuncType *)(other))->tag)));
    (void)hoisted__Bool_2196;
    return hoisted__Bool_2196;
    __builtin_unreachable();
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2220 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2220;
    if (hoisted__Bool_2220) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
        return _r; }
    }
    Bool hoisted__Bool_2221 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2221;
    if (hoisted__Bool_2221) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
        return _r; }
    }
    Bool hoisted__Bool_2222 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2222;
    if (hoisted__Bool_2222) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
        return _r; }
    }
    Bool hoisted__Bool_2223 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2223;
    if (hoisted__Bool_2223) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
        return _r; }
    }
    Bool hoisted__Bool_2224 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2224;
    if (hoisted__Bool_2224) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
        return _r; }
    }
    Bool hoisted__Bool_2225 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2225;
    if (hoisted__Bool_2225) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
        return _r; }
    }
    Bool hoisted__Bool_2226 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2226;
    if (hoisted__Bool_2226) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
        return _r; }
    }
    Bool hoisted__Bool_2227 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2227;
    if (hoisted__Bool_2227) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
        return _r; }
    }
    Bool hoisted__Bool_2228 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreFunc});
    (void)hoisted__Bool_2228;
    if (hoisted__Bool_2228) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreFunc;
        return _r; }
    }
    Bool hoisted__Bool_2229 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreProc});
    (void)hoisted__Bool_2229;
    if (hoisted__Bool_2229) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreProc;
        return _r; }
    }
    Bool hoisted__Bool_2230 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreLazyFunc});
    (void)hoisted__Bool_2230;
    if (hoisted__Bool_2230) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreLazyFunc;
        return _r; }
    }
    static Str hoisted__Str_2231 = (Str){.c_str = (void *)"FuncType.clone:70:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2231;
    UNREACHABLE(&hoisted__Str_2231);
    Str_delete(&hoisted__Str_2231, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
    __builtin_unreachable();
}

USize FuncType_size(void) {
    U32 hoisted__U32_2232 = 1;
    (void)hoisted__U32_2232;
    return hoisted__U32_2232;
    __builtin_unreachable();
}


OwnType *OwnType_Own() {
    OwnType *r = malloc(sizeof(OwnType));
    *r = (OwnType){ .tag = OwnType_TAG_Own };
    return r;
}
OwnType *OwnType_Ref() {
    OwnType *r = malloc(sizeof(OwnType));
    *r = (OwnType){ .tag = OwnType_TAG_Ref };
    return r;
}
OwnType *OwnType_Shallow() {
    OwnType *r = malloc(sizeof(OwnType));
    *r = (OwnType){ .tag = OwnType_TAG_Shallow };
    return r;
}
Bool OwnType_eq(OwnType * self, OwnType * other) {
    U32 hoisted__U32_2233 = 1;
    (void)hoisted__U32_2233;
    Bool hoisted__Bool_2234 = ((Bool)((((OwnType *)(self))->tag) == (((OwnType *)(other))->tag)));
    (void)hoisted__Bool_2234;
    return hoisted__Bool_2234;
    __builtin_unreachable();
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2242 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2242;
    if (hoisted__Bool_2242) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
        return _r; }
    }
    Bool hoisted__Bool_2243 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2243;
    if (hoisted__Bool_2243) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
        return _r; }
    }
    Bool hoisted__Bool_2244 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2244;
    if (hoisted__Bool_2244) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
        return _r; }
    }
    static Str hoisted__Str_2245 = (Str){.c_str = (void *)"OwnType.clone:108:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2245;
    UNREACHABLE(&hoisted__Str_2245);
    Str_delete(&hoisted__Str_2245, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
    __builtin_unreachable();
}

USize OwnType_size(void) {
    U32 hoisted__U32_2246 = 1;
    (void)hoisted__U32_2246;
    return hoisted__U32_2246;
    __builtin_unreachable();
}


GcStorage *GcStorage_Unset() {
    GcStorage *r = malloc(sizeof(GcStorage));
    *r = (GcStorage){ .tag = GcStorage_TAG_Unset };
    return r;
}
GcStorage *GcStorage_Stack() {
    GcStorage *r = malloc(sizeof(GcStorage));
    *r = (GcStorage){ .tag = GcStorage_TAG_Stack };
    return r;
}
GcStorage *GcStorage_HeapBox() {
    GcStorage *r = malloc(sizeof(GcStorage));
    *r = (GcStorage){ .tag = GcStorage_TAG_HeapBox };
    return r;
}
Bool GcStorage_eq(GcStorage * self, GcStorage * other) {
    U32 hoisted__U32_2247 = 1;
    (void)hoisted__U32_2247;
    Bool hoisted__Bool_2248 = ((Bool)((((GcStorage *)(self))->tag) == (((GcStorage *)(other))->tag)));
    (void)hoisted__Bool_2248;
    return hoisted__Bool_2248;
    __builtin_unreachable();
}

void GcStorage_delete(GcStorage * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

GcStorage * GcStorage_clone(GcStorage * self) {
    Bool hoisted__Bool_2256 = GcStorage_eq(self, &(GcStorage){.tag = GcStorage_TAG_Unset});
    (void)hoisted__Bool_2256;
    if (hoisted__Bool_2256) {
        { GcStorage *_r = malloc(sizeof(GcStorage)); _r->tag = GcStorage_TAG_Unset;
        return _r; }
    }
    Bool hoisted__Bool_2257 = GcStorage_eq(self, &(GcStorage){.tag = GcStorage_TAG_Stack});
    (void)hoisted__Bool_2257;
    if (hoisted__Bool_2257) {
        { GcStorage *_r = malloc(sizeof(GcStorage)); _r->tag = GcStorage_TAG_Stack;
        return _r; }
    }
    Bool hoisted__Bool_2258 = GcStorage_eq(self, &(GcStorage){.tag = GcStorage_TAG_HeapBox});
    (void)hoisted__Bool_2258;
    if (hoisted__Bool_2258) {
        { GcStorage *_r = malloc(sizeof(GcStorage)); _r->tag = GcStorage_TAG_HeapBox;
        return _r; }
    }
    static Str hoisted__Str_2259 = (Str){.c_str = (void *)"GcStorage.clone:119:1", .count = 21ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2259;
    UNREACHABLE(&hoisted__Str_2259);
    Str_delete(&hoisted__Str_2259, (Bool){0});
    { GcStorage *_r = malloc(sizeof(GcStorage)); _r->tag = GcStorage_TAG_Unset;
    return _r; }
    __builtin_unreachable();
}

USize GcStorage_size(void) {
    U32 hoisted__U32_2260 = 1;
    (void)hoisted__U32_2260;
    return hoisted__U32_2260;
    __builtin_unreachable();
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2262 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2262;
    Declaration *hoisted__Declaration_2263 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2263->name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2263->doc = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2263->explicit_type = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    hoisted__Declaration_2263->is_mut = self->is_mut;
    hoisted__Declaration_2263->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2263->is_priv = self->is_priv;
    hoisted__Declaration_2263->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2263->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2263->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2263->default_value = hoisted__Expr_2262;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2263->orig_name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    { GcStorage *_ca = GcStorage_clone(&self->gc_storage); hoisted__Declaration_2263->gc_storage = *_ca; free(_ca); }
    (void)hoisted__Declaration_2263;
    return hoisted__Declaration_2263;
    __builtin_unreachable();
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2265 = 0;
    (void)hoisted__Bool_2265;
    Str_delete(&self->name, hoisted__Bool_2265);
    Bool hoisted__Bool_2266 = 0;
    (void)hoisted__Bool_2266;
    Str_delete(&self->doc, hoisted__Bool_2266);
    Bool hoisted__Bool_2267 = 0;
    (void)hoisted__Bool_2267;
    Str_delete(&self->explicit_type, hoisted__Bool_2267);
    Bool hoisted__Bool_2268 = 0;
    (void)hoisted__Bool_2268;
    Bool_delete(&self->is_mut, hoisted__Bool_2268);
    Bool hoisted__Bool_2269 = 0;
    (void)hoisted__Bool_2269;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2269);
    Bool hoisted__Bool_2270 = 0;
    (void)hoisted__Bool_2270;
    Bool_delete(&self->is_priv, hoisted__Bool_2270);
    Bool hoisted__Bool_2271 = 0;
    (void)hoisted__Bool_2271;
    Bool_delete(&self->used, hoisted__Bool_2271);
    Bool hoisted__Bool_2272 = 0;
    (void)hoisted__Bool_2272;
    OwnType_delete(&self->own_type, hoisted__Bool_2272);
    Bool hoisted__Bool_2273 = 0;
    (void)hoisted__Bool_2273;
    Type_delete(&self->til_type, hoisted__Bool_2273);
    Bool hoisted__Bool_2274 = ((Bool)((UPtr)(self->default_value) == 0));
    (void)hoisted__Bool_2274;
    Bool hoisted__Bool_2275 = ((Bool)(!(hoisted__Bool_2274)));
    (void)hoisted__Bool_2275;
    if (hoisted__Bool_2275) {
        Bool hoisted__Bool_2264 = 1;
        (void)hoisted__Bool_2264;
        Expr_delete(self->default_value, hoisted__Bool_2264);
    }
    Bool hoisted__Bool_2276 = 0;
    (void)hoisted__Bool_2276;
    Str_delete(&self->orig_name, hoisted__Bool_2276);
    Bool hoisted__Bool_2277 = 0;
    (void)hoisted__Bool_2277;
    GcStorage_delete(&self->gc_storage, hoisted__Bool_2277);
    if (call_free) {
        free(self);
    }
}

USize Declaration_size(void) {
    U32 hoisted__U32_2278 = 112;
    (void)hoisted__U32_2278;
    return hoisted__U32_2278;
    __builtin_unreachable();
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2280 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2280->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2280->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2280->return_type = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2280->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2280->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2280->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2280->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2280->return_shallow_explicit = self->return_shallow_explicit;
    hoisted__FunctionDef_2280->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2280->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2280->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2280->closure_name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    hoisted__FunctionDef_2280->noreturn = self->noreturn;
    (void)hoisted__FunctionDef_2280;
    return hoisted__FunctionDef_2280;
    __builtin_unreachable();
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2281 = 0;
    (void)hoisted__Bool_2281;
    FuncType_delete(&self->func_type, hoisted__Bool_2281);
    Bool hoisted__Bool_2282 = 0;
    (void)hoisted__Bool_2282;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2282);
    Bool hoisted__Bool_2283 = 0;
    (void)hoisted__Bool_2283;
    Str_delete(&self->return_type, hoisted__Bool_2283);
    Bool hoisted__Bool_2284 = 0;
    (void)hoisted__Bool_2284;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2284);
    Bool hoisted__Bool_2285 = 0;
    (void)hoisted__Bool_2285;
    I32_delete(&self->variadic_index, hoisted__Bool_2285);
    Bool hoisted__Bool_2286 = 0;
    (void)hoisted__Bool_2286;
    I32_delete(&self->kwargs_index, hoisted__Bool_2286);
    Bool hoisted__Bool_2287 = 0;
    (void)hoisted__Bool_2287;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2287);
    Bool hoisted__Bool_2288 = 0;
    (void)hoisted__Bool_2288;
    Bool_delete(&self->return_shallow_explicit, hoisted__Bool_2288);
    Bool hoisted__Bool_2289 = 0;
    (void)hoisted__Bool_2289;
    Bool_delete(&self->auto_generated, hoisted__Bool_2289);
    Bool hoisted__Bool_2290 = 0;
    (void)hoisted__Bool_2290;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2290);
    Bool hoisted__Bool_2291 = 0;
    (void)hoisted__Bool_2291;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2291);
    Bool hoisted__Bool_2292 = 0;
    (void)hoisted__Bool_2292;
    Str_delete(&self->closure_name, hoisted__Bool_2292);
    Bool hoisted__Bool_2293 = 0;
    (void)hoisted__Bool_2293;
    Bool_delete(&self->noreturn, hoisted__Bool_2293);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2294 = 0;
    (void)hoisted__U32_2294;
    U64 hoisted__U64_2295 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2294); });
    (void)hoisted__U64_2295;
    return hoisted__U64_2295;
    __builtin_unreachable();
}

USize FunctionDef_size(void) {
    U32 hoisted__U32_2296 = 112;
    (void)hoisted__U32_2296;
    return hoisted__U32_2296;
    __builtin_unreachable();
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2299 = malloc(sizeof(FCallData));
    hoisted__FCallData_2299->is_splat = self->is_splat;
    hoisted__FCallData_2299->does_throw = self->does_throw;
    hoisted__FCallData_2299->is_bang = self->is_bang;
    hoisted__FCallData_2299->own_args = self->own_args;
    hoisted__FCallData_2299->keep_outer_args = self->keep_outer_args;
    hoisted__FCallData_2299->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2299->til_type = *_ca; free(_ca); }
    hoisted__FCallData_2299->noreturn_call = self->noreturn_call;
    hoisted__FCallData_2299->ref_args = self->ref_args;
    (void)hoisted__FCallData_2299;
    return hoisted__FCallData_2299;
    __builtin_unreachable();
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2300 = 0;
    (void)hoisted__Bool_2300;
    Bool_delete(&self->is_splat, hoisted__Bool_2300);
    Bool hoisted__Bool_2301 = 0;
    (void)hoisted__Bool_2301;
    Bool_delete(&self->does_throw, hoisted__Bool_2301);
    Bool hoisted__Bool_2302 = 0;
    (void)hoisted__Bool_2302;
    Bool_delete(&self->is_bang, hoisted__Bool_2302);
    Bool hoisted__Bool_2303 = 0;
    (void)hoisted__Bool_2303;
    U64_delete(&self->own_args, hoisted__Bool_2303);
    Bool hoisted__Bool_2304 = 0;
    (void)hoisted__Bool_2304;
    U64_delete(&self->keep_outer_args, hoisted__Bool_2304);
    Bool hoisted__Bool_2305 = 0;
    (void)hoisted__Bool_2305;
    Bool_delete(&self->swap_replace, hoisted__Bool_2305);
    Bool hoisted__Bool_2306 = 0;
    (void)hoisted__Bool_2306;
    Type_delete(&self->til_type, hoisted__Bool_2306);
    Bool hoisted__Bool_2307 = 0;
    (void)hoisted__Bool_2307;
    Bool_delete(&self->noreturn_call, hoisted__Bool_2307);
    Bool hoisted__Bool_2308 = 0;
    (void)hoisted__Bool_2308;
    U64_delete(&self->ref_args, hoisted__Bool_2308);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2309 = 0;
    (void)hoisted__U32_2309;
    U64 hoisted__U64_2310 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2309); });
    (void)hoisted__U64_2310;
    return hoisted__U64_2310;
    __builtin_unreachable();
}

USize FCallData_size(void) {
    U32 hoisted__U32_2311 = 72;
    (void)hoisted__U32_2311;
    return hoisted__U32_2311;
    __builtin_unreachable();
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2324 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2324->text = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2324->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2324;
    return hoisted__LiteralNumData_2324;
    __builtin_unreachable();
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2325 = 0;
    (void)hoisted__Bool_2325;
    Str_delete(&self->text, hoisted__Bool_2325);
    Bool hoisted__Bool_2326 = 0;
    (void)hoisted__Bool_2326;
    Type_delete(&self->til_type, hoisted__Bool_2326);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2327 = 0;
    (void)hoisted__U32_2327;
    U64 hoisted__U64_2328 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2327); });
    (void)hoisted__U64_2328;
    return hoisted__U64_2328;
    __builtin_unreachable();
}

USize LiteralNumData_size(void) {
    U32 hoisted__U32_2329 = 40;
    (void)hoisted__U32_2329;
    return hoisted__U32_2329;
    __builtin_unreachable();
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2339 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2339->name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2339->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2339;
    return hoisted__IdentData_2339;
    __builtin_unreachable();
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2340 = 0;
    (void)hoisted__Bool_2340;
    Str_delete(&self->name, hoisted__Bool_2340);
    Bool hoisted__Bool_2341 = 0;
    (void)hoisted__Bool_2341;
    Type_delete(&self->til_type, hoisted__Bool_2341);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2342 = 0;
    (void)hoisted__U32_2342;
    U64 hoisted__U64_2343 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2342); });
    (void)hoisted__U64_2343;
    return hoisted__U64_2343;
    __builtin_unreachable();
}

USize IdentData_size(void) {
    U32 hoisted__U32_2344 = 40;
    (void)hoisted__U32_2344;
    return hoisted__U32_2344;
    __builtin_unreachable();
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2350 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2350->name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2350->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2350;
    return hoisted__FieldAccessData_2350;
    __builtin_unreachable();
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2351 = 0;
    (void)hoisted__Bool_2351;
    Str_delete(&self->name, hoisted__Bool_2351);
    Bool hoisted__Bool_2352 = 0;
    (void)hoisted__Bool_2352;
    Type_delete(&self->til_type, hoisted__Bool_2352);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2353 = 0;
    (void)hoisted__U32_2353;
    U64 hoisted__U64_2354 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2353); });
    (void)hoisted__U64_2354;
    return hoisted__U64_2354;
    __builtin_unreachable();
}

USize FieldAccessData_size(void) {
    U32 hoisted__U32_2355 = 40;
    (void)hoisted__U32_2355;
    return hoisted__U32_2355;
    __builtin_unreachable();
}

StructDef * StructDef_clone(StructDef * self) {
    Vec__Declaration *hoisted__Vec__Declaration_2366 = Vec__Declaration_clone(self->fields);
    (void)hoisted__Vec__Declaration_2366;
    Vec__Declaration *hoisted__Vec__Declaration_2367 = Vec__Declaration_clone(self->ns_decls);
    (void)hoisted__Vec__Declaration_2367;
    Map__Str_USize *hoisted__Map__Str_USize_2368 = Map__Str_USize_clone(self->fields_index);
    (void)hoisted__Map__Str_USize_2368;
    Map__Str_USize *hoisted__Map__Str_USize_2369 = Map__Str_USize_clone(self->ns_index);
    (void)hoisted__Map__Str_USize_2369;
    StructDef *hoisted__StructDef_2370 = malloc(sizeof(StructDef));
    hoisted__StructDef_2370->fields = hoisted__Vec__Declaration_2366;
    hoisted__StructDef_2370->ns_decls = hoisted__Vec__Declaration_2367;
    hoisted__StructDef_2370->fields_index = hoisted__Map__Str_USize_2368;
    hoisted__StructDef_2370->ns_index = hoisted__Map__Str_USize_2369;
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2370->c_tag = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    hoisted__StructDef_2370->is_interface = self->is_interface;
    hoisted__StructDef_2370->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2370->implements_name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    (void)hoisted__StructDef_2370;
    return hoisted__StructDef_2370;
    __builtin_unreachable();
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2375 = ((Bool)((UPtr)(self->fields) == 0));
    (void)hoisted__Bool_2375;
    Bool hoisted__Bool_2376 = ((Bool)(!(hoisted__Bool_2375)));
    (void)hoisted__Bool_2376;
    if (hoisted__Bool_2376) {
        Bool hoisted__Bool_2371 = 1;
        (void)hoisted__Bool_2371;
        Vec__Declaration_delete(self->fields, hoisted__Bool_2371);
    }
    Bool hoisted__Bool_2377 = ((Bool)((UPtr)(self->ns_decls) == 0));
    (void)hoisted__Bool_2377;
    Bool hoisted__Bool_2378 = ((Bool)(!(hoisted__Bool_2377)));
    (void)hoisted__Bool_2378;
    if (hoisted__Bool_2378) {
        Bool hoisted__Bool_2372 = 1;
        (void)hoisted__Bool_2372;
        Vec__Declaration_delete(self->ns_decls, hoisted__Bool_2372);
    }
    Bool hoisted__Bool_2379 = ((Bool)((UPtr)(self->fields_index) == 0));
    (void)hoisted__Bool_2379;
    Bool hoisted__Bool_2380 = ((Bool)(!(hoisted__Bool_2379)));
    (void)hoisted__Bool_2380;
    if (hoisted__Bool_2380) {
        Bool hoisted__Bool_2373 = 1;
        (void)hoisted__Bool_2373;
        Map__Str_USize_delete(self->fields_index, hoisted__Bool_2373);
    }
    Bool hoisted__Bool_2381 = ((Bool)((UPtr)(self->ns_index) == 0));
    (void)hoisted__Bool_2381;
    Bool hoisted__Bool_2382 = ((Bool)(!(hoisted__Bool_2381)));
    (void)hoisted__Bool_2382;
    if (hoisted__Bool_2382) {
        Bool hoisted__Bool_2374 = 1;
        (void)hoisted__Bool_2374;
        Map__Str_USize_delete(self->ns_index, hoisted__Bool_2374);
    }
    Bool hoisted__Bool_2383 = 0;
    (void)hoisted__Bool_2383;
    Str_delete(&self->c_tag, hoisted__Bool_2383);
    Bool hoisted__Bool_2384 = 0;
    (void)hoisted__Bool_2384;
    Bool_delete(&self->is_interface, hoisted__Bool_2384);
    Bool hoisted__Bool_2385 = 0;
    (void)hoisted__Bool_2385;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2385);
    Bool hoisted__Bool_2386 = 0;
    (void)hoisted__Bool_2386;
    Str_delete(&self->implements_name, hoisted__Bool_2386);
    if (call_free) {
        free(self);
    }
}

USize StructDef_size(void) {
    U32 hoisted__U32_2387 = 72;
    (void)hoisted__U32_2387;
    return hoisted__U32_2387;
    __builtin_unreachable();
}

VariantDef * VariantDef_clone(VariantDef * self) {
    VariantDef *hoisted__VariantDef_2399 = malloc(sizeof(VariantDef));
    { Str *_ca = Str_clone(&self->name); hoisted__VariantDef_2399->name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    { Str *_ca = Str_clone(&self->doc); hoisted__VariantDef_2399->doc = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    { Str *_ca = Str_clone(&self->payload_type); hoisted__VariantDef_2399->payload_type = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    hoisted__VariantDef_2399->payload_const = self->payload_const;
    hoisted__VariantDef_2399->tag_value = self->tag_value;
    hoisted__VariantDef_2399->payload_ref = self->payload_ref;
    (void)hoisted__VariantDef_2399;
    return hoisted__VariantDef_2399;
    __builtin_unreachable();
}

void VariantDef_delete(VariantDef * self, Bool call_free) {
    Bool hoisted__Bool_2400 = 0;
    (void)hoisted__Bool_2400;
    Str_delete(&self->name, hoisted__Bool_2400);
    Bool hoisted__Bool_2401 = 0;
    (void)hoisted__Bool_2401;
    Str_delete(&self->doc, hoisted__Bool_2401);
    Bool hoisted__Bool_2402 = 0;
    (void)hoisted__Bool_2402;
    Str_delete(&self->payload_type, hoisted__Bool_2402);
    Bool hoisted__Bool_2403 = 0;
    (void)hoisted__Bool_2403;
    Bool_delete(&self->payload_const, hoisted__Bool_2403);
    Bool hoisted__Bool_2404 = 0;
    (void)hoisted__Bool_2404;
    I64_delete(&self->tag_value, hoisted__Bool_2404);
    Bool hoisted__Bool_2405 = 0;
    (void)hoisted__Bool_2405;
    Bool_delete(&self->payload_ref, hoisted__Bool_2405);
    if (call_free) {
        free(self);
    }
}

U64 VariantDef_hash(VariantDef * self, HashFn hasher) {
    U32 hoisted__U32_2406 = 0;
    (void)hoisted__U32_2406;
    U64 hoisted__U64_2407 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, VariantDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2406); });
    (void)hoisted__U64_2407;
    return hoisted__U64_2407;
    __builtin_unreachable();
}

USize VariantDef_size(void) {
    U32 hoisted__U32_2408 = 72;
    (void)hoisted__U32_2408;
    return hoisted__U32_2408;
    __builtin_unreachable();
}

EnumDef * EnumDef_clone(EnumDef * self) {
    Vec__Declaration *hoisted__Vec__Declaration_2416 = Vec__Declaration_clone(self->ns_decls);
    (void)hoisted__Vec__Declaration_2416;
    Map__Str_USize *hoisted__Map__Str_USize_2417 = Map__Str_USize_clone(self->ns_index);
    (void)hoisted__Map__Str_USize_2417;
    EnumDef *hoisted__EnumDef_2418 = malloc(sizeof(EnumDef));
    hoisted__EnumDef_2418->ns_decls = hoisted__Vec__Declaration_2416;
    hoisted__EnumDef_2418->ns_index = hoisted__Map__Str_USize_2417;
    { Vec__VariantDef *_ca = Vec__VariantDef_clone(&self->variants); hoisted__EnumDef_2418->variants = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2418->implements_name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    { Str *_ca = Str_clone(&self->tag_type); hoisted__EnumDef_2418->tag_type = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    (void)hoisted__EnumDef_2418;
    return hoisted__EnumDef_2418;
    __builtin_unreachable();
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2421 = ((Bool)((UPtr)(self->ns_decls) == 0));
    (void)hoisted__Bool_2421;
    Bool hoisted__Bool_2422 = ((Bool)(!(hoisted__Bool_2421)));
    (void)hoisted__Bool_2422;
    if (hoisted__Bool_2422) {
        Bool hoisted__Bool_2419 = 1;
        (void)hoisted__Bool_2419;
        Vec__Declaration_delete(self->ns_decls, hoisted__Bool_2419);
    }
    Bool hoisted__Bool_2423 = ((Bool)((UPtr)(self->ns_index) == 0));
    (void)hoisted__Bool_2423;
    Bool hoisted__Bool_2424 = ((Bool)(!(hoisted__Bool_2423)));
    (void)hoisted__Bool_2424;
    if (hoisted__Bool_2424) {
        Bool hoisted__Bool_2420 = 1;
        (void)hoisted__Bool_2420;
        Map__Str_USize_delete(self->ns_index, hoisted__Bool_2420);
    }
    Bool hoisted__Bool_2425 = 0;
    (void)hoisted__Bool_2425;
    Vec__VariantDef_delete(&self->variants, hoisted__Bool_2425);
    Bool hoisted__Bool_2426 = 0;
    (void)hoisted__Bool_2426;
    Str_delete(&self->implements_name, hoisted__Bool_2426);
    Bool hoisted__Bool_2427 = 0;
    (void)hoisted__Bool_2427;
    Str_delete(&self->tag_type, hoisted__Bool_2427);
    if (call_free) {
        free(self);
    }
}

USize EnumDef_size(void) {
    U32 hoisted__U32_2428 = 64;
    (void)hoisted__U32_2428;
    return hoisted__U32_2428;
    __builtin_unreachable();
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2459 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2459->name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    hoisted__AssignData_2459->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2459->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2459->swap_replace = self->swap_replace;
    hoisted__AssignData_2459->is_move = self->is_move;
    (void)hoisted__AssignData_2459;
    return hoisted__AssignData_2459;
    __builtin_unreachable();
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2460 = 0;
    (void)hoisted__Bool_2460;
    Str_delete(&self->name, hoisted__Bool_2460);
    Bool hoisted__Bool_2461 = 0;
    (void)hoisted__Bool_2461;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2461);
    Bool hoisted__Bool_2462 = 0;
    (void)hoisted__Bool_2462;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2462);
    Bool hoisted__Bool_2463 = 0;
    (void)hoisted__Bool_2463;
    Bool_delete(&self->swap_replace, hoisted__Bool_2463);
    Bool hoisted__Bool_2464 = 0;
    (void)hoisted__Bool_2464;
    Bool_delete(&self->is_move, hoisted__Bool_2464);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_2465 = 0;
    (void)hoisted__U32_2465;
    U64 hoisted__U64_2466 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2465); });
    (void)hoisted__U64_2466;
    return hoisted__U64_2466;
    __builtin_unreachable();
}

USize AssignData_size(void) {
    U32 hoisted__U32_2467 = 24;
    (void)hoisted__U32_2467;
    return hoisted__U32_2467;
    __builtin_unreachable();
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_2469 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_2469->name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    hoisted__FieldAssignData_2469->save_old_delete = self->save_old_delete;
    hoisted__FieldAssignData_2469->transfers_own = self->transfers_own;
    hoisted__FieldAssignData_2469->is_move = self->is_move;
    (void)hoisted__FieldAssignData_2469;
    return hoisted__FieldAssignData_2469;
    __builtin_unreachable();
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_2470 = 0;
    (void)hoisted__Bool_2470;
    Str_delete(&self->name, hoisted__Bool_2470);
    Bool hoisted__Bool_2471 = 0;
    (void)hoisted__Bool_2471;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2471);
    Bool hoisted__Bool_2472 = 0;
    (void)hoisted__Bool_2472;
    Bool_delete(&self->transfers_own, hoisted__Bool_2472);
    Bool hoisted__Bool_2473 = 0;
    (void)hoisted__Bool_2473;
    Bool_delete(&self->is_move, hoisted__Bool_2473);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_2474 = 0;
    (void)hoisted__U32_2474;
    U64 hoisted__U64_2475 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2474); });
    (void)hoisted__U64_2475;
    return hoisted__U64_2475;
    __builtin_unreachable();
}

USize FieldAssignData_size(void) {
    U32 hoisted__U32_2476 = 24;
    (void)hoisted__U32_2476;
    return hoisted__U32_2476;
    __builtin_unreachable();
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_2478 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_2478->name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    hoisted__ForInData_2478->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_2478->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->name2); hoisted__ForInData_2478->name2 = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    hoisted__ForInData_2478->is_mut2 = self->is_mut2;
    (void)hoisted__ForInData_2478;
    return hoisted__ForInData_2478;
    __builtin_unreachable();
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_2479 = 0;
    (void)hoisted__Bool_2479;
    Str_delete(&self->name, hoisted__Bool_2479);
    Bool hoisted__Bool_2480 = 0;
    (void)hoisted__Bool_2480;
    Bool_delete(&self->is_mut, hoisted__Bool_2480);
    Bool hoisted__Bool_2481 = 0;
    (void)hoisted__Bool_2481;
    Type_delete(&self->til_type, hoisted__Bool_2481);
    Bool hoisted__Bool_2482 = 0;
    (void)hoisted__Bool_2482;
    Str_delete(&self->name2, hoisted__Bool_2482);
    Bool hoisted__Bool_2483 = 0;
    (void)hoisted__Bool_2483;
    Bool_delete(&self->is_mut2, hoisted__Bool_2483);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_2484 = 0;
    (void)hoisted__U32_2484;
    U64 hoisted__U64_2485 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2484); });
    (void)hoisted__U64_2485;
    return hoisted__U64_2485;
    __builtin_unreachable();
}

USize ForInData_size(void) {
    U32 hoisted__U32_2486 = 72;
    (void)hoisted__U32_2486;
    return hoisted__U32_2486;
    __builtin_unreachable();
}

Literal *Literal_Str(Str * val) {
    Literal *r = malloc(sizeof(Literal));
    r->tag = Literal_TAG_Str;
    r->data.Str = *val;
    if (val->cap != TIL_CAP_LIT) { free(val); }
    return r;
}
Literal *Literal_Num(LiteralNumData * val) {
    Literal *r = malloc(sizeof(Literal));
    r->tag = Literal_TAG_Num;
    r->data.Num = *val;
    free(val);
    return r;
}
Literal *Literal_Bool(Bool * val) {
    Literal *r = malloc(sizeof(Literal));
    r->tag = Literal_TAG_Bool;
    r->data.Bool = *val;
    return r;
}
Literal *Literal_Null() {
    Literal *r = malloc(sizeof(Literal));
    r->tag = Literal_TAG_Null;
    return r;
}
Literal *Literal_MapLit() {
    Literal *r = malloc(sizeof(Literal));
    r->tag = Literal_TAG_MapLit;
    return r;
}
Literal *Literal_SetLit() {
    Literal *r = malloc(sizeof(Literal));
    r->tag = Literal_TAG_SetLit;
    return r;
}
void Literal_delete(Literal * self, Bool call_free) {
    U32 hoisted__U32_2527 = 1;
    (void)hoisted__U32_2527;
    Bool hoisted__Bool_2528 = ((Bool)((((Literal *)(self))->tag) == (((Literal *)(&(Literal){.tag = Literal_TAG_Str}))->tag)));
    (void)hoisted__Bool_2528;
    if (hoisted__Bool_2528) {
        Str *hoisted__Str_2521 = ((void *)((U8 *)(self) + offsetof(Literal, data)));
        (void)hoisted__Str_2521;
        (void)hoisted__Str_2521;
        Bool hoisted__Bool_2522 = 0;
        (void)hoisted__Bool_2522;
        Str_delete(hoisted__Str_2521, hoisted__Bool_2522);
    }
    U32 hoisted__U32_2529 = 1;
    (void)hoisted__U32_2529;
    Bool hoisted__Bool_2530 = ((Bool)((((Literal *)(self))->tag) == (((Literal *)(&(Literal){.tag = Literal_TAG_Num}))->tag)));
    (void)hoisted__Bool_2530;
    if (hoisted__Bool_2530) {
        LiteralNumData *hoisted__LiteralNumData_2523 = ((void *)((U8 *)(self) + offsetof(Literal, data)));
        (void)hoisted__LiteralNumData_2523;
        (void)hoisted__LiteralNumData_2523;
        Bool hoisted__Bool_2524 = 0;
        (void)hoisted__Bool_2524;
        LiteralNumData_delete(hoisted__LiteralNumData_2523, hoisted__Bool_2524);
    }
    U32 hoisted__U32_2531 = 1;
    (void)hoisted__U32_2531;
    Bool hoisted__Bool_2532 = ((Bool)((((Literal *)(self))->tag) == (((Literal *)(&(Literal){.tag = Literal_TAG_Bool}))->tag)));
    (void)hoisted__Bool_2532;
    if (hoisted__Bool_2532) {
        Bool *hoisted__Bool_2525 = ((void *)((U8 *)(self) + offsetof(Literal, data)));
        (void)hoisted__Bool_2525;
        (void)hoisted__Bool_2525;
        Bool hoisted__Bool_2526 = 0;
        (void)hoisted__Bool_2526;
        Bool_delete(hoisted__Bool_2525, hoisted__Bool_2526);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    U32 hoisted__U32_2578 = 1;
    (void)hoisted__U32_2578;
    Bool hoisted__Bool_2579 = ((Bool)((((Literal *)(self))->tag) == (((Literal *)(&(Literal){.tag = Literal_TAG_Str}))->tag)));
    (void)hoisted__Bool_2579;
    if (hoisted__Bool_2579) {
        Str *_clone_payload_Str_0 = ((void *)((U8 *)(self) + offsetof(Literal, data)));
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_2573 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_2573;
        Literal *hoisted__Literal_2574 = Literal_Str(hoisted__Str_2573);
        (void)hoisted__Literal_2574;
        return hoisted__Literal_2574;
    }
    U32 hoisted__U32_2580 = 1;
    (void)hoisted__U32_2580;
    Bool hoisted__Bool_2581 = ((Bool)((((Literal *)(self))->tag) == (((Literal *)(&(Literal){.tag = Literal_TAG_Num}))->tag)));
    (void)hoisted__Bool_2581;
    if (hoisted__Bool_2581) {
        LiteralNumData *_clone_payload_Num_1 = ((void *)((U8 *)(self) + offsetof(Literal, data)));
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_2575 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_2575;
        Literal *hoisted__Literal_2576 = Literal_Num(hoisted__LiteralNumData_2575);
        (void)hoisted__Literal_2576;
        return hoisted__Literal_2576;
    }
    U32 hoisted__U32_2582 = 1;
    (void)hoisted__U32_2582;
    Bool hoisted__Bool_2583 = ((Bool)((((Literal *)(self))->tag) == (((Literal *)(&(Literal){.tag = Literal_TAG_Bool}))->tag)));
    (void)hoisted__Bool_2583;
    if (hoisted__Bool_2583) {
        Bool *_clone_payload_Bool_2 = ((void *)((U8 *)(self) + offsetof(Literal, data)));
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_2577 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_2577;
        return hoisted__Literal_2577;
    }
    U32 hoisted__U32_2584 = 1;
    (void)hoisted__U32_2584;
    Bool hoisted__Bool_2585 = ((Bool)((((Literal *)(self))->tag) == (((Literal *)(&(Literal){.tag = Literal_TAG_Null}))->tag)));
    (void)hoisted__Bool_2585;
    if (hoisted__Bool_2585) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
        return _r; }
    }
    U32 hoisted__U32_2586 = 1;
    (void)hoisted__U32_2586;
    Bool hoisted__Bool_2587 = ((Bool)((((Literal *)(self))->tag) == (((Literal *)(&(Literal){.tag = Literal_TAG_MapLit}))->tag)));
    (void)hoisted__Bool_2587;
    if (hoisted__Bool_2587) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
        return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
    __builtin_unreachable();
}

USize Literal_size(void) {
    U32 hoisted__U32_2588 = 48;
    (void)hoisted__U32_2588;
    return hoisted__U32_2588;
    __builtin_unreachable();
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_2591 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_2591->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_2591->result_temp = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    (void)hoisted__MatchData_2591;
    return hoisted__MatchData_2591;
    __builtin_unreachable();
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_2592 = 0;
    (void)hoisted__Bool_2592;
    Type_delete(&self->til_type, hoisted__Bool_2592);
    Bool hoisted__Bool_2593 = 0;
    (void)hoisted__Bool_2593;
    Str_delete(&self->result_temp, hoisted__Bool_2593);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_2594 = 0;
    (void)hoisted__U32_2594;
    U64 hoisted__U64_2595 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2594); });
    (void)hoisted__U64_2595;
    return hoisted__U64_2595;
    __builtin_unreachable();
}

USize MatchData_size(void) {
    U32 hoisted__U32_2596 = 40;
    (void)hoisted__U32_2596;
    return hoisted__U32_2596;
    __builtin_unreachable();
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_2601 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_2601->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__CaptureBlockData_2601->closure_name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    (void)hoisted__CaptureBlockData_2601;
    return hoisted__CaptureBlockData_2601;
    __builtin_unreachable();
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_2602 = 0;
    (void)hoisted__Bool_2602;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2602);
    Bool hoisted__Bool_2603 = 0;
    (void)hoisted__Bool_2603;
    Str_delete(&self->closure_name, hoisted__Bool_2603);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_2604 = 0;
    (void)hoisted__U32_2604;
    U64 hoisted__U64_2605 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2604); });
    (void)hoisted__U64_2605;
    return hoisted__U64_2605;
    __builtin_unreachable();
}

USize CaptureBlockData_size(void) {
    U32 hoisted__U32_2606 = 32;
    (void)hoisted__U32_2606;
    return hoisted__U32_2606;
    __builtin_unreachable();
}

NodeType *NodeType_Body() {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_Body;
    return r;
}
NodeType *NodeType_Literal(Literal * val) {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_Literal;
    r->data.Literal = *val;
    free(val);
    return r;
}
NodeType *NodeType_Ident(IdentData * val) {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_Ident;
    r->data.Ident = *val;
    free(val);
    return r;
}
NodeType *NodeType_Decl(Declaration * val) {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_Decl;
    r->data.Decl = *val;
    free(val);
    return r;
}
NodeType *NodeType_Assign(AssignData * val) {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_Assign;
    r->data.Assign = *val;
    free(val);
    return r;
}
NodeType *NodeType_FCall(FCallData * val) {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_FCall;
    r->data.FCall = *val;
    free(val);
    return r;
}
NodeType *NodeType_FuncDef(FunctionDef * val) {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_FuncDef;
    r->data.FuncDef = *val;
    free(val);
    return r;
}
NodeType *NodeType_StructDef(StructDef * val) {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_StructDef;
    r->data.StructDef = *val;
    free(val);
    return r;
}
NodeType *NodeType_EnumDef(EnumDef * val) {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_EnumDef;
    r->data.EnumDef = *val;
    free(val);
    return r;
}
NodeType *NodeType_FieldAccess(FieldAccessData * val) {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_FieldAccess;
    r->data.FieldAccess = *val;
    free(val);
    return r;
}
NodeType *NodeType_FieldAssign(FieldAssignData * val) {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_FieldAssign;
    r->data.FieldAssign = *val;
    free(val);
    return r;
}
NodeType *NodeType_Return() {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_Return;
    return r;
}
NodeType *NodeType_If() {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_If;
    return r;
}
NodeType *NodeType_While() {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_While;
    return r;
}
NodeType *NodeType_ForIn(ForInData * val) {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_ForIn;
    r->data.ForIn = *val;
    free(val);
    return r;
}
NodeType *NodeType_NamedArg(Str * val) {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_NamedArg;
    r->data.NamedArg = *val;
    if (val->cap != TIL_CAP_LIT) { free(val); }
    return r;
}
NodeType *NodeType_Break() {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_Break;
    return r;
}
NodeType *NodeType_Continue() {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_Continue;
    return r;
}
NodeType *NodeType_Switch() {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_Switch;
    return r;
}
NodeType *NodeType_Match(MatchData * val) {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_Match;
    r->data.Match = *val;
    free(val);
    return r;
}
NodeType *NodeType_Case() {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_Case;
    return r;
}
NodeType *NodeType_NoDefaultArg() {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_NoDefaultArg;
    return r;
}
NodeType *NodeType_Throw() {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_Throw;
    return r;
}
NodeType *NodeType_Catch() {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_Catch;
    return r;
}
NodeType *NodeType_RestPattern() {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_RestPattern;
    return r;
}
NodeType *NodeType_CaptureBlock(CaptureBlockData * val) {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_CaptureBlock;
    r->data.CaptureBlock = *val;
    free(val);
    return r;
}
NodeType *NodeType_Loc() {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_Loc;
    return r;
}
NodeType *NodeType_BodyValue(CaptureBlockData * val) {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_BodyValue;
    r->data.BodyValue = *val;
    free(val);
    return r;
}
NodeType *NodeType_ListPattern() {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_ListPattern;
    return r;
}
void NodeType_delete(NodeType * self, Bool call_free) {
    U32 hoisted__U32_3075 = 1;
    (void)hoisted__U32_3075;
    Bool hoisted__Bool_3076 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Literal}))->tag)));
    (void)hoisted__Bool_3076;
    if (hoisted__Bool_3076) {
        Literal *hoisted__Literal_3045 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__Literal_3045;
        (void)hoisted__Literal_3045;
        Bool hoisted__Bool_3046 = 0;
        (void)hoisted__Bool_3046;
        Literal_delete(hoisted__Literal_3045, hoisted__Bool_3046);
    }
    U32 hoisted__U32_3077 = 1;
    (void)hoisted__U32_3077;
    Bool hoisted__Bool_3078 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Ident}))->tag)));
    (void)hoisted__Bool_3078;
    if (hoisted__Bool_3078) {
        IdentData *hoisted__IdentData_3047 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__IdentData_3047;
        (void)hoisted__IdentData_3047;
        Bool hoisted__Bool_3048 = 0;
        (void)hoisted__Bool_3048;
        IdentData_delete(hoisted__IdentData_3047, hoisted__Bool_3048);
    }
    U32 hoisted__U32_3079 = 1;
    (void)hoisted__U32_3079;
    Bool hoisted__Bool_3080 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Decl}))->tag)));
    (void)hoisted__Bool_3080;
    if (hoisted__Bool_3080) {
        Declaration *hoisted__Declaration_3049 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__Declaration_3049;
        (void)hoisted__Declaration_3049;
        Bool hoisted__Bool_3050 = 0;
        (void)hoisted__Bool_3050;
        Declaration_delete(hoisted__Declaration_3049, hoisted__Bool_3050);
    }
    U32 hoisted__U32_3081 = 1;
    (void)hoisted__U32_3081;
    Bool hoisted__Bool_3082 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Assign}))->tag)));
    (void)hoisted__Bool_3082;
    if (hoisted__Bool_3082) {
        AssignData *hoisted__AssignData_3051 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__AssignData_3051;
        (void)hoisted__AssignData_3051;
        Bool hoisted__Bool_3052 = 0;
        (void)hoisted__Bool_3052;
        AssignData_delete(hoisted__AssignData_3051, hoisted__Bool_3052);
    }
    U32 hoisted__U32_3083 = 1;
    (void)hoisted__U32_3083;
    Bool hoisted__Bool_3084 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_FCall}))->tag)));
    (void)hoisted__Bool_3084;
    if (hoisted__Bool_3084) {
        FCallData *hoisted__FCallData_3053 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__FCallData_3053;
        (void)hoisted__FCallData_3053;
        Bool hoisted__Bool_3054 = 0;
        (void)hoisted__Bool_3054;
        FCallData_delete(hoisted__FCallData_3053, hoisted__Bool_3054);
    }
    U32 hoisted__U32_3085 = 1;
    (void)hoisted__U32_3085;
    Bool hoisted__Bool_3086 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_FuncDef}))->tag)));
    (void)hoisted__Bool_3086;
    if (hoisted__Bool_3086) {
        FunctionDef *hoisted__FunctionDef_3055 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__FunctionDef_3055;
        (void)hoisted__FunctionDef_3055;
        Bool hoisted__Bool_3056 = 0;
        (void)hoisted__Bool_3056;
        FunctionDef_delete(hoisted__FunctionDef_3055, hoisted__Bool_3056);
    }
    U32 hoisted__U32_3087 = 1;
    (void)hoisted__U32_3087;
    Bool hoisted__Bool_3088 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_StructDef}))->tag)));
    (void)hoisted__Bool_3088;
    if (hoisted__Bool_3088) {
        StructDef *hoisted__StructDef_3057 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__StructDef_3057;
        (void)hoisted__StructDef_3057;
        Bool hoisted__Bool_3058 = 0;
        (void)hoisted__Bool_3058;
        StructDef_delete(hoisted__StructDef_3057, hoisted__Bool_3058);
    }
    U32 hoisted__U32_3089 = 1;
    (void)hoisted__U32_3089;
    Bool hoisted__Bool_3090 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_EnumDef}))->tag)));
    (void)hoisted__Bool_3090;
    if (hoisted__Bool_3090) {
        EnumDef *hoisted__EnumDef_3059 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__EnumDef_3059;
        (void)hoisted__EnumDef_3059;
        Bool hoisted__Bool_3060 = 0;
        (void)hoisted__Bool_3060;
        EnumDef_delete(hoisted__EnumDef_3059, hoisted__Bool_3060);
    }
    U32 hoisted__U32_3091 = 1;
    (void)hoisted__U32_3091;
    Bool hoisted__Bool_3092 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAccess}))->tag)));
    (void)hoisted__Bool_3092;
    if (hoisted__Bool_3092) {
        FieldAccessData *hoisted__FieldAccessData_3061 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__FieldAccessData_3061;
        (void)hoisted__FieldAccessData_3061;
        Bool hoisted__Bool_3062 = 0;
        (void)hoisted__Bool_3062;
        FieldAccessData_delete(hoisted__FieldAccessData_3061, hoisted__Bool_3062);
    }
    U32 hoisted__U32_3093 = 1;
    (void)hoisted__U32_3093;
    Bool hoisted__Bool_3094 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAssign}))->tag)));
    (void)hoisted__Bool_3094;
    if (hoisted__Bool_3094) {
        FieldAssignData *hoisted__FieldAssignData_3063 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__FieldAssignData_3063;
        (void)hoisted__FieldAssignData_3063;
        Bool hoisted__Bool_3064 = 0;
        (void)hoisted__Bool_3064;
        FieldAssignData_delete(hoisted__FieldAssignData_3063, hoisted__Bool_3064);
    }
    U32 hoisted__U32_3095 = 1;
    (void)hoisted__U32_3095;
    Bool hoisted__Bool_3096 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_ForIn}))->tag)));
    (void)hoisted__Bool_3096;
    if (hoisted__Bool_3096) {
        ForInData *hoisted__ForInData_3065 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__ForInData_3065;
        (void)hoisted__ForInData_3065;
        Bool hoisted__Bool_3066 = 0;
        (void)hoisted__Bool_3066;
        ForInData_delete(hoisted__ForInData_3065, hoisted__Bool_3066);
    }
    U32 hoisted__U32_3097 = 1;
    (void)hoisted__U32_3097;
    Bool hoisted__Bool_3098 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_NamedArg}))->tag)));
    (void)hoisted__Bool_3098;
    if (hoisted__Bool_3098) {
        Str *hoisted__Str_3067 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__Str_3067;
        (void)hoisted__Str_3067;
        Bool hoisted__Bool_3068 = 0;
        (void)hoisted__Bool_3068;
        Str_delete(hoisted__Str_3067, hoisted__Bool_3068);
    }
    U32 hoisted__U32_3099 = 1;
    (void)hoisted__U32_3099;
    Bool hoisted__Bool_3100 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Match}))->tag)));
    (void)hoisted__Bool_3100;
    if (hoisted__Bool_3100) {
        MatchData *hoisted__MatchData_3069 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__MatchData_3069;
        (void)hoisted__MatchData_3069;
        Bool hoisted__Bool_3070 = 0;
        (void)hoisted__Bool_3070;
        MatchData_delete(hoisted__MatchData_3069, hoisted__Bool_3070);
    }
    U32 hoisted__U32_3101 = 1;
    (void)hoisted__U32_3101;
    Bool hoisted__Bool_3102 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_CaptureBlock}))->tag)));
    (void)hoisted__Bool_3102;
    if (hoisted__Bool_3102) {
        CaptureBlockData *hoisted__CaptureBlockData_3071 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__CaptureBlockData_3071;
        (void)hoisted__CaptureBlockData_3071;
        Bool hoisted__Bool_3072 = 0;
        (void)hoisted__Bool_3072;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3071, hoisted__Bool_3072);
    }
    U32 hoisted__U32_3103 = 1;
    (void)hoisted__U32_3103;
    Bool hoisted__Bool_3104 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_BodyValue}))->tag)));
    (void)hoisted__Bool_3104;
    if (hoisted__Bool_3104) {
        CaptureBlockData *hoisted__CaptureBlockData_3073 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__CaptureBlockData_3073;
        (void)hoisted__CaptureBlockData_3073;
        Bool hoisted__Bool_3074 = 0;
        (void)hoisted__Bool_3074;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3073, hoisted__Bool_3074);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    U32 hoisted__U32_3328 = 1;
    (void)hoisted__U32_3328;
    Bool hoisted__Bool_3329 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Body}))->tag)));
    (void)hoisted__Bool_3329;
    if (hoisted__Bool_3329) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
        return _r; }
    }
    U32 hoisted__U32_3330 = 1;
    (void)hoisted__U32_3330;
    Bool hoisted__Bool_3331 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Literal}))->tag)));
    (void)hoisted__Bool_3331;
    if (hoisted__Bool_3331) {
        Literal *_clone_payload_Literal_1 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3298 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3298;
        NodeType *hoisted__NodeType_3299 = NodeType_Literal(hoisted__Literal_3298);
        (void)hoisted__NodeType_3299;
        return hoisted__NodeType_3299;
    }
    U32 hoisted__U32_3332 = 1;
    (void)hoisted__U32_3332;
    Bool hoisted__Bool_3333 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Ident}))->tag)));
    (void)hoisted__Bool_3333;
    if (hoisted__Bool_3333) {
        IdentData *_clone_payload_Ident_2 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3300 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3300;
        NodeType *hoisted__NodeType_3301 = NodeType_Ident(hoisted__IdentData_3300);
        (void)hoisted__NodeType_3301;
        return hoisted__NodeType_3301;
    }
    U32 hoisted__U32_3334 = 1;
    (void)hoisted__U32_3334;
    Bool hoisted__Bool_3335 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Decl}))->tag)));
    (void)hoisted__Bool_3335;
    if (hoisted__Bool_3335) {
        Declaration *_clone_payload_Decl_3 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3302 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3302;
        NodeType *hoisted__NodeType_3303 = NodeType_Decl(hoisted__Declaration_3302);
        (void)hoisted__NodeType_3303;
        return hoisted__NodeType_3303;
    }
    U32 hoisted__U32_3336 = 1;
    (void)hoisted__U32_3336;
    Bool hoisted__Bool_3337 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Assign}))->tag)));
    (void)hoisted__Bool_3337;
    if (hoisted__Bool_3337) {
        AssignData *_clone_payload_Assign_4 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3304 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3304;
        NodeType *hoisted__NodeType_3305 = NodeType_Assign(hoisted__AssignData_3304);
        (void)hoisted__NodeType_3305;
        return hoisted__NodeType_3305;
    }
    U32 hoisted__U32_3338 = 1;
    (void)hoisted__U32_3338;
    Bool hoisted__Bool_3339 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_FCall}))->tag)));
    (void)hoisted__Bool_3339;
    if (hoisted__Bool_3339) {
        FCallData *_clone_payload_FCall_5 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3306 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3306;
        NodeType *hoisted__NodeType_3307 = NodeType_FCall(hoisted__FCallData_3306);
        (void)hoisted__NodeType_3307;
        return hoisted__NodeType_3307;
    }
    U32 hoisted__U32_3340 = 1;
    (void)hoisted__U32_3340;
    Bool hoisted__Bool_3341 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_FuncDef}))->tag)));
    (void)hoisted__Bool_3341;
    if (hoisted__Bool_3341) {
        FunctionDef *_clone_payload_FuncDef_6 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3308 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3308;
        NodeType *hoisted__NodeType_3309 = NodeType_FuncDef(hoisted__FunctionDef_3308);
        (void)hoisted__NodeType_3309;
        return hoisted__NodeType_3309;
    }
    U32 hoisted__U32_3342 = 1;
    (void)hoisted__U32_3342;
    Bool hoisted__Bool_3343 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_StructDef}))->tag)));
    (void)hoisted__Bool_3343;
    if (hoisted__Bool_3343) {
        StructDef *_clone_payload_StructDef_7 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3310 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3310;
        NodeType *hoisted__NodeType_3311 = NodeType_StructDef(hoisted__StructDef_3310);
        (void)hoisted__NodeType_3311;
        return hoisted__NodeType_3311;
    }
    U32 hoisted__U32_3344 = 1;
    (void)hoisted__U32_3344;
    Bool hoisted__Bool_3345 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_EnumDef}))->tag)));
    (void)hoisted__Bool_3345;
    if (hoisted__Bool_3345) {
        EnumDef *_clone_payload_EnumDef_8 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3312 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3312;
        NodeType *hoisted__NodeType_3313 = NodeType_EnumDef(hoisted__EnumDef_3312);
        (void)hoisted__NodeType_3313;
        return hoisted__NodeType_3313;
    }
    U32 hoisted__U32_3346 = 1;
    (void)hoisted__U32_3346;
    Bool hoisted__Bool_3347 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAccess}))->tag)));
    (void)hoisted__Bool_3347;
    if (hoisted__Bool_3347) {
        FieldAccessData *_clone_payload_FieldAccess_9 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3314 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3314;
        NodeType *hoisted__NodeType_3315 = NodeType_FieldAccess(hoisted__FieldAccessData_3314);
        (void)hoisted__NodeType_3315;
        return hoisted__NodeType_3315;
    }
    U32 hoisted__U32_3348 = 1;
    (void)hoisted__U32_3348;
    Bool hoisted__Bool_3349 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAssign}))->tag)));
    (void)hoisted__Bool_3349;
    if (hoisted__Bool_3349) {
        FieldAssignData *_clone_payload_FieldAssign_10 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3316 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3316;
        NodeType *hoisted__NodeType_3317 = NodeType_FieldAssign(hoisted__FieldAssignData_3316);
        (void)hoisted__NodeType_3317;
        return hoisted__NodeType_3317;
    }
    U32 hoisted__U32_3350 = 1;
    (void)hoisted__U32_3350;
    Bool hoisted__Bool_3351 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Return}))->tag)));
    (void)hoisted__Bool_3351;
    if (hoisted__Bool_3351) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
        return _r; }
    }
    U32 hoisted__U32_3352 = 1;
    (void)hoisted__U32_3352;
    Bool hoisted__Bool_3353 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_If}))->tag)));
    (void)hoisted__Bool_3353;
    if (hoisted__Bool_3353) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
        return _r; }
    }
    U32 hoisted__U32_3354 = 1;
    (void)hoisted__U32_3354;
    Bool hoisted__Bool_3355 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_While}))->tag)));
    (void)hoisted__Bool_3355;
    if (hoisted__Bool_3355) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
        return _r; }
    }
    U32 hoisted__U32_3356 = 1;
    (void)hoisted__U32_3356;
    Bool hoisted__Bool_3357 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_ForIn}))->tag)));
    (void)hoisted__Bool_3357;
    if (hoisted__Bool_3357) {
        ForInData *_clone_payload_ForIn_14 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3318 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3318;
        NodeType *hoisted__NodeType_3319 = NodeType_ForIn(hoisted__ForInData_3318);
        (void)hoisted__NodeType_3319;
        return hoisted__NodeType_3319;
    }
    U32 hoisted__U32_3358 = 1;
    (void)hoisted__U32_3358;
    Bool hoisted__Bool_3359 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_NamedArg}))->tag)));
    (void)hoisted__Bool_3359;
    if (hoisted__Bool_3359) {
        Str *_clone_payload_NamedArg_15 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3320 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3320;
        NodeType *hoisted__NodeType_3321 = NodeType_NamedArg(hoisted__Str_3320);
        (void)hoisted__NodeType_3321;
        return hoisted__NodeType_3321;
    }
    U32 hoisted__U32_3360 = 1;
    (void)hoisted__U32_3360;
    Bool hoisted__Bool_3361 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Break}))->tag)));
    (void)hoisted__Bool_3361;
    if (hoisted__Bool_3361) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
        return _r; }
    }
    U32 hoisted__U32_3362 = 1;
    (void)hoisted__U32_3362;
    Bool hoisted__Bool_3363 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Continue}))->tag)));
    (void)hoisted__Bool_3363;
    if (hoisted__Bool_3363) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
        return _r; }
    }
    U32 hoisted__U32_3364 = 1;
    (void)hoisted__U32_3364;
    Bool hoisted__Bool_3365 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Switch}))->tag)));
    (void)hoisted__Bool_3365;
    if (hoisted__Bool_3365) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
        return _r; }
    }
    U32 hoisted__U32_3366 = 1;
    (void)hoisted__U32_3366;
    Bool hoisted__Bool_3367 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Match}))->tag)));
    (void)hoisted__Bool_3367;
    if (hoisted__Bool_3367) {
        MatchData *_clone_payload_Match_19 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3322 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3322;
        NodeType *hoisted__NodeType_3323 = NodeType_Match(hoisted__MatchData_3322);
        (void)hoisted__NodeType_3323;
        return hoisted__NodeType_3323;
    }
    U32 hoisted__U32_3368 = 1;
    (void)hoisted__U32_3368;
    Bool hoisted__Bool_3369 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Case}))->tag)));
    (void)hoisted__Bool_3369;
    if (hoisted__Bool_3369) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
        return _r; }
    }
    U32 hoisted__U32_3370 = 1;
    (void)hoisted__U32_3370;
    Bool hoisted__Bool_3371 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_NoDefaultArg}))->tag)));
    (void)hoisted__Bool_3371;
    if (hoisted__Bool_3371) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
        return _r; }
    }
    U32 hoisted__U32_3372 = 1;
    (void)hoisted__U32_3372;
    Bool hoisted__Bool_3373 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Throw}))->tag)));
    (void)hoisted__Bool_3373;
    if (hoisted__Bool_3373) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
        return _r; }
    }
    U32 hoisted__U32_3374 = 1;
    (void)hoisted__U32_3374;
    Bool hoisted__Bool_3375 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Catch}))->tag)));
    (void)hoisted__Bool_3375;
    if (hoisted__Bool_3375) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
        return _r; }
    }
    U32 hoisted__U32_3376 = 1;
    (void)hoisted__U32_3376;
    Bool hoisted__Bool_3377 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_RestPattern}))->tag)));
    (void)hoisted__Bool_3377;
    if (hoisted__Bool_3377) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
        return _r; }
    }
    U32 hoisted__U32_3378 = 1;
    (void)hoisted__U32_3378;
    Bool hoisted__Bool_3379 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_CaptureBlock}))->tag)));
    (void)hoisted__Bool_3379;
    if (hoisted__Bool_3379) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3324 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3324;
        NodeType *hoisted__NodeType_3325 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3324);
        (void)hoisted__NodeType_3325;
        return hoisted__NodeType_3325;
    }
    U32 hoisted__U32_3380 = 1;
    (void)hoisted__U32_3380;
    Bool hoisted__Bool_3381 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Loc}))->tag)));
    (void)hoisted__Bool_3381;
    if (hoisted__Bool_3381) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
        return _r; }
    }
    U32 hoisted__U32_3382 = 1;
    (void)hoisted__U32_3382;
    Bool hoisted__Bool_3383 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_BodyValue}))->tag)));
    (void)hoisted__Bool_3383;
    if (hoisted__Bool_3383) {
        CaptureBlockData *_clone_payload_BodyValue_27 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_BodyValue_27;
        (void)_clone_payload_BodyValue_27;
        CaptureBlockData *hoisted__CaptureBlockData_3326 = CaptureBlockData_clone(_clone_payload_BodyValue_27);
        (void)hoisted__CaptureBlockData_3326;
        NodeType *hoisted__NodeType_3327 = NodeType_BodyValue(hoisted__CaptureBlockData_3326);
        (void)hoisted__NodeType_3327;
        return hoisted__NodeType_3327;
    }
    { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_ListPattern;
    return _r; }
    __builtin_unreachable();
}

USize NodeType_size(void) {
    U32 hoisted__U32_3384 = 120;
    (void)hoisted__U32_3384;
    return hoisted__U32_3384;
    __builtin_unreachable();
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3385 = ((Bool)((UPtr)(self) == 0));
    (void)hoisted__Bool_3385;
    if (hoisted__Bool_3385) {
        return;
    }
    Bool hoisted__Bool_3386 = 0;
    (void)hoisted__Bool_3386;
    NodeType_delete(&self->node_type, hoisted__Bool_3386);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3427 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3427->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3427->children = *_ca; free(_ca); }
    hoisted__Expr_3427->line = line;
    hoisted__Expr_3427->col = col;
    (void)hoisted__Expr_3427;
    return hoisted__Expr_3427;
    __builtin_unreachable();
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3685 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3685->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3685->children = *_ca; free(_ca); }
    hoisted__Expr_3685->line = self->line;
    hoisted__Expr_3685->col = self->col;
    (void)hoisted__Expr_3685;
    return hoisted__Expr_3685;
    __builtin_unreachable();
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3686 = 0;
    (void)hoisted__U32_3686;
    U64 hoisted__U64_3687 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3686); });
    (void)hoisted__U64_3687;
    return hoisted__U64_3687;
    __builtin_unreachable();
}

USize Expr_size(void) {
    U32 hoisted__U32_3688 = 144;
    (void)hoisted__U32_3688;
    return hoisted__U32_3688;
    __builtin_unreachable();
}

Map__Str_USize * Map__Str_USize_new(void) {
    Map__Str_USize *hoisted__Map__Str_USize_3689 = malloc(sizeof(Map__Str_USize));
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__Str_USize_3689->keys = *_ca; free(_ca); }
    { Vec__USize *_ca = Vec__USize_new(); hoisted__Map__Str_USize_3689->values = *_ca; free(_ca); }
    (void)hoisted__Map__Str_USize_3689;
    return hoisted__Map__Str_USize_3689;
    __builtin_unreachable();
}

void Map__Str_USize_delete(Map__Str_USize * self, Bool call_free) {
    Bool hoisted__Bool_3818 = 0;
    (void)hoisted__Bool_3818;
    Vec__Str_delete(&self->keys, hoisted__Bool_3818);
    Bool hoisted__Bool_3819 = 0;
    (void)hoisted__Bool_3819;
    Vec__USize_delete(&self->values, hoisted__Bool_3819);
    if (call_free) {
        free(self);
    }
}

Map__Str_USize * Map__Str_USize_clone(Map__Str_USize * self) {
    Map__Str_USize *hoisted__Map__Str_USize_3820 = malloc(sizeof(Map__Str_USize));
    { Vec__Str *_ca = Vec__Str_clone(&self->keys); hoisted__Map__Str_USize_3820->keys = *_ca; free(_ca); }
    { Vec__USize *_ca = Vec__USize_clone(&self->values); hoisted__Map__Str_USize_3820->values = *_ca; free(_ca); }
    (void)hoisted__Map__Str_USize_3820;
    return hoisted__Map__Str_USize_3820;
    __builtin_unreachable();
}

U64 Map__Str_USize_hash(Map__Str_USize * self, HashFn hasher) {
    U32 hoisted__U32_3821 = 0;
    (void)hoisted__U32_3821;
    U64 hoisted__U64_3822 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__Str_USize *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3821); });
    (void)hoisted__U64_3822;
    return hoisted__U64_3822;
    __builtin_unreachable();
}

USize Map__Str_USize_size(void) {
    U32 hoisted__U32_3823 = 32;
    (void)hoisted__U32_3823;
    return hoisted__U32_3823;
    __builtin_unreachable();
}

Vec__VariantDef * Vec__VariantDef_new(void) {
    U8 *hoisted__U8_3824 = malloc(sizeof(U8));
    *hoisted__U8_3824 = 0;
    (void)hoisted__U8_3824;
    U32 hoisted__U32_3825 = 0;
    (void)hoisted__U32_3825;
    I64 hoisted__I64_3826 = 0;
    (void)hoisted__I64_3826;
    Vec__VariantDef *hoisted__Vec__VariantDef_3827 = malloc(sizeof(Vec__VariantDef));
    hoisted__Vec__VariantDef_3827->data = hoisted__U8_3824;
    hoisted__Vec__VariantDef_3827->count = hoisted__U32_3825;
    hoisted__Vec__VariantDef_3827->cap = hoisted__I64_3826;
    (void)hoisted__Vec__VariantDef_3827;
    return hoisted__Vec__VariantDef_3827;
    __builtin_unreachable();
}

void Vec__VariantDef_clear(Vec__VariantDef * self) {
    {
        U32 _re_U32_3839 = self->count;
        (void)_re_U32_3839;
        U32 _rc_U32_3839 = 0;
        (void)_rc_U32_3839;
        Bool hoisted__Bool_3850 = ((Bool)(_rc_U32_3839 <= _re_U32_3839));
        (void)hoisted__Bool_3850;
        if (hoisted__Bool_3850) {
            while (1) {
                Bool _wcond_Bool_3840 = ((Bool)(_rc_U32_3839 < _re_U32_3839));
                (void)_wcond_Bool_3840;
                if (_wcond_Bool_3840) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_3839);
                (++_rc_U32_3839);
                U32 hoisted__U32_3841 = 72;
                (void)hoisted__U32_3841;
                U32 hoisted__U32_3842 = ((U32)(i * hoisted__U32_3841));
                (void)hoisted__U32_3842;
                VariantDef *hoisted__VariantDef_3843 = ((void *)((U8 *)(self->data) + (hoisted__U32_3842)));
                (void)hoisted__VariantDef_3843;
                (void)hoisted__VariantDef_3843;
                Bool hoisted__Bool_3844 = 0;
                (void)hoisted__Bool_3844;
                VariantDef_delete(hoisted__VariantDef_3843, hoisted__Bool_3844);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3845 = ((Bool)(_rc_U32_3839 > _re_U32_3839));
                (void)_wcond_Bool_3845;
                if (_wcond_Bool_3845) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_3839);
                (--_rc_U32_3839);
                U32 hoisted__U32_3846 = 72;
                (void)hoisted__U32_3846;
                U32 hoisted__U32_3847 = ((U32)(i * hoisted__U32_3846));
                (void)hoisted__U32_3847;
                VariantDef *hoisted__VariantDef_3848 = ((void *)((U8 *)(self->data) + (hoisted__U32_3847)));
                (void)hoisted__VariantDef_3848;
                (void)hoisted__VariantDef_3848;
                Bool hoisted__Bool_3849 = 0;
                (void)hoisted__Bool_3849;
                VariantDef_delete(hoisted__VariantDef_3848, hoisted__Bool_3849);
            }
        }
    }
    U32 hoisted__U32_3851 = 0;
    (void)hoisted__U32_3851;
    self->count = hoisted__U32_3851;
}

void Vec__VariantDef_delete(Vec__VariantDef * self, Bool call_free) {
    Vec__VariantDef_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__VariantDef * Vec__VariantDef_clone(Vec__VariantDef * self) {
    U32 hoisted__U32_4111 = 0;
    (void)hoisted__U32_4111;
    Bool hoisted__Bool_4112 = ((Bool)(self->cap == hoisted__U32_4111));
    (void)hoisted__Bool_4112;
    if (hoisted__Bool_4112) {
        U8 *hoisted__U8_4087 = malloc(sizeof(U8));
        *hoisted__U8_4087 = 0;
        (void)hoisted__U8_4087;
        U32 hoisted__U32_4088 = 0;
        (void)hoisted__U32_4088;
        I64 hoisted__I64_4089 = 0;
        (void)hoisted__I64_4089;
        Vec__VariantDef *hoisted__Vec__VariantDef_4090 = malloc(sizeof(Vec__VariantDef));
        hoisted__Vec__VariantDef_4090->data = hoisted__U8_4087;
        hoisted__Vec__VariantDef_4090->count = hoisted__U32_4088;
        hoisted__Vec__VariantDef_4090->cap = hoisted__I64_4089;
        (void)hoisted__Vec__VariantDef_4090;
        return hoisted__Vec__VariantDef_4090;
    }
    U32 hoisted__U32_4113 = 72;
    (void)hoisted__U32_4113;
    U32 hoisted__U32_4114 = ((U32)(self->cap * hoisted__U32_4113));
    (void)hoisted__U32_4114;
    U8 *new_data = malloc(hoisted__U32_4114);
    {
        U32 _re_U32_4091 = self->count;
        (void)_re_U32_4091;
        U32 _rc_U32_4091 = 0;
        (void)_rc_U32_4091;
        Bool hoisted__Bool_4110 = ((Bool)(_rc_U32_4091 <= _re_U32_4091));
        (void)hoisted__Bool_4110;
        if (hoisted__Bool_4110) {
            while (1) {
                Bool _wcond_Bool_4092 = ((Bool)(_rc_U32_4091 < _re_U32_4091));
                (void)_wcond_Bool_4092;
                if (_wcond_Bool_4092) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4091);
                (++_rc_U32_4091);
                U32 hoisted__U32_4093 = 72;
                (void)hoisted__U32_4093;
                U32 hoisted__U32_4094 = ((U32)(i * hoisted__U32_4093));
                (void)hoisted__U32_4094;
                VariantDef *src = ((void *)((U8 *)(self->data) + (hoisted__U32_4094)));
                VariantDef *cloned = VariantDef_clone(src);
                U32 hoisted__U32_4095 = 72;
                (void)hoisted__U32_4095;
                U32 hoisted__U32_4096 = ((U32)(i * hoisted__U32_4095));
                (void)hoisted__U32_4096;
                void *hoisted__v_4097 = ((void *)((U8 *)(new_data) + (hoisted__U32_4096)));
                (void)hoisted__v_4097;
                (void)hoisted__v_4097;
                U32 hoisted__U32_4098 = 72;
                (void)hoisted__U32_4098;
                memcpy(hoisted__v_4097, cloned, hoisted__U32_4098);
                I32 hoisted__I32_4099 = 0;
                (void)hoisted__I32_4099;
                U32 hoisted__U32_4100 = 72;
                (void)hoisted__U32_4100;
                memset(cloned, hoisted__I32_4099, hoisted__U32_4100);
                VariantDef_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4101 = ((Bool)(_rc_U32_4091 > _re_U32_4091));
                (void)_wcond_Bool_4101;
                if (_wcond_Bool_4101) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4091);
                (--_rc_U32_4091);
                U32 hoisted__U32_4102 = 72;
                (void)hoisted__U32_4102;
                U32 hoisted__U32_4103 = ((U32)(i * hoisted__U32_4102));
                (void)hoisted__U32_4103;
                VariantDef *src = ((void *)((U8 *)(self->data) + (hoisted__U32_4103)));
                VariantDef *cloned = VariantDef_clone(src);
                U32 hoisted__U32_4104 = 72;
                (void)hoisted__U32_4104;
                U32 hoisted__U32_4105 = ((U32)(i * hoisted__U32_4104));
                (void)hoisted__U32_4105;
                void *hoisted__v_4106 = ((void *)((U8 *)(new_data) + (hoisted__U32_4105)));
                (void)hoisted__v_4106;
                (void)hoisted__v_4106;
                U32 hoisted__U32_4107 = 72;
                (void)hoisted__U32_4107;
                memcpy(hoisted__v_4106, cloned, hoisted__U32_4107);
                I32 hoisted__I32_4108 = 0;
                (void)hoisted__I32_4108;
                U32 hoisted__U32_4109 = 72;
                (void)hoisted__U32_4109;
                memset(cloned, hoisted__I32_4108, hoisted__U32_4109);
                VariantDef_delete(cloned, 1);
            }
        }
    }
    Vec__VariantDef *hoisted__Vec__VariantDef_4115 = malloc(sizeof(Vec__VariantDef));
    hoisted__Vec__VariantDef_4115->data = new_data;
    hoisted__Vec__VariantDef_4115->count = self->count;
    hoisted__Vec__VariantDef_4115->cap = self->cap;
    (void)hoisted__Vec__VariantDef_4115;
    return hoisted__Vec__VariantDef_4115;
    __builtin_unreachable();
}

USize Vec__VariantDef_size(void) {
    U32 hoisted__U32_4116 = 16;
    (void)hoisted__U32_4116;
    return hoisted__U32_4116;
    __builtin_unreachable();
}

Vec__Declaration * Vec__Declaration_new(void) {
    U8 *hoisted__U8_4410 = malloc(sizeof(U8));
    *hoisted__U8_4410 = 0;
    (void)hoisted__U8_4410;
    U32 hoisted__U32_4411 = 0;
    (void)hoisted__U32_4411;
    I64 hoisted__I64_4412 = 0;
    (void)hoisted__I64_4412;
    Vec__Declaration *hoisted__Vec__Declaration_4413 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_4413->data = hoisted__U8_4410;
    hoisted__Vec__Declaration_4413->count = hoisted__U32_4411;
    hoisted__Vec__Declaration_4413->cap = hoisted__I64_4412;
    (void)hoisted__Vec__Declaration_4413;
    return hoisted__Vec__Declaration_4413;
    __builtin_unreachable();
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_4425 = self->count;
        (void)_re_U32_4425;
        U32 _rc_U32_4425 = 0;
        (void)_rc_U32_4425;
        Bool hoisted__Bool_4436 = ((Bool)(_rc_U32_4425 <= _re_U32_4425));
        (void)hoisted__Bool_4436;
        if (hoisted__Bool_4436) {
            while (1) {
                Bool _wcond_Bool_4426 = ((Bool)(_rc_U32_4425 < _re_U32_4425));
                (void)_wcond_Bool_4426;
                if (_wcond_Bool_4426) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4425);
                (++_rc_U32_4425);
                U32 hoisted__U32_4427 = 112;
                (void)hoisted__U32_4427;
                U32 hoisted__U32_4428 = ((U32)(i * hoisted__U32_4427));
                (void)hoisted__U32_4428;
                Declaration *hoisted__Declaration_4429 = ((void *)((U8 *)(self->data) + (hoisted__U32_4428)));
                (void)hoisted__Declaration_4429;
                (void)hoisted__Declaration_4429;
                Bool hoisted__Bool_4430 = 0;
                (void)hoisted__Bool_4430;
                Declaration_delete(hoisted__Declaration_4429, hoisted__Bool_4430);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4431 = ((Bool)(_rc_U32_4425 > _re_U32_4425));
                (void)_wcond_Bool_4431;
                if (_wcond_Bool_4431) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4425);
                (--_rc_U32_4425);
                U32 hoisted__U32_4432 = 112;
                (void)hoisted__U32_4432;
                U32 hoisted__U32_4433 = ((U32)(i * hoisted__U32_4432));
                (void)hoisted__U32_4433;
                Declaration *hoisted__Declaration_4434 = ((void *)((U8 *)(self->data) + (hoisted__U32_4433)));
                (void)hoisted__Declaration_4434;
                (void)hoisted__Declaration_4434;
                Bool hoisted__Bool_4435 = 0;
                (void)hoisted__Bool_4435;
                Declaration_delete(hoisted__Declaration_4434, hoisted__Bool_4435);
            }
        }
    }
    U32 hoisted__U32_4437 = 0;
    (void)hoisted__U32_4437;
    self->count = hoisted__U32_4437;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U32 hoisted__U32_4697 = 0;
    (void)hoisted__U32_4697;
    Bool hoisted__Bool_4698 = ((Bool)(self->cap == hoisted__U32_4697));
    (void)hoisted__Bool_4698;
    if (hoisted__Bool_4698) {
        U8 *hoisted__U8_4673 = malloc(sizeof(U8));
        *hoisted__U8_4673 = 0;
        (void)hoisted__U8_4673;
        U32 hoisted__U32_4674 = 0;
        (void)hoisted__U32_4674;
        I64 hoisted__I64_4675 = 0;
        (void)hoisted__I64_4675;
        Vec__Declaration *hoisted__Vec__Declaration_4676 = malloc(sizeof(Vec__Declaration));
        hoisted__Vec__Declaration_4676->data = hoisted__U8_4673;
        hoisted__Vec__Declaration_4676->count = hoisted__U32_4674;
        hoisted__Vec__Declaration_4676->cap = hoisted__I64_4675;
        (void)hoisted__Vec__Declaration_4676;
        return hoisted__Vec__Declaration_4676;
    }
    U32 hoisted__U32_4699 = 112;
    (void)hoisted__U32_4699;
    U32 hoisted__U32_4700 = ((U32)(self->cap * hoisted__U32_4699));
    (void)hoisted__U32_4700;
    U8 *new_data = malloc(hoisted__U32_4700);
    {
        U32 _re_U32_4677 = self->count;
        (void)_re_U32_4677;
        U32 _rc_U32_4677 = 0;
        (void)_rc_U32_4677;
        Bool hoisted__Bool_4696 = ((Bool)(_rc_U32_4677 <= _re_U32_4677));
        (void)hoisted__Bool_4696;
        if (hoisted__Bool_4696) {
            while (1) {
                Bool _wcond_Bool_4678 = ((Bool)(_rc_U32_4677 < _re_U32_4677));
                (void)_wcond_Bool_4678;
                if (_wcond_Bool_4678) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4677);
                (++_rc_U32_4677);
                U32 hoisted__U32_4679 = 112;
                (void)hoisted__U32_4679;
                U32 hoisted__U32_4680 = ((U32)(i * hoisted__U32_4679));
                (void)hoisted__U32_4680;
                Declaration *src = ((void *)((U8 *)(self->data) + (hoisted__U32_4680)));
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_4681 = 112;
                (void)hoisted__U32_4681;
                U32 hoisted__U32_4682 = ((U32)(i * hoisted__U32_4681));
                (void)hoisted__U32_4682;
                void *hoisted__v_4683 = ((void *)((U8 *)(new_data) + (hoisted__U32_4682)));
                (void)hoisted__v_4683;
                (void)hoisted__v_4683;
                U32 hoisted__U32_4684 = 112;
                (void)hoisted__U32_4684;
                memcpy(hoisted__v_4683, cloned, hoisted__U32_4684);
                I32 hoisted__I32_4685 = 0;
                (void)hoisted__I32_4685;
                U32 hoisted__U32_4686 = 112;
                (void)hoisted__U32_4686;
                memset(cloned, hoisted__I32_4685, hoisted__U32_4686);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4687 = ((Bool)(_rc_U32_4677 > _re_U32_4677));
                (void)_wcond_Bool_4687;
                if (_wcond_Bool_4687) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4677);
                (--_rc_U32_4677);
                U32 hoisted__U32_4688 = 112;
                (void)hoisted__U32_4688;
                U32 hoisted__U32_4689 = ((U32)(i * hoisted__U32_4688));
                (void)hoisted__U32_4689;
                Declaration *src = ((void *)((U8 *)(self->data) + (hoisted__U32_4689)));
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_4690 = 112;
                (void)hoisted__U32_4690;
                U32 hoisted__U32_4691 = ((U32)(i * hoisted__U32_4690));
                (void)hoisted__U32_4691;
                void *hoisted__v_4692 = ((void *)((U8 *)(new_data) + (hoisted__U32_4691)));
                (void)hoisted__v_4692;
                (void)hoisted__v_4692;
                U32 hoisted__U32_4693 = 112;
                (void)hoisted__U32_4693;
                memcpy(hoisted__v_4692, cloned, hoisted__U32_4693);
                I32 hoisted__I32_4694 = 0;
                (void)hoisted__I32_4694;
                U32 hoisted__U32_4695 = 112;
                (void)hoisted__U32_4695;
                memset(cloned, hoisted__I32_4694, hoisted__U32_4695);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_4701 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_4701->data = new_data;
    hoisted__Vec__Declaration_4701->count = self->count;
    hoisted__Vec__Declaration_4701->cap = self->cap;
    (void)hoisted__Vec__Declaration_4701;
    return hoisted__Vec__Declaration_4701;
    __builtin_unreachable();
}

USize Vec__Declaration_size(void) {
    U32 hoisted__U32_4702 = 16;
    (void)hoisted__U32_4702;
    return hoisted__U32_4702;
    __builtin_unreachable();
}

Vec__Expr * Vec__Expr_new(void) {
    U8 *hoisted__U8_4703 = malloc(sizeof(U8));
    *hoisted__U8_4703 = 0;
    (void)hoisted__U8_4703;
    U32 hoisted__U32_4704 = 0;
    (void)hoisted__U32_4704;
    I64 hoisted__I64_4705 = 0;
    (void)hoisted__I64_4705;
    Vec__Expr *hoisted__Vec__Expr_4706 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_4706->data = hoisted__U8_4703;
    hoisted__Vec__Expr_4706->count = hoisted__U32_4704;
    hoisted__Vec__Expr_4706->cap = hoisted__I64_4705;
    (void)hoisted__Vec__Expr_4706;
    return hoisted__Vec__Expr_4706;
    __builtin_unreachable();
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_4718 = self->count;
        (void)_re_U32_4718;
        U32 _rc_U32_4718 = 0;
        (void)_rc_U32_4718;
        Bool hoisted__Bool_4729 = ((Bool)(_rc_U32_4718 <= _re_U32_4718));
        (void)hoisted__Bool_4729;
        if (hoisted__Bool_4729) {
            while (1) {
                Bool _wcond_Bool_4719 = ((Bool)(_rc_U32_4718 < _re_U32_4718));
                (void)_wcond_Bool_4719;
                if (_wcond_Bool_4719) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4718);
                (++_rc_U32_4718);
                U32 hoisted__U32_4720 = 144;
                (void)hoisted__U32_4720;
                U32 hoisted__U32_4721 = ((U32)(i * hoisted__U32_4720));
                (void)hoisted__U32_4721;
                Expr *hoisted__Expr_4722 = ((void *)((U8 *)(self->data) + (hoisted__U32_4721)));
                (void)hoisted__Expr_4722;
                (void)hoisted__Expr_4722;
                Bool hoisted__Bool_4723 = 0;
                (void)hoisted__Bool_4723;
                Expr_delete(hoisted__Expr_4722, hoisted__Bool_4723);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4724 = ((Bool)(_rc_U32_4718 > _re_U32_4718));
                (void)_wcond_Bool_4724;
                if (_wcond_Bool_4724) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4718);
                (--_rc_U32_4718);
                U32 hoisted__U32_4725 = 144;
                (void)hoisted__U32_4725;
                U32 hoisted__U32_4726 = ((U32)(i * hoisted__U32_4725));
                (void)hoisted__U32_4726;
                Expr *hoisted__Expr_4727 = ((void *)((U8 *)(self->data) + (hoisted__U32_4726)));
                (void)hoisted__Expr_4727;
                (void)hoisted__Expr_4727;
                Bool hoisted__Bool_4728 = 0;
                (void)hoisted__Bool_4728;
                Expr_delete(hoisted__Expr_4727, hoisted__Bool_4728);
            }
        }
    }
    U32 hoisted__U32_4730 = 0;
    (void)hoisted__U32_4730;
    self->count = hoisted__U32_4730;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_4990 = 0;
    (void)hoisted__U32_4990;
    Bool hoisted__Bool_4991 = ((Bool)(self->cap == hoisted__U32_4990));
    (void)hoisted__Bool_4991;
    if (hoisted__Bool_4991) {
        U8 *hoisted__U8_4966 = malloc(sizeof(U8));
        *hoisted__U8_4966 = 0;
        (void)hoisted__U8_4966;
        U32 hoisted__U32_4967 = 0;
        (void)hoisted__U32_4967;
        I64 hoisted__I64_4968 = 0;
        (void)hoisted__I64_4968;
        Vec__Expr *hoisted__Vec__Expr_4969 = malloc(sizeof(Vec__Expr));
        hoisted__Vec__Expr_4969->data = hoisted__U8_4966;
        hoisted__Vec__Expr_4969->count = hoisted__U32_4967;
        hoisted__Vec__Expr_4969->cap = hoisted__I64_4968;
        (void)hoisted__Vec__Expr_4969;
        return hoisted__Vec__Expr_4969;
    }
    U32 hoisted__U32_4992 = 144;
    (void)hoisted__U32_4992;
    U32 hoisted__U32_4993 = ((U32)(self->cap * hoisted__U32_4992));
    (void)hoisted__U32_4993;
    U8 *new_data = malloc(hoisted__U32_4993);
    {
        U32 _re_U32_4970 = self->count;
        (void)_re_U32_4970;
        U32 _rc_U32_4970 = 0;
        (void)_rc_U32_4970;
        Bool hoisted__Bool_4989 = ((Bool)(_rc_U32_4970 <= _re_U32_4970));
        (void)hoisted__Bool_4989;
        if (hoisted__Bool_4989) {
            while (1) {
                Bool _wcond_Bool_4971 = ((Bool)(_rc_U32_4970 < _re_U32_4970));
                (void)_wcond_Bool_4971;
                if (_wcond_Bool_4971) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4970);
                (++_rc_U32_4970);
                U32 hoisted__U32_4972 = 144;
                (void)hoisted__U32_4972;
                U32 hoisted__U32_4973 = ((U32)(i * hoisted__U32_4972));
                (void)hoisted__U32_4973;
                Expr *src = ((void *)((U8 *)(self->data) + (hoisted__U32_4973)));
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_4974 = 144;
                (void)hoisted__U32_4974;
                U32 hoisted__U32_4975 = ((U32)(i * hoisted__U32_4974));
                (void)hoisted__U32_4975;
                void *hoisted__v_4976 = ((void *)((U8 *)(new_data) + (hoisted__U32_4975)));
                (void)hoisted__v_4976;
                (void)hoisted__v_4976;
                U32 hoisted__U32_4977 = 144;
                (void)hoisted__U32_4977;
                memcpy(hoisted__v_4976, cloned, hoisted__U32_4977);
                I32 hoisted__I32_4978 = 0;
                (void)hoisted__I32_4978;
                U32 hoisted__U32_4979 = 144;
                (void)hoisted__U32_4979;
                memset(cloned, hoisted__I32_4978, hoisted__U32_4979);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4980 = ((Bool)(_rc_U32_4970 > _re_U32_4970));
                (void)_wcond_Bool_4980;
                if (_wcond_Bool_4980) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4970);
                (--_rc_U32_4970);
                U32 hoisted__U32_4981 = 144;
                (void)hoisted__U32_4981;
                U32 hoisted__U32_4982 = ((U32)(i * hoisted__U32_4981));
                (void)hoisted__U32_4982;
                Expr *src = ((void *)((U8 *)(self->data) + (hoisted__U32_4982)));
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_4983 = 144;
                (void)hoisted__U32_4983;
                U32 hoisted__U32_4984 = ((U32)(i * hoisted__U32_4983));
                (void)hoisted__U32_4984;
                void *hoisted__v_4985 = ((void *)((U8 *)(new_data) + (hoisted__U32_4984)));
                (void)hoisted__v_4985;
                (void)hoisted__v_4985;
                U32 hoisted__U32_4986 = 144;
                (void)hoisted__U32_4986;
                memcpy(hoisted__v_4985, cloned, hoisted__U32_4986);
                I32 hoisted__I32_4987 = 0;
                (void)hoisted__I32_4987;
                U32 hoisted__U32_4988 = 144;
                (void)hoisted__U32_4988;
                memset(cloned, hoisted__I32_4987, hoisted__U32_4988);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_4994 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_4994->data = new_data;
    hoisted__Vec__Expr_4994->count = self->count;
    hoisted__Vec__Expr_4994->cap = self->cap;
    (void)hoisted__Vec__Expr_4994;
    return hoisted__Vec__Expr_4994;
    __builtin_unreachable();
}

USize Vec__Expr_size(void) {
    U32 hoisted__U32_4995 = 16;
    (void)hoisted__U32_4995;
    return hoisted__U32_4995;
    __builtin_unreachable();
}

Vec__USize * Vec__USize_new(void) {
    U8 *hoisted__U8_4996 = malloc(sizeof(U8));
    *hoisted__U8_4996 = 0;
    (void)hoisted__U8_4996;
    U32 hoisted__U32_4997 = 0;
    (void)hoisted__U32_4997;
    I64 hoisted__I64_4998 = 0;
    (void)hoisted__I64_4998;
    Vec__USize *hoisted__Vec__USize_4999 = malloc(sizeof(Vec__USize));
    hoisted__Vec__USize_4999->data = hoisted__U8_4996;
    hoisted__Vec__USize_4999->count = hoisted__U32_4997;
    hoisted__Vec__USize_4999->cap = hoisted__I64_4998;
    (void)hoisted__Vec__USize_4999;
    return hoisted__Vec__USize_4999;
    __builtin_unreachable();
}

void Vec__USize_clear(Vec__USize * self) {
    {
        U32 _re_U32_5011 = self->count;
        (void)_re_U32_5011;
        U32 _rc_U32_5011 = 0;
        (void)_rc_U32_5011;
        Bool hoisted__Bool_5022 = ((Bool)(_rc_U32_5011 <= _re_U32_5011));
        (void)hoisted__Bool_5022;
        if (hoisted__Bool_5022) {
            while (1) {
                Bool _wcond_Bool_5012 = ((Bool)(_rc_U32_5011 < _re_U32_5011));
                (void)_wcond_Bool_5012;
                if (_wcond_Bool_5012) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5011);
                (++_rc_U32_5011);
                USize hoisted__U32_5013 = U32_size();
                (void)hoisted__U32_5013;
                U32 hoisted__U32_5014 = ((U32)(i * hoisted__U32_5013));
                (void)hoisted__U32_5014;
                U32 *hoisted__U32_5015 = ((void *)((U8 *)(self->data) + (hoisted__U32_5014)));
                (void)hoisted__U32_5015;
                (void)hoisted__U32_5015;
                Bool hoisted__Bool_5016 = 0;
                (void)hoisted__Bool_5016;
                U32_delete(hoisted__U32_5015, hoisted__Bool_5016);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5017 = ((Bool)(_rc_U32_5011 > _re_U32_5011));
                (void)_wcond_Bool_5017;
                if (_wcond_Bool_5017) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5011);
                (--_rc_U32_5011);
                USize hoisted__U32_5018 = U32_size();
                (void)hoisted__U32_5018;
                U32 hoisted__U32_5019 = ((U32)(i * hoisted__U32_5018));
                (void)hoisted__U32_5019;
                U32 *hoisted__U32_5020 = ((void *)((U8 *)(self->data) + (hoisted__U32_5019)));
                (void)hoisted__U32_5020;
                (void)hoisted__U32_5020;
                Bool hoisted__Bool_5021 = 0;
                (void)hoisted__Bool_5021;
                U32_delete(hoisted__U32_5020, hoisted__Bool_5021);
            }
        }
    }
    U32 hoisted__U32_5023 = 0;
    (void)hoisted__U32_5023;
    self->count = hoisted__U32_5023;
}

void Vec__USize_delete(Vec__USize * self, Bool call_free) {
    Vec__USize_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__USize * Vec__USize_clone(Vec__USize * self) {
    U32 hoisted__U32_5283 = 0;
    (void)hoisted__U32_5283;
    Bool hoisted__Bool_5284 = ((Bool)(self->cap == hoisted__U32_5283));
    (void)hoisted__Bool_5284;
    if (hoisted__Bool_5284) {
        U8 *hoisted__U8_5259 = malloc(sizeof(U8));
        *hoisted__U8_5259 = 0;
        (void)hoisted__U8_5259;
        U32 hoisted__U32_5260 = 0;
        (void)hoisted__U32_5260;
        I64 hoisted__I64_5261 = 0;
        (void)hoisted__I64_5261;
        Vec__USize *hoisted__Vec__USize_5262 = malloc(sizeof(Vec__USize));
        hoisted__Vec__USize_5262->data = hoisted__U8_5259;
        hoisted__Vec__USize_5262->count = hoisted__U32_5260;
        hoisted__Vec__USize_5262->cap = hoisted__I64_5261;
        (void)hoisted__Vec__USize_5262;
        return hoisted__Vec__USize_5262;
    }
    USize hoisted__U32_5285 = U32_size();
    (void)hoisted__U32_5285;
    U32 hoisted__U32_5286 = ((U32)(self->cap * hoisted__U32_5285));
    (void)hoisted__U32_5286;
    U8 *new_data = malloc(hoisted__U32_5286);
    {
        U32 _re_U32_5263 = self->count;
        (void)_re_U32_5263;
        U32 _rc_U32_5263 = 0;
        (void)_rc_U32_5263;
        Bool hoisted__Bool_5282 = ((Bool)(_rc_U32_5263 <= _re_U32_5263));
        (void)hoisted__Bool_5282;
        if (hoisted__Bool_5282) {
            while (1) {
                Bool _wcond_Bool_5264 = ((Bool)(_rc_U32_5263 < _re_U32_5263));
                (void)_wcond_Bool_5264;
                if (_wcond_Bool_5264) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5263);
                (++_rc_U32_5263);
                USize hoisted__U32_5265 = U32_size();
                (void)hoisted__U32_5265;
                U32 hoisted__U32_5266 = ((U32)(i * hoisted__U32_5265));
                (void)hoisted__U32_5266;
                U32 *src = ((void *)((U8 *)(self->data) + (hoisted__U32_5266)));
                U32 cloned = (DEREF(src));
                USize hoisted__U32_5267 = U32_size();
                (void)hoisted__U32_5267;
                U32 hoisted__U32_5268 = ((U32)(i * hoisted__U32_5267));
                (void)hoisted__U32_5268;
                void *hoisted__v_5269 = ((void *)((U8 *)(new_data) + (hoisted__U32_5268)));
                (void)hoisted__v_5269;
                (void)hoisted__v_5269;
                USize hoisted__U32_5270 = U32_size();
                (void)hoisted__U32_5270;
                memcpy(hoisted__v_5269, &cloned, hoisted__U32_5270);
                I32 hoisted__I32_5271 = 0;
                (void)hoisted__I32_5271;
                USize hoisted__U32_5272 = U32_size();
                (void)hoisted__U32_5272;
                memset(&cloned, hoisted__I32_5271, hoisted__U32_5272);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5273 = ((Bool)(_rc_U32_5263 > _re_U32_5263));
                (void)_wcond_Bool_5273;
                if (_wcond_Bool_5273) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5263);
                (--_rc_U32_5263);
                USize hoisted__U32_5274 = U32_size();
                (void)hoisted__U32_5274;
                U32 hoisted__U32_5275 = ((U32)(i * hoisted__U32_5274));
                (void)hoisted__U32_5275;
                U32 *src = ((void *)((U8 *)(self->data) + (hoisted__U32_5275)));
                U32 cloned = (DEREF(src));
                USize hoisted__U32_5276 = U32_size();
                (void)hoisted__U32_5276;
                U32 hoisted__U32_5277 = ((U32)(i * hoisted__U32_5276));
                (void)hoisted__U32_5277;
                void *hoisted__v_5278 = ((void *)((U8 *)(new_data) + (hoisted__U32_5277)));
                (void)hoisted__v_5278;
                (void)hoisted__v_5278;
                USize hoisted__U32_5279 = U32_size();
                (void)hoisted__U32_5279;
                memcpy(hoisted__v_5278, &cloned, hoisted__U32_5279);
                I32 hoisted__I32_5280 = 0;
                (void)hoisted__I32_5280;
                USize hoisted__U32_5281 = U32_size();
                (void)hoisted__U32_5281;
                memset(&cloned, hoisted__I32_5280, hoisted__U32_5281);
            }
        }
    }
    Vec__USize *hoisted__Vec__USize_5287 = malloc(sizeof(Vec__USize));
    hoisted__Vec__USize_5287->data = new_data;
    hoisted__Vec__USize_5287->count = self->count;
    hoisted__Vec__USize_5287->cap = self->cap;
    (void)hoisted__Vec__USize_5287;
    return hoisted__Vec__USize_5287;
    __builtin_unreachable();
}

USize Vec__USize_size(void) {
    U32 hoisted__U32_5288 = 16;
    (void)hoisted__U32_5288;
    return hoisted__U32_5288;
    __builtin_unreachable();
}

__attribute__((noreturn)) void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_5966 = 3;
    (void)hoisted__U32_5966;
    Array__Str *_va_Array_145 = Array__Str_new(hoisted__U32_5966);
    (void)_va_Array_145;
    I64 _va_Array_145_ek = 0;
    (void)_va_Array_145_ek;
    U32 hoisted__U32_5967 = 0;
    (void)hoisted__U32_5967;
    Str *hoisted__Str_5968 = Str_clone(loc);
    (void)hoisted__Str_5968;
    Array__Str_set(_va_Array_145, hoisted__U32_5967, hoisted__Str_5968, &_va_Array_145_ek);
    U32 hoisted__U32_5969 = 1;
    (void)hoisted__U32_5969;
    (void)_til_str_lits[162];
    (void)_til_str_lits[162];
    Array__Str_set(_va_Array_145, hoisted__U32_5969, &_til_str_lits[162], &_va_Array_145_ek);
    Array__Str *hoisted__Array__Str_5971 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_5971;
    U32 hoisted__U32_5972 = 2;
    (void)hoisted__U32_5972;
    Str *hoisted__Str_5973 = format(hoisted__Array__Str_5971);
    (void)hoisted__Str_5973;
    Array__Str_set(_va_Array_145, hoisted__U32_5972, hoisted__Str_5973, &_va_Array_145_ek);
    Array__Str_delete(parts, 1);
    println(_va_Array_145);
    I64 hoisted__I64_5974 = 1;
    (void)hoisted__I64_5974;
    exit(hoisted__I64_5974);
}

__attribute__((noreturn)) void UNREACHABLE(Str * loc) {
    U32 hoisted__U32_5981 = 1;
    (void)hoisted__U32_5981;
    Array__Str *_va_Array_147 = Array__Str_new(hoisted__U32_5981);
    (void)_va_Array_147;
    I64 _va_Array_147_ek = 0;
    (void)_va_Array_147_ek;
    U32 hoisted__U32_5982 = 0;
    (void)hoisted__U32_5982;
    (void)_til_str_lits[163];
    (void)_til_str_lits[163];
    Array__Str_set(_va_Array_147, hoisted__U32_5982, &_til_str_lits[163], &_va_Array_147_ek);
    panic(_va_Array_147, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_5987 = ((Bool)(!(cond)));
    (void)hoisted__Bool_5987;
    if (hoisted__Bool_5987) {
        U32 hoisted__U32_5984 = 1;
        (void)hoisted__U32_5984;
        Array__Str *_va_Array_148 = Array__Str_new(hoisted__U32_5984);
        (void)_va_Array_148;
        I64 _va_Array_148_ek = 0;
        (void)_va_Array_148_ek;
        U32 hoisted__U32_5985 = 0;
        (void)hoisted__U32_5985;
        (void)_til_str_lits[164];
        (void)_til_str_lits[164];
        Array__Str_set(_va_Array_148, hoisted__U32_5985, &_til_str_lits[164], &_va_Array_148_ek);
        panic(_va_Array_148, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_5995 = parts;
        (void)_fc_Array__Str_5995;
        (void)_fc_Array__Str_5995;
        U32 _fi_USize_5995 = 0;
        (void)_fi_USize_5995;
        while (1) {
            USize hoisted__U32_5997 = (_fc_Array__Str_5995->cap);
            (void)hoisted__U32_5997;
            Bool _wcond_Bool_5996 = ((Bool)(_fi_USize_5995 < hoisted__U32_5997));
            (void)_wcond_Bool_5996;
            if (_wcond_Bool_5996) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_5995->data) + (((U32)(_fi_USize_5995 * 16))))));
            U32 hoisted__U32_5998 = 1;
            (void)hoisted__U32_5998;
            U32 hoisted__U32_5999 = ((U32)(_fi_USize_5995 + hoisted__U32_5998));
            (void)hoisted__U32_5999;
            _fi_USize_5995 = hoisted__U32_5999;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_6012 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_6012;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_6012;
    return _r; }
    __builtin_unreachable();
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_6013 = 0;
    (void)hoisted__U32_6013;
    U64 hoisted__U64_6014 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_6013); });
    (void)hoisted__U64_6014;
    return hoisted__U64_6014;
    __builtin_unreachable();
}

USize Range_size(void) {
    U32 hoisted__U32_6038 = 16;
    (void)hoisted__U32_6038;
    return hoisted__U32_6038;
    __builtin_unreachable();
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_6052 = 3;
    (void)hoisted__I64_6052;
    (void)_til_str_lits[167];
    (void)_til_str_lits[167];
    assert_eq__I64(result, hoisted__I64_6052, &_til_str_lits[167]);
    Str_delete(&_til_str_lits[167], (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_6060 = 15;
    (void)hoisted__I64_6060;
    (void)_til_str_lits[168];
    (void)_til_str_lits[168];
    assert_eq__I64(result, hoisted__I64_6060, &_til_str_lits[168]);
    Str_delete(&_til_str_lits[168], (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_6068 = 26;
    (void)hoisted__I64_6068;
    (void)_til_str_lits[169];
    (void)_til_str_lits[169];
    assert_eq__I64(result, hoisted__I64_6068, &_til_str_lits[169]);
    Str_delete(&_til_str_lits[169], (Bool){0});
}

void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lits[170];
    (void)_til_str_lits[170];
    (void)_til_str_lits[171];
    (void)_til_str_lits[171];
    assert_eq__Str(&result, &_til_str_lits[170], &_til_str_lits[171]);
    Str_delete(&_til_str_lits[170], (Bool){0});
    Str_delete(&_til_str_lits[171], (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lits[170];
    (void)_til_str_lits[170];
    (void)_til_str_lits[172];
    (void)_til_str_lits[172];
    assert_eq__Str(&r, &_til_str_lits[170], &_til_str_lits[172]);
    Str_delete(&_til_str_lits[170], (Bool){0});
    Str_delete(&_til_str_lits[172], (Bool){0});
    Str_delete(&r, (Bool){0});
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lits[173];
    (void)_til_str_lits[173];
    (void)_til_str_lits[174];
    (void)_til_str_lits[174];
    assert_eq__Str(&r2, &_til_str_lits[173], &_til_str_lits[174]);
    Str_delete(&_til_str_lits[173], (Bool){0});
    Str_delete(&_til_str_lits[174], (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lits[175];
    (void)_til_str_lits[175];
    (void)_til_str_lits[176];
    (void)_til_str_lits[176];
    assert_eq__Str(&d, &_til_str_lits[175], &_til_str_lits[176]);
    Str_delete(&d, (Bool){0});
    Str_delete(&_til_str_lits[175], (Bool){0});
    Str_delete(&_til_str_lits[176], (Bool){0});
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lits[177];
    (void)_til_str_lits[177];
    (void)_til_str_lits[178];
    (void)_til_str_lits[178];
    assert_eq__Str(&d2, &_til_str_lits[177], &_til_str_lits[178]);
    Str_delete(&d2, (Bool){0});
    Str_delete(&_til_str_lits[177], (Bool){0});
    Str_delete(&_til_str_lits[178], (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_6137 = 106;
    (void)hoisted__I64_6137;
    (void)_til_str_lits[179];
    (void)_til_str_lits[179];
    assert_eq__I64(d3, hoisted__I64_6137, &_til_str_lits[179]);
    Str_delete(&_til_str_lits[179], (Bool){0});
}

void test_lolalalo(void) {
    static Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lits[182];
    (void)_til_str_lits[182];
    assert_eq__Str(&lola_rec, &lola_it, &_til_str_lits[182]);
    Str_delete(&_til_str_lits[182], (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    (void)_til_str_lits[183];
    (void)_til_str_lits[183];
    assert_eq__Str(&lalo_rec, &lalo_it, &_til_str_lits[183]);
    Str_delete(&_til_str_lits[183], (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_6630 = 8;
    (void)hoisted__I64_6630;
    (void)_til_str_lits[184];
    (void)_til_str_lits[184];
    assert_eq__I64(result, hoisted__I64_6630, &_til_str_lits[184]);
    Str_delete(&_til_str_lits[184], (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_6634 = 1;
    (void)hoisted__Bool_6634;
    (void)_til_str_lits[185];
    (void)_til_str_lits[185];
    assert(hoisted__Bool_6634, &_til_str_lits[185]);
    Str_delete(&_til_str_lits[185], (Bool){0});
    Bool hoisted__Bool_6638 = 1;
    (void)hoisted__Bool_6638;
    (void)_til_str_lits[186];
    (void)_til_str_lits[186];
    assert(hoisted__Bool_6638, &_til_str_lits[186]);
    Str_delete(&_til_str_lits[186], (Bool){0});
}

void test_fold_f32(void) {
    (void)_til_str_lits[187];
    (void)_til_str_lits[187];
    (void)_til_str_lits[187];
    (void)_til_str_lits[187];
    (void)_til_str_lits[188];
    (void)_til_str_lits[188];
    assert_eq__Str(&_til_str_lits[187], &_til_str_lits[187], &_til_str_lits[188]);
    Str_delete(&_til_str_lits[187], (Bool){0});
    Str_delete(&_til_str_lits[187], (Bool){0});
    Str_delete(&_til_str_lits[188], (Bool){0});
    (void)_til_str_lits[189];
    (void)_til_str_lits[189];
    (void)_til_str_lits[189];
    (void)_til_str_lits[189];
    (void)_til_str_lits[190];
    (void)_til_str_lits[190];
    assert_eq__Str(&_til_str_lits[189], &_til_str_lits[189], &_til_str_lits[190]);
    Str_delete(&_til_str_lits[189], (Bool){0});
    Str_delete(&_til_str_lits[189], (Bool){0});
    Str_delete(&_til_str_lits[190], (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_6656 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_6656;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_6656;
    return _r; }
    __builtin_unreachable();
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_6657 = 0;
    (void)hoisted__U32_6657;
    U64 hoisted__U64_6658 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_6657); });
    (void)hoisted__U64_6658;
    return hoisted__U64_6658;
    __builtin_unreachable();
}

USize CfVec2_size(void) {
    U32 hoisted__U32_6682 = 16;
    (void)hoisted__U32_6682;
    return hoisted__U32_6682;
    __builtin_unreachable();
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_6683 = 42;
    (void)hoisted__I64_6683;
    (void)_til_str_lits[193];
    (void)_til_str_lits[193];
    assert_eq__I64(v.x, hoisted__I64_6683, &_til_str_lits[193]);
    Str_delete(&_til_str_lits[193], (Bool){0});
    I64 hoisted__I64_6685 = 99;
    (void)hoisted__I64_6685;
    (void)_til_str_lits[194];
    (void)_til_str_lits[194];
    assert_eq__I64(v.y, hoisted__I64_6685, &_til_str_lits[194]);
    Str_delete(&_til_str_lits[194], (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_6689 = 10;
    (void)hoisted__I64_6689;
    (void)_til_str_lits[195];
    (void)_til_str_lits[195];
    assert_eq__I64(p.x, hoisted__I64_6689, &_til_str_lits[195]);
    Str_delete(&_til_str_lits[195], (Bool){0});
    I64 hoisted__I64_6691 = 20;
    (void)hoisted__I64_6691;
    (void)_til_str_lits[196];
    (void)_til_str_lits[196];
    assert_eq__I64(p.y, hoisted__I64_6691, &_til_str_lits[196]);
    Str_delete(&_til_str_lits[196], (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_6698 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_6698;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_6698;
    return _r; }
    __builtin_unreachable();
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_6699 = 0;
    (void)hoisted__U32_6699;
    U64 hoisted__U64_6700 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_6699); });
    (void)hoisted__U64_6700;
    return hoisted__U64_6700;
    __builtin_unreachable();
}

USize CfRect_size(void) {
    U32 hoisted__U32_6724 = 32;
    (void)hoisted__U32_6724;
    return hoisted__U32_6724;
    __builtin_unreachable();
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_6725 = 5;
    (void)hoisted__I64_6725;
    (void)_til_str_lits[200];
    (void)_til_str_lits[200];
    assert_eq__I64(r.top_left.x, hoisted__I64_6725, &_til_str_lits[200]);
    Str_delete(&_til_str_lits[200], (Bool){0});
    I64 hoisted__I64_6727 = 10;
    (void)hoisted__I64_6727;
    (void)_til_str_lits[201];
    (void)_til_str_lits[201];
    assert_eq__I64(r.top_left.y, hoisted__I64_6727, &_til_str_lits[201]);
    Str_delete(&_til_str_lits[201], (Bool){0});
    I64 hoisted__I64_6729 = 100;
    (void)hoisted__I64_6729;
    (void)_til_str_lits[202];
    (void)_til_str_lits[202];
    assert_eq__I64(r.bottom_right.x, hoisted__I64_6729, &_til_str_lits[202]);
    Str_delete(&_til_str_lits[202], (Bool){0});
    I64 hoisted__I64_6731 = 200;
    (void)hoisted__I64_6731;
    (void)_til_str_lits[203];
    (void)_til_str_lits[203];
    assert_eq__I64(r.bottom_right.y, hoisted__I64_6731, &_til_str_lits[203]);
    Str_delete(&_til_str_lits[203], (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_6734 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_6734;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_6734;
    return _r; }
    __builtin_unreachable();
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_6735 = 0;
    (void)hoisted__U32_6735;
    U64 hoisted__U64_6736 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_6735); });
    (void)hoisted__U64_6736;
    return hoisted__U64_6736;
    __builtin_unreachable();
}

USize CfVec3f_size(void) {
    U32 hoisted__U32_6769 = 12;
    (void)hoisted__U32_6769;
    return hoisted__U32_6769;
    __builtin_unreachable();
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_6773 = F32_to_str(v.x);
    (void)hoisted__Str_6773;
    (void)_til_str_lits[205];
    (void)_til_str_lits[205];
    (void)_til_str_lits[206];
    (void)_til_str_lits[206];
    assert_eq__Str(hoisted__Str_6773, &_til_str_lits[205], &_til_str_lits[206]);
    Str_delete(hoisted__Str_6773, 1);
    Str_delete(&_til_str_lits[205], (Bool){0});
    Str_delete(&_til_str_lits[206], (Bool){0});
    Str *hoisted__Str_6776 = F32_to_str(v.y);
    (void)hoisted__Str_6776;
    (void)_til_str_lits[207];
    (void)_til_str_lits[207];
    (void)_til_str_lits[208];
    (void)_til_str_lits[208];
    assert_eq__Str(hoisted__Str_6776, &_til_str_lits[207], &_til_str_lits[208]);
    Str_delete(hoisted__Str_6776, 1);
    Str_delete(&_til_str_lits[207], (Bool){0});
    Str_delete(&_til_str_lits[208], (Bool){0});
    Str *hoisted__Str_6779 = F32_to_str(v.z);
    (void)hoisted__Str_6779;
    (void)_til_str_lits[209];
    (void)_til_str_lits[209];
    (void)_til_str_lits[210];
    (void)_til_str_lits[210];
    assert_eq__Str(hoisted__Str_6779, &_til_str_lits[209], &_til_str_lits[210]);
    Str_delete(hoisted__Str_6779, 1);
    Str_delete(&_til_str_lits[209], (Bool){0});
    Str_delete(&_til_str_lits[210], (Bool){0});
    CfVec3f_delete(&v, (Bool){0});
}

Color *Color_Red() {
    Color *r = malloc(sizeof(Color));
    *r = (Color){ .tag = Color_TAG_Red };
    return r;
}
Color *Color_Green() {
    Color *r = malloc(sizeof(Color));
    *r = (Color){ .tag = Color_TAG_Green };
    return r;
}
Color *Color_Blue() {
    Color *r = malloc(sizeof(Color));
    *r = (Color){ .tag = Color_TAG_Blue };
    return r;
}
Bool Color_eq(Color * self, Color * other) {
    U32 hoisted__U32_6782 = 1;
    (void)hoisted__U32_6782;
    Bool hoisted__Bool_6783 = ((Bool)((((Color *)(self))->tag) == (((Color *)(other))->tag)));
    (void)hoisted__Bool_6783;
    return hoisted__Bool_6783;
    __builtin_unreachable();
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_6791 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_6791;
    if (hoisted__Bool_6791) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
        return _r; }
    }
    Bool hoisted__Bool_6792 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_6792;
    if (hoisted__Bool_6792) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
        return _r; }
    }
    Bool hoisted__Bool_6793 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_6793;
    if (hoisted__Bool_6793) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
        return _r; }
    }
    static Str hoisted__Str_6794 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6794;
    UNREACHABLE(&hoisted__Str_6794);
    Str_delete(&hoisted__Str_6794, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
    __builtin_unreachable();
}

USize Color_size(void) {
    U32 hoisted__U32_6795 = 1;
    (void)hoisted__U32_6795;
    return hoisted__U32_6795;
    __builtin_unreachable();
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_6796 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_6796;
    (void)_til_str_lits[214];
    (void)_til_str_lits[214];
    assert(hoisted__Bool_6796, &_til_str_lits[214]);
    Str_delete(&_til_str_lits[214], (Bool){0});
    Bool hoisted__Bool_6798 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_6798;
    Bool hoisted__Bool_6799 = ((Bool)(!(hoisted__Bool_6798)));
    (void)hoisted__Bool_6799;
    (void)_til_str_lits[215];
    (void)_til_str_lits[215];
    assert(hoisted__Bool_6799, &_til_str_lits[215]);
    Str_delete(&_til_str_lits[215], (Bool){0});
}

Token *Token_Num(I64 * val) {
    Token *r = malloc(sizeof(Token));
    r->tag = Token_TAG_Num;
    r->data.Num = *val;
    return r;
}
Token *Token_Name(Str * val) {
    Token *r = malloc(sizeof(Token));
    r->tag = Token_TAG_Name;
    r->data.Name = *val;
    if (val->cap != TIL_CAP_LIT) { free(val); }
    return r;
}
Token *Token_Eof() {
    Token *r = malloc(sizeof(Token));
    r->tag = Token_TAG_Eof;
    return r;
}
void Token_delete(Token * self, Bool call_free) {
    U32 hoisted__U32_6824 = 1;
    (void)hoisted__U32_6824;
    Bool hoisted__Bool_6825 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    (void)hoisted__Bool_6825;
    if (hoisted__Bool_6825) {
        I64 *hoisted__I64_6820 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        (void)hoisted__I64_6820;
        (void)hoisted__I64_6820;
        Bool hoisted__Bool_6821 = 0;
        (void)hoisted__Bool_6821;
        I64_delete(hoisted__I64_6820, hoisted__Bool_6821);
    }
    U32 hoisted__U32_6826 = 1;
    (void)hoisted__U32_6826;
    Bool hoisted__Bool_6827 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Name}))->tag)));
    (void)hoisted__Bool_6827;
    if (hoisted__Bool_6827) {
        Str *hoisted__Str_6822 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        (void)hoisted__Str_6822;
        (void)hoisted__Str_6822;
        Bool hoisted__Bool_6823 = 0;
        (void)hoisted__Bool_6823;
        Str_delete(hoisted__Str_6822, hoisted__Bool_6823);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    U32 hoisted__U32_6855 = 1;
    (void)hoisted__U32_6855;
    Bool hoisted__Bool_6856 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    (void)hoisted__Bool_6856;
    if (hoisted__Bool_6856) {
        I64 *_clone_payload_Num_0 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_6852 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_6852;
        return hoisted__Token_6852;
    }
    U32 hoisted__U32_6857 = 1;
    (void)hoisted__U32_6857;
    Bool hoisted__Bool_6858 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Name}))->tag)));
    (void)hoisted__Bool_6858;
    if (hoisted__Bool_6858) {
        Str *_clone_payload_Name_1 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_6853 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_6853;
        Token *hoisted__Token_6854 = Token_Name(hoisted__Str_6853);
        (void)hoisted__Token_6854;
        return hoisted__Token_6854;
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
    __builtin_unreachable();
}

USize Token_size(void) {
    U32 hoisted__U32_6859 = 24;
    (void)hoisted__U32_6859;
    return hoisted__U32_6859;
    __builtin_unreachable();
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_6861 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_6861;
    (void)_til_str_lits[218];
    (void)_til_str_lits[218];
    assert(hoisted__Bool_6861, &_til_str_lits[218]);
    Str_delete(&_til_str_lits[218], (Bool){0});
    Bool hoisted__Bool_6863 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag));
    (void)hoisted__Bool_6863;
    Bool hoisted__Bool_6864 = ((Bool)(!(hoisted__Bool_6863)));
    (void)hoisted__Bool_6864;
    (void)_til_str_lits[219];
    (void)_til_str_lits[219];
    assert(hoisted__Bool_6864, &_til_str_lits[219]);
    Str_delete(&_til_str_lits[219], (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_6866 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_6866;
    (void)_til_str_lits[220];
    (void)_til_str_lits[220];
    assert(hoisted__Bool_6866, &_til_str_lits[220]);
    Str_delete(&_til_str_lits[220], (Bool){0});
    Bool hoisted__Bool_6868 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_6868;
    Bool hoisted__Bool_6869 = ((Bool)(!(hoisted__Bool_6868)));
    (void)hoisted__Bool_6869;
    (void)_til_str_lits[221];
    (void)_til_str_lits[221];
    assert(hoisted__Bool_6869, &_til_str_lits[221]);
    Str_delete(&_til_str_lits[221], (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_6873 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_6873;
    (void)_til_str_lits[222];
    (void)_til_str_lits[222];
    assert(hoisted__Bool_6873, &_til_str_lits[222]);
    Str_delete(&_til_str_lits[222], (Bool){0});
    Bool hoisted__Bool_6875 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag));
    (void)hoisted__Bool_6875;
    Bool hoisted__Bool_6876 = ((Bool)(!(hoisted__Bool_6875)));
    (void)hoisted__Bool_6876;
    (void)_til_str_lits[223];
    (void)_til_str_lits[223];
    assert(hoisted__Bool_6876, &_til_str_lits[223]);
    Str_delete(&_til_str_lits[223], (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_6946 = ((Bool)(a != b));
    (void)hoisted__Bool_6946;
    if (hoisted__Bool_6946) {
        U32 hoisted__U32_6935 = 5;
        (void)hoisted__U32_6935;
        Array__Str *_va_Array_185 = Array__Str_new(hoisted__U32_6935);
        (void)_va_Array_185;
        I64 _va_Array_185_ek = 0;
        (void)_va_Array_185_ek;
        U32 hoisted__U32_6936 = 0;
        (void)hoisted__U32_6936;
        (void)_til_str_lits[224];
        (void)_til_str_lits[224];
        Array__Str_set(_va_Array_185, hoisted__U32_6936, &_til_str_lits[224], &_va_Array_185_ek);
        U32 hoisted__U32_6938 = 1;
        (void)hoisted__U32_6938;
        Str *hoisted__Str_6939 = I64_to_str(a);
        (void)hoisted__Str_6939;
        Array__Str_set(_va_Array_185, hoisted__U32_6938, hoisted__Str_6939, &_va_Array_185_ek);
        U32 hoisted__U32_6940 = 2;
        (void)hoisted__U32_6940;
        (void)_til_str_lits[225];
        (void)_til_str_lits[225];
        Array__Str_set(_va_Array_185, hoisted__U32_6940, &_til_str_lits[225], &_va_Array_185_ek);
        U32 hoisted__U32_6942 = 3;
        (void)hoisted__U32_6942;
        Str *hoisted__Str_6943 = I64_to_str(b);
        (void)hoisted__Str_6943;
        Array__Str_set(_va_Array_185, hoisted__U32_6942, hoisted__Str_6943, &_va_Array_185_ek);
        U32 hoisted__U32_6944 = 4;
        (void)hoisted__U32_6944;
        (void)_til_str_lits[226];
        (void)_til_str_lits[226];
        Array__Str_set(_va_Array_185, hoisted__U32_6944, &_til_str_lits[226], &_va_Array_185_ek);
        panic(_va_Array_185, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_6958 = Str_neq(a, b);
    (void)hoisted__Bool_6958;
    if (hoisted__Bool_6958) {
        U32 hoisted__U32_6947 = 5;
        (void)hoisted__U32_6947;
        Array__Str *_va_Array_186 = Array__Str_new(hoisted__U32_6947);
        (void)_va_Array_186;
        I64 _va_Array_186_ek = 0;
        (void)_va_Array_186_ek;
        U32 hoisted__U32_6948 = 0;
        (void)hoisted__U32_6948;
        (void)_til_str_lits[224];
        (void)_til_str_lits[224];
        Array__Str_set(_va_Array_186, hoisted__U32_6948, &_til_str_lits[224], &_va_Array_186_ek);
        U32 hoisted__U32_6950 = 1;
        (void)hoisted__U32_6950;
        Str *hoisted__Str_6951 = Str_to_str(a);
        (void)hoisted__Str_6951;
        Array__Str_set(_va_Array_186, hoisted__U32_6950, hoisted__Str_6951, &_va_Array_186_ek);
        U32 hoisted__U32_6952 = 2;
        (void)hoisted__U32_6952;
        (void)_til_str_lits[225];
        (void)_til_str_lits[225];
        Array__Str_set(_va_Array_186, hoisted__U32_6952, &_til_str_lits[225], &_va_Array_186_ek);
        U32 hoisted__U32_6954 = 3;
        (void)hoisted__U32_6954;
        Str *hoisted__Str_6955 = Str_to_str(b);
        (void)hoisted__Str_6955;
        Array__Str_set(_va_Array_186, hoisted__U32_6954, hoisted__Str_6955, &_va_Array_186_ek);
        U32 hoisted__U32_6956 = 4;
        (void)hoisted__U32_6956;
        (void)_til_str_lits[226];
        (void)_til_str_lits[226];
        Array__Str_set(_va_Array_186, hoisted__U32_6956, &_til_str_lits[226], &_va_Array_186_ek);
        panic(_va_Array_186, loc);
    }
}

USize Str_len_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return Str_len(_a0);
}
static __attribute__((unused)) TilClosure Str_len_dyn__til_closure = { (void *)Str_len_dyn, NULL, NULL };
I64 Str_cmp_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Str_cmp(_a0, _a1);
}
static __attribute__((unused)) TilClosure Str_cmp_dyn__til_closure = { (void *)Str_cmp_dyn, NULL, NULL };
Bool Str_eq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Str_eq(_a0, _a1);
}
static __attribute__((unused)) TilClosure Str_eq_dyn__til_closure = { (void *)Str_eq_dyn, NULL, NULL };
void *Str_with_capacity_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Str_with_capacity(*(USize *)_a0);
}
static __attribute__((unused)) TilClosure Str_with_capacity_dyn__til_closure = { (void *)Str_with_capacity_dyn, NULL, NULL };
void Str_push_str_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    Str_push_str(_a0, _a1);
}
static __attribute__((unused)) TilClosure Str_push_str_dyn__til_closure = { (void *)Str_push_str_dyn, NULL, NULL };
void *Str_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Str_clone(_a0);
}
static __attribute__((unused)) TilClosure Str_clone_dyn__til_closure = { (void *)Str_clone_dyn, NULL, NULL };
void *Str_to_str_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Str_to_str(_a0);
}
static __attribute__((unused)) TilClosure Str_to_str_dyn__til_closure = { (void *)Str_to_str_dyn, NULL, NULL };
void Str_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Str_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Str_delete_dyn__til_closure = { (void *)Str_delete_dyn, NULL, NULL };
U64 Str_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Str_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure Str_hash_dyn__til_closure = { (void *)Str_hash_dyn, NULL, NULL };
USize Str_size_dyn(void *til_env) {
    (void)til_env;
    return Str_size();
}
static __attribute__((unused)) TilClosure Str_size_dyn__til_closure = { (void *)Str_size_dyn, NULL, NULL };
Bool Str_neq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Str_neq(_a0, _a1);
}
static __attribute__((unused)) TilClosure Str_neq_dyn__til_closure = { (void *)Str_neq_dyn, NULL, NULL };
void *OutOfBounds_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)OutOfBounds_clone(_a0);
}
static __attribute__((unused)) TilClosure OutOfBounds_clone_dyn__til_closure = { (void *)OutOfBounds_clone_dyn, NULL, NULL };
void OutOfBounds_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    OutOfBounds_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure OutOfBounds_delete_dyn__til_closure = { (void *)OutOfBounds_delete_dyn, NULL, NULL };
U64 OutOfBounds_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return OutOfBounds_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure OutOfBounds_hash_dyn__til_closure = { (void *)OutOfBounds_hash_dyn, NULL, NULL };
USize OutOfBounds_size_dyn(void *til_env) {
    (void)til_env;
    return OutOfBounds_size();
}
static __attribute__((unused)) TilClosure OutOfBounds_size_dyn__til_closure = { (void *)OutOfBounds_size_dyn, NULL, NULL };
void *KeyNotFound_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)KeyNotFound_clone(_a0);
}
static __attribute__((unused)) TilClosure KeyNotFound_clone_dyn__til_closure = { (void *)KeyNotFound_clone_dyn, NULL, NULL };
void KeyNotFound_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    KeyNotFound_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure KeyNotFound_delete_dyn__til_closure = { (void *)KeyNotFound_delete_dyn, NULL, NULL };
U64 KeyNotFound_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return KeyNotFound_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure KeyNotFound_hash_dyn__til_closure = { (void *)KeyNotFound_hash_dyn, NULL, NULL };
USize KeyNotFound_size_dyn(void *til_env) {
    (void)til_env;
    return KeyNotFound_size();
}
static __attribute__((unused)) TilClosure KeyNotFound_size_dyn__til_closure = { (void *)KeyNotFound_size_dyn, NULL, NULL };
void *Array__Str_new_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Array__Str_new(*(USize *)_a0);
}
static __attribute__((unused)) TilClosure Array__Str_new_dyn__til_closure = { (void *)Array__Str_new_dyn, NULL, NULL };
USize Array__Str_len_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return Array__Str_len(_a0);
}
static __attribute__((unused)) TilClosure Array__Str_len_dyn__til_closure = { (void *)Array__Str_len_dyn, NULL, NULL };
void *Array__Str_unsafe_get_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return (void *)Array__Str_unsafe_get(_a0, _a1);
}
static __attribute__((unused)) TilClosure Array__Str_unsafe_get_dyn__til_closure = { (void *)Array__Str_unsafe_get_dyn, NULL, NULL };
void Array__Str_unsafe_set_dyn(void *til_env, void *_a0, void *_a1, void *_a2) {
    (void)til_env;
    Array__Str_unsafe_set(_a0, *(USize *)_a1, _a2);
}
static __attribute__((unused)) TilClosure Array__Str_unsafe_set_dyn__til_closure = { (void *)Array__Str_unsafe_set_dyn, NULL, NULL };
void Array__Str_set_dyn(void *til_env, void *_a0, void *_a1, void *_a2, void *_a3) {
    (void)til_env;
    Array__Str_set(_a0, *(USize *)_a1, _a2, _a3);
}
static __attribute__((unused)) TilClosure Array__Str_set_dyn__til_closure = { (void *)Array__Str_set_dyn, NULL, NULL };
void Array__Str_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Array__Str_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Array__Str_delete_dyn__til_closure = { (void *)Array__Str_delete_dyn, NULL, NULL };
void *Array__Str_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Array__Str_clone(_a0);
}
static __attribute__((unused)) TilClosure Array__Str_clone_dyn__til_closure = { (void *)Array__Str_clone_dyn, NULL, NULL };
USize Array__Str_size_dyn(void *til_env) {
    (void)til_env;
    return Array__Str_size();
}
static __attribute__((unused)) TilClosure Array__Str_size_dyn__til_closure = { (void *)Array__Str_size_dyn, NULL, NULL };
void *Vec__Str_new_dyn(void *til_env) {
    (void)til_env;
    return (void *)Vec__Str_new();
}
static __attribute__((unused)) TilClosure Vec__Str_new_dyn__til_closure = { (void *)Vec__Str_new_dyn, NULL, NULL };
void Vec__Str_clear_dyn(void *til_env, void *_a0) {
    (void)til_env;
    Vec__Str_clear(_a0);
}
static __attribute__((unused)) TilClosure Vec__Str_clear_dyn__til_closure = { (void *)Vec__Str_clear_dyn, NULL, NULL };
void Vec__Str_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Vec__Str_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Vec__Str_delete_dyn__til_closure = { (void *)Vec__Str_delete_dyn, NULL, NULL };
void *Vec__Str_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Vec__Str_clone(_a0);
}
static __attribute__((unused)) TilClosure Vec__Str_clone_dyn__til_closure = { (void *)Vec__Str_clone_dyn, NULL, NULL };
USize Vec__Str_size_dyn(void *til_env) {
    (void)til_env;
    return Vec__Str_size();
}
static __attribute__((unused)) TilClosure Vec__Str_size_dyn__til_closure = { (void *)Vec__Str_size_dyn, NULL, NULL };
USize Dynamic_size_dyn(void *til_env) {
    (void)til_env;
    return Dynamic_size();
}
static __attribute__((unused)) TilClosure Dynamic_size_dyn__til_closure = { (void *)Dynamic_size_dyn, NULL, NULL };
void *Dynamic_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Dynamic_clone(_a0);
}
static __attribute__((unused)) TilClosure Dynamic_clone_dyn__til_closure = { (void *)Dynamic_clone_dyn, NULL, NULL };
void Dynamic_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Dynamic_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Dynamic_delete_dyn__til_closure = { (void *)Dynamic_delete_dyn, NULL, NULL };
I64 U8_cmp_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U8_cmp(*(U8 *)_a0, *(U8 *)_a1);
}
static __attribute__((unused)) TilClosure U8_cmp_dyn__til_closure = { (void *)U8_cmp_dyn, NULL, NULL };
void *U8_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    U8 *_r = malloc(sizeof(U8)); *_r = U8_clone(_a0); return _r;
}
static __attribute__((unused)) TilClosure U8_clone_dyn__til_closure = { (void *)U8_clone_dyn, NULL, NULL };
void U8_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    U8_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure U8_delete_dyn__til_closure = { (void *)U8_delete_dyn, NULL, NULL };
USize U8_size_dyn(void *til_env) {
    (void)til_env;
    return U8_size();
}
static __attribute__((unused)) TilClosure U8_size_dyn__til_closure = { (void *)U8_size_dyn, NULL, NULL };
U64 U8_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U8_hash(*(U8 *)_a0, _a1);
}
static __attribute__((unused)) TilClosure U8_hash_dyn__til_closure = { (void *)U8_hash_dyn, NULL, NULL };
I64 U32_cmp_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U32_cmp(*(U32 *)_a0, *(U32 *)_a1);
}
static __attribute__((unused)) TilClosure U32_cmp_dyn__til_closure = { (void *)U32_cmp_dyn, NULL, NULL };
void *U32_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    U32 *_r = malloc(sizeof(U32)); *_r = U32_clone(_a0); return _r;
}
static __attribute__((unused)) TilClosure U32_clone_dyn__til_closure = { (void *)U32_clone_dyn, NULL, NULL };
void U32_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    U32_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure U32_delete_dyn__til_closure = { (void *)U32_delete_dyn, NULL, NULL };
USize U32_size_dyn(void *til_env) {
    (void)til_env;
    return U32_size();
}
static __attribute__((unused)) TilClosure U32_size_dyn__til_closure = { (void *)U32_size_dyn, NULL, NULL };
U64 U32_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U32_hash(*(U32 *)_a0, _a1);
}
static __attribute__((unused)) TilClosure U32_hash_dyn__til_closure = { (void *)U32_hash_dyn, NULL, NULL };
void *U64_to_str_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)U64_to_str(*(U64 *)_a0);
}
static __attribute__((unused)) TilClosure U64_to_str_dyn__til_closure = { (void *)U64_to_str_dyn, NULL, NULL };
I64 U64_cmp_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U64_cmp(*(U64 *)_a0, *(U64 *)_a1);
}
static __attribute__((unused)) TilClosure U64_cmp_dyn__til_closure = { (void *)U64_cmp_dyn, NULL, NULL };
void *U64_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    U64 *_r = malloc(sizeof(U64)); *_r = U64_clone(_a0); return _r;
}
static __attribute__((unused)) TilClosure U64_clone_dyn__til_closure = { (void *)U64_clone_dyn, NULL, NULL };
void U64_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    U64_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure U64_delete_dyn__til_closure = { (void *)U64_delete_dyn, NULL, NULL };
USize U64_size_dyn(void *til_env) {
    (void)til_env;
    return U64_size();
}
static __attribute__((unused)) TilClosure U64_size_dyn__til_closure = { (void *)U64_size_dyn, NULL, NULL };
U64 U64_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U64_hash(*(U64 *)_a0, _a1);
}
static __attribute__((unused)) TilClosure U64_hash_dyn__til_closure = { (void *)U64_hash_dyn, NULL, NULL };
I64 I8_cmp_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I8_cmp(*(I8 *)_a0, *(I8 *)_a1);
}
static __attribute__((unused)) TilClosure I8_cmp_dyn__til_closure = { (void *)I8_cmp_dyn, NULL, NULL };
void *I8_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    I8 *_r = malloc(sizeof(I8)); *_r = I8_clone(_a0); return _r;
}
static __attribute__((unused)) TilClosure I8_clone_dyn__til_closure = { (void *)I8_clone_dyn, NULL, NULL };
void I8_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    I8_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure I8_delete_dyn__til_closure = { (void *)I8_delete_dyn, NULL, NULL };
USize I8_size_dyn(void *til_env) {
    (void)til_env;
    return I8_size();
}
static __attribute__((unused)) TilClosure I8_size_dyn__til_closure = { (void *)I8_size_dyn, NULL, NULL };
U64 I8_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I8_hash(*(I8 *)_a0, _a1);
}
static __attribute__((unused)) TilClosure I8_hash_dyn__til_closure = { (void *)I8_hash_dyn, NULL, NULL };
I64 I32_cmp_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I32_cmp(*(I32 *)_a0, *(I32 *)_a1);
}
static __attribute__((unused)) TilClosure I32_cmp_dyn__til_closure = { (void *)I32_cmp_dyn, NULL, NULL };
void *I32_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    I32 *_r = malloc(sizeof(I32)); *_r = I32_clone(_a0); return _r;
}
static __attribute__((unused)) TilClosure I32_clone_dyn__til_closure = { (void *)I32_clone_dyn, NULL, NULL };
void I32_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    I32_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure I32_delete_dyn__til_closure = { (void *)I32_delete_dyn, NULL, NULL };
USize I32_size_dyn(void *til_env) {
    (void)til_env;
    return I32_size();
}
static __attribute__((unused)) TilClosure I32_size_dyn__til_closure = { (void *)I32_size_dyn, NULL, NULL };
U64 I32_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I32_hash(*(I32 *)_a0, _a1);
}
static __attribute__((unused)) TilClosure I32_hash_dyn__til_closure = { (void *)I32_hash_dyn, NULL, NULL };
void *I64_to_str_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)I64_to_str(*(I64 *)_a0);
}
static __attribute__((unused)) TilClosure I64_to_str_dyn__til_closure = { (void *)I64_to_str_dyn, NULL, NULL };
I64 I64_cmp_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I64_cmp(*(I64 *)_a0, *(I64 *)_a1);
}
static __attribute__((unused)) TilClosure I64_cmp_dyn__til_closure = { (void *)I64_cmp_dyn, NULL, NULL };
void *I64_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    I64 *_r = malloc(sizeof(I64)); *_r = I64_clone(_a0); return _r;
}
static __attribute__((unused)) TilClosure I64_clone_dyn__til_closure = { (void *)I64_clone_dyn, NULL, NULL };
void I64_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    I64_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure I64_delete_dyn__til_closure = { (void *)I64_delete_dyn, NULL, NULL };
USize I64_size_dyn(void *til_env) {
    (void)til_env;
    return I64_size();
}
static __attribute__((unused)) TilClosure I64_size_dyn__til_closure = { (void *)I64_size_dyn, NULL, NULL };
U64 I64_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I64_hash(*(I64 *)_a0, _a1);
}
static __attribute__((unused)) TilClosure I64_hash_dyn__til_closure = { (void *)I64_hash_dyn, NULL, NULL };
void *F32_to_str_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)F32_to_str(*(F32 *)_a0);
}
static __attribute__((unused)) TilClosure F32_to_str_dyn__til_closure = { (void *)F32_to_str_dyn, NULL, NULL };
I64 F32_cmp_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return F32_cmp(*(F32 *)_a0, *(F32 *)_a1);
}
static __attribute__((unused)) TilClosure F32_cmp_dyn__til_closure = { (void *)F32_cmp_dyn, NULL, NULL };
void *F32_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    F32 *_r = malloc(sizeof(F32)); *_r = F32_clone(_a0); return _r;
}
static __attribute__((unused)) TilClosure F32_clone_dyn__til_closure = { (void *)F32_clone_dyn, NULL, NULL };
void F32_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    F32_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure F32_delete_dyn__til_closure = { (void *)F32_delete_dyn, NULL, NULL };
USize F32_size_dyn(void *til_env) {
    (void)til_env;
    return F32_size();
}
static __attribute__((unused)) TilClosure F32_size_dyn__til_closure = { (void *)F32_size_dyn, NULL, NULL };
U64 F32_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return F32_hash(*(F32 *)_a0, _a1);
}
static __attribute__((unused)) TilClosure F32_hash_dyn__til_closure = { (void *)F32_hash_dyn, NULL, NULL };
I64 Bool_cmp_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Bool_cmp(*(Bool *)_a0, *(Bool *)_a1);
}
static __attribute__((unused)) TilClosure Bool_cmp_dyn__til_closure = { (void *)Bool_cmp_dyn, NULL, NULL };
void *Bool_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    Bool *_r = malloc(sizeof(Bool)); *_r = Bool_clone(_a0); return _r;
}
static __attribute__((unused)) TilClosure Bool_clone_dyn__til_closure = { (void *)Bool_clone_dyn, NULL, NULL };
void Bool_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Bool_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Bool_delete_dyn__til_closure = { (void *)Bool_delete_dyn, NULL, NULL };
USize Bool_size_dyn(void *til_env) {
    (void)til_env;
    return Bool_size();
}
static __attribute__((unused)) TilClosure Bool_size_dyn__til_closure = { (void *)Bool_size_dyn, NULL, NULL };
U64 Bool_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Bool_hash(*(Bool *)_a0, _a1);
}
static __attribute__((unused)) TilClosure Bool_hash_dyn__til_closure = { (void *)Bool_hash_dyn, NULL, NULL };
Bool Primitive_eq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Primitive_eq(_a0, _a1);
}
static __attribute__((unused)) TilClosure Primitive_eq_dyn__til_closure = { (void *)Primitive_eq_dyn, NULL, NULL };
void Primitive_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Primitive_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Primitive_delete_dyn__til_closure = { (void *)Primitive_delete_dyn, NULL, NULL };
void *Primitive_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Primitive_clone(_a0);
}
static __attribute__((unused)) TilClosure Primitive_clone_dyn__til_closure = { (void *)Primitive_clone_dyn, NULL, NULL };
USize Primitive_size_dyn(void *til_env) {
    (void)til_env;
    return Primitive_size();
}
static __attribute__((unused)) TilClosure Primitive_size_dyn__til_closure = { (void *)Primitive_size_dyn, NULL, NULL };
void *Type_Unknown_dyn(void *til_env) {
    (void)til_env;
    return (void *)Type_Unknown();
}
static __attribute__((unused)) TilClosure Type_Unknown_dyn__til_closure = { (void *)Type_Unknown_dyn, NULL, NULL };
void *Type_None_dyn(void *til_env) {
    (void)til_env;
    return (void *)Type_None();
}
static __attribute__((unused)) TilClosure Type_None_dyn__til_closure = { (void *)Type_None_dyn, NULL, NULL };
void *Type_Struct_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Type_Struct(_a0);
}
static __attribute__((unused)) TilClosure Type_Struct_dyn__til_closure = { (void *)Type_Struct_dyn, NULL, NULL };
void *Type_StructDef_dyn(void *til_env) {
    (void)til_env;
    return (void *)Type_StructDef();
}
static __attribute__((unused)) TilClosure Type_StructDef_dyn__til_closure = { (void *)Type_StructDef_dyn, NULL, NULL };
void *Type_Enum_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Type_Enum(_a0);
}
static __attribute__((unused)) TilClosure Type_Enum_dyn__til_closure = { (void *)Type_Enum_dyn, NULL, NULL };
void *Type_EnumDef_dyn(void *til_env) {
    (void)til_env;
    return (void *)Type_EnumDef();
}
static __attribute__((unused)) TilClosure Type_EnumDef_dyn__til_closure = { (void *)Type_EnumDef_dyn, NULL, NULL };
void *Type_FuncDef_dyn(void *til_env) {
    (void)til_env;
    return (void *)Type_FuncDef();
}
static __attribute__((unused)) TilClosure Type_FuncDef_dyn__til_closure = { (void *)Type_FuncDef_dyn, NULL, NULL };
void *Type_FuncPtr_dyn(void *til_env) {
    (void)til_env;
    return (void *)Type_FuncPtr();
}
static __attribute__((unused)) TilClosure Type_FuncPtr_dyn__til_closure = { (void *)Type_FuncPtr_dyn, NULL, NULL };
void *Type_Dynamic_dyn(void *til_env) {
    (void)til_env;
    return (void *)Type_Dynamic();
}
static __attribute__((unused)) TilClosure Type_Dynamic_dyn__til_closure = { (void *)Type_Dynamic_dyn, NULL, NULL };
void *Type_Custom_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Type_Custom(_a0);
}
static __attribute__((unused)) TilClosure Type_Custom_dyn__til_closure = { (void *)Type_Custom_dyn, NULL, NULL };
void *Type_Primitive_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Type_Primitive(_a0);
}
static __attribute__((unused)) TilClosure Type_Primitive_dyn__til_closure = { (void *)Type_Primitive_dyn, NULL, NULL };
void *Type_FuncPtrSig_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Type_FuncPtrSig(_a0);
}
static __attribute__((unused)) TilClosure Type_FuncPtrSig_dyn__til_closure = { (void *)Type_FuncPtrSig_dyn, NULL, NULL };
void *Type_Body_dyn(void *til_env) {
    (void)til_env;
    return (void *)Type_Body();
}
static __attribute__((unused)) TilClosure Type_Body_dyn__til_closure = { (void *)Type_Body_dyn, NULL, NULL };
void Type_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Type_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Type_delete_dyn__til_closure = { (void *)Type_delete_dyn, NULL, NULL };
void *Type_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Type_clone(_a0);
}
static __attribute__((unused)) TilClosure Type_clone_dyn__til_closure = { (void *)Type_clone_dyn, NULL, NULL };
USize Type_size_dyn(void *til_env) {
    (void)til_env;
    return Type_size();
}
static __attribute__((unused)) TilClosure Type_size_dyn__til_closure = { (void *)Type_size_dyn, NULL, NULL };
Bool FuncType_eq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return FuncType_eq(_a0, _a1);
}
static __attribute__((unused)) TilClosure FuncType_eq_dyn__til_closure = { (void *)FuncType_eq_dyn, NULL, NULL };
void FuncType_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    FuncType_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure FuncType_delete_dyn__til_closure = { (void *)FuncType_delete_dyn, NULL, NULL };
void *FuncType_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)FuncType_clone(_a0);
}
static __attribute__((unused)) TilClosure FuncType_clone_dyn__til_closure = { (void *)FuncType_clone_dyn, NULL, NULL };
USize FuncType_size_dyn(void *til_env) {
    (void)til_env;
    return FuncType_size();
}
static __attribute__((unused)) TilClosure FuncType_size_dyn__til_closure = { (void *)FuncType_size_dyn, NULL, NULL };
Bool OwnType_eq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return OwnType_eq(_a0, _a1);
}
static __attribute__((unused)) TilClosure OwnType_eq_dyn__til_closure = { (void *)OwnType_eq_dyn, NULL, NULL };
void OwnType_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    OwnType_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure OwnType_delete_dyn__til_closure = { (void *)OwnType_delete_dyn, NULL, NULL };
void *OwnType_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)OwnType_clone(_a0);
}
static __attribute__((unused)) TilClosure OwnType_clone_dyn__til_closure = { (void *)OwnType_clone_dyn, NULL, NULL };
USize OwnType_size_dyn(void *til_env) {
    (void)til_env;
    return OwnType_size();
}
static __attribute__((unused)) TilClosure OwnType_size_dyn__til_closure = { (void *)OwnType_size_dyn, NULL, NULL };
Bool GcStorage_eq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return GcStorage_eq(_a0, _a1);
}
static __attribute__((unused)) TilClosure GcStorage_eq_dyn__til_closure = { (void *)GcStorage_eq_dyn, NULL, NULL };
void GcStorage_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    GcStorage_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure GcStorage_delete_dyn__til_closure = { (void *)GcStorage_delete_dyn, NULL, NULL };
void *GcStorage_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)GcStorage_clone(_a0);
}
static __attribute__((unused)) TilClosure GcStorage_clone_dyn__til_closure = { (void *)GcStorage_clone_dyn, NULL, NULL };
USize GcStorage_size_dyn(void *til_env) {
    (void)til_env;
    return GcStorage_size();
}
static __attribute__((unused)) TilClosure GcStorage_size_dyn__til_closure = { (void *)GcStorage_size_dyn, NULL, NULL };
void *Declaration_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Declaration_clone(_a0);
}
static __attribute__((unused)) TilClosure Declaration_clone_dyn__til_closure = { (void *)Declaration_clone_dyn, NULL, NULL };
void Declaration_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Declaration_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Declaration_delete_dyn__til_closure = { (void *)Declaration_delete_dyn, NULL, NULL };
USize Declaration_size_dyn(void *til_env) {
    (void)til_env;
    return Declaration_size();
}
static __attribute__((unused)) TilClosure Declaration_size_dyn__til_closure = { (void *)Declaration_size_dyn, NULL, NULL };
void *FunctionDef_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)FunctionDef_clone(_a0);
}
static __attribute__((unused)) TilClosure FunctionDef_clone_dyn__til_closure = { (void *)FunctionDef_clone_dyn, NULL, NULL };
void FunctionDef_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    FunctionDef_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure FunctionDef_delete_dyn__til_closure = { (void *)FunctionDef_delete_dyn, NULL, NULL };
U64 FunctionDef_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return FunctionDef_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure FunctionDef_hash_dyn__til_closure = { (void *)FunctionDef_hash_dyn, NULL, NULL };
USize FunctionDef_size_dyn(void *til_env) {
    (void)til_env;
    return FunctionDef_size();
}
static __attribute__((unused)) TilClosure FunctionDef_size_dyn__til_closure = { (void *)FunctionDef_size_dyn, NULL, NULL };
void *FCallData_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)FCallData_clone(_a0);
}
static __attribute__((unused)) TilClosure FCallData_clone_dyn__til_closure = { (void *)FCallData_clone_dyn, NULL, NULL };
void FCallData_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    FCallData_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure FCallData_delete_dyn__til_closure = { (void *)FCallData_delete_dyn, NULL, NULL };
U64 FCallData_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return FCallData_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure FCallData_hash_dyn__til_closure = { (void *)FCallData_hash_dyn, NULL, NULL };
USize FCallData_size_dyn(void *til_env) {
    (void)til_env;
    return FCallData_size();
}
static __attribute__((unused)) TilClosure FCallData_size_dyn__til_closure = { (void *)FCallData_size_dyn, NULL, NULL };
void *LiteralNumData_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)LiteralNumData_clone(_a0);
}
static __attribute__((unused)) TilClosure LiteralNumData_clone_dyn__til_closure = { (void *)LiteralNumData_clone_dyn, NULL, NULL };
void LiteralNumData_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    LiteralNumData_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure LiteralNumData_delete_dyn__til_closure = { (void *)LiteralNumData_delete_dyn, NULL, NULL };
U64 LiteralNumData_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return LiteralNumData_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure LiteralNumData_hash_dyn__til_closure = { (void *)LiteralNumData_hash_dyn, NULL, NULL };
USize LiteralNumData_size_dyn(void *til_env) {
    (void)til_env;
    return LiteralNumData_size();
}
static __attribute__((unused)) TilClosure LiteralNumData_size_dyn__til_closure = { (void *)LiteralNumData_size_dyn, NULL, NULL };
void *IdentData_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)IdentData_clone(_a0);
}
static __attribute__((unused)) TilClosure IdentData_clone_dyn__til_closure = { (void *)IdentData_clone_dyn, NULL, NULL };
void IdentData_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    IdentData_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure IdentData_delete_dyn__til_closure = { (void *)IdentData_delete_dyn, NULL, NULL };
U64 IdentData_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return IdentData_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure IdentData_hash_dyn__til_closure = { (void *)IdentData_hash_dyn, NULL, NULL };
USize IdentData_size_dyn(void *til_env) {
    (void)til_env;
    return IdentData_size();
}
static __attribute__((unused)) TilClosure IdentData_size_dyn__til_closure = { (void *)IdentData_size_dyn, NULL, NULL };
void *FieldAccessData_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)FieldAccessData_clone(_a0);
}
static __attribute__((unused)) TilClosure FieldAccessData_clone_dyn__til_closure = { (void *)FieldAccessData_clone_dyn, NULL, NULL };
void FieldAccessData_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    FieldAccessData_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure FieldAccessData_delete_dyn__til_closure = { (void *)FieldAccessData_delete_dyn, NULL, NULL };
U64 FieldAccessData_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return FieldAccessData_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure FieldAccessData_hash_dyn__til_closure = { (void *)FieldAccessData_hash_dyn, NULL, NULL };
USize FieldAccessData_size_dyn(void *til_env) {
    (void)til_env;
    return FieldAccessData_size();
}
static __attribute__((unused)) TilClosure FieldAccessData_size_dyn__til_closure = { (void *)FieldAccessData_size_dyn, NULL, NULL };
void *StructDef_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)StructDef_clone(_a0);
}
static __attribute__((unused)) TilClosure StructDef_clone_dyn__til_closure = { (void *)StructDef_clone_dyn, NULL, NULL };
void StructDef_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    StructDef_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure StructDef_delete_dyn__til_closure = { (void *)StructDef_delete_dyn, NULL, NULL };
USize StructDef_size_dyn(void *til_env) {
    (void)til_env;
    return StructDef_size();
}
static __attribute__((unused)) TilClosure StructDef_size_dyn__til_closure = { (void *)StructDef_size_dyn, NULL, NULL };
void *VariantDef_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)VariantDef_clone(_a0);
}
static __attribute__((unused)) TilClosure VariantDef_clone_dyn__til_closure = { (void *)VariantDef_clone_dyn, NULL, NULL };
void VariantDef_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    VariantDef_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure VariantDef_delete_dyn__til_closure = { (void *)VariantDef_delete_dyn, NULL, NULL };
U64 VariantDef_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return VariantDef_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure VariantDef_hash_dyn__til_closure = { (void *)VariantDef_hash_dyn, NULL, NULL };
USize VariantDef_size_dyn(void *til_env) {
    (void)til_env;
    return VariantDef_size();
}
static __attribute__((unused)) TilClosure VariantDef_size_dyn__til_closure = { (void *)VariantDef_size_dyn, NULL, NULL };
void *EnumDef_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)EnumDef_clone(_a0);
}
static __attribute__((unused)) TilClosure EnumDef_clone_dyn__til_closure = { (void *)EnumDef_clone_dyn, NULL, NULL };
void EnumDef_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    EnumDef_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure EnumDef_delete_dyn__til_closure = { (void *)EnumDef_delete_dyn, NULL, NULL };
USize EnumDef_size_dyn(void *til_env) {
    (void)til_env;
    return EnumDef_size();
}
static __attribute__((unused)) TilClosure EnumDef_size_dyn__til_closure = { (void *)EnumDef_size_dyn, NULL, NULL };
void *AssignData_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)AssignData_clone(_a0);
}
static __attribute__((unused)) TilClosure AssignData_clone_dyn__til_closure = { (void *)AssignData_clone_dyn, NULL, NULL };
void AssignData_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    AssignData_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure AssignData_delete_dyn__til_closure = { (void *)AssignData_delete_dyn, NULL, NULL };
U64 AssignData_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return AssignData_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure AssignData_hash_dyn__til_closure = { (void *)AssignData_hash_dyn, NULL, NULL };
USize AssignData_size_dyn(void *til_env) {
    (void)til_env;
    return AssignData_size();
}
static __attribute__((unused)) TilClosure AssignData_size_dyn__til_closure = { (void *)AssignData_size_dyn, NULL, NULL };
void *FieldAssignData_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)FieldAssignData_clone(_a0);
}
static __attribute__((unused)) TilClosure FieldAssignData_clone_dyn__til_closure = { (void *)FieldAssignData_clone_dyn, NULL, NULL };
void FieldAssignData_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    FieldAssignData_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure FieldAssignData_delete_dyn__til_closure = { (void *)FieldAssignData_delete_dyn, NULL, NULL };
U64 FieldAssignData_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return FieldAssignData_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure FieldAssignData_hash_dyn__til_closure = { (void *)FieldAssignData_hash_dyn, NULL, NULL };
USize FieldAssignData_size_dyn(void *til_env) {
    (void)til_env;
    return FieldAssignData_size();
}
static __attribute__((unused)) TilClosure FieldAssignData_size_dyn__til_closure = { (void *)FieldAssignData_size_dyn, NULL, NULL };
void *ForInData_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)ForInData_clone(_a0);
}
static __attribute__((unused)) TilClosure ForInData_clone_dyn__til_closure = { (void *)ForInData_clone_dyn, NULL, NULL };
void ForInData_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    ForInData_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure ForInData_delete_dyn__til_closure = { (void *)ForInData_delete_dyn, NULL, NULL };
U64 ForInData_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return ForInData_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure ForInData_hash_dyn__til_closure = { (void *)ForInData_hash_dyn, NULL, NULL };
USize ForInData_size_dyn(void *til_env) {
    (void)til_env;
    return ForInData_size();
}
static __attribute__((unused)) TilClosure ForInData_size_dyn__til_closure = { (void *)ForInData_size_dyn, NULL, NULL };
void *Literal_Str_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Literal_Str(_a0);
}
static __attribute__((unused)) TilClosure Literal_Str_dyn__til_closure = { (void *)Literal_Str_dyn, NULL, NULL };
void *Literal_Num_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Literal_Num(_a0);
}
static __attribute__((unused)) TilClosure Literal_Num_dyn__til_closure = { (void *)Literal_Num_dyn, NULL, NULL };
void *Literal_Bool_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Literal_Bool(_a0);
}
static __attribute__((unused)) TilClosure Literal_Bool_dyn__til_closure = { (void *)Literal_Bool_dyn, NULL, NULL };
void *Literal_Null_dyn(void *til_env) {
    (void)til_env;
    return (void *)Literal_Null();
}
static __attribute__((unused)) TilClosure Literal_Null_dyn__til_closure = { (void *)Literal_Null_dyn, NULL, NULL };
void *Literal_MapLit_dyn(void *til_env) {
    (void)til_env;
    return (void *)Literal_MapLit();
}
static __attribute__((unused)) TilClosure Literal_MapLit_dyn__til_closure = { (void *)Literal_MapLit_dyn, NULL, NULL };
void *Literal_SetLit_dyn(void *til_env) {
    (void)til_env;
    return (void *)Literal_SetLit();
}
static __attribute__((unused)) TilClosure Literal_SetLit_dyn__til_closure = { (void *)Literal_SetLit_dyn, NULL, NULL };
void Literal_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Literal_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Literal_delete_dyn__til_closure = { (void *)Literal_delete_dyn, NULL, NULL };
void *Literal_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Literal_clone(_a0);
}
static __attribute__((unused)) TilClosure Literal_clone_dyn__til_closure = { (void *)Literal_clone_dyn, NULL, NULL };
USize Literal_size_dyn(void *til_env) {
    (void)til_env;
    return Literal_size();
}
static __attribute__((unused)) TilClosure Literal_size_dyn__til_closure = { (void *)Literal_size_dyn, NULL, NULL };
void *MatchData_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)MatchData_clone(_a0);
}
static __attribute__((unused)) TilClosure MatchData_clone_dyn__til_closure = { (void *)MatchData_clone_dyn, NULL, NULL };
void MatchData_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    MatchData_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure MatchData_delete_dyn__til_closure = { (void *)MatchData_delete_dyn, NULL, NULL };
U64 MatchData_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return MatchData_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure MatchData_hash_dyn__til_closure = { (void *)MatchData_hash_dyn, NULL, NULL };
USize MatchData_size_dyn(void *til_env) {
    (void)til_env;
    return MatchData_size();
}
static __attribute__((unused)) TilClosure MatchData_size_dyn__til_closure = { (void *)MatchData_size_dyn, NULL, NULL };
void *CaptureBlockData_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)CaptureBlockData_clone(_a0);
}
static __attribute__((unused)) TilClosure CaptureBlockData_clone_dyn__til_closure = { (void *)CaptureBlockData_clone_dyn, NULL, NULL };
void CaptureBlockData_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    CaptureBlockData_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure CaptureBlockData_delete_dyn__til_closure = { (void *)CaptureBlockData_delete_dyn, NULL, NULL };
U64 CaptureBlockData_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return CaptureBlockData_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure CaptureBlockData_hash_dyn__til_closure = { (void *)CaptureBlockData_hash_dyn, NULL, NULL };
USize CaptureBlockData_size_dyn(void *til_env) {
    (void)til_env;
    return CaptureBlockData_size();
}
static __attribute__((unused)) TilClosure CaptureBlockData_size_dyn__til_closure = { (void *)CaptureBlockData_size_dyn, NULL, NULL };
void *NodeType_Body_dyn(void *til_env) {
    (void)til_env;
    return (void *)NodeType_Body();
}
static __attribute__((unused)) TilClosure NodeType_Body_dyn__til_closure = { (void *)NodeType_Body_dyn, NULL, NULL };
void *NodeType_Literal_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)NodeType_Literal(_a0);
}
static __attribute__((unused)) TilClosure NodeType_Literal_dyn__til_closure = { (void *)NodeType_Literal_dyn, NULL, NULL };
void *NodeType_Ident_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)NodeType_Ident(_a0);
}
static __attribute__((unused)) TilClosure NodeType_Ident_dyn__til_closure = { (void *)NodeType_Ident_dyn, NULL, NULL };
void *NodeType_Decl_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)NodeType_Decl(_a0);
}
static __attribute__((unused)) TilClosure NodeType_Decl_dyn__til_closure = { (void *)NodeType_Decl_dyn, NULL, NULL };
void *NodeType_Assign_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)NodeType_Assign(_a0);
}
static __attribute__((unused)) TilClosure NodeType_Assign_dyn__til_closure = { (void *)NodeType_Assign_dyn, NULL, NULL };
void *NodeType_FCall_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)NodeType_FCall(_a0);
}
static __attribute__((unused)) TilClosure NodeType_FCall_dyn__til_closure = { (void *)NodeType_FCall_dyn, NULL, NULL };
void *NodeType_FuncDef_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)NodeType_FuncDef(_a0);
}
static __attribute__((unused)) TilClosure NodeType_FuncDef_dyn__til_closure = { (void *)NodeType_FuncDef_dyn, NULL, NULL };
void *NodeType_StructDef_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)NodeType_StructDef(_a0);
}
static __attribute__((unused)) TilClosure NodeType_StructDef_dyn__til_closure = { (void *)NodeType_StructDef_dyn, NULL, NULL };
void *NodeType_EnumDef_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)NodeType_EnumDef(_a0);
}
static __attribute__((unused)) TilClosure NodeType_EnumDef_dyn__til_closure = { (void *)NodeType_EnumDef_dyn, NULL, NULL };
void *NodeType_FieldAccess_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)NodeType_FieldAccess(_a0);
}
static __attribute__((unused)) TilClosure NodeType_FieldAccess_dyn__til_closure = { (void *)NodeType_FieldAccess_dyn, NULL, NULL };
void *NodeType_FieldAssign_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)NodeType_FieldAssign(_a0);
}
static __attribute__((unused)) TilClosure NodeType_FieldAssign_dyn__til_closure = { (void *)NodeType_FieldAssign_dyn, NULL, NULL };
void *NodeType_Return_dyn(void *til_env) {
    (void)til_env;
    return (void *)NodeType_Return();
}
static __attribute__((unused)) TilClosure NodeType_Return_dyn__til_closure = { (void *)NodeType_Return_dyn, NULL, NULL };
void *NodeType_If_dyn(void *til_env) {
    (void)til_env;
    return (void *)NodeType_If();
}
static __attribute__((unused)) TilClosure NodeType_If_dyn__til_closure = { (void *)NodeType_If_dyn, NULL, NULL };
void *NodeType_While_dyn(void *til_env) {
    (void)til_env;
    return (void *)NodeType_While();
}
static __attribute__((unused)) TilClosure NodeType_While_dyn__til_closure = { (void *)NodeType_While_dyn, NULL, NULL };
void *NodeType_ForIn_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)NodeType_ForIn(_a0);
}
static __attribute__((unused)) TilClosure NodeType_ForIn_dyn__til_closure = { (void *)NodeType_ForIn_dyn, NULL, NULL };
void *NodeType_NamedArg_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)NodeType_NamedArg(_a0);
}
static __attribute__((unused)) TilClosure NodeType_NamedArg_dyn__til_closure = { (void *)NodeType_NamedArg_dyn, NULL, NULL };
void *NodeType_Break_dyn(void *til_env) {
    (void)til_env;
    return (void *)NodeType_Break();
}
static __attribute__((unused)) TilClosure NodeType_Break_dyn__til_closure = { (void *)NodeType_Break_dyn, NULL, NULL };
void *NodeType_Continue_dyn(void *til_env) {
    (void)til_env;
    return (void *)NodeType_Continue();
}
static __attribute__((unused)) TilClosure NodeType_Continue_dyn__til_closure = { (void *)NodeType_Continue_dyn, NULL, NULL };
void *NodeType_Switch_dyn(void *til_env) {
    (void)til_env;
    return (void *)NodeType_Switch();
}
static __attribute__((unused)) TilClosure NodeType_Switch_dyn__til_closure = { (void *)NodeType_Switch_dyn, NULL, NULL };
void *NodeType_Match_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)NodeType_Match(_a0);
}
static __attribute__((unused)) TilClosure NodeType_Match_dyn__til_closure = { (void *)NodeType_Match_dyn, NULL, NULL };
void *NodeType_Case_dyn(void *til_env) {
    (void)til_env;
    return (void *)NodeType_Case();
}
static __attribute__((unused)) TilClosure NodeType_Case_dyn__til_closure = { (void *)NodeType_Case_dyn, NULL, NULL };
void *NodeType_NoDefaultArg_dyn(void *til_env) {
    (void)til_env;
    return (void *)NodeType_NoDefaultArg();
}
static __attribute__((unused)) TilClosure NodeType_NoDefaultArg_dyn__til_closure = { (void *)NodeType_NoDefaultArg_dyn, NULL, NULL };
void *NodeType_Throw_dyn(void *til_env) {
    (void)til_env;
    return (void *)NodeType_Throw();
}
static __attribute__((unused)) TilClosure NodeType_Throw_dyn__til_closure = { (void *)NodeType_Throw_dyn, NULL, NULL };
void *NodeType_Catch_dyn(void *til_env) {
    (void)til_env;
    return (void *)NodeType_Catch();
}
static __attribute__((unused)) TilClosure NodeType_Catch_dyn__til_closure = { (void *)NodeType_Catch_dyn, NULL, NULL };
void *NodeType_RestPattern_dyn(void *til_env) {
    (void)til_env;
    return (void *)NodeType_RestPattern();
}
static __attribute__((unused)) TilClosure NodeType_RestPattern_dyn__til_closure = { (void *)NodeType_RestPattern_dyn, NULL, NULL };
void *NodeType_CaptureBlock_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)NodeType_CaptureBlock(_a0);
}
static __attribute__((unused)) TilClosure NodeType_CaptureBlock_dyn__til_closure = { (void *)NodeType_CaptureBlock_dyn, NULL, NULL };
void *NodeType_Loc_dyn(void *til_env) {
    (void)til_env;
    return (void *)NodeType_Loc();
}
static __attribute__((unused)) TilClosure NodeType_Loc_dyn__til_closure = { (void *)NodeType_Loc_dyn, NULL, NULL };
void *NodeType_BodyValue_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)NodeType_BodyValue(_a0);
}
static __attribute__((unused)) TilClosure NodeType_BodyValue_dyn__til_closure = { (void *)NodeType_BodyValue_dyn, NULL, NULL };
void *NodeType_ListPattern_dyn(void *til_env) {
    (void)til_env;
    return (void *)NodeType_ListPattern();
}
static __attribute__((unused)) TilClosure NodeType_ListPattern_dyn__til_closure = { (void *)NodeType_ListPattern_dyn, NULL, NULL };
void NodeType_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    NodeType_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure NodeType_delete_dyn__til_closure = { (void *)NodeType_delete_dyn, NULL, NULL };
void *NodeType_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)NodeType_clone(_a0);
}
static __attribute__((unused)) TilClosure NodeType_clone_dyn__til_closure = { (void *)NodeType_clone_dyn, NULL, NULL };
USize NodeType_size_dyn(void *til_env) {
    (void)til_env;
    return NodeType_size();
}
static __attribute__((unused)) TilClosure NodeType_size_dyn__til_closure = { (void *)NodeType_size_dyn, NULL, NULL };
void Expr_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Expr_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Expr_delete_dyn__til_closure = { (void *)Expr_delete_dyn, NULL, NULL };
void *Expr_new_dyn(void *til_env, void *_a0, void *_a1, void *_a2) {
    (void)til_env;
    return (void *)Expr_new(_a0, *(U32 *)_a1, *(U32 *)_a2);
}
static __attribute__((unused)) TilClosure Expr_new_dyn__til_closure = { (void *)Expr_new_dyn, NULL, NULL };
void *Expr_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Expr_clone(_a0);
}
static __attribute__((unused)) TilClosure Expr_clone_dyn__til_closure = { (void *)Expr_clone_dyn, NULL, NULL };
U64 Expr_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Expr_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure Expr_hash_dyn__til_closure = { (void *)Expr_hash_dyn, NULL, NULL };
USize Expr_size_dyn(void *til_env) {
    (void)til_env;
    return Expr_size();
}
static __attribute__((unused)) TilClosure Expr_size_dyn__til_closure = { (void *)Expr_size_dyn, NULL, NULL };
void *Map__Str_USize_new_dyn(void *til_env) {
    (void)til_env;
    return (void *)Map__Str_USize_new();
}
static __attribute__((unused)) TilClosure Map__Str_USize_new_dyn__til_closure = { (void *)Map__Str_USize_new_dyn, NULL, NULL };
void Map__Str_USize_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Map__Str_USize_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Map__Str_USize_delete_dyn__til_closure = { (void *)Map__Str_USize_delete_dyn, NULL, NULL };
void *Map__Str_USize_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Map__Str_USize_clone(_a0);
}
static __attribute__((unused)) TilClosure Map__Str_USize_clone_dyn__til_closure = { (void *)Map__Str_USize_clone_dyn, NULL, NULL };
U64 Map__Str_USize_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Map__Str_USize_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure Map__Str_USize_hash_dyn__til_closure = { (void *)Map__Str_USize_hash_dyn, NULL, NULL };
USize Map__Str_USize_size_dyn(void *til_env) {
    (void)til_env;
    return Map__Str_USize_size();
}
static __attribute__((unused)) TilClosure Map__Str_USize_size_dyn__til_closure = { (void *)Map__Str_USize_size_dyn, NULL, NULL };
void *Vec__VariantDef_new_dyn(void *til_env) {
    (void)til_env;
    return (void *)Vec__VariantDef_new();
}
static __attribute__((unused)) TilClosure Vec__VariantDef_new_dyn__til_closure = { (void *)Vec__VariantDef_new_dyn, NULL, NULL };
void Vec__VariantDef_clear_dyn(void *til_env, void *_a0) {
    (void)til_env;
    Vec__VariantDef_clear(_a0);
}
static __attribute__((unused)) TilClosure Vec__VariantDef_clear_dyn__til_closure = { (void *)Vec__VariantDef_clear_dyn, NULL, NULL };
void Vec__VariantDef_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Vec__VariantDef_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Vec__VariantDef_delete_dyn__til_closure = { (void *)Vec__VariantDef_delete_dyn, NULL, NULL };
void *Vec__VariantDef_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Vec__VariantDef_clone(_a0);
}
static __attribute__((unused)) TilClosure Vec__VariantDef_clone_dyn__til_closure = { (void *)Vec__VariantDef_clone_dyn, NULL, NULL };
USize Vec__VariantDef_size_dyn(void *til_env) {
    (void)til_env;
    return Vec__VariantDef_size();
}
static __attribute__((unused)) TilClosure Vec__VariantDef_size_dyn__til_closure = { (void *)Vec__VariantDef_size_dyn, NULL, NULL };
void *Vec__Declaration_new_dyn(void *til_env) {
    (void)til_env;
    return (void *)Vec__Declaration_new();
}
static __attribute__((unused)) TilClosure Vec__Declaration_new_dyn__til_closure = { (void *)Vec__Declaration_new_dyn, NULL, NULL };
void Vec__Declaration_clear_dyn(void *til_env, void *_a0) {
    (void)til_env;
    Vec__Declaration_clear(_a0);
}
static __attribute__((unused)) TilClosure Vec__Declaration_clear_dyn__til_closure = { (void *)Vec__Declaration_clear_dyn, NULL, NULL };
void Vec__Declaration_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Vec__Declaration_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Vec__Declaration_delete_dyn__til_closure = { (void *)Vec__Declaration_delete_dyn, NULL, NULL };
void *Vec__Declaration_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Vec__Declaration_clone(_a0);
}
static __attribute__((unused)) TilClosure Vec__Declaration_clone_dyn__til_closure = { (void *)Vec__Declaration_clone_dyn, NULL, NULL };
USize Vec__Declaration_size_dyn(void *til_env) {
    (void)til_env;
    return Vec__Declaration_size();
}
static __attribute__((unused)) TilClosure Vec__Declaration_size_dyn__til_closure = { (void *)Vec__Declaration_size_dyn, NULL, NULL };
void *Vec__Expr_new_dyn(void *til_env) {
    (void)til_env;
    return (void *)Vec__Expr_new();
}
static __attribute__((unused)) TilClosure Vec__Expr_new_dyn__til_closure = { (void *)Vec__Expr_new_dyn, NULL, NULL };
void Vec__Expr_clear_dyn(void *til_env, void *_a0) {
    (void)til_env;
    Vec__Expr_clear(_a0);
}
static __attribute__((unused)) TilClosure Vec__Expr_clear_dyn__til_closure = { (void *)Vec__Expr_clear_dyn, NULL, NULL };
void Vec__Expr_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Vec__Expr_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Vec__Expr_delete_dyn__til_closure = { (void *)Vec__Expr_delete_dyn, NULL, NULL };
void *Vec__Expr_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Vec__Expr_clone(_a0);
}
static __attribute__((unused)) TilClosure Vec__Expr_clone_dyn__til_closure = { (void *)Vec__Expr_clone_dyn, NULL, NULL };
USize Vec__Expr_size_dyn(void *til_env) {
    (void)til_env;
    return Vec__Expr_size();
}
static __attribute__((unused)) TilClosure Vec__Expr_size_dyn__til_closure = { (void *)Vec__Expr_size_dyn, NULL, NULL };
void *Vec__USize_new_dyn(void *til_env) {
    (void)til_env;
    return (void *)Vec__USize_new();
}
static __attribute__((unused)) TilClosure Vec__USize_new_dyn__til_closure = { (void *)Vec__USize_new_dyn, NULL, NULL };
void Vec__USize_clear_dyn(void *til_env, void *_a0) {
    (void)til_env;
    Vec__USize_clear(_a0);
}
static __attribute__((unused)) TilClosure Vec__USize_clear_dyn__til_closure = { (void *)Vec__USize_clear_dyn, NULL, NULL };
void Vec__USize_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Vec__USize_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Vec__USize_delete_dyn__til_closure = { (void *)Vec__USize_delete_dyn, NULL, NULL };
void *Vec__USize_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Vec__USize_clone(_a0);
}
static __attribute__((unused)) TilClosure Vec__USize_clone_dyn__til_closure = { (void *)Vec__USize_clone_dyn, NULL, NULL };
USize Vec__USize_size_dyn(void *til_env) {
    (void)til_env;
    return Vec__USize_size();
}
static __attribute__((unused)) TilClosure Vec__USize_size_dyn__til_closure = { (void *)Vec__USize_size_dyn, NULL, NULL };
void *Range_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Range_clone(_a0);
}
static __attribute__((unused)) TilClosure Range_clone_dyn__til_closure = { (void *)Range_clone_dyn, NULL, NULL };
void Range_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Range_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Range_delete_dyn__til_closure = { (void *)Range_delete_dyn, NULL, NULL };
U64 Range_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Range_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure Range_hash_dyn__til_closure = { (void *)Range_hash_dyn, NULL, NULL };
USize Range_size_dyn(void *til_env) {
    (void)til_env;
    return Range_size();
}
static __attribute__((unused)) TilClosure Range_size_dyn__til_closure = { (void *)Range_size_dyn, NULL, NULL };
void *CfVec2_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)CfVec2_clone(_a0);
}
static __attribute__((unused)) TilClosure CfVec2_clone_dyn__til_closure = { (void *)CfVec2_clone_dyn, NULL, NULL };
void CfVec2_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    CfVec2_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure CfVec2_delete_dyn__til_closure = { (void *)CfVec2_delete_dyn, NULL, NULL };
U64 CfVec2_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return CfVec2_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure CfVec2_hash_dyn__til_closure = { (void *)CfVec2_hash_dyn, NULL, NULL };
USize CfVec2_size_dyn(void *til_env) {
    (void)til_env;
    return CfVec2_size();
}
static __attribute__((unused)) TilClosure CfVec2_size_dyn__til_closure = { (void *)CfVec2_size_dyn, NULL, NULL };
void *CfRect_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)CfRect_clone(_a0);
}
static __attribute__((unused)) TilClosure CfRect_clone_dyn__til_closure = { (void *)CfRect_clone_dyn, NULL, NULL };
void CfRect_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    CfRect_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure CfRect_delete_dyn__til_closure = { (void *)CfRect_delete_dyn, NULL, NULL };
U64 CfRect_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return CfRect_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure CfRect_hash_dyn__til_closure = { (void *)CfRect_hash_dyn, NULL, NULL };
USize CfRect_size_dyn(void *til_env) {
    (void)til_env;
    return CfRect_size();
}
static __attribute__((unused)) TilClosure CfRect_size_dyn__til_closure = { (void *)CfRect_size_dyn, NULL, NULL };
void *CfVec3f_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)CfVec3f_clone(_a0);
}
static __attribute__((unused)) TilClosure CfVec3f_clone_dyn__til_closure = { (void *)CfVec3f_clone_dyn, NULL, NULL };
void CfVec3f_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    CfVec3f_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure CfVec3f_delete_dyn__til_closure = { (void *)CfVec3f_delete_dyn, NULL, NULL };
U64 CfVec3f_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return CfVec3f_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure CfVec3f_hash_dyn__til_closure = { (void *)CfVec3f_hash_dyn, NULL, NULL };
USize CfVec3f_size_dyn(void *til_env) {
    (void)til_env;
    return CfVec3f_size();
}
static __attribute__((unused)) TilClosure CfVec3f_size_dyn__til_closure = { (void *)CfVec3f_size_dyn, NULL, NULL };
Bool Color_eq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Color_eq(_a0, _a1);
}
static __attribute__((unused)) TilClosure Color_eq_dyn__til_closure = { (void *)Color_eq_dyn, NULL, NULL };
void Color_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Color_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Color_delete_dyn__til_closure = { (void *)Color_delete_dyn, NULL, NULL };
void *Color_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Color_clone(_a0);
}
static __attribute__((unused)) TilClosure Color_clone_dyn__til_closure = { (void *)Color_clone_dyn, NULL, NULL };
USize Color_size_dyn(void *til_env) {
    (void)til_env;
    return Color_size();
}
static __attribute__((unused)) TilClosure Color_size_dyn__til_closure = { (void *)Color_size_dyn, NULL, NULL };
void *Token_Num_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Token_Num(_a0);
}
static __attribute__((unused)) TilClosure Token_Num_dyn__til_closure = { (void *)Token_Num_dyn, NULL, NULL };
void *Token_Name_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Token_Name(_a0);
}
static __attribute__((unused)) TilClosure Token_Name_dyn__til_closure = { (void *)Token_Name_dyn, NULL, NULL };
void *Token_Eof_dyn(void *til_env) {
    (void)til_env;
    return (void *)Token_Eof();
}
static __attribute__((unused)) TilClosure Token_Eof_dyn__til_closure = { (void *)Token_Eof_dyn, NULL, NULL };
void Token_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Token_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Token_delete_dyn__til_closure = { (void *)Token_delete_dyn, NULL, NULL };
void *Token_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Token_clone(_a0);
}
static __attribute__((unused)) TilClosure Token_clone_dyn__til_closure = { (void *)Token_clone_dyn, NULL, NULL };
USize Token_size_dyn(void *til_env) {
    (void)til_env;
    return Token_size();
}
static __attribute__((unused)) TilClosure Token_size_dyn__til_closure = { (void *)Token_size_dyn, NULL, NULL };
void *dyn_fn(Str *type_name, Str *method) {
    (void)type_name; (void)method;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)&Str_len_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&Str_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)&Str_eq_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 13ULL && memcmp(method->c_str, "with_capacity", 13ULL) == 0) return (void*)&Str_with_capacity_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "push_str", 8ULL) == 0) return (void*)&Str_push_str_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Str_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)&Str_to_str_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Str_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&Str_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Str_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)&Str_neq_dyn__til_closure;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&OutOfBounds_clone_dyn__til_closure;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&OutOfBounds_delete_dyn__til_closure;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&OutOfBounds_hash_dyn__til_closure;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&OutOfBounds_size_dyn__til_closure;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "KeyNotFound", 11ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&KeyNotFound_clone_dyn__til_closure;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "KeyNotFound", 11ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&KeyNotFound_delete_dyn__til_closure;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "KeyNotFound", 11ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&KeyNotFound_hash_dyn__til_closure;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "KeyNotFound", 11ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&KeyNotFound_size_dyn__til_closure;
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)&Array__Str_new_dyn__til_closure;
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)&Array__Str_len_dyn__til_closure;
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "unsafe_get", 10ULL) == 0) return (void*)&Array__Str_unsafe_get_dyn__til_closure;
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "unsafe_set", 10ULL) == 0) return (void*)&Array__Str_unsafe_set_dyn__til_closure;
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "set", 3ULL) == 0) return (void*)&Array__Str_set_dyn__til_closure;
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Array__Str_delete_dyn__til_closure;
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Array__Str_clone_dyn__til_closure;
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Array__Str_size_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)&Vec__Str_new_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clear", 5ULL) == 0) return (void*)&Vec__Str_clear_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Vec__Str_delete_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Vec__Str_clone_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Vec__Str_size_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Dynamic_size_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Dynamic_clone_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Dynamic_delete_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&U8_cmp_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&U8_clone_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&U8_delete_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&U8_size_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&U8_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&U32_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&U32_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&U32_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&U32_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&U32_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)&U64_to_str_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&U64_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&U64_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&U64_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&U64_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&U64_hash_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&I8_cmp_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&I8_clone_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&I8_delete_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&I8_size_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&I8_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&I32_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&I32_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&I32_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&I32_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&I32_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)&I64_to_str_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&I64_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&I64_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&I64_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&I64_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&I64_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)&F32_to_str_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&F32_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&F32_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&F32_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&F32_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&F32_hash_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&Bool_cmp_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Bool_clone_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Bool_delete_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Bool_size_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&Bool_hash_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)&Primitive_eq_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Primitive_delete_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Primitive_clone_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Primitive_size_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "Unknown", 7ULL) == 0) return (void*)&Type_Unknown_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "None", 4ULL) == 0) return (void*)&Type_None_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "Struct", 6ULL) == 0) return (void*)&Type_Struct_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "StructDef", 9ULL) == 0) return (void*)&Type_StructDef_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "Enum", 4ULL) == 0) return (void*)&Type_Enum_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "EnumDef", 7ULL) == 0) return (void*)&Type_EnumDef_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "FuncDef", 7ULL) == 0) return (void*)&Type_FuncDef_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "FuncPtr", 7ULL) == 0) return (void*)&Type_FuncPtr_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "Dynamic", 7ULL) == 0) return (void*)&Type_Dynamic_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "Custom", 6ULL) == 0) return (void*)&Type_Custom_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "Primitive", 9ULL) == 0) return (void*)&Type_Primitive_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "FuncPtrSig", 10ULL) == 0) return (void*)&Type_FuncPtrSig_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "Body", 4ULL) == 0) return (void*)&Type_Body_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Type_delete_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Type_clone_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Type_size_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)&FuncType_eq_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&FuncType_delete_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&FuncType_clone_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&FuncType_size_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)&OwnType_eq_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&OwnType_delete_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&OwnType_clone_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&OwnType_size_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "GcStorage", 9ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)&GcStorage_eq_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "GcStorage", 9ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&GcStorage_delete_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "GcStorage", 9ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&GcStorage_clone_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "GcStorage", 9ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&GcStorage_size_dyn__til_closure;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Declaration_clone_dyn__til_closure;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Declaration_delete_dyn__til_closure;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Declaration_size_dyn__til_closure;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&FunctionDef_clone_dyn__til_closure;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&FunctionDef_delete_dyn__til_closure;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&FunctionDef_hash_dyn__til_closure;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&FunctionDef_size_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&FCallData_clone_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&FCallData_delete_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&FCallData_hash_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&FCallData_size_dyn__til_closure;
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&LiteralNumData_clone_dyn__til_closure;
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&LiteralNumData_delete_dyn__til_closure;
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&LiteralNumData_hash_dyn__til_closure;
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&LiteralNumData_size_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&IdentData_clone_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&IdentData_delete_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&IdentData_hash_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&IdentData_size_dyn__til_closure;
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&FieldAccessData_clone_dyn__til_closure;
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&FieldAccessData_delete_dyn__til_closure;
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&FieldAccessData_hash_dyn__til_closure;
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&FieldAccessData_size_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&StructDef_clone_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&StructDef_delete_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&StructDef_size_dyn__til_closure;
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "VariantDef", 10ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&VariantDef_clone_dyn__til_closure;
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "VariantDef", 10ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&VariantDef_delete_dyn__til_closure;
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "VariantDef", 10ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&VariantDef_hash_dyn__til_closure;
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "VariantDef", 10ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&VariantDef_size_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&EnumDef_clone_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&EnumDef_delete_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&EnumDef_size_dyn__til_closure;
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&AssignData_clone_dyn__til_closure;
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&AssignData_delete_dyn__til_closure;
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&AssignData_hash_dyn__til_closure;
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&AssignData_size_dyn__til_closure;
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&FieldAssignData_clone_dyn__til_closure;
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&FieldAssignData_delete_dyn__til_closure;
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&FieldAssignData_hash_dyn__til_closure;
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&FieldAssignData_size_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&ForInData_clone_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&ForInData_delete_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&ForInData_hash_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&ForInData_size_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "Str", 3ULL) == 0) return (void*)&Literal_Str_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "Num", 3ULL) == 0) return (void*)&Literal_Num_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "Bool", 4ULL) == 0) return (void*)&Literal_Bool_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "Null", 4ULL) == 0) return (void*)&Literal_Null_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "MapLit", 6ULL) == 0) return (void*)&Literal_MapLit_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "SetLit", 6ULL) == 0) return (void*)&Literal_SetLit_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Literal_delete_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Literal_clone_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Literal_size_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&MatchData_clone_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&MatchData_delete_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&MatchData_hash_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&MatchData_size_dyn__til_closure;
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&CaptureBlockData_clone_dyn__til_closure;
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&CaptureBlockData_delete_dyn__til_closure;
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&CaptureBlockData_hash_dyn__til_closure;
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&CaptureBlockData_size_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "Body", 4ULL) == 0) return (void*)&NodeType_Body_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "Literal", 7ULL) == 0) return (void*)&NodeType_Literal_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "Ident", 5ULL) == 0) return (void*)&NodeType_Ident_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "Decl", 4ULL) == 0) return (void*)&NodeType_Decl_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "Assign", 6ULL) == 0) return (void*)&NodeType_Assign_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "FCall", 5ULL) == 0) return (void*)&NodeType_FCall_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "FuncDef", 7ULL) == 0) return (void*)&NodeType_FuncDef_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "StructDef", 9ULL) == 0) return (void*)&NodeType_StructDef_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "EnumDef", 7ULL) == 0) return (void*)&NodeType_EnumDef_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 11ULL && memcmp(method->c_str, "FieldAccess", 11ULL) == 0) return (void*)&NodeType_FieldAccess_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 11ULL && memcmp(method->c_str, "FieldAssign", 11ULL) == 0) return (void*)&NodeType_FieldAssign_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "Return", 6ULL) == 0) return (void*)&NodeType_Return_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "If", 2ULL) == 0) return (void*)&NodeType_If_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "While", 5ULL) == 0) return (void*)&NodeType_While_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "ForIn", 5ULL) == 0) return (void*)&NodeType_ForIn_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "NamedArg", 8ULL) == 0) return (void*)&NodeType_NamedArg_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "Break", 5ULL) == 0) return (void*)&NodeType_Break_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "Continue", 8ULL) == 0) return (void*)&NodeType_Continue_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "Switch", 6ULL) == 0) return (void*)&NodeType_Switch_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "Match", 5ULL) == 0) return (void*)&NodeType_Match_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "Case", 4ULL) == 0) return (void*)&NodeType_Case_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 12ULL && memcmp(method->c_str, "NoDefaultArg", 12ULL) == 0) return (void*)&NodeType_NoDefaultArg_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "Throw", 5ULL) == 0) return (void*)&NodeType_Throw_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "Catch", 5ULL) == 0) return (void*)&NodeType_Catch_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 11ULL && memcmp(method->c_str, "RestPattern", 11ULL) == 0) return (void*)&NodeType_RestPattern_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 12ULL && memcmp(method->c_str, "CaptureBlock", 12ULL) == 0) return (void*)&NodeType_CaptureBlock_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "Loc", 3ULL) == 0) return (void*)&NodeType_Loc_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "BodyValue", 9ULL) == 0) return (void*)&NodeType_BodyValue_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 11ULL && memcmp(method->c_str, "ListPattern", 11ULL) == 0) return (void*)&NodeType_ListPattern_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&NodeType_delete_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&NodeType_clone_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&NodeType_size_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Expr_delete_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)&Expr_new_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Expr_clone_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&Expr_hash_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Expr_size_dyn__til_closure;
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "Map__Str_USize", 14ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)&Map__Str_USize_new_dyn__til_closure;
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "Map__Str_USize", 14ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Map__Str_USize_delete_dyn__til_closure;
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "Map__Str_USize", 14ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Map__Str_USize_clone_dyn__til_closure;
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "Map__Str_USize", 14ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&Map__Str_USize_hash_dyn__til_closure;
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "Map__Str_USize", 14ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Map__Str_USize_size_dyn__til_closure;
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "Vec__VariantDef", 15ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)&Vec__VariantDef_new_dyn__til_closure;
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "Vec__VariantDef", 15ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clear", 5ULL) == 0) return (void*)&Vec__VariantDef_clear_dyn__til_closure;
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "Vec__VariantDef", 15ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Vec__VariantDef_delete_dyn__til_closure;
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "Vec__VariantDef", 15ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Vec__VariantDef_clone_dyn__til_closure;
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "Vec__VariantDef", 15ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Vec__VariantDef_size_dyn__til_closure;
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)&Vec__Declaration_new_dyn__til_closure;
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clear", 5ULL) == 0) return (void*)&Vec__Declaration_clear_dyn__til_closure;
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Vec__Declaration_delete_dyn__til_closure;
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Vec__Declaration_clone_dyn__til_closure;
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Vec__Declaration_size_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)&Vec__Expr_new_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clear", 5ULL) == 0) return (void*)&Vec__Expr_clear_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Vec__Expr_delete_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Vec__Expr_clone_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Vec__Expr_size_dyn__til_closure;
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Vec__USize", 10ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)&Vec__USize_new_dyn__til_closure;
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Vec__USize", 10ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clear", 5ULL) == 0) return (void*)&Vec__USize_clear_dyn__til_closure;
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Vec__USize", 10ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Vec__USize_delete_dyn__til_closure;
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Vec__USize", 10ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Vec__USize_clone_dyn__til_closure;
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Vec__USize", 10ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Vec__USize_size_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Range_clone_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Range_delete_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&Range_hash_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Range_size_dyn__til_closure;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&CfVec2_clone_dyn__til_closure;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&CfVec2_delete_dyn__til_closure;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&CfVec2_hash_dyn__til_closure;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&CfVec2_size_dyn__til_closure;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&CfRect_clone_dyn__til_closure;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&CfRect_delete_dyn__til_closure;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&CfRect_hash_dyn__til_closure;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&CfRect_size_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&CfVec3f_clone_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&CfVec3f_delete_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&CfVec3f_hash_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&CfVec3f_size_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)&Color_eq_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Color_delete_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Color_clone_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Color_size_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "Num", 3ULL) == 0) return (void*)&Token_Num_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "Name", 4ULL) == 0) return (void*)&Token_Name_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "Eof", 3ULL) == 0) return (void*)&Token_Eof_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Token_delete_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Token_clone_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Token_size_dyn__til_closure;
    fprintf(stderr, "dyn_fn: unknown %s.%s\n", (char*)type_name->c_str, (char*)method->c_str);
    exit(1);
}

U32 dyn_size_of(Str *type_name) {
    (void)type_name;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) return sizeof(Dynamic);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) return sizeof(Str);
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) return sizeof(OutOfBounds);
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "KeyNotFound", 11ULL) == 0) return sizeof(KeyNotFound);
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0) return sizeof(Array__Str);
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0) return sizeof(Vec__Str);
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) return sizeof(Dynamic);
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) return sizeof(U8);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) return sizeof(U32);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) return sizeof(U64);
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0) return sizeof(I8);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) return sizeof(I32);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) return sizeof(I64);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) return sizeof(F32);
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) return sizeof(Bool);
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0) return sizeof(Primitive);
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) return sizeof(Type);
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) return sizeof(FuncType);
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) return sizeof(OwnType);
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "GcStorage", 9ULL) == 0) return sizeof(GcStorage);
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0) return sizeof(Declaration);
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) return sizeof(FunctionDef);
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) return sizeof(FCallData);
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) return sizeof(LiteralNumData);
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) return sizeof(IdentData);
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) return sizeof(FieldAccessData);
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) return sizeof(StructDef);
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "VariantDef", 10ULL) == 0) return sizeof(VariantDef);
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) return sizeof(EnumDef);
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) return sizeof(AssignData);
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) return sizeof(FieldAssignData);
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) return sizeof(ForInData);
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) return sizeof(Literal);
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) return sizeof(MatchData);
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) return sizeof(CaptureBlockData);
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) return sizeof(NodeType);
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) return sizeof(Expr);
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "Map__Str_USize", 14ULL) == 0) return sizeof(Map__Str_USize);
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "Vec__VariantDef", 15ULL) == 0) return sizeof(Vec__VariantDef);
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) return sizeof(Vec__Declaration);
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) return sizeof(Vec__Expr);
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Vec__USize", 10ULL) == 0) return sizeof(Vec__USize);
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) return sizeof(Range);
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) return sizeof(CfVec2);
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) return sizeof(CfRect);
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) return sizeof(CfVec3f);
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) return sizeof(Color);
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) return sizeof(Token);
    fprintf(stderr, "dyn_size_of: unknown type %.*s\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

I64 struct_field_count(Str *type_name) {
    (void)type_name;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) {
        return 3LL;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "KeyNotFound", 11ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0) {
        return 2LL;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0) {
        return 3LL;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0) {
        return 12LL;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        return 13LL;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        return 9LL;
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        return 2LL;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        return 2LL;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        return 2LL;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        return 8LL;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "VariantDef", 10ULL) == 0) {
        return 6LL;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        return 5LL;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        return 5LL;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        return 4LL;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        return 5LL;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        return 2LL;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        return 2LL;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        return 4LL;
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "Map__Str_USize", 14ULL) == 0) {
        return 2LL;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "Vec__VariantDef", 15ULL) == 0) {
        return 3LL;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) {
        return 3LL;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) {
        return 3LL;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Vec__USize", 10ULL) == 0) {
        return 3LL;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) {
        return 2LL;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        return 2LL;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        return 2LL;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        return 3LL;
    }
    fprintf(stderr, "struct_field_count: type '%.*s' not found\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

Str *struct_field_name(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[0];
        if (*index == 1LL) return &_til_str_lits[2];
        if (*index == 2LL) return &_til_str_lits[4];
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) {
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "KeyNotFound", 11ULL) == 0) {
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[5];
        if (*index == 1LL) return &_til_str_lits[4];
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[5];
        if (*index == 1LL) return &_til_str_lits[2];
        if (*index == 2LL) return &_til_str_lits[4];
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) {
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) {
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) {
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) {
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[47];
        if (*index == 1LL) return &_til_str_lits[48];
        if (*index == 2LL) return &_til_str_lits[49];
        if (*index == 3LL) return &_til_str_lits[50];
        if (*index == 4LL) return &_til_str_lits[51];
        if (*index == 5LL) return &_til_str_lits[52];
        if (*index == 6LL) return &_til_str_lits[53];
        if (*index == 7LL) return &_til_str_lits[54];
        if (*index == 8LL) return &_til_str_lits[56];
        if (*index == 9LL) return &_til_str_lits[58];
        if (*index == 10LL) return &_til_str_lits[60];
        if (*index == 11LL) return &_til_str_lits[61];
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[63];
        if (*index == 1LL) return &_til_str_lits[65];
        if (*index == 2LL) return &_til_str_lits[67];
        if (*index == 3LL) return &_til_str_lits[68];
        if (*index == 4LL) return &_til_str_lits[70];
        if (*index == 5LL) return &_til_str_lits[71];
        if (*index == 6LL) return &_til_str_lits[72];
        if (*index == 7LL) return &_til_str_lits[73];
        if (*index == 8LL) return &_til_str_lits[74];
        if (*index == 9LL) return &_til_str_lits[75];
        if (*index == 10LL) return &_til_str_lits[76];
        if (*index == 11LL) return &_til_str_lits[77];
        if (*index == 12LL) return &_til_str_lits[78];
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[79];
        if (*index == 1LL) return &_til_str_lits[80];
        if (*index == 2LL) return &_til_str_lits[81];
        if (*index == 3LL) return &_til_str_lits[82];
        if (*index == 4LL) return &_til_str_lits[83];
        if (*index == 5LL) return &_til_str_lits[84];
        if (*index == 6LL) return &_til_str_lits[56];
        if (*index == 7LL) return &_til_str_lits[85];
        if (*index == 8LL) return &_til_str_lits[86];
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[87];
        if (*index == 1LL) return &_til_str_lits[56];
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[47];
        if (*index == 1LL) return &_til_str_lits[56];
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[47];
        if (*index == 1LL) return &_til_str_lits[56];
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[88];
        if (*index == 1LL) return &_til_str_lits[89];
        if (*index == 2LL) return &_til_str_lits[90];
        if (*index == 3LL) return &_til_str_lits[92];
        if (*index == 4LL) return &_til_str_lits[93];
        if (*index == 5LL) return &_til_str_lits[94];
        if (*index == 6LL) return &_til_str_lits[95];
        if (*index == 7LL) return &_til_str_lits[96];
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "VariantDef", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[47];
        if (*index == 1LL) return &_til_str_lits[48];
        if (*index == 2LL) return &_til_str_lits[97];
        if (*index == 3LL) return &_til_str_lits[98];
        if (*index == 4LL) return &_til_str_lits[99];
        if (*index == 5LL) return &_til_str_lits[100];
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[89];
        if (*index == 1LL) return &_til_str_lits[92];
        if (*index == 2LL) return &_til_str_lits[101];
        if (*index == 3LL) return &_til_str_lits[96];
        if (*index == 4LL) return &_til_str_lits[103];
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[47];
        if (*index == 1LL) return &_til_str_lits[104];
        if (*index == 2LL) return &_til_str_lits[105];
        if (*index == 3LL) return &_til_str_lits[84];
        if (*index == 4LL) return &_til_str_lits[106];
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[47];
        if (*index == 1LL) return &_til_str_lits[104];
        if (*index == 2LL) return &_til_str_lits[107];
        if (*index == 3LL) return &_til_str_lits[106];
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[47];
        if (*index == 1LL) return &_til_str_lits[50];
        if (*index == 2LL) return &_til_str_lits[56];
        if (*index == 3LL) return &_til_str_lits[108];
        if (*index == 4LL) return &_til_str_lits[109];
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[56];
        if (*index == 1LL) return &_til_str_lits[115];
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[76];
        if (*index == 1LL) return &_til_str_lits[77];
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[153];
        if (*index == 1LL) return &_til_str_lits[155];
        if (*index == 2LL) return &_til_str_lits[157];
        if (*index == 3LL) return &_til_str_lits[158];
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "Map__Str_USize", 14ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[159];
        if (*index == 1LL) return &_til_str_lits[160];
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "Vec__VariantDef", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[5];
        if (*index == 1LL) return &_til_str_lits[2];
        if (*index == 2LL) return &_til_str_lits[4];
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[5];
        if (*index == 1LL) return &_til_str_lits[2];
        if (*index == 2LL) return &_til_str_lits[4];
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[5];
        if (*index == 1LL) return &_til_str_lits[2];
        if (*index == 2LL) return &_til_str_lits[4];
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Vec__USize", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[5];
        if (*index == 1LL) return &_til_str_lits[2];
        if (*index == 2LL) return &_til_str_lits[4];
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[165];
        if (*index == 1LL) return &_til_str_lits[166];
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[191];
        if (*index == 1LL) return &_til_str_lits[192];
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[197];
        if (*index == 1LL) return &_til_str_lits[199];
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[191];
        if (*index == 1LL) return &_til_str_lits[192];
        if (*index == 2LL) return &_til_str_lits[204];
    }
    fprintf(stderr, "struct_field_name: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

I64 struct_field_is_mut(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) {
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "KeyNotFound", 11ULL) == 0) {
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 0;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) {
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) {
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) {
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) {
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
        if (*index == 3LL) return 1;
        if (*index == 4LL) return 1;
        if (*index == 5LL) return 1;
        if (*index == 6LL) return 1;
        if (*index == 7LL) return 1;
        if (*index == 8LL) return 1;
        if (*index == 9LL) return 1;
        if (*index == 10LL) return 1;
        if (*index == 11LL) return 1;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
        if (*index == 3LL) return 1;
        if (*index == 4LL) return 1;
        if (*index == 5LL) return 1;
        if (*index == 6LL) return 1;
        if (*index == 7LL) return 1;
        if (*index == 8LL) return 1;
        if (*index == 9LL) return 1;
        if (*index == 10LL) return 1;
        if (*index == 11LL) return 1;
        if (*index == 12LL) return 1;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
        if (*index == 3LL) return 1;
        if (*index == 4LL) return 1;
        if (*index == 5LL) return 1;
        if (*index == 6LL) return 1;
        if (*index == 7LL) return 1;
        if (*index == 8LL) return 1;
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
        if (*index == 3LL) return 1;
        if (*index == 4LL) return 1;
        if (*index == 5LL) return 1;
        if (*index == 6LL) return 1;
        if (*index == 7LL) return 1;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "VariantDef", 10ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
        if (*index == 3LL) return 1;
        if (*index == 4LL) return 1;
        if (*index == 5LL) return 1;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
        if (*index == 3LL) return 1;
        if (*index == 4LL) return 1;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
        if (*index == 3LL) return 1;
        if (*index == 4LL) return 1;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
        if (*index == 3LL) return 1;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
        if (*index == 3LL) return 1;
        if (*index == 4LL) return 1;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
        if (*index == 3LL) return 1;
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "Map__Str_USize", 14ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "Vec__VariantDef", 15ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Vec__USize", 10ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
    }
    fprintf(stderr, "struct_field_is_mut: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

Str *struct_field_type(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[1];
        if (*index == 1LL) return &_til_str_lits[3];
        if (*index == 2LL) return &_til_str_lits[3];
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) {
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "KeyNotFound", 11ULL) == 0) {
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[6];
        if (*index == 1LL) return &_til_str_lits[3];
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[6];
        if (*index == 1LL) return &_til_str_lits[3];
        if (*index == 2LL) return &_til_str_lits[3];
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) {
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) {
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) {
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) {
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[20];
        if (*index == 1LL) return &_til_str_lits[20];
        if (*index == 2LL) return &_til_str_lits[20];
        if (*index == 3LL) return &_til_str_lits[15];
        if (*index == 4LL) return &_til_str_lits[15];
        if (*index == 5LL) return &_til_str_lits[15];
        if (*index == 6LL) return &_til_str_lits[15];
        if (*index == 7LL) return &_til_str_lits[55];
        if (*index == 8LL) return &_til_str_lits[57];
        if (*index == 9LL) return &_til_str_lits[59];
        if (*index == 10LL) return &_til_str_lits[20];
        if (*index == 11LL) return &_til_str_lits[62];
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[64];
        if (*index == 1LL) return &_til_str_lits[66];
        if (*index == 2LL) return &_til_str_lits[20];
        if (*index == 3LL) return &_til_str_lits[69];
        if (*index == 4LL) return &_til_str_lits[12];
        if (*index == 5LL) return &_til_str_lits[12];
        if (*index == 6LL) return &_til_str_lits[55];
        if (*index == 7LL) return &_til_str_lits[15];
        if (*index == 8LL) return &_til_str_lits[15];
        if (*index == 9LL) return &_til_str_lits[15];
        if (*index == 10LL) return &_til_str_lits[66];
        if (*index == 11LL) return &_til_str_lits[20];
        if (*index == 12LL) return &_til_str_lits[15];
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[15];
        if (*index == 1LL) return &_til_str_lits[15];
        if (*index == 2LL) return &_til_str_lits[15];
        if (*index == 3LL) return &_til_str_lits[8];
        if (*index == 4LL) return &_til_str_lits[8];
        if (*index == 5LL) return &_til_str_lits[15];
        if (*index == 6LL) return &_til_str_lits[57];
        if (*index == 7LL) return &_til_str_lits[15];
        if (*index == 8LL) return &_til_str_lits[8];
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[20];
        if (*index == 1LL) return &_til_str_lits[57];
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[20];
        if (*index == 1LL) return &_til_str_lits[57];
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[20];
        if (*index == 1LL) return &_til_str_lits[57];
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[66];
        if (*index == 1LL) return &_til_str_lits[66];
        if (*index == 2LL) return &_til_str_lits[91];
        if (*index == 3LL) return &_til_str_lits[91];
        if (*index == 4LL) return &_til_str_lits[20];
        if (*index == 5LL) return &_til_str_lits[15];
        if (*index == 6LL) return &_til_str_lits[15];
        if (*index == 7LL) return &_til_str_lits[20];
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "VariantDef", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[20];
        if (*index == 1LL) return &_til_str_lits[20];
        if (*index == 2LL) return &_til_str_lits[20];
        if (*index == 3LL) return &_til_str_lits[15];
        if (*index == 4LL) return &_til_str_lits[13];
        if (*index == 5LL) return &_til_str_lits[15];
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[66];
        if (*index == 1LL) return &_til_str_lits[91];
        if (*index == 2LL) return &_til_str_lits[102];
        if (*index == 3LL) return &_til_str_lits[20];
        if (*index == 4LL) return &_til_str_lits[20];
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[20];
        if (*index == 1LL) return &_til_str_lits[15];
        if (*index == 2LL) return &_til_str_lits[15];
        if (*index == 3LL) return &_til_str_lits[15];
        if (*index == 4LL) return &_til_str_lits[15];
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[20];
        if (*index == 1LL) return &_til_str_lits[15];
        if (*index == 2LL) return &_til_str_lits[15];
        if (*index == 3LL) return &_til_str_lits[15];
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[20];
        if (*index == 1LL) return &_til_str_lits[15];
        if (*index == 2LL) return &_til_str_lits[57];
        if (*index == 3LL) return &_til_str_lits[20];
        if (*index == 4LL) return &_til_str_lits[15];
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[57];
        if (*index == 1LL) return &_til_str_lits[20];
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[66];
        if (*index == 1LL) return &_til_str_lits[20];
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[154];
        if (*index == 1LL) return &_til_str_lits[156];
        if (*index == 2LL) return &_til_str_lits[11];
        if (*index == 3LL) return &_til_str_lits[11];
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "Map__Str_USize", 14ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[69];
        if (*index == 1LL) return &_til_str_lits[161];
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "Vec__VariantDef", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[6];
        if (*index == 1LL) return &_til_str_lits[3];
        if (*index == 2LL) return &_til_str_lits[3];
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[6];
        if (*index == 1LL) return &_til_str_lits[3];
        if (*index == 2LL) return &_til_str_lits[3];
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[6];
        if (*index == 1LL) return &_til_str_lits[3];
        if (*index == 2LL) return &_til_str_lits[3];
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Vec__USize", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[6];
        if (*index == 1LL) return &_til_str_lits[3];
        if (*index == 2LL) return &_til_str_lits[3];
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[8];
        if (*index == 1LL) return &_til_str_lits[8];
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[13];
        if (*index == 1LL) return &_til_str_lits[13];
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[198];
        if (*index == 1LL) return &_til_str_lits[198];
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[14];
        if (*index == 1LL) return &_til_str_lits[14];
        if (*index == 2LL) return &_til_str_lits[14];
    }
    fprintf(stderr, "struct_field_type: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

I64 enum_variant_count(Str *type_name) {
    (void)type_name;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0) {
        return 10LL;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        return 13LL;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        return 11LL;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        return 3LL;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "GcStorage", 9ULL) == 0) {
        return 3LL;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        return 6LL;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        return 29LL;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        return 3LL;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        return 3LL;
    }
    fprintf(stderr, "enum_variant_count: type '%.*s' not found\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

Str *enum_variant_name(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[9];
        if (*index == 1LL) return &_til_str_lits[10];
        if (*index == 2LL) return &_til_str_lits[1];
        if (*index == 3LL) return &_til_str_lits[6];
        if (*index == 4LL) return &_til_str_lits[11];
        if (*index == 5LL) return &_til_str_lits[12];
        if (*index == 6LL) return &_til_str_lits[8];
        if (*index == 7LL) return &_til_str_lits[13];
        if (*index == 8LL) return &_til_str_lits[14];
        if (*index == 9LL) return &_til_str_lits[15];
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[17];
        if (*index == 1LL) return &_til_str_lits[18];
        if (*index == 2LL) return &_til_str_lits[19];
        if (*index == 3LL) return &_til_str_lits[21];
        if (*index == 4LL) return &_til_str_lits[22];
        if (*index == 5LL) return &_til_str_lits[23];
        if (*index == 6LL) return &_til_str_lits[24];
        if (*index == 7LL) return &_til_str_lits[25];
        if (*index == 8LL) return &_til_str_lits[7];
        if (*index == 9LL) return &_til_str_lits[26];
        if (*index == 10LL) return &_til_str_lits[27];
        if (*index == 11LL) return &_til_str_lits[28];
        if (*index == 12LL) return &_til_str_lits[29];
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[30];
        if (*index == 1LL) return &_til_str_lits[31];
        if (*index == 2LL) return &_til_str_lits[32];
        if (*index == 3LL) return &_til_str_lits[33];
        if (*index == 4LL) return &_til_str_lits[34];
        if (*index == 5LL) return &_til_str_lits[35];
        if (*index == 6LL) return &_til_str_lits[36];
        if (*index == 7LL) return &_til_str_lits[37];
        if (*index == 8LL) return &_til_str_lits[38];
        if (*index == 9LL) return &_til_str_lits[39];
        if (*index == 10LL) return &_til_str_lits[40];
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[41];
        if (*index == 1LL) return &_til_str_lits[42];
        if (*index == 2LL) return &_til_str_lits[43];
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "GcStorage", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[44];
        if (*index == 1LL) return &_til_str_lits[45];
        if (*index == 2LL) return &_til_str_lits[46];
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[20];
        if (*index == 1LL) return &_til_str_lits[110];
        if (*index == 2LL) return &_til_str_lits[15];
        if (*index == 3LL) return &_til_str_lits[112];
        if (*index == 4LL) return &_til_str_lits[113];
        if (*index == 5LL) return &_til_str_lits[114];
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[29];
        if (*index == 1LL) return &_til_str_lits[118];
        if (*index == 2LL) return &_til_str_lits[119];
        if (*index == 3LL) return &_til_str_lits[121];
        if (*index == 4LL) return &_til_str_lits[123];
        if (*index == 5LL) return &_til_str_lits[125];
        if (*index == 6LL) return &_til_str_lits[24];
        if (*index == 7LL) return &_til_str_lits[21];
        if (*index == 8LL) return &_til_str_lits[23];
        if (*index == 9LL) return &_til_str_lits[128];
        if (*index == 10LL) return &_til_str_lits[130];
        if (*index == 11LL) return &_til_str_lits[132];
        if (*index == 12LL) return &_til_str_lits[133];
        if (*index == 13LL) return &_til_str_lits[134];
        if (*index == 14LL) return &_til_str_lits[135];
        if (*index == 15LL) return &_til_str_lits[137];
        if (*index == 16LL) return &_til_str_lits[138];
        if (*index == 17LL) return &_til_str_lits[139];
        if (*index == 18LL) return &_til_str_lits[140];
        if (*index == 19LL) return &_til_str_lits[141];
        if (*index == 20LL) return &_til_str_lits[143];
        if (*index == 21LL) return &_til_str_lits[144];
        if (*index == 22LL) return &_til_str_lits[145];
        if (*index == 23LL) return &_til_str_lits[146];
        if (*index == 24LL) return &_til_str_lits[147];
        if (*index == 25LL) return &_til_str_lits[148];
        if (*index == 26LL) return &_til_str_lits[150];
        if (*index == 27LL) return &_til_str_lits[151];
        if (*index == 28LL) return &_til_str_lits[152];
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[211];
        if (*index == 1LL) return &_til_str_lits[212];
        if (*index == 2LL) return &_til_str_lits[213];
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[110];
        if (*index == 1LL) return &_til_str_lits[216];
        if (*index == 2LL) return &_til_str_lits[217];
    }
    fprintf(stderr, "enum_variant_name: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

I64 enum_variant_has_payload(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
        if (*index == 3LL) return 0;
        if (*index == 4LL) return 0;
        if (*index == 5LL) return 0;
        if (*index == 6LL) return 0;
        if (*index == 7LL) return 0;
        if (*index == 8LL) return 0;
        if (*index == 9LL) return 0;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 1;
        if (*index == 3LL) return 0;
        if (*index == 4LL) return 1;
        if (*index == 5LL) return 0;
        if (*index == 6LL) return 0;
        if (*index == 7LL) return 0;
        if (*index == 8LL) return 0;
        if (*index == 9LL) return 1;
        if (*index == 10LL) return 1;
        if (*index == 11LL) return 1;
        if (*index == 12LL) return 0;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
        if (*index == 3LL) return 0;
        if (*index == 4LL) return 0;
        if (*index == 5LL) return 0;
        if (*index == 6LL) return 0;
        if (*index == 7LL) return 0;
        if (*index == 8LL) return 0;
        if (*index == 9LL) return 0;
        if (*index == 10LL) return 0;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "GcStorage", 9ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
        if (*index == 3LL) return 0;
        if (*index == 4LL) return 0;
        if (*index == 5LL) return 0;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
        if (*index == 3LL) return 1;
        if (*index == 4LL) return 1;
        if (*index == 5LL) return 1;
        if (*index == 6LL) return 1;
        if (*index == 7LL) return 1;
        if (*index == 8LL) return 1;
        if (*index == 9LL) return 1;
        if (*index == 10LL) return 1;
        if (*index == 11LL) return 0;
        if (*index == 12LL) return 0;
        if (*index == 13LL) return 0;
        if (*index == 14LL) return 1;
        if (*index == 15LL) return 1;
        if (*index == 16LL) return 0;
        if (*index == 17LL) return 0;
        if (*index == 18LL) return 0;
        if (*index == 19LL) return 1;
        if (*index == 20LL) return 0;
        if (*index == 21LL) return 0;
        if (*index == 22LL) return 0;
        if (*index == 23LL) return 0;
        if (*index == 24LL) return 0;
        if (*index == 25LL) return 1;
        if (*index == 26LL) return 0;
        if (*index == 27LL) return 1;
        if (*index == 28LL) return 0;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 0;
    }
    fprintf(stderr, "enum_variant_has_payload: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

Str *enum_variant_payload_type(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[16];
        if (*index == 1LL) return &_til_str_lits[16];
        if (*index == 2LL) return &_til_str_lits[16];
        if (*index == 3LL) return &_til_str_lits[16];
        if (*index == 4LL) return &_til_str_lits[16];
        if (*index == 5LL) return &_til_str_lits[16];
        if (*index == 6LL) return &_til_str_lits[16];
        if (*index == 7LL) return &_til_str_lits[16];
        if (*index == 8LL) return &_til_str_lits[16];
        if (*index == 9LL) return &_til_str_lits[16];
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[16];
        if (*index == 1LL) return &_til_str_lits[16];
        if (*index == 2LL) return &_til_str_lits[20];
        if (*index == 3LL) return &_til_str_lits[16];
        if (*index == 4LL) return &_til_str_lits[20];
        if (*index == 5LL) return &_til_str_lits[16];
        if (*index == 6LL) return &_til_str_lits[16];
        if (*index == 7LL) return &_til_str_lits[16];
        if (*index == 8LL) return &_til_str_lits[16];
        if (*index == 9LL) return &_til_str_lits[20];
        if (*index == 10LL) return &_til_str_lits[27];
        if (*index == 11LL) return &_til_str_lits[20];
        if (*index == 12LL) return &_til_str_lits[16];
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[16];
        if (*index == 1LL) return &_til_str_lits[16];
        if (*index == 2LL) return &_til_str_lits[16];
        if (*index == 3LL) return &_til_str_lits[16];
        if (*index == 4LL) return &_til_str_lits[16];
        if (*index == 5LL) return &_til_str_lits[16];
        if (*index == 6LL) return &_til_str_lits[16];
        if (*index == 7LL) return &_til_str_lits[16];
        if (*index == 8LL) return &_til_str_lits[16];
        if (*index == 9LL) return &_til_str_lits[16];
        if (*index == 10LL) return &_til_str_lits[16];
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[16];
        if (*index == 1LL) return &_til_str_lits[16];
        if (*index == 2LL) return &_til_str_lits[16];
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "GcStorage", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[16];
        if (*index == 1LL) return &_til_str_lits[16];
        if (*index == 2LL) return &_til_str_lits[16];
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[20];
        if (*index == 1LL) return &_til_str_lits[111];
        if (*index == 2LL) return &_til_str_lits[15];
        if (*index == 3LL) return &_til_str_lits[16];
        if (*index == 4LL) return &_til_str_lits[16];
        if (*index == 5LL) return &_til_str_lits[16];
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[16];
        if (*index == 1LL) return &_til_str_lits[118];
        if (*index == 2LL) return &_til_str_lits[120];
        if (*index == 3LL) return &_til_str_lits[122];
        if (*index == 4LL) return &_til_str_lits[124];
        if (*index == 5LL) return &_til_str_lits[126];
        if (*index == 6LL) return &_til_str_lits[127];
        if (*index == 7LL) return &_til_str_lits[21];
        if (*index == 8LL) return &_til_str_lits[23];
        if (*index == 9LL) return &_til_str_lits[129];
        if (*index == 10LL) return &_til_str_lits[131];
        if (*index == 11LL) return &_til_str_lits[16];
        if (*index == 12LL) return &_til_str_lits[16];
        if (*index == 13LL) return &_til_str_lits[16];
        if (*index == 14LL) return &_til_str_lits[136];
        if (*index == 15LL) return &_til_str_lits[20];
        if (*index == 16LL) return &_til_str_lits[16];
        if (*index == 17LL) return &_til_str_lits[16];
        if (*index == 18LL) return &_til_str_lits[16];
        if (*index == 19LL) return &_til_str_lits[142];
        if (*index == 20LL) return &_til_str_lits[16];
        if (*index == 21LL) return &_til_str_lits[16];
        if (*index == 22LL) return &_til_str_lits[16];
        if (*index == 23LL) return &_til_str_lits[16];
        if (*index == 24LL) return &_til_str_lits[16];
        if (*index == 25LL) return &_til_str_lits[149];
        if (*index == 26LL) return &_til_str_lits[16];
        if (*index == 27LL) return &_til_str_lits[149];
        if (*index == 28LL) return &_til_str_lits[16];
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[16];
        if (*index == 1LL) return &_til_str_lits[16];
        if (*index == 2LL) return &_til_str_lits[16];
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[13];
        if (*index == 1LL) return &_til_str_lits[20];
        if (*index == 2LL) return &_til_str_lits[16];
    }
    fprintf(stderr, "enum_variant_payload_type: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

I64 enum_variant_tag_value(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0) {
        if (*index == 0LL) return 0LL;
        if (*index == 1LL) return 1LL;
        if (*index == 2LL) return 2LL;
        if (*index == 3LL) return 3LL;
        if (*index == 4LL) return 4LL;
        if (*index == 5LL) return 5LL;
        if (*index == 6LL) return 6LL;
        if (*index == 7LL) return 7LL;
        if (*index == 8LL) return 8LL;
        if (*index == 9LL) return 9LL;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return 0LL;
        if (*index == 1LL) return 1LL;
        if (*index == 2LL) return 2LL;
        if (*index == 3LL) return 3LL;
        if (*index == 4LL) return 4LL;
        if (*index == 5LL) return 5LL;
        if (*index == 6LL) return 6LL;
        if (*index == 7LL) return 7LL;
        if (*index == 8LL) return 8LL;
        if (*index == 9LL) return 9LL;
        if (*index == 10LL) return 10LL;
        if (*index == 11LL) return 11LL;
        if (*index == 12LL) return 12LL;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return 0LL;
        if (*index == 1LL) return 1LL;
        if (*index == 2LL) return 2LL;
        if (*index == 3LL) return 3LL;
        if (*index == 4LL) return 4LL;
        if (*index == 5LL) return 5LL;
        if (*index == 6LL) return 6LL;
        if (*index == 7LL) return 7LL;
        if (*index == 8LL) return 8LL;
        if (*index == 9LL) return 9LL;
        if (*index == 10LL) return 10LL;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return 0LL;
        if (*index == 1LL) return 1LL;
        if (*index == 2LL) return 2LL;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "GcStorage", 9ULL) == 0) {
        if (*index == 0LL) return 0LL;
        if (*index == 1LL) return 1LL;
        if (*index == 2LL) return 2LL;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return 0LL;
        if (*index == 1LL) return 1LL;
        if (*index == 2LL) return 2LL;
        if (*index == 3LL) return 3LL;
        if (*index == 4LL) return 4LL;
        if (*index == 5LL) return 5LL;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return 0LL;
        if (*index == 1LL) return 1LL;
        if (*index == 2LL) return 2LL;
        if (*index == 3LL) return 3LL;
        if (*index == 4LL) return 4LL;
        if (*index == 5LL) return 5LL;
        if (*index == 6LL) return 6LL;
        if (*index == 7LL) return 7LL;
        if (*index == 8LL) return 8LL;
        if (*index == 9LL) return 9LL;
        if (*index == 10LL) return 10LL;
        if (*index == 11LL) return 11LL;
        if (*index == 12LL) return 12LL;
        if (*index == 13LL) return 13LL;
        if (*index == 14LL) return 14LL;
        if (*index == 15LL) return 15LL;
        if (*index == 16LL) return 16LL;
        if (*index == 17LL) return 17LL;
        if (*index == 18LL) return 18LL;
        if (*index == 19LL) return 19LL;
        if (*index == 20LL) return 20LL;
        if (*index == 21LL) return 21LL;
        if (*index == 22LL) return 22LL;
        if (*index == 23LL) return 23LL;
        if (*index == 24LL) return 24LL;
        if (*index == 25LL) return 25LL;
        if (*index == 26LL) return 26LL;
        if (*index == 27LL) return 27LL;
        if (*index == 28LL) return 28LL;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return 0LL;
        if (*index == 1LL) return 1LL;
        if (*index == 2LL) return 2LL;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return 0LL;
        if (*index == 1LL) return 1LL;
        if (*index == 2LL) return 2LL;
    }
    fprintf(stderr, "enum_variant_tag_value: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

I64 enum_variant_payload_is_const(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
        if (*index == 3LL) return 0;
        if (*index == 4LL) return 0;
        if (*index == 5LL) return 0;
        if (*index == 6LL) return 0;
        if (*index == 7LL) return 0;
        if (*index == 8LL) return 0;
        if (*index == 9LL) return 0;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
        if (*index == 3LL) return 0;
        if (*index == 4LL) return 0;
        if (*index == 5LL) return 0;
        if (*index == 6LL) return 0;
        if (*index == 7LL) return 0;
        if (*index == 8LL) return 0;
        if (*index == 9LL) return 0;
        if (*index == 10LL) return 0;
        if (*index == 11LL) return 0;
        if (*index == 12LL) return 0;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
        if (*index == 3LL) return 0;
        if (*index == 4LL) return 0;
        if (*index == 5LL) return 0;
        if (*index == 6LL) return 0;
        if (*index == 7LL) return 0;
        if (*index == 8LL) return 0;
        if (*index == 9LL) return 0;
        if (*index == 10LL) return 0;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "GcStorage", 9ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
        if (*index == 3LL) return 0;
        if (*index == 4LL) return 0;
        if (*index == 5LL) return 0;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
        if (*index == 3LL) return 0;
        if (*index == 4LL) return 0;
        if (*index == 5LL) return 0;
        if (*index == 6LL) return 0;
        if (*index == 7LL) return 0;
        if (*index == 8LL) return 0;
        if (*index == 9LL) return 0;
        if (*index == 10LL) return 0;
        if (*index == 11LL) return 0;
        if (*index == 12LL) return 0;
        if (*index == 13LL) return 0;
        if (*index == 14LL) return 0;
        if (*index == 15LL) return 0;
        if (*index == 16LL) return 0;
        if (*index == 17LL) return 0;
        if (*index == 18LL) return 0;
        if (*index == 19LL) return 0;
        if (*index == 20LL) return 0;
        if (*index == 21LL) return 0;
        if (*index == 22LL) return 0;
        if (*index == 23LL) return 0;
        if (*index == 24LL) return 0;
        if (*index == 25LL) return 0;
        if (*index == 26LL) return 0;
        if (*index == 27LL) return 0;
        if (*index == 28LL) return 0;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
    }
    fprintf(stderr, "enum_variant_payload_is_const: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

I64 enum_variant_payload_is_ref(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
        if (*index == 3LL) return 0;
        if (*index == 4LL) return 0;
        if (*index == 5LL) return 0;
        if (*index == 6LL) return 0;
        if (*index == 7LL) return 0;
        if (*index == 8LL) return 0;
        if (*index == 9LL) return 0;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
        if (*index == 3LL) return 0;
        if (*index == 4LL) return 0;
        if (*index == 5LL) return 0;
        if (*index == 6LL) return 0;
        if (*index == 7LL) return 0;
        if (*index == 8LL) return 0;
        if (*index == 9LL) return 0;
        if (*index == 10LL) return 0;
        if (*index == 11LL) return 0;
        if (*index == 12LL) return 0;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
        if (*index == 3LL) return 0;
        if (*index == 4LL) return 0;
        if (*index == 5LL) return 0;
        if (*index == 6LL) return 0;
        if (*index == 7LL) return 0;
        if (*index == 8LL) return 0;
        if (*index == 9LL) return 0;
        if (*index == 10LL) return 0;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "GcStorage", 9ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
        if (*index == 3LL) return 0;
        if (*index == 4LL) return 0;
        if (*index == 5LL) return 0;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
        if (*index == 3LL) return 0;
        if (*index == 4LL) return 0;
        if (*index == 5LL) return 0;
        if (*index == 6LL) return 0;
        if (*index == 7LL) return 0;
        if (*index == 8LL) return 0;
        if (*index == 9LL) return 0;
        if (*index == 10LL) return 0;
        if (*index == 11LL) return 0;
        if (*index == 12LL) return 0;
        if (*index == 13LL) return 0;
        if (*index == 14LL) return 0;
        if (*index == 15LL) return 0;
        if (*index == 16LL) return 0;
        if (*index == 17LL) return 0;
        if (*index == 18LL) return 0;
        if (*index == 19LL) return 0;
        if (*index == 20LL) return 0;
        if (*index == 21LL) return 0;
        if (*index == 22LL) return 0;
        if (*index == 23LL) return 0;
        if (*index == 24LL) return 0;
        if (*index == 25LL) return 0;
        if (*index == 26LL) return 0;
        if (*index == 27LL) return 0;
        if (*index == 28LL) return 0;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
    }
    fprintf(stderr, "enum_variant_payload_is_ref: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

I64 func_sig_param_count(Str *type_name) {
    (void)type_name;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "HashFn", 6ULL) == 0) {
        return 2LL;
    }
    fprintf(stderr, "func_sig_param_count: type '%.*s' not found\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

Str *func_sig_param_type(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "HashFn", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[7];
        if (*index == 1LL) return &_til_str_lits[3];
    }
    fprintf(stderr, "func_sig_param_type: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

I64 func_sig_return_count(Str *type_name) {
    (void)type_name;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "HashFn", 6ULL) == 0) {
        return 1LL;
    }
    fprintf(stderr, "func_sig_return_count: type '%.*s' not found\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

Str *func_sig_return_type(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "HashFn", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lits[8];
    }
    fprintf(stderr, "func_sig_return_type: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

I64 func_sig_throw_count(Str *type_name) {
    (void)type_name;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "HashFn", 6ULL) == 0) {
        return 0LL;
    }
    fprintf(stderr, "func_sig_throw_count: type '%.*s' not found\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

Str *func_sig_throw_type(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "HashFn", 6ULL) == 0) {
    }
    fprintf(stderr, "func_sig_throw_type: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

int main(void) {
    CAP_LIT = 4294967295;
    CAP_VIEW = 4294967294;
    ELEM_POD = 0;
    ELEM_BOXED = 1;
    ELEM_FN = 2;
    { Type *_hp = (Type *)Type_clone(&(Type){.tag = Type_TAG_None}); TYPE_NONE = *_hp; free(_hp); }
    { Type *_hp = (Type *)Type_clone(&(Type){.tag = Type_TAG_Unknown}); TYPE_UNKNOWN = *_hp; free(_hp); }
    { Type *_hp = (Type *)Type_clone(&(Type){.tag = Type_TAG_Dynamic}); TYPE_DYNAMIC = *_hp; free(_hp); }
    { Type *_hp = (Type *)Type_clone(&(Type){.tag = Type_TAG_FuncPtr}); TYPE_FUNCPTR = *_hp; free(_hp); }
    { Type *_hp = (Type *)Type_clone(&(Type){.tag = Type_TAG_Body}); TYPE_BODY = *_hp; free(_hp); }
    { Type *_hp = (Type *)Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_Bool}; _oa; })); TYPE_BOOL = *_hp; free(_hp); }
    { Type *_hp = (Type *)Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_I64}; _oa; })); TYPE_I64 = *_hp; free(_hp); }
    { Type *_hp = (Type *)Type_Struct(&(Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}); TYPE_STR = *_hp; free(_hp); }
    { Type *_hp = (Type *)Type_Struct(&(Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT}); TYPE_STRUCTDEF = *_hp; free(_hp); }
    { Type *_hp = (Type *)Type_Struct(&(Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT}); TYPE_ENUMDEF = *_hp; free(_hp); }
    { Type *_hp = (Type *)Type_Struct(&(Str){.c_str = (void *)"Map", .count = 3ULL, .cap = TIL_CAP_LIT}); TYPE_MAP = *_hp; free(_hp); }
    { Type *_hp = (Type *)Type_Struct(&(Str){.c_str = (void *)"Set", .count = 3ULL, .cap = TIL_CAP_LIT}); TYPE_SET = *_hp; free(_hp); }
    test_simple_add();
    fprintf(stderr, "  pass: %s\n", "test_simple_add");
    test_nested_arithmetic();
    fprintf(stderr, "  pass: %s\n", "test_nested_arithmetic");
    test_deeply_nested();
    fprintf(stderr, "  pass: %s\n", "test_deeply_nested");
    test_string_concat();
    fprintf(stderr, "  pass: %s\n", "test_string_concat");
    test_variadic_fold();
    fprintf(stderr, "  pass: %s\n", "test_variadic_fold");
    test_variadic_direct_fold();
    fprintf(stderr, "  pass: %s\n", "test_variadic_direct_fold");
    test_lolalalo();
    fprintf(stderr, "  pass: %s\n", "test_lolalalo");
    test_fold_variable();
    fprintf(stderr, "  pass: %s\n", "test_fold_variable");
    test_loc_folded();
    fprintf(stderr, "  pass: %s\n", "test_loc_folded");
    test_fold_f32();
    fprintf(stderr, "  pass: %s\n", "test_fold_f32");
    test_struct_fold_simple();
    fprintf(stderr, "  pass: %s\n", "test_struct_fold_simple");
    test_struct_fold_values();
    fprintf(stderr, "  pass: %s\n", "test_struct_fold_values");
    test_struct_fold_nested();
    fprintf(stderr, "  pass: %s\n", "test_struct_fold_nested");
    test_struct_fold_f32();
    fprintf(stderr, "  pass: %s\n", "test_struct_fold_f32");
    test_enum_fold();
    fprintf(stderr, "  pass: %s\n", "test_enum_fold");
    test_enum_payload_fold();
    fprintf(stderr, "  pass: %s\n", "test_enum_payload_fold");
    test_enum_return_fold();
    fprintf(stderr, "  pass: %s\n", "test_enum_return_fold");
    test_enum_payload_return_fold();
    fprintf(stderr, "  pass: %s\n", "test_enum_payload_return_fold");
    fprintf(stderr, "18/18 tests passed\n");
    return 0;
}
