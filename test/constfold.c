#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

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
typedef struct Map__I64_Str Map__I64_Str;
typedef struct Vec__Bool Vec__Bool;
typedef struct Vec__I64 Vec__I64;
typedef struct Vec__Declaration Vec__Declaration;
typedef struct Vec__Expr Vec__Expr;
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
    Str msg;
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
    U8 tag;
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
    USize count;
    USize cap;
} Vec__Bool;


typedef struct Vec__I64 {
    U8 *data;
    USize count;
    USize cap;
} Vec__I64;


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
} FunctionDef;


typedef struct StructDef {
    Vec__Declaration fields;
    Vec__Declaration ns_decls;
    Str c_tag;
    Bool is_interface;
    Bool interface_ns_marker;
    Str implements_name;
} StructDef;


typedef struct CaptureBlockData {
    Vec__Declaration captures;
    Str closure_name;
} CaptureBlockData;


typedef struct Map__I64_Str {
    Vec__I64 keys;
    Vec__Str values;
} Map__I64_Str;


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
    } data;
};

typedef struct Expr {
    NodeType node_type;
    Vec__Expr children;
    U32 line;
    U32 col;
} Expr;


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
OutOfBounds * OutOfBounds_clone(OutOfBounds * self);
void OutOfBounds_delete(OutOfBounds * self, Bool call_free);
U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher);
USize OutOfBounds_size(void);
Array__Str * Array__Str_new(USize cap);
USize Array__Str_len(Array__Str * self);
Str * Array__Str_unsafe_get(Array__Str * self, USize * i);
void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val);
void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
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
Str * U32_to_str(U32 val);
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
U64 StructDef_hash(StructDef * self, HashFn hasher);
USize StructDef_size(void);
EnumDef * EnumDef_clone(EnumDef * self);
void EnumDef_delete(EnumDef * self, Bool call_free);
U64 EnumDef_hash(EnumDef * self, HashFn hasher);
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
Map__I64_Str * Map__I64_Str_new(void);
void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free);
Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self);
U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher);
USize Map__I64_Str_size(void);
Vec__Bool * Vec__Bool_new(void);
void Vec__Bool_clear(Vec__Bool * self);
void Vec__Bool_delete(Vec__Bool * self, Bool call_free);
Vec__Bool * Vec__Bool_clone(Vec__Bool * self);
USize Vec__Bool_size(void);
Vec__I64 * Vec__I64_new(void);
void Vec__I64_clear(Vec__I64 * self);
void Vec__I64_delete(Vec__I64 * self, Bool call_free);
Vec__I64 * Vec__I64_clone(Vec__I64 * self);
USize Vec__I64_size(void);
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
void panic(Array__Str * parts, Str * loc);
void UNREACHABLE(Str * loc);
void assert(Bool cond, Str * loc);
void println(Array__Str * parts);
void swap_bytes(void * a, void * b, UPtr size);
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
OutOfBounds * OutOfBounds_clone(OutOfBounds * self);
void OutOfBounds_delete(OutOfBounds * self, Bool call_free);
U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher);
USize OutOfBounds_size(void);
Array__Str * Array__Str_new(USize cap);
USize Array__Str_len(Array__Str * self);
Str * Array__Str_unsafe_get(Array__Str * self, USize * i);
void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val);
void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
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
Str * U32_to_str(U32 val);
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
U64 StructDef_hash(StructDef * self, HashFn hasher);
USize StructDef_size(void);
EnumDef * EnumDef_clone(EnumDef * self);
void EnumDef_delete(EnumDef * self, Bool call_free);
U64 EnumDef_hash(EnumDef * self, HashFn hasher);
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
Map__I64_Str * Map__I64_Str_new(void);
void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free);
Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self);
U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher);
USize Map__I64_Str_size(void);
Vec__Bool * Vec__Bool_new(void);
void Vec__Bool_clear(Vec__Bool * self);
void Vec__Bool_delete(Vec__Bool * self, Bool call_free);
Vec__Bool * Vec__Bool_clone(Vec__Bool * self);
USize Vec__Bool_size(void);
Vec__I64 * Vec__I64_new(void);
void Vec__I64_clear(Vec__I64 * self);
void Vec__I64_delete(Vec__I64 * self, Bool call_free);
Vec__I64 * Vec__I64_clone(Vec__I64 * self);
USize Vec__I64_size(void);
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
void panic(Array__Str * parts, Str * loc);
void UNREACHABLE(Str * loc);
void assert(Bool cond, Str * loc);
void println(Array__Str * parts);
void swap_bytes(void * a, void * b, UPtr size);
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

static __attribute__((unused)) Str _til_str_lit_0 = (Str){.c_str = (void *)"c_str", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_1 = (Str){.c_str = (void *)"I8", .count = 2ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_2 = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_3 = (Str){.c_str = (void *)"USize", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_4 = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_5 = (Str){.c_str = (void *)"msg", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_6 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_7 = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_8 = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_9 = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_10 = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_11 = (Str){.c_str = (void *)"I16", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_12 = (Str){.c_str = (void *)"U16", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_13 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_14 = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_15 = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_16 = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_17 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_18 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_19 = (Str){.c_str = (void *)"Unknown", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_20 = (Str){.c_str = (void *)"None", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_21 = (Str){.c_str = (void *)"Struct", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_22 = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_23 = (Str){.c_str = (void *)"Enum", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_24 = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_25 = (Str){.c_str = (void *)"FuncDef", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_26 = (Str){.c_str = (void *)"FuncPtr", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_27 = (Str){.c_str = (void *)"Custom", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_28 = (Str){.c_str = (void *)"Primitive", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_29 = (Str){.c_str = (void *)"FuncPtrSig", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_30 = (Str){.c_str = (void *)"Body", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_31 = (Str){.c_str = (void *)"Func", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_32 = (Str){.c_str = (void *)"Proc", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_33 = (Str){.c_str = (void *)"Test", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_34 = (Str){.c_str = (void *)"Macro", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_35 = (Str){.c_str = (void *)"ExtFunc", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_36 = (Str){.c_str = (void *)"ExtProc", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_37 = (Str){.c_str = (void *)"LazyFunc", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_38 = (Str){.c_str = (void *)"LazyProc", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_39 = (Str){.c_str = (void *)"CoreFunc", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_40 = (Str){.c_str = (void *)"CoreProc", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_41 = (Str){.c_str = (void *)"CoreLazyFunc", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_42 = (Str){.c_str = (void *)"Own", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_43 = (Str){.c_str = (void *)"Ref", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_44 = (Str){.c_str = (void *)"Shallow", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_45 = (Str){.c_str = (void *)"Unset", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_46 = (Str){.c_str = (void *)"Stack", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_47 = (Str){.c_str = (void *)"HeapBox", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_48 = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_49 = (Str){.c_str = (void *)"doc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_50 = (Str){.c_str = (void *)"explicit_type", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_51 = (Str){.c_str = (void *)"is_mut", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_52 = (Str){.c_str = (void *)"redundant_mut", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_53 = (Str){.c_str = (void *)"is_priv", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_54 = (Str){.c_str = (void *)"used", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_55 = (Str){.c_str = (void *)"own_type", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_56 = (Str){.c_str = (void *)"OwnType", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_57 = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_58 = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_59 = (Str){.c_str = (void *)"default_value", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_60 = (Str){.c_str = (void *)"Expr", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_61 = (Str){.c_str = (void *)"orig_name", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_62 = (Str){.c_str = (void *)"gc_storage", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_63 = (Str){.c_str = (void *)"GcStorage", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_64 = (Str){.c_str = (void *)"func_type", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_65 = (Str){.c_str = (void *)"FuncType", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_66 = (Str){.c_str = (void *)"params", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_67 = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_68 = (Str){.c_str = (void *)"return_type", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_69 = (Str){.c_str = (void *)"throw_types", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_70 = (Str){.c_str = (void *)"Vec__Str", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_71 = (Str){.c_str = (void *)"variadic_index", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_72 = (Str){.c_str = (void *)"kwargs_index", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_73 = (Str){.c_str = (void *)"return_own_type", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_74 = (Str){.c_str = (void *)"return_shallow_explicit", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_75 = (Str){.c_str = (void *)"auto_generated", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_76 = (Str){.c_str = (void *)"is_enum_variant_ctor", .count = 20ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_77 = (Str){.c_str = (void *)"captures", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_78 = (Str){.c_str = (void *)"closure_name", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_79 = (Str){.c_str = (void *)"is_splat", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_80 = (Str){.c_str = (void *)"does_throw", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_81 = (Str){.c_str = (void *)"is_bang", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_82 = (Str){.c_str = (void *)"own_args", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_83 = (Str){.c_str = (void *)"swap_replace", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_84 = (Str){.c_str = (void *)"text", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_85 = (Str){.c_str = (void *)"fields", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_86 = (Str){.c_str = (void *)"ns_decls", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_87 = (Str){.c_str = (void *)"c_tag", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_88 = (Str){.c_str = (void *)"is_interface", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_89 = (Str){.c_str = (void *)"interface_ns_marker", .count = 19ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_90 = (Str){.c_str = (void *)"implements_name", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_91 = (Str){.c_str = (void *)"variants", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_92 = (Str){.c_str = (void *)"payload_types", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_93 = (Str){.c_str = (void *)"Map__I64_Str", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_94 = (Str){.c_str = (void *)"payload_consts", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_95 = (Str){.c_str = (void *)"Vec__Bool", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_96 = (Str){.c_str = (void *)"tag_type", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_97 = (Str){.c_str = (void *)"tag_values", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_98 = (Str){.c_str = (void *)"Vec__I64", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_99 = (Str){.c_str = (void *)"save_old_delete", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_100 = (Str){.c_str = (void *)"is_payload_alias", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_101 = (Str){.c_str = (void *)"name2", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_102 = (Str){.c_str = (void *)"is_mut2", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_103 = (Str){.c_str = (void *)"Num", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_104 = (Str){.c_str = (void *)"LiteralNumData", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_105 = (Str){.c_str = (void *)"Null", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_106 = (Str){.c_str = (void *)"MapLit", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_107 = (Str){.c_str = (void *)"SetLit", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_108 = (Str){.c_str = (void *)"result_temp", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_109 = (Str){.c_str = (void *)"Literal", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_110 = (Str){.c_str = (void *)"Ident", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_111 = (Str){.c_str = (void *)"IdentData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_112 = (Str){.c_str = (void *)"Decl", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_113 = (Str){.c_str = (void *)"Declaration", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_114 = (Str){.c_str = (void *)"Assign", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_115 = (Str){.c_str = (void *)"AssignData", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_116 = (Str){.c_str = (void *)"FCall", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_117 = (Str){.c_str = (void *)"FCallData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_118 = (Str){.c_str = (void *)"FunctionDef", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_119 = (Str){.c_str = (void *)"FieldAccess", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_120 = (Str){.c_str = (void *)"FieldAccessData", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_121 = (Str){.c_str = (void *)"FieldAssign", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_122 = (Str){.c_str = (void *)"FieldAssignData", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_123 = (Str){.c_str = (void *)"Return", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_124 = (Str){.c_str = (void *)"If", .count = 2ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_125 = (Str){.c_str = (void *)"While", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_126 = (Str){.c_str = (void *)"ForIn", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_127 = (Str){.c_str = (void *)"ForInData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_128 = (Str){.c_str = (void *)"NamedArg", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_129 = (Str){.c_str = (void *)"Break", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_130 = (Str){.c_str = (void *)"Continue", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_131 = (Str){.c_str = (void *)"Switch", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_132 = (Str){.c_str = (void *)"Match", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_133 = (Str){.c_str = (void *)"MatchData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_134 = (Str){.c_str = (void *)"Case", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_135 = (Str){.c_str = (void *)"NoDefaultArg", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_136 = (Str){.c_str = (void *)"Throw", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_137 = (Str){.c_str = (void *)"Catch", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_138 = (Str){.c_str = (void *)"RestPattern", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_139 = (Str){.c_str = (void *)"CaptureBlock", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_140 = (Str){.c_str = (void *)"CaptureBlockData", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_141 = (Str){.c_str = (void *)"Loc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_142 = (Str){.c_str = (void *)"BodyValue", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_143 = (Str){.c_str = (void *)"ListPattern", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_144 = (Str){.c_str = (void *)"node_type", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_145 = (Str){.c_str = (void *)"NodeType", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_146 = (Str){.c_str = (void *)"children", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_147 = (Str){.c_str = (void *)"Vec__Expr", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_148 = (Str){.c_str = (void *)"line", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_149 = (Str){.c_str = (void *)"col", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_150 = (Str){.c_str = (void *)"keys", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_151 = (Str){.c_str = (void *)"values", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_152 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_153 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_154 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_155 = (Str){.c_str = (void *)"./src/core/exit.til:27:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_156 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_157 = (Str){.c_str = (void *)"./src/core/exit.til:35:9", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_158 = (Str){.c_str = (void *)"start", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_159 = (Str){.c_str = (void *)"end", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_160 = (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_161 = (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_162 = (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_163 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_164 = (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_165 = (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_166 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_167 = (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_168 = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_169 = (Str){.c_str = (void *)"test/constfold.til:72:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_170 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_171 = (Str){.c_str = (void *)"test/constfold.til:74:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_172 = (Str){.c_str = (void *)"test/constfold.til:76:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_173 = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_174 = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_175 = (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_176 = (Str){.c_str = (void *)"test/constfold.til:130:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_177 = (Str){.c_str = (void *)"test/constfold.til:137:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_178 = (Str){.c_str = (void *)"test/constfold.til:142:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_179 = (Str){.c_str = (void *)"test/constfold.til:143:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_180 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_181 = (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_182 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_183 = (Str){.c_str = (void *)"test/constfold.til:156:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_184 = (Str){.c_str = (void *)"x", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_185 = (Str){.c_str = (void *)"y", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_186 = (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_187 = (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_188 = (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_189 = (Str){.c_str = (void *)"test/constfold.til:186:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_190 = (Str){.c_str = (void *)"top_left", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_191 = (Str){.c_str = (void *)"CfVec2", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_192 = (Str){.c_str = (void *)"bottom_right", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_193 = (Str){.c_str = (void *)"test/constfold.til:202:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_194 = (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_195 = (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_196 = (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_197 = (Str){.c_str = (void *)"z", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_198 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_199 = (Str){.c_str = (void *)"test/constfold.til:228:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_200 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_201 = (Str){.c_str = (void *)"test/constfold.til:229:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_202 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_203 = (Str){.c_str = (void *)"test/constfold.til:230:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_204 = (Str){.c_str = (void *)"Red", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_205 = (Str){.c_str = (void *)"Green", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_206 = (Str){.c_str = (void *)"Blue", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_207 = (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_208 = (Str){.c_str = (void *)"test/constfold.til:241:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_209 = (Str){.c_str = (void *)"Name", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_210 = (Str){.c_str = (void *)"Eof", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_211 = (Str){.c_str = (void *)"test/constfold.til:249:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_212 = (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_213 = (Str){.c_str = (void *)"test/constfold.til:259:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_214 = (Str){.c_str = (void *)"test/constfold.til:260:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_215 = (Str){.c_str = (void *)"test/constfold.til:271:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_216 = (Str){.c_str = (void *)"test/constfold.til:272:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_217 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_218 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_219 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_220 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_221 = (Str){.c_str = (void *)"Fn", .count = 2ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_222 = (Str){.c_str = (void *)"?", .count = 1ULL, .cap = TIL_CAP_LIT};

U32 CAP_LIT;
U32 CAP_VIEW;
U32 ELEM_POD;
U32 ELEM_BOXED;
U32 ELEM_FN;

Str * format(Array__Str * parts) {
    U32 total = 0;
    {
        Array__Str *_fc_Array__Str_99 = parts;
        (void)_fc_Array__Str_99;
        (void)_fc_Array__Str_99;
        U32 _fi_USize_99 = 0;
        (void)_fi_USize_99;
        while (1) {
            USize hoisted__U32_101 = (_fc_Array__Str_99->cap);
            (void)hoisted__U32_101;
            Bool _wcond_Bool_100 = ((Bool)(_fi_USize_99 < hoisted__U32_101));
            (void)_wcond_Bool_100;
            if (_wcond_Bool_100) {
            } else {
                break;
            }
            Str *s = (((void *)((U8 *)(_fc_Array__Str_99->data) + (((U64)(_fi_USize_99 * 16))))));
            U32 hoisted__U32_102 = 1;
            (void)hoisted__U32_102;
            U32 hoisted__U32_103 = ((U32)(_fi_USize_99 + hoisted__U32_102));
            (void)hoisted__U32_103;
            _fi_USize_99 = hoisted__U32_103;
            USize hoisted__U32_104 = (s->count);
            (void)hoisted__U32_104;
            U32 hoisted__U32_105 = ((U32)(total + hoisted__U32_104));
            (void)hoisted__U32_105;
            total = hoisted__U32_105;
        }
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_106 = parts;
        (void)_fc_Array__Str_106;
        (void)_fc_Array__Str_106;
        U32 _fi_USize_106 = 0;
        (void)_fi_USize_106;
        while (1) {
            USize hoisted__U32_108 = (_fc_Array__Str_106->cap);
            (void)hoisted__U32_108;
            Bool _wcond_Bool_107 = ((Bool)(_fi_USize_106 < hoisted__U32_108));
            (void)_wcond_Bool_107;
            if (_wcond_Bool_107) {
            } else {
                break;
            }
            Str *s = (((void *)((U8 *)(_fc_Array__Str_106->data) + (((U64)(_fi_USize_106 * 16))))));
            U32 hoisted__U32_109 = 1;
            (void)hoisted__U32_109;
            U32 hoisted__U32_110 = ((U32)(_fi_USize_106 + hoisted__U32_109));
            (void)hoisted__U32_110;
            _fi_USize_106 = hoisted__U32_110;
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
    Bool hoisted__Bool_126 = ((Bool)(b->count < a->count));
    (void)hoisted__Bool_126;
    if (hoisted__Bool_126) {
        min_len = b->count;
    }
    I32 c = memcmp(a->c_str, b->c_str, min_len);
    I32 hoisted__I32_127 = 0;
    (void)hoisted__I32_127;
    Bool hoisted__Bool_128 = ((Bool)(c < hoisted__I32_127));
    (void)hoisted__Bool_128;
    if (hoisted__Bool_128) {
        I64 hoisted__I64_124 = -1;
        (void)hoisted__I64_124;
        return hoisted__I64_124;
    }
    I32 hoisted__I32_129 = 0;
    (void)hoisted__I32_129;
    Bool hoisted__Bool_130 = ((Bool)(c > hoisted__I32_129));
    (void)hoisted__Bool_130;
    if (hoisted__Bool_130) {
        I64 hoisted__I64_125 = 1;
        (void)hoisted__I64_125;
        return hoisted__I64_125;
    }
    I64 hoisted__I64_131 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_131;
    return hoisted__I64_131;
    __builtin_unreachable();
}

Bool Str_eq(Str * a, Str * b) {
    Bool hoisted__Bool_134 = ((Bool)(a->count != b->count));
    (void)hoisted__Bool_134;
    if (hoisted__Bool_134) {
        Bool hoisted__Bool_132 = 0;
        (void)hoisted__Bool_132;
        return hoisted__Bool_132;
    }
    Bool hoisted__Bool_135 = ptr_eq(a->c_str, b->c_str);
    (void)hoisted__Bool_135;
    if (hoisted__Bool_135) {
        Bool hoisted__Bool_133 = 1;
        (void)hoisted__Bool_133;
        return hoisted__Bool_133;
    }
    I32 hoisted__I32_136 = memcmp(a->c_str, b->c_str, a->count);
    (void)hoisted__I32_136;
    I32 hoisted__I32_137 = 0;
    (void)hoisted__I32_137;
    Bool hoisted__Bool_138 = ((Bool)(hoisted__I32_136 == hoisted__I32_137));
    (void)hoisted__Bool_138;
    return hoisted__Bool_138;
    __builtin_unreachable();
}

Str * Str_with_capacity(USize n) {
    U32 hoisted__U32_140 = 0;
    (void)hoisted__U32_140;
    Bool hoisted__Bool_141 = ((Bool)(n == hoisted__U32_140));
    (void)hoisted__Bool_141;
    if (hoisted__Bool_141) {
        static Str hoisted__Str_139 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_139;
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_139; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_142 = 1;
    (void)hoisted__U32_142;
    U32 hoisted__U64_143 = ((U64)(n + hoisted__U32_142));
    (void)hoisted__U64_143;
    I8 *buf = malloc(hoisted__U64_143);
    I32 hoisted__I32_144 = 0;
    (void)hoisted__I32_144;
    U64 hoisted__U64_145 = 1ULL;
    (void)hoisted__U64_145;
    memset(buf, hoisted__I32_144, hoisted__U64_145);
    I64 hoisted__I64_146 = 0;
    (void)hoisted__I64_146;
    Str *hoisted__Str_147 = malloc(sizeof(Str));
    hoisted__Str_147->c_str = buf;
    hoisted__Str_147->count = hoisted__I64_146;
    hoisted__Str_147->cap = n;
    (void)hoisted__Str_147;
    return hoisted__Str_147;
    __builtin_unreachable();
}

void Str_push_str(Str * self, Str * s) {
    U32 hoisted__U32_160 = 0;
    (void)hoisted__U32_160;
    Bool hoisted__Bool_161 = ((Bool)(s->count == hoisted__U32_160));
    (void)hoisted__Bool_161;
    if (hoisted__Bool_161) {
        return;
    }
    Bool hoisted__Bool_162 = ((Bool)(self->cap >= CAP_VIEW));
    (void)hoisted__Bool_162;
    if (hoisted__Bool_162) {
        U32 hoisted__U32_150 = 1;
        (void)hoisted__U32_150;
        Array__Str *_va_Array_3 = Array__Str_new(hoisted__U32_150);
        (void)_va_Array_3;
        I64 _va_Array_3_ek = 0;
        (void)_va_Array_3_ek;
        OutOfBounds *_va_Array_3_eo = malloc(sizeof(OutOfBounds));
        _va_Array_3_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_3_eo;
        U32 hoisted__U32_151 = 0;
        (void)hoisted__U32_151;
        static Str hoisted__Str_152 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_152;
        static Str hoisted__Str_153 = (Str){.c_str = (void *)"./src/core/str.til:118:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_153;
        Array__Str_set(_va_Array_3, hoisted__U32_151, &hoisted__Str_152, &_va_Array_3_ek, _va_Array_3_eo, &hoisted__Str_153);
        OutOfBounds_delete(_va_Array_3_eo, 1);
        Str_delete(&hoisted__Str_153, (Bool){0});
        static Str hoisted__Str_154 = (Str){.c_str = (void *)"./src/core/str.til:118:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_154;
        panic(_va_Array_3, &hoisted__Str_154);
        Str_delete(&hoisted__Str_154, (Bool){0});
    }
    U32 new_len = ((U32)(self->count + s->count));
    Bool hoisted__Bool_163 = ((Bool)(new_len > self->cap));
    (void)hoisted__Bool_163;
    if (hoisted__Bool_163) {
        U32 hoisted__U32_155 = 1;
        (void)hoisted__U32_155;
        Array__Str *_va_Array_4 = Array__Str_new(hoisted__U32_155);
        (void)_va_Array_4;
        I64 _va_Array_4_ek = 0;
        (void)_va_Array_4_ek;
        OutOfBounds *_va_Array_4_eo = malloc(sizeof(OutOfBounds));
        _va_Array_4_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_4_eo;
        U32 hoisted__U32_156 = 0;
        (void)hoisted__U32_156;
        static Str hoisted__Str_157 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_157;
        static Str hoisted__Str_158 = (Str){.c_str = (void *)"./src/core/str.til:122:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_158;
        Array__Str_set(_va_Array_4, hoisted__U32_156, &hoisted__Str_157, &_va_Array_4_ek, _va_Array_4_eo, &hoisted__Str_158);
        OutOfBounds_delete(_va_Array_4_eo, 1);
        Str_delete(&hoisted__Str_158, (Bool){0});
        static Str hoisted__Str_159 = (Str){.c_str = (void *)"./src/core/str.til:122:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_159;
        panic(_va_Array_4, &hoisted__Str_159);
        Str_delete(&hoisted__Str_159, (Bool){0});
    }
    void *hoisted__v_164 = ((void *)((U8 *)(self->c_str) + (self->count)));
    (void)hoisted__v_164;
    (void)hoisted__v_164;
    memcpy(hoisted__v_164, s->c_str, s->count);
    self->count = (new_len);
    void *hoisted__v_165 = ((void *)((U8 *)(self->c_str) + (new_len)));
    (void)hoisted__v_165;
    (void)hoisted__v_165;
    I32 hoisted__I32_166 = 0;
    (void)hoisted__I32_166;
    U64 hoisted__U64_167 = 1ULL;
    (void)hoisted__U64_167;
    memset(hoisted__v_165, hoisted__I32_166, hoisted__U64_167);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_169 = 0;
    (void)hoisted__U32_169;
    Bool hoisted__Bool_170 = ((Bool)(val->count == hoisted__U32_169));
    (void)hoisted__Bool_170;
    if (hoisted__Bool_170) {
        static Str hoisted__Str_168 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_168;
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_168; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_171 = 1;
    (void)hoisted__U32_171;
    U32 hoisted__U64_172 = ((U64)(val->count + hoisted__U32_171));
    (void)hoisted__U64_172;
    I8 *new_data = malloc(hoisted__U64_172);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_173 = ((void *)((U8 *)(new_data) + (val->count)));
    (void)hoisted__v_173;
    (void)hoisted__v_173;
    I32 hoisted__I32_174 = 0;
    (void)hoisted__I32_174;
    U64 hoisted__U64_175 = 1ULL;
    (void)hoisted__U64_175;
    memset(hoisted__v_173, hoisted__I32_174, hoisted__U64_175);
    Str *hoisted__Str_176 = malloc(sizeof(Str));
    hoisted__Str_176->c_str = new_data;
    hoisted__Str_176->count = val->count;
    hoisted__Str_176->cap = val->count;
    (void)hoisted__Str_176;
    return hoisted__Str_176;
    __builtin_unreachable();
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_177 = Str_clone(self);
    (void)hoisted__Str_177;
    return hoisted__Str_177;
    __builtin_unreachable();
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_178 = ((Bool)(self->cap < CAP_VIEW));
    (void)hoisted__Bool_178;
    if (hoisted__Bool_178) {
        free(self->c_str);
    }
    Bool hoisted__Bool_179 = ((Bool)(self->cap != CAP_LIT));
    (void)hoisted__Bool_179;
    Bool hoisted__Bool_180 = ((Bool)((call_free) && (hoisted__Bool_179)));
    (void)hoisted__Bool_180;
    if (hoisted__Bool_180) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_375 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, self->c_str, self->count); });
    (void)hoisted__U64_375;
    return hoisted__U64_375;
    __builtin_unreachable();
}

USize Str_size(void) {
    U32 hoisted__U32_562 = 16;
    (void)hoisted__U32_562;
    return hoisted__U32_562;
    __builtin_unreachable();
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_571 = Str_eq(a, b);
    (void)hoisted__Bool_571;
    Bool hoisted__Bool_572 = ((Bool)(!(hoisted__Bool_571)));
    (void)hoisted__Bool_572;
    return hoisted__Bool_572;
    __builtin_unreachable();
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_663 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_663->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_663;
    return hoisted__OutOfBounds_663;
    __builtin_unreachable();
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_664 = 0;
    (void)hoisted__Bool_664;
    Str_delete(&self->msg, hoisted__Bool_664);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_665 = 0;
    (void)hoisted__U32_665;
    U64 hoisted__U64_666 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_665); });
    (void)hoisted__U64_666;
    return hoisted__U64_666;
    __builtin_unreachable();
}

USize OutOfBounds_size(void) {
    U32 hoisted__U32_685 = 16;
    (void)hoisted__U32_685;
    return hoisted__U32_685;
    __builtin_unreachable();
}

Array__Str * Array__Str_new(USize cap) {
    U64 hoisted__U64_709 = 16ULL;
    (void)hoisted__U64_709;
    void * hoisted__v_710 = calloc(cap, hoisted__U64_709);
    (void)hoisted__v_710;
    Array__Str *hoisted__Array__Str_711 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_711->data = hoisted__v_710;
    hoisted__Array__Str_711->cap = cap;
    (void)hoisted__Array__Str_711;
    return hoisted__Array__Str_711;
    __builtin_unreachable();
}

USize Array__Str_len(Array__Str * self) {
    return self->cap;
    __builtin_unreachable();
}

Str * Array__Str_unsafe_get(Array__Str * self, USize * i) {
    U32 hoisted__U32_712 = 16;
    (void)hoisted__U32_712;
    U32 hoisted__U64_713 = ((U64)(DEREF(i) * hoisted__U32_712));
    (void)hoisted__U64_713;
    void *hoisted__v_714 = ((void *)((U8 *)(self->data) + (hoisted__U64_713)));
    (void)hoisted__v_714;
    (void)hoisted__v_714;
    return hoisted__v_714;
    __builtin_unreachable();
}

void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val) {
    Str *hoisted__Str_741 = (((void *)((U8 *)(self->data) + (((U64)(i * 16))))));
    (void)hoisted__Str_741;
    (void)hoisted__Str_741;
    Bool hoisted__Bool_742 = 0;
    (void)hoisted__Bool_742;
    Str_delete(hoisted__Str_741, hoisted__Bool_742);
    Str *hoisted__Str_743 = (((void *)((U8 *)(self->data) + (((U64)(i * 16))))));
    (void)hoisted__Str_743;
    (void)hoisted__Str_743;
    U64 hoisted__U64_744 = 16ULL;
    (void)hoisted__U64_744;
    memcpy(hoisted__Str_743, val, hoisted__U64_744);
    I32 hoisted__I32_745 = 0;
    (void)hoisted__I32_745;
    U64 hoisted__U64_746 = 16ULL;
    (void)hoisted__U64_746;
    if ((val)->cap != TIL_CAP_LIT) { memset(val, hoisted__I32_745, hoisted__U64_746); };
    Str_delete(val, 1);
}

void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc) {
    Bool hoisted__Bool_769 = ((Bool)(i >= self->cap));
    (void)hoisted__Bool_769;
    if (hoisted__Bool_769) {
        U32 hoisted__U32_747 = 6;
        (void)hoisted__U32_747;
        Array__Str *_va_Array_16 = Array__Str_new(hoisted__U32_747);
        (void)_va_Array_16;
        I64 _va_Array_16_ek = 0;
        (void)_va_Array_16_ek;
        OutOfBounds *_va_Array_16_eo = malloc(sizeof(OutOfBounds));
        _va_Array_16_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_16_eo;
        U32 hoisted__U32_748 = 0;
        (void)hoisted__U32_748;
        Str *hoisted__Str_749 = Str_clone(loc);
        (void)hoisted__Str_749;
        static Str hoisted__Str_750 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_750;
        Array__Str_set(_va_Array_16, hoisted__U32_748, hoisted__Str_749, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_750);
        Str_delete(&hoisted__Str_750, (Bool){0});
        U32 hoisted__U32_751 = 1;
        (void)hoisted__U32_751;
        static Str hoisted__Str_752 = (Str){.c_str = (void *)":Array.set: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_752;
        static Str hoisted__Str_753 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_753;
        Array__Str_set(_va_Array_16, hoisted__U32_751, &hoisted__Str_752, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_753);
        Str_delete(&hoisted__Str_753, (Bool){0});
        U32 hoisted__U32_754 = 2;
        (void)hoisted__U32_754;
        Str *hoisted__Str_755 = U32_to_str(i);
        (void)hoisted__Str_755;
        static Str hoisted__Str_756 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_756;
        Array__Str_set(_va_Array_16, hoisted__U32_754, hoisted__Str_755, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_756);
        Str_delete(&hoisted__Str_756, (Bool){0});
        U32 hoisted__U32_757 = 3;
        (void)hoisted__U32_757;
        static Str hoisted__Str_758 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_758;
        static Str hoisted__Str_759 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_759;
        Array__Str_set(_va_Array_16, hoisted__U32_757, &hoisted__Str_758, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_759);
        Str_delete(&hoisted__Str_759, (Bool){0});
        U32 hoisted__U32_760 = 4;
        (void)hoisted__U32_760;
        Str *hoisted__Str_761 = U32_to_str(self->cap);
        (void)hoisted__Str_761;
        static Str hoisted__Str_762 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_762;
        Array__Str_set(_va_Array_16, hoisted__U32_760, hoisted__Str_761, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_762);
        Str_delete(&hoisted__Str_762, (Bool){0});
        U32 hoisted__U32_763 = 5;
        (void)hoisted__U32_763;
        static Str hoisted__Str_764 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_764;
        static Str hoisted__Str_765 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_765;
        Array__Str_set(_va_Array_16, hoisted__U32_763, &hoisted__Str_764, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_765);
        OutOfBounds_delete(_va_Array_16_eo, 1);
        Str_delete(&hoisted__Str_765, (Bool){0});
        OutOfBounds *hoisted__OutOfBounds_766 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_16); hoisted__OutOfBounds_766->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_766;
        U32 hoisted__U32_767 = 16;
        (void)hoisted__U32_767;
        swap_bytes(_err_OutOfBounds, hoisted__OutOfBounds_766, hoisted__U32_767);
        OutOfBounds_delete(hoisted__OutOfBounds_766, 1);
        I64 hoisted__I64_768 = 1;
        (void)hoisted__I64_768;
        *_err_kind = hoisted__I64_768;
    }
    I64 hoisted__I64_770 = 0;
    (void)hoisted__I64_770;
    Bool hoisted__Bool_771 = ((Bool)(DEREF(_err_kind) == hoisted__I64_770));
    (void)hoisted__Bool_771;
    if (hoisted__Bool_771) {
        Array__Str_unsafe_set(self, i, val);
    } else {
        Str_delete(val, 1);
    }
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_772 = self->cap;
        (void)_re_U32_772;
        U32 _rc_U32_772 = 0;
        (void)_rc_U32_772;
        Bool hoisted__Bool_783 = ((Bool)(_rc_U32_772 <= _re_U32_772));
        (void)hoisted__Bool_783;
        if (hoisted__Bool_783) {
            while (1) {
                Bool _wcond_Bool_773 = ((Bool)(_rc_U32_772 < _re_U32_772));
                (void)_wcond_Bool_773;
                if (_wcond_Bool_773) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_772);
                (++_rc_U32_772);
                U32 hoisted__U32_774 = 16;
                (void)hoisted__U32_774;
                U32 hoisted__U64_775 = ((U64)(i * hoisted__U32_774));
                (void)hoisted__U64_775;
                Str *hoisted__Str_776 = ((void *)((U8 *)(self->data) + (hoisted__U64_775)));
                (void)hoisted__Str_776;
                (void)hoisted__Str_776;
                Bool hoisted__Bool_777 = 0;
                (void)hoisted__Bool_777;
                Str_delete(hoisted__Str_776, hoisted__Bool_777);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_778 = ((Bool)(_rc_U32_772 > _re_U32_772));
                (void)_wcond_Bool_778;
                if (_wcond_Bool_778) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_772);
                (--_rc_U32_772);
                U32 hoisted__U32_779 = 16;
                (void)hoisted__U32_779;
                U32 hoisted__U64_780 = ((U64)(i * hoisted__U32_779));
                (void)hoisted__U64_780;
                Str *hoisted__Str_781 = ((void *)((U8 *)(self->data) + (hoisted__U64_780)));
                (void)hoisted__Str_781;
                (void)hoisted__Str_781;
                Bool hoisted__Bool_782 = 0;
                (void)hoisted__Bool_782;
                Str_delete(hoisted__Str_781, hoisted__Bool_782);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_804 = 16;
    (void)hoisted__U32_804;
    U32 hoisted__U64_805 = ((U64)(self->cap * hoisted__U32_804));
    (void)hoisted__U64_805;
    U8 *new_data = malloc(hoisted__U64_805);
    {
        U32 _re_U32_784 = self->cap;
        (void)_re_U32_784;
        U32 _rc_U32_784 = 0;
        (void)_rc_U32_784;
        Bool hoisted__Bool_803 = ((Bool)(_rc_U32_784 <= _re_U32_784));
        (void)hoisted__Bool_803;
        if (hoisted__Bool_803) {
            while (1) {
                Bool _wcond_Bool_785 = ((Bool)(_rc_U32_784 < _re_U32_784));
                (void)_wcond_Bool_785;
                if (_wcond_Bool_785) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_784);
                (++_rc_U32_784);
                U32 hoisted__U32_786 = 16;
                (void)hoisted__U32_786;
                U32 hoisted__U64_787 = ((U64)(i * hoisted__U32_786));
                (void)hoisted__U64_787;
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U64_787)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_788 = 16;
                (void)hoisted__U32_788;
                U32 hoisted__U64_789 = ((U64)(i * hoisted__U32_788));
                (void)hoisted__U64_789;
                void *hoisted__v_790 = ((void *)((U8 *)(new_data) + (hoisted__U64_789)));
                (void)hoisted__v_790;
                (void)hoisted__v_790;
                U64 hoisted__U64_791 = 16ULL;
                (void)hoisted__U64_791;
                memcpy(hoisted__v_790, cloned, hoisted__U64_791);
                I32 hoisted__I32_792 = 0;
                (void)hoisted__I32_792;
                U64 hoisted__U64_793 = 16ULL;
                (void)hoisted__U64_793;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_792, hoisted__U64_793); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_794 = ((Bool)(_rc_U32_784 > _re_U32_784));
                (void)_wcond_Bool_794;
                if (_wcond_Bool_794) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_784);
                (--_rc_U32_784);
                U32 hoisted__U32_795 = 16;
                (void)hoisted__U32_795;
                U32 hoisted__U64_796 = ((U64)(i * hoisted__U32_795));
                (void)hoisted__U64_796;
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U64_796)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_797 = 16;
                (void)hoisted__U32_797;
                U32 hoisted__U64_798 = ((U64)(i * hoisted__U32_797));
                (void)hoisted__U64_798;
                void *hoisted__v_799 = ((void *)((U8 *)(new_data) + (hoisted__U64_798)));
                (void)hoisted__v_799;
                (void)hoisted__v_799;
                U64 hoisted__U64_800 = 16ULL;
                (void)hoisted__U64_800;
                memcpy(hoisted__v_799, cloned, hoisted__U64_800);
                I32 hoisted__I32_801 = 0;
                (void)hoisted__I32_801;
                U64 hoisted__U64_802 = 16ULL;
                (void)hoisted__U64_802;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_801, hoisted__U64_802); };
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_806 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_806->data = new_data;
    hoisted__Array__Str_806->cap = self->cap;
    (void)hoisted__Array__Str_806;
    return hoisted__Array__Str_806;
    __builtin_unreachable();
}

USize Array__Str_size(void) {
    U32 hoisted__U32_807 = 16;
    (void)hoisted__U32_807;
    return hoisted__U32_807;
    __builtin_unreachable();
}

Vec__Str * Vec__Str_new(void) {
    U64 hoisted__U64_808 = 16ULL;
    (void)hoisted__U64_808;
    void * hoisted__v_809 = malloc(hoisted__U64_808);
    (void)hoisted__v_809;
    U32 hoisted__U32_810 = 0;
    (void)hoisted__U32_810;
    I64 hoisted__I64_811 = 1;
    (void)hoisted__I64_811;
    Vec__Str *hoisted__Vec__Str_812 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_812->data = hoisted__v_809;
    hoisted__Vec__Str_812->count = hoisted__U32_810;
    hoisted__Vec__Str_812->cap = hoisted__I64_811;
    (void)hoisted__Vec__Str_812;
    return hoisted__Vec__Str_812;
    __builtin_unreachable();
}

void Vec__Str_clear(Vec__Str * self) {
    {
        U32 _re_U32_821 = self->count;
        (void)_re_U32_821;
        U32 _rc_U32_821 = 0;
        (void)_rc_U32_821;
        Bool hoisted__Bool_832 = ((Bool)(_rc_U32_821 <= _re_U32_821));
        (void)hoisted__Bool_832;
        if (hoisted__Bool_832) {
            while (1) {
                Bool _wcond_Bool_822 = ((Bool)(_rc_U32_821 < _re_U32_821));
                (void)_wcond_Bool_822;
                if (_wcond_Bool_822) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_821);
                (++_rc_U32_821);
                U32 hoisted__U32_823 = 16;
                (void)hoisted__U32_823;
                U32 hoisted__U64_824 = ((U64)(i * hoisted__U32_823));
                (void)hoisted__U64_824;
                Str *hoisted__Str_825 = ((void *)((U8 *)(self->data) + (hoisted__U64_824)));
                (void)hoisted__Str_825;
                (void)hoisted__Str_825;
                Bool hoisted__Bool_826 = 0;
                (void)hoisted__Bool_826;
                Str_delete(hoisted__Str_825, hoisted__Bool_826);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_827 = ((Bool)(_rc_U32_821 > _re_U32_821));
                (void)_wcond_Bool_827;
                if (_wcond_Bool_827) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_821);
                (--_rc_U32_821);
                U32 hoisted__U32_828 = 16;
                (void)hoisted__U32_828;
                U32 hoisted__U64_829 = ((U64)(i * hoisted__U32_828));
                (void)hoisted__U64_829;
                Str *hoisted__Str_830 = ((void *)((U8 *)(self->data) + (hoisted__U64_829)));
                (void)hoisted__Str_830;
                (void)hoisted__Str_830;
                Bool hoisted__Bool_831 = 0;
                (void)hoisted__Bool_831;
                Str_delete(hoisted__Str_830, hoisted__Bool_831);
            }
        }
    }
    U32 hoisted__U32_833 = 0;
    (void)hoisted__U32_833;
    self->count = hoisted__U32_833;
}

void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Str * Vec__Str_clone(Vec__Str * self) {
    U32 hoisted__U32_1064 = 16;
    (void)hoisted__U32_1064;
    U32 hoisted__U64_1065 = ((U64)(self->cap * hoisted__U32_1064));
    (void)hoisted__U64_1065;
    U8 *new_data = malloc(hoisted__U64_1065);
    {
        U32 _re_U32_1044 = self->count;
        (void)_re_U32_1044;
        U32 _rc_U32_1044 = 0;
        (void)_rc_U32_1044;
        Bool hoisted__Bool_1063 = ((Bool)(_rc_U32_1044 <= _re_U32_1044));
        (void)hoisted__Bool_1063;
        if (hoisted__Bool_1063) {
            while (1) {
                Bool _wcond_Bool_1045 = ((Bool)(_rc_U32_1044 < _re_U32_1044));
                (void)_wcond_Bool_1045;
                if (_wcond_Bool_1045) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_1044);
                (++_rc_U32_1044);
                U32 hoisted__U32_1046 = 16;
                (void)hoisted__U32_1046;
                U32 hoisted__U64_1047 = ((U64)(i * hoisted__U32_1046));
                (void)hoisted__U64_1047;
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U64_1047)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1048 = 16;
                (void)hoisted__U32_1048;
                U32 hoisted__U64_1049 = ((U64)(i * hoisted__U32_1048));
                (void)hoisted__U64_1049;
                void *hoisted__v_1050 = ((void *)((U8 *)(new_data) + (hoisted__U64_1049)));
                (void)hoisted__v_1050;
                (void)hoisted__v_1050;
                U64 hoisted__U64_1051 = 16ULL;
                (void)hoisted__U64_1051;
                memcpy(hoisted__v_1050, cloned, hoisted__U64_1051);
                I32 hoisted__I32_1052 = 0;
                (void)hoisted__I32_1052;
                U64 hoisted__U64_1053 = 16ULL;
                (void)hoisted__U64_1053;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1052, hoisted__U64_1053); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1054 = ((Bool)(_rc_U32_1044 > _re_U32_1044));
                (void)_wcond_Bool_1054;
                if (_wcond_Bool_1054) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_1044);
                (--_rc_U32_1044);
                U32 hoisted__U32_1055 = 16;
                (void)hoisted__U32_1055;
                U32 hoisted__U64_1056 = ((U64)(i * hoisted__U32_1055));
                (void)hoisted__U64_1056;
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U64_1056)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1057 = 16;
                (void)hoisted__U32_1057;
                U32 hoisted__U64_1058 = ((U64)(i * hoisted__U32_1057));
                (void)hoisted__U64_1058;
                void *hoisted__v_1059 = ((void *)((U8 *)(new_data) + (hoisted__U64_1058)));
                (void)hoisted__v_1059;
                (void)hoisted__v_1059;
                U64 hoisted__U64_1060 = 16ULL;
                (void)hoisted__U64_1060;
                memcpy(hoisted__v_1059, cloned, hoisted__U64_1060);
                I32 hoisted__I32_1061 = 0;
                (void)hoisted__I32_1061;
                U64 hoisted__U64_1062 = 16ULL;
                (void)hoisted__U64_1062;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1061, hoisted__U64_1062); };
                Str_delete(cloned, 1);
            }
        }
    }
    Vec__Str *hoisted__Vec__Str_1066 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1066->data = new_data;
    hoisted__Vec__Str_1066->count = self->count;
    hoisted__Vec__Str_1066->cap = self->cap;
    (void)hoisted__Vec__Str_1066;
    return hoisted__Vec__Str_1066;
    __builtin_unreachable();
}

USize Vec__Str_size(void) {
    U32 hoisted__U32_1067 = 16;
    (void)hoisted__U32_1067;
    return hoisted__U32_1067;
    __builtin_unreachable();
}

USize Dynamic_size(void) {
    U32 hoisted__U32_1070 = 8;
    (void)hoisted__U32_1070;
    return hoisted__U32_1070;
    __builtin_unreachable();
}

void * Dynamic_clone(void * self) {
    U64 hoisted__U64_1071 = 8ULL;
    (void)hoisted__U64_1071;
    void * out = malloc(hoisted__U64_1071);
    U64 hoisted__U64_1072 = 8ULL;
    (void)hoisted__U64_1072;
    memcpy(out, self, hoisted__U64_1072);
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
    U32 hoisted__U32_1160 = 1;
    (void)hoisted__U32_1160;
    return hoisted__U32_1160;
    __builtin_unreachable();
}

U64 U8_hash(U8 self, HashFn hasher) {
    U32 hoisted__U32_1245 = 1;
    (void)hoisted__U32_1245;
    U64 hoisted__U64_1246 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1245); });
    (void)hoisted__U64_1246;
    return hoisted__U64_1246;
    __builtin_unreachable();
}

Str * U32_to_str(U32 val) {
    I64 hoisted__I64_1342 = U32_to_i64(val);
    (void)hoisted__I64_1342;
    Str *hoisted__Str_1343 = I64_to_str(hoisted__I64_1342);
    (void)hoisted__Str_1343;
    return hoisted__Str_1343;
    __builtin_unreachable();
}

void U32_delete(U32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize U32_size(void) {
    U32 hoisted__U32_1350 = 4;
    (void)hoisted__U32_1350;
    return hoisted__U32_1350;
    __builtin_unreachable();
}

U64 U32_hash(U32 self, HashFn hasher) {
    U32 hoisted__U32_1435 = 4;
    (void)hoisted__U32_1435;
    U64 hoisted__U64_1436 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1435); });
    (void)hoisted__U64_1436;
    return hoisted__U64_1436;
    __builtin_unreachable();
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *hoisted__Str_1437 = U64_to_str_ext(val);
    (void)hoisted__Str_1437;
    return hoisted__Str_1437;
    __builtin_unreachable();
}

void U64_delete(U64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize U64_size(void) {
    U32 hoisted__U32_1442 = 8;
    (void)hoisted__U32_1442;
    return hoisted__U32_1442;
    __builtin_unreachable();
}

U64 U64_hash(U64 self, HashFn hasher) {
    U32 hoisted__U32_1527 = 8;
    (void)hoisted__U32_1527;
    U64 hoisted__U64_1528 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1527); });
    (void)hoisted__U64_1528;
    return hoisted__U64_1528;
    __builtin_unreachable();
}

void I8_delete(I8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize I8_size(void) {
    U32 hoisted__U32_1545 = 1;
    (void)hoisted__U32_1545;
    return hoisted__U32_1545;
    __builtin_unreachable();
}

U64 I8_hash(I8 self, HashFn hasher) {
    U32 hoisted__U32_1546 = 1;
    (void)hoisted__U32_1546;
    U64 hoisted__U64_1547 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1546); });
    (void)hoisted__U64_1547;
    return hoisted__U64_1547;
    __builtin_unreachable();
}

void I32_delete(I32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize I32_size(void) {
    U32 hoisted__U32_1724 = 4;
    (void)hoisted__U32_1724;
    return hoisted__U32_1724;
    __builtin_unreachable();
}

U64 I32_hash(I32 self, HashFn hasher) {
    U32 hoisted__U32_1866 = 4;
    (void)hoisted__U32_1866;
    U64 hoisted__U64_1867 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1866); });
    (void)hoisted__U64_1867;
    return hoisted__U64_1867;
    __builtin_unreachable();
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1878 = 0;
    (void)hoisted__I64_1878;
    Bool hoisted__Bool_1879 = ((Bool)(val < hoisted__I64_1878));
    (void)hoisted__Bool_1879;
    if (hoisted__Bool_1879) {
        U64 hoisted__U64_1868 = 0ULL;
        (void)hoisted__U64_1868;
        U64 hoisted__U64_1869 = (U64)(val);
        (void)hoisted__U64_1869;
        U64 mag = ((U64)(hoisted__U64_1868 - hoisted__U64_1869));
        U32 hoisted__U32_1870 = 2;
        (void)hoisted__U32_1870;
        Array__Str *_va_Array_44 = Array__Str_new(hoisted__U32_1870);
        (void)_va_Array_44;
        I64 _va_Array_44_ek = 0;
        (void)_va_Array_44_ek;
        OutOfBounds *_va_Array_44_eo = malloc(sizeof(OutOfBounds));
        _va_Array_44_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_44_eo;
        U32 hoisted__U32_1871 = 0;
        (void)hoisted__U32_1871;
        static Str hoisted__Str_1872 = (Str){.c_str = (void *)"-", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1872;
        static Str hoisted__Str_1873 = (Str){.c_str = (void *)"./src/core/numbers.til:626:20", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1873;
        Array__Str_set(_va_Array_44, hoisted__U32_1871, &hoisted__Str_1872, &_va_Array_44_ek, _va_Array_44_eo, &hoisted__Str_1873);
        Str_delete(&hoisted__Str_1873, (Bool){0});
        U32 hoisted__U32_1874 = 1;
        (void)hoisted__U32_1874;
        Str *hoisted__Str_1875 = U64_to_str(mag);
        (void)hoisted__Str_1875;
        static Str hoisted__Str_1876 = (Str){.c_str = (void *)"./src/core/numbers.til:626:20", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1876;
        Array__Str_set(_va_Array_44, hoisted__U32_1874, hoisted__Str_1875, &_va_Array_44_ek, _va_Array_44_eo, &hoisted__Str_1876);
        OutOfBounds_delete(_va_Array_44_eo, 1);
        Str_delete(&hoisted__Str_1876, (Bool){0});
        Str *hoisted__Str_1877 = format(_va_Array_44);
        (void)hoisted__Str_1877;
        return hoisted__Str_1877;
    }
    U64 hoisted__U64_1880 = (U64)(val);
    (void)hoisted__U64_1880;
    Str *hoisted__Str_1881 = U64_to_str(hoisted__U64_1880);
    (void)hoisted__Str_1881;
    return hoisted__Str_1881;
    __builtin_unreachable();
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize I64_size(void) {
    U32 hoisted__U32_1895 = 8;
    (void)hoisted__U32_1895;
    return hoisted__U32_1895;
    __builtin_unreachable();
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_2053 = 8;
    (void)hoisted__U32_2053;
    U64 hoisted__U64_2054 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2053); });
    (void)hoisted__U64_2054;
    return hoisted__U64_2054;
    __builtin_unreachable();
}

void F32_delete(F32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize F32_size(void) {
    U32 hoisted__U32_2056 = 4;
    (void)hoisted__U32_2056;
    return hoisted__U32_2056;
    __builtin_unreachable();
}

U64 F32_hash(F32 self, HashFn hasher) {
    U32 hoisted__U32_2074 = 4;
    (void)hoisted__U32_2074;
    U64 hoisted__U64_2075 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, F32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2074); });
    (void)hoisted__U64_2075;
    return hoisted__U64_2075;
    __builtin_unreachable();
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_2126 = ((Bool)(a == b));
    (void)hoisted__Bool_2126;
    if (hoisted__Bool_2126) {
        I64 hoisted__I64_2124 = 0;
        (void)hoisted__I64_2124;
        return hoisted__I64_2124;
    }
    if (b) {
        I64 hoisted__I64_2125 = -1;
        (void)hoisted__I64_2125;
        return hoisted__I64_2125;
    }
    I64 hoisted__I64_2127 = 1;
    (void)hoisted__I64_2127;
    return hoisted__I64_2127;
    __builtin_unreachable();
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize Bool_size(void) {
    U32 hoisted__U32_2128 = 1;
    (void)hoisted__U32_2128;
    return hoisted__U32_2128;
    __builtin_unreachable();
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_2129 = 1;
    (void)hoisted__U32_2129;
    U64 hoisted__U64_2130 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2129); });
    (void)hoisted__U64_2130;
    return hoisted__U64_2130;
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
    U32 hoisted__U32_2264 = 1;
    (void)hoisted__U32_2264;
    Bool hoisted__Bool_2265 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I16}))->tag));
    (void)hoisted__Bool_2265;
    if (hoisted__Bool_2265) {
        U32 hoisted__U32_2244 = 1;
        (void)hoisted__U32_2244;
        Bool hoisted__Bool_2245 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I16}))->tag));
        (void)hoisted__Bool_2245;
        return hoisted__Bool_2245;
    }
    U32 hoisted__U32_2266 = 1;
    (void)hoisted__U32_2266;
    Bool hoisted__Bool_2267 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U16}))->tag));
    (void)hoisted__Bool_2267;
    if (hoisted__Bool_2267) {
        U32 hoisted__U32_2246 = 1;
        (void)hoisted__U32_2246;
        Bool hoisted__Bool_2247 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U16}))->tag));
        (void)hoisted__Bool_2247;
        return hoisted__Bool_2247;
    }
    U32 hoisted__U32_2268 = 1;
    (void)hoisted__U32_2268;
    Bool hoisted__Bool_2269 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I8}))->tag));
    (void)hoisted__Bool_2269;
    if (hoisted__Bool_2269) {
        U32 hoisted__U32_2248 = 1;
        (void)hoisted__U32_2248;
        Bool hoisted__Bool_2249 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I8}))->tag));
        (void)hoisted__Bool_2249;
        return hoisted__Bool_2249;
    }
    U32 hoisted__U32_2270 = 1;
    (void)hoisted__U32_2270;
    Bool hoisted__Bool_2271 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U8}))->tag));
    (void)hoisted__Bool_2271;
    if (hoisted__Bool_2271) {
        U32 hoisted__U32_2250 = 1;
        (void)hoisted__U32_2250;
        Bool hoisted__Bool_2251 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U8}))->tag));
        (void)hoisted__Bool_2251;
        return hoisted__Bool_2251;
    }
    U32 hoisted__U32_2272 = 1;
    (void)hoisted__U32_2272;
    Bool hoisted__Bool_2273 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U32}))->tag));
    (void)hoisted__Bool_2273;
    if (hoisted__Bool_2273) {
        U32 hoisted__U32_2252 = 1;
        (void)hoisted__U32_2252;
        Bool hoisted__Bool_2253 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U32}))->tag));
        (void)hoisted__Bool_2253;
        return hoisted__Bool_2253;
    }
    U32 hoisted__U32_2274 = 1;
    (void)hoisted__U32_2274;
    Bool hoisted__Bool_2275 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I32}))->tag));
    (void)hoisted__Bool_2275;
    if (hoisted__Bool_2275) {
        U32 hoisted__U32_2254 = 1;
        (void)hoisted__U32_2254;
        Bool hoisted__Bool_2255 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I32}))->tag));
        (void)hoisted__Bool_2255;
        return hoisted__Bool_2255;
    }
    U32 hoisted__U32_2276 = 1;
    (void)hoisted__U32_2276;
    Bool hoisted__Bool_2277 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U64}))->tag));
    (void)hoisted__Bool_2277;
    if (hoisted__Bool_2277) {
        U32 hoisted__U32_2256 = 1;
        (void)hoisted__U32_2256;
        Bool hoisted__Bool_2257 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U64}))->tag));
        (void)hoisted__Bool_2257;
        return hoisted__Bool_2257;
    }
    U32 hoisted__U32_2278 = 1;
    (void)hoisted__U32_2278;
    Bool hoisted__Bool_2279 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I64}))->tag));
    (void)hoisted__Bool_2279;
    if (hoisted__Bool_2279) {
        U32 hoisted__U32_2258 = 1;
        (void)hoisted__U32_2258;
        Bool hoisted__Bool_2259 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I64}))->tag));
        (void)hoisted__Bool_2259;
        return hoisted__Bool_2259;
    }
    U32 hoisted__U32_2280 = 1;
    (void)hoisted__U32_2280;
    Bool hoisted__Bool_2281 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_F32}))->tag));
    (void)hoisted__Bool_2281;
    if (hoisted__Bool_2281) {
        U32 hoisted__U32_2260 = 1;
        (void)hoisted__U32_2260;
        Bool hoisted__Bool_2261 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_F32}))->tag));
        (void)hoisted__Bool_2261;
        return hoisted__Bool_2261;
    }
    U32 hoisted__U32_2282 = 1;
    (void)hoisted__U32_2282;
    Bool hoisted__Bool_2283 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_Bool}))->tag));
    (void)hoisted__Bool_2283;
    if (hoisted__Bool_2283) {
        U32 hoisted__U32_2262 = 1;
        (void)hoisted__U32_2262;
        Bool hoisted__Bool_2263 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_Bool}))->tag));
        (void)hoisted__Bool_2263;
        return hoisted__Bool_2263;
    }
    Bool hoisted__Bool_2284 = 0;
    (void)hoisted__Bool_2284;
    return hoisted__Bool_2284;
    __builtin_unreachable();
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2306 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2306;
    if (hoisted__Bool_2306) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
        return _r; }
    }
    Bool hoisted__Bool_2307 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2307;
    if (hoisted__Bool_2307) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
        return _r; }
    }
    Bool hoisted__Bool_2308 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2308;
    if (hoisted__Bool_2308) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
        return _r; }
    }
    Bool hoisted__Bool_2309 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2309;
    if (hoisted__Bool_2309) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
        return _r; }
    }
    Bool hoisted__Bool_2310 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2310;
    if (hoisted__Bool_2310) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
        return _r; }
    }
    Bool hoisted__Bool_2311 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2311;
    if (hoisted__Bool_2311) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
        return _r; }
    }
    Bool hoisted__Bool_2312 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2312;
    if (hoisted__Bool_2312) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
        return _r; }
    }
    Bool hoisted__Bool_2313 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2313;
    if (hoisted__Bool_2313) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
        return _r; }
    }
    Bool hoisted__Bool_2314 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2314;
    if (hoisted__Bool_2314) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
        return _r; }
    }
    Bool hoisted__Bool_2315 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2315;
    if (hoisted__Bool_2315) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
        return _r; }
    }
    static Str hoisted__Str_2316 = (Str){.c_str = (void *)"Primitive.clone:15:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2316;
    UNREACHABLE(&hoisted__Str_2316);
    Str_delete(&hoisted__Str_2316, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
    __builtin_unreachable();
}

USize Primitive_size(void) {
    U32 hoisted__U32_2317 = 1;
    (void)hoisted__U32_2317;
    return hoisted__U32_2317;
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
    U32 hoisted__U32_2396 = 1;
    (void)hoisted__U32_2396;
    Bool hoisted__Bool_2397 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Struct}))->tag));
    (void)hoisted__Bool_2397;
    if (hoisted__Bool_2397) {
        Str *hoisted__Str_2386 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Str_2386;
        (void)hoisted__Str_2386;
        Bool hoisted__Bool_2387 = 0;
        (void)hoisted__Bool_2387;
        Str_delete(hoisted__Str_2386, hoisted__Bool_2387);
    }
    U32 hoisted__U32_2398 = 1;
    (void)hoisted__U32_2398;
    Bool hoisted__Bool_2399 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Enum}))->tag));
    (void)hoisted__Bool_2399;
    if (hoisted__Bool_2399) {
        Str *hoisted__Str_2388 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Str_2388;
        (void)hoisted__Str_2388;
        Bool hoisted__Bool_2389 = 0;
        (void)hoisted__Bool_2389;
        Str_delete(hoisted__Str_2388, hoisted__Bool_2389);
    }
    U32 hoisted__U32_2400 = 1;
    (void)hoisted__U32_2400;
    Bool hoisted__Bool_2401 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Custom}))->tag));
    (void)hoisted__Bool_2401;
    if (hoisted__Bool_2401) {
        Str *hoisted__Str_2390 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Str_2390;
        (void)hoisted__Str_2390;
        Bool hoisted__Bool_2391 = 0;
        (void)hoisted__Bool_2391;
        Str_delete(hoisted__Str_2390, hoisted__Bool_2391);
    }
    U32 hoisted__U32_2402 = 1;
    (void)hoisted__U32_2402;
    Bool hoisted__Bool_2403 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Primitive}))->tag));
    (void)hoisted__Bool_2403;
    if (hoisted__Bool_2403) {
        Primitive *hoisted__Primitive_2392 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Primitive_2392;
        (void)hoisted__Primitive_2392;
        Bool hoisted__Bool_2393 = 0;
        (void)hoisted__Bool_2393;
        Primitive_delete(hoisted__Primitive_2392, hoisted__Bool_2393);
    }
    U32 hoisted__U32_2404 = 1;
    (void)hoisted__U32_2404;
    Bool hoisted__Bool_2405 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtrSig}))->tag));
    (void)hoisted__Bool_2405;
    if (hoisted__Bool_2405) {
        Str *hoisted__Str_2394 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Str_2394;
        (void)hoisted__Str_2394;
        Bool hoisted__Bool_2395 = 0;
        (void)hoisted__Bool_2395;
        Str_delete(hoisted__Str_2394, hoisted__Bool_2395);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    U32 hoisted__U32_2506 = 1;
    (void)hoisted__U32_2506;
    Bool hoisted__Bool_2507 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Unknown}))->tag));
    (void)hoisted__Bool_2507;
    if (hoisted__Bool_2507) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
        return _r; }
    }
    U32 hoisted__U32_2508 = 1;
    (void)hoisted__U32_2508;
    Bool hoisted__Bool_2509 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_None}))->tag));
    (void)hoisted__Bool_2509;
    if (hoisted__Bool_2509) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
        return _r; }
    }
    U32 hoisted__U32_2510 = 1;
    (void)hoisted__U32_2510;
    Bool hoisted__Bool_2511 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Struct}))->tag));
    (void)hoisted__Bool_2511;
    if (hoisted__Bool_2511) {
        Str *_clone_payload_Struct_2 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2496 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2496;
        Type *hoisted__Type_2497 = Type_Struct(hoisted__Str_2496);
        (void)hoisted__Type_2497;
        return hoisted__Type_2497;
    }
    U32 hoisted__U32_2512 = 1;
    (void)hoisted__U32_2512;
    Bool hoisted__Bool_2513 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_StructDef}))->tag));
    (void)hoisted__Bool_2513;
    if (hoisted__Bool_2513) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
        return _r; }
    }
    U32 hoisted__U32_2514 = 1;
    (void)hoisted__U32_2514;
    Bool hoisted__Bool_2515 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Enum}))->tag));
    (void)hoisted__Bool_2515;
    if (hoisted__Bool_2515) {
        Str *_clone_payload_Enum_4 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2498 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2498;
        Type *hoisted__Type_2499 = Type_Enum(hoisted__Str_2498);
        (void)hoisted__Type_2499;
        return hoisted__Type_2499;
    }
    U32 hoisted__U32_2516 = 1;
    (void)hoisted__U32_2516;
    Bool hoisted__Bool_2517 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_2517;
    if (hoisted__Bool_2517) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
        return _r; }
    }
    U32 hoisted__U32_2518 = 1;
    (void)hoisted__U32_2518;
    Bool hoisted__Bool_2519 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_2519;
    if (hoisted__Bool_2519) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
        return _r; }
    }
    U32 hoisted__U32_2520 = 1;
    (void)hoisted__U32_2520;
    Bool hoisted__Bool_2521 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtr}))->tag));
    (void)hoisted__Bool_2521;
    if (hoisted__Bool_2521) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
        return _r; }
    }
    U32 hoisted__U32_2522 = 1;
    (void)hoisted__U32_2522;
    Bool hoisted__Bool_2523 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Dynamic}))->tag));
    (void)hoisted__Bool_2523;
    if (hoisted__Bool_2523) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
        return _r; }
    }
    U32 hoisted__U32_2524 = 1;
    (void)hoisted__U32_2524;
    Bool hoisted__Bool_2525 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Custom}))->tag));
    (void)hoisted__Bool_2525;
    if (hoisted__Bool_2525) {
        Str *_clone_payload_Custom_9 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2500 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2500;
        Type *hoisted__Type_2501 = Type_Custom(hoisted__Str_2500);
        (void)hoisted__Type_2501;
        return hoisted__Type_2501;
    }
    U32 hoisted__U32_2526 = 1;
    (void)hoisted__U32_2526;
    Bool hoisted__Bool_2527 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Primitive}))->tag));
    (void)hoisted__Bool_2527;
    if (hoisted__Bool_2527) {
        Primitive *_clone_payload_Primitive_10 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2502 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2502;
        Type *hoisted__Type_2503 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2502; _oa; }));
        (void)hoisted__Type_2503;
        return hoisted__Type_2503;
    }
    U32 hoisted__U32_2528 = 1;
    (void)hoisted__U32_2528;
    Bool hoisted__Bool_2529 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtrSig}))->tag));
    (void)hoisted__Bool_2529;
    if (hoisted__Bool_2529) {
        Str *_clone_payload_FuncPtrSig_11 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_FuncPtrSig_11;
        (void)_clone_payload_FuncPtrSig_11;
        Str *hoisted__Str_2504 = Str_clone(_clone_payload_FuncPtrSig_11);
        (void)hoisted__Str_2504;
        Type *hoisted__Type_2505 = Type_FuncPtrSig(hoisted__Str_2504);
        (void)hoisted__Type_2505;
        return hoisted__Type_2505;
    }
    { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Body;
    return _r; }
    __builtin_unreachable();
}

USize Type_size(void) {
    U32 hoisted__U32_2530 = 24;
    (void)hoisted__U32_2530;
    return hoisted__U32_2530;
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
    U32 hoisted__U32_2564 = 1;
    (void)hoisted__U32_2564;
    Bool hoisted__Bool_2565 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Func}))->tag));
    (void)hoisted__Bool_2565;
    if (hoisted__Bool_2565) {
        U32 hoisted__U32_2542 = 1;
        (void)hoisted__U32_2542;
        Bool hoisted__Bool_2543 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Func}))->tag));
        (void)hoisted__Bool_2543;
        return hoisted__Bool_2543;
    }
    U32 hoisted__U32_2566 = 1;
    (void)hoisted__U32_2566;
    Bool hoisted__Bool_2567 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Proc}))->tag));
    (void)hoisted__Bool_2567;
    if (hoisted__Bool_2567) {
        U32 hoisted__U32_2544 = 1;
        (void)hoisted__U32_2544;
        Bool hoisted__Bool_2545 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Proc}))->tag));
        (void)hoisted__Bool_2545;
        return hoisted__Bool_2545;
    }
    U32 hoisted__U32_2568 = 1;
    (void)hoisted__U32_2568;
    Bool hoisted__Bool_2569 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Test}))->tag));
    (void)hoisted__Bool_2569;
    if (hoisted__Bool_2569) {
        U32 hoisted__U32_2546 = 1;
        (void)hoisted__U32_2546;
        Bool hoisted__Bool_2547 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Test}))->tag));
        (void)hoisted__Bool_2547;
        return hoisted__Bool_2547;
    }
    U32 hoisted__U32_2570 = 1;
    (void)hoisted__U32_2570;
    Bool hoisted__Bool_2571 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Macro}))->tag));
    (void)hoisted__Bool_2571;
    if (hoisted__Bool_2571) {
        U32 hoisted__U32_2548 = 1;
        (void)hoisted__U32_2548;
        Bool hoisted__Bool_2549 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Macro}))->tag));
        (void)hoisted__Bool_2549;
        return hoisted__Bool_2549;
    }
    U32 hoisted__U32_2572 = 1;
    (void)hoisted__U32_2572;
    Bool hoisted__Bool_2573 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtFunc}))->tag));
    (void)hoisted__Bool_2573;
    if (hoisted__Bool_2573) {
        U32 hoisted__U32_2550 = 1;
        (void)hoisted__U32_2550;
        Bool hoisted__Bool_2551 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtFunc}))->tag));
        (void)hoisted__Bool_2551;
        return hoisted__Bool_2551;
    }
    U32 hoisted__U32_2574 = 1;
    (void)hoisted__U32_2574;
    Bool hoisted__Bool_2575 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtProc}))->tag));
    (void)hoisted__Bool_2575;
    if (hoisted__Bool_2575) {
        U32 hoisted__U32_2552 = 1;
        (void)hoisted__U32_2552;
        Bool hoisted__Bool_2553 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtProc}))->tag));
        (void)hoisted__Bool_2553;
        return hoisted__Bool_2553;
    }
    U32 hoisted__U32_2576 = 1;
    (void)hoisted__U32_2576;
    Bool hoisted__Bool_2577 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyFunc}))->tag));
    (void)hoisted__Bool_2577;
    if (hoisted__Bool_2577) {
        U32 hoisted__U32_2554 = 1;
        (void)hoisted__U32_2554;
        Bool hoisted__Bool_2555 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyFunc}))->tag));
        (void)hoisted__Bool_2555;
        return hoisted__Bool_2555;
    }
    U32 hoisted__U32_2578 = 1;
    (void)hoisted__U32_2578;
    Bool hoisted__Bool_2579 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyProc}))->tag));
    (void)hoisted__Bool_2579;
    if (hoisted__Bool_2579) {
        U32 hoisted__U32_2556 = 1;
        (void)hoisted__U32_2556;
        Bool hoisted__Bool_2557 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyProc}))->tag));
        (void)hoisted__Bool_2557;
        return hoisted__Bool_2557;
    }
    U32 hoisted__U32_2580 = 1;
    (void)hoisted__U32_2580;
    Bool hoisted__Bool_2581 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreFunc}))->tag));
    (void)hoisted__Bool_2581;
    if (hoisted__Bool_2581) {
        U32 hoisted__U32_2558 = 1;
        (void)hoisted__U32_2558;
        Bool hoisted__Bool_2559 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreFunc}))->tag));
        (void)hoisted__Bool_2559;
        return hoisted__Bool_2559;
    }
    U32 hoisted__U32_2582 = 1;
    (void)hoisted__U32_2582;
    Bool hoisted__Bool_2583 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreProc}))->tag));
    (void)hoisted__Bool_2583;
    if (hoisted__Bool_2583) {
        U32 hoisted__U32_2560 = 1;
        (void)hoisted__U32_2560;
        Bool hoisted__Bool_2561 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreProc}))->tag));
        (void)hoisted__Bool_2561;
        return hoisted__Bool_2561;
    }
    U32 hoisted__U32_2584 = 1;
    (void)hoisted__U32_2584;
    Bool hoisted__Bool_2585 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreLazyFunc}))->tag));
    (void)hoisted__Bool_2585;
    if (hoisted__Bool_2585) {
        U32 hoisted__U32_2562 = 1;
        (void)hoisted__U32_2562;
        Bool hoisted__Bool_2563 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreLazyFunc}))->tag));
        (void)hoisted__Bool_2563;
        return hoisted__Bool_2563;
    }
    Bool hoisted__Bool_2586 = 0;
    (void)hoisted__Bool_2586;
    return hoisted__Bool_2586;
    __builtin_unreachable();
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2610 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2610;
    if (hoisted__Bool_2610) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
        return _r; }
    }
    Bool hoisted__Bool_2611 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2611;
    if (hoisted__Bool_2611) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
        return _r; }
    }
    Bool hoisted__Bool_2612 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2612;
    if (hoisted__Bool_2612) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
        return _r; }
    }
    Bool hoisted__Bool_2613 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2613;
    if (hoisted__Bool_2613) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
        return _r; }
    }
    Bool hoisted__Bool_2614 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2614;
    if (hoisted__Bool_2614) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
        return _r; }
    }
    Bool hoisted__Bool_2615 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2615;
    if (hoisted__Bool_2615) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
        return _r; }
    }
    Bool hoisted__Bool_2616 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2616;
    if (hoisted__Bool_2616) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
        return _r; }
    }
    Bool hoisted__Bool_2617 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2617;
    if (hoisted__Bool_2617) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
        return _r; }
    }
    Bool hoisted__Bool_2618 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreFunc});
    (void)hoisted__Bool_2618;
    if (hoisted__Bool_2618) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreFunc;
        return _r; }
    }
    Bool hoisted__Bool_2619 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreProc});
    (void)hoisted__Bool_2619;
    if (hoisted__Bool_2619) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreProc;
        return _r; }
    }
    Bool hoisted__Bool_2620 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreLazyFunc});
    (void)hoisted__Bool_2620;
    if (hoisted__Bool_2620) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreLazyFunc;
        return _r; }
    }
    static Str hoisted__Str_2621 = (Str){.c_str = (void *)"FuncType.clone:70:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2621;
    UNREACHABLE(&hoisted__Str_2621);
    Str_delete(&hoisted__Str_2621, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
    __builtin_unreachable();
}

USize FuncType_size(void) {
    U32 hoisted__U32_2622 = 1;
    (void)hoisted__U32_2622;
    return hoisted__U32_2622;
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
    U32 hoisted__U32_2629 = 1;
    (void)hoisted__U32_2629;
    Bool hoisted__Bool_2630 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Own}))->tag));
    (void)hoisted__Bool_2630;
    if (hoisted__Bool_2630) {
        U32 hoisted__U32_2623 = 1;
        (void)hoisted__U32_2623;
        Bool hoisted__Bool_2624 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Own}))->tag));
        (void)hoisted__Bool_2624;
        return hoisted__Bool_2624;
    }
    U32 hoisted__U32_2631 = 1;
    (void)hoisted__U32_2631;
    Bool hoisted__Bool_2632 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Ref}))->tag));
    (void)hoisted__Bool_2632;
    if (hoisted__Bool_2632) {
        U32 hoisted__U32_2625 = 1;
        (void)hoisted__U32_2625;
        Bool hoisted__Bool_2626 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Ref}))->tag));
        (void)hoisted__Bool_2626;
        return hoisted__Bool_2626;
    }
    U32 hoisted__U32_2633 = 1;
    (void)hoisted__U32_2633;
    Bool hoisted__Bool_2634 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Shallow}))->tag));
    (void)hoisted__Bool_2634;
    if (hoisted__Bool_2634) {
        U32 hoisted__U32_2627 = 1;
        (void)hoisted__U32_2627;
        Bool hoisted__Bool_2628 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Shallow}))->tag));
        (void)hoisted__Bool_2628;
        return hoisted__Bool_2628;
    }
    Bool hoisted__Bool_2635 = 0;
    (void)hoisted__Bool_2635;
    return hoisted__Bool_2635;
    __builtin_unreachable();
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2643 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2643;
    if (hoisted__Bool_2643) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
        return _r; }
    }
    Bool hoisted__Bool_2644 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2644;
    if (hoisted__Bool_2644) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
        return _r; }
    }
    Bool hoisted__Bool_2645 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2645;
    if (hoisted__Bool_2645) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
        return _r; }
    }
    static Str hoisted__Str_2646 = (Str){.c_str = (void *)"OwnType.clone:108:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2646;
    UNREACHABLE(&hoisted__Str_2646);
    Str_delete(&hoisted__Str_2646, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
    __builtin_unreachable();
}

USize OwnType_size(void) {
    U32 hoisted__U32_2647 = 1;
    (void)hoisted__U32_2647;
    return hoisted__U32_2647;
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
    U32 hoisted__U32_2654 = 1;
    (void)hoisted__U32_2654;
    Bool hoisted__Bool_2655 = ((Bool)(((GcStorage *)(self))->tag == ((GcStorage *)(&(GcStorage){.tag = GcStorage_TAG_Unset}))->tag));
    (void)hoisted__Bool_2655;
    if (hoisted__Bool_2655) {
        U32 hoisted__U32_2648 = 1;
        (void)hoisted__U32_2648;
        Bool hoisted__Bool_2649 = ((Bool)(((GcStorage *)(other))->tag == ((GcStorage *)(&(GcStorage){.tag = GcStorage_TAG_Unset}))->tag));
        (void)hoisted__Bool_2649;
        return hoisted__Bool_2649;
    }
    U32 hoisted__U32_2656 = 1;
    (void)hoisted__U32_2656;
    Bool hoisted__Bool_2657 = ((Bool)(((GcStorage *)(self))->tag == ((GcStorage *)(&(GcStorage){.tag = GcStorage_TAG_Stack}))->tag));
    (void)hoisted__Bool_2657;
    if (hoisted__Bool_2657) {
        U32 hoisted__U32_2650 = 1;
        (void)hoisted__U32_2650;
        Bool hoisted__Bool_2651 = ((Bool)(((GcStorage *)(other))->tag == ((GcStorage *)(&(GcStorage){.tag = GcStorage_TAG_Stack}))->tag));
        (void)hoisted__Bool_2651;
        return hoisted__Bool_2651;
    }
    U32 hoisted__U32_2658 = 1;
    (void)hoisted__U32_2658;
    Bool hoisted__Bool_2659 = ((Bool)(((GcStorage *)(self))->tag == ((GcStorage *)(&(GcStorage){.tag = GcStorage_TAG_HeapBox}))->tag));
    (void)hoisted__Bool_2659;
    if (hoisted__Bool_2659) {
        U32 hoisted__U32_2652 = 1;
        (void)hoisted__U32_2652;
        Bool hoisted__Bool_2653 = ((Bool)(((GcStorage *)(other))->tag == ((GcStorage *)(&(GcStorage){.tag = GcStorage_TAG_HeapBox}))->tag));
        (void)hoisted__Bool_2653;
        return hoisted__Bool_2653;
    }
    Bool hoisted__Bool_2660 = 0;
    (void)hoisted__Bool_2660;
    return hoisted__Bool_2660;
    __builtin_unreachable();
}

void GcStorage_delete(GcStorage * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

GcStorage * GcStorage_clone(GcStorage * self) {
    Bool hoisted__Bool_2668 = GcStorage_eq(self, &(GcStorage){.tag = GcStorage_TAG_Unset});
    (void)hoisted__Bool_2668;
    if (hoisted__Bool_2668) {
        { GcStorage *_r = malloc(sizeof(GcStorage)); _r->tag = GcStorage_TAG_Unset;
        return _r; }
    }
    Bool hoisted__Bool_2669 = GcStorage_eq(self, &(GcStorage){.tag = GcStorage_TAG_Stack});
    (void)hoisted__Bool_2669;
    if (hoisted__Bool_2669) {
        { GcStorage *_r = malloc(sizeof(GcStorage)); _r->tag = GcStorage_TAG_Stack;
        return _r; }
    }
    Bool hoisted__Bool_2670 = GcStorage_eq(self, &(GcStorage){.tag = GcStorage_TAG_HeapBox});
    (void)hoisted__Bool_2670;
    if (hoisted__Bool_2670) {
        { GcStorage *_r = malloc(sizeof(GcStorage)); _r->tag = GcStorage_TAG_HeapBox;
        return _r; }
    }
    static Str hoisted__Str_2671 = (Str){.c_str = (void *)"GcStorage.clone:119:1", .count = 21ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2671;
    UNREACHABLE(&hoisted__Str_2671);
    Str_delete(&hoisted__Str_2671, (Bool){0});
    { GcStorage *_r = malloc(sizeof(GcStorage)); _r->tag = GcStorage_TAG_Unset;
    return _r; }
    __builtin_unreachable();
}

USize GcStorage_size(void) {
    U32 hoisted__U32_2672 = 1;
    (void)hoisted__U32_2672;
    return hoisted__U32_2672;
    __builtin_unreachable();
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2674 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2674;
    Declaration *hoisted__Declaration_2675 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2675->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2675->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2675->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2675->is_mut = self->is_mut;
    hoisted__Declaration_2675->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2675->is_priv = self->is_priv;
    hoisted__Declaration_2675->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2675->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2675->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2675->default_value = hoisted__Expr_2674;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2675->orig_name = *_ca; free(_ca); }
    { GcStorage *_ca = GcStorage_clone(&self->gc_storage); hoisted__Declaration_2675->gc_storage = *_ca; free(_ca); }
    (void)hoisted__Declaration_2675;
    return hoisted__Declaration_2675;
    __builtin_unreachable();
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2676 = 0;
    (void)hoisted__Bool_2676;
    Str_delete(&self->name, hoisted__Bool_2676);
    Bool hoisted__Bool_2677 = 0;
    (void)hoisted__Bool_2677;
    Str_delete(&self->doc, hoisted__Bool_2677);
    Bool hoisted__Bool_2678 = 0;
    (void)hoisted__Bool_2678;
    Str_delete(&self->explicit_type, hoisted__Bool_2678);
    Bool hoisted__Bool_2679 = 0;
    (void)hoisted__Bool_2679;
    Bool_delete(&self->is_mut, hoisted__Bool_2679);
    Bool hoisted__Bool_2680 = 0;
    (void)hoisted__Bool_2680;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2680);
    Bool hoisted__Bool_2681 = 0;
    (void)hoisted__Bool_2681;
    Bool_delete(&self->is_priv, hoisted__Bool_2681);
    Bool hoisted__Bool_2682 = 0;
    (void)hoisted__Bool_2682;
    Bool_delete(&self->used, hoisted__Bool_2682);
    Bool hoisted__Bool_2683 = 0;
    (void)hoisted__Bool_2683;
    OwnType_delete(&self->own_type, hoisted__Bool_2683);
    Bool hoisted__Bool_2684 = 0;
    (void)hoisted__Bool_2684;
    Type_delete(&self->til_type, hoisted__Bool_2684);
    Bool hoisted__Bool_2685 = 1;
    (void)hoisted__Bool_2685;
    Expr_delete(self->default_value, hoisted__Bool_2685);
    Bool hoisted__Bool_2686 = 0;
    (void)hoisted__Bool_2686;
    Str_delete(&self->orig_name, hoisted__Bool_2686);
    Bool hoisted__Bool_2687 = 0;
    (void)hoisted__Bool_2687;
    GcStorage_delete(&self->gc_storage, hoisted__Bool_2687);
    if (call_free) {
        free(self);
    }
}

USize Declaration_size(void) {
    U32 hoisted__U32_2688 = 112;
    (void)hoisted__U32_2688;
    return hoisted__U32_2688;
    __builtin_unreachable();
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2690 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2690->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2690->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2690->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2690->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2690->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2690->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2690->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2690->return_shallow_explicit = self->return_shallow_explicit;
    hoisted__FunctionDef_2690->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2690->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2690->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2690->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2690;
    return hoisted__FunctionDef_2690;
    __builtin_unreachable();
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2691 = 0;
    (void)hoisted__Bool_2691;
    FuncType_delete(&self->func_type, hoisted__Bool_2691);
    Bool hoisted__Bool_2692 = 0;
    (void)hoisted__Bool_2692;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2692);
    Bool hoisted__Bool_2693 = 0;
    (void)hoisted__Bool_2693;
    Str_delete(&self->return_type, hoisted__Bool_2693);
    Bool hoisted__Bool_2694 = 0;
    (void)hoisted__Bool_2694;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2694);
    Bool hoisted__Bool_2695 = 0;
    (void)hoisted__Bool_2695;
    I32_delete(&self->variadic_index, hoisted__Bool_2695);
    Bool hoisted__Bool_2696 = 0;
    (void)hoisted__Bool_2696;
    I32_delete(&self->kwargs_index, hoisted__Bool_2696);
    Bool hoisted__Bool_2697 = 0;
    (void)hoisted__Bool_2697;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2697);
    Bool hoisted__Bool_2698 = 0;
    (void)hoisted__Bool_2698;
    Bool_delete(&self->return_shallow_explicit, hoisted__Bool_2698);
    Bool hoisted__Bool_2699 = 0;
    (void)hoisted__Bool_2699;
    Bool_delete(&self->auto_generated, hoisted__Bool_2699);
    Bool hoisted__Bool_2700 = 0;
    (void)hoisted__Bool_2700;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2700);
    Bool hoisted__Bool_2701 = 0;
    (void)hoisted__Bool_2701;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2701);
    Bool hoisted__Bool_2702 = 0;
    (void)hoisted__Bool_2702;
    Str_delete(&self->closure_name, hoisted__Bool_2702);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2703 = 0;
    (void)hoisted__U32_2703;
    U64 hoisted__U64_2704 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2703); });
    (void)hoisted__U64_2704;
    return hoisted__U64_2704;
    __builtin_unreachable();
}

USize FunctionDef_size(void) {
    U32 hoisted__U32_2705 = 104;
    (void)hoisted__U32_2705;
    return hoisted__U32_2705;
    __builtin_unreachable();
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2708 = malloc(sizeof(FCallData));
    hoisted__FCallData_2708->is_splat = self->is_splat;
    hoisted__FCallData_2708->does_throw = self->does_throw;
    hoisted__FCallData_2708->is_bang = self->is_bang;
    hoisted__FCallData_2708->own_args = self->own_args;
    hoisted__FCallData_2708->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2708->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2708;
    return hoisted__FCallData_2708;
    __builtin_unreachable();
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2709 = 0;
    (void)hoisted__Bool_2709;
    Bool_delete(&self->is_splat, hoisted__Bool_2709);
    Bool hoisted__Bool_2710 = 0;
    (void)hoisted__Bool_2710;
    Bool_delete(&self->does_throw, hoisted__Bool_2710);
    Bool hoisted__Bool_2711 = 0;
    (void)hoisted__Bool_2711;
    Bool_delete(&self->is_bang, hoisted__Bool_2711);
    Bool hoisted__Bool_2712 = 0;
    (void)hoisted__Bool_2712;
    U64_delete(&self->own_args, hoisted__Bool_2712);
    Bool hoisted__Bool_2713 = 0;
    (void)hoisted__Bool_2713;
    Bool_delete(&self->swap_replace, hoisted__Bool_2713);
    Bool hoisted__Bool_2714 = 0;
    (void)hoisted__Bool_2714;
    Type_delete(&self->til_type, hoisted__Bool_2714);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2715 = 0;
    (void)hoisted__U32_2715;
    U64 hoisted__U64_2716 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2715); });
    (void)hoisted__U64_2716;
    return hoisted__U64_2716;
    __builtin_unreachable();
}

USize FCallData_size(void) {
    U32 hoisted__U32_2717 = 48;
    (void)hoisted__U32_2717;
    return hoisted__U32_2717;
    __builtin_unreachable();
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2730 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2730->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2730->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2730;
    return hoisted__LiteralNumData_2730;
    __builtin_unreachable();
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2731 = 0;
    (void)hoisted__Bool_2731;
    Str_delete(&self->text, hoisted__Bool_2731);
    Bool hoisted__Bool_2732 = 0;
    (void)hoisted__Bool_2732;
    Type_delete(&self->til_type, hoisted__Bool_2732);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2733 = 0;
    (void)hoisted__U32_2733;
    U64 hoisted__U64_2734 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2733); });
    (void)hoisted__U64_2734;
    return hoisted__U64_2734;
    __builtin_unreachable();
}

USize LiteralNumData_size(void) {
    U32 hoisted__U32_2735 = 40;
    (void)hoisted__U32_2735;
    return hoisted__U32_2735;
    __builtin_unreachable();
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2745 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2745->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2745->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2745;
    return hoisted__IdentData_2745;
    __builtin_unreachable();
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2746 = 0;
    (void)hoisted__Bool_2746;
    Str_delete(&self->name, hoisted__Bool_2746);
    Bool hoisted__Bool_2747 = 0;
    (void)hoisted__Bool_2747;
    Type_delete(&self->til_type, hoisted__Bool_2747);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2748 = 0;
    (void)hoisted__U32_2748;
    U64 hoisted__U64_2749 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2748); });
    (void)hoisted__U64_2749;
    return hoisted__U64_2749;
    __builtin_unreachable();
}

USize IdentData_size(void) {
    U32 hoisted__U32_2750 = 40;
    (void)hoisted__U32_2750;
    return hoisted__U32_2750;
    __builtin_unreachable();
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2756 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2756->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2756->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2756;
    return hoisted__FieldAccessData_2756;
    __builtin_unreachable();
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2757 = 0;
    (void)hoisted__Bool_2757;
    Str_delete(&self->name, hoisted__Bool_2757);
    Bool hoisted__Bool_2758 = 0;
    (void)hoisted__Bool_2758;
    Type_delete(&self->til_type, hoisted__Bool_2758);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2759 = 0;
    (void)hoisted__U32_2759;
    U64 hoisted__U64_2760 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2759); });
    (void)hoisted__U64_2760;
    return hoisted__U64_2760;
    __builtin_unreachable();
}

USize FieldAccessData_size(void) {
    U32 hoisted__U32_2761 = 40;
    (void)hoisted__U32_2761;
    return hoisted__U32_2761;
    __builtin_unreachable();
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2766 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2766->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2766->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2766->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2766->is_interface = self->is_interface;
    hoisted__StructDef_2766->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2766->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2766;
    return hoisted__StructDef_2766;
    __builtin_unreachable();
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2767 = 0;
    (void)hoisted__Bool_2767;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2767);
    Bool hoisted__Bool_2768 = 0;
    (void)hoisted__Bool_2768;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2768);
    Bool hoisted__Bool_2769 = 0;
    (void)hoisted__Bool_2769;
    Str_delete(&self->c_tag, hoisted__Bool_2769);
    Bool hoisted__Bool_2770 = 0;
    (void)hoisted__Bool_2770;
    Bool_delete(&self->is_interface, hoisted__Bool_2770);
    Bool hoisted__Bool_2771 = 0;
    (void)hoisted__Bool_2771;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2771);
    Bool hoisted__Bool_2772 = 0;
    (void)hoisted__Bool_2772;
    Str_delete(&self->implements_name, hoisted__Bool_2772);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U32 hoisted__U32_2773 = 0;
    (void)hoisted__U32_2773;
    U64 hoisted__U64_2774 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2773); });
    (void)hoisted__U64_2774;
    return hoisted__U64_2774;
    __builtin_unreachable();
}

USize StructDef_size(void) {
    U32 hoisted__U32_2775 = 72;
    (void)hoisted__U32_2775;
    return hoisted__U32_2775;
    __builtin_unreachable();
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2780 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2780->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2780->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2780->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2780->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2780->implements_name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->tag_type); hoisted__EnumDef_2780->tag_type = *_ca; free(_ca); }
    { Vec__I64 *_ca = Vec__I64_clone(&self->tag_values); hoisted__EnumDef_2780->tag_values = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2780;
    return hoisted__EnumDef_2780;
    __builtin_unreachable();
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2781 = 0;
    (void)hoisted__Bool_2781;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2781);
    Bool hoisted__Bool_2782 = 0;
    (void)hoisted__Bool_2782;
    Vec__Str_delete(&self->variants, hoisted__Bool_2782);
    Bool hoisted__Bool_2783 = 0;
    (void)hoisted__Bool_2783;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2783);
    Bool hoisted__Bool_2784 = 0;
    (void)hoisted__Bool_2784;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2784);
    Bool hoisted__Bool_2785 = 0;
    (void)hoisted__Bool_2785;
    Str_delete(&self->implements_name, hoisted__Bool_2785);
    Bool hoisted__Bool_2786 = 0;
    (void)hoisted__Bool_2786;
    Str_delete(&self->tag_type, hoisted__Bool_2786);
    Bool hoisted__Bool_2787 = 0;
    (void)hoisted__Bool_2787;
    Vec__I64_delete(&self->tag_values, hoisted__Bool_2787);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U32 hoisted__U32_2788 = 0;
    (void)hoisted__U32_2788;
    U64 hoisted__U64_2789 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2788); });
    (void)hoisted__U64_2789;
    return hoisted__U64_2789;
    __builtin_unreachable();
}

USize EnumDef_size(void) {
    U32 hoisted__U32_2790 = 128;
    (void)hoisted__U32_2790;
    return hoisted__U32_2790;
    __builtin_unreachable();
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2820 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2820->name = *_ca; free(_ca); }
    hoisted__AssignData_2820->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2820->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2820->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_2820;
    return hoisted__AssignData_2820;
    __builtin_unreachable();
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2821 = 0;
    (void)hoisted__Bool_2821;
    Str_delete(&self->name, hoisted__Bool_2821);
    Bool hoisted__Bool_2822 = 0;
    (void)hoisted__Bool_2822;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2822);
    Bool hoisted__Bool_2823 = 0;
    (void)hoisted__Bool_2823;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2823);
    Bool hoisted__Bool_2824 = 0;
    (void)hoisted__Bool_2824;
    Bool_delete(&self->swap_replace, hoisted__Bool_2824);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_2825 = 0;
    (void)hoisted__U32_2825;
    U64 hoisted__U64_2826 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2825); });
    (void)hoisted__U64_2826;
    return hoisted__U64_2826;
    __builtin_unreachable();
}

USize AssignData_size(void) {
    U32 hoisted__U32_2827 = 24;
    (void)hoisted__U32_2827;
    return hoisted__U32_2827;
    __builtin_unreachable();
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_2829 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_2829->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_2829->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_2829;
    return hoisted__FieldAssignData_2829;
    __builtin_unreachable();
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_2830 = 0;
    (void)hoisted__Bool_2830;
    Str_delete(&self->name, hoisted__Bool_2830);
    Bool hoisted__Bool_2831 = 0;
    (void)hoisted__Bool_2831;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2831);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_2832 = 0;
    (void)hoisted__U32_2832;
    U64 hoisted__U64_2833 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2832); });
    (void)hoisted__U64_2833;
    return hoisted__U64_2833;
    __builtin_unreachable();
}

USize FieldAssignData_size(void) {
    U32 hoisted__U32_2834 = 24;
    (void)hoisted__U32_2834;
    return hoisted__U32_2834;
    __builtin_unreachable();
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_2836 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_2836->name = *_ca; free(_ca); }
    hoisted__ForInData_2836->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_2836->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->name2); hoisted__ForInData_2836->name2 = *_ca; free(_ca); }
    hoisted__ForInData_2836->is_mut2 = self->is_mut2;
    (void)hoisted__ForInData_2836;
    return hoisted__ForInData_2836;
    __builtin_unreachable();
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_2837 = 0;
    (void)hoisted__Bool_2837;
    Str_delete(&self->name, hoisted__Bool_2837);
    Bool hoisted__Bool_2838 = 0;
    (void)hoisted__Bool_2838;
    Bool_delete(&self->is_mut, hoisted__Bool_2838);
    Bool hoisted__Bool_2839 = 0;
    (void)hoisted__Bool_2839;
    Type_delete(&self->til_type, hoisted__Bool_2839);
    Bool hoisted__Bool_2840 = 0;
    (void)hoisted__Bool_2840;
    Str_delete(&self->name2, hoisted__Bool_2840);
    Bool hoisted__Bool_2841 = 0;
    (void)hoisted__Bool_2841;
    Bool_delete(&self->is_mut2, hoisted__Bool_2841);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_2842 = 0;
    (void)hoisted__U32_2842;
    U64 hoisted__U64_2843 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2842); });
    (void)hoisted__U64_2843;
    return hoisted__U64_2843;
    __builtin_unreachable();
}

USize ForInData_size(void) {
    U32 hoisted__U32_2844 = 72;
    (void)hoisted__U32_2844;
    return hoisted__U32_2844;
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
    U32 hoisted__U32_2885 = 1;
    (void)hoisted__U32_2885;
    Bool hoisted__Bool_2886 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Str}))->tag));
    (void)hoisted__Bool_2886;
    if (hoisted__Bool_2886) {
        Str *hoisted__Str_2879 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Str_2879;
        (void)hoisted__Str_2879;
        Bool hoisted__Bool_2880 = 0;
        (void)hoisted__Bool_2880;
        Str_delete(hoisted__Str_2879, hoisted__Bool_2880);
    }
    U32 hoisted__U32_2887 = 1;
    (void)hoisted__U32_2887;
    Bool hoisted__Bool_2888 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Num}))->tag));
    (void)hoisted__Bool_2888;
    if (hoisted__Bool_2888) {
        LiteralNumData *hoisted__LiteralNumData_2881 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__LiteralNumData_2881;
        (void)hoisted__LiteralNumData_2881;
        Bool hoisted__Bool_2882 = 0;
        (void)hoisted__Bool_2882;
        LiteralNumData_delete(hoisted__LiteralNumData_2881, hoisted__Bool_2882);
    }
    U32 hoisted__U32_2889 = 1;
    (void)hoisted__U32_2889;
    Bool hoisted__Bool_2890 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Bool}))->tag));
    (void)hoisted__Bool_2890;
    if (hoisted__Bool_2890) {
        Bool *hoisted__Bool_2883 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Bool_2883;
        (void)hoisted__Bool_2883;
        Bool hoisted__Bool_2884 = 0;
        (void)hoisted__Bool_2884;
        Bool_delete(hoisted__Bool_2883, hoisted__Bool_2884);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    U32 hoisted__U32_2945 = 1;
    (void)hoisted__U32_2945;
    Bool hoisted__Bool_2946 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Str}))->tag));
    (void)hoisted__Bool_2946;
    if (hoisted__Bool_2946) {
        Str *_clone_payload_Str_0 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_2940 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_2940;
        Literal *hoisted__Literal_2941 = Literal_Str(hoisted__Str_2940);
        (void)hoisted__Literal_2941;
        return hoisted__Literal_2941;
    }
    U32 hoisted__U32_2947 = 1;
    (void)hoisted__U32_2947;
    Bool hoisted__Bool_2948 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Num}))->tag));
    (void)hoisted__Bool_2948;
    if (hoisted__Bool_2948) {
        LiteralNumData *_clone_payload_Num_1 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_2942 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_2942;
        Literal *hoisted__Literal_2943 = Literal_Num(hoisted__LiteralNumData_2942);
        (void)hoisted__Literal_2943;
        return hoisted__Literal_2943;
    }
    U32 hoisted__U32_2949 = 1;
    (void)hoisted__U32_2949;
    Bool hoisted__Bool_2950 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Bool}))->tag));
    (void)hoisted__Bool_2950;
    if (hoisted__Bool_2950) {
        Bool *_clone_payload_Bool_2 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_2944 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_2944;
        return hoisted__Literal_2944;
    }
    U32 hoisted__U32_2951 = 1;
    (void)hoisted__U32_2951;
    Bool hoisted__Bool_2952 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Null}))->tag));
    (void)hoisted__Bool_2952;
    if (hoisted__Bool_2952) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
        return _r; }
    }
    U32 hoisted__U32_2953 = 1;
    (void)hoisted__U32_2953;
    Bool hoisted__Bool_2954 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_MapLit}))->tag));
    (void)hoisted__Bool_2954;
    if (hoisted__Bool_2954) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
        return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
    __builtin_unreachable();
}

USize Literal_size(void) {
    U32 hoisted__U32_2955 = 48;
    (void)hoisted__U32_2955;
    return hoisted__U32_2955;
    __builtin_unreachable();
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_2958 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_2958->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_2958->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_2958;
    return hoisted__MatchData_2958;
    __builtin_unreachable();
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_2959 = 0;
    (void)hoisted__Bool_2959;
    Type_delete(&self->til_type, hoisted__Bool_2959);
    Bool hoisted__Bool_2960 = 0;
    (void)hoisted__Bool_2960;
    Str_delete(&self->result_temp, hoisted__Bool_2960);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_2961 = 0;
    (void)hoisted__U32_2961;
    U64 hoisted__U64_2962 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2961); });
    (void)hoisted__U64_2962;
    return hoisted__U64_2962;
    __builtin_unreachable();
}

USize MatchData_size(void) {
    U32 hoisted__U32_2963 = 40;
    (void)hoisted__U32_2963;
    return hoisted__U32_2963;
    __builtin_unreachable();
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_2968 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_2968->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__CaptureBlockData_2968->closure_name = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_2968;
    return hoisted__CaptureBlockData_2968;
    __builtin_unreachable();
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_2969 = 0;
    (void)hoisted__Bool_2969;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2969);
    Bool hoisted__Bool_2970 = 0;
    (void)hoisted__Bool_2970;
    Str_delete(&self->closure_name, hoisted__Bool_2970);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_2971 = 0;
    (void)hoisted__U32_2971;
    U64 hoisted__U64_2972 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2971); });
    (void)hoisted__U64_2972;
    return hoisted__U64_2972;
    __builtin_unreachable();
}

USize CaptureBlockData_size(void) {
    U32 hoisted__U32_2973 = 32;
    (void)hoisted__U32_2973;
    return hoisted__U32_2973;
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
    U32 hoisted__U32_3472 = 1;
    (void)hoisted__U32_3472;
    Bool hoisted__Bool_3473 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Literal}))->tag));
    (void)hoisted__Bool_3473;
    if (hoisted__Bool_3473) {
        Literal *hoisted__Literal_3442 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Literal_3442;
        (void)hoisted__Literal_3442;
        Bool hoisted__Bool_3443 = 0;
        (void)hoisted__Bool_3443;
        Literal_delete(hoisted__Literal_3442, hoisted__Bool_3443);
    }
    U32 hoisted__U32_3474 = 1;
    (void)hoisted__U32_3474;
    Bool hoisted__Bool_3475 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Ident}))->tag));
    (void)hoisted__Bool_3475;
    if (hoisted__Bool_3475) {
        IdentData *hoisted__IdentData_3444 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__IdentData_3444;
        (void)hoisted__IdentData_3444;
        Bool hoisted__Bool_3445 = 0;
        (void)hoisted__Bool_3445;
        IdentData_delete(hoisted__IdentData_3444, hoisted__Bool_3445);
    }
    U32 hoisted__U32_3476 = 1;
    (void)hoisted__U32_3476;
    Bool hoisted__Bool_3477 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Decl}))->tag));
    (void)hoisted__Bool_3477;
    if (hoisted__Bool_3477) {
        Declaration *hoisted__Declaration_3446 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Declaration_3446;
        (void)hoisted__Declaration_3446;
        Bool hoisted__Bool_3447 = 0;
        (void)hoisted__Bool_3447;
        Declaration_delete(hoisted__Declaration_3446, hoisted__Bool_3447);
    }
    U32 hoisted__U32_3478 = 1;
    (void)hoisted__U32_3478;
    Bool hoisted__Bool_3479 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Assign}))->tag));
    (void)hoisted__Bool_3479;
    if (hoisted__Bool_3479) {
        AssignData *hoisted__AssignData_3448 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__AssignData_3448;
        (void)hoisted__AssignData_3448;
        Bool hoisted__Bool_3449 = 0;
        (void)hoisted__Bool_3449;
        AssignData_delete(hoisted__AssignData_3448, hoisted__Bool_3449);
    }
    U32 hoisted__U32_3480 = 1;
    (void)hoisted__U32_3480;
    Bool hoisted__Bool_3481 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FCall}))->tag));
    (void)hoisted__Bool_3481;
    if (hoisted__Bool_3481) {
        FCallData *hoisted__FCallData_3450 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__FCallData_3450;
        (void)hoisted__FCallData_3450;
        Bool hoisted__Bool_3451 = 0;
        (void)hoisted__Bool_3451;
        FCallData_delete(hoisted__FCallData_3450, hoisted__Bool_3451);
    }
    U32 hoisted__U32_3482 = 1;
    (void)hoisted__U32_3482;
    Bool hoisted__Bool_3483 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_3483;
    if (hoisted__Bool_3483) {
        FunctionDef *hoisted__FunctionDef_3452 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__FunctionDef_3452;
        (void)hoisted__FunctionDef_3452;
        Bool hoisted__Bool_3453 = 0;
        (void)hoisted__Bool_3453;
        FunctionDef_delete(hoisted__FunctionDef_3452, hoisted__Bool_3453);
    }
    U32 hoisted__U32_3484 = 1;
    (void)hoisted__U32_3484;
    Bool hoisted__Bool_3485 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_StructDef}))->tag));
    (void)hoisted__Bool_3485;
    if (hoisted__Bool_3485) {
        StructDef *hoisted__StructDef_3454 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__StructDef_3454;
        (void)hoisted__StructDef_3454;
        Bool hoisted__Bool_3455 = 0;
        (void)hoisted__Bool_3455;
        StructDef_delete(hoisted__StructDef_3454, hoisted__Bool_3455);
    }
    U32 hoisted__U32_3486 = 1;
    (void)hoisted__U32_3486;
    Bool hoisted__Bool_3487 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_3487;
    if (hoisted__Bool_3487) {
        EnumDef *hoisted__EnumDef_3456 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__EnumDef_3456;
        (void)hoisted__EnumDef_3456;
        Bool hoisted__Bool_3457 = 0;
        (void)hoisted__Bool_3457;
        EnumDef_delete(hoisted__EnumDef_3456, hoisted__Bool_3457);
    }
    U32 hoisted__U32_3488 = 1;
    (void)hoisted__U32_3488;
    Bool hoisted__Bool_3489 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAccess}))->tag));
    (void)hoisted__Bool_3489;
    if (hoisted__Bool_3489) {
        FieldAccessData *hoisted__FieldAccessData_3458 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__FieldAccessData_3458;
        (void)hoisted__FieldAccessData_3458;
        Bool hoisted__Bool_3459 = 0;
        (void)hoisted__Bool_3459;
        FieldAccessData_delete(hoisted__FieldAccessData_3458, hoisted__Bool_3459);
    }
    U32 hoisted__U32_3490 = 1;
    (void)hoisted__U32_3490;
    Bool hoisted__Bool_3491 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAssign}))->tag));
    (void)hoisted__Bool_3491;
    if (hoisted__Bool_3491) {
        FieldAssignData *hoisted__FieldAssignData_3460 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__FieldAssignData_3460;
        (void)hoisted__FieldAssignData_3460;
        Bool hoisted__Bool_3461 = 0;
        (void)hoisted__Bool_3461;
        FieldAssignData_delete(hoisted__FieldAssignData_3460, hoisted__Bool_3461);
    }
    U32 hoisted__U32_3492 = 1;
    (void)hoisted__U32_3492;
    Bool hoisted__Bool_3493 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_ForIn}))->tag));
    (void)hoisted__Bool_3493;
    if (hoisted__Bool_3493) {
        ForInData *hoisted__ForInData_3462 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__ForInData_3462;
        (void)hoisted__ForInData_3462;
        Bool hoisted__Bool_3463 = 0;
        (void)hoisted__Bool_3463;
        ForInData_delete(hoisted__ForInData_3462, hoisted__Bool_3463);
    }
    U32 hoisted__U32_3494 = 1;
    (void)hoisted__U32_3494;
    Bool hoisted__Bool_3495 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NamedArg}))->tag));
    (void)hoisted__Bool_3495;
    if (hoisted__Bool_3495) {
        Str *hoisted__Str_3464 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Str_3464;
        (void)hoisted__Str_3464;
        Bool hoisted__Bool_3465 = 0;
        (void)hoisted__Bool_3465;
        Str_delete(hoisted__Str_3464, hoisted__Bool_3465);
    }
    U32 hoisted__U32_3496 = 1;
    (void)hoisted__U32_3496;
    Bool hoisted__Bool_3497 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Match}))->tag));
    (void)hoisted__Bool_3497;
    if (hoisted__Bool_3497) {
        MatchData *hoisted__MatchData_3466 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__MatchData_3466;
        (void)hoisted__MatchData_3466;
        Bool hoisted__Bool_3467 = 0;
        (void)hoisted__Bool_3467;
        MatchData_delete(hoisted__MatchData_3466, hoisted__Bool_3467);
    }
    U32 hoisted__U32_3498 = 1;
    (void)hoisted__U32_3498;
    Bool hoisted__Bool_3499 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_CaptureBlock}))->tag));
    (void)hoisted__Bool_3499;
    if (hoisted__Bool_3499) {
        CaptureBlockData *hoisted__CaptureBlockData_3468 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__CaptureBlockData_3468;
        (void)hoisted__CaptureBlockData_3468;
        Bool hoisted__Bool_3469 = 0;
        (void)hoisted__Bool_3469;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3468, hoisted__Bool_3469);
    }
    U32 hoisted__U32_3500 = 1;
    (void)hoisted__U32_3500;
    Bool hoisted__Bool_3501 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_BodyValue}))->tag));
    (void)hoisted__Bool_3501;
    if (hoisted__Bool_3501) {
        CaptureBlockData *hoisted__CaptureBlockData_3470 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__CaptureBlockData_3470;
        (void)hoisted__CaptureBlockData_3470;
        Bool hoisted__Bool_3471 = 0;
        (void)hoisted__Bool_3471;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3470, hoisted__Bool_3471);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    U32 hoisted__U32_3770 = 1;
    (void)hoisted__U32_3770;
    Bool hoisted__Bool_3771 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Body}))->tag));
    (void)hoisted__Bool_3771;
    if (hoisted__Bool_3771) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
        return _r; }
    }
    U32 hoisted__U32_3772 = 1;
    (void)hoisted__U32_3772;
    Bool hoisted__Bool_3773 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Literal}))->tag));
    (void)hoisted__Bool_3773;
    if (hoisted__Bool_3773) {
        Literal *_clone_payload_Literal_1 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3740 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3740;
        NodeType *hoisted__NodeType_3741 = NodeType_Literal(hoisted__Literal_3740);
        (void)hoisted__NodeType_3741;
        return hoisted__NodeType_3741;
    }
    U32 hoisted__U32_3774 = 1;
    (void)hoisted__U32_3774;
    Bool hoisted__Bool_3775 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Ident}))->tag));
    (void)hoisted__Bool_3775;
    if (hoisted__Bool_3775) {
        IdentData *_clone_payload_Ident_2 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3742 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3742;
        NodeType *hoisted__NodeType_3743 = NodeType_Ident(hoisted__IdentData_3742);
        (void)hoisted__NodeType_3743;
        return hoisted__NodeType_3743;
    }
    U32 hoisted__U32_3776 = 1;
    (void)hoisted__U32_3776;
    Bool hoisted__Bool_3777 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Decl}))->tag));
    (void)hoisted__Bool_3777;
    if (hoisted__Bool_3777) {
        Declaration *_clone_payload_Decl_3 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3744 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3744;
        NodeType *hoisted__NodeType_3745 = NodeType_Decl(hoisted__Declaration_3744);
        (void)hoisted__NodeType_3745;
        return hoisted__NodeType_3745;
    }
    U32 hoisted__U32_3778 = 1;
    (void)hoisted__U32_3778;
    Bool hoisted__Bool_3779 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Assign}))->tag));
    (void)hoisted__Bool_3779;
    if (hoisted__Bool_3779) {
        AssignData *_clone_payload_Assign_4 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3746 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3746;
        NodeType *hoisted__NodeType_3747 = NodeType_Assign(hoisted__AssignData_3746);
        (void)hoisted__NodeType_3747;
        return hoisted__NodeType_3747;
    }
    U32 hoisted__U32_3780 = 1;
    (void)hoisted__U32_3780;
    Bool hoisted__Bool_3781 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FCall}))->tag));
    (void)hoisted__Bool_3781;
    if (hoisted__Bool_3781) {
        FCallData *_clone_payload_FCall_5 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3748 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3748;
        NodeType *hoisted__NodeType_3749 = NodeType_FCall(hoisted__FCallData_3748);
        (void)hoisted__NodeType_3749;
        return hoisted__NodeType_3749;
    }
    U32 hoisted__U32_3782 = 1;
    (void)hoisted__U32_3782;
    Bool hoisted__Bool_3783 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_3783;
    if (hoisted__Bool_3783) {
        FunctionDef *_clone_payload_FuncDef_6 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3750 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3750;
        NodeType *hoisted__NodeType_3751 = NodeType_FuncDef(hoisted__FunctionDef_3750);
        (void)hoisted__NodeType_3751;
        return hoisted__NodeType_3751;
    }
    U32 hoisted__U32_3784 = 1;
    (void)hoisted__U32_3784;
    Bool hoisted__Bool_3785 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_StructDef}))->tag));
    (void)hoisted__Bool_3785;
    if (hoisted__Bool_3785) {
        StructDef *_clone_payload_StructDef_7 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3752 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3752;
        NodeType *hoisted__NodeType_3753 = NodeType_StructDef(hoisted__StructDef_3752);
        (void)hoisted__NodeType_3753;
        return hoisted__NodeType_3753;
    }
    U32 hoisted__U32_3786 = 1;
    (void)hoisted__U32_3786;
    Bool hoisted__Bool_3787 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_3787;
    if (hoisted__Bool_3787) {
        EnumDef *_clone_payload_EnumDef_8 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3754 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3754;
        NodeType *hoisted__NodeType_3755 = NodeType_EnumDef(hoisted__EnumDef_3754);
        (void)hoisted__NodeType_3755;
        return hoisted__NodeType_3755;
    }
    U32 hoisted__U32_3788 = 1;
    (void)hoisted__U32_3788;
    Bool hoisted__Bool_3789 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAccess}))->tag));
    (void)hoisted__Bool_3789;
    if (hoisted__Bool_3789) {
        FieldAccessData *_clone_payload_FieldAccess_9 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3756 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3756;
        NodeType *hoisted__NodeType_3757 = NodeType_FieldAccess(hoisted__FieldAccessData_3756);
        (void)hoisted__NodeType_3757;
        return hoisted__NodeType_3757;
    }
    U32 hoisted__U32_3790 = 1;
    (void)hoisted__U32_3790;
    Bool hoisted__Bool_3791 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAssign}))->tag));
    (void)hoisted__Bool_3791;
    if (hoisted__Bool_3791) {
        FieldAssignData *_clone_payload_FieldAssign_10 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3758 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3758;
        NodeType *hoisted__NodeType_3759 = NodeType_FieldAssign(hoisted__FieldAssignData_3758);
        (void)hoisted__NodeType_3759;
        return hoisted__NodeType_3759;
    }
    U32 hoisted__U32_3792 = 1;
    (void)hoisted__U32_3792;
    Bool hoisted__Bool_3793 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Return}))->tag));
    (void)hoisted__Bool_3793;
    if (hoisted__Bool_3793) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
        return _r; }
    }
    U32 hoisted__U32_3794 = 1;
    (void)hoisted__U32_3794;
    Bool hoisted__Bool_3795 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_If}))->tag));
    (void)hoisted__Bool_3795;
    if (hoisted__Bool_3795) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
        return _r; }
    }
    U32 hoisted__U32_3796 = 1;
    (void)hoisted__U32_3796;
    Bool hoisted__Bool_3797 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_While}))->tag));
    (void)hoisted__Bool_3797;
    if (hoisted__Bool_3797) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
        return _r; }
    }
    U32 hoisted__U32_3798 = 1;
    (void)hoisted__U32_3798;
    Bool hoisted__Bool_3799 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_ForIn}))->tag));
    (void)hoisted__Bool_3799;
    if (hoisted__Bool_3799) {
        ForInData *_clone_payload_ForIn_14 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3760 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3760;
        NodeType *hoisted__NodeType_3761 = NodeType_ForIn(hoisted__ForInData_3760);
        (void)hoisted__NodeType_3761;
        return hoisted__NodeType_3761;
    }
    U32 hoisted__U32_3800 = 1;
    (void)hoisted__U32_3800;
    Bool hoisted__Bool_3801 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NamedArg}))->tag));
    (void)hoisted__Bool_3801;
    if (hoisted__Bool_3801) {
        Str *_clone_payload_NamedArg_15 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3762 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3762;
        NodeType *hoisted__NodeType_3763 = NodeType_NamedArg(hoisted__Str_3762);
        (void)hoisted__NodeType_3763;
        return hoisted__NodeType_3763;
    }
    U32 hoisted__U32_3802 = 1;
    (void)hoisted__U32_3802;
    Bool hoisted__Bool_3803 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Break}))->tag));
    (void)hoisted__Bool_3803;
    if (hoisted__Bool_3803) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
        return _r; }
    }
    U32 hoisted__U32_3804 = 1;
    (void)hoisted__U32_3804;
    Bool hoisted__Bool_3805 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Continue}))->tag));
    (void)hoisted__Bool_3805;
    if (hoisted__Bool_3805) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
        return _r; }
    }
    U32 hoisted__U32_3806 = 1;
    (void)hoisted__U32_3806;
    Bool hoisted__Bool_3807 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Switch}))->tag));
    (void)hoisted__Bool_3807;
    if (hoisted__Bool_3807) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
        return _r; }
    }
    U32 hoisted__U32_3808 = 1;
    (void)hoisted__U32_3808;
    Bool hoisted__Bool_3809 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Match}))->tag));
    (void)hoisted__Bool_3809;
    if (hoisted__Bool_3809) {
        MatchData *_clone_payload_Match_19 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3764 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3764;
        NodeType *hoisted__NodeType_3765 = NodeType_Match(hoisted__MatchData_3764);
        (void)hoisted__NodeType_3765;
        return hoisted__NodeType_3765;
    }
    U32 hoisted__U32_3810 = 1;
    (void)hoisted__U32_3810;
    Bool hoisted__Bool_3811 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Case}))->tag));
    (void)hoisted__Bool_3811;
    if (hoisted__Bool_3811) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
        return _r; }
    }
    U32 hoisted__U32_3812 = 1;
    (void)hoisted__U32_3812;
    Bool hoisted__Bool_3813 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NoDefaultArg}))->tag));
    (void)hoisted__Bool_3813;
    if (hoisted__Bool_3813) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
        return _r; }
    }
    U32 hoisted__U32_3814 = 1;
    (void)hoisted__U32_3814;
    Bool hoisted__Bool_3815 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Throw}))->tag));
    (void)hoisted__Bool_3815;
    if (hoisted__Bool_3815) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
        return _r; }
    }
    U32 hoisted__U32_3816 = 1;
    (void)hoisted__U32_3816;
    Bool hoisted__Bool_3817 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Catch}))->tag));
    (void)hoisted__Bool_3817;
    if (hoisted__Bool_3817) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
        return _r; }
    }
    U32 hoisted__U32_3818 = 1;
    (void)hoisted__U32_3818;
    Bool hoisted__Bool_3819 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_RestPattern}))->tag));
    (void)hoisted__Bool_3819;
    if (hoisted__Bool_3819) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
        return _r; }
    }
    U32 hoisted__U32_3820 = 1;
    (void)hoisted__U32_3820;
    Bool hoisted__Bool_3821 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_CaptureBlock}))->tag));
    (void)hoisted__Bool_3821;
    if (hoisted__Bool_3821) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3766 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3766;
        NodeType *hoisted__NodeType_3767 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3766);
        (void)hoisted__NodeType_3767;
        return hoisted__NodeType_3767;
    }
    U32 hoisted__U32_3822 = 1;
    (void)hoisted__U32_3822;
    Bool hoisted__Bool_3823 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Loc}))->tag));
    (void)hoisted__Bool_3823;
    if (hoisted__Bool_3823) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
        return _r; }
    }
    U32 hoisted__U32_3824 = 1;
    (void)hoisted__U32_3824;
    Bool hoisted__Bool_3825 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_BodyValue}))->tag));
    (void)hoisted__Bool_3825;
    if (hoisted__Bool_3825) {
        CaptureBlockData *_clone_payload_BodyValue_27 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_BodyValue_27;
        (void)_clone_payload_BodyValue_27;
        CaptureBlockData *hoisted__CaptureBlockData_3768 = CaptureBlockData_clone(_clone_payload_BodyValue_27);
        (void)hoisted__CaptureBlockData_3768;
        NodeType *hoisted__NodeType_3769 = NodeType_BodyValue(hoisted__CaptureBlockData_3768);
        (void)hoisted__NodeType_3769;
        return hoisted__NodeType_3769;
    }
    { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_ListPattern;
    return _r; }
    __builtin_unreachable();
}

USize NodeType_size(void) {
    U32 hoisted__U32_3826 = 136;
    (void)hoisted__U32_3826;
    return hoisted__U32_3826;
    __builtin_unreachable();
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3827 = ((Bool)((UPtr)(self) == 0));
    (void)hoisted__Bool_3827;
    if (hoisted__Bool_3827) {
        return;
    }
    Bool hoisted__Bool_3828 = 0;
    (void)hoisted__Bool_3828;
    NodeType_delete(&self->node_type, hoisted__Bool_3828);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3875 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3875->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3875->children = *_ca; free(_ca); }
    hoisted__Expr_3875->line = line;
    hoisted__Expr_3875->col = col;
    (void)hoisted__Expr_3875;
    return hoisted__Expr_3875;
    __builtin_unreachable();
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_4177 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_4177->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_4177->children = *_ca; free(_ca); }
    hoisted__Expr_4177->line = self->line;
    hoisted__Expr_4177->col = self->col;
    (void)hoisted__Expr_4177;
    return hoisted__Expr_4177;
    __builtin_unreachable();
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_4178 = 0;
    (void)hoisted__U32_4178;
    U64 hoisted__U64_4179 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_4178); });
    (void)hoisted__U64_4179;
    return hoisted__U64_4179;
    __builtin_unreachable();
}

USize Expr_size(void) {
    U32 hoisted__U32_4180 = 160;
    (void)hoisted__U32_4180;
    return hoisted__U32_4180;
    __builtin_unreachable();
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_4181 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_4181->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_4181->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4181;
    return hoisted__Map__I64_Str_4181;
    __builtin_unreachable();
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_4280 = 0;
    (void)hoisted__Bool_4280;
    Vec__I64_delete(&self->keys, hoisted__Bool_4280);
    Bool hoisted__Bool_4281 = 0;
    (void)hoisted__Bool_4281;
    Vec__Str_delete(&self->values, hoisted__Bool_4281);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_4282 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_4282->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_4282->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4282;
    return hoisted__Map__I64_Str_4282;
    __builtin_unreachable();
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U32 hoisted__U32_4283 = 0;
    (void)hoisted__U32_4283;
    U64 hoisted__U64_4284 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_4283); });
    (void)hoisted__U64_4284;
    return hoisted__U64_4284;
    __builtin_unreachable();
}

USize Map__I64_Str_size(void) {
    U32 hoisted__U32_4285 = 32;
    (void)hoisted__U32_4285;
    return hoisted__U32_4285;
    __builtin_unreachable();
}

Vec__Bool * Vec__Bool_new(void) {
    U64 hoisted__U64_4286 = 1ULL;
    (void)hoisted__U64_4286;
    void * hoisted__v_4287 = malloc(hoisted__U64_4286);
    (void)hoisted__v_4287;
    U32 hoisted__U32_4288 = 0;
    (void)hoisted__U32_4288;
    I64 hoisted__I64_4289 = 1;
    (void)hoisted__I64_4289;
    Vec__Bool *hoisted__Vec__Bool_4290 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4290->data = hoisted__v_4287;
    hoisted__Vec__Bool_4290->count = hoisted__U32_4288;
    hoisted__Vec__Bool_4290->cap = hoisted__I64_4289;
    (void)hoisted__Vec__Bool_4290;
    return hoisted__Vec__Bool_4290;
    __builtin_unreachable();
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U32 _re_U32_4299 = self->count;
        (void)_re_U32_4299;
        U32 _rc_U32_4299 = 0;
        (void)_rc_U32_4299;
        Bool hoisted__Bool_4310 = ((Bool)(_rc_U32_4299 <= _re_U32_4299));
        (void)hoisted__Bool_4310;
        if (hoisted__Bool_4310) {
            while (1) {
                Bool _wcond_Bool_4300 = ((Bool)(_rc_U32_4299 < _re_U32_4299));
                (void)_wcond_Bool_4300;
                if (_wcond_Bool_4300) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4299);
                (++_rc_U32_4299);
                U32 hoisted__U32_4301 = 1;
                (void)hoisted__U32_4301;
                U32 hoisted__U64_4302 = ((U64)(i * hoisted__U32_4301));
                (void)hoisted__U64_4302;
                Bool *hoisted__Bool_4303 = ((void *)((U8 *)(self->data) + (hoisted__U64_4302)));
                (void)hoisted__Bool_4303;
                (void)hoisted__Bool_4303;
                Bool hoisted__Bool_4304 = 0;
                (void)hoisted__Bool_4304;
                Bool_delete(hoisted__Bool_4303, hoisted__Bool_4304);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4305 = ((Bool)(_rc_U32_4299 > _re_U32_4299));
                (void)_wcond_Bool_4305;
                if (_wcond_Bool_4305) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4299);
                (--_rc_U32_4299);
                U32 hoisted__U32_4306 = 1;
                (void)hoisted__U32_4306;
                U32 hoisted__U64_4307 = ((U64)(i * hoisted__U32_4306));
                (void)hoisted__U64_4307;
                Bool *hoisted__Bool_4308 = ((void *)((U8 *)(self->data) + (hoisted__U64_4307)));
                (void)hoisted__Bool_4308;
                (void)hoisted__Bool_4308;
                Bool hoisted__Bool_4309 = 0;
                (void)hoisted__Bool_4309;
                Bool_delete(hoisted__Bool_4308, hoisted__Bool_4309);
            }
        }
    }
    U32 hoisted__U32_4311 = 0;
    (void)hoisted__U32_4311;
    self->count = hoisted__U32_4311;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U32 hoisted__U32_4542 = 1;
    (void)hoisted__U32_4542;
    U32 hoisted__U64_4543 = ((U64)(self->cap * hoisted__U32_4542));
    (void)hoisted__U64_4543;
    U8 *new_data = malloc(hoisted__U64_4543);
    {
        U32 _re_U32_4522 = self->count;
        (void)_re_U32_4522;
        U32 _rc_U32_4522 = 0;
        (void)_rc_U32_4522;
        Bool hoisted__Bool_4541 = ((Bool)(_rc_U32_4522 <= _re_U32_4522));
        (void)hoisted__Bool_4541;
        if (hoisted__Bool_4541) {
            while (1) {
                Bool _wcond_Bool_4523 = ((Bool)(_rc_U32_4522 < _re_U32_4522));
                (void)_wcond_Bool_4523;
                if (_wcond_Bool_4523) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4522);
                (++_rc_U32_4522);
                U32 hoisted__U32_4524 = 1;
                (void)hoisted__U32_4524;
                U32 hoisted__U64_4525 = ((U64)(i * hoisted__U32_4524));
                (void)hoisted__U64_4525;
                Bool *src = ((void *)((U8 *)(self->data) + (hoisted__U64_4525)));
                Bool cloned = (DEREF(src));
                U32 hoisted__U32_4526 = 1;
                (void)hoisted__U32_4526;
                U32 hoisted__U64_4527 = ((U64)(i * hoisted__U32_4526));
                (void)hoisted__U64_4527;
                void *hoisted__v_4528 = ((void *)((U8 *)(new_data) + (hoisted__U64_4527)));
                (void)hoisted__v_4528;
                (void)hoisted__v_4528;
                U64 hoisted__U64_4529 = 1ULL;
                (void)hoisted__U64_4529;
                memcpy(hoisted__v_4528, &cloned, hoisted__U64_4529);
                I32 hoisted__I32_4530 = 0;
                (void)hoisted__I32_4530;
                U64 hoisted__U64_4531 = 1ULL;
                (void)hoisted__U64_4531;
                memset(&cloned, hoisted__I32_4530, hoisted__U64_4531);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4532 = ((Bool)(_rc_U32_4522 > _re_U32_4522));
                (void)_wcond_Bool_4532;
                if (_wcond_Bool_4532) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4522);
                (--_rc_U32_4522);
                U32 hoisted__U32_4533 = 1;
                (void)hoisted__U32_4533;
                U32 hoisted__U64_4534 = ((U64)(i * hoisted__U32_4533));
                (void)hoisted__U64_4534;
                Bool *src = ((void *)((U8 *)(self->data) + (hoisted__U64_4534)));
                Bool cloned = (DEREF(src));
                U32 hoisted__U32_4535 = 1;
                (void)hoisted__U32_4535;
                U32 hoisted__U64_4536 = ((U64)(i * hoisted__U32_4535));
                (void)hoisted__U64_4536;
                void *hoisted__v_4537 = ((void *)((U8 *)(new_data) + (hoisted__U64_4536)));
                (void)hoisted__v_4537;
                (void)hoisted__v_4537;
                U64 hoisted__U64_4538 = 1ULL;
                (void)hoisted__U64_4538;
                memcpy(hoisted__v_4537, &cloned, hoisted__U64_4538);
                I32 hoisted__I32_4539 = 0;
                (void)hoisted__I32_4539;
                U64 hoisted__U64_4540 = 1ULL;
                (void)hoisted__U64_4540;
                memset(&cloned, hoisted__I32_4539, hoisted__U64_4540);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_4544 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4544->data = new_data;
    hoisted__Vec__Bool_4544->count = self->count;
    hoisted__Vec__Bool_4544->cap = self->cap;
    (void)hoisted__Vec__Bool_4544;
    return hoisted__Vec__Bool_4544;
    __builtin_unreachable();
}

USize Vec__Bool_size(void) {
    U32 hoisted__U32_4545 = 16;
    (void)hoisted__U32_4545;
    return hoisted__U32_4545;
    __builtin_unreachable();
}

Vec__I64 * Vec__I64_new(void) {
    U64 hoisted__U64_4546 = 8ULL;
    (void)hoisted__U64_4546;
    void * hoisted__v_4547 = malloc(hoisted__U64_4546);
    (void)hoisted__v_4547;
    U32 hoisted__U32_4548 = 0;
    (void)hoisted__U32_4548;
    I64 hoisted__I64_4549 = 1;
    (void)hoisted__I64_4549;
    Vec__I64 *hoisted__Vec__I64_4550 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_4550->data = hoisted__v_4547;
    hoisted__Vec__I64_4550->count = hoisted__U32_4548;
    hoisted__Vec__I64_4550->cap = hoisted__I64_4549;
    (void)hoisted__Vec__I64_4550;
    return hoisted__Vec__I64_4550;
    __builtin_unreachable();
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U32 _re_U32_4559 = self->count;
        (void)_re_U32_4559;
        U32 _rc_U32_4559 = 0;
        (void)_rc_U32_4559;
        Bool hoisted__Bool_4570 = ((Bool)(_rc_U32_4559 <= _re_U32_4559));
        (void)hoisted__Bool_4570;
        if (hoisted__Bool_4570) {
            while (1) {
                Bool _wcond_Bool_4560 = ((Bool)(_rc_U32_4559 < _re_U32_4559));
                (void)_wcond_Bool_4560;
                if (_wcond_Bool_4560) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4559);
                (++_rc_U32_4559);
                U32 hoisted__U32_4561 = 8;
                (void)hoisted__U32_4561;
                U32 hoisted__U64_4562 = ((U64)(i * hoisted__U32_4561));
                (void)hoisted__U64_4562;
                I64 *hoisted__I64_4563 = ((void *)((U8 *)(self->data) + (hoisted__U64_4562)));
                (void)hoisted__I64_4563;
                (void)hoisted__I64_4563;
                Bool hoisted__Bool_4564 = 0;
                (void)hoisted__Bool_4564;
                I64_delete(hoisted__I64_4563, hoisted__Bool_4564);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4565 = ((Bool)(_rc_U32_4559 > _re_U32_4559));
                (void)_wcond_Bool_4565;
                if (_wcond_Bool_4565) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4559);
                (--_rc_U32_4559);
                U32 hoisted__U32_4566 = 8;
                (void)hoisted__U32_4566;
                U32 hoisted__U64_4567 = ((U64)(i * hoisted__U32_4566));
                (void)hoisted__U64_4567;
                I64 *hoisted__I64_4568 = ((void *)((U8 *)(self->data) + (hoisted__U64_4567)));
                (void)hoisted__I64_4568;
                (void)hoisted__I64_4568;
                Bool hoisted__Bool_4569 = 0;
                (void)hoisted__Bool_4569;
                I64_delete(hoisted__I64_4568, hoisted__Bool_4569);
            }
        }
    }
    U32 hoisted__U32_4571 = 0;
    (void)hoisted__U32_4571;
    self->count = hoisted__U32_4571;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_4802 = 8;
    (void)hoisted__U32_4802;
    U32 hoisted__U64_4803 = ((U64)(self->cap * hoisted__U32_4802));
    (void)hoisted__U64_4803;
    U8 *new_data = malloc(hoisted__U64_4803);
    {
        U32 _re_U32_4782 = self->count;
        (void)_re_U32_4782;
        U32 _rc_U32_4782 = 0;
        (void)_rc_U32_4782;
        Bool hoisted__Bool_4801 = ((Bool)(_rc_U32_4782 <= _re_U32_4782));
        (void)hoisted__Bool_4801;
        if (hoisted__Bool_4801) {
            while (1) {
                Bool _wcond_Bool_4783 = ((Bool)(_rc_U32_4782 < _re_U32_4782));
                (void)_wcond_Bool_4783;
                if (_wcond_Bool_4783) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4782);
                (++_rc_U32_4782);
                U32 hoisted__U32_4784 = 8;
                (void)hoisted__U32_4784;
                U32 hoisted__U64_4785 = ((U64)(i * hoisted__U32_4784));
                (void)hoisted__U64_4785;
                I64 *src = ((void *)((U8 *)(self->data) + (hoisted__U64_4785)));
                I64 cloned = (DEREF(src));
                U32 hoisted__U32_4786 = 8;
                (void)hoisted__U32_4786;
                U32 hoisted__U64_4787 = ((U64)(i * hoisted__U32_4786));
                (void)hoisted__U64_4787;
                void *hoisted__v_4788 = ((void *)((U8 *)(new_data) + (hoisted__U64_4787)));
                (void)hoisted__v_4788;
                (void)hoisted__v_4788;
                U64 hoisted__U64_4789 = 8ULL;
                (void)hoisted__U64_4789;
                memcpy(hoisted__v_4788, &cloned, hoisted__U64_4789);
                I32 hoisted__I32_4790 = 0;
                (void)hoisted__I32_4790;
                U64 hoisted__U64_4791 = 8ULL;
                (void)hoisted__U64_4791;
                memset(&cloned, hoisted__I32_4790, hoisted__U64_4791);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4792 = ((Bool)(_rc_U32_4782 > _re_U32_4782));
                (void)_wcond_Bool_4792;
                if (_wcond_Bool_4792) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4782);
                (--_rc_U32_4782);
                U32 hoisted__U32_4793 = 8;
                (void)hoisted__U32_4793;
                U32 hoisted__U64_4794 = ((U64)(i * hoisted__U32_4793));
                (void)hoisted__U64_4794;
                I64 *src = ((void *)((U8 *)(self->data) + (hoisted__U64_4794)));
                I64 cloned = (DEREF(src));
                U32 hoisted__U32_4795 = 8;
                (void)hoisted__U32_4795;
                U32 hoisted__U64_4796 = ((U64)(i * hoisted__U32_4795));
                (void)hoisted__U64_4796;
                void *hoisted__v_4797 = ((void *)((U8 *)(new_data) + (hoisted__U64_4796)));
                (void)hoisted__v_4797;
                (void)hoisted__v_4797;
                U64 hoisted__U64_4798 = 8ULL;
                (void)hoisted__U64_4798;
                memcpy(hoisted__v_4797, &cloned, hoisted__U64_4798);
                I32 hoisted__I32_4799 = 0;
                (void)hoisted__I32_4799;
                U64 hoisted__U64_4800 = 8ULL;
                (void)hoisted__U64_4800;
                memset(&cloned, hoisted__I32_4799, hoisted__U64_4800);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_4804 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_4804->data = new_data;
    hoisted__Vec__I64_4804->count = self->count;
    hoisted__Vec__I64_4804->cap = self->cap;
    (void)hoisted__Vec__I64_4804;
    return hoisted__Vec__I64_4804;
    __builtin_unreachable();
}

USize Vec__I64_size(void) {
    U32 hoisted__U32_4805 = 16;
    (void)hoisted__U32_4805;
    return hoisted__U32_4805;
    __builtin_unreachable();
}

Vec__Declaration * Vec__Declaration_new(void) {
    U64 hoisted__U64_5066 = 112ULL;
    (void)hoisted__U64_5066;
    void * hoisted__v_5067 = malloc(hoisted__U64_5066);
    (void)hoisted__v_5067;
    U32 hoisted__U32_5068 = 0;
    (void)hoisted__U32_5068;
    I64 hoisted__I64_5069 = 1;
    (void)hoisted__I64_5069;
    Vec__Declaration *hoisted__Vec__Declaration_5070 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5070->data = hoisted__v_5067;
    hoisted__Vec__Declaration_5070->count = hoisted__U32_5068;
    hoisted__Vec__Declaration_5070->cap = hoisted__I64_5069;
    (void)hoisted__Vec__Declaration_5070;
    return hoisted__Vec__Declaration_5070;
    __builtin_unreachable();
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_5079 = self->count;
        (void)_re_U32_5079;
        U32 _rc_U32_5079 = 0;
        (void)_rc_U32_5079;
        Bool hoisted__Bool_5090 = ((Bool)(_rc_U32_5079 <= _re_U32_5079));
        (void)hoisted__Bool_5090;
        if (hoisted__Bool_5090) {
            while (1) {
                Bool _wcond_Bool_5080 = ((Bool)(_rc_U32_5079 < _re_U32_5079));
                (void)_wcond_Bool_5080;
                if (_wcond_Bool_5080) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5079);
                (++_rc_U32_5079);
                U32 hoisted__U32_5081 = 112;
                (void)hoisted__U32_5081;
                U32 hoisted__U64_5082 = ((U64)(i * hoisted__U32_5081));
                (void)hoisted__U64_5082;
                Declaration *hoisted__Declaration_5083 = ((void *)((U8 *)(self->data) + (hoisted__U64_5082)));
                (void)hoisted__Declaration_5083;
                (void)hoisted__Declaration_5083;
                Bool hoisted__Bool_5084 = 0;
                (void)hoisted__Bool_5084;
                Declaration_delete(hoisted__Declaration_5083, hoisted__Bool_5084);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5085 = ((Bool)(_rc_U32_5079 > _re_U32_5079));
                (void)_wcond_Bool_5085;
                if (_wcond_Bool_5085) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5079);
                (--_rc_U32_5079);
                U32 hoisted__U32_5086 = 112;
                (void)hoisted__U32_5086;
                U32 hoisted__U64_5087 = ((U64)(i * hoisted__U32_5086));
                (void)hoisted__U64_5087;
                Declaration *hoisted__Declaration_5088 = ((void *)((U8 *)(self->data) + (hoisted__U64_5087)));
                (void)hoisted__Declaration_5088;
                (void)hoisted__Declaration_5088;
                Bool hoisted__Bool_5089 = 0;
                (void)hoisted__Bool_5089;
                Declaration_delete(hoisted__Declaration_5088, hoisted__Bool_5089);
            }
        }
    }
    U32 hoisted__U32_5091 = 0;
    (void)hoisted__U32_5091;
    self->count = hoisted__U32_5091;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U32 hoisted__U32_5322 = 112;
    (void)hoisted__U32_5322;
    U32 hoisted__U64_5323 = ((U64)(self->cap * hoisted__U32_5322));
    (void)hoisted__U64_5323;
    U8 *new_data = malloc(hoisted__U64_5323);
    {
        U32 _re_U32_5302 = self->count;
        (void)_re_U32_5302;
        U32 _rc_U32_5302 = 0;
        (void)_rc_U32_5302;
        Bool hoisted__Bool_5321 = ((Bool)(_rc_U32_5302 <= _re_U32_5302));
        (void)hoisted__Bool_5321;
        if (hoisted__Bool_5321) {
            while (1) {
                Bool _wcond_Bool_5303 = ((Bool)(_rc_U32_5302 < _re_U32_5302));
                (void)_wcond_Bool_5303;
                if (_wcond_Bool_5303) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5302);
                (++_rc_U32_5302);
                U32 hoisted__U32_5304 = 112;
                (void)hoisted__U32_5304;
                U32 hoisted__U64_5305 = ((U64)(i * hoisted__U32_5304));
                (void)hoisted__U64_5305;
                Declaration *src = ((void *)((U8 *)(self->data) + (hoisted__U64_5305)));
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5306 = 112;
                (void)hoisted__U32_5306;
                U32 hoisted__U64_5307 = ((U64)(i * hoisted__U32_5306));
                (void)hoisted__U64_5307;
                void *hoisted__v_5308 = ((void *)((U8 *)(new_data) + (hoisted__U64_5307)));
                (void)hoisted__v_5308;
                (void)hoisted__v_5308;
                U64 hoisted__U64_5309 = 112ULL;
                (void)hoisted__U64_5309;
                memcpy(hoisted__v_5308, cloned, hoisted__U64_5309);
                I32 hoisted__I32_5310 = 0;
                (void)hoisted__I32_5310;
                U64 hoisted__U64_5311 = 112ULL;
                (void)hoisted__U64_5311;
                memset(cloned, hoisted__I32_5310, hoisted__U64_5311);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5312 = ((Bool)(_rc_U32_5302 > _re_U32_5302));
                (void)_wcond_Bool_5312;
                if (_wcond_Bool_5312) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5302);
                (--_rc_U32_5302);
                U32 hoisted__U32_5313 = 112;
                (void)hoisted__U32_5313;
                U32 hoisted__U64_5314 = ((U64)(i * hoisted__U32_5313));
                (void)hoisted__U64_5314;
                Declaration *src = ((void *)((U8 *)(self->data) + (hoisted__U64_5314)));
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5315 = 112;
                (void)hoisted__U32_5315;
                U32 hoisted__U64_5316 = ((U64)(i * hoisted__U32_5315));
                (void)hoisted__U64_5316;
                void *hoisted__v_5317 = ((void *)((U8 *)(new_data) + (hoisted__U64_5316)));
                (void)hoisted__v_5317;
                (void)hoisted__v_5317;
                U64 hoisted__U64_5318 = 112ULL;
                (void)hoisted__U64_5318;
                memcpy(hoisted__v_5317, cloned, hoisted__U64_5318);
                I32 hoisted__I32_5319 = 0;
                (void)hoisted__I32_5319;
                U64 hoisted__U64_5320 = 112ULL;
                (void)hoisted__U64_5320;
                memset(cloned, hoisted__I32_5319, hoisted__U64_5320);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_5324 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5324->data = new_data;
    hoisted__Vec__Declaration_5324->count = self->count;
    hoisted__Vec__Declaration_5324->cap = self->cap;
    (void)hoisted__Vec__Declaration_5324;
    return hoisted__Vec__Declaration_5324;
    __builtin_unreachable();
}

USize Vec__Declaration_size(void) {
    U32 hoisted__U32_5325 = 16;
    (void)hoisted__U32_5325;
    return hoisted__U32_5325;
    __builtin_unreachable();
}

Vec__Expr * Vec__Expr_new(void) {
    U64 hoisted__U64_5326 = 160ULL;
    (void)hoisted__U64_5326;
    void * hoisted__v_5327 = malloc(hoisted__U64_5326);
    (void)hoisted__v_5327;
    U32 hoisted__U32_5328 = 0;
    (void)hoisted__U32_5328;
    I64 hoisted__I64_5329 = 1;
    (void)hoisted__I64_5329;
    Vec__Expr *hoisted__Vec__Expr_5330 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5330->data = hoisted__v_5327;
    hoisted__Vec__Expr_5330->count = hoisted__U32_5328;
    hoisted__Vec__Expr_5330->cap = hoisted__I64_5329;
    (void)hoisted__Vec__Expr_5330;
    return hoisted__Vec__Expr_5330;
    __builtin_unreachable();
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_5339 = self->count;
        (void)_re_U32_5339;
        U32 _rc_U32_5339 = 0;
        (void)_rc_U32_5339;
        Bool hoisted__Bool_5350 = ((Bool)(_rc_U32_5339 <= _re_U32_5339));
        (void)hoisted__Bool_5350;
        if (hoisted__Bool_5350) {
            while (1) {
                Bool _wcond_Bool_5340 = ((Bool)(_rc_U32_5339 < _re_U32_5339));
                (void)_wcond_Bool_5340;
                if (_wcond_Bool_5340) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5339);
                (++_rc_U32_5339);
                U32 hoisted__U32_5341 = 160;
                (void)hoisted__U32_5341;
                U32 hoisted__U64_5342 = ((U64)(i * hoisted__U32_5341));
                (void)hoisted__U64_5342;
                Expr *hoisted__Expr_5343 = ((void *)((U8 *)(self->data) + (hoisted__U64_5342)));
                (void)hoisted__Expr_5343;
                (void)hoisted__Expr_5343;
                Bool hoisted__Bool_5344 = 0;
                (void)hoisted__Bool_5344;
                Expr_delete(hoisted__Expr_5343, hoisted__Bool_5344);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5345 = ((Bool)(_rc_U32_5339 > _re_U32_5339));
                (void)_wcond_Bool_5345;
                if (_wcond_Bool_5345) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5339);
                (--_rc_U32_5339);
                U32 hoisted__U32_5346 = 160;
                (void)hoisted__U32_5346;
                U32 hoisted__U64_5347 = ((U64)(i * hoisted__U32_5346));
                (void)hoisted__U64_5347;
                Expr *hoisted__Expr_5348 = ((void *)((U8 *)(self->data) + (hoisted__U64_5347)));
                (void)hoisted__Expr_5348;
                (void)hoisted__Expr_5348;
                Bool hoisted__Bool_5349 = 0;
                (void)hoisted__Bool_5349;
                Expr_delete(hoisted__Expr_5348, hoisted__Bool_5349);
            }
        }
    }
    U32 hoisted__U32_5351 = 0;
    (void)hoisted__U32_5351;
    self->count = hoisted__U32_5351;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_5582 = 160;
    (void)hoisted__U32_5582;
    U32 hoisted__U64_5583 = ((U64)(self->cap * hoisted__U32_5582));
    (void)hoisted__U64_5583;
    U8 *new_data = malloc(hoisted__U64_5583);
    {
        U32 _re_U32_5562 = self->count;
        (void)_re_U32_5562;
        U32 _rc_U32_5562 = 0;
        (void)_rc_U32_5562;
        Bool hoisted__Bool_5581 = ((Bool)(_rc_U32_5562 <= _re_U32_5562));
        (void)hoisted__Bool_5581;
        if (hoisted__Bool_5581) {
            while (1) {
                Bool _wcond_Bool_5563 = ((Bool)(_rc_U32_5562 < _re_U32_5562));
                (void)_wcond_Bool_5563;
                if (_wcond_Bool_5563) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5562);
                (++_rc_U32_5562);
                U32 hoisted__U32_5564 = 160;
                (void)hoisted__U32_5564;
                U32 hoisted__U64_5565 = ((U64)(i * hoisted__U32_5564));
                (void)hoisted__U64_5565;
                Expr *src = ((void *)((U8 *)(self->data) + (hoisted__U64_5565)));
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5566 = 160;
                (void)hoisted__U32_5566;
                U32 hoisted__U64_5567 = ((U64)(i * hoisted__U32_5566));
                (void)hoisted__U64_5567;
                void *hoisted__v_5568 = ((void *)((U8 *)(new_data) + (hoisted__U64_5567)));
                (void)hoisted__v_5568;
                (void)hoisted__v_5568;
                U64 hoisted__U64_5569 = 160ULL;
                (void)hoisted__U64_5569;
                memcpy(hoisted__v_5568, cloned, hoisted__U64_5569);
                I32 hoisted__I32_5570 = 0;
                (void)hoisted__I32_5570;
                U64 hoisted__U64_5571 = 160ULL;
                (void)hoisted__U64_5571;
                memset(cloned, hoisted__I32_5570, hoisted__U64_5571);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5572 = ((Bool)(_rc_U32_5562 > _re_U32_5562));
                (void)_wcond_Bool_5572;
                if (_wcond_Bool_5572) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5562);
                (--_rc_U32_5562);
                U32 hoisted__U32_5573 = 160;
                (void)hoisted__U32_5573;
                U32 hoisted__U64_5574 = ((U64)(i * hoisted__U32_5573));
                (void)hoisted__U64_5574;
                Expr *src = ((void *)((U8 *)(self->data) + (hoisted__U64_5574)));
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5575 = 160;
                (void)hoisted__U32_5575;
                U32 hoisted__U64_5576 = ((U64)(i * hoisted__U32_5575));
                (void)hoisted__U64_5576;
                void *hoisted__v_5577 = ((void *)((U8 *)(new_data) + (hoisted__U64_5576)));
                (void)hoisted__v_5577;
                (void)hoisted__v_5577;
                U64 hoisted__U64_5578 = 160ULL;
                (void)hoisted__U64_5578;
                memcpy(hoisted__v_5577, cloned, hoisted__U64_5578);
                I32 hoisted__I32_5579 = 0;
                (void)hoisted__I32_5579;
                U64 hoisted__U64_5580 = 160ULL;
                (void)hoisted__U64_5580;
                memset(cloned, hoisted__I32_5579, hoisted__U64_5580);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_5584 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5584->data = new_data;
    hoisted__Vec__Expr_5584->count = self->count;
    hoisted__Vec__Expr_5584->cap = self->cap;
    (void)hoisted__Vec__Expr_5584;
    return hoisted__Vec__Expr_5584;
    __builtin_unreachable();
}

USize Vec__Expr_size(void) {
    U32 hoisted__U32_5585 = 16;
    (void)hoisted__U32_5585;
    return hoisted__U32_5585;
    __builtin_unreachable();
}

void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_6475 = 3;
    (void)hoisted__U32_6475;
    Array__Str *_va_Array_161 = Array__Str_new(hoisted__U32_6475);
    (void)_va_Array_161;
    I64 _va_Array_161_ek = 0;
    (void)_va_Array_161_ek;
    OutOfBounds *_va_Array_161_eo = malloc(sizeof(OutOfBounds));
    _va_Array_161_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_161_eo;
    U32 hoisted__U32_6476 = 0;
    (void)hoisted__U32_6476;
    Str *hoisted__Str_6477 = Str_clone(loc);
    (void)hoisted__Str_6477;
    (void)_til_str_lit_152;
    (void)_til_str_lit_152;
    Array__Str_set(_va_Array_161, hoisted__U32_6476, hoisted__Str_6477, &_va_Array_161_ek, _va_Array_161_eo, &_til_str_lit_152);
    Str_delete(&_til_str_lit_152, (Bool){0});
    U32 hoisted__U32_6479 = 1;
    (void)hoisted__U32_6479;
    (void)_til_str_lit_153;
    (void)_til_str_lit_153;
    (void)_til_str_lit_152;
    (void)_til_str_lit_152;
    Array__Str_set(_va_Array_161, hoisted__U32_6479, &_til_str_lit_153, &_va_Array_161_ek, _va_Array_161_eo, &_til_str_lit_152);
    Str_delete(&_til_str_lit_152, (Bool){0});
    Array__Str *hoisted__Array__Str_6482 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_6482;
    U32 hoisted__U32_6483 = 2;
    (void)hoisted__U32_6483;
    Str *hoisted__Str_6484 = format(hoisted__Array__Str_6482);
    (void)hoisted__Str_6484;
    (void)_til_str_lit_152;
    (void)_til_str_lit_152;
    Array__Str_set(_va_Array_161, hoisted__U32_6483, hoisted__Str_6484, &_va_Array_161_ek, _va_Array_161_eo, &_til_str_lit_152);
    OutOfBounds_delete(_va_Array_161_eo, 1);
    Str_delete(&_til_str_lit_152, (Bool){0});
    Array__Str_delete(parts, 1);
    println(_va_Array_161);
    I64 hoisted__I64_6486 = 1;
    (void)hoisted__I64_6486;
    exit(hoisted__I64_6486);
}

void UNREACHABLE(Str * loc) {
    U32 hoisted__U32_6495 = 1;
    (void)hoisted__U32_6495;
    Array__Str *_va_Array_163 = Array__Str_new(hoisted__U32_6495);
    (void)_va_Array_163;
    I64 _va_Array_163_ek = 0;
    (void)_va_Array_163_ek;
    OutOfBounds *_va_Array_163_eo = malloc(sizeof(OutOfBounds));
    _va_Array_163_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_163_eo;
    U32 hoisted__U32_6496 = 0;
    (void)hoisted__U32_6496;
    (void)_til_str_lit_154;
    (void)_til_str_lit_154;
    (void)_til_str_lit_155;
    (void)_til_str_lit_155;
    Array__Str_set(_va_Array_163, hoisted__U32_6496, &_til_str_lit_154, &_va_Array_163_ek, _va_Array_163_eo, &_til_str_lit_155);
    OutOfBounds_delete(_va_Array_163_eo, 1);
    Str_delete(&_til_str_lit_155, (Bool){0});
    panic(_va_Array_163, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_6503 = ((Bool)(!(cond)));
    (void)hoisted__Bool_6503;
    if (hoisted__Bool_6503) {
        U32 hoisted__U32_6499 = 1;
        (void)hoisted__U32_6499;
        Array__Str *_va_Array_164 = Array__Str_new(hoisted__U32_6499);
        (void)_va_Array_164;
        I64 _va_Array_164_ek = 0;
        (void)_va_Array_164_ek;
        OutOfBounds *_va_Array_164_eo = malloc(sizeof(OutOfBounds));
        _va_Array_164_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_164_eo;
        U32 hoisted__U32_6500 = 0;
        (void)hoisted__U32_6500;
        (void)_til_str_lit_156;
        (void)_til_str_lit_156;
        (void)_til_str_lit_157;
        (void)_til_str_lit_157;
        Array__Str_set(_va_Array_164, hoisted__U32_6500, &_til_str_lit_156, &_va_Array_164_ek, _va_Array_164_eo, &_til_str_lit_157);
        OutOfBounds_delete(_va_Array_164_eo, 1);
        Str_delete(&_til_str_lit_157, (Bool){0});
        panic(_va_Array_164, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_6513 = parts;
        (void)_fc_Array__Str_6513;
        (void)_fc_Array__Str_6513;
        U32 _fi_USize_6513 = 0;
        (void)_fi_USize_6513;
        while (1) {
            USize hoisted__U32_6515 = (_fc_Array__Str_6513->cap);
            (void)hoisted__U32_6515;
            Bool _wcond_Bool_6514 = ((Bool)(_fi_USize_6513 < hoisted__U32_6515));
            (void)_wcond_Bool_6514;
            if (_wcond_Bool_6514) {
            } else {
                break;
            }
            Str *s = (((void *)((U8 *)(_fc_Array__Str_6513->data) + (((U64)(_fi_USize_6513 * 16))))));
            U32 hoisted__U32_6516 = 1;
            (void)hoisted__U32_6516;
            U32 hoisted__U32_6517 = ((U32)(_fi_USize_6513 + hoisted__U32_6516));
            (void)hoisted__U32_6517;
            _fi_USize_6513 = hoisted__U32_6517;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

void swap_bytes(void * a, void * b, UPtr size) {
    U8 *tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_6530 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_6530;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_6530;
    return _r; }
    __builtin_unreachable();
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_6531 = 0;
    (void)hoisted__U32_6531;
    U64 hoisted__U64_6532 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_6531); });
    (void)hoisted__U64_6532;
    return hoisted__U64_6532;
    __builtin_unreachable();
}

USize Range_size(void) {
    U32 hoisted__U32_6563 = 16;
    (void)hoisted__U32_6563;
    return hoisted__U32_6563;
    __builtin_unreachable();
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_6579 = 3;
    (void)hoisted__I64_6579;
    (void)_til_str_lit_160;
    (void)_til_str_lit_160;
    assert_eq__I64(result, hoisted__I64_6579, &_til_str_lit_160);
    Str_delete(&_til_str_lit_160, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_6587 = 15;
    (void)hoisted__I64_6587;
    (void)_til_str_lit_161;
    (void)_til_str_lit_161;
    assert_eq__I64(result, hoisted__I64_6587, &_til_str_lit_161);
    Str_delete(&_til_str_lit_161, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_6595 = 26;
    (void)hoisted__I64_6595;
    (void)_til_str_lit_162;
    (void)_til_str_lit_162;
    assert_eq__I64(result, hoisted__I64_6595, &_til_str_lit_162);
    Str_delete(&_til_str_lit_162, (Bool){0});
}

void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_163;
    (void)_til_str_lit_163;
    (void)_til_str_lit_164;
    (void)_til_str_lit_164;
    assert_eq__Str(&result, &_til_str_lit_163, &_til_str_lit_164);
    Str_delete(&_til_str_lit_163, (Bool){0});
    Str_delete(&_til_str_lit_164, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_163;
    (void)_til_str_lit_163;
    (void)_til_str_lit_165;
    (void)_til_str_lit_165;
    assert_eq__Str(&r, &_til_str_lit_163, &_til_str_lit_165);
    Str_delete(&_til_str_lit_163, (Bool){0});
    Str_delete(&_til_str_lit_165, (Bool){0});
    Str_delete(&r, (Bool){0});
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_166;
    (void)_til_str_lit_166;
    (void)_til_str_lit_167;
    (void)_til_str_lit_167;
    assert_eq__Str(&r2, &_til_str_lit_166, &_til_str_lit_167);
    Str_delete(&_til_str_lit_166, (Bool){0});
    Str_delete(&_til_str_lit_167, (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_168;
    (void)_til_str_lit_168;
    (void)_til_str_lit_169;
    (void)_til_str_lit_169;
    assert_eq__Str(&d, &_til_str_lit_168, &_til_str_lit_169);
    Str_delete(&d, (Bool){0});
    Str_delete(&_til_str_lit_168, (Bool){0});
    Str_delete(&_til_str_lit_169, (Bool){0});
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_170;
    (void)_til_str_lit_170;
    (void)_til_str_lit_171;
    (void)_til_str_lit_171;
    assert_eq__Str(&d2, &_til_str_lit_170, &_til_str_lit_171);
    Str_delete(&d2, (Bool){0});
    Str_delete(&_til_str_lit_170, (Bool){0});
    Str_delete(&_til_str_lit_171, (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_6682 = 106;
    (void)hoisted__I64_6682;
    (void)_til_str_lit_172;
    (void)_til_str_lit_172;
    assert_eq__I64(d3, hoisted__I64_6682, &_til_str_lit_172);
    Str_delete(&_til_str_lit_172, (Bool){0});
}

void test_lolalalo(void) {
    static Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_175;
    (void)_til_str_lit_175;
    assert_eq__Str(&lola_rec, &lola_it, &_til_str_lit_175);
    Str_delete(&_til_str_lit_175, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    (void)_til_str_lit_176;
    (void)_til_str_lit_176;
    assert_eq__Str(&lalo_rec, &lalo_it, &_til_str_lit_176);
    Str_delete(&_til_str_lit_176, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_7285 = 8;
    (void)hoisted__I64_7285;
    (void)_til_str_lit_177;
    (void)_til_str_lit_177;
    assert_eq__I64(result, hoisted__I64_7285, &_til_str_lit_177);
    Str_delete(&_til_str_lit_177, (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_7289 = 1;
    (void)hoisted__Bool_7289;
    (void)_til_str_lit_178;
    (void)_til_str_lit_178;
    assert(hoisted__Bool_7289, &_til_str_lit_178);
    Str_delete(&_til_str_lit_178, (Bool){0});
    Bool hoisted__Bool_7293 = 1;
    (void)hoisted__Bool_7293;
    (void)_til_str_lit_179;
    (void)_til_str_lit_179;
    assert(hoisted__Bool_7293, &_til_str_lit_179);
    Str_delete(&_til_str_lit_179, (Bool){0});
}

void test_fold_f32(void) {
    (void)_til_str_lit_180;
    (void)_til_str_lit_180;
    (void)_til_str_lit_180;
    (void)_til_str_lit_180;
    (void)_til_str_lit_181;
    (void)_til_str_lit_181;
    assert_eq__Str(&_til_str_lit_180, &_til_str_lit_180, &_til_str_lit_181);
    Str_delete(&_til_str_lit_180, (Bool){0});
    Str_delete(&_til_str_lit_180, (Bool){0});
    Str_delete(&_til_str_lit_181, (Bool){0});
    (void)_til_str_lit_182;
    (void)_til_str_lit_182;
    (void)_til_str_lit_182;
    (void)_til_str_lit_182;
    (void)_til_str_lit_183;
    (void)_til_str_lit_183;
    assert_eq__Str(&_til_str_lit_182, &_til_str_lit_182, &_til_str_lit_183);
    Str_delete(&_til_str_lit_182, (Bool){0});
    Str_delete(&_til_str_lit_182, (Bool){0});
    Str_delete(&_til_str_lit_183, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_7311 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_7311;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_7311;
    return _r; }
    __builtin_unreachable();
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_7312 = 0;
    (void)hoisted__U32_7312;
    U64 hoisted__U64_7313 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7312); });
    (void)hoisted__U64_7313;
    return hoisted__U64_7313;
    __builtin_unreachable();
}

USize CfVec2_size(void) {
    U32 hoisted__U32_7344 = 16;
    (void)hoisted__U32_7344;
    return hoisted__U32_7344;
    __builtin_unreachable();
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_7345 = 42;
    (void)hoisted__I64_7345;
    (void)_til_str_lit_186;
    (void)_til_str_lit_186;
    assert_eq__I64(v.x, hoisted__I64_7345, &_til_str_lit_186);
    Str_delete(&_til_str_lit_186, (Bool){0});
    I64 hoisted__I64_7347 = 99;
    (void)hoisted__I64_7347;
    (void)_til_str_lit_187;
    (void)_til_str_lit_187;
    assert_eq__I64(v.y, hoisted__I64_7347, &_til_str_lit_187);
    Str_delete(&_til_str_lit_187, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_7351 = 10;
    (void)hoisted__I64_7351;
    (void)_til_str_lit_188;
    (void)_til_str_lit_188;
    assert_eq__I64(p.x, hoisted__I64_7351, &_til_str_lit_188);
    Str_delete(&_til_str_lit_188, (Bool){0});
    I64 hoisted__I64_7353 = 20;
    (void)hoisted__I64_7353;
    (void)_til_str_lit_189;
    (void)_til_str_lit_189;
    assert_eq__I64(p.y, hoisted__I64_7353, &_til_str_lit_189);
    Str_delete(&_til_str_lit_189, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_7360 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_7360;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_7360;
    return _r; }
    __builtin_unreachable();
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_7361 = 0;
    (void)hoisted__U32_7361;
    U64 hoisted__U64_7362 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7361); });
    (void)hoisted__U64_7362;
    return hoisted__U64_7362;
    __builtin_unreachable();
}

USize CfRect_size(void) {
    U32 hoisted__U32_7393 = 32;
    (void)hoisted__U32_7393;
    return hoisted__U32_7393;
    __builtin_unreachable();
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_7394 = 5;
    (void)hoisted__I64_7394;
    (void)_til_str_lit_193;
    (void)_til_str_lit_193;
    assert_eq__I64(r.top_left.x, hoisted__I64_7394, &_til_str_lit_193);
    Str_delete(&_til_str_lit_193, (Bool){0});
    I64 hoisted__I64_7396 = 10;
    (void)hoisted__I64_7396;
    (void)_til_str_lit_194;
    (void)_til_str_lit_194;
    assert_eq__I64(r.top_left.y, hoisted__I64_7396, &_til_str_lit_194);
    Str_delete(&_til_str_lit_194, (Bool){0});
    I64 hoisted__I64_7398 = 100;
    (void)hoisted__I64_7398;
    (void)_til_str_lit_195;
    (void)_til_str_lit_195;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_7398, &_til_str_lit_195);
    Str_delete(&_til_str_lit_195, (Bool){0});
    I64 hoisted__I64_7400 = 200;
    (void)hoisted__I64_7400;
    (void)_til_str_lit_196;
    (void)_til_str_lit_196;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_7400, &_til_str_lit_196);
    Str_delete(&_til_str_lit_196, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_7403 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_7403;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_7403;
    return _r; }
    __builtin_unreachable();
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_7404 = 0;
    (void)hoisted__U32_7404;
    U64 hoisted__U64_7405 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7404); });
    (void)hoisted__U64_7405;
    return hoisted__U64_7405;
    __builtin_unreachable();
}

USize CfVec3f_size(void) {
    U32 hoisted__U32_7448 = 12;
    (void)hoisted__U32_7448;
    return hoisted__U32_7448;
    __builtin_unreachable();
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_7452 = F32_to_str(v.x);
    (void)hoisted__Str_7452;
    (void)_til_str_lit_198;
    (void)_til_str_lit_198;
    (void)_til_str_lit_199;
    (void)_til_str_lit_199;
    assert_eq__Str(hoisted__Str_7452, &_til_str_lit_198, &_til_str_lit_199);
    Str_delete(hoisted__Str_7452, 1);
    Str_delete(&_til_str_lit_198, (Bool){0});
    Str_delete(&_til_str_lit_199, (Bool){0});
    Str *hoisted__Str_7455 = F32_to_str(v.y);
    (void)hoisted__Str_7455;
    (void)_til_str_lit_200;
    (void)_til_str_lit_200;
    (void)_til_str_lit_201;
    (void)_til_str_lit_201;
    assert_eq__Str(hoisted__Str_7455, &_til_str_lit_200, &_til_str_lit_201);
    Str_delete(hoisted__Str_7455, 1);
    Str_delete(&_til_str_lit_200, (Bool){0});
    Str_delete(&_til_str_lit_201, (Bool){0});
    Str *hoisted__Str_7458 = F32_to_str(v.z);
    (void)hoisted__Str_7458;
    (void)_til_str_lit_202;
    (void)_til_str_lit_202;
    (void)_til_str_lit_203;
    (void)_til_str_lit_203;
    assert_eq__Str(hoisted__Str_7458, &_til_str_lit_202, &_til_str_lit_203);
    Str_delete(hoisted__Str_7458, 1);
    Str_delete(&_til_str_lit_202, (Bool){0});
    Str_delete(&_til_str_lit_203, (Bool){0});
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
    U32 hoisted__U32_7467 = 1;
    (void)hoisted__U32_7467;
    Bool hoisted__Bool_7468 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Red}))->tag));
    (void)hoisted__Bool_7468;
    if (hoisted__Bool_7468) {
        U32 hoisted__U32_7461 = 1;
        (void)hoisted__U32_7461;
        Bool hoisted__Bool_7462 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Red}))->tag));
        (void)hoisted__Bool_7462;
        return hoisted__Bool_7462;
    }
    U32 hoisted__U32_7469 = 1;
    (void)hoisted__U32_7469;
    Bool hoisted__Bool_7470 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Green}))->tag));
    (void)hoisted__Bool_7470;
    if (hoisted__Bool_7470) {
        U32 hoisted__U32_7463 = 1;
        (void)hoisted__U32_7463;
        Bool hoisted__Bool_7464 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Green}))->tag));
        (void)hoisted__Bool_7464;
        return hoisted__Bool_7464;
    }
    U32 hoisted__U32_7471 = 1;
    (void)hoisted__U32_7471;
    Bool hoisted__Bool_7472 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Blue}))->tag));
    (void)hoisted__Bool_7472;
    if (hoisted__Bool_7472) {
        U32 hoisted__U32_7465 = 1;
        (void)hoisted__U32_7465;
        Bool hoisted__Bool_7466 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Blue}))->tag));
        (void)hoisted__Bool_7466;
        return hoisted__Bool_7466;
    }
    Bool hoisted__Bool_7473 = 0;
    (void)hoisted__Bool_7473;
    return hoisted__Bool_7473;
    __builtin_unreachable();
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_7481 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7481;
    if (hoisted__Bool_7481) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
        return _r; }
    }
    Bool hoisted__Bool_7482 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7482;
    if (hoisted__Bool_7482) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
        return _r; }
    }
    Bool hoisted__Bool_7483 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_7483;
    if (hoisted__Bool_7483) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
        return _r; }
    }
    static Str hoisted__Str_7484 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7484;
    UNREACHABLE(&hoisted__Str_7484);
    Str_delete(&hoisted__Str_7484, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
    __builtin_unreachable();
}

USize Color_size(void) {
    U32 hoisted__U32_7485 = 1;
    (void)hoisted__U32_7485;
    return hoisted__U32_7485;
    __builtin_unreachable();
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_7486 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7486;
    (void)_til_str_lit_207;
    (void)_til_str_lit_207;
    assert(hoisted__Bool_7486, &_til_str_lit_207);
    Str_delete(&_til_str_lit_207, (Bool){0});
    Bool hoisted__Bool_7488 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7488;
    Bool hoisted__Bool_7489 = ((Bool)(!(hoisted__Bool_7488)));
    (void)hoisted__Bool_7489;
    (void)_til_str_lit_208;
    (void)_til_str_lit_208;
    assert(hoisted__Bool_7489, &_til_str_lit_208);
    Str_delete(&_til_str_lit_208, (Bool){0});
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
    U32 hoisted__U32_7514 = 1;
    (void)hoisted__U32_7514;
    Bool hoisted__Bool_7515 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_7515;
    if (hoisted__Bool_7515) {
        I64 *hoisted__I64_7510 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__I64_7510;
        (void)hoisted__I64_7510;
        Bool hoisted__Bool_7511 = 0;
        (void)hoisted__Bool_7511;
        I64_delete(hoisted__I64_7510, hoisted__Bool_7511);
    }
    U32 hoisted__U32_7516 = 1;
    (void)hoisted__U32_7516;
    Bool hoisted__Bool_7517 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Name}))->tag));
    (void)hoisted__Bool_7517;
    if (hoisted__Bool_7517) {
        Str *hoisted__Str_7512 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Str_7512;
        (void)hoisted__Str_7512;
        Bool hoisted__Bool_7513 = 0;
        (void)hoisted__Bool_7513;
        Str_delete(hoisted__Str_7512, hoisted__Bool_7513);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    U32 hoisted__U32_7551 = 1;
    (void)hoisted__U32_7551;
    Bool hoisted__Bool_7552 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_7552;
    if (hoisted__Bool_7552) {
        I64 *_clone_payload_Num_0 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_7548 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_7548;
        return hoisted__Token_7548;
    }
    U32 hoisted__U32_7553 = 1;
    (void)hoisted__U32_7553;
    Bool hoisted__Bool_7554 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Name}))->tag));
    (void)hoisted__Bool_7554;
    if (hoisted__Bool_7554) {
        Str *_clone_payload_Name_1 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_7549 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_7549;
        Token *hoisted__Token_7550 = Token_Name(hoisted__Str_7549);
        (void)hoisted__Token_7550;
        return hoisted__Token_7550;
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
    __builtin_unreachable();
}

USize Token_size(void) {
    U32 hoisted__U32_7555 = 24;
    (void)hoisted__U32_7555;
    return hoisted__U32_7555;
    __builtin_unreachable();
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_7557 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_7557;
    (void)_til_str_lit_211;
    (void)_til_str_lit_211;
    assert(hoisted__Bool_7557, &_til_str_lit_211);
    Str_delete(&_til_str_lit_211, (Bool){0});
    Bool hoisted__Bool_7559 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag));
    (void)hoisted__Bool_7559;
    Bool hoisted__Bool_7560 = ((Bool)(!(hoisted__Bool_7559)));
    (void)hoisted__Bool_7560;
    (void)_til_str_lit_212;
    (void)_til_str_lit_212;
    assert(hoisted__Bool_7560, &_til_str_lit_212);
    Str_delete(&_til_str_lit_212, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_7562 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7562;
    (void)_til_str_lit_213;
    (void)_til_str_lit_213;
    assert(hoisted__Bool_7562, &_til_str_lit_213);
    Str_delete(&_til_str_lit_213, (Bool){0});
    Bool hoisted__Bool_7564 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7564;
    Bool hoisted__Bool_7565 = ((Bool)(!(hoisted__Bool_7564)));
    (void)hoisted__Bool_7565;
    (void)_til_str_lit_214;
    (void)_til_str_lit_214;
    assert(hoisted__Bool_7565, &_til_str_lit_214);
    Str_delete(&_til_str_lit_214, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_7569 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_7569;
    (void)_til_str_lit_215;
    (void)_til_str_lit_215;
    assert(hoisted__Bool_7569, &_til_str_lit_215);
    Str_delete(&_til_str_lit_215, (Bool){0});
    Bool hoisted__Bool_7571 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag));
    (void)hoisted__Bool_7571;
    Bool hoisted__Bool_7572 = ((Bool)(!(hoisted__Bool_7571)));
    (void)hoisted__Bool_7572;
    (void)_til_str_lit_216;
    (void)_til_str_lit_216;
    assert(hoisted__Bool_7572, &_til_str_lit_216);
    Str_delete(&_til_str_lit_216, (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_7689 = ((Bool)(a != b));
    (void)hoisted__Bool_7689;
    if (hoisted__Bool_7689) {
        U32 hoisted__U32_7673 = 5;
        (void)hoisted__U32_7673;
        Array__Str *_va_Array_203 = Array__Str_new(hoisted__U32_7673);
        (void)_va_Array_203;
        I64 _va_Array_203_ek = 0;
        (void)_va_Array_203_ek;
        OutOfBounds *_va_Array_203_eo = malloc(sizeof(OutOfBounds));
        _va_Array_203_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_203_eo;
        U32 hoisted__U32_7674 = 0;
        (void)hoisted__U32_7674;
        (void)_til_str_lit_217;
        (void)_til_str_lit_217;
        (void)_til_str_lit_218;
        (void)_til_str_lit_218;
        Array__Str_set(_va_Array_203, hoisted__U32_7674, &_til_str_lit_217, &_va_Array_203_ek, _va_Array_203_eo, &_til_str_lit_218);
        Str_delete(&_til_str_lit_218, (Bool){0});
        U32 hoisted__U32_7677 = 1;
        (void)hoisted__U32_7677;
        Str *hoisted__Str_7678 = I64_to_str(a);
        (void)hoisted__Str_7678;
        (void)_til_str_lit_218;
        (void)_til_str_lit_218;
        Array__Str_set(_va_Array_203, hoisted__U32_7677, hoisted__Str_7678, &_va_Array_203_ek, _va_Array_203_eo, &_til_str_lit_218);
        Str_delete(&_til_str_lit_218, (Bool){0});
        U32 hoisted__U32_7680 = 2;
        (void)hoisted__U32_7680;
        (void)_til_str_lit_219;
        (void)_til_str_lit_219;
        (void)_til_str_lit_218;
        (void)_til_str_lit_218;
        Array__Str_set(_va_Array_203, hoisted__U32_7680, &_til_str_lit_219, &_va_Array_203_ek, _va_Array_203_eo, &_til_str_lit_218);
        Str_delete(&_til_str_lit_218, (Bool){0});
        U32 hoisted__U32_7683 = 3;
        (void)hoisted__U32_7683;
        Str *hoisted__Str_7684 = I64_to_str(b);
        (void)hoisted__Str_7684;
        (void)_til_str_lit_218;
        (void)_til_str_lit_218;
        Array__Str_set(_va_Array_203, hoisted__U32_7683, hoisted__Str_7684, &_va_Array_203_ek, _va_Array_203_eo, &_til_str_lit_218);
        Str_delete(&_til_str_lit_218, (Bool){0});
        U32 hoisted__U32_7686 = 4;
        (void)hoisted__U32_7686;
        (void)_til_str_lit_220;
        (void)_til_str_lit_220;
        (void)_til_str_lit_218;
        (void)_til_str_lit_218;
        Array__Str_set(_va_Array_203, hoisted__U32_7686, &_til_str_lit_220, &_va_Array_203_ek, _va_Array_203_eo, &_til_str_lit_218);
        OutOfBounds_delete(_va_Array_203_eo, 1);
        Str_delete(&_til_str_lit_218, (Bool){0});
        panic(_va_Array_203, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_7706 = Str_neq(a, b);
    (void)hoisted__Bool_7706;
    if (hoisted__Bool_7706) {
        U32 hoisted__U32_7690 = 5;
        (void)hoisted__U32_7690;
        Array__Str *_va_Array_204 = Array__Str_new(hoisted__U32_7690);
        (void)_va_Array_204;
        I64 _va_Array_204_ek = 0;
        (void)_va_Array_204_ek;
        OutOfBounds *_va_Array_204_eo = malloc(sizeof(OutOfBounds));
        _va_Array_204_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_204_eo;
        U32 hoisted__U32_7691 = 0;
        (void)hoisted__U32_7691;
        (void)_til_str_lit_217;
        (void)_til_str_lit_217;
        (void)_til_str_lit_218;
        (void)_til_str_lit_218;
        Array__Str_set(_va_Array_204, hoisted__U32_7691, &_til_str_lit_217, &_va_Array_204_ek, _va_Array_204_eo, &_til_str_lit_218);
        Str_delete(&_til_str_lit_218, (Bool){0});
        U32 hoisted__U32_7694 = 1;
        (void)hoisted__U32_7694;
        Str *hoisted__Str_7695 = Str_to_str(a);
        (void)hoisted__Str_7695;
        (void)_til_str_lit_218;
        (void)_til_str_lit_218;
        Array__Str_set(_va_Array_204, hoisted__U32_7694, hoisted__Str_7695, &_va_Array_204_ek, _va_Array_204_eo, &_til_str_lit_218);
        Str_delete(&_til_str_lit_218, (Bool){0});
        U32 hoisted__U32_7697 = 2;
        (void)hoisted__U32_7697;
        (void)_til_str_lit_219;
        (void)_til_str_lit_219;
        (void)_til_str_lit_218;
        (void)_til_str_lit_218;
        Array__Str_set(_va_Array_204, hoisted__U32_7697, &_til_str_lit_219, &_va_Array_204_ek, _va_Array_204_eo, &_til_str_lit_218);
        Str_delete(&_til_str_lit_218, (Bool){0});
        U32 hoisted__U32_7700 = 3;
        (void)hoisted__U32_7700;
        Str *hoisted__Str_7701 = Str_to_str(b);
        (void)hoisted__Str_7701;
        (void)_til_str_lit_218;
        (void)_til_str_lit_218;
        Array__Str_set(_va_Array_204, hoisted__U32_7700, hoisted__Str_7701, &_va_Array_204_ek, _va_Array_204_eo, &_til_str_lit_218);
        Str_delete(&_til_str_lit_218, (Bool){0});
        U32 hoisted__U32_7703 = 4;
        (void)hoisted__U32_7703;
        (void)_til_str_lit_220;
        (void)_til_str_lit_220;
        (void)_til_str_lit_218;
        (void)_til_str_lit_218;
        Array__Str_set(_va_Array_204, hoisted__U32_7703, &_til_str_lit_220, &_va_Array_204_ek, _va_Array_204_eo, &_til_str_lit_218);
        OutOfBounds_delete(_va_Array_204_eo, 1);
        Str_delete(&_til_str_lit_218, (Bool){0});
        panic(_va_Array_204, loc);
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
void Array__Str_set_dyn(void *til_env, void *_a0, void *_a1, void *_a2, void *_a3, void *_a4, void *_a5) {
    (void)til_env;
    Array__Str_set(_a0, *(USize *)_a1, _a2, _a3, _a4, _a5);
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
I64 U32_to_i64_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return U32_to_i64(*(U32 *)_a0);
}
static __attribute__((unused)) TilClosure U32_to_i64_dyn__til_closure = { (void *)U32_to_i64_dyn, NULL, NULL };
void *U32_to_str_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)U32_to_str(*(U32 *)_a0);
}
static __attribute__((unused)) TilClosure U32_to_str_dyn__til_closure = { (void *)U32_to_str_dyn, NULL, NULL };
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
U64 StructDef_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return StructDef_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure StructDef_hash_dyn__til_closure = { (void *)StructDef_hash_dyn, NULL, NULL };
USize StructDef_size_dyn(void *til_env) {
    (void)til_env;
    return StructDef_size();
}
static __attribute__((unused)) TilClosure StructDef_size_dyn__til_closure = { (void *)StructDef_size_dyn, NULL, NULL };
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
U64 EnumDef_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return EnumDef_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure EnumDef_hash_dyn__til_closure = { (void *)EnumDef_hash_dyn, NULL, NULL };
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
void *Map__I64_Str_new_dyn(void *til_env) {
    (void)til_env;
    return (void *)Map__I64_Str_new();
}
static __attribute__((unused)) TilClosure Map__I64_Str_new_dyn__til_closure = { (void *)Map__I64_Str_new_dyn, NULL, NULL };
void Map__I64_Str_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Map__I64_Str_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Map__I64_Str_delete_dyn__til_closure = { (void *)Map__I64_Str_delete_dyn, NULL, NULL };
void *Map__I64_Str_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Map__I64_Str_clone(_a0);
}
static __attribute__((unused)) TilClosure Map__I64_Str_clone_dyn__til_closure = { (void *)Map__I64_Str_clone_dyn, NULL, NULL };
U64 Map__I64_Str_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Map__I64_Str_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure Map__I64_Str_hash_dyn__til_closure = { (void *)Map__I64_Str_hash_dyn, NULL, NULL };
USize Map__I64_Str_size_dyn(void *til_env) {
    (void)til_env;
    return Map__I64_Str_size();
}
static __attribute__((unused)) TilClosure Map__I64_Str_size_dyn__til_closure = { (void *)Map__I64_Str_size_dyn, NULL, NULL };
void *Vec__Bool_new_dyn(void *til_env) {
    (void)til_env;
    return (void *)Vec__Bool_new();
}
static __attribute__((unused)) TilClosure Vec__Bool_new_dyn__til_closure = { (void *)Vec__Bool_new_dyn, NULL, NULL };
void Vec__Bool_clear_dyn(void *til_env, void *_a0) {
    (void)til_env;
    Vec__Bool_clear(_a0);
}
static __attribute__((unused)) TilClosure Vec__Bool_clear_dyn__til_closure = { (void *)Vec__Bool_clear_dyn, NULL, NULL };
void Vec__Bool_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Vec__Bool_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Vec__Bool_delete_dyn__til_closure = { (void *)Vec__Bool_delete_dyn, NULL, NULL };
void *Vec__Bool_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Vec__Bool_clone(_a0);
}
static __attribute__((unused)) TilClosure Vec__Bool_clone_dyn__til_closure = { (void *)Vec__Bool_clone_dyn, NULL, NULL };
USize Vec__Bool_size_dyn(void *til_env) {
    (void)til_env;
    return Vec__Bool_size();
}
static __attribute__((unused)) TilClosure Vec__Bool_size_dyn__til_closure = { (void *)Vec__Bool_size_dyn, NULL, NULL };
void *Vec__I64_new_dyn(void *til_env) {
    (void)til_env;
    return (void *)Vec__I64_new();
}
static __attribute__((unused)) TilClosure Vec__I64_new_dyn__til_closure = { (void *)Vec__I64_new_dyn, NULL, NULL };
void Vec__I64_clear_dyn(void *til_env, void *_a0) {
    (void)til_env;
    Vec__I64_clear(_a0);
}
static __attribute__((unused)) TilClosure Vec__I64_clear_dyn__til_closure = { (void *)Vec__I64_clear_dyn, NULL, NULL };
void Vec__I64_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Vec__I64_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Vec__I64_delete_dyn__til_closure = { (void *)Vec__I64_delete_dyn, NULL, NULL };
void *Vec__I64_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Vec__I64_clone(_a0);
}
static __attribute__((unused)) TilClosure Vec__I64_clone_dyn__til_closure = { (void *)Vec__I64_clone_dyn, NULL, NULL };
USize Vec__I64_size_dyn(void *til_env) {
    (void)til_env;
    return Vec__I64_size();
}
static __attribute__((unused)) TilClosure Vec__I64_size_dyn__til_closure = { (void *)Vec__I64_size_dyn, NULL, NULL };
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i64", 6ULL) == 0) return (void*)&U32_to_i64_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)&U32_to_str_dyn__til_closure;
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
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&StructDef_hash_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&StructDef_size_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&EnumDef_clone_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&EnumDef_delete_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&EnumDef_hash_dyn__til_closure;
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
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)&Map__I64_Str_new_dyn__til_closure;
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Map__I64_Str_delete_dyn__til_closure;
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Map__I64_Str_clone_dyn__til_closure;
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&Map__I64_Str_hash_dyn__til_closure;
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Map__I64_Str_size_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)&Vec__Bool_new_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clear", 5ULL) == 0) return (void*)&Vec__Bool_clear_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Vec__Bool_delete_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Vec__Bool_clone_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Vec__Bool_size_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)&Vec__I64_new_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clear", 5ULL) == 0) return (void*)&Vec__I64_clear_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Vec__I64_delete_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Vec__I64_clone_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Vec__I64_size_dyn__til_closure;
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
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) return sizeof(EnumDef);
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) return sizeof(AssignData);
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) return sizeof(FieldAssignData);
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) return sizeof(ForInData);
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) return sizeof(Literal);
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) return sizeof(MatchData);
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) return sizeof(CaptureBlockData);
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) return sizeof(NodeType);
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) return sizeof(Expr);
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) return sizeof(Map__I64_Str);
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0) return sizeof(Vec__Bool);
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) return sizeof(Vec__I64);
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) return sizeof(Vec__Declaration);
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) return sizeof(Vec__Expr);
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
        return 1LL;
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
        return 12LL;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        return 6LL;
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
        return 6LL;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        return 7LL;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        return 4LL;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        return 2LL;
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
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        return 2LL;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0) {
        return 3LL;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) {
        return 3LL;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) {
        return 3LL;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) {
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
        if (*index == 0LL) return &_til_str_lit_0;
        if (*index == 1LL) return &_til_str_lit_2;
        if (*index == 2LL) return &_til_str_lit_4;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_5;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_7;
        if (*index == 1LL) return &_til_str_lit_4;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_7;
        if (*index == 1LL) return &_til_str_lit_2;
        if (*index == 2LL) return &_til_str_lit_4;
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
        if (*index == 0LL) return &_til_str_lit_48;
        if (*index == 1LL) return &_til_str_lit_49;
        if (*index == 2LL) return &_til_str_lit_50;
        if (*index == 3LL) return &_til_str_lit_51;
        if (*index == 4LL) return &_til_str_lit_52;
        if (*index == 5LL) return &_til_str_lit_53;
        if (*index == 6LL) return &_til_str_lit_54;
        if (*index == 7LL) return &_til_str_lit_55;
        if (*index == 8LL) return &_til_str_lit_57;
        if (*index == 9LL) return &_til_str_lit_59;
        if (*index == 10LL) return &_til_str_lit_61;
        if (*index == 11LL) return &_til_str_lit_62;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_64;
        if (*index == 1LL) return &_til_str_lit_66;
        if (*index == 2LL) return &_til_str_lit_68;
        if (*index == 3LL) return &_til_str_lit_69;
        if (*index == 4LL) return &_til_str_lit_71;
        if (*index == 5LL) return &_til_str_lit_72;
        if (*index == 6LL) return &_til_str_lit_73;
        if (*index == 7LL) return &_til_str_lit_74;
        if (*index == 8LL) return &_til_str_lit_75;
        if (*index == 9LL) return &_til_str_lit_76;
        if (*index == 10LL) return &_til_str_lit_77;
        if (*index == 11LL) return &_til_str_lit_78;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_79;
        if (*index == 1LL) return &_til_str_lit_80;
        if (*index == 2LL) return &_til_str_lit_81;
        if (*index == 3LL) return &_til_str_lit_82;
        if (*index == 4LL) return &_til_str_lit_83;
        if (*index == 5LL) return &_til_str_lit_57;
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_84;
        if (*index == 1LL) return &_til_str_lit_57;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_48;
        if (*index == 1LL) return &_til_str_lit_57;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_48;
        if (*index == 1LL) return &_til_str_lit_57;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_85;
        if (*index == 1LL) return &_til_str_lit_86;
        if (*index == 2LL) return &_til_str_lit_87;
        if (*index == 3LL) return &_til_str_lit_88;
        if (*index == 4LL) return &_til_str_lit_89;
        if (*index == 5LL) return &_til_str_lit_90;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_86;
        if (*index == 1LL) return &_til_str_lit_91;
        if (*index == 2LL) return &_til_str_lit_92;
        if (*index == 3LL) return &_til_str_lit_94;
        if (*index == 4LL) return &_til_str_lit_90;
        if (*index == 5LL) return &_til_str_lit_96;
        if (*index == 6LL) return &_til_str_lit_97;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_48;
        if (*index == 1LL) return &_til_str_lit_99;
        if (*index == 2LL) return &_til_str_lit_100;
        if (*index == 3LL) return &_til_str_lit_83;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_48;
        if (*index == 1LL) return &_til_str_lit_99;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_48;
        if (*index == 1LL) return &_til_str_lit_51;
        if (*index == 2LL) return &_til_str_lit_57;
        if (*index == 3LL) return &_til_str_lit_101;
        if (*index == 4LL) return &_til_str_lit_102;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_57;
        if (*index == 1LL) return &_til_str_lit_108;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_77;
        if (*index == 1LL) return &_til_str_lit_78;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_144;
        if (*index == 1LL) return &_til_str_lit_146;
        if (*index == 2LL) return &_til_str_lit_148;
        if (*index == 3LL) return &_til_str_lit_149;
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_150;
        if (*index == 1LL) return &_til_str_lit_151;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_7;
        if (*index == 1LL) return &_til_str_lit_2;
        if (*index == 2LL) return &_til_str_lit_4;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_7;
        if (*index == 1LL) return &_til_str_lit_2;
        if (*index == 2LL) return &_til_str_lit_4;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_7;
        if (*index == 1LL) return &_til_str_lit_2;
        if (*index == 2LL) return &_til_str_lit_4;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_7;
        if (*index == 1LL) return &_til_str_lit_2;
        if (*index == 2LL) return &_til_str_lit_4;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_158;
        if (*index == 1LL) return &_til_str_lit_159;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_184;
        if (*index == 1LL) return &_til_str_lit_185;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_190;
        if (*index == 1LL) return &_til_str_lit_192;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_184;
        if (*index == 1LL) return &_til_str_lit_185;
        if (*index == 2LL) return &_til_str_lit_197;
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
        if (*index == 0LL) return 1;
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
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
        if (*index == 3LL) return 1;
        if (*index == 4LL) return 1;
        if (*index == 5LL) return 1;
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
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
        if (*index == 3LL) return 1;
        if (*index == 4LL) return 1;
        if (*index == 5LL) return 1;
        if (*index == 6LL) return 1;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
        if (*index == 3LL) return 1;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
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
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) {
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
        if (*index == 0LL) return &_til_str_lit_1;
        if (*index == 1LL) return &_til_str_lit_3;
        if (*index == 2LL) return &_til_str_lit_3;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_8;
        if (*index == 1LL) return &_til_str_lit_3;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_8;
        if (*index == 1LL) return &_til_str_lit_3;
        if (*index == 2LL) return &_til_str_lit_3;
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
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_6;
        if (*index == 2LL) return &_til_str_lit_6;
        if (*index == 3LL) return &_til_str_lit_17;
        if (*index == 4LL) return &_til_str_lit_17;
        if (*index == 5LL) return &_til_str_lit_17;
        if (*index == 6LL) return &_til_str_lit_17;
        if (*index == 7LL) return &_til_str_lit_56;
        if (*index == 8LL) return &_til_str_lit_58;
        if (*index == 9LL) return &_til_str_lit_60;
        if (*index == 10LL) return &_til_str_lit_6;
        if (*index == 11LL) return &_til_str_lit_63;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_65;
        if (*index == 1LL) return &_til_str_lit_67;
        if (*index == 2LL) return &_til_str_lit_6;
        if (*index == 3LL) return &_til_str_lit_70;
        if (*index == 4LL) return &_til_str_lit_14;
        if (*index == 5LL) return &_til_str_lit_14;
        if (*index == 6LL) return &_til_str_lit_56;
        if (*index == 7LL) return &_til_str_lit_17;
        if (*index == 8LL) return &_til_str_lit_17;
        if (*index == 9LL) return &_til_str_lit_17;
        if (*index == 10LL) return &_til_str_lit_67;
        if (*index == 11LL) return &_til_str_lit_6;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_17;
        if (*index == 1LL) return &_til_str_lit_17;
        if (*index == 2LL) return &_til_str_lit_17;
        if (*index == 3LL) return &_til_str_lit_10;
        if (*index == 4LL) return &_til_str_lit_17;
        if (*index == 5LL) return &_til_str_lit_58;
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_58;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_58;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_58;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_67;
        if (*index == 1LL) return &_til_str_lit_67;
        if (*index == 2LL) return &_til_str_lit_6;
        if (*index == 3LL) return &_til_str_lit_17;
        if (*index == 4LL) return &_til_str_lit_17;
        if (*index == 5LL) return &_til_str_lit_6;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_67;
        if (*index == 1LL) return &_til_str_lit_70;
        if (*index == 2LL) return &_til_str_lit_93;
        if (*index == 3LL) return &_til_str_lit_95;
        if (*index == 4LL) return &_til_str_lit_6;
        if (*index == 5LL) return &_til_str_lit_6;
        if (*index == 6LL) return &_til_str_lit_98;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_17;
        if (*index == 2LL) return &_til_str_lit_17;
        if (*index == 3LL) return &_til_str_lit_17;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_17;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_17;
        if (*index == 2LL) return &_til_str_lit_58;
        if (*index == 3LL) return &_til_str_lit_6;
        if (*index == 4LL) return &_til_str_lit_17;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_58;
        if (*index == 1LL) return &_til_str_lit_6;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_67;
        if (*index == 1LL) return &_til_str_lit_6;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_145;
        if (*index == 1LL) return &_til_str_lit_147;
        if (*index == 2LL) return &_til_str_lit_13;
        if (*index == 3LL) return &_til_str_lit_13;
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_98;
        if (*index == 1LL) return &_til_str_lit_70;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_8;
        if (*index == 1LL) return &_til_str_lit_3;
        if (*index == 2LL) return &_til_str_lit_3;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_8;
        if (*index == 1LL) return &_til_str_lit_3;
        if (*index == 2LL) return &_til_str_lit_3;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_8;
        if (*index == 1LL) return &_til_str_lit_3;
        if (*index == 2LL) return &_til_str_lit_3;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_8;
        if (*index == 1LL) return &_til_str_lit_3;
        if (*index == 2LL) return &_til_str_lit_3;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_10;
        if (*index == 1LL) return &_til_str_lit_10;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_15;
        if (*index == 1LL) return &_til_str_lit_15;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_191;
        if (*index == 1LL) return &_til_str_lit_191;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_16;
        if (*index == 1LL) return &_til_str_lit_16;
        if (*index == 2LL) return &_til_str_lit_16;
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
        if (*index == 0LL) return &_til_str_lit_11;
        if (*index == 1LL) return &_til_str_lit_12;
        if (*index == 2LL) return &_til_str_lit_1;
        if (*index == 3LL) return &_til_str_lit_8;
        if (*index == 4LL) return &_til_str_lit_13;
        if (*index == 5LL) return &_til_str_lit_14;
        if (*index == 6LL) return &_til_str_lit_10;
        if (*index == 7LL) return &_til_str_lit_15;
        if (*index == 8LL) return &_til_str_lit_16;
        if (*index == 9LL) return &_til_str_lit_17;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_19;
        if (*index == 1LL) return &_til_str_lit_20;
        if (*index == 2LL) return &_til_str_lit_21;
        if (*index == 3LL) return &_til_str_lit_22;
        if (*index == 4LL) return &_til_str_lit_23;
        if (*index == 5LL) return &_til_str_lit_24;
        if (*index == 6LL) return &_til_str_lit_25;
        if (*index == 7LL) return &_til_str_lit_26;
        if (*index == 8LL) return &_til_str_lit_9;
        if (*index == 9LL) return &_til_str_lit_27;
        if (*index == 10LL) return &_til_str_lit_28;
        if (*index == 11LL) return &_til_str_lit_29;
        if (*index == 12LL) return &_til_str_lit_30;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_31;
        if (*index == 1LL) return &_til_str_lit_32;
        if (*index == 2LL) return &_til_str_lit_33;
        if (*index == 3LL) return &_til_str_lit_34;
        if (*index == 4LL) return &_til_str_lit_35;
        if (*index == 5LL) return &_til_str_lit_36;
        if (*index == 6LL) return &_til_str_lit_37;
        if (*index == 7LL) return &_til_str_lit_38;
        if (*index == 8LL) return &_til_str_lit_39;
        if (*index == 9LL) return &_til_str_lit_40;
        if (*index == 10LL) return &_til_str_lit_41;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_42;
        if (*index == 1LL) return &_til_str_lit_43;
        if (*index == 2LL) return &_til_str_lit_44;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "GcStorage", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_45;
        if (*index == 1LL) return &_til_str_lit_46;
        if (*index == 2LL) return &_til_str_lit_47;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_103;
        if (*index == 2LL) return &_til_str_lit_17;
        if (*index == 3LL) return &_til_str_lit_105;
        if (*index == 4LL) return &_til_str_lit_106;
        if (*index == 5LL) return &_til_str_lit_107;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_30;
        if (*index == 1LL) return &_til_str_lit_109;
        if (*index == 2LL) return &_til_str_lit_110;
        if (*index == 3LL) return &_til_str_lit_112;
        if (*index == 4LL) return &_til_str_lit_114;
        if (*index == 5LL) return &_til_str_lit_116;
        if (*index == 6LL) return &_til_str_lit_25;
        if (*index == 7LL) return &_til_str_lit_22;
        if (*index == 8LL) return &_til_str_lit_24;
        if (*index == 9LL) return &_til_str_lit_119;
        if (*index == 10LL) return &_til_str_lit_121;
        if (*index == 11LL) return &_til_str_lit_123;
        if (*index == 12LL) return &_til_str_lit_124;
        if (*index == 13LL) return &_til_str_lit_125;
        if (*index == 14LL) return &_til_str_lit_126;
        if (*index == 15LL) return &_til_str_lit_128;
        if (*index == 16LL) return &_til_str_lit_129;
        if (*index == 17LL) return &_til_str_lit_130;
        if (*index == 18LL) return &_til_str_lit_131;
        if (*index == 19LL) return &_til_str_lit_132;
        if (*index == 20LL) return &_til_str_lit_134;
        if (*index == 21LL) return &_til_str_lit_135;
        if (*index == 22LL) return &_til_str_lit_136;
        if (*index == 23LL) return &_til_str_lit_137;
        if (*index == 24LL) return &_til_str_lit_138;
        if (*index == 25LL) return &_til_str_lit_139;
        if (*index == 26LL) return &_til_str_lit_141;
        if (*index == 27LL) return &_til_str_lit_142;
        if (*index == 28LL) return &_til_str_lit_143;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_204;
        if (*index == 1LL) return &_til_str_lit_205;
        if (*index == 2LL) return &_til_str_lit_206;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_103;
        if (*index == 1LL) return &_til_str_lit_209;
        if (*index == 2LL) return &_til_str_lit_210;
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
        if (*index == 0LL) return &_til_str_lit_18;
        if (*index == 1LL) return &_til_str_lit_18;
        if (*index == 2LL) return &_til_str_lit_18;
        if (*index == 3LL) return &_til_str_lit_18;
        if (*index == 4LL) return &_til_str_lit_18;
        if (*index == 5LL) return &_til_str_lit_18;
        if (*index == 6LL) return &_til_str_lit_18;
        if (*index == 7LL) return &_til_str_lit_18;
        if (*index == 8LL) return &_til_str_lit_18;
        if (*index == 9LL) return &_til_str_lit_18;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_18;
        if (*index == 1LL) return &_til_str_lit_18;
        if (*index == 2LL) return &_til_str_lit_6;
        if (*index == 3LL) return &_til_str_lit_18;
        if (*index == 4LL) return &_til_str_lit_6;
        if (*index == 5LL) return &_til_str_lit_18;
        if (*index == 6LL) return &_til_str_lit_18;
        if (*index == 7LL) return &_til_str_lit_18;
        if (*index == 8LL) return &_til_str_lit_18;
        if (*index == 9LL) return &_til_str_lit_6;
        if (*index == 10LL) return &_til_str_lit_28;
        if (*index == 11LL) return &_til_str_lit_6;
        if (*index == 12LL) return &_til_str_lit_18;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_18;
        if (*index == 1LL) return &_til_str_lit_18;
        if (*index == 2LL) return &_til_str_lit_18;
        if (*index == 3LL) return &_til_str_lit_18;
        if (*index == 4LL) return &_til_str_lit_18;
        if (*index == 5LL) return &_til_str_lit_18;
        if (*index == 6LL) return &_til_str_lit_18;
        if (*index == 7LL) return &_til_str_lit_18;
        if (*index == 8LL) return &_til_str_lit_18;
        if (*index == 9LL) return &_til_str_lit_18;
        if (*index == 10LL) return &_til_str_lit_18;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_18;
        if (*index == 1LL) return &_til_str_lit_18;
        if (*index == 2LL) return &_til_str_lit_18;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "GcStorage", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_18;
        if (*index == 1LL) return &_til_str_lit_18;
        if (*index == 2LL) return &_til_str_lit_18;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_104;
        if (*index == 2LL) return &_til_str_lit_17;
        if (*index == 3LL) return &_til_str_lit_18;
        if (*index == 4LL) return &_til_str_lit_18;
        if (*index == 5LL) return &_til_str_lit_18;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_18;
        if (*index == 1LL) return &_til_str_lit_109;
        if (*index == 2LL) return &_til_str_lit_111;
        if (*index == 3LL) return &_til_str_lit_113;
        if (*index == 4LL) return &_til_str_lit_115;
        if (*index == 5LL) return &_til_str_lit_117;
        if (*index == 6LL) return &_til_str_lit_118;
        if (*index == 7LL) return &_til_str_lit_22;
        if (*index == 8LL) return &_til_str_lit_24;
        if (*index == 9LL) return &_til_str_lit_120;
        if (*index == 10LL) return &_til_str_lit_122;
        if (*index == 11LL) return &_til_str_lit_18;
        if (*index == 12LL) return &_til_str_lit_18;
        if (*index == 13LL) return &_til_str_lit_18;
        if (*index == 14LL) return &_til_str_lit_127;
        if (*index == 15LL) return &_til_str_lit_6;
        if (*index == 16LL) return &_til_str_lit_18;
        if (*index == 17LL) return &_til_str_lit_18;
        if (*index == 18LL) return &_til_str_lit_18;
        if (*index == 19LL) return &_til_str_lit_133;
        if (*index == 20LL) return &_til_str_lit_18;
        if (*index == 21LL) return &_til_str_lit_18;
        if (*index == 22LL) return &_til_str_lit_18;
        if (*index == 23LL) return &_til_str_lit_18;
        if (*index == 24LL) return &_til_str_lit_18;
        if (*index == 25LL) return &_til_str_lit_140;
        if (*index == 26LL) return &_til_str_lit_18;
        if (*index == 27LL) return &_til_str_lit_140;
        if (*index == 28LL) return &_til_str_lit_18;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_18;
        if (*index == 1LL) return &_til_str_lit_18;
        if (*index == 2LL) return &_til_str_lit_18;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_15;
        if (*index == 1LL) return &_til_str_lit_6;
        if (*index == 2LL) return &_til_str_lit_18;
    }
    fprintf(stderr, "enum_variant_payload_type: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
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
        if (*index == 0LL) return &_til_str_lit_9;
        if (*index == 1LL) return &_til_str_lit_3;
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
        if (*index == 0LL) return &_til_str_lit_10;
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
