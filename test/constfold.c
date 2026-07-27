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


#define DEREF(p) (*(p ? p : (fprintf(stderr, "panic: null deref\n"), exit(1), p)))
#define TIL_CAP_LIT ((USize)-1)
#define TIL_CAP_VIEW ((USize)-2)
void print_single(Str *s) {
    fwrite(s->c_str, 1, (size_t)s->count, stdout);
}
void print_flush() {
    putchar('\n');
}

static Str _til_str_lits[70] = {
    (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT},
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
    (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:186:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:202:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:228:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:229:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:230:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:241:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:249:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:259:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:260:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:271:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:272:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"FunctionDef", .count = 11ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Fn", .count = 2ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"I16", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"U16", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"I8", .count = 2ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Body", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"?", .count = 1ULL, .cap = TIL_CAP_LIT},
};
#define TIL_LIT_GUARD(p) do { UPtr _g = (UPtr)(const void *)(p); if (_g >= (UPtr)(const void *)_til_str_lits && _g < (UPtr)(const void *)(_til_str_lits + 70)) { fprintf(stderr, "panic: write through a shared string literal\n"); exit(1); } } while (0)

U32 CAP_LIT;
U32 CAP_VIEW;

Str * format(Array__Str * parts) {
    U32 total = 0;
    {
        Array__Str *_fc_Array__Str_55 = parts;
        (void)_fc_Array__Str_55;
        (void)_fc_Array__Str_55;
        U32 _fi_USize_55 = 0;
        (void)_fi_USize_55;
        while (1) {
            USize hoisted__U32_57 = (_fc_Array__Str_55->cap);
            Bool _wcond_Bool_56 = ((Bool)(_fi_USize_55 < hoisted__U32_57));
            (void)_wcond_Bool_56;
            if (_wcond_Bool_56) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_55->data) + (((U32)(_fi_USize_55 * 16))))));
            U32 hoisted__U32_58 = 1;
            U32 hoisted__U32_59 = ((U32)(_fi_USize_55 + hoisted__U32_58));
            _fi_USize_55 = hoisted__U32_59;
            USize hoisted__U32_60 = (s->count);
            U32 hoisted__U32_61 = ((U32)(total + hoisted__U32_60));
            total = hoisted__U32_61;
        }
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_62 = parts;
        (void)_fc_Array__Str_62;
        (void)_fc_Array__Str_62;
        U32 _fi_USize_62 = 0;
        (void)_fi_USize_62;
        while (1) {
            USize hoisted__U32_64 = (_fc_Array__Str_62->cap);
            Bool _wcond_Bool_63 = ((Bool)(_fi_USize_62 < hoisted__U32_64));
            (void)_wcond_Bool_63;
            if (_wcond_Bool_63) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_62->data) + (((U32)(_fi_USize_62 * 16))))));
            U32 hoisted__U32_65 = 1;
            U32 hoisted__U32_66 = ((U32)(_fi_USize_62 + hoisted__U32_65));
            _fi_USize_62 = hoisted__U32_66;
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
    Bool hoisted__Bool_81 = ((Bool)(b->count < a->count));
    if (hoisted__Bool_81) {
        min_len = b->count;
    }
    I32 c = memcmp(a->c_str, b->c_str, min_len);
    I32 hoisted__I32_82 = 0;
    Bool hoisted__Bool_83 = ((Bool)(c < hoisted__I32_82));
    if (hoisted__Bool_83) {
        I64 hoisted__I64_79 = -1;
        return hoisted__I64_79;
    }
    I32 hoisted__I32_84 = 0;
    Bool hoisted__Bool_85 = ((Bool)(c > hoisted__I32_84));
    if (hoisted__Bool_85) {
        I64 hoisted__I64_80 = 1;
        return hoisted__I64_80;
    }
    I64 hoisted__I64_86 = U32_cmp(a->count, b->count);
    return hoisted__I64_86;
    __builtin_unreachable();
}

Bool Str_eq(Str * a, Str * b) {
    Bool hoisted__Bool_89 = ((Bool)(a->count != b->count));
    if (hoisted__Bool_89) {
        Bool hoisted__Bool_87 = 0;
        return hoisted__Bool_87;
    }
    Bool hoisted__Bool_90 = ptr_eq(a->c_str, b->c_str);
    if (hoisted__Bool_90) {
        Bool hoisted__Bool_88 = 1;
        return hoisted__Bool_88;
    }
    I32 hoisted__I32_91 = memcmp(a->c_str, b->c_str, a->count);
    I32 hoisted__I32_92 = 0;
    Bool hoisted__Bool_93 = ((Bool)(hoisted__I32_91 == hoisted__I32_92));
    return hoisted__Bool_93;
    __builtin_unreachable();
}

Str * Str_with_capacity(USize n) {
    U32 hoisted__U32_95 = 0;
    Bool hoisted__Bool_96 = ((Bool)(n == hoisted__U32_95));
    if (hoisted__Bool_96) {
        static Str hoisted__Str_94 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_94; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_97 = 1;
    I8 *buf = malloc(((U32)(n + hoisted__U32_97)));
    I32 hoisted__I32_98 = 0;
    U64 hoisted__U64_99 = 1ULL;
    memset(buf, hoisted__I32_98, hoisted__U64_99);
    I64 hoisted__I64_100 = 0;
    Str *hoisted__Str_101 = malloc(sizeof(Str));
    hoisted__Str_101->c_str = buf;
    hoisted__Str_101->count = hoisted__I64_100;
    hoisted__Str_101->cap = n;
    return hoisted__Str_101;
    __builtin_unreachable();
}

void Str_push_str(Str * self, Str * s) {
    U32 hoisted__U32_112 = 0;
    Bool hoisted__Bool_113 = ((Bool)(s->count == hoisted__U32_112));
    if (hoisted__Bool_113) {
        return;
    }
    Bool hoisted__Bool_114 = ((Bool)(self->cap >= CAP_VIEW));
    if (hoisted__Bool_114) {
        U32 hoisted__U32_104 = 1;
        Array__Str *_va_Array_1 = Array__Str_new(hoisted__U32_104);
        (void)_va_Array_1;
        I64 _va_Array_1_ek = 0;
        (void)_va_Array_1_ek;
        U32 hoisted__U32_105 = 0;
        static Str hoisted__Str_106 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_1, hoisted__U32_105, &hoisted__Str_106, &_va_Array_1_ek);
        static Str hoisted__Str_107 = (Str){.c_str = (void *)"./src/core/str.til:118:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        panic(_va_Array_1, &hoisted__Str_107);
        Str_delete(&hoisted__Str_107, (Bool){0});
    }
    U32 new_len = ((U32)(self->count + s->count));
    Bool hoisted__Bool_115 = ((Bool)(new_len > self->cap));
    if (hoisted__Bool_115) {
        U32 hoisted__U32_108 = 1;
        Array__Str *_va_Array_2 = Array__Str_new(hoisted__U32_108);
        (void)_va_Array_2;
        I64 _va_Array_2_ek = 0;
        (void)_va_Array_2_ek;
        U32 hoisted__U32_109 = 0;
        static Str hoisted__Str_110 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_2, hoisted__U32_109, &hoisted__Str_110, &_va_Array_2_ek);
        static Str hoisted__Str_111 = (Str){.c_str = (void *)"./src/core/str.til:122:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        panic(_va_Array_2, &hoisted__Str_111);
        Str_delete(&hoisted__Str_111, (Bool){0});
    }
    void *hoisted__v_116 = ((void *)((U8 *)(self->c_str) + (self->count)));
    memcpy(hoisted__v_116, s->c_str, s->count);
    self->count = (new_len);
    void *hoisted__v_117 = ((void *)((U8 *)(self->c_str) + (new_len)));
    I32 hoisted__I32_118 = 0;
    U64 hoisted__U64_119 = 1ULL;
    memset(hoisted__v_117, hoisted__I32_118, hoisted__U64_119);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_121 = 0;
    Bool hoisted__Bool_122 = ((Bool)(val->count == hoisted__U32_121));
    if (hoisted__Bool_122) {
        static Str hoisted__Str_120 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_120; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_123 = 1;
    I8 *new_data = malloc(((U32)(val->count + hoisted__U32_123)));
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_124 = ((void *)((U8 *)(new_data) + (val->count)));
    I32 hoisted__I32_125 = 0;
    U64 hoisted__U64_126 = 1ULL;
    memset(hoisted__v_124, hoisted__I32_125, hoisted__U64_126);
    Str *hoisted__Str_127 = malloc(sizeof(Str));
    hoisted__Str_127->c_str = new_data;
    hoisted__Str_127->count = val->count;
    hoisted__Str_127->cap = val->count;
    return hoisted__Str_127;
    __builtin_unreachable();
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_128 = Str_clone(self);
    return hoisted__Str_128;
    __builtin_unreachable();
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_129 = ((Bool)(self->cap < CAP_VIEW));
    if (hoisted__Bool_129) {
        free(self->c_str);
    }
    Bool hoisted__Bool_130 = ((Bool)(self->cap != CAP_LIT));
    Bool hoisted__Bool_131 = ((Bool)((call_free) && (hoisted__Bool_130)));
    if (hoisted__Bool_131) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_326 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, self->c_str, self->count); });
    return hoisted__U64_326;
    __builtin_unreachable();
}

USize Str_size(void) {
    U32 hoisted__U32_498 = 16;
    return hoisted__U32_498;
    __builtin_unreachable();
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_507 = Str_eq(a, b);
    Bool hoisted__Bool_508 = ((Bool)(!(hoisted__Bool_507)));
    return hoisted__Bool_508;
    __builtin_unreachable();
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * _self) {
    (void)_self;
    OutOfBounds *hoisted__OutOfBounds_589 = malloc(sizeof(OutOfBounds));
    return hoisted__OutOfBounds_589;
    __builtin_unreachable();
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_590 = 0;
    U64 hoisted__U64_591 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_590); });
    return hoisted__U64_591;
    __builtin_unreachable();
}

USize OutOfBounds_size(void) {
    U32 hoisted__U32_599 = 1;
    return hoisted__U32_599;
    __builtin_unreachable();
}

Array__Str * Array__Str_new(USize cap) {
    void * hoisted__v_611 = calloc(cap, 16);
    Array__Str *hoisted__Array__Str_612 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_612->data = hoisted__v_611;
    hoisted__Array__Str_612->cap = cap;
    return hoisted__Array__Str_612;
    __builtin_unreachable();
}

USize Array__Str_len(Array__Str * self) {
    return self->cap;
    __builtin_unreachable();
}

Str * Array__Str_unsafe_get(Array__Str * self, USize * i) {
    U32 hoisted__U32_613 = 16;
    U32 hoisted__U32_614 = ((U32)(DEREF(i) * hoisted__U32_613));
    void *hoisted__v_615 = ((void *)((U8 *)(self->data) + (hoisted__U32_614)));
    return hoisted__v_615;
    __builtin_unreachable();
}

void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val) {
    Str *hoisted__Str_621 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    Bool hoisted__Bool_622 = 0;
    Str_delete(hoisted__Str_621, hoisted__Bool_622);
    Str *hoisted__Str_623 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    U32 hoisted__U32_624 = 16;
    memcpy(hoisted__Str_623, val, hoisted__U32_624);
    I32 hoisted__I32_625 = 0;
    U32 hoisted__U32_626 = 16;
    if ((val)->cap != TIL_CAP_LIT) { memset(val, hoisted__I32_625, hoisted__U32_626); };
    Str_delete(val, 1);
}

void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind) {
    Bool hoisted__Bool_628 = ((Bool)(i >= self->cap));
    if (hoisted__Bool_628) {
        I64 hoisted__I64_627 = 1;
        *_err_kind = hoisted__I64_627;
    }
    I64 hoisted__I64_629 = 0;
    Bool hoisted__Bool_630 = ((Bool)(DEREF(_err_kind) == hoisted__I64_629));
    if (hoisted__Bool_630) {
        Array__Str_unsafe_set(self, i, val);
    } else {
        Str_delete(val, 1);
    }
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_631 = self->cap;
        (void)_re_U32_631;
        U32 _rc_U32_631 = 0;
        (void)_rc_U32_631;
        Bool hoisted__Bool_642 = ((Bool)(_rc_U32_631 <= _re_U32_631));
        if (hoisted__Bool_642) {
            while (1) {
                Bool _wcond_Bool_632 = ((Bool)(_rc_U32_631 < _re_U32_631));
                (void)_wcond_Bool_632;
                if (_wcond_Bool_632) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_631);
                (++_rc_U32_631);
                U32 hoisted__U32_633 = 16;
                U32 hoisted__U32_634 = ((U32)(i * hoisted__U32_633));
                Str *hoisted__Str_635 = ((void *)((U8 *)(self->data) + (hoisted__U32_634)));
                Bool hoisted__Bool_636 = 0;
                Str_delete(hoisted__Str_635, hoisted__Bool_636);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_637 = ((Bool)(_rc_U32_631 > _re_U32_631));
                (void)_wcond_Bool_637;
                if (_wcond_Bool_637) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_631);
                (--_rc_U32_631);
                U32 hoisted__U32_638 = 16;
                U32 hoisted__U32_639 = ((U32)(i * hoisted__U32_638));
                Str *hoisted__Str_640 = ((void *)((U8 *)(self->data) + (hoisted__U32_639)));
                Bool hoisted__Bool_641 = 0;
                Str_delete(hoisted__Str_640, hoisted__Bool_641);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_663 = 16;
    U8 *new_data = malloc(((U32)(self->cap * hoisted__U32_663)));
    {
        U32 _re_U32_643 = self->cap;
        (void)_re_U32_643;
        U32 _rc_U32_643 = 0;
        (void)_rc_U32_643;
        Bool hoisted__Bool_662 = ((Bool)(_rc_U32_643 <= _re_U32_643));
        if (hoisted__Bool_662) {
            while (1) {
                Bool _wcond_Bool_644 = ((Bool)(_rc_U32_643 < _re_U32_643));
                (void)_wcond_Bool_644;
                if (_wcond_Bool_644) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_643);
                (++_rc_U32_643);
                U32 hoisted__U32_645 = 16;
                U32 hoisted__U32_646 = ((U32)(i * hoisted__U32_645));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_646)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_647 = 16;
                U32 hoisted__U32_648 = ((U32)(i * hoisted__U32_647));
                void *hoisted__v_649 = ((void *)((U8 *)(new_data) + (hoisted__U32_648)));
                U32 hoisted__U32_650 = 16;
                memcpy(hoisted__v_649, cloned, hoisted__U32_650);
                I32 hoisted__I32_651 = 0;
                U32 hoisted__U32_652 = 16;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_651, hoisted__U32_652); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_653 = ((Bool)(_rc_U32_643 > _re_U32_643));
                (void)_wcond_Bool_653;
                if (_wcond_Bool_653) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_643);
                (--_rc_U32_643);
                U32 hoisted__U32_654 = 16;
                U32 hoisted__U32_655 = ((U32)(i * hoisted__U32_654));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_655)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_656 = 16;
                U32 hoisted__U32_657 = ((U32)(i * hoisted__U32_656));
                void *hoisted__v_658 = ((void *)((U8 *)(new_data) + (hoisted__U32_657)));
                U32 hoisted__U32_659 = 16;
                memcpy(hoisted__v_658, cloned, hoisted__U32_659);
                I32 hoisted__I32_660 = 0;
                U32 hoisted__U32_661 = 16;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_660, hoisted__U32_661); };
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_664 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_664->data = new_data;
    hoisted__Array__Str_664->cap = self->cap;
    return hoisted__Array__Str_664;
    __builtin_unreachable();
}

USize Array__Str_size(void) {
    U32 hoisted__U32_665 = 16;
    return hoisted__U32_665;
    __builtin_unreachable();
}

Vec__Str * Vec__Str_new(void) {
    U8 *hoisted__U8_666 = malloc(sizeof(U8));
    *hoisted__U8_666 = 0;
    U32 hoisted__U32_667 = 0;
    I64 hoisted__I64_668 = 0;
    Vec__Str *hoisted__Vec__Str_669 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_669->data = hoisted__U8_666;
    hoisted__Vec__Str_669->count = hoisted__U32_667;
    hoisted__Vec__Str_669->cap = hoisted__I64_668;
    return hoisted__Vec__Str_669;
    __builtin_unreachable();
}

void Vec__Str_clear(Vec__Str * self) {
    {
        U32 _re_U32_680 = self->count;
        (void)_re_U32_680;
        U32 _rc_U32_680 = 0;
        (void)_rc_U32_680;
        Bool hoisted__Bool_691 = ((Bool)(_rc_U32_680 <= _re_U32_680));
        if (hoisted__Bool_691) {
            while (1) {
                Bool _wcond_Bool_681 = ((Bool)(_rc_U32_680 < _re_U32_680));
                (void)_wcond_Bool_681;
                if (_wcond_Bool_681) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_680);
                (++_rc_U32_680);
                U32 hoisted__U32_682 = 16;
                U32 hoisted__U32_683 = ((U32)(i * hoisted__U32_682));
                Str *hoisted__Str_684 = ((void *)((U8 *)(self->data) + (hoisted__U32_683)));
                Bool hoisted__Bool_685 = 0;
                Str_delete(hoisted__Str_684, hoisted__Bool_685);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_686 = ((Bool)(_rc_U32_680 > _re_U32_680));
                (void)_wcond_Bool_686;
                if (_wcond_Bool_686) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_680);
                (--_rc_U32_680);
                U32 hoisted__U32_687 = 16;
                U32 hoisted__U32_688 = ((U32)(i * hoisted__U32_687));
                Str *hoisted__Str_689 = ((void *)((U8 *)(self->data) + (hoisted__U32_688)));
                Bool hoisted__Bool_690 = 0;
                Str_delete(hoisted__Str_689, hoisted__Bool_690);
            }
        }
    }
    U32 hoisted__U32_692 = 0;
    self->count = hoisted__U32_692;
}

void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Str * Vec__Str_clone(Vec__Str * self) {
    U32 hoisted__U32_950 = 0;
    Bool hoisted__Bool_951 = ((Bool)(self->cap == hoisted__U32_950));
    if (hoisted__Bool_951) {
        U8 *hoisted__U8_926 = malloc(sizeof(U8));
        *hoisted__U8_926 = 0;
        U32 hoisted__U32_927 = 0;
        I64 hoisted__I64_928 = 0;
        Vec__Str *hoisted__Vec__Str_929 = malloc(sizeof(Vec__Str));
        hoisted__Vec__Str_929->data = hoisted__U8_926;
        hoisted__Vec__Str_929->count = hoisted__U32_927;
        hoisted__Vec__Str_929->cap = hoisted__I64_928;
        return hoisted__Vec__Str_929;
    }
    U32 hoisted__U32_952 = 16;
    U8 *new_data = malloc(((U32)(self->cap * hoisted__U32_952)));
    {
        U32 _re_U32_930 = self->count;
        (void)_re_U32_930;
        U32 _rc_U32_930 = 0;
        (void)_rc_U32_930;
        Bool hoisted__Bool_949 = ((Bool)(_rc_U32_930 <= _re_U32_930));
        if (hoisted__Bool_949) {
            while (1) {
                Bool _wcond_Bool_931 = ((Bool)(_rc_U32_930 < _re_U32_930));
                (void)_wcond_Bool_931;
                if (_wcond_Bool_931) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_930);
                (++_rc_U32_930);
                U32 hoisted__U32_932 = 16;
                U32 hoisted__U32_933 = ((U32)(i * hoisted__U32_932));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_933)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_934 = 16;
                U32 hoisted__U32_935 = ((U32)(i * hoisted__U32_934));
                void *hoisted__v_936 = ((void *)((U8 *)(new_data) + (hoisted__U32_935)));
                U32 hoisted__U32_937 = 16;
                memcpy(hoisted__v_936, cloned, hoisted__U32_937);
                I32 hoisted__I32_938 = 0;
                U32 hoisted__U32_939 = 16;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_938, hoisted__U32_939); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_940 = ((Bool)(_rc_U32_930 > _re_U32_930));
                (void)_wcond_Bool_940;
                if (_wcond_Bool_940) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_930);
                (--_rc_U32_930);
                U32 hoisted__U32_941 = 16;
                U32 hoisted__U32_942 = ((U32)(i * hoisted__U32_941));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_942)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_943 = 16;
                U32 hoisted__U32_944 = ((U32)(i * hoisted__U32_943));
                void *hoisted__v_945 = ((void *)((U8 *)(new_data) + (hoisted__U32_944)));
                U32 hoisted__U32_946 = 16;
                memcpy(hoisted__v_945, cloned, hoisted__U32_946);
                I32 hoisted__I32_947 = 0;
                U32 hoisted__U32_948 = 16;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_947, hoisted__U32_948); };
                Str_delete(cloned, 1);
            }
        }
    }
    Vec__Str *hoisted__Vec__Str_953 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_953->data = new_data;
    hoisted__Vec__Str_953->count = self->count;
    hoisted__Vec__Str_953->cap = self->cap;
    return hoisted__Vec__Str_953;
    __builtin_unreachable();
}

USize Vec__Str_size(void) {
    U32 hoisted__U32_954 = 16;
    return hoisted__U32_954;
    __builtin_unreachable();
}

USize Dynamic_size(void) {
    U32 hoisted__U32_957 = 8;
    return hoisted__U32_957;
    __builtin_unreachable();
}

void * Dynamic_clone(void * self) {
    U8 *out = malloc(8);
    U32 hoisted__U32_958 = 8;
    memcpy(out, self, hoisted__U32_958);
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
    U32 hoisted__U32_1065 = 1;
    return hoisted__U32_1065;
    __builtin_unreachable();
}

U64 U8_hash(U8 self, HashFn hasher) {
    U32 hoisted__U32_1132 = 1;
    U64 hoisted__U64_1133 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1132); });
    return hoisted__U64_1133;
    __builtin_unreachable();
}

void U32_delete(U32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize U32_size(void) {
    U32 hoisted__U32_1219 = 4;
    return hoisted__U32_1219;
    __builtin_unreachable();
}

U64 U32_hash(U32 self, HashFn hasher) {
    U32 hoisted__U32_1286 = 4;
    U64 hoisted__U64_1287 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1286); });
    return hoisted__U64_1287;
    __builtin_unreachable();
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *hoisted__Str_1288 = U64_to_str_ext(val);
    return hoisted__Str_1288;
    __builtin_unreachable();
}

void U64_delete(U64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize U64_size(void) {
    U32 hoisted__U32_1293 = 8;
    return hoisted__U32_1293;
    __builtin_unreachable();
}

U64 U64_hash(U64 self, HashFn hasher) {
    U32 hoisted__U32_1360 = 8;
    U64 hoisted__U64_1361 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1360); });
    return hoisted__U64_1361;
    __builtin_unreachable();
}

void I8_delete(I8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize I8_size(void) {
    U32 hoisted__U32_1378 = 1;
    return hoisted__U32_1378;
    __builtin_unreachable();
}

U64 I8_hash(I8 self, HashFn hasher) {
    U32 hoisted__U32_1379 = 1;
    U64 hoisted__U64_1380 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1379); });
    return hoisted__U64_1380;
    __builtin_unreachable();
}

void I32_delete(I32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize I32_size(void) {
    U32 hoisted__U32_1527 = 4;
    return hoisted__U32_1527;
    __builtin_unreachable();
}

U64 I32_hash(I32 self, HashFn hasher) {
    U32 hoisted__U32_1639 = 4;
    U64 hoisted__U64_1640 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1639); });
    return hoisted__U64_1640;
    __builtin_unreachable();
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1649 = 0;
    Bool hoisted__Bool_1650 = ((Bool)(val < hoisted__I64_1649));
    if (hoisted__Bool_1650) {
        U64 hoisted__U64_1641 = 0ULL;
        U64 hoisted__U64_1642 = (U64)(val);
        U64 mag = ((U64)(hoisted__U64_1641 - hoisted__U64_1642));
        U32 hoisted__U32_1643 = 2;
        Array__Str *_va_Array_39 = Array__Str_new(hoisted__U32_1643);
        (void)_va_Array_39;
        I64 _va_Array_39_ek = 0;
        (void)_va_Array_39_ek;
        U32 hoisted__U32_1644 = 0;
        static Str hoisted__Str_1645 = (Str){.c_str = (void *)"-", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_39, hoisted__U32_1644, &hoisted__Str_1645, &_va_Array_39_ek);
        U32 hoisted__U32_1646 = 1;
        Str *hoisted__Str_1647 = U64_to_str(mag);
        Array__Str_set(_va_Array_39, hoisted__U32_1646, hoisted__Str_1647, &_va_Array_39_ek);
        Str *hoisted__Str_1648 = format(_va_Array_39);
        return hoisted__Str_1648;
    }
    U64 hoisted__U64_1651 = (U64)(val);
    Str *hoisted__Str_1652 = U64_to_str(hoisted__U64_1651);
    return hoisted__Str_1652;
    __builtin_unreachable();
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize I64_size(void) {
    U32 hoisted__U32_1666 = 8;
    return hoisted__U32_1666;
    __builtin_unreachable();
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_1792 = 8;
    U64 hoisted__U64_1793 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1792); });
    return hoisted__U64_1793;
    __builtin_unreachable();
}

void F32_delete(F32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize F32_size(void) {
    U32 hoisted__U32_1795 = 4;
    return hoisted__U32_1795;
    __builtin_unreachable();
}

U64 F32_hash(F32 self, HashFn hasher) {
    U32 hoisted__U32_1811 = 4;
    U64 hoisted__U64_1812 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, F32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1811); });
    return hoisted__U64_1812;
    __builtin_unreachable();
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_1855 = ((Bool)(a == b));
    if (hoisted__Bool_1855) {
        I64 hoisted__I64_1853 = 0;
        return hoisted__I64_1853;
    }
    if (b) {
        I64 hoisted__I64_1854 = -1;
        return hoisted__I64_1854;
    }
    I64 hoisted__I64_1856 = 1;
    return hoisted__I64_1856;
    __builtin_unreachable();
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize Bool_size(void) {
    U32 hoisted__U32_1857 = 1;
    return hoisted__U32_1857;
    __builtin_unreachable();
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_1858 = 1;
    U64 hoisted__U64_1859 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1858); });
    return hoisted__U64_1859;
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
    Bool hoisted__Bool_1929 = ((Bool)((((Primitive *)(self))->tag) == (((Primitive *)(other))->tag)));
    return hoisted__Bool_1929;
    __builtin_unreachable();
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1951 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    if (hoisted__Bool_1951) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
        return _r; }
    }
    Bool hoisted__Bool_1952 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    if (hoisted__Bool_1952) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
        return _r; }
    }
    Bool hoisted__Bool_1953 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    if (hoisted__Bool_1953) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
        return _r; }
    }
    Bool hoisted__Bool_1954 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    if (hoisted__Bool_1954) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
        return _r; }
    }
    Bool hoisted__Bool_1955 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    if (hoisted__Bool_1955) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
        return _r; }
    }
    Bool hoisted__Bool_1956 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    if (hoisted__Bool_1956) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
        return _r; }
    }
    Bool hoisted__Bool_1957 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    if (hoisted__Bool_1957) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
        return _r; }
    }
    Bool hoisted__Bool_1958 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    if (hoisted__Bool_1958) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
        return _r; }
    }
    Bool hoisted__Bool_1959 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    if (hoisted__Bool_1959) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
        return _r; }
    }
    Bool hoisted__Bool_1960 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    if (hoisted__Bool_1960) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
        return _r; }
    }
    static Str hoisted__Str_1961 = (Str){.c_str = (void *)"Primitive.clone:16:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    UNREACHABLE(&hoisted__Str_1961);
    Str_delete(&hoisted__Str_1961, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
    __builtin_unreachable();
}

USize Primitive_size(void) {
    U32 hoisted__U32_1962 = 1;
    return hoisted__U32_1962;
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
    Bool hoisted__Bool_2015 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Struct}))->tag)));
    if (hoisted__Bool_2015) {
        Str *hoisted__Str_2005 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        Bool hoisted__Bool_2006 = 0;
        Str_delete(hoisted__Str_2005, hoisted__Bool_2006);
    }
    Bool hoisted__Bool_2016 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Enum}))->tag)));
    if (hoisted__Bool_2016) {
        Str *hoisted__Str_2007 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        Bool hoisted__Bool_2008 = 0;
        Str_delete(hoisted__Str_2007, hoisted__Bool_2008);
    }
    Bool hoisted__Bool_2017 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Custom}))->tag)));
    if (hoisted__Bool_2017) {
        Str *hoisted__Str_2009 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        Bool hoisted__Bool_2010 = 0;
        Str_delete(hoisted__Str_2009, hoisted__Bool_2010);
    }
    Bool hoisted__Bool_2018 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Primitive}))->tag)));
    if (hoisted__Bool_2018) {
        Primitive *hoisted__Primitive_2011 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        Bool hoisted__Bool_2012 = 0;
        Primitive_delete(hoisted__Primitive_2011, hoisted__Bool_2012);
    }
    Bool hoisted__Bool_2019 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_FuncPtrSig}))->tag)));
    if (hoisted__Bool_2019) {
        Str *hoisted__Str_2013 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        Bool hoisted__Bool_2014 = 0;
        Str_delete(hoisted__Str_2013, hoisted__Bool_2014);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2092 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Unknown}))->tag)));
    if (hoisted__Bool_2092) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
        return _r; }
    }
    Bool hoisted__Bool_2093 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_None}))->tag)));
    if (hoisted__Bool_2093) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
        return _r; }
    }
    Bool hoisted__Bool_2094 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Struct}))->tag)));
    if (hoisted__Bool_2094) {
        Str *_clone_payload_Struct_2 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2082 = Str_clone(_clone_payload_Struct_2);
        Type *hoisted__Type_2083 = Type_Struct(hoisted__Str_2082);
        return hoisted__Type_2083;
    }
    Bool hoisted__Bool_2095 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_StructDef}))->tag)));
    if (hoisted__Bool_2095) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
        return _r; }
    }
    Bool hoisted__Bool_2096 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Enum}))->tag)));
    if (hoisted__Bool_2096) {
        Str *_clone_payload_Enum_4 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2084 = Str_clone(_clone_payload_Enum_4);
        Type *hoisted__Type_2085 = Type_Enum(hoisted__Str_2084);
        return hoisted__Type_2085;
    }
    Bool hoisted__Bool_2097 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_EnumDef}))->tag)));
    if (hoisted__Bool_2097) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
        return _r; }
    }
    Bool hoisted__Bool_2098 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_FuncDef}))->tag)));
    if (hoisted__Bool_2098) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
        return _r; }
    }
    Bool hoisted__Bool_2099 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_FuncPtr}))->tag)));
    if (hoisted__Bool_2099) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
        return _r; }
    }
    Bool hoisted__Bool_2100 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Dynamic}))->tag)));
    if (hoisted__Bool_2100) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
        return _r; }
    }
    Bool hoisted__Bool_2101 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Custom}))->tag)));
    if (hoisted__Bool_2101) {
        Str *_clone_payload_Custom_9 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2086 = Str_clone(_clone_payload_Custom_9);
        Type *hoisted__Type_2087 = Type_Custom(hoisted__Str_2086);
        return hoisted__Type_2087;
    }
    Bool hoisted__Bool_2102 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Primitive}))->tag)));
    if (hoisted__Bool_2102) {
        Primitive *_clone_payload_Primitive_10 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2088 = DEREF(_clone_payload_Primitive_10);
        Type *hoisted__Type_2089 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2088; _oa; }));
        return hoisted__Type_2089;
    }
    Bool hoisted__Bool_2103 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_FuncPtrSig}))->tag)));
    if (hoisted__Bool_2103) {
        Str *_clone_payload_FuncPtrSig_11 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)_clone_payload_FuncPtrSig_11;
        (void)_clone_payload_FuncPtrSig_11;
        Str *hoisted__Str_2090 = Str_clone(_clone_payload_FuncPtrSig_11);
        Type *hoisted__Type_2091 = Type_FuncPtrSig(hoisted__Str_2090);
        return hoisted__Type_2091;
    }
    { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Body;
    return _r; }
    __builtin_unreachable();
}

USize Type_size(void) {
    U32 hoisted__U32_2104 = 24;
    return hoisted__U32_2104;
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
    Bool hoisted__Bool_2116 = ((Bool)((((FuncType *)(self))->tag) == (((FuncType *)(other))->tag)));
    return hoisted__Bool_2116;
    __builtin_unreachable();
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2140 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    if (hoisted__Bool_2140) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
        return _r; }
    }
    Bool hoisted__Bool_2141 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    if (hoisted__Bool_2141) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
        return _r; }
    }
    Bool hoisted__Bool_2142 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    if (hoisted__Bool_2142) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
        return _r; }
    }
    Bool hoisted__Bool_2143 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    if (hoisted__Bool_2143) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
        return _r; }
    }
    Bool hoisted__Bool_2144 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    if (hoisted__Bool_2144) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
        return _r; }
    }
    Bool hoisted__Bool_2145 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    if (hoisted__Bool_2145) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
        return _r; }
    }
    Bool hoisted__Bool_2146 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    if (hoisted__Bool_2146) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
        return _r; }
    }
    Bool hoisted__Bool_2147 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    if (hoisted__Bool_2147) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
        return _r; }
    }
    Bool hoisted__Bool_2148 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreFunc});
    if (hoisted__Bool_2148) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreFunc;
        return _r; }
    }
    Bool hoisted__Bool_2149 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreProc});
    if (hoisted__Bool_2149) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreProc;
        return _r; }
    }
    Bool hoisted__Bool_2150 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreLazyFunc});
    if (hoisted__Bool_2150) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreLazyFunc;
        return _r; }
    }
    static Str hoisted__Str_2151 = (Str){.c_str = (void *)"FuncType.clone:71:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    UNREACHABLE(&hoisted__Str_2151);
    Str_delete(&hoisted__Str_2151, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
    __builtin_unreachable();
}

USize FuncType_size(void) {
    U32 hoisted__U32_2152 = 1;
    return hoisted__U32_2152;
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
    Bool hoisted__Bool_2153 = ((Bool)((((OwnType *)(self))->tag) == (((OwnType *)(other))->tag)));
    return hoisted__Bool_2153;
    __builtin_unreachable();
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2161 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    if (hoisted__Bool_2161) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
        return _r; }
    }
    Bool hoisted__Bool_2162 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    if (hoisted__Bool_2162) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
        return _r; }
    }
    Bool hoisted__Bool_2163 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    if (hoisted__Bool_2163) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
        return _r; }
    }
    static Str hoisted__Str_2164 = (Str){.c_str = (void *)"OwnType.clone:109:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    UNREACHABLE(&hoisted__Str_2164);
    Str_delete(&hoisted__Str_2164, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
    __builtin_unreachable();
}

USize OwnType_size(void) {
    U32 hoisted__U32_2165 = 1;
    return hoisted__U32_2165;
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
    Bool hoisted__Bool_2166 = ((Bool)((((GcStorage *)(self))->tag) == (((GcStorage *)(other))->tag)));
    return hoisted__Bool_2166;
    __builtin_unreachable();
}

void GcStorage_delete(GcStorage * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

GcStorage * GcStorage_clone(GcStorage * self) {
    Bool hoisted__Bool_2174 = GcStorage_eq(self, &(GcStorage){.tag = GcStorage_TAG_Unset});
    if (hoisted__Bool_2174) {
        { GcStorage *_r = malloc(sizeof(GcStorage)); _r->tag = GcStorage_TAG_Unset;
        return _r; }
    }
    Bool hoisted__Bool_2175 = GcStorage_eq(self, &(GcStorage){.tag = GcStorage_TAG_Stack});
    if (hoisted__Bool_2175) {
        { GcStorage *_r = malloc(sizeof(GcStorage)); _r->tag = GcStorage_TAG_Stack;
        return _r; }
    }
    Bool hoisted__Bool_2176 = GcStorage_eq(self, &(GcStorage){.tag = GcStorage_TAG_HeapBox});
    if (hoisted__Bool_2176) {
        { GcStorage *_r = malloc(sizeof(GcStorage)); _r->tag = GcStorage_TAG_HeapBox;
        return _r; }
    }
    static Str hoisted__Str_2177 = (Str){.c_str = (void *)"GcStorage.clone:120:1", .count = 21ULL, .cap = TIL_CAP_LIT};
    UNREACHABLE(&hoisted__Str_2177);
    Str_delete(&hoisted__Str_2177, (Bool){0});
    { GcStorage *_r = malloc(sizeof(GcStorage)); _r->tag = GcStorage_TAG_Unset;
    return _r; }
    __builtin_unreachable();
}

USize GcStorage_size(void) {
    U32 hoisted__U32_2178 = 1;
    return hoisted__U32_2178;
    __builtin_unreachable();
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2180 = Expr_clone(self->default_value);
    Declaration *hoisted__Declaration_2181 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2181->name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2181->doc = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2181->explicit_type = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    hoisted__Declaration_2181->is_mut = self->is_mut;
    hoisted__Declaration_2181->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2181->is_priv = self->is_priv;
    hoisted__Declaration_2181->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2181->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2181->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2181->default_value = hoisted__Expr_2180;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2181->orig_name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    { GcStorage *_ca = GcStorage_clone(&self->gc_storage); hoisted__Declaration_2181->gc_storage = *_ca; free(_ca); }
    return hoisted__Declaration_2181;
    __builtin_unreachable();
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2183 = 0;
    Str_delete(&self->name, hoisted__Bool_2183);
    Bool hoisted__Bool_2184 = 0;
    Str_delete(&self->doc, hoisted__Bool_2184);
    Bool hoisted__Bool_2185 = 0;
    Str_delete(&self->explicit_type, hoisted__Bool_2185);
    Bool hoisted__Bool_2186 = 0;
    Bool_delete(&self->is_mut, hoisted__Bool_2186);
    Bool hoisted__Bool_2187 = 0;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2187);
    Bool hoisted__Bool_2188 = 0;
    Bool_delete(&self->is_priv, hoisted__Bool_2188);
    Bool hoisted__Bool_2189 = 0;
    Bool_delete(&self->used, hoisted__Bool_2189);
    Bool hoisted__Bool_2190 = 0;
    OwnType_delete(&self->own_type, hoisted__Bool_2190);
    Bool hoisted__Bool_2191 = 0;
    Type_delete(&self->til_type, hoisted__Bool_2191);
    Bool hoisted__Bool_2192 = ((Bool)((UPtr)(self->default_value) == 0));
    Bool hoisted__Bool_2193 = ((Bool)(!(hoisted__Bool_2192)));
    if (hoisted__Bool_2193) {
        Bool hoisted__Bool_2182 = 1;
        Expr_delete(self->default_value, hoisted__Bool_2182);
    }
    Bool hoisted__Bool_2194 = 0;
    Str_delete(&self->orig_name, hoisted__Bool_2194);
    Bool hoisted__Bool_2195 = 0;
    GcStorage_delete(&self->gc_storage, hoisted__Bool_2195);
    if (call_free) {
        free(self);
    }
}

USize Declaration_size(void) {
    U32 hoisted__U32_2196 = 112;
    return hoisted__U32_2196;
    __builtin_unreachable();
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2198 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2198->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2198->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2198->return_type = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2198->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2198->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2198->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2198->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2198->return_shallow_explicit = self->return_shallow_explicit;
    hoisted__FunctionDef_2198->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2198->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2198->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2198->closure_name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    hoisted__FunctionDef_2198->noreturn = self->noreturn;
    return hoisted__FunctionDef_2198;
    __builtin_unreachable();
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2199 = 0;
    FuncType_delete(&self->func_type, hoisted__Bool_2199);
    Bool hoisted__Bool_2200 = 0;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2200);
    Bool hoisted__Bool_2201 = 0;
    Str_delete(&self->return_type, hoisted__Bool_2201);
    Bool hoisted__Bool_2202 = 0;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2202);
    Bool hoisted__Bool_2203 = 0;
    I32_delete(&self->variadic_index, hoisted__Bool_2203);
    Bool hoisted__Bool_2204 = 0;
    I32_delete(&self->kwargs_index, hoisted__Bool_2204);
    Bool hoisted__Bool_2205 = 0;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2205);
    Bool hoisted__Bool_2206 = 0;
    Bool_delete(&self->return_shallow_explicit, hoisted__Bool_2206);
    Bool hoisted__Bool_2207 = 0;
    Bool_delete(&self->auto_generated, hoisted__Bool_2207);
    Bool hoisted__Bool_2208 = 0;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2208);
    Bool hoisted__Bool_2209 = 0;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2209);
    Bool hoisted__Bool_2210 = 0;
    Str_delete(&self->closure_name, hoisted__Bool_2210);
    Bool hoisted__Bool_2211 = 0;
    Bool_delete(&self->noreturn, hoisted__Bool_2211);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2212 = 0;
    U64 hoisted__U64_2213 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2212); });
    return hoisted__U64_2213;
    __builtin_unreachable();
}

USize FunctionDef_size(void) {
    U32 hoisted__U32_2214 = 112;
    return hoisted__U32_2214;
    __builtin_unreachable();
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2217 = malloc(sizeof(FCallData));
    hoisted__FCallData_2217->is_splat = self->is_splat;
    hoisted__FCallData_2217->does_throw = self->does_throw;
    hoisted__FCallData_2217->is_bang = self->is_bang;
    hoisted__FCallData_2217->own_args = self->own_args;
    hoisted__FCallData_2217->keep_outer_args = self->keep_outer_args;
    hoisted__FCallData_2217->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2217->til_type = *_ca; free(_ca); }
    hoisted__FCallData_2217->noreturn_call = self->noreturn_call;
    hoisted__FCallData_2217->ref_args = self->ref_args;
    return hoisted__FCallData_2217;
    __builtin_unreachable();
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2218 = 0;
    Bool_delete(&self->is_splat, hoisted__Bool_2218);
    Bool hoisted__Bool_2219 = 0;
    Bool_delete(&self->does_throw, hoisted__Bool_2219);
    Bool hoisted__Bool_2220 = 0;
    Bool_delete(&self->is_bang, hoisted__Bool_2220);
    Bool hoisted__Bool_2221 = 0;
    U64_delete(&self->own_args, hoisted__Bool_2221);
    Bool hoisted__Bool_2222 = 0;
    U64_delete(&self->keep_outer_args, hoisted__Bool_2222);
    Bool hoisted__Bool_2223 = 0;
    Bool_delete(&self->swap_replace, hoisted__Bool_2223);
    Bool hoisted__Bool_2224 = 0;
    Type_delete(&self->til_type, hoisted__Bool_2224);
    Bool hoisted__Bool_2225 = 0;
    Bool_delete(&self->noreturn_call, hoisted__Bool_2225);
    Bool hoisted__Bool_2226 = 0;
    U64_delete(&self->ref_args, hoisted__Bool_2226);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2227 = 0;
    U64 hoisted__U64_2228 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2227); });
    return hoisted__U64_2228;
    __builtin_unreachable();
}

USize FCallData_size(void) {
    U32 hoisted__U32_2229 = 72;
    return hoisted__U32_2229;
    __builtin_unreachable();
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2268 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2268->text = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2268->til_type = *_ca; free(_ca); }
    return hoisted__LiteralNumData_2268;
    __builtin_unreachable();
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2269 = 0;
    Str_delete(&self->text, hoisted__Bool_2269);
    Bool hoisted__Bool_2270 = 0;
    Type_delete(&self->til_type, hoisted__Bool_2270);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2271 = 0;
    U64 hoisted__U64_2272 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2271); });
    return hoisted__U64_2272;
    __builtin_unreachable();
}

USize LiteralNumData_size(void) {
    U32 hoisted__U32_2273 = 40;
    return hoisted__U32_2273;
    __builtin_unreachable();
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2283 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2283->name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2283->til_type = *_ca; free(_ca); }
    return hoisted__IdentData_2283;
    __builtin_unreachable();
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2284 = 0;
    Str_delete(&self->name, hoisted__Bool_2284);
    Bool hoisted__Bool_2285 = 0;
    Type_delete(&self->til_type, hoisted__Bool_2285);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2286 = 0;
    U64 hoisted__U64_2287 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2286); });
    return hoisted__U64_2287;
    __builtin_unreachable();
}

USize IdentData_size(void) {
    U32 hoisted__U32_2288 = 40;
    return hoisted__U32_2288;
    __builtin_unreachable();
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2294 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2294->name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2294->til_type = *_ca; free(_ca); }
    return hoisted__FieldAccessData_2294;
    __builtin_unreachable();
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2295 = 0;
    Str_delete(&self->name, hoisted__Bool_2295);
    Bool hoisted__Bool_2296 = 0;
    Type_delete(&self->til_type, hoisted__Bool_2296);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2297 = 0;
    U64 hoisted__U64_2298 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2297); });
    return hoisted__U64_2298;
    __builtin_unreachable();
}

USize FieldAccessData_size(void) {
    U32 hoisted__U32_2299 = 40;
    return hoisted__U32_2299;
    __builtin_unreachable();
}

StructDef * StructDef_clone(StructDef * self) {
    Vec__Declaration *hoisted__Vec__Declaration_2312 = Vec__Declaration_clone(self->fields);
    Vec__Declaration *hoisted__Vec__Declaration_2313 = Vec__Declaration_clone(self->ns_decls);
    Map__Str_USize *hoisted__Map__Str_USize_2314 = Map__Str_USize_clone(self->fields_index);
    Map__Str_USize *hoisted__Map__Str_USize_2315 = Map__Str_USize_clone(self->ns_index);
    StructDef *hoisted__StructDef_2316 = malloc(sizeof(StructDef));
    hoisted__StructDef_2316->fields = hoisted__Vec__Declaration_2312;
    hoisted__StructDef_2316->ns_decls = hoisted__Vec__Declaration_2313;
    hoisted__StructDef_2316->fields_index = hoisted__Map__Str_USize_2314;
    hoisted__StructDef_2316->ns_index = hoisted__Map__Str_USize_2315;
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2316->c_tag = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    hoisted__StructDef_2316->is_interface = self->is_interface;
    hoisted__StructDef_2316->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2316->implements_name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    return hoisted__StructDef_2316;
    __builtin_unreachable();
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2321 = ((Bool)((UPtr)(self->fields) == 0));
    Bool hoisted__Bool_2322 = ((Bool)(!(hoisted__Bool_2321)));
    if (hoisted__Bool_2322) {
        Bool hoisted__Bool_2317 = 1;
        Vec__Declaration_delete(self->fields, hoisted__Bool_2317);
    }
    Bool hoisted__Bool_2323 = ((Bool)((UPtr)(self->ns_decls) == 0));
    Bool hoisted__Bool_2324 = ((Bool)(!(hoisted__Bool_2323)));
    if (hoisted__Bool_2324) {
        Bool hoisted__Bool_2318 = 1;
        Vec__Declaration_delete(self->ns_decls, hoisted__Bool_2318);
    }
    Bool hoisted__Bool_2325 = ((Bool)((UPtr)(self->fields_index) == 0));
    Bool hoisted__Bool_2326 = ((Bool)(!(hoisted__Bool_2325)));
    if (hoisted__Bool_2326) {
        Bool hoisted__Bool_2319 = 1;
        Map__Str_USize_delete(self->fields_index, hoisted__Bool_2319);
    }
    Bool hoisted__Bool_2327 = ((Bool)((UPtr)(self->ns_index) == 0));
    Bool hoisted__Bool_2328 = ((Bool)(!(hoisted__Bool_2327)));
    if (hoisted__Bool_2328) {
        Bool hoisted__Bool_2320 = 1;
        Map__Str_USize_delete(self->ns_index, hoisted__Bool_2320);
    }
    Bool hoisted__Bool_2329 = 0;
    Str_delete(&self->c_tag, hoisted__Bool_2329);
    Bool hoisted__Bool_2330 = 0;
    Bool_delete(&self->is_interface, hoisted__Bool_2330);
    Bool hoisted__Bool_2331 = 0;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2331);
    Bool hoisted__Bool_2332 = 0;
    Str_delete(&self->implements_name, hoisted__Bool_2332);
    if (call_free) {
        free(self);
    }
}

USize StructDef_size(void) {
    U32 hoisted__U32_2333 = 72;
    return hoisted__U32_2333;
    __builtin_unreachable();
}

VariantDef * VariantDef_clone(VariantDef * self) {
    VariantDef *hoisted__VariantDef_2347 = malloc(sizeof(VariantDef));
    { Str *_ca = Str_clone(&self->name); hoisted__VariantDef_2347->name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    { Str *_ca = Str_clone(&self->doc); hoisted__VariantDef_2347->doc = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    { Str *_ca = Str_clone(&self->payload_type); hoisted__VariantDef_2347->payload_type = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    hoisted__VariantDef_2347->payload_const = self->payload_const;
    hoisted__VariantDef_2347->tag_value = self->tag_value;
    hoisted__VariantDef_2347->payload_ref = self->payload_ref;
    return hoisted__VariantDef_2347;
    __builtin_unreachable();
}

void VariantDef_delete(VariantDef * self, Bool call_free) {
    Bool hoisted__Bool_2348 = 0;
    Str_delete(&self->name, hoisted__Bool_2348);
    Bool hoisted__Bool_2349 = 0;
    Str_delete(&self->doc, hoisted__Bool_2349);
    Bool hoisted__Bool_2350 = 0;
    Str_delete(&self->payload_type, hoisted__Bool_2350);
    Bool hoisted__Bool_2351 = 0;
    Bool_delete(&self->payload_const, hoisted__Bool_2351);
    Bool hoisted__Bool_2352 = 0;
    I64_delete(&self->tag_value, hoisted__Bool_2352);
    Bool hoisted__Bool_2353 = 0;
    Bool_delete(&self->payload_ref, hoisted__Bool_2353);
    if (call_free) {
        free(self);
    }
}

U64 VariantDef_hash(VariantDef * self, HashFn hasher) {
    U32 hoisted__U32_2354 = 0;
    U64 hoisted__U64_2355 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, VariantDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2354); });
    return hoisted__U64_2355;
    __builtin_unreachable();
}

USize VariantDef_size(void) {
    U32 hoisted__U32_2356 = 72;
    return hoisted__U32_2356;
    __builtin_unreachable();
}

EnumDef * EnumDef_clone(EnumDef * self) {
    Vec__Declaration *hoisted__Vec__Declaration_2365 = Vec__Declaration_clone(self->ns_decls);
    Map__Str_USize *hoisted__Map__Str_USize_2366 = Map__Str_USize_clone(self->ns_index);
    EnumDef *hoisted__EnumDef_2367 = malloc(sizeof(EnumDef));
    hoisted__EnumDef_2367->ns_decls = hoisted__Vec__Declaration_2365;
    hoisted__EnumDef_2367->ns_index = hoisted__Map__Str_USize_2366;
    { Vec__VariantDef *_ca = Vec__VariantDef_clone(&self->variants); hoisted__EnumDef_2367->variants = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2367->implements_name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    { Str *_ca = Str_clone(&self->tag_type); hoisted__EnumDef_2367->tag_type = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    return hoisted__EnumDef_2367;
    __builtin_unreachable();
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2370 = ((Bool)((UPtr)(self->ns_decls) == 0));
    Bool hoisted__Bool_2371 = ((Bool)(!(hoisted__Bool_2370)));
    if (hoisted__Bool_2371) {
        Bool hoisted__Bool_2368 = 1;
        Vec__Declaration_delete(self->ns_decls, hoisted__Bool_2368);
    }
    Bool hoisted__Bool_2372 = ((Bool)((UPtr)(self->ns_index) == 0));
    Bool hoisted__Bool_2373 = ((Bool)(!(hoisted__Bool_2372)));
    if (hoisted__Bool_2373) {
        Bool hoisted__Bool_2369 = 1;
        Map__Str_USize_delete(self->ns_index, hoisted__Bool_2369);
    }
    Bool hoisted__Bool_2374 = 0;
    Vec__VariantDef_delete(&self->variants, hoisted__Bool_2374);
    Bool hoisted__Bool_2375 = 0;
    Str_delete(&self->implements_name, hoisted__Bool_2375);
    Bool hoisted__Bool_2376 = 0;
    Str_delete(&self->tag_type, hoisted__Bool_2376);
    if (call_free) {
        free(self);
    }
}

USize EnumDef_size(void) {
    U32 hoisted__U32_2377 = 64;
    return hoisted__U32_2377;
    __builtin_unreachable();
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2408 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2408->name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    hoisted__AssignData_2408->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2408->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2408->swap_replace = self->swap_replace;
    hoisted__AssignData_2408->is_move = self->is_move;
    return hoisted__AssignData_2408;
    __builtin_unreachable();
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2409 = 0;
    Str_delete(&self->name, hoisted__Bool_2409);
    Bool hoisted__Bool_2410 = 0;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2410);
    Bool hoisted__Bool_2411 = 0;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2411);
    Bool hoisted__Bool_2412 = 0;
    Bool_delete(&self->swap_replace, hoisted__Bool_2412);
    Bool hoisted__Bool_2413 = 0;
    Bool_delete(&self->is_move, hoisted__Bool_2413);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_2414 = 0;
    U64 hoisted__U64_2415 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2414); });
    return hoisted__U64_2415;
    __builtin_unreachable();
}

USize AssignData_size(void) {
    U32 hoisted__U32_2416 = 24;
    return hoisted__U32_2416;
    __builtin_unreachable();
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_2418 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_2418->name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    hoisted__FieldAssignData_2418->save_old_delete = self->save_old_delete;
    hoisted__FieldAssignData_2418->transfers_own = self->transfers_own;
    hoisted__FieldAssignData_2418->is_move = self->is_move;
    return hoisted__FieldAssignData_2418;
    __builtin_unreachable();
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_2419 = 0;
    Str_delete(&self->name, hoisted__Bool_2419);
    Bool hoisted__Bool_2420 = 0;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2420);
    Bool hoisted__Bool_2421 = 0;
    Bool_delete(&self->transfers_own, hoisted__Bool_2421);
    Bool hoisted__Bool_2422 = 0;
    Bool_delete(&self->is_move, hoisted__Bool_2422);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_2423 = 0;
    U64 hoisted__U64_2424 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2423); });
    return hoisted__U64_2424;
    __builtin_unreachable();
}

USize FieldAssignData_size(void) {
    U32 hoisted__U32_2425 = 24;
    return hoisted__U32_2425;
    __builtin_unreachable();
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_2427 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_2427->name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    hoisted__ForInData_2427->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_2427->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->name2); hoisted__ForInData_2427->name2 = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    hoisted__ForInData_2427->is_mut2 = self->is_mut2;
    return hoisted__ForInData_2427;
    __builtin_unreachable();
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_2428 = 0;
    Str_delete(&self->name, hoisted__Bool_2428);
    Bool hoisted__Bool_2429 = 0;
    Bool_delete(&self->is_mut, hoisted__Bool_2429);
    Bool hoisted__Bool_2430 = 0;
    Type_delete(&self->til_type, hoisted__Bool_2430);
    Bool hoisted__Bool_2431 = 0;
    Str_delete(&self->name2, hoisted__Bool_2431);
    Bool hoisted__Bool_2432 = 0;
    Bool_delete(&self->is_mut2, hoisted__Bool_2432);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_2433 = 0;
    U64 hoisted__U64_2434 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2433); });
    return hoisted__U64_2434;
    __builtin_unreachable();
}

USize ForInData_size(void) {
    U32 hoisted__U32_2435 = 72;
    return hoisted__U32_2435;
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
    Bool hoisted__Bool_2464 = ((Bool)((((Literal *)(self))->tag) == (((Literal *)(&(Literal){.tag = Literal_TAG_Str}))->tag)));
    if (hoisted__Bool_2464) {
        Str *hoisted__Str_2458 = ((void *)((U8 *)(self) + offsetof(Literal, data)));
        Bool hoisted__Bool_2459 = 0;
        Str_delete(hoisted__Str_2458, hoisted__Bool_2459);
    }
    Bool hoisted__Bool_2465 = ((Bool)((((Literal *)(self))->tag) == (((Literal *)(&(Literal){.tag = Literal_TAG_Num}))->tag)));
    if (hoisted__Bool_2465) {
        LiteralNumData *hoisted__LiteralNumData_2460 = ((void *)((U8 *)(self) + offsetof(Literal, data)));
        Bool hoisted__Bool_2461 = 0;
        LiteralNumData_delete(hoisted__LiteralNumData_2460, hoisted__Bool_2461);
    }
    Bool hoisted__Bool_2466 = ((Bool)((((Literal *)(self))->tag) == (((Literal *)(&(Literal){.tag = Literal_TAG_Bool}))->tag)));
    if (hoisted__Bool_2466) {
        Bool *hoisted__Bool_2462 = ((void *)((U8 *)(self) + offsetof(Literal, data)));
        Bool hoisted__Bool_2463 = 0;
        Bool_delete(hoisted__Bool_2462, hoisted__Bool_2463);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    Bool hoisted__Bool_2506 = ((Bool)((((Literal *)(self))->tag) == (((Literal *)(&(Literal){.tag = Literal_TAG_Str}))->tag)));
    if (hoisted__Bool_2506) {
        Str *_clone_payload_Str_0 = ((void *)((U8 *)(self) + offsetof(Literal, data)));
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_2501 = Str_clone(_clone_payload_Str_0);
        Literal *hoisted__Literal_2502 = Literal_Str(hoisted__Str_2501);
        return hoisted__Literal_2502;
    }
    Bool hoisted__Bool_2507 = ((Bool)((((Literal *)(self))->tag) == (((Literal *)(&(Literal){.tag = Literal_TAG_Num}))->tag)));
    if (hoisted__Bool_2507) {
        LiteralNumData *_clone_payload_Num_1 = ((void *)((U8 *)(self) + offsetof(Literal, data)));
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_2503 = LiteralNumData_clone(_clone_payload_Num_1);
        Literal *hoisted__Literal_2504 = Literal_Num(hoisted__LiteralNumData_2503);
        return hoisted__Literal_2504;
    }
    Bool hoisted__Bool_2508 = ((Bool)((((Literal *)(self))->tag) == (((Literal *)(&(Literal){.tag = Literal_TAG_Bool}))->tag)));
    if (hoisted__Bool_2508) {
        Bool *_clone_payload_Bool_2 = ((void *)((U8 *)(self) + offsetof(Literal, data)));
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_2505 = Literal_Bool(_clone_payload_Bool_2);
        return hoisted__Literal_2505;
    }
    Bool hoisted__Bool_2509 = ((Bool)((((Literal *)(self))->tag) == (((Literal *)(&(Literal){.tag = Literal_TAG_Null}))->tag)));
    if (hoisted__Bool_2509) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
        return _r; }
    }
    Bool hoisted__Bool_2510 = ((Bool)((((Literal *)(self))->tag) == (((Literal *)(&(Literal){.tag = Literal_TAG_MapLit}))->tag)));
    if (hoisted__Bool_2510) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
        return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
    __builtin_unreachable();
}

USize Literal_size(void) {
    U32 hoisted__U32_2511 = 48;
    return hoisted__U32_2511;
    __builtin_unreachable();
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_2514 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_2514->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_2514->result_temp = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    return hoisted__MatchData_2514;
    __builtin_unreachable();
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_2515 = 0;
    Type_delete(&self->til_type, hoisted__Bool_2515);
    Bool hoisted__Bool_2516 = 0;
    Str_delete(&self->result_temp, hoisted__Bool_2516);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_2517 = 0;
    U64 hoisted__U64_2518 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2517); });
    return hoisted__U64_2518;
    __builtin_unreachable();
}

USize MatchData_size(void) {
    U32 hoisted__U32_2519 = 40;
    return hoisted__U32_2519;
    __builtin_unreachable();
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_2524 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_2524->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__CaptureBlockData_2524->closure_name = *_ca; if (_ca->cap != TIL_CAP_LIT) { free(_ca); } }
    return hoisted__CaptureBlockData_2524;
    __builtin_unreachable();
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_2525 = 0;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2525);
    Bool hoisted__Bool_2526 = 0;
    Str_delete(&self->closure_name, hoisted__Bool_2526);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_2527 = 0;
    U64 hoisted__U64_2528 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2527); });
    return hoisted__U64_2528;
    __builtin_unreachable();
}

USize CaptureBlockData_size(void) {
    U32 hoisted__U32_2529 = 32;
    return hoisted__U32_2529;
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
    Bool hoisted__Bool_2884 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Literal}))->tag)));
    if (hoisted__Bool_2884) {
        Literal *hoisted__Literal_2854 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        Bool hoisted__Bool_2855 = 0;
        Literal_delete(hoisted__Literal_2854, hoisted__Bool_2855);
    }
    Bool hoisted__Bool_2885 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Ident}))->tag)));
    if (hoisted__Bool_2885) {
        IdentData *hoisted__IdentData_2856 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        Bool hoisted__Bool_2857 = 0;
        IdentData_delete(hoisted__IdentData_2856, hoisted__Bool_2857);
    }
    Bool hoisted__Bool_2886 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Decl}))->tag)));
    if (hoisted__Bool_2886) {
        Declaration *hoisted__Declaration_2858 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        Bool hoisted__Bool_2859 = 0;
        Declaration_delete(hoisted__Declaration_2858, hoisted__Bool_2859);
    }
    Bool hoisted__Bool_2887 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Assign}))->tag)));
    if (hoisted__Bool_2887) {
        AssignData *hoisted__AssignData_2860 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        Bool hoisted__Bool_2861 = 0;
        AssignData_delete(hoisted__AssignData_2860, hoisted__Bool_2861);
    }
    Bool hoisted__Bool_2888 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_FCall}))->tag)));
    if (hoisted__Bool_2888) {
        FCallData *hoisted__FCallData_2862 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        Bool hoisted__Bool_2863 = 0;
        FCallData_delete(hoisted__FCallData_2862, hoisted__Bool_2863);
    }
    Bool hoisted__Bool_2889 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_FuncDef}))->tag)));
    if (hoisted__Bool_2889) {
        FunctionDef *hoisted__FunctionDef_2864 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        Bool hoisted__Bool_2865 = 0;
        FunctionDef_delete(hoisted__FunctionDef_2864, hoisted__Bool_2865);
    }
    Bool hoisted__Bool_2890 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_StructDef}))->tag)));
    if (hoisted__Bool_2890) {
        StructDef *hoisted__StructDef_2866 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        Bool hoisted__Bool_2867 = 0;
        StructDef_delete(hoisted__StructDef_2866, hoisted__Bool_2867);
    }
    Bool hoisted__Bool_2891 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_EnumDef}))->tag)));
    if (hoisted__Bool_2891) {
        EnumDef *hoisted__EnumDef_2868 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        Bool hoisted__Bool_2869 = 0;
        EnumDef_delete(hoisted__EnumDef_2868, hoisted__Bool_2869);
    }
    Bool hoisted__Bool_2892 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAccess}))->tag)));
    if (hoisted__Bool_2892) {
        FieldAccessData *hoisted__FieldAccessData_2870 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        Bool hoisted__Bool_2871 = 0;
        FieldAccessData_delete(hoisted__FieldAccessData_2870, hoisted__Bool_2871);
    }
    Bool hoisted__Bool_2893 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAssign}))->tag)));
    if (hoisted__Bool_2893) {
        FieldAssignData *hoisted__FieldAssignData_2872 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        Bool hoisted__Bool_2873 = 0;
        FieldAssignData_delete(hoisted__FieldAssignData_2872, hoisted__Bool_2873);
    }
    Bool hoisted__Bool_2894 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_ForIn}))->tag)));
    if (hoisted__Bool_2894) {
        ForInData *hoisted__ForInData_2874 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        Bool hoisted__Bool_2875 = 0;
        ForInData_delete(hoisted__ForInData_2874, hoisted__Bool_2875);
    }
    Bool hoisted__Bool_2895 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_NamedArg}))->tag)));
    if (hoisted__Bool_2895) {
        Str *hoisted__Str_2876 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        Bool hoisted__Bool_2877 = 0;
        Str_delete(hoisted__Str_2876, hoisted__Bool_2877);
    }
    Bool hoisted__Bool_2896 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Match}))->tag)));
    if (hoisted__Bool_2896) {
        MatchData *hoisted__MatchData_2878 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        Bool hoisted__Bool_2879 = 0;
        MatchData_delete(hoisted__MatchData_2878, hoisted__Bool_2879);
    }
    Bool hoisted__Bool_2897 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_CaptureBlock}))->tag)));
    if (hoisted__Bool_2897) {
        CaptureBlockData *hoisted__CaptureBlockData_2880 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        Bool hoisted__Bool_2881 = 0;
        CaptureBlockData_delete(hoisted__CaptureBlockData_2880, hoisted__Bool_2881);
    }
    Bool hoisted__Bool_2898 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_BodyValue}))->tag)));
    if (hoisted__Bool_2898) {
        CaptureBlockData *hoisted__CaptureBlockData_2882 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        Bool hoisted__Bool_2883 = 0;
        CaptureBlockData_delete(hoisted__CaptureBlockData_2882, hoisted__Bool_2883);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    Bool hoisted__Bool_3093 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Body}))->tag)));
    if (hoisted__Bool_3093) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
        return _r; }
    }
    Bool hoisted__Bool_3094 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Literal}))->tag)));
    if (hoisted__Bool_3094) {
        Literal *_clone_payload_Literal_1 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3063 = Literal_clone(_clone_payload_Literal_1);
        NodeType *hoisted__NodeType_3064 = NodeType_Literal(hoisted__Literal_3063);
        return hoisted__NodeType_3064;
    }
    Bool hoisted__Bool_3095 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Ident}))->tag)));
    if (hoisted__Bool_3095) {
        IdentData *_clone_payload_Ident_2 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3065 = IdentData_clone(_clone_payload_Ident_2);
        NodeType *hoisted__NodeType_3066 = NodeType_Ident(hoisted__IdentData_3065);
        return hoisted__NodeType_3066;
    }
    Bool hoisted__Bool_3096 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Decl}))->tag)));
    if (hoisted__Bool_3096) {
        Declaration *_clone_payload_Decl_3 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3067 = Declaration_clone(_clone_payload_Decl_3);
        NodeType *hoisted__NodeType_3068 = NodeType_Decl(hoisted__Declaration_3067);
        return hoisted__NodeType_3068;
    }
    Bool hoisted__Bool_3097 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Assign}))->tag)));
    if (hoisted__Bool_3097) {
        AssignData *_clone_payload_Assign_4 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3069 = AssignData_clone(_clone_payload_Assign_4);
        NodeType *hoisted__NodeType_3070 = NodeType_Assign(hoisted__AssignData_3069);
        return hoisted__NodeType_3070;
    }
    Bool hoisted__Bool_3098 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_FCall}))->tag)));
    if (hoisted__Bool_3098) {
        FCallData *_clone_payload_FCall_5 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3071 = FCallData_clone(_clone_payload_FCall_5);
        NodeType *hoisted__NodeType_3072 = NodeType_FCall(hoisted__FCallData_3071);
        return hoisted__NodeType_3072;
    }
    Bool hoisted__Bool_3099 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_FuncDef}))->tag)));
    if (hoisted__Bool_3099) {
        FunctionDef *_clone_payload_FuncDef_6 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3073 = FunctionDef_clone(_clone_payload_FuncDef_6);
        NodeType *hoisted__NodeType_3074 = NodeType_FuncDef(hoisted__FunctionDef_3073);
        return hoisted__NodeType_3074;
    }
    Bool hoisted__Bool_3100 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_StructDef}))->tag)));
    if (hoisted__Bool_3100) {
        StructDef *_clone_payload_StructDef_7 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3075 = StructDef_clone(_clone_payload_StructDef_7);
        NodeType *hoisted__NodeType_3076 = NodeType_StructDef(hoisted__StructDef_3075);
        return hoisted__NodeType_3076;
    }
    Bool hoisted__Bool_3101 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_EnumDef}))->tag)));
    if (hoisted__Bool_3101) {
        EnumDef *_clone_payload_EnumDef_8 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3077 = EnumDef_clone(_clone_payload_EnumDef_8);
        NodeType *hoisted__NodeType_3078 = NodeType_EnumDef(hoisted__EnumDef_3077);
        return hoisted__NodeType_3078;
    }
    Bool hoisted__Bool_3102 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAccess}))->tag)));
    if (hoisted__Bool_3102) {
        FieldAccessData *_clone_payload_FieldAccess_9 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3079 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        NodeType *hoisted__NodeType_3080 = NodeType_FieldAccess(hoisted__FieldAccessData_3079);
        return hoisted__NodeType_3080;
    }
    Bool hoisted__Bool_3103 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAssign}))->tag)));
    if (hoisted__Bool_3103) {
        FieldAssignData *_clone_payload_FieldAssign_10 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3081 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        NodeType *hoisted__NodeType_3082 = NodeType_FieldAssign(hoisted__FieldAssignData_3081);
        return hoisted__NodeType_3082;
    }
    Bool hoisted__Bool_3104 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Return}))->tag)));
    if (hoisted__Bool_3104) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
        return _r; }
    }
    Bool hoisted__Bool_3105 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_If}))->tag)));
    if (hoisted__Bool_3105) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
        return _r; }
    }
    Bool hoisted__Bool_3106 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_While}))->tag)));
    if (hoisted__Bool_3106) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
        return _r; }
    }
    Bool hoisted__Bool_3107 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_ForIn}))->tag)));
    if (hoisted__Bool_3107) {
        ForInData *_clone_payload_ForIn_14 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3083 = ForInData_clone(_clone_payload_ForIn_14);
        NodeType *hoisted__NodeType_3084 = NodeType_ForIn(hoisted__ForInData_3083);
        return hoisted__NodeType_3084;
    }
    Bool hoisted__Bool_3108 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_NamedArg}))->tag)));
    if (hoisted__Bool_3108) {
        Str *_clone_payload_NamedArg_15 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3085 = Str_clone(_clone_payload_NamedArg_15);
        NodeType *hoisted__NodeType_3086 = NodeType_NamedArg(hoisted__Str_3085);
        return hoisted__NodeType_3086;
    }
    Bool hoisted__Bool_3109 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Break}))->tag)));
    if (hoisted__Bool_3109) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
        return _r; }
    }
    Bool hoisted__Bool_3110 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Continue}))->tag)));
    if (hoisted__Bool_3110) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
        return _r; }
    }
    Bool hoisted__Bool_3111 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Switch}))->tag)));
    if (hoisted__Bool_3111) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
        return _r; }
    }
    Bool hoisted__Bool_3112 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Match}))->tag)));
    if (hoisted__Bool_3112) {
        MatchData *_clone_payload_Match_19 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3087 = MatchData_clone(_clone_payload_Match_19);
        NodeType *hoisted__NodeType_3088 = NodeType_Match(hoisted__MatchData_3087);
        return hoisted__NodeType_3088;
    }
    Bool hoisted__Bool_3113 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Case}))->tag)));
    if (hoisted__Bool_3113) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
        return _r; }
    }
    Bool hoisted__Bool_3114 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_NoDefaultArg}))->tag)));
    if (hoisted__Bool_3114) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
        return _r; }
    }
    Bool hoisted__Bool_3115 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Throw}))->tag)));
    if (hoisted__Bool_3115) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
        return _r; }
    }
    Bool hoisted__Bool_3116 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Catch}))->tag)));
    if (hoisted__Bool_3116) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
        return _r; }
    }
    Bool hoisted__Bool_3117 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_RestPattern}))->tag)));
    if (hoisted__Bool_3117) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
        return _r; }
    }
    Bool hoisted__Bool_3118 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_CaptureBlock}))->tag)));
    if (hoisted__Bool_3118) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3089 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        NodeType *hoisted__NodeType_3090 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3089);
        return hoisted__NodeType_3090;
    }
    Bool hoisted__Bool_3119 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_Loc}))->tag)));
    if (hoisted__Bool_3119) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
        return _r; }
    }
    Bool hoisted__Bool_3120 = ((Bool)((((NodeType *)(self))->tag) == (((NodeType *)(&(NodeType){.tag = NodeType_TAG_BodyValue}))->tag)));
    if (hoisted__Bool_3120) {
        CaptureBlockData *_clone_payload_BodyValue_27 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_BodyValue_27;
        (void)_clone_payload_BodyValue_27;
        CaptureBlockData *hoisted__CaptureBlockData_3091 = CaptureBlockData_clone(_clone_payload_BodyValue_27);
        NodeType *hoisted__NodeType_3092 = NodeType_BodyValue(hoisted__CaptureBlockData_3091);
        return hoisted__NodeType_3092;
    }
    { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_ListPattern;
    return _r; }
    __builtin_unreachable();
}

USize NodeType_size(void) {
    U32 hoisted__U32_3121 = 120;
    return hoisted__U32_3121;
    __builtin_unreachable();
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3122 = ((Bool)((UPtr)(self) == 0));
    if (hoisted__Bool_3122) {
        return;
    }
    Bool hoisted__Bool_3123 = 0;
    NodeType_delete(&self->node_type, hoisted__Bool_3123);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3164 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3164->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3164->children = *_ca; free(_ca); }
    hoisted__Expr_3164->line = line;
    hoisted__Expr_3164->col = col;
    return hoisted__Expr_3164;
    __builtin_unreachable();
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3354 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3354->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3354->children = *_ca; free(_ca); }
    hoisted__Expr_3354->line = self->line;
    hoisted__Expr_3354->col = self->col;
    return hoisted__Expr_3354;
    __builtin_unreachable();
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3355 = 0;
    U64 hoisted__U64_3356 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3355); });
    return hoisted__U64_3356;
    __builtin_unreachable();
}

USize Expr_size(void) {
    U32 hoisted__U32_3357 = 144;
    return hoisted__U32_3357;
    __builtin_unreachable();
}

Map__Str_USize * Map__Str_USize_new(void) {
    Map__Str_USize *hoisted__Map__Str_USize_3398 = malloc(sizeof(Map__Str_USize));
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__Str_USize_3398->keys = *_ca; free(_ca); }
    { Vec__USize *_ca = Vec__USize_new(); hoisted__Map__Str_USize_3398->values = *_ca; free(_ca); }
    return hoisted__Map__Str_USize_3398;
    __builtin_unreachable();
}

void Map__Str_USize_delete(Map__Str_USize * self, Bool call_free) {
    Bool hoisted__Bool_3519 = 0;
    Vec__Str_delete(&self->keys, hoisted__Bool_3519);
    Bool hoisted__Bool_3520 = 0;
    Vec__USize_delete(&self->values, hoisted__Bool_3520);
    if (call_free) {
        free(self);
    }
}

Map__Str_USize * Map__Str_USize_clone(Map__Str_USize * self) {
    Map__Str_USize *hoisted__Map__Str_USize_3521 = malloc(sizeof(Map__Str_USize));
    { Vec__Str *_ca = Vec__Str_clone(&self->keys); hoisted__Map__Str_USize_3521->keys = *_ca; free(_ca); }
    { Vec__USize *_ca = Vec__USize_clone(&self->values); hoisted__Map__Str_USize_3521->values = *_ca; free(_ca); }
    return hoisted__Map__Str_USize_3521;
    __builtin_unreachable();
}

U64 Map__Str_USize_hash(Map__Str_USize * self, HashFn hasher) {
    U32 hoisted__U32_3522 = 0;
    U64 hoisted__U64_3523 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__Str_USize *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3522); });
    return hoisted__U64_3523;
    __builtin_unreachable();
}

USize Map__Str_USize_size(void) {
    U32 hoisted__U32_3524 = 32;
    return hoisted__U32_3524;
    __builtin_unreachable();
}

Vec__VariantDef * Vec__VariantDef_new(void) {
    U8 *hoisted__U8_3525 = malloc(sizeof(U8));
    *hoisted__U8_3525 = 0;
    U32 hoisted__U32_3526 = 0;
    I64 hoisted__I64_3527 = 0;
    Vec__VariantDef *hoisted__Vec__VariantDef_3528 = malloc(sizeof(Vec__VariantDef));
    hoisted__Vec__VariantDef_3528->data = hoisted__U8_3525;
    hoisted__Vec__VariantDef_3528->count = hoisted__U32_3526;
    hoisted__Vec__VariantDef_3528->cap = hoisted__I64_3527;
    return hoisted__Vec__VariantDef_3528;
    __builtin_unreachable();
}

void Vec__VariantDef_clear(Vec__VariantDef * self) {
    {
        U32 _re_U32_3539 = self->count;
        (void)_re_U32_3539;
        U32 _rc_U32_3539 = 0;
        (void)_rc_U32_3539;
        Bool hoisted__Bool_3550 = ((Bool)(_rc_U32_3539 <= _re_U32_3539));
        if (hoisted__Bool_3550) {
            while (1) {
                Bool _wcond_Bool_3540 = ((Bool)(_rc_U32_3539 < _re_U32_3539));
                (void)_wcond_Bool_3540;
                if (_wcond_Bool_3540) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_3539);
                (++_rc_U32_3539);
                U32 hoisted__U32_3541 = 72;
                U32 hoisted__U32_3542 = ((U32)(i * hoisted__U32_3541));
                VariantDef *hoisted__VariantDef_3543 = ((void *)((U8 *)(self->data) + (hoisted__U32_3542)));
                Bool hoisted__Bool_3544 = 0;
                VariantDef_delete(hoisted__VariantDef_3543, hoisted__Bool_3544);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3545 = ((Bool)(_rc_U32_3539 > _re_U32_3539));
                (void)_wcond_Bool_3545;
                if (_wcond_Bool_3545) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_3539);
                (--_rc_U32_3539);
                U32 hoisted__U32_3546 = 72;
                U32 hoisted__U32_3547 = ((U32)(i * hoisted__U32_3546));
                VariantDef *hoisted__VariantDef_3548 = ((void *)((U8 *)(self->data) + (hoisted__U32_3547)));
                Bool hoisted__Bool_3549 = 0;
                VariantDef_delete(hoisted__VariantDef_3548, hoisted__Bool_3549);
            }
        }
    }
    U32 hoisted__U32_3551 = 0;
    self->count = hoisted__U32_3551;
}

void Vec__VariantDef_delete(Vec__VariantDef * self, Bool call_free) {
    Vec__VariantDef_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__VariantDef * Vec__VariantDef_clone(Vec__VariantDef * self) {
    U32 hoisted__U32_3809 = 0;
    Bool hoisted__Bool_3810 = ((Bool)(self->cap == hoisted__U32_3809));
    if (hoisted__Bool_3810) {
        U8 *hoisted__U8_3785 = malloc(sizeof(U8));
        *hoisted__U8_3785 = 0;
        U32 hoisted__U32_3786 = 0;
        I64 hoisted__I64_3787 = 0;
        Vec__VariantDef *hoisted__Vec__VariantDef_3788 = malloc(sizeof(Vec__VariantDef));
        hoisted__Vec__VariantDef_3788->data = hoisted__U8_3785;
        hoisted__Vec__VariantDef_3788->count = hoisted__U32_3786;
        hoisted__Vec__VariantDef_3788->cap = hoisted__I64_3787;
        return hoisted__Vec__VariantDef_3788;
    }
    U32 hoisted__U32_3811 = 72;
    U8 *new_data = malloc(((U32)(self->cap * hoisted__U32_3811)));
    {
        U32 _re_U32_3789 = self->count;
        (void)_re_U32_3789;
        U32 _rc_U32_3789 = 0;
        (void)_rc_U32_3789;
        Bool hoisted__Bool_3808 = ((Bool)(_rc_U32_3789 <= _re_U32_3789));
        if (hoisted__Bool_3808) {
            while (1) {
                Bool _wcond_Bool_3790 = ((Bool)(_rc_U32_3789 < _re_U32_3789));
                (void)_wcond_Bool_3790;
                if (_wcond_Bool_3790) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_3789);
                (++_rc_U32_3789);
                U32 hoisted__U32_3791 = 72;
                U32 hoisted__U32_3792 = ((U32)(i * hoisted__U32_3791));
                VariantDef *src = ((void *)((U8 *)(self->data) + (hoisted__U32_3792)));
                VariantDef *cloned = VariantDef_clone(src);
                U32 hoisted__U32_3793 = 72;
                U32 hoisted__U32_3794 = ((U32)(i * hoisted__U32_3793));
                void *hoisted__v_3795 = ((void *)((U8 *)(new_data) + (hoisted__U32_3794)));
                U32 hoisted__U32_3796 = 72;
                memcpy(hoisted__v_3795, cloned, hoisted__U32_3796);
                I32 hoisted__I32_3797 = 0;
                U32 hoisted__U32_3798 = 72;
                memset(cloned, hoisted__I32_3797, hoisted__U32_3798);
                VariantDef_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3799 = ((Bool)(_rc_U32_3789 > _re_U32_3789));
                (void)_wcond_Bool_3799;
                if (_wcond_Bool_3799) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_3789);
                (--_rc_U32_3789);
                U32 hoisted__U32_3800 = 72;
                U32 hoisted__U32_3801 = ((U32)(i * hoisted__U32_3800));
                VariantDef *src = ((void *)((U8 *)(self->data) + (hoisted__U32_3801)));
                VariantDef *cloned = VariantDef_clone(src);
                U32 hoisted__U32_3802 = 72;
                U32 hoisted__U32_3803 = ((U32)(i * hoisted__U32_3802));
                void *hoisted__v_3804 = ((void *)((U8 *)(new_data) + (hoisted__U32_3803)));
                U32 hoisted__U32_3805 = 72;
                memcpy(hoisted__v_3804, cloned, hoisted__U32_3805);
                I32 hoisted__I32_3806 = 0;
                U32 hoisted__U32_3807 = 72;
                memset(cloned, hoisted__I32_3806, hoisted__U32_3807);
                VariantDef_delete(cloned, 1);
            }
        }
    }
    Vec__VariantDef *hoisted__Vec__VariantDef_3812 = malloc(sizeof(Vec__VariantDef));
    hoisted__Vec__VariantDef_3812->data = new_data;
    hoisted__Vec__VariantDef_3812->count = self->count;
    hoisted__Vec__VariantDef_3812->cap = self->cap;
    return hoisted__Vec__VariantDef_3812;
    __builtin_unreachable();
}

USize Vec__VariantDef_size(void) {
    U32 hoisted__U32_3813 = 16;
    return hoisted__U32_3813;
    __builtin_unreachable();
}

Vec__Declaration * Vec__Declaration_new(void) {
    U8 *hoisted__U8_4103 = malloc(sizeof(U8));
    *hoisted__U8_4103 = 0;
    U32 hoisted__U32_4104 = 0;
    I64 hoisted__I64_4105 = 0;
    Vec__Declaration *hoisted__Vec__Declaration_4106 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_4106->data = hoisted__U8_4103;
    hoisted__Vec__Declaration_4106->count = hoisted__U32_4104;
    hoisted__Vec__Declaration_4106->cap = hoisted__I64_4105;
    return hoisted__Vec__Declaration_4106;
    __builtin_unreachable();
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_4117 = self->count;
        (void)_re_U32_4117;
        U32 _rc_U32_4117 = 0;
        (void)_rc_U32_4117;
        Bool hoisted__Bool_4128 = ((Bool)(_rc_U32_4117 <= _re_U32_4117));
        if (hoisted__Bool_4128) {
            while (1) {
                Bool _wcond_Bool_4118 = ((Bool)(_rc_U32_4117 < _re_U32_4117));
                (void)_wcond_Bool_4118;
                if (_wcond_Bool_4118) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4117);
                (++_rc_U32_4117);
                U32 hoisted__U32_4119 = 112;
                U32 hoisted__U32_4120 = ((U32)(i * hoisted__U32_4119));
                Declaration *hoisted__Declaration_4121 = ((void *)((U8 *)(self->data) + (hoisted__U32_4120)));
                Bool hoisted__Bool_4122 = 0;
                Declaration_delete(hoisted__Declaration_4121, hoisted__Bool_4122);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4123 = ((Bool)(_rc_U32_4117 > _re_U32_4117));
                (void)_wcond_Bool_4123;
                if (_wcond_Bool_4123) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4117);
                (--_rc_U32_4117);
                U32 hoisted__U32_4124 = 112;
                U32 hoisted__U32_4125 = ((U32)(i * hoisted__U32_4124));
                Declaration *hoisted__Declaration_4126 = ((void *)((U8 *)(self->data) + (hoisted__U32_4125)));
                Bool hoisted__Bool_4127 = 0;
                Declaration_delete(hoisted__Declaration_4126, hoisted__Bool_4127);
            }
        }
    }
    U32 hoisted__U32_4129 = 0;
    self->count = hoisted__U32_4129;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U32 hoisted__U32_4387 = 0;
    Bool hoisted__Bool_4388 = ((Bool)(self->cap == hoisted__U32_4387));
    if (hoisted__Bool_4388) {
        U8 *hoisted__U8_4363 = malloc(sizeof(U8));
        *hoisted__U8_4363 = 0;
        U32 hoisted__U32_4364 = 0;
        I64 hoisted__I64_4365 = 0;
        Vec__Declaration *hoisted__Vec__Declaration_4366 = malloc(sizeof(Vec__Declaration));
        hoisted__Vec__Declaration_4366->data = hoisted__U8_4363;
        hoisted__Vec__Declaration_4366->count = hoisted__U32_4364;
        hoisted__Vec__Declaration_4366->cap = hoisted__I64_4365;
        return hoisted__Vec__Declaration_4366;
    }
    U32 hoisted__U32_4389 = 112;
    U8 *new_data = malloc(((U32)(self->cap * hoisted__U32_4389)));
    {
        U32 _re_U32_4367 = self->count;
        (void)_re_U32_4367;
        U32 _rc_U32_4367 = 0;
        (void)_rc_U32_4367;
        Bool hoisted__Bool_4386 = ((Bool)(_rc_U32_4367 <= _re_U32_4367));
        if (hoisted__Bool_4386) {
            while (1) {
                Bool _wcond_Bool_4368 = ((Bool)(_rc_U32_4367 < _re_U32_4367));
                (void)_wcond_Bool_4368;
                if (_wcond_Bool_4368) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4367);
                (++_rc_U32_4367);
                U32 hoisted__U32_4369 = 112;
                U32 hoisted__U32_4370 = ((U32)(i * hoisted__U32_4369));
                Declaration *src = ((void *)((U8 *)(self->data) + (hoisted__U32_4370)));
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_4371 = 112;
                U32 hoisted__U32_4372 = ((U32)(i * hoisted__U32_4371));
                void *hoisted__v_4373 = ((void *)((U8 *)(new_data) + (hoisted__U32_4372)));
                U32 hoisted__U32_4374 = 112;
                memcpy(hoisted__v_4373, cloned, hoisted__U32_4374);
                I32 hoisted__I32_4375 = 0;
                U32 hoisted__U32_4376 = 112;
                memset(cloned, hoisted__I32_4375, hoisted__U32_4376);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4377 = ((Bool)(_rc_U32_4367 > _re_U32_4367));
                (void)_wcond_Bool_4377;
                if (_wcond_Bool_4377) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4367);
                (--_rc_U32_4367);
                U32 hoisted__U32_4378 = 112;
                U32 hoisted__U32_4379 = ((U32)(i * hoisted__U32_4378));
                Declaration *src = ((void *)((U8 *)(self->data) + (hoisted__U32_4379)));
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_4380 = 112;
                U32 hoisted__U32_4381 = ((U32)(i * hoisted__U32_4380));
                void *hoisted__v_4382 = ((void *)((U8 *)(new_data) + (hoisted__U32_4381)));
                U32 hoisted__U32_4383 = 112;
                memcpy(hoisted__v_4382, cloned, hoisted__U32_4383);
                I32 hoisted__I32_4384 = 0;
                U32 hoisted__U32_4385 = 112;
                memset(cloned, hoisted__I32_4384, hoisted__U32_4385);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_4390 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_4390->data = new_data;
    hoisted__Vec__Declaration_4390->count = self->count;
    hoisted__Vec__Declaration_4390->cap = self->cap;
    return hoisted__Vec__Declaration_4390;
    __builtin_unreachable();
}

USize Vec__Declaration_size(void) {
    U32 hoisted__U32_4391 = 16;
    return hoisted__U32_4391;
    __builtin_unreachable();
}

Vec__Expr * Vec__Expr_new(void) {
    U8 *hoisted__U8_4392 = malloc(sizeof(U8));
    *hoisted__U8_4392 = 0;
    U32 hoisted__U32_4393 = 0;
    I64 hoisted__I64_4394 = 0;
    Vec__Expr *hoisted__Vec__Expr_4395 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_4395->data = hoisted__U8_4392;
    hoisted__Vec__Expr_4395->count = hoisted__U32_4393;
    hoisted__Vec__Expr_4395->cap = hoisted__I64_4394;
    return hoisted__Vec__Expr_4395;
    __builtin_unreachable();
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_4406 = self->count;
        (void)_re_U32_4406;
        U32 _rc_U32_4406 = 0;
        (void)_rc_U32_4406;
        Bool hoisted__Bool_4417 = ((Bool)(_rc_U32_4406 <= _re_U32_4406));
        if (hoisted__Bool_4417) {
            while (1) {
                Bool _wcond_Bool_4407 = ((Bool)(_rc_U32_4406 < _re_U32_4406));
                (void)_wcond_Bool_4407;
                if (_wcond_Bool_4407) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4406);
                (++_rc_U32_4406);
                U32 hoisted__U32_4408 = 144;
                U32 hoisted__U32_4409 = ((U32)(i * hoisted__U32_4408));
                Expr *hoisted__Expr_4410 = ((void *)((U8 *)(self->data) + (hoisted__U32_4409)));
                Bool hoisted__Bool_4411 = 0;
                Expr_delete(hoisted__Expr_4410, hoisted__Bool_4411);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4412 = ((Bool)(_rc_U32_4406 > _re_U32_4406));
                (void)_wcond_Bool_4412;
                if (_wcond_Bool_4412) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4406);
                (--_rc_U32_4406);
                U32 hoisted__U32_4413 = 144;
                U32 hoisted__U32_4414 = ((U32)(i * hoisted__U32_4413));
                Expr *hoisted__Expr_4415 = ((void *)((U8 *)(self->data) + (hoisted__U32_4414)));
                Bool hoisted__Bool_4416 = 0;
                Expr_delete(hoisted__Expr_4415, hoisted__Bool_4416);
            }
        }
    }
    U32 hoisted__U32_4418 = 0;
    self->count = hoisted__U32_4418;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_4676 = 0;
    Bool hoisted__Bool_4677 = ((Bool)(self->cap == hoisted__U32_4676));
    if (hoisted__Bool_4677) {
        U8 *hoisted__U8_4652 = malloc(sizeof(U8));
        *hoisted__U8_4652 = 0;
        U32 hoisted__U32_4653 = 0;
        I64 hoisted__I64_4654 = 0;
        Vec__Expr *hoisted__Vec__Expr_4655 = malloc(sizeof(Vec__Expr));
        hoisted__Vec__Expr_4655->data = hoisted__U8_4652;
        hoisted__Vec__Expr_4655->count = hoisted__U32_4653;
        hoisted__Vec__Expr_4655->cap = hoisted__I64_4654;
        return hoisted__Vec__Expr_4655;
    }
    U32 hoisted__U32_4678 = 144;
    U8 *new_data = malloc(((U32)(self->cap * hoisted__U32_4678)));
    {
        U32 _re_U32_4656 = self->count;
        (void)_re_U32_4656;
        U32 _rc_U32_4656 = 0;
        (void)_rc_U32_4656;
        Bool hoisted__Bool_4675 = ((Bool)(_rc_U32_4656 <= _re_U32_4656));
        if (hoisted__Bool_4675) {
            while (1) {
                Bool _wcond_Bool_4657 = ((Bool)(_rc_U32_4656 < _re_U32_4656));
                (void)_wcond_Bool_4657;
                if (_wcond_Bool_4657) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4656);
                (++_rc_U32_4656);
                U32 hoisted__U32_4658 = 144;
                U32 hoisted__U32_4659 = ((U32)(i * hoisted__U32_4658));
                Expr *src = ((void *)((U8 *)(self->data) + (hoisted__U32_4659)));
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_4660 = 144;
                U32 hoisted__U32_4661 = ((U32)(i * hoisted__U32_4660));
                void *hoisted__v_4662 = ((void *)((U8 *)(new_data) + (hoisted__U32_4661)));
                U32 hoisted__U32_4663 = 144;
                memcpy(hoisted__v_4662, cloned, hoisted__U32_4663);
                I32 hoisted__I32_4664 = 0;
                U32 hoisted__U32_4665 = 144;
                memset(cloned, hoisted__I32_4664, hoisted__U32_4665);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4666 = ((Bool)(_rc_U32_4656 > _re_U32_4656));
                (void)_wcond_Bool_4666;
                if (_wcond_Bool_4666) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4656);
                (--_rc_U32_4656);
                U32 hoisted__U32_4667 = 144;
                U32 hoisted__U32_4668 = ((U32)(i * hoisted__U32_4667));
                Expr *src = ((void *)((U8 *)(self->data) + (hoisted__U32_4668)));
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_4669 = 144;
                U32 hoisted__U32_4670 = ((U32)(i * hoisted__U32_4669));
                void *hoisted__v_4671 = ((void *)((U8 *)(new_data) + (hoisted__U32_4670)));
                U32 hoisted__U32_4672 = 144;
                memcpy(hoisted__v_4671, cloned, hoisted__U32_4672);
                I32 hoisted__I32_4673 = 0;
                U32 hoisted__U32_4674 = 144;
                memset(cloned, hoisted__I32_4673, hoisted__U32_4674);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_4679 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_4679->data = new_data;
    hoisted__Vec__Expr_4679->count = self->count;
    hoisted__Vec__Expr_4679->cap = self->cap;
    return hoisted__Vec__Expr_4679;
    __builtin_unreachable();
}

USize Vec__Expr_size(void) {
    U32 hoisted__U32_4680 = 16;
    return hoisted__U32_4680;
    __builtin_unreachable();
}

Vec__USize * Vec__USize_new(void) {
    U8 *hoisted__U8_4681 = malloc(sizeof(U8));
    *hoisted__U8_4681 = 0;
    U32 hoisted__U32_4682 = 0;
    I64 hoisted__I64_4683 = 0;
    Vec__USize *hoisted__Vec__USize_4684 = malloc(sizeof(Vec__USize));
    hoisted__Vec__USize_4684->data = hoisted__U8_4681;
    hoisted__Vec__USize_4684->count = hoisted__U32_4682;
    hoisted__Vec__USize_4684->cap = hoisted__I64_4683;
    return hoisted__Vec__USize_4684;
    __builtin_unreachable();
}

void Vec__USize_clear(Vec__USize * self) {
    {
        U32 _re_U32_4695 = self->count;
        (void)_re_U32_4695;
        U32 _rc_U32_4695 = 0;
        (void)_rc_U32_4695;
        Bool hoisted__Bool_4706 = ((Bool)(_rc_U32_4695 <= _re_U32_4695));
        if (hoisted__Bool_4706) {
            while (1) {
                Bool _wcond_Bool_4696 = ((Bool)(_rc_U32_4695 < _re_U32_4695));
                (void)_wcond_Bool_4696;
                if (_wcond_Bool_4696) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4695);
                (++_rc_U32_4695);
                USize hoisted__U32_4697 = U32_size();
                U32 hoisted__U32_4698 = ((U32)(i * hoisted__U32_4697));
                U32 *hoisted__U32_4699 = ((void *)((U8 *)(self->data) + (hoisted__U32_4698)));
                Bool hoisted__Bool_4700 = 0;
                U32_delete(hoisted__U32_4699, hoisted__Bool_4700);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4701 = ((Bool)(_rc_U32_4695 > _re_U32_4695));
                (void)_wcond_Bool_4701;
                if (_wcond_Bool_4701) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4695);
                (--_rc_U32_4695);
                USize hoisted__U32_4702 = U32_size();
                U32 hoisted__U32_4703 = ((U32)(i * hoisted__U32_4702));
                U32 *hoisted__U32_4704 = ((void *)((U8 *)(self->data) + (hoisted__U32_4703)));
                Bool hoisted__Bool_4705 = 0;
                U32_delete(hoisted__U32_4704, hoisted__Bool_4705);
            }
        }
    }
    U32 hoisted__U32_4707 = 0;
    self->count = hoisted__U32_4707;
}

void Vec__USize_delete(Vec__USize * self, Bool call_free) {
    Vec__USize_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__USize * Vec__USize_clone(Vec__USize * self) {
    U32 hoisted__U32_4965 = 0;
    Bool hoisted__Bool_4966 = ((Bool)(self->cap == hoisted__U32_4965));
    if (hoisted__Bool_4966) {
        U8 *hoisted__U8_4941 = malloc(sizeof(U8));
        *hoisted__U8_4941 = 0;
        U32 hoisted__U32_4942 = 0;
        I64 hoisted__I64_4943 = 0;
        Vec__USize *hoisted__Vec__USize_4944 = malloc(sizeof(Vec__USize));
        hoisted__Vec__USize_4944->data = hoisted__U8_4941;
        hoisted__Vec__USize_4944->count = hoisted__U32_4942;
        hoisted__Vec__USize_4944->cap = hoisted__I64_4943;
        return hoisted__Vec__USize_4944;
    }
    USize hoisted__U32_4967 = U32_size();
    U8 *new_data = malloc(((U32)(self->cap * hoisted__U32_4967)));
    {
        U32 _re_U32_4945 = self->count;
        (void)_re_U32_4945;
        U32 _rc_U32_4945 = 0;
        (void)_rc_U32_4945;
        Bool hoisted__Bool_4964 = ((Bool)(_rc_U32_4945 <= _re_U32_4945));
        if (hoisted__Bool_4964) {
            while (1) {
                Bool _wcond_Bool_4946 = ((Bool)(_rc_U32_4945 < _re_U32_4945));
                (void)_wcond_Bool_4946;
                if (_wcond_Bool_4946) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4945);
                (++_rc_U32_4945);
                USize hoisted__U32_4947 = U32_size();
                U32 hoisted__U32_4948 = ((U32)(i * hoisted__U32_4947));
                U32 *src = ((void *)((U8 *)(self->data) + (hoisted__U32_4948)));
                U32 cloned = (DEREF(src));
                USize hoisted__U32_4949 = U32_size();
                U32 hoisted__U32_4950 = ((U32)(i * hoisted__U32_4949));
                void *hoisted__v_4951 = ((void *)((U8 *)(new_data) + (hoisted__U32_4950)));
                USize hoisted__U32_4952 = U32_size();
                memcpy(hoisted__v_4951, &cloned, hoisted__U32_4952);
                I32 hoisted__I32_4953 = 0;
                USize hoisted__U32_4954 = U32_size();
                memset(&cloned, hoisted__I32_4953, hoisted__U32_4954);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4955 = ((Bool)(_rc_U32_4945 > _re_U32_4945));
                (void)_wcond_Bool_4955;
                if (_wcond_Bool_4955) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4945);
                (--_rc_U32_4945);
                USize hoisted__U32_4956 = U32_size();
                U32 hoisted__U32_4957 = ((U32)(i * hoisted__U32_4956));
                U32 *src = ((void *)((U8 *)(self->data) + (hoisted__U32_4957)));
                U32 cloned = (DEREF(src));
                USize hoisted__U32_4958 = U32_size();
                U32 hoisted__U32_4959 = ((U32)(i * hoisted__U32_4958));
                void *hoisted__v_4960 = ((void *)((U8 *)(new_data) + (hoisted__U32_4959)));
                USize hoisted__U32_4961 = U32_size();
                memcpy(hoisted__v_4960, &cloned, hoisted__U32_4961);
                I32 hoisted__I32_4962 = 0;
                USize hoisted__U32_4963 = U32_size();
                memset(&cloned, hoisted__I32_4962, hoisted__U32_4963);
            }
        }
    }
    Vec__USize *hoisted__Vec__USize_4968 = malloc(sizeof(Vec__USize));
    hoisted__Vec__USize_4968->data = new_data;
    hoisted__Vec__USize_4968->count = self->count;
    hoisted__Vec__USize_4968->cap = self->cap;
    return hoisted__Vec__USize_4968;
    __builtin_unreachable();
}

USize Vec__USize_size(void) {
    U32 hoisted__U32_4969 = 16;
    return hoisted__U32_4969;
    __builtin_unreachable();
}

__attribute__((noreturn)) void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_5574 = 3;
    Array__Str *_va_Array_147 = Array__Str_new(hoisted__U32_5574);
    (void)_va_Array_147;
    I64 _va_Array_147_ek = 0;
    (void)_va_Array_147_ek;
    U32 hoisted__U32_5575 = 0;
    Str *hoisted__Str_5576 = Str_clone(loc);
    Array__Str_set(_va_Array_147, hoisted__U32_5575, hoisted__Str_5576, &_va_Array_147_ek);
    U32 hoisted__U32_5577 = 1;
    Array__Str_set(_va_Array_147, hoisted__U32_5577, &_til_str_lits[0], &_va_Array_147_ek);
    Array__Str *hoisted__Array__Str_5579 = Array__Str_clone(parts);
    U32 hoisted__U32_5580 = 2;
    Str *hoisted__Str_5581 = format(hoisted__Array__Str_5579);
    Array__Str_set(_va_Array_147, hoisted__U32_5580, hoisted__Str_5581, &_va_Array_147_ek);
    Array__Str_delete(parts, 1);
    println(_va_Array_147);
    I64 hoisted__I64_5582 = 1;
    exit(hoisted__I64_5582);
}

__attribute__((noreturn)) void UNREACHABLE(Str * loc) {
    U32 hoisted__U32_5589 = 1;
    Array__Str *_va_Array_149 = Array__Str_new(hoisted__U32_5589);
    (void)_va_Array_149;
    I64 _va_Array_149_ek = 0;
    (void)_va_Array_149_ek;
    U32 hoisted__U32_5590 = 0;
    Array__Str_set(_va_Array_149, hoisted__U32_5590, &_til_str_lits[1], &_va_Array_149_ek);
    panic(_va_Array_149, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_5595 = ((Bool)(!(cond)));
    if (hoisted__Bool_5595) {
        U32 hoisted__U32_5592 = 1;
        Array__Str *_va_Array_150 = Array__Str_new(hoisted__U32_5592);
        (void)_va_Array_150;
        I64 _va_Array_150_ek = 0;
        (void)_va_Array_150_ek;
        U32 hoisted__U32_5593 = 0;
        Array__Str_set(_va_Array_150, hoisted__U32_5593, &_til_str_lits[2], &_va_Array_150_ek);
        panic(_va_Array_150, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_5603 = parts;
        (void)_fc_Array__Str_5603;
        (void)_fc_Array__Str_5603;
        U32 _fi_USize_5603 = 0;
        (void)_fi_USize_5603;
        while (1) {
            USize hoisted__U32_5605 = (_fc_Array__Str_5603->cap);
            Bool _wcond_Bool_5604 = ((Bool)(_fi_USize_5603 < hoisted__U32_5605));
            (void)_wcond_Bool_5604;
            if (_wcond_Bool_5604) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_5603->data) + (((U32)(_fi_USize_5603 * 16))))));
            U32 hoisted__U32_5606 = 1;
            U32 hoisted__U32_5607 = ((U32)(_fi_USize_5603 + hoisted__U32_5606));
            _fi_USize_5603 = hoisted__U32_5607;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_5620 = (Range){.start = val->start, .end = val->end};
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_5620;
    return _r; }
    __builtin_unreachable();
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_5621 = 0;
    U64 hoisted__U64_5622 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_5621); });
    return hoisted__U64_5622;
    __builtin_unreachable();
}

USize Range_size(void) {
    U32 hoisted__U32_5646 = 16;
    return hoisted__U32_5646;
    __builtin_unreachable();
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_5660 = 3;
    assert_eq__I64(result, hoisted__I64_5660, &_til_str_lits[3]);
    Str_delete(&_til_str_lits[3], (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_5668 = 15;
    assert_eq__I64(result, hoisted__I64_5668, &_til_str_lits[4]);
    Str_delete(&_til_str_lits[4], (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_5676 = 26;
    assert_eq__I64(result, hoisted__I64_5676, &_til_str_lits[5]);
    Str_delete(&_til_str_lits[5], (Bool){0});
}

void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&result, &_til_str_lits[6], &_til_str_lits[7]);
    Str_delete(&_til_str_lits[6], (Bool){0});
    Str_delete(&_til_str_lits[7], (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&r, &_til_str_lits[6], &_til_str_lits[8]);
    Str_delete(&_til_str_lits[6], (Bool){0});
    Str_delete(&_til_str_lits[8], (Bool){0});
    Str_delete(&r, (Bool){0});
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&r2, &_til_str_lits[9], &_til_str_lits[10]);
    Str_delete(&_til_str_lits[9], (Bool){0});
    Str_delete(&_til_str_lits[10], (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&d, &_til_str_lits[11], &_til_str_lits[12]);
    Str_delete(&d, (Bool){0});
    Str_delete(&_til_str_lits[11], (Bool){0});
    Str_delete(&_til_str_lits[12], (Bool){0});
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&d2, &_til_str_lits[13], &_til_str_lits[14]);
    Str_delete(&d2, (Bool){0});
    Str_delete(&_til_str_lits[13], (Bool){0});
    Str_delete(&_til_str_lits[14], (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_5745 = 106;
    assert_eq__I64(d3, hoisted__I64_5745, &_til_str_lits[15]);
    Str_delete(&_til_str_lits[15], (Bool){0});
}

void test_lolalalo(void) {
    static Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&lola_rec, &lola_it, &_til_str_lits[18]);
    Str_delete(&_til_str_lits[18], (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    assert_eq__Str(&lalo_rec, &lalo_it, &_til_str_lits[19]);
    Str_delete(&_til_str_lits[19], (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_6238 = 8;
    assert_eq__I64(result, hoisted__I64_6238, &_til_str_lits[20]);
    Str_delete(&_til_str_lits[20], (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_6242 = 1;
    assert(hoisted__Bool_6242, &_til_str_lits[21]);
    Str_delete(&_til_str_lits[21], (Bool){0});
    Bool hoisted__Bool_6246 = 1;
    assert(hoisted__Bool_6246, &_til_str_lits[22]);
    Str_delete(&_til_str_lits[22], (Bool){0});
}

void test_fold_f32(void) {
    assert_eq__Str(&_til_str_lits[23], &_til_str_lits[23], &_til_str_lits[24]);
    Str_delete(&_til_str_lits[23], (Bool){0});
    Str_delete(&_til_str_lits[23], (Bool){0});
    Str_delete(&_til_str_lits[24], (Bool){0});
    assert_eq__Str(&_til_str_lits[25], &_til_str_lits[25], &_til_str_lits[26]);
    Str_delete(&_til_str_lits[25], (Bool){0});
    Str_delete(&_til_str_lits[25], (Bool){0});
    Str_delete(&_til_str_lits[26], (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_6264 = (CfVec2){.x = self->x, .y = self->y};
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_6264;
    return _r; }
    __builtin_unreachable();
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_6265 = 0;
    U64 hoisted__U64_6266 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_6265); });
    return hoisted__U64_6266;
    __builtin_unreachable();
}

USize CfVec2_size(void) {
    U32 hoisted__U32_6290 = 16;
    return hoisted__U32_6290;
    __builtin_unreachable();
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_6291 = 42;
    assert_eq__I64(v.x, hoisted__I64_6291, &_til_str_lits[27]);
    Str_delete(&_til_str_lits[27], (Bool){0});
    I64 hoisted__I64_6293 = 99;
    assert_eq__I64(v.y, hoisted__I64_6293, &_til_str_lits[28]);
    Str_delete(&_til_str_lits[28], (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_6297 = 10;
    assert_eq__I64(p.x, hoisted__I64_6297, &_til_str_lits[29]);
    Str_delete(&_til_str_lits[29], (Bool){0});
    I64 hoisted__I64_6299 = 20;
    assert_eq__I64(p.y, hoisted__I64_6299, &_til_str_lits[30]);
    Str_delete(&_til_str_lits[30], (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_6306 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_6306;
    return _r; }
    __builtin_unreachable();
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_6307 = 0;
    U64 hoisted__U64_6308 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_6307); });
    return hoisted__U64_6308;
    __builtin_unreachable();
}

USize CfRect_size(void) {
    U32 hoisted__U32_6332 = 32;
    return hoisted__U32_6332;
    __builtin_unreachable();
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_6333 = 5;
    assert_eq__I64(r.top_left.x, hoisted__I64_6333, &_til_str_lits[31]);
    Str_delete(&_til_str_lits[31], (Bool){0});
    I64 hoisted__I64_6335 = 10;
    assert_eq__I64(r.top_left.y, hoisted__I64_6335, &_til_str_lits[32]);
    Str_delete(&_til_str_lits[32], (Bool){0});
    I64 hoisted__I64_6337 = 100;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_6337, &_til_str_lits[33]);
    Str_delete(&_til_str_lits[33], (Bool){0});
    I64 hoisted__I64_6339 = 200;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_6339, &_til_str_lits[34]);
    Str_delete(&_til_str_lits[34], (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_6342 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_6342;
    return _r; }
    __builtin_unreachable();
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_6343 = 0;
    U64 hoisted__U64_6344 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_6343); });
    return hoisted__U64_6344;
    __builtin_unreachable();
}

USize CfVec3f_size(void) {
    U32 hoisted__U32_6377 = 12;
    return hoisted__U32_6377;
    __builtin_unreachable();
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_6381 = F32_to_str(v.x);
    assert_eq__Str(hoisted__Str_6381, &_til_str_lits[35], &_til_str_lits[36]);
    Str_delete(hoisted__Str_6381, 1);
    Str_delete(&_til_str_lits[35], (Bool){0});
    Str_delete(&_til_str_lits[36], (Bool){0});
    Str *hoisted__Str_6384 = F32_to_str(v.y);
    assert_eq__Str(hoisted__Str_6384, &_til_str_lits[37], &_til_str_lits[38]);
    Str_delete(hoisted__Str_6384, 1);
    Str_delete(&_til_str_lits[37], (Bool){0});
    Str_delete(&_til_str_lits[38], (Bool){0});
    Str *hoisted__Str_6387 = F32_to_str(v.z);
    assert_eq__Str(hoisted__Str_6387, &_til_str_lits[39], &_til_str_lits[40]);
    Str_delete(hoisted__Str_6387, 1);
    Str_delete(&_til_str_lits[39], (Bool){0});
    Str_delete(&_til_str_lits[40], (Bool){0});
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
    Bool hoisted__Bool_6390 = ((Bool)((((Color *)(self))->tag) == (((Color *)(other))->tag)));
    return hoisted__Bool_6390;
    __builtin_unreachable();
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_6398 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    if (hoisted__Bool_6398) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
        return _r; }
    }
    Bool hoisted__Bool_6399 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    if (hoisted__Bool_6399) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
        return _r; }
    }
    Bool hoisted__Bool_6400 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    if (hoisted__Bool_6400) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
        return _r; }
    }
    static Str hoisted__Str_6401 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    UNREACHABLE(&hoisted__Str_6401);
    Str_delete(&hoisted__Str_6401, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
    __builtin_unreachable();
}

USize Color_size(void) {
    U32 hoisted__U32_6402 = 1;
    return hoisted__U32_6402;
    __builtin_unreachable();
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_6403 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    assert(hoisted__Bool_6403, &_til_str_lits[41]);
    Str_delete(&_til_str_lits[41], (Bool){0});
    Bool hoisted__Bool_6405 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    Bool hoisted__Bool_6406 = ((Bool)(!(hoisted__Bool_6405)));
    assert(hoisted__Bool_6406, &_til_str_lits[42]);
    Str_delete(&_til_str_lits[42], (Bool){0});
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
    Bool hoisted__Bool_6425 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    if (hoisted__Bool_6425) {
        I64 *hoisted__I64_6421 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Bool hoisted__Bool_6422 = 0;
        I64_delete(hoisted__I64_6421, hoisted__Bool_6422);
    }
    Bool hoisted__Bool_6426 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Name}))->tag)));
    if (hoisted__Bool_6426) {
        Str *hoisted__Str_6423 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Bool hoisted__Bool_6424 = 0;
        Str_delete(hoisted__Str_6423, hoisted__Bool_6424);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_6451 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    if (hoisted__Bool_6451) {
        I64 *_clone_payload_Num_0 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_6448 = Token_Num(_clone_payload_Num_0);
        return hoisted__Token_6448;
    }
    Bool hoisted__Bool_6452 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Name}))->tag)));
    if (hoisted__Bool_6452) {
        Str *_clone_payload_Name_1 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_6449 = Str_clone(_clone_payload_Name_1);
        Token *hoisted__Token_6450 = Token_Name(hoisted__Str_6449);
        return hoisted__Token_6450;
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
    __builtin_unreachable();
}

USize Token_size(void) {
    U32 hoisted__U32_6453 = 24;
    return hoisted__U32_6453;
    __builtin_unreachable();
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_6455 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    assert(hoisted__Bool_6455, &_til_str_lits[43]);
    Str_delete(&_til_str_lits[43], (Bool){0});
    Bool hoisted__Bool_6457 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag));
    Bool hoisted__Bool_6458 = ((Bool)(!(hoisted__Bool_6457)));
    assert(hoisted__Bool_6458, &_til_str_lits[44]);
    Str_delete(&_til_str_lits[44], (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_6460 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    assert(hoisted__Bool_6460, &_til_str_lits[45]);
    Str_delete(&_til_str_lits[45], (Bool){0});
    Bool hoisted__Bool_6462 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    Bool hoisted__Bool_6463 = ((Bool)(!(hoisted__Bool_6462)));
    assert(hoisted__Bool_6463, &_til_str_lits[46]);
    Str_delete(&_til_str_lits[46], (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_6467 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    assert(hoisted__Bool_6467, &_til_str_lits[47]);
    Str_delete(&_til_str_lits[47], (Bool){0});
    Bool hoisted__Bool_6469 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag));
    Bool hoisted__Bool_6470 = ((Bool)(!(hoisted__Bool_6469)));
    assert(hoisted__Bool_6470, &_til_str_lits[48]);
    Str_delete(&_til_str_lits[48], (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_6538 = ((Bool)(a != b));
    if (hoisted__Bool_6538) {
        U32 hoisted__U32_6527 = 5;
        Array__Str *_va_Array_187 = Array__Str_new(hoisted__U32_6527);
        (void)_va_Array_187;
        I64 _va_Array_187_ek = 0;
        (void)_va_Array_187_ek;
        U32 hoisted__U32_6528 = 0;
        Array__Str_set(_va_Array_187, hoisted__U32_6528, &_til_str_lits[49], &_va_Array_187_ek);
        U32 hoisted__U32_6530 = 1;
        Str *hoisted__Str_6531 = I64_to_str(a);
        Array__Str_set(_va_Array_187, hoisted__U32_6530, hoisted__Str_6531, &_va_Array_187_ek);
        U32 hoisted__U32_6532 = 2;
        Array__Str_set(_va_Array_187, hoisted__U32_6532, &_til_str_lits[50], &_va_Array_187_ek);
        U32 hoisted__U32_6534 = 3;
        Str *hoisted__Str_6535 = I64_to_str(b);
        Array__Str_set(_va_Array_187, hoisted__U32_6534, hoisted__Str_6535, &_va_Array_187_ek);
        U32 hoisted__U32_6536 = 4;
        Array__Str_set(_va_Array_187, hoisted__U32_6536, &_til_str_lits[51], &_va_Array_187_ek);
        panic(_va_Array_187, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_6550 = Str_neq(a, b);
    if (hoisted__Bool_6550) {
        U32 hoisted__U32_6539 = 5;
        Array__Str *_va_Array_188 = Array__Str_new(hoisted__U32_6539);
        (void)_va_Array_188;
        I64 _va_Array_188_ek = 0;
        (void)_va_Array_188_ek;
        U32 hoisted__U32_6540 = 0;
        Array__Str_set(_va_Array_188, hoisted__U32_6540, &_til_str_lits[49], &_va_Array_188_ek);
        U32 hoisted__U32_6542 = 1;
        Str *hoisted__Str_6543 = Str_to_str(a);
        Array__Str_set(_va_Array_188, hoisted__U32_6542, hoisted__Str_6543, &_va_Array_188_ek);
        U32 hoisted__U32_6544 = 2;
        Array__Str_set(_va_Array_188, hoisted__U32_6544, &_til_str_lits[50], &_va_Array_188_ek);
        U32 hoisted__U32_6546 = 3;
        Str *hoisted__Str_6547 = Str_to_str(b);
        Array__Str_set(_va_Array_188, hoisted__U32_6546, hoisted__Str_6547, &_va_Array_188_ek);
        U32 hoisted__U32_6548 = 4;
        Array__Str_set(_va_Array_188, hoisted__U32_6548, &_til_str_lits[51], &_va_Array_188_ek);
        panic(_va_Array_188, loc);
    }
}

int main(void) {
    CAP_LIT = 4294967295;
    CAP_VIEW = 4294967294;
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
